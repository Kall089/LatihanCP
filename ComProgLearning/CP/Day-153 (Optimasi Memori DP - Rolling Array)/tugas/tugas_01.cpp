/*
============================================================
📋 TUGAS 01: Festival Tanpa Stan Bertetangga (House Robber O(1) Memory)
============================================================
Source: Classic DP / House Robber Variation
Difficulty: Medium
Topics: 1D DP, State Compression, O(1) Memory

PROBLEM:
Diberikan sebuah deretan N stan di festival. Stan ke-i menghasilkan keuntungan nilai[i].
Kamu boleh memilih beberapa stan untuk dikunjungi, asalkan TIDAK ADA DUA STAN YANG BERSEBELAHAN
yang sama-sama dipilih.
Nilai keuntungan stan bisa bernilai negatif, dan kamu diperbolehkan memilih untuk tidak mengunjungi
stan mana pun (keuntungan 0).
Tentukan keuntungan maksimum yang dapat diperoleh.
Program HARUS memproses input dalam memori tambahan O(1) (dilarang menyimpan array).

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat nilai[0], ..., nilai[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: keuntungan maksimum.

CONSTRAINTS:
1 <= N <= 200.000
-10^9 <= nilai[i] <= 10^9
Memori tambahan O(1)

SAMPLE INPUT 1:
4
2 7 9 3

SAMPLE OUTPUT 1:
11
(Pilih stan 1 [2] dan stan 3 [9]: 2 + 9 = 11)

SAMPLE INPUT 2:
3
-1 -2 -3

SAMPLE OUTPUT 2:
0
(Tidak memilih stan mana pun memberikan nilai 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan 2 variabel sliding window O(1) memory

    return 0;
}
