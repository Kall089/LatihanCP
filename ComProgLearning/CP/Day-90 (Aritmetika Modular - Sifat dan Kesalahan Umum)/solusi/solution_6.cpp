/*
 * Day 22 — Aritmatika Modular
 * File  : solution_6.cpp
 * Topik : Perkalian Modular dengan Modulus Besar — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: dua metode, keduanya menghindari overflow 64-bit
 *
 * MASALAH:
 *   A, B < M ≤ 10^18. Maka A × B bisa mencapai ~10^36.
 *   long long hanya sampai ~9.22 × 10^18 → overflow (undefined behavior).
 *
 * METODE 1 — __int128 (GCC/Clang extension)
 *   Tipe 128-bit menampung sampai ~1.7 × 10^38 → cukup untuk 10^36.
 *     return (__int128)a * b % m;
 *   Cast satu operand sudah cukup — operand lain di-promote otomatis.
 *   Hasil akhir < m ≤ 10^18 → aman di-cast balik ke long long.
 *   Kecepatan: praktis O(1), instruksi hardware.
 *
 * METODE 2 — Binary multiplication (portable, tanpa __int128)
 *   Analog binary exponentiation, tapi perkalian → penjumlahan berulang:
 *     A × B = A×(b0·2^0 + b1·2^1 + ...) = jumlah dari A·2^k untuk bit menyala
 *
 *     res = 0
 *     while b > 0:
 *         if (b & 1) res = (res + a) % m
 *         a = (a + a) % m          ← penjumlahan, bukan perkalian → tidak overflow
 *         b >>= 1
 *
 *   Aman karena res, a < m ≤ 10^18 → res + a < 2×10^18 < 9.22×10^18 ✓
 *   Kompleksitas: O(log B) ≈ 60 iterasi.
 *
 * Verifikasi sample 1:
 *   (2, 3, 10^9+7) = 6                                            ✓
 *   (M-1, M-1, M) dengan M = 999999999999999999:
 *     (M-1) ≡ -1 (mod M) → (-1)×(-1) = 1                          ✓
 *   (0, 12345, ...) = 0                                           ✓
 *
 * Verifikasi sample 2:
 *   999999999 × 999999999 = 999999998000000001
 *   mod 10^18 = 999999998000000001 - 999999998×10^9...
 *     karena 999999998000000001 < 10^18? Tidak: 10^18 = 1000000000000000000,
 *     dan 999999998000000001 < 10^18 ✓ → hasil = 999999998000000001
 *   (5, 5, 8) = 25 % 8 = 1                                        ✓
 *
 * Complexity: Metode 1 O(1), Metode 2 O(log B). Space O(1).
 *
 * Edge cases:
 *   - A = 0 atau B = 0 → hasil 0
 *   - M = 1            → hasil 0
 *   - A = B = M-1      → hasil 1 (trik verifikasi cepat: (-1)² = 1)
 *   - __int128 tidak bisa langsung di-cout → cast ke long long
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// METODE 1: pakai tipe 128-bit
ll mulmod128(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

// METODE 2: binary multiplication — portable, tanpa __int128
ll mulmodBinary(ll a, ll b, ll m) {
    ll res = 0;
    a %= m;
    if (a < 0) a += m;
    while (b > 0) {
        if (b & 1) {
            res += a;
            if (res >= m) res -= m;     // lebih cepat dari % m
        }
        a += a;                          // a = 2a
        if (a >= m) a -= m;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        ll a, b, m;
        cin >> a >> b >> m;

        ll r1 = mulmod128(a, b, m);
        ll r2 = mulmodBinary(a, b, m);

        // Kedua metode harus memberi hasil identik
        assert(r1 == r2);

        cout << r1 << "\n";
    }

    return 0;
}
