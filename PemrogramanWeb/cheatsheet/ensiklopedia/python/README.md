# Ensiklopedia Cheatsheet Python

Katalog tipe, fungsi, dan method Python untuk kuliah pemrograman web dan analisis data. Bukan daftar seluruh PyPI. Yang dicover: **dasar Python**, **file/JSON/CSV**, **NumPy**, **pandas**, **matplotlib/seaborn**, plus **requests**, **datetime**, dan **regex**.

Bahasa Indonesia, seperti menjelaskan ke teman satu kelas. Setiap entri punya: **tipe**, **untuk apa**, **contoh yang bisa dijalankan**, **apa yang terjadi di output**, **biasanya digabung dengan apa**, dan **satu kesalahan yang sering**.

[← Cheatsheet utama](../../README.md) · [Indeks ensiklopedia](../README.md)

## Cara memakai folder ini

1. Buka file sesuai topik, lalu cari nama di daftar isi.
2. Baca **Untuk apa** dulu, baru salin **Contoh implementasi**.
3. Contoh adalah skrip terpisah. Jangan menempelkan semua contoh ke satu file.
4. Setelah menyalin, ubah satu nilai lalu jalankan lagi. Kalau output berubah sesuai dugaan, kamu sudah paham.

Urutan belajar: **01 tipe → 02 kontrol/fungsi → 03 file → 04 NumPy array → 05 NumPy hitung → 06 pandas tabel → 07 filter/groupby → 08 grafik → 09 HTTP/tanggal/regex → 10 resep**.

## Cara install

Python sudah sering terpasang di macOS. Cek dulu:

```bash
python3 --version
```

Kalau muncul `Python 3.10` atau lebih baru, lanjut. Kalau perintah tidak ketemu, unduh dari [python.org](https://www.python.org/downloads/) atau pakai Homebrew: `brew install python`.

### pip

`pip` mengunduh paket. Selalu panggil lewat `python3 -m pip` supaya yang terpakai adalah pip milik Python yang sama.

```bash
python3 -m pip --version
python3 -m pip install --upgrade pip
```

### venv (sangat disarankan)

Lingkungan virtual menyimpan paket di folder proyek, bukan di Python sistem. Satu mata kuliah satu venv, supaya versi pandas tidak bentrok dengan tugas lain.

```bash
cd /Users/haikalmuzhoffar/KULIAH/PemrogramanWeb
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install numpy pandas matplotlib seaborn requests jupyter
```

Setelah `activate`, prompt biasanya diawali `(.venv)`. Untuk keluar: `deactivate`.

Di Windows (kalau suatu saat buka laptop lain):

```bat
python -m venv .venv
.venv\Scripts\activate
```

### Paket yang dipakai ensiklopedia ini

| Paket | Untuk apa |
| --- | --- |
| *(bawaan)* | tipe, kontrol, file, `json`, `csv`, `pathlib`, `datetime`, `re` |
| `numpy` | array, dtype, broadcast, statistik, matriks |
| `pandas` | Series, DataFrame, filter, groupby, merge |
| `matplotlib` | plot garis, batang, hist, scatter |
| `seaborn` | countplot, heatmap, tema grafik |
| `requests` | GET/POST HTTP |

Ini **bukan** katalog seluruh PyPI. Tidak dibahas: Django, Flask, FastAPI, scikit-learn, TensorFlow, Polars, SQLAlchemy, dan ratusan paket lain. Kalau tugas kuliah memakai stack di tabel, folder ini cukup.

### Jupyter (opsional)

Notebook enak untuk coba pandas baris demi baris. Tidak wajib.

```bash
source .venv/bin/activate
python -m pip install jupyter
jupyter notebook
```

Atau `jupyter lab`. Sel selalu dijalankan dari atas. Kalau variabel `df` tiba-tiba tidak ketemu, sel pembuatnya belum dijalankan.

### Menjalankan contoh

Simpan potongan kode ke `coba.py`, lalu:

```bash
source .venv/bin/activate
python coba.py
```

Atau tempel di REPL:

```bash
python
```

Keluar REPL: `exit()` atau Ctrl-D.

Contoh matplotlib menulis file `.png` di folder kerja. Contoh `requests` butuh internet. Contoh file/JSON/CSV menulis file kecil; hapus sendiri kalau sudah selesai.

## Daftar file

| File | Isi |
| --- | --- |
| [01-dasar-tipe-variabel.md](01-dasar-tipe-variabel.md) | `int`, `float`, `str`, `bool`, `None`, `list`, `tuple`, `dict`, `set`, operator, method umum |
| [02-kontrol-fungsi-modul.md](02-kontrol-fungsi-modul.md) | `if`, loop, `def`, `lambda`, `import`, `try`, class singkat |
| [03-file-pathlib-json-csv.md](03-file-pathlib-json-csv.md) | `open`, `pathlib`, `json`, `csv` |
| [04-numpy-array-tipe.md](04-numpy-array-tipe.md) | `ndarray`, dtype, `shape`, `axis`, indeks, slice, broadcast |
| [05-numpy-operasi-statistik.md](05-numpy-operasi-statistik.md) | `sum`, `mean`, `std`, `argmax`, `reshape`, `matmul`, `where`, `clip` |
| [06-pandas-series-dataframe.md](06-pandas-series-dataframe.md) | Series, DataFrame, dtypes, `loc`/`iloc`, `head`, `info`, `describe` |
| [07-pandas-filter-groupby-merge.md](07-pandas-filter-groupby-merge.md) | filter, `assign`, groupby, merge/join/concat, data hilang |
| [08-matplotlib-seaborn.md](08-matplotlib-seaborn.md) | plot garis/batang/hist/scatter, label, legend, countplot, heatmap |
| [09-requests-datetime-regex.md](09-requests-datetime-regex.md) | `requests`, `datetime`, `timedelta`, `re` |
| [10-resep-analisis-kesalahan.md](10-resep-analisis-kesalahan.md) | resep CSV → bersih → groupby → grafik, plus kesalahan umum |

## Peta cepat: “Saya ingin…”

### Menyimpan data

- Bilangan utuh: [01 — `int`](01-dasar-tipe-variabel.md#int)
- Desimal: [01 — `float`](01-dasar-tipe-variabel.md#float)
- Teks: [01 — `str`](01-dasar-tipe-variabel.md#str)
- Ya/tidak: [01 — `bool`](01-dasar-tipe-variabel.md#bool)
- Kosong sadar: [01 — `None`](01-dasar-tipe-variabel.md#none)
- Daftar bisa diubah: [01 — `list`](01-dasar-tipe-variabel.md#list)
- Daftar terkunci: [01 — `tuple`](01-dasar-tipe-variabel.md#tuple)
- Pasangan kunci-nilai: [01 — `dict`](01-dasar-tipe-variabel.md#dict)
- Anggota unik: [01 — `set`](01-dasar-tipe-variabel.md#set)

### Memilih, mengulang, membungkus langkah

- Cabang: [02 — `if`](02-kontrol-fungsi-modul.md#if)
- Ulang daftar: [02 — `for`](02-kontrol-fungsi-modul.md#for)
- Fungsi: [02 — `def`](02-kontrol-fungsi-modul.md#def)
- Modul: [02 — `import`](02-kontrol-fungsi-modul.md#import)
- Error: [02 — `try`](02-kontrol-fungsi-modul.md#try-except-finally)

### Baca tulis file

- Teks biasa: [03 — `open`](03-file-pathlib-json-csv.md#open)
- Path modern: [03 — `Path`](03-file-pathlib-json-csv.md#path)
- JSON: [03 — `json.loads`](03-file-pathlib-json-csv.md#jsonloads)
- CSV: [03 — `csv.DictReader`](03-file-pathlib-json-csv.md#csvdictreader)

### Hitung cepat di array

- Buat array: [04 — `np.array`](04-numpy-array-tipe.md#nparray)
- Tipe elemen: [04 — `dtype`](04-numpy-array-tipe.md#dtype)
- Rata-rata: [05 — `mean`](05-numpy-operasi-statistik.md#npmean)
- Kali matriks: [05 — `matmul`](05-numpy-operasi-statistik.md#npmatmul)
- Ganti bersyarat: [05 — `where`](05-numpy-operasi-statistik.md#npwhere)

### Tabel seperti Excel

- Satu kolom: [06 — Series](06-pandas-series-dataframe.md#series)
- Banyak kolom: [06 — DataFrame](06-pandas-series-dataframe.md#dataframe)
- Ambil baris/kolom: [06 — `loc`](06-pandas-series-dataframe.md#loc)
- Saring: [07 — filter](07-pandas-filter-groupby-merge.md#filter-boolean)
- Ringkas per kelompok: [07 — `groupby`](07-pandas-filter-groupby-merge.md#groupby)
- Gabung tabel: [07 — `merge`](07-pandas-filter-groupby-merge.md#merge)

### Gambar dan internet

- Garis: [08 — `plot`](08-matplotlib-seaborn.md#pltplot)
- Batang: [08 — `bar`](08-matplotlib-seaborn.md#pltbar)
- Heatmap: [08 — `heatmap`](08-matplotlib-seaborn.md#snsheatmap)
- Ambil API: [09 — `requests.get`](09-requests-datetime-regex.md#requestsget)
- Tanggal: [09 — `datetime`](09-requests-datetime-regex.md#datetimedatetime)
- Pola teks: [09 — `re.search`](09-requests-datetime-regex.md#research)

### Alur analisis utuh

- Baca CSV sampai grafik: [10 — resep utama](10-resep-analisis-kesalahan.md#resep-baca-csv-bersihkan-groupby-grafik)

## Aturan contoh

- Setiap contoh punya `import` (kalau perlu), data kecil, dan `print`.
- Nama variabel memakai konteks kuliah: nilai, mata kuliah, toko ATK, absensi.
- NumPy/pandas butuh paket terpasang. Kalau `ModuleNotFoundError`, aktifkan venv lalu `pip install` lagi.
- Matplotlib contoh ini menyimpan PNG. Tidak memaksa jendela GUI.
- `requests` contoh ini memakai URL publik. Ganti URL jika layanan sedang down.

## Yang tidak diklaim

Folder ini **tidak** mengcover semua package di PyPI. Tidak ada jaminan versi terbaru setiap fungsi. Fokusnya: cukup untuk tugas data + dasar Python, dengan contoh yang bisa dijalankan malam ini.

Kembali ke [indeks ensiklopedia](../README.md).
