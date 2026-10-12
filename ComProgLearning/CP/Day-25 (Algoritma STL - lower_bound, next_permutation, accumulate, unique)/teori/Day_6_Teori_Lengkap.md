# Day 6 — STL Algorithms

## Tujuan Pembelajaran
- [ ] Menguasai `sort` dengan custom comparator (struct, lambda, multi-criteria)
- [ ] Menggunakan `lower_bound` dan `upper_bound` untuk binary search O(log n)
- [ ] Menggunakan `next_permutation` untuk generate semua permutasi
- [ ] Memanfaatkan `accumulate`, `count_if`, `max_element` untuk reduksi
- [ ] Menguasai `find`, `reverse`, `rotate`, `unique` dan kapan memakainya
- [ ] Memahami `transform`, `fill`, `iota` untuk inisialisasi dan transformasi
- [ ] Menggunakan `all_of`, `any_of`, `none_of` untuk cek kondisi batch
- [ ] Menerapkan pola Coordinate Compression dengan `lower_bound`
- [ ] Memahami perbedaan `stable_sort` vs `sort`

---

## 1. `sort` — O(n log n)

```cpp
#include <algorithm> // sudah ada di <bits/stdc++.h>

vector<int> A = {3, 1, 4, 1, 5};

// Ascending (default)
sort(A.begin(), A.end());

// Descending
sort(A.begin(), A.end(), greater<int>());

// Custom comparator — lambda
sort(A.begin(), A.end(), [](int a, int b) {
    return a > b; // descending
});
```

### Sort Struct Multi-Criteria
```cpp
struct Student { string name; int score; };

sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    if (a.score != b.score) return a.score > b.score; // score desc
    return a.name < b.name;                           // name asc (tiebreak)
});
```

### `stable_sort` — Pertahankan Urutan Relatif
```cpp
// Jika dua elemen equal, urutan semula dipertahankan
stable_sort(A.begin(), A.end(), comp);
// Contoh: sort by score saja → siswa dengan nilai sama tetap urut sesuai input
```

---

## 2. `lower_bound` & `upper_bound` — O(log n)

**Prasyarat**: Array harus sudah **sorted**.

```cpp
vector<int> A = {1, 2, 2, 3, 4, 4};

// lower_bound: iterator ke elemen pertama >= x
auto lo = lower_bound(A.begin(), A.end(), 2); // → index 1
// upper_bound: iterator ke elemen pertama > x
auto hi = upper_bound(A.begin(), A.end(), 2); // → index 3

int count     = hi - lo;               // 2 (jumlah elemen == 2)
int first_geq = lo - A.begin();        // 1 (index pertama >= 2)
bool exists   = binary_search(A.begin(), A.end(), 2); // true
```

### Pola Umum di CP
```cpp
// Cari index elemen pertama >= x (atau n jika tidak ada)
int lb = lower_bound(A.begin(), A.end(), x) - A.begin();

// Hitung elemen dalam range [l, r]
int cnt = upper_bound(A.begin(), A.end(), r)
        - lower_bound(A.begin(), A.end(), l);
```

---

## 3. `next_permutation` — Generate Semua Permutasi

```cpp
vector<int> A = {1, 2, 3};
sort(A.begin(), A.end()); // mulai dari terkecil!

do {
    for (int x : A) cout << x << " ";
    cout << "\n";
} while (next_permutation(A.begin(), A.end()));
// Total: n! iterasi
```

**Catatan**: `next_permutation` mengembalikan `false` saat kembali ke permutasi awal → loop berhenti.

`prev_permutation` untuk arah sebaliknya.

---

## 4. `accumulate` — Reduksi Array

```cpp
#include <numeric>

vector<int> A = {1, 2, 3, 4, 5};

// Sum
ll sum = accumulate(A.begin(), A.end(), 0LL); // 15

// Product
ll prod = accumulate(A.begin(), A.end(), 1LL,
    [](ll acc, int x) { return acc * x; }); // 120

// Product mod
const int MOD = 1e9+7;
ll pmod = accumulate(A.begin(), A.end(), 1LL,
    [&](ll acc, int x) { return acc * x % MOD; });

// Custom: sum of squares
ll sq = accumulate(A.begin(), A.end(), 0LL,
    [](ll acc, int x) { return acc + (ll)x*x; }); // 55
```

---

## 5. `max_element`, `min_element`, `count`, `count_if`

```cpp
// Max & Min
int mx = *max_element(A.begin(), A.end());
int mn = *min_element(A.begin(), A.end());
auto it = max_element(A.begin(), A.end());
int idx = it - A.begin(); // index elemen maksimum

// Count exact
int cnt = count(A.begin(), A.end(), 3);

// Count dengan kondisi
int evens = count_if(A.begin(), A.end(), [](int x){ return x%2==0; });
```

---

## 6. `find`, `reverse`, `rotate`, `unique`

```cpp
// find — O(n)
auto it = find(A.begin(), A.end(), 5);
if (it != A.end()) cout << "Found at " << it - A.begin();

// reverse — in-place
reverse(A.begin(), A.end());

// rotate — kiri k posisi
rotate(A.begin(), A.begin() + k, A.end());
// kanan k posisi:
rotate(A.begin(), A.begin() + n - k, A.end());

// unique — hapus consecutive duplicates (harus sorted dulu!)
sort(A.begin(), A.end());
A.erase(unique(A.begin(), A.end()), A.end());
```

---

## 7. `nth_element` & `partial_sort`

```cpp
// nth_element: letakkan elemen yang seharusnya di index k (tidak sorted sepenuhnya)
nth_element(A.begin(), A.begin() + k, A.end()); // O(n) rata-rata

// partial_sort: sort hanya k elemen pertama
partial_sort(A.begin(), A.begin() + k, A.end()); // O(n log k)

// Contoh: cari median
nth_element(A.begin(), A.begin() + n/2, A.end());
int median = A[n/2];
```

---

## 8. `transform` & `copy_if` — Transformasi dan Filter

```cpp
vector<int> A = {1, 2, 3, 4, 5};
vector<int> B(A.size());

// transform: apply function ke setiap elemen, simpan ke B
transform(A.begin(), A.end(), B.begin(),
    [](int x){ return x * x; });        // B = {1,4,9,16,25}

// transform dua range: A[i] + B[i]
vector<int> C(A.size());
transform(A.begin(), A.end(), B.begin(), C.begin(),
    [](int a, int b){ return a + b; }); // C = {2,6,12,20,30}

// copy_if: copy elemen yang memenuhi kondisi
vector<int> evens;
copy_if(A.begin(), A.end(), back_inserter(evens),
    [](int x){ return x % 2 == 0; });  // evens = {2,4}

// remove_if + erase: hapus elemen yang memenuhi kondisi
A.erase(remove_if(A.begin(), A.end(), [](int x){ return x%2==0; }), A.end());
// A = {1,3,5}
```

---

## 9. `fill` & `iota` — Inisialisasi Array

```cpp
vector<int> A(10);

// fill: set semua elemen ke nilai tertentu
fill(A.begin(), A.end(), 0);         // {0,0,...,0}
fill(A.begin(), A.begin()+5, -1);    // {-1,-1,-1,-1,-1,0,...}

// iota: isi dengan nilai berurutan
iota(A.begin(), A.end(), 1);         // {1,2,3,...,10}
iota(A.begin(), A.end(), 0);         // {0,1,2,...,9}

// Pola penting CP: index sorting
vector<int> idx(n);
iota(idx.begin(), idx.end(), 0);     // idx = {0,1,2,...,n-1}
sort(idx.begin(), idx.end(),
    [&](int i, int j){ return A[i] < A[j]; }); // sort by value
// Sekarang idx[0] = index elemen terkecil, dst.
```

---

## 10. `all_of`, `any_of`, `none_of` — Cek Kondisi Batch

```cpp
vector<int> A = {2, 4, 6, 8};

// all_of: apakah SEMUA elemen memenuhi?
bool allEven = all_of(A.begin(), A.end(),
    [](int x){ return x % 2 == 0; }); // true

// any_of: apakah ADA setidaknya satu yang memenuhi?
bool hasNeg = any_of(A.begin(), A.end(),
    [](int x){ return x < 0; });       // false

// none_of: apakah TIDAK ADA yang memenuhi?
bool noZero = none_of(A.begin(), A.end(),
    [](int x){ return x == 0; });      // true

// Contoh CP: cek apakah string hanya berisi digit
string s = "12345";
bool allDigit = all_of(s.begin(), s.end(), ::isdigit); // true
```

---

## 11. Coordinate Compression — Pola Penting di CP

Mengubah nilai besar ke index kecil (0-indexed) tanpa mengubah urutan relatif.

```cpp
vector<int> A = {100, 5, 50, 100, 5};

// Step 1: Buat sorted unique
vector<int> sorted_unique = A;
sort(sorted_unique.begin(), sorted_unique.end());
sorted_unique.erase(
    unique(sorted_unique.begin(), sorted_unique.end()),
    sorted_unique.end());
// sorted_unique = {5, 50, 100}

// Step 2: Replace tiap nilai dengan rank-nya (0-indexed)
for (int& x : A) {
    x = (int)(lower_bound(sorted_unique.begin(), sorted_unique.end(), x)
              - sorted_unique.begin());
}
// A = {2, 0, 1, 2, 0}

// Kompleksitas: O(n log n)
// Sangat berguna untuk: BIT/Fenwick Tree, segment tree, counting inversions
```

---

## 12. Set Operations pada Sorted Ranges

```cpp
vector<int> A = {1, 2, 3, 4};   // harus sorted!
vector<int> B = {2, 4, 6};      // harus sorted!
vector<int> inter, uni, diff;

// Irisan (intersection)
set_intersection(A.begin(), A.end(), B.begin(), B.end(),
    back_inserter(inter));        // {2, 4}

// Gabungan (union)
set_union(A.begin(), A.end(), B.begin(), B.end(),
    back_inserter(uni));          // {1,2,3,4,6}

// Selisih (difference): A − B
set_difference(A.begin(), A.end(), B.begin(), B.end(),
    back_inserter(diff));         // {1, 3}

// Merge dua sorted range
vector<int> merged;
merge(A.begin(), A.end(), B.begin(), B.end(),
    back_inserter(merged));       // {1,2,2,3,4,4,6}
```

---

## 13. Common Mistakes

1. **`lower_bound` tanpa sort terlebih dahulu**
   - Hasilnya undefined! Array harus sorted sebelum binary search

2. **`unique` tanpa sort**
   - `unique` hanya menghapus **consecutive** duplicates
   - Selalu: `sort` → `unique` → `erase`

3. **Iterator arithmetic: `lo - A.begin()` bukan `*lo`**
   - `lower_bound` mengembalikan iterator, bukan indeks

4. **`accumulate` dengan nilai awal salah**
   - Sum: nilai awal `0LL` (bukan `0` jika bisa overflow)
   - Product: nilai awal `1LL`

5. **`next_permutation` tanpa sort awal**
   - Harus mulai dari permutasi terkecil (sorted)

6. **`transform` output size tidak cocok**
   - Output range harus sudah punya cukup ruang, atau gunakan `back_inserter`

7. **`all_of` pada range kosong** → selalu `true` (vacuous truth)
   - Perlu cek `!A.empty()` jika ini tidak diinginkan

---

## 14. Kompleksitas

| Algoritma | Waktu | Keterangan |
|-----------|-------|------------|
| `sort` | O(n log n) | introsort |
| `stable_sort` | O(n log² n) | atau O(n log n) dengan memori |
| `lower/upper_bound` | O(log n) | harus sorted |
| `next_permutation` | O(n) per langkah | total O(n! × n) |
| `accumulate` | O(n) | |
| `max/min_element` | O(n) | |
| `transform` | O(n) | |
| `fill` | O(n) | |
| `iota` | O(n) | |
| `all_of/any_of/none_of` | O(n) | short-circuit |
| `copy_if` | O(n) | |
| `set_intersection/union` | O(n+m) | keduanya harus sorted |
| `nth_element` | O(n) | rata-rata |
| `unique` | O(n) | setelah sort |

---

## 15. Quick Reference

```cpp
// Sort
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>());
sort(v.begin(), v.end(), [](int a, int b){ return a>b; });

// Binary Search (sorted!)
auto lo = lower_bound(v.begin(), v.end(), x); // first >= x
auto hi = upper_bound(v.begin(), v.end(), x); // first > x
int cnt = (int)(hi - lo);                      // count == x
int idx = (int)(lo - v.begin());               // index

// Transformasi
transform(v.begin(), v.end(), v.begin(), [](int x){ return x*2; });
iota(idx.begin(), idx.end(), 0);               // 0,1,...,n-1
fill(v.begin(), v.end(), 0);                   // semua jadi 0

// Cek batch
bool ok = all_of(v.begin(), v.end(), pred);
bool any = any_of(v.begin(), v.end(), pred);

// Coordinate Compression
sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end());
int rank = lower_bound(v.begin(),v.end(),x) - v.begin();

// Deduplicate
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

---

## 16. Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| CSES | Sorting and Searching | sort, bs |
| LC 56 | Merge Intervals | sort + greedy |
| LC 179 | Largest Number | custom comparator |
| LC 315 | Count of Smaller Numbers | merge sort |
| LC 31 | Next Permutation | next_permutation logic |
| CSES | Movie Festival | sort by end time |
| LC 300 | Longest Increasing Subsequence | lower_bound O(n log n) |
| LC 287 | Find the Duplicate Number | nth_element |
