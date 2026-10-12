/*
 * Day 11 — Recursion Dasar
 * File  : solution_5.cpp
 * Topik : GCD & LCM Rekursif (Algoritma Euclidean)
 * Pendekatan: Euclidean algorithm, O(log min(a,b)) per query
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b); // Euclidean: gcd(a,b) = gcd(b, a%b)
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b; // Bagi dulu agar hindari overflow
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;
        cout << gcd(a, b) << " " << lcm(a, b) << "\n";
    }

    return 0;
}
