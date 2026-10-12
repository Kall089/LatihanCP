/*
============================================================
📋 TUGAS 09: Restaurant Customers
============================================================
Source: CSES 1619
Difficulty: Easy
Topics: sweep line / difference array pada koordinat besar (Day 31 + 38)

PROBLEM:
Sebuah restoran mencatat N pelanggan. Pelanggan ke-i datang pada waktu
A[i] dan pergi pada waktu B[i]; ia berada di dalam restoran selama
interval [A[i], B[i]).

PERHATIKAN: interval di soal ini SETENGAH TERBUKA - pelanggan sudah
pergi tepat pada waktu B[i]. Bandingkan dengan Exercise 6 yang memakai
interval tertutup, dan perhatikan bagaimana satu detail ini mengubah
kodemu.

Cari jumlah pelanggan terbanyak yang berada di restoran bersamaan.

INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: A[i] dan B[i]

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= A[i] < B[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
3
5 8
2 4
3 9
output:
2
penjelasan: pada waktu 5..8 ada pelanggan 1 dan 3.

SAMPLE 2 - bersentuhan di ujung
input:
3
1 2
2 3
3 4
output:
1
penjelasan: karena intervalnya setengah terbuka, pelanggan 1 sudah
pergi tepat saat pelanggan 2 datang. Jawabannya 1, bukan 2.
Kalau kamu menjawab 2, kamu memperlakukannya sebagai interval tertutup.

SAMPLE 3 - N = 1
input:
1
1 10
output:
1

SAMPLE 4 - tidak ada yang berbarengan
input:
3
1 2
3 4
5 6
output:
1
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- interval SETENGAH TERBUKA -> peristiwa (A, +1) dan (B, -1), TANPA +1
- pada waktu yang sama, -1 harus diproses SEBELUM +1. Cara mudah:
  urutkan pasangan (waktu, delta), karena -1 < +1 secara numerik
- jangan membuat array sebesar 10^9
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
