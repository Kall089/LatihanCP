# Day 213 — KMP: Prefix Function & Pencarian Pola O(n + m)

> **Ide satu kalimat:** jarimu di teks **tidak pernah mundur**; yang mundur hanyalah "sudah cocok berapa huruf".

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 213, kamu akan mampu:

- [ ] Menjelaskan arti **tabel pi** dengan kalimat sendiri
- [ ] Membangun tabel pi dalam **O(m)** dan menjelaskan kenapa bukan O(m²)
- [ ] Mencari pola dalam **O(n + m)** tanpa memundurkan indeks teks
- [ ] Menemukan **semua border** lewat rantai pi
- [ ] Menghitung **periode terkecil** dengan `n − pi[n−1]`
- [ ] Menghitung **berapa kali tiap prefiks muncul** dalam satu kali jalan
- [ ] Memutuskan kapan memakai KMP dan kapan hashing lebih cocok

---

## Struktur Folder

```
Day-213 (KMP - Prefix Function dan Pencarian Pola)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_213_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Bangun Tabel Pi)
│   ├── exercise_2.cpp   (Warm-up  : Cari Semua Posisi Pola)
│   ├── exercise_3.cpp   (Core     : Border Terpanjang)
│   ├── exercise_4.cpp   (Core     : Periode Terkecil)
│   ├── exercise_5.cpp   (Challenge: Semua Border)
│   └── exercise_6.cpp   (Contest  : Hitung Kemunculan Tiap Prefiks)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← pi, matching, border, periode, automaton, rotasi
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori
`teori/Day_213_Teori_Lengkap.md`. Dua bagian yang paling menentukan:
**analogi mencari kata di buku** (bagian 1) dan **trace membangun pi** (bagian 4).
Kalau kamu sudah paham kenapa `j = pi[j-1]` berarti "geser pola tanpa memundurkan teks",
sisanya akan terasa mudah.

### Langkah 2 — Pelajari Template
`template/template.cpp` berisi delapan bagian siap pakai: `bangunPi`, `cariKMP`,
trik penggabungan, `semuaBorder`, `periodeTerkecil`, `hitungPrefiks`, KMP automaton,
dan turunan seperti cek rotasi.

**Salin `bangunPi` dan `cariKMP` ke template pribadimu** — hanya 15 baris, tapi menghemat
waktu setiap kali ketemu soal string.

### Langkah 3 — Kerjakan Latihan Berurutan
```bash
g++ -O2 -std=c++17 latihan/exercise_1.cpp -o latihan/exercise_1
echo "ababc" | ./latihan/exercise_1
```
Urutannya menanjak: bangun pi → cari pola → border → periode → rantai border →
akumulasi mundur.

### Langkah 4 — Cek Solusi (kalau macet > 30 menit)
Semua solusi **sudah diverifikasi**: 18 uji sample lolos, dan keenamnya diuji-stres
melawan definisi harfiah/brute force sebanyak **2.400 kasus acak** — semua cocok.

### Langkah 5 — Kerjakan 15 Tugas Mandiri
Target minimal **10 dari 15** sebelum lanjut ke Day 214 (Aplikasi Prefix Function).

---

## Quick Reference — Cheatsheet KMP

```
ARTI pi[i]
  panjang awalan TERPANJANG dari p[0..i] yang juga menjadi akhirannya,
  tetapi bukan seluruh potongan itu sendiri

BANGUN pi                                          O(m)
  for (i = 1..m-1) {
      j = pi[i-1];
      while (j > 0 && p[i] != p[j]) j = pi[j-1];
      if (p[i] == p[j]) j++;
      pi[i] = j;
  }

CARI POLA                                          O(n)
  for (i = 0..n-1) {
      while (j > 0 && t[i] != p[j]) j = pi[j-1];
      if (t[i] == p[j]) j++;
      if (j == m) { catat(i - m + 1); j = pi[j-1]; }   // BUKAN j = 0!
  }

TURUNAN LANGSUNG
  border terpanjang = pi[n-1]
  semua border      = rantai k = pi[k-1] sampai 0
  periode terkecil  = n - pi[n-1]
  pengulangan utuh  = periode < n DAN n % periode == 0
  hitung prefiks    = telusuri MUNDUR, cnt[pi[i]-1] += cnt[i]

TRIK GABUNG   pi(pola + '#' + teks), cari nilai == |pola|
```

---

## Enam Jebakan Terbesar

| Jebakan | Gejala | Perbaikan |
|---|---|---|
| `j = 0` saat gagal | Kembali jadi pencarian naif | `j = pi[j-1]` |
| `j = 0` setelah ketemu | Kemunculan tumpang tindih hilang | `j = pi[j-1]` |
| Pemisah bisa muncul di string | Trik penggabungan salah hasil | Pakai `'#'` atau `'\1'` |
| Lupa syarat `periode < n` | "abcd" salah dijawab pengulangan | Cek dua syarat |
| Prefiks dihitung maju | Nilai belum lengkap saat dialirkan | Telusuri **mundur** |
| Border dikira boleh seluruh string | "aaa" dijawab 3, seharusnya 2 | Harus *proper prefix* |

> **Uji dengan `"aaaa"`.** String ini menangkap hampir semua bug KMP sekaligus:
> tumpang tindih, rantai border panjang, dan kesalahan proper prefix.

---

## KMP atau Hashing (Day 211)?

```
Butuh jaminan 100% benar, tanpa peluang tabrakan?
├── Ya → KMP
└── Tidak masalah probabilistik
    ├── Pertanyaannya cuma "cari pola ini" → KMP (lebih rapi)
    └── Pertanyaan bermacam-macam tentang substring sembarang → HASHING
```

Di Codeforces yang punya **fase hacking**, KMP lebih aman karena tidak bisa dipatahkan
oleh anti-hash test.

Sebaliknya, kelebihan hashing: sekali prefix hash dibangun, ia menjawab banyak jenis
pertanyaan tentang substring sembarang. KMP terikat pada satu pola.

---

## Soal Online Judge Rekomendasi

### CSES String Section
- [String Matching](https://cses.fi/problemset/task/1753) — persis exercise 2
- [Finding Borders](https://cses.fi/problemset/task/1732) — persis exercise 5
- [Finding Periods](https://cses.fi/problemset/task/1733) — persis exercise 4

### Codeforces
- [CF 432D - Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) — persis exercise 6
- [CF 1200E - Compress Words](https://codeforces.com/problemset/problem/1200/E) — overlap dua string (tugas 08)
- [CF 471D - MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) — KMP pada selisih

### LeetCode
- [28. Find the Index of the First Occurrence](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)
- [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) — periode
- [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) — trik penggabungan

### AtCoder
- [ABC 150F - Xor Shift](https://atcoder.jp/contests/abc150/tasks/abc150_f) — KMP pada barisan angka

---

## Checklist Penyelesaian

- [ ] Membaca teori, terutama trace membangun pi
- [ ] Bisa menjelaskan sendiri **kenapa membangun pi itu O(n), bukan O(n²)**
- [ ] Bisa menjelaskan **kenapa `j = pi[j-1]` setelah pola ditemukan**
- [ ] `exercise_1.cpp` — bangun tabel pi
- [ ] `exercise_2.cpp` — cari semua posisi pola
- [ ] `exercise_3.cpp` — border terpanjang
- [ ] `exercise_4.cpp` — periode (ingat dua syarat!)
- [ ] `exercise_5.cpp` — semua border lewat rantai
- [ ] `exercise_6.cpp` — hitung prefiks (telusuri mundur!)
- [ ] Minimal 10 dari 15 tugas mandiri
- [ ] Submit & AC **CSES String Matching** dan **Finding Borders**
- [ ] Bisa menjelaskan kapan memilih KMP dan kapan memilih hashing

---

**Materi visual pendamping:** buka `learn-cp-visual` → menu **String → KMP & Pencocokan Pola**
untuk melihat pola bergeser di bawah teks langkah demi langkah, lengkap dengan tabel pi
yang ikut bergerak.

**Posisi di Roadmap:** Day 213 (Algoritma String, Day 211-224).
Lanjut ke Day 214 (Aplikasi Prefix Function: Periode, Border, Automaton) atau Day 215 (Z-Function).
