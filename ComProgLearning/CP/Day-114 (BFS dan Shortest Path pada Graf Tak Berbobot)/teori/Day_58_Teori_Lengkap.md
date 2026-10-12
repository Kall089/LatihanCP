# Day 58 — BFS (Breadth-First Search): Teori Lengkap

## 1. Apa itu BFS?

**BFS (Breadth-First Search)** adalah algoritma penelusuran graph yang mengunjungi semua node **level per level** — mulai dari source, kunjungi semua tetangga langsung (level 1), lalu tetangga dari tetangga (level 2), dan seterusnya.

### Analogi: Penyebaran Air

Bayangkan kamu meneteskan tinta ke atas kain. Tinta menyebar ke segala arah secara merata — semua titik berjarak 1 terisi dulu, lalu yang berjarak 2, dan seterusnya. Inilah cara kerja BFS.

### Properti Utama BFS

| Properti | Keterangan |
|---------|-----------|
| **Struktur data** | Queue (FIFO) |
| **Traversal** | Level per level (level-order) |
| **Jarak** | `dist[v]` = jumlah edge terpendek dari source ke v |
| **Kompleksitas** | O(V + E) |
| **Shortest path** | Benar untuk **unweighted** graph |

---

## 2. Algoritma BFS — Step by Step

### Pseudocode

```
BFS(graph, source):
    buat array dist[], isi semua dengan -1
    dist[source] = 0
    buat queue Q, masukkan source ke Q

    while Q tidak kosong:
        u = keluarkan dari depan Q (dequeue)
        untuk setiap tetangga v dari u:
            jika dist[v] == -1:   // belum dikunjungi
                dist[v] = dist[u] + 1
                masukkan v ke belakang Q
```

### Implementasi C++

```cpp
#include <bits/stdc++.h>
using namespace std;

// BFS dari source s pada graph dengan n node
// adj[u] = daftar tetangga u (unweighted, undirected)
vector<int> bfs(int s, int n, vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {       // belum dikunjungi
                dist[v] = dist[u] + 1; // jarak = jarak u + 1
                q.push(v);
            }
        }
    }
    return dist;  // dist[v] = -1 jika v tidak terjangkau
}
```

### Trace BFS — Contoh

```
Graph:
  1 -- 2 -- 4
  |         |
  3 --------+

BFS dari node 1:

Langkah 0: queue=[1], dist=[0,-1,-1,-1,-1] (index 0 diabaikan)
Langkah 1: proses 1 → tetangga 2,3 → dist=[0,0,1,1,-1], queue=[2,3]
Langkah 2: proses 2 → tetangga 4 → dist=[0,0,1,1,2], queue=[3,4]
Langkah 3: proses 3 → tetangga 4 sudah dikunjungi → queue=[4]
Langkah 4: proses 4 → tidak ada tetangga baru → queue=[]

Hasil: dist = [-,0,1,1,2]
  Node 1: jarak 0 (source)
  Node 2: jarak 1
  Node 3: jarak 1
  Node 4: jarak 2
```

---

## 3. Shortest Path pada Unweighted Graph

BFS secara otomatis menemukan **shortest path** (jalur terpendek dalam jumlah edge) karena sifat level-order traversal-nya: node yang pertama kali dikunjungi selalu melalui jalur terpendek.

### Implementasi — Shortest Path + Rekonstruksi Path

```cpp
// Kembalikan path terpendek dari src ke dst
// Jika tidak ada path, kembalikan vector kosong
vector<int> shortest_path(int src, int dst, int n,
                           vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);
    vector<int> prev(n + 1, -1);  // simpan parent
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) break;  // sudah sampai tujuan

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prev[v] = u;        // simpan parent v adalah u
                q.push(v);
            }
        }
    }

    if (dist[dst] == -1) return {};  // tidak ada path

    // Rekonstruksi path: trace dari dst ke src
    vector<int> path;
    for (int v = dst; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());  // balik agar src→dst
    return path;
}
```

### Mengapa BFS Menjamin Shortest Path?

**Bukti informal**: BFS mengunjungi node dalam urutan jarak non-decreasing. Ketika kita pertama kali mencapai node v dengan jarak d, tidak mungkin ada cara lain untuk mencapai v dengan jarak < d, karena semua node pada jarak < d sudah diproses lebih dahulu.

---

## 4. BFS pada Grid

Grid (N×M) dapat diperlakukan sebagai graph implisit: setiap sel adalah node, dan edge menghubungkan sel yang berdekatan (4-arah atau 8-arah).

### Template BFS Grid

```cpp
int R, C;
vector<string> grid(R);  // '#' = tembok, '.' = bisa dilalui

// 4-arah: atas, bawah, kiri, kanan
int dx[] = {-1, 1,  0, 0};
int dy[] = { 0, 0, -1, 1};

// BFS dari (sr,sc) ke (er,ec)
int bfs_grid(int sr, int sc, int er, int ec) {
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();

        if (r == er && c == ec) return dist[r][c];

        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d];
            int nc = c + dy[d];
            // Cek batas, bukan tembok, belum dikunjungi
            if (nr >= 0 && nr < R && nc >= 0 && nc < C
                && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1;  // tidak terjangkau
}
```

### Tips Grid BFS

```cpp
// Koordinat (r, c) bisa diencode sebagai integer tunggal:
int encode(int r, int c, int C) { return r * C + c; }

// Pair<int,int> lebih mudah dibaca untuk debugging
// Jika perlu performa: gunakan encode + queue<int>
```

---

## 5. Multi-source BFS

**Ide**: Alih-alih BFS dari satu titik, mulai BFS dari **banyak titik sekaligus** dengan memasukkan semua source ke queue awal dengan dist = 0.

### Kapan Digunakan?

- "Berapa jarak terdekat setiap sel dari **salah satu** sel yang ditandai?"
- "Sebarkan api dari semua titik api secara bersamaan"
- "Jarak dari daratan terdekat untuk setiap laut"

### Implementasi

```cpp
// Multi-source BFS
// sources = daftar semua node awal
vector<int> multi_bfs(vector<int>& sources, int n,
                       vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);
    queue<int> q;

    // Masukkan SEMUA source ke queue dengan dist = 0
    for (int s : sources) {
        dist[s] = 0;
        q.push(s);
    }

    // BFS normal selanjutnya
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}
```

### Contoh: Jarak dari Daratan Terdekat (Grid)

```cpp
// Grid: 1 = daratan, 0 = laut
// Cari jarak terpendek setiap sel laut ke daratan terdekat
int R, C;
vector<vector<int>> grid(R, vector<int>(C));
vector<vector<int>> dist(R, vector<int>(C, -1));
queue<pair<int,int>> q;

// Masukkan semua daratan ke queue
for (int r = 0; r < R; r++)
    for (int c = 0; c < C; c++)
        if (grid[r][c] == 1) {
            dist[r][c] = 0;
            q.push({r, c});
        }

// BFS menyebar dari semua daratan sekaligus
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r+dx[d], nc = c+dy[d];
        if (nr>=0&&nr<R&&nc>=0&&nc<C&&dist[nr][nc]==-1) {
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
}
// dist[r][c] = jarak ke daratan terdekat
```

---

## 6. BFS Level-Order Tree Traversal

Pada tree (atau graph tanpa cycle), BFS menghasilkan **level-order traversal** — kunjungi node level demi level dari root.

### Implementasi

```cpp
// BFS level-order traversal
// Kembalikan array of arrays: result[level] = daftar node di level itu
vector<vector<int>> level_order(int root, int n,
                                 vector<vector<int>>& adj) {
    vector<vector<int>> result;
    vector<bool> visited(n + 1, false);
    queue<int> q;

    visited[root] = true;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();  // jumlah node di level ini
        vector<int> level;

        for (int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            level.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        result.push_back(level);
    }
    return result;
}
```

---

## 7. 0-1 BFS

**0-1 BFS** adalah variasi BFS untuk graph dengan edge weight **hanya 0 atau 1**. Lebih cepat dari Dijkstra (O(V+E) vs O((V+E)logV)).

### Ide Utama

Gunakan **deque** (double-ended queue):
- Edge weight **0**: push ke **depan** deque (tidak menambah level)
- Edge weight **1**: push ke **belakang** deque (menambah level)

```cpp
// adj01[u] = {(v, w)} dengan w ∈ {0, 1}
vector<pair<int,int>> adj01[MAXN];

vector<int> bfs_01(int src, int n) {
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    deque<int> dq;
    dist[src] = 0;
    dq.push_front(src);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();

        for (auto [v, w] : adj01[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);   // edge gratis
                else        dq.push_back(v);     // edge normal
            }
        }
    }
    return dist;
}
```

---

## 8. BFS vs DFS — Kapan Pakai Mana?

```
┌──────────────────────┬─────────────────────┬─────────────────────┐
│ Kasus                │ BFS                 │ DFS                 │
├──────────────────────┼─────────────────────┼─────────────────────┤
│ Shortest path        │ ✓✓ Benar (unweighted│ ✗ SALAH!            │
│ Level-order          │ ✓✓ Natural           │ ✗ Tidak langsung   │
│ Connected components │ ✓ Bisa              │ ✓ Bisa              │
│ Cycle detection      │ ✓ Bisa              │ ✓✓ Lebih mudah      │
│ Topological sort     │ ✓ (Kahn's)          │ ✓✓ Lebih umum       │
│ Bipartite check      │ ✓ Natural           │ ✓ Bisa              │
│ Memori terpakai      │ O(V) — queue        │ O(V) — call stack   │
│ Graf sangat dalam    │ ✓ Aman              │ ✗ Stack overflow    │
└──────────────────────┴─────────────────────┴─────────────────────┘

ATURAN MUDAH:
• Soal minta "jarak terpendek" (unweighted) → BFS
• Soal minta "level ke-berapa" → BFS
• Soal minta "apakah bisa dari A ke B" → BFS atau DFS sama saja
• Soal ada cycle, topological → DFS
```

---

## 9. Kompleksitas BFS

| Operasi | Kompleksitas |
|---------|-------------|
| BFS (graph adj list) | O(V + E) |
| BFS (grid R×C) | O(R × C) |
| Multi-source BFS | O(V + E) |
| 0-1 BFS | O(V + E) |
| Dijkstra (weighted) | O((V+E) log V) |

---

## 10. Common Pitfalls & Tips

### Pitfalls

**1. Lupa tandai visited sebelum push ke queue**
```cpp
// SALAH — bisa push node yang sama berkali-kali → TLE!
for (int v : adj[u]) {
    if (dist[v] == -1) {
        q.push(v);
        // dist[v] belum diset! node lain bisa push v lagi
    }
}

// BENAR — tandai langsung saat push:
for (int v : adj[u]) {
    if (dist[v] == -1) {
        dist[v] = dist[u] + 1;  // tandai dulu
        q.push(v);
    }
}
```

**2. Menggunakan DFS untuk mencari shortest path**
```cpp
// SALAH — DFS tidak menjamin shortest path!
// DFS bisa mengambil jalur panjang terlebih dahulu.
// Selalu gunakan BFS untuk shortest path unweighted.
```

**3. Lupa cek batas pada grid BFS**
```cpp
// SALAH — out of bounds!
int nr = r + dx[d], nc = c + dy[d];
if (grid[nr][nc] != '#') { ... }  // nr, nc bisa negatif atau >= R/C!

// BENAR:
if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') { ... }
```

**4. Multi-source BFS lupa inisialisasi semua source**
```cpp
// SALAH — hanya satu source yang dimasukkan:
dist[sources[0]] = 0; q.push(sources[0]);

// BENAR — semua source dimasukkan dulu:
for (int s : sources) { dist[s] = 0; q.push(s); }
```

### Pro Tips

**Tip 1: Gunakan `dist[v] != -1` sebagai "visited"**
```cpp
// Tidak perlu array visited terpisah.
// dist[v] == -1  ↔  belum dikunjungi
// dist[v] >= 0   ↔  sudah dikunjungi
```

**Tip 2: Early termination jika hanya perlu jarak ke satu tujuan**
```cpp
while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == dst) return dist[dst];  // langsung return
    ...
}
```

**Tip 3: Encode koordinat grid ke integer**
```cpp
// Lebih cepat dari queue<pair<int,int>>
// encode: r*C + c
// decode: r = id/C, c = id%C
queue<int> q;
q.push(sr*C + sc);
while (!q.empty()) {
    int id = q.front(); q.pop();
    int r = id/C, c = id%C;
    ...
}
```

---

## Ringkasan

| Topik | Inti |
|-------|------|
| BFS dasar | Queue + dist array, O(V+E) |
| Shortest path | dist[] otomatis berisi jarak terpendek |
| Rekonstruksi path | Simpan prev[], trace balik dari dst |
| Grid BFS | Sama seperti graph, gunakan dx/dy |
| Multi-source | Masukkan semua source ke queue awal |
| Level-order | Catat ukuran queue tiap level |
| 0-1 BFS | Deque: weight 0 → front, weight 1 → back |
