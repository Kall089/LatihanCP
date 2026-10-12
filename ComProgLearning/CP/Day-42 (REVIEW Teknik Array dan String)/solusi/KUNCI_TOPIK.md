# 🔑 Kunci Topik — Day 42

> **Jangan buka file ini sebelum mencoba.** Seluruh nilai hari ini ada pada
> proses menebak tekniknya sendiri. Membaca duluan mengubah sesi diagnosis
> menjadi sesi menyalin.

Pakai file ini dengan cara: kerjakan dulu, catat tebakanmu, **baru** cocokkan.
Kolom terakhir memberitahu hari mana yang perlu diulang kalau kamu meleset.

---

## Latihan (exercise_1 .. exercise_6)

| # | Judul | Teknik | Sinyal penentu | Kalau meleset, ulangi |
|---|-------|--------|----------------|----------------------|
| 1 | Pemanas Gedung | difference array + counting | "setelah SEMUA perintah selesai" | Day 31 |
| 2 | Pasangan Hari Genap | prefix mod + counting | "ada berapa", bukan "maksimum" | Day 29, 40 |
| 3 | Rute Pendakian | Kadane | berurutan + max jumlah + ada negatif + panjang bebas | Day 35 |
| 4 | Hari Lebih Panas | monotonic stack | "untuk setiap i, cari yang terdekat" | Day 36 |
| 5 | Pasangan Kabel | sorting + two pointers | "pasangan", bukan "subarray" → boleh sort | Day 32 |
| 6 | Keranjang Buah | window variabel + frequency map | "berurutan" + "terpanjang" + syarat monoton | Day 34, 40 |

---

## Tugas (tugas_01 .. tugas_15)

| # | Judul | Teknik | Sinyal penentu | Kalau meleset, ulangi |
|---|-------|--------|----------------|----------------------|
| 01 | Rentang Seimbang | transformasi ±1 + prefix map | "sama banyak" → jumlah nol | Day 29, 40 |
| 02 | Apartemen | sorting + two pointers | dua daftar, dicocokkan | Day 32 |
| 03 | Kincir Ria | sorting + two pointers greedy | "minimum gondola", muat dua | Day 32 |
| 04 | Subarray Terpendek ≥ S | two pointers | semua positif + "terpendek" | Day 32, 34 |
| 05 | Rata-rata Panjang K | sliding window tetap | "panjangnya tepat K" | Day 33 |
| 06 | Rentang Harga Saham | monotonic stack | "berapa hari ke belakang sampai..." | Day 36 |
| 07 | Next Greater Melingkar | monotonic stack + trik 2N | "melingkar" + "berikutnya yang lebih besar" | Day 36 |
| 08 | Kelipatan pada Subarray | prefix mod + indeks pertama | "kelipatan K" + syarat panjang ≥ 2 | Day 29, 90 |
| 09 | Membaca Buku | two pointers | semua positif + "berurutan" + batas total | Day 32 |
| 10 | Deret Berurutan | hash set / sorting | posisi tidak penting → boleh sort | Day 21, 40 |
| 11 | Jendela Terkecil Memuat T | window variabel + counting | "terpendek yang memuat semua" | Day 34, 39 |
| 12 | Tiket Konser | multiset + upper_bound | "termahal yang ≤ X" + item terpakai habis | Day 21, 25 |
| 13 | Terpendek ≥ K (ada negatif) | prefix + monotonic deque | ada negatif → two pointers batal | Day 37 |
| 14 | Dua Segmen Panjang Tetap | prefix sum + kunci titik potong | dua segmen, panjang tetap | Day 29, 35 |
| 15 | Median Jendela Geser | multiset + iterator median | "tiap jendela ukuran K" + median | Day 21, 24 |

---

## Cara membaca hasil diagnosismu

Hitung berapa banyak yang **tekniknya salah tebak** (bukan yang implementasinya
bug — itu masalah berbeda).

**0–3 meleset** — kamu siap masuk Day 43. Lubangnya kecil, akan tertutup
sendiri lewat latihan berikutnya.

**4–7 meleset** — ada satu atau dua hari yang benar-benar bocor. Lihat kolom
terakhir, cari hari mana yang paling sering muncul, ulangi **hari itu saja**.
Jangan mengulang seluruh blok; itu buang waktu dan kamu akan mengulang bagian
yang sudah kamu kuasai.

**8+ meleset** — pengenalan polanya belum terbentuk. Yang paling efektif bukan
mengulang teori, tapi mengerjakan Drill 1 di Day-35B dan bagian "Pohon
Keputusan" di Day 41 sampai kamu bisa menyebutnya dari ingatan. Baru kemudian
ulangi tugas hari ini.

---

## Pola kesalahan yang perlu dicurigai

Kalau tebakan salahmu punya pola, itu lebih informatif daripada jumlahnya:

| Pola | Artinya | Perbaikan |
|---|---|---|
| Sering menebak Kadane padahal soal "ada berapa" | belum membedakan optimasi dari counting | Day 35B bagian B.4 |
| Sering menebak sliding window padahal ada negatif | belum memegang syarat monotonisitas | Day 34 |
| Tidak sadar boleh sorting | belum membedakan "subarray" dari "pasangan/himpunan" | Day 41 bagian 5 |
| Menebak benar tapi implementasinya selalu bug | bukan masalah pengenalan; masalah invariant | Day 42 teori bagian 1 |
| Selalu buntu di soal Hard | wajar; itu memang butuh 2–3 teknik digabung | lanjut saja ke Day 43 |
