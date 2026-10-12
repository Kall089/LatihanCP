# Day 149 — LCS & Edit Distance: Tabel Dua String

> **Ide satu kalimat:** satu tabel `(i, j)` untuk dua string, satu pertanyaan di setiap sel — "apakah huruf terakhirnya cocok?" — dan **edit distance adalah LCS dengan operator yang ditukar**.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan arti `dp[i][j]` pada DP dua string sebagai kalimat lengkap
- [ ] Menulis **LCS** `O(nm)` dan merekonstruksi barisannya
- [ ] Menulis **edit distance** (Levenshtein) dan menjelaskan **tiga operasinya** di tabel
- [ ] Melihat bahwa keduanya **tabel yang sama** dengan init & operator berbeda
- [ ] Menurunkan **LCSubstring** (berdekatan) dan tahu bedanya dari LCS
- [ ] Memakai **rolling array** untuk memangkas memori jadi `O(min(n,m))`
- [ ] Menurunkan **SCS** (supersequence terpendek) dan **jumlah penghapusan minimum** dari LCS
- [ ] Mengenali bahwa **LIS = LCS** antara permutasi dan versi terurutnya

---

## Struktur Folder

```
Day-149 (LCS dan Edit Distance - Tabel Dua String)/
├── README.md
├── materi.md
├── teori/Day_149_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (50 menit)

1. **Bagian 2** — kenapa state-nya dua dimensi, dan kenapa "huruf terakhir"
   adalah pertanyaan yang tepat.
2. **Bagian 5** — tabel perbandingan LCS vs edit distance. Perhatikan bahwa
   struktur loopnya identik.
3. **Bagian 6** — rekonstruksi. Hampir semua soal kontes menuntutnya.

### Langkah 2 — Template (10 menit)

```cpp
// LCS
if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

// EDIT DISTANCE
if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
else                  dp[i][j] = 1 + min({dp[i-1][j-1],   // ganti
                                          dp[i-1][j],     // hapus
                                          dp[i][j-1]});   // sisip
```

### Langkah 3 — Latihan (150 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | LCS Panjangnya | Easy | 20 mnt | tabel dasar |
| 2 | LCS + Rekonstruksi | Medium | 25 mnt | telusuri balik |
| 3 | Edit Distance | Medium | 25 mnt | tiga operasi |
| 4 | Edit Distance + Daftar Operasi | Hard | 30 mnt | rekonstruksi jejak |
| 5 | Substring Bersama Terpanjang | Medium | 25 mnt | berdekatan, reset ke 0 |
| 6 | Supersequence Terpendek | Hard | 25 mnt | turunan LCS |

### Langkah 4 — Tugas

**01–05** dasar (LC 1143, 72, 583, CSES 1639, AtCoder DP-F).
**06–10** varian (LCSubstring, SCS, biaya operasi berbeda, LCS tiga string).
**11–15** level kontes (Hirschberg `O(n)` memori, LCS dari permutasi via LIS, wildcard/regex matching).

---

## Cheatsheet

```
DEFINISI (tulis lengkap sebelum menulis kode!)
  dp[i][j] = jawaban untuk PREFIKS a[0..i-1] dan b[0..j-1]
  ukuran tabel (n+1) x (m+1). Baris/kolom 0 = string kosong.
  1-INDEXED di tabel, 0-INDEXED di string -> a[i-1], b[j-1]. Sumber bug utama.

LCS  (Longest Common SUBSEQUENCE)
  cocok  : dp[i][j] = dp[i-1][j-1] + 1
  beda   : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
  base   : dp[0][*] = dp[*][0] = 0
  Ada TIGA sel tetangga; yang diagonal hanya dipakai saat COCOK.

EDIT DISTANCE (Levenshtein)
  cocok  : dp[i][j] = dp[i-1][j-1]                    (gratis)
  beda   : dp[i][j] = 1 + min(diagonal, atas, kiri)
             diagonal = GANTI   a[i-1] -> b[j-1]
             atas     = HAPUS   a[i-1]
             kiri     = SISIP   b[j-1]
  base   : dp[i][0] = i   (hapus semua)
           dp[0][j] = j   (sisipkan semua)
  BASE-NYA BUKAN NOL. Ini beda paling penting dari LCS.

LONGEST COMMON SUBSTRING (berdekatan!)
  cocok  : dp[i][j] = dp[i-1][j-1] + 1
  beda   : dp[i][j] = 0                <-- RESET, bukan max
  jawaban: max atas SELURUH tabel, bukan dp[n][m]

TURUNAN DARI LCS
  hapus minimum agar dua string sama : n + m - 2*LCS
  supersequence terpendek (SCS)      : n + m - LCS
  LIS dari permutasi                 : LCS(perm, 1..n terurut)

ROLLING ARRAY  O(nm) -> O(min(n,m)) memori
  hanya butuh baris i-1 dan i. SIMPAN dp[i-1][j-1] SEBELUM ditimpa.
  Tidak bisa dipakai kalau butuh REKONSTRUKSI (kecuali Hirschberg).

REKONSTRUKSI (telusuri balik dari dp[n][m])
  LCS: kalau a[i-1]==b[j-1] -> ambil huruf, i--, j--
       else pindah ke tetangga yang nilainya SAMA dengan dp[i][j]
  ED : bandingkan dp[i][j] dengan ketiga tetangga untuk tahu operasi mana

KOMPLEKSITAS  O(n*m) waktu. n, m <= 5000 aman; 10^5 x 10^5 TIDAK.
  (LCS untuk string besar: bitset O(nm/64), atau Hunt-Szymanski)
```

---

## Common Mistakes

1. **Indeks tertukar** — `a[i]` alih-alih `a[i-1]`. Bug nomor satu di DP dua string.
2. **Base case edit distance diisi 0** — harus `i` dan `j`.
3. **LCSubstring memakai `max` alih-alih reset ke 0.**
4. **Jawaban LCSubstring diambil dari `dp[n][m]`** — harusnya `max` seluruh tabel.
5. **Rolling array tanpa menyimpan nilai diagonal** sebelum ditimpa.
6. **Rekonstruksi dari tabel yang sudah digulung** — mustahil.
7. **Alokasi `dp` berukuran `n × m`** alih-alih `(n+1) × (m+1)`.
8. **Mengira LCS unik** — panjangnya unik, barisannya belum tentu.
9. **`int` untuk tabel besar** — `5000 × 5000 × 4 byte` = 100 MB, bisa MLE.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis kedua rekurens dari ingatan
- [ ] Bisa menyebut operasi apa yang diwakili atas/kiri/diagonal pada edit distance
- [ ] Tahu kenapa base case keduanya berbeda
- [ ] Bisa merekonstruksi LCS dan daftar operasi edit distance
- [ ] Bisa mengubah LCS jadi LCSubstring dengan mengganti satu baris
- [ ] Bisa menurunkan SCS dan "hapus minimum" dari LCS
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (LC 1143 dan LC 72 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 1143 — Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) | LeetCode | dasar |
| [LC 72 — Edit Distance](https://leetcode.com/problems/edit-distance/) | LeetCode | Levenshtein |
| [LC 583 — Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/) | LeetCode | turunan LCS |
| [LC 1092 — Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/) | LeetCode | SCS + rekonstruksi |
| [LC 44 — Wildcard Matching](https://leetcode.com/problems/wildcard-matching/) | LeetCode | tabel dua string |
| [LC 10 — Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/) | LeetCode | varian sulit |
| [CSES 1639 — Edit Distance](https://cses.fi/problemset/task/1639) | CSES | Levenshtein |
| [AtCoder DP-F — LCS](https://atcoder.jp/contests/dp/tasks/dp_f) | AtCoder | LCS + rekonstruksi |

---

## Preview

**Day 150** — DP pada grid: tabel dua dimensi lagi, tapi kali ini
dimensinya adalah **posisi**, bukan prefiks string. Kamu akan melihat bahwa
"telusuri balik untuk merekonstruksi" adalah teknik yang sama persis.
**Day 151** — range DP, di mana state-nya adalah **interval** `[l, r]` dan
urutan pengisiannya bukan lagi baris demi baris melainkan **berdasarkan
panjang interval**.
