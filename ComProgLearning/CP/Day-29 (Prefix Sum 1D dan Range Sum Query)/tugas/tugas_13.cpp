/*
============================================================
📋 TUGAS 13: Jumlah Semua Subarray
============================================================
Source: Original
Difficulty: Hard
Topics: kontribusi tiap elemen

PROBLEM:
Diberikan array N bilangan, hitung TOTAL dari jumlah seluruh subarray
yang mungkin. Sebagai contoh, untuk [1,2] subarraynya adalah [1], [2],
dan [1,2], sehingga totalnya 1 + 2 + 3 = 6.
Cetak hasilnya modulo 1_000_000_007.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan mod 1e9+7

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= a[i] <= 10^9

SAMPLE INPUT 1:
2
1 2

SAMPLE OUTPUT 1:
6
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Jangan menjumlahkan subarray satu per satu. Hitung BERAPA KALI setiap elemen muncul: elemen ke-i muncul di (i+1)*(n-i) subarray.

    return 0;
}
