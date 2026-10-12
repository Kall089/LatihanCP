# 0-1 BFS

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **113** (ekspansi). Dasar antrean FIFO ada di [dfs-bfs.md](dfs-bfs.md). State plus biaya 0/1 ada di [bfs-state.md](bfs-state.md). Heap untuk bobot sebarang tak negatif ada di [dijkstra.md](dijkstra.md). File ini memisahkan **deque** dari BFS biasa, lalu membandingkannya dengan Dijkstra pada graf yang sama.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**, fungsi terpisah, `main` hanya menguji.

## Daftar isi

- [Peta senjata](#peta-senjata)
- [Kenapa deque benar](#kenapa-deque-benar)
- [Jejak numerik vs Dijkstra](#jejak-numerik-vs-dijkstra)
- [Kode dasar dan entri usang](#kode-dasar-dan-entri-usang)
- [Rekonstruksi jalur](#rekonstruksi-jalur)
- [Grid: portal, lantai, tembok](#grid-portal-lantai-tembok)
- [Banyak sumber](#banyak-sumber)
- [Dial dan bobot kecil](#dial-dan-bobot-kecil)
- [State 0-1, bukan sisa-k](#state-0-1-bukan-sisa-k)
- [Ringkasan](#ringkasan)

---

## Peta senjata

**Teori:** BFS biasa mengunci jarak saat simpul **pertama kali** masuk antrean, karena setiap sisi menambah tepat 1. Kalau sisi boleh berbobot 0, jarak bisa **tidak naik**. FIFO biasa salah: tetangga lewat sisi 0 harus diproses **sekarang**, sebelum tetangga lewat sisi 1. Deque melakukan itu: `push_front` untuk 0, `push_back` untuk 1. Analoginya: jalan kaki biaya 1, teleport biaya 0; teleport diproses “masih di menit yang sama”.

Dijkstra juga benar pada bobot 0/1 (karena `w ≥ 0`), tetapi heap `O((n+m) log n)` membuang kerja. 0-1 BFS adalah Dijkstra yang antreannya sudah terurut karena hanya dua nilai.

**Kapan:** setiap sisi (atau setiap transisi state) berbobot **tepat** `{0, 1}`. Portal, “pindah lantai gratis”, “pakai kartu atau tidak”. Jangan jika ada 2, 3, … — itu [dijkstra.md](dijkstra.md) atau Dial. Jangan jika ada negatif — [bellman-floyd.md](bellman-floyd.md). Jangan DFS: jalur dalam dulu, jarak 0/1 rusak.

| Bobot | Alat | File |
|---|---|---|
| semua 1 (atau tak berbobot) | `queue` BFS | [dfs-bfs.md](dfs-bfs.md) |
| hanya 0 dan 1 | deque 0-1 | **ini** |
| integer kecil `0..K` | Dial / bucket | di bawah |
| `≥ 0` sebarang | heap Dijkstra | [dijkstra.md](dijkstra.md) |
| ada negatif | Bellman / SPFA | [bellman-floyd.md](bellman-floyd.md) |
| state + kunci / sisa tembok | BFS state seragam | [bfs-state.md](bfs-state.md) |

**Proses:** kartu keputusan. Soal: “minimum biaya, tiap langkah 0 atau 1”. Hitung `|V|` dulu (sel, atau sel×mask). Jika `w` bisa 2, berhenti — bukan file ini.

**Kode:** kerangka baca sisi 0/1.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<pair<int, int>>> baca01(int n, int m, bool berarah) {
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].push_back({v, w});
        if (!berarah) g[v].push_back({u, w});
    }
    return g;
}

bool hanya01(const vector<vector<pair<int, int>>>& g) {
    for (auto& adj : g)
        for (auto [v, w] : adj)
            if (w != 0 && w != 1) return false;
    return true;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(3);
    g[0].push_back({1, 0});
    g[1].push_back({2, 1});
    cout << hanya01(g) << '\n';                    // 1
    return 0;
}
```

**Jebakan:**

1. Membaca `w` lalu memakai `queue` BFS — sisi 0 diabaikan sebagai “sudah vis”.
2. Graf tak berarah: lupa sisi balik dengan **bobot yang sama**.
3. Soal 1-index: lupa `--u; --v`.

**Kompleksitas:** bangun list `O(n + m)`.

---

## Kenapa deque benar

**Teori:** Invariansi: isi deque selalu terurut non-menurun menurut `dist`, dan nilainya hanya dua lapis berurutan (`d` di depan, `d+1` di belakang). Sisi 0 menjaga `dist` tetap `d` → masuk depan, masih lapis yang sama. Sisi 1 menaikkan ke `d+1` → masuk belakang. Yang keluar depan punya `dist` terkecil yang belum dikunci. Analoginya dua antrian yang ditempel: “sekarang” dan “sebentar lagi”.

Bukti singkat: misalkan `u` keluar dengan `dist[u] = d`. Semua yang masih di deque bernilai `d` atau `d+1`. Relaksasi `v` lewat 0 mendapat `d` dan didorong ke depan; lewat 1 mendapat `d+1` dan ke belakang. Tidak ada cara mendapat `d-1` dari sini karena bobot tidak negatif.

Perbedaan dengan BFS: BFS menandai `vis` saat **push** dan tidak pernah merelaksasi ulang. 0-1 **harus** merelaksasi ulang jika menemukan jalur 0 yang lebih baik (contoh: `s → t` bobot 1, lalu jalur `s → u → t` dua kali 0).

**Kapan:** pakai invariansi ini untuk men-debug: cetak deque, pastikan tidak ada `2` muncul sebelum semua `1` habis. Jangan `push_back` untuk bobot 0 — invariansi pecah, jawaban bisa lebih besar.

**Proses:** tiga simpul, sisi `0→1 (1), 0→2 (0), 2→1 (0)`.

Jika BFS biasa (abaikan bobot, vis saat push):

```
antrean [0], vis 0
push 1 dan 2, dist[1]=1 (salah), dist[2]=1 (salah, harus 0)
```

Deque:

```
[0] dist 0
pop 0: 1 ← 1 belakang, 2 ← 0 depan
[2, 1]
pop 2: 1 ← 0 lebih baik, depan
[1 (dist 0), 1 (usang dist 1)]
```

`dist[1] = 0`. BFS biasa menjawab 1.

**Kode:** versi yang **salah** (BFS vis-saat-push) vs benar, diuji pada graf ini.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfsSalahAbaikanBobot(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, w] : g[u]) if (dist[v] >= INF) {
            dist[v] = dist[u] + 1; // salah: w dibuang
            q.push(v);
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(3);
    g[0].push_back({1, 1});
    g[0].push_back({2, 0});
    g[2].push_back({1, 0});
    auto d = bfsSalahAbaikanBobot(3, g, 0);
    cout << d[1] << '\n';                          // 1  (seharusnya 0)
    return 0;
}
```

**Jebakan:**

1. Menyalin pola BFS `if (dist[v] == INF)` ke 0-1: jalur 0 yang datang belakangan ditolak.
2. Mengira “pertama kali dikunjungi = final” seperti BFS — hanya benar jika semua sisi 1.

**Kompleksitas:** penjelasan O(1); implementasi salah tetap `O(n+m)` tetapi jawabannya dusta.

---

## Jejak numerik vs Dijkstra

**Teori:** Graf uji **berbeda** dari contoh 4 simpul di [dfs-bfs.md](dfs-bfs.md). Enam simpul, sumber 0. Sisi berarah:

```
0 --0--> 1 --1--> 3 --0--> 5
|        |        ^
1        0        1
v        v        |
2 --0--> 4 -------+
     \--1--> 5
```

Daftar sisi `(u, v, w)`:

`0→1:0, 0→2:1, 1→3:1, 1→4:0, 2→4:0, 4→3:1, 4→5:1, 3→5:0`.

**Kapan:** menghitung tangan sebelum percaya `main`. Jika jejak deque dan jejak heap Dijkstra **beda dist**, salah satu implementasi rusak (pada 0/1 keduanya wajib sama).

**Proses:** deque. Notasi `u@d` = simpul `u` berjarak `d`.

| langkah | pop | deque setelah relaksasi | dist `[0..5]` |
|---|---|---|---|
| init | — | `0@0` | `0,∞,∞,∞,∞,∞` |
| 1 | 0 | `1@0, 2@1` | `0,0,1,∞,∞,∞` |
| 2 | 1 | `4@0, 2@1, 3@1` | `0,0,1,1,0,∞` |
| 3 | 4 | `2@1, 3@1, 5@1` (3 lewat 4 = 1, sama; 5←1) | `0,0,1,1,0,1` |
| 4 | 2 | 4 sudah 0, tidak membaik | sama |
| 5 | 3 | `5@1` sudah, 3→5 bobot 0 memberi 1, sama | sama |
| 6 | 5 | selesai | `0,0,1,1,0,1` |

Jalur ke 5: `0-1-4-5` biaya `0+0+1=1`, atau `0-1-3-5` biaya `0+1+0=1`.

Dijkstra heap pada graf yang sama:

| pop `(d,u)` | relaksasi |
|---|---|
| `(0,0)` | 1←0, 2←1 |
| `(0,1)` | 3←1, 4←0 |
| `(0,4)` | 5←1, 3 tetap 1 |
| `(1,2)` | 4 tidak membaik |
| `(1,3)` | 5 tetap 1 |
| `(1,5)` | selesai |

Dist identik. Heap menyimpan pasangan dan log; deque hanya dua ujung.

**Kode:** kedua fungsi, satu graf, bandingkan.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<ll> bfs01(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return dist;
}

vector<ll> dijkstra(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dist[v]) {
            dist[v] = d + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

int main() {
    FASTIO;
    int n = 6;
    vector<vector<pair<int, int>>> g(n);
    auto add = [&](int u, int v, int w) { g[u].push_back({v, w}); };
    add(0, 1, 0); add(0, 2, 1); add(1, 3, 1); add(1, 4, 0);
    add(2, 4, 0); add(4, 3, 1); add(4, 5, 1); add(3, 5, 0);
    auto a = bfs01(n, g, 0);
    auto b = dijkstra(n, g, 0);
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
    // 0 0 1 1 0 1
    cout << (a == b) << '\n';                      // 1
    return 0;
}
```

**Jebakan:**

1. Membandingkan dengan BFS jumlah sisi: ke 5 ada jalur 3 sisi (`0-1-3-5`) dan 3 sisi (`0-1-4-5`); BFS tak berbobot tidak membedakan 0 vs 1.
2. `priority_queue` default max-heap: jarak terbalik.

**Kompleksitas:** 0-1 `O(n+m)`, Dijkstra `O((n+m) log n)` pada graf yang sama.

---

## Kode dasar dan entri usang

**Teori:** Relaksasi ketat `dist[u]+w < dist[v]` boleh mendorong `v` berkali-kali. Entri lama tetap di deque. Saat `v` keluar dengan `d > dist[v]`, itu usang: lewati. Analoginya: surat “jarak 3” datang setelah kamu sudah tahu jarak 1 — buang surat itu.

Tanpa skip, relaksasi dari usang tidak mempebaiki (ketat), jadi jawaban tetap benar, tetapi deque membengkak sampai `O(n m)` di graf jelek.

**Kapan:** `n, m ≤ 1e6` hampir selalu aman tanpa skip. Tetap tulis skip: murah dan sama polanya dengan Dijkstra lazy.

**Proses:** sisi `0→1 (1)` dua kali, plus `0→1 (0)` belakangan di daftar. Urutan tetangga: dulu 1, lalu 0. Deque: `1@1` masuk belakang, lalu `1@0` masuk depan. Pop `1@0` final; pop `1@1` usang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfs01Skip(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        if (false) { } // tempat komentar: cek usang di bawah
        for (auto [v, w] : g[u]) {
            if (w != 0 && w != 1) continue; // jaga-jaga
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

vector<ll> bfs01SkipKetat(int n, const vector<vector<pair<int, int>>>& g, int s) {
    vector<ll> dist(n, INF);
    vector<int> inq(n, 0);
    deque<int> dq;
    dist[s] = 0;
    dq.push_front(s);
    inq[s] = 1;
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        inq[u] = 0;
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (!inq[v]) {
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
                inq[v] = 1;
            } else if (w == 0) {
                // sudah di deque; posisi mungkin belakang — dorong depan saja
                dq.push_front(v);
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(2);
    g[0].push_back({1, 1});
    g[0].push_back({1, 0});
    auto d = bfs01Skip(2, g, 0);
    cout << d[1] << '\n';                          // 0
    return 0;
}
```

Versi `inq` menghemat dobel, tetapi dorongan depan saat `v` sudah di belakang **menggandakan** entri. Untuk kontes, versi relaksasi ketat tanpa `inq` (fungsi pertama) paling pendek dan cukup.

**Jebakan:**

1. `push_front` dan `push_back` tertukar.
2. `w` bertipe `ll` lalu dibandingkan `== 0` setelah overflow.
3. `INF = LLONG_MAX` lalu `INF + 0` overflow — pakai `4e18`.

**Kompleksitas:** `O(n + m)` jika tiap simpul didorong O(1) kali rata-rata; worst-case lebih gemuk tanpa disiplin, tetap jauh di bawah heap pada 0/1.

---

## Rekonstruksi jalur

**Teori:** Simpan `par[v] = u` saat `dist[v]` membaik. Setelah selesai, jalan dari `t` ke `s`. Analoginya: setiap kali harga baru tercatat, tempel stiker “dari siapa”.

Jika ada banyak jalur optimal, `par` menyimpan yang **terakhir** merelaksasi. Mau yang leksikografis: saat `dist` sama, bandingkan calon parent (bukan file wajib).

**Kapan:** “cetak rute portal”. Jangan merekonstruksi dari `dist` saja tanpa parent: tetangganya bisa banyak.

**Proses:** graf 6 simpul di atas, `s=0`, `t=5`. Satu jejak parent:

```
par[1]=0, par[4]=1, par[2]=0, par[3]=1, par[5]=4
jalur 5←4←1←0  →  0-1-4-5
```

Kalau `3→5` merelaksasi belakangan dengan dist sama, parent bisa jadi 3: `0-1-3-5`. Kedua biaya 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

pair<vector<ll>, vector<int>> bfs01Par(int n, const vector<vector<pair<int, int>>>& g, int s) {
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
    return {dist, par};
}

vector<int> bangunJalur(const vector<int>& par, int s, int t) {
    if (s != t && par[t] == -1) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path.empty() || path[0] != s) return {};
    return path;
}

int main() {
    FASTIO;
    int n = 6;
    vector<vector<pair<int, int>>> g(n);
    g[0].push_back({1, 0}); g[0].push_back({2, 1});
    g[1].push_back({3, 1}); g[1].push_back({4, 0});
    g[2].push_back({4, 0}); g[4].push_back({3, 1});
    g[4].push_back({5, 1}); g[3].push_back({5, 0});
    auto [d, par] = bfs01Par(n, g, 0);
    auto p = bangunJalur(par, 0, 5);
    cout << d[5] << '\n';                          // 1
    for (int x : p) cout << x << ' ';
    cout << '\n';                                  // 0 1 4 5  (atau 0 1 3 5)
    return 0;
}
```

**Jebakan:**

1. Lupa `reverse`.
2. `par[s]` tidak `-1` lalu loop tak hingga.
3. Mengupdate `par` saat `dist` **sama** tanpa niat — jalur tetap optimal, tetapi tes sampel bisa beda rute.

**Kompleksitas:** sama `O(n+m)`, rekonstruksi `O(panjang jalur)`.

---

## Grid: portal, lantai, tembok

**Teori:** Sel adalah simpul. Empat arah. Biaya pada **sel tujuan** (konvensi file ini, sama semangat [bfs-state.md](bfs-state.md)): `.` = 0, `X` = 1, `#` = terlarang. Portal: pasangan huruf `A`…`Z` adalah sisi **tambahan bobot 0** antar sel yang sama hurufnya (setelah masuk sel itu). Analoginya: lantai biasa gratis, pasir mahal 1, lubang cacing gratis.

Jangan mencampur “boleh hancurkan ≤ K tembok” ke sini. Itu dimensi `sisa` plus BFS seragam di [bfs-state.md](bfs-state.md).

**Kapan:** labirin dua jenis lantai; “minimum pasir yang diinjak”. Jangan 8 arah kecuali soal bilang diagonal.

**Proses:** peta 2×5, start `(0,0)`, goal `(1,4)`.

```
. X . . .
. . X . .
```

id = `r*C+c`. Dist (biaya sel tujuan, start 0):

```
0 1 1 1 1
0 0 1 1 1
```

Goal dist **1** (satu `X` di jalur atas, atau satu `X` di bawah). Jalur bawah: `(0,0)-(1,0)-(1,1)-(1,2 X)-(1,3)-(1,4)` biaya 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

int idrc(int r, int c, int C) { return r * C + c; }

vector<ll> bfs01Grid(const vector<string>& a, pair<int, int> S, char mahal) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<ll> dist(R * C, INF);
    deque<int> dq;
    int s = idrc(S.first, S.second, C);
    dist[s] = 0;
    dq.push_front(s);
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int r = u / C, c = u % C;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (a[nr][nc] == '#') continue;
            int w = (a[nr][nc] == mahal);
            int v = idrc(nr, nc, C);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

vector<ll> bfs01Portal(const vector<string>& a, pair<int, int> S) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<int>> hur(26);
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (a[r][c] >= 'A' && a[r][c] <= 'Z')
                hur[a[r][c] - 'A'].push_back(idrc(r, c, C));
    vector<ll> dist(R * C, INF);
    deque<int> dq;
    int s = idrc(S.first, S.second, C);
    dist[s] = 0;
    dq.push_front(s);
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int r = u / C, c = u % C;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || a[nr][nc] == '#') continue;
            int v = idrc(nr, nc, C);
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                dq.push_back(v);
            }
        }
        char ch = a[r][c];
        if (ch >= 'A' && ch <= 'Z') {
            for (int v : hur[ch - 'A']) if (v != u && dist[u] + 0 < dist[v]) {
                dist[v] = dist[u];
                dq.push_front(v);
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<string> a = {".X...", "..X.."};
    auto d = bfs01Grid(a, {0, 0}, 'X');
    cout << d[idrc(1, 4, 5)] << '\n';              // 1
    vector<string> b = {"A.#.A"};
    auto p = bfs01Portal(b, {0, 0});
    cout << p[4] << '\n';                          // 0  (portal A ke A)
    return 0;
}
```

**Jebakan:**

1. Biaya di sel **asal** — start yang `X` dibiayai dua kali atau tidak sama sekali.
2. Portal dipasang sebagai langkah 1: jawaban terlalu besar.
3. Huruf portal dipakai ulang tanpa daftar `hur`.
4. Diagonal tidak diminta tetapi diaktifkan.

**Kompleksitas:** grid `O(RC)`; portal tambahan `O(RC + Σ|hur|^2)` jika tiap kunjungan menyapu semua pasangan — cache “sudah teleport huruf ini” jika `|hur|` besar.

---

## Banyak sumber

**Teori:** Semua sumber `dist = 0`, semua masuk depan deque. Gelombang 0/1 dari semuanya sekaligus. Analoginya: beberapa portal masuk (gratis) plus pasir. Bukan `k` kali 0-1 lalu `min`.

**Kapan:** “jarak 0-1 ke gerbang terdekat”. Jangan menumpuk sumber dobel tanpa cek `dist`.

**Proses:** garis 5 simpul `0-1-2-3-4`, sisi berurutan bobot 1, plus sisi `1-2` bobot 0 (paralel). Sumber 0 dan 4.

```
dist awal 0:0, 4:0
dari 0: 1 ← 1
dari 4: 3 ← 1
dari 1: 2 ← 1 (sisi 1) dan 2 ← 1 (sisi 0 dari 1? sisi 1-2 bobot 0 → 2 ← 1)
```

Sebenarnya `1-2` bobot 0: `dist[2] = dist[1] + 0 = 1`. Dari 3 juga 1. Jadi `[0,1,1,1,0]`.

Tanpa sisi 0: `[0,1,2,1,0]` seperti BFS multi di [dfs-bfs.md](dfs-bfs.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfs01Multi(int n, const vector<vector<pair<int, int>>>& g, const vector<int>& src) {
    vector<ll> dist(n, INF);
    deque<int> dq;
    for (int s : src) if (dist[s] > 0) {
        dist[s] = 0;
        dq.push_front(s);
    }
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(5);
    auto add = [&](int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    add(0, 1, 1); add(1, 2, 0); add(2, 3, 1); add(3, 4, 1);
    auto d = bfs01Multi(5, g, {0, 4});
    for (ll x : d) cout << x << ' ';
    cout << '\n';                                  // 0 1 1 1 0
    return 0;
}
```

**Jebakan:**

1. Sumber diisi `dist=0` tetapi tidak masuk deque.
2. Menjalankan 0-1 dari tiap gerbang: `O(k(n+m))`.

**Kompleksitas:** tetap `O(n+m)`.

---

## Dial dan bobot kecil

**Teori:** Jika bobot integer `0..K` dengan `K` kecil (bukan hanya 0/1), pakai ** Dial **: `K+1` bucket (deque atau vector antrean) menurut `dist % (K+1)` atau bucket `dist` sampai `maxDist`. Analoginya: 0-1 adalah Dial dengan 2 ember. Dijkstra heap menang jika `K` besar.

0-1 **bukan** Dial: jangan menulis `K+1` bucket jika `K=1` — deque dua ujung sudah cukup.

**Kapan:** `w ≤ 10` dan `n m` besar, heap ketat. Jangan Dial untuk `w ≤ 1e9`.

**Proses:** sisi `0→1 (2), 0→2 (1), 2→1 (2)`, `K=2`. Dist: `0=0, 2=1, 1=2` (lewat 0 langsung) atau `1+2=3` kalah.

Ember: `B[0]={0}`, pop 0, 2 masuk `B[1]`, 1 masuk `B[2]`. Pop ember 1: simpul 2, 1 lewat 2 = 3 > 2. Jawab `dist[1]=2`.

**Kode:** Dial sederhana dengan `vector<queue<int>>` berukuran `maxDist+1` (aman jika `maxDist = n*K` kecil).

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> dial(int n, const vector<vector<pair<int, int>>>& g, int s, int K) {
    ll MAXD = 1LL * n * K + 5;
    vector<ll> dist(n, INF);
    vector<queue<int>> bucket(MAXD + 1);
    dist[s] = 0;
    bucket[0].push(s);
    for (ll d = 0; d <= MAXD; d++) {
        while (!bucket[d].empty()) {
            int u = bucket[d].front();
            bucket[d].pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : g[u]) {
                ll nd = dist[u] + w;
                if (nd < dist[v] && nd <= MAXD) {
                    dist[v] = nd;
                    bucket[nd].push(v);
                }
            }
        }
    }
    return dist;
}

int main() {
    FASTIO;
    vector<vector<pair<int, int>>> g(3);
    g[0].push_back({1, 2});
    g[0].push_back({2, 1});
    g[2].push_back({1, 2});
    auto d = dial(3, g, 0, 2);
    cout << d[1] << ' ' << d[2] << '\n';           // 2 1
    return 0;
}
```

**Jebakan:**

1. Memakai 0-1 BFS pada `w=2`: `push_back` menganggap semua non-zero sama, `dist[1]` bisa 3 jika urutan jelek, atau kebetulan benar — **tidak dijamin**.
2. `MAXD = n*K` overflow `int`.

**Kompleksitas:** Dial `O(n K + m)`, memori `O(n K)` jika bucket per jarak.

---

## State 0-1, bukan sisa-k

**Teori:** [bfs-state.md](bfs-state.md) meratakan tuple jadi id. Jika transisi state berbiaya 0 atau 1, deque pada id. Jika soal “hancurkan paling banyak K tembok” dan **setiap langkah tetap 1**, itu BFS biasa pada `(pos, sisa)` — **bukan** 0-1.

Analoginya: membayar pasir (0/1 pada langkah) vs membawa K bom (dimensi).

**Kapan:** “portal gratis di state yang sama”, “toggle saklar gratis vs langkah mahal”. Jangan menempel deque pada `(pos, sisa)` hanya karena ada angka 0.

**Proses:** dua sel `0-1`, saklar di 0: toggle bit gratis (0), pindah ke 1 biaya 1. State `(pos, bit)`, id `pos*2+bit`. Start `(0,0)`.

```
(0,0) --0--> (0,1) --1--> (1,1)
(0,0) --1--> (1,0)
```

Dist ke `(1,1)` = 1 (toggle lalu langkah). Bukan 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

int id2(int pos, int bit) { return pos * 2 + bit; }

vector<ll> bfs01Saklar() {
    int N = 4;
    vector<vector<pair<int, int>>> g(N);
    g[id2(0, 0)].push_back({id2(0, 1), 0});
    g[id2(0, 1)].push_back({id2(0, 0), 0});
    g[id2(0, 0)].push_back({id2(1, 0), 1});
    g[id2(0, 1)].push_back({id2(1, 1), 1});
    g[id2(1, 0)].push_back({id2(1, 1), 0});
    g[id2(1, 1)].push_back({id2(1, 0), 0});
    vector<ll> dist(N, INF);
    deque<int> dq;
    dist[id2(0, 0)] = 0;
    dq.push_front(id2(0, 0));
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return dist;
}

int main() {
    FASTIO;
    auto d = bfs01Saklar();
    cout << d[id2(1, 1)] << '\n';                  // 1
    return 0;
}
```

**Jebakan:**

1. `vis` hanya `pos` — bit hilang.
2. Toggle dianggap biaya 1 tanpa baca soal.
3. `|S|` tidak dihitung: `n * 2^k` meledak.

**Kompleksitas:** `O(|S| + |transisi|)`.

---

## Ringkasan

**Teori:** Deque menjaga dua lapis jarak. Sisi 0 depan, sisi 1 belakang. Dist sama dengan Dijkstra, waktu linier.

**Kapan:**

| Soal | Alat |
|---|---|
| 0/1 saja | 0-1 BFS |
| semua 1 | BFS |
| `w ≥ 0` umum | Dijkstra |
| `w` kecil `0..K` | Dial |
| sisa K tembok, langkah 1 | BFS state |

**Proses saku:** gambar 6 simpul di atas, cocokkan `0 0 1 1 0 1`, baru tempel kode.

**Jebakan lintas:**

1. `push_back` untuk 0.
2. Vis-saat-push seperti BFS.
3. 0-1 dipakai pada `w=2`.
4. Sisa-K dicampur deque.
5. Heap dipilih padahal 0/1 — biasanya AC, tetapi lebih lambat dan bukan senjata yang diminta latihan.

**Kompleksitas saku:** `O(n+m)` waktu dan memori. Heap `O((n+m) log n)` untuk cek silang.

Lanjut: [dfs-bfs.md](dfs-bfs.md) · [dijkstra.md](dijkstra.md) · [bfs-state.md](bfs-state.md) · [08 Graf](README.md)
