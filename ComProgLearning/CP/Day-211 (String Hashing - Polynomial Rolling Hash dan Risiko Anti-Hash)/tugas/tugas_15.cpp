/*
============================================================
📋 TUGAS 15: Hash Ganda Anti-Tabrakan
============================================================
Source: Original
Difficulty: Hard
Topics: Double hashing

PROBLEM:
Diberikan N string. Hitung ada berapa string BERBEDA di antaranya.
Jumlah string bisa mencapai 10^5, sehingga hash tunggal berisiko tabrakan
karena paradoks ulang tahun.

Kerjakan dengan DOUBLE HASHING dan bandingkan hasilnya dengan hash tunggal
untuk melihat sendiri kapan tabrakan mulai berbahaya.

INPUT FORMAT:
- Baris pertama: bilangan N
- N baris berikutnya: satu string per baris

OUTPUT FORMAT:
- Satu bilangan: banyaknya string berbeda.

CONSTRAINTS:
- 1 <= N <= 10^5
- Total panjang seluruh string <= 10^6

SAMPLE INPUT 1:
5
abc
abc
ab
c
abc

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
#include <unordered_set>   // sebagian bits/stdc++.h tidak memuatnya
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ingat: long long, petakan huruf ke 1..26, dan +M sebelum modulo

    return 0;
}
