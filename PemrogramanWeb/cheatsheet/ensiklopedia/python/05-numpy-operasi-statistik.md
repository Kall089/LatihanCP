# 05 — NumPy: operasi, statistik, matriks

[← 04 Array](04-numpy-array-tipe.md) · [Indeks](README.md) · [Lanjut 06 →](06-pandas-series-dataframe.md)

Setelah array terbentuk, kamu menjumlah, mencari rata-rata, mengubah bentuk, mengkalikan matriks, dan mengganti nilai bersyarat. Hampir semua fungsi di bawah menerima argumen `axis`.

## Daftar isi

- [np.sum](#npsum)
- [np.mean](#npmean)
- [np.std](#npstd)
- [np.var](#npvar)
- [np.min](#npmin)
- [np.max](#npmax)
- [np.argmin](#npargmin)
- [np.argmax](#npargmax)
- [np.median](#npmedian)
- [np.percentile](#nppercentile)
- [np.reshape](#npreshape)
- [transpose / T](#transpose--t)
- [np.matmul](#npmatmul)
- [operator @](#operator-)
- [np.dot](#npdot)
- [np.where](#npwhere)
- [np.clip](#npclip)
- [np.unique](#npunique)
- [np.sort](#npsort)
- [np.argsort](#npargsort)
- [np.concatenate](#npconcatenate)
- [np.stack](#npstack)
- [np.hstack vstack](#nphstack-vstack)
- [np.split](#npsplit)
- [np.cumsum](#npcumsum)
- [np.all dan np.any](#npall-dan-npany)
- [np.abs](#npabs)
- [np.round](#npround)
- [np.nanmean](#npnanmean)
- [operasi elemen](#operasi-elemen)

## np.sum

**Tipe:** fungsi / method ndarray

**Untuk apa:** menjumlah elemen. Tanpa `axis` = semua. Dengan `axis` = lumut di sumbu itu. `keepdims=True` mempertahankan dimensi supaya mudah di-broadcast lagi.

**Contoh implementasi:**

```python
import numpy as np

m = np.array([[10, 20, 30], [40, 50, 60]])
print(np.sum(m))
print(m.sum(axis=0))
print(m.sum(axis=1, keepdims=True))
```

**Yang terjadi:**

- Total semua: `210`.
- Per kolom: `[50 70 90]`.
- Per baris tetap 2d: `[[60] [150]]`.

**Biasanya digabungkan dengan:** `mean` (sum/len), mask bool (`mask.sum()`).

**Jangan:** `sum(array)` bawaan Python pada array besar. Lambat dan bisa aneh di dimensi. Pakai `np.sum`.

## np.mean

**Tipe:** fungsi / method ndarray

**Untuk apa:** rata-rata aritmetika. Ini fungsi yang paling sering kamu pakai di nilai ujian dan eksperimen.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80.0, 70.0, 90.0, 60.0])
print(np.mean(nilai))
m = nilai.reshape(2, 2)
print(m.mean(axis=0))
print(m.mean(axis=1))
```

**Yang terjadi:**

- Rata-rata vektor: `75.0`.
- `m` = `[[80 70] [90 60]]`.
- `axis=0`: rata kolom `[85. 65.]`.
- `axis=1`: rata baris `[75. 75.]`.

**Biasanya digabungkan dengan:** `std` untuk z-score, pandas `groupby.mean`.

**Jangan:** `mean` pada array berisi `NaN` tanpa `nanmean`. Hasilnya `nan` seluruhnya.

## np.std

**Tipe:** fungsi / method ndarray

**Untuk apa:** simpangan baku. Default NumPy memakai populasi (`ddof=0`), yaitu bagi n. Statistik sampel sering `ddof=1` (bagi n−1). Pandas default-nya `ddof=1` — beda ini sering bikin laporan tidak cocok.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80.0, 70.0, 90.0, 60.0])
print(np.std(nilai))
print(np.std(nilai, ddof=1))
print((nilai - nilai.mean()) / nilai.std())
```

**Yang terjadi:**

- `std` populasi ≈ `11.180...`.
- `ddof=1` sedikit lebih besar ≈ `12.909...`.
- Baris terakhir adalah z-score: tiap nilai dikurangi rata-rata lalu dibagi std.

**Biasanya digabungkan dengan:** `mean`, standardisasi fitur, deteksi outlier kasar `|z| > 3`.

**Jangan:** meniru angka Excel/SPSS tanpa cek `ddof`. Tanyakan: populasi atau sampel?

## np.var

**Tipe:** fungsi / method ndarray

**Untuk apa:** varians, kuadrat dari simpangan. `std = sqrt(var)` (dengan `ddof` yang sama).

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80.0, 70.0, 90.0])
print(np.var(nilai))
print(np.var(nilai, ddof=1))
print(np.sqrt(np.var(nilai)))
```

**Yang terjadi:**

- Varians populasi tercetak.
- `ddof=1` lebih besar.
- Akar varians populasi sama dengan `std` default.

**Biasanya digabungkan dengan:** `std`, teori peluang.

**Jangan:** membandingkan `var` dengan `std` seolah satuan sama. Varians satuannya kuadrat.

## np.min

**Tipe:** fungsi / method ndarray

**Untuk apa:** elemen terkecil. Dengan `axis`, minimum per potong.

**Contoh implementasi:**

```python
import numpy as np

m = np.array([[80, 70, 90], [60, 95, 55]])
print(np.min(m))
print(m.min(axis=0))
print(m.min(axis=1))
```

**Yang terjadi:**

- Global: `55`.
- Per kolom: `[60 70 55]`.
- Per baris: `[70 55]`.

**Biasanya digabungkan dengan:** `max` untuk rentang, `clip` batas bawah.

**Jangan:** `min` pada array kosong. `ValueError`.

## np.max

**Tipe:** fungsi / method ndarray

**Untuk apa:** elemen terbesar. Sering dipasangkan `argmax` jika kamu butuh posisinya, bukan nilainya.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 99, 70, 99])
print(np.max(nilai))
print(np.ptp(nilai))
```

**Yang terjadi:**

- Max: `99`.
- `ptp` (peak to peak) = max − min → `29`.

**Biasanya digabungkan dengan:** normalisasi min-max `(x - min) / (max - min)`.

**Jangan:** `max` vs `maximum`. `np.max` mereduksi; `np.maximum(a, b)` membandingkan per elemen dua array.

## np.argmin

**Tipe:** fungsi / method ndarray

**Untuk apa:** **indeks** elemen terkecil, bukan nilainya. Kalau ada seri, yang pertama menang.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 60, 90, 60])
i = np.argmin(nilai)
print(i, nilai[i])
m = np.array([[8, 2], [3, 1]])
print(m.argmin())
print(m.argmin(axis=1))
```

**Yang terjadi:**

- Indeks `1` (60 pertama), nilai `60`. 60 kedua di indeks 3 diabaikan.
- Tanpa axis, `argmin` pada `m` meratakan dulu: indeks `3` (angka 1).
- `axis=1`: per baris → `[1 1]` (kolom kedua masing-masing).

**Biasanya digabungkan dengan:** cari mahasiswa nilai terendah, jarak terdekat.

**Jangan:** memakai indeks `argmin` 1d pada matriks tanpa `unravel_index` jika kamu butuh (baris, kolom).

## np.argmax

**Tipe:** fungsi / method ndarray

**Untuk apa:** indeks elemen terbesar. Klasik untuk “kelas mana yang probabilitasnya paling tinggi” atau nilai ujian tertinggi.

**Contoh implementasi:**

```python
import numpy as np

skor = np.array([0.1, 0.7, 0.2])
print(np.argmax(skor))
m = np.array([[1, 9, 3], [8, 2, 7]])
print(m.argmax(axis=1))
```

**Yang terjadi:**

- Vektor: indeks `1` (0.7).
- Per baris: baris 0 max di kolom 1, baris 1 max di kolom 0 → `[1 0]`.

**Biasanya digabungkan dengan:** `softmax` (di luar bab), ranking, `take_along_axis`.

**Jangan:** mengira `argmax` mengembalikan nilai. Itu `max`. Campur keduanya bikin off-by-one mental.

## np.median

**Tipe:** fungsi NumPy

**Untuk apa:** nilai tengah setelah diurutkan. Tahan outlier dibanding `mean`. Untuk genap, rata-rata dua tengah.

**Contoh implementasi:**

```python
import numpy as np

print(np.median([10, 20, 1000]))
print(np.mean([10, 20, 1000]))
print(np.median([10, 20, 30, 40]))
```

**Yang terjadi:**

- Median `[10,20,1000]` = `20`.
- Mean terpengaruh 1000 → `343.33...`.
- Empat angka: rata-rata 20 dan 30 → `25.0`.

**Biasanya digabungkan dengan:** `percentile`, boxplot, ringkasan kelas yang ada nilai ekstrem.

**Jangan:** `median` pada data ordinal string. Urutan harus numerik.

## np.percentile

**Tipe:** fungsi NumPy

**Untuk apa:** nilai di bawah persentase tertentu. `50` = median. `25` dan `75` = kuartil.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([50, 60, 70, 80, 90])
print(np.percentile(nilai, 50))
print(np.percentile(nilai, [25, 75]))
```

**Yang terjadi:**

- P50 = `70` (median).
- P25 dan P75 tercetak sebagai array dua elemen.

**Biasanya digabungkan dengan:** deteksi outlier IQR, seaborn boxplot.

**Jangan:** `percentile(data, 0.5)` mengira 50%. Argumen `q` dalam skala 0–100, bukan 0–1. `0.5` artinya 0.5%, hampir minimum.

## np.reshape

**Tipe:** fungsi / method (diulang singkat, fokus praktik hitung)

**Untuk apa:** merapikan vektor jadi matriks sebelum `matmul` atau statistik per kelompok yang kamu susun manual.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 70, 90, 60, 85, 75])
per_mhs = nilai.reshape(3, 2)
print(per_mhs)
print(per_mhs.mean(axis=1))
```

**Yang terjadi:**

- 3 mahasiswa × 2 ujian.
- Rata-rata per mahasiswa: baris-wise.

**Biasanya digabungkan dengan:** `mean(axis=…)`, `matmul`.

**Jangan:** `reshape` yang urutan isinya salah. NumPy isi **row-major** default (C-order): kiri ke kanan, baru turun.

## transpose / T

**Tipe:** atribut / fungsi ndarray

**Untuk apa:** menukar sumbu. Matriks 2d: baris jadi kolom. Wajib sebelum beberapa `matmul` agar `(n, k) @ (k, m)` cocok.

**Contoh implementasi:**

```python
import numpy as np

m = np.array([[1, 2, 3], [4, 5, 6]])
print(m.shape, m.T.shape)
print(m.T)
print(np.transpose(m))
```

**Yang terjadi:**

- `(2, 3)` jadi `(3, 2)`.
- `T` =
  ```
  [[1 4]
   [2 5]
   [3 6]]
  ```
- `np.transpose` sama untuk 2d.

**Biasanya digabungkan dengan:** `matmul`, gambar `axes=(2, 0, 1)` (lanjutan).

**Jangan:** `v.T` pada vektor 1d `(3,)`. Shape tetap `(3,)`. Tambah `newaxis` dulu jika butuh kolom.

## np.matmul

**Tipe:** fungsi perkalian matriks

**Untuk apa:** perkalian matriks sungguhan, bukan kali per elemen. Syarat: kolom kiri = baris kanan.

**Contoh implementasi:**

```python
import numpy as np

A = np.array([[1, 2], [3, 4]])
B = np.array([[5, 6], [7, 8]])
print(np.matmul(A, B))
print(A * B)
```

**Yang terjadi:**

- `matmul`:
  ```
  [[19 22]
   [43 50]]
  ```
  karena `1*5+2*7=19`, dst.
- `A * B` adalah **per elemen**: `[[5 12] [21 32]]`. Beda total.

**Biasanya digabungkan dengan:** `.T`, regresi linear sederhana, transformasi.

**Jangan:** menukar `*` dan `matmul`. Ini kesalahan nomor satu di soal matriks.

## operator @

**Tipe:** operator Python (matriks)

**Untuk apa:** gula sintaks untuk `matmul`. Lebih mudah dibaca: `A @ B @ v`.

**Contoh implementasi:**

```python
import numpy as np

A = np.array([[2, 0], [0, 3]])
v = np.array([4, 5])
print(A @ v)
print((A @ v).shape)
```

**Yang terjadi:**

- `A @ v` → `[8 15]` (2×2 kali vektor 2).
- Shape hasil `(2,)`.

**Biasanya digabungkan dengan:** rantai transformasi, rumus `(X.T @ X)`.

**Jangan:** `@` pada list Python. `TypeError`. Harus array (atau objek yang mendukung).

## np.dot

**Tipe:** fungsi NumPy

**Untuk apa:** historis: dot product 1d, matmul 2d, dan perilaku rumit di ndim tinggi. Kode baru lebih jelas memakai `@` / `matmul` untuk matriks dan `np.vdot`/`inner` sesuai kebutuhan.

**Contoh implementasi:**

```python
import numpy as np

u = np.array([1, 2, 3])
v = np.array([4, 5, 6])
print(np.dot(u, v))
print(u @ v)
```

**Yang terjadi:**

- `1*4 + 2*5 + 3*6` = `32`.
- `@` pada 1d juga inner product, hasil sama.

**Biasanya digabungkan dengan:** kemiripan kosinus (dot / (norm×norm)).

**Jangan:** `dot` tiga array berdimensi tinggi tanpa baca docs. Pakai `einsum` atau `matmul` eksplisit.

## np.where

**Tipe:** fungsi NumPy

**Untuk apa:** dua wajah. `where(kondisi, ya, tidak)` mengganti nilai bersyarat (seperti `IF` Excel). `where(kondisi)` saja mengembalikan indeks elemen True.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([60, 80, 55, 90])
huruf = np.where(nilai >= 70, "L", "TL")
print(huruf)
idx = np.where(nilai < 70)
print(idx, nilai[idx])
```

**Yang terjadi:**

- Huruf: `['TL' 'L' 'TL' 'L']`.
- `where` tanpa x/y: tuple indeks `(array([0, 2]),)`.
- `nilai[idx]` → `[60 55]`.

**Biasanya digabungkan dengan:** mask, `clip` (untuk batas numerik murni `clip` lebih pendek).

**Jangan:** `where(nilai >= 70, "L", 0)` mencampur str dan int → array object. Samakan tipe.

## np.clip

**Tipe:** fungsi / method ndarray

**Untuk apa:** memotong nilai di luar rentang `[min, max]`. Nilai di dalam dibiarkan. Enak untuk membatasi probabilitas, RGB, atau nilai ujian 0–100.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([-5, 40, 80, 150])
print(np.clip(nilai, 0, 100))
print(nilai)
```

**Yang terjadi:**

- Hasil: `[0 40 80 100]`.
- `nilai` asli tidak berubah kecuali kamu tulis `nilai = ...` atau `out=`.

**Biasanya digabungkan dengan:** normalisasi, gambar, `where`.

**Jangan:** `clip` min > max. Perilaku membingungkan / error. Cek urutan.

## np.unique

**Tipe:** fungsi NumPy

**Untuk apa:** nilai unik, opsional terurut, plus hitungan. Mirip `set` tapi hasil array dan bisa `return_counts`.

**Contoh implementasi:**

```python
import numpy as np

angkatan = np.array([21, 22, 21, 23, 22, 21])
print(np.unique(angkatan))
u, c = np.unique(angkatan, return_counts=True)
print(u, c)
```

**Yang terjadi:**

- Unik terurut: `[21 22 23]`.
- Counts: `21` muncul 3, `22` dua, `23` satu → `[3 2 1]`.

**Biasanya digabungkan dengan:** histogram kasar, `value_counts` pandas (lebih nyaman untuk tabel).

**Jangan:** `unique` pada float hasil hitungan. `1.0` dan `1.0000000002` dianggap beda.

## np.sort

**Tipe:** fungsi / method

**Untuk apa:** `np.sort` mengembalikan salinan terurut. `a.sort()` mengurutkan di tempat. Default axis terakhir.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([80, 70, 90])
print(np.sort(a))
print(a)
m = np.array([[8, 1, 5], [3, 9, 2]])
print(np.sort(m, axis=1))
```

**Yang terjadi:**

- Salinan `[70 80 90]`, `a` tetap `[80 70 90]`.
- Tiap baris `m` diurut: `[[1 5 8] [2 3 9]]`.

**Biasanya digabungkan dengan:** `percentile` manual, median.

**Jangan:** `a = a.sort()` — `ndarray.sort` mengembalikan `None`.

## np.argsort

**Tipe:** fungsi / method

**Untuk apa:** indeks yang akan mengurutkan array. Pakai itu untuk mengurutkan array lain secara selaras (nama vs nilai).

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 70, 90])
nama = np.array(["Haikal", "Siti", "Budi"])
idx = np.argsort(nilai)
print(idx)
print(nama[idx], nilai[idx])
print(nama[np.argsort(-nilai)])
```

**Yang terjadi:**

- `idx` → `[1 0 2]` (70, 80, 90).
- Nama selaras: Siti, Haikal, Budi.
- `-nilai` untuk descending: Budi, Haikal, Siti.

**Biasanya digabungkan dengan:** ranking, pilih top-k `idx[-3:]`.

**Jangan:** `argsort` lalu mengira hasilnya sudah nilai. Itu indeks.

## np.concatenate

**Tipe:** fungsi NumPy

**Untuk apa:** menempel array di suatu axis. Shape di axis lain harus sama.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6]])
print(np.concatenate([a, b], axis=0))
c = np.array([[7], [8]])
print(np.concatenate([a, c], axis=1))
```

**Yang terjadi:**

- `axis=0`: tambah 1 baris → shape `(3, 2)`.
- `axis=1`: tambah 1 kolom → shape `(2, 3)`.

**Biasanya digabungkan dengan:** batch data, pandas `concat` untuk tabel berlabel.

**Jangan:** `concatenate` vektor `(3,)` dengan matriks `(1, 3)` tanpa samakan `ndim`. `ValueError`.

## np.stack

**Tipe:** fungsi NumPy

**Untuk apa:** menumpuk array **baru** di axis baru. Semua input harus shape sama. Beda dengan `concatenate` yang menempel di axis yang sudah ada.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
print(np.stack([a, b], axis=0), np.stack([a, b], axis=0).shape)
print(np.stack([a, b], axis=1).shape)
```

**Yang terjadi:**

- `axis=0` → shape `(2, 3)` (dua baris).
- `axis=1` → `(3, 2)` (dua kolom).

**Biasanya digabungkan dengan:** kumpulan sample seukuran, channel gambar.

**Jangan:** menukar `stack` dan `concatenate` lalu kaget `ndim` naik 1.

## np.hstack vstack

**Tipe:** fungsi pembungkus concatenate

**Untuk apa:** `vstack` tempel vertikal (baris), `hstack` horizontal (kolom). Lebih mudah diingat untuk 1d/2d.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
print(np.vstack([a, b]))
print(np.hstack([a, b]))
```

**Yang terjadi:**

- `vstack` → matriks 2×3.
- `hstack` → vektor `[1 2 3 4 5 6]`.

**Biasanya digabungkan dengan:** merakit fitur, menambah kolom bias `1`.

**Jangan:** `hstack` dua matriks beda jumlah baris. Samakan dulu.

## np.split

**Tipe:** fungsi NumPy

**Untuk apa:** memotong array jadi beberapa potong. Bisa diberi jumlah bagian sama, atau indeks potong.

**Contoh implementasi:**

```python
import numpy as np

a = np.arange(6)
print(np.split(a, 3))
print(np.split(a, [2, 5]))
```

**Yang terjadi:**

- Bagi 3: `[0 1]`, `[2 3]`, `[4 5]`.
- Indeks 2 dan 5: `[0 1]`, `[2 3 4]`, `[5]`.

**Biasanya digabungkan dengan:** train/test kasar, batch.

**Jangan:** `split(a, 4)` pada 6 elemen. Tidak habis dibagi → error. Pakai `array_split` jika boleh tidak rata.

## np.cumsum

**Tipe:** fungsi / method

**Untuk apa:** jumlah kumulatif. Elemen ke-i adalah jumlah dari awal sampai i. Berguna untuk frekuensi kumulatif dan running total.

**Contoh implementasi:**

```python
import numpy as np

hadir = np.array([1, 1, 0, 1, 1])
print(np.cumsum(hadir))
print(np.cumsum(hadir) / np.arange(1, 6))
```

**Yang terjadi:**

- Kumulatif: `[1 2 2 3 4]`.
- Baris kedua: rasio kehadiran berjalan.

**Biasanya digabungkan dengan:** `cumprod`, grafik running average.

**Jangan:** mengira `cumsum` mereset per kelompok. Untuk itu `pandas.groupby.cumsum`.

## np.all dan np.any

**Tipe:** fungsi / method ndarray

**Untuk apa:** reduksi logika. `all` = semua True, `any` = ada True. Bisa per axis.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([[80, 70], [90, 40]])
print(np.all(nilai >= 70))
print(np.any(nilai < 50))
print(np.all(nilai >= 70, axis=1))
```

**Yang terjadi:**

- Tidak semua ≥ 70 → `False`.
- Ada 40 < 50 → `True`.
- Per baris: baris 0 semua lulus `True`, baris 1 `False`.

**Biasanya digabungkan dengan:** assert data, filter mahasiswa “lulus semua MK”.

**Jangan:** `if nilai >= 70:` pada array. `ValueError: The truth value of an array is ambiguous`. Pakai `all`/`any`.

## np.abs

**Tipe:** fungsi / ufunc

**Untuk apa:** nilai mutlak per elemen. Sama dengan `np.absolute`.

**Contoh implementasi:**

```python
import numpy as np

selisih = np.array([10, -3, -7, 2])
print(np.abs(selisih))
print(np.abs(selisih).mean())
```

**Yang terjadi:**

- `[10 3 7 2]`.
- MAE kasar: rata-rata abs = `5.5`.

**Biasanya digabungkan dengan:** error model, jarak.

**Jangan:** `abs(array)` sebenarnya juga memanggil ufunc, tapi `np.abs` lebih eksplisit di kode data.

## np.round

**Tipe:** fungsi / ufunc

**Untuk apa:** membulatkan per elemen ke `decimals` tertentu. Banker's rounding yang sama dengan Python bisa muncul.

**Contoh implementasi:**

```python
import numpy as np

ipk = np.array([3.755, 2.504, 3.125])
print(np.round(ipk, 2))
```

**Yang terjadi:**

- Dua desimal, kira-kira `[3.76 2.5  3.12]` (nilai tengah `.xx5` ikuti aturan IEEE).

**Biasanya digabungkan dengan:** tampilan laporan, `astype` setelah skala.

**Jangan:** membulatkan di tengah pipeline lalu menghitung ulang rata-rata. Bulatkan di akhir.

## np.nanmean

**Tipe:** fungsi `nan*` 

**Untuk apa:** rata-rata mengabaikan `NaN`. Ada keluarga: `nansum`, `nanstd`, `nanmin`. Wajib saat data bolong.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80.0, np.nan, 90.0])
print(np.mean(nilai))
print(np.nanmean(nilai))
print(np.isnan(nilai))
```

**Yang terjadi:**

- `mean` biasa → `nan`.
- `nanmean` → `85.0` (hanya 80 dan 90).
- `isnan` → `[False True False]`.

**Biasanya digabungkan dengan:** pandas missing data (file 07), `np.nan_to_num`.

**Jangan:** membandingkan `x == np.nan`. Selalu False. Pakai `np.isnan(x)`.

## operasi elemen

**Tipe:** ufunc aritmetika (`+ - * / **`)

**Untuk apa:** hitung per elemen, dengan broadcast. Ini alasan orang pindah dari loop `for`.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 70, 90], dtype=float)
bobot = np.array([0.3, 0.3, 0.4])
print(nilai / 100)
print(nilai * bobot)
print((nilai * bobot).sum())
print(nilai ** 2)
```

**Yang terjadi:**

- Bagi 100: `[0.8 0.7 0.9]`.
- Kali bobot per elemen, lalu `sum` = nilai tertimbang.
- Kuadrat per elemen.

**Biasanya digabungkan dengan:** `clip`, `where`, grafik.

**Jangan:** loop `for i in range(len(nilai)):` untuk kali skalar. Tulis `nilai * 1.05`.

---

Tabel pandas (Series/DataFrame) di [06-pandas-series-dataframe.md](06-pandas-series-dataframe.md).
