# Day 214 — Aplikasi Prefix Function: Periode, Border & Automaton

> **Ide satu kalimat:** hari ini tidak ada algoritma baru — kita **memanen** dari tabel `pi` yang sudah kamu buat kemarin.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 214, kamu akan mampu:

- [ ] Membuktikan `periode p ⟺ border n−p`, bukan sekadar menghafalnya
- [ ] Menemukan **periode terkecil** dan tahu kapan ia **tidak** berarti pengulangan utuh
- [ ] Mengumpulkan **semua border** lewat rantai pi dalam O(n)
- [ ] Menghitung **kemunculan setiap prefiks** dalam satu kali jalan O(n)
- [ ] Membangun **KMP automaton** dan menjelaskan kenapa `aut[pi[i−1]][c]` boleh dipinjam
- [ ] Memakai automaton sebagai **graf state untuk DP counting**
- [ ] Menghitung **jumlah substring berbeda** dengan pi pada string terbalik

---

## Struktur Folder

```
Day-214 (Aplikasi Prefix Function - Periode, Border dan Automaton)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_214_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Blok Terkecil / Kompresi)
│   ├── exercise_2.cpp   (Warm-up  : Semua Border)
│   ├── exercise_3.cpp   (Core     : Hitung Kemunculan Tiap Prefiks)
│   ├── exercise_4.cpp   (Core     : Pencocokan pada Stream via Automaton)
│   ├── exercise_5.cpp   (Challenge: Jumlah Substring Berbeda)
│   └── exercise_6.cpp   (Contest  : DP Kata Sandi Aman)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← periode, border, hitungPrefiks, automaton, DP, palindrom, rotasi
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

`teori/Day_214_Teori_Lengkap.md`. Tiga bagian yang paling menentukan:

1. **Teorema periode ⟺ border** (bagian 1). Kalau kamu bisa menjelaskan ini ke orang lain
   tanpa melihat catatan, setengah hari ini sudah beres.
2. **Trace automaton `"aba"`** (bagian 4.2). Perhatikan bagaimana state 3 langsung ke state 2
   saat membaca `'b'` — di situlah `while` KMP "hilang".
3. **Trace hitungPrefiks pada `"aaa"`** (bagian 4.3). Loop mundurnya terlihat seperti sihir
   sampai kamu menelusurinya sekali dengan tangan.

### Langkah 2 — Pelajari Template (15 menit)

`template/template.cpp` berisi delapan bagian siap pakai. Yang **wajib** masuk template
pribadimu:

```cpp
int k = n - pi[n-1];               // periode terkecil
bool utuh = (n % k == 0);          // <- tulis dua baris ini SEKALIGUS
```

dan `bangunAutomaton` (12 baris). Dua benda ini muncul di puluhan soal.

### Langkah 3 — Kerjakan Latihan (90–120 menit)

| # | Judul | Tingkat | Waktu target | Konsep utama |
|---|-------|---------|--------------|--------------|
| 1 | Blok Terkecil | Easy | 10 mnt | `n − pi[n−1]` + cek `n % k` |
| 2 | Semua Border | Easy | 10 mnt | rantai pi, ingat `reverse` |
| 3 | Hitung Kemunculan Prefiks | Medium | 25 mnt | agregasi mundur |
| 4 | Stream Matching | Medium | 25 mnt | bangun automaton |
| 5 | Substring Berbeda | Hard | 30 mnt | pi pada string terbalik |
| 6 | Kata Sandi Aman | Hard | 35 mnt | DP di atas automaton |

**Aturan frustrasi 30 menit** tetap berlaku: buntu lewat dari itu → buka `solusi/`,
baca **penjelasan approach-nya saja** (bagian komentar atas), tutup lagi, lalu tulis
kodenya sendiri dari nol.

### Langkah 4 — Tugas (di luar sesi)

15 soal di `tugas/`, progresif:

- **01–05 (Easy):** langsung turunan rumus. Harus bisa < 15 menit masing-masing.
- **06–10 (Medium):** butuh satu langkah transformasi (reverse, concat, komplemen).
- **11–15 (Hard):** soal kontes asli — CF 526D, CF 471D, ABC257 G. Ini yang membentuk rating.

---

## Cara Kompilasi & Uji

```bash
g++ -std=c++17 -O2 -Wall -o sol solusi/solution_1.cpp
echo "abcabcabc" | ./sol
```

Uji cepat semua solusi terhadap sample:

```bash
for i in 1 2 3 4 5 6; do
  g++ -std=c++17 -O2 -Wall -o /tmp/s$i solusi/solution_$i.cpp && echo "solution_$i OK"
done
```

---

## Cheatsheet Hari Ini

```
border terpanjang   = pi[n-1]
semua border        = pi[n-1] -> pi[k-1] -> ... -> 0    (hasilnya MENURUN)
periode terkecil    = n - pi[n-1]
pengulangan utuh    = n % (n - pi[n-1]) == 0            (JANGAN LUPA)
tambahan agar utuh  = (k - n % k) % k
akhiran palindromik = pi terakhir dari rev(s)+'\1'+s  (tambah di AWAL)
awalan  palindromik = pi terakhir dari s+'\1'+rev(s)  (tambah di AKHIR)
cari pola           = pi dari pola + '#' + teks
hitung tiap prefiks = cnt[pi[i]]++ ; wariskan mundur ; +1
automaton           = aut[i][c] = cocok ? i+1 : aut[pi[i-1]][c]
DP hindari pola     = O(L*m*A), buang transisi ke state m
substring berbeda   = Σ (|cur| - max pi(rev(cur)))      O(n²), n ≤ 5000
```

---

## Common Mistakes Hari Ini

1. **Lupa `n % k == 0`.** Penyebab WA nomor satu. `"abcabca"` periodenya 3, tapi bukan
   pengulangan utuh.
2. **Separator bocor.** `'#'` boleh saja ada di input. Pakai `'\1'` atau karakter di luar
   alfabet soal.
3. **Automaton tanpa sentinel `'#'`.** State terakhir tidak punya transisi keluar → out of bounds.
4. **MLE automaton.** `m = 10^6 × 26` = 104 MB. Automaton hanya untuk `m` kecil.
5. **`int` pada `hitungPrefiks`.** Total kemunculan bisa ~5·10¹¹.
6. **Lupa `reverse` pada daftar border.** Rantai pi menghasilkan urutan menurun.
7. **Menelusuri rantai pi per posisi** di soal hitungPrefiks → O(n²) → TLE pada `"aaa...a"`.

---

## Checklist Sebelum Lanjut ke Day 215

- [ ] Bisa menulis `bangunPi` dari ingatan dalam < 2 menit
- [ ] Bisa menjelaskan kenapa `periode = n − pi[n−1]` tanpa melihat catatan
- [ ] Ingat cek `n % k == 0` **tanpa** diingatkan
- [ ] Bisa membangun automaton dari ingatan
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah menyelesaikan minimal 8 dari 15 tugas
- [ ] Sudah submit minimal 1 soal ke online judge dan dapat AC

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1732 — Finding Borders](https://cses.fi/problemset/task/1732) | CSES | rantai border |
| [CSES 1733 — Finding Periods](https://cses.fi/problemset/task/1733) | CSES | periode |
| [CF 432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) | Codeforces | border + hitungPrefiks |
| [CF 471D — MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) | Codeforces | pi pada array selisih |
| [CF 526D — Om Nom and Necklace](https://codeforces.com/problemset/problem/526/D) | Codeforces | periodisitas lanjut |
| [CF 1200 — Compress String](https://codeforces.com/problemset) | Codeforces | kompresi |
| [ABC 257 G — Prefix Concatenation](https://atcoder.jp/contests/abc257/tasks/abc257_g) | AtCoder | pi + DP |
| [SPOJ NHAY](https://www.spoj.com/problems/NHAY/) | SPOJ | matching dasar |
| [UVa 455 — Periodic Strings](https://onlinejudge.org/) | UVa | periode dasar |

---

## Preview Day 215 — Z-Function

Besok kamu belajar alat kedua untuk string: **Z-function**. Kalau `pi[i]` menjawab
*"berapa panjang awalan yang juga akhiran sampai posisi i"*, maka `z[i]` menjawab
*"berapa panjang kecocokan antara S dan sufiks yang mulai di i"*.

Pertanyaannya berbeda, tapi banyak soal bisa dikerjakan dengan salah satu — dan salah satunya
selalu terasa jauh lebih nyaman. Belajar memilih itulah inti Day 215.
