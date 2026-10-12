# 04 — NumPy: array, dtype, shape, indexing, broadcast

[← 03 File](03-file-pathlib-json-csv.md) · [Indeks](README.md) · [Lanjut 05 →](05-numpy-operasi-statistik.md)

NumPy menyimpan banyak angka dalam **satu blok memori** bernama `ndarray`. Semua elemen bertipe sama (`dtype`). Itu sebabnya hitungan vektor jauh lebih cepat daripada loop Python murni. Install: `python -m pip install numpy`.

Konvensi: `import numpy as np`.

## Daftar isi

- [np.array](#nparray)
- [ndarray](#ndarray)
- [dtype](#dtype)
- [int32](#int32)
- [int64](#int64)
- [float32](#float32)
- [float64](#float64)
- [bool dtype](#bool-dtype)
- [dtype object](#dtype-object)
- [shape](#shape)
- [ndim](#ndim)
- [size](#size)
- [itemsize dan nbytes](#itemsize-dan-nbytes)
- [axis](#axis)
- [indexing](#indexing-ndarray)
- [slicing](#slicing-ndarray)
- [fancy indexing](#fancy-indexing)
- [boolean mask](#boolean-mask)
- [broadcast](#broadcast)
- [np.newaxis](#npnewaxis)
- [np.zeros](#npzeros)
- [np.ones](#npones)
- [np.full](#npfull)
- [np.arange](#nparange)
- [np.linspace](#nplinspace)
- [np.eye](#npeye)
- [astype](#astype)
- [copy versus view](#copy-versus-view)
- [np.reshape](#npreshape)

## np.array

**Tipe:** fungsi konstruktor NumPy

**Untuk apa:** membuat `ndarray` dari list, tuple, atau iterable. Ini pintu masuk paling sering. NumPy menebak `dtype` dari isi, atau kamu tentukan sendiri.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 70, 90])
matriks = np.array([[1, 2, 3], [4, 5, 6]])
campur = np.array([80, 70.5])
print(nilai)
print(matriks)
print(campur, campur.dtype)
```

**Yang terjadi:**

- `nilai` adalah vektor 1 dimensi: `[80 70 90]`.
- `matriks` 2 baris 3 kolom.
- Campuran int dan float dipromosikan ke `float64`; `70.5` memaksa semuanya pecahan.

**Biasanya digabungkan dengan:** `dtype=`, `reshape`, operasi vektor file 05.

**Jangan:** `np.array(80, 70, 90)` — itu dua/tiga argumen, bukan satu list. Bungkus `[...]`.

## ndarray

**Tipe:** class NumPy (`numpy.ndarray`)

**Untuk apa:** wadah n-dimensi. Hampir semua hasil NumPy bertipe ini, termasuk “skalar” hasil `array.sum()` kadang masih 0-d array. Atribut penting: `shape`, `dtype`, `ndim`.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([[80, 70], [90, 65]])
print(type(a))
print(a.ndim, a.shape, a.dtype)
print(isinstance(a, np.ndarray))
```

**Yang terjadi:**

- `type(a)` → `<class 'numpy.ndarray'>`.
- `ndim=2`, `shape=(2, 2)`, `dtype` biasanya `int64` di macOS 64-bit (bisa `int32` di Windows).
- `isinstance` → `True`.

**Biasanya digabungkan dengan:** pandas (kolom bisa diubah ke array lewat `.to_numpy()`).

**Jangan:** mengira `type(a[0, 0])` selalu `int` Python. Itu sering `numpy.int64`. Untuk JSON, konversi `int(a[0, 0])`.

## dtype

**Tipe:** objek tipe elemen ndarray

**Untuk apa:** menyatakan tipe **setiap** elemen: integer lebar berapa, float lebar berapa, bool. Satu array satu dtype (kecuali `object`, yang sebaiknya dihindari).

**Contoh implementasi:**

```python
import numpy as np

a = np.array([80, 70, 90], dtype=np.int32)
b = np.array([80, 70, 90], dtype="float64")
print(a.dtype, b.dtype)
print(a)
print(b)
```

**Yang terjadi:**

- `a.dtype` → `int32`, cetakan `[80 70 90]`.
- `b.dtype` → `float64`, cetakan `[80. 70. 90.]` (ada titik).

**Biasanya digabungkan dengan:** `astype`, baca file biner, hemat memori.

**Jangan:** mencampur string nama orang ke array angka. Array jadi `object` atau error saat operasi matematika.

## int32

**Tipe:** dtype ndarray (bilangan utuh 32-bit)

**Untuk apa:** integer dari sekitar −2 juta sampai +2 juta (`-2147483648` … `2147483647`). Lebih hemat memori daripada `int64`. Cukup untuk nilai ujian, tahun, indeks sedang.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([80, 70, 90], dtype=np.int32)
print(a.dtype, a.itemsize)
besar = np.array([3000000000], dtype=np.int64)
print(besar)
try:
    np.array([3000000000], dtype=np.int32)
except OverflowError as e:
    print("overflow saat buat:", e)
```

**Yang terjadi:**

- `itemsize` `int32` = 4 byte.
- 3 miliar tidak muat di `int32` (batas ~2,1 miliar); pembuatan bisa `OverflowError` atau wrap, tergantung versi. Contoh menangkap error.
- Versi `int64` aman.

**Biasanya digabungkan dengan:** gambar (kadang), indeks, data diskrit.

**Jangan:** menaruh jumlah penduduk dunia atau uang triliunan di `int32`. Overflow membuat angka jadi negatif tanpa ribut.

## int64

**Tipe:** dtype ndarray (bilangan utuh 64-bit)

**Untuk apa:** integer besar: timestamp nanodetik, uang dalam rupiah utuh, ID. Default integer NumPy di banyak platform 64-bit.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([80, 70], dtype=np.int64)
print(a.dtype, a.itemsize)
print(np.array([10**15], dtype=np.int64))
```

**Yang terjadi:**

- `itemsize` = 8 byte.
- `10**15` muat; tercetak `1000000000000000`.

**Biasanya digabungkan dengan:** indeks pandas, waktu Unix * 1000.

**Jangan:** mengira `int64` sama dengan `int` Python tak terbatas. `int64` tetap overflow di `2**63`.

## float32

**Tipe:** dtype ndarray (pecahan 32-bit)

**Untuk apa:** hemat memori dan kadang lebih cepat di GPU/model. Presisi ~7 digit desimal. Untuk IPK dan rata-rata kelas, biasanya masih oke; untuk akumulasi panjang, hati-hati.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([3.75, 2.5], dtype=np.float32)
print(a.dtype, a.itemsize)
print(a)
print(np.array([0.1], dtype=np.float32) + np.array([0.2], dtype=np.float32))
```

**Yang terjadi:**

- 4 byte per elemen.
- Cetakan `3.75 2.5`.
- `0.1 + 0.2` di float32 juga tidak persis `0.3`.

**Biasanya digabungkan dengan:** machine learning (di luar bab), gambar.

**Jangan:** membandingkan `float32` dengan literal Python `0.1` (`float64`) lalu kaget tidak sama.

## float64

**Tipe:** dtype ndarray (pecahan 64-bit, default)

**Untuk apa:** pecahan “biasa” di sains data. Presisi ~15 digit. Ini default `np.array([1.0, 2.0])`.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([3.75, 2.5])
print(a.dtype)
print(a.sum())
print((np.array([0.1]) + np.array([0.2]))[0])
```

**Yang terjadi:**

- `dtype` → `float64`.
- `sum` → `6.25`.
- Elemen `0.1+0.2` → `0.30000000000000004`, sama seperti float Python.

**Biasanya digabungkan dengan:** hampir semua statistik file 05, pandas `float64`.

**Jangan:** mengira pindah ke NumPy menyembuhkan error desimal uang. Tetap hitung uang sebagai `int` rupiah jika perlu persis.

## bool dtype

**Tipe:** dtype ndarray

**Untuk apa:** mask `True`/`False` untuk menyaring elemen. Hasil perbandingan array adalah array bool. Satu elemen 1 byte, bukan 1 bit (ada packing khusus, tapi dtype `bool_` standar 1 byte).

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([60, 80, 90])
mask = nilai >= 70
print(mask, mask.dtype)
print(nilai[mask])
print(mask.sum())
```

**Yang terjadi:**

- `mask` → `[False  True  True]`, dtype `bool`.
- `nilai[mask]` → `[80 90]`.
- `mask.sum()` menghitung `True` sebagai 1 → `2` (berapa yang lulus).

**Biasanya digabungkan dengan:** `np.where`, filter pandas, indexing boolean.

**Jangan:** `nilai >= 70 and nilai <= 90`. `and` tidak bekerja di array. Pakai `&` dan kurung: `(nilai >= 70) & (nilai <= 90)`.

## dtype object

**Tipe:** dtype ndarray (pointer Python)

**Untuk apa:** menampung objek Python sebarang di dalam array. Kehilangan kecepatan NumPy. Kadang muncul tanpa sengaja saat list berisi tipe campur atau string panjang + angka.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([80, "tujuh puluh", None], dtype=object)
print(a, a.dtype)
print(type(a[0]), type(a[1]))
```

**Yang terjadi:**

- dtype `object`.
- Elemen pertama masih `int`, kedua `str`.
- Operasi `a + 1` akan error atau perilaku aneh.

**Biasanya digabungkan dengan:** (sebaiknya) dikonversi ke kolom pandas terpisah, bukan dihitung di NumPy.

**Jangan:** `np.array([1, 2, [3, 4]])` lalu kaget dapat object. Rapikan jadi array 2d atau list biasa.

## shape

**Tipe:** atribut ndarray (tuple)

**Untuk apa:** menyatakan jumlah elemen per sumbu. `(4,)` vektor 4, `(2, 3)` 2 baris 3 kolom, `(2, 3, 4)` tensor. Wajib dicek sebelum `matmul` dan `broadcast`.

**Contoh implementasi:**

```python
import numpy as np

v = np.array([80, 70, 90, 65])
m = np.array([[1, 2, 3], [4, 5, 6]])
print(v.shape)
print(m.shape)
print(np.array(5).shape)
```

**Yang terjadi:**

- `v.shape` → `(4,)`.
- `m.shape` → `(2, 3)`.
- Skalar array → `()` tuple kosong.

**Biasanya digabungkan dengan:** `reshape`, `axis`, pandas `.shape`.

**Jangan:** menulis `if shape == 4`. `shape` adalah tuple. Bandingkan `(4,)` atau `shape[0]`.

## ndim

**Tipe:** atribut ndarray

**Untuk apa:** berapa banyak sumbu. 0 = skalar, 1 = vektor, 2 = matriks. `ndim == len(shape)`.

**Contoh implementasi:**

```python
import numpy as np

print(np.array(3).ndim)
print(np.array([3, 4]).ndim)
print(np.array([[3, 4]]).ndim)
```

**Yang terjadi:**

- `0`, `1`, `2` berturut-turut.

**Biasanya digabungkan dengan:** cek input fungsi, `np.newaxis` untuk menambah dimensi.

**Jangan:** mengira `[[1, 2, 3]]` sama dengan `[1, 2, 3]`. `ndim` 2 vs 1; `matmul` dan broadcast berbeda.

## size

**Tipe:** atribut ndarray

**Untuk apa:** total elemen, hasil kali semua angka di `shape`. Bukan ukuran byte (`nbytes`).

**Contoh implementasi:**

```python
import numpy as np

m = np.zeros((2, 3, 4))
print(m.shape, m.size)
print(2 * 3 * 4)
```

**Yang terjadi:**

- `shape (2, 3, 4)`, `size 24`.
- Perkalian manual sama 24.

**Biasanya digabungkan dengan:** `reshape(m.size)` jadi vektor, cek kosong `size == 0`.

**Jangan:** menukar `size` dengan `len(m)`. `len` hanya sumbu pertama: `len` matriks `(2,3)` adalah `2`.

## itemsize dan nbytes

**Tipe:** atribut ndarray

**Untuk apa:** `itemsize` byte per elemen, `nbytes` total ≈ `itemsize * size`. Berguna memperkirakan RAM.

**Contoh implementasi:**

```python
import numpy as np

a = np.zeros(1000, dtype=np.float64)
b = np.zeros(1000, dtype=np.float32)
print(a.itemsize, a.nbytes)
print(b.itemsize, b.nbytes)
```

**Yang terjadi:**

- `float64`: 8 byte × 1000 = 8000.
- `float32`: 4 byte × 1000 = 4000.

**Biasanya digabungkan dengan:** pilih dtype hemat, cek apakah data muat di laptop.

**Jangan:** mengira `nbytes` termasuk overhead Python object. Ini ukuran buffer array, bukan seluruh proses.

## axis

**Tipe:** parameter operasi reduksi

**Untuk apa:** memilih **sumbu yang dilumat**. Bayangkan: `axis=0` merosot di arah baris (turun), `axis=1` merosot di arah kolom (ke samping). Hasil `shape` kehilangan sumbu itu.

**Contoh implementasi:**

```python
import numpy as np

m = np.array([
    [1, 2, 3],
    [4, 5, 6],
])
print("semua", m.sum())
print("axis=0", m.sum(axis=0), m.sum(axis=0).shape)
print("axis=1", m.sum(axis=1), m.sum(axis=1).shape)
```

**Yang terjadi:**

- Tanpa axis: `21` (semua elemen).
- `axis=0`: jumlah per kolom `[5 7 9]`, shape `(3,)`.
- `axis=1`: jumlah per baris `[6 15]`, shape `(2,)`.

**Biasanya digabungkan dengan:** `mean`, `std`, `argmax`, pandas `axis`.

**Jangan:** menghafal “axis=0 itu kolom” tanpa gambar. Cek `shape` sebelum dan sesudah. Kalau ragu, `print`.

## indexing ndarray

**Tipe:** sintaks akses elemen

**Untuk apa:** mengambil satu elemen atau subarray. Matriks pakai `a[baris, kolom]`, bukan `a[baris][kolom]` (yang terakhir membuat view antara, lebih lambat dan kadang salinan).

**Contoh implementasi:**

```python
import numpy as np

m = np.array([[10, 20, 30], [40, 50, 60]])
print(m[0, 1])
print(m[1])
print(m[-1, -1])
```

**Yang terjadi:**

- `m[0, 1]` → `20` (baris 0, kolom 1).
- `m[1]` → baris kedua `[40 50 60]`.
- `m[-1, -1]` → `60`.

**Biasanya digabungkan dengan:** slicing, `np.where` untuk cari indeks dulu.

**Jangan:** `m[0, 3]` pada 3 kolom. `IndexError`. Indeks sah 0..2.

## slicing ndarray

**Tipe:** sintaks potong array

**Untuk apa:** mengambil rentang `[mulai:selesai:langkah]` per sumbu. Hasil sering **view**: mengubah potongan bisa mengubah asli. Batas kanan terbuka, sama seperti list.

**Contoh implementasi:**

```python
import numpy as np

m = np.arange(12).reshape(3, 4)
print(m)
print("baris 0-1, kolom 1-3:")
print(m[0:2, 1:3])
print("semua baris, kolom terakhir:")
print(m[:, -1])
```

**Yang terjadi:**

- `m` adalah
  ```
  [[ 0  1  2  3]
   [ 4  5  6  7]
   [ 8  9 10 11]]
  ```
- `m[0:2, 1:3]` → `[[1 2] [5 6]]`.
- `m[:, -1]` → `[3 7 11]`.

**Biasanya digabungkan dengan:** `copy()` jika mau potongan mandiri, broadcast assignment `m[:, 0] = 0`.

**Jangan:** mengira slicing 1d `m[0:2][1:3]` sama dengan `m[0:2, 1:3]`. Rantai `[][]` memotong bertahap, bukan dua sumbu sekaligus.

## fancy indexing

**Tipe:** indexing dengan array indeks

**Untuk apa:** mengambil banyak elemen sesuai daftar indeks, tidak harus berurutan. Hasilnya **salinan**, bukan view.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([60, 70, 80, 90, 100])
idx = np.array([4, 0, 2])
print(nilai[idx])
m = np.arange(12).reshape(3, 4)
print(m[[0, 2], [1, 3]])
```

**Yang terjadi:**

- `nilai[idx]` → `[100 60 80]` (urutan mengikuti `idx`).
- Pasangan indeks `(0,1)` dan `(2,3)` → elemen `1` dan `11`.

**Biasanya digabungkan dengan:** `argsort`, `argmax`, ambil top-k.

**Jangan:** menukar fancy dan slice di kepala: `m[[0, 2], 1:3]` adalah campuran (baris 0 dan 2, kolom 1–2). Cetak hasilnya.

## boolean mask

**Tipe:** indexing dengan array bool

**Untuk apa:** menyaring elemen yang syaratnya benar. Panjang mask harus selaras (broadcastable) dengan array.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([60, 75, 40, 90])
print(nilai[nilai >= 70])
nilai[nilai < 70] = 70
print(nilai)
```

**Yang terjadi:**

- Saring: `[75 90]`.
- Assignment: yang < 70 diganti 70 → `[70 75 70 90]`.

**Biasanya digabungkan dengan:** `& | ~`, `np.where`, filter pandas.

**Jangan:** `nilai[nilai >= 70 and nilai < 95]`. Pakai `(nilai >= 70) & (nilai < 95)`.

## broadcast

**Tipe:** aturan operasi antar array

**Untuk apa:** menyejajarkan shape berbeda tanpa menulis loop. NumPy “meregangkan” sumbu berukuran 1. Contoh klasik: matriks `(3, 4)` dikurangi vektor `(4,)`.

**Contoh implementasi:**

```python
import numpy as np

m = np.array([[10, 20, 30], [40, 50, 60]], dtype=float)
rata_kolom = m.mean(axis=0)
print("rata kolom", rata_kolom)
print(m - rata_kolom)
v = np.array([[1], [2]])
print(m + v)
```

**Yang terjadi:**

- `rata_kolom` shape `(3,)`: rata-rata tiap kolom.
- `m - rata_kolom` mengurangi setiap baris dengan vektor yang sama (center per kolom).
- `v` shape `(2, 1)` ditambah ke `(2, 3)`: setiap kolom dapat `+1` di baris 0 dan `+2` di baris 1.

**Biasanya digabungkan dengan:** standardisasi `(x - mean) / std`, `np.newaxis`.

**Jangan:** mengandalkan broadcast yang tidak sengaja. Kalau `shape` tidak selaras: `ValueError: operands could not be broadcast`. Cetak kedua `shape`.

## np.newaxis

**Tipe:** alias `None` untuk menambah sumbu

**Untuk apa:** mengubah vektor `(3,)` jadi baris `(1, 3)` atau kolom `(3, 1)` supaya broadcast/matmul sesuai.

**Contoh implementasi:**

```python
import numpy as np

v = np.array([1, 2, 3])
print(v.shape)
print(v[np.newaxis, :].shape)
print(v[:, np.newaxis].shape)
print(v[:, None] * v[None, :])
```

**Yang terjadi:**

- `(3,)` → `(1, 3)` dan `(3, 1)`.
- Perkalian kolom × baris → matriks 3×3 (tabel kali).

**Biasanya digabungkan dengan:** broadcast, `reshape`, jarak antar titik.

**Jangan:** menumpuk `newaxis` sampai `ndim` 5 tanpa komentar. Teman satu kelompok tersesat.

## np.zeros

**Tipe:** fungsi pabrik array

**Untuk apa:** array berisi nol. Untuk akumulator, placeholder, atau mask awal. Default `float64`.

**Contoh implementasi:**

```python
import numpy as np

print(np.zeros(4))
print(np.zeros((2, 3), dtype=int))
```

**Yang terjadi:**

- Vektor `[0. 0. 0. 0.]`.
- Matriks 2×3 integer `0`.

**Biasanya digabungkan dengan:** loop isi manual (kalau terpaksa), `dtype=bool` (False).

**Jangan:** `np.zeros(2, 3)` — shape harus satu tuple `(2, 3)`.

## np.ones

**Tipe:** fungsi pabrik array

**Untuk apa:** array berisi satu. Berguna untuk bobot awal, pengali, atau `np.ones_like(a)`.

**Contoh implementasi:**

```python
import numpy as np

print(np.ones(3))
print(np.ones((2, 2), dtype=np.int32))
a = np.array([80, 70, 90])
print(np.ones_like(a))
```

**Yang terjadi:**

- `[1. 1. 1.]`.
- Matriks 2×2 `int32` berisi 1.
- `ones_like` meniru shape dan dtype `a`: `[1 1 1]`.

**Biasanya digabungkan dengan:** broadcast, matriks identitas kalikan skalar.

**Jangan:** memakai `ones` sebagai “array kosong”. Kosong yang dimaksud orang biasanya `zeros` atau `empty` (isi sampah).

## np.full

**Tipe:** fungsi pabrik array

**Untuk apa:** mengisi semua elemen dengan nilai yang sama, bukan hanya 0/1.

**Contoh implementasi:**

```python
import numpy as np

print(np.full((2, 3), 70))
print(np.full(4, 3.14, dtype=float))
```

**Yang terjadi:**

- Matriks 2×3 semua `70`.
- Vektor empat `3.14`.

**Biasanya digabungkan dengan:** nilai pengisi missing (sementara), background gambar.

**Jangan:** `full` dengan list `[1, 2]` sebagai fill_value untuk shape aneh lalu kaget dtype object.

## np.arange

**Tipe:** fungsi pabrik array

**Untuk apa:** deret angka seperti `range`, tapi hasilnya ndarray dan boleh float. Batas kanan terbuka.

**Contoh implementasi:**

```python
import numpy as np

print(np.arange(5))
print(np.arange(2, 10, 2))
print(np.arange(0.0, 1.0, 0.3))
```

**Yang terjadi:**

- `0..4`.
- `2,4,6,8`.
- Float: `0.0 0.3 0.6 0.9` (bisa ada kejutan presisi; untuk jumlah titik pasti, pakai `linspace`).

**Biasanya digabungkan dengan:** `reshape`, sumbu x grafik.

**Jangan:** `arange(0, 1, 0.1)` lalu andalkan panjang persis 10. Float step bisa 10 atau 11 elemen. `linspace` lebih aman.

## np.linspace

**Tipe:** fungsi pabrik array

**Untuk apa:** deret dengan **jumlah titik** yang kamu tentukan, inklusif di kedua ujung (default). Ideal untuk sumbu grafik.

**Contoh implementasi:**

```python
import numpy as np

print(np.linspace(0, 1, 5))
print(np.linspace(0, 10, 3))
```

**Yang terjadi:**

- 5 titik dari 0 sampai 1: `0, 0.25, 0.5, 0.75, 1`.
- 3 titik dari 0 sampai 10: `0, 5, 10`.

**Biasanya digabungkan dengan:** matplotlib `plot(x, y)`, fungsi matematika.

**Jangan:** menukar argumen `linspace(start, jumlah, stop)`. Urutannya `start, stop, num`.

## np.eye

**Tipe:** fungsi pabrik array

**Untuk apa:** matriks identitas: 1 di diagonal, 0 di tempat lain. Bahan aljabar linear, bukan kebutuhan harian pandas, tapi sering muncul di soal matriks.

**Contoh implementasi:**

```python
import numpy as np

print(np.eye(3))
print(np.eye(3, k=1))
```

**Yang terjadi:**

- 3×3 identitas.
- `k=1` menggeser diagonal ke atas: 1 di atas diagonal utama.

**Biasanya digabungkan dengan:** `matmul`, sistem persamaan.

**Jangan:** `eye(3, 3, 3)` mengira tensor 3d. Argumen ketiga adalah `k` (geser diagonal), bukan dimensi ketiga.

## astype

**Tipe:** method ndarray

**Untuk apa:** menyalin array ke dtype lain. Casting float→int memotong ke arah nol. Casting ke bool: 0 jadi False, selainnya True.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([1.9, 2.1, 0.0])
print(a.astype(int))
print(a.astype(bool))
print(a.astype(np.float32).dtype)
```

**Yang terjadi:**

- Int: `[1 2 0]`.
- Bool: `[ True  True False]`.
- `float32` dtype berubah, nilai kira-kira sama.

**Biasanya digabungkan dengan:** hemat memori, persiapan `int` untuk indeks.

**Jangan:** `astype(int)` pada NaN. Hasil tidak masuk akal / peringatan. Tangani NaN dulu.

## copy versus view

**Tipe:** konsep memori ndarray

**Untuk apa:** tahu kapan mengubah potongan merusak asli. Slicing dasar biasanya view. Fancy/boolean biasanya copy. `a.copy()` memaksa salinan.

**Contoh implementasi:**

```python
import numpy as np

a = np.array([10, 20, 30, 40])
potong = a[1:3]
potong[0] = 999
print("asli setelah view", a)

b = np.array([10, 20, 30, 40])
salin = b[1:3].copy()
salin[0] = 999
print("asli setelah copy", b)
print("b.base is None", b.base is None, "potong.base is a", potong.base is a)
```

**Yang terjadi:**

- View: `a` jadi `[10 999 30 40]`.
- Copy: `b` tetap `[10 20 30 40]`.
- `base` menunjuk array pemilik; `None` berarti pemilik sendiri.

**Biasanya digabungkan dengan:** slicing, fungsi yang tidak boleh mengubah input.

**Jangan:** mengembalikan slice dari fungsi lalu pemanggil mengubahnya tanpa sadar merusak cache internal.

## np.reshape

**Tipe:** fungsi / method ndarray

**Untuk apa:** mengubah `shape` tanpa (biasanya) mengubah data. Jumlah elemen harus sama. `-1` berarti “hitung otomatis”.

**Contoh implementasi:**

```python
import numpy as np

a = np.arange(6)
print(a.reshape(2, 3))
print(a.reshape(3, -1))
print(a.reshape(2, 3).T)
```

**Yang terjadi:**

- `reshape(2, 3)`:
  ```
  [[0 1 2]
   [3 4 5]]
  ```
- `reshape(3, -1)` → 3×2.
- `.T` adalah transpose: 3×2 dari 2×3.

**Biasanya digabungkan dengan:** `matmul`, gambar (`H, W, C`), file 05.

**Jangan:** `reshape` yang elemennya tidak pas: `arange(6).reshape(2, 4)` → `ValueError`.

---

Operasi statistik dan matriks ada di [05-numpy-operasi-statistik.md](05-numpy-operasi-statistik.md).
