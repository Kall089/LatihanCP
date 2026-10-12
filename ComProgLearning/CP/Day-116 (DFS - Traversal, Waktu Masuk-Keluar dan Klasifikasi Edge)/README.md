# Day 59 — DFS (Depth-First Search)

## Deskripsi Topik

**DFS (Depth-First Search)** menjelajahi graph dengan masuk **sedalam mungkin** di satu cabang sebelum mundur (*backtrack*) dan mencoba cabang lain. Kontras dengan BFS (Day 58) yang menyebar merata lapis demi lapis.

Analogi: menjelajahi labirin dengan segulung benang — jalan terus sampai buntu, lalu ikuti benang mundur ke persimpangan terakhir yang belum tuntas. Benang itu adalah **call stack** rekursi.

DFS adalah fondasi untuk hampir seluruh Bulan 3:
- **Connected components** — berapa kelompok terpisah?
- **Cycle detection** — undirected (cek parent) dan directed (3-color)
- **Topological sort** — urutan yang menghormati semua prasyarat
- **Discovery/finish time** — fondasi bridges (Day 73), SCC (Day 74), LCA (Day 47)

⚠️ **DFS TIDAK menjamin jalur terpendek.** Kalau soal menyebut "minimal langkah" atau "jarak terpendek", pakai BFS.

---

## Tujuan Pembelajaran

- [ ] Memahami cara kerja DFS dan bedanya dengan BFS (stack vs queue)
- [ ] Mengimplementasikan DFS **rekursif** dan **iteratif** (stack eksplisit)
- [ ] Menghitung **connected components** dan ukurannya
- [ ] Mendeteksi cycle pada graph **tak berarah** dengan cek parent
- [ ] Mendeteksi cycle pada graph **berarah** dengan 3-color
- [ ] Memahami **kenapa cek parent gagal** pada graph berarah
- [ ] Menghasilkan **topological sort** lewat post-order + reverse
- [ ] Menggunakan **discovery/finish time** untuk cek ancestor O(1)
- [ ] Menerapkan DFS pada **grid** (flood fill)
- [ ] Mengenali dan menghindari **stack overflow** pada graph dalam

---

## Struktur Folder

```
Day-59 (DFS)/
├── README.md                       ← Panduan ini
├── teori/
│   └── Day_59_Teori_Lengkap.md    ← Teori lengkap + trace table
├── latihan/
│   ├── exercise_1.cpp             ← DFS Dasar (urutan kunjungan)
│   ├── exercise_2.cpp             ← Connected Components
│   ├── exercise_3.cpp             ← Cycle Detection (tak berarah)
│   ├── exercise_4.cpp             ← Cycle Detection (berarah, 3-color)
│   ├── exercise_5.cpp             ← Topological Sort
│   └── exercise_6.cpp             ← DFS Iteratif (anti stack overflow)
├── solusi/
│   └── solution_1.cpp — solution_6.cpp
├── tugas/
│   └── tugas_01.cpp — tugas_15.cpp    ← 15 tugas mandiri (tanpa solusi)
└── template/
    └── template.cpp               ← 11 pola DFS siap pakai
```

---

## Prerequisites

| Hari | Topik | Kenapa dibutuhkan |
|------|-------|-------------------|
| Day 57 | Graph representation | Adjacency list adalah struktur dasarnya |
| Day 58 | BFS | Perbandingan langsung — kapan pakai yang mana |
| Day 11 | Rekursi | DFS rekursif memakai call stack |
| Day 5 | Stack | DFS iteratif memakai stack eksplisit |

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45–60 menit)
Baca `teori/Day_59_Teori_Lengkap.md`. Yang wajib benar-benar dipahami:
- Trace DFS langkah demi langkah dengan call stack
- Trace 3-color pada dua kasus: yang bersiklus DAN yang tidak (bagian ini
  menjelaskan kenapa "sudah dikunjungi" tidak cukup untuk graph berarah)
- Kenapa post-order harus dibalik untuk topological sort

### Langkah 2 — Kerjakan Latihan (90–120 menit)
Kerjakan exercise 1–6 **tanpa melihat solusi**. Urutannya progresif:
DFS dasar → komponen → cycle undirected → cycle directed → topo sort → iteratif.

### Langkah 3 — Cek Solusi
```bash
g++ -std=c++17 -O2 -Wall -o sol solusi/solution_4.cpp
./sol < input.txt
```
Semua solusi sudah dikompilasi dan diverifikasi terhadap sample I/O.

### Langkah 4 — Kerjakan Tugas (150–180 menit)
- Easy: tugas_01–05 (**semua** harus dikerjakan)
- Medium: pilih minimal 3 dari tugas_06–10
- Hard: pilih minimal 2 dari tugas_11–15

### Langkah 5 — Online Judge
Mulai dari CSES 1666 (Building Roads) — itu tugas_14 dalam bentuk aslinya.

---

## Ringkasan Latihan

| No | File | Topik | Kesulitan | Konsep Kunci |
|----|------|-------|-----------|--------------|
| 1 | exercise_1.cpp | DFS Dasar | ★☆☆☆☆ | Rekursi + visited |
| 2 | exercise_2.cpp | Connected Components | ★★☆☆☆ | Loop semua node sebagai start |
| 3 | exercise_3.cpp | Cycle Undirected | ★★★☆☆ | Cek parent |
| 4 | exercise_4.cpp | Cycle Directed | ★★★★☆ | 3-color / recursion stack |
| 5 | exercise_5.cpp | Topological Sort | ★★★★☆ | Post-order + reverse |
| 6 | exercise_6.cpp | DFS Iteratif | ★★★☆☆ | Stack eksplisit, cek saat pop |

---

## Ringkasan Tugas (15 Soal)

| No | Topik | Kesulitan | Kategori |
|----|-------|-----------|----------|
| 01 | Cek Keterhubungan Dua Node | ★☆☆☆☆ | Easy |
| 02 | Ukuran Setiap Component | ★☆☆☆☆ | Easy |
| 03 | Menghitung Pulau di Grid | ★★☆☆☆ | Easy |
| 04 | Apakah Graph Ini Pohon? | ★★☆☆☆ | Easy |
| 05 | Ukuran Subtree Setiap Node | ★★☆☆☆ | Easy |
| 06 | Bipartite Check (2-coloring) | ★★★☆☆ | Medium |
| 07 | Rekonstruksi Jalur | ★★★☆☆ | Medium |
| 08 | Course Schedule (topo sort) | ★★★☆☆ | Medium |
| 09 | Area Terbesar di Grid | ★★★☆☆ | Medium |
| 10 | Discovery/Finish Time (ancestor O(1)) | ★★★★☆ | Medium |
| 11 | Rekonstruksi Cycle Berarah | ★★★★☆ | Hard |
| 12 | Jalur Terpanjang pada DAG | ★★★★☆ | Hard |
| 13 | Diameter Pohon (double DFS) | ★★★★☆ | Hard |
| 14 | Edge Minimum agar Terhubung | ★★★★☆ | Hard |
| 15 | Cycle di Grid (panjang ≥ 4) | ★★★★★ | Hard |

---

## DFS vs BFS — Tabel Keputusan

| Kebutuhan | Pilih |
|-----------|-------|
| Shortest path pada graph **unweighted** | **BFS** |
| Connected components | Keduanya (DFS lebih ringkas) |
| Deteksi cycle | **DFS** |
| Topological sort | DFS (post-order) atau Kahn/BFS (Day 60) |
| Ada/tidaknya path | Keduanya |
| Subtree size, tree DP | **DFS** |
| Bridges, articulation points, SCC | **DFS** (butuh tin/tout) |
| Backtracking / enumerasi | **DFS** |
| Level / jarak dari sumber | **BFS** |
| Graph sangat dalam (~10⁶) | **BFS** atau DFS iteratif |

---

## Rekomendasi Online Judge

### CSES (cses.fi/problemset)
| Problem | Judul | Terkait |
|---------|-------|---------|
| 1666 | Building Roads | tugas_14 |
| 1192 | Counting Rooms | tugas_03 |
| 1669 | Round Trip (undirected) | exercise_3 |
| 1678 | Round Trip II (directed) | tugas_11 |
| 1679 | Course Schedule | exercise_5, tugas_08 |
| 1682 | Flight Routes Check | SCC preview |
| 1668 | Building Teams | tugas_06 (bipartite) |

### LeetCode
| Problem | Judul |
|---------|-------|
| 200 | Number of Islands |
| 695 | Max Area of Island |
| 547 | Number of Provinces |
| 207 | Course Schedule |
| 210 | Course Schedule II |
| 785 | Is Graph Bipartite? |
| 802 | Find Eventual Safe States |

### Codeforces
| Problem | Judul | Rating |
|---------|-------|--------|
| 510B | Fox And Two Dots | 1500 (= tugas_15) |
| 977E | Cyclic Components | 1500 |
| 580C | Kefa and Park | 1500 |
| 115A | Party | 900 |

### AtCoder
| Problem | Judul |
|---------|-------|
| ATC 001 A | Depth First Search |
| ABC 138 D | Ki (tree DFS) |
| ABC 168 D | .. (Double Dots) |

---

## Kesalahan Umum (Common Mistakes)

1. **Lupa `visited[u] = true` di awal fungsi.** Kalau ditandai setelah loop, node yang sama masuk berkali-kali pada graph bersiklus → infinite recursion → crash. Ini bug DFS nomor satu.

2. **Hanya `dfs(1)` untuk graph yang tidak dijamin terhubung.** Node di komponen lain tidak akan pernah tersentuh. Selalu `for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);`

3. **Memakai cek parent pada graph BERARAH.** Contoh `1→2, 1→3, 2→3` akan salah dilaporkan sebagai cycle. Graph berarah butuh 3-color.

4. **Lupa `reverse()` pada topological sort.** Post-order menghasilkan urutan terbalik dari yang benar.

5. **Stack overflow pada graph dalam.** Rekursi kedalaman 10⁶ pada stack default (~8 MB) akan crash. Solusi: DFS iteratif, atau BFS.

6. **Undirected graph hanya di-push satu arah.** Harus `adj[u].push_back(v)` DAN `adj[v].push_back(u)`.

7. **DFS iteratif lupa cek `visited` saat pop.** Node bisa masuk stack lebih dari sekali sebelum sempat ditandai — kalau tidak di-skip, ia diproses berulang.

8. **Tidak reset `visited` pada multi test case.** Sisa data test case sebelumnya merusak jawaban. Reset hanya sebanyak `n` yang dipakai, jangan `memset` seluruh MAXN tiap test case (bisa TLE).

9. **Memakai DFS untuk shortest path.** DFS menemukan *sebuah* jalur, bukan yang terpendek.

10. **1-indexed vs 0-indexed tertukar.** Node 0 terlewat atau `visited[n]` di luar batas.

---

## Quick Reference Cheatsheet

```cpp
// --- DFS DASAR ---
void dfs(int u) {
    visited[u] = true;                          // TANDAI DI AWAL
    for (int v : adj[u]) if (!visited[v]) dfs(v);
}

// --- CONNECTED COMPONENTS ---
int comp = 0;
for (int i = 1; i <= n; i++)
    if (!visited[i]) { comp++; dfs(i); }

// --- CYCLE UNDIRECTED (cek parent) ---
bool cyc(int u, int p) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) { if (cyc(v, u)) return true; }
        else if (v != p) return true;           // back edge
    }
    return false;
}

// --- CYCLE DIRECTED (3-color) ---
// 0 = WHITE (belum), 1 = GRAY (di recursion stack), 2 = BLACK (selesai)
bool cycD(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return true;         // GRAY → CYCLE
        if (color[v] == 0 && cycD(v)) return true;
    }
    color[u] = 2;
    return false;
}

// --- TOPOLOGICAL SORT ---
void dfsT(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfsT(v);
    topo.push_back(u);                          // POST-ORDER
}
reverse(topo.begin(), topo.end());              // WAJIB

// --- DFS ITERATIF ---
st.push(start);
while (!st.empty()) {
    int u = st.top(); st.pop();
    if (visited[u]) continue;                   // WAJIB
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) st.push(v);
}

// --- GRID 4-ARAH ---
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};

// --- DISCOVERY / FINISH TIME ---
// isAncestor(u,v) ⟺ tin[u] <= tin[v] && tout[v] <= tout[u]
```

### Kompleksitas

```
Adjacency List  : Time O(V + E)  |  Space O(V + E) + O(V) call stack
Adjacency Matrix: Time O(V²)     |  Space O(V²)

Aman untuk V + E sampai ~10^6.
Kedalaman rekursi > ~10^6 → stack overflow, pakai iteratif.
```

---

## Checklist Sebelum Lanjut ke Day 60

- [ ] Bisa menulis DFS rekursif dari ingatan tanpa contoh
- [ ] Bisa menjelaskan kenapa cek parent gagal pada graph berarah
- [ ] Bisa menjelaskan kenapa post-order harus dibalik
- [ ] Tahu kapan harus pakai DFS iteratif alih-alih rekursif
- [ ] Bisa memutuskan DFS vs BFS hanya dari membaca soal
- [ ] Sudah menyelesaikan minimal 10 dari 15 tugas
- [ ] Sudah AC minimal 2 soal DFS di online judge
- [ ] `template/template.cpp` sudah disimpan untuk dipakai hari berikutnya

---

## Preview Day 60 — Topological Sort (Kahn's Algorithm)

Besok: topological sort dengan pendekatan **BFS + in-degree**, alternatif dari DFS post-order yang kita pelajari hari ini.

Koneksi ke hari ini:
- Kahn mendeteksi cycle secara alami — kalau node terproses < N, ada cycle
- Kahn bebas risiko stack overflow (iteratif secara inheren)
- Dengan `priority_queue`, Kahn bisa menghasilkan urutan **lexicographically smallest** — sesuatu yang tidak bisa dijamin DFS

Setelah Day 60, kamu akan punya dua cara menyelesaikan masalah yang sama, dan tahu kapan memilih yang mana.
