# FFT, NTT, dan konvolusi

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **246**. Perkalian polinom `O(n log n)`.

> **Ide satu kalimat:** konvolusi adalah kali polinom; DFT mengevaluasi di akar satuan, kali titik-ke-titik, inverse mengembalikan koefisien; NTT melakukan hal yang sama di modulo prima NTT-friendly.

Sebelumnya: [matrix & XOR](matrix-xor.md). Modular dasar: [modular-ncr.md](modular-ncr.md).

## Daftar isi

- [Konvolusi naif](#konvolusi-naif)
- [Ide FFT](#ide-fft)
- [Ukuran dan aliasing](#ukuran-dan-aliasing)
- [FFT rekursif](#fft-rekursif)
- [FFT iteratif](#fft-iteratif)
- [Perkalian polinom (konvolusi yang bisa dikompilasi)](#perkalian-polinom-konvolusi-yang-bisa-dikompilasi)
- [NTT](#ntt)
- [Kapan FFT vs NTT vs naif](#kapan-fft-vs-ntt-vs-naif)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Konvolusi naif

**Teori:** `c[k] = Σ_{i+j=k} a[i] b[j]`. Ini koefisien `(Σ a_i x^i)(Σ b_j x^j)`. Panjang hasil `n + m − 1`. Analoginya: setiap pasangan `(i, j)` menyumbang ke “hari” `i+j`, seperti jumlah dadu.

**Kapan:** `n, m ≤ 2000`, atau debug. Jangan `n = 1e5` naif (`1e10` kerja).

**Proses:** `A = 1 + 2x + 3x^2`, `B = 2 + x`.

```
(1+2x+3x^2)(2+x)
= 2 + x + 4x + 2x^2 + 6x^2 + 3x^3
= 2 + 5x + 8x^2 + 3x^3
```

Koefisien `[1,2,3] * [2,1] = [2,5,8,3]`.

`[1,1,1] * [1,1,1] = [1,2,3,2,1]`.

Jumlah dadu 1..6 dua kali: `a = [0,1,1,1,1,1,1]`, `c[k]` = banyak cara jumlah `k`. `c[2]=1`, `c[7]=6`, `c[12]=1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> conv_naif(const vector<ll>& a, const vector<ll>& b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> c(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    return c;
}

int main() {
    FASTIO;
    auto c = conv_naif({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n'; // 2 5 8 3
    auto d = conv_naif({1, 1, 1}, {1, 1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n'; // 1 2 3 2 1
    return 0;
}
```

**Jebakan:** panjang `n+m` bukan `n+m-1`; array kosong; overflow `a[i]*b[j]` di `int`.

**Kompleksitas:** `O(n m)` waktu, `O(n+m)` memori.

---

## Ide FFT

**Teori:** DFT mengevaluasi polinom di `n` akar satuan `ω^0, …, ω^{n−1}` dengan `ω = e^{−2π i / n}` (arah maju). Di titik-titik itu, perkalian polinom = **kali berpasangan** nilai. Inverse DFT mengembalikan koefisien. FFT (Cooley–Tukey) menghitung DFT dalam `O(n log n)`: pecah indeks genap/ganjil, `T(n) = 2T(n/2)+O(n)`, `n` pangkat 2.

```
A(x) = A_even(x^2) + x A_odd(x^2)
A(ω^k)       = Ae(ω^{2k}) + ω^k Ao(ω^{2k})
A(ω^{k+n/2}) = Ae(...)     − ω^k Ao(...)
```

Dua DFT berukuran `n/2` plus `n/2` kupu-kupu.

Analoginya: daripada menjumlahkan semua pasangan di meja, kamu memotret polinom di titik ajaib, kali foto, lalu rekonstruksi. Titik ajaib membuat geser-indeks menjadi putar-fase.

NTT = FFT yang sama, tetapi `ω` hidup di modulo prima `p = q · 2^s + 1`. Tidak ada error pecahan. `998244353 = 119 · 2^{23} + 1`, akar primitif `3`.

**Kapan:** perkalian polinom, string matching kasar, count pasangan jumlah, generating function. `n ≤ 1<<20` (~1e6) lolos. Jangan FFT untuk `n = 50` kecuali mau — `O(n^2)` lebih sederhana. Jangan FFT double jika butuh exact mod `1e9+7` tanpa trik.

**Proses:** sketsa `n = 2`, `a = [1, 2]`, `ω = e^{−iπ} = −1`.

```
y0 = 1 + 2 = 3
y1 = 1 + (−1)*2 = −1
```

DFT `[1,2]` = `[3, −1]`. Inverse dengan `ω = +1` dan bagi 2: `[(3−1)/2, (3−(−1))/2] = [1, 2]`.

Untuk kali `[1,2,3]*[2,1]`, pad ke `n = 4`, evaluasi 4 titik, kali 4 pasangan, inverse, `llround` → `[2,5,8,3]`.

**Kode:** seksi ide tidak menggantikan implementasi — mini cek identitas DFT size 2:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
using cd = complex<double>;

int main() {
    FASTIO;
    cd a0 = 1, a1 = 2;
    cd w = -1;
    cd y0 = a0 + a1;
    cd y1 = a0 + w * a1;
    cout << y0.real() << ' ' << y1.real() << '\n'; // 3 -1
    cd z0 = (y0 + y1) / 2.0;
    cd z1 = (y0 - y1) / 2.0;
    cout << z0.real() << ' ' << z1.real() << '\n'; // 1 2
    return 0;
}
```

**Jebakan:** `n` bukan pangkat 2; `n` terlalu pendek; memakai `pow` double untuk `ω` di loop dalam; mengira FFT menggantikan semua `O(n^2)` termasuk yang bukan konvolusi.

**Kompleksitas:** ide `O(n log n)` vs naif `O(n^2)`.

---

## Ukuran dan aliasing

**Teori:** DFT periodik: jika kamu mengevaluasi di `n` titik padahal derajat hasil `≥ n`, koefisien berlipat `c'[k] = Σ_t c[k + t n]` (aliasing). Wajib `n ≥ deg(A)+deg(B)+1` dan `n` pangkat 2. Analoginya: jam 12 jam tidak membedakan 13:00 dan 1:00 — panjang buffer harus menampung “hari berikutnya”.

**Kapan:** selalu cek `n` sebelum FFT. Pad nol sampai pangkat 2.

**Proses:** `[1,1] * [1,1] = [1,2,1]`. Jika `n = 2` (terlalu pendek):

```
hasil “terbungkus”: c[0]+c[2] = 1+1 = 2, c[1] = 2
→ [2, 2] salah
```

`n = 4` aman: `[1,2,1,0]`.

`[1,2,3]*[2,1]` derajat 3, butuh `n ≥ 4`. `n = 4` pas.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int next_pow2(int need) {
    int n = 1;
    while (n < need) n <<= 1;
    return n;
}

int main() {
    FASTIO;
    int sa = 3, sb = 2;
    int need = sa + sb; // >= sa+sb-1, loop < sa+sb aman
    cout << next_pow2(need) << '\n'; // 4
    cout << next_pow2(2 + 2) << '\n'; // 4, untuk [1,1]*[1,1]
    return 0;
}
```

**Jebakan:** `n = a.size()` tanpa pad; memotong hasil sebelum `llround`; mengira `need = max(sa, sb)`.

**Kompleksitas:** `O(1)` hitung `n`, memori `O(n)` setelah pad.

---

## FFT rekursif

**Teori:** pecah genap/ganjil, basis `n = 1`. Inverse memakai `ω^{−1}` dan bagi 2 di tiap level (total `/n`). Lebih mudah dibaca, lebih boros memori daripada iteratif.

**Kapan:** paham / debug. Submit: iteratif. `n ≤ 1<<18` rekursif sering masih lolos.

**Proses:** `n = 4`, `a = [1, 2, 3, 0]` (pad). Genap `[1,3]`, ganjil `[2,0]`.

DFT size 2 genap (ω2 = −1):

```
[1+3, 1-3] = [4, -2]
```

Ganjil:

```
[2+0, 2-0] = [2, 2]
```

ω4 = `e^{−iπ/2} = −i`.

```
k=0: 4 + 1 * 2 = 6
k=1: -2 + (−i)*2 = -2 - 2i
k=2: 4 - 2 = 2
k=3: -2 - (−i)*2 = -2 + 2i
```

Ini evaluasi `1+2x+3x^2` di `1, −i, −1, i`. Cek `x=1`: `1+2+3=6`. `x=-1`: `1-2+3=2`. Cocok.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
using cd = complex<double>;

void fft_rec(vector<cd>& a, bool invert) {
    int n = (int)a.size();
    if (n == 1) return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft_rec(a0, invert);
    fft_rec(a1, invert);
    double ang = 2 * acos(-1) / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<ll> kali_polinom_rec(vector<ll> a, vector<ll> b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)(a.size() + b.size())) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft_rec(fa, false);
    fft_rec(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft_rec(fa, true);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) c[i] = llround(fa[i].real());
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

int main() {
    FASTIO;
    auto c = kali_polinom_rec({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n'; // 2 5 8 3
    auto d = kali_polinom_rec({4, 0, 1}, {1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n'; // 4 4 1 1   (4+x^2)(1+x)
    return 0;
}
```

**Jebakan:** `n` ganjil; lupa `resize` pangkat 2; inverse tanpa bagi; `llround` vs `(ll)(x.real()+0.5)` pada negatif; `M_PI` tidak portabel — `acos(-1)` lebih aman.

**Kompleksitas:** `O(n log n)` waktu, `O(n log n)` memori stack + vektor sementara.

---

## FFT iteratif

**Teori:** bit-reversal menaruh indeks seperti daun rekursi, lalu kupu-kupu bottom-up `len = 2, 4, …, n`. Sama benarnya dengan rekursif. Ini versi yang biasa disalin di kontes.

Bit-reversal 2-bit: `00,01,10,11` → `00,10,01,11` yaitu indeks `0,2,1,3`.

**Kapan:** submit. Koefisien aman di `double` kira-kira `|c[k]| < 1e12` setelah konvolusi (aturan kasar). Exact integer besar → NTT.

**Proses:** `[1,2,3,0]` setelah bit-reversal `n=4`: `[1,3,2,0]`. Butterfly `len=2`, lalu `len=4`, hasil evaluasi sama seperti rekursif.

Cek kedua: `[1,1,1]*[1,1,1]=[1,2,3,2,1]`.

`[1,0,1]*[1,0,1]=[1,0,2,0,1]` yaitu `(1+x^2)^2 = 1 + 2x^2 + x^4`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
using cd = complex<double>;

void fft(vector<cd>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd& x : a) x /= n;
}

int main() {
    FASTIO;
    vector<cd> a = {1, 2, 3, 0};
    fft(a, false);
    fft(a, true);
    for (cd x : a) cout << llround(x.real()) << ' ';
    cout << '\n'; // 1 2 3 0
    return 0;
}
```

**Jebakan:** bit-reversal salah; `x /= n` lupa; `n` bukan pangkat 2; presisi `1e15`.

**Kompleksitas:** `O(n log n)` waktu, `O(n)` memori.

---

## Perkalian polinom (konvolusi yang bisa dikompilasi)

**Teori:** bungkus FFT iteratif menjadi `conv(a, b)` yang mengembalikan vektor `ll`. Ini fungsi yang kamu uji dulu dengan `[1,2,3]*[2,1]=[2,5,8,3]` sebelum menempel ke soal.

**Kapan:** konvolusi integer tidak terlalu besar, atau count pasangan. Setelah itu potong trailing nol jika derajat penting.

**Proses:** tiga tes wajib.

```
[1,2,3] * [2,1]     = [2,5,8,3]
[1,1,1] * [1,1,1]   = [1,2,3,2,1]
[4,0,1] * [1,1]     = [4,4,1,1]
```

Jika salah satu gagal, jangan lanjut soal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
using cd = complex<double>;

void fft(vector<cd>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (cd& x : a) x /= n;
}

vector<ll> conv(const vector<ll>& a, const vector<ll>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<ll> c(n);
    for (int i = 0; i < n; i++) c[i] = llround(fa[i].real());
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

int main() {
    FASTIO;
    auto c = conv({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n'; // 2 5 8 3
    auto d = conv({1, 1, 1}, {1, 1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n'; // 1 2 3 2 1
    auto e = conv({4, 0, 1}, {1, 1});
    for (ll x : e) cout << x << ' ';
    cout << '\n'; // 4 4 1 1
    return 0;
}
```

**Jebakan:** `while (n < a.size()+b.size())` vs `size()+size()-1` — `n ≥ sa+sb-1`, loop `n < sa+sb` aman (satu lebih). `llround` pada nilai negatif. Trailing nol terpotong sampai satu 0 untuk polinom nol.

**Kompleksitas:** `O(n log n)`, `n` pangkat 2 ≥ panjang hasil.

---

## NTT

**Teori:** DFT di `Z/pZ`. Butuh `n | (p−1)`, `n = 2^k`. `ω = g^{(p−1)/n}` dengan `g` akar primitif. Inverse `ω^{−1}` dan `n^{−1}`. Untuk `p = 998244353`, `g = 3`, `n ≤ 2^{23}`. Hasil **exact** modulo `p`. Langkah kupu-kupu identik FFT, ganti `cis` jadi `modpow`.

**Kapan:** konvolusi modular `998244353`. Mod `1e9+7` **bukan** NTT-friendly — pakai tiga modulus + CRT, split koefisien, atau `O(n^2)`. Jangan NTT double-modulus tanpa CRT.

**Proses:** `[1,2,3]*[2,1] ≡ [2,5,8,3] (mod 998244353)` karena angka kecil.

`n = 4`, `ω = 3^{(p−1)/4}`. `p−1 = 998244352`, `/4 = 249561088`. `ω^4 = 1`, `ω^2 = −1`. Inverse kali `inv(4)`.

Jika hasil asli `c[i] ≥ p`, NTT memberi `c[i] % p`, bukan integer tak bermodulus.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int MOD = 998244353;
const int G = 3;

ll modpow(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void ntt(vector<ll>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = modpow(G, (MOD - 1) / len);
        if (invert) wlen = modpow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = modpow(n, MOD - 2);
        for (ll& x : a) x = x * inv_n % MOD;
    }
}

vector<ll> conv_ntt(vector<ll> a, vector<ll> b) {
    int need = (int)a.size() + (int)b.size();
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    while (a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

int main() {
    FASTIO;
    auto c = conv_ntt({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n'; // 2 5 8 3
    auto d = conv_ntt({1, 1, 1}, {1, 1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n'; // 1 2 3 2 1
    return 0;
}
```

Akar primitif `3` benar untuk `998244353`. Modulus NTT lain yang sering: `7340033`, `1004535809`. Jangan ganti `G` sembarangan.

**Jebakan:** `MOD−1` tidak habis `len` (`n > 2^{23}`); `G` bukan primitive root; inverse `wlen` vs inverse `n` tertukar; `u−v` negatif tanpa `+MOD`; memakai NTT ini untuk `1e9+7`; `int` overflow `w*v` — di sini `ll`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`, `n ≤ 2^{23}` untuk modulus ini.

---

## Kapan FFT vs NTT vs naif

**Teori:** pilih alat dari kebutuhan exactness dan ukuran. Double FFT cepat ditulis, rawan `llround` salah jika koefisien besar. NTT exact di satu modulus. Naif tidak punya konstanta `log` dan tidak punya presisi.

**Kapan:**

| situasi | pilih |
|---|---|
| `n ≤ 2000` | naif |
| integer kecil, `|c| < 1e12` | FFT double + `conv` |
| `mod 998244353` | NTT |
| `mod 1e9+7` exact, `n` besar | 3-NTT + CRT (di luar template singkat ini) |
| `mod 1e9+7`, `n ≤ 2000` | naif modular |

**Proses:** soal “banyak pasangan `a_i + b_j = x`”, `n = 1e5`, nilai `0..1e6`. Bentuk histogram `A[val]++`, `B[val]++`, `conv(A, B)`, baca `c[x]`. `n_fft ≈ 2e6`, lolos.

Soal `mod 1e9+7` kali polinom derajat `1e5`: naif TLE, FFT double salah, NTT `998244353` salah modulus — perlu strategi lain.

**Kode:** kerangka count jumlah (histogram).

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// pakai conv() dari seksi sebelumnya
// sketsa:
// vector<ll> A(MAX+1), B(MAX+1);
// for (x : a) A[x]++;
// for (x : b) B[x]++;
// auto C = conv(A, B);
// jawab C[s]

int main() {
    FASTIO;
    vector<ll> A(7, 0), B(7, 0);
    for (int i = 1; i <= 6; i++) A[i] = B[i] = 1;
    // naif kecil
    vector<ll> C(13, 0);
    for (int i = 0; i <= 6; i++)
        for (int j = 0; j <= 6; j++)
            C[i + j] += A[i] * B[j];
    cout << C[2] << ' ' << C[7] << ' ' << C[12] << '\n'; // 1 6 1
    return 0;
}
```

**Jebakan:** histogram 1-based vs 0; `conv` memotong trailing nol lalu indeks `s` hilang; dua FFT pada array berbeda panjang tanpa pad sama.

**Kompleksitas:** histogram `O(MAX log MAX)`.

---

## Peta keputusan

```
kali / konvolusi
├── n ≤ 2000                    → naif
├── angka kecil, boleh double   → FFT + conv()
├── mod 998244353               → NTT
├── mod 1e9+7 exact, n besar    → 3-NTT+CRT atau pecah koefisien
└── bukan konvolusi             → jangan FFT
```

| tes | keluaran |
|---|---|
| `[1,2,3]*[2,1]` | `2 5 8 3` |
| `[1,1,1]*[1,1,1]` | `1 2 3 2 1` |
| DFT lalu inverse | kembali ke array semula |

---

## Ringkasan

1. Konvolusi `c[k] = Σ_{i+j=k} a[i]b[j]` = kali polinom.
2. FFT: evaluasi di akar satuan, kali titik, interpolasi. `n` pangkat 2, cukup panjang.
3. Rekursif untuk paham; iteratif + `conv()` untuk submit.
4. Uji selalu `[1,2,3]*[2,1]=[2,5,8,3]` sebelum soal.
5. NTT exact di `998244353` dengan `g = 3`; bukan untuk `1e9+7`.
6. Presisi double membatasi ukuran koefisien; overflow modular membatasi makna integer asli.

Kembali ke [indeks folder 07](README.md) atau [indeks CP](../README.md).
