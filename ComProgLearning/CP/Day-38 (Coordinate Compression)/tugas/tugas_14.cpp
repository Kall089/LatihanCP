/*
============================================================
📋 TUGAS 14: Nilai ke-K Terkecil Dinamis
============================================================
Source: Original
Difficulty: Hard
Topics: kompresi + BIT + descent

PROBLEM:
Mula-mula himpunan kosong. Ada Q operasi: '+ x' menambahkan x, '- x'
menghapus satu salinan x, atau '? k' menanyakan nilai terkecil ke-k yang
ada saat itu. Dijamin operasi selalu valid.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?'

CONSTRAINTS:
- 1 <= Q <= 2*10^5
- 1 <= x <= 10^9

SAMPLE INPUT 1:
5
+ 5
+ 2
? 1
- 2
? 1

SAMPLE OUTPUT 1:
2
5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Baca SEMUA operasi dulu (offline), kumpulkan semua x, kompres, lalu BIT dengan pencarian biner di dalamnya.

    return 0;
}
