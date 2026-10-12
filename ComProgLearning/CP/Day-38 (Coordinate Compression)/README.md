# Day 38 — Coordinate Compression

> **Ide satu kalimat:** nilai boleh sampai 10⁹, tapi kalau `n` cuma 10⁵, hanya 10⁵ nilai yang benar-benar ada — beri mereka nomor kursi.

---

## Tujuan Pembelajaran

- [ ] Mengenali tanda soal yang butuh kompresi dalam 10 detik
- [ ] Menulis idiom `sort` + `unique` + `erase` + `lower_bound` tanpa ragu
- [ ] Menjelaskan kenapa `unique` **tidak** menghapus apa pun sendirian
- [ ] Memilih antara kompresi **jenis A** (buang duplikat) dan **jenis B** (peringkat penuh)
- [ ] Memakai `r+1` pada masalah interval dan tahu apa yang rusak tanpanya
- [ ] Menerapkan sweep line berbasis kejadian
- [ ] Menyadari kapan kompresi **tidak** diperlukan

---

## Struktur Folder

```
Day-38 (Coordinate Compression)/
├── README.md
├── teori/Day_38_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (30 menit)

1. **Analogi nomor kursi bioskop** — kenapa kompresi masuk akal.
2. **Bagian "sifat yang dipertahankan"** — kompresi menjaga urutan tapi
   **menghancurkan jarak**. Ini yang membedakan soal yang boleh dikompres dari yang tidak.
3. **Trace 4.2 dan 4.3** — kenapa `erase` wajib, dan kenapa `r+1` wajib.

### Langkah 2 — Template (10 menit)

Salin struct `Kompres` ke template pribadimu. Empat fungsi pendek yang menghilangkan
seluruh kelas bug: lupa `sort`, lupa `erase`, salah `lower_bound`.

### Langkah 3 — Latihan (75 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Kompres Array | Easy | 10 mnt | idiom baku |
| 2 | Frekuensi Nilai Besar | Easy | 15 mnt | verifikasi `v[p] == x` |
| 3 | Peringkat Penuh | Medium | 15 mnt | jenis B, sort indeks |
| 4 | Total Panjang Tertutup | Medium | 15 mnt | sweep, **tanpa** kompresi |
| 5 | Berapa Interval per Titik | Hard | 25 mnt | kejadian `+1`/`−1` di `r+1` |
| 6 | Grid Setelah Pemadatan | Hard | 15 mnt | kompresi 2D murni |

Exercise 4 sengaja **tidak** memerlukan kompresi. Itu bagian dari pelajarannya:
nilai besar tidak otomatis berarti kompresi.

### Langkah 4 — Tugas

**01–05** terapan langsung. **06–10** kompresi bertemu struktur data dan sweep
(CSES 1144, CF 1000C, CF 670C). **11–15** level kontes (SPOJ INVCNT, LC 218).

Tugas 6, 11, dan 14 butuh Fenwick Tree (Day 170). Kerjakan strukturnya sekarang
(kompresi + offline), lalu lengkapi setelah Day 170.

---

## Cheatsheet

```
IDIOM BAKU
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());      <- erase WAJIB
  idx = lower_bound(v.begin(), v.end(), x) - v.begin();

unique() TIDAK menghapus. Ia memindahkan yang unik ke depan; size() tetap.
sort() WAJIB dulu; unique hanya membuang duplikat BERDAMPINGAN.

DIPERTAHANKAN : urutan relatif, kesamaan
HILANG        : jarak / selisih  -> pakai v[peringkat] untuk nilai asli

JENIS A (buang duplikat)  : nilai sama -> peringkat sama   (frekuensi, BIT)
JENIS B (peringkat penuh) : setiap posisi unik             (jadi permutasi)

INTERVAL: masukkan l DAN r+1, pakai setengah terbuka [idx(l), idx(r+1))
SWEEP   : kejadian (l, +1) dan (r+1, -1); sumbangkan per SEGMEN

KUMPULKAN SEMUA nilai (termasuk dari QUERY) sebelum bangun()
TIDAK butuh kompresi kalau cukup sort + bandingkan
```

---

## map atau Kompresi?

| Situasi | Pilih |
| ------- | ----- |
| Struktur diakses sekali-dua kali | `map` — lebih cepat ditulis |
| Struktur diakses berkali-kali (BIT, segtree, DP) | **kompresi** |
| Butuh iterasi berurutan atas nilai | **kompresi** |
| Online, nilai baru muncul di tengah jalan | `map` |
| Codeforces dengan fase hack | hindari `unordered_map` |

---

## Common Mistakes

1. **`unique` tanpa `erase`.** Ukuran tidak berubah, ekornya sampah.
2. **Lupa `sort` sebelum `unique`.**
3. **Query memakai nilai yang tidak ada di kamus.** `lower_bound` mengembalikan posisi
   penyisipan, bukan "tidak ditemukan" — verifikasi `v[p] == x`.
4. **Lupa `r+1` pada interval.** Celah antar interval menghilang.
5. **Kompresi merusak jarak** — kalau menghitung panjang, pakai `v[peringkat]`.
6. **Memakai kompresi padahal tidak perlu.** Menambah kode dan risiko.
7. **`int` untuk nilai `10^9`** muat, tapi jumlahnya tidak.

---

## Checklist Sebelum Lanjut ke Day 39/40

- [ ] Bisa menulis idiom baku dari ingatan dalam < 30 detik
- [ ] Bisa menjelaskan apa yang terjadi kalau `erase` dilupakan
- [ ] Bisa menyebutkan satu soal yang **tidak** butuh kompresi meski nilainya besar
- [ ] Paham kenapa `r+1` diperlukan pada interval
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (ABC 213 C paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [ABC 213 C — Reorder Cards](https://atcoder.jp/contests/abc213/tasks/abc213_c) | AtCoder | kompresi 2D murni |
| [CSES 1144 — Salary Queries](https://cses.fi/problemset/task/1144) | CSES | kompresi + BIT |
| [CF 670C — Cinema](https://codeforces.com/problemset/problem/670/C) | Codeforces | kompresi + hitung |
| [CF 1000C — Covered Points Count](https://codeforces.com/problemset/problem/1000/C) | Codeforces | sweep + `r+1` |
| [LC 218 — The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/) | LeetCode | sweep + multiset |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | kompresi + inversi |

---

## Preview Day 40 — Counting & Frequency Array

Kompresi hari ini adalah **prasyaratnya**. Begitu nilai sudah dikecilkan ke `[0, m)`,
array frekuensi menjadi mungkin — dan array frekuensi adalah senjata paling sederhana
sekaligus paling sering terpakai di CP: mode, anagram, pasangan berselisih K,
counting sort, dan puluhan soal Div3 lain.
