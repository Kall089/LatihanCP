/*
============================================================
📋 TUGAS 12: Inversi Setelah Pembalikan
============================================================
Source: Original
Difficulty: Hard
Topics: inversi + analisis

PROBLEM:
Diberikan permutasi 1..N dan Q operasi. Setiap operasi membalik urutan
elemen pada sebuah segmen [l, r]. Setelah setiap operasi, cetak berapa
inversi yang ada. N dan Q kecil, tetapi carilah cara yang lebih baik
daripada menghitung ulang dari nol setiap kali.

INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: permutasi
- Q baris: l dan r

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= Q <= 2000

SAMPLE INPUT 1:
3 1
1 2 3
1 3

SAMPLE OUTPUT 1:
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
    // Membalik segmen panjang k mengubah inversi DI DALAM segmen menjadi C(k,2) dikurangi nilai sebelumnya. Inversi lintas segmen tidak berubah.

    return 0;
}
