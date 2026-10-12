# Cheatsheet Python

[← Daftar panduan](README.md) · [Ensiklopedia Python](ensiklopedia/python/README.md)

Python mengolah **data dan langkah** di komputermu: menghitung, membaca CSV, merapikan tabel, lalu menggambar grafik. Browser tidak menjalankan file `.py`. Kamu menjalankan skrip lewat terminal, Jupyter, atau editor.

Versi cepat ini cukup untuk tugas harian. Detail tiap fungsi ada di [ensiklopedia/python](ensiklopedia/python/README.md).

## Daftar isi

- [Persiapan](#persiapan)
- [Tipe dan variabel](#tipe-dan-variabel)
- [Kondisi dan perulangan](#kondisi-dan-perulangan)
- [Fungsi dan modul](#fungsi-dan-modul)
- [List, dict, tuple, dan set](#list-dict-tuple-dan-set)
- [File, JSON, dan CSV](#file-json-dan-csv)
- [NumPy: array](#numpy-array)
- [NumPy: operasi dan statistik](#numpy-operasi-dan-statistik)
- [Pandas: Series dan DataFrame](#pandas-series-dan-dataframe)
- [Pandas: filter, groupby, merge](#pandas-filter-groupby-merge)
- [Grafik singkat](#grafik-singkat)
- [Requests dan waktu](#requests-dan-waktu)
- [Kesalahan umum](#kesalahan-umum)

## Persiapan

**Untuk apa:** menjalankan skrip tanpa mengotori paket sistem. Pakai `python3` dan lingkungan virtual.

```bash
python3 --version
python3 -m venv .venv
source .venv/bin/activate          # Windows: .venv\Scripts\activate
python -m pip install -U pip
python -m pip install numpy pandas matplotlib seaborn requests
```

Buat file `latihan.py`, lalu jalankan `python latihan.py`. Jupyter opsional: `python -m pip install jupyter` lalu `jupyter notebook`.

**Contoh implementasi:** di folder tugas, buat `.venv`, aktifkan, install `pandas`, lalu cetak `import pandas as pd; print(pd.__version__)`. Jika versi tampil, lingkungan siap.

**Biasanya digabungkan dengan:** semua bab di bawah. Cara install lengkap: [README ensiklopedia](ensiklopedia/python/README.md).

## Tipe dan variabel

**Untuk apa:** memberi nama pada data agar bisa dipakai lagi.

```python
nama = "Haikal"          # str: teks
jumlah = 2               # int: bilangan bulat
harga = 45000.0          # float: pecahan
tersedia = True          # bool: benar/salah
kosong = None            # belum ada nilai

print(f"{nama} membeli {jumlah} barang")
print(type(harga))       # <class 'float'>
```

Python tidak menulis tipe di depan variabel. Tipe mengikuti nilai. String pakai tanda kutip. `f"..."` menyisipkan nilai ke teks.

**Contoh implementasi:** simpan `nama`, `jumlah`, dan `harga`, lalu hitung `total = jumlah * harga` dan cetak dengan `f"Total: {total}"`.

**Biasanya digabungkan dengan:** kondisi, fungsi, dan kolom DataFrame. Rincian tiap tipe: [01 — tipe dan variabel](ensiklopedia/python/01-dasar-tipe-variabel.md).

## Kondisi dan perulangan

**Untuk apa:** memilih jalan, lalu mengulang langkah per item.

```python
stok = 5
produk = ["Buku", "Pensil", "Tas"]

if stok > 0:
    print("Bisa dibeli")
elif stok == 0:
    print("Habis")
else:
    print("Data stok aneh")

for nama in produk:
    print(nama)

i = 0
while i < 3:
    print(i)
    i += 1
```

Indentasi (spasi di depan baris) wajib; Python memakai ini sebagai blok. `==` membandingkan, `=` menugaskan. `for` paling nyaman untuk list.

**Contoh implementasi:** loop daftar harga `[45000, 5000, 90000]`, cetak `"mahal"` jika di atas 10000, selain itu `"murah"`.

**Biasanya digabungkan dengan:** filter Pandas dan peringatan stok. Kontrol lengkap: [02 — kontrol dan fungsi](ensiklopedia/python/02-kontrol-fungsi-modul.md).

## Fungsi dan modul

**Untuk apa:** membungkus langkah yang dipakai berkali-kali, lalu membaginya ke file lain.

```python
def format_rupiah(nilai: int) -> str:
    return f"Rp{nilai:,}".replace(",", ".")

def total_belanja(harga, jumlah=1):
    return harga * jumlah

print(format_rupiah(total_belanja(45000, 2)))
```

Di `util.py` kamu menulis fungsi, lalu di `latihan.py` menulis `from util import format_rupiah`. Parameter adalah masukan. `return` adalah keluaran. `jumlah=1` dipakai jika argumen tidak dikirim.

**Contoh implementasi:** pindahkan `format_rupiah` ke `util.py`, impor di `latihan.py`, lalu format tiga harga dari list.

**Biasanya digabungkan dengan:** `pathlib`, Pandas, dan skrip analisis. Modul dan `import`: [02 — kontrol dan fungsi](ensiklopedia/python/02-kontrol-fungsi-modul.md).

## List, dict, tuple, dan set

**Untuk apa:** menyimpan daftar, data beratribut, nilai tetap, atau kumpulan unik.

```python
nama = ["Buku", "Pensil", "Tas"]          # list: bisa diubah
nama.append("Penghapus")

produk = {"nama": "Buku", "harga": 45000}  # dict: kunci → nilai
print(produk["nama"])

koordinat = (1, 3)                         # tuple: tidak diganti isinya
unik = {"Buku", "Buku", "Tas"}             # set: "Buku" hanya sekali

tersedia = [n for n in nama if n != "Pensil"]
```

Akses list pakai indeks mulai 0. Akses dict pakai kunci. List comprehension membuat list baru dari loop singkat.

**Contoh implementasi:** list of dict `[{"nama": "Buku", "stok": 3}, ...]`, lalu buat list nama yang `stok > 0`.

**Biasanya digabungkan dengan:** JSON, CSV, dan DataFrame. Tiap koleksi: [01 — tipe dan variabel](ensiklopedia/python/01-dasar-tipe-variabel.md).

## File, JSON, dan CSV

**Untuk apa:** menyimpan atau membaca data di disk.

```python
from pathlib import Path
import json
import csv

folder = Path("data")
folder.mkdir(exist_ok=True)

Path("data/catatan.txt").write_text("Halo toko\n", encoding="utf-8")
teks = Path("data/catatan.txt").read_text(encoding="utf-8")

produk = {"nama": "Buku", "harga": 45000}
Path("data/produk.json").write_text(json.dumps(produk, ensure_ascii=False, indent=2))
kembali = json.loads(Path("data/produk.json").read_text(encoding="utf-8"))

with Path("data/produk.csv").open("w", newline="", encoding="utf-8") as f:
    penulis = csv.DictWriter(f, fieldnames=["nama", "harga"])
    penulis.writeheader()
    penulis.writerow({"nama": "Buku", "harga": 45000})
```

`Path` lebih nyaman daripada string path mentah. `encoding="utf-8"` menjaga huruf Indonesia. Untuk tabel besar, lanjut ke Pandas, bukan `csv` manual.

**Contoh implementasi:** tulis tiga baris produk ke `data/produk.csv`, baca lagi, lalu cetak kolom `nama`.

**Biasanya digabungkan dengan:** `read_csv` Pandas. File, JSON, CSV: [03 — file dan format](ensiklopedia/python/03-file-pathlib-json-csv.md).

## NumPy: array

**Untuk apa:** menghitung banyak angka sekaligus, lebih cepat daripada loop list biasa.

```python
import numpy as np

harga = np.array([45000, 5000, 90000], dtype=np.int64)
print(harga.shape)        # (3,) — satu dimensi, 3 angka
print(harga.dtype)        # int64
print(harga[0], harga[-1])
print(harga[harga > 10000])

tabel = np.array([[1, 2, 3], [4, 5, 6]])
print(tabel[0, 1])        # 2 — baris 0, kolom 1
print(tabel[:, 0])        # kolom pertama
```

`ndarray` punya `shape` (ukuran) dan `dtype` (jenis angka). Slicing memakai `awal:akhir`. Broadcast: operasi ke seluruh array tanpa loop Python.

**Contoh implementasi:** buat array stok `[3, 0, 2]`, ambil yang lebih dari 0, lalu kalikan `harga * stok` untuk nilai persediaan.

**Biasanya digabungkan dengan:** Pandas (kolom numerik) dan Matplotlib. Array dan indexing: [04 — NumPy array](ensiklopedia/python/04-numpy-array-tipe.md).

## NumPy: operasi dan statistik

**Untuk apa:** jumlah, rata-rata, posisi nilai ekstrem, dan aljabar kecil.

```python
import numpy as np

harga = np.array([45000.0, 5000.0, 90000.0])
print(harga.sum(), harga.mean(), harga.std())
print(harga.min(), harga.max(), harga.argmax())  # argmax: indeks termahal
print(np.clip(harga, 0, 50000))                  # potong ke rentang

a = np.array([[1, 2], [3, 4]])
print(a.T)                   # transpose
print(a.reshape(4))          # ratakan
print(np.matmul(a, a))       # perkalian matriks
print(np.where(harga > 10000, "mahal", "murah"))
```

`axis=0` menghitung per kolom, `axis=1` per baris, pada array 2D. `where` memilih nilai berdasarkan syarat.

**Contoh implementasi:** matriks penjualan 2 toko × 3 produk, hitung `sum(axis=1)` untuk total per toko, lalu `argmax` toko terlaris.

**Biasanya digabungkan dengan:** `describe()` Pandas. Operasi lengkap: [05 — NumPy statistik](ensiklopedia/python/05-numpy-operasi-statistik.md).

## Pandas: Series dan DataFrame

**Untuk apa:** mengolah tabel (baris × kolom), seperti spreadsheet di kode.

```python
import pandas as pd

df = pd.DataFrame(
    {
        "nama": ["Buku", "Pensil", "Tas"],
        "harga": [45000, 5000, 90000],
        "stok": [3, 0, 2],
    }
)

print(df.head())
print(df.info())
print(df.describe())
print(df["nama"])            # Series: satu kolom
print(df.loc[0, "harga"])    # label baris/kolom
print(df.iloc[0, 1])         # posisi numerik
```

`DataFrame` adalah tabel. `Series` adalah satu kolom. `loc` memakai nama, `iloc` memakai nomor. `head()` melihat cuplikan, `info()` melihat tipe, `describe()` ringkasan angka.

**Contoh implementasi:** baca `data/produk.csv` dengan `pd.read_csv(...)`, lalu `print(df[["nama", "harga"]])`.

**Biasanya digabungkan dengan:** file CSV dan groupby. Dasar tabel: [06 — Series dan DataFrame](ensiklopedia/python/06-pandas-series-dataframe.md).

## Pandas: filter, groupby, merge

**Untuk apa:** menyaring baris, meringkas kelompok, dan menggabung tabel.

```python
import pandas as pd

df = pd.DataFrame(
    {
        "nama": ["Buku", "Pensil", "Tas", "Buku"],
        "kategori": ["Alat", "Alat", "Tas", "Alat"],
        "harga": [45000, 5000, 90000, 47000],
        "stok": [3, 0, 2, 1],
    }
)

ada = df.loc[df["stok"] > 0]
ringkas = df.groupby("kategori", as_index=False)["harga"].mean()

diskon = pd.DataFrame({"nama": ["Buku", "Tas"], "potong": [5000, 10000]})
gabung = df.merge(diskon, on="nama", how="left")
print(ada, ringkas, gabung)
```

Filter memakai syarat di dalam `[]` atau `loc`. `groupby` + agregasi (`mean`, `sum`, `count`) merangkum. `merge` menyambung seperti join SQL. `how="left"` menjaga semua baris kiri.

**Contoh implementasi:** dari CSV penjualan, `groupby("hari")["total"].sum()`, lalu tampilkan 3 hari terlaris dengan `sort_values(..., ascending=False).head(3)`.

**Biasanya digabungkan dengan:** grafik dan resep bersih data. Filter sampai merge: [07 — filter dan groupby](ensiklopedia/python/07-pandas-filter-groupby-merge.md).

## Grafik singkat

**Untuk apa:** melihat pola yang sulit dibaca dari angka mentah.

```python
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.DataFrame({"nama": ["Buku", "Pensil", "Tas"], "harga": [45, 5, 90]})

plt.figure()
plt.bar(df["nama"], df["harga"])
plt.xlabel("Produk")
plt.ylabel("Harga (ribu)")
plt.title("Harga produk")
plt.tight_layout()
plt.savefig("harga.png")
# plt.show()  # jika di Jupyter atau jendela GUI

sns.countplot(data=df, x="nama")
```

Satu `figure` untuk satu gambar. Label sumbu wajib agar grafik bisa dibaca orang lain. Seaborn nyaman untuk hitung kategori dan heatmap.

**Contoh implementasi:** setelah groupby total harian, `plt.plot(ringkas["hari"], ringkas["total"])` lalu simpan `penjualan.png`.

**Biasanya digabungkan dengan:** DataFrame yang sudah dibersihkan. Plot lengkap: [08 — matplotlib dan seaborn](ensiklopedia/python/08-matplotlib-seaborn.md).

## Requests dan waktu

**Untuk apa:** mengambil data dari internet dan mengolah tanggal.

```python
from datetime import datetime, timedelta
import re
import requests

sekarang = datetime.now()
besok = sekarang + timedelta(days=1)
print(sekarang.strftime("%Y-%m-%d"))

teks = "Hubungi 0812-0000-1111"
print(re.findall(r"\d{4}", teks))

# respons = requests.get("https://httpbin.org/get", timeout=10)
# print(respons.status_code, respons.json())
```

`timeout` mencegah skrip menunggu tanpa batas. Cek `status_code` sebelum `json()`. Regex (`re`) mencari pola teks, bukan mengganti Pandas.

**Contoh implementasi:** `GET` ke API latihan, ambil list JSON, `pd.DataFrame(data)`, lalu simpan CSV.

**Biasanya digabungkan dengan:** Pandas setelah data sampai. HTTP, tanggal, regex: [09 — requests dan waktu](ensiklopedia/python/09-requests-datetime-regex.md).

## Kesalahan umum

- **`ModuleNotFoundError`:** paket belum diinstall, atau venv belum aktif.
- **`SettingWithCopyWarning`:** ubah lewat `df.loc[syarat, "kolom"] = nilai`, jangan rantai filter lalu assign.
- **Loop list lambat:** untuk angka banyak, pindah ke NumPy/Pandas.
- **`KeyError`:** nama kolom salah; cek `df.columns`.
- **Path file tidak ketemu:** jalankan skrip dari folder yang benar, atau pakai `Path(__file__).parent`.
- **Grafik kosong:** data setelah filter jadi 0 baris; `print(df.shape)` dulu.

Resep utuh (baca CSV → bersih → groupby → grafik): [10 — resep dan kesalahan](ensiklopedia/python/10-resep-analisis-kesalahan.md).

Latihan: buat CSV 8 baris penjualan, hitung total per kategori, gambar batang, simpan PNG.

## Peta ensiklopedia

| Ingin… | Buka |
| --- | --- |
| Tipe dasar | [01](ensiklopedia/python/01-dasar-tipe-variabel.md) |
| `if`, loop, fungsi | [02](ensiklopedia/python/02-kontrol-fungsi-modul.md) |
| File / JSON / CSV | [03](ensiklopedia/python/03-file-pathlib-json-csv.md) |
| `ndarray`, slice | [04](ensiklopedia/python/04-numpy-array-tipe.md) |
| `mean`, `matmul` | [05](ensiklopedia/python/05-numpy-operasi-statistik.md) |
| DataFrame | [06](ensiklopedia/python/06-pandas-series-dataframe.md) |
| filter / groupby | [07](ensiklopedia/python/07-pandas-filter-groupby-merge.md) |
| grafik | [08](ensiklopedia/python/08-matplotlib-seaborn.md) |
| HTTP / tanggal | [09](ensiklopedia/python/09-requests-datetime-regex.md) |
| resep analisis | [10](ensiklopedia/python/10-resep-analisis-kesalahan.md) |

Referensi: [Python docs](https://docs.python.org/3/) · [NumPy](https://numpy.org/doc/stable/) · [Pandas](https://pandas.pydata.org/docs/).
