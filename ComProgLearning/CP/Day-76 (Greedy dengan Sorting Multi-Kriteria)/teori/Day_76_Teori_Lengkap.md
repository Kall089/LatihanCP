# 📘 Day 76 — Greedy dengan Sorting Multi-Kriteria

> **Prasyarat:** Day 71 (exchange argument), Day 47 (stabilitas), Day 43–46
> (komparator), Day 72–73 (interval), Day 74 (perbandingan rasio).

---

## Daftar Isi

1. [Bug yang Tidak Pernah Tertangkap Generator Buruk](#1)
2. [Strict Weak Ordering](#2)
3. [Tiga Cara Menulis Tie-Break](#3)
4. [Stabilitas: Kapan Penting](#4)
5. [Pola A — Dominasi & Pareto Front](#5)
6. [Pola B — Sapuan Event dengan Tie-Break](#6)
7. [Pola C — Penjadwalan Dua Tahap](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Bug yang Tidak Pernah Tertangkap Generator Buruk

Hari ini seluruhnya tentang satu pertanyaan:

> **Ketika kriteria pertama seri, apa yang menentukan urutan?**

Kesalahan tie-break punya sifat yang berbahaya: kodenya **benar pada hampir
semua masukan acak**. Kalau generatormu memakai `rand() % 1000000000`, dua nilai
yang sama hampir tidak pernah muncul, dan bugnya tidak akan pernah terlihat.

Lalu di kontes, juri memakai data dengan banyak nilai berulang — dan kamu WA
tanpa tahu kenapa.

> **Aturan generator:** untuk menguji tie-break, pakai rentang nilai **kecil**
> (misalnya `0..3`). Semakin sering seri terjadi, semakin cepat bugnya muncul.

Template hari ini menjalankan 20.000 kasus dengan nilai dibatasi `0..3` justru
karena alasan ini. Dengan rentang `0..10^9`, semua kasus itu akan lolos meski
komparatornya salah.

Ini pelajaran metodologis yang berlaku jauh di luar hari ini:

| Yang diuji | Rentang generator |
|---|---|
| Tie-break | **kecil** (`0..3`) |
| Interval tumpang tindih | **kecil** (`0..15`) |
| Overflow | **maksimum** (`10^18`) |
| Presisi pecahan | dua nilai yang **hampir sama** |

Generator yang bagus adalah generator yang **dirancang untuk memecahkan kodemu**,
bukan yang "acak saja".

---

<a name="2"></a>
## 2. Strict Weak Ordering

`std::sort` mensyaratkan komparator memenuhi **strict weak ordering**. Kalau
tidak, akibatnya bukan sekadar urutan yang salah — `std::sort` bisa **membaca di
luar batas array** dan program crash atau berperilaku tak terduga.

Tiga syaratnya:

| Syarat | Artinya |
|---|---|
| Irrefleksif | `cmp(x, x) == false` |
| Asimetris | `cmp(x,y)` dan `cmp(y,x)` tidak boleh keduanya `true` |
| Transitif | `cmp(x,y)` dan `cmp(y,z)` ⇒ `cmp(x,z)` |

### Kesalahan nomor satu: memakai `<=`

```cpp
return x.a <= y.a;      // ❌ cmp(x, x) == true → melanggar irrefleksif
return x.a <  y.a;      // ✅
```

Kenapa orang menulis `<=`? Karena naluri "kalau sama, biarkan urutannya apa
adanya". Tetapi komparator bukan tempat menyatakan itu — nilai `false` sudah
berarti "tidak ada preferensi".

### Kesalahan nomor dua: tie-break yang tidak lengkap

```cpp
// ❌ SALAH
bool cmp(Item x, Item y) {
    if (x.a < y.a) return true;
    if (x.b < y.b) return true;    // dijalankan meski x.a > y.a !
    return false;
}
```

Komparator ini bisa mengatakan `cmp(x,y)` dan `cmp(y,x)` keduanya `true`. Bentuk
yang benar selalu memeriksa **kesamaan** dulu:

```cpp
// ✅ BENAR
bool cmp(Item x, Item y) {
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}
```

### Pemeriksa cepat

Jalankan komparatormu pada dua elemen **identik**. Kalau mengembalikan `true`,
komparatornya salah. Template hari ini menyediakan `komparatorSah()` yang
memeriksa ketiga syarat secara menyeluruh pada data kecil.

---

<a name="3"></a>
## 3. Tiga Cara Menulis Tie-Break

### (a) Lambda eksplisit — paling jelas, paling aman

```cpp
sort(v.begin(), v.end(), [](const Item& x, const Item& y) {
    if (x.a != y.a) return x.a < y.a;      // utama: a menaik
    return x.b > y.b;                      // tie-break: b menurun
});
```

Gunakan ini secara default. Kejelasan lebih berharga daripada keringkasan.

### (b) `tuple` — ringkas, tetapi hanya untuk semua-menaik

```cpp
return make_tuple(x.a, -x.b) < make_tuple(y.a, -y.b);
```

`tuple` membandingkan leksikografis, semuanya menaik. Untuk membalik satu kolom,
negasikan nilainya.

⚠️ **Bahaya negasi:** `-LLONG_MIN` meluap. Kalau nilaimu bisa mencapai batas tipe
data, jangan pakai trik ini.

⚠️ **Bahaya kedua:** negasi tidak bekerja untuk `string`. Untuk membalik urutan
string, kamu harus memakai lambda.

### (c) `pair` di dalam vector — tercepat saat kontes

```cpp
vector<pair<ll, ll>> v;
for (...) v.push_back({a, -b});
sort(v.begin(), v.end());
```

Tidak perlu menulis komparator sama sekali. Cocok untuk soal sederhana, dengan
peringatan negasi yang sama.

---

<a name="4"></a>
## 4. Stabilitas: Kapan Penting

| | Stabil? | Kompleksitas |
|---|---|---|
| `std::sort` | **tidak** | `O(n log n)` |
| `std::stable_sort` | ya | `O(n log n)` dengan memori tambahan, `O(n log²n)` tanpa |

**Sorting stabil** mempertahankan urutan relatif elemen yang seri.

Kapan itu penting? Ketika soal berkata "kalau seri, keluarkan sesuai urutan
masukan", atau ketika kamu mengurutkan berkali-kali menurut kriteria berbeda
(radix-style).

### Cara yang lebih baik daripada `stable_sort`

Tambahkan **indeks asli** sebagai tie-break terakhir:

```cpp
sort(v.begin(), v.end(), [](const Item& x, const Item& y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b > y.b;
    return x.idx < y.idx;              // tie-break terakhir: urutan asli
});
```

Keuntungannya:

- **Eksplisit** — pembaca kodemu tahu persis apa yang terjadi
- **Deterministik** — tidak bergantung pada implementasi pustaka
- **Menjamin strict weak ordering** — karena indeks selalu unik, tidak ada dua
  elemen yang "sama" menurut komparator

Poin terakhir itu berharga: dengan indeks sebagai tie-break, komparatormu menjadi
**total order**, dan seluruh kelas bug seri lenyap.

---

<a name="5"></a>
## 5. Pola A — Dominasi & Pareto Front

> Titik `i` **didominasi** oleh `j` bila `a_j ≥ a_i` dan `b_j ≥ b_i` dengan
> **minimal satu strict**. Titik yang tidak didominasi siapa pun disebut
> **Pareto-optimal**.

Perhatikan definisinya: dua titik yang **identik** tidak saling mendominasi
(tidak ada yang strict), sehingga keduanya Pareto-optimal.

### Aturannya

```
titik i Pareto-optimal
⟺  b_i maksimum di dalam kelompok ber-a SAMA
    DAN  b_i > maksimum b di antara semua titik ber-a LEBIH BESAR
```

Perhatikan **dua tanda pembanding yang berbeda**:

- di dalam kelompok `a` yang sama: seri diperbolehkan (`==` maksimum kelompok)
- terhadap kelompok `a` yang lebih besar: **strict** `>` — karena `a` sudah kalah,
  `b` yang seri pun sudah cukup untuk mendominasi

Menyamakan kedua pembanding itu adalah bug klasik yang **hanya muncul saat ada
nilai berulang**.

### Implementasi

```cpp
sort(v.begin(), v.end(), [](const Item& x, const Item& y) {
    if (x.a != y.a) return x.a > y.a;      // a MENURUN
    return x.b > y.b;                      // b MENURUN saat seri
});

ll maxBdiKiri = LLONG_MIN;
int i = 0;
while (i < n) {
    int j = i;
    while (j < n && v[j].a == v[i].a) j++;      // kelompok ber-a sama
    ll maxBkelompok = v[i].b;                    // sudah terurut menurun
    for (int k = i; k < j; k++)
        if (v[k].b == maxBkelompok && v[k].b > maxBdiKiri) hasil++;
    maxBdiKiri = max(maxBdiKiri, maxBkelompok);
    i = j;
}
```

Memproses **per kelompok** (bukan per elemen) adalah kuncinya. Sapuan naif
elemen-per-elemen akan salah pada `a` yang seri.

### Soal-soal yang memakainya

- Nested Ranges (CSES 2168/2169) — "berapa rentang yang memuat / dimuat"
- Russian Doll Envelopes — dominasi + LIS
- Skyline / titik maksimum pada bidang
- Menghitung pasangan `(i,j)` dengan `a_i ≤ a_j` dan `b_i ≤ b_j`

---

<a name="6"></a>
## 6. Pola B — Sapuan Event dengan Tie-Break

Sudah muncul di Day 72–73, tetapi kali ini dari sudut pandang tie-break.

Pada waktu yang **sama**, urutan pemrosesan event menentukan jawaban:

| Model interval | Yang diproses dulu |
|---|---|
| Setengah terbuka `[l, r)` | **SELESAI** |
| Tertutup `[l, r]` | **MULAI** |

`pair` mengurutkan `{t, -1}` sebelum `{t, +1}` secara otomatis karena `-1 < +1`.
Itu kebetulan yang menguntungkan untuk model setengah terbuka.

Untuk model tertutup, ada dua cara:

```cpp
// (a) geser waktu event selesai
ev.push_back({r + 1, -1});          // hanya untuk waktu bilangan bulat

// (b) beri kode yang mengurut belakangan
ev.push_back({r, +2});              // +1 (mulai) < +2 (selesai)
// lalu saat memproses: cur += (d == +2) ? -1 : d;
```

Cara (b) lebih umum karena bekerja untuk waktu real.

---

<a name="7"></a>
## 7. Pola C — Penjadwalan Dua Tahap

> `n` pekerjaan. Pekerjaan `i` butuh `a_i` waktu pada **satu mesin bersama**,
> lalu `b_i` waktu pada tahap kedua yang **paralel tak terbatas**. Minimalkan
> waktu selesai terakhir.

**Jawaban: urutkan `b` MENURUN.**

Perhatikan bahwa `a` sama sekali tidak muncul dalam kriteria pengurutan — itu
mengejutkan, dan justru itulah yang membuat soal ini instruktif.

### Bukti (exchange argument)

Ambil urutan optimal. Lihat dua pekerjaan **berdampingan** `i` lalu `j`. Misalkan
waktu mesin bersama sebelum keduanya adalah `S`.

```
urutan (i, j): selesai = max( S + a_i + b_i ,  S + a_i + a_j + b_j )
urutan (j, i): selesai = max( S + a_j + b_j ,  S + a_i + a_j + b_i )
```

Kurangi `S + a_i + a_j` dari kedua sisi (konstan):

```
(i, j): max( b_i − a_j ,  b_j )
(j, i): max( b_j − a_i ,  b_i )
```

Andaikan `b_i ≥ b_j`. Maka:

- `b_i − a_j ≤ b_i` dan `b_j ≤ b_i` → sisi kiri `≤ b_i`
- sisi kanan memuat `b_i` → sisi kanan `≥ b_i`

Jadi urutan `(i, j)` **tidak lebih buruk** ketika `b_i ≥ b_j`. Menukar pasangan
berdampingan yang melanggar aturan tidak pernah memperburuk. ∎

Pekerjaan lain tidak terpengaruh karena `a_i + a_j` tetap sama, sehingga waktu
mulai pekerjaan berikutnya identik.

**Diverifikasi:** 20.000 kasus acak dibandingkan dengan seluruh permutasi —
semuanya cocok.

### Kenapa ini penting

Soal ini contoh sempurna bahwa **kriteria pengurutan harus diturunkan, bukan
ditebak**. Naluri akan menyarankan `a` menaik (kerjakan yang cepat dulu), atau
rasio `a/b`. Keduanya salah. Hanya exchange argument yang memberi jawabannya.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Daftar periksa sebelum `sort`

1. Apa kriteria **utamanya**? Menaik atau menurun?
2. Kalau seri, apa yang menentukan? Menaik atau menurun?
3. Kalau masih seri, apakah urutannya penting? Kalau ya → tambahkan indeks.
4. Apakah komparatornya memakai `<` (bukan `<=`)?
5. Apakah setiap cabang memeriksa **ketidaksamaan** dulu?
6. Kalau ada rasio, apakah dibandingkan dengan **perkalian silang**?

### Jebakan

1. **Lupa tie-break sama sekali** — lolos generator berentang besar, gagal di juri.
2. **Memakai `<=`** — melanggar strict weak ordering, bisa crash.
3. **Tie-break tidak memeriksa kesamaan dulu** — komparator asimetris.
4. **Negasi untuk membalik urutan** pada nilai yang bisa `LLONG_MIN`.
5. **Mengandalkan `std::sort` untuk stabilitas** — ia tidak stabil.
6. **Menyamakan pembanding dalam-kelompok dan antar-kelompok** pada dominasi.
7. **Menebak kriteria pengurutan** alih-alih menurunkannya.

### Kompleksitas

| Operasi | Waktu |
|---|---|
| Sorting multi-kriteria | `O(n log n)` |
| Pareto front | `O(n log n)` |
| Sapuan event | `O(n log n)` |
| Penjadwalan dua tahap | `O(n log n)` |

### Latihan mandiri

- Ambil kembali kode Day 72 dan Day 73 kamu, lalu jalankan ulang stress test-nya
  dengan koordinat dibatasi `0..3` alih-alih `0..15`. Kalau ada bug tie-break
  yang tersembunyi, sekaranglah ia akan muncul.
- Tulis komparator yang **sengaja** melanggar strict weak ordering (memakai `<=`),
  lalu jalankan `std::sort` pada 10.000 elemen dengan banyak nilai sama.
  Kompilasi dengan `-D_GLIBCXX_DEBUG` untuk melihat pustaka menangkapnya. Bendera
  itu layak kamu ingat — ia menangkap banyak kesalahan yang tidak terlihat.
