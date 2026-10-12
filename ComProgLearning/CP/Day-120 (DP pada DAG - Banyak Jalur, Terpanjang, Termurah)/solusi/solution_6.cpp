/*
============================================================
✅ Solution 6: Jalur Terpanjang yang Wajib Melewati Simpul K
============================================================
Approach: dekomposisi dua bagian -- DP maju dari 1, DP mundur dari N
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Setiap jalur 1 -> N yang melewati K terpecah TEPAT di K menjadi
             dua bagian yang saling bebas: 1 -> K dan K -> N. Maksimumkan
             keduanya secara terpisah dan jumlahkan.

📖 KENAPA MEMISAHKANNYA SAH:
   Pada graf umum, menggabungkan dua jalur optimal bisa menghasilkan jalur yang
   MENGULANG simpul -- tidak valid. Pada DAG hal itu MUSTAHIL: kalau ada simpul
   x muncul di kedua bagian, maka ada jalur x -> K -> x, yaitu siklus.
   Ketiadaan siklus persis yang membuat dekomposisi ini benar.

📖 DUA DP:
   A[v] = jalur terpanjang 1 -> v          (DP maju di graf ASLI, sumber 1)
   B[v] = jalur terpanjang v -> N          (DP di graf TERBALIK, sumber N)
   jawaban = A[K] + B[K]   (kalau keduanya bukan sentinel)

⚠️ B MEMBUTUHKAN GRAF TERBALIK DAN URUTAN TOPOLOGISNYA SENDIRI.
   Membalik semua edge menghasilkan DAG lagi (dengan urutan topologis yang
   merupakan kebalikan urutan aslinya). Jalankan Kahn kedua kali di graf itu.
   JANGAN lupa membangun indeg yang baru -- indeg lama sudah habis terpakai.

⚠️ CEK KEDUANYA. Sampel 3: K=3 tidak terjangkau dari 1, jadi A[3] = NEG dan
   jawabannya -1, meskipun B[3] ada.

⚠️ K == 1 ATAU K == N adalah kasus valid, bukan kasus khusus.
   A[1] = 0 dan B[N] = 0, jadi rumusnya tetap bekerja.

VERIFIKASI SAMPEL 1 (K=3):
   A[3] = 2   (1-3)
   B[3] = max(7 lewat 3-5, 1+2 lewat 3-4-5) = 7
   jawaban 2 + 7 = 9  ✓

VERIFIKASI SAMPEL 2 (K=4):
   A[4] = max(3+4 lewat 1-2-4, 2+1 lewat 1-3-4) = 7
   B[4] = 2
   jawaban 9  ✓

🔄 ALTERNATIVE APPROACHES:
- DP dengan state tambahan dp[v][0/1] = terpanjang ke v dengan/ tanpa sudah
  melewati K. Satu sapuan, tidak butuh graf terbalik. Bagus kalau simpul
  wajibnya banyak? Tidak -- untuk k simpul wajib, state jadi 2^k. Untuk SATU
  simpul wajib, kedua cara sama baiknya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

// DP jalur terpanjang dari sumber s pada graf g (dengan n simpul)
vector<ll> longest(int n, const vector<vector<pair<int,ll>>>& g, int s) {
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (auto& e : g[u]) indeg[e.first]++;
    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);

    vector<ll> dp(n + 1, NEG);
    dp[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] != NEG) dp[v] = max(dp[v], dp[u] + w);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int,ll>>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        rg[v].push_back({u, w});          // graf TERBALIK
    }

    vector<ll> A = longest(n, g,  1);     // 1 -> v
    vector<ll> B = longest(n, rg, n);     // v -> N

    if (A[k] == NEG || B[k] == NEG) { cout << -1 << '\n'; return 0; }
    cout << A[k] + B[k] << '\n';
    return 0;
}
