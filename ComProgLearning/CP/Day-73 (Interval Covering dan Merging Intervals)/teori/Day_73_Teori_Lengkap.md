# 📘 Day 73 — Interval Covering & Merging Intervals

> **Prasyarat:** Day 71 (exchange argument), Day 72 (activity selection),
> Day 38/40 (kompresi koordinat), Day 31 (difference array).

---

## Daftar Isi

1. [Kenapa Hari Ini Urut Menurut `l`, Bukan `r`](#1)
2. [Merging Intervals](#2)
3. [Interval Covering: Greedy Jangkauan Terjauh](#3)
4. [Bukti Covering](#4)
5. [Titik Penusuk Minimum (Dual Activity Selection)](#5)
6. [Bilangan Bulat vs Kontinu](#6)
7. [Varian Turunan: Lubang, Sisip, Irisan, Union](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Kenapa Hari Ini Urut Menurut `l`, Bukan `r`

Day 72 menanamkan satu refleks: *interval → urut menurut ujung `r`*. Hari ini
refleks itu harus dilonggarkan, karena dua pola utama hari ini justru mengurutkan
menurut **awal `l`**.

Alasannya struktural. Bandingkan pertanyaannya:

| Pertanyaan | Yang diproses | Urut menurut |
|---|---|---|
| "Pilih sebanyak mungkin yang saling lepas" | *pilihan* — mau ambil yang mana | `r` |
| "Gabungkan yang beririsan" | *garis waktu* — sapu dari kiri ke kanan | `l` |
| "Tutupi `[S, T]`" | *garis waktu* — dorong batas ke kanan | `l` |
| "Tembak semua interval dengan titik sesedikit mungkin" | *pilihan* | `r` |

Polanya: kalau kamu **menyapu sumbu** dari kiri ke kanan, urutkan menurut `l`.
Kalau kamu **memilih himpunan bagian** dan pertanyaannya "berapa banyak", urutkan
menurut `r`.

> Kriteria pengurutan ditentukan oleh **pertanyaan**, bukan oleh bentuk datanya.

Kesalahan paling umum di blok ini adalah menyalin kode Day 72 dan mengganti
soalnya. Tulis ulang dari nol setiap kali.

---

<a name="2"></a>
## 2. Merging Intervals

> Diberikan `n` interval. Gabungkan semua yang beririsan sehingga tersisa
> daftar interval yang saling terpisah.

Contoh: `[1,3] [2,6] [8,10] [15,18]` → `[1,6] [8,10] [15,18]`.

```cpp
sort(a.begin(), a.end());        // urut l, lalu r

vector<pll> res{a[0]};
for (size_t i = 1; i < a.size(); i++) {
    auto [l, r] = a[i];
    if (l <= res.back().second)
        res.back().second = max(res.back().second, r);   // max, WAJIB
    else
        res.push_back({l, r});
}
```

`O(n log n)`, didominasi pengurutan.

### Kenapa cukup melihat interval terakhir saja

Setelah diurutkan menurut `l`, interval berikutnya punya `l` yang **tidak lebih
kecil** dari semua yang sudah diproses. Jadi kalau ia tidak beririsan dengan blok
terakhir di `res`, ia pasti juga tidak beririsan dengan blok mana pun sebelumnya
— karena blok-blok itu berakhir bahkan lebih awal.

Ini invarian yang membuat algoritmanya `O(n)` setelah pengurutan, bukan `O(n²)`.

### Jebakan `max` yang wajib diingat

```cpp
res.back().second = a[i].second;          // ❌ SALAH
res.back().second = max(res.back().second, a[i].second);   // ✅
```

Contoh yang menghancurkan versi salah: `[1,10]` lalu `[2,3]`. Setelah
pengurutan urutannya memang begitu, dan versi salah akan memendekkan `[1,10]`
menjadi `[1,3]`. Bug ini lolos dari banyak sampel karena butuh interval yang
**termuat penuh** di dalam interval sebelumnya.

### Bersentuhan: digabung atau tidak?

`[1,3]` dan `[3,5]`:

| Model | Syarat | Hasil |
|---|---|---|
| Menutupi garis kontinu | `l <= akhir` | `[1,5]` |
| Rentang setengah terbuka `[l, r)` | `l < akhir` | tetap terpisah |

Seperti Day 72, tentukan sebelum menulis kode.

---

<a name="3"></a>
## 3. Interval Covering: Greedy Jangkauan Terjauh

> Diberikan `n` interval dan target `[S, T]`. Pilih interval **sesedikit mungkin**
> sehingga gabungannya menutupi seluruh `[S, T]`.

Ini pola yang benar-benar baru — bukan varian Day 72.

**Algoritmanya:**

```
sampai = S
selama sampai < T:
    terjauh = sampai
    untuk semua interval dengan l <= sampai:
        terjauh = max(terjauh, r)
    jika terjauh == sampai:  gagal, ada lubang
    sampai = terjauh
    hit++
```

Dengan interval terurut menurut `l`, penunjuk `i` hanya maju sehingga totalnya
`O(n)` setelah pengurutan.

### Menjalankannya dengan tangan

Interval `[0,3] [2,6] [5,9] [8,12]`, target `[0, 12]`:

| `sampai` | Kandidat (`l ≤ sampai`) | `terjauh` | Ambil |
|---|---|---|---|
| 0 | `[0,3]` | 3 | ✅ 1 |
| 3 | `[2,6]` | 6 | ✅ 2 |
| 6 | `[5,9]` | 9 | ✅ 3 |
| 9 | `[8,12]` | 12 | ✅ 4 |

Jawaban: **4**.

Perhatikan bahwa pada langkah pertama hanya `[0,3]` yang memenuhi `l ≤ 0`.
Interval `[2,6]` punya `l = 2 > 0`, sehingga belum boleh dipakai — memakainya
akan menyisakan lubang `(0, 2)`.

### Kesalahan yang sangat umum

```
❌ ambil interval PERTAMA yang l <= sampai
✅ ambil interval dengan r TERBESAR di antara yang l <= sampai
```

Versi salah bisa memakai jauh lebih banyak interval dari yang diperlukan.

### Kapan IMPOSSIBLE

Kalau pada suatu putaran tidak ada interval yang bisa memperluas `sampai`
(`terjauh == sampai`), ada lubang yang tidak bisa ditutup — kembalikan `-1`.
Banyak solusi lupa menangani ini dan mendapat TLE karena loop tak berujung.

---

<a name="4"></a>
## 4. Bukti Covering

**Klaim.** Ada solusi optimal yang, sebagai interval pertama, memakai interval
dengan `r` terbesar di antara semua interval yang memenuhi `l ≤ S`.

**Bukti.** Sebut interval itu `x`. Ambil sembarang solusi optimal `O`.

Solusi `O` harus menutupi titik `S`, jadi ia memuat suatu interval `y` dengan
`l_y ≤ S ≤ r_y`. Menurut definisi `x`, kita punya `r_x ≥ r_y` (keduanya memenuhi
`l ≤ S`, dan `x` yang terjauh).

Ganti `y` dengan `x`, hasilkan `O' = O \ {y} ∪ {x}`.

Apakah `O'` masih menutupi `[S, T]`? Bagian yang tadinya ditutupi oleh `y` adalah
`[max(S, l_y), r_y] = [S, r_y]`. Interval `x` menutupi `[S, r_x] ⊇ [S, r_y]`.
Jadi setiap titik yang ditutupi `y` juga ditutupi `x`. Penutupannya utuh.

Dan `|O'| = |O|`, jadi `O'` juga optimal. ∎

**Langkah induksi.** Setelah memakai `x`, sisa yang harus ditutupi adalah
`[r_x, T]`, sebuah soal covering yang identik strukturnya dan lebih kecil.
Optimal substructure terpenuhi. Induksi menyelesaikan buktinya.

Perhatikan bahwa argumennya **berbeda** dari Day 72: di sana kita menukar untuk
menjaga *jumlah*, di sini kita menukar untuk menjaga *penutupan*. Bentuknya sama
(exchange argument), isinya tidak.

---

<a name="5"></a>
## 5. Titik Penusuk Minimum (Dual Activity Selection)

> Berapa titik minimum sehingga setiap interval memuat setidaknya satu titik?

Ini masalah **dual** dari activity selection, dan jawabannya **persis sama
angkanya**.

```cpp
sort menurut r;
ll titik = LLONG_MIN;
int hit = 0;
for (auto& [l, r] : a)
    if (l > titik) { hit++; titik = r; }   // tembak di ujung KANAN
```

**Kenapa angkanya sama?**

- **Batas bawah:** kalau ada `k` interval yang saling lepas, kamu butuh minimal
  `k` titik (satu titik tidak bisa menusuk dua interval yang lepas).
- **Batas atas:** algoritma di atas memakai tepat sebanyak interval yang
  terpilih dalam activity selection.

Batas bawah = batas atas → optimal. Ini contoh **dualitas LP** yang muncul secara
alami; kamu tidak perlu teorinya, tetapi mengenali polanya sangat membantu.

**Kenapa menembak di `r`, bukan di tengah atau di `l`?** Menembak sejauh mungkin
ke kanan memaksimalkan peluang panah yang sama juga menusuk interval berikutnya.
Ini exchange argument yang sama persis dengan Day 72.

Soal LeetCode 452 (*Minimum Arrows to Burst Balloons*) adalah persis ini.

---

<a name="6"></a>
## 6. Bilangan Bulat vs Kontinu

Perbedaan yang menyebabkan banyak WA halus.

**Kasus kontinu.** `[1, 3]` dan `[4, 6]` menyisakan lubang `(3, 4)` — segmen
garis di antara keduanya tidak tertutupi.

**Kasus bilangan bulat.** Kalau `[1,3]` berarti himpunan `{1,2,3}` dan `[4,6]`
berarti `{4,5,6}`, maka gabungannya `{1..6}` — **tidak ada lubang**.

**Trik penyeragaman:** untuk soal bilangan bulat, ubah setiap `[l, r]` menjadi
`[l, r+1]` lalu pakai seluruh kode kontinu tanpa perubahan.

```
{1,2,3} -> [1, 4)
{4,5,6} -> [4, 7)
[1,4) dan [4,7) bersentuhan di 4 -> digabung menjadi [1,7) = {1..6} ✓
```

Trik yang sama dipakai untuk sapuan event: `{r + 1, -1}` alih-alih `{r, -1}`.

**Cara cepat memutuskan:** kalau soal berbicara tentang "hari", "menit ke-", atau
"posisi ke-", hampir pasti bilangan bulat. Kalau berbicara tentang "panjang",
"waktu", atau "koordinat real", kontinu.

---

<a name="7"></a>
## 7. Varian Turunan

Sekali kamu punya `gabungInterval`, banyak soal turun langsung darinya.

### Total panjang tertutupi

```cpp
ll total = 0;
for (auto& [l, r] : gabungInterval(a)) total += r - l;
```

Soal klasik: total panjang bayangan bangunan, total waktu server sibuk.

### Lubang di dalam `[S, T]`

Sapu blok gabungan, catat celah di antaranya. Lihat `cariLubang` di template.

### Menyisipkan interval baru `O(n)`

Kalau daftarnya sudah terurut dan terpisah, tidak perlu mengurutkan ulang:

```
1. salin semua yang berakhir sebelum interval baru dimulai
2. lebur semua yang beririsan ke dalam interval baru
3. dorong interval baru
4. salin sisanya
```

### Irisan dua daftar interval

Dua penunjuk. Untuk `A[i]` dan `B[j]`, irisannya adalah
`[max(l_A, l_B), min(r_A, r_B)]` — valid kalau `l ≤ r`. Majukan penunjuk yang
`r`-nya lebih kecil.

```cpp
while (i < A.size() && j < B.size()) {
    ll l = max(A[i].first, B[j].first);
    ll r = min(A[i].second, B[j].second);
    if (l <= r) res.push_back({l, r});
    if (A[i].second < B[j].second) i++; else j++;
}
```

### Alternatif: difference array

Kalau koordinatnya kecil (atau setelah kompresi), banyak soal interval bisa
diselesaikan dengan **difference array** (Day 31) alih-alih penggabungan:
`d[l]++`, `d[r]--`, lalu prefix sum. Yang bernilai `> 0` adalah bagian yang
tertutupi.

Kapan memilih mana:

| | Merging | Difference array |
|---|---|---|
| Butuh daftar blok hasil | ✅ | butuh sapuan tambahan |
| Butuh "berapa lapis tumpang tindih" | ❌ | ✅ |
| Koordinat besar | ✅ langsung | perlu kompresi dulu |
| Banyak update, satu query | lambat | ✅ |

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Tabel keputusan

| Pertanyaan | Urut | Teknik | Kompleksitas |
|---|---|---|---|
| Gabungkan yang beririsan | `l` | sapuan + `max` | `O(n log n)` |
| Total panjang tertutupi | `l` | gabung lalu jumlahkan | `O(n log n)` |
| Tutupi `[S,T]` sesedikit mungkin | `l` | jangkauan terjauh | `O(n log n)` |
| Titik penusuk minimum | `r` | tembak di `r` | `O(n log n)` |
| Berapa lapis tumpang tindih | — | difference array / sapuan event | `O(n log n)` |
| Sisipkan ke daftar terurut | — | tiga fase | `O(n)` |

### Jebakan

1. **Lupa `max` saat menggabungkan.** Butuh interval yang termuat penuh untuk
   memunculkan bugnya, sehingga sering lolos sampel.
2. **Covering: mengambil yang pertama muat, bukan yang terjauh.**
3. **Covering: lupa kasus IMPOSSIBLE** → loop tak berujung → TLE.
4. **Mencampur kriteria pengurutan** antara Day 72 dan Day 73.
5. **Bilangan bulat diperlakukan sebagai kontinu.** Pakai trik `r + 1`.
6. **Covering dimulai dari `sampai = 0`** padahal `S` bisa bukan nol.
7. **Penunjuk `i` di-reset di dalam loop luar** → `O(n²)` dan TLE.

### Kompleksitas

| Operasi | Waktu | Memori |
|---|---|---|
| Merge intervals | `O(n log n)` | `O(n)` |
| Interval covering | `O(n log n)` | `O(n)` |
| Titik penusuk | `O(n log n)` | `O(1)` tambahan |
| Insert ke daftar terurut | `O(n)` | `O(n)` |
| Irisan dua daftar | `O(n + m)` | `O(n + m)` |

### Latihan mandiri

- Tulis versi covering yang juga **mencetak interval mana** yang dipakai, lalu
  verifikasi bahwa gabungannya memang menutupi `[S, T]` dengan program pemeriksa
  terpisah. Program pemeriksa yang ditulis independen sering menemukan bug yang
  tidak kamu duga.
- Selesaikan "total panjang tertutupi" dengan **dua cara** (merging dan
  difference array + kompresi), lalu bandingkan hasilnya pada 10.000 masukan
  acak. Kalau berbeda, salah satunya punya bug kasus tepi — biasanya soal
  bilangan bulat vs kontinu.
