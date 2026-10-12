/*
============================================================
📋 TUGAS 05: Jarak Edit Minimum dengan Operasi Tertimbang
============================================================
Source: Classic String DP / Weighted Edit Distance
Difficulty: Medium
Topics: Edit Distance, Weighted Operations

PROBLEM:
Diberikan dua string A dan B, serta biaya untuk 3 operasi pengeditan:
- Biaya insert satu karakter: c_ins
- Biaya delete satu karakter: c_del
- Biaya replace satu karakter dengan karakter lain: c_rep
Jika karakter sama, biaya = 0.
Tentukan total biaya minimum untuk mengubah string A menjadi string B!

INPUT FORMAT:
Baris pertama berisi string A.
Baris kedua berisi string B.
Baris ketiga berisi tiga bilangan bulat c_ins, c_del, c_rep.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
0 <= |A|, |B| <= 2.000
1 <= c_ins, c_del, c_rep <= 1.000

SAMPLE INPUT 1:
abc
abd
2 3 4

SAMPLE OUTPUT 1:
4
(Ganti 'c' menjadi 'd' dengan biaya 4)

SAMPLE INPUT 2:
abc
abd
5 5 12

SAMPLE OUTPUT 2:
10
(Hapus 'c' [biaya 5], lalu sisip 'd' [biaya 5] = total 10 < replace 12)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    ll c_ins, c_del, c_rep;
    cin >> c_ins >> c_del >> c_rep;

    // TODO: Selesaikan Weighted Edit Distance

    return 0;
}
