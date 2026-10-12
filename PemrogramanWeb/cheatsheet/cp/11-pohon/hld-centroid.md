# HLD dan centroid

[← LCA](lca.md) · [Pohon](README.md) · [String →](../12-string/README.md)

Day 204–206. Memecah jalur jadi O(log n) segmen array, dan membelah pohon di tengah.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Hafalkan [lca.md](lca.md) dan [segment-tree.md](../10-struktur-data/segment-tree.md) dulu. HLD tanpa LCA di kepala biasanya 200 baris yang tidak bisa di-debug.

## Daftar isi

- [Ide HLD](#ide-hld)
- [Anak berat dan rantai](#anak-berat-dan-rantai)
- [Posisi DFS](#posisi-dfs)
- [Query jalur](#query-jalur)
- [Query subtree](#query-subtree)
- [Sisi vs simpul](#sisi-vs-simpul)
- [Ide centroid](#ide-centroid)
- [Cari centroid](#cari-centroid)
- [Decomp dan pasangan jarak](#decomp-dan-pasangan-jarak)
- [HLD vs centroid](#hld-vs-centroid)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Ide HLD

**Teori:** Heavy-Light Decomposition memecah pohon menjadi rantai (jalur turun) sehingga setiap jalur u–v terpecah jadi O(log n) potongan beruntun di array. Tiap rantai dilinierkan, Segment Tree menjawab potongan.

Sisi ke anak dengan subtree terbesar = **heavy**. Sisi lain = **light**. Naik lewat light: ukuran subtree ayah > 2 · sz[anak] (kira-kira). Paling banyak log n sisi light di jalur ke akar. Tiap ganti rantai = satu query SegTree.

Analogi: tol (heavy) vs kampung (light). Ke ibu kota hampir selalu di tol, sesekali ganti gerbang.

**Kapan:**

- Pakai: update/query pada **jalur** atau subtree, n,q 10^5, operasi asosiatif.
- Jangan: hanya jarak statis — LCA cukup.
- Jangan: minggu pertama belajar pohon.

**Proses:** pohon 6 simpul. `sz`: 3=1,4=1,5=1,1=3,2=2,0=6. Anak berat 0 = 1. Anak berat 1 = 3 (atau 4).

```
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

**Jebakan:** menulis HLD untuk “jarak 3,5” — `dep+lca` dua baris.

**Kompleksitas:** build O(n), query jalur O(log² n) dengan SegTree O(log n) per potongan.

## Anak berat dan rantai

**Teori:** `dfsSz` mengisi `sz`, `par`, `dep`, `heavy`. `heavy[v] = -1` jika daun.

**Kapan:** selalu sebelum `dfsPos`.

**Proses:**

```
sz[3]=1, sz[4]=1, sz[1]=3
sz[5]=1, sz[2]=2
sz[0]=6
heavy[0]=1, heavy[1]=3, heavy[2]=5
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

**Jebakan:** tie sz sama: pilih siapa saja, rantai tetap benar, `pos` beda. `par[root]` harus −1 sebelum `dfsSz`.

**Kompleksitas:** O(n).

## Posisi DFS

**Teori:** `dfsPos(v, head)`: `head[v]=h`, `pos[v]=timer++`. Kunjungi **anak berat dulu** dengan head yang sama. Anak light mulai rantai baru, head = dirinya.

Akibat: simpul satu rantai beruntun di `pos`. Subtree v juga beruntun: `[pos[v], pos[v]+sz[v]-1]`.

**Kapan:** wajib urutan berat dulu.

**Proses:**

```
pos: 0→0, 1→1, 3→2, 4→3, 2→4, 5→5
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

**Jebakan:** anak berat tidak pertama → rantai tidak beruntun, query `[pos[head], pos[x]]` merangkul simpul asing.

**Kompleksitas:** O(n).

## Query jalur

**Teori:** selama `head[u] != head[v]`, naikkan yang `head`-nya lebih dalam: jawab `[pos[head[x]], pos[x]]`, lalu `x = par[head[x]]`. Setelah satu rantai, jawab `[pos[u], pos[v]]` (urutkan pos).

Termasuk LCA jika query **simpul**.

**Kapan:** jumlah/min/XOR simpul di jalur.

**Proses:** jalur 4–5.

```
head[4]=4, head[5]=2 berbeda
dep[head[4]]=2, dep[head[5]]=1 → naik 4
  f(pos[4], pos[4]) = f(3,3)
  4 → par[4]=1
head[1]=0, head[5]=2 berbeda
dep[0]=0 < dep[2]=1 → naik 5
  f(pos[2], pos[5]) = f(4,5)
  5 → par[2]=0
head[1]=head[0]=0
  f(pos[0], pos[1]) = f(0,1)   simpul 0 dan 1
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

Pasang SegSum: isi `base[pos[v]] = nilai[v]`.

```cpp
ll jumlahJalur(HLD& h, SegTree& st, int u, int v) {
    ll s = 0;
    h.jalur(u, v, [&](int L, int R) {
        if (L > R) swap(L, R);
        s += st.query(1, 0, h.n - 1, L, R);
    });
    return s;
}

void setSimpul(HLD& h, SegTree& st, int v, ll x) {
    st.update(1, 0, h.n - 1, h.pos[v], x);
}
```

Tempel `SegTree` jumlah dari folder 10.

**Jebakan:** `u = par[head[u]]` lupa → loop. Operasi tidak komutatif (concat): butuh arah naik/turun terpisah. `f` menerima L>R jika kamu tidak menukar pos — di satu rantai kita urutkan `dep` dulu jadi pos naik.

**Kompleksitas:** O(log n) potongan × O(log n) SegTree.

## Query subtree

**Teori:** bonus HLD: `[pos[v], pos[v]+sz[v]-1]` = subtree, karena berat dulu + sisa anak.

**Kapan:** campur query jalur dan subtree di satu SegTree.

**Proses:** v=1, pos=1, sz=3 → indeks 1,2,3 = simpul 1,3,4. Benar.

**Kode:**

```cpp
ll jumlahSubtree(HLD& h, SegTree& st, int v) {
    return st.query(1, 0, h.n - 1, h.pos[v], h.pos[v] + h.sz[v] - 1);
}
```

**Jebakan:** Euler file diameter juga bisa subtree. HLD berharga jika **juga** ada jalur.

**Kompleksitas:** O(log n).

## Sisi vs simpul

**Teori:** nilai di **sisi**: letakkan bobot sisi (ayah–v) di simpul v (anak). Query jalur: **jangan** ikut LCA (tidak ada sisi di LCA).

```
f(pos[u]+1, pos[v])  saat u,v satu rantai, u lebih dangkal
```

**Kapan:** CSES *Path Queries* sisi.

**Proses:** jalur 3–5, sisi 3-1, 1-0, 0-2, 2-5. Empat sisi, lima simpul. Skip LCA 0.

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
```

**Jebakan:** query simpul memakai `jalurSisi` atau sebaliknya. Update sisi (a,b): letakkan di `dep` lebih dalam.

**Kompleksitas:** sama.

## Ide centroid

**Teori:** centroid = simpul yang setiap komponen sisa, setelah dihapus, berukuran ≤ n/2. Setiap pohon punya satu atau dua centroid.

Pohon centroid: pilih centroid, hapus, ulangi. Tinggi O(log n) karena tiap level ukuran ≤ setengah.

Setiap jalur melewati tepat satu centroid “tertinggi” (pertama yang memisahkan u dan v). Hitung kontribusi di situ, rekursi komponen.

Analogi: ibu kota membelah negara. Sensus jalur yang lewat ibu kota, lalu tiap provinsi.

**Kapan:**

- Pakai: hitung **semua jalur** berjarak k, pasangan sifat, D&C pada pohon.
- Jangan: update/query jalur biasa — HLD lebih langsung.
- Jangan: tulis lengkap di 20 menit pertama kontes jika belum pernah AC.

**Proses:** rantai 0-1-2-3-4, n=5.

```
sz dari 0: 5,4,3,2,1
0 anak sz=4 > 2 → ke 1
1 anak sz=3 > 2 → ke 2
2 anak sz=2, 2 > 5/2=2? tidak
centroid = 2, komponen {0,1} dan {3,4}
```

**Kode:** `mati[c]=true` setelah proses.

**Jebakan:** memakai centroid untuk “jumlah jalur 3–5” sekali — LCA.

**Kompleksitas:** traversal O(n log n) plus kerja `proses`.

## Cari centroid

**Teori:**

1. `hitungSz` di komponen hidup (`!mati`).
2. Dari akar komponen, selama ada anak hidup dengan `sz > nKomp/2`, pindah.
3. Berhenti: centroid.

**Kapan:** setiap `decomp`.

**Proses:** nKomp=5, 5/2=2. sz anak 2 tidak > 2, berhenti.

**Kode:**

```cpp
struct Centroid {
    vector<vector<int>> g;
    vector<int> sz;
    vector<char> mati;

    explicit Centroid(vector<vector<int>> g_) : g(move(g_)) {
        int n = (int)g.size();
        sz.assign(n, 0);
        mati.assign(n, 0);
    }

    int hitungSz(int v, int p) {
        sz[v] = 1;
        for (int u : g[v])
            if (u != p && !mati[u]) sz[v] += hitungSz(u, v);
        return sz[v];
    }

    int cari(int v, int p, int nKomp) {
        for (int u : g[v])
            if (u != p && !mati[u] && sz[u] > nKomp / 2)
                return cari(u, v, nKomp);
        return v;
    }
};
```

**Jebakan:** lupa `mati` → `hitungSz` merambah komponen mati, centroid salah, TLE/stack. `sz == nKomp/2` boleh, tidak wajib pindah.

**Kompleksitas:** O(ukuran komponen).

## Decomp dan pasangan jarak

**Teori:** contoh: banyak pasangan jarak tepat K. Di centroid c, kumpulkan jarak dari c ke simpul di tiap cabang. Untuk jarak d, tambah `cnt[K-d]` dari cabang **sebelumnya** (supaya dua kaki berbeda). Lalu masukkan cabang ini ke `cnt`. Jangan hitung pasangan dalam satu cabang — itu level bawah.

Termasuk pasangan (c, x) jika d=K.

**Kapan:** CSES *Distance Queries* sejenis hitung, bukan query online.

**Proses:** K=3 pada pohon 6 simpul. Pasangan (3,5)=4, (3,2)=3 ya, (4,5)=4, (4,2)=3 ya, (1,5)=3 ya. Hitung di centroid (0 atau 1 tergantung).

Angka kecil: rantai 0-1-2, K=2. Centroid 1. Cabang 0: d=1. Cabang 2: d=1. `cnt[0]=1` (centroid). Cabang 0: K-1=1 belum ada. Masukkan d=1. Cabang 2: cnt[1]=1 → +1 pasangan 0–2. Benar.

**Kode:**

```cpp
    ll pasanganJarak = 0;
    int targetK = 0;

    void kumpulkan(int v, int p, int d, vector<int>& daftar) {
        daftar.push_back(d);
        for (int u : g[v])
            if (u != p && !mati[u]) kumpulkan(u, v, d + 1, daftar);
    }

    void proses(int c) {
        map<int, int> sudah;
        sudah[0] = 1;
        for (int u : g[c]) if (!mati[u]) {
            vector<int> daftar;
            kumpulkan(u, c, 1, daftar);
            for (int d : daftar)
                if (targetK >= d) pasanganJarak += sudah[targetK - d];
            for (int d : daftar) sudah[d]++;
        }
    }

    void decomp(int v) {
        int nKomp = hitungSz(v, -1);
        int c = cari(v, -1, nKomp);
        mati[c] = 1;
        proses(c);
        for (int u : g[c]) if (!mati[u]) decomp(u);
    }
```

`map` O(n log² n). n besar: array frekuensi + bersihkan bucket jarak.

**Jebakan:** menghitung pasangan dua kali (jalur yang tidak “bertemu” di c ikut). Masukkan cabang ke `sudah` **sebelum** query cabang yang sama. Lupa `mati[c]=1` sebelum rekursi.

**Kompleksitas:** O(n log n) traversal, `proses` sering O(n log n) atau O(n log² n).

## HLD vs centroid

**Teori:**

| Soal | Alat |
|---|---|
| jarak / LCA | lifting |
| update simpul, jumlah jalur | HLD + SegTree |
| update sisi, min jalur | HLD sisi |
| hitung semua jalur jarak k | centroid |
| unik subtree | small-to-large |
| subtree saja, update titik | Euler + BIT |

**Kapan:** HLD = struktur query. Centroid = D&C hitung.

**Proses:** “ubah a[v], jumlah di jalur u v” → HLD. “berapa jalur panjang 5” → centroid.

**Kode:** jangan campur `mati` HLD.

**Jebakan:** centroid decomposition untuk query online tanpa menyimpan pohon centroid + data jarak.

**Kompleksitas:** HLD log² per query. Centroid biasanya offline total n log n.

## Uji naif

**Teori:** jumlah jalur naif: jalan u ke v (par+dep atau LCA). Banding HLD.

**Kapan:** n ≤ 20, random pohon.

**Proses:** pohon contoh, nilai 1 pada setiap simpul, jumlah jalur = dist+1.

**Kode:**

```cpp
// butuh SegTree jumlah: lihat 10-struktur-data/segment-tree.md

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
    vector<ll> val(6, 1), datar(6);
    for (int v = 0; v < 6; v++) datar[h.pos[v]] = val[v];
    SegTree st(6);
    st.build(1, 0, 5, datar);
    for (int i = 0; i < 6; i++)
        for (int j = i; j < 6; j++) {
            ll a = jumlahJalur(h, st, i, j);
            ll b = naifJalur(i, j, h.par, h.dep, val);
            if (a != b) {
                cout << "WA " << i << ' ' << j << '\n';
                return 0;
            }
        }
    cout << "ok\n";
}
```

Centroid: n kecil hitung pasangan O(n²) BFS.

**Jebakan:** naif `par` dari HLD hanya valid jika akar sama.

**Kompleksitas:** tes O(n² log²).

## Ringkasan

1. HLD: heavy = subtree terbesar, rantai, pos beruntun.
2. Jalur = O(log n) segmen. Subtree = satu segmen.
3. Sisi: skip LCA, nilai di anak.
4. Centroid: komponen ≤ n/2, decomp tinggi log.
5. Hitung jalur di centroid, rekursi cabang.
6. Jarak statis: LCA, bukan HLD.

Latihan Day 204–206. Jangan salin folder ComprogLearning.
