/*
============================================================
📋 TUGAS 14: BFS — Transformasi Kata (Word Ladder)
============================================================
Source: LeetCode 127 Word Ladder (simplified, inspired)
Difficulty: Medium-Hard
Topics: BFS pada implicit graph, string manipulation

PROBLEM:
Diberikan kata awal beginWord, kata tujuan endWord, dan
daftar kata yang valid (wordList).
Setiap langkah: ubah tepat SATU huruf dari kata saat ini
menjadi kata valid lain dalam wordList.

Temukan jumlah langkah minimum dari beginWord ke endWord.
Jika tidak bisa, cetak 0.

Catatan: beginWord tidak harus ada di wordList.

INPUT FORMAT:
- Baris 1: string beginWord
- Baris 2: string endWord
- Baris 3: integer k (jumlah kata di wordList)
- k baris berikutnya: string (kata di wordList)

OUTPUT FORMAT:
- Satu integer: jumlah langkah minimum (termasuk beginWord
  dan endWord), atau 0 jika tidak ada jalur

CONSTRAINTS:
- 1 ≤ panjang kata ≤ 5
- 1 ≤ k ≤ 500
- Semua kata huruf kecil, panjang sama

SAMPLE INPUT 1:
hit
cog
6
hot
dot
dog
lot
log
cog

SAMPLE OUTPUT 1:
5

(hit → hot → dot → dog → cog, 5 kata = 4 langkah + 1 = 5)

SAMPLE INPUT 2:
hit
cog
5
hot
dot
dog
lot
log

SAMPLE OUTPUT 2:
0

NOTE: Ini BFS pada "implicit graph" di mana node = kata,
      edge = beda satu huruf.
      Untuk tiap kata, coba ganti tiap posisi dengan 'a'-'z'.
      Cek apakah hasilnya ada di wordList (gunakan unordered_set).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
