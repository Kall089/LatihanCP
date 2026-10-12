/*
============================================================
✅ Solution 2: Daftar Keping Terkecil (Coin Change Reconstruction)
============================================================
Approach: Unbounded Coin Change DP + Greedy Lexicographical Reconstruction
Complexity: Time O(N * X) | Space O(X + N)
Key Insight:
1. Urutkan semua denominasi keping koin secara menaik di awal: c_1 < c_2 < ... < c_N.
2. Tabulasi DP:
   dp[s] = jumlah keping minimum untuk membentuk nominal tepat s.
   Basis: dp[0] = 0, dp[s] = INF untuk s > 0.
   Untuk setiap s dari 1 sampai X:
     Untuk setiap koin v:
       Jika v <= s dan dp[s - v] != INF:
         dp[s] = min(dp[s], dp[s - v] + 1).

3. Penelusuran Rekonstruksi Leksikografis:
   Karena urutan output bebas dan kita ingin susunan leksikografis terkecil,
   kita harus memilih nilai keping PERTAMA sekecil mungkin, lalu nilai kedua sekecil mungkin, dst.
   Saat berada pada sisa nominal s:
   Iterasi koin v secara menaik:
   Jika v <= s dan dp[s] == dp[s - v] + 1:
     Koin v ini DIJAMIN berada dalam solusi optimal dan merupakan keping terkecil
     yang valid!
     Cetak v, lalu update s = s - v.
     Ulangi sampai s = 0.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // Urutkan nilai keping menaik
    sort(c.begin(), c.end());

    // Tabulasi DP
    vector<int> dp(x + 1, INF);
    dp[0] = 0;

    for (int s = 1; s <= x; s++) {
        for (int v : c) {
            if (v <= s && dp[s - v] != INF) {
                dp[s] = min(dp[s], dp[s - v] + 1);
            }
        }
    }

    if (dp[x] == INF) {
        cout << -1 << "\n";
        return 0;
    }

    cout << dp[x] << "\n";

    if (x == 0) {
        cout << "EMPTY\n";
        return 0;
    }

    // Rekonstruksi leksikografis
    vector<int> result;
    int cur = x;
    while (cur > 0) {
        for (int v : c) {
            if (v <= cur && dp[cur] == dp[cur - v] + 1) {
                result.push_back(v);
                cur -= v;
                break;
            }
        }
    }

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << (i + 1 == result.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
