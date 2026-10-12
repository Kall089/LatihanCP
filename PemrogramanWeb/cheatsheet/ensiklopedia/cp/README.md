# Ensiklopedia Competitive Programming (C++) — versi lama

**Versi lengkap sekarang di folder terpisah:** [`../../cp/README.md`](../../cp/README.md).

**Dynamic programming:** [`../../cp/09-dp/README.md`](../../cp/09-dp/README.md) (satu file per Day).

File 00–19 di folder ini tetap ada sebagai ringkasan. Untuk belajar, pakai `cheatsheet/cp/`.

[← Daftar ensiklopedia](../README.md) · [Peta cepat](../../cp.md)

Cheatsheet C++ untuk kontes: Codeforces, AtCoder, CSES, TLX / Gemastik. Bahasa Indonesia mudah. Tiap algoritma memakai enam blok yang sama: **Teori**, **Kapan**, **Proses** (angka kecil), **Kode** fungsi modular, **Jebakan**, **Kompleksitas**.

Ini **bukan** ensiklopedia C++ + Unreal di folder [`../cpp`](../cpp/README.md). Folder itu tentang bahasa dan engine. Folder **ini** tentang algoritma kontes.

Kurikulum mengikuti daftar materi di `KULIAH/ComprogLearning/CP/DAFTAR-MATERI.md` (16 folder, Day 015–252). File 00–19 merangkum, bukan menyalin 2500 file latihan. Latihan harian tetap di **ComprogLearning/CP**.

Bagian dasar (00–05) juga punya catatan singkat di [README-dasar.md](README-dasar.md). Pakai file ini sebagai **indeks lengkap**.

## Daftar isi

- [Cara memakai folder ini](#cara-memakai-folder-ini)
- [Konvensi kode](#konvensi-kode)
- [Indeks semua file 00–19](#indeks-semua-file-0019)
- [Urutan belajar lima tahap](#urutan-belajar-lima-tahap)
- [Peta ke DAFTAR-MATERI](#peta-ke-daftar-materi)
- [Latihan harian di ComProgLearning](#latihan-harian-di-comproglearning)
- [Peta cepat “saya ingin…”](#peta-cepat-saya-ingin)
- [Compile](#compile)
- [Yang tidak dibahas](#yang-tidak-dibahas)

## Cara memakai folder ini

1. Buka tabel [indeks 00–19](#indeks-semua-file-0019), pilih file sesuai soal.
2. Baca **Kapan** sebelum menyalin kode. Banyak WA lahir dari struktur yang benar untuk soal yang salah.
3. Kerjakan simulasi **Proses** di kertas. Jika angka tidak cocok, jangan compile dulu.
4. Salin **satu** fungsi ke `tes.cpp`, compile, ubah satu nilai, lihat akibatnya.
5. Setelah paham, pindah ke folder Day di ComProgLearning dan kerjakan latihan/tugas di sana. Jangan menempel seluruh ensiklopedia ke satu file.

Format tiap entri:

```text
### Nama
**Teori:** analogi + kenapa benar
**Kapan dipakai / kapan tidak.**
**Proses:** angka kecil, langkah demi langkah
**Kode:** #include <bits/stdc++.h>, fungsi terpisah, main mini
**Jebakan:** 2–4 kesalahan
**Kompleksitas:** waktu dan memori
```

## Konvensi kode

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

| Aturan | Artinya |
| --- | --- |
| 0-indexed | `a[0]` elemen pertama, kecuali Fenwick di dalam struktur (1-based) |
| `ll` | jumlah, hasil kali, hash, luas ×2, jarak berbobot |
| fungsi modular | bangun / query / update / dfs dipisah; `main` hanya menguji |
| `'\n'` | bukan `endl`, kecuali soal interaktif yang butuh flush |
| `const vector<ll>&` | jangan salin array besar |
| identitas operasi | sum=0, min=+∞, gcd=0, XOR=0 |

Di macOS, `bits/stdc++.h` kadang tidak ada di `clang++`. Pakai `g++` Homebrew atau include header yang dipakai saja.

## Indeks semua file 00–19

### Fondasi dan STL — tahap 1 awal

| File | Isi | Folder / Day |
| --- | --- | --- |
| [00-template-io-kompleksitas.md](00-template-io-kompleksitas.md) | template, fast I/O, Big-O, baca constraint, overflow, memori | 01 · Day 015 |
| [01-stl-vector-set-map-pq.md](01-stl-vector-set-map-pq.md) | vector, pair, tuple, set, map, priority_queue, comparator | 02 · Day 018, 021 |
| [02-stl-sort-bound-bitset.md](02-stl-sort-bound-bitset.md) | sort, lower/upper_bound, unique, permutasi, bitset | 02 · Day 025, 026 |
| [03-prefix-diff-twopointer-window.md](03-prefix-diff-twopointer-window.md) | prefix sum, difference array, two pointers, sliding window | 03 · Day 029, 032 |
| [04-kadane-mono-stack-deque-compress.md](04-kadane-mono-stack-deque-compress.md) | Kadane, monotonic stack/deque, kompresi koordinat | 03 · Day 035–038 |
| [05-sorting-binsearch-ternary-mitm.md](05-sorting-binsearch-ternary-mitm.md) | merge/inversi, binary search on answer, ternary, interaktif, MITM | 04 · Day 044–054 |

### Rekursi, greedy, bilangan — tahap 1 akhir & tahap 2

| File | Isi | Folder / Day |
| --- | --- | --- |
| [06-rekursi-subset-backtrack-memo.md](06-rekursi-subset-backtrack-memo.md) | rekursi, subset, bitmask, backtracking, memoisasi | 05 · Day 057–067 |
| [07-greedy-interval-konstruktif.md](07-greedy-interval-konstruktif.md) | greedy vs DP, interval, exchange argument, konstruktif | 06 · Day 071–075 |
| [08-number-sieve-gcd-modular.md](08-number-sieve-gcd-modular.md) | sieve, faktor, GCD, modular, nCr, invers Fermat | 07 · Day 088, 090 |
| [09-number-crt-catalan-matrix-fft.md](09-number-crt-catalan-matrix-fft.md) | ext. Euclid, CRT, Catalan, Mobius, matrix expo, XOR basis, FFT/NTT | 07 · Day 092–111, 246 |

### Graf — tahap 2 (awal) dan tahap 5 (lanjut)

| File | Isi | Folder / Day |
| --- | --- | --- |
| [10-graf-dfs-bfs-topo.md](10-graf-dfs-bfs-topo.md) | representasi, DFS, BFS, flood, siklus, bipartit, topo, Euler, 0-1 BFS | 08 · Day 113–124 |
| [11-graf-dijkstra-bellman-floyd-mst.md](11-graf-dijkstra-bellman-floyd-mst.md) | Dijkstra, Bellman-Ford, Floyd, Kruskal, Prim | 08 · Day 127–136 |
| [12-graf-dsu-scc-bridge-2sat-flow.md](12-graf-dsu-scc-bridge-2sat-flow.md) | DSU, SCC, bridge, 2-SAT, max flow, matching, MCMF | 08 · Day 134, 225–234 |

### Dynamic programming — tahap 3

| File | Isi | Folder / Day |
| --- | --- | --- |
| [13-dp-prinsip-1d-knapsack.md](13-dp-prinsip-1d-knapsack.md) | state/transisi/basis, tangga, robber, Kadane, coin, 0-1 knapsack, LIS | 09 · Day 141–148 |
| [14-dp-string-grid-range.md](14-dp-string-grid-range.md) | LCS, edit, grid, range DP, rekonstruksi, rolling array | 09 · Day 149–153 |
| [15-dp-bitmask-digit-tree-optim.md](15-dp-bitmask-digit-tree-optim.md) | TSP bitmask, SOS, digit DP, tree DP, reroot, CHT/Knuth ide | 09 · Day 155–168, 244, 248 |

### Struktur data & pohon — tahap 4

| File | Isi | Folder / Day |
| --- | --- | --- |
| [16-segtree-bit-sparse-mo.md](16-segtree-bit-sparse-mo.md) | Fenwick, Segment Tree, lazy, Sparse Table, sqrt, Mo | 10 · Day 169–183 |
| [17-pohon-lca-hld-centroid.md](17-pohon-lca-hld-centroid.md) | diameter, Euler tour, binary lifting, LCA, HLD ide, centroid ide | 11 · Day 193–206 |

### String, geometri, permainan, cara kerja — tahap 5 + kapan saja

| File | Isi | Folder / Day |
| --- | --- | --- |
| [18-string-hash-kmp-z-trie.md](18-string-hash-kmp-z-trie.md) | hashing, KMP, Z, Manacher ide, Trie, SA ide | 12 · Day 211–219 |
| [19-geo-nim-stress-random.md](19-geo-nim-stress-random.md) | cross, hull, Sprague-Grundy, stress test, anti-hash | 13, 14, 16 · Day 236, 240, 250, 252 |

Treap, DSU rollback, parallel binary search, Aho-Corasick, SAM, sweep line penuh: disebut sebagai peta di file 16–19, dikerjakan di Day terkait jika sudah perlu.

## Urutan belajar lima tahap

Ini salinan semangat **Saran urutan belajar** di `DAFTAR-MATERI.md`. Nomor Day tinggi (225 ke atas) bukan otomatis “paling sulit”; itu urutan penyusunan.

### Tahap 1 — fondasi (Day 015 sampai 072)

**Folder 01–06. File 00–07.**

Tanpa ini, materi berikutnya terasa hafalan. Target: melihat `n ≤ 2·10^5` lalu menolak O(n²) tanpa mengetik; memilih vector/set/map; menulis prefix, two pointers, binary search on answer; merekursi dengan basis; membedakan greedy yang bisa dibuktikan dan yang tidak.

Urutan file:

```
00 kompleksitas
 → 01 kontainer  → 02 sort/bound
 → 03 prefix/window  → 04 Kadane/mono/kompresi
 → 05 binsearch/ternary/MITM
 → 06 rekursi/backtrack/memo
 → 07 greedy/interval
```

Checkpoint jujur: soal Div. 2 A–B (atau CSES *Introductory / Sorting and Searching* mudah) selesai tanpa membuka Google setiap lima menit.

### Tahap 2 — alat kerja (Day 088 sampai 136)

**Folder 07 dan 08 bagian awal (sampai MST). File 08–11.**

Sebagian besar soal kontes tingkat menengah selesai sampai sini: sieve, modular, DFS/BFS, Dijkstra, DSU+Kruskal.

```
08 sieve/gcd/mod  → 09 CRT/matrix/FFT (FFT boleh ditunda)
10 DFS/BFS/topo   → 11 Dijkstra/Bellman/Floyd/MST
```

File 09 bagian FFT dan file 12 (flow, 2-SAT) **boleh menunggu**. Day 246 FFT dan Day 225–234 graf lanjut masuk tahap 5 menurut daftar resmi, meski nomor filenya 09 dan 12.

Checkpoint: rating setara ~1400 mental model — soal cerita jadi graf + jarak, atau jadi aritmetika modulo.

### Tahap 3 — dynamic programming (Day 141 sampai 168)

**Folder 09. File 13–15.**

Bagian terbesar dan paling menentukan untuk naik tingkat. Jangan loncat ke bitmask sebelum knapsack dan LCS terasa biasa.

```
13 prinsip + 1D + knapsack + LIS
 → 14 string/grid/range + rekonstruksi
 → 15 bitmask/digit/tree + ide CHT
```

Checkpoint: CSES DP section 10+ soal, atau Educational DP Contest A–N tanpa menyalin editorial baris demi baris.

### Tahap 4 — struktur data & pohon (Day 169 sampai 206)

**Folder 10 dan 11. File 16–17.**

```
16 Sparse Table → Fenwick → SegTree → lazy ide → Mo
 → 17 diameter → Euler → LCA → (baru) HLD ide → centroid ide
```

HLD dan centroid adalah ide besar. Jangan menulis 200 baris HLD sebelum tiga soal LCA berstatus AC.

Checkpoint: CSES *Range Queries* dan *Tree Algorithms* (diameter, subtree, company queries) nyaman.

### Tahap 5 — string, graf lanjut, geometri (Day 211 ke atas)

**Folder 12, 13, 14, dan sisa folder 08. File 18, 19, plus 12 dan sisa 09.**

Ambil sesuai kebutuhan, tidak harus berurutan.

```
18 hash → KMP/Z → Trie → (SA jika perlu)
19 cross/hull  dan  Nim/SG
12 SCC/bridge/2-SAT/flow     saat soal memaksa
09 FFT / 15 CHT              saat n log n polinom atau DP garis
```

### Kapan saja — folder 16, file 19 bagian akhir

Day 250 (stress) dan 252 (random / anti-hash) **tidak** butuh prasyarat berat. Semakin awal dipakai, semakin banyak waktu kontes yang dihemat. Baca [stress test](19-geo-nim-stress-random.md#stress-test) begitu kamu punya solusi pertama yang bisa salah diam-diam (BIT, hash, geometri).

### Sepanjang semua tahap — folder 15 latihan soal

`DAFTAR-MATERI` folder 15 berisi tiga dek soal (DP, graf, greedy), dipetakan ke deck materi. Kerjakan **berbarengan**, bukan setelah semua file 00–19 selesai. Tiap baris di sana menyebut Day-nya.

## Peta ke DAFTAR-MATERI

| Folder kurikulum | Nama | File cheatsheet | Catatan |
| --- | --- | --- | --- |
| 01 | Dasar | 00 | kompleksitas dulu |
| 02 | STL | 01, 02 | kontainer vs algoritma STL |
| 03 | Teknik array | 03, 04 | prefix sampai kompresi |
| 04 | Sorting & searching | 05 | termasuk interaktif + MITM |
| 05 | Rekursi | 06 | jembatan ke DP |
| 06 | Greedy | 07 | bukti vs “terasa benar” |
| 07 | Teori bilangan | 08, 09 | FFT boleh ditunda |
| 08 | Graf | 10, 11, 12 | 12 = lanjut, tahap 5 |
| 09 | DP | 13, 14, 15 | CHT/Knuth ide di 15 |
| 10 | Struktur data | 16 | Treap/PBS hanya disebut |
| 11 | Pohon | 17 | HLD/centroid sebagai ide |
| 12 | String | 18 | Aho/SAM sebagai peta |
| 13 | Geometri | 19 | hull + cross; sweep peta |
| 14 | Teori permainan | 19 | Nim + Grundy |
| 15 | Latihan soal | — | kerjakan di ComProgLearning + CSES |
| 16 | Teknik kontes | 19 | stress + random + anti-hash |

## Latihan harian di ComProgLearning

Ensiklopedia ini **tidak** menggantikan repo latihan. Jangan menyalin 2500 file dari sana ke sini.

**Lokasi:** `/Users/haikalmuzhoffar/KULIAH/ComProgLearning/CP`

(Ejaan folder: `ComProgLearning`. Beberapa catatan menulis `ComprogLearning` — yang di disk adalah `ComProgLearning`.)

Isi tiap Day biasanya:

```
Day-XXX (Nama Topik)/
  README.md
  teori/          penjelasan panjang
  template/       kode hafalan
  latihan/        exercise_*.cpp
  solusi/         solution_*.cpp
  tugas/          tugas_*.cpp
```

Cara pakai berdua:

1. Baca cheatsheet (file 00–19) sampai simulasi angka cocok.
2. Buka Day yang sama di tabel di atas.
3. Kerjakan `latihan/` tanpa buka `solusi/`.
4. Jika WA, tulis brute + generator (file 19), baru baca teori Day.
5. `tugas/` setelah latihan lulus.

Indeks resmi: [`DAFTAR-MATERI.md`](../../../../ComProgLearning/CP/DAFTAR-MATERI.md)

Contoh pasangan file ↔ Day untuk tahap 4–5 (fokus file 16–19):

| Cheatsheet | Day folder (nama kira-kira) |
| --- | --- |
| 16 Sparse Table | Day-169 Sparse Table |
| 16 Fenwick | Day-170 Fenwick Tree |
| 16 Segment Tree | Day-172 Segment Tree |
| 16 lazy | Day-176 Lazy Propagation |
| 16 Mo | Day-183 Sqrt & Mo |
| 17 diameter | Day-198 Diameter |
| 17 Euler | Day-199 Euler Tour |
| 17 LCA | Day-201 Binary Lifting |
| 17 HLD | Day-204 HLD |
| 17 centroid | Day-206 Centroid |
| 18 hash | Day-211 String Hashing |
| 18 KMP | Day-213 KMP |
| 18 Z / Manacher | Day-215 Z-Function |
| 18 Trie | Day-217 Trie |
| 18 SA | Day-219 Suffix Array |
| 19 geo | Day-240 Geometri & Hull |
| 19 Nim | Day-236 Sprague-Grundy |
| 19 stress | Day-250 Stress Testing |
| 19 random | Day-252 Randomisasi |

Sumber soal tambahan (bukan disalin ke folder ini):

- CSES Problem Set — `cses.fi/problemset`
- AtCoder Educational DP — `atcoder.jp`
- Codeforces — virtual Div. 2
- TLX / TOKI — `tlx.toki.id` (Gemastik arsip)

Rencana enam minggu ada di dek Latihan-01..03 di ComProgLearning folder 15.

## Peta cepat “saya ingin…”

### Array dan pencarian

- Jumlah `[l, r]` statis → [03 prefix](03-prefix-diff-twopointer-window.md)
- Jumlah + update → [16 Fenwick](16-segtree-bit-sparse-mo.md#fenwick-tree-bit)
- Min `[l, r]` statis → [16 Sparse Table](16-segtree-bit-sparse-mo.md#sparse-table)
- Min + update → [16 Segment Tree](16-segtree-bit-sparse-mo.md#segment-tree)
- Update rentang → [16 lazy](16-segtree-bit-sparse-mo.md#lazy-propagation--ide)
- Banyak unik `[l, r]` offline → [16 Mo](16-segtree-bit-sparse-mo.md#algoritma-mo)
- Inversi → [05 merge](05-sorting-binsearch-ternary-mitm.md) atau [16 BIT](16-segtree-bit-sparse-mo.md#bit-inversi-dan-urutan-ke-k)
- “Nilai terkecil yang memenuhi” → [05 binsearch on answer](05-sorting-binsearch-ternary-mitm.md)

### Graf dan pohon

- Komponen, labirin, pewarna 2 → [10](10-graf-dfs-bfs-topo.md)
- Jarak berbobot ≥0 → [11 Dijkstra](11-graf-dijkstra-bellman-floyd-mst.md)
- Bobot negatif / siklus jelek → [11 Bellman](11-graf-dijkstra-bellman-floyd-mst.md)
- MST → [11 Kruskal](11-graf-dijkstra-bellman-floyd-mst.md)
- SCC, jembatan, 2-SAT, aliran → [12](12-graf-dsu-scc-bridge-2sat-flow.md)
- Diameter pohon → [17](17-pohon-lca-hld-centroid.md#diameter-dua-dfs)
- Subtree sum → [17 Euler](17-pohon-lca-hld-centroid.md#euler-tour-dan-query-subtree)
- LCA / jarak pohon → [17](17-pohon-lca-hld-centroid.md#lca)
- Query jalur + update → [17 HLD](17-pohon-lca-hld-centroid.md#hld--ide)

### DP dan string

- Ambil / tidak, kapasitas → [13 knapsack](13-dp-prinsip-1d-knapsack.md)
- Dua string → [14 LCS](14-dp-string-grid-range.md)
- Himpunan sebagai state → [15 bitmask](15-dp-bitmask-digit-tree-optim.md)
- Dua potongan sama? → [18 hash](18-string-hash-kmp-z-trie.md#prefix-hash-dan-potongan-o1)
- Cari pola → [18 KMP / Z](18-string-hash-kmp-z-trie.md#kmp-dan-prefix-function)
- XOR max → [18 Binary Trie](18-string-hash-kmp-z-trie.md#binary-trie-xor)

### Kontes

- WA tidak ketemu → [19 stress](19-geo-nim-stress-random.md#stress-test)
- Hash di-hack → [19 anti-hash](19-geo-nim-stress-random.md#anti-hash)
- Beberapa tumpukan / permainan pecah → [19 Grundy](19-geo-nim-stress-random.md#sprague-grundy)
- Titik & pagar → [19 hull](19-geo-nim-stress-random.md#convex-hull)

## Compile

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o tes tes.cpp && ./tes
```

| Bendera | Untuk apa |
| --- | --- |
| `-std=c++17` | structured binding, `if constexpr` |
| `-O2` | waktu mirip juri; matikan saat debug aneh |
| `-Wall -Wextra` | baca peringatannya |
| `-g` | debugger |
| `-fsanitize=address,undefined` | lokal, bukan di juri | 

Soal interaktif: flush setiap output (`cout << flush` atau `endl`). Jangan menonaktifkan sinkronisasi lalu lupa flush.

Estimasi kasar 2 detik C++ (file 00 membahas lebih teliti):

```
n ≤ 10        n! , 2^n * n^2 longgar
n ≤ 20        2^n, 2^n * n
n ≤ 400       n^3
n ≤ 2000      n^2 , n^2 log n pas
n ≤ 1e5       n log n, n √n (Mo hati-hati)
n ≤ 1e6       n , n log n ketat
n ≤ 1e18      log n, matrix expo, math
```

## Yang tidak dibahas

- Unreal Engine, `UPROPERTY`, Blueprint — itu [`../cpp`](../cpp/README.md).
- Cheat, hack, exploit, reverse engineering.
- Menyalin seluruh repo ComProgLearning ke sini.
- Setiap variasi Segment Tree persisten / Li Chao penuh / SA-IS — cukup ide + rujukan Day.

Dokumentasi ini mengikuti kurikulum yang ada di `DAFTAR-MATERI.md` per **22 September 2026**. Nama folder Day bisa sedikit berbeda di disk; nomor Day-nya yang dipegang.

## Lima kalimat yang perlu terbawa

- Constraint dulu, kode kemudian.
- `int` jebol di `2·10^5 × 10^9`.
- Operasi + ada/tidaknya update menentukan prefix vs Sparse vs BIT vs SegTree.
- Pohon = satu jalur unik; graf umum tidak.
- Stress test lebih murah daripada empat kali WA.

## Rencana seminggu (contoh)

Jangan membaca 19 file dalam tujuh hari. Satu tahap, satu kebiasaan.

| Hari | Baca cheatsheet | Latihan |
| --- | --- | --- |
| Sen | 1 topik file sesuai tahapmu | 3 soal CSES / Day latihan |
| Sel | ulang jebakan topik kemarin | 3 soal, 1 di-stress (file 19) |
| Rab | topik baru | 3 soal |
| Kam | virtual 3 soal campur 90 menit | catat yang kosong |
| Jum | isi kekosongan dari Kamis | Day tugas |
| Sab | review + tulis ulang **satu** template dari ingatan | — |
| Min | istirahat atau virtual contest tim | folder 15 jika ada |

Setelah AC, pindahkan template yang sering dipakai ke satu `template.cpp` milikmu. Ensiklopedia tetap rujukan, bukan tempat copy-paste saat kontes.

Mulai dari [00 — template dan kompleksitas](00-template-io-kompleksitas.md) jika baru, atau lompat ke tahap yang sedang kamu kerjakan. Latihan hari ini: buka satu folder Day di `KULIAH/ComProgLearning/CP`, bukan membuka dua belas file cheatsheet sekaligus.
