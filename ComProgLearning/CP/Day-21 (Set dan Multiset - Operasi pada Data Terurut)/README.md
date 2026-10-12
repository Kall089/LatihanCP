# 📦 Day 4: STL Containers 2 — Set, Map, Unordered_Set, Unordered_Map, Multiset

**Hari**: Day 4 dari 150 Hari Competitive Programming  
**Topik**: STL Associative & Unordered Containers  
**Prerequisites**: Day 3 (vector, string, pair, tuple)  
**Difficulty**: ⭐⭐ (Beginner-Intermediate)

---

## 🎯 Learning Objectives

Setelah menyelesaikan Day 4, kamu harus bisa:
- [ ] Menggunakan `set` untuk menyimpan elemen unik terurut
- [ ] Menggunakan `map` sebagai dictionary (key → value)
- [ ] Memilih `unordered_set`/`unordered_map` saat butuh O(1) average
- [ ] Menggunakan `multiset` untuk koleksi terurut dengan duplikat
- [ ] Mengetahui kapan pakai mana (set vs unordered_set vs multiset)
- [ ] Menerapkan frequency counting dengan map

---

## 📚 Struktur Folder

```
Day-4 (STL Containers 2 - Set, Map, Unordered, Multiset)/
├── teori/
│   └── Day_4_Teori_Lengkap.md   ← Baca ini PERTAMA
├── latihan/
│   ├── exercise_1.cpp  (Warm-up: Set operasi dasar)
│   ├── exercise_2.cpp  (Warm-up: Map frequency count)
│   ├── exercise_3.cpp  (Core: Multiset operations)
│   ├── exercise_4.cpp  (Core: Map + custom logic)
│   ├── exercise_5.cpp  (Challenge: Set intersection/difference)
│   └── exercise_6.cpp  (Contest-level: Complex map usage)
├── solusi/
│   ├── solution_1.cpp ~ solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp ~ tugas_15.cpp (TANPA solusi!)
├── template/
│   └── template.cpp
└── README.md  ← Kamu di sini
```

---

## 📖 Step-by-Step Learning Guide

### Langkah 1: Baca Teori (30-45 menit)
Buka `teori/Day_4_Teori_Lengkap.md` dan pahami:
1. Set vs Multiset vs Unordered_set
2. Map vs Unordered_map
3. Kapan pakai mana (decision tree)
4. Iterator, lower_bound, upper_bound di set/map

### Langkah 2: Kerjakan Exercise (60-90 menit)
- Mulai dari `exercise_1.cpp` (paling mudah)
- Jangan lihat solusi dulu! Coba sendiri minimal 15 menit
- Jika stuck, baca hint di komentar exercise

### Langkah 3: Cek Solusi & Belajar
- Bandingkan kode kamu dengan `solusi/solution_X.cpp`
- Perhatikan approach yang berbeda
- Pahami analisis kompleksitas

### Langkah 4: Kerjakan Tugas (self-practice)
- `tugas/tugas_01-15.cpp` — tanpa solusi!
- Ini untuk mengetes pemahaman kamu

---

## 🔗 Link Soal Online Judge Terkait

| No | Platform | Soal | Topik |
|----|----------|------|-------|
| 1 | CSES | Distinct Numbers | Set |
| 2 | CSES | Concert Tickets | Multiset + lower/upper_bound |
| 3 | CSES | Sum of Two Values | Map/Unordered_map |
| 4 | Codeforces | 4C - Registration System | Map frequency |
| 5 | AtCoder ABC | ABC155D | Map operations |

---

## ⚠️ Common Mistakes Hari Ini

1. **Erase di multiset** — `ms.erase(x)` hapus SEMUA x! Pakai `ms.erase(ms.find(x))` untuk hapus satu
2. **Iterasi sambil erase** — harus `it = s.erase(it)` bukan `s.erase(it); it++`
3. **Unordered container + custom type** — butuh hash function sendiri
4. **Map `[]` operator** — akses key yang tidak ada akan INSERT default value!
5. **Set tidak bisa modify elemen** — harus erase lalu insert yang baru

---

## ✅ Checklist Sebelum Lanjut ke Day 5

- [ ] Paham perbedaan set vs multiset vs unordered_set
- [ ] Bisa pakai map sebagai frequency counter
- [ ] Paham kapan O(log n) acceptable vs butuh O(1)
- [ ] Bisa pakai lower_bound/upper_bound di set
- [ ] Paham bahaya `ms.erase(value)` di multiset
- [ ] Sudah selesai minimal 4/6 exercise
- [ ] Sudah coba minimal 5/15 tugas

---

## 👀 Preview Day 5

**Day 5: STL Containers 3 — stack, queue, deque, priority_queue**
- Stack: LIFO, bracket matching, next greater element
- Queue: FIFO, BFS
- Deque: double-ended, sliding window
- Priority Queue: heap, greedy algorithms

---

## 📝 Quick Reference Cheatsheet

```cpp
// === SET (sorted, unique) ===
set<int> s;
s.insert(x);              // O(log n)
s.erase(x);              // O(log n), hapus elemen x
s.count(x);              // 0 atau 1
s.find(x);               // iterator, atau s.end()
s.lower_bound(x);        // iterator ke >= x
s.upper_bound(x);        // iterator ke > x
*s.begin();              // elemen terkecil
*s.rbegin();             // elemen terbesar

// === MULTISET (sorted, allows duplicates) ===
multiset<int> ms;
ms.insert(x);            // O(log n)
ms.erase(ms.find(x));   // hapus SATU occurrence x
ms.erase(x);            // hapus SEMUA occurrence x!
ms.count(x);            // jumlah x

// === MAP (key → value, sorted by key) ===
map<string, int> m;
m["key"] = value;        // insert/update O(log n)
m.count("key");          // 0 atau 1
m.erase("key");          // hapus
for (auto& [k, v] : m)  // iterasi

// === UNORDERED_MAP (O(1) average) ===
unordered_map<string, int> um;
um["key"] = value;       // O(1) average
um.count("key");         // O(1) average
// Tidak terurut! Iterasi = random order
```
