/*
============================================================
📋 TUGAS 08: Prefix Terkecil
============================================================
Source: Original
Difficulty: Medium
Topics: prefix + minimum berjalan

PROBLEM:
Diberikan array N bilangan. Cari jumlah subarray MINIMUM (subarray tidak
boleh kosong). Selesaikan menggunakan prefix sum, bukan Kadane.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
5
3 -4 2 -3 1

SAMPLE OUTPUT 1:
-5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // min subarray = min(pre[j] - max pre[i] untuk i<j). Simpan maksimum prefix yang sudah lewat.

    return 0;
}
