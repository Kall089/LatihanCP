/*
============================================================
📋 TUGAS 13: Query Minimum dengan Satu Update Sementara
============================================================
Source: Original
Difficulty: Hard
Topics: batas sparse table

PROBLEM:
Diberikan array statis dan Q query. Setiap query berisi rentang [a,b] DAN
sebuah posisi p dengan nilai baru v yang berlaku HANYA untuk query itu
(perubahan tidak permanen). Cetak minimum rentang seandainya a[p] diganti v.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: a, b, p, v

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 2
5 1 9 3 7
1 5 2 100
1 3 3 0

SAMPLE OUTPUT 1:
3
0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Sparse table tidak mendukung update. Tetapi karena perubahannya sementara dan hanya satu posisi, pecah rentang menjadi bagian sebelum p, nilai v, dan bagian sesudah p.

    return 0;
}
