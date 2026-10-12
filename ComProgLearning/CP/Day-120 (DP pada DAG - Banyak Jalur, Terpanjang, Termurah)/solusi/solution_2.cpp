/*
============================================================
✅ Solution 2: Jalur Terpanjang di DAG
============================================================
Approach: Kahn -> DP max dalam urutan topologis
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Jalur terpanjang ke v = max atas semua pendahulu u dari
             (jalur terpanjang ke u) + w(u,v). Urutan topologis menjamin
             dp[u] sudah final saat dipakai.

📖 KENAPA INI ISTIMEWA:
   Jalur terpanjang pada graf UMUM adalah masalah NP-hard -- ia memuat
   Hamiltonian path sebagai kasus khusus. Pada DAG ia selesai dalam waktu
   LINEAR. Perbedaan ini sepenuhnya berasal dari ketiadaan siklus: dengan
   siklus berbobot positif, jawabannya tak hingga.

⚠️ SENTINEL HARUS DILEWATI, BUKAN SEKADAR DIINISIALISASI.
       if (dp[u] == NEG) continue;
   Tanpa baris ini, simpul yang tak terjangkau dari 1 akan "merelaksasi"
   tetangganya dengan NEG + w. Nilai itu jauh lebih besar dari NEG, jadi ia
   MENANG melawan sentinel dan menular ke seluruh graf. Gejala: jawaban berupa
   angka negatif raksasa yang tidak masuk akal.

⚠️ NEG = LLONG_MIN / 4, BUKAN LLONG_MIN.
   Kalau kamu memakai LLONG_MIN, ekspresi dp[u] + w akan UNDERFLOW (undefined
   behavior) bahkan sebelum sempat dibandingkan. Beri ruang.

⚠️ long long WAJIB. Sampel 3: 3 * 10^9 sudah melewati batas int.

VERIFIKASI SAMPEL 1:
   dp awal: [_,0,-,-,-,-]
   u=1: dp[2]=3, dp[3]=2
   u=2: dp[4]=3+4=7
   u=3: dp[4]=max(7,2+1)=7 ; dp[5]=2+7=9
   u=4: dp[5]=max(9,7+2)=9
   dp[5] = 9  ✓

VERIFIKASI SAMPEL 2: dp[3] tetap NEG -> cetak -1  ✓

🔄 ALTERNATIVE APPROACHES:
- Membalik tanda bobot lalu Dijkstra: SALAH. Dijkstra tidak boleh bobot
  negatif; hasilnya bukan sekadar tidak optimal, tapi keliru.
- Bellman-Ford dengan bobot dinegasikan: benar, tapi O(V*E) -- jauh lebih
  lambat dan tidak ada gunanya di DAG.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

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

    vector<ll> dp(n + 1, NEG);
    dp[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] != NEG) dp[v] = max(dp[v], dp[u] + w);
            if (--indeg[v] == 0) q.push(v);
        }
    }

    cout << (dp[n] == NEG ? -1 : dp[n]) << '\n';
    return 0;
}
