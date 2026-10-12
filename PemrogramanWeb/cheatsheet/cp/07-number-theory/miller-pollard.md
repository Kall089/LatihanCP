# Miller-Rabin dan Pollard Rho (edukasi 64-bit)

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **095**. Uji prima dan faktor untuk `n ≤ 10^18` pada soal kontes.

> **Ide satu kalimat:** Miller-Rabin menanyai saksi tetap sampai `n < 2^64` terbukti prima; Pollard Rho mencari faktor non-trivial lewat jalan acak `x^2 + c`, lalu rekursi.

Sebelumnya: [exgcd & CRT](ext-euclid-crt.md). Untuk `n ≤ 1e7` pakai [sieve](sieve-gcd.md), bukan file ini.

**Lingkup edukasi:** hanya bilangan kontes 64-bit. Bukan kriptanalisis, bukan memecah RSA, bukan kunci atau flag. Implementasi di bawah untuk soal CP (`n ≤ 1e18`, puluhan sampai ratusan query).

## Daftar isi

- [Kenapa trial gagal](#kenapa-trial-gagal)
- [Miller-Rabin: teori](#miller-rabin-teori)
- [Saksi deterministik 64-bit](#saksi-deterministik-64-bit)
- [Simulasi saksi](#simulasi-saksi)
- [Pollard Rho: teori](#pollard-rho-teori)
- [Simulasi Rho pada 91](#simulasi-rho-pada-91)
- [Faktorisasi gabungan](#faktorisasi-gabungan)
- [φ dan d(n) dari faktor 64-bit](#φ-dan-dn-dari-faktor-64-bit)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Kenapa trial gagal

**Teori:** trial sampai `√n` untuk `n = 10^18` adalah `10^9` langkah. Satu query masih berat di batas waktu ketat; `10^5` query mustahil. Sieve sampai `10^18` tidak muat memori. Jadi uji prima harus sublinear pada `n`, dan faktor harus lebih dekat ke `n^{1/4}` daripada `n^{1/2}`.

**Kapan:** pindah ke file ini jika `n > 1e12` atau banyak `n > 1e9` yang butuh faktor. Tetap trial / SPF jika `n ≤ 1e7` atau sedikit `n ≤ 1e12`.

**Proses:** bandingkan skala.

```
n = 10^12, √n = 10^6          trial sekali OK
n = 10^18, √n = 10^9          trial sekali rawan TLE
n = 10^18, n^{1/4} = 10^{4.5} ≈ 3e4   harapan Rho
```

`10^9+7` prima: trial sampai `≈ 31623` masih cepat. `10^18 + 3` butuh alat lain.

**Kode:** pengingat batas, bukan alat utama.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool trial_ok_sekali(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    FASTIO;
    cout << trial_ok_sekali(1000000007LL) << '\n'; // 1, √n ≈ 3e4
    // Jangan panggil trial_ok_sekali(1e18) di loop 1e5.
    return 0;
}
```

**Jebakan:** `i * i` overflow; mengira “sekali 1e18” selalu aman; sieve `vector` berukuran `1e18`.

**Kompleksitas:** trial `O(√n)` — alasan file ini ada.

---

## Miller-Rabin: teori

**Teori:** tulis `n − 1 = 2^s · d` dengan `d` ganjil. Untuk saksi `a`, hitung `x0 = a^d mod n`. `n` lolos saksi ini jika `x0 ≡ 1` atau ada `0 ≤ r < s` dengan `a^{2^r d} ≡ −1 (mod n)`. Jika suatu kuadrat menjadi 1 tanpa melalui −1, atau tidak pernah 1 / −1, maka `n` **pasti komposit**. Jika lolos, `n` mungkin prima atau strong pseudoprime terhadap `a`.

Analoginya: saksi menanyai apakah `n` berlaku seperti prima di grup perkalian. Satu jawaban salah = ketahuan bohong. Beberapa saksi tetap cukup untuk seluruh `uint64`.

Syarat `n` ganjil > 2. Genap cukup diuji habis 2.

Perkalian harus `__int128`: `a * b % n` pada 64-bit overflow.

**Kapan:** `n ≤ 10^18`, banyak query, Pollard butuh uji prima dulu. Jangan 1–2 saksi acak jika kamu butuh deterministik 64-bit. Jangan trial `√(1e18)` di loop ketat.

**Proses:** pecah `n − 1` untuk beberapa `n`.

```
n = 91,  n-1 = 90 = 2^1 * 45     s=1, d=45
n = 97,  n-1 = 96 = 2^5 * 3      s=5, d=3
n = 25,  n-1 = 24 = 2^3 * 3      s=3, d=3
n = 17,  n-1 = 16 = 2^4 * 1      s=4, d=1
```

Untuk prima, `a^{n-1} ≡ 1` (Fermat) dan rantai kuadrat dari `a^d` hanya boleh menyentuh −1 lalu 1.

**Kode:** pecah `n-1` saja dulu.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<ll, int> split_n1(ll n) {
    ll d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    return {d, s};
}

int main() {
    FASTIO;
    for (ll n : {91LL, 97LL, 25LL, 17LL}) {
        auto [d, s] = split_n1(n);
        cout << n << ' ' << s << ' ' << d << '\n';
    }
    return 0;
}
```

**Jebakan:** lupa `n < 2`; `d` genap tersisa; `modpow` `int`; `a % n == 0` (saksi kelipatan `n`).

**Kompleksitas:** pecah `O(log n)`.

---

## Saksi deterministik 64-bit

**Teori:** himpunan saksi tetap membuat uji **deterministik** untuk seluruh rentang 64-bit. Dua daftar yang sering dipakai:

1. `{2, 325, 9375, 28178, 450775, 9780504, 1795265022}` — tujuh angka, cukup `n < 2^64`.
2. `{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}` — dua belas prima kecil, juga cukup 64-bit.

Ini hasil pemeriksaan matematis rentang, bukan “acak sampai beruntung”. Untuk edukasi kontes, salin daftar itu apa adanya. Jangan menambah saksi acak lalu mengklaim pasti.

Filter prima kecil dulu (`2..29`) mempercepat komposit genap / kelipatan kecil.

**Kapan:** semua uji `n` 64-bit di soal. Jangan kurangi daftar “supaya singkat” tanpa tahu batas jaminan (`n < 3e9` bisa lebih sedikit saksi, tetapi mudah salah).

**Proses:** kerangka saksi `a` terhadap `n`.

```
x = a^d mod n
jika x == 1 atau x == n-1 → lolos
ulangi s-1 kali: x = x^2 mod n
    jika x == n-1 → lolos
gagal → komposit
```

Jika semua saksi lolos → prima (untuk `n` 64-bit dan daftar di atas).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mulmod(ll a, ll b, ll m) {
    return (ll)((__int128)a * b % m);
}

ll modpow(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
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
    return true; // komposit
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
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        if (witness(a, n, s, d)) return false;
    }
    return true;
}

int main() {
    FASTIO;
    cout << is_prime_mr(91) << '\n';              // 0
    cout << is_prime_mr(97) << '\n';              // 1
    cout << is_prime_mr(1e9 + 7) << '\n';         // 1
    cout << is_prime_mr(1e9 + 6) << '\n';         // 0
    cout << is_prime_mr(1) << is_prime_mr(2) << '\n'; // 0 1
    return 0;
}
```

**Jebakan:** `a * b % m` tanpa `__int128`; saksi `a ≥ n` tanpa `a % n`; 1 saksi acak lalu klaim pasti; `n` genap tidak difilter (tetap benar, buang waktu); `modpow` overflow.

**Kompleksitas:** `O(k log^2 n)` dengan `k ≈ 7`. Cukup untuk `1e5` uji 64-bit.

---

## Simulasi saksi

**Teori:** melihat angka membuat cabang “lolos / gagal” konkret. Komposit 91 sering dipakai karena kecil dan `s = 1` (hanya satu peluang −1).

**Kapan:** debug implementasi. Jika `91` lolos saksi 2, `modpow` atau `witness` salah.

**Proses:** `n = 91`, `s = 1`, `d = 45`, `a = 2`.

```
x = 2^45 mod 91
2^6  = 64
2^7  = 128 ≡ 37
2^8  = 74
2^9  = 57
2^{10}= 23
...
diketahui 2^45 ≡ 57 (mod 91)
57 ≠ 1 dan 57 ≠ 90
s=1, tidak ada kuadrat lagi
→ saksi 2 menolak 91. Komposit.
```

`n = 25`, `s = 3`, `d = 3`, `a = 2`:

```
2^3 = 8 ≠ 1, ≠ 24
8^2 = 64 ≡ 14
14^2 = 196 ≡ 21  (196-2*25=196-50=146, 146-5*25=146-125=21)
21 ≠ 24
→ komposit (benar, 25=5^2)
```

`n = 97`, `d = 3`, `a = 2`:

```
2^3 = 8
8^2 = 64
64^2 = 4096. 4096 / 97: 97*42=4074, sisa 22
22^2 = 484. 97*5=485, sisa 96 ≡ -1  → lolos
```

**Kode:** cetak rantai kuadrat.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mulmod(ll a, ll b, ll m) { return (ll)((__int128)a * b % m); }

ll modpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

void rantai(ll a, ll n) {
    ll d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    ll x = modpow(a, d, n);
    cout << "x0=" << x << '\n';
    for (int i = 1; i < s; i++) {
        x = mulmod(x, x, n);
        cout << "x" << i << '=' << x << '\n';
    }
}

int main() {
    FASTIO;
    rantai(2, 91);
    rantai(2, 97);
    return 0;
}
```

**Jebakan:** menghitung `2^45` di `double`; membandingkan −1 dengan `−1` bertanda bukan `n-1`.

**Kompleksitas:** sama `modpow`.

---

## Pollard Rho: teori

**Teori:** untuk `n` komposit 64-bit, jalan `x → x^2 + c (mod n)` di ruang `Z/nZ` yang “pecah” menurut faktor. Floyd: kura-kura satu langkah, kelinci dua langkah; `d = gcd(|x − y|, n)`. Jika `1 < d < n`, `d` faktor non-trivial. Jika `d = n`, ganti `c` dan titik awal. Prima harus dideteksi Miller-Rabin **sebelum** Rho, kalau tidak loop tidak habis.

Analoginya: dua pelari di lintasan modulo `n`; selisih mereka lebih cepat kelipatan faktor tersembunyi daripada trial `√n`.

Ini algoritma harapan, bukan kriptanalisis. Untuk semiprima ketat dekat `1e18`, waktu fluktuatif tetapi biasanya cukup untuk batas kontes jika query tidak ribuan.

Brent (opsional) mengganti Floyd dengan langkah 1, 2, 4, … dan batch `gcd` — sering lebih cepat, tidak wajib.

**Kapan:** faktorisasi 64-bit, puluhan sampai ratusan `n`. Jangan untuk bilangan ratusan bit. Jangan Rho tanpa uji prima. Jangan klaim “memecah kunci”.

**Proses:** kerangka.

```
jika n genap → 2
jika n prima (MR) → sendiri
ulang:
    pilih c, x acak
    y = x
    selama d == 1:
        x = f(x)
        y = f(f(y))
        d = gcd(|x-y|, n)
    jika d ≠ n → faktor
rekursi pada d dan n/d
```

**Kode:** fungsi `pollard` saja; gabungan di seksi berikutnya.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mulmod(ll a, ll b, ll m) { return (ll)((__int128)a * b % m); }

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

int main() {
    FASTIO;
    // edukasi: faktor 91 pasti 7 atau 13
    ll d = pollard(91);
    cout << d << ' ' << 91 / d << '\n';
    return 0;
}
```

**Jebakan:** Rho pada prima; `gcd` 32-bit; overflow kuadrat; tidak membagi 2 dulu; `c = 0` sering jelek; `llabs` pada `LLONG_MIN`.

**Kompleksitas:** harapan `O(n^{1/4} polylog)` per faktor.

---

## Simulasi Rho pada 91

**Teori:** `n = 91 = 7 · 13` kecil, `c` dan start bisa dipaku supaya jejak bisa dihitung tangan. Ini untuk paham, bukan untuk submit (di kontes `c` diacak).

**Kapan:** menelusuri kenapa `gcd(|x-y|, n)` tiba-tiba > 1.

**Proses:** `f(x) = x^2 + 1 mod 91`, start `x = y = 2`.

```
langkah  x (kura)  y (kelinci)  |x-y|  gcd
1        f(2)=5     f(f(2))=26   21     gcd(21,91)=7
```

Ketemu `d = 7` di langkah pertama. `91 / 7 = 13`. Selesai.

Jalur `x` saja: `2 → 5 → 26 → 40 → 16 → 74 → 17 → 17^2+1=290 ≡ 17?` tidak perlu. Yang penting selisih kura-kelinci.

Jika suatu `c` gagal (`d = n` terus), ganti `c`. Itu normal.

**Kode:** jejak deterministik.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mulmod(ll a, ll b, ll m) { return (ll)((__int128)a * b % m); }

int main() {
    FASTIO;
    ll n = 91, c = 1, x = 2, y = 2, d = 1;
    auto f = [&](ll v) { return (mulmod(v, v, n) + c) % n; };
    int step = 0;
    while (d == 1 && step < 20) {
        x = f(x);
        y = f(f(y));
        d = std::gcd(llabs(x - y), n);
        step++;
        cout << step << ' ' << x << ' ' << y << ' ' << d << '\n';
    }
    return 0;
}
```

Keluaran pertama harus `1 5 26 7`.

**Jebakan:** `f(f(y))` ditulis `f(y)` dua kali pada variabel yang sudah berubah salah; `% n` setelah `+ c` bisa `n` jika jumlah = `n` — `(x+c)%n` aman.

**Kompleksitas:** contoh `O(1)` praktis.

---

## Faktorisasi gabungan

**Teori:** bungkus: genap → 2; Miller-Rabin → prima; else Pollard lalu rekursi. Keluaran daftar prima (dengan pengulangan pangkat). Sort jika soal ingin urut.

**Kapan:** satu fungsi `faktor(n)` untuk `n ≤ 1e18` di soal counting / φ / CRT pecah modulus. Jangan rekursi tanpa memperkecil `n`.

**Proses:** `n = 84`.

```
84 genap → 2, sisanya 42
42 genap → 2, sisanya 21
21 komposit, Rho → 3 atau 7
3 dan 7 prima
84 = 2 · 2 · 3 · 7
```

`n = 1` → kosong. `n` prima → satu elemen.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll mulmod(ll a, ll b, ll m) { return (ll)((__int128)a * b % m); }

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
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        if (witness(a, n, s, d)) return false;
    }
    return true;
}

ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    mt19937_64 rng(n ^ 0x9e3779b97f4a7c15ULL);
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
    FASTIO;
    vector<ll> f;
    faktor_rho(91, f);
    sort(f.begin(), f.end());
    for (ll x : f) cout << x << ' ';
    cout << '\n'; // 7 13
    f.clear();
    faktor_rho(84, f);
    sort(f.begin(), f.end());
    for (ll x : f) cout << x << ' ';
    cout << '\n'; // 2 2 3 7
    return 0;
}
```

**Jebakan:** lupa sort; `n = 1`; rekursi `d` dan `d` (salah, harus `n/d`); seed acak membuat WA flaky pada tes yang mengharapkan urutan tertentu — sort selalu.

**Kompleksitas:** praktis `n = 1e18` biasanya puluhan ms per angka, kadang lebih pada semiprima ketat.

---

## φ dan d(n) dari faktor 64-bit

**Teori:** setelah daftar prima, gabung pangkat. `φ(n) = n Π (1 − 1/p)`, `d(n) = Π (a+1)`. Sama seperti file sieve, tetapi sumber faktornya Rho, bukan SPF.

**Kapan:** satu `n ≤ 1e18`, butuh `φ(n)` atau jumlah pembagi. Jangan sieve sampai `n`.

**Proses:** `n = 84 = 2^2 · 3 · 7`.

```
φ(84) = 84 * 1/2 * 2/3 * 6/7 = 24
d(84) = 3 * 2 * 2 = 12
```

Yang koprima dengan 84: 1, 5, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 53, 55, 59, 61, 67, 71, 73, 79, 83 — hitung 24? 1..83 step, lebih mudah percaya rumus plus cek kecil: `φ(12)=4` sudah diuji di file modular.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll phi_from(vector<ll> f) {
    sort(f.begin(), f.end());
    ll n = 1, res = 1;
    for (ll p : f) n *= p;
    res = n;
    for (size_t i = 0; i < f.size();) {
        ll p = f[i];
        while (i < f.size() && f[i] == p) i++;
        res -= res / p;
    }
    return res;
}

ll d_from(vector<ll> f) {
    sort(f.begin(), f.end());
    ll d = 1;
    for (size_t i = 0; i < f.size();) {
        ll p = f[i];
        int a = 0;
        while (i < f.size() && f[i] == p) {
            i++;
            a++;
        }
        d *= (a + 1);
    }
    return d;
}

int main() {
    FASTIO;
    vector<ll> f = {2, 2, 3, 7};
    cout << phi_from(f) << ' ' << d_from(f) << '\n'; // 24 12
    return 0;
}
```

**Jebakan:** mengalikan `n` overflow jika kamu membentuk `n` ulang dari faktor tanpa perlu; lupa menggabungkan pangkat; `φ` dikurangi dua kali untuk `p` yang sama.

**Kompleksitas:** `O(ω log)` setelah faktor, `ω` jumlah prima dengan pengulangan.

---

## Peta keputusan

```
n ≤ 1e7 banyak query     → sieve / SPF
n ≤ 1e12 sedikit         → trial √n
n ≤ 1e18 uji prima       → Miller-Rabin saksi tetap
n ≤ 1e18 faktor          → MR + Pollard Rho
n ratusan bit / kunci    → di luar lingkup file ini
```

| langkah | wajib | jika dilompati |
|---|---|---|
| saring 2 | ya | Rho lambat pada genap |
| MR sebelum Rho | ya | loop pada prima |
| `__int128` | ya | WA senyap |
| sort faktor | jika output urut | WA tes |

---

## Ringkasan

1. Trial dan sieve tidak untuk banyak `n = 1e18`.
2. Miller-Rabin deterministik 64-bit memakai daftar saksi tetap, bukan 1 acak.
3. `witness` gagal → komposit pasti; lolos semua saksi → prima di rentang ini.
4. Pollard Rho edukasi: Floyd + `gcd`, ganti `c` jika gagal.
5. Selalu MR dulu, rekursi `d` dan `n/d`, sort jika perlu.
6. File ini untuk soal kontes 64-bit, bukan memecah kriptografi.

Pencacahan: [catalan-stirling.md](catalan-stirling.md).
