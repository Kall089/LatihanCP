/*
============================================================
✅ Solution 4: Rekonstruksi Subsekuens Bersama Terpanjang (LCS Reconstruction)
============================================================
Approach: 2D Dynamic Programming + Table Backtracking
Complexity: Time O(|s| * |t|) | Space O(|s| * |t|)
Key Insight:
1. Tahap Tabulasi:
   Tabel dp[i][j] menyimpan panjang LCS dari prefix s[0..i-1] dan prefix t[0..j-1].
   - Jika s[i-1] == t[j-1]:
     dp[i][j] = dp[i-1][j-1] + 1
   - Jika tidak sama:
     dp[i][j] = max(dp[i-1][j], dp[i][j-1])

2. Tahap Penelusuran Mundur (Backtracking):
   Mulai dari sudut kanan bawah: i = |s|, j = |t|.
   Selama i > 0 dan j > 0:
   - Jika s[i-1] == t[j-1]:
     Karakter ini harus dimasukkan ke dalam LCS.
     Tambahkan s[i-1] ke dalam string penampung, lalu mundur secara diagonal: i--, j--.
   - Jika berbeda:
     Bandingkan sel atas (dp[i-1][j]) dan sel kiri (dp[i][j-1]).
     Mundurlah ke sel yang nilainya lebih besar (atau sama):
     Jika dp[i-1][j] >= dp[i][j-1]: i--.
     Jika tidak: j--.

3. Balikkan (reverse) string penampung karena karakter dikumpulkan dari belakang ke depan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    int n = s.size();
    int m = t.size();

    // dp[i][j]: panjang LCS dari s[0..i-1] dan t[0..j-1]
    // Ukuran 3001 x 3001 int ~ 36 MB (sangat aman dalam 256 MB)
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Rekonstruksi mundur dari (n, m)
    string lcs_str = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            lcs_str.push_back(s[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs_str.begin(), lcs_str.end());
    cout << lcs_str << "\n";

    return 0;
}
