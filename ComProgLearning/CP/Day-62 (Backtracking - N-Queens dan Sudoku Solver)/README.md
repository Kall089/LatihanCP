# Day 12 — Backtracking

## Tujuan Pembelajaran

- [ ] Memahami paradigma backtracking: "coba → rekursi → undo"
- [ ] Mengimplementasikan generate permutasi dengan `used[]` array
- [ ] Mengimplementasikan generate subsets dengan `start` index
- [ ] Menguasai Combination Sum dengan pruning (sort + break)
- [ ] Memecahkan N-Queens dengan diagonal bitmask check
- [ ] Menggunakan DFS + backtracking untuk Word Search di grid 2D

---

## Struktur Folder

```
Day-12 (Backtracking)/
├── README.md
├── teori/
│   ├── Day_12_Teori_Lengkap.md       ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_12_Presentation.pptx     ← Presentasi 16 slide
├── latihan/
│   ├── exercise_1.cpp  ← Generate All Permutations
│   ├── exercise_2.cpp  ← Generate All Subsets (Power Set)
│   ├── exercise_3.cpp  ← Combination Sum (boleh ulang)
│   ├── exercise_4.cpp  ← N-Queens Problem
│   ├── exercise_5.cpp  ← Subset Sum + Rekonstruksi
│   └── exercise_6.cpp  ← Word Search di Grid 2D
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_12_Teori_Lengkap.md` (atau buka PPT)
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | Generate All Permutations (backtracking) | Warm-up |
| exercise_2.cpp | Generate All Subsets / Power Set | Core |
| exercise_3.cpp | Combination Sum — elemen boleh diulang | Core |
| exercise_4.cpp | N-Queens — hitung semua solusi | Challenge |
| exercise_5.cpp | Subset Sum — ada/tidak + rekonstruksi | Challenge |
| exercise_6.cpp | Word Search di Grid 2D | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Generate All Binary Strings of Length N | Easy |
| tugas_02 | Generate Parentheses | Easy |
| tugas_03 | Phone Number Letter Combinations | Easy |
| tugas_04 | Palindrome Partitioning | Easy |
| tugas_05 | Combination Sum II (No Duplicates) | Medium |
| tugas_06 | Permutations with Duplicates | Medium |
| tugas_07 | Sudoku Solver | Medium |
| tugas_08 | N-Queens — Print All Solutions | Medium |
| tugas_09 | Restore IP Addresses | Medium |
| tugas_10 | Letter Case Permutation | Medium |
| tugas_11 | Cryptarithmetic Puzzle | Hard |
| tugas_12 | Hamiltonian Path in Grid | Hard |
| tugas_13 | Partition to K Equal Sum Subsets | Hard |
| tugas_14 | Expression Add Operators | Hard |
| tugas_15 | Minimum Subset Sum Difference | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 46    | Permutations | Backtracking dasar |
| LC 78    | Subsets | Power set |
| LC 39    | Combination Sum | Pruning |
| LC 40    | Combination Sum II | No dup |
| LC 51    | N-Queens | Classic |
| LC 79    | Word Search | DFS + backtrack |
| LC 17    | Letter Combinations of Phone Number | Backtracking |
| CSES     | Chessboard and Queens | N-Queens variant |

---

## Common Mistakes

1. **Lupa UNDO** → setiap `push_back` harus ada `pop_back` setelah rekursi
2. **i vs i+1 di Combination Sum** → boleh ulang: `backtrack(cands, i, ...)` | tidak boleh: `i+1`
3. **N-Queens: diag1 index negatif** → gunakan `diag1[row-col+n]` (tambahkan +n)
4. **Word Search: tidak restore grid** → `grid[r][c] = '#'` lalu `grid[r][c] = tmp` wajib!
5. **Combination Sum tanpa sort** → `if (cands[i] > target) break` hanya valid jika sorted

---

## Quick Cheatsheet

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
```
