/*
============================================================
✅ Solution 3: Pekan Komunitas Kreatif (Vacation - AtCoder DP-C)
============================================================
Approach: Dynamic Programming 2D (State Berbasis Pilihan Terakhir)
Complexity: Time O(N) | Space O(N) atau O(1) dengan Rolling Variables

Key Insight:
Untuk menentukan keputusan legal di hari i, kita hanya membutuhkan
informasi mengenai kegiatan apa yang dipilih tepat di hari (i - 1).
Oleh karena itu, kita mendefinisikan state:
dp[i][j] = kepuasan maksimum dari hari 0 sampai hari i dengan kegiatan di hari i adalah j (0, 1, 2).

Transisi:
dp[i][0] = cost[i][0] + max(dp[i - 1][1], dp[i - 1][2])
dp[i][1] = cost[i][1] + max(dp[i - 1][0], dp[i - 1][2])
dp[i][2] = cost[i][2] + max(dp[i - 1][0], dp[i - 1][1])

Base case (hari 0):
dp[0][j] = cost[0][j] untuk setiap j in {0, 1, 2}.

Jawaban akhir:
max(dp[N - 1][0], dp[N - 1][1], dp[N - 1][2])

Sample 1:
Input:
3
10 40 70
20 50 80
30 60 90
Output:
210

Sample 2:
Input:
1
-5 -2 -9
Output:
-2

Sample 3:
Input:
7
6 7 8
8 8 3
2 5 2
7 8 6
4 6 8
2 3 4
7 5 1
Output:
46
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> cost(n, vector<long long>(3));
    for (int i = 0; i < n; i++) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // Menggunakan rolling variable untuk efisiensi memori O(1)
    long long dp0 = cost[0][0];
    long long dp1 = cost[0][1];
    long long dp2 = cost[0][2];

    for (int i = 1; i < n; i++) {
        long long next0 = cost[i][0] + max(dp1, dp2);
        long long next1 = cost[i][1] + max(dp0, dp2);
        long long next2 = cost[i][2] + max(dp0, dp1);

        dp0 = next0;
        dp1 = next1;
        dp2 = next2;
    }

    long long ans = max({dp0, dp1, dp2});
    cout << ans << "\n";

    return 0;
}
