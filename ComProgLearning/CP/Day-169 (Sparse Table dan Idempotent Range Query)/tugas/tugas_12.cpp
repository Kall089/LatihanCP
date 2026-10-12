/*
============================================================
📋 TUGAS 12: Subarray dengan Minimum Tertentu
============================================================
Source: Original
Difficulty: Hard
Topics: divide and conquer atas minimum

PROBLEM:
Diberikan array N bilangan BERBEDA. Untuk setiap elemen, hitung ada berapa
subarray yang elemen itu menjadi MINIMUM-nya. Cetak N bilangan.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan berbeda

OUTPUT FORMAT:
- N bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5

SAMPLE INPUT 1:
4
3 1 4 2

SAMPLE OUTPUT 1:
1
4
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
    // Bisa dengan monotonic stack (Day 36) O(n), atau divide and conquer memakai sparse table indeks: pecah di posisi minimum lalu rekursi. Bandingkan keduanya.

    return 0;
}
