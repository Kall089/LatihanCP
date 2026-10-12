/*
 * Day 19 — Two Pointers
 * File  : tugas_12.cpp
 * Topik : Minimum Window Substring
 * Tingkat: Hard
 * -----------------------------------------------
 * Diberikan dua string S dan T. Temukan substring terpendek dari S yang
 * mengandung SEMUA karakter dari T (termasuk duplikat). Jika tidak ada,
 * output string kosong "".
 *
 * Contoh:
 *   S = "ADOBECODEBANC", T = "ABC"
 *   Minimum window: "BANC" (panjang 4)
 *
 * Pendekatan Sliding Window (Two Pointers):
 *   - Gunakan frequency map untuk T
 *   - L = 0, R = 0: expand R ke kanan
 *   - Ketika semua karakter T sudah masuk window: coba shrink dari L
 *   - Update jawaban dengan window terkecil yang valid
 *   - Lanjutkan expand R
 *
 * Implementasi:
 *   - need[c] = jumlah karakter c yang dibutuhkan dari T
 *   - have[c] = jumlah karakter c dalam window saat ini
 *   - formed = jumlah jenis karakter yang sudah terpenuhi
 *   - required = jumlah jenis karakter unik dalam T
 *   - Window valid jika formed == required
 *
 * Input format  : Baris 1: string S
 *                 Baris 2: string T
 * Output format : Substring S terpendek yang mengandung semua karakter T,
 *                 atau "" jika tidak ada
 * Constraints   : 1 ≤ |S| ≤ 10^5
 *                 1 ≤ |T| ≤ 10^5
 *                 S dan T berisi huruf besar dan kecil
 *
 * Sample Input 1:      Sample Output 1:
 * ADOBECODEBANC        BANC
 * ABC
 *
 * Sample Input 2:      Sample Output 2:
 * a
 * aa
 *
 * Sample Input 3:      Sample Output 3:
 * a                    a
 * a
 *
 * Penjelasan Sample 1:
 *   T="ABC", perlu A,B,C masing-masing satu.
 *   Window "ADOBEC" [0..5] valid, panjang 6
 *   Window "DOBECODEBA" tidak lebih kecil
 *   Window "BANC" [9..12] valid, panjang 4 → MINIMUM ✓
 *
 * Penjelasan Sample 2:
 *   S="a", T="aa". S hanya punya satu 'a', T butuh dua. Tidak mungkin → "" ✓
 *
 * Hint:
 *   map<char,int> need, have;
 *   for (char c : T) need[c]++;
 *   int required = need.size();
 *   int formed = 0;
 *   int L = 0, minLen = INT_MAX, minL = 0;
 *   for (int R = 0; R < S.size(); R++) {
 *       have[S[R]]++;
 *       if (need.count(S[R]) && have[S[R]] == need[S[R]]) formed++;
 *       while (formed == required) {
 *           // update min window
 *           // shrink dari kiri
 *       }
 *   }
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
