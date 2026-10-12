# 📊 Day 45: Quick Sort, Quickselect & nth_element

> **Prasyarat:** Rekursi, Merge Sort (Day 44), Sorting O(n²) (Day 43)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"elemen terkecil ke-k"*, *"median"*, *"k terbesar"*, *"partisi"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 45, kamu akan mampu:

- [ ] Menulis **partisi Lomuto** dan **Hoare**, serta tahu bedanya
- [ ] Menjelaskan kenapa quicksort punya kasus terburuk **O(n²)** dan merge sort tidak
- [ ] Menjelaskan kenapa **pivot acak** menyelesaikan masalah itu di praktik
- [ ] Menulis **quickselect** dan menjelaskan kenapa rata-ratanya **O(n)**
- [ ] Memakai `nth_element`, `partial_sort`, dan `partition` dari STL
- [ ] Menangani **banyak elemen kembar** dengan partisi tiga arah (Dutch flag)
- [ ] Memilih antara `sort`, `partial_sort`, dan `nth_element` secara sadar

---

## 🔍 1. Konsep & Intuisi

### Kebalikan dari merge sort

```
MERGE SORT  : bagi secara buta (di tengah)  ->  kerja saat MENGGABUNG
QUICK SORT  : kerja saat MEMBAGI (partisi)  ->  gabung gratis (tidak ada)
```

Setelah partisi, bagian kiri **seluruhnya** ≤ pivot dan bagian kanan **seluruhnya**
≥ pivot. Begitu kedua bagian terurut, seluruh array terurut — tanpa langkah
penggabungan apa pun.

```
[5, 2, 8, 1, 9, 3]      pivot = 3

partisi:
[2, 1] [3] [5, 8, 9]
 ≤3         ≥3

lalu urutkan kiri dan kanan secara rekursif. Selesai — tidak ada merge.
```

### Konsekuensi: pembagian tidak dijamin seimbang

```
BAIK (pivot mendekati median):
   n -> n/2 + n/2 -> kedalaman log n -> O(n log n)

BURUK (pivot selalu ekstrem):
   n -> 0 + (n-1) -> kedalaman n -> O(n^2)
```

Kapan kasus buruk terjadi? Kalau pivot selalu elemen terkecil atau terbesar.
Dengan pivot = elemen terakhir, array yang **sudah terurut** memicu kasus terburuk —
ironis, dan justru sering terjadi pada data nyata.

> **Pertahanan:** pilih pivot **secara acak**. Peluang mendapat pembagian buruk
> berulang kali menjadi sangat kecil, dan yang lebih penting: **penyerang tidak bisa
> menyusun input yang memicu kasus terburuk**, karena ia tidak tahu bilangan acakmu.

⚠️ Di Codeforces, `std::sort` yang memakai pivot deterministik pernah bisa di-hack.
Pustaka modern memakai **introsort** (quicksort yang beralih ke heapsort saat
kedalaman terlalu dalam), sehingga `std::sort` sekarang dijamin O(n log n).
Tetapi kalau kamu menulis quicksort sendiri, **wajib** memakai pivot acak.

### Quickselect: mencari elemen ke-k tanpa mengurutkan

Setelah partisi, kita tahu **persis** posisi akhir pivot. Kalau posisi itu sudah
sama dengan `k`, kita selesai. Kalau tidak, kita hanya perlu **satu sisi** saja.

```
cari elemen terkecil ke-3 (indeks 2) dari [5, 2, 8, 1, 9, 3]

partisi dengan pivot 3 -> [2, 1, 3, 5, 8, 9], pivot di indeks 2
indeks 2 == k=2  ->  jawabannya 3.  SELESAI.

Kita tidak pernah mengurutkan [5, 8, 9] sama sekali.
```

**Kenapa rata-ratanya O(n)?** Karena kita hanya menelusuri satu sisi:

```
n + n/2 + n/4 + n/8 + ... = 2n  ->  O(n)
```

Bandingkan dengan merge sort yang harus memproses **kedua** sisi, menghasilkan
`n log n`. Membuang setengah pekerjaan di setiap level adalah perbedaan antara
`O(n log n)` dan `O(n)`.

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Rata-rata | Terburuk | Ruang | Stabil |
| ------- | --------- | -------- | ----- | ------ |
| Quicksort (pivot acak) | O(n log n) | O(n²) sangat kecil peluangnya | O(log n) | ❌ |
| Quicksort (pivot tetap) | O(n log n) | **O(n²)** mudah dipicu | O(log n) | ❌ |
| Quickselect | **O(n)** | O(n²) | O(1) | — |
| Median of medians | O(n) | **O(n) dijamin** | O(n) | — |
| `nth_element` | O(n) | O(n) dijamin (introselect) | O(1) | — |
| `partial_sort` (k terkecil) | O(n log k) | O(n log k) | O(1) | ❌ |
| `sort` | O(n log n) | O(n log n) | O(log n) | ❌ |

### Perbandingan praktis untuk "cari k terkecil"

```
n = 10^6, k = 10

sort lalu ambil k pertama    : ~10^6 * 20 = 2*10^7   operasi
partial_sort                 : ~10^6 * log(10) ~ 3*10^6
nth_element                  : ~10^6                  <- tercepat
```

Kalau kamu hanya butuh **elemen ke-k** (bukan k elemen terurut), `nth_element`
adalah jawaban yang benar. Kalau butuh k elemen **terurut**, `partial_sort`.

---

## 💻 3. Implementasi C++

### 3.1 Partisi Lomuto (lebih mudah diingat)

```cpp
// Mengembalikan posisi akhir pivot. Rentang inklusif [lo, hi].
int partisiLomuto(vector<int>& a, int lo, int hi) {
    int pivot = a[hi];              // pivot = elemen terakhir
    int i = lo;                     // batas: a[lo..i-1] semuanya <= pivot
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);              // taruh pivot di tempatnya
    return i;
}
```

Invariant: setelah `j` langkah, `a[lo..i-1]` semuanya ≤ pivot dan `a[i..j-1]`
semuanya > pivot.

Kelemahan: pada array yang **semua elemennya sama**, Lomuto membagi menjadi
`n−1` dan `0` — kasus terburuk. Ini masalah nyata, bukan teoretis.

### 3.2 Quicksort dengan pivot acak

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void quickSort(vector<int>& a, int lo, int hi) {
    while (lo < hi) {
        int r = lo + rng() % (hi - lo + 1);
        swap(a[r], a[hi]);                      // pivot acak -> pindah ke belakang
        int p = partisiLomuto(a, lo, hi);

        // rekursi ke sisi yang LEBIH KECIL, iterasi ke sisi besar
        // -> kedalaman stack dijamin O(log n)
        if (p - lo < hi - p) { quickSort(a, lo, p - 1); lo = p + 1; }
        else                 { quickSort(a, p + 1, hi); hi = p - 1; }
    }
}
```

Dua pertahanan sekaligus:

1. **Pivot acak** — penyerang tidak bisa menyusun input terburuk.
2. **Rekursi ke sisi kecil saja** — kedalaman stack dijamin `O(log n)` meski
   pembagiannya buruk, karena sisi kecil paling besar setengahnya.

⚠️ Jangan memakai `rand()`. Di beberapa sistem `RAND_MAX` hanya 32767, dan
distribusinya buruk. `mt19937` dengan seed dari waktu adalah standar CP.

### 3.3 Quickselect

```cpp
// Mengembalikan elemen terkecil ke-k (0-based) dan MENGUBAH urutan a.
int quickSelect(vector<int>& a, int k) {
    int lo = 0, hi = a.size() - 1;
    while (lo < hi) {
        int r = lo + rng() % (hi - lo + 1);
        swap(a[r], a[hi]);
        int p = partisiLomuto(a, lo, hi);

        if (p == k) return a[p];
        if (p < k) lo = p + 1;      // buang seluruh sisi kiri
        else       hi = p - 1;      // buang seluruh sisi kanan
    }
    return a[lo];
}
```

Perhatikan: **tidak ada rekursi**. Karena kita hanya menelusuri satu sisi,
loop `while` sudah cukup — dan ruangnya menjadi O(1).

### 3.4 Partisi tiga arah (Dutch national flag)

Kalau banyak elemen kembar, Lomuto menjadi lambat. Partisi tiga arah
menempatkan **semua** elemen yang sama dengan pivot di tengah sekaligus:

```cpp
// Setelah selesai: a[lo..lt-1] < pivot, a[lt..gt] == pivot, a[gt+1..hi] > pivot
void partisi3(vector<int>& a, int lo, int hi, int& lt, int& gt) {
    int pivot = a[lo + rng() % (hi - lo + 1)];
    lt = lo; gt = hi;
    int i = lo;
    while (i <= gt) {
        if      (a[i] < pivot) swap(a[lt++], a[i++]);
        else if (a[i] > pivot) swap(a[i], a[gt--]);   // i TIDAK maju
        else                   i++;
    }
}
```

⚠️ Saat menukar dengan `gt`, `i` **tidak boleh maju** — elemen yang baru datang
dari belakang belum diperiksa.

Dengan partisi tiga arah, array berisi satu nilai berulang selesai dalam **O(n)**.

### 3.5 STL: yang sebenarnya kamu pakai di kontes

```cpp
// elemen terkecil ke-k (0-based). Rata-rata O(n).
nth_element(a.begin(), a.begin() + k, a.end());
int jawab = a[k];
// Setelah ini: a[0..k-1] <= a[k] <= a[k+1..n-1], tetapi TIDAK terurut.

// k elemen terkecil, TERURUT. O(n log k).
partial_sort(a.begin(), a.begin() + k, a.end());

// pisahkan berdasarkan predikat, O(n). Mengembalikan batasnya.
auto it = partition(a.begin(), a.end(), [](int x){ return x % 2 == 0; });

// versi stabil, O(n log n) atau O(n) dengan memori tambahan
stable_partition(a.begin(), a.end(), pred);
```

**Median dengan `nth_element`:**

```cpp
int n = a.size();
nth_element(a.begin(), a.begin() + n/2, a.end());
int median = a[n/2];                       // untuk n ganjil
```

Untuk `n` genap kamu butuh dua nilai; panggil `nth_element` dua kali, atau
manfaatkan bahwa setelah panggilan pertama, `max` dari `a[0..n/2-1]` adalah
kandidat kedua.

---

## 🔄 4. Trace & Simulasi

### 4.1 Partisi Lomuto pada `[5, 2, 8, 1, 9, 3]`, pivot = 3 (`a[hi]`)

```
lo=0, hi=5, pivot=3, i=0
```

| j | a[j] | a[j] ≤ 3? | aksi | array | i |
| - | ---- | --------- | ---- | ----- | - |
| 0 | 5 | tidak | — | [5,2,8,1,9,3] | 0 |
| 1 | 2 | ya | swap(a[0], a[1]), i→1 | [2,5,8,1,9,3] | 1 |
| 2 | 8 | tidak | — | [2,5,8,1,9,3] | 1 |
| 3 | 1 | ya | swap(a[1], a[3]), i→2 | [2,1,8,5,9,3] | 2 |
| 4 | 9 | tidak | — | [2,1,8,5,9,3] | 2 |

```
akhir: swap(a[2], a[5])  ->  [2, 1, 3, 5, 9, 8]
                                     ^
                            pivot di indeks 2

kiri  [2, 1]    semuanya <= 3   ✓
kanan [5, 9, 8] semuanya >= 3   ✓
```

Perhatikan bahwa kiri dan kanan **tidak terurut** — itu tugas rekursi berikutnya.

### 4.2 Quickselect mencari elemen terkecil ke-3 (k=2)

```
[5, 2, 8, 1, 9, 3]     k = 2

partisi -> [2, 1, 3, 5, 9, 8], pivot di p = 2
p == k  ->  JAWABANNYA a[2] = 3.  SELESAI.
```

Kita berhenti setelah **satu** partisi. Array `[5, 9, 8]` tidak pernah disentuh lagi.
Bandingkan dengan mengurutkan seluruhnya: kita akan membuang pekerjaan pada bagian
yang jawabannya tidak ada di sana.

### 4.3 Kasus terburuk quicksort

```
a = [1, 2, 3, 4, 5],  pivot = elemen TERAKHIR (deterministik)

partisi pivot=5 -> [1,2,3,4 | 5]   kiri 4 elemen, kanan 0
partisi pivot=4 -> [1,2,3 | 4]     kiri 3 elemen, kanan 0
partisi pivot=3 -> [1,2 | 3]
partisi pivot=2 -> [1 | 2]

kedalaman = n, kerja total = n + (n-1) + ... + 1 = O(n^2)
```

Array yang **sudah terurut** — kasus yang paling sering muncul di data nyata —
justru memicu kasus terburuk. Dengan pivot acak, peluang ini menjadi dapat diabaikan.

### 4.4 Partisi tiga arah pada array penuh kembaran

```
a = [2, 2, 2, 2, 2],  pivot = 2

i=0: a[0]==2 -> i=1
i=1: a[1]==2 -> i=2
...
i=4: a[4]==2 -> i=5, loop selesai

hasil: lt=0, gt=4  ->  seluruh array adalah "sama dengan pivot"
rekursi ke [lo, lt-1] dan [gt+1, hi] -> KEDUANYA KOSONG
-> selesai dalam O(n)
```

Dengan Lomuto, array yang sama akan membelah `4 + 0`, lalu `3 + 0`, dan seterusnya —
`O(n²)`. Perbedaan yang sangat nyata.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "elemen terkecil ke-k" | `nth_element`, O(n) |
| "median" | `nth_element` di `n/2` |
| "k elemen terbesar, terurut" | `partial_sort` dengan komparator terbalik |
| "k elemen terbesar, urutan bebas" | `nth_element` lalu ambil bagiannya |
| "pisahkan genap dan ganjil" | `partition`, O(n) |
| "pisahkan tetapi urutan asli harus terjaga" | `stable_partition` |
| "banyak elemen kembar" | partisi tiga arah |
| "elemen ke-k pada banyak query" | urutkan sekali, O(1) per query |
| "elemen ke-k dengan update" | order statistic tree (Day 180) |

### Pattern: k terbesar dengan heap

Kalau `k` sangat kecil dan `n` sangat besar, heap berukuran `k` mengalahkan semuanya:

```cpp
priority_queue<int, vector<int>, greater<int>> pq;   // min-heap ukuran k
for (int x : a) {
    pq.push(x);
    if ((int)pq.size() > k) pq.pop();                // buang yang terkecil
}
// isi pq = k elemen TERBESAR
```

O(n log k) waktu, **O(k) ruang** — dan yang penting, ia bekerja pada **stream**:
kamu tidak perlu menyimpan seluruh `n` elemen. `nth_element` butuh seluruh array
di memori.

### Pattern: median bergerak

Untuk *"median dari window yang bergerak"*, quickselect **tidak** cocok karena
harus dijalankan ulang setiap langkah. Yang benar adalah **dua heap**
(max-heap untuk separuh bawah, min-heap untuk separuh atas) atau multiset dengan
iterator penunjuk tengah.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Pivot deterministik.** Array terurut memicu O(n²). Selalu acak.

2. **Memakai `rand()`.** `RAND_MAX` bisa hanya 32767, dan `rand() % n` bias.
   Pakai `mt19937`.

3. **Rekursi ke kedua sisi tanpa optimasi ekor.** Kedalaman stack bisa O(n) dan
   menyebabkan stack overflow. Rekursi ke sisi **kecil**, iterasi ke sisi besar.

4. **Lupa bahwa `nth_element` mengubah array.** Setelah dipanggil, urutan elemen
   lain **tidak terdefinisi**. Kalau kamu masih butuh array aslinya, salin dulu.

5. **`i` maju setelah tukar dengan `gt`** pada partisi tiga arah. Elemen yang baru
   datang belum diperiksa.

6. **`k` 1-based vs 0-based.** `nth_element(a.begin(), a.begin()+k, a.end())`
   memberi elemen terkecil ke-`(k+1)`. Ini penyebab off-by-one paling sering.

7. **Menulis quicksort sendiri padahal `std::sort` cukup.** Buang waktu dan
   menambah risiko.

8. **Mengira `nth_element` mengurutkan.** Ia hanya menjamin satu posisi benar dan
   dua sisi terpartisi.

### Edge cases wajib diuji

```
n = 1                  -> quickselect harus langsung mengembalikan a[0]
semua elemen sama      -> Lomuto O(n^2), tiga arah O(n)
array sudah terurut    -> pivot deterministik gagal, pivot acak selamat
array terurut terbalik -> sama
k = 0 dan k = n-1      -> batas ekstrem quickselect
banyak nilai kembar    -> uji partisi tiga arah
```

---

## 🏆 7. Tips Contest

**Aturan praktis:** jangan menulis quicksort. Pakai `std::sort`.
Yang benar-benar berguna dari hari ini adalah **`nth_element`** — dan banyak
peserta tidak tahu fungsi ini ada.

**Pohon keputusan:**

```
Butuh seluruh array terurut?          -> sort
Butuh k elemen terkecil, TERURUT?     -> partial_sort       O(n log k)
Butuh elemen ke-k saja?               -> nth_element        O(n)
Butuh k terbesar dari STREAM?         -> heap ukuran k      O(n log k), ruang O(k)
Butuh memisahkan berdasarkan syarat?  -> partition          O(n)
```

**Kapan menulis partisi sendiri?** Kalau soal meminta sesuatu yang khas, misalnya
*"susun ulang array sehingga semua bilangan genap di depan"* dengan batasan tambahan,
atau saat kamu butuh partisi tiga arah untuk data penuh kembaran.

**Angka yang berguna:** untuk `n = 10^6` dan `k = 10`, `nth_element` sekitar 20×
lebih cepat daripada `sort`. Kalau soalnya ketat waktu dan kamu hanya butuh
elemen ke-k, ini bisa menjadi pembeda.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  QUICK SORT / QUICKSELECT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MERGE: bagi buta -> kerja saat MENGGABUNG
  QUICK: kerja saat MEMBAGI -> gabung gratis

  LOMUTO (pivot = a[hi]):
    i = lo;
    for (j = lo; j < hi; j++) if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]); return i;

  PERTAHANAN WAJIB
    1. pivot ACAK (mt19937, bukan rand())
    2. rekursi ke sisi KECIL, iterasi ke sisi besar -> stack O(log n)

  QUICKSELECT: hanya telusuri SATU sisi
    n + n/2 + n/4 + ... = 2n  ->  O(n) rata-rata

  TIGA ARAH (banyak kembaran):
    a[i] < p -> swap(a[lt++], a[i++])
    a[i] > p -> swap(a[i], a[gt--])      i TIDAK maju
    a[i] == p -> i++

  STL YANG SEBENARNYA DIPAKAI
    nth_element(b, b+k, e)   elemen ke-k (0-based), O(n)
    partial_sort(b, b+k, e)  k terkecil TERURUT, O(n log k)
    partition(b, e, pred)    pisahkan, O(n)
    stable_partition         versi stabil

  nth_element MENGUBAH array dan TIDAK mengurutkan
  k terbesar dari STREAM -> heap ukuran k, ruang O(k)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [LeetCode 215 — Kth Largest Element](https://leetcode.com/problems/kth-largest-element-in-an-array/) | LeetCode | quickselect |
| [LeetCode 973 — K Closest Points](https://leetcode.com/problems/k-closest-points-to-origin/) | LeetCode | `nth_element` |
| [LeetCode 75 — Sort Colors](https://leetcode.com/problems/sort-colors/) | LeetCode | Dutch flag |
| [LeetCode 347 — Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | LeetCode | counting + `nth_element` |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | multiset |
| [SPOJ MKTHNUM — K-th Number](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | k-th pada rentang (persistent) |
| [CF 977C — Less or Equal](https://codeforces.com/problemset/problem/977/C) | Codeforces | pemilihan ke-k |
| [UVa 10041 — Vito's Family](https://onlinejudge.org/) | UVa | median |

---

**Selanjutnya:** Day 46 — Counting, Radix & Bucket Sort. Semua yang kita lihat sejauh
ini adalah pengurutan berbasis **perbandingan**, yang punya batas bawah teoretis
`Ω(n log n)`. Besok kita melanggar batas itu — bukan dengan trik, melainkan dengan
tidak membandingkan sama sekali.
