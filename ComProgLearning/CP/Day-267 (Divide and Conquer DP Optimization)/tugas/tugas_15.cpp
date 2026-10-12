/*
============================================================
📋 TUGAS 15: Partisi String dengan Biaya Pengulangan Karakter
============================================================
Source: Classic D&C DP Optimization / Strings
Difficulty: Menantang
Topics: Divide and Conquer DP Optimization, Sliding Window

PROBLEM:
Diberikan sebuah string S dengan panjang N berisi huruf kecil 'a'..'z'.
Kamu harus membagi string S menjadi TEPAT K substring berurutan tak kosong.
Biaya suatu substring S[l..r] didefinisikan sebagai JUMLAH PASANGAN INDEKS (i, j)
sedemikian sehingga l <= i < j <= r dan S[i] == S[j] (pasangan karakter kembar).

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh string menjadi tepat K substring!

INPUT FORMAT:
Baris pertama berisi dua bilangan bulat N dan K.
Baris kedua berisi string S.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: biaya minimum.

CONSTRAINTS:
1 <= K <= min(N, 20)
1 <= N <= 20.000
S hanya terdiri dari huruf kecil 'a'..'z'

SAMPLE INPUT 1:
6 2
abacba

SAMPLE OUTPUT 1:
1
(Bagi "aba" (sepasang 'a', biaya 1) dan "cba" (tanpa karakter kembar, biaya 0), total = 1 + 0 = 1)

SAMPLE INPUT 2:
4 4
aaaa

SAMPLE OUTPUT 2:
0
(Bagi menjadi 4 substring: "a", "a", "a", "a", masing-masing biaya 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    string s;
    if (!(cin >> s)) return 0;

    // TODO: Selesaikan dengan D&C DP + Two-Pointer Sliding Window

    return 0;
}
