# Day 22 — Aritmatika Modular

## Deskripsi Topik

**Aritmatika Modular** adalah sistem bilangan yang "melingkar" — setelah mencapai modulus `m`, nilai membungkus kembali ke 0. Seperti jam dinding yang kembali ke 12 setiap putaran.

Di competitive programming, ini adalah **fondasi wajib**. Banyak soal counting menghasilkan jawaban astronomis (10^100000 digit), sehingga soal meminta jawaban `modulo 10^9+7`. Kita tidak pernah menyimpan angka raksasa itu — cukup jaga semua nilai antara tetap kecil dengan mengambil mod di setiap langkah.

Dua hal yang paling sering bikin WA di soal modular:
- **Modulo bilangan negatif** — C++ memberi hasil negatif, matematika tidak
- **Integer overflow saat perkalian** — `int * int` overflow sebelum `%` sempat jalan

Hari ini juga memperkenalkan **binary exponentiation** — algoritma O(log n) yang akan terpakai terus sampai Day 150.

---

## Tujuan Pembelajaran

- [ ] Memahami definisi modulo dan kongruensi (`a ≡ b (mod m)`)
- [ ] Menguasai 4 properti distributif: `+`, `−`, `×`, `^` boleh di-mod kapan saja
- [ ] Memahami **mengapa** pembagian modular TIDAK berlaku
- [ ] Menangani modulo bilangan negatif dengan `((a % m) + m) % m`
- [ ] Mencegah overflow: cast `(ll)` sebelum perkalian, `__int128` untuk modulus besar
- [ ] Mengimplementasikan **binary exponentiation** O(log n) dari nol
- [ ] Menghitung modulo bilangan 100.000 digit dengan Horner's rule
- [ ] Membangun prefix sum modular dengan pengurangan yang aman
- [ ] Mengenali pola soal yang butuh reduksi eksponen (Fermat)
- [ ] Memahami periodisitas modular sebagai teknik pemecahan soal

---

## Struktur Folder

```
Day-22 (Aritmatika Modular)/
├── README.md                       ← Panduan ini
├── teori/
│   └── Day_22_Teori_Lengkap.md    ← Teori lengkap + trace table + bukti
├── latihan/
│   ├── exercise_1.cpp             ← Sum & Product Array Mod M (warm-up)
│   ├── exercise_2.cpp             ← Modulo Bilangan Negatif
│   ├── exercise_3.cpp             ← Binary Exponentiation
│   ├── exercise_4.cpp             ← Modulo Bilangan Raksasa (Horner)
│   ├── exercise_5.cpp             ← Prefix Sum Modular + Range Query
│   └── exercise_6.cpp             ← Perkalian Modulus Besar (__int128)
├── solusi/
│   └── solution_1.cpp — solution_6.cpp
├── tugas/
│   └── tugas_01.cpp — tugas_15.cpp    ← 15 tugas mandiri (tanpa solusi)
└── template/
    └── template.cpp               ← Semua utilitas modular siap pakai
```

---

## Prerequisites

| Hari | Topik | Kenapa dibutuhkan |
|------|-------|-------------------|
| Day 2 | Tipe data & overflow | Inti dari pencegahan overflow modular |
| Day 13 | Bitmask | Binary exponentiation membaca eksponen bit per bit |
| Day 29 (preview) | Prefix sum | Dipakai di exercise_5 & tugas_09 |

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45–60 menit)
Baca `teori/Day_22_Teori_Lengkap.md` sampai habis. Yang wajib benar-benar dipahami:
- Bukti properti perkalian (kenapa boleh mod kapan saja)
- Diagram garis bilangan modulo negatif C++ vs matematis
- Trace table `modpow(3, 13, 1000)` — ikuti baris per baris dengan pensil

### Langkah 2 — Kerjakan Latihan (60–90 menit)
Kerjakan exercise 1–6 **tanpa melihat solusi**. Urutannya sengaja progresif:
properti dasar → negatif → modpow → bilangan raksasa → aplikasi → overflow ekstrem.

### Langkah 3 — Cek Solusi
Bandingkan approach kamu dengan `solusi/`. Semua solusi sudah dikompilasi
dan diverifikasi terhadap sample I/O.

```bash
g++ -std=c++17 -O2 -Wall -o sol solusi/solution_3.cpp
./sol < input.txt
```

### Langkah 4 — Kerjakan Tugas (120–150 menit)
- Easy: tugas_01–05 (**semua** harus dikerjakan)
- Medium: pilih minimal 3 dari tugas_06–10
- Hard: pilih minimal 2 dari tugas_11–15

### Langkah 5 — Online Judge
Submit ke CSES 1095 (Exponentiation) — itu adalah exercise_3 dalam bentuk aslinya.

---

## Ringkasan Latihan

| No | File | Topik | Kesulitan | Konsep Kunci |
|----|------|-------|-----------|--------------|
| 1 | exercise_1.cpp | Sum & Product Array Mod M | ★☆☆☆☆ | Properti distributif |
| 2 | exercise_2.cpp | Modulo Bilangan Negatif | ★★☆☆☆ | `((a%m)+m)%m` |
| 3 | exercise_3.cpp | Binary Exponentiation | ★★★☆☆ | modpow O(log n) |
| 4 | exercise_4.cpp | Modulo Bilangan Raksasa | ★★☆☆☆ | Horner's rule |
| 5 | exercise_5.cpp | Prefix Sum Modular | ★★★☆☆ | Pengurangan `+MOD` |
| 6 | exercise_6.cpp | Perkalian Modulus Besar | ★★★★☆ | `__int128` / binary mul |

---

## Ringkasan Tugas (15 Soal)

| No | Topik | Kesulitan | Kategori |
|----|-------|-----------|----------|
| 01 | Digit Terakhir dari A^B | ★☆☆☆☆ | Easy |
| 02 | Jumlah 1..N Mod M (jebakan pembagian) | ★☆☆☆☆ | Easy |
| 03 | Sisa Bagi Raksasa oleh 3 dan 9 | ★☆☆☆☆ | Easy |
| 04 | Jam Melingkar (mod 24, X negatif) | ★☆☆☆☆ | Easy |
| 05 | Rotasi Array Melingkar | ★★☆☆☆ | Easy |
| 06 | Fibonacci N ≤ 10^7 (iteratif) | ★★★☆☆ | Medium |
| 07 | Faktorial Modulo dengan Precompute | ★★★☆☆ | Medium |
| 08 | Deret Geometri Tanpa Pembagian | ★★★★☆ | Medium |
| 09 | Subarray Sum Habis Dibagi K | ★★★★☆ | Medium |
| 10 | Menara Pangkat A^(B^C) (Fermat) | ★★★★☆ | Medium |
| 11 | Fibonacci N ≤ 10^18 (Matrix Exp) | ★★★★☆ | Hard |
| 12 | Pasangan dengan Jumlah Habis Dibagi K | ★★★★☆ | Hard |
| 13 | Polynomial Hash Prefix | ★★★☆☆ | Hard |
| 14 | Jumlah Pangkat ∑ i^K | ★★★★☆ | Hard |
| 15 | Periodisitas: X² ≡ 1 (mod M) | ★★★★★ | Hard |

---

## Rekomendasi Online Judge

### CSES (cses.fi/problemset)
| Problem | Judul | Catatan |
|---------|-------|---------|
| 1095 | Exponentiation | Persis exercise_3 |
| 1712 | Exponentiation II | Menara pangkat, seperti tugas_10 |
| 1662 | Subarray Divisibility | Persis tugas_09 |
| 1079 | Binomial Coefficients | Butuh Day 27 juga |

### Codeforces
| Problem | Judul | Rating |
|---------|-------|--------|
| 913A | Modular Exponentiation | 1000 |
| 630I | Parking Lot | 1300 |
| 1279B | Verse For Santa | 1200 |
| 615D | Multipliers | 2000 (modpow + Fermat) |

### AtCoder
| Problem | Judul |
|---------|-------|
| ABC 156 D | Bouquet |
| ABC 034 C | Route |
| ABC 178 C | Ubiquity |

### SPOJ / LeetCode
| Platform | Problem | Judul |
|----------|---------|-------|
| SPOJ | LASTDIG | Last Digit (= tugas_01) |
| SPOJ | ZSUM | Just Add It |
| SPOJ | FLIB | Fibonacci with a Twist |
| LeetCode | 372 | Super Pow |
| LeetCode | 50 | Pow(x, n) |
| LeetCode | 974 | Subarray Sums Divisible by K (= tugas_09) |

---

## Kesalahan Umum (Common Mistakes)

1. **Lupa `+MOD` pada pengurangan.** `(a - b) % MOD` bisa menghasilkan nilai negatif. Selalu `(a - b + MOD) % MOD`. Ini penyebab WA nomor satu di soal modular.

2. **Overflow karena tidak cast.** `int a, b; int c = a * b % MOD;` — perkalian dievaluasi sebagai `int` dulu dan overflow SEBELUM `%` sempat jalan. Fix: `ll c = (ll)a * b % MOD;`

3. **Membagi langsung.** `(a / b) % MOD` tidak valid. Butuh modular inverse (Day 27), dan itu pun hanya kalau MOD prima. Untuk deret geometri, pakai divide & conquer (lihat tugas_08).

4. **`MOD` dideklarasikan `const int`.** Akibatnya ekspresi tetap dievaluasi sebagai `int`. Selalu `const ll MOD = 1e9 + 7;`

5. **`const int INF = 1e18;`** — 10^18 tidak muat di `int`. Harus `const ll INF = 1e18;`

6. **Memakai `pow()` dari `<cmath>`.** Mengembalikan `double` → kehilangan presisi untuk angka besar. Selalu tulis `modpow` sendiri.

7. **Modulo negatif dipakai sebagai index array.** `arr[(i - k) % n]` bisa menghasilkan index negatif → segfault, bukan sekadar jawaban salah. Lihat tugas_05.

8. **Lupa `1 % m` pada inisialisasi.** Kalau `m == 1`, `result = 1` salah — harus `result = 1 % m` agar jadi 0.

9. **Mengambil mod terlalu jarang.** Dalam loop akumulasi, ambil mod tiap iterasi, bukan sekali di akhir.

10. **Menukar modulus basis dan eksponen** pada soal Fermat. Basis di-mod `p`, eksponen di-mod `p−1`. Tertukar = jawaban salah.

---

## Quick Reference Cheatsheet

### Empat Properti Inti

```
(a + b) % m  =  ((a % m) + (b % m)) % m
(a − b) % m  =  ((a % m) − (b % m) + m) % m      ← +m WAJIB
(a × b) % m  =  ((a % m) × (b % m)) % m
(a ^ b) % m  =  binary exponentiation

(a / b) % m  =  ❌ TIDAK VALID — butuh modular inverse (Day 27)
```

### Snippet Wajib Hafal

```cpp
const ll MOD = 1e9 + 7;

// Normalisasi (untuk nilai yang mungkin negatif)
ll norm(ll a) { return ((a % MOD) + MOD) % MOD; }

// Binary exponentiation — O(log e)
ll modpow(ll b, ll e, ll m = MOD) {
    ll r = 1 % m; b %= m; if (b < 0) b += m;
    while (e > 0) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

// Bilangan raksasa (string) mod m — Horner
ll bigMod(const string& s, ll m) {
    ll r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % m;
    return r;
}

// Perkalian aman untuk m sampai ~9×10^18
ll mulBig(ll a, ll b, ll m) { return (__int128)a * b % m; }

// Range sum modular
ll rangeSum = (pre[r] - pre[l-1] + MOD) % MOD;   // +MOD WAJIB
```

### Batas Aman Tipe Data

```
int        : sampai  2.147 × 10^9
long long  : sampai  9.223 × 10^18
__int128   : sampai  1.701 × 10^38

MOD = 10^9+7  →  MOD² ≈ 10^18  →  aman di long long  ✓
MOD = 10^18   →  MOD² ≈ 10^36  →  butuh __int128     ⚠
```

### Uji Habis Dibagi (dari sifat 10^k mod m)

```
mod 2  → digit terakhir
mod 3  → jumlah semua digit
mod 4  → dua digit terakhir
mod 5  → digit terakhir
mod 8  → tiga digit terakhir
mod 9  → jumlah semua digit
mod 11 → alternating sum digit
```

---

## Checklist Sebelum Lanjut ke Day 23

- [ ] Bisa menjelaskan **mengapa** boleh mengambil mod di tengah perhitungan
- [ ] Bisa menulis `modpow` dari ingatan tanpa melihat contoh
- [ ] Tahu persis kapan `+MOD` diperlukan dan kenapa
- [ ] Bisa menghitung apakah suatu perkalian akan overflow sebelum menulis kode
- [ ] Paham kenapa pembagian modular butuh perlakuan khusus
- [ ] Sudah menyelesaikan minimal 10 dari 15 tugas
- [ ] Sudah AC minimal 1 soal modular di online judge
- [ ] `template/template.cpp` sudah disimpan dan siap dipakai hari-hari berikutnya

---

## Preview Day 23 — GCD & LCM

Besok: **Euclidean algorithm** untuk GCD dalam O(log n), **extended GCD**, dan LCM.

Koneksi ke hari ini:
- Extended GCD adalah cara **umum** mencari modular inverse (berlaku untuk MOD yang tidak prima — Fermat tidak bisa)
- `gcd(a, m) = 1` adalah syarat keberadaan inverse — konsep yang muncul di tugas_10 hari ini
- Chinese Remainder Theorem (Day 137) menggabungkan modulo berbeda, dan itu berdiri di atas GCD + aritmatika modular

Rangkaian Day 22–27 adalah satu paket utuh: modular → GCD → prima → modpow → kombinatorika → inverse. Pastikan fondasi hari ini kokoh sebelum lanjut.
