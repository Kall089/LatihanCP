# Day 40 — Counting & Frequency Array sebagai Senjata Utama

> **Ide satu kalimat:** kotak surat, bukan perbandingan semua-lawan-semua — satu sapuan memasukkan, satu sapuan membaca.

---

## Tujuan Pembelajaran

- [ ] Memilih **array** alih-alih `map` ketika domainnya kecil, dan tahu selisihnya ~100×
- [ ] Memakai frekuensi untuk **anagram**, **mode**, **pasangan**
- [ ] Menghitung pasangan **berselisih K** dan **berjumlah K** dengan pola yang benar
- [ ] Menggabungkan frekuensi dengan **prefix sum** untuk query rentang nilai
- [ ] Memakai **26 prefix sum** untuk query substring
- [ ] Menghitung **frekuensi dari frekuensi**
- [ ] Membersihkan array pada multi-test case **tanpa** `memset`

---

## Struktur Folder

```
Day-40 (Counting dan Frequency Array sebagai Senjata Utama)/
├── README.md
├── teori/Day_40_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (30 menit)

1. **Bagian "kenapa array, bukan map"** — angka konkret 1 ns vs 100 ns. Ini bukan
   optimasi mikro; untuk `n = 10^6` itu selisih AC dan TLE.
2. **Dua pola sapuan** — terutama pola 2 (hitung dulu, daftarkan kemudian).
   Pola itu muncul di Day 29, hari ini, dan akan muncul lagi berkali-kali.
3. **Trace 4.2** — demonstrasi bug urutan operasi. Pendek tapi meyakinkan.

### Langkah 2 — Template (10 menit)

Yang harus jadi refleks:

```cpp
const int MAKS = 1e6 + 5;
int cnt[MAKS];              // GLOBAL: otomatis nol, tidak membebani stack
```

Dan untuk multi-test case, **jangan pernah** `memset` di dalam loop.

### Langkah 3 — Latihan (75 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Nilai Paling Sering | Easy | 10 mnt | array global, tie-breaking |
| 2 | Anagram Beruntun | Easy | 10 mnt | 26 huruf, cek murah dulu |
| 3 | Pasangan Selisih K | Medium | 20 mnt | urutan operasi, `K = 0` |
| 4 | Query Rentang Nilai | Medium | 15 mnt | frekuensi + prefix |
| 5 | Huruf dalam Substring | Hard | 20 mnt | 26 prefix, hitung memori |
| 6 | Tepat K Kemunculan | Hard | 25 mnt | dua lapis + pembersihan |

Exercise 6 adalah yang paling penting hari ini — bukan karena algoritmanya,
tetapi karena **pembersihan array** adalah penyebab TLE yang paling sering tidak
disadari.

### Langkah 4 — Tugas

**01–05** terapan langsung (CSES 1621, LC 242, LC 169). **06–10** pasangan dan query
(CSES 1640). **11–15** level kontes (LC 1248, LC 1200).

Tugas 11 dan 14 menggabungkan hari ini dengan Day 29 dan Day 33 — perhatikan
bagaimana teknik-teknik ini saling menumpuk.

---

## Cheatsheet

```
const int MAKS = 1e6 + 5;
int cnt[MAKS];                     GLOBAL

POLA 1: for (x : a) cnt[x]++;  lalu  for (v : domain) baca cnt[v]
POLA 2: for (x : a) { hasil += cnt[pasangan(x)]; cnt[x]++; }
        hitung SEBELUM mendaftarkan diri -> tidak berpasangan dengan diri
        sendiri, dan tiap pasangan terhitung sekali

selisih K : hasil += cnt[x-K] + cnt[x+K]     K == 0 HARUS dipisah
jumlah K  : hasil += cnt[K-x]
anagram   : cek panjang, hitung s, --cnt saat menyapu t, negatif -> bukan
<= x      : ubah cnt jadi prefix sum atas NILAI
substring : 26 prefix, pre[i+1] = pre[i] lalu naikkan satu slot
tepat k kali : dua lapis -> cnt[nilai], lalu cntCnt[cnt[nilai]]

PILIH ALAT
  domain <= 1e6        -> array          (~1 ns)
  domain besar, n kecil -> kompresi (Day 38) lalu array
  online               -> map            (~100 ns)

MULTI TEST CASE
  JANGAN: memset(cnt, 0, sizeof cnt)  di dalam loop  -> O(V) per kasus
  PAKAI : for (x : a) cnt[x] = 0;                    -> O(n) per kasus
  atau  : array cap waktu, stamp[x] != kasusKe berarti kosong

OVERFLOW: hitungan pasangan bisa 2e10 -> long long
```

---

## Common Mistakes

1. **`memset` array besar di dalam loop test case.** TLE paling halus di topik ini.
2. **Mendaftarkan diri sebelum menghitung.** Elemen berpasangan dengan dirinya sendiri.
3. **`K = 0` tidak dipisah.** Setiap pasangan terhitung dua kali.
4. **`int` untuk hitungan pasangan.** Bisa mencapai `2·10^10`.
5. **Nilai negatif sebagai indeks.** Pakai offset atau kompres.
6. **Array besar di dalam fungsi.** 4 MB di stack → segmentation fault.
7. **`map` padahal domain kecil.** Kehilangan faktor 100 secara cuma-cuma.
8. **Lupa cek panjang pada anagram.**

---

## Checklist Sebelum Lanjut ke Day 41/42

- [ ] Bisa menjelaskan kenapa array frekuensi harus global
- [ ] Bisa menjelaskan kenapa "hitung dulu, daftarkan kemudian" itu benar
- [ ] Tahu apa yang salah dengan `memset` di dalam loop test case
- [ ] Bisa memutuskan array vs `map` dalam 5 detik dari batasan soal
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1621 dan CSES 1640 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1621 — Distinct Numbers](https://cses.fi/problemset/task/1621) | CSES | nilai berbeda |
| [CSES 1640 — Sum of Two Values](https://cses.fi/problemset/task/1640) | CSES | pasangan berjumlah K |
| [LC 242 — Valid Anagram](https://leetcode.com/problems/valid-anagram/) | LeetCode | anagram |
| [LC 169 — Majority Element](https://leetcode.com/problems/majority-element/) | LeetCode | mode / Boyer–Moore |
| [LC 1200 — Minimum Absolute Difference](https://leetcode.com/problems/minimum-absolute-difference/) | LeetCode | counting sort |
| [LC 1248 — Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/) | LeetCode | counting + prefix |
| [ABC 155 C — Poll](https://atcoder.jp/contests/abc155/tasks/abc155_c) | AtCoder | frekuensi + sort |

---

## Preview Day 41–42 dan Day 43

Day 41–42 adalah **latihan terpadu dan review** untuk seluruh teknik array
(Day 29–40): prefix sum, difference array, two pointers, sliding window, Kadane,
monotonic stack/deque, kompresi, dan counting.

Setelah itu Day 43 memulai blok **sorting**, dan counting sort yang kamu lihat sekilas
hari ini akan kembali sebagai algoritma pengurutan penuh di Day 46 — lengkap dengan
radix sort dan analisis kapan ia mengalahkan `sort` bawaan.
