/*
============================================================
📋 TUGAS 08: Maximize Sum After K Negations
============================================================
Source: LeetCode 1005
Difficulty: Medium
Topics: Paritas

PROBLEM:
Diberikan n bilangan dan bilangan K. Lakukan TEPAT K operasi; tiap operasi mengubah
tanda satu elemen (boleh elemen yang sama berkali-kali).
Cari jumlah maksimum setelah tepat K operasi.

INPUT FORMAT:
Baris 1: n dan K
Baris 2: n bilangan

OUTPUT FORMAT:
Satu bilangan: jumlah maksimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= K <= 10^9, -10^9 <= a[i] <= 10^9

SAMPLE INPUT 1:
4 3
-1 -2 -3 4

SAMPLE OUTPUT 1:
10
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Dua tahap: balik negatif dari yang nilai mutlaknya terbesar, lalu tangani sisa operasi lewat paritas. Cari elemen terkecil SETELAH tahap pertama, bukan pada array asli.

    return 0;
}
