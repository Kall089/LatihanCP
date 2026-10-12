/*
============================================================
  Exercise 1: Queue Simulation — Process Scheduling
============================================================
Simulasikan Round-Robin CPU scheduling menggunakan queue.
Diberikan n proses dengan burst time masing-masing dan quantum time.
Cetak urutan proses yang selesai dan total waiting time rata-rata.

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 100
  - 1 ≤ burst[i] ≤ 1000
  - 1 ≤ quantum ≤ 100

📎 SAMPLE INPUT:
  3 2
  4 3 5

📎 SAMPLE OUTPUT:
  P2 selesai di t=5
  P1 selesai di t=9
  P3 selesai di t=12
  Avg waiting time: 3.33

💡 HINT:
  Gunakan queue<pair<int,int>> untuk {burst_sisa, process_id}.
  Setiap iterasi: dequeue, kurangi quantum, jika masih sisa → enqueue kembali.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, quantum; cin >> n >> quantum;
    queue<pair<int,int>> q; // {burst_sisa, pid}
    vector<int> burst(n);
    for (int i = 0; i < n; i++) {
        cin >> burst[i];
        q.push({burst[i], i+1});
    }

    int time = 0;
    double total_wait = 0;

    while (!q.empty()) {
        auto [b, pid] = q.front(); q.pop();

        // TODO: proses dengan quantum
        // Jika b > quantum → kurangi dan re-enqueue
        // Jika b <= quantum → selesai, hitung waiting time
    }

    cout << fixed << setprecision(2);
    cout << "Avg waiting time: " << total_wait/n << "\n";
    return 0;
}
