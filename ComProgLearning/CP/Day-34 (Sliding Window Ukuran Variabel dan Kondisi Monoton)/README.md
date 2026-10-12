# Day 34 — Sliding Window Ukuran Variabel & Kondisi Monoton

> **Ide satu kalimat:** dua ujung yang **hanya maju** — itu sebabnya loop bersarang ini tetap O(n).

---

## Tujuan Pembelajaran

- [ ] Membedakan window **ukuran tetap** (Day 33) dan **ukuran variabel** (hari ini)
- [ ] Menguji **monotonisitas** predikat sebelum memilih alat ini
- [ ] Menulis kedua kerangka baku dan tahu **di mana** baris `catat` diletakkan
- [ ] Menjelaskan argumen amortisasi O(n)
- [ ] Memakai trik **`atMost(K) − atMost(K−1)`** untuk predikat "tepat K"
- [ ] Membedakan `best = max(...)` (terpanjang) dari `hasil += r − l + 1` (banyaknya)
- [ ] Mengenali kapan window **gagal** dan harus diganti prefix + map

---

## Struktur Folder

```
Day-34 (Sliding Window Ukuran Variabel dan Kondisi Monoton)/
├── README.md
├── teori/Day_34_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian syarat monotonisitas.** Ini bagian terpenting hari ini. Kalau kamu bisa
   menjawab *"kenapa sliding window salah kalau ada bilangan negatif?"* tanpa melihat
   catatan, kamu tidak akan salah pilih alat lagi.
2. **Dua diagram kerangka** — perhatikan bahwa satu-satunya perbedaan antara
   "terpanjang" dan "terpendek" adalah letak baris `catat`.
3. **Trace 4.1 dan 4.2** dibuat pada array yang **sama persis** supaya kamu bisa
   membandingkan dua kerangka berdampingan.

### Langkah 2 — Template (10 menit)

Hafalkan pasangan bercermin ini:

```cpp
masuk : if (cnt[x]++ == 0) jenis++;
keluar: if (--cnt[x] == 0) jenis--;
```

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Segmen Terpanjang | Easy | 10 mnt | kerangka terpanjang |
| 2 | Segmen Terpendek | Easy | 15 mnt | letak `catat` berpindah |
| 3 | Playlist | Medium | 20 mnt | `lastSeen`, syarat `>= l` |
| 4 | Paling Banyak K Jenis | Medium | 20 mnt | hitungan jenis |
| 5 | Tepat K Jenis | Hard | 25 mnt | trik pengurangan |
| 6 | Blok Seragam | Hard | 25 mnt | `lebar − maxFreq` |

### Langkah 4 — Tugas

**01–05** terapan langsung (CF 279B, LC 209, CSES 1141, LC 904, LC 3).
**06–10** menghitung banyak subarray (CSES 2428, LC 992, LC 930, LC 424).
**11–15** level kontes (LC 76, LC 1438).

Tugas 12 butuh monotonic deque (Day 37) dan tugas 15 justru **tidak boleh** memakai
sliding window. Keduanya sengaja ada di sini untuk melatih pemilihan alat, bukan
sekadar penerapan.

---

## Cheatsheet

```
SYARAT: predikat MONOTON terhadap pelebaran window
        ada bilangan NEGATIF -> biasanya TIDAK monoton -> prefix + map

TERPANJANG                      TERPENDEK
  masuk a[r]                      masuk a[r]
  while (TIDAK layak)             while (MASIH layak)
      keluar a[l], l++                catat (r - l + 1)
  catat (r - l + 1)                   keluar a[l], l++

terpanjang -> best = max(best, r - l + 1)
banyaknya  -> hasil += r - l + 1          (long long!)
tepat K    -> atMost(K) - atMost(K-1)

masuk : if (cnt[x]++ == 0) jenis++;
keluar: if (--cnt[x] == 0) jenis--;

boleh ganti K -> while ((r-l+1) - maxFreq > K) susutkan
```

---

## Pohon Keputusan Cepat

```
Soal minta subarray/substring dengan suatu sifat?
  ├─ ada bilangan negatif?        -> prefix + map (Day 29)
  ├─ butuh max/min DI DALAM window? -> monotonic deque (Day 37)
  ├─ minta "tepat K"?             -> atMost(K) - atMost(K-1)
  ├─ minta terpanjang?            -> catat SETELAH while
  └─ minta terpendek?             -> catat DI DALAM while
```

---

## Common Mistakes

1. **Memakai window padahal ada bilangan negatif.** Salah konsep, bukan salah kode —
   hasilnya kelihatan masuk akal tapi salah.
2. **Salah menaruh baris `catat`.**
3. **Lupa syarat `lastSeen[x] >= l`** → `l` mundur → jawaban salah.
4. **Operasi masuk dan keluar tidak bercermin.** Setiap `+=` harus punya `-=`.
5. **`best = INT_MAX` dicetak apa adanya** saat tidak ada jawaban.
6. **`int` untuk `hasil += r − l + 1`.** Bisa mencapai `2·10^10`.
7. **`unordered_map` di loop panas** untuk `n = 10^6`. Kompres dulu (Day 38), pakai array.

---

## Checklist Sebelum Lanjut ke Day 35

- [ ] Bisa menulis kedua kerangka tanpa melihat catatan
- [ ] Bisa menjelaskan argumen amortisasi O(n)
- [ ] Bisa menyebutkan **satu contoh** di mana window salah dan prefix+map benar
- [ ] Paham beda `best = max(...)` dan `hasil += r − l + 1`
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1141 dan LC 209 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1141 — Playlist](https://cses.fi/problemset/task/1141) | CSES | terpanjang tanpa duplikat |
| [CSES 2428 — Subarray Distinct Values](https://cses.fi/problemset/task/2428) | CSES | atMost, hitung banyak |
| [LC 3 — Longest Substring Without Repeating](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | LeetCode | `lastSeen` |
| [LC 209 — Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | LeetCode | terpendek |
| [LC 424 — Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | LeetCode | boleh ganti K |
| [LC 930 — Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/) | LeetCode | trik pengurangan |
| [LC 992 — Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/) | LeetCode | trik pengurangan |
| [CF 279B — Books](https://codeforces.com/problemset/problem/279/B) | Codeforces | terpanjang |

---

## Preview Day 35 — Kadane's Algorithm

Besok kamu akan menemui soal yang terlihat sangat mirip hari ini — *"subarray dengan
jumlah maksimum"* — tetapi sliding window **tidak bisa** menyelesaikannya, karena
bilangan negatif merusak monotonisitas.

Solusinya adalah DP satu dimensi yang menyamar sebagai loop biasa. Setelah paham
Kadane, kamu akan punya dua alat pelengkap: window untuk yang monoton, Kadane untuk
yang tidak.
