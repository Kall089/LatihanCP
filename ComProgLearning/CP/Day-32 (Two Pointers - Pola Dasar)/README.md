# Day 19 — Two Pointers

## Deskripsi Topik

**Two Pointers** adalah teknik algoritmik yang menggunakan dua indeks (pointer) untuk menelusuri struktur data secara efisien. Alih-alih menggunakan nested loop O(n²), teknik ini sering menurunkan kompleksitas menjadi O(n) dengan memanfaatkan properti sorted array atau kondisi tertentu.

---

## Tujuan Pembelajaran

- [ ] Memahami konsep dasar two pointers dan kapan menggunakannya
- [ ] Mengimplementasikan **Opposite Direction Pointers** (L dari kiri, R dari kanan, bergerak ke tengah)
- [ ] Menyelesaikan Two Sum pada sorted array dengan O(n)
- [ ] Menyelesaikan Three Sum dengan O(n²) menggunakan outer loop + two pointers
- [ ] Menyelesaikan Container With Most Water dengan greedy two pointers
- [ ] Mengimplementasikan **Same Direction Pointers** (slow-fast pattern)
- [ ] Remove Duplicates in-place dengan slow-fast pointers
- [ ] Menghitung Longest Subarray dengan constraint sum ≤ K
- [ ] Merge dua sorted array dengan O(n+m)
- [ ] Dutch National Flag dengan 3 pointers (low, mid, high)
- [ ] Menganalisis kompleksitas dan menghindari pitfalls umum
- [ ] Mengenali pola mana yang tepat untuk suatu problem

---

## Struktur Folder

```
Day-19 (Two Pointers)/
├── README.md                    ← Panduan ini
├── teori/
│   ├── Day_19_Teori_Lengkap.md  ← Teori lengkap dengan contoh & trace table
│   ├── generate_presentation.py ← Script untuk generate PPT
│   └── Day_19_Presentation.pptx ← (generated)
├── latihan/
│   ├── exercise_1.cpp           ← Two Sum Sorted Array
│   ├── exercise_2.cpp           ← Remove Duplicates In-Place
│   ├── exercise_3.cpp           ← Container With Most Water
│   ├── exercise_4.cpp           ← Three Sum Closest
│   ├── exercise_5.cpp           ← Valid Palindrome
│   └── exercise_6.cpp           ← Merge Two Sorted Arrays
├── solusi/
│   ├── solution_1.cpp           ← Solusi exercise 1
│   ├── solution_2.cpp           ← Solusi exercise 2
│   ├── solution_3.cpp           ← Solusi exercise 3
│   ├── solution_4.cpp           ← Solusi exercise 4
│   ├── solution_5.cpp           ← Solusi exercise 5
│   └── solution_6.cpp           ← Solusi exercise 6
├── tugas/
│   ├── tugas_01.cpp — tugas_15.cpp   ← 15 tugas mandiri
└── template/
    └── template.cpp             ← Template pola two pointers
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)
Baca `teori/Day_19_Teori_Lengkap.md` dari awal hingga akhir. Perhatikan:
- ASCII art pergerakan pointer
- Trace table setiap langkah
- Proof correctness setiap pola

### Langkah 2 — Lihat Presentasi (15 menit)
Generate dan lihat PPT:
```bash
cd teori/
python3 generate_presentation.py
```

### Langkah 3 — Kerjakan Latihan (60–90 menit)
Kerjakan exercise 1–6 **tanpa melihat solusi**. Gunakan `template/template.cpp` sebagai acuan pola.

### Langkah 4 — Cek Solusi
Bandingkan approach kamu dengan solusi di `solusi/`. Perhatikan edge cases yang mungkin kamu lewatkan.

### Langkah 5 — Kerjakan Tugas (90–120 menit)
Pilih minimal 8 dari 15 tugas. Prioritaskan:
- Easy: tugas_01–05 (semua harus dikerjakan)
- Medium: pilih 3 dari tugas_06–10
- Hard: pilih 2 dari tugas_11–15 (tantangan)

### Langkah 6 — Online Judge
Submit ke platform online judge untuk validasi. Lihat rekomendasi soal di bawah.

---

## Ringkasan Latihan

| No | File | Topik | Kesulitan | Konsep Kunci |
|----|------|-------|-----------|--------------|
| 1 | exercise_1.cpp | Two Sum Sorted Array | ★☆☆☆☆ | Opposite direction, sorted pre-condition |
| 2 | exercise_2.cpp | Remove Duplicates In-Place | ★★☆☆☆ | Slow-fast same direction |
| 3 | exercise_3.cpp | Container With Most Water | ★★☆☆☆ | Greedy: move smaller pointer |
| 4 | exercise_4.cpp | Three Sum Closest | ★★★☆☆ | Sort + outer loop + two pointers |
| 5 | exercise_5.cpp | Valid Palindrome | ★★☆☆☆ | Opposite direction + char filter |
| 6 | exercise_6.cpp | Merge Two Sorted Arrays | ★☆☆☆☆ | Two independent pointers, merge |

---

## Ringkasan Tugas (15 Soal)

| No | Topik | Kesulitan | Kategori |
|----|-------|-----------|----------|
| 01 | Count Pairs Sum = K | ★☆☆☆☆ | Easy |
| 02 | Common Element Two Sorted Arrays | ★☆☆☆☆ | Easy |
| 03 | Pair with Sum = 0 | ★☆☆☆☆ | Easy |
| 04 | Squares of Sorted Array | ★★☆☆☆ | Easy |
| 05 | Move Zeros to End | ★★☆☆☆ | Easy |
| 06 | Longest Subarray Sum ≤ K | ★★☆☆☆ | Medium |
| 07 | Two Sum II — Count All Pairs | ★★☆☆☆ | Medium |
| 08 | Sort Colors (Dutch Flag) | ★★★☆☆ | Medium |
| 09 | Four Sum | ★★★☆☆ | Medium |
| 10 | Longest Mountain in Array | ★★★☆☆ | Medium |
| 11 | Trapping Rain Water | ★★★★☆ | Hard |
| 12 | Minimum Window Substring | ★★★★☆ | Hard |
| 13 | K-diff Pairs | ★★★☆☆ | Hard |
| 14 | Palindrome Pairs | ★★★★★ | Hard |
| 15 | Subarray Equal 0s and 1s | ★★★★☆ | Hard |

---

## Rekomendasi Online Judge

### LeetCode
| Problem | Judul | Tingkat |
|---------|-------|---------|
| #167 | Two Sum II – Input Array Is Sorted | Easy |
| #26 | Remove Duplicates from Sorted Array | Easy |
| #11 | Container With Most Water | Medium |
| #15 | 3Sum | Medium |
| #125 | Valid Palindrome | Easy |
| #75 | Sort Colors (Dutch Flag) | Medium |
| #977 | Squares of a Sorted Array | Easy |
| #42 | Trapping Rain Water | Hard |
| #76 | Minimum Window Substring | Hard |
| #16 | 3Sum Closest | Medium |

### CSES (cses.fi)
| Problem | Judul |
|---------|-------|
| 1621 | Distinct Numbers |
| 1640 | Sum of Two Values |
| 1643 | Maximum Subarray Sum |

### Codeforces
| Round | Problem | Topik |
|-------|---------|-------|
| CF 1A | Theatre Square | Warm-up |
| CF 580C | Kefa and Park | Two pointer variant |
| CF 381C | Sereja and Suffixes | Pointer technique |

---

## Kesalahan Umum (Common Mistakes)

1. **Array tidak di-sort** — Two Sum dengan opposite direction HANYA bekerja pada sorted array. Selalu sort dulu jika diperlukan.

2. **Arah pointer terbalik** — Jika `sum < target`, L harus naik (bukan R turun). Logika arah pointer harus konsisten.

3. **Infinite loop** — Pastikan setiap iterasi, minimal satu pointer bergerak. Jangan kondisi di mana keduanya tidak bergerak.

4. **Skip duplikat lupa** — Pada Three Sum, setelah menemukan triplet, skip semua duplikat A[L] dan A[R] sebelum lanjut.

5. **Off-by-one pada boundary** — `while (L < R)` bukan `while (L <= R)` untuk opposite direction. Jika L==R, kita tidak ingin pakai elemen yang sama dua kali.

6. **Slow pointer tidak maju** — Pada slow-fast, slow hanya maju ketika kondisi valid terpenuhi, bukan setiap iterasi.

7. **Tidak handle array kosong atau ukuran 1** — Selalu cek edge cases sebelum menjalankan two pointer.

---

## Quick Reference Cheatsheet

### Pola Two Pointers

```
POLA 1: OPPOSITE DIRECTION
━━━━━━━━━━━━━━━━━━━━━━━━━
Array: [1, 2, 4, 5, 8, 9]
        L              R
Pre-condition: SORTED
Use for: pair sum, palindrome, container water

int L = 0, R = n - 1;
while (L < R) {
    if (found)     break;
    else if (...)  L++;   // need larger value
    else           R--;   // need smaller value
}

─────────────────────────────────────────────

POLA 2: SAME DIRECTION (SLOW-FAST)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Array: [1, 1, 2, 3, 3, 4]
        S
           F→→→→→→→→→→→
Use for: remove duplicates, sliding window

int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (valid(A[fast])) A[slow++] = A[fast];
}

─────────────────────────────────────────────

POLA 3: MERGE TWO ARRAYS
━━━━━━━━━━━━━━━━━━━━━━━━
A: [1, 3, 5]    B: [2, 4, 6]
    i               j

int i = 0, j = 0;
while (i < n && j < m) {
    if (A[i] <= B[j]) out(A[i++]);
    else               out(B[j++]);
}

─────────────────────────────────────────────

POLA 4: THREE POINTERS (DUTCH FLAG)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Array: [0,1,2,1,0,2]
        low  mid    high
Use for: 3-way partition

int low=0, mid=0, high=n-1;
while (mid <= high) {
    if (A[mid]==0) swap(A[low++],A[mid++]);
    else if (A[mid]==1) mid++;
    else swap(A[mid],A[high--]);
}
```

### Keputusan Pola

```
Problem melibatkan PAIR/SUM?
    └─ Array sorted?
        ├─ YES → Opposite Direction Pointers
        └─ NO  → Sort dulu, lalu Opposite Direction

Problem melibatkan SUBARRAY/WINDOW?
    └─ Same Direction (Slow-Fast / Sliding Window)

Problem melibatkan MERGE?
    └─ Two independent pointers, satu per array

Problem melibatkan PARTITION?
    └─ Dutch National Flag (3 pointers)
```

---

## Kompleksitas Algoritma

| Algoritma | Time | Space | Keterangan |
|-----------|------|-------|------------|
| Two Sum Sorted | O(n) | O(1) | Satu scan, dua pointer |
| Three Sum | O(n²) | O(1) | Outer O(n) + inner O(n) |
| Container Water | O(n) | O(1) | Satu scan |
| Remove Duplicates | O(n) | O(1) | Satu scan slow-fast |
| Merge Two Sorted | O(n+m) | O(n+m) | Satu scan per array |
| Dutch Flag | O(n) | O(1) | Satu scan, 3 pointer |
| Trapping Rain Water | O(n) | O(1) | Two pointer dari ujung |

---

*Day 19 — Two Pointers | Competitive Programming Learning*
