/*
============================================================
📋 TUGAS 01: Minimalkan Keterlambatan Maksimum
============================================================
Source: Klasik (1 || Lmax)
Difficulty: Easy
Topics: EDF

PROBLEM:
Ada n pekerjaan pada satu mesin, semuanya harus dikerjakan mulai waktu 0. Pekerjaan
ke-i butuh t[i] waktu dan bertenggat d[i]. Keterlambatan sebuah pekerjaan adalah
waktu selesainya dikurangi tenggatnya (boleh negatif).
Minimalkan keterlambatan TERBESAR.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: t[i] dan d[i]

OUTPUT FORMAT:
Satu bilangan (boleh negatif)

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= t[i] <= 10^9, 1 <= d[i] <= 10^18

SAMPLE INPUT 1:
3
3 6
2 8
1 9

SAMPLE OUTPUT 1:
-3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urut tenggat menaik. Durasi tidak muncul dalam kriteria — buktikan sendiri kenapa. Jangan inisialisasi maksimum dengan nol.

    return 0;
}
