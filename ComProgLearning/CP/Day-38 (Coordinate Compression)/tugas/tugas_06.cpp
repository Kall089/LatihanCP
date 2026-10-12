/*
============================================================
📋 TUGAS 06: Salary Queries
============================================================
Source: CSES 1144
Difficulty: Medium
Topics: kompresi + BIT

PROBLEM:
Perusahaan punya N karyawan dengan gaji tertentu. Ada Q operasi: '! k x'
mengubah gaji karyawan ke-k menjadi x, atau '? a b' menanyakan berapa
karyawan yang gajinya berada di antara a dan b.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N gaji
- Q baris berisi operasi

OUTPUT FORMAT:
- Satu baris per operasi '?'

CONSTRAINTS:
- 1 <= N, Q <= 2*10^5
- 1 <= gaji <= 10^9

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
    // Kumpulkan SEMUA nilai (gaji awal, x dari update, a dan b dari query) sebelum kompres. Lalu BIT (Day 170).

    return 0;
}
