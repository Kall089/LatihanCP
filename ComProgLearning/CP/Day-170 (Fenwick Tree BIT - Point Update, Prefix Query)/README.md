# Day 170 — Fenwick Tree (BIT): Point Update, Prefix Query

> **Ide satu kalimat:** sepuluh baris, `O(log n)` untuk update **dan** query — dan `i & -i` adalah seluruh sihirnya.

---

## Tujuan Pembelajaran

- [ ] Menulis BIT dari nol dalam **kurang dari satu menit**
- [ ] Menjelaskan arti `i & -i` dan kenapa ia memberi bit terendah yang menyala
- [ ] Menjelaskan kenapa update **naik** dan query **turun**
- [ ] Menghitung **inversi** dan **"berapa yang lebih kecil di kanan"**
- [ ] Membalik peran untuk **range update, point query**
- [ ] Menggabungkan BIT dengan **kompresi koordinat**, termasuk secara **offline**
- [ ] Memakai **descent** untuk mencari elemen ke-k dalam `O(log n)`

---

## Struktur Folder

```
Day-170 (Fenwick Tree BIT - Point Update, Prefix Query)/
├── README.md
├── teori/Day_170_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Diagram blok** (bagian 1) — melihat bahwa `tree[i]` menanggung blok
   sepanjang `lowbit(i)` membuat seluruh sisanya masuk akal.
2. **Trace 4.2 dan 4.3** — `query(7)` memakai tiga blok, `update(5)` menyentuh
   tiga simpul. Perhatikan bahwa `tree[7]` **tidak** ikut diperbarui.
3. **Bagian `i = 0` menyebabkan hang** — bug nomor satu, dan gejalanya tidak
   memberi petunjuk apa pun.

### Langkah 2 — Template (10 menit)

Sepuluh baris yang harus jadi refleks:

```cpp
void update(int i, ll d) { for (; i <= n; i += i & -i) t[i] += d; }
ll query(int i) { ll s=0; for (; i>0; i -= i & -i) s += t[i]; return s; }
ll range(int l, int r) { return query(r) - query(l-1); }
```

### Langkah 3 — Latihan (110 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Update & Jumlah | Easy | 20 mnt | BIT dasar, "ganti" vs "tambah" |
| 2 | Hitung Inversi | Medium | 25 mnt | + kompresi, arah sapuan |
| 3 | Lebih Kecil di Kanan | Medium | 15 mnt | hasil per posisi, batas ketat |
| 4 | Range Update | Medium | 20 mnt | BIT atas difference array |
| 5 | Gaji Karyawan | Hard | 25 mnt | offline, kumpulkan semua nilai |
| 6 | Terkecil ke-K | Hard | 25 mnt | multiset + descent |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1648, 1651, SPOJ INVCNT, LC 315).
**06–10** varian (CSES 1144, LC 493, BIT 2D, CSES 1734).
**11–15** level kontes (CF 61E, UVa 11525, RURQ, Mo's + BIT).

---

## Cheatsheet

```
struct BIT {
    int n; vector<ll> t;
    void update(int i, ll d) { for (; i <= n; i += i & -i) t[i] += d; }
    ll query(int i) { ll s=0; for (; i>0; i -= i & -i) s += t[i]; return s; }
    ll range(int l, int r) { return query(r) - query(l - 1); }
};

1-INDEXED WAJIB. i = 0 -> i & -i = 0 -> LOOP TAK BERUJUNG (program hang).
tree[i] menanggung a[i - (i&-i) + 1 .. i]
UPDATE naik (i += i&-i) : blok yang MEMUAT i
QUERY turun (i -= i&-i) : blok yang MENUTUPI prefiks

SYARAT: operasi punya INVERS (sum, XOR). min/max/gcd -> segment tree.

TIGA STRUKTUR, TIGA SYARAT
  prefix sum   : INVERS    + statis   -> O(1)
  sparse table : IDEMPOTEN + statis   -> O(1)
  Fenwick      : INVERS    + dinamis  -> O(log n)
  segment tree : ASOSIATIF + dinamis  -> O(log n), paling umum

POLA
  "ganti nilai"     : update(k, baru - lama), simpan array asli terpisah
  inversi           : kompresi, sapu KANAN, query(rank-1), update(rank,1)
  range update      : BIT atas DIFFERENCE array; update(l,v), update(r+1,-v)
  RURQ              : dua BIT, prefix(i) = b1.query(i)*i - b2.query(i)
  multiset dinamis  : update(v,+1)/(v,-1), query(x), descent untuk ke-k
  2D                : dua loop bersarang, O(log n log m)

build O(n): t[i] += a[i]; j = i + (i&-i); if (j<=n) t[j] += t[i];
NILAI BESAR -> KOMPRESI (Day 38). Nilai dari QUERY juga harus masuk kamus!
long long: jumlah 2e14, inversi 2e10
```

---

## Common Mistakes

1. **0-indexed** → `i & -i = 0` → program hang tanpa pesan error.
2. **Lupa kompresi koordinat.**
3. **Nilai dari operasi update tidak masuk kamus** — butuh offline.
4. **`int` untuk jumlah/inversi.**
5. **Memakai BIT untuk min/max** — tidak punya invers.
6. **`query(rank)` alih-alih `query(rank-1)`** pada inversi — ikut menghitung kembar.
7. **Mencampur arah sapuan** pada inversi.
8. **`update(r+1)` melebihi `n`** — alokasikan `n+2`.
9. **"Ganti" diperlakukan sebagai "tambah"** — nilai menumpuk.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis BIT dari ingatan dalam < 1 menit
- [ ] Bisa menjelaskan `i & -i` lewat two's complement
- [ ] Tahu kenapa 1-indexed wajib, dan gejala kalau lupa
- [ ] Hafal satu arah sapuan untuk inversi dan konsisten memakainya
- [ ] Tahu kapan butuh offline (nilai dari query)
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1648 dan 1651 paling cepat)

---

## Tugas yang Kini Terbuka

BIT adalah prasyarat yang paling sering dirujuk di materi yang sudah kamu punya.
Setelah hari ini, tugas-tugas berikut bisa kamu kerjakan:

| Hari | Tugas | Topik |
| ---- | ----- | ----- |
| Day 38 | tugas 6, 11, 14 | Salary Queries, inversi, k-th dinamis |
| Day 44 | tugas 11 | count of smaller after self |
| Day 45 | tugas 12 | nilai ke-k pada rentang |
| Day 49 | tugas 15 | bound pada struktur dinamis |
| Day 53 | tugas 6, 9 | PBS atas nilai, ambang bertahap |

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1648 — Dynamic Range Sum](https://cses.fi/problemset/task/1648) | CSES | BIT dasar |
| [CSES 1651 — Range Update Queries](https://cses.fi/problemset/task/1651) | CSES | difference array |
| [CSES 1144 — Salary Queries](https://cses.fi/problemset/task/1144) | CSES | offline + kompresi |
| [CSES 1734 — Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | offline |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | inversi |
| [LC 315 — Count of Smaller After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LeetCode | per posisi |
| [LC 493 — Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | LeetCode | varian ambang |
| [CF 61E — Enemy is weak](https://codeforces.com/problemset/problem/61/E) | Codeforces | inversi tripel |

---

## Preview

**Day 171** — Fenwick 2D dan varian range update secara lengkap.
**Day 172–178** — Segment Tree, yang menyelesaikan kelemahan terbesar BIT:
ia bekerja untuk **operasi apa pun yang asosiatif**, termasuk `min`, `max`,
dan `gcd`, serta mendukung **lazy propagation** untuk update rentang.
