# 📊 Day 43: Sorting O(n²) — Bubble, Selection, Insertion

> **Prasyarat:** Array (Day 7), Kompleksitas (Day 15–16), Swap & fungsi (Day 6)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"berapa pertukaran"*, *"hampir terurut"*, *"stabil"*, *"simulasikan pengurutan"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 43, kamu akan mampu:

- [ ] Menulis ketiga algoritma dari nol dan menjelaskan **invariant** masing-masing
- [ ] Menjelaskan arti **stabilitas** dan menyebutkan mana yang stabil
- [ ] Menghubungkan **jumlah swap bubble sort** dengan **banyaknya inversi**
- [ ] Menjelaskan kenapa insertion sort **cepat** pada data hampir terurut
- [ ] Menyebutkan kenapa selection sort punya **jumlah swap minimum**
- [ ] Memilih algoritma yang tepat untuk `n` kecil dan kondisi tertentu
- [ ] Memahami kenapa `std::sort` tetap memakai insertion sort di bagian dalamnya

---

## 🔍 1. Konsep & Intuisi

### Kenapa mempelajari algoritma yang "kalah"?

`std::sort` selalu lebih cepat. Tiga algoritma ini tetap dipelajari karena:

1. **Soal kontes sering menanyakan prosesnya**, bukan hasilnya
   (*"berapa pertukaran yang dilakukan bubble sort?"*).
2. **Jumlah swap bubble sort = banyaknya inversi** — sebuah besaran yang muncul
   di banyak soal (Day 44).
3. **Insertion sort benar-benar dipakai** di dalam `std::sort` untuk potongan kecil.
4. Ketiganya melatih cara berpikir **invariant**, yang jauh lebih penting daripada
   algoritmanya sendiri.

### Tiga strategi, tiga invariant

```
BUBBLE SORT — "gelembung naik ke permukaan"
  Setelah putaran ke-k, k elemen TERBESAR sudah berada di posisi akhirnya (kanan).

  [5, 1, 4, 2]
   ↕                5>1 tukar -> [1, 5, 4, 2]
      ↕             5>4 tukar -> [1, 4, 5, 2]
         ↕          5>2 tukar -> [1, 4, 2, 5]   <- 5 sudah di tempat
```

```
SELECTION SORT — "cari yang terkecil, taruh di depan"
  Setelah putaran ke-k, k elemen TERKECIL sudah berada di posisi akhirnya (kiri).

  [5, 1, 4, 2]      terkecil = 1 (indeks 1), tukar dengan indeks 0
  [1, 5, 4, 2]      terkecil sisanya = 2 (indeks 3), tukar dengan indeks 1
  [1, 2, 4, 5]      terkecil sisanya = 4, sudah di tempat
```

```
INSERTION SORT — "seperti menyusun kartu di tangan"
  Setelah langkah ke-k, k elemen PERTAMA sudah terurut di antara mereka sendiri
  (tetapi belum tentu di posisi akhirnya).

  [5 | 1, 4, 2]     ambil 1, geser 5 ke kanan, sisipkan
  [1, 5 | 4, 2]     ambil 4, geser 5, sisipkan
  [1, 4, 5 | 2]     ambil 2, geser 5 dan 4, sisipkan
  [1, 2, 4, 5]
```

> **Perbedaan halus tapi penting:** bubble dan selection menempatkan elemen di posisi
> **final**-nya. Insertion hanya menjaga bagian kiri **terurut relatif** — posisi
> finalnya bisa bergeser lagi. Inilah yang membuat insertion cocok untuk data yang
> datang bertahap (streaming).

### Stabilitas

Sebuah pengurutan disebut **stabil** kalau elemen dengan kunci yang sama
**mempertahankan urutan aslinya**.

```
Data: (Ani, 90), (Budi, 85), (Citra, 90)
Urutkan berdasarkan nilai, menurun:

STABIL     : (Ani, 90), (Citra, 90), (Budi, 85)     Ani tetap sebelum Citra ✓
TIDAK STABIL: (Citra, 90), (Ani, 90), (Budi, 85)    urutan asli hilang     ✗
```

```
Bubble    : STABIL      (hanya menukar yang BERDAMPINGAN dan hanya kalau > )
Insertion : STABIL      (berhenti menggeser saat bertemu yang sama)
Selection : TIDAK STABIL (menukar elemen berjauhan, bisa melompati kembaran)
```

Contoh selection sort merusak stabilitas:

```
[2a, 2b, 1]     (2a dan 2b bernilai sama, ditandai untuk membedakan)
terkecil = 1, tukar dengan posisi 0
[1, 2b, 2a]     <- 2b sekarang MENDAHULUI 2a. Urutan asli rusak.
```

Stabilitas penting saat kamu mengurutkan berdasarkan beberapa kriteria secara
bertahap (Day 47), atau saat identitas elemen bermakna.

---

## 🧮 2. Analisis Kompleksitas

| Algoritma | Terbaik | Rata-rata | Terburuk | Swap terburuk | Ruang | Stabil |
| --------- | ------- | --------- | -------- | ------------- | ----- | ------ |
| Bubble (dengan flag) | **O(n)** | O(n²) | O(n²) | O(n²) | O(1) | ✅ |
| Bubble (tanpa flag) | O(n²) | O(n²) | O(n²) | O(n²) | O(1) | ✅ |
| Selection | O(n²) | O(n²) | O(n²) | **O(n)** | O(1) | ❌ |
| Insertion | **O(n)** | O(n²) | O(n²) | O(n²) | O(1) | ✅ |
| `std::sort` | O(n log n) | O(n log n) | O(n log n) | — | O(log n) | ❌ |
| `std::stable_sort` | O(n log n) | O(n log n) | O(n log n) | — | O(n) | ✅ |

### Tiga catatan yang benar-benar berguna

**1. Selection sort punya jumlah swap paling sedikit: tepat `n−1`.**
Kalau operasi tukarnya sangat mahal (misalnya menukar objek besar, atau menulis ke
disk/flash yang punya batas siklus tulis), selection sort menang meski
perbandingannya banyak.

**2. Insertion sort adalah O(n + jumlah inversi).**
Untuk data yang **hampir terurut** — misalnya setiap elemen paling jauh `k` posisi dari
tempatnya — insertion sort berjalan dalam **O(nk)**, yang bisa jauh lebih cepat dari
`n log n` saat `k` kecil.

**3. Jumlah swap bubble sort = banyaknya inversi.**
Setiap swap pada elemen berdampingan menghilangkan **tepat satu** inversi, dan array
terurut punya nol inversi. Ini bukan kebetulan; ini identitas yang berguna, dan
menjadi jembatan ke Day 44.

### Batas praktis

```
n <= 1000     -> O(n^2) aman (10^6 operasi)
n <= 5000     -> O(n^2) masih aman (2.5 * 10^7)
n <= 10000    -> mulai berisiko (10^8), tergantung konstanta
n > 10000     -> WAJIB O(n log n)
```

---

## 💻 3. Implementasi C++

### 3.1 Bubble sort dengan optimasi flag

```cpp
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool adaTukar = false;
        for (int j = 0; j + 1 < n - i; j++)      // n-i: ekor sudah beres
            if (a[j] > a[j + 1]) {                // '>' bukan '>=' -> STABIL
                swap(a[j], a[j + 1]);
                adaTukar = true;
            }
        if (!adaTukar) break;                     // sudah terurut, berhenti
    }
}
```

Flag `adaTukar` membuat kasus terbaik menjadi **O(n)**: satu sapuan tanpa pertukaran
membuktikan array sudah terurut.

⚠️ `a[j] > a[j+1]`, **bukan** `>=`. Kalau memakai `>=`, elemen kembar akan ditukar
dan stabilitas hilang — sekaligus menambah swap yang sia-sia.

### 3.2 Menghitung swap bubble sort = inversi

```cpp
long long hitungSwapBubble(vector<int> a) {      // salinan, bukan referensi
    int n = a.size();
    long long swapCount = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j + 1 < n - i; j++)
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); swapCount++; }
    return swapCount;
}
```

Untuk `n > 5000` ini terlalu lambat — pakai merge sort (Day 44) atau BIT (Day 170)
untuk menghitung inversi dalam O(n log n). Tetapi hasilnya **identik**.

### 3.3 Selection sort

```cpp
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;     // '<' -> ambil yang PERTAMA
        if (minIdx != i) swap(a[i], a[minIdx]);   // hindari swap sia-sia
    }
}
```

Jumlah swap: paling banyak `n−1`. Jumlah perbandingan: selalu `n(n−1)/2`, tidak peduli
datanya — selection sort **tidak bisa** memanfaatkan data yang sudah hampir terurut.

### 3.4 Insertion sort

```cpp
void insertionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int kunci = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > kunci) {          // '>' -> berhenti saat sama, STABIL
            a[j + 1] = a[j];                       // GESER, bukan swap
            j--;
        }
        a[j + 1] = kunci;
    }
}
```

⚠️ Perhatikan bahwa ini **menggeser**, bukan menukar. Satu penulisan per langkah,
bukan tiga (swap butuh tiga penulisan). Itu sebabnya insertion sort punya konstanta
yang sangat kecil dan dipakai di dalam `std::sort`.

### 3.5 Insertion sort dengan binary search

```cpp
void binaryInsertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int kunci = a[i];
        // upper_bound -> menyisipkan SETELAH yang sama -> tetap stabil
        int pos = upper_bound(a.begin(), a.begin() + i, kunci) - a.begin();
        for (int j = i; j > pos; j--) a[j] = a[j - 1];
        a[pos] = kunci;
    }
}
```

Perbandingan turun menjadi O(n log n), tetapi **pergeserannya tetap O(n²)** —
karena memindahkan elemen di array tetap butuh menyalin. Berguna hanya kalau
operasi perbandingannya mahal (misalnya membandingkan string panjang).

---

## 🔄 4. Trace & Simulasi

### 4.1 Bubble sort pada `a = [5, 1, 4, 2]`

**Putaran 1** (batas `j+1 < 4`):

| j | bandingkan | tukar? | array setelahnya |
| - | ---------- | ------ | ---------------- |
| 0 | 5 vs 1 | ya | [1, 5, 4, 2] |
| 1 | 5 vs 4 | ya | [1, 4, 5, 2] |
| 2 | 5 vs 2 | ya | [1, 4, 2, 5] |

```
5 sudah di posisi final. adaTukar = true, lanjut.
```

**Putaran 2** (batas `j+1 < 3`):

| j | bandingkan | tukar? | array setelahnya |
| - | ---------- | ------ | ---------------- |
| 0 | 1 vs 4 | tidak | [1, 4, 2, 5] |
| 1 | 4 vs 2 | ya | [1, 2, 4, 5] |

**Putaran 3** (batas `j+1 < 2`):

| j | bandingkan | tukar? |
| - | ---------- | ------ |
| 0 | 1 vs 2 | tidak |

```
adaTukar = false -> BERHENTI (padahal loop luar masih menyisakan putaran)

Total swap = 4
Verifikasi inversi pada [5,1,4,2]: (5,1) (5,4) (5,2) (4,2) = 4  ✓
```

Kecocokan ini bukan kebetulan — inilah identitas swap-bubble = inversi.

### 4.2 Selection sort pada `a = [5, 1, 4, 2]`

| i | cari minimum di a[i..3] | minIdx | tukar | array |
| - | ----------------------- | ------ | ----- | ----- |
| 0 | min(5,1,4,2) = 1 | 1 | a[0]↔a[1] | [1, 5, 4, 2] |
| 1 | min(5,4,2) = 2 | 3 | a[1]↔a[3] | [1, 2, 4, 5] |
| 2 | min(4,5) = 4 | 2 | tidak perlu | [1, 2, 4, 5] |

```
Total swap = 2  (bandingkan: bubble butuh 4)
Total perbandingan = 3 + 2 + 1 = 6  (selalu, apa pun datanya)
```

### 4.3 Insertion sort pada `a = [5, 1, 4, 2]`

| i | kunci | pergeseran | array setelahnya |
| - | ----- | ---------- | ---------------- |
| 1 | 1 | 5 digeser ke kanan | [1, 5, 4, 2] |
| 2 | 4 | 5 digeser | [1, 4, 5, 2] |
| 3 | 2 | 5 dan 4 digeser | [1, 2, 4, 5] |

```
Total pergeseran = 1 + 1 + 2 = 4  (sama dengan jumlah inversi!)
```

### 4.4 Insertion sort pada data hampir terurut

```
a = [1, 2, 3, 5, 4]      hanya satu pasangan yang terbalik

i=1 kunci 2: tidak ada pergeseran
i=2 kunci 3: tidak ada pergeseran
i=3 kunci 5: tidak ada pergeseran
i=4 kunci 4: satu pergeseran

Total kerja: 4 perbandingan + 1 pergeseran  ->  praktis O(n)
```

Bandingkan dengan selection sort pada data yang sama: tetap 10 perbandingan.
Selection sort **buta** terhadap keteraturan data; insertion sort memanfaatkannya.

### 4.5 Stabilitas dirusak oleh selection sort

```
a = [(2,'a'), (2,'b'), (1,'c')]        urutkan berdasarkan angka

Selection sort:
   i=0: minimum = 1 di indeks 2, tukar a[0] dengan a[2]
        [(1,'c'), (2,'b'), (2,'a')]
        -> 'b' sekarang MENDAHULUI 'a'. Urutan asli rusak.  ✗

Insertion sort:
   i=1: kunci (2,'b'), a[0] = (2,'a'), 2 > 2 salah -> berhenti, tidak digeser
        [(2,'a'), (2,'b'), (1,'c')]
   i=2: kunci (1,'c'), geser keduanya
        [(1,'c'), (2,'a'), (2,'b')]
        -> 'a' tetap sebelum 'b'.  ✓
```

Perhatikan bahwa yang menjaga stabilitas insertion sort adalah `a[j] > kunci`
(bukan `>=`) — kondisi berhenti saat bertemu nilai yang sama.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "berapa pertukaran bubble sort" | hitung inversi |
| "berapa langkah sampai terurut" | simulasi, atau inversi |
| "data hampir terurut, setiap elemen ≤ k dari tempatnya" | insertion sort O(nk), atau heap ukuran k |
| "operasi tukar sangat mahal" | selection sort (`n−1` swap) |
| "harus stabil" | insertion / bubble / `stable_sort` |
| "urutkan bertahap beberapa kriteria" | butuh stabil (Day 47) |
| `n ≤ 1000` dan logikanya rumit | O(n²) tidak apa-apa, prioritaskan kebenaran |
| `n > 10^4` | wajib O(n log n) |

### Pattern: cocktail shaker sort (bubble dua arah)

```cpp
// Menyapu bolak-balik. Membantu pada kasus "kura-kura":
// elemen kecil di ujung kanan bergerak sangat lambat pada bubble biasa.
void cocktailSort(vector<int>& a) {
    int kiri = 0, kanan = a.size() - 1;
    while (kiri < kanan) {
        for (int j = kiri; j < kanan; j++) if (a[j] > a[j+1]) swap(a[j], a[j+1]);
        kanan--;
        for (int j = kanan; j > kiri; j--) if (a[j-1] > a[j]) swap(a[j-1], a[j]);
        kiri++;
    }
}
```

Tetap O(n²), tetapi konstanta lebih baik pada data tertentu. Layak diketahui,
jarang dibutuhkan.

### Pattern: pengurutan sebagian dengan selection

Kalau kamu hanya butuh `k` elemen terkecil dan `k` sangat kecil:

```cpp
for (int i = 0; i < k; i++) { /* satu putaran selection sort */ }
```

O(nk), mengalahkan sorting penuh saat `k` kecil. (`nth_element` di Day 45 memberi
O(n) untuk masalah serupa.)

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Batas loop bubble salah.** `j + 1 < n - i` — memakai `j < n - i` menyebabkan
   akses `a[n]` di luar array.

2. **Memakai `>=` alih-alih `>`.** Merusak stabilitas dan menambah swap sia-sia.

3. **Insertion sort memakai `swap` alih-alih menggeser.** Tetap benar, tetapi tiga kali
   lebih banyak penulisan memori.

4. **Mengira selection sort stabil.** Tidak. Kalau soal butuh stabil, jangan pakai.

5. **`int` untuk jumlah swap.** Untuk `n = 10^5`, inversi bisa mencapai `5·10^9`.

6. **Mengubah array asli saat hanya ingin menghitung swap.** Terima parameter
   **by value**, bukan by reference.

7. **Memakai O(n²) saat `n = 10^5`.** 10^10 operasi. Selalu periksa batas dulu.

8. **Lupa `a[j] = a[j-1]` arahnya.** Pada insertion sort, pergeseran ke **kanan**;
   menuliskannya terbalik akan menimpa data.

### Edge cases wajib diuji

```
n = 0 atau n = 1        -> loop tidak boleh berjalan; jangan crash
array sudah terurut     -> bubble dengan flag harus O(n)
array terurut terbalik  -> kasus terburuk, inversi = n(n-1)/2
semua elemen sama       -> tidak boleh ada swap sama sekali
dua elemen              -> kasus terkecil yang bermakna
```

---

## 🏆 7. Tips Contest

**Kapan menulis sorting sendiri?** Hampir tidak pernah — pakai `std::sort`.
Pengecualiannya:

- Soal secara eksplisit meminta **jumlah operasi** dari algoritma tertentu.
- Soal meminta **keadaan array setelah k langkah** (simulasi).
- Kamu butuh **stabil** dan tidak ingin memakai `stable_sort` (jarang; pakai saja).

**Yang benar-benar berguna dari hari ini** bukan ketiga algoritmanya, melainkan:

1. **Jumlah swap bubble = inversi.** Ini muncul di banyak soal, dan Day 44 akan
   memberimu cara menghitungnya dalam O(n log n).
2. **Kesadaran akan stabilitas.** Ini akan menentukan AC/WA di Day 47.
3. **Insertion sort cepat pada data hampir terurut.** Kadang jadi jawaban tak terduga.

**Angka yang harus diingat:** `n ≤ 5000` masih aman untuk O(n²). Kalau soal memberi
`n ≤ 1000` dan solusi O(n²)-mu jelas benar, **jangan** buang waktu mengoptimalkan —
batas itu adalah izin dari penyusun soal.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  TIGA SORTING O(n^2)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
             invariant                    stabil  swap    terbaik
  BUBBLE     k terbesar sudah di kanan     YA     O(n^2)  O(n) dgn flag
  SELECTION  k terkecil sudah di kiri      TIDAK  n-1     O(n^2)
  INSERTION  k pertama terurut relatif     YA     O(n^2)  O(n)

  IDENTITAS PENTING
    swap bubble = banyaknya INVERSI
    kerja insertion = O(n + inversi)

  STABILITAS
    dijaga oleh '>' (bukan '>='), yaitu berhenti saat bertemu yang sama
    selection merusaknya karena menukar elemen BERJAUHAN

  KAPAN DIPAKAI
    swap mahal          -> selection (n-1 swap)
    hampir terurut      -> insertion (O(nk))
    butuh stabil        -> insertion / bubble / stable_sort
    n <= 5000           -> O(n^2) aman
    n > 10^4            -> WAJIB O(n log n)

  std::sort memakai insertion sort untuk potongan kecil (< 16 elemen)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [HackerRank — Sorting: Bubble Sort](https://www.hackerrank.com/challenges/ctci-bubble-sort/) | HackerRank | hitung swap |
| [HackerRank — Insertion Sort Advanced](https://www.hackerrank.com/challenges/insertion-sort/) | HackerRank | inversi |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | sort + two pointers |
| [CF 339B / 266B — Div3 sorting](https://codeforces.com/problemset) | Codeforces | simulasi |
| [UVa 10327 — Flip Sort](https://onlinejudge.org/) | UVa | jumlah swap berdampingan |
| [SPOJ CODESPTB — Insertion Sort](https://www.spoj.com/problems/CODESPTB/) | SPOJ | inversi |
| [LeetCode 912 — Sort an Array](https://leetcode.com/problems/sort-an-array/) | LeetCode | latihan implementasi |

---

**Selanjutnya:** Day 44 — Merge Sort & Inversion Count. Identitas "swap bubble = inversi"
yang kamu temukan hari ini akan menjadi **soalnya sendiri**, dan kamu akan belajar
menghitungnya dalam O(n log n) alih-alih O(n²) — dengan cara yang nyaris gratis di dalam
merge sort.
