# 📊 Day 22: Aritmatika Modular

**Hari**: Day 22 dari 150 Hari Competitive Programming
**Topik**: Aritmatika Modular — Properties, (a+b)%m, (a*b)%m, Overflow Prevention
**Prerequisites**: Tipe data & overflow (Day 2), Loop dasar, Binary representation (Day 13)
**Difficulty**: ⭐⭐ (Easy–Intermediate, tapi FONDASI untuk Day 23–27)
**Learning Objectives**:
- Memahami definisi operasi modulo dan kongruensi (`a ≡ b (mod m)`)
- Menguasai 4 properti distributif modulo: penjumlahan, pengurangan, perkalian, pangkat
- Menangani **modulo bilangan negatif** dengan benar di C++
- Mencegah **integer overflow** saat mengalikan dua bilangan besar mod m
- Mengimplementasikan **binary exponentiation** (`modpow`) O(log n)
- Menghitung modulo dari bilangan SANGAT besar (ratusan digit) dengan Horner's rule
- Mengetahui apa yang **TIDAK** bisa dilakukan: pembagian modulo (preview Day 27)

---

## 🔍 1. Konsep & Intuisi

### Apa itu Modulo?

`a % m` (dibaca "a mod m") adalah **sisa** pembagian `a` oleh `m`.

```
17 % 5 = 2      karena 17 = 3×5 + 2
20 % 5 = 0      karena 20 = 4×5 + 0
 3 % 5 = 3      karena  3 = 0×5 + 3
```

Secara formal: `a = q·m + r` dengan `0 ≤ r < m`, maka `a % m = r`.

### Analogi: Jam Dinding

Modulo = **aritmatika melingkar**. Jam dinding adalah mod 12:

```
        12(0)
    11        1
  10            2
 9               3      Jam 10 + 5 jam = jam 3
  8             4       (10 + 5) % 12 = 15 % 12 = 3 ✓
    7        5
        6

Setelah mencapai 12, angka "membungkus" kembali ke 0.
```

Hari dalam seminggu = mod 7. Arah mata angin 90° = mod 360. Semua sistem yang "berputar" adalah aritmatika modular.

### Mengapa PENTING di Competitive Programming?

Banyak soal counting menghasilkan jawaban yang **astronomis besar** — misal "berapa banyak cara menyusun 10⁵ objek?" bisa mencapai 10^100000 digit. Tidak ada tipe data yang muat.

Solusi: soal meminta jawaban **modulo 10⁹+7**. Kita tidak perlu menyimpan angka raksasa — cukup jaga semua hasil antara tetap kecil dengan mengambil mod di setiap langkah.

```
Tanpa mod:  1 × 2 × 3 × ... × 100000  →  OVERFLOW di langkah ke-21
Dengan mod: ((1×2)%M ×3)%M ×4)%M ...  →  selalu < 10⁹+7, AMAN ✓
```

### Mengapa `10⁹ + 7`?

| Alasan | Penjelasan |
|--------|-----------|
| **Prima** | Membuat modular inverse selalu ada (Fermat, Day 27) |
| **Muat di `int`** | 10⁹+7 < 2³¹−1 ≈ 2.1×10⁹ |
| **Perkalian muat di `long long`** | (10⁹+7)² ≈ 10¹⁸ < 9.2×10¹⁸ ✓ |
| **Cukup besar** | Peluang collision/kebetulan jawaban 0 sangat kecil |

Varian lain yang sering muncul: `998244353` (prima, ramah NTT — Day 138), `10⁹+9`.

### Kongruensi

Notasi `a ≡ b (mod m)` dibaca "a kongruen b modulo m", artinya `m` habis membagi `(a − b)`.

```
17 ≡ 2 (mod 5)       karena 17 − 2 = 15 = 3×5
-3 ≡ 4 (mod 7)       karena -3 − 4 = -7 = -1×7
```

Semua bilangan yang kongruen mod m berada di **residue class** yang sama. Mod 5 membagi seluruh bilangan bulat menjadi 5 kelas:

```
kelas 0: ..., -10, -5,  0,  5, 10, ...
kelas 1: ...,  -9, -4,  1,  6, 11, ...
kelas 2: ...,  -8, -3,  2,  7, 12, ...
kelas 3: ...,  -7, -2,  3,  8, 13, ...
kelas 4: ...,  -6, -1,  4,  9, 14, ...
```

---

## 🧮 2. Properti Aritmatika Modular

Ini adalah **inti** dari Day 22. Hafalkan 4 aturan ini:

```
┌───────────────────────────────────────────────────────────────┐
│ (1) PENJUMLAHAN                                               │
│     (a + b) % m  =  ((a % m) + (b % m)) % m                   │
│                                                               │
│ (2) PENGURANGAN                                               │
│     (a − b) % m  =  ((a % m) − (b % m) + m) % m               │
│                     └──────────────────┬──┘                   │
│                        WAJIB +m agar tidak negatif!           │
│                                                               │
│ (3) PERKALIAN                                                 │
│     (a × b) % m  =  ((a % m) × (b % m)) % m                    │
│                                                               │
│ (4) PANGKAT                                                   │
│     (a ^ b) % m  =  ((a % m) ^ b) % m                          │
│                     → hitung dengan binary exponentiation      │
│                                                               │
│ (5) PEMBAGIAN  ❌ TIDAK BERLAKU!                              │
│     (a / b) % m  ≠  ((a % m) / (b % m)) % m                    │
│     → butuh MODULAR INVERSE (Day 27)                          │
└───────────────────────────────────────────────────────────────┘
```

### Bukti Singkat Properti Perkalian

Tulis `a = q₁m + r₁` dan `b = q₂m + r₂` (dengan `r₁ = a%m`, `r₂ = b%m`).

```
a × b = (q₁m + r₁)(q₂m + r₂)
      = q₁q₂m² + q₁m·r₂ + q₂m·r₁ + r₁r₂
      = m(q₁q₂m + q₁r₂ + q₂r₁) + r₁r₂
        └──────── kelipatan m ────────┘

Karena bagian pertama habis dibagi m:
(a × b) % m = (r₁ × r₂) % m = ((a%m) × (b%m)) % m  ∎
```

Bukti untuk penjumlahan analog. Inilah alasan kita boleh mengambil mod **kapan saja** di tengah perhitungan.

### Contoh Numerik

```
a = 17, b = 23, m = 5

(a + b) % m = 40 % 5 = 0
((a%5) + (b%5)) % 5 = (2 + 3) % 5 = 5 % 5 = 0        ✓

(a × b) % m = 391 % 5 = 1
((a%5) × (b%5)) % 5 = (2 × 3) % 5 = 6 % 5 = 1        ✓

(a − b) % m = -6 % 5 = -1  ← C++ beri NEGATIF!
((2 − 3) + 5) % 5 = 4 % 5 = 4                        ✓ (benar secara matematis)
```

---

## ⚠️ 3. Dua Jebakan Terbesar

### JEBAKAN A — Modulo Bilangan Negatif di C++

Di matematika, hasil `a mod m` selalu di rentang `[0, m−1]`. Tapi **C++ tidak**:

```cpp
cout << (-7 % 3);   // C++ output: -1   (bukan 2!)
cout << (-1 % 5);   // C++ output: -1   (bukan 4!)
```

C++ (sejak C++11) memakai **truncation toward zero**, sehingga tanda hasil mengikuti tanda operand kiri.

```
Garis bilangan mod 5:

matematis:   -7  -6  -5  -4  -3  -2  -1   0   1   2
             3   4   0   1   2   3   4    0   1   2

C++:         -7  -6  -5  -4  -3  -2  -1   0   1   2
            -2  -1   0  -4  -3  -2  -1    0   1   2
             ↑           ↑
             hasil NEGATIF — bahaya kalau dipakai sebagai index array!
```

**Fix universal:**

```cpp
// Normalisasi ke [0, m-1]
ll mod_norm(ll a, ll m) {
    return ((a % m) + m) % m;
}
```

Kenapa `((a % m) + m) % m` dan bukan `(a + m) % m`? Karena `a` bisa jauh lebih negatif dari `−m` (misal `a = -10⁹`, `m = 7`). `a % m` lebih dulu menyempitkan ke `(−m, m)`, baru `+m` menjamin positif, lalu `% m` mengembalikan ke rentang.

**Kapan ini menggigit di contest?**
- Rumus prefix sum modular: `(pre[r] - pre[l-1] + MOD) % MOD` ← lupa `+MOD` = WA
- Inclusion-exclusion: banyak pengurangan
- Hashing string: selisih hash (Day 33)
- Index array: `arr[(i - k) % n]` bisa jadi index negatif → **segfault**

### JEBAKAN B — Overflow Saat Perkalian

```cpp
const int MOD = 1e9 + 7;
int a = 1e9, b = 1e9;
int c = a * b % MOD;        // ❌ a*b overflow int SEBELUM % dijalankan
```

`a * b` dievaluasi lebih dulu sebagai `int × int → int`. Nilai 10¹⁸ tidak muat di 32-bit → **undefined behavior**.

```cpp
ll c = (ll)a * b % MOD;     // ✅ cast SATU operand → perkalian jadi 64-bit
```

**Aturan aman**: kalau dua nilai < 10⁹ dikalikan, hasilnya < 10¹⁸ → muat di `long long` (batas ≈ 9.22×10¹⁸). Selalu simpan variabel modular sebagai `long long`.

**Kalau MOD > ~3×10⁹?** Bahkan `long long` bisa overflow. Gunakan `__int128`:

```cpp
ll mulmod(ll a, ll b, ll m) {
    return (__int128)a * b % m;   // aman sampai m ≈ 9×10¹⁸
}
```

---

## 💻 4. Implementasi C++

### 4.1 Operasi Modular Dasar

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

// Normalisasi ke [0, MOD-1] — aman untuk input negatif
ll norm(ll a) { return ((a % MOD) + MOD) % MOD; }

ll addmod(ll a, ll b) { return (a + b) % MOD; }             // asumsi a,b sudah di [0,MOD)
ll submod(ll a, ll b) { return (a - b + MOD) % MOD; }       // +MOD cegah negatif
ll mulmod(ll a, ll b) { return (a % MOD) * (b % MOD) % MOD; }
```

Catatan: `addmod` aman karena `a + b < 2×10⁹ < 9.2×10¹⁸`.

### 4.2 Binary Exponentiation (modpow) — O(log n)

Menghitung `a^b mod m`. Naif O(b) terlalu lambat kalau `b = 10¹⁸`.

**Idea**: pecah eksponen menjadi biner.

```
a^13 = a^(1101₂) = a^8 × a^4 × a^1
       ↑ hanya bit yang menyala yang dikalikan
```

```cpp
ll modpow(ll base, ll exp, ll m = MOD) {
    ll result = 1;
    base %= m;
    if (base < 0) base += m;        // jaga-jaga base negatif
    while (exp > 0) {
        if (exp & 1)                // bit terakhir menyala?
            result = result * base % m;
        base = base * base % m;     // kuadratkan: a → a² → a⁴ → a⁸ ...
        exp >>= 1;                  // geser ke bit berikutnya
    }
    return result;
}
```

**Time**: O(log b) — sekitar 60 iterasi untuk `b = 10¹⁸`.
**Space**: O(1) (versi iteratif; versi rekursif O(log b) stack).

### 4.3 Modulo Bilangan Sangat Besar (Horner's Rule)

Input berupa string 1000 digit, hitung nilainya mod m.

```cpp
// Nilai bilangan = d0*10^(k-1) + d1*10^(k-2) + ... + dk-1
// Horner: value = (((d0*10 + d1)*10 + d2)*10 + ...) 
ll bigMod(const string& s, ll m) {
    ll res = 0;
    for (char c : s) {
        res = (res * 10 + (c - '0')) % m;   // ambil mod TIAP digit
    }
    return res;
}
```

`res < m ≤ 10⁹` dan `res*10 + 9 < 10¹⁰` → aman di `long long`.

### 4.4 Factorial Modular

```cpp
ll factmod(ll n, ll m = MOD) {
    ll res = 1;
    for (ll i = 2; i <= n; i++)
        res = res * i % m;      // mod tiap langkah → tidak pernah overflow
    return res;
}
```

### 4.5 Perkalian Aman untuk Modulus Besar

```cpp
ll mulmod_big(ll a, ll b, ll m) {
    return (__int128)a * b % m;
}

// Alternatif tanpa __int128 (binary multiplication, O(log b)):
ll mulmod_safe(ll a, ll b, ll m) {
    ll res = 0;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res + a) % m;
        a = (a * 2) % m;
        b >>= 1;
    }
    return res;
}
```

---

## 🔄 5. Trace & Simulasi

### Trace modpow(3, 13, 1000)

Target: `3^13 mod 1000`. Nilai asli `3^13 = 1594323` → `1594323 % 1000 = 323`.

Biner `13 = 1101₂`.

| Iterasi | exp | exp&1 | result (sebelum) | base | result (sesudah) | base (sesudah) |
|---------|-----|-------|------------------|------|------------------|----------------|
| 1 | 13 (1101) | 1 | 1 | 3 | 1×3 = **3** | 3²=**9** |
| 2 | 6 (110) | 0 | 3 | 9 | 3 (tidak berubah) | 9²=81 |
| 3 | 3 (11) | 1 | 3 | 81 | 3×81 = **243** | 81²=6561%1000=**561** |
| 4 | 1 (1) | 1 | 243 | 561 | 243×561=136323 %1000 = **323** | 561²%1000=721 |
| 5 | 0 | — | stop | | **323** ✓ | |

Hanya 4 iterasi, bukan 13. Untuk exp = 10¹⁸ → hanya 60 iterasi.

### Trace bigMod("12345", 7)

`12345 % 7`: 12345 = 1763×7 + 4 → jawaban **4**.

| Digit | res sebelum | res×10 + digit | % 7 |
|-------|-------------|----------------|-----|
| 1 | 0 | 0×10+1 = 1 | 1 |
| 2 | 1 | 1×10+2 = 12 | 5 |
| 3 | 5 | 5×10+3 = 53 | 4 |
| 4 | 4 | 4×10+4 = 44 | 2 |
| 5 | 2 | 2×10+5 = 25 | **4** ✓ |

### Trace Overflow yang Gagal vs Berhasil

```
MOD = 1_000_000_007
a = 999_999_999, b = 999_999_999

❌ int a*b   = 999999998000000001  → tidak muat di int32 (max 2147483647)
              → wrap-around jadi nilai sampah, hasil % MOD SALAH

✅ (ll)a*b   = 999999998000000001  → muat di int64 (max 9223372036854775807)
              → % MOD = 999999986000000049 ... 
              hasil akhir benar = 49
```

---

## 📝 6. Variasi & Pattern

| Pola Soal | Teknik |
|-----------|--------|
| "Jawab modulo 10⁹+7" | Ambil mod tiap operasi, simpan di `long long` |
| "Hitung aᵇ mod m, b ≤ 10¹⁸" | Binary exponentiation |
| "Bilangan 10⁵ digit mod m" | Horner's rule per digit |
| "Selisih dua prefix sum modular" | `(pre[r] - pre[l-1] + MOD) % MOD` |
| "Apakah a habis dibagi 3 / 9?" | Jumlah digit mod 3 / 9 |
| "Apakah habis dibagi 11?" | Alternating sum digit mod 11 |
| "Digit terakhir dari aᵇ" | `modpow(a, b, 10)` |
| "Angka ke-N dalam siklus" | `arr[N % period]` — cari periode dulu |
| "Jam / hari setelah X langkah" | `(start + X) % 12` atau `% 7` |
| "a/b mod p" | Modular inverse — Day 27 |

### Sifat Turunan yang Berguna

```
1. Cyclicity digit terakhir: aⁿ mod 10 berulang tiap ≤ 4
   2^1..2^5 mod 10 = 2,4,8,6,2  → periode 4

2. Uji habis dibagi:
   mod 2  → digit terakhir
   mod 3  → jumlah semua digit
   mod 4  → dua digit terakhir
   mod 5  → digit terakhir
   mod 9  → jumlah semua digit
   mod 11 → alternating sum digit

3. Fermat's Little Theorem (Day 27 preview):
   Jika p prima dan gcd(a,p)=1  →  a^(p-1) ≡ 1 (mod p)
   Konsekuensi: a^b mod p = a^(b mod (p-1)) mod p  (untuk b sangat besar)
```

---

## ⚠️ 7. Common Mistakes & Edge Cases

1. **Lupa `+MOD` pada pengurangan**
   ```cpp
   ans = (a - b) % MOD;          // ❌ bisa negatif
   ans = (a - b + MOD) % MOD;    // ✅
   ```

2. **Overflow karena tidak cast**
   ```cpp
   int res = a * b % MOD;        // ❌
   ll res = (ll)a * b % MOD;     // ✅
   ```

3. **Mengambil mod terlalu jarang** — dalam loop akumulasi, ambil mod tiap iterasi, bukan di akhir.

4. **Membagi langsung**
   ```cpp
   ans = (a / b) % MOD;          // ❌ TIDAK VALID
   ans = a * modpow(b, MOD-2) % MOD;  // ✅ (butuh MOD prima, Day 27)
   ```

5. **`MOD` dideklarasikan `int` lalu dipakai di ekspresi `int`** — deklarasikan `const ll MOD = 1e9+7;` untuk auto-promote perkalian.

6. **`INF` didefinisikan salah**
   ```cpp
   const int INF = 1e18;         // ❌ overflow — 1e18 tidak muat di int
   const ll INF = 1e18;          // ✅
   ```

7. **Hasil akhir 0 vs MOD** — jika jawaban ≡ 0, cetak `0`, bukan `MOD`. Normalisasi terakhir menjamin ini.

8. **`pow()` dari `<cmath>`** — mengembalikan `double`, kehilangan presisi untuk angka besar. Jangan pernah pakai `pow()` untuk modular exponentiation.

### Edge Cases yang Wajib Dicek

| Kasus | Perilaku benar |
|-------|----------------|
| `modpow(a, 0, m)` | = 1 (termasuk `modpow(0,0,m)` — konvensi CP: 1) |
| `modpow(0, b, m)`, b>0 | = 0 |
| `m = 1` | Semua hasil = 0 |
| `a = 0` dalam perkalian | Hasil 0, tidak error |
| Input negatif | Wajib `norm()` dulu |
| `n = 0` pada factorial | `0! = 1` |

---

## 🏆 8. Tips Contest

- **Deklarasikan di template**: `const ll MOD = 1e9+7;` + fungsi `modpow` sudah siap sebelum contest mulai.
- **Red flag "pakai modular"**: soal menyebut *"output the answer modulo 10⁹+7"*, atau constraint jawaban jelas overflow (`N ≤ 10⁵` tapi jawaban = kombinasi/faktorial).
- **Red flag "pakai modpow"**: eksponen `≤ 10¹⁸`, atau butuh modular inverse.
- **Debug WA di soal modular** — cek urutan ini:
  1. Ada pengurangan tanpa `+MOD`?
  2. Ada perkalian tanpa cast `(ll)`?
  3. `MOD` tipe `int` atau `ll`?
  4. Sudah normalisasi output akhir?
- **Stress test cepat**: bandingkan hasil modular dengan brute force `__int128` pada N kecil.
- **Jangan pakai `%` berlebihan** — `%` relatif lambat (~20–40 cycles). Untuk loop 10⁸, ganti dengan conditional subtract:
  ```cpp
  res += x; if (res >= MOD) res -= MOD;   // lebih cepat dari res = (res+x)%MOD
  ```

---

## 📌 9. Ringkasan & Cheatsheet

```cpp
// ═══════════ CHEATSHEET DAY 22 ═══════════
const ll MOD = 1e9 + 7;

ll norm(ll a)          { return ((a % MOD) + MOD) % MOD; }
ll add(ll a, ll b)     { return (a + b) % MOD; }
ll sub(ll a, ll b)     { return (a - b + MOD) % MOD; }
ll mul(ll a, ll b)     { return (a % MOD) * (b % MOD) % MOD; }

ll modpow(ll b, ll e, ll m = MOD) {
    ll r = 1; b %= m; if (b < 0) b += m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

ll bigMod(const string& s, ll m) {           // bilangan raksasa (string)
    ll r = 0; for (char c : s) r = (r * 10 + (c - '0')) % m; return r;
}

ll mulBig(ll a, ll b, ll m) { return (__int128)a * b % m; }  // m sampai 9e18
```

### Key Points

| Konsep | Ingat ini |
|--------|-----------|
| Distributif | `+`, `−`, `×`, `^` boleh di-mod kapan saja |
| Pembagian | ❌ TIDAK boleh — butuh inverse (Day 27) |
| Negatif | Selalu `((a % m) + m) % m` |
| Overflow | Cast `(ll)` sebelum perkalian; `__int128` untuk mod besar |
| Pangkat | Binary exponentiation O(log n), JANGAN `pow()` |
| Bilangan raksasa | Horner per digit |

### Latihan Online Judge

| Platform | Problem | Judul |
|----------|---------|-------|
| CSES | 1095 | Exponentiation |
| CSES | 1712 | Exponentiation II (tower, butuh Fermat) |
| Codeforces | 913A | Modular Exponentiation |
| Codeforces | 630I | Parking Lot (modpow) |
| AtCoder | ABC 156 D | Bouquet (modpow + inverse) |
| SPOJ | LASTDIG | Last Digit |
| SPOJ | ZSUM | Just Add It |
| LeetCode | 372 | Super Pow |
| LeetCode | 50 | Pow(x, n) |
| Project Euler | 48 | Self Powers |

---

**Next (Day 23)**: GCD & LCM — Euclidean algorithm, extended GCD, dan aplikasinya. Modular arithmetic hari ini akan langsung terpakai di sana.
