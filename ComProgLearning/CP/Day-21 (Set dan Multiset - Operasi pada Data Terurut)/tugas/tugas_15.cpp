/*
============================================================
📋 TUGAS 15: LRU Cache Simulation (Map + List concept)
============================================================
Source: LeetCode-style / Codeforces
Difficulty: Hard
Topics: map, deque/set for order tracking

PROBLEM:
Simulasikan cache dengan kapasitas K. Ada N access requests (integer ID).
Untuk setiap request:
- Jika ID sudah ada di cache: "HIT" (pindahkan ke most-recent)
- Jika ID tidak ada:
  - Jika cache belum penuh: "MISS" (tambahkan ke cache)
  - Jika cache penuh: "MISS" (buang yang LEAST RECENTLY USED, tambah baru)

Setelah semua request, cetak isi cache dari most recent ke least recent.

INPUT:
- Baris pertama: dua integer N dan K
- Baris kedua: N integer (ID request)

OUTPUT:
- N baris: "HIT" atau "MISS" untuk setiap request
- Baris terakhir: isi cache (most recent → least recent)

CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- 1 ≤ ID ≤ 1,000,000,000

SAMPLE INPUT:
7 3
1 2 3 4 2 1 5

SAMPLE OUTPUT:
MISS
MISS
MISS
MISS
HIT
MISS
MISS
5 1 2

NOTE: 
- req 1: cache=[1], MISS
- req 2: cache=[2,1], MISS
- req 3: cache=[3,2,1], MISS (full)
- req 4: cache=[4,3,2], MISS (evict 1)
- req 2: cache=[2,4,3], HIT (move 2 to front)
- req 1: cache=[1,2,4], MISS (evict 3)
- req 5: cache=[5,1,2], MISS (evict 4)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Gunakan list<int> + unordered_map<int, list<int>::iterator>
    //       Atau simulasi dengan deque + set untuk cek existence

    return 0;
}
