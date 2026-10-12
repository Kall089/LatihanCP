# Competitive Programming (C++) — Dasar

[← Daftar ensiklopedia](../README.md)

> **Ide satu kalimat:** fondasi kontes adalah membaca batas soal, memilih kontainer yang tepat, lalu mengubah array dengan prefix, pointer, atau pencarian — bukan menghafal rumus.

Folder ini adalah cheatsheet **bagian dasar** (kurikulum ComprogLearning folder **01–04**). Bahasa Indonesia. Semua indeks **0-based** kecuali disebut 1-based. Kode memakai `#include <bits/stdc++.h>`, `typedef long long ll`, dan **fungsi modular** (bukan semua logika di `main`).

Ini **bukan** `README.md` utama folder. File ini bisa digabung nanti. Jangan menimpa file lain di luar `ensiklopedia/cp/`.

## Cara baca

1. Buka file sesuai topik di tabel bawah.
2. Tiap algoritma punya enam blok tetap: **Teori**, **Kapan dipakai / tidak**, **Proses**, **Kode**, **Jebakan**, **Kompleksitas**.
3. Kalau ada **state** dan **transisi** (Kadane, window, deque), baca itu dulu — itu alasan kenapa kodenya benar, bukan komentar hiasan.
4. Salin **satu** contoh ke file `.cpp`, compile, ubah satu angka, lihat akibatnya.
5. Jangan menempel semua contoh ke satu file. Tiap `main` adalah tes mini terpisah.

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o tes tes.cpp
./tes
```

Di macOS, `bits/stdc++.h` kadang tidak ada di `clang++`. Pakai `g++` (Homebrew) atau ganti include ke header yang dipakai saja.

## Konvensi kode

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

| Aturan | Artinya |
| --- | --- |
| 0-indexed | `a[0]` elemen pertama. Range inklusif `a[l..r]` = `pre[r+1] - pre[l]` |
| `ll` | jumlah, hasil kali, prefix, inversi — default `long long` |
| fungsi modular | bangun / query / update dipisah; `main` hanya menguji |
| `'\n'` | bukan `endl` (kecuali soal interaktif yang butuh flush) |
| `const vector<ll>&` | jangan copy array besar |

## Daftar file bagian dasar

| File | Isi | Day ComprogLearning |
| --- | --- | --- |
| [00-template-io-kompleksitas.md](00-template-io-kompleksitas.md) | template, fast I/O, Big-O, baca constraint | 015 |
| [01-stl-vector-set-map-pq.md](01-stl-vector-set-map-pq.md) | vector, pair, tuple, set, map, priority_queue | 018, 021 |
| [02-stl-sort-bound-bitset.md](02-stl-sort-bound-bitset.md) | sort, bound, unique, permutasi, bitset | 025, 026 |
| [03-prefix-diff-twopointer-window.md](03-prefix-diff-twopointer-window.md) | prefix, difference, two pointers, window | 029, 032 |
| [04-kadane-mono-stack-deque-compress.md](04-kadane-mono-stack-deque-compress.md) | Kadane, mono stack/deque, kompresi | 035–038 |
| [05-sorting-binsearch-ternary-mitm.md](05-sorting-binsearch-ternary-mitm.md) | merge/inversi, binsearch, ternary, interaktif, MITM | 044, 048, 050, 052, 054 |

## Peta kurikulum 01–04

### 01 — Dasar

Day **015** Analisis Kompleksitas: Big-O, membaca batasan, memilih algoritma **sebelum** mengetik. Itu seluruh file 00.

### 02 — STL

| Day | Materi | File |
| --- | --- | --- |
| 018 | vector, pair, tuple, comparator | 01 |
| 021 | set, map, priority_queue | 01 |
| 025 | sort, lower_bound, unique, next_permutation | 02 |
| 026 | bitset, subset sum satu baris | 02 |

### 03 — Teknik Array

| Day | Materi | File |
| --- | --- | --- |
| 029 | prefix sum & difference array | 03 |
| 032 | two pointers & sliding window | 03 |
| 035 | Kadane & maximum subarray | 04 |
| 036 | monotonic stack | 04 |
| 037 | monotonic deque | 04 |
| 038 | kompresi koordinat | 04 |

### 04 — Sorting & Searching

| Day | Materi | File |
| --- | --- | --- |
| 044 | merge sort, inversi, D&C | 05 |
| 048 | binary search & on answer | 05 |
| 050 | ternary search & unimodal | 05 |
| 052 | soal interaktif (flush, anggaran tanya) | 05 |
| 054 | meet in the middle | 05 |

## Urutan belajar yang masuk akal

1. **00** sampai kamu bisa melihat `n ≤ 2·10^5` lalu menolak O(n²) tanpa mengetik.
2. **01** sampai kamu memilih vector / set / map / heap dalam 10 detik.
3. **02** sampai `sort` + `lower_bound` + `unique` tertulis dari ingatan.
4. **03** sampai range sum O(1) dan window monoton terasa biasa.
5. **04** sampai Kadane, NGE, window max, dan kompresi kursi bioskop.
6. **05** sampai “cari jawaban, bukan cari nilai” dan `2^40` dipecah jadi dua kali `2^20`.

Jangan loncat ke graf atau DP sebelum prefix dan binary search nyaman. Kurikulum ComprogLearning menempatkan folder 01–04 sebagai tahap fondasi (Day 015 sampai sebelum rekursi).

## Yang belum ada di bagian ini

Rekursi, bitmask, backtracking, greedy, number theory, graf, DP, struktur data (BIT, segtree), pohon, string, geometri — itu folder kurikulum 05 ke atas. Jangan dicampur ke file 00–05.

## Compile dan tes mini

Setiap blok **Kode** berisi fungsi plus `main` yang menguji angka kecil dari blok **Proses**. Kalau output tidak cocok dengan simulasi, bug ada di pemahaman atau di salinan — perbaiki dulu, jangan lanjut.

```bash
# satu file, satu tes
g++ -std=c++17 -O2 -o tes tes.cpp && ./tes
```

Untuk stress test (ada di file 00 dan 05): tulis versi naif O(n²), bandingan 1000 kasus acak, baru percaya versi cepat.

## Ingat lima kalimat

- Constraint dulu, kode kemudian.
- `int` jebol di `2·10^5 × 10^9`.
- Prefix butuh `pre[0] = 0` berukuran `n+1`.
- `unique` tidak menghapus; `erase` yang menghapus.
- Binary search butuh predikat **monoton**; puncak/lembah itu ternary atau binsearch pada selisih.

Kembali ke [daftar ensiklopedia](../README.md).
