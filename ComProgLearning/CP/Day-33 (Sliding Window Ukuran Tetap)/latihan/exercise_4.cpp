/*
 * Day 20 — Sliding Window
 * File  : exercise_4.cpp
 * Topik : Longest Substring with at most K Distinct Characters
 * -----------------------------------------------
 * Diberikan string s (huruf kecil saja) dan integer K.
 * Cari panjang SUBSTRING kontinu TERPANJANG yang mengandung
 * paling banyak K karakter berbeda (distinct).
 *
 * Pendekatan VARIABLE-SIZE WINDOW + FREQUENCY MAP:
 *   - Expand R: freq[s[R]]++
 *   - Shrink WHILE freq.size() > K:
 *       freq[s[L]]--
 *       jika 0, erase dari map (penting!)
 *       L++
 *   - Update ans = max(ans, R - L + 1)
 *
 * Input format  : Baris 1: string s
 *                 Baris 2: integer K
 * Output format : panjang substring terpanjang
 * Constraints   : 1 ≤ |s| ≤ 200.000
 *                 1 ≤ K ≤ 26
 *                 s hanya berisi huruf kecil 'a'..'z'
 *
 * Sample Input 1:        Sample Output 1:
 * araaci                 4
 * 2
 *
 * Sample Input 2:        Sample Output 2:
 * cbbebi                 5
 * 3
 *
 * Sample Input 3:        Sample Output 3:
 * abcdef                 1
 * 1
 *
 * NOTE Sample 1: substring "araa" panjang 4 dengan {a,r}.
 * NOTE Sample 2: substring "cbbeb" punya {c,b,e}=3 distinct, panjang 5.
 *                Atau "bbebi" {b,e,i}=3 distinct, panjang 5.
 * NOTE Sample 3: K=1 → tiap karakter unik, max length = 1.
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

    // TODO: Implementasi variable-size window + frequency map
    // Hint:
    // unordered_map<char, int> freq;
    // int L = 0, ans = 0;
    // for (int R = 0; R < n; R++) {
    //     freq[s[R]]++;
    //     while ((int)freq.size() > K) {
    //         freq[s[L]]--;
    //         if (freq[s[L]] == 0) freq.erase(s[L]);
    //         L++;
    //     }
    //     ans = max(ans, R - L + 1);
    // }
    // cout << ans;

    return 0;
}
