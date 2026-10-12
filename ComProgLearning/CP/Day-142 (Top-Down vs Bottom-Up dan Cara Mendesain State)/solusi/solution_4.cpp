/*
============================================================
✅ Solution 4: Satu Kupon di Jalur Dieng
============================================================
Approach: Dynamic Programming 2D (State Berbasis Sumber Daya Terbatas)
Complexity: Time O(N) | Space O(N)

Key Insight:
Mengapa satu dimensi dp[i] gagal?
Karena state (pos i, kupon masih utuh) memungkinkan opsi gratis di langkah berikutnya,
sedangkan state (pos i, kupon sudah terpakai) tidak mengizinkan opsi gratis.
Karena masa depannya berbeda, kedua kondisi ini TIDAK SETARA dan wajib dipisahkan dimensinya.

Definisi State:
dp[i][0] = energi minimum mencapai pos i tanpa pernah menggunakan kupon.
dp[i][1] = energi minimum mencapai pos i di mana kupon sudah pernah digunakan.

Transisi (Pull atau Push DP):
Lebih intuitif menggunakan Push DP (Forward DP):
Dari pos i, untuk setiap next_pos in {i + 1, i + 2} yang valid (< N):
1. Biaya lompatan normal: cost = |H[next_pos] - H[i]|
   - dp[next_pos][0] = min(dp[next_pos][0], dp[i][0] + cost)
   - dp[next_pos][1] = min(dp[next_pos][1], dp[i][1] + cost)
2. Gunakan kupon pada lompatan ini (hanya jika sebelumnya belum dipakai):
   - dp[next_pos][1] = min(dp[next_pos][1], dp[i][0] + 0)

Basis:
dp[0][0] = 0; dp[0][1] = 0; semua lainnya diisi INF.

Jawaban akhir:
min(dp[N - 1][0], dp[N - 1][1])

Sample 1:
Input:
4
0 9 10 100
Output:
9

Sample 2:
Input:
1
88
Output:
0

Sample 3:
Input:
2
0 1000000000
Output:
0
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    if (n <= 1) {
        cout << 0 << "\n";
        return 0;
    }

    // dp[i][0]: kupon belum dipakai
    // dp[i][1]: kupon sudah dipakai
    vector<vector<long long>> dp(n, vector<long long>(2, INF));
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 0; i < n; i++) {
        for (int next_pos : {i + 1, i + 2}) {
            if (next_pos < n) {
                long long cost = abs(h[next_pos] - h[i]);

                // 1. Lompat normal tanpa memakai kupon saat ini
                if (dp[i][0] < INF) {
                    dp[next_pos][0] = min(dp[next_pos][0], dp[i][0] + cost);
                }
                if (dp[i][1] < INF) {
                    dp[next_pos][1] = min(dp[next_pos][1], dp[i][1] + cost);
                }

                // 2. Gunakan kupon pada lompatan ini (dari state kupon belum terpakai)
                if (dp[i][0] < INF) {
                    dp[next_pos][1] = min(dp[next_pos][1], dp[i][0] + 0LL);
                }
            }
        }
    }

    long long ans = min(dp[n - 1][0], dp[n - 1][1]);
    cout << ans << "\n";

    return 0;
}
