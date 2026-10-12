# 📊 Day 42: REVIEW Teknik Array & String

**Hari**: Day 42 dari 308 Hari Competitive Programming
**Topik**: Konsolidasi dan Diagnosis Diri (Day 29–41)
**Prerequisites**: Day 29–41
**Difficulty**: ⭐⭐⭐

**Learning Objectives**:
- Mengenali teknik dari soal yang **tidak berlabel**
- Mendiagnosis lubang pemahaman sendiri, lalu menambalnya secara terarah
- Menghafal invariant setiap teknik, bukan bentuk kodenya
- Menyatakan siap (atau belum) masuk blok Sorting & Searching

---

## 🔍 1. Konsep & Intuisi

### Hari review bukan hari mengulang

Membaca ulang catatan Day 29–41 terasa produktif tapi hampir tidak berguna:
kamu akan mengenali semuanya dan menyimpulkan "sudah paham". Itu **ilusi
familiaritas** — mengenali sesuatu jauh lebih mudah daripada memproduksinya.

Hari ini dirancang sebaliknya: **produksi dulu, baru diagnosis**. Kamu
mengerjakan set soal campuran tanpa label, mencatat di mana kamu tersendat,
lalu hanya mengulang bagian yang benar-benar bocor.

Kalau kamu hanya punya waktu dua jam hari ini, pakai untuk mengerjakan
latihan — bukan membaca bagian ini.

### Peta besar Day 29–41

Sepuluh alat, dikelompokkan berdasarkan **pertanyaan yang dijawabnya**:

```
┌─ MENJAWAB PERTANYAAN TENTANG RENTANG ────────────────────┐
│  prefix sum 1D    jumlah a[l..r]              Day 29     │
│  prefix sum 2D    jumlah submatriks           Day 30     │
│  difference array banyak update, query akhir  Day 31     │
└──────────────────────────────────────────────────────────┘

┌─ MENCARI SUBARRAY / SUBSTRING TERBAIK ───────────────────┐
│  two pointers     syarat monoton              Day 32     │
│  window tetap     panjang tepat k             Day 33     │
│  window variabel  panjang bebas, syarat monoton Day 34   │
│  Kadane           max/min jumlah, ada negatif Day 35     │
└──────────────────────────────────────────────────────────┘

┌─ MENJAWAB "TETANGGA" DAN "EKSTREM" ──────────────────────┐
│  monotonic stack  tetangga terdekat lebih besar/kecil    │
│                                               Day 36     │
│  monotonic deque  ekstrem pada jendela geser  Day 37     │
└──────────────────────────────────────────────────────────┘

┌─ MENANGANI NILAI DAN FREKUENSI ──────────────────────────┐
│  koordinat        nilai besar, kejadian sedikit Day 38   │
│  string           palindrom, anagram, frekuensi Day 39   │
│  counting         nilai kecil dan rapat        Day 40    │
└──────────────────────────────────────────────────────────┘
```

### Invariant: yang harus kamu hafal, bukan kodenya

Kode bisa diturunkan ulang dalam dua menit **kalau** invariant-nya kamu pegang.
Sebaliknya, hafal kode tanpa invariant akan runtuh begitu soalnya sedikit
berbeda. Ini daftar lengkapnya:

| Teknik | Invariant di awal tiap iterasi |
|---|---|
| Prefix sum | `P[i]` = jumlah `i` elemen pertama |
| Difference array | `d` menyimpan **selisih** dengan tetangga kiri |
| Two pointers | untuk `l` sekarang, semua `l' < l` sudah pasti gagal |
| Window variabel | `[l, r]` adalah window **terpanjang yang valid** berakhir di `r` |
| Kadane | `cur` = jumlah maksimum subarray yang **berakhir di `i`** |
| Monotonic stack | isi stack = kandidat yang **belum tertutupi** |
| Monotonic deque | isi deque = kandidat yang **belum kadaluarsa dan belum tertutupi** |
| Prefix + map | `cnt[v]` = berapa kali nilai prefix `v` sudah muncul |

**Uji diri:** tutup tabel ini, lalu tuliskan kedelapan invariant dari ingatan.
Yang tidak bisa kamu tulis adalah teknik yang belum benar-benar kamu miliki —
apa pun perasaanmu tentangnya.

---

## 🧮 2. Analisis Kompleksitas

### Diagnosis dari gejala TLE

Kalau solusimu TLE, gejalanya menunjukkan penyakitnya:

| Gejala | Kemungkinan penyebab | Perbaikan |
|---|---|---|
| TLE pada `n = 2·10^5`, kodemu terasa `O(n)` | `unordered_map` kena anti-hash | ganti `map` atau kompresi |
| TLE, ada loop di dalam loop baris | rebuild struktur per iterasi | bangun sekali di luar |
| TLE pada soal update rentang | update naif `O(nQ)` | difference array |
| TLE pada soal query rentang | hitung ulang tiap query | prefix sum |
| TLE pada `while` di dalam `for` | benar-benar `O(n^2)`, bukan amortisasi | cek: tiap elemen keluar berapa kali? |
| MLE pada DP 2D | array `n × k` penuh | gulung satu dimensi |

Baris terakhir dari kolom pertama penting: `while` di dalam `for` **tidak
otomatis** `O(n^2)`. Yang menentukan adalah apakah setiap elemen bisa keluar
lebih dari sekali. Pada monotonic stack/deque dan two pointers, tidak bisa —
maka `O(n)`. Pada window yang pointer kirinya bisa **mundur**, bisa — maka
`O(n^2)`.

### Diagnosis dari gejala WA

| Gejala | Kemungkinan penyebab |
|---|---|
| Benar untuk sampel, salah untuk tes besar | overflow `int` |
| Salah hanya saat semua elemen negatif | inisialisasi `best = 0` |
| Salah hanya saat `n = 1` | loop dimulai dari indeks yang salah |
| Meleset persis 1 dari jawaban benar | off-by-one prefix, atau interval tertutup/terbuka |
| Salah hanya saat ada nilai kembar | `<` vs `<=` pada monotonic stack |
| Salah hanya saat ada elemen bernilai 0 | mengira `0` termasuk negatif |
| Salah hanya untuk input dengan negatif | `%` menghasilkan sisa negatif |

Tabel ini layak dipasang di dekat meja. Sebagian besar WA di blok ini adalah
salah satu dari tujuh baris tersebut.

---

## 💻 3. Implementasi C++

Bukan kode baru — ini **kartu ingatan**: bentuk minimal tiap teknik, cukup
untuk memicu ingatan tanpa memberi jawaban.

```cpp
// prefix sum          P[i+1] = P[i] + a[i];  sum(l,r) = P[r+1] - P[l]
// difference          d[l] += v; d[r+1] -= v;  lalu prefix sum
// two pointers        for r: while(!valid) l++;  <- l TIDAK PERNAH mundur
// window tetap        sum += a[r] - a[r-k]
// window variabel     for r: masuk(a[r]); while(rusak) keluar(a[l++]);
// kadane              cur = max(x, cur + x); best = max(best, cur)
// monotonic stack     while(!st.empty() && kalah(st.top(), x)) st.pop(); st.push(i)
// monotonic deque     pop_front kadaluarsa; pop_back tertutupi; push_back(i)
// prefix + map        cnt[0]=1; pre+=x; res+=cnt[pre-k]; cnt[pre]++
// kompresi            sort -> unique -> lower_bound
// sweep tertutup      (L,+1), (R+1,-1)
// sweep setengah      (L,+1), (R,-1)
```

### Kerangka stress test — hafalkan bentuknya

Ini alat paling berharga dari seluruh blok ini, dan yang paling jarang dipakai
pemula. Kerangkanya selalu sama:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cepat(vector<ll> a) { /* solusimu */ return 0; }
ll brute(vector<ll> a) { /* O(n^2) yang jelas benar */ return 0; }

int main() {
    mt19937 rng(12345);
    vector<ll> terkecil;
    for (int iter = 0; iter < 100000; iter++) {
        int n = 1 + rng() % 8;                       // KECIL, supaya terbaca
        vector<ll> a(n);
        for (int i = 0; i < n; i++)
            a[i] = (ll)(rng() % 21) - 10;            // rentang kecil juga
        if (cepat(a) != brute(a))
            if (terkecil.empty() || a.size() < terkecil.size()) terkecil = a;
    }
    if (terkecil.empty()) cout << "lolos semua\n";
    else { for (ll x : terkecil) cout << x << " "; cout << "\n"; }
    return 0;
}
```

Dua keputusan desain yang membuatnya berguna:

1. **`n` dan rentang nilai dibuat kecil** — counterexample dengan 4 elemen
   bisa kamu telusuri dengan tangan; yang 200 elemen tidak.
2. **Simpan yang TERKECIL, bukan yang pertama ditemukan** — counterexample
   pertama biasanya acak dan besar.

Batasnya: stress test hanya menemukan bug **di dalam ruang tesnya**. Bug
overflow, bug performa, dan bug batas `n` besar tidak akan pernah muncul dari
array acak kecil. Untuk itu, baca constraint.

---

## 🔄 4. Trace / Simulasi

### Satu array, enam pertanyaan, enam teknik

`a = [3, 1, 4, 1, 5]`. Perhatikan bagaimana **kalimat pertanyaannya** yang
menentukan teknik, bukan datanya.

| Pertanyaan | Kata kunci penentu | Teknik | Jawaban |
|---|---|---|---|
| jumlah `a[1..3]`, banyak query | "banyak query", array tetap | prefix sum | `6` |
| jumlah subarray maksimum | "maksimum", panjang bebas | Kadane | `14` |
| maksimum tiap jendela ukuran 2 | "tiap jendela ukuran k" | deque / window tetap | `[3,4,4,5]` |
| ada berapa subarray berjumlah 5 | "ada berapa" | prefix + map | `2` |
| untuk tiap `i`, elemen lebih besar terdekat di kanan | "untuk tiap i, terdekat" | monotonic stack | `[4,4,5,5,-1]` |
| subarray terpendek berjumlah ≥ 8 | semua positif, "terpendek ≥" | two pointers | `2` |

Lima dari enam pertanyaan itu punya data yang sama persis. Yang berubah cuma
**satu frasa** di kalimat soalnya. Inilah yang dilatih hari ini.

Verifikasi dua yang paling mudah salah:

```
"ada berapa subarray berjumlah 5"
  prefix : 0, 3, 4, 8, 9, 14
  cari pasangan berselisih 5 : (3,8) dan (4,9)
  -> subarray [1,4] dan [4,1]                        jawaban 2

"untuk tiap i, elemen lebih besar terdekat di kanan"
  i=0 (3) -> 4 di indeks 2
  i=1 (1) -> 4 di indeks 2
  i=2 (4) -> 5 di indeks 4
  i=3 (1) -> 5 di indeks 4
  i=4 (5) -> tidak ada                    -> [4, 4, 5, 5, -1]
```

---

## 📝 5. Variasi & Pattern

### Enam frasa yang paling menentukan

Kalau kamu hanya sanggup menghafal enam hal dari blok ini, hafalkan bahwa
frasa-frasa berikut hampir selalu menunjuk satu teknik:

| Frasa di soal | Menunjuk ke |
|---|---|
| "ada berapa banyak pasangan/subarray" | prefix + map / counting |
| "setelah semua operasi selesai" | difference array |
| "untuk setiap `i`, cari `j` terdekat" | monotonic stack |
| "untuk setiap jendela berukuran `k`" | monotonic deque / window tetap |
| "terpanjang / terpendek yang memenuhi" | window variabel / two pointers |
| "maksimum / minimum jumlah dari suatu segmen" | Kadane |

### Tiga pasangan yang paling sering tertukar

**1. "ada berapa" versus "berapa maksimum"**
Dua pertanyaan yang terdengar mirip, dua teknik yang sama sekali berbeda.
Kadane tidak bisa menghitung banyaknya; `map` tidak bisa mencari maksimum
secara efisien. Baca kata kerjanya sebelum memilih.

**2. Two pointers versus window variabel**
Keduanya memakai dua pointer yang tidak mundur. Bedanya pada apa yang dicari:
two pointers biasanya mencari **pasangan** setelah sorting; window variabel
mencari **rentang berurutan**. Kalau kamu boleh mengurutkan datanya, itu
hampir pasti two pointers, bukan window.

**3. Monotonic stack versus monotonic deque**
Stack menjawab "tetangga terdekat" — pertanyaan tentang **posisi**.
Deque menjawab "ekstrem di jendela" — pertanyaan tentang **nilai**.
Kalau ada kata "berukuran `k`" di soal, hampir pasti deque.

---

## ⚠️ 6. Common Mistakes & Edge Cases

Sepuluh kesalahan terbesar di seluruh blok, diurutkan dari yang paling sering:

1. **`best = 0` padahal jawaban boleh negatif.** Muncul di Kadane, submatriks,
   dan semua varian "maksimum". Selalu tanya: bolehkah kosong?
2. **Sliding window pada data yang punya elemen negatif.** Melebarkan window
   tidak lagi monoton, jadi dasar tekniknya hilang.
3. **`int` untuk jumlah.** `2·10^5 × 10^9 = 2·10^14`.
4. **`unordered_map` di Codeforces.** Anti-hash, TLE.
5. **`%` menghasilkan sisa negatif di C++.** `((x % m) + m) % m`.
6. **Difference array berukuran `n`, bukan `n+1`.**
7. **Interval tertutup vs setengah terbuka.** `R+1` versus `R`.
8. **Deque menyimpan nilai, bukan indeks.**
9. **`<` vs `<=` pada monotonic stack saat ada nilai kembar.** Untuk soal
   *counting*, ini menentukan apakah subarray terhitung dua kali.
10. **Pointer kiri mundur.** Kalau `l` bisa berkurang, kompleksitas amortisasi
    tidak lagi berlaku dan kodenya `O(n^2)`.

### Checklist edge case universal

```
n = 1
semua elemen sama
semua elemen negatif
ada elemen bernilai 0
k = 1  dan  k = n
jawaban tidak ada  -> soal minta cetak apa?
nilai maksimum di ujung kiri, lalu di ujung kanan
```

---

## 🏆 7. Tips Contest

**Protokol 60 detik pertama pada soal array:**

```
1. Lihat n dan Q       -> kompleksitas target
2. Ada negatif?        -> menyingkirkan sliding window
3. Ada batas panjang?  -> menyingkirkan Kadane
4. "ada berapa" atau "maksimum"?
5. Ada update?         -> di tengah atau di akhir saja?
6. Nilai sampai 10^9 tapi kejadiannya sedikit? -> kompresi
```

**Kapan menyerah pada pendekatan cerdas:** kalau setelah 10 menit kamu belum
yakin, tulis `O(n^2)` dulu. Untuk soal Div2 A–B, `O(n^2)` sering justru lolos.
Untuk yang tidak lolos, brute force itu tetap berguna sebagai pembanding
stress test — jadi waktunya tidak terbuang.

**Urutan mengerjakan kontes:** baca SEMUA soal dulu, 5 menit. Kerjakan yang
kamu langsung kenali tekniknya. Soal yang butuh 3 teknik digabung hampir tidak
pernah menjadi soal termudah — jangan terjebak di sana lebih dari 20 menit
saat masih ada soal lain yang belum dibaca.

---

## 📌 8. Ringkasan

### Key points

- Hari review = **produksi dulu, diagnosis kemudian**. Membaca ulang catatan
  memberi ilusi paham.
- Hafalkan **invariant**, bukan kode. Kode bisa diturunkan ulang; invariant tidak.
- Gejala WA dan TLE punya pemetaan yang cukup rapi ke penyebabnya — pakai
  tabel diagnosis di Bagian 2 sebelum menebak-nebak.
- Stress test adalah alat paling berharga dari blok ini. Buat kecil, simpan
  yang terkecil.

### Cheatsheet diagnosis

```
salah saat semua negatif       -> best = 0
salah saat n = 1               -> loop mulai dari indeks salah
meleset persis 1               -> off-by-one / interval tertutup vs terbuka
salah saat ada nilai kembar    -> < vs <= pada monotonic stack
salah saat ada elemen 0        -> mengira 0 itu negatif
salah hanya pada input negatif -> % memberi sisa negatif
benar di sampel, salah di tes besar -> overflow
TLE padahal terasa O(n)        -> unordered_map anti-hash
```

### Kriteria lulus blok ini

Kamu siap masuk Day 43 (Sorting) kalau ketiganya terpenuhi:

- [ ] Bisa menulis kedelapan invariant dari ingatan
- [ ] Menyelesaikan minimal 4 dari 6 latihan hari ini **tanpa** melihat label topik
- [ ] Bisa menyebutkan penyebab paling mungkin untuk setiap baris di
      cheatsheet diagnosis

### Link soal latihan campuran

| Soal | Platform | Teknik (jangan dilihat sebelum mencoba) |
|---|---|---|
| [CSES 1620 — Factory Machines](https://cses.fi/problemset/task/1620) | CSES | ‖ binary search on answer |
| [CSES 1084 — Apartments](https://cses.fi/problemset/task/1084) | CSES | ‖ sorting + two pointers |
| [CSES 1090 — Ferris Wheel](https://cses.fi/problemset/task/1090) | CSES | ‖ sorting + two pointers |
| [CSES 1073 — Towers](https://cses.fi/problemset/task/1073) | CSES | ‖ multiset / greedy |
| [LC 739 — Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | LeetCode | ‖ monotonic stack |
| [LC 904 — Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/) | LeetCode | ‖ window + counting |
| [LC 525 — Contiguous Array](https://leetcode.com/problems/contiguous-array/) | LeetCode | ‖ transformasi + prefix map |
| [CF 279B — Books](https://codeforces.com/problemset/problem/279/B) | Codeforces | ‖ two pointers |
