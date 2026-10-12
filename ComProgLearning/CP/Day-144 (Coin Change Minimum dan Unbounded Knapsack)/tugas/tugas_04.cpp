/*
============================================================
📋 TUGAS 04: Pembagian Kemasan Jeruk Grosir
============================================================
Source: Competitive Programming Classic
Difficulty: Easy
Topics: Unbounded Subset Sum / Reachability

PROBLEM:
Toko buah menjual jeruk dalam N ukuran kemasan berbeda a[0], ..., a[N-1].
Setiap ukuran kemasan dapat dibeli berkali-kali tanpa batas.
Seorang pembeli ingin membeli jeruk sebanyak mungkin hingga mendekati X buah,
tetapi TIDAK BOLEH melebihi X buah.
Tentukan selisih terkecil antara X dan total jeruk yang berhasil dibeli (X - total_jeruk).

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan X.
Baris kedua berisi N bilangan bulat a[0], ..., a[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: selisih minimum (X - total_terdekat).

CONSTRAINTS:
1 <= N <= 100
1 <= X <= 10.000
1 <= a[i] <= 10.000

SAMPLE INPUT 1:
2 11
3 5

SAMPLE OUTPUT 1:
0
(Penjelasan: Pembeli bisa membeli dua kemasan 3 dan satu kemasan 5 = 6 + 5 = 11 jeruk. Selisih = 11 - 11 = 0)

SAMPLE INPUT 2:
2 7
4 6

SAMPLE OUTPUT 2:
1
(Penjelasan: Jumlah jeruk <= 7 yang bisa dibeli adalah 0, 4, atau 6. Paling mendekati adalah 6. Selisih = 7 - 6 = 1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // TODO: Gunakan DP Boolean Unbounded Knapsack
    // can[w] = true jika total w bisa dibentuk.
    // can[0] = true.
    // Loop kemasan, loop kapasitas maju w dari a[i] ke x: can[w] |= can[w - a[i]].
    // Cari w terbesar <= x yang can[w] bernilai true.

    return 0;
}
