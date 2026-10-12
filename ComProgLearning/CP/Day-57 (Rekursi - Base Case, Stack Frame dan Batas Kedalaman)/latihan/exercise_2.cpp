/*
 * Day 11 — Recursion Dasar
 * File  : exercise_2.cpp
 * Topik : Fibonacci dengan Memoization
 * -----------------------------------------------
 * Hitung bilangan Fibonacci ke-n.
 * F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
 *
 * Catatan: JANGAN gunakan rekursi naif (TLE untuk n besar).
 * Gunakan memoization: simpan hasil F(n) di array memo[].
 *
 * Input format  : Satu bilangan n
 * Output format : Nilai F(n)
 * Constraints   : 0 ≤ n ≤ 50
 *
 * Sample Input 1:      Sample Output 1:
 * 10                   55
 *
 * Sample Input 2:      Sample Output 2:
 * 0                    0
 *
 * Sample Input 3:      Sample Output 3:
 * 1                    1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll memo[55]; // memo[i] = F(i), -1 jika belum dihitung

// TODO: Implementasikan Fibonacci dengan memoization
// 1. Cek apakah memo[n] sudah ada (bukan -1)
// 2. Jika sudah, return memo[n] (CACHE HIT)
// 3. Jika belum, hitung dan simpan ke memo[n] (CACHE MISS)
ll fib(int n) {
    if (n <= 1) return n; // BASE CASE: F(0)=0, F(1)=1

    // TODO: Cek cache
    // if (memo[n] != -1) return memo[n];

    // TODO: Hitung dan simpan
    // return memo[n] = fib(n-1) + fib(n-2);

    return 0; // ganti ini
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(memo, -1, sizeof(memo)); // inisialisasi: semua belum dihitung

    int n;
    cin >> n;
    cout << fib(n) << "\n";

    return 0;
}
