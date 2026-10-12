/*
============================================================
✅ Solution 4: Panjang LCS Dua Baris Bergantian (LCS Length O(min(N, M)) Space)
============================================================
Approach: 2-Row Rolling Array DP
Complexity: Time O(|S| * |T|) | Space O(min(|S|, |T|))
Key Insight:
1. Memori DP 2D Biasa:
   dp[5001][5001] int = ~100.04 MB -> Memory Limit Exceeded (batas 64 MB).
   Namun perhatikan rekurens LCS:
   dp[i][j] hanya membaca:
   - dp[i - 1][j - 1] (diagonal atas-kiri)
   - dp[i - 1][j]     (atas)
   - dp[i][j - 1]     (kiri pada baris yang sama)
   Artinya, kita HANYA membutuhkan baris i - 1 dan baris i!

2. Pola 2 Baris:
   vector<int> prev(M + 1, 0);
   vector<int> cur(M + 1, 0);
   Untuk setiap karakter s[i-1]:
     cur[0] = 0;
     Untuk setiap j dari 1 s.d. M:
       cur[j] = (s[i-1] == t[j-1] ? prev[j-1] + 1 : max(prev[j], cur[j-1]));
     prev.swap(cur);

3. Optimasi Dimensi:
   Dengan menukar string jika |T| > |S|, kita memastikan M <= 5000.
   Memori yang dialokasikan hanya 2 * 5001 * 4 byte ~ 40 KB!
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // Pastikan t adalah string yang lebih pendek
    if (t.size() > s.size()) {
        swap(s, t);
    }

    int n = s.size();
    int m = t.size();

    vector<int> prev(m + 1, 0);
    vector<int> cur(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                cur[j] = prev[j - 1] + 1;
            } else {
                cur[j] = max(prev[j], cur[j - 1]);
            }
        }
        prev.swap(cur);
    }

    cout << prev[m] << "\n";

    return 0;
}
