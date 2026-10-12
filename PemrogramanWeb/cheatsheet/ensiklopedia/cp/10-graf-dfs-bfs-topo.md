# 10 — Graf: DFS, BFS, flood fill, siklus, bipartit, topo, Euler, 0-1 BFS

[← 09 Teori bilangan lanjut](09-number-crt-catalan-matrix-fft.md) · [Indeks](README.md) · [Lanjut 11 →](11-graf-dijkstra-bellman-floyd-mst.md)

Folder **08 Graf** di `ComProgLearning/CP/DAFTAR-MATERI.md`: Day 113 (representasi + DFS/BFS), 117 (flood/komponen), 118 (siklus + bipartit), 119 (topo + DAG), 121 (Euler), 124 (BFS ruang state). **0-1 BFS** ikut di sini karena masih keluarga BFS; Dijkstra/Bellman/Floyd/MST ada di file 11.

Semua kode di file ini: `#include <bits/stdc++.h>`, `typedef long long ll`, **0-indexed**, fungsi terpisah, `main` hanya menguji.

## Daftar isi

- [Konvensi dan cara pilih senjata](#konvensi-dan-cara-pilih-senjata)
- [Representasi graf](#representasi-graf)
- [DFS](#dfs)
- [DFS waktu masuk-keluar](#dfs-waktu-masuk-keluar)
- [BFS](#bfs)
- [Flood fill dan komponen](#flood-fill-dan-komponen)
- [Deteksi siklus tak berarah](#deteksi-siklus-tak-berarah)
- [Deteksi siklus berarah](#deteksi-siklus-berarah)
- [Graf bipartit](#graf-bipartit)
- [Topological sort Kahn](#topological-sort-kahn)
- [Topological sort DFS](#topological-sort-dfs)
- [DP pada DAG](#dp-pada-dag)
- [Lintasan dan sirkuit Euler](#lintasan-dan-sirkuit-euler)
- [BFS pada ruang state](#bfs-pada-ruang-state)
- [0-1 BFS](#0-1-bfs)
- [Ringkasan file ini](#ringkasan-file-ini)

---

## Konvensi dan cara pilih senjata

**Teori:** Graf adalah pasangan `(V, E)`: simpul dan sisi. Soal CP hampir selalu memberi `n` simpul dan `m` sisi, lalu meminta jarak, urutan, komponen, atau ada-tidaknya suatu sifat. Dua penelusuran dasar merampas hampir semua soal tanpa bobot: DFS masuk sedalam mungkin lalu mundur, BFS menyebar lapis demi lapis. Kalau sisi berbobot 0 atau 1, deque menggantikan antrean biasa. Kalau bobot sebarang tak negatif, lompat ke Dijkstra di file 11.

**Kapan dipakai:** Pakai bab ini jika soal bicara tetangga, peta, prasyarat, labirin, mewarnai dua warna, atau “lewati setiap sisi tepat sekali”. Jangan memaksa DFS/BFS jika yang diminta adalah jarak berbobot sebarang, MST, aliran, atau komponen kuat berarah — itu file 11 dan 12.

**Proses:** Baca `n m`, bangun daftar ketetanggaan, tentukan berarah atau tidak, lalu pilih senjata dari tabel.

| Yang diminta | Alat |
|---|---|
| Jarak sisi-sama / tak berbobot | BFS |
| Komponen, flood, subtree | DFS atau BFS |
| Siklus tak berarah | DFS + parent |
| Siklus berarah | DFS 3 warna atau Kahn |
| Dua warna / ganjil-genap | BFS/DFS pewarnaan |
| Urutan prasyarat | Kahn atau DFS post-order |
| Banyak jalur / termurah di DAG | Topo lalu DP |
| Lewati setiap sisi sekali | Hierholzer (Euler) |
| Simpul = keadaan (kunci, langkah) | BFS ruang state |
| Bobot hanya 0 dan 1 | 0-1 BFS |

**Kode:** kerangka baca input yang dipakai seluruh file.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> bacaTakBerarah(int n, int m) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;                 // soal 1-indexed -> simpan 0-indexed
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

vector<vector<int>> bacaBerarah(int n, int m) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    auto g = bacaTakBerarah(n, m);
    cout << n << ' ' << g[0].size() << '\n';
    return 0;
}
```

**Jebakan:**

1. Lupa `--u; --v;` jika soal 1-indexed — akses `g[n]` langsung keluar batas.
2. Menambah sisi balik pada graf yang seharusnya berarah, atau sebaliknya.
3. `vector<vector<int>> g(n)` vs `g(n+1)` tercampur: file ini **selalu `g(n)`**.
4. Multi-sisi dan self-loop: DFS/BFS tetap jalan, tetapi deteksi siklus dan Euler harus sadar.

**Kompleksitas:** membangun daftar ketetanggaan `O(n + m)` waktu dan memori.

---

## Representasi graf

**Teori:** Tiga cara menyimpan sisi. **Daftar ketetanggaan** (`vector<vector<int>>`) menyimpan, untuk tiap `u`, daftar `v` yang bisa dicapai satu langkah. Analogikan buku alamat: tiap orang punya daftar temannya. **Matriks ketetanggaan** `adj[u][v]` adalah kotak `n × n`: ada sisi atau tidak (atau bobotnya). **Daftar sisi** adalah array `{u, v, w}` — paling nyaman diurutkan (Kruskal). Daftar ketetanggaan menang di graf jarang (`m` jauh lebih kecil dari `n²`), yaitu hampir semua soal kontes.

**Kapan dipakai:** Daftar ketetanggaan untuk DFS/BFS/Dijkstra. Matriks untuk Floyd-Warshall atau graf padat `n ≤ 400`. Daftar sisi untuk Kruskal dan saat sisi harus diurutkan. Jangan memakai matriks `n = 1e5`: memori `n²` meledak.

**Proses:** Graf tak berarah 4 simpul, sisi `0-1, 0-2, 1-2, 1-3`.

```
    0
   / \
  1---2
  |
  3
```

Daftar ketetanggaan (urutan sesuai urutan baca sisi):

```
g[0] = {1, 2}
g[1] = {0, 2, 3}
g[2] = {0, 1}
g[3] = {1}
```

Matriks (1 = ada sisi):

```
    0 1 2 3
0   0 1 1 0
1   1 0 1 1
2   1 1 0 0
3   0 1 0 0
```

Daftar sisi: `(0,1), (0,2), (1,2), (1,3)` plus pasangan balik jika perlu.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Sisi { int u, v; ll w; };

vector<vector<int>> dariSisiTakBerarah(int n, const vector<Sisi>& sisi) {
    vector<vector<int>> g(n);
    for (auto e : sisi) {
        g[e.u].push_back(e.v);
        g[e.v].push_back(e.u);
    }
    return g;
}

vector<vector<pair<int, ll>>> dariSisiBerbobot(int n, const vector<Sisi>& sisi, bool berarah) {
    vector<vector<pair<int, ll>>> g(n);
    for (auto e : sisi) {
        g[e.u].push_back({e.v, e.w});
        if (!berarah) g[e.v].push_back({e.u, e.w});
    }
    return g;
}

vector<vector<int>> matriksKeList(const vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<vector<int>> g(n);
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (adj[u][v]) g[u].push_back(v);
    return g;
}

int derajat(const vector<vector<int>>& g, int u) {
    return (int)g[u].size();
}

int main() {
    vector<Sisi> sisi = {{0, 1, 1}, {0, 2, 1}, {1, 2, 1}, {1, 3, 1}};
    auto g = dariSisiTakBerarah(4, sisi);
    cout << derajat(g, 1) << '\n';          // 3
    cout << g[0].size() << ' ' << g[3].size() << '\n';  // 2 1
    return 0;
}
```

**Jebakan:**

1. Graf berbobot disimpan sebagai `vector<int>` lalu bobot hilang — pakai `pair<int,ll>`.
2. Matriks tak berarah harus simetris; lupa mengisi `adj[v][u]`.
3. Iterasi `for (int v = 0; v < n; v++)` pada list: salah, list bukan matriks.
4. `g.assign(n, {})` setelah `g(n+1)` dari kode orang lain: sisa kebiasaan 1-indexed.

**Kompleksitas:** list `O(n + m)` memori, cek sisi `O(derajat(u))`. Matriks `O(n²)` memori, cek sisi `O(1)`.

---

## DFS

**Teori:** DFS (Depth-First Search) memilih satu tetangga, masuk sedalam mungkin, baru mundur ke persimpangan terakhir yang masih punya cabang belum dicoba. Analoginya labirin plus gulungan benang: benang adalah *call stack*. Algoritma benar untuk “mengunjungi setiap simpul yang tercapai” karena setiap simpul ditandai `vis` tepat sekali, dan setiap sisi ditinjau konstan kali. Urutan kunjungan **bukan** urutan jarak; itu kerja BFS.

**Kapan dipakai:** komponen, siklus, subtree, waktu masuk-keluar, backtracking, jembatan/titik artikulasi (file 12), topological sort versi DFS. Jangan dipakai untuk jarak terpendek pada graf tak berbobot — DFS bisa menemukan jalur panjang dulu.

**Proses:** mulai dari 0, tetangga diurutkan naik.

```
    0
   / \
  1   2
 / \   \
3   4   5
```

Langkah rekursif:

| aksi | stack panggilan | kunjung |
|---|---|---|
| masuk 0 | [0] | 0 |
| masuk 1 | [0, 1] | 0 1 |
| masuk 3 | [0, 1, 3] | 0 1 3 |
| 3 buntu, mundur | [0, 1] | |
| masuk 4 | [0, 1, 4] | 0 1 3 4 |
| mundur ke 0 | [0] | |
| masuk 2 | [0, 2] | 0 1 3 4 2 |
| masuk 5 | [0, 2, 5] | 0 1 3 4 2 5 |

Urutan preorder: `0, 1, 3, 4, 2, 5`. BFS dari 0 akan `0, 1, 2, 3, 4, 5`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfsRek(int u, const vector<vector<int>>& g, vector<int>& vis, vector<int>& urut) {
    vis[u] = 1;
    urut.push_back(u);
    for (int v : g[u])
        if (!vis[v]) dfsRek(v, g, vis, urut);
}

vector<int> dfsDari(int n, const vector<vector<int>>& g, int s) {
    vector<int> vis(n), urut;
    dfsRek(s, g, vis, urut);
    return urut;
}

vector<int> dfsIteratif(int n, const vector<vector<int>>& g, int s) {
    vector<int> vis(n), urut;
    stack<int> st;
    st.push(s);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        urut.push_back(u);
        for (int i = (int)g[u].size() - 1; i >= 0; i--) {
            int v = g[u][i];
            if (!vis[v]) st.push(v);
        }
    }
    return urut;
}

vector<int> dfsSemuaKomponen(int n, const vector<vector<int>>& g) {
    vector<int> vis(n), urut;
    for (int s = 0; s < n; s++)
        if (!vis[s]) dfsRek(s, g, vis, urut);
    return urut;
}

int main() {
    vector<vector<int>> g = {
        {1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}
    };
    auto a = dfsDari(6, g, 0);
    for (int x : a) cout << x << ' ';
    cout << '\n';                       // 0 1 3 4 2 5
    return 0;
}
```

**Jebakan:**

1. Rekursi pada `n = 1e5` rantai lurus: *stack overflow*. Pakai DFS iteratif atau `ulimit`/pragma stack (tidak portable).
2. Lupa `vis`: loop tak hingga pada graf berkisi.
3. DFS iteratif mendorong tetangga dari kiri ke kanan tanpa membalik: urutan beda dari rekursif (boleh, asal tidak diuji persis).
4. Hanya DFS dari simpul 0 pada graf tak terhubung: komponen lain tidak terjamah.

**Kompleksitas:** waktu `O(n + m)`, memori `O(n + m)` plus stack `O(n)` kasus terburuk.

---

## DFS waktu masuk-keluar

**Teori:** Setiap simpul mendapat dua cap waktu: `tin[u]` saat pertama kali masuk, `tout[u]` saat semua keturunan selesai. Pada pohon DFS, subtree `u` adalah interval `[tin[u], tout[u])`. Analoginya nomor antrian masuk-keluar gedung: siapa pun yang masuk setelah kamu dan keluar sebelum kamu berada di dalam “gedungmu”. Inilah alasan DFS menjadi fondasi LCA, Euler tour, query subtree, jembatan, dan SCC.

**Kapan dipakai:** “apakah `v` keturunan `u`?”, ukuran subtree, meratakan pohon jadi array (file 17), low-link (file 12). Jangan dipakai jika graf bukan hasil DFS tree dan kamu mengira interval selalu subtree — di graf umum, interval hanya subtree **pohon DFS**, bukan tetangga silang.

**Proses:** pohon yang sama seperti DFS di atas. Timer mulai 0, `tout` dicatat setelah anak selesai (satu timer untuk keduanya).

| peristiwa | timer | tin/tout |
|---|---|---|
| masuk 0 | 0 | tin[0]=0 |
| masuk 1 | 1 | tin[1]=1 |
| masuk 3 | 2 | tin[3]=2 |
| keluar 3 | 3 | tout[3]=3 |
| masuk 4 | 4 | tin[4]=4 |
| keluar 4 | 5 | tout[4]=5 |
| keluar 1 | 6 | tout[1]=6 |
| masuk 2 | 7 | tin[2]=7 |
| masuk 5 | 8 | tin[5]=8 |
| keluar 5 | 9 | tout[5]=9 |
| keluar 2 | 10 | tout[2]=10 |
| keluar 0 | 11 | tout[0]=11 |

`3` keturunan `1` karena `tin[1] ≤ tin[3] < tout[1]` → `1 ≤ 2 < 6`. `2` bukan keturunan `1`: `tin[2]=7` tidak `< 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DfsWaktu {
    vector<int> tin, tout, par, sz;
    int timer = 0;

    void jalan(int u, int p, const vector<vector<int>>& g) {
        par[u] = p;
        tin[u] = timer++;
        sz[u] = 1;
        for (int v : g[u]) if (v != p) {
            jalan(v, u, g);
            sz[u] += sz[v];
        }
        tout[u] = timer;
    }

    DfsWaktu(int n, const vector<vector<int>>& g, int akar)
        : tin(n), tout(n), par(n, -1), sz(n) {
        jalan(akar, -1, g);
    }

    bool keturunan(int u, int v) const {      // v di subtree u?
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

int main() {
    vector<vector<int>> g = {
        {1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}
    };
    DfsWaktu d(6, g, 0);
    cout << d.keturunan(1, 3) << ' ' << d.keturunan(1, 2) << '\n'; // 1 0
    cout << d.sz[0] << ' ' << d.sz[1] << '\n';                     // 6 3
    return 0;
}
```

**Jebakan:**

1. Membandingkan `tout` dengan `<` vs `≤` tergantung apakah `tout` diisi sebelum atau sesudah increment — samakan konvensi.
2. Memanggil `keturunan` antar komponen: `tin` komponen lain overlap atau tidak terisi.
3. Di graf berkisi, harus skip parent; kalau tidak, DFS turun lalu naik tanpa henti.
4. `sz[u]` pada graf umum menghitung ukuran **pohon DFS**, bukan komponen jika ada back-edge (back-edge tidak dilalui ke anak baru).

**Kompleksitas:** `O(n + m)` satu kali DFS, query keturunan `O(1)`.

---

## BFS

**Teori:** BFS (Breadth-First Search) memakai antrean FIFO. Simpul keluar antrean dalam urutan jarak (jumlah sisi) dari sumber. Analoginya gelombang air di lantai: genangan mencapai ubin jarak 1, baru jarak 2. Bukti: pertama kali sebuah simpul masuk antrean, semua jalur yang lebih pendek sudah diproses (karena antrean monoton terhadap jarak). Maka `dist[v]` yang ditulis saat `vis[v]=1` adalah jarak terpendek pada graf **tak berbobot** atau berbobot sama.

**Kapan dipakai:** jarak terpendek sisi-sama, labirin, minimum langkah, pewarnaan lapis, bipartit. Jangan dipakai jika sisi berbobot beda — jalur 5 sisi berbobot 1 lebih pendek dari 1 sisi berbobot 100, tetapi BFS menganggap yang 1 sisi lebih dulu “selesai”.

**Proses:** graf `0-1, 0-2, 1-3, 2-3, 3-4`, sumber 0.

```
0 — 1 — 3 — 4
 \     /
  — 2 —
```

| langkah | keluar | antrean setelah | dist |
|---|---|---|---|
| init | — | [0] | 0:0 |
| 1 | 0 | [1, 2] | 1:1, 2:1 |
| 2 | 1 | [2, 3] | 3:2 |
| 3 | 2 | [3] | 3 sudah vis |
| 4 | 3 | [4] | 4:3 |
| 5 | 4 | [] | selesai |

`dist = [0, 1, 1, 2, 3]`. Jalur 0-2-3-4 dan 0-1-3-4 sama-sama panjang 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;

vector<int> bfsJarak(int n, const vector<vector<int>>& g, int s) {
    vector<int> dist(n, INF);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}

vector<int> bfsJalur(int n, const vector<vector<int>>& g, int s, int t) {
    vector<int> dist(n, INF), par(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            par[v] = u;
            q.push(v);
        }
    }
    if (dist[t] == INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int bfsBanyakJalur(int n, const vector<vector<int>>& g, int s, int t, int mod) {
    vector<int> dist(n, INF);
    vector<ll> cara(n, 0);
    queue<int> q;
    dist[s] = 0;
    cara[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                cara[v] = cara[u];
                q.push(v);
            } else if (dist[v] == dist[u] + 1) {
                cara[v] = (cara[v] + cara[u]) % mod;
            }
        }
    }
    return dist[t] == INF ? 0 : (int)cara[t];
}

int main() {
    vector<vector<int>> g = {{1, 2}, {0, 3}, {0, 3}, {1, 2, 4}, {3}};
    auto d = bfsJarak(5, g, 0);
    for (int x : d) cout << x << ' ';
    cout << '\n';                               // 0 1 1 2 3
    auto p = bfsJalur(5, g, 0, 4);
    for (int x : p) cout << x << ' ';
    cout << '\n';                               // 0 1 3 4  (atau 0 2 3 4)
    cout << bfsBanyakJalur(5, g, 0, 4, 1000000007) << '\n'; // 2
    return 0;
}
```

**Jebakan:**

1. Menandai `vis` terlalu lambat (saat *pop*) tanpa cek `dist==INF` saat *push*: simpul masuk antrean berkali-kali, masih benar untuk jarak tetapi lambat.
2. Memakai BFS pada sisi berbobot beda.
3. Rekonstruksi jalur: lupa `reverse`, atau `par[s]` tidak `-1` sehingga loop.
4. Multi-source BFS: masukkan **semua** sumber di awal dengan `dist=0`, bukan BFS terpisah lalu ambil min (yang itu `O(k(n+m))`).

**Kompleksitas:** `O(n + m)` waktu dan memori. Multi-source sama.

---

## Flood fill dan komponen

**Teori:** Flood fill adalah DFS/BFS yang mewarnai semua sel/simpul sewarna yang terhubung. Analoginya menuang cat pada peta: cat mengalir ke sel tetangga bernilai sama. Pada graf abstrak, ini menghitung **komponen terhubung**: partisi simpul yang saling tercapai. Setiap komponen dikunjungi dari satu wakil; jumlah wakil = jumlah komponen.

**Kapan dipakai:** “berapa pulau”, “ukuran daerah ‘.’”, “bisa pergi dari A ke B tanpa tembok”, pewarnaan grid. Jangan memakai rekursi flood pada grid `1000 × 1000` tanpa yakin stack aman — BFS/iteratif lebih tenang. Jangan flood jika sel “hidup” satu-satu seiring waktu: itu DSU (file 12).

**Proses:** grid 4×5, `#` tembok, `.` lantai. Hitung pulau `.` dengan 4 arah.

```
. # . . #
. # # . .
# . . # .
. . # . .
```

Mulai `(0,0)` mewarnai 2 sel kolom-0 baris 0-1. `(0,2)` mewarnai daerah kanan-atas (4 sel). `(2,1)` mewarnai daerah tengah-bawah. `(3,0)` sudah kena. `(2,4)` dan `(3,3)` membentuk pulau kanan-bawah. Total **4** komponen lantai jika 4-arah (hitung teliti di kode uji). Simulasi komponen graf: sisi `0-1, 1-2, 3-4` → komponen `{0,1,2}` dan `{3,4}` = 2.

Langkah flood dari `(0,0)` 4-arah:

| antrian | sel | cat |
|---|---|---|
| [(0,0)] | (0,0) | id 1 |
| [(1,0)] | (1,0) | id 1 |
| [] | selesai daerah 1, ukuran 2 | |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int komponenTerhubung(int n, const vector<vector<int>>& g, vector<int>& id) {
    id.assign(n, -1);
    int k = 0;
    for (int s = 0; s < n; s++) if (id[s] == -1) {
        queue<int> q;
        q.push(s);
        id[s] = k;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (id[v] == -1) {
                id[v] = k;
                q.push(v);
            }
        }
        k++;
    }
    return k;
}

int floodUkuran(vector<string>& a, int sr, int sc, char dari, char ke) {
    int R = (int)a.size(), C = (int)a[0].size();
    if (a[sr][sc] != dari) return 0;
    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};
    queue<pair<int, int>> q;
    q.push({sr, sc});
    a[sr][sc] = ke;
    int sz = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        sz++;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (a[nr][nc] != dari) continue;
            a[nr][nc] = ke;
            q.push({nr, nc});
        }
    }
    return sz;
}

int hitungPulau(vector<string> a) {
    int R = (int)a.size(), ans = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < (int)a[r].size(); c++)
            if (a[r][c] == '.') {
                floodUkuran(a, r, c, '.', '#');
                ans++;
            }
    return ans;
}

int main() {
    vector<vector<int>> g = {{1}, {0, 2}, {1}, {4}, {3}};
    vector<int> id;
    cout << komponenTerhubung(5, g, id) << '\n';          // 2
    vector<string> grid = {".#..#", ".##..", "#..#.", "..#.."};
    cout << hitungPulau(grid) << '\n';
    return 0;
}
```

**Jebakan:**

1. 4-arah vs 8-arah: soal “pulau” sering 8-arah (diagonal nyambung). Baca pernyataan.
2. Menandai `vis` setelah pop di grid besar: antrean meledak karena sel yang sama didorong dari banyak tetangga.
3. Recolor `'.'` menjadi `'#'` menimpa peta asli — salin grid jika masih dipakai.
4. Indeks `(r, c)` vs `(x, y)` tertukar; `n` baris `m` kolom dibaca terbalik.

**Kompleksitas:** `O(n + m)` graf, `O(R C)` grid. Setiap sel/simpul sekali.

---

## Deteksi siklus tak berarah

**Teori:** Pada graf tak berarah, sisi ke simpul yang sudah dikunjungi **bukan parent** adalah back-edge, dan back-edge menutup siklus. Analoginya: kamu jalan di hutan, bertemu jejak lama yang bukan jalan pulang — berarti ada putaran. Kenapa parent dikecualikan: sisi `{u, p}` dikunjungi dua kali (dari kedua ujung); itu bukan siklus.

**Kapan dipakai:** “apakah jaringan punya loop”, validasi pohon (`m == n-1` **dan** tak ada siklus **dan** terhubung), soal yang rusak jika ada putaran. Jangan memakai cek parent pada graf berarah — parent tidak terdefinisi sama. Jangan menyimpulkan “ada siklus” hanya dari `m ≥ n` tanpa cek komponen.

**Proses:** sisi `0-1, 1-2, 2-0, 2-3`. DFS dari 0, parent 0 adalah `-1`.

| u | parent | tetangga | keputusan |
|---|---|---|---|
| 0 | -1 | 1 | turun ke 1 |
| 1 | 0 | 0 skip, 2 turun | |
| 2 | 1 | 1 skip, 0 sudah vis dan bukan parent | **siklus 2-0** |
| 2 | 1 | 3 belum vis | turun (tidak perlu, sudah ketemu) |

Siklus `0-1-2-0`. Jika sisi `2-0` dihapus, DFS selesai tanpa back-edge; graf adalah pohon plus mungkin tidak terhubung.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool dfsSiklus(int u, int p, const vector<vector<int>>& g, vector<int>& vis) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        if (vis[v]) return true;
        if (dfsSiklus(v, u, g, vis)) return true;
    }
    return false;
}

bool adaSiklusTakBerarah(int n, const vector<vector<int>>& g) {
    vector<int> vis(n);
    for (int s = 0; s < n; s++)
        if (!vis[s] && dfsSiklus(s, -1, g, vis)) return true;
    return false;
}

bool adalahPohon(int n, const vector<vector<int>>& g) {
    int m = 0;
    for (int u = 0; u < n; u++) m += (int)g[u].size();
    m /= 2;
    if (m != n - 1) return false;
    return !adaSiklusTakBerarah(n, g);
}

vector<int> satuSiklus(int n, const vector<vector<int>>& g) {
    vector<int> vis(n), par(n, -1), siklus;
    int start = -1, ketemu = -1;
    function<bool(int, int)> dfs = [&](int u, int p) {
        vis[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            if (!vis[v]) {
                par[v] = u;
                if (dfs(v, u)) return true;
            } else {
                start = v;
                ketemu = u;
                return true;
            }
        }
        return false;
    };
    for (int s = 0; s < n; s++)
        if (!vis[s] && dfs(s, -1)) break;
    if (ketemu == -1) return {};
    siklus.push_back(start);
    for (int x = ketemu; x != start; x = par[x]) siklus.push_back(x);
    siklus.push_back(start);
    reverse(siklus.begin(), siklus.end());
    return siklus;
}

int main() {
    vector<vector<int>> g = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    cout << adaSiklusTakBerarah(4, g) << '\n';     // 1
    auto c = satuSiklus(4, g);
    for (int x : c) cout << x << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:**

1. Multi-sisi `u-v` dua kali: tetangga `v` muncul dua kali, yang kedua terlihat seperti back-edge. Tandai sisi atau pakai DSU.
2. Self-loop `u-u` adalah siklus; cek `v == u`.
3. `m == n-1` saja tidak cukup: bisa ada siklus di satu komponen dan komponen lain terputus.
4. Rekonstruksi: arah `par` dari `ketemu` ke `start`, lalu tutup dengan `start`.

**Kompleksitas:** `O(n + m)`.

---

## Deteksi siklus berarah

**Teori:** Pada graf berarah, back-edge menuju simpul yang **sedang** di stack rekursi (warna abu-abu). Analoginya: mata kuliah A butuh B, B butuh C, C butuh A — kamu sedang mengurus A ketika syaratnya kembali ke A. Tiga warna: 0 putih (belum), 1 abu (sedang), 2 hitam (selesai). Sisi ke hitam adalah forward/cross, **bukan** siklus. Kahn memberi tes yang sama: jika urutan topologis tidak memuat semua simpul, ada siklus.

**Kapan dipakai:** dependensi, “apakah ada deadlock”, syarat topological sort. Jangan memakai tes parent tak berarah. Jangan menyimpulkan siklus dari “sisi ke simpul sudah dikunjungi” tanpa membedakan abu vs hitam.

**Proses:** sisi `0→1, 1→2, 2→0, 0→3`.

| u | warna saat masuk | tetangga | warna v | arti |
|---|---|---|---|---|
| 0 | 0→1 | 1 | 0 | turun |
| 1 | 1 | 2 | 0 | turun |
| 2 | 1 | 0 | 1 abu | **back-edge, siklus** |
|  |  |  |  | 3 tidak perlu |

Kalau `2→0` diganti `2→3`: 2 melihat 3 putih, 3 selesai hitam, 0 selesai. Tidak ada sisi ke abu → DAG.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool dfsArah(int u, const vector<vector<int>>& g, vector<int>& wrn) {
    wrn[u] = 1;
    for (int v : g[u]) {
        if (wrn[v] == 1) return true;
        if (wrn[v] == 0 && dfsArah(v, g, wrn)) return true;
    }
    wrn[u] = 2;
    return false;
}

bool adaSiklusBerarah(int n, const vector<vector<int>>& g) {
    vector<int> wrn(n, 0);
    for (int s = 0; s < n; s++)
        if (wrn[s] == 0 && dfsArah(s, g, wrn)) return true;
    return false;
}

vector<int> simpulDiSiklusAtauTerpengaruh(int n, const vector<vector<int>>& g) {
    // Kahn: yang tidak masuk urutan = di siklus atau tergantung siklus
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    vector<int> ok(n, 0);
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ok[u] = 1;
        cnt++;
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    vector<int> sisa;
    if (cnt == n) return sisa;
    for (int u = 0; u < n; u++) if (!ok[u]) sisa.push_back(u);
    return sisa;
}

int main() {
    vector<vector<int>> g = {{1, 3}, {2}, {0}, {}};
    cout << adaSiklusBerarah(4, g) << '\n';        // 1
    auto s = simpulDiSiklusAtauTerpengaruh(4, g);
    for (int x : s) cout << x << ' ';
    cout << '\n';                                  // 0 1 2   (3 bebas)
    return 0;
}
```

**Jebakan:**

1. Dua warna saja: sisi ke simpul hitam dikira siklus (salah).
2. Graf tak berarah diperlakukan 3-warna tanpa membuang sisi balik: setiap sisi jadi “siklus” palsu.
3. Kahn: `ord.size() != n` adalah tes lengkap; tidak perlu DFS tambahan jika hanya butuh ya/tidak.
4. Self-loop `u→u` langsung warna 1 ke 1.

**Kompleksitas:** `O(n + m)`.

---

## Graf bipartit

**Teori:** Graf bipartit bisa diwarnai dua warna sehingga setiap sisi menghubungkan warna berbeda. Setara dengan: **tidak ada siklus ganjil**. Analoginya pewarnaan peta catur: petak hitam hanya bertetangga putih. Pewarnaan BFS/DFS: berikan warna 0 ke sumber, tetangga 1, tetangga-nya lagi 0. Konflik = sisi menghubungkan dua simpul sewarna = siklus ganjil.

**Kapan dipakai:** matching (file 12), “bagi dua kelompok yang tidak berteman di dalam kelompok”, papan catur, soal paritas. Jangan mengira graf tanpa siklus (pohon) bisa gagal: pohon selalu bipartit. Jangan mengira graf berarah memakai definisi yang sama tanpa mengubah “sisi” jadi tak berarah.

**Proses:** sisi `0-1, 1-2, 2-3, 3-0` (kotak, siklus 4 = genap) vs tambah `0-2` (diagonal, siklus 3).

Kotak:

| u | warna | tetangga | warna v |
|---|---|---|---|
| 0 | 0 | 1, 3 | 1 dan 1 |
| 1 | 1 | 2 | 0 |
| 3 | 1 | 2 | 2 sudah 0, cocok |
| 2 | 0 | — | bipartit, partisi {0,2} / {1,3} |

Tambah `0-2`: 0 berwarna 0, 2 sudah 0 → konflik. Siklus `0-1-2-0` panjang 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool pewarna(int s, const vector<vector<int>>& g, vector<int>& col) {
    queue<int> q;
    col[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (col[v] == -1) {
                col[v] = col[u] ^ 1;
                q.push(v);
            } else if (col[v] == col[u]) return false;
        }
    }
    return true;
}

bool bipartit(int n, const vector<vector<int>>& g, vector<int>& col) {
    col.assign(n, -1);
    for (int s = 0; s < n; s++)
        if (col[s] == -1 && !pewarna(s, g, col)) return false;
    return true;
}

pair<vector<int>, vector<int>> duaSisi(int n, const vector<vector<int>>& g) {
    vector<int> col;
    if (!bipartit(n, g, col)) return {{}, {}};
    vector<int> kiri, kanan;
    for (int i = 0; i < n; i++) (col[i] == 0 ? kiri : kanan).push_back(i);
    return {kiri, kanan};
}

int main() {
    vector<vector<int>> kotak = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    vector<int> col;
    cout << bipartit(4, kotak, col) << '\n';       // 1
    vector<vector<int>> segitiga = {{1, 2}, {0, 2}, {0, 1}};
    cout << bipartit(3, segitiga, col) << '\n';    // 0
    return 0;
}
```

**Jebakan:**

1. Hanya mewarnai komponen simpul 0: komponen lain bisa punya siklus ganjil.
2. Simpul terisolasi tetap bipartit; masuk sisi mana pun.
3. Soal matching butuh **sudah** diketahui partisi kiri/kanan; pewarnaan memberi partisi, tetapi sisi di dalam input bisa meragukan mana “kiri”.
4. Graf tidak terhubung: tiap komponen diwarnai sendiri; jangan memaksa warna global dari komponen lain.

**Kompleksitas:** `O(n + m)`.

---

## Topological sort Kahn

**Teori:** Urutan topologis adalah barisan semua simpul sehingga setiap sisi `u → v` menempatkan `u` sebelum `v`. Analoginya rencana studi: mata kuliah hanya boleh diambil setelah prasyaratnya. Teorema: urutan ada **jika dan hanya jika** graf adalah DAG. Kahn berulang kali mengambil simpul ber-indegree 0, “menghapusnya”, dan mengurangi indegree tetangga. Mesin kebenarannya: setiap DAG tak kosong punya simpul indegree 0 (kalau tidak, jalan mundur tak hingga → siklus).

**Kapan dipakai:** prasyarat, kompilasi, DP pada DAG, deteksi siklus berarah (`ord.size() != n`). Jangan dipakai pada graf tak berarah. Jangan mengharapkan urutan unik — banyak DAG punya banyak urutan sah.

**Proses:** sisi `0→2, 1→2, 1→3, 2→4, 3→4` (simpul 0..4).

Indegree awal: `[0, 0, 2, 1, 2]`.

| antrean | ambil | efek indegree | hasil |
|---|---|---|---|
| [0, 1] | 0 | 2: 2→1 | [0] |
| [1] | 1 | 2: 1→0 push 2; 3: 1→0 push 3 | [0, 1] |
| [2, 3] | 2 | 4: 2→1 | [0, 1, 2] |
| [3] | 3 | 4: 1→0 push 4 | [0, 1, 2, 3] |
| [4] | 4 | — | [0, 1, 2, 3, 4] |

`size == 5` → DAG. Kalau tambah `4→1`, indegree 1 menjadi 1 di awal; 1 tidak pernah 0 bersama 4 → `ord` tidak lengkap.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> kahn(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n), ord;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

vector<int> kahnLeksikografis(int n, const vector<vector<int>>& g) {
    vector<int> indeg(n), ord;
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n; u++) if (!indeg[u]) pq.push(u);
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) pq.push(v);
    }
    return ord;
}

struct InfoTopo {
    vector<int> ord, lvl;
    bool dag = true, unik = true;
};

InfoTopo kahnLengkap(int n, const vector<vector<int>>& g) {
    InfoTopo r;
    r.lvl.assign(n, 0);
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        if ((int)q.size() > 1) r.unik = false;
        int u = q.front();
        q.pop();
        r.ord.push_back(u);
        for (int v : g[u]) {
            r.lvl[v] = max(r.lvl[v], r.lvl[u] + 1);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    r.dag = ((int)r.ord.size() == n);
    if (!r.dag) r.unik = false;
    return r;
}

int main() {
    vector<vector<int>> g = {{2}, {2, 3}, {4}, {4}, {}};
    auto ord = kahn(5, g);
    if ((int)ord.size() != 5) cout << "SIKLUS\n";
    else {
        for (int x : ord) cout << x << ' ';
        cout << '\n';                              // 0 1 2 3 4 atau 1 0 ...
    }
    auto info = kahnLengkap(5, g);
    cout << info.unik << ' ' << info.lvl[4] << '\n'; // 0  2
    return 0;
}
```

**Jebakan:**

1. Membandingkan output dengan satu urutan tetap padahal soal menerima semua urutan sah.
2. Lupa cek `ord.size() == n` lalu memakai `ord` untuk DP — diam-diam salah.
3. Input `u v` artinya “u sebelum v” atau “u tergantung v”? Baca; arah sisi terbalik merusak semua.
4. Leksikografis butuh heap, bukan `queue`.

**Kompleksitas:** Kahn `O(n + m)`, leksikografis `O((n + m) log n)`.

---

## Topological sort DFS

**Teori:** DFS selesai (post-order) pada DAG menuliskan simpul setelah semua yang bergantung padanya (tetangga ke depan) selesai. Membalik daftar post-order memberi urutan topologis. Analoginya: kamu menandatangani form setelah semua form yang kamu butuhkan sudah ditandatangani; tumpukan form yang selesai, dibalik, adalah urutan kerja. Back-edge ke warna abu menolak DAG.

**Kapan dipakai:** saat DFS sudah ditulis, atau butuh klasifikasi sisi. Kahn lebih nyaman untuk “unik?” dan “level prasyarat”. Keduanya sah.

**Proses:** sisi `0→1, 0→2, 1→3, 2→3`. DFS dari 0, tetangga kecil dulu.

| peristiwa | post |
|---|---|
| 0 masuk, ke 1 | |
| 1 ke 3 | |
| 3 selesai | [3] |
| 1 selesai | [3, 1] |
| 0 ke 2 | |
| 2 ke 3 (hitam, skip) | |
| 2 selesai | [3, 1, 2] |
| 0 selesai | [3, 1, 2, 0] |

Balik: `0, 2, 1, 3` atau jika 2 dikunjungi dulu dari pemanggilan terpisah, urutan berubah tetapi tetap sah (`0` sebelum `1` dan `2`, keduanya sebelum `3`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct TopoDFS {
    vector<int> wrn, ord;
    bool siklus = false;

    void dfs(int u, const vector<vector<int>>& g) {
        wrn[u] = 1;
        for (int v : g[u]) {
            if (wrn[v] == 1) { siklus = true; return; }
            if (wrn[v] == 0) {
                dfs(v, g);
                if (siklus) return;
            }
        }
        wrn[u] = 2;
        ord.push_back(u);
    }

    vector<int> run(int n, const vector<vector<int>>& g) {
        wrn.assign(n, 0);
        ord.clear();
        siklus = false;
        for (int s = 0; s < n && !siklus; s++)
            if (wrn[s] == 0) dfs(s, g);
        if (siklus) return {};
        reverse(ord.begin(), ord.end());
        return ord;
    }
};

int main() {
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    TopoDFS t;
    auto ord = t.run(4, g);
    for (int x : ord) cout << x << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:**

1. Lupa `reverse` — itu post-order, bukan topo.
2. Menulis simpul di **preorder** (saat masuk) — salah total.
3. Tidak menjalankan DFS dari semua sumber: simpul indegree 0 yang bukan akar pertama hilang.
4. Stack overflow pada DAG berbentuk rantai `1e5`.

**Kompleksitas:** `O(n + m)`.

---

## DP pada DAG

**Teori:** Setelah urutan topologis ada, setiap sisi pergi ke simpul yang lebih belakang. DP bisa diisi dari kiri ke kanan tanpa siklus update. Analoginya: menghitung nilai ujian hanya setelah semua prasyarat punya nilai. Pola push: `dp[v] ⊕= f(dp[u], w(u,v))`. Tiga pertanyaan klasik: banyak jalur, jalur terpanjang, jalur termurah. Bobot negatif **boleh** untuk min/max di DAG — beda dari Dijkstra.

**Kapan dipakai:** “berapa cara dari S ke T”, “rantai tugas terpanjang”, “biaya minimum proyek berprasyarat”. Jangan DP jika ada siklus (kecuali soal khusus *mean cycle*). Jangan Dijkstra jika ada bobot negatif tetapi graf DAG — topo-DP lebih tepat.

**Proses:** sisi berbobot `0→1 (2), 0→2 (1), 1→3 (3), 2→3 (10)`, sumber 0. Banyak jalur ke 3 = 2. Terpanjang `0-2-3` = 11. Termurah `0-1-3` = 5.

| u dalam topo [0,1,2,3] | push |
|---|---|
| 0, dp=0 (jarak), cara=1 | dp[1]=2, dp[2]=1, cara[1]=cara[2]=1 |
| 1 | dp[3]=5, cara[3]=1 |
| 2 | dp_max[3]=11, cara[3]=2, dp_min[3] tetap 5 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

vector<int> topoDariBerbobot(int n, const vector<vector<pair<int, ll>>>& g) {
    vector<int> indeg(n);
    for (int u = 0; u < n; u++)
        for (auto [v, w] : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 0; u < n; u++) if (!indeg[u]) q.push(u);
    vector<int> ord;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (auto [v, w] : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}

vector<ll> banyakJalur(int n, const vector<vector<pair<int, ll>>>& g,
                       const vector<int>& ord, int s) {
    vector<ll> dp(n, 0);
    dp[s] = 1;
    for (int u : ord) {
        if (!dp[u]) continue;
        for (auto [v, w] : g[u]) dp[v] = (dp[v] + dp[u]) % MOD;
    }
    return dp;
}

vector<ll> jalurTerpanjang(int n, const vector<vector<pair<int, ll>>>& g,
                           const vector<int>& ord, int s) {
    vector<ll> dp(n, -INF);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == -INF) continue;
        for (auto [v, w] : g[u]) dp[v] = max(dp[v], dp[u] + w);
    }
    return dp;
}

vector<ll> jalurTermurahDAG(int n, const vector<vector<pair<int, ll>>>& g,
                            const vector<int>& ord, int s) {
    vector<ll> dp(n, INF);
    dp[s] = 0;
    for (int u : ord) {
        if (dp[u] == INF) continue;
        for (auto [v, w] : g[u]) dp[v] = min(dp[v], dp[u] + w);
    }
    return dp;
}

int main() {
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 2});
    g[0].push_back({2, 1});
    g[1].push_back({3, 3});
    g[2].push_back({3, 10});
    auto ord = topoDariBerbobot(n, g);
    cout << banyakJalur(n, g, ord, 0)[3] << '\n';       // 2
    cout << jalurTerpanjang(n, g, ord, 0)[3] << '\n';   // 11
    cout << jalurTermurahDAG(n, g, ord, 0)[3] << '\n';  // 5
    return 0;
}
```

**Jebakan:**

1. Tidak mengabaikan `dp[u] == ±INF`: `-INF + w` overflow, atau simpul tak terjangkau “menulari” tetangga.
2. `ord.size() != n` tetap dipakai.
3. Inisialisasi `dp[s] = 0` tetapi `s` bukan sumber logis soal (sumber jamak: taruh 0 di semua sumber).
4. Modulo lupa pada banyak jalur.

**Kompleksitas:** `O(n + m)` setelah graf dibangun.

---

## Lintasan dan sirkuit Euler

**Teori:** Lintasan Euler melewati **setiap sisi tepat sekali**. Sirkuit Euler kembali ke awal. Hierholzer: dari simpul sekarang, jalan greedy menyusuri sisi belum dipakai sampai macet; macet berarti sirkuit lokal selesai, sisipkan sirkuit itu ke tur global, lalu lanjut sisa sisi di simpul sebelumnya. Analoginya: keliling kota memakai setiap jalan sekali — kalau macet di rumah, kamu sudah menutup putaran; putaran kecil disambung di persimpangan yang masih punya jalan sisa.

Syarat tak berarah: graf (abaikan isolasi) terhubung, sirkuit jika semua derajat genap, lintasan jika tepat 0 atau 2 derajat ganjil (mulai di yang ganjil).

Syarat berarah: lemah-terhubung (abaikan isolasi), sirkuit jika `in = out` di semua simpul, lintasan jika satu start `out = in+1`, satu end `in = out+1`, sisanya sama.

**Kapan dipakai:** “gambar tanpa angkat pena”, “urutkan kartu/domino”, de Bruijn, “rekonstruksi pasangan beruntun”. Jangan dipaksa jika yang diminta Hamilton (setiap **simpul** sekali) — itu NP-berat, beda soal.

**Proses:** tak berarah, sisi `0-1, 1-2, 2-3, 3-0, 0-2`. Derajat: 0:3, 1:2, 2:3, 3:2 → dua ganjil (0 dan 2) → lintasan, mulai di 0.

Hierholzer dari 0, sisi disimpan dua arah dengan id:

| stack | sisi terpakai | catatan |
|---|---|---|
| [0] | — | mulai |
| [0, 1] | 0-1 | |
| [0, 1, 2] | 1-2 | |
| [0, 1, 2, 3] | 2-3 | |
| [0, 1, 2, 3, 0] | 3-0 | |
| [0, 1, 2, 3, 0, 2] | 0-2 | 0 macet setelah ini |
| pop 2 (macet), 0, 3, 2, 1, 0 | | tur balik: 2 0 3 2 1 0 → dibalik 0 1 2 3 0 2 |

Semua 5 sisi terpakai. Tur `0-1-2-3-0-2` sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct EulerTakBerarah {
    int n;
    vector<vector<pair<int, int>>> g;     // {tetangga, id sisi}
    vector<int> used;

    EulerTakBerarah(int n, const vector<pair<int, int>>& sisi) : n(n), g(n) {
        used.assign(sisi.size(), 0);
        for (int i = 0; i < (int)sisi.size(); i++) {
            int u = sisi[i].first, v = sisi[i].second;
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }
    }

    vector<int> hierholzer(int start) {
        vector<int> stack = {start}, path;
        vector<int> it(n, 0);
        while (!stack.empty()) {
            int u = stack.back();
            while (it[u] < (int)g[u].size() && used[g[u][it[u]].second]) it[u]++;
            if (it[u] == (int)g[u].size()) {
                path.push_back(u);
                stack.pop_back();
            } else {
                auto [v, id] = g[u][it[u]++];
                used[id] = 1;
                stack.push_back(v);
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

bool eulerBisaTakBerarah(int n, const vector<pair<int, int>>& sisi, int& start) {
    vector<int> deg(n);
    vector<vector<int>> g(n);
    for (auto [u, v] : sisi) {
        deg[u]++; deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ganjil = 0;
    start = 0;
    for (int i = 0; i < n; i++) if (deg[i]) { start = i; break; }
    for (int i = 0; i < n; i++) if (deg[i] & 1) { ganjil++; start = i; }
    if (ganjil != 0 && ganjil != 2) return false;
    vector<int> vis(n);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs(v);
    };
    dfs(start);
    for (int i = 0; i < n; i++) if (deg[i] && !vis[i]) return false;
    return true;
}

vector<int> eulerBerarah(int n, vector<vector<int>> g) {
    vector<int> stack = {0}, path, it(n, 0);
    // pemanggil harus set start yang benar
    while (!stack.empty()) {
        int u = stack.back();
        if (it[u] < (int)g[u].size()) {
            int v = g[u][it[u]++];
            stack.push_back(v);
        } else {
            path.push_back(u);
            stack.pop_back();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> eulerBerarahDari(int start, vector<vector<int>> g) {
    vector<int> stack = {start}, path, it((int)g.size(), 0);
    while (!stack.empty()) {
        int u = stack.back();
        if (it[u] < (int)g[u].size()) stack.push_back(g[u][it[u]++]);
        else { path.push_back(u); stack.pop_back(); }
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    int start;
    cout << eulerBisaTakBerarah(4, sisi, start) << ' ' << start << '\n'; // 1 0 atau 2
    EulerTakBerarah e(4, sisi);
    auto p = e.hierholzer(start);
    for (int x : p) cout << x << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:**

1. Hamilton ≠ Euler. Soal “kunjungi kota sekali” bukan Hierholzer.
2. Tak berarah: sisi harus punya **id** dan `used[id]`, bukan hanya hapus satu arah.
3. Tidak cek keterhubungan: derajat genap di dua komponen terpisah tidak punya sirkuit global.
4. Output Hierholzer adalah barisan **simpul** sepanjang `m+1`. Soal kadang minta id sisi — simpan pasangan `(v, id)`.
5. Start salah pada lintasan (mulai di derajat genap padahal ada 2 ganjil): sisi tersisa, path tidak memuat semua.

**Kompleksitas:** `O(n + m)`.

---

## BFS pada ruang state

**Teori:** Kadang “simpul” bukan tempat, melainkan **keadaan**: `(posisi, kunci yang dipegang)`, `(posisi robot A, posisi robot B)`, `(sisa langkah ajaib)`. BFS tetap benar jika setiap transisi berbiaya 1. Jumlah keadaan harus muat: `posisi × 2^kunci ≤ ~1e7`. Analoginya: kamu bukan hanya di ruangan, tetapi “di ruangan plus sudah punya kunci merah”. Dua orang di ruangan sama dengan kunci beda adalah dua simpul beda.

**Kapan dipakai:** labirin + kunci, sliding puzzle kecil, knight + obstacle berstatus, soal “minimum operasi untuk mengubah string” jika alfabet kecil. Jangan BFS jika biaya transisi tidak seragam — pakai Dijkstra/0-1 BFS. Jangan jika state `n × n × n` dengan `n = 400` (64 juta, rapuh).

**Proses:** koridor 4 sel `0-1-2-3`, kunci di sel 1 (bit 0), pintu terkunci antara 2 dan 3 butuh kunci. Start 0 tanpa kunci, goal 3 dengan kunci.

State id = `pos * 2 + punyaKunci`.

```
state 0: pos 0, kunci 0
ambil langkah ke 1 → state 2 (pos 1, kunci 0) lalu otomatis pickup → state 3 (pos 1, kunci 1)
dari 3 ke 2 (pos 2, kunci 1) ke 3 (pos 3, kunci 1) GOAL
```

| dist | state (pos, kunci) |
|---|---|
| 0 | (0, 0) |
| 1 | (1, 0) lalu pickup di tempat: sering digabung jadi (1, 1) biaya 1 |
| 2 | (2, 1) |
| 3 | (3, 1) |

Tanpa kunci, transisi 2→3 dilarang. Jawaban 3 langkah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;

int idState(int pos, int mask, int nMask) {
    return pos * nMask + mask;
}

int bfsKunci(int n, const vector<vector<int>>& g,
             const vector<int>& kunciDi,          // bit kunci di sel, 0 jika tidak
             const vector<int>& butuh,            // mask kunci untuk MENINGGALKAN u menuju v? pakai sisi
             int start, int goal, int K) {
    // versi sederhana: untuk masuk sel v butuh (mask & butuh[v]) == butuh[v]
    int M = 1 << K;
    vector<int> dist(n * M, INF);
    queue<int> q;
    int mask0 = kunciDi[start];
    int s = idState(start, mask0, M);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int pos = cur / M, mask = cur % M;
        if (pos == goal) return dist[cur];
        for (int v : g[pos]) {
            if ((mask & butuh[v]) != butuh[v]) continue;
            int nmask = mask | kunciDi[v];
            int nxt = idState(v, nmask, M);
            if (dist[nxt] > dist[cur] + 1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

int bfsOperasi(const string& mulai, const string& target,
               const vector<pair<string, string>>& aturan) {
    // tiap aturan: ganti substring? di sini aturan adalah “ganti seluruh string jika sama”
    // pola lebih umum: state = integer kecil. contoh: minimum +1 / -1 / *2 ke target
    (void)mulai; (void)target; (void)aturan;
    return -1;
}

int minOperasiAngka(int start, int target) {
    // +1, -1, *2, jangan lewat 2*target
    if (start == target) return 0;
    int BATAS = max(start, target) * 2 + 5;
    vector<int> dist(BATAS + 1, INF);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) return dist[u];
        int kandidat[3] = {u + 1, u - 1, u * 2};
        for (int v : kandidat) {
            if (v < 0 || v > BATAS) continue;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return -1;
}

int main() {
    vector<vector<int>> g = {{1}, {0, 2}, {1, 3}, {2}};
    vector<int> kunciDi = {0, 1, 0, 0};   // kunci bit0 di sel 1
    vector<int> butuh = {0, 0, 0, 1};     // sel 3 butuh kunci
    cout << bfsKunci(4, g, kunciDi, butuh, 0, 3, 1) << '\n'; // 3
    cout << minOperasiAngka(3, 11) << '\n';
    return 0;
}
```

**Jebakan:**

1. State tidak memuat informasi yang membedakan “bisa/tidak” — BFS menemukan jalur mustahil atau kehilangan jalur.
2. `vis` hanya pada posisi, bukan `(posisi, mask)`: kunci diabaikan.
3. Batas state tidak dipotong: `*2` ke tak hingga.
4. Biaya tidak 1 (misalnya mundur lebih mahal) tetapi tetap BFS biasa.

**Kompleksitas:** `O(jumlah_state + jumlah_transisi)`.

---

## 0-1 BFS

**Teori:** Jika setiap sisi berbobot **0 atau 1**, jarak masih bisa dihitung seperti BFS, tetapi antrean diganti **deque**. Sisi 0 dimasukkan ke **depan** (jarak tidak naik), sisi 1 ke **belakang** (jarak +1). Deque selalu terurut non-menurun terhadap jarak, jadi yang keluar depan sudah final seperti BFS. Analoginya: jalan biasa biaya 1, teleport biaya 0. Teleport diproses “sekarang juga”, jalan biasa antre di gelombang berikutnya. Ini kasus khusus Dijkstra yang `O(n + m)` tanpa heap.

**Kapan dipakai:** grid “jalan vs portal”, sisi biasa vs sisi gratis, graf dua jenis biaya. Jangan dipakai jika ada bobot 2, 3, … — itu Dijkstra atau Dial. Jangan Dijkstra heap jika bobot hanya 0/1: 0-1 BFS lebih cepat dan lebih pendek.

**Proses:** sisi `0→1 (1), 0→2 (0), 2→1 (0), 1→3 (1), 2→3 (1)`, sumber 0.

| deque (jarak, simpul) | pop | relaksasi |
|---|---|---|
| [(0,0)] | 0 | 1 ← 1 (belakang), 2 ← 0 (depan) |
| [(0,2), (1,1)] | 2 | 1 ← 0+0=0 lebih baik, depan; 3 ← 1 belakang |
| [(0,1), (1,1 usang), (1,3)] | 1 | dist 0, ke 3: 0+1=1 tidak lebih baik |
| [(1,1), (1,3)] | 1 usang skip | |
| [(1,3)] | 3 | selesai |

`dist = [0, 0, 0, 1]`. Jalur terbaik ke 1 adalah `0-2-1` (dua teleport), bukan `0-1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfs01(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

vector<int> jalur01(int n, const vector<vector<pair<int, int>>>& g, int s, int t) {
    vector<ll> dist(n, INF);
    vector<int> par(n, -1);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            par[v] = u;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    if (dist[t] >= INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

vector<ll> bfs01Grid(const vector<string>& a, pair<int, int> S, char mahal) {
    int R = (int)a.size(), C = (int)a[0].size();
    auto id = [&](int r, int c) { return r * C + c; };
    vector<ll> dist(R * C, INF);
    deque<int> dq;
    dist[id(S.first, S.second)] = 0;
    dq.push_front(id(S.first, S.second));
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int r = u / C, c = u % C;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || a[nr][nc] == '#') continue;
            int w = (a[nr][nc] == mahal);
            int v = id(nr, nc);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

int main() {
    vector<vector<pair<int, int>>> g(4);
    g[0].push_back({1, 1});
    g[0].push_back({2, 0});
    g[2].push_back({1, 0});
    g[1].push_back({3, 1});
    g[2].push_back({3, 1});
    auto d = bfs01(4, g, 0);
    for (ll x : d) cout << x << ' ';
    cout << '\n';                                  // 0 0 0 1
    return 0;
}
```

**Jebakan:**

1. `push_back` untuk bobot 0: urutan deque rusak, jawaban bisa salah.
2. Bobot di luar `{0,1}` lolos tanpa assert.
3. Tidak skip entri usang: masih benar (relaksasi `dist[u]+w < dist[v]` melindungi), tetapi deque lebih gemuk.
4. Grid: biaya diletakkan di sel asal, bukan sel tujuan — off-by-one klasik.

**Kompleksitas:** `O(n + m)` waktu dan memori.

---

## Ringkasan file ini

**Teori:** DFS dan BFS adalah dua cara berjalan. DFS membawa cap waktu dan cocok untuk sifat struktural (siklus, subtree, Euler via Hierholzer yang juga stack). BFS membawa jarak sisi-sama, pewarnaan lapis, dan — dengan deque — bobot 0/1. Kahn adalah BFS pada indegree; itu kunci DAG. Flood fill adalah BFS/DFS di grid.

**Kapan dipakai:** soal tanpa bobot sebarang. Kalau muncul `w_i` sampai `1e9`, buka file 11.

**Proses (kartu saku):**

1. Gambar 4–6 simpul, telusuri tangan, cocokkan dengan `vis`/`dist`.
2. Tulis fungsi, uji graf kecil di `main`.
3. Baru tempel ke soal.

**Kode:** peta cepat — salin fungsi di atas, jangan campur 0-indexed dan 1-indexed.

**Jebakan lintas topik:**

1. Stack rekursi `1e5`.
2. Graf tidak terhubung: loop `for s = 0..n-1`.
3. Arah sisi vs soal “berteman” (tak berarah) / “mengikuti” (berarah).
4. Euler vs Hamilton; BFS vs Dijkstra; 2 warna vs 3 warna.

**Kompleksitas saku:** hampir semua `O(n + m)`. Kahn lex `O((n+m) log n)`. Ruang state `O(|S|)`.

### Latihan harian

Deck lengkap ada di `/Users/haikalmuzhoffar/KULIAH/ComProgLearning/CP/`, Day 113, 114, 116, 117, 118, 119, 120, 121, 124. Cheatsheet ini ringkasan; latihan harian jangan disalin ke sini.

### Isi file berikutnya

File 11: Dijkstra, Bellman-Ford, Floyd-Warshall, MST (Kruskal/Prim). File 12: DSU, SCC, jembatan, 2-SAT, max flow, matching, MCMF.
