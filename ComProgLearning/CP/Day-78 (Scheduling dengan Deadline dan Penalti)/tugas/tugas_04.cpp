/*
============================================================
📋 TUGAS 04: Denda Berbobot dengan Durasi Bervariasi
============================================================
Source: 1 || sum wj Uj (NP-hard umum)
Difficulty: Hard
Topics: DP di atas waktu

PROBLEM:
Ada n tugas pada satu mesin. Tugas ke-i butuh t[i] waktu, bertenggat d[i], dan
berdenda w[i] kalau terlambat. Semua tugas harus dikerjakan.
Cari total denda minimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i], d[i], w[i]

OUTPUT FORMAT:
Satu bilangan: total denda minimum

CONSTRAINTS:
1 <= n <= 2000, 1 <= t[i] <= 100, 1 <= d[i] <= 2*10^5, 1 <= w[i] <= 10^9

SAMPLE INPUT 1:
3
3 3 5
3 4 10
3 5 1

SAMPLE OUTPUT 1:
6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Uji dulu kedua greedy (buang durasi terbesar, buang denda terkecil) dengan brute force — keduanya gagal. Lalu susun DP; tenggat harus menjadi BATAS ATAS loop, bukan pemeriksaan terpisah.

    return 0;
}
