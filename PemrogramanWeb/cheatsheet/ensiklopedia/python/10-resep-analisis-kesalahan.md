# 10 — Resep analisis dan kesalahan umum

[← 09 HTTP/tanggal/regex](09-requests-datetime-regex.md) · [Indeks](README.md)

Bab ini merangkai potongan 01–09 jadi alur kerja: **baca CSV → bersihkan → groupby → grafik**. Setelah itu katalog error yang paling sering merusak tugas kuliah, masing-masing dengan contoh yang bisa dijalankan.

Tidak ada klaim “semua package PyPI”. Stack-nya tetap: Python dasar, file, NumPy, pandas, matplotlib/seaborn, requests.

## Daftar isi

- [Resep: baca CSV → bersihkan → groupby → grafik](#resep-baca-csv-bersihkan-groupby-grafik)
- [Resep: dua CSV di-merge lalu ringkas](#resep-dua-csv-di-merge-lalu-ringkas)
- [Resep: NumPy cepat tanpa pandas](#resep-numpy-cepat-tanpa-pandas)
- [Resep: ambil JSON API jadi tabel](#resep-ambil-json-api-jadi-tabel)
- [ModuleNotFoundError](#modulenotfounderror)
- [FileNotFoundError](#filenotfounderror)
- [UnicodeDecodeError](#unicodedecodeerror)
- [KeyError kolom](#keyerror-kolom)
- [SettingWithCopyWarning](#settingwithcopywarning)
- [ValueError broadcast](#valueerror-broadcast)
- [Truthy array ambigu](#truthy-array-ambigu)
- [and pada mask](#and-pada-mask)
- [merge menggandakan baris](#merge-menggandakan-baris)
- [dtype object tersembunyi](#dtype-object-tersembunyi)
- [NaN bandel](#nan-bandel)
- [std pandas vs NumPy](#std-pandas-vs-numpy)
- [loc vs iloc tertukar](#loc-vs-iloc-tertukar)
- [JSONDecodeError](#jsondecodeerror)
- [timeout requests](#timeout-requests)
- [grafik kosong / file 0 byte](#grafik-kosong--file-0-byte)
- [Checklist sebelum kumpul tugas](#checklist-sebelum-kumpul-tugas)

## Resep: baca CSV → bersihkan → groupby → grafik

**Tipe:** resep alur (bukan satu fungsi)

**Untuk apa:** pola tugas analisis paling umum. Kamu dapat file nilai, harus merapikan huruf/spasi/angka, menghitung rata-rata per kelas atau per MK, lalu menggambar batang. Setiap langkah kecil supaya error mudah dicari.

**Contoh implementasi:**

```python
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

path = Path("_resep_nilai.csv")
path.write_text(
    "nama,mk,nilai\n"
    "Haikal,Web,88\n"
    "Siti, Web,70\n"
    "Budi,Basis,91\n"
    "Ana,Web,-\n"
    "Dedi,Basis,60\n"
    "Siti,Web,70\n",
    encoding="utf-8",
)

df = pd.read_csv(path)
print("1. mentah")
print(df)
print(df.dtypes)

df = df.copy()
df.columns = [c.strip().lower() for c in df.columns]
df["mk"] = df["mk"].astype(str).str.strip()
df["nilai"] = pd.to_numeric(df["nilai"], errors="coerce")
print("2. setelah tipe dan strip")
print(df)

print("3. duplikat penuh", int(df.duplicated().sum()))
df = df.drop_duplicates()

print("4. missing nilai", int(df["nilai"].isna().sum()))
df = df.dropna(subset=["nilai"])

ringkas = (
    df.groupby("mk", as_index=False)
    .agg(rata=("nilai", "mean"), n=("nilai", "size"))
    .sort_values("rata", ascending=False)
)
print("5. groupby")
print(ringkas)

sns.set_theme(style="whitegrid")
ax = sns.barplot(data=ringkas, x="mk", y="rata")
ax.set_xlabel("Mata kuliah")
ax.set_ylabel("Rata-rata nilai")
ax.set_title("Rata-rata nilai per MK")
for i, row in enumerate(ringkas.itertuples(index=False)):
    ax.text(i, row.rata + 0.5, f"n={row.n}", ha="center")

out = Path("_resep_bar.png")
plt.savefig(out, bbox_inches="tight")
plt.close()
print("6. grafik", out, "byte", out.stat().st_size)

out.unlink()
path.unlink()
```

**Yang terjadi:**

- **Langkah 1.** CSV terbacat; kolom `nilai` mungkin `object` karena ada `-`.
- **Langkah 2.** Nama kolom dirapikan. ` Web` jadi `Web`. `-` menjadi `NaN` lewat `to_numeric(..., errors="coerce")`.
- **Langkah 3.** Baris Siti Web 70 muncul dua kali; `drop_duplicates` menyisakan satu.
- **Langkah 4.** Ana tanpa nilai dibuang. Jangan diam-diam: cetak jumlah missing.
- **Langkah 5.** `groupby` menghasilkan rata-rata dan n per MK. `as_index=False` biar `mk` tetap kolom (enak untuk seaborn).
- **Langkah 6.** `barplot` memakai tabel ringkas, bukan data mentah (jadi tinggi batang = rata-rata yang kamu hitung). Label `n=` mencegah grafik berbohong soal sampel kecil.
- File percobaan dihapus di akhir.

**Biasanya digabungkan dengan:** `info`, `merge` data mahasiswa, `heatmap` korelasi jika kolom lebih banyak.

**Jangan:** langsung `sns.barplot(data=df_mentah, x="mk", y="nilai")` tanpa cek missing/duplikat, lalu kaget angka tidak sama dengan `groupby` di laporan (seaborn merata-rata sendiri, termasuk kejutan NA).

## Resep: dua CSV di-merge lalu ringkas

**Tipe:** resep alur

**Untuk apa:** nilai ada di satu file, nama/angkatan di file lain. Gabungkan pada kunci `nim`, cek baris menggandakan, baru `groupby`.

**Contoh implementasi:**

```python
from pathlib import Path

import pandas as pd

p_nilai = Path("_resep_a.csv")
p_mhs = Path("_resep_b.csv")
p_nilai.write_text("nim,nilai\n2101,88\n2102,70\n2103,91\n", encoding="utf-8")
p_mhs.write_text("nim,nama,angkatan\n2101,Haikal,21\n2102,Siti,21\n2104,Ana,22\n", encoding="utf-8")

nilai = pd.read_csv(p_nilai, dtype={"nim": str})
mhs = pd.read_csv(p_mhs, dtype={"nim": str})
print("unik nim nilai", nilai["nim"].is_unique, "mhs", mhs["nim"].is_unique)

gabung = pd.merge(nilai, mhs, on="nim", how="left", validate="one_to_one")
print(gabung)
print("tanpa nama", gabung["nama"].isna().sum())

per_ang = gabung.dropna(subset=["angkatan"]).groupby("angkatan")["nilai"].mean()
print(per_ang)

p_nilai.unlink()
p_mhs.unlink()
```

**Yang terjadi:**

- `dtype={"nim": str}` mencegah `02101` jadi angka `2101`.
- Kedua kunci unik → `validate="one_to_one"` lolos.
- `left` menjaga 2103; namanya `NaN` (tidak ada di master mahasiswa).
- Rata-rata angkatan hanya yang punya `angkatan` (2103 terbuang di `dropna`).

**Biasanya digabungkan dengan:** `how="inner"` jika baris yatim memang tidak relevan, `indicator=True` untuk audit.

**Jangan:** `merge` tanpa `validate` saat NIM duplikat. Satu mahasiswa jadi empat baris, rata-rata semu.

## Resep: NumPy cepat tanpa pandas

**Tipe:** resep alur

**Untuk apa:** data sudah murni angka (hasil eksperimen, matriks). Tidak perlu nama kolom. Lebih sedikit overhead.

**Contoh implementasi:**

```python
import numpy as np

# 4 mahasiswa x 3 kuis
m = np.array([
    [70, 80, 90],
    [60, 65, 70],
    [90, 85, 95],
    [50, 55, 40],
], dtype=float)

print("rata per mhs", m.mean(axis=1))
print("rata per kuis", m.mean(axis=0))
print("tertinggi global", m.max(), "di", np.unravel_index(m.argmax(), m.shape))

z = (m - m.mean(axis=0)) / m.std(axis=0, ddof=0)
print("z-score kuis 0", z[:, 0].round(2))
print("clip 0-100", np.clip(m + 5, 0, 100))
```

**Yang terjadi:**

- `axis=1` merata per baris (mahasiswa).
- `axis=0` merata per kolom (kuis).
- `argmax` datar → `unravel_index` jadi (baris, kolom) nilai 95.
- Z-score: tiap kuis dikurangi mean kolom, dibagi std kolom (broadcast).
- `clip` memaksa tetap 0–100 setelah +5.

**Biasanya digabungkan dengan:** `matplotlib` `imshow` untuk matriks, pandas jika muncul label.

**Jangan:** `mean` tanpa `axis` lalu mengira itu per mahasiswa. Tanpa axis = satu angka untuk seluruh matriks.

## Resep: ambil JSON API jadi tabel

**Tipe:** resep alur

**Untuk apa:** endpoint mengembalikan list of dict. Kamu ubah jadi DataFrame, pilih kolom, konversi tanggal.

**Contoh implementasi:**

```python
import pandas as pd
import requests

try:
    r = requests.get("https://httpbin.org/json", timeout=10)
    r.raise_for_status()
    data = r.json()
    print("tipe akar", type(data), "kunci", list(data)[:6])
    df = pd.json_normalize(data)
    print(df.shape)
    print(df.columns.tolist()[:8])
except requests.RequestException as e:
    print("lewati demo jaringan:", type(e).__name__)
```

**Yang terjadi:**

- Akar biasanya `dict`.
- `json_normalize` meratakan kunci bersarang jadi kolom dengan titik (`slideshow.author`, dll. pada httpbin).
- `shape` 1 baris × N kolom (objek tunggal). Untuk list, `DataFrame(list_of_dict)` lebih langsung.
- Offline: pesan lewat, tidak merusak sisa file.

**Biasanya digabungkan dengan:** `params` pagination, `explode` jika ada list di sel.

**Jangan:** `pd.DataFrame(dict_bersarang)` tanpa `orient` — kolomnya jadi kunci tingkat atas, list jadi satu sel aneh.

## ModuleNotFoundError

**Tipe:** eksepsi impor

**Untuk apa:** Python tidak menemukan paket. Bukan berarti paket “rusak”; biasanya venv salah atau belum `pip install`.

**Contoh implementasi:**

```python
try:
    import paket_yang_tidak_ada  # noqa: F401
except ModuleNotFoundError as e:
    print("nama:", e.name)
    print("saran: python -m pip install numpy pandas matplotlib seaborn requests")
```

**Yang terjadi:**

- `e.name` adalah nama modul yang gagal.
- Pesan saran mengingatkan install lewat `python -m pip` (bukan `pip` acak).

**Biasanya digabungkan dengan:** `python -m pip show pandas`, cek `which python`.

**Jangan:** `pip install` di Python A lalu menjalankan `python3` Python B. Selalu `python -m pip`.

## FileNotFoundError

**Tipe:** eksepsi I/O

**Untuk apa:** path salah, atau folder kerja bukan yang kamu kira. `Path.cwd()` menyelamatkan.

**Contoh implementasi:**

```python
from pathlib import Path

print("cwd", Path.cwd())
try:
    Path("data/nilai.csv").read_text(encoding="utf-8")
except FileNotFoundError:
    print("tidak ketemu relatif terhadap cwd")
    print("coba", Path(__file__).resolve().parent / "data" / "nilai.csv")
```

**Yang terjadi:**

- `cwd` tercetak (folder dari mana kamu mengetik `python ...`).
- Baca gagal → saran path di samping file skrip, bukan cwd.

**Biasanya digabungkan dengan:** `Path.exists`, struktur tugas `data/`.

**Jangan:** hardcode `C:\Users\...` atau `/Users/nama/...` di tugas kelompok. Temanmu tidak punya path itu.

## UnicodeDecodeError

**Tipe:** eksepsi encoding

**Untuk apa:** file bukan UTF-8 (sering ekspor Excel Windows). Coba `utf-8-sig` atau `cp1252`, lalu simpan ulang UTF-8.

**Contoh implementasi:**

```python
from pathlib import Path

path = Path("_enc.csv")
path.write_bytes("nilai;satu\r\n".encode("cp1252"))
try:
    path.read_text(encoding="utf-8")
except UnicodeDecodeError as e:
    print("utf-8 gagal:", e.reason)
teks = path.read_text(encoding="cp1252")
print(teks.strip())
path.unlink()
```

**Yang terjadi:**

- File dibuat dengan encoding Windows.
- Baca UTF-8 gagal, alasan tercetak.
- Baca `cp1252` berhasil.

**Biasanya digabungkan dengan:** `pd.read_csv(..., encoding="utf-8-sig")`.

**Jangan:** `errors="ignore"` diam-diam. Huruf hilang, analisis tetap “sukses”.

## KeyError kolom

**Tipe:** eksepsi pandas / dict

**Untuk apa:** nama kolom tidak persis. Spasi, kapital, BOM `\ufeff` di header pertama.

**Contoh implementasi:**

```python
import pandas as pd
from pathlib import Path

path = Path("_bom.csv")
path.write_bytes(b"\xef\xbb\xbfNilai\n88\n")
df = pd.read_csv(path)
print("kolom mentah:", df.columns.tolist())
try:
    print(df["nilai"])
except KeyError:
    print("gagal kunci 'nilai'")
df.columns = [c.replace("\ufeff", "").strip().lower() for c in df.columns]
print(df["nilai"].iloc[0])
path.unlink()
```

**Yang terjadi:**

- Header bisa `'Nilai'` atau `'\ufeffNilai'`.
- `df["nilai"]` gagal.
- Setelah dinormalisasi, `88` terbaca.

**Biasanya digabungkan dengan:** `rename`, `read_csv(..., encoding="utf-8-sig")` yang membuang BOM.

**Jangan:** `df.nilai` pada kolom `nilai uts` (spasi). Attribute tidak jalan; pakai `df["nilai uts"]` atau rename dulu.

## SettingWithCopyWarning

**Tipe:** peringatan pandas

**Untuk apa:** kamu mengubah potongan yang mungkin view, bukan copy. Hasilnya kadang berubah, kadang tidak. Hilangkan dengan `.copy()` + `loc`.

**Contoh implementasi:**

```python
import pandas as pd
import warnings

df = pd.DataFrame({"nilai": [88, 70, 55], "mk": ["Web", "Web", "Basis"]})
view = df[df["mk"] == "Web"]
with warnings.catch_warnings(record=True) as w:
    warnings.simplefilter("always")
    view["nilai"] = view["nilai"] + 1
    print("peringatan?", any("Copy" in str(x.message) for x in w))

aman = df.loc[df["mk"] == "Web"].copy()
aman["nilai"] = aman["nilai"] + 1
print("asli", df["nilai"].tolist())
print("aman", aman["nilai"].tolist())
```

**Yang terjadi:**

- Assignment pada `view` sering memicu peringatan (tergantung versi).
- `df` asli bisa tidak berubah sesuai harapan.
- Pola `loc` + `copy` jelas: salinan terpisah, asli tetap.

**Biasanya digabungkan dengan:** filter, `assign` (mengembalikan baru).

**Jangan:** `df[df.mk=="Web"]["nilai"] = 0` (rantai `[][]`). Itu sumber klasik warning.

## ValueError broadcast

**Tipe:** eksepsi NumPy

**Untuk apa:** dua array tidak bisa disejajarkan. Cetak kedua `shape` sebelum panik.

**Contoh implementasi:**

```python
import numpy as np

a = np.ones((2, 3))
b = np.ones((2, 4))
try:
    print(a + b)
except ValueError as e:
    print("shape", a.shape, b.shape)
    print(e)
```

**Yang terjadi:**

- `(2,3)` vs `(2,4)` tidak broadcast.
- Pesan `operands could not be broadcast together`.

**Biasanya digabungkan dengan:** `reshape`, `newaxis`, cek `len`.

**Jangan:** `reshape` paksa sampai “muat” tanpa sadar urutan elemen sudah kacau.

## Truthy array ambigu

**Tipe:** eksepsi NumPy/pandas

**Untuk apa:** `if array:` tidak didefinisikan untuk lebih dari satu elemen. Pakai `any`/`all`/`empty`.

**Contoh implementasi:**

```python
import numpy as np

nilai = np.array([80, 70, 90])
try:
    if nilai:
        print("ya")
except ValueError as e:
    print("ambigu:", e)

print("ada yang >= 85?", np.any(nilai >= 85))
```

**Yang terjadi:**

- `if nilai` melempar `The truth value of an array is ambiguous`.
- `np.any` → `True` karena 90.

**Biasanya digabungkan dengan:** filter, assert.

**Jangan:** `if df:` untuk cek kosong. Pakai `if df.empty:`.

## and pada mask

**Tipe:** kesalahan operator

**Untuk apa:** mask kolom harus `&` `|` `~`, dikurung. `and` adalah operator Python untuk satu nilai kebenaran.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 55], "mk": ["Web", "Web"]})
try:
    df[(df["nilai"] >= 70) and (df["mk"] == "Web")]
except ValueError as e:
    print("and gagal:", str(e)[:50])
print(df[(df["nilai"] >= 70) & (df["mk"] == "Web")])
```

**Yang terjadi:**

- `and` error ambiguous.
- `&` berhasil: satu baris 88 Web.

**Biasanya digabungkan dengan:** `loc`, `query`.

**Jangan:** lupa kurung: `df["nilai"] >= 70 & df["mk"] == "Web"` dihitung sebagai `70 & df["mk"]` dulu (bitwise), hasil kacau.

## merge menggandakan baris

**Tipe:** jebakan relasi

**Untuk apa:** kunci kanan tidak unik. Setiap kecocokan dikalikan. `validate` dan `duplicated` adalah sabuk pengaman.

**Contoh implementasi:**

```python
import pandas as pd

kiri = pd.DataFrame({"nim": ["2101", "2102"], "nilai": [88, 70]})
kanan = pd.DataFrame({"nim": ["2101", "2101"], "mk": ["Web", "Basis"]})
print("sebelum", kiri.shape, kanan.shape)
print(pd.merge(kiri, kanan, on="nim", how="left"))
try:
    pd.merge(kiri, kanan, on="nim", how="left", validate="one_to_one")
except pd.errors.MergeError as e:
    print("validate menolak:", type(e).__name__)
```

**Yang terjadi:**

- Merge biasa: 2101 muncul dua baris (Web dan Basis), shape membesar.
- `validate="one_to_one"` melempar `MergeError` — lebih baik gagal daripada diam-diam salah.

**Biasanya digabungkan dengan:** `drop_duplicates`, `groupby` dulu di sisi kanan.

**Jangan:** percaya `shape` awal. Bandingkan `len` sebelum dan sesudah setiap merge.

## dtype object tersembunyi

**Tipe:** jebakan tipe

**Untuk apa:** kolom kelihatan angka, `mean` error atau mengabaikan. Cek `dtypes` dan sample `repr`.

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series(["88", "70", "91 "])
print(s.dtype)
try:
    print(s.mean())
except TypeError as e:
    print("mean gagal:", type(e).__name__)
print(pd.to_numeric(s.str.strip()).mean())
```

**Yang terjadi:**

- `dtype` object/string.
- `mean` gagal (atau di versi tertentu perilaku aneh).
- Setelah `strip` + `to_numeric`, rata-rata `(88+70+91)/3`.

**Biasanya digabungkan dengan:** `info`, `astype`.

**Jangan:** `replace(",", ".")` lupa pada desimal Eropa `"88,5"` sebelum `to_numeric`.

## NaN bandel

**Tipe:** jebakan missing

**Untuk apa:** `NaN != NaN`, `== np.nan` selalu False, `mean` NumPy jadi NaN. Gunakan `isna` / `nanmean`.

**Contoh implementasi:**

```python
import numpy as np
import pandas as pd

x = np.nan
print("x == x", x == x)
print(pd.isna(x), np.isnan(x))
a = np.array([80.0, np.nan, 90.0])
print("mean", np.mean(a), "nanmean", np.nanmean(a))
```

**Yang terjadi:**

- `x == x` → `False`.
- `isna`/`isnan` → `True`.
- `mean` → `nan`, `nanmean` → `85.0`.

**Biasanya digabungkan dengan:** `dropna`, `fillna`.

**Jangan:** `if nilai == None` pada sel pandas kosong. Itu sering `NaN`, bukan `None`.

## std pandas vs NumPy

**Tipe:** jebakan statistik

**Untuk apa:** default `ddof` berbeda. Laporan “std 12.9 vs 11.2” bisa keduanya benar.

**Contoh implementasi:**

```python
import numpy as np
import pandas as pd

nilai = [80.0, 70.0, 90.0, 60.0]
print("np default", np.std(nilai))
print("np ddof=1", np.std(nilai, ddof=1))
print("pd default", pd.Series(nilai).std())
```

**Yang terjadi:**

- NumPy default ≈ 11.18 (`ddof=0`).
- NumPy `ddof=1` dan pandas ≈ 12.91, saling cocok.

**Biasanya digabungkan dengan:** `describe`, tulis catatan kaki di laporan.

**Jangan:** menyalin angka std dari dua tool ke tabel yang sama tanpa menyebut rumus.

## loc vs iloc tertukar

**Tipe:** jebakan indexer

**Untuk apa:** `loc` label, `iloc` posisi. Setelah `sort_values`, baris pertama **bukan** indeks 0.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70, 91]}, index=[10, 20, 30])
urut = df.sort_values("nilai")
print(urut)
print("iloc[0]", urut.iloc[0]["nilai"])
print("loc[10]", urut.loc[10]["nilai"])
```

**Yang terjadi:**

- Setelah sort: 70 (idx 20), 88 (idx 10), 91 (idx 30).
- `iloc[0]` → 70 (paling kecil, posisi atas).
- `loc[10]` → 88 (label 10, bukan “baris ke-10”).

**Biasanya digabungkan dengan:** `reset_index`, top-k `nlargest`.

**Jangan:** `df.loc[0]` setelah filter yang menyisakan indeks asli 5, 9, 12. `KeyError`.

## JSONDecodeError

**Tipe:** eksepsi `json`

**Untuk apa:** tubuh bukan JSON: HTML error, file kosong, koma terakhir. Cetak `r.text[:200]` sebelum parse.

**Contoh implementasi:**

```python
import json

try:
    json.loads("<html>error</html>")
except json.JSONDecodeError as e:
    print("posisi", e.pos, "pesan", e.msg)
```

**Yang terjadi:**

- Parse gagal di dekat posisi 0.
- `msg` menjelaskan token tak terduga.

**Biasanya digabungkan dengan:** `raise_for_status`, cek `Content-Type`.

**Jangan:** `loads` dua kali pada objek yang sudah dict.

## timeout requests

**Tipe:** eksepsi jaringan

**Untuk apa:** server lambat atau dead. Tangkap `requests.Timeout`, beri pesan manusiawi.

**Contoh implementasi:**

```python
import requests

try:
    requests.get("https://httpbin.org/delay/5", timeout=1)
except requests.Timeout:
    print("server terlalu lama, coba lagi atau ganti URL")
```

**Yang terjadi:**

- Delay 5 detik vs timeout 1 detik → cabang Timeout.

**Biasanya digabungkan dengan:** retry 2–3 kali, backoff.

**Jangan:** retry tanpa batas pada 401 (salah kunci). Itu bukan timeout.

## grafik kosong / file 0 byte

**Tipe:** kesalahan alur matplotlib

**Untuk apa:** `savefig` setelah `close`, atau figure salah, atau data kosong. Cek `len(df)` dan urutan save.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

fig, ax = plt.subplots()
ax.bar(["Web"], [80])
path = Path("_kosong_demo.png")
fig.savefig(path, bbox_inches="tight")
plt.close(fig)
print("ukuran benar", path.stat().st_size)

path2 = Path("_setelah_close.png")
plt.savefig(path2)
plt.close()
print("setelah close tanpa figure aktif, size", path2.stat().st_size)

path.unlink()
path2.unlink(missing_ok=True)
```

**Yang terjadi:**

- File pertama punya ukuran wajar.
- `savefig` setelah figure ditutup membuat figure kosong baru — file aneh/kecil. Itulah gejala “PNG putih”.

**Biasanya digabungkan dengan:** `fig.savefig` eksplisit, cek `df.empty`.

**Jangan:** menumpuk `plot` di loop tanpa `clf`/`close` lalu kaget garis lama masih ada.

## Checklist sebelum kumpul tugas

**Tipe:** daftar periksa

**Untuk apa:** lima menit terakhir sebelum zip dikirim. Lebih murah daripada nilai potong karena path dan seed.

**Contoh implementasi:**

```python
from pathlib import Path

cek = {
    "ada venv atau requirements": True,
    "CSV relatif, bukan path absolut laptop": True,
    "random_state tertulis jika sample": True,
    "index=False saat to_csv": True,
    "grafik punya label sumbu": True,
    "jumlah baris sebelum/sesudah dropna tercatat": True,
}
for k, v in cek.items():
    print(("[x]" if v else "[ ]"), k)
print("folder kerja", Path.cwd())
```

**Yang terjadi:**

- Setiap butir tercetak `[x]`.
- Ganti `True` jadi `False` secara manual saat review jika butir belum kamu lakukan.
- `cwd` mengingatkan dari mana skrip dijalankan.

**Biasanya digabungkan dengan:** README singkat “cara jalankan: `python analisis.py`”.

**Jangan:** mengirim file `_contoh_*.csv` sisa ensiklopedia ini. Hapus sampah percobaan.

---

Kembali ke [peta folder](README.md). Urutan ulang jika perlu: [01](01-dasar-tipe-variabel.md) · [06 pandas](06-pandas-series-dataframe.md) · [07 olah](07-pandas-filter-groupby-merge.md) · [08 grafik](08-matplotlib-seaborn.md).
