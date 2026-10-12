/*
============================================================
📋 TUGAS 14: Presisi yang Menipu
============================================================
Source: Original
Difficulty: Hard
Topics: analisis presisi

PROBLEM:
Diberikan Q kasus, masing-masing berisi bilangan bulat a dan b dengan
1 <= a, b <= 10^18. Cetak 'YA' kalau a habis dibagi b, 'TIDAK' kalau tidak.
Kamu HARUS mengerjakannya tanpa operator modulo, hanya dengan pembagian.
Soal ini melatihmu melihat kenapa pendekatan berbasis double GAGAL di sini.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi a dan b

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= Q <= 10^5

SAMPLE INPUT 1:
2
1000000000000000000 1000000000000000000
1000000000000000000 3

SAMPLE OUTPUT 1:
YA
TIDAK
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Coba dulu dengan double dan lihat di mana ia salah. Lalu kerjakan dengan pembagian BILANGAN BULAT: (a / b) * b == a. Pelajarannya: double punya ~15-17 digit signifikan, tidak cukup untuk 10^18.

    return 0;
}
