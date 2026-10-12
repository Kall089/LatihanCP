# Day 127 — Dijkstra dengan Priority Queue

> **Ide satu kalimat:** selalu keluarkan simpul terdekat yang belum final — dan sadari bahwa seluruh algoritma ini berdiri di atas satu asumsi yang **runtuh total** begitu ada bobot negatif.

---

## Tujuan Pembelajaran

- [ ] Menulis Dijkstra `O(E log V)` dari nol dalam < 3 menit
- [ ] Menjelaskan **kenapa** simpul yang keluar dari heap sudah pasti final
- [ ] Menunjukkan **contoh tandingan konkret** di mana bobot negatif membuat Dijkstra salah
- [ ] Memakai teknik **lazy deletion** (skip entri usang) alih-alih `decrease-key`
- [ ] Merekonstruksi jalur terpendek dengan `parent[]`
- [ ] Menghitung **banyak jalur terpendek**, min/max edge, dan varian lain
- [ ] Memilih di antara Dijkstra, BFS 0-1, Bellman-Ford, dan DP-DAG

---

## Struktur Folder

```
Day-127 (Dijkstra dengan Priority Queue)/
├── README.md
├── materi.md
├── teori/Day_127_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (50 menit)

1. **Bagian 3** — bukti kebenaran. Baca sampai kamu bisa menyebut di kalimat
   mana persis asumsi "bobot ≥ 0" dipakai.
2. **Bagian 5** — contoh tandingan bobot negatif. Trace dengan tangan; ini
   yang diminta soal hari ini.
3. **Bagian 4.2** — lazy deletion. Ini bukan trik gaya, ini yang membuat
   implementasi C++ standar bekerja.

### Langkah 2 — Template (10 menit)

```cpp
priority_queue<pll, vector<pll>, greater<pll>> pq;
dist[s] = 0; pq.push({0, s});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;              // ENTRI USANG
    for (auto [v, w] : g[u])
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
}
```

### Langkah 3 — Latihan (140 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Jarak Terpendek Dasar | Easy | 20 mnt | template, long long |
| 2 | Rekonstruksi Rute | Easy | 20 mnt | parent[] |
| 3 | Bukti Dijkstra Gagal | Medium | 25 mnt | contoh tandingan negatif |
| 4 | Menghitung Jalur Terpendek | Medium | 25 mnt | dist + cnt |
| 5 | Jalur dengan Edge Termahal Minimum | Medium | 25 mnt | ganti operator gabung |
| 6 | Dijkstra dengan State Ganda | Hard | 35 mnt | dist[v][k] |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1671, 1195, LC 743, 1631).
**06–10** varian (counting, minimax, k-shortest, node splitting).
**11–15** level kontes (CF 20C, 545E, tiket diskon, grid berbobot, multi-source).

---

## Cheatsheet

```
SYARAT MUTLAK: SEMUA bobot >= 0. Satu edge negatif saja -> jawaban bisa salah.
  Ada bobot negatif -> Bellman-Ford (Day 129) atau, kalau DAG, DP-DAG (Day 120).
  Bobot hanya 0 dan 1 -> BFS 0-1 (Day 115), O(V+E), lebih cepat.

INTI ALGORITMA (lazy deletion, gaya C++)
  pq berisi pasangan (jarak, simpul), MIN-heap
  pop -> kalau d > dist[u] SKIP (entri usang)
  kalau tidak, relaksasi semua tetangga, push yang membaik

KOMPLEKSITAS  O(E log V)   [heap biner; pq bisa memuat sampai E entri]
  versi O(V^2) tanpa heap: lebih baik untuk graf SANGAT padat (E ~ V^2)

KENAPA POP = FINAL (dan di mana bobot>=0 dipakai)
  Saat u di-pop dengan jarak d, andaikan ada jalur lebih pendek ke u.
  Jalur itu harus keluar dari himpunan simpul yang sudah final lewat suatu
  edge (x -> y) dengan y BELUM final. Maka dist[y] <= panjang prefiks
  <= panjang total < d. Tapi y ada di heap dengan nilai <= d, jadi y akan
  di-pop DULUAN, bukan u. Kontradiksi.
  ^^^ Langkah "panjang prefiks <= panjang total" HANYA benar kalau sisa
      jalurnya tidak negatif. Di situlah syaratnya dipakai.

TIPE DATA
  dist: long long. 2*10^5 edge * 10^9 = 2*10^14, int jebol.
  INF = LLONG_MAX/4 (bukan LLONG_MAX -> dist[u]+w overflow)

VARIAN (ubah operator gabung / isi state)
  hitung jalur terpendek : baru <  dist[v] -> cnt[v] = cnt[u]
                           baru == dist[v] -> cnt[v] += cnt[u]
  minimax (edge termahal minimum) : dist[v] = min(dist[v], max(dist[u], w))
  maximin (bottleneck terlebar)   : dist[v] = max(dist[v], min(dist[u], w))
  jalur terandal (probabilitas)   : max-heap, dist[v] = max(dist[v], dist[u]*p)
  k kupon / k penerbangan         : dist[v][k], heap menyimpan (d, v, k)
  banyak sumber                   : push SEMUA sumber di awal dengan dist 0

JEBAKAN
  - lupa "if (d > dist[u]) continue;" -> tetap benar tapi bisa jauh lebih lambat
  - priority_queue default MAX-heap: wajib greater<>
  - graf tak berarah: push kedua arah
  - edge ganda / self-loop: aman, relaksasi menanganinya sendiri
```

---

## Common Mistakes

1. **Memakai Dijkstra pada graf berbobot negatif.** Kesalahan nomor satu, dan hasilnya *bukan* sekadar suboptimal — ia salah.
2. **Membalik tanda bobot untuk mencari jalur terpanjang** — membuat semua bobot negatif; Dijkstra tidak berlaku.
3. **`int` untuk `dist`** → overflow diam-diam.
4. **`INF = LLONG_MAX`** → `dist[u] + w` overflow sebelum sempat dibandingkan.
5. **Lupa `greater<>`** pada `priority_queue` → jadi max-heap.
6. **Lupa `if (d > dist[u]) continue;`** → heap membengkak, TLE pada graf besar.
7. **Memakai array `visited` bergaya BFS** dan menandai simpul saat *dipush* alih-alih saat *dipop*.
8. **Graf tak berarah tapi hanya push satu arah.**
9. **Mereset `dist` dengan `memset(dist, 0x3f, ...)` lalu memakai `long long`** — nilainya bukan yang kamu kira.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis Dijkstra lengkap dari ingatan
- [ ] Bisa menyebut kalimat persis dalam bukti yang memakai asumsi bobot ≥ 0
- [ ] Bisa membuat contoh tandingan 4 simpul di mana Dijkstra salah
- [ ] Tahu bedanya lazy deletion dan decrease-key
- [ ] Bisa mengubah Dijkstra jadi minimax hanya dengan mengganti satu baris
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1671 dan LC 743 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1671 — Shortest Routes I](https://cses.fi/problemset/task/1671) | CSES | Dijkstra dasar |
| [CSES 1195 — Flight Discount](https://cses.fi/problemset/task/1195) | CSES | state ganda |
| [CSES 1202 — Investigation](https://cses.fi/problemset/task/1202) | CSES | count + min/max edge |
| [LC 743 — Network Delay Time](https://leetcode.com/problems/network-delay-time/) | LeetCode | dasar |
| [LC 1631 — Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) | LeetCode | minimax di grid |
| [LC 787 — Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) | LeetCode | dist[v][k] |
| [CF 20C — Dijkstra?](https://codeforces.com/problemset/problem/20/C) | Codeforces | rekonstruksi |
| [CF 545E — Paths and Trees](https://codeforces.com/problemset/problem/545/E) | Codeforces | shortest path tree |

---

## Preview

**Day 128** — varian Dijkstra: menghitung jalur, k-shortest path, node splitting.
**Day 129** — **Bellman-Ford**, yang menerima bobot negatif dan mendeteksi
siklus negatif — tepat pada titik di mana Dijkstra menyerah hari ini.
