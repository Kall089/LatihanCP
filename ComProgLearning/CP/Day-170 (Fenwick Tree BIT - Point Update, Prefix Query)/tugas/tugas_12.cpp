/*
============================================================
📋 TUGAS 12: Permutation dari Bilangan Inversi
============================================================
Source: UVa 11525
Difficulty: Hard
Topics: BIT + descent

PROBLEM:
Diberikan barisan S[1..K] di mana S[i] menyatakan berapa bilangan yang
lebih kecil dari elemen ke-i dan belum terpakai. Rekonstruksi permutasi
1..K yang menghasilkan barisan itu.

INPUT FORMAT:
- Baris pertama: T
- Setiap kasus: K lalu K bilangan S

OUTPUT FORMAT:
- T baris berisi K bilangan

CONSTRAINTS:
- 1 <= K <= 5*10^4

SAMPLE INPUT 1:
1
3
0 1 0

SAMPLE OUTPUT 1:
1 3 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // BIT menyimpan 1 untuk setiap bilangan yang masih tersedia. Elemen ke-i adalah bilangan tersedia ke-(S[i]+1) - pakai descent.

    return 0;
}
