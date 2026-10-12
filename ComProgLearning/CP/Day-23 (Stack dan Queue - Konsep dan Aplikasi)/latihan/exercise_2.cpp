/*
============================================================
🏋️ Exercise 2: Queue Simulation (Kasir)
============================================================
Day: 5 | Difficulty: Easy
Topic: Queue, simulation
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N orang mengantri di kasir. Setiap orang butuh waktu t[i] detik
untuk dilayani. Kasir melayani satu per satu dari depan antrian.

Untuk setiap orang, cetak WAKTU selesai mereka dilayani (kumulatif).

📥 INPUT FORMAT:
- Baris pertama: integer N
- Baris kedua: N integer (waktu layanan masing-masing orang)

📤 OUTPUT FORMAT:
- N integer: waktu selesai masing-masing orang (dipisah spasi)

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ t[i] ≤ 1,000

📎 SAMPLE INPUT 1:
5
3 2 5 1 4

📎 SAMPLE OUTPUT 1:
3 5 10 11 15

📎 SAMPLE INPUT 2:
3
1 1 1

📎 SAMPLE OUTPUT 2:
1 2 3

💡 HINT: Cukup hitung prefix sum! Tapi implementasi dengan queue
         untuk latihan konsep FIFO.

🎯 Learning Goals:
- [ ] Simulasi antrian dengan queue
- [ ] Proses FIFO (first in, first out)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        q.push(t);
    }

    int curr = 0;
    while (!q.empty())
    {
        curr += q.front();
        cout << curr << " ";
        q.pop();
    }

    // TODO: Masukkan semua ke queue

    // TODO: Proses queue: current_time += waktu, output current_time

    return 0;
}
