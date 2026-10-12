/*
============================================================
✅ Solution 6: Memotong Batang Bambu (Minimum Cost to Cut a Stick)
============================================================
Approach: Coordinate Sort + Range DP
Complexity: Time O(C^3) | Space O(C^2) di mana C <= 100
Key Insight:
1. Tambahkan titik koordinat 0 (ujung kiri batang) dan L (ujung kanan batang)
   ke dalam array titik potong `cuts`.
2. Urutkan array sehingga titik-titik potong berbaris secara monoton:
   A = [0, c_1, c_2, ..., c_C, L].
   Ukuran total array adalah M = C + 2.

3. Sekarang masalah menjadi: berapa biaya minimum memotong seluruh titik potong
   di antara indeks l dan indeks r?
   Definisikan `dp[l][r]` sebagai biaya minimum tersebut.

4. Ketika kita memilih titik k (l < k < r) sebagai titik potong PERTAMA pada segmen (l, r):
   - Segmen saat ini membentang dari posisi koordinat A[l] sampai A[r].
   - Biaya pemotongan segmen ini adalah panjangnya: (A[r] - A[l]).
   - Segmen terbelah menjadi sub-segmen kiri (l, k) dan sub-segmen kanan (k, r).
   - Biaya masing-masing sub-segmen adalah dp[l][k] dan dp[k][r].

Transisi:
dp[l][r] = min_{l < k < r} (dp[l][k] + dp[k][r]) + (A[r] - A[l])

Basis: dp[l][l + 1] = 0 (tidak ada titik potong di antara dua titik bersebelahan).
Jawaban akhir: dp[0][M - 1].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, c;
    if (!(cin >> L >> c)) return 0;

    vector<int> cuts(c);
    for (int i = 0; i < c; i++) {
        cin >> cuts[i];
    }

    // Bentuk array koordinat terurut termasuk 0 dan L
    vector<ll> A;
    A.push_back(0);
    for (int x : cuts) A.push_back(x);
    A.push_back(L);
    sort(A.begin(), A.end());

    int m = A.size();
    vector<vector<ll>> dp(m, vector<ll>(m, 0));

    // len adalah selisih indeks (r - l)
    for (int len = 2; len < m; len++) {
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INF;

            ll seg_len = A[r] - A[l];

            for (int k = l + 1; k < r; k++) {
                ll cost = dp[l][k] + dp[k][r] + seg_len;
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }

    cout << dp[0][m - 1] << "\n";

    return 0;
}
