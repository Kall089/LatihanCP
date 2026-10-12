/*
============================================================
📋 TUGAS 04: Rekonstruksi Knapsack 0/1 Barang Terpilih
============================================================
Source: Classic 0/1 Knapsack / Table Backtracking
Difficulty: Medium
Topics: 2D Knapsack, Table Backtracking, Item Reconstruction

PROBLEM:
Diberikan N barang dengan bobot w[i] dan nilai v[i], serta kapasitas tas W.
Setiap barang boleh diambil paling banyak sekali.
Tentukan:
1. Di baris pertama: total nilai maksimum yang dapat dibawa.
2. Di baris kedua: banyak barang yang dipilih (K).
3. Di baris ketiga: daftar nomor indeks barang yang dipilih (1-indexed) terurut menaik.
Jika nilai maksimum adalah 0, baris kedua cetak 0 dan baris ketiga cetak baris kosong.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan W.
N baris berikutnya masing-masing berisi dua bilangan bulat w[i] dan v[i].

OUTPUT FORMAT:
Baris pertama: nilai maksimum.
Baris kedua: jumlah barang terpilih K.
Baris ketiga: K bilangan bulat menyatakan indeks barang terpilih terurut menaik.

CONSTRAINTS:
1 <= N <= 1.000
1 <= W <= 10.000
1 <= w[i] <= W
0 <= v[i] <= 10^9

SAMPLE INPUT 1:
3 5
2 3
3 4
4 5

SAMPLE OUTPUT 1:
7
2
1 2
(Penjelasan: Barang 1 (berat 2, nilai 3) dan Barang 2 (berat 3, nilai 4).
Total berat = 5 <= 5, total nilai = 7. K = 2, barang: 1 2)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<ll> w(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    // TODO: Selesaikan Knapsack 0/1 2D dan rekonstruksi tabel mundur

    return 0;
}
