/*
============================================================
📋 TUGAS 02: Job Sequencing with Deadlines
============================================================
Source: Klasik (GfG)
Difficulty: Medium
Topics: Regret deadline+untung

PROBLEM:
Ada n pekerjaan; masing-masing butuh tepat 1 satuan waktu, memberi keuntungan p[i],
dan harus dikerjakan pada slot 1 sampai d[i]. Satu slot satu pekerjaan.
Cari total keuntungan maksimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: d[i] dan p[i]

OUTPUT FORMAT:
Satu bilangan: keuntungan maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= d[i] <= n, 1 <= p[i] <= 10^9

SAMPLE INPUT 1:
4
4 20
1 10
1 40
1 30

SAMPLE OUTPUT 1:
60
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Arah heap BERLAWANAN dengan Tugas 01. Pikirkan kenapa: apa yang dimaksud 'terburuk' ketika semua pekerjaan memakan slot yang sama?

    return 0;
}
