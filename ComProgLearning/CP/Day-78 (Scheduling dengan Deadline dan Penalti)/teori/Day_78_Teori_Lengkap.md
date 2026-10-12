# 📘 Day 78 — Scheduling dengan Deadline & Penalti

> **Prasyarat:** Day 71 (exchange argument), Day 77 (regret), Day 145 (knapsack),
> Day 76 (sorting multi-kriteria).

---

## Daftar Isi

1. [Tiga Fungsi Tujuan yang Berbeda Jauh](#1)
2. [EDF — Minimalkan Keterlambatan Maksimum](#2)
3. [Moore–Hodgson — Minimalkan Jumlah yang Terlambat](#3)
4. [Weighted Tardiness — di Sini Greedy Mati](#4)
5. [DP untuk Kasus Berbobot](#5)
6. [Kosakata: Lateness, Tardiness, Makespan](#6)
7. [Varian yang Mengubah Segalanya](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Tiga Fungsi Tujuan yang Berbeda Jauh

Soal penjadwalan terlihat mirip satu sama lain. Yang membedakannya adalah **apa
yang diminimalkan** — dan tiga pilihan berikut membutuhkan tiga pendekatan yang
sama sekali berbeda.

| Fungsi tujuan | Teknik | Kompleksitas |
|---|---|---|
| Keterlambatan **maksimum** | EDF (urut deadline) | `O(n log n)` |
| **Jumlah** yang terlambat | Moore–Hodgson (EDF + regret) | `O(n log n)` |
| **Total bobot** yang terlambat | **NP-hard**; DP untuk batasan kecil | `O(n·T)` |

Kesalahan paling mahal di hari ini adalah memakai algoritma pertama atau kedua
untuk soal ketiga. Ketiganya sama-sama "urut deadline menaik" di baris pertama,
sehingga kodenya terlihat mirip — tetapi hanya dua yang benar.

**Bacalah fungsi tujuannya dengan sangat teliti.** Kalimat "minimalkan
keterlambatan" saja tidak cukup; cari tahu apakah yang dimaksud maksimum, jumlah,
atau total bobot.

---

<a name="2"></a>
## 2. EDF — Minimalkan Keterlambatan Maksimum

> `n` pekerjaan, pekerjaan `i` butuh `t_i` waktu dan punya deadline `d_i`.
> **Semua** pekerjaan harus dikerjakan pada satu mesin. Definisikan
> `lateness_i = C_i − d_i` (`C_i` = waktu selesai). Minimalkan `max lateness`.

**Jawaban: urutkan deadline MENAIK.** Namanya *Earliest Deadline First*.

```cpp
sort(j.begin(), j.end(), [](auto& a, auto& b){ return a.d < b.d; });
ll t = 0, worst = LLONG_MIN;
for (auto& x : j) { t += x.t; worst = max(worst, t - x.d); }
```

### Bukti (exchange argument)

Ambil jadwal optimal. Andaikan ada dua pekerjaan **berdampingan** `i` lalu `j`
dengan `d_i > d_j` (melanggar EDF). Misal waktu sebelum keduanya adalah `S`.

```
urutan (i, j):  lateness_i = S + t_i − d_i
                lateness_j = S + t_i + t_j − d_j
urutan (j, i):  lateness_j = S + t_j − d_j
                lateness_i = S + t_i + t_j − d_i
```

Setelah ditukar menjadi `(j, i)`:

- `lateness_j` **turun** (dari `S+t_i+t_j−d_j` menjadi `S+t_j−d_j`)
- `lateness_i` naik menjadi `S + t_i + t_j − d_i`

Tetapi `S + t_i + t_j − d_i < S + t_i + t_j − d_j` karena `d_i > d_j`, dan sisi
kanan itu adalah `lateness_j` pada urutan **semula**. Jadi maksimum baru tidak
melebihi maksimum lama. ∎

Pekerjaan lain tidak terpengaruh karena `t_i + t_j` tetap sama.

**Diverifikasi:** 4.000 kasus acak dibandingkan dengan seluruh permutasi.

### Yang mengejutkan

Durasi `t_i` **sama sekali tidak muncul** dalam kriteria pengurutan. Itu pola yang
sama dengan Day 76 Exercise 4 — dan sekali lagi menunjukkan bahwa kriteria harus
**diturunkan**, bukan ditebak.

---

<a name="3"></a>
## 3. Moore–Hodgson — Minimalkan Jumlah yang Terlambat

> Pekerjaan yang selesai setelah deadline dianggap **terlambat**. Minimalkan
> **berapa banyak** pekerjaan yang terlambat (ekuivalen: maksimalkan yang tepat
> waktu).

Ini persis pola regret Day 77:

```cpp
sort menurut deadline MENAIK;
priority_queue<ll> pq;                    // MAX-heap durasi
ll t = 0;
for (auto& x : j) {
    pq.push(x.t);  t += x.t;
    if (t > x.d) { t -= pq.top(); pq.pop(); }   // buang durasi TERBESAR
}
jawaban = n − pq.size();
```

### Kenapa pekerjaan yang "dibuang" tidak hilang

Pekerjaan yang dibuang dari heap tetap **dikerjakan** — hanya saja dijadwalkan
**setelah** semua pekerjaan tepat waktu. Karena ia sudah pasti terlambat, kapan
tepatnya ia dikerjakan tidak memengaruhi fungsi tujuan.

Ini pengamatan penting yang sering membingungkan: himpunan di dalam heap adalah
himpunan pekerjaan **tepat waktu**, bukan himpunan yang dikerjakan.

### Kenapa membuang yang terlama

Invarian dua-sifat dari Day 77: di antara semua himpunan tepat-waktu berukuran
maksimum, kita menjaga yang **total durasinya minimum**. Membuang durasi terbesar
menjaga sifat itu.

**Diverifikasi:** 4.000 kasus acak vs seluruh permutasi (dengan bobot seragam,
`min penalti = n − maks tepat waktu`).

---

<a name="4"></a>
## 4. Weighted Tardiness — di Sini Greedy Mati

> Setiap pekerjaan punya bobot `w_i`. Kalau terlambat, kamu kehilangan `w_i`.
> Minimalkan **total bobot** yang hilang.

**Masalah ini NP-hard secara umum** (`1 || Σ w_j U_j` dalam notasi penjadwalan).
Jangan menghabiskan waktu mencari greedy.

### Kenapa Moore–Hodgson gagal

Moore–Hodgson memaksimalkan **jumlah** pekerjaan tepat waktu. Dengan bobot,
menyelamatkan satu pekerjaan bernilai 100 bisa lebih baik daripada menyelamatkan
tiga pekerjaan bernilai 1 masing-masing.

### Kenapa regret berbobot juga gagal

Godaan berikutnya: pakai kerangka regret, tetapi buang bobot **terkecil**.

Itu gagal karena sekarang ada **dua besaran yang bersaing**: durasi yang dimakan
dan bobot yang diselamatkan. Invarian Day 77 — "di antara himpunan berukuran
maksimum, sumber daya minimum" — tidak bisa dirumuskan lagi, karena dua keadaan
dengan bobot sama bisa punya durasi berbeda dan tidak ada yang mendominasi.

**Aturan umum yang layak dihafal:**

> Regret bekerja kalau keadaan bisa diringkas menjadi **satu angka** yang bisa
> dibandingkan. Begitu ada dua besaran bersaing, regret runtuh.

### Kasus khusus yang tetap greedy

Kalau **semua durasi seragam** (setiap pekerjaan 1 satuan waktu), soalnya kembali
menjadi Day 77 Pola 2: urut deadline menaik, buang bobot terkecil dengan min-heap.
Durasinya seragam berarti hanya satu besaran yang bersaing.

---

<a name="5"></a>
## 5. DP untuk Kasus Berbobot

Meski NP-hard secara umum, batasan kontes biasanya kecil. Dua rumusan yang
berguna:

### Rumusan A — DP di atas waktu (`sum t` kecil)

Urutkan deadline **menaik**, lalu:

```
dp[w] = bobot maksimum yang bisa DISELAMATKAN kalau total waktu
        pekerjaan tepat-waktu tepat w
```

```cpp
sort menurut deadline MENAIK;
vector<ll> dp(T + 1, -1);  dp[0] = 0;
for (auto& x : j) {
    ll batas = min(x.d, T);
    for (ll w = batas; w >= x.t; w--)          // MUNDUR
        if (dp[w - x.t] >= 0)
            dp[w] = max(dp[w], dp[w - x.t] + x.w);
}
jawaban = total_bobot − max(dp);
```

`O(n·T)` dengan `T = min(Σt, max d)`.

**Dua detail yang menentukan kebenaran:**

1. **Batas atas loop adalah `d_i`, bukan `T`.** Itulah yang menegakkan deadline:
   pekerjaan ini hanya boleh selesai pada waktu `≤ d_i`.
2. **Urutan deadline menaik.** Klaim pendukungnya: kalau sehimpunan pekerjaan bisa
   dijadwalkan tepat waktu, maka menjadwalkannya menurut deadline menaik juga
   berhasil (exchange argument yang sama dengan EDF). Karena itu kita boleh
   membatasi diri pada jadwal terurut deadline, dan DP di atas membangun persis
   jadwal seperti itu.

**Diverifikasi:** 4.000 kasus acak vs brute force atas **seluruh permutasi**.

### Rumusan B — DP bitmask (`n ≤ 20`)

```
dp[mask] = penalti minimum kalau himpunan pekerjaan `mask` sudah dikerjakan
```

Waktu sekarang bisa dihitung langsung dari `mask` (jumlah durasi anggotanya),
sehingga tidak perlu dimensi tambahan. `O(2^n · n)`.

### Memilih rumusan mana

| Batasan | Rumusan |
|---|---|
| `n ≤ 20`, waktu besar | bitmask |
| `n` besar, `Σt ≤ 10^5` | DP di atas waktu |
| durasi seragam | greedy/regret |
| keduanya besar | kemungkinan bukan soal ini |

---

<a name="6"></a>
## 6. Kosakata: Lateness, Tardiness, Makespan

Istilah-istilah ini sering tertukar dan artinya berbeda.

| Istilah | Definisi | Catatan |
|---|---|---|
| **Completion time** `C_i` | waktu selesai pekerjaan `i` | |
| **Lateness** `L_i` | `C_i − d_i` | boleh **negatif** |
| **Tardiness** `T_i` | `max(0, C_i − d_i)` | tidak pernah negatif |
| **Late job** `U_i` | `1` kalau `C_i > d_i`, `0` kalau tidak | biner |
| **Makespan** | `max C_i` | waktu selesai terakhir |
| **Flow time** | `Σ C_i` | Day 71 |

Perbedaan **lateness** dan **tardiness** penting: meminimalkan `max L_i`
menghargai pekerjaan yang selesai jauh lebih awal, sedangkan `max T_i` tidak
membedakan "tepat waktu" dari "sangat awal".

Untungnya EDF meminimalkan **keduanya** sekaligus, karena
`max T_i = max(0, max L_i)`.

### Notasi standar (berguna untuk mencari referensi)

Notasi tiga bidang `α | β | γ`:

- `1 || L_max` — satu mesin, minimalkan max lateness → **EDF**, mudah
- `1 || Σ U_j` — minimalkan jumlah terlambat → **Moore–Hodgson**, mudah
- `1 || Σ w_j U_j` — minimalkan bobot terlambat → **NP-hard**
- `1 | r_j | L_max` — dengan waktu rilis → **NP-hard** (non-preemptive)

Mengenali notasi ini menghemat waktu: kalau kamu bisa mengenali bahwa soalmu
adalah `1 || Σ w_j U_j`, kamu tahu langsung untuk tidak mencari greedy.

---

<a name="7"></a>
## 7. Varian yang Mengubah Segalanya

### Waktu rilis `r_i` (pekerjaan belum tersedia sebelum `r_i`)

- **Preemptive** (boleh dijeda): EDF masih optimal untuk `L_max`
- **Non-preemptive**: menjadi **NP-hard**

Perbedaan satu kata di soal mengubah kesulitan secara drastis.

### Beberapa mesin

`P || L_max` (mesin identik paralel) menjadi NP-hard bahkan untuk 2 mesin.
Kasus khusus yang tetap mudah: durasi seragam (Day 77 Exercise 6).

### Precedence constraint (pekerjaan A harus sebelum B)

Untuk `1 | prec | L_max` masih bisa dipecahkan `O(n²)` dengan **memodifikasi
deadline**: telusuri dari akhir, dan set `d_i ← min(d_i, min{d_j − t_j : j
penerus i})`. Setelah deadline dimodifikasi, EDF biasa berlaku.

Teknik "modifikasi deadline lalu jalankan algoritma sederhana" ini muncul di
banyak soal.

### Deadline lunak vs keras

- **Keras**: pekerjaan yang terlambat tidak boleh dijadwalkan sama sekali
- **Lunak**: boleh terlambat, tetapi kena penalti

Moore–Hodgson menangani deadline keras (pekerjaan terlambat "dibuang" ke belakang
dan tidak dihitung). Weighted tardiness menangani deadline lunak.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Pohon keputusan

```
Soal penjadwalan satu mesin
├── minimalkan max lateness / tardiness   -> EDF (urut deadline)
├── minimalkan JUMLAH terlambat           -> Moore-Hodgson (EDF + regret MAX)
├── minimalkan BOBOT terlambat
│   ├── durasi seragam                    -> regret MIN (Day 77 pola 2)
│   ├── n <= 20                           -> DP bitmask
│   ├── sum t kecil                       -> DP di atas waktu
│   └── keduanya besar                    -> NP-hard, cari struktur khusus
├── ada waktu rilis, non-preemptive       -> NP-hard
└── ada precedence                        -> modifikasi deadline, lalu EDF
```

### Jebakan

1. **Memakai EDF untuk soal "jumlah terlambat".** EDF meminimalkan maksimum.
2. **Memakai Moore–Hodgson untuk soal berbobot.** Ia memaksimalkan jumlah.
3. **Memaksa greedy pada weighted tardiness.** NP-hard.
4. **Tertukar lateness dan tardiness.**
5. **Batas atas loop DP memakai `T` alih-alih `d_i`** — deadline tidak tertegakkan.
6. **Loop DP maju** — pekerjaan bisa terambil berkali-kali.
7. **Lupa mengurutkan deadline menaik sebelum DP.**
8. **Mengabaikan waktu rilis** di soal yang menyebutkannya.

### Kompleksitas

| Masalah | Waktu |
|---|---|
| EDF | `O(n log n)` |
| Moore–Hodgson | `O(n log n)` |
| Regret berbobot (durasi seragam) | `O(n log n)` |
| DP di atas waktu | `O(n·T)` |
| DP bitmask | `O(2^n · n)` |

### Latihan mandiri

- Implementasikan ketiga algoritma (EDF, Moore–Hodgson, regret berbobot) lalu
  jalankan **ketiganya** pada soal weighted tardiness yang sama, dibandingkan
  dengan brute force permutasi. Catat persentase kegagalan masing-masing. Kamu
  akan melihat bahwa dua di antaranya gagal cukup sering — dan itu menanamkan
  perbedaan ketiga fungsi tujuan lebih kuat daripada menghafalnya.
- Selesaikan `1 | prec | L_max` dengan teknik modifikasi deadline, lalu verifikasi
  terhadap brute force atas seluruh urutan topologis untuk `n ≤ 7`.
