# 07 — Bounded knapsack

[← Subset sum](06-subset-sum.md) · [← 09-dp](README.md) · [LIS →](08-lis.md)

Day ComprogLearning: **147**. Stok `k[i]` terbatas, lebih dari satu, kurang dari tak hingga. Pecah biner mengubah `k` menjadi `O(log k)` paket 0-1.

> **Ide satu kalimat:** `{1, 2, 4, ..., sisa}` mencakup setiap kuantitas `0..k` tanpa melebihi `k`; tiap paket di-loop mundur.

## Daftar isi

- [Spektrum knapsack](#spektrum-knapsack)
- [Naif menduplikasi barang](#naif-menduplikasi-barang)
- [Pecah biner](#pecah-biner)
- [Bukti paket sisa](#bukti-paket-sisa)
- [Implementasi mundur](#implementasi-mundur)
- [Pintasan unbounded](#pintasan-unbounded)
- [Jejak angka lengkap](#jejak-angka-lengkap)

---

## Spektrum knapsack

**Teori:** Tiga saudara knapsack hanya berbeda stok. 0-1: `k[i] = 1`. Bounded: `1 < k[i] < ∞`. Unbounded: `k[i] = ∞`. Toko kelontong adalah bounded: mie instan ada 7 bungkus, bukan 1 dan bukan tak hingga. Formulasi: pilih integer `q[i]` dengan `0 ≤ q[i] ≤ k[i]`, `sum q[i]*w[i] ≤ W`, maksimalkan `sum q[i]*v[i]`. Kalau `k[i] = 1` untuk semua, kembali ke file 05. Kalau `k[i] * w[i] ≥ W`, barang itu berperilaku unbounded di dalam tas ini.

**Kapan:** stok tertulis lebih dari 1 dan tidak "tak terbatas". **Tidak:** `k = 1` murni, atau `k` begitu besar dibanding `W/w` tanpa memanfaatkan pintasan.

**STATE:** setelah semua jenis diproses, `dp[c]` adalah nilai maksimum kapasitas `c` dengan menghormati stok.

**TRANSISI:** setiap salinan atau paket adalah keputusan 0-1: masuk atau tidak.

**BASIS:** `dp[0] = 0`.

**Proses:** tiga soal yang kelihatan sama, `W = 6`, barang berat 2 nilai 3.

```
stok     nama          jawaban   cara
1        0-1           3         satu barang
3        bounded       9         tiga barang, berat 6
∞        unbounded     9         sama, karena 4 sudah tidak muat
```

Pada `W = 8`, stok 3 memberi 9 (berat 6, sisa 2 kosong), unbounded memberi 12.

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

ll unboundedKnapsackMax(int W, const vector<int>& wt, const vector<ll>& val) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = wt[i]; w <= W; w++)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsack01({2}, {3}, 8) << "\n";              // 3
    cout << unboundedKnapsackMax(8, {2}, {3}) << "\n";    // 12
    return 0;
}
```

**Jebakan:** memakai unbounded pada stok 3 dan `W = 8`, jawaban 12 padahal stok habis di 6.

**Kompleksitas:** memilih saudara yang salah tidak mengubah notasi `O(n W)`, ia mengubah angka.

---

## Naif menduplikasi barang

**Teori:** Cara pertama: tulis barang `i` sebanyak `k[i]` kali, lalu jalankan 0-1. Benar, lambat. `N = 100`, `W = 10000`, `k[i] = 1000` menghasilkan `Σk = 1e5` barang virtual dan `W * Σk = 1e9` operasi. TLE. Selain itu, `k[i]` boleh dipotong menjadi `min(k[i], W / w[i])` karena lebih dari itu tidak muat. Pemotongan ini wajib sebelum menghitung `Σk`, dan tetap tidak menyelamatkan jika banyak jenis hampir mengisi `W`.

**Kapan:** `Σk` kecil, misalnya total salinan `≤ 2000`. **Tidak:** `k[i] = 1e6`.

**STATE:** setiap salinan adalah barang 0-1 identik.

**TRANSISI:** loop mundur per salinan.

**BASIS:** `dp[0] = 0`.

**Proses:** barang berat 2 nilai 3, stok 5, `W = 7`. `c_eff = min(5, 7/2) = 3`. Naif menulis tiga salinan `(2,3)`.

```
salinan1  dp[2]=3, dp[4]=3, dp[6]=3
salinan2  dp[4]=6, dp[6]=9, dp[2] tetap 3
salinan3  dp[6]=9 sudah, dp[4]=6, tidak ada ruang ketiga? 
          c=6: max(9, dp[4]+3)=9  (dp[4] sudah 6, 6+3=9)
          berat 6 = tiga kali, nilai 9
```

`W = 7` sisa 1 kosong. Jawaban 9.

Hitung operasi naif tanpa potong: 5 salinan * 7 = 35, masih kecil. Dengan `k = 1e6` menjadi jutaan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsackBoundedNaif(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        int boleh = min(k[i], w[i] ? W / w[i] : 0);
        for (int t = 0; t < boleh; t++)
            for (int c = W; c >= w[i]; c--)
                dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    }
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsackBoundedNaif({2}, {3}, {5}, 7) << "\n"; // 9
    return 0;
}
```

**Jebakan:** tidak memotong `k` oleh `W/w`. Loop salinan maju pada kapasitas (barang yang sama masuk `W/w` kali dalam satu salinan — kacau).

**Kompleksitas:** `O(W Σ min(k, W/w))`. Bisa `10^9`.

---

## Pecah biner

**Teori:** Setiap bilangan `0..2^m-1` punya representasi unik dari `{1, 2, 4, ..., 2^{m-1}}`. Timbangan pasar menimbang 1 sampai 15 gram dengan anak 1, 2, 4, 8. Stok `k` yang bukan `2^m-1` diselesaikan dengan mengambil pangkat dua selama muat, lalu sisa sebagai paket terakhir. `k = 13` menjadi `{1, 2, 4, 6}`. Jumlah paket `≤ floor(log2 k) + 1`. `k = 1000` menjadi sekitar 10 paket, bukan 1000. Setiap paket adalah barang 0-1 berbobot `q*w` dan bernilai `q*v`. Loop kapasitas mundur per paket. Maju pada paket membuat paket yang sama dipakai dua kali, melebihi stok.

**Kapan:** `k` besar, `W` sedang. **Tidak:** `k = 1` (tidak perlu pecah), atau `k*w ≥ W` (pintasan unbounded lebih pendek).

**STATE:** setelah paket-paket barang `i` dimasukkan, setiap kuantitas `0..k[i]` yang muat sudah terwakili sebagai subset paket.

**TRANSISI:** paket `(q*w, q*v)` di-0-1-kan mundur.

**BASIS:** sebelum paket, `dp` milik barang sebelumnya.

**Proses:** pecah beberapa `k`.

```
k     ambil berurutan           paket
1     1                         {1}
2     1, sisa 1                 {1,1}
3     1, 2                      {1,2}
5     1, 2, sisa 2              {1,2,2}
7     1, 2, 4                   {1,2,4}
13    1, 2, 4, sisa 6           {1,2,4,6}
1000  1,2,4,...,512, sisa 489   10 paket
```

`k = 2` menjadi `{1,1}` dua paket identik. Itu sah: subset memberi 0, 1, atau 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> pecahBiner(int k) {
    vector<int> paket;
    int sisa = k;
    for (int p = 1; sisa > 0; p *= 2) {
        int ambil = min(p, sisa);
        paket.push_back(ambil);
        sisa -= ambil;
    }
    return paket;
}

int main() {
    FASTIO;
    for (int x : pecahBiner(13)) cout << x << " "; // 1 2 4 6
    cout << "\n";
    for (int x : pecahBiner(1000)) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** mengambil 8 pada `k = 13` sehingga total 15, lalu "membatasi saat isi tas". Itu bisa melebihi stok jika 8 dan 4 dan 2 terambil. Sisa wajib dipotong.

**Kompleksitas:** pecah `O(log k)`. Total jenis virtual `O(Σ log k)`.

---

## Bukti paket sisa

**Teori:** Klaim: `{1, 2, 4, ..., 2^{t-1}, r}` dengan `r = k - (2^t - 1)` dan `1 ≤ r ≤ 2^t` mencakup setiap integer `0..k`. Bagian pangkat dua mencakup `0..2^t-1`. Menambah `r` mencakup `r .. r+2^t-1`. Karena `r ≤ 2^t`, dua interval bertemu atau tumpang tindih, gabungannya `0..k`. Tidak ada lubang. Tidak ada jumlah paket yang melebihi `k` karena total isi paket tepat `k`. Inilah alasan sisa tidak boleh diganti `2^t`.

**Kapan:** ragu apakah `{1,2,4,6}` sah untuk 13. **Tidak:** memakai bukti ini untuk loop maju.

**STATE:** setiap integer `q` di `[0, k]` punya subset paket yang jumlahnya `q`.

**TRANSISI:** pilih atau tidak tiap paket; itu sistem bilangan hampir biner.

**BASIS:** `q = 0` subset kosong.

**Proses:** `k = 13`, paket `{1, 2, 4, 6}`.

```
tanpa 6: subset {1,2,4} = 0..7
dengan 6: 6..13
gabungan 0..13
tumpang 6 dan 7
```

Tabel `q` ke subset (salah satu):

```
q    pecahan
0    —
1    1
2    2
3    1+2
4    4
5    1+4
6    6  (atau 2+4)
7    1+6
8    2+6
9    1+2+6
10   4+6
11   1+4+6
12   2+4+6
13   1+2+4+6
```

Kalau paket `{1,2,4,8}` total 15: `q = 14 = 2+4+8` memakai 14 > 13. Terlarang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool mencakupSemua(int k, const vector<int>& paket) {
    vector<char> bisa(k + 1, 0);
    bisa[0] = 1;
    for (int p : paket)
        for (int s = k; s >= p; s--)
            if (bisa[s - p]) bisa[s] = 1;
    for (int q = 0; q <= k; q++)
        if (!bisa[q]) return false;
    return true;
}

int main() {
    FASTIO;
    cout << mencakupSemua(13, {1, 2, 4, 6}) << "\n"; // 1
    cout << mencakupSemua(13, {1, 2, 4, 8}) << "\n"; // 0,  dan 8+4+2=14>13
    return 0;
}
```

**Jebakan:** membuktikan "bisa membentuk k" saja. Yang dibutuhkan adalah **semua** `0..k`.

**Kompleksitas:** verifikasi `O(k log k)`. Produksi cukup percaya bukti interval.

---

## Implementasi mundur

**Teori:** Untuk setiap jenis, pecah `k`, lalu tiap paket diumpankan ke 0-1 1D mundur. `bobot = q * w`, `nilai = q * v` memakai `ll`. Jika `bobot > W`, paket itu dilewati; paket lebih kecil mungkin masih muat. `p *= 2` pada `int` aman selama `sisa` membatasi, tetapi `k` besar lebih aman dihitung lewat `sisa` dan `min`. Jangan loop maju "karena unbounded kemarin".

**Kapan:** implementasi standar bounded. **Tidak:** pecah lalu loop maju.

**STATE:** `dp[c]` nilai maksimum kapasitas `c` setelah paket yang sudah diumpankan.

**TRANSISI:** `dp[c] = max(dp[c], dp[c - bobot] + nilai)` mundur.

**BASIS:** `dp` nol.

**Proses:** barang berat 2 nilai 3, stok 5, `W = 7`. `c_eff = min(5, 3) = 3`. Paket 1 lalu 2. (Kalau tidak potong, paket 1, 2, 2; paket ketiga bobot 4, `W = 7`.)

Dengan potong ke 3, paket `{1, 2}`:

```
paket 1: (2,3)
mundur  dp[2]=3, dp[4]=3, dp[6]=3

paket 2: (4,6)
c=7 max(3, dp[3]+6)=6? dp[3] masih 3 -> 9
c=6 max(3, dp[2]+6)=9
c=4 max(3, dp[0]+6)=6
hasil dp[6]=9, dp[7]=9
```

Nilai 9 = tiga unit (berat 6). Cocok naif.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsackBounded(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        int sisa = k[i];
        if (w[i] > 0) sisa = min(sisa, W / w[i]);
        for (int p = 1; sisa > 0; p *= 2) {
            int ambil = min(p, sisa);
            sisa -= ambil;
            ll bobot = (ll)ambil * w[i], nilai = (ll)ambil * v[i];
            if (bobot > W) continue;
            for (int c = W; c >= bobot; c--)
                dp[c] = max(dp[c], dp[c - (int)bobot] + nilai);
        }
    }
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsackBounded({2}, {3}, {5}, 7) << "\n"; // 9
    cout << knapsackBounded({2}, {3}, {5}, 8) << "\n"; // 12? stok efektif 4, 4*3=12
    return 0;
}
```

Pada `W = 8`, `min(5, 4) = 4`, paket `{1, 2, 1}` atau `{1, 2, sisa 1}`, empat unit, nilai 12. Unbounded juga 12. Stok 5 tidak terpakai penuh.

**Jebakan:** paket maju. `ambil * w` overflow `int`. Lupa potong `W/w`. `w[i] = 0` pembagian.

**Kompleksitas:** `O(W Σ log min(k, W/w))` waktu, `O(W)` memori.

---

## Pintasan unbounded

**Teori:** Jika `k[i] * w[i] ≥ W`, stok tidak habis sebelum tas penuh. Jenis itu identik unbounded: satu loop maju `O(W)` tanpa faktor log. Hybrid ini disebut complete knapsack di banyak editorial Tiongkok. Campur jenis: yang stoknya ketat tetap pecah biner mundur; yang stoknya longgar maju. Jangan maju pada jenis yang stoknya ketat.

**Kapan:** `k` besar dan `w` kecil. **Tidak:** `k * w < W` tetapi tetap maju.

**STATE:** setelah jenis unbounded-efektif, `dp[c]` boleh memuat jenis itu berkali-kali sampai `c`.

**TRANSISI:** `for (c = w; c <= W; c++) dp[c] = max(dp[c], dp[c-w] + v)`.

**BASIS:** `dp` milik jenis sebelumnya.

**Proses:** `W = 10`, barang A `w=3 v=5 k=1`, barang B `w=2 v=3 k=100`.

```
A ketat: mundur, dp[3]=5, dp[6]=5, dp[9]=5
B longgar (200>=10): maju
c=2: 3
c=3: max(5, 3) = 5
c=4: 6
c=5: max(5, 3+3)=6? dp[5-2]+3=dp[3]+3=8
c=6: max(5, dp[4]+3=9, dp[3]+3=8)=9
c=7: dp[5]+3=11
c=8: dp[6]+3=12
c=9: max(5, dp[7]+3=14)=14
c=10: dp[8]+3=15
```

Jawaban 15: satu A dan dua B? 5+3+3=11 berat 3+2+2=7. Lima B = 15 berat 10. `dp[10]=15` adalah lima B, A tidak terpakai. `k_B` longgar memang mengizinkan itu.

Uji stok ketat salah maju: `k_B = 2`, `2*2=4 < 10`. Maju akan menulis lima B. Pecah `{1,1}` mundur hanya dua B, plus A: `5+3+3=11`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsackBoundedHybrid(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        if (w[i] <= 0) continue;
        if ((ll)k[i] * w[i] >= W) {
            for (int c = w[i]; c <= W; c++)
                dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
            continue;
        }
        int sisa = k[i];
        for (int p = 1; sisa > 0; p *= 2) {
            int ambil = min(p, sisa);
            sisa -= ambil;
            ll bobot = (ll)ambil * w[i], nilai = (ll)ambil * v[i];
            for (int c = W; c >= bobot; c--)
                dp[c] = max(dp[c], dp[c - (int)bobot] + nilai);
        }
    }
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsackBoundedHybrid({3, 2}, {5, 3}, {1, 100}, 10) << "\n"; // 15
    cout << knapsackBoundedHybrid({3, 2}, {5, 3}, {1, 2}, 10) << "\n";   // 11
    return 0;
}
```

**Jebakan:** syarat `k*w >= W` dihitung `int` overflow. Maju pada semua jenis "supaya cepat".

**Kompleksitas:** jenis longgar `O(W)`, jenis ketat `O(W log k)`.

---

## Jejak angka lengkap

**Teori:** Dua jenis, pecah biner, tanpa hybrid, supaya jejak terlihat. A: `w=2 v=3 k=3`. B: `w=3 v=4 k=2`. `W = 10`. Efektif A `min(3,5)=3` paket `{1,2}`. B `min(2,3)=2` paket `{1,1}`.

**Kapan:** mengetik kode, isi tabel ini dulu. **Tidak:** menyerah pada "terlalu banyak paket".

**STATE:** `dp[0..10]` setelah setiap paket.

**TRANSISI:** mundur per paket.

**BASIS:** nol.

**Proses:** isi setiap `max` lengkap. Jangan menebak sel yang tidak dihitung.

```
awal                 [0 0 0 0 0 0 0 0 0 0 0]

A paket 1 (2,3)
                     [0 0 3 3 3 3 3 3 3 3 3]

A paket 2 (4,6)
c=10 max(3,3+6)=9
c=8  max(3,3+6)=9
c=6  max(3,3+6)=9
c=4  max(3,0+6)=6
                     [0 0 3 3 6 6 9 9 9 9 9]

B paket 1 (3,4)
c=10 max(9, dp[7]+4=13)=13    tiga A + satu B
c=9  max(9, dp[6]+4=13)=13
c=8  max(9, dp[5]+4=10)=10
c=7  max(9, dp[4]+4=10)=10    dua A + satu B
c=6  max(9, dp[3]+4=7)=9
c=5  max(6, dp[2]+4=7)=7
c=4  max(6, 4)=6
c=3  max(3, 4)=4
                     [0 0 3 4 6 7 9 10 10 13 13]

B paket 2 (3,4)
c=10 max(13, dp[7]+4=14)=14   dua A + dua B
c=9  max(13, dp[6]+4=13)=13
c=8  max(10, dp[5]+4=11)=11
```

Jawaban `dp[10] = 14`. Dua A (berat 4, nilai 6) plus dua B (berat 6, nilai 8).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsackBounded(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W);

int main() {
    FASTIO;
    cout << knapsackBounded({2, 3}, {3, 4}, {3, 2}, 10) << "\n"; // 14
    return 0;
}

ll knapsackBounded(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        int sisa = k[i];
        if (w[i] > 0) sisa = min(sisa, W / w[i]);
        for (int p = 1; sisa > 0; p *= 2) {
            int ambil = min(p, sisa);
            sisa -= ambil;
            int bobot = ambil * w[i];
            ll nilai = (ll)ambil * v[i];
            for (int c = W; c >= bobot; c--)
                dp[c] = max(dp[c], dp[c - bobot] + nilai);
        }
    }
    return dp[W];
}
```

**Jebakan:** menghentikan jejak saat angka kelihatan masuk akal, atau melewatkan `c=7` pada B pertama sehingga `dua A + satu B = 10` hilang. Bandingkan dengan enumerasi `qA=0..3`, `qB=0..2`.

Enumerasi:

```
qA qB  berat nilai
0  0   0     0
0  1   3     4
0  2   6     8
1  0   2     3
1  1   5     7
1  2   8     11
2  0   4     6
2  1   7     10
2  2   10    14   <-
3  0   6     9
3  1   9     13
3  2   12    tidak muat
```

Maksimum 14. Tabel yang sudah diperbaiki cocok.

**Kompleksitas:** jejak tangan `O(W * jumlah paket)`. Untuk yakin, enumerasi `O(Π (k+1))` pada jenis sedikit.

---

Uji cepat: stok 5 berat 2 nilai 3 `W=7` = 9; `W=8` efektif 4 = 12; A/B di atas `W=10` = 14; `{1,2,4,6}` mencakup 0..13; `{1,2,4,8}` tidak boleh untuk 13. Lanjut ke [08 — LIS](08-lis.md) untuk `O(n^2)`, tails `O(n log n)`, dan rekonstruksi.
