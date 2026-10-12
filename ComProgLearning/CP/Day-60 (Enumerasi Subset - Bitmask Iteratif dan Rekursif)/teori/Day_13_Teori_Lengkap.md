# Day 13 — Bitmask Enumeration: Teori Lengkap

## 1. Apa itu Bitmask?

**Bitmask** adalah teknik merepresentasikan suatu **himpunan** menggunakan bilangan bulat, di mana setiap bit (0 atau 1) menyatakan apakah suatu elemen ada di dalam himpunan atau tidak.

### Contoh Representasi

Misalkan kita punya 4 elemen: `{A, B, C, D}` dengan indeks `{0, 1, 2, 3}`.

| Bit | Elemen | Makna |
|-----|--------|-------|
| bit 0 (nilai 1) | A | A ada jika bit 0 = 1 |
| bit 1 (nilai 2) | B | B ada jika bit 1 = 1 |
| bit 2 (nilai 4) | C | C ada jika bit 2 = 1 |
| bit 3 (nilai 8) | D | D ada jika bit 3 = 1 |

Contoh: himpunan `{A, C}` → bit 0 dan bit 2 aktif → `0101` (biner) = **5** (desimal)

```
Desimal  Biner    Himpunan
   0     0000     {} (kosong)
   1     0001     {A}
   2     0010     {B}
   3     0011     {A, B}
   5     0101     {A, C}
   7     0111     {A, B, C}
  15     1111     {A, B, C, D}
```

### Keunggulan Bitmask
- Operasi set (cek/tambah/hapus elemen) dalam **O(1)**
- Representasi kompak: n elemen muat dalam 1 integer
- Cocok untuk **n ≤ 20** (int 32-bit) atau **n ≤ 60** (long long 64-bit)

---

## 2. Operator Bitwise

### 2.1 AND (`&`)
Hasil 1 hanya jika **kedua** bit adalah 1.

```
  1010   (10)
& 1100   (12)
------
  1000   (8)
```

**Kegunaan**: Cek apakah bit tertentu aktif, interseksi dua himpunan.

### 2.2 OR (`|`)
Hasil 1 jika **salah satu atau kedua** bit adalah 1.

```
  1010   (10)
| 0100   (4)
------
  1110   (14)
```

**Kegunaan**: Set sebuah bit, union dua himpunan.

### 2.3 XOR (`^`)
Hasil 1 jika **tepat satu** bit adalah 1 (berbeda).

```
  1010   (10)
^ 1100   (12)
------
  0110   (6)
```

**Kegunaan**: Toggle bit, cari elemen yang tidak berpasangan.

### 2.4 NOT (`~`)
Membalik semua bit (complement).

```
~  1010   (10)
= ...110101   (semua bit dibalik, termasuk bit tinggi)
```

**Kegunaan**: Membuat mask untuk clear bit.

### 2.5 Left Shift (`<<`)
Geser bit ke kiri sebanyak k posisi (kalikan 2^k).

```
  0001 << 3 = 1000   (1 × 8 = 8)
  0011 << 2 = 1100   (3 × 4 = 12)
```

**Kegunaan**: Membuat bitmask untuk bit ke-i: `1 << i`

### 2.6 Right Shift (`>>`)
Geser bit ke kanan sebanyak k posisi (bagi 2^k).

```
  1000 >> 3 = 0001   (8 ÷ 8 = 1)
  1100 >> 2 = 0011   (12 ÷ 4 = 3)
```

**Kegunaan**: Cek bit ke-i: `(mask >> i) & 1`

---

## 3. Operasi Bitmask Umum

### 3.1 Cek apakah bit ke-i aktif

```cpp
bool isSet = (mask >> i) & 1;
// atau
bool isSet = (mask & (1 << i)) != 0;
```

**Cara kerja**: Shift mask ke kanan i posisi, lalu AND dengan 1.
Jika hasil = 1, bit ke-i aktif; jika = 0, tidak aktif.

```
mask = 1010  (bit 3,1 aktif)
i = 1

mask >> 1 = 0101
0101 & 0001 = 0001  → bit 1 aktif ✓
```

### 3.2 Set bit ke-i (jadikan 1)

```cpp
mask = mask | (1 << i);
// atau
mask |= (1 << i);
```

```
mask = 1010, i = 2
1 << 2 = 0100
1010 | 0100 = 1110  → bit 2 sekarang aktif
```

### 3.3 Clear bit ke-i (jadikan 0)

```cpp
mask = mask & ~(1 << i);
// atau
mask &= ~(1 << i);
```

```
mask = 1110, i = 2
1 << 2 = 0100
~0100 = ...1011
1110 & ...1011 = 1010  → bit 2 dihapus
```

### 3.4 Toggle bit ke-i (balik: 0→1 atau 1→0)

```cpp
mask = mask ^ (1 << i);
// atau
mask ^= (1 << i);
```

```
mask = 1010, i = 1
1 << 1 = 0010
1010 ^ 0010 = 1000  → bit 1 di-toggle dari 1 → 0
```

### 3.5 Hitung jumlah bit aktif (popcount)

```cpp
int cnt = __builtin_popcount(mask);    // untuk int
int cnt = __builtin_popcountll(mask);  // untuk long long
```

```
mask = 1011  → 3 bit aktif
__builtin_popcount(0b1011) = 3
```

### 3.6 Lowest Set Bit (bit aktif paling kanan)

```cpp
int low = mask & -mask;   // nilai (bukan indeks)
int idx = __builtin_ctz(mask);  // indeks (count trailing zeros)
```

```
mask = 1100
-mask dalam two's complement = ...0100
mask & -mask = 0100  → lowest set bit adalah bit 2 (nilai 4)
```

### 3.7 Hapus Lowest Set Bit

```cpp
mask = mask & (mask - 1);
```

```
mask = 1100
mask - 1 = 1011
1100 & 1011 = 1000  → lowest set bit (bit 2) dihapus
```

**Kegunaan**: Iterasi semua bit aktif dalam O(jumlah bit aktif).

```cpp
int tmp = mask;
while (tmp) {
    int low = tmp & -tmp;   // ambil lowest bit
    int idx = __builtin_ctz(tmp);  // indeksnya
    // proses bit idx ...
    tmp &= tmp - 1;  // hapus lowest bit
}
```

---

## 4. Fungsi Builtin C++

| Fungsi | Keterangan | Contoh |
|--------|-----------|--------|
| `__builtin_popcount(x)` | Jumlah bit 1 (int) | `popcount(0b1011) = 3` |
| `__builtin_popcountll(x)` | Jumlah bit 1 (long long) | sama, tapi untuk ll |
| `__builtin_ctz(x)` | Count trailing zeros (indeks lowest bit) | `ctz(0b1100) = 2` |
| `__builtin_clz(x)` | Count leading zeros | `clz(1) = 31` (int 32-bit) |
| `__builtin_parity(x)` | 1 jika jumlah bit 1 ganjil | `parity(0b1011) = 1` |

---

## 5. Iterasi Semua Subset

### 5.1 Iterasi semua subset dari n elemen

```cpp
int n = 3;  // 3 elemen: {0, 1, 2}

for (int mask = 0; mask < (1 << n); mask++) {
    // mask merepresentasikan satu subset
    // bit i aktif = elemen i ada di subset ini
    
    cout << "Subset: {";
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) cout << i << " ";
    }
    cout << "}\n";
}
```

**Trace untuk n=3** (total 2^3 = 8 subset):

| mask (desimal) | Biner | Subset |
|---------------|-------|--------|
| 0 | 000 | {} |
| 1 | 001 | {0} |
| 2 | 010 | {1} |
| 3 | 011 | {0,1} |
| 4 | 100 | {2} |
| 5 | 101 | {0,2} |
| 6 | 110 | {1,2} |
| 7 | 111 | {0,1,2} |

**Kompleksitas**: O(2^n) untuk iterasi, O(n × 2^n) jika ada pemrosesan O(n) per subset.

### 5.2 Contoh: Subset Sum

Cari apakah ada subset dari array `a[]` yang jumlahnya = K.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    bool found = false;
    for (int mask = 0; mask < (1 << n); mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) sum += a[i];
        }
        if (sum == K) {
            found = true;
            // Cetak subset:
            cout << "Subset ditemukan: {";
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) cout << a[i] << " ";
            }
            cout << "}\n";
            break;
        }
    }
    
    if (!found) cout << "Tidak ada subset dengan jumlah " << K << "\n";
    return 0;
}
```

**Trace** untuk `a = {3, 1, 4, 2}`, `K = 5`:

| mask | Subset | Sum |
|------|--------|-----|
| 0101 | {3,4} | 7 |
| 0110 | {1,4} | 5 ✓ |

---

## 6. Iterasi Semua Subset dari Suatu Mask

Terkadang kita hanya ingin mengiterasi semua subset dari mask tertentu (bukan semua 2^n subset).

```cpp
int mask = 0b1010;  // hanya bit 1 dan bit 3 aktif

// Iterasi semua subset dari mask (kecuali empty set):
for (int sub = mask; sub > 0; sub = (sub-1) & mask) {
    // proses sub...
}
// Proses empty set (sub = 0) secara manual jika diperlukan
```

**Trace** untuk `mask = 1010` (bit 1 dan 3 aktif):

| sub | Biner | Subset dari {1,3} |
|-----|-------|------------------|
| 1010 | 1010 | {1,3} |
| 1000 | 1000 | {3} |
| 0010 | 0010 | {1} |
| 0000 | 0000 | {} (loop berhenti) |

**Kenapa `(sub-1) & mask`?**
- `sub - 1` membalik lowest set bit dari sub dan semua bit di bawahnya
- `& mask` memastikan kita hanya menggunakan bit-bit yang ada di mask

### Kenapa O(3^n)?

Setiap elemen dari n elemen bisa berada dalam 3 kondisi:
1. Tidak ada di mask (tidak pernah dipilih)
2. Ada di mask tapi tidak di sub
3. Ada di mask dan di sub

Sehingga total iterasi seluruh pasangan (mask, sub) = 3^n.

```cpp
// Total iterasi O(3^n):
for (int mask = 0; mask < (1 << n); mask++) {
    for (int sub = mask; sub > 0; sub = (sub-1) & mask) {
        // proses pasangan (mask, sub)
    }
}
```

---

## 7. Intro Bitmask DP

Bitmask DP digunakan ketika **state** permasalahan bergantung pada **himpunan elemen mana yang sudah dikunjungi/digunakan**.

**Kapan pakai Bitmask DP?**
- n kecil (biasanya n ≤ 20)
- State bergantung pada himpunan elemen yang sudah diproses
- Tanpa bitmask, state space terlalu besar

### Contoh: Hamiltonian Path (TSP)

**Problem**: Diberikan graph dengan n kota, cari rute terpendek yang mengunjungi semua kota tepat sekali.

**State**: `dp[mask][v]` = jarak terpendek untuk mengunjungi semua kota dalam `mask`, berakhir di kota `v`.

```cpp
int n;
vector<vector<int>> dist(n, vector<int>(n));  // jarak antar kota

// dp[mask][v] = jarak min mengunjungi semua di mask, terakhir di v
vector<vector<int>> dp(1 << n, vector<int>(n, INF));

// Base case: mulai dari kota 0
dp[1][0] = 0;  // mask = 000...001 (hanya kota 0), di kota 0, cost = 0

// Transisi
for (int mask = 1; mask < (1 << n); mask++) {
    for (int v = 0; v < n; v++) {
        if (dp[mask][v] == INF) continue;
        if (!((mask >> v) & 1)) continue;  // v harus ada di mask
        
        // Coba pergi ke kota u yang belum dikunjungi
        for (int u = 0; u < n; u++) {
            if ((mask >> u) & 1) continue;  // u sudah dikunjungi
            int newMask = mask | (1 << u);
            dp[newMask][u] = min(dp[newMask][u], dp[mask][v] + dist[v][u]);
        }
    }
}

// Jawaban: min dp[allVisited][v] untuk semua v
int allVisited = (1 << n) - 1;
int ans = INF;
for (int v = 0; v < n; v++) {
    ans = min(ans, dp[allVisited][v]);
}
```

**Kompleksitas**: O(n² × 2^n) waktu, O(n × 2^n) memori.

---

## 8. Common Pitfalls & Tips

### Pitfalls

**1. Integer overflow saat n >= 31**
```cpp
// SALAH jika i >= 31:
int mask = 1 << i;   // overflow!

// BENAR: gunakan long long
long long mask = 1LL << i;
```

**2. Operator precedence yang menyebabkan bug**
```cpp
// SALAH:
if (mask & 1 == 0)   // diinterpretasikan sebagai mask & (1 == 0) = mask & 0

// BENAR:
if ((mask & 1) == 0)
```

**3. Lupa empty set saat iterasi subset**
```cpp
// Loop ini SKIP sub = 0 (empty set):
for (int sub = mask; sub > 0; sub = (sub-1) & mask) { ... }

// Jika perlu proses empty set, tambahkan manual:
for (int sub = mask; sub > 0; sub = (sub-1) & mask) { /* ... */ }
// Proses sub = 0 di sini:
process(0);
```

**4. Signed vs unsigned right shift**
```cpp
int x = -1;
cout << (x >> 1);  // UB atau mengisi dengan sign bit (implementation-defined)

// Gunakan unsigned jika perlu right shift logis:
unsigned int ux = (unsigned int)x;
cout << (ux >> 1);  // selalu mengisi dengan 0
```

### Pro Tips

**Tip 1: `bitset<>` untuk n besar**
```cpp
bitset<1000> bs;
bs.set(5);     // set bit 5
bs.reset(3);   // clear bit 3
bs.count();    // jumlah bit aktif
```

**Tip 2: Iterasi bit aktif secara efisien**
```cpp
int tmp = mask;
while (tmp) {
    int i = __builtin_ctz(tmp);  // indeks lowest bit
    // proses elemen i...
    tmp &= tmp - 1;  // hapus lowest bit
}
```

**Tip 3: Cek apakah mask adalah subset dari super_mask**
```cpp
bool isSubset = (mask & super_mask) == mask;
```

**Tip 4: Complement dari mask (semua elemen yang TIDAK ada di mask)**
```cpp
int fullMask = (1 << n) - 1;
int complement = fullMask ^ mask;  // atau fullMask & ~mask
```

---

## 9. Contoh Lengkap — Encode/Decode Himpunan

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;  // 5 elemen: 0,1,2,3,4
    
    // Encode himpunan {0, 2, 4} sebagai bitmask
    int mask = 0;
    vector<int> elements = {0, 2, 4};
    for (int e : elements) {
        mask |= (1 << e);  // set bit ke-e
    }
    cout << "Mask untuk {0,2,4}: " << mask << " (biner: " << bitset<5>(mask) << ")\n";
    // Output: 21 (biner: 10101)
    
    // Decode bitmask ke himpunan
    cout << "Decode mask " << mask << ": {";
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) cout << i << " ";
    }
    cout << "}\n";
    
    // Operasi himpunan
    int setA = 0b10101;  // {0, 2, 4}
    int setB = 0b01110;  // {1, 2, 3}
    
    int unionAB = setA | setB;          // {0,1,2,3,4}
    int intersectAB = setA & setB;      // {2}
    int diffAB = setA & ~setB;          // A - B = {0,4}
    
    cout << "Union:     " << bitset<5>(unionAB) << "\n";
    cout << "Intersect: " << bitset<5>(intersectAB) << "\n";
    cout << "Diff A-B:  " << bitset<5>(diffAB) << "\n";
    
    return 0;
}
```

---

## Ringkasan

| Konsep | Rumus | Kompleksitas |
|--------|-------|-------------|
| Cek bit i | `(mask >> i) & 1` | O(1) |
| Set bit i | `mask \| (1 << i)` | O(1) |
| Clear bit i | `mask & ~(1 << i)` | O(1) |
| Toggle bit i | `mask ^ (1 << i)` | O(1) |
| Popcount | `__builtin_popcount(mask)` | O(1) |
| Lowest set bit | `mask & -mask` | O(1) |
| Hapus lowest bit | `mask & (mask-1)` | O(1) |
| Iterasi semua subset | `for mask in [0, 2^n)` | O(2^n) |
| Iterasi subset dari mask | `for sub = mask; sub > 0; sub = (sub-1)&mask` | O(subset count) |
| Total subset-of-subset | semua (mask, sub) pasangan | O(3^n) |
