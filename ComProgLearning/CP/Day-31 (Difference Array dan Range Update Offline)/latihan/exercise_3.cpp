/*
============================================================
🏋️ Exercise 3: Pengunjung Restoran Terbanyak
============================================================
Day: 29 | Difficulty: Medium
Topic: Sweep Line / Event Counting (difference array pada koordinat besar)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah restoran mencatat waktu datang dan waktu pergi setiap pelanggan.
Pelanggan ke-i datang pada waktu a[i] dan pergi pada waktu b[i].
Artinya pelanggan tersebut BERADA di dalam restoran pada rentang waktu
[a[i], b[i]) — sudah tidak dihitung tepat pada saat b[i].
Manajer ingin tahu berapa jumlah pelanggan TERBANYAK yang berada
di dalam restoran pada saat yang bersamaan.

Perhatikan: nilai waktu bisa mencapai 10^9, jadi kamu TIDAK BISA
membuat array sepanjang sumbu waktu.

📥 INPUT FORMAT:
- Baris pertama: satu integer N (jumlah pelanggan)
- N baris berikutnya: dua integer a[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu integer: jumlah pelanggan terbanyak yang bersamaan.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2 × 10^5
- 1 ≤ a[i] < b[i] ≤ 10^9

📎 SAMPLE INPUT 1:
3
5 8
2 4
3 9

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
4
1 10
2 3
2 5
6 7

📎 SAMPLE OUTPUT 2:
3

💡 HINT:
- Ini tetap difference array, hanya saja indeksnya tidak bisa jadi array.
- Buat daftar "kejadian": (waktu datang, +1) dan (waktu pergi, -1).
- Urutkan semua kejadian menurut waktu. Kalau waktunya sama,
  proses yang -1 lebih dulu (karena pergi tepat di b tidak lagi dihitung).
- Jalankan penjumlahan berjalan, catat nilai terbesarnya.

🎯 Learning Goals:
- [ ] Mengenali sweep line sebagai difference array pada koordinat besar
- [ ] Menangani urutan kejadian saat waktunya sama (tie-breaking)
- [ ] Menyelesaikan soal tipe "paling banyak bersamaan"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n;
    cin >> n;

    vector<pair<int, int>> events;
    events.reserve(n * 2);

    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        events.push_back({u, 1});
        events.push_back({v, -1});
    }

    sort(events.begin(), events.end());

    int max_val = 0;
    int curr = 0;

    for (const auto &event : events)
    {
        curr += event.second;
        max_val = max(curr, max_val);
    }

    cout << max_val;
}