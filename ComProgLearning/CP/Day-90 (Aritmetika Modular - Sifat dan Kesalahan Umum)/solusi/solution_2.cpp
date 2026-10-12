/*
 * Day 22 — Aritmatika Modular
 * File  : solution_2.cpp
 * Topik : Modulo Bilangan Negatif — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Normalisasi ((a % m) + m) % m
 *
 * Idea:
 *   C++ memakai truncation toward zero, sehingga tanda hasil % mengikuti
 *   tanda operand KIRI:
 *       (-7) % 3 = -1     (matematis seharusnya 2)
 *
 *   Perbaikan 3 langkah:
 *     1. a % m       → hasil di rentang (-m, m)
 *     2. + m         → hasil di rentang (0, 2m)
 *     3. % m         → hasil di rentang [0, m)
 *
 * Kenapa bukan (a + m) % m saja?
 *   Kalau a = -10^18 dan m = 7, maka a + m masih sangat negatif.
 *   Langkah % m HARUS dilakukan lebih dulu untuk menyempitkan rentang.
 *
 * Verifikasi sample 1:
 *   (-7, 3):    -7%3 = -1  → (-1+3)%3 = 2                    ✓
 *   (-1, 5):    -1%5 = -1  → (-1+5)%5 = 4                    ✓
 *   (17, 8):    17%8 =  1  → (1+8)%8  = 1                    ✓
 *   (-10, 5):  -10%5 =  0  → (0+5)%5  = 0                    ✓
 *   (-1000000000007, 10): -1000000000007%10 = -7 → (-7+10)%10 = 3  ✓
 *
 * Verifikasi sample 2:
 *   (0,7)=0 ✓   (-1,7): -1%7=-1 → 6 ✓   (8,7): 8%7=1 → 1 ✓
 *
 * Complexity: O(1) per query, O(Q) total. Space O(1).
 *
 * Edge cases:
 *   - a = 0 → hasil 0
 *   - m = 1 → hasil selalu 0
 *   - a kelipatan m (positif atau negatif) → hasil 0, bukan m
 *   - a = -10^18 (batas bawah) → tetap aman karena %m dilakukan pertama
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Normalisasi ke [0, m-1] — definisi modulo matematis
ll norm(ll a, ll m) {
    return ((a % m) + m) % m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;

    while (q--) {
        ll a, m;
        cin >> a >> m;
        cout << norm(a, m) << "\n";
    }

    return 0;
}
