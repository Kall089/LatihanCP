# 📊 Day 29: Prefix Sum 1D & Range Sum Query

> **Prasyarat:** Array (Day 7), Kompleksitas (Day 15–16), Overflow (Day 9)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"jumlah dari L sampai R"*, *"banyak query"*, *"subarray dengan jumlah ..."*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 29, kamu akan mampu:

- [ ] Membangun prefix sum dan menjawab range sum dalam **O(1)** per query
- [ ] Memilih konvensi indeks yang **tidak** menimbulkan off-by-one
- [ ] Mengenali kapan prefix sum tidak berlaku (operasi yang tidak punya invers)
- [ ] Memakai **prefix XOR** dan **prefix count** dengan pola pikir yang sama
- [ ] Menghitung **banyak subarray dengan jumlah = K** dalam O(n) memakai map
- [ ] Menghitung **banyak subarray yang habis dibagi K** lewat sisa bagi
- [ ] Memilih tipe data yang benar agar tidak overflow

---

## 🔍 1. Konsep & Intuisi

### Masalah

Diberikan array `a[0..n-1]` dan `q` pertanyaan berupa *"berapa jumlah `a[l] + ... + a[r]`?"*.

Cara naif: loop dari `l` sampai `r` untuk setiap query.

```
n = 10^5, q = 10^5, tiap query menyapu 10^5 elemen
-> 10^10 operasi -> TLE telak (batas aman ~10^8)
```

### Analogi: patokan kilometer di jalan tol

Bayangkan jalan tol dengan patokan kilometer di setiap pintu keluar.
Untuk tahu jarak antara pintu 5 dan pintu 12, kamu **tidak** mengukur ulang jalannya —
kamu cukup mengurangkan dua angka yang sudah tertulis:

```
KM 12  −  KM 5  =  jarak yang dicari
```

Prefix sum adalah patokan kilometer itu. Kita bayar O(n) sekali di awal untuk memasang
patokan, lalu setiap pertanyaan jaraknya gratis.

### Definisi

```
pre[i] = a[0] + a[1] + ... + a[i-1]        (jumlah i elemen PERTAMA)
pre[0] = 0                                  (belum ada elemen)
```

```
a   :     3    1    4    1    5
index:    0    1    2    3    4

pre : 0    3    4    8    9   14
index 0    1    2    3    4    5
      ↑
   selalu 0 — inilah yang menghapus semua off-by-one
```

```
jumlah a[l..r]  =  pre[r+1] − pre[l]
```

Contoh: jumlah `a[1..3]` = `1 + 4 + 1` = 6. Cek rumus: `pre[4] − pre[1]` = `9 − 3` = 6 ✓

> **Kenapa `pre` berukuran `n+1` dan bukan `n`?** Karena `pre[0] = 0` menghilangkan
> percabangan `if (l == 0)`. Percabangan itu adalah sumber bug terbesar di topik ini.
> Bayar satu slot memori, hemat satu jam debugging.

### Syarat agar prefix sum bekerja

Prefix sum bekerja untuk operasi yang punya **invers**:

| Operasi | Punya invers? | Bisa prefix? |
| ------- | ------------- | ------------ |
| `+` | ya (`−`) | ✅ prefix sum |
| `XOR` | ya (XOR sendiri) | ✅ prefix XOR |
| `*` (tanpa nol) | ya (bagi) | ⚠️ hati-hati nol & presisi |
| `min` / `max` | **tidak** | ❌ pakai Sparse Table (Day 169) |
| `gcd` | **tidak** | ❌ pakai Sparse Table / Segment Tree |

Ini pembeda penting: banyak pemula mencoba "prefix min" dan bingung kenapa salah.
Tidak ada cara "mengurangkan" sebuah minimum.

---

## 🧮 2. Analisis Kompleksitas

| Pendekatan | Preprocessing | Per query | Total (n = q = 10^5) |
| ---------- | ------------- | --------- | -------------------- |
| Naif | O(1) | O(n) | 10^10 ❌ |
| **Prefix sum** | **O(n)** | **O(1)** | **2·10^5** ✅ |
| Segment tree | O(n) | O(log n) | 1.7·10^6 (berlebihan di sini) |

**Ruang:** O(n) tambahan. Kalau memori ketat, prefix sum boleh ditulis **di tempat**
(`a[i] += a[i-1]`), tapi kamu kehilangan array asli — biasanya tidak sepadan.

**Kapan prefix sum kalah:** kalau ada **update** di tengah query. Setiap update memaksa
membangun ulang prefix (O(n)). Untuk itu pakai Fenwick Tree (Day 170).

```
hanya query, tanpa update      -> prefix sum
ada update titik + query range -> Fenwick / Segment Tree
ada update range, query di akhir -> difference array (Day 31)
```

---

## 💻 3. Implementasi C++

### 3.1 Bentuk baku

```cpp
int n;
cin >> n;
vector<long long> a(n), pre(n + 1, 0);
for (int i = 0; i < n; i++) cin >> a[i];

for (int i = 0; i < n; i++)
    pre[i + 1] = pre[i] + a[i];        // pre[i+1] = jumlah i+1 elemen pertama

// query (l, r) 0-based inklusif:
long long jawab = pre[r + 1] - pre[l];
```

⚠️ **Tipe data.** `n = 10^5` dan `a[i]` sampai `10^9` menghasilkan jumlah `10^14`.
`int` jebol di `2.1·10^9`. Pakai `long long` untuk `pre`, **selalu**, meski `a[i]` kecil.
Biayanya nol; risikonya WA yang sulit dilacak.

### 3.2 Prefix XOR

```cpp
vector<int> px(n + 1, 0);
for (int i = 0; i < n; i++) px[i + 1] = px[i] ^ a[i];

int xorRange = px[r + 1] ^ px[l];      // XOR adalah inversnya sendiri
```

Tidak ada masalah overflow di sini — XOR tidak pernah membesar.

### 3.3 Prefix count (menghitung, bukan menjumlah)

*Berapa bilangan genap di `a[l..r]`?*

```cpp
vector<int> cnt(n + 1, 0);
for (int i = 0; i < n; i++)
    cnt[i + 1] = cnt[i] + (a[i] % 2 == 0);

int genap = cnt[r + 1] - cnt[l];
```

Pola pikirnya identik: ubah pertanyaan jadi array 0/1, lalu jumlahkan.
Ini adalah trik yang jauh lebih sering berguna daripada prefix sum biasa.

### 3.4 Menghitung subarray dengan jumlah = K

Ini lompatan konseptual hari ini. Perhatikan:

```
jumlah a[l..r] = K
pre[r+1] − pre[l] = K
pre[l] = pre[r+1] − K
```

Jadi untuk setiap ujung kanan `r`, kita cukup bertanya: *"berapa banyak prefix sebelumnya
yang nilainya `pre[r+1] − K`?"* — dan itu satu lookup di `map`.

```cpp
long long hitungSubarraySamaDengan(const vector<long long>& a, long long K) {
    unordered_map<long long, long long> freq;
    freq[0] = 1;                        // prefix kosong; JANGAN LUPA
    long long cur = 0, hasil = 0;

    for (long long v : a) {
        cur += v;
        auto it = freq.find(cur - K);
        if (it != freq.end()) hasil += it->second;
        freq[cur]++;
    }
    return hasil;
}
```

> ⚠️ `freq[0] = 1` mewakili prefix kosong. Tanpa itu, subarray yang **dimulai dari indeks 0**
> tidak akan terhitung. Ini bug nomor satu di soal jenis ini.

**Catatan penting:** teknik ini bekerja untuk bilangan **negatif** juga — berbeda dengan
sliding window (Day 33–34) yang butuh semua elemen non-negatif. Kalau soal mengizinkan
angka negatif, sliding window **tidak** berlaku; prefix + map berlaku.

### 3.5 Subarray yang habis dibagi K

```
jumlah a[l..r] habis dibagi K
(pre[r+1] − pre[l]) % K == 0
pre[r+1] % K == pre[l] % K
```

Jadi: hitung berapa pasang prefix yang **sisa baginya sama**.

```cpp
long long hitungHabisDibagi(const vector<long long>& a, long long K) {
    vector<long long> cnt(K, 0);
    cnt[0] = 1;
    long long cur = 0, hasil = 0;
    for (long long v : a) {
        cur = ((cur + v) % K + K) % K;   // normalisasi sisa NEGATIF
        hasil += cnt[cur];
        cnt[cur]++;
    }
    return hasil;
}
```

⚠️ `((x % K) + K) % K` wajib kalau ada bilangan negatif — di C++, `(-7) % 3` bernilai `-1`,
bukan `2`. Ini jebakan yang sangat sering lolos dari pengujian lokal.

---

## 🔄 4. Trace & Simulasi

### 4.1 Membangun prefix — `a = [3, 1, 4, 1, 5]`

| i | a[i] | pre[i] | operasi | pre[i+1] |
| - | ---- | ------ | ------- | -------- |
| — | — | pre[0] = 0 | inisialisasi | — |
| 0 | 3 | 0 | 0 + 3 | **3** |
| 1 | 1 | 3 | 3 + 1 | **4** |
| 2 | 4 | 4 | 4 + 4 | **8** |
| 3 | 1 | 8 | 8 + 1 | **9** |
| 4 | 5 | 9 | 9 + 5 | **14** |

```
pre = [0, 3, 4, 8, 9, 14]

Query (l=1, r=3): pre[4] − pre[1] = 9 − 3 = 6      -> 1+4+1 = 6   ✓
Query (l=0, r=4): pre[5] − pre[0] = 14 − 0 = 14    -> semuanya    ✓
Query (l=2, r=2): pre[3] − pre[2] = 8 − 4 = 4      -> satu elemen ✓
```

Perhatikan query terakhir: satu elemen tunggal pun bekerja tanpa perlakuan khusus.
Itu hadiah dari `pre[0] = 0`.

### 4.2 Subarray jumlah = 5 pada `a = [1, 2, 3, -1, 2]`

```
freq = {0: 1}, cur = 0, hasil = 0
```

| v | cur | cari `cur − 5` | ada? | hasil | freq setelahnya |
| - | --- | -------------- | ---- | ----- | --------------- |
| 1 | 1 | −4 | tidak | 0 | {0:1, 1:1} |
| 2 | 3 | −2 | tidak | 0 | {0:1, 1:1, 3:1} |
| 3 | 6 | 1 | **ya (1×)** | **1** | {0:1,1:1,3:1,6:1} |
| −1 | 5 | 0 | **ya (1×)** | **2** | {...,5:1} |
| 2 | 7 | 2 | tidak | 2 | {...,7:1} |

```
hasil = 2
Verifikasi manual: [2,3] jumlah 5 ✓   dan  [1,2,3,-1] jumlah 5 ✓
```

Perhatikan langkah ke-4: pasangannya adalah `pre = 0`, yaitu **prefix kosong**.
Tanpa `freq[0] = 1`, subarray `[1,2,3,-1]` akan hilang dari hitungan.

### 4.3 Habis dibagi 3 pada `a = [2, -2, 3]`

```
K = 3, cnt = [1, 0, 0], cur = 0, hasil = 0
```

| v | cur mentah | cur ternormalisasi | cnt[cur] sebelumnya | hasil | cnt setelahnya |
| - | ---------- | ------------------ | ------------------- | ----- | -------------- |
| 2 | 2 | 2 | 0 | 0 | [1,0,1] |
| −2 | 0 | 0 | 1 | **1** | [2,0,1] |
| 3 | 3 → 0 | 0 | 2 | **3** | [3,0,1] |

```
hasil = 3
Verifikasi: [2,-2] = 0 ✓   [3] = 3 ✓   [2,-2,3] = 3 ✓
```

Tanpa normalisasi, langkah ke-2 akan menghasilkan `cur = 0` dengan benar, tapi kalau
`a = [-2, 2]` maka `(-2) % 3 = -1` di C++ dan indeks `cnt[-1]` adalah **out of bounds**.

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "jumlah dari L sampai R", banyak query, tanpa update | prefix sum polos |
| "berapa banyak X di antara L dan R" | prefix count (array 0/1) |
| "XOR dari L sampai R" | prefix XOR |
| "berapa subarray dengan jumlah tepat K" | prefix + map |
| "berapa subarray yang jumlahnya kelipatan K" | prefix + hitung sisa bagi |
| "rata-rata segmen panjang k" | prefix sum, bagi di akhir |
| "seimbangkan kiri dan kanan" | `pre[i] == total − pre[i+1]` |
| "jumlah pada submatriks" | prefix 2D (Day 30) |
| "banyak penambahan rentang, dijawab di akhir" | difference array (Day 31) |
| "ada update di tengah query" | Fenwick Tree (Day 170) |

### Pattern: indeks keseimbangan

*Cari indeks `i` di mana jumlah elemen di kirinya sama dengan jumlah di kanannya.*

```cpp
long long total = pre[n];
for (int i = 0; i < n; i++) {
    long long kiri = pre[i];                 // a[0..i-1]
    long long kanan = total - pre[i + 1];    // a[i+1..n-1]
    if (kiri == kanan) { /* ketemu di i */ }
}
```

### Pattern: jumlah maksimum segmen panjang tepat k

```cpp
long long best = LLONG_MIN;
for (int i = 0; i + k <= n; i++)
    best = max(best, pre[i + k] - pre[i]);
```

Ini sebenarnya sliding window ukuran tetap (Day 33) yang ditulis dengan prefix sum.
Dua cara pandang untuk hal yang sama — pilih yang lebih jelas bagimu.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **`int` untuk prefix sum.** `10^5 × 10^9 = 10^14`. Selalu `long long`.

2. **Off-by-one karena `pre` berukuran `n`.** Pakai ukuran `n+1` dengan `pre[0] = 0`.
   Kalau kamu menemukan diri menulis `if (l == 0)`, konvensimu salah.

3. **Lupa `freq[0] = 1`** pada penghitungan subarray. Subarray yang mulai dari indeks 0 hilang.

4. **Sisa bagi negatif.** `(-7) % 3 == -1` di C++. Normalisasi dengan `((x % K) + K) % K`.

5. **Memakai prefix untuk `min`/`max`/`gcd`.** Tidak bisa — tidak ada inversnya.

6. **Membangun ulang prefix setiap query** karena ada update. Kalau ada update, ganti alat.

7. **Campur 0-based dan 1-based** di tengah kode. Pilih satu di awal, tulis di komentar.

8. **`unordered_map` di-hack.** Di Codeforces, `unordered_map` dengan kunci `long long`
   bisa dijadikan O(n²) oleh tes adversarial. Kalau ragu, pakai `map` (lebih lambat tapi aman)
   atau tambahkan custom hash.

### Edge cases wajib diuji

```
n = 1                       -> query (0,0) harus benar
semua elemen 0              -> subarray jumlah 0 sangat banyak, cek overflow hitungan
semua elemen negatif        -> sliding window gagal, prefix+map tetap benar
K = 0 pada "jumlah = K"     -> banyak jawaban; pastikan tidak infinite loop
l == r                      -> satu elemen
l = 0, r = n−1              -> seluruh array
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Melihat `q` besar dan pertanyaannya *"jumlah L..R"* → tulis prefix sum **sebelum**
  membaca sisa soal. Lima baris, hampir pasti terpakai.
- Melihat *"berapa banyak subarray yang ..."* → pikirkan dua kandidat: prefix+map,
  atau sliding window. Pembedanya: **ada bilangan negatif atau tidak.**
- Melihat kata *"kelipatan"* atau *"habis dibagi"* → sisa bagi prefix.

**Kebiasaan yang menyelamatkan:**

```cpp
vector<long long> pre(n + 1, 0);        // n+1, long long. Selalu.
for (int i = 0; i < n; i++) pre[i+1] = pre[i] + a[i];
```

Tulis dua baris ini secara refleks. Verifikasi sekali dengan query `(0, 0)` dan `(0, n−1)`
sebelum lanjut — dua detik, menghemat submit yang gagal.

**Manajemen waktu:** kalau soal terasa butuh prefix sum tapi rumusnya tidak keluar dalam
5 menit, tulis dulu versi naif O(nq) untuk `n` kecil, cocokkan dengan sample, baru optimalkan.
Naif yang benar adalah alat debugging terbaik.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  PREFIX SUM 1D
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  pre[0] = 0
  pre[i+1] = pre[i] + a[i]              ukuran n+1, tipe long long

  jumlah a[l..r] = pre[r+1] - pre[l]    0-based, inklusif

  VARIAN
    prefix XOR   : px[i+1] = px[i] ^ a[i];  range = px[r+1] ^ px[l]
    prefix count : cnt[i+1] = cnt[i] + (kondisi(a[i]) ? 1 : 0)

  SUBARRAY JUMLAH = K              (boleh negatif)
    freq[0] = 1;                   <- JANGAN LUPA
    cur += v; hasil += freq[cur - K]; freq[cur]++;

  SUBARRAY HABIS DIBAGI K
    cur = ((cur + v) % K + K) % K; <- normalisasi negatif
    hasil += cnt[cur]; cnt[cur]++;

  TIDAK BISA prefix: min, max, gcd (tidak punya invers)
  ADA UPDATE       : Fenwick (Day 170), bukan prefix
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1646 — Static Range Sum Queries](https://cses.fi/problemset/task/1646) | CSES | prefix polos |
| [CSES 1661 — Subarray Sums II](https://cses.fi/problemset/task/1661) | CSES | prefix + map (ada negatif) |
| [CSES 1662 — Subarray Divisibility](https://cses.fi/problemset/task/1662) | CSES | sisa bagi |
| [CSES 1650 — Range XOR Queries](https://cses.fi/problemset/task/1650) | CSES | prefix XOR |
| [LeetCode 560 — Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | LeetCode | prefix + map |
| [LeetCode 724 — Find Pivot Index](https://leetcode.com/problems/find-pivot-index/) | LeetCode | keseimbangan |
| [CF 1352 — Sum of Round Numbers dst.](https://codeforces.com/problemset) | Codeforces | latihan Div3 |
| [AtCoder ABC 122 C — GeT AC](https://atcoder.jp/contests/abc122/tasks/abc122_c) | AtCoder | prefix count |

---

**Selanjutnya:** Day 30 — Prefix Sum 2D. Ide yang sama persis, tapi pengurangannya
melibatkan **empat** sudut alih-alih dua, dan satu bagian ikut terkurang dua kali sehingga
harus dikembalikan (inklusi-eksklusi). Kalau `pre[0] = 0` sudah menjadi refleks bagimu,
versi 2D-nya akan terasa wajar.
