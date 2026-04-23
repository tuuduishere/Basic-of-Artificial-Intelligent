#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct Machine {
    int id, finishTime;
    Machine(int _id) : id(_id), finishTime(0) {}
    bool operator<(const Machine &other) const {
        return finishTime > other.finishTime || (finishTime == other.finishTime && id > other.id);
    }
};

int main() {
    ifstream input("schedulex.txt");
    int n;
    input >> n;
    vector<int> jobTimes(n);
    for (int i = 0; i < n; i++) {
        input >> jobTimes[i];
    }
    input.close();
    
    int m = 3; // Số lượng máy cố định là 3
    vector<vector<pair<int, int>>> machines(m);
    priority_queue<Machine> pq;
    for (int i = 0; i < m; i++) {
        pq.push(Machine(i));
    }
    
    for (int i = 0; i < n; i++) {
        Machine machine = pq.top();
        pq.pop();
        machine.finishTime += jobTimes[i];
        machines[machine.id].push_back({i + 1, jobTimes[i]});
        pq.push(machine);
    }
    
    int maxTime = 0;
    for (int i = 0; i < m; i++) {
        cout << "P" << i + 1 << ": ";
        int finish = 0;
        for (auto job : machines[i]) {
            cout << "J" << job.first << "(" << job.second << ") ";
            finish += job.second;
        }
        maxTime = max(maxTime, finish);
        cout << endl;
    }
    cout << "\nThoi gian hoan thanh tat ca cong viec la: " << maxTime << endl;
    return 0;
}