/*
============================================================
✅ Solution 4: Rekonstruksi Rute Terpanjang
============================================================
Approach: DP max + array parent, telusuri balik
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: DP menghitung NILAI; parent menyimpan KEPUTUSAN. Setiap kali
             dp[v] benar-benar membaik, edge yang menyebabkannya adalah edge
             terakhir dari jalur optimal ke v. Simpan pengirimnya.

📖 ALGORITMANYA:
   if (dp[u] + w > dp[v]) { dp[v] = dp[u] + w; par[v] = u; }
   lalu: v = N; while (v) { path.push(v); v = par[v]; } reverse.

⚠️ par[v] HARUS DI DALAM if. Kalau ditulis di luar, par[v] menjadi pengirim
   TERAKHIR YANG DILIHAT, bukan yang terbaik. Jalur yang tercetak lalu tidak
   sesuai dengan nilai dp -- bug yang sangat membingungkan karena angkanya benar
   tapi jalurnya salah.

⚠️ PAKAI ">" BUKAN ">=".
   Dengan ">=", pada kasus seri par[v] bisa diperbarui ke simpul lain yang
   nilainya sama. Itu sendiri tidak salah, TAPI kalau kamu tidak hati-hati
   dengan urutan pemrosesan, penelusuran balik bisa berputar. Aturan aman:
   pakai ">" dan jangan sentuh par kalau tidak ada perbaikan.

⚠️ CEK KETERJANGKAUAN SEBELUM MENELUSURI. Kalau dp[N] == NEG, par[N] masih 0
   dan loop penelusuran akan menghasilkan sampah. Cetak IMPOSSIBLE dan keluar.

⚠️ SERI DIPERBOLEHKAN. Sampel 1 punya dua jalur bernilai 9. Jawaban mana pun
   yang bernilai 9 benar -- jangan bandingkan output dengan satu string tetap.

VERIFIKASI SAMPEL 1:
   dp[2]=3 par=1 ; dp[3]=2 par=1
   dp[4]=7 par=2 ; (dari 3: 2+1=3, tidak membaik, par tetap 2)
   dp[5]=9 par=3 (2+7) ; (dari 4: 7+2=9, TIDAK > 9, par tetap 3)
   telusuri 5 -> 3 -> 1  =>  1 3 5, nilai 9  ✓
   (Implementasi di bawah memproses edge dalam urutan input, jadi hasil bisa
    "1 3 5" atau "1 2 4 5" tergantung urutan; keduanya sah.)

🔄 ALTERNATIVE APPROACHES:
- Tanpa par[]: telusuri balik dari N dengan mencari pendahulu u yang memenuhi
  dp[u] + w == dp[N]. Butuh graf terbalik, dan sama cepatnya. Lebih hemat
  memori sedikit, tapi lebih mudah salah.
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
    vector<int> par(n + 1, 0);
    dp[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            if (dp[u] != NEG && dp[u] + w > dp[v]) {   // ">" dan di DALAM if
                dp[v] = dp[u] + w;
                par[v] = u;
            }
            if (--indeg[v] == 0) q.push(v);
        }
    }

    if (dp[n] == NEG) { cout << "IMPOSSIBLE\n"; return 0; }

    vector<int> path;
    for (int v = n; v != 0; v = par[v]) {
        path.push_back(v);
        if (v == 1) break;
    }
    reverse(path.begin(), path.end());

    cout << dp[n] << '\n';
    for (size_t i = 0; i < path.size(); i++)
        cout << path[i] << " \n"[i + 1 == path.size()];
    return 0;
}
