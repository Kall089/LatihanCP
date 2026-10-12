# 📦 Day 3: STL Containers 1 — Vector, String, Pair, Tuple

**Hari**: Day 3 dari 150 Hari Competitive Programming  
**Topik**: STL Containers Dasar (vector, string, pair, tuple)  
**Prerequisites**: Day 1-2 (Setup, tipe data, I/O)  
**Difficulty**: ⭐ (Beginner)

---

## 🎯 Learning Objectives

Setelah menyelesaikan Day 3, kamu harus bisa:
- [ ] Menggunakan `vector` untuk menyimpan data dinamis
- [ ] Memanipulasi `string` dengan operasi CP-friendly
- [ ] Menggunakan `pair` untuk menyimpan dua nilai terkait
- [ ] Menggunakan `tuple` untuk menyimpan tiga atau lebih nilai
- [ ] Memilih container yang tepat untuk masalah yang diberikan
- [ ] Menulis kode C++ yang efisien menggunakan STL containers

---

## 📚 Struktur Folder

```
Day-3 (STL Containers 1 - Vector, String, Pair, Tuple)/
├── teori/
│   └── Day_3_Teori_Lengkap.md   ← Baca ini PERTAMA
├── latihan/
│   ├── exercise_1.cpp  (Warm-up: Vector dasar)
│   ├── exercise_2.cpp  (Warm-up: String manipulation)
│   ├── exercise_3.cpp  (Core: Pair sorting)
│   ├── exercise_4.cpp  (Core: Vector operations)
│   ├── exercise_5.cpp  (Challenge: Kombinasi containers)
│   └── exercise_6.cpp  (Contest-level: Complex data)
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
Buka `teori/Day_3_Teori_Lengkap.md` dan pahami:
1. Vector: deklarasi, operasi, iterasi
2. String: manipulasi, substring, compare
3. Pair: akses `.first`, `.second`, sorting
4. Tuple: `get<>`, `tie()`, `make_tuple()`

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
| 1 | CSES | Distinct Numbers | Vector + Sort |
| 2 | Codeforces | 1807A - Plus or Minus | Basic I/O + String |
| 3 | Codeforces | 4A - Watermelon | Basic pair usage |
| 4 | AtCoder | ABC085B - Kagami Mochi | Vector + unique |
| 5 | Codeforces | 1669A - Division | Vector operations |

---

## ⚠️ Common Mistakes Hari Ini

1. **Akses index out of bounds** — `v[i]` tanpa cek `i < v.size()`
2. **Lupa `resize` atau `reserve`** — akses vector kosong
3. **String compare dengan `==` vs `.compare()`** — di CP biasa `==` cukup
4. **Pair sorting default** — sort by `.first` dulu, baru `.second`
5. **`size()` return `unsigned`** — hati-hati `v.size() - 1` saat vector kosong (underflow!)

---

## ✅ Checklist Sebelum Lanjut ke Day 4

- [ ] Bisa deklarasi dan manipulasi vector tanpa lihat referensi
- [ ] Paham perbedaan `push_back` vs `emplace_back`
- [ ] Bisa sort vector dengan custom comparator
- [ ] Paham kapan pakai pair vs struct
- [ ] Bisa manipulasi string (substr, find, reverse)
- [ ] Sudah selesai minimal 4/6 exercise
- [ ] Sudah coba minimal 5/15 tugas

---

## 👀 Preview Day 4

**Day 4: STL Containers 2 — set, map, unordered_set, unordered_map, multiset**
- Kapan pakai set vs unordered_set?
- Map sebagai frequency counter
- Multiset untuk sorted collection dengan duplikat

---

## 📝 Quick Reference Cheatsheet

```cpp
// === VECTOR ===
vector<int> v(n);          // size n, default 0
vector<int> v(n, val);     // size n, semua = val
v.push_back(x);           // tambah di belakang O(1)
v.pop_back();             // hapus belakang O(1)
v.size();                 // jumlah elemen
v.empty();                // true jika kosong
v.clear();                // hapus semua
sort(v.begin(), v.end()); // sort ascending

// === STRING ===
string s = "hello";
s.size() / s.length();    // panjang string
s.substr(pos, len);       // substring
s.find("lo");             // posisi pertama, npos jika tidak ada
s += "world";             // concatenate
reverse(s.begin(), s.end()); // balik string

// === PAIR ===
pair<int,int> p = {3, 5};
p.first; p.second;        // akses elemen
make_pair(a, b);          // buat pair

// === TUPLE ===
tuple<int,int,int> t = {1, 2, 3};
get<0>(t);                // akses elemen ke-0
auto [a, b, c] = t;      // structured binding (C++17)
tie(a, b, c) = t;        // unpack tuple
```
