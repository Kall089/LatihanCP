/*
 * Day 20 — Sliding Window
 * File  : solution_4.cpp
 * Topik : Longest Substring with at most K Distinct — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Variable-Size Sliding Window + Frequency Map
 *
 * Idea:
 *   - freq[c] = jumlah occurrence c dalam window saat ini.
 *   - freq.size() = jumlah karakter DISTINCT dalam window.
 *   - Expand R: freq[s[R]]++
 *   - WHILE freq.size() > K (terlalu banyak distinct):
 *       freq[s[L]]--
 *       jika 0, ERASE dari map (PENTING!)
 *       L++
 *   - Update ans = max(ans, R - L + 1)
 *
 * ⚠️ KENAPA harus erase saat freq jadi 0?
 *   Jika tidak erase, freq.size() akan terus menghitung karakter
 *   yang sebenarnya sudah keluar dari window.
 *
 * Verifikasi sample 1: s="araaci", K=2
 *   R=0: freq{a:1}, size=1, ans=1
 *   R=1: freq{a:1,r:1}, size=2, ans=2
 *   R=2: freq{a:2,r:1}, size=2, ans=3
 *   R=3: freq{a:3,r:1}, size=2, ans=4
 *   R=4: freq{a:3,r:1,c:1}, size=3>2 → shrink:
 *        L=0 'a' freq{a:2,r:1,c:1}, size=3>2
 *        L=1 'r' freq{a:2,c:1}, size=2 ✓, L=2
 *        ans=max(4, 4-2+1=3)=4
 *   R=5: freq{a:2,c:1,i:1}, size=3>2 → shrink:
 *        L=2 'a' freq{a:1,c:1,i:1}, size=3>2
 *        L=3 'a' freq{c:1,i:1}, size=2 ✓, L=4
 *        ans=max(4, 5-4+1=2)=4
 *   Output: 4 ✓
 *
 * Complexity: O(n) time amortized, O(K) space (max K key di map)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int K;
    cin >> s >> K;
    int n = s.size();

    unordered_map<char, int> freq;
    int L = 0, ans = 0;

    for (int R = 0; R < n; R++) {
        freq[s[R]]++;                          // expand: tambah char baru

        while ((int)freq.size() > K) {         // terlalu banyak distinct
            freq[s[L]]--;
            if (freq[s[L]] == 0)
                freq.erase(s[L]);              // wajib erase!
            L++;
        }

        ans = max(ans, R - L + 1);
    }

    cout << ans << "\n";
    return 0;
}
