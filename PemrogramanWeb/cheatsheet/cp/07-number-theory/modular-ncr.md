# Aritmetika modular, invers Fermat, dan nCr

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **090**. Kelas sisa, pangkat, invers, kombinasi.

> **Ide satu kalimat:** modulus menjaga jawaban di `{0, …, m−1}`; pembagian modular adalah kali invers; jika `m` prima, invers = `a^{m−2}` dan `C(n, k)` jadi tiga kali tabel faktorial.

Sebelumnya: [sieve & GCD](sieve-gcd.md). Lanjut: [exgcd & CRT](ext-euclid-crt.md).

## Daftar isi

- [Aritmetika modular](#aritmetika-modular)
- [Pangkat modular](#pangkat-modular)
- [Invers Fermat](#invers-fermat)
- [Invers 1..n linear](#invers-1n-linear)
- [nCr prakomputasi](#ncr-prakomputasi)
- [nPr dan stars-and-bars](#npr-dan-stars-and-bars)
- [Lucas](#lucas)
- [Fungsi Euler totient](#fungsi-euler-totient)
- [Teorema Euler dan Fermat kecil](#teorema-euler-dan-fermat-kecil)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Aritmetika modular

**Teori:** `a ≡ b (mod m)` artinya `m | (a − b)`. Kelas sisa `{0, 1, …, m−1}` tertutup untuk `+`, `−`, `*`. Boleh `%` kapan saja sebelum operasi itu. Pembagian **tidak** boleh `%` langsung: `(a / b) % m ≠ (a % m) / (b % m)`. Analoginya jam 12 jam: `9 + 4 = 1`, bukan 13.

Di C++, `(-5) % 3` bisa `-2`, bukan 1. Matematika ingin perwakilan non-negatif. Normalisasi: `((a % m) + m) % m`.

Perkalian `1e9 * 1e9 = 1e18` muat `ll`. `1e18 * 1e18` tidak — pakai `__int128` atau pecah modulus.

**Kapan:** hampir semua counting, `10^9+7` atau `998244353`. Prefix sum mod. Jangan `double`. Jangan `%` setelah overflow `int * int`. Jangan `pow` dari `<cmath>`.

**Proses:** `m = 7`.

```
(10 + 8) % 7 = 18 % 7 = 4
(10 % 7 + 8 % 7) % 7 = (3 + 1) % 7 = 4

(10 * 8) % 7 = 80 % 7 = 3
(3 * 1) % 7 = 3

(10 - 8) % 7 = 2
(3 - 1) % 7 = 2

(-5) % 7 di C++ bisa -5
norm = (-5 + 7) % 7 = 2    karena -5 = -7 + 2
```

`submod(3, 10, 7) = (3 - 10 + 7) % 7 = 0` karena `3 - 10 = -7 ≡ 0`.

`1e9+7` prima, enak untuk Fermat. `1e9+6` komposit — Fermat gagal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

ll norm(ll a, ll m = MOD) {
    a %= m;
    if (a < 0) a += m;
    return a;
}

ll addmod(ll a, ll b, ll m = MOD) { return (norm(a, m) + norm(b, m)) % m; }
ll submod(ll a, ll b, ll m = MOD) { return (norm(a, m) - norm(b, m) + m) % m; }
ll mulmod(ll a, ll b, ll m = MOD) {
    return (ll)((__int128)norm(a, m) * norm(b, m) % m);
}

int main() {
    FASTIO;
    cout << addmod(10, 8, 7) << '\n';       // 4
    cout << mulmod(10, 8, 7) << '\n';       // 3
    cout << submod(3, 10, 7) << '\n';       // 0
    cout << norm(-5, 7) << '\n';            // 2
    cout << mulmod(1000000000LL, 1000000000LL) << '\n';
    return 0;
}
```

**Jebakan:** `%` negatif; `int` overflow sebelum `%`; `pow` double; `(a - b) % m` tanpa `+ m`; `MOD` bertipe `int` lalu `a + b` overflow dulu; menulis `a * b % m` saat `a, b` dekat `1e18`.

**Kompleksitas:** `O(1)` per operasi. `__int128` sedikit lebih mahal, tetap `O(1)`.

---

## Pangkat modular

**Teori:** `a^e mod m` dengan kuadrat berulang. Baca bit `e` dari rendah: jika bit hidup, kalikan ke hasil; selalu kuadratkan basis. `e = 0` → `1 % m`. `m = 1` → 0. Analoginya: `a^{13} = a^8 * a^4 * a^1` karena `13 = 1101_2`.

**Kapan:** invers Fermat, hashing, `2^n mod m`, matrix (lihat [matrix-xor.md](matrix-xor.md)). `e` sampai `10^18`. Jangan `for (i = 0; i < e; i++)`.

**Proses:** `3^13 mod 100`. `13 = 1101_2`.

```
res=1, a=3
bit0 1: res=3,   a=9
bit1 0:          a=81
bit2 1: res=3*81=243 ≡ 43, a=81*81=6561 ≡ 61
bit3 1: res=43*61=2623 ≡ 23
```

Cek: `3^13 = 1594323`, `1594323 % 100 = 23`.

`2^10 mod 1000 = 1024 % 1000 = 24`. `5^0 mod 7 = 1`. `2^10 mod 1 = 0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll modpow(ll a, ll e, ll m) {
    if (m == 1) return 0;
    ll res = 1 % m;
    a %= m;
    if (a < 0) a += m;
    while (e > 0) {
        if (e & 1) res = (ll)((__int128)res * a % m);
        a = (ll)((__int128)a * a % m);
        e >>= 1;
    }
    return res;
}

int main() {
    FASTIO;
    cout << modpow(3, 13, 100) << '\n'; // 23
    cout << modpow(2, 10, 1000) << '\n'; // 24
    cout << modpow(5, 0, 7) << '\n';     // 1
    cout << modpow(2, 10, 1) << '\n';    // 0
    return 0;
}
```

**Jebakan:** `pow(3, 13)` double; `a * a` overflow; `e` negatif (itu invers, bukan pangkat); `1 % m` saat `m = 1`; basis negatif tanpa normalisasi.

**Kompleksitas:** `O(log e)` kali, `O(1)` memori.

---

## Invers Fermat

**Teori:** jika `m` prima dan `gcd(a, m) = 1`, maka `a^{m−2} ≡ a^{−1} (mod m)`. Fermat kecil: `a^{m−1} ≡ 1`, jadi `a · a^{m−2} ≡ 1`. Analoginya: di dunia mod `m`, kali `a` bisa dibatalkan oleh suatu `b`.

Ini **hanya** untuk modulus prima. Jika `m` komposit, pakai [exgcd](ext-euclid-crt.md). Jika `m | a`, invers tidak ada.

**Kapan:** `MOD = 1e9+7` atau `998244353`, bagi modular, `invfact`. Jangan jika `m` komposit. Jangan jika `a ≡ 0`.

**Proses:** `a = 3`, `m = 11`. `3^{9} mod 11` seharusnya invers.

```
3^1 = 3
3^2 = 9
3^4 = 81 ≡ 4     (81 - 7*11 = 81 - 77)
3^8 = 16 ≡ 5
3^9 = 3^8 * 3 ≡ 15 ≡ 4
```

`3 * 4 = 12 ≡ 1 (mod 11)`. Ya, invers = 4.

`a = 6`, `m = 11`: `6 * 2 = 12 ≡ 1`, invers 2. Cek Fermat: `6^9 mod 11`.

`inv_fermat(2, 8)` sampah: 8 bukan prima, `gcd(2, 8) ≠ 1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll modpow(ll a, ll e, ll m) {
    ll res = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) res = (ll)((__int128)res * a % m);
        a = (ll)((__int128)a * a % m);
        e >>= 1;
    }
    return res;
}

ll inv_fermat(ll a, ll m) {
    return modpow(a, m - 2, m); // m prima
}

int main() {
    FASTIO;
    cout << inv_fermat(3, 11) << '\n'; // 4
    cout << inv_fermat(6, 11) << '\n'; // 2
    const ll MOD = 1000000007LL;
    ll i = inv_fermat(10, MOD);
    cout << (ll)((__int128)10 * i % MOD) << '\n'; // 1
    return 0;
}
```

**Jebakan:** `m` tidak prima; `a ≡ 0`; menghitung `m - 2` saat `m = 1`; pakai Fermat untuk `10^9+6`; banyak invers `1..n` dihitung satu-satu `O(n log m)` padahal ada `O(n)`.

**Kompleksitas:** `O(log m)` per invers.

---

## Invers 1..n linear

**Teori:** `inv[1] = 1`, lalu `inv[i] = m - (m / i) * inv[m % i] % m`. Turunan: tulis `m = q i + r` dengan `r = m % i`, `q = m / i`. Maka `q i ≡ -r (mod m)`, kali `inv[i] inv[r]`: `q inv[r] ≡ -inv[i]`. Jadi `inv[i] ≡ -q inv[r]`. Analoginya: sisa `m % i` sudah punya invers, pinjam untuk membangun invers `i`.

**Kapan:** butuh semua invers `1..n` dengan `n ≤ 1e6`, `m` prima. Lebih cepat daripada `n` kali Fermat. Jangan jika `m` tidak prima.

**Proses:** `m = 11`, hitung `inv[1..10]`.

```
inv[1] = 1
i=2: q=5, r=1, inv[2] = 11 - 5*1 = 6     cek 2*6=12≡1
i=3: q=3, r=2, inv[3] = 11 - 3*6 = 11-18 → (11-18+11)=4
     3*4=12≡1
i=4: q=2, r=3, inv[4] = 11 - 2*4 = 3      4*3=12≡1
i=5: q=2, r=1, inv[5] = 11 - 2*1 = 9      5*9=45≡1 (44+1)
```

Tabel: `1, 6, 4, 3, 9, 2, 8, 7, 5, 10` karena pasangan `(1,1),(2,6),(3,4),(5,9),(7,8),(10,10)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 11;

vector<ll> inv_linear(int n, ll m) {
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = m - (m / i) * inv[m % i] % m;
    return inv;
}

int main() {
    FASTIO;
    auto inv = inv_linear(10, 11);
    for (int i = 1; i <= 10; i++) cout << inv[i] << ' ';
    cout << '\n'; // 1 6 4 3 9 2 8 7 5 10
    for (int i = 1; i <= 10; i++)
        cout << (i * inv[i] % 11) << ' ';
    cout << '\n'; // semua 1
    return 0;
}
```

**Jebakan:** `inv[0]`; `m` komposit; rumus tanpa `% m` pada suku kedua; `n ≥ m` — invers `i` yang kelipatan `m` tidak ada.

**Kompleksitas:** `O(n)` waktu, `O(n)` memori.

---

## nCr prakomputasi

**Teori:** `C(n, k) = n! / (k! (n − k)!)` untuk `0 ≤ k ≤ n`, else 0. Mod prima `p`: `fact[i]` dan `invfact[i] = (i!)^{−1}`, lalu `C(n, k) = fact[n] * invfact[k] * invfact[n − k]`. Hitung `invfact[n] = fact[n]^{p−2}`, mundur `invfact[i] = invfact[i+1] * (i+1)`. Analoginya: pilih `k` dari `n` kursi; urutan di dalam kelompok tidak dihitung.

**Kapan:** counting, Catalan, stars and bars `C(n + k − 1, k)`. `n ≤ 1e6`, `p` prima. `n ≥ p` hati-hati: `n! ≡ 0`, mungkin perlu Lucas. Jangan hitung `n * (n−1) * …` di `int`. Jangan bagi `fact[k]` tanpa invers.

**Proses:** `C(5, 2) = 10`. `5! = 120`, `2! = 2`, `3! = 6`, `120 / 12 = 10`.

Tabel kecil:

```
C(0, 0) = 1
C(4, 0..4) = 1 4 6 4 1
C(6, 3) = 20
C(10, 3) = 120
```

`C(5, 2) mod 7 = 3`. Faktorial mod 7: `1, 1, 2, 6, 24≡3, 120≡1`. `invfact[2] = inv(2) = 4`, `invfact[3] = inv(6) = 6` karena `6 * 6 = 36 ≡ 1`. `1 * 4 * 6 = 24 ≡ 3`.

`C(3, 5) = 0`. `C(n, 0) = C(n, n) = 1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
        for (int i = n; i >= 1; i--)
            invfact[i - 1] = invfact[i] * i % MOD;
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }
    ll P(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[n - k] % MOD;
    }
};

int main() {
    FASTIO;
    Comb cb(20);
    cout << cb.C(5, 2) << '\n';                 // 10
    cout << cb.C(6, 3) << '\n';                 // 20
    cout << cb.C(4, 0) << ' ' << cb.C(4, 4) << '\n'; // 1 1
    cout << cb.C(3, 5) << '\n';                 // 0
    cout << cb.P(5, 2) << '\n';                 // 20
    return 0;
}
```

**Jebakan:** `k > n` tidak di-return 0; `MOD` tidak prima; `n ≥ MOD` fact jadi 0; membangun `Comb(1e7)` tiap tes; `invfact[0]` salah; overflow `fact[i] = fact[i-1] * i` jika `MOD` dan `i` `int` — pakai `ll`.

**Kompleksitas:** prakomputasi `O(n + log MOD)`, query `O(1)`, memori `O(n)`.

---

## nPr dan stars-and-bars

**Teori:** `P(n, k) = n! / (n − k)!` = barisan `k` objek berbeda dari `n`. Stars and bars: banyak solusi non-negatif `x1 + … + xk = n` adalah `C(n + k − 1, k − 1)`. Jika tiap `xi ≥ 1`, substitusi `yi = xi − 1` → `C(n − 1, k − 1)` untuk `n ≥ k`. Analoginya: `n` bintang dan `k − 1` sekat.

**Kapan:** “berapa barisan”, “bagi kue identik ke piring”, bound atas `xi ≤ r` (lalu inklusi-eksklusi, lihat [inklusi-mobius.md](inklusi-mobius.md)). Jangan stars-and-bars jika objek berbeda — itu `k^n` atau Stirling.

**Proses:** `x + y + z = 5`, `x, y, z ≥ 0`. `C(5 + 3 − 1, 2) = C(7, 2) = 21`.

Daftar singkat `z` dari 0 sampai 5: jumlah cara `(x+y = 5−z)` = 6, 5, 4, 3, 2, 1 → 21.

Jika `x, y, z ≥ 1` dan jumlah 5: `C(4, 2) = 6`. Partisi: `(1,1,3)` dan permutasi (3), `(1,2,2)` dan permutasi (3).

`P(5, 2) = 5 * 4 = 20`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
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
        for (int i = n; i >= 1; i--)
            invfact[i - 1] = invfact[i] * i % MOD;
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }
    ll stars(int n, int k) { // x1+...+xk = n, xi >= 0
        if (k <= 0) return n == 0;
        return C(n + k - 1, k - 1);
    }
    ll stars_pos(int n, int k) { // xi >= 1
        if (n < k) return 0;
        return C(n - 1, k - 1);
    }
};

int main() {
    FASTIO;
    Comb cb(40);
    cout << cb.stars(5, 3) << '\n';     // 21
    cout << cb.stars_pos(5, 3) << '\n'; // 6
    return 0;
}
```

**Jebakan:** tertukar `C(n+k-1, k)` vs `C(n+k-1, k-1)` (sama hanya jika simetri kebetulan); `k = 0`; objek berbeda vs identik; bound `xi ≥ 0` vs `≥ 1`.

**Kompleksitas:** sama `Comb`, query `O(1)`.

---

## Lucas

**Teori:** untuk prima `p`, `C(n, k) mod p = Π C(n_i, k_i)` pada digit `n` dan `k` di basis `p`. Jika suatu `k_i > n_i`, hasil 0. Analoginya: pilih `k` benda dari `n` yang dikelompokkan basis `p` harus sah di tiap digit.

**Kapan:** `n` besar (`1e18`) tetapi `p` kecil (`≤ 1e6` supaya `Comb(p-1)` muat), atau `n ≥ p` sehingga faktorial mentah 0. Jangan Lucas untuk `MOD = 1e9+7` dengan `n < MOD` — prakomputasi biasa lebih sederhana.

**Proses:** `C(10, 3) mod 7`. `10 = 1 * 7 + 3`, `3 = 0 * 7 + 3`.

```
C(1, 0) * C(3, 3) = 1 * 1 = 1
```

Langsung: `C(10, 3) = 120`, `120 / 7 = 17 * 7 = 119`, sisa 1. Cocok.

`C(8, 4) mod 5`. `8 = 1 * 5 + 3`, `4 = 0 * 5 + 4`. `C(3, 4) = 0`. Memang `C(8, 4) = 70 ≡ 0 (mod 5)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll modpow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

struct CombP {
    ll p;
    vector<ll> fact, invfact;
    CombP(ll p_) : p(p_) {
        fact.resize(p);
        invfact.resize(p);
        fact[0] = 1;
        for (int i = 1; i < p; i++) fact[i] = fact[i - 1] * i % p;
        invfact[p - 1] = modpow(fact[p - 1], p - 2, p);
        for (int i = p - 1; i >= 1; i--)
            invfact[i - 1] = invfact[i] * i % p;
    }
    ll Csmall(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % p * invfact[n - k] % p;
    }
    ll C(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        ll ans = 1;
        while (n || k) {
            ans = ans * Csmall((int)(n % p), (int)(k % p)) % p;
            n /= p;
            k /= p;
        }
        return ans;
    }
};

int main() {
    FASTIO;
    CombP cb(7);
    cout << cb.C(10, 3) << '\n'; // 1
    CombP cb5(5);
    cout << cb5.C(8, 4) << '\n'; // 0
    return 0;
}
```

**Jebakan:** `p` tidak prima; membangun `fact` sampai `n` bukan `p`; lupa digit `k_i > n_i` → 0; memakai Lucas untuk modulus komposit.

**Kompleksitas:** prakomputasi `O(p)`, query `O(log_p n)`.

---

## Fungsi Euler totient

**Teori:** `φ(n)` = banyak `1 ≤ k ≤ n` dengan `gcd(k, n) = 1`. `φ(1) = 1`. Rumus: `φ(n) = n Π (1 − 1/p)` untuk prima `p | n`. Implementasi: `res = n`, untuk tiap `p` bagi habis `n`, `res -= res / p`. Analoginya: di lingkaran `n` titik, berapa langkah yang menghasilkan siklus penuh (koprima).

**Kapan:** teorema Euler, ukuran grup `(Z/nZ)*`, jumlah GCD lewat `φ` / Mobius. Sieve `φ[1..n]` linear. Jangan `O(n log n)` gcd per query jika `n` besar.

**Proses:** `n = 12 = 2^2 · 3`.

```
φ(12) = 12 * (1 - 1/2) * (1 - 1/3) = 12 * 1/2 * 2/3 = 4
```

Yang koprima: 1, 5, 7, 11.

`n = 7` prima: `φ = 6`. `n = p^k`: `φ = p^k − p^{k−1}`. `φ(8) = 4` (1, 3, 5, 7). `φ(1) = 1`.

Sieve: inisialisasi `φ[i] = i`, untuk setiap prima `p`, kurangi `φ[j] -= φ[j] / p` pada kelipatan `j`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    cout << phi(1) << ' ' << phi(7) << ' ' << phi(12) << ' ' << phi(8) << '\n';
    // 1 6 4 4
    auto a = sieve_phi(12);
    for (int i = 1; i <= 12; i++) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** `φ(1) = 1` bukan 0; overflow `i * i` pada 64-bit; sieve mengubah `p[i]` sebelum tes “apakah prima” — pola `if (p[i] == i)` wajib sebelum kelipatan.

**Kompleksitas:** satu `n` `O(√n)`. Sieve `O(n log log n)`, memori `O(n)`.

---

## Teorema Euler dan Fermat kecil

**Teori:** Euler: jika `gcd(a, m) = 1` maka `a^{φ(m)} ≡ 1 (mod m)`. Fermat: `m` prima, `a^{m−1} ≡ 1 (mod m)` jika `m` tidak membagi `a`. Reduksi eksponen: `a^e ≡ a^{e mod φ(m)} (mod m)` **hanya jika** koprima. Jika tidak koprima, pecah modulus atau hati-hati. Analoginya: pangkat di grup hingga berulang setiap ukuran grup.

**Kapan:** `a^b` dengan `b` raksasa (string digit), mengurangi eksponen. Jangan `e % (m − 1)` jika `m` tidak prima. Jangan jika `gcd(a, m) > 1` tanpa pecah.

**Proses:** `3^8 mod 7`. `7` prima, `φ = 6`. `8 % 6 = 2`. `3^2 = 9 ≡ 2`. Langsung `3^8 = 6561`, `6561 − 937 * 7 = 6561 − 6559 = 2`.

`2^{10} mod 10`. `gcd(2, 10) = 2 ≠ 1`. Euler tidak menjamin reduksi `% φ(10) = % 4`. Kebetulan kadang cocok, jangan diandalkan.

Eksponen string `"8"` untuk `3^8 mod 7`: baca digit `% 6` → 8 % 6 = 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
        if (e & 1) r = (ll)((__int128)r * a % m);
        a = (ll)((__int128)a * a % m);
        e >>= 1;
    }
    return r;
}

// b sebagai string, syarat gcd(a, m) = 1
ll pow_string(ll a, const string& b, ll m) {
    ll ph = phi(m), e = 0;
    for (char c : b) e = (e * 10 + (c - '0')) % ph;
    return modpow(a, e, m);
}

int main() {
    FASTIO;
    cout << modpow(3, 8, 7) << ' ' << modpow(3, 2, 7) << '\n'; // 2 2
    cout << pow_string(3, string("8"), 7) << '\n';             // 2
    return 0;
}
```

Kalau `gcd(a, m) ≠ 1`, jangan `pow_string` ini. Pecah lewat CRT atau hitung langsung jika eksponen kecil.

**Jebakan:** mereduksi selalu `% (MOD − 1)` padahal MOD komposit; `a` dan `m` tidak koprima; `φ` salah hitung; string eksponen tanpa `% phi`.

**Kompleksitas:** `φ` `O(√m)`, pangkat `O(log e)`, string `O(|b|)`.

---

## Peta keputusan

```
+ / - / * mod m          → norm, ll / __int128
a^e mod m                → modpow, bukan pow()
bagi, m prima            → Fermat a^{m-2}
banyak invers 1..n       → inv linear O(n)
bagi, m umum             → exgcd (file ext-euclid-crt)
C(n,k) n≤1e6 m prima     → fact + invfact
C(n,k) n besar p kecil   → Lucas
stars-and-bars           → C(n+k-1, k-1)
a^b, b string, koprima   → e %= φ(m)
φ(n)                     → rumus faktor / sieve
```

| modulus | invers | nCr | catatan |
|---|---|---|---|
| `1e9+7` | Fermat | precompute | paling umum |
| `998244353` | Fermat | precompute | NTT di [fft.md](fft.md) |
| komposit | exgcd | Lucas / CRT | jangan Fermat |
| `1` | — | — | semua 0 |

---

## Ringkasan

1. Normalisasi negatif. Kali besar pakai `__int128`.
2. Invers ada iff koprima. Fermat hanya untuk modulus prima.
3. `nCr` = tiga kali tabel, bukan lima kali `for` di `int`.
4. Invers `1..n` linear lebih hemat daripada `n` Fermat.
5. Lucas memecah digit basis `p` ketika `n ≥ p`.
6. Euler mereduksi eksponen hanya jika `gcd(a, m) = 1`.

Koefisien Bézout dan CRT: [ext-euclid-crt.md](ext-euclid-crt.md).
