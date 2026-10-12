# Day 57 — Graph Representation

## Tujuan Pembelajaran

Setelah menyelesaikan Day 57, kamu akan mampu:

- [ ] Memahami konsep graph: node, edge, directed/undirected, weighted/unweighted
- [ ] Mengimplementasikan **Adjacency List** menggunakan `vector<vector<pair<int,int>>>`
- [ ] Mengimplementasikan **Adjacency Matrix** dan tahu kapan memakainya
- [ ] Mengimplementasikan **Edge List** dan tahu kapan memakainya
- [ ] Menghitung degree, in-degree, dan out-degree node
- [ ] Membaca graph dari input standar CP dalam berbagai format
- [ ] Memilih representasi yang tepat berdasarkan constraint soal

---

## Struktur Folder

```
Day-57 (Graph Representation)/
├── README.md               ← Panduan ini
├── teori/
│   ├── Day_57_Teori_Lengkap.md     ← Teori lengkap (Markdown)
│   ├── generate_presentation.py    ← Script generate PPT
│   └── Day_57_Presentation.pptx   ← PPT (setelah script dijalankan)
├── latihan/
│   ├── exercise_1.cpp   (Warm-up : Baca & Print Adjacency List)
│   ├── exercise_2.cpp   (Core    : Konversi antar representasi)
│   ├── exercise_3.cpp   (Core    : Degree sequence & properti dasar)
│   ├── exercise_4.cpp   (Challenge: Adjacency Matrix Operations)
│   ├── exercise_5.cpp   (Challenge: Edge List + Sorting)
│   └── exercise_6.cpp   (Contest : Graph dari input format CP nyata)
├── solusi/
│   ├── solution_1.cpp   through   solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Starter template dengan semua 3 representasi
```

---

## Panduan Belajar

### Langkah 1 — Lihat Presentasi
```bash
cd teori/
python3 generate_presentation.py   # Generate Day_57_Presentation.pptx
```

### Langkah 2 — Baca Teori Lengkap
Buka `teori/Day_57_Teori_Lengkap.md` untuk teori detail.

### Langkah 3 — Kerjakan Latihan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1
```

### Langkah 4 — Cek Solusi (jika stuck > 30 menit)

### Langkah 5 — Kerjakan 15 Tugas Mandiri

---

## Quick Reference — Kapan Pakai Apa?

```
┌──────────────────┬───────────────────┬─────────────────────┐
│ Representasi     │ Memori            │ Waktu Akses Edge    │
├──────────────────┼───────────────────┼─────────────────────┤
│ Adjacency List   │ O(V + E)          │ O(degree(u))        │
│ Adjacency Matrix │ O(V²)             │ O(1) cek edge(u,v)  │
│ Edge List        │ O(E)              │ O(E) cari edge(u,v) │
└──────────────────┴───────────────────┴─────────────────────┘

PAKAI Adjacency List jika:
  ✓ Graph sparse (E << V²): kebanyakan soal CP
  ✓ Perlu iterasi tetangga: BFS, DFS, Dijkstra, dll.
  ✓ V sampai 10^5 atau lebih

PAKAI Adjacency Matrix jika:
  ✓ Graph dense (E ≈ V²) dan V kecil (V ≤ 1000)
  ✓ Perlu cek edge(u,v) dalam O(1)
  ✓ Floyd-Warshall (all-pairs shortest path)

PAKAI Edge List jika:
  ✓ Perlu sort edge berdasarkan bobot: Kruskal MST
  ✓ Hanya perlu iterasi semua edge, bukan tetangga spesifik
  ✓ Bellman-Ford
```

---

## Terminologi Graph

| Istilah | Definisi |
|---------|---------|
| **Node / Vertex (V)** | Titik dalam graph |
| **Edge (E)** | Sambungan antara dua node |
| **Directed / Digraph** | Edge punya arah (u→v ≠ v→u) |
| **Undirected** | Edge tidak berarah (u-v = v-u) |
| **Weighted** | Setiap edge punya bobot/cost |
| **Degree(u)** | Jumlah edge yang menyentuh u (undirected) |
| **In-degree(u)** | Jumlah edge masuk ke u (directed) |
| **Out-degree(u)** | Jumlah edge keluar dari u (directed) |
| **Simple graph** | Tidak ada self-loop atau multi-edge |
| **Dense graph** | E ≈ V² |
| **Sparse graph** | E << V² (kebanyakan soal CP) |

---

## Cara Baca Input Graph (Format CP)

```cpp
// Format 1: n node, m edge, undirected unweighted
int n, m;
cin >> n >> m;
vector<vector<int>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Format 2: n node, m edge, directed weighted
vector<vector<pair<int,int>>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});  // hanya satu arah
}

// Format 3: adjacency matrix (n×n)
vector<vector<int>> mat(n + 1, vector<int>(n + 1, 0));
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        cin >> mat[i][j];
```

---

## Soal Online Judge

### CSES Problem Set
- [Building Roads](https://cses.fi/problemset/task/1666) — graph dasar (BFS/DFS)
- [Message Route](https://cses.fi/problemset/task/1667) — BFS shortest path
- [Counting Rooms](https://cses.fi/problemset/task/1192) — connected components grid

### Codeforces
- [CF 263A — Beautiful Matrix](https://codeforces.com/problemset/problem/263/A)
- [CF 580C — Kefa and Park](https://codeforces.com/problemset/problem/580/C) — tree traversal

### LeetCode
- [133. Clone Graph](https://leetcode.com/problems/clone-graph/)
- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)

---

## Checklist Penyelesaian

- [ ] Menonton/membaca semua materi teori
- [ ] Menyelesaikan exercise_1 (baca & print adjacency list)
- [ ] Menyelesaikan exercise_2 (konversi representasi)
- [ ] Menyelesaikan exercise_3 (degree sequence)
- [ ] Menyelesaikan exercise_4 (adjacency matrix ops)
- [ ] Menyelesaikan exercise_5 (edge list + sort)
- [ ] Mencoba exercise_6 (input format CP nyata)
- [ ] Mengerjakan minimal 10 dari 15 tugas
- [ ] Mencoba minimal 1 soal online judge
