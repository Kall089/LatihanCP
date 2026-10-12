/*
============================================================
📋 TUGAS 14: Kth Smallest in Sorted Matrix
============================================================
Source: LeetCode 378
Difficulty: Hard
Topics: binary search pada nilai

PROBLEM:
Diberikan matriks N x N yang setiap barisnya dan setiap kolomnya terurut
menaik, cari elemen terkecil ke-k.

INPUT FORMAT:
- Baris pertama: N dan k
- N baris berisi N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 300
- 1 <= k <= N*N

SAMPLE INPUT 1:
3 8
1 5 9
10 11 13
12 13 15

SAMPLE OUTPUT 1:
13
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Binary search pada NILAI, bukan indeks. Predikatnya 'berapa elemen <= x', yang bisa dihitung O(N) dengan menyusuri dari pojok.

    return 0;
}
