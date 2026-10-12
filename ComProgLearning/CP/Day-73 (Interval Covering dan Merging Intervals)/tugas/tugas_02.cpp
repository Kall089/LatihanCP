/*
============================================================
📋 TUGAS 02: Insert Interval
============================================================
Source: LeetCode 57
Difficulty: Easy
Topics: Sisip O(n)

PROBLEM:
Diberikan daftar n interval yang SUDAH terurut dan saling terpisah, serta satu
interval baru. Sisipkan interval baru dan gabungkan bila perlu.
Selesaikan tanpa mengurutkan ulang.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r
Baris terakhir: l dan r interval baru

OUTPUT FORMAT:
Baris 1: banyaknya interval hasil
Baris berikutnya: masing-masing satu interval

CONSTRAINTS:
0 <= n <= 10^4, 0 <= koordinat <= 10^5

SAMPLE INPUT 1:
3
1 3
6 9
12 16
4 8

SAMPLE OUTPUT 1:
3
1 3
4 9
12 16
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tiga fase: salin yang berakhir di kiri, lebur yang beririsan, salin sisanya. Tanpa sort, O(n).

    return 0;
}
