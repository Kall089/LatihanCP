/*
============================================================
📋 TUGAS 11: Denda Bertumbuh
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Fungsi penalti tidak biner

PROBLEM:
Ada n tugas pada satu mesin. Tugas ke-i butuh t[i] waktu dan bertenggat d[i].
Kalau tugas ke-i selesai pada waktu C, dendanya adalah w[i] dikali maksimum dari nol
dan C dikurangi d[i] (jadi denda BERTUMBUH sebanding keterlambatan, bukan biner).
Cari total denda minimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i], d[i], w[i]

OUTPUT FORMAT:
Satu bilangan: total denda minimum

CONSTRAINTS:
1 <= n <= 12, 1 <= t[i] <= 100, 1 <= d[i] <= 1000, 1 <= w[i] <= 100

SAMPLE INPUT 1:
2
3 3 5
3 4 10

SAMPLE OUTPUT 1:
15
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perhatikan bahwa dendanya BUKAN biner lagi. Semua teknik hari ini mengasumsikan denda biner (tepat waktu atau tidak). Batasan n <= 12 memberitahumu pendekatan mana yang dimaksud.

    return 0;
}
