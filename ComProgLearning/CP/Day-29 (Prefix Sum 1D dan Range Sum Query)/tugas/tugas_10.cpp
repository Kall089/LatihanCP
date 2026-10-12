/*
============================================================
📋 TUGAS 10: Prefix Sum Melingkar
============================================================
Source: Original
Difficulty: Medium
Topics: prefix + duplikasi array

PROBLEM:
Diberikan array melingkar berisi N bilangan (setelah elemen terakhir kembali
ke elemen pertama) dan Q pertanyaan rentang [L, R] yang boleh MELINGKAR
(artinya L bisa lebih besar dari R). Cetak jumlah elemen pada rentang itu.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: L dan R (1-based)

OUTPUT FORMAT:
- Q baris berisi bilangan

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
4 2
1 2 3 4
2 3
4 2

SAMPLE OUTPUT 1:
5
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kalau L <= R rentang biasa; kalau L > R pecah jadi dua bagian, atau pakai array digandakan.

    return 0;
}
