# 📊 Day 50: Binary Search on Answer (Predikat Monoton)

> **Prasyarat:** Binary Search pada Array (Day 48), Greedy & Simulasi Dasar  
> **Difficulty:** ⭐⭐⭐  
> **Learning Objectives:**  
> - Mengenali kapan masalah dapat diselesaikan dengan Binary Search pada Jawaban  
> - Memahami sifat **Monotonisitas** dari fungsi penentu `check(mid)`  
> - Menulis fungsi pembantu `check(mid)` berbasis simulasi atau Greedy $O(N)$  
> - Menguasai pola pencarian jawaban minimum dan jawaban maksimum  

---

## 🔍 1. Konsep & Intuisi

Pada Binary Search biasa (Day 48), kita mencari nilai di dalam array yang tersimpan di memori.  
Pada **Binary Search on Answer** (Parametric Search), tidak ada array tersimpan! Kita melakukan Binary Search pada **ruang kemungkinan jawaban** (misal range $1$ sampai $10^{18}$).

### Syarat Utama: Monotonisitas Predikat $P(X)$
Fungsi `check(X)` adalah pertanyaan bernilai `true` atau `false`.

1. **Kasus Minimalkan Jawaban:**
   - Jika waktu $X = 100$ detik cukup untuk memproduksi barang, maka $X = 101, 102, 1000$ detik PASTI cukup.
   - Sifat Predikat: `[false, false, false, TRUE, TRUE, TRUE]`
   - Target kita: Titik *TRUE* paling kiri (jawaban terkecil yang valid).

2. **Kasus Maksimalkan Jawaban:**
   - Jika gergaji setinggi $H = 10$ meter menghasilkan kayu cukup, maka $H = 9, 8, 1$ meter PASTI menghasilkan lebih banyak kayu.
   - Sifat Predikat: `[TRUE, TRUE, TRUE, false, false, false]`
   - Target kita: Titik *TRUE* paling kanan (jawaban terbesar yang valid).

---

## 🧮 2. Analisis Kompleksitas

- **Time Complexity:** $O(T_{\text{check}} \times \log_2(\text{High} - \text{Low}))$
  - Jika fungsi `check(mid)` membutuhkan $O(N)$ dan range jawaban $10^{12}$, maka Binary Search melakukan $\approx 40$ iterasi. Total waktu: $40 \times O(N) = O(N)$. Ini SANGAT CEPAT!
- **Space Complexity:** $O(1)$ atau sesuai kebutuhan `check(mid)`.

---

## 💻 3. Implementasi C++ Standard

### Template Minimalkan Jawaban
```cpp
#include <bits/stdc++.h>
using namespace std;

// Fungsi Predikat Monoton
bool check(long long mid, const vector<long long>& arr, long long k) {
    long long count = 0;
    for (long long x : arr) {
        count += mid / x;
        if (count >= k) return true; // Early exit
    }
    return count >= k;
}

long long solveMinAnswer(const vector<long long>& arr, long long k) {
    long long low = 1, high = 1e18; // Range jawaban yang aman
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, arr, k)) {
            ans = mid;
            high = mid - 1; // Coba cari yang lebih kecil lagi
        } else {
            low = mid + 1; // mid kurang besar
        }
    }
    return ans;
}
```

---

## ⚠️ 4. Common Mistakes & Edge Cases

1. **Range `high` Kurang Besar:**
   - Jika kemungkinan jawaban bisa mencapai $10^{18}$, menetapkan `high = 1e9` akan menghasilkan **Wrong Answer (WA)**.
   - Hati-hati dengan `low + high` yang melampaui limit `long long` jika `high = 2e18`.

2. **Pencarian Real Number (Double):**
   - Jangan pakai `while (low <= high)` untuk `double`.
   - Gunakan iterasi tetap (misal 100 kali):
     ```cpp
     for (int iter = 0; iter < 100; iter++) {
         double mid = low + (high - low) / 2;
         if (check(mid)) high = mid;
         else low = mid;
     }
     ```

3. **`check(mid)` Mengalami Overflow:**
   - Di dalam `check(mid)`, perhitungan total atau jumlah perkalian bisa melampaui `long long`. Gunakan early exit jika `total >= target`.

---

## 🏆 5. Tips Contest & Pattern Recognition

- **Kata Kunci Soal:**
  - *"Minimalkan waktu maksimum..."*
  - *"Maksimalkan jarak minimum..."*
  - *"Berapa kapasitas paling sedikit yang mampu..."*
- Jika membaca soal seperti di atas, **LANGSUNG PIKIRKAN BINARY SEARCH ON ANSWER**!
