# Diameter pohon

[← Small-to-large](small-to-large.md) · [Pohon](README.md) · [Euler tour →](euler-tour.md)

Day **198**. Jalur sederhana terpanjang di pohon: dua DFS (atau dua BFS) dan tree DP dua cabang. Pusat, radius, dan rekonstruksi jalur ikut di sini. Flatten subtree ada di [euler-tour.md](euler-tour.md).

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Pohon = n simpul, n−1 sisi, terhubung, tanpa siklus. Ada **tepat satu** jalur sederhana antara dua simpul. Graf 0-indexed.

## Daftar isi

- [Pohon vs graf](#pohon-vs-graf)
- [Definisi diameter](#definisi-diameter)
- [Dua DFS](#dua-dfs)
- [Dua BFS setara](#dua-bfs-setara)
- [Rekonstruksi jalur](#rekonstruksi-jalur)
- [Pusat dan radius](#pusat-dan-radius)
- [Diameter lewat tree DP](#diameter-lewat-tree-dp)
- [Sisi berbobot](#sisi-berbobot)
- [Hutan dan n kecil](#hutan-dan-n-kecil)
- [Tinggi vs diameter](#tinggi-vs-diameter)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Pohon vs graf

**Teori:** jika ada siklus, “jalur terpanjang” (simple path terpanjang) NP-berat. Teknik file ini butuh pohon, atau spanning tree yang kamu pilih sadar. Akar boleh dipilih. `par[v]` = ayah, `dep[v]` = jarak sisi ke akar. Subtree = v dan keturunan menurut akar itu.

Analogi: satu jalan desa tanpa putaran. Dari rumah mana pun ke rumah lain, rute unik. “Yang paling jauh” punya arti geometris: ujung-ujung cabang.

**Kapan:**

- Pakai: soal menjamin pohon, atau `m = n−1` dan terhubung.
- Jangan: graf umum, DAG, grid dengan siklus.
- Jangan: bobot negatif pada dua DFS — bukti ujung gagal.

**Proses:** n=6, sisi `0-1, 0-2, 1-3, 1-4, 2-5`, akar 0.

```
        0
       / \
      1   2
     / \   \
    3   4   5
```

`par[3]=1`, `dep[5]=2`, subtree 1 = {1,3,4}. Jalur 3–5 = 3-1-0-2-5, unik, 4 sisi.

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

**Jebakan:** input 1-based lupa −1. DFS tanpa menolak ayah = tak hingga. n=1: tidak ada sisi, diameter 0. `m ≠ n−1` bukan pohon.

**Kompleksitas:** O(n) bangun, memori O(n).

## Definisi diameter

**Teori:** diameter = panjang jalur sederhana terpanjang. Satuan: jumlah sisi (unweighted) atau jumlah bobot (weighted, biasanya `w ≥ 0`). Beberapa soal minta **banyak simpul** = sisi+1. Baca soal.

Eksentrisitas `ecc(v)` = jarak terjauh dari v. Diameter = max `ecc(v)`. Radius = min `ecc(v)`. Pusat = simpul yang mencapai radius.

Pada pohon, semua pusat terletak di tengah jalur diameter. Tidak perlu hitung `ecc` dari setiap simpul.

**Kapan:** “longest path”, “ibu kota”, “minimalkan max jarak”, “diameter setelah menambah sisi”.

**Proses:** pohon contoh. `ecc(0)=2`, `ecc(1)=3`, `ecc(3)=4`. Diameter 4, radius 2, pusat 0 (dan 2 jika dihitung sisi tengah — lihat bagian pusat).

```
jauh dari 3: 3-1-0-2-5 = 4 sisi
jauh dari 0: 0-1-3 atau 0-2-5 = 2 sisi
```

**Kode:** definisi lewat eksentrisitas naif (hanya n kecil).

```cpp
int eksentrisitas(int s, const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    int best = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        best = max(best, dist[v]);
        for (int u : g[v]) if (dist[u] == -1) {
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
    return best;
}

int diameterNaifEcc(const vector<vector<int>>& g) {
    int d = 0;
    for (int v = 0; v < (int)g.size(); v++)
        d = max(d, eksentrisitas(v, g));
    return d;
}
```

**Jebakan:** campur “panjang sisi” dan “banyak simpul”. Soal “output the path” butuh rekonstruksi, bukan hanya angka.

**Kompleksitas:** naif O(n²). Target O(n).

## Dua DFS

**Teori:** pada pohon berbobot tak negatif:

1. Dari simpul mana pun `s`, DFS/BFS cari yang terjauh `u`.
2. Dari `u`, cari yang terjauh `v`.
3. Jalur `u–v` adalah diameter. Panjang = jarak `u` ke `v`.

Kenapa `u` adalah ujung diameter. Misal diameter `x–y` dan `u` bukan ujung. Ambil jalur dari `u` ke jalur `x–y`, ketemu `w`. Karena `u` terjauh dari `s`, dan pohon tanpa siklus, memperpanjang ke `x` atau `y` menghasilkan kontradiksi dengan kejauhan `u` (atau dengan maksimalitas `x–y`). Sketsa lengkap: `u` harus salah satu ujung; langkah kedua mengambil ujung lain.

Dua DFS cukup: pohon tidak punya siklus, antrean BFS tidak wajib. DFS mengisi `dist` dari satu sumber sama benarnya.

**Kapan:**

- Pakai: jalur terpanjang, pilih pusat, tinggi setelah reroot ke pusat.
- Jangan: bobot negatif — “terjauh” pertama bisa bukan ujung.
- Jangan: graf umum.

**Proses:** mulai dari 0.

```
DFS1 dari 0:
  dist: 0:0, 1:1, 2:1, 3:2, 4:2, 5:2
  u = 3 (salah satu jarak 2; 4 atau 5 juga sah)

DFS2 dari 3:
  3:0, 1:1, 0:2, 4:2, 2:3, 5:4
  v = 5, diameter = 4
```

Jika mulai dari 2: DFS1 terjauh 3 atau 4, DFS2 tetap panjang 4.

**Kode:**

```cpp
void dfsJauh(int v, int p, int d, const vector<vector<int>>& g,
             int& bestV, int& bestD, vector<int>* dist = nullptr,
             vector<int>* par = nullptr) {
    if (dist) (*dist)[v] = d;
    if (par) (*par)[v] = p;
    if (d > bestD) {
        bestD = d;
        bestV = v;
    }
    for (int u : g[v]) if (u != p)
        dfsJauh(u, v, d + 1, g, bestV, bestD, dist, par);
}

int diameterDuaDfs(const vector<vector<int>>& g) {
    int n = (int)g.size();
    if (n == 0) return 0;
    int u = 0, du = -1;
    dfsJauh(0, -1, 0, g, u, du);
    int v = u, dv = -1;
    dfsJauh(u, -1, 0, g, v, dv);
    return dv;
}
```

**Jebakan:** mengambil “paling dalam dari akar 0” sebagai ujung — salah jika 0 di tengah. Harus dua kali. Tie jarak: pilih simpul mana pun. Komponen >1: bukan pohon, DFS dari 0 buta.

**Kompleksitas:** O(n).

## Dua BFS setara

**Teori:** BFS dari satu sumber mengisi jarak sisi. Pada unweighted, sama dengan DFS di atas. BFS enak jika nanti kamu sudah punya template graf, atau takut stack DFS pada rantai n=2·10^5 (naik `ulimit` / tulis iteratif).

**Kapan:** sama dengan dua DFS. Pilih satu dan konsisten.

**Proses:** BFS1 dari 0 → u=3. BFS2 dari 3 → v=5, dist=4. Identik.

**Kode:**

```cpp
pair<int, int> jauhDari(int start, const vector<vector<int>>& g,
                        vector<int>* par = nullptr) {
    int n = (int)g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    if (par) {
        par->assign(n, -1);
        (*par)[start] = -1;
    }
    int best = start;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] > dist[best]) best = v;
        for (int u : g[v]) if (dist[u] == -1) {
            dist[u] = dist[v] + 1;
            if (par) (*par)[u] = v;
            q.push(u);
        }
    }
    return {best, dist[best]};
}

int diameterDuaBfs(const vector<vector<int>>& g) {
    if (g.empty()) return 0;
    int u = jauhDari(0, g).first;
    return jauhDari(u, g).second;
}
```

**Jebakan:** `dist[u]==-1` wajib; tanpa itu ayah dikunjungi lagi. Mencampur BFS berbobot (itu Dijkstra).

**Kompleksitas:** O(n).

## Rekonstruksi jalur

**Teori:** penelusuran kedua simpan `par`. Jalan dari `v` ke `u`, lalu `reverse`. Panjang sisi = `path.size()-1`.

**Kapan:** cetak jalur, cari pusat, “warna semua simpul di diameter”.

**Proses:** dari 5: 5←2←0←1←3, reverse → `[3,1,0,2,5]`.

**Kode:**

```cpp
vector<int> jalurDiameter(const vector<vector<int>>& g) {
    if (g.empty()) return {};
    int u = 0, du = -1;
    dfsJauh(0, -1, 0, g, u, du);
    int n = (int)g.size();
    vector<int> par(n, -1), dist(n, 0);
    int v = u, dv = -1;
    dfsJauh(u, -1, 0, g, v, dv, &dist, &par);
    vector<int> path;
    for (int x = v; x != -1; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());
    return path;
}
```

**Jebakan:** lupa `reverse`. `par[u]` harus −1. Memakai `par` dari DFS pertama (akar 0) — salah, harus dari ujung `u`.

**Kompleksitas:** O(n).

## Pusat dan radius

**Teori:** pusat = simpul yang meminimalkan eksentrisitas. Pada pohon: tengah diameter.

- Banyak simpul di jalur ganjil (panjang sisi genap): satu pusat.
- Banyak simpul genap (panjang sisi ganjil): dua pusat bertetangga.

Tinggi setelah root di pusat ≈ `ceil(diameter/2)`. Radius = `ceil(diameter/2)` pada unweighted.

Soal “pilih ibu kota”: root di pusat. Soal “hapus daun berulang”: sisa 1 atau 2 simpul = pusat (peel layers).

**Kapan:** minimalkan max jarak, “pusat pohon”, reroot optimal.

**Proses:** jalur `[3,1,0,2,5]`, 5 simpul, 4 sisi.

```
indeks   0  1  2  3  4
simpul   3  1  0  2  5
tengah   path[(m-1)/2] = path[2] = 0
         path[m/2]     = path[2] = 0
satu pusat: 0
```

Jalur 4 simpul `[a,b,c,d]`: mid0=`path[1]`, mid1=`path[2]` → dua pusat.

n=2: path dua simpul, dua pusat. n=1: pusat 0.

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

int radiusDariDiameter(int diamSisi) {
    return (diamSisi + 1) / 2;
}
```

Setelah punya pusat, tinggi = eksentrisitas pusat.

```cpp
int tinggiJikaAkar(int root, const vector<vector<int>>& g) {
    int dummy = root, h = -1;
    dfsJauh(root, -1, 0, g, dummy, h);
    return h;
}
```

**Jebakan:** campur panjang sisi dan banyak simpul. Tes n=2. Mengira pusat selalu unik. `path[m/2]` saja tanpa `(m-1)/2` salah untuk dua pusat.

**Kompleksitas:** O(n).

## Diameter lewat tree DP

**Teori:** berakar di mana pun. Di setiap v, dua jalur **turun** terpanjang ke daun (anak berbeda). Belokan di v = jumlah keduanya (dalam sisi). Diameter = maksimum belokan di semua v.

`tinggi[v]` = 1 + max tinggi anak, daun 0. Belok = `h1 + h2` dua anak terbaik (0 jika kurang dari dua anak).

Kenapa lengkap: jalur terpanjang punya “puncak” (simpul paling dekat ke akar, atau belokan). Semua jalur adalah turun-turun lewat satu puncak.

**Kapan:** sudah DFS berakar, butuh tinggi **dan** diameter sekali jalan. Bobot sisi ≥ 0. Tree DP lain di [19-tree.md](../09-dp/19-tree.md).

**Proses:** akar 0.

```
tinggi[3]=0, [4]=0, [5]=0
tinggi[1]=1, [2]=1, [0]=2
di 1: satu turun 1 → belok 1 (jalur 3-1-4 = 2 jika dua daun)
  best1=1 (ke 3), best2=1 (ke 4) → belok 2
di 2: best1=1 → belok 1
di 0: best1=2, best2=2 → belok 4
diameter = 4
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

Versi yang juga mengisi `tinggi[]` dan simpul belokan:

```cpp
struct DiamDP {
    int diam = 0;
    int puncak = 0;
    vector<int> tinggi;

    int dfs(int v, int p, const vector<vector<int>>& g) {
        tinggi[v] = 0;
        int b1 = 0, b2 = 0;
        for (int u : g[v]) if (u != p) {
            int h = dfs(u, v, g) + 1;
            tinggi[v] = max(tinggi[v], h);
            if (h > b1) {
                b2 = b1;
                b1 = h;
            } else if (h > b2) b2 = h;
        }
        if (b1 + b2 > diam) {
            diam = b1 + b2;
            puncak = v;
        }
        return tinggi[v];
    }
};
```

**Jebakan:** hanya menyimpan satu “terpanjang”. Daun return 0, bukan −1. `ans` di luar lambda harus di-capture. Pohon tidak terhubung: DFS satu akar buta. Mengambil `tinggi[root]*2` sebagai diameter — salah pada rantai.

**Kompleksitas:** O(n).

## Sisi berbobot

**Teori:** ganti `+1` jadi `+w`. Dua DFS: “terjauh” = jumlah bobot maksimum. Tree DP: dua turun berbobot. Syarat **w ≥ 0**. Jika w boleh negatif, dua DFS salah; DP masih bisa jika jalur boleh pilih cabang (tapi “turun terpanjang” harus hati-hati: cabang negatif jangan dipaksa).

`dep` untuk LCA tetap **jumlah sisi**. Jarak berbobot pakai `distRoot` di [lca.md](lca.md).

**Kapan:** CSES *Tree Distance* berbobot, “longest weighted path”.

**Proses:** semua w=1 → sama dengan unweighted. Sisi 0-1 bobot 10, lain 1: diameter lewat 3-1-0-2-5 = 1+10+1+1=13, lebih besar dari 3-1-4=2.

**Kode:**

```cpp
void dfsJauhW(int v, int p, ll d,
              const vector<vector<pair<int, int>>>& g,
              int& bestV, ll& bestD) {
    if (d > bestD) {
        bestD = d;
        bestV = v;
    }
    for (auto [u, w] : g[v]) if (u != p)
        dfsJauhW(u, v, d + w, g, bestV, bestD);
}

ll diameterBobotDuaDfs(const vector<vector<pair<int, int>>>& g) {
    if (g.empty()) return 0;
    int u = 0;
    ll du = -1;
    dfsJauhW(0, -1, 0, g, u, du);
    int v = u;
    ll dv = -1;
    dfsJauhW(u, -1, 0, g, v, dv);
    return dv;
}

ll diameterBobotDP(const vector<vector<pair<int, int>>>& g) {
    ll ans = 0;
    function<ll(int, int)> dfs = [&](int v, int p) -> ll {
        ll best1 = 0, best2 = 0;
        for (auto [u, w] : g[v]) if (u != p) {
            ll h = dfs(u, v) + w;
            if (h > best1) {
                best2 = best1;
                best1 = h;
            } else if (h > best2) best2 = h;
        }
        ans = max(ans, best1 + best2);
        return best1;
    };
    if (!g.empty()) dfs(0, -1);
    return ans;
}
```

**Jebakan:** `int` overflow — pakai `ll`. Mencampur `dep` sisi dengan kilogram. w negatif + dua DFS.

**Kompleksitas:** O(n).

## Hutan dan n kecil

**Teori:** hutan = kumpulan pohon. Diameter graf = max diameter komponen. Dua DFS dari 0 hanya melihat satu komponen. Loop semua simpul belum dikunjungi.

n=0: 0. n=1: 0. Bintang: diameter 2. Rantai: diameter n−1.

**Kapan:** soal tidak menjamin terhubung. “Forest of trees”.

**Proses:** dua bintang terpisah ukuran 4 dan 3. Diameter 2 (bintang besar). Bukan 4.

**Kode:**

```cpp
int diameterHutan(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<char> seen(n, 0);
    int ans = 0;
    for (int s = 0; s < n; s++) if (!seen[s]) {
        int u = s, du = -1;
        dfsJauh(s, -1, 0, g, u, du);
        int v = u, dv = -1;
        vector<int> dist;
        dfsJauh(u, -1, 0, g, v, dv);
        ans = max(ans, dv);
        function<void(int, int)> mark = [&](int x, int p) {
            seen[x] = 1;
            for (int y : g[x]) if (y != p) mark(y, x);
        };
        mark(s, -1);
    }
    return ans;
}
```

**Jebakan:** menandai hanya `u` dan `v`, bukan seluruh komponen. Menggabungkan ujung antar komponen.

**Kompleksitas:** O(n).

## Tinggi vs diameter

**Teori:** tinggi berakar r = max jarak dari r. Diameter ≥ tinggi untuk setiap r, dan diameter ≥ tinggi(r) untuk r mana pun. `diam ≤ 2·tinggi(r)` selalu (jalur belok di r paling-paling dua turun). Ketat: bintang berakar di pusat, `diam=2`, `tinggi=1`. Rantai berakar di ujung: `diam = tinggi`.

Jangan mengganti diameter dengan `tinggi[0]` kecuali soal minta tinggi.

**Kapan:** debug: cek `diameterDP == diameterDuaDfs`. Cek `tinggi(pusat) == radius`.

**Proses:**

| pohon | akar | tinggi | diameter |
|---|---|---|---|
| rantai 0-1-2-3 | 0 | 3 | 3 |
| rantai | 1 atau 2 | 2 | 3 |
| bintang pusat 0 | 0 | 1 | 2 |
| contoh 6 simpul | 0 | 2 | 4 |

**Kode:**

```cpp
bool cekInvarian(const vector<vector<int>>& g) {
    int d1 = diameterDuaDfs(g);
    int d2 = diameterDP(g);
    if (d1 != d2) return false;
    auto [c, c2] = pusat(g);
    int rad = tinggiJikaAkar(c, g);
    if (rad != radiusDariDiameter(d1) && c2 == -1) {
        // unweighted: radius = ceil(d/2)
    }
    return rad == radiusDariDiameter(d1) || c2 != -1;
}
```

**Jebakan:** `2*tinggi[root]` sebagai jawaban “diameter”. Hanya upper bound.

**Kompleksitas:** O(n).

## Uji naif

**Teori:** diameter naif = max BFS dari setiap simpul. Banding dua DFS, dua BFS, DP. Tes: rantai, bintang, pohon contoh, n=1, n=2.

**Kapan:** n ≤ 40, atau setelah ubah `best2`.

**Proses:** rantai 0-1-2-3, diameter 3. Bintang 0 pusat + 1,2,3, diameter 2. Contoh 6 simpul, 4.

**Kode:**

```cpp
int diameterNaif(const vector<vector<int>>& g) {
    int best = 0;
    for (int s = 0; s < (int)g.size(); s++)
        best = max(best, jauhDari(s, g).second);
    return best;
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    int a = diameterDuaDfs(g), b = diameterDuaBfs(g);
    int c = diameterDP(g), d = diameterNaif(g);
    cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';   // 4 4 4 4
    auto path = jalurDiameter(g);
    cout << path.size() - 1 << '\n';                         // 4
    auto [p1, p2] = pusat(g);
    cout << p1 << ' ' << p2 << '\n';                         // 0 -1
    vector<vector<int>> rantai(4);
    for (int i = 0; i < 3; i++) {
        rantai[i].push_back(i + 1);
        rantai[i + 1].push_back(i);
    }
    cout << diameterDuaDfs(rantai) << '\n';                  // 3
}
```

**Jebakan:** naif di graf berbobot negatif tidak setara “terjauh BFS”. Tes hanya pohon terhubung.

**Kompleksitas:** naif O(n²).

## Ringkasan

1. Diameter pohon: dua DFS/BFS dari ujung, atau DP dua cabang. Bobot ≥ 0.
2. Jangan percaya “paling dalam dari akar 0”.
3. Pusat di tengah jalur. Radius = `ceil(diam/2)` unweighted.
4. Rekonstruksi: `par` dari penelusuran **kedua**.
5. Hutan: ulang per komponen.
6. Subtree sebagai array: [euler-tour.md](euler-tour.md). Jarak u–v: [lca.md](lca.md).

Latihan Day 198. Jangan salin `exercise_*.cpp` dari ComprogLearning.
