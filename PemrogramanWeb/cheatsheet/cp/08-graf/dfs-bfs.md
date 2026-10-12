# DFS, BFS, dan 0-1 BFS

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **113**. Dua telusur dasar graf tanpa bobot sebarang, plus representasi dan 0-1 BFS. Flood/komponen, siklus, topo, Euler, dan BFS-state punya file sendiri di folder ini.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**, fungsi terpisah, `main` hanya menguji.

## Daftar isi

- [Cara pilih senjata](#cara-pilih-senjata)
- [Representasi graf](#representasi-graf)
- [DFS](#dfs)
- [DFS waktu masuk-keluar](#dfs-waktu-masuk-keluar)
- [BFS](#bfs)
- [BFS banyak sumber](#bfs-banyak-sumber)
- [0-1 BFS](#0-1-bfs)
- [Ringkasan](#ringkasan)

---

## Cara pilih senjata

**Teori:** Graf adalah pasangan `(V, E)`. Soal CP hampir selalu memberi `n` simpul dan `m` sisi, lalu meminta jarak, urutan kunjungan, atau “apakah tercapai”. DFS masuk sedalam mungkin lalu mundur (benang di labirin). BFS menyebar lapis demi lapis (gelombang air). Kalau sisi hanya berbobot 0 atau 1, deque menggantikan antrean: sisi 0 masuk depan, sisi 1 masuk belakang. Kalau bobot sebarang tak negatif, lompat ke [dijkstra.md](dijkstra.md).

**Kapan:** Pakai file ini jika soal bicara tetangga, labirin tanpa biaya beda, atau “minimum langkah”. Jangan memaksa DFS/BFS jika yang diminta jarak berbobot sebarang, MST, aliran, atau SCC.

| Yang diminta | Alat | File |
|---|---|---|
| Jarak sisi-sama | BFS | ini |
| Bobot hanya 0 dan 1 | 0-1 BFS | ini |
| Komponen / pulau | DFS atau BFS | [flood-komponen.md](flood-komponen.md) |
| Siklus / 2 warna | DFS 2/3 warna | [siklus-bipartit.md](siklus-bipartit.md) |
| Prasyarat / DP DAG | Kahn | [topo-dp-dag.md](topo-dp-dag.md) |
| Setiap sisi sekali | Hierholzer | [euler.md](euler.md) |
| Simpul = keadaan | BFS state | [bfs-state.md](bfs-state.md) |
| Bobot `≥ 0` sebarang | Dijkstra | [dijkstra.md](dijkstra.md) |

**Proses:** Baca `n m`, tentukan berarah atau tidak, bangun daftar ketetanggaan, baru pilih senjata. Graf uji sepanjang file: 6 simpul, sisi tak berarah `0-1, 0-2, 1-3, 1-4, 2-5` kecuali disebut lain.

```
    0
   / \
  1   2
 / \   \
3   4   5
```

**Kode:** kerangka baca input.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<int>> bacaTakBerarah(int n, int m) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

vector<vector<int>> bacaBerarah(int n, int m) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }
    return g;
}

int main() {
    FASTIO;
    int n, m;
    if (!(cin >> n >> m)) return 0;
    auto g = bacaTakBerarah(n, m);
    cout << n << ' ' << (g.empty() ? 0 : (int)g[0].size()) << '\n';
    return 0;
}
```

**Jebakan:**

1. Lupa `--u; --v;` jika soal 1-indexed — akses `g[n]` keluar batas.
2. Menambah sisi balik pada graf yang seharusnya berarah.
3. File ini selalu `g(n)`, bukan `g(n+1)`.
4. Self-loop dan multi-sisi: DFS/BFS tetap jalan, Euler dan deteksi siklus harus sadar.

**Kompleksitas:** membangun list `O(n + m)` waktu dan memori.

---

## Representasi graf

**Teori:** Tiga cara menyimpan sisi. **Daftar ketetanggaan** `vector<vector<int>>` adalah buku alamat: tiap orang punya daftar temannya. **Matriks** `adj[u][v]` adalah kotak `n × n`. **Daftar sisi** `{u, v, w}` nyaman diurutkan (Kruskal). List menang di graf jarang (`m ≪ n²`), yaitu hampir semua soal kontes.

**Kapan:** List untuk DFS/BFS/Dijkstra. Matriks untuk Floyd atau `n ≤ 400` padat. Daftar sisi untuk Kruskal. Jangan matriks `n = 1e5`: memori `n²` meledak.

**Proses:** graf 4 simpul, sisi `0-1, 0-2, 1-2, 1-3`.

```
    0
   / \
  1---2
  |
  3
```

List (urutan baca sisi):

```
g[0] = {1, 2}
g[1] = {0, 2, 3}
g[2] = {0, 1}
g[3] = {1}
```

Matriks (1 = ada sisi):

```
    0 1 2 3
0   0 1 1 0
1   1 0 1 1
2   1 1 0 0
3   0 1 0 0
```

Daftar sisi: `(0,1), (0,2), (1,2), (1,3)` plus pasangan balik jika tak berarah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Sisi { int u, v; ll w; };

vector<vector<int>> dariSisiTakBerarah(int n, const vector<Sisi>& sisi) {
    vector<vector<int>> g(n);
    for (auto e : sisi) {
        g[e.u].push_back(e.v);
        g[e.v].push_back(e.u);
    }
    return g;
}

vector<vector<pair<int, ll>>> dariSisiBerbobot(int n, const vector<Sisi>& sisi, bool berarah) {
    vector<vector<pair<int, ll>>> g(n);
    for (auto e : sisi) {
        g[e.u].push_back({e.v, e.w});
        if (!berarah) g[e.v].push_back({e.u, e.w});
    }
    return g;
}

int derajat(const vector<vector<int>>& g, int u) {
    return (int)g[u].size();
}

int main() {
    FASTIO;
    vector<Sisi> sisi = {{0, 1, 1}, {0, 2, 1}, {1, 2, 1}, {1, 3, 1}};
    auto g = dariSisiTakBerarah(4, sisi);
    cout << derajat(g, 1) << '\n';                 // 3
    cout << g[0].size() << ' ' << g[3].size() << '\n'; // 2 1
    return 0;
}
```

**Jebakan:**

1. Graf berbobot disimpan `vector<int>` lalu bobot hilang — pakai `pair<int,ll>`.
2. Matriks tak berarah harus simetris.
3. Iterasi `for (int v = 0; v < n; v++)` pada list: list bukan matriks.
4. `g.assign(n, {})` setelah kebiasaan `g(n+1)` orang lain.

**Kompleksitas:** list `O(n + m)` memori, cek sisi `O(deg(u))`. Matriks `O(n²)` memori, cek sisi `O(1)`.

---

## DFS

**Teori:** DFS (Depth-First Search) memilih satu tetangga, masuk sedalam mungkin, baru mundur ke persimpangan yang masih punya cabang. Analoginya labirin plus gulungan benang: benang adalah *call stack*. Setiap simpul ditandai `vis` tepat sekali, setiap sisi ditinjau konstan kali. Urutan kunjungan **bukan** urutan jarak — itu kerja BFS.

**Kapan:** komponen, siklus, subtree, waktu masuk-keluar, backtracking, jembatan (lihat [scc-bridge.md](scc-bridge.md)), topo versi DFS. Jangan untuk jarak terpendek tak berbobot: DFS bisa menemukan jalur panjang dulu.

**Proses:** mulai dari 0, tetangga diurutkan naik. Graf pohon di puncak file.

| aksi | stack panggilan | kunjung |
|---|---|---|
| masuk 0 | `[0]` | 0 |
| masuk 1 | `[0, 1]` | 0 1 |
| masuk 3 | `[0, 1, 3]` | 0 1 3 |
| 3 buntu, mundur | `[0, 1]` | |
| masuk 4 | `[0, 1, 4]` | 0 1 3 4 |
| mundur ke 0 | `[0]` | |
| masuk 2 | `[0, 2]` | 0 1 3 4 2 |
| masuk 5 | `[0, 2, 5]` | 0 1 3 4 2 5 |

Preorder: `0, 1, 3, 4, 2, 5`. BFS dari 0 akan `0, 1, 2, 3, 4, 5`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void dfsRek(int u, const vector<vector<int>>& g, vector<int>& vis, vector<int>& urut) {
    vis[u] = 1;
    urut.push_back(u);
    for (int v : g[u])
        if (!vis[v]) dfsRek(v, g, vis, urut);
}

vector<int> dfsDari(int n, const vector<vector<int>>& g, int s) {
    vector<int> vis(n), urut;
    dfsRek(s, g, vis, urut);
    return urut;
}

vector<int> dfsIteratif(int n, const vector<vector<int>>& g, int s) {
    vector<int> vis(n), urut;
    stack<int> st;
    st.push(s);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        urut.push_back(u);
        for (int i = (int)g[u].size() - 1; i >= 0; i--) {
            int v = g[u][i];
            if (!vis[v]) st.push(v);
        }
    }
    return urut;
}

vector<int> dfsSemuaKomponen(int n, const vector<vector<int>>& g) {
    vector<int> vis(n), urut;
    for (int s = 0; s < n; s++)
        if (!vis[s]) dfsRek(s, g, vis, urut);
    return urut;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {
        {1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}
    };
    auto a = dfsDari(6, g, 0);
    for (int x : a) cout << x << ' ';
    cout << '\n';                                  // 0 1 3 4 2 5
    return 0;
}
```

**Jebakan:**

1. Rekursi pada `n = 1e5` rantai lurus: *stack overflow*. Pakai DFS iteratif.
2. Lupa `vis`: loop tak hingga pada graf berkisi.
3. DFS iteratif mendorong kiri-ke-kanan tanpa membalik: urutan beda dari rekursif (boleh, asal tidak diuji persis).
4. Hanya DFS dari simpul 0 pada graf tak terhubung: komponen lain tidak terjamah.

**Kompleksitas:** waktu `O(n + m)`, memori `O(n + m)` plus stack `O(n)` kasus terburuk.

---

## DFS waktu masuk-keluar

**Teori:** Setiap simpul mendapat dua cap: `tin[u]` saat pertama kali masuk, `tout[u]` saat semua keturunan selesai. Pada pohon DFS, subtree `u` adalah interval `[tin[u], tout[u])`. Analoginya nomor antrian masuk-keluar gedung: siapa pun yang masuk setelah kamu dan keluar sebelum kamu berada di “gedungmu”. Fondasi LCA, Euler tour, query subtree, jembatan, dan SCC.

**Kapan:** “apakah `v` keturunan `u`?”, ukuran subtree, meratakan pohon. Jangan mengira interval selalu subtree di graf umum — itu subtree **pohon DFS**, bukan tetangga silang.

**Proses:** pohon yang sama. Timer mulai 0, `tout` dicatat setelah anak selesai.

| peristiwa | timer | tin/tout |
|---|---|---|
| masuk 0 | 0 | `tin[0]=0` |
| masuk 1 | 1 | `tin[1]=1` |
| masuk 3 | 2 | `tin[3]=2` |
| keluar 3 | 3 | `tout[3]=3` |
| masuk 4 | 4 | `tin[4]=4` |
| keluar 4 | 5 | `tout[4]=5` |
| keluar 1 | 6 | `tout[1]=6` |
| masuk 2 | 7 | `tin[2]=7` |
| masuk 5 | 8 | `tin[5]=8` |
| keluar 5 | 9 | `tout[5]=9` |
| keluar 2 | 10 | `tout[2]=10` |
| keluar 0 | 11 | `tout[0]=11` |

`3` keturunan `1` karena `tin[1] ≤ tin[3] < tout[1]` → `1 ≤ 2 < 6`. `2` bukan keturunan `1`: `tin[2]=7` tidak `< 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DfsWaktu {
    vector<int> tin, tout, par, sz;
    int timer = 0;

    void jalan(int u, int p, const vector<vector<int>>& g) {
        par[u] = p;
        tin[u] = timer++;
        sz[u] = 1;
        for (int v : g[u]) if (v != p) {
            jalan(v, u, g);
            sz[u] += sz[v];
        }
        tout[u] = timer;
    }

    DfsWaktu(int n, const vector<vector<int>>& g, int akar)
        : tin(n), tout(n), par(n, -1), sz(n) {
        jalan(akar, -1, g);
    }

    bool keturunan(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

int main() {
    FASTIO;
    vector<vector<int>> g = {
        {1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}
    };
    DfsWaktu d(6, g, 0);
    cout << d.keturunan(1, 3) << ' ' << d.keturunan(1, 2) << '\n'; // 1 0
    cout << d.sz[0] << ' ' << d.sz[1] << '\n';                     // 6 3
    return 0;
}
```

**Jebakan:**

1. Membandingkan `tout` dengan `<` vs `≤` tergantung kapan `tout` diisi — samakan konvensi.
2. Memanggil `keturunan` antar komponen: `tin` overlap atau tidak terisi.
3. Di graf berkisi, wajib skip parent.
4. `sz[u]` pada graf umum adalah ukuran **pohon DFS**, bukan komponen jika ada back-edge.

**Kompleksitas:** `O(n + m)` satu DFS, query keturunan `O(1)`.

---

## BFS

**Teori:** BFS memakai antrean FIFO. Simpul keluar dalam urutan jarak (jumlah sisi) dari sumber. Analoginya gelombang air: genangan mencapai ubin jarak 1, baru jarak 2. Bukti: pertama kali sebuah simpul masuk antrean, semua jalur yang lebih pendek sudah diproses (antrean monoton terhadap jarak). Maka `dist[v]` saat pertama kali ditulis adalah jarak terpendek pada graf **tak berbobot**.

**Kapan:** jarak sisi-sama, labirin, minimum langkah, pewarnaan lapis. Jangan jika sisi berbobot beda — jalur 5 sisi berbobot 1 lebih pendek dari 1 sisi berbobot 100, tetapi BFS menganggap yang 1 sisi “selesai” dulu.

**Proses:** graf `0-1, 0-2, 1-3, 2-3, 3-4`, sumber 0.

```
0 — 1 — 3 — 4
 \     /
  — 2 —
```

| langkah | keluar | antrean setelah | dist |
|---|---|---|---|
| init | — | `[0]` | 0:0 |
| 1 | 0 | `[1, 2]` | 1:1, 2:1 |
| 2 | 1 | `[2, 3]` | 3:2 |
| 3 | 2 | `[3]` | 3 sudah vis |
| 4 | 3 | `[4]` | 4:3 |
| 5 | 4 | `[]` | selesai |

`dist = [0, 1, 1, 2, 3]`. Jalur `0-2-3-4` dan `0-1-3-4` sama panjang 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const int INF = 1e9;

vector<int> bfsJarak(int n, const vector<vector<int>>& g, int s) {
    vector<int> dist(n, INF);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}

vector<int> bfsJalur(int n, const vector<vector<int>>& g, int s, int t) {
    vector<int> dist(n, INF), par(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            par[v] = u;
            q.push(v);
        }
    }
    if (dist[t] == INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int bfsBanyakJalur(int n, const vector<vector<int>>& g, int s, int t, int mod) {
    vector<int> dist(n, INF);
    vector<ll> cara(n, 0);
    queue<int> q;
    dist[s] = 0;
    cara[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                cara[v] = cara[u];
                q.push(v);
            } else if (dist[v] == dist[u] + 1) {
                cara[v] = (cara[v] + cara[u]) % mod;
            }
        }
    }
    return dist[t] == INF ? 0 : (int)cara[t];
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1, 2}, {0, 3}, {0, 3}, {1, 2, 4}, {3}};
    auto d = bfsJarak(5, g, 0);
    for (int x : d) cout << x << ' ';
    cout << '\n';                                  // 0 1 1 2 3
    auto p = bfsJalur(5, g, 0, 4);
    for (int x : p) cout << x << ' ';
    cout << '\n';                                  // 0 1 3 4  (atau 0 2 3 4)
    cout << bfsBanyakJalur(5, g, 0, 4, 1000000007) << '\n'; // 2
    return 0;
}
```

**Jebakan:**

1. Menandai `vis` saat *pop* tanpa cek `dist==INF` saat *push*: simpul masuk antrean berkali-kali.
2. Memakai BFS pada sisi berbobot beda.
3. Rekonstruksi: lupa `reverse`, atau `par[s]` bukan `-1` sehingga loop.
4. Multi-source: masukkan **semua** sumber di awal, bukan BFS terpisah lalu `min`.

**Kompleksitas:** `O(n + m)` waktu dan memori.

---

## BFS banyak sumber

**Teori:** Jika banyak sumber “sudah terbakar” di menit 0, masukkan semuanya ke antrean dengan `dist = 0`. Gelombang menyebar dari semua sumber sekaligus. Analoginya beberapa api di hutan: waktu habisnya sebuah pohon adalah jarak ke api **terdekat**, bukan ke api pertama yang kamu simulasi.

**Kapan:** “jarak ke tembok terdekat”, “berapa menit sampai semua sel basah”, multi-exit labirin. Jangan menjalankan `k` kali BFS lalu ambil min: itu `O(k(n+m))`.

**Proses:** garis 5 sel `0-1-2-3-4`, sumber di 0 dan 4.

| langkah | keluar | antrean | dist |
|---|---|---|---|
| init | — | `[0, 4]` | `[0, ∞, ∞, ∞, 0]` |
| 1 | 0 | `[4, 1]` | 1 ← 1 |
| 2 | 4 | `[1, 3]` | 3 ← 1 |
| 3 | 1 | `[3, 2]` | 2 ← 2 |
| 4 | 3 | `[2]` | 2 sudah 2, sama |
| 5 | 2 | `[]` | `[0, 1, 2, 1, 0]` |

Sel tengah berjarak 2 ke kedua sumber.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const int INF = 1e9;

vector<int> bfsMulti(int n, const vector<vector<int>>& g, const vector<int>& src) {
    vector<int> dist(n, INF);
    queue<int> q;
    for (int s : src) {
        dist[s] = 0;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1}, {0, 2}, {1, 3}, {2, 4}, {3}};
    auto d = bfsMulti(5, g, {0, 4});
    for (int x : d) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 1 0
    return 0;
}
```

**Jebakan:**

1. Sumber dobel di antrean: cek `dist[s] == INF` sebelum push, atau set dulu semua `dist`.
2. Mencampur `dist` BFS lama tanpa `assign(INF)`.
3. Grid: sumber adalah semua sel `'#'` atau semua pintu — kumpulkan dulu, baru satu BFS.

**Kompleksitas:** tetap `O(n + m)`.

---

## 0-1 BFS

**Teori:** Jika setiap sisi berbobot **0 atau 1**, jarak masih dihitung seperti BFS, tetapi antrean diganti **deque**. Sisi 0 masuk **depan** (jarak tidak naik), sisi 1 masuk **belakang** (jarak +1). Deque selalu terurut non-menurun, jadi yang keluar depan sudah final. Analoginya: jalan biasa biaya 1, teleport biaya 0. Teleport diproses “sekarang juga”. Ini kasus khusus Dijkstra yang `O(n + m)` tanpa heap.

**Kapan:** grid “jalan vs portal”, sisi biasa vs sisi gratis, dua jenis biaya. Jangan jika ada bobot 2, 3, … — itu Dijkstra atau Dial. Jangan Dijkstra heap jika bobot hanya 0/1: 0-1 BFS lebih cepat. Varian state (kunci + sel mahal) ada di [bfs-state.md](bfs-state.md).

**Proses:** sisi `0→1 (1), 0→2 (0), 2→1 (0), 1→3 (1), 2→3 (1)`, sumber 0.

| deque `(jarak, simpul)` | pop | relaksasi |
|---|---|---|
| `[(0,0)]` | 0 | 1 ← 1 belakang, 2 ← 0 depan |
| `[(0,2), (1,1)]` | 2 | 1 ← 0 lebih baik, depan; 3 ← 1 belakang |
| `[(0,1), (1,1 usang), (1,3)]` | 1 | dist 0, ke 3: 1 tidak lebih baik |
| `[(1,1), (1,3)]` | 1 usang skip | |
| `[(1,3)]` | 3 | selesai |

`dist = [0, 0, 0, 1]`. Jalur terbaik ke 1 adalah `0-2-1` (dua teleport), bukan `0-1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfs01(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

vector<int> jalur01(int n, const vector<vector<pair<int, int>>>& g, int s, int t) {
    vector<ll> dist(n, INF);
    vector<int> par(n, -1);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            par[v] = u;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    if (dist[t] >= INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

vector<ll> bfs01Grid(const vector<string>& a, pair<int, int> S, char mahal) {
    int R = (int)a.size(), C = (int)a[0].size();
    auto id = [&](int r, int c) { return r * C + c; };
    vector<ll> dist(R * C, INF);
    deque<int> dq;
    dist[id(S.first, S.second)] = 0;
    dq.push_front(id(S.first, S.second));
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int r = u / C, c = u % C;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || a[nr][nc] == '#') continue;
            int w = (a[nr][nc] == mahal);
            int v = id(nr, nc);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(4);
    g[0].push_back({1, 1});
    g[0].push_back({2, 0});
    g[2].push_back({1, 0});
    g[1].push_back({3, 1});
    g[2].push_back({3, 1});
    auto d = bfs01(4, g, 0);
    for (ll x : d) cout << x << ' ';
    cout << '\n';                                  // 0 0 0 1
    return 0;
}
```

**Jebakan:**

1. `push_back` untuk bobot 0: urutan deque rusak, jawaban bisa salah.
2. Bobot di luar `{0,1}` lolos tanpa assert.
3. Tidak skip entri usang: masih benar (relaksasi ketat melindungi), tetapi deque lebih gemuk.
4. Grid: biaya diletakkan di sel asal, bukan tujuan — off-by-one klasik.

**Kompleksitas:** `O(n + m)` waktu dan memori.

---

## Ringkasan

**Teori:** DFS membawa cap waktu dan sifat struktural. BFS membawa jarak sisi-sama. Deque membawa bobot 0/1. Ketiganya `O(n + m)`.

**Kapan:** soal tanpa bobot sebarang. Kalau muncul `w_i` sampai `1e9`, buka [dijkstra.md](dijkstra.md).

**Proses saku:**

1. Gambar 4–6 simpul, telusuri tangan, cocokkan `vis`/`dist`.
2. Tulis fungsi, uji graf kecil di `main`.
3. Baru tempel ke soal.

**Jebakan lintas topik:**

1. Stack rekursi `1e5`.
2. Graf tidak terhubung: loop `for s = 0..n-1`.
3. Arah sisi vs “berteman” / “mengikuti”.
4. BFS vs Dijkstra; 0-1 BFS vs heap.

**Kompleksitas saku:** hampir semua `O(n + m)`. Ruang state di [bfs-state.md](bfs-state.md) adalah `O(|S|)`.

Lanjut: [flood-komponen.md](flood-komponen.md) · [siklus-bipartit.md](siklus-bipartit.md) · [dijkstra.md](dijkstra.md)
