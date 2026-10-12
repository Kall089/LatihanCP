/*
============================================================
📋 TUGAS 05: Memotong Batang Bambu (Rod Cutting Problem)
============================================================
Source: CLRS Classic / DP Foundation
Difficulty: Easy
Topics: Unbounded Knapsack Maksimum Nilai

PROBLEM:
Diberikan sebatang bambu dengan panjang total L meter.
Toko kayu menetapkan daftar harga potongan: sepotong bambu berukuran i meter
(1 <= i <= L) bernilai p[i] rupiah.
Kamu boleh memotong bambu tersebut menjadi beberapa bagian dengan panjang
bilangan bulat positif sehingga total panjang potongan sama dengan L meter.
Tentukan total nilai pendapatan maksimum yang bisa kamu dapatkan.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat L.
Baris kedua berisi L bilangan bulat p[1], p[2], ..., p[L].

OUTPUT FORMAT:
Satu bilangan bulat: nilai maksimum yang bisa didapat.

CONSTRAINTS:
1 <= L <= 1.000
1 <= p[i] <= 1.000.000

SAMPLE INPUT 1:
4
1 5 8 9

SAMPLE OUTPUT 1:
10
(Penjelasan: Potong bambu menjadi 2 bagian masing-masing berukuran 2 meter: nilai = 5 + 5 = 10)

SAMPLE INPUT 2:
5
2 5 7 8 10

SAMPLE OUTPUT 2:
12
(Penjelasan: Potong menjadi ukuran 2 + 2 + 1: nilai = 5 + 5 + 2 = 12)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L;
    if (!(cin >> L)) return 0;

    vector<ll> p(L + 1);
    for (int i = 1; i <= L; i++) {
        cin >> p[i];
    }

    // TODO: Selesaikan Rod Cutting dengan Unbounded Knapsack
    // dp[len] = nilai maksimal dari bambu sepanjang len
    // dp[0] = 0
    // Transisi: dp[len] = max_{i=1..len} (dp[len - i] + p[i])

    return 0;
}
