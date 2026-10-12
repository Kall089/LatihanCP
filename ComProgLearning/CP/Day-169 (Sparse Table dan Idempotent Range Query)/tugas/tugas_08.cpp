/*
============================================================
📋 TUGAS 08: CGCDSSQ
============================================================
Source: Codeforces 475D
Difficulty: Medium
Topics: gcd + sifat O(log V)

PROBLEM:
Diberikan array N bilangan dan Q query berisi sebuah nilai x. Untuk setiap
query, hitung ADA BERAPA subarray yang GCD-nya tepat x.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan
- Baris ketiga: Q
- Q baris: satu bilangan x

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= Q <= 3*10^5

SAMPLE INPUT 1:
3
2 6 3
2
2
3

SAMPLE OUTPUT 1:
1
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
    // Kalau ujung kiri ditetapkan dan ujung kanan digeser, gcd hanya berubah O(log V) kali. Jaga daftar (nilai gcd, berapa banyak) per ujung kanan.

    return 0;
}
