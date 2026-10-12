# 📊 Day 46: Counting Sort, Radix Sort & Bucket Sort

> **Prasyarat:** Frequency Array (Day 40), Prefix Sum (Day 29), Sorting (Day 43–45)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"nilai kecil"*, *"n sangat besar"*, *"urutkan string"*, *"batas waktu ketat"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 46, kamu akan mampu:

- [ ] Menjelaskan batas bawah **Ω(n log n)** untuk pengurutan berbasis perbandingan
- [ ] Menjelaskan kenapa counting sort **tidak melanggar** batas itu
- [ ] Menulis counting sort yang **stabil** dengan prefix sum
- [ ] Menulis **radix sort LSD** dan menjelaskan kenapa stabilitas menjadi syarat mutlak
- [ ] Memilih **ukuran digit** (basis) yang tepat dan menghitung akibatnya
- [ ] Menangani **bilangan negatif** dan **string**
- [ ] Memutuskan kapan non-komparasi mengalahkan `std::sort` — dengan angka

---

## 🔍 1. Konsep & Intuisi

### Batas bawah Ω(n log n) dan cara melewatinya

Setiap algoritma pengurutan yang bekerja **hanya dengan membandingkan** dua elemen
punya batas bawah `Ω(n log n)`. Alasannya singkat:

```
ada n! kemungkinan urutan awal
setiap perbandingan memberi 1 bit informasi (lebih besar / lebih kecil)
butuh setidaknya log2(n!) bit untuk membedakan seluruh kemungkinan
log2(n!) ~ n log2(n)   (aproksimasi Stirling)
```

Merge sort, quicksort, heapsort — semuanya tunduk pada batas ini.

**Counting sort tidak melanggarnya**, ia hanya berada **di luar model**: ia tidak
pernah membandingkan dua elemen sama sekali. Ia memakai nilai elemen **langsung
sebagai alamat memori**. Informasi yang didapat dari satu operasi jauh lebih banyak
daripada satu bit.

> Ini pelajaran yang lebih umum: kalau sebuah batas bawah menghalangimu, periksa
> apakah asumsinya benar-benar berlaku pada masalahmu. Sering kali jalan keluarnya
> bukan algoritma yang lebih pintar, melainkan **model yang berbeda**.

### Analogi: menyortir surat berdasarkan kode pos

Petugas pos tidak membandingkan dua surat untuk menentukan mana yang lebih dulu.
Ia melihat kode posnya dan **langsung memasukkannya ke kotak yang sesuai**.
Setelah semua surat masuk, ia mengambil isi kotak berurutan dari kotak pertama.

Tidak ada perbandingan. Itulah counting sort.

### Counting sort: tiga langkah

```
a = [4, 2, 2, 8, 3, 3, 1]      nilai 0..8

Langkah 1 — hitung frekuensi
   nilai :  0  1  2  3  4  5  6  7  8
   cnt   :  0  1  2  2  1  0  0  0  1

Langkah 2 — prefix sum (berapa elemen bernilai <= v)
   cnt   :  0  1  3  5  6  6  6  6  7

Langkah 3 — tempatkan, JALAN MUNDUR agar STABIL
   hasil : [1, 2, 2, 3, 3, 4, 8]
```

⚠️ **Kenapa langkah 3 berjalan mundur?** Karena `cnt[v]` setelah prefix sum
menyatakan *"posisi terakhir + 1 untuk nilai v"*. Dengan menyapu dari belakang dan
mengurangi `cnt[v]` sebelum menulis, elemen yang **belakangan** pada input ditempatkan
di posisi yang **lebih belakang** juga — dan itulah definisi stabil.

Menyapu maju juga menghasilkan array terurut, tetapi urutan elemen berkunci sama
menjadi terbalik. Untuk mengurutkan bilangan polos itu tidak terasa; untuk radix sort
itu **fatal**, seperti akan kita lihat.

### Radix sort: counting sort berlapis

Bagaimana kalau nilainya sampai `10^9`? Array `cnt` sebesar itu mustahil.

Radix sort memecah setiap bilangan menjadi **digit** (dalam basis tertentu) dan
mengurutkan digit demi digit, dari yang **paling tidak signifikan** ke yang paling
signifikan (LSD — Least Significant Digit).

```
a = [170, 45, 75, 90, 802, 24, 2, 66]

lewat 1 (satuan) : [170, 90, 802, 2, 24, 45, 75, 66]
                     ↑0   ↑0  ↑2  ↑2  ↑4  ↑5  ↑5  ↑6

lewat 2 (puluhan): [802, 2, 24, 45, 66, 170, 75, 90]
                     ↑0  ↑0 ↑2  ↑4  ↑6  ↑7  ↑7  ↑9

lewat 3 (ratusan): [2, 24, 45, 66, 75, 90, 170, 802]
                    ↑0 ↑0  ↑0  ↑0  ↑0  ↑0  ↑1   ↑8
```

⚠️ **Stabilitas adalah syarat mutlak di sini.** Setelah lewat pertama, urutan
berdasarkan satuan sudah benar. Lewat kedua mengurutkan berdasarkan puluhan —
dan untuk bilangan dengan puluhan yang sama, urutan hasil lewat pertama **harus
dipertahankan**. Kalau counting sort yang dipakai tidak stabil, radix sort menghasilkan
sampah.

Inilah alasan sesungguhnya kita repot dengan "jalan mundur" di langkah 3.

### Bucket sort

Kalau data tersebar **seragam** pada suatu rentang, bagi rentang itu menjadi `n`
ember, lempar setiap elemen ke embernya, urutkan isi tiap ember, lalu gabungkan.

```
data seragam di [0, 1), n = 5
ember: [0,0.2) [0.2,0.4) [0.4,0.6) [0.6,0.8) [0.8,1)
```

Rata-rata setiap ember berisi 1 elemen, sehingga totalnya O(n). Tetapi kalau
distribusinya **tidak** seragam (semua masuk satu ember), ia degenerasi menjadi
kompleksitas algoritma pengurutan ember itu — biasanya O(n²) atau O(n log n).

Di kontes, bucket sort jarang dipakai karena asumsi keseragamannya rapuh.
Counting dan radix jauh lebih dapat diandalkan.

---

## 🧮 2. Analisis Kompleksitas

| Algoritma | Waktu | Ruang | Stabil | Syarat |
| --------- | ----- | ----- | ------ | ------ |
| Counting sort | O(n + V) | O(n + V) | ✅ | V (rentang nilai) kecil |
| Radix sort LSD | O(d · (n + B)) | O(n + B) | ✅ | nilai bilangan bulat |
| Bucket sort | O(n) rata-rata | O(n) | tergantung | distribusi seragam |
| `std::sort` | O(n log n) | O(log n) | ❌ | — |

`V` = rentang nilai, `d` = banyak digit, `B` = basis.

### Kapan counting sort menang? Hitung, jangan tebak

```
counting sort : n + V
std::sort     : n * log2(n) * c     (c ~ 1.5 untuk konstanta praktis)

n = 10^6, V = 10^6  ->  counting 2*10^6   vs  sort 3*10^7    counting MENANG 15x
n = 10^3, V = 10^6  ->  counting 10^6     vs  sort 1.5*10^4  sort MENANG 60x
n = 10^6, V = 10^9  ->  counting MUSTAHIL (4 GB memori)
```

Aturan praktisnya: **counting sort menang kalau `V` sebanding atau lebih kecil
daripada `n log n`.** Kalau `V` jauh lebih besar dari `n`, kamu membayar untuk slot
kosong yang tidak pernah dipakai.

### Memilih basis radix sort

```
nilai sampai 2^32, basis B, banyak lewat d = 32 / log2(B)

B = 10    -> d = 10 lewat, cnt kecil          lambat
B = 256   -> d = 4 lewat,  cnt 256 slot       BAGUS
B = 65536 -> d = 2 lewat,  cnt 65536 slot     lebih cepat, memori masih kecil
B = 2^32  -> d = 1 lewat,  cnt 4 miliar slot  MUSTAHIL
```

`B = 256` (satu byte per lewat) adalah pilihan yang lazim: `d = 4` untuk `int`,
`cnt` hanya 1 KB sehingga muat di cache L1, dan pengambilan digitnya cukup
`(x >> shift) & 255` — sangat murah.

**Angka nyata:** untuk mengurutkan `10^7` bilangan `int` acak, radix sort basis 256
biasanya **2–3× lebih cepat** daripada `std::sort`. Itu selisih yang bisa menentukan
AC atau TLE pada soal berbatas waktu ketat.

---

## 💻 3. Implementasi C++

### 3.1 Counting sort (versi sederhana, tanpa data terkait)

```cpp
void countingSortSederhana(vector<int>& a, int maks) {
    vector<int> cnt(maks + 1, 0);
    for (int x : a) cnt[x]++;

    int idx = 0;
    for (int v = 0; v <= maks; v++)
        while (cnt[v]--) a[idx++] = v;
}
```

Cukup kalau elemennya hanya bilangan polos. Tidak berlaku kalau setiap elemen
membawa data lain (misalnya `pair<nilai, nama>`), karena kita menulis ulang nilainya
alih-alih memindahkan objeknya.

### 3.2 Counting sort STABIL (versi yang benar-benar dipakai)

```cpp
vector<int> countingSortStabil(const vector<int>& a, int maks) {
    int n = a.size();
    vector<int> cnt(maks + 1, 0), hasil(n);

    for (int x : a) cnt[x]++;                       // 1. frekuensi
    for (int v = 1; v <= maks; v++) cnt[v] += cnt[v - 1];   // 2. prefix sum

    for (int i = n - 1; i >= 0; i--)                // 3. MUNDUR -> stabil
        hasil[--cnt[a[i]]] = a[i];

    return hasil;
}
```

Tiga baris kunci. Perhatikan `--cnt[a[i]]`: pengurangan terjadi **sebelum** dipakai
sebagai indeks, karena `cnt[v]` menyatakan "posisi terakhir + 1".

### 3.3 Counting sort untuk data berpasangan

```cpp
struct Item { int kunci; int data; };

vector<Item> countingSortItem(const vector<Item>& a, int maks) {
    int n = a.size();
    vector<int> cnt(maks + 1, 0);
    vector<Item> hasil(n);

    for (auto& it : a) cnt[it.kunci]++;
    for (int v = 1; v <= maks; v++) cnt[v] += cnt[v - 1];
    for (int i = n - 1; i >= 0; i--) hasil[--cnt[a[i].kunci]] = a[i];

    return hasil;
}
```

Inilah bentuk yang dipakai sebagai bahan bakar radix sort dan konstruksi suffix array
(Day 220).

### 3.4 Menangani bilangan negatif

Dua cara:

```cpp
// Cara 1 — geser dengan offset
int mn = *min_element(a.begin(), a.end());
for (int& x : a) x -= mn;            // sekarang semuanya >= 0
countingSort(a, maks - mn);
for (int& x : a) x += mn;            // kembalikan
```

```cpp
// Cara 2 — pada radix sort, balik bit tanda pada lewat terakhir
// karena representasi two's complement membuat bilangan negatif
// terlihat lebih BESAR kalau dibaca sebagai unsigned
```

Cara 1 lebih mudah diingat dan cukup untuk hampir semua soal.

### 3.5 Radix sort LSD basis 256

```cpp
void radixSort(vector<uint32_t>& a) {
    int n = a.size();
    vector<uint32_t> tmp(n);

    for (int shift = 0; shift < 32; shift += 8) {
        int cnt[256] = {0};

        for (uint32_t x : a) cnt[(x >> shift) & 255]++;
        for (int v = 1; v < 256; v++) cnt[v] += cnt[v - 1];
        for (int i = n - 1; i >= 0; i--)             // MUNDUR -> stabil
            tmp[--cnt[(a[i] >> shift) & 255]] = a[i];

        a.swap(tmp);                                  // swap, bukan salin
    }
}
```

Empat lewat, masing-masing O(n + 256). `a.swap(tmp)` menukar penunjuk internal
vector — O(1), tidak menyalin apa pun.

Untuk `int` bertanda, konversikan dulu dengan `x ^ 0x80000000` (membalik bit tanda),
lalu balikkan setelah selesai. Trik ini membuat urutan `unsigned` sama dengan
urutan `signed`.

### 3.6 Mengurutkan string dengan radix sort

```cpp
// Mengurutkan string yang panjangnya SAMA, dari karakter terakhir ke depan
void radixSortString(vector<string>& a, int L) {
    int n = a.size();
    vector<string> tmp(n);
    for (int pos = L - 1; pos >= 0; pos--) {
        vector<int> cnt(256, 0);
        for (auto& s : a) cnt[(unsigned char)s[pos]]++;
        for (int v = 1; v < 256; v++) cnt[v] += cnt[v - 1];
        for (int i = n - 1; i >= 0; i--)
            tmp[--cnt[(unsigned char)a[i][pos]]] = a[i];
        a.swap(tmp);
    }
}
```

Untuk string berpanjang berbeda, urutkan dulu berdasarkan panjang atau tambahkan
padding — atau pakai MSD radix sort yang lebih rumit.

### 3.7 Bucket sort

```cpp
void bucketSort(vector<double>& a) {              // asumsi nilai di [0, 1)
    int n = a.size();
    vector<vector<double>> ember(n);

    for (double x : a) ember[min(n - 1, (int)(x * n))].push_back(x);
    for (auto& e : ember) sort(e.begin(), e.end());

    int idx = 0;
    for (auto& e : ember) for (double x : e) a[idx++] = x;
}
```

O(n) **hanya kalau** distribusinya seragam. Kalau semua elemen jatuh ke satu ember,
kompleksitasnya menjadi O(n log n) atau lebih buruk.

---

## 🔄 4. Trace & Simulasi

### 4.1 Counting sort stabil pada `a = [4, 2, 2, 8, 3, 3, 1]`

**Langkah 1 — frekuensi:**

```
v   : 0  1  2  3  4  5  6  7  8
cnt : 0  1  2  2  1  0  0  0  1
```

**Langkah 2 — prefix sum:**

```
v   : 0  1  2  3  4  5  6  7  8
cnt : 0  1  3  5  6  6  6  6  7
              ↑
       "ada 5 elemen bernilai <= 3"
```

**Langkah 3 — penempatan mundur:**

| i | a[i] | `--cnt[a[i]]` | tulis di | hasil |
| - | ---- | ------------- | -------- | ----- |
| 6 | 1 | 1→0 | 0 | `[1, _, _, _, _, _, _]` |
| 5 | 3 | 5→4 | 4 | `[1, _, _, _, 3, _, _]` |
| 4 | 3 | 4→3 | 3 | `[1, _, _, 3, 3, _, _]` |
| 3 | 8 | 7→6 | 6 | `[1, _, _, 3, 3, _, 8]` |
| 2 | 2 | 3→2 | 2 | `[1, _, 2, 3, 3, _, 8]` |
| 1 | 2 | 2→1 | 1 | `[1, 2, 2, 3, 3, _, 8]` |
| 0 | 4 | 6→5 | 5 | `[1, 2, 2, 3, 3, 4, 8]` |

```
hasil = [1, 2, 2, 3, 3, 4, 8]   ✓
```

Perhatikan baris `i=2` dan `i=1`: dua angka `2` ditempatkan di posisi 2 dan 1.
Yang **belakangan** pada input (indeks 2) mendapat posisi yang **lebih belakang**.
Itulah stabilitas.

### 4.2 Kenapa radix sort hancur tanpa stabilitas

```
a = [21, 12, 11]

lewat 1 (satuan): urut berdasarkan digit satuan
   21(1), 11(1), 12(2)  ->  [21, 11, 12]

lewat 2 (puluhan): urut berdasarkan digit puluhan
   Kedua elemen pertama sama-sama berpuluhan 1 dan 2:
   21(2), 11(1), 12(1)

   DENGAN STABIL: 11 dan 12 mempertahankan urutan hasil lewat 1
     -> [11, 12, 21]   ✓ BENAR

   TANPA STABIL: 11 dan 12 boleh tertukar
     -> [12, 11, 21]   ✗ SALAH
```

Informasi dari lewat sebelumnya **hanya** tersimpan dalam urutan relatif.
Stabilitas adalah satu-satunya yang menjaganya.

### 4.3 Radix sort basis 10 pada `[170, 45, 75, 90, 802, 24, 2, 66]`

```
awal          : 170  45  75  90  802  24   2  66

lewat satuan  : 170  90  802   2  24  45  75  66
                 ↑0   ↑0   ↑2  ↑2  ↑4  ↑5  ↑5  ↑6

lewat puluhan : 802   2  24  45  66  170  75  90
                 ↑0  ↑0  ↑2  ↑4  ↑6   ↑7  ↑7  ↑9

lewat ratusan :   2  24  45  66  75  90  170  802
                 ↑0  ↑0  ↑0  ↑0  ↑0  ↑0   ↑1   ↑8
```

Perhatikan lewat puluhan: `802` dan `2` sama-sama berdigit puluhan `0`, dan urutan
relatifnya (802 sebelum 2) diwarisi dari lewat satuan. Pada lewat ratusan urutan itu
akhirnya diperbaiki karena digit ratusannya berbeda.

### 4.4 Kapan counting sort kalah

```
n = 1000, nilai sampai 10^6

counting sort : 1000 + 10^6 = 1.001 * 10^6 operasi
std::sort     : 1000 * log2(1000) * 1.5 ~ 1.5 * 10^4 operasi

std::sort MENANG sekitar 60 kali lipat.
```

Kita membayar untuk 999.000 slot yang tidak pernah dipakai. Ini kesalahan yang
sering terjadi: memakai counting sort secara refleks tanpa memeriksa apakah `V`
sebanding dengan `n`.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| `n` besar, nilai ≤ 10^6 | counting sort |
| `n` besar, nilai ≤ 10^9, batas waktu ketat | radix sort |
| nilai ≤ 10^9 tetapi `n` kecil | `std::sort` |
| nilai ≤ 10^9, butuh array frekuensi | kompresi (Day 38) lalu counting |
| urutkan string berpanjang sama | radix sort per karakter |
| urutkan pasangan (kunci kecil, data) | counting sort stabil |
| "urutkan lalu jawab query rentang nilai" | counting + prefix (Day 40) |
| konstruksi suffix array | counting sort berulang (Day 220) |

### Pattern: mengurutkan berdasarkan dua kunci

Radix sort mengajarkan pola umum yang sangat berguna:

```
Untuk mengurutkan berdasarkan (kunci1, kunci2):
  urutkan berdasarkan kunci2 DULU (yang kurang penting),
  lalu urutkan berdasarkan kunci1 SECARA STABIL.
```

Ini bekerja untuk pengurutan apa pun, bukan hanya radix. Berguna kalau kamu
punya beberapa kunci dengan prioritas berbeda dan tidak ingin menulis komparator
yang rumit (Day 47).

### Pattern: counting sort sebagai bagian algoritma lain

Counting sort muncul kembali di:

- **Suffix array** (Day 220) — pengurutan pasangan peringkat, O(n log n) alih-alih O(n log²n).
- **Topological sort** — bucket berdasarkan derajat masuk.
- **Sieve dan tabulasi** — semuanya adalah "indeks sebagai alamat".

Menguasainya sekarang membuat materi-materi itu terasa akrab nanti.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Menyapu maju di langkah penempatan.** Hasilnya tetap terurut untuk bilangan
   polos, tetapi **tidak stabil** — dan radix sort langsung hancur.

2. **Memakai counting sort saat `V >> n`.** Untuk `n = 1000` dan `V = 10^9`,
   ini MLE atau sangat lambat. Selalu hitung dulu.

3. **Lupa bilangan negatif.** Indeks array negatif adalah perilaku tak terdefinisi
   yang sering tidak crash — bug senyap. Pakai offset.

4. **`cnt` dialokasikan di dalam loop radix.** Empat alokasi tidak masalah, tetapi
   kalau lewatnya banyak, ini terasa. Deklarasikan array biasa di dalam loop
   (murah) atau reset array luar.

5. **Menyalin `tmp` ke `a` alih-alih `swap`.** `swap` pada vector adalah O(1);
   penyalinan O(n). Untuk 4 lewat, ini 4n penyalinan yang bisa dihindari.

6. **Radix sort pada `int` bertanda tanpa penyesuaian.** Bilangan negatif akan
   terurut **setelah** yang positif, karena bit tandanya bernilai 1.

7. **Array `cnt` berukuran besar di dalam fungsi.** `int cnt[1000000]` di stack
   menyebabkan segmentation fault. Deklarasikan global atau pakai `vector`.

8. **Mengira bucket sort selalu O(n).** Hanya kalau distribusinya seragam.

### Edge cases wajib diuji

```
semua elemen sama          -> counting sort O(n + V), tetap benar
n = 1                      -> jangan crash
nilai 0                    -> indeks 0 valid, tidak perlu perlakuan khusus
nilai negatif              -> wajib offset
nilai maksimum tepat di batas array cnt  -> ukuran harus maks+1, bukan maks
array kosong               -> loop tidak boleh berjalan
data berpasangan           -> uji stabilitasnya secara eksplisit
```

---

## 🏆 7. Tips Contest

**Pertanyaan pertama sebelum memilih:** berapa `n` dan berapa `V`?

```
V <= 10^6 dan V <= n log n     ->  counting sort
V <= 2^32 dan n >= 10^6 dan waktu ketat  ->  radix sort basis 256
selain itu                     ->  std::sort
```

**Kapan ini benar-benar menyelamatkan?** Soal dengan `n = 10^7` dan batas waktu
1 detik. `std::sort` sekitar 1.2 detik, radix sort sekitar 0.4 detik. Jarang, tetapi
saat terjadi, tidak ada alternatif lain.

**Yang lebih sering berguna daripada algoritmanya:** pola *"urutkan berdasarkan
kunci kurang penting dulu, lalu kunci penting secara stabil"*. Pola ini menyelesaikan
banyak soal pengurutan multi-kriteria tanpa komparator rumit.

**Jangan lupa alternatif yang lebih sederhana:** kalau kamu hanya butuh array
terurut dari nilai kecil, kadang array frekuensi + sapuan sudah cukup dan kamu
tidak perlu "mengurutkan" sama sekali (Day 40).

**Peringatan:** jangan menulis radix sort di kontes kecuali kamu sudah menyimpannya
di template dan yakin `std::sort` tidak cukup. Menulisnya dari nol saat kontes
memakan 10 menit dan berisiko salah.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  PENGURUTAN NON-KOMPARASI
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  BATAS BAWAH: pengurutan berbasis PERBANDINGAN >= n log n
  Counting sort tidak melanggarnya -- ia di LUAR model
  (memakai nilai sebagai ALAMAT, bukan membandingkan)

  COUNTING SORT STABIL (tiga langkah):
    1. for (x : a) cnt[x]++;
    2. for (v = 1..maks) cnt[v] += cnt[v-1];
    3. for (i = n-1 DOWNTO 0) hasil[--cnt[a[i]]] = a[i];
                ^^^^^^^^^^^^ MUNDUR = STABIL

  RADIX SORT LSD basis 256 (4 lewat untuk 32 bit):
    for (shift = 0; shift < 32; shift += 8)
        counting sort STABIL pada (x >> shift) & 255
    a.swap(tmp)   <- O(1), jangan menyalin

  STABILITAS ADALAH SYARAT MUTLAK radix sort.
  Tanpa stabil, informasi dari lewat sebelumnya HILANG.

  KAPAN MENANG (hitung, jangan tebak)
    counting : n + V      menang kalau V <~ n log n
    radix    : 4(n + 256) menang untuk n >= 1e6, ~2-3x std::sort
    sort     : n log n    aman untuk hampir semua kasus lain

  NEGATIF: geser dengan offset, atau balik bit tanda pada radix
  cnt BESAR: deklarasikan GLOBAL, jangan di stack

  POLA UMUM YANG LEBIH BERGUNA:
    urutkan kunci KURANG PENTING dulu, lalu kunci PENTING secara STABIL
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1091 — Concert Tickets](https://cses.fi/problemset/task/1091) | CSES | pemilihan |
| [LeetCode 912 — Sort an Array](https://leetcode.com/problems/sort-an-array/) | LeetCode | implementasi bebas |
| [LeetCode 164 — Maximum Gap](https://leetcode.com/problems/maximum-gap/) | LeetCode | bucket sort O(n) |
| [LeetCode 1122 — Relative Sort Array](https://leetcode.com/problems/relative-sort-array/) | LeetCode | counting sort |
| [CF 977D / Div3 sorting](https://codeforces.com/problemset) | Codeforces | pengurutan kustom |
| [SPOJ CODESPTB](https://www.spoj.com/problems/CODESPTB/) | SPOJ | inversi |
| [ABC 224 D / ABC 209 C](https://atcoder.jp/) | AtCoder | counting |
| [UVa 11462 — Age Sort](https://onlinejudge.org/) | UVa | counting sort murni |

---

**Selanjutnya:** Day 47 (sudah kamu selesaikan) — Sorting Multi-Kriteria & Stabilitas.
Pola *"kunci kurang penting dulu, lalu kunci penting secara stabil"* yang kamu temukan
di radix sort hari ini adalah **inti** dari materi itu. Setelah itu Day 48 memulai
blok binary search.
