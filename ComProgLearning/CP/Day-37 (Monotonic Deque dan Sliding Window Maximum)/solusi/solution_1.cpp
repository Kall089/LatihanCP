/*
============================================================
  Solution 1: Queue Simulation — Round-Robin Scheduling
============================================================
Kompleksitas: O(n × ceil(max_burst/quantum))
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, quantum; cin >> n >> quantum;
    queue<pair<int,int>> q;
    vector<int> burst(n), arrival(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> burst[i];
        q.push({burst[i], i+1});
    }
    int time = 0;
    double total_wait = 0;
    vector<int> finish(n+1, 0);
    while (!q.empty()) {
        auto [b, pid] = q.front(); q.pop();
        if (b > quantum) {
            time += quantum;
            q.push({b - quantum, pid});
        } else {
            time += b;
            finish[pid] = time;
            int wait = finish[pid] - burst[pid-1];
            total_wait += wait;
            cout << "P" << pid << " selesai di t=" << time << "\n";
        }
    }
    cout << fixed << setprecision(2);
    cout << "Avg waiting time: " << total_wait/n << "\n";
    return 0;
}
