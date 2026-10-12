# Siklus dan graf bipartit

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **118**. Ada-tidaknya putaran, dan pewarnaan dua warna. Dasar DFS ada di [dfs-bfs.md](dfs-bfs.md). Urutan prasyarat (Kahn) diulang singkat di sini hanya sebagai tes siklus berarah; penuhnya di [topo-dp-dag.md](topo-dp-dag.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Siklus tak berarah](#siklus-tak-berarah)
- [Rekonstruksi siklus tak berarah](#rekonstruksi-siklus-tak-berarah)
- [Pohon atau bukan](#pohon-atau-bukan)
- [Siklus berarah tiga warna](#siklus-berarah-tiga-warna)
- [Sisa Kahn](#sisa-kahn)
- [Graf bipartit](#graf-bipartit)
- [Ringkasan](#ringkasan)

---

## Siklus tak berarah

**Teori:** Pada graf tak berarah, sisi ke simpul yang sudah dikunjungi **bukan parent** adalah back-edge, dan back-edge menutup siklus. Analoginya: jalan di hutan, bertemu jejak lama yang bukan jalan pulang. Parent dikecualikan karena sisi `{u, p}` dikunjungi dari kedua ujung; itu bukan putaran.

**Kapan:** “apakah jaringan punya loop”, validasi pohon, soal yang rusak jika ada putaran. Jangan memakai cek parent pada graf berarah. Jangan menyimpulkan siklus hanya dari `m ≥ n` tanpa cek komponen.

**Proses:** sisi `0-1, 1-2, 2-0, 2-3`. DFS dari 0, parent 0 adalah `-1`.

```
  0
 / \
1---2—3
```

| u | parent | tetangga | keputusan |
|---|---|---|---|
| 0 | -1 | 1 | turun ke 1 |
| 1 | 0 | 0 skip, 2 turun | |
| 2 | 1 | 1 skip, 0 sudah vis dan bukan parent | **siklus 2-0** |
| 2 | 1 | 3 belum vis | turun (opsional) |

Siklus `0-1-2-0`. Jika sisi `2-0` dihapus, DFS selesai tanpa back-edge.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

int main() {
    FASTIO;
    vector<vector<int>> g = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    cout << adaSiklusTakBerarah(4, g) << '\n';     // 1
    vector<vector<int>> pohon = {{1}, {0, 2}, {1}};
    cout << adaSiklusTakBerarah(3, pohon) << '\n'; // 0
    return 0;
}
```

**Jebakan:**

1. Multi-sisi `u-v` dua kali: tetangga `v` muncul dua kali, yang kedua terlihat seperti back-edge. Tandai id sisi atau pakai DSU.
2. Self-loop `u-u` adalah siklus; cek `v == u`.
3. Hanya DFS dari 0: siklus di komponen lain lolos.
4. Graf berarah dipaksa tes parent: salah total.

**Kompleksitas:** `O(n + m)`.

---

## Rekonstruksi siklus tak berarah

**Teori:** Saat back-edge `ketemu → start` ditemukan, jejak `par` dari `ketemu` naik ke `start`, lalu tutup dengan `start`. Analoginya: kamu bertemu tanda lama, lalu mengikuti jejak pulang sampai tanda itu.

**Kapan:** soal minta satu siklus, bukan hanya ya/tidak. Jangan membangun semua siklus (bisa eksponensial).

**Proses:** graf yang sama. Misal DFS 0-1-2, back-edge `2-0`. `start=0`, `ketemu=2`, `par[2]=1`, `par[1]=0`.

```
naik: 2 → 1 → 0
tutup: 0
barisan: 0, 1, 2, 0   (setelah reverse dari [0, 2, 1, 0] tergantung cara push)
```

Satu siklus sah: `0-1-2-0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

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
    FASTIO;
    vector<vector<int>> g = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    auto c = satuSiklus(4, g);
    for (int x : c) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 0  (atau rotasi)
    return 0;
}
```

**Jebakan:**

1. Arah `par` terbalik: barisan tidak menutup.
2. Multi-sisi tanpa id: “siklus” palsu `u-v-u`.
3. Self-loop: siklus panjang 1; beberapa soal menolak, beberapa menerima — baca.
4. `reverse` lupa: output masih benar sebagai siklus terbalik, tetapi beda dari jejak DFS.

**Kompleksitas:** `O(n + m)`.

---

## Pohon atau bukan

**Teori:** Pohon = graf tak berarah **terhubung** dan **tanpa siklus**. Setara: terhubung dan `m = n-1`. Setara: `m = n-1` dan tanpa siklus. Satu syarat saja tidak cukup: `m = n-1` bisa siklus di satu komponen plus komponen terputus.

**Kapan:** “apakah jaringan pohon”, “tambah sisi minimum supaya pohon” (itu `k-1` jika `k` komponen dan sudah acyclic). Jangan memakai definisi pohon pada graf berarah (itu arborescence).

**Proses:**

| graf | n | m | terhubung | siklus | pohon? |
|---|---|---|---|---|---|
| `0-1, 1-2` | 3 | 2 | ya | tidak | ya |
| `0-1, 1-2, 2-0` | 3 | 3 | ya | ya | tidak |
| `0-1, 2-3` | 4 | 2 | tidak | tidak | tidak |
| `0-1, 1-2, 2-0` plus 3 isolasi | 4 | 3 | tidak | ya | tidak, meski `m=n-1` |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int hitungSisi(const vector<vector<int>>& g) {
    int m = 0;
    for (int u = 0; u < (int)g.size(); u++) m += (int)g[u].size();
    return m / 2;
}

bool terhubung(int n, const vector<vector<int>>& g) {
    vector<int> vis(n);
    int s = 0, cnt = 0;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        cnt++;
        for (int v : g[u]) if (!vis[v]) dfs(v);
    };
    dfs(s);
    return cnt == n;
}

bool adalahPohon(int n, const vector<vector<int>>& g) {
    if (hitungSisi(g) != n - 1) return false;
    return terhubung(n, g);
}

bool adalahHutan(int n, const vector<vector<int>>& g) {
    vector<int> vis(n);
    function<bool(int, int)> dfs = [&](int u, int p) {
        vis[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            if (vis[v]) return false;
            if (!dfs(v, u)) return false;
        }
        return true;
    };
    for (int s = 0; s < n; s++)
        if (!vis[s] && !dfs(s, -1)) return false;
    return true;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1}, {0, 2}, {1}};
    cout << adalahPohon(3, g) << ' ' << adalahHutan(3, g) << '\n'; // 1 1
    vector<vector<int>> s = {{1, 2}, {0, 2}, {0, 1}, {}};
    cout << adalahPohon(4, s) << ' ' << adalahHutan(4, s) << '\n'; // 0 0
    return 0;
}
```

Pohon dicek lewat `m = n-1` plus satu DFS keterhubungan; hutan dicek acyclic per komponen.

**Jebakan:**

1. `m == n-1` saja.
2. `m` dihitung dari `g[u].size()` tanpa bagi 2.
3. Hutan (acyclic, boleh banyak komponen) dikira pohon.

**Kompleksitas:** `O(n + m)`.

---

## Siklus berarah tiga warna

**Teori:** Pada graf berarah, back-edge menuju simpul yang **sedang** di stack rekursi (warna abu-abu). Analoginya: mata kuliah A butuh B, B butuh C, C butuh A. Tiga warna: 0 putih (belum), 1 abu (sedang), 2 hitam (selesai). Sisi ke hitam adalah forward/cross, **bukan** siklus. Dua warna saja salah.

**Kapan:** dependensi, deadlock, syarat topological sort. Jangan tes parent tak berarah. Jangan menyimpulkan siklus dari “sisi ke simpul sudah dikunjungi” tanpa membedakan abu vs hitam.

**Proses:** sisi `0→1, 1→2, 2→0, 0→3`.

| u | warna saat masuk | tetangga | warna v | arti |
|---|---|---|---|---|
| 0 | 0→1 | 1 | 0 | turun |
| 1 | 1 | 2 | 0 | turun |
| 2 | 1 | 0 | 1 abu | **back-edge, siklus** |
| | | | | 3 tidak perlu |

Kalau `2→0` diganti `2→3`: 2 melihat 3 putih, 3 selesai hitam, 0 selesai. Tidak ada sisi ke abu → DAG.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

int main() {
    FASTIO;
    vector<vector<int>> g = {{1, 3}, {2}, {0}, {}};
    cout << adaSiklusBerarah(4, g) << '\n';        // 1
    vector<vector<int>> dag = {{1, 3}, {2}, {3}, {}};
    cout << adaSiklusBerarah(4, dag) << '\n';      // 0
    return 0;
}
```

**Jebakan:**

1. Dua warna: sisi ke hitam dikira siklus.
2. Graf tak berarah diperlakukan 3-warna tanpa membuang sisi balik: setiap sisi jadi “siklus” palsu.
3. Self-loop `u→u` langsung warna 1 ke 1.
4. Tidak menghitamkan saat selesai: seluruh komponen terlihat abu selamanya.

**Kompleksitas:** `O(n + m)`.

---

## Sisa Kahn

**Teori:** Kahn berulang kali menghapus simpul indegree 0. Yang tidak pernah masuk urutan berada di siklus, atau hanya bisa dicapai lewat siklus. Analoginya: mata kuliah yang prasyaratnya berputar tidak pernah “siap diambil”. Tes lengkap: `ord.size() != n`.

**Kapan:** butuh daftar simpul yang “terkunci siklus”, atau kamu sudah menulis Kahn untuk topo. Penuhnya di [topo-dp-dag.md](topo-dp-dag.md).

**Proses:** sisi `0→1, 1→2, 2→0, 0→3`. Indegree `[1, 1, 1, 1]` — tunggu: 3 hanya dari 0, indegree `[1,1,1,1]`? 0 dari 2, 1 dari 0, 2 dari 1, 3 dari 0 → `[1,1,1,1]`. Tidak ada yang 0? 3 punya 1. Semua ≥ 1. Tidak ada yang masuk antrean? 0 punya indegree 1. `ord` kosong. Tetapi 3 **bisa** selesai jika 0 dihapus — 3 tergantung siklus, bukan anggota siklus. Perbaiki: indegree 3 = 1, 0 = 1. Memang tidak ada sumber. Semua 4 “terpengaruh”.

Graf `0→1, 1→2, 2→0, 3` (3 isolasi berarah). Indegree `[1,1,1,0]`. Ambil 3. `ord = [3]`. Sisa `{0,1,2}`.

| antrean | ambil | sisa belum ok |
|---|---|---|
| `[3]` | 3 | 0,1,2 |
| `[]` | — | 0,1,2 siklus |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> simpulTerpengaruhSiklus(int n, const vector<vector<int>>& g) {
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
    FASTIO;
    vector<vector<int>> g = {{1}, {2}, {0}, {}};
    auto s = simpulTerpengaruhSiklus(4, g);
    for (int x : s) cout << x << ' ';
    cout << '\n';                                  // 0 1 2
    return 0;
}
```

**Jebakan:**

1. Mengira sisa Kahn = tepat simpul di siklus (3 di contoh pertama file 3-warna ikut jika bergantung).
2. Lupa `ord.size() == n` lalu memakai `ord` untuk DP.
3. Arah sisi “u sebelum v” terbalik di input.

**Kompleksitas:** `O(n + m)`.

---

## Graf bipartit

**Teori:** Graf bipartit bisa diwarnai dua warna sehingga setiap sisi menghubungkan warna berbeda. Setara dengan: **tidak ada siklus ganjil**. Analoginya papan catur: hitam hanya bertetangga putih. Pewarnaan BFS: sumber 0, tetangga 1, berikutnya 0. Konflik = dua ujung sewarna = siklus ganjil.

Pohon selalu bipartit. Graf tak terhubung bipartit iff setiap komponen bipartit.

**Kapan:** matching ([sat2-flow.md](sat2-flow.md)), “bagi dua kelompok yang tidak berteman di dalam”, paritas. Jangan mengira graf berarah memakai definisi yang sama tanpa mengubah sisi jadi tak berarah.

**Proses:** kotak `0-1, 1-2, 2-3, 3-0` (siklus 4 = genap) vs tambah `0-2` (siklus 3).

Kotak:

| u | warna | tetangga | warna v |
|---|---|---|---|
| 0 | 0 | 1, 3 | 1 dan 1 |
| 1 | 1 | 2 | 0 |
| 3 | 1 | 2 | 2 sudah 0, cocok |
| 2 | 0 | — | bipartit, `{0,2}` / `{1,3}` |

Tambah `0-2`: 0 berwarna 0, 2 sudah 0 → konflik. Siklus `0-1-2-0` panjang 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    vector<vector<int>> kotak = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    vector<int> col;
    cout << bipartit(4, kotak, col) << '\n';       // 1
    vector<vector<int>> segitiga = {{1, 2}, {0, 2}, {0, 1}};
    cout << bipartit(3, segitiga, col) << '\n';    // 0
    return 0;
}
```

**Jebakan:**

1. Hanya mewarnai komponen simpul 0.
2. Simpul terisolasi tetap bipartit; masuk sisi mana pun.
3. Matching butuh partisi kiri/kanan; pewarnaan memberi partisi, tetapi “mana kiri” bisa terbalik per komponen.
4. Memaksa warna global dari komponen lain.

**Kompleksitas:** `O(n + m)`.

---

## Ringkasan

**Teori:** Tak berarah: back-edge ≠ parent. Berarah: sisi ke abu. Bipartit: tidak ada siklus ganjil. Pohon: terhubung + acyclic + `m = n-1`.

**Kapan:** loop, deadlock, 2 kelompok, validasi pohon. Topo penuh di file berikutnya.

**Proses:** gambar kotak vs segitiga, warnai tangan, cocokkan dengan BFS.

**Jebakan lintas:**

1. Dua warna pada graf berarah.
2. `m = n-1` tanpa keterhubungan.
3. Multi-sisi sebagai siklus palsu.
4. Kahn sisa ≠ tepat anggota siklus.

**Kompleksitas saku:** semua `O(n + m)`.

Lanjut: [topo-dp-dag.md](topo-dp-dag.md) · [dfs-bfs.md](dfs-bfs.md) · [sat2-flow.md](sat2-flow.md)
