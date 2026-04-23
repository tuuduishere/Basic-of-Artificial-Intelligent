#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

const int INF = numeric_limits<int>::max();

void readData(const string &filename, vector<vector<int>> &costMatrix, int &n, int &u) {
    ifstream file(filename);
    if (!file) {
        cerr << "Loi mo file!" << endl;
        exit(1);
    }
    file >> n >> u;
    u--; // Chuyển về chỉ số từ 0
    costMatrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> costMatrix[i][j];
        }
    }
    file.close();
}

vector<int> GTS1_TSP(const vector<vector<int>> &costMatrix, int n, int start) {
    vector<bool> visited(n, false);
    vector<int> tour = {start};
    visited[start] = true;
    int cost = 0, v = start;
    
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
    
    cout << "Best: ";
    for (int city : tour) {
        cout << city + 1 << " ";
    }
    cout << "\nCost: " << cost << endl;
    return tour;
}

int main() {
    vector<vector<int>> costMatrix;
    int n, start;
    readData("GTS1x.txt", costMatrix, n, start);
    GTS1_TSP(costMatrix, n, start);
    return 0;
}