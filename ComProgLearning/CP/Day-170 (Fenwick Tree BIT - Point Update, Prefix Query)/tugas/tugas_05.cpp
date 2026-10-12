/*
============================================================
📋 TUGAS 05: XOR pada Rentang dengan Update
============================================================
Source: Original
Difficulty: Easy
Topics: BIT untuk XOR

PROBLEM:
Array N bilangan, Q operasi: '1 k u' mengganti a[k] menjadi u, '2 a b'
mencetak hasil XOR seluruh elemen a[a..b].

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi jenis 2

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5

SAMPLE INPUT 1:
4 3
1 2 3 4
2 1 4
1 2 5
2 1 4

SAMPLE OUTPUT 1:
4
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // XOR punya INVERS (dirinya sendiri), jadi BIT berlaku. range(l,r) = query(r) XOR query(l-1). Untuk 'ganti', XOR-kan nilai lama lalu nilai baru.

    return 0;
}
