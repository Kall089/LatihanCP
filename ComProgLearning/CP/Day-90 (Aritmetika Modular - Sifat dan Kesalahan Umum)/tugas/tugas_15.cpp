/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_15.cpp
 * Topik : Periodisitas Modular — Hitung X dengan X² ≡ 1 (mod M)
 * Tingkat: Hard ★★★★★
 * -----------------------------------------------
 * Diberikan N dan M. Hitung banyaknya bilangan bulat X dalam rentang
 * [1, N] yang memenuhi:
 *
 *     X² ≡ 1  (mod M)
 *
 * N bisa mencapai 10^18, jadi mengecek satu per satu jelas TLE.
 *
 * IDE KUNCI — PERIODISITAS:
 *   Apakah X memenuhi kondisi HANYA bergantung pada X mod M
 *   (karena X ≡ Y (mod M) ⟹ X² ≡ Y² (mod M)).
 *
 *   Jadi pola "memenuhi / tidak" berulang dengan periode M.
 *
 *   Langkah:
 *     1. Cari himpunan residu baik: G = { r ∈ [0, M-1] : r² ≡ 1 (mod M) }
 *        → O(M), hitung r*r % M (cast long long!)
 *     2. Rentang [1, N] berisi floor(N/M) blok penuh, masing-masing
 *        menyumbang |G| bilangan
 *     3. Sisa rem = N mod M → cek residu 1, 2, ..., rem satu per satu
 *
 *   Kompleksitas: O(M), bukan O(N).
 *
 * ⚠️ r*r bisa mencapai (2×10^5)² = 4×10^10 → WAJIB long long.
 * ⚠️ Hati-hati batas blok terakhir: apakah residu rem termasuk atau tidak.
 *
 * Input format  : Baris 1: N dan M
 * Output format : satu bilangan — banyaknya X di [1, N] dengan X² ≡ 1 (mod M)
 * Constraints   : 1 ≤ N ≤ 10^18
 *                 1 ≤ M ≤ 1.000.000
 *
 * Sample Input 1:        Sample Output 1:
 * 10 8                   5
 *
 * Sample Input 2:        Sample Output 2:
 * 100 5                  40
 *
 * Sample Input 3:                    Sample Output 3:
 * 1000000000000000000 12             333333333333333333
 *
 * Sample Input 4:        Sample Output 4:
 * 7 3                    5
 *
 * NOTE Sample 1: M=8, residu baik = {1,3,5,7} (4 buah).
 *      X di [1,10] yang memenuhi: 1, 3, 5, 7, 9 → 5 bilangan.
 *      (9 ≡ 1 mod 8, dan 1² ≡ 1 ✓)
 * NOTE Sample 2: M=5, residu baik = {1,4} (2 buah).
 *      [1,100] = 20 blok penuh × 2 = 40.
 * NOTE Sample 4: M=3, residu baik = {1,2}. X di [1,7]: 1,2,4,5,7 → 5.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan — cari residu baik O(M), lalu hitung blok penuh + sisa

    return 0;
}
