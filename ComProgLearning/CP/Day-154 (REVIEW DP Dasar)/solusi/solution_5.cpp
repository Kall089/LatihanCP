/*
============================================================
✅ Solution 5: Pemotongan Bambu Biaya Minimum (Interval / Range DP)
============================================================
Approach: Range Dynamic Programming O(M^3)
Complexity: Time O(M^3) | Space O(M^2)
Key Insight:
1. Reduksi Batas:
   Alih-alih memikirkan panjang L yang besar (10^6), perhatikan bahwa yang penting hanyalah
   M titik potong. Tambahkan 0 di awal dan L di akhir array:
   A = {0, cuts_sorted[0], ..., cuts_sorted[M-1], L}.
   Banyak titik menjadi K = M + 2 <= 102.

2. State & Transisi Interval DP:
   dp[i][j] = biaya minimum untuk memotong semua titik di antara indeks i dan j (dari koordinat A[i] ke A[j]).
   Jika j == i + 1: tidak ada titik potong di antara A[i] dan A[j], biaya = 0.
   Jika j > i + 1:
     Kita harus memilih titik k pertama (i < k < j) yang dipotong.
     Biaya memotong di k adalah panjang segmen saat ini, yaitu (A[j] - A[i]).
     Setelah dipotong di k, segmen terbelah menjadi submasalah [i, k] dan [k, j].
     Maka: dp[i][j] = min_{i < k < j} (dp[i][k] + dp[k][j]) + (A[j] - A[i]).

3. Urutan Komputasi:
   Loop terluar harus berdasarkan panjang interval len = 2, 3, ..., K - 1.
   Jawaban akhir berada di dp[0][K - 1].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll L;
    int m;
    if (!(cin >> L >> m)) return 0;

    vector<ll> cuts(m);
    for (int i = 0; i < m; i++) {
        cin >> cuts[i];
    }

    cuts.push_back(0);
    cuts.push_back(L);
    sort(cuts.begin(), cuts.end());

    int k = cuts.size(); // k = m + 2

    // dp[i][j]: biaya minimum memotong seluruh titik antara indeks i dan j
    vector<vector<ll>> dp(k, vector<ll>(k, 0));

    for (int len = 2; len < k; len++) {
        for (int i = 0; i + len < k; i++) {
            int j = i + len;
            ll min_cost = INF;

            for (int p = i + 1; p < j; p++) {
                min_cost = min(min_cost, dp[i][p] + dp[p][j]);
            }

            dp[i][j] = min_cost + (cuts[j] - cuts[i]);
        }
    }

    cout << dp[0][k - 1] << "\n";

    return 0;
}
