/*
============================================================
✅ Solution 3: Potongan Sandi Palindrom (Palindrome Partitioning II)
============================================================
Approach: Two-Stage DP (Range DP Precomputation + 1D Linear DP)
Complexity: Time O(|S|^2) | Space O(|S|^2)
Key Insight:
Memotong string menjadi seminimal mungkin palindrom dapat dipecah menjadi dua tahap:

Tahap 1: Tabel Palindrom Range DP
isPal[l][r] menyatakan apakah substring S[l..r] adalah palindrom.
- Karakter tunggal (len = 1) selalu palindrom.
- Dua karakter (len = 2) palindrom jika S[l] == S[r].
- Panjang >= 3: palindrom jika S[l] == S[r] DAN bagian dalamnya isPal[l+1][r-1] == true.
Tabel ini dihitung dalam O(N^2).

Tahap 2: DP 1D Linear Menghitung Jumlah Bagian
Definisikan dp[r] = jumlah bagian palindrom minimum untuk prefix r karakter pertama (S[0..r-1]).
- dp[0] = 0 (string kosong butuh 0 bagian).
- Untuk setiap r dari 1 sampai n:
  Setiap kemungkinan bagian terakhir adalah S[l..r-1] untuk suatu l < r.
  Jika isPal[l][r-1] == true:
    dp[r] = min(dp[r], dp[l] + 1).

Hasil akhir:
Jumlah potongan (cuts) = (jumlah bagian palindrom) - 1 = dp[n] - 1.
Jika seluruh string sudah palindrom, dp[n] = 1, sehingga 1 - 1 = 0 potongan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.size();

    // Tahap 1: Tabel Palindrom Range DP
    vector<vector<bool>> is_pal(n, vector<bool>(n, false));

    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                if (len <= 2) {
                    is_pal[l][r] = true;
                } else {
                    is_pal[l][r] = is_pal[l + 1][r - 1];
                }
            }
        }
    }

    // Tahap 2: DP 1D untuk Menghitung Jumlah Bagian Minimum
    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;

    for (int r = 1; r <= n; r++) {
        for (int l = 0; l < r; l++) {
            if (is_pal[l][r - 1]) {
                dp[r] = min(dp[r], dp[l] + 1);
            }
        }
    }

    cout << dp[n] - 1 << "\n";

    return 0;
}
