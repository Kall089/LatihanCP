/*
============================================================
📋 TUGAS 12: Xor Shift
============================================================
Source: AtCoder ABC150 F
Difficulty: Hard
Topics: z pada array

PROBLEM:
Diberikan dua array a[0..n-1] dan b[0..n-1]. Cari semua pasangan (k, x)
sedemikian sehingga b[i] == a[(i + k) mod n] XOR x untuk setiap i.
Cetak semua pasangan tersebut, urut berdasarkan k menaik.

INPUT FORMAT:
- Baris pertama: n
- Baris kedua: n bilangan a[i]
- Baris ketiga: n bilangan b[i]

OUTPUT FORMAT:
- Setiap baris: k dan x

CONSTRAINTS:
- 1 <= n <= 2 * 10^5
- 0 <= a[i], b[i] < 2^30

SAMPLE INPUT 1:
3
0 2 1
1 2 3

SAMPLE OUTPUT 1:
1 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Bekerja pada array selisih XOR d[i] = a[i] XOR a[i+1]. Z-function pada array, bukan string.

    return 0;
}
