# Day 48 — Binary Search pada Array Terurut

> **Ide utama:** Jika array sudah terurut, daripada mengecek satu per satu $O(N)$, potong ruang pencarian menjadi dua di setiap langkah hingga tersisa 1 elemen ($O(\log N)$).

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 48, kamu akan mampu:

- [ ] Memahami konsep **Divide and Conquer** pada Binary Search $O(\log N)$
- [ ] Menghindari jebakan **integer overflow** `(low + high) / 2` $\to$ `low + (high - low) / 2`
- [ ] Mengimplementasikan **Binary Search Manual** tanpa bug *off-by-one* atau *infinite loop*
- [ ] Menggunakan STL `std::lower_bound` dan `std::upper_bound` dengan mahir
- [ ] Mencari frekuensi elemen dan kemunculan pertama/terakhir pada array terurut
- [ ] Menyelesaikan variasi seperti **Search in Rotated Sorted Array**

---

## 📁 Struktur Folder

```
Day-48 (Binary Search pada Array Terurut)/
├── README.md               ← Panduan ini
├── teori/
│   └── Day_48_Teori_Lengkap.md     ← Teori mendalam + trace + analisis
├── latihan/
│   ├── exercise_1.cpp   (Warm-up  : Binary Search Standard)
│   ├── exercise_2.cpp   (Warm-up  : Lower Bound & Upper Bound Manual)
│   ├── exercise_3.cpp   (Core     : Hitung Frekuensi Elemen)
│   ├── exercise_4.cpp   (Core     : First and Last Position - LeetCode 34)
│   ├── exercise_5.cpp   (Challenge: Floor and Ceiling in Sorted Array)
│   └── exercise_6.cpp   (Contest  : Search in Rotated Sorted Array)
├── solusi/
│   └── solution_1.cpp .. solution_6.cpp
├── tugas/
│   └── tugas_01.cpp .. tugas_15.cpp (15 Soal Mandiri TANPA Solusi)
└── template/
    └── template.cpp     ← Snippet Binary Search, lower_bound, upper_bound
```

---

## 💡 Quick Reference — Pattern Binary Search

```cpp
// 1. Standar (Cari nilai pasti)
int low = 0, high = n - 1;
while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) low = mid + 1;
    else high = mid - 1;
}

// 2. Lower Bound Manual (Elemen pertama >= target)
int low = 0, high = n; // Range [0, n]
while (low < high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] >= target) high = mid;
    else low = mid + 1;
}
// low adalah indeks elemen pertama >= target

// 3. Upper Bound Manual (Elemen pertama > target)
int low = 0, high = n;
while (low < high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] > target) high = mid;
    else low = mid + 1;
}
// low adalah indeks elemen pertama > target
```

---

## 🔗 Soal Rekomendasi Online Judge

- **LeetCode 704**: Binary Search
- **LeetCode 34**: Find First and Last Position of Element in Sorted Array
- **LeetCode 35**: Search Insert Position
- **LeetCode 33**: Search in Rotated Sorted Array
- **CSES**: Array Division / Maximum Subarray Sum variations
