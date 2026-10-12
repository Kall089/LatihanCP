/*
============================================================
📋 TUGAS 07: Sambung Maksimal
============================================================
Source: Original
Difficulty: Medium
Topics: overlap via z

PROBLEM:
Diberikan dua string A dan B, cari panjang sufiks A terpanjang yang juga
merupakan prefiks B. Panjangnya tidak boleh melebihi min(|A|, |B|).

INPUT FORMAT:
- Baris pertama: A
- Baris kedua: B

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= |A|, |B| <= 5 * 10^5

SAMPLE INPUT 1:
abcde
cdefg

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
    // Bangun z pada B + '\\1' + A, cari i di bagian A dengan z[i] == panjang sisa.

    return 0;
}
