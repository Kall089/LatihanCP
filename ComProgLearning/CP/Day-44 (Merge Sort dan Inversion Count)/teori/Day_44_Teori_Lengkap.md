# 📊 Day 44: Merge Sort & Inversion Count

> **Prasyarat:** Rekursi dasar, Sorting O(n²) (Day 43), Kompleksitas (Day 15–16)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"berapa pasangan terbalik"*, *"berapa swap berdampingan"*, *"gabungkan dua array terurut"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 44, kamu akan mampu:

- [ ] Menulis merge sort dari nol dengan langkah **merge** yang benar
- [ ] Menjelaskan kenapa merge sort **stabil** dan `std::sort` tidak
- [ ] Menghitung **inversi** dalam O(n log n) dengan satu baris tambahan
- [ ] Menjelaskan **kenapa** baris itu menambahkan `mid − i` dan bukan 1
- [ ] Menyesuaikan pola merge untuk **pasangan penting** (`a[i] > 2·a[j]`)
- [ ] Menggabungkan **k array terurut** dengan heap
- [ ] Memilih antara merge sort, BIT, dan `std::sort` secara sadar

---

## 🔍 1. Konsep & Intuisi

### Divide and conquer

```
             [5, 2, 4, 6, 1, 3]
                    ↓ BAGI
       [5, 2, 4]          [6, 1, 3]
          ↓                   ↓
    [5]  [2, 4]         [6]  [1, 3]
              ↓                   ↓
         [2]  [4]            [1]  [3]

                    ↑ GABUNG
    [5]  [2, 4]         [6]  [1, 3]
       [2, 4, 5]          [1, 3, 6]
             [1, 2, 3, 4, 5, 6]
```

Membagi itu murah (hanya menghitung titik tengah). Seluruh pekerjaan ada di
**penggabungan**, dan penggabungan dua array terurut adalah O(panjangnya).

### Kenapa O(n log n)?

```
Kedalaman rekursi = log2(n)     karena setiap level membagi dua
Kerja per level   = O(n)        setiap elemen disalin tepat sekali per level

Total = O(n log n)
```

```
level 0 : [============ n ============]     kerja n
level 1 : [==== n/2 ====][==== n/2 ====]    kerja n
level 2 : [n/4][n/4][n/4][n/4]              kerja n
...
level log n : elemen tunggal                kerja n
```

Berbeda dari quicksort, pembagiannya **selalu** seimbang — tidak ada kasus terburuk
O(n²). Itu jaminan yang berharga.

### Langkah merge

```
kiri  : [2, 4, 5]        i menunjuk ke sini
kanan : [1, 3, 6]        j menunjuk ke sini

ambil yang lebih kecil, majukan penunjuknya:

  i=0(2) vs j=0(1) -> ambil 1, j++     hasil: [1]
  i=0(2) vs j=1(3) -> ambil 2, i++     hasil: [1,2]
  i=1(4) vs j=1(3) -> ambil 3, j++     hasil: [1,2,3]
  i=1(4) vs j=2(6) -> ambil 4, i++     hasil: [1,2,3,4]
  i=2(5) vs j=2(6) -> ambil 5, i++     hasil: [1,2,3,4,5]
  kiri habis -> salin sisa kanan       hasil: [1,2,3,4,5,6]
```

⚠️ Saat seri, ambil dari **kiri** (`a[i] <= a[j]`). Inilah yang membuat merge sort
**stabil**. Menulis `<` alih-alih `<=` akan merusak stabilitas.

### Inversi: ide inti hari ini

```
inversi = pasangan (i, j) dengan i < j dan a[i] > a[j]
```

Ini besaran yang mengukur *"seberapa jauh array dari terurut"*, dan Day 43 sudah
menunjukkan bahwa ia sama dengan **jumlah swap bubble sort**.

**Pengamatan kunci:** saat menggabungkan, kalau kita mengambil elemen dari bagian
**kanan**, itu berarti elemen itu lebih kecil dari **seluruh sisa** bagian kiri.

```
kiri  : [2, 4, 5]     i = 0, sisa = 3 elemen (2, 4, 5)
kanan : [1, 3, 6]     j = 0

Kita ambil 1 dari kanan. Artinya 1 lebih kecil dari 2, 4, DAN 5.
Ketiganya berada di SEBELUM 1 pada array asli.
-> tiga inversi sekaligus, dalam satu langkah.
```

```cpp
if (a[i] <= a[j]) tmp[k++] = a[i++];
else { tmp[k++] = a[j++]; inversi += mid - i; }   // <- satu baris ini saja
```

> **Kenapa `mid − i` dan bukan 1?** Karena bagian kiri **sudah terurut**. Kalau `a[j]`
> lebih kecil dari `a[i]`, ia otomatis lebih kecil dari `a[i+1]`, `a[i+2]`, ... sampai
> `a[mid−1]`. Semuanya sekaligus. Inilah yang mengubah O(n²) menjadi O(n log n):
> kita menghitung banyak inversi dalam satu operasi.

Inversi yang **di dalam** bagian kiri dan **di dalam** bagian kanan sudah dihitung
oleh pemanggilan rekursif. Yang tersisa hanyalah inversi **lintas batas**, dan itulah
yang dihitung saat merge. Tidak ada yang terlewat, tidak ada yang dobel.

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Waktu | Ruang | Stabil |
| ------- | ----- | ----- | ------ |
| Merge sort | O(n log n) **selalu** | O(n) | ✅ |
| Inversion count (merge) | O(n log n) | O(n) | — |
| Inversion count (BIT) | O(n log n) | O(n) | — |
| `std::sort` (introsort) | O(n log n) | O(log n) | ❌ |
| `std::stable_sort` | O(n log n) | O(n) | ✅ |
| Merge k array (heap) | O(N log k) | O(k) | ✅ |

**Merge sort vs `std::sort`:**

| | merge sort | `std::sort` |
| --- | --- | --- |
| Terburuk | O(n log n) dijamin | O(n log n) dijamin (introsort) |
| Ruang tambahan | O(n) | O(log n) |
| Stabil | ya | tidak |
| Kecepatan praktis | lebih lambat ~2× | lebih cepat |
| Bisa menghitung inversi | **ya** | tidak |

Di kontes, pakai `std::sort` untuk mengurutkan. Tulis merge sort hanya kalau kamu
butuh **hasil sampingannya** — dan hasil sampingan yang paling sering dibutuhkan
adalah inversi.

**Batas praktis inversi:** `n = 10^5` menghasilkan paling banyak `n(n−1)/2 ≈ 5·10^9`
inversi. `int` jebol. `long long` **wajib**.

---

## 💻 3. Implementasi C++

### 3.1 Merge sort baku

```cpp
void mergeSort(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return;                  // 0 atau 1 elemen: sudah terurut
    int mid = l + (r - l) / 2;               // hindari overflow l+r

    mergeSort(a, tmp, l, mid);
    mergeSort(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r)
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];   // '<=' -> STABIL
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];

    for (int t = l; t < r; t++) a[t] = tmp[t];
}
```

Dipanggil dengan `mergeSort(a, tmp, 0, n)` — konvensi setengah terbuka `[l, r)`,
yang jauh lebih sedikit menimbulkan off-by-one daripada `[l, r]`.

⚠️ **Alokasikan `tmp` sekali di luar**, bukan di dalam rekursi. Membuat vector baru
di setiap pemanggilan menambahkan biaya alokasi yang bisa membuat kodemu 5× lebih lambat.

### 3.2 Inversion count

```cpp
long long invCount(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;

    long long inv = invCount(a, tmp, l, mid) + invCount(a, tmp, mid, r);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            inv += mid - i;              // <- SATU BARIS yang membedakan
        }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return inv;
}
```

Perbedaan dari merge sort biasa hanya satu baris. Itu sebabnya inversi disebut
"nyaris gratis" di dalam merge sort.

⚠️ `a[i] <= a[j]` — dengan `<=`, elemen kembar **tidak** dihitung sebagai inversi.
Kalau soal mendefinisikan inversi sebagai `a[i] >= a[j]`, ubah menjadi `<`.
Baca definisinya baik-baik.

### 3.3 Pasangan penting: `a[i] > 2·a[j]`

Beberapa soal meminta pasangan dengan kondisi lain, misalnya *"berapa pasangan
(i, j) dengan i < j dan a[i] > 2·a[j]"*. Polanya sama, tetapi penghitungannya
harus **dipisahkan** dari langkah merge:

```cpp
long long hitungPenting(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    long long res = hitungPenting(a, tmp, l, mid) + hitungPenting(a, tmp, mid, r);

    // FASE 1: hitung pasangan, dua pointer terpisah
    int j = mid;
    for (int i = l; i < mid; i++) {
        while (j < r && (long long)a[i] > 2LL * a[j]) j++;
        res += j - mid;
    }

    // FASE 2: merge biasa
    int i2 = l, j2 = mid, k = l;
    while (i2 < mid && j2 < r) tmp[k++] = (a[i2] <= a[j2]) ? a[i2++] : a[j2++];
    while (i2 < mid) tmp[k++] = a[i2++];
    while (j2 < r)   tmp[k++] = a[j2++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return res;
}
```

⚠️ **Kenapa dua fase terpisah?** Karena kondisinya (`> 2·a[j]`) berbeda dari kondisi
yang dipakai merge (`<= a[j]`). Mencoba menggabungkannya menjadi satu loop akan
menghitung salah. Fase 1 memakai two pointers pada dua bagian yang **sudah terurut** —
`j` hanya maju, jadi totalnya tetap O(n) per level.

### 3.4 Merge k array terurut

```cpp
vector<int> mergeK(vector<vector<int>>& arr) {
    // {nilai, indeks array, indeks di dalam array}
    priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;
    for (int i = 0; i < (int)arr.size(); i++)
        if (!arr[i].empty()) pq.push({arr[i][0], i, 0});

    vector<int> hasil;
    while (!pq.empty()) {
        auto [v, ai, idx] = pq.top(); pq.pop();
        hasil.push_back(v);
        if (idx + 1 < (int)arr[ai].size())
            pq.push({arr[ai][idx + 1], ai, idx + 1});
    }
    return hasil;
}
```

O(N log k) dengan N = total elemen. Mengalahkan "gabungkan satu per satu"
yang O(Nk).

### 3.5 Merge sort iteratif (bottom-up)

```cpp
void mergeSortIteratif(vector<int>& a) {
    int n = a.size();
    vector<int> tmp(n);
    for (int lebar = 1; lebar < n; lebar *= 2)
        for (int l = 0; l < n; l += 2 * lebar) {
            int mid = min(l + lebar, n), r = min(l + 2 * lebar, n);
            int i = l, j = mid, k = l;
            while (i < mid && j < r) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
            while (i < mid) tmp[k++] = a[i++];
            while (j < r)   tmp[k++] = a[j++];
            for (int t = l; t < r; t++) a[t] = tmp[t];
        }
}
```

Menghindari rekursi. Berguna kalau batas kedalaman stack menjadi masalah,
atau untuk memahami strukturnya lebih jelas.

---

## 🔄 4. Trace & Simulasi

### 4.1 Merge sort pada `a = [5, 2, 4, 6, 1, 3]`

```
mergeSort(0, 6)
├── mergeSort(0, 3)          [5, 2, 4]
│   ├── mergeSort(0, 1)      [5]                  basis
│   ├── mergeSort(1, 3)      [2, 4]
│   │   ├── mergeSort(1, 2)  [2]                  basis
│   │   ├── mergeSort(2, 3)  [4]                  basis
│   │   └── merge -> [2, 4]
│   └── merge [5] + [2,4] -> [2, 4, 5]
├── mergeSort(3, 6)          [6, 1, 3]
│   ├── mergeSort(3, 4)      [6]                  basis
│   ├── mergeSort(4, 6)      [1, 3]
│   │   └── merge -> [1, 3]
│   └── merge [6] + [1,3] -> [1, 3, 6]
└── merge [2,4,5] + [1,3,6] -> [1, 2, 3, 4, 5, 6]
```

### 4.2 Menghitung inversi pada array yang sama

**Merge `[5]` + `[2, 4]`** (sisa kiri = 1 elemen):

| langkah | bandingkan | ambil | inversi ditambah | alasan |
| ------- | ---------- | ----- | ---------------- | ------ |
| 1 | 5 vs 2 | 2 (kanan) | **+1** | 2 lebih kecil dari sisa kiri: {5} |
| 2 | 5 vs 4 | 4 (kanan) | **+1** | 4 lebih kecil dari {5} |
| 3 | kanan habis | 5 | 0 | — |

```
sub-total = 2   -> pasangan (5,2) dan (5,4)   ✓
```

**Merge `[6]` + `[1, 3]`:**

| langkah | ambil | inversi | alasan |
| ------- | ----- | ------- | ------ |
| 1 | 1 (kanan) | **+1** | 1 < {6} |
| 2 | 3 (kanan) | **+1** | 3 < {6} |

```
sub-total = 2   -> (6,1) dan (6,3)   ✓
```

**Merge `[2, 4, 5]` + `[1, 3, 6]`:**

| i | sisa kiri | bandingkan | ambil | inversi ditambah |
| - | --------- | ---------- | ----- | ---------------- |
| 0 | {2,4,5} | 2 vs 1 | 1 (kanan) | **+3** |
| 0 | {2,4,5} | 2 vs 3 | 2 (kiri) | 0 |
| 1 | {4,5} | 4 vs 3 | 3 (kanan) | **+2** |
| 1 | {4,5} | 4 vs 6 | 4 (kiri) | 0 |
| 2 | {5} | 5 vs 6 | 5 (kiri) | 0 |
| 3 | {} | kiri habis | 6 | 0 |

```
sub-total = 5
```

```
TOTAL = 2 + 2 + 5 = 9
```

Verifikasi manual pada `[5, 2, 4, 6, 1, 3]`:

```
(5,2) (5,4) (5,1) (5,3)   -> 4
(2,1)                      -> 1
(4,1) (4,3)                -> 2
(6,1) (6,3)                -> 2
                    total = 9   ✓
```

Perhatikan langkah pertama merge terakhir: mengambil `1` menambahkan **3** sekaligus,
karena `1` lebih kecil dari `2`, `4`, dan `5` — semuanya berada sebelum `1` pada array
asli. Inilah yang membuat algoritmanya O(n log n) alih-alih O(n²).

### 4.3 Stabilitas merge sort

```
kiri  : [(2, 'a')]        kanan : [(2, 'b')]

dengan a[i] <= a[j] : 2 <= 2 benar -> ambil dari KIRI dulu
   hasil: [(2,'a'), (2,'b')]     urutan asli terjaga  ✓

dengan a[i] < a[j]  : 2 < 2 salah -> ambil dari KANAN dulu
   hasil: [(2,'b'), (2,'a')]     urutan asli RUSAK    ✗
```

Satu karakter, dan itulah seluruh perbedaan antara stabil dan tidak.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "berapa pasangan (i,j), i<j, a[i]>a[j]" | inversi via merge |
| "berapa swap berdampingan minimum" | inversi (Day 43) |
| "berapa pergeseran insertion sort" | inversi |
| "pasangan dengan a[i] > 2·a[j]" | merge dua fase |
| "gabungkan k array terurut" | heap, O(N log k) |
| "harus stabil dan n besar" | `stable_sort` |
| "hitung elemen lebih kecil di kanan, per posisi" | merge + pelacakan indeks, atau BIT |
| "median dari dua array terurut" | binary search pada partisi, bukan merge |

### Pattern: count of smaller after self

*Untuk setiap `i`, berapa `j > i` dengan `a[j] < a[i]`?*

Merge sort bisa melakukannya, tetapi kamu harus mengurutkan **indeks**, bukan nilai,
agar bisa mengaitkan hitungan ke posisi aslinya. BIT + kompresi (Day 38 + 170)
biasanya lebih mudah ditulis untuk varian ini.

### Pattern: inversi antara dua permutasi

*Berapa banyak pasangan yang urutannya berbeda antara permutasi A dan B?*

Petakan setiap nilai ke posisinya di `B`, lalu hitung inversi pada array hasil
pemetaan. Trik "ubah masalah dua objek menjadi masalah satu objek" ini sering muncul.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`int` untuk hitungan inversi.** `n = 10^5` bisa menghasilkan `5·10^9`.

2. **`inv += 1` alih-alih `inv += mid − i`.** Ini menghasilkan angka yang jauh lebih
   kecil dan sekilas terlihat masuk akal — bug yang sulit dilihat tanpa stress test.

3. **`inv += mid − i` ditulis setelah `i` berubah.** Urutan operasi penting;
   `i` tidak boleh sudah maju saat dipakai menghitung.

4. **`<` alih-alih `<=`** merusak stabilitas dan, pada penghitungan inversi, ikut
   menghitung pasangan kembar.

5. **Mengalokasikan `tmp` di dalam rekursi.** Bisa membuat kodemu beberapa kali
   lebih lambat.

6. **`mid = (l + r) / 2` pada indeks besar.** Untuk `l, r` di dekat `2^31` ini overflow.
   Pakai `l + (r − l) / 2` sebagai kebiasaan.

7. **Lupa menyalin `tmp` kembali ke `a`.** Rekursi berikutnya akan membaca data lama.

8. **Mencampur konvensi `[l, r)` dan `[l, r]`.** Pilih setengah terbuka dan konsisten.

### Edge cases wajib diuji

```
n = 0, n = 1              -> basis rekursi, tidak boleh crash
array sudah terurut       -> inversi = 0
array terurut terbalik    -> inversi = n(n-1)/2, kasus maksimum
semua elemen sama         -> inversi = 0 (dengan definisi a[i] > a[j])
dua elemen                -> kasus terkecil yang bermakna
nilai negatif             -> tidak masalah
```

---

## 🏆 7. Tips Contest

**Kapan menulis merge sort?** Hampir hanya kalau kamu butuh **inversi**.
Untuk mengurutkan saja, `std::sort` lebih cepat dan lebih pendek.

**Tiga cara menghitung inversi — pilih yang mana?**

| Cara | Kompleksitas | Kelebihan |
| ---- | ------------ | --------- |
| Merge sort | O(n log n) | tidak butuh kompresi, ruang O(n) |
| BIT + kompresi | O(n log n) | lebih mudah diperluas ke varian lain |
| `policy_based` ordered set | O(n log n) | paling pendek ditulis |

Untuk inversi murni, merge sort biasanya paling cepat. Untuk varian
("berapa yang lebih kecil di kanan **per posisi**", "inversi pada rentang"),
BIT lebih fleksibel.

**Kebiasaan yang menyelamatkan:** simpan merge sort + inversi sebagai **satu fungsi**
di template. Perbedaannya cuma satu baris, jadi tidak ada alasan menyimpan dua versi.

**Stress test wajib untuk soal inversi.** Bug `+= 1` alih-alih `+= mid − i` tidak
akan terlihat pada sampel kecil. Tulis brute force O(n²), bandingkan pada 1000 array
acak berukuran ≤ 8. Lima menit, dan hampir semua bug tertangkap.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MERGE SORT & INVERSION COUNT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  mergeSort(l, r)  konvensi SETENGAH TERBUKA [l, r)
    if (r - l <= 1) return;
    mid = l + (r - l) / 2;          <- hindari overflow
    rekursi kiri, rekursi kanan, lalu MERGE

  MERGE (stabil karena '<='):
    tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];

  INVERSI -- satu baris tambahan:
    else { tmp[k++] = a[j++]; inv += mid - i; }
                                    ^^^^^^^^^
    KENAPA mid - i: kiri sudah terurut, jadi a[j] lebih kecil dari
    SELURUH sisa kiri sekaligus.

  inv WAJIB long long   (n=1e5 -> 5e9)
  tmp dialokasikan SEKALI di luar rekursi

  VARIAN a[i] > 2*a[j] : DUA FASE terpisah
    fase 1 two pointers untuk menghitung, fase 2 merge biasa

  MERGE K ARRAY: heap, O(N log k)

  KAPAN PAKAI
    mau urut saja        -> std::sort (lebih cepat, lebih pendek)
    butuh stabil         -> stable_sort
    butuh INVERSI        -> merge sort  <- satu-satunya alasan nyata
    varian per-posisi    -> BIT + kompresi (Day 38 + 170)

  STRESS TEST WAJIB: brute force O(n^2) vs merge, 1000 array acak
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | inversi klasik |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | sort + two pointers |
| [LeetCode 493 — Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | LeetCode | `a[i] > 2·a[j]` |
| [LeetCode 315 — Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | LeetCode | per posisi |
| [LeetCode 88 — Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) | LeetCode | merge in-place |
| [LeetCode 23 — Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | LeetCode | heap |
| [UVa 10810 — Ultra QuickSort](https://onlinejudge.org/) | UVa | inversi |
| [CF 1042D / 1324D](https://codeforces.com/problemset) | Codeforces | inversi + prefix |
| [HackerRank — Merge Sort: Counting Inversions](https://www.hackerrank.com/challenges/ctci-merge-sort/) | HackerRank | inversi |

---

**Selanjutnya:** Day 45 — Quick Sort, Quickselect & `nth_element`. Di sana kamu akan
melihat sisi lain dari divide and conquer: pembagiannya **tidak dijamin seimbang**,
sehingga ada kasus terburuk O(n²) — tetapi sebagai gantinya ia bekerja **di tempat**
dan memberi `nth_element` yang O(n).
