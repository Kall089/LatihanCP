/*
============================================================
📋 TUGAS 03: Partisi Wajib pada Gerbang
============================================================
Source: Classic D&C DP Variation
Difficulty: Medium
Topics: Divide and Conquer DP Optimization, Constrained Split

PROBLEM:
Diberikan array N bilangan bulat a[0], ..., a[N-1].
Bagi array menjadi TEPAT K segmen tak kosong dengan biaya setiap segmen adalah kuadrat jumlah bobotnya.
Namun, terdapat satu aturan khusus:
BATAS SETELAH ELEMEN KE-B (indeks 1-based B) WAJIB MENJADI SALAH SATU TITIK PEMISAH SEGMEN!
(Artinya, suatu segmen harus berakhir tepat pada elemen ke-B, dan segmen berikutnya dimulai dari elemen ke-(B+1)).

Tentukan TOTAL BIAYA MINIMUM untuk mempartisi array dengan syarat tersebut!

INPUT FORMAT:
Baris pertama berisi tiga bilangan bulat N, K, dan B.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: total biaya minimum.

CONSTRAINTS:
2 <= N <= 10.000
2 <= K <= min(N, 20)
1 <= B < N
0 <= a[i] <= 1.000

SAMPLE INPUT 1:
4 2 2
1 2 3 4

SAMPLE OUTPUT 1:
58
(Wajib dipotong di B=2: [1, 2] -> sum 3, cost 9; [3, 4] -> sum 7, cost 49. Total = 9 + 49 = 58)

SAMPLE INPUT 2:
3 3 1
2 0 1

SAMPLE OUTPUT 2:
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, b;
    if (!(cin >> n >> k >> b)) return 0;

    // TODO: Selesaikan dengan memadukan D&C DP pada bagian kiri (1..B) dan kanan (B+1..N)

    return 0;
}
