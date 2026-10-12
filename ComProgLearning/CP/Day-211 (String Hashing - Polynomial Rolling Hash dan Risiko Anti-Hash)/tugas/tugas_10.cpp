/*
============================================================
📋 TUGAS 10: Anagram Bergerak
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: Rolling frequency (bukan hash polinomial)

PROBLEM:
Diberikan teks T dan pola P. Hitung ada berapa posisi di T yang potongannya
sepanjang |P| merupakan ANAGRAM dari P (huruf sama, urutan boleh beda).

Petunjuk: soal ini justru lebih cocok memakai tabel frekuensi bergeser
daripada hash polinomial. Gunakan kesempatan ini untuk membandingkan
kapan hashing tepat dipakai dan kapan tidak.

INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

OUTPUT FORMAT:
- Satu bilangan: banyaknya posisi yang merupakan anagram P.

CONSTRAINTS:
- 1 <= |P| <= |T| <= 2 x 10^5

SAMPLE INPUT 1:
cbaebabacd
abc

SAMPLE OUTPUT 1:
2
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
