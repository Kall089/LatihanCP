# 📅 Day 75 — Huffman Coding & Greedy dengan Heap

> **Bulan 5–6 · Blok Greedy & Ad-hoc (Day 71–82)**
> Sampai kemarin, setiap greedy cukup dengan `sort` sekali. Hari ini pola itu
> patah — dan alasannya bisa diringkas dalam satu pertanyaan.

---

## 🎯 Tujuan Hari Ini

- [ ] Menjawab **"apakah keputusanku menghasilkan kandidat baru?"** sebelum memilih struktur data
- [ ] Menulis Huffman dari nol, dengan **arah heap yang benar**
- [ ] Membuktikan Huffman lewat dua lemma exchange argument
- [ ] Memakai identitas **`Σ f·depth = Σ setiap gabungan`** untuk menghindari membangun pohon
- [ ] Mengenali Huffman yang **disamarkan** (memotong, membelah, menyambung)
- [ ] Menguasai empat pola heap lain di luar Huffman

---

## 🔑 Penyaring Utama: Sort atau Heap?

> **Apakah keputusanmu MENGHASILKAN kandidat baru?**

| | Greedy + `sort` | Greedy + heap |
|---|---|---|
| Himpunan kandidat | tetap | **berubah** |
| Keputusan menciptakan kandidat baru | tidak | **ya** |
| Contoh | activity selection, fractional knapsack | Huffman, penggabungan berkas |

Pada Huffman, menggabungkan dua simpul menciptakan simpul ketiga yang nilainya
**tidak ada di dalam masukan** — jadi mustahil ikut diurutkan di awal.

### Kenapa "urut sekali lalu gabung berurutan" salah

| Masukan | Sekuensial | Huffman |
|---|---|---|
| `{1,1,1,1,100}` | 113 | **112** |
| `{1,1,1,1,1,1}` | 20 | **16** |
| `{5,9,12,13,16,45}` | 234 | **224** |

Contoh kedua paling jelas: sekuensial membangun rantai miring (kedalaman 5),
Huffman membangun pohon seimbang (kedalaman 3). Selisihnya 25%.

---

## 🧠 Inti Materi

### Algoritma

```cpp
priority_queue<ll, vector<ll>, greater<ll>> pq(f.begin(), f.end());  // MIN-heap
ll total = 0;
while (pq.size() > 1) {
    ll x = pq.top(); pq.pop();
    ll y = pq.top(); pq.pop();
    total += x + y;      // biaya penggabungan ini
    pq.push(x + y);      // hasilnya jadi kandidat baru
}
```

⚠️ **`priority_queue` bawaan C++ adalah MAX-heap.** Lupa `greater<ll>` tidak
menghasilkan error apa pun — hanya jawaban salah. Salah satu bug tersulit dilacak.

### Bukti — dua lemma

**Lemma 1 (greedy choice).** Ada pohon optimal yang menempatkan dua frekuensi
terkecil sebagai saudara di kedalaman maksimum.
Tukar nilai terkecil `x` dengan daun terdalam `a`:
`Δ = (f_a − f_x)·(d_x − d_a) ≤ 0` karena `f_a ≥ f_x` dan `d_x ≤ d_a`.

**Lemma 2 (optimal substructure).** Ganti `x, y` bersaudara dengan satu simpul
`x+y`. Maka `biaya(T) = biaya(T') + x + y`, dan suku `x+y` **konstan** — jadi
meminimalkan `T` sama dengan meminimalkan `T'`.

### Identitas yang menghemat pekerjaan

```
Σ f_i · depth_i  =  Σ (setiap nilai gabungan yang pernah dibuat)
```

Kalau soal hanya minta **total biaya**, kamu tidak perlu pohon sama sekali.
Pohon eksplisit baru dibutuhkan untuk **panjang kode per simbol**.

### Varian

| Varian | Perubahan |
|---|---|
| Maksimasi | gabungkan dua **terbesar** (max-heap) |
| K-ary | ambil `K` terkecil; tambah dummy sampai `(n−1) mod (K−1) == 0` |
| Kedalaman terbatas | Huffman **tidak berlaku** — pakai Package-Merge `O(n·L)` |

**Kenapa dummy di awal?** Penggabungan awal berada paling **dalam** di pohon, dan
tempat itu memang untuk nilai terkecil. Min-heap otomatis mengambil dummy (nilai 0)
lebih dulu.

### Empat pola heap lain

| Pola | Bentuk |
|---|---|
| A — `K` operasi ambil ekstrem | pop, olah, push kembali |
| B — gabung `K` daftar terurut | heap `(nilai, daftar, indeks)`, `O(N log K)` |
| C — pelihara `K` terbaik | **`K` terbesar → MIN-heap; `K` terkecil → MAX-heap** |
| D — regret / pembatalan | Day 77 |

Pola C adalah yang paling sering tertukar. Naluri mengatakan sebaliknya.

---

## 📁 Struktur Berkas

```
Day-75 (Huffman Coding dan Greedy dengan Heap)/
├── README.md
├── teori/
│   └── Day_75_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   Menggabungkan Tumpukan Batu  (Easy)   Huffman dasar
│   ├── exercise_2.cpp   Panjang Kode Huffman         (Easy)   bangun pohon
│   ├── exercise_3.cpp   Membelah Papan               (Medium) Huffman terbalik
│   ├── exercise_4.cpp   Kabel Bertingkat             (Medium) K-ary + dummy
│   ├── exercise_5.cpp   Membagi Tugas ke Mesin       (Hard)   heap penjadwal
│   └── exercise_6.cpp   Menyewa K Pekerja            (Hard)   rasio + heap
├── solusi/
│   └── solution_1..6.cpp
├── tugas/
│   └── tugas_01..15.cpp
└── template/
    └── template.cpp
```

---

## ✅ Semua Kode Sudah Diverifikasi

| Yang diuji | Cara | Hasil |
|---|---|---|
| Seluruh 30 berkas | `g++ -std=c++17 -O2 -Wall` | lolos |
| Solusi 1–6 | semua contoh masukan di soal | cocok |
| Solusi 1 (Huffman) | 400 kasus acak vs brute force **seluruh urutan penggabungan** | cocok |
| Solusi 2 (pohon) | 2.000 kasus: `Σ f·panjang` = jawaban Solusi 1 | cocok |
| Solusi 3 (membelah) | 2.000 kasus: keluaran identik dengan Solusi 1 | cocok |
| Solusi 4 (K-ary) | 300 kasus acak vs brute force semua ukuran gabungan | cocok |
| Solusi 5 (mesin) | 3.000 kasus acak vs simulasi referensi | cocok |
| Solusi 6 (pekerja) | 1.500 kasus acak vs seluruh `C(n,K)` | cocok |
| Template | 400 kasus acak vs brute force `O(n!)` | cocok |

Angka yang saya tulis sendiri lalu dikoreksi setelah dihitung ulang: Exercise 4
(`25` → `21`), Exercise 5 (`8` → `9`), Tugas 13 (`29` → `26`), dan satu contoh
tandingan di teori yang ternyata bukan contoh tandingan.

Exercise 6 juga diganti seluruhnya: versi awalnya ("gabungkan dengan batas ukuran
`B`") ternyata setara dengan **bin packing**, yang NP-hard — tidak layak sebagai
latihan greedy. Penggantinya menggabungkan rasio Day 74 dengan heap Day 75.

---

## ⚠️ Jebakan

1. **`priority_queue` default = MAX-heap.** Huffman butuh min-heap.
2. **`K` terkecil → MAX-heap**, `K` terbesar → MIN-heap. Sering tertukar.
3. **Lupa `long long`** — `n = 2·10^5` dengan `f = 10^9` → `~10^14`.
4. **Kasus `n = 1`** — biaya `0`, panjang kode `1`. Baca soal.
5. **Telusuri pohon secara rekursif** → stack overflow pada frekuensi Fibonacci.
6. **K-ary tanpa dummy** → pohon tidak penuh → tidak optimal.
7. **Menyangka kode Huffman unik** — banyak pohon optimal.
8. **Membuktikan aturan yang sudah diberikan soal** (Exercise 5) — buang waktu.

---

## 🔗 Prasyarat & Kelanjutan

**Dipakai hari ini:** exchange argument (Day 71), priority queue (Day 24),
perbandingan rasio (Day 74), heap dalam sapuan (Day 73 Exercise 6).

**Tugas yang butuh materi lain:** Tugas 08 (dua heap + lazy deletion) dan
Tugas 11 (dua struktur bekerja sama) adalah pemanasan langsung untuk Day 77.

**Berikutnya:**

- Day 76 — Greedy dengan Sorting Multi-Kriteria
- Day 77 — Greedy + Priority Queue (teknik regret/pembatalan)
- Day 78 — Scheduling dengan Deadline & Penalti

---

## 📝 Checklist Penguasaan

- [ ] Refleks bertanya "apakah keputusanku menghasilkan kandidat baru?"
- [ ] Bisa menulis Huffman dari nol dalam kurang dari 60 detik, arah heap benar
- [ ] Bisa menyebutkan kedua lemma buktinya
- [ ] Hafal identitas `Σ f·depth = Σ gabungan`
- [ ] Bisa menurunkan syarat dummy `(n−1) mod (K−1) == 0` sendiri
- [ ] Tidak pernah tertukar antara "K terkecil → max-heap" dan sebaliknya
- [ ] Bisa mengenali "memotong / membelah / menyambung" sebagai Huffman
