/*
============================================================
📋 TUGAS 11: Jendela Terkecil yang Memuat Semua
============================================================
Source: LeetCode 76
Difficulty: Hard
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Diberikan string S dan string T. Cari SUBSTRING terpendek dari S yang memuat
seluruh karakter T beserta jumlah kemunculannya (T boleh punya karakter
berulang). Kalau tidak ada, cetak tanda minus.

Kalau ada beberapa yang sama pendek, cetak yang paling kiri.

INPUT FORMAT:
- Baris pertama: string S
- Baris kedua: string T

OUTPUT FORMAT:
- Satu string, atau - kalau tidak ada

CONSTRAINTS:
- 1 <= |S| <= 2*10^5
- 1 <= |T| <= 100
- keduanya huruf besar dan kecil

------------------------------------------------------------
SAMPLE 1 - kasus klasik
input:
ADOBECODEBANC
ABC
output:
BANC

SAMPLE 2 - sama persis
input:
a
a
output:
a

SAMPLE 3 - tidak cukup
input:
a
aa
output:
-
penjelasan: T butuh dua huruf a, S hanya punya satu.

SAMPLE 4 - karakter berulang
input:
aab
ab
output:
ab
penjelasan: jawabannya posisi 2..3, bukan 1..3.

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- pantau BERAPA BANYAK jenis karakter yang sudah terpenuhi, jangan bandingkan
  seluruh map tiap langkah (itu mengalikan kompleksitas dengan 52)
- window mengecil hanya SETELAH valid
- perhatikan jumlah kemunculan, bukan sekadar keberadaan
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TEBAKAN TEKNIK SAYA: ______________________
    // SINYAL DI SOAL     : ______________________

    // TODO: Kerjakan di sini

    return 0;
}
