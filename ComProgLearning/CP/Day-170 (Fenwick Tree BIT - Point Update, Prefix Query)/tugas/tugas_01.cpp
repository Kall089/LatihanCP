/*
============================================================
📋 TUGAS 01: Dynamic Range Sum Queries
============================================================
Source: CSES 1648
Difficulty: Easy
Topics: BIT dasar

PROBLEM:
Array N bilangan, Q operasi: '1 k u' mengganti a[k] menjadi u, '2 a b'
mencetak jumlah a[a..b].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi jenis 2

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
8 4
3 2 4 5 1 1 5 3
2 1 4
2 5 6
1 3 1
2 1 4

SAMPLE OUTPUT 1:
14
2
11
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // BIT 1-INDEXED. 'Ganti' = tambah SELISIH, jadi simpan nilai lama terpisah.

    return 0;
}
