/*
============================================================
📋 TUGAS 03: Kincir Ria
============================================================
Source: CSES 1090
Difficulty: Easy
Topics: ❓ DIRAHASIAKAN — tebak dulu, kunci ada di solusi/KUNCI_TOPIK.md

PROBLEM:
Ada N anak yang ingin naik kincir ria. Setiap gondola muat paling banyak DUA
anak, dan total berat keduanya tidak boleh melebihi X.

Cari jumlah gondola minimum yang dibutuhkan supaya semua anak terangkut.

INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan, berat tiap anak

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 1 <= X <= 10^9
- 1 <= berat <= X

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
4 10
7 2 3 9
output:
3

SAMPLE 2 - pas berdua
input:
2 10
5 5
output:
1

SAMPLE 3 - tidak ada yang bisa berbagi
input:
3 9
9 9 9
output:
3
penjelasan: setiap anak butuh gondolanya sendiri.

SAMPLE 4 - semua bisa berpasangan
input:
4 2
1 1 1 1
output:
2

------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- urutkan, lalu pasangkan yang TERINGAN dengan yang TERBERAT
- kalau tidak muat, yang terberat naik sendiri
- buktikan sendiri kenapa greedy ini optimal sebelum submit
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
