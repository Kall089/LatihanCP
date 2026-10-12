# 📊 Day 29: Difference Array & Range Update Offline

> **Prasyarat:** Prefix Sum 1D (Day 28)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"tambahkan X ke semua elemen dari L sampai R"*, *"berapa banyak yang aktif pada waktu T"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 29, kamu akan mampu:

- [ ] Menjelaskan hubungan **difference array ↔ prefix sum** (keduanya saling membalik)
- [ ] Melakukan **range update** `a[L..R] += v` dalam **O(1)** per operasi
- [ ] Merekonstruksi array final dengan satu kali **prefix sum** O(N)
- [ ] Mengenali pola **sweep line / event counting** (berapa objek aktif pada suatu titik)
- [ ] Memperluas ke **Difference Array 2D** untuk update submatriks
- [ ] Menghindari jebakan **indeks r+1 di luar array** dan **overflow**

---

## 🔍 1. Konsep & Intuisi

### Apa itu Difference Array?

**Difference array** adalah array `diff` yang menyimpan **selisih antar elemen bertetangga** dari array asli `a`:

```
diff[0] = a[0]
diff[i] = a[i] - a[i-1]     untuk i ≥ 1
```

Kenapa ini berguna? Karena kalau kita jumlahkan `diff` dari depan (prefix sum), kita **mendapatkan kembali array aslinya**:

```
a[i] = diff[0] + diff[1] + ... + diff[i]
```

> **Difference array dan prefix sum adalah dua operasi yang saling membalik.**
> Prefix sum "menjumlahkan", difference array "menyelisihkan".
> Kalau prefix sum menjawab *query* rentang dengan cepat, difference array melakukan *update* rentang dengan cepat.

### Analogi kehidupan nyata: catatan gaji karyawan

Bayangkan kamu HRD dengan 100.000 karyawan. Direktur memberi 50.000 perintah seperti ini:

> "Naikkan gaji karyawan nomor 300 sampai 8.000 sebesar 1 juta."

**Cara naif:** buka file gaji, ubah 7.701 baris satu per satu. Ulangi 50.000 kali → sekitar 385 juta operasi. Terlalu lama.

**Cara difference array:** kamu cuma menulis **dua sticky note**:
- Sticky note di karyawan **300**: *"mulai dari sini, +1 juta"*
- Sticky note di karyawan **8.001**: *"mulai dari sini, −1 juta"* (efeknya berhenti)

Setiap perintah cuma butuh **2 tulisan**, tidak peduli rentangnya sepanjang apa. Di akhir hari, kamu berjalan sekali dari karyawan pertama sampai terakhir sambil menjumlahkan semua sticky note yang kamu lewati — dan gaji semua orang langsung benar.

### Mengapa penting di CP?

| Situasi | Tanpa difference array | Dengan difference array |
|---|---|---|
| Q update rentang | O(Q × N) | **O(Q + N)** |
| N = 10⁵, Q = 10⁵ | 10¹⁰ operasi → **TLE** | 2 × 10⁵ operasi → **AC** |

Difference array juga merupakan **fondasi** dari:
- Sweep line / event counting (Day 33)
- Segment tree dengan lazy propagation (Day 68) — versi "online"-nya
- Prefix sum 2D untuk update submatriks (Day 30)

### Kapan digunakan? (Pattern Recognition)

Gunakan difference array **jika dan hanya jika**:

1. ✅ Ada banyak operasi **update rentang** (`a[L..R] += v`)
2. ✅ **Semua update diberikan lebih dulu**, jawaban baru diminta di akhir → disebut **offline**
3. ✅ Tidak ada query di tengah-tengah update

❌ **Jangan pakai** kalau ada query *di antara* update (misalnya: update, tanya, update, tanya). Itu kasus **online** → pakai Segment Tree / BIT dengan lazy propagation.

### Visualisasi ASCII

Array awal semua nol, lalu operasi `[2..4] += 5`:

```
Indeks :   0    1    2    3    4    5    6
a      :   0    0    0    0    0    0    0

Tandai dua titik saja:
diff   :   0    0   +5    0    0   -5    0
                    ↑              ↑
              mulai naik      berhenti naik
              (indeks L)      (indeks R+1)

Jalan dari kiri sambil menjumlahkan (prefix sum):
berjalan:  0    0    5    5    5    0    0
a final :  0    0    5    5    5    0    0
                    └────────────┘
                    tepat rentang [2..4]
```

**Kenapa `-5` ditaruh di indeks R+1, bukan R?**
Karena efek `+5` harus tetap terasa **sampai dengan** indeks R. Kalau `-5` ditaruh di R, maka indeks R sendiri sudah dibatalkan — rentangnya jadi `[L..R-1]`, salah satu elemen kurang.

### Dua operasi yang saling membalik

```
        difference (selisih)
   a  ──────────────────────►  diff
   ▲                             │
   │                             │
   └─────────────────────────────┘
        prefix sum (jumlah)
```

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Kompleksitas | Penjelasan |
|---|---|---|
| Satu range update | **O(1)** | Hanya 2 penulisan: `diff[l] += v`, `diff[r+1] -= v` |
| Q kali range update | **O(Q)** | Tidak bergantung panjang rentang |
| Rekonstruksi array final | **O(N)** | Satu kali prefix sum |
| **Total** | **O(N + Q)** | |
| Memori | **O(N)** | Satu array tambahan berukuran N+1 |

### Perbandingan dengan pendekatan lain

| Pendekatan | Update | Query | Cocok untuk |
|---|---|---|---|
| Loop biasa | O(panjang rentang) | O(1) | Q sangat kecil |
| **Difference Array** | **O(1)** | **O(N) sekali di akhir** | **Offline, update banyak** |
| Prefix Sum | O(N) rebuild | O(1) | Query banyak, data statis |
| Segment Tree + Lazy | O(log N) | O(log N) | **Online**, update & query berselang-seling |
| BIT (Fenwick) | O(log N) | O(log N) | Online, kode lebih pendek dari segtree |

**Kapan approach ini optimal:**
Ketika N dan Q sama-sama besar (sampai 10⁶), semua update diketahui di awal, dan kita hanya perlu melihat hasil akhirnya. Difference array adalah solusi **tercepat dan paling sederhana** untuk kasus ini — jauh lebih pendek daripada segment tree.

---

## 💻 3. Implementasi C++

### 3.1 Difference Array 1D (paling sering dipakai)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // PENTING: ukuran n + 2, bukan n.
    // Kita butuh slot untuk indeks r+1 ketika r = n-1.
    vector<ll> diff(n + 2, 0);

    // ── Tahap 1: catat semua update dalam O(1) masing-masing ──
    for (int i = 0; i < q; i++) {
        int l, r;
        ll v;
        cin >> l >> r >> v;      // 1-indexed: tambah v ke a[l..r]
        diff[l] += v;            // mulai bertambah dari sini
        diff[r + 1] -= v;        // berhenti bertambah setelah r
    }

    // ── Tahap 2: rekonstruksi array final dengan prefix sum ──
    vector<ll> a(n + 1, 0);
    ll berjalan = 0;
    for (int i = 1; i <= n; i++) {
        berjalan += diff[i];     // akumulasi semua "sticky note"
        a[i] = berjalan;
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << " \n"[i == n];

    return 0;
}
```

### 3.2 Kalau array awalnya TIDAK nol

```cpp
// a[] sudah berisi nilai awal. Bangun diff dari a dulu.
vector<ll> bangunDiff(const vector<ll>& a, int n) {
    vector<ll> diff(n + 2, 0);
    for (int i = 1; i <= n; i++)
        diff[i] = a[i] - a[i - 1];   // a[0] dianggap 0
    return diff;
}

// ...lakukan semua update pada diff...

// Rekonstruksi (sama seperti sebelumnya)
void rekonstruksi(vector<ll>& diff, vector<ll>& a, int n) {
    for (int i = 1; i <= n; i++)
        a[i] = a[i - 1] + diff[i];
}
```

### 3.3 Versi hemat memori (tanpa array a terpisah)

```cpp
// diff langsung diubah jadi array hasil di tempat (in-place).
for (int i = 1; i <= n; i++)
    diff[i] += diff[i - 1];
// Sekarang diff[i] adalah nilai akhir a[i]. Hemat satu array.
```

### 3.4 Difference Array 2D (update submatriks)

```cpp
const int MAXN = 1005;
ll diff2[MAXN][MAXN];

// Tambahkan v ke seluruh submatriks (r1,c1) sampai (r2,c2)
void updateSubmatriks(int r1, int c1, int r2, int c2, ll v) {
    diff2[r1][c1]         += v;
    diff2[r1][c2 + 1]     -= v;
    diff2[r2 + 1][c1]     -= v;
    diff2[r2 + 1][c2 + 1] += v;   // dikurangi dua kali, kembalikan sekali
}

// Rekonstruksi: prefix sum 2D di tempat
void rekonstruksi2D(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            diff2[i][j] += diff2[i-1][j] + diff2[i][j-1] - diff2[i-1][j-1];
}
```

> **Empat titik, bukan dua.** Di 1D efek update "bocor" ke kanan sehingga butuh 1 penambal.
> Di 2D efek bocor ke kanan **dan** ke bawah, jadi butuh 3 penambal — dan pojok kanan-bawah
> terlanjur dikurangi dua kali, sehingga harus dikembalikan sekali (prinsip inklusi-eksklusi).

---

## 🔄 4. Trace / Simulasi

### Contoh: N = 7, tiga operasi update

```
Operasi:
  1) a[2..4] += 5
  2) a[3..6] += 3
  3) a[1..7] += 1
```

**Tahap 1 — catat semua update (masing-masing O(1)):**

| Operasi | diff[l] += v | diff[r+1] -= v | Isi diff setelahnya (indeks 1..8) |
|---|---|---|---|
| awal | — | — | `0 0 0 0 0 0 0 0` |
| a[2..4] += 5 | diff[2] += 5 | diff[5] -= 5 | `0 5 0 0 -5 0 0 0` |
| a[3..6] += 3 | diff[3] += 3 | diff[7] -= 3 | `0 5 3 0 -5 0 -3 0` |
| a[1..7] += 1 | diff[1] += 1 | diff[8] -= 1 | `1 5 3 0 -5 0 -3 -1` |

Perhatikan: hanya **6 penulisan** untuk 3 operasi, walaupun total elemen tersentuh 3+4+7 = 14.

**Tahap 2 — rekonstruksi dengan prefix sum (satu kali jalan):**

| i | diff[i] | berjalan (a[i]) | Penjelasan |
|---|---|---|---|
| 1 | +1 | **1** | Hanya operasi 3 yang aktif |
| 2 | +5 | **6** | Operasi 3 + operasi 1 mulai |
| 3 | +3 | **9** | Operasi 3 + 1 + 2 aktif semua |
| 4 | 0 | **9** | Tidak ada perubahan |
| 5 | −5 | **4** | Operasi 1 berhenti (rentangnya habis di 4) |
| 6 | 0 | **4** | Tidak ada perubahan |
| 7 | −3 | **1** | Operasi 2 berhenti (habis di 6) |

**Array final: `1 6 9 9 4 4 1`**

**Verifikasi manual (cara lambat):**

```
Indeks :   1    2    3    4    5    6    7
op 3   :  +1   +1   +1   +1   +1   +1   +1
op 1   :   .   +5   +5   +5    .    .    .
op 2   :   .    .   +3   +3   +3   +3    .
        ─────────────────────────────────
total  :   1    6    9    9    4    4    1   ✅ COCOK
```

### Diagram: kenapa r+1?

```
Operasi a[2..4] += 5

          i=1   i=2   i=3   i=4   i=5   i=6
diff  :    0    +5     0     0    -5     0
                 ↑                 ↑
          "nyalakan"         "matikan"
                             di i=5, BUKAN i=4

Efek berjalan:
          0     5     5     5     0     0
                └───────────────┘
                aktif di 2,3,4 — tepat 3 elemen ✅

Kalau -5 salah ditaruh di i=4:
diff  :    0    +5     0    -5     0     0
Efek  :    0     5     5     0     0     0
                └─────────┘
                cuma 2,3 — indeks 4 hilang ❌
```

---

## 📝 5. Variasi & Pattern

### Variasi 1: Mencari nilai maksimum setelah semua update

Tidak perlu menyimpan array final. Cukup lacak nilai berjalan:

```cpp
ll berjalan = 0, maksimum = 0;
for (int i = 1; i <= n; i++) {
    berjalan += diff[i];
    maksimum = max(maksimum, berjalan);
}
cout << maksimum << "\n";
```
*Contoh soal: CSES Traffic Lights (variasi), LeetCode 1109 Corporate Flight Bookings.*

### Variasi 2: Event counting / sweep line

"Ada N orang, masing-masing datang jam `s` dan pulang jam `e`. Berapa jumlah orang terbanyak yang ada di ruangan pada saat bersamaan?"

```cpp
// Orang ke-i hadir pada interval [s, e-1] (pulang jam e = sudah tidak ada)
for (int i = 0; i < n; i++) {
    int s, e;
    cin >> s >> e;
    diff[s]     += 1;   // satu orang masuk
    diff[e]     -= 1;   // satu orang keluar
}
// Prefix sum -> jumlah orang di tiap satuan waktu, ambil maksimumnya
```

> **Ini pola yang paling sering muncul di kontes.** Kata kuncinya: *"paling banyak bersamaan"*,
> *"jumlah interval yang menutupi titik X"*, *"ruangan minimal yang dibutuhkan"*.

### Variasi 3: Cek apakah kapasitas terlampaui

```cpp
// Mobil dengan kapasitas C, penumpang naik di from dan turun di to.
bool bisa = true;
ll penumpang = 0;
for (int i = 0; i <= maksTitik; i++) {
    penumpang += diff[i];
    if (penumpang > C) { bisa = false; break; }
}
```
*Contoh soal: LeetCode 1094 Car Pooling.*

### Variasi 4: Difference array pada nilai besar → coordinate compression

Kalau posisi mencapai 10⁹ tapi jumlah interval hanya 10⁵, jangan bikin array sebesar 10⁹. Kumpulkan semua titik penting (`l` dan `r+1`), urutkan, lalu pakai `map<int,ll>` atau kompresi koordinat.

```cpp
map<int, ll> ev;             // event terurut otomatis
for (auto [l, r, v] : updates) {
    ev[l]     += v;
    ev[r + 1] -= v;
}
ll berjalan = 0;
for (auto [posisi, delta] : ev) {
    berjalan += delta;       // nilai berlaku sampai event berikutnya
}
```

### Variasi 5: Update perkalian atau XOR

Difference array bekerja untuk operasi yang punya **kebalikan**:
- Penjumlahan ↔ pengurangan ✅ (paling umum)
- XOR ↔ XOR ✅ (`diff[l] ^= v; diff[r+1] ^= v;`)
- Perkalian ↔ pembagian ⚠️ (hati-hati bilangan bulat & nol)
- Maksimum ❌ **tidak bisa** — `max` tidak punya kebalikan

### Variasi 6: Difference array untuk barisan aritmetika

Untuk update `a[l..r] += (mulai, mulai+beda, mulai+2·beda, ...)`, pakai **difference dua tingkat**:

```cpp
diff[l]     += mulai;
diff[l + 1] += beda - mulai;
diff[r + 1] -= beda * (r - l + 1) + mulai - beda;  // hati-hati, turunkan sendiri
diff[r + 2] += beda * (r - l + 1) + mulai - beda - ... ;
// Lebih aman: pakai dua array diff bertingkat, lalu prefix sum dua kali.
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### ❌ Mistake 1: Ukuran array kurang (paling sering!)

```cpp
vector<ll> diff(n);          // ❌ SALAH
diff[r + 1] -= v;            // r = n-1 -> diff[n] -> OUT OF BOUNDS!

vector<ll> diff(n + 2, 0);   // ✅ BENAR, selalu sediakan 2 slot lebih
```

Ini menyebabkan *runtime error* atau — yang lebih jahat — **jawaban salah diam-diam** kalau pakai array statis global.

### ❌ Mistake 2: Menaruh pengurang di r, bukan r+1

```cpp
diff[r] -= v;       // ❌ rentang jadi [l..r-1], satu elemen hilang
diff[r + 1] -= v;   // ✅
```

Gejala: jawaban selalu meleset sedikit di ujung kanan rentang.

### ❌ Mistake 3: Overflow

```cpp
vector<int> diff(n + 2);     // ❌ kalau v sampai 10^9 dan Q sampai 10^5
// Nilai akhir bisa mencapai 10^14 -> jauh melewati batas int (~2.1 × 10^9)

vector<long long> diff(n + 2);  // ✅
```

### ❌ Mistake 4: Bingung 0-indexed vs 1-indexed

Kalau soal memberi indeks mulai dari 1, **pertahankan 1-indexed** di kode. Mencampur keduanya adalah sumber bug yang paling sulit dilacak. Konsistensi lebih penting daripada hemat satu slot memori.

```cpp
// Kalau soal 0-indexed dan kamu ingin memakai 1-indexed:
diff[l + 1] += v;
diff[r + 2] -= v;   // ingat: keduanya digeser +1
```

### ❌ Mistake 5: Memakai difference array padahal ada query di tengah

```
Input: update, update, TANYA, update, TANYA
```
Difference array **tidak bisa** menjawab ini secara efisien, karena rekonstruksi butuh O(N) tiap kali ditanya. Ini kasus **online** → gunakan **BIT** atau **Segment Tree dengan lazy propagation**.

### ❌ Mistake 6: Lupa reset antar test case

```cpp
// Kalau ada T test case dan diff adalah array global:
fill(diff, diff + n + 2, 0);   // ✅ WAJIB, jangan pakai memset untuk long long besar
```

### Edge Cases yang perlu diuji

| Kasus | Kenapa berbahaya |
|---|---|
| `l == r` (rentang 1 elemen) | Cek rumus tetap benar: `diff[l] += v`, `diff[l+1] -= v` |
| `r == n` (menyentuh ujung kanan) | `diff[n+1]` harus ada — inilah alasan ukuran n+2 |
| `v` negatif | Rumus tetap sama, tidak ada perlakuan khusus |
| Q = 0 (tidak ada update) | Array final harus sama dengan array awal |
| Semua update rentangnya penuh `[1..n]` | Hasil = jumlah semua v, cek overflow di sini |

---

## 🏆 7. Tips Contest

### Red flags — tanda soal ini pakai difference array

Kalau kamu menemukan kalimat berikut di soal, langsung curigai difference array:

- 🚩 *"Tambahkan X pada semua elemen dari indeks L sampai R"* + **N, Q ≥ 10⁵**
- 🚩 *"Setelah semua operasi, cetak array akhir / nilai maksimum"*
- 🚩 *"Berapa banyak interval yang menutupi titik ini?"*
- 🚩 *"Berapa jumlah maksimum yang aktif secara bersamaan?"*
- 🚩 *"Berapa ruangan/bus/petugas minimal yang dibutuhkan?"*
- 🚩 Semua query diberikan **di awal**, jawaban diminta **di akhir** (offline)

### Cara memutuskan dalam 10 detik

```
Ada update rentang?
├── Tidak → prefix sum biasa atau lainnya
└── Ya
    ├── Ada query DI ANTARA update? (online)
    │   └── Ya → Segment Tree + Lazy / BIT
    └── Tidak (semua update dulu, baru dibaca) → DIFFERENCE ARRAY ✅
```

### Time management

- Menulis difference array 1D: **≤ 3 menit**. Kalau lebih lama, kamu terlalu banyak berpikir — polanya cuma 2 baris.
- Selalu tulis `vector<long long> diff(n + 2, 0);` sebagai refleks. Dua hal sekaligus teratasi: overflow dan out-of-bounds.
- Jangan cetak array final kalau soal cuma minta maksimum — hemat waktu I/O.

### Trik implementasi

```cpp
// 1. Fungsi pembantu supaya tidak salah tulis rumus saat gugup
inline void tambah(vector<ll>& d, int l, int r, ll v) {
    d[l] += v;
    d[r + 1] -= v;
}

// 2. Rekonstruksi in-place, tidak perlu array kedua
for (int i = 1; i <= n; i++) d[i] += d[i - 1];

// 3. Untuk sweep line dengan koordinat besar, langsung pakai map
map<int, ll> ev;
```

### Kesalahan yang membuang waktu paling banyak di kontes

Membuat segment tree (60+ baris, 15 menit) untuk soal yang sebenarnya cukup difference array (5 baris, 2 menit). **Selalu cek dulu apakah soalnya offline.**

---

## 📌 8. Ringkasan & Cheatsheet

### Cheatsheet Singkat

```
╔══════════════════════════════════════════════════════════════╗
║  DIFFERENCE ARRAY — CHEATSHEET                               ║
╠══════════════════════════════════════════════════════════════╣
║  DEKLARASI                                                   ║
║    vector<long long> diff(n + 2, 0);   // WAJIB n+2          ║
║                                                              ║
║  RANGE UPDATE  a[l..r] += v      (O(1))                      ║
║    diff[l]     += v;                                         ║
║    diff[r + 1] -= v;             // r+1, BUKAN r             ║
║                                                              ║
║  REKONSTRUKSI  (O(n))                                        ║
║    for (int i = 1; i <= n; i++) diff[i] += diff[i - 1];      ║
║    // sekarang diff[i] = nilai akhir a[i]                    ║
║                                                              ║
║  DARI ARRAY AWAL YANG TIDAK NOL                              ║
║    for (int i = 1; i <= n; i++) diff[i] = a[i] - a[i - 1];   ║
║                                                              ║
║  2D — UPDATE SUBMATRIKS (r1,c1)..(r2,c2)                     ║
║    d[r1][c1] += v;        d[r1][c2+1] -= v;                  ║
║    d[r2+1][c1] -= v;      d[r2+1][c2+1] += v;                ║
║    // rekonstruksi = prefix sum 2D                           ║
║                                                              ║
║  KOMPLEKSITAS   Update O(1) | Rekonstruksi O(n) | Mem O(n)   ║
╚══════════════════════════════════════════════════════════════╝
```

### Key Points

1. **Difference array = kebalikan prefix sum.** Prefix sum mempercepat *query*, difference array mempercepat *update*.
2. **Kunci utamanya `r + 1`.** Efek update harus dimatikan *setelah* elemen terakhir, bukan pada elemen terakhir.
3. **Selalu `n + 2` dan `long long`.** Dua kebiasaan ini mencegah dua bug paling umum.
4. **Hanya untuk kasus offline.** Kalau ada query di tengah update, naik level ke segment tree dengan lazy.
5. **Sweep line adalah difference array yang menyamar.** Kata kunci "paling banyak bersamaan" hampir selalu berarti teknik ini.
6. **Di 2D butuh 4 titik**, bukan 2 — karena kebocoran terjadi ke dua arah.

### Hubungan dengan materi lain

```
Day 28: Prefix Sum 1D  ──┐
                         ├──► Day 29: DIFFERENCE ARRAY (kamu di sini)
Day 30: Prefix Sum 2D  ──┘            │
                                      ├──► Day 33: Sweep Line & Event
                                      └──► Day 68: Segment Tree + Lazy (versi online)
```

### Link Soal Latihan di Online Judge

**CSES Problem Set**
- [Room Allocation](https://cses.fi/problemset/task/1164) — sweep line klasik
- [Restaurant Customers](https://cses.fi/problemset/task/1619) — maksimum pengunjung bersamaan
- [Traffic Lights](https://cses.fi/problemset/task/1163) — variasi (butuh set)

**LeetCode**
- [1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/) — difference array paling murni
- [1094. Car Pooling](https://leetcode.com/problems/car-pooling/) — cek kapasitas
- [370. Range Addition](https://leetcode.com/problems/range-addition/) — versi dasar (premium)
- [2536. Increment Submatrices by One](https://leetcode.com/problems/increment-submatrices-by-one/) — difference array 2D

**Codeforces**
- [CF 276C - Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) — difference array + greedy
- [CF 1355C - Count Triangles](https://codeforces.com/problemset/problem/1355/C)
- [CF 466C - Number of Ways](https://codeforces.com/problemset/problem/466/C) — prefix sum

**AtCoder**
- [ABC183D - Water Heater](https://atcoder.jp/contests/abc183/tasks/abc183_d) — cek kapasitas dengan difference array
- [ABC188D - Snuke Prime](https://atcoder.jp/contests/abc188/tasks/abc188_d) — difference array + koordinat besar

---

*Selesai Day 29. Lanjut ke Day 30 (Prefix Sum 2D) untuk memperluas kedua teknik ini ke dua dimensi.*
