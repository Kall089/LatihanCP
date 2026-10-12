/*
 * Day 11 — Recursion Dasar
 * File  : exercise_4.cpp
 * Topik : Fast Power (a^b mod m)
 * -----------------------------------------------
 * Hitung (a^b) mod m menggunakan Fast Power rekursif.
 * Kompleksitas target: O(log b) — bukan O(b).
 *
 * Ide:
 *   a^b = (a^(b/2))^2          jika b genap
 *   a^b = a * (a^(b/2))^2      jika b ganjil
 *   a^0 = 1                    base case
 *
 * Input format  : Tiga bilangan a b m dalam satu baris
 * Output format : (a^b) mod m
 * Constraints   : 1 ≤ a,b ≤ 10^9, 1 ≤ m ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 2 10 1000000007      1024
 *
 * Sample Input 2:      Sample Output 2:
 * 3 0 100              1
 *
 * Sample Input 3:      Sample Output 3:
 * 5 3 13               8
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Implementasikan fast power O(log exp)
// BASE CASE: exp == 0 → return 1
// Jika exp genap: hitung half = fastpow(base, exp/2, mod)
//                 return (half * half) % mod
// Jika exp ganjil: return (base%mod * fastpow(base, exp-1, mod)) % mod
ll fastpow(ll base, ll exp, ll mod) {
    // TODO: isi implementasi di sini
    return 0; // ganti ini
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, b, m;
    cin >> a >> b >> m;

    cout << fastpow(a, b, m) << "\n";

    return 0;
}
