# Meet in the middle

[← README](README.md) · [Indeks CP](../README.md)

`2^40` mustahil, tetapi `2^20 + 2^20` seketika. Tukar perkalian menjadi penjumlahan: bangkitkan semua subset dua paruh, lalu cocokkan dengan binary search.

Day terkait: **054**. `n <= 40` adalah sinyal klasik. Jika kapasitas `W` kecil, DP knapsack di folder 09 biasanya lebih sederhana.

## Daftar isi

- [Ide belah dua](#ide-belah-dua)
- [Bangun semua jumlah subset](#bangun-semua-jumlah-subset)
- [Subset sum MITM](#subset-sum-mitm)
- [Knapsack MITM dan prefix maksimum](#knapsack-mitm-dan-prefix-maksimum)
- [4-SUM sebagai MITM](#4-sum-sebagai-mitm)
- [Kapan DP menang](#kapan-dp-menang)
- [Peta keputusan](#peta-keputusan)

---

## Ide belah dua

**Teori:** Analoginya dua tim merakit puzzle: masing-masing 20 keping (sekitar satu juta susunan), lalu dicocokkan, bukan 40 keping sekaligus (satu triliun). Setiap subset penuh = subset kiri ∪ subset kanan. Kita tidak enumerasi `2^n` secara buta, melainkan enumerasi `2^{n/2}` dua kali lalu mencari pelengkap. Alasan benar: operasi himpunan bersifat kartesian; pencarian pelengkap menggantikan loop kedua.

**Kapan:** `n <= 40`, “pilih subset jumlah `X`”, atau knapsack nilai/berat terpisah dengan `W` besar. Jangan `n <= 20` (brute langsung lebih pendek). Jangan `n = 50`. Jangan jika `W <= 1e6` dan `n` kecil — DP `O(nW)` menang.

**Proses:** `n = 4`, belah `2 + 2`. Jumlah subset penuh `16`. Jumlah yang dibangun `4 + 4 = 8`, lalu 4 pencarian.

1. Kiri 2 elemen: `2^2 = 4` jumlah.
2. Kanan 2 elemen: 4 jumlah.
3. Untuk tiap jumlah kiri, cari `X - s` di kanan yang sudah diurut.
4. Kerja sekitar `4 log 4`, bukan 16 kali kerja berat jika n membesar.
5. Untuk `n = 40`: `2^20 ≈ 1e6` per paruh, aman.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int tengah(int n) { return n / 2; }

ll perkiraanKerja(int n) {
    int a = n / 2, b = n - a;
    return (1LL << a) + (1LL << b);
}

int main() {
    FASTIO;
    cout << tengah(40) << '\n';          // 20
    cout << perkiraanKerja(40) << '\n';  // 2e6-an
    cout << perkiraanKerja(20) << '\n';  // 2e3-an, brute juga hidup
    cout << (1LL << 20) << '\n';         // 1048576
    return 0;
}
```

Jangan menulis `1 << 40` pada `int`.

**Jebakan:**
1. Membelah `1 + 39`: paruh kanan tetap `2^39`.
2. `n` ganjil tidak apa-apa; yang penting kedua paruh dekat.
3. Mengira MITM mengurangi eksponen jadi `n/4` tanpa alasan.

**Kompleksitas:** waktu kasar `O(2^{n/2} n)`, memori `O(2^{n/2})`.

---

## Bangun semua jumlah subset

**Teori:** Cara naif `O(k 2^k)`: untuk tiap mask, jumlahkan bit hidup. Cara linear `O(2^k)`: `hasil[mask] = hasil[mask tanpa lowbit] + a[lowbit]`. Analoginya menambah satu barang ke keranjang yang sudah dihitung. `b = __builtin_ctz(mask)` adalah indeks bit terendah.

**Kapan:** setiap kali kamu butuh semua jumlah atau semua pasangan `(berat, nilai)`. Jangan loop `i = 0..k-1` di dalam mask jika `k = 20` dan kamu melakukan ini berkali-kali di dalam tes besar. Satu kali `O(k 2^k)` masih aman.

**Proses:** `a = [1, 2, 4]`.

| mask | bit | rumus | jumlah |
| ---: | --- | --- | ---: |
| 0 | 000 | 0 | 0 |
| 1 | 001 | 0+1 | 1 |
| 2 | 010 | 0+2 | 2 |
| 3 | 011 | 1+2 | 3 |
| 4 | 100 | 0+4 | 4 |
| 5 | 101 | 1+4 | 5 |
| 6 | 110 | 2+4 | 6 |
| 7 | 111 | 3+4 | 7 |

Lowbit mask `6` (`110`) adalah bit 1, `6 ^ 2 = 4`, `hasil[4] + 2 = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> semuaJumlah(const vector<ll>& a) {
    int k = (int)a.size();
    vector<ll> res(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        res[mask] = res[mask ^ (1 << b)] + a[b];
    }
    return res;
}

vector<ll> semuaJumlahNaif(const vector<ll>& a) {
    int k = (int)a.size();
    vector<ll> res(1 << k, 0);
    for (int mask = 0; mask < (1 << k); mask++) {
        ll s = 0;
        for (int i = 0; i < k; i++)
            if (mask & (1 << i)) s += a[i];
        res[mask] = s;
    }
    return res;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 4};
    auto x = semuaJumlah(a);
    auto y = semuaJumlahNaif(a);
    cout << (x == y) << '\n'; // 1
    for (ll s : x) cout << s << ' ';
    cout << '\n'; // 0 1 2 3 4 5 6 7
    return 0;
}
```

**Jebakan:**
1. `1 << k` saat `k >= 31` pada `int`.
2. Overflow jumlah: barang `1e9`, 20 barang, pakai `ll`.
3. Menggunakan `ctz(0)`.

**Kompleksitas:** `O(2^k)` atau `O(k 2^k)`, memori `O(2^k)`.

---

## Subset sum MITM

**Teori:** Bagi array, bangun semua jumlah kiri dan kanan, sort kanan, untuk tiap `s` kiri hitung berapa kali `X - s` muncul di kanan. Analoginya dua orang membawa uang, total harus pas. Alasan benar: setiap pasangan `(subset kiri, subset kanan)` terwakili. Subset kosong menghasilkan jumlah `0`; putuskan sesuai soal apakah `X = 0` dihitung.

**Kapan:** hitung banyak subset berjumlah `X`, atau cek ada/tidak. `n <= 40`. Jangan `binary_search` yang hanya `bool` jika soal minta banyaknya.

**Proses:** `a = [1, 2, 3, 4]`, `X = 7`, bagi `2+2`.

1. Kiri `{1,2}`: `0, 1, 2, 3`.
2. Kanan `{3,4}`: `0, 3, 4, 7`.
3. Sort kanan: `0, 3, 4, 7`.
4. `s = 0` cari `7` ada. `s = 1` cari `6` tidak. `s = 2` cari `5` tidak. `s = 3` cari `4` ada.
5. Dua subset: `{3,4}` dan `{1,2,4}`.

`X = 0` menghitung subset kosong sekali: kiri `0` ketemu kanan `0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> semuaJumlah(const vector<ll>& a) {
    int k = (int)a.size();
    vector<ll> res(1 << k, 0);
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        res[mask] = res[mask ^ (1 << b)] + a[b];
    }
    return res;
}

ll hitungSubsetJumlah(const vector<ll>& a, ll X) {
    int n = (int)a.size();
    int mid = n / 2;
    vector<ll> kiri(a.begin(), a.begin() + mid);
    vector<ll> kanan(a.begin() + mid, a.end());
    auto A = semuaJumlah(kiri);
    auto B = semuaJumlah(kanan);
    sort(B.begin(), B.end());
    ll ans = 0;
    for (ll s : A) {
        auto lo = lower_bound(B.begin(), B.end(), X - s);
        auto hi = upper_bound(B.begin(), B.end(), X - s);
        ans += (hi - lo);
    }
    return ans;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 3, 4};
    cout << hitungSubsetJumlah(a, 7) << '\n'; // 2
    cout << hitungSubsetJumlah(a, 0) << '\n'; // 1 (kosong)
    cout << hitungSubsetJumlah(a, 6) << '\n'; // 2 yaitu {2,4} dan {1,2,3}
    return 0;
}
```

**Jebakan:**
1. Enumerasi `O(2^k · k)` berulang tanpa perlu.
2. `binary_search` hanya bool, padahal perlu kemunculan.
3. `int` untuk `ans` (bisa `2^{40}`).
4. Lupa subset kosong.

**Kompleksitas:** waktu `O(2^{n/2} n)`, memori `O(2^{n/2})`. `n = 40` sekitar 2e6 aman; `n = 50` tidak.

---

## Knapsack MITM dan prefix maksimum

**Teori:** Analoginya etalase yang diurut murah ke mahal: kalau uangmu cukup untuk barang ke-7, barang ke-5 yang lebih murah bisa jauh lebih berharga. Kamu ingin **nilai terbaik di antara semua yang muat**, bukan nilai barang persis di batas. Bangkitkan subset kiri `(berat, nilai)`, sort by berat, `pref[i] = max(nilai[0..i])`. Untuk subset kanan, `upper_bound` berat `W - s`, ambil `pref` di indeks itu. Tanpa prefix max, kamu hanya melihat satu subset yang beratnya paling dekat. Itu bug nomor satu MITM knapsack.

**Kapan:** `n <= 40`, berat dan nilai terpisah, kapasitas `W` besar (tidak muat DP `n · W`). Jangan jika `W <= 1e6` dan `n <= 100` — DP lebih sederhana.

**Proses:** contoh yang mematahkan tanpa prefix: kiri menghasilkan `(berat, nilai) = (0,0), (3,2), (4,1)` setelah sort berat. Cari sisa `4`. `upper_bound` jatuh setelah berat `4`, kandidat terakhir berat `4` nilai `1` — padahal berat `3` nilai `2` lebih baik. Prefix max: `[0, 2, 2]`.

Simulasi lengkap kecil, barang `(2,3), (2,1), (3,5)`, `W = 4`:

1. Semua subset dua paruh digabung lewat sisa kapasitas.
2. Sort A menurut berat.
3. `pref[0] = A[0].second`, `pref[i] = max(pref[i-1], A[i].second)`.
4. Untuk `(w, val)` dari B, jika `w > W` skip. `it = upper_bound(A, {W-w, +∞})`, mundur satu, ambil `pref`.
5. Jaga `it == begin`. Optimal di contoh ini `5` dari barang `(3,5)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<pair<ll, ll>> subsetBeratNilai(const vector<pair<ll, ll>>& a) {
    int k = (int)a.size();
    vector<pair<ll, ll>> res(1 << k, {0, 0});
    for (int mask = 1; mask < (1 << k); mask++) {
        int b = __builtin_ctz(mask);
        res[mask] = {res[mask ^ (1 << b)].first + a[b].first,
                     res[mask ^ (1 << b)].second + a[b].second};
    }
    return res;
}

ll knapsackMITM(const vector<pair<ll, ll>>& barang, ll W) {
    int n = (int)barang.size();
    int mid = n / 2;
    vector<pair<ll, ll>> L(barang.begin(), barang.begin() + mid);
    vector<pair<ll, ll>> R(barang.begin() + mid, barang.end());
    auto A = subsetBeratNilai(L);
    auto B = subsetBeratNilai(R);
    sort(A.begin(), A.end());
    vector<ll> pref(A.size());
    pref[0] = A[0].second;
    for (int i = 1; i < (int)A.size(); i++)
        pref[i] = max(pref[i - 1], A[i].second);
    ll best = 0;
    for (auto [w, val] : B) {
        if (w > W) continue;
        ll sisa = W - w;
        auto it = upper_bound(A.begin(), A.end(), make_pair(sisa, LLONG_MAX));
        if (it == A.begin()) {
            best = max(best, val);
            continue;
        }
        --it;
        int idx = (int)(it - A.begin());
        best = max(best, val + pref[idx]);
    }
    return best;
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> a = {{3, 2}, {4, 1}};
    cout << knapsackMITM(a, 4) << '\n'; // 2
    vector<pair<ll, ll>> b = {{2, 3}, {2, 1}, {3, 5}};
    cout << knapsackMITM(b, 4) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Lupa prefix maksimum.
2. `upper_bound` pair tanpa `LLONG_MAX` di second — urutan pair salah.
3. Memori `2^20` pair sekitar 16 MB; hitung dulu.
4. Berat negatif merusak sort dan bound.

**Kompleksitas:** waktu `O(2^{n/2} n)`, memori `O(2^{n/2})`.

---

## 4-SUM sebagai MITM

**Teori:** Analoginya dua orang masing-masing memilih dua kartu, lalu mengecek apakah total empat kartu nol. Empat loop `O(n^4)`; MITM `O(n^2 log n)`: semua `a[i] + a[j]`, sort, untuk tiap pasangan lain cari pelengkap. Semangat yang sama: pecah kerja jadi dua paruh. Pola UVa 1152, SPOJ ABCDEF.

**Kapan:** `n <= 4000` untuk empat array, jumlah target. Jangan `unordered_map` telanjang di Codeforces tanpa hati-hati. Jangan `n = 1e5` (`n^2` mati).

**Proses:** `A = {1, 2}`, `B = {-2, -1}`, `C = {-1, 2}`, `D = {0, 2}`, target `0`.

1. `AB = {1-2, 1-1, 2-2, 2-1} = {-1, 0, 0, 1}`.
2. `CD = {-1+0, -1+2, 2+0, 2+2} = {-1, 1, 2, 4}`.
3. `CD = -1` butuh `1` di AB, ada sekali.
4. `CD = 1` butuh `-1` di AB, ada sekali.
5. Jawaban `2`. Salah satu: `1 + (-2) + (-1) + 2 = 0`.

Jika satu array 4-sum, jaga indeks tidak overlap.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll empatJumlahNol(const vector<ll>& A, const vector<ll>& B,
                  const vector<ll>& C, const vector<ll>& D) {
    vector<ll> ab;
    for (ll x : A) for (ll y : B) ab.push_back(x + y);
    sort(ab.begin(), ab.end());
    ll ans = 0;
    for (ll x : C) for (ll y : D) {
        ll butuh = -(x + y);
        auto lo = lower_bound(ab.begin(), ab.end(), butuh);
        auto hi = upper_bound(ab.begin(), ab.end(), butuh);
        ans += (hi - lo);
    }
    return ans;
}

int main() {
    FASTIO;
    vector<ll> A = {1, 2}, B = {-2, -1}, C = {-1, 2}, D = {0, 2};
    cout << empatJumlahNol(A, B, C, D) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Overflow jumlah pair.
2. Hash hack pada `unordered_map`.
3. Indeks sama dipakai dua kali pada 4-sum satu array.
4. `int` untuk jawaban: `n = 4000` bisa `16e12`? Empat array 4000: pasangan `1.6e7`, jawaban muat `ll`.

**Kompleksitas:** waktu `O(n^2 log n)`, memori `O(n^2)`. `n = 1000` → 1e6 aman; `n = 5000` ketat.

---

## Kapan DP menang

**Teori:** MITM dan DP sama-sama menaklukkan “ambil atau tidak”. Bedanya dimensi. DP knapsack hidup jika `W` kecil: state `(i, sisa)` atau `dp[w]`. MITM hidup jika `n` kecil dan `W` besar. Analoginya: kalau rak tas pendek, isi tabel; kalau barang sedikit, belah dua. Greedy rasio **bukan** pengganti keduanya untuk 0-1.

**Kapan:** lihat batasan sebelum memilih senjata. Jangan MITM `n = 40`, `W = 1000` hanya karena “keren”. Jangan DP `W = 1e12`.

**Proses:** tiga soal, tiga alat.

1. `n = 20`, `X` bebas: bitmask `2^20` cukup, MITM tidak wajib.
2. `n = 36`, `X` bebas: MITM.
3. `n = 80`, `W = 1e5`: DP `O(nW)`, MITM mustahil.

Greedy rasio pada `(2,3), (3,4)`, `W = 3` mengambil `3`, DP/MITM mengambil `4`. Itu pengingat: MITM adalah brute pintar, bukan greedy.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll dp01(const vector<ll>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int cap = W; cap >= (int)w[i]; cap--)
            dp[cap] = max(dp[cap], v[i] + dp[cap - (int)w[i]]);
    return dp[W];
}

ll greedyRasio(vector<ll> w, vector<ll> v, ll W) {
    int n = (int)w.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return v[i] * w[j] > v[j] * w[i];
    });
    ll nilai = 0;
    for (int i : idx) if (w[i] <= W) {
        W -= w[i];
        nilai += v[i];
    }
    return nilai;
}

int main() {
    FASTIO;
    vector<ll> w = {2, 3}, v = {3, 4};
    cout << "dp=" << dp01(w, v, 3)
         << " greedy=" << greedyRasio(w, v, 3) << '\n'; // 4 vs 3
    return 0;
}
```

Folder 09 membahas tabel ini secara penuh. File ini hanya menandai perbatasan.

**Jebakan:**
1. Memilih MITM karena `n = 40` padahal `W = 200`.
2. Memilih greedy karena “knapsack”.
3. Tabel DP `W = 1e7` di memori 256 MB tanpa hitung.

**Kompleksitas:** DP `O(nW)`, MITM `O(2^{n/2} n)`, greedy `O(n log n)` tetapi bisa salah.

---

## Peta keputusan

```text
n <= 20, kerja O(n) per subset
  → bitmask biasa, folder 05

n <= 40, jumlah / knapsack W besar
  → MITM file ini

n <= 100, W <= 1e5
  → DP knapsack, folder 09

4 array, n <= 2000
  → 4-SUM MITM

Knapsack 0-1, n besar, W besar
  → bukan MITM, bukan DP naif
```

| bug | perbaikan |
| --- | --- |
| tidak ada prefix max | `pref[i] = max(pref[i-1], nilai)` |
| `binary_search` bool | `upper - lower` |
| belah 5+35 | belah hampir sama |
| `int` jawaban | `ll` |

Ringkasan: belah, bangkitkan, sort, bound. Knapsack wajib prefix maksimum. Greedy rasio bukan MITM.

Lanjut ke folder [05-rekursi](../05-rekursi/README.md) untuk enumerasi subset, atau [09-dp](../09-dp/README.md) jika `W` kecil.
