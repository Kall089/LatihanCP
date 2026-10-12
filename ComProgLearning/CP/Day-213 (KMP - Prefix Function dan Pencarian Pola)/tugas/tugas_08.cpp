/*
============================================================
📋 TUGAS 08: Overlap Dua String
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: pi pada gabungan

PROBLEM:
Diberikan dua string A dan B. Cari panjang TERPANJANG dari akhiran A yang
sekaligus menjadi awalan B. Nilai ini dipakai saat menggabungkan dua kata
dengan tumpang tindih maksimum.
Petunjuk: bangun pi dari B + "#" + A, lalu ambil nilai terakhirnya.

INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

OUTPUT FORMAT:
- Satu bilangan: panjang overlap.

CONSTRAINTS:
- 1 <= |A|, |B| <= 10^5

SAMPLE INPUT 1:
kompetisi
sisipan

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ingat inti KMP: j = pi[j - 1], dan indeks teks tidak pernah mundur

    return 0;
}
