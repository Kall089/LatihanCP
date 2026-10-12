/*
 * Day 11 — Recursion Dasar
 * File  : exercise_5.cpp
 * Topik : GCD & LCM Rekursif (Algoritma Euclidean)
 * -----------------------------------------------
 * Untuk q pasang bilangan, hitung GCD dan LCM-nya.
 * Gunakan algoritma Euclidean rekursif.
 *
 * Teorema Euclidean:
 *   gcd(a, b) = gcd(b, a mod b)  untuk b != 0
 *   gcd(a, 0) = a                base case
 *   lcm(a, b) = a * b / gcd(a,b)
 *
 * PERHATIAN: Hitung lcm(a,b) sebagai (a/gcd(a,b))*b untuk hindari overflow!
 *
 * Input format  : Baris 1: q (jumlah query)
 *                 Baris 2..q+1: a b per baris
 * Output format : Tiap baris: gcd(a,b) lcm(a,b)
 * Constraints   : 1 ≤ q ≤ 10^4, 1 ≤ a,b ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 3                    6 36
 * 12 18                1 1000000000
 * 1 1000000000         12 60
 * 60 12
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Implementasikan GCD rekursif (Euclidean)
// gcd(a, 0) = a
// gcd(a, b) = gcd(b, a % b)
ll gcd(ll a, ll b) {
    // TODO: isi implementasi di sini
    return 0; // ganti ini
}

// TODO: Implementasikan LCM menggunakan GCD
// lcm(a, b) = a / gcd(a,b) * b  (bagi dulu untuk hindari overflow)
ll lcm(ll a, ll b) {
    // TODO: isi implementasi di sini
    return 0; // ganti ini
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
