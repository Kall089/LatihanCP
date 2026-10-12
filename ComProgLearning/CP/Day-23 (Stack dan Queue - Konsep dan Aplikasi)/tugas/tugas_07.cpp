/*
============================================================
📋 TUGAS 7: Queue — Round Robin Scheduling
============================================================
Source: Classic OS Scheduling
Difficulty: Medium
Topics: queue, simulation

PROBLEM:
Ada N proses, masing-masing punya nama dan waktu eksekusi.
CPU menggunakan Round Robin scheduling dengan time quantum Q.
Setiap proses dieksekusi maksimal Q ms, lalu pindah ke belakang
antrian jika belum selesai.

Cetak waktu selesai setiap proses (dalam urutan selesai).

INPUT:
- Baris pertama: dua integer N dan Q
- N baris berikutnya: nama (string) dan waktu (integer)

OUTPUT:
- Untuk setiap proses yang selesai: "nama waktu_selesai"
  (urut berdasarkan waktu selesai)

CONSTRAINTS:
- 1 ≤ N ≤ 100,000
- 1 ≤ Q ≤ 1,000
- 1 ≤ waktu ≤ 100,000

SAMPLE INPUT:
3 2
P1 5
P2 3
P3 2

SAMPLE OUTPUT:
P3 6
P2 9
P1 10

NOTE: t=0-2: P1 (sisa 3). t=2-4: P2 (sisa 1). t=4-6: P3 (done!).
      t=6-8: P1 (sisa 1). t=8-9: P2 (done!). t=9-10: P1 (done!).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
