# Day 119 — Topological Sort: Algoritma Kahn & Deteksi Siklus

> **Ide satu kalimat:** urutkan simpul sehingga setiap panah menunjuk ke kanan — dan kalau tidak bisa, berarti ada siklus.

---

## Tujuan Pembelajaran

- [ ] Menjelaskan apa itu **urutan topologis** dan kapan ia ada
- [ ] Menulis **Kahn (BFS in-degree)** dari nol dalam < 2 menit
- [ ] Menulis versi **DFS post-order + reverse** dan tahu bedanya
- [ ] Memakai `hasil.size() != n` sebagai **detektor siklus** pada graf berarah
- [ ] Menghasilkan urutan topologis **leksikografis terkecil** dengan priority_queue
- [ ] Mengenali kapan urutannya **unik** (setiap langkah antrean berisi tepat 1 simpul)
- [ ] Menerjemahkan soal "prasyarat / dependency" menjadi graf berarah

---

## Struktur Folder

```
Day-119 (Topological Sort - Algoritma Kahn dan Deteksi Siklus)/
├── README.md
├── materi.md
├── teori/Day_119_Teori_Lengkap.md
├── latihan/exercise_1.cpp .. exercise_6.cpp
├── solusi/solution_1.cpp .. solution_6.cpp
├── tugas/tugas_01.cpp .. tugas_15.cpp
└── template/template.cpp
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (40 menit)

1. **Definisi & syarat** — urutan topologis ADA jika dan hanya jika graf adalah DAG.
2. **Kahn langkah demi langkah** — trace bagian 4 dengan tangan, catat isi antrean tiap iterasi.
3. **Kenapa `size != n` berarti siklus** — ini inti hari ini, bukan efek samping.

### Langkah 2 — Template (10 menit)

Yang harus jadi refleks:

```cpp
vector<int> kahn(int n, vector<vector<int>>& g) {
    vector<int> indeg(n + 1, 0), ord;
    for (int u = 1; u <= n; u++) for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 1; u <= n; u++) if (!indeg[u]) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop(); ord.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ord;   // ord.size() < n  =>  ADA SIKLUS
}
```

### Langkah 3 — Latihan (120 menit)

| # | Judul | Tingkat | Target | Konsep |
|---|-------|---------|--------|--------|
| 1 | Urutan Kuliah | Easy | 20 mnt | Kahn dasar, indegree |
| 2 | Deteksi Siklus Berarah | Easy | 15 mnt | `size != n` |
| 3 | Urutan Leksikografis Terkecil | Medium | 20 mnt | priority_queue |
| 4 | Apakah Urutannya Unik? | Medium | 20 mnt | antrean berukuran 1 |
| 5 | Rantai Terpanjang Prasyarat | Medium | 25 mnt | level/longest path di DAG |
| 6 | Rekonstruksi Urutan dari Perbandingan | Hard | 30 mnt | model graf dari data |

### Langkah 4 — Tugas

**01–05** dasar (CSES 1679, LC 207, LC 210, AtCoder).
**06–10** varian (leksikografis, unik, level, urutan alien).
**11–15** level kontes (CF 510C, semester paralel, deadlock, DP di atas topo order).

---

## Cheatsheet

```
DEFINISI
  Urutan topologis: barisan semua simpul sehingga untuk setiap edge u->v,
  u muncul SEBELUM v.
  ADA  <=> graf berarah TANPA siklus (DAG).
  TIDAK unik secara umum. Bisa banyak sekali urutan yang sah.

KAHN (BFS in-degree)              O(V + E)
  1. hitung indeg[v] untuk semua v
  2. antre semua simpul dengan indeg == 0
  3. ambil u, tulis ke hasil, kurangi indeg tetangganya
  4. tetangga yang indeg-nya jadi 0 -> masuk antrean
  5. AKHIR: ord.size() == n ? urutan valid : ADA SIKLUS

DFS (post-order + reverse)        O(V + E)
  dfs(u): tandai, kunjungi anak, PUSH u SETELAH anak selesai
  reverse(hasil)
  deteksi siklus butuh 3 WARNA: 0 belum, 1 sedang di stack, 2 selesai
  ketemu warna 1 -> back edge -> SIKLUS

VARIAN
  leksikografis terkecil : ganti queue -> priority_queue<int,vector<int>,greater<>>
                            (O((V+E) log V))
  urutan unik?           : setiap iterasi antrean harus berukuran TEPAT 1
  longest chain / level  : lvl[v] = max(lvl[v], lvl[u]+1) saat relaksasi
  banyak urutan topologis: #P-hard umum; n<=20 -> DP bitmask

KENAPA SIKLUS MEMBUAT KAHN MACET
  Setiap simpul di dalam siklus punya minimal satu pendahulu yang juga di
  siklus. Indeg-nya tidak pernah bisa turun ke 0, jadi ia tidak pernah masuk
  antrean. Semua simpul siklus (dan keturunannya) hilang dari hasil.

JEBAKAN
  - graf TAK BERARAH tidak punya urutan topologis. Jangan dipaksakan.
  - indeg dihitung dari SEMUA edge, termasuk simpul terisolasi (indeg 0, ikut).
  - self-loop u->u langsung berarti tidak ada urutan.
  - edge ganda u->v dua kali: indeg[v] naik 2, dan turun 2 juga -> aman.
  - reset indeg antar test case.
```

---

## Common Mistakes

1. **Lupa memasukkan simpul terisolasi** — indeg 0, harus ikut ke hasil.
2. **Mengecek siklus dengan "visited" saja** (cara graf tak berarah) — pada graf berarah butuh 3 warna, atau cukup pakai Kahn.
3. **`ord.size() == n` tidak dicek** — program mengeluarkan urutan cacat tanpa peringatan.
4. **Indeg tidak direset** antar test case.
5. **Menggunakan `queue` lalu mengurutkan hasil** untuk mendapat leksikografis terkecil — salah total; harus `priority_queue` di dalam proses.
6. **Membalik arah edge** saat memodelkan prasyarat. "A syarat B" berarti `A -> B`.
7. **Rekursi DFS terlalu dalam** pada rantai 10^5 simpul — Kahn iteratif lebih aman.
8. **Menganggap urutan topologis unik** dan membandingkan output dengan satu jawaban tetap.

---

## Checklist Sebelum Lanjut

- [ ] Bisa menulis Kahn dari ingatan tanpa melihat
- [ ] Bisa menjelaskan mengapa simpul dalam siklus tak pernah mencapai indeg 0
- [ ] Bisa mengubah Kahn menjadi versi leksikografis dalam 10 detik
- [ ] Tahu cara memeriksa keunikan urutan
- [ ] Sudah menyelesaikan minimal exercise 1–4
- [ ] Sudah AC minimal 2 soal (CSES 1679 dan LC 210 paling cepat)

---

## Link Soal Online

| Soal | Platform | Fokus |
| ---- | -------- | ----- |
| [CSES 1679 — Course Schedule](https://cses.fi/problemset/task/1679) | CSES | Kahn + deteksi siklus |
| [CSES 1757 — Longest Flight Route](https://cses.fi/problemset/task/1680) | CSES | topo + DP |
| [LC 207 — Course Schedule](https://leetcode.com/problems/course-schedule/) | LeetCode | siklus |
| [LC 210 — Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | LeetCode | urutan |
| [LC 269 — Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) | LeetCode | model graf |
| [CF 510C — Fox And Names](https://codeforces.com/problemset/problem/510/C) | Codeforces | model + topo |
| [AtCoder DP-G — Longest Path](https://atcoder.jp/contests/dp/tasks/dp_g) | AtCoder | DP di DAG |

---

## Preview

**Day 120** — DP pada DAG: begitu punya urutan topologis, tiga pertanyaan
berbeda (banyak jalur, jalur terpanjang, jalur termurah) diselesaikan dengan
kerangka loop yang **persis sama**, hanya operator penggabungnya yang berubah.
