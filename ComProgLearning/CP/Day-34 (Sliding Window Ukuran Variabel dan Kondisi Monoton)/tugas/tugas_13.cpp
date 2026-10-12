/*
============================================================
📋 TUGAS 13: Jumlah Tepat S dengan Nol
============================================================
Source: Original
Difficulty: Hard
Topics: trik pengurangan, jebakan nol

PROBLEM:
Diberikan array N bilangan NON-NEGATIF (boleh nol) dan target S.
Hitung berapa banyak subarray yang jumlahnya tepat S.

INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= a[i], S <= 10^9

SAMPLE INPUT 1:
5 3
1 0 2 0 1

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
    // Elemen nol membuat banyak subarray berbeda dengan jumlah sama. Trik atMost tetap benar; naif dua pointer biasa TIDAK.

    return 0;
}
