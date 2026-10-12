# 08 — Sieve, GCD, dan aritmetika modular

[← 07 greedy](07-greedy-interval-konstruktif.md) · [Indeks](README.md) · [Lanjut: CRT & FFT →](09-number-crt-catalan-matrix-fft.md)

Kurikulum: folder **07 — Teori Bilangan** bagian awal di `DAFTAR-MATERI` (Day 088, 090; fondasi untuk 092).

Latihan harian: `KULIAH/ComProgLearning/CP` Day-85 sampai Day-96, khususnya Day-90.

> **Ide satu kalimat:** GCD merapikan dua bilangan lewat sisa bagi, sieve menyiapkan semua prima sampai `n`, modular menjaga jawaban tetap di `{0,1,...,m-1}` tanpa pernah menyimpan angka raksasa.

## Daftar isi

- [GCD Euclid](#gcd-euclid)
- [LCM](#lcm)
- [Extended Euclid](#extended-euclid)
- [Persamaan Diophantine linear](#persamaan-diophantine-linear)
- [Uji prima trial division](#uji-prima-trial-division)
- [Sieve of Eratosthenes](#sieve-of-eratosthenes)
- [Linear sieve dan SPF](#linear-sieve-dan-spf)
- [Faktorisasi dengan SPF](#faktorisasi-dengan-spf)
- [Banyak dan jumlah pembagi](#banyak-dan-jumlah-pembagi)
- [Aritmetika modular](#aritmetika-modular)
- [Pangkat modular](#pangkat-modular)
- [Invers modular: Fermat](#invers-modular-fermat)
- [Invers modular: Extended Euclid](#invers-modular-extended-euclid)
- [nCr modular](#ncr-modular)
- [Fungsi Euler totient](#fungsi-euler-totient)
- [Teorema Euler dan Fermat kecil](#teorema-euler-dan-fermat-kecil)
- [Miller-Rabin](#miller-rabin)
- [Pollard Rho](#pollard-rho)
- [Peta keputusan bab ini](#peta-keputusan-bab-ini)
- [Ringkasan](#ringkasan)

## GCD Euclid

**Teori:** `gcd(a, b)` adalah bilangan positif terbesar yang membagi `a` dan `b`. Algoritma Euclid: `gcd(a, b) = gcd(b, a mod b)`, berhenti di `gcd(a, 0) = |a|`. Kenapa benar: setiap pembagi bersama `a` dan `b` juga membagi `a - qb`, yaitu sisa. Analoginya memotong pita: pita panjang `a` dan `b`, potong yang panjang dengan yang pendek sampai habis — sisa terakhir adalah ukuran ubin terbesar.

**Kapan:** sederhanakan pecahan, LCM, ukuran langkah, jumlah kotak di persegi, CRT (file 09), invers. `n` sampai `10^18` tetap cepat. Jangan loop `for i=min(a,b); i>=1; i--`. Jangan `gcd` rekursif pada `int` negatif tanpa `abs` — definisi CP biasanya non-negatif, tetapi input bisa minus.

**Proses:** `gcd(1071, 462)`.

```
1071 = 2*462 + 147
462  = 3*147 + 21
147  = 7*21  + 0
gcd = 21
```

Cek: `1071/21=51`, `462/21=22`. `gcd(51,22)=1`, jadi 21 tepat.

`gcd(0, 12) = 12`. `gcd(0, 0)` secara implementasi sering 0; di soal hampir tidak muncul.

Langkah Euclid terburuk dekat Fibonacci: `gcd(F_{n+1}, F_n) = 1` butuh n langkah. Untuk 64-bit, langkah < 100.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd_rec(ll a, ll b) {
    a = llabs(a); b = llabs(b);
    if (b == 0) return a;
    return gcd_rec(b, a % b);
}

ll gcd_iter(ll a, ll b) {
    a = llabs(a); b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    cout << gcd_iter(1071, 462) << '\n';   // 21
    cout << gcd_iter(0, 12) << '\n';       // 12
    cout << gcd_iter(-15, 25) << '\n';     // 5
    cout << __gcd(1071, 462) << '\n';      // 21, gcc
    cout << std::gcd(1071, 462) << '\n';   // C++17
    return 0;
}
```

**Jebakan:** `%` pada negatif di C++ (sisa mengikuti tanda pembilang); `gcd(0,0)`; mengira `__gcd` ada di semua compiler tanpa GCC; overflow `llabs(LLONG_MIN)`.

**Kompleksitas:** waktu `O(log min(a,b))`, memori `O(1)` iteratif, `O(log)` stack rekursif.

---

## LCM

**Teori:** `lcm(a, b) = |a / gcd(a, b) * b|`. Bagi dulu baru kali, supaya tidak overflow di tengah. Kenapa rumus benar: `a = g·x`, `b = g·y` dengan `gcd(x,y)=1`, maka kelipatan persekutuan terkecil = `g·x·y`. Analoginya jadwal dua bus: satu setiap 12 menit, satu setiap 18, ketemu setiap 36 = `12/6*18`.

**Kapan:** periode bersama, ukuran kotak, “kelipatan terkecil yang habis dibagi semua”. Untuk banyak angka: lipat `lcm` berantai, waspadai overflow / pakai pecah faktor. Jangan `a*b/gcd` pada `int` jika `a*b` melewati 2e9.

**Proses:** `a=12, b=18`. `gcd=6`. `12/6*18=36`.

Tiga angka `4, 6, 8`:

```
lcm(4,6)=12
lcm(12,8)=24
```

`4=2^2`, `6=2·3`, `8=2^3` → max pangkat `2^3 · 3 = 24`.

`lcm(0, 5)`: secara matematika sering dianggap 0 (kelipatan 0 hanya 0). Di soal, `a=0` jarang. Tetap jaga: jika `a==0 || b==0` return 0.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd_iter(ll a, ll b) {
    a = llabs(a); b = llabs(b);
    while (b) { a %= b; swap(a, b); }
    return a;
}

ll lcm_ll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    a = llabs(a); b = llabs(b);
    return a / gcd_iter(a, b) * b;         // bagi dulu
}

bool lcm_aman(ll a, ll b, ll& out) {
    if (a == 0 || b == 0) { out = 0; return true; }
    a = llabs(a); b = llabs(b);
    ll g = gcd_iter(a, b);
    ll x = a / g;
    if (x > LLONG_MAX / b) return false;   // overflow
    out = x * b;
    return true;
}

ll lcm_banyak(const vector<ll>& a) {
    ll res = 1;
    for (ll x : a) {
        ll nxt;
        if (!lcm_aman(res, x, nxt)) return -1;
        res = nxt;
    }
    return res;
}

int main() {
    cout << lcm_ll(12, 18) << '\n';        // 36
    cout << lcm_banyak({4, 6, 8}) << '\n'; // 24
    ll out;
    cout << lcm_aman(LLONG_MAX, 2, out) << '\n'; // 0, overflow
    return 0;
}
```

**Jebakan:** `a * b / gcd` overflow sebelum bagi; `lcm` berantai melewati `ll` tanpa cek; `lcm` vs `gcd` tertukar di rumus pecahan.

**Kompleksitas:** sama Euclid `O(log)` per pasangan.

---

## Extended Euclid

**Teori:** selain `g = gcd(a,b)`, cari `x, y` supaya `a x + b y = g`. Identitas Bézout: selalu ada. Rekonstruksi dari Euclid: dari `a = qb + r` dan `b x1 + r y1 = g` substitusi `r = a - qb` → `a y1 + b (x1 - q y1) = g`. Analoginya: kamu punya koin `a` dan `b` (boleh utang = negatif), susun jumlah `g`.

**Kapan:** invers modular saat `m` tidak prima, Diophantine, CRT. Jangan pakai Fermat (`a^{m-2}`) jika `m` komposit.

**Proses:** `a=30, b=18`.

```
30 = 1*18 + 12
18 = 1*12 + 6
12 = 2*6  + 0
g = 6
```

Mundur:

```
6 = 18 - 1*12
12 = 30 - 1*18
6 = 18 - 1*(30-18) = -1*30 + 2*18
```

Jadi `x=-1, y=2`. Cek: `30*(-1)+18*2 = -30+36=6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ll x, y;
    ll g = exgcd(30, 18, x, y);
    cout << g << ' ' << x << ' ' << y << '\n'; // 6 -1 2
    cout << 30 * x + 18 * y << '\n';           // 6
    g = exgcd(7, 3, x, y);
    cout << g << ' ' << x << ' ' << y << '\n'; // 1 -2 5? 7*(-2)+3*5=-14+15=1
    return 0;
}
```

Jika `a` atau `b` negatif, normalisasi dulu atau sesuaikan tanda `x,y` setelahnya. Banyak soal menjamin `a,b > 0`.

**Jebakan:** menukar `x = x1 - q*y1` vs `x = y1`; overflow `q * y1` pada 64-bit ekstrem; mengira solusi unik — umum: `x += b/g`, `y -= a/g`.

**Kompleksitas:** `O(log min(a,b))` waktu dan stack.

---

## Persamaan Diophantine linear

**Teori:** `a x + b y = c` punya solusi integer iff `g | c` dengan `g = gcd(a,b)`. Satu solusi dari exgcd dikali `c/g`. Semua solusi: `x = x0 + (b/g) t`, `y = y0 - (a/g) t`. Analoginya: langkah `a` ke kanan, `b` ke kiri, bisa tiba di `c` hanya jika `c` kelipatan ukuran langkah dasar `g`.

**Kapan:** “ada berapa pasangan non-negatif”, frog jump, chicken nugget sederhana dua ukuran. Tiga variabel atau `x,y ≥ 0` plus minimalkan `x+y` — masih bisa, iterasi `t` di rentang. Jangan brute `x` sampai `1e12`.

**Proses:** `4x + 6y = 10`. `g=2`, `2|10` ya. Exgcd `4x+6y=2` → `x=-1, y=1` (karena `4*(-1)+6*1=2`). Kali 5: `x=-5, y=5`. Umum: `x=-5+3t`, `y=5-2t`.

Cari `x≥0, y≥0`:

```
-5+3t ≥ 0 → t ≥ 2
5-2t ≥ 0 → t ≤ 2
t=2: x=1, y=1
```

Satu solusi non-negatif: `4*1+6*1=10`.

`4x+6y=5`: `2` tidak membagi 5 → mustahil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

bool dio(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    g = exgcd(a, b, x, y);
    if (g < 0) { g = -g; x = -x; y = -y; }
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    return true;
}

// jumlah solusi x>=0, y>=0 (bisa 0, 1, atau banyak)
ll hitung_nonneg(ll a, ll b, ll c) {
    ll x, y, g;
    if (!dio(a, b, c, x, y, g)) return 0;
    ll bg = b / g, ag = a / g;
    // x + bg*t >= 0, y - ag*t >= 0
    // t >= ceil(-x / bg), t <= floor(y / ag)
    auto ceil_div = [](ll p, ll q) {
        if (q < 0) { p = -p; q = -q; }
        return p >= 0 ? (p + q - 1) / q : p / q;
    };
    auto floor_div = [](ll p, ll q) {
        if (q < 0) { p = -p; q = -q; }
        return p >= 0 ? p / q : -((-p + q - 1) / q);
    };
    ll tmin = ceil_div(-x, bg);
    ll tmax = floor_div(y, ag);
    if (tmax < tmin) return 0;
    return tmax - tmin + 1;
}

int main() {
    ll x, y, g;
    cout << dio(4, 6, 10, x, y, g) << ' ' << x << ' ' << y << '\n';
    cout << 4 * x + 6 * y << '\n';         // 10
    cout << hitung_nonneg(4, 6, 10) << '\n'; // 1
    cout << hitung_nonneg(4, 6, 5) << '\n';  // 0
    return 0;
}
```

Pembagian ceil/floor bertanda mudah salah. Untuk kontes, uji beberapa `t` di sekitar `-x/(b/g)` jika rentang kecil.

**Jebakan:** lupa `g | c`; overflow `x *= c/g`; menghitung `t` dengan `double`; `a=0` atau `b=0` kasus terpisah.

**Kompleksitas:** `O(log)` plus aritmetika solusi. Enumerasi `t` `O(jumlah solusi)` jika diminta daftar.

---

## Uji prima trial division

**Teori:** `n > 1` prima jika tidak punya pembagi di `2..√n`. Cukup cek `2` lalu bilangan ganjil, atau `2,3` lalu `i, i+2` berselisih 6. Kenapa `√n`: kalau `n = a b` dan `a ≤ b` maka `a ≤ √n`. Analoginya: kalau kotak tidak bisa disusun dari bata lebih kecil dari sisi akar, ia “batu utuh”.

**Kapan:** satu atau sedikit `n ≤ 10^12` (`√n = 1e6` aman), `n ≤ 10^18` sekali-sekali masih lolos jika konstan ketat. Banyak query `n ≤ 1e6` → sieve. `n ≤ 10^18` banyak query → Miller-Rabin.

**Proses:** `n = 91 = 7*13`. `√91 ≈ 9.5`. Cek 2,3,5,7. `91 % 7 == 0` → bukan prima.

`n = 97`. `√97 ≈ 9.8`. Cek 2,3,5,7. Tidak habis → prima.

`n = 1` bukan prima. `n = 2` prima. `n = 9` habis 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

vector<ll> faktor_trial(ll n) {
    vector<ll> f;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            f.push_back(i);
            n /= i;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}

int main() {
    cout << is_prime(1) << is_prime(2) << is_prime(91) << is_prime(97) << '\n';
    // 0 1 0 1
    auto f = faktor_trial(84);
    for (ll x : f) cout << x << ' ';       // 2 2 3 7
    cout << '\n';
    return 0;
}
```

**Jebakan:** `i * i <= n` overflow jika `i` dan `n` `int` dekat 46341; `n` negatif; loop `i <= n` TLE; `1` dianggap prima.

**Kompleksitas:** uji `O(√n)`, faktor `O(√n)`, memori `O(jumlah faktor)`.

---

## Sieve of Eratosthenes

**Teori:** dari `2` sampai `n`, setiap kali ketemu bilangan yang masih hidup, ia prima; matikan semua kelipatannya. Optimasi: mulai menandai dari `p*p` (kelipatan lebih kecil sudah dipukul prima lebih kecil). Analoginya: barisan anak, setiap “kapten” yang belum duduk menyuruh kelipatannya duduk.

**Kapan:** semua prima `≤ n` dengan `n ≤ 1e7` nyaman, `1e8` jika hafal memori (`1e8` byte = 100 MB, pakai `vector<char>` bukan `bool` bit-proxy lambat / atau bitset). Banyak query “apakah `x` prima” untuk `x ≤ n`. Jangan sieve sampai `1e12`.

**Proses:** `n = 20`. Awal semua true kecuali 0,1.

```
p=2  matikan 4,6,8,10,12,14,16,18,20
p=3  matikan 9,12,15,18
p=5  mulai 25 > 20, selesai
p=7  49>20
```

Hidup: 2,3,5,7,11,13,17,19.

`12` dipukul 2, lalu 3 lagi — tidak apa, sudah false.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> sieve_primes(int n) {
    vector<char> is(n + 1, true);
    if (n >= 0) is[0] = false;
    if (n >= 1) is[1] = false;
    for (int p = 2; (ll)p * p <= n; p++) {
        if (!is[p]) continue;
        for (int q = p * p; q <= n; q += p) is[q] = false;
    }
    vector<int> p;
    for (int i = 2; i <= n; i++)
        if (is[i]) p.push_back(i);
    return p;
}

int main() {
    auto p = sieve_primes(20);
    for (int x : p) cout << x << ' ';
    cout << '\n';                          // 2 3 5 7 11 13 17 19
    cout << sieve_primes(100).size() << '\n'; // 25
    return 0;
}
```

`p * p` wajib `ll` saat `n` dekat `INT_MAX`, atau `p <= n/p`.

**Jebakan:** mulai kelipatan dari `2p` bukan `p*p` (lebih lambat, tetap benar); `vector<bool>`; `n=1` akses `is[1]`; sieve di tiap testcase `t=1e4` — precompute sekali.

**Kompleksitas:** waktu `O(n log log n)`, memori `O(n)`.

---

## Linear sieve dan SPF

**Teori:** setiap komposit ditandai **tepat sekali**, oleh prima terkecilnya (SPF). Loop `i=2..n`: jika `i` belum punya SPF, ia prima. Lalu untuk setiap prima `p` dengan `p <= spf[i]` dan `i*p <= n`, set `spf[i*p]=p`. Linear karena tiap `j` dikunjungi sekali. SPF berguna: faktorisasi `O(log n)` per angka setelah `O(n)` prakomputasi.

**Kapan:** `n ≤ 1e7`, banyak faktorisasi / totient / mobius (file 09). Sieve biasa sudah cukup jika hanya daftar prima. Jangan linear sieve sampai `1e8` jika memori ketat (`spf` array `int` = 400 MB).

**Proses:** `n = 10`.

```
i=2  belum spf → prima, spf[2]=2
     p=2: 4, spf[4]=2
i=3  prima, spf[3]=3
     p=2: 6, spf[6]=2
     p=3: 9, spf[9]=3
i=4  spf[4]=2
     p=2: 8, spf[8]=2
     p=3 berhenti karena 3>spf[4]
i=5  prima
     10, spf[10]=2
     15>10 stop
```

`spf[1]` tidak terpakai. `spf[7]` terisi saat `i=7`. `spf[8]=2`, `spf[9]=3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LinearSieve {
    vector<int> spf, primes;
    LinearSieve(int n) {
        spf.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf[i] || (ll)i * p > n) break;
                spf[i * p] = p;
            }
        }
    }
};

int main() {
    LinearSieve s(20);
    for (int p : s.primes) cout << p << ' ';
    cout << '\n';
    for (int i = 2; i <= 20; i++)
        cout << i << ':' << s.spf[i] << ' ';
    cout << '\n';
    // 4:2 9:3 10:2 14:2 15:3 16:2 25 tidak ada
    return 0;
}
```

**Jebakan:** kondisi `p > spf[i]` dibalik → tidak linear, SPF salah; `i * p` overflow `int`; memakai `spf[1]`.

**Kompleksitas:** waktu `O(n)`, memori `O(n)`.

---

## Faktorisasi dengan SPF

**Teori:** selama `n > 1`, bagi `n` dengan `spf[n]`, catat. Setiap langkah `n` mengecil minimal terbagi prima, jumlah langkah `O(log n)`. Tanpa sieve: trial sampai `√n`, sama seperti seksi trial. Untuk `n ≤ 10^18` sekali: trial sampai `1e7` plus Miller-Rabin / Pollard.

**Kapan:** banyak `n ≤ N` setelah sieve `N`. Fungsi multiplikatif, pecah modulus. Jangan trial `√(1e18)` sebanyak `1e5` query.

**Proses:** `n = 84`, anggap SPF sudah ada.

```
spf[84]=2 → 2, n=42
spf[42]=2 → 2, n=21
spf[21]=3 → 3, n=7
spf[7]=7  → 7, n=1
```

`84 = 2^2 · 3 · 7`.

Tanpa array, trial:

```
2|84 → 2, 42
2|42 → 2, 21
3|21 → 3, 7
7 prima
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> spf_build(int n) {
    vector<int> spf(n + 1);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; (ll)i * i <= n; i++)
        if (spf[i] == i)
            for (int j = i * i; j <= n; j += i)
                if (spf[j] == j) spf[j] = i;
    return spf;
}

vector<pair<int, int>> faktor_spf(int n, const vector<int>& spf) {
    vector<pair<int, int>> f;
    while (n > 1) {
        int p = spf[n], c = 0;
        while (n % p == 0) {
            n /= p;
            c++;
        }
        f.push_back({p, c});
    }
    return f;
}

int main() {
    int N = 1000;
    vector<int> spf(N + 1);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; (ll)i * i <= N; i++)
        if (spf[i] == i)
            for (int j = i * i; j <= N; j += i)
                if (spf[j] == j) spf[j] = i;
    auto f = faktor_spf(84, spf);
    for (auto [p, c] : f) cout << p << '^' << c << ' ';
    cout << '\n';                          // 2^2 3^1 7^1
    return 0;
}
```

Pakai `spf_build(N)` di `main`, lalu `faktor_spf(84, spf)`.

**Jebakan:** `n` lebih besar dari ukuran array SPF; `n=1` hasil kosong (benar, tidak ada prima); menggabungkan pangkat salah (push setiap kali tanpa counter).

**Kompleksitas:** prakomputasi `O(n log log n)` atau `O(n)`, query `O(log n)`.

---

## Banyak dan jumlah pembagi

**Teori:** jika `n = p1^{a1} ... pk^{ak}`, maka jumlah pembagi `d(n) = (a1+1)...(ak+1)`, jumlah nilai pembagi `σ(n) = Π (p^{a+1}-1)/(p-1)`. Kenapa: pembagi = pilih pangkat `0..ai` independen (aturan perkalian). Analoginya menu: untuk setiap topping, pilih berapa sendok 0 sampai max.

**Kapan:** “berapa pembagi”, “jumlah semua pembagi”, bilangan sempurna. Hitung `d(n)` untuk semua `n ≤ N` dengan sieve kelipatan. Jangan enumerasi `1..n` per query.

**Proses:** `n = 84 = 2^2 · 3^1 · 7^1`.

```
d(84) = 3*2*2 = 12
pembagi: 1,2,4,3,6,12,7,14,28,21,42,84
σ(84) = (2^3-1)/(2-1) * (3^2-1)/2 * (7^2-1)/6
      = 7 * 4 * 8 = 224
```

Cek: 1+2+3+4+6+7+12+14+21+28+42+84 = 224.

Untuk semua `n ≤ 10`: sieve kelipatan menambah 1 ke `d[j]` dan menambah `i` ke `sig[j]` untuk `j+=i`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll d_from_faktor(const vector<pair<ll, int>>& f) {
    ll d = 1;
    for (auto [p, a] : f) d *= (a + 1);
    return d;
}

ll sigma_from_faktor(const vector<pair<ll, int>>& f) {
    ll s = 1;
    for (auto [p, a] : f) {
        ll pw = 1, sum = 0;
        for (int i = 0; i <= a; i++) {
            sum += pw;
            pw *= p;
        }
        s *= sum;
    }
    return s;
}

void sieve_d_sigma(int n, vector<int>& d, vector<ll>& sig) {
    d.assign(n + 1, 0);
    sig.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i) {
            d[j]++;
            sig[j] += i;
        }
}

int main() {
    vector<pair<ll, int>> f = {{2, 2}, {3, 1}, {7, 1}};
    cout << d_from_faktor(f) << ' ' << sigma_from_faktor(f) << '\n'; // 12 224
    vector<int> d;
    vector<ll> sig;
    sieve_d_sigma(10, d, sig);
    cout << d[10] << ' ' << sig[10] << '\n'; // 4 18  (1+2+5+10)
    return 0;
}
```

**Jebakan:** overflow `σ` untuk `n` besar; `d(1)=1`; loop sieve dari `i=0`; rumus `(p^{a+1}-1)/(p-1)` bagi integer vs kali `sum` pangkat (lebih aman).

**Kompleksitas:** rumus `O(jumlah prima berbeda)`. Sieve semua `O(n log n)`.

---

## Aritmetika modular

**Teori:** `a ≡ b (mod m)` artinya `m | (a-b)`. Kelas sisa `{0,1,...,m-1}` tertutup untuk `+,-,*`. Sifat: boleh `%` kapan saja sebelum `+,-,*`. Pembagian **tidak** boleh `%` langsung: ` (a/b) % m ≠ (a%m)/(b%m) `. Analoginya jam 12 jam: 9+4 = 1, bukan 13.

Di C++, `(-5) % 3 = -2`, bukan 1. Matematika ingin `1`. Normalisasi: `((a % m) + m) % m`.

**Kapan:** hampir semua soal counting, `10^9+7` atau `998244353`. Prefix sum mod. Jangan `double`. Jangan `%` setelah overflow `int*int`.

**Proses:** `m = 7`.

```
(10 + 8) % 7 = 18 % 7 = 4
(10%7 + 8%7)%7 = (3+1)%7 = 4

(10 * 8) % 7 = 80 % 7 = 3
3*1 % 7 = 3

(10 - 8) % 7 = 2
(3 - 1) % 7 = 2

(-5) % 7 di C++ bisa -5
norm = (-5+7)%7 = 2    karena -5 = -7+2
```

`1e9+7` prima, enak untuk invers. `10^9+6` bukan prima — Fermat gagal.

Perkalian `1e9 * 1e9` = `1e18` muat `ll`. `1e18 * 1e18` tidak — butuh `__int128` atau modulus kecil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

ll norm(ll a, ll m = MOD) {
    a %= m;
    if (a < 0) a += m;
    return a;
}

ll addmod(ll a, ll b, ll m = MOD) { return (norm(a, m) + norm(b, m)) % m; }
ll submod(ll a, ll b, ll m = MOD) { return (norm(a, m) - norm(b, m) + m) % m; }
ll mulmod(ll a, ll b, ll m = MOD) { return (__int128)norm(a, m) * norm(b, m) % m; }

int main() {
    cout << addmod(10, 8, 7) << '\n';      // 4
    cout << mulmod(10, 8, 7) << '\n';      // 3
    cout << submod(3, 10, 7) << '\n';      // 0? 3-10=-7 ≡ 0
    cout << norm(-5, 7) << '\n';           // 2
    cout << mulmod(1000000000LL, 1000000000LL) << '\n';
    return 0;
}
```

`submod(3,10,7) = (3-10+7)%7 = 0`. `3-10 ≡ -7 ≡ 0`.

**Jebakan:** `%` negatif; `int` overflow sebelum `%`; `pow` double; menulis `(a-b)%m` tanpa `+m`; `MOD` `int` lalu `a+b` overflow `int` dulu.

**Kompleksitas:** `O(1)` per operasi. `__int128` sedikit lebih mahal, tetap `O(1)`.

---

## Pangkat modular

**Teori:** `a^e mod m` dengan kuadrat berulang. Sama seperti file 06, wajib `%` tiap kali. Iteratif membaca bit `e`. `e=0` → `1 % m`. `m=1` → 0.

**Kapan:** invers Fermat, matrix (file 09), hashing, “hitung 2^n mod m”. `e` sampai `10^18`. Jangan `for i=0;i<e;i++`.

**Proses:** `2^13 mod 100`. `13=1101_2`.

```
res=1, a=2
bit0 1: res=2, a=4
bit1 0:         a=16
bit2 1: res=32, a=256≡56
bit3 1: res=32*56=1792≡92
```

`2^13=8192 ≡ 92`. Ya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modpow(ll a, ll e, ll m) {
    if (m == 1) return 0;
    ll res = 1 % m;
    a %= m;
    if (a < 0) a += m;
    while (e > 0) {
        if (e & 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return res;
}

int main() {
    cout << modpow(2, 13, 100) << '\n';    // 92
    cout << modpow(3, 13, 1000) << '\n';   // 323
    cout << modpow(5, 0, 7) << '\n';       // 1
    cout << modpow(2, 10, 1) << '\n';      // 0
    return 0;
}
```

**Jebakan:** `pow(2,13)` double; `a*a` overflow; `e` negatif tidak didefinisikan di sini (itu invers); `1 % m` saat `m=1`.

**Kompleksitas:** `O(log e)` kali, `O(1)` memori.

---

## Invers modular: Fermat

**Teori:** jika `m` prima dan `gcd(a,m)=1`, maka `a^{m-2} ≡ a^{-1} (mod m)` karena Fermat: `a^{m-1} ≡ 1`, jadi `a · a^{m-2} ≡ 1`. Analoginya: di dunia mod `m`, kali `a` bisa dibatalkan oleh suatu `b`.

**Kapan:** `MOD = 1e9+7` atau `998244353`, faktorial invers, bagi modular. Jangan jika `m` komposit. Jangan jika `m | a` — invers tidak ada.

**Proses:** `a=3, m=7`. `3^{5} mod 7` seharusnya invers.

```
3^1=3
3^2=2
3^3=6≡-1
3^4≡-3≡4
3^5≡12≡5
```

`3*5=15≡1 (mod 7)`. Ya, invers = 5. Cek: `3*5-2*7=15-14=1`.

`2` invers mod 7: `2*4=8≡1`, invers 4. `2^{5}=32≡4`. Cocok.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modpow(ll a, ll e, ll m) {
    ll res = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return res;
}

ll inv_fermat(ll a, ll m) {
    return modpow(a, m - 2, m);            // m prima
}

int main() {
    cout << inv_fermat(3, 7) << '\n';      // 5
    cout << inv_fermat(2, 7) << '\n';      // 4
    const ll MOD = 1000000007LL;
    ll i = inv_fermat(10, MOD);
    cout << (__int128)10 * i % MOD << '\n'; // 1
    return 0;
}
```

**Jebakan:** `m` tidak prima (`inv_fermat(2,8)` sampah); `a ≡ 0`; menghitung `m-2` saat `m=1`; pakai Fermat untuk `m=10^9+6`.

**Kompleksitas:** `O(log m)` per invers. Banyak invers `1..n` lebih baik `invfact` (seksi nCr).

---

## Invers modular: Extended Euclid

**Teori:** cari `x` pada `a x ≡ 1 (mod m)` = `a x + m y = 1`. Ada iff `gcd(a,m)=1`. Exgcd memberi `x`. Normalisasi `x` ke `[0,m)`. Ini jalan untuk **modulus apa pun yang koprima dengan a**, tidak harus prima.

**Kapan:** `m` komposit, CRT, invers di `mod 1e9` (bukan +7). Jangan jika `gcd > 1` kecuali soal meminta solusi `a x ≡ b (mod m)` yang bisa dibagi `g`.

**Proses:** `a=10, m=21`. `gcd(10,21)=1`. Exgcd:

```
21=2*10+1
10=10*1+0
1 = 21 - 2*10
10 x + 21 y =1 → x=-2, y=1
```

`x ≡ -2 ≡ 19 (mod 21)`. Cek: `10*19=190`, `190/21=9*21=189`, sisa 1.

`a=10, m=15`, `gcd=5 ≠ 1`, tidak ada invers. `10x ≡ 1 (mod 15)` mustahil (kiri kelipatan 5, kanan 1).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll inv_exgcd(ll a, ll m) {
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (g != 1 && g != -1) return -1;      // tidak ada
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {
    cout << inv_exgcd(10, 21) << '\n';     // 19
    cout << (__int128)10 * 19 % 21 << '\n'; // 1
    cout << inv_exgcd(10, 15) << '\n';     // -1
    cout << inv_exgcd(3, 7) << '\n';       // 5
    return 0;
}
```

**Jebakan:** tidak menormalisasi `x` negatif; `g=-1` dari `a` negatif; mengembalikan `x` tanpa `% m` (bisa di luar rentang).

**Kompleksitas:** `O(log m)`.

---

## nCr modular

**Teori:** `C(n,k) = n! / (k! (n-k)!)` untuk `0 ≤ k ≤ n`, else 0. Mod prima `p`: prakomputasi `fact[i]` dan `invfact[i] = (i!)^{-1}`, lalu `C(n,k) = fact[n] * invfact[k] * invfact[n-k]`. `invfact[n] = fact[n]^{p-2}`, lalu `invfact[i] = invfact[i+1] * (i+1)`. Analoginya: pilih `k` dari `n` kursi, urutan di dalam kelompok tidak dihitung.

**Kapan:** counting, Catalan (file 09), stars and bars `C(n+k-1, k)`. `n ≤ 1e6`, `p` prima. `n ≥ p` hati-hati: `n! ≡ 0`, Lucas mungkin perlu. Jangan hitung `n*(n-1)*...` di `int`. Jangan bagi `fact[k]` tanpa invers.

**Proses:** `C(5,2)=10`. `5!=120`, `2!=2`, `3!=6`, `120/12=10`.

Tabel kecil:

```
C(0,0)=1
C(4,0..4)= 1 4 6 4 1
C(6,3)=20
```

`C(5,2) mod 7 = 3`. `fact=[1,1,2,6,24≡3,120≡1]` mod 7? `24%7=3`, `120%7=1`. `invfact[2]=inv(2)=4`, `invfact[3]=inv(6)=6` karena `6*6=36≡1`. `1*4*6=24≡3`. Ya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

ll modpow(ll a, ll e, ll m = MOD) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

struct Comb {
    vector<ll> fact, invfact;
    Comb(int n) {
        fact.resize(n + 1);
        invfact.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
        invfact[n] = modpow(fact[n], MOD - 2);
        for (int i = n; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }
};

int main() {
    Comb cb(20);
    cout << cb.C(5, 2) << '\n';            // 10
    cout << cb.C(6, 3) << '\n';            // 20
    cout << cb.C(4, 0) << ' ' << cb.C(4, 4) << '\n'; // 1 1
    cout << cb.C(3, 5) << '\n';            // 0
    return 0;
}
```

Lucas (ide): `C(n,k) mod p = Π C(n_i, k_i)` pada digit basis `p`. Dipakai jika `n` besar, `p` kecil.

**Jebakan:** `k>n` tidak di-return 0; `MOD` tidak prima; `n ≥ MOD` fact menjadi 0; membangun `Comb(1e7)` tiap tes; `invfact[0]` salah hitung.

**Kompleksitas:** prakomputasi `O(n + log MOD)`, query `O(1)`. Memori `O(n)`.

---

## Fungsi Euler totient

**Teori:** `φ(n)` = banyak `1 ≤ k ≤ n` dengan `gcd(k,n)=1`. `φ(1)=1`. Rumus: `φ(n) = n Π (1 - 1/p)` untuk prima `p | n`. Implementasi: `res = n`, untuk tiap `p` bagi habis `n`, `res -= res/p`. Analoginya: di lingkaran `n` titik, berapa yang langkahnya menghasilkan siklus penuh (koprima).

**Kapan:** teorema Euler, ukuran grup `(Z/nZ)*`, jumlah `gcd` lewat `φ` (file 09 Mobius). Sieve `φ[1..n]` linear. Jangan `O(n log n)` gcd per query jika `n` besar.

**Proses:** `n = 12 = 2^2 · 3`.

```
φ(12)=12*(1-1/2)*(1-1/3)=12*1/2*2/3=4
```

Yang koprima: 1,5,7,11. Ya empat.

`n=7` prima: `φ=6`. `n=p^k`: `φ=p^k - p^{k-1}`. `φ(8)=4` (1,3,5,7).

Sieve `n=10`:

```
i=2: kurangi kelipatan 2: φ[2]-=1 →1, φ[4]-=2 →2, φ[6]-=3 →2, φ[8]-=4 →4, φ[10]-=5 →4
...
```

Lebih aman rumus SPF: `φ[i] = φ[i/p] * p` jika `p^2 | i`, else `φ[i/p]*(p-1)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

vector<int> sieve_phi(int n) {
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    for (int i = 2; i <= n; i++)
        if (p[i] == i)
            for (int j = i; j <= n; j += i)
                p[j] -= p[j] / i;
    return p;
}

int main() {
    cout << phi(1) << ' ' << phi(7) << ' ' << phi(12) << ' ' << phi(8) << '\n';
    // 1 6 4 4
    auto a = sieve_phi(12);
    for (int i = 1; i <= 12; i++) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** `φ(1)=1` bukan 0; `res -= res/p` vs `res = res/p*(p-1)` (sama jika dikerjakan benar); overflow `n` 64-bit di `i*i`; sieve mengubah `p[i]` sebelum dipakai sebagai “prima” — pola `if (p[i]==i)` wajib sebelum kelipatan, dan kelipatan memakai rumus `-= p[j]/i` pada nilai **sekarang**, itu benar untuk totient sieve standar.

**Kompleksitas:** satu `n` `O(√n)`. Sieve `O(n log log n)`. Memori sieve `O(n)`.

---

## Teorema Euler dan Fermat kecil

**Teori:** Euler: jika `gcd(a,m)=1` maka `a^{φ(m)} ≡ 1 (mod m)`. Fermat: `m` prima, `a^{m-1} ≡ 1 (mod m)` jika `m` tidak membagi `a`. Dipakai mereduksi eksponen: `a^e ≡ a^{e mod φ(m)} (mod m)` **hanya jika** `gcd(a,m)=1`. Jika tidak koprima, perlu hati-hati (kadang `e ≥ φ` plus syarat lain / CRT). Analoginya: pangkat di grup hingga berulang setiap ukuran grup.

**Kapan:** `a^b` dengan `b` raksasa (string 10^5 digit), mengurangi eksponen. Jangan mengurangi `e % (m-1)` jika `m` tidak prima. Jangan jika `gcd(a,m)>1` tanpa pecah modulus.

**Proses:** `3^8 mod 7`. `7` prima, `φ=6`. `8 % 6 = 2`. `3^2=9≡2`. Langsung `3^8=6561`, `6561/7`: 7*937=6559, sisa 2. Cocok.

`2^{10} mod 10`. `gcd(2,10)=2 ≠ 1`. `φ(10)=4`. `10%4=2`, `2^2=4`, tetapi `2^{10}=1024 ≡ 4` kebetulan. `2^5=32≡2`, `5%4=1`, `2^1=2` kebetulan lagi. `2^6=64≡4`, `6%4=2`, `4` ok. Tidak selalu aman untuk semua komposit; rumus Euler mensyaratkan koprima.

`4^{2} mod 10 = 16≡6`. `gcd(4,10)=2`. `2 % φ(10)=2`, `4^2≡6`, `4^{2}` memang 6. `4^3=64≡4`, `3%4=3`, `4^3≡4`. Berbahaya mengandalkan tanpa syarat.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    if (n > 1) res -= res / n;
    return res;
}

ll modpow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

// b diberikan sebagai string, gcd(a,m)=1
ll pow_string(ll a, const string& b, ll m) {
    ll ph = phi(m), e = 0;
    for (char c : b) e = (e * 10 + (c - '0')) % ph;
    return modpow(a, e, m);
}

int main() {
    cout << modpow(3, 8, 7) << ' ' << modpow(3, 2, 7) << '\n'; // 2 2
    cout << pow_string(3, string("8"), 7) << '\n';             // 2
    return 0;
}
```

Kalau `gcd(a,m)≠1`, jangan `pow_string` ini. Pecah lewat CRT atau hitung hati-hati.

**Jebakan:** mereduksi eksponen selalu `% (MOD-1)` padahal MOD komposit; `a` dan `m` tidak koprima; `φ` salah hitung.

**Kompleksitas:** `φ` `O(√m)`, pangkat `O(log e)`, string eksponen `O(|b|)`.

---

## Miller-Rabin

**Teori:** uji prima probabilistik / deterministik untuk 64-bit. Tulis `n-1 = 2^s · d`, `d` ganjil. Untuk saksi `a`, hitung `a^d mod n`. Lolos jika hasil 1 atau di suatu titik `a^{2^k d} ≡ -1`. Jika bukan, `n` komposit pasti. Jika lolos semua saksi dari himpunan tetap, `n < 2^64` dijamin prima. Analoginya: saksi menanyai “apakah kamu berlaku seperti prima di grup”; satu jawaban salah = ketahuan bohong.

**Kapan:** `n ≤ 10^18`, banyak query, Pollard butuh uji prima. Jangan trial `√(1e18)` di loop ketat. Jangan saksi acak 2-3 kali jika kamu butuh deterministik 64-bit — pakai daftar di bawah.

**Proses:** `n=91=7*13`. `n-1=90=2*45`. `s=1,d=45`. Saksi `a=2`: `2^{45} mod 91`.

Hitung `2^{45} mod 91`. `2^6=64`, `2^7=37`, ... atau binpow. `2^{45} = 35184372088832`. Mod 91: sebenarnya `2^6≡64`, kita percaya kode. Diketahui `2^{45} ≡ 57 (mod 91)` bukan 1, dan `2^{90}≡1` tetapi `2^{45}≠-1` (yaitu ≠90). `s=1` hanya satu peluang `-1`. 57 ≠ 1 dan ≠ 90 → komposit. Ketahuan.

`n=97`. `96=32*3=2^5 * 3`. `2^3=8 ≠1, 8^2=64, 64^2=15, ...` akan lolos saksi 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mulmod(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

ll modpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool witness(ll a, ll n, ll s, ll d) {
    ll x = modpow(a % n, d, n);
    if (x == 1 || x == n - 1) return false; // bukan saksi jahat
    for (int i = 1; i < s; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return false;
    }
    return true;                           // komposit
}

bool is_prime_mr(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
        if (n % p == 0) return n == p;
    }
    ll d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    // saksi deterministik 64-bit
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        if (witness(a, n, s, d)) return false;
    }
    return true;
}

int main() {
    cout << is_prime_mr(91) << '\n';       // 0
    cout << is_prime_mr(97) << '\n';       // 1
    cout << is_prime_mr(1e9 + 7) << '\n';  // 1
    cout << is_prime_mr(1e9 + 6) << '\n';  // 0
    cout << is_prime_mr(9223372036854775783LL) << '\n'; // prima dekat 2^63, 1
    return 0;
}
```

Saksi tujuh angka itu cukup untuk seluruh `uint64`. Alternatif: `{2,3,5,7,11,13,17,19,23,29,31,37}`.

**Jebakan:** `a*b % m` overflow tanpa `__int128`; `n` genap tidak disaring (tetap jalan, tetapi buang waktu); `modpow` `int`; saksi `a ≥ n` tanpa `a%n`; memakai 1 saksi acak lalu klaim pasti prima.

**Kompleksitas:** `O(k log^2 n)` dengan `k` saksi (≈7). Cukup cepat untuk 1e5 uji 64-bit.

---

## Pollard Rho

**Teori:** faktorisasi `n ≤ 10^18` yang komposit. Jalan acak `x → x^2 + c mod n`, cari `d = gcd(|x-y|, n)` dengan `y` “kura-kura-kelinci” atau batch Brent. Jika `1 < d < n`, `d` faktor. Lalu rekursi. Prima dideteksi Miller-Rabin dulu. Analoginya: dua orang berlari di lintasan modulo `n`; selisih mereka kelipatan faktor tersembunyi lebih cepat daripada `√n` trial.

**Kapan:** faktorisasi 64-bit, 1..puluhan query, atau `n` sampai 1e18 beberapa ratus kali. Jangan untuk `n` 1024-bit (kriptografi). Jangan Rho tanpa uji prima — loop tak habis pada prima.

**Proses:** `n=91`. Misal `c=1`, `x0=2`.

```
f(x)=x^2+1 mod 91
x=2, y=2
kelinci dua langkah, kura satu:
ini implementasi Floyd. Kita lihat gcd|x-y|.
Nilai konkret bergantung c dan start.
Salah satu run: ketemu 7 atau 13.
91/7=13, selesai.
```

Simulasi pendek `c=1`, `x=2`:

```
2 → 5 → 26 → 40 → 16 → 74 → 16  (siklus?)
74^2+1=5476+1=5477, 5477/91=60*91=5460, sisa 17. Mari pakai kode, bukan tebak.
```

Yang penting: setelah ketemu `d=7`, faktor `7` dan `13`, keduanya prima.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mulmod(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

ll modpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

bool witness(ll a, ll n, ll s, ll d) {
    ll x = modpow(a % n, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int i = 1; i < s; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return false;
    }
    return true;
}

bool is_prime_mr(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
        if (n % p == 0) return n == p;
    ll d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; s++; }
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        if (witness(a, n, s, d)) return false;
    }
    return true;
}

ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        ll c = rng() % (n - 1) + 1;
        ll x = rng() % n, y = x, d = 1;
        auto f = [&](ll v) { return (mulmod(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = std::gcd(llabs(x - y), n);
        }
        if (d != n) return d;
    }
}

void faktor_rho(ll n, vector<ll>& out) {
    if (n == 1) return;
    if (is_prime_mr(n)) {
        out.push_back(n);
        return;
    }
    ll d = pollard(n);
    faktor_rho(d, out);
    faktor_rho(n / d, out);
}

int main() {
    vector<ll> f;
    faktor_rho(91, f);
    sort(f.begin(), f.end());
    for (ll x : f) cout << x << ' ';       // 7 13
    cout << '\n';
    f.clear();
    faktor_rho(84, f);
    sort(f.begin(), f.end());
    for (ll x : f) cout << x << ' ';       // 2 2 3 7
    cout << '\n';
    return 0;
}
```

**Jebakan:** Rho pada prima (tidak ketemu `d`); `gcd` 32-bit; overflow kuadrat; tidak membagi 2 dulu; lupa sort faktor; `c=0` jelek — acak ulang.

**Kompleksitas:** harapan `O(n^{1/4} polylog)` per faktor. Praktis `n=1e18` biasanya < 50 ms per angka, kadang lebih jika semiprima ketat.

---

## Peta keputusan bab ini

```
gcd / lcm / ax+by=c     → Euclid / exgcd
prima satu n ≤ 1e12     → trial √n
prima banyak n ≤ 1e7    → sieve / linear sieve
prima n ≤ 1e18          → Miller-Rabin
faktor banyak n ≤ 1e7   → SPF
faktor n ≤ 1e18         → Pollard + MR
a^e mod m               → modpow, bukan pow()
bagi modular, m prima   → Fermat a^{m-2}
bagi modular, m umum    → exgcd, butuh gcd=1
C(n,k) n≤1e6 m prima    → fact + invfact
φ(n)                    → rumus faktor / sieve
```

| modulus | invers | nCr | catatan |
| --- | --- | --- | --- |
| `1e9+7` | Fermat | precompute | paling umum |
| `998244353` | Fermat | precompute | NTT (file 09) |
| komposit | exgcd | Lucas / CRT | jangan Fermat |
| `1` | — | — | semua 0 |

---

## Ringkasan

1. Euclid = sisa bagi berulang. LCM = bagi dulu, baru kali.
2. Exgcd memberi koefisien Bézout: invers dan Diophantine.
3. Sieve menyiapkan prima dan SPF; trial / MR / Rho memakai skala `n` yang berbeda.
4. Modular: normalisasi negatif, `ll` / `__int128` sebelum `%`.
5. Invers ada iff koprima. Fermat hanya untuk modulus prima.
6. `nCr` = tiga kali tabel, bukan lima kali `for` di `int`.

Lanjut ke [09 CRT, Catalan, matrix, XOR basis, FFT](09-number-crt-catalan-matrix-fft.md).
