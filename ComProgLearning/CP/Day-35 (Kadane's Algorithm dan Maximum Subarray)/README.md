# Day 35 — Kadane's Algorithm & Maximum Subarray

> **Ide satu kalimat:** kalau beban yang kamu bawa dari belakang bernilai negatif, buang saja.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan kenapa sliding window **gagal** untuk masalah ini
- [ ] Menurunkan Kadane sebagai **DP satu dimensi**, bukan menghafal tiga barisnya
- [ ] Menjawab *"subarray boleh kosong atau tidak?"* sebelum menulis satu baris pun
- [ ] Melacak **indeks** subarray terbaik
- [ ] Menyelesaikan varian **melingkar** beserta penjaga kasus semua-negatif
- [ ] Menyelesaikan **maximum product** dengan dua variabel
- [ ] Memakai Kadane sebagai inti **submatriks maksimum O(R²C)**

---

## Struktur Folder

```
Day-35 (Kadane's Algorithm dan Maximum Subarray)/
├── README.md
├── teori/Day_35_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian "kenapa sliding window gagal"** — ini menghubungkan hari ini dengan Day 34
   dan menjelaskan kenapa kamu butuh alat kedua.
2. **Dua sudut pandang** (prefix minimum vs DP) — keduanya benar dan setara.
   Pilih satu yang lebih masuk akal bagimu, tapi pahami keduanya karena soal lanjutan
   kadang lebih mudah lewat salah satunya.
3. **Trace 4.2 (semua negatif)** — pendek tapi ini yang paling sering membuat WA.

### Langkah 2 — Template (10 menit)

Template berisi delapan bagian, termasuk `kadaneNaif` untuk **stress test**.
Kebiasaan ini layak dibentuk sekarang: tulis versi O(n²), bandingkan pada 1000 array
acak, dan hampir semua bug Kadane akan tertangkap dalam hitungan detik.

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Subarray Maksimum | Easy | 10 mnt | Kadane, inisialisasi `best` |
| 2 | Beserta Posisinya | Easy | 20 mnt | `curL`, tie-breaking |
| 3 | Keuntungan Saham | Medium | 15 mnt | transformasi selisih |
| 4 | Melingkar | Medium | 25 mnt | `total − minSum` + penjaga |
| 5 | Hasil Kali | Hard | 25 mnt | dua variabel |
| 6 | Submatriks | Hard | 30 mnt | kunci baris + Kadane |

### Langkah 4 — Tugas

Setiap tugas punya **4–5 sample test case**, bukan satu. Susunannya disengaja:
sample 1 kasus normal, lalu edge case (semua negatif / `n = 1`), lalu satu sample
yang memang dirancang untuk **mematahkan implementasi yang hampir benar**.
Kalau sample 1 lolos tapi sample 4 gagal, itu bukan sial — itu memang jebakannya.

| # | Judul | Tingkat | Sumber | Konsep |
|---|-------|---------|--------|--------|
| 01 | Maximum Subarray Sum | Easy | CSES 1643 | Kadane dasar, overflow |
| 02 | Subarray Jumlah Minimum | Easy | Original | negasi + pakai ulang alat |
| 03 | Buy and Sell Stock | Easy | LC 121 | Kadane pada selisih |
| 04 | Boleh Kosong vs Tidak | Easy | Original | inisialisasi `best` |
| 05 | Posisi Subarray Terbaik | Easy | Original | indeks + tie-breaking |
| 06 | Circular Subarray | Medium | LC 918 | melingkar + penjaga |
| 07 | Maximum Product | Medium | LC 152 | dua variabel |
| 08 | With One Deletion | Medium | LC 1186 | satu state tambahan |
| 09 | Dua Subarray Terpisah | Medium | Original | prefiks + sufiks |
| 10 | Maximum Sum Rectangle | Medium | UVa 108 | kunci baris + Kadane |
| 11 | Maximum Subarray Sum II | Hard | CSES 1644 | **bukan Kadane** |
| 12 | Beautiful Array | Hard | CF 1155D | tiga state |
| 13 | Setelah K Pengulangan | Hard | Original | analisis tanda total |
| 14 | Tepat K Segmen | Hard | Original | generalisasi Kadane |
| 15 | Submatriks Melingkar | Hard | Original | gabungan 06 + 10 |

Tugas 11 sengaja **tidak bisa** diselesaikan dengan Kadane — panjang subarray dibatasi,
dan itu butuh monotonic deque (Day 37). Kerjakan setelah Day 37, atau sekarang dengan
O(n²) untuk `n` kecil.

---

## Cheatsheet

```
cur  = max(x, cur + x);
best = max(best, cur);

best = LLONG_MIN  -> subarray TIDAK boleh kosong   <- default
best = 0          -> subarray BOLEH kosong

setara (prefix): best = max(pre[r+1] - min pre[l]),  hitung best SEBELUM
                 memperbarui minPre

melingkar : max(kadane, total - kadaneMin)
            KECUALI semua negatif -> kembalikan kadane
produk    : lacak curMax DAN curMin; kalau x < 0 tukar dulu
<= 1 hapus: dua state
submatriks: kunci baris atas+bawah, akumulasi kolom, Kadane 1D. O(R^2 C)
saham     : Kadane pada array SELISIH

panjang dibatasi <= k  -> BUKAN Kadane, pakai deque atas prefix (Day 37)
panjang tepat k        -> window ukuran tetap (Day 33)
```

---

## Common Mistakes

1. **`best = 0` padahal subarray tidak boleh kosong.** Penyebab WA nomor satu.
2. **Lupa penjaga semua-negatif pada varian melingkar.** `total − minSum` = 0 = kosong.
3. **Kadane biasa untuk perkalian.** Harus melacak minimum.
4. **Overflow.** `2·10^5 × 10^9 = 2·10^14`; perkalian meledak lebih cepat lagi.
5. **`curL` diperbarui di tempat yang salah.** Hanya saat memutuskan mulai baru.
6. **Mengira Kadane bisa dibatasi panjang.** Tidak bisa.
7. **`O(R²C)` dianggap selalu cukup.** 300×300 lolos, 1000×1000 tidak.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis Kadane dari ingatan dalam < 1 menit
- [ ] Selalu bertanya "boleh kosong atau tidak?" sebelum menulis
- [ ] Bisa menjelaskan lubang pada rumus melingkar
- [ ] Bisa menjelaskan kenapa produk butuh dua variabel
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1643 dan LC 121 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1643 — Maximum Subarray Sum](https://cses.fi/problemset/task/1643) | CSES | Kadane dasar |
| [CSES 1644 — Maximum Subarray Sum II](https://cses.fi/problemset/task/1644) | CSES | panjang dibatasi (bukan Kadane) |
| [LC 53 — Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | LeetCode | Kadane |
| [LC 121 — Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | LeetCode | selisih |
| [LC 152 — Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | LeetCode | dua variabel |
| [LC 918 — Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) | LeetCode | melingkar |
| [LC 1186 — Max Subarray Sum with One Deletion](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/) | LeetCode | dua state |
| [CF 1155D — Beautiful Array](https://codeforces.com/problemset/problem/1155/D) | Codeforces | Kadane + state |
| [UVa 108 — Maximum Sum](https://onlinejudge.org/) | UVa | submatriks |

---

## Preview Day 36 (sudah kamu selesaikan) — Monotonic Stack

Perhatikan benang merah tiga hari ini: Day 34 memakai **dua pointer** yang monoton,
Day 35 memakai **satu state rolling**, Day 36–37 memakai **struktur** yang menjaga
urutan monoton.

Ketiganya adalah cara berbeda untuk melakukan hal yang sama: **membuang informasi yang
sudah pasti tidak berguna lagi.** Itulah inti hampir semua teknik O(n) pada array.
