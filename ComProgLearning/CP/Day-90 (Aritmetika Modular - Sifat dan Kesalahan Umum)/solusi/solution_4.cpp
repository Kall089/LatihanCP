/*
 * Day 22 — Aritmatika Modular
 * File  : solution_4.cpp
 * Topik : Modulo Bilangan Raksasa (Horner) — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Horner's Rule + properti distributif modulo
 *
 * Idea:
 *   Sebuah bilangan desimal d0 d1 d2 ... dk-1 bernilai
 *     N = ((...((d0)*10 + d1)*10 + d2)*10 + ...) + dk-1
 *
 *   Karena (a*10 + d) % m = ((a%m)*10 + d) % m, kita boleh mengambil mod
 *   setiap kali memproses satu digit. Nilai antara tidak pernah membesar.
 *
 * Bukti tidak overflow:
 *   res selalu < m ≤ 10^9
 *   res*10 + 9 < 10^10  ≪  9.2×10^18 (batas long long) ✓
 *
 * Trace "12345" mod 7:
 *   digit | res sebelum | res*10 + d | % 7
 *     1   |      0      |     1      |  1
 *     2   |      1      |    12      |  5
 *     3   |      5      |    53      |  4
 *     4   |      4      |    44      |  2
 *     5   |      2      |    25      |  4  ← hasil ✓
 *   Cek: 12345 = 1763×7 + 4 ✓
 *
 * Verifikasi sample 2: 10^20 mod (10^9+7)
 *   10^20 = (10^9)^2 × 100. Karena 10^9 ≡ -7 (mod 10^9+7):
 *   ≡ 49 × 100 = 4900 ✓ (output program: 4900)
 *
 * Verifikasi sample 3: 987654321987654321 mod (10^9+7) = 74074116 ✓
 *
 * Complexity: O(panjang N) time, O(panjang N) space untuk menyimpan string
 *
 * Edge cases:
 *   - N = "0"     → hasil 0
 *   - M = 1       → hasil selalu 0
 *   - N 100.000 digit → tetap O(n), cepat
 *   - Leading zero pada input → tidak mempengaruhi hasil
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll bigMod(const string& s, ll m) {
    ll res = 0;
    for (char c : s) {
        res = (res * 10 + (c - '0')) % m;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n;
    ll m;
    cin >> n >> m;

    cout << bigMod(n, m) << "\n";
    return 0;
}
