#include <iostream>
#include <bits/stdc++.h>
#include <chrono> // Thêm thư viện chrono
using namespace std;

int n; // số thành phố
vector<vector<double>> distanceMatrix;

int POP_SIZE = 50;
int GENERATIONS = 500;
double CROSSOVER_RATE = 0.8;
double MUTATION_RATE = 0.02;
int RUNS = 500;

double totalDistance(const vector<int>& route) {
    double dist = 0;
    for (int i = 0; i < n; i++)
        dist += distanceMatrix[route[i]][route[(i + 1) % n]];
    return dist;
}

vector<int> randomRoute() {
    vector<int> route(n);
    iota(route.begin(), route.end(), 0);
    random_shuffle(route.begin(), route.end());
    return route;
}

vector<vector<int>> initializePopulation() {
    vector<vector<int>> population;
    for (int i = 0; i < POP_SIZE; i++)
        population.push_back(randomRoute());
    return population;
}

vector<int> tournamentSelection(vector<vector<int>>& pop) {
    int k = 5;
    double bestDist = 1e9;
    vector<int> best;
    for (int i = 0; i < k; i++) {
        int idx = rand() % pop.size();
        double dist = totalDistance(pop[idx]);
        if (dist < bestDist) {
            bestDist = dist;
            best = pop[idx];
        }
    }
    return best;
}

vector<int> crossoverOX(const vector<int>& p1, const vector<int>& p2) {
    int a = rand() % n, b = rand() % n;
    if (a > b) swap(a, b);
    vector<int> child(n, -1);
    unordered_set<int> inChild;
    for (int i = a; i <= b; i++) {
        child[i] = p1[i];
        inChild.insert(p1[i]);
    }
    int j = (b + 1) % n;
    for (int i = 0; i < n; i++) {
        int idx = (b + 1 + i) % n;
        if (!inChild.count(p2[idx])) {
            child[j] = p2[idx];
            j = (j + 1) % n;
        }
    }
    return child;
}

void mutate(vector<int>& individual) {
    if ((double) rand() / RAND_MAX < MUTATION_RATE) {
        int i = rand() % n;
        int j = rand() % n;
        swap(individual[i], individual[j]);
    }
}

int main() {
    srand(time(0));
    ifstream file("tspx.txt");
    file >> n;
    distanceMatrix.resize(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> distanceMatrix[i][j];

    auto start = chrono::high_resolution_clock::now(); // Bắt đầu đếm thời gian

    vector<int> globalBest;
    double globalBestDist = 1e9;

    for (int run = 1; run <= RUNS; run++) {
        auto population = initializePopulation();
        vector<int> best;
        double bestDist = 1e9;

        for (int gen = 0; gen < GENERATIONS; gen++) {
            vector<vector<int>> newPop;
            for (int i = 0; i < POP_SIZE; i++) {
                auto parent1 = tournamentSelection(population);
                auto parent2 = tournamentSelection(population);
                vector<int> child = ((double) rand() / RAND_MAX < CROSSOVER_RATE) ?
                    crossoverOX(parent1, parent2) : parent1;
                mutate(child);
                newPop.push_back(child);
                double d = totalDistance(child);
                if (d < bestDist) {
                    bestDist = d;
                    best = child;
                }
            }
            population = newPop;
        }

        cout << "Chay input lan " << run << " Best Cost " << bestDist << endl;

        if (bestDist < globalBestDist) {
            globalBestDist = bestDist;
            globalBest = best;
        }
    }

    cout << "Final PATH: "<< endl;
    for (int i : globalBest) cout << i << " ";
    cout << globalBest[0]; // quay lại điểm xuất phát
    cout << "\nTong quang duong tot nhat: " << globalBestDist << endl;

    auto end = chrono::high_resolution_clock::now(); // Kết thúc đếm thời gian
    chrono::duration<double> elapsed = end - start;
    cout << "Thoi gian chay chuong trinh: " << elapsed.count() << " giay" << endl;

    return 0;
}
