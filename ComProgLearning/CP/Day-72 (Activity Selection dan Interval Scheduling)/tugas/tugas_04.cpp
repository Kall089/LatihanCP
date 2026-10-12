/*
============================================================
📋 TUGAS 04: Projects
============================================================
Source: CSES 1140
Difficulty: Medium
Topics: Weighted interval scheduling

PROBLEM:
Ada n proyek. Proyek ke-i berlangsung dari hari a[i] sampai hari b[i] (inklusif) dan
memberi keuntungan p[i]. Hanya satu proyek boleh dikerjakan pada satu hari.
Cari total keuntungan maksimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: a[i], b[i], p[i]

OUTPUT FORMAT:
Satu bilangan: keuntungan maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= a[i] <= b[i] <= 10^9, 1 <= p[i] <= 10^9

SAMPLE INPUT 1:
4
2 4 4
3 6 6
6 8 2
5 7 3

SAMPLE OUTPUT 1:
7
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Interval TERTUTUP — proyek berikutnya harus mulai pada hari yang benar-benar lebih besar dari b. Itu menentukan lower_bound atau upper_bound.

    return 0;
}
