/*
============================================================
📋 TUGAS 08: Sliding Window Median
============================================================
Source: LeetCode 480
Difficulty: Hard
Topics: Dua heap

PROBLEM:
Diberikan array n bilangan dan jendela berukuran k. Untuk setiap posisi jendela,
cetak MEDIAN elemen di dalam jendela itu.
Kalau k genap, median adalah rata-rata dua elemen tengah.

INPUT FORMAT:
Baris 1: n dan k
Baris 2: n bilangan

OUTPUT FORMAT:
n-k+1 bilangan real dengan satu angka di belakang koma

CONSTRAINTS:
1 <= k <= n <= 10^5, -10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
8 3
1 3 -1 -3 5 3 6 7

SAMPLE OUTPUT 1:
1.0
-1.0
-1.0
3.0
5.0
6.0
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua heap: max-heap untuk separuh kecil, min-heap untuk separuh besar. Penghapusan elemen yang keluar jendela adalah bagian tersulit — pelajari teknik lazy deletion.

    return 0;
}
