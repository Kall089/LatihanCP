# 17 — Diameter, Euler tour, LCA, HLD, centroid

[← 16 struktur data](16-segtree-bit-sparse-mo.md) · [README](README.md) · [Lanjut 18 →](18-string-hash-kmp-z-trie.md)

Folder 11 di `DAFTAR-MATERI`: **pohon** sebagai graf khusus (n simpul, n−1 sisi, tidak ada siklus). Banyak soal “jalur”, “subtree”, “leluhur bersama” selesai di sini. HLD dan centroid adalah ide besar; kode lengkapnya panjang — pahami dulu apa yang dipecah.

Latihan harian: `ComProgLearning/CP` Day 193 (small-to-large), 198 (diameter), 199 (Euler tour), 201 (binary lifting), 204 (HLD), 206 (centroid).

Graf 0-indexed. Pohon biasanya di-root di 0 kecuali soal menentukan akar. `typedef long long ll`.

## Daftar isi

- [Pohon vs graf](#pohon-vs-graf)
- [Diameter dua DFS](#diameter-dua-dfs)
- [Diameter lewat DP](#diameter-lewat-dp)
- [Euler tour dan query subtree](#euler-tour-dan-query-subtree)
- [Binary lifting](#binary-lifting)
- [LCA](#lca)
- [Jarak dan jalur lewat LCA](#jarak-dan-jalur-lewat-lca)
- [HLD — ide](#hld--ide)
- [Centroid — ide](#centroid--ide)
- [Small-to-large (singkat)](#small-to-large-singkat)
- [Tabel pilih teknik pohon](#tabel-pilih-teknik-pohon)
- [Ringkasan](#ringkasan)

## Pohon vs graf

**Teori:** pohon = graf terhubung tanpa siklus. Akibat langsung: ada **tepat satu** jalur sederhana antara dua simpul. Itu alasan diameter, LCA, dan HLD masuk akal. Jika ada siklus, “jalur” tidak unik dan hampir semua rumus di file ini rusak.

Akar dipilih. Setiap simpul kecuali akar punya satu **ayah**. Anak-anak membentuk **subtree**. Kedalaman `dep[v]` = jarak ke akar (jumlah sisi).

**Kapan dipakai / kapan tidak.**

- Pakai teknik pohon hanya jika soal menjamin pohon, atau kamu sudah mengambil *spanning tree*.
- Jika n simpul dan m > n−1 sisi, ini graf. Kembali ke file 10–12.

**Proses:** n=6, sisi `0-1, 0-2, 1-3, 1-4, 2-5`, akar 0.

```
        0
       / \
      1   2
     / \   \
    3   4   5
```

`par[0]=-1`, `par[1]=0`, `par[3]=1`. Subtree 1 = {1,3,4}. Jalur 3–5 = 3-1-0-2-5, unik.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfsAkar(int v, int p, const vector<vector<int>>& g,
             vector<int>& par, vector<int>& dep) {
    par[v] = p;
    for (int u : g[v]) if (u != p) {
        dep[u] = dep[v] + 1;
        dfsAkar(u, v, g, par, dep);
    }
}

vector<vector<int>> bacaPohon(int n, istream& in) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        in >> a >> b;                       // sudah 0-based
        g[a].push_back(b);
        g[b].push_back(a);
    }
    return g;
}
```

**Jebakan:** soal 1-based — kurangi 1 saat baca. DFS tanpa menolak ayah mengunjungi ayah lagi dan seolah-olah ada siklus. n=1: tidak ada sisi, diameter 0.

**Kompleksitas:** bangun dan DFS O(n).

## Diameter dua DFS

**Teori:** diameter = jalur terpanjang (jumlah sisi, atau jumlah bobot). Di pohon **tanpa bobot negatif**, cukup dua DFS/BFS:

1. Dari simpul mana pun, cari simpul terjauh `u`.
2. Dari `u`, cari simpul terjauh `v`.
3. Jalur `u–v` adalah diameter.

Kenapa benar (sketsa): `u` pasti salah satu ujung diameter. Jika ujung diameter adalah `x–y` dan `u` bukan `x` atau `y`, jalur dari `u` ke jalur `x–y` menempel di suatu titik. Karena `u` paling jauh dari titik start, kontradiksi kecuali `u` berimpit dengan ujung. Bukti lengkap ada di Day 198; untuk kontes, ingat syarat: pohon, bobot tak negatif.

**Kapan dipakai / kapan tidak.**

- Pakai: “jalur terpanjang”, “minimalkan tinggi setelah memilih pusat”, dua pusat (pohon even/odd diameter).
- Jangan: ada bobot negatif — dua DFS bisa salah.
- Jangan: graf umum — itu *longest path*, NP-berat.

**Proses:** pohon di atas, mulai dari 0.

```
DFS1 dari 0: jarak  0:0, 1:1, 2:1, 3:2, 4:2, 5:2
terjauh u = 3 (salah satu yang jarak 2)

DFS2 dari 3: 3:0, 1:1, 0:2, 4:2, 2:3, 5:4
terjauh v = 5, jarak 4
diameter = 4     jalur 3-1-0-2-5
```

**Kode:**

```cpp
pair<int, int> jauhDari(int start, const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int best = start;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] > dist[best]) best = v;
        for (int u : g[v]) if (dist[u] == -1) {
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
    return {best, dist[best]};
}

int diameter(const vector<vector<int>>& g) {
    if (g.empty()) return 0;
    int u = jauhDari(0, g).first;
    return jauhDari(u, g).second;
}

// rekonstruksi simpul di jalur diameter
vector<int> jalurDiameter(const vector<vector<int>>& g) {
    int u = jauhDari(0, g).first;
    int n = (int)g.size();
    vector<int> par(n, -1), dist(n, -1);
    queue<int> q;
    q.push(u);
    dist[u] = 0;
    int v = u;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (dist[x] > dist[v]) v = x;
        for (int y : g[x]) if (dist[y] == -1) {
            dist[y] = dist[x] + 1;
            par[y] = x;
            q.push(y);
        }
    }
    vector<int> path;
    for (int x = v; x != -1; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());
    return path;
}
```

Pusat pohon: jika panjang jalur genap, dua pusat di tengah; jika ganjil, satu pusat. Berguna untuk “akar yang meminimalkan tinggi”.

**Jebakan:** mengambil “simpul terdalam dari akar 0” sebagai ujung — salah jika akar di tengah. Harus dua kali. Bobot: ganti BFS jadi Dijkstra hanya jika bobot ≥ 0 dan kamu tetap memakai argumen yang sama; lebih aman DFS berbobot dari u.

**Kompleksitas:** O(n) waktu, O(n) memori.

## Diameter lewat DP

**Teori:** untuk setiap simpul, hitung dua jalur turun terpanjang ke daun (lewat anak berbeda). Diameter yang “membelok” di `v` = jumlah dua jalur itu. Diameter global = maksimum belokan. Ini merangkap jika nanti kamu butuh lebih dari sekadar angka diameter (misalnya DP lain di pohon).

**Kapan dipakai / kapan tidak.**

- Pakai: sudah DFS berakar, ingin diameter + tinggi subtree sekaligus.
- Pakai: bobot sisi, asalkan tidak negatif atau kamu sadar “terpanjang” vs “terpendek”.
- Dua BFS lebih pendek jika hanya butuh angka.

**Proses:** akar 0.

```
tinggi[3]=0, [4]=0, [5]=0
tinggi[1]=1, [2]=1, [0]=2
di 1: dua turun 0 dan 0 → belok 0
di 0: dua turun 2 dan 2 → belok 4     (1+1 + 2 sisi ke daun? 
  jalur turun dari 0 lewat 1: 0-1-3 panjang 2
  lewat 2: 0-2-5 panjang 2
  belok = 2+2 = 4)
```

**Kode:**

```cpp
int diameterDP(const vector<vector<int>>& g) {
    int n = (int)g.size();
    int ans = 0;
    function<int(int, int)> dfs = [&](int v, int p) -> int {
        int best1 = 0, best2 = 0;           // tinggi turun, dalam sisi
        for (int u : g[v]) if (u != p) {
            int h = dfs(u, v) + 1;
            if (h > best1) {
                best2 = best1;
                best1 = h;
            } else if (h > best2) best2 = h;
        }
        ans = max(ans, best1 + best2);
        return best1;
    };
    if (n) dfs(0, -1);
    return ans;
}
```

**Jebakan:** menyimpan hanya satu “terpanjang” lalu belokan kehilangan jalur kedua. Daun mengembalikan 0, bukan −1. Pohon tidak terhubung (bukan pohon) → DFS satu akar tidak melihat komponen lain.

**Kompleksitas:** O(n).

## Euler tour dan query subtree

**Teori:** DFS mencatat waktu masuk `tin[v]` dan keluar `tout[v]`. Letakkan nilai simpul di posisi `tin[v]` pada array datar. Subtree `v` = segmen beruntun `[tin[v], tout[v]]` (jika `tout` inklusif dan kamu mengisi sekali) **atau** `[tin[v], tout[v])` tergantung konvensi.

Dua gaya populer:

1. **Masuk saja.** `tin[v]` unik 0..n−1, `tout[v]` = waktu terakhir di subtree. Subtree = `[tin[v], tout[v]]` pada array `euler` sepanjang n.
2. **Masuk dan keluar.** Array panjang 2n, +nilai saat masuk, −nilai saat keluar. Prefix sampai `tin[v]` = jalur akar–v. Berguna untuk query jalur jika digabung HLD/BIT.

Di sini gaya 1: meratakan subtree menjadi range query. Lalu pasang Fenwick / Segment Tree dari file 16.

**Kapan dipakai / kapan tidak.**

- Pakai: “jumlah/min di subtree”, “tambah 1 ke seluruh subtree”, “apakah a ancestor b”.
- Jangan: query jalur `u–v` yang naik-turun — Euler tour subtree **bukan** jalur. Jalur butuh LCA + HLD atau Euler+RMQ khusus.

**Proses:** pohon contoh, urutan DFS anak dari kecil.

```
DFS: 0, 1, 3, 4, 2, 5
tin:  0:0, 1:1, 3:2, 4:3, 2:4, 5:5
tout: 3:2, 4:3, 1:3, 5:5, 2:5, 0:5
subtree 1 = [tin=1, tout=3] = simpul 1,3,4
```

`isAncestor(a, b)`: `tin[a] <= tin[b] && tout[b] <= tout[a]`.

**Kode:**

```cpp
struct Euler {
    vector<int> tin, tout, id;              // id[t] = simpul dengan tin=t
    int timer = 0;

    void dfs(int v, int p, const vector<vector<int>>& g) {
        tin[v] = timer;
        id[timer] = v;
        timer++;
        for (int u : g[v]) if (u != p) dfs(u, v, g);
        tout[v] = timer - 1;                // inklusif
    }

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        tin.assign(n, 0);
        tout.assign(n, 0);
        id.assign(n, 0);
        timer = 0;
        if (n) dfs(root, -1, g);
    }

    bool ancestor(int a, int b) const {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }
};

// jumlah nilai subtree, update titik — pakai BIT 1-based pada tin
struct SubtreeSum {
    Euler eu;
    BIT bit;                                // dari file 16, atau tempel ulang
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

Jika `BIT` belum ditempel, salin struct dari file 16. Untuk file ini berdiri sendiri, tempel `BIT` pendek di atas `SubtreeSum` saat compile.

Euler **in-out** untuk jalur akar–v:

```cpp
void dfsInOut(int v, int p, const vector<vector<int>>& g,
              vector<int>& in, vector<int>& out, vector<int>& seq, int& t) {
    in[v] = t;
    seq[t++] = v;                           // +v
    for (int u : g[v]) if (u != p) dfsInOut(u, p, g, in, out, seq, t);
    out[v] = t;
    seq[t++] = v;                           // v lagi (keluar)
}
```

**Jebakan:**

- Mencampur inklusif/eksklusif `tout`. Pilih satu, uji subtree daun: `tin==tout` pada gaya 1.
- Query jalur pakai `[tin[u], tin[v]]` — **salah**, itu bukan jalur.
- Akar salah: Euler bergantung akar. Soal “pohon tanpa akar” tetap pilih 0, kecuali query “subtree” menurut akar lain (reroot, file 15).

**Kompleksitas:** bangun O(n), query/update mengikuti BIT/segtree O(log n).

## Binary lifting

**Teori:** `up[k][v]` = leluhur ke-`2^k` dari `v`. `up[0][v] = ayah`. `up[k][v] = up[k-1][up[k-1][v]]`. Naik `d` langkah: tulis `d` dalam biner, lompat bit yang menyala. Sama seperti Sparse Table, tetapi di rantai ayah.

```
naik 13 = 8+4+1 langkah: lompat 2^3, 2^2, 2^0
```

**Kapan dipakai / kapan tidak.**

- Pakai: leluhur ke-k, LCA, “naik sampai syarat gagal” (binary search di jalur naik).
- Jangan: graf dengan siklus sebagai “ayah” — tidak terdefinisi.

**Proses:** pohon contoh.

```
v     0  1  2  3  4  5
up0  -1  0  0  1  1  2
up1  -1 -1 -1  0  0  0     (kakek, 2 langkah)
```

Leluhur ke-2 dari 3: `up[1][3] = 0`. Leluhur ke-3 dari 3: naik 1 ke 1, lalu naik 2 ke `up[1][1] = -1` → tidak ada, sudah lewat akar.

**Kode:**

```cpp
struct Lift {
    int LOG;
    vector<int> dep;
    vector<vector<int>> up;

    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
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

    int naik(int v, int d) const {
        if (d < 0 || (v != -1 && d > dep[v])) return -1;
        for (int k = 0; k < LOG && v != -1; k++)
            if (d & (1 << k)) v = up[k][v];
        return v;
    }
};
```

**Jebakan:** `LOG` terlalu kecil (`16` untuk n=2·10^5 → 2^16=65536 < n, naik jauh rusak). Pakai 18–20, atau hitung dari n. `up[k-1][v]==-1` harus tetap `-1`, bukan `up[k-1][0]`.

**Kompleksitas:** build O(n log n), naik O(log n), memori O(n log n).

## LCA

**Teori:** LCA(u, v) = leluhur bersama yang **paling dalam** (paling jauh dari akar). Jalur `u–v` = `u ↗ LCA ↘ v`. Semua pertemuan jalur ke akar terjadi di rantai LCA–akar.

Algoritma binary lifting:

1. Jika `dep[u] < dep[v]`, tukar.
2. Naikkan `u` sampai kedalaman sama dengan `v`.
3. Jika sudah sama, itu LCA (satu di bawah yang lain).
4. Naikkan keduanya **bersamaan** dari bit besar: jika ayah ke-`2^k` berbeda, lompat. Berhenti saat `up[0][u]==up[0][v]`.
5. Ayah itulah LCA.

Kenapa bit besar dulu: sama seperti binary search. Kita tidak boleh melewati LCA. Lompat hanya jika masih di bawah LCA (ayah 2^k berbeda artinya belum ketemu).

**Kapan dipakai / kapan tidak.**

- Pakai: jarak, “apakah w di jalur u–v”, query jalur (dengan HLD atau prefix di akar).
- Alternatif: Euler tour + RMQ (Sparse Table argmin pada kedalaman). Query O(1), build O(n log n). Bagus jika banyak query, tidak perlu `naik`.

**Proses:** LCA(3, 5) pada pohon contoh.

```
dep[3]=2, dep[5]=2  sudah sama
up[1][3]=0, up[1][5]=0  sama → jangan lompat 2
up[0][3]=1, up[0][5]=2  berbeda → lompat ke 1 dan 2
ayah keduanya = 0 = LCA
```

LCA(3, 4): setelah samakan depth, `u=3, v=4`, ayah langsung sama 1, dan 3≠4 → LCA=1.

**Kode:**

```cpp
struct LCA : Lift {
    int get(int u, int v) const {
        if (u == -1 || v == -1) return -1;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 6;
    vector<vector<int>> g(n);
    auto tambah = [&](int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    };
    tambah(0, 1); tambah(0, 2); tambah(1, 3);
    tambah(1, 4); tambah(2, 5);
    LCA lca;
    lca.build(g, 0);
    cout << lca.get(3, 5) << '\n';          // 0
    cout << lca.get(3, 4) << '\n';          // 1
    cout << lca.get(2, 5) << '\n';          // 2
}
```

Versi Euler + RMQ (ide, cukup untuk query O(1)):

```
DFS catat setiap kunjungan (masuk ke anak, kembali ke ayah).
Array euler kedalaman: 0,1,3,1,4,1,0,2,5,2,0
LCA(u,v) = simpul dengan dep minimum pada segmen antara
kemunculan pertama u dan kemunculan pertama v.
```

Pakai `SparseArgMin` file 16 pada array `dep[euler[i]]`.

**Jebakan:**

- Setelah samakan depth, lupa kasus `u==v`.
- Loop bit dari kecil: bisa “loncat melewati” dan tidak ketemu.
- LCA dari dua akar berbeda (hutan): `get` bisa −1; cek komponen dulu.
- Soal 1-based, kamu 0-based, LCA 0 tercetak 0 lalu dianggap salah.

**Kompleksitas:** build O(n log n), query O(log n). Euler+RMQ: query O(1).

## Jarak dan jalur lewat LCA

**Teori:** `dist(u, v) = dep[u] + dep[v] − 2·dep[LCA]`. Jika sisi berbobot, ganti `dep` dengan jarak terberat dari akar `distRoot`.

`w` ada di jalur `u–v` jika `dist(u,v) = dist(u,w) + dist(w,v)`.

Titik ke-k di jalur `u→v` (0 = u):

- `len = dist(u,v)`. Jika `k > len` tidak ada.
- `du = dep[u] - dep[lca]`. Jika `k <= du`, naik `k` dari u.
- Jika tidak, naik `len-k` dari v.

**Kapan dipakai / kapan tidak.**

- Pakai: hampir semua soal jarak di pohon tanpa update sisi.
- Update sisi: prefix ke akar rusak; pindah ke HLD + segtree.

**Proses:** dist(3,5) = 2+2−2·0 = 4. Titik ke-2 dari 3 ke 5: `du=2`, k=2 ≤ 2 → naik 2 dari 3 = 0.

**Kode:**

```cpp
int jarak(const LCA& lca, int u, int v) {
    int w = lca.get(u, v);
    return lca.dep[u] + lca.dep[v] - 2 * lca.dep[w];
}

bool diJalur(const LCA& lca, int u, int v, int w) {
    return jarak(lca, u, v) == jarak(lca, u, w) + jarak(lca, w, v);
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

**Jebakan:** rumus jarak memakai `dep` sisi-unit. Kalau DFS `dep` diisi salah (lupa +1), semua jarak runtuh. `titikKeK` off-by-one di puncak LCA: k=du harus kembali LCA, bukan anak.

**Kompleksitas:** O(log n) per pertanyaan.

## HLD — ide

**Teori:** Heavy-Light Decomposition memecah pohon menjadi **rantai** (jalur turun) sehingga setiap jalur `u–v` terpecah menjadi O(log n) potongan beruntun. Tiap rantai dilinierkan ke array, lalu Segment Tree menjawab query potongan.

Cara memecah:

1. Hitung `sz[v]` = ukuran subtree.
2. Anak **berat** = anak dengan `sz` terbesar. Sisi ke anak berat = **heavy**. Sisi lain = **light**.
3. Rantai: mulai dari simpul yang bukan anak berat (kepala rantai), ikut terus sisi heavy ke bawah.

Mengapa O(log n) potongan: setiap kali kamu naik lewat sisi **light**, ukuran subtree **minimal berlipat dua** (karena light berarti ada saudara yang tidak lebih kecil — sebenarnya: sisi light menuju ayah yang subtree-nya > 2·sz[anak]). Jadi paling banyak log n sisi light di jalur ke akar. Tiap lompat rantai = satu query segtree.

Analogi: jalan tol (heavy) dan jalan kampung (light). Perjalanan ke ibu kota: kamu hampir selalu di tol, sesekali belok masuk gerbang baru. Jumlah gerbang sedikit.

Query jalur `u–v`:

```
selama head[u] != head[v]:
    biarkan yang lebih dalam naik dulu
    jawab segmen [pos[head[x]], pos[x]] pada rantai x
    x = ayah[head[x]]
sisanya u dan v satu rantai: jawab [pos[u], pos[v]]
```

Query subtree: `sz[v]` simpul beruntun jika urutan DFS mengunjungi anak berat **dulu** — `pos[v] .. pos[v]+sz[v]-1`. Itu bonus: HLD sekaligus Euler yang ramah rantai.

**Kapan dipakai / kapan tidak.**

- Pakai: update/query pada **jalur** atau subtree, n,q 10^5, operasi asosiatif (jumlah, min, XOR).
- Jangan: hanya jarak statis — LCA cukup.
- Jangan: minggu pertama belajar pohon. Hafalkan LCA + Euler dulu.

**Proses:** pohon contoh. `sz`: 3=1,4=1,5=1,1=3,2=2,0=6. Anak berat 0 adalah 1 (sz 3>2). Anak berat 1 adalah 3 atau 4 (sama, pilih 3).

```
rantai head 0: 0-1-3     pos: 0,1,3 → indeks 0,1,2
rantai head 4: 4         pos 3
rantai head 2: 2-5       pos 4,5
```

Jalur 4–5: 4 naik ke 1 (satu query rantai 4), 1 dan 0 satu rantai, 2–5 rantai lain. Tiga potongan. O(log n) di pohon besar.

**Kode (kerangka, fungsi modular):**

```cpp
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, pos;
    int timer = 0;

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

    // panggil f(L, R) untuk tiap segmen pos inklusif di jalur u-v
    template <class F>
    void jalur(int u, int v, F f) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            f(pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        f(pos[u], pos[v]);                  // termasuk LCA
        // jika query sisi (bukan simpul), mulai dari anak: f(pos[u]+1, pos[v])
    }
};
```

Pasang `SegSum` pada array `val` yang diisi `base[v]` di indeks `pos[v]`. Query jumlah jalur: akumulasi `seg.range(L, R)` di dalam `f`.

**Jebakan:**

- Anak berat tidak dikunjungi dulu di `dfsPos` → rantai tidak beruntun di `pos`.
- Query sisi vs simpul: LCA terhitung dua kali atau sisi ke LCA ikut — tentukan dulu objek di segmen.
- Komutatif: min dan sum OK. Operasi **tidak komutatif** (misalnya concatenasi) butuh arah naik/turun terpisah.
- Lupa `u = par[head[u]]` → loop tak hingga jika `head` salah.

**Kompleksitas:** build O(n), query/update jalur O(log² n) jika segtree O(log n) per potongan. Memori O(n).

## Centroid — ide

**Teori:** centroid = simpul yang setiap komponen sisa, setelah ia dihapus, berukuran ≤ n/2. Setiap pohon punya satu atau dua centroid. Kamu bisa **membangun pohon centroid**: pilih centroid, hapus, ulangi di tiap komponen. Tinggi pohon centroid O(log n) karena tiap level ukuran terpotong ≥ setengah.

Pakai: soal “pasangan simpul dengan sifat pada jarak”, “jumlah jalur yang memenuhi”, “update titik + query min jarak ke himpunan”. Ide: setiap jalur melewati tepat satu centroid “tertinggi” (pertama yang memisahkan). Hitung kontribusi di centroid itu, lalu rekursi.

Analogi: ibukota yang membelah negara jadi provinsi kecil. Sensus jalur: hitung yang lewat ibukota, lalu tiap provinsi mengurus sendiri.

Cari centroid:

1. Hitung `sz` di komponen yang masih hidup.
2. Jalan dari akar komponen: selama ada anak (di komponen) dengan `sz > nKomp/2`, pindah ke sana.
3. Berhenti: itu centroid.

Tandai `mati[c]=true` lalu rekursi.

**Kapan dipakai / kapan tidak.**

- Pakai: menghitung sesuatu pada **semua jalur**, divide-and-conquer pada pohon, atau struktur “centroid + info jarak”.
- Jangan: query jalur update biasa — HLD lebih langsung.
- Jangan: menulis centroid decomposition lengkap di 20 menit pertama kontes jika belum pernah AC soal CSES *Distance Queries* / CF centroid klasik.

**Proses:** pohon rantai 0-1-2-3-4, n=5.

```
sz dari 0: 5,4,3,2,1
jalan: 0 punya anak sz=4 > 2, pindah 1
1 punya anak sz=3 > 2, pindah 2
2 punya anak sz=2 yang tidak > 2.5? 2 > 5/2=2? tidak
centroid = 2     komponen {0,1} dan {3,4}
```

**Kode (cari + kerangka decomp):**

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

    // contoh: hitung pasangan jarak tepat k (tanpa bobot)
    ll pasanganJarak;
    int targetK;
    void kumpulkan(int v, int p, int d, vector<int>& daftar) {
        daftar.push_back(d);
        for (int u : g[v])
            if (u != p && !mati[u]) kumpulkan(u, v, d + 1, daftar);
    }

    void proses(int c) {
        map<int, int> sudah;
        sudah[0] = 1;                       // centroid sendiri
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
};
```

`map` di `proses` O(n log² n) dan mudah. Untuk n besar, ganti `map` jadi array/frekuensi + bucket jarak, atau FFT/centroid + convolution (lanjutan).

**Jebakan:**

- Lupa `mati` → `hitungSz` merambah komponen yang sudah dihapus, sz salah, centroid salah, sering TLE/stack.
- Menghitung pasangan **dua kali**: jalur yang tidak lewat centroid ikut terhitung di level bawah, jadi di `proses` hanya jalur yang **lewat c** (dua kaki berbeda, atau satu kaki + c).
- `nKomp/2` integer: sz == nKomp/2 boleh, tidak wajib pindah.
- Memakai centroid untuk query online tanpa menyimpan pohon centroid + data — kerangka di atas hanya **offline hitung**.

**Kompleksitas:** tiap simpul jadi centroid sekali, tiap level menelusuri komponennya: O(n log n) traversal. Kerja tambahan di `proses` menentukan total (sering O(n log n) atau O(n log² n)).

## Small-to-large (singkat)

**Teori:** DSU on tree. Ingin himpunan nilai di setiap subtree. Jika kamu menggabungkan himpunan anak ke ayah dengan menyalin yang kecil ke yang besar, tiap nilai pindah O(log n) kali (ukuran himpunan yang memuatnya minimal dobel). Total O(n log n).

Versi sack: pertahankan data anak berat, rekursi anak ringan sambil menambah, lalu hapus anak ringan jika ayah tidak mewarisi.

**Kapan dipakai / kapan tidak.**

- Pakai: “banyak warna berbeda di subtree”, query subtree offline.
- Jangan: query jalur — bukan domainnya.

**Proses:** pohon contoh, warna `[1, 2, 1, 3, 2, 1]` pada 0..5.

```
subtree 1 = {1,3,4} warna 2,3,2 → unik 2
subtree 0 = semua → unik 3
```

Sack: anak berat 0 adalah 1. DFS 2 dulu (`keep=false`), catat, hapus; DFS 1 (`keep=true`) mewarisi {2,3}; tambah 0 (warna 1) dan subtree 2 lagi. `ans[0]=3`.

**Kode:**

```cpp
void tambahWarna(int c, int d, vector<int>& cnt, int& jenis) {
    if (d > 0) {
        if (cnt[c]++ == 0) jenis++;
    } else {
        if (--cnt[c] == 0) jenis--;
    }
}

void dfsSack(int v, int p, bool keep,
             const vector<vector<int>>& g,
             const vector<int>& sz, const vector<int>& heavy,
             const vector<int>& tin, const vector<int>& tout,
             const vector<int>& id, const vector<int>& warna,
             vector<int>& cnt, int& jenis, vector<int>& ans) {
    for (int u : g[v])
        if (u != p && u != heavy[v])
            dfsSack(u, v, false, g, sz, heavy, tin, tout, id, warna,
                    cnt, jenis, ans);
    if (heavy[v] != -1)
        dfsSack(heavy[v], v, true, g, sz, heavy, tin, tout, id, warna,
                cnt, jenis, ans);
    tambahWarna(warna[v], +1, cnt, jenis);
    for (int u : g[v]) if (u != p && u != heavy[v])
        for (int t = tin[u]; t <= tout[u]; t++)
            tambahWarna(warna[id[t]], +1, cnt, jenis);
    ans[v] = jenis;
    if (!keep)
        for (int t = tin[v]; t <= tout[v]; t++)
            tambahWarna(warna[id[t]], -1, cnt, jenis);
}
```

`tin/tout/id` dari Euler gaya 1. `heavy` dari HLD `dfsSz`. Warna dikompresi ke 0..n-1.

**Jebakan:** menghapus data anak berat yang seharusnya diwariskan ke ayah. `keep` salah = WA sunyi. Menambah `v` dua kali jika kamu juga mengiterasi subtree berat.

**Kompleksitas:** O(n log n) add/remove. Memori O(n).

## LCA lewat Euler + RMQ

**Teori:** DFS mencatat setiap *kunjungan* (masuk dan kembali). LCA(u, v) = simpul **paling dangkal** pada segmen euler antara kemunculan pertama u dan pertama v. Itu RMQ pada array kedalaman — Sparse Table argmin, query O(1).

**Kapan dipakai / kapan tidak.** Banyak query LCA, tidak perlu `naik(k)`. Jika butuh titik ke-k di jalur, binary lifting tetap lebih enak.

**Proses:** euler kedalaman pohon contoh (anak kecil dulu):

```
seq : 0 1 3 1 4 1 0 2 5 2 0
dep : 0 1 2 1 2 1 0 1 2 1 0
first[3]=2, first[5]=8
RMQ dep pada [2,8] → indeks 6, simpul 0 = LCA
```

**Kode:**

```cpp
struct LCA_RMQ {
    vector<int> first, euler, depE;
    SparseArgMin st;                        // file 16, simpan indeks

    void dfs(int v, int p, int d, const vector<vector<int>>& g,
             vector<int>& dep) {
        first[v] = (int)euler.size();
        euler.push_back(v);
        depE.push_back(d);
        dep[v] = d;
        for (int u : g[v]) if (u != p) {
            dfs(u, v, d + 1, g, dep);
            euler.push_back(v);
            depE.push_back(d);
        }
    }

    vector<int> dep;
    void build(const vector<vector<int>>& g, int root = 0) {
        int n = (int)g.size();
        first.assign(n, -1);
        dep.assign(n, 0);
        euler.clear();
        depE.clear();
        if (n) dfs(root, -1, 0, g, dep);
        st.build(depE);
    }

    int get(int u, int v) const {
        int a = first[u], b = first[v];
        if (a > b) swap(a, b);
        return euler[st.queryIdx(a, b)];
    }
};
```

Tempel `SparseArgMin` dari file 16 di atas struct ini.

**Jebakan:** RMQ pada `first[u]..first[v]` memakai kemunculan **pertama**, bukan sembarang. Array euler panjang 2n−1, bukan n.

**Kompleksitas:** build O(n log n), query O(1).

## Jarak berbobot

**Teori:** ganti `dep` sisi-unit dengan `distRoot[v]` = jumlah bobot dari akar. Rumus sama: `dist(u,v) = distRoot[u] + distRoot[v] − 2·distRoot[lca]`. Update sisi merusak `distRoot` — pindah ke HLD.

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

`LCA::build` tetap memakai sisi tak berbobot untuk ayah/kedalaman (jumlah sisi). `naik` masih benar. Yang berubah hanya rumus jarak.

**Jebakan:** mengisi `dep` dengan bobot lalu `naik(d)` meloncat “d sisi” padahal d adalah kilogram. Pisahkan `dep` (sisi) dan `distRoot` (bobot).

**Kompleksitas:** sama O(n log n) build, O(log n) query.

## Tabel pilih teknik pohon

| Soal | Alat |
| --- | --- |
| jalur terpanjang | 2× BFS/DFS |
| jumlah/min subtree, update titik | Euler + BIT/segtree |
| apakah a leluhur b | Euler `tin/tout` |
| jarak, LCA, titik ke-k | binary lifting |
| banyak query LCA, array statis | Euler + Sparse Table |
| update/query **jalur** | HLD + segtree |
| hitung semua jalur / jarak k | centroid |
| banyak unik di tiap subtree | small-to-large |
| jawaban untuk setiap akar | reroot (file 15) |

Urutan belajar yang hemat WA:

```
1. DFS parent/dep/sz
2. Diameter
3. Euler subtree
4. Binary lifting + LCA + jarak
5. Baru HLD
6. Baru centroid
```

Melompat ke HLD sebelum LCA biasanya menghasilkan kode 200 baris yang tidak bisa di-debug.

## Ringkasan

1. Pohon = satu jalur unik. Itu izin semua rumus di sini.
2. Diameter: dua penelusuran dari ujung, atau DP dua cabang.
3. Euler tour mengubah subtree menjadi `[tin, tout]` — lalu file 16 yang bekerja.
4. Binary lifting = Sparse Table di rantai ayah. LCA = samakan depth, naik bareng.
5. `dist(u,v) = dep[u]+dep[v]−2·dep[lca]`.
6. HLD: rantai heavy, jalur jadi O(log n) segmen array.
7. Centroid: potong di tengah, tinggi decomp O(log n), hitung jalur yang “bertemu” di sana.

Latihan: CSES *Tree Diameter*, *Subtree Queries*, *Company Queries II*, lalu *Path Queries*. Folder Day 198–206 di `ComProgLearning/CP` mengikuti urutan yang sama. Jangan lompat ke HLD sebelum tiga soal LCA berstatus AC.
