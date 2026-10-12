# 📘 Day 79 — Cara Membuktikan (atau Membantah) Greedy

> **Prasyarat:** seluruh Day 71–78. Hari ini tidak memperkenalkan algoritma baru;
> ia memberi **perkakas** untuk memutuskan apakah sebuah ide greedy benar.

---

## Daftar Isi

1. [Urutan Kerja yang Benar](#1)
2. [Menulis Brute Force yang Pasti Benar](#2)
3. [Merancang Generator untuk Memecahkan Kodemu](#3)
4. [Mengecilkan Contoh Tandingan](#4)
5. [Empat Alat Bukti](#5)
6. [Tanda-Tanda Greedy Akan Gagal](#6)
7. [Angka-Angka yang Layak Diingat](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Urutan Kerja yang Benar

Hampir semua orang membalik urutan ini, dan itu adalah pemborosan waktu terbesar
di kontes.

```
❌ URUTAN YANG SALAH
   1. punya ide greedy
   2. yakin ia benar
   3. tulis kodenya (20 menit)
   4. submit
   5. WA
   6. tidak tahu kenapa

✅ URUTAN YANG BENAR
   1. tulis BRUTE FORCE dulu        (5 menit, pasti benar)
   2. tulis GENERATOR yang dirancang untuk memecahkan
   3. baru tulis greedy
   4. adu keduanya ribuan kali      (30 detik)
   5. kalau lolos, BARU cari buktinya
```

**Menulis bukti untuk ide yang salah** adalah kesia-siaan yang paling sering
terjadi. Kamu bisa menghabiskan 15 menit mencoba membuktikan sesuatu yang bisa
dibantah dalam 30 detik oleh stress test.

Sebaliknya, kalau stress test lolos 20.000 kasus, peluang idemu salah menjadi
sangat kecil — dan sekarang kamu tahu **apa** yang harus dibuktikan, sehingga
buktinya jauh lebih mudah dicari.

### Kenapa brute force dulu

1. Ia **pasti benar** — tidak ada yang perlu dipercayai
2. Menulisnya memaksa kamu memahami soal dengan tepat
3. Ia menjadi patokan untuk semua ide berikutnya, bukan hanya yang pertama

Waktu yang "hilang" untuk menulisnya hampir selalu kembali berlipat.

---

<a name="2"></a>
## 2. Menulis Brute Force yang Pasti Benar

Aturan utamanya: **brute force harus jelas benar, bukan cepat.** Jangan
mengoptimalkannya — setiap optimasi adalah kesempatan untuk salah.

### Tiga bentuk yang menutup hampir semua kebutuhan

**(a) Semua himpunan bagian** — untuk "pilih sebagian", `n ≤ 20`:

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    // bangun himpunan, periksa kelayakan, hitung nilainya
}
```

**(b) Semua permutasi** — untuk "susun urutan", `n ≤ 8`:

```cpp
vector<int> p(n);
iota(p.begin(), p.end(), 0);
do {
    // simulasikan urutan p, hitung nilainya
} while (next_permutation(p.begin(), p.end()));
```

**(c) Rekursi menyeluruh** — untuk "lakukan operasi berulang":

```cpp
ll rec(Keadaan s) {
    if (selesai(s)) return nilai(s);
    ll best = ...;
    for (setiap langkah yang mungkin)
        best = optimalkan(best, rec(langkahkan(s, langkah)));
    return best;
}
```

### Batas ukuran yang praktis

| Bentuk | `n` maksimum praktis | Alasan |
|---|---|---|
| Himpunan bagian `2^n` | 18–20 | `2^20 ≈ 10^6` |
| Permutasi `n!` | 8 | `8! = 40320` |
| Rekursi penuh | bergantung percabangan | ukur sendiri |

Kalau brute force-mu terlalu lambat untuk `n` yang kamu butuhkan, **kecilkan
`n`**, jangan optimalkan brute force-nya. Bug greedy hampir selalu muncul pada
`n` kecil.

---

<a name="3"></a>
## 3. Merancang Generator untuk Memecahkan Kodemu

Ini bagian yang paling sering dilakukan asal-asalan, dan paling menentukan.

> **Generator yang bagus dirancang untuk MEMECAHKAN kodemu, bukan "acak saja".**

### Eksperimen yang membuktikan poin ini

Ambil bug sederhana: soal "pilih dua bilangan dengan **nilai berbeda** yang
jumlahnya terbesar", dengan kode salah yang mengambil dua terbesar tanpa memeriksa
keunikan nilai.

| Rentang generator | Persentase kegagalan |
|---|---|
| `1..3` | **54,3%** |
| `1..1.000.000` | **0,0%** |

**Bug yang sama. Generator berbeda. Kesimpulan yang berlawanan.** Dengan rentang
besar, kamu akan menyimpulkan kodemu benar dan submit — lalu WA.

Template hari ini menjalankan eksperimen ini sendiri agar kamu melihat angkanya.

### Tabel rentang menurut apa yang diuji

| Yang ingin dipecahkan | Rentang nilai | Ukuran `n` |
|---|---|---|
| Tie-break, nilai berulang | **sangat kecil** (`0..3`) | kecil |
| Interval tumpang tindih | kecil (`0..15`) | kecil |
| Overflow | **maksimum** (`10^18`) | maksimum |
| Presisi pecahan | dua nilai hampir sama | kecil |
| Kasus tepi | `n = 1`, `n = 2`, semua sama | minimum |
| Performa | maksimum | maksimum |

### Prinsip: buat tabrakan sering terjadi

Kalau soalmu tentang interval, buat koordinatnya kecil supaya interval sering
bertabrakan. Kalau tentang komparator, buat nilainya sedikit supaya seri sering
terjadi. Kalau tentang kapasitas, buat kapasitasnya ketat supaya batasan sering
terlanggar.

**Struktur khusus juga penting.** Selain acak seragam, cobalah: semua nilai sama,
nilai terurut menaik, terurut menurun, satu nilai sangat besar di antara yang
kecil, dan barisan Fibonacci (untuk memaksa kedalaman rekursi).

---

<a name="4"></a>
## 4. Mengecilkan Contoh Tandingan

Setelah stress test menemukan kegagalan, contoh pertamanya biasanya besar dan
sulit dipahami. **Kecilkan dulu sebelum menganalisisnya.**

Algoritmanya sederhana dan bisa ditulis sekali lalu dipakai selamanya:

```
selama masih berubah:
    untuk tiap elemen:
        coba BUANG elemen itu
        kalau masih gagal, terima pengecilan
    untuk tiap elemen:
        coba KECILKAN nilainya
        kalau masih gagal, terima pengecilan
```

Contoh tandingan minimal jauh lebih berharga:

- **mudah dipahami** — kamu bisa melihat *kenapa* greedy gagal
- **mudah diingat** — menjadi perkakas untuk soal-soal berikutnya
- **mudah dipakai menguji** ide perbaikanmu

Contoh tandingan klasik yang layak dihafal semuanya berukuran 3–5 elemen. Itu
bukan kebetulan — pengecilan otomatislah yang membuatnya begitu.

---

<a name="5"></a>
## 5. Empat Alat Bukti

Setelah stress test lolos, saatnya membuktikan. Empat pola ini menutup hampir
semua greedy yang akan kamu temui.

### (a) Exchange argument — yang paling sering dipakai

> Ambil solusi optimal yang **melanggar** kriteria greedy. Cari dua elemen
> **berdampingan** yang melanggar. Tukar. Tunjukkan tidak memburuk.

Kenapa berdampingan? Karena penukaran dua elemen berdampingan tidak mengubah apa
pun untuk elemen di luar keduanya — dan itulah yang membuat perhitungannya bisa
disederhanakan sampai tersisa perbandingan dua elemen.

Dipakai di: Day 71 (semua), Day 72 (activity selection), Day 74 (fractional),
Day 76 (dua tahap), Day 78 (EDF).

### (b) Greedy stays ahead

> Tunjukkan bahwa setelah langkah ke-`k`, solusi greedy selalu "tidak lebih
> buruk" dari solusi optimal mana pun pada ukuran tertentu.

Untuk activity selection: setelah memilih `k` interval, interval ke-`k` yang
dipilih greedy selesai **tidak lebih lambat** dari interval ke-`k` solusi mana pun.

Cocok ketika greedy membangun solusi selangkah demi selangkah dan ada ukuran
alami yang bisa dibandingkan.

### (c) Argumen dominasi keadaan

> Tunjukkan keadaan yang dihasilkan greedy **mendominasi**: apa pun yang bisa
> dilakukan dari keadaan lain, bisa juga dilakukan dari keadaan ini.

Untuk regret (Day 77): setelah memproses `i` kandidat, greedy menjaga himpunan
berukuran maksimum **dan** ber-sumber-daya-terpakai minimum. Sifat kedua yang
membuat induksinya berjalan.

Ini juga yang memberi **penyaring cepat**: kalau keadaan tidak bisa diringkas
menjadi satu angka yang bisa dibandingkan, dominasi tidak bisa dirumuskan, dan
greedy kemungkinan besar salah.

### (d) Batas bawah bertemu batas atas

> Tunjukkan batas bawah `B` yang berlaku untuk **semua** solusi, lalu tunjukkan
> greedy mencapai `B`.

Untuk "ruangan minimum" (Day 72): batas bawah adalah tumpang tindih maksimum
(jelas dibutuhkan), dan algoritma sapuan mencapainya persis.

Ini bukti terbersih kalau kamu bisa menemukan batas bawahnya, dan sering
memberikan pemahaman terdalam tentang struktur soal.

---

<a name="6"></a>
## 6. Tanda-Tanda Greedy Akan Gagal

Daftar periksa cepat sebelum menghabiskan waktu.

| Tanda | Kemungkinan besar |
|---|---|
| `n ≤ 20` | bitmask / brute force |
| `n ≤ 100` + kapasitas | DP knapsack |
| Ada **bobot** per elemen | curigai DP |
| **Dua besaran bersaing** | hampir pasti DP |
| "pilih paling banyak `K`" dengan trade-off | DP atau regret |
| Jawaban monoton terhadap suatu nilai | binary search on answer |
| Idemu benar untuk 10 kasus lalu gagal | greedy-nya memang salah |

**"Dua besaran bersaing" adalah penyaring terkuat.** Kalau kamu tidak bisa
mengurutkan keadaan menurut satu angka, greedy hampir pasti mati.

### Batasan kecil hampir selalu disengaja

Kalau soal memberi `n ≤ 18` padahal algoritmamu `O(n log n)`, kamu hampir pasti
salah membaca soal — atau soalnya memang tidak bisa greedy. Penulis soal tidak
memasang batasan sekecil itu tanpa alasan.

---

<a name="7"></a>
## 7. Angka-Angka yang Layak Diingat

Persentase kegagalan yang diukur langsung (bukan ditebak) pada masukan acak kecil:

| Klaim greedy | Persentase gagal |
|---|---|
| Knapsack 0/1 pakai rasio tertinggi | **~12%** |
| Tukar uang pakai koin terbesar | **~10%** |
| Antrean bermodal pakai `m` menurun (Day 76) | **~2%** |

### Kenapa angka-angka ini penting

Kalau kamu menguji ide greedy pada **5 sampel** dan semuanya lolos, sementara
ide itu sebenarnya gagal 12% dari waktu, peluang lolos lima kali berturut-turut
adalah `0,88^5 ≈ 53%`.

> **Lima sampel tidak membuktikan apa pun.**

Bahkan pada tingkat kegagalan 2%, kamu butuh sekitar 150 kasus untuk punya peluang
95% menemukannya. Karena itu stress test harus **ribuan** kasus, bukan puluhan —
dan itu murah: 20.000 kasus kecil biasanya selesai dalam hitungan detik.

### Contoh tandingan yang layak dihafal

| Klaim | Contoh tandingan | Greedy | Optimal |
|---|---|---|---|
| Knapsack 0/1 rasio | `W=10`, `(6,7) (5,5) (5,5)` | 7 | 10 |
| Koin terbesar | koin `{1,3,4}`, bayar 6 | 3 | 2 |
| Interval terpendek dulu | `[1,10] [9,12] [11,20]` | 1 | 2 |
| Interval mulai terkecil | `[1,100] [2,3] [4,5]` | 1 | 2 |
| Jembatan senter | `{1,2,5,10}` | 19 | 17 |
| Huffman sekuensial | `{1,1,1,1,1,1}` | 20 | 16 |

Enam contoh ini menutup sebagian besar kesalahan greedy yang akan kamu temui.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Daftar periksa sebelum submit solusi greedy

1. Sudahkah aku menulis brute force?
2. Sudahkah aku menjalankan minimal 10.000 kasus?
3. Apakah generatorku memakai rentang nilai **kecil**?
4. Sudahkah aku mencoba `n = 1`, `n = 2`, dan semua-nilai-sama?
5. Sudahkah aku mencoba struktur khusus (terurut, semua sama, satu outlier)?
6. Apakah aku bisa menuliskan buktinya dalam tiga kalimat?
7. Apakah batasan soal masuk akal untuk `O(n log n)`?

Kalau nomor 6 tidak bisa dijawab, jangan submit — cari lagi.

### Jebakan

1. **Menulis greedy dulu, brute force belakangan** (atau tidak sama sekali).
2. **Generator berentang besar** — bug tie-break dan kasus tepi tidak akan muncul.
3. **Menguji hanya puluhan kasus.**
4. **Menganalisis contoh tandingan yang besar** tanpa mengecilkannya dulu.
5. **Menghabiskan waktu membuktikan ide yang salah.**
6. **Mengabaikan batasan kecil** yang jelas disengaja penulis soal.
7. **Brute force yang "dioptimalkan"** — setiap optimasi adalah kesempatan salah.
8. **Membandingkan greedy dengan greedy lain** alih-alih dengan brute force.

### Latihan mandiri

- Simpan kerangka `stressTest` dari template hari ini ke dalam berkas templatemu
  sendiri. Ia dirancang agar cukup mengganti tiga lambda untuk soal apa pun.
  Perkakas yang siap pakai adalah perbedaan antara "seharusnya aku uji" dan
  "sudah kuuji".
- Ambil tiga soal greedy yang sudah kamu selesaikan dari Day 71–78, lalu jalankan
  ulang stress test-nya dengan rentang nilai **dibagi sepuluh**. Catat apakah ada
  yang mulai gagal. Kalau ada, kamu baru saja menemukan bug yang akan muncul di
  kontes.
- Tulis versi `perkecil` yang juga bisa mengecilkan **struktur** masukan (misalnya
  menghapus sisi dari graf), bukan hanya nilai dan panjang array.
