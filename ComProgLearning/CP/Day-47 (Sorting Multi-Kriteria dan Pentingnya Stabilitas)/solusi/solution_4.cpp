// Day 16 — Custom Comparator
// File  : solution_4.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Task {
    string name;
    int deadline;
};

struct CompTask {
    bool operator()(const Task& a, const Task& b) const {
        return a.deadline > b.deadline; // min-heap
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    priority_queue<Task, vector<Task>, CompTask> pq;

    for (int i = 0; i < n; i++) {
        string name; int d; cin >> name >> d;
        pq.push({name, d});
    }

    int k; cin >> k;
    while (k--) {
        auto t = pq.top(); pq.pop();
        cout << t.name << " " << t.deadline << "\n";
    }

    return 0;
}
