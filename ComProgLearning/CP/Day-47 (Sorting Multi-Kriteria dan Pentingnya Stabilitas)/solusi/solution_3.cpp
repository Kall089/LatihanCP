// Day 16 — Custom Comparator
// File  : solution_3.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Task {
    string name;
    int deadline, priority;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<Task> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].name >> v[i].deadline >> v[i].priority;

    sort(v.begin(), v.end(), [](const Task& a, const Task& b) {
        if (a.deadline != b.deadline) return a.deadline < b.deadline;
        if (a.priority != b.priority) return a.priority > b.priority;
        return a.name < b.name;
    });

    for (auto& t : v)
        cout << t.name << " " << t.deadline << " " << t.priority << "\n";

    return 0;
}
