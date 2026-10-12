# 📊 Day 48: Binary Search pada Array Terurut

> **Prasyarat:** Array Statis & Vector (Day 18), Sorting (Day 47)  
> **Difficulty:** ⭐⭐  
> **Learning Objectives:**  
> - Memahami intuisi pencarian biner pada array terurut  
> - Menguasai pola penulisan loop Binary Search bebas dari Infinite Loop  
> - Memahami perbedaan dan implementasi `lower_bound` dan `upper_bound`  
> - Menghitung kompleksitas $O(\log N)$  

---

## 🔍 1. Konsep & Intuisi

Pencarian Linier (Linear Search) memeriksa elemen satu per satu dari awal sampai akhir. Jika ada $N = 1.000.000$ elemen, dalam kasus terburuk kita butuh $1.000.000$ operasi ($O(N)$).

**Binary Search** memanfaatkan sifat terurut (*sorted*) dari data.
Bayangkan kamu mencari kata "Kucing" di kamus cetak 1000 halaman:
1. Kamu tidak membuka dari halaman 1, 2, 3...
2. Kamu membuka tepat di tengah (halaman 500).
3. Jika menemukan kata berawalan "M", kamu tahu "K" pasti berada di paruh pertama (halaman 1–499). Kamu langsung membuang paruh kedua!
4. Proses ini mengeliminasi setengah dari sisa data pada tiap langkah.

### Diagram Alur Eliminasi
```
Ruang Pencarian Awal: [1, 3, 5, 8, 12, 15, 19, 21, 25, 30] (N = 10, Target = 19)

Langkah 1: mid = (0 + 9) / 2 = 4 (nilai = 12)
           12 < 19 -> Buang sebelah kiri!
           Ruang baru: [15, 19, 21, 25, 30] (indeks 5..9)

Langkah 2: mid = (5 + 9) / 2 = 7 (nilai = 21)
           21 > 19 -> Buang sebelah kanan!
           Ruang baru: [15, 19] (indeks 5..6)

Langkah 3: mid = (5 + 6) / 2 = 5 (nilai = 15)
           15 < 19 -> Buang sebelah kiri!
           Ruang baru: [19] (indeks 6..6)

Langkah 4: mid = 6 (nilai = 19) -> KETEMU! (Indeks 6)
```

---

## 🧮 2. Analisis Kompleksitas

- **Time Complexity:** $O(\log_2 N)$
  - $N = 10^6 \to \approx 20$ operasi.
  - $N = 10^9 \to \approx 30$ operasi.
- **Space Complexity:** $O(1)$ untuk versi iteratif.

---

## 💻 3. Implementasi C++

### A. Binary Search Standard (Cari Indeks)
```cpp
#include <bits/stdc++.h>
using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = (int)arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; // Hindari overflow
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // Tidak ditemukan
}
```

### B. Lower Bound Manual (`>= target`)
```cpp
int lowerBound(const vector<int>& arr, int target) {
    int low = 0, high = arr.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= target) high = mid;
        else low = mid + 1;
    }
    return low;
}
```

### C. Upper Bound Manual (`> target`)
```cpp
int upperBound(const vector<int>& arr, int target) {
    int low = 0, high = arr.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > target) high = mid;
        else low = mid + 1;
    }
    return low;
}
```

---

## ⚠️ 4. Common Mistakes & Edge Cases

1. **Integer Overflow pada `mid`:**
   - ❌ `int mid = (low + high) / 2;` (Jika `low + high > 2^31 - 1`, akan overflow!)
   - ✅ `int mid = low + (high - low) / 2;`

2. **Infinite Loop (Off-by-one):**
   - Perhatikan pengubahan `low = mid + 1` dan `high = mid - 1`. Jika lupa `+1` atau `-1` pada rentang `low <= high`, program bisa terjebak *infinite loop*.

3. **Array Tidak Terurut:**
   - Binary Search WAJIB dijalankan pada array terurut! Jika belum terurut, panggil `sort(arr.begin(), arr.end())` terlebih dahulu.

---

## 🏆 5. Tips Contest

- Di C++ STL, gunakan fungsi bawaan `std::lower_bound` dan `std::upper_bound`:
  ```cpp
  auto it = lower_bound(arr.begin(), arr.end(), target);
  int idx = distance(arr.begin(), it);
  ```
- Untuk menghitung berapa kali angka `X` muncul di sorted array:
  ```cpp
  int count_X = upper_bound(all(arr), X) - lower_bound(all(arr), X);
  ```
