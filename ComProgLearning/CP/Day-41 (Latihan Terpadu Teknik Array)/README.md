# Day 41 — Latihan Terpadu Teknik Array

> **Ide satu kalimat:** hari ini kamu tidak belajar alat baru — kamu belajar
> memilih dan menggabungkan sepuluh alat yang sudah kamu punya.

---

## Kenapa hari ini ada

Selama Day 29–40, setiap soal datang dengan label. Kamu tahu soal di folder
Day 35 pasti Kadane sebelum membacanya. Di kontes tidak ada label, dan soal
jarang memakai satu alat saja.

Hari ini melatih dua hal yang tidak terlatih oleh soal per-topik:

1. **Memilih** — melihat soal asing dan menentukan tekniknya dalam < 1 menit
2. **Menggabungkan** — enam latihan hari ini semuanya butuh **minimal dua** teknik

---

## Tujuan Pembelajaran

- [ ] Memakai pohon keputusan untuk memilih teknik dari batasan dan kata kunci soal
- [ ] Menggabungkan dua teknik tanpa merusak kompleksitas
- [ ] Mengenali **transformasi** yang mengubah soal asing jadi soal yang dikenal
- [ ] Menghitung kompleksitas **sebelum** menulis kode, bukan sesudah TLE
- [ ] Menulis stress test untuk solusi gabungan

---

## Struktur Folder

```
Day-41 (Latihan Terpadu Teknik Array)/
├── README.md
├── teori/Day_41_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp        <- 11 alat siap salin
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

Tiga bagian yang paling menentukan:

1. **"Benang merah yang menyatukan semuanya"** — semua teknik O(n) array
   adalah cara membuang informasi yang pasti tidak berguna lagi. Kalau kamu
   bisa menyebutkan *apa yang dibuang dan kenapa aman*, kamu hampir selalu
   sudah menemukan tekniknya.
2. **Pohon keputusan di Bagian 5** — cetak atau salin ke catatan. Ini yang
   akan kamu pakai di kontes.
3. **Tabel transformasi** — enam baris, dan lima di antaranya muncul di
   latihan hari ini.

### Langkah 2 — Template (15 menit)

`template/template.cpp` berisi 11 alat lengkap: prefix 1D/2D, difference array,
Kadane, two pointers, monotonic stack (termasuk `luasHistogram`), monotonic
deque, coordinate compression, prefix+map, dan sweep line.

Jangan cuma menyalinnya. **Baca komentar peringatannya** — di situ ada bug-bug
yang akan kamu buat hari ini kalau tidak dibaca.

### Langkah 3 — Latihan (150 menit)

Setiap latihan menggabungkan minimal dua hari:

| # | Judul | Tingkat | Target | Gabungan |
|---|-------|---------|--------|----------|
| 1 | Rata-rata Periode Tetap | Easy | 15 mnt | prefix sum + window tetap |
| 2 | Pengecatan Pagar | Easy | 20 mnt | difference array + counting |
| 3 | Substring Seimbang | Medium | 25 mnt | transformasi + prefix + map |
| 4 | Jendela Rentang Terbatas | Medium | 35 mnt | window variabel + 2 deque |
| 5 | Persegi Panjang di Ladang | Hard | 40 mnt | monotonic stack + per baris |
| 6 | Kepadatan Pengunjung | Hard | 30 mnt | kompresi + difference + sorting |

Latihan 3 adalah yang paling penting untuk dikerjakan **tanpa hint**. Ia
kelihatan seperti soal string, dan seluruh kesulitannya ada di menemukan
transformasi `'a' → +1, 'b' → −1`. Kalau kamu menemukannya sendiri, kamu sudah
menguasai inti hari ini.

Latihan 5 dan 6 sengaja sulit. Kalau mentok 30 menit, buka solusinya — tapi
baca bagian **PENJELASAN PENDEKATAN** dulu, jangan langsung ke kodenya.

### Langkah 4 — Tugas (15 soal)

**01–05** teknik tunggal dari sumber nyata (CSES, LeetCode), untuk memastikan
tiap alat masih tajam. **06–10** level menengah, sudah mulai menggabungkan.
**11–15** level kontes.

Semua tugas punya **3–4 sample test case** dengan penjelasan, dan sampelnya
memang dirancang untuk mematahkan implementasi yang hampir benar. Contoh:

- tugas 03 sample 4 → menguji `%` pada bilangan negatif di C++
- tugas 07 sample 4 → menguji perlakuan nilai kembar pada monotonic stack
- tugas 09 sample 2 → menguji interval setengah terbuka vs tertutup

Perhatikan pasangan **tugas 01 vs 02** (two pointers vs prefix+map) dan
**Exercise 6 vs tugas 09** (interval tertutup vs setengah terbuka). Keduanya
sengaja diletakkan berdekatan supaya perbedaannya terasa.

---

## Cheatsheet

```
sum(l..r) = P[r+1] - P[l]                        P berukuran n+1, P[0]=0
diff      : d[l]+=v, d[r+1]-=v, finalisasi prefix sum    d berukuran n+1
diff 2D   : 4 titik, pola inklusi-eksklusi
window    : perluas r, while(rusak) kecilkan l           butuh MONOTON
kadane    : cur = max(x, cur+x)                          tanpa batas panjang
mono stack: while(!st.empty() && kalah(top, x)) pop; push
mono deque: pop_front kadaluarsa, pop_back tertutupi, simpan INDEKS
prefix+map: cnt[0]=1; pre+=x; res+=cnt[pre-k]; cnt[pre]++
sweep     : (L,+1) dan (R+1,-1) untuk interval TERTUTUP
            (L,+1) dan (R,-1)   untuk interval SETENGAH TERBUKA
tepat(K)  = palingBanyak(K) - palingBanyak(K-1)

n <= 10^6 -> O(n)        n <= 10^5 -> O(n log n)
n <= 5000 -> O(n^2)      n <= 20   -> O(2^n)
```

---

## Common Mistakes

1. **Sliding window pada array yang punya elemen negatif.** Window variabel
   butuh monotonisitas. Ini kesalahan nomor satu di blok ini.
2. **Kompleksitas terkalikan tanpa disadari.** Monotonic stack di dalam loop
   baris = `O(RC)`, aman. Rebuild prefix sum di dalam loop = `O(RC²)`, TLE.
   Tanya: apa yang dibangun **sekali**, apa yang dibangun **per iterasi**?
3. **`unordered_map` kena anti-hash.** TLE yang membingungkan karena kodemu
   "sudah O(n)". Pakai `map`, atau kompresi koordinat, atau tambah salt.
4. **`%` pada bilangan negatif.** Di C++, `(-2) % 5 == -2`. Normalkan dengan
   `((x % m) + m) % m`.
5. **Difference array berukuran `n`, bukan `n+1`.** `d[r+1]` jebol saat `r = n−1`.
6. **Monotonic deque menyimpan nilai, bukan indeks.** Bug struktural — kamu
   tidak bisa membuang elemen kadaluarsa kalau tidak tahu posisinya.
7. **Interval tertutup vs setengah terbuka tertukar.** `R+1` versus `R`.
   Satu karakter, jawaban berbeda.
8. **Prefix sum tanpa `long long`.** `2·10⁵ × 10⁹ = 2·10¹⁴`.

---

## Checklist Sebelum Lanjut ke Day 42

- [ ] Bisa menyebutkan pohon keputusan dari ingatan sampai cabang ketiga
- [ ] Selesai exercise 1–4 tanpa membuka solusi
- [ ] Bisa menjelaskan kenapa two pointers gagal saat ada elemen negatif
- [ ] Bisa menjelaskan hubungan sweep line dengan difference array
- [ ] Sudah AC minimal 3 tugas di online judge aslinya
- [ ] Pernah menulis satu stress test dan menemukan bug lewat itu

---

## Link Soal Online

| Soal | Platform | Gabungan teknik |
| ---- | -------- | --------------- |
| [CSES 1660 — Subarray Sums I](https://cses.fi/problemset/task/1660) | CSES | two pointers |
| [CSES 1661 — Subarray Sums II](https://cses.fi/problemset/task/1661) | CSES | prefix + map |
| [CSES 1662 — Subarray Divisibility](https://cses.fi/problemset/task/1662) | CSES | prefix mod |
| [CSES 1141 — Playlist](https://cses.fi/problemset/task/1141) | CSES | window + posisi terakhir |
| [CSES 1619 — Restaurant Customers](https://cses.fi/problemset/task/1619) | CSES | sweep line |
| [LC 84 — Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | LeetCode | monotonic stack |
| [LC 85 — Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) | LeetCode | stack + per baris |
| [LC 907 — Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) | LeetCode | stack + kontribusi |
| [LC 42 — Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) | LeetCode | two pointers |
| [LC 239 — Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | LeetCode | monotonic deque |
| [LC 1004 — Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) | LeetCode | window variabel |
| [LC 1438 — Longest Subarray Abs Diff ≤ Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) | LeetCode | window + 2 deque |
| [LC 992 — Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/) | LeetCode | trik `tepat = ≤K − ≤K−1` |
| [CF 1398C — Good Subarrays](https://codeforces.com/problemset/problem/1398/C) | Codeforces | transformasi + map |

---

## Preview Day 42 — REVIEW Array & String

Day 42 adalah hari review: tidak ada teknik baru sama sekali, hanya
**diagnosis**. Kamu akan mengerjakan set soal campuran tanpa label, lalu
memetakan kesalahanmu ke hari asalnya. Tujuannya menemukan lubang yang tersisa
sebelum masuk blok Sorting & Searching (Day 43).
