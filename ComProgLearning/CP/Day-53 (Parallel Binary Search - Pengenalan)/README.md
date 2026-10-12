# Day 53 — Parallel Binary Search (Pengenalan)

> **Ide satu kalimat:** jangan menguji satu murid pada 17 tingkat — uji **semua** murid pada satu tingkat, 17 kali.

---

## Tujuan Pembelajaran

- [ ] Mengenali pola *"banyak query, masing-masing butuh binary search"*
- [ ] Menjelaskan kenapa binary search satu per satu terlalu lambat
- [ ] Menulis kerangka baku: `lo[]`, `hi[]`, **bucket** berdasarkan `mid`
- [ ] Menganalisis kompleksitas menjadi `O(log n × (n·C + q·Cq))`
- [ ] Mengenali syarat wajib: **offline** dan **monoton**
- [ ] Tidak lupa **me-reset** struktur data setiap putaran
- [ ] Memeriksa dulu apakah **satu sapuan** sudah cukup

---

## Struktur Folder

```
Day-53 (Parallel Binary Search - Pengenalan)/
├── README.md
├── teori/Day_53_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Analogi ujian sekelas** — kenapa mengelompokkan query mengubah `q · log n`
   persiapan menjadi `log n` persiapan.
2. **Trace 4.1** — empat putaran menjawab tiga query, dengan angka lengkap.
3. **Trace 4.2** — kenapa lupa reset merusak semuanya, dan kenapa bugnya
   sulit terlihat.

### Langkah 2 — Template (15 menit)

Tujuh baris inti yang harus kamu hafal:

```cpp
while (adaYangJalan) {
    isiBucket();          // mid[i] -> bucket[mid[i]]
    resetStruktur();      // JANGAN LUPA
    for (t = 1..n) {
        terapkan(t);
        for (i : bucket[t]) perbarui(lo[i], hi[i]);
    }
}
```

### Langkah 3 — Latihan (120 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Tabungan | Easy | 15 mnt | **satu sapuan** — PBS tidak perlu |
| 2 | Ember | Medium | 30 mnt | kerangka PBS + BIT |
| 3 | Meteor | Medium | 30 mnt | rentang melingkar, biaya total |
| 4 | Kota Terhubung | Hard | 25 mnt | PBS + DSU, tanpa rollback |
| 5 | Nilai ke-K | Hard | 30 mnt | PBS atas **nilai**, bukan waktu |
| 6 | Pulau Muncul | Hard | 30 mnt | DSU + grid + syarat tambahan |

Exercise 1 sengaja **tidak** membutuhkan PBS — ia mengajarkan pemeriksaan yang
harus kamu lakukan sebelum menulis teknik yang lebih berat.

### Langkah 4 — Tugas

**01–05** dasar dan diagnosis (termasuk tugas 5 yang melatih pohon keputusan).
**06–10** terapan (SPOJ MKTHNUM, grid, DSU berbobot).
**11–15** level kontes; tugas 11 dan 12 sengaja **bukan** PBS — CSES 1734 adalah
offline biasa, dan tugas 12 memakai trik **proses mundur**.

---

## Cheatsheet

```
MASALAH: q query x binary search x pengujian O(n)  ->  O(q n log n) MUSTAHIL
IDE    : jalankan SEMUA binary search BERBARENGAN, log(n) putaran

KERANGKA:
  lo[i] = 1, hi[i] = n + 1              n+1 = "tidak pernah terpenuhi"
  while (masih ada lo < hi) {
      bucket[mid[i]].push_back(i)
      resetStruktur();                  <- BUG NOMOR SATU kalau lupa
      for (t = 1..n) {                  sapuan PENUH, jangan melompat
          terapkanKejadian(t);
          for (i : bucket[t])
              if (cukup(i)) hi[i] = t; else lo[i] = t + 1;
      }
  }

KOMPLEKSITAS: O(log n * (n*C + q*Cq))
  n = q = 2e5, C = Cq = log n  ->  ~6e7   aman

SYARAT WAJIB
  1. OFFLINE  (tahu semua query di awal)
  2. MONOTON  (sekali terpenuhi, selamanya)
  3. struktur bisa dibangun ulang dengan biaya wajar

POHON KEPUTUSAN SEBELUM MENULIS
  query online?              -> PBS TIDAK berlaku
  ambang bisa diurutkan?     -> SATU sapuan O(n+q), LEBIH BAIK
  n, q kecil?                -> naif saja
  selain itu                 -> PBS

STRUKTUR DATA: pakai BIT (update & query O(log n))
  difference array TIDAK cocok: update O(1) tapi baca O(m)

DSU pada PBS: tidak butuh ROLLBACK (tiap putaran mulai dari nol)
Overflow: hentikan akumulasi setelah melewati ambang
```

---

## Common Mistakes

1. **Lupa reset struktur data.** Putaran pertama benar, sisanya salah.
2. **Reset terlalu mahal.** `memset` array besar `log n` kali.
3. **Loop `t` tidak berjalan penuh.** Keadaan struktur menjadi salah.
4. **`hi` diinisialisasi `n`** alih-alih `n+1` — tidak ada slot "tidak pernah".
5. **Overflow** saat mengakumulasi — hentikan setelah melewati ambang.
6. **Difference array untuk query titik** — baca `O(m)`, terlalu lambat.
7. **Realokasi `bucket` di dalam loop** — pakai `clear()`.
8. **Menganggap query bisa online.**

---

## Checklist Sebelum Lanjut ke Day 54

- [ ] Bisa menulis kerangka tujuh baris dari ingatan
- [ ] Selalu memeriksa dulu apakah satu sapuan sudah cukup
- [ ] Bisa menjelaskan kenapa reset wajib, dan gejala kalau lupa
- [ ] Bisa menghitung kompleksitas dengan angka sungguhan
- [ ] Tahu kenapa DSU di PBS tidak butuh rollback
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 1 soal (SPOJ MKTHNUM atau Meteors)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [POI Meteors](https://szkopul.edu.pl/problemset/) | POI | contoh klasik |
| [SPOJ MKTHNUM](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | PBS atas nilai |
| [CSES 1734 — Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | offline (bukan PBS) |
| [CF 786C](https://codeforces.com/problemset/problem/786/C) | Codeforces | offline |
| [CF 1000F](https://codeforces.com/problemset/problem/1000/F) | Codeforces | query offline |

---

## Preview Day 54 — Meet in the Middle

Teknik berbeda dengan semangat yang sama: memecah masalah yang terlalu besar
menjadi dua bagian yang masing-masing bisa dikerjakan.

`2^40` mustahil, tetapi `2^20 + 2^20` seketika — asalkan kamu bisa **menggabungkan**
kedua paruh dengan pencarian terurut. Day 49 (`lower_bound`) akan menjadi alat
penggabungnya.
