/*
============================================================
📋 TUGAS 13: Titik Terjauh dari Poligon
============================================================
Source: Original
Difficulty: Hard
Topics: binary search + geometri

PROBLEM:
Diberikan poligon cembung dengan N titik sudut, cari lingkaran TERBESAR
yang seluruhnya berada di dalam poligon. Cetak jari-jarinya dengan 6
desimal.

INPUT FORMAT:
- Baris pertama: N
- N baris berisi koordinat x dan y (berlawanan arah jarum jam)

OUTPUT FORMAT:
- Satu bilangan, 6 desimal

CONSTRAINTS:
- 3 <= N <= 100

SAMPLE INPUT 1:
4
0 0
10 0
10 10
0 10

SAMPLE OUTPUT 1:
5.000000
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Predikatnya: 'adakah titik yang jaraknya >= r dari SEMUA sisi?' Geser setiap sisi ke dalam sejauh r lalu cek apakah irisannya masih tidak kosong.

    return 0;
}
