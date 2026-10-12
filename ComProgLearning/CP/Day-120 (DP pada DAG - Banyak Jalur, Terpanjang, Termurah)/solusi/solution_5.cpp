/*
============================================================
✅ Solution 5: Tiga Jawaban dalam Satu Sapuan
============================================================
Approach: tiga array DP di dalam loop edge yang sama
Complexity: Time O(N + M) | Space O(N)
Key Insight: Ketiga pertanyaan memakai urutan evaluasi yang IDENTIK, jadi
             tidak ada alasan menyapu graf tiga kali. Satu loop, tiga
             pembaruan.

📖 YANG BERUBAH HANYA TIGA HAL PER PERTANYAAN:
   cnt   : init cnt[1]=1, lainnya 0     ; cnt[v] += cnt[u]        ; mod
   best  : init best[1]=0, lainnya NEG  ; best[v] = max(., best[u]+w)
   cheap : init cheap[1]=0, lainnya POS ; cheap[v] = min(., cheap[u]+w)

⚠️ TIGA SYARAT SENTINEL YANG TERPISAH. Jangan menggabungkan penjagaannya jadi
   satu if. Pada masalah ini ketiganya kebetulan bernilai sama (u terjangkau
   dari 1 atau tidak), tapi menuliskannya terpisah membuat kode tetap benar
   kalau nanti sumbernya berbeda-beda.

⚠️ cnt TIDAK BUTUH PENJAGA karena 0 adalah elemen netral penjumlahan.
   best dan cheap BUTUH karena NEG + w dan POS + w merusak.

⚠️ SATU LOOP, BUKAN TIGA. Selain lebih cepat, ini juga mencegah bug klasik
   "lupa mereset indeg" saat menjalankan Kahn berkali-kali.

VERIFIKASI SAMPEL 1:
   cnt[5] = 3, best[5] = 9, cheap[5] = 5   ✓ (lihat trace di teori bagian 5)

VERIFIKASI SAMPEL 3 (1->2 dan 3->4, N=4):
   4 tak terjangkau dari 1 -> cnt 0, best NEG -> -1, cheap POS -> -1  ✓

🔄 ALTERNATIVE APPROACHES:
- Tiga fungsi terpisah yang masing-masing membangun ulang indeg. Lebih mudah
  dibaca, tiga kali lebih lambat -- masih O(N+M) jadi biasanya tetap lolos.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
const ll NEG = LLONG_MIN / 4;
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

    vector<ll> cnt(n + 1, 0), best(n + 1, NEG), cheap(n + 1, POS);
    cnt[1] = 1; best[1] = 0; cheap[1] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            cnt[v] = (cnt[v] + cnt[u]) % MOD;                    // netral 0
            if (best[u]  != NEG) best[v]  = max(best[v],  best[u]  + w);
            if (cheap[u] != POS) cheap[v] = min(cheap[v], cheap[u] + w);
            if (--indeg[v] == 0) q.push(v);
        }
    }

    cout << cnt[n] << '\n';
    cout << (best[n]  == NEG ? -1 : best[n])  << '\n';
    cout << (cheap[n] == POS ? -1 : cheap[n]) << '\n';
    return 0;
}
