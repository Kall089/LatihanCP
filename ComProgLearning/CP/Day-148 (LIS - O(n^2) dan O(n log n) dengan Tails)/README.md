# Day 148 — LIS: O(n²) dan O(n log n) dengan Tails

> **Ide satu kalimat:** `tails[k]` adalah **ekor terkecil** di antara semua subsekuens naik berpanjang `k+1` — dan begitu kamu percaya kalimat itu, `lower_bound` melakukan sisanya.

---

## Tujuan Pembelajaran

- [ ] Menulis LIS `O(n²)` dan menjelaskan definisi `dp[i]`-nya
- [ ] Menulis LIS `O(n log n)` dengan `tails` dan `lower_bound` dalam < 2 menit
- [ ] Menjelaskan **apa isi array `tails`** — dan kenapa ia **bukan** LIS-nya
- [ ] Membuktikan bahwa `tails` selalu **terurut menaik**
- [ ] Membedakan **strictly increasing** (`lower_bound`) dan **non-decreasing** (`upper_bound`)
- [ ] **Merekonstruksi** salah satu LIS yang sah
- [ ] Menghitung **banyaknya** LIS (butuh Fenwick, Day 170)
- [ ] Mengenali LIS yang menyamar: box stacking, Russian doll, LDS, patience sorting

---

## Struktur Folder

```
Day-148 (LIS - O(n^2) dan O(n log n) dengan Tails)/
├── README.md
├── materi.md
├── teori/Day_148_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (50 menit)

1. **Bagian 3** — versi `O(n²)` dulu. Kamu harus bisa menulisnya sebelum
   menyentuh versi cepat.
2. **Bagian 4** — arti `tails`. Baca sampai kamu bisa menjelaskannya ke orang
   lain tanpa melihat kode. Ini inti hari ini.
3. **Bagian 4.4** — kenapa `tails` **bukan** LIS, meskipun panjangnya benar.

### Langkah 2 — Template (10 menit)

```cpp
vector<int> tails;
for (int x : a) {
    auto it = lower_bound(tails.begin(), tails.end(), x);   // KETAT naik
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}
// panjang LIS = tails.size()
```

Ganti `lower_bound` → `upper_bound` untuk versi **tidak menurun**.

### Langkah 3 — Latihan (140 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | LIS O(n²) | Easy | 20 mnt | dp "berakhir di i" |
| 2 | LIS O(n log n) | Medium | 20 mnt | tails + lower_bound |
| 3 | Ketat vs Tidak Menurun | Medium | 20 mnt | lower vs upper bound |
| 4 | Rekonstruksi LIS | Medium | 30 mnt | parent + posisi di tails |
| 5 | Menghitung Banyak LIS | Hard | 30 mnt | dp panjang + dp jumlah |
| 6 | Menumpuk Kotak (LIS Menyamar) | Hard | 30 mnt | sorting + tie-break terbalik |

### Langkah 4 — Tugas

**01–05** dasar (LC 300, 674, CSES 1145, AtCoder DP-Q).
**06–10** varian (LDS, LIS non-decreasing, rekonstruksi, russian doll).
**11–15** level kontes (banyak LIS, LIS 2D, partisi Dilworth, patience sorting).

---

## Cheatsheet

```
VERSI O(n^2) — definisi "BERAKHIR TEPAT DI i"
  dp[i] = panjang LIS yang berakhir tepat di i
  dp[i] = 1 + max(dp[j]) untuk semua j < i dengan a[j] < a[i]   (0 kalau tidak ada)
  jawaban = max atas SELURUH dp   <-- bukan dp[n-1]

VERSI O(n log n) — tails
  tails[k] = EKOR TERKECIL di antara semua subsekuens naik berpanjang k+1
  tails SELALU terurut menaik (bukan kebetulan -- lihat teori 4.2)
  untuk tiap x: cari posisi p = lower_bound(tails, x)
      p == tails.size()  -> push_back(x)   (LIS memanjang)
      selain itu         -> tails[p] = x   (ekor panjang p+1 jadi lebih kecil)
  panjang LIS = tails.size()

  !!! tails BUKAN LIS-nya. Panjangnya benar, ISINYA belum tentu subsekuens
      yang sah. Untuk mendapat LIS-nya, rekonstruksi dengan parent[].

KETAT vs TIDAK MENURUN
  strictly increasing (a < b)   -> lower_bound   (gantikan yang >= x)
  non-decreasing      (a <= b)  -> upper_bound   (gantikan yang >  x)
  Uji dengan [1,1,1]: ketat -> 1, tidak menurun -> 3

TURUNAN LANGSUNG
  LDS (menurun terpanjang)       : balik array, atau negasikan nilainya
  LIS pada nilai besar/negatif   : tails menyimpan NILAI, jadi tidak masalah
  jumlah minimum barisan naik    : = panjang LDS (teorema Dilworth)
  patience sorting               : tails = tumpukan kartu; ini asal-usulnya

MENGHITUNG BANYAK LIS
  butuh (panjang, jumlah) per posisi
  O(n^2): dua array, gabungkan saat panjang sama
  O(n log n): Fenwick atas nilai terkompresi, menyimpan (maxLen, count)

LIS YANG MENYAMAR
  box stacking / russian doll : urutkan w menaik, h MENURUN saat w sama,
                                lalu LIS pada h   <-- tie-break TERBALIK,
                                supaya dua kotak selebar sama tidak keduanya terpakai
  jalur terpanjang di DAG     : edge i->j bila i<j dan a[i]<a[j]  (Day 120)

OVERFLOW & TIPE
  nilai boleh negatif -> jangan pakai sentinel 0
  banyak LIS -> modulo 1e9+7
```

---

## Common Mistakes

1. **Mengira `tails` adalah LIS-nya.** Panjangnya benar; isinya tidak.
2. **`lower_bound` vs `upper_bound` tertukar** → jawaban meleset pada elemen kembar.
3. **Jawaban `O(n²)` diambil dari `dp[n-1]`** padahal definisinya "berakhir tepat di i".
4. **`vector` `tails` tidak dibersihkan** antar test case.
5. **Box stacking tanpa tie-break menurun** → dua kotak dengan lebar sama ikut terhitung.
6. **Rekonstruksi dengan mengembalikan isi `tails`** → barisan yang tidak sah.
7. **Menghitung banyak LIS dengan menjumlahkan sembarangan** tanpa memisahkan per panjang.
8. **Lupa bahwa `a[i]` boleh negatif** dan memakai `0` sebagai nilai netral.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis kedua versi dari ingatan
- [ ] Bisa menjelaskan arti `tails[k]` dalam satu kalimat
- [ ] Bisa membuktikan `tails` terurut menaik
- [ ] Tahu kapan `lower_bound` dan kapan `upper_bound`
- [ ] Bisa merekonstruksi salah satu LIS
- [ ] Bisa mengenali box stacking sebagai LIS
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (LC 300 dan CSES 1145 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 300 — Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | LeetCode | dasar |
| [LC 673 — Number of LIS](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) | LeetCode | menghitung |
| [LC 354 — Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) | LeetCode | tie-break terbalik |
| [CSES 1145 — Increasing Subsequence](https://cses.fi/problemset/task/1145) | CSES | n = 2·10^5 |
| [AtCoder DP-Q — Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) | AtCoder | LIS berbobot + BIT |
| [LC 1671 — Minimum Removals to Make Mountain](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/) | LeetCode | LIS dua arah |
| [SPOJ — Longest Common Increasing Subsequence](https://www.spoj.com/problems/LCIS/) | SPOJ | gabung LCS + LIS |

---

## Preview

**Day 149** — LCS dan edit distance: DP di atas **dua** string, di mana
state-nya menjadi dua dimensi. Menariknya, LIS dan LCS punya hubungan: LIS
dari sebuah permutasi sama dengan LCS antara permutasi itu dan `1..n` yang
terurut. **Day 170** (Fenwick) memberi alat untuk versi LIS berbobot dan
penghitungan LIS dalam `O(n log n)`.
