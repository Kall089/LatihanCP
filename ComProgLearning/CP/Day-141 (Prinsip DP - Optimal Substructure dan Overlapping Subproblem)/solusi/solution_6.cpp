/*
============================================================
✅ Solution 6: Lompatan Minimum
============================================================
Approach: Forward DP (mendorong nilai ke state berikutnya)
Complexity: Time O(N^2) pada kasus terburuk | Space O(N)
Key Insight:
Sampai sekarang kita selalu menghitung dp[i] dengan MENARIK dari state
sebelumnya. Soal ini lebih alami dikerjakan sebaliknya: dari state i
kita MENDORONG nilai ke semua state yang bisa dicapai. Keduanya sah,
dan memilih arah yang tepat sering membuat kode jauh lebih sederhana.

Baris "if (dp[i] == INF) continue;" penting: tanpa itu, batu yang tidak
terjangkau akan menyebarkan nilai INF + 1 dan merusak jawaban.

Untuk N yang jauh lebih besar, soal ini punya solusi greedy O(N),
tapi versi DP ini lebih mudah dibuktikan benar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int INF = 1e9;
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> dp(n + 1, INF);
    dp[1] = 0;                                   // basis: sudah di batu pertama

    for (int i = 1; i <= n; i++) {
        if (dp[i] == INF) continue;              // batu ini tidak terjangkau, lewati
        int batas = min(n, i + a[i]);
        for (int j = i + 1; j <= batas; j++)
            dp[j] = min(dp[j], dp[i] + 1);
    }

    cout << (dp[n] == INF ? -1 : dp[n]) << "\n";

    return 0;
}
