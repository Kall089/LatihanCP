# Day 146 — Subset Sum & Partition Problem

> **Ide satu kalimat:** subset sum adalah 0/1 knapsack yang jawabannya bukan nilai maksimum, melainkan **jumlah mana saja yang bisa dicapai**.

---

## Tujuan Pembelajaran

- [ ] Menulis DP boolean `bisa[s]` untuk menjawab apakah target `S` bisa dibentuk
- [ ] Menjelaskan kenapa `bisa[0] = true` adalah basis wajib
- [ ] Menjelaskan kenapa loop sum tetap harus **mundur**
- [ ] Mencetak semua jumlah subset yang mungkin
- [ ] Mengubah equal partition menjadi subset sum target `total / 2`
- [ ] Mengubah minimum partition difference menjadi pencarian sum terdekat `total / 2`
- [ ] Menghitung banyak subset dengan sum tertentu, termasuk kasus elemen `0`
- [ ] Memakai `bitset` untuk mempercepat subset sum dan banyak query

---

## Struktur Folder

```
Day-146 (Subset Sum dan Partition Problem)/
├── README.md
├── teori/Day_146_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. Kuasai definisi `bisa[s]`: apakah ada subset dari item yang sudah diproses dengan jumlah tepat `s`.
2. Baca trace loop mundur. Ini sama pentingnya dengan Day 145: loop maju mengizinkan item dipakai berkali-kali.
3. Perhatikan bagian transformasi partisi. Banyak soal DP mudah terlihat berbeda, padahal semua kembali ke subset sum.

### Langkah 2 — Hafalkan Template (10 menit)

```cpp
vector<char> bisa(S + 1, 0);
bisa[0] = 1;

for (int x : a)
    for (int s = S; s >= x; s--)
        if (bisa[s - x]) bisa[s] = 1;
```

Untuk semua jumlah sampai `total`, ganti batas `S` menjadi `total`. Untuk menghitung cara, ganti boolean menjadi angka dan `OR` menjadi `+`.

### Langkah 3 — Latihan (120 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Ada Target? | Easy | 15 mnt | DP boolean dasar |
| 2 | Semua Jumlah Koin | Easy | 20 mnt | daftar reachable sums |
| 3 | Bagi Rata | Medium | 20 mnt | equal partition |
| 4 | Selisih Terkecil | Medium | 25 mnt | minimum partition difference |
| 5 | Berapa Banyak Cara? | Medium | 25 mnt | counting subset sum |
| 6 | Banyak Query Target | Hard | 25 mnt | bitset subset sum |

### Langkah 4 — Tugas

**01-05** membangun refleks subset sum. **06-10** memaksa transformasi partisi dan counting. **11-15** menaikkan level ke query, rekonstruksi, dan kombinasi constraint.

Target minimal sebelum lanjut:

- Exercise 1-4 selesai tanpa melihat solusi
- Exercise 5 selesai sambil sadar efek angka `0`
- Exercise 6 dipahami meskipun belum hafal implementasi `bitset`
- AC minimal CSES 1745 dan satu soal partition

---

## Cheatsheet

```
SUBSET SUM EXISTENCE
  bisa[s] = apakah sum s bisa dibentuk dari item yang sudah diproses
  bisa[0] = true
  for x in a:
      for s = S down to x:
          bisa[s] |= bisa[s-x]

KENAPA MUNDUR?
  mundur -> bisa[s-x] masih state sebelum x diproses -> x dipakai paling banyak sekali
  maju   -> bisa[s-x] bisa sudah memakai x -> berubah jadi unbounded

SEMUA JUMLAH
  S = total seluruh elemen
  kumpulkan semua s > 0 dengan bisa[s] = true

EQUAL PARTITION
  total ganjil -> NO
  total genap  -> cek bisa[total/2]

MINIMUM DIFFERENCE
  cari s <= total/2 yang reachable dan paling besar
  jawaban = total - 2*s

COUNTING
  cara[0] = 1
  for x in a:
      for s = K down to x:
          cara[s] += cara[s-x]
  jika x = 0, semua cara[s] akan terduplikasi; ini benar

TARGET +/- EXPRESSION
  pilih subset positif P, sisanya negatif
  P - (total - P) = target
  2P = total + target
  jadi hitung subset sum P bila valid

BITSET
  bitset<MAX_SUM+1> bs;
  bs[0] = 1;
  for x in a: bs |= bs << x;
```

---

## Common Mistakes

1. Lupa `bisa[0] = 1`, sehingga tidak ada sum baru yang pernah terbentuk.
2. Loop sum maju pada subset 0/1.
3. Memasukkan sum `0` ke output padahal soal meminta subset tidak kosong.
4. Equal partition tanpa mengecek `total` ganjil.
5. Minimum difference mencari semua `s`, padahal cukup sampai `total / 2`.
6. Counting subset sum memakai `vector<char>` atau `bool`, padahal butuh jumlah cara.
7. Menghapus angka `0` pada counting. Elemen `0` tetap menggandakan jumlah cara.
8. Memakai `int` untuk jumlah cara tanpa modulo.

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1745 — Money Sums](https://cses.fi/problemset/task/1745) | CSES | semua jumlah subset |
| [CSES 1093 — Two Sets II](https://cses.fi/problemset/task/1093) | CSES | counting partition |
| [LeetCode 416 — Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) | LeetCode | equal partition |
| [LeetCode 494 — Target Sum](https://leetcode.com/problems/target-sum/) | LeetCode | transformasi +/- |
| [LeetCode 1049 — Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) | LeetCode | minimum difference |
| [AtCoder DP D — Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d) | AtCoder | penguatan Day 145 |

---

## Preview

**Day 147** — Bounded Knapsack: ketika setiap nilai punya stok terbatas. Teknik kunci berikutnya adalah memecah stok `k` menjadi paket `1, 2, 4, ...` agar kembali menjadi beberapa item 0/1.
