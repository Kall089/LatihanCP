/*
============================================================
📋 TUGAS 03: Job Sequencing dengan Denda
============================================================
Source: Klasik
Difficulty: Medium
Topics: Regret berbobot seragam

PROBLEM:
Ada n tugas, masing-masing butuh tepat 1 satuan waktu. Tugas ke-i bertenggat d[i] dan
berdenda w[i] kalau selesai setelah tenggatnya. Semua tugas harus dikerjakan.
Cari total denda minimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: d[i] dan w[i]

OUTPUT FORMAT:
Satu bilangan: total denda minimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= d[i] <= n, 1 <= w[i] <= 10^9

SAMPLE INPUT 1:
4
1 10
1 40
1 30
4 20

SAMPLE OUTPUT 1:
40
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Durasi seragam menyelamatkan greedy di sini. Arah heap BERLAWANAN dengan Tugas 02 — pikirkan kenapa. Hitung komplemennya: total denda dikurangi denda yang bisa dihindari.

    return 0;
}
