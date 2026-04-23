#include <iostream>

#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Job {
    int id, a, b;
};

bool compareN1(const Job &j1, const Job &j2) {
    return j1.a < j2.a;
}

bool compareN2(const Job &j1, const Job &j2) {
    return j1.b > j2.b;
}

vector<Job> johnsonAlgorithm(vector<Job> &jobs) {
    vector<Job> N1, N2;
    for (const auto &job : jobs) {
        if (job.a <= job.b) N1.push_back(job);
        else N2.push_back(job);
    }
    sort(N1.begin(), N1.end(), compareN1);
    sort(N2.begin(), N2.end(), compareN2);
    N1.insert(N1.end(), N2.begin(), N2.end());
    return N1;
}

int computeCompletionTime(const vector<Job> &schedule) {
    int timeA = 0, timeB = 0;
    for (const auto &job : schedule) {
        timeA += job.a;
        timeB = max(timeA, timeB) + job.b;
    }
    return timeB;
}

int main() {
    ifstream input("Johnsonx.txt");
    if (!input) {
        cerr << "Khong the mo file input.txt" << endl;
        return 1;
    }
    
    int n;
    input >> n;
    vector<Job> jobs(n);
    
    for (int i = 0; i < n; i++) {
        jobs[i].id = i + 1;
    }
    
    for (int i = 0; i < n; i++) {
        input >> jobs[i].a;
    }
    for (int i = 0; i < n; i++) {
        input >> jobs[i].b;
    }
    input.close();

    vector<Job> schedule = johnsonAlgorithm(jobs);
    cout << "Lich gia cong: ";
    for (const auto &job : schedule) {
        cout << "J" << job.id << " ";
    }
    cout << endl;

    int totalCompletionTime = computeCompletionTime(schedule);
    cout << "Thoi gian hoan thanh tat ca cong viec: " << totalCompletionTime << endl;
    
    return 0;
}
