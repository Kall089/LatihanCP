# 12 — Graf: DSU, SCC, jembatan, 2-SAT, aliran, matching, MCMF

[← 11 Dijkstra MST](11-graf-dijkstra-bellman-floyd-mst.md) · [Indeks](README.md) · [Lanjut 13 →](13-dp-prinsip-1d-knapsack.md)

Sisa folder **08 Graf** di `DAFTAR-MATERI.md` (Tahap 5, Day tinggi): 134 DSU (fondasi MST, diulang utuh di sini), 225 SCC, 227 jembatan & titik artikulasi, 229 2-SAT, 231 max-flow / min-cut, 233 matching bipartit, 234 MCMF & penugasan. Semua kode 0-indexed, `#include <bits/stdc++.h>`, `typedef long long ll`, fungsi terpisah.

## Daftar isi

- [DSU](#dsu)
- [DSU tambahan](#dsu-tambahan)
- [SCC Kosaraju](#scc-kosaraju)
- [SCC Tarjan](#scc-tarjan)
- [Kondensasi DAG](#kondensasi-dag)
- [Jembatan](#jembatan)
- [Titik artikulasi](#titik-artikulasi)
- [2-SAT](#2-sat)
- [Aliran: Ford-Fulkerson dan Edmonds-Karp](#aliran-ford-fulkerson-dan-edmonds-karp)
- [Dinic](#dinic)
- [Min-cut](#min-cut)
- [Matching bipartit Kuhn](#matching-bipartit-kuhn)
- [König](#könig)
- [MCMF](#mcmf)
- [Hungarian ide](#hungarian-ide)
- [Ringkasan file ini](#ringkasan-file-ini)

---

## DSU

**Teori:** Disjoint Set Union menjawab dua pertanyaan pada himpunan yang terus digabung: `find(x)` = kelompok mana, `unite(a, b)` = satukan dua kelompok. Analoginya silsilah: tiap orang menunjuk orang tua, naik sampai leluhur yang menunjuk dirinya sendiri — itulah nama kelompok. Menggabung cukup membuat satu leluhur menunjuk ke leluhur lain, bukan mewarnai ulang semua anggota.

Tanpa optimasi, rantai bisa panjang `n` sehingga `find` `O(n)`. **Union by size** menempel pohon kecil ke pohon besar: tinggi `O(log n)`. **Path compression / path halving** meratakan jalur ke akar. Keduanya bersama: `O(α(n))` amortisasi, praktis konstanta. `α(n) ≤ 4` untuk semua `n` yang muat di memori.

**Kapan dipakai:** “apakah terhubung setelah menambah sisi”, Kruskal, gabung kelompok online, deteksi siklus tak berarah. Jangan dipakai jika sisi **dihapus** (DSU tidak bisa split) kecuali trik offline: proses mundur, hapus jadi tambah, atau DSU rollback. Jangan untuk jarak/jalur di dalam komponen.

**Proses:** elemen 0..5, operasi:

```
unite(0,1), unite(1,2), unite(3,4), find(2), find(4), unite(2,3), sama(0,4)
```

| op | par (akar saja yang penting) | sz akar | komponen |
|---|---|---|---|
| init | tiap i→i | semua 1 | 6 |
| 0-1 | 1 di bawah 0 (sz sama, 0 tetap akar) | sz[0]=2 | 5 |
| 1-2 | find(1)=0, 2 di bawah 0 | sz[0]=3 | 4 |
| 3-4 | 4 di bawah 3 | sz[3]=2 | 3 |
| find(2) | 2→0 | | |
| find(4) | 4→3 | | |
| 2-3 | akar 0 sz3 vs 3 sz2 → 3 di bawah 0 | sz[0]=5 | 2 |
| sama(0,4) | find(4)=0 | ya | 2 |

Simpul 5 tetap sendiri.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    int komponen;
    DSU(int n) : par(n), sz(n, 1), komponen(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {                          // path halving iteratif
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
    int ukuran(int x) { return sz[find(x)]; }  // find DULU
};

int main() {
    DSU d(6);
    d.unite(0, 1);
    d.unite(1, 2);
    d.unite(3, 4);
    cout << d.sama(0, 2) << ' ' << d.sama(0, 4) << '\n';   // 1 0
    d.unite(2, 3);
    cout << d.sama(0, 4) << ' ' << d.ukuran(4) << ' ' << d.komponen << '\n';
    // 1 5 2
    return 0;
}
```

**Jebakan:**

1. Membaca `sz[x]` tanpa `find(x)` — ukuran hanya valid di **akar**.
2. Path compression rekursif pada rantai `n = 1e6`: stack overflow. Pakai iteratif.
3. `unite` tidak mengembalikan `bool` lalu Kruskal menjumlah sisi siklus.
4. Mencampur 0-indexed elemen dengan DSU `n+1` tanpa disiplin.

**Kompleksitas:** `O(α(n))` per `find`/`unite` dengan kedua optimasi, memori `O(n)`.

---

## DSU tambahan

**Teori:** DSU adalah kerangka: simpan agregat di akar, rollback tanpa compression, petakan grid ke indeks, atau artikan `par[i]` sebagai “posisi kosong berikutnya”. Analoginya: folder yang digabung mewarisi jumlah file; *undo* hanya aman jika kita tidak meratakan sejarah; sel `(r,c)` adalah nomor `r*C+c`.

**Kapan dipakai:** “jumlah nilai di komponen”, connectivity offline mundur, sel hidup satu-satu, “isi kursi kosong pertama ≥ x”. Jangan rollback + path compression: compression mengubah simpul yang tidak tercatat.

**Proses:** rollback. `unite(0,1)`, `unite(2,3)`, checkpoint, `unite(1,2)`, `sama(0,3)==1`, rollback, `sama(0,3)==0`.

| waktu | komponen | catatan |
|---|---|---|
| 0 | 4 | |
| +0-1 | 3 | catat 1 menempel ke 0 |
| +2-3 | 2 | catat 3 menempel ke 2 |
| +1-2 | 1 | catat 2 menempel ke 0 |
| rollback | 2 | 2 lepas, 0 dan 2 terpisah lagi |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    vector<pair<int, int>> his;            // {yang jadi anak, sz akar lama}
    DSURollback(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {                      // TANPA compression
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

int idxGrid(int r, int c, int C) { return r * C + c; }

struct PosisiKosong {
    vector<int> nxt;
    PosisiKosong(int n) : nxt(n + 1) { iota(nxt.begin(), nxt.end(), 0); }
    int find(int x) {
        while (nxt[x] != x) { nxt[x] = nxt[nxt[x]]; x = nxt[x]; }
        return x;
    }
    int pakai(int i) {                     // kursi kosong pertama >= i
        int p = find(i);
        if (p < (int)nxt.size() - 1) nxt[p] = find(p + 1);
        return p;
    }
};

bool bipartitDSU(int n, const vector<pair<int, int>>& sisi) {
    // x dan x+n = dua “warna”; sisi u-v menyatukan u dengan v+n dan v dengan u+n
    vector<int> par(2 * n), sz(2 * n, 1);
    iota(par.begin(), par.end(), 0);
    auto find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    };
    auto unite = [&](int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    };
    for (auto [u, v] : sisi) {
        unite(u, v + n);
        unite(v, u + n);
    }
    for (int i = 0; i < n; i++)
        if (find(i) == find(i + n)) return false;
    return true;
}

int main() {
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
    cout << bipartitDSU(3, {{0, 1}, {1, 2}, {2, 0}}) << '\n'; // 0 siklus ganjil
    return 0;
}
```

**Jebakan:**

1. Rollback memakai path compression: `undo` tidak bisa mengembalikan bentuk lama.
2. Agregat dibaca di anak, bukan akar.
3. Grid: `r*C+c` vs `c*R+r` tercampur.
4. Bipartit-DSU: lupa menyatukan **dua** pasangan `(u, v+n)` dan `(v, u+n)`.

**Kompleksitas:** agregat sama `α(n)`; rollback `O(log n)` per op; bipartit-DSU `O(m α(n))`.

---

## SCC Kosaraju

**Teori:** Strongly Connected Component adalah himpunan simpul di graf **berarah** yang setiap pasangan saling mencapai. Analoginya kota dengan jalan satu arah: dalam satu SCC kamu bisa putar-putar ke semua anggota, antar SCC paling-paling satu arah. Kosaraju dua DFS: (1) DFS pada `G`, catat urutan selesai; (2) DFS pada `G^T` (sisi dibalik) dalam urutan selesai terbalik. Setiap pohon DFS kedua adalah satu SCC.

Kenapa benar: waktu selesai terakhir berada di SCC sumber pada `G`. DFS pada `G^T` dari simpul itu hanya menjangkau SCC itu, karena sisi keluar `G` menjadi sisi masuk `G^T`.

**Kapan dipakai:** “kelompok yang saling bisa kirim pesan”, kondensasi jadi DAG, 2-SAT, “berapa sisi supaya graf kuat-terhubung”. Jangan memakai komponen tak berarah (DFS biasa) sebagai pengganti SCC.

**Proses:** sisi `0→1, 1→2, 2→0, 1→3, 3→4, 4→3`.

```
SCC A = {0,1,2}   SCC B = {3,4}
A --> B
```

DFS1 dari 0: 0-1-2 (2 selesai), 1 ke 3-4 (4,3 selesai), 1 selesai, 0 selesai. `order` contoh: `2, 4, 3, 1, 0`. Reverse: `0, 1, 3, 4, 2`.

`G^T`: `1→0, 2→1, 0→2, 3→1, 4→3, 3→4`.

DFS2 dari 0: 0,2,1 (lewat `0→2→1`) → SCC `{0,1,2}`. Berikutnya 3: 3,4 → SCC `{3,4}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    Kosaraju k(5);
    k.add(0, 1); k.add(1, 2); k.add(2, 0);
    k.add(1, 3); k.add(3, 4); k.add(4, 3);
    cout << k.run() << '\n';                       // 2
    for (int i = 0; i < 5; i++) cout << k.comp[i] << ' ';
    cout << '\n';                                  // 0 0 0 1 1   (id bisa beda, kelompok sama)
    return 0;
}
```

**Jebakan:**

1. Lupa membangun `G^T` saat menambah sisi.
2. DFS2 pada `G` bukan `G^T`.
3. Urutan kedua tidak dibalik: SCC pecah salah.
4. Graf tak berarah: setiap komponen biasa adalah “SCC” trivial — jangan Kosaraju tanpa arah.

**Kompleksitas:** `O(n + m)` waktu dan memori.

---

## SCC Tarjan

**Teori:** Satu DFS. `disc[u]` waktu pertama kali masuk, `low[u]` waktu tertua yang bisa dicapai `u` lewat pohon DFS plus back-edge ke simpul **masih di stack**. Jika `low[u] == disc[u]`, `u` adalah akar SCC: pop stack sampai `u`. Analoginya: rombongan pendaki; `low` adalah jejak tertua yang masih “dalam ekspedisi yang sama”. Kalau jejak tertua rombongan adalah diri sendiri, rombongan itu tertutup.

**Kapan dipakai:** satu pass, butuh low-link yang sama dengan jembatan. Kosaraju lebih mudah diingat (dua DFS). Keduanya benar. Untuk 2-SAT, nomor SCC Tarjan (increment saat pop) **terbalik** terhadap Kosaraju — lihat bab 2-SAT.

**Proses:** graf yang sama. DFS 0-1-2, 2→0 back-edge on-stack, `low[2]=disc[0]`, naik ke 1, 1→3-4, 4→3 on-stack, `low[4]=disc[3]`, 3 `low==disc` pop `{4,3}`, lalu 1 mendapat 2 dan 0, `low[0]==disc[0]` pop `{2,1,0}`.

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
typedef long long ll;

struct TarjanSCC {
    int n, timer = 0, ncomp = 0;
    vector<vector<int>> g;
    vector<int> disc, low, on, comp;
    vector<int> st;

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
                low[u] = min(low[u], disc[v]);     // bukan low[v]
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
    TarjanSCC t(5);
    t.add(0, 1); t.add(1, 2); t.add(2, 0);
    t.add(1, 3); t.add(3, 4); t.add(4, 3);
    cout << t.run() << '\n';                       // 2
    return 0;
}
```

**Jebakan:**

1. `low[u] = min(low[u], low[v])` pada back-edge ke simpul **tidak** on-stack — merusak SCC (cross-edge ke SCC lama).
2. Lupa `on[v]` saat pop.
3. Self-loop: simpul tetap SCC sendiri kecuali ada cara balik; self-loop membuatnya “kuat” ke diri, tetap satu anggota.
4. Mencampur rumus jembatan (`low[v] > disc[u]`) tanpa stack — itu bukan SCC.

**Kompleksitas:** `O(n + m)`.

---

## Kondensasi DAG

**Teori:** Kontraksi setiap SCC jadi satu super-simpul. Sisi `u→v` antar SCC berbeda menjadi sisi `comp[u] → comp[v]` (tanpa duplikat). Hasilnya **DAG**. Analoginya: peta negara, dalam negeri kamu bebas, antar negara hanya satu arah. Soal “minimum sisi agar kuat-terhubung” pada graf yang sudah cond: jika 1 SCC, 0; else `max(sumber, tenggelam)` pada DAG.

**Kapan dipakai:** DP pada SCC, 2-SAT assignment, “bisa mencapai dari A ke B setelah paham kelompok”. Jangan menambah sisi di dalam SCC ke DAG.

**Proses:** SCC `{0,1,2}=A`, `{3,4}=B`, sisi A→B. Sumber DAG: A (indeg 0). Tenggelam: B (outdeg 0). `max(1,1)=1` sisi (B→A) cukup membuat kuat-terhubung.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    vector<vector<int>> g = {{1}, {2, 3}, {0}, {4}, {3}};
    vector<int> comp = {0, 0, 0, 1, 1};
    auto dag = kondensasi(2, g, comp);
    cout << dag[0].size() << ' ' << sisiSupayaKuat(2, dag) << '\n'; // 1 1
    return 0;
}
```

**Jebakan:**

1. Multi-sisi A→B dihitung sumber/tenggelam salah jika tidak di-unique — indeg tetap benar, hanya boros.
2. Graf awal tidak terhubung lemah: rumus `max(src, snk)` mensyaratkan **lemah-terhubung**. Kalau tidak, hitung per komponen lemah.
3. `ncomp==1` harus 0, bukan 1.

**Kompleksitas:** `O(n + m log m)` jika sort sisi DAG; atau `set` `O(m log m)`.

---

## Jembatan

**Teori:** Jembatan adalah sisi yang jika dihapus menambah jumlah komponen. Pada DFS tak berarah, `(u,v)` (v anak u) adalah jembatan jika `low[v] > disc[u]`: subtree `v` tidak punya back-edge ke `u` atau leluhurnya. Analoginya: satu-satunya jembatan sungai; tidak ada jalan memutar pulang.

Multi-sisi: dua sisi paralel `u-v` **bukan** jembatan. Karena itu sisi harus punya **id**; skip hanya sisi parent, bukan semua sisi ke parent.

**Kapan dipakai:** “sisi kritis”, *bridge-tree* (kontraksi 2-edge-connected), soal kabel yang putus memisahkan jaringan. Jangan rumus `low[v] >= disc[u]` — itu artikulasi, bukan jembatan.

**Proses:** sisi id0:0-1, id1:1-2, id2:2-0, id3:1-3.

```
  0
 / \
1---2
|
3
```

DFS 0-1-2, 2→0 back, `low[2]=disc[0]`, `low[1]=0`, sisi 0-1 **bukan** jembatan. 1-3: `low[3]=disc[3] > disc[1]` → **jembatan 1-3**.

| u | v | low[v] | disc[u] | jembatan? |
|---|---|---|---|---|
| 1 | 3 | 3 | 1 | ya |
| 0 | 1 | 0 | 0 | tidak (`>` gagal) |
| 1 | 2 | 0 | 1 | tidak |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Jembatan {
    int n, timer = 0;
    vector<vector<pair<int, int>>> g;      // {v, id}
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
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    Jembatan j(4, sisi);
    auto b = j.run();
    cout << b.size() << '\n';                      // 1
    cout << b[0].first << ' ' << b[0].second << '\n';
    return 0;
}
```

**Jebakan:**

1. `if (v == p) continue` tanpa id: multi-sisi ke parent dikira parent, jembatan palsu.
2. `low[v] >= disc[u]` untuk jembatan: terlalu longgar, sisi ke artikulasi ikut.
3. Graf berarah: definisi jembatan berbeda (edge connectivity berarah).
4. Self-loop bukan jembatan.

**Kompleksitas:** `O(n + m)`.

---

## Titik artikulasi

**Teori:** Titik artikulasi (cut vertex) adalah simpul yang jika dihapus (beserta sisinya) menambah komponen. Untuk **akar** DFS: artikulasi jika punya ≥ 2 anak pohon DFS. Untuk **bukan akar**: jika ada anak `v` dengan `low[v] >= disc[u]` — subtree `v` tidak bisa “loncat” ke atas `u`. Analoginya: bandara hub; semua penerbangan daerah lewat kamu, tidak ada rute ke luar.

**Kapan dipakai:** “kota kritis”, *block-cut tree*. Jangan menghapus simpul lalu BFS `n` kali pada `n=1e5`. Jangan menyamakan dengan jembatan: ujung jembatan sering artikulasi, tetapi tidak selalu (jembatan ke daun: daun bukan artikulasi jika derajat 1? Daun **bukan** artikulasi; tetangga dalamnya iya).

**Proses:** graf jembatan di atas. Akar 0: satu anak pohon (1, karena 2 tercapai lewat 1 atau sebagai anak?). Bergantung pohon DFS.

DFS 0-1-2 (2 back ke 0), 1-3:

- 0 akar, 1 anak → **bukan** artikulasi.
- 1 punya anak 3 dengan `low[3] >= disc[1]` → **1 artikulasi**. Juga anak 2 dengan `low[2] < disc[1]` (ke 0).
- 2, 3 bukan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    Artikulasi a(4, sisi);
    auto v = a.run();
    for (int x : v) cout << x << ' ';
    cout << '\n';                                  // 1
    return 0;
}
```

**Jebakan:**

1. Akar dengan 1 anak dianggap artikulasi — salah.
2. `art[u] = 1` di dalam loop tanpa `pe != -1`: akar bisa tertandai salah sebelum tes anak.
3. Simpul terisolasi bukan artikulasi.
4. Menandai berkali-kali OK; lupa `art` array dan memakai `push` di loop menghasilkan duplikat.

**Kompleksitas:** `O(n + m)`.

---

## 2-SAT

**Teori:** 2-SAT: setiap klausa punya paling banyak 2 literal, misalnya `(a ∨ ¬b)`. Klausa `(x ∨ y)` setara implikasi `(¬x → y) ∧ (¬y → x)`. Bangun graf implikasi: simpul `2*i` = `x_i`, `2*i+1` = `¬x_i`. Graf ini punya solusi jika dan hanya jika tidak ada `x` dan `¬x` di SCC yang sama. Analoginya: “kalau kamu menolak A, kamu wajib terima B”, dan sebaliknya; jika menolak A memaksa A, sistem jebak.

Penugasan (Kosaraju seperti bab SCC, id naik saat DFS2): `x_i = true` jika `comp[2*i] > comp[2*i+1]`. Artinya kita memilih literal yang SCC-nya “lebih hilir” pada `G` sesuai penomoran Kosaraju di file ini.

**Kapan dipakai:** “pilih satu dari dua”, “tidak boleh A dan B bersamaan”, pewarnaan 2 sisi dengan syarat, beberapa *scheduling*. Jangan 3-SAT (NP-berat). Jangan lupa klausa unit `(x)` = `(x ∨ x)`.

**Proses:** variabel `x0, x1`. Klausa `(x0 ∨ x1)`, `(¬x0 ∨ x1)` → `x1` wajib true, `x0` bebas.

Implikasi:

```
(x0 ∨ x1):   ¬x0 → x1,  ¬x1 → x0     sisi 1→2, 3→0
(¬x0 ∨ x1):  x0 → x1,   ¬x1 → ¬x0    sisi 0→2, 3→1
```

Simpul: 0=x0, 1=¬x0, 2=x1, 3=¬x1.

Sisi: `1→2, 3→0, 0→2, 3→1`.

`¬x1` (3) mencapai 0 dan 1, yaitu `x0` dan `¬x0`? 3→0 dan 3→1, tetapi 0 dan 1 tidak saling mencapai 3 dalam satu SCC dengan 3. Cek `x1` dan `¬x1`: 2 tidak mencapai 3, 3 tidak ke 2 dalam siklus. `x0` dan `¬x0`: 0→2, 1→2, tidak saling. SAT. Assignment Kosaraju: `x1` true.

Kalau tambah `(¬x1 ∨ ¬x1)` yaitu `¬x1` wajib: sisi `2→3`. Kini 2↔3 mungkin plus rantai ke 0 dan 1. Jika `x1` dan `¬x1` satu SCC → UNSAT. Simulasi: 0→2→3→0 siklus memuat 0,2,3 dan 3→1, 1→2 → semua satu SCC termasuk 0 dan 1 → UNSAT.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct TwoSAT {
    int n;
    vector<vector<int>> g, gt;
    vector<int> vis, order, comp, ans;

    TwoSAT(int nvar) : n(nvar), g(2 * nvar), gt(2 * nvar) {}

    int id(int x, bool isTrue) {               // x = 0..n-1
        return 2 * x + (isTrue ? 0 : 1);
    }
    int neg(int u) { return u ^ 1; }

    void implikasi(int u, int v) {             // u => v
        g[u].push_back(v);
        gt[v].push_back(u);
    }
    void klausa(int x, bool vx, int y, bool vy) {
        // (x==vx) or (y==vy)
        implikasi(id(x, !vx), id(y, vy));
        implikasi(id(y, !vy), id(x, vx));
    }
    void unit(int x, bool vx) { klausa(x, vx, x, vx); }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    }
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : gt[u]) if (comp[v] == -1) dfs2(v, c);
    }

    bool solve() {
        int N = 2 * n;
        vis.assign(N, 0);
        order.clear();
        for (int s = 0; s < N; s++) if (!vis[s]) dfs1(s);
        comp.assign(N, -1);
        int cid = 0;
        for (int i = N - 1; i >= 0; i--)
            if (comp[order[i]] == -1) dfs2(order[i], cid++);
        ans.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            ans[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};

int main() {
    TwoSAT sat(2);
    sat.klausa(0, true, 1, true);              // x0 atau x1
    sat.klausa(0, false, 1, true);             // ~x0 atau x1
    cout << sat.solve() << ' ' << sat.ans[1] << '\n';  // 1 1
    TwoSAT bad(1);
    bad.unit(0, true);
    bad.unit(0, false);
    cout << bad.solve() << '\n';               // 0
    return 0;
}
```

**Jebakan:**

1. `id` tertukar: `2*x` vs `2*x+1` untuk true/false — samakan `neg = xor 1`.
2. Hanya menambah satu implikasi per klausa.
3. `comp[x] > comp[~x]` hanya untuk **Kosaraju penomoran DFS2 naik**. Tarjan increment-saat-pop memakai `<`.
4. Variabel 1-indexed di soal, array 0-indexed di graf: geser sekali.

**Kompleksitas:** `O(n + m)` dengan `m` = 2 × jumlah klausa.

---

## Aliran: Ford-Fulkerson dan Edmonds-Karp

**Teori:** Jaringan: sisi punya kapasitas. Aliran `f` memenuhi 0 ≤ f ≤ cap dan kekekalan di simpul selain sumber `s` dan tenggelam `t`. Teorema **max-flow min-cut**: aliran maksimum = kapasitas potongan `s-t` minimum. **Sisi residual**: sisa `cap-f` maju, plus sisi balik `f` untuk membatalkan. Jalur augmenting di residual menambah aliran. Ford-Fulkerson mencari jalur apa pun (DFS); Edmonds-Karp memakai BFS (jalur tersedikit sisi). Analoginya: pipa air; sisi balik = “menyesal, kirim balik supaya jalur lain bisa pakai pipa”.

**Kapan dipakai:** “maksimum barang dari gudang ke toko”, bipartit matching via flow, pemotongan minimum. Jangan jika `n` besar dan kapasitas 1e9 dengan DFS naif (bisa augment 1 satuan berkali-kali). Edmonds-Karp `O(n m²)` aman untuk `n ≤ 200`, `m ≤ 2000` kasar.

**Proses:** `s=0, t=3`. Sisi (u,v,cap): `0-1:3, 0-2:2, 1-2:1, 1-3:2, 2-3:4`.

BFS residual pertama: `0-1-3` bottleneck 2. Aliran 2. Residual: 1→0:2, 3→1:2, 0→1 sisa 1.

Kedua: `0-2-3` bottleneck 2. Aliran 4. Atau `0-1-2-3` sisa 1 lalu sisa 1.

Max flow = 4? Kapasitas keluar 0 adalah 3+2=5. Cut `{0,1,2}` vs `{3}`: sisi 1-3 (2) + 2-3 (4) = 6. Cut `{0}` vs sisanya: 3+2=5. Cut `{0,2}` vs `{1,3}`: 0-1:3 + 2-3:4 + 2-1 residual... cut maju: 0→1 (3) dan 2→3 (4) = 7. Min cut keluar s: 5. Bisakah flow 5? 1-3 hanya 2, 2-3 4, masuk ke {1,2} dari 0 = 5, sisi 1-2:1 memindah. Aliran: 0→1:3, 1→3:2, 1→2:1, 0→2:2, 2→3:3. Total ke t = 5. Ya, max flow **5**.

Simulasi Edmonds-Karp:

| jalur BFS | bottleneck | flow |
|---|---|---|
| 0-1-3 | 2 | 2 |
| 0-2-3 | 2 | 4 |
| 0-1-2-3 | 1 | 5 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct EK {
    int n;
    vector<vector<int>> g;
    vector<ll> cap;
    vector<int> to;

    EK(int n) : n(n), g(n) {}

    void add(int u, int v, ll c) {
        g[u].push_back((int)to.size());
        to.push_back(v);
        cap.push_back(c);
        g[v].push_back((int)to.size());
        to.push_back(u);
        cap.push_back(0);                      // sisi balik
    }

    ll bfs(int s, int t, vector<int>& par) {
        par.assign(n, -1);
        par[s] = -2;
        queue<pair<int, ll>> q;
        q.push({s, INF});
        while (!q.empty()) {
            auto [u, f] = q.front();
            q.pop();
            for (int id : g[u]) {
                int v = to[id];
                if (par[v] != -1 || cap[id] <= 0) continue;
                par[v] = id;
                ll nf = min(f, cap[id]);
                if (v == t) return nf;
                q.push({v, nf});
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0, add;
        vector<int> par;
        while ((add = bfs(s, t, par))) {
            flow += add;
            for (int v = t; v != s; ) {
                int id = par[v];
                cap[id] -= add;
                cap[id ^ 1] += add;
                v = to[id ^ 1];
            }
        }
        return flow;
    }
};

int main() {
    EK ek(4);
    ek.add(0, 1, 3);
    ek.add(0, 2, 2);
    ek.add(1, 2, 1);
    ek.add(1, 3, 2);
    ek.add(2, 3, 4);
    cout << ek.maxflow(0, 3) << '\n';              // 5
    return 0;
}
```

**Jebakan:**

1. Lupa sisi balik `cap=0` — aliran tidak bisa dibatalkan, jawaban terlalu kecil.
2. `id ^ 1` mensyaratkan sisi balik dipush **langsung setelah** sisi maju.
3. Graf tak berarah: tambah `add(u,v,c)` dan `add(v,u,c)` **terpisah** (empat residual), atau satu trik cap dua arah — jangan dobel tanpa pikir.
4. Multi-sisi: boleh `add` berkali-kali; jangan menimpa.

**Kompleksitas:** Edmonds-Karp `O(n m²)`. Ford-Fulkerson DFS `O(F m)` dengan `F` = nilai flow.

---

## Dinic

**Teori:** Dinic membangun **graf berlevel** (BFS jarak residual dari `s`), lalu mengirim *blocking flow*: DFS yang hanya maju ke level +1 sampai tidak ada jalur di level graph. Setelah blocking flow, BFS diulang. Jumlah fase `O(n)`, tiap fase `O(n m)` naif, dengan pointer sisi `O(n² m)` terburuk; pada unit network jauh lebih cepat. Analoginya: gelombang (level) plus menyedot semua pipa selevel sebelum menggambar ulang peta.

**Kapan dipakai:** default max-flow kontes, `n ≤ 1000`, `m ≤ 5000` sering lolos; matching bipartit via Dinic sangat cepat. Jangan menulis DFS tanpa `ptr` (pointer sisi): fase mengulang sisi yang sudah kering.

**Proses:** jaringan yang sama. Level awal: 0:0, 1:1, 2:1, 3:2. DFS bisa kirim 2 lewat 0-1-3 dan 2 lewat 0-2-3 lalu 1 lewat 0-1-2-3 pada residual yang masih naik level. Satu atau dua fase menutup flow 5.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct Dinic {
    struct E { int v; ll c; int rev; };
    int n;
    vector<vector<E>> g;
    vector<int> lvl, ptr;

    Dinic(int n) : n(n), g(n) {}

    void add(int u, int v, ll c) {
        g[u].push_back({v, c, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size() - 1});
    }

    bool bfs(int s, int t) {
        lvl.assign(n, -1);
        queue<int> q;
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& e : g[u]) if (e.c > 0 && lvl[e.v] == -1) {
                lvl[e.v] = lvl[u] + 1;
                q.push(e.v);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(int u, int t, ll f) {
        if (!f || u == t) return f;
        for (int& i = ptr[u]; i < (int)g[u].size(); i++) {
            auto& e = g[u][i];
            if (e.c <= 0 || lvl[e.v] != lvl[u] + 1) continue;
            ll pushed = dfs(e.v, t, min(f, e.c));
            if (pushed) {
                e.c -= pushed;
                g[e.v][e.rev].c += pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }
};

int main() {
    Dinic d(4);
    d.add(0, 1, 3);
    d.add(0, 2, 2);
    d.add(1, 2, 1);
    d.add(1, 3, 2);
    d.add(2, 3, 4);
    cout << d.maxflow(0, 3) << '\n';               // 5
    return 0;
}
```

**Jebakan:**

1. DFS boleh ke `lvl[v] != lvl[u]+1` — salah, bisa loop.
2. `ptr` di-reset tiap fase, bukan sekali seumur hidup.
3. Kapasitas `int` overflow jika banyak sisi 1e9.
4. Memakai Dinic tanpa sisi balik (lupa `rev`).

**Kompleksitas:** `O(n² m)` terburuk, praktis jauh lebih baik. Unit cap: `O(min(n^{2/3}, m^{1/2}) m)`.

---

## Min-cut

**Teori:** Setelah max-flow, residual dari `s` mewarnai himpunan `S` yang masih tercapai. Sisi asli `u→v` dengan `u ∈ S`, `v ∉ S` adalah min-cut. Kapasitasnya = max-flow. Analoginya: setelah pipa jenuh, kota yang masih “basah” dari sumber vs yang kering; perbatasan basah-kering adalah potongan termurah.

**Kapan dipakai:** “hapus sisi berkapasitas minimum supaya s tak sampai t”, partisi, *project selection* (graf keuntungan). Jangan mengambil semua sisi jenuh: tidak semua sisi jenuh ada di suatu min-cut.

**Proses:** flow 5 pada contoh. Residual dari 0: 0 masih ke? 0→1 sisa 0, 0→2 sisa 0. 0 tidak ke mana-mana. `S={0}`, cut maju 0-1 dan 0-2 kapasitas 5. Cocok.

Jika ada sisa 0→1, 1 tidak ke t, 1 masuk S, cut bergeser.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// memakai struct Dinic di atas
vector<int> himpunanS(Dinic& d, int s) {
    vector<int> vis(d.n), S;
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        S.push_back(u);
        for (auto& e : d.g[u]) if (e.c > 0 && !vis[e.v]) {
            vis[e.v] = 1;
            q.push(e.v);
        }
    }
    return S;
}

vector<pair<int, int>> sisiCut(Dinic& d, int s, const vector<pair<int, int>>& asli) {
    vector<int> vis(d.n);
    for (int u : himpunanS(d, s)) vis[u] = 1;
    vector<pair<int, int>> cut;
    for (auto [u, v] : asli) if (vis[u] && !vis[v]) cut.push_back({u, v});
    return cut;
}

int main() {
    Dinic d(4);
    vector<pair<int, int>> asli;
    auto addasli = [&](int u, int v, ll c) {
        d.add(u, v, c);
        asli.push_back({u, v});
    };
    addasli(0, 1, 3); addasli(0, 2, 2); addasli(1, 2, 1);
    addasli(1, 3, 2); addasli(2, 3, 4);
    cout << d.maxflow(0, 3) << '\n';
    auto S = himpunanS(d, 0);
    cout << S.size() << '\n';                      // 1  (hanya sumber)
    return 0;
}
```

**Jebakan:**

1. BFS min-cut memakai sisi residual `c>0`, bukan graf asli.
2. Mencetak sisi balik sebagai cut.
3. Multi-sumber: tambah super-sumber dulu, cut di jaringan diperluas.

**Kompleksitas:** satu BFS `O(n + m)` setelah flow.

---

## Matching bipartit Kuhn

**Teori:** Matching: himpunan sisi tanpa dua sisi berbagi simpul. Pada graf bipartit `(Kiri, Kanan, E)`, teorema Hall memberi syarat, algoritma jalur augmenting membangun matching: cari jalur yang mulai di kiri bebas, selang-seling tak-matching / matching, berakhir di kanan bebas, lalu *flip*. Kuhn: DFS dari setiap kiri yang belum berpasangan, dengan `used` per percobaan. Analoginya: menari — jika pasanganmu bisa pindah ke orang lain yang kosong, kamu mengambil tempatnya.

Ukuran matching maksimum = jumlah jalur augmenting yang berhasil, paling banyak `min(|K|,|R|)`.

**Kapan dipakai:** penugasan 0-1, “berapa orang dapat kursi”, teorema König. Jangan Kuhn pada graf umum (butuh Blossom). Jangan jika sisi berbobot — itu Hungarian/MCMF.

**Proses:** kiri {0,1,2}, kanan {0,1,2}. Sisi `0-0, 0-1, 1-0, 2-1`.

| coba kiri | DFS | matching kanan (mt[kanan]=kiri) |
|---|---|---|
| 0 | ambil kanan 0 | 0←0 |
| 1 | 0 sudah, augment: 1 ambil 0, 0 pindah ke 1 | 0←1, 1←0 |
| 2 | 1 sudah, 0 (kiri 0) coba pindah: 0 sudah dicoba used... 1 tidak punya alternatif selain 0,1. 2-1: mt[1]=0, kiri 0 bisa ke 0? 0 dipegang 1. Gagal? 2 hanya ke 1. | matching 2 |

Sebenarnya matching maksimum 2 (0-0, 2-1) atau (1-0, 0-1) atau (1-0, 2-1). Kuhn menemukan 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Kuhn {
    int nL, nR;
    vector<vector<int>> g;                 // g[kiri] = daftar kanan
    vector<int> mt, used;                  // mt[kanan] = kiri atau -1

    Kuhn(int nL, int nR) : nL(nL), nR(nR), g(nL), mt(nR, -1) {}
    void add(int u, int v) { g[u].push_back(v); }

    bool dfs(int u) {
        if (used[u]) return false;
        used[u] = 1;
        for (int v : g[u]) {
            if (mt[v] == -1 || dfs(mt[v])) {
                mt[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int match = 0;
        mt.assign(nR, -1);
        for (int u = 0; u < nL; u++) {
            used.assign(nL, 0);
            if (dfs(u)) match++;
        }
        return match;
    }

    vector<pair<int, int>> pasangan() const {
        vector<pair<int, int>> res;
        for (int v = 0; v < nR; v++) if (mt[v] != -1) res.push_back({mt[v], v});
        return res;
    }
};

int matchingViaDinic(int nL, int nR, const vector<pair<int, int>>& sisi) {
    // s = nL+nR, t = s+1, kiri 0..nL-1, kanan nL..nL+nR-1
    int s = nL + nR, t = s + 1;
    Dinic d(t + 1);
    for (int u = 0; u < nL; u++) d.add(s, u, 1);
    for (int v = 0; v < nR; v++) d.add(nL + v, t, 1);
    for (auto [u, v] : sisi) d.add(u, nL + v, 1);
    return (int)d.maxflow(s, t);
}

int main() {
    Kuhn k(3, 3);
    k.add(0, 0); k.add(0, 1); k.add(1, 0); k.add(2, 1);
    cout << k.maxMatching() << '\n';               // 2
    return 0;
}
```

`matchingViaDinic` membutuhkan `struct Dinic` di unit yang sama; di cheatsheet ini ia menempel setelah bab Dinic.

**Jebakan:**

1. `used` tidak di-reset tiap kiri — kehilangan augmenting path.
2. Indeks kanan dan kiri tertukar.
3. Kuhn berulang tanpa greedy awal: masih benar, sedikit lebih lambat. Greedy inisialisasi opsional.
4. Graf tidak bipartit: jalur bisa blossom, Kuhn salah.

**Kompleksitas:** Kuhn `O(n_L · (n + m))`. Dinic matching lebih baik pada padat.

---

## König

**Teori:** Pada graf bipartit, ukuran **vertex cover minimum** = ukuran matching maksimum. Vertex cover: himpunan simpul yang menyentuh semua sisi. Konstruksi: dari matching maksimum, BFS/DFS *Konig*: mulai dari kiri **bebas**, jalan selang-seling (non-matching ke kanan, matching kembali ke kiri). Misal `Z` simpul tersentuh. Cover = `(Kiri − Z) ∪ (Kanan ∩ Z)`. Analoginya: jaga semua jalan dengan satpam seminimum mungkin; satpam diletakkan di “sisi matching yang tidak bisa di-augment”.

**Kapan dipakai:** “hapus minimum baris/kolom yang menutup semua 1”, *minimum path cover* pada DAG (matching pada split). Jangan memakai rumus ini di graf non-bipartit.

**Proses:** matching `1-0, 0-1` (kiri-kanan), kiri 2 bebas. Jalan dari 2: 2→1 (non-match), 1 kanan match ke kiri 0, 0→0 (non-match), 0 kanan match ke kiri 1, 1 kiri tidak punya sisa. `Z` = kiri {2,0,1} semua, kanan {1,0}. `Kiri − Z` kosong, `Kanan ∩ Z` = {0,1}. Cover = dua simpul kanan — menyentuh semua sisi. Ukuran 2 = matching.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<vector<int>, vector<int>> konig(const Kuhn& k) {
    int nL = k.nL, nR = k.nR;
    vector<int> kiriPas(nL, -1);
    for (int v = 0; v < nR; v++) if (k.mt[v] != -1) kiriPas[k.mt[v]] = v;
    vector<int> visL(nL), visR(nR);
    function<void(int)> dfs = [&](int u) {
        if (visL[u]) return;
        visL[u] = 1;
        for (int v : k.g[u]) if (k.mt[v] != u && !visR[v]) {
            visR[v] = 1;
            if (k.mt[v] != -1) dfs(k.mt[v]);
        }
    };
    for (int u = 0; u < nL; u++) if (kiriPas[u] == -1) dfs(u);
    vector<int> coverL, coverR;
    for (int u = 0; u < nL; u++) if (!visL[u]) coverL.push_back(u);
    for (int v = 0; v < nR; v++) if (visR[v]) coverR.push_back(v);
    return {coverL, coverR};
}

int pathCoverDAG(int n, const vector<vector<int>>& g) {
    // split u -> u_kiri, u_kanan; sisi u->v menjadi u_kiri - v_kanan
    Kuhn k(n, n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) k.add(u, v);
    return n - k.maxMatching();
}

int main() {
    Kuhn k(3, 3);
    k.add(0, 0); k.add(0, 1); k.add(1, 0); k.add(2, 1);
    k.maxMatching();
    auto [cl, cr] = konig(k);
    cout << cl.size() + cr.size() << '\n';         // 2
    return 0;
}
```

**Jebakan:**

1. Cover diambil `Kiri ∩ Z` alih-alih `Kiri − Z`.
2. Path cover: rumus `n - matching` hanya untuk DAG (setelah split), bukan graf umum.
3. Independent set maksimum bipartit = `n - matching` = pelengkap vertex cover.

**Kompleksitas:** sama matching plus `O(n + m)` penelusuran.

---

## MCMF

**Teori:** Minimum Cost Maximum Flow: tiap sisi punya kapasitas dan **biaya per satuan**. Cari aliran sebesar mungkin (atau tepat `K`) dengan total `flow * cost` minimum. Algoritma jalur terpendek beruntun: berulang kali cari jalur augmenting berbiaya terkecil di residual (SPFA, karena biaya residual bisa negatif akibat sisi balik `−cost`), kirim bottleneck, akumulasi `cost += bottleneck * dist[t]`. Analoginya: kirim barang lewat rute termurah dulu; setelah pipa penuh, rute sisa mungkin membatalkan rute lama (sisi balik berbiaya negatif).

**Kapan dipakai:** penugasan berbobot, “kirim K unit termurah”, matching berbobot via aliran. Jangan jika hanya max flow tanpa biaya. Jangan Dijkstra tanpa potensial jika ada biaya negatif.

**Proses:** `s=0, a=1, b=2, t=3`. Sisi:

```
0→1 cap 1 cost 2
0→2 cap 1 cost 5
1→3 cap 1 cost 4
2→3 cap 1 cost 1
```

Jalur termurah: `0-1-3` cost 6, kirim 1. Residual balik 1→0 cost −2, 3→1 cost −4. Jalur kedua `0-2-3` cost 6. Total flow 2, cost 12. (Tidak ada jalur silang lebih murah.)

Jika ada `1→2` cap 1 cost −10 setelah flow pertama, SPFA bisa memakai pembatalan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct MCMF {
    struct E { int v; ll cap, cost; int rev; };
    int n;
    vector<vector<E>> g;

    MCMF(int n) : n(n), g(n) {}

    void add(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, cap, cost, (int)g[v].size()});
        g[v].push_back({u, 0, -cost, (int)g[u].size() - 1});
    }

    pair<ll, ll> minCostFlow(int s, int t, ll maxF = INF) {
        ll flow = 0, cost = 0;
        while (flow < maxF) {
            vector<ll> dist(n, INF);
            vector<int> inq(n, 0), pu(n, -1), pe(n, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            inq[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = 0;
                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto& e = g[u][i];
                    if (e.cap > 0 && dist[u] + e.cost < dist[e.v]) {
                        dist[e.v] = dist[u] + e.cost;
                        pu[e.v] = u;
                        pe[e.v] = i;
                        if (!inq[e.v]) { q.push(e.v); inq[e.v] = 1; }
                    }
                }
            }
            if (dist[t] >= INF) break;
            ll add = maxF - flow;
            for (int v = t; v != s; v = pu[v])
                add = min(add, g[pu[v]][pe[v]].cap);
            for (int v = t; v != s; v = pu[v]) {
                auto& e = g[pu[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
            cost += add * dist[t];
        }
        return {flow, cost};
    }
};

ll penugasanMCMF(const vector<vector<ll>>& a) {
    // a[i][j] = biaya kiri i ke kanan j, kotak n x n
    int n = (int)a.size();
    int s = 2 * n, t = 2 * n + 1;
    MCMF f(t + 1);
    for (int i = 0; i < n; i++) {
        f.add(s, i, 1, 0);
        f.add(n + i, t, 1, 0);
        for (int j = 0; j < n; j++) f.add(i, n + j, 1, a[i][j]);
    }
    return f.minCostFlow(s, t, n).second;
}

int main() {
    MCMF f(4);
    f.add(0, 1, 1, 2);
    f.add(0, 2, 1, 5);
    f.add(1, 3, 1, 4);
    f.add(2, 3, 1, 1);
    auto [fl, cs] = f.minCostFlow(0, 3);
    cout << fl << ' ' << cs << '\n';               // 2 12
    vector<vector<ll>> a = {{3, 1}, {2, 4}};
    cout << penugasanMCMF(a) << '\n';              // 1+2 = 3
    return 0;
}
```

**Jebakan:**

1. Sisi balik harus `−cost`, bukan `cost`.
2. SPFA tanpa `inq`: TLE.
3. Menambah `cost += dist[t]` tanpa kali bottleneck — salah jika `add > 1`.
4. Siklus biaya negatif dengan cap > 0: SPFA bisa loop; jaringan penugasan biasanya tidak punya (setelah konstruksi benar).
5. `maxF` terlalu besar pada graf tanpa cut: loop sampai residual habis — itu max flow, OK, tetapi pastikan `t` tak tercapai berhenti.

**Kompleksitas:** `O(F · SPFA)` ≈ `O(F n m)` terburuk. Untuk `n ≤ 100`, `F ≤ n` pada penugasan: ~`n² m`.

---

## Hungarian ide

**Teori:** Penugasan `n × n` mencari bijeksi kiri-kanan berbiaya minimum. Hungarian `O(n³)` menjaga *dual*: label baris dan kolom `u[i]`, `v[j]` sehingga `a[i][j] >= u[i] + v[j]`. Sisi *equality* (`a[i][j] == u[i] + v[j]`) membentuk subgraph. Matching sempurna di subgraph itu = penugasan optimal (teorema dualitas). Jika matching belum sempurna, label digeser sedikit agar sisi baru masuk tanpa merusak ketidaksamaan. Analoginya: tawar-menawar gaji minimum per orang dan per pekerjaan; pasangan yang “tepat di harga” boleh dikawinkan.

Di kontes, untuk `n ≤ 100` Hungarian nyaman; untuk `n` sama tetapi kamu sudah punya MCMF, penugasan lewat aliran juga benar (lebih lambat konstanta). Kode di bawah adalah versi Kuhn–Munkres `O(n³)` untuk **minimum**, 0-indexed di API, 1-indexed di dalam.

**Kapan dipakai:** matriks biaya persegi, *assignment problem*, “pasangan minimum”. Jangan jika hanya 0-1 tanpa biaya (Kuhn cukup). Jangan `n = 400` tanpa yakin TL: `64e6` operasi long long biasanya masih muat, `n = 1000` sudah 1e9.

**Proses:** matriks

```
3 1
2 4
```

Pilihan: `3+4=7` atau `1+2=3`. Optimal **3** (kiri0-kanan1, kiri1-kanan0).

Langkah ide (bukan jejak setiap delta):

1. Inisialisasi: belum ada pasangan.
2. Masukkan baris 1 (indeks 0): kolom termurah ke 1 adalah 1. Pasangkan.
3. Masukkan baris 2: kolom 0 biaya 2, lebih baik daripada merebut kolom 1 (4) plus pindah baris 1 ke kolom 0 (3) = 7. Dual menyesuaikan, matching menjadi `(0,1)` dan `(1,0)`.
4. `−v[0]` pada implementasi di bawah menyimpan total minimum = 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

pair<ll, vector<int>> hungarian(const vector<vector<ll>>& a) {
    int n = (int)a.size();
    vector<vector<ll>> A(n + 1, vector<ll>(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) A[i + 1][j + 1] = a[i][j];
    vector<ll> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(n + 1, INF);
        vector<int> used(n + 1, 0);
        do {
            used[j0] = 1;
            int i0 = (int)p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= n; j++) if (!used[j]) {
                ll cur = A[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = (int)way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> matchL(n, -1);             // matchL[kiri] = kanan
    for (int j = 1; j <= n; j++) if (p[j]) matchL[p[j] - 1] = j - 1;
    return {-v[0], matchL};
}

int main() {
    vector<vector<ll>> a = {{3, 1}, {2, 4}};
    auto [cost, m] = hungarian(a);
    cout << cost << ' ' << m[0] << ' ' << m[1] << '\n';   // 3 1 0
    return 0;
}
```

**Jebakan:**

1. Matriks tidak persegi: padat dengan baris/kolom dummy berbiaya 0 atau `INF` sesuai soal.
2. Soal maksimum: kalikan `−1` atau `C - a[i][j]` dengan `C` cukup besar, lalu Hungarian min.
3. `INF` terlalu kecil dibanding `a[i][j]` membuat delta salah.
4. Mencampur 0-index API dengan loop 1-index tanpa `+1/−1`.

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## Ringkasan file ini

**Teori:** DSU menggabung himpunan. SCC mengontraksi putaran berarah. Low-link menemukan jembatan dan artikulasi. 2-SAT adalah SCC pada graf implikasi. Aliran memakai residual dan jalur augmenting; matching bipartit adalah aliran unit; MCMF menambah biaya; Hungarian adalah dual khusus penugasan.

**Kapan dipakai:**

| Soal | Alat |
|---|---|
| Gabung / terhubung online | DSU |
| Saling mencapai berarah | SCC |
| Sisi/simpul kritis tak berarah | jembatan / artikulasi |
| Klausa 2 literal | 2-SAT |
| Kapasitas s-t | Dinic |
| Pasangan 0-1 | Kuhn atau Dinic |
| Vertex cover bipartit | König |
| Kirim aliran berbiaya | MCMF |
| Matriks n×n berbiaya | Hungarian atau MCMF |

**Proses:** uji setiap fungsi pada graf 4–6 simpul di `main` sebelum menempel ke soal. Untuk 2-SAT, uji dulu kasus `x` wajib true dan `x` kontradiksi. Untuk flow, hitung cut tangan.

**Kode:** salin **satu** struct (`Dinic` / `MCMF` / `TwoSAT` / `DSU`) utuh. Jangan campur 0-indexed dan 1-indexed. `id ^ 1` hanya aman jika sisi balik dipush langsung setelah sisi maju.

**Jebakan lintas topik:**

1. DSU `sz[x]` tanpa `find`.
2. Kosaraju DFS kedua pada `G` bukan `G^T`.
3. Jembatan tanpa id sisi (multi-sisi palsu).
4. 2-SAT `comp[x] > comp[~x]` hanya untuk Kosaraju di file ini.
5. Flow tanpa sisi balik.
6. Kuhn tanpa reset `used`.
7. MCMF sisi balik bukan `−cost`.

**Kompleksitas saku:**

| Alat | Waktu |
|---|---|
| DSU | `O(α(n))` / rollback `O(log n)` |
| Kosaraju / Tarjan | `O(n + m)` |
| Jembatan / artikulasi | `O(n + m)` |
| 2-SAT | `O(n + m)` |
| Edmonds-Karp | `O(n m²)` |
| Dinic | `O(n² m)` terburuk |
| Kuhn | `O(n (n + m))` |
| MCMF SPFA | `O(F n m)` |
| Hungarian | `O(n³)` |

### Latihan harian

`ComProgLearning/CP/` Day 134, 225, 227, 229, 231, 233, 234. Jangan menyalin folder latihan ke ensiklopedia.

### Peta tiga file graf

- File 10: jalan tanpa bobot sebarang — DFS, BFS, flood, siklus, bipartit, topo, Euler, 0-1 BFS.
- File 11: jarak berbobot dan MST — Dijkstra, Bellman, Floyd, Kruskal, Prim.
- File 12: struktur dan aliran — DSU, SCC, jembatan, 2-SAT, flow, matching, MCMF.
