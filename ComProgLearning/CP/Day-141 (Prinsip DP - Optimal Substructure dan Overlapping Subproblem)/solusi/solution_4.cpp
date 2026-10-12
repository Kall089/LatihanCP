/*
============================================================
✅ Solution 4: Koin Minimum
============================================================
Approach: DP 1D pola minimum + penanda tak tercapai
Complexity: Time O(T x K) | Space O(T)
Key Insight:
Sama seperti soal tangga, kuncinya adalah memikirkan PILIHAN TERAKHIR:
koin apa yang dipakai paling akhir. Setelah koin itu dipakai, sisanya
adalah submasalah yang lebih kecil dan sudah pernah dihitung.

Soal ini juga contoh nyata kegagalan greedy. Dengan koin {1, 3, 4} dan
target 6, greedy mengambil 4 lalu terpaksa 1 + 1 (3 koin), sedangkan
jawaban optimalnya 3 + 3 (2 koin). Karena itu kita wajib memakai DP.

Pengecekan dp[v-c] != INF penting agar INF + 1 tidak dianggap solusi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int INF = 1e9;
    int k, t;
    if (!(cin >> k >> t)) return 0;
    vector<int> koin(k);
    for (int &x : koin) cin >> x;

    vector<int> dp(t + 1, INF);
    dp[0] = 0;                                  // basis: 0 koin untuk nilai 0
    for (int v = 1; v <= t; v++)
        for (int c : koin)
            if (c <= v && dp[v - c] != INF)
                dp[v] = min(dp[v], dp[v - c] + 1);

    cout << (dp[t] == INF ? -1 : dp[t]) << "\n";

    return 0;
}
