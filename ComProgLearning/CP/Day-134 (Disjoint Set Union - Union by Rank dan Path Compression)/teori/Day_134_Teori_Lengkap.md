# 📊 Day 134: Disjoint Set Union — Union by Rank & Path Compression

> **Prasyarat:** Array (Day 7), Rekursi (Day 57), Graf dasar (Day 113)
> **Estimasi belajar:** 3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"apakah terhubung"*, *"gabungkan dua kelompok"*, *"berapa komponen"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 134, kamu akan mampu:

- [ ] Menulis DSU dari nol dalam **kurang dari satu menit**
- [ ] Menjelaskan kenapa **path compression** dan **union by size** dibutuhkan **keduanya**
- [ ] Menyatakan kompleksitasnya sebagai `O(α(n))` dan tahu artinya secara praktis
- [ ] Melacak **ukuran komponen** dan **banyaknya komponen** tanpa biaya tambahan
- [ ] Menerapkan DSU pada **Kruskal**, **deteksi siklus**, dan **komponen terhubung**
- [ ] Mengenali kapan DSU **tidak** cukup (penghapusan sisi) dan apa gantinya
- [ ] Memahami kenapa **rollback** melarang path compression

---

## 🔍 1. Konsep & Intuisi

### Masalah yang diselesaikan

DSU menjawab dua pertanyaan pada himpunan yang terus digabungkan:

```
find(x)      : x berada di kelompok mana?
unite(a, b)  : gabungkan kelompok a dan kelompok b
```

Kelihatan sederhana, tetapi implementasi naif sangat lambat:

```
menyimpan "warna" tiap elemen, lalu unite = ubah seluruh warna satu kelompok
-> satu unite bisa O(n), total O(n^2)
```

### Analogi: silsilah keluarga

Setiap orang menunjuk ke satu "orang tua". Untuk mengetahui kelompok seseorang,
kamu naik terus sampai menemukan **leluhur tertinggi** — orang yang menunjuk ke
dirinya sendiri. Leluhur itulah identitas kelompoknya.

```
par:  1 -> 3 -> 5 -> 5        find(1) = 5
      2 -> 5                  find(2) = 5
      4 -> 4                  find(4) = 4

Kelompok: {1, 2, 3, 5} dan {4}
```

Menggabungkan dua kelompok cukup membuat satu leluhur menunjuk ke leluhur
lainnya — **satu operasi**, bukan mengubah seluruh anggota.

### Dua optimasi, dan kenapa keduanya dibutuhkan

**Tanpa optimasi apa pun**, rantainya bisa menjadi garis lurus sepanjang `n`:

```
1 -> 2 -> 3 -> 4 -> ... -> n
find(1) menelusuri n langkah  ->  O(n) per operasi
```

**Optimasi 1 — Union by size/rank:** selalu sambungkan pohon yang **lebih kecil**
ke bawah pohon yang lebih besar.

```
Kalau selalu menggabung kecil ke besar, sebuah pohon berketinggian h
harus memuat setidaknya 2^h simpul.
n simpul  ->  tinggi paling besar log2(n).
```

**Optimasi 2 — Path compression:** setelah `find(x)`, sambungkan langsung seluruh
simpul di jalur itu ke akarnya.

```
sebelum:  1 -> 2 -> 3 -> 4        find(1) menelusuri 3 langkah
sesudah:  1 -> 4, 2 -> 4, 3 -> 4  find(1) berikutnya 1 langkah
```

> **Kenapa keduanya?**
> - Hanya union by size: `O(log n)` per operasi — sudah baik, tetapi bukan optimal.
> - Hanya path compression: `O(log n)` amortisasi — juga baik.
> - **Keduanya:** `O(α(n))` amortisasi, praktis konstanta.
>
> Menuliskan keduanya hanya menambah dua baris, jadi tidak ada alasan memilih satu.

### Apa itu α(n)?

`α` adalah **inverse Ackermann function** — tumbuh sangat lambat sehingga untuk
seluruh `n` yang muat di alam semesta, nilainya **≤ 4**.

```
α(n) <= 4 untuk n < 2^2^2^2^16
```

Secara praktis, anggap saja DSU adalah **O(1) per operasi**. Ini salah satu
struktur data dengan rasio kekuatan-terhadap-panjang-kode terbaik di CP:
sepuluh baris, hampir konstanta.

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Naif | + union by size | + path compression | Keduanya |
| ------- | ---- | --------------- | ------------------ | -------- |
| `find` | O(n) | O(log n) | O(log n) amortisasi | **O(α(n))** |
| `unite` | O(n) | O(log n) | O(log n) amortisasi | **O(α(n))** |
| Ruang | O(n) | O(n) | O(n) | O(n) |

**Untuk `n = 10^6` dan `q = 10^6` operasi:** sekitar `4·10^6` langkah — seketika.

**Perbandingan dengan alternatif:**

| Kebutuhan | Alat |
| --------- | ---- |
| Gabung + cek terhubung | **DSU** |
| Gabung + **pisah** | ❌ DSU tidak bisa; pakai LCT atau offline (Day 191) |
| Query terhubung **pada waktu tertentu** | DSU + parallel binary search (Day 53) |
| Jarak antar simpul | ❌ DSU tidak menyimpan struktur; pakai BFS/DFS |
| Komponen pada graf **statis** | DFS/BFS sama cepatnya dan lebih fleksibel |

⚠️ **DSU tidak bisa memisahkan.** Ini keterbatasan yang mendasar, bukan
kekurangan implementasi. Kalau soal menghapus sisi, trik standarnya adalah
**membalik waktu** — penghapusan menjadi penambahan (lihat bagian 5).

---

## 💻 3. Implementasi C++

### 3.1 Bentuk baku (hafalkan ini)

```cpp
struct DSU {
    vector<int> par, sz;
    int komponen;

    DSU(int n) : par(n), sz(n, 1), komponen(n) {
        iota(par.begin(), par.end(), 0);        // par[i] = i
    }

    int find(int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];               // path halving
            x = par[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;               // sudah satu kelompok
        if (sz[a] < sz[b]) swap(a, b);          // union by size
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
        return true;                            // benar-benar menggabungkan
    }

    bool sama(int a, int b) { return find(a) == find(b); }
    int ukuran(int x) { return sz[find(x)]; }
};
```

Sepuluh baris inti. Perhatikan tiga hal yang membuatnya jauh lebih berguna:

1. **`unite` mengembalikan `bool`** — `true` kalau benar-benar menggabungkan.
   Ini yang dipakai Kruskal dan deteksi siklus, jadi gratis dan sering dibutuhkan.
2. **`komponen`** dilacak otomatis — tidak perlu menghitung ulang.
3. **`sz`** memberi ukuran komponen dalam O(α), juga gratis.

### 3.2 Path halving vs path compression rekursif

```cpp
// Versi rekursif -- lebih pendek, tetapi bisa stack overflow untuk n besar
int find(int x) {
    return par[x] == x ? x : par[x] = find(par[x]);
}

// Versi iteratif dengan path halving -- dipakai di template ini
int find(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
    return x;
}
```

**Path halving** menyambungkan setiap simpul ke **kakeknya** alih-alih langsung
ke akar. Kompleksitas amortisasinya **sama** `O(α(n))`, tetapi:

- Tidak rekursif → tidak ada risiko stack overflow untuk `n = 10^6`.
- Satu kali jalan, bukan dua (rekursif turun lalu naik).

⚠️ Untuk `n = 10^6` dengan rantai panjang, versi rekursif bisa menyebabkan
**stack overflow** di beberapa juri. Biasakan versi iteratif.

### 3.3 Union by size vs union by rank

```cpp
// Union by SIZE -- menyimpan banyaknya simpul
if (sz[a] < sz[b]) swap(a, b);
par[b] = a; sz[a] += sz[b];

// Union by RANK -- menyimpan perkiraan tinggi
if (rnk[a] < rnk[b]) swap(a, b);
par[b] = a;
if (rnk[a] == rnk[b]) rnk[a]++;
```

Keduanya memberi jaminan yang sama. **Union by size lebih disukai** karena
`sz` juga memberi **ukuran komponen** secara gratis — informasi yang sering
diminta soal. `rnk` tidak memberi apa-apa selain jaminan kompleksitas.

### 3.4 Kruskal (MST) — penerapan paling klasik

```cpp
long long kruskal(int n, vector<array<long long,3>>& sisi) {   // {bobot, u, v}
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    long long total = 0;
    int dipakai = 0;
    for (auto& [w, u, v] : sisi)
        if (d.unite(u, v)) {                    // nilai kembalian dipakai di sini
            total += w;
            if (++dipakai == n - 1) break;      // MST selesai
        }
    return dipakai == n - 1 ? total : -1;       // -1 = graf tidak terhubung
}
```

Perhatikan bahwa `unite` yang mengembalikan `bool` membuat Kruskal menjadi
lima baris. Tanpa itu kamu harus memanggil `sama()` lebih dulu — dua kali `find`
yang tidak perlu.

### 3.5 Melacak informasi tambahan per komponen

Pola yang sangat sering dipakai: simpan agregat apa pun di **akar** komponen.

```cpp
vector<long long> jumlah;      // total nilai dalam komponen
vector<int> maksimum;          // nilai terbesar dalam komponen

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
    jumlah[a] += jumlah[b];                     // gabungkan agregatnya
    maksimum[a] = max(maksimum[a], maksimum[b]);
    return true;
}
```

⚠️ Agregat **hanya valid di akar**. Selalu baca lewat `jumlah[find(x)]`,
bukan `jumlah[x]`. Ini bug yang sangat sering terjadi.

### 3.6 DSU dengan rollback (pratinjau Day 191)

Beberapa soal butuh **membatalkan** penggabungan. Itu mungkin, tetapi ada harga:

```cpp
struct DSURollback {
    vector<int> par, sz;
    vector<pair<int,int>> riwayat;              // {simpul yang diubah, ukuran lama}

    int find(int x) {                           // TANPA path compression!
        while (par[x] != x) x = par[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        riwayat.push_back({b, sz[a]});
        par[b] = a; sz[a] += sz[b];
        return true;
    }

    void rollback() {
        auto [b, ukuranLama] = riwayat.back(); riwayat.pop_back();
        sz[par[b]] = ukuranLama;
        par[b] = b;
    }
};
```

⚠️ **Path compression harus dibuang.** Ia mengubah struktur pohon secara tidak
terlacak, sehingga pembatalan menjadi mustahil. Akibatnya kompleksitasnya naik
menjadi `O(log n)` — masih baik, tetapi bukan lagi `α(n)`.

Inilah sebabnya di Day 53 (parallel binary search) kita **tidak** butuh rollback:
setiap putaran memulai dari nol, sehingga path compression tetap boleh dipakai.

---

## 🔄 4. Trace & Simulasi

### 4.1 Membangun DSU pada 6 simpul

```
Awal: par = [0,1,2,3,4,5], sz = [1,1,1,1,1,1], komponen = 6
```

| Operasi | find(a) | find(b) | aksi | par setelahnya | komponen |
| ------- | ------- | ------- | ---- | -------------- | -------- |
| unite(0,1) | 0 | 1 | sz sama, 1 → 0 | `[0,0,2,3,4,5]` | 5 |
| unite(2,3) | 2 | 3 | 3 → 2 | `[0,0,2,2,4,5]` | 4 |
| unite(0,2) | 0 (sz 2) | 2 (sz 2) | 2 → 0 | `[0,0,0,2,4,5]` | 3 |
| unite(1,3) | 0 | 0 | **sudah sama** → `false` | tidak berubah | 3 |
| unite(4,5) | 4 | 5 | 5 → 4 | `[0,0,0,2,4,4]` | 2 |

```
Komponen akhir: {0,1,2,3} dan {4,5}
sz[0] = 4, sz[4] = 2
```

Perhatikan `unite(1,3)` mengembalikan `false` — inilah yang dipakai Kruskal untuk
menolak sisi yang membentuk siklus.

### 4.2 Path halving beraksi

```
Andaikan struktur pohonnya (tanpa optimasi) menjadi rantai:
   0 <- 1 <- 2 <- 3 <- 4        (par[4]=3, par[3]=2, par[2]=1, par[1]=0)

find(4) dengan path halving:
   x=4: par[4] = par[par[4]] = par[3] = 2;  x = 2
   x=2: par[2] = par[par[2]] = par[1] = 0;  x = 0
   x=0: par[0] == 0, berhenti

Setelah find(4):
   par[4] = 2, par[2] = 0, par[3] = 2, par[1] = 0
   Rantai memendek dari 4 langkah menjadi 2 langkah.

find(4) berikutnya:
   x=4: par[4] = par[par[4]] = par[2] = 0;  x = 0
   Selesai dalam 1 langkah.
```

Setiap `find` **memperbaiki** struktur untuk pemanggilan berikutnya. Itulah
sebabnya kompleksitasnya **amortisasi** — satu operasi bisa lambat, tetapi
rata-rata sepanjang seluruh program hampir konstanta.

### 4.3 Kenapa union by size penting

```
TANPA union by size, selalu gabung b ke a:
  unite(0,1): 1 -> 0
  unite(1,2): find(1)=0, 2 -> 0        (kebetulan masih datar)

Tetapi kalau urutannya dibalik:
  unite(1,0): 0 -> 1
  unite(2,1): 1 -> 2
  unite(3,2): 2 -> 3
  ...
  Terbentuk RANTAI sepanjang n. find dari ujung = O(n).

DENGAN union by size, pohon yang lebih kecil selalu masuk ke bawah pohon
yang lebih besar, sehingga tingginya tidak pernah melebihi log2(n).
```

Path compression saja sebenarnya sudah cukup untuk `O(log n)` amortisasi,
tetapi kombinasi keduanya memberi `α(n)` — dan biayanya hanya satu baris.

### 4.4 Kruskal pada graf kecil

```
Sisi (bobot, u, v): (1,0,1) (2,2,3) (3,0,2) (4,1,3) (5,0,3)
n = 4, butuh 3 sisi
```

| Sisi | `unite` | hasil | total | dipakai |
| ---- | ------- | ----- | ----- | ------- |
| (1,0,1) | 0≠1 | **ambil** | 1 | 1 |
| (2,2,3) | 2≠3 | **ambil** | 3 | 2 |
| (3,0,2) | 0≠2 | **ambil** | 6 | 3 → selesai |

```
MST = 1 + 2 + 3 = 6, memakai 3 sisi.
Sisi (4,1,3) dan (5,0,3) tidak pernah diperiksa karena kita berhenti lebih awal.
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "apakah u dan v terhubung" | `find(u) == find(v)` |
| "berapa komponen terhubung" | lacak `komponen` di dalam `unite` |
| "berapa anggota komponen u" | `sz[find(u)]` |
| "minimum spanning tree" | Kruskal (sort + DSU) |
| "adakah siklus" | `unite` mengembalikan `false` |
| "berapa sisi minimal agar terhubung" | `komponen − 1` |
| sisi **dihapus** seiring waktu | ❌ balik waktu, atau offline (Day 191) |
| "kapan u dan v terhubung" | DSU + parallel binary search (Day 53) |
| komponen dengan **parity** / relasi | DSU berbobot (Day 135) |

### Pattern: membalik waktu untuk penghapusan

DSU tidak bisa memisahkan. Tetapi kalau soal menghapus sisi satu per satu:

```
Proses MUNDUR: mulai dari keadaan AKHIR (setelah semua penghapusan),
lalu tambahkan kembali sisi-sisi dalam urutan terbalik.
Penghapusan menjadi PENAMBAHAN, dan DSU kembali berlaku.
```

Ini trik yang sangat sering menyelamatkan, dan patut menjadi refleks begitu
kamu melihat "sisi dihapus".

### Pattern: DSU pada grid

Grid `R × C` dipetakan menjadi indeks tunggal `r * C + c`. Setelah itu seluruh
soal komponen pada grid (flood fill, pulau, perkolasi) bisa dikerjakan dengan DSU.

```cpp
auto idx = [&](int r, int c) { return r * C + c; };
```

DSU sering **lebih mudah** daripada BFS/DFS ketika sel-sel diaktifkan satu per satu,
karena kamu tidak perlu menelusuri ulang seluruh grid setiap kali.

### Pattern: DSU untuk "gabungkan interval"

Trik yang elegan: `par[i]` berarti *"posisi kosong pertama mulai dari i"*.

```cpp
int cariKosong(int i) { return i == find(i) ? i : (par[i] = cariKosong(par[i])); }
// setelah memakai posisi p: par[p] = p + 1
```

Berguna untuk soal "tempatkan setiap benda di posisi kosong pertama yang tersedia".

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Membaca `sz[x]` alih-alih `sz[find(x)]`.** Agregat hanya valid di akar.
   Ini bug nomor satu di topik ini.

2. **Lupa `find` sebelum membandingkan.** `par[a] == par[b]` **tidak** berarti
   satu komponen; harus `find(a) == find(b)`.

3. **Inisialisasi terlewat.** `par[i] = i` untuk seluruh `i`. Lupa ini membuat
   seluruh elemen mengira akarnya adalah simpul 0.

4. **1-based vs 0-based.** Kalau simpul dinomori 1..n, alokasikan `n+1` slot.

5. **`find` rekursif pada `n = 10^6`.** Bisa stack overflow. Pakai iteratif.

6. **Path compression bersama rollback.** Tidak boleh — rollback menjadi mustahil.

7. **Mengira DSU bisa memisahkan.** Tidak bisa, dan tidak akan pernah bisa.

8. **Menghitung komponen dengan menyapu seluruh simpul setiap query.**
   `O(n)` per query; lacak di dalam `unite` saja.

### Edge cases wajib diuji

```
n = 1                     -> satu komponen, unite(0,0) mengembalikan false
unite(x, x)               -> harus false, jangan menurunkan `komponen`
seluruh simpul terpisah   -> komponen == n
seluruh simpul tergabung  -> komponen == 1, sz[akar] == n
unite yang sama berkali-kali -> hanya yang pertama mengembalikan true
graf tidak terhubung pada Kruskal -> deteksi lewat `dipakai != n-1`
```

---

## 🏆 7. Tips Contest

**DSU adalah struktur data dengan rasio manfaat terhadap panjang kode terbaik
di seluruh CP.** Sepuluh baris, hampir konstanta, dan muncul di ratusan soal.
Hafalkan sampai bisa ditulis tanpa berpikir.

**Selalu tulis versi lengkapnya**, bukan versi minimal:

```cpp
struct DSU {
    vector<int> par, sz;
    int komponen;
    // find, unite yang mengembalikan bool, sama, ukuran
};
```

Tiga tambahan (`bool` kembalian, `komponen`, `sz`) tidak menambah biaya apa pun
dan sering langsung diminta soal. Menulisnya belakangan saat kontes membuang waktu.

**Red flag → aksi:**

- *"apakah terhubung"*, *"gabungkan"*, *"berapa kelompok"* → DSU, langsung.
- *"minimum spanning tree"* → Kruskal = sort + DSU. Lima baris.
- *"sisi dihapus"* → balik waktu.
- *"kapan terhubung"* → DSU + parallel binary search (Day 53).

**Yang DSU tidak bisa:** jarak, jalur, pemisahan, dan struktur di dalam komponen.
Kalau soal butuh itu, DSU bukan alatnya — pakai BFS/DFS atau LCT.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  DISJOINT SET UNION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  struct DSU {
      vector<int> par, sz;  int komponen;
      DSU(int n): par(n), sz(n,1), komponen(n) { iota(par.begin(),par.end(),0); }

      int find(int x) {                       PATH HALVING, iteratif
          while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
          return x;
      }
      bool unite(int a, int b) {
          a = find(a); b = find(b);
          if (a == b) return false;           <- dipakai Kruskal & deteksi siklus
          if (sz[a] < sz[b]) swap(a, b);      UNION BY SIZE
          par[b] = a; sz[a] += sz[b]; komponen--;
          return true;
      }
  };

  DUA OPTIMASI, KEDUANYA DIBUTUHKAN
    union by size saja      -> O(log n)
    path compression saja   -> O(log n) amortisasi
    KEDUANYA                -> O(alpha(n)), praktis KONSTANTA (alpha <= 4)

  GRATIS DAN SERING DIMINTA
    ukuran komponen : sz[find(x)]     <- find DULU, jangan sz[x]
    banyak komponen : lacak di unite
    ada siklus?     : unite mengembalikan false

  KRUSKAL: sort sisi, lalu unite; berhenti setelah n-1 sisi

  TIDAK BISA MEMISAHKAN
    sisi dihapus -> BALIK WAKTU (hapus jadi tambah)
    butuh online -> Link-Cut Tree
    "kapan terhubung" -> DSU + parallel binary search (Day 53)

  ROLLBACK: buang path compression -> O(log n), bukan alpha(n)
  find rekursif pada n = 1e6 -> risiko STACK OVERFLOW, pakai iteratif
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1676 — Road Construction](https://cses.fi/problemset/task/1676) | CSES | komponen + ukuran maksimum |
| [CSES 1675 — Road Reparation](https://cses.fi/problemset/task/1675) | CSES | Kruskal |
| [CSES 1666 — Building Roads](https://cses.fi/problemset/task/1666) | CSES | komponen |
| [LeetCode 547 — Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | LeetCode | komponen |
| [LeetCode 684 — Redundant Connection](https://leetcode.com/problems/redundant-connection/) | LeetCode | deteksi siklus |
| [LeetCode 721 — Accounts Merge](https://leetcode.com/problems/accounts-merge/) | LeetCode | DSU + map |
| [CF 217A / 445B](https://codeforces.com/problemset) | Codeforces | komponen |
| [SPOJ CHAIN / HERDING](https://www.spoj.com/) | SPOJ | DSU berbobot |
| [UVa 10608 — Friends](https://onlinejudge.org/) | UVa | ukuran komponen terbesar |

---

**Selanjutnya:** Day 135 — DSU Berbobot / DSU dengan Parity, yang menyimpan
**relasi** antara simpul dan akarnya (misalnya "berbeda warna" atau "selisih
nilai"), lalu Day 136–137 — Kruskal dan Prim secara lengkap.

Dan yang lebih dekat: DSU ini adalah prasyarat untuk **tugas 4 dan 6 di Day 53**
(parallel binary search) yang sudah kamu punya — kamu sekarang bisa mengerjakannya.
