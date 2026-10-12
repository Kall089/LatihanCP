/*
============================================================
📋 TUGAS 13: Skor Game Arkade
============================================================
Source: Competitive Programming Classic
Difficulty: Hard
Topics: Unbounded Knapsack Optimization

PROBLEM:
Dalam sebuah game arkade, seorang pemain dapat memilih N aksi berbeda
yang dapat dijalankan berulang kali.
Aksi ke-i membutuhkan stamina sebesar s[i] dan menghasilkan p[i] skor.
Pemain memiliki total stamina sebesar S.
Tentukan skor total maksimum yang dapat diraih pemain tanpa melampaui total stamina S.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan S.
N baris berikutnya, masing-masing berisi dua bilangan bulat s[i] dan p[i].

OUTPUT FORMAT:
Satu bilangan bulat: skor total maksimum.

CONSTRAINTS:
1 <= N <= 1.000
1 <= S <= 100.000
1 <= s[i] <= S
1 <= p[i] <= 10^9

SAMPLE INPUT 1:
3 10
3 7
4 10
2 4

SAMPLE OUTPUT 1:
24
(Penjelasan: Ambil aksi 2 dua kali (stamina 4+4=8, skor 20) + aksi 3 satu kali (stamina 2, skor 4) = stamina 10, total skor 24)

SAMPLE INPUT 2:
1 5
6 100

SAMPLE OUTPUT 2:
0
(Penjelasan: Aksi membutuhkan 6 stamina > 5 stamina yang tersedia, tidak bisa dijalankan)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    if (!(cin >> n >> s)) return 0;

    vector<int> stamina(n);
    vector<ll> poin(n);
    for (int i = 0; i < n; i++) {
        cin >> stamina[i] >> poin[i];
    }

    // TODO: Selesaikan dengan Unbounded Knapsack standar
    // vector<ll> dp(s + 1, 0)
    // Loop aksi, loop kapasitas maju dari stamina[i] sampai s

    return 0;
}
