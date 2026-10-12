# Daftar Materi Competitive Programming

111 deck, tersusun dalam 16 folder mengikuti urutan belajar. Setiap deck memakai
struktur yang sama:

1. **Sampul** dan **Agenda**
2. **Sebelum Mulai** — empat slide pembuka: penjelasan sederhana lewat analogi,
   materi ini tentang apa, kapan dipakai dan kapan tidak, serta posisinya di
   antara materi lain
3. **Teori** — definisi, gagasan inti, dan alasan kenapa algoritmanya benar
4. **Simulasi** — tiga langkah bergambar dengan angka yang bisa diperiksa sendiri
5. **Kode** — implementasi lengkap dengan anotasi per baris penting
6. **Jebakan** — empat kesalahan yang paling sering terjadi
7. **Contoh soal** — pernyataan, pembahasan, dan kode lengkap
8. **Latihan mandiri** — lima soal dengan tingkat kesulitannya
9. **Ringkasan** — empat hal yang perlu terbawa

Semua kode memakai C++ dengan `cin`/`cout`.

---

## 01 — Dasar

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 015 | Analisis Kompleksitas | Big-O, membaca batasan soal, memilih algoritma sebelum mengetik |

## 02 — STL

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 018 | Kontainer STL & Comparator | vector, pair, tuple, cara menulis comparator yang benar |
| 021 | set, map & priority_queue | Kontainer terurut, kapan pakai yang mana |
| 025 | Algoritma STL Penting | sort, lower_bound, unique, next_permutation |
| 026 | Optimasi Bitset | 64 nilai boolean per instruksi, subset sum satu baris |

## 03 — Teknik Array

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 029 | Prefix Sum & Difference Array | Query rentang O(1), update rentang O(1) |
| 032 | Two Pointers & Sliding Window | Dua penunjuk yang hanya maju, O(n²) menjadi O(n) |
| 035 | Kadane & Maximum Subarray | DP satu dimensi pertama yang perlu dikuasai |
| 036 | Monotonic Stack | Elemen lebih besar berikutnya, dalam O(n) |
| 037 | Monotonic Deque | Maksimum pada jendela geser |
| 038 | Kompresi Koordinat | Nilai raksasa menjadi indeks array |

## 04 — Sorting & Searching

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 044 | Merge Sort, Inversi & D&C | Pecah, taklukkan, gabungkan — plus menghitung inversi |
| 048 | Binary Search & on Answer | Mencari jawaban, bukan hanya mencari nilai |
| 050 | Ternary Search & Unimodal | Puncak atau lembah pada fungsi yang tidak monoton |
| 052 | Soal Interaktif | Flush, anggaran pertanyaan, binary search interaktif |
| 054 | Meet in the Middle | Membelah 2^n menjadi dua kali 2^(n/2) |

## 05 — Rekursi

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 057 | Rekursi (Fondasi DP) | Kasus dasar, pemanggilan, dan cara menalarnya |
| 060 | Enumerasi Subset & Bitmask | Operasi bit dan menelusuri seluruh himpunan bagian |
| 062 | Backtracking | Mencoba, mundur, dan memangkas cabang |
| 066 | Memoization | Jembatan dari rekursi ke dynamic programming |
| 067 | Dari Memoisasi ke DP Bottom-Up | Tabel yang sama, urutan pengisian yang berbeda |

## 06 — Greedy

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 071 | Greedy & Kapan Harus DP | Kapan mengambil yang terbaik saat ini benar |
| 072 | Interval & Exchange Argument | Cara membuktikan sebuah greedy benar |
| 075 | Algoritma Konstruktif | Membuat jawaban yang sah, bukan yang optimal |

## 07 — Teori Bilangan & Aljabar

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 088 | Sieve, Faktorisasi & GCD | Prima, faktor, dan algoritma Euclid |
| 090 | Aritmetika Modular & nCr | Invers modulo, kombinasi, teorema Fermat kecil |
| 092 | Extended Euclid, Invers & CRT | gcd beserta koefisiennya; invers untuk modulus apa pun |
| 095 | Miller-Rabin & Pollard Rho | Uji keprimaan dan faktorisasi sampai 10^18 |
| 099 | Catalan, Stirling & Burnside | Tiga alat pencacahan yang paling sering muncul |
| 103 | Inklusi-Eksklusi | Tambah tunggal, kurangi pasangan, tambah bertiga |
| 105 | Fungsi Mobius & Inversi | Menukar syarat gcd menjadi syarat kelipatan |
| 108 | Matrix Exponentiation | Rekurens linear untuk n sampai 10^18 |
| 111 | Basis Linear XOR | 2^n himpunan bagian menjadi 60 bilangan |
| 246 | FFT & Perkalian Polinomial | Konvolusi O(n²) menjadi O(n log n) |

## 08 — Graf

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 113 | Graf, DFS & BFS | Representasi graf dan dua penelusuran dasarnya |
| 117 | Flood Fill & Komponen | Mewarnai daerah, menghitung komponen |
| 118 | Deteksi Siklus & Bipartit | Mencari siklus, mewarnai dua warna |
| 119 | Topological Sort & DP DAG | Urutan prasyarat, dan DP di atasnya |
| 121 | Lintasan & Sirkuit Euler | Melewati setiap sisi tepat sekali |
| 124 | BFS pada Ruang State | Ketika simpulnya adalah keadaan, bukan tempat |
| 127 | Dijkstra | Jarak terpendek pada bobot tak negatif |
| 129 | Bellman-Ford | Bobot negatif dan deteksi siklus negatif |
| 131 | Floyd-Warshall | Jarak semua pasangan dalam O(n³) |
| 134 | Disjoint Set Union | Union by size dan path compression |
| 136 | Minimum Spanning Tree | Kruskal dan Prim |
| 225 | Strongly Connected Component | Tarjan dan Kosaraju, kondensasi graf |
| 227 | Bridge & Articulation Point | Titik lemah jaringan lewat low-link |
| 229 | 2-SAT | Soal logika menjadi soal graf |
| 231 | Aliran Maksimum & Min Cut | Dinic, sisi balik, teorema max-flow min-cut |
| 233 | Pencocokan Bipartit | Jalur penambah, Kuhn, teorema Konig |
| 234 | Aliran Biaya Minimum & Penugasan | MCMF dengan SPFA, dan Hungarian O(n^3) |

## 09 — Dynamic Programming

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 141 | Prinsip Dynamic Programming | Submasalah, keadaan, transisi |
| 142 | Top-Down, Bottom-Up & State | Dua gaya penulisan, satu cara berpikir |
| 143 | DP Linear 1D | Bentuk DP paling dasar |
| 144 | Coin Change & Unbounded Knapsack | Barang boleh diambil berkali-kali |
| 145 | 0-1 Knapsack & Rekonstruksi | Ambil atau tidak, plus menelusuri jawabannya |
| 146 | Subset Sum & Partition | Bisa atau tidak, dan membagi dua sama besar |
| 147 | Bounded Knapsack | Dekomposisi biner untuk batas jumlah |
| 148 | Longest Increasing Subsequence | O(n log n) dengan binary search |
| 149 | LCS & Edit Distance | DP dua dimensi pada dua string |
| 150 | DP pada Grid | Jalur, halangan, dan arah gerak |
| 151 | Range DP | Menggabungkan selang, dari kecil ke besar |
| 152 | Rekonstruksi Jalur DP | Mengeluarkan jawabannya, bukan hanya nilainya |
| 153 | Optimasi Memori DP | Dua baris, satu baris, atau bahkan satu variabel |
| 154 | REVIEW DP Dasar | Rangkuman dan latihan terpadu |
| 155 | Desain State Lanjut | Memilih keadaan yang tepat |
| 156 | DP Bitmask (TSP) | Keadaan berupa himpunan bagian |
| 157 | DP Bitmask (Assignment) | Penugasan optimal dengan bitmask |
| 158 | Sum over Subsets (SOS DP) | Menjumlahkan seluruh himpunan bagian, O(n 2^n) |
| 159 | Digit DP | Menghitung bilangan dengan syarat pada digitnya |
| 160 | DP pada Pohon | Menggabungkan jawaban dari anak ke ayah |
| 161 | Knapsack pada Pohon | Kapasitas dibagi antar subtree |
| 162 | Rerooting Technique | Jawaban untuk setiap simpul sebagai akar |
| 163 | DP Probabilitas & Ekspektasi | Linearitas ekspektasi dan keadaan pecahan |
| 164 | DP dengan Bitset | Optimasi konstan untuk keadaan boolean |
| 165 | Game DP & DAG State | Posisi menang dan kalah |
| 166 | Broken Profile DP | Menutup grid dengan potongan |
| 167 | Latihan Terpadu DP | Soal gabungan tingkat menengah |
| 168 | REVIEW DP Menengah | Rangkuman seluruh materi DP |
| 244 | Convex Hull Trick & Li Chao | Suku DP berbentuk garis, minimumnya soal geometri |
| 248 | Optimasi DP: D&C & Knuth | Memangkas jangkauan titik pecah, O(n^3) jadi O(n^2) |

## 10 — Struktur Data

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 169 | Sparse Table | Query minimum O(1) pada data tetap |
| 170 | Fenwick Tree (BIT) | Prefix sum dengan update, kode terpendek |
| 172 | Segment Tree | Query dan update rentang yang serba bisa |
| 176 | Lazy Propagation | Update rentang dalam O(log n) |
| 179 | Segment Tree Persisten | Menyimpan seluruh versi, log n simpul per perubahan |
| 183 | Sqrt Decomposition & Mo | Blok akar n, dan pengurutan query |
| 185 | Treap & Implicit Treap | Seimbang tanpa aturan perputaran; array yang bisa dipotong |
| 187 | DSU Rollback & Konektivitas Dinamis | Penghapusan sisi diubah menjadi pembatalan |
| 189 | Parallel Binary Search | Ribuan binary search berbagi satu sapuan waktu |

## 11 — Pohon

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 193 | Small to Large & DSU on Tree | Query subtree untuk setiap simpul, O(n log n) |
| 198 | Diameter Pohon | Dua DFS, atau satu DP |
| 199 | Euler Tour & Query Subtree | Meratakan pohon menjadi array |
| 201 | Binary Lifting & LCA | Leluhur bersama terdekat dalam O(log n) |
| 204 | Heavy-Light Decomposition | Query jalur menjadi query rentang |
| 206 | Centroid Decomposition | Membelah pohon pada titik seimbangnya |

## 12 — String

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 211 | String Hashing | Membandingkan potongan dalam O(1) |
| 213 | KMP & Prefix Function | Pencarian pola dalam O(n + m) |
| 215 | Z-Function & Manacher | Awalan dan palindrom, keduanya linear |
| 217 | Trie & Binary Trie | Pohon awalan, dan XOR terbesar |
| 219 | Suffix Array & LCP | Semua sufiks diurutkan, Kasai untuk LCP |
| 221 | Aho-Corasick | Banyak pola sekaligus, satu kali telusur |
| 223 | Suffix Automaton | Mesin terkecil yang mengenali seluruh substring |

## 13 — Geometri

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 240 | Geometri Dasar & Convex Hull | Hasil kali silang, orientasi, monotone chain |
| 242 | Sweep Line & Titik Terdekat | Garis yang bergerak, bidang menjadi barisan |

## 14 — Teori Permainan

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 236 | Teori Permainan & Sprague-Grundy | Nim, bilangan grundy, permainan gabungan |

## 16 — Teknik Kontes

Dua deck yang tidak berisi algoritma, melainkan cara kerja. Keduanya bisa dibaca
kapan saja, tidak harus setelah materi lain.

| Day | Materi | Isi singkat |
|-----|--------|-------------|
| 250 | Stress Testing & Bug Sendiri | Uji banding, memperkecil kasus, memeriksa sifat jawaban |
| 252 | Randomisasi dalam Kompetisi | Anti-hash, mengacak urutan, menghitung peluang gagal |

---

## 15 — Latihan Soal

Tiga deck kumpulan soal, bukan materi baru. Isinya 146 soal bertingkat dari
AtCoder Educational DP Contest, CSES, Codeforces, dan arsip Gemastik, masing-masing
dipetakan ke deck materi yang relevan.

| Berkas | Isi | Jumlah soal |
|--------|-----|-------------|
| Latihan-01 | Kumpulan Soal DP — EDPC A sampai Z, CSES DP, Codeforces | 50 |
| Latihan-02 | Kumpulan Soal Graf — CSES Graph Algorithms, Codeforces | 50 |
| Latihan-03 | Kumpulan Soal Greedy — CSES Sorting & Searching, Codeforces | 46 |

Setiap deck berisi: cara memakai daftarnya, cara mengenali jenis soal dari
pernyataannya, tiga tingkat kesulitan, soal Gemastik yang sudah diperiksa isinya,
kesalahan yang sering terjadi, dan rencana latihan enam minggu.

Soal Gemastik diambil dari arsip resmi TLX (`tlx.toki.id/problems`). Untuk
Gemastik 14 (2021) pernyataan soalnya terbuka untuk umum, jadi jenis soalnya
sudah dipastikan. Untuk tahun 2022 ke atas pernyataannya perlu dibuka sendiri
lewat akun TLX.

## Saran urutan belajar

**Tahap 1 — fondasi (Day 015 sampai 072).** Folder 01 sampai 06.
Tanpa ini, materi berikutnya akan terasa seperti hafalan.

**Tahap 2 — alat kerja (Day 088 sampai 136).** Folder 07 dan 08 bagian awal
(sampai MST). Sebagian besar soal kontes tingkat menengah selesai dengan
materi sampai titik ini.

**Tahap 3 — dynamic programming (Day 141 sampai 168).** Folder 09.
Bagian terbesar dan paling menentukan untuk naik tingkat.

**Tahap 4 — struktur data & pohon (Day 169 sampai 206).** Folder 10 dan 11.

**Tahap 5 — string, graf lanjut, geometri (Day 211 ke atas).** Folder 12, 13, 14
dan sisa folder 08. Ambil sesuai kebutuhan, tidak harus berurutan.

**Kapan saja — folder 16.** Day 250 dan 252 tidak butuh prasyarat berat.
Semakin awal dipakai, semakin banyak waktu kontes yang dihemat, karena keduanya
tentang cara kerja: menemukan bug sendiri dan memakai keacakan dengan benar.

**Sepanjang semua tahap — folder 15.** Kumpulan soalnya dipakai berbarengan,
bukan setelah semua materi selesai. Tiap baris di sana menyebut deck materinya,
jadi bisa langsung dikerjakan begitu deck yang bersangkutan sudah dibaca.

## Catatan

- Materi bertanda Day tinggi (225 ke atas) bukan berarti harus dipelajari
  paling akhir. Nomor hanya menandai urutan penyusunan, bukan tingkat kesulitan.
- Setiap deck bisa dibaca berdiri sendiri, karena slide "Posisi Materi Ini"
  selalu menyebut prasyarat dan lanjutannya.
- Angka pada setiap simulasi sudah diperiksa ulang secara terpisah, jadi bisa
  dipakai untuk menguji pemahaman sendiri.
