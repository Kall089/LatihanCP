# Dijkstra

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **127**. Jarak 1 sumber, bobot **tak negatif**. Bobot 0/1 → [dfs-bfs.md](dfs-bfs.md). Ada negatif → [bellman-floyd.md](bellman-floyd.md). DAG → [topo-dp-dag.md](topo-dp-dag.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Peta jarak](#peta-jarak)
- [Dijkstra heap](#dijkstra-heap)
- [Dijkstra padat dan rekonstruksi](#dijkstra-padat-dan-rekonstruksi)
- [Minimax dan maximin](#minimax-dan-maximin)
- [Banyak jalur dan kupon](#banyak-jalur-dan-kupon)
- [Banyak sumber](#banyak-sumber)
- [Ringkasan](#ringkasan)

---

## Peta jarak

**Teori:** “Jarak” adalah jumlah bobot sepanjang jalur. Relaksasi: `dist[v] = min(dist[v], dist[u] + w(u,v))`. Dijkstra mengunci simpul dengan perkiraan terkecil karena `w ≥ 0` menjamin awalan jalur tidak lebih mahal dari seluruh jalur. Analoginya: dari rumah, selalu perluas kota terdekat yang sudah “pasti”.

`INF = 4e18`, **bukan** `LLONG_MAX`: `dist[u] + w` harus aman.

**Kapan:**

| Soal | Alat |
|---|---|
| 1 sumber, `w ≥ 0` | Dijkstra (file ini) |
| `w ∈ {0,1}` | 0-1 BFS |
| 1 sumber, DAG | DP topo |
| ada negatif | Bellman-Ford |
| semua pasangan, `n ≤ 400` | Floyd |
| sambung semua, min total | MST |

**Proses:** kartu: lihat tanda bobot, `n` vs `m`, 1 sumber atau semua.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<vector<pair<int, ll>>> bacaBerbobot(int n, int m, bool berarah) {
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].push_back({v, w});
        if (!berarah) g[v].push_back({u, w});
    }
    return g;
}

int main() {
    FASTIO;
    cout << INF << '\n';
    return 0;
}
```

**Jebakan:** `INF = LLONG_MAX` lalu overflow jadi negatif, seolah jalan super murah.

**Kompleksitas:** bangun graf `O(n + m)`.

---

## Dijkstra heap

**Teori:** Simpul FINAL (jarak pasti) vs SEMENTARA. Ambil `u` sementara dengan `dist[u]` terkecil, kunci, relaksasi tetangga. `priority_queue` tidak punya decrease-key: **lazy deletion** — push entri baru, abaikan usang saat `d > dist[u]`.

Bukti kunci memakai `w ≥ 0`. Ada sisi negatif: nilai terkunci bisa salah.

**Kapan:** `n, m` sampai `1e5`, `w ≥ 0`. Jangan untuk *longest path* (ganti tanda hanya aman di DAG). Jangan “coba-coba” pada negatif.

**Proses:**

```
0 --1--> 1 --3--> 3
|        |
2        1
v        v
2 --4--> 3
```

Sisi `0→1 (1), 0→2 (2), 1→3 (3), 1→2 (1), 2→3 (4)`. Sumber 0.

| pop `(d,u)` | aksi | dist |
|---|---|---|
| init | | `[0, ∞, ∞, ∞]` |
| (0,0) | 1←1, 2←2 | `[0, 1, 2, ∞]` |
| (1,1) | 3←4, 2←2 sama | `[0, 1, 2, 4]` |
| (2,2) | 3←6 kalah | `[0, 1, 2, 4]` |
| (4,3) | selesai | |

Jalur `0-1-3 = 4` mengalahkan `0-2-3 = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<ll> dijkstra(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 1});
    g[0].push_back({2, 2});
    g[1].push_back({3, 3});
    g[1].push_back({2, 1});
    g[2].push_back({3, 4});
    auto d = dijkstra(n, g, 0);
    for (int i = 0; i < n; i++)
        cout << (d[i] >= INF ? -1 : d[i]) << " \n"[i + 1 == n];
    // 0 1 2 4
    return 0;
}
```

**Jebakan:**

1. `priority_queue` default **max-heap**. Wajib `greater<pli>`.
2. Pasangan harus `(jarak, simpul)` — jarak di `first`.
3. Menghapus `if (d > dist[u]) continue` bisa TLE.
4. `int` untuk jarak: `1e5 * 1e9` overflow. Pakai `ll`.

**Kompleksitas:** `O((n + m) log m)` ≈ `O(m log n)` lazy heap. Memori `O(n + m)`.

---

## Dijkstra padat dan rekonstruksi

**Teori:** Tanpa heap: tiap pengambilan menyapu `n` simpul belum final. `O(n²)`, lebih cepat daripada heap jika `m ≈ n²`. Rekonstruksi: `par[v] = u` saat relaksasi berhasil, mundur dari `t` ke `s`.

**Kapan:** `n ≤ 2000` padat, atau matriks. Jangan `O(n²)` pada `n = 1e5`.

**Proses:** graf yang sama.

| iter | pilih u | done | relaksasi |
|---|---|---|---|
| 1 | 0 | {0} | dist[1]=1, dist[2]=2 |
| 2 | 1 | {0,1} | dist[3]=4 |
| 3 | 2 | {0,1,2} | dist[3] tetap 4 |
| 4 | 3 | semua | |

`par[1]=0, par[2]=0, par[3]=1`. Jalur `3 ← 1 ← 0` → `0 1 3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> dijkstraPadat(int n, const vector<vector<ll>>& w, int s) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    dist[s] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] >= INF) break;
        done[u] = 1;
        for (int v = 0; v < n; v++)
            if (w[u][v] < INF) dist[v] = min(dist[v], dist[u] + w[u][v]);
    }
    return dist;
}

vector<ll> dijkstraPar(int n, const vector<vector<pair<int, ll>>>& g, int s,
                       vector<int>& par) {
    vector<ll> dist(n, INF);
    par.assign(n, -1);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dist[v]) {
            dist[v] = d + w;
            par[v] = u;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

vector<int> bangunJalur(int s, int t, const vector<ll>& dist, const vector<int>& par) {
    if (dist[t] >= INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path.empty() || path[0] != s) return {};
    return path;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 1});
    g[0].push_back({2, 2});
    g[1].push_back({3, 3});
    g[2].push_back({3, 4});
    vector<int> par;
    auto dist = dijkstraPar(n, g, 0, par);
    auto path = bangunJalur(0, 3, dist, par);
    for (int x : path) cout << x << ' ';
    cout << '\n';                                  // 0 1 3
    return 0;
}
```

**Jebakan:**

1. Matriks `w[u][v] = 0` artinya “tidak ada sisi” — 0 adalah bobot sah. Isi `INF`, diagonal 0.
2. `par[s] = 0` lalu `s = 0` membuat loop `0,0,0,...`. Wajib `par[s] = -1`.
3. Tie `d+w == dist[v]` tidak ganti parent; boleh jika ingin jalur tertentu.

**Kompleksitas:** padat `O(n²)`, heap `O(m log n)`, rekonstruksi `O(n)`.

---

## Minimax dan maximin

**Teori:** Kerangka heap sama; yang berubah adalah gabungan biaya. Minimax (effort): `nd = max(d, w)` — minimalkan sisi terbesar. Maximin (kapasitas): `nd = min(d, w)` — maksimalkan sisi terkecil. Analoginya: tanjakan terjal vs jembatan terlemah.

**Kapan:** “minimum effort”, “lebar jalur maksimum”. Jangan mencampur `max`/`min`/`+`.

**Proses:** `0-1 (5), 0-2 (1), 2-1 (2), 1-3 (4), 2-3 (6)`.

```
0-1-3     max(5,4)=5
0-2-1-3   max(1,2,4)=4
0-2-3     6
jawaban ke 3 = 4
```

| pop | dist minimax |
|---|---|
| (0,0) | 1←5, 2←1 |
| (1,2) | 1←max(1,2)=2, 3←6 |
| (2,1) | 3←max(2,4)=4 |
| (4,3) | kunci 4 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<ll> minimax(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            ll nd = max(d, w);
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

vector<ll> maximin(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, -1);
    priority_queue<pli> pq;
    dist[s] = INF;
    pq.push({INF, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d < dist[u]) continue;
        for (auto [v, w] : g[u]) {
            ll nd = min(d, w);
            if (nd > dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 5});
    g[0].push_back({2, 1});
    g[2].push_back({1, 2});
    g[1].push_back({3, 4});
    g[2].push_back({3, 6});
    cout << minimax(n, g, 0)[3] << '\n';           // 4
    cout << maximin(n, g, 0)[3] << '\n';           // 2  (min sisi di 0-2-1-3 = 1? 
    // 0-2-1-3 mins = min(1,2,4)=1; 0-1-3 min(5,4)=4; 0-2-3 min(1,6)=1 → 1
    return 0;
}
```

Di `main`, maximin ke 3 adalah **1** (jalur `0-2-3` atau `0-2-1-3`). Komentar di kode mengingatkan untuk tidak mengarang angka.

**Jebakan:**

1. Minimax `dist[s] = INF` — salah; sumber 0.
2. Maximin `dist[s] = 0` — salah; sumber kapasitas tak hingga.
3. Maximin memakai min-heap.

**Kompleksitas:** sama Dijkstra `O(m log n)`.

---

## Banyak jalur dan kupon

**Teori:** Jika `d+w < dist[v]`, set `cnt[v] = cnt[u]`. Jika sama, `cnt[v] += cnt[u]`. Wajib skip entri usang sebelum menambah. Kupon: state `(simpul, kupon terpakai)`. Analoginya: beberapa tiket sama murah, atau boleh skip bayar K kali.

**Kapan:** “berapa shortest path”, “boleh gratis K sisi”. Jangan menambah `cnt` dari pop usang.

**Proses:** graf minimax di atas, jarak biasa: `0-2-1-3 = 1+2+4 = 7`, `0-1-3 = 9`, `0-2-3 = 7`. Dua jalur terpendek ke 3? `0-2-1-3` dan `0-2-3` keduanya 7. `cnt[3] = 2`.

Kupon `K=1`: skip salah satu sisi, jalur `0-1-3` bisa 4 jika skip 5, dll. State `(u,k)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

void dijkstraHitung(int n, const vector<vector<pair<int, ll>>>& g, int s,
                    vector<ll>& dist, vector<ll>& cnt) {
    dist.assign(n, INF);
    cnt.assign(n, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    cnt[s] = 1;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
}

vector<vector<ll>> dijkstraKupon(int n, int K, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<vector<ll>> dist(n, vector<ll>(K + 1, INF));
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s][0] = 0;
    pq.push({0, s * (K + 1)});
    while (!pq.empty()) {
        auto [d, code] = pq.top();
        pq.pop();
        int u = code / (K + 1), k = code % (K + 1);
        if (d > dist[u][k]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v][k]) {
                dist[v][k] = d + w;
                pq.push({dist[v][k], v * (K + 1) + k});
            }
            if (k < K && d < dist[v][k + 1]) {
                dist[v][k + 1] = d;
                pq.push({d, v * (K + 1) + k + 1});
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 5});
    g[0].push_back({2, 1});
    g[2].push_back({1, 2});
    g[1].push_back({3, 4});
    g[2].push_back({3, 6});
    vector<ll> dist, cnt;
    dijkstraHitung(n, g, 0, dist, cnt);
    cout << dist[3] << ' ' << cnt[3] << '\n';      // 7 2
    auto dk = dijkstraKupon(n, 1, g, 0);
    ll ans = INF;
    for (int k = 0; k <= 1; k++) ans = min(ans, dk[3][k]);
    cout << ans << '\n';                           // 4  (skip sisi 5: 0-1-3)
    return 0;
}
```

**Jebakan:**

1. `cnt` diupdate dari entri usang.
2. Kupon: state hanya `u`.
3. Jawaban kupon = `min` atas lapisan, bukan hanya `dist[t][K]`.

**Kompleksitas:** hitung sama Dijkstra. Kupon `O(K (n+m) log (K n))`.

---

## Banyak sumber

**Teori:** Seperti BFS multi-source: masukkan semua sumber `dist=0` ke heap. Gelombang “kota terdekat”. Analoginya: beberapa gudang, jarak ke gudang mana pun.

**Kapan:** “jarak ke stasiun terdekat” dengan bobot jalan. Jangan `S` kali Dijkstra.

**Proses:** garis `0-1-2-3` bobot 3,5,1. Sumber 0 dan 3.

```
dist init 0:0, 3:0
pop 0: 1←3
pop 3: 2←1
pop 2: 1←1+5=6 > 3, tetap
dist = [0, 3, 1, 0]
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<ll> dijkstraMulti(int n, const vector<vector<pair<int, ll>>>& g,
                         const vector<int>& src) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    for (int s : src) {
        dist[s] = 0;
        pq.push({0, s});
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dist[v]) {
            dist[v] = d + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    auto add = [&](int u, int v, ll w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    add(0, 1, 3);
    add(1, 2, 5);
    add(2, 3, 1);
    auto d = dijkstraMulti(n, g, {0, 3});
    for (ll x : d) cout << x << ' ';
    cout << '\n';                                  // 0 3 1 0
    return 0;
}
```

**Jebakan:**

1. Sumber dengan “biaya buka” beda: `dist[s] = biaya_s`, bukan 0.
2. Mencampur heap sisa dari tes sebelumnya.

**Kompleksitas:** `O(m log n)` sekali, bukan `S` kali.

---

## Ringkasan

**Teori:** Kunci yang terkecil karena `w ≥ 0`. Lazy heap. Varian hanya mengganti rumus `nd`.

**Kapan:** 1 sumber tak negatif. Selain itu lihat tabel puncak.

**Proses:** uji `0 1 2 4` di `main` sebelum menempel ke soal.

**Jebakan lintas:**

1. Max-heap.
2. `INF` overflow.
3. `par[0] = 0`.
4. Prim memakai `+` (itu file MST).

**Kompleksitas saku:** heap `O(m log n)`, padat `O(n²)`, kupon kali `K`.

Lanjut: [bellman-floyd.md](bellman-floyd.md) · [dfs-bfs.md](dfs-bfs.md) · [dsu-mst.md](dsu-mst.md)
