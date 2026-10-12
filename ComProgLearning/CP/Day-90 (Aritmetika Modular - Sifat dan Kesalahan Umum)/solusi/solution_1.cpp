/*
 * Day 22 — Aritmatika Modular
 * File  : solution_1.cpp
 * Topik : Jumlah & Hasil Kali Array Modulo M — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Properti distributif modulo
 *
 * Idea:
 *   (a + b) % m = ((a%m) + (b%m)) % m
 *   (a × b) % m = ((a%m) × (b%m)) % m
 *   → boleh ambil mod di SETIAP langkah akumulasi, hasil tetap benar
 *
 * Kunci overflow-safety:
 *   sum  : sum < m ≤ 10^9, A[i] ≤ 10^9  → sum + A[i] < 2×10^9, muat long long
 *   prod : prod < m ≤ 10^9, A[i]%m < 10^9 → hasil kali < 10^18, muat long long
 *          (tapi TIDAK muat int — inilah kenapa harus long long)
 *
 * Verifikasi sample:
 *   Sample 1: A=[1,2,3,4,5], M=10^9+7
 *     sum  = 15 (< M, tidak berubah)          → 15  ✓
 *     prod = 120 (< M)                        → 120 ✓
 *
 *   Sample 2: A=[10,20,30], M=7
 *     sum:  0+10=10%7=3; 3+20=23%7=2; 2+30=32%7=4  → 4  ✓
 *     prod: 1×10=10%7=3; 3×20=60%7=4; 4×30=120%7=1 → 1  ✓
 *     (cek: 60%7=4 ✓, 6000%7=1 ✓)
 *
 *   Sample 3: A=[10^9, 999999999, 5, 3], M=100
 *     sum  = 2000000007 % 100 = 7             → 7  ✓
 *     prod: 10^9 % 100 = 0 → semua sisanya 0  → 0  ✓
 *
 * Complexity: O(n) time, O(1) extra space
 *
 * Edge cases:
 *   - Ada A[i] = 0 → product jadi 0 (benar)
 *   - M = 1 → semua hasil 0
 *   - N = 1 → sum = prod = A[0] % M
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;

    ll sum = 0;
    ll prod = 1 % m;   // penting: kalau m == 1, prod harus mulai dari 0

    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        x %= m;                 // kecilkan dulu

        sum = (sum + x) % m;    // properti penjumlahan
        prod = prod * x % m;    // properti perkalian (long long → aman)
    }

    cout << sum << "\n";
    cout << prod << "\n";
    return 0;
}
