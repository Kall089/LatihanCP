# Cheatsheet Competitive Programming

Folder ini adalah **cheatsheet CP lengkap**: teori, kapan dipakai, simulasi angka, fungsi C++ modular, jebakan, dan kompleksitas.

Ini **bukan** latihan harian. Soal, `exercise_*.cpp`, dan `tugas_*.cpp` tetap di `KULIAH/ComprogLearning/CP`. Jangan menyalin ribuan file itu ke sini.

Ini juga **bukan** C++ + Unreal. Bahasa dan engine ada di [`../ensiklopedia/cpp`](../ensiklopedia/cpp/README.md).

## Dynamic programming ada di sini

**Buka [`09-dp/README.md`](09-dp/README.md).**

Urutan di dalam folder itu mengikuti Day 141–168, 244, 248:

| File | Materi | Day |
|---|---|---|
| [01-prinsip.md](09-dp/01-prinsip.md) | overlapping + optimal substructure | 141 |
| [02-topdown-bottomup.md](09-dp/02-topdown-bottomup.md) | memo vs tabel | 142 |
| [03-linear-1d.md](09-dp/03-linear-1d.md) | tangga, robber, frog | 143 |
| [04-coin-unbounded.md](09-dp/04-coin-unbounded.md) | koin min / banyak cara | 144 |
| [05-01-knapsack.md](09-dp/05-01-knapsack.md) | ambil atau tidak | 145 |
| [06-subset-sum.md](09-dp/06-subset-sum.md) | partition | 146 |
| [07-bounded-knapsack.md](09-dp/07-bounded-knapsack.md) | dekomposisi biner | 147 |
| [08-lis.md](09-dp/08-lis.md) | O(n log n) | 148 |
| [09-lcs-edit.md](09-dp/09-lcs-edit.md) | dua string | 149 |
| [10-grid.md](09-dp/10-grid.md) | jalur, halangan | 150 |
| [11-range.md](09-dp/11-range.md) | gabung selang | 151 |
| [12-rekonstruksi.md](09-dp/12-rekonstruksi.md) | jejak jawaban | 152 |
| [13-memori.md](09-dp/13-memori.md) | rolling array | 153 |
| [14-state-lanjut.md](09-dp/14-state-lanjut.md) | desain state | 155 |
| [15-bitmask-tsp.md](09-dp/15-bitmask-tsp.md) | himpunan sebagai state | 156 |
| [16-bitmask-assignment.md](09-dp/16-bitmask-assignment.md) | penugasan | 157 |
| [17-sos.md](09-dp/17-sos.md) | sum over subsets | 158 |
| [18-digit.md](09-dp/18-digit.md) | syarat per digit | 159 |
| [19-tree.md](09-dp/19-tree.md) | anak ke ayah | 160 |
| [20-knapsack-pohon.md](09-dp/20-knapsack-pohon.md) | kapasitas subtree | 161 |
| [21-reroot.md](09-dp/21-reroot.md) | setiap simpul sebagai akar | 162 |
| [22-probabilitas.md](09-dp/22-probabilitas.md) | ekspektasi | 163 |
| [23-bitset.md](09-dp/23-bitset.md) | konvolusi boolean | 164 |
| [24-game.md](09-dp/24-game.md) | menang/kalah DAG | 165 |
| [25-broken-profile.md](09-dp/25-broken-profile.md) | tiling grid | 166 |
| [26-cht.md](09-dp/26-cht.md) | Convex Hull Trick | 244 |
| [27-dnc-knuth.md](09-dp/27-dnc-knuth.md) | D&C opt + Knuth | 248 |

Ringkasan cepat (satu halaman) juga ada di [`../cp.md`](../cp.md). Versi lama yang lebih pendek: [`../ensiklopedia/cp`](../ensiklopedia/cp/README.md).

## Semua folder materi

| Folder | Isi | Day |
|---|---|---|
| [01-dasar](01-dasar/README.md) | kompleksitas, I/O, overflow | 015 |
| [02-stl](02-stl/README.md) | vector, set, map, pq, sort, bound, bitset | 018–026 |
| [03-array](03-array/README.md) | prefix, two pointers, Kadane, mono stack | 029–038 |
| [04-sorting-searching](04-sorting-searching/README.md) | merge, binsearch, ternary, MITM | 044–054 |
| [05-rekursi](05-rekursi/README.md) | subset, backtrack, memo | 057–067 |
| [06-greedy](06-greedy/README.md) | interval, exchange, konstruktif | 071–075 |
| [07-number-theory](07-number-theory/README.md) | sieve, modular, CRT, FFT | 088–111, 246 |
| [08-graf](08-graf/README.md) | DFS/BFS sampai flow | 113–136, 225–234 |
| [09-dp](09-dp/README.md) | **seluruh DP** | 141–168, 244, 248 |
| [10-struktur-data](10-struktur-data/README.md) | BIT, SegTree, Mo, Treap | 169–189 |
| [11-pohon](11-pohon/README.md) | LCA, HLD, centroid | 193–206 |
| [12-string](12-string/README.md) | hash, KMP, Trie, SA | 211–223 |
| [13-geometri](13-geometri/README.md) | cross, hull, sweep | 240–242 |
| [14-game-theory](14-game-theory/README.md) | Nim, Grundy | 236 |
| [16-teknik-kontes](16-teknik-kontes/README.md) | stress, random, anti-hash | 250, 252 |

Folder 15 di ComprogLearning adalah **kumpulan soal**, bukan teori baru. Kerjakan di sana.

## Cara baca tiap file

```text
### Nama teknik
**Teori:** analogi + kenapa benar
**Kapan:** dipakai / tidak
**Proses:** angka kecil, langkah demi langkah
**Kode:** fungsi terpisah + main mini
**Jebakan:** 2–4 kesalahan
**Kompleksitas:** waktu dan memori
```

Sebelum mengetik DP, jawab tiga kalimat:

```
1. STATE     : dp[i] artinya apa?
2. TRANSISI  : dihitung dari state mana, operator apa?
3. BASIS     : state terkecil nilainya berapa, kenapa?
```

## Konvensi kode

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

| Aturan | Artinya |
|---|---|
| 0-indexed | `a[0]` elemen pertama, kecuali Fenwick (1-based di dalam) |
| `ll` | jumlah, hasil kali, hash, jarak berbobot |
| fungsi modular | bangun / query / dfs / transisi dipisah dari `main` |
| `'\n'` | bukan `endl`, kecuali interaktif |
| identitas | sum=0, min=+∞, gcd=0, XOR=0 |

Compile:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o tes tes.cpp && ./tes
```

Di macOS, `bits/stdc++.h` kadang tidak ada di `clang++`. Pakai `g++` Homebrew.

## Urutan belajar

1. Fondasi: 01 → 06
2. Alat: 07 + 08 (sampai MST)
3. **DP: 09** (jangan loncat ke bitmask sebelum knapsack)
4. Struktur data + pohon: 10 → 11
5. String / graf lanjut / geo: sesuai soal

Latihan: buka Day yang sama di `KULIAH/ComprogLearning/CP`, kerjakan `latihan/` dulu.

## Peta cepat

| Saya ingin… | Buka |
|---|---|
| Jumlah `[l, r]` statis | [03-array/prefix](03-array/prefix-difference.md) |
| Ambil / tidak, kapasitas | [09-dp/05 knapsack](09-dp/05-01-knapsack.md) |
| Dua string | [09-dp/09 LCS](09-dp/09-lcs-edit.md) |
| Himpunan sebagai state | [09-dp/15 TSP](09-dp/15-bitmask-tsp.md) |
| Interval greedy | [06-greedy/interval](06-greedy/interval-exchange.md) |
| Jarak bobot ≥ 0 | [08-graf/dijkstra](08-graf/dijkstra.md) |
| Update + query rentang | [10-struktur-data/segtree](10-struktur-data/segment-tree.md) |
| Cari pola di string | [12-string/kmp](12-string/kmp.md) |
| WA tidak ketemu | [16-teknik-kontes/stress](16-teknik-kontes/stress-test.md) |

Kurikulum: `KULIAH/ComprogLearning/CP/DAFTAR-MATERI.md` (16 folder, Day 015–252).
