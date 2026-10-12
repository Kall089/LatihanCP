# 📘 Day 72 — Activity Selection & Interval Scheduling

> **Prasyarat:** Day 71 (exchange argument), Day 43–47 (sorting & komparator),
> Day 24 (priority queue), Day 49 (lower_bound).

---

## Daftar Isi

1. [Kenapa Interval Punya Bab Sendiri](#1)
2. [Activity Selection: Masalah Intinya](#2)
3. [Bukti: Kenapa "Ujung Terkecil" Benar](#3)
4. [Tiga Kriteria Salah yang Terlihat Masuk Akal](#4)
5. [Tertutup vs Setengah Terbuka: Penyebab WA Nomor Satu](#5)
6. [Varian: Minimal Dibuang, Minimal Ruangan](#6)
7. [Kapan Greedy Berhenti Bekerja: Interval Berbobot](#7)
8. [Ringkasan, Jebakan, dan Latihan Mandiri](#8)

---

<a name="1"></a>
## 1. Kenapa Interval Punya Bab Sendiri

Soal interval muncul terus-menerus di kontes, dan alasannya struktural: interval
adalah cara paling alami untuk memodelkan **waktu**, **rentang koordinat**,
**segmen pada garis**, dan **subarray**. Begitu kamu bisa mengenali "ini soal
interval", ruang kemungkinan solusinya menyempit drastis menjadi kira-kira lima
pola.

Yang membuatnya berbahaya: soal-soal interval terlihat mirip satu sama lain
padahal jawabannya sangat berbeda.

| Pertanyaan | Jawabannya |
|---|---|
| Berapa **paling banyak** interval saling lepas? | greedy, urut ujung |
| Berapa **paling sedikit** interval dibuang agar sisanya lepas? | greedy yang sama, `n − hasil` |
| Berapa **ruangan minimum** untuk menjadwalkan **semua**? | sapuan event / heap |
| Berapa **total bobot maksimum** interval saling lepas? | **DP**, bukan greedy |
| Berapa interval minimum untuk **menutupi** `[0, T]`? | greedy berbeda (Day 73) |

Empat kata pertama dalam soal ("paling banyak", "paling sedikit", "semua",
"bobot") menentukan seluruh pendekatanmu. Membaca soal dengan teliti di sini
lebih berharga daripada mengetik cepat.

---

<a name="2"></a>
## 2. Activity Selection: Masalah Intinya

> Diberikan `n` interval `[l_i, r_i]`. Pilih sebanyak mungkin interval sehingga
> tidak ada dua yang tumpang tindih.

**Algoritmanya tiga baris:**

```cpp
sort(a.begin(), a.end(), [](auto& x, auto& y){ return x.r < y.r; });

int hit = 0;
ll akhir = LLONG_MIN;
for (auto& it : a)
    if (it.l > akhir) { hit++; akhir = it.r; }
```

Kompleksitas `O(n log n)`, didominasi pengurutan. Sapuannya sendiri `O(n)`.

**Intuisi satu kalimat:**

> Interval yang **selesai paling awal** menyisakan sisa waktu **terbanyak** untuk
> semua interval berikutnya.

Perhatikan bahwa intuisi ini tidak menyebut panjang, tidak menyebut waktu mulai.
Yang penting hanya: kapan sumber daya itu **bebas kembali**.

### Menjalankannya dengan tangan

Interval: `[1,4] [3,5] [0,6] [5,7] [3,9] [5,9] [6,10] [8,11] [8,12] [2,14] [12,16]`

Setelah diurutkan menurut `r` (sudah terurut di atas):

| Interval | `akhir` sekarang | Diambil? |
|---|---|---|
| `[1,4]` | −∞ | ✅ → `akhir = 4` |
| `[3,5]` | 4 | ❌ (3 ≤ 4) |
| `[0,6]` | 4 | ❌ |
| `[5,7]` | 4 | ✅ → `akhir = 7` |
| `[3,9]` `[5,9]` | 7 | ❌ |
| `[6,10]` | 7 | ❌ |
| `[8,11]` | 7 | ✅ → `akhir = 11` |
| `[8,12]` `[2,14]` | 11 | ❌ |
| `[12,16]` | 11 | ✅ → `akhir = 16` |

Hasil: **4** interval — `[1,4] [5,7] [8,11] [12,16]`.

---

<a name="3"></a>
## 3. Bukti: Kenapa "Ujung Terkecil" Benar

Ini exchange argument dari Day 71, diterapkan pada interval.

**Klaim.** Ada solusi optimal yang memuat interval dengan `r` terkecil.

**Bukti.** Misalkan `x` adalah interval dengan `r` terkecil di antara semua
interval. Ambil sembarang solusi optimal `S`.

- Jika `x ∈ S`, selesai.
- Jika `x ∉ S`, lihat interval `y ∈ S` yang selesai paling awal. Karena `x`
  punya `r` terkecil secara global, `r_x ≤ r_y`.

  Ganti `y` dengan `x`, hasilkan `S' = S \ {y} ∪ {x}`.

  Apakah `S'` masih saling lepas? Interval lain di `S` semuanya mulai **setelah**
  `r_y` (karena `y` selesai paling awal di `S` dan `S` saling lepas). Karena
  `r_x ≤ r_y`, interval-interval itu juga mulai setelah `r_x`. Jadi ya, `S'`
  saling lepas.

  Dan `|S'| = |S|`, jadi `S'` juga optimal. ∎

**Langkah induksi.** Setelah mengambil `x`, buang semua interval yang tumpang
tindih dengannya (mereka tidak mungkin dipakai bersama `x`). Sisanya adalah
soal activity selection yang lebih kecil dan strukturnya identik — inilah
**optimal substructure**. Ulangi argumen yang sama.

Dua bahan Day 71 lengkap: greedy choice property (klaim di atas) + optimal
substructure (langkah induksi). Greedy-nya sah.

---

<a name="4"></a>
## 4. Tiga Kriteria Salah yang Terlihat Masuk Akal

Ini bagian terpenting dari hari ini. Hafalkan ketiga contoh tandingannya.

### ❌ Salah 1: urutkan menurut waktu **mulai**

```
[1, 100]   [2, 3]   [4, 5]
```

Greedy-mulai mengambil `[1,100]` lebih dulu, lalu tidak ada lagi yang muat → **1**.
Optimal: `[2,3]` dan `[4,5]` → **2**.

*Kenapa gagal:* mulai lebih awal tidak berarti apa-apa kalau interval itu
menahan sumber daya selamanya.

### ❌ Salah 2: urutkan menurut **panjang** (terpendek dulu)

```
[1, 10]   [9, 12]   [11, 20]
```

Greedy-panjang mengambil `[9,12]` (panjang 3) lebih dulu, dan interval itu
memblokir **keduanya** → **1**. Optimal: `[1,10]` dan `[11,20]` → **2**.

*Kenapa gagal:* interval pendek yang berada di **tengah** bisa merusak dua
interval sekaligus. Yang penting bukan seberapa banyak waktu yang dipakai,
melainkan **di mana** interval itu berakhir.

### ❌ Salah 3: urutkan menurut **jumlah konflik** (paling sedikit konflik dulu)

Ini kriteria yang paling meyakinkan, dan tetap salah. Contoh tandingan klasik:

```
[0,2] [0,2] [0,2]
      [2,4]
[4,6] [4,6] [4,6]
      [6,8]
[8,10] [8,10] [8,10]
```

Susunannya dibuat agar sebuah interval di tengah punya konflik paling sedikit
tetapi memilihnya menghalangi dua pilihan yang lebih baik. Kriteria ini bisa
memberikan 3 padahal optimal 4.

*Pelajaran:* "paling sedikit konflik" adalah heuristik, bukan bukti. Kalau kamu
tidak bisa menuliskan exchange argument untuk sebuah kriteria, kriteria itu
belum layak dipercaya.

### Ringkasan tabel

| Kriteria | Benar? | Contoh tandingan |
|---|---|---|
| **Ujung `r` terkecil** | ✅ | — |
| Awal `l` terkecil | ❌ | `[1,100] [2,3] [4,5]` |
| Panjang terpendek | ❌ | `[1,10] [9,12] [11,20]` |
| Konflik paling sedikit | ❌ | susunan bertingkat di atas |

---

<a name="5"></a>
## 5. Tertutup vs Setengah Terbuka: Penyebab WA Nomor Satu

Perhatikan dua interval: `[1, 5]` dan `[5, 9]`.

**Apakah keduanya bentrok?** Jawabannya bergantung sepenuhnya pada soal.

| Konteks soal | Model | Syarat pada kode |
|---|---|---|
| "Film selesai jam 5, film lain mulai jam 5" | setengah terbuka `[l, r)` | `it.l >= akhir` |
| "Kamu berada di lokasi antara detik 1 dan 5 inklusif" | tertutup `[l, r]` | `it.l > akhir` |
| Interval bilangan bulat, `[1,5]` berarti `{1,2,3,4,5}` | tertutup | `it.l > akhir` |

CSES *Movie Festival* memakai model **setengah terbuka**: film yang selesai pada
menit 5 tidak bertabrakan dengan film yang mulai pada menit 5. Karena itu
sampelnya

```
3
3 5
4 9
5 8
```

berjawaban **2** (`[3,5]` lalu `[5,8]`), bukan 1.

**Cara menghindari jebakan ini:** sebelum menulis kode, jalankan contoh sampel
dengan tangan memakai kedua model. Salah satunya akan cocok. Kalau soalnya tidak
punya sampel yang membedakan keduanya, baca ulang pernyataan soal dengan curiga.

Template hari ini menyediakan bendera eksplisit:

```cpp
int maksSalingLepas(vector<Interval> a, bool bolehSentuh = false);
```

Menuliskannya secara eksplisit lebih baik daripada mengingat-ingat.

---

<a name="6"></a>
## 6. Varian: Minimal Dibuang, Minimal Ruangan

### Varian A — buang sesedikit mungkin

> Berapa interval minimum yang harus dihapus agar sisanya saling lepas?

Ini soal yang **sama persis**, hanya dibalik cara menanyakannya:

```
jawaban = n − maksSalingLepas(a)
```

Jangan menulis algoritma baru. Kenali penyamarannya.

### Varian B — ruangan / mesin minimum

> Semua `n` rapat **harus** dijadwalkan. Berapa ruangan minimum yang dibutuhkan?

Ini **bukan** activity selection — tidak ada yang dibuang. Jawabannya adalah
**tumpang tindih maksimum** pada satu titik waktu.

**Cara 1 — sapuan event** (`O(n log n)`):

```cpp
for (auto& it : a) {
    ev.push_back({it.l, +1});
    ev.push_back({it.r, -1});
}
sort(ev.begin(), ev.end());   // pada waktu sama, -1 diproses lebih dulu
int cur = 0, best = 0;
for (auto& e : ev) { cur += e.second; best = max(best, cur); }
```

Perhatikan bahwa `pair` mengurutkan `{t, -1}` sebelum `{t, +1}` secara otomatis
karena `-1 < +1`. Itu berarti rapat yang selesai pada waktu `t` membebaskan
ruangan sebelum rapat yang mulai pada `t` masuk — model **setengah terbuka**.
Kalau soalmu tertutup, pakai `{it.r + 1, -1}`.

**Cara 2 — heap** (`O(n log n)`), lebih intuitif:

```cpp
sort menurut l;
priority_queue<ll, vector<ll>, greater<ll>> pq;   // waktu selesai
for (auto& it : a) {
    if (!pq.empty() && pq.top() <= it.l) pq.pop();   // satu ruangan bebas
    pq.push(it.r);
}
jawaban = pq.size();
```

Isi heap adalah "ruangan yang sedang terpakai, diurutkan menurut kapan bebas".

**Kenapa hasilnya sama dengan tumpang tindih maksimum?** Batas bawahnya jelas:
kalau ada `k` interval yang saling menindih pada waktu `t`, kamu butuh minimal
`k` ruangan. Algoritma di atas tidak pernah membuka ruangan baru kecuali semua
yang ada terpakai, sehingga jumlah ruangan yang dibuka persis sama dengan
tumpang tindih maksimum. Batas bawah tercapai → optimal.

---

<a name="7"></a>
## 7. Kapan Greedy Berhenti Bekerja: Interval Berbobot

> Setiap interval punya bobot `w_i`. Maksimalkan **total bobot** interval yang
> saling lepas.

**Greedy "ujung terkecil" gagal total:**

```
[1, 10] bobot 100
[1, 2]  bobot 1
[3, 4]  bobot 1
```

Greedy mengambil `[1,2]` lalu `[3,4]` → total **2**. Optimal: `[1,10]` → **100**.

Buktinya rusak di langkah mana? Pada Bagian 3 kita menukar `y` dengan `x` dan
berkata "`|S'| = |S|`". Dengan bobot, `|S'| = |S|` tidak lagi berarti
`bobot(S') = bobot(S)`. Penukarannya bisa memperburuk. Greedy-nya batal.

**Solusinya DP.** Urutkan menurut `r`, lalu:

```
dp[i] = max( dp[i-1],  w[i] + dp[p(i)] )
```

dengan `p(i)` = jumlah interval yang `r`-nya **kurang dari** `l[i]`, dicari
dengan `lower_bound` pada array `r` yang sudah terurut. `O(n log n)`.

```cpp
int p = lower_bound(R.begin(), R.begin() + i, L[i]) - R.begin();
dp[i + 1] = max(dp[i], W[i] + dp[p]);
```

**Sinyal pengenalnya:** begitu soal menyebut bobot, nilai, atau keuntungan per
interval — berhenti berpikir greedy dan mulai berpikir DP. Ini konsisten dengan
tabel sinyal Day 71.

---

<a name="8"></a>
## 8. Ringkasan, Jebakan, dan Latihan Mandiri

### Peta keputusan

```
Soal interval
├── "sebanyak mungkin saling lepas"      -> urut r, greedy
├── "sesedikit mungkin dibuang"          -> n − greedy di atas
├── "semua harus dijadwalkan, berapa
│    ruangan/mesin"                      -> sapuan event atau heap
├── "total bobot maksimum"               -> DP + lower_bound
└── "tutupi seluruh [0, T]"              -> greedy jangkauan (Day 73)
```

### Jebakan

1. **Mengurutkan menurut `l`.** Naluri paling kuat, dan salah. Selalu `r`.
2. **Tertutup vs setengah terbuka.** Tentukan sebelum menulis kode, jangan
   sesudah WA.
3. **`akhir` diinisialisasi 0.** Kalau ada interval dengan `l` bernilai 0 atau
   negatif, ini melewatkan interval pertama. Pakai `LLONG_MIN`.
4. **Menyangka soal berbobot bisa greedy.** Cari kata "bobot"/"nilai"/"harga".
5. **Ruangan minimum dikira activity selection.** Baca apakah interval boleh
   dibuang. Kalau tidak boleh, itu soal berbeda.
6. **Sapuan event dengan urutan salah.** `{r, -1}` harus diproses sebelum
   `{r, +1}` untuk model setengah terbuka. `pair` melakukannya otomatis; kalau
   kamu memakai struct sendiri, periksa komparatormu.

### Kompleksitas

| Masalah | Waktu | Memori |
|---|---|---|
| Activity selection | `O(n log n)` | `O(n)` |
| Minimal dibuang | `O(n log n)` | `O(n)` |
| Ruangan minimum (event) | `O(n log n)` | `O(n)` |
| Ruangan minimum (heap) | `O(n log n)` | `O(n)` |
| Interval berbobot (DP) | `O(n log n)` | `O(n)` |

### Latihan mandiri (di luar berkas latihan)

- Tulis brute force `2^n` untuk `n ≤ 18`, lalu bandingkan greedy-`r`,
  greedy-`l`, dan greedy-panjang pada 10.000 masukan acak. Catat berapa persen
  masing-masing gagal. Angkanya akan membuat kamu tidak pernah lagi memakai
  greedy-`l`.
- Modifikasi soal ruangan minimum: alih-alih jumlah ruangan, cetak **jadwal**
  (ruangan mana untuk rapat mana). Petunjuk: simpan indeks ruangan bersama
  waktu selesai di dalam heap.
