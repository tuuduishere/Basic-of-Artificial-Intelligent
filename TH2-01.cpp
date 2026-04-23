#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;

vector<int> welshPowellColoring(const vector<vector<int>> &graph, int n) {
    vector<int> degree(n, 0), color(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) degree[i]++;
        }
    }
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return degree[a] > degree[b]; });
    
    int currentColor = 0;
    for (int v : order) {
        if (color[v] == -1) {
            color[v] = currentColor;
            for (int u : order) {
                if (color[u] == -1) {
                    bool canColor = true;
                    for (int k = 0; k < n; k++) {
                        if (graph[u][k] && color[k] == currentColor) {
                            canColor = false;
                            break;
                        }
                    }
                    if (canColor) color[u] = currentColor;
                }
            }
            currentColor++;
        }
    }
    return color;
}

int main() {
    ifstream input("inputWP.txt");
    int n;
    input >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            input >> graph[i][j];
        }
    }
    input.close();
    
    vector<int> colorWP = welshPowellColoring(graph, n);
    cout << "Ket qua to: \n";
    for (int i = 0; i < n; i++) cout << "Dinh:" << (i + 1) << " Mau: " << colorWP[i] << endl;
    cout << endl;
    return 0;
}
