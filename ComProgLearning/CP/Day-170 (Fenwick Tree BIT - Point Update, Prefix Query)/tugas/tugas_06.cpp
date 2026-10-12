/*
============================================================
📋 TUGAS 06: Salary Queries
============================================================
Source: CSES 1144
Difficulty: Medium
Topics: BIT + kompresi offline

PROBLEM:
N karyawan bergaji p[i]. Operasi '! k x' mengubah gaji, '? a b' menghitung
berapa karyawan bergaji di antara a dan b.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N gaji
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?'

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5
- gaji sampai 10^9

SAMPLE INPUT 1:
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3

SAMPLE OUTPUT 1:
3
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Nilai baru dari operasi '!' juga harus masuk kamus kompresi - baca SELURUH operasi dulu (offline).

    return 0;
}
