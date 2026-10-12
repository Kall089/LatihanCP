# Euler tour pada pohon

[← Diameter](diameter.md) · [Pohon](README.md) · [LCA →](lca.md)

Day **199**. Meratakan subtree jadi segmen array lewat waktu masuk/keluar. Setelah itu Fenwick atau Segment Tree menjawab update/query subtree seperti rentang biasa.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Prasyarat: pohon berakar ([diameter.md](diameter.md)), BIT ([fenwick.md](../10-struktur-data/fenwick.md)), SegTree ([segment-tree.md](../10-struktur-data/segment-tree.md)). Query **jalur** u–v: [hld.md](hld.md) atau [lca.md](lca.md), bukan `[tin[u], tin[v]]`.

## Daftar isi

- [Dua gaya Euler](#dua-gaya-euler)
- [Gaya 1: subtree sebagai rentang](#gaya-1-subtree-sebagai-rentang)
- [Cek leluhur](#cek-leluhur)
- [Subtree + BIT](#subtree--bit)
- [Subtree + SegTree](#subtree--segtree)
- [Update subtree, baca titik](#update-subtree-baca-titik)
- [Gaya 2: in-out jalur akar](#gaya-2-in-out-jalur-akar)
- [Campur nilai sisi](#campur-nilai-sisi)
- [Yang bukan Euler subtree](#yang-bukan-euler-subtree)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Dua gaya Euler

**Teori:** DFS mencatat waktu. Ada dua konvensi yang sering dicampur sampai WA:

| Gaya | Array | `tin`/`tout` | Kegunaan |
|---|---|---|---|
| 1. Subtree | panjang n | `tout` inklusif = waktu terakhir di subtree | jumlah/min subtree |
| 2. In-out | panjang 2n | `out` = indeks keluar (tulis kedua kali) | prefix jalur akar–v |

Euler + RMQ untuk LCA (array 2n−1, setiap kembali ke ayah dicatat) ada di [lca.md](lca.md). Itu gaya ketiga. Jangan campur ketiga indeks.

Analogi: absensi. Gaya 1: tiap orang dicentang **sekali** saat masuk ruangan keluarga. Keluarga = blok beruntun. Gaya 2: centang masuk dan keluar; jumlah yang masih di dalam = jalur ke kepala suku.

**Kapan:**

- Pakai gaya 1: “jumlah nilai di subtree v”, “tambah seluruh subtree”.
- Pakai gaya 2: “jumlah akar→v”, difference di jalur ke akar.
- Jangan: query jalur u–v arbitrer tanpa HLD/LCA.

**Proses:** pohon

```
        0
       / \
      1   2
     / \   \
    3   4   5
```

Anak dikunjungi dari kecil.

**Kode:** kerangka waktu.

```cpp
int timer = 0;
```

**Jebakan:** membaca tutorial A (`tout` inklusif) lalu menyalin query tutorial B (`out` eksklusif 2n). Uji daun: gaya 1 `tin==tout`; gaya 2 `out==tin+1`.

**Kompleksitas:** O(n) bangun.

## Gaya 1: subtree sebagai rentang

**Teori:** saat masuk v, `tin[v] = timer`, `id[timer] = v`, `timer++`. Setelah semua anak, `tout[v] = timer-1`. Subtree v = indeks `[tin[v], tout[v]]` pada array panjang n. Daun: `tin==tout`. Akar: `[0, n-1]` jika DFS mulai 0.

`id[t]` = simpul yang dicatat pada waktu t. Nilai simpul diletakkan di `datar[tin[v]]`.

**Kapan:** flatten + struktur data 1D. Small-to-large sack juga memakai rentang ini ([small-to-large.md](small-to-large.md)).

**Proses:**

```
DFS: 0, 1, 3, 4, 2, 5
tin:  0:0, 1:1, 3:2, 4:3, 2:4, 5:5
tout: 3:2, 4:3, 1:3, 5:5, 2:5, 0:5
id:   [0, 1, 3, 4, 2, 5]

subtree 1 = [1,3] = simpul 1,3,4
subtree 2 = [4,5] = 2,5
subtree 3 = [2,2] = 3
subtree 0 = [0,5] = semua
```

**Kode:**

```cpp
struct Euler {
    vector<int> tin, tout, id;
    int timer = 0;

    void dfs(int v, int p, const vector<vector<int>>& g) {
        tin[v] = timer;
        id[timer] = v;
        timer++;
        for (int u : g[v]) if (u != p) dfs(u, v, g);
        tout[v] = timer - 1;
    }

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        tin.assign(n, 0);
        tout.assign(n, 0);
        id.assign(n, 0);
        timer = 0;
        if (n) dfs(root, -1, g);
    }

    int sz(int v) const { return tout[v] - tin[v] + 1; }
};
```

**Jebakan:** `tout = timer` tanpa `−1` mengubah inklusif jadi eksklusif — sesuaikan query. Akar salah: subtree menurut akar lain butuh reroot. Urutan anak mengubah `id`, bukan kebenaran rentang.

**Kompleksitas:** O(n).

## Cek leluhur

**Teori:** a leluhur b (atau a==b) iff `tin[a] <= tin[b] && tout[b] <= tout[a]`. Bukti: subtree = segmen bersarang. Dua segmen saling lepas atau satu di dalam yang lain (pohon).

**Kapan:** filter sebelum LCA, virtual tree, “apakah w di subtree v”.

**Proses:**

```
ancestor(1,3) = tin 1≤2 dan tout 2≤3 → ya
ancestor(2,3) = tin 4≤2? tidak
ancestor(0,5) ya
ancestor(3,3) ya
```

**Kode:**

```cpp
bool ancestor(const Euler& eu, int a, int b) {
    return eu.tin[a] <= eu.tin[b] && eu.tout[b] <= eu.tout[a];
}
```

**Jebakan:** `tout[b] < tout[a]` tanpa `=` membuang a==b. Membandingkan `dep` saja tidak cukup (sepupu sama dalam).

**Kompleksitas:** O(1).

## Subtree + BIT

**Teori:** letakkan nilai simpul di indeks `tin[v]`. Jumlah subtree = range Fenwick `[tin, tout]`. Fenwick **1-based** di dalam: `update(tin+1, d)`.

Update titik + jumlah subtree: BIT biasa. Lihat [fenwick.md](../10-struktur-data/fenwick.md) untuk `lowbit`.

**Kapan:** n,q 10^5, hanya jumlah/XOR. Min/max → SegTree.

**Proses:** nilai `[1,2,3,4,5,6]` pada simpul 0..5.

```
datar[tin] = val[v]
datar = [1, 2, 3, 4, 5, 6]   (kebetulan sama karena tin=v pada contoh ini? 
  tin 0,1,3,4,2,5 → datar = val[0],val[1],val[3],val[4],val[2],val[5]
                 = 1, 2, 3, 4, 5, 6  ya)

subtree 1 = 2+3+4 = 9? val[1]+val[3]+val[4] = 2+4+5 = 11
Set simpul 3 jadi 10: 2+10+5 = 17
```

**Kode:**

```cpp
struct BIT {
    int n;
    vector<ll> t;
    void init(int n_) { n = n_; t.assign(n + 2, 0); }
    void update(int i, ll d) { for (; i <= n; i += i & -i) t[i] += d; }
    ll query(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll range(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
    void build(const vector<ll>& a) {       // a 0-based panjang n
        init((int)a.size());
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
};

struct SubtreeSum {
    Euler eu;
    BIT bit;
    vector<ll> val;

    SubtreeSum(const vector<vector<int>>& g, const vector<ll>& a, int root = 0)
        : val(a) {
        eu.build(g, root);
        int n = (int)a.size();
        vector<ll> datar(n);
        for (int v = 0; v < n; v++) datar[eu.tin[v]] = a[v];
        bit.build(datar);
    }

    void setVal(int v, ll x) {
        ll d = x - val[v];
        val[v] = x;
        bit.update(eu.tin[v] + 1, d);
    }

    ll query(int v) const {
        return bit.range(eu.tin[v] + 1, eu.tout[v] + 1);
    }
};
```

**Jebakan:** `update(tin)` tanpa +1 → indeks 0 merusak BIT. Membangun `datar[v]=a[v]` tanpa `tin`. Query `range(tin, tout)` 0-based langsung ke BIT 1-based.

**Kompleksitas:** O(n) bangun, O(log n) update/query.

## Subtree + SegTree

**Teori:** operasi tanpa invers (`min`, `gcd`, simpul kaya) butuh SegTree pada `datar`. Rentang sama `[tin[v], tout[v]]` 0-based di daun.

**Kapan:** min/max subtree, jumlah + min campur, “posisi pertama di subtree”.

**Proses:** min subtree 1 pada nilai `[1,2,3,4,5,6]` = min(2,4,5)=2.

**Kode:** SegTree jumlah ringkas, indeks data 0-based, simpul 1-based.

```cpp
struct SegSum {
    int n;
    vector<ll> t;
    explicit SegSum(int n_) : n(n_), t(4 * max(n_, 1) + 4, 0) {}

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
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

struct SubtreeSeg {
    Euler eu;
    SegSum st;
    int n;

    SubtreeSeg(const vector<vector<int>>& g, const vector<ll>& a, int root = 0)
        : st((int)a.size()), n((int)a.size()) {
        eu.build(g, root);
        vector<ll> datar(n);
        for (int v = 0; v < n; v++) datar[eu.tin[v]] = a[v];
        if (n) st.build(1, 0, n - 1, datar);
    }

    void setVal(int v, ll x) { st.update(1, 0, n - 1, eu.tin[v], x); }

    ll query(int v) const {
        return st.query(1, 0, n - 1, eu.tin[v], eu.tout[v]);
    }
};
```

Min: ganti identitas 0 jadi `LLONG_MAX`, `+` jadi `min`.

**Jebakan:** `4*n` terlalu kecil jika n=1 dan kamu tulis `4*n` tanpa `max`. Query kosong n=0.

**Kompleksitas:** O(n) bangun, O(log n) update/query, memori O(n).

## Update subtree, baca titik

**Teori:** tambah +x pada seluruh subtree v = difference pada array datar: `+x` di `tin[v]`, `−x` di `tout[v]+1`. BIT difference: `update(tin+1, +x)`, `update(tout+2, −x)` (1-based). Baca titik u = prefix `query(tin[u]+1)`.

Ini dual dari “update titik, jumlah subtree”.

**Kapan:** CSES *Subtree Queries* varian range-add. Lazy SegTree juga bisa.

**Proses:** +5 pada subtree 1. Simpul 1,3,4 naik 5. Baca 3: 4+5=9. Baca 2: tetap 5.

```
diff[tin[1]] += 5        indeks 1
diff[tout[1]+1] -= 5     indeks 4
prefix: 0,5,5,5,0,0 pada tin 0..5 → simpul 0,1,3,4,2,5
```

**Kode:**

```cpp
struct SubtreeAdd {
    Euler eu;
    BIT bit;
    int n;

    SubtreeAdd(const vector<vector<int>>& g, const vector<ll>& a, int root = 0) {
        eu.build(g, root);
        n = (int)a.size();
        bit.init(n + 2);
        for (int v = 0; v < n; v++) {
            bit.update(eu.tin[v] + 1, a[v]);
            bit.update(eu.tin[v] + 2, -a[v]);   // titik: +a lalu batalkan setelahnya
        }
    }

    void addSubtree(int v, ll x) {
        bit.update(eu.tin[v] + 1, x);
        bit.update(eu.tout[v] + 2, -x);
    }

    ll get(int v) const { return bit.query(eu.tin[v] + 1); }
};
```

Inisialisasi lewat difference: set titik v jadi `a[v]` = addSubtree yang hanya mencakup `tin[v]`.

**Jebakan:** `tout+1` vs `tout+2` karena geser 1-based. Lupa `−x` di kanan → seluruh sufiks array rusak. Mencampur API `setVal` titik dengan difference tanpa rebuild.

**Kompleksitas:** O(log n).

## Gaya 2: in-out jalur akar

**Teori:** array panjang 2n. Masuk: catat v, `in[v]=t++`. Keluar: catat v lagi, `out[v]=t++`. Prefix sampai `in[v]` jika +nilai saat masuk dan −nilai saat keluar = jumlah jalur akar–v (simpul di jalur masih “terbuka”).

BIT: `update(in[v]+1, +x)`, `update(out[v]+1, −x)`. Query jalur akar–v = `query(in[v]+1)`.

Update nilai v: kurangi lama, tambah baru di `in` dan `out`.

**Kapan:** jumlah/XOR jalur akar–v + update titik. Jalur u–v = `akar(u)+akar(v)−2·akar(lca)` plus/minus lca tergantung nilai di lca. Tetap butuh LCA. HLD lebih umum.

**Proses:**

```
seq: 0, 1, 3, 3, 4, 4, 1, 2, 5, 5, 2, 0
in[0]=0  out[0]=11
in[1]=1  out[1]=6
in[3]=2  out[3]=3
in[5]=8  out[5]=9
```

Nilai semua 1. Prefix in[5]: simpul terbuka 0,2,5 jumlah 3 = jalur 0-2-5.

**Kode:**

```cpp
struct EulerInOut {
    vector<int> in, out, seq;
    int timer = 0;

    void dfs(int v, int p, const vector<vector<int>>& g) {
        in[v] = timer;
        seq[timer++] = v;
        for (int u : g[v]) if (u != p) dfs(u, v, g);
        out[v] = timer;
        seq[timer++] = v;
    }

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        in.assign(n, 0);
        out.assign(n, 0);
        seq.assign(2 * n, 0);
        timer = 0;
        if (n) dfs(root, -1, g);
    }
};

struct PathToRoot {
    EulerInOut eu;
    BIT bit;
    vector<ll> val;
    int m;                                  // 2n

    PathToRoot(const vector<vector<int>>& g, const vector<ll>& a, int root = 0)
        : val(a) {
        eu.build(g, root);
        m = 2 * (int)a.size();
        bit.init(m + 2);
        for (int v = 0; v < (int)a.size(); v++) setVal(v, a[v]);
    }

    void setVal(int v, ll x) {
        ll d = x - val[v];
        val[v] = x;
        bit.update(eu.in[v] + 1, d);
        bit.update(eu.out[v] + 1, -d);
    }

    ll query(int v) const { return bit.query(eu.in[v] + 1); }
};
```

Jalur u–v dengan nilai simpul (butuh LCA):

```cpp
ll jumlahJalur(const PathToRoot& pt, const vector<int>& dep,
               function<int(int, int)> lca, int u, int v) {
    int w = lca(u, v);
    return pt.query(u) + pt.query(v) - 2 * pt.query(w) + pt.val[w];
}
```

**Jebakan:** dua gaya `out`. Jangan pakai `tout` gaya 1 di rumus `−x` gaya 2. `seq` panjang 2n, BIT `n` terlalu pendek.

**Kompleksitas:** O(n) bangun, O(log n) query.

## Campur nilai sisi

**Teori:** bobot sisi (ayah–v) diletakkan di simpul v (anak). Subtree sisi “di bawah v” = rentang `[tin[v]+1, tout[v]]` atau `[tin[v], tout[v]]` tergantung apakah sisi ke ayah ikut — biasanya **tidak** ikut di v, jadi skip `tin[v]`.

Jalur akar–v gaya 2: masukkan bobot saat masuk anak, batalkan saat keluar.

**Kapan:** CSES *Path Queries* sisi + hanya subtree, atau in-out.

**Proses:** sisi 1-3 bobot 7 di simpul 3. Subtree 1 (sisi dalam) = sisi 1-3 dan 1-4.

**Kode:**

```cpp
void taruhSisiDiAnak(int v, int p, const vector<vector<pair<int, int>>>& g,
                     vector<ll>& valAnak) {
    for (auto [u, w] : g[v]) if (u != p) {
        valAnak[u] = w;
        taruhSisiDiAnak(u, v, g, valAnak);
    }
}

ll jumlahSisiSubtree(const SubtreeSum& ss, int v) {
    if (ss.eu.tin[v] == ss.eu.tout[v]) return 0;   // daun: tidak ada sisi dalam
    return ss.bit.range(ss.eu.tin[v] + 2, ss.eu.tout[v] + 1);
}
```

Setelah `SubtreeSum` diisi `valAnak`, range skip `tin[v]` (nilai sisi ke ayah, atau 0 di akar).

**Jebakan:** menghitung sisi ke ayah dua kali. Update sisi (a,b): letakkan di `dep` lebih dalam.

**Kompleksitas:** sama.

## Yang bukan Euler subtree

**Teori:**

| Pertanyaan | Alat |
|---|---|
| jumlah/min subtree | Euler + BIT/Seg |
| apakah ancestor | tin/tout |
| jarak u–v statis | LCA |
| update + jumlah **jalur** | HLD |
| unik warna subtree | small-to-large |
| semua jalur jarak k | centroid |

`[tin[u], tin[v]]` **bukan** jalur u–v. Itu potongan urutan DFS, bisa memuat cabang asing.

**Kapan:** jika soal bilang “path”, tutup file ini kecuali in-out + LCA.

**Proses:** tin[3]=2, tin[5]=5, rentang [2,5] = simpul 3,4,2,5. Jalur 3–5 = 3,1,0,2,5. Berbeda.

**Kode:** jangan `bit.range(tin[u], tin[v])` untuk jalur.

**Jebakan:** tutorial “Euler tour tree” di graf umum (link-cut / make-root) berbeda dari flatten ini.

**Kompleksitas:** salah algoritma.

## Uji naif

**Teori:** jumlah subtree naif = DFS dari v menolak ayah menurut akar tetap. Banding BIT dan SegTree. Ancestor naif: naik ke akar.

**Kapan:** n ≤ 40.

**Proses:** pohon contoh, nilai 1..6. Subtree 1 = 11. Setelah set 3→10, 17. `ancestor(1,3)=1`, `(2,3)=0`.

**Kode:**

```cpp
ll jumlahNaif(int v, int p, const vector<vector<int>>& g, const vector<ll>& val) {
    ll s = val[v];
    for (int u : g[v]) if (u != p) s += jumlahNaif(u, v, g, val);
    return s;
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    vector<ll> a = {1, 2, 3, 4, 5, 6};
    SubtreeSum ss(g, a);
    SubtreeSeg sg(g, a);
    cout << ss.query(1) << ' ' << sg.query(1) << '\n';       // 11 11
    ss.setVal(3, 10);
    sg.setVal(3, 10);
    a[3] = 10;
    cout << ss.query(1) << ' ' << jumlahNaif(1, 0, g, a) << '\n'; // 17 17
    Euler eu;
    eu.build(g);
    cout << ancestor(eu, 1, 3) << ' ' << ancestor(eu, 2, 3) << '\n'; // 1 0
    PathToRoot pt(g, vector<ll>(6, 1));
    cout << pt.query(5) << '\n';                             // 3
}
```

**Jebakan:** naif dari v dengan `p=-1` merambah seluruh graf jika v bukan akar. Kirim ayah sungguhan (par[v]).

**Kompleksitas:** tes O(n) per query.

## Ringkasan

1. Gaya 1: subtree = `[tin, tout]` panjang n. Daun `tin==tout`.
2. Fenwick 1-based: `tin+1`. SegTree 0-based: `tin` langsung.
3. `ancestor` dari tin/tout O(1).
4. Dual: update subtree + baca titik = difference.
5. Gaya 2 in-out: jalur akar–v. Jangan campur `out`.
6. Jalur u–v: LCA + rumus, atau [hld.md](hld.md).

Latihan Day 199. Jangan salin folder ComprogLearning.
