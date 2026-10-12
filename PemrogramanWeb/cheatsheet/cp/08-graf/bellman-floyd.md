# Bellman-Ford, SPFA, Floyd-Warshall

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **129–131**. Bobot negatif, deteksi siklus negatif, semua pasangan. Dijkstra hanya untuk `w ≥ 0` di [dijkstra.md](dijkstra.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Bellman-Ford](#bellman-ford)
- [Tandai minus tak hingga](#tandai-minus-tak-hingga)
- [SPFA](#spfa)
- [Kendala selisih](#kendala-selisih)
- [Floyd-Warshall](#floyd-warshall)
- [Johnson singkat](#johnson-singkat)
- [Ringkasan](#ringkasan)

---

## Bellman-Ford

**Teori:** Relaksasi semua sisi diulang `n-1` kali. Setelah `i` putaran, `dist[v]` benar untuk semua jalur paling banyak `i` sisi (jika tidak ada siklus negatif tercapai). Analoginya: berita harga disebar jam demi jam; setelah `n-1` hop, jalur sederhana paling panjang sudah tertampung. Putaran ke-`n` yang masih merelaksasi = siklus negatif **tercapai dari sumber** (atau dari simpul berhingga).

**Kapan:** ada bobot negatif, deteksi siklus negatif, kendala selisih. Jangan default: `O(n m)` TLE pada `n,m = 1e5`. Jangan Dijkstra “dengan harapan” pada negatif.

**Proses:** sisi `0→1 (4), 0→2 (5), 1→2 (−3), 2→3 (1), 1→3 (4)`, sumber 0. Tanpa siklus negatif.

Putaran 1 (urut sisi):

| sisi | dist baru |
|---|---|
| 0→1 | 4 |
| 0→2 | 5 |
| 1→2 | 4+(−3)=1 |
| 2→3 | 1+1=2 |
| 1→3 | 8, kalah dari 2 |

`dist = [0, 4, 1, 2]`. Putaran 2 diam. Tambah `3→1 (−4)`: siklus `1-2-3-1` bobot −6. Putaran ke-`n` masih berubah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

pair<vector<ll>, bool> bellman(int n, const vector<Edge>& e, int s) {
    vector<ll> dist(n, INF);
    dist[s] = 0;
    bool siklusNeg = false;
    for (int it = 0; it < n; it++) {
        bool ubah = false;
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ubah = true;
                if (it == n - 1) siklusNeg = true;
            }
        }
        if (!ubah) break;
    }
    return {dist, siklusNeg};
}

int main() {
    FASTIO;
    vector<Edge> e = {
        {0, 1, 4}, {0, 2, 5}, {1, 2, -3}, {2, 3, 1}, {1, 3, 4}
    };
    auto [d, neg] = bellman(4, e, 0);
    cout << neg << ' ' << d[3] << '\n';            // 0 2
    e.push_back({3, 1, -4});
    auto [d2, neg2] = bellman(4, e, 0);
    cout << neg2 << '\n';                          // 1
    return 0;
}
```

**Jebakan:**

1. Relaksasi dari `dist[u] == INF`: `INF + (−5)` jadi “berhingga palsu”. Skip.
2. Siklus negatif yang **tidak tercapai dari s** tidak boleh menggagalkan simpul lain.
3. `n-1` vs `n` putaran: deteksi di putaran ke-`n` (indeks `n-1`).
4. Early break sebelum putaran n jika kamu masih butuh deteksi — `break` hanya jika `!ubah`, aman.

**Kompleksitas:** `O(n m)` waktu, `O(n + m)` memori.

---

## Tandai minus tak hingga

**Teori:** Setelah terdeteksi, `dist` di simpul siklus bukan angka bermakna. Tandai simpul yang terelaksasi di putaran `n`, lalu BFS/DFS maju: semua yang tercapai dari sana adalah `-∞`. Analoginya: sekali harga bisa diturunkan tanpa batas, semua kota hilir ikut “gratis tak hingga”.

**Kapan:** soal “cetak jarak atau `−1` jika bisa −∞”. Jangan mencetak `dist` mentah setelah flag negatif.

**Proses:** graf plus `3→1 (−4)`. Simpul 1,2,3 terelaksasi di putaran 4, 0 tidak. `kena = [0,1,1,1]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

vector<int> kenaSiklusNegatif(int n, const vector<Edge>& e, int s) {
    vector<ll> dist(n, INF);
    dist[s] = 0;
    vector<int> kena(n, 0);
    for (int it = 0; it < n; it++) {
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (it == n - 1) kena[v] = 1;
            }
        }
    }
    vector<vector<int>> g(n);
    for (auto [u, v, w] : e) g[u].push_back(v);
    queue<int> q;
    for (int i = 0; i < n; i++) if (kena[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (!kena[v]) {
            kena[v] = 1;
            q.push(v);
        }
    }
    return kena;
}

int main() {
    FASTIO;
    vector<Edge> e = {
        {0, 1, 4}, {0, 2, 5}, {1, 2, -3}, {2, 3, 1}, {1, 3, 4}, {3, 1, -4}
    };
    auto k = kenaSiklusNegatif(4, e, 0);
    for (int x : k) cout << x << ' ';
    cout << '\n';                                  // 0 1 1 1
    return 0;
}
```

**Jebakan:**

1. Hanya menandai `v` di putaran n, tanpa BFS hilir: simpul di belakang siklus terlewat.
2. Mengisi `dist[v] = -INF` lalu masih merelaksasi `−INF + w` overflow.

**Kompleksitas:** `O(n m)`.

---

## SPFA

**Teori:** Bellman yang hanya merelaksasi sisi dari simpul yang baru membaik (antrean). Rata-rata cepat, terburuk `O(n m)` dan bisa dibuat TLE. Deteksi praktis: simpul masuk antrean `≥ n` kali. Analoginya: hanya stasiun yang baru dapat berita yang menyiarkan.

**Kapan:** negatif, `n` sedang, kode pendek. Jangan andalkan di juri yang punya tes anti-SPFA. Aman: Bellman jika `n m ≤ 1e8`, Dijkstra jika tidak negatif.

**Proses:** graf Bellman tanpa siklus. Antrean `[0]`.

| pop | membaik | antrean |
|---|---|---|
| 0 | 1←4, 2←5 | `[1, 2]` |
| 1 | 2←1, 3←8 | `[2, 2, 3]` |
| 2 (dist 5 usang) | skip | `[2, 3]` |
| 2 (dist 1) | 3←2 | `[3, 3]` |
| 3 | selesai | |

`inqueue` mencegah duduk dua kali **sekaligus**; boleh masuk lagi setelah keluar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

pair<vector<ll>, bool> spfa(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    vector<int> inq(n, 0), cnt(n, 0);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inq[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (!inq[v]) {
                q.push(v);
                inq[v] = 1;
                if (++cnt[v] >= n) return {dist, true};
            }
        }
    }
    return {dist, false};
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 4});
    g[0].push_back({2, 5});
    g[1].push_back({2, -3});
    g[2].push_back({3, 1});
    g[1].push_back({3, 4});
    auto [d, neg] = spfa(n, g, 0);
    cout << neg << ' ' << d[3] << '\n';            // 0 2
    return 0;
}
```

**Jebakan:**

1. Lupa `inq[v]`: antrean meledak.
2. `cnt[v] >= n` praktis, bukan satu-satunya.
3. SPFA sebagai “Dijkstra lebih cepat” pada bobot positif: heap lebih stabil.

**Kompleksitas:** rata-rata `O(k m)` `k` kecil, terburuk `O(n m)`.

---

## Kendala selisih

**Teori:** `x_v - x_u ≤ w` setara sisi `u → v` berbobot `w`. Solusi ada iff graf kendala **tanpa siklus negatif**. `x_v = dist[v]` dari dummy yang dihubungkan ke semua dengan bobot 0 adalah satu solusi. Analoginya: “B tidak boleh lebih dari 5 jam setelah A” = jalan A→B biaya 5.

**Kapan:** jadwal beda waktu, *difference constraints*. Jangan jika kendala perkalian atau XOR.

**Proses:**

```
x1 - x0 ≤ 3     sisi 0→1 (3)
x2 - x1 ≤ 2     sisi 1→2 (2)
x0 - x2 ≤ -6    sisi 2→0 (−6)
```

Siklus `0-1-2-0` bobot `3+2-6 = −1` → **mustahil**.

Ganti ketiga jadi `x0 - x2 ≤ −4` (sisi `2→0 (−4)`). Siklus `1 ≥ 0`. Dummy 3 ke 0,1,2 bobot 0. Bellman dari 3 memberi nilai `x`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

void tambahSyarat(vector<Edge>& e, int u, int v, ll w) {
    e.push_back({u, v, w}); // x[v] - x[u] <= w
}

pair<bool, vector<ll>> selesaikanKendala(int n, vector<Edge> e) {
    int s = n;
    for (int i = 0; i < n; i++) e.push_back({s, i, 0});
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;
    for (int it = 0; it < n + 1; it++) {
        bool ubah = false;
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ubah = true;
                if (it == n) return {false, {}};
            }
        }
        if (!ubah) break;
    }
    dist.pop_back();
    return {true, dist};
}

int main() {
    FASTIO;
    vector<Edge> e;
    tambahSyarat(e, 0, 1, 3);
    tambahSyarat(e, 1, 2, 2);
    tambahSyarat(e, 2, 0, -4);
    auto [ok, x] = selesaikanKendala(3, e);
    cout << ok << ' ' << x[0] << ' ' << x[1] << ' ' << x[2] << '\n';
    return 0;
}
```

**Jebakan:**

1. Arah terbalik: sisi **dari u ke v** untuk `x[v]-x[u]≤w`.
2. Lupa dummy: Bellman dari 0 tidak melihat komponen lain.
3. `x_v - x_u ≥ c` menjadi `x_u - x_v ≤ -c`.
4. `x_v = x_u` = dua sisi 0.

**Kompleksitas:** `O(n (n + m))` dengan dummy.

---

## Floyd-Warshall

**Teori:** `dp[k][i][j]` = jarak `i→j` yang hanya boleh transit di `{0..k-1}`. Transisi: `min` lewat `k` atau tidak. Loop **k di luar** wajib. Analoginya: tahun ke-`k` bandara `k` dibuka sebagai transit. `dist[i][i] < 0` = `i` mencapai siklus negatif.

**Kapan:** `n ≤ 400`, semua pasangan, *transitive closure*, minimax semua pasangan. Jangan `n = 1000`. Jangan 1 sumber saja.

**Proses:** tak berarah: `0-1:3, 0-2:8, 1-2:2, 1-3:5, 2-3:1`.

Matriks awal:

```
    0  3  8  ∞
    3  0  2  5
    8  2  0  1
    ∞  5  1  0
```

Setelah `k=1` (transit 1): `0→2` jadi `5`, `0→3` jadi `8`.
Setelah `k=2`: `0→3` jadi `6` (0-1-2-3), `1→3` jadi `3`.
Setelah `k=3`: diam. `dist[0][3] = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

void floyd(int n, vector<vector<ll>>& d) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k] < INF)
                for (int j = 0; j < n; j++)
                    if (d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

vector<vector<int>> floydPar(int n, vector<vector<ll>>& d) {
    vector<vector<int>> nxt(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) nxt[i][j] = i;
            else if (d[i][j] < INF) nxt[i][j] = j;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k] < INF)
                for (int j = 0; j < n; j++)
                    if (d[k][j] < INF && d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        nxt[i][j] = nxt[i][k];
                    }
    return nxt;
}

vector<int> jalurFloyd(int s, int t, const vector<vector<int>>& nxt) {
    if (nxt[s][t] == -1) return {};
    vector<int> path = {s};
    while (s != t) {
        s = nxt[s][t];
        path.push_back(s);
    }
    return path;
}

bool adaSiklusNegatifFloyd(int n, const vector<vector<ll>>& d) {
    for (int i = 0; i < n; i++) if (d[i][i] < 0) return true;
    return false;
}

void tutupTransitif(int n, vector<vector<int>>& reach) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (reach[i][k])
                for (int j = 0; j < n; j++)
                    reach[i][j] |= reach[k][j];
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    auto add = [&](int u, int v, ll w) {
        d[u][v] = min(d[u][v], w);
        d[v][u] = min(d[v][u], w);
    };
    add(0, 1, 3); add(0, 2, 8); add(1, 2, 2); add(1, 3, 5); add(2, 3, 1);
    auto nxt = floydPar(n, d);
    cout << d[0][3] << '\n';                       // 6
    auto p = jalurFloyd(0, 3, nxt);
    for (int x : p) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 3
    cout << adaSiklusNegatifFloyd(n, d) << '\n';
    return 0;
}
```

**Jebakan:**

1. Loop `i,j,k` — **salah**. Harus `k, i, j`.
2. Tidak mengisi `d[i][i] = 0`.
3. Multi-sisi: ambil `min`.
4. `d[i][k] + d[k][j]` tanpa cek `INF`: overflow.
5. Rekonstruksi setelah siklus negatif bisa loop — cek `d[x][x] < 0`.

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## Johnson singkat

**Teori:** Semua pasangan pada graf jarang berbobot negatif (tanpa siklus): dummy `s` sisi 0 ke semua, Bellman dari `s` memberi potensial `h`. Bobot baru `w' = w + h[u] - h[v] ≥ 0`. Dijkstra dari tiap simpul, kembalikan `dist = dist' - h[u] + h[v]`. Analoginya: geser ketinggian kota supaya tidak ada tanjakan negatif.

**Kapan:** `n ≤ 2000` jarang, ada minus, tidak ada siklus negatif. `n ≤ 400` padat → Floyd lebih pendek.

**Proses:** `0→1 (1), 1→2 (−3), 0→2 (2)`. Dummy 3. `h ≈ [0, 0, −3]`.

```
w'(0,1) = 1
w'(1,2) = 0
w'(0,2) = 5
dist' dari 0: [0, 1, 1]
kembali ke 2: 1 - 0 + (−3) = −2
```

Cocok `0-1-2 = −2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

vector<ll> dijkstraW(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
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

pair<bool, vector<vector<ll>>> johnson(int n, const vector<Edge>& e) {
    vector<Edge> ee = e;
    int s = n;
    for (int v = 0; v < n; v++) ee.push_back({s, v, 0});
    vector<ll> h(n + 1, INF);
    h[s] = 0;
    for (int it = 0; it < n + 1; it++) {
        bool ubah = false;
        for (auto [u, v, w] : ee) {
            if (h[u] >= INF) continue;
            if (h[u] + w < h[v]) {
                h[v] = h[u] + w;
                ubah = true;
                if (it == n) return {false, {}};
            }
        }
        if (!ubah) break;
    }
    vector<vector<pair<int, ll>>> g(n);
    for (auto [u, v, w] : e) g[u].push_back({v, w + h[u] - h[v]});
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for (int u = 0; u < n; u++) {
        auto dist = dijkstraW(n, g, u);
        for (int v = 0; v < n; v++)
            if (dist[v] < INF) d[u][v] = dist[v] - h[u] + h[v];
    }
    return {true, d};
}

int main() {
    FASTIO;
    vector<Edge> e = {{0, 1, 1}, {1, 2, -3}, {0, 2, 2}};
    auto [ok, d] = johnson(3, e);
    cout << ok << ' ' << d[0][2] << '\n';          // 1 -2
    return 0;
}
```

**Jebakan:**

1. Lupa `dist' - h[u] + h[v]`.
2. Dummy tidak ke semua simpul.
3. Ada siklus negatif: harus gagal di Bellman.

**Kompleksitas:** `O(n m)` Bellman + `n` Dijkstra = `O(n m log n)`, memori hasil `O(n²)`.

---

## Ringkasan

**Teori:** Bellman mengulang sisi. SPFA mengantrikan yang berubah. Floyd membuka transit `k`. Johnson menetralkan minus lalu Dijkstra.

**Kapan:** minus → Bellman; semua pasangan kecil → Floyd; jarang minus → Johnson.

**Proses:** uji `dist[3]=2` dan Floyd `6` di `main`.

**Jebakan lintas:**

1. Relaksasi dari `INF`.
2. Floyd loop bukan `k` luar.
3. Siklus negatif tercetak sebagai angka.
4. Arah kendala selisih.

**Kompleksitas saku:** Bellman/SPFA terburuk `O(n m)`, Floyd `O(n³)`, Johnson `O(n m log n)`.

Lanjut: [dsu-mst.md](dsu-mst.md) · [dijkstra.md](dijkstra.md) · [topo-dp-dag.md](topo-dp-dag.md)
