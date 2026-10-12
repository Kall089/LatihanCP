/*
============================================================
✅ Solution 5: Subsekuens Bersama Terpanjang (LCS Top-Down)
============================================================
Approach: Top-Down Dynamic Programming with 2D Memoization
Complexity: Time O(|S| * |T|) | Space O(|S| * |T|)
Key Insight:
1. Rekursi Sufiks LCS:
   solve(i, j) menghitung panjang LCS dari S[i..N-1] dan T[j..M-1].
   - Jika i == N atau j == M, salah satu string sudah habis -> return 0.
   - Jika S[i] == T[j]: karakter cocok, pasti optimal mengambil karakter ini:
     1 + solve(i + 1, j + 1).
   - Jika S[i] != T[j]: karakter berbeda, coba lewatkan satu karakter dari S atau T:
     max(solve(i + 1, j), solve(i, j + 1)).

2. Memoisasi:
   memo[N + 1][M + 1] diinisialisasi dengan -1.
   Setiap pasangan indeks (i, j) hanya dihitung satu kali, sehingga waktu komputasi O(|S| * |T|).
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

    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));

    function<int(int, int)> solve = [&](int i, int j) -> int {
        // Base case: salah satu string telah habis
        if (i == n || j == m) return 0;

        // Cek memo
        if (memo[i][j] != -1) return memo[i][j];

        // Transisi
        if (s[i] == t[j]) {
            return memo[i][j] = 1 + solve(i + 1, j + 1);
        } else {
            return memo[i][j] = max(solve(i + 1, j), solve(i, j + 1));
        }
    };

    cout << solve(0, 0) << "\n";

    return 0;
}
