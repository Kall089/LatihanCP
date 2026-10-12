/*
============================================================
📋 TUGAS 06: Rekonstruksi Operasi Edit Distance
============================================================
Source: LeetCode 72 / Classic Levenshtein Distance
Difficulty: Hard
Topics: 2D DP Backtracking, Edit Distance Operations

PROBLEM:
Diberikan dua string A dan B. Kamu ingin mengubah string A menjadi string B
menggunakan sesedikit mungkin operasi dasar:
- KEEP: karakter cocok, tidak ada biaya.
- REPLACE c: mengganti karakter pada A dengan karakter c.
- INSERT c: menyisipkan karakter c ke dalam A.
- DELETE: menghapus karakter pada A.

Cetak jumlah operasi minimum di baris pertama.
Di baris-baris berikutnya, cetak urutan operasi yang dilakukan dari awal string hingga akhir.

INPUT FORMAT:
Baris pertama berisi string A.
Baris kedua berisi string B.

OUTPUT FORMAT:
Baris pertama: satu bilangan bulat, jarak Levenshtein minimum.
Baris berikutnya: daftar operasi yang dilakukan (satu per baris).

CONSTRAINTS:
1 <= |A|, |B| <= 500

SAMPLE INPUT 1:
cat
cut

SAMPLE OUTPUT 1:
1
KEEP c
REPLACE u
KEEP t
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    // TODO: Selesaikan Edit Distance dan rekonstruksi operasi mundur

    return 0;
}
