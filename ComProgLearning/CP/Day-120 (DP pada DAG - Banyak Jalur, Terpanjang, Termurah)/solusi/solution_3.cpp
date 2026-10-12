/*
============================================================
✅ Solution 3: Jalur Termurah di DAG (Bobot Boleh Negatif)
============================================================
Approach: Kahn -> DP min dalam urutan topologis
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Identik dengan Solution 2, hanya max -> min dan NEG -> POS.
             Inilah maksud "satu kerangka, tiga pertanyaan".

📖 KENAPA BOBOT NEGATIF TIDAK MASALAH DI SINI:
   Dijkstra bergantung pada asumsi bahwa begitu sebuah simpul dikeluarkan dari
   heap, jaraknya sudah final -- asumsi yang runtuh kalau ada edge negatif yang
   bisa memperpendek jalur belakangan. DP di DAG TIDAK memakai asumsi itu sama
   sekali. Ia memakai asumsi yang berbeda dan lebih kuat: urutan topologis
   menjamin semua pendahulu sudah selesai. Bobot boleh apa saja.
   (Yang tidak boleh adalah SIKLUS negatif -- dan DAG tidak punya siklus.)

⚠️ SAMPEL 2 ADALAH PERANGKAP DIJKSTRA.
   1->2 (1), 1->3 (10), 2->4 (10), 3->4 (-20).
   Dijkstra mengeluarkan 2 (jarak 1), lalu 4 (jarak 11), dan MENGUNCI 4.
   Ia tidak akan pernah melihat bahwa lewat 3 hasilnya -10. DP DAG benar.

⚠️ POS = LLONG_MAX / 4. Sama seperti Solution 2: beri ruang agar dp[u] + w
   tidak overflow.

⚠️ if (dp[u] == POS) continue; tetap WAJIB.

VERIFIKASI SAMPEL 1:
   u=1: dp[2]=3, dp[3]=2
   u=2: dp[4]=7
   u=3: dp[4]=min(7, 2+1)=3 ; dp[5]=2+7=9
   u=4: dp[5]=min(9, 3+2)=5
   dp[5] = 5  ✓  (1-3-4-5)

VERIFIKASI SAMPEL 2:
   u=1: dp[2]=1, dp[3]=10
   u=2: dp[4]=11
   u=3: dp[4]=min(11, 10-20) = -10
   dp[4] = -10  ✓

🔄 ALTERNATIVE APPROACHES:
- Bellman-Ford: benar juga (dan menangani graf bersiklus), tapi O(V*E).
- Dijkstra: hanya kalau semua bobot non-negatif. Pada graf DAG dengan bobot
  non-negatif, DP ini tetap lebih cepat: O(V+E) vs O(E log V).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll POS = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        indeg[v]++;
    }

    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);

    vector<ll> dp(n + 1, POS);
    dp[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] != POS) dp[v] = min(dp[v], dp[u] + w);
            if (--indeg[v] == 0) q.push(v);
        }
    }

    if (dp[n] == POS) cout << "TIDAK TERJANGKAU\n";
    else cout << dp[n] << '\n';
    return 0;
}
