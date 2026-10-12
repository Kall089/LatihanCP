/*
============================================================
📋 TUGAS 09: Semester Paralel
============================================================
Source: Varian klasik (level / longest chain)
Difficulty: Medium
Topics: Kahn + level

PROBLEM:
N mata kuliah, M prasyarat. Boleh mengambil berapa pun per semester.
Cetak jumlah semester minimum, lalu daftar mata kuliah tiap semester
(terurut menaik). Jika mustahil, cetak -1 saja.

INPUT FORMAT:
- Baris 1: N M
- M baris: u v

OUTPUT FORMAT:
- Baris 1: jumlah semester S
- S baris berikutnya: isi tiap semester

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 4                    3
1 3                    1 2
2 3                    3
3 4                    4 5
3 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 0                    1
                       1 2 3

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
2 2                    -1
1 2
2 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Kelompokkan simpul berdasarkan lvl[].
    return 0;
}
