# 27 — D&C optimization & Knuth (Day 248)

[← CHT](26-cht.md) · [README](README.md) · [Indeks DP](README.md)

> **Satu kalimat:** jika titik pecah monoton, jangan menelusuri semua `k` — D&C membagi lapisan, Knuth memangkas rentang jadi `O(n^2)`.

Day ComprogLearning: **248**. Syarat: quadrangle inequality / monoton `opt`. Tanpa syarat, ini WA yang terlihat meyakinkan.

Tiga pertanyaan:

```
1. STATE     : dp[i][j] atau dp[layer][r] seperti range / bagi kelompok
2. TRANSISI  : k hanya di [optL, optR] yang menyempit
3. BASIS     : satu kelompok / interval kosong = 0 atau C penuh
```

## Daftar isi

- [Teori dua saudara](#teori-dua-saudara)
- [Kapan](#kapan)
- [Quadrangle inequality](#quadrangle-inequality)
- [D&C DP](#dc-dp)
- [Proses D&C](#proses-dc)
- [Knuth](#knuth)
- [Proses Knuth](#proses-knuth)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori dua saudara

**Teori:** Range / layer DP klasik:

```
dp[l][r] = min_{k} dp[l][k] + dp[k+1][r] + C(l,r)     // Knuth-ish
dp[i][j] = min_{k<j} dp[i-1][k] + C(k+1, j)            // D&C
```

Naif: `O(n^3)` atau `O(K n^2)`. Terlalu lambat untuk `n = 2000` / `n = 1e5, K = 20`.

Jika `opt[i][j]` = `k` terbaik **tidak turun** saat `j` naik (dan/atau saat `i` naik), kita tidak perlu meninjau semua `k`.

- **D&C opt:** satu lapisan, hitung `mid`, brute `k` di rentang, rekursi kiri dengan `optR = opt_mid`, kanan `optL = opt_mid`. `O(n log n)` per lapisan.
- **Knuth:** dua dimensi interval, `opt[l][r-1] ≤ opt[l][r] ≤ opt[l+1][r]`, cukup loop `k` di situ. Total `O(n^2)`.

Analoginya: toko sudah tahu titik potong harga di kota 50. Kota 49 tidak mungkin potong lebih kanan dari itu.

CHT ([26](26-cht.md)) adalah kasus khusus `C` linear. D&C/Knuth berlaku untuk `C` yang "cembung" lebih umum (jumlah segmen, variansi, ...).

---

## Kapan

**Kapan D&C.**

```
dp[i][j] = min_{k<j} dp[i-1][k] + C(k+1,j)
```

`i ≤ 200` lapisan (kelompok), `j ≤ 1e5`, `C` O(1) setelah prefix. Contoh: bagi array jadi `K` potongan, biaya `(sum)^2` atau variansi.

**Kapan Knuth.**

```
dp[l][r] = min_{l≤k<r} dp[l][k] + dp[k+1][r] + C(l,r)
```

`n ≤ 2000`, `C` monoton + QI. Contoh: gabung batu, biaya = jumlah rentang.

**Kapan tidak.**

1. `C` sembarang — `opt` tidak monoton.
2. `n ≤ 400` — `O(n^3)` lebih aman.
3. Transisi garis — CHT lebih sederhana.
4. Kamu belum membuktikan / melihat QI di editorial, lalu "coba Knuth" — risiko WA.

---

## Quadrangle inequality

**Teori:** fungsi biaya `C(l,r)` (pada interval tertutup indeks) memenuhi QI jika untuk `a ≤ b ≤ c ≤ d`:

```
C(a,c) + C(b,d) ≤ C(a,d) + C(b,c)
```

Monoton (untuk Knuth sering perlu): `C(b,c) ≤ C(a,d)` jika `[b,c] ⊆ [a,d]`.

Akibat kasar: `opt` monoton. Bukti lengkap panjang; untuk cheatsheet: **uji `C` pada angka kecil** sebelum percaya.

**Contoh `C` yang sering lolos:**

| C(l,r) | QI? |
|---|---|
| `sum[l..r]` | ya (pada interval positif) |
| `(sum[l..r])^2` | ya jika elemen ≥ 0 |
| `w[r] - w[l]` | sering |
| `max[l..r]` | sering monoton, cek QI |
| biaya acak `rnd[l][r]` | tidak |

**Proses cek QI:** `a=0,b=1,c=2,d=3`, `C = sum`.

```
arr 1,2,3,4
C(0,2)=6, C(1,3)=9, jumlah 15
C(0,3)=10, C(1,2)=5, jumlah 15
≤  terpenuhi sama dengan
```

Kalau `C` = elemen tengah aneh, bisa pecah.

Knuth butuh QI + monoton `C` untuk bentuk `dp = min (dp+dp+C)`. D&C butuh monoton `opt` pada lapisan (cukup "QI pada C" di banyak soal kelompok).

---

## D&C DP

**STATE:** `dp[i][j]` = biaya min membagi `j` elemen pertama menjadi `i` kelompok (kelompok = segmen kontigu).

**TRANSISI:** kelompok terakhir mulai di `k+1`,

```
dp[i][j] = min_{i-1 ≤ k < j} dp[i-1][k] + C(k+1, j)
```

`opt[i][j]` = `k` terbaik. Monoton: `opt[i][j] ≤ opt[i][j+1]`.

**BASIS:** `dp[1][j] = C(0,j)` atau `C(1,j)` sesuai indeks. `dp[i][0] = 0`. `j < i` = INF (tidak cukup elemen).

Algoritma satu lapisan:

```
dnc(L, R, optL, optR):
    if L > R return
    mid = (L+R)/2
    cari k terbaik di [optL, min(mid-1, optR)]
    cur[mid] = prev[k] + C(k+1, mid)
    dnc(L, mid-1, optL, k)
    dnc(mid+1, R, k, optR)
```

Setiap `j` dihitung sekali; setiap `k` di satu segmen `O(panjang)` — total `O(n log n)` per lapisan.

---

## Proses D&C

Bagi `[1, 3, 5]` jadi 2 kelompok, `C(l,r) = (sum[l..r])^2`. Indeks 1..3.

```
1 kelompok:
  C(1,1)=1, C(1,2)=16, C(1,3)=81

2 kelompok, j=3:
  k=1: 1 + (3+5)^2 = 1+64=65
  k=2: 16 + 25 = 41
opt = 2
```

`j=2`:

```
k=1: 1 + 9 = 10
```

Monoton: `opt[2] ≤ opt[3]`.

Naif dan D&C sama 41.

---

## Knuth

**STATE:** `dp[l][r]` biaya gabung interval `l..r` jadi satu. `opt[l][r]` = `k` terbaik (potong setelah `k`).

**TRANSISI:**

```
lo = opt[l][r-1]
hi = opt[l+1][r]
for k = lo..hi:
    kandidat dp[l][k] + dp[k+1][r] + C(l,r)
```

Isi menaik menurut `len = r-l+1`.

**BASIS:** `dp[i][i] = 0`, `opt[i][i] = i`. Untuk `len=2`, `k=l`, satu pilihan.

---

## Proses Knuth

Empat batu `1,1,1,1`. `C = sum` interval.

```
Gabung 2: biaya 2, opt = kiri
Gabung 3: (2)+1 + sum3=3 → 2+3=5, dua potong simetris
Gabung 4:
  ((1+1)+(1+1)) = 2+2+4=8
  kiri-berat 9
```

Knuth menemukan 8.

Tiga batu `10,20,30`:

```
(10+20)=30 lalu +30 = 60, plus 60? 
standar: dp[0][1]=30, dp[1][2]=50
dp[0][2] = min(0+50+60, 30+0+60) = 90
```

Sama file range DP.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll costSum2(const vector<ll>& pref, int l, int r) {
    // l,r 0-based inclusive
    if (l > r) return 0;
    ll s = pref[r + 1] - pref[l];
    return s * s;
}

void dnc(int L, int R, int optL, int optR, const vector<ll>& prev,
         vector<ll>& cur, const vector<ll>& pref) {
    if (L > R) return;
    int mid = (L + R) / 2;
    pair<ll, int> best = {INF, optL};
    int hi = min(mid - 1, optR);
    for (int k = optL; k <= hi; k++) {
        ll val = prev[k] + costSum2(pref, k + 1, mid);
        if (val < best.first) best = {val, k};
    }
    cur[mid] = best.first;
    dnc(L, mid - 1, optL, best.second, prev, cur, pref);
    dnc(mid + 1, R, best.second, optR, prev, cur, pref);
}

vector<ll> layersDC(const vector<ll>& a, int K) {
    int n = (int)a.size();
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<ll> prev(n), cur(n, INF);
    for (int j = 0; j < n; j++) prev[j] = costSum2(pref, 0, j);
    for (int i = 2; i <= K; i++) {
        fill(cur.begin(), cur.end(), INF);
        dnc(0, n - 1, 0, n - 1, prev, cur, pref);
        prev.swap(cur);
    }
    return prev;
}

ll knuthMerge(const vector<ll>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            int lo = opt[l][r - 1];
            int hi = opt[l + 1][r];
            hi = min(hi, r - 1);
            lo = min(lo, hi);
            ll add = pref[r + 1] - pref[l];
            for (int k = lo; k <= hi; k++) {
                ll cost = dp[l][k] + (k + 1 <= r ? dp[k + 1][r] : 0) + add;
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }
    return dp[0][n - 1];
}

ll mergeCubic(const vector<ll>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            ll add = pref[r + 1] - pref[l];
            for (int k = l; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + add);
        }
    return dp[0][n - 1];
}

int main() {
    FASTIO;
    cout << knuthMerge({1, 1, 1, 1}) << " " << mergeCubic({1, 1, 1, 1}) << "\n";
    cout << knuthMerge({10, 20, 30}) << "\n"; // 90
    auto dp = layersDC({1, 3, 5}, 2);
    cout << dp[2] << "\n"; // 41
    return 0;
}
```

Untuk `layersDC`, indeks `cur[mid]` memakai `C(k+1, mid)` dengan `k` = akhir kelompok sebelumnya. `prev` = lapisan `i-1`. Pastikan `optL` awal 0 dan `j` cukup besar: untuk `i` kelompok, `j ≥ i-1`. Di `dnc` seluruh `[0,n-1]` boleh, slot mustahil tetap INF jika `hi < optL`.

Perbaiki aman:

```cpp
if (optL > hi) {
    cur[mid] = INF;
    dnc(L, mid - 1, optL, optR, prev, cur, pref);
    dnc(mid + 1, R, optL, optR, prev, cur, pref);
    return;
}
```

---

## Jebakan

1. **Knuth pada `C` yang tidak QI.** `opt` merosot, jawaban lebih besar/kecil diam.

2. **`opt` diagonal tidak diisi.** `lo` sampah.

3. **`hi < lo`.** Clamp `lo = min(lo,hi)`.

4. **D&C: `C` O(n)` di dalam.** Hilang keuntungan. Prefiks dulu.

5. **D&C: `optR` vs `mid-1`.** `k` harus `< mid` (kelompok terakhir tidak kosong).

6. **Indeks 0/1 campur** pada `pref[r+1]-pref[l]`.

7. **Membandingkan Knuth dengan cubic hanya di satu tes.** Tulis `assert(knuth==cubic)` untuk banyak array positif kecil.

8. **Layer `K > n`.** INF.

9. **Overflow `sum^2`.** `sum` 1e9 * n → `__int128` atau cek soal.

10. **Menukar D&C vs Knuth rumus.** Bentuk `dp+dp+C` → Knuth. Bentuk `prev[k]+C(k+1,j)` → D&C.

---

## Kompleksitas

| Metode | Waktu | n aman |
|---|---|---|
| cubic merge | `O(n^3)` | 400 |
| Knuth | `O(n^2)` | 2000 |
| layer naif | `O(K n^2)` | n=3000, K=20 pas? 1.8e8 |
| D&C | `O(K n log n)` * cost C | n=1e5, K=200 jika C O(1) |

Memori: Knuth `O(n^2)`. D&C dua baris `O(n)`.

Jika Knuth `hi-lo` tidak menyempit, waktu kembali `O(n^3)` — hitung total iterasi `k` saat debug.

---

## Tabel uji

| Algoritma | Input | Output |
|---|---|---|
| Knuth / cubic | 1,1,1,1 | 8 |
| Knuth / cubic | 10,20,30 | 90 |
| Knuth | satu elemen | 0 |
| D&C K=1 | 1,3,5 | 81 |
| D&C K=2 | 1,3,5 | 41 |
| D&C K=3 | 1,3,5 | 1+9+25=35 |

Brute K-groups `n ≤ 8`: DFS potong.

---

## Checklist

1. Tulis naif, uji.
2. Cek QI / monoton `opt` (print `opt` pada n kecil: tidak turun).
3. Pilih D&C vs Knuth sesuai bentuk rumus.
4. `C` O(1).
5. `INF` untuk mustahil.
6. Knuth: `opt[l][r-1]..opt[l+1][r]`.
7. D&C: rekursi kiri/kanan dengan `k` mid.
8. `ll` / overflow kuadrat.

---

## Print opt untuk percaya

```cpp
// setelah cubic, simpan argmin
// untuk fixed l, baris opt[l][l], opt[l][l+1], ... harus non-decreasing
```

Kalau ada penurunan, **jangan Knuth**.

Untuk D&C: fixed layer, `opt[j]` vs `opt[j+1]` non-decreasing.

---

## Hubungan CHT

| | CHT | D&C | Knuth |
|---|---|---|---|
| bentuk | `m_j * x_i + c_j` | `prev[k]+C(k,j)` | `dp+dp+C` |
| syarat | garis, monoton | opt monoton | QI + opt 2D |
| waktu | O(n) / n log | O(K n log n) | O(n^2) |

Kadang **keduanya** berlaku. Pilih yang lebih pendek.

---

## Kenapa Knuth O(n^2)?

Untuk tiap `len`, tiap `l`, loop `k` sepanjang `opt[l+1][r] - opt[l][r-1]`. Jumlah lebar itu, jika `opt` monoton 2D, telescoping: tiap "celah" antar `opt` tetangga dibayar sekali per `len`. Total per `len` adalah `O(n)`, semua `len` → `O(n^2)`.

Kalau `opt` acak, lebar `O(n)` per sel → `O(n^3)` lagi.

Hitung di debug:

```cpp
long long iter = 0;
// di dalam for k: iter++;
// harus ≈ c * n * n, c kecil (2..8), bukan n^3/6
```

---

## D&C vs naif lapisan: angka

`n=5`, `K=2`, `C=(sum)^2`, array `1,1,1,1,1`.

1 kelompok: `(5)^2=25`.

2 kelompok, potong setelah `k`:

```
k=0: 1 + 16 = 17
k=1: 4 + 9 = 13
k=2: 9 + 4 = 13
k=3: 16 + 1 = 17
```

Min 13. D&C `mid` akan menemukan salah satu `k=1` atau `2`, lalu sisi kiri/kanan menyempit.

---

## C(l,r) = (sum)^2 memenuhi QI? (sketsa angka)

Elemen positif `1,2,3,4`. `a=0,b=1,c=2,d=3`:

```
C(a,c)=(1+2+3)^2=36
C(b,d)=(2+3+4)^2=81  jumlah 117
C(a,d)=(10)^2=100
C(b,c)=(2+3)^2=25    jumlah 125
36+81=117 ≤ 125  OK
```

Kalau ada negatif, kuadrat jumlah bisa merusak monoton `opt`. Jangan Knuth buta.

---

## Urutan isi Knuth

`len` kecil dulu: `dp[l][k]` dan `dp[k+1][r]` sudah selesai karena lebih pendek. `opt[l][r-1]` (lebih pendek 1) dan `opt[l+1][r]` (lebih pendek 1) sudah ada. Itulah mengapa clamp memakai tetangga itu, bukan `opt` sama `len`.

---

## Satu elemen dan dua elemen

Knuth `n=1` → 0. `n=2` → `C(0,1)` saja, `opt=0`. D&C `K=1` → `C(0,n-1)`. `K=2`, `n=2` → `C(0,0)+C(1,1)`.

Uji ini menangkap `INF` yang tidak ter-overwrite.

---

## Ringkasan dinding

```
D&C: hitung mid, brute k di [optL,optR], belah
Knuth: k ∈ [opt[l][r-1], opt[l+1][r]]
C harus QI / opt monoton
uji: batu 1,1,1,1 → 8 ; 10,20,30 → 90
K=2 pada 1,3,5 → 41
```
