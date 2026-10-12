/*
============================================================
📋 TUGAS 10: Mengecat Pagar (Paint Fence)
============================================================
Source: LeetCode 276
Difficulty: Medium
Topics: State Design, Counting DP

PROBLEM:
Terdapat N tiang pagar yang berderet lurus (tiang 1 sampai N).
Kamu memiliki K pilihan warna berbeda untuk mengecat tiang-tiang tersebut.
Aturan: Tidak boleh ada LEBIH DARI DUA tiang bersebelahan yang memiliki warna yang sama!
(Artinya: 2 tiang berdampingan boleh sewarna, tetapi 3 tiang berdampingan sewarna DILARANG).
Hitung banyaknya cara mengecat seluruh pagar modulo 1.000.000.007.

INPUT FORMAT:
Satu baris berisi dua bilangan bulat N dan K.

OUTPUT FORMAT:
Satu bilangan bulat: banyak cara pengecatan modulo 1.000.000.007.

CONSTRAINTS:
1 <= N <= 100.000
1 <= K <= 100.000

SAMPLE INPUT 1:
3 2

SAMPLE OUTPUT 1:
6
(Penjelasan: Misal warna {M, B}. Pola panjang 3 yang dilarang adalah MMM dan BBB. Total 2^3 - 2 = 6.)

SAMPLE INPUT 2:
1 1

SAMPLE OUTPUT 2:
1

SAMPLE INPUT 3:
7 2

SAMPLE OUTPUT 3:
42
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Definisikan dua state untuk tiang ke-i:
    // same: tiang ke-i memiliki warna yang sama dengan tiang ke-(i-1)
    // diff: tiang ke-i memiliki warna yang BERBEDA dari tiang ke-(i-1)
    // Transisi:
    // next_same = diff
    // next_diff = (same + diff) * (k - 1) % MOD

    return 0;
}
