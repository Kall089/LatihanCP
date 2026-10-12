# 09 — Dynamic Programming

[← Indeks CP](../README.md)

DP adalah **rekursi yang menolak menghitung submasalah yang sama dua kali**. Setiap soal DP adalah DAG: simpul = state, sisi = transisi.

Folder ini adalah versi lengkap. Satu file per materi Day 141–168, 244, 248. Latihan harian tetap di `KULIAH/ComprogLearning/CP` folder Day terkait.

## Tiga pertanyaan sebelum kode

```
1. STATE     : dp[...] artinya apa? (kalimat lengkap, bukan "jawabannya")
2. TRANSISI  : dihitung dari state mana, operator apa (+ / max / min / ||)
3. BASIS     : state terkecil nilainya berapa, dan kenapa?
```

Kalau STATE tidak bisa ditulis satu kalimat, jangan mengetik tabel dulu.

## Empat pola transisi

| Pola | Operator | Contoh |
|---|---|---|
| berapa cara | `+` (sering `% MOD`) | tangga, coin combinations |
| maksimum / minimum | `max` / `min` | knapsack, robber, coin min |
| bisa / tidak | `\|\|` atau OR boolean | subset sum |
| minimal langkah | `min(dp[i], dp[j] + 1)` | jump, coin |

## Dua definisi yang sering tertukar

| Definisi | Artinya | Jawaban akhir |
|---|---|---|
| **sampai i** | elemen `i` boleh dipakai atau tidak | biasanya `dp[n]` atau `dp[n-1]` |
| **berakhir tepat di i** | elemen `i` wajib dipakai sebagai ekor | `max` / `min` atas seluruh `dp[i]` |

## Urutan baca (jangan loncat)

```
01 prinsip
 → 02 top-down / bottom-up
 → 03 linear 1D
 → 04 coin / unbounded
 → 05 0-1 knapsack
 → 06 subset sum
 → 07 bounded
 → 08 LIS
 → 09 LCS / edit
 → 10 grid
 → 11 range
 → 12 rekonstruksi
 → 13 memori
 → 14 state lanjut
 → 15 bitmask TSP
 → 16 assignment
 → 17 SOS
 → 18 digit
 → 19 tree
 → 20 knapsack pohon
 → 21 reroot
 → 22 probabilitas
 → 23 bitset
 → 24 game
 → 25 broken profile
 → 26 CHT
 → 27 D&C / Knuth
```

Bitmask sebelum knapsack terasa seperti hafalan. CHT sebelum range DP biasanya sia-sia.

## Daftar file

### Dasar (Day 141–148)

| File | Isi | Day |
|---|---|---|
| [01-prinsip.md](01-prinsip.md) | overlapping, optimal substructure, fibonacci | 141 |
| [02-topdown-bottomup.md](02-topdown-bottomup.md) | memo, tabel, urutan isi | 142 |
| [03-linear-1d.md](03-linear-1d.md) | tangga, house robber, frog, Kadane | 143 |
| [04-coin-unbounded.md](04-coin-unbounded.md) | koin min, kombinasi vs permutasi | 144 |
| [05-01-knapsack.md](05-01-knapsack.md) | ambil/tidak, rekonstruksi | 145 |
| [06-subset-sum.md](06-subset-sum.md) | bisa/tidak, partition | 146 |
| [07-bounded-knapsack.md](07-bounded-knapsack.md) | stok terbatas, pecah biner | 147 |
| [08-lis.md](08-lis.md) | O(n²) dan O(n log n) | 148 |

### String, grid, range (Day 149–153)

| File | Isi | Day |
|---|---|---|
| [09-lcs-edit.md](09-lcs-edit.md) | LCS, edit distance | 149 |
| [10-grid.md](10-grid.md) | jalur, batu, 3 arah | 150 |
| [11-range.md](11-range.md) | MCM, palindrom, batu | 151 |
| [12-rekonstruksi.md](12-rekonstruksi.md) | jejak `prev[]` | 152 |
| [13-memori.md](13-memori.md) | dua baris, satu baris | 153 |

### Lanjut (Day 155–168)

| File | Isi | Day |
|---|---|---|
| [14-state-lanjut.md](14-state-lanjut.md) | menambah dimensi yang tepat | 155 |
| [15-bitmask-tsp.md](15-bitmask-tsp.md) | TSP, Hamilton | 156 |
| [16-bitmask-assignment.md](16-bitmask-assignment.md) | matching biaya | 157 |
| [17-sos.md](17-sos.md) | jumlah seluruh subset | 158 |
| [18-digit.md](18-digit.md) | tight, leading zero | 159 |
| [19-tree.md](19-tree.md) | DP anak → ayah | 160 |
| [20-knapsack-pohon.md](20-knapsack-pohon.md) | kapasitas dibagi subtree | 161 |
| [21-reroot.md](21-reroot.md) | jawaban untuk setiap akar | 162 |
| [22-probabilitas.md](22-probabilitas.md) | linearitas ekspektasi | 163 |
| [23-bitset.md](23-bitset.md) | subset sum cepat | 164 |
| [24-game.md](24-game.md) | winning / losing position | 165 |
| [25-broken-profile.md](25-broken-profile.md) | tiling, profil kolom | 166 |

Day 154, 167, 168 adalah review + latihan terpadu di ComprogLearning, bukan teori baru.

### Optimasi (Day 244, 248)

| File | Isi | Day |
|---|---|---|
| [26-cht.md](26-cht.md) | garis, Li Chao ide | 244 |
| [27-dnc-knuth.md](27-dnc-knuth.md) | titik pecah monoton | 248 |

## Peta cepat

| Soal kira-kira | File |
|---|---|
| n ≤ 1e5, keputusan linear | 03, 04, 08 |
| kapasitas W ≤ 1e5, n kecil | 05, 06, 07 |
| dua string | 09 |
| grid n,m ≤ 1000 | 10 |
| n ≤ 400, gabung interval | 11 |
| n ≤ 20, himpunan | 15, 16 |
| syarat digit 1..R | 18 |
| pohon n ≤ 1e5 | 19, 21 |
| transisi berbentuk `min(dp[j] + b[j]*a[i])` | 26 |

## Cara pakai berdua dengan ComprogLearning

1. Baca file di sini sampai simulasi angka cocok.
2. Buka folder Day yang sama, kerjakan `latihan/` tanpa `solusi/`.
3. Jika WA, tulis brute + generator ([16-teknik-kontes](../16-teknik-kontes/stress-test.md)).
4. `tugas/` setelah latihan lulus.

Checkpoint: CSES DP 10+ soal, atau AtCoder Educational DP A–N tanpa menyalin editorial baris demi baris.
