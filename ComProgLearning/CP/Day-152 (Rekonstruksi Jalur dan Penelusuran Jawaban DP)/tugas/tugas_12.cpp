/*
============================================================
📋 TUGAS 12: Rekonstruksi Partisi Subset Sama Bobot
============================================================
Source: LeetCode 416 (Partition Equal Subset Sum)
Difficulty: Medium
Topics: Subset Sum DP, 0/1 Knapsack Reconstruction

PROBLEM:
Diberikan N buah bilangan bulat positif a[0], ..., a[N-1].
Tentukan apakah array tersebut dapat dibagi menjadi DUA SUBSET yang memiliki JUMLAH SAMA PERSIS.
Jika mungkin:
Cetak "BISA" di baris pertama.
Di baris kedua, cetak banyak elemen pada salah satu subset (K).
Di baris ketiga, cetak nomor indeks (1-indexed) dari elemen-elemen yang masuk ke dalam subset tersebut.
Jika tidak mungkin, cetak "TIDAK BISA" saja.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
Baris kedua berisi N bilangan bulat positif a[0], ..., a[N-1].

OUTPUT FORMAT:
"BISA" diikuti jumlah elemen dan indeks 1-based, atau "TIDAK BISA".

CONSTRAINTS:
1 <= N <= 200
1 <= a[i] <= 100
Total jumlah elemen <= 20.000

SAMPLE INPUT 1:
4
1 5 11 5

SAMPLE OUTPUT 1:
BISA
3
1 2 4
(Penjelasan: Total = 22, target = 11. Subset {1, 5, 5} berindeks 1, 2, 4 berjumlah 11)

SAMPLE INPUT 2:
3
1 2 5

SAMPLE OUTPUT 2:
TIDAK BISA
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
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    // TODO: Selesaikan Subset Sum Partition dan rekonstruksi elemen subset

    return 0;
}
