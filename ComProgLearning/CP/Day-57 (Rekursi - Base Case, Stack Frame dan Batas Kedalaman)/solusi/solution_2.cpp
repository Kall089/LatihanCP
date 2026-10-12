/*
 * Day 11 — Recursion Dasar
 * File  : solution_2.cpp
 * Topik : Fibonacci dengan Memoization
 * Pendekatan: Top-down DP (memoization), O(n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll memo[55];

ll fib(int n) {
    if (n <= 1) return n;            // BASE CASE: F(0)=0, F(1)=1
    if (memo[n] != -1) return memo[n]; // CACHE HIT: sudah dihitung
    return memo[n] = fib(n-1) + fib(n-2); // CACHE MISS: hitung dan simpan
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(memo, -1, sizeof(memo)); // -1 = belum dihitung

    int n;
    cin >> n;
    cout << fib(n) << "\n";

    return 0;
}
