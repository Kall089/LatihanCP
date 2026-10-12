/*
============================================================
📋 TUGAS 09: Task Scheduler
============================================================
Source: LeetCode 621
Difficulty: Medium
Topics: Heap + penjadwalan

PROBLEM:
Ada n tugas, masing-masing berupa satu huruf kapital. Dua tugas dengan huruf yang SAMA
harus dipisahkan oleh setidaknya k satuan waktu. Setiap satuan waktu kamu mengerjakan
satu tugas atau menganggur.
Cari waktu total minimum untuk menyelesaikan seluruh tugas.

INPUT FORMAT:
Baris 1: n dan k
Baris 2: string berisi n huruf kapital

OUTPUT FORMAT:
Satu bilangan: waktu total minimum

CONSTRAINTS:
1 <= n <= 10^4, 0 <= k <= 100

SAMPLE INPUT 1:
6 2
AAABBB

SAMPLE OUTPUT 1:
8
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Solusi heap: selalu jalankan tugas dengan sisa terbanyak yang sedang tidak dalam masa tunggu. Ada juga rumus tertutup — cari sendiri, lalu buktikan keduanya memberi hasil sama dengan stress test.

    return 0;
}
