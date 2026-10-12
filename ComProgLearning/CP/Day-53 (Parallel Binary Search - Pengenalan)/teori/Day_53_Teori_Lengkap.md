# 📊 Day 53: Parallel Binary Search (Pengenalan)

> **Prasyarat:** Binary Search on Answer (Day 50), Bound Manual (Day 49), Prefix/Difference Array (Day 29, 31)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"untuk setiap query, kapan pertama kali ..."*, *"waktu paling awal"*, *"query offline"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 53, kamu akan mampu:

- [ ] Mengenali pola *"banyak query, masing-masing butuh binary search"*
- [ ] Menjelaskan kenapa binary search satu per satu **terlalu lambat**
- [ ] Menjalankan **semua** binary search **berbarengan**, satu lapis per putaran
- [ ] Menyusun kerangka baku: `lo[]`, `hi[]`, **bucket** berdasarkan `mid`
- [ ] Menganalisis kompleksitasnya menjadi `O((n + q) log n × biaya)`
- [ ] Mengenali syarat wajibnya: query harus **offline** dan predikat **monoton**
- [ ] Menghindari jebakan **me-reset struktur data** di setiap putaran

---

## 🔍 1. Konsep & Intuisi

### Masalah yang memaksa teknik ini

Bentuk soalnya selalu mirip:

```
Ada N kejadian yang terjadi berurutan (waktu 1, 2, ..., N).
Ada Q pertanyaan. Untuk setiap pertanyaan, cari WAKTU PALING AWAL
di mana suatu kondisi menjadi terpenuhi.
```

Setiap pertanyaan **sendirian** adalah binary search biasa: predikatnya monoton
(kalau kondisi terpenuhi pada waktu `t`, ia juga terpenuhi pada `t+1`).

Tetapi ada masalah: untuk **menguji** predikat pada waktu `t`, kamu harus
**menerapkan** `t` kejadian pertama — dan itu `O(t)`.

```
q pertanyaan × log n langkah × O(n) per pengujian  =  O(q · n log n)

q = n = 10^5  ->  10^5 × 17 × 10^5 = 1.7 × 10^11    MUSTAHIL
```

### Analogi: satu kelas ujian, bukan satu-satu

Bayangkan 1000 murid, masing-masing perlu diuji pada 17 tingkat kesulitan berbeda
untuk mengetahui tingkat mereka. Menyiapkan sebuah ujian butuh waktu lama.

**Cara boros:** untuk setiap murid, siapkan ujian tingkat 1, uji dia, siapkan ujian
tingkat 2, uji dia, ... → 17.000 kali persiapan ujian.

**Cara efisien:** semua murid memulai dengan menebak tingkat 8. Siapkan ujian
tingkat 8 **sekali**, uji **semua** murid sekaligus. Sekarang murid terbagi dua
kelompok, dan masing-masing kelompok punya tebakan berikutnya. Ulangi 17 putaran.

Setiap putaran menyiapkan paling banyak `n` ujian **secara total** — bukan per murid.
Itulah parallel binary search.

### Kerangkanya

```
Setiap query i punya rentang pencarian sendiri [lo[i], hi[i]].

Ulangi log(n) kali:
    1. Untuk tiap query yang belum selesai, hitung mid[i] = (lo[i] + hi[i]) / 2.
    2. KELOMPOKKAN query berdasarkan mid[i]  ->  bucket[mid].push_back(i)
    3. Reset struktur data. Sapu waktu t = 1..n:
         - terapkan kejadian ke-t ke struktur data
         - jawab SELURUH query di bucket[t]  (mereka sedang menguji mid = t)
    4. Perbarui lo[i] atau hi[i] berdasarkan hasilnya.
```

```
Putaran 1:   semua query menguji mid ~ n/2
             sapuan tunggal t=1..n menjawab SEMUANYA

Putaran 2:   query terbagi; sebagian menguji n/4, sebagian 3n/4
             satu sapuan lagi menjawab semuanya

...          log(n) putaran, masing-masing SATU sapuan O(n)
```

> **Inti idenya:** kita menukar *"q sapuan panjang, satu per query"* menjadi
> *"log n sapuan, masing-masing melayani semua query sekaligus"*.

### Syarat wajib

```
1. OFFLINE. Kita harus tahu SEMUA query di awal untuk bisa mengelompokkannya.
   Kalau query harus dijawab satu per satu (online), teknik ini TIDAK berlaku.

2. MONOTON. Predikat setiap query harus monoton terhadap waktu — sekali
   terpenuhi, selamanya terpenuhi. Tanpa itu, binary search-nya sendiri salah.

3. Struktur data harus bisa DIBANGUN ULANG dari nol dengan biaya wajar,
   karena setiap putaran memulai dari keadaan kosong.
```

---

## 🧮 2. Analisis Kompleksitas

Misalkan `C` = biaya menerapkan satu kejadian ke struktur data, dan `Cq` = biaya
menjawab satu query.

| Pendekatan | Kompleksitas | untuk n = q = 10^5 |
| ---------- | ------------ | ------------------ |
| Binary search per query | `O(q · n · C · log n)` | 1.7·10^11 ❌ |
| **Parallel binary search** | `O(log n × (n·C + q·Cq))` | 3.4·10^6 ✅ |
| Segment tree pada waktu | `O((n + q) log² n)` | serupa, lebih rumit |

Turunannya:

```
log(n) putaran
  setiap putaran: sapuan penuh n kejadian    -> n · C
                  menjawab q query           -> q · Cq
total = log(n) · (n·C + q·Cq)
```

Dengan `C = O(log n)` (misalnya BIT) dan `Cq = O(log n)`:

```
17 × (10^5 × 17 + 10^5 × 17) = 17 × 3.4·10^6 = 5.8·10^7    aman
```

⚠️ **Bagian yang sering salah dihitung:** biaya **me-reset** struktur data.
Kalau kamu memakai `memset` pada array `10^6` di setiap putaran, itu
`17 × 10^6 = 1.7·10^7` — masih aman. Tetapi kalau strukturmu berukuran `10^7`,
reset-nya sendiri menjadi bagian terberat. Reset hanya slot yang benar-benar
tersentuh kalau memungkinkan (pola yang sama dengan Day 40).

---

## 💻 3. Implementasi C++

### 3.1 Kerangka baku

```cpp
int n, q;                       // n kejadian, q query
vector<int> lo(q, 1), hi(q, n + 1);   // jawaban di [lo, hi]; n+1 = "tidak pernah"

while (true) {
    // 1. kelompokkan query berdasarkan mid-nya
    vector<vector<int>> bucket(n + 2);
    bool adaYangJalan = false;

    for (int i = 0; i < q; i++)
        if (lo[i] < hi[i]) {
            int mid = lo[i] + (hi[i] - lo[i]) / 2;
            bucket[mid].push_back(i);
            adaYangJalan = true;
        }

    if (!adaYangJalan) break;   // semua query sudah menyempit ke satu titik

    // 2. reset struktur data
    resetStruktur();

    // 3. satu sapuan menjawab SEMUA query
    for (int t = 1; t <= n; t++) {
        terapkanKejadian(t);

        for (int i : bucket[t]) {
            if (cukup(i)) hi[i] = t;        // kondisi sudah terpenuhi di waktu t
            else          lo[i] = t + 1;    // belum, cari lebih ke kanan
        }
    }
}

// lo[i] == n+1 berarti kondisinya tidak pernah terpenuhi
```

⚠️ **Perhatikan bahwa loop `t` berjalan penuh dari 1 sampai n**, meski bucket-nya
kosong di sebagian besar `t`. Itu memang harus — struktur data harus dibangun
secara bertahap agar keadaannya benar saat mencapai `t` yang punya query.

### 3.2 Contoh lengkap: Meteor (pola klasik)

*Ada `n` negara mengelilingi lingkaran dengan `m` sektor. Setiap negara punya target
`p[i]`. Ada `k` hujan meteor; hujan ke-`j` menambahkan `a[j]` unit ke setiap sektor
pada rentang `[l[j], r[j]]` (rentangnya bisa membungkus). Untuk setiap negara, cari
hujan keberapa yang membuat totalnya mencapai target.*

```cpp
// Struktur: BIT untuk range update, point query (Day 170)
long long bit[MAXM];

void tambah(int i, long long v) { for (; i <= m; i += i & -i) bit[i] += v; }
long long baca(int i) { long long s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
void rangeAdd(int l, int r, long long v) {
    if (l <= r) { tambah(l, v); tambah(r + 1, -v); }
    else { tambah(l, v); tambah(m + 1, -v); tambah(1, v); tambah(r + 1, -v); }  // membungkus
}

// ... di dalam sapuan:
for (int t = 1; t <= k; t++) {
    rangeAdd(l[t], r[t], a[t]);
    for (int i : bucket[t]) {
        long long total = 0;
        for (int s : sektor[i]) {          // sektor milik negara i
            total += baca(s);
            if (total >= p[i]) break;      // hentikan lebih awal: cegah overflow
        }
        if (total >= p[i]) hi[i] = t;
        else               lo[i] = t + 1;
    }
}
```

⚠️ Total seluruh `sektor[i]` di seluruh negara adalah `m`, sehingga menjawab
**semua** query dalam satu putaran hanya `O(m log m)` — bukan `O(q · m)`.
Ini penting: biaya menjawab dijamin oleh **total** ukuran data, bukan per query.

### 3.3 Contoh sederhana tanpa struktur data rumit

Kadang struktur datanya hanya array biasa. Berikut pola *"kapan sebuah elemen
mencapai ambang"* dengan difference array (Day 31):

```cpp
// n operasi, masing-masing menambah v ke rentang [l, r]
// q query: untuk posisi p dengan target T, operasi keberapa yang membuatnya >= T?

vector<long long> diff(m + 2);

// dalam sapuan:
resetDiff();
for (int t = 1; t <= n; t++) {
    diff[l[t]] += v[t];
    diff[r[t] + 1] -= v[t];

    if (!bucket[t].empty()) {
        // butuh nilai SEBENARNYA, jadi harus akumulasi -- ini O(m) per bucket
        // -> untuk banyak bucket, pakai BIT alih-alih difference array
    }
}
```

⚠️ Pelajaran dari contoh ini: pilih struktur data yang mendukung **update dan
query secara bergantian**. Difference array cepat untuk update tetapi butuh
`O(m)` untuk membaca satu nilai — tidak cocok. BIT memberi `O(log m)` untuk
keduanya, dan itulah pilihan yang tepat.

### 3.4 Varian: menjawab dalam satu putaran dengan pengurutan

Kalau predikat query hanya bergantung pada **nilai** (bukan struktur), kamu sering
bisa mengurutkan query dan menjawabnya dalam **satu** sapuan — tanpa `log n` putaran:

```cpp
sort(query.begin(), query.end());        // urutkan berdasarkan ambang
int ptr = 0;
for (int t = 1; t <= n; t++) {
    terapkanKejadian(t);
    while (ptr < q && sudahCukup(query[ptr])) {
        jawab[query[ptr].id] = t;
        ptr++;
    }
}
```

Ini `O(n + q)` — jauh lebih baik. **Selalu periksa dulu apakah varian ini berlaku
sebelum menulis parallel binary search.** Ia berlaku kalau ambang batas query
bisa diurutkan dan kondisinya monoton terhadap ambang itu.

---

## 🔄 4. Trace & Simulasi

### 4.1 Contoh kecil

```
n = 8 kejadian. Kejadian ke-t menambah 1 ke seluruh posisi.
q = 3 query, masing-masing bertanya "kapan totalnya mencapai T?"
   query 0: T = 2
   query 1: T = 5
   query 2: T = 7
```

**Keadaan awal:** `lo = [1,1,1]`, `hi = [9,9,9]`

**Putaran 1:**

```
mid[0] = 1 + (9-1)/2 = 5
mid[1] = 5
mid[2] = 5
bucket[5] = {0, 1, 2}

sapuan t = 1..8, total setelah t kejadian = t
  t = 5: total = 5
     query 0 (T=2): 5 >= 2  ya  -> hi[0] = 5
     query 1 (T=5): 5 >= 5  ya  -> hi[1] = 5
     query 2 (T=7): 5 >= 7  tidak -> lo[2] = 6

lo = [1, 1, 6],  hi = [5, 5, 9]
```

Perhatikan: **satu** sapuan menjawab **tiga** query sekaligus.

**Putaran 2:**

```
mid[0] = 1 + (5-1)/2 = 3
mid[1] = 3
mid[2] = 6 + (9-6)/2 = 7
bucket[3] = {0, 1},  bucket[7] = {2}

sapuan t = 1..8
  t = 3: total = 3
     query 0 (T=2): 3 >= 2 ya   -> hi[0] = 3
     query 1 (T=5): 3 >= 5 tidak -> lo[1] = 4
  t = 7: total = 7
     query 2 (T=7): 7 >= 7 ya   -> hi[2] = 7

lo = [1, 4, 6],  hi = [3, 5, 7]
```

**Putaran 3:**

```
mid[0] = 2, mid[1] = 4, mid[2] = 6
bucket[2] = {0}, bucket[4] = {1}, bucket[6] = {2}

  t = 2: total 2 >= 2 ya   -> hi[0] = 2
  t = 4: total 4 >= 5 tidak -> lo[1] = 5
  t = 6: total 6 >= 7 tidak -> lo[2] = 7

lo = [1, 5, 7],  hi = [2, 5, 7]
```

**Putaran 4:**

```
query 1 dan 2 sudah selesai (lo == hi). Hanya query 0 yang jalan.
mid[0] = 1
  t = 1: total 1 >= 2 tidak -> lo[0] = 2

lo = [2, 5, 7] == hi   -> SELESAI
```

```
Jawaban: query 0 -> waktu 2, query 1 -> waktu 5, query 2 -> waktu 7   ✓
Total sapuan: 4 (= log2(8) + 1), bukan 3 × 4 = 12.
```

### 4.2 Kenapa harus reset di setiap putaran

```
Putaran 1 berakhir dengan struktur data memuat SELURUH 8 kejadian.
Putaran 2 dimulai dan langsung menerapkan kejadian 1 lagi.

TANPA reset: struktur memuat kejadian 1..8 DITAMBAH kejadian 1 lagi.
             Total di t=3 menjadi 8+3 = 11, bukan 3.
             Seluruh jawaban salah.
```

Reset adalah bagian wajib dari kerangka, dan **melupakannya menghasilkan bug yang
sangat membingungkan** karena putaran pertama selalu benar.

### 4.3 Perbandingan jumlah operasi

```
Cara naif  : 3 query × 4 langkah binary search × 8 kejadian = 96 operasi
Parallel   : 4 putaran × 8 kejadian                          = 32 operasi

Untuk n = q = 10^5:
Cara naif  : 10^5 × 17 × 10^5 = 1.7 × 10^11    MUSTAHIL
Parallel   : 17 × 10^5        = 1.7 × 10^6     seketika
```

Perbedaannya bukan konstanta — ia menghilangkan satu faktor `q` sepenuhnya.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "untuk setiap query, kapan pertama kali ..." | parallel binary search |
| "waktu paling awal kondisi terpenuhi" | sama |
| "setelah operasi keberapa" | sama |
| ambang query bisa **diurutkan** | **satu sapuan + two pointers** (lebih baik) |
| query harus dijawab **online** | ❌ tidak berlaku; pakai segment tree/persistent |
| "kth smallest dalam rentang" | parallel binary search atas nilai, atau wavelet tree |
| konektivitas seiring waktu | parallel binary search + DSU rollback (Day 191) |

### Pattern: binary search atas NILAI, bukan waktu

Beberapa soal memakai parallel binary search atas **nilai jawaban**, bukan waktu:

```
"untuk setiap query, cari nilai terkecil ke-k pada rentang"
-> binary search atas nilai x untuk setiap query
-> di dalam sapuan, tambahkan elemen bernilai <= x ke BIT
-> hitung berapa yang masuk rentang query
```

Kerangkanya identik; hanya makna "waktu" yang berganti menjadi "nilai terurut".

### Pattern: kombinasi dengan DSU rollback

Soal konektivitas seperti *"kapan simpul u dan v pertama kali terhubung?"*
memakai parallel binary search dengan DSU. Karena setiap putaran harus mulai dari
nol, DSU biasa cukup — tidak perlu rollback. Rollback baru diperlukan untuk
varian yang lebih rumit (Day 191).

### Kapan JANGAN memakai teknik ini

```
1. Query online                      -> mustahil
2. Ambang bisa diurutkan             -> satu sapuan lebih baik (O(n+q))
3. n atau q kecil (<= 1000)          -> naif sudah cukup, jangan menambah risiko
4. Predikat tidak monoton            -> binary search-nya sendiri salah
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Lupa me-reset struktur data.** Putaran pertama benar, sisanya salah —
   membingungkan karena sampel kecil sering hanya butuh satu putaran.

2. **Reset terlalu mahal.** `memset` array besar `log n` kali bisa menjadi bagian
   terberat. Reset hanya yang tersentuh kalau bisa.

3. **Loop `t` tidak berjalan penuh.** Struktur data harus dibangun bertahap;
   melompati `t` yang bucket-nya kosong membuat keadaannya salah.

4. **`hi` diinisialisasi `n` alih-alih `n+1`.** Tanpa slot "tidak pernah terpenuhi",
   query yang tidak punya jawaban akan salah dilaporkan.

5. **Overflow saat mengakumulasi.** Hentikan penjumlahan setelah melewati ambang
   (pola yang sama dengan Day 49 dan 51).

6. **Memakai difference array untuk query titik.** Update cepat tetapi baca `O(m)`.
   Pakai BIT.

7. **Membuat `vector<vector<int>> bucket` di dalam loop putaran.** Alokasi berulang
   bisa mahal; pakai satu array yang di-`clear()`.

8. **Menganggap query bisa online.** Teknik ini **wajib** offline.

### Edge cases wajib diuji

```
query yang kondisinya SUDAH terpenuhi di waktu 1   -> jawaban 1
query yang TIDAK PERNAH terpenuhi                   -> lo == n+1
q = 1                                               -> harus sama dengan binary search biasa
n = 1                                               -> satu putaran saja
semua query identik                                 -> semuanya masuk bucket yang sama
```

---

## 🏆 7. Tips Contest

**Tanda pengenal soal ini:** kalimat *"untuk setiap query, cari waktu/operasi
paling awal ..."* dengan `n` dan `q` keduanya besar. Kalau kamu melihat itu dan
solusi per-query jelas `O(n)`, parallel binary search hampir pasti jawabannya.

**Sebelum menulisnya, periksa dua hal:**

1. **Apakah query-nya online?** Kalau ya, teknik ini mati; cari pendekatan lain.
2. **Bisakah ambangnya diurutkan?** Kalau ya, satu sapuan `O(n + q)` jauh lebih
   sederhana dan lebih cepat.

**Kerangka yang harus kamu hafal** hanya tujuh baris inti:

```cpp
while (adaYangJalan) {
    isiBucket();          // mid[i] -> bucket[mid[i]]
    resetStruktur();      // JANGAN LUPA
    for (t = 1..n) {
        terapkan(t);
        for (i : bucket[t]) perbarui(lo[i], hi[i]);
    }
}
```

**Debugging:** kalau jawabanmu benar untuk `q = 1` tetapi salah untuk `q` besar,
hampir pasti masalah reset. Kalau benar di putaran pertama saja, itu juga reset.

**Waspadai batas waktu:** teknik ini menambahkan faktor `log n` di atas biaya
sapuan. Kalau sapuannya sudah `O(n log n)`, totalnya `O(n log² n)` — hitung ulang
dengan angka sungguhan sebelum menulis.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  PARALLEL BINARY SEARCH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MASALAH: q query, masing-masing butuh binary search, dan setiap
  pengujian predikat berbiaya O(n)  ->  O(q n log n)  MUSTAHIL

  IDE: jalankan SEMUA binary search BERBARENGAN.
       log(n) putaran, masing-masing SATU sapuan yang melayani
       seluruh query sekaligus.

  KERANGKA:
    lo[i] = 1, hi[i] = n + 1        (n+1 = "tidak pernah terpenuhi")
    while (masih ada yang lo < hi) {
        bucket[mid[i]].push_back(i)          kelompokkan
        resetStruktur();                     <- JANGAN LUPA
        for (t = 1..n) {
            terapkanKejadian(t);
            for (i : bucket[t])
                if (cukup(i)) hi[i] = t; else lo[i] = t + 1;
        }
    }

  KOMPLEKSITAS: O(log n * (n*C + q*Cq))
    n = q = 1e5, C = Cq = log n  ->  ~6e7   aman

  SYARAT WAJIB
    1. OFFLINE  (harus tahu semua query di awal)
    2. MONOTON  (sekali terpenuhi, selamanya terpenuhi)
    3. struktur bisa dibangun ulang dengan biaya wajar

  PERIKSA DULU SEBELUM MENULIS
    ambang bisa diurutkan?  -> SATU sapuan + two pointers, O(n+q)  LEBIH BAIK
    query online?           -> teknik ini TIDAK berlaku
    n, q kecil?             -> naif saja

  BUG NOMOR SATU: lupa reset -> putaran pertama benar, sisanya salah
  Pakai BIT (update & query O(log n)), BUKAN difference array
  (update cepat tetapi baca O(m))
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [POI Meteors](https://szkopul.edu.pl/problemset/problem/7JrCYZ7LhEK4nBR5zbAXpcmM/site/) | POI / Codeforces gym | contoh klasik |
| [CF 1000F / 813E](https://codeforces.com/problemset) | Codeforces | query offline |
| [SPOJ MKTHNUM](https://www.spoj.com/problems/MKTHNUM/) | SPOJ | kth pada rentang |
| [CSES 1734 — Distinct Values Queries](https://cses.fi/problemset/task/1734) | CSES | offline + BIT |
| [CF 786C](https://codeforces.com/problemset/problem/786/C) | Codeforces | offline |
| [Codechef — beberapa soal PBS](https://www.codechef.com/) | CodeChef | latihan |
| [AtCoder ABC 179 F / 262 F](https://atcoder.jp/) | AtCoder | offline query |

---

**Selanjutnya:** Day 54 — Meet in the Middle. Teknik yang berbeda dengan semangat
yang sama: memecah masalah yang terlalu besar (`2^40`) menjadi dua bagian yang
masing-masing bisa dikerjakan (`2^20`), lalu menggabungkan hasilnya dengan
pencarian terurut.
