# 📋 PROMPT TEMPLATE — Pembelajaran Data Mining dengan Python (112 Hari)

## 🎯 Cara Menggunakan Template Ini:

1. Copy prompt di bawah
2. Ganti `[DAY_NUMBER]` dengan nomor hari (contoh: 1, 2, 3, dst.)
3. Paste ke chat AI (Cascade, ChatGPT, Claude, dll.)
4. AI akan otomatis membuat struktur lengkap sesuai roadmap Data Mining 112 hari

---

## 📝 PROMPT TEMPLATE LENGKAP (Copy Paste Ini):

```
Buatkan materi pembelajaran Data Mining lengkap untuk DAY [DAY_NUMBER] sesuai roadmap 112 hari dengan Python.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
⚠️ CRITICAL CHECKLIST (BEFORE YOU START):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. ✅ TEORI NOTEBOOK (teori/Day_XX_Teori_Lengkap.ipynb):
   - Semua cell harus RUNNABLE (tidak ada broken imports atau missing deps)
   - Setiap section punya markdown cell penjelasan + code cell implementasi
   - Visualisasi WAJIB (matplotlib/seaborn) untuk setiap konsep utama
   - Dataset yang digunakan: sklearn.datasets, seaborn datasets, atau generate sintetis
   - Output cell disimpan (bisa langsung di-run dari atas ke bawah)

2. ✅ EXERCISE NOTEBOOKS (latihan/exercise_X.ipynb):
   - Setiap exercise dalam file .ipynb TERPISAH
   - Punya markdown cell deskripsi lengkap + context
   - Code cell dengan # TODO: komentar yang jelas
   - Expected output dijelaskan di markdown cell setelah TODO
   - Dataset yang sama dengan teori (konsisten)

3. ✅ SOLUTION NOTEBOOKS (solusi/solution_X.ipynb):
   - Implementasi LENGKAP (NO TODO cells di solution)
   - Penjelasan approach di markdown cell sebelum code
   - Output cell tersimpan / bisa langsung di-run
   - Interpretasi hasil wajib ada (bukan hanya kode)

4. ✅ QUALITY:
   - Python 3.x compatible
   - Import semua library di cell pertama (convention)
   - Gunakan random_state=42 untuk reproducibility
   - Visualisasi: figsize yang jelas, title, label, legend
   - Penjelasan dalam Bahasa Indonesia

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

STRUKTUR WAJIB:

1. FOLDER STRUCTURE:
DataMining/Day-[DAY_NUMBER] ([TOPIC_NAME])/
├── teori/
│   └── Day_[DAY_NUMBER]_Teori_Lengkap.ipynb   (teori + kode + visualisasi interaktif)
├── latihan/
│   ├── exercise_1.ipynb  (5–8 exercise notebooks dengan TODO)
│   ├── exercise_2.ipynb
│   ├── ... (hingga exercise_5+.ipynb)
├── solusi/
│   ├── solution_1.ipynb  (solusi lengkap + penjelasan)
│   ├── solution_2.ipynb
│   └── ... (satu per exercise)
├── dataset/              (jika pakai dataset custom/lokal)
└── README.md             (panduan belajar hari ini)

2. FORMAT TEORI NOTEBOOK (WAJIB):

Setiap teori notebook harus punya urutan cell seperti ini:

[Cell 1 - Markdown]: Header
# 📊 Day X: [Judul Topik]
**Tanggal**: Day X dari 112 Hari Data Mining
**Topik**: [Topik Utama]
**Prerequisites**: [Apa yang perlu diketahui]
**Learning Objectives**: bullet points apa yang akan dipelajari

[Cell 2 - Code]: Setup & Imports (SELALU pertama)
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn... import ...
# dll sesuai kebutuhan

plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['figure.figsize'] = (10, 6)
np.random.seed(42)

[Cell 3 - Markdown]: Section 1 — Penjelasan Konsep
## 🔍 1. [Nama Konsep]
Penjelasan konsep dalam Bahasa Indonesia yang DETAIL:
- Apa itu (definisi)
- Mengapa penting
- Kapan digunakan
- Intuisi visual/analogi

[Cell 4 - Code]: Demo konsep dengan dataset nyata
# Kode yang mendemonstrasikan konsep
# Dengan komentar step-by-step

[Cell 5 - Code]: Visualisasi konsep
fig, ax = plt.subplots(...)
# Visualisasi yang informatif
plt.title('...')
plt.tight_layout()
plt.show()

[Cell N - Markdown]: Summary
## 📌 Ringkasan
- Poin penting 1
- Poin penting 2
- Kapan pakai teknik ini
- Common pitfalls

[Cell N+1 - Markdown]: Lanjut ke Latihan
## 🏋️ Selanjutnya: Latihan
Buka folder `latihan/` untuk mengerjakan exercise hari ini.

3. FORMAT EXERCISE NOTEBOOK (WAJIB):

[Cell 1 - Markdown]:
# 🏋️ Exercise X: [Judul]
**Day**: X | **Difficulty**: Easy/Medium/Hard
**Topic**: [Topik]

## 📋 Problem Statement
[Deskripsi LENGKAP minimal 3-5 kalimat]:
- Konteks/scenario yang relevan
- Apa yang diminta secara jelas
- Data yang tersedia
- Output yang diharapkan

## 🎯 Learning Goals
- [ ] Goal 1
- [ ] Goal 2

[Cell 2 - Code]: Load data / Setup
# Setup
import numpy as np
import pandas as pd
...

# Load atau generate dataset
# Jelaskan dataset dalam komentar

[Cell 3 - Markdown]:
## 📝 Langkah Pengerjaan
1. Step 1: ...
2. Step 2: ...
3. Step 3: ...

[Cell 4 - Code]: TODO cells
# ============================================================
# TODO 1: [Instruksi jelas apa yang harus dilakukan]
# Expected: [Jelaskan output yang diharapkan]
# ============================================================

# Tulis kode kamu di sini
...

[Cell 5 - Markdown]: Setelah TODO
**💡 Hint**: [Hint jika macet]

**✅ Expected Output**: [Deskripsi output yang benar]

[Last Cell - Markdown]:
## 🤔 Pertanyaan Refleksi
1. Apa yang kamu pelajari dari exercise ini?
2. Kapan kamu akan menggunakan teknik ini di dunia nyata?
3. Apa keterbatasan dari pendekatan ini?

4. FORMAT SOLUTION NOTEBOOK (WAJIB):

[Cell 1 - Markdown]:
# ✅ Solution X: [Judul]
**Approach**: [Pendekatan/algoritma/teknik yang digunakan]
**Key Insight**: [Insight kunci mengapa approach ini benar]

[Cell 2 - Code]: Full imports
import numpy as np
...

[Cell 3 - Markdown]:
## 📖 Penjelasan Pendekatan
[Penjelasan MENGAPA approach ini dipilih]
[Langkah-langkah solusi]

[Cell 4 - Code]: Solusi LENGKAP
# Step 1: [Komentar]
...
# Step 2: [Komentar]
...

[Cell 5 - Code/Markdown]: Interpretasi & Analisis Hasil
# Interpretasi output — bukan hanya print angka!
# Jelaskan apa artinya dalam konteks masalah

[Last Cell - Markdown]:
## 📌 Takeaways dari Solusi Ini
- Poin 1
- Poin 2
- Alternative approaches yang bisa dicoba

5. ISI MATERI WAJIB:

A. TEORI NOTEBOOK (.ipynb):
   ✅ Penjelasan konsep MENDALAM dalam Bahasa Indonesia
   ✅ Untuk APA teknik ini (real-world use cases)
   ✅ Kapan & mengapa pakai teknik ini (decision guidance)
   ✅ Visualisasi WAJIB untuk setiap konsep (matplotlib/seaborn)
   ✅ Step-by-step kode Python dengan komentar per line
   ✅ Math intuisi (bukan derivasi penuh, tapi arti setiap rumus)
   ✅ Comparison dengan alternative approaches
   ✅ Contoh dengan dataset yang relevan & realistis
   ✅ Common pitfalls & cara menghindarinya
   ✅ Real-world interpretation of results
   ✅ Summary cell di akhir setiap section
   ✅ Section struktur:
      - 🔍 Konsep & Intuisi
      - 🧮 Math Dasar (ringan, dengan intuisi)
      - 💻 Implementasi Python (step-by-step)
      - 📊 Visualisasi & Interpretasi
      - ⚠️ Common Mistakes
      - 🎯 Kapan Pakai Teknik Ini
      - 📌 Summary

B. EXERCISE NOTEBOOKS (.ipynb):
   ✅ 5–8 exercise per hari (progresif easy → hard)
   ✅ Setiap exercise dalam file TERPISAH (exercise_1.ipynb, ...)
   ✅ Problem statement LENGKAP & kontekstual
   ✅ Dataset yang relevan dengan topik hari ini
   ✅ TODO cells yang jelas dengan expected output
   ✅ Hints tersedia (tapi tidak spoil solusi)
   ✅ Pertanyaan refleksi di akhir
   ✅ Tingkat kesulitan:
      - Exercise 1-2: Warm-up (langsung dari teori)
      - Exercise 3-4: Core (butuh pemahaman lebih dalam)
      - Exercise 5-6: Challenge (kombinasi konsep)
      - Exercise 7-8: Real-world application (opsional)

C. SOLUTION NOTEBOOKS (.ipynb):
   ✅ Satu solution per exercise (solution_1.ipynb, ...)
   ✅ Kode LENGKAP & bisa langsung di-run
   ✅ Penjelasan approach SEBELUM kode
   ✅ Interpretasi hasil (bukan hanya angka)
   ✅ Insights dari hasil (business/analytical perspective)
   ✅ Alternative approaches disebutkan
   ✅ Visualisasi tambahan jika memperjelas

D. README.md:
   ✅ Learning objectives hari ini
   ✅ Prerequisites
   ✅ Step-by-step learning guide
   ✅ Dataset yang digunakan & cara loadnya
   ✅ Breakdown exercise (tingkat kesulitan)
   ✅ Checklist sebelum lanjut ke hari berikutnya
   ✅ Common mistakes hari ini
   ✅ Preview hari selanjutnya
   ✅ Quick reference cheatsheet teknik hari ini

6. PYTHON REQUIREMENTS & STYLE:

   ✅ Python 3.x (3.8+)
   ✅ Library wajib: numpy, pandas, matplotlib, seaborn, scikit-learn
   ✅ random_state=42 untuk semua yang random (reproducibility)
   ✅ Gunakan f-string untuk formatting output
   ✅ Visualisasi:
      - figsize yang informatif (biasanya (10,6) atau (12,8))
      - Title yang deskriptif
      - Axis label selalu ada
      - Legend jika multi-series
      - plt.tight_layout() selalu dipanggil
      - plt.show() di akhir setiap plot
   ✅ Dataset convention:
      - X = features (kapital)
      - y = target (lowercase)
      - X_train, X_test, y_train, y_test (snake_case)
   ✅ Gunakan sklearn pipeline jika relevan
   ✅ Print hasil dengan konteks (bukan hanya angka):
      # ❌ print(score)
      # ✅ print(f"Accuracy: {score:.4f} ({score*100:.2f}%)")
   ✅ Komentar dalam code cell: Bahasa Indonesia
   ✅ Markdown cell: Bahasa Indonesia

7. QUALITY CHECKLIST:

   ✅ Semua notebook bisa di-run dari atas ke bawah tanpa error
   ✅ Tidak ada broken import atau missing dependency
   ✅ Visualisasi tampil dengan benar
   ✅ Random state konsisten (42) untuk reproducibility
   ✅ Exercise notebooks punya TODO yang jelas
   ✅ Solution notebooks COMPLETE (tidak ada TODO yang tersisa)
   ✅ Dataset tersedia (dari sklearn/seaborn atau generate sintetis)
   ✅ README lengkap dan actionable
   ✅ Interpretasi hasil selalu ada (bukan hanya output)

8. KONTEN SPESIFIK:

   Lihat roadmap Day [DAY_NUMBER]:
   - Topik utama: [akan auto-detect dari roadmap]
   - Tools/library: [sesuai topik]
   - Dataset: [pilih yang relevan]
   - Focus: [praktis dan hands-on, bukan teori kering]

PENTING:
- Fokus pada PRACTICAL DATA MINING mindset
- Emphasis pada interpretasi & insight, bukan hanya akurasi
- Code harus RUNNABLE tanpa modifikasi
- Visualisasi WAJIB — data mining tanpa visualisasi itu buta
- Penjelasan dalam Bahasa Indonesia
- Selalu tanya: "Apa artinya hasil ini untuk bisnis/user?"
- Common pitfalls WAJIB disebutkan
- Materi harus DEEP & PRACTICAL, bukan teori kering
- Exercise harus memaksa berpikir, bukan sekadar copy-paste

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 🔥 PROMPT SINGKAT (Untuk Daily Use):

```
Lanjut Data Mining Day [DAY_NUMBER]

Buat struktur lengkap:
- teori/Day_XX_Teori_Lengkap.ipynb (teori + kode + visualisasi)
- latihan/exercise_1-5.ipynb (exercise dengan TODO cells)
- solusi/solution_1-5.ipynb (solusi lengkap)
- README.md

Ikuti roadmap 112 hari Data Mining. Semua notebook harus RUNNABLE.
Penjelasan Bahasa Indonesia. Dataset dari sklearn/seaborn.
```

---

## 📌 QUICK REFERENCE — Notebook Cell Conventions

### 🏷️ Emoji Section Headers (Pakai Konsisten):
| Emoji | Arti | Contoh |
|-------|------|--------|
| 🔍 | Konsep/Penjelasan | `## 🔍 1. Apa itu Mean?` |
| 🧮 | Math / Formula | `## 🧮 2. Rumus Variance` |
| 💻 | Implementasi Kode | `## 💻 3. Implementasi Python` |
| 📊 | Visualisasi | `## 📊 4. Plot Distribusi` |
| ⚠️ | Warning / Pitfall | `## ⚠️ Common Mistakes` |
| 🎯 | Kapan Dipakai | `## 🎯 Kapan Pakai Ini?` |
| 📌 | Summary / Key Points | `## 📌 Ringkasan` |
| 🏋️ | Exercise / Latihan | `## 🏋️ Exercise` |
| ✅ | Solusi / Done | `## ✅ Solution` |
| 💡 | Hint / Tips | `**💡 Hint**:` |
| 🤔 | Refleksi | `## 🤔 Pertanyaan Refleksi` |

### 📐 Template Cell Imports (Copy-Paste Setiap Hari):
```python
# ============================================================
# 📦 IMPORTS — Day XX: [Topik]
# ============================================================
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Scikit-learn (sesuaikan dengan topik)
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, classification_report

# Style
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 12
np.random.seed(42)

print("✅ Setup selesai!")
```

### 📏 Template TODO Cell:
```python
# ============================================================
# TODO X: [Instruksi jelas]
# 
# Kamu diminta untuk:
# 1. [Langkah 1]
# 2. [Langkah 2]
#
# Expected output: [Deskripsi output yang benar]
# Hint: [Hint ringan]
# ============================================================

# Tulis kode kamu di sini ↓

```

---

## 📌 QUICK REFERENCE — Roadmap Data Mining (112 Hari)

---

### 🟦 BULAN 1 — FOUNDATION (STATISTIK + PREPROCESSING + PYTHON + PROBABILITY)

#### **Minggu 1 — Data & Statistik Dasar**
- **Day 1**: Tipe data (numerical, categorical, ordinal, nominal), struktur dataset, pandas DataFrame intro
- **Day 2**: Mean, median, mode — kapan masing-masing misleading, resistant statistics
- **Day 3**: Variance, standard deviation, IQR — mengukur spread data
- **Day 4**: Distribusi data: normal, skewed (kiri/kanan), heavy-tailed, bimodal
- **Day 5**: Visualisasi dasar: histogram, boxplot, violin plot — membaca cerita dari grafik
- **Day 6**: Correlation vs causation — Pearson, Spearman, heatmap, Simpson's paradox
- **Day 7**: Review Minggu 1 + analisis dataset sederhana end-to-end (Iris / Titanic)

**Target Minggu 1**: Bisa melihat data dan "curiga" kalau ada yang aneh 🔍

#### **Minggu 2 — Data Preprocessing (REAL SKILL)**
- **Day 8**: Missing value — deteksi, drop vs impute (mean/median/mode/KNN imputer)
- **Day 9**: Outlier detection — IQR method, z-score, isolation forest intro
- **Day 10**: Encoding — label encoding, one-hot encoding, ordinal encoding, target encoding
- **Day 11**: Normalization vs standardization — MinMaxScaler, StandardScaler, RobustScaler
- **Day 12**: Feature scaling impact — kapan penting, kapan tidak (tree vs distance-based models)
- **Day 13**: Data leakage — jenis-jenisnya, cara deteksi, mengapa mematikan model production
- **Day 14**: Mini project: cleaning dataset kotor lengkap (custom dataset dengan berbagai masalah)

**Target Minggu 2**: Paham bahwa 80% kerja data mining = cleaning 🧹

#### **Minggu 3 — Python Tools untuk Data Mining (WAJIB)**
- **Day 15**: Python dasar untuk data — list comprehension, lambda, *args/**kwargs, file I/O
- **Day 16**: NumPy mendalam — array operations, broadcasting, vectorization vs loop
- **Day 17**: Pandas core — Series, DataFrame, indexing (loc/iloc), chaining
- **Day 18**: Data manipulation — filter, groupby, pivot_table, merge/join, apply/transform
- **Day 19**: Matplotlib mendalam — subplots, custom styles, annotations, saving figures
- **Day 20**: Seaborn — distribusi, relasi, kategori, heatmap, pairplot, FacetGrid
- **Day 21**: Exploratory Data Analysis (EDA) — workflow lengkap, profiling, storytelling dengan data

**Target Minggu 3**: Bisa "ngobrol" sama data 🗣️

#### **Minggu 4 — Probability Dasar**
- **Day 22**: Probability rules — AND, OR, complement, mutually exclusive, independence
- **Day 23**: Conditional probability — P(A|B), joint probability table, law of total probability
- **Day 24**: Bayes theorem — intuisi dengan contoh nyata (spam filter, medical test), Bayesian thinking
- **Day 25**: Random variable — diskrit vs kontinu, expected value, PMF, PDF, CDF
- **Day 26**: Distribusi penting — normal (68-95-99.7), binomial, Poisson, exponential
- **Day 27**: Sampling — population vs sample, sampling bias, Central Limit Theorem, confidence interval intro
- **Day 28**: Review Bulan 1 + quiz + analisis dataset dengan semua tools yang sudah dipelajari

**Target Minggu 4**: Paham ketidakpastian, bukan hanya angka 🎲

---

### 🟨 BULAN 2 — CORE MACHINE LEARNING

#### **Minggu 5 — Supervised Learning: Regression**
- **Day 29**: Regression concept — supervised vs unsupervised, regression vs classification, mana yang cocok
- **Day 30**: Linear Regression — OLS, interpretasi koefisien, asumsi model, residual analysis
- **Day 31**: Overfitting vs underfitting — bias-variance intuisi awal, learning curve
- **Day 32**: Train/test split — holdout, mengapa shuffle, stratified split, temporal split
- **Day 33**: Regression metrics — MSE, MAE, RMSE, R², Adjusted R², MAPE, kapan pakai mana
- **Day 34**: Regularization — Ridge (L2), Lasso (L1), ElasticNet, efek pada koefisien, alpha tuning
- **Day 35**: Review Minggu 5 + mini project regression (dataset harga rumah / salary prediction)

#### **Minggu 6 — Classification**
- **Day 36**: Logistic Regression — dari linear ke probabilitas, sigmoid, interpretasi, decision boundary
- **Day 37**: Decision Tree — information gain, Gini impurity, depth control, pruning, visualisasi tree
- **Day 38**: K-Nearest Neighbors (KNN) — distance metrics, curse of dimensionality, k selection
- **Day 39**: Evaluation metrics — accuracy, precision, recall, F1-score, kapan mana yang dipakai
- **Day 40**: Confusion matrix — TP/TN/FP/FN, interpretasi per-class, imbalanced data preview
- **Day 41**: ROC curve, AUC — threshold tradeoff, interpretasi business, PR curve untuk imbalanced
- **Day 42**: Review Minggu 6 + mini project classification (Titanic / Breast Cancer dataset)

#### **Minggu 7 — Advanced Models**
- **Day 43**: Random Forest — bagging, feature importance, OOB score, hyperparameters
- **Day 44**: Gradient Boosting — AdaBoost, GBM, XGBoost intro, kapan lebih baik dari RF
- **Day 45**: Bias-variance tradeoff mendalam — decomposisi error, implikasinya untuk model selection
- **Day 46**: Feature importance — dari tree models, permutation importance, SHAP intro
- **Day 47**: Cross-validation — k-fold, stratified k-fold, LeaveOneOut, cross_val_score
- **Day 48**: Hyperparameter tuning — GridSearchCV, RandomizedSearchCV, Bayesian optimization intro
- **Day 49**: Review Minggu 7 + benchmark berbagai model pada satu dataset

#### **Minggu 8 — Unsupervised Learning**
- **Day 50**: Clustering concept — apa itu unsupervised, use cases, evaluasi tanpa label
- **Day 51**: K-Means — algoritma, elbow method, silhouette score, inisialisasi K-Means++
- **Day 52**: Hierarchical clustering — linkage methods, dendrogram, kapan lebih baik dari K-Means
- **Day 53**: DBSCAN — density-based, epsilon & min_samples, noise handling, shape clusters
- **Day 54**: Dimensionality reduction — PCA: variance explained, scree plot, loadings, 2D visualization
- **Day 55**: Practice clustering — dataset customer segmentation, interpretasi cluster yang terbentuk
- **Day 56**: Review Bulan 2 + quiz komprehensif supervised + unsupervised

---

### 🟥 BULAN 3 — REAL DATA & PIPELINE THINKING

#### **Minggu 9 — Feature Engineering**
- **Day 57**: Feature selection — filter methods (correlation, chi2, ANOVA), wrapper (RFE), embedded (Lasso)
- **Day 58**: Feature transformation — log transform, Box-Cox, power transform, kapan diperlukan
- **Day 59**: Handling categorical advanced — target encoding, frequency encoding, binary encoding
- **Day 60**: Interaction features — polynomial features, domain-knowledge interactions, feature crosses
- **Day 61**: Time-based features — hour/day/month extraction, lag features, rolling window
- **Day 62**: Practice feature engineering — take raw dataset, engineer features, compare model performance
- **Day 63**: Review Minggu 9 + feature engineering checklist

#### **Minggu 10 — Pipeline Thinking**
- **Day 64**: sklearn Pipeline — ColumnTransformer, make_pipeline, why pipeline = no leakage
- **Day 65**: End-to-end workflow — dari raw data → deployment-ready model, checklist pipeline
- **Day 66**: Data leakage revisited (lebih dalam) — temporal leakage, target leakage, train-test contamination
- **Day 67**: Model comparison framework — fair comparison, baseline model, statistical significance test
- **Day 68**: Error analysis — confusion matrix deep dive, error patterns, where model fails & why
- **Day 69**: Practice pipeline — bangun pipeline lengkap untuk 2 dataset berbeda
- **Day 70**: Review Minggu 10 + end-to-end project mini

#### **Minggu 11 — Big Picture Skill**
- **Day 71**: Problem framing — dari pertanyaan bisnis ke ML task, output yang dibutuhkan
- **Day 72**: Business understanding — stakeholder needs, cost of errors (FP vs FN), success metrics
- **Day 73**: Metric selection di dunia nyata — kasus nyata kapan accuracy salah metric
- **Day 74**: Precision vs recall tradeoff — threshold tuning untuk business requirement
- **Day 75**: Interpretability — white box vs black box, LIME intro, SHAP values
- **Day 76**: Model limitations — distribusi shift, concept drift, what can't ML do
- **Day 77**: Review Minggu 11 + case study analisis model gagal di production

#### **Minggu 12 — Mini Project Brutal**
- **Day 78**: Setup project — pilih dataset Kaggle, definisi masalah, success criteria
- **Day 79**: Data cleaning & EDA mendalam — profiling, visualisasi distribusi, anomali detection
- **Day 80**: Feature engineering — domain knowledge + statistical features
- **Day 81**: Modeling — baseline → multiple models → hyperparameter tuning
- **Day 82**: Evaluation mendalam — cross-validation, error analysis, confusion matrix interpretasi
- **Day 83**: Insight & storytelling — apa yang kamu temukan, business recommendation
- **Day 84**: Presentasi mini project — README, notebook yang bersih, insight summary

**Target Bulan 3**: Bukan akurasi tinggi, tapi CERITA dari data 📖

---

### 🟥 BULAN 4 — ADVANCED + SPECIALIZATION

#### **Minggu 13 — Time Series Analysis**
- **Day 85**: Time series concepts — stationarity, trend, seasonality, autocorrelation (ACF/PACF)
- **Day 86**: Decomposition — additive vs multiplicative, seasonal_decompose, STL
- **Day 87**: Stationarity testing — ADF test, KPSS, differencing, log transform
- **Day 88**: ARIMA family — AR, MA, ARIMA, SARIMA, pmdarima auto_arima
- **Day 89**: ML untuk time series — lag features, rolling features, train/test split temporal
- **Day 90**: Forecasting evaluation — MAE, RMSE, MAPE, SMAPE, walk-forward validation
- **Day 91**: Practice time series — forecast dataset penjualan / cuaca / traffic

#### **Minggu 14 — NLP Dasar**
- **Day 92**: Text data basics — tokenization, stopwords, stemming, lemmatization
- **Day 93**: Bag of Words & TF-IDF — konsep, implementasi, limitations
- **Day 94**: Text classification — sentiment analysis dengan TF-IDF + Logistic Regression
- **Day 95**: Word embeddings intro — Word2Vec intuisi, cosine similarity, aplikasi
- **Day 96**: Text preprocessing pipeline — cleaning → tokenize → vectorize → model
- **Day 97**: Practice NLP — sentiment analysis atau topic categorization
- **Day 98**: Review NLP + intro ke modern NLP (transformers — sekilas, tidak mendalam)

#### **Minggu 15 — Recommender Systems**
- **Day 99**: Recommender concepts — collaborative filtering, content-based, hybrid
- **Day 100**: User-based collaborative filtering — similarity matrix, KNN untuk rekomendasi
- **Day 101**: Item-based collaborative filtering — item similarity, scalability
- **Day 102**: Matrix factorization — SVD, NMF, latent factors intuisi
- **Day 103**: Content-based filtering — feature representation item, TF-IDF untuk content
- **Day 104**: Evaluasi recommender — precision@K, recall@K, NDCG, cold start problem
- **Day 105**: Practice — bangun simple recommender untuk MovieLens dataset

#### **Minggu 16 — Final Project + Portfolio**
- **Day 106**: Final project kick-off — pilih domain (e-commerce, healthcare, finance, dll.)
- **Day 107**: Data collection & cleaning — scraping/download + cleaning komprehensif
- **Day 108**: Feature engineering & modeling — pipeline lengkap
- **Day 109**: Advanced evaluation & interpretasi — SHAP, error analysis, business insight
- **Day 110**: Documentation — README, notebook yang bersih, visualisasi portfolio-worthy
- **Day 111**: Portfolio review — struktur GitHub, penjelasan project, presentation tips
- **Day 112**: Retrospektif 112 hari + next steps (Kaggle, NLP lanjutan, Deep Learning path)

---

## 🗂️ Dataset Quick Reference

### 📦 Sklearn Built-in Datasets
```python
from sklearn.datasets import (
    load_iris,            # Klasifikasi 3 kelas, 150 sampel
    load_wine,            # Klasifikasi wine, 178 sampel
    load_breast_cancer,   # Klasifikasi biner, 569 sampel
    load_digits,          # Image classification, 1797 sampel
    load_boston,          # ⚠️ Deprecated — pakai fetch_california_housing
    fetch_california_housing,  # Regresi harga rumah
    make_classification,  # Generate dataset klasifikasi sintetis
    make_regression,      # Generate dataset regresi sintetis
    make_blobs,           # Generate clusters sintetis
    make_moons,           # Dataset bentuk bulan (non-linear)
    make_circles,         # Dataset lingkaran (non-linear)
)
```

### 🌊 Seaborn Datasets
```python
import seaborn as sns
tips    = sns.load_dataset('tips')      # Restaurant tips — regresi/klasifikasi
titanic = sns.load_dataset('titanic')   # Titanic survival — klasifikasi biner
penguins= sns.load_dataset('penguins') # Penguin species — klasifikasi 3 kelas
flights = sns.load_dataset('flights')  # Monthly passengers — time series
iris    = sns.load_dataset('iris')     # Bunga iris — klasifikasi klasik
diamonds= sns.load_dataset('diamonds') # Harga berlian — regresi
```

### 🎲 Generate Sintetis (Reproducible)
```python
import numpy as np
np.random.seed(42)

# Dataset regresi sintetis
n = 200
X_synth = np.random.randn(n, 3)
y_synth = 3*X_synth[:,0] + 2*X_synth[:,1] - X_synth[:,2] + np.random.randn(n)*0.5

# Dataset dengan missing values
df = pd.DataFrame({'A': [1,2,np.nan,4], 'B': ['x','y',np.nan,'z']})
```

---

## 🛠️ Cheatsheet: Sklearn Pipeline

```python
from sklearn.pipeline import Pipeline
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.impute import SimpleImputer
from sklearn.ensemble import RandomForestClassifier

# Definisi features
numeric_features = ['age', 'fare']
categorical_features = ['sex', 'embarked']

# Preprocessor per tipe kolom
numeric_transformer = Pipeline([
    ('imputer', SimpleImputer(strategy='median')),
    ('scaler', StandardScaler())
])

categorical_transformer = Pipeline([
    ('imputer', SimpleImputer(strategy='most_frequent')),
    ('encoder', OneHotEncoder(handle_unknown='ignore'))
])

preprocessor = ColumnTransformer([
    ('num', numeric_transformer, numeric_features),
    ('cat', categorical_transformer, categorical_features)
])

# Full pipeline
clf_pipeline = Pipeline([
    ('preprocessor', preprocessor),
    ('classifier', RandomForestClassifier(n_estimators=100, random_state=42))
])

# Fit & evaluate
clf_pipeline.fit(X_train, y_train)
score = clf_pipeline.score(X_test, y_test)
print(f"Pipeline Accuracy: {score:.4f}")
```

---

## 📏 Cheatsheet: Evaluasi Model

```python
from sklearn.metrics import (
    # Classification
    accuracy_score, precision_score, recall_score, f1_score,
    classification_report, confusion_matrix, ConfusionMatrixDisplay,
    roc_auc_score, roc_curve, average_precision_score,
    
    # Regression
    mean_squared_error, mean_absolute_error, r2_score,
    mean_absolute_percentage_error
)

# Classification report lengkap
print(classification_report(y_test, y_pred, target_names=class_names))

# Confusion matrix visual
cm = confusion_matrix(y_test, y_pred)
disp = ConfusionMatrixDisplay(cm, display_labels=class_names)
disp.plot(cmap='Blues')
plt.title('Confusion Matrix')
plt.tight_layout()
plt.show()

# ROC Curve
fpr, tpr, _ = roc_curve(y_test, y_prob[:, 1])
auc = roc_auc_score(y_test, y_prob[:, 1])
plt.plot(fpr, tpr, label=f'AUC = {auc:.3f}')
plt.plot([0,1],[0,1],'--', color='gray')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC Curve')
plt.legend()
plt.tight_layout()
plt.show()
```

---

## 🔑 Key Mindsets untuk Data Mining

### 1. 🤔 Selalu Tanya "Mengapa?"
- Mengapa metric ini? → Pahami business impact
- Mengapa model ini? → Pahami tradeoffs
- Mengapa fitur ini? → Pahami domain knowledge

### 2. 📊 Visualisasi Dulu, Model Kemudian
```
❌ Salah: Load data → langsung train model → lihat akurasi
✅ Benar: Load data → EDA → cleaning → feature eng → model → interpretasi
```

### 3. ⚠️ Waspadai Data Leakage
```python
# ❌ Salah: Fit scaler pada ALL data
scaler.fit(X)  # Lihat test set!
X_scaled = scaler.transform(X)
X_train, X_test = train_test_split(X_scaled, ...)

# ✅ Benar: Fit scaler HANYA pada train set
X_train, X_test, y_train, y_test = train_test_split(X, y, ...)
scaler.fit(X_train)   # Hanya train!
X_train = scaler.transform(X_train)
X_test = scaler.transform(X_test)   # Transform saja, jangan fit!
```

### 4. 🎯 Baseline Selalu Dulu
```python
# Sebelum model canggih, selalu bandingkan dengan baseline sederhana
from sklearn.dummy import DummyClassifier
dummy = DummyClassifier(strategy='most_frequent')
dummy.fit(X_train, y_train)
print(f"Baseline accuracy: {dummy.score(X_test, y_test):.4f}")
# Jika model lo cuma sedikit lebih baik dari dummy → masalah!
```

### 5. 📌 Interpretasi > Akurasi
```
Akurasi 95% tapi tidak tahu kenapa → BERBAHAYA
Akurasi 82% tapi paham setiap keputusan → BERGUNA
```

---

## ⚙️ Setup Environment (Satu Kali)

```bash
# Buat virtual environment
python -m venv venv
source venv/bin/activate   # Mac/Linux
# venv\Scripts\activate    # Windows

# Install semua dependency
pip install numpy pandas matplotlib seaborn scikit-learn \
            jupyter jupyterlab notebook \
            xgboost lightgbm \
            statsmodels scipy \
            imbalanced-learn \
            shap \
            wordcloud nltk

# Verifikasi
python -c "import numpy, pandas, sklearn, matplotlib, seaborn; print('✅ All OK')"

# Jalankan Jupyter
jupyter lab
```

---

## 📁 Contoh Folder Day 1 (Referensi Struktur):

```
DataMining/Day-01 (Tipe Data & Struktur Dataset)/
├── teori/
│   └── Day_01_Teori_Lengkap.ipynb
├── latihan/
│   ├── exercise_1.ipynb   # Identifikasi tipe data dari dataset nyata
│   ├── exercise_2.ipynb   # Buat DataFrame dari berbagai sumber
│   ├── exercise_3.ipynb   # Statistik deskriptif dasar
│   ├── exercise_4.ipynb   # Deteksi inconsistency dalam dataset
│   └── exercise_5.ipynb   # EDA mini dengan Titanic
├── solusi/
│   ├── solution_1.ipynb
│   ├── solution_2.ipynb
│   ├── solution_3.ipynb
│   ├── solution_4.ipynb
│   └── solution_5.ipynb
└── README.md
```

---

*Template ini mengikuti filosofi: **"Belajar Data Mining yang baik bukan tentang hafalan rumus, tapi tentang curiosity terhadap data dan kemampuan bercerita dari angka."*** 📊
