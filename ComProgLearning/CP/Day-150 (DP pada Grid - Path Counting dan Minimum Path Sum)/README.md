# Day 150 — DP pada Grid: Path Counting & Minimum Path Sum

> **Ide satu kalimat:** grid dengan gerakan hanya kanan-dan-bawah **adalah DAG**, urutan topologisnya sudah gratis (baris demi baris), dan halangan diselesaikan dengan satu baris: `dp = 0`.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan kenapa grid kanan-bawah adalah **DAG**, dan kenapa itu penting
- [ ] **Menghitung jalur** dari `(1,1)` ke `(R,C)` dengan dan tanpa halangan
- [ ] Mencari **jumlah jalur minimum** (dan maksimum) beserta rekonstruksinya
- [ ] Menangani **halangan** tanpa `if` bercabang-cabang
- [ ] Memakai **rolling array** untuk memangkas memori jadi `O(C)`
- [ ] Menyelesaikan versi **4 arah** — dan tahu kenapa itu **bukan lagi DP**
- [ ] Mengenali varian: grid berlapis (state tambahan), jalur bertemu, segitiga
- [ ] Memakai **kombinatorika** kalau tidak ada halangan sama sekali

---

## Struktur Folder

```
Day-150 (DP pada Grid - Path Counting dan Minimum Path Sum)/
├── README.md
├── materi.md
├── teori/Day_150_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Bagian 2** — grid sebagai DAG. Kalau kamu sudah paham Day 120, hari ini
   hampir seluruhnya sudah kamu miliki.
2. **Bagian 4** — halangan. Perhatikan bahwa `dp = 0` bekerja untuk
   penghitungan tetapi **tidak** untuk minimum — di sana sentinelnya `INF`.
3. **Bagian 7** — kenapa gerakan 4 arah mematahkan DP dan memaksa BFS/Dijkstra.

### Langkah 2 — Template (10 menit)

```cpp
// hitung jalur                       // jumlah minimum
dp[i][j] = dp[i-1][j] + dp[i][j-1];   dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1]);
// halangan: dp[i][j] = 0             // halangan: dp[i][j] = INF
```

### Langkah 3 — Latihan (140 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Menghitung Jalur | Easy | 15 mnt | dp aditif, base tepi |
| 2 | Jalur dengan Halangan | Easy | 20 mnt | `dp = 0` |
| 3 | Jumlah Jalur Minimum | Medium | 20 mnt | min + biaya sel |
| 4 | Minimum + Rekonstruksi | Medium | 25 mnt | telusuri balik |
| 5 | Maksimum Permen dengan Halangan | Medium | 25 mnt | max + sentinel `-INF` |
| 6 | Dua Jalur Sekaligus | Hard | 35 mnt | state gabungan `dp[k][i1][i2]` |

### Langkah 4 — Tugas

**01–05** dasar (LC 62, 63, 64, 120, AtCoder DP-H).
**06–10** varian (jalur maksimum, kombinatorika, rolling array, jalur ke-K).
**11–15** level kontes (dua jalur, grid berlapis kunci, 4 arah dengan Dijkstra, jalur dengan tepat K belokan).

---

## Cheatsheet

```
KENAPA GRID KANAN-BAWAH BOLEH DI-DP
  setiap gerakan menambah (i + j) tepat 1 -> mustahil ada siklus -> DAG.
  Urutan topologisnya OTOMATIS: baris demi baris, kiri ke kanan.
  Ini kasus khusus Day 120 dengan urutan topologis yang gratis.

MENGHITUNG JALUR
  dp[i][j] = dp[i-1][j] + dp[i][j-1]
  base     : dp[0][0] = 1 ; di luar grid dianggap 0
  halangan : dp[i][j] = 0        (0 = elemen netral penjumlahan -> jalur mati)
  MODULO   : R,C = 1000 -> jumlah jalur ~ C(1998,999), astronomis

JUMLAH MINIMUM / MAKSIMUM
  dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1])
  base     : dp[0][0] = a[0][0]
  halangan : dp[i][j] = INF  (untuk min) atau -INF (untuk max)
  !!! LEWATI sel bersentinel saat merelaksasi, jangan sampai INF + a menular

MEMBACA TEPI TANPA if BERTUMPUK
  cara 1: padding — pakai indeks 1..R, 1..C; baris/kolom 0 berisi identitas
          (0 untuk jumlah, INF untuk min). dp[1][1] harus di-set MANUAL.
  cara 2: isi baris 0 dan kolom 0 lebih dulu, lalu loop dari (1,1)
  Cara 1 lebih pendek dan lebih sedikit bug.

ROLLING ARRAY  O(R*C) -> O(C) memori
  dp[j] = dp[j] + dp[j-1]     // dp[j] lama = baris atas, dp[j-1] = kiri
  loop j dari KIRI KE KANAN. Untuk min: dp[j] = a + min(dp[j], dp[j-1]).
  Rekonstruksi jadi mustahil.

TANPA HALANGAN -> KOMBINATORIKA
  banyak jalur = C(R+C-2, R-1)   -- O(R+C) dengan faktorial + invers modular
  Berguna kalau R, C sampai 10^6 sehingga tabel tidak muat.

4 ARAH (atas/bawah/kiri/kanan) BUKAN LAGI DP
  ada siklus -> tidak ada urutan topologis.
  biaya sama       -> BFS (Day 114)
  biaya non-negatif-> DIJKSTRA (Day 127)
  "jalur terpanjang tanpa mengulang sel" -> NP-hard

VARIAN PENTING
  segitiga (LC 120)        : tetangga (i-1,j-1) dan (i-1,j)
  grid + K kunci/koin      : dp[i][j][k], dimensi tambahan diproses di dalam
  DUA jalur sekaligus      : keduanya melangkah bersamaan; k = i1+j1 = i2+j2,
                             jadi state cukup dp[k][i1][i2] -> O(R*C*R)
  tepat K belokan          : dp[i][j][arah][k]
```

---

## Common Mistakes

1. **Sel awal juga halangan** — jawabannya 0, tapi banyak kode langsung menulis `dp[0][0] = 1`.
2. **Halangan pada soal minimum diisi 0** alih-alih `INF` — jalur haram jadi murah.
3. **Sentinel `INF` ikut dipakai merelaksasi** → nilai sampah menular.
4. **Lupa modulo** pada penghitungan jalur.
5. **Rolling array dengan loop `j` dari kanan** — arahnya harus kiri ke kanan.
6. **Rekonstruksi dari tabel yang sudah digulung** — mustahil.
7. **Mencoba DP pada gerakan 4 arah** — grafnya bersiklus.
8. **`int` untuk jumlah biaya** — `10^6` sel × `10^9` jauh melampaui `int`.
9. **Membaca grid `char` dengan `cin >> `per karakter** alih-alih per baris.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menjelaskan kenapa grid kanan-bawah pasti DAG
- [ ] Bisa menulis kedua rekurens (hitung & minimum) dari ingatan
- [ ] Tahu sentinel yang benar untuk masing-masing (0 vs INF vs −INF)
- [ ] Bisa memakai padding untuk menghilangkan `if` tepi
- [ ] Bisa merekonstruksi jalur optimal
- [ ] Tahu kapan harus beralih ke BFS/Dijkstra
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 3 soal (LC 62, 63, 64 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 62 — Unique Paths](https://leetcode.com/problems/unique-paths/) | LeetCode | dasar |
| [LC 63 — Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) | LeetCode | halangan |
| [LC 64 — Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) | LeetCode | minimum |
| [LC 120 — Triangle](https://leetcode.com/problems/triangle/) | LeetCode | segitiga |
| [LC 174 — Dungeon Game](https://leetcode.com/problems/dungeon-game/) | LeetCode | DP arah TERBALIK |
| [LC 1631 — Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) | LeetCode | 4 arah → Dijkstra |
| [AtCoder DP-H — Grid 1](https://atcoder.jp/contests/dp/tasks/dp_h) | AtCoder | halangan + modulo |
| [AtCoder DP-Y — Grid 2](https://atcoder.jp/contests/dp/tasks/dp_y) | AtCoder | halangan jarang + kombinatorika |
| [CF 118D / IOI Grader varian](https://codeforces.com/problemset) | Codeforces | dua jalur |

---

## Preview

**Day 151** — range DP: state-nya interval `[l, r]`, dan urutan pengisiannya
bukan lagi baris demi baris melainkan **berdasarkan panjang interval**.
**Day 152–153** — rekonstruksi jawaban DP secara umum dan optimasi memori
(rolling array), yaitu dua teknik yang hari ini kamu pakai secara khusus,
digeneralisasi.
