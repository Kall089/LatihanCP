# 📘 Day 77 — Greedy + Priority Queue: Teknik Regret

> **Prasyarat:** Day 71 (exchange argument), Day 24 (priority queue),
> Day 75 (greedy dengan heap), Day 72 (activity selection).

---

## Daftar Isi

1. [Ide Inti: Ambil Dulu, Sesali Kemudian](#1)
2. [Kenapa Regret Selalu Aman](#2)
3. [Pola 1 — Deadline + Durasi](#3)
4. [Pola 2 — Deadline + Keuntungan](#4)
5. [Pola 3 — Menunda Keputusan (Isi Ulang)](#5)
6. [Pola 4 — Dua Struktur Bekerja Sama](#6)
7. [Cara Mengenali Soal Regret](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Ide Inti: Ambil Dulu, Sesali Kemudian

Sampai Day 76, setiap greedy membuat keputusan **final**: ambil atau lewati, lalu
lanjut. Hari ini keputusannya bisa **dibatalkan**.

> **Ambil dulu semua yang terlihat menguntungkan. Kalau batasannya terlanggar,
> batalkan pilihan TERBURUK yang sudah diambil.**

Kenapa ini lebih kuat daripada "menolak sejak awal"? Karena saat kamu bertemu
sebuah kandidat, kamu **belum tahu** apa yang akan datang. Menolak sekarang
membuang informasi. Menerima lalu membatalkan nanti menunda keputusan sampai kamu
punya informasi yang cukup.

### Perbedaan dengan Day 75

| | Day 75 | Day 77 |
|---|---|---|
| Isi heap | kandidat yang **belum** dipilih | pilihan yang **sudah** diambil |
| Operasi | ambil yang terbaik | **buang** yang terburuk |
| Contoh | Huffman | jadwal deadline |

Keduanya memakai `priority_queue`, tetapi peranannya berlawanan. Membedakan
keduanya adalah setengah dari penguasaan hari ini.

---

<a name="2"></a>
## 2. Kenapa Regret Selalu Aman

Ini argumen **dominasi keadaan** — bentuk exchange argument yang sedikit berbeda
dari hari-hari sebelumnya.

Misalkan kita memproses kandidat dalam urutan tertentu, dan setelah memproses `i`
kandidat pertama kita punya himpunan terpilih `S_i`.

**Klaim.** Untuk setiap `i`, himpunan `S_i` yang dihasilkan algoritma regret
punya dua sifat sekaligus:

1. `|S_i|` **maksimum** di antara semua himpunan bagian layak dari `i` kandidat pertama
2. di antara semua yang berukuran maksimum, `S_i` punya **total sumber daya terpakai minimum**

Sifat kedua itulah yang membuat induksi berjalan. Keadaan dengan sumber daya
terpakai lebih kecil **mendominasi** — apa pun yang bisa dilakukan dari keadaan
lain, bisa juga dilakukan dari keadaan ini.

**Langkah induksi.** Saat kandidat ke-`(i+1)` datang:

- Kalau ditambahkan tanpa melanggar → `|S|` bertambah 1, dan itu jelas maksimum.
- Kalau melanggar → kita membuang anggota terburuk. Ukurannya kembali seperti
  semula, tetapi sumber daya terpakai **tidak lebih besar** dari sebelumnya
  (karena kita membuang yang paling boros di antara `S ∪ {baru}`).

Jadi kedua sifat terjaga. ∎

**Kunci pembuktiannya:** urutan pemrosesan harus membuat batasan makin **ketat**
(misalnya deadline menaik). Kalau tidak, membuang anggota lama bisa merusak
kelayakan sesuatu yang sudah diputuskan — dan buktinya batal.

---

<a name="3"></a>
## 3. Pola 1 — Deadline + Durasi

> `n` kursus. Kursus `i` butuh `t_i` waktu dan harus **selesai** sebelum `d_i`.
> Hanya satu kursus dikerjakan pada satu waktu. Maksimalkan jumlah kursus.

```cpp
sort(k.begin(), k.end());            // deadline MENAIK
priority_queue<ll> pq;               // MAX-heap durasi terpilih
ll total = 0;
for (auto& [d, t] : k) {
    pq.push(t);
    total += t;
    if (total > d) {                 // deadline terlanggar
        total -= pq.top();           // batalkan yang TERLAMA
        pq.pop();
    }
}
jawaban = pq.size();
```

### Kenapa deadline menaik

Saat memproses kursus dengan deadline `d`, seluruh kursus terpilih punya deadline
`≤ d`. Kalau `total ≤ d` maka **seluruh** jadwal itu layak — karena setiap kursus
selesai lebih awal dari `total`, dan deadline-nya sudah diperiksa saat ia masuk.

Urutan lain merusak sifat ini.

### Kenapa membuang yang terlama

Membuang kursus terlama mengurangi `total` **sebanyak-banyaknya** dengan biaya
hanya satu kursus. Itu persis sifat "sumber daya terpakai minimum" dari Bagian 2.

Perhatikan: kursus yang dibuang bisa saja kursus yang **baru saja ditambahkan** —
dan itu benar. Kalau kursus baru adalah yang terlama, menolaknya memang pilihan
terbaik.

### Contoh

`{(5,2), (6,2), (7,1), (9,3), (100,100)}` — pasangan `(deadline, durasi)`:

| Kursus | `total` setelah push | Melanggar? | Aksi | `|S|` |
|---|---|---|---|---|
| `(5,2)` | 2 | tidak | — | 1 |
| `(6,2)` | 4 | tidak | — | 2 |
| `(7,1)` | 5 | tidak | — | 3 |
| `(9,3)` | 8 | tidak | — | 4 |
| `(100,100)` | 108 | **ya** (>100) | buang durasi 100 | 4 |

Jawaban: **4**.

---

<a name="4"></a>
## 4. Pola 2 — Deadline + Keuntungan

> `n` pekerjaan, masing-masing butuh **tepat 1** satuan waktu, punya deadline
> `d_i` dan keuntungan `p_i`. Maksimalkan total keuntungan.

```cpp
sort(j.begin(), j.end());                            // deadline MENAIK
priority_queue<ll, vector<ll>, greater<ll>> pq;      // MIN-heap keuntungan
ll total = 0;
for (auto& [d, p] : j) {
    pq.push(p);
    total += p;
    if ((ll)pq.size() > d) {         // slot waktu tidak cukup
        total -= pq.top();           // batalkan keuntungan TERKECIL
        pq.pop();
    }
}
```

### Perhatikan perbedaannya dari Pola 1

| | Pola 1 | Pola 2 |
|---|---|---|
| Batasan | `total durasi ≤ d` | `jumlah pekerjaan ≤ d` |
| Yang dibatalkan | durasi **terbesar** | keuntungan **terkecil** |
| Arah heap | **MAX** | **MIN** |

Keduanya "membatalkan yang terburuk" — tetapi *terburuk* berarti hal yang berbeda.
Pada Pola 1 kita ingin membebaskan **waktu**; pada Pola 2 setiap pekerjaan memakan
slot yang sama, jadi yang penting adalah **nilainya**.

Salah arah heap tidak menghasilkan error apa pun — hanya jawaban salah.

### Kenapa `pq.size() > d` benar

Karena deadline diurutkan menaik, kalau kita punya `k` pekerjaan terpilih semuanya
berdeadline `≤ d`, kita bisa menjadwalkannya pada slot `1, 2, ..., k`. Layak
selama `k ≤ d` untuk setiap prefiks — dan pemeriksaan di setiap langkah menjamin itu
(teorema Hall untuk kasus interval).

---

<a name="5"></a>
## 5. Pola 3 — Menunda Keputusan (Isi Ulang)

> Perjalanan sejauh `D`. Ada `n` pom bensin di posisi `p_i` berisi `b_i` liter.
> Tangki awal `awal` liter, 1 liter per satuan jarak. Cari pemberhentian minimum.

Naluri: "isi kalau bahan bakar tipis". Itu memaksa keputusan sebelum informasinya
lengkap.

**Idenya terbalik:** jangan pernah isi saat melewati pom. Simpan saja sebagai
**kupon**. Saat bahan bakar benar-benar habis, baru pakai kupon **terbesar** yang
sudah terlewat.

```cpp
priority_queue<ll> pq;               // MAX-heap kupon
ll bahan = awal, posisi = 0;
while (posisi < D) {
    while (i < n && pom[i].pos <= posisi + bahan) pq.push(pom[i++].liter);
    posisi += bahan;  bahan = 0;
    if (posisi >= D) break;
    if (pq.empty()) return -1;       // macet
    bahan = pq.top(); pq.pop();      // pakai kupon TERBESAR
    hit++;
}
```

Ini regret dalam bentuk paling murni: kita **menunda** setiap keputusan sampai ia
tidak bisa ditunda lagi, lalu mengambil yang terbaik dari seluruh pilihan yang
sudah tersedia — termasuk pilihan yang "seharusnya" diambil jauh di belakang.

**Kenapa boleh mengambil kupon dari pom yang sudah terlewat?** Karena secara
matematis tidak ada bedanya kapan bahan bakar itu ditambahkan — yang penting hanya
apakah kita bisa mencapai pom itu. Menunda keputusan tidak mengubah kelayakan,
tetapi memberi informasi lebih banyak.

---

<a name="6"></a>
## 6. Pola 4 — Dua Struktur Bekerja Sama

> Modal awal `C`, boleh menjalankan `K` proyek. Proyek `i` butuh modal `m_i` dan
> memberi keuntungan `p_i` yang langsung menambah modal.

```cpp
sort(proyek.begin(), proyek.end());          // menurut modal MENAIK
priority_queue<ll> pq;                       // MAX-heap keuntungan terjangkau
size_t i = 0;
for (int t = 0; t < K; t++) {
    while (i < n && proyek[i].modal <= C) pq.push(proyek[i++].untung);
    if (pq.empty()) break;
    C += pq.top(); pq.pop();
}
```

Dua struktur dengan peran berbeda:

- **array terurut** — antrean proyek yang **belum terjangkau**, menunggu modal naik
- **heap** — proyek yang **sudah terjangkau**, siap dipilih

Setiap kali modal naik, penunjuk `i` maju dan memindahkan proyek dari array ke
heap. Karena modal hanya membesar, penunjuk **tidak pernah mundur** — total
`O(n log n)`.

Pola "penunjuk monoton memindahkan elemen dari struktur A ke struktur B" muncul
sangat sering. Kenali bentuknya.

---

<a name="7"></a>
## 7. Cara Mengenali Soal Regret

Tiga tanda yang muncul bersamaan:

1. **Keputusan diproses berurutan** menurut sesuatu (waktu, posisi, deadline)
2. **Ada batasan yang bisa terlanggar** (kapasitas, waktu, uang, slot)
3. **Membatalkan satu pilihan mengembalikan sumber daya** dalam jumlah terhitung

Kalau ketiganya ada, coba regret sebelum mencoba DP.

### Kalimat pemicu di soal

- "maksimalkan jumlah ... yang bisa diselesaikan sebelum tenggat"
- "kamu boleh membatalkan / mengganti pilihan"
- "berapa kali minimal kamu harus berhenti / mengisi ulang"
- "pilih paling banyak K, tetapi syaratnya berubah seiring waktu"

### Kapan regret **tidak** berlaku

Kalau membatalkan sebuah pilihan **tidak** mengembalikan sumber daya secara bersih
— misalnya pilihan itu sudah mengubah keadaan lain secara permanen — regret
runtuh. Contoh: soal di mana urutan pengerjaan memengaruhi biaya pekerjaan
berikutnya. Di situ biasanya DP.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Tabel empat pola

| Pola | Urut menurut | Isi heap | Arah | Yang dibuang |
|---|---|---|---|---|
| Deadline + durasi | deadline ↑ | durasi terpilih | **MAX** | durasi terbesar |
| Deadline + untung | deadline ↑ | untung terpilih | **MIN** | untung terkecil |
| Isi ulang | posisi ↑ | kupon terlewat | **MAX** | — (mengambil) |
| Modal bertumbuh | modal ↑ | untung terjangkau | **MAX** | — (mengambil) |

Dua pola pertama **membuang**, dua pola terakhir **mengambil**. Semuanya memakai
prinsip yang sama: menunda keputusan sampai informasinya lengkap.

### Jebakan

1. **Arah heap salah.** Bandingkan Pola 1 dan Pola 2 — "terburuk" berarti hal yang
   berbeda.
2. **Urutan pemrosesan salah.** Regret hanya benar kalau batasannya makin ketat.
3. **Menolak sejak awal** alih-alih mengambil lalu membatalkan.
4. **Lupa mengurangi akumulator** saat membatalkan.
5. **Mengisi bahan bakar saat melewati pom** — menunda lebih baik.
6. **Lupa `long long`** pada akumulator.
7. **Menyangka elemen yang baru masuk tidak boleh dibuang.** Boleh — dan sering
   memang itu yang terbaik.

### Kompleksitas

Keempat pola: `O(n log n)`, didominasi pengurutan dan operasi heap.

### Latihan mandiri

- Ambil Pola 1, lalu ubah heap-nya menjadi min-heap. Jalankan stress test dan
  catat berapa persen kasus yang gagal. Lakukan hal yang sama untuk Pola 2 dengan
  max-heap. Dua eksperimen ini menanamkan perbedaannya lebih kuat daripada
  menghafal.
- Tulis versi Pola 1 yang juga **mencetak kursus mana** yang diambil. Petunjuk:
  simpan indeks di dalam heap, dan ingat bahwa yang dibuang bisa jadi elemen yang
  baru saja masuk.
