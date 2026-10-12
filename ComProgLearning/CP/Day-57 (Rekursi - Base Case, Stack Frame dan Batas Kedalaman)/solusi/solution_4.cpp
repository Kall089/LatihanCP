/*
 * Day 11 — Recursion Dasar
 * File  : solution_4.cpp
 * Topik : Fast Power (a^b mod m)
 * Pendekatan: Exponentiation by squaring, O(log b) time & space
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fastpow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1LL;                      // BASE CASE: a^0 = 1
    ll half = fastpow(base, exp / 2, mod);
    ll half2 = (half * half) % mod;
    if (exp % 2 == 0) return half2;                // a^(2k) = (a^k)^2
    return (base % mod * half2) % mod;             // a^(2k+1) = a * (a^k)^2
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, b, m;
    cin >> a >> b >> m;
    cout << fastpow(a, b, m) << "\n";

    return 0;
}
