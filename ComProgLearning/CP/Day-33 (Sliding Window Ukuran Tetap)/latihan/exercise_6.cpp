/*
 * Day 20 — Sliding Window
 * File  : exercise_6.cpp
 * Topik : Longest Substring Without Repeating Characters
 * -----------------------------------------------
 * Diberikan string s. Cari panjang SUBSTRING kontinu TERPANJANG
 * yang semua karakternya UNIK (tidak ada duplikat).
 *
 * Pendekatan VARIABLE-SIZE WINDOW + LAST-SEEN MAP:
 *   - Maintain unordered_map<char, int> last (karakter → index terakhir)
 *   - Expand R:
 *       jika s[R] sudah pernah dilihat dan posisi >= L:
 *           L = last[s[R]] + 1   (lompat L ke setelah duplikat)
 *       last[s[R]] = R
 *   - Update ans = max(ans, R - L + 1)
 *
 * Alternatif: pakai freq[char] dan shrink while freq[s[R]] > 1.
 *
 * Input format  : Satu baris berisi string s (huruf kecil & angka)
 * Output format : panjang substring terpanjang tanpa duplikat
 * Constraints   : 1 ≤ |s| ≤ 200.000
 *                 s berisi karakter ASCII printable (32-126)
 *
 * Sample Input 1:        Sample Output 1:
 * abcabcbb              3
 *
 * Sample Input 2:        Sample Output 2:
 * bbbbb                 1
 *
 * Sample Input 3:        Sample Output 3:
 * pwwkew                3
 *
 * Sample Input 4:        Sample Output 4:
 * dvdf                  3
 *
 * NOTE Sample 1: "abc" panjang 3.
 * NOTE Sample 3: "wke" atau "kew" panjang 3.
 * NOTE Sample 4: "vdf" panjang 3 (penting: L harus lompat dengan benar).
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    // TODO: Implementasi variable-size window dengan last-seen map
    // Hint (versi optimal):
    // unordered_map<char, int> last;
    // int L = 0, ans = 0;
    // for (int R = 0; R < n; R++) {
    //     if (last.count(s[R]) && last[s[R]] >= L) {
    //         L = last[s[R]] + 1;   // lompat L
    //     }
    //     last[s[R]] = R;
    //     ans = max(ans, R - L + 1);
    // }
    // cout << ans;
    //
    // ALTERNATIF dengan frequency:
    // unordered_map<char, int> freq;
    // for (int R = 0; R < n; R++) {
    //     freq[s[R]]++;
    //     while (freq[s[R]] > 1) {
    //         freq[s[L]]--;
    //         L++;
    //     }
    //     ans = max(ans, R - L + 1);
    // }

    return 0;
}
