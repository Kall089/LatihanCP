# Day 143 — Teori Lengkap: DP Linear 1D

---

## 1. Kenapa Empat Soal Ini Digabung

Climbing stairs, house robber, frog jump, dan Kadane biasanya diajarkan
terpisah, seolah-olah masing-masing punya triknya sendiri. Padahal keempatnya
adalah **satu bentuk yang sama**:

```
dp[i] = <gabungan> atas beberapa dp[j] dengan j < i
```

Yang berbeda hanya tiga hal:

| | apa yang dihitung | operator gabung | dari mana saja |
|---|---|---|---|
| tangga | banyak cara | `+` | `i-1`, `i-2` |
| house robber | nilai maksimum | `max` | `i-1` (lewati), `i-2` (ambil) |
| frog jump | biaya minimum | `min` | `i-1` .. `i-k` |
| Kadane | jumlah maksimum | `max` | `i-1` saja (atau mulai ulang) |

Kalau kamu bisa menurunkan salah satunya dari nol, kamu bisa menurunkan
semuanya. Metodenya ada di bagian 2.

---

## 2. Metode Menurunkan Rekurens 1D

Ini bagian terpenting dokumen ini. Jangan menghafal rumus; hafalkan
**prosedurnya**.

### Langkah 1 — Tulis definisi `dp[i]` sebagai KALIMAT LENGKAP

Bukan "dp[i] adalah jawabannya". Tulis persis apa yang dihitung, dan
perhatikan perbedaan halus berikut yang menjadi sumber bug nomor satu:

- **"sampai i"** — `dp[i]` = jawaban terbaik dengan mempertimbangkan
  `a[0..i]`, dan elemen `i` **boleh dipakai atau tidak**.
- **"berakhir tepat di i"** — `dp[i]` = jawaban terbaik dari solusi yang
  **wajib** memakai elemen `i` sebagai elemen terakhirnya.

Konsekuensinya berbeda:

| definisi | jawaban akhir |
|---|---|
| "sampai i" | `dp[n-1]` |
| "berakhir tepat di i" | `max(dp[0..n-1])` |

House robber memakai yang pertama. Kadane (dan LIS di Day 148) memakai yang
kedua. Mencampurnya adalah cara tercepat mendapat jawaban yang salah pada
kasus uji besar tapi benar pada kasus kecil.

### Langkah 2 — Tanyakan: apa KEPUTUSAN TERAKHIR?

Untuk sampai ke keadaan `i`, apa langkah terakhir yang mungkin? Daftarkan
semuanya. Untuk tangga: langkah terakhir 1 anak tangga, atau 2 anak tangga.
Untuk house robber: rumah ke-`i` dirampok, atau tidak.

### Langkah 3 — Gabungkan

- Menghitung **banyaknya** cara → jumlahkan (`+`).
- Mencari yang **terbaik** → `max` atau `min`.

Pastikan pilihan-pilihannya **saling lepas** (tidak tumpang tindih) dan
**mencakup semua kemungkinan**. Kalau tumpang tindih, hitungan cara jadi
ganda.

### Langkah 4 — Base case, lalu uji `n = 1` dan `n = 2` DENGAN TANGAN

Hampir semua bug DP 1D ada di sini, bukan di rekurensnya.

---

## 3. Climbing Stairs

**Soal.** Ada `n` anak tangga. Sekali melangkah boleh naik 1 atau 2 anak
tangga. Ada berapa cara mencapai anak tangga ke-`n`?

**Definisi.** `dp[i]` = banyak cara mencapai anak tangga ke-`i`.

**Keputusan terakhir.** Langkah terakhir dari `i-1` (naik 1) atau dari `i-2`
(naik 2). Kedua himpunan cara itu saling lepas — dibedakan oleh langkah
terakhirnya.

```
dp[i] = dp[i-1] + dp[i-2]
dp[0] = 1        (satu cara: tidak melangkah sama sekali)
dp[1] = 1
```

Itu Fibonacci. Tapi turunkanlah, jangan kenali.

**Kenapa `dp[0] = 1`, bukan 0?** Karena "berdiri di titik awal" adalah satu
cara yang sah, yaitu barisan langkah kosong. Kalau kamu memakai `dp[0] = 0`,
seluruh hasil menjadi nol. Cara mengeceknya: hitung `dp[2]` dengan tangan
(harus 2: `1+1` dan `2`) dan pastikan rumusmu mengeluarkan 2.

### 3.1 Varian: Langkah 1..k

```cpp
dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-k]
```

Naif `O(nk)`. Untuk `k` besar, pakai **prefix sum bergulir**: karena
`dp[i] = S(i-1) - S(i-k-1)` dengan `S` prefix sum dari `dp`, ini jadi `O(n)`.
(CSES 1633 "Dice Combinations" memakai `k = 6`, jadi naif sudah cukup.)

### 3.2 Varian: Ada Anak Tangga Rusak

Kalau `i` rusak, `dp[i] = 0`. Selesai. **Jangan** menuliskannya sebagai
`continue` yang melewati penugasan — nilai lama di array bisa tersisa.

### 3.3 Varian: Biaya Minimum (LC 746)

Ganti operator: `dp[i] = min(dp[i-1], dp[i-2]) + cost[i]`. Perhatikan bahwa
biaya dibayar saat **menginjak**, jadi `cost[i]` ditambahkan di luar `min`.

---

## 4. House Robber

**Soal.** Deret rumah dengan nilai `a[0..n-1]`. Tidak boleh merampok dua rumah
yang **bersebelahan**. Maksimalkan total.

**Definisi.** `dp[i]` = total maksimum dengan mempertimbangkan rumah `0..i`
("sampai i").

**Keputusan terakhir.** Rumah `i` dirampok atau tidak.

- Tidak dirampok → hasilnya sama seperti sampai `i-1`: `dp[i-1]`.
- Dirampok → `i-1` haram, jadi kita menyambung dari `i-2`: `dp[i-2] + a[i]`.

```
dp[i]  = max(dp[i-1], dp[i-2] + a[i])
dp[0]  = a[0]
dp[1]  = max(a[0], a[1])
jawaban = dp[n-1]
```

**Kesalahan klasik: greedy "ambil selang-seling".** Untuk `[2, 1, 1, 2]`,
greedy indeks genap memberi `2 + 1 = 3`, indeks ganjil memberi `1 + 2 = 3`,
tapi jawaban benarnya `a[0] + a[3] = 4`. DP menemukannya; greedy tidak.

**Rolling variable:**

```cpp
ll prev2 = 0, prev1 = 0;
for (ll x : a) {
    ll cur = max(prev1, prev2 + x);
    prev2 = prev1;
    prev1 = cur;
}
// jawaban = prev1
```

Perhatikan bahwa dengan inisialisasi `0, 0` kita tidak perlu menangani `n = 1`
atau `n = 2` secara khusus — base case-nya sudah termuat. Ini bukan
kebetulan; `dp[-1] = dp[-2] = 0` memang definisi yang konsisten.

**Urutan penugasan mutlak.** `prev2 = prev1;` harus mendahului
`prev1 = cur;`. Terbalik, keduanya rusak dan hasilnya salah tanpa peringatan.

### 4.1 Varian Melingkar (LC 213)

Rumah `0` dan `n-1` sekarang bertetangga. Godaan pertama adalah menambal
rekurens dengan `if`. Itu hampir selalu salah.

Cara yang benar dan pendek: **jalankan versi linear dua kali.**

- (a) pada `a[0 .. n-2]` — memaksa rumah terakhir tidak dirampok
- (b) pada `a[1 .. n-1]` — memaksa rumah pertama tidak dirampok

Jawabannya `max(a, b)`.

**Kenapa ini mencakup semua kasus?** Rumah pertama dan terakhir tidak mungkin
dirampok bersamaan. Jadi setiap solusi yang sah pasti melewatkan minimal satu
di antara keduanya, dan karena itu tercakup oleh (a) atau (b). Sebaliknya,
setiap solusi dari (a) dan (b) pasti sah.

**Kasus `n = 1` harus ditangani terpisah** — kalau tidak, `a[0..n-2]` adalah
rentang kosong.

---

## 5. Frog Jump

**Soal (AtCoder DP-A/B).** Ada `n` batu dengan ketinggian `h[0..n-1]`. Katak
mulai di batu 0 dan ingin sampai di batu `n-1`. Dari batu `i` ia boleh
melompat ke `i+1` .. `i+k`, dengan biaya `|h[i] - h[j]|`. Cari total biaya
minimum.

**Definisi.** `dp[i]` = biaya minimum untuk sampai di batu `i`.

```
dp[i] = min over j = 1..k of  dp[i-j] + |h[i] - h[i-j]|      (untuk i-j >= 0)
dp[0] = 0
```

`O(nk)`. Untuk `k = 2` (DP-A) atau `k <= 100` (DP-B) itu cukup.

**Kenapa greedy gagal di sini.** Melompat ke batu dengan ketinggian paling
mirip terlihat masuk akal, tetapi lompatan yang mahal sekarang bisa membuka
posisi yang jauh lebih murah nanti. Contoh `h = [10, 30, 40, 20]` dengan
`k = 2`: greedy dari 0 memilih batu 1 (selisih 20), lalu ke 3 (selisih 10),
total 30. DP menemukan `0 → 2 → 3` dengan biaya `30 + 20 = 50`... yang lebih
buruk. Coba `h = [10, 30, 40, 50, 20]` sendiri; intinya, biaya lokal terkecil
bukan jaminan.

**Untuk `k` besar (sampai `10^5`).** `O(nk)` tidak cukup. Kalau biayanya bukan
`|h[i]-h[j]|` melainkan sesuatu yang bisa dipisah (misalnya `dp[j] + c`),
gunakan **monotonic deque** (Day 37) untuk mengambil minimum jendela geser
dalam `O(1)` amortisasi, sehingga totalnya `O(n)`. Untuk biaya absolut yang
bergantung pada `i` **dan** `j` sekaligus, dekomposisinya lebih rumit dan
biasanya soal tidak memintanya.

---

## 6. Kadane — dan Kenapa Ia Sebenarnya DP

Kebanyakan orang menghafal Kadane sebagai trik tiga baris. Mari turunkan.

**Soal.** Cari subarray **tidak kosong** yang jumlahnya maksimum.

**Percobaan pertama (dan gagal):** `dp[i]` = jumlah subarray maksimum di
`a[0..i]`. Rekurensnya buntu — kita tidak tahu apakah subarray terbaik sampai
`i-1` bisa **disambung** dengan `a[i]` atau tidak.

**Definisi yang benar:** `dp[i]` = jumlah maksimum dari subarray yang
**berakhir tepat di `i`**.

Sekarang keputusan terakhirnya jelas: subarray yang berakhir di `i` entah

- hanya berisi `a[i]` saja, atau
- merupakan perpanjangan dari subarray yang berakhir di `i-1`.

```
dp[i]   = max(a[i], dp[i-1] + a[i])
jawaban = max atas SELURUH dp[i]
```

Karena `dp[i]` hanya butuh `dp[i-1]`, kita cukup satu variabel:

```cpp
ll cur = a[0], best = a[0];
for (int i = 1; i < n; i++) {
    cur = max(a[i], cur + a[i]);
    best = max(best, cur);
}
```

**Ini persis Kadane.** Bukan trik; itu DP 1D dengan definisi "berakhir tepat
di i" dan memori yang digulung.

### 6.1 Jebakan `best = 0`

Kalau semua elemen negatif — misalnya `[-5, -2, -9]` — jawaban yang benar
adalah `-2` (subarray tidak boleh kosong). Menginisialisasi `best = 0`
memberi `0`, yang salah.

Inisialisasi yang aman: `best = a[0]` dan `cur = a[0]`, lalu mulai loop dari
`i = 1`. **Kecuali** kalau soal memang mengizinkan subarray kosong — beberapa
soal begitu. **Baca soalnya.**

### 6.2 Rekonstruksi Indeks

```cpp
ll cur = a[0], best = a[0];
int s = 0, bs = 0, be = 0;
for (int i = 1; i < n; i++) {
    if (a[i] > cur + a[i]) { cur = a[i]; s = i; }   // MULAI ULANG di i
    else                     cur = cur + a[i];
    if (cur > best) { best = cur; bs = s; be = i; }
}
```

Kuncinya: `s` diperbarui **hanya saat mulai ulang**, dan `bs/be` dicatat
**hanya saat rekor baru**. Menggabungkan keduanya jadi satu `if` adalah bug
yang umum.

### 6.3 Varian Melingkar (LC 918)

Subarray boleh melingkar dari akhir ke awal. Dua kemungkinan:

- Tidak melingkar → Kadane biasa.
- Melingkar → yang **dibuang** adalah subarray di tengah, jadi jawabannya
  `total - (subarray minimum)`.

```
jawaban = max(kadaneMax, total - kadaneMin)
```

**Kasus khusus:** kalau semua elemen negatif, `total - kadaneMin` menjadi `0`
(karena subarray minimumnya adalah seluruh array), yang berarti "subarray
kosong" — tidak sah. Deteksi dengan `if (kadaneMax < 0) jawaban = kadaneMax;`.

### 6.4 Varian Produk (LC 152)

Untuk **hasil kali** maksimum, satu variabel tidak cukup: mengalikan dengan
angka negatif membalik peran maksimum dan minimum. Simpan **dua**:

```cpp
ll mx = a[0], mn = a[0], best = a[0];
for (int i = 1; i < n; i++) {
    ll x = a[i];
    ll nmx = max({x, mx * x, mn * x});
    ll nmn = min({x, mx * x, mn * x});
    mx = nmx; mn = nmn;                 // hitung dulu, tugaskan kemudian
    best = max(best, mx);
}
```

Menugaskan `mx` sebelum menghitung `nmn` adalah bug klasik — `nmn` lalu
memakai `mx` yang sudah berubah.

---

## 7. Rolling Variable — Memangkas Memori

Kalau `dp[i]` hanya butuh sejumlah **tetap** nilai sebelumnya, array
`O(n)`-nya tidak perlu:

```cpp
// dp[i] = max(dp[i-1], dp[i-2] + x)
ll a = 0, b = 0;
for (ll x : arr) { ll c = max(b, a + x); a = b; b = c; }
```

Kapan **tidak boleh** digulung: kalau kamu perlu **merekonstruksi** jawabannya
(butuh seluruh array `dp` atau array pilihan terpisah), atau kalau rekurensnya
melihat mundur sejauh `k` yang tidak tetap.

Untuk frog jump dengan lompatan sampai `k`, kamu bisa menyimpan hanya `k`
nilai terakhir — memori `O(k)`, bukan `O(n)`.

---

## 8. Kesalahan yang Paling Sering Terjadi

1. **Definisi `dp[i]` tidak ditulis sebagai kalimat lengkap.** Semua bug lain
   berakar di sini.
2. **"Berakhir tepat di i" vs "sampai i" tertukar**, lalu jawaban akhir
   diambil dari tempat yang salah.
3. **Kadane dengan `best = 0`** pada array yang seluruhnya negatif.
4. **House robber melingkar ditambal dengan `if`** alih-alih dijalankan dua
   kali.
5. **Base case `n = 1`, `n = 2` tidak diuji dengan tangan.**
6. **Urutan penugasan rolling variable terbalik.**
7. **Lupa modulo** pada soal menghitung banyak cara.
8. **`int` untuk akumulasi** — `2·10^5 · 10^9 = 2·10^14`.
9. **Frog jump `O(nk)` pada `k` besar** → TLE.
10. **Rekonstruksi Kadane dengan `s` dan `bs` diperbarui di `if` yang sama.**

---

## 9. Ringkasan

- Semua DP 1D lahir dari pertanyaan yang sama: **apa keputusan terakhirnya?**
- Tulis definisi `dp[i]` sebagai kalimat lengkap. Bedakan "sampai i" dari
  "berakhir tepat di i" — itu menentukan di mana jawabanmu berada.
- Tangga = `+`; house robber = `max` dengan larangan tetangga; frog jump =
  `min` atas jendela `k`; Kadane = `max` dengan opsi mulai ulang.
- Kadane bukan trik: ia DP "berakhir tepat di i" dengan memori digulung.
- Varian melingkar diselesaikan dengan **dua kali jalan linear**, bukan
  tambalan.
- Rolling variable memangkas memori jadi `O(1)` — perhatikan urutan
  penugasannya.
