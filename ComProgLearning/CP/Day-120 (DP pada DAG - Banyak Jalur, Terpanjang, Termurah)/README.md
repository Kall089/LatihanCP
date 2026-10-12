# Day 120 — DP pada DAG: Banyak Jalur, Terpanjang, Termurah

> **Ide satu kalimat:** urutan topologis membuat DAG jadi "array", dan begitu simpul berbaris, tiga pertanyaan berbeda dijawab oleh **kerangka loop yang persis sama** — hanya operator penggabungnya yang ditukar.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan kenapa **urutan topologis = urutan evaluasi DP yang benar**
- [ ] Menulis kerangka DP-di-DAG sekali, lalu memakainya untuk **tiga** pertanyaan
- [ ] **Menghitung banyak jalur** (dengan modulo) dari sumber ke tujuan
- [ ] Mencari **jalur terpanjang** — mudah di DAG, NP-hard di graf umum
- [ ] Mencari **jalur termurah** — dan tahu kapan ini mengalahkan Dijkstra
- [ ] **Merekonstruksi** jalur optimalnya, bukan cuma nilainya
- [ ] Membedakan **forward (push)** dan **backward (pull)** DP dan memilih yang tepat

---

## Struktur Folder

```
Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)/
├── README.md
├── materi.md
├── teori/Day_120_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)

1. **Bagian 2** — kenapa DAG boleh di-DP dan graf bersiklus tidak. Ini bukan
   detail teknis; ini seluruh alasan hari ini ada.
2. **Bagian 4** — tabel tiga pertanyaan berdampingan. Perhatikan bahwa hanya
   kolom "gabung" dan "nilai awal" yang berubah.
3. **Bagian 6** — rekonstruksi jalur. Hampir semua soal kontes menuntut ini.

### Langkah 2 — Template (10 menit)

Kerangka yang sama untuk semuanya:

```cpp
for (int u : topoOrder)
    for (auto [v, w] : g[u])
        dp[v] = GABUNG(dp[v], dp[u] OPERASI w);
```

| Pertanyaan | init | GABUNG | OPERASI |
|---|---|---|---|
| banyak jalur | dp[s]=1, sisanya 0 | `+` (mod) | `* 1` (abaikan bobot) |
| terpanjang | dp[s]=0, sisanya −INF | `max` | `+ w` |
| termurah | dp[s]=0, sisanya +INF | `min` | `+ w` |

### Langkah 3 — Latihan (130 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Banyak Jalur 1→N | Easy | 20 mnt | dp aditif + modulo |
| 2 | Jalur Terpanjang di DAG | Easy | 20 mnt | max, −INF untuk tak terjangkau |
| 3 | Jalur Termurah di DAG | Medium | 20 mnt | min, boleh bobot NEGATIF |
| 4 | Rekonstruksi Rute Optimal | Medium | 25 mnt | parent[] |
| 5 | Tiga Jawaban Sekaligus | Medium | 20 mnt | satu sapuan, tiga array |
| 6 | Jalur Terpanjang Melewati Simpul Wajib | Hard | 30 mnt | dekomposisi dua arah |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1680, 1681, AtCoder DP-G, DP-H).
**06–10** varian (hitung jalur mod, rekonstruksi, dua kriteria).
**11–15** level kontes (DAG dari grid, DAG dari LIS, DAG kondensasi SCC).

---

## Cheatsheet

```
SYARAT MUTLAK: graf harus DAG. Ada siklus -> DP tidak terdefinisi
  (jalur terpanjang bisa tak hingga; jumlah jalur bisa tak hingga).

DUA GAYA
  PULL (backward): dp[v] dihitung dari semua PENDAHULU v
      butuh graf terbalik; loop simpul dalam urutan topologis
  PUSH (forward):  dp[u] sudah final -> lempar ke semua PENERUS
      tidak butuh graf terbalik; lebih sering dipakai
  Keduanya O(V + E). Pilih PUSH kalau ragu.

KERANGKA (PUSH)
  for u in topo:  for (v,w) in g[u]:  dp[v] = gabung(dp[v], f(dp[u], w))

TIGA PERTANYAAN, SATU KERANGKA
  banyak jalur  init dp[s]=1  lainnya 0      gabung +   (mod 1e9+7)
  terpanjang    init dp[s]=0  lainnya -INF   gabung max  f = dp[u]+w
  termurah      init dp[s]=0  lainnya +INF   gabung min  f = dp[u]+w

TAK TERJANGKAU
  WAJIB pakai sentinel (-INF / +INF) dan LEWATI simpul bersentinel,
  kalau tidak -INF + w akan overflow/menular. Cek: if (dp[u] == NEG) continue;

REKONSTRUKSI
  simpan par[v] = u setiap kali dp[v] DIPERBARUI (bukan setiap kali dilihat)
  telusuri balik dari tujuan, lalu reverse

KAPAN DP-DAG MENGALAHKAN DIJKSTRA
  - graf DAG dan ada bobot NEGATIF  -> Dijkstra salah, DP benar, O(V+E)
  - butuh jalur TERPANJANG          -> Dijkstra tidak bisa sama sekali
  - butuh MENGHITUNG jalur          -> DP alami

OVERFLOW
  banyak jalur: pakai modulo, atau __int128/unsigned long long kalau diminta eksak
  panjang jalur: 2*10^5 edge * 10^9 = 2*10^14 -> long long

BANYAK SUMBER: tambahkan super-source, atau init dp[u]=0 untuk semua u
  (tergantung apakah jalur boleh mulai di mana saja)
```

---

## Common Mistakes

1. **Memakai simpul bersentinel** (`-INF`) untuk merelaksasi tetangga → nilai sampah menyebar.
2. **Lupa modulo** pada penghitungan jalur → overflow senyap.
3. **Mengurutkan simpul dengan cara lain** (misalnya nomor simpul) — hanya urutan topologis yang menjamin `dp[u]` sudah final.
4. **Menjalankan DP pada graf bersiklus** — cek dulu dengan Kahn (Day 119).
5. **Menyimpan `parent` di tempat yang salah** — hanya saat `dp[v]` benar-benar berubah.
6. **`int` untuk total bobot** — overflow.
7. **Memakai Dijkstra untuk jalur terpanjang** dengan membalik tanda bobot — salah, karena bobot jadi negatif.
8. **Mengira "banyak jalur" berarti "banyak jalur terpendek"** — dua soal berbeda; yang kedua butuh gabungan min + count.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis kerangka `for u in topo: for (v,w) in g[u]` dari ingatan
- [ ] Bisa mengubah "terpanjang" jadi "termurah" hanya dengan mengganti 3 hal
- [ ] Tahu kenapa sentinel harus dilewati, bukan cuma diinisialisasi
- [ ] Bisa merekonstruksi jalur, bukan hanya nilainya
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1680 dan AtCoder DP-G paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1680 — Longest Flight Route](https://cses.fi/problemset/task/1680) | CSES | terpanjang + rekonstruksi |
| [CSES 1681 — Game Routes](https://cses.fi/problemset/task/1681) | CSES | banyak jalur mod |
| [CSES 1682 — Investigation](https://cses.fi/problemset/task/1202) | CSES | min + count + panjang |
| [AtCoder DP-G — Longest Path](https://atcoder.jp/contests/dp/tasks/dp_g) | AtCoder | terpanjang |
| [AtCoder DP-H — Grid 1](https://atcoder.jp/contests/dp/tasks/dp_h) | AtCoder | banyak jalur di grid |
| [LC 1857 — Largest Color Value in a DAG](https://leetcode.com/problems/largest-color-value-in-a-directed-graph/) | LeetCode | DP vektor di DAG |
| [CF 721C — Journey](https://codeforces.com/problemset/problem/721/C) | Codeforces | DP dua dimensi di DAG |

---

## Preview

**Day 121–126** melanjutkan graf dasar. **Day 127** memperkenalkan Dijkstra —
yang menyelesaikan jalur termurah pada graf **bersiklus**, dengan syarat bobot
tidak negatif. Perhatikan bahwa DP-DAG hari ini justru **boleh** bobot negatif;
perbedaan syarat inilah yang menentukan alat mana yang dipakai.
