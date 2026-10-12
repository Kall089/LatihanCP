/*
============================================================
📋 TUGAS 2: Queue — Print Order
============================================================
Source: Original
Difficulty: Easy
Topics: queue

PROBLEM:
Ada N dokumen di printer queue. Setiap dokumen punya priority (1-9).
Printer HANYA mencetak dokumen dengan priority TERTINGGI di antrian.
Jika depan antrian bukan priority tertinggi, pindah ke belakang antrian.

Berapa kali cetak sampai dokumen di posisi M (0-indexed) tercetak?

INPUT:
- Baris pertama: dua integer N dan M
- Baris kedua: N integer (priority masing-masing dokumen)

OUTPUT:
- Satu integer: urutan cetak dokumen ke-M

CONSTRAINTS:
- 1 ≤ N ≤ 100
- 0 ≤ M < N
- 1 ≤ priority ≤ 9

SAMPLE INPUT:
4 2
1 3 4 2

SAMPLE OUTPUT:
2

NOTE: Queue: [1,3,4,2]. Dokumen target = index 2 (priority 4).
      - Front=1, bukan max(4). Move to back: [3,4,2,1]
      - Front=3, bukan max(4). Move to back: [4,2,1,3]
      - Front=4, IS max. PRINT! Count=1. Queue: [2,1,3]
      Tapi target kita sudah tercetak (itu index 2 asal), jadi jawaban = 1?
      
      Wait, re-check: target awal index 2 = priority 4.
      Setelah rotasi: [3,4,2,1] — target sekarang di index 1
      Rotasi lagi: [4,2,1,3] — target sekarang di index 0
      Print 4 (target!) — count = 1? 
      
      Hmm let me re-trace:
      Urutan cetak: 4 (count=1), 3 (count=2), 2, 1
      Target priority 4 dicetak ke-1.
      Actually sample output = 2, let me re-read...
      
      Re-check: N=4, M=2 berarti dokumen di posisi awal index 2.
      Priority array = [1, 3, 4, 2]. Target = dokumen index 2 = priority 4.
      Ini dicetak pertama (highest priority). Tapi output = 2?
      
      Hmm perhaps: posisi 0-indexed. Let me use different sample:
      
UPDATED SAMPLE:
N=4 M=0, priorities = [1, 3, 4, 2]
Target = index 0 (priority 1). This gets printed last → output 4.

ACTUAL SAMPLE INPUT:
4 0
1 3 4 2

ACTUAL SAMPLE OUTPUT:
4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Simulasi queue<pair<int,int>> (priority, original_index)
    //       Cek apakah front = max priority. Jika ya: cetak. Jika tidak: pindah ke belakang.

    return 0;
}
