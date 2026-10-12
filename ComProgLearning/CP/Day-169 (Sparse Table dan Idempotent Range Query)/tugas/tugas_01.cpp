/*
============================================================
📋 TUGAS 01: Static Range Minimum Queries
============================================================
Source: CSES 1647
Difficulty: Easy
Topics: sparse table

PROBLEM:
Array statis N bilangan, Q query rentang [a,b]. Cetak minimum tiap rentang.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: a dan b

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3

SAMPLE OUTPUT 1:
2
1
1
4
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tiga detail: batas build i+(1<<k)<=n, blok kanan r-(1<<k)+1, dan log2 lewat tabel.

    return 0;
}
