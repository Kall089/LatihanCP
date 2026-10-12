# 📊 Day 3: STL Containers 1 — Vector, String, Pair, Tuple

**Hari**: Day 3 dari 150 Hari Competitive Programming  
**Topik**: STL Containers Dasar  
**Prerequisites**: Tipe data C++, Input/Output, Compiler setup  
**Difficulty**: ⭐ (Beginner)  
**Learning Objectives**:

- Memahami dan menggunakan `vector` secara efisien
- Memanipulasi `string` untuk problem solving
- Menggunakan `pair` dan `tuple` untuk data composite
- Mengetahui kapan menggunakan container mana

---

## 🔍 1. Konsep & Intuisi

### Apa itu STL Containers?

STL (Standard Template Library) adalah kumpulan class template di C++ yang menyediakan **struktur data siap pakai**. Di competitive programming, kita tidak perlu implementasi dari nol — cukup pakai STL.

**Analogi Kehidupan Nyata:**

- **Vector** = Rak buku yang bisa diperpanjang otomatis
- **String** = Kalung huruf yang bisa dipotong, disambung, dibalik
- **Pair** = Amplop berisi 2 kertas (nama & nilai)
- **Tuple** = Amplop berisi 3+ kertas

### Mengapa Penting di CP?

Hampir **100% soal CP** menggunakan minimal satu STL container. Tanpa STL, kamu harus menulis ratusan baris kode untuk hal yang bisa dilakukan 1 baris.

```
Tanpa STL:  int arr[100]; int size = 0; // manual resize, manual copy...
Dengan STL: vector<int> v; v.push_back(x); // otomatis!
```

### Kapan Digunakan (Pattern Recognition)

| Situasi                                      | Container                           |
| -------------------------------------------- | ----------------------------------- |
| Butuh array dinamis (ukuran berubah)         | `vector`                            |
| Manipulasi teks/karakter                     | `string`                            |
| Menyimpan 2 nilai terkait (x,y), (id, score) | `pair`                              |
| Menyimpan 3+ nilai terkait                   | `tuple`                             |
| Sort berdasarkan beberapa kriteria           | `vector<pair>` atau `vector<tuple>` |

---

## 🧮 2. Analisis Kompleksitas

### Vector

| Operasi              |  Kompleksitas  | Catatan                 |
| -------------------- | :------------: | ----------------------- |
| `push_back(x)`       | O(1) amortized | Kadang O(n) saat resize |
| `pop_back()`         |      O(1)      |                         |
| `v[i]` (akses index) |      O(1)      |                         |
| `insert(pos, x)`     |      O(n)      | Geser elemen            |
| `erase(pos)`         |      O(n)      | Geser elemen            |
| `size()`             |      O(1)      |                         |
| `sort(all(v))`       |   O(n log n)   |                         |
| `find()`             |      O(n)      | Linear search           |

### String

| Operasi              | Kompleksitas  | Catatan                  |
| -------------------- | :-----------: | ------------------------ |
| `s[i]`               |     O(1)      |                          |
| `s += t`             |   O(len(t))   | Append                   |
| `s.substr(pos, len)` |    O(len)     | Buat string baru         |
| `s.find(pattern)`    | O(n\*m) worst | n=len(s), m=len(pattern) |
| `reverse(all(s))`    |     O(n)      |                          |
| `sort(all(s))`       |  O(n log n)   | Sort karakter            |

### Pair & Tuple

| Operasi              | Kompleksitas |
| -------------------- | :----------: |
| Buat pair/tuple      |     O(1)     |
| Akses elemen         |     O(1)     |
| Compare (untuk sort) |     O(1)     |

---

## 💻 3. Implementasi C++

### 3.1 Vector — Array Dinamis

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    vector<int> v1;              // kosong
    vector<int> v2(5);           // [0, 0, 0, 0, 0]
    vector<int> v3(5, -1);       // [-1, -1, -1, -1, -1]
    vector<int> v4 = {3, 1, 4, 1, 5};  // initializer list

    // === TAMBAH & HAPUS ELEMEN ===
    v1.push_back(10);   // v1 = [10]
    v1.push_back(20);   // v1 = [10, 20]
    v1.push_back(30);   // v1 = [10, 20, 30]
    v1.pop_back();      // v1 = [10, 20]

    // === AKSES ELEMEN ===
    cout << v4[0] << '\n';       // 3 (0-indexed)
    cout << v4.front() << '\n';  // 3 (elemen pertama)
    cout << v4.back() << '\n';   // 5 (elemen terakhir)

    // === UKURAN ===
    cout << v4.size() << '\n';   // 5
    cout << v4.empty() << '\n';  // 0 (false, tidak kosong)

    // === ITERASI ===
    // Cara 1: index
    for (int i = 0; i < (int)v4.size(); i++) {
        cout << v4[i] << ' ';
    }
    cout << '\n';

    // Cara 2: range-based for (RECOMMENDED di CP)
    for (int x : v4) {
        cout << x << ' ';
    }
    cout << '\n';

    // Cara 3: reference (jika mau modify)
    for (int &x : v4) {
        x *= 2;  // kalikan semua elemen dengan 2
    }

    // === SORT ===
    sort(v4.begin(), v4.end());         // ascending
    sort(v4.rbegin(), v4.rend());       // descending

    // === RESIZE & CLEAR ===
    v4.resize(3);       // potong jadi 3 elemen
    v4.clear();         // hapus semua, size = 0

    return 0;
}
```

### 3.2 Vector — Teknik Penting untuk CP

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === INPUT N ELEMEN ===
    int n;
    cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;  // baca langsung

    // === REMOVE DUPLICATES (setelah sort) ===
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    // Sekarang v hanya berisi elemen unik

    // === FIND ELEMEN ===
    // Linear search
    auto it = find(v.begin(), v.end(), 42);
    if (it != v.end()) {
        cout << "Found at index: " << (it - v.begin()) << '\n';
    }

    // Binary search (HARUS sorted dulu!)
    if (binary_search(v.begin(), v.end(), 42)) {
        cout << "42 exists!\n";
    }

    // === LOWER/UPPER BOUND (sorted vector) ===
    // lower_bound: iterator ke elemen >= x
    // upper_bound: iterator ke elemen > x
    auto lb = lower_bound(v.begin(), v.end(), 5);
    auto ub = upper_bound(v.begin(), v.end(), 5);
    int count_5 = ub - lb;  // jumlah elemen == 5

    // === SUM SEMUA ELEMEN ===
    long long total = accumulate(v.begin(), v.end(), 0LL);

    // === MIN & MAX ===
    int mn = *min_element(v.begin(), v.end());
    int mx = *max_element(v.begin(), v.end());

    // === 2D VECTOR ===
    int rows = 3, cols = 4;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    grid[1][2] = 5;  // baris 1, kolom 2

    return 0;
}
```

### 3.3 String — Manipulasi Teks

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI & INPUT ===
    string s1 = "hello";
    string s2;
    cin >> s2;          // baca satu kata (stop di spasi)
    // getline(cin, s2); // baca satu baris (termasuk spasi)

    // === UKURAN ===
    cout << s1.size() << '\n';    // 5
    cout << s1.length() << '\n';  // 5 (sama saja)

    // === AKSES KARAKTER ===
    cout << s1[0] << '\n';    // 'h'
    cout << s1.back() << '\n'; // 'o'

    // === CONCATENATION ===
    string s3 = s1 + " world";  // "hello world"
    s1 += "!";                  // "hello!"

    // === SUBSTRING ===
    string sub = s3.substr(0, 5);   // "hello" (dari index 0, panjang 5)
    string sub2 = s3.substr(6);     // "world" (dari index 6 sampai akhir)

    // === FIND ===
    size_t pos = s3.find("world");
    if (pos != string::npos) {
        cout << "Found at position: " << pos << '\n';  // 6
    }

    // === REVERSE ===
    string s4 = "abcde";
    reverse(s4.begin(), s4.end());  // "edcba"

    // === SORT CHARACTERS ===
    string s5 = "dcba";
    sort(s5.begin(), s5.end());  // "abcd"

    // === KONVERSI ===
    int num = 123;
    string str_num = to_string(num);  // "123"
    int back_to_int = stoi(str_num);  // 123
    long long big = stoll("999999999999");

    // === COMPARE ===
    if (s1 == s2) cout << "sama\n";
    if (s1 < s2) cout << "s1 lebih kecil (lexicographic)\n";

    // === CEK PALINDROME ===
    string original = "racecar";
    string rev = original;
    reverse(rev.begin(), rev.end());
    if (original == rev) cout << "Palindrome!\n";

    // === ITERASI PER KARAKTER ===
    string word = "hello";
    for (char c : word) {
        cout << c << ' ';  // h e l l o
    }
    cout << '\n';

    // === FREQUENCY COUNT ===
    string text = "aabbbcc";
    int freq[26] = {};
    for (char c : text) {
        freq[c - 'a']++;
    }
    // freq[0]=2 (a), freq[1]=3 (b), freq[2]=2 (c)

    return 0;
}
```

### 3.4 Pair — Dua Nilai Terkait

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    pair<int, int> p1 = {3, 5};
    pair<int, int> p2 = make_pair(7, 2);
    pair<string, int> p3 = {"Alice", 95};

    // === AKSES ===
    cout << p1.first << ' ' << p1.second << '\n';  // 3 5
    cout << p3.first << ' ' << p3.second << '\n';  // Alice 95

    // === STRUCTURED BINDING (C++17) ===
    auto [nama, score] = p3;
    cout << nama << " got " << score << '\n';

    // === SORTING PAIRS ===
    // Default: sort by .first, then by .second
    vector<pair<int,int>> vp = {{3,1}, {1,5}, {3,2}, {1,3}};
    sort(vp.begin(), vp.end());
    // Result: {1,3}, {1,5}, {3,1}, {3,2}

    // Sort by .second:
    sort(vp.begin(), vp.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });

    // === COMMON CP PATTERN: simpan (value, index) ===
    int n = 5;
    vector<int> arr = {30, 10, 50, 20, 40};
    vector<pair<int,int>> val_idx;
    for (int i = 0; i < n; i++) {
        val_idx.push_back({arr[i], i});
    }
    sort(val_idx.begin(), val_idx.end());
    // Sekarang val_idx = {(10,1), (20,3), (30,0), (40,4), (50,2)}
    // Kita tahu elemen terkecil (10) ada di index 1

    // === PAIR SEBAGAI RETURN VALUE ===
    // pair<int,int> findMinMax(vector<int>& v) {
    //     return {*min_element(all(v)), *max_element(all(v))};
    // }

    return 0;
}
```

### 3.5 Tuple — Tiga atau Lebih Nilai

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    tuple<int, int, int> t1 = {1, 2, 3};
    tuple<string, int, double> t2 = {"Bob", 20, 3.5};

    // === AKSES (get<index>) ===
    cout << get<0>(t1) << '\n';  // 1
    cout << get<1>(t1) << '\n';  // 2
    cout << get<2>(t1) << '\n';  // 3

    // === STRUCTURED BINDING (C++17) — RECOMMENDED ===
    auto [name, age, gpa] = t2;
    cout << name << " " << age << " " << gpa << '\n';

    // === TIE (unpack ke variabel) ===
    int a, b, c;
    tie(a, b, c) = t1;  // a=1, b=2, c=3

    // === SORTING TUPLES ===
    // Default: sort by elemen 0, lalu 1, lalu 2
    vector<tuple<int,int,int>> vt = {{3,1,4}, {1,5,9}, {3,1,2}};
    sort(vt.begin(), vt.end());
    // Result: {1,5,9}, {3,1,2}, {3,1,4}

    // === CP PATTERN: simpan (distance, x, y) ===
    // Sort otomatis by distance dulu
    vector<tuple<int,int,int>> points;
    points.push_back({5, 0, 1});   // dist=5, koordinat (0,1)
    points.push_back({2, 3, 4});   // dist=2, koordinat (3,4)
    points.push_back({5, 1, 0});   // dist=5, koordinat (1,0)
    sort(points.begin(), points.end());
    // Sorted by distance: (2,3,4), (5,0,1), (5,1,0)

    // === KAPAN PAIR vs TUPLE vs STRUCT? ===
    // Pair:  2 elemen, cukup .first/.second
    // Tuple: 3+ elemen tapi sementara (tidak perlu nama field)
    // Struct: butuh nama field yang jelas, reusable

    return 0;
}
```

---

## 🔄 4. Trace / Simulasi

### Trace: Vector Push Back & Resize

```
Operasi                  | Vector State      | Size | Capacity
-------------------------|-------------------|------|----------
vector<int> v;           | []                | 0    | 0
v.push_back(10);         | [10]              | 1    | 1
v.push_back(20);         | [10, 20]          | 2    | 2
v.push_back(30);         | [10, 20, 30]      | 3    | 4  ← resize!
v.push_back(40);         | [10, 20, 30, 40]  | 4    | 4
v.push_back(50);         | [10,20,30,40,50]  | 5    | 8  ← resize!
v.pop_back();            | [10, 20, 30, 40]  | 4    | 8
```

**Insight**: Capacity selalu power of 2. Saat penuh, capacity digandakan (amortized O(1)).

### Trace: Sort Vector of Pairs

```
Input: vp = {(3,1), (1,5), (3,2), (1,3)}

Sort default (by first, then second):

Step 1: Compare (3,1) vs (1,5) → 3 > 1, swap
Step 2: Compare (3,1) vs (3,2) → first sama (3==3), compare second: 1 < 2, no swap
...

Result: {(1,3), (1,5), (3,1), (3,2)}
         ↑ first=1     ↑ first=3
         sorted ascending by .first

         Untuk first yang sama (1,1): sorted by .second (3 < 5)
         Untuk first yang sama (3,3): sorted by .second (1 < 2)
```

### Trace: Remove Duplicates dari Vector

```
Input: v = [3, 1, 4, 1, 5, 3, 2, 1]

Step 1: sort(v.begin(), v.end())
        v = [1, 1, 1, 2, 3, 3, 4, 5]

Step 2: unique(v.begin(), v.end())
        v = [1, 2, 3, 4, 5, ?, ?, ?]
                              ↑ unique returns iterator here
        (elemen setelah iterator = garbage)

Step 3: v.erase(unique_end, v.end())
        v = [1, 2, 3, 4, 5]

Result: 5 elemen unik
```

---

## 📝 5. Variasi & Pattern

### Pattern 1: Input ke Vector lalu Proses

```cpp
// Baca N elemen, cari jumlah elemen unik
int n; cin >> n;
vector<int> v(n);
for (int &x : v) cin >> x;
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
cout << v.size() << '\n';
```

### Pattern 2: Pair untuk Coordinate/Index Tracking

```cpp
// Simpan (value, original_index) lalu sort by value
vector<pair<int,int>> indexed;
for (int i = 0; i < n; i++) {
    indexed.push_back({arr[i], i});
}
sort(indexed.begin(), indexed.end());
// Sekarang bisa akses: elemen terkecil = indexed[0].first
//                       index aslinya = indexed[0].second
```

### Pattern 3: String Frequency Count

```cpp
// Hitung frekuensi setiap huruf
string s; cin >> s;
int freq[26] = {};
for (char c : s) freq[c - 'a']++;
// freq[0] = jumlah 'a', freq[1] = jumlah 'b', dst.
```

### Pattern 4: Tuple untuk Multi-Criteria Sort

```cpp
// Sort siswa by: (kelas ascending, nilai descending, nama ascending)
vector<tuple<int, int, string>> students;
// Trick: negate nilai supaya descending jadi ascending
students.push_back({kelas, -nilai, nama});
sort(students.begin(), students.end());
```

### Pattern 5: Vector 2D sebagai Grid/Matrix

```cpp
int n, m; cin >> n >> m;
vector<vector<char>> grid(n, vector<char>(m));
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        cin >> grid[i][j];
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### Mistake 1: Unsigned Subtraction Underflow

```cpp
vector<int> v;  // empty
// BAHAYA: v.size() - 1 = sangat besar! (unsigned underflow)
for (int i = 0; i < v.size() - 1; i++) { ... }  // BUG!

// FIX: cast ke int
for (int i = 0; i < (int)v.size() - 1; i++) { ... }  // SAFE
```

### Mistake 2: Akses Index Out of Bounds

```cpp
vector<int> v = {1, 2, 3};
cout << v[5];  // UNDEFINED BEHAVIOR! Tidak error tapi garbage value

// FIX: selalu cek bounds
if (i >= 0 && i < (int)v.size()) {
    cout << v[i];
}
```

### Mistake 3: String npos

```cpp
string s = "hello";
int pos = s.find("xyz");   // return string::npos (bukan -1!)
if (pos == -1) { ... }     // Ini bisa work karena npos == -1 as int
                            // Tapi lebih aman:
if (s.find("xyz") == string::npos) { ... }  // BETTER
```

### Mistake 4: Push_back dalam Loop yang Iterasi Vector

```cpp
// BAHAYA: iterator invalidation!
for (auto it = v.begin(); it != v.end(); it++) {
    if (*it == 5) v.push_back(10);  // BUG! iterator bisa invalid
}

// FIX: gunakan index-based loop atau kumpulkan dulu, push setelah loop
```

### Edge Cases yang Sering Miss

- **Vector kosong** → cek `v.empty()` sebelum akses `v[0]` atau `v.back()`
- **String kosong** → `s.substr(0, 0)` = `""`
- **N = 0** → loop tidak jalan, tapi hati-hati return value
- **Semua elemen sama** → `unique` tetap menyisakan 1 elemen

---

## 🏆 7. Tips Contest

### Kapan Pakai Vector vs Array Biasa?

| Gunakan Vector           | Gunakan Array `int a[N]` |
| ------------------------ | ------------------------ |
| Ukuran belum tahu        | Ukuran fixed & diketahui |
| Butuh push_back/pop_back | Hanya akses index        |
| Butuh sort/unique/erase  | Performance kritis       |
| Return dari fungsi       | Global array besar       |

### Red Flags yang Menandakan Pakai Container Ini

- "Simpan data lalu sort" → `vector` + `sort`
- "Cari elemen terkecil/terbesar ke-k" → `vector` + `sort` atau `nth_element`
- "Simpan koordinat (x, y)" → `vector<pair<int,int>>`
- "Sort by multiple criteria" → `vector<tuple<...>>`
- "Manipulasi string, balik, potong" → `string` operations
- "Hitung frekuensi karakter" → `string` + array `freq[26]`

### Speed Tips

```cpp
// 1. Reserve jika tahu ukuran (avoid reallocations)
vector<int> v;
v.reserve(n);  // alokasi kapasitas n, tapi size masih 0

// 2. emplace_back lebih cepat dari push_back untuk objects
v.emplace_back(x, y);  // construct in-place

// 3. Swap trick untuk free memory
vector<int>().swap(v);  // v sekarang benar-benar kosong (capacity = 0)

// 4. Avoid string concatenation in loop (pakai ostringstream)
// Atau cukup kumpulkan di vector lalu print
```

---

## 📌 8. Ringkasan

### Key Points

1. **Vector** = array dinamis, pakai untuk hampir semua kasus di CP
2. **String** = sequence of chars, banyak built-in functions berguna
3. **Pair** = 2 nilai terkait, sort otomatis by first lalu second
4. **Tuple** = 3+ nilai terkait, sort lexicographic

### Cheatsheet Singkat

```cpp
// VECTOR
vector<int> v(n); for(int &x:v) cin>>x;
sort(all(v));
v.erase(unique(all(v)), v.end());  // remove dup

// STRING
s.substr(pos, len); s.find("x"); reverse(all(s));
to_string(123); stoi("123");

// PAIR
pair<int,int> p = {a,b}; p.first; p.second;
vector<pii> vp; sort(all(vp)); // sort by first, then second

// TUPLE
auto [a,b,c] = make_tuple(1,2,3); // C++17
get<0>(t); get<1>(t); get<2>(t);
```

### Link Soal Latihan Online Judge

| Platform        | Problem            | Topik                  |
| --------------- | ------------------ | ---------------------- |
| CSES            | Distinct Numbers   | Vector + Sort + Unique |
| CSES            | Apartments         | Vector + Two Pointers  |
| Codeforces      | 1669A              | Basic Vector           |
| AtCoder ABC085B | Kagami Mochi       | Vector + Unique        |
| Codeforces      | 1807A              | String Processing      |
| CSES            | Palindrome Reorder | String + Freq Count    |
