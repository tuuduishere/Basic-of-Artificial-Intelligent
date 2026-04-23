#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;

vector<int> dsaturColoring(const vector<vector<int>> &graph, int n) {
    vector<int> color(n, -1), degree(n, 0), saturation(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) degree[i]++;
        }
    }
    auto maxSaturation = [&](int v) { return make_pair(saturation[v], degree[v]); };
    set<int> uncolored;
    for (int i = 0; i < n; i++) uncolored.insert(i);

    while (!uncolored.empty()) {
        int v = *max_element(uncolored.begin(), uncolored.end(), [&](int a, int b) {
            return maxSaturation(a) < maxSaturation(b);
        });
        uncolored.erase(v);
        
        set<int> usedColors;
        for (int i = 0; i < n; i++) {
            if (graph[v][i] && color[i] != -1) {
                usedColors.insert(color[i]);
            }
        }
        int c = 0;
        while (usedColors.count(c)) c++;
        color[v] = c;

        for (int i : uncolored) {
            if (graph[v][i]) {
                set<int> neighborColors;
                for (int j = 0; j < n; j++) {
                    if (graph[i][j] && color[j] != -1) {
                        neighborColors.insert(color[j]);
                    }
                }
                saturation[i] = neighborColors.size();
            }
        }
    }
    return color;
}

int main() {
    ifstream inputFile("inputDSA.txt");
    if (!inputFile) {
        cout << "Cant open" << endl;
        return 1;
    }
    
    int n;
    inputFile >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i][j];
        }
    }
    inputFile.close();
    
    vector<int> color = dsaturColoring(graph, n);
    cout << "Ket qua to \n";
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << (i + 1) << " : Mau " << color[i] << "\n";
    }
    return 0;
}
