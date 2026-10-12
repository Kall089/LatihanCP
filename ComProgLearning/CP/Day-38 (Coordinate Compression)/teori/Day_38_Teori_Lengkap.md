# 📊 Day 38: Coordinate Compression

> **Prasyarat:** Sorting (Day 20), STL vector & algoritma (Day 18, 25), `lower_bound` (Day 25)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"nilai sampai 10^9 tapi n cuma 10^5"*, *"interval"*, *"peringkat"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 38, kamu akan mampu:

- [ ] Mengenali tanda-tanda soal yang butuh kompresi koordinat dalam 10 detik
- [ ] Menulis idiom baku `sort` + `unique` + `erase` + `lower_bound` tanpa ragu
- [ ] Menjelaskan kenapa `unique` **tidak** menghapus apa pun dengan sendirinya
- [ ] Memilih antara kompresi **membuang duplikat** dan kompresi **peringkat**
- [ ] Menerapkan kompresi pada **interval** dan tahu kenapa `r+1` sering perlu ditambahkan
- [ ] Menggabungkan kompresi dengan **sweep line** untuk masalah interval
- [ ] Melakukan kompresi **dua dimensi**

---

## 🔍 1. Konsep & Intuisi

### Masalah

Banyak algoritma dan struktur data yang cepat memerlukan array yang diindeks oleh
**nilai**, bukan posisi. Misalnya array frekuensi, Fenwick Tree, atau bucket.

```
"berapa kali nilai v muncul?"  ->  cnt[v]++     butuh array sebesar nilai maksimum
```

Kalau `a[i]` bisa mencapai `10^9`, array `cnt` sebesar itu butuh 4 GB — mustahil.

Tapi perhatikan: `n` hanya `10^5`. Artinya **paling banyak 10^5 nilai berbeda** yang
benar-benar muncul. Sisanya adalah 999.900.000 slot kosong yang tidak pernah dipakai.

### Analogi: nomor kursi di bioskop

Bayangkan sebuah bioskop menjual tiket dengan nomor identitas pembeli — 16 digit.
Untuk mendata siapa duduk di mana, kamu **tidak** membuat daftar sepanjang 10^16 baris.
Kamu cukup mengurutkan pembeli yang benar-benar hadir, lalu memberi mereka nomor
kursi 1, 2, 3, ... sesuai urutan.

Kompresi koordinat adalah proses memberi nomor kursi itu.

```
nilai asli   :  1000000000    5    999    5    1000000000
                     ↓        ↓     ↓     ↓         ↓
nilai unik   :  [5, 999, 1000000000]
peringkat    :       0    1        2
                     ↓        ↓     ↓     ↓         ↓
hasil kompresi:      2        0     1     0         2
```

### Sifat yang dipertahankan

Kompresi menjaga **urutan relatif** dan **kesamaan**:

```
a[i] < a[j]  <=>  comp[i] < comp[j]
a[i] == a[j] <=>  comp[i] == comp[j]
```

Yang **hilang** adalah **jarak**:

```
asli   : 5, 999, 1000000000     selisih 994 dan 999999001
kompres: 0, 1,   2              selisih 1 dan 1
```

> **Uji kelayakan:** kalau soalmu hanya peduli *"mana yang lebih besar"* dan
> *"mana yang sama"*, kompresi aman. Kalau soalmu peduli *"berapa selisihnya"*
> atau *"berapa jumlahnya"*, kompresi akan merusak jawabannya — kecuali kamu
> menyimpan nilai aslinya juga dan memakainya saat menghitung.

---

## 🧮 2. Analisis Kompleksitas

| Langkah | Waktu | Ruang |
| ------- | ----- | ----- |
| Salin nilai | O(n) | O(n) |
| Sort | O(n log n) | — |
| `unique` + `erase` | O(n) | — |
| Petakan tiap elemen (`lower_bound`) | O(n log n) | — |
| **Total** | **O(n log n)** | **O(n)** |

Setelah kompresi, nilai berada di rentang `[0, m)` dengan `m ≤ n`, sehingga struktur
data berbasis array menjadi mungkin.

**Perbandingan dengan alternatif:**

| Pendekatan | Waktu | Kapan dipakai |
| ---------- | ----- | ------------- |
| `map<ll, int>` langsung | O(n log n), konstanta besar | prototipe cepat, n kecil |
| `unordered_map` | O(n) rata-rata | cepat, tapi bisa di-hack di Codeforces |
| **Kompresi + array** | **O(n log n) sekali, lalu O(1)** | **saat array diakses berkali-kali** |

Kompresi menang telak ketika struktur datanya diakses **berulang kali** setelahnya
(BIT, segment tree, DP). Biaya `log n` dibayar sekali di awal, bukan setiap akses.

---

## 💻 3. Implementasi C++

### 3.1 Idiom baku (hafalkan)

```cpp
vector<long long> v = a;                    // salinan nilai
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());   // buang duplikat

// petakan setiap elemen ke peringkatnya
for (int i = 0; i < n; i++)
    a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();

// v[x] mengembalikan nilai asli dari peringkat x
```

⚠️ **`unique` tidak menghapus apa pun.** Ia hanya memindahkan elemen unik ke depan dan
mengembalikan iterator ke akhir bagian yang unik. Isi setelah iterator itu **tidak
terdefinisi**. Karena itu `erase` wajib. Menulis `unique(...)` tanpa `erase` adalah
kesalahan pemula yang menghasilkan bug senyap.

⚠️ **`sort` wajib sebelum `unique`.** `unique` hanya membuang duplikat yang
**berdampingan**. Tanpa sort, `[1, 2, 1]` tetap menjadi `[1, 2, 1]`.

### 3.2 Sebagai struct yang bisa dipakai ulang

```cpp
struct Kompres {
    vector<long long> v;

    void tambah(long long x) { v.push_back(x); }

    void bangun() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int idx(long long x) const {            // nilai -> peringkat
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    long long nilai(int i) const { return v[i]; }   // peringkat -> nilai
    int size() const { return v.size(); }
};
```

Pola pakai: kumpulkan **semua** nilai yang akan pernah ditanyakan (termasuk nilai dari
query, bukan hanya dari array!), lalu `bangun()` sekali.

> ⚠️ Jebakan besar: kalau query menanyakan nilai yang **tidak ada** di array, nilai itu
> harus ikut dimasukkan sebelum `bangun()`. Kalau tidak, `idx()` akan mengembalikan
> posisi yang salah. Kumpulkan semuanya dulu, kompres belakangan.

### 3.3 Dua jenis kompresi

**Jenis A — buang duplikat** (nilai sama → peringkat sama):

```
a       = [10, 50, 10, 30]
unik    = [10, 30, 50]
hasil   = [ 0,  2,  0,  1]
```

Dipakai untuk: array frekuensi, BIT, "berapa nilai berbeda".

**Jenis B — peringkat penuh** (setiap posisi dapat peringkat unik, seri dipecah
berdasarkan indeks):

```
a       = [10, 50, 10, 30]
hasil   = [ 0,  3,  1,  2]
```

Dipakai untuk: mengubah array menjadi permutasi, sebagian soal inversion count.

```cpp
// Jenis B
vector<int> urut(n);
iota(urut.begin(), urut.end(), 0);
sort(urut.begin(), urut.end(), [&](int i, int j) {
    if (a[i] != a[j]) return a[i] < a[j];
    return i < j;                            // pemecah seri
});
vector<int> rank_(n);
for (int k = 0; k < n; k++) rank_[urut[k]] = k;
```

Pilih yang mana? Tanyakan: *"apakah dua nilai yang sama harus diperlakukan sebagai
hal yang sama?"* Ya → jenis A. Tidak → jenis B.

### 3.4 Kompresi pada interval — kenapa `r+1` penting

Untuk masalah interval, mengompres hanya titik ujungnya sering **salah**.

```
interval: [1, 5] dan [7, 9]
titik unik: 1, 5, 7, 9  ->  peringkat 0, 1, 2, 3

Setelah kompresi, [0,1] dan [2,3] terlihat BERDAMPINGAN,
padahal aslinya ada celah 6 di antaranya!
```

Solusinya: masukkan juga `r + 1` untuk setiap interval `[l, r]`.

```cpp
for (auto& [l, r] : interval) {
    titik.push_back(l);
    titik.push_back(r + 1);        // <- ini yang menjaga celah tetap terlihat
}
```

Dengan begitu, interval `[l, r]` menjadi setengah terbuka `[idx(l), idx(r+1))`,
dan celah antar interval tetap terwakili oleh setidaknya satu slot.

### 3.5 Sweep line dengan kompresi: total panjang tertutup

```cpp
long long totalTertutup(vector<pair<long long,long long>> iv) {
    sort(iv.begin(), iv.end());
    long long total = 0, akhir = LLONG_MIN;
    for (auto& [l, r] : iv) {
        long long mulai = max(l, akhir + 1);
        if (r >= mulai) total += r - mulai + 1;
        akhir = max(akhir, r);
    }
    return total;
}
```

Menariknya, masalah ini **tidak butuh** kompresi sama sekali — cukup sort.
Ini pengingat penting: kompresi adalah alat untuk **mengindeks array**, bukan
solusi otomatis untuk setiap soal bernilai besar. Kalau kamu tidak butuh array
yang diindeks nilai, kamu mungkin tidak butuh kompresi.

### 3.6 Kompresi dua dimensi

```cpp
Kompres kx, ky;
for (auto& p : titik) { kx.tambah(p.x); ky.tambah(p.y); }
kx.bangun(); ky.bangun();

vector<vector<int>> grid(kx.size(), vector<int>(ky.size(), 0));
for (auto& p : titik) grid[kx.idx(p.x)][ky.idx(p.y)] = 1;
```

Ini mengubah bidang `10^9 × 10^9` menjadi grid paling besar `n × n`.
Untuk `n = 1000`, grid `1000 × 1000` sudah nyaman diproses.

---

## 🔄 4. Trace & Simulasi

### 4.1 Kompresi dasar — `a = [1000000000, 5, 999, 5, 1000000000]`

```
Langkah 1 — salin       : v = [1000000000, 5, 999, 5, 1000000000]
Langkah 2 — sort        : v = [5, 5, 999, 1000000000, 1000000000]
Langkah 3 — unique      : v = [5, 999, 1000000000, ?, ?]
                                                    ↑
                              iterator kembalian menunjuk ke sini
                              (isi setelahnya TIDAK TERDEFINISI)
Langkah 4 — erase       : v = [5, 999, 1000000000]      ukuran 3
```

```
Langkah 5 — petakan (lower_bound):
   a[0] = 1000000000 -> indeks 2
   a[1] = 5          -> indeks 0
   a[2] = 999        -> indeks 1
   a[3] = 5          -> indeks 0
   a[4] = 1000000000 -> indeks 2

hasil = [2, 0, 1, 0, 2]
```

Sekarang `cnt[3]` sudah cukup, alih-alih `cnt[1000000001]`.

### 4.2 Kenapa `unique` tanpa `erase` berbahaya

```
sebelum : [5, 5, 999, 1000000000, 1000000000]     size() = 5
unique  : [5, 999, 1000000000, X, X]              size() TETAP 5
                               ↑
                    isi tak terdefinisi (biasanya sisa lama, tapi tidak dijamin)

Kalau kamu langsung memakai v.size() = 5 dan lower_bound pada seluruh v,
hasilnya bisa benar KADANG-KADANG dan salah di lain waktu -- bug terburuk.
```

### 4.3 Interval tanpa dan dengan `r+1`

```
interval: [1, 5], [7, 9]

TANPA r+1:
   titik unik = [1, 5, 7, 9]
   [1,5] -> [0, 1]
   [7,9] -> [2, 3]
   Kesimpulan salah: slot 1 dan slot 2 bersebelahan, jadi terlihat MENYAMBUNG.

DENGAN r+1:
   titik = {1, 6, 7, 10}  ->  unik = [1, 6, 7, 10]
   [1,5] -> [idx(1), idx(6)) = [0, 1)
   [7,9] -> [idx(7), idx(10)) = [2, 3)
   Sekarang slot 1 (mewakili nilai 6) berada DI ANTARA keduanya,
   sehingga celah tetap terlihat.  ✓
```

### 4.4 Dua jenis kompresi pada `a = [10, 50, 10, 30]`

```
JENIS A (buang duplikat):
   unik = [10, 30, 50]
   hasil = [0, 2, 0, 1]
   -> dua angka 10 mendapat peringkat SAMA

JENIS B (peringkat penuh):
   pasangan (nilai, indeks) terurut:
     (10,0) (10,2) (30,3) (50,1)
   peringkat: indeks 0 -> 0, indeks 2 -> 1, indeks 3 -> 2, indeks 1 -> 3
   hasil = [0, 3, 1, 2]
   -> dua angka 10 mendapat peringkat BERBEDA, dipecah oleh indeks
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "a[i] sampai 10^9, n sampai 10^5" + butuh array frekuensi | kompresi jenis A |
| "hitung inversi" | kompresi + BIT (Day 170) |
| "berapa nilai berbeda di rentang" | kompresi + offline query |
| interval koordinat besar | kompresi dengan `r+1` |
| "titik pada bidang 10^9 × 10^9" | kompresi 2D |
| "ubah array jadi permutasi" | kompresi jenis B |
| "cari nilai ke-k terkecil" | kompresi + BIT / persistent segtree |
| hanya butuh urut dan bandingkan | ❌ mungkin tidak butuh kompresi sama sekali |

### Pattern: kumpulkan dulu, kompres belakangan

Ini pola yang paling sering salah dilakukan:

```cpp
// SALAH: query dikompres dengan kamus yang tidak memuatnya
Kompres k;
for (int x : a) k.tambah(x);
k.bangun();
// ... lalu query menanyakan nilai 42 yang tidak ada di a -> idx(42) salah

// BENAR: kumpulkan SEMUA nilai yang akan pernah muncul, baru bangun
Kompres k;
for (int x : a) k.tambah(x);
for (auto& q : query) k.tambah(q.nilai);
k.bangun();
```

### Pattern: kompresi + offline

Banyak soal query menjadi mudah kalau kamu:

1. Baca **semua** query dulu (offline).
2. Kumpulkan seluruh nilai dari array dan query.
3. Kompres sekali.
4. Proses dengan array/BIT.

Kemampuan membaca semua query di awal adalah "kekuatan super" yang sering dilupakan.
Kalau soal tidak memaksa jawaban langsung (online), pertimbangkan offline.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`unique` tanpa `erase`.** Ukuran vektor tidak berubah, dan isi di belakang
   tidak terdefinisi.

2. **Lupa `sort` sebelum `unique`.** `unique` hanya membuang duplikat berdampingan.

3. **Query dikompres dengan kamus yang tidak memuat nilainya.** `lower_bound` akan
   mengembalikan posisi penyisipan, bukan posisi nilai — dan itu diam-diam salah.

4. **Lupa `r+1` pada masalah interval.** Celah antar interval menghilang.

5. **Kompresi merusak jarak.** Kalau soal menghitung panjang/jumlah, simpan nilai
   aslinya dan pakai `v[peringkat]` saat menghitung, bukan peringkatnya.

6. **`lower_bound` pada vektor yang tidak terurut.** Perilaku tidak terdefinisi.

7. **Memakai kompresi padahal tidak perlu.** Kalau kamu hanya perlu mengurutkan dan
   membandingkan, `sort` saja sudah cukup. Kompresi menambah kode dan risiko.

8. **`int` untuk nilai asli yang mencapai `10^9`.** Muat, tapi jumlahnya tidak.
   Gunakan `long long` untuk nilai dan `int` untuk peringkat.

### Edge cases wajib diuji

```
semua elemen sama         -> setelah kompresi ukuran kamus = 1
n = 1                     -> kamus berisi satu elemen
nilai negatif             -> tidak masalah, sort menanganinya
nilai 0                   -> tidak masalah
nilai duplikat di query   -> pastikan sudah masuk kamus
interval berdampingan [1,5] dan [6,9]  -> uji dengan dan tanpa r+1
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Melihat `1 <= a[i] <= 10^9` dan `n <= 2*10^5` **bersamaan** → hampir pasti kompresi
  atau `map`. Kalau ada BIT/segment tree di soal, pasti kompresi.
- Melihat koordinat besar + interval → kompresi dengan `r+1`.
- Melihat "berapa nilai berbeda" → kompresi.

**Keputusan cepat map vs kompresi:**

| Situasi | Pilih |
| ------- | ----- |
| Struktur diakses sekali-dua kali | `map`, lebih cepat ditulis |
| Struktur diakses `n log n` kali (BIT, segtree) | **kompresi**, jauh lebih cepat |
| Butuh iterasi berurutan atas nilai | **kompresi** (indeks 0..m−1 langsung berurutan) |
| Soal online, nilai baru muncul di tengah jalan | `map` — kompresi butuh semua nilai di awal |

**Simpan struct `Kompres` di template pribadimu.** Empat fungsi pendek, tetapi ia
menghilangkan seluruh kelas bug (lupa `erase`, lupa `sort`, salah `lower_bound`).

**Manajemen waktu:** kompresi seharusnya memakan < 3 menit untuk ditulis. Kalau lebih
lama, kamu belum menghafal idiomnya — dan itu 3 menit yang terbuang di setiap soal.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  COORDINATE COMPRESSION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  IDIOM BAKU (hafalkan)
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());     <- erase WAJIB
    idx = lower_bound(v.begin(), v.end(), x) - v.begin();

  MEMPERTAHANKAN : urutan relatif, kesamaan
  MENGHANCURKAN  : jarak / selisih / jumlah
    -> kalau butuh nilai asli, pakai v[peringkat]

  DUA JENIS
    A. buang duplikat  -> nilai sama dapat peringkat sama  (array frekuensi, BIT)
    B. peringkat penuh -> setiap posisi unik, seri dipecah indeks (jadi permutasi)

  INTERVAL
    masukkan l DAN r+1, lalu pakai setengah terbuka [idx(l), idx(r+1))
    tanpa r+1, celah antar interval MENGHILANG

  KUMPULKAN DULU, KOMPRES BELAKANGAN
    nilai dari query juga harus masuk kamus!

  TIDAK BUTUH KOMPRESI kalau kamu cuma perlu sort + bandingkan
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1144 — Salary Queries](https://cses.fi/problemset/task/1144) | CSES | kompresi + BIT |
| [CSES 1652 — Forest Queries](https://cses.fi/problemset/task/1652) | CSES | (pembanding: tanpa kompresi) |
| [CF 670C — Cinema](https://codeforces.com/problemset/problem/670/C) | Codeforces | kompresi + hitung |
| [CF 1000C — Covered Points Count](https://codeforces.com/problemset/problem/1000/C) | Codeforces | interval + sweep |
| [LeetCode 1893 — Check if All Integers Covered](https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/) | LeetCode | interval kecil |
| [LeetCode 218 — The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/) | LeetCode | sweep + koordinat |
| [AtCoder ABC 213 C — Reorder Cards](https://atcoder.jp/contests/abc213/tasks/abc213_c) | AtCoder | kompresi 2D murni |
| [SPOJ INVCNT](https://www.spoj.com/problems/INVCNT/) | SPOJ | kompresi + inversi |

---

**Selanjutnya:** Day 39 (sudah kamu selesaikan) dan Day 40 — Counting & Frequency Array.
Kompresi hari ini adalah **prasyarat** untuk itu: begitu nilai sudah dikecilkan ke
`[0, m)`, array frekuensi menjadi mungkin, dan array frekuensi adalah salah satu senjata
paling sederhana sekaligus paling sering terpakai di CP.
