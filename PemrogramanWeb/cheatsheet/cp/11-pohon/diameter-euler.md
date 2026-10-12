# Diameter dan Euler tour

[← Small-to-large](small-to-large.md) · [Pohon](README.md) · [LCA →](lca.md)

Day 198–199. Jalur terpanjang di pohon, dan meratakan subtree jadi segmen array.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Pohon = n simpul, n−1 sisi, terhubung, tanpa siklus. Ada **tepat satu** jalur sederhana antara dua simpul.

## Daftar isi

- [Pohon vs graf](#pohon-vs-graf)
- [Diameter dua BFS](#diameter-dua-bfs)
- [Rekonstruksi jalur](#rekonstruksi-jalur)
- [Pusat pohon](#pusat-pohon)
- [Diameter lewat DP](#diameter-lewat-dp)
- [Euler tour subtree](#euler-tour-subtree)
- [Subtree + BIT](#subtree--bit)
- [Euler in-out](#euler-in-out)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Pohon vs graf

**Teori:** jika ada siklus, “jalur terpanjang” NP-berat dan Euler subtree tidak unik. Teknik file ini butuh pohon (atau spanning tree yang kamu pilih sadar).

Akar dipilih. `par[v]`, `dep[v]` = jarak sisi ke akar. Subtree = v dan keturunan.

**Kapan:** soal menjamin pohon, atau m = n−1 dan terhubung. Jika m > n−1, kembali ke graf.

**Proses:** n=6, sisi `0-1, 0-2, 1-3, 1-4, 2-5`, akar 0.

```
        0
       / \
      1   2
     / \   \
    3   4   5
```

`par[3]=1`, `dep[5]=2`, subtree 1 = {1,3,4}. Jalur 3–5 = 3-1-0-2-5, unik.

**Kode:**

```cpp
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
        in >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    return g;
}
```

**Jebakan:** input 1-based. DFS tanpa menolak ayah. n=1: tidak ada sisi, diameter 0.

**Kompleksitas:** O(n).

## Diameter dua BFS

**Teori:** diameter = jalur terpanjang (jumlah sisi, atau bobot ≥ 0). Dua penelusuran:

1. Dari simpul mana pun, cari yang terjauh `u`.
2. Dari `u`, cari yang terjauh `v`.
3. Jalur `u–v` adalah diameter.

Sketsa: `u` adalah salah satu ujung diameter. Jika diameter `x–y` dan `u` bukan ujung, cabang dari `u` ke jalur itu menghasilkan kontradiksi dengan kejauhan `u` (bobot tak negatif).

**Kapan:**

- Pakai: jalur terpanjang, minimalkan tinggi setelah pilih pusat.
- Jangan: bobot negatif — dua BFS bisa salah.
- Jangan: graf umum.

**Proses:** mulai dari 0.

```
BFS1 dari 0: jarak 0,1,1,2,2,2  → u=3 (salah satu jarak 2)
BFS2 dari 3: 3:0, 1:1, 0:2, 4:2, 2:3, 5:4
v=5, diameter = 4
jalur 3-1-0-2-5
```

Jika mulai dari 2: BFS1 terjauh 3 atau 4, BFS2 tetap 4.

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
```

**Jebakan:** mengambil “paling dalam dari akar 0” sebagai ujung — salah jika 0 di tengah. Harus dua kali. Komponen >1: bukan pohon.

**Kompleksitas:** O(n).

## Rekonstruksi jalur

**Teori:** BFS kedua simpan `par`. Jalan dari `v` ke `u`.

**Kapan:** cetak jalur, cari pusat (tengah jalur).

**Proses:** dari 5: 5←2←0←1←3, reverse.

**Kode:**

```cpp
vector<int> jalurDiameter(const vector<vector<int>>& g) {
    if (g.empty()) return {};
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

**Jebakan:** `reverse` lupa. `par[u]` harus −1.

**Kompleksitas:** O(n).

## Pusat pohon

**Teori:** pusat = simpul yang meminimalkan eksentrisitas (jarak ke yang terjauh). Pada pohon: tengah diameter. Panjang ganjil (jumlah sisi): satu pusat. Genap: dua pusat bertetangga.

Tinggi setelah root di pusat = `ceil(diameter/2)`.

**Kapan:** “pilih ibu kota”, minimalkan max jarak.

**Proses:** jalur `[3,1,0,2,5]` panjang sisi 4, genap, dua tengah: indeks 2 dan 3 → simpul 0 dan 2.

```
path = [3,1,0,2,5]  size 5, tengah path[2]=0, dan untuk even edges juga path[1] atau path[2]?
sisi=4, simpul=5, dua pusat path[2] dan path[1]? 
tengah: path[sz/2] = path[2]=0 dan path[(sz-1)/2]=path[2]=0 tunggal?
```

Hati-hati definisi. Diameter 4 sisi, 5 simpul. Pusat: satu simpul di tengah (0) jika kita ukur simpul; dua sisi tengah 1-0 dan 0-2. Biasanya:

```
int mid1 = path[(int)path.size() / 2];
int mid0 = path[((int)path.size() - 1) / 2];
```

Untuk 5 simpul: mid0 = path[2]=0, mid1 = path[2]=0. Satu pusat.

Diameter 3 sisi, 4 simpul `[a,b,c,d]`: mid0=path[1], mid1=path[2] → dua pusat.

**Kode:**

```cpp
pair<int, int> pusat(const vector<vector<int>>& g) {
    auto path = jalurDiameter(g);
    int m = (int)path.size();
    if (m == 0) return {0, -1};
    int a = path[(m - 1) / 2];
    int b = path[m / 2];
    if (a == b) return {a, -1};
    return {a, b};
}
```

**Jebakan:** campur “panjang sisi” dan “banyak simpul”. Tes n=2: path dua simpul, dua pusat.

**Kompleksitas:** O(n).

## Diameter lewat DP

**Teori:** di setiap v, dua jalur turun terpanjang ke daun (anak berbeda). Belokan di v = jumlah keduanya (dalam sisi). Diameter = max belokan.

**Kapan:** sudah DFS berakar, butuh tinggi + diameter. Bobot sisi ≥ 0.

**Proses:** akar 0.

```
tinggi[3]=0, [4]=0, [5]=0
tinggi[1]=1, [2]=1, [0]=2
di 0: dua turun 2 dan 2 → belok 4
```

Jalur 3-1-0-2-5: 2+2 sisi dari 0.

**Kode:**

```cpp
int diameterDP(const vector<vector<int>>& g) {
    int n = (int)g.size();
    int ans = 0;
    function<int(int, int)> dfs = [&](int v, int p) -> int {
        int best1 = 0, best2 = 0;
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

Bobot:

```cpp
int dfsBobot(int v, int p, const vector<vector<pair<int, int>>>& g, ll& ans) {
    ll best1 = 0, best2 = 0;
    for (auto [u, w] : g[v]) if (u != p) {
        ll h = dfsBobot(u, v, g, ans) + w;
        if (h > best1) {
            best2 = best1;
            best1 = h;
        } else if (h > best2) best2 = h;
    }
    ans = max(ans, best1 + best2);
    return (int)best1;                      // jika w dan h muat int; lebih aman ll
}
```

Pakai `ll` murni jika bobot besar.

**Jebakan:** hanya satu “terpanjang”. Daun return 0 bukan −1. Pohon tidak terhubung: DFS satu akar buta.

**Kompleksitas:** O(n).

## Euler tour subtree

**Teori:** DFS mencatat `tin[v]` (masuk) dan `tout[v]` (keluar). Gaya 1: isi sekali saat masuk, `tout` inklusif = waktu terakhir di subtree. Subtree v = `[tin[v], tout[v]]` pada array panjang n.

`isAncestor(a,b)`: `tin[a] <= tin[b] && tout[b] <= tout[a]`.

**Kapan:** jumlah/min subtree, tambah seluruh subtree, cek leluhur. **Bukan** query jalur naik-turun.

**Proses:** anak kecil dulu.

```
DFS: 0, 1, 3, 4, 2, 5
tin:  0:0, 1:1, 3:2, 4:3, 2:4, 5:5
tout: 3:2, 4:3, 1:3, 5:5, 2:5, 0:5
subtree 1 = [1,3] = simpul 1,3,4
daun 3: tin=tout=2
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

    bool ancestor(int a, int b) const {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
    }
};
```

**Jebakan:** campur inklusif/eksklusif. Uji daun. Query jalur pakai `[tin[u], tin[v]]` **salah**.

**Kompleksitas:** O(n) bangun.

## Subtree + BIT

**Teori:** letakkan nilai simpul di indeks `tin[v]`. Jumlah subtree = range Fenwick `[tin, tout]`. Ingat Fenwick **1-based** di dalam: `update(tin+1)`.

**Kapan:** update titik + jumlah subtree. Update subtree + baca titik: difference pada `[tin, tout]`.

**Proses:** nilai `[1,2,3,4,5,6]` pada 0..5. Subtree 1 = 2+4+5 = 11. Set simpul 3 jadi 10: 2+10+5=17.

**Kode:** BIT ringkas 1-based.

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
    void build(const vector<ll>& a) {
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

**Jebakan:** `update(tin)` tanpa +1. Akar salah: subtree menurut akar lain butuh reroot.

**Kompleksitas:** O(n) bangun, O(log n) update/query.

## Euler in-out

**Teori:** array panjang 2n. Masuk +nilai, keluar −nilai (atau catat waktu `in/out`). Prefix sampai `in[v]` = jalur akar–v jika +saat masuk −saat keluar.

**Kapan:** jumlah jalur akar–v + BIT difference. HLD tetap lebih umum untuk jalur u–v.

**Proses:**

```
seq simpul: 0,1,3,3,4,4,1,2,5,5,2,0
in[3]=2, out[3]=3
```

**Kode:**

```cpp
void dfsInOut(int v, int p, const vector<vector<int>>& g,
              vector<int>& in, vector<int>& out, vector<int>& seq, int& t) {
    in[v] = t;
    seq[t++] = v;
    for (int u : g[v]) if (u != p) dfsInOut(u, p, g, in, out, seq, t);
    out[v] = t;
    seq[t++] = v;
}
```

Jumlah jalur akar–v dengan nilai simpul: BIT `update(in[v]+1, +x)`, `update(out[v]+1, −x)` (out gaya ini). Query `query(in[v]+1)`.

**Jebakan:** dua gaya `out` (inklusif subtree vs indeks keluar). Jangan campur dengan Euler gaya 1.

**Kompleksitas:** O(n).

## Uji naif

**Teori:** diameter naif O(n²) BFS dari setiap simpul. Subtree naif DFS jumlah.

**Kapan:** n ≤ 40.

**Proses:** rantai 0-1-2-3, diameter 3. Bintang, diameter 2.

**Kode:**

```cpp
int diameterNaif(const vector<vector<int>>& g) {
    int n = (int)g.size(), best = 0;
    for (int s = 0; s < n; s++) best = max(best, jauhDari(s, g).second);
    return best;
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    cout << diameter(g) << ' ' << diameterDP(g) << ' '
         << diameterNaif(g) << '\n';        // 4 4 4
    Euler eu;
    eu.build(g);
    cout << eu.ancestor(1, 3) << ' ' << eu.ancestor(2, 3) << '\n'; // 1 0
}
```

**Jebakan:** naif di graf berbobot negatif tidak setara “terjauh BFS”.

**Kompleksitas:** naif O(n²).

## Ringkasan

1. Diameter: dua BFS/DFS, atau DP dua cabang. Bobot ≥ 0.
2. Pusat di tengah jalur diameter.
3. Euler gaya 1: subtree = `[tin, tout]`, lalu Fenwick 1-based.
4. `ancestor` dari tin/tout. Jalur ≠ subtree.
5. In-out untuk prefix akar–v.
6. Lanjut [lca.md](lca.md) untuk jarak u–v.

Latihan Day 198–199. Jangan salin latihan ComprogLearning.
