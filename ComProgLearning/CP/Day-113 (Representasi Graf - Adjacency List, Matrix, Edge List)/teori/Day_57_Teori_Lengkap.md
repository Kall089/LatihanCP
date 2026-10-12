# Day 57 — Graph Representation: Teori Lengkap

## 1. Apa itu Graph?

**Graph** adalah struktur data yang terdiri dari:
- **V** (Vertices / Nodes) — kumpulan titik
- **E** (Edges) — kumpulan sambungan antar titik

Notasi: G = (V, E)

### Jenis-jenis Graph

| Jenis | Keterangan | Contoh |
|-------|-----------|--------|
| **Undirected** | Edge tidak punya arah, u-v = v-u | Jalan 2 arah |
| **Directed (Digraph)** | Edge punya arah, u→v ≠ v→u | Jalan 1 arah |
| **Weighted** | Setiap edge punya bobot | Peta jarak kota |
| **Unweighted** | Semua edge dianggap cost 1 | Jaringan pertemanan |
| **Simple** | Tanpa self-loop dan multi-edge | Kebanyakan soal CP |
| **Dense** | E ≈ V² | Graph complete |
| **Sparse** | E << V² | Kebanyakan soal CP |
| **Tree** | Graph connected tanpa cycle dengan V-1 edge | Struktur hierarki |
| **DAG** | Directed Acyclic Graph | Dependency graph |

---

## 2. Adjacency List

**Ide**: Tiap node menyimpan daftar tetangganya.

```cpp
// Unweighted, undirected
vector<vector<int>> adj(n + 1);

// Weighted, undirected: adj[u] = {(v, w), ...}
vector<vector<pair<int,int>>> adj(n + 1);

// Tambah edge undirected weighted
adj[u].push_back({v, w});
adj[v].push_back({u, w});

// Tambah edge directed
adj[u].push_back({v, w});  // hanya satu arah
```

### Contoh Graph dan Adjacency List-nya

```
Graph (undirected, weighted):
  1 --3-- 2
  |       |
  5       2
  |       |
  3 --1-- 4

Adjacency List:
  adj[1] = {(2,3), (3,5)}
  adj[2] = {(1,3), (4,2)}
  adj[3] = {(1,5), (4,1)}
  adj[4] = {(2,2), (3,1)}
```

### Cara Baca dari Input

```cpp
int n, m;
cin >> n >> m;

vector<vector<pair<int,int>>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});  // hapus untuk directed
}

// Iterasi tetangga node u:
for (auto [v, w] : adj[u]) {
    // proses edge u→v dengan berat w
}
```

### Kompleksitas

| Operasi | Kompleksitas |
|---------|-------------|
| Tambah edge | O(1) amortized |
| Cek apakah edge(u,v) ada | O(degree(u)) |
| Iterasi tetangga u | O(degree(u)) |
| Memori | O(V + E) |

### Kapan Pakai?

✓ Graph **sparse** (kebanyakan soal CP): E << V²
✓ Algoritma yang perlu iterasi tetangga: BFS, DFS, Dijkstra, Bellman-Ford, dll.
✓ V besar (sampai 10^5 atau lebih)

---

## 3. Adjacency Matrix

**Ide**: Matrix 2D di mana `mat[u][v]` menyimpan bobot edge u→v (atau 0/INF jika tidak ada).

```cpp
int n;
vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
// atau untuk weighted: isi INF sebagai "tidak ada edge"
const int INF = 1e9;
vector<vector<int>> mat(n + 1, vector<int>(n + 1, INF));
for (int i = 0; i <= n; i++) mat[i][i] = 0;  // diagonal = 0

// Tambah edge (u,v) dengan berat w:
mat[u][v] = w;
mat[v][u] = w;  // hapus untuk directed

// Cek apakah ada edge u→v:
if (mat[u][v] != INF) { /* ada edge */ }
```

### Contoh

```
Graph (directed, unweighted):
  1→2, 1→3, 2→4, 3→4

Adjacency Matrix (1-indexed, 0 = tidak ada, 1 = ada):
      1  2  3  4
  1 [ 0  1  1  0 ]
  2 [ 0  0  0  1 ]
  3 [ 0  0  0  1 ]
  4 [ 0  0  0  0 ]
```

### Kompleksitas

| Operasi | Kompleksitas |
|---------|-------------|
| Tambah edge | O(1) |
| Cek edge(u,v) | O(1) |
| Iterasi tetangga u | O(V) |
| Memori | O(V²) |

### Kapan Pakai?

✓ Graph **dense** atau V **kecil** (V ≤ 1000)
✓ Perlu cek edge(u,v) dalam O(1)
✓ Floyd-Warshall (all-pairs shortest path): O(V³)
✗ JANGAN jika V = 10^5: memori V² = 10^10 bytes → MLE!

---

## 4. Edge List

**Ide**: Simpan semua edge dalam satu array/vector sebagai pasangan (atau tuple) node.

```cpp
// Unweighted, directed:
vector<pair<int,int>> edges;  // {u, v}
edges.push_back({u, v});

// Weighted:
vector<tuple<int,int,int>> edges;  // {w, u, v} atau {u, v, w}
edges.push_back({w, u, v});

// Sort berdasarkan weight (untuk Kruskal):
sort(edges.begin(), edges.end());  // sort berdasarkan field pertama (w)
```

### Contoh

```
Graph (undirected, weighted):
  1-2 (w=3), 1-3 (w=5), 2-4 (w=2), 3-4 (w=1)

Edge List:
  {(3,1,2), (5,1,3), (2,2,4), (1,3,4)}

Setelah sort berdasarkan weight:
  {(1,3,4), (2,2,4), (3,1,2), (5,1,3)}
```

### Kompleksitas

| Operasi | Kompleksitas |
|---------|-------------|
| Tambah edge | O(1) |
| Sort edges | O(E log E) |
| Iterasi semua edge | O(E) |
| Cek edge(u,v) | O(E) |
| Memori | O(E) |

### Kapan Pakai?

✓ Algoritma yang butuh edge ter-sort: **Kruskal MST**
✓ Bellman-Ford (iterasi semua edge E kali)
✓ Saat hanya perlu iterasi semua edge, bukan tetangga spesifik
✗ JANGAN jika perlu cek tetangga spesifik: gunakan adj list

---

## 5. Perbandingan Lengkap

```
┌─────────────────┬────────────┬─────────────┬─────────────┐
│ Operasi         │ Adj. List  │ Adj. Matrix │ Edge List   │
├─────────────────┼────────────┼─────────────┼─────────────┤
│ Tambah edge     │ O(1)       │ O(1)        │ O(1)        │
│ Cek edge (u,v)  │ O(deg(u))  │ O(1)        │ O(E)        │
│ Iterasi tetangga│ O(deg(u))  │ O(V)        │ O(E)        │
│ Iterasi semua   │ O(V+E)     │ O(V²)       │ O(E)        │
│ Memori          │ O(V+E)     │ O(V²)       │ O(E)        │
├─────────────────┼────────────┼─────────────┼─────────────┤
│ BFS / DFS       │ ✓✓ Terbaik │ ✓ Bisa      │ ✗ Tidak     │
│ Dijkstra        │ ✓✓ Terbaik │ ✓ Bisa      │ ✗ Tidak     │
│ Floyd-Warshall  │ ✗ Lambat   │ ✓✓ Terbaik  │ ✗ Tidak     │
│ Kruskal MST     │ ✗ Tidak    │ ✗ Tidak     │ ✓✓ Terbaik  │
│ Bellman-Ford    │ ✓ Bisa     │ ✓ Bisa      │ ✓✓ Terbaik  │
└─────────────────┴────────────┴─────────────┴─────────────┘
```

---

## 6. Properti Dasar Graph

### Degree

```cpp
// Undirected graph:
// degree(u) = jumlah tetangga u
int degree_u = adj[u].size();  // adjacency list
int degree_u = 0;
for (int v = 1; v <= n; v++) if (mat[u][v]) degree_u++;  // adj matrix

// Directed graph:
// out-degree(u) = jumlah edge keluar
int out_deg = adj[u].size();
// in-degree(u) = dihitung terpisah
vector<int> in_deg(n + 1, 0);
for (int u = 1; u <= n; u++)
    for (auto [v, w] : adj[u])
        in_deg[v]++;

// Handshaking Lemma: sum degree = 2 × E (undirected)
```

### Graph Properties

```cpp
// Cek simple graph (tidak ada self-loop, tidak ada multi-edge):
// Self-loop: edge dari u ke u sendiri
// Multi-edge: lebih dari satu edge antara u dan v

// Cek apakah node u terisolasi (tidak punya tetangga):
bool isolated = adj[u].empty();

// Hitung jumlah edge (undirected):
int total_edges = 0;
for (int u = 1; u <= n; u++) total_edges += adj[u].size();
total_edges /= 2;  // setiap edge dihitung 2x
```

---

## 7. Konversi Antar Representasi

### Adjacency List → Adjacency Matrix

```cpp
int n;
vector<vector<pair<int,int>>> adj(n + 1);
// ... isi adj ...

// Konversi ke matrix
const int INF = 1e9;
vector<vector<int>> mat(n + 1, vector<int>(n + 1, INF));
for (int u = 0; u <= n; u++) mat[u][u] = 0;

for (int u = 1; u <= n; u++)
    for (auto [v, w] : adj[u])
        mat[u][v] = min(mat[u][v], w);  // min untuk multi-edge
```

### Adjacency List → Edge List

```cpp
vector<tuple<int,int,int>> edges;  // {w, u, v}
for (int u = 1; u <= n; u++)
    for (auto [v, w] : adj[u])
        if (u < v)  // untuk undirected: hindari duplikat
            edges.push_back({w, u, v});

sort(edges.begin(), edges.end());
```

### Edge List → Adjacency List

```cpp
vector<vector<pair<int,int>>> adj(n + 1);
for (auto [w, u, v] : edges) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});  // hapus untuk directed
}
```

---

## 8. Contoh Lengkap — Baca & Tampilkan Graph

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Adjacency List (weighted, undirected)
    vector<vector<pair<int,int>>> adj(n + 1);
    vector<tuple<int,int,int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({w, u, v});
    }

    // Cetak adjacency list
    cout << "=== Adjacency List ===\n";
    for (int u = 1; u <= n; u++) {
        cout << u << ": ";
        for (auto [v, w] : adj[u])
            cout << "(" << v << "," << w << ") ";
        cout << "\n";
    }

    // Cetak degree
    cout << "\n=== Degree ===\n";
    for (int u = 1; u <= n; u++)
        cout << "deg(" << u << ") = " << adj[u].size() << "\n";

    // Sort edge list by weight
    sort(edges.begin(), edges.end());
    cout << "\n=== Edge List (sorted by weight) ===\n";
    for (auto [w, u, v] : edges)
        cout << u << " - " << v << " (w=" << w << ")\n";

    return 0;
}
```

---

## 9. Common Pitfalls & Tips

### Pitfalls

**1. Lupa inisialisasi ukuran adjacency list**
```cpp
// SALAH: adj tidak di-resize, akan segfault saat adj[u] diakses
vector<vector<int>> adj;

// BENAR:
vector<vector<int>> adj(n + 1);  // n+1 karena 1-indexed
```

**2. Off-by-one: 0-indexed vs 1-indexed**
```cpp
// Soal CP biasanya node 1..n (1-indexed)
// Pastikan ukuran adj = n+1, bukan n
vector<vector<int>> adj(n + 1);  // index 0 diabaikan
```

**3. Lupa kedua arah untuk undirected graph**
```cpp
// SALAH (jadi directed):
adj[u].push_back(v);

// BENAR (undirected):
adj[u].push_back(v);
adj[v].push_back(u);
```

**4. Adjacency matrix terlalu besar**
```cpp
// SALAH jika n = 10^5:
int mat[100001][100001];  // 10^10 bytes = 10 GB → MLE!

// BENAR: gunakan adj list untuk n besar
```

### Pro Tips

**Tip 1: Gunakan struct untuk graph yang kompleks**
```cpp
struct Edge {
    int to, weight, id;  // id berguna untuk Euler path dll.
};
vector<Edge> adj[MAXN];
```

**Tip 2: Implicit graph (grid)**
```cpp
// Grid n×m bisa diperlakukan sebagai graph tanpa membangun adj list eksplisit
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
// Cek tetangga (x,y):
for (int d = 0; d < 4; d++) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        // proses tetangga (nx, ny)
    }
}
```

**Tip 3: Kompres node jika nilai node besar**
```cpp
// Jika node bernilai 0..10^9, kompres ke 0..k-1
map<int,int> compress;
int idx = 0;
for (int v : all_nodes) compress[v] = idx++;
```

---

## Ringkasan

| Representasi | Memori | Pilihan Terbaik Untuk |
|-------------|--------|----------------------|
| Adjacency List | O(V+E) | BFS, DFS, Dijkstra — graph sparse |
| Adjacency Matrix | O(V²) | Floyd-Warshall — graph dense/kecil |
| Edge List | O(E) | Kruskal MST, Bellman-Ford |
