# 📊 Day 30: Prefix Sum 2D & Submatrix Sum

**Hari**: Day 30 dari 308 Hari Competitive Programming
**Topik**: Prefix Sum 2D, Submatrix Sum Query, 2D Range Queries
**Prerequisites**: Prefix Sum 1D (Day 29), Array 2D, Nested loops
**Difficulty**: ⭐⭐
**Learning Objectives**:
- Memahami konsep dan intuisi prefix sum 2D (tabel integral)
- Membangun tabel prefix sum 2D dari matriks
- Menjawab submatrix sum query dalam O(1)
- Menerapkan inclusion-exclusion pada persegi panjang 2D
- Menyelesaikan variasi soal: max submatrix sum, counting, frequency

---

## 🔍 1. Konsep & Intuisi

### Apa itu Prefix Sum 2D?

Prefix Sum 2D adalah **perluasan prefix sum 1D ke dimensi dua** (matriks). Jika pada 1D kita menyimpan jumlah kumulatif dari kiri ke kanan, pada 2D kita menyimpan **jumlah kumulatif dari pojok kiri-atas (1,1) sampai sel (i,j)**.

**Analogi kehidupan nyata:**
Bayangkan kamu punya peta curah hujan berbentuk grid. Kamu ingin tahu total curah hujan di suatu area persegi panjang. Tanpa prefix sum 2D, kamu harus menjumlahkan satu-satu semua sel di area itu. Dengan prefix sum 2D, kamu cukup menghitung **4 operasi aritmatika** saja!

### Mengapa penting di CP?

- Banyak soal CP melibatkan **query berulang** pada submatriks
- Tanpa prefix sum 2D: setiap query O(R×C) → TLE untuk Q banyak
- Dengan prefix sum 2D: setiap query O(1) setelah preprocessing O(N×M)

### Kapan digunakan? (Pattern Recognition)

Gunakan Prefix Sum 2D ketika:
1. ✅ Diberikan matriks 2D dan **banyak query** "jumlah elemen di submatriks (r1,c1) sampai (r2,c2)"
2. ✅ Soal melibatkan **submatriks dengan ukuran tetap** (fixed-size submatrix)
3. ✅ Perlu menghitung **frekuensi** elemen tertentu di area 2D
4. ✅ Gabungan prefix sum 2D + binary search / two pointers
5. ✅ Soal tentang "berapa banyak submatriks yang jumlahnya = k"

**Red flag kata kunci:** "submatrix", "rectangular region", "sum in rectangle", "2D grid query"

### Definisi Formal

Diberikan matriks `A[1..N][1..M]`, definisikan:

```
psum[i][j] = Σ A[r][c] untuk semua 1 ≤ r ≤ i, 1 ≤ c ≤ j
```

Atau secara intuitif: `psum[i][j]` = jumlah semua elemen di persegi panjang dari `(1,1)` sampai `(i,j)`.

### Visualisasi ASCII

**Matriks asli A (4×4):**
```
     c=1  c=2  c=3  c=4
r=1 [  1    2    3    4 ]
r=2 [  5    6    7    8 ]
r=3 [  9   10   11   12 ]
r=4 [ 13   14   15   16 ]
```

**Prefix Sum psum[i][j]:**
```
     c=0  c=1   c=2   c=3   c=4
r=0 [  0    0     0     0     0 ]   ← baris 0 = 0
r=1 [  0    1     3     6    10 ]
r=2 [  0    6    14    24    36 ]
r=3 [  0   15    33    54    78 ]
r=4 [  0   28    60    96   136 ]
         ↑
     kolom 0 = 0
```

Contoh: `psum[2][3] = 1+2+3+5+6+7 = 24` (semua elemen di kotak (1,1)→(2,3))

### Prinsip Inclusion-Exclusion

Untuk membangun `psum[i][j]`, kita gunakan prinsip inklusi-eksklusi:

```
psum[i][j] = A[i][j] 
           + psum[i-1][j]     ← daerah di atas
           + psum[i][j-1]     ← daerah di kiri
           - psum[i-1][j-1]   ← daerah yang dihitung dua kali (kurangi)
```

**Visualisasi:**
```
┌───────────┬────┐
│           │    │
│  psum     │ b  │  psum[i-1][j] = a + b
│  [i-1]    │    │  psum[i][j-1] = a + c
│  [j-1]=a  │    │  psum[i-1][j-1] = a
│           │    │
├───────────┼────┤
│     c     │A[i]│  psum[i][j] = a+b + a+c - a + A[i][j]
│           │[j] │            = a + b + c + A[i][j] ✓
└───────────┴────┘
```

### Query: Jumlah Submatriks (r1,c1) → (r2,c2)

Untuk menjawab query "jumlah elemen dari (r1,c1) sampai (r2,c2)":

```
sum = psum[r2][c2] 
    - psum[r1-1][c2]     ← hapus bagian atas
    - psum[r2][c1-1]     ← hapus bagian kiri
    + psum[r1-1][c1-1]   ← tambah kembali yang dikurangi dua kali
```

**Visualisasi Query:**
```
┌──────────┬──────────┐
│          │          │
│    A     │    B     │  Kita ingin area D saja
│          │          │
├──────────┼──────────┤
│          │//////////│
│    C     │/// D ////│  sum(D) = psum[r2][c2]
│          │//////////│         - psum[r1-1][c2]  (hapus A+B)
│          │//////////│         - psum[r2][c1-1]  (hapus A+C)
└──────────┴──────────┘         + psum[r1-1][c1-1] (A dihapus 2×, tambah balik)
```

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Brute Force | Prefix Sum 2D |
|---------|-------------|---------------|
| **Preprocessing** | - | O(N × M) |
| **Satu Query** | O(N × M) | O(1) |
| **Q Queries** | O(Q × N × M) | O(N × M + Q) |

- **Space Complexity**: O(N × M) untuk tabel prefix sum
- **Kapan optimal**: Ketika Q ≥ 2 (lebih dari 1 query), prefix sum 2D selalu lebih baik
- **Kapan tidak perlu**: Jika hanya 1 query dan N,M kecil, brute force cukup

### Perbandingan dengan pendekatan lain:

| Pendekatan | Build | Query | Update | Cocok untuk |
|------------|-------|-------|--------|-------------|
| Brute force | O(1) | O(N×M) | O(1) | Query sedikit |
| **Prefix Sum 2D** | **O(N×M)** | **O(1)** | **Rebuild O(N×M)** | **Query banyak, STATIC** |
| Segment Tree 2D | O(N×M) | O(log N × log M) | O(log N × log M) | Query + Update dinamis |
| Fenwick Tree 2D | O(N×M log² ) | O(log N × log M) | O(log N × log M) | Query + Update dinamis |

---

## 💻 3. Implementasi C++

### 3.1 Build Prefix Sum 2D

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    // 1-indexed: baris 1..n, kolom 1..m
    // Baris 0 dan kolom 0 = 0 (padding)
    vector<vector<long long>> a(n + 1, vector<long long>(m + 1, 0));
    vector<vector<long long>> psum(n + 1, vector<long long>(m + 1, 0));
    
    // Baca matriks
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    
    // Build prefix sum 2D
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            psum[i][j] = a[i][j]
                       + psum[i-1][j]      // atas
                       + psum[i][j-1]      // kiri
                       - psum[i-1][j-1];   // overlap
        }
    }
    
    // Query: jumlah submatriks (r1,c1) → (r2,c2)
    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        
        long long sum = psum[r2][c2]
                      - psum[r1-1][c2]
                      - psum[r2][c1-1]
                      + psum[r1-1][c1-1];
        
        cout << sum << '\n';
    }
    
    return 0;
}
```

### 3.2 Prefix Sum 2D dengan Array Statis (Lebih Cepat)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
long long a[MAXN][MAXN];
long long psum[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    // Baca matriks (1-indexed)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    
    // Build prefix sum 2D
    // Baris 0 dan kolom 0 otomatis 0 (global array)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            psum[i][j] = a[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
    
    // Fungsi query
    // sum(r1, c1, r2, c2) = jumlah elemen di submatriks [r1..r2][c1..c2]
    auto query = [&](int r1, int c1, int r2, int c2) -> long long {
        return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
    };
    
    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        cout << query(r1, c1, r2, c2) << '\n';
    }
    
    return 0;
}
```

### 3.3 Prefix Sum 2D pada Matriks 0-indexed

```cpp
// Jika input 0-indexed (baris 0..n-1, kolom 0..m-1):
// Cara 1: Shift ke 1-indexed saat baca
// Cara 2: Buat psum berukuran (n+1)×(m+1), offset +1

// Contoh konversi:
// a[0..n-1][0..m-1] → psum[0..n][0..m]
// psum[i][j] = jumlah elemen a[0..i-1][0..j-1]

for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        psum[i][j] = a[i-1][j-1] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];

// Query (r1,c1) → (r2,c2) dalam 0-indexed:
// sum = psum[r2+1][c2+1] - psum[r1][c2+1] - psum[r2+1][c1] + psum[r1][c1]
```

---

## 🔄 4. Trace / Simulasi

### Contoh: Matriks 3×4

```
Input matriks A (1-indexed):
     c=1  c=2  c=3  c=4
r=1 [  1    2    3    4 ]
r=2 [  5    6    7    8 ]
r=3 [  9   10   11   12 ]
```

**Step 1: Inisialisasi psum (semua 0)**
```
     c=0  c=1  c=2  c=3  c=4
r=0 [  0    0    0    0    0 ]
r=1 [  0    ?    ?    ?    ? ]
r=2 [  0    ?    ?    ?    ? ]
r=3 [  0    ?    ?    ?    ? ]
```

**Step 2: Isi psum baris per baris, kolom per kolom**

```
psum[1][1] = A[1][1] + psum[0][1] + psum[1][0] - psum[0][0]
           = 1       + 0          + 0          - 0
           = 1

psum[1][2] = A[1][2] + psum[0][2] + psum[1][1] - psum[0][1]
           = 2       + 0          + 1          - 0
           = 3

psum[1][3] = 3 + 0 + 3 - 0 = 6
psum[1][4] = 4 + 0 + 6 - 0 = 10

psum[2][1] = 5 + 1 + 0 - 0 = 6
psum[2][2] = 6 + 3 + 6 - 1 = 14
psum[2][3] = 7 + 6 + 14 - 3 = 24
psum[2][4] = 8 + 10 + 24 - 6 = 36

psum[3][1] = 9 + 6 + 0 - 0 = 15
psum[3][2] = 10 + 14 + 15 - 6 = 33
psum[3][3] = 11 + 24 + 33 - 14 = 54
psum[3][4] = 12 + 36 + 54 - 24 = 78
```

**Hasil psum:**
```
     c=0  c=1   c=2   c=3   c=4
r=0 [  0    0     0     0     0 ]
r=1 [  0    1     3     6    10 ]
r=2 [  0    6    14    24    36 ]
r=3 [  0   15    33    54    78 ]
```

**Step 3: Contoh Query**

Query: Jumlah submatriks dari (2,2) sampai (3,4)

```
Submatriks yang dimaksud:
[  6    7    8 ]
[ 10   11   12 ]

Jawaban seharusnya: 6+7+8+10+11+12 = 54

Hitung dengan rumus:
sum = psum[3][4] - psum[1][4] - psum[3][1] + psum[1][1]
    = 78         - 10         - 15         + 1
    = 54  ✓
```

Query: Jumlah submatriks dari (1,1) sampai (2,3)

```
Submatriks:
[ 1   2   3 ]
[ 5   6   7 ]

Jawaban: 1+2+3+5+6+7 = 24

sum = psum[2][3] - psum[0][3] - psum[2][0] + psum[0][0]
    = 24         - 0          - 0          + 0
    = 24  ✓
```

Query: Satu sel (2,3)

```
sum = psum[2][3] - psum[1][3] - psum[2][2] + psum[1][2]
    = 24         - 6          - 14         + 3
    = 7  ✓  (yang ada di A[2][3])
```

---

## 📝 5. Variasi & Pattern

### Variasi 1: Maximum Sum Submatrix (Fixed Size K×L)

Diberikan matriks N×M, cari submatriks berukuran K×L dengan jumlah terbesar.

```cpp
long long max_sum = LLONG_MIN;
for (int i = K; i <= n; i++) {
    for (int j = L; j <= m; j++) {
        // Submatriks kiri-atas = (i-K+1, j-L+1), kanan-bawah = (i, j)
        long long sum = query(i - K + 1, j - L + 1, i, j);
        max_sum = max(max_sum, sum);
    }
}
```

### Variasi 2: Count Submatrix with Sum = Target

Jumlah submatriks (r1,c1)→(r2,c2) yang sumnya tepat = target.

```cpp
// Pendekatan: Fixkan kolom kiri (c1) dan kanan (c2),
// kompres baris jadi 1D prefix sum, lalu gunakan teknik 1D (hashmap)
long long count = 0;
for (int c1 = 1; c1 <= m; c1++) {
    // row_sum[i] = jumlah baris i dari kolom c1 sampai c2
    vector<long long> row_sum(n + 1, 0);
    for (int c2 = c1; c2 <= m; c2++) {
        for (int i = 1; i <= n; i++)
            row_sum[i] += a[i][c2];
        
        // Sekarang cari subarray 1D dengan jumlah = target
        unordered_map<long long, int> freq;
        freq[0] = 1;
        long long curr = 0;
        for (int i = 1; i <= n; i++) {
            curr += row_sum[i];
            if (freq.count(curr - target))
                count += freq[curr - target];
            freq[curr]++;
        }
    }
}
```

### Variasi 3: Prefix Sum 2D untuk Boolean / Counting

Menghitung jumlah elemen yang memenuhi kondisi tertentu di submatriks.

```cpp
// Contoh: hitung jumlah sel bernilai ganjil di submatriks
vector<vector<int>> odd(n + 1, vector<int>(m + 1, 0));
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        odd[i][j] = (a[i][j] % 2 == 1 ? 1 : 0);

// Build prefix sum pada matriks odd
// Query: berapa sel ganjil di submatriks (r1,c1)→(r2,c2)?
```

### Variasi 4: Difference Array 2D (Range Update)

Update semua elemen di submatriks (r1,c1)→(r2,c2) dengan +val secara efisien.

```cpp
// Difference array 2D: update O(1) per query, reconstruct O(N×M) di akhir
long long diff[MAXN][MAXN] = {};

void range_add(int r1, int c1, int r2, int c2, long long val) {
    diff[r1][c1]     += val;
    diff[r1][c2+1]   -= val;
    diff[r2+1][c1]   -= val;
    diff[r2+1][c2+1] += val;
}

// Reconstruct: prefix sum 2D pada diff[][]
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
// Sekarang diff[i][j] = nilai akhir dari update-update
```

### Variasi 5: Prefix Sum 2D pada Grid dengan Karakter

```cpp
// Hitung jumlah '#' di submatriks
// Buat matriks 0/1: cnt[i][j] = (grid[i][j] == '#' ? 1 : 0)
// Lalu prefix sum pada cnt
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### Mistake 1: Lupa Padding Baris 0 / Kolom 0
```cpp
// ❌ SALAH: tidak ada padding → akses psum[-1][j] = UB!
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        psum[i][j] = a[i][j] + psum[i-1][j] + ...  // i-1 = -1 saat i=0!

// ✅ BENAR: gunakan 1-indexed dengan baris/kolom 0 = 0
```

### Mistake 2: Overflow pada long long
```cpp
// Jika N,M ≤ 1000 dan A[i][j] ≤ 10^9:
// psum bisa sampai 1000 × 1000 × 10^9 = 10^15 → butuh long long!

// ❌ SALAH:
int psum[MAXN][MAXN];

// ✅ BENAR:
long long psum[MAXN][MAXN];
```

### Mistake 3: Urutan Query (r1 ≤ r2, c1 ≤ c2)
```cpp
// Pastikan r1 ≤ r2 dan c1 ≤ c2, jika tidak dijamin:
if (r1 > r2) swap(r1, r2);
if (c1 > c2) swap(c1, c2);
```

### Mistake 4: Off-by-one pada Konversi 0-indexed ↔ 1-indexed
```cpp
// Selalu konsisten! Pilih 1-indexed dari awal untuk prefix sum 2D.
// Jika soal 0-indexed, konversi dengan +1 saat baca.
```

### Mistake 5: Salah Rumus Inclusion-Exclusion
```cpp
// ❌ SALAH (typo umum):
psum[i][j] = a[i][j] + psum[i-1][j] + psum[i][j-1] + psum[i-1][j-1];
//                                                     ↑ harusnya MINUS!

// ✅ BENAR:
psum[i][j] = a[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
```

### Edge Cases:
1. **Matriks 1×1**: Query pada satu sel → `psum[1][1] - 0 - 0 + 0 = a[1][1]`
2. **Query seluruh matriks**: `psum[n][m]`
3. **Query satu baris**: `(r1,1)→(r1,m)` → `psum[r1][m] - psum[r1-1][m]`
4. **Query satu kolom**: `(1,c1)→(n,c1)` → `psum[n][c1] - psum[n][c1-1]`
5. **Elemen negatif**: Prefix sum tetap bekerja, hati-hati sum bisa negatif
6. **Matriks besar (1000×1000)**: Gunakan array statis, bukan vector (lebih cepat)

---

## 🏆 7. Tips Contest

### Kapan Pakai Prefix Sum 2D?

| Red Flag | Contoh |
|----------|--------|
| "Diberikan matriks, jawab Q query tentang submatriks" | Submatrix sum query |
| "Cari submatriks K×L dengan sum terbesar" | Fixed-size sliding window 2D |
| "Berapa submatriks dengan sum = X" | Kompresi baris + hashmap 1D |
| "Grid dengan '#' dan '.', hitung '#' di area" | Boolean prefix sum |
| "Update area persegi panjang, lalu query" | Difference array 2D |

### Time Management

1. **Coding prefix sum 2D: ± 3-5 menit** (jika sudah hafal rumus)
2. **Debug: Cek dengan tangan** pada matriks 2×2 atau 3×3
3. **Template**: Simpan template, copy-paste saat contest

### Trick Implementasi

```cpp
// Trick 1: Build langsung tanpa array a terpisah
// Baca input langsung ke psum, lalu transformasi in-place
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        cin >> psum[i][j];
        psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
    }

// Trick 2: Lambda untuk query (hindari copy-paste rumus)
auto query = [&](int r1, int c1, int r2, int c2) -> long long {
    return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
};

// Trick 3: Prefix sum 2D pada frekuensi karakter
// Buat 26 prefix sum 2D (satu per huruf) — berguna untuk counting query
```

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
════════════════════════════════════════════════════════════
  PREFIX SUM 2D — CHEATSHEET
════════════════════════════════════════════════════════════

BUILD (1-indexed, baris/kolom 0 = 0):
  psum[i][j] = a[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1]

QUERY sum(r1,c1 → r2,c2):
  = psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1]

KOMPLEKSITAS:
  Build : O(N × M)
  Query : O(1) per query
  Space : O(N × M)

INGAT:
  ✓ Gunakan 1-indexed (padding baris 0 & kolom 0)
  ✓ Gunakan long long jika sum bisa > 2×10⁹
  ✓ Pastikan r1 ≤ r2 dan c1 ≤ c2
  ✓ Rumus = inclusion-exclusion (+ + - untuk build, - - + untuk query)
════════════════════════════════════════════════════════════
```

### Key Points

1. **Prefix Sum 2D = perluasan prefix sum 1D ke 2 dimensi**
2. **Build O(N×M), Query O(1)** — sangat efisien untuk banyak query
3. **Kunci**: Pahami prinsip inclusion-exclusion pada persegi panjang
4. **1-indexed**: Selalu gunakan 1-indexed untuk menghindari akses di luar batas
5. **Long long**: Selalu pertimbangkan overflow
6. **Variasi penting**: Fixed-size submatrix sum, boolean counting, difference array 2D

### Link Soal Latihan di Online Judge

| Platform | Soal | Deskripsi |
|----------|------|-----------|
| CSES | [Forest Queries](https://cses.fi/problemset/task/1652) | Hitung pohon di area persegi panjang |
| Codeforces | [CF 1722D - Line](https://codeforces.com/contest/1722/problem/D) | 2D prefix sum application |
| Codeforces | [CF 611C - New Year and Domino](https://codeforces.com/contest/611/problem/C) | Prefix sum 2D counting |
| LeetCode | [304. Range Sum Query 2D](https://leetcode.com/problems/range-sum-query-2d-immutable/) | Submatrix sum immutable |
| LeetCode | [1314. Matrix Block Sum](https://leetcode.com/problems/matrix-block-sum/) | Block sum fixed radius |
| AtCoder | [ABC106D - AtCoder Express 2](https://atcoder.jp/contests/abc106/tasks/abc106_d) | 2D counting |
| SPOJ | [MATSUM](https://www.spoj.com/problems/MATSUM/) | Matrix sum query |
