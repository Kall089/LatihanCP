/*
============================================================
📋 TUGAS 01: Maximum Subarray Sum
============================================================
Source: CSES 1643
Difficulty: Easy
Topics: kadane dasar

PROBLEM:
Diberikan array N bilangan bulat (boleh negatif). Cari jumlah subarray
TIDAK KOSONG yang paling besar.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal, ada positif dan negatif
input:
8
-1 3 -2 5 3 -5 2 2
output:
9
penjelasan: subarray [3,-2,5,3] = 9. Menambahkan -5 di belakangnya
membuat jumlahnya turun jadi 4, jadi berhenti di situ.

SAMPLE 2 - semua negatif
input:
4
-5 -1 -3 -2
output:
-1
penjelasan: karena subarray tidak boleh kosong, jawabannya elemen
terbesar yaitu -1. Kalau kodemu mencetak 0, berarti best kamu
diinisialisasi 0 dan itu salah.

SAMPLE 3 - N = 1
input:
1
-1000000000
output:
-1000000000
penjelasan: loop harus tetap benar saat hanya ada satu elemen.

SAMPLE 4 - uji overflow
input:
5
1000000000 1000000000 1000000000 1000000000 1000000000
output:
5000000000
penjelasan: jawabannya 5*10^9, jauh melewati batas int (~2.1*10^9).
Kalau kamu memakai int, sample ini akan mencetak angka negatif ngawur.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- best diinisialisasi LLONG_MIN atau a[0], BUKAN 0
- semua variabel penampung jumlah bertipe long long
- kode benar untuk N = 1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long best = arr[0];
    long long curr = arr[0];

    for (int i = 1; i < n; i++)
    {
        curr = max(arr[i], curr + arr[i]);
        best = max(curr, best);
    }

    cout << best;
}