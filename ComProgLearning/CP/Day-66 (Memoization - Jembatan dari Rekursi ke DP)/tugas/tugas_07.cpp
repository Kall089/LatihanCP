/*
============================================================
📋 TUGAS 07: Jarak Edit Levenshtein Top-Down
============================================================
Source: Classic String DP / Top-Down Memoization
Difficulty: Medium
Topics: 2D Top-Down Memoization, Strings

PROBLEM:
Diberikan dua string teks S dan T.
Kamu diperbolehkan melakukan tiga jenis operasi pengeditan:
1. Menyisipkan satu karakter.
2. Menghapus satu karakter.
3. Mengganti satu karakter dengan karakter lain.

Hitung JUMLAH OPERASI MINIMUM untuk mengubah string S menjadi string T!

Wajib diimplementasikan menggunakan REKURSIF DENGAN MEMOISASI (Top-Down)!

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi string T.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jarak edit minimum.

CONSTRAINTS:
0 <= |S|, |T| <= 1.000
Karakter hanya huruf kecil 'a'..'z'

SAMPLE INPUT 1:
horse
ros

SAMPLE OUTPUT 1:
3
(horse -> rorse [ganti 'h'->'r'] -> rose [hapus 'r'] -> ros [hapus 'e'])

SAMPLE INPUT 2:
intention
execution

SAMPLE OUTPUT 2:
5
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // TODO: Selesaikan dengan 2D top-down memoization

    return 0;
}
