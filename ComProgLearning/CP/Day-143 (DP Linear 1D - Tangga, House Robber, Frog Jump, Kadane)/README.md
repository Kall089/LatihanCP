# Day 143 — DP Linear 1D: Tangga, House Robber, Frog Jump & Kadane

> **Ide satu kalimat:** empat soal yang kelihatan berbeda ternyata satu bentuk yang sama — `dp[i]` bergantung pada beberapa `dp` sebelumnya, dan yang membedakan hanya **apa yang boleh dilewati**.

---

## Tujuan Pembelajaran

- [ ] Menulis rekurens 1D dari deskripsi soal tanpa menghafal rumus
- [ ] **Climbing stairs** — hitung cara, dan variannya (langkah k, ada tangga rusak)
- [ ] **House robber** — larangan mengambil dua yang bersebelahan, termasuk versi melingkar
- [ ] **Frog jump** — biaya minimum dengan lompatan sampai `k`
- [ ] **Kadane** — subarray dengan jumlah maksimum, dan hubungannya dengan DP
- [ ] Menjelaskan kenapa Kadane sebenarnya **DP dua state yang disederhanakan**
- [ ] **Rolling variable** — memangkas memori `O(n)` menjadi `O(1)`
- [ ] Merekonstruksi jawaban (rumah mana yang dirampok, subarray mana yang dipilih)

---

## Struktur Folder

```
Day-143 (DP Linear 1D - Tangga, House Robber, Frog Jump, Kadane)/
├── README.md
├── materi.md
├── teori/Day_143_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Bagian 2** — cara menurunkan rekurens dari "keputusan terakhir". Ini
   metodenya; sisanya cuma penerapan.
2. **Bagian 6** — Kadane sebagai DP. Sebagian besar orang menghafal Kadane
   sebagai trik; hari ini kamu melihat dari mana ia datang.
3. **Bagian 7** — rolling variable. Pola yang akan kamu pakai seumur hidup.

### Langkah 2 — Template (10 menit)

Empat rekurens yang harus hafal di luar kepala:

```cpp
// tangga      : dp[i] = dp[i-1] + dp[i-2]
// house robber: dp[i] = max(dp[i-1], dp[i-2] + a[i])
// frog jump   : dp[i] = min over j in 1..k of dp[i-j] + |h[i]-h[i-j]|
// kadane      : cur = max(a[i], cur + a[i]); best = max(best, cur)
```

### Langkah 3 — Latihan (130 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Menaiki Tangga | Easy | 15 mnt | dp aditif, modulo |
| 2 | Tangga Rusak & Langkah k | Easy | 20 mnt | larangan + jendela k |
| 3 | Perampok Rumah | Medium | 20 mnt | max dua pilihan |
| 4 | Perampok Rumah Melingkar | Medium | 25 mnt | dua kali jalan linear |
| 5 | Katak Melompat (Frog Jump) | Medium | 25 mnt | min, biaya absolut |
| 6 | Kadane + Rekonstruksi | Medium | 25 mnt | subarray maksimum, indeksnya |

### Langkah 4 — Tugas

**01–05** dasar (LC 70, 198, 213, 746, AtCoder DP-A/B).
**06–10** varian (Kadane melingkar, produk maksimum, jumlah maksimum tanpa dua bersebelahan).
**11–15** level kontes (Kadane 2D, DP + deque untuk k besar, rekonstruksi, DP dengan cooldown).

---

## Cheatsheet

```
CARA MENURUNKAN REKURENS 1D (selalu sama)
  1. definisikan dp[i] dengan KALIMAT LENGKAP
     "dp[i] = jawaban terbaik dengan mempertimbangkan a[0..i]"
     atau "dp[i] = jawaban terbaik yang BERAKHIR TEPAT di i"   <- BEDA!
  2. tanyakan: apa KEPUTUSAN TERAKHIR yang membawa ke i?
  3. tulis semua kemungkinannya, gabungkan dengan + / max / min
  4. tentukan base case, lalu CEK dengan tangan untuk n = 1 dan n = 2

EMPAT POLA INTI
  tangga        dp[i] = dp[i-1] + dp[i-2]                 (hitung cara)
  house robber  dp[i] = max(dp[i-1], dp[i-2] + a[i])      (larangan tetangga)
  frog jump     dp[i] = min_{j=1..k} dp[i-j] + cost(i-j,i)
  kadane        cur = max(a[i], cur + a[i]) ; best = max(best, cur)

"BERAKHIR DI i" vs "SAMPAI i" -- SUMBER BUG NOMOR SATU
  kadane memakai "berakhir TEPAT di i" -> jawabannya max atas SELURUH dp
  house robber memakai "sampai i"      -> jawabannya dp[n-1] saja

MELINGKAR (rumah pertama dan terakhir bertetangga)
  jalankan versi linear DUA KALI:
    (a) pada a[0..n-2]   (buang yang terakhir)
    (b) pada a[1..n-1]   (buang yang pertama)
  ambil max. n == 1 harus ditangani terpisah.

ROLLING VARIABLE  (memori O(n) -> O(1))
  dp[i] hanya butuh dp[i-1] dan dp[i-2]  ->  simpan dua variabel
  ll a = 0, b = 0;
  for x : arr { ll c = max(b, a + x); a = b; b = c; }   // b = jawaban
  URUTAN PENUGASAN PENTING. Salah urutan = a dan b sama-sama rusak.

KADANE
  best diinisialisasi a[0], BUKAN 0 -- kalau semua negatif, jawaban 0 SALAH
  (kecuali soal mengizinkan subarray kosong; BACA SOALNYA)
  varian melingkar: max(kadaneBiasa, total - kadaneMinimum)
                    kasus khusus: semua negatif -> jawaban = kadaneBiasa
  varian PRODUK: simpan max DAN min (angka negatif membalik peran)

OVERFLOW
  tangga: modulo 1e9+7
  kadane: 2*10^5 * 10^9 = 2*10^14 -> long long
```

---

## Common Mistakes

1. **Definisi `dp[i]` tidak ditulis sebagai kalimat lengkap** — semua bug berikutnya berakar di sini.
2. **Mencampur "berakhir tepat di i" dan "sampai i"** lalu salah mengambil jawaban akhir.
3. **Kadane diinisialisasi `best = 0`** padahal semua elemen negatif → jawaban salah.
4. **House robber melingkar** dikerjakan dengan satu sapuan dan tambalan `if` — hampir selalu salah; jalankan dua kali.
5. **Base case `n = 1` dan `n = 2`** tidak diperiksa.
6. **Urutan penugasan rolling variable terbalik.**
7. **Frog jump dengan `k` besar** dikerjakan `O(nk)` → TLE; butuh monotonic deque (Day 37).
8. **Lupa modulo** pada soal hitung cara.
9. **`int` untuk akumulasi jumlah** → overflow.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis keempat rekurens dari ingatan
- [ ] Bisa menjelaskan Kadane sebagai DP, bukan sebagai trik
- [ ] Tahu kapan jawaban ada di `dp[n-1]` dan kapan di `max(dp)`
- [ ] Bisa mengubah versi `O(n)` memori jadi `O(1)` tanpa berpikir lama
- [ ] Bisa menangani varian melingkar
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 3 soal (LC 70, 198, 53 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [LC 70 — Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) | LeetCode | dasar |
| [LC 746 — Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) | LeetCode | min |
| [LC 198 — House Robber](https://leetcode.com/problems/house-robber/) | LeetCode | larangan tetangga |
| [LC 213 — House Robber II](https://leetcode.com/problems/house-robber-ii/) | LeetCode | melingkar |
| [LC 53 — Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | LeetCode | Kadane |
| [LC 918 — Maximum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) | LeetCode | Kadane melingkar |
| [LC 152 — Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | LeetCode | max+min |
| [AtCoder DP-A — Frog 1](https://atcoder.jp/contests/dp/tasks/dp_a) | AtCoder | frog jump |
| [AtCoder DP-B — Frog 2](https://atcoder.jp/contests/dp/tasks/dp_b) | AtCoder | lompatan k |
| [CSES 1633 — Dice Combinations](https://cses.fi/problemset/task/1633) | CSES | tangga langkah 6 |

---

## Preview

**Day 144–147** — knapsack dan variannya: DP yang state-nya bukan lagi cuma
indeks, tapi indeks **dan kapasitas**. **Day 148** — LIS, di mana rekurens
`O(n²)` yang alami dipercepat jadi `O(n log n)`. Semua itu berdiri di atas
kebiasaan yang kamu bangun hari ini: **tulis definisi `dp` sebagai kalimat
lengkap sebelum menulis kode apa pun.**
