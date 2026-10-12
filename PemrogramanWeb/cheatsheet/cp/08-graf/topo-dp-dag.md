# Topological sort dan DP pada DAG

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **119**. Urutan prasyarat dan DP setelah urutan itu ada. Tes siklus berarah juga di [siklus-bipartit.md](siklus-bipartit.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Kahn](#kahn)
- [Kahn leksikografis dan unik](#kahn-leksikografis-dan-unik)
- [Topo DFS](#topo-dfs)
- [DP banyak jalur](#dp-banyak-jalur)
- [DP terpanjang dan termurah](#dp-terpanjang-dan-termurah)
- [Banyak sumber dan jalur kritis](#banyak-sumber-dan-jalur-kritis)
- [Ringkasan](#ringkasan)

---

## Kahn

**Teori:** Urutan topologis adalah barisan semua simpul sehingga setiap sisi `u → v` menempatkan `u` sebelum `v`. Analoginya rencana studi: mata kuliah hanya boleh diambil setelah prasyaratnya. Teorema: urutan ada **jika dan hanya jika** graf adalah DAG. Kahn berulang kali mengambil simpul ber-indegree 0, menghapusnya, dan mengurangi indegree tetangga. Setiap DAG tak kosong punya simpul indegree 0 (kalau tidak, jalan mundur tak hingga → siklus).

**Kapan:** prasyarat, kompilasi, DP pada DAG, deteksi siklus (`ord.size() != n`). Jangan pada graf tak berarah. Jangan mengharapkan urutan unik.

**Proses:** sisi `0→2, 1→2, 1→3, 2→4, 3→4` (simpul 0..4).

Indegree awal: `[0, 0, 2, 1, 2]`.

| antrean | ambil | efek indegree | hasil |
|---|---|---|---|
| `[0, 1]` | 0 | 2: 2→1 | `[0]` |
| `[1]` | 1 | 2: 1→0 push 2; 3: 1→0 push 3 | `[0, 1]` |
| `[2, 3]` | 2 | 4: 2→1 | `[0, 1, 2]` |
| `[3]` | 3 | 4: 1→0 push 4 | `[0, 1, 2, 3]` |
| `[4]` | 4 | — | `[0, 1, 2, 3, 4]` |

`size == 5` → DAG. Tambah `4→1`: indegree 1 menjadi 1 di awal; 1 tidak pernah 0 bersama 4 → `ord` tidak lengkap.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> kahn(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n), ord;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{2}, {2, 3}, {4}, {4}, {}};
    auto ord = kahn(5, g);
    if ((int)ord.size() != 5) cout << "SIKLUS\n";
    else {
        for (int x : ord) cout << x << ' ';
        cout << '\n';                              // 0 1 2 3 4 atau 1 0 ...
    }
    return 0;
}
```

**Jebakan:**

1. Membandingkan output dengan satu urutan tetap padahal soal menerima semua urutan sah.
2. Lupa cek `ord.size() == n` lalu memakai `ord` untuk DP.
3. Input `u v` artinya “u sebelum v” atau “u tergantung v”? Arah terbalik merusak semua.
4. Menghitung indegree dari list tak berarah.

**Kompleksitas:** `O(n + m)`.

---

## Kahn leksikografis dan unik

**Teori:** Jika soal minta urutan **leksikografis terkecil**, ganti `queue` dengan `priority_queue` min. Urutan unik jika setiap saat hanya ada **satu** simpul indegree 0 (tidak ada kebebasan memilih). Analoginya: jika dua mata kuliah siap bersamaan, kamu boleh menukar urutannya.

Level `lvl[v] = max(lvl[u]+1)` sepanjang sisi adalah “sedini-lewatnya” dalam satuan prasyarat.

**Kapan:** “cetak urutan nomor terkecil”, “apakah urutan wajib”, jalur kritis jumlah sisi. Jangan heap jika soal tidak peduli urutan.

**Proses:** graf yang sama. Awal indegree 0: `{0,1}` — tidak unik. Lex: ambil 0 dulu, lalu 1, lalu 2 (sebelum 3 karena 2 lebih kecil setelah keduanya 0? Setelah ambil 0: indeg 2 jadi 1, antrean `{1}`. Ambil 1: 2 dan 3 jadi 0. Heap `[2,3]`, ambil 2, lalu 3, lalu 4. Lex = `0 1 2 3 4`.

`lvl[4] = 2` (misal `0-2-4` atau `1-3-4`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> kahnLeksikografis(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n), ord;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; u++) if (!indeg[u]) pq.push(u);
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) pq.push(v);
    }
    return ord;
}

struct InfoTopo {
    vector<int> ord, lvl;
    bool dag = true, unik = true;
};

InfoTopo kahnLengkap(int n, const vector<vector<int>>& g) {
    InfoTopo r;
    r.lvl.assign(n, 0);
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        if ((int)q.size() > 1) r.unik = false;
        int u = q.front();
        q.pop();
        r.ord.push_back(u);
        for (int v : g[u]) {
            r.lvl[v] = max(r.lvl[v], r.lvl[u] + 1);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    r.dag = ((int)r.ord.size() == n);
    if (!r.dag) r.unik = false;
    return r;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{2}, {2, 3}, {4}, {4}, {}};
    auto lex = kahnLeksikografis(5, g);
    for (int x : lex) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 3 4
    auto info = kahnLengkap(5, g);
    cout << info.unik << ' ' << info.lvl[4] << '\n'; // 0  2
    return 0;
}
```

**Jebakan:**

1. Leksikografis memakai `queue` biasa (urutan masuk, bukan nomor kecil).
2. `unik` dihitung dari “hanya satu sumber di awal”, bukan tiap langkah.
3. `lvl` pada simpul tak terjangkau tetap 0 — bedakan sumber vs tak masuk DAG rusak.

**Kompleksitas:** lex `O((n + m) log n)`, lengkap `O(n + m)`.

---

## Topo DFS

**Teori:** DFS selesai (post-order) pada DAG menuliskan simpul setelah semua tetangga ke depan selesai. Membalik daftar post-order memberi urutan topologis. Analoginya: kamu menandatangani form setelah semua form yang kamu butuhkan sudah ditandatangani. Back-edge ke warna abu menolak DAG.

**Kapan:** DFS sudah ditulis, atau butuh klasifikasi sisi. Kahn lebih nyaman untuk “unik?” dan level. Keduanya sah.

**Proses:** sisi `0→1, 0→2, 1→3, 2→3`. DFS dari 0, tetangga kecil dulu.

| peristiwa | post |
|---|---|
| 0 masuk, ke 1 | |
| 1 ke 3 | |
| 3 selesai | `[3]` |
| 1 selesai | `[3, 1]` |
| 0 ke 2 | |
| 2 ke 3 (hitam, skip) | |
| 2 selesai | `[3, 1, 2]` |
| 0 selesai | `[3, 1, 2, 0]` |

Balik: `0, 2, 1, 3`. Tetap sah: 0 sebelum 1 dan 2, keduanya sebelum 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct TopoDFS {
    vector<int> wrn, ord;
    bool siklus = false;

    void dfs(int u, const vector<vector<int>>& g) {
        wrn[u] = 1;
        for (int v : g[u]) {
            if (wrn[v] == 1) { siklus = true; return; }
            if (wrn[v] == 0) {
                dfs(v, g);
                if (siklus) return;
            }
        }
        wrn[u] = 2;
        ord.push_back(u);
    }

    vector<int> run(int n, const vector<vector<int>>& g) {
        wrn.assign(n, 0);
        ord.clear();
        siklus = false;
        for (int s = 0; s < n && !siklus; s++)
            if (wrn[s] == 0) dfs(s, g);
        if (siklus) return {};
        reverse(ord.begin(), ord.end());
        return ord;
    }
};

int main() {
    FASTIO;
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    TopoDFS t;
    auto ord = t.run(4, g);
    for (int x : ord) cout << x << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:**

1. Lupa `reverse` — itu post-order, bukan topo.
2. Menulis simpul di **preorder** (saat masuk).
3. Tidak menjalankan DFS dari semua sumber.
4. Stack overflow pada rantai `1e5`.

**Kompleksitas:** `O(n + m)`.

---

## DP banyak jalur

**Teori:** Setelah urutan topologis ada, setiap sisi pergi ke simpul yang lebih belakang. DP bisa diisi kiri-ke-kanan tanpa siklus update. Analoginya: menghitung nilai ujian hanya setelah semua prasyarat punya nilai. Pola push: `dp[v] += dp[u]`. Bobot diabaikan untuk “banyak jalur”.

**Kapan:** “berapa cara dari S ke T”. Jangan jika ada siklus (kecuali *mean cycle* khusus). Jangan lupa modulo.

**Proses:** sisi `0→1, 0→2, 1→3, 2→3`, sumber 0. Dua jalur ke 3.

| u dalam topo `[0,1,2,3]` | `cara` setelah push |
|---|---|
| 0, `cara[0]=1` | `cara[1]=1`, `cara[2]=1` |
| 1 | `cara[3]=1` |
| 2 | `cara[3]=2` |
| 3 | tetap 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

vector<int> topoDariBerbobot(int n, const vector<vector<pair<int, ll>>>& g) {
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (auto [v, w] : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    vector<int> ord;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (auto [v, w] : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

vector<ll> banyakJalur(int n, const vector<vector<pair<int, ll>>>& g,
                       const vector<int>& ord, int s) {
    vector<ll> dp(n, 0);
    dp[s] = 1;
    for (int u : ord) {
        if (!dp[u]) continue;
        for (auto [v, w] : g[u]) dp[v] = (dp[v] + dp[u]) % MOD;
    }
    return dp;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 1});
    g[0].push_back({2, 1});
    g[1].push_back({3, 1});
    g[2].push_back({3, 1});
    auto ord = topoDariBerbobot(n, g);
    cout << banyakJalur(n, g, ord, 0)[3] << '\n';  // 2
    return 0;
}
```

**Jebakan:**

1. `if (!dp[u]) continue` men-skip simpul yang `cara=0` — benar untuk “dari s”; salah jika kamu ingin menjumlah dari **semua** sumber (inisialisasi semua sumber = 1).
2. `ord.size() != n` tetap dipakai.
3. Modulo lupa, overflow `ll` pada `n,m` besar tanpa mod.

**Kompleksitas:** `O(n + m)`.

---

## DP terpanjang dan termurah

**Teori:** Di DAG, jalur terpanjang dan termurah keduanya sah dengan relaksasi `max` / `min`. Bobot negatif **boleh** — beda dari Dijkstra. Analoginya: proyek berprasyarat, total durasi vs total biaya.

Inisialisasi: terpanjang `dp[s]=0`, lain `-INF`. Termurah `dp[s]=0`, lain `+INF`. Jangan update dari state yang belum tercapai.

**Kapan:** “rantai tugas terpanjang”, “biaya minimum proyek”. Jangan Dijkstra jika ada negatif tetapi graf DAG — topo-DP lebih tepat. Jangan *longest path* di graf umum (NP-berat).

**Proses:** sisi berbobot `0→1 (2), 0→2 (1), 1→3 (3), 2→3 (10)`, sumber 0.

```
terpanjang 0-2-3 = 11
termurah   0-1-3 = 5
banyak     2
```

| u | push min | push max |
|---|---|---|
| 0, dp=0 | 1←2, 2←1 | sama |
| 1 | 3←5 | 3←5 |
| 2 | 3 tetap 5 | 3←11 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> jalurTerpanjang(int n, const vector<vector<pair<int, ll>>>& g,
                           const vector<int>& ord, int s) {
    vector<ll> dp(n, -INF);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == -INF) continue;
        for (auto [v, w] : g[u]) dp[v] = max(dp[v], dp[u] + w);
    }
    return dp;
}

vector<ll> jalurTermurahDAG(int n, const vector<vector<pair<int, ll>>>& g,
                            const vector<int>& ord, int s) {
    vector<ll> dp(n, INF);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == INF) continue;
        for (auto [v, w] : g[u]) dp[v] = min(dp[v], dp[u] + w);
    }
    return dp;
}

vector<int> bangunDariPar(int s, int t, const vector<int>& par) {
    if (t < 0) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path.empty() || path[0] != s) return {};
    return path;
}

vector<int> jalurMinRekonstruksi(int n, const vector<vector<pair<int, ll>>>& g,
                                 const vector<int>& ord, int s, int t) {
    vector<ll> dp(n, INF);
    vector<int> par(n, -1);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == INF) continue;
        for (auto [v, w] : g[u]) if (dp[u] + w < dp[v]) {
            dp[v] = dp[u] + w;
            par[v] = u;
        }
    }
    if (dp[t] >= INF) return {};
    return bangunDariPar(s, t, par);
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 2});
    g[0].push_back({2, 1});
    g[1].push_back({3, 3});
    g[2].push_back({3, 10});
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (auto [v, w] : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    vector<int> ord;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (auto [v, w] : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    cout << jalurTerpanjang(n, g, ord, 0)[3] << '\n';   // 11
    cout << jalurTermurahDAG(n, g, ord, 0)[3] << '\n';  // 5
    auto p = jalurMinRekonstruksi(n, g, ord, 0, 3);
    for (int x : p) cout << x << ' ';
    cout << '\n';                                       // 0 1 3
    return 0;
}
```

**Jebakan:**

1. Tidak mengabaikan `dp[u] == ±INF`: `-INF + w` overflow.
2. Inisialisasi terpanjang `0` di semua simpul: jalur “kosong” di simpul tak terkait ikut.
3. `par[s]` bukan `-1` lalu loop saat `s = 0`.

**Kompleksitas:** `O(n + m)`.

---

## Banyak sumber dan jalur kritis

**Teori:** Sumber jamak: taruh `dp = 0` (atau `cara = 1`) di semua simpul indegree 0, atau di daftar sumber soal. Jalur kritis = jalur terpanjang dari “mulai” ke “selesai”; slack simpul adalah selisih `latest - earliest`. Analoginya: bagan Gantt, tugas yang slack-nya 0 tidak boleh mundur.

**Kapan:** proyek, “hari minimum sampai semua selesai” = `max dp[u]` terpanjang dari sumber. Jangan campur unit: sisi = durasi tugas di ujung vs durasi sisi.

**Proses:** tugas 0..3, durasi simpul `[2, 3, 4, 1]`, sisi prasyarat `0→2, 1→2, 2→3`.

Earliest finish: proses topo, `ef[v] = max(ef[v], ef[u]) + dur[v]` dengan basis `ef[sumber] = dur[sumber]`.

| u | ef |
|---|---|
| 0 | 2 |
| 1 | 3 |
| 2 | max(2,3)+4 = 7 |
| 3 | 7+1 = 8 |

Proyek selesai hari 8. Jalur kritis `1-2-3` (1 lebih ketat dari 0).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> earliestFinish(int n, const vector<vector<int>>& g,
                          const vector<ll>& dur, const vector<int>& ord) {
    vector<ll> ef(n, 0);
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    for (int u = 0; u < n; u++) if (!indeg[u]) ef[u] = dur[u];
    for (int u : ord) {
        for (int v : g[u]) ef[v] = max(ef[v], ef[u] + dur[v]);
    }
    return ef;
}

ll selesaiProyek(const vector<ll>& ef) {
    ll ans = 0;
    for (ll x : ef) ans = max(ans, x);
    return ans;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{2}, {2}, {3}, {}};
    vector<ll> dur = {2, 3, 4, 1};
    auto ord = vector<int>{0, 1, 2, 3};
    auto ef = earliestFinish(4, g, dur, ord);
    cout << selesaiProyek(ef) << '\n';             // 8
    cout << ef[2] << ' ' << ef[3] << '\n';         // 7 8
    return 0;
}
```

**Jebakan:**

1. Menjumlah `dur[u] + dur[v]` dua kali di sisi.
2. Sumber tidak diinisialisasi `dur[u]`, `ef` tetap 0.
3. `selesaiProyek` mengambil `ef[n-1]` padahal sink bukan simpul terakhir.

**Kompleksitas:** `O(n + m)`.

---

## Ringkasan

**Teori:** Kahn/DFS memberi urutan. DP push mengikuti urutan. DAG mengizinkan min, max, dan jumlah jalur, termasuk bobot negatif.

**Kapan:** prasyarat, banyak cara, rantai terpanjang, biaya proyek. Ada siklus → jangan DP ini. Bobot `≥ 0` graf umum → Dijkstra.

**Proses:** uji 4 simpul di `main`, cocokkan 2 jalur / 11 / 5.

**Jebakan lintas:**

1. Lupa `ord.size() == n`.
2. `reverse` DFS.
3. Update dari `±INF`.
4. Lex tanpa heap.

**Kompleksitas saku:** `O(n + m)`, lex `O((n+m) log n)`.

Lanjut: [euler.md](euler.md) · [siklus-bipartit.md](siklus-bipartit.md) · [dijkstra.md](dijkstra.md)
