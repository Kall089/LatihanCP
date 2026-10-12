# 📊 Day 71: Prinsip Greedy & Exchange Argument

> **Prasyarat:** Sorting (Day 20, 47), Complete Search (Day 59), 0/1 Knapsack (Day 145 — sebagai pembanding)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"minimum/maksimum"*, *"pilih urutan terbaik"*, *"n besar tapi terasa sederhana"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 71, kamu akan mampu:

- [ ] Menyatakan apa itu **greedy** dan kapan ia berhak dipakai
- [ ] Menulis **exchange argument** sebagai bukti, bukan sekadar firasat
- [ ] Membedakan **greedy choice property** dan **optimal substructure**
- [ ] Membantah greedy dengan **contoh tandingan** secepat mungkin
- [ ] Menemukan **kriteria pengurutan** yang benar lewat perbandingan dua elemen
- [ ] Mengenali kapan greedy **gagal** dan DP diperlukan
- [ ] Memakai **stress test** untuk menguji dugaan greedy dalam hitungan menit

---

## 🔍 1. Konsep & Intuisi

### Apa itu greedy

```
Greedy = di setiap langkah, ambil pilihan yang TERLIHAT terbaik saat itu,
         tanpa pernah meninjau ulang keputusan sebelumnya.
```

Itu terdengar naif — dan memang sering salah. Yang membuat greedy menarik
adalah: ketika ia benar, ia biasanya **jauh** lebih sederhana dan cepat
daripada alternatifnya.

```
DP knapsack     : O(n·W), tabel besar, rekonstruksi rumit
Greedy fractional: sort + satu sapuan, 5 baris
```

### Dua syarat yang harus dipenuhi

Greedy sah kalau **keduanya** berlaku:

```
1. GREEDY CHOICE PROPERTY
   Ada pilihan pertama yang "terlihat terbaik" yang PASTI menjadi bagian
   dari suatu solusi optimal.

2. OPTIMAL SUBSTRUCTURE
   Setelah pilihan itu diambil, sisa masalahnya adalah masalah sejenis
   yang lebih kecil, dan solusi optimalnya bisa digabungkan.
```

Syarat kedua dimiliki juga oleh DP. Yang membedakan greedy adalah syarat
pertama: **kita tidak perlu mencoba semua pilihan pertama**, karena satu di
antaranya sudah dijamin aman.

> **Intinya:** DP bertanya *"pilihan mana yang terbaik?"* dan mencoba semuanya.
> Greedy mengklaim *"pilihan ini pasti aman"* dan tidak mencoba yang lain.
> Klaim itulah yang harus dibuktikan.

### Analogi: menyusun antrean kasir

Ada beberapa pelanggan dengan waktu layanan berbeda. Kamu ingin
**meminimumkan total waktu tunggu semua orang**.

Firasat: layani yang **paling cepat** dulu. Kenapa?

```
Dua pelanggan berdampingan dengan waktu a dan b.
  urutan (a, b): a menunggu 0, b menunggu a  -> total tunggu = a
  urutan (b, a): b menunggu 0, a menunggu b  -> total tunggu = b

Kalau a < b, urutan (a, b) lebih baik.
```

Perhatikan bahwa kita membandingkan **dua elemen berdampingan** dan
menunjukkan bahwa menukarnya tidak pernah memperbaiki keadaan. Itulah
**exchange argument**, dan itulah cara baku membuktikan greedy.

### Exchange argument — kerangka bakunya

```
1. Ambil solusi OPTIMAL apa pun, sebut O.
2. Andaikan O BERBEDA dari solusi greedy G pada suatu titik.
   Ambil titik perbedaan PALING AWAL.
3. Tunjukkan bahwa kamu bisa MENUKAR sesuatu di O agar ia menjadi lebih
   mirip G, TANPA membuatnya lebih buruk.
4. Ulangi sampai O berubah menjadi G.
   Kesimpulan: G juga optimal.
```

Langkah 3 adalah inti. Kalau kamu bisa menunjukkan pertukaran itu selalu
mungkin dan tidak pernah merugikan, buktimu selesai.

⚠️ Perhatikan bahwa kita **tidak** membuktikan "greedy adalah satu-satunya
solusi optimal" — hanya bahwa ia **salah satu**. Itu sudah cukup.

### Membantah greedy: contoh tandingan

Membuktikan greedy butuh kerja; **membantahnya** sering hanya butuh satu
contoh kecil. Karena itu, urutan kerja yang efisien adalah:

```
1. Tebak kriteria greedy.
2. Cari contoh tandingan selama 2-3 menit (mulai dari n = 2 dan 3).
3. Kalau tidak ketemu, jalankan stress test terhadap brute force.
4. Baru kalau lolos, coba buktikan dengan exchange argument.
```

Contoh klasik: greedy rasio pada 0/1 knapsack.

```
W = 10
A: berat 6, nilai 7   rasio 1.167   <- rasio tertinggi
B: berat 5, nilai 5   rasio 1.000
C: berat 5, nilai 5   rasio 1.000

Greedy rasio: ambil A (7), sisa 4, tidak ada yang muat  -> 7
Optimal     : B + C                                     -> 10
```

Tiga baris, dan seluruh dugaan runtuh. Ini jauh lebih murah daripada
mencoba membuktikan sesuatu yang salah selama satu jam.

---

## 🧮 2. Analisis Kompleksitas

Greedy biasanya `O(n log n)` (didominasi pengurutan) atau `O(n)`.
Yang lebih penting adalah **perbandingan dengan alternatifnya**:

| Masalah | Greedy | DP / Complete search |
| ------- | ------ | -------------------- |
| Fractional knapsack | O(n log n) ✅ | tidak perlu |
| 0/1 knapsack | ❌ salah | O(n·W) |
| Activity selection | O(n log n) ✅ | O(n²) DP juga bisa |
| Coin change (koin kanonis) | O(n) ✅ | O(n·V) |
| Coin change (koin sembarang) | ❌ salah | O(n·V) |
| Minimum spanning tree | O(m log m) ✅ | — |
| Traveling salesman | ❌ salah | O(2ⁿ·n) |

⚠️ **Perhatikan dua baris "koin"**: masalah yang sama, jawaban berbeda,
tergantung himpunan koinnya. Greedy tidak punya sifat "aman secara umum" —
kebenarannya bergantung pada **struktur soal**, dan itulah kenapa pembuktian
tidak bisa dilewati.

```
koin {1, 5, 10, 25}  -> greedy BENAR (sistem kanonis)
koin {1, 3, 4}       -> greedy SALAH
    bayar 6: greedy 4+1+1 = 3 koin ; optimal 3+3 = 2 koin
```

---

## 💻 3. Implementasi C++

### 3.1 Kerangka umum greedy

```cpp
sort(a.begin(), a.end(), kriteria);      // urutkan berdasarkan kriteria greedy
Hasil h = kosong;
for (auto& x : a)
    if (bolehDiambil(x, h)) ambil(x, h); // ambil kalau sah, tanpa meninjau ulang
```

Hampir seluruh soal greedy berbentuk ini. Pekerjaan sesungguhnya bukan
menulis kodenya, melainkan menemukan **`kriteria`** yang benar.

### 3.2 Menemukan kriteria lewat perbandingan dua elemen

Ini teknik yang paling berguna dari seluruh hari ini.

*Susun `n` bilangan menjadi satu string sehingga hasilnya sebesar mungkin.*

```
[3, 30, 34, 5, 9]  ->  "9534330"
```

Kriteria apa? Bukan "besar dulu" (30 vs 3: mana dulu?). Jawabannya muncul
dari membandingkan **dua elemen berdampingan**:

```cpp
sort(a.begin(), a.end(), [](const string& x, const string& y) {
    return x + y > y + x;               // mana yang menghasilkan gabungan lebih besar
});
```

> **Pola umum:** kalau kamu tidak tahu kriteria pengurutannya, tanyakan
> *"kalau hanya ada DUA elemen, mana yang harus lebih dulu?"* Jawabannya
> langsung menjadi komparator.

⚠️ Komparator seperti ini harus memenuhi **strict weak ordering** — kalau
tidak, `std::sort` bisa crash. Untuk `x+y > y+x` sifat itu terpenuhi
(bisa dibuktikan), tetapi tidak semua komparator "intuitif" aman.

### 3.3 Exchange argument dalam kode: penjadwalan

*n pekerjaan, pekerjaan `i` butuh waktu `t[i]`. Minimumkan total waktu
selesai semua pekerjaan.*

```cpp
sort(t.begin(), t.end());               // terpendek dulu (SPT: shortest processing time)
long long sekarang = 0, total = 0;
for (long long x : t) {
    sekarang += x;
    total += sekarang;                  // waktu selesai pekerjaan ini
}
```

**Buktinya** (exchange argument): ambil solusi optimal. Kalau ada dua
pekerjaan berdampingan dengan `t[i] > t[j]` (yang lebih lama duluan),
tukar keduanya:

```
sebelum: ... i j ...   kontribusi = (S + t[i]) + (S + t[i] + t[j])
sesudah: ... j i ...   kontribusi = (S + t[j]) + (S + t[j] + t[i])

selisih = t[i] - t[j] > 0  ->  menukar MENGURANGI total
```

Pekerjaan lain sama sekali tidak terpengaruh, karena total waktu kedua
pekerjaan itu tidak berubah. Jadi setiap pasangan yang "terbalik" bisa
ditukar tanpa merugikan → urutan menaik optimal.

### 3.4 Stress test — cara tercepat menguji dugaan

```cpp
// brute force: coba SELURUH permutasi (n kecil)
long long brute(vector<int> a) {
    sort(a.begin(), a.end());
    long long best = LLONG_MAX;
    do {
        best = min(best, hitung(a));
    } while (next_permutation(a.begin(), a.end()));
    return best;
}

int main() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 10000; iter++) {
        int n = 1 + rng() % 7;
        vector<int> a(n);
        for (int& x : a) x = 1 + rng() % 20;
        if (greedy(a) != brute(a)) {
            // cetak contoh tandingan dan berhenti
            return 1;
        }
    }
}
```

⚠️ **Ini bukan bukti**, tetapi ia menemukan contoh tandingan jauh lebih
cepat daripada memikirkannya. Kalau greedy-mu salah untuk `n ≤ 7`,
stress test akan menemukannya dalam hitungan detik.

Kalau lolos 10.000 kasus, dugaanmu **mungkin** benar — dan saat itulah
layak menghabiskan waktu untuk membuktikannya.

### 3.5 Ketika greedy gagal: sinyal peringatan

```cpp
// Sinyal bahwa greedy kemungkinan SALAH:
// 1. Ada BATASAN kapasitas dan barang tidak bisa dipotong  -> DP
// 2. Pilihan sekarang mengubah HIMPUNAN pilihan berikutnya secara rumit
// 3. Soal minta "berapa CARA", bukan "berapa MAKSIMUM"     -> DP/kombinatorik
// 4. n kecil (<= 20) padahal soalnya terlihat mudah        -> penyusun soal
//    sengaja memberi ruang untuk brute force/DP eksponensial
```

Poin 4 sangat berguna: **batas soal adalah petunjuk**. Kalau `n ≤ 20`
padahal greedy `O(n log n)` sanggup menangani `10^6`, penyusun soal
kemungkinan besar tahu greedy tidak berlaku.

---

## 🔄 4. Trace & Simulasi

### 4.1 Exchange argument pada penjadwalan `t = [3, 1, 2]`

**Seluruh urutan dan total waktu selesai:**

| Urutan | waktu selesai | total |
| ------ | ------------- | ----- |
| (1,2,3) | 1, 3, 6 | **10** ← greedy |
| (1,3,2) | 1, 4, 6 | 11 |
| (2,1,3) | 2, 3, 6 | 11 |
| (2,3,1) | 2, 5, 6 | 13 |
| (3,1,2) | 3, 4, 6 | 13 |
| (3,2,1) | 3, 5, 6 | 14 |

Greedy (urut menaik) memberi 10, dan itu memang minimum.

**Kenapa menukar pasangan terbalik selalu membantu** — ambil `(2, 1, 3)`:

```
Pasangan berdampingan (2, 1) terbalik. Tukar menjadi (1, 2, 3).
   sebelum: 2 + 3 = 5   (kontribusi dua pekerjaan pertama)
   sesudah: 1 + 3 = 4
   Pekerjaan ketiga tidak terpengaruh: keduanya selesai di waktu 6.
   Total turun dari 11 menjadi 10.   ✓
```

Setiap urutan yang bukan menaik punya setidaknya satu pasangan berdampingan
yang terbalik, dan menukarnya selalu memperbaiki. Jadi urutan menaik pasti
optimal.

### 4.2 Menemukan komparator lewat dua elemen

*Susun `[3, 30]` menjadi bilangan terbesar.*

```
"3" + "30" = "330"
"30" + "3" = "303"
330 > 303  ->  "3" harus lebih dulu
```

Perhatikan bahwa "urut menurun sebagai bilangan" akan memberi `30` dulu
(karena 30 > 3) — dan itu **salah**. Perbandingan gabungan memberi jawaban
yang benar.

*Uji pada `[3, 30, 34, 5, 9]`:*

```
komparator x+y > y+x menghasilkan urutan: 9, 5, 34, 3, 30
gabungan: "9534330"

Verifikasi terhadap kandidat lain:
   "9534303" (menukar 3 dan 30)  ->  lebih kecil   ✓
```

### 4.3 Contoh tandingan untuk greedy koin

```
koin {1, 3, 4}, bayar 6

Greedy (ambil terbesar dulu):
   ambil 4  -> sisa 2
   ambil 1  -> sisa 1
   ambil 1  -> sisa 0
   total 3 koin

Optimal: 3 + 3 = 2 koin
```

Perhatikan betapa kecilnya contoh ini: tiga koin, satu target. Kalau kamu
menguji dugaanmu dengan `n ≤ 4` selama dua menit, kamu akan menemukannya.

### 4.4 Greedy yang tampak benar tetapi salah

*Pilih sebanyak mungkin interval yang tidak tumpang tindih.*

Dugaan pertama: **ambil yang terpendek dulu.**

```
Interval: [1, 10], [9, 12], [11, 20]

Greedy terpendek: [9,12] (panjang 3) dulu  ->  keduanya bentrok  -> 1 interval
Optimal         : [1,10] dan [11,20]        ->  2 interval
```

Dugaan kedua: **ambil yang mulai paling awal.**

```
Interval: [1, 100], [2, 3], [4, 5]

Greedy mulai awal: [1,100]  ->  1 interval
Optimal          : [2,3] dan [4,5]  ->  2 interval
```

Dugaan ketiga: **ambil yang BERAKHIR paling awal.** Ini yang benar —
dan buktinya adalah exchange argument (Day 72).

Perhatikan bahwa dua dugaan pertama terasa sama masuk akalnya. Firasat
tidak cukup; contoh tandingan dan bukti yang menentukan.

---

## 📝 5. Variasi & Pattern

| Sinyal di soal | Kemungkinan |
| -------------- | ----------- |
| "minimalkan total waktu tunggu" | urut menaik (SPT) |
| "sebanyak mungkin yang tidak bentrok" | urut berdasarkan **akhir** (Day 72) |
| "barang boleh dipotong" | greedy rasio (Day 74) |
| "barang tidak boleh dipotong" | ❌ greedy; DP knapsack (Day 145) |
| "susun jadi string terbesar/terkecil" | komparator gabungan |
| "gabungkan dua tumpukan berulang" | heap, ambil dua terkecil (Day 75) |
| "berapa cara" | ❌ greedy; DP/kombinatorik |
| `n ≤ 20` padahal terlihat mudah | ❌ greedy; brute force/DP bitmask |

### Pattern: greedy + struktur data

Banyak greedy butuh "ambil yang terbaik saat ini" secara **berulang** dari
himpunan yang berubah. Di situlah heap masuk:

```cpp
priority_queue<...> pq(a.begin(), a.end());
while (pq.size() > 1) {
    auto x = pq.top(); pq.pop();
    auto y = pq.top(); pq.pop();
    pq.push(gabung(x, y));
}
```

Ini kerangka Huffman coding (Day 75) dan banyak soal "gabungkan dua tumpukan".

### Pattern: greedy dengan penyesalan (regret)

Kadang greedy perlu **membatalkan** keputusan sebelumnya kalau ada yang
lebih baik. Polanya: simpan yang sudah diambil di heap, dan tukar kalau
kandidat baru lebih menguntungkan (Day 77).

### Pattern: exchange argument untuk menemukan komparator

Kalau soal minta mengurutkan `n` benda dan kamu tidak tahu kriterianya:

```
1. Ambil DUA benda i dan j.
2. Hitung biaya kalau i dulu, dan biaya kalau j dulu.
3. Susun pertidaksamaannya, sederhanakan.
4. Hasilnya adalah komparatormu.
```

Contoh: dua benda dengan `(a[i], b[i])`, biaya urutan `i` lalu `j`
adalah `a[i] + max(0, b[i] - ...)` dan seterusnya — sederhanakan sampai
menjadi perbandingan dua besaran.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Memakai greedy tanpa menguji.** Ini kesalahan terbesar. Dua menit
   mencari contoh tandingan menghemat satu jam.

2. **Mengira "terbesar dulu" selalu benar.** Untuk susunan string, untuk
   knapsack, untuk koin — semuanya punya contoh tandingan.

3. **Komparator melanggar strict weak ordering.** `std::sort` bisa crash
   (bukan sekadar salah). Pastikan komparatormu **transitif** dan
   `cmp(x, x)` selalu `false`.

4. **Membuktikan dengan "terasa benar".** Exchange argument atau stress test;
   firasat bukan bukti.

5. **Melewatkan sinyal batas soal.** `n ≤ 20` hampir selalu berarti bukan greedy.

6. **Greedy benar tetapi implementasinya salah** — misalnya lupa bahwa
   setelah mengambil sesuatu, himpunan kandidat berubah.

7. **Tidak menangani seri.** Kalau dua elemen sama menurut kriteria, urutan
   di antara mereka kadang penting kadang tidak. Periksa.

### Edge cases wajib diuji

```
n = 1                     -> jawabannya trivial, jangan crash
seluruh elemen sama       -> komparator harus tetap valid
n = 2                     -> kasus terkecil yang membedakan dua kriteria
nilai nol atau negatif    -> banyak greedy mengasumsikan positif
himpunan kosong           -> periksa apakah soal mengizinkannya
```

---

## 🏆 7. Tips Contest

**Urutan kerja yang efisien:**

```
1. Tebak kriteria greedy (30 detik)
2. Cari contoh tandingan dengan n = 2, 3 (2 menit)
3. Kalau bersih, tulis brute force + stress test (5 menit)
4. Kalau lolos, tulis greedy dan submit
5. Buktikan dengan exchange argument HANYA kalau kamu ragu
```

Perhatikan bahwa membuktikan ada di urutan **terakhir**. Di kontes,
stress test memberi keyakinan yang cukup dengan biaya jauh lebih murah.

**Sinyal kuat bahwa greedy benar:**

- `n` besar (`10^5` ke atas) dan soalnya terasa sederhana
- Ada kata "minimum"/"maksimum" tanpa batasan yang rumit
- Soalnya terasa seperti "urutkan lalu sapu"

**Sinyal kuat bahwa greedy salah:**

- `n ≤ 20` atau `n ≤ 40` (brute force / MITM / DP bitmask)
- Ada kapasitas dan benda tidak bisa dipotong
- Soal minta "berapa cara"

**Kalau kamu buntu menemukan kriteria,** tanyakan: *"kalau hanya ada dua
benda, mana yang harus lebih dulu?"* Jawabannya langsung menjadi komparator.
Teknik ini menyelesaikan sangat banyak soal greedy tingkat menengah.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  PRINSIP GREEDY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  DUA SYARAT
    1. GREEDY CHOICE  : ada pilihan pertama yang PASTI aman
    2. OPTIMAL SUBSTRUCTURE : sisanya masalah sejenis yang lebih kecil
    Syarat 2 dimiliki DP juga. Syarat 1 yang membedakan.

  EXCHANGE ARGUMENT (cara baku membuktikan)
    1. ambil solusi optimal O
    2. cari perbedaan PALING AWAL dengan greedy G
    3. TUKAR sesuatu di O agar lebih mirip G, tanpa memperburuk
    4. ulangi sampai O = G  ->  G optimal

  MENEMUKAN KOMPARATOR
    "kalau hanya ada DUA elemen, mana dulu?"
    -> jawabannya langsung menjadi komparator
    contoh: susun string terbesar -> sort(x + y > y + x)

  URUTAN KERJA DI KONTES
    tebak (30 dtk) -> cari contoh tandingan n=2,3 (2 mnt)
    -> stress test vs brute force (5 mnt) -> tulis -> submit
    Membuktikan ada di urutan TERAKHIR.

  SINYAL GREEDY SALAH
    n <= 20/40           -> brute force, MITM, DP bitmask
    kapasitas + tak bisa dipotong -> DP knapsack (Day 145)
    "berapa CARA"        -> DP / kombinatorik
    pilihan mengubah himpunan berikutnya secara rumit

  CONTOH TANDINGAN KLASIK
    knapsack rasio : W=10, (6,7) (5,5) (5,5) -> greedy 7, optimal 10
    koin {1,3,4}   : bayar 6 -> greedy 3 koin, optimal 2
    interval terpendek dulu : [1,10] [9,12] [11,20] -> greedy 1, optimal 2

  KOMPARATOR harus STRICT WEAK ORDERING, kalau tidak sort() bisa CRASH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1084 — Apartments](https://cses.fi/problemset/task/1084) | CSES | greedy + two pointers |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | greedy dua ujung |
| [CSES 1073 — Towers](https://cses.fi/problemset/task/1073) | CSES | greedy + multiset |
| [LeetCode 179 — Largest Number](https://leetcode.com/problems/largest-number/) | LeetCode | komparator gabungan |
| [LeetCode 455 — Assign Cookies](https://leetcode.com/problems/assign-cookies/) | LeetCode | greedy dasar |
| [CF 1526C1 — Potions](https://codeforces.com/problemset/problem/1526/C1) | Codeforces | greedy + regret |
| [CF 379C — New Year Ratings](https://codeforces.com/problemset/problem/379/C) | Codeforces | greedy + sort |
| [AtCoder ABC 121 D / ABC 091 B](https://atcoder.jp/) | AtCoder | observasi greedy |
| [UVa 10037 — Bridge](https://onlinejudge.org/) | UVa | exchange argument nontrivial |

---

**Selanjutnya:** Day 72 — Activity Selection & Interval Scheduling, tempat
exchange argument dipakai untuk membuktikan bahwa "urut berdasarkan waktu
**akhir**" adalah kriteria yang benar — dan kenapa dua dugaan lain yang
sama masuk akalnya justru salah.
