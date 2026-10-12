/*
============================================================
📋 TUGAS 11: Pemilihan Kurung Ekspresi Logika Boolean
============================================================
Source: Classic DP / Boolean Parenthesization
Difficulty: Hard
Topics: Range DP Counting, Multiple State Tracking

PROBLEM:
Diberikan sebuah ekspresi logika boolean yang terdiri dari simbol:
- Operand: 'T' (True) dan 'F' (False)
- Operator di antara dua operand: '&' (AND), '|' (OR), '^' (XOR)
Panjang simbol total adalah 2*N - 1 (ada N operand dan N - 1 operator).

Hitung berapa banyak cara berbeda untuk memberi tanda kurung pada seluruh ekspresi
sedemikian rupa sehingga hasil evaluasi akhir dari ekspresi bernilai TRUE.
Keluarkan hasil perhitungan modulo 1.003 (atau modulo 1.000.000.007 jika standar CP).
Gunakan MOD = 1.000.000.007.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N, menyatakan banyak operand.
Baris kedua berisi string operand (panjang N, berisi 'T' dan 'F').
Baris ketiga berisi string operator (panjang N - 1, berisi '&', '|', '^').

OUTPUT FORMAT:
Satu bilangan bulat: banyak cara pengurungan bernilai TRUE modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 100

SAMPLE INPUT 1:
3
TFT
^&

SAMPLE OUTPUT 1:
2
(Penjelasan: Ekspresi: T ^ F & T.
Dua cara pengurungan:
1. ((T ^ F) & T) = T & T = T (True)
2. (T ^ (F & T)) = T ^ F = T (True)
Kedua cara menghasilkan True, total = 2)

SAMPLE INPUT 2:
2
TF
|

SAMPLE OUTPUT 2:
1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string opnd, optr;
    if (!(cin >> n >> opnd >> optr)) return 0;

    // TODO: Selesaikan Boolean Parenthesization dengan Range DP
    // true_dp[l][r] dan false_dp[l][r]
    // Coba semua titik pecah k dan kombinasikan dengan operator optr[k]

    return 0;
}
