# Kadane dan Variasi Subarray

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** kalau beban dari belakang sudah negatif, buang saja.

Day ComprogLearning: **035** Kadane. Semua 0-based. Fungsi modular. `ll` untuk jumlah. Sliding window gagal di sini karena elemen negatif mematahkan monoton.

## Daftar isi

- [Kadane](#kadane)
- [Kadane beserta indeks](#kadane-beserta-indeks)
- [Kadane sebagai prefix min](#kadane-sebagai-prefix-min)
- [Kadane melingkar](#kadane-melingkar)
- [Subarray jumlah minimum](#subarray-jumlah-minimum)
- [Maximum product subarray](#maximum-product-subarray)
- [Kadane 2D](#kadane-2d)
- [Beli jual saham satu transaksi](#beli-jual-saham-satu-transaksi)

---

## Kadane

> **Ide satu kalimat:** kalau beban dari belakang sudah negatif, buang saja.

### Kadane

**Teori:** Analoginya membawa tas di trek pendakian: jika isi tas sudah merugikan, lebih baik tas baru di titik ini. Sliding window gagal karena elemen negatif mematahkan monoton. Dua sudut setara: (1) DP, (2) prefix minus prefix minimum di kiri. Alasan DP benar: subarray terbaik yang **berakhir di i** hanya dua pilihan — mulai baru di i, atau sambung dari i-1.

**Kapan:** Pakai maximum subarray bebas panjang. Jangan jika panjang dibatasi (window / deque prefix). Jangan `best=0` saat wajib ada elemen.

**Proses:** `a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`.

| i | a[i] | cur = max(x, cur+x) | best |
| ---: | ---: | ---: | ---: |
| 0 | -2 | -2 | -2 |
| 1 | 1 | 1 | 1 |
| 2 | -3 | -2 | 1 |
| 3 | 4 | 4 | 4 |
| 4 | -1 | 3 | 4 |
| 5 | 2 | 5 | 5 |
| 6 | 1 | 6 | 6 |
| 7 | -5 | 1 | 6 |
| 8 | 4 | 5 | 6 |

1. i=3 memulai tas baru bernilai 4.
2. Rantai `4,-1,2,1` mencapai 6.
3. Sisa tidak memecahkan 6.
4. Array semua negatif `{ -5,-2,-3 }` menjawab -2, bukan 0.
5. `best = LLONG_MIN` menjaga nonempty.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadane(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MIN;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << kadane(a) << '\n'; // 6
    vector<ll> b = {-5, -2, -3};
    cout << kadane(b) << '\n'; // -2
    return 0;
}
```

**Jebakan:**
1. `best = 0` pada array semua negatif.
2. Overflow `int`.
3. Mengira Kadane bisa “panjang ≤ k”.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane beserta indeks

> **Ide satu kalimat:** catat kapan kamu memutuskan “tas baru”, itu kiri; kanan selalu i saat `best` pecah.

### Kadane beserta indeks

**Teori:** Analoginya besides berat tas, kamu butuh foto start dan finish. `curL` berubah **hanya** saat kamu mulai baru (`cur < 0` sebelum menambah). Saat `cur > best`, simpan `[curL, i]`. Alasan tie-break: kalau soal minta paling kiri, update `best` hanya saat `cur > best`, bukan `>=`.

**Kapan:** Pakai rekonstruksi. Jangan update `curL` setiap iterasi.

**Proses:** `a = [1, -2, 3, 1]`.

| i | a[i] | cur | curL | best | [bestL, bestR] |
| ---: | ---: | ---: | ---: | ---: | --- |
| 0 | 1 | 1 | 0 | 1 | 0,0 |
| 1 | -2 | -1 | 0 | 1 | 0,0 |
| 2 | 3 | 3 | 2 | 3 | 2,2 |
| 3 | 1 | 4 | 2 | 4 | 2,3 |

1. Setelah i=1, cur negatif.
2. i=2 mulai baru di indeks 2.
3. i=3 menyambung.
4. Jawaban nilai 4, indeks 2..3.
5. Tie `>` menjaga segmen paling kiri.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Segmen {
    ll nilai;
    int l, r;
};

Segmen kadanePosisi(const vector<ll>& a) {
    ll cur = a[0], best = a[0];
    int curL = 0, bestL = 0, bestR = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (cur < 0) {
            cur = a[i];
            curL = i;
        } else cur += a[i];
        if (cur > best) {
            best = cur;
            bestL = curL;
            bestR = i;
        }
    }
    return {best, bestL, bestR};
}

int main() {
    FASTIO;
    vector<ll> a = {1, -2, 3, 1};
    auto s = kadanePosisi(a);
    cout << s.nilai << ' ' << s.l << ' ' << s.r << '\n'; // 4 2 3
    return 0;
}
```

**Jebakan:**
1. `curL = i` setiap langkah.
2. Tie `>=` versus `>` tidak sesuai soal.
3. `n=1` terlewat jika loop dari 0 tanpa inisialisasi.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane sebagai prefix min

> **Ide satu kalimat:** jumlah `[l..r] = pre[r+1]-pre[l]`; agar besar, `pre[l]` harus kecil.

### Kadane sebagai prefix min

**Teori:** Analoginya jarak patok: kamu berdiri di KM sekarang, dan ingin jarak terbesar dari patok terendah di belakang. `best = max(pre[i] - minPrefixSebelumnya)`. Alasan sama dengan Kadane: membuang prefix terburuk di kiri. Versi ini mudah diperluas ke “panjang paling sedikit 2” dengan menunda update min.

**Kapan:** Pakai jika kamu sudah punya prefix, atau butuh syarat tambahan pada l. Jangan campur rumus 1-based.

**Proses:** `a = [1, -2, 3, 1]`, `pre = [0,1,-1,2,3]`.

| i (pre) | pre[i] | min kiri | pre[i]-min | best |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 1 | 0 | 1 | 1 |
| 2 | -1 | 0 | -1 | 1 |
| 3 | 2 | -1 | 3 | 3 |
| 4 | 3 | -1 | 4 | 4 |

1. Min kiri setelah melihat -1 menjadi -1.
2. `3 - (-1) = 4` = subarray `[3,1]`.
3. Sama dengan Kadane.
4. `freq` tidak perlu; hanya satu min.
5. Untuk “jumlah = K”, min diganti map.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadanePrefixMin(const vector<ll>& a) {
    ll pre = 0, minPre = 0, best = LLONG_MIN;
    for (ll x : a) {
        pre += x;
        best = max(best, pre - minPre);
        minPre = min(minPre, pre);
    }
    return best;
}

int main() {
    FASTIO;
    cout << kadanePrefixMin({1, -2, 3, 1}) << '\n'; // 4
    cout << kadanePrefixMin({-5, -2, -3}) << '\n'; // -2
    return 0;
}
```

**Jebakan:**
1. Update `minPre` sebelum `best` — menghitung subarray kosong 0.
2. `minPre` awal bukan 0 — kehilangan prefix mulai di 0.
3. Semua negatif: jika update salah, jawaban 0.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane melingkar

> **Ide satu kalimat:** subarray melingkar = total minus lubang (subarray minimum) di tengah.

### Kadane melingkar

**Teori:** Analoginya kalung manik: potongan terbaik yang nyambung ujung-ujung sama dengan “buang sepotong terburuk di tengah”. `max(kadaneBiasa, total - kadaneMin)`. Lubang: jika semua negatif, `total - minSum` = 0 = array kosong — **dilarang**. Kembalikan Kadane biasa (elemen terbesar).

**Kapan:** Pakai LC 918. Jangan tanpa penjaga semua-negatif.

**Proses:** `a = [5, -3, 5]`.

| Versi | hitung | nilai |
| --- | --- | ---: |
| Kadane max | 5-3+5 | 7 |
| total | 5-3+5 | 7 |
| Kadane min | -3 | -3 |
| circular | 7-(-3) | 10 |

1. Circular adalah `[5] + [5]` nyambung.
2. Jawaban 10.
3. `a = [-2,-1,-3]`: Kadane=-1.
4. `total-minSum=0` kosong → jawab −1.
5. Penjaga wajib.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadaneMax(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MIN;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

ll kadaneMin(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MAX;
    for (ll x : a) {
        cur = min(x, cur + x);
        best = min(best, cur);
    }
    return best;
}

ll kadaneMelingkar(const vector<ll>& a) {
    ll biasa = kadaneMax(a);
    ll total = 0;
    for (ll x : a) total += x;
    ll cand = total - kadaneMin(a);
    if (biasa < 0) return biasa;
    return max(biasa, cand);
}

int main() {
    FASTIO;
    cout << kadaneMelingkar({5, -3, 5}) << '\n';   // 10
    cout << kadaneMelingkar({-2, -1, -3}) << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. Lupa semua-negatif.
2. `total` overflow.
3. Min Kadane dengan `best=0`.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Subarray jumlah minimum

> **Ide satu kalimat:** Kadane pada `−a`, atau transisi `min` bukan `max`.

### Subarray jumlah minimum

**Teori:** Analoginya tas yang ingin **paling ringan** (bisa negatif: utang besar). Transisi cermin. Alasan benar: struktur subarray sama. Dipakai di rumus melingkar dan “buang potongan terburuk”.

**Kapan:** Pakai lubang kalung, “kerugian terbesar”. Jangan campur inisialisasi `best=0` jika wajib nonempty.

**Proses:** `a = [3, -2, 4, -5, 1]`.

| i | x | cur | best |
| ---: | ---: | ---: | ---: |
| 0 | 3 | 3 | 3 |
| 1 | -2 | -2 | -2 |
| 2 | 4 | 2 | -2 |
| 3 | -5 | -5 | -5 |
| 4 | 1 | -4 | -5 |

1. Jawaban −5 (satu elemen).
2. Rantai lebih panjang tidak lebih kecil.
3. `best=0` akan salah.
4. Negasi array lalu Kadane max juga bisa, hati-hati `LLONG_MIN`.
5. Nonempty wajib.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadaneMinimum(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MAX;
    for (ll x : a) {
        cur = min(x, cur + x);
        best = min(best, cur);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {3, -2, 4, -5, 1};
    cout << kadaneMinimum(a) << '\n'; // -5
    return 0;
}
```

**Jebakan:**
1. `best=0`.
2. Negasi overflow `INT_MIN`.
3. Lupa nonempty.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Maximum product subarray

> **Ide satu kalimat:** dua negatif jadi positif; jadi kamu harus membawa **minimum** juga.

### Maximum product subarray

**Teori:** Analoginya hutang kali hutang = kekayaan. Satu variabel `curMax` kalah saat `-2 * (-5)`. Saat `x<0`, max dan min bertukar peran. Alasan benar: hasil kali terbaik/buruk yang berakhir di i hanya dari `{x, curMax*x, curMin*x}`.

**Kapan:** Pakai LC 152. Jangan Kadane jumlah. Hati-hati overflow — di kontes sering modulo atau nilai kecil.

**Proses:** `a = [2, 3, -2, 4]`.

| i | x | mx | mn | best |
| ---: | ---: | ---: | ---: | ---: |
| 0 | 2 | 2 | 2 | 2 |
| 1 | 3 | 6 | 3 | 6 |
| 2 | -2 | -2 | -12 | 6 |
| 3 | 4 | 4 | -48 | 6 |

1. `[2,3]=6` juara.
2. Dua negatif pada `[2,-5,-2]` menghidupkan 20.
3. Nol mematahkan rantai; `max(x, mx*x)` mulai baru.
4. Satu variabel gagal di langkah x=-2.
5. Overflow mudah pada n panjang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll maxProduk(const vector<ll>& a) {
    ll mx = a[0], mn = a[0], best = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        ll x = a[i];
        if (x < 0) swap(mx, mn);
        mx = max(x, mx * x);
        mn = min(x, mn * x);
        best = max(best, mx);
    }
    return best;
}

int main() {
    FASTIO;
    cout << maxProduk({2, 3, -2, 4}) << '\n'; // 6
    cout << maxProduk({2, -5, -2}) << '\n';   // 20
    return 0;
}
```

**Jebakan:**
1. Satu variabel.
2. Nol mematahkan rantai — rumus sudah mulai baru, tapi tes harus ada.
3. Overflow.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane 2D

> **Ide satu kalimat:** kunci dua tepi kiri-kanan, padatkan jadi array 1D, lalu Kadane.

### Kadane 2D

**Teori:** Analoginya memilih dua dinding vertikal, lalu menjumlah tiap baris di antara dinding itu menjadi satu angka, kemudian mencari jalur horizontal terbaik dengan Kadane. Alasan O(n³): O(n²) pasangan kolom, O(n) Kadane. Untuk n=200 masih sering muat; n=500 ketat.

**Kapan:** Pakai maximum submatrix, n≤200–300. Jangan n=1000. Jangan lupa reset temp tiap ganti kiri.

**Proses:** matriks

```
 1  -2
-3   4
```

1. Kolom 0..0: temp `[1,-3]`, Kadane 1.
2. Kolom 1..1: temp `[-2,4]`, Kadane 4.
3. Kolom 0..1: temp `[-1,1]`, Kadane 1.
4. Jawaban 4 (satu sel).
5. Jika matriks `[[1,2],[3,4]]`, seluruh 10.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadane(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MIN;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

ll maxSubmatrix(const vector<vector<ll>>& a) {
    int n = (int)a.size(), m = (int)a[0].size();
    ll best = LLONG_MIN;
    for (int L = 0; L < m; L++) {
        vector<ll> temp(n, 0);
        for (int R = L; R < m; R++) {
            for (int i = 0; i < n; i++) temp[i] += a[i][R];
            best = max(best, kadane(temp));
        }
    }
    return best;
}

int main() {
    FASTIO;
    vector<vector<ll>> a = {{1, -2}, {-3, 4}};
    cout << maxSubmatrix(a) << '\n'; // 4
    return 0;
}
```

**Jebakan:**
1. Tidak mengosongkan `temp` saat L berganti.
2. `int` untuk jumlah sel 200×200×1e9.
3. n,m tertukar baris/kolom.

**Kompleksitas:** O(n · m²) waktu, O(n) memori.

---

## Beli jual saham satu transaksi

> **Ide satu kalimat:** Kadane pada selisih harga harian, atau catat harga beli terendah sejauh ini.

### Beli jual saham satu transaksi

**Teori:** Analoginya pasar: kamu ingat harga termurah yang sudah terlihat, lalu tiap hari bertanya “kalau jual sekarang, untung berapa?”. Itu sama dengan maximum subarray pada array selisih. Alasan benar: satu transaksi = pilih l<r, maksimalkan `harga[r]-harga[l]`.

**Kapan:** Pakai satu beli satu jual. Jangan untuk banyak transaksi tanpa reset. Jangan jual sebelum beli.

**Proses:** `p = [7,1,5,3,6,4]`.

| i | harga | min beli | untung jika jual |
| ---: | ---: | ---: | ---: |
| 0 | 7 | 7 | 0 |
| 1 | 1 | 1 | 0 |
| 2 | 5 | 1 | 4 |
| 3 | 3 | 1 | 2 |
| 4 | 6 | 1 | 5 |
| 5 | 4 | 1 | 3 |

1. Beli di 1, jual di 6, untung 5.
2. Tidak ada transaksi: 0.
3. Array menurun: 0.
4. Selisih harian `[ -6,4,-2,3,-2 ]`, Kadane 5.
5. Dua sudut sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll untungSatuTransaksi(const vector<ll>& p) {
    ll beli = p[0], best = 0;
    for (int i = 1; i < (int)p.size(); i++) {
        best = max(best, p[i] - beli);
        beli = min(beli, p[i]);
    }
    return best;
}

int main() {
    FASTIO;
    cout << untungSatuTransaksi({7, 1, 5, 3, 6, 4}) << '\n'; // 5
    cout << untungSatuTransaksi({7, 6, 4}) << '\n';          // 0
    return 0;
}
```

**Jebakan:**
1. Update `beli` sebelum hitung untung hari ini — menjual di harga yang sama.
2. Jawaban negatif padahal boleh tidak bertransaksi.
3. Dua transaksi diselesaikan dengan rumus satu transaksi.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Ringkasan

- `cur = max(x, cur+x)`, `best` mulai `LLONG_MIN` jika nonempty.
- Indeks: ganti `curL` hanya saat mulai baru.
- Melingkar: total minus Kadane min, jaga semua-negatif.
- Produk: bawa max dan min.
- 2D: padatkan kolom, lalu Kadane.
- Panjang tetap bukan Kadane — itu window.

Lanjut: [mono stack dan deque](mono-stack-deque.md).
