# 07 — pandas: filter, groupby, merge, data hilang

[← 06 Series/DataFrame](06-pandas-series-dataframe.md) · [Indeks](README.md) · [Lanjut 08 →](08-matplotlib-seaborn.md)

Setelah tabel berdiri, pekerjaan harian: saring baris, buat kolom baru, ringkas per kelompok, gabung dua tabel, dan bereskan lubang. Ini bab yang paling sering kamu buka saat tugas analisis.

## Daftar isi

- [filter boolean](#filter-boolean)
- [query](#query)
- [isin](#isin)
- [between](#between)
- [assign](#assign)
- [apply](#apply)
- [map](#map)
- [groupby](#groupby)
- [agg](#agg)
- [size dan count](#size-dan-count)
- [transform](#transform)
- [merge](#merge)
- [join](#join)
- [concat](#concat)
- [isna](#isna)
- [dropna](#dropna)
- [fillna](#fillna)
- [duplicated](#duplicated)
- [drop_duplicates](#drop_duplicates)
- [pivot_table](#pivot_table)
- [melt](#melt)
- [str accessor](#str-accessor)
- [dt accessor](#dt-accessor)

## filter boolean

**Tipe:** indexing DataFrame dengan Series bool

**Untuk apa:** mengambil baris yang syaratnya benar. Tulis kondisi pada kolom, bungkus `df[...]`. Beberapa syarat memakai `&` `|` `~` plus kurung, bukan `and`/`or`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "nama": ["Haikal", "Siti", "Budi", "Ana"],
    "mk": ["Web", "Web", "Basis", "Web"],
    "nilai": [88, 70, 91, 55],
})
lulus_web = df[(df["mk"] == "Web") & (df["nilai"] >= 70)]
print(lulus_web)
print(df[~(df["nilai"] >= 70)])
```

**Yang terjadi:**

- Syarat Web dan nilai ≥ 70: Haikal 88, Siti 70.
- `~` membalik: yang tidak lulus → Ana 55.

**Biasanya digabungkan dengan:** `loc`, `assign`, `value_counts` pada hasil saring.

**Jangan:** `df[df["mk"] == "Web" and df["nilai"] >= 70]`. `and` memaksa kebenaran satu nilai. `ValueError: ambiguous`.

## query

**Tipe:** method DataFrame

**Untuk apa:** filter dengan string ekspresi, kadang lebih mudah dibaca. Nama kolom jadi variabel di dalam string. Kolom berkspasi pakai backtick.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"mk": ["Web", "Basis"], "nilai": [88, 55]})
print(df.query("mk == 'Web' and nilai >= 70"))
ambang = 80
print(df.query("nilai >= @ambang"))
```

**Yang terjadi:**

- Query pertama: hanya baris Web 88.
- `@ambang` merujuk variabel Python `80` → tetap baris 88.

**Biasanya digabungkan dengan:** eksplorasi cepat di notebook.

**Jangan:** menyisipkan input user ke string `query` tanpa sanitasi (meski tugas kuliah). Untuk kode tahan lama, filter boolean lebih eksplisit.

## isin

**Tipe:** method Series

**Untuk apa:** cek keanggotaan di daftar. Pengganti banyak `==` yang di-`|`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Basis", "Jaringan", "AI"],
    "nilai": [88, 70, 60, 90],
})
inti = ["Web", "Basis"]
print(df[df["mk"].isin(inti)])
```

**Yang terjadi:**

- Hanya Web dan Basis yang lolos (dua baris pertama).

**Biasanya digabungkan dengan:** `~df["mk"].isin(...)` untuk buang kategori, `unique`.

**Jangan:** `df["mk"] in inti`. Itu cek apakah **seluruh Series** jadi anggota list, bukan per baris. `ValueError` / selalu salah.

## between

**Tipe:** method Series

**Untuk apa:** rentang inklusif default: `bawah <= x <= atas`. Enak untuk nilai ujian, umur, harga.

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series([55, 70, 88, 100])
print(s.between(70, 90))
print(s[s.between(70, 90)])
```

**Yang terjadi:**

- Mask: False, True, True, False.
- Nilai tersaring: 70 dan 88.

**Biasanya digabungkan dengan:** filter DataFrame `df[df["nilai"].between(70, 85)]`.

**Jangan:** `between(90, 70)` terbalik. Hasilnya semua False. Urutkan min, max.

## assign

**Tipe:** method DataFrame

**Untuk apa:** menambah atau menimpa kolom, mengembalikan salinan. Bisa beberapa kolom sekaligus. Lambda menerima DataFrame yang sedang dibangun (kolom baru bisa dipakai kolom berikutnya di versi modern, hati-hati urutan).

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nilai": [88, 70, 55]})
out = df.assign(
    lulus=lambda x: x["nilai"] >= 70,
    predikat=lambda x: x["nilai"].map(lambda n: "A" if n >= 85 else "B" if n >= 70 else "C"),
)
print(out)
```

**Yang terjadi:**

- Kolom `lulus`: True, True, False.
- `predikat`: A, B, C.
- `df` asli tanpa kolom baru.

**Biasanya digabungkan dengan:** filter, `groupby`, rantai method.

**Jangan:** `df.assign(lulus=df["nilai"] >= 70)` pada potongan yang bukan copy lalu bingung SettingWithCopy. Lebih aman rantai dari sumber.

## apply

**Tipe:** method Series/DataFrame

**Untuk apa:** menjalankan fungsi Python per baris atau per kolom. Fleksibel, sering **lambat**. Pakai vektor (`+`, `str`, `np.where`) jika bisa.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"uts": [80, 70], "uas": [90, 60]})

def akhir(row):
    return 0.4 * row["uts"] + 0.6 * row["uas"]

print(df.apply(akhir, axis=1))
print(0.4 * df["uts"] + 0.6 * df["uas"])
```

**Yang terjadi:**

- `apply` axis=1: per baris, hasil Series dua nilai: `86.0` dan `64.0`.
- Versi vektor menghasilkan angka yang sama, lebih cepat.

**Biasanya digabungkan dengan:** logika yang tidak bisa vektor, parsing aneh.

**Jangan:** `apply` untuk `lambda x: x + 1` pada kolom angka. Tulis `df["nilai"] + 1`.

## map

**Tipe:** method Series

**Untuk apa:** memetakan tiap nilai lewat dict atau fungsi. Enak mengganti kode jadi label.

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series(["A", "B", "A", "C"])
print(s.map({"A": 4, "B": 3, "C": 2}))
print(s.map(lambda x: x.lower()))
```

**Yang terjadi:**

- Dict: `4, 3, 4, 2`.
- Fungsi: `a, b, a, c`.
- Kunci yang tidak ada di dict jadi `NaN`.

**Biasanya digabungkan dengan:** predikat huruf, encoding kategori sederhana.

**Jangan:** menukar `map` DataFrame (di versi baru ada, maknanya beda). Untuk tabel, tentukan kolom: `df["huruf"].map(...)`.

## groupby

**Tipe:** method DataFrame (obyek GroupBy)

**Untuk apa:** memecah baris menurut kunci, lalu menghitung per kelompok. Pola split-apply-combine. Setelah `groupby` kamu hampir selalu `agg` / `mean` / `size`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis", "Basis", "Web"],
    "nilai": [88, 70, 91, 60, 75],
})
print(df.groupby("mk")["nilai"].mean())
print(df.groupby("mk")["nilai"].mean().reset_index())
```

**Yang terjadi:**

- Series indeks `mk`: Basis rata-rata `(91+60)/2 = 75.5`, Web `(88+70+75)/3 = 77.666...`.
- `reset_index()` membuat kolom `mk` dan `nilai` biasa.

**Biasanya digabungkan dengan:** `agg`, `merge` hasil ringkas ke tabel asli, grafik batang.

**Jangan:** `groupby` lalu `print(g)` mengira tabel sudah jadi. Itu objek GroupBy; belum dihitung sampai kamu `mean`/`agg`.

## agg

**Tipe:** method GroupBy / DataFrame

**Untuk apa:** beberapa ringkasan sekaligus: `mean`, `median`, `count`, fungsi sendiri. Nama kolom hasil bisa di-tuple (`named aggregation`).

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis"],
    "nilai": [88, 70, 91],
    "sks": [3, 3, 3],
})
print(
    df.groupby("mk").agg(
        rata=("nilai", "mean"),
        maks=("nilai", "max"),
        n=("nilai", "count"),
    )
)
```

**Yang terjadi:**

- Web: rata 79, maks 88, n 2.
- Basis: rata 91, maks 91, n 1.

**Biasanya digabungkan dengan:** `reset_index`, `sort_values("rata")`.

**Jangan:** `agg("mean", "max")` tanpa struktur. Kirim list `["mean", "max"]` atau named agg seperti di atas.

## size dan count

**Tipe:** method GroupBy

**Untuk apa:** `size` menghitung baris per kelompok, termasuk yang NaN di kolom lain. `count` menghitung non-null per kolom. `value_counts` sering lebih pendek untuk satu kolom.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis", "Web"],
    "nilai": [88, None, 91, 70],
})
print(df.groupby("mk").size())
print(df.groupby("mk")["nilai"].count())
```

**Yang terjadi:**

- `size`: Web 3, Basis 1 (semua baris).
- `count` pada `nilai`: Web 2 (satu None tidak dihitung), Basis 1.

**Biasanya digabungkan dengan:** cek kelengkapan data, pie/bar jumlah mahasiswa.

**Jangan:** menukar `count` dan `size` saat ada missing. Laporan jumlah mahasiswa bisa selisih.

## transform

**Tipe:** method GroupBy

**Untuk apa:** menghitung per kelompok lalu **menempelkan hasil ke setiap baris asli** (shape tetap). Cocok untuk “nilai minus rata-rata kelasnya”.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis", "Basis"],
    "nilai": [80, 100, 70, 90],
})
df = df.assign(rata_mk=df.groupby("mk")["nilai"].transform("mean"))
df = df.assign(delta=df["nilai"] - df["rata_mk"])
print(df)
```

**Yang terjadi:**

- Rata Web = 90, Basis = 80. Setiap baris dapat rata kelompoknya.
- `delta`: −10, +10, −10, +10.

**Biasanya digabungkan dengan:** z-score per kelompok, isi missing dengan median kelompok.

**Jangan:** menukar `transform` dengan `agg`. `agg` meruntuhkan jadi satu baris per kelompok.

## merge

**Tipe:** fungsi / method `pd.merge`

**Untuk apa:** gabung dua tabel menurut kolom kunci (seperti JOIN SQL). `how`: `inner`, `left`, `right`, `outer`. Ini alat relasi paling penting di pandas.

**Contoh implementasi:**

```python
import pandas as pd

nilai = pd.DataFrame({"nim": ["2101", "2102", "2103"], "nilai": [88, 70, 91]})
mhs = pd.DataFrame({"nim": ["2101", "2102", "2104"], "nama": ["Haikal", "Siti", "Ana"]})
print(pd.merge(nilai, mhs, on="nim", how="inner"))
print(pd.merge(nilai, mhs, on="nim", how="left"))
```

**Yang terjadi:**

- `inner`: hanya NIM yang ada di kedua tabel → 2101, 2102.
- `left`: semua baris `nilai`, 2103 namanya `NaN` (tidak ada di `mhs`).

**Biasanya digabungkan dengan:** `validate="one_to_one"`, cek `shape` sesudah merge.

**Jangan:** merge tanpa sadar kunci duplikat. Relasi many-to-many **menggandakan baris**. Cek `df["nim"].duplicated()` sebelum merge.

## join

**Tipe:** method DataFrame

**Untuk apa:** merge memakai **indeks** (default), atau `on` kolom kiri vs indeks kanan. Lebih pendek jika kamu sudah `set_index`.

**Contoh implementasi:**

```python
import pandas as pd

kiri = pd.DataFrame({"nilai": [88, 70]}, index=["2101", "2102"])
kanan = pd.DataFrame({"nama": ["Haikal", "Siti"]}, index=["2101", "2102"])
print(kiri.join(kanan))
```

**Yang terjadi:**

- Satu tabel: indeks NIM, kolom `nilai` dan `nama`.

**Biasanya digabungkan dengan:** `set_index`, time series.

**Jangan:** `join` pada kolom biasa tanpa `on`/`set_index` lalu kaget kunci tidak cocok. Untuk kolom, `merge` lebih jelas.

## concat

**Tipe:** fungsi `pd.concat`

**Untuk apa:** menumpuk tabel secara vertikal (baris) atau horizontal (kolom). Bukan join menurut kunci; itu tempel.

**Contoh implementasi:**

```python
import pandas as pd

a = pd.DataFrame({"nama": ["Haikal"], "nilai": [88]})
b = pd.DataFrame({"nama": ["Siti"], "nilai": [70]})
print(pd.concat([a, b], ignore_index=True))
print(pd.concat([a, b], axis=1))
```

**Yang terjadi:**

- `axis=0` + `ignore_index`: dua baris, indeks 0,1.
- `axis=1`: kolom bergandengan; nama kolom `nama`/`nilai` **duplikat**, baris menyejajarkan indeks (keduanya 0) jadi satu baris lebar.

**Biasanya digabungkan dengan:** banyak CSV `Path.glob`, `reset_index`.

**Jangan:** `concat` dua tabel beda skema tanpa cek. Kolom yang tidak ada diisi `NaN`.

## isna

**Tipe:** method / fungsi (`isna` = `isnull`)

**Untuk apa:** mask `True` di sel hilang (`NaN`, `None`, `NaT`). `notna` kebalikannya. `isna().sum()` = jumlah lubang per kolom.

**Contoh implementasi:**

```python
import pandas as pd
import numpy as np

df = pd.DataFrame({"nilai": [88, np.nan, 70], "nama": ["A", None, "C"]})
print(df.isna())
print(df.isna().sum())
```

**Yang terjadi:**

- Tabel bool: `nilai` True di baris 1, `nama` True di baris 1.
- `sum`: masing-masing kolom 1 missing.

**Biasanya digabungkan dengan:** `dropna`, `fillna`, `info`.

**Jangan:** `df["nilai"] == np.nan`. Selalu False. Pakai `isna`.

## dropna

**Tipe:** method

**Untuk apa:** membuang baris (`axis=0`) atau kolom yang mengandung NA. `subset` membatasi kolom yang dicek. `how="all"` hanya buang jika semua kosong.

**Contoh implementasi:**

```python
import pandas as pd
import numpy as np

df = pd.DataFrame({"nama": ["A", "B", None], "nilai": [88, np.nan, 70]})
print(df.dropna())
print(df.dropna(subset=["nama"]))
```

**Yang terjadi:**

- `dropna()`: sisa hanya baris A 88 (baris lain ada NA).
- `subset=["nama"]`: buang baris tanpa nama; baris B (nilai NaN) tetap.

**Biasanya digabungkan dengan:** cek `len` sebelum/sesudah, laporan “dibuang n baris”.

**Jangan:** `dropna` diam-diam di tengah analisis sampai N menyusut tanpa dicatat.

## fillna

**Tipe:** method

**Untuk apa:** mengisi lubang: konstanta, median, `ffill`/`bfill`. Lebih baik isi yang masuk akal daripada membuang semua baris.

**Contoh implementasi:**

```python
import pandas as pd
import numpy as np

s = pd.Series([80, np.nan, 90, np.nan])
print(s.fillna(s.median()))
print(s.fillna(method=None))
print(s.ffill())
```

**Yang terjadi:**

- Median dari 80 dan 90 = 85; dua NaN jadi 85.
- `ffill`: 80, **80**, 90, **90** (isi dari atas).

**Biasanya digabungkan dengan:** `groupby.transform("median")` untuk isi per kelompok.

**Jangan:** `fillna(0)` pada kolom yang 0 bermakna (nilai ujian). Nol palsu menggeser rata-rata.

## duplicated

**Tipe:** method

**Untuk apa:** mask baris yang mengulang. Default: kemunculan pertama `False`, sisanya `True`. `keep=False` menandai semua anggota grup duplikat.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nim": ["2101", "2101", "2102"], "nilai": [88, 88, 70]})
print(df.duplicated())
print(df.duplicated(subset=["nim"], keep=False))
```

**Yang terjadi:**

- Duplikat penuh: baris 1 True (sama dengan baris 0).
- `subset=["nim"], keep=False`: baris 0 dan 1 True (NIM sama), 2102 False.

**Biasanya digabungkan dengan:** `drop_duplicates`, audit merge.

**Jangan:** cek duplikat hanya seluruh baris padahal kunci bisnisnya NIM. Dua baris nilai beda, NIM sama, `duplicated()` tanpa subset bisa False.

## drop_duplicates

**Tipe:** method

**Untuk apa:** menyisakan satu baris per kunci. `keep="first"` / `"last"`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nim": ["2101", "2101", "2102"], "nilai": [80, 88, 70]})
print(df.drop_duplicates(subset=["nim"], keep="last"))
```

**Yang terjadi:**

- Untuk 2101 disimpan baris nilai 88 (terakhir), plus 2102.

**Biasanya digabungkan dengan:** `sort_values("tanggal")` dulu, lalu `keep="last"` = data terbaru.

**Jangan:** drop tanpa `subset` jika hanya sebagian kolom yang boleh unik.

## pivot_table

**Tipe:** fungsi / method

**Untuk apa:** ringkasan 2d: baris × kolom, nilai diaggregasi. Excel pivot. Default `mean`.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis", "Basis"],
    "sesi": ["uts", "uas", "uts", "uas"],
    "nilai": [80, 90, 70, 60],
})
print(pd.pivot_table(df, index="mk", columns="sesi", values="nilai", aggfunc="mean"))
```

**Yang terjadi:**

- Tabel: index Web/Basis, kolom uts/uas, isi 80/90 dan 70/60.

**Biasanya digabungkan dengan:** seaborn `heatmap`, `fill_value=0`.

**Jangan:** `pivot` (bukan `pivot_table`) saat ada duplikat pasangan index×columns. `pivot` menolak duplikat; `pivot_table` mengaggregasi.

## melt

**Tipe:** fungsi / method

**Untuk apa:** kebalikan pivot: kolom lebar jadi panjang (`id_vars` tetap, sisanya `variable`/`value`). Enak untuk seaborn yang suka format long.

**Contoh implementasi:**

```python
import pandas as pd

df = pd.DataFrame({"nama": ["Haikal", "Siti"], "uts": [80, 70], "uas": [90, 85]})
print(df.melt(id_vars="nama", value_vars=["uts", "uas"], var_name="sesi", value_name="nilai"))
```

**Yang terjadi:**

- Empat baris: tiap orang × tiap sesi, kolom `sesi` dan `nilai`.

**Biasanya digabungkan dengan:** `groupby`, `sns.barplot`.

**Jangan:** `melt` tanpa `id_vars` sehingga identitas baris hilang.

## str accessor

**Tipe:** accessor Series (`str`)

**Untuk apa:** method string vektor: `strip`, `lower`, `contains`, `replace`, `slice`. Hanya untuk kolom teks / object / string dtype.

**Contoh implementasi:**

```python
import pandas as pd

s = pd.Series(["  Web ", "basis", "WEB"])
print(s.str.strip().str.lower())
print(s.str.contains("web", case=False))
```

**Yang terjadi:**

- Normalisasi: `web`, `basis`, `web`.
- `contains` case-insensitive: True, False, True.

**Biasanya digabungkan dengan:** filter, `extract` regex (file 09), rapikan CSV kotor.

**Jangan:** `df["nama"].strip()`. Series tidak punya `strip` langsung. Wajib `.str.strip()`.

## dt accessor

**Tipe:** accessor Series datetime

**Untuk apa:** ambil `year`, `month`, `day`, `day_name` dari kolom `datetime64`. Kolom harus sudah datetime (`to_datetime`).

**Contoh implementasi:**

```python
import pandas as pd

s = pd.to_datetime(pd.Series(["2026-09-01", "2026-10-15"]))
print(s.dt.month)
print(s.dt.day_name())
```

**Yang terjadi:**

- Bulan: 9 dan 10.
- Nama hari (lokal English default): Tuesday, Thursday (tanggal contoh).

**Biasanya digabungkan dengan:** `groupby(s.dt.to_period("M"))`, time series plot.

**Jangan:** `dt` pada kolom yang masih string. `AttributeError`. `pd.to_datetime` dulu, `errors="coerce"`.

---

Grafik di [08-matplotlib-seaborn.md](08-matplotlib-seaborn.md).
