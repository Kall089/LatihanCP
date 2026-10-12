# 08 — matplotlib dan seaborn

[← 07 Filter/groupby](07-pandas-filter-groupby-merge.md) · [Indeks](README.md) · [Lanjut 09 →](09-requests-datetime-regex.md)

Grafik adalah cara paling jujur menunjukkan pola. matplotlib adalah mesin dasar. seaborn duduk di atasnya: tema lebih rapi, fungsi statistik (`countplot`, `heatmap`) lebih pendek.

```bash
python -m pip install matplotlib seaborn
```

Contoh di bawah **menyimpan PNG** ke file `_plot_...png` lalu menghapusnya. Di notebook, ganti `savefig` dengan `plt.show()` atau biarkan sel menampilkan figure. Jangan lupa `plt.close()` di skrip agar memori tidak menumpuk.

## Daftar isi

- [plt.plot](#pltplot)
- [plt.bar](#pltbar)
- [plt.hist](#plthist)
- [plt.scatter](#pltscatter)
- [plt.xlabel ylabel title](#pltxlabel-ylabel-title)
- [plt.legend](#pltlegend)
- [plt.savefig](#pltsavefig)
- [fig ax](#fig-ax)
- [plt.subplots](#pltsubplots)
- [xticks](#xticks)
- [grid](#grid)
- [figsize](#figsize)
- [color](#color)
- [sns.set_theme](#snsset_theme)
- [sns.countplot](#snscountplot)
- [sns.barplot](#snsbarplot)
- [sns.histplot](#snshistplot)
- [sns.scatterplot](#snsscatterplot)
- [sns.lineplot](#snslineplot)
- [sns.boxplot](#snsboxplot)
- [sns.heatmap](#snsheatmap)

## plt.plot

**Tipe:** fungsi matplotlib (`pyplot`)

**Untuk apa:** garis yang menghubungkan titik berurutan. Cocok nilai per minggu, running average, dua deret dibandingkan. Bukan untuk kategori tak berurut — itu tugas `bar`.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

minggu = [1, 2, 3, 4]
nilai = [70, 75, 80, 78]
plt.plot(minggu, nilai, marker="o")
plt.xlabel("Minggu")
plt.ylabel("Nilai")
plt.title("Perkembangan kuis")
path = Path("_plot_line.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("tersimpan", path, "ukuran", path.stat().st_size)
path.unlink()
```

**Yang terjadi:**

- Empat titik dihubungkan garis, tiap titik ada marker lingkaran.
- Label sumbu dan judul tertulis di figure.
- `savefig` menulis PNG; `st_size` > 0 menandakan file tidak kosong.
- `close` menutup figure; `unlink` membersihkan percobaan.

**Biasanya digabungkan dengan:** `legend` untuk banyak garis, pandas `df.plot`.

**Jangan:** `plot` kategori `["Web", "Basis"]` sebagai sumbu x numerik tersembunyi 0,1 tanpa `xticks`. Pakai `bar`.

## plt.bar

**Tipe:** fungsi matplotlib

**Untuk apa:** batang untuk membandingkan kategori: rata-rata per MK, jumlah mahasiswa per kelas. Tinggi batang = nilai.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

mk = ["Web", "Basis", "Jaringan"]
rata = [77.6, 75.5, 81.0]
plt.bar(mk, rata)
plt.ylabel("Rata-rata")
plt.title("Nilai per mata kuliah")
path = Path("_plot_bar.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("ok", path.exists())
path.unlink()
```

**Yang terjadi:**

- Tiga batang, tinggi sesuai `rata`.
- Sumbu x memuat nama MK.
- File tercipta (`exists` True) lalu dihapus.

**Biasanya digabungkan dengan:** `groupby.mean()`, `xticks(rotation=30)` jika nama panjang.

**Jangan:** terlalu banyak kategori (30+). Batang tidak terbaca. Sort dulu, ambil top 10, atau pakai bar horizontal `barh`.

## plt.hist

**Tipe:** fungsi matplotlib

**Untuk apa:** histogram: membagi angka dike dalam keranjang (bin), menghitung frekuensi. Menjawab “sebaran nilai seperti apa?”, bukan “rata-rata berapa?”.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

nilai = [55, 60, 70, 70, 75, 80, 80, 80, 90, 95]
plt.hist(nilai, bins=5, edgecolor="black")
plt.xlabel("Nilai")
plt.ylabel("Jumlah")
path = Path("_plot_hist.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("bins=5")
path.unlink()
```

**Yang terjadi:**

- 10 angka dimasukkan ke 5 bin.
- Sumbu y adalah hitungan, bukan nilai itu sendiri.
- `edgecolor` membuat batas bin kelihatan.

**Biasanya digabungkan dengan:** `describe`, seaborn `histplot` + KDE.

**Jangan:** terlalu sedikit atau terlalu banyak bin. `bins=2` menyesatkan; `bins=100` pada 10 data juga menyesatkan.

## plt.scatter

**Tipe:** fungsi matplotlib

**Untuk apa:** titik lepas untuk hubungan dua angka: uts vs uas, jam belajar vs nilai. Mencari pola “naik bersama” atau outlier.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

uts = [60, 70, 80, 90, 50]
uas = [65, 72, 88, 85, 40]
plt.scatter(uts, uas)
plt.xlabel("UTS")
plt.ylabel("UAS")
plt.title("UTS vs UAS")
path = Path("_plot_scatter.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("n titik", len(uts))
path.unlink()
```

**Yang terjadi:**

- Lima titik; (50,40) terlihat lebih rendah (outlier kasar).
- Tidak ada garis penghubung (beda dengan `plot`).

**Biasanya digabungkan dengan:** `alpha=0.5` jika titik bertumpuk, `sns.scatterplot` + hue.

**Jangan:** `scatter` lalu menarik kesimpulan sebab-akibat. Korelasi bukan penyebab.

## plt.xlabel ylabel title

**Tipe:** fungsi pyplot (anotasi)

**Untuk apa:** menamai sumbu dan judul. Grafik tanpa label adalah hiasan. Tulis satuan jika ada (`Nilai (0-100)`).

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

plt.plot([1, 2, 3], [70, 80, 75])
plt.xlabel("Pertemuan ke-")
plt.ylabel("Rata-rata kuis")
plt.title("Kelas Pemrograman Web")
path = Path("_plot_label.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("label lengkap")
path.unlink()
```

**Yang terjadi:**

- Judul di atas, x di bawah, y di kiri (vertikal).
- PNG memuat teks itu.

**Biasanya digabungkan dengan:** `legend`, `tight_layout` / `bbox_inches="tight"`.

**Jangan:** judul yang mengulang isi sumbu (`Plot of y vs x`). Tulis klaim singkat: “Rata-rata kuis naik sampai minggu 2”.

## plt.legend

**Tipe:** fungsi pyplot

**Untuk apa:** menjelaskan beberapa deret di satu sumbu. Setiap `plot(..., label="...")` lalu `legend()`.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

x = [1, 2, 3, 4]
plt.plot(x, [70, 75, 80, 78], label="Kelas A")
plt.plot(x, [65, 68, 72, 80], label="Kelas B")
plt.legend()
path = Path("_plot_legend.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("dua garis")
path.unlink()
```

**Yang terjadi:**

- Dua garis warna berbeda.
- Kotak legend memuat “Kelas A” dan “Kelas B”.

**Biasanya digabungkan dengan:** `label=`, `loc="best"` / `"lower right"`.

**Jangan:** `legend()` tanpa `label`. Kotak kosong atau memakai nama seri `0`, `1`.

## plt.savefig

**Tipe:** fungsi pyplot

**Untuk apa:** menulis figure ke file (PNG, PDF, SVG). Di skrip tanpa GUI, ini cara utama “melihat” grafik. `dpi` mengatur ketajaman, `bbox_inches="tight"` memotong pinggir kosong dan menyelamatkan label yang terpotong.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

plt.bar(["A", "B"], [3, 5])
path = Path("_plot_save.png")
plt.savefig(path, dpi=120, bbox_inches="tight")
plt.close()
print(path.suffix, path.stat().st_size > 0)
path.unlink()
```

**Yang terjadi:**

- File `.png` tercipta, ukurannya lebih dari 0 byte → `True`.

**Biasanya digabungkan dengan:** laporan Markdown `![](_plot.png)`, tugas PDF.

**Jangan:** `savefig` setelah `close()`. Figure sudah hilang, file kosong/error. Urutan: gambar → save → close.

## fig ax

**Tipe:** objek `Figure` dan `Axes`

**Untuk apa:** gaya eksplisit: `fig` adalah kanvas, `ax` adalah satu area gambar. Lebih rapi daripada `plt.` global saat banyak subplot atau saat membungkus fungsi.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

fig, ax = plt.subplots()
ax.plot([1, 2, 3], [70, 80, 75], marker="o")
ax.set_xlabel("Minggu")
ax.set_ylabel("Nilai")
ax.set_title("Pakai Axes")
path = Path("_plot_ax.png")
fig.savefig(path, bbox_inches="tight")
plt.close(fig)
print("fig+ax")
path.unlink()
```

**Yang terjadi:**

- Satu axes menggambar garis.
- Method-nya `set_xlabel`, bukan `plt.xlabel`.
- `fig.savefig` menyimpan kanvas itu.

**Biasanya digabungkan dengan:** `subplots(1, 2)`, seaborn `ax=ax`.

**Jangan:** mencampur `plt.plot` dan `ax.plot` pada figure berbeda lalu `savefig` yang salah. Pilih satu gaya per fungsi.

## plt.subplots

**Tipe:** fungsi pyplot

**Untuk apa:** membuat beberapa axes dalam satu figure: `nrows`, `ncols`. Hasil `axs` adalah array jika lebih dari satu.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

fig, axs = plt.subplots(1, 2, figsize=(8, 3))
axs[0].bar(["Web", "Basis"], [80, 70])
axs[0].set_title("Rata-rata")
axs[1].hist([60, 70, 70, 80, 90], bins=3)
axs[1].set_title("Sebaran")
fig.tight_layout()
path = Path("_plot_sub.png")
fig.savefig(path, bbox_inches="tight")
plt.close(fig)
print("dua panel")
path.unlink()
```

**Yang terjadi:**

- Panel kiri batang, kanan hist.
- `tight_layout` mengurangi teks bertabrakan.
- Satu file PNG memuat keduanya.

**Biasanya digabungkan dengan:** laporan “ringkas + sebaran”, `sharey=True`.

**Jangan:** `subplots(2)` mengira 2 kolom. Argumen pertama adalah `nrows`. Tulis `subplots(1, 2)`.

## xticks

**Tipe:** fungsi / method Axes

**Untuk apa:** mengatur posisi dan teks tick sumbu x. Memutar label panjang, atau memasang nama kategori.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

nama = ["Pemrograman Web", "Basis Data", "Jaringan Komputer"]
plt.bar(range(len(nama)), [80, 70, 85])
plt.xticks(range(len(nama)), nama, rotation=25, ha="right")
path = Path("_plot_xticks.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("label miring")
path.unlink()
```

**Yang terjadi:**

- Batang di posisi 0,1,2.
- Label diganti nama panjang, diputar 25 derajat supaya tidak tabrakan.

**Biasanya digabungkan dengan:** `bar`, `savefig(..., bbox_inches="tight")`.

**Jangan:** `xticks` teks tanpa `range` posisi yang selaras. Tick dan label harus sama panjang.

## grid

**Tipe:** fungsi / method Axes

**Untuk apa:** garis bantu horizontal/vertikal agar tinggi batang lebih mudah dibaca. Jangan sampai lebih ramai dari data.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

plt.plot([1, 2, 3], [70, 80, 75])
plt.grid(True, axis="y", linestyle="--", alpha=0.5)
path = Path("_plot_grid.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("grid y")
path.unlink()
```

**Yang terjadi:**

- Garis putus-putus horizontal, transparan 0.5.
- Sumbu x tidak penuh garis (hanya `axis="y"`).

**Biasanya digabungkan dengan:** `bar`, tema seaborn.

**Jangan:** grid + warna mencolok + marker besar. Grafik jadi poster 2003.

## figsize

**Tipe:** parameter figure (inci)

**Untuk apa:** lebar × tinggi dalam inci. Default kira-kira `(6.4, 4.8)`. Perbesar jika banyak kategori atau subplot.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

fig, ax = plt.subplots(figsize=(4, 3))
ax.plot([1, 2, 3], [1, 4, 2])
path = Path("_plot_size.png")
fig.savefig(path, dpi=100)
plt.close(fig)
print("lebar px kira-kira", 4 * 100)
path.unlink()
```

**Yang terjadi:**

- Figure 4×3 inci, dpi 100 → sekitar 400×300 piksel (plus margin).
- File lebih kecil daripada figsize 12 inci.

**Biasanya digabungkan dengan:** `subplots`, `sns.set_theme`.

**Jangan:** `figsize=(400, 300)` mengira piksel. Itu 400 **inci**. File raksasa / RAM habis.

## color

**Tipe:** parameter seniman plot

**Untuk apa:** menentukan warna garis/batang/titik. Bisa nama (`"steelblue"`), hex (`"#1f77b4"`), atau tuple RGB 0–1.

**Contoh implementasi:**

```python
import matplotlib.pyplot as plt
from pathlib import Path

plt.bar(["Lulus", "Tidak"], [8, 2], color=["#2ca02c", "#d62728"])
path = Path("_plot_color.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("hijau-merah")
path.unlink()
```

**Yang terjadi:**

- Batang lulus hijau, tidak lulus merah.
- Hex dikenali matplotlib.

**Biasanya digabungkan dengan:** `hue` seaborn (lebih sistematis), palet `tab10`.

**Jangan:** merah-hijau sebagai satu-satunya pembeda jika grafik bisa jadi abu-abu cetak / buta warna. Tambah pola atau label angka.

## sns.set_theme

**Tipe:** fungsi seaborn

**Untuk apa:** mengatur gaya global: background, grid, palet, font. Panggil sekali di awal notebook.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
from pathlib import Path

sns.set_theme(style="whitegrid", context="talk")
plt.plot([1, 2, 3], [70, 80, 75])
path = Path("_plot_theme.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
sns.set_theme()  # kembali default wajar
print("tema whitegrid")
path.unlink()
```

**Yang terjadi:**

- Grid lembut, font `talk` lebih besar (cocok slide).
- Reset `set_theme()` supaya contoh berikutnya tidak mewarisi font raksasa.

**Biasanya digabungkan dengan:** semua plot seaborn/matplotlib setelahnya.

**Jangan:** memanggil `set_theme` di dalam loop. Cukup sekali.

## sns.countplot

**Tipe:** fungsi seaborn

**Untuk apa:** menghitung frekuensi kategori dan langsung menggambar batang. Pengganti `value_counts` + `bar` dalam satu langkah.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({"mk": ["Web", "Web", "Basis", "Web", "Jaringan", "Basis"]})
ax = sns.countplot(data=df, x="mk")
ax.set_title("Jumlah entri per MK")
path = Path("_plot_count.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print(df["mk"].value_counts().to_dict())
path.unlink()
```

**Yang terjadi:**

- Batang Web tertinggi (3), Basis 2, Jaringan 1.
- `value_counts` di print memverifikasi angka yang sama.

**Biasanya digabungkan dengan:** `hue` (mis. lulus/tidak), `order=` untuk urut manual.

**Jangan:** `countplot(y="nilai")` pada kolom numerik kontinu. Itu 100 kategori. Pakai `histplot`.

## sns.barplot

**Tipe:** fungsi seaborn

**Untuk apa:** batang **agregat** (default mean) plus interval kepercayaan. Bedanya dengan `countplot`: di sini ada `y` numerik.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({
    "mk": ["Web", "Web", "Basis", "Basis"],
    "nilai": [80, 90, 70, 60],
})
sns.barplot(data=df, x="mk", y="nilai", errorbar=None)
path = Path("_plot_barplot.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("mean Web", df.loc[df["mk"] == "Web", "nilai"].mean())
path.unlink()
```

**Yang terjadi:**

- Tinggi batang Web = 85, Basis = 65.
- `errorbar=None` mematikan garis error (untuk n kecil sering menyesatkan).
- Print memverifikasi 85.0.

**Biasanya digabungkan dengan:** `groupby.mean()` sebagai cek, `hue="angkatan"`.

**Jangan:** mengira `barplot` menghitung jumlah. Jumlah = `countplot` atau `y` yang sudah di-`size`.

## sns.histplot

**Tipe:** fungsi seaborn

**Untuk apa:** histogram modern, bisa overlay KDE (`kde=True`), bisa `hue` kelompok.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({"nilai": [55, 60, 70, 70, 80, 80, 80, 90]})
sns.histplot(data=df, x="nilai", bins=4, kde=True)
path = Path("_plot_histplot.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("n", len(df))
path.unlink()
```

**Yang terjadi:**

- Empat bin + kurva KDE halus di atas hist.
- `n=8` sesuai data.

**Biasanya digabungkan dengan:** `describe`, banding dua kelas `hue="kelas"`.

**Jangan:** KDE pada data 5 titik lalu percaya “puncak distribusi”. Terlalu sedikit.

## sns.scatterplot

**Tipe:** fungsi seaborn

**Untuk apa:** scatter dengan `hue`, `style`, `size` untuk dimensi tambahan tanpa subplot.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({
    "uts": [60, 70, 80, 90],
    "uas": [65, 72, 88, 85],
    "mk": ["Web", "Web", "Basis", "Basis"],
})
sns.scatterplot(data=df, x="uts", y="uas", hue="mk")
path = Path("_plot_scat.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("hue mk")
path.unlink()
```

**Yang terjadi:**

- Empat titik, warna menurut MK, legend otomatis.

**Biasanya digabungkan dengan:** `alpha`, `relplot` untuk facet.

**Jangan:** 8 kategori `hue` dengan warna mirip. Gabung kategori langka jadi “lainnya”.

## sns.lineplot

**Tipe:** fungsi seaborn

**Untuk apa:** garis agregat: default merata-rata `y` per `x` jika ada beberapa observasi, plus pita error. Untuk satu deret sudah di-agregat, hasilnya mirip `plt.plot`.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({
    "minggu": [1, 1, 2, 2, 3, 3],
    "nilai": [70, 80, 75, 85, 78, 88],
    "kelas": ["A", "B", "A", "B", "A", "B"],
})
sns.lineplot(data=df, x="minggu", y="nilai", hue="kelas", marker="o")
path = Path("_plot_lineplot.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print("dua kelas")
path.unlink()
```

**Yang terjadi:**

- Dua garis A dan B naik perlahan.
- Karena satu nilai per (minggu, kelas), tidak ada agregat tersembunyi.

**Biasanya digabungkan dengan:** time series pandas, `hue`.

**Jangan:** `lineplot` pada data mentah banyak duplikat `x` tanpa sadar bahwa seaborn **merata-rata**. Kalau ingin semua titik, `estimator=None` atau `scatterplot`.

## sns.boxplot

**Tipe:** fungsi seaborn

**Untuk apa:** ringkasan sebaran: median, kuartil, whisker, titik outlier. Lebih jujur daripada hanya mean.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({
    "mk": ["Web"] * 5 + ["Basis"] * 5,
    "nilai": [60, 70, 75, 80, 95, 40, 65, 70, 72, 73],
})
sns.boxplot(data=df, x="mk", y="nilai")
path = Path("_plot_box.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
print(df.groupby("mk")["nilai"].median().to_dict())
path.unlink()
```

**Yang terjadi:**

- Dua kotak; Web cenderung lebih tinggi, Basis punya ekor bawah (40).
- Print median untuk cek: Web 75, Basis 70.

**Biasanya digabungkan dengan:** `describe`, `percentile`.

**Jangan:** boxplot n=2. Kotak tidak bermakna. Tulis titik saja.

## sns.heatmap

**Tipe:** fungsi seaborn

**Untuk apa:** mewarnai matriks: korelasi antar kolom, pivot jumlah, confusion matrix. `annot=True` menulis angka di sel.

**Contoh implementasi:**

```python
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

df = pd.DataFrame({
    "uts": [60, 70, 80, 90, 50],
    "uas": [65, 72, 88, 85, 40],
    "hadir": [8, 9, 10, 10, 4],
})
korelasi = df.corr(numeric_only=True)
print(korelasi.round(2))
sns.heatmap(korelasi, annot=True, fmt=".2f", cmap="vlag", center=0)
path = Path("_plot_heat.png")
plt.savefig(path, bbox_inches="tight")
plt.close()
path.unlink()
```

**Yang terjadi:**

- `corr` 3×3; diagonal 1.00.
- UTS–UAS dan hadir biasanya positif di data ini (50/40/4 menarik ke bawah bersama).
- Heatmap menuliskan angka dua desimal, cmap `vlag` (negatif–positif), `center=0`.

**Biasanya digabungkan dengan:** `pivot_table`, `annot`, `fmt="d"` untuk hitungan integer.

**Jangan:** heatmap 50×50 tanpa `xticklabels` diatur. Tidak terbaca. Pilih subset kolom.

---

HTTP, tanggal, dan regex di [09-requests-datetime-regex.md](09-requests-datetime-regex.md).
