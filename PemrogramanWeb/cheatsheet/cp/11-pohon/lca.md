# LCA dan binary lifting

[← Diameter & Euler](diameter-euler.md) · [Pohon](README.md) · [HLD & centroid →](hld-centroid.md)

Day 201. Leluhur bersama paling dalam, jarak, dan titik ke-k di jalur.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Prasyarat: DFS `par`/`dep` di [diameter-euler.md](diameter-euler.md). Sparse argmin di [sparse-table.md](../10-struktur-data/sparse-table.md).

## Daftar isi

- [Binary lifting](#binary-lifting)
- [Naik k langkah](#naik-k-langkah)
- [Algoritma LCA](#algoritma-lca)
- [Simulasi LCA](#simulasi-lca)
- [Jarak dan titik ke-k](#jarak-dan-titik-ke-k)
- [Titik di jalur](#titik-di-jalur)
- [Jarak berbobot](#jarak-berbobot)
- [Euler + RMQ](#euler--rmq)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Binary lifting

**Teori:** `up[k][v]` = leluhur ke-`2^k` dari v. `up[0][v] = ayah`. Recurrence:

```
up[k][v] = up[k-1][ up[k-1][v] ]
```

Jika ayah tidak ada, tetap −1. Sama semangatnya dengan Sparse Table, tetapi di rantai menuju akar.

**Kapan:**

- Pakai: leluhur ke-k, LCA, binary search syarat di jalur naik.
- Jangan: graf dengan siklus sebagai ayah.

**Proses:** pohon

```
        0
       / \
      1   2
     / \   \
    3   4   5
```

```
v     0   1   2   3   4   5
up0  -1   0   0   1   1   2
up1  -1  -1  -1   0   0   0
up2  -1  -1  -1  -1  -1  -1
```

Leluhur ke-2 dari 3 = `up[1][3] = 0`.

**Kode:**

```cpp
struct Lift {
    int LOG;
    vector<int> dep;
    vector<vector<int>> up;

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        LOG = 1;
        while ((1 << LOG) <= max(1, n)) LOG++;
        dep.assign(n, 0);
        up.assign(LOG, vector<int>(n, -1));

        function<void(int, int)> dfs = [&](int v, int p) {
            up[0][v] = p;
            for (int u : g[v]) if (u != p) {
                dep[u] = dep[v] + 1;
                dfs(u, v);
            }
        };
        if (n) dfs(root, -1);

        for (int k = 1; k < LOG; k++)
            for (int v = 0; v < n; v++) {
                int m = up[k - 1][v];
                up[k][v] = (m == -1 ? -1 : up[k - 1][m]);
            }
    }
};
```

**Jebakan:** `LOG = 16` untuk n=2·10^5: 2^16=65536 < n, naik jauh rusak. Pakai 18–20 atau hitung dari n. `up[k-1][v]==-1` jangan diindeks `up[k-1][0]`.

**Kompleksitas:** build O(n log n), memori O(n log n).

## Naik k langkah

**Teori:** tulis k dalam biner. Bit yang menyala = lompat `2^bit`.

```
naik 13 = 8+4+1: lompat 2^3, 2^2, 2^0
```

**Kapan:** titik ke-k, samakan kedalaman sebelum LCA.

**Proses:** dari 3 naik 2: bit 1 menyala → `up[1][3]=0`. Dari 3 naik 3: 1+2 → ke 1 lalu `up[1][1]=-1`.

**Kode:**

```cpp
    int naik(int v, int d) const {
        if (d < 0 || (v != -1 && d > dep[v])) return -1;
        for (int k = 0; k < LOG && v != -1; k++)
            if (d & (1 << k)) v = up[k][v];
        return v;
    }
```

**Jebakan:** `d > dep[v]` harus −1, bukan akar. `d=0` mengembalikan v.

**Kompleksitas:** O(log n).

## Algoritma LCA

**Teori:** LCA(u,v) = leluhur bersama paling dalam. Jalur u–v = u ↗ LCA ↘ v.

Langkah:

1. Jika `dep[u] < dep[v]`, tukar.
2. Naikkan u sampai kedalaman = v.
3. Jika u==v, itu LCA (satu di bawah yang lain).
4. Naikkan keduanya dari bit **besar**: jika `up[k]` berbeda, lompat. Berhenti saat ayah langsung sama.
5. `up[0][u]` adalah LCA.

Kenapa bit besar dulu: seperti binary search. Jangan melewati LCA. Lompat hanya jika ayah 2^k masih berbeda (masih di bawah LCA).

**Kapan:** jarak, “apakah w di jalur”, titk ke-k. Banyak query tanpa `naik`: Euler+RMQ.

**Proses:** lihat bagian berikutnya.

**Kode:**

```cpp
struct LCA : Lift {
    int get(int u, int v) const {
        if (u < 0 || v < 0) return -1;
        if (dep[u] < dep[v]) swap(u, v);
        u = naik(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        return up[0][u];
    }
};
```

**Jebakan:** setelah samakan depth, lupa `u==v`. Loop bit dari kecil. Hutan: komponen beda, `get` bisa −1. Soal 1-based, LCA 0 tercetak 0.

**Kompleksitas:** O(log n) per query.

## Simulasi LCA

**Teori:** jejak angka mencegah off-by-one.

**Kapan:** WA tes 1.

**Proses:** LCA(3,5).

```
dep[3]=2, dep[5]=2  sudah sama, 3≠5
k=2: up2 keduanya -1 sama, jangan lompat
k=1: up1[3]=0, up1[5]=0 sama, jangan lompat
k=0: up0[3]=1, up0[5]=2 berbeda, lompat ke 1 dan 2
ayah = up0[1]=0 = LCA
```

LCA(3,4):

```
depth sama, 3≠4
up1 keduanya 0 sama
up0 keduanya 1 sama → tidak lompat
ayah = 1 = LCA
```

LCA(2,5): samakan, naik 5 sebanyak 1 → 2. u==v=2.

**Kode:**

```cpp
int main() {
    FASTIO;
    int n = 6;
    vector<vector<int>> g(n);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    LCA lca;
    lca.build(g, 0);
    cout << lca.get(3, 5) << '\n';          // 0
    cout << lca.get(3, 4) << '\n';          // 1
    cout << lca.get(2, 5) << '\n';          // 2
}
```

**Jebakan:** menggambar pohon beda akar. LCA bergantung akar.

**Kompleksitas:** tiga query O(log n).

## Jarak dan titik ke-k

**Teori:**

```
dist(u,v) = dep[u] + dep[v] − 2·dep[LCA]
```

Titik ke-k di jalur u→v (0 = u):

- `len = dist(u,v)`. Jika k di luar, −1.
- `du = dep[u]-dep[lca]`. Jika `k <= du`, naik k dari u.
- Jika tidak, naik `len-k` dari v.

**Kapan:** hampir semua jarak statis tanpa update sisi.

**Proses:** dist(3,5)=2+2−0=4. Titik ke-2 dari 3 ke 5: du=2, k=2 ≤ 2 → naik 2 dari 3 = 0.

```
jalur: 3,1,0,2,5
indeks 0 1 2 3 4
k=2 → 0
k=3 → naik 4-3=1 dari 5 = 2
```

**Kode:**

```cpp
int jarak(const LCA& lca, int u, int v) {
    int w = lca.get(u, v);
    return lca.dep[u] + lca.dep[v] - 2 * lca.dep[w];
}

int titikKeK(const LCA& lca, int u, int v, int k) {
    int w = lca.get(u, v);
    int du = lca.dep[u] - lca.dep[w];
    int dv = lca.dep[v] - lca.dep[w];
    if (k < 0 || k > du + dv) return -1;
    if (k <= du) return lca.naik(u, k);
    return lca.naik(v, du + dv - k);
}
```

**Jebakan:** `k=du` harus LCA, bukan anak. `dep` salah (lupa +1) meruntuhkan semua.

**Kompleksitas:** O(log n).

## Titik di jalur

**Teori:** w ada di jalur u–v iff `dist(u,v) = dist(u,w)+dist(w,v)`.

Setara: w ancestor u atau v, dan LCA(u,v) ancestor w... rumus jarak lebih pendek.

**Kapan:** “apakah gudang di jalur truk”.

**Proses:** w=1, u=3, v=5: dist(3,5)=4, dist(3,1)+dist(1,5)=1+3=4. Ya. w=4: 2+4=6≠4. Tidak.

**Kode:**

```cpp
bool diJalur(const LCA& lca, int u, int v, int w) {
    return jarak(lca, u, v) == jarak(lca, u, w) + jarak(lca, w, v);
}
```

**Jebakan:** overflow `int` jika n besar dan kamu pakai bobot — ganti `ll` untuk jarak berbobot.

**Kompleksitas:** O(log n).

## Jarak berbobot

**Teori:** `distRoot[v]` = jumlah bobot akar→v. Rumus sama:

```
dist(u,v) = distRoot[u] + distRoot[v] − 2·distRoot[lca]
```

`dep` tetap **jumlah sisi** untuk `naik` dan samakan depth. Jangan campur kilogram dengan langkah.

Update sisi merusak `distRoot` → [HLD](hld-centroid.md).

**Kapan:** sisi berbobot, query jarak statis.

**Proses:** sisi 0-1 bobot 5, lainnya 1. distRoot[3]=5+1=6, [5]=1+1=2, lca=0, dist=6+2=8.

**Kode:**

```cpp
void dfsBobot(int v, int p, ll d,
              const vector<vector<pair<int, int>>>& g,
              vector<int>& par, vector<int>& dep, vector<ll>& distRoot) {
    par[v] = p;
    distRoot[v] = d;
    for (auto [u, w] : g[v]) if (u != p) {
        dep[u] = dep[v] + 1;
        dfsBobot(u, v, d + w, g, par, dep, distRoot);
    }
}

ll jarakBobot(const LCA& lca, const vector<ll>& distRoot, int u, int v) {
    int w = lca.get(u, v);
    return distRoot[u] + distRoot[v] - 2 * distRoot[w];
}
```

`LCA::build` tetap pada graf tak berbobot (daftar tetangga).

**Jebakan:** mengisi `dep` dengan bobot lalu `naik(d)` meloncat “d sisi”.

**Kompleksitas:** sama.

## Euler + RMQ

**Teori:** DFS mencatat setiap kunjungan (masuk dan kembali). LCA(u,v) = simpul paling **dangkal** pada segmen euler antara kemunculan **pertama** u dan v. RMQ pada array kedalaman — Sparse Table argmin, query O(1).

Array euler panjang 2n−1.

**Kapan:** banyak LCA, tidak perlu `naik(k)`. Titik ke-k tetap lifting.

**Proses:**

```
seq : 0 1 3 1 4 1 0 2 5 2 0
dep : 0 1 2 1 2 1 0 1 2 1 0
first[3]=2, first[5]=8
RMQ dep [2,8] → indeks 6, simpul 0
```

**Kode:** argmin ringkas.

```cpp
struct SparseArgMin {
    vector<vector<int>> st;
    vector<int> lg, a;
    void build(const vector<int>& a_) {
        a = a_;
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = (n ? lg[n] + 1 : 1);
        st.assign(K, vector<int>(n));
        for (int i = 0; i < n; i++) st[0][i] = i;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++) {
                int x = st[k - 1][i], y = st[k - 1][i + (1 << (k - 1))];
                st[k][i] = (a[x] <= a[y] ? x : y);
            }
    }
    int queryIdx(int l, int r) const {
        int k = lg[r - l + 1];
        int x = st[k][l], y = st[k][r - (1 << k) + 1];
        return a[x] <= a[y] ? x : y;
    }
};

struct LCA_RMQ {
    vector<int> first, euler, depE, dep;
    SparseArgMin st;

    void dfs(int v, int p, int d, const vector<vector<int>>& g) {
        first[v] = (int)euler.size();
        euler.push_back(v);
        depE.push_back(d);
        dep[v] = d;
        for (int u : g[v]) if (u != p) {
            dfs(u, v, d + 1, g);
            euler.push_back(v);
            depE.push_back(d);
        }
    }

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        first.assign(n, -1);
        dep.assign(n, 0);
        euler.clear();
        depE.clear();
        if (n) dfs(root, -1, 0, g);
        st.build(depE);
    }

    int get(int u, int v) const {
        int a = first[u], b = first[v];
        if (a > b) swap(a, b);
        return euler[st.queryIdx(a, b)];
    }
};
```

**Jebakan:** RMQ memakai first, bukan kemunculan acak. Panjang 2n−1, bukan n.

**Kompleksitas:** build O(n log n), query O(1).

## Uji naif

**Teori:** naif: naik u dan v ke akar, simpan set ancestor u, pilih yang terdalam di v.

**Kapan:** n ≤ 30, semua pasangan.

**Proses:** 6 simpul, 15 pasangan, banding lifting vs RMQ vs naif.

**Kode:**

```cpp
int lcaNaif(int u, int v, const vector<int>& par, const vector<int>& dep) {
    while (dep[u] > dep[v]) u = par[u];
    while (dep[v] > dep[u]) v = par[v];
    while (u != v) {
        u = par[u];
        v = par[v];
    }
    return u;
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    LCA lca;
    lca.build(g, 0);
    LCA_RMQ rmq;
    rmq.build(g, 0);
    vector<int> par(6, -1), dep(6, 0);
    function<void(int, int)> dfs = [&](int v, int p) {
        par[v] = p;
        for (int u : g[v]) if (u != p) {
            dep[u] = dep[v] + 1;
            dfs(u, v);
        }
    };
    dfs(0, -1);
    for (int i = 0; i < 6; i++)
        for (int j = i; j < 6; j++) {
            int a = lca.get(i, j), b = rmq.get(i, j), c = lcaNaif(i, j, par, dep);
            if (a != b || a != c) {
                cout << "WA " << i << ' ' << j << '\n';
                return 0;
            }
        }
    cout << "ok\n";
}
```

**Jebakan:** naif tanpa samakan depth dulu loop tak hingga jika bug par.

**Kompleksitas:** naif O(n) per pasangan.

## Ringkasan

1. `up[k][v]` = kakek 2^k. LOG cukup besar.
2. LCA: samakan depth, naik bareng dari bit besar, ambil ayah.
3. `dist = dep[u]+dep[v]−2 dep[lca]`.
4. Titik ke-k: cabang sebelum/sesudah LCA.
5. Bobot: `distRoot`, `dep` tetap sisi.
6. Euler+RMQ: query O(1), tanpa `naik`.

Latihan Day 201. Jangan salin `exercise_*.cpp`.
