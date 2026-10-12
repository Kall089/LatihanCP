# Day 49 — Lower/Upper Bound Manual & Off-by-One Trap

> **Ide satu kalimat:** hafalkan **satu** kerangka, lalu setiap soal binary search cuma menyisakan satu pertanyaan — *apa predikat monotonnya?*

---

## Tujuan Pembelajaran

- [ ] Menulis `lower_bound` dan `upper_bound` dari nol tanpa ragu
- [ ] Menyatakan **invariant** dan memakainya untuk membuktikan kebenaran
- [ ] Memakai kerangka **"first true"** yang menghapus seluruh kelas bug
- [ ] Menjelaskan kenapa `lo + (hi − lo) / 2` bukan sekadar gaya
- [ ] Menjelaskan kenapa loop selalu berhenti — dan kapan ia berputar selamanya
- [ ] Menurunkan **hitungan rentang** dari kedua bound
- [ ] Tahu jebakan `std::lower_bound` pada `set`

---

## Struktur Folder

```
Day-49 (Lower dan Upper Bound Manual serta Off-by-One Trap)/
├── README.md
├── teori/Day_49_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Kerangka "first true"** (bagian 1). Ini satu-satunya hal yang perlu kamu hafal
   dari seluruh topik binary search.
2. **Bagian invariant** — kenapa kerangka itu benar, dan kenapa loopnya berhenti.
3. **Trace 4.4 dan 4.5** — overflow yang nyata, dan loop tak berujung pada varian
   "last true". Keduanya pendek tetapi menjelaskan aturan yang sering dihafal tanpa
   dipahami.

### Langkah 2 — Template (10 menit)

Satu hal yang harus jadi refleks:

```cpp
int lo = 0, hi = n;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (p(mid)) hi = mid;
    else        lo = mid + 1;
}
// lo = indeks PERTAMA yang p true (atau n)
```

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Bound Manual | Easy | 15 mnt | kerangka, `[lo, hi)` |
| 2 | Hitung Rentang Nilai | Easy | 10 mnt | `ub(R) − lb(L)`, wajib sort |
| 3 | Nilai Terdekat | Medium | 20 mnt | dua kasus tepi |
| 4 | Predikat Non-Perbandingan | Medium | 25 mnt | ruang **nilai**, overflow |
| 5 | Pasangan Selisih Terbatas | Hard | 20 mnt | dua tempat overflow |
| 6 | Penjadwalan Tiket | Hard | 25 mnt | multiset, jebakan `std::` |

Exercise 4 adalah jembatan ke Day 50: kerangka yang sama, tetapi ruang pencariannya
nilai jawaban. Di sana `lo + (hi − lo) / 2` berhenti menjadi kebiasaan baik dan
menjadi **keharusan**.

### Langkah 4 — Tugas

**01–05** terapan langsung (LC 35, LC 34, CF 600B, UVa 10611).
**06–10** varian (CSES 1620, CSES 1091, LC 658).
**11–15** level kontes (SPOJ AGGRCOW, LC 33, LC 4, LC 378).

---

## Cheatsheet

```
SATU KERANGKA (first true), konvensi [lo, hi), hi = n:
  while (lo < hi) {
      mid = lo + (hi - lo) / 2;
      if (p(mid)) hi = mid;        mid MUNGKIN jawabannya
      else        lo = mid + 1;    mid PASTI bukan
  }

  lower_bound -> p(i) = (a[i] >= x)
  upper_bound -> p(i) = (a[i] >  x)      bedanya SATU KARAKTER

INVARIANT: indeks < lo semuanya FALSE, indeks >= hi semuanya TRUE

TURUNAN
  jumlah == x       : ub(x) - lb(x)
  jumlah di [L, R]  : ub(R) - lb(L)
  x ada?            : lb != n && a[lb] == x
  terakhir <= x     : ub(x) - 1     cek != 0 DULU
  terakhir <  x     : lb(x) - 1     cek != 0 DULU
  terkecil >= x     : a[lb(x)]      cek != n DULU

"last true": mid = lo + (hi - lo + 1) / 2   <- BULATKAN KE ATAS
  (kalau memakai lo = mid, tanpa +1 loopnya TAK BERUJUNG)

set/map: s.lower_bound(x)  O(log n)   BENAR
         std::lower_bound(s.begin(), ...)  O(n)  -> TLE SENYAP
multiset: s.erase(it) hapus SATU; s.erase(nilai) hapus SEMUA

array MENURUN: greater<>()
array TIDAK TERURUT: hasilnya sampah TANPA error
```

---

## Common Mistakes

1. **Tidak cek `i < n`** sebelum `a[i]`. Kedua bound bisa mengembalikan `n`.
2. **Tidak cek `i != 0`** sebelum `a[i-1]`.
3. **`(lo + hi) / 2`** pada rentang besar → overflow.
4. **Mencampur konvensi `[lo, hi)` dan `[lo, hi]`.**
5. **`lo = mid` tanpa pembulatan ke atas** → loop tak berujung.
6. **`std::lower_bound` pada `set`** → O(n), TLE senyap.
7. **Array tidak diurutkan** → jawaban sampah tanpa error.
8. **`s.erase(nilai)`** menghapus **semua** salinan.
9. **Mengira `lower_bound` mencari nilai `x`** — ia mencari **posisi**.

---

## Checklist Sebelum Lanjut ke Day 50/51

- [ ] Bisa menulis kerangka first-true dari ingatan dalam < 30 detik
- [ ] Bisa menjelaskan invariantnya
- [ ] Bisa menjelaskan kenapa loopnya pasti berhenti
- [ ] Selalu menguji tiga kasus: `x` di bawah semua, di atas semua, tidak ada di tengah
- [ ] Tahu jebakan `std::lower_bound` pada `set`
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (LC 35 dan CSES 1091 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 35 — Search Insert Position](https://leetcode.com/problems/search-insert-position/) | LeetCode | `lower_bound` murni |
| [LC 34 — First and Last Position](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) | LeetCode | kedua bound |
| [LC 33 — Search in Rotated Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | LeetCode | binary search termodifikasi |
| [LC 658 — Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) | LeetCode | bound + jendela |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | multiset |
| [CSES 1620 — Factory Machines](https://cses.fi/problemset/task/1620) | CSES | binary search jawaban |
| [CF 600B — Queries about less or equal](https://codeforces.com/problemset/problem/600/B) | Codeforces | `upper_bound` |
| [UVa 10611 — The Playboy Chimp](https://onlinejudge.org/) | UVa | kasus tepi |
| [SPOJ AGGRCOW](https://www.spoj.com/problems/AGGRCOW/) | SPOJ | binary search jawaban |

---

## Preview Day 50 dan Day 51

Day 50 (sudah kamu selesaikan) memakai kerangka ini pada **ruang jawaban**.
Day 51 memakainya pada **bilangan real**, di mana `lo == hi` tidak pernah tercapai
sehingga kriteria berhentinya harus diganti — dan di sana muncul kelas jebakan
baru: presisi.
