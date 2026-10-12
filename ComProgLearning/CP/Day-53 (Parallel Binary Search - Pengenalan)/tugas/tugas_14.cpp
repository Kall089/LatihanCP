/*
============================================================
📋 TUGAS 14: Batas Waktu Ketat
============================================================
Source: Original
Difficulty: Hard
Topics: analisis kompleksitas

PROBLEM:
Sebuah soal punya N = 2*10^5 kejadian dan Q = 2*10^5 query. Diberikan
biaya menerapkan satu kejadian (C) dan biaya menjawab satu query (Cq)
dalam satuan operasi, tentukan apakah parallel binary search akan lolos
dalam batas 10^8 operasi. Cetak LOLOS atau TIDAK untuk setiap kasus.

INPUT FORMAT:
- Baris pertama: T
- T baris: C dan Cq

OUTPUT FORMAT:
- T baris

CONSTRAINTS:
- 1 <= T <= 100
- 1 <= C, Cq <= 1000

SAMPLE INPUT 1:
2
20 20
500 500

SAMPLE OUTPUT 1:
LOLOS
TIDAK
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Rumusnya log(N) * (N*C + Q*Cq). Soal ini melatihmu MENGHITUNG sebelum menulis, bukan menulis lalu berharap.

    return 0;
}
