/*
============================================================
📋 TUGAS 03: Range XOR Queries
============================================================
Source: CSES 1650
Difficulty: Easy
Topics: prefix xor

PROBLEM:
Diberikan array N bilangan dan Q pertanyaan rentang [a, b]. Cetak hasil XOR
seluruh elemen pada rentang tersebut.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris: a dan b

OUTPUT FORMAT:
- Q baris berisi bilangan

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5
- 1 <= a[i] <= 10^9

SAMPLE INPUT 1:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3

SAMPLE OUTPUT 1:
3
0
6
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
    // XOR adalah inversnya sendiri: range = px[r] ^ px[l-1].

    return 0;
}
