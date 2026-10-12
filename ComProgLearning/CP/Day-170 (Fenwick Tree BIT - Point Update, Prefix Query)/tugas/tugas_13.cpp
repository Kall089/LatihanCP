/*
============================================================
📋 TUGAS 13: Range Update Range Query
============================================================
Source: Original
Difficulty: Hard
Topics: dua BIT

PROBLEM:
Array N bilangan, Q operasi: '1 a b u' menambah u ke a[a..b], '2 a b'
mencetak JUMLAH a[a..b].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi jenis 2

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
5 3
1 2 3 4 5
2 1 5
1 2 4 10
2 1 5

SAMPLE OUTPUT 1:
15
45
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Butuh DUA BIT. prefix(i) = b1.query(i)*i - b2.query(i). Turunkan sendiri rumusnya, atau bandingkan dengan segment tree lazy (Day 176).

    return 0;
}
