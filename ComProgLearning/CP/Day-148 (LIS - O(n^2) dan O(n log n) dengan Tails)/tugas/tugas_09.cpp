/*
============================================================
📋 TUGAS 09: Minimum Removals to Make Mountain Array
============================================================
Source: LC 1671
Difficulty: Medium
Topics: LIS dua arah

PROBLEM:
Array disebut "gunung" kalau ada indeks i dengan a[0]<...<a[i]>...>a[n-1],
dan i bukan ujung. Cari jumlah MINIMUM elemen yang harus dihapus.

INPUT: Baris 1 N; Baris 2 N bilangan
OUTPUT: satu bilangan
CONSTRAINTS: 3 <= N <= 1000

SAMPLE INPUT 1:            SAMPLE OUTPUT 1:
3                          0
1 3 1
Penjelasan: sudah berbentuk gunung, tidak perlu menghapus apa pun.

SAMPLE INPUT 2:            SAMPLE OUTPUT 2:
7                          3
2 1 1 5 6 2 3

SAMPLE INPUT 3:            SAMPLE OUTPUT 3:
5                          0
1 2 3 2 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // pre[i] = LIS berakhir di i (dari kiri)
    // suf[i] = LDS mulai di i    (dari kanan)
    // puncak sah kalau pre[i] > 1 DAN suf[i] > 1
    // jawaban = n - max(pre[i] + suf[i] - 1)
    return 0;}
