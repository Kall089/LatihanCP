/*
============================================================
📋 TUGAS 12: Substring Berbeda dengan Query Tambah
============================================================
Source: Original
Difficulty: Hard
Topics: pi inkremental

PROBLEM:
Mula-mula string S kosong. Ada Q operasi, masing-masing menambahkan satu
karakter di akhir S. Setelah setiap operasi, cetak banyaknya substring
berbeda yang dimiliki S saat itu.

INPUT FORMAT:
- Baris pertama: Q
- Baris kedua: string sepanjang Q berisi karakter yang ditambahkan berurutan

OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

CONSTRAINTS:
- 1 <= Q <= 5000

SAMPLE INPUT 1:
3
aba

SAMPLE OUTPUT 1:
1
3
5
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Setiap penambahan melahirkan |cur| - max(pi(rev(cur))) substring baru.

    return 0;
}
