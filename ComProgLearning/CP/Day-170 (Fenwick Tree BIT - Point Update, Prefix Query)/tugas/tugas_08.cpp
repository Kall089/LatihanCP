/*
============================================================
📋 TUGAS 08: Nilai Terkecil ke-K Dinamis
============================================================
Source: Original
Difficulty: Medium
Topics: BIT + descent

PROBLEM:
Himpunan mula-mula kosong. Operasi '+ x' menyisipkan, '- x' menghapus satu
salinan, '? k' mencetak nilai terkecil ke-k.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?'

CONSTRAINTS:
- 1 <= Q <= 2*10^5
- 1 <= x <= 10^9

SAMPLE INPUT 1:
6
+ 5
+ 2
+ 8
? 2
- 2
? 2

SAMPLE OUTPUT 1:
5
8
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // BIT menyimpan HITUNGAN per nilai. Kerjakan dulu dengan binary search di luar O(log^2 n), lalu perbaiki dengan descent O(log n).

    return 0;
}
