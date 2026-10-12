/*
============================================================
📋 TUGAS 11: Suffix Array Sederhana
============================================================
Source: Original
Difficulty: Hard
Topics: counting sort berulang

PROBLEM:
Bangun suffix array dari sebuah string sepanjang N memakai pengurutan
berulang atas pasangan peringkat. Gunakan counting sort di setiap tahap
agar totalnya O(N log N), bukan O(N log^2 N). Cetak suffix array-nya.

INPUT FORMAT:
- Satu baris: string S

OUTPUT FORMAT:
- N bilangan (indeks awal sufiks terurut)

CONSTRAINTS:
- 1 <= |S| <= 10^5

SAMPLE INPUT 1:
banana

SAMPLE OUTPUT 1:
5 3 1 0 4 2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Setiap tahap mengurutkan pasangan (peringkat[i], peringkat[i+k]). Radix sort dua lewat pada pasangan itu. Materi lengkapnya Day 220.

    return 0;
}
