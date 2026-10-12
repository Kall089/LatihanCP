/*
============================================================
📋 TUGAS 05: Jump Game II
============================================================
Source: LeetCode 45
Difficulty: Medium
Topics: Covering dalam penyamaran

PROBLEM:
Diberikan array n bilangan a[i]. Dari posisi i kamu bisa melompat ke posisi mana pun
dari i+1 sampai i+a[i]. Dijamin posisi n-1 selalu bisa dicapai.
Cari jumlah lompatan minimum dari posisi 0 ke posisi n-1.

INPUT FORMAT:
Baris 1: n
Baris 2: n bilangan a[i]

OUTPUT FORMAT:
Satu bilangan: jumlah lompatan minimum

CONSTRAINTS:
1 <= n <= 10^4, 0 <= a[i] <= 1000

SAMPLE INPUT 1:
5
2 3 1 1 4

SAMPLE OUTPUT 1:
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
    // Petak i sama dengan interval [i, i+a[i]]. Setelah melihat pemetaan itu, ini Exercise 3 tanpa perlu membangun array interval.

    return 0;
}
