# 📊 Day 41: Latihan Terpadu Teknik Array

**Hari**: Day 41 dari 308 Hari Competitive Programming
**Topik**: Memilih dan Menggabungkan Teknik Array (Day 29–40)
**Prerequisites**: Day 29 (prefix sum), 30 (prefix 2D), 31 (difference array), 32 (two pointers), 33–34 (sliding window), 35 (Kadane), 36 (monotonic stack), 37 (monotonic deque), 38 (coordinate compression), 39 (string), 40 (counting)
**Difficulty**: ⭐⭐⭐

**Learning Objectives**:
- Memilih teknik yang tepat dari 12 hari terakhir dalam **kurang dari satu menit**
- Menggabungkan **dua atau lebih** teknik dalam satu soal
- Mengenali **transformasi** yang mengubah soal asing menjadi soal yang sudah dikenal
- Memperkirakan kompleksitas sebelum menulis kode, bukan sesudah TLE

---

## 🔍 1. Konsep & Intuisi

### Hari ini tidak ada algoritma baru

Dua belas hari terakhir memberimu sekitar sepuluh alat. Masalahnya sekarang bukan
"bagaimana cara kerja alat X", tapi **"alat mana yang harus saya ambil?"** — dan itu
keterampilan yang berbeda, yang tidak terlatih hanya dengan mengerjakan soal
per-topik. Saat soal datang dengan label "Day 35", kamu sudah tahu jawabannya
sebelum membaca. Di kontes tidak ada label.

Sebagian besar soal Div2 A–C sebenarnya adalah salah satu dari sepuluh alat ini,
atau gabungan dua di antaranya.

### Benang merah yang menyatukan semuanya

Semua teknik O(n) pada array bekerja dengan prinsip yang sama:

> **Buang informasi yang sudah pasti tidak akan berguna lagi.**

```
Kadane           buang prefix yang jumlahnya negatif
                 (beban negatif merugikan semua kandidat masa depan secara seragam)

Two pointers     buang kandidat kiri yang sudah pasti gagal
                 (kalau [l,r] sudah gagal, [l,r+1] juga gagal -> l tidak perlu diulang)

Monotonic stack  buang kandidat yang tertutupi elemen lebih baik dan lebih dekat

Monotonic deque  buang kandidat yang lebih tua DAN lebih kecil dari yang baru masuk

Sliding window   buang bagian kiri window yang membuat kondisi rusak
```

Kalau kamu bisa menyebutkan "apa yang dibuang dan kenapa aman" untuk sebuah soal,
kamu hampir selalu sudah menemukan tekniknya.

### Sumbu kedua: apa yang kamu KUNCI

Cara pandang kedua yang sama berdayanya. Hampir semua teknik ini adalah cara
mengurangi masalah dua-dimensi (`l` dan `r`) menjadi satu dimensi:

```
            ruang asli: semua pasangan (l, r)  ->  O(n^2)

kunci r, cari l terbaik         -> Kadane, prefix+map, monotonic stack
kunci r, l bergerak monoton     -> two pointers, sliding window
kunci pasangan baris (2D)       -> submatriks maksimum
kunci "jawaban" lalu verifikasi -> binary search on answer (Day 50)
```

Pertanyaan pertama pada soal array yang belum kamu kenali: **"apa yang paling
masuk akal untuk dikunci?"**

---

## 🧮 2. Analisis Kompleksitas

### Tabel keputusan dari batasan `n`

Sebelum memilih teknik, lihat `n`. Ini menyempitkan pilihan secara drastis:

| Batas `n` | Kompleksitas yang muat | Teknik yang mungkin |
|---|---|---|
| `n ≤ 10` | `O(n!)`, `O(2^n · n)` | permutasi, enumerasi subset |
| `n ≤ 20` | `O(2^n)` | bitmask, meet in the middle |
| `n ≤ 500` | `O(n^3)` | DP interval, Floyd–Warshall |
| `n ≤ 5000` | `O(n^2)` | DP 2D, brute force pasangan |
| `n ≤ 10^5` | `O(n log n)` | sorting, binary search, set/map |
| `n ≤ 10^6` | `O(n)` | **semua teknik Day 29–40** |
| `n ≤ 10^9` | `O(log n)` atau `O(1)` | rumus, coordinate compression |

Baris terakhir penting: kalau `n` sampai `10^9` tapi jumlah **kejadian**-nya kecil,
itu sinyal **coordinate compression** (Day 38).

### Biaya masing-masing alat

| Teknik | Waktu | Memori | Prasyarat |
|---|---|---|---|
| Prefix sum 1D | `O(n)` bangun, `O(1)` query | `O(n)` | array statis |
| Prefix sum 2D | `O(RC)` bangun, `O(1)` query | `O(RC)` | matriks statis |
| Difference array | `O(1)` update, `O(n)` finalisasi | `O(n)` | update dulu, query belakangan |
| Two pointers | `O(n)` | `O(1)` | kondisi monoton |
| Sliding window tetap | `O(n)` | `O(1)` | panjang tetap |
| Sliding window variabel | `O(n)` | `O(1)` | kondisi monoton terhadap panjang |
| Kadane | `O(n)` | `O(1)` | tanpa batas panjang |
| Monotonic stack | `O(n)` amortisasi | `O(n)` | cari tetangga terdekat |
| Monotonic deque | `O(n)` amortisasi | `O(k)` | ekstrem pada jendela geser |
| Coordinate compression | `O(n log n)` | `O(n)` | nilai besar, jumlah sedikit |
| Frequency array | `O(n + V)` | `O(V)` | nilai kecil dan rapat |

---

## 💻 3. Implementasi C++

Satu file berisi kerangka semua alat, supaya kamu bisa membandingkan bentuknya
berdampingan. Detail masing-masing sudah dibahas di harinya.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ── 1. PREFIX SUM 1D ─────────────────────────────────────
// sum(l..r) 0-based inklusif = P[r+1] - P[l]
vector<ll> buildPrefix(const vector<ll>& a) {
    vector<ll> P(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); i++) P[i + 1] = P[i] + a[i];
    return P;
}

// ── 2. DIFFERENCE ARRAY ──────────────────────────────────
// tambah v ke rentang [l, r] sebanyak Q kali, baru finalisasi sekali
struct Diff {
    vector<ll> d;
    Diff(int n) : d(n + 1, 0) {}
    void add(int l, int r, ll v) { d[l] += v; d[r + 1] -= v; }
    vector<ll> finish() {
        vector<ll> a(d.size() - 1);
        ll run = 0;
        for (size_t i = 0; i + 1 < d.size(); i++) { run += d[i]; a[i] = run; }
        return a;
    }
};

// ── 3. SLIDING WINDOW VARIABEL ───────────────────────────
// pola umum: perluas kanan, kecilkan kiri selama kondisi rusak
int windowTerpanjang(const vector<int>& a, int batas) {
    int l = 0, best = 0, sum = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > batas) sum -= a[l++];   // <- "buang kiri yang merusak"
        best = max(best, r - l + 1);
    }
    return best;
}

// ── 4. KADANE ────────────────────────────────────────────
ll kadane(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) { cur = max(x, cur + x); best = max(best, cur); }
    return best;
}

// ── 5. MONOTONIC STACK: previous smaller element ─────────
// pse[i] = indeks elemen pertama di KIRI i yang nilainya < a[i], atau -1
vector<int> prevSmaller(const vector<ll>& a) {
    int n = a.size();
    vector<int> pse(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

// ── 6. MONOTONIC DEQUE: maksimum pada jendela ukuran k ───
vector<ll> maxJendela(const vector<ll>& a, int k) {
    deque<int> dq;                 // simpan INDEKS, nilainya menurun
    vector<ll> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();   // kadaluarsa
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();   // tertutupi
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// ── 7. COORDINATE COMPRESSION ────────────────────────────
vector<int> kompres(vector<ll> v) {
    vector<ll> s = v;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    vector<int> res(v.size());
    for (size_t i = 0; i < v.size(); i++)
        res[i] = lower_bound(s.begin(), s.end(), v[i]) - s.begin();
    return res;
}

// ── 8. PREFIX + HASH MAP: hitung subarray dengan sum = k ─
ll hitungSubarraySum(const vector<ll>& a, ll k) {
    unordered_map<ll, ll> cnt;
    cnt[0] = 1;                    // prefix kosong
    ll pre = 0, res = 0;
    for (ll x : a) {
        pre += x;
        auto it = cnt.find(pre - k);
        if (it != cnt.end()) res += it->second;
        cnt[pre]++;
    }
    return res;
}
```

---

## 🔄 4. Trace / Simulasi

### 4.1 Membedakan tiga teknik pada satu array yang sama

`a = [2, -1, 3, -4, 5]`, lalu tiga pertanyaan berbeda.

**Pertanyaan A — "jumlah subarray maksimum"** → Kadane

```
i    a[i]   cur = max(a[i], cur+a[i])   best
0     2     max(2, 0+2)   = 2            2
1    -1     max(-1, 2-1)  = 1            2
2     3     max(3, 1+3)   = 4            4
3    -4     max(-4, 4-4)  = 0            4
4     5     max(5, 0+5)   = 5            5
                                    jawaban = 5
```

**Pertanyaan B — "ada berapa subarray dengan jumlah = 4"** → prefix + map

```
pre  : 0   2   1   4   0   5
       ^ prefix kosong

i=0  pre=2   cari 2-4=-2  -> tidak ada        cnt{0:1, 2:1}
i=1  pre=1   cari 1-4=-3  -> tidak ada        cnt{0:1, 2:1, 1:1}
i=2  pre=4   cari 4-4=0   -> ADA 1 kali  +1   cnt{..., 4:1}
i=3  pre=0   cari 0-4=-4  -> tidak ada        cnt{0:2, ...}
i=4  pre=5   cari 5-4=1   -> ADA 1 kali  +1   cnt{..., 5:1}
                                    jawaban = 2
```
Yaitu `[2,-1,3]` dan `[3,-4,5]`. Perhatikan: Kadane sama sekali tidak bisa
menjawab pertanyaan ini, dan map tidak bisa menjawab pertanyaan A secara efisien.
**Kata "ada berapa" versus "berapa maksimum" mengubah tekniknya total.**

**Pertanyaan C — "maksimum pada setiap jendela ukuran 3"** → monotonic deque

```
i=0  a=2   deque kosong                  -> [0]            (nilai: 2)
i=1  a=-1  a[0]=2 > -1, tidak pop        -> [0,1]          (2, -1)
i=2  a=3   a[1]=-1 <= 3 pop, a[0]=2<=3 pop -> [2]          (3)      keluar: 3
i=3  a=-4  a[2]=3 > -4                   -> [2,3]          (3, -4)  keluar: 3
i=4  a=5   pop 3, pop 2                  -> [4]            (5)      keluar: 5
                                    jawaban = [3, 3, 5]
```

### 4.2 Trace difference array

Array awal `[0,0,0,0,0]`, tiga operasi: `+5` pada `[0,2]`, `+3` pada `[1,4]`,
`-2` pada `[2,3]`.

```
d awal :  [ 0,  0,  0,  0,  0,  0]      (ukuran n+1)

+5 [0,2]: d[0] += 5, d[3] -= 5
          [ 5,  0,  0, -5,  0,  0]
+3 [1,4]: d[1] += 3, d[5] -= 3
          [ 5,  3,  0, -5,  0, -3]
-2 [2,3]: d[2] -= 2, d[4] += 2
          [ 5,  3, -2, -5,  2, -3]

finalisasi (prefix sum berjalan):
  i=0  run = 5              a[0] = 5
  i=1  run = 5+3   = 8      a[1] = 8
  i=2  run = 8-2   = 6      a[2] = 6
  i=3  run = 6-5   = 1      a[3] = 1
  i=4  run = 1+2   = 3      a[4] = 3

hasil : [5, 8, 6, 1, 3]
```

Tiga operasi rentang selesai dalam `O(1)` masing-masing, ditambah satu kali
`O(n)` di akhir. Bandingkan dengan update naif `O(nQ)`.

---

## 📝 5. Variasi & Pattern

### Pohon keputusan besar

```
Soal tentang ARRAY / STRING, target O(n) atau O(n log n)
│
├─ Ada QUERY rentang, arraynya TIDAK berubah?
│   └─ prefix sum (1D / 2D)
│
├─ Ada banyak UPDATE rentang, query BARU di akhir?
│   └─ difference array
│
├─ Ada update DAN query berselang-seling?
│   └─ Fenwick / segment tree  (Day 170+, bukan hari ini)
│
├─ Cari SUBARRAY / SUBSTRING yang memenuhi syarat?
│   ├─ panjang TETAP k          -> sliding window tetap
│   ├─ panjang bebas, syaratnya MONOTON terhadap panjang
│   │                            -> two pointers / window variabel
│   ├─ max/min JUMLAH, tanpa batas panjang, ada negatif
│   │                            -> Kadane
│   ├─ max/min JUMLAH, ADA batas panjang
│   │                            -> prefix + monotonic deque
│   └─ MENGHITUNG banyaknya dengan sum = k / habis dibagi m
│                                -> prefix + hash map
│
├─ Untuk TIAP elemen, cari tetangga terdekat yang lebih besar/kecil?
│   └─ monotonic stack
│
├─ Ekstrem pada jendela yang bergeser?
│   └─ monotonic deque
│
├─ Nilai sampai 10^9 tapi jumlah kejadian sedikit?
│   └─ coordinate compression (+ difference array / sweep)
│
└─ Nilai kecil dan rapat (<= 10^6), butuh hitung frekuensi?
    └─ frequency array / counting
```

### Kombinasi yang sering muncul

Ini yang dilatih hari ini. Soal kontes jarang memakai satu alat saja.

| Kombinasi | Soal khasnya |
|---|---|
| prefix sum + sliding window | rata-rata maksimum pada jendela tetap |
| difference array + counting | "berapa nilai maksimum setelah semua update" |
| prefix sum + hash map | substring seimbang, subarray habis dibagi m |
| sliding window + dua monotonic deque | jendela dengan `max − min ≤ k` |
| monotonic stack + iterasi baris | persegi panjang terbesar di matriks biner |
| coordinate compression + difference array | overlap interval maksimum (sweep line) |
| Kadane + prefix/sufiks | dua subarray terpisah |
| prefix 2D + Kadane | submatriks maksimum |

### Transformasi: mengubah soal asing jadi soal dikenal

| Soal aslinya | Transformasi | Jadi soal apa |
|---|---|---|
| untung jual-beli saham | array selisih `d[i] = p[i] − p[i−1]` | Kadane |
| substring dengan jumlah `a` = jumlah `b` | `+1` untuk 'a', `−1` untuk 'b' | prefix + map |
| subarray dengan rata-rata ≥ `x` | kurangi semua elemen dengan `x` | subarray sum ≥ 0 |
| subarray habis dibagi `m` | prefix **modulo** `m` | prefix + map |
| interval `[l, r]` bernilai besar | kompresi koordinat | difference array |
| matriks biner, cari persegi panjang | tinggi kolom per baris | histogram + monotonic stack |

Baris pertama dan kedua adalah **teknik yang sama**: ubah representasi, lalu
masalahnya menjadi masalah yang sudah kamu bisa. Kalau kamu buntu pada sebuah
soal array, tanyakan **"apa yang bisa saya ubah supaya ini jadi soal prefix sum?"**

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Memakai sliding window pada array yang punya elemen negatif.**
   Window variabel butuh **monotonisitas**: melebarkan window harus selalu
   menaikkan (atau selalu menurunkan) nilai yang dipantau. Dengan elemen negatif
   itu tidak berlaku, dan `while (sum > batas) sum -= a[l++]` jadi tidak valid.
   Ini kesalahan nomor satu di blok ini.

2. **Prefix sum tanpa `long long`.** `2·10^5 × 10^9 = 2·10^14`. `int` jebol.

3. **Off-by-one pada `sum(l..r)`.** Dengan `P` berukuran `n+1` dan `P[0] = 0`,
   rumusnya `P[r+1] − P[l]` untuk indeks 0-based inklusif. Tulis satu kali di
   template, jangan diturunkan ulang tiap soal.

4. **Difference array: lupa `d[r+1] -= v` saat `r = n−1`.** Karena itu `d`
   berukuran `n+1`, bukan `n`.

5. **Monotonic deque menyimpan nilai, bukan indeks.** Kamu tidak bisa membuang
   elemen kadaluarsa kalau tidak tahu posisinya.

6. **`unordered_map` kena anti-hash di Codeforces.** Untuk soal prefix+map,
   pakai `map` atau tambahkan salt acak pada hash. Ini penyebab TLE yang
   membingungkan karena kodemu "sudah O(n)".

7. **Coordinate compression tapi lupa bahwa rentang jadi setengah terbuka.**
   Untuk interval `[l, r)` versus `[l, r]`, kompresi harus konsisten — kalau
   tidak, dua interval yang bersentuhan akan salah dihitung tumpang tindih.

8. **Kombinasi teknik tapi kompleksitasnya dikalikan tanpa disadari.**
   Monotonic stack di dalam loop baris = `O(R · C)`, itu aman. Tapi rebuild
   prefix sum di dalam loop = `O(R · C^2)`, itu TLE. Selalu tanya: apa yang
   dibangun **sekali**, apa yang dibangun **per iterasi**.

### Edge case wajib diuji

```
n = 1                     semua teknik harus tetap benar
semua elemen sama         monotonic stack: <= vs < menentukan duplikat
semua elemen negatif      Kadane, dan semua "max" lain
window k = n              deque tidak boleh membuang apa pun
window k = 1              hasilnya harus array itu sendiri
query l == r              prefix sum harus mengembalikan a[l]
tidak ada jawaban valid   apa yang dicetak? -1? 0? baca soal
```

---

## 🏆 7. Tips Contest

**Urutan membaca soal array (30 detik pertama):**

1. Lihat `n` dan `Q` → tentukan kompleksitas target
2. Cari kata kunci: "berurutan/subarray" · "ada berapa" · "maksimum" ·
   "untuk setiap i" · "setelah semua operasi" · "terdekat"
3. Cek tanda: apakah ada nilai negatif? Ini menyingkirkan sliding window
4. Cek batas panjang: ada? Ini menyingkirkan Kadane

**Red flag yang langsung menunjuk satu teknik:**

| Kalimat | Teknik |
|---|---|
| "setelah semua operasi, cetak arraynya" | difference array |
| "untuk setiap i, cari j terdekat sehingga..." | monotonic stack |
| "untuk setiap jendela ukuran k" | monotonic deque / window tetap |
| "ada berapa pasangan (l, r) sehingga..." | prefix + map |
| "1 ≤ a[i] ≤ 10^9, n ≤ 2·10^5" tapi soal tentang rentang | coordinate compression |
| "semua elemen positif" + "sum ≥ s terpendek" | two pointers |

**Manajemen waktu:** kalau setelah 10 menit kamu belum yakin tekniknya, tulis
solusi `O(n^2)` dulu untuk `n` kecil, jalankan pada contoh, dan **cari polanya**.
Sering kali brute force kecil langsung memperlihatkan struktur jawabannya.
Ini teknik resmi, namanya *generate and test* (Day 67).

**Stress test itu wajib untuk soal gabungan.** Solusi yang menggabungkan dua
teknik punya dua kali lipat permukaan bug. Tulis brute force `O(n^2)`, bandingkan
pada 1000 array acak kecil. Butuh 5 menit, menghemat 40 menit debugging.

---

## 📌 8. Ringkasan

### Key points

- Hari ini bukan tentang alat baru, tapi tentang **memilih** dan **menggabungkan**
- Semua teknik O(n) array = "buang yang sudah pasti tidak berguna"
- Pertanyaan pembuka: **apa yang saya kunci?** dan **apa yang saya buang?**
- Kata "ada berapa" vs "berapa maksimum" mengubah teknik secara total
- Elemen negatif menyingkirkan sliding window; batas panjang menyingkirkan Kadane

### Cheatsheet

```
sum(l..r) = P[r+1] - P[l]                       P berukuran n+1, P[0]=0
diff      : d[l]+=v, d[r+1]-=v, finalisasi prefix sum       d berukuran n+1
window    : perluas r, while(rusak) kecilkan l        butuh MONOTON
kadane    : cur = max(x, cur+x)                       tanpa batas panjang
mono stack: while(!st.empty() && kalah(st.top(), x)) pop; push
mono deque: pop_front yang kadaluarsa, pop_back yang tertutupi, simpan INDEKS
prefix+map: cnt[0]=1; pre+=x; res+=cnt[pre-k]; cnt[pre]++
kompresi  : sort -> unique -> lower_bound

n <= 10^6  -> O(n)          n <= 10^5 -> O(n log n)
n <= 5000  -> O(n^2)        n <= 20   -> O(2^n)
```

### Link soal latihan

| Soal | Platform | Gabungan teknik |
|---|---|---|
| [CSES 1662 — Subarray Divisibility](https://cses.fi/problemset/task/1662) | CSES | prefix mod + map |
| [CSES 1661 — Subarray Sums II](https://cses.fi/problemset/task/1661) | CSES | prefix + map |
| [CSES 1660 — Subarray Sums I](https://cses.fi/problemset/task/1660) | CSES | two pointers |
| [CSES 1141 — Longest Substring](https://cses.fi/problemset/task/2428) | CSES | window + frekuensi |
| [LC 239 — Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | LeetCode | monotonic deque |
| [LC 85 — Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) | LeetCode | mono stack + per baris |
| [LC 1438 — Longest Subarray with Abs Diff ≤ Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) | LeetCode | window + 2 deque |
| [CF 466C — Number of Ways](https://codeforces.com/problemset/problem/466/C) | Codeforces | prefix + counting |
| [CF 1355C — Count Triangles](https://codeforces.com/problemset/problem/1355/C) | Codeforces | two pointers + counting |
