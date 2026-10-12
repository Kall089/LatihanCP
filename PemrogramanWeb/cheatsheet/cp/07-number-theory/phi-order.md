# Euler totient, orde, dan diskrit log

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day **096–098**. Perluasan [φ singkat di modular-ncr](modular-ncr.md) dan [φ dari faktor 64-bit](miller-pollard.md): sifat multiplikatif, sieve, reduksi pangkat, orde, BSGS untuk persamaan kontes.

> **Ide satu kalimat:** `φ(n)` menghitung ukuran grup unit; `a^{φ(n)} ≡ 1` jika koprima; orde adalah periode terkecil; diskrit log di kontes dicari dengan baby-step giant-step, bukan untuk menyerang kunci kripto.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`.

## Daftar isi

- [Definisi dan rumus φ](#definisi-dan-rumus-φ)
- [Sifat multiplikatif](#sifat-multiplikatif)
- [Identitas jumlah totient](#identitas-jumlah-totient)
- [Sieve φ](#sieve-φ)
- [Iterasi dan jumlah](#iterasi-dan-jumlah)
- [Teorema Euler a^φ(n) ≡ 1](#teorema-euler-aφn--1)
- [Orde multiplikatif](#orde-multiplikatif)
- [Akar primitif kontes](#akar-primitif-kontes)
- [Diskrit log BSGS](#diskrit-log-bsgs)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Definisi dan rumus φ

**Teori:** `φ(n)` = banyak `k` di `{1, …, n}` dengan `gcd(k, n) = 1`. `φ(1) = 1` karena `gcd(1, 1) = 1`. Jika `n = Π p_i^{a_i}` maka

```
φ(n) = n * Π (1 − 1/p_i) = Π p_i^{a_i−1} (p_i − 1)
```

Implementasi trial: `res = n`, untuk tiap prima `p | n` bagi habis `n` lalu `res -= res / p`. Analoginya: buang kelipatan tiap prima, tetapi kelipatan dua prima terbuang dua kali — rumus sudah mengoreksi seperti inklusi.

**Kapan:** ukuran `(Z/nZ)*`, reduksi eksponen, jumlah GCD lewat `Σ φ`. Satu `n ≤ 1e12` trial `O(√n)`. `n ≤ 1e18` faktor dulu (lihat Pollard di file lain). Jangan `O(n)` gcd naif per query.

**Proses:** hitung beberapa nilai yang berbeda dari contoh `12` di file modular.

| n | faktor | rumus | φ(n) | unit |
|---:|---|---|---:|---|
| 1 | — | 1 | 1 | 1 |
| 9 | `3^2` | `9 − 3 = 6` | 6 | 1,2,4,5,7,8 |
| 15 | `3·5` | `15·2/3·4/5 = 8` | 8 | 1,2,4,7,8,11,13,14 |
| 16 | `2^4` | `16 − 8 = 8` | 8 | ganjil |
| 21 | `3·7` | `21·2/3·6/7 = 12` | 12 | 1,2,4,5,8,10,11,13,16,17,19,20 |
| 36 | `2^2·3^2` | `36·1/2·2/3 = 12` | 12 | 1,5,7,11,13,17,19,23,25,29,31,35 |
| 100 | `2^2·5^2` | `100·1/2·4/5 = 40` | 40 | — |

Cek `15`: dari 1..15 buang kelipatan 3 atau 5: buang 3,5,6,9,10,12,15 dan juga 3·5 sudah masuk. Sisa 8. Cocok.

`φ(p) = p−1` untuk prima. `φ(2p) = p−1` jika `p` ganjil prima: `φ(14) = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int main() {
    FASTIO;
    for (ll n : {1LL, 9, 15, 16, 21, 36, 100})
        cout << n << ' ' << phi(n) << '\n';
    // 1 1 / 9 6 / 15 8 / 16 8 / 21 12 / 36 12 / 100 40
    return 0;
}
```

**Jebakan:** `φ(1) = 0` salah; `p * p` overflow jika `n` dekat `2^63` — bandingkan `p <= n/p`; mengurangi `res/p` dua kali untuk pangkat yang sama; `int` untuk `n = 1e12`.

**Kompleksitas:** `O(√n)` waktu, `O(1)` memori.

---

## Sifat multiplikatif

**Teori:** `f` multiplikatif jika `gcd(a, b) = 1` ⇒ `f(ab) = f(a) f(b)`. `φ` multiplikatif: `φ(15) = φ(3)φ(5) = 2·4 = 8`. Tidak sepenuhnya multiplikatif: `φ(9) = 6 ≠ φ(3)φ(3) = 4`. Karena itu rumus diuraikan per pangkat prima, bukan dikali `φ(p)` sebanyak `a` kali.

Jika `gcd(a, b) = d > 1`, rumus koreksi: `φ(ab) = φ(a)φ(b) · d / φ(d)`. Cek `a = 6`, `b = 15`, `d = 3`: `φ(90) =? 2·8·3/2 = 24`. `90 = 2·3^2·5`, `φ = 90·1/2·2/3·4/5 = 24`. Cocok.

**Kapan:** menghitung `φ` setelah faktorisasi; CRT memecah modulus `n = Π p^a` lalu menggabungkan. Jangan kalikan `φ(p^a)` seolah `φ(p)^a`.

**Proses:** bangun `φ(60)` dari potongan koprima.

```
60 = 4 · 15, gcd(4,15)=1
φ(4)=2, φ(15)=8 → φ(60)=16

60 = 3 · 20, gcd=1
φ(3)=2, φ(20)=8 → 16

60 = 6 · 10, gcd=2
φ(6)=2, φ(10)=4, d=2, φ(d)=1
2·4·2/1 = 16
```

Unit mod 60: banyak 16. Contoh: 1,7,11,13,17,19,23,29,31,37,41,43,47,49,53,59.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

ll phi_ab(ll a, ll b) {
    ll d = std::gcd(a, b);
    return phi(a) * phi(b) / phi(d) * d;
}

int main() {
    FASTIO;
    cout << phi(3) * phi(5) << ' ' << phi(15) << '\n'; // 8 8
    cout << phi(3) * phi(3) << ' ' << phi(9) << '\n';  // 4 6  (bukan sama)
    cout << phi_ab(6, 10) << ' ' << phi(60) << '\n';   // 16 16
    cout << phi_ab(4, 15) << '\n';                     // 16
    return 0;
}
```

**Jebakan:** mengira `φ` sepenuhnya multiplikatif; membagi `φ(d)` dulu sehingga pecahan terpotong — di kode di atas `phi(a)*phi(b)` habis `phi(d)` secara teori, tetap pakai `ll`; `gcd = 0`.

**Kompleksitas:** sama trial per argumen.

---

## Identitas jumlah totient

**Teori:** `Σ_{d|n} φ(d) = n`. Kenapa: kelompokkan `{1, …, n}` menurut `gcd(k, n) = d`. Tulis `k = d · t` dengan `gcd(t, n/d) = 1`, banyaknya `φ(n/d)`. Jadi `Σ_{d|n} φ(n/d) = n`, ganti `e = n/d`. Analoginya: pecahan `k/n` dalam bentuk tereduksi `t/(n/d)` — setiap penyebut muncul `φ` kali.

Inversi Mobius membalik ini: `φ(n) = Σ_{d|n} μ(d) (n/d)`. Detail inversi di [mobius.md](mobius.md); di sini identitas dipakai sebagai tes sieve.

**Kapan:** verifikasi `φ[1..n]`; jumlah `gcd(i, n)` = `Σ_{d|n} d φ(n/d)`; soal “berapa pecahan tereduksi berpenyebut `n`”. Jangan menghitung `Σ φ` dengan loop `gcd` jika `n` besar.

**Proses:** `n = 20`. Pembagi: 1,2,4,5,10,20.

| d | φ(d) |
|---:|---:|
| 1 | 1 |
| 2 | 1 |
| 4 | 2 |
| 5 | 4 |
| 10 | 4 |
| 20 | 8 |

Jumlah 1+1+2+4+4+8 = 20.

`n = 9`: `φ(1)+φ(3)+φ(9) = 1+2+6 = 9`.

`n = 21`: `φ(1)+φ(3)+φ(7)+φ(21) = 1+2+6+12 = 21`.

Jumlah `gcd(k, 20)` untuk `k = 1..20`:

```
Σ d φ(20/d) = 1·8 + 2·4 + 4·4 + 5·2 + 10·1 + 20·1
= 8+8+16+10+10+20 = 72
```

Naif: tiap `k` `gcd` lalu jumlah — harus 72.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

vector<ll> divisors(ll n) {
    vector<ll> d;
    for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
        d.push_back(i);
        if (i * i != n) d.push_back(n / i);
    }
    sort(d.begin(), d.end());
    return d;
}

ll sum_phi_div(ll n) {
    ll s = 0;
    for (ll d : divisors(n)) s += phi(d);
    return s;
}

ll sum_gcd_to_n(ll n) {
    ll s = 0;
    for (ll d : divisors(n)) s += d * phi(n / d);
    return s;
}

int main() {
    FASTIO;
    cout << sum_phi_div(20) << ' ' << sum_phi_div(9) << ' ' << sum_phi_div(21) << '\n';
    // 20 9 21
    cout << sum_gcd_to_n(20) << '\n'; // 72
    ll naive = 0;
    for (int k = 1; k <= 20; k++) naive += std::gcd(k, 20);
    cout << naive << '\n'; // 72
    return 0;
}
```

**Jebakan:** menjumlah `φ(n/d)` tanpa menukar indeks; `sum gcd(i,j)` dua variabel bukan rumus ini; overflow `d * φ(n/d)` jika `n` besar.

**Kompleksitas:** `O(√n)` enumerasi pembagi plus `O(√n)` per `φ`.

---

## Sieve φ

**Teori:** dua pola. Klasik: isi `φ[i] = i`, untuk tiap `p` prima, pada kelipatan `j` lakukan `φ[j] -= φ[j]/p` sekali. Linear: saat `i * q` pertama kali, jika `q | i` maka `φ[i*q] = φ[i] * q` (pangkat naik), else `φ[i*q] = φ[i] * φ[q]`. Analoginya: setiap kelipatan “ketemu” prima `p` lalu dikurangi fraksi `1/p`.

**Kapan:** butuh seluruh `φ[1..n]`, `n ≤ 1e7`. Jangan trial per indeks. Jangan linear sieve sampai `1e8` jika memori ketat.

**Proses:** klasik sampai 10.

```
init  1 2 3 4 5 6 7 8 9 10
p=2   1 1 3 2 5 3 7 4 9 5
p=3   1 1 2 2 5 2 7 4 6 5
p=5   1 1 2 2 4 2 7 4 6 4
p=7   1 1 2 2 4 2 6 4 6 4
```

Cek: `φ(8)=4`, `φ(9)=6`, `φ(10)=4`. Linear menghasilkan baris yang sama.

`Σ_{i=1}^{10} φ(i) = 1+1+2+2+4+2+6+4+6+4 = 32`. Identitas: banyak pasangan `(k, i)` dengan `1 ≤ k ≤ i ≤ 10` dan `gcd(k, i) = 1`? Bukan itu; `Σ_{m=1}^n φ(m)` = banyak pecahan tereduksi `a/b` dengan `1 ≤ b ≤ n`, `0 < a ≤ b` kalau `φ(1)` menghitung `1/1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> sieve_phi(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int p = 2; p <= n; p++) if (phi[p] == p) {
        for (int j = p; j <= n; j += p) phi[j] -= phi[j] / p;
    }
    return phi;
}

vector<int> linear_phi(int n) {
    vector<int> phi(n + 1), pr;
    vector<char> vis(n + 1, 0);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pr.push_back(i);
            phi[i] = i - 1;
        }
        for (int q : pr) {
            if ((ll)i * q > n) break;
            vis[i * q] = 1;
            if (i % q == 0) {
                phi[i * q] = phi[i] * q;
                break;
            }
            phi[i * q] = phi[i] * (q - 1);
        }
    }
    return phi;
}

int main() {
    FASTIO;
    auto a = sieve_phi(10);
    auto b = linear_phi(10);
    for (int i = 1; i <= 10; i++) cout << a[i] << ' ';
    cout << '\n'; // 1 1 2 2 4 2 6 4 6 4
    for (int i = 1; i <= 10; i++) cout << b[i] << ' ';
    cout << '\n';
    cout << (a == b) << '\n'; // 1  (sama termasuk indeks 0)
    return 0;
}
```

**Jebakan:** `if (phi[p] == p)` harus sebelum mengubah kelipatan — itu tes “masih prima”; linear lupa `break` saat `q | i` sehingga `φ` salah di kuadrat; `phi[1]`; overflow `i * q`.

**Kompleksitas:** klasik `O(n log log n)`, linear `O(n)`, memori `O(n)`.

---

## Iterasi dan jumlah

**Teori:** `φ(n) < n` untuk `n ≥ 2`, jadi barisan `n, φ(n), φ(φ(n)), …` turun ke 1 dalam `O(log n)` langkah kasar (lebih ketat `O(log log n)` rata-rata, terburuk lebih longgar). Jumlah `Σ_{i=1}^n φ(i)` punya bentuk tertutup kira-kira `3n^2/π^2`. Prefix sieve: `pref[i] = pref[i-1] + φ[i]`.

Banyak pasangan `1 ≤ x, y ≤ n` dengan `gcd(x, y) = 1` **terurut termasuk urutan** = `2 Σ_{i=1}^n φ(i) − 1` (pasangan `(1,1)` sekali). Itu berbeda dari rumus Mobius `Σ μ(d) floor(n/d)^2` — keduanya harus sama.

**Kapan:** “berapa langkah sampai 1 jika tiap kali ganti `n` jadi `φ(n)`”; prefix totient; cek konsistensi rumus koprima. Jangan iterasi `φ` dengan sieve ulang tiap langkah.

**Proses:** rantai dari 100.

```
100 → 40 → 16 → 8 → 4 → 2 → 1     (6 langkah)
36  → 12 → 4  → 2 → 1            (4)
21  → 12 → 4  → 2 → 1            (4)
```

Prefix `Σ_{i≤10} φ = 32`. Pasangan koprima di `1..10` (arah penuh):

```
2*32 − 1 = 63
```

Mobius: `floor(10/d)^2` untuk `d=1..10` kali `μ` = `100 − 25 − 9 + 0 − 4 + 4 − 1 + 0 + 0 + 1 = 66`? Hati-hati: rumus itu termasuk `(i,j)` **semua** `1..n`, dan `(1,1)` dst. Hitung ulang:

```
μ: 1,-1,-1,0,-1,1,-1,0,0,1
t: 10,5,3,2,2,1,1,1,1,1
t^2: 100,25,9,4,4,1,1,1,1,1
Σ μ t^2 = 100-25-9-4+1-1+1 = 63
```

Ya 63. Kekeliruan di atas: `μ(4)=0` sehingga `−4` tidak masuk; `μ(6)=+1` memberi `+1`, bukan `+4`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int chain_len(ll n) {
    int s = 0;
    while (n > 1) {
        n = phi(n);
        s++;
    }
    return s;
}

int main() {
    FASTIO;
    cout << chain_len(100) << ' ' << chain_len(36) << ' ' << chain_len(21) << '\n';
    // 6 4 4
    vector<int> ph = {0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4};
    ll pref = 0;
    for (int i = 1; i <= 10; i++) pref += ph[i];
    cout << pref << ' ' << 2 * pref - 1 << '\n'; // 32 63
    return 0;
}
```

**Jebakan:** menghitung langkah termasuk `n` awal sebagai “sudah 1”; rumus `2Σφ−1` vs `Σ μ floor^2` tertukar inklusi `(i,j)` tak terurut; overflow prefix `n = 1e7` → `Σ φ ≈ 3e13` masih `ll`.

**Kompleksitas:** rantai `O(langkah · √n)`; prefix sieve `O(n)`.

---

## Teorema Euler a^φ(n) ≡ 1

**Teori:** jika `gcd(a, n) = 1` maka `a^{φ(n)} ≡ 1 (mod n)`. Fermat: `n` prima ⇒ `a^{n−1} ≡ 1 (mod n)` selama `n ∤ a`. Reduksi: `a^e ≡ a^{e mod φ(n)} (mod n)` **hanya** jika koprima. Jika tidak koprima, jangan `% φ(n)`. Untuk `e ≥ 0` dan `n` sebarang, pecah via CRT atau pakai `a^e = 0` setelah cukup pangkat jika `a` dan `n` berbagi semua prima.

Fungsi Carmichael `λ(n)` adalah eksponen grup: `a^{λ(n)} ≡ 1` untuk semua unit, dan `λ(n) | φ(n)`, kadang lebih kecil. `λ(8) = 2` sementara `φ(8) = 4`: `3^2 = 9 ≡ 1 (mod 8)`, bukan baru di pangkat 4.

**Kapan:** pangkat besar `a^b mod n` dengan `b` string; inverse `a^{φ(n)−1}` jika `n` komposit dan koprima. Jangan mereduksi `% (MOD−1)` kecuali MOD prima. Jangan Euler untuk `2^{10} mod 10`.

**Proses:** beberapa tes.

`7^{100} mod 15`. `gcd(7,15)=1`, `φ(15)=8`, `100 % 8 = 4`. `7^2=49≡4`, `7^4≡16≡1`. Jadi `7^{100}≡1`. Langsung: `7^1=7`, `7^2=4`, `7^3=28≡13`, `7^4=91≡1`, periode 4 yang membagi 8.

`2^{10} mod 21`. `gcd(2,21)=1`, `φ(21)=12`, `10 % 12 = 10`. `2^{10}=1024`. `1024 / 21 = 48*21=1008`, sisa 16. Jadi 16, **bukan** `2^{10 % 12}` yang kebetulan sama karena 10 sudah `< 12`.

`2^{10} mod 10`. `gcd ≠ 1`. `φ(10)=4`, `10%4=2`, `2^2=4 ≠ 2^{10} % 10 = 4` kebetulan. `2^5 % 10 = 2`, `5%4=1`, `2^1=2` kebetulan lagi. `3^5 % 10 = 3`, aman karena koprima. Jangan andalkan kasus 2.

`5^8 mod 16`. `gcd(5,16)=1`, `φ(16)=8`, jadi `5^8 ≡ 1`. `5^2=25≡9`, `5^4≡81≡1`, sudah 1 lebih awal (`λ(16)=4`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll norm(ll a, ll m) {
    a %= m;
    if (a < 0) a += m;
    return a;
}

ll modpow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a = norm(a, m);
    while (e) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

ll pow_euler(ll a, ll e, ll n) {
    a = norm(a, n);
    if (n == 1) return 0;
    if (std::gcd(a, n) != 1) return modpow(a, e, n); // jangan reduksi
    ll ph = phi(n);
    return modpow(a, e % ph, n);
}

int main() {
    FASTIO;
    cout << pow_euler(7, 100, 15) << ' ' << modpow(7, 100, 15) << '\n'; // 1 1
    cout << pow_euler(2, 10, 21) << ' ' << modpow(2, 10, 21) << '\n';   // 16 16
    cout << pow_euler(5, 8, 16) << '\n';                                // 1
    cout << modpow(2, 10, 10) << '\n';                                  // 4
    return 0;
}
```

**Jebakan:** `e % φ` saat tidak koprima; `modpow` dengan `r = 1` tanpa `% m` saat `m = 1`; string eksponen: harus `% φ` **sambil** membaca digit, bukan parse `e` ke `ll`; `λ` vs `φ` — reduksi `% φ` tetap sah, `% λ` juga sah dan kadang lebih kecil.

**Kompleksitas:** `φ` `O(√n)`, pangkat `O(log e)`.

---

## Orde multiplikatif

**Teori:** orde `ord_n(a)` untuk `gcd(a, n) = 1` adalah `e > 0` terkecil dengan `a^e ≡ 1 (mod n)`. Selalu `ord | φ(n)` (lebih ketat `ord | λ(n)`). Mencari: faktorisasi `φ(n)`, mulai `e = φ(n)`, untuk tiap `p^k || e` turunkan `e /= p` selama `a^{e/p} ≡ 1`. Analoginya: periode siklus `a, a^2, …` di grup unit.

**Kapan:** panjang siklus LCG, “kapan `a^x ≡ 1` pertama”, primitive root (`ord = φ(n)`). Jangan uji `e = 1,2,3,…` sampai `n` jika `φ` terfaktor.

**Proses:** `ord_17(3)`. `17` prima, `φ = 16 = 2^4`.

```
3^16 ≡ 1
3^8 = 6561 ≡ 16 ≡ −1 ≠ 1   (6561−385*17=6561−6545=16)
3^4 = 81 ≡ 13 ≠ 1
tidak bisa turun → ord = 16  (akar primitif)
```

`ord_13(2)`: `φ=12=2^2·3`.

```
2^12 ≡ 1
2^6=64≡12≡−1 ≠ 1  → tidak bagi 2 sekali dari 12? e=12, p=2: 2^{6}≠1, e tetap
p=2 lagi: sudah tidak
p=3: 2^{4}=16≡3 ≠ 1
ord = 12  (juga primitif)
```

`ord_15(7)`: `φ=8`. `7^1=7`, `7^2=4`, `7^4=1` → orde 4, membagi 8.

`ord_8(3)`: `φ=4`, `3^1=3`, `3^2=1` → 2, sama dengan `λ(8)`.

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

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

vector<pair<ll, int>> factor(ll n) {
    vector<pair<ll, int>> f;
    for (ll p = 2; p * p <= n; p++) if (n % p == 0) {
        int c = 0;
        while (n % p == 0) {
            n /= p;
            c++;
        }
        f.push_back({p, c});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}

ll order(ll a, ll n) {
    a %= n;
    if (std::gcd(a, n) != 1) return -1;
    ll ph = phi(n), e = ph;
    for (auto [p, c] : factor(ph)) {
        (void)c;
        while (e % p == 0 && modpow(a, e / p, n) == 1) e /= p;
    }
    return e;
}

int main() {
    FASTIO;
    cout << order(3, 17) << '\n'; // 16
    cout << order(2, 13) << '\n'; // 12
    cout << order(7, 15) << '\n'; // 4
    cout << order(3, 8) << '\n';  // 2
    cout << order(2, 10) << '\n'; // -1
    return 0;
}
```

**Jebakan:** tidak membagi `p` berulang (pangkat di `φ`); `a` tidak dikurangi mod `n`; `gcd ≠ 1` tetap dipaksa; overflow `modpow` jika `m` besar dan `r*a` `int`.

**Kompleksitas:** faktor `φ` `O(√φ)` plus `O(ω log φ)` pangkat.

---

## Akar primitif kontes

**Teori:** `g` akar primitif modulo `n` jika `ord_n(g) = φ(n)`, yaitu generator grup unit — hanya ada jika grup siklik. Ada primitive root iff `n = 1, 2, 4, p^k, 2p^k` untuk `p` ganjil prima. Mod `8` tidak ada: unit `{1,3,5,7}` semua kuadrat `1`. Uji `g`: untuk tiap prima `q | φ(n)`, `g^{φ/q} ≢ 1`. Analoginya: `g` mengelilingi semua unit sebelum kembali.

**Kapan:** NTT butuh generator `g` (lihat [ntt.md](ntt.md)); BSGS butuh basis; “apakah 3 generator mod p”. Jangan mencari di `n = 15`: grup `C2×C4`, tidak siklik, tidak ada primitive root. `φ(15)=8` tetapi tidak ada elemen orde 8 (`7` orde 4, `2` orde 4, `4` orde 2).

**Proses:** cari primitive root terkecil mod 17.

```
φ=16, prima | 16 hanya 2
uji g^{8} ≢ 1
g=2: 2^8=256≡1  (256−15*17=256−255) gagal
g=3: 3^8≡−1 ≢ 1  berhasil
```

Mod 13: `φ=12=2^2·3`, uji `g^{6}` dan `g^{4}`.

```
g=2: 2^6=64≡12≢1, 2^4=3≢1 → 2 primitif
```

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

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

vector<ll> prime_divs(ll n) {
    vector<ll> v;
    for (ll p = 2; p * p <= n; p++) if (n % p == 0) {
        v.push_back(p);
        while (n % p == 0) n /= p;
    }
    if (n > 1) v.push_back(n);
    return v;
}

bool is_primitive(ll g, ll n, ll ph, const vector<ll>& qs) {
    if (std::gcd(g, n) != 1) return false;
    for (ll q : qs)
        if (modpow(g, ph / q, n) == 1) return false;
    return true;
}

ll find_primitive(ll n) {
    ll ph = phi(n);
    auto qs = prime_divs(ph);
    for (ll g = 1; g < n; g++)
        if (is_primitive(g, n, ph, qs)) return g;
    return -1;
}

int main() {
    FASTIO;
    cout << find_primitive(17) << '\n'; // 3
    cout << find_primitive(13) << '\n'; // 2
    cout << find_primitive(15) << '\n'; // -1
    cout << find_primitive(7) << '\n';  // 3
    return 0;
}
```

**Jebakan:** menguji semua pembagi `φ`, bukan hanya prima; `g = 1` lolos jika lupa tes; mencari di modulus tanpa grup siklik; `g^{φ} ≡ 1` selalu — itu **bukan** tes primitif.

**Kompleksitas:** `O(n · ω(φ) log φ)` naif; di kontes `n` prima ~`1e9` cukup coba `g` kecil `O(ω log n)` pangkat.

---

## Diskrit log BSGS

**Teori:** soal kontes: cari `x` dengan `a^x ≡ b (mod m)`, biasanya `m` prima dan `gcd(a, m) = 1`. Tulis `x = i·s − j` atau `x = i·s + j` dengan `s = ceil(√m)`, `0 ≤ j < s`, `i < s`. Versi `+`: `a^j = b · (a^{-s})^i`. Prakomputasi baby `a^j` di hashmap, lalu giant kali `a^{-s}`. Analoginya: meet-in-the-middle pada eksponen, sama semangat [MITM](../04-sorting-searching/meet-in-the-middle.md).

Ini **alat persamaan di kontes** (periode, “kapan potensial jadi X”, generator). Bukan prosedur menyerang Diffie–Hellman, diskrit log kripto, atau kunci nyata. `m` kontes biasanya `≤ 1e9` sehingga `√m ≈ 3e4` sampai `1e6` masuk.

Jika banyak solusi, BSGS mengembalikan yang terkecil `0 ≤ x < ord` jika kamu batasi `i, j` di `ord`, atau `0 ≤ x < m−1` untuk prima.

**Kapan:** `a^x = b` mod prima, `m ≤ ~1e10` longgar / `1e9` nyaman. Jangan `O(m)` loop. Jangan jika `gcd(a, m) > 1` tanpa mereduksi dulu (bisa tak ada solusi). Jangan pakai untuk “pecahkan kunci”.

**Proses:** `3^x ≡ 13 (mod 17)`, `s = 5` karena `5^2=25>17`.

Baby `3^j mod 17`:

| j | 3^j |
|---:|---:|
| 0 | 1 |
| 1 | 3 |
| 2 | 9 |
| 3 | 10 |
| 4 | 13 |

`13` sudah di `j = 4` → `x = 4`. Cek `3^4=81≡13` (`81−4*17=81−68`).

Tanpa keberuntungan di baby, lanjut. `5^x ≡ 8 (mod 23)`, `s = 5`.

```
5^j: 1, 5, 2, 10, 4     (j=0..4)
inv = 5^{-5} mod 23
5^2=2, 5^4=4, 5^5=20 ≡ −3
inv(−3)=inv(20). 20*?≡1. 20*15=300≡1? 299=13*23, 300−299=1. Ya 15.
giant mulai cur=8
i=0: 8 tidak di baby
i=1: 8*15=120≡5  (120−5*23=120−115)  → j=1
x = 1*5 + 1 = 6
```

`5^6 = 15625`. `15625 / 23`: atau langkah `5^2=2`, `5^4=4`, `5^6=4*2=8`. Cocok.

`2^x ≡ 11 (mod 13)`: `2^7=128≡11` (`13*9=117`, `128−117=11`). BSGS `s=4`:

```
2^j: 1,2,4,8
2^{-4}=2^{-4}≡2^{8} karena 2^{12}≡1, 2^8=256≡9  (atau inv 16≡3 → inv3=9)
cur=11
i=0: 11 tidak
i=1: 11*9=99≡8 → j=3
x=4+3=7
```

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

ll modinv(ll a, ll m) { // m prima
    return modpow(a, m - 2, m);
}

// mencari x terkecil >= 0, a^x ≡ b (mod p), p prima.
// -1 jika tidak ada di 0..p-2. Hanya untuk persamaan kontes.
ll bsgs(ll a, ll b, ll p) {
    a %= p;
    b %= p;
    if (p == 1) return 0;
    if (b == 1) return 0;
    if (a == 0) return (b == 0 ? 1 : -1);
    ll s = (ll)sqrt((long double)p) + 1;
    unordered_map<ll, ll> baby;
    baby.reserve((size_t)s * 2);
    ll ap = 1;
    for (ll j = 0; j < s; j++) {
        if (!baby.count(ap)) baby[ap] = j;
        ap = ap * a % p;
    }
    ll factor = modinv(modpow(a, s, p), p);
    ll cur = b;
    for (ll i = 0; i <= s; i++) {
        auto it = baby.find(cur);
        if (it != baby.end()) {
            ll x = i * s + it->second;
            if (x < p) return x;
        }
        cur = cur * factor % p;
    }
    return -1;
}

int main() {
    FASTIO;
    cout << bsgs(3, 13, 17) << '\n'; // 4
    cout << bsgs(5, 8, 23) << '\n';  // 6
    cout << bsgs(2, 11, 13) << '\n'; // 7
    cout << bsgs(2, 1, 13) << '\n';  // 0
    cout << bsgs(3, 2, 17) << '\n';  // -1 atau nilai jika ada; 3^x tidak pernah 2
    return 0;
}
```

`3` generator mod 17, jadi setiap `b ≠ 0` punya solusi. `3^x ≡ 2`: `x = 14` karena `3^{14} = 3^{-2} ≡ inv(9) = 2` (`9*2=18≡1`). Kode harus menemukan 14. Jika keluaran `-1`, perbesar loop `i` sampai `s` inklusif — di atas `i <= s` menutup `x` sampai `s^2 ≥ p`.

**Jebakan:** hashmap menimpa `j` lebih kecil — simpan `j` pertama; `a^{-s}` salah inverse; `b = 0` pada prima (hanya jika `a = 0`); `unordered_map` hash collision TLE — cadangan `map` atau increment-key; memakai BSGS untuk modulus komposit tanpa CRT / grup; mengira ini alat kripto.

**Kompleksitas:** `O(√p)` waktu dan memori. Pohlig–Hellman (jika `p−1` smooth) lebih cepat, tetap untuk persamaan kontes, bukan serangan kunci.

---

## Peta keputusan

```
butuh φ(n) satu angka          → trial / faktor
butuh φ[1..n]                  → sieve
Σ φ(d)=n atau Σ gcd(k,n)       → identitas totient
a^e mod n, gcd=1               → e %= φ(n) lalu modpow
gcd(a,n)≠1                     → jangan Euler mentah
periode a^e ≡ 1                → orde (bagi φ)
generator / NTT g              → primitive root
a^x ≡ b mod p (kontes)         → BSGS
n ≤ 1e18 faktor                → Pollard di miller-pollard.md
```

| tes | hasil |
|---|---|
| `φ(36)` | 12 |
| `φ(3)φ(5)` | `φ(15)=8` |
| `Σ_{d\|20} φ(d)` | 20 |
| `7^{100} mod 15` | 1 |
| `ord_17(3)` | 16 |
| `3^x ≡ 13 (mod 17)` | 4 |

---

## Ringkasan

1. `φ` multiplikatif pada argumen koprima; rumus `n Π (1−1/p)`.
2. `Σ_{d|n} φ(d) = n` adalah tes sieve dan sumber `Σ gcd`.
3. Euler: `a^{φ(n)} ≡ 1` hanya jika koprima; reduksi eksponen ikut syarat itu.
4. Orde membagi `φ(n)`; primitive root ada hanya pada bentuk modulus tertentu.
5. BSGS menyelesaikan diskrit log **soal kontes** di `O(√p)`, bukan serangan kripto.

Lanjut inversi dan hitungan GCD: [mobius.md](mobius.md). Modular dasar: [modular-ncr.md](modular-ncr.md).
