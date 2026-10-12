# Day 134 — Disjoint Set Union: Union by Rank & Path Compression

> **Ide satu kalimat:** sepuluh baris, hampir konstanta, ratusan soal — rasio manfaat terhadap panjang kode terbaik di seluruh CP.

---

## Tujuan Pembelajaran

- [ ] Menulis DSU dari nol dalam **kurang dari satu menit**
- [ ] Menjelaskan kenapa **path compression** dan **union by size** dibutuhkan **keduanya**
- [ ] Tahu arti `O(α(n))` secara praktis (`α ≤ 4`, anggap konstanta)
- [ ] Melacak **ukuran komponen** dan **banyaknya komponen** tanpa biaya tambahan
- [ ] Menerapkan pada **Kruskal**, **deteksi siklus**, dan **grid**
- [ ] Tahu kenapa DSU **tidak bisa memisahkan**, dan trik **balik waktu**
- [ ] Tahu kenapa **rollback** melarang path compression

---

## Struktur Folder

```
Day-134 (Disjoint Set Union - Union by Rank dan Path Compression)/
├── README.md
├── teori/Day_134_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Analogi silsilah keluarga** — kenapa menggabungkan cukup satu operasi.
2. **Bagian "dua optimasi"** — masing-masing memberi `O(log n)`, keduanya
   memberi `O(α(n))`. Biayanya dua baris.
3. **Trace 4.2 (path halving)** — perhatikan bahwa setiap `find` **memperbaiki**
   struktur untuk pemanggilan berikutnya. Itulah arti "amortisasi".

### Langkah 2 — Template (10 menit)

Hafalkan versi **lengkapnya**, bukan versi minimal:

```cpp
struct DSU {
    vector<int> par, sz;
    int komponen;
    int  find(int x);
    bool unite(int a, int b);   // bool: dipakai Kruskal & deteksi siklus
    int  ukuran(int x);         // sz[find(x)] -- find DULU
};
```

Tiga tambahan itu gratis dan sering langsung diminta soal.

### Langkah 3 — Latihan (90 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Kelompok Pertemanan | Easy | 15 mnt | DSU dasar, lacak komponen |
| 2 | Deteksi Siklus | Easy | 10 mnt | nilai kembalian `bool` |
| 3 | Total Kekayaan | Medium | 20 mnt | agregat di **perwakilan** |
| 4 | Membangun Jalan | Medium | 15 mnt | statistik inkremental |
| 5 | Kruskal | Hard | 25 mnt | MST, deteksi tidak terhubung |
| 6 | Pulau pada Grid | Hard | 25 mnt | grid, tiga jebakan batas |

### Langkah 4 — Tugas

**01–05** dasar (LC 547, CSES 1676, LC 684, CSES 1666).
**06–10** penerapan (CSES 1675, LC 721, LC 305, UVa 10608, second-best MST).
**11–15** level kontes.

**Tugas 11 adalah tugas 4 di Day 53** yang tadinya menunggu prasyarat ini —
kamu sekarang bisa mengerjakannya. Tugas 13 adalah pratinjau Day 135 (DSU berbobot),
tugas 15 pratinjau Day 191.

---

## Cheatsheet

```
struct DSU {
    vector<int> par, sz;  int komponen;
    DSU(int n): par(n), sz(n,1), komponen(n) { iota(par.begin(),par.end(),0); }

    int find(int x) {                      PATH HALVING, iteratif
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;          <- Kruskal & deteksi siklus
        if (sz[a] < sz[b]) swap(a, b);     UNION BY SIZE
        par[b] = a; sz[a] += sz[b]; komponen--;
        return true;
    }
};

union by size saja     -> O(log n)
path compression saja  -> O(log n) amortisasi
KEDUANYA               -> O(alpha(n)), alpha <= 4, praktis KONSTANTA

GRATIS: ukuran komponen sz[find(x)] | banyak komponen | ada siklus?
KRUSKAL: sort sisi, unite, berhenti setelah n-1 sisi
AGREGAT: simpan di AKAR, baca lewat find(x)   <- BUG NOMOR SATU

TIDAK BISA MEMISAHKAN
  sisi dihapus       -> BALIK WAKTU (hapus jadi tambah)
  "kapan terhubung"  -> DSU + parallel binary search (Day 53)
  online             -> Link-Cut Tree
ROLLBACK: buang path compression -> O(log n)
find rekursif pada n = 1e6 -> risiko stack overflow
```

---

## Common Mistakes

1. **`sz[x]` alih-alih `sz[find(x)]`.** Agregat hanya valid di akar.
2. **`par[a] == par[b]`** tidak berarti satu komponen — harus `find`.
3. **Lupa inisialisasi `par[i] = i`.**
4. **1-based dengan array berukuran `n`** — alokasikan `n+1`.
5. **`find` rekursif pada `n = 10^6`** — stack overflow.
6. **Path compression bersama rollback** — pembatalan menjadi mustahil.
7. **Mengira DSU bisa memisahkan.**
8. **Menghitung komponen dengan menyapu setiap query** — lacak di `unite`.
9. **`unite(x, x)` menurunkan `komponen`** — harus `false` tanpa efek.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis DSU lengkap dari ingatan dalam < 1 menit
- [ ] Bisa menjelaskan kenapa kedua optimasi dibutuhkan
- [ ] Selalu membaca agregat lewat `find(x)`
- [ ] Bisa menulis Kruskal dalam lima baris
- [ ] Tahu trik balik waktu untuk penghapusan sisi
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1676 dan 1675 paling cepat)
- [ ] **Sudah mengerjakan ulang tugas 4 dan 6 di Day 53** yang tadinya terkunci

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1676 — Road Construction](https://cses.fi/problemset/task/1676) | CSES | komponen + ukuran |
| [CSES 1675 — Road Reparation](https://cses.fi/problemset/task/1675) | CSES | Kruskal |
| [CSES 1666 — Building Roads](https://cses.fi/problemset/task/1666) | CSES | komponen |
| [LC 547 — Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | LeetCode | komponen |
| [LC 684 — Redundant Connection](https://leetcode.com/problems/redundant-connection/) | LeetCode | deteksi siklus |
| [LC 721 — Accounts Merge](https://leetcode.com/problems/accounts-merge/) | LeetCode | DSU + map |
| [LC 305 — Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/) | LeetCode | DSU grid |
| [UVa 10608 — Friends](https://onlinejudge.org/) | UVa | ukuran terbesar |

---

## Preview

**Day 135** — DSU Berbobot / Parity: menyimpan **relasi** antara simpul dan akarnya
(misalnya "berbeda kubu" atau "selisih nilai"), yang membuka soal-soal seperti
tugas 13 hari ini.

**Day 136–137** — Kruskal dan Prim secara lengkap, termasuk kapan masing-masing menang.

**Day 191** — Offline dynamic connectivity dengan DSU rollback, yang menjawab
keterbatasan "tidak bisa memisahkan" secara umum.
