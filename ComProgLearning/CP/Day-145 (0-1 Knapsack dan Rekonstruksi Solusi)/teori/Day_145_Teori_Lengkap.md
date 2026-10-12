# 📊 Day 145: 0/1 Knapsack & Rekonstruksi Solusi

> **Prasyarat:** Prinsip DP (Day 141), Rekursi & Memoization (Day 66), Meet in the Middle (Day 54)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"pilih barang"*, *"kapasitas"*, *"maksimalkan nilai"*, *"barang mana yang dipilih"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 145, kamu akan mampu:

- [ ] Menurunkan rekurens knapsack 0/1 dari definisi state
- [ ] Menulis versi **2D** dan versi **1D (rolling array)** dengan benar
- [ ] Menjelaskan kenapa loop kapasitas versi 1D harus **MUNDUR**
- [ ] **Merekonstruksi** barang mana yang dipilih, dengan dan tanpa tabel penuh
- [ ] Membedakan **0/1**, **unbounded**, dan **bounded** knapsack
- [ ] Memilih antara DP `O(nW)`, DP atas **nilai**, dan **meet in the middle**
- [ ] Mengenali knapsack yang menyamar (subset sum, partisi, penukaran uang)

---

## 🔍 1. Konsep & Intuisi

### Masalahnya

```
n barang; barang ke-i punya berat w[i] dan nilai v[i].
Tas berkapasitas W. Setiap barang boleh diambil PALING BANYAK SEKALI.
Maksimalkan total nilai tanpa melebihi kapasitas.
```

Kata **"paling banyak sekali"** itulah yang membuatnya *0/1* — setiap barang
punya keputusan biner: ambil atau tidak.

### Kenapa greedy gagal

Godaan pertama: ambil barang dengan **rasio nilai/berat** tertinggi lebih dulu.
Itu benar untuk **fractional** knapsack (barang boleh dipotong), tetapi **salah**
untuk 0/1:

```
W = 10
barang A: berat 6, nilai 7   -> rasio 1.17   <- rasio tertinggi
barang B: berat 5, nilai 5   -> rasio 1.00
barang C: berat 5, nilai 5   -> rasio 1.00

Greedy rasio : ambil A (nilai 7), sisa kapasitas 4, tidak ada yang muat -> 7
Optimal      : ambil B dan C (nilai 10)                                 -> 10
```

Greedy gagal karena mengambil A **menghabiskan** kapasitas dengan cara yang
menghalangi kombinasi yang lebih baik. Tidak ada urutan greedy yang benar
untuk 0/1 knapsack — inilah alasan DP diperlukan.

### Mendefinisikan state

```
dp[i][c] = nilai maksimum yang bisa diperoleh dengan
           mempertimbangkan i barang pertama, kapasitas tersisa c
```

Untuk setiap barang ada **dua pilihan**:

```
TIDAK ambil barang ke-i  ->  dp[i-1][c]
AMBIL barang ke-i        ->  dp[i-1][c - w[i]] + v[i]      (butuh c >= w[i])

dp[i][c] = max(kedua pilihan)
```

Basisnya `dp[0][c] = 0` — tanpa barang, nilainya nol berapa pun kapasitasnya.

> **Kenapa `dp[i-1]` dan bukan `dp[i]` di sisi kanan?** Karena setiap barang
> hanya boleh diambil **sekali**. Merujuk ke `dp[i]` berarti mengizinkan barang
> yang sama dipakai lagi — dan itu justru rekurens untuk **unbounded** knapsack.
> Satu perbedaan indeks memisahkan dua masalah yang berbeda.

### Diagram tabel

```
       c=0  1  2  3  4  5
i=0     0   0  0  0  0  0        tanpa barang
i=1     0   0  0  3  3  3        barang (w=3, v=3)
i=2     0   0  4  4  4  7        + barang (w=2, v=4)
i=3     0   0  4  4  4  7        + barang (w=4, v=2)

Setiap sel hanya bergantung pada BARIS DI ATASNYA:
  dp[i][c] <- dp[i-1][c]           (langsung di atas)
  dp[i][c] <- dp[i-1][c - w[i]]    (di atas, geser ke kiri sejauh w[i])
```

Karena hanya butuh satu baris sebelumnya, seluruh tabel bisa diringkas menjadi
**satu array** — dan itulah optimasi rolling array.

---

## 🧮 2. Analisis Kompleksitas

| Varian | Waktu | Ruang | Kapan dipakai |
| ------ | ----- | ----- | ------------- |
| DP 2D | O(n·W) | O(n·W) | butuh rekonstruksi mudah |
| DP 1D (rolling) | O(n·W) | **O(W)** | default |
| DP atas nilai | O(n·ΣV) | O(ΣV) | `W` besar, nilai kecil |
| Meet in the middle | O(2^(n/2)·n) | O(2^(n/2)) | `n ≤ 40`, `W` besar |
| Brute force | O(2^n) | O(1) | `n ≤ 20` |

### Memilih varian — hitung, jangan tebak

```
n = 100,  W = 10^5   ->  DP: 10^7            AMAN
n = 100,  W = 10^9   ->  DP: 10^11           MUSTAHIL -> cek nilai
n = 40,   W = 10^15  ->  MITM: 4*10^7        AMAN     (Day 54)
n = 1000, W = 10^5   ->  DP: 10^8            ketat, tetapi biasanya lolos
n = 100,  ΣV = 10^4  ->  DP atas nilai: 10^6 AMAN meski W = 10^18
```

**Aturan praktis:**

```
W kecil (<= 10^6)          -> DP atas KAPASITAS
V kecil (ΣV <= 10^6)       -> DP atas NILAI
keduanya besar, n <= 40    -> meet in the middle (Day 54)
keduanya besar, n besar    -> soalnya punya struktur lain; cari ulang
```

**Memori:** `O(n·W)` untuk `n = 100`, `W = 10^5` adalah `10^7` int = 40 MB —
sudah berisiko. Versi 1D hanya `400 KB`. Itulah kenapa rolling array bukan
sekadar optimasi, melainkan sering **keharusan**.

---

## 💻 3. Implementasi C++

### 3.1 Versi 2D (paling jelas, mudah direkonstruksi)

```cpp
long long knapsack2D(const vector<int>& w, const vector<long long>& v, int W) {
    int n = w.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(W + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];                        // tidak ambil
            if (c >= w[i - 1])                              // muat?
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }
    return dp[n][W];
}
```

⚠️ Perhatikan `w[i-1]` dan `v[i-1]`: tabel `dp` berindeks 1..n untuk barang,
tetapi array barangnya 0-based. Ketidakcocokan ini adalah sumber off-by-one
yang sangat sering. Alternatifnya: buat `w` dan `v` juga 1-based.

### 3.2 Versi 1D (rolling array) — yang biasanya dipakai

```cpp
long long knapsack1D(const vector<int>& w, const vector<long long>& v, int W) {
    vector<long long> dp(W + 1, 0);

    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)                     // MUNDUR!
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);

    return dp[W];
}
```

⚠️ **Loop kapasitas harus MUNDUR.** Ini bagian terpenting hari ini.

```
MUNDUR (c dari W ke w[i]):
   saat membaca dp[c - w[i]], nilainya MASIH dari iterasi barang SEBELUMNYA
   -> barang ke-i belum pernah dipakai -> setiap barang dipakai paling banyak SEKALI
   -> ini 0/1 knapsack  ✓

MAJU (c dari w[i] ke W):
   saat membaca dp[c - w[i]], nilainya SUDAH diperbarui pada iterasi ini
   -> barang ke-i bisa dipakai LAGI -> setiap barang boleh berkali-kali
   -> ini UNBOUNDED knapsack  ✗ (untuk soal 0/1)
```

Jadi satu perubahan arah loop mengubah masalah yang diselesaikan. Ini bukan
detail teknis — ini **definisi** yang tertanam dalam kode.

### 3.3 Rekonstruksi dengan tabel 2D

```cpp
vector<int> rekonstruksi2D(const vector<int>& w, const vector<long long>& v,
                           int W, const vector<vector<long long>>& dp) {
    vector<int> dipilih;
    int c = W;
    for (int i = (int)w.size(); i >= 1; i--) {
        if (dp[i][c] != dp[i - 1][c]) {          // nilainya berubah -> barang diambil
            dipilih.push_back(i - 1);            // indeks 0-based
            c -= w[i - 1];
        }
    }
    reverse(dipilih.begin(), dipilih.end());
    return dipilih;
}
```

Idenya: telusuri **mundur** dari `dp[n][W]`. Kalau nilainya sama dengan baris di
atasnya, barang ke-`i` tidak diambil; kalau berbeda, ia pasti diambil.

⚠️ Membutuhkan tabel 2D penuh — `O(n·W)` memori.

### 3.4 Rekonstruksi tanpa tabel penuh

Kalau memori tidak cukup untuk tabel 2D, simpan **jejak keputusan** dalam bit:

```cpp
// ambil[i][c] = apakah barang i diambil untuk mencapai dp[i][c]
vector<vector<char>> ambil(n + 1, vector<char>(W + 1, 0));

for (int i = 1; i <= n; i++)
    for (int c = W; c >= 0; c--) {
        if (c >= w[i-1] && dp[c - w[i-1]] + v[i-1] > dp[c]) {
            dp[c] = dp[c - w[i-1]] + v[i-1];
            ambil[i][c] = 1;
        }
    }
```

Ini masih `O(n·W)` memori, tetapi **satu byte** per sel alih-alih delapan —
delapan kali lebih hemat. Untuk `n = 100`, `W = 10^5` itu 10 MB alih-alih 80 MB.

Alternatif yang benar-benar `O(W)` memori: **divide and conquer** (Hirschberg),
`O(n·W)` waktu tetapi `O(W)` memori. Jarang dibutuhkan di CP.

### 3.5 Subset sum — knapsack yang menyamar

*Adakah subhimpunan yang jumlahnya tepat `S`?*

```cpp
vector<char> bisa(S + 1, 0);
bisa[0] = 1;
for (int x : a)
    for (int c = S; c >= x; c--)                 // MUNDUR, sama alasannya
        if (bisa[c - x]) bisa[c] = 1;
```

Ini knapsack 0/1 dengan `nilai = berat`. Versi `bitset` jauh lebih cepat:

```cpp
bitset<100001> bs;
bs[0] = 1;
for (int x : a) bs |= bs << x;                   // O(n·S/64)
```

Faktor 64 dari bitset sering mengubah `10^9` menjadi `1.5·10^7` — dan itu
membuat soal yang tampak mustahil menjadi mudah.

### 3.6 Unbounded & bounded knapsack

```cpp
// UNBOUNDED: setiap barang boleh berkali-kali -> loop MAJU
for (int i = 0; i < n; i++)
    for (int c = w[i]; c <= W; c++)
        dp[c] = max(dp[c], dp[c - w[i]] + v[i]);

// BOUNDED: barang ke-i tersedia k[i] buah
// Naif: perlakukan sebagai k[i] barang terpisah -> O(W * sum k)
// Dekomposisi BINER: pecah k menjadi 1, 2, 4, ..., sisa
for (int i = 0; i < n; i++) {
    int sisa = k[i];
    for (int p = 1; sisa > 0; p *= 2) {
        int ambil = min(p, sisa);
        sisa -= ambil;
        // perlakukan sebagai SATU barang berbobot ambil*w[i], nilai ambil*v[i]
        for (int c = W; c >= ambil * w[i]; c--)
            dp[c] = max(dp[c], dp[c - ambil * w[i]] + (long long)ambil * v[i]);
    }
}
```

Dekomposisi biner mengubah `O(W · Σk)` menjadi `O(W · Σ log k)` — untuk
`k = 10^6` itu 20 barang alih-alih sejuta. (Materi lengkapnya Day 147.)

### 3.7 DP atas nilai (saat `W` sangat besar)

```cpp
// dp[val] = berat MINIMUM untuk mencapai nilai tepat val
const long long INF = LLONG_MAX / 4;
long long totalV = accumulate(v.begin(), v.end(), 0LL);
vector<long long> dp(totalV + 1, INF);
dp[0] = 0;

for (int i = 0; i < n; i++)
    for (long long val = totalV; val >= v[i]; val--)
        if (dp[val - v[i]] != INF)
            dp[val] = min(dp[val], dp[val - v[i]] + w[i]);

long long best = 0;
for (long long val = totalV; val >= 0; val--)
    if (dp[val] <= W) { best = val; break; }
```

**Membalik peran nilai dan berat.** Berguna ketika `W = 10^18` tetapi
`Σv ≤ 10^4`. Pola "tukar apa yang menjadi indeks dan apa yang menjadi isi"
muncul di banyak soal DP.

---

## 🔄 4. Trace & Simulasi

### 4.1 Tabel 2D pada `w = [3, 2, 4]`, `v = [3, 4, 2]`, `W = 5`

```
       c=0   1   2   3   4   5
i=0     0    0   0   0   0   0
```

**Barang 1 (w=3, v=3):**

| c | tidak ambil | ambil (butuh c≥3) | dp[1][c] |
| - | ----------- | ----------------- | -------- |
| 0 | 0 | — | 0 |
| 1 | 0 | — | 0 |
| 2 | 0 | — | 0 |
| 3 | 0 | dp[0][0] + 3 = 3 | **3** |
| 4 | 0 | dp[0][1] + 3 = 3 | **3** |
| 5 | 0 | dp[0][2] + 3 = 3 | **3** |

**Barang 2 (w=2, v=4):**

| c | tidak ambil | ambil (butuh c≥2) | dp[2][c] |
| - | ----------- | ----------------- | -------- |
| 2 | 0 | dp[1][0] + 4 = 4 | **4** |
| 3 | 3 | dp[1][1] + 4 = 4 | **4** |
| 4 | 3 | dp[1][2] + 4 = 4 | **4** |
| 5 | 3 | dp[1][3] + 4 = **7** | **7** |

**Barang 3 (w=4, v=2):**

| c | tidak ambil | ambil (butuh c≥4) | dp[3][c] |
| - | ----------- | ----------------- | -------- |
| 4 | 4 | dp[2][0] + 2 = 2 | **4** |
| 5 | 7 | dp[2][1] + 2 = 2 | **7** |

```
Jawaban dp[3][5] = 7  ->  ambil barang 1 (w=3,v=3) dan barang 2 (w=2,v=4)
Total berat 5, total nilai 7.   ✓
```

### 4.2 Rekonstruksi mundur

```
Mulai dari i=3, c=5, dp[3][5] = 7

i=3: dp[3][5]=7 == dp[2][5]=7  ->  barang 3 TIDAK diambil, c tetap 5
i=2: dp[2][5]=7 != dp[1][5]=3  ->  barang 2 DIAMBIL, c = 5 - 2 = 3
i=1: dp[1][3]=3 != dp[0][3]=0  ->  barang 1 DIAMBIL, c = 3 - 3 = 0

Dipilih: barang 1 dan 2   ✓
```

### 4.3 Kenapa loop 1D harus mundur — demonstrasi

```
w = [2], v = [3], W = 4.  Jawaban BENAR: 3 (barang hanya boleh sekali).

MUNDUR (c = 4, 3, 2):
   c=4: dp[4] = max(0, dp[2] + 3) = max(0, 0 + 3) = 3     dp[2] masih 0  ✓
   c=3: dp[3] = max(0, dp[1] + 3) = 3
   c=2: dp[2] = max(0, dp[0] + 3) = 3
   dp = [0, 0, 3, 3, 3]  ->  dp[4] = 3   BENAR

MAJU (c = 2, 3, 4):
   c=2: dp[2] = max(0, dp[0] + 3) = 3
   c=3: dp[3] = max(0, dp[1] + 3) = 3
   c=4: dp[4] = max(0, dp[2] + 3) = max(0, 3 + 3) = 6     dp[2] SUDAH 3  ✗
   dp[4] = 6  ->  barang dipakai DUA KALI. Ini unbounded, bukan 0/1.
```

Satu karakter (`c--` vs `c++`) mengubah masalah yang diselesaikan.

### 4.4 Kenapa greedy rasio gagal

```
W = 10
A: w=6, v=7, rasio 1.167
B: w=5, v=5, rasio 1.000
C: w=5, v=5, rasio 1.000

Greedy: ambil A (sisa 4), B tidak muat, C tidak muat  ->  7
DP    : dp[10] = 10 (ambil B dan C)                   ->  10
```

Greedy rasio benar untuk **fractional** knapsack (Day 74) karena di sana kamu
boleh mengambil sebagian barang. Untuk 0/1, keputusan biner membuat "sisa
kapasitas yang terbuang" menjadi masalah nyata.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "pilih barang, maksimalkan nilai, ada kapasitas" | 0/1 knapsack |
| "adakah subhimpunan berjumlah S" | subset sum (nilai = berat) |
| "bagi jadi dua bagian berjumlah sama" | subset sum dengan `S = total/2` |
| "berapa cara membayar tepat X" | penukaran uang (hitung, bukan maksimum) |
| barang boleh **berkali-kali** | unbounded → loop **maju** |
| barang tersedia `k` buah | bounded → dekomposisi biner (Day 147) |
| "barang mana yang dipilih" | rekonstruksi |
| `W` besar, nilai kecil | DP atas **nilai** |
| `n ≤ 40`, keduanya besar | meet in the middle (Day 54) |
| barang boleh **dipotong** | greedy rasio (Day 74), bukan DP |

### Pattern: partisi menjadi dua bagian sama

```cpp
long long total = accumulate(a.begin(), a.end(), 0LL);
if (total % 2) return false;                 // ganjil: mustahil
// lalu subset sum dengan target total/2
```

Menyadari bahwa "partisi seimbang" adalah subset sum menghemat banyak waktu.

### Pattern: menghitung cara, bukan memaksimalkan

```cpp
// Berapa CARA memilih subhimpunan yang jumlahnya tepat S?
vector<long long> cara(S + 1, 0);
cara[0] = 1;
for (int x : a)
    for (int c = S; c >= x; c--)
        cara[c] += cara[c - x];              // += , bukan max
```

Struktur rekurensnya identik; hanya operasi penggabungannya yang berubah dari
`max` menjadi `+`. Pola ini berlaku untuk hampir semua DP: **ganti operator,
dapatkan masalah berbeda.**

### Pattern: knapsack dengan bitset

Untuk subset sum murni (tanpa nilai), `bitset` memberi percepatan 64×:

```cpp
bitset<MAXS> bs;
bs[0] = 1;
for (int x : a) bs |= bs << x;
// bs[S] menunjukkan apakah jumlah S bisa dicapai
```

`n = 100`, `S = 10^5` → `10^7 / 64 ≈ 1.5·10^5` operasi. Nyaris gratis.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Loop kapasitas MAJU pada 0/1.** Menghasilkan unbounded knapsack.
   Bug nomor satu, dan hasilnya terlihat "masuk akal" (hanya terlalu besar).

2. **Off-by-one antara `dp[i]` dan `w[i-1]`.** Pilih satu konvensi dan
   konsisten; atau buat array barang 1-based.

3. **`int` untuk nilai total.** `n = 100` dengan `v = 10^9` memberi `10^11`.

4. **Memori `O(n·W)`.** `100 × 10^5` int = 40 MB. Pakai versi 1D.

5. **Lupa `c >= w[i]`.** Mengakses `dp[c - w[i]]` dengan indeks negatif.

6. **Mengira greedy rasio benar.** Hanya untuk fractional knapsack.

7. **Merekonstruksi dari tabel 1D.** Tidak bisa — tabel 1D menimpa riwayatnya.
   Butuh 2D, atau simpan jejak keputusan.

8. **Subset sum diinisialisasi `bisa[0] = 0`.** Harus `1` — jumlah nol selalu
   bisa dicapai dengan subhimpunan kosong.

### Edge cases wajib diuji

```
W = 0                    -> jawabannya 0
seluruh barang > W       -> jawabannya 0
n = 1                    -> ambil atau tidak
seluruh berat sama       -> jadi masalah "berapa banyak yang muat"
nilai nol                -> tetap valid, jawabannya bisa 0
total berat <= W         -> ambil semuanya
subset sum S = 0         -> selalu bisa (subhimpunan kosong)
```

---

## 🏆 7. Tips Contest

**Langkah pertama selalu: hitung `n × W`.**

```
n * W <= 10^8   -> DP kapasitas, tulis versi 1D
n * ΣV <= 10^8  -> DP nilai
n <= 40         -> meet in the middle (Day 54)
```

Menentukan ini di awal menghemat waktu yang sangat banyak — banyak orang
menulis DP lebih dulu lalu baru sadar `W = 10^18`.

**Tulis versi 1D sebagai default.** Ia lebih pendek, lebih hemat memori, dan
sama cepatnya. Beralih ke 2D hanya kalau kamu butuh rekonstruksi.

**Hafalkan tiga baris ini:**

```cpp
for (int i = 0; i < n; i++)
    for (int c = W; c >= w[i]; c--)          // MUNDUR untuk 0/1
        dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
```

Dan ingat bahwa mengubah `c--` menjadi `c++` memberimu unbounded knapsack —
dua soal dengan satu template.

**Knapsack sering menyamar.** Kalau soal berbicara tentang "memilih beberapa hal
dengan batas total", periksa apakah itu knapsack sebelum mencari yang lebih rumit.

**Untuk subset sum murni, langsung pakai bitset.** Percepatan 64× itu nyata dan
kodenya justru lebih pendek.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  0/1 KNAPSACK
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  dp[i][c] = max(dp[i-1][c], dp[i-1][c - w[i]] + v[i])
  dp[i-1] di KEDUA sisi -> setiap barang PALING BANYAK SEKALI

  VERSI 1D (default):
    for (i = 0..n-1)
        for (c = W; c >= w[i]; c--)          <- MUNDUR!
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);

    MUNDUR -> dp[c-w[i]] masih dari barang SEBELUMNYA -> 0/1   ✓
    MAJU   -> dp[c-w[i]] sudah diperbarui -> UNBOUNDED

  REKONSTRUKSI: butuh tabel 2D, telusuri MUNDUR
    dp[i][c] != dp[i-1][c]  ->  barang i diambil, c -= w[i]

  VARIAN
    unbounded  : loop MAJU
    bounded k  : dekomposisi biner 1,2,4,... -> O(W log k) (Day 147)
    subset sum : nilai = berat; bitset memberi 64x
    hitung cara: ganti max jadi +
    W besar, V kecil: DP atas NILAI (dp[val] = berat minimum)

  PILIH VARIAN -- HITUNG DULU
    n*W  <= 1e8  -> DP kapasitas
    n*SV <= 1e8  -> DP nilai
    n <= 40      -> meet in the middle (Day 54)

  GREEDY RASIO SALAH untuk 0/1 (benar hanya untuk FRACTIONAL, Day 74)
  long long untuk nilai total | subset sum: bisa[0] = 1
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1158 — Book Shop](https://cses.fi/problemset/task/1158) | CSES | 0/1 knapsack murni |
| [CSES 1745 — Money Sums](https://cses.fi/problemset/task/1745) | CSES | subset sum, seluruh jumlah |
| [CSES 1633 — Dice Combinations](https://cses.fi/problemset/task/1633) | CSES | (pembanding: unbounded) |
| [LeetCode 416 — Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) | LeetCode | partisi seimbang |
| [LeetCode 494 — Target Sum](https://leetcode.com/problems/target-sum/) | LeetCode | subset sum bertanda |
| [LeetCode 1049 — Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) | LeetCode | partisi menyamar |
| [SPOJ KNAPSACK / PARTY](https://www.spoj.com/) | SPOJ | knapsack klasik |
| [UVa 10130 — SuperSale](https://onlinejudge.org/) | UVa | knapsack berulang |
| [AtCoder DP Contest D — Knapsack 1](https://atcoder.jp/contests/dp/tasks/dp_d) | AtCoder | 0/1 dasar |
| [AtCoder DP Contest E — Knapsack 2](https://atcoder.jp/contests/dp/tasks/dp_e) | AtCoder | DP atas **nilai** |

---

**Selanjutnya:** Day 146 — Subset Sum & Partition Problem secara mendalam, dan
Day 147 — Bounded Knapsack dengan dekomposisi biner.

Dan yang lebih dekat: knapsack ini adalah prasyarat untuk **tugas 15 di Day 51**
(optimasi rasio dengan batasan) yang sudah kamu punya — kamu sekarang bisa
menggabungkan binary search di luar dengan knapsack di dalam.
