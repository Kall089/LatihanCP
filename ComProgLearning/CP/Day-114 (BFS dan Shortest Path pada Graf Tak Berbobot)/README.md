# Day 58 — BFS (Breadth-First Search)

## Tujuan Pembelajaran

Setelah menyelesaikan Day 58, kamu akan mampu:

- [ ] Mengimplementasikan BFS menggunakan **queue** (FIFO)
- [ ] Melakukan **level-order traversal** pada graph dan tree
- [ ] Menemukan **shortest path pada unweighted graph** dengan BFS
- [ ] Mengaplikasikan BFS pada **grid** (4-arah dan 8-arah)
- [ ] Mengimplementasikan **Multi-source BFS** (banyak titik awal sekaligus)
- [ ] Memahami **kompleksitas O(V+E)** dan kapan BFS lebih unggul dari DFS
- [ ] Menyelesaikan soal 0-1 BFS menggunakan **deque**

---

## Struktur Folder

```
Day-58 (BFS)/
├── README.md               ← Panduan ini
├── teori/
│   ├── Day_58_Teori_Lengkap.md     ← Teori lengkap (Markdown)
│   ├── generate_presentation.py    ← Script generate PPT
│   └── Day_58_Presentation.pptx   ← PPT (setelah script dijalankan)
├── latihan/
│   ├── exercise_1.cpp   (Warm-up : BFS dasar, kunjungi semua node)
│   ├── exercise_2.cpp   (Core    : BFS shortest path unweighted)
│   ├── exercise_3.cpp   (Core    : BFS pada grid, hitung langkah ke tujuan)
│   ├── exercise_4.cpp   (Challenge: Multi-source BFS)
│   ├── exercise_5.cpp   (Challenge: BFS level-order tree traversal)
│   └── exercise_6.cpp   (Contest : 0-1 BFS dengan deque)
├── solusi/
│   └── solution_1-6.cpp   ← Solusi lengkap semua exercise
├── tugas/
│   ├── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Starter template BFS lengkap
```

---

## Panduan Belajar

### Langkah 1 — Lihat Presentasi
```bash
cd teori/
python3 generate_presentation.py   # Generate Day_58_Presentation.pptx
```

### Langkah 2 — Baca Teori Lengkap
Buka `teori/Day_58_Teori_Lengkap.md` untuk teori detail.

### Langkah 3 — Kerjakan Latihan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1
```

### Langkah 4 — Cek Solusi (jika stuck > 30 menit)

### Langkah 5 — Kerjakan 15 Tugas Mandiri

---

## Quick Reference — BFS Cheatsheet

```
BFS (Breadth-First Search):
  • Struktur data: Queue (FIFO)
  • Traversal: level per level (level-order)
  • Jarak: dist[node] = jumlah edge dari source
  • Kompleksitas: O(V + E)

Template dasar BFS:
┌─────────────────────────────────────────────────────────────┐
│  queue<int> q;                                              │
│  vector<int> dist(n+1, -1);                                 │
│  dist[src] = 0;                                             │
│  q.push(src);                                               │
│  while (!q.empty()) {                                        │
│      int u = q.front(); q.pop();                             │
│      for (int v : adj[u]) {                                  │
│          if (dist[v] == -1) {                                │
│              dist[v] = dist[u] + 1;                          │
│              q.push(v);                                      │
│          }                                                   │
│      }                                                       │
│  }                                                           │
└─────────────────────────────────────────────────────────────┘

PAKAI BFS jika:
  ✓ Ingin shortest path pada UNWEIGHTED graph
  ✓ Perlu traversal level per level
  ✓ Multi-source: mulai dari banyak titik sekaligus
  ✓ Grid BFS: temukan jarak terpendek di maze

PAKAI DFS jika:
  ✓ Deteksi cycle
  ✓ Topological sort
  ✓ Backtracking
  ✗ JANGAN DFS untuk shortest path (bisa salah!)
```

---

## Terminologi BFS

| Istilah | Definisi |
|---------|---------|
| **Source / Sumber** | Node awal BFS dimulai |
| **Queue** | Struktur FIFO untuk BFS |
| **Visited / dist** | Array penanda node sudah dikunjungi |
| **Level** | Jarak (dalam edge) dari source |
| **BFS Tree** | Pohon yang terbentuk dari edge BFS |
| **Multi-source** | BFS dimulai dari banyak source sekaligus |
| **0-1 BFS** | BFS dengan edge weight 0 atau 1, pakai deque |
| **Connected Component** | Komponen yang terhubung, ditemukan BFS |

---

## Pola BFS Penting

```cpp
// Pola 1: BFS biasa (shortest path unweighted)
queue<int> q;
vector<int> dist(n+1, -1);
dist[src] = 0; q.push(src);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) { dist[v] = dist[u]+1; q.push(v); }
    }
}

// Pola 2: BFS rekonstruksi path
vector<int> prev(n+1, -1);
// ... jalankan BFS, simpan prev[v] = u ...
// Rekonstruksi: trace dari dst ke src lewat prev[]

// Pola 3: Multi-source BFS
queue<int> q;
vector<int> dist(n+1, -1);
for (int src : sources) { dist[src] = 0; q.push(src); }
// ... lanjut BFS biasa ...

// Pola 4: BFS pada grid
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
queue<pair<int,int>> q;
vector<vector<int>> dist(R, vector<int>(C, -1));
dist[sr][sc] = 0; q.push({sr, sc});
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r+dx[d], nc = c+dy[d];
        if (nr>=0&&nr<R&&nc>=0&&nc<C&&dist[nr][nc]==-1) {
            dist[nr][nc] = dist[r][c]+1; q.push({nr,nc});
        }
    }
}
```

---

## Soal Online Judge

### CSES Problem Set
- [Message Route](https://cses.fi/problemset/task/1667) — BFS shortest path + rekonstruksi path
- [Counting Rooms](https://cses.fi/problemset/task/1192) — BFS grid, connected components
- [Labyrinth](https://cses.fi/problemset/task/1193) — BFS grid dengan rekonstruksi path
- [Shortest Routes I](https://cses.fi/problemset/task/1671) — Dijkstra (BFS weighted)

### Codeforces
- [CF 1037D — Valid BFS?](https://codeforces.com/problemset/problem/1037/D) — validasi urutan BFS
- [CF 242C — King's Path](https://codeforces.com/problemset/problem/242/C) — BFS di grid besar (sparse)

### LeetCode
- [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) — Multi-source BFS
- [1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/) — Multi-source BFS

---

## Checklist Penyelesaian

- [ ] Menonton/membaca semua materi teori
- [ ] Menyelesaikan exercise_1 (BFS dasar, kunjungi semua node)
- [ ] Menyelesaikan exercise_2 (BFS shortest path unweighted)
- [ ] Menyelesaikan exercise_3 (BFS pada grid)
- [ ] Menyelesaikan exercise_4 (Multi-source BFS)
- [ ] Menyelesaikan exercise_5 (BFS level-order tree traversal)
- [ ] Mencoba exercise_6 (0-1 BFS dengan deque)
- [ ] Mengerjakan minimal 10 dari 15 tugas
- [ ] Mencoba minimal 1 soal online judge
