# Day 13 — Bitmask Enumeration

## Tujuan Pembelajaran

Setelah menyelesaikan Day 13, kamu akan mampu:

- [ ] Memahami representasi himpunan sebagai bitmask
- [ ] Menguasai semua operator bitwise: `&`, `|`, `^`, `~`, `<<`, `>>`
- [ ] Melakukan operasi set/clear/toggle/check bit secara efisien
- [ ] Menggunakan `__builtin_popcount`, `__builtin_ctz`, `__builtin_clz`
- [ ] Mengiterasi semua subset dari n elemen dalam O(2^n)
- [ ] Mengiterasi semua subset dari suatu mask dalam O(subset)
- [ ] Memahami kompleksitas O(3^n) untuk enumerasi subset-of-subset
- [ ] Menerapkan bitmask untuk Subset Sum dan intro Bitmask DP

---

## Struktur Folder

```
Day-13 (Bitmask Enumeration)/
├── README.md               ← Panduan ini
├── teori/
│   ├── Day_13_Teori_Lengkap.md     ← Teori lengkap (Markdown)
│   ├── generate_presentation.py    ← Script generate PPT
│   └── Day_13_Presentation.pptx   ← PPT (setelah script dijalankan)
├── latihan/
│   ├── exercise_1.cpp   (Warm-up : Bit Operations Dasar)
│   ├── exercise_2.cpp   (Core    : Check Subset)
│   ├── exercise_3.cpp   (Core    : Print Semua Subset)
│   ├── exercise_4.cpp   (Challenge: Subset Sum)
│   ├── exercise_5.cpp   (Challenge: Enumerate Subsets of Mask)
│   └── exercise_6.cpp   (Contest : Hamiltonian Path / Bitmask DP)
├── solusi/
│   ├── solution_1.cpp   through   solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Starter template dengan bitmask macros
```

---

## Panduan Belajar

### Langkah 1 — Lihat Presentasi
```bash
cd teori/
python3 generate_presentation.py   # Generate Day_13_Presentation.pptx
```
Buka `Day_13_Presentation.pptx` dan pelajari:
- Visualisasi bit diagram per operasi
- Trace tabel iterasi subset
- Pola CP bitmask

### Langkah 2 — Baca Teori Lengkap
Buka `teori/Day_13_Teori_Lengkap.md` untuk teori detail dengan contoh kode.

### Langkah 3 — Kerjakan Latihan
Buka `latihan/exercise_X.cpp`, baca soal di komentar, lalu implementasikan sendiri di bagian `TODO`.

```bash
# Compile dan jalankan exercise
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1
```

**Urutan yang direkomendasikan**: exercise_1 → 2 → 3 → 4 → 5 → 6

### Langkah 4 — Cek Solusi
Jika stuck >30 menit, buka `solusi/solution_X.cpp` untuk referensi.

### Langkah 5 — Kerjakan Tugas
Kerjakan 15 soal di `tugas/` secara mandiri. **Tidak ada solusi** — ini untuk mengukur pemahamanmu.

---

## Quick Reference — Cheatsheet Bitmask

```cpp
// === OPERASI DASAR ===
int mask = 0b1010;   // mask = 10 dalam desimal

// Cek bit ke-i (0-indexed dari kanan)
bool isSet = (mask >> i) & 1;      // atau: BIT(mask, i)

// Set bit ke-i menjadi 1
mask = mask | (1 << i);            // atau: SETBIT(mask, i)

// Clear bit ke-i menjadi 0
mask = mask & ~(1 << i);           // atau: CLRBIT(mask, i)

// Toggle bit ke-i
mask = mask ^ (1 << i);            // atau: TOGBIT(mask, i)

// Hitung jumlah bit aktif
int cnt = __builtin_popcount(mask); // atau: POPCOUNT(mask)

// Lowest set bit (nilai, bukan indeks)
int low = mask & -mask;            // atau: LOWBIT(mask)

// Hapus lowest set bit
mask = mask & (mask - 1);

// === ITERASI SUBSET ===
int n = 4;

// Semua subset dari {0,1,...,n-1}:
for (int mask = 0; mask < (1 << n); mask++) {
    // proses mask...
}

// Semua subset dari mask tertentu:
for (int sub = mask; sub > 0; sub = (sub-1) & mask) {
    // proses sub...
}
// Jangan lupa: sub=0 (empty set) tidak masuk loop, proses manual jika perlu

// === BUILTIN FUNCTIONS ===
__builtin_popcount(x)   // jumlah bit 1 (int)
__builtin_popcountll(x) // jumlah bit 1 (long long)
__builtin_ctz(x)        // count trailing zeros (indeks lowest set bit)
__builtin_clz(x)        // count leading zeros
__builtin_parity(x)     // 1 jika jumlah bit 1 ganjil, 0 jika genap
```

---

## Kompleksitas

| Operasi | Kompleksitas |
|---------|-------------|
| Operasi bit tunggal (set/clear/check) | O(1) |
| Iterasi semua subset dari n elemen | O(2^n) |
| Iterasi subset dari suatu mask | O(jumlah subset mask) |
| Total iterasi subset-of-subset semua mask | O(3^n) |
| Bitmask DP (n state, m transisi) | O(n × 2^n) |

> **Batasan praktis**: n ≤ 20 untuk O(2^n), n ≤ 15 untuk O(n × 2^n) dengan konstanta besar.

---

## Soal Online Judge

### CSES Problem Set
- [Counting Rooms](https://cses.fi/problemset/task/1192) — prerequisite BFS
- [Hamiltonian Flights](https://cses.fi/problemset/task/1690) — bitmask DP
- [Elevator Rides](https://cses.fi/problemset/task/1653) — bitmask DP

### Codeforces
- [CF 1446C — Xor Tree](https://codeforces.com/problemset/problem/1446/C)
- [CF 327E — Axis Walking](https://codeforces.com/problemset/problem/327/E) — subset sum bitmask

### LeetCode
- [78. Subsets](https://leetcode.com/problems/subsets/)
- [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)

---

## Common Mistakes

1. **Integer overflow saat shift**: Gunakan `1LL << i` jika i >= 31
2. **n=32 overflow**: `1 << 32` adalah UB di C++, gunakan `1LL << 32`
3. **Lupa empty set di subset iteration**: loop `sub > 0` skip sub=0
4. **Salah urutan operator**: `&` dan `|` punya preseden lebih rendah dari `==`
   - Salah: `if (mask & 1 == 0)` → harus `if ((mask & 1) == 0)`

---

## Checklist Penyelesaian

- [ ] Menonton/membaca semua materi teori
- [ ] Menyelesaikan exercise_1 (bit operations)
- [ ] Menyelesaikan exercise_2 (check subset)
- [ ] Menyelesaikan exercise_3 (print semua subset)
- [ ] Menyelesaikan exercise_4 (subset sum)
- [ ] Menyelesaikan exercise_5 (enumerate subsets of mask)
- [ ] Mencoba exercise_6 (bitmask DP)
- [ ] Mengerjakan minimal 10 dari 15 tugas
- [ ] Mencoba minimal 1 soal online judge
