/*
============================================================
✅ Solution 1: Banyak Jalur dari 1 ke N
============================================================
Approach: Kahn -> DP aditif dalam urutan topologis
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Setiap jalur 1 -> v memiliki tepat SATU edge terakhir u -> v.
             Maka banyak jalur ke v = jumlah banyak jalur ke seluruh pendahulunya.
             Tidak ada jalur yang terhitung dua kali, karena edge terakhirnya beda.

📖 ALGORITMANYA:
   dp[1] = 1, sisanya 0
   for u dalam urutan topologis:
       for v tetangga u:  dp[v] = (dp[v] + dp[u]) % MOD
   jawaban dp[N]

⚠️ KENAPA URUTAN TOPOLOGIS WAJIB. Saat u diproses, semua pendahulu u sudah
   diproses, jadi dp[u] SUDAH FINAL. Kalau kamu menyapu simpul dengan urutan
   nomor (1,2,3,...), dp[u] bisa saja masih setengah jadi dan kontribusinya
   hilang -- jawaban terlalu kecil, dan bug-nya tidak kelihatan pada graf kecil.

⚠️ MODULO. Pada DAG 30 simpul saja jumlah jalur bisa melampaui 2^30. Selalu
   simpan sebagai long long dan modulo setiap penjumlahan.

⚠️ TAK TERJANGKAU OTOMATIS BENAR. Simpul yang tidak bisa dicapai dari 1
   punya dp = 0, dan 0 adalah elemen netral penjumlahan, jadi ia tidak
   mencemari apa pun. Ini kemewahan yang TIDAK dimiliki versi max/min --
   di sana sentinel harus dilewati secara eksplisit.

VERIFIKASI SAMPEL 1:
   topo 1 2 3 4 5
   u=1: dp[2]=1, dp[3]=1
   u=2: dp[4]=1
   u=3: dp[4]=2, dp[5]=1
   u=4: dp[5]=1+2=3
   dp[5] = 3  ✓  (1-2-4-5, 1-3-4-5, 1-3-5)

VERIFIKASI SAMPEL 3:
   1 memberi 1 ke 2 dan 3; keduanya memberi 1 ke 4 dan ke 5 -> dp[4]=dp[5]=2
   dp[6] = dp[4] + dp[5] = 4  ✓

🔄 ALTERNATIVE APPROACHES:
- Memoisasi rekursif f(u) = jumlah f(v). Setara, tapi rekursi 10^5 dalam
  berisiko stack overflow.
- Kalau soal minta hasil EKSAK tanpa modulo dan angkanya besar: big integer
  atau __int128 kalau muat.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);

    vector<ll> dp(n + 1, 0);
    dp[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
            if (--indeg[v] == 0) q.push(v);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
