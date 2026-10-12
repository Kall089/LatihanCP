# Day 51 — Binary Search pada Bilangan Real & Kontrol Presisi

> **Ide satu kalimat:** ganti `while (lo < hi)` dengan **100 iterasi tetap**, dan hafalkan satu transformasi: `a[i] − x`.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan kenapa `while (lo < hi)` **tidak bisa** dipakai pada bilangan real
- [ ] Memilih **iterasi tetap** dan tahu kenapa lebih aman daripada epsilon
- [ ] Menghitung berapa iterasi untuk presisi tertentu
- [ ] Membedakan kesalahan **absolut** dan **relatif**
- [ ] Memakai `fixed` + `setprecision` dengan benar
- [ ] Menguasai transformasi **`a[i] − x`** dan turunannya untuk rasio
- [ ] Tahu kapan soal sebaiknya diubah menjadi **bilangan bulat**

---

## Struktur Folder

```
Day-51 (Binary Search pada Bilangan Real dan Kontrol Presisi)/
├── README.md
├── teori/Day_51_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Bagian "dua kriteria berhenti"** — kenapa epsilon bisa **tak berujung**.
   Trace 4.3 memberi contoh konkretnya.
2. **Bagian trik `a[i] − x`** (3.4). Ini bagian terpenting hari ini, dan yang
   membuka seluruh keluarga soal rata-rata/rasio.
3. **Trace 4.4** — `setprecision` tanpa `fixed`. Pendek, tetapi ia penyebab WA
   pada algoritma yang sebenarnya sudah benar.

### Langkah 2 — Template (10 menit)

Tiga baris yang harus jadi refleks:

```cpp
for (int it = 0; it < 100; it++) {
    double mid = (lo + hi) / 2;
    if (bisa(mid)) hi = mid; else lo = mid;   // lo = mid, BUKAN mid + 1
}
printf("%.9f\n", lo);
```

### Langkah 3 — Latihan (100 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Akar Kuadrat | Easy | 15 mnt | kerangka, batas `max(1, v)` |
| 2 | Membagi Tali | Easy | 20 mnt | arah predikat terbalik |
| 3 | Rata-rata K Elemen | Medium | 20 mnt | transformasi `a[i] − x` |
| 4 | Rata-rata Segmen | Medium | 25 mnt | + prefix sum + min berjalan |
| 5 | Rasio Terbaik | Hard | 20 mnt | fractional programming |
| 6 | Pompa Bensin | Hard | 25 mnt | minimalkan maksimum, `ceil` |

Exercise 3 sengaja punya solusi langsung yang lebih sederhana — ia ada untuk
melatih transformasi yang **wajib** dipakai di Exercise 4 dan 5.

### Langkah 4 — Tugas

**01–05** kerangka dan presisi dasar (POJ 1064, UVa 10341).
**06–10** transformasi `a[i] − x` (POJ 2018, LC 644, POJ 3111, LC 774).
**11–15** level kontes; tugas 11 dan 15 menggabungkan hari ini dengan graf (Day 129)
dan DP (Day 145).

Tugas 14 sengaja **tidak** bisa diselesaikan dengan `double` — ia menunjukkan
batas keras presisi 15–17 digit.

---

## Cheatsheet

```
KERANGKA BAKU:
  double lo = ..., hi = ...;
  for (int it = 0; it < 100; it++) {
      double mid = (lo + hi) / 2;
      if (bisa(mid)) hi = mid;
      else           lo = mid;         <- lo = mid, BUKAN mid + 1
  }
  printf("%.9f\n", lo);

ITERASI TETAP > EPSILON
  epsilon bisa TAK BERUJUNG pada nilai besar
  100 iterasi -> faktor 2^100 ~ 1e30
  rentang / 2^k <= presisi  ->  1e9 dan 1e-6 butuh k >= 50

MENCETAK
  printf("%.9f\n", x)  atau  cout << fixed << setprecision(9) << x
  'fixed' WAJIB (tanpanya = digit SIGNIFIKAN, bukan desimal)
  cetak LEBIH BANYAK desimal dari yang diminta
  pakai double, JANGAN float

JANGAN PERNAH  if (a == b)  untuk double
  fabs(a-b) < EPS, atau epsilon RELATIF untuk nilai besar

TRIK a[i] - x  (paling penting):
  rata-rata >= x  <=>  sum(a[i] - x) >= 0
  rasio P/Q >= x  <=>  sum(p[i] - x*q[i]) >= 0    [syarat: q[i] > 0]

ceil PADA double: pakai ceil(g/D - 1e-9) untuk menghindari ceil palsu
BULATKAN hasil akhir: llround(x * 100), JANGAN (int)(x * 100)

ATURAN PERTAMA: kalau jawabannya bisa bilangan bulat, JANGAN pakai double
```

---

## Common Mistakes

1. **`lo = mid + 1`** pada bilangan real → melompati rentang jawaban.
2. **`while (hi − lo > eps)`** pada nilai besar → tak berujung.
3. **`setprecision` tanpa `fixed`** → digit signifikan, bukan desimal.
4. **Mencetak desimal terlalu sedikit.**
5. **`if (a == b)`** untuk `double`.
6. **Epsilon absolut pada nilai besar.**
7. **Batas atas terlalu kecil** (jebakan `hi = v` saat `v < 1`).
8. **`float` alih-alih `double`** — hanya ~7 digit signifikan.
9. **`(int)(x * 100)`** memotong `2.4999999` menjadi 249 — pakai `llround`.
10. **Lupa syarat `q[i] > 0`** pada transformasi rasio.

---

## Checklist Sebelum Lanjut ke Day 52

- [ ] Bisa menulis kerangka iterasi tetap dari ingatan
- [ ] Bisa menjelaskan kenapa epsilon bisa tak berujung
- [ ] Bisa **menurunkan** transformasi `a[i] − x`, bukan menghafalnya
- [ ] Tahu kenapa transformasi rasio butuh `q[i] > 0`
- [ ] Selalu bertanya "bisakah ini dikerjakan sebagai bilangan bulat?"
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (POJ 1064 atau LC 644)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [POJ 1064 — Cable Master](http://poj.org/problem?id=1064) | POJ | predikat greedy |
| [POJ 2018 — Best Cow Fences](http://poj.org/problem?id=2018) | POJ | `a[i] − x` + prefix |
| [POJ 3111 — K Best](http://poj.org/problem?id=3111) | POJ | fractional programming |
| [LC 644 — Maximum Average Subarray II](https://leetcode.com/problems/maximum-average-subarray-ii/) | LeetCode | `a[i] − x` |
| [LC 774 — Minimize Max Distance](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) | LeetCode | minimalkan maksimum |
| [UVa 10341 — Solve It](https://onlinejudge.org/) | UVa | akar persamaan |
| [UVa 10566 — Crossed Ladders](https://onlinejudge.org/) | UVa | geometri + real |

---

## Preview Day 52 — Ternary Search

Binary search membutuhkan predikat **monoton**. Besok kamu akan menemui fungsi
yang **naik lalu turun** (unimodal), di mana tidak ada predikat monoton yang bisa
dibentuk sama sekali — sehingga binary search benar-benar tidak berlaku.

Ternary search menyelesaikannya dengan membuang **sepertiga** ruang pencarian di
setiap langkah. Seluruh kontrol presisi yang kamu pelajari hari ini berlaku persis
sama di sana, termasuk iterasi tetap dan `fixed` + `setprecision`.
