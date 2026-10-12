/*
============================================================
📋 TUGAS 07: Accounts Merge
============================================================
Source: LeetCode 721
Difficulty: Medium
Topics: DSU + map

PROBLEM:
Diberikan N akun, masing-masing berisi nama dan beberapa email. Dua akun
milik orang yang sama kalau berbagi setidaknya satu email. Gabungkan akun
dan cetak setiap orang beserta email-emailnya (terurut).

INPUT FORMAT:
- Baris pertama: N
- N baris: nama lalu daftar email

OUTPUT FORMAT:
- Beberapa baris hasil penggabungan

CONSTRAINTS:
- 1 <= N <= 1000

SAMPLE INPUT 1:
3
John a@x b@x
John b@x c@x
Mary d@x

SAMPLE OUTPUT 1:
John a@x b@x c@x
Mary d@x
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Petakan setiap email ke indeks unik dengan map, lalu DSU atas indeks itu.

    return 0;
}
