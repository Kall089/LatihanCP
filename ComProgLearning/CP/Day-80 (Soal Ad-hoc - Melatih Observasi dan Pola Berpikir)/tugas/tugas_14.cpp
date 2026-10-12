/*
============================================================
📋 TUGAS 14: Ad-hoc dengan Batasan Raksasa
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Rumus tertutup

PROBLEM:
Diberikan n sampai 10^18, hitung jumlah seluruh bilangan dari 1 sampai n yang habis
dibagi 3 atau 5, modulo 10^9+7.

INPUT FORMAT:
Baris 1: n

OUTPUT FORMAT:
Satu bilangan modulo 10^9+7

CONSTRAINTS:
1 <= n <= 10^18

SAMPLE INPUT 1:
10

SAMPLE OUTPUT 1:
33
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Batasan 10^18 menuntut rumus tertutup. Pakai inklusi-eksklusi: kelipatan 3, ditambah kelipatan 5, dikurangi kelipatan 15. Untuk masing-masing, jumlah deret aritmetika punya rumus. Hati-hati dengan pembagian 2 dalam aritmetika modular.

    return 0;
}
