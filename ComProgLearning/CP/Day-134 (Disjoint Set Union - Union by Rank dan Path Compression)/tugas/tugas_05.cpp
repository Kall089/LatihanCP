/*
============================================================
📋 TUGAS 05: Building Roads
============================================================
Source: CSES 1666
Difficulty: Easy
Topics: komponen + jalan penghubung

PROBLEM:
N kota dan M jalan yang sudah ada. Cari jumlah jalan MINIMAL yang harus
ditambahkan agar seluruh kota terhubung, beserta daftar pasangan kota yang
harus dihubungkan.

INPUT FORMAT:
- Baris pertama: N dan M
- M baris: a dan b

OUTPUT FORMAT:
- Baris pertama: jumlah jalan baru
- Baris berikutnya: pasangan kota

CONSTRAINTS:
- 1 <= N, M <= 2*10^5

SAMPLE INPUT 1:
4 2
1 2
3 4

SAMPLE OUTPUT 1:
1
1 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Jumlah jalan minimal = komponen - 1. Kumpulkan satu perwakilan per komponen lalu hubungkan berurutan.

    return 0;
}
