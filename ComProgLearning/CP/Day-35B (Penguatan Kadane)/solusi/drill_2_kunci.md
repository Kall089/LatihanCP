# ✅ Kunci Drill 2 — Enam Kadane yang Rusak

Aturan soal: subarray **tidak boleh kosong**.

---

### bug1 — `best = 0`
**Bug:** nilai awal `best` menjawab pertanyaan yang berbeda.
`0` adalah jumlah subarray **kosong**, jadi kode ini diam-diam mengizinkan kosong.
**Counterexample:** `[-5]` → benar `-5`, dapat `0`.
**Perbaikan:** `best = LLONG_MIN` (atau `best = cur = a[0]`, loop dari `i = 1`).
**Pelajaran:** ini bug Kadane paling sering di kontes. Tanyakan "boleh kosong?"
**sebelum** menulis baris pertama.

---

### bug2 — urutan update terbalik
```cpp
best = max(best, cur);      // <- cur di sini masih milik i-1
cur  = max(x, cur + x);
```
**Bug:** `best` dibaca sebelum `cur` menyerap `a[i]`, jadi `best` **tertinggal satu
langkah** dan elemen terakhir tidak pernah dipertimbangkan. Untuk `n = 1`, `best`
tidak pernah berubah dari `cur` awal (0).
**Counterexample:** `[5]` → benar `5`, dapat `0`.
**Perbaikan:** tukar dua barisnya. Invariant-nya jelas: *`best` selalu jawaban untuk
prefix yang sudah selesai diproses.*

---

### bug3 — "pengaman" yang justru merusak
Inti Kadane-nya (`if (cur < 0) cur = 0; cur += x;`) sebenarnya **benar**.
Yang salah baris terakhir: `if (best < 0) best = 0;`
**Bug:** memaksa jawaban minimal 0 — lagi-lagi mengizinkan subarray kosong.
**Counterexample:** `[-5]` → benar `-5`, dapat `0`.
**Pelajaran:** waspadai baris "pengaman" yang kamu tambahkan karena panik melihat
angka negatif. Negatif sering memang jawabannya.

---

### bug4 — elemen pertama dihitung dua kali
```cpp
ll best = a[0], cur = a[0];
for (size_t i = 0; ...)      // <- seharusnya i = 1
```
**Bug:** `cur` sudah berisi `a[0]`, lalu iterasi `i = 0` menambahkannya lagi:
`cur = max(a[0], a[0] + a[0])`.
**Counterexample:** `[5]` → benar `5`, dapat `10`.
**Perbaikan:** `i = 1`. Atau lebih aman: `cur = 0; best = LLONG_MIN;` dan loop dari 0 —
lebih sedikit yang bisa salah karena tidak ada nilai awal yang perlu diselaraskan.

---

### bug5 — prefix minimum diperbarui terlalu cepat
```cpp
pre += x;
minPre = min(minPre, pre);         // <- pre saat ini ikut jadi kandidat
best   = max(best, pre - minPre);
```
**Bug:** `minPre` boleh berisi `P[l]` dengan `l ≤ r`, padahal syaratnya `l < r`.
Kalau `minPre == pre`, maka `pre - minPre == 0` — itu subarray kosong.
**Counterexample:** `[-5]` → benar `-5`, dapat `0`.
**Perbaikan:** hitung `best` **dulu**, baru perbarui `minPre`.
**Pelajaran:** di semua teknik "kunci ujung kanan, cari yang terbaik di kiri",
pertanyaan **"apakah dirinya sendiri boleh ikut jadi kandidat?"** adalah sumber bug
tetap. Berlaku juga di monotonic stack dan prefix+map nanti.

---

### bug6 — overflow (yang tidak terjaring stress test)
**Bug:** `cur` dan `best` bertipe `int`. Jumlah bisa melebihi ~2,1 miliar.
Juga `INT_MIN + x` sudah undefined behavior sejak iterasi pertama.
**Kenapa stress test diam:** tesnya memakai `n ≤ 6` dan `|a[i]| ≤ 10`, jumlah maksimum
hanya 60. Overflow tidak akan pernah muncul.
**Counterexample buatan:** `n = 100000` elemen bernilai `100000` → jawaban `10^10`,
jauh di atas `INT_MAX ≈ 2,15 × 10^9`.
**Perbaikan:** `long long`.
**Pelajaran — ini yang paling penting dari drill ini:** stress test hanya menemukan
bug yang **ada di dalam ruang tesnya**. Bug tipe data, bug performa, dan bug batas
`n` tidak akan pernah muncul dari array acak kecil. Baca ulang **constraint** soal;
kalau `n · max|a[i]| > 2 × 10^9`, pakai `long long`.

---

## Rangkuman: enam bug, tiga akar masalah

| Akar masalah | Bug |
|---|---|
| Salah menjawab "boleh kosong?" | 1, 3, 5 |
| Invariant/urutan update tidak dipegang | 2, 4 |
| Batas tipe data & constraint | 6 |

Kalau di soal berikutnya kamu cuma sempat mengecek tiga hal sebelum submit,
cek tiga baris di tabel itu.
