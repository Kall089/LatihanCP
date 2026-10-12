# Day 50 — Binary Search on Answer (Predikat Monoton)

> **Ide Utama:** Ketika sebuah masalah menanyakan *"Berapa nilai X terkecil/terbesar yang memenuhi syarat P(X)?"* dan sifat $P(X)$ adalah **monoton** (misal: false, false, ..., true, true), kita bisa melakukan Binary Search pada ruang jawaban $X$, bukan pada array!

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 50, kamu akan mampu:

- [ ] Memahami konsep **Parametric Search** / **Binary Search on Answer**
- [ ] Mengenali **Pola Red Flag**: *"Minimalkan Nilai Maksimum"* atau *"Maksimalkan Nilai Minimum"*
- [ ] Merancang fungsi boolean `check(mid)` (Predikat Monoton)
- [ ] Menentukan batas pencarian jawaban (`low` dan `high`) dengan aman
- [ ] Menggunakan Binary Search pada **Floating Point** (Bilangan Real dengan Epsilon)
- [ ] Menyelesaikan soal-soal standar CP (Factory Machines, Aggressive Cows, Koko Eating Bananas)

---

## 📁 Struktur Folder

```
Day-50 (Binary Search on Answer - Predikat Monoton)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_50_Teori_Lengkap.md     ← Teori lengkap 8 bagian
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Factory Machines - CSES)
│   ├── exercise_2.cpp   (Warm-up  : Aggressive Cows - SPOJ)
│   ├── exercise_3.cpp   (Core     : EKO / Potong Kayu)
│   ├── exercise_4.cpp   (Core     : Array Division / Split Array - CSES/LeetCode 410)
│   ├── exercise_5.cpp   (Challenge: Ship Packages Within D Days - LeetCode 1011)
│   └── exercise_6.cpp   (Contest  : Binary Search on Real Numbers / Precision)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp .. tugas_15.cpp (15 Soal Mandiri TANPA Solusi)
└── template/
    └── template.cpp     ← Template Parametric Search (Min & Max variant)
```

---

## 💡 Quick Reference — Pattern Binary Search on Answer

```cpp
// Skenario A: Minimalkan Jawaban X (Predikat: 0 0 0 1 1 1)
// Cari nilai X terkecil yang memenuhi check(X) == true
long long low = min_val, high = max_val;
long long ans = high;

while (low <= high) {
    long long mid = low + (high - low) / 2;
    if (check(mid)) {
        ans = mid;         // simpulkan mid valid, coba cari yang lebih kecil
        high = mid - 1;
    } else {
        low = mid + 1;    // mid tidak cukup besar
    }
}

// Skenario B: Maksimalkan Jawaban X (Predikat: 1 1 1 0 0 0)
// Cari nilai X terbesar yang memenuhi check(X) == true
long long low = min_val, high = max_val;
long long ans = low;

while (low <= high) {
    long long mid = low + (high - low) / 2;
    if (check(mid)) {
        ans = mid;         // simpulkan mid valid, coba cari yang lebih besar
        low = mid + 1;
    } else {
        high = mid - 1;   // mid terlalu besar
    }
}
```

---

## 🔗 Soal Rekomendasi Online Judge

- **CSES**: Factory Machines, Array Division
- **SPOJ**: AGGRCOW, EKO
- **LeetCode 875**: Koko Eating Bananas
- **LeetCode 1011**: Capacity To Ship Packages Within D Days
- **LeetCode 1760**: Minimum Limit of Balls in Bag
- **Codeforces**: 1201C (Maximum Median), 1613C (Poisoned Dagger)
