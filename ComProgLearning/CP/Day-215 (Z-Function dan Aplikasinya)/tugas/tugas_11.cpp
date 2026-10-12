/*
============================================================
📋 TUGAS 11: Who Killed Cock Robin
============================================================
Source: AtCoder ABC141 E
Difficulty: Hard
Topics: z + binary search

PROBLEM:
Diberikan string S sepanjang N, cari panjang TERPANJANG substring yang
muncul setidaknya dua kali di dalam S TANPA saling tumpang tindih.
Jika tidak ada substring berulang, cetak 0.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: string S

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 5000

SAMPLE INPUT 1:
5
ababa

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap posisi awal i, bangun z dari S[i..]. Kecocokan tidak tumpang tindih kalau jaraknya >= panjangnya.

    return 0;
}
