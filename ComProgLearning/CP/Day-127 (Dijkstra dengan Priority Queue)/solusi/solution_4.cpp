/*
============================================================
✅ Solution 4: Menghitung Banyak Jalur Terpendek
============================================================
Approach: Dijkstra + array penghitung
Complexity: Time O(E log V) | Space O(V + E)
Key Insight: Setiap jalur terpendek ke v punya tepat satu edge terakhir u -> v
             yang memenuhi dist[u] + w == dist[v]. Jadi cnt[v] adalah jumlah
             cnt[u] atas semua u seperti itu.

📖 DUA CABANG YANG BERBEDA PERLAKUAN:
   baru <  dist[v] : ditemukan jalur yang LEBIH PENDEK -> semua hitungan lama
                     jadi tidak relevan. dist[v] = baru; cnt[v] = cnt[u]; PUSH.
   baru == dist[v] : ditemukan cara LAIN dengan panjang sama -> tambahkan.
                     cnt[v] += cnt[u]; JANGAN PUSH (dist[v] tidak berubah, jadi
                     push hanya menambah entri usang).

⚠️ BOBOT HARUS POSITIF (bukan sekadar non-negatif).
   Kalau ada edge berbobot 0, sebuah simpul bisa direlaksasi ke nilai yang sama
   berkali-kali dan penghitungannya jadi kacau/ganda. Untuk bobot 0, ubah
   grafnya (gabungkan simpul yang terhubung edge-0) atau proses dengan DP di
   atas urutan dist yang sudah final.

⚠️ cnt[u] YANG DIPAKAI HARUS SUDAH FINAL.
   Karena kita hanya memproses u setelah lolos "d > dist[u] -> skip",
   dist[u] sudah final di titik itu, dan cnt[u] pun sudah lengkap. Ini alasan
   mengapa pemeriksaan entri usang di sini BUKAN sekadar optimasi.

⚠️ MODULO. Banyak jalur bisa tumbuh eksponensial. cnt sebagai long long + mod.

VERIFIKASI SAMPEL 1 (1->2:1, 1->3:1, 2->4:1, 3->4:1, 1->4:5):
   pop (0,1): dist[2]=1 cnt=1 ; dist[3]=1 cnt=1 ; dist[4]=5 cnt=1
   pop (1,2): 1+1=2 < 5  -> dist[4]=2, cnt[4]=cnt[2]=1, push
   pop (1,3): 1+1=2 == 2 -> cnt[4] += cnt[3] -> cnt[4]=2   (tanpa push)
   pop (2,4): selesai ; pop (5,4): usang, skip
   hasil "2 2"  ✓

VERIFIKASI SAMPEL 3: tiga cabang 1->{2,3,4} bobot 2, lalu ke 5 bobot 3.
   dist[5] = 5, cnt[5] = 1+1+1 = 3  ✓

🔄 ALTERNATIVE APPROACHES:
- Jalankan Dijkstra dulu untuk mendapat dist final, lalu urutkan simpul
  berdasarkan dist dan hitung cnt dengan satu sapuan DP. Lebih mudah dibuktikan
  benar, dan menangani bobot 0 dengan lebih rapi.
- Varian CSES 1202 juga meminta jumlah edge minimum dan maksimum di antara
  jalur terpendek -- polanya identik, tinggal menambah dua array.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = LLONG_MAX / 4;
const ll MOD = 1000000007LL;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, INF), cnt(n + 1, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[1] = 0; cnt[1] = 1; pq.push({0, 1});
    while (!pq.empty()) {
        pli t = pq.top(); pq.pop();
        ll d = t.first; int u = t.second;
        if (d > dist[u]) continue;
        for (auto& e : g[u]) {
            int v = e.first; ll w = e.second;
            ll baru = d + w;
            if (baru < dist[v]) {
                dist[v] = baru;
                cnt[v] = cnt[u];
                pq.push({baru, v});
            } else if (baru == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;   // TANPA push
            }
        }
    }

    if (dist[n] >= INF) cout << "-1 0\n";
    else cout << dist[n] << ' ' << cnt[n] << '\n';
    return 0;
}
