# 06 — pandas: Series, DataFrame, indeks, loc/iloc

[← 05 NumPy hitung](05-numpy-operasi-statistik.md) · [Indeks](README.md) · [Lanjut 07 →](07-pandas-filter-groupby-merge.md)

pandas adalah tabel berlabel. **Series** satu kolom, **DataFrame** banyak kolom. Di bawahnya sering ada NumPy, tapi kamu bekerja dengan nama kolom dan indeks, bukan hanya angka posisi.

```bash
python -m pip install pandas
```

Konvensi: `import pandas as pd`.

## Daftar isi

- [Series](#series)
- [DataFrame](#dataframe)
- [dtypes](#dtypes)
- [index](#index)
- [columns](#columns)
- [pilih kolom](#pilih-kolom)
- [loc](#loc)
- [iloc](#iloc)
- [at dan iat](#at-dan-iat)
- [head](#head)
- [tail](#tail)
- [info](#info)
- [describe](#describe)
- [shape](#shape)
- [values dan to_numpy](#values-dan-to_numpy)
- [read_csv](#read_csv)
- [to_csv](#to_csv)
- [value_counts](#value_counts)
- [unique dan nunique](#unique-dan-nunique)
- [sort_values](#sort_values)
- [sort_index](#sort_index)
- [rename](#rename)
- [drop](#drop)
- [reset_index](#reset_index)
- [set_index](#set_index)
- [astype](#astype)
- [copy](#copy)
- [sample](#sample)
- [assign singkat](#assign-singkat)

## Series

**Tipe:** class `pandas.Series`

**Untuk apa:** vektor 1d berlabel. Setiap nilai punya indeks. Satu kolom DataFrame adalah Series. Operasi NumPy-like (`mean`, `+`) tersedia, plus label.

**Contoh implementasi:**

```python
import pandas as pd

nilai = pd.Series([80, 70, 90], index=["Haikal", "Siti", "Budi"], name="uts")
print(nilai)
print(nilai["Siti"])
print(nilai.mean())
print(nilai.dtype)
```

**Yang terjadi:**

- Cetakan tiga baris berlabel nama, plus `Name: uts` dan `dtype: int64`.
- `nilai["Siti"]` → `70` (akses label, bukan posisi).
- `mean` → `80.0`.
- `dtype` integer (tepatnya tergantung platform).

**Biasanya digabungkan dengan:** DataFrame `df["uts"]`, `value_counts`.

**Jangan:** mengira `nilai[0]` selalu elemen pertama. Kalau indeksnya integer lain, `[]` memakai **label**. Pakai `iloc[0]` untuk posisi.

## DataFrame

**Tipe:** class `pandas.DataFrame`

**Untuk apa:** tabel 2d: baris × kolom bernama. Ini objek utama analisis data tabular. Bisa dibuat dari dict kolom, list of dict, atau file.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti", "Budi"],
    "mk": ["Web", "Web", "Basis"],
    "nilai": [88, 70, 91],
})
print(df)
print(type(df))
```

**Yang terjadi:**

- Tabel 3 baris, 3 kolom, indeks default `0,1,2`.
- `type` → `<class 'pandas.DataFrame'>`.

**Biasanya digabungkan dengan:** `read_csv`, `loc`, `groupby`, matplotlib.

**Jangan:** membuat DataFrame dari dict yang panjang listnya beda. `ValueError: arrays must all be same length`.

## dtypes

**Tipe:** atribut DataFrame (Series of dtype)

**Untuk apa:** melihat tipe tiap kolom. Analisis rusak hampir selalu karena kolom angka masih `object` (string). Cek ini lebih dulu daripada `mean`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti"],
    "nilai": ["88", "70"],
    "lulus": [True, False],
})
print(df.dtypes)
print(pd.to_numeric(df["nilai"]).dtype)
```

**Yang terjadi:**

- `nama` object/string, `nilai` object (karena diketik sebagai str), `lulus` bool.
- `to_numeric` mengubah nilai jadi numerik (`int64` atau `int64` nullable).

**Biasanya digabungkan dengan:** `astype`, `read_csv` `dtype=`, `info`.

**Jangan:** `df["nilai"].mean()` saat dtype object berisi string angka. Error atau hasil mustahil. Konversi dulu.

## index

**Tipe:** atribut `Index`

**Untuk apa:** label baris. Default `RangeIndex` 0..n-1. Bisa nama, tanggal, NIM. Banyak fungsi (`loc`, `reindex`, `align`) bergantung pada ini, bukan urutan fisik saja.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70]}, index=["2101", "2102"])
print(df.index)
print(df.index.tolist())
print(df.loc["2101"])
```

**Yang terjadi:**

- `index` menampilkan `Index(['2101', '2102'], ...)`.
- `tolist()` → `['2101', '2102']`.
- `loc["2101"]` mengambil baris itu sebagai Series.

**Biasanya digabungkan dengan:** `set_index`, `reset_index`, `loc`.

**Jangan:** menganggap indeks selalu unik. Duplikat diizinkan, dan `loc` lalu mengembalikan beberapa baris. `df.index.is_unique` untuk cek.

## columns

**Tipe:** atribut `Index` (nama kolom)

**Untuk apa:** daftar nama kolom. Bisa diganti, diurut, dipilih. Nama duplikat diizinkan tapi menyulitkan; hindari.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88], "mk": ["Web"]})
print(df.columns.tolist())
df.columns = ["skor", "mata_kuliah"]
print(df)
```

**Yang terjadi:**

- Awal: `['nilai', 'mk']`.
- Ganti semua nama sekaligus → kolom `skor`, `mata_kuliah`.

**Biasanya digabungkan dengan:** `rename`, `reindex`, filter `df[df.columns[:2]]`.

**Jangan:** `df.columns[0] = "x"` di beberapa versi (Index immutable). Pakai `rename` atau assign `columns` utuh.

## pilih kolom

**Tipe:** indexing DataFrame

**Untuk apa:** `df["nilai"]` → Series. `df[["nilai", "mk"]]` → DataFrame (perhatikan list di dalam). Ini operasi harian nomor satu.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti"],
    "nilai": [88, 70],
    "mk": ["Web", "Web"],
})
kolom = df["nilai"]
tabel = df[["nama", "nilai"]]
print(type(kolom), type(tabel))
print(tabel)
```

**Yang terjadi:**

- Satu kurung: Series.
- Kurung berisi list: DataFrame 2 kolom.
- `print(tabel)` menampilkan nama dan nilai saja.

**Biasanya digabungkan dengan:** filter, `assign`, `groupby`.

**Jangan:** `df["nama", "nilai"]` tanpa list dalam. Itu tuple key → `KeyError`. Tulis `df[["nama", "nilai"]]`.

## loc

**Tipe:** indexer berbasis label

**Untuk apa:** pilih baris/kolom menurut **nama**. Sintaks `df.loc[baris, kolom]`. Slice `loc` **inklusif di kedua ujung** (beda dengan Python biasa dan `iloc`).

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame(
    {"nilai": [88, 70, 91], "mk": ["Web", "Web", "Basis"]},
    index=["Haikal", "Siti", "Budi"],
)
print(df.loc["Siti"])
print(df.loc["Haikal":"Siti", "nilai"])
print(df.loc[df["nilai"] >= 80, ["mk", "nilai"]])
```

**Yang terjadi:**

- Satu label: Series baris Siti.
- Slice nama `Haikal` sampai `Siti` **termasuk Siti**, kolom `nilai`.
- Mask boolean + daftar kolom: hanya yang nilai ≥ 80.

**Biasanya digabungkan dengan:** filter, `assign` lewat `df.loc[mask, "kolom"] = ...`.

**Jangan:** `loc` dengan integer 0 mengira posisi jika indeksnya NIM string. 0 bukan label. Pakai `iloc`.

## iloc

**Tipe:** indexer berbasis posisi

**Untuk apa:** pilih menurut urutan fisik, seperti array. `iloc[0]` baris pertama, `iloc[:, 1]` kolom kedua. Slice **eksklusif di kanan**, seperti Python.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti", "Budi"],
    "nilai": [88, 70, 91],
})
print(df.iloc[0])
print(df.iloc[0:2, 0:2])
print(df.iloc[-1, 1])
```

**Yang terjadi:**

- Baris 0: Series Haikal 88.
- `0:2, 0:2` → dua baris pertama, dua kolom pertama (tanpa baris Budi).
- `-1, 1` → `91` (nilai Budi).

**Biasanya digabungkan dengan:** sample urutan, split train/test kasar `iloc[:n]`.

**Jangan:** `iloc["Haikal"]`. Label tidak diterima. `TypeError` / indexer error.

## at dan iat

**Tipe:** indexer skalar

**Untuk apa:** ambil atau set **satu** sel, lebih tegas dan sering lebih cepat. `at` label, `iat` posisi.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70]}, index=["Haikal", "Siti"])
print(df.at["Siti", "nilai"])
df.iat[0, 0] = 90
print(df)
```

**Yang terjadi:**

- `at` → `70`.
- `iat[0, 0] = 90` mengubah nilai Haikal.
- Tabel: Haikal 90, Siti 70.

**Biasanya digabungkan dengan:** loop kecil (lebih baik vektorisasi), koreksi satu sel.

**Jangan:** `at` untuk ambil banyak sel. Untuk slice, tetap `loc`.

## head

**Tipe:** method DataFrame/Series

**Untuk apa:** melihat n baris pertama (default 5). Reflex pertama setelah `read_csv`. Tidak mengubah data.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": range(10)})
print(df.head())
print(df.head(3))
```

**Yang terjadi:**

- Default: baris 0–4.
- `head(3)`: 0–2.

**Biasanya digabungkan dengan:** `tail`, `info`, `describe`.

**Jangan:** mengira `head` mengembalikan salinan yang aman diubah. Itu view/copy ambigu; untuk ubah data pakai `loc` pada `df` asli.

## tail

**Tipe:** method DataFrame/Series

**Untuk apa:** n baris terakhir. Berguna melihat data time-series terbaru atau cek footer file.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": range(10)})
print(df.tail(2))
```

**Yang terjadi:**

- Dua baris terakhir: indeks 8 dan 9, nilai 8 dan 9.

**Biasanya digabungkan dengan:** `head`, `sort_values`.

**Jangan:** `tail` sebagai “sampel acak”. Itu ujung tabel, bias urutan file. Pakai `sample`.

## info

**Tipe:** method DataFrame

**Untuk apa:** ringkasan teknis: jumlah baris, kolom, non-null, dtype, perkiraan memori. Cetak ke layar, return-nya `None`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti", None],
    "nilai": [88, 70, 91],
})
df.info()
```

**Yang terjadi:**

- 3 entries, kolom `nama` non-null = 2 (ada None), `nilai` 3.
- Dtype tercetak.
- Tidak ada nilai yang di-`print` dari return; output adalah side effect.

**Biasanya digabungkan dengan:** `isna`, `dtypes`, langkah bersih-bersih.

**Jangan:** `x = df.info()` lalu memakai `x`. `x` adalah `None`.

## describe

**Tipe:** method DataFrame/Series

**Untuk apa:** statistik deskriptif kolom numerik: count, mean, std, min, kuartil, max. `include="all"` menambah kolom kategori.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nilai": [88, 70, 91, 65],
    "mk": ["Web", "Web", "Basis", "Web"],
})
print(df.describe())
print(df.describe(include="all"))
```

**Yang terjadi:**

- `describe()` default: hanya `nilai` (mean, std, min, 25%, 50%, 75%, max).
- `include="all"`: kolom `mk` dapat `unique`, `top`, `freq`.

**Biasanya digabungkan dengan:** `groupby.describe`, laporan awal EDA.

**Jangan:** percaya `std` tanpa ingat pandas memakai `ddof=1`. Beda dengan `np.std` default.

## shape

**Tipe:** atribut tuple

**Untuk apa:** `(jumlah_baris, jumlah_kolom)`. Cek cepat apakah merge menggandakan baris.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"a": [1, 2, 3], "b": [4, 5, 6]})
print(df.shape)
print(df.shape[0], len(df))
```

**Yang terjadi:**

- `(3, 2)`.
- `shape[0]` dan `len(df)` sama-sama 3.

**Biasanya digabungkan dengan:** assert setelah filter/merge, `head`.

**Jangan:** `shape()` dengan kurung. Itu atribut, bukan method. `TypeError`.

## values dan to_numpy

**Tipe:** atribut / method

**Untuk apa:** keluar ke NumPy. `to_numpy()` cara modern. `values` masih ada. Hati-hati dtype: tabel campur (angka+string) menghasilkan array `object`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70], "sks": [3, 3]})
print(df.to_numpy())
print(df["nilai"].to_numpy())
```

**Yang terjadi:**

- Matriks 2×2 integer.
- Series → vektor 1d `[88 70]`.

**Biasanya digabungkan dengan:** NumPy `matmul`, scikit-learn (di luar bab).

**Jangan:** mengubah `to_numpy()` lalu mengira DataFrame ikut berubah. Itu salinan atau view tergantung kasus; jangan andalkan. Ubah lewat `df.loc`.

## read_csv

**Tipe:** fungsi `pd.read_csv`

**Untuk apa:** membaca file CSV jadi DataFrame. Parameter yang paling sering: `sep`, `encoding`, `na_values`, `dtype`, `parse_dates`, `usecols`.

**Contoh implementasi:**

```python
import pandas as pd
from pathlib import Path

path = Path("_contoh_nilai.csv")
path.write_text("nama,nilai\nHaikal,88\nSiti,70\n", encoding="utf-8")
df = pd.read_csv(path)
print(df)
print(df.dtypes)
path.unlink()
```

**Yang terjadi:**

- Dua baris data, kolom `nama` dan `nilai`.
- `nilai` terdeteksi numerik otomatis.

**Biasanya digabungkan dengan:** `head`, `info`, `Path`.

**Jangan:** `read_csv` file Excel `.xlsx`. Itu bukan CSV. Pakai `read_excel` (butuh openpyxl) atau ekspor CSV dulu.

## to_csv

**Tipe:** method DataFrame

**Untuk apa:** menulis tabel ke CSV. `index=False` hampir selalu kamu inginkan agar kolom indeks 0,1,2 tidak tersimpan sebagai kolom tak bernama.

**Contoh implementasi:**

```python
import pandas as pd
from pathlib import Path

path = Path("_contoh_out.csv")
df = pd.DataFrame({"nama": ["Haikal"], "nilai": [88]})
df.to_csv(path, index=False)
print(path.read_text(encoding="utf-8"))
path.unlink()
```

**Yang terjadi:**

- Isi file: header `nama,nilai` lalu `Haikal,88`.
- Tanpa kolom indeks.

**Biasanya digabungkan dengan:** `reset_index`, encoding `utf-8-sig` agar Excel Windows membaca huruf Indonesia.

**Jangan:** `to_csv` berulang tanpa `index=False` lalu `read_csv` lagi. Indeks menumpuk jadi `Unnamed: 0`.

## value_counts

**Tipe:** method Series

**Untuk apa:** menghitung frekuensi tiap nilai unik, default terurut dari yang paling sering. Ini `groupby size` untuk satu kolom.

**Contoh implementasi:**

```python
import pandas as pd

mk = pd.Series(["Web", "Web", "Basis", "Web", "Jaringan"])
print(mk.value_counts())
print(mk.value_counts(normalize=True))
```

**Yang terjadi:**

- Web 3, Basis 1, Jaringan 1.
- `normalize=True` → proporsi (Web 0.6).

**Biasanya digabungkan dengan:** `bar`, seaborn `countplot`, cek ketidakseimbangan kelas.

**Jangan:** `value_counts` pada DataFrame langsung tanpa kolom (versi lama error). Tulis `df["mk"].value_counts()`.

## unique dan nunique

**Tipe:** method Series

**Untuk apa:** `unique` daftar nilai unik (urutan kemunculan). `nunique` jumlahnya. `dropna=True` default pada `nunique` (abaikan NaN).

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series(["Web", "Basis", "Web", None])
print(s.unique())
print(s.nunique())
print(s.nunique(dropna=False))
```

**Yang terjadi:**

- `unique` memuat `Web`, `Basis`, `None`/`NaN`.
- `nunique()` → `2` (NaN tidak dihitung).
- `dropna=False` → `3`.

**Biasanya digabungkan dengan:** validasi kategori, `isin`.

**Jangan:** `unique` pada DataFrame. Itu method Series. Untuk tabel: `df.nunique()`.

## sort_values

**Tipe:** method DataFrame/Series

**Untuk apa:** mengurutkan baris menurut kolom. Default tidak mengubah asli (`inplace=False`); hasil baru dikembalikan.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nama": ["Haikal", "Siti", "Budi"], "nilai": [88, 70, 91]})
print(df.sort_values("nilai"))
print(df.sort_values(["nilai"], ascending=False))
```

**Yang terjadi:**

- Naik: Siti 70, Haikal 88, Budi 91.
- Turun: Budi, Haikal, Siti.
- `df` asli tetap urutan lama kecuali di-assign ulang.

**Biasanya digabungkan dengan:** `head` top-k, `groupby` + `sort`.

**Jangan:** `df.sort_values("nilai")` tanpa menyimpan lalu kira `df` sudah terurut. Tulis `df = df.sort_values(...)`.

## sort_index

**Tipe:** method

**Untuk apa:** mengurutkan menurut indeks. Berguna setelah `set_index` tanggal atau nama.

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series([88, 70], index=["Haikal", "Ana"])
print(s.sort_index())
```

**Yang terjadi:**

- Indeks alfabet: Ana dulu, baru Haikal.

**Biasanya digabungkan dengan:** time series, `reindex`.

**Jangan:** menukar dengan `sort_values` saat kamu ingin urut **isi** kolom.

## rename

**Tipe:** method DataFrame

**Untuk apa:** mengganti nama indeks atau kolom dengan dict pemetaan. Lebih aman daripada menimpa `columns` utuh.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"Nilai UTS": [88], "MK": ["Web"]})
baru = df.rename(columns={"Nilai UTS": "nilai_uts", "MK": "mk"})
print(baru.columns.tolist())
```

**Yang terjadi:**

- Kolom jadi `['nilai_uts', 'mk']`.
- `df` asli tidak berubah.

**Biasanya digabungkan dengan:** `str.strip` pada nama kolom kotor dari Excel.

**Jangan:** `rename` dengan typo kunci. Kunci yang tidak ketemu diabaikan diam-diam. Cek `columns` sesudahnya.

## drop

**Tipe:** method DataFrame

**Untuk apa:** membuang baris atau kolom. `axis=1` / `columns=` untuk kolom. Default tidak inplace.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nama": ["A"], "tmp": [1], "nilai": [88]})
print(df.drop(columns=["tmp"]))
print(df.drop(index=[0]))
```

**Yang terjadi:**

- Tanpa `tmp`: kolom `nama`, `nilai`.
- `drop(index=[0])`: tabel kosong (baris satu-satunya dibuang).
- `df` asli masih utuh.

**Biasanya digabungkan dengan:** buang kolom ID, `dropna`.

**Jangan:** `df.drop("tmp")` tanpa `axis`/`columns` — itu mencari **label baris** `tmp`. `KeyError`.

## reset_index

**Tipe:** method

**Untuk apa:** mengubah indeks jadi kolom biasa, lalu indeks baru 0..n-1. Setelah `groupby`, hampir selalu kamu `reset_index` supaya hasilnya tabel datar.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70]}, index=["Haikal", "Siti"])
print(df.reset_index())
print(df.reset_index(drop=True))
```

**Yang terjadi:**

- Default: kolom `index` (nama) + `nilai`.
- `drop=True`: nama dibuang, sisa kolom `nilai` dengan indeks 0,1.

**Biasanya digabungkan dengan:** `groupby`, `sort_values`.

**Jangan:** `reset_index` berulang tanpa `drop` — muncul `index`, `index_1`, `level_0`.

## set_index

**Tipe:** method

**Untuk apa:** memakai kolom sebagai indeks. Enak untuk `loc` menurut NIM atau tanggal.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nim": ["2101", "2102"], "nilai": [88, 70]})
df2 = df.set_index("nim")
print(df2)
print(df2.loc["2102"])
```

**Yang terjadi:**

- Indeks `nim`, kolom tersisa `nilai`.
- `loc["2102"]` → 70.

**Biasanya digabungkan dengan:** `loc`, join pada indeks.

**Jangan:** `set_index` kolom yang tidak unik lalu `loc` satu label — dapat banyak baris tanpa peringatan keras.

## astype

**Tipe:** method Series/DataFrame

**Untuk apa:** mengubah dtype kolom. Sering `astype({"nilai": "int64"})` atau `"category"` untuk kolom berulang.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": ["88", "70"], "sks": [3.0, 3.0]})
df = df.astype({"nilai": int, "sks": int})
print(df.dtypes)
```

**Yang terjadi:**

- Kedua kolom jadi integer.
- `"88"` berhasil karena isi numerik murni.

**Biasanya digabungkan dengan:** `to_numeric(errors="coerce")` jika ada sampah `"-"`.

**Jangan:** `astype(int)` pada kolom ada `NaN`. Error. Pakai `Int64` nullable atau drop/fill dulu.

## copy

**Tipe:** method

**Untuk apa:** salinan eksplisit. Mengurangi SettingWithCopyWarning saat kamu potong lalu ubah.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70, 91]})
potong = df[df["nilai"] >= 80].copy()
potong["nilai"] = potong["nilai"] + 1
print(df)
print(potong)
```

**Yang terjadi:**

- `df` asli tetap 88, 70, 91.
- `potong` hanya dua baris, nilainya +1.

**Biasanya digabungkan dengan:** filter, pipeline aman.

**Jangan:** `df2 = df` lalu ubah `df2`. Itu nama lain untuk objek yang sama (kecuali kamu `copy`).

## sample

**Tipe:** method

**Untuk apa:** ambil baris acak. `n` jumlah, `frac` proporsi, `random_state` supaya hasilnya bisa diulang di laporan.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nama": list("ABCDE"), "nilai": [1, 2, 3, 4, 5]})
print(df.sample(n=2, random_state=0))
print(df.sample(frac=0.4, random_state=0))
```

**Yang terjadi:**

- Dua baris acak, sama setiap kali karena `random_state=0`.
- `frac=0.4` dari 5 baris → 2 baris.

**Biasanya digabungkan dengan:** cek data, split acak kasar.

**Jangan:** `sample` tanpa `random_state` di tugas yang harus direproduksi dosen.

## assign singkat

**Tipe:** method DataFrame (pengantar; lengkap di file 07)

**Untuk apa:** menambah kolom baru, mengembalikan DataFrame baru. Enak dirantai.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70]})
print(df.assign(lulus=lambda x: x["nilai"] >= 70))
```

**Yang terjadi:**

- Kolom `lulus`: `True`, `True` (70 ≥ 70).
- `df` asli tanpa kolom itu.

**Biasanya digabungkan dengan:** filter, `groupby`.

**Jangan:** `df.assign(nilai=df["nilai"] + 1)` lalu mengira in-place. Assign ulang: `df = df.assign(...)`.

---

Filter, groupby, merge, dan data hilang di [07-pandas-filter-groupby-merge.md](07-pandas-filter-groupby-merge.md).
