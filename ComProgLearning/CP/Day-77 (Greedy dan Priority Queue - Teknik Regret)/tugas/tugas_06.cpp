/*
============================================================
📋 TUGAS 06: Mesin Ganda
============================================================
Source: Latihan mandiri
Difficulty: Hard
Topics: Regret kapasitas M

PROBLEM:
Ada n pekerjaan (masing-masing 1 satuan waktu, tenggat d[i], keuntungan p[i]) dan M
mesin identik. Pada tiap slot waktu paling banyak M pekerjaan dikerjakan.
Cari total keuntungan maksimum.

INPUT FORMAT:
Baris 1: n dan M
n baris berikutnya: d[i] dan p[i]

OUTPUT FORMAT:
Satu bilangan: keuntungan maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= M <= 10^5, 1 <= d[i] <= n, 1 <= p[i] <= 10^9

SAMPLE INPUT 1:
4 2
1 10
1 20
1 30
2 5

SAMPLE OUTPUT 1:
55
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perubahannya satu baris dari Tugas 02. Awas overflow pada d dikali M — keduanya muat di int, hasilnya tidak. Verifikasi silang dengan M = 1 terhadap Tugas 02.

    return 0;
}
