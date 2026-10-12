/*
============================================================
📋 TUGAS 08: Kapan Melebihi Rata-rata
============================================================
Source: Original
Difficulty: Hard
Topics: PBS + prefix

PROBLEM:
N kejadian; kejadian ke-t menambah v[t] ke posisi p[t] (satu posisi saja).
Untuk tiap query (posisi p, target T), cari kejadian keberapa nilai di p
melebihi T. Selesaikan dengan PBS meski ada cara yang lebih langsung, lalu
BANDINGKAN waktu berjalannya dengan cara langsung itu.

INPUT FORMAT:
- Baris pertama: M, N, Q
- N baris: p v
- Q baris: p T

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= M, N, Q <= 2*10^5

SAMPLE INPUT 1:
3 3 2
1 5
2 3
1 4
1 8
2 10

SAMPLE OUTPUT 1:
3
-1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Cara langsung: kelompokkan kejadian per posisi lalu prefix sum. PBS bekerja tetapi berlebihan - itulah pelajarannya.

    return 0;
}
