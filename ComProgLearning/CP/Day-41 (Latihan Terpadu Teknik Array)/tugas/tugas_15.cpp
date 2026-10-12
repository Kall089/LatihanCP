/*
============================================================
📋 TUGAS 15: Menghitung Subarray Stabil
============================================================
Source: Original (varian LeetCode 1438)
Difficulty: Hard (Contest-level)
Topics: sliding window + dua monotonic deque + counting (Day 34 + 37 + 40)

PROBLEM:
Diberikan array N bilangan dan bilangan K. Sebuah subarray disebut
STABIL kalau selisih antara nilai terbesar dan terkecil di dalamnya
tidak melebihi K.

Hitung ada BERAPA BANYAK subarray yang stabil.

Exercise 4 mencari subarray stabil TERPANJANG. Soal ini mencari
BANYAKNYA. Perhatikan bahwa struktur intinya sama persis - yang berubah
hanya satu baris di dalam loop. Kenali polanya: begitu kamu punya
window terpanjang yang valid dan berakhir di r, banyaknya subarray
valid yang berakhir di r adalah panjang window itu.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 2*10^5
- 0 <= K <= 10^9
- 1 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus kecil
input:
3 2
1 3 6
output:
4
penjelasan: yang stabil: [1], [3], [6], dan [1,3]. Subarray [3,6]
selisihnya 3 > 2, jadi tidak.

SAMPLE 2 - semua sama dengan K = 0
input:
3 0
5 5 5
output:
6
penjelasan: SEMUA 6 subarray stabil.

SAMPLE 3 - K cukup besar
input:
4 3
1 2 3 4
output:
10
penjelasan: semua subarray stabil, ada 4*5/2 = 10.

SAMPLE 4 - K = 0 dengan nilai berselang-seling
input:
4 0
10 1 10 1
output:
4
penjelasan: hanya subarray sepanjang 1 yang stabil. Jawabannya N.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- setelah window [l, r] valid, tambahkan (r - l + 1) ke jawaban
- validitas window bersifat monoton: kalau [l, r] valid, semua
  subwindow-nya juga valid. Itu yang membuat penjumlahan ini benar
- jawabannya bisa ~2*10^10, pakai long long
- verifikasi dengan brute force O(n^2) pada n <= 200
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
