# DSU, Kruskal, dan Prim

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **134–136**. Gabung himpunan dan pohon rentang minimum. DSU juga fondasi Kruskal. Jarak berbobot di [dijkstra.md](dijkstra.md) — Prim **bukan** `dist[u]+w`.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [DSU](#dsu)
- [DSU tambahan](#dsu-tambahan)
- [Kruskal](#kruskal)
- [Prim](#prim)
- [Varian MST](#varian-mst)
- [Sisi wajib dan bottleneck](#sisi-wajib-dan-bottleneck)
- [Ringkasan](#ringkasan)

---

## DSU

**Teori:** Disjoint Set Union menjawab `find(x)` = kelompok mana dan `unite(a,b)` = satukan. Analoginya silsilah: naik sampai leluhur yang menunjuk dirinya. Tanpa optimasi rantai `O(n)`. **Union by size** menempel yang kecil ke yang besar (`O(log n)` tinggi). **Path halving/compression** meratakan. Keduanya: `O(α(n))` amortisasi, praktis konstanta.

**Kapan:** “apakah terhubung setelah menambah sisi”, Kruskal, gabung kelompok online, deteksi siklus tak berarah. Jangan jika sisi **dihapus** kecuali rollback/offline mundur. Jangan untuk jarak di dalam komponen.

**Proses:** elemen 0..5.

```
unite(0,1), unite(1,2), unite(3,4), find(2), find(4), unite(2,3), sama(0,4)
```

| op | akar penting | sz | komponen |
|---|---|---|---|
| init | tiap i→i | 1 | 6 |
| 0-1 | 1 di bawah 0 | sz[0]=2 | 5 |
| 1-2 | 2 di bawah 0 | sz[0]=3 | 4 |
| 3-4 | 4 di bawah 3 | sz[3]=2 | 3 |
| find(2) | 2→0 | | |
| unite 2-3 | 3 di bawah 0 | sz[0]=5 | 2 |
| sama(0,4) | find(4)=0 | ya | 2 |

Simpul 5 sendiri.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    int komponen;
    DSU(int n) : par(n), sz(n, 1), komponen(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
        return true;
    }
    bool sama(int a, int b) { return find(a) == find(b); }
    int ukuran(int x) { return sz[find(x)]; }
};

int main() {
    FASTIO;
    DSU d(6);
    d.unite(0, 1);
    d.unite(1, 2);
    d.unite(3, 4);
    cout << d.sama(0, 2) << ' ' << d.sama(0, 4) << '\n'; // 1 0
    d.unite(2, 3);
    cout << d.sama(0, 4) << ' ' << d.ukuran(4) << ' ' << d.komponen << '\n';
    // 1 5 2
    return 0;
}
```

**Jebakan:**

1. `sz[x]` tanpa `find(x)` — ukuran hanya valid di **akar**.
2. Path compression rekursif pada rantai `1e6`: stack overflow.
3. `unite` tidak mengembalikan `bool` lalu Kruskal menjumlah sisi siklus.
4. DSU `n` vs simpul sampai `n` (1-index).

**Kompleksitas:** `O(α(n))` per op, memori `O(n)`.

---

## DSU tambahan

**Teori:** Simpan agregat di akar, rollback tanpa compression, petakan grid `(r,c) → r*C+c`, atau `par[i]` = kursi kosong berikutnya. Analoginya: folder gabung mewarisi jumlah file; *undo* hanya aman jika sejarah tidak diratakan.

**Kapan:** jumlah nilai komponen, connectivity offline mundur, sel hidup, “kursi kosong pertama ≥ x”. Jangan rollback + path compression.

**Proses:** rollback. `unite(0,1)`, `unite(2,3)`, checkpoint, `unite(1,2)`, `sama(0,3)==1`, rollback, `sama(0,3)==0`.

| waktu | komponen |
|---|---|
| 0 | 4 |
| +0-1 | 3 |
| +2-3 | 2 |
| +1-2 | 1 |
| rollback | 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DSUAgregat {
    vector<int> par, sz;
    vector<ll> jumlah;
    DSUAgregat(const vector<ll>& a)
        : par(a.size()), sz(a.size(), 1), jumlah(a) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        jumlah[a] += jumlah[b];
        return true;
    }
    ll total(int x) { return jumlah[find(x)]; }
};

struct DSURollback {
    vector<int> par, sz;
    vector<pair<int, int>> his;
    DSURollback(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) x = par[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        his.push_back({b, sz[a]});
        par[b] = a;
        sz[a] += sz[b];
        return true;
    }
    void rollback() {
        if (his.empty()) return;
        auto [b, old] = his.back();
        his.pop_back();
        sz[par[b]] = old;
        par[b] = b;
    }
    int checkpoint() const { return (int)his.size(); }
    void rollbackKe(int t) { while ((int)his.size() > t) rollback(); }
};

struct PosisiKosong {
    vector<int> nxt;
    PosisiKosong(int n) : nxt(n + 1) { iota(nxt.begin(), nxt.end(), 0); }
    int find(int x) {
        while (nxt[x] != x) { nxt[x] = nxt[nxt[x]]; x = nxt[x]; }
        return x;
    }
    int pakai(int i) {
        int p = find(i);
        if (p < (int)nxt.size() - 1) nxt[p] = find(p + 1);
        return p;
    }
};

int idxGrid(int r, int c, int C) { return r * C + c; }

int main() {
    FASTIO;
    DSURollback d(4);
    d.unite(0, 1);
    d.unite(2, 3);
    int t = d.checkpoint();
    d.unite(1, 2);
    cout << (d.find(0) == d.find(3)) << '\n';      // 1
    d.rollbackKe(t);
    cout << (d.find(0) == d.find(3)) << '\n';      // 0
    PosisiKosong pk(5);
    cout << pk.pakai(2) << ' ' << pk.pakai(2) << '\n'; // 2 3
    return 0;
}
```

**Jebakan:**

1. Rollback memakai compression: undo rusak.
2. Agregat dibaca di anak.
3. Grid `r*C+c` vs `c*R+r`.

**Kompleksitas:** agregat `α(n)`; rollback `O(log n)` per op.

---

## Kruskal

**Teori:** Urutkan sisi naik bobot, pasang jika kedua ujung belum satu komponen. Teorema cut: sisi paling ringan yang menyeberangi suatu potongan aman masuk suatu MST. Analoginya: kabel termurah dulu, skip jika kedua kota sudah nyambung. Pohon rentang: `n-1` sisi. Kurang dari itu → tidak terhubung.

**Kapan:** tak berarah berbobot, `m` sampai `2e5`. Jangan pada graf berarah (arborescence). 

**Proses:** 6 simpul, sisi `(w,u,v)`:

```
(1,0,1), (2,1,2), (2,0,2), (3,1,3), (4,2,4), (4,3,4), (5,3,5), (6,4,5), (10,0,5)
```

| sisi | DSU | ambil? | total |
|---|---|---|---|
| 0-1 : 1 | beda | ya | 1 |
| 1-2 : 2 | beda | ya | 3 |
| 0-2 : 2 | sama | tidak | 3 |
| 1-3 : 3 | beda | ya | 6 |
| 2-4 : 4 | beda | ya | 10 |
| 3-4 : 4 | sama | tidak | 10 |
| 3-5 : 5 | beda | ya | 15 |
| 4-5 : 6 | sama | tidak | 15 |

5 sisi, MST = 15.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    int komponen;
    DSU(int n) : par(n), sz(n, 1), komponen(n) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
        return true;
    }
};

struct Sisi { ll w; int u, v; };
bool operator<(const Sisi& a, const Sisi& b) { return a.w < b.w; }

pair<ll, vector<Sisi>> kruskal(int n, vector<Sisi> sisi) {
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    ll total = 0;
    vector<Sisi> pakai;
    for (auto e : sisi) if (d.unite(e.u, e.v)) {
        total += e.w;
        pakai.push_back(e);
        if ((int)pakai.size() == n - 1) break;
    }
    if ((int)pakai.size() != n - 1) return {-1, {}};
    return {total, pakai};
}

int main() {
    FASTIO;
    vector<Sisi> sisi = {
        {1, 0, 1}, {2, 1, 2}, {2, 0, 2}, {3, 1, 3}, {4, 2, 4},
        {4, 3, 4}, {5, 3, 5}, {6, 4, 5}, {10, 0, 5}
    };
    auto [tot, pakai] = kruskal(6, sisi);
    cout << tot << ' ' << pakai.size() << '\n';    // 15 5
    return 0;
}
```

**Jebakan:**

1. Tidak cek `pakai.size() == n-1`.
2. `unite` diabaikan: sisi siklus ikut jumlah.
3. Graf 1-index, DSU `n`.

**Kompleksitas:** `O(m log m)` sort + `O(m α(n))`.

---

## Prim

**Teori:** Tumbuhkan satu pohon: mulai simpul 0, selalu tambah sisi paling ringan keluar himpunan. Dual Kruskal. Implementasi heap mirip Dijkstra, tetapi `dist[v]` = **bobot sisi** ke pohon, **bukan** `dist[u]+w`. Analoginya: ibukota memasang kabel ke desa terdekat yang belum terlayani.

**Kapan:** graf padat `O(n²)`; jarang Kruskal biasanya lebih pendek. Bobot MST sama.

**Proses:** graf Kruskal, mulai 0.

| pohon | kandidat | ambil | + |
|---|---|---|---|
| {0} | 0-1:1 | 1 | 1 |
| {0,1} | 1-2:2 | 2 | 2 |
| {0,1,2} | 1-3:3 | 3 | 3 |
| {0..3} | 2-4:4 | 4 | 4 |
| {0..4} | 3-5:5 | 5 | 5 |

Total 15.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

ll prim(int n, const vector<vector<pair<int, ll>>>& g) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    ll total = 0;
    int ambil = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (done[u]) continue;
        done[u] = 1;
        total += d;
        ambil++;
        for (auto [v, w] : g[u])
            if (!done[v] && w < dist[v]) {
                dist[v] = w;
                pq.push({w, v});
            }
    }
    return ambil == n ? total : -1;
}

ll primPadat(int n, const vector<vector<ll>>& w) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    dist[0] = 0;
    ll total = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] >= INF) return -1;
        done[u] = 1;
        total += dist[u];
        for (int v = 0; v < n; v++)
            if (!done[v]) dist[v] = min(dist[v], w[u][v]);
    }
    return total;
}

int main() {
    FASTIO;
    int n = 6;
    vector<vector<pair<int, ll>>> g(n);
    auto add = [&](int u, int v, ll w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    add(0, 1, 1); add(1, 2, 2); add(0, 2, 2); add(1, 3, 3);
    add(2, 4, 4); add(3, 4, 4); add(3, 5, 5); add(4, 5, 6); add(0, 5, 10);
    cout << prim(n, g) << '\n';                    // 15
    return 0;
}
```

**Jebakan:**

1. `dist[v] = dist[u] + w` — itu Dijkstra, MST biasanya lebih besar.
2. `ambil < n`: kembalikan `-1`.
3. `total += d` pada sumber: `d=0`, aman.

**Kompleksitas:** heap `O(m log n)`, padat `O(n²)`.

---

## Varian MST

**Teori:** **Maximum spanning tree:** Kruskal menurun. **Bottleneck MST:** minimalkan sisi terberat — setiap MST bottleneck-optimal (sisi terakhir Kruskal). **Second-best:** untuk tiap sisi non-MST `e=(u,v)`, ganti sisi terberat di jalur `u-v` pada MST; ambil peningkatan terkecil ketat. Analoginya: jaringan cadangan hampir sehemat MST.

**Kapan:** “pohon kedua”, “minimalkan kabel termahal”. Jangan second-best `O(nm)` pada `n=1e5` tanpa LCA.

**Proses:** MST = 15. Sisi `4-5:6`: jalur MST 4-2-1-3-5, terberat 5, ganti → total **16**. Itu second-best ketat.

| non-MST | max di jalur | total baru |
|---|---|---|
| 0-2 : 2 | 2 | 15 |
| 3-4 : 4 | 4 | 15 |
| 4-5 : 6 | 5 | 16 |
| 0-5 :10 | 5 | 20 |

MST maksimum: 10+6+4+3+2 = **25** (bukan 5 sisi terberat mentah = 28 berkisi).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
        return true;
    }
};

struct Sisi { ll w; int u, v; int id; };
bool operator<(const Sisi& a, const Sisi& b) { return a.w < b.w; }

ll mstMaksimum(int n, vector<Sisi> sisi) {
    sort(sisi.begin(), sisi.end(), [](Sisi a, Sisi b) { return a.w > b.w; });
    DSU d(n);
    ll tot = 0;
    int k = 0;
    for (auto e : sisi) if (d.unite(e.u, e.v)) { tot += e.w; k++; }
    return k == n - 1 ? tot : -1;
}

ll bottleneckMin(int n, vector<Sisi> sisi) {
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    ll berat = -1;
    int k = 0;
    for (auto e : sisi) if (d.unite(e.u, e.v)) { berat = e.w; k++; }
    return k == n - 1 ? berat : -1;
}

ll maxDiJalur(int u, int target, const vector<vector<pair<int, ll>>>& tree) {
    vector<ll> mx(tree.size(), -1);
    vector<int> vis(tree.size());
    function<void(int, ll)> dfs = [&](int x, ll cur) {
        vis[x] = 1;
        mx[x] = cur;
        for (auto [y, w] : tree[x]) if (!vis[y]) dfs(y, max(cur, w));
    };
    dfs(u, 0);
    return mx[target];
}

ll secondBest(int n, const vector<Sisi>& sisi, const vector<int>& inMST,
              const vector<vector<pair<int, ll>>>& tree, ll totMST) {
    ll best = INF;
    for (auto e : sisi) if (!inMST[e.id]) {
        ll mx = maxDiJalur(e.u, e.v, tree);
        if (mx < 0) continue;
        ll cand = totMST - mx + e.w;
        if (cand > totMST) best = min(best, cand);
    }
    return best >= INF ? -1 : best;
}

int main() {
    FASTIO;
    vector<Sisi> sisi = {
        {1, 0, 1, 0}, {2, 1, 2, 1}, {2, 0, 2, 2}, {3, 1, 3, 3}, {4, 2, 4, 4},
        {4, 3, 4, 5}, {5, 3, 5, 6}, {6, 4, 5, 7}, {10, 0, 5, 8}
    };
    cout << bottleneckMin(6, sisi) << '\n';        // 5
    cout << mstMaksimum(6, sisi) << '\n';          // 25
    return 0;
}
```

**Jebakan:**

1. Second-best sama total MST (banyak MST) vs ketat lebih besar.
2. `maxDiJalur` `O(n)` per sisi → `O(nm)`.
3. 5 sisi terberat mentah bukan maximum spanning tree.

**Kompleksitas:** Kruskal; second-best naif `O(n m)`.

---

## Sisi wajib dan bottleneck

**Teori:** MST yang **wajib** memuat beberapa sisi: `unite` dulu sisi wajib (jika membentuk siklus → mustahil), lalu Kruskal sisa. Bottleneck sudah di bab varian: jawaban = sisi terakhir yang masuk MST. Analoginya: kabel pemerintah sudah terpasang, sisanya pasar bebas.

**Kapan:** “harus memakai jembatan ini”, “minimalkan sisi termahal”. 

**Proses:** wajib `0-5` bobot 10. Setelah unite 0-5, Kruskal: 0-1 (1), 1-2 (2), 1-3 (3), 2-4 (4). Total `10+1+2+3+4 = 20`. Tanpa wajib, MST 15. Sisi `4-5` dan `3-5` tertolak karena 5 sudah nyambung lewat 0.

**Kode:**

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
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
        return true;
    }
};

struct Sisi { ll w; int u, v; };

ll kruskalWajib(int n, vector<Sisi> sisi, const vector<Sisi>& wajib) {
    DSU d(n);
    ll tot = 0;
    int k = 0;
    for (auto e : wajib) {
        if (!d.unite(e.u, e.v)) return -1;
        tot += e.w;
        k++;
    }
    sort(sisi.begin(), sisi.end(), [](Sisi a, Sisi b) { return a.w < b.w; });
    for (auto e : sisi) if (d.unite(e.u, e.v)) { tot += e.w; k++; }
    return k == n - 1 ? tot : -1;
}

int main() {
    FASTIO;
    vector<Sisi> sisi = {
        {1, 0, 1}, {2, 1, 2}, {2, 0, 2}, {3, 1, 3}, {4, 2, 4},
        {4, 3, 4}, {5, 3, 5}, {6, 4, 5}, {10, 0, 5}
    };
    cout << kruskalWajib(6, sisi, {{10, 0, 5}}) << '\n'; // 20
    cout << kruskalWajib(6, sisi, {{2, 0, 2}, {2, 1, 2}}) << '\n'; // -1 siklus
    return 0;
}
```

**Jebakan:**

1. Sisi wajib siklus: langsung mustahil, bukan skip.
2. Menghitung wajib dua kali jika masih ada di daftar `sisi` — `unite` kedua mengembalikan false, aman.
3. Bottleneck pada graf berarah bukan MST.

**Kompleksitas:** sama Kruskal.

---

## Ringkasan

**Teori:** DSU menggabung. Kruskal sort + unite. Prim tumbuh dari satu titik dengan `w` sisi, bukan jumlah jalur. Cut property menjamin greedy.

**Kapan:** terhubung online → DSU. Min kabel → MST. Jarak → Dijkstra, bukan Prim.

**Proses:** uji total 15 di `main`.

**Jebakan lintas:**

1. `sz[x]` tanpa find.
2. Prim `+`.
3. `n-1` tidak dicek.
4. Rollback + compression.

**Kompleksitas saku:** DSU `α(n)`, Kruskal `m log m`, Prim heap `m log n` / padat `n²`.

Lanjut: [scc-bridge.md](scc-bridge.md) · [dijkstra.md](dijkstra.md) · [flood-komponen.md](flood-komponen.md)
