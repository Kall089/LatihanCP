/*
============================================================
📋 TUGAS 10: Cinema
============================================================
Source: CF 670C
Difficulty: Medium
Topics: kompresi + hitung

PROBLEM:
N penonton, masing-masing tahu satu bahasa. Ada M film, film ke-j punya
bahasa audio b[j] dan subtitle c[j]. Pilih film yang memaksimalkan jumlah
penonton yang mengerti audionya; kalau seri, maksimalkan yang mengerti
subtitle-nya. Cetak nomor filmnya.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bahasa penonton
- Baris ketiga: M
- Baris keempat: M bahasa audio
- Baris kelima: M bahasa subtitle

OUTPUT FORMAT:
- Satu bilangan (1-based)

CONSTRAINTS:
- 1 <= N, M <= 2*10^5
- bahasa sampai 10^9

SAMPLE INPUT 1:
3
2 3 2
2
3 2
2 3

SAMPLE OUTPUT 1:
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
    // Kompres bahasa penonton lalu hitung frekuensi. Bahasa film yang tidak ada di kamus berarti 0 penonton.

    return 0;
}
