/*
 * Day 22 — Aritmatika Modular
 * File  : solution_3.cpp
 * Topik : Binary Exponentiation — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Binary (Fast) Exponentiation
 *
 * Idea:
 *   Tulis eksponen dalam biner. A^13 = A^(1101₂) = A^8 × A^4 × A^1.
 *   Kita kuadratkan base tiap iterasi (A → A² → A⁴ → A⁸ ...) dan
 *   mengalikannya ke hasil hanya ketika bit yang bersesuaian menyala.
 *
 *   result = 1
 *   while exp > 0:
 *       if (exp & 1) result = result * base % m
 *       base = base * base % m
 *       exp >>= 1
 *
 * Trace 3^13 mod 1000:
 *   iter | exp  | bit | result           | base
 *     1  | 1101 |  1  | 1×3 = 3          | 9
 *     2  |  110 |  0  | 3                | 81
 *     3  |   11 |  1  | 3×81 = 243       | 6561%1000 = 561
 *     4  |    1 |  1  | 243×561 = 136323 → %1000 = 323 | 721
 *   hasil = 323 ✓  (3^13 = 1594323, 1594323 % 1000 = 323)
 *
 * Verifikasi sample 1 lainnya:
 *   5^0 mod 10^9+7 = 1                    ✓
 *   2^10 mod 1024 = 1024 % 1024 = 0       ✓
 *   7^100 mod 1 = 0 (semua mod 1 = 0)     ✓
 *
 * Verifikasi sample 2:
 *   2^100 mod 10^9+7 = 976371285          ✓
 *   10^18 mod 10^9+7 = 49                 ✓ (karena 10^18 = (10^9)^2 dan
 *                                            10^9 ≡ -7 → (-7)^2 = 49)
 *   999999999^2 mod 10^9+7: 999999999 ≡ -8 → 64 ... periksa: 10^9+7-999999999=8,
 *   jadi 999999999 ≡ -8 (mod 10^9+7) → (-8)^2 = 64. Output = 64.
 *
 * Complexity: O(log B) per query → O(T log B) total. Space O(1).
 *
 * Edge cases:
 *   - B = 0        → hasil 1 (konvensi A^0 = 1); jika M = 1 hasil 0
 *   - A = 0, B > 0 → hasil 0
 *   - M = 1        → hasil selalu 0; ditangani otomatis oleh `result = 1 % m`
 *   - A ≥ M        → base %= m di awal
 *
 * Alternative approaches:
 *   - Naif loop B kali: O(B) → TLE untuk B = 10^18
 *   - pow() dari <cmath>: double, kehilangan presisi → SALAH
 *   - Rekursif: O(log B) juga, tapi pakai stack O(log B)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modpow(ll base, ll exp, ll m) {
    ll result = 1 % m;      // 1%m menangani kasus m == 1 → result = 0
    base %= m;
    if (base < 0) base += m;

    while (exp > 0) {
        if (exp & 1)                    // bit menyala → kalikan ke hasil
            result = result * base % m;
        base = base * base % m;         // kuadratkan base
        exp >>= 1;                      // geser ke bit berikutnya
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        ll a, b, m;
        cin >> a >> b >> m;
        cout << modpow(a, b, m) << "\n";
    }

    return 0;
}
