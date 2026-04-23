#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

const int INF = numeric_limits<int>::max();

void readData(const string &filename, vector<vector<int>> &costMatrix, int &n, vector<int> &initialCities) {
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file!" << endl;
        exit(1);
    }
    file >> n;
    int p;
    file >> p;
    initialCities.resize(p);
    for (int i = 0; i < p; i++) {
        file >> initialCities[i];
        initialCities[i]--; // Chuyển về chỉ số từ 0
    }
    costMatrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> costMatrix[i][j];
        }
    }
    file.close();
}

vector<int> GTS1_TSP(const vector<vector<int>> &costMatrix, int n, int start, int &cost) {
    vector<bool> visited(n, false);
    vector<int> tour = {start};
    visited[start] = true;
    cost = 0;
    int v = start;
    
    for (int i = 1; i < n; i++) {
        int nextCity = -1, minCost = INF;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && costMatrix[v][j] < minCost) {
                minCost = costMatrix[v][j];
                nextCity = j;
            }
        }
        tour.push_back(nextCity);
        cost += minCost;
        visited[nextCity] = true;
        v = nextCity;
    }
    tour.push_back(start); // Quay về thành phố xuất phát
    cost += costMatrix[v][start];
    return tour;
}

void GTS2_TSP(const vector<vector<int>> &costMatrix, int n, const vector<int> &initialCities) {
    int bestCost = INF;
    vector<int> bestTour;
    
    for (int start : initialCities) {
        int cost;
        vector<int> tour = GTS1_TSP(costMatrix, n, start, cost);
        if (cost < bestCost) {
            bestCost = cost;
            bestTour = tour;
        }
    }
    
    cout << "Best: ";
    for (int city : bestTour) {
        cout << city + 1 << " ";
    }
    cout << "\nCost: " << bestCost << endl;
}

int main() {
    vector<vector<int>> costMatrix;
    int n;
    vector<int> initialCities;
    readData("GTS2x.txt", costMatrix, n, initialCities);
    GTS2_TSP(costMatrix, n, initialCities);
    return 0;
}
