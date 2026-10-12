/*
============================================================
📋 TUGAS 03: LIS dengan Indeks Terkecil
============================================================
Source: Classic DP / LIS Lexicographical Indices
Difficulty: Medium
Topics: 1D DP, Suffix DP for Indices, Lexicographical Reconstruction

PROBLEM:
Diberikan sebuah array A berukuran N.
Tentukan Subsekuens Naik Ketat Terpanjang (LIS) dari array A.
Cetak panjang LIS pada baris pertama.
Pada baris kedua, cetak daftar nomor indeks (1-indexed) dari elemen-elemen yang terpilih
dalam LIS tersebut.
Jika ada beberapa LIS dengan panjang maksimum yang sama, pilih daftar indeks yang
TERKECIL SECARA LEKSIKOGRAFIS.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat A[0], A[1], ..., A[N-1].

OUTPUT FORMAT:
Baris pertama: panjang LIS.
Baris kedua: daftar indeks 1-based elemen terpilih dipisahkan spasi.

CONSTRAINTS:
1 <= N <= 500
-10^9 <= A[i] <= 10^9

SAMPLE INPUT 1:
4
2 1 3 4

SAMPLE OUTPUT 1:
3
1 3 4
(Penjelasan: Dua LIS berpanjang 3 adalah [2, 3, 4] dengan indeks [1, 3, 4]
dan [1, 3, 4] dengan indeks [2, 3, 4].
Pada posisi pertama, indeks 1 < 2, sehingga [1, 3, 4] menang)

SAMPLE INPUT 2:
3
7 7 7

SAMPLE OUTPUT 2:
1
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Selesaikan LIS dengan Indeks Leksikografis Terkecil
    // Suffix DP: dp[i] = panjang LIS terpanjang yang DIMULAI dari elemen i
    // Rekonstruksi maju dari indeks 0 s.d. n-1

    return 0;
}
