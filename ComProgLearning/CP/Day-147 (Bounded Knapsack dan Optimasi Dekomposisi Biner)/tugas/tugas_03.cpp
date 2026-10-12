/*
============================================================
📋 TUGAS 03: Jangkauan Total Skor Ujian
============================================================
Source: Educational / Subset Sum
Difficulty: Medium
Topics: Bounded Reachability, Boolean DP

PROBLEM:
Dalam sebuah sistem penilaian ujian, terdapat N jenis tipe soal.
Soal tipe ke-i bernilai w[i] poin dan terdapat paling banyak c[i] butir soal jenis tersebut.
Seorang siswa dapat menjawab dengan benar sembarang subset dari butir-butir soal yang ada.
Tentukan berapa banyak total poin UNIK dalam rentang 1 sampai S (inklusif)
yang mungkin diperoleh siswa tersebut. Skor 0 tidak dihitung.

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan S.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

OUTPUT FORMAT:
Satu bilangan bulat: banyaknya kemungkinan total skor unik dalam [1, S].

CONSTRAINTS:
1 <= N <= 80
1 <= S <= 30.000
1 <= w[i] <= S
1 <= c[i] <= 500

SAMPLE INPUT 1:
2 12
3 3
4 2

SAMPLE OUTPUT 1:
8
(Penjelasan: Skor yang mungkin dalam [1, 12] adalah: 3, 4, 6, 7, 8, 9, 10, 11, 12. Total ada 8 skor unik)

SAMPLE INPUT 2:
1 10
2 4

SAMPLE OUTPUT 2:
4
(Penjelasan: Skor yang mungkin: 2, 4, 6, 8. Total 4 skor unik)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    if (!(cin >> n >> s)) return 0;

    vector<int> w(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Reachability dengan Boolean DP
    // vector<bool> can(s + 1, false); can[0] = true;
    // Pecah c[i] biner, update can[j] |= can[j - q * w[i]] secara mundur

    return 0;
}
