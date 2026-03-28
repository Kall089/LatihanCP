# 📊 Day 1: Tipe Data & Struktur Dataset

**Bulan**: 1 — Foundation | **Minggu**: 1 — Data & Statistik Dasar  
**Estimasi Waktu**: 2–3 jam teori + 3–4 jam latihan = **5–7 jam total**

---

## 🎯 Learning Objectives

Setelah menyelesaikan Day 1, kamu akan:
- [ ] Membedakan 4 tipe data: Nominal, Ordinal, Discrete, Continuous
- [ ] Menentukan tipe data dengan domain knowledge (bukan hanya dtypes)
- [ ] Membuat Pandas DataFrame dari dictionary, list of dicts, dan CSV
- [ ] Menggunakan `.info()`, `.describe()`, `.dtypes`, `.shape`, `.value_counts()`
- [ ] Mengakses data dengan `.loc`, `.iloc`, dan boolean filtering
- [ ] Mengubah tipe data dengan `.astype()` dan `pd.CategoricalDtype`
- [ ] Mendeteksi inkonsistensi data secara sistematis
- [ ] Membuat EDA sederhana dengan visualisasi yang bermakna

---

## 📋 Prerequisites

- Python dasar: variabel, list, dict, loop, function
- Jupyter Notebook/Lab sudah terinstall
- Library: `numpy`, `pandas`, `matplotlib`, `seaborn`

```bash
pip install numpy pandas matplotlib seaborn jupyter
```

---

## 📁 Struktur Folder

```
Day-01 (Tipe Data & Struktur Dataset)/
├── teori/
│   └── Day_01_Teori_Lengkap.ipynb    ← Mulai di sini!
├── latihan/
│   ├── exercise_1.ipynb    # Identifikasi tipe data (Easy)
│   ├── exercise_2.ipynb    # Buat DataFrame berbagai sumber (Easy)
│   ├── exercise_3.ipynb    # Statistik deskriptif & groupby (Easy-Med)
│   ├── exercise_4.ipynb    # Deteksi inkonsistensi data (Medium)
│   └── exercise_5.ipynb    # Mini EDA Titanic (Medium)
├── solusi/
│   ├── solution_1.ipynb    ← Lihat SETELAH mencoba sendiri!
│   ├── solution_2.ipynb
│   ├── solution_3.ipynb
│   ├── solution_4.ipynb
│   └── solution_5.ipynb
└── README.md               ← File ini
```

---

## 🗺️ Step-by-Step Learning Guide

### Step 1: Baca Teori (60–90 menit)
1. Buka `teori/Day_01_Teori_Lengkap.ipynb`
2. Jalankan setiap cell dari atas ke bawah (**Run All** atau Shift+Enter)
3. Fokus pada:
   - Taksonomi 4 tipe data + kapan masing-masing dipakai
   - Fungsi eksplorasi pandas: `.info()`, `.describe()`, `.dtypes`
   - Perbedaan `.loc` vs `.iloc`
   - Demo `CategoricalDtype` untuk ordinal

### Step 2: Latihan (3–4 jam)

| Exercise | Topik | Estimasi | Priority |
|----------|-------|----------|----------|
| `exercise_1.ipynb` | Identifikasi tipe data | 30 mnt | ⭐⭐⭐ Wajib |
| `exercise_2.ipynb` | Buat & gabung DataFrame | 45 mnt | ⭐⭐⭐ Wajib |
| `exercise_3.ipynb` | Statistik & groupby | 45 mnt | ⭐⭐⭐ Wajib |
| `exercise_4.ipynb` | Deteksi inkonsistensi | 45 mnt | ⭐⭐ Penting |
| `exercise_5.ipynb` | Mini EDA Titanic | 60 mnt | ⭐⭐⭐ Wajib |

### Step 3: Review Solusi (30 menit)
- Buka solusi HANYA setelah mencoba sendiri minimal 15 menit
- Bandingkan pendekatan kamu dengan solusi
- Catat teknik yang belum kamu gunakan

---

## 📦 Dataset yang Digunakan

| Exercise | Dataset | Cara Load |
|----------|---------|-----------|
| exercise_1 | E-Commerce sintetis | Sudah di-generate di notebook |
| exercise_2 | Data pasien sintetis | Sudah di-generate di notebook |
| exercise_3 | Penjualan retail sintetis | `np.random` dengan seed=42 |
| exercise_4 | Survei kotor sintetis | Sudah di-generate di notebook |
| exercise_5 | Titanic | `sns.load_dataset('titanic')` |

> Semua dataset sudah tersedia di dalam notebook — tidak perlu download eksternal.

---

## ✅ Checklist Sebelum Lanjut ke Day 2

### Konsep
- [ ] Bisa jelaskan perbedaan Nominal vs Ordinal dengan contoh 3 kasus berbeda
- [ ] Tahu mengapa kode pos adalah Nominal meskipun berupa angka
- [ ] Paham kapan pakai `.loc` vs `.iloc`
- [ ] Bisa set kolom ordinal dengan `pd.CategoricalDtype(ordered=True)`

### Teknik Pandas
- [ ] Bisa buat DataFrame dari dict dan list of dicts
- [ ] Bisa gunakan `.merge()` untuk menggabungkan 2 DataFrame
- [ ] Bisa gunakan `.groupby().agg()` untuk agregasi multi-kolom
- [ ] Bisa gunakan `.isnull().sum()` untuk deteksi missing value
- [ ] Bisa filter dengan boolean mask + kondisi ganda (`&`, `|`)

### Exercise
- [ ] Selesaikan minimal **4 dari 5 exercise** (semua exercise 1, 2, 3, 5 wajib)
- [ ] Bisa jawab pertanyaan refleksi di setiap exercise

---

## 🔑 Quick Reference — Fungsi Pandas Day 1

```python
# Eksplorasi dasar
df.shape                      # (n_baris, n_kolom)
df.head(n) / df.tail(n)       # n baris pertama/terakhir
df.info()                     # ringkasan + tipe data + missing
df.dtypes                     # tipe data setiap kolom
df.describe()                 # statistik deskriptif numerik
df.describe(include='all')    # termasuk kategorik
df['kol'].value_counts()      # distribusi nilai kategorik
df.isnull().sum()             # missing value per kolom
df.nunique()                  # nilai unik per kolom

# Akses data
df['kolom']                   # satu kolom (Series)
df[['kol1','kol2']]           # beberapa kolom (DataFrame)
df.loc[baris, kolom]          # akses by label
df.iloc[baris, kolom]         # akses by posisi integer
df[df['kol'] > nilai]         # boolean filtering
df[(cond1) & (cond2)]         # filter multi kondisi

# Manipulasi
df['kolom'].astype(tipe)      # konversi tipe data
df['baru'] = df['kol']*2      # tambah kolom baru
df.groupby('kol').agg(...)    # agregasi per grup
pd.merge(df1, df2, on='key')  # gabungkan 2 DataFrame
df.to_csv('file.csv', index=False)  # simpan ke CSV

# Ordinal
dtype_ord = pd.CategoricalDtype(categories=['S','M','L'], ordered=True)
df['ukuran'] = df['ukuran'].astype(dtype_ord)
```

---

## ⚠️ Common Mistakes Day 1

1. **Angka = Numerik** — SALAH! Kode pos, ID, nomor telepon adalah angka tapi NOMINAL
2. **Percaya `dtypes` bulat-bulat** — `dtypes` hanya format penyimpanan, bukan tipe statistik
3. **Lupa `index=False` saat `to_csv()`** — akan muncul kolom `Unnamed: 0` saat dibaca kembali
4. **`.loc` vs `.iloc` tertukar** — `.loc` by label, `.iloc` by integer position
5. **Ordinal tanpa urutan eksplisit** — selalu set `ordered=True` agar comparison bekerja benar
6. **EDA = akurasi model** — SALAH! EDA untuk memahami data, bukan langsung prediksi

---

## 🔮 Preview Day 2

**Day 2: Mean, Median, Mode — Kapan Masing-Masing Misleading**

Topics yang akan dipelajari:
- Mean: sensitif terhadap outlier, kapan menipu?
- Median: lebih robust, kapan lebih baik dari mean?
- Mode: untuk kategorik, kapan berguna?
- Trimmed mean, weighted mean
- Real-world cases: gaji CEO + karyawan, harga properti

**Preparation**: Pastikan sudah install `scipy` untuk fungsi statistik lanjutan:
```bash
pip install scipy
```

---

## 📈 Progress Tracking

- Date: _____________
- Exercise selesai: ____ / 5
- Waktu total: ____ jam
- Konsep yang masih bingung:
  ```

  ```

---

*"Memahami tipe data adalah langkah pertama dalam setiap proyek data mining. Salah di sini = salah di seterusnya."* 🎯
