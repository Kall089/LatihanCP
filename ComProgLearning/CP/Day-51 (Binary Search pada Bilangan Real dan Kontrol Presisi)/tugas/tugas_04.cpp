/*
============================================================
📋 TUGAS 04: Perbandingan Presisi
============================================================
Source: Original
Difficulty: Easy
Topics: epsilon

PROBLEM:
Diberikan Q pasang bilangan real a dan b. Untuk setiap pasangan, cetak
'SAMA' kalau keduanya dianggap sama dalam toleransi 1e-9, 'KURANG' kalau
a < b, dan 'LEBIH' kalau a > b. Perhatikan bahwa nilai bisa mencapai 1e18
sehingga toleransi absolut saja tidak cukup.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi a dan b

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= Q <= 10^5

SAMPLE INPUT 1:
3
0.1 0.1
1 2
1000000000000000000 1000000000000000001

SAMPLE OUTPUT 1:
SAMA
KURANG
SAMA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk nilai besar pakai epsilon RELATIF: fabs(a-b) <= eps * max(1, |a|, |b|).

    return 0;
}
