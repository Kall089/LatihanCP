# 📘 Day 75 — Huffman Coding & Greedy dengan Heap

> **Prasyarat:** Day 71 (exchange argument), Day 24 (priority queue),
> Day 43–47 (komparator), Day 73 Exercise 6 (heap dalam sapuan).

---

## Daftar Isi

1. [Kapan Sort Tidak Cukup](#1)
2. [Masalah Huffman](#2)
3. [Bukti Huffman](#3)
4. [Dua Rumus yang Sama](#4)
5. [Membangun Pohon & Panjang Kode](#5)
6. [Varian: K-ary, Maksimum, Kedalaman Terbatas](#6)
7. [Pola Heap Lain di Luar Huffman](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Kapan Sort Tidak Cukup

Sampai Day 74, setiap greedy yang kamu tulis punya bentuk yang sama:

```
urutkan sekali menurut suatu kriteria
sapu dari kiri ke kanan
```

Bentuk itu bekerja karena **urutan keputusannya sudah tetap sejak awal**.
Mengambil sebuah barang tidak mengubah barang lain.

Hari ini pola itu patah.

> **Tanda pengenal terkuat: keputusanmu MENGHASILKAN kandidat baru.**

Pada Huffman, menggabungkan dua simpul menciptakan simpul ketiga yang harus ikut
bersaing lagi. Nilai simpul baru itu tidak ada di dalam masukan, jadi tidak
mungkin ikut diurutkan di awal.

| | Greedy + sort | Greedy + heap |
|---|---|---|
| Himpunan kandidat | tetap | berubah |
| Keputusan menciptakan kandidat baru | tidak | **ya** |
| Struktur | `sort` sekali | `priority_queue` |
| Contoh | activity selection, fractional knapsack | Huffman, penggabungan file |

**Kesalahan umum:** menyangka "urutkan sekali, lalu gabungkan berurutan dari kiri"
setara dengan Huffman. Strategi itu selalu menggabungkan hasil sebelumnya dengan
elemen berikutnya, tanpa pernah membiarkan hasil gabungan **bersaing kembali**.

| Masukan | Sekuensial | Huffman |
|---|---|---|
| `{1, 1, 1, 1, 100}` | 113 | **112** |
| `{1, 1, 1, 1, 1, 1}` | 20 | **16** |
| `{5, 9, 12, 13, 16, 45}` | 234 | **224** |

Contoh kedua paling jelas: dengan enam nilai identik, strategi sekuensial
membangun rantai miring (kedalaman 5), sedangkan Huffman membangun pohon
seimbang (kedalaman 3). Selisihnya 25%.

Inti perbedaannya: hasil penggabungan **harus** kembali masuk ke dalam himpunan
kandidat dan bersaing dengan elemen asli. Struktur yang bisa melakukan itu
dengan cepat adalah heap, bukan array terurut.

---

<a name="2"></a>
## 2. Masalah Huffman

> Diberikan `n` simbol dengan frekuensi `f_1, ..., f_n`. Berikan setiap simbol
> sebuah kode biner sehingga **tidak ada kode yang menjadi awalan kode lain**
> (*prefix-free*). Minimalkan `Σ f_i · panjang_i`.

Syarat prefix-free itu setara dengan: setiap simbol menempati **daun** dari
sebuah pohon biner, dan panjang kodenya adalah kedalaman daun itu.

Jadi soalnya menjadi: **bangun pohon biner yang meminimalkan `Σ f_i · depth_i`.**

### Algoritmanya

```cpp
priority_queue<ll, vector<ll>, greater<ll>> pq(f.begin(), f.end());
ll total = 0;
while (pq.size() > 1) {
    ll x = pq.top(); pq.pop();
    ll y = pq.top(); pq.pop();
    total += x + y;          // biaya penggabungan ini
    pq.push(x + y);          // hasilnya jadi kandidat baru
}
```

`O(n log n)`.

### Menjalankannya dengan tangan

Frekuensi `{5, 9, 12, 13, 16, 45}`:

| Langkah | Ambil dua terkecil | Gabungan | Antrean sesudahnya | Total |
|---|---|---|---|---|
| 1 | 5, 9 | 14 | 12, 13, 14, 16, 45 | 14 |
| 2 | 12, 13 | 25 | 14, 16, 25, 45 | 39 |
| 3 | 14, 16 | 30 | 25, 30, 45 | 69 |
| 4 | 25, 30 | 55 | 45, 55 | 124 |
| 5 | 45, 55 | 100 | 100 | **224** |

Panjang kode yang dihasilkan: `4 4 3 3 3 1`. Periksa:
`5·4 + 9·4 + 12·3 + 13·3 + 16·3 + 45·1 = 20+36+36+39+48+45 = 224`. ✓

Perhatikan bahwa simbol paling sering (45) mendapat kode terpendek (1 bit) — itu
memang tujuan seluruh algoritma.

---

<a name="3"></a>
## 3. Bukti Huffman

Buktinya dua bagian, keduanya exchange argument.

### Lemma 1 — dua frekuensi terkecil bersaudara

**Klaim.** Ada pohon optimal yang menempatkan dua simbol berfrekuensi terkecil
sebagai **saudara pada kedalaman maksimum**.

**Bukti.** Sebut `x` dan `y` dua simbol berfrekuensi terkecil. Ambil pohon
optimal `T`.

Pada pohon optimal, daun terdalam pasti punya saudara (kalau tidak, simpul
induknya bisa dihapus dan seluruh subpohon dinaikkan satu tingkat — biayanya
turun, kontradiksi). Sebut dua daun bersaudara terdalam itu `a` dan `b`.

Tukar `x` dengan `a`. Perubahan biayanya:

```
Δ = (f_x·d_a + f_a·d_x) − (f_x·d_x + f_a·d_a)
  = (f_a − f_x)·(d_x − d_a)
```

Karena `x` berfrekuensi minimum, `f_a ≥ f_x`. Karena `a` berada di kedalaman
maksimum, `d_x ≤ d_a`, jadi `d_x − d_a ≤ 0`. Maka `Δ ≤ 0` — biayanya **tidak
naik**.

Ulangi untuk `y` dan `b`. Hasilnya pohon optimal dengan `x` dan `y` bersaudara di
kedalaman maksimum. ∎

### Lemma 2 — optimal substructure

**Klaim.** Kalau `x` dan `y` bersaudara, ganti keduanya dengan satu simbol `z`
berfrekuensi `f_x + f_y`. Pohon optimal untuk masalah `(n−1)` simbol yang baru,
setelah `z` dipecah kembali menjadi `x` dan `y`, adalah pohon optimal untuk
masalah asli.

**Bukti.** Misalkan `T` pohon untuk masalah asli dengan `x, y` bersaudara pada
kedalaman `d`, dan `T'` pohon yang sama dengan `x, y` diganti `z` pada
kedalaman `d−1`. Hubungan biayanya:

```
biaya(T) = biaya(T') + f_x + f_y
```

Sukunya `f_x + f_y` **konstan** — tidak bergantung pada bentuk pohon. Jadi
meminimalkan `biaya(T)` sama persis dengan meminimalkan `biaya(T')`. ∎

Kedua lemma itu memberi greedy choice property + optimal substructure — dua bahan
Day 71. Induksi menyelesaikan buktinya.

**Verifikasi empiris.** Template hari ini menjalankan brute force atas **semua**
urutan penggabungan (`O(n!)`, `n ≤ 7`) pada 400 kasus acak dan mencocokkannya
dengan greedy. Semuanya cocok.

---

<a name="4"></a>
## 4. Dua Rumus yang Sama

Ini identitas yang menghemat banyak pekerjaan:

```
Σ f_i · depth_i   =   Σ (setiap nilai gabungan yang pernah dibuat)
```

**Kenapa sama?** Sebuah daun berkedalaman `d` berarti frekuensinya ikut terhitung
dalam `d` penggabungan yang berbeda (setiap kali subpohon yang memuatnya
digabungkan naik satu tingkat). Jadi `f_i` muncul tepat `depth_i` kali dalam
jumlah seluruh gabungan.

**Akibatnya:** kalau soal hanya meminta **total biaya**, kamu tidak perlu
membangun pohonnya sama sekali. Cukup jumlahkan `x + y` di setiap langkah. Itulah
kenapa `huffmanBiaya` di template hanya delapan baris.

Kamu baru butuh pohon eksplisit kalau soal meminta **panjang kode per simbol**
atau **kodenya sendiri**.

---

<a name="5"></a>
## 5. Membangun Pohon & Panjang Kode

Kalau kamu butuh panjang kode:

1. Alokasikan `2n − 1` simpul (pohon biner penuh dengan `n` daun punya tepat
   `2n − 1` simpul).
2. Heap menyimpan `(nilai, indeks_simpul)`.
3. Setiap penggabungan membuat simpul internal baru dengan dua anak.
4. Telusuri dari akar, catat kedalaman tiap daun.

**Telusuri secara iteratif**, bukan rekursif. Pohon Huffman bisa berkedalaman
`O(n)` pada kasus terburuk (frekuensi Fibonacci: `1, 1, 2, 3, 5, 8, ...`
menghasilkan pohon yang sangat miring), sehingga rekursi dengan `n = 2·10^5`
berisiko stack overflow.

**Kode yang tidak unik.** Ada banyak pohon optimal (menukar anak kiri/kanan tidak
mengubah biaya). Karena itu soal yang meminta "cetak kodenya" biasanya menerima
jawaban mana pun yang panjangnya benar, atau menetapkan aturan tie-break
tambahan. Baca soal dengan teliti.

**Kasus `n = 1`.** Tidak ada penggabungan. Biayanya `0`, tetapi panjang kodenya
harus `1` (kamu tetap butuh satu bit untuk mengirim simbol itu). Soal berbeda
mendefinisikannya berbeda — periksa contoh masukannya.

---

<a name="6"></a>
## 6. Varian

### K-ary Huffman

Setiap penggabungan menyatukan `K` nilai, bukan 2. Berguna untuk pengkodean
berbasis alfabet berukuran `K`.

**Syarat penting:** agar pohonnya penuh, jumlah daun harus memenuhi
`(n − 1) mod (K − 1) == 0`. Kalau tidak, tambahkan simpul **dummy bernilai 0**
sampai syaratnya terpenuhi.

Kenapa dummy ditambahkan di **awal**, bukan di akhir? Karena dummy bernilai 0
akan terambil paling awal oleh min-heap, sehingga ia "mengisi" penggabungan
pertama yang tidak penuh. Kalau kamu membiarkan penggabungan **terakhir** yang
tidak penuh, biayanya lebih besar — nilai-nilai besar terpaksa berada lebih
dalam.

### Memaksimalkan, bukan meminimalkan

Kalau soal meminta biaya **maksimum**, gabungkan dua nilai **terbesar** (max-heap).
Buktinya cerminan langsung: tanda pertidaksamaan pada Lemma 1 berbalik.

### Kedalaman terbatas (Length-Limited Huffman)

Kalau ada batasan `depth_i ≤ L`, Huffman biasa **tidak berlaku**. Solusinya
algoritma Package-Merge, `O(n·L)`. Jarang muncul di kontes tingkat menengah,
tetapi kenali namanya agar kamu tidak menghabiskan waktu memaksa greedy.

### Batas bawah kedalaman

Kedalaman maksimum pohon Huffman dibatasi oleh barisan Fibonacci: untuk mencapai
kedalaman `d`, kamu butuh total frekuensi minimal `Fib(d+2)`. Karena `Fib(87)`
sudah melebihi `10^18`, kedalaman tidak akan pernah melebihi sekitar 87 pada
batasan `long long`. Fakta ini berguna untuk mengalokasikan array kedalaman.

---

<a name="7"></a>
## 7. Pola Heap Lain di Luar Huffman

Huffman hanyalah kasus paling terkenal. Kenali polanya secara umum.

### Pola A — "lakukan `K` operasi, tiap kali ambil ekstrem"

```cpp
priority_queue<ll> pq(a.begin(), a.end());
for (int i = 0; i < K; i++) {
    ll x = pq.top(); pq.pop();
    skor += x;
    pq.push(ubah(x));            // elemen kembali dalam bentuk baru
}
```

Contoh: "makan permen paling banyak, tetapi jumlahnya berkurang setengah setiap
kali"; "kurangi tumpukan terbesar `K` kali".

### Pola B — gabungkan `K` daftar terurut

Heap berisi satu elemen dari tiap daftar. `O(N log K)`.

### Pola C — pelihara `K` elemen terbaik sejauh ini

Min-heap berukuran `K`. Untuk tiap elemen baru: kalau lebih besar dari puncak,
buang puncak dan masukkan yang baru. `O(n log K)` dan memori `O(K)` — jauh lebih
baik daripada mengurutkan seluruhnya kalau `K` kecil.

### Pola D — heap sebagai "regret" (Day 77)

Ambil semua yang terlihat bagus, lalu **batalkan** pilihan terburuk saat melanggar
batasan. Dibahas penuh di Day 77; hari ini cukup tahu bahwa heap adalah alatnya.

### Cara memilih heap yang benar

```cpp
priority_queue<ll> maxHeap;                                  // terbesar di atas
priority_queue<ll, vector<ll>, greater<ll>> minHeap;         // terkecil di atas
```

**Default C++ adalah MAX-heap.** Huffman butuh **MIN-heap**. Lupa `greater<ll>`
menghasilkan jawaban yang salah tanpa crash dan tanpa peringatan kompiler —
salah satu bug tersulit dilacak di seluruh materi ini.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Pengenalan pola

```
Soal greedy
├── himpunan kandidat TETAP        -> sort sekali
└── keputusan MENCIPTAKAN kandidat -> heap
    ├── gabungkan dua terkecil     -> Huffman (minimasi)
    ├── gabungkan dua terbesar     -> Huffman terbalik (maksimasi)
    ├── gabungkan K sekaligus      -> K-ary + dummy
    ├── ambil ekstrem K kali       -> heap sederhana
    └── batalkan pilihan terburuk  -> regret (Day 77)
```

### Jebakan

1. **`priority_queue` default adalah MAX-heap.** Huffman butuh min-heap.
2. **Lupa `long long`.** `n = 2·10^5` dengan `f = 10^9` → total `~10^14`.
3. **Kasus `n = 1`.** Biaya `0`, panjang kode `1`. Baca soal.
4. **"Urutkan lalu gabungkan berpasangan"** ≠ Huffman.
5. **Telusuri pohon secara rekursif** → stack overflow pada frekuensi Fibonacci.
6. **K-ary tanpa dummy** → pohon tidak penuh → biaya tidak optimal.
7. **Menyangka kode Huffman unik.** Banyak pohon optimal; hanya panjangnya yang
   tertentu (dan itu pun tidak selalu unik).

### Kompleksitas

| Operasi | Waktu | Memori |
|---|---|---|
| Huffman biaya | `O(n log n)` | `O(n)` |
| Huffman + pohon | `O(n log n)` | `O(n)` |
| K-ary Huffman | `O(n log n)` | `O(n)` |
| Gabung `K` daftar | `O(N log K)` | `O(K)` |
| `K` terbaik | `O(n log K)` | `O(K)` |

### Latihan mandiri

- Cari frekuensi yang menghasilkan pohon Huffman **sedalam mungkin** untuk
  `n = 10`. (Petunjuk: Fibonacci.) Lalu periksa berapa kedalamannya, dan
  bandingkan dengan `log₂ n` — selisihnya akan mengejutkanmu, dan menjelaskan
  kenapa telusuri iteratif itu penting.
- Implementasikan Huffman dua kali: sekali dengan `priority_queue`, sekali dengan
  **dua antrean biasa** (satu berisi frekuensi asli yang sudah diurutkan, satu
  berisi hasil gabungan). Yang kedua berjalan `O(n log n)` untuk pengurutan lalu
  `O(n)` untuk sisanya, dan tidak butuh heap sama sekali. Buktikan bahwa antrean
  kedua selalu terurut menaik secara otomatis — itu pengamatan yang bagus.
