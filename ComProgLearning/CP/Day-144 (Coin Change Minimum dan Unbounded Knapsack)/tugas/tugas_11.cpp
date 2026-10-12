/*
============================================================
📋 TUGAS 11: Rekonstruksi Koin Leksikografis Terkecil
============================================================
Source: Competitive Programming Variation
Difficulty: Hard
Topics: Coin Change Minimum + Lexicographical Tie-breaking

PROBLEM:
Diberikan N jenis koin berbeda c[0], ..., c[N-1] dan sebuah nominal target X.
Setiap jenis koin tersedia dalam jumlah tak terbatas.
Cari susunan koin pembentuk X yang memenuhi:
1. Memiliki jumlah koin MINIMUM.
2. Jika ada beberapa kombinasi dengan jumlah koin minimum yang sama,
   pilih kombinasi yang jika diurutkan secara menaik (c_1 <= c_2 <= ... <= c_k),
   menghasilkan barisan yang SECARA LEKSIKOGRAFIS PALING KECIL
   (artinya koin dengan nilai terkecil dipilih sebanyak mungkin di awal).

Keluarkan koin-koin tersebut dalam urutan menaik dipisahkan spasi.
Jika nominal X mustahil dibentuk, cetak -1.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat c[0], ..., c[N-1].

OUTPUT FORMAT:
Satu baris: daftar koin yang diurutkan menaik dipisahkan spasi, atau -1 jika mustahil.

CONSTRAINTS:
1 <= N <= 50
1 <= X <= 10.000
1 <= c[i] <= 10.000

SAMPLE INPUT 1:
3 6
1 3 4

SAMPLE OUTPUT 1:
3 3
(Penjelasan: Koin minimum = 2 keping. Pilihan yang mungkin: {3, 3} (1 koin tidak ada 2 keping yang menghasilkan 6). Output: 3 3)

SAMPLE INPUT 2:
3 8
1 3 4

SAMPLE OUTPUT 2:
4 4
(Penjelasan: Koin minimum = 2 keping (4 + 4). Output: 4 4)

SAMPLE INPUT 3:
2 5
2 4

SAMPLE OUTPUT 3:
-1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // TODO: Selesaikan dengan DP Coin Change Min + Rekonstruksi Leksikografis
    // 1. Hitung dp[i] = koin minimum untuk nominal i
    // 2. Jika dp[x] == INF cetak -1
    // 3. Rekonstruksi: dari target x, pilih koin terkecil c_k sedemikian sehingga
    //    dp[x - c_k] == dp[x] - 1, lalu lanjutkan secara greedy pada x - c_k.
    // 4. Urutkan koin yang diperoleh dan cetak.

    return 0;
}
