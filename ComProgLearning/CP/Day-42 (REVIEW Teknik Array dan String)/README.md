# Day 42 — REVIEW Teknik Array & String

> **Ide satu kalimat:** hari review yang benar bukan membaca ulang catatan,
> tapi memproduksi jawaban tanpa label lalu mendiagnosis di mana kamu tersendat.

---

## Yang membuat hari ini berbeda

**Semua soal di folder ini tidak berlabel topik.** Header-nya bertuliskan
`Topic: ❓ DIRAHASIAKAN`. Itu disengaja.

Selama Day 29–41, soal selalu datang dengan konteks: kamu tahu soal di folder
Day 36 pasti monotonic stack sebelum membacanya. Itu membuat latihan terasa
lancar, tapi melewatkan keterampilan yang sebenarnya menentukan di kontes —
**mengenali teknik dari kalimat soal**.

Hari ini menutup celah itu. Kamu menebak dulu, mengerjakan, lalu mencocokkan
dengan `solusi/KUNCI_TOPIK.md` yang memberitahu hari mana yang perlu diulang
kalau tebakanmu meleset.

---

## Tujuan Pembelajaran

- [ ] Mengenali teknik dari soal tanpa label, minimal 12 dari 21 soal
- [ ] Menuliskan **delapan invariant** Day 29–40 dari ingatan
- [ ] Memakai tabel diagnosis WA/TLE untuk menemukan bug tanpa menebak-nebak
- [ ] Menulis stress test dan menemukan minimal satu bug lewat itu
- [ ] Memutuskan sendiri: siap ke Day 43, atau ada hari yang perlu diulang

---

## Struktur Folder

```
Day-42 (REVIEW Teknik Array dan String)/
├── README.md
├── teori/Day_42_Teori_Lengkap.md      <- peta + tabel diagnosis
├── latihan/exercise_1.cpp .. exercise_6.cpp     <- TANPA label topik
├── solusi/
│   ├── solution_1.cpp .. solution_6.cpp         <- topik + diagnosis diri
│   └── KUNCI_TOPIK.md                <- 🔒 jangan dibuka sebelum mencoba
├── tugas/tugas_01.cpp .. tugas_15.cpp           <- TANPA label topik
└── template/template.cpp             <- kerangka stress test + checklist
```

---

## Panduan Belajar

### Langkah 0 — Uji ingatan (10 menit, sebelum apa pun)

Tutup semua file. Di kertas, tulis **delapan invariant** ini dari ingatan:

```
prefix sum · difference array · two pointers · window variabel
kadane · monotonic stack · monotonic deque · prefix + map
```

Untuk masing-masing, satu kalimat: *"di awal tiap iterasi, X berarti ___"*.

Cocokkan dengan tabel di `teori/` bagian 1. Yang tidak bisa kamu tulis adalah
teknik yang belum benar-benar kamu miliki — apa pun perasaanmu tentangnya.
Catat hasilnya; ini baseline-mu.

### Langkah 1 — Latihan tanpa label (120 menit)

Enam soal, semuanya bercerita, semuanya tanpa label. Untuk setiap soal,
**isi dua baris ini di file sebelum menulis kode**:

```cpp
// TEKNIK SAYA: ______________________
// ALASAN     : ______________________
```

Baris "alasan" itu yang penting. Kalau alasanmu "kayaknya sih", tebakanmu
belum berbasis sinyal — dan itu informasi diagnostik yang berharga.

| # | Judul | Tingkat | Target |
|---|-------|---------|--------|
| 1 | Pemanas Gedung | Easy | 15 mnt |
| 2 | Pasangan Hari Genap | Medium | 20 mnt |
| 3 | Rute Pendakian Terbaik | Easy | 15 mnt |
| 4 | Menunggu Hari Lebih Panas | Medium | 25 mnt |
| 5 | Pasangan Kabel | Medium | 20 mnt |
| 6 | Keranjang Buah | Hard | 30 mnt |

Exercise 3 dan 5 sengaja diletakkan berdekatan. Keduanya kelihatan mirip,
tapi yang satu **tidak boleh** diurutkan dan yang satu **boleh**. Kalau kamu
menangkap perbedaannya sendiri, itu tanda pengenalan polamu sudah terbentuk.

### Langkah 2 — Cocokkan dan diagnosis (20 menit)

Baru sekarang buka `solusi/KUNCI_TOPIK.md`.

Hitung berapa banyak yang **tekniknya** salah tebak — bukan yang
implementasinya bug, itu masalah berbeda dan penanganannya juga berbeda.

Setiap file solusi punya bagian `🩺 DIAGNOSIS DIRI` yang memetakan gejala
spesifik ke hari yang perlu diulang. Baca bagian itu meski tebakanmu benar.

### Langkah 3 — Baca teori, tapi hanya bagian yang relevan (30 menit)

`teori/Day_42_Teori_Lengkap.md` bukan untuk dibaca dari awal ke akhir.
Pakai sesuai hasil diagnosis:

| Gejalamu | Baca bagian |
|---|---|
| Salah menebak teknik | Bagian 5 — enam frasa penentu, tiga pasangan yang tertukar |
| Menebak benar, implementasi bug | Bagian 2 — tabel diagnosis WA |
| Solusi benar tapi TLE | Bagian 2 — tabel diagnosis TLE |
| Tidak tahu harus mulai dari mana | Bagian 4 — satu array, enam pertanyaan |

### Langkah 4 — Tugas (15 soal, simulasi kontes)

Semuanya tanpa label, diurutkan kasar dari mudah ke sulit, dan diambil dari
judge nyata (CSES, LeetCode, Codeforces). Setiap tugas punya **4 sample test
case** dengan penjelasan.

**Cara paling berguna mengerjakannya:** ambil 5 soal acak, set timer 90 menit,
kerjakan seperti kontes. Baru setelah waktunya habis, cocokkan dengan kunci.
Mengerjakan berurutan tanpa batas waktu tidak melatih hal yang sama.

Beberapa pasangan sengaja diletakkan untuk dibandingkan:

- **tugas 04 vs 13** — "subarray terpendek dengan jumlah ≥ K", satu tanpa
  negatif dan satu dengan. Tekniknya berbeda total. Ini pasangan paling
  instruktif di seluruh hari ini.
- **tugas 02 vs 03** — dua soal two pointers yang polanya berbeda
  (mencocokkan dua daftar vs greedy dari dua ujung).
- **tugas 06 vs 07** — monotonic stack lurus vs melingkar.

---

## Kriteria Lulus

Kamu siap masuk **Day 43 (Sorting)** kalau ketiganya terpenuhi:

- [ ] Bisa menulis minimal 6 dari 8 invariant dari ingatan
- [ ] Menebak teknik dengan benar untuk minimal 4 dari 6 latihan
- [ ] Menyelesaikan minimal 8 dari 15 tugas

Kalau belum, `solusi/KUNCI_TOPIK.md` bagian akhir memberi panduan spesifik
berdasarkan **pola** kesalahanmu, bukan sekadar jumlahnya. Ulangi hari yang
paling sering muncul di kolom terakhir — jangan mengulang seluruh blok.

---

## Cheatsheet Diagnosis

```
GEJALA WA
  salah saat semua negatif         -> best = 0
  salah saat n = 1                 -> loop mulai dari indeks salah
  meleset persis 1                 -> off-by-one / tertutup vs setengah terbuka
  salah saat ada nilai kembar      -> < vs <= pada monotonic stack
  salah saat ada elemen 0          -> mengira 0 itu negatif
  salah hanya pada input negatif   -> % memberi sisa negatif
  benar di sampel, salah di besar  -> overflow int

GEJALA TLE
  terasa O(n) tapi TLE             -> unordered_map kena anti-hash
  while di dalam for               -> tiap elemen keluar berapa kali?
  loop bersarang                   -> ada yang di-rebuild per iterasi?

ENAM FRASA PENENTU
  "ada berapa banyak"              -> prefix + map / counting
  "setelah semua operasi"          -> difference array
  "untuk setiap i, cari terdekat"  -> monotonic stack
  "untuk setiap jendela ukuran k"  -> monotonic deque / window tetap
  "terpanjang / terpendek yang..."  -> window variabel / two pointers
  "maksimum jumlah suatu segmen"   -> Kadane
```

---

## Link Soal Latihan Campuran

Kolom teknik sengaja diberi pemisah `‖` — tutup dengan jari sampai kamu
selesai mencoba.

| Soal | Platform | ‖ Teknik |
| ---- | -------- | -------- |
| [CSES 1084 — Apartments](https://cses.fi/problemset/task/1084) | CSES | ‖ sorting + two pointers |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | ‖ two pointers greedy |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | ‖ multiset |
| [CSES 1620 — Factory Machines](https://cses.fi/problemset/task/1620) | CSES | ‖ binary search on answer |
| [LC 209 — Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | LeetCode | ‖ two pointers |
| [LC 525 — Contiguous Array](https://leetcode.com/problems/contiguous-array/) | LeetCode | ‖ transformasi + prefix map |
| [LC 739 — Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | LeetCode | ‖ monotonic stack |
| [LC 901 — Online Stock Span](https://leetcode.com/problems/online-stock-span/) | LeetCode | ‖ monotonic stack |
| [LC 503 — Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) | LeetCode | ‖ mono stack melingkar |
| [LC 76 — Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | LeetCode | ‖ window + counting |
| [LC 862 — Shortest Subarray with Sum ≥ K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/) | LeetCode | ‖ prefix + deque |
| [LC 480 — Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) | LeetCode | ‖ multiset |
| [CF 279B — Books](https://codeforces.com/problemset/problem/279/B) | Codeforces | ‖ two pointers |

---

## Preview Day 43 — Sorting O(n²)

Blok berikutnya (Day 43–56) tentang **sorting dan searching**, dan puncaknya
adalah *binary search on answer* di Day 50 — salah satu teknik dengan rasio
kegunaan-per-kerumitan tertinggi di seluruh CP.

Benang merahnya menyambung langsung dari blok ini. Day 29–42 melatih
*"kunci satu ujung, lalu manfaatkan monotonisitas"*. Binary search on answer
adalah pola yang sama, hanya yang dikunci bukan indeks, melainkan
**jawabannya sendiri**.
