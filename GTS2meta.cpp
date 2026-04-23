#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

int n;
vector<vector<double>> dist;

double calcDistance(const vector<int>& tour) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += dist[tour[i]][tour[(i + 1) % n]];
    }
    return total;
}

void twoOptSwap(vector<int>& tour, int i, int k) {
    reverse(tour.begin() + i, tour.begin() + k + 1);
}

vector<int> greedy2Opt(const vector<vector<double>>& distMatrix) {
    vector<int> tour(n);
    iota(tour.begin(), tour.end(), 0);

    bool improved = true;
    while (improved) {
        improved = false;
        double bestDistance = calcDistance(tour);

        for (int i = 1; i < n - 1; i++) {
            for (int k = i + 1; k < n; k++) {
                vector<int> newTour = tour;
                twoOptSwap(newTour, i, k);
                double newDist = calcDistance(newTour);

                if (newDist < bestDistance) {
                    tour = newTour;
                    bestDistance = newDist;
                    improved = true;
                }
            }
        }
    }

    return tour;
}

int main() {
    ifstream file("tspx.txt");
    file >> n;
    dist.resize(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> dist[i][j];

    auto start = high_resolution_clock::now();

    vector<int> bestTour = greedy2Opt(dist);
    double bestDist = calcDistance(bestTour);

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    cout << "Best Tour (GTS2): ";
    for (int i : bestTour) cout << i << " ";
    cout << bestTour[0] << endl; // quay lại điểm xuất phát

    cout << "Total Distance: " << bestDist << endl;
    cout << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds" << endl;

    return 0;
}
