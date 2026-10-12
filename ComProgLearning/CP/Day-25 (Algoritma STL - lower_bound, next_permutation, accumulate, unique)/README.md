# Day 6 — STL Algorithms

## Tujuan Pembelajaran

- [ ] Menguasai `sort` dengan custom comparator (lambda, struct, multi-criteria)
- [ ] Menggunakan `lower_bound` dan `upper_bound` untuk binary search O(log n)
- [ ] Menggunakan `next_permutation` untuk generate semua permutasi
- [ ] Memanfaatkan `accumulate`, `count_if`, `max_element` untuk reduksi
- [ ] Menguasai `find`, `reverse`, `rotate`, `unique` dan kapan menggunakannya
- [ ] Memahami perbedaan `sort` vs `stable_sort`

---

## Struktur Folder

```
Day-6 (STL Algorithms)/
├── README.md
├── teori/
│   ├── Day_6_Teori_Lengkap.md        ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_6_Presentation.pptx      ← Presentasi 14 slide
├── latihan/
│   ├── exercise_1.cpp  ← Sort Basic & Descending
│   ├── exercise_2.cpp  ← lower_bound & upper_bound
│   ├── exercise_3.cpp  ← next_permutation
│   ├── exercise_4.cpp  ← accumulate & Reduction
│   ├── exercise_5.cpp  ← find, count, reverse, rotate
│   └── exercise_6.cpp  ← Sort Struct & Multi-Criteria
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_6_Teori_Lengkap.md` (atau buka PPT)
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | Sort ascending & descending | Warm-up |
| exercise_2.cpp | lower_bound, upper_bound, count | Core |
| exercise_3.cpp | next_permutation — all permutations | Core |
| exercise_4.cpp | accumulate, count_if, max_element | Core |
| exercise_5.cpp | find, count, reverse, rotate | Core |
| exercise_6.cpp | Sort struct multi-criteria (score desc, name asc) | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Coordinate Compression | Easy |
| tugas_02 | Count Inversions (Brute Force) | Easy |
| tugas_03 | Merge Two Sorted Arrays | Easy |
| tugas_04 | Find Kth Occurrence | Easy |
| tugas_05 | Sort by Absolute Value | Medium |
| tugas_06 | Minimum Difference Between Any Two | Medium |
| tugas_07 | Count Elements in Range | Medium |
| tugas_08 | Lexicographically Smallest After K Swaps | Medium |
| tugas_09 | Meeting Schedule Conflict | Medium |
| tugas_10 | Maximum Area Rectangle from Points | Medium |
| tugas_11 | Minimum Arrows to Burst Balloons | Hard |
| tugas_12 | Wiggle Sort II | Hard |
| tugas_13 | Largest Number (Custom Sort) | Hard |
| tugas_14 | Patience Sorting (LIS) | Hard |
| tugas_15 | Count of Smaller Numbers After Self | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| CSES     | Sorting and Searching | sort, binary search |
| LC 56    | Merge Intervals | sort + greedy |
| LC 179   | Largest Number | custom comparator |
| LC 315   | Count of Smaller Numbers | merge sort |
| LC 31    | Next Permutation | next_permutation logic |
| CSES     | Movie Festival | sort by end time |
| LC 349   | Intersection of Two Arrays | sort + bs |
| LC 300   | Longest Increasing Subsequence | lower_bound O(n log n) |

---

## Common Mistakes

1. **`lower_bound` tanpa sort** → array harus sorted dulu, selalu!
2. **`unique` tanpa sort** → hanya hapus consecutive dup, butuh `sort` dulu
3. **Iterator vs nilai**: `lo - A.begin()` = index, `*lo` = nilai
4. **`accumulate` dengan `0` bukan `0LL`** → bisa overflow jika sum > INT_MAX
5. **`next_permutation` tanpa sort di awal** → tidak generate semua permutasi

---

## Quick Cheatsheet

```cpp
// Sort
sort(v.begin(), v.end());                          // ascending
sort(v.begin(), v.end(), greater<int>());           // descending
sort(v.begin(), v.end(), [](int a, int b){ ... });  // lambda

// Binary Search (harus sorted!)
auto lo = lower_bound(v.begin(), v.end(), x); // first >= x
auto hi = upper_bound(v.begin(), v.end(), x); // first > x
int cnt = hi - lo;              // jumlah elemen == x
int idx = lo - v.begin();       // index elemen

// Accumulate & friends
ll sum = accumulate(v.begin(), v.end(), 0LL);
int mx = *max_element(v.begin(), v.end());
int n  = count_if(v.begin(), v.end(), [](int x){ return x%2==0; });

// Toolbox
reverse(v.begin(), v.end());
rotate(v.begin(), v.begin()+k, v.end()); // rotate kiri k
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end()); // deduplicate
```
