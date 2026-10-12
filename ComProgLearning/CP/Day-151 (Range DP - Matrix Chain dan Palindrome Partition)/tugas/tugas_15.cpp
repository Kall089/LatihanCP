/*
============================================================
📋 TUGAS 15: Penggabungan Melingkar Tumpukan Batu (Circular Stone Merging)
============================================================
Source: Classic Circular DP / POJ 1179 Variation
Difficulty: Hard
Topics: Circular Range DP, Array Duplication

PROBLEM:
Terdapat N tumpukan batu yang diletakkan MELINGKAR dalam sebuah lingkaran.
Tumpukan ke-i memiliki bobot a[i].
Karena posisinya melingkar, tumpukan terakhir a[N-1] bersebelahan dengan tumpukan pertama a[0].
Dalam satu operasi, kamu boleh menggabungkan dua tumpukan batu yang BERSEBELAHAN dalam lingkaran.
Biaya penggabungan adalah jumlah bobot kedua tumpukan yang digabung.
Tentukan biaya total MINIMUM untuk menggabungkan seluruh batu menjadi satu tumpukan tunggal.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

OUTPUT FORMAT:
Satu bilangan bulat: biaya total minimum.

CONSTRAINTS:
1 <= N <= 100
0 <= a[i] <= 10^9

SAMPLE INPUT 1:
3
10 20 30

SAMPLE OUTPUT 1:
90
(Penjelasan: Untuk N = 3, lingkaran memiliki konfigurasi yang sama, biaya 90)

SAMPLE INPUT 2:
4
4 5 9 4

SAMPLE OUTPUT 2:
43
(Penjelasan:
Jika dibuka melingkar, biaya minimum menggabungkan 4 elemen melingkar adalah 43)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    // Gandakan array menjadi 2*N untuk memodelkan struktur melingkar
    vector<ll> b(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        b[i] = a[i % n];
    }

    vector<ll> pref(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        pref[i + 1] = pref[i] + b[i];
    }

    // TODO: Selesaikan Circular Stone Merging
    // 1. Range DP pada array b berukuran 2*N untuk len sampai N
    // 2. Jawaban = min_{0 <= i < n} dp[i][i + n - 1]

    return 0;
}
