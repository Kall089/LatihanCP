/*
============================================================
📋 TUGAS 07: Antrean Bermodal
============================================================
Source: Latihan mandiri (Codeforces-style)
Difficulty: Hard
Topics: Kriteria untuk kelayakan

PROBLEM:
Ada n tugas; tugas ke-i butuh modal minimal m[i] untuk dimulai dan menghabiskan c[i]
(dijamin c[i] <= m[i]). Modal awalmu M dan tidak boleh negatif kapan pun.
Tentukan apakah ada urutan yang memungkinkan seluruh tugas dikerjakan.

INPUT FORMAT:
Baris 1: n dan M
n baris berikutnya: m[i] dan c[i]

OUTPUT FORMAT:
YES atau NO

CONSTRAINTS:
1 <= n <= 2*10^5, 0 <= M <= 10^18, 0 <= c[i] <= m[i] <= 10^9

SAMPLE INPUT 1:
2 20
10 5
8 6

SAMPLE OUTPUT 1:
YES
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dugaan 'urut m menurun' terlihat sangat masuk akal dan SALAH — ia gagal pada sekitar 2 persen kasus acak. Turunkan kriteria yang benar dari syarat kelayakan dua tugas berdampingan.

    return 0;
}
