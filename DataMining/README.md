# 🔍 Data Mining Learning Path

Folder ini berisi materi pembelajaran **Data Mining & Machine Learning** secara terstruktur, dari fondasi statistik hingga advanced techniques.

## 📁 Struktur Folder

```
DataMining/
├── PROMPT_TEMPLATE_DATAMINING.md   ← Template prompt untuk generate materi harian
├── README.md                       ← File ini
└── Day-XX (Topic Name)/            ← Satu folder per hari
    ├── teori/
    │   └── Day_XX_Teori_Lengkap.ipynb   ← Teori + kode + visualisasi
    ├── latihan/
    │   ├── exercise_1.ipynb             ← Latihan dengan TODO cells
    │   ├── exercise_2.ipynb
    │   └── ...
    ├── solusi/
    │   ├── solution_1.ipynb             ← Solusi lengkap
    │   └── ...
    ├── dataset/                         ← Dataset lokal jika diperlukan
    └── README.md                        ← Panduan hari itu
```

## 🗺️ Roadmap Singkat (112 Hari)

| Bulan | Tema | Hari |
|-------|------|------|
| 1 | Foundation: Statistik + Preprocessing + Python Tools + Probability | 1–28 |
| 2 | Core ML: Supervised + Classification + Advanced + Unsupervised | 29–56 |
| 3 | Real Data: Feature Engineering + Pipeline + Big Picture + Mini Project | 57–84 |
| 4 | Advanced: Time Series + NLP + Recommender + Final Project | 85–112 |

## 🛠️ Setup Environment

```bash
# Buat virtual environment
python -m venv venv
source venv/bin/activate  # Mac/Linux
# venv\Scripts\activate   # Windows

# Install dependencies
pip install numpy pandas matplotlib seaborn scikit-learn jupyter notebook

# Atau pakai conda
conda create -n datamining python=3.11
conda activate datamining
conda install numpy pandas matplotlib seaborn scikit-learn jupyter
```

## ▶️ Cara Buka Notebook

```bash
# Dari folder DataMining
jupyter notebook

# Atau Jupyter Lab (lebih modern)
pip install jupyterlab
jupyter lab
```

## 📌 Cara Menggunakan Template

1. Buka `PROMPT_TEMPLATE_DATAMINING.md`
2. Copy prompt sesuai hari yang ingin dibuat
3. Paste ke AI (Cascade / ChatGPT / dll)
4. AI akan generate struktur lengkap untuk hari tersebut

---

**"Data is the new oil — but only if you know how to refine it."** 🛢️
