/*
 * Day 20 — Sliding Window
 * File  : solution_6.cpp
 * Topik : Longest Substring Without Repeating Characters — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Variable-Size Window + Last-Seen Map (versi optimal)
 *
 * Idea:
 *   last[c] = index TERAKHIR karakter c muncul.
 *   Saat scan R:
 *     - Jika last.count(s[R]) dan last[s[R]] >= L:
 *         L = last[s[R]] + 1   (lompat L ke setelah duplikat lama)
 *     - last[s[R]] = R
 *     - ans = max(ans, R - L + 1)
 *
 * Versi alternatif (lebih intuitif tapi sedikit lebih lambat):
 *   Pakai freq[c] dan shrink WHILE freq[s[R]] > 1.
 *
 * Verifikasi sample 4: s="dvdf"
 *   R=0 'd': last={}, no jump; last[d]=0; ans=1; L=0
 *   R=1 'v': last={d:0}, no v; last[v]=1; ans=2; L=0
 *   R=2 'd': last[d]=0 >= L=0 → L = 0+1 = 1; last[d]=2; ans=max(2,2)=2
 *   R=3 'f': no jump; last[f]=3; ans=max(2, 3-1+1=3)=3 ✓
 *
 *   ⚠️ Bug umum: jika tidak cek `last[s[R]] >= L`, kita akan jump
 *      L mundur (yang salah) saat duplikat sudah keluar dari window.
 *      Misal "abba" di R=3: last[a]=0, tapi L sudah = 2.
 *      Tanpa cek: L=0+1=1 (SALAH, harus tetap L=2).
 *      Dengan cek: 0 < 2, no jump → L=2 (BENAR).
 *
 * Verifikasi sample 1: s="abcabcbb"
 *   R=0 a: ans=1; L=0
 *   R=1 b: ans=2; L=0
 *   R=2 c: ans=3; L=0
 *   R=3 a: last[a]=0 >= 0 → L=1; ans=max(3, 3-1+1=3)=3
 *   R=4 b: last[b]=1 >= 1 → L=2; ans=max(3, 4-2+1=3)=3
 *   R=5 c: last[c]=2 >= 2 → L=3; ans=max(3, 5-3+1=3)=3
 *   R=6 b: last[b]=4 >= 3 → L=5; ans=max(3, 6-5+1=2)=3
 *   R=7 b: last[b]=6 >= 5 → L=7; ans=max(3, 7-7+1=1)=3
 *   Output: 3 ✓
 *
 * Complexity: O(n) time, O(min(n, |alphabet|)) space
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    unordered_map<char, int> last;   // char → last seen index
    int L = 0, ans = 0;

    for (int R = 0; R < n; R++) {
        // Jika s[R] sudah dilihat DAN posisinya masih di dalam window
        if (last.count(s[R]) && last[s[R]] >= L) {
            L = last[s[R]] + 1;       // lompat L ke setelah duplikat
        }
        last[s[R]] = R;
        ans = max(ans, R - L + 1);
    }

    cout << ans << "\n";
    return 0;
}
