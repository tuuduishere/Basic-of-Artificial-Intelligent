#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef pair<int, string> Node;
#define INF numeric_limits<int>::max()

struct Graph {
    unordered_map<string, unordered_map<string, int>> adj;
};

vector<string> a_star(Graph& graph, unordered_map<string, int>& heuristic, string start, string goal, int& path_length) {
    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    unordered_map<string, string> came_from;
    unordered_map<string, int> g_score;
    unordered_map<string, int> f_score;
    
    for (auto& node : graph.adj) {
        g_score[node.first] = INF;
        f_score[node.first] = INF;
    }
    g_score[start] = 0;
    f_score[start] = heuristic[start];
    open_set.push({f_score[start], start});
    
    while (!open_set.empty()) {
        string current = open_set.top().second;
        open_set.pop();
        
        if (current == goal) {
            vector<string> path;
            path_length = g_score[goal];
            while (came_from.find(current) != came_from.end()) {
                path.push_back(current);
                current = came_from[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        
        for (auto& neighbor : graph.adj[current]) {
            int tentative_g_score = g_score[current] + neighbor.second;
            if (tentative_g_score < g_score[neighbor.first]) {
                came_from[neighbor.first] = current;
                g_score[neighbor.first] = tentative_g_score;
                f_score[neighbor.first] = g_score[neighbor.first] + heuristic[neighbor.first];
                open_set.push({f_score[neighbor.first], neighbor.first});
            }
        }
    }
    path_length = -1;
    return {};
}

void read_graph_from_file(const string& filename, Graph& graph, unordered_map<string, int>& heuristic, string& start, string& goal) {
    ifstream file(filename);
    if (!file) {
        cerr << "Can't open" << endl;
        exit(1);
    }
    
    int n, m;
    file >> n >> m;
    file >> start >> goal;
    
    for (int i = 0; i < m; i++) {
        string u, v;
        int cost;
        file >> u >> v >> cost;
        graph.adj[u][v] = cost;
        graph.adj[v][u] = cost;
    }
    
    for (int i = 0; i < n; i++) {
        string node;
        int h;
        file >> node >> h;
        heuristic[node] = h;
    }
    
    file.close();
}

int main() {
    Graph graph;
    unordered_map<string, int> heuristic;
    string start, goal;
    int path_length = 0;
    
    read_graph_from_file("pathx.txt", graph, heuristic, start, goal);
    
    vector<string> path = a_star(graph, heuristic, start, goal, path_length);
    
    if (!path.empty()) {
        cout << "\nBest way: ";
        for (const auto& node : path) {
            cout << node << " ";
        }
        cout << "\nLength: " << path_length<< endl;
    } else {
        cout << "\nCan't find path!";
    }
    return 0;
}
