/*
 * Day 11 — Recursion Dasar
 * File  : solution_1.cpp
 * Topik : Factorial Rekursif
 * Pendekatan: Linear recursion, depth O(n), O(n) stack
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll factorial(int n) {
    if (n == 0) return 1LL;           // BASE CASE: 0! = 1
    return (ll)n * factorial(n - 1);  // n! = n * (n-1)!
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    cout << factorial(n) << "\n";

    return 0;
}
