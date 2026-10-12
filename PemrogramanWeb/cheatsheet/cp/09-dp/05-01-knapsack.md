# 05 — 0-1 knapsack

[← Coin unbounded](04-coin-unbounded.md) · [← 09-dp](README.md) · [Subset sum →](06-subset-sum.md)

Day ComprogLearning: **145**. Tiap barang paling banyak sekali. Loop kapasitas 1D **mundur**. Rekonstruksi memakai perbandingan baris atau jejak `prev`.

> **Ide satu kalimat:** `dp[i][c] = max(lewati, ambil dari baris sebelumnya)`; versi 1D mundur agar `dp[c-w]` masih milik barang lama.

## Daftar isi

- [Masalah dan greedy rasio](#masalah-dan-greedy-rasio)
- [Tabel dua dimensi](#tabel-dua-dimensi)
- [Versi 1D loop mundur](#versi-1d-loop-mundur)
- [Rekonstruksi barang](#rekonstruksi-barang)
- [DP atas nilai](#dp-atas-nilai)
- [Kapan ganti model](#kapan-ganti-model)
- [Stress lawan naif](#stress-lawan-naif)

---

## Masalah dan greedy rasio

**Teori:** Ada `n` barang. Barang `i` punya berat `w[i]` dan nilai `v[i]`. Tas berkapasitas `W`. Setiap barang diambil atau tidak, tidak boleh dipotong, tidak boleh diulang. Maksimalkan nilai. Greedy rasio `v/w` benar untuk knapsack pecahan, salah untuk 0-1. Contoh: `W = 10`, A(6,7), B(5,5), C(5,5). Rasio mengambil A nilai 7, sisa 4 kosong. Optimal B+C = 10. Greedy gagal karena A mengunci kapasitas. Tidak ada urutan greedy yang benar untuk 0-1 umum. Hitung `n * W` sebelum menulis DP: `W = 1e18` bukan soal kapasitas 1D.

**Kapan:** pilih subset, `n * W ≤ 1e8`. **Tidak:** `W` raksasa nilai kecil (DP atas nilai), `n ≤ 40` dan `W` besar (meet in the middle), barang boleh diulang (file 04).

**STATE:** `dp[i][c]` adalah nilai maksimum memakai subset dari `i` barang pertama dengan total berat paling banyak `c`.

**TRANSISI:** `dp[i][c] = max(dp[i-1][c], dp[i-1][c-w[i-1]] + v[i-1])` jika `c >= w[i-1]`, selain itu hanya opsi lewati.

**BASIS:** `dp[0][c] = 0` untuk semua `c`. Tanpa barang, nilai nol.

**Proses:** counterexample greedy.

```
W=10
A  w=6 v=7  rasio 1.17
B  w=5 v=5  rasio 1.00
C  w=5 v=5  rasio 1.00

Greedy rasio: A, sisa 4, diam, nilai 7
Optimal:      B+C, berat 10, nilai 10
```

Enumerasi 2^3:

```
mask   barang     berat  nilai  sah?
000    —          0      0      ya
001    A          6      7      ya
010    B          5      5      ya
011    A B        11     12     tidak
100    C          5      5      ya
101    A C        11     12     tidak
110    B C        10     10     ya  <- terbaik
111    A B C      16     17     tidak
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsackNaif(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll bw = 0, bv = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                bw += w[i];
                bv += v[i];
            }
        if (bw <= W) best = max(best, bv);
    }
    return best;
}

int main() {
    FASTIO;
    vector<int> w = {6, 5, 5};
    vector<ll> v = {7, 5, 5};
    cout << knapsackNaif(w, v, 10) << "\n"; // 10
    return 0;
}
```

**Jebakan:** mengambil rasio lalu "kalau sisa muat barang berikutnya". Itu tetap greedy. `n > 20` pada naif TLE.

**Kompleksitas:** naif `O(2^n n)`. DP berikutnya `O(n W)`.

---

## Tabel dua dimensi

**Teori:** Tabel `dp[i][c]` paling jujur untuk pemahaman dan rekonstruksi. Setiap sel hanya membaca baris di atasnya: tepat di atas (lewati) atau geser kiri sejauh `w` (ambil). Karena itu, seluruh baris `i` bisa dihitung setelah baris `i-1` final. Off-by-one klasik: tabel 1-based untuk barang, array `w` 0-based, jadi barang ke-`i` memakai `w[i-1]`. Memori `n * W` int pada `n = 100`, `W = 1e5` adalah 40 MB — sering terlalu besar. Untuk nilai saja, gulung ke 1D. Untuk rekonstruksi mudah, tahan 2D jika muat.

**Kapan:** `n * W` muat memori dan kita ingin jejak barang. **Tidak:** `W = 1e6`, `n = 500` pada 2D.

**STATE:** `dp[i][c]` adalah nilai maksimum dari subset barang `0..i-1` dengan berat total paling banyak `c`.

**TRANSISI:** lewati `dp[i][c] = dp[i-1][c]`; ambil jika `c >= w[i-1]` maka kandidat `dp[i-1][c-w[i-1]] + v[i-1]`.

**BASIS:** baris `i = 0` seluruhnya 0.

**Proses:** barang `(3,3), (2,4), (4,2)`, `W = 5`.

```
       c=0  1  2  3  4  5
i=0     0   0  0  0  0  0
i=1     0   0  0  3  3  3     +(3,3)
i=2     0   0  4  4  4  7     +(2,4)  sel 5 = 3+4
i=3     0   0  4  4  4  7     +(4,2)  tidak memperbaiki
```

Rinci sel `i=2, c=5`:

```
lewati = dp[1][5] = 3
ambil  = dp[1][5-2] + 4 = 3+4 = 7
max = 7
```

Rinci sel `i=3, c=5`:

```
lewati = 7
ambil  = dp[2][1] + 2 = 0+2 = 2
max = 7
```

Jawaban `dp[3][5] = 7`: barang 0 dan 1, berat 5, nilai 7.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<ll>> knapsackTabel(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];
            if (c >= w[i - 1])
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }
    return dp;
}

ll knapsack2D(const vector<int>& w, const vector<ll>& v, int W) {
    auto dp = knapsackTabel(w, v, W);
    return dp[(int)w.size()][W];
}

int main() {
    FASTIO;
    vector<int> w = {3, 2, 4};
    vector<ll> v = {3, 4, 2};
    cout << knapsack2D(w, v, 5) << "\n"; // 7
    return 0;
}
```

**Jebakan:** `w[i]` padahal loop `i` 1-based. Membaca `dp[i][c-w]` dari baris yang sama — itu unbounded.

**Kompleksitas:** `O(n W)` waktu dan memori.

---

## Versi 1D loop mundur

**Teori:** Karena sel hanya butuh baris sebelumnya, satu array cukup. Loop kapasitas **mundur** dari `W` ke `w[i]`. Saat `c` diisi, `dp[c-w]` belum tersentuh barang `i`, jadi masih nilai lama. Loop maju pada barang yang sama membuat `dp[c-w]` sudah berisi barang `i`, lalu barang itu masuk dua kali. Itulah satu-satunya perbedaan karakter antara file 04 dan file ini. Uji wajib: satu barang `(2,3)`, `W = 6`. Mundur harus 3. Maju memberi 9.

**Kapan:** default kontes untuk nilai saja. **Tidak:** butuh rekonstruksi tanpa menyimpan jejak lain.

**STATE:** setelah barang `0..i` selesai, `dp[c]` adalah nilai maksimum kapasitas paling banyak `c` memakai subset dari barang-barang itu, tiap barang sekali.

**TRANSISI:** `dp[c] = max(dp[c], dp[c-w[i]] + v[i])` dengan `c` mundur.

**BASIS:** seluruh `dp[c] = 0` sebelum barang pertama.

**Proses:** barang `(2,3), (3,4), (4,5)`, `W = 6`.

```
awal        [0 0 0 0 0 0 0]

+(2,3) mundur c=6..2
c=6: max(0, dp[4]+3)=3
c=5: 3
c=4: 3
c=3: 3
c=2: 3
setelah     [0 0 3 3 3 3 3]

+(3,4) mundur
c=6: max(3, 3+4)=7
c=5: max(3, 3+4)=7
c=4: max(3, 0+4)=4
c=3: max(3, 0+4)=4
setelah     [0 0 3 4 4 7 7]

+(4,5) mundur
c=6: max(7, 3+5)=8
c=5: max(7, 3+5)=8
c=4: max(4, 0+5)=5
setelah     [0 0 3 4 5 8 8]
```

Jawaban 8: barang 0 dan 2 (berat 6, nilai 8) mengalahkan 0+1 = 7.

Kalau barang ketiga di-loop **maju**, pada contoh ini kebetulan masih 8. Bahaya muncul pada barang kecil: maju pada `(2,3)` sendirian sudah 9.

Jejak mundur satu barang `(2,3)` `W=6`:

```
c=6 baca dp[4]=0 -> 3
c=4 baca dp[2]=0 -> 3
c=2 baca dp[0]=0 -> 3
tidak ada rantai 3,6,9
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsack01(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsack01({3, 2, 4}, {3, 4, 2}, 5) << "\n"; // 7
    cout << knapsack01({2, 3, 4}, {3, 4, 5}, 6) << "\n"; // 8
    cout << knapsack01({2}, {3}, 6) << "\n";             // 3
    return 0;
}
```

**Jebakan:** `for (int c = w[i]; c <= W; c++)` pada 0-1. Overflow `v` pakai `int` saat `n * max v` besar.

**Kompleksitas:** `O(n W)` waktu, `O(W)` memori.

---

## Rekonstruksi barang

**Teori:** Soal sering minta indeks barang, bukan hanya nilai. Pada tabel 2D, mulai dari `i = n`, `c = W`. Jika `dp[i][c] != dp[i-1][c]`, barang `i-1` diambil dan `c -= w[i-1]`. Jika sama, dilewati. Jangan membandingkan `dp[i][c]` dengan `dp[i][c-w]` — itu baris yang salah. Pada 1D murni, riwayat hilang. Simpan `prev` 2D `n * W` karakter (ambil atau tidak), atau tahan tabel nilai 2D. Rekonstruksi tidak unik jika ada dua subset sama nilainya; perbandingan `!=` mengambil salah satu.

**Kapan:** output "barang mana". **Tidak:** mengira 1D otomatis bisa ditelusuri mundur tanpa jejak.

**STATE:** `dp[i][c]` seperti biasa. `ambil[i][c]` bernilai benar jika transisi optimal di `(i, c)` memakai barang `i-1`.

**TRANSISI:** saat kandidat ambil menang, tulis jejak ambil; saat lewati menang atau seri, tulis lewati (seri = tidak wajib ambil).

**BASIS:** baris 0 tidak punya jejak barang.

**Proses:** tabel Day 145, `W = 5`, jawaban 7.

```
i=3 c=5  dp[3][5]=7 == dp[2][5]=7  -> barang 2 tidak
i=2 c=5  dp[2][5]=7 != dp[1][5]=3  -> barang 1 diambil, c=3
i=1 c=3  dp[1][3]=3 != dp[0][3]=0  -> barang 0 diambil, c=0
i=0 selesai
indeks: 0, 1  (berat 3+2, nilai 3+4)
```

Contoh seri: jika barang 2 juga bernilai 0, `==` tetap menolaknya. Itu sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<ll>> knapsackTabel(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];
            if (c >= w[i - 1])
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }
    return dp;
}

vector<int> knapsackPilih(const vector<int>& w, int W, const vector<vector<ll>>& dp) {
    vector<int> dipilih;
    int c = W;
    for (int i = (int)w.size(); i >= 1; i--)
        if (dp[i][c] != dp[i - 1][c]) {
            dipilih.push_back(i - 1);
            c -= w[i - 1];
        }
    reverse(dipilih.begin(), dipilih.end());
    return dipilih;
}

int main() {
    FASTIO;
    vector<int> w = {3, 2, 4};
    vector<ll> v = {3, 4, 2};
    auto dp = knapsackTabel(w, v, 5);
    cout << dp[3][5] << "\n";
    for (int i : knapsackPilih(w, 5, dp)) cout << i << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** membandingkan dengan `dp[i][c-w]`. Lupa `c -= w` setelah mengambil. Mencetak 1-based tanpa menyebutkan konvensi.

**Kompleksitas:** isi `O(n W)`, telusur `O(n)`.

---

## DP atas nilai

**Teori:** Kadang `W` sampai `1e18` tetapi jumlah nilai `Σv` kecil, misalnya `n = 100`, `v[i] ≤ 1000`. Balik peran: `dp[val]` = berat minimum untuk meraih nilai tepat `val`. Inisialisasi `INF`, `dp[0] = 0`. Loop mundur pada `val`. Jawaban adalah `val` terbesar dengan `dp[val] <= W`. Ini masih 0-1. Jangan maju. `ll` untuk berat.

**Kapan:** `n * Σv ≤ 1e8` dan `W` terlalu besar untuk indeks. **Tidak:** `Σv` juga raksasa — itu MITM atau struktur lain.

**STATE:** `dp[val]` adalah berat minimum subset yang jumlah nilainya tepat `val`, atau `INF` jika belum ada.

**TRANSISI:** `dp[val] = min(dp[val], dp[val-v[i]] + w[i])` mundur.

**BASIS:** `dp[0] = 0`.

**Proses:** barang `(6,7), (5,5), (5,5)`, `W = 10`, `Σv = 17`.

```
awal dp[0]=0, lain INF

+(6,7)  dp[7]=6
+(5,5)  dp[5]=5, dp[12]=6+5=11
+(5,5)  dp[5] tetap 5
        dp[10]=5+5=10
        dp[12] tetap 11
        dp[17]=11+5=16
```

`val` dari 17 turun, yang `dp[val] <= 10` pertama adalah `val = 10` dengan berat 10. Cocok dengan B+C.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll knapsackAtasNilai(const vector<int>& w, const vector<ll>& v, ll W) {
    ll totalV = accumulate(v.begin(), v.end(), 0LL);
    vector<ll> dp(totalV + 1, INF);
    dp[0] = 0;
    for (size_t i = 0; i < w.size(); i++)
        for (ll val = totalV; val >= v[i]; val--)
            if (dp[val - v[i]] != INF)
                dp[val] = min(dp[val], dp[val - v[i]] + w[i]);
    for (ll val = totalV; val >= 0; val--)
        if (dp[val] <= W) return val;
    return 0;
}

int main() {
    FASTIO;
    cout << knapsackAtasNilai({6, 5, 5}, {7, 5, 5}, 10) << "\n"; // 10
    return 0;
}
```

**Jebakan:** loop maju pada nilai. Membandingkan `dp[val] < W` padahal kapasitas `<= W`. `int` untuk `W = 1e18`.

**Kompleksitas:** `O(n Σv)` waktu, `O(Σv)` memori.

---

## Kapan ganti model

**Teori:** DP kapasitas bukan satu-satunya tombol. Hitung dulu. `n = 100`, `W = 1e5` aman. `n = 100`, `W = 1e9` mustahil. `n = 40`, `W = 1e15` adalah meet in the middle: belah 20+20, enumerasi subset, pairing. `n = 20` naif sudah cukup untuk stress. `Σv` kecil memicu DP nilai. File 06 membahas subset sum, yang merupakan knapsack boolean. File 07 memecah stok terbatas. Jangan memaksa `vector<ll> dp(1e9)`.

**Kapan:** constraint dibaca sebelum typedef. **Tidak:** menulis `knapsack01` dulu lalu kaget MLE.

**STATE:** model dipilih supaya `|state| × biaya` muat, bukan supaya rumusnya cantik.

**TRANSISI:** MITM tidak memakai transisi DP; ia enumerasi plus sort atau two pointers.

**BASIS:** naif `n ≤ 20` adalah basis uji, bukan solusi kontes `n = 40`.

**Proses:**

```
n     W         Σv      pilihan
100   1e5       besar   knapsack01 1D
100   1e18      1e4     atas nilai
40    1e15      besar   MITM
20    apa saja  apa     naif untuk stress
1000  1e5       besar   1e8 ketat, biasanya lolos
```

Sketsa MITM (bukan implementasi penuh Day 54):

```
kiri  n/2 barang -> daftar (berat, nilai)
kanan sisanya    -> daftar (berat, nilai)
untuk setiap kiri, cari kanan dengan berat sisa terbesar, nilai maksimum prefix
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool pilihKapasitas(int n, ll W, ll sumV) {
    if (n <= 20) return true; // naif juga boleh
    if (W <= 100000 && (ll)n * W <= 100000000LL) return true;
    if (sumV <= 100000 && (ll)n * sumV <= 100000000LL) return false; // pakai nilai
    return false; // MITM atau soal lain
}

int main() {
    FASTIO;
    cout << pilihKapasitas(100, 100000, 1000000000LL) << "\n"; // 1
    cout << pilihKapasitas(100, 1000000000000LL, 5000) << "\n"; // 0 -> nilai
    return 0;
}
```

**Jebakan:** `n * W` dihitung `int`. `W = 1e5` tertulis 10000 karena salah hitung nol.

**Kompleksitas:** keputusan model `O(1)` di kertas. Salah model `O(TLE)`.

---

## Stress lawan naif

**Teori:** Knapsack mudah salah diam-diam: arah loop, off-by-one, overflow. Generator kecil plus `knapsackNaif` menangkap hampir semua bug 0-1. Batasi `n ≤ 12`, `W ≤ 30`, nilai kecil. Seed tetap supaya gagal bisa diulang. Bandingkan `knapsack01` dan `knapsack2D` juga. Jangan stress `n = 40` dengan naif.

**Kapan:** setelah fungsi ditulis, sebelum submit. **Tidak:** mengganti uji tangan `{3,2,4}` / `W=5` / 7.

**STATE:** setiap tes acak adalah instance 0-1 yang sah.

**TRANSISI:** assert kesetaraan naif dan DP.

**BASIS:** `n = 1`, `W = 0`, semua `w > W`.

**Proses:** satu tes yang harus lolos.

```
w = [3,2,4] v = [3,4,2] W = 5
naif = 7, 1D = 7, 2D = 7, pilih {0,1}
atas nilai = 7
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsack01(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

ll knapsackNaif(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll bw = 0, bv = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                bw += w[i];
                bv += v[i];
            }
        if (bw <= W) best = max(best, bv);
    }
    return best;
}

int main() {
    FASTIO;
    mt19937 rng(123);
    for (int t = 0; t < 1000; t++) {
        int n = rng() % 8 + 1, W = rng() % 20;
        vector<int> w(n);
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            w[i] = rng() % 8 + 1;
            v[i] = rng() % 20;
        }
        assert(knapsack01(w, v, W) == knapsackNaif(w, v, W));
    }
    cout << "ok\n";
    return 0;
}
```

**Jebakan:** `rng() % 0`. `n = 0` jika soal tidak mengizinkan. Assert dimatikan dengan `-DNDEBUG` di beberapa template — cetak beda, jangan hanya assert.

**Kompleksitas:** 1000 tes `n ≤ 8` sangat cepat. Itu jaring pengaman, bukan bukti untuk `W = 1e5`.

---

Uji cepat: greedy A/B/C `W=10` = 10 bukan 7; `(3,3),(2,4),(4,2)` `W=5` = 7 barang 0 dan 1; `(2,3)` `W=6` mundur = 3; `(2,3),(3,4),(4,5)` `W=6` = 8. Lanjut ke [06 — subset sum](06-subset-sum.md) untuk DP boolean, partisi, dan mention meet in the middle.
