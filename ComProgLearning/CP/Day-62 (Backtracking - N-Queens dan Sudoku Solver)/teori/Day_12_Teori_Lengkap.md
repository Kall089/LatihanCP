# Day 12 — Backtracking

## Tujuan Pembelajaran
- [ ] Memahami paradigma backtracking: "coba → rekursi → undo"
- [ ] Mengimplementasikan generate permutasi dengan `used[]` array
- [ ] Mengimplementasikan generate subsets dengan `start` index
- [ ] Menguasai Combination Sum dengan pruning (sort + break)
- [ ] Memecahkan N-Queens dengan diagonal bitmask check
- [ ] Menggunakan DFS + backtracking untuk Word Search di grid 2D
- [ ] Memahami Graph Coloring sebagai contoh constraint backtracking
- [ ] Menerapkan Palindrome Partitioning (aplikasi backtracking + string)
- [ ] Memilih strategi pruning yang tepat untuk setiap masalah
- [ ] Membedakan kapan pakai Backtracking vs Dynamic Programming

---

## 1. Paradigma Backtracking

Backtracking = eksplorasi ruang solusi secara sistematis dengan **prune** (pangkas) cabang yang tidak mungkin.

```
void backtrack(state) {
    if (goal reached) {
        record solution;
        return;
    }
    for (each choice) {
        if (choice is valid) {   // ← PRUNING
            make choice;         // modify state
            backtrack(next);     // recurse
            undo choice;         // restore state (backtrack!)
        }
    }
}
```

**Kunci**: Selalu **undo** modifikasi setelah rekursi kembali.

---

## 2. Generate All Permutations

```cpp
vector<int> perm;
vector<bool> used(n+1, false);

void backtrack() {
    if ((int)perm.size() == n) {
        for (int x : perm) cout << x << " ";
        cout << "\n";
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            perm.push_back(i);
            backtrack();
            perm.pop_back();   // undo
            used[i] = false;   // undo
        }
    }
}
```

**Kompleksitas**: O(n! × n) — n! permutasi, tiap membutuhkan O(n) untuk cetak.

---

## 3. Generate All Subsets (Power Set)

```cpp
vector<int> subset;

void backtrack(int start) {
    // Cetak subset saat ini (termasuk kosong)
    print(subset);

    for (int i = start; i <= n; i++) {
        subset.push_back(i);
        backtrack(i + 1);   // i+1: tidak boleh pakai elemen sebelumnya
        subset.pop_back();
    }
}
```

`start` memastikan setiap subset hanya di-generate sekali (tidak ada duplikat).

**Kompleksitas**: O(2^n × n) — 2^n subset, tiap butuh O(n) untuk proses.

---

## 4. Combination Sum (dengan Pruning)

**Masalah**: Temukan semua kombinasi dari array yang jumlahnya = target (elemen boleh diulang).

```cpp
void backtrack(vector<int>& cands, int start, int target) {
    if (target == 0) { result.push_back(current); return; }

    for (int i = start; i < (int)cands.size(); i++) {
        if (cands[i] > target) break; // ← PRUNING (harus sorted!)
        current.push_back(cands[i]);
        backtrack(cands, i, target - cands[i]); // i: boleh pakai lagi
        current.pop_back();
    }
}
```

**Pruning**: Sort array dulu → jika `cands[i] > target`, semua elemen berikutnya juga > target → break.

---

## 5. N-Queens Problem

**Masalah**: Tempatkan N ratu sehingga tidak ada yang saling serang.

**Representasi konflik**:
- Kolom: `cols[col]`
- Diagonal ↘: `diag1[row - col + N]` (nilainya sama di satu diagonal)
- Diagonal ↙: `diag2[row + col]` (nilainya sama di satu diagonal)

```cpp
void solve(int row) {
    if (row == n) { solutions++; return; }
    for (int col = 0; col < n; col++) {
        if (cols[col] || diag1[row-col+n] || diag2[row+col]) continue;
        // Tempatkan ratu
        cols[col] = diag1[row-col+n] = diag2[row+col] = true;
        solve(row + 1);
        // Angkat ratu
        cols[col] = diag1[row-col+n] = diag2[row+col] = false;
    }
}
```

| N | Jumlah Solusi |
|---|--------------|
| 4 | 2 |
| 5 | 10 |
| 8 | 92 |
| 12 | 14200 |

---

## 6. Subset Sum — Backtracking + Rekonstruksi

```cpp
bool backtrack(int idx, int remaining) {
    if (remaining == 0) return true;           // ditemukan!
    if (idx == n || remaining < 0) return false; // tidak mungkin

    // Coba AMBIL A[idx]
    chosen.push_back(A[idx]);
    if (backtrack(idx+1, remaining - A[idx])) return true;
    chosen.pop_back(); // undo

    // Coba SKIP A[idx]
    return backtrack(idx+1, remaining);
}
```

**Optimasi**: Sort descending → elemen besar lebih awal → pruning `remaining < 0` lebih cepat.

---

## 7. Word Search di Grid (DFS + Backtracking)

```cpp
int dr[]={-1,1,0,0}, dc[]={0,0,-1,1};

bool dfs(int r, int c, int idx) {
    if (idx == (int)word.size()) return true;
    if (r<0||r>=R||c<0||c>=C) return false;
    if (grid[r][c] != word[idx]) return false;

    char tmp = grid[r][c];
    grid[r][c] = '#'; // tandai visited

    bool found = false;
    for (int d = 0; d < 4; d++)
        if (dfs(r+dr[d], c+dc[d], idx+1)) { found = true; break; }

    grid[r][c] = tmp; // restore
    return found;
}
```

**Kunci**: Tandai sel sebagai `'#'` sementara → lebih hemat memori daripada `visited[][]`.

---

## 8. Graph Coloring — Constraint Backtracking

**Masalah**: Beri warna pada N simpul dengan M warna sehingga tidak ada dua simpul bertetangga berwarna sama.

```cpp
bool canColor(vector<vector<int>>& adj, vector<int>& color, int v, int c) {
    for (int u : adj[v])
        if (color[u] == c) return false;
    return true;
}

bool graphColor(vector<vector<int>>& adj, vector<int>& color, int v, int m) {
    if (v == (int)adj.size()) return true; // semua simpul sudah diberi warna

    for (int c = 1; c <= m; c++) {
        if (canColor(adj, color, v, c)) {
            color[v] = c;                       // PILIH warna c
            if (graphColor(adj, color, v+1, m)) return true;
            color[v] = 0;                       // UNDO (backtrack)
        }
    }
    return false; // tidak ada solusi dengan m warna
}

// Di main:
int n, m; // n simpul, m warna
vector<vector<int>> adj(n);
vector<int> color(n, 0); // 0 = belum diberi warna
graphColor(adj, color, 0, m);
```

**Contoh aplikasi**: Map coloring (4-color theorem), register allocation, penjadwalan.

---

## 9. Palindrome Partitioning

**Masalah**: Partisi string menjadi bagian-bagian yang semuanya palindrom.

```cpp
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

void backtrack(const string& s, int start,
               vector<string>& cur, vector<vector<string>>& res) {
    if (start == (int)s.size()) {
        res.push_back(cur); // semua bagian palindrom
        return;
    }
    for (int end = start; end < (int)s.size(); end++) {
        if (isPalin(s, start, end)) {
            cur.push_back(s.substr(start, end - start + 1)); // PILIH
            backtrack(s, end + 1, cur, res);                  // EXPLORE
            cur.pop_back();                                   // UNDO
        }
    }
}
// Input "aab" → output: [["a","a","b"], ["aa","b"]]
```

**Optimasi**: Precompute tabel `dp[i][j] = true jika s[i..j] palindrom` → O(1) per cek, O(n²) preprocessing.

---

## 10. Strategi Pruning

| Teknik | Kapan Dipakai | Contoh |
|--------|---------------|--------|
| Early termination (target < 0) | Subset sum, combination sum | `if (remaining < 0) return false` |
| Sort + break | Combination sum | `if (cands[i] > target) break` |
| Skip duplikat | Combination sum II | `if (i>start && cands[i]==cands[i-1]) continue` |
| Forward checking | N-Queens, Sudoku, graph coloring | `if (!isValid(state)) continue` |
| Symmetry breaking | N-Queens (fix first row) | Kurangi cabang di level pertama |
| Batas atas estimasi | Branch and bound | Jika upper bound < best → pangkas |
| Memoization | Backtracking + overlapping subproblems | `if (memo[state] != -1) return memo[state]` |

---

## 11. Backtracking vs Dynamic Programming

| Aspek | Backtracking | Dynamic Programming |
|-------|-------------|---------------------|
| **Tujuan** | Temukan SEMUA solusi / solusi pertama | Hitung nilai optimal (min/max/count) |
| **State** | Eksplisit (modify & undo) | Tabular (dp array) |
| **Overlapping** | Tidak (atau sedikit) | Banyak submasalah overlapping |
| **Memori** | O(kedalaman rekursi) | O(jumlah state) |
| **Ketika N** | N ≤ 20 (eksponensial OK) | N bisa besar (polynomial) |
| **Output** | Daftar solusi / satu solusi | Angka tunggal atau dp array |
| **Contoh** | N-Queens, Sudoku, permutasi | LCS, knapsack, Fibonacci |

**Kapan backtracking?**: Perlu **semua solusi** atau **membangun solusi** secara bertahap, dan pruning bisa mengurangi ruang pencarian secara signifikan.

**Hybrid**: Backtracking + memoization = rekursi dengan DP (top-down DP), berguna jika banyak state yang sama dikunjungi.

---

## 12. Common Mistakes

1. **Lupa UNDO state**
   - Setiap modifikasi harus di-restore setelah rekursi
   - `push_back → backtrack → pop_back`

2. **Start index salah di Combination Sum**
   - Boleh ulang: `backtrack(cands, i, ...)` (bukan `i+1`)
   - Tidak boleh ulang: `backtrack(cands, i+1, ...)`

3. **N-Queens diagonal index**
   - `diag1[row-col+n]` perlu `+n` agar tidak negatif

4. **Word Search: tidak restore grid**
   - Setelah `grid[r][c] = '#'`, harus `grid[r][c] = tmp` saat return (SEMUA path!)

5. **Tidak sort dulu di Combination Sum**
   - Tanpa sort, `if (cands[i] > target) break` tidak benar!

6. **isPalin tidak O(1)**: Untuk palindrome partitioning dengan n > 100, precompute dp tabel palindrom

---

## 13. Kompleksitas

| Algoritma | Waktu | Ruang |
|-----------|-------|-------|
| Generate All Permutations | O(n! × n) | O(n) |
| Generate All Subsets | O(2^n × n) | O(n) |
| Combination Sum | O(N^(T/M)) dipruning | O(T/M) |
| N-Queens | O(n!) dipruning | O(n) |
| Subset Sum | O(2^n) | O(n) |
| Word Search | O(R×C × 4^L) | O(L) |
| Graph Coloring | O(m^n) dipruning | O(n) |
| Palindrome Partition | O(n × 2^n) | O(n) |

---

## 14. Quick Cheatsheet

```cpp
// Template Universal
void bt(state) {
    if (done) { record; return; }
    for (choice) { if (valid) { make; bt(next); undo; } }
}

// Permutasi
if (!used[i]) { used[i]=true; perm.push_back(i); bt(); perm.pop_back(); used[i]=false; }

// Subsets
for (int i=start; i<=n; i++) { subset.push_back(i); bt(i+1); subset.pop_back(); }

// Combination Sum (sort dulu!)
if (cands[i] > target) break;
backtrack(cands, i, target - cands[i]); // i untuk boleh ulang

// N-Queens
cols[c]=diag1[r-c+n]=diag2[r+c]=true; solve(r+1);
cols[c]=diag1[r-c+n]=diag2[r+c]=false;

// Grid DFS
char tmp=grid[r][c]; grid[r][c]='#'; dfs(...); grid[r][c]=tmp;

// Graph Coloring
for (int c=1; c<=m; c++) {
    if (canColor(adj, color, v, c)) { color[v]=c; solve(v+1); color[v]=0; }
}
```

---

## 15. Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 46 | Permutations | Backtracking dasar |
| LC 78 | Subsets | Power set |
| LC 39 | Combination Sum | Pruning |
| LC 40 | Combination Sum II | No dup |
| LC 51 | N-Queens | Classic |
| LC 79 | Word Search | DFS + backtracking |
| LC 17 | Letter Combinations Phone Number | BT |
| LC 131 | Palindrome Partitioning | BT + palindrome |
| LC 22 | Generate Parentheses | BT constraint |
| CSES | Chessboard and Queens | N-Queens variant |
