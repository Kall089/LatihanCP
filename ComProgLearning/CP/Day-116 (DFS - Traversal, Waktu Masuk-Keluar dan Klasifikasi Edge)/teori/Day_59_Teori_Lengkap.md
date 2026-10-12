# 📊 Day 59: DFS (Depth-First Search)

**Hari**: Day 59 dari 150 Hari Competitive Programming
**Topik**: DFS — Connected Components, Cycle Detection, Topological Sort
**Prerequisites**: Graph representation (Day 57), BFS (Day 58), Rekursi (Day 11), Stack (Day 5)
**Difficulty**: ⭐⭐⭐ (Intermediate — fondasi untuk seluruh Bulan 3)
**Learning Objectives**:
- Memahami cara kerja DFS dan perbedaan mendasarnya dengan BFS
- Mengimplementasikan DFS rekursif DAN iteratif (dengan stack eksplisit)
- Menghitung connected components pada graph tak berarah
- Mendeteksi cycle pada graph tak berarah (parent check)
- Mendeteksi cycle pada graph berarah (3-color / recursion stack)
- Menghasilkan topological sort dengan DFS post-order
- Memahami klasifikasi edge (tree, back, forward, cross) dan discovery/finish time
- Menghindari stack overflow pada graph besar

---

## 🔍 1. Konsep & Intuisi

### Apa itu DFS?

**DFS (Depth-First Search)** menjelajahi graph dengan cara **masuk sedalam mungkin** di satu cabang sebelum mundur (*backtrack*) dan mencoba cabang lain.

Kontras dengan BFS yang menyebar merata lapis demi lapis, DFS "menerjang lurus" sampai buntu.

```
Graph:        1
             / \
            2   3
           / \   \
          4   5   6

DFS dari 1:  1 → 2 → 4 → (buntu, mundur) → 5 → (mundur) → 3 → 6
Urutan visit: 1, 2, 4, 5, 3, 6

BFS dari 1:  lapis 0: 1 | lapis 1: 2,3 | lapis 2: 4,5,6
Urutan visit: 1, 2, 3, 4, 5, 6
```

### Analogi: Menjelajahi Labirin

Bayangkan kamu di labirin dengan segulung benang:
- Pilih satu lorong, jalan terus sambil mengulur benang
- Sampai buntu? Ikuti benang mundur ke persimpangan terakhir yang masih punya lorong belum dicoba
- Ulangi sampai semua lorong terjelajahi

Benang itu **call stack** rekursi. Mundur itu **backtracking**.

BFS sebaliknya seperti menuangkan air: menyebar rata ke segala arah sekaligus.

### Kapan Pakai DFS vs BFS?

| Kebutuhan | Pilih |
|-----------|-------|
| Shortest path pada graph **unweighted** | **BFS** |
| Connected components | Keduanya (DFS lebih ringkas) |
| Deteksi cycle | **DFS** |
| Topological sort | **DFS** (post-order) atau Kahn/BFS |
| Ada/tidaknya path antara dua node | Keduanya |
| Subtree size, tree DP | **DFS** |
| Bridges, articulation points, SCC | **DFS** (butuh discovery time) |
| Backtracking / enumerasi solusi | **DFS** |
| Level/jarak dari sumber | **BFS** |
| Graph sangat dalam (depth ~10⁶) | **BFS** atau DFS iteratif (hindari stack overflow) |

**Aturan praktis**: kalau soal minta **jarak terpendek**, pakai BFS. Selain itu, DFS biasanya lebih ringkas ditulis.

### Struktur Data yang Dipakai

```
BFS → Queue (FIFO)  → "yang duluan masuk, duluan diproses" → menyebar
DFS → Stack (LIFO)  → "yang terakhir masuk, duluan diproses" → mendalam
      ↑
      Pada versi rekursif, stack ini adalah CALL STACK — implisit,
      tidak perlu kita buat sendiri.
```

---

## 🧮 2. Analisis Kompleksitas

```
Adjacency List:
  Time  : O(V + E)
    - Setiap node dikunjungi tepat 1× (dijaga array visited)  → O(V)
    - Setiap edge ditelusuri tepat 1× (2× untuk undirected)   → O(E)
  Space : O(V) untuk visited + O(V) call stack (worst case: graph berupa rantai)

Adjacency Matrix:
  Time  : O(V²)  ← karena untuk tiap node harus scan V kolom
  Space : O(V²)
```

**Kenapa O(V+E) dan bukan O(V×E)?** Karena array `visited` menjamin tiap node diproses sekali. Total pekerjaan = jumlah semua tetangga di semua node = jumlah derajat = 2E untuk undirected.

| Ukuran Graph | V + E | Aman? |
|--------------|-------|-------|
| V=10⁵, E=2×10⁵ | 3×10⁵ | ✅ sangat cepat |
| V=10⁶, E=2×10⁶ | 3×10⁶ | ✅ aman |
| V=10⁵ berbentuk rantai | depth 10⁵ | ⚠️ rekursi ~10-16 MB stack, biasanya masih OK |
| V=10⁶ berbentuk rantai | depth 10⁶ | ❌ **stack overflow** — pakai DFS iteratif |

---

## 💻 3. Implementasi C++

### 3.1 DFS Rekursif (Bentuk Standar)

```cpp
const int MAXN = 200005;
vector<int> adj[MAXN];      // adjacency list
bool visited[MAXN];

void dfs(int u) {
    visited[u] = true;              // 1. tandai SEGERA saat masuk
    // ... proses node u di sini (pre-order) ...

    for (int v : adj[u]) {          // 2. telusuri semua tetangga
        if (!visited[v]) {
            dfs(v);                 // 3. rekursi ke tetangga belum dikunjungi
        }
    }
    // ... proses node u di sini (post-order) ...
}
```

⚠️ **Tandai `visited[u] = true` di AWAL fungsi**, bukan setelah loop. Kalau tidak, node yang sama bisa masuk berkali-kali → infinite loop pada graph bersiklus.

### 3.2 DFS Iteratif (Stack Eksplisit)

Dipakai ketika kedalaman bisa mencapai ~10⁶ dan rekursi berisiko stack overflow.

```cpp
void dfsIterative(int start) {
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (visited[u]) continue;   // bisa masuk stack >1× → skip duplikat
        visited[u] = true;
        // ... proses node u ...

        // push terbalik agar urutan visit sama dengan versi rekursif
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!visited[v]) st.push(v);
        }
    }
}
```

⚠️ Beda penting dengan versi rekursif: node bisa masuk stack lebih dari sekali (sebelum sempat ditandai). Karena itu cek `visited` dilakukan **saat pop**, bukan hanya saat push.

### 3.3 Connected Components

Berapa banyak "pulau" terpisah dalam graph tak berarah?

```cpp
int countComponents(int n) {
    int components = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components++;
            dfs(i);                 // satu panggilan = satu komponen penuh
        }
    }
    return components;
}
```

Idenya: setiap kali kita menemukan node yang belum terjamah, itu pasti awal dari komponen baru — karena semua node yang terhubung dengannya sudah pasti akan ikut ditandai oleh `dfs(i)`.

Variasi umum: simpan `comp[u] = components` untuk mencatat komponen tiap node, atau hitung ukuran tiap komponen.

### 3.4 Cycle Detection — Graph TAK BERARAH

Kuncinya: kalau kita menemukan tetangga yang sudah dikunjungi **dan bukan parent kita**, berarti ada jalan lain menuju node itu → cycle.

```cpp
bool dfsCycleUndirected(int u, int parent) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsCycleUndirected(v, u)) return true;
        }
        else if (v != parent) {
            return true;            // sudah dikunjungi & bukan parent → CYCLE
        }
    }
    return false;
}
```

⚠️ **Jebakan multi-edge**: jika ada dua edge terpisah antara u dan v, itu SUDAH cycle, tapi cek `v != parent` akan melewatkannya. Kalau soal mengizinkan multi-edge, lacak *edge id* alih-alih parent node.

⚠️ **Self-loop** (`u → u`) juga cycle, tapi lolos cek parent. Tangani terpisah bila constraint mengizinkan.

### 3.5 Cycle Detection — Graph BERARAH (3-Color)

Pada graph berarah, cek parent TIDAK cukup. Contoh: `1→2, 1→3, 2→3` punya node terkunjungi ulang tapi **tidak** bersiklus.

Yang menandakan cycle adalah **back edge**: edge menuju node yang masih berada di *recursion stack* saat ini.

```
color[u] = 0 → WHITE : belum dikunjungi
color[u] = 1 → GRAY  : sedang diproses (ada di recursion stack)
color[u] = 2 → BLACK : selesai diproses (beserta semua turunannya)
```

```cpp
int color[MAXN];

bool dfsCycleDirected(int u) {
    color[u] = 1;                   // GRAY — masuk recursion stack
    for (int v : adj[u]) {
        if (color[v] == 1) return true;             // back edge → CYCLE
        if (color[v] == 0 && dfsCycleDirected(v)) return true;
        // color[v] == 2 (BLACK) → cabang sudah selesai, aman, lewati
    }
    color[u] = 2;                   // BLACK — keluar recursion stack
    return false;
}
```

Kenapa BLACK aman? Karena kalau `v` sudah selesai sepenuhnya, semua yang bisa dicapai dari `v` juga sudah selesai — tidak mungkin ada jalur balik ke `u` yang masih GRAY.

### 3.6 Topological Sort (DFS Post-Order)

Untuk **DAG** (Directed Acyclic Graph): urutkan node sehingga setiap edge `u→v` berarti `u` muncul sebelum `v`. Aplikasi: urutan mata kuliah dengan prasyarat, urutan build dependency.

```cpp
vector<int> topoOrder;

void dfsTopo(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfsTopo(v);
    }
    topoOrder.push_back(u);         // POST-ORDER: setelah semua turunan selesai
}

vector<int> topologicalSort(int n) {
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfsTopo(i);

    reverse(topoOrder.begin(), topoOrder.end());   // WAJIB dibalik!
    return topoOrder;
}
```

**Kenapa post-order lalu dibalik?** Node `u` baru dimasukkan setelah SEMUA node yang bisa dicapai darinya sudah masuk. Jadi dalam list, `u` selalu berada SETELAH semua turunannya. Dibalik → `u` berada SEBELUM semuanya. ✓

⚠️ Topological sort hanya ada jika graph adalah DAG. Kalau ada cycle, gabungkan dengan deteksi cycle 3-color dan laporkan "IMPOSSIBLE".

### 3.7 Discovery Time & Finish Time

Fondasi untuk bridges (Day 73), SCC (Day 74), dan Euler tour (Day 48).

```cpp
int timer = 0;
int tin[MAXN], tout[MAXN];

void dfsTime(int u) {
    tin[u] = timer++;               // waktu masuk
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) dfsTime(v);
    tout[u] = timer++;              // waktu keluar
}

// Properti yang sangat berguna:
// u adalah ANCESTOR dari v  ⟺  tin[u] < tin[v] && tout[v] < tout[u]
// → cek "apakah v ada di subtree u" dalam O(1)!
```

### 3.8 DFS pada Grid

Grid adalah graph implisit: tiap sel adalah node, tetangganya adalah 4 (atau 8) sel di sekitarnya.

```cpp
int dr[] = {-1, 1, 0, 0};       // atas, bawah, kiri, kanan
int dc[] = {0, 0, -1, 1};

char grid[1005][1005];
bool vis[1005][1005];
int R, C;

void dfsGrid(int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) return;   // di luar grid
    if (vis[r][c] || grid[r][c] == '#') return;       // sudah dikunjungi / tembok

    vis[r][c] = true;
    for (int d = 0; d < 4; d++)
        dfsGrid(r + dr[d], c + dc[d]);
}
```

⚠️ Grid 1000×1000 penuh bisa menghasilkan kedalaman rekursi 10⁶ → **risiko stack overflow**. Untuk grid besar, pakai BFS atau DFS iteratif.

---

## 🔄 4. Trace & Simulasi

### Trace DFS pada Graph Tak Berarah

```
Graph (undirected):     1 ─── 2
                        │     │
                        3 ─── 4 ─── 5

adj[1] = {2, 3}
adj[2] = {1, 4}
adj[3] = {1, 4}
adj[4] = {2, 3, 5}
adj[5] = {4}
```

| Langkah | Aksi | Call Stack | visited |
|---------|------|-----------|---------|
| 1 | dfs(1), tandai 1 | [1] | {1} |
| 2 | tetangga 2 belum → dfs(2) | [1,2] | {1,2} |
| 3 | tetangga 1 sudah, 4 belum → dfs(4) | [1,2,4] | {1,2,4} |
| 4 | tetangga 2 sudah, 3 belum → dfs(3) | [1,2,4,3] | {1,2,4,3} |
| 5 | tetangga 1 sudah, 4 sudah → buntu, **return** | [1,2,4] | {1,2,4,3} |
| 6 | lanjut tetangga 4: node 5 → dfs(5) | [1,2,4,5] | {1,2,4,3,5} |
| 7 | tetangga 4 sudah → buntu, **return** | [1,2,4] | semua |
| 8 | 4 selesai, **return** | [1,2] | semua |
| 9 | 2 selesai, **return** | [1] | semua |
| 10 | lanjut tetangga 1: node 3 sudah → selesai | [] | semua |

**Urutan visit (pre-order)**: 1, 2, 4, 3, 5
**Urutan selesai (post-order)**: 3, 5, 4, 2, 1

### Trace Cycle Detection Berarah (3-Color)

```
Graph berarah: 1 → 2 → 3 → 1     (jelas ada cycle)
```

| Langkah | Node | Aksi | color[] |
|---------|------|------|---------|
| 1 | 1 | masuk, jadi GRAY | 1:G 2:W 3:W |
| 2 | 2 | dari 1, masuk, GRAY | 1:G 2:G 3:W |
| 3 | 3 | dari 2, masuk, GRAY | 1:G 2:G 3:G |
| 4 | 1 | dari 3 → color[1] == GRAY | **CYCLE ✓** |

Bandingkan dengan graph tanpa cycle:

```
Graph berarah: 1 → 2, 1 → 3, 2 → 3    (DAG, tidak ada cycle)
```

| Langkah | Node | Aksi | color[] |
|---------|------|------|---------|
| 1 | 1 | masuk, GRAY | 1:G |
| 2 | 2 | dari 1, GRAY | 1:G 2:G |
| 3 | 3 | dari 2, GRAY | 1:G 2:G 3:G |
| 4 | 3 | tidak ada tetangga → BLACK | 1:G 2:G 3:B |
| 5 | 2 | selesai → BLACK | 1:G 2:B 3:B |
| 6 | 1 | tetangga 3 → color[3] == BLACK, **aman, lewati** | 1:G 2:B 3:B |
| 7 | 1 | selesai → BLACK | semua B, **tidak ada cycle ✓** |

Perhatikan langkah 6: node 3 dikunjungi ulang tapi BUKAN cycle. Inilah alasan cek "sudah dikunjungi" saja tidak cukup untuk graph berarah.

### Trace Topological Sort

```
Graph: 5 → 2, 5 → 0, 4 → 0, 4 → 1, 2 → 3, 3 → 1
(node 0..5, contoh klasik)
```

Mulai dari node 0 (tidak punya keluar) → post-order langsung push 0.
Lanjut node 1 → push 1.
Node 2 → 3 → 1(sudah) → push 3, push 2.
Node 4 → 0(sudah), 1(sudah) → push 4.
Node 5 → 2(sudah), 0(sudah) → push 5.

```
topoOrder (post-order) = [0, 1, 3, 2, 4, 5]
dibalik                = [5, 4, 2, 3, 1, 0]   ← jawaban
```

Verifikasi: 5 sebelum 2 ✓, 5 sebelum 0 ✓, 4 sebelum 0 ✓, 4 sebelum 1 ✓, 2 sebelum 3 ✓, 3 sebelum 1 ✓. Semua edge terpenuhi.

---

## 📝 5. Variasi & Pattern

| Pola Soal | Teknik DFS |
|-----------|-----------|
| "Berapa banyak pulau/kelompok?" | Connected components |
| "Apakah graph ini pohon?" | Terhubung DAN E == V−1 DAN tidak bersiklus |
| "Apakah ada urutan yang valid?" | Topological sort (deteksi cycle dulu) |
| "Deadlock / dependency melingkar?" | Cycle detection berarah |
| "Ukuran kelompok terbesar" | DFS sambil hitung ukuran komponen |
| "Bisakah diwarnai 2 warna?" | DFS coloring (bipartite — Day 61) |
| "Isi area yang terhubung" | Flood fill (Day 62) |
| "Ukuran subtree tiap node" | DFS post-order pada tree |
| "Apakah v ada di subtree u?" | tin/tout time |
| "Semua kemungkinan susunan" | DFS + backtracking (Day 12) |
| "Jalur terpanjang di DAG" | DFS + DP on DAG (Day 100) |

### Klasifikasi Edge (untuk graph berarah)

```
Tree edge     : edge yang dipakai DFS untuk masuk ke node baru (WHITE)
Back edge     : menuju node GRAY (ancestor)   → PENANDA CYCLE
Forward edge  : menuju node BLACK keturunan sendiri
Cross edge    : menuju node BLACK di cabang lain
```

Pada graph tak berarah, hanya ada tree edge dan back edge.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Lupa menandai `visited[u] = true` di awal fungsi** — infinite loop pada graph bersiklus. Ini bug DFS nomor satu.

2. **Hanya DFS dari node 1** — graph bisa terdiri dari beberapa komponen terpisah. Untuk memproses seluruh graph, loop semua node:
   ```cpp
   for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
   ```

3. **Pakai cek parent untuk graph BERARAH** — salah. Graph berarah butuh 3-color / recursion stack.

4. **Lupa membalik hasil topological sort** — hasil post-order adalah kebalikan dari urutan yang benar.

5. **Stack overflow pada graph dalam** — rekursi kedalaman 10⁶ pada stack 8 MB akan crash. Solusi: DFS iteratif, atau BFS jika memungkinkan.

6. **Undirected graph hanya di-push satu arah**
   ```cpp
   adj[u].push_back(v);           // ❌ hanya setengah
   adj[u].push_back(v);
   adj[v].push_back(u);           // ✅ kedua arah
   ```

7. **Tidak reset `visited` pada multi test case** — sisa data dari test case sebelumnya membuat jawaban salah. Reset hanya sebanyak `n` yang dipakai (jangan `memset` seluruh MAXN tiap test case — bisa TLE).

8. **Node 0-indexed vs 1-indexed tertukar** — array `visited[0]` tidak dipakai atau justru node 0 terlewat.

9. **Rekursi pada grid besar** — grid 1000×1000 semua sel bisa dilalui = depth 10⁶.

### Edge Cases yang Wajib Dicek

| Kasus | Perilaku benar |
|-------|----------------|
| Graph kosong (n=0) | Output 0 komponen |
| Node tunggal tanpa edge | 1 komponen, tidak ada cycle |
| Graph tidak terhubung | Harus loop semua node sebagai start |
| Self-loop (u→u) | Cycle pada directed; pada undirected juga cycle |
| Multi-edge | Cycle pada undirected — cek parent tidak cukup |
| Graph lengkap | E = V(V−1)/2, tetap O(V+E) |
| Semua node terisolasi | Jumlah komponen = n |

---

## 🏆 7. Tips Contest

- **Red flag pakai DFS**: "berapa kelompok", "apakah ada siklus", "urutan yang valid", "ukuran area", "apakah terhubung", "semua kemungkinan".
- **Red flag pakai BFS**: kata "**minimal langkah**", "**jarak terpendek**", "**lapis**". Kalau ada kata itu, jangan pakai DFS.
- **Naikkan stack size** kalau terpaksa rekursi dalam (beberapa judge mengizinkan):
  ```cpp
  #pragma comment(linker, "/STACK:268435456")   // hanya Windows/MSVC
  ```
  Cara portable: tulis ulang jadi iteratif.
- **Template siap pakai** — simpan adjacency list + dfs dasar di template, tinggal ubah bagian "proses node".
- **Debug DFS**: cetak `u` di awal dan akhir fungsi dengan indentasi sesuai kedalaman — struktur rekursinya langsung kelihatan.
- **Estimasi memori**: `vector<int> adj[200005]` dengan 4×10⁵ edge ≈ beberapa MB, aman. Adjacency matrix 10⁵×10⁵ jelas mustahil.
- **Reset efisien**: `fill(visited, visited+n+1, false)` alih-alih `memset` seluruh array.

---

## 📌 8. Ringkasan & Cheatsheet

```cpp
// ═══════════ CHEATSHEET DAY 59 ═══════════
vector<int> adj[MAXN];
bool visited[MAXN];

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
        else if (v != p) return true;
    }
    return false;
}

// --- CYCLE DIRECTED (3-color) ---
int color[MAXN];    // 0=putih 1=abu 2=hitam
bool cycD(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) return true;
        if (color[v] == 0 && cycD(v)) return true;
    }
    color[u] = 2;
    return false;
}

// --- TOPOLOGICAL SORT ---
vector<int> topo;
void dfsT(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfsT(v);
    topo.push_back(u);                          // POST-ORDER
}
// setelah loop semua node: reverse(topo.begin(), topo.end());

// --- DISCOVERY / FINISH TIME ---
int timer = 0, tin[MAXN], tout[MAXN];
void dfsTm(int u) {
    tin[u] = timer++;  visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfsTm(v);
    tout[u] = timer++;
}
// isAncestor(u,v) = tin[u] < tin[v] && tout[v] < tout[u]
```

### Key Points

| Konsep | Ingat ini |
|--------|-----------|
| Struktur data | Stack (LIFO) — rekursi memakai call stack |
| Kompleksitas | O(V+E) adjacency list |
| Shortest path | ❌ DFS TIDAK menjamin — pakai BFS |
| Cycle undirected | Tetangga terkunjungi & bukan parent |
| Cycle directed | Tetangga berwarna GRAY (back edge) |
| Topo sort | Post-order lalu **reverse** |
| Bahaya | Stack overflow pada depth > ~10⁶ |

### Latihan Online Judge

| Platform | Problem | Judul |
|----------|---------|-------|
| CSES | 1666 | Building Roads (connected components) |
| CSES | 1682 | Flight Routes Check |
| CSES | 1678 | Round Trip II (cycle directed + rekonstruksi) |
| CSES | 1669 | Round Trip (cycle undirected) |
| CSES | 1679 | Course Schedule (topological sort) |
| CSES | 1192 | Counting Rooms (flood fill) |
| LeetCode | 200 | Number of Islands |
| LeetCode | 207 | Course Schedule |
| LeetCode | 210 | Course Schedule II |
| LeetCode | 547 | Number of Provinces |
| Codeforces | 977E | Cyclic Components |
| AtCoder | ATC 001 A | Depth First Search |

---

**Next (Day 60)**: Topological Sort dengan **Kahn's algorithm** (berbasis BFS + in-degree) — pendekatan alternatif dari yang kita pelajari hari ini, plus cara mendeteksi cycle darinya.
