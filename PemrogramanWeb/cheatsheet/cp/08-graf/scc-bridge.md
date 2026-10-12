# SCC, jembatan, dan titik artikulasi

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **225–227**. Komponen kuat berarah, sisi/simpul kritis tak berarah. 2-SAT memakai SCC di [sat2-flow.md](sat2-flow.md). Low-link di sini.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [SCC Kosaraju](#scc-kosaraju)
- [SCC Tarjan](#scc-tarjan)
- [Kondensasi DAG](#kondensasi-dag)
- [Jembatan](#jembatan)
- [Titik artikulasi](#titik-artikulasi)
- [Bridge-tree ide](#bridge-tree-ide)
- [Ringkasan](#ringkasan)

---

## SCC Kosaraju

**Teori:** Strongly Connected Component: himpunan simpul di graf **berarah** yang setiap pasangan saling mencapai. Analoginya kota satu arah: dalam satu SCC kamu bisa putar ke semua anggota; antar SCC paling-paling satu arah. Kosaraju: (1) DFS pada `G`, catat selesai; (2) DFS pada `G^T` dalam urutan selesai terbalik. Setiap pohon DFS kedua = satu SCC.

Kenapa: waktu selesai terakhir ada di SCC sumber pada `G`. DFS pada `G^T` dari situ hanya menjangkau SCC itu.

**Kapan:** “saling kirim pesan”, kondensasi DAG, 2-SAT, “berapa sisi supaya kuat-terhubung”. Jangan pengganti komponen tak berarah.

**Proses:** sisi `0→1, 1→2, 2→0, 1→3, 3→4, 4→3`.

```
SCC A = {0,1,2}  -->  SCC B = {3,4}
```

DFS1 dari 0: 0-1-2 (2 selesai), 1 ke 3-4 (4,3 selesai), 1 selesai, 0 selesai. `order` contoh `2,4,3,1,0`. Reverse mulai 0.

`G^T`: `1→0, 2→1, 0→2, 3→1, 4→3, 3→4`.

DFS2 dari 0: `{0,1,2}`. Lalu 3: `{3,4}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Kosaraju {
    int n, ncomp = 0;
    vector<vector<int>> g, gt;
    vector<int> vis, order, comp;

    Kosaraju(int n) : n(n), g(n), gt(n) {}

    void add(int u, int v) {
        g[u].push_back(v);
        gt[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int id) {
        comp[u] = id;
        for (int v : gt[u]) if (comp[v] == -1) dfs2(v, id);
    }

    int run() {
        vis.assign(n, 0);
        order.clear();
        for (int s = 0; s < n; s++) if (!vis[s]) dfs1(s);
        comp.assign(n, -1);
        ncomp = 0;
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, ncomp++);
        }
        return ncomp;
    }
};

int main() {
    FASTIO;
    Kosaraju k(5);
    k.add(0, 1); k.add(1, 2); k.add(2, 0);
    k.add(1, 3); k.add(3, 4); k.add(4, 3);
    cout << k.run() << '\n';                       // 2
    for (int i = 0; i < 5; i++) cout << k.comp[i] << ' ';
    cout << '\n';                                  // 0 0 0 1 1  (id boleh beda)
    return 0;
}
```

**Jebakan:**

1. Lupa membangun `G^T` saat `add`.
2. DFS2 pada `G` bukan `G^T`.
3. Urutan kedua tidak dibalik.
4. Graf tak berarah: jangan Kosaraju tanpa arah.

**Kompleksitas:** `O(n + m)`.

---

## SCC Tarjan

**Teori:** Satu DFS. `disc[u]` waktu masuk, `low[u]` waktu tertua yang bisa dicapai `u` lewat pohon plus back-edge ke simpul **masih di stack**. Jika `low[u] == disc[u]`, `u` akar SCC: pop sampai `u`. Analoginya: jejak tertua rombongan adalah diri sendiri → rombongan tertutup.

**Kapan:** satu pass, low-link sama dengan jembatan. Kosaraju lebih mudah diingat. Untuk 2-SAT, nomor SCC Tarjan (naik saat pop) **terbalik** terhadap Kosaraju — lihat [sat2-flow.md](sat2-flow.md).

**Proses:** graf yang sama. DFS 0-1-2, 2→0 on-stack, `low[2]=disc[0]`, naik, 1→3-4, 4→3 on-stack, `low[3]==disc[3]` pop `{4,3}`, lalu `low[0]==disc[0]` pop `{2,1,0}`.

| u | disc | low akhir | pop |
|---|---|---|---|
| 0 | 0 | 0 | {2,1,0} |
| 1 | 1 | 0 | ikut 0 |
| 2 | 2 | 0 | ikut 0 |
| 3 | 3 | 3 | {4,3} |
| 4 | 4 | 3 | ikut 3 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct TarjanSCC {
    int n, timer = 0, ncomp = 0;
    vector<vector<int>> g;
    vector<int> disc, low, on, comp, st;

    TarjanSCC(int n) : n(n), g(n) {}
    void add(int u, int v) { g[u].push_back(v); }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        st.push_back(u);
        on[u] = 1;
        for (int v : g[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (on[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            while (true) {
                int x = st.back();
                st.pop_back();
                on[x] = 0;
                comp[x] = ncomp;
                if (x == u) break;
            }
            ncomp++;
        }
    }

    int run() {
        disc.assign(n, -1);
        low.assign(n, 0);
        on.assign(n, 0);
        comp.assign(n, -1);
        timer = ncomp = 0;
        st.clear();
        for (int s = 0; s < n; s++) if (disc[s] == -1) dfs(s);
        return ncomp;
    }
};

int main() {
    FASTIO;
    TarjanSCC t(5);
    t.add(0, 1); t.add(1, 2); t.add(2, 0);
    t.add(1, 3); t.add(3, 4); t.add(4, 3);
    cout << t.run() << '\n';                       // 2
    return 0;
}
```

**Jebakan:**

1. `low[u] = min(low[u], low[v])` pada back-edge ke simpul **tidak** on-stack — merusak SCC.
2. Lupa `on[v]` saat pop.
3. Mencampur rumus jembatan `low[v] > disc[u]` tanpa stack.

**Kompleksitas:** `O(n + m)`.

---

## Kondensasi DAG

**Teori:** Kontraksi tiap SCC jadi super-simpul. Sisi antar SCC jadi sisi DAG (unique). Analoginya: peta negara, dalam negeri bebas, antar negara satu arah. Minimum sisi agar kuat-terhubung pada graf yang **lemah-terhubung**: jika 1 SCC maka 0; else `max(sumber, tenggelam)` pada DAG.

**Kapan:** DP pada SCC, 2-SAT assignment, “bisa A ke B setelah paham kelompok”. Jangan menambah sisi dalam SCC ke DAG.

**Proses:** A→B. Sumber A, tenggelam B. `max(1,1)=1` sisi (B→A) cukup.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<int>> kondensasi(int ncomp, const vector<vector<int>>& g,
                               const vector<int>& comp) {
    vector<vector<int>> dag(ncomp);
    vector<pair<int, int>> isi;
    for (int u = 0; u < (int)g.size(); u++)
        for (int v : g[u]) if (comp[u] != comp[v])
            isi.push_back({comp[u], comp[v]});
    sort(isi.begin(), isi.end());
    isi.erase(unique(isi.begin(), isi.end()), isi.end());
    for (auto [a, b] : isi) dag[a].push_back(b);
    return dag;
}

int sisiSupayaKuat(int ncomp, const vector<vector<int>>& dag) {
    if (ncomp <= 1) return 0;
    vector<int> indeg(ncomp), outdeg(ncomp);
    for (int u = 0; u < ncomp; u++)
        for (int v : dag[u]) { outdeg[u]++; indeg[v]++; }
    int src = 0, snk = 0;
    for (int i = 0; i < ncomp; i++) {
        if (!indeg[i]) src++;
        if (!outdeg[i]) snk++;
    }
    return max(src, snk);
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1}, {2, 3}, {0}, {4}, {3}};
    vector<int> comp = {0, 0, 0, 1, 1};
    auto dag = kondensasi(2, g, comp);
    cout << dag[0].size() << ' ' << sisiSupayaKuat(2, dag) << '\n'; // 1 1
    return 0;
}
```

**Jebakan:**

1. Rumus `max(src,snk)` mensyaratkan **lemah-terhubung**. Kalau tidak, hitung per komponen lemah.
2. `ncomp==1` harus 0, bukan 1.

**Kompleksitas:** `O(n + m log m)` jika sort sisi DAG.

---

## Jembatan

**Teori:** Jembatan = sisi yang jika dihapus menambah komponen. Pada DFS tak berarah, `(u,v)` (v anak u) jembatan iff `low[v] > disc[u]`: subtree `v` tidak punya back-edge ke `u` atau leluhur. Analoginya: satu-satunya jembatan sungai.

Multi-sisi paralel **bukan** jembatan. Sisi harus punya **id**; skip hanya sisi parent, bukan semua ke parent.

**Kapan:** “sisi kritis”, bridge-tree. Jangan rumus `low[v] >= disc[u]` — itu artikulasi.

**Proses:** sisi `0-1, 1-2, 2-0, 1-3`.

```
  0
 / \
1---2
|
3
```

DFS 0-1-2, 2→0 back, `low[1]=0`, sisi 0-1 bukan jembatan. 1-3: `low[3] > disc[1]` → **jembatan**.

| u | v | low[v] | disc[u] | jembatan? |
|---|---|---|---|---|
| 1 | 3 | 3 | 1 | ya |
| 0 | 1 | 0 | 0 | tidak |
| 1 | 2 | 0 | 1 | tidak |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Jembatan {
    int n, timer = 0;
    vector<vector<pair<int, int>>> g;
    vector<int> disc, low;
    vector<pair<int, int>> bridges;

    Jembatan(int n, const vector<pair<int, int>>& sisi) : n(n), g(n) {
        for (int i = 0; i < (int)sisi.size(); i++) {
            int u = sisi[i].first, v = sisi[i].second;
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }
    }

    void dfs(int u, int pe) {
        disc[u] = low[u] = timer++;
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (disc[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) bridges.push_back({u, v});
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<pair<int, int>> run() {
        disc.assign(n, -1);
        low.assign(n, 0);
        timer = 0;
        bridges.clear();
        for (int s = 0; s < n; s++) if (disc[s] == -1) dfs(s, -1);
        return bridges;
    }
};

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    Jembatan j(4, sisi);
    auto b = j.run();
    cout << b.size() << '\n';                      // 1
    return 0;
}
```

**Jebakan:**

1. `if (v == p) continue` tanpa id: multi-sisi dikira parent, jembatan palsu.
2. `>=` untuk jembatan: terlalu longgar.
3. Self-loop bukan jembatan.

**Kompleksitas:** `O(n + m)`.

---

## Titik artikulasi

**Teori:** Cut vertex: hapus simpul (plus sisinya) menambah komponen. **Akar** DFS: artikulasi jika ≥ 2 anak pohon DFS. **Bukan akar:** ada anak `v` dengan `low[v] >= disc[u]`. Analoginya: bandara hub.

Daun **bukan** artikulasi. Ujung jembatan sering artikulasi, tetapi daun di ujung jembatan tidak.

**Kapan:** “kota kritis”, block-cut tree. Jangan hapus simpul lalu BFS `n` kali pada `n=1e5`.

**Proses:** graf jembatan. DFS 0-1-2 (back ke 0), 1-3.

- 0 akar, 1 anak → bukan artikulasi.
- 1 punya anak 3 dengan `low[3] >= disc[1]` → **1 artikulasi**.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Artikulasi {
    int n, timer = 0;
    vector<vector<pair<int, int>>> g;
    vector<int> disc, low, art;

    Artikulasi(int n, const vector<pair<int, int>>& sisi) : n(n), g(n) {
        for (int i = 0; i < (int)sisi.size(); i++) {
            g[sisi[i].first].push_back({sisi[i].second, i});
            g[sisi[i].second].push_back({sisi[i].first, i});
        }
    }

    void dfs(int u, int pe) {
        disc[u] = low[u] = timer++;
        int anak = 0;
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (disc[v] == -1) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (pe != -1 && low[v] >= disc[u]) art[u] = 1;
                anak++;
            } else low[u] = min(low[u], disc[v]);
        }
        if (pe == -1 && anak > 1) art[u] = 1;
    }

    vector<int> run() {
        disc.assign(n, -1);
        low.assign(n, 0);
        art.assign(n, 0);
        timer = 0;
        for (int s = 0; s < n; s++) if (disc[s] == -1) dfs(s, -1);
        vector<int> res;
        for (int i = 0; i < n; i++) if (art[i]) res.push_back(i);
        return res;
    }
};

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    Artikulasi a(4, sisi);
    auto v = a.run();
    for (int x : v) cout << x << ' ';
    cout << '\n';                                  // 1
    return 0;
}
```

**Jebakan:**

1. Akar 1 anak dianggap artikulasi.
2. `art[u]=1` di loop tanpa `pe != -1`.
3. Isolasi bukan artikulasi.

**Kompleksitas:** `O(n + m)`.

---

## Bridge-tree ide

**Teori:** Kontraksi setiap komponen 2-edge-connected (tidak terpisah oleh jembatan) jadi super-simpul. Jembatan menjadi sisi pohon. Hasilnya **pohon** (atau hutan). Analoginya: pulau kokoh disambung jembatan kayu. Jarak jembatan, diameter “kritis”, dan “tambah 1 sisi minimalkan jembatan” jadi soal pohon.

**Kapan:** “berapa jembatan di jalur u-v”, “tambah sisi agar tidak ada jembatan”. Jangan mengontraksi artikulasi dengan rumus yang sama (itu block-cut, beda: vertex-biconnected).

**Proses:** graf tadi. Komponen 2-edge: `{0,1,2}` dan `{3}`. Jembatan 1-3. Pohon 2 simpul.

Tambah sisi 3-0: jembatan hilang, 1 komponen 2-edge.

Rumus kasar: jika bridge-tree adalah jalur, tambah sisi antara dua daun ujung.

**Kode:** sketsa id komponen setelah jembatan diketahui.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
};

vector<vector<int>> bridgeTree(int n, const vector<pair<int, int>>& sisi,
                               const vector<pair<int, int>>& bridges) {
    set<pair<int, int>> br;
    for (auto [u, v] : bridges) {
        if (u > v) swap(u, v);
        br.insert({u, v});
    }
    DSU d(n);
    for (auto [u, v] : sisi) {
        int a = u, b = v;
        if (a > b) swap(a, b);
        if (!br.count({a, b})) d.unite(u, v);
    }
    vector<int> id(n, -1);
    int k = 0;
    for (int i = 0; i < n; i++) if (d.find(i) == i) id[i] = k++;
    for (int i = 0; i < n; i++) id[i] = id[d.find(i)];
    vector<vector<int>> tree(k);
    for (auto [u, v] : bridges) {
        int a = id[u], b = id[v];
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    return tree;
}

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    vector<pair<int, int>> br = {{1, 3}};
    auto t = bridgeTree(4, sisi, br);
    cout << t.size() << ' ' << t[0].size() << '\n'; // 2 1
    return 0;
}
```

**Jebakan:**

1. Multi-sisi: set `{min,max}` menelan dua kabel paralel sebagai satu “jembatan” — padahal bukan jembatan. Pakai id sisi.
2. Mengira tree selalu 1 komponen: graf awal tak terhubung → hutan.

**Kompleksitas:** `O(n + m log m)` dengan `set`, atau `O(n+m)` dengan flag id.

---

## Ringkasan

**Teori:** SCC = saling mencapai berarah. Kosaraju dua DFS, Tarjan satu DFS + stack. Jembatan `low[v] > disc[u]`. Artikulasi akar ≥2 anak atau `low[v] >= disc[u]`.

**Kapan:** pesan bolak-balik, sisi/kota kritis, kondensasi untuk DP.

**Proses:** uji 2 SCC dan 1 jembatan di `main`.

**Jebakan lintas:**

1. `>` vs `>=`.
2. Jembatan tanpa id.
3. DFS2 pada G.
4. `max(src,snk)` tanpa lemah-terhubung.

**Kompleksitas saku:** semua `O(n + m)` kecuali unique sisi DAG.

Lanjut: [sat2-flow.md](sat2-flow.md) · [siklus-bipartit.md](siklus-bipartit.md) · [dsu-mst.md](dsu-mst.md)
