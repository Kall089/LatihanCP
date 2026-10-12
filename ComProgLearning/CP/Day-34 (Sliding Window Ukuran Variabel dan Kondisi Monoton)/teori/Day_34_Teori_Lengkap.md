# 📊 Day 34: Sliding Window Ukuran Variabel & Kondisi Monoton

> **Prasyarat:** Two Pointers (Day 32), Sliding Window Ukuran Tetap (Day 33), Prefix Sum (Day 29)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"subarray terpanjang yang ..."*, *"subarray terpendek yang ..."*, *"paling banyak K jenis"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 34, kamu akan mampu:

- [ ] Membedakan window **ukuran tetap** (Day 33) dan **ukuran variabel** (hari ini)
- [ ] Menyatakan syarat kelayakan teknik ini: **monotonisitas predikat**
- [ ] Menulis kerangka baku *"perluas kanan, susutkan kiri"* tanpa ragu
- [ ] Menjelaskan kenapa dua pointer yang keduanya maju menghasilkan **O(n)**, bukan O(n²)
- [ ] Menangani varian **terpanjang** dan **terpendek** dengan benar
- [ ] Memakai trik **`atMost(K) − atMost(K−1)`** untuk soal "tepat K"
- [ ] Mengenali kapan sliding window **gagal** dan harus diganti prefix + map

---

## 🔍 1. Konsep & Intuisi

### Bedanya dengan Day 33

```
Day 33 (ukuran TETAP)   : window selalu selebar k
                          -> masuk satu, keluar satu, selalu

Day 34 (ukuran VARIABEL): lebar window ditentukan oleh KONDISI
                          -> masuk satu, keluar NOL ATAU LEBIH
```

### Analogi: menyeret selang air di taman

Bayangkan kamu menyiram taman memanjang dengan selang berujung dua penjepit.
Kamu menarik ujung kanan maju terus (tidak pernah mundur). Kalau selangnya jadi
terlalu tegang, kamu majukan ujung kiri sampai kembali longgar.

Kedua ujung **hanya bergerak maju**. Ujung kanan bergerak `n` kali, ujung kiri
paling banyak `n` kali. Total `2n` langkah — itulah kenapa O(n), meskipun kelihatannya
seperti ada loop bersarang.

### Syarat kelayakan: MONOTONISITAS

Sliding window hanya sah kalau predikatnya monoton terhadap pelebaran window:

```
Untuk "terpanjang":
   window layak  ->  SEMUA sub-window di dalamnya juga layak
   (memperlebar hanya bisa membuat makin tidak layak)

Untuk "terpendek":
   window layak  ->  SEMUA super-window yang memuatnya juga layak
   (memperlebar hanya bisa membuat makin layak)
```

Contoh yang **memenuhi** syarat:

```
"jumlah <= S" dengan semua elemen >= 0
   tambah elemen -> jumlah naik atau tetap  -> monoton ✓

"paling banyak K karakter berbeda"
   tambah elemen -> banyak jenis naik atau tetap  -> monoton ✓
```

Contoh yang **melanggar** syarat:

```
"jumlah <= S" dengan elemen NEGATIF
   tambah elemen -> jumlah bisa TURUN  -> tidak monoton ✗
   -> pakai prefix sum + map / struktur terurut (Day 29)

"jumlah tepat K" dengan elemen negatif
   sama, tidak monoton ✗
```

> **Uji cepat sebelum menulis kode:** *"Kalau window saya perlebar satu langkah,
> apakah 'kelayakan' bisa berubah bolak-balik?"* Kalau bisa, sliding window salah alat.

### Diagram kerangka

```
       l                     r
       ↓                     ↓
[ . . [ ================== ] . . . ]
        window saat ini

for r in 0..n-1:
    masukkan a[r] ke window
    while (window TIDAK layak):        <- untuk varian "terpanjang"
        keluarkan a[l]; l++
    catat jawaban dari window [l..r]
```

```
for r in 0..n-1:
    masukkan a[r] ke window
    while (window MASIH layak):        <- untuk varian "terpendek"
        catat jawaban dari window [l..r]
        keluarkan a[l]; l++
```

Perhatikan bedanya: pada "terpanjang", kita mencatat **setelah** menyusutkan;
pada "terpendek", kita mencatat **sebelum** menyusutkan. Salah menaruh baris `catat`
adalah bug paling sering di topik ini.

---

## 🧮 2. Analisis Kompleksitas

| Varian | Waktu | Ruang | Catatan |
| ------ | ----- | ----- | ------- |
| Jumlah / hitungan sederhana | O(n) | O(1) | penjaga window cuma satu variabel |
| Banyak jenis karakter | O(n) | O(A) | A = ukuran alfabet atau map |
| Dengan `map` (nilai besar) | O(n log n) | O(n) | faktor log dari map |
| Dengan array frekuensi | O(n) | O(A) | kalau nilai bisa dikompresi |

**Kenapa O(n) dan bukan O(n²)?** `l` dan `r` masing-masing hanya bergerak maju,
dan masing-masing paling banyak `n` langkah. Loop `while` di dalam boleh berjalan
banyak kali dalam satu iterasi, tetapi **totalnya** sepanjang seluruh program tetap ≤ n.
Ini argumen **amortisasi** yang sama dengan KMP dan Z-function.

**Perbandingan dengan alternatif:**

| Situasi | Alat |
| ------- | ---- |
| semua elemen ≥ 0, cari terpanjang/terpendek | **sliding window O(n)** |
| ada elemen negatif | prefix + map O(n log n) (Day 29) |
| butuh maksimum/minimum di dalam window | monotonic deque (Day 37) |
| jawaban bisa dicek dengan predikat monoton atas panjang | binary search on answer (Day 50) |

---

## 💻 3. Implementasi C++

### 3.1 Terpanjang dengan jumlah ≤ S (elemen non-negatif)

```cpp
int terpanjangJumlahMaks(const vector<long long>& a, long long S) {
    int n = a.size(), l = 0, best = 0;
    long long sum = 0;

    for (int r = 0; r < n; r++) {
        sum += a[r];                       // masukkan
        while (sum > S) {                  // selama TIDAK layak
            sum -= a[l];                   // keluarkan
            l++;
        }
        best = max(best, r - l + 1);       // catat SETELAH menyusut
    }
    return best;
}
```

⚠️ Kalau ada `a[i] > S`, window akan menyusut sampai kosong (`l = r + 1`) dan
`r - l + 1` menjadi 0 — bukan negatif. Kerangka ini aman tanpa penanganan khusus.

### 3.2 Terpendek dengan jumlah ≥ S (elemen non-negatif)

```cpp
int terpendekJumlahMin(const vector<long long>& a, long long S) {
    int n = a.size(), l = 0, best = INT_MAX;
    long long sum = 0;

    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= S) {                 // selama MASIH layak
            best = min(best, r - l + 1);   // catat SEBELUM menyusut
            sum -= a[l];
            l++;
        }
    }
    return (best == INT_MAX) ? 0 : best;   // 0 = tidak ada yang memenuhi
}
```

### 3.3 Terpanjang tanpa karakter berulang

```cpp
int terpanjangUnik(const string& s) {
    vector<int> lastSeen(256, -1);
    int l = 0, best = 0;

    for (int r = 0; r < (int)s.size(); r++) {
        // kalau karakter ini pernah muncul DI DALAM window, lompatkan l
        if (lastSeen[(unsigned char)s[r]] >= l)
            l = lastSeen[(unsigned char)s[r]] + 1;

        lastSeen[(unsigned char)s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}
```

Perhatikan syarat `>= l`. Tanpa itu, karakter yang muncul **sebelum** window akan
salah memundurkan `l` — dan `l` yang mundur langsung merusak jaminan O(n).

### 3.4 Paling banyak K jenis berbeda

```cpp
int terpanjangAtMostK(const vector<int>& a, int K) {
    unordered_map<int, int> cnt;
    int l = 0, best = 0, jenis = 0;

    for (int r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) jenis++;     // jenis baru masuk
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--; // jenis habis, keluar
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}
```

Pola `if (cnt[x]++ == 0) jenis++;` dan `if (--cnt[x] == 0) jenis--;` adalah pasangan
yang harus dihafal. Menuliskannya terbalik (`++cnt[x] == 1`) juga benar, tetapi
mencampur gaya di satu fungsi adalah resep bug.

### 3.5 Trik "tepat K" = atMost(K) − atMost(K−1)

Menghitung subarray dengan **tepat** K jenis sulit dilakukan langsung, karena
predikatnya tidak monoton. Tapi "paling banyak K" monoton. Maka:

```cpp
long long atMost(const vector<int>& a, int K) {
    if (K < 0) return 0;
    unordered_map<int, int> cnt;
    long long hasil = 0;
    int l = 0, jenis = 0;

    for (int r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) jenis++;
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--;
            l++;
        }
        hasil += r - l + 1;                // semua subarray berakhir di r
    }
    return hasil;
}

long long tepatK(const vector<int>& a, int K) {
    return atMost(a, K) - atMost(a, K - 1);
}
```

**Kenapa `hasil += r - l + 1`?** Karena setiap subarray yang berakhir di `r` dan
dimulai di `l..r` semuanya layak (monotonisitas menjamin ini). Banyaknya `r - l + 1`.
Ini adalah cara menghitung **banyak** subarray, bukan mencari yang terpanjang —
perbedaan yang sering tertukar.

Trik pengurangan ini berlaku untuk **semua** predikat "tepat" yang versinya
"paling banyak" bersifat monoton. Simpan pola ini; ia muncul terus-menerus.

---

## 🔄 4. Trace & Simulasi

### 4.1 Terpanjang jumlah ≤ 7 pada `a = [2, 3, 1, 2, 4, 3]`

| r | a[r] | sum setelah masuk | menyusut? | l | window | panjang | best |
| - | ---- | ----------------- | --------- | - | ------ | ------- | ---- |
| 0 | 2 | 2 | tidak | 0 | [2] | 1 | **1** |
| 1 | 3 | 5 | tidak | 0 | [2,3] | 2 | **2** |
| 2 | 1 | 6 | tidak | 0 | [2,3,1] | 3 | **3** |
| 3 | 2 | 8 > 7 | buang 2 → 6 | 1 | [3,1,2] | 3 | 3 |
| 4 | 4 | 10 > 7 | buang 3 → 7 | 2 | [1,2,4] | 3 | 3 |
| 5 | 3 | 10 > 7 | buang 1 → 9 > 7, buang 2 → 7 | 4 | [4,3] | 2 | 3 |

```
best = 3    ->  [2,3,1] atau [3,1,2] atau [1,2,4]
```

Perhatikan baris terakhir: `while` berjalan dua kali dalam satu iterasi. Itu boleh —
yang penting `l` tidak pernah mundur, sehingga total gerakannya tetap ≤ n.

### 4.2 Terpendek jumlah ≥ 7 pada array yang sama

| r | sum | while layak? | catat | l setelahnya | best |
| - | --- | ------------ | ----- | ------------ | ---- |
| 0 | 2 | tidak | — | 0 | ∞ |
| 1 | 5 | tidak | — | 0 | ∞ |
| 2 | 6 | tidak | — | 0 | ∞ |
| 3 | 8 | ya | panjang 4 | 1 (sum 6) | **4** |
| 4 | 10 | ya | panjang 4 | 2 (sum 7) | 4 |
| | 7 | ya | panjang 3 | 3 (sum 6) | **3** |
| 5 | 9 | ya | panjang 3 | 4 (sum 7) | 3 |
| | 7 | ya | panjang 2 | 5 (sum 3) | **2** |

```
best = 2    ->  [4,3]
```

Bandingkan dua tabel ini. Kerangkanya nyaris identik, tetapi posisi baris `catat`
berbeda — dan itulah satu-satunya hal yang membedakan "terpanjang" dari "terpendek".

### 4.3 Tepat 2 jenis pada `a = [1, 2, 1, 2, 3]`

```
atMost(2):
  r=0 [1]         l=0  += 1   -> 1
  r=1 [1,2]       l=0  += 2   -> 3
  r=2 [1,2,1]     l=0  += 3   -> 6
  r=3 [1,2,1,2]   l=0  += 4   -> 10
  r=4 jenis=3, susut sampai l=2 ([1,2,3] masih 3 jenis -> l=3, [2,3] 2 jenis)
      l=3  += 2   -> 12

atMost(1):
  r=0 [1]         l=0  += 1   -> 1
  r=1 susut l=1   [2] += 1    -> 2
  r=2 susut l=2   [1] += 1    -> 3
  r=3 susut l=3   [2] += 1    -> 4
  r=4 susut l=4   [3] += 1    -> 5

tepat 2 = 12 - 5 = 7
```

Verifikasi manual: `[1,2] [2,1] [1,2] [1,2,1] [2,1,2] [1,2,1,2] [2,3]` → 7 ✓

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "subarray terpanjang dengan jumlah ≤ S", elemen ≥ 0 | window terpanjang |
| "subarray terpendek dengan jumlah ≥ S", elemen ≥ 0 | window terpendek |
| "substring terpanjang tanpa karakter berulang" | window + `lastSeen` |
| "paling banyak K jenis berbeda" | window + map hitungan |
| "**tepat** K jenis / tepat K angka ganjil" | `atMost(K) − atMost(K−1)` |
| "berapa **banyak** subarray yang ..." | window + `hasil += r − l + 1` |
| "boleh mengganti paling banyak K karakter" | window + hitung karakter mayoritas |
| ada elemen **negatif** | ❌ window; pakai prefix + map (Day 29) |
| butuh max/min **di dalam** window | monotonic deque (Day 37) |

### Pattern: "boleh mengubah paling banyak K elemen"

*Substring terpanjang berisi huruf sama, boleh mengganti ≤ K huruf.*

```cpp
int cnt[26] = {0};
int l = 0, best = 0, maxFreq = 0;
for (int r = 0; r < n; r++) {
    maxFreq = max(maxFreq, ++cnt[s[r] - 'A']);
    // jumlah yang harus diganti = lebar window − frekuensi terbanyak
    while ((r - l + 1) - maxFreq > K) {
        cnt[s[l] - 'A']--;
        l++;
    }
    best = max(best, r - l + 1);
}
```

### Pattern: dua window sekaligus

Beberapa soal "tepat K" bisa diselesaikan dengan **dua pointer kiri** (`l1`, `l2`)
alih-alih dua kali pemanggilan `atMost`. Lebih cepat, tapi lebih rawan salah.
Untuk kontes, `atMost(K) − atMost(K−1)` lebih aman.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Memakai window padahal ada bilangan negatif.** Ini kesalahan konseptual, bukan
   kesalahan kode — hasilnya terlihat masuk akal tapi salah. Selalu cek constraint
   `a[i] >= 0` sebelum memilih alat ini.

2. **Salah menaruh baris `catat`.** Terpanjang → catat **setelah** `while`.
   Terpendek → catat **di dalam** `while`, sebelum menyusut.

3. **`l` mundur.** Pada varian `lastSeen`, lupa syarat `>= l` membuat `l` mundur dan
   jaminan O(n) hilang — bahkan hasilnya salah.

4. **Lupa mengembalikan keadaan saat menyusut.** Setiap `sum += a[r]` harus punya
   pasangan `sum -= a[l]`; setiap `cnt[a[r]]++` harus punya `cnt[a[l]]--`.
   Tulis keduanya berdekatan supaya mudah diperiksa.

5. **`best` tidak diinisialisasi dengan benar.** Terpanjang mulai dari 0;
   terpendek mulai dari `INT_MAX` dan **wajib** ditangani kalau tidak ada jawaban.

6. **`unordered_map` di dalam loop panas.** Untuk `n = 10^6`, `unordered_map` bisa
   jauh lebih lambat dari array. Kalau nilainya kecil atau bisa dikompresi (Day 38),
   pakai array.

7. **Overflow pada `hasil += r - l + 1`.** Untuk `n = 10^5`, totalnya bisa `5·10^9`.
   Pakai `long long`.

### Edge cases wajib diuji

```
n = 1                      -> window satu elemen
semua elemen > S           -> jawaban 0, window pernah kosong
tidak ada yang memenuhi    -> terpendek harus mengembalikan 0/-1, bukan INT_MAX
K = 0 pada "at most K"     -> window selalu kosong
K >= n                     -> window seluruh array
semua elemen sama          -> window tidak pernah menyusut
```

---

## 🏆 7. Tips Contest

**Alur pengambilan keputusan (30 detik pertama):**

```
Soal minta subarray/substring dengan suatu sifat?
  |
  +-- Ada bilangan negatif?  --YA-->  prefix + map (Day 29), BUKAN window
  |
  +-- Butuh max/min di dalam window?  --YA-->  monotonic deque (Day 37)
  |
  +-- Minta "tepat K"?  --YA-->  atMost(K) - atMost(K-1)
  |
  +-- Minta "terpanjang"?  -->  catat SETELAH while
  |
  +-- Minta "terpendek"?   -->  catat DI DALAM while
```

**Kebiasaan yang menyelamatkan:** tulis operasi "masuk" dan "keluar" sebagai dua baris
yang bercermin, misalnya `sum += a[r]` dan `sum -= a[l]`. Kalau kamu bisa membaca kode
dan melihat setiap "masuk" punya pasangan "keluar", kemungkinan besar kodenya benar.

**Manajemen waktu:** kalau kamu ragu apakah predikatnya monoton, uji dengan array
kecil di kertas selama 2 menit. Dua menit itu jauh lebih murah daripada 30 menit
men-debug algoritma yang memang salah pilih.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  SLIDING WINDOW UKURAN VARIABEL
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  SYARAT: predikat MONOTON terhadap pelebaran window
          (kalau ada bilangan negatif, biasanya TIDAK monoton)

  TERPANJANG                      TERPENDEK
    masuk a[r]                      masuk a[r]
    while (TIDAK layak)             while (MASIH layak)
        keluar a[l], l++                catat (r - l + 1)
    catat (r - l + 1)                   keluar a[l], l++

  HITUNG BANYAK SUBARRAY
    hasil += r - l + 1          (semua yang berakhir di r)   long long!

  TEPAT K
    atMost(K) - atMost(K-1)

  POLA HITUNGAN JENIS
    masuk : if (cnt[x]++ == 0) jenis++;
    keluar: if (--cnt[x] == 0) jenis--;

  O(n) karena l dan r HANYA MAJU, total gerakan <= 2n
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1141 — Playlist](https://cses.fi/problemset/task/1141) | CSES | terpanjang tanpa duplikat |
| [CSES 2428 — Subarray Distinct Values](https://cses.fi/problemset/task/2428) | CSES | atMost K, hitung banyak |
| [LeetCode 3 — Longest Substring Without Repeating](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | LeetCode | pola `lastSeen` |
| [LeetCode 209 — Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | LeetCode | terpendek |
| [LeetCode 424 — Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | LeetCode | boleh ganti K |
| [LeetCode 992 — Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/) | LeetCode | trik pengurangan |
| [LeetCode 930 — Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/) | LeetCode | trik pengurangan |
| [CF 279B — Books](https://codeforces.com/problemset/problem/279/B) | Codeforces | terpanjang jumlah ≤ t |
| [ABC 032 C — 列](https://atcoder.jp/contests/abc032/tasks/abc032_c) | AtCoder | hati-hati elemen nol |

---

**Selanjutnya:** Day 35 — Kadane's Algorithm. Di sana kamu akan menemukan bahwa
"subarray dengan jumlah maksimum" **tidak** bisa diselesaikan dengan sliding window
(karena ada bilangan negatif), dan butuh cara pandang yang sama sekali berbeda:
DP satu dimensi yang menyamar sebagai loop sederhana.
