# Day 16 — Custom Comparator

## Tujuan Pembelajaran

- [ ] Memahami konsep **strict weak ordering** yang dibutuhkan comparator
- [ ] Mengimplementasikan `operator<` pada struct untuk auto-sort
- [ ] Membuat **comparator functor** struct untuk reusability
- [ ] Menguasai **lambda comparator** untuk inline, concise sorting
- [ ] Menerapkan **multi-criteria sort** (3+ kriteria, tiebreaking chain)
- [ ] Membuat `priority_queue` dengan custom comparator (min-heap struct)
- [ ] Menggunakan `set` dan `map` dengan custom comparator
- [ ] Memahami perbedaan `sort` vs `stable_sort` dengan custom comparator

---

## Struktur Folder

```
Day-16 (Custom Comparator)/
├── README.md
├── teori/
│   ├── Day_16_Teori_Lengkap.md       ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_16_Presentation.pptx     ← Presentasi 16 slide
├── latihan/
│   ├── exercise_1.cpp  ← operator< overloading pada struct Point
│   ├── exercise_2.cpp  ← Sort students: comparator functor struct
│   ├── exercise_3.cpp  ← Task scheduling: multi-criteria lambda (3 kriteria)
│   ├── exercise_4.cpp  ← priority_queue<Task> dengan min-heap functor
│   ├── exercise_5.cpp  ← Index sort: sort indices by value
│   └── exercise_6.cpp  ← Version string sort (1.10.3 vs 1.9.5)
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_16_Teori_Lengkap.md`
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | operator< overloading pada struct Point | Warm-up |
| exercise_2.cpp | Comparator functor struct untuk sort Students | Core |
| exercise_3.cpp | Lambda multi-criteria: 3+ kriteria sort | Core |
| exercise_4.cpp | priority_queue<Task> dengan custom min-heap | Challenge |
| exercise_5.cpp | Index sort: sort indices berdasarkan nilai | Challenge |
| exercise_6.cpp | Version string sort: "1.10.3" > "1.9.5" | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Sort by string length, then lex | Easy |
| tugas_02 | Sort by absolute value | Easy |
| tugas_03 | Sort intervals by (end, then start) | Easy |
| tugas_04 | Even first (asc), odd after (desc) | Easy |
| tugas_05 | Sort by frequency desc, then value asc | Medium |
| tugas_06 | Top-K elements using min-heap | Medium |
| tugas_07 | Sort by popcount (set bits), then value | Medium |
| tugas_08 | Sort by number of divisors | Medium |
| tugas_09 | Weighted job scheduling (sort by deadline) | Medium |
| tugas_10 | Merge K sorted arrays using min-heap | Medium |
| tugas_11 | Sort points by polar angle from origin | Hard |
| tugas_12 | Meeting Rooms II (min-heap end times) | Hard |
| tugas_13 | Sort "words" by frequency in text | Hard |
| tugas_14 | Lexicographically smallest after K swaps | Hard |
| tugas_15 | Strict weak ordering validator | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 179 | Largest Number | Custom comparator string |
| LC 56 | Merge Intervals | Sort by start time |
| LC 253 | Meeting Rooms II | Min-heap custom |
| LC 973 | K Closest Points | Max-heap custom |
| LC 692 | Top K Frequent Words | Custom comp (freq+lex) |
| LC 1235 | Maximum Profit in Job Scheduling | Sort by end |
| CSES | Movie Festival | Sort by end time |
| CF 1A | Theatre Square | Custom math |

---

## Common Mistakes

1. **Comparator dengan `<=` (bukan `<`)** → Violates strict weak ordering → undefined behavior!
2. **`operator<` yang tidak consistent** → `a<b` dan `b<a` keduanya true → UB
3. **Priority queue arah terbalik** → `priority_queue` default adalah max-heap. Untuk min-heap, gunakan `greater<T>` atau invert comparator
4. **Lambda capture yang expired** → Lambda yang capture reference ke variabel lokal yang sudah tidak ada
5. **Functor state mutable** → Comparator tidak boleh punya state yang berubah antar-panggilan (tidak deterministic)

---

## Quick Cheatsheet

```cpp
// operator< (auto-sort)
struct Point { int x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

// Lambda comparator
sort(v.begin(), v.end(), [](const T& a, const T& b){
    if (a.key1 != b.key1) return a.key1 < b.key1;
    return a.key2 < b.key2;
});

// Functor struct
struct Comp {
    bool operator()(const T& a, const T& b) const {
        return a.val < b.val;
    }
};

// Min-heap via priority_queue
priority_queue<T, vector<T>, Comp> pq;
// atau: priority_queue<T, vector<T>, greater<T>> pq;

// Custom set
set<T, Comp> s;
```
