# Day 33 — String Hashing: Polynomial Hash, Rabin-Karp & Collision

> **Ide satu kalimat:** ubah string menjadi **angka**, supaya membandingkan dua potongan cukup satu langkah, bukan mengeja huruf demi huruf.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 33, kamu akan mampu:

- [ ] Menjelaskan cara kerja **polynomial hashing** dan kenapa ia membuat perbandingan jadi O(1)
- [ ] Membangun **prefix hash** lalu mengambil hash substring mana pun dalam **O(1)**
- [ ] Mengimplementasikan **Rabin-Karp** untuk pencarian pola O(n + m)
- [ ] Menghitung peluang **tabrakan** dan menekannya dengan **double hashing**
- [ ] Memakai **base acak** sebagai pengaman dari anti-hash test
- [ ] Menyelesaikan pola klasik: palindrom substring, substring berbeda, substring bersama terpanjang
- [ ] Memutuskan kapan memakai hashing dan kapan lebih baik memakai KMP

---

## Struktur Folder

```
Day-33 (String Hashing)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_33_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Bandingkan Dua Substring)
│   ├── exercise_2.cpp   (Warm-up  : Rabin-Karp Hitung Kemunculan)
│   ├── exercise_3.cpp   (Core     : Palindrom Substring)
│   ├── exercise_4.cpp   (Core     : Menghitung Substring Berbeda)
│   ├── exercise_5.cpp   (Challenge: Substring Berulang Terpanjang)
│   └── exercise_6.cpp   (Contest  : Substring Bersama Terpanjang)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← Hash, HashGanda, Rabin-Karp, HashPalindrom
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori
`teori/Day_33_Teori_Lengkap.md`. Bagian yang wajib dipahami betul:
**analogi nomor punggung** (bagian 1) dan **trace menyamakan bobot** (bagian 4, contoh 3).
Kalau bagian "kenapa dikalikan silang" sudah masuk akal, sisanya akan mudah.

### Langkah 2 — Pelajari Template
`template/template.cpp` berisi empat alat siap pakai:
`struct Hash` (tunggal), `struct HashGanda` (aman), `rabinKarp`, dan `HashPalindrom`.

**Salin `struct Hash` ke template pribadimu.** Menulis ulang saat kontes membuang 5 menit.

### Langkah 3 — Kerjakan Latihan Berurutan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
./latihan/exercise_1 < input.txt
```
Urutannya sengaja menanjak: perbandingan dasar → Rabin-Karp → dua hash sekaligus →
normalisasi hash → binary search + hash → dua string sekaligus.

### Langkah 4 — Cek Solusi (kalau macet > 30 menit)
Semua solusi **sudah diverifikasi**: 18 uji sample lolos, dan keenamnya diuji-stres
melawan brute force sebanyak **1.800 kasus acak** — semua cocok.

### Langkah 5 — Kerjakan 15 Tugas Mandiri
Target minimal **10 dari 15** sebelum lanjut ke Day 34 (KMP).

---

## Quick Reference — Cheatsheet String Hashing

```
RUMUS DASAR
  hash(s) = SUM s[i] * p^i   (mod m)
  p = 131 (prima > alfabet), m = 1e9+9 (prima besar)
  petakan huruf ke 1..26, JANGAN 0..25

PREFIX HASH
  h[i+1] = h[i] + (s[i]-'a'+1) * p[i]
  p[i+1] = p[i] * P

HASH SUBSTRING (mentah, masih berbobot p^l)
  get(l, r) = (h[r+1] - h[l] + M) % M

BANDINGKAN s[a..b] vs s[c..d]   -> kalikan silang, JANGAN membagi
  get(a,b) * p[c] % M  ==  get(c,d) * p[a] % M

NORMALISASI (kalau hash mau dimasukkan ke set / map)
  get(l, r) * p[n - l] % M

KOMPLEKSITAS
  bangun O(n) | ambil hash substring O(1) | bandingkan O(1)

PENGAMAN TABRAKAN
  n > 1e4         -> WAJIB double hashing
  ada fase hack   -> base acak (mt19937_64)
```

---

## Empat Jebakan Terbesar

| Jebakan | Gejala | Perbaikan |
|---|---|---|
| Memetakan 'a' → 0 | "a", "aa", "aaa" semuanya berhash 0 | Pakai `c - 'a' + 1` |
| Lupa `+ M` saat mengurangi | Hasil negatif, jawaban acak | `(h[r+1] - h[l] + M) % M` |
| Lupa normalisasi sebelum masuk set | Substring identik dianggap berbeda | Kalikan `p[n - l]` |
| Satu mod untuk data besar | Tabrakan (paradoks ulang tahun) | Double hashing |

### Kenapa satu mod tidak cukup

Kalau kita membandingkan **semua pasangan** dari k substring, jumlah pasangannya sekitar k²/2:

| Jumlah substring k | Peluang tabrakan (1 mod ≈ 10⁹) |
|---|---|
| 1.000 | ~0,05 % |
| 10.000 | ~5 % |
| 50.000 | ~70 % ⚠️ |
| 100.000 | ~99 % ❌ |

Dengan **double hashing**, peluangnya turun menjadi sekitar 10⁻¹⁸ — praktis nol.

---

## Hashing atau KMP?

```
Cuma cari SATU pola di dalam teks?
├── Ya → KMP (Day 34) — deterministik, tidak ada risiko tabrakan
└── Tidak — perlu membandingkan banyak potongan sembarang
    └── HASHING ✅ — jauh lebih fleksibel
```

Sekali prefix hash dibangun, ia bisa menjawab: apakah dua potongan sama, apakah sebuah
potongan palindrom, berapa substring berbeda, substring bersama terpanjang — semuanya
dari satu struktur yang sama. KMP tidak bisa melakukan itu.

---

## Soal Online Judge Rekomendasi

### CSES
- [String Matching](https://cses.fi/problemset/task/1753) — persis exercise 2
- [Finding Borders](https://cses.fi/problemset/task/1732) — tugas 08
- [Finding Periods](https://cses.fi/problemset/task/1733) — tugas 09
- [Longest Palindrome](https://cses.fi/problemset/task/1111) — hash maju + mundur

### LeetCode
- [28. Find the Index of the First Occurrence](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)
- [1044. Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/) — persis exercise 5
- [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/)
- [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) — tugas 10

### Codeforces
- [CF 271D - Good Substrings](https://codeforces.com/problemset/problem/271/D) — substring berbeda
- [CF 985F - Isomorphic Strings](https://codeforces.com/problemset/problem/985/F) — hashing per huruf

### AtCoder
- [ABC 141E - Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e) — persis exercise 5

---

## Checklist Penyelesaian

- [ ] Membaca teori, terutama trace "menyamakan bobot"
- [ ] Bisa menjelaskan sendiri **kenapa dikalikan silang, bukan dibagi**
- [ ] Bisa menyebutkan **kenapa 'a' dipetakan ke 1, bukan 0**
- [ ] `exercise_1.cpp` — bandingkan dua substring
- [ ] `exercise_2.cpp` — Rabin-Karp
- [ ] `exercise_3.cpp` — palindrom substring (hash maju + mundur)
- [ ] `exercise_4.cpp` — substring berbeda (normalisasi!)
- [ ] `exercise_5.cpp` — binary search + hash
- [ ] `exercise_6.cpp` — dua string sekaligus
- [ ] Minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC **CSES String Matching**
- [ ] Bisa menjelaskan kapan wajib pakai double hashing

---

## Catatan Kompilasi

Berkas yang memakai `unordered_set` menyertakan `#include <unordered_set>` secara eksplisit.
Ini karena `bits/stdc++.h` pada sebagian sistem (termasuk macOS dengan Apple clang)
**tidak** memuat header tersebut. Menuliskannya eksplisit membuat kode tetap jalan
di mesinmu maupun di online judge.

---

**Materi visual pendamping:** buka `learn-cp-visual` → menu **String → String Hashing**.
Lanjutan langsung dari materi ini adalah **Day 34 (KMP)** — versi deterministik yang
tidak punya risiko tabrakan sama sekali.
