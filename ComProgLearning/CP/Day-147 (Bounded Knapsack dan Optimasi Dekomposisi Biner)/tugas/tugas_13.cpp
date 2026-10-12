/*
============================================================
📋 TUGAS 13: Alokasi Waktu Server Komputasi
============================================================
Source: Classic Job Scheduling DP
Difficulty: Hard
Topics: Bounded Knapsack Optimization, Time Window

PROBLEM:
Sebuah kluster server memiliki kuota waktu komputasi tersisa T detik.
Terdapat N jenis batch tugas komputasi.
Satu batch tugas jenis ke-i memerlukan waktu eksekusi w[i] detik,
memberikan nilai performa v[i] poin, dan antrean tugas jenis tersebut hanya
tersedia sebanyak c[i] batch.
Tentukan total performa maksimum yang dapat diselesaikan oleh kluster server
tanpa melebihi batas total waktu T detik.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan T.
N baris berikutnya, masing-masing berisi tiga bilangan bulat w[i], v[i], dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: performa total maksimum.

CONSTRAINTS:
1 <= N <= 200
1 <= T <= 40.000
1 <= w[i] <= T
1 <= v[i] <= 10^9
1 <= c[i] <= 2.000

SAMPLE INPUT 1:
3 25
5 15 3
8 22 2
4 11 4

SAMPLE OUTPUT 1:
72
(Penjelasan: Ambil 2 tugas jenis 0 (waktu 10, poin 30) + 1 tugas jenis 1 (waktu 8, poin 22) + 1 tugas jenis 2 (waktu 4, poin 11) = waktu 22, poin 63.
Atau 3 tugas jenis 0 (waktu 15, poin 45) + 2 tugas jenis 2 (waktu 8, poin 22) = waktu 23, poin 67.
Atau 1 tugas 0 (5, 15) + 2 tugas 1 (16, 44) + 1 tugas 2 (4, 11) = waktu 25, poin 70.
Kombinasi terbaik: 2 tugas 1 (waktu 16, poin 44) + 2 tugas 2 (waktu 8, poin 22) = waktu 24, poin 66.
Mari periksa: 1 tugas 0 (5, 15) + 1 tugas 1 (8, 22) + 3 tugas 2 (12, 33) = waktu 25, poin 15 + 22 + 33 = 70.
Bagaimana dengan: 2 tugas 0 (10, 30) + 1 tugas 1 (8, 22) = waktu 18. Sisa waktu 7, ambil 1 tugas 2 (4, 11) = waktu 22, poin 63.
Jika 5 tugas jenis 0 dan 2:
Tugas 0 (5, 15, rasio 3.0), Tugas 1 (8, 22, rasio 2.75), Tugas 2 (4, 11, rasio 2.75).
Ambil 3 tugas 0 (15 detik, 45 poin). Sisa waktu 10 detik. Ambil 2 tugas 2 (8 detik, 22 poin) = 23 detik, 67 poin.
Atau ambil 1 tugas 1 (8 detik, 22 poin) = 23 detik, 67 poin.
Jika ambil 2 tugas 0 (10 detik, 30 poin) + 1 tugas 1 (8 detik, 22 poin) + 1 tugas 2 (4 detik, 11 poin) = 22 detik, 63 poin.
Jika ambil 1 tugas 0 (5 detik, 15 poin) + 2 tugas 1 (16 detik, 44 poin) + 1 tugas 2 (4 detik, 11 poin) = waktu tepat 25 detik, total poin 70!)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    vector<int> w(n);
    vector<ll> v(n);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Knapsack dengan Dekomposisi Biner
    // vector<ll> dp(t + 1, 0)
    // Gunakan hybrid shortcut jika c[i] * w[i] >= t

    return 0;
}
