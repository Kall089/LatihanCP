# Heavy-Light Decomposition

[← LCA](lca.md) · [Pohon](README.md) · [Centroid →](centroid.md)

Day **204**. Memecah setiap jalur u–v jadi O(log n) segmen beruntun di array, lalu Segment Tree menjawab tiap potongan. Hafalkan [lca.md](lca.md) dan [segment-tree.md](../10-struktur-data/segment-tree.md) dulu. HLD tanpa LCA di kepala biasanya 200 baris yang tidak bisa di-debug.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Subtree saja, tanpa jalur: [euler-tour.md](euler-tour.md) lebih pendek. Jarak statis: LCA, bukan HLD.

## Daftar isi

- [Ide HLD](#ide-hld)
- [Anak berat](#anak-berat)
- [Rantai dan posisi](#rantai-dan-posisi)
- [Bangun lengkap](#bangun-lengkap)
- [Query jalur simpul](#query-jalur-simpul)
- [Pasang SegTree](#pasang-segtree)
- [Query subtree](#query-subtree)
- [Sisi vs simpul](#sisi-vs-simpul)
- [Operasi tidak komutatif](#operasi-tidak-komutatif)
- [LCA lewat HLD](#lca-lewat-hld)
- [HLD vs alat lain](#hld-vs-alat-lain)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Ide HLD

**Teori:** Heavy-Light Decomposition memecah pohon menjadi rantai (jalur turun). Sisi ke anak dengan subtree terbesar = **heavy**. Sisi lain = **light**. Naik lewat light: ukuran subtree ayah > 2 · sz[anak] (kira-kira, jika heavy unik). Paling banyak O(log n) sisi light di jalur ke akar. Tiap ganti rantai = satu query SegTree. Total O(log n) potongan.

Rantai dilinierkan: simpul satu rantai beruntun di `pos`. Query `[pos[head], pos[x]]` valid hanya jika DFS mengunjungi **anak berat dulu**.

Analogi: tol (heavy) vs kampung (light). Ke ibu kota hampir selalu di tol, sesekali ganti gerbang.

**Kapan:**

- Pakai: update/query pada **jalur** atau subtree, n,q 10^5, operasi asosiatif.
- Jangan: hanya jarak statis — LCA dua baris.
- Jangan: minggu pertama belajar pohon.
- Jangan: hitung semua pasangan jarak k — [centroid.md](centroid.md).

**Proses:** pohon 6 simpul. `sz`: 3=1, 4=1, 5=1, 1=3, 2=2, 0=6. Anak berat 0 = 1. Anak berat 1 = 3 (atau 4, tie).

```
        0
       / \
      1   2
     / \   \
    3   4   5

rantai head 0: 0-1-3
rantai head 4: 4
rantai head 2: 2-5
```

Jalur 4–5: rantai 4, potongan di rantai 0, rantai 2. Tiga potongan.

**Kode:** field.

```cpp
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, pos;
    int timer = 0;
};
```

**Jebakan:** menulis HLD untuk “jarak 3 ke 5” — `dep[u]+dep[v]−2·dep[lca]`.

**Kompleksitas:** build O(n), query jalur O(log² n) dengan SegTree O(log n) per potongan.

## Anak berat

**Teori:** `dfsSz` mengisi `sz`, `par`, `dep`, `heavy`. `heavy[v] = -1` jika daun. Anak berat = argmax `sz[anak]`. Tie: pilih siapa saja; rantai tetap benar, `pos` beda.

**Kapan:** selalu sebelum `dfsPos`. `par[root] = -1` sebelum mulai.

**Proses:**

```
sz[3]=1, sz[4]=1, sz[1]=3
sz[5]=1, sz[2]=2
sz[0]=6
heavy[0]=1, heavy[1]=3, heavy[2]=5
heavy[3]=heavy[4]=heavy[5]=-1
```

**Kode:**

```cpp
    void dfsSz(int v, const vector<vector<int>>& g) {
        sz[v] = 1;
        heavy[v] = -1;
        for (int u : g[v]) if (u != par[v]) {
            par[u] = v;
            dep[u] = dep[v] + 1;
            dfsSz(u, g);
            sz[v] += sz[u];
            if (heavy[v] == -1 || sz[u] > sz[heavy[v]]) heavy[v] = u;
        }
    }
```

**Jebakan:** `par[root]` bukan −1 → `u != par[v]` gagal, ayah ikut, stack overflow. Tie tidak dipecahkan: sah. Mengambil anak pertama sebagai heavy tanpa `sz`.

**Kompleksitas:** O(n).

## Rantai dan posisi

**Teori:** `dfsPos(v, h)`: `head[v]=h`, `pos[v]=timer++`. Kunjungi **anak berat dulu** dengan head yang sama. Anak light mulai rantai baru, head = dirinya.

Akibat:

1. Simpul satu rantai beruntun, `pos` naik ke daun.
2. Subtree v juga beruntun: `[pos[v], pos[v]+sz[v]-1]` (berat dulu + sisa anak).

**Kapan:** wajib urutan berat dulu. Tanpa itu `[pos[head], pos[x]]` merangkul simpul asing.

**Proses:**

```
dfsPos(0, 0):
  pos[0]=0, heavy 1
  dfsPos(1, 0):
    pos[1]=1, heavy 3
    dfsPos(3, 0): pos[3]=2
    light 4: dfsPos(4, 4): pos[4]=3
  light 2: dfsPos(2, 2):
    pos[2]=4, heavy 5
    dfsPos(5, 2): pos[5]=5

pos:  0→0, 1→1, 3→2, 4→3, 2→4, 5→5
head: 0,1,3 = 0;  4=4;  2,5=2
```

**Kode:**

```cpp
    void dfsPos(int v, int h, const vector<vector<int>>& g) {
        head[v] = h;
        pos[v] = timer++;
        if (heavy[v] != -1) dfsPos(heavy[v], h, g);
        for (int u : g[v])
            if (u != par[v] && u != heavy[v]) dfsPos(u, u, g);
    }
```

**Jebakan:** anak berat tidak pertama. `head[v]=v` untuk semua — itu bukan HLD, potongan jadi O(n). `timer` tidak di-reset saat rebuild.

**Kompleksitas:** O(n).

## Bangun lengkap

**Teori:** alokasi, `dfsSz(root)`, `dfsPos(root, root)`. n=0 aman.

**Kapan:** sekali setelah baca pohon. Akar sesuai soal (sering 0 atau 1-based−1).

**Proses:** root 0 pada contoh → tabel di atas.

**Kode:**

```cpp
    void build(const vector<vector<int>>& g, int root = 0) {
        n = (int)g.size();
        par.assign(n, -1);
        dep.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        timer = 0;
        if (!n) return;
        dfsSz(root, g);
        dfsPos(root, root, g);
    }
```

**Jebakan:** `build` dua kali tanpa `timer=0`. Graf bukan pohon: `sz[root] != n`.

**Kompleksitas:** O(n) waktu dan memori.

## Query jalur simpul

**Teori:** selama `head[u] != head[v]`, naikkan yang `head`-nya lebih dalam: jawab `[pos[head[x]], pos[x]]`, lalu `x = par[head[x]]`. Setelah satu rantai, jawab `[pos[u], pos[v]]` (urutkan supaya `pos` naik: yang `dep` lebih kecil dulu).

Termasuk LCA jika query **simpul**.

**Kapan:** jumlah/min/XOR simpul di jalur.

**Proses:** jalur 4–5.

```
head[4]=4, head[5]=2 berbeda
dep[head[4]]=2, dep[head[5]]=1 → naik 4
  f(pos[4], pos[4]) = f(3,3)     simpul {4}
  4 → par[4]=1
head[1]=0, head[5]=2 berbeda
dep[0]=0 < dep[2]=1 → naik 5
  f(pos[2], pos[5]) = f(4,5)     simpul {2,5}
  5 → par[2]=0
head[1]=head[0]=0
  dep[1]>dep[0] → f(pos[0], pos[1]) = f(0,1)   {0,1}
```

Potongan: {4}, {2,5}, {0,1}. Jalur nyata 4-1-0-2-5. Simpul 4,1,0,2,5. Ya.

**Kode:**

```cpp
    template <class F>
    void jalur(int u, int v, F f) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            f(pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        f(pos[u], pos[v]);
    }
```

**Jebakan:** `u = par[u]` bukan `par[head[u]]` → lambat/salah. Lupa `swap` depth head → loop atau skip. `f` menerima L>R jika kamu tidak menukar `dep` di satu rantai — di kode ini `dep` diurutkan, `pos` naik di rantai.

**Kompleksitas:** O(log n) potongan.

## Pasang SegTree

**Teori:** isi `base[pos[v]] = nilai[v]`. Query jumlah = akumulasi `st.query` tiap potongan. Update simpul = `st.update(pos[v], x)`.

Tempel SegTree jumlah. Identitas 0.

**Kapan:** CSES *Path Queries* simpul, CF path add/sum.

**Proses:** semua nilai 1. Jumlah jalur 4–5 = 5 simpul = 5. Set simpul 0 jadi 10: jumlah 14.

**Kode:**

```cpp
struct SegSum {
    int n;
    vector<ll> t;
    explicit SegSum(int n_) : n(n_), t(4 * max(n_, 1) + 4, 0) {}

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = (l < (int)a.size() ? a[l] : 0);
            return;
        }
        int m = (l + r) / 2;
        build(v * 2, l, m, a);
        build(v * 2 + 1, m + 1, r, a);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void update(int v, int l, int r, int i, ll x) {
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(v * 2, l, m, i, x);
        else update(v * 2 + 1, m + 1, r, i, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    ll query(int v, int l, int r, int ql, int qr) const {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return query(v * 2, l, m, ql, qr) + query(v * 2 + 1, m + 1, r, ql, qr);
    }
};

ll jumlahJalur(HLD& h, SegSum& st, int u, int v) {
    ll s = 0;
    h.jalur(u, v, [&](int L, int R) {
        if (L > R) swap(L, R);
        s += st.query(1, 0, h.n - 1, L, R);
    });
    return s;
}

void setSimpul(HLD& h, SegSum& st, int v, ll x) {
    st.update(1, 0, h.n - 1, h.pos[v], x);
}

void isiBase(HLD& h, const vector<ll>& val, vector<ll>& base) {
    base.assign(h.n, 0);
    for (int v = 0; v < h.n; v++) base[h.pos[v]] = val[v];
}
```

Update rentang jalur (+x semua simpul di u–v): lazy SegTree, `update(L,R,+x)` di tiap potongan. Lihat [lazy.md](../10-struktur-data/lazy.md).

**Jebakan:** `base[v]=val[v]` tanpa `pos`. `st.query` dengan n=0. Operasi min: identitas bukan 0.

**Kompleksitas:** O(log² n) per query.

## Query subtree

**Teori:** bonus: `[pos[v], pos[v]+sz[v]-1]` = subtree, karena berat dulu + sisa anak. Satu query SegTree, O(log n).

**Kapan:** soal campur jalur dan subtree di satu struktur. Jika **hanya** subtree: Euler + BIT cukup, tanpa HLD.

**Proses:** v=1, pos=1, sz=3 → indeks 1,2,3 = simpul 1,3,4. Benar.

**Kode:**

```cpp
ll jumlahSubtree(HLD& h, SegSum& st, int v) {
    return st.query(1, 0, h.n - 1, h.pos[v], h.pos[v] + h.sz[v] - 1);
}
```

**Jebakan:** `pos[v]+sz[v]` tanpa `−1`. Euler file lain juga bisa subtree — HLD berharga jika **juga** ada jalur.

**Kompleksitas:** O(log n).

## Sisi vs simpul

**Teori:** nilai di **sisi**: letakkan bobot sisi (ayah–v) di simpul v (anak). Query jalur: **jangan** ikut LCA (tidak ada sisi di LCA).

```
satu rantai, u lebih dangkal: f(pos[u]+1, pos[v])
u==v: tidak ada sisi, jangan panggil f
```

Saat masih beda rantai, potongan `[pos[head], pos[x]]` seluruhnya sisi (head ke x), sah — sisi ke `par[head]` belum masuk, akan diurus setelah lompat.

**Kapan:** CSES *Path Queries* sisi, min sisi di jalur.

**Proses:** jalur 3–5, sisi 3-1, 1-0, 0-2, 2-5. Empat sisi, lima simpul. Skip LCA 0.

```
nilai di anak: val[3], val[1], val[2], val[5]  (val[0] tidak dipakai)
```

Update sisi (a,b): simpul yang `dep` lebih dalam.

**Kode:**

```cpp
    template <class F>
    void jalurSisi(int u, int v, F f) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            f(pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        if (u != v) f(pos[u] + 1, pos[v]);
    }

void setSisi(HLD& h, SegSum& st, int a, int b, ll x) {
    if (h.dep[a] < h.dep[b]) swap(a, b);
    st.update(1, 0, h.n - 1, h.pos[a], x);
}

ll jumlahSisi(HLD& h, SegSum& st, int u, int v) {
    ll s = 0;
    h.jalurSisi(u, v, [&](int L, int R) {
        if (L > R) swap(L, R);
        s += st.query(1, 0, h.n - 1, L, R);
    });
    return s;
}
```

**Jebakan:** query simpul memakai `jalurSisi` atau sebaliknya. `pos[u]+1` saat u==v menghasilkan L>R. Update sisi di simpul dangkal.

**Kompleksitas:** sama O(log² n).

## Operasi tidak komutatif

**Teori:** concat, hash arah, “string di jalur”. `a⊕b ≠ b⊕a`. Potongan naik dan turun harus dipisah. Kumpulkan vektor naik dari u ke LCA, vektor turun dari v ke LCA, gabung dengan reverse yang perlu.

HLD `jalur` di atas menggabungkan tanpa arah. Untuk jumlah/min/XOR (komutatif) aman.

**Kapan:** hash polinom di jalur, non-commutative matrix.

**Proses:** jalur 4-1-0-2-5. Naik 4→1→0, turun 0→2→5. Concat “410” + “25” vs kebalikan.

**Kode:** kerangka dua arah.

```cpp
    template <class F>
    void jalurArah(int u, int v, F naik, F turun) {
        int a = u, b = v;
        vector<pair<int, int>> A, B;
        while (head[a] != head[b]) {
            if (dep[head[a]] >= dep[head[b]]) {
                A.push_back({pos[head[a]], pos[a]});
                a = par[head[a]];
            } else {
                B.push_back({pos[head[b]], pos[b]});
                b = par[head[b]];
            }
        }
        if (dep[a] > dep[b]) A.push_back({pos[b], pos[a]});
        else B.push_back({pos[a], pos[b]});
        for (auto [L, R] : A) naik(L, R);
        reverse(B.begin(), B.end());
        for (auto [L, R] : B) turun(L, R);
    }
```

SegTree harus punya query terbalik (atau simpan hash mundur).

**Jebakan:** memakai `jumlahJalur` untuk concat. Reverse salah potongan.

**Kompleksitas:** tetap O(log n) potongan.

## LCA lewat HLD

**Teori:** setelah `head` sama, yang `dep` lebih kecil adalah LCA. Sama proses dengan `jalur` tanpa `f`. Berguna jika HLD sudah ada dan kamu malas lifting terpisah. Query O(log n).

**Kapan:** sudah bangun HLD. Banyak LCA murni: lifting atau Euler+RMQ lebih ringan.

**Proses:** LCA(4,5): naik 4 ke 1, naik 5 ke 0, head sama, dep[1]>dep[0] → 0.

**Kode:**

```cpp
    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

int jarak(const HLD& h, int u, int v) {
    int w = h.lca(u, v);
    return h.dep[u] + h.dep[v] - 2 * h.dep[w];
}
```

**Jebakan:** `lca` HLD bergantung akar yang sama dengan `build`.

**Kompleksitas:** O(log n).

## HLD vs alat lain

**Teori:**

| Soal | Alat |
|---|---|
| jarak / LCA statis | lifting |
| subtree saja, update titik | Euler + BIT |
| update simpul, jumlah jalur | HLD + SegTree |
| update sisi, min jalur | HLD sisi |
| hitung semua jalur jarak k | centroid |
| unik warna subtree | small-to-large |
| k simpul penting | [virtual-tree.md](virtual-tree.md) |

**Kapan:** HLD = struktur query online. Centroid = D&C hitung offline.

**Proses:** “ubah a[v], jumlah di jalur u v” → HLD. “berapa jalur panjang 5” → centroid.

**Kode:** jangan campur array `mati` centroid ke dalam HLD.

**Jebakan:** HLD untuk query offline yang cukup dua DFS. Overengineering.

**Kompleksitas:** HLD log² per query. Euler subtree log. LCA log atau O(1).

## Uji naif

**Teori:** jumlah jalur naif: jalan u ke v lewat `par`+`dep`. Banding HLD. Tes semua pasangan n≤20. Sisi: jumlah `dist` jika semua bobot 1.

**Kapan:** setelah tulis `jalur` / `jalurSisi`.

**Proses:** pohon contoh, nilai 1 tiap simpul, jumlah jalur = dist+1.

**Kode:**

```cpp
ll naifJalur(int u, int v, const vector<int>& par, const vector<int>& dep,
             const vector<ll>& val) {
    ll s = 0;
    while (u != v) {
        if (dep[u] < dep[v]) swap(u, v);
        s += val[u];
        u = par[u];
    }
    return s + val[u];
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    HLD h;
    h.build(g, 0);
    vector<ll> val(6, 1), base;
    isiBase(h, val, base);
    SegSum st(6);
    st.build(1, 0, 5, base);
    for (int i = 0; i < 6; i++)
        for (int j = i; j < 6; j++) {
            ll a = jumlahJalur(h, st, i, j);
            ll b = naifJalur(i, j, h.par, h.dep, val);
            if (a != b) {
                cout << "WA " << i << ' ' << j << '\n';
                return 0;
            }
        }
    cout << jumlahSubtree(h, st, 1) << '\n';                 // 3
    cout << h.lca(4, 5) << ' ' << jarak(h, 3, 5) << '\n';    // 0 4
    cout << "ok\n";
}
```

**Jebakan:** naif `par` dari HLD hanya valid jika akar sama. Tes sisi: `jumlahSisi` vs `jarak` jika w=1.

**Kompleksitas:** tes O(n² log²).

## Ringkasan

1. Heavy = subtree terbesar. Rantai. `pos` beruntun jika berat dulu.
2. Jalur simpul = O(log n) segmen, termasuk LCA.
3. Jalur sisi = skip LCA, nilai di anak.
4. Subtree = satu segmen `[pos, pos+sz-1]`.
5. Komutatif: akumulasi langsung. Concat: pisah naik/turun.
6. Jarak statis: LCA. Hitung semua jalur: centroid.

Latihan Day 204. Jangan salin `exercise_*.cpp`.
