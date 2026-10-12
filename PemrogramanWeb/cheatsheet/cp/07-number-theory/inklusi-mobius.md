# Inklusi-eksklusi dan fungsi Mobius

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **103–105**. Tanda plus-minus pada syarat dan pada kisi pembagi.

> **Ide satu kalimat:** inklusi-eksklusi memperbaiki hitungan ganda; Mobius adalah tanda itu yang sudah dikemas untuk pembagi, sehingga `gcd = 1` dan inversi jumlah jadi rumus siap pakai.

Terkait: [sieve](sieve-gcd.md) untuk linear `μ`, [nCr](modular-ncr.md) untuk derangement / surjektif.

## Daftar isi

- [Inklusi-eksklusi dua dan tiga](#inklusi-eksklusi-dua-dan-tiga)
- [IE mask umum](#ie-mask-umum)
- [Derangement](#derangement)
- [Surjektif lewat IE](#surjektif-lewat-ie)
- [Stars-and-bars berbatas](#stars-and-bars-berbatas)
- [Fungsi Mobius](#fungsi-mobius)
- [Sieve Mobius](#sieve-mobius)
- [Inversi Mobius](#inversi-mobius)
- [Pasangan koprima dan gcd](#pasangan-koprima-dan-gcd)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Inklusi-eksklusi dua dan tiga

**Teori:** `|A ∪ B| = |A| + |B| − |A ∩ B|`. Tiga himpunan: tambah tunggal, kurang pasangan, tambah irisan tiga. Umum: `Σ (−1)^{|S|+1} |∩_{i∈S} A_i|`. Elemen di tepat `r` himpunan dihitung `C(r,1) − C(r,2) + … = 1`. Analoginya: absensi ganda di dua klub harus dikurangi sekali.

**Kapan:** “habis dibagi 2 atau 3 atau 5”, union syarat. `m` syarat dengan `m ≤ 20` enumerasi mask. Jangan `m = 30` tanpa struktur.

**Proses:** berapa angka `1..30` habis 2, 3, atau 5?

```
|A2| = 15, |A3| = 10, |A5| = 6
|A2∩A3| = 5   (6,12,18,24,30)
|A2∩A5| = 3   (10,20,30)
|A3∩A5| = 2   (15,30)
|ketiga| = 1  (30)
union = 15+10+6 -5-3-2 +1 = 22
```

Buang yang tidak habis 2,3,5: 1,7,11,13,17,19,23,29 = 8. `30 − 8 = 22`.

Tiga klub: 12 di A, 9 di B, 8 di C, 5 AB, 4 AC, 3 BC, 2 ABC.

```
union = 12+9+8 -5-4-3 +2 = 19
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll union3(ll A, ll B, ll C, ll AB, ll AC, ll BC, ll ABC) {
    return A + B + C - AB - AC - BC + ABC;
}

int main() {
    FASTIO;
    cout << union3(15, 10, 6, 5, 3, 2, 1) << '\n'; // 22
    cout << union3(12, 9, 8, 5, 4, 3, 2) << '\n';  // 19
    return 0;
}
```

**Jebakan:** tanda `(-1)^{|S|}` vs `{|S|+1}`; menghitung irisan salah (LCM vs kali); double-count manual.

**Kompleksitas:** `O(1)` untuk 3 himpunan.

---

## IE mask umum

**Teori:** `m` syarat, loop `mask = 1 .. 2^m−1`. Untuk tiap mask, bentuk LCM (atau produk jika syarat koprima / prima), tambah `tanda * floor(n / lcm)`. Tanda `+` jika popcount ganjil. Analoginya: setiap subset syarat adalah satu suku IE.

Jika `p_i` tidak koprima, **harus LCM**, bukan kali. `floor(n/12)` untuk “habis 4 dan 6”, bukan `floor(n/24)`.

**Kapan:** `m ≤ 20`, “berapa yang habis salah satu `p_i`”. Jangan `m = 25` naif (`3e7` masih bisa, `m = 30` berat).

**Proses:** `n = 30`, `p = {2, 3, 5}`.

```
mask 001  l=2   + 15
mask 010  l=3   + 10
mask 011  l=6   - 5
mask 100  l=5   + 6
mask 101  l=10  - 3
mask 110  l=15  - 2
mask 111  l=30  + 1
jumlah 22
```

`n = 100`, `{4, 6}`: LCM(4,6)=12, bukan 24.

```
+ floor(100/4) + floor(100/6) - floor(100/12)
= 25 + 16 - 8 = 33
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll gcd_iter(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm_ll(ll a, ll b) {
    return a / gcd_iter(a, b) * b;
}

ll habis_atau(ll n, const vector<ll>& p) {
    int m = (int)p.size();
    ll ans = 0;
    for (int mask = 1; mask < (1 << m); mask++) {
        ll l = 1;
        bool ov = false;
        for (int i = 0; i < m && !ov; i++)
            if (mask & (1 << i)) {
                if (l > n / p[i] && p[i] > 0) {
                    // cek LCM overflow vs n
                    ll g = gcd_iter(l, p[i]);
                    if (l / g > n / p[i]) ov = true;
                    else l = l / g * p[i];
                } else {
                    l = lcm_ll(l, p[i]);
                }
            }
        if (ov || l > n) continue;
        ll tanda = (__builtin_popcount(mask) % 2) ? 1 : -1;
        ans += tanda * (n / l);
    }
    return ans;
}

int main() {
    FASTIO;
    cout << habis_atau(30, {2, 3, 5}) << '\n'; // 22
    cout << habis_atau(100, {4, 6}) << '\n';   // 33
    return 0;
}
```

**Jebakan:** kali bukan LCM; overflow `l *= p[i]`; tanda terbalik; `mask = 0` ikut terhitung.

**Kompleksitas:** `O(2^m · m)`.

---

## Derangement

**Teori:** `!n` = permutasi tanpa titik tetap. Rumus: `!n = n! Σ_{k=0}^n (−1)^k / k!`. Rekurens: `!n = (n − 1) [!(n−1) + !(n−2)]` atau `!n = n · !(n−1) + (−1)^n`. Analoginya: setiap orang tidak mendapat hadiah sendiri.

**Kapan:** “tidak ada yang tetap”, hat-check, mapping tanpa fixed point. Mod prima: `fact[n] * Σ invfact[k] * tanda`.

**Proses:** `n = 3`.

```
3! (1 - 1 + 1/2 - 1/6) = 6 - 6 + 3 - 1 = 2
```

Dua: `2,3,1` dan `3,1,2`. `n = 4`: `24 (1 -1 +1/2 -1/6 +1/24) = 24-24+12-4+1 = 9`.

```
!0=1
!1=0
!2=1
!3=2
!4=9
!5=44
!6=265
```

Cek rekurens: `!4 = 3 (!3 + !2) = 3(2+1)=9`. `!5 = 4(9+2)=44`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

ll derange(int n) {
    ll d = 1; // !0
    for (int i = 1; i <= n; i++)
        d = i * d + (i % 2 ? -1 : 1);
    return d;
}

ll derange_mod(int n) {
    vector<ll> fact(n + 1), invfact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    auto modpow = [&](ll a, ll e) {
        ll r = 1;
        while (e) {
            if (e & 1) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    };
    invfact[n] = modpow(fact[n], MOD - 2);
    for (int i = n; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    ll s = 0;
    for (int k = 0; k <= n; k++) {
        ll t = invfact[k];
        if (k & 1) s = (s - t + MOD) % MOD;
        else s = (s + t) % MOD;
    }
    return fact[n] * s % MOD;
}

int main() {
    FASTIO;
    cout << derange(3) << ' ' << derange(4) << ' ' << derange(5) << '\n';
    // 2 9 44
    cout << derange_mod(5) << '\n'; // 44
    return 0;
}
```

**Jebakan:** `!0 = 1`; overflow `ll` cepat (`!20` sudah besar); tanda `(-1)^k`; `derange` `int` vs `ll`.

**Kompleksitas:** `O(n)` atau `O(n + log MOD)`.

---

## Surjektif lewat IE

**Teori:** fungsi `n` objek berbeda → `k` kotak berlabel, onto: `k! S(n, k) = Σ_{j=0}^k (−1)^{k−j} C(k, j) j^n`. IE: mulai dari `k^n`, kurangi satu kotak kosong, tambah dua kosong, … Analoginya: semua pewarnaan `k` warna, buang yang tidak memakai semua warna.

**Kapan:** “tiap kelompok tidak kosong dan bernama”, “onto”. Jangan `k^n` jika kosong dilarang. `n, k ≤ 1e6` perlu hati-hati: `j^n` pakai `modpow`, `C(k,j)` hanya untuk `j ≤ k`.

**Proses:** `n = 3`, `k = 2`.

```
2^3 = 8
C(2,1)*1^3 = 2
C(2,0)*0^3 = 0
surjektif = 8 - 2 = 6
```

Enam: tiap fungsi yang bukan konstan. `2! S(3,2) = 2 * 3 = 6`.

`n = 4`, `k = 2`: `16 − 2 = 14`. `2! * 7 = 14`.

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

ll surjektif(int n, int k) {
    if (k < 0 || n < 0) return 0;
    if (k == 0) return n == 0;
    vector<ll> fact(k + 1), invfact(k + 1);
    fact[0] = 1;
    for (int i = 1; i <= k; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[k] = modpow(fact[k], MOD - 2);
    for (int i = k; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    auto C = [&](int a, int b) {
        return fact[a] * invfact[b] % MOD * invfact[a - b] % MOD;
    };
    ll ans = 0;
    for (int j = 0; j <= k; j++) {
        ll t = C(k, j) * modpow(j, n) % MOD;
        if ((k - j) & 1) ans = (ans - t + MOD) % MOD;
        else ans = (ans + t) % MOD;
    }
    return ans;
}

int main() {
    FASTIO;
    cout << surjektif(3, 2) << '\n'; // 6
    cout << surjektif(4, 2) << '\n'; // 14
    cout << surjektif(4, 4) << '\n'; // 24
    return 0;
}
```

**Jebakan:** `0^n` untuk `n = 0` harus 1; tanda `(-1)^{k-j}`; `k > n` hasil 0 (kecuali `0,0`).

**Kompleksitas:** `O(k + k log n)`.

---

## Stars-and-bars berbatas

**Teori:** `x1 + … + xk = n`, `0 ≤ xi ≤ r`. Tanpa batas atas: `C(n + k − 1, k − 1)`. IE: kurangi kasus suatu `xi ≥ r+1`. Substitusi `xi' = xi − (r+1)`, jumlah jadi `n − (r+1)`, lalu stars-and-bars lagi. Tambah dua variabel yang keduanya `≥ r+1`, dst. Analoginya: tiap piring paling banyak `r` kue; jika satu piring curang, ganti variabel.

**Kapan:** bound seragam, `k ≤ 20` jika IE mask, atau `k` kecil. Jangan DP `O(n k r)` jika rumus cukup.

**Proses:** `x+y+z = 5`, `0 ≤ tiap ≤ 3`.

Tanpa batas: `C(7, 2) = 21`. Kurangi satu variabel `≥ 4`: `x' + y + z = 1`, `C(3, 2) = 3`, ada 3 pilihan variabel → −9. Dua variabel `≥ 4`: `5 − 8 < 0` → 0. Hasil 12.

Daftar: maksimum 3. Total komposisi non-neg jumlah 5 dengan tiap ≤ 3. Cek: (3,2,0) dan permutasi 6; (3,1,1) permutasi 3; (2,2,1) permutasi 3. `6+3+3=12`.

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
        for (int i = n; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }
};

ll bounded_stars(int n, int k, int r, Comb& cb) {
    ll ans = 0;
    for (int j = 0; j <= k; j++) {
        ll sisa = n - (ll)j * (r + 1);
        if (sisa < 0) break;
        ll t = cb.C(k, j) * cb.C((int)sisa + k - 1, k - 1) % MOD;
        if (j & 1) ans = (ans - t + MOD) % MOD;
        else ans = (ans + t) % MOD;
    }
    return ans;
}

int main() {
    FASTIO;
    Comb cb(40);
    cout << bounded_stars(5, 3, 3, cb) << '\n'; // 12
    cout << cb.C(7, 2) << '\n';                 // 21 tanpa batas
    return 0;
}
```

**Jebakan:** substitusi `r` bukan `r+1`; `C(sisa+k-1, k-1)` saat `k = 0`; overflow `j*(r+1)`.

**Kompleksitas:** `O(k)` setelah tabel.

---

## Fungsi Mobius

**Teori:** `μ(1) = 1`, `μ(n) = 0` jika ada kuadrat prima, `μ(n) = (−1)^k` jika `n` hasil `k` prima berbeda. Sifat kunci: `Σ_{d|n} μ(d) = [n == 1]`. Analoginya: Möbius adalah “tanda inklusi-eksklusi siap pakai” pada kisi pembagi.

**Kapan:** jumlah `gcd(i, j) == 1`, ganti syarat `gcd == k` menjadi `k | gcd` lalu Mobius. Jangan trial `μ` per query jika banyak `n` kecil — sieve.

**Proses:**

| n | faktor | μ |
|---:|---|---:|
| 1 | — | 1 |
| 2 | 2 | −1 |
| 3 | 3 | −1 |
| 4 | 2^2 | 0 |
| 5 | 5 | −1 |
| 6 | 2·3 | 1 |
| 7 | 7 | −1 |
| 8 | 2^3 | 0 |
| 9 | 3^2 | 0 |
| 10 | 2·5 | 1 |
| 30 | 2·3·5 | −1 |

`Σ_{d|6} μ(d) = μ(1)+μ(2)+μ(3)+μ(6) = 1−1−1+1 = 0` karena 6 ≠ 1. `Σ_{d|1} μ = 1`.

`Σ_{d|4} μ = μ(1)+μ(2)+μ(4) = 1−1+0 = 0`.

**Kode:** `μ` satu angka dari faktor.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int mu_one(ll n) {
    if (n == 1) return 1;
    int k = 0;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            n /= i;
            k++;
            if (n % i == 0) return 0;
        }
    }
    if (n > 1) k++;
    return (k & 1) ? -1 : 1;
}

int main() {
    FASTIO;
    for (int i = 1; i <= 10; i++) cout << mu_one(i) << ' ';
    cout << '\n'; // 1 -1 -1 0 -1 1 -1 0 0 1
    return 0;
}
```

**Jebakan:** `μ(1)`; kuadrat tidak di-nol-kan; `k` menghitung pangkat bukan prima berbeda.

**Kompleksitas:** `O(√n)` per angka.

---

## Sieve Mobius

**Teori:** linear sieve: prima baru `μ[p] = −1`; jika `q | i` maka `μ[i*q] = 0` dan `break`; else `μ[i*q] = −μ[i]`. Sieve klasik: mulai `μ[i]=1`, untuk prima `p` kalikan −1 pada kelipatan, nol-kan kelipatan `p^2`.

**Kapan:** `μ[1..n]`, `n ≤ 1e7`. Fondasi rumus pasangan koprima.

**Proses:** `n = 10`, linear.

```
i=2 prima μ=-1, tandai 4 (q| i → μ4=0), 6 (μ=-μ2=1)
i=3 prima μ=-1, 6 sudah, 9 μ=0
i=5 prima μ=-1, 10 μ=1
```

Hasil: `1,-1,-1,0,-1,1,-1,0,0,1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> sieve_mu(int n) {
    vector<int> mu(n + 1), p;
    vector<char> vis(n + 1, 0);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            p.push_back(i);
            mu[i] = -1;
        }
        for (int q : p) {
            if ((ll)i * q > n) break;
            vis[i * q] = 1;
            if (i % q == 0) {
                mu[i * q] = 0;
                break;
            }
            mu[i * q] = -mu[i];
        }
    }
    return mu;
}

int main() {
    FASTIO;
    auto mu = sieve_mu(30);
    for (int i = 1; i <= 10; i++) cout << mu[i] << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** `break` saat `q | i` wajib (supaya kuadrat → 0); `μ[1]`; `vis` tidak menandai prima.

**Kompleksitas:** `O(n)` waktu, `O(n)` memori.

---

## Inversi Mobius

**Teori:** jika `g(n) = Σ_{d|n} f(d)` maka `f(n) = Σ_{d|n} μ(d) g(n/d)`. Versi kelipatan: `g(n) = Σ_{n|d} f(d)` punya inversi `f(n) = Σ_{n|d} μ(d/n) g(d)`. Karena `Σ_{d|n} μ(d) = [n==1]`, konvolusi Dirichlet dengan `μ` menginversi fungsi konstan 1. Analoginya: prefix-pembagi dibalik seperti difference array di kisi.

**Kapan:** kamu bisa menghitung `g` (lebih mudah, misalnya “kelipatan”) dan butuh `f` (“tepat”). Jangan tertukar arah `d|n` vs `n|d`.

**Proses:** misal `g(n) = Σ_{d|n} φ(d) = n`. Inversi: `φ(n) = Σ_{d|n} μ(d) (n/d)`.

`n = 6`:

```
μ(1)*6 + μ(2)*3 + μ(3)*2 + μ(6)*1
= 6 + (−1)*3 + (−1)*2 + 1*1 = 6-3-2+1 = 2
```

`φ(6) = 2` (1 dan 5). Cocok.

`n = 12`:

```
d|12: 1,2,3,4,6,12
μ: 1,-1,-1,0,1,0
g=n/d: 12,6,4,3,2,1
jumlah: 12-6-4+0+2+0 = 4 = φ(12)
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> sieve_mu(int n);

// definisi ulang singkat
vector<int> build_mu(int n) {
    vector<int> mu(n + 1), pr;
    vector<char> vis(n + 1, 0);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pr.push_back(i);
            mu[i] = -1;
        }
        for (int q : pr) {
            if ((ll)i * q > n) break;
            vis[i * q] = 1;
            if (i % q == 0) {
                mu[i * q] = 0;
                break;
            }
            mu[i * q] = -mu[i];
        }
    }
    return mu;
}

ll phi_via_mu(int n, const vector<int>& mu) {
    ll ans = 0;
    for (int d = 1; d * d <= n; d++) {
        if (n % d) continue;
        ans += (ll)mu[d] * (n / d);
        if (d * d != n) ans += (ll)mu[n / d] * d;
    }
    return ans;
}

int main() {
    FASTIO;
    auto mu = build_mu(20);
    cout << phi_via_mu(6, mu) << ' ' << phi_via_mu(12, mu) << '\n'; // 2 4
    return 0;
}
```

**Jebakan:** arah inversi tertukar; `μ` diindeks `n/d` vs `d`; overflow `t * t` di rumus lain.

**Kompleksitas:** `O(√n)` per `n` jika enumerasi pembagi, atau `O(n log n)` untuk semua `n` lewat kelipatan.

---

## Pasangan koprima dan gcd

**Teori:** banyak pasangan `1 ≤ i, j ≤ n` dengan `gcd(i, j) = 1` adalah `Σ_{d=1}^n μ(d) floor(n/d)^2`. Turunan: `[gcd=1] = Σ_{d|gcd} μ(d)`, lalu tukar urutan. Untuk `gcd = k`: pasang `i' = i/k`, `j' = j/k` ≤ `floor(n/k)`, lalu koprima. Jumlah semua pasangan tertimbang `f(gcd)` sering jadi `Σ μ * F(floor)`.

Analoginya: Mobius menyaring kelipatan menjadi “tepat 1”.

**Kapan:** coprime pairs, `Σ gcd(i,j)`, `Σ lcm(i,j)` (dengan rumus `ij/gcd`). `n ≤ 1e7` naif `O(n)`, `n ≤ 1e12` pakai blocks `floor` `O(√n)`.

**Proses:** `n = 3`. Total 9 pasangan. Bukan koprima: `(2,2),(3,3)` saja? Juga tidak: `(2,2)` gcd2, `(3,3)` gcd3. `(1,1)` gcd1. Jadi 7 koprima.

```
μ(1)*9 + μ(2)*1 + μ(3)*1 = 9 - 1 - 1 = 7
```

`n = 4`:

```
floor(4/d): 4,2,1,1
μ: 1,-1,-1,0
4^2 - 2^2 - 1^2 + 0 = 16-4-1 = 11
```

Daftar: 16 pasangan minus `(2,2)(2,4)(4,2)(4,4)(3,3)` = 5, `16-5=11`. Ya.

`gcd = 2`, `n = 6`: `n/k = 3`, koprima di `1..3` = 7. Jadi 7 pasangan dengan `gcd = 2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> build_mu(int n) {
    vector<int> mu(n + 1), pr;
    vector<char> vis(n + 1, 0);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pr.push_back(i);
            mu[i] = -1;
        }
        for (int q : pr) {
            if ((ll)i * q > n) break;
            vis[i * q] = 1;
            if (i % q == 0) {
                mu[i * q] = 0;
                break;
            }
            mu[i * q] = -mu[i];
        }
    }
    return mu;
}

ll coprime_pairs(int n, const vector<int>& mu) {
    ll ans = 0;
    for (int d = 1; d <= n; d++) {
        ll t = n / d;
        ans += (ll)mu[d] * t * t;
    }
    return ans;
}

ll gcd_eq_k(int n, int k, const vector<int>& mu) {
    return coprime_pairs(n / k, mu);
}

int main() {
    FASTIO;
    auto mu = build_mu(20);
    cout << coprime_pairs(3, mu) << '\n'; // 7
    cout << coprime_pairs(4, mu) << '\n'; // 11
    cout << gcd_eq_k(6, 2, mu) << '\n';   // 7
    return 0;
}
```

Blocks `floor` (Dirichlet): untuk `n` besar, `l = 1; while (l <= n) { v = n/l; r = n/v; … l = r+1; }` agar semua `d` dengan `n/d` sama diproses sekali. Perlu `Σ μ` prefix.

**Jebakan:** `t * t` overflow (`n = 1e9` → `1e18` muat `ll`, `2e9` rawan); rumus `i ≤ j` vs semua pasangan; `n/k` integer.

**Kompleksitas:** `O(n)` atau `O(√n)` dengan blocks. Memori `O(n)` untuk `μ`.

---

## Peta keputusan

```
union syarat m ≤ 20          → IE mask + LCM
tidak ada titik tetap        → derangement
onto / kotak bernama penuh   → IE surjektif / k! S(n,k)
stars berbatas atas          → IE substitusi
[n==1] pada pembagi          → Σ μ(d)
g(n)=Σ_{d|n} f(d)            → inversi Mobius
gcd==1 atau gcd==k           → Σ μ floor^2
```

| tanda | sumber |
|---|---|
| `(-1)^{|S|+1}` | IE himpunan |
| `μ(n)` | `n` square-free |
| `(-1)^k / k!` | derangement |
| `(-1)^{k-j} C(k,j)` | surjektif |

---

## Ringkasan

1. IE: tambah ganjil, kurang genap. LCM jika syarat tidak koprima.
2. Derangement dan surjektif adalah IE pada “posisi / warna kosong”.
3. `μ` nol pada kuadrat, `±1` pada square-free, dan jumlah di pembagi adalah `[n==1]`.
4. Inversi membalik jumlah di kisi pembagi; `φ` adalah contoh baku.
5. Coprime pairs = `Σ μ(d) floor(n/d)^2`; `gcd = k` = rumus itu pada `n/k`.

Matrix expo dan basis XOR: [matrix-xor.md](matrix-xor.md).
