# Day 216 — Manacher: Semua Substring Palindrom dalam O(n)

> **Ide satu kalimat:** ini adalah z-box Day 215 dengan **satu perubahan** — cerminnya refleksi, bukan translasi.

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 216, kamu akan mampu:

- [ ] Menjelaskan kenapa palindrom **genap** butuh perlakuan khusus, dan bagaimana `#` menghapus masalah itu
- [ ] Menulis Manacher versi transformasi **11 baris** dari ingatan
- [ ] Menurunkan ketiga rumus konversi indeks sendiri (bukan menghafalnya)
- [ ] Menghitung total **kemunculan** palindrom, dan tahu itu **bukan** jumlah palindrom berbeda
- [ ] Menjawab *"apakah S[l..r] palindrom"* dalam **O(1)**
- [ ] Memakai Manacher sebagai **oracle** untuk DP, bukan sebagai jawaban akhir
- [ ] Memilih antara Manacher, hashing, dan Eertree secara sadar

---

## Struktur Folder

```
Day-216 (Manacher - Semua Substring Palindrom)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_216_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Palindrom Terpanjang)
│   ├── exercise_2.cpp   (Warm-up  : Hitung Substring Palindrom)
│   ├── exercise_3.cpp   (Core     : Query Palindrom O(1))
│   ├── exercise_4.cpp   (Core     : Potongan Palindrom Minimal)
│   ├── exercise_5.cpp   (Challenge: Derajat Palindrom — CF 7D)
│   └── exercise_6.cpp   (Contest  : Palisection — CF 17E)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp     through   tugas_15.cpp
└── template/
    └── template.cpp     ← manacher, manacher2, CekPalindrom, awalan/akhiran, DP partisi
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

`teori/Day_216_Teori_Lengkap.md`. Tiga bagian yang menentukan:

1. **Diagram cermin** (bagian 1). Letakkan berdampingan dengan diagram z-box Day 215.
   Perbedaannya cuma `p[2c − i]` vs `z[i − l]`. Kalau kamu melihat itu, kamu sudah
   memahami Manacher.
2. **Tabel trace `"abba"`** (bagian 4.1). Perhatikan baris `i = 5` dan `i = 7`:
   keduanya menyalin dari cermin.
3. **Verifikasi total = 6** di bagian yang sama. Hitung manual, cocokkan dengan rumus
   `Σ (p[i]+1)/2`. Kalau kamu bisa menurunkan rumus itu sendiri, bagian counting selesai.

### Langkah 2 — Pelajari Template (15 menit)

Yang wajib masuk template pribadimu — **beserta komentar konversi indeksnya**:

```cpp
// panjang asli      = p[i]
// posisi awal di S  = (i - p[i]) / 2
// pusat untuk (l,r) = l + r + 1
```

> ⚠️ Konversi indeks inilah — **bukan algoritmanya** — yang biasanya salah saat kontes.
> Tulis ketiga baris komentar itu di template. Biaya nol, manfaatnya besar.

### Langkah 3 — Kerjakan Latihan (100–130 menit)

| # | Judul | Tingkat | Waktu target | Konsep utama |
|---|-------|---------|--------------|--------------|
| 1 | Palindrom Terpanjang | Easy | 20 mnt | Manacher + konversi indeks |
| 2 | Hitung Palindrom | Easy | 15 mnt | `Σ (p[i]+1)/2`, `long long` |
| 3 | Query O(1) | Medium | 20 mnt | turunkan `pusat = l+r+1` |
| 4 | Potongan Minimal | Medium | 25 mnt | Manacher sebagai oracle DP |
| 5 | Derajat Palindrom (CF 7D) | Hard | 30 mnt | `p[i] >= i`, DP `k[i/2]+1` |
| 6 | Palisection (CF 17E) | Hard | 45 mnt | difference array + komplemen |

Exercise 6 adalah soal Codeforces asli dengan `n = 2·10^6`. Kalau kamu menyelesaikannya
sendiri, hari ini sukses besar.

### Langkah 4 — Tugas (di luar sesi)

- **01–05 (Easy):** terapan langsung dari template.
- **06–10 (Medium):** Manacher + satu lapis logika (DP, paritas, arah).
- **11–15 (Hard):** CF 17E, CF 1080E, plus tugas 12 yang **sengaja tidak bisa** dikerjakan
  dengan Manacher — itu jembatan ke Eertree.

---

## Cara Kompilasi & Uji

```bash
g++ -std=c++17 -O2 -Wall -o sol solusi/solution_6.cpp
printf '4\nbabb\n' | ./sol      # -> 6
```

Solution 6 sudah diuji terhadap brute force pada 400 string acak.

---

## Cheatsheet Hari Ini

```
T = # a # b # ... #      |T| = 2n+1, semua palindrom jadi GANJIL

INTI:
  if (i < r) p[i] = min(r - i, p[2*c - i]);              // CERMIN
  while (aman && t[i-p[i]-1] == t[i+p[i]+1]) p[i]++;
  if (i + p[i] > r) { c = i; r = i + p[i]; }

KONVERSI INDEKS (paling sering salah):
  panjang asli       = p[i]
  posisi awal di S   = (i - p[i]) / 2
  pusat untuk (l, r) = l + r + 1
  S[l..r] palindrom  = p[l + r + 1] >= r - l + 1
  awalan i palindrom = p[i] >= i

HITUNGAN:
  total kemunculan   = Σ (p[i] + 1) / 2       <- long long WAJIB
  palindrom BERBEDA  = Eertree, BUKAN Manacher

VERSI DUA ARRAY (n besar):
  d1[i] = jumlah palindrom ganjil berpusat di i
  d2[i] = jumlah palindrom genap, pusat di celah SEBELUM i
  total = Σ d1 + Σ d2                          <- tanpa rumus (p+1)/2
```

---

## Pemetaan Tiga Hari Terakhir

| | Day 213–214 (pi) | Day 215 (z) | Day 216 (Manacher) |
| --- | --- | --- | --- |
| Pertanyaan | awalan = akhiran? | cocok dari posisi i? | palindrom berpusat di i? |
| Simetri | translasi ke belakang | translasi | **refleksi** |
| Pointer monoton | `j` (amortisasi) | `r` | `r` |
| Punya automaton? | ✓ | ✗ | ✗ |
| Untuk DP counting string | ✓ terbaik | — | via Eertree |

Ketiganya adalah **satu ide yang sama**: simpan bukti terjauh yang sudah kamu punya,
gunakan kembali lewat simetri, dan biarkan satu pointer maju monoton membayar seluruh biaya.
Kalau kamu menangkap itu, kamu tidak sedang menghafal tiga algoritma — kamu memahami satu.

---

## Common Mistakes Hari Ini

1. **Konversi indeks salah.** Bukan algoritmanya yang sulit. Verifikasi dengan `"abba"`
   sebelum submit: `p[4] = 4`, posisi `(4−4)/2 = 0`, jawab `"abba"`.
2. **`#` ada di dalam input.** Pakai `'\1'` kalau alfabetnya luas — sama persis dengan
   jebakan separator Day 215.
3. **Batas ekspansi cuma satu sisi.** `i - p[i] - 1 >= 0` **dan** `i + p[i] + 1 < n`,
   dua-duanya wajib. Melewatkan salah satu kadang lolos di lokal tapi RE di judge.
4. **Mengira Manacher menghitung palindrom berbeda.** `"aaa"` → 6 kemunculan, 3 berbeda.
5. **`int` untuk total.** `"aaa...a"` dengan `n = 10^6` → ~5·10^11.
6. **Mencampur konvensi `d2`.** Sebagian sumber memakai pusat di celah **setelah** `i`.
   Pakai versi template ini saja.
7. **Menulis Manacher padahal `n ≤ 5000`.** Ekspansi naif lebih pendek dan lebih kecil
   risikonya. Jangan pamer algoritma saat kontes.

---

## Checklist Sebelum Lanjut ke Day 217

- [ ] Bisa menulis Manacher dari ingatan dalam < 3 menit
- [ ] Bisa menurunkan `pusat = l + r + 1` di kertas, bukan menghafalnya
- [ ] Bisa menjelaskan kenapa `Σ (p[i]+1)/2` tidak menghitung ganda
- [ ] Tahu kapan Manacher **tidak** cukup (palindrom berbeda → Eertree)
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah menyelesaikan minimal 8 dari 15 tugas
- [ ] Sudah AC minimal 2 soal di online judge (CSES 1111 dan LeetCode 647 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1111 — Longest Palindrome](https://cses.fi/problemset/task/1111) | CSES | Manacher dasar |
| [LeetCode 5 — Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) | LeetCode | pemanasan |
| [LeetCode 647 — Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) | LeetCode | counting |
| [LeetCode 132 — Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/) | LeetCode | Manacher + DP |
| [CF 7D — Palindrome Degree](https://codeforces.com/problemset/problem/7/D) | Codeforces | DP rekursif |
| [CF 17E — Palisection](https://codeforces.com/problemset/problem/17/E) | Codeforces | difference array + komplemen |
| [CF 1080E — Sonya and Matrix Beauty](https://codeforces.com/problemset/problem/1080/E) | Codeforces | Manacher pada matriks |
| [SPOJ LPS](https://www.spoj.com/problems/LPS/) | SPOJ | palindrom terpanjang |
| [SPOJ MSUBSTR](https://www.spoj.com/problems/MSUBSTR/) | SPOJ | counting |

---

## Preview Day 217 — Trie

Tiga hari terakhir kita menganalisis **satu string** sedalam-dalamnya. Mulai besok
kita menyimpan **banyak string bersama-sama**.

Trie adalah fondasi untuk **Aho-Corasick** (Day 219), yang pada dasarnya adalah
**KMP automaton untuk banyak pola sekaligus** — jadi tabel `aut` yang kamu bangun
di Day 214 akan kembali, kali ini di atas pohon.
