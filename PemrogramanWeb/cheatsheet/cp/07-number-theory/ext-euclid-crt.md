# Extended Euclid, Diophantine, dan CRT

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **092**. Koefisien Bézout, invers umum, sistem sisa.

> **Ide satu kalimat:** exgcd mencari `x, y` pada `ax + by = gcd`; itu membuka invers saat modulus tidak prima, solusi Diophantine, dan penggabungan sisa CRT.

Sebelumnya: [modular & nCr](modular-ncr.md). Lanjut: [Miller & Pollard](miller-pollard.md).

## Daftar isi

- [Extended Euclid](#extended-euclid)
- [Exgcd iteratif](#exgcd-iteratif)
- [Persamaan Diophantine linear](#persamaan-diophantine-linear)
- [Kongruensi ax ≡ b](#kongruensi-ax--b)
- [Invers lewat exgcd](#invers-lewat-exgcd)
- [CRT modulus koprima](#crt-modulus-koprima)
- [CRT umum](#crt-umum)
- [Tiga kongruensi atau lebih](#tiga-kongruensi-atau-lebih)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Extended Euclid

**Teori:** selain `g = gcd(a, b)`, cari `x, y` supaya `a x + b y = g`. Identitas Bézout: selalu ada. Rekonstruksi: dari `a = q b + r` dan `b x1 + r y1 = g`, substitusi `r = a − q b` → `a y1 + b (x1 − q y1) = g`. Analoginya: kamu punya koin `a` dan `b` (utang = negatif), susun jumlah `g`.

Basis: `b = 0` → `x = 1`, `y = 0`, `g = a` (atau `|a|` setelah normalisasi).

**Kapan:** invers modular saat `m` tidak prima, Diophantine, CRT. Jangan pakai Fermat `a^{m−2}` jika `m` komposit.

**Proses:** `a = 48`, `b = 18`.

```
48 = 2 * 18 + 12
18 = 1 * 12 + 6
12 = 2 * 6  + 0
g = 6
```

Mundur:

```
6 = 18 - 1 * 12
12 = 48 - 2 * 18
6 = 18 - 1 * (48 - 2 * 18) = -1 * 48 + 3 * 18
```

Jadi `x = -1`, `y = 3`. Cek: `48 * (-1) + 18 * 3 = -48 + 54 = 6`.

Solusi umum: `x = -1 + (18/6) t = -1 + 3 t`, `y = 3 - (48/6) t = 3 - 8 t`.

`t = 1`: `x = 2`, `y = -5`. Cek: `48 * 2 + 18 * (-5) = 96 - 90 = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    ll x, y;
    ll g = exgcd(48, 18, x, y);
    cout << g << ' ' << x << ' ' << y << '\n'; // 6 -1 3
    cout << 48 * x + 18 * y << '\n';           // 6
    g = exgcd(7, 3, x, y);
    cout << g << ' ' << x << ' ' << y << '\n'; // 1 -2 5
    cout << 7 * x + 3 * y << '\n';             // 1
    return 0;
}
```

Jika `a` atau `b` negatif, normalisasi dulu atau sesuaikan tanda `x, y` setelahnya. Banyak soal menjamin `a, b > 0`.

**Jebakan:** menukar `x = x1 - q * y1` vs `x = y1`; overflow `q * y1` pada 64-bit ekstrem; mengira solusi unik.

**Kompleksitas:** `O(log min(a, b))` waktu dan stack.

---

## Exgcd iteratif

**Teori:** simpan koefisien lama/baru seperti tabel Euclid diperluas. Hindari stack rekursi. Analoginya: dua kolom “koefisien a” dan “koefisien b” di-update setiap sisa.

Satu bentuk: `x2, x1` untuk koefisien `a`; tiap langkah `x = x2 - q * x1`.

**Kapan:** kontes yang sama dengan rekursif; lebih aman jika khawatir kedalaman (untuk 64-bit, rekursi tetap dangkal). Berguna jika ingin semua sisa di sepanjang jalan.

**Proses:** `a = 48`, `b = 18` (sama).

```
q    a    b    x2  x1   y2  y1
     48   18   1   0    0   1
2    18   12   0   1    1  -2     x = 1-2*0=1, y=0-2*1=-2? 
```

Lebih aman mengikuti kode: setelah selesai, `x, y` memenuhi identitas. Cek dengan `48x + 18y`.

Verifikasi kode di bawah: harus cetak `6 -1 3` atau pasangan setara `6 2 -5`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll exgcd_iter(ll a, ll b, ll& x, ll& y) {
    ll x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    while (b) {
        ll q = a / b;
        ll na = b, nb = a % b;
        ll nx = x0 - q * x1;
        ll ny = y0 - q * y1;
        a = na;
        b = nb;
        x0 = x1;
        y0 = y1;
        x1 = nx;
        y1 = ny;
    }
    x = x0;
    y = y0;
    return a;
}

int main() {
    FASTIO;
    ll x, y;
    ll g = exgcd_iter(48, 18, x, y);
    cout << g << ' ' << x << ' ' << y << '\n';
    cout << 48 * x + 18 * y << '\n'; // 6
    return 0;
}
```

**Jebakan:** meng-update `a, b` sebelum memakai `q = a / b`; menukar pasangan `(x0, x1)` tidak bersamaan dengan `(y0, y1)`; `g` negatif jika `a` negatif.

**Kompleksitas:** `O(log)` waktu, `O(1)` memori.

---

## Persamaan Diophantine linear

**Teori:** `a x + b y = c` punya solusi integer iff `g | c` dengan `g = gcd(a, b)`. Satu solusi: exgcd untuk `g`, lalu kali `c / g`. Semua solusi: `x = x0 + (b / g) t`, `y = y0 − (a / g) t`. Analoginya: langkah `a` kanan dan `b` kiri hanya bisa tiba di `c` jika `c` kelipatan ukuran langkah dasar `g`.

**Kapan:** “ada berapa pasangan non-negatif”, lompat katak, dua ukuran kemasan. Tiga variabel atau minimalkan `x + y` — iterasi `t` di rentang. Jangan brute `x` sampai `1e12`.

**Proses:** `4x + 6y = 10`. `g = 2`, `2 | 10` ya. Exgcd `4x + 6y = 2` → `x = -1`, `y = 1` (`4*(-1)+6*1=2`). Kali 5: `x = -5`, `y = 5`. Umum: `x = -5 + 3t`, `y = 5 - 2t`.

Cari `x ≥ 0`, `y ≥ 0`:

```
-5 + 3t ≥ 0 → t ≥ 2
5 - 2t ≥ 0  → t ≤ 2
t = 2: x = 1, y = 1
```

Satu solusi non-negatif: `4*1 + 6*1 = 10`.

`4x + 6y = 5`: 2 tidak membagi 5 → mustahil.

`9x + 6y = 3`: `g = 3 | 3`. Exgcd `9x+6y=3` → bagi 3: `3x+2y=1`. Satu solusi `x = -1`, `y = 2` karena `9*(-1)+6*2=3`. Umum `x = -1 + 2t`, `y = 2 - 3t`. Non-negatif: `-1+2t ≥ 0` → `t ≥ 1`; `2-3t ≥ 0` → `t ≤ 0`. Kosong.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

bool dio(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    g = exgcd(a, b, x, y);
    if (g < 0) {
        g = -g;
        x = -x;
        y = -y;
    }
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    return true;
}

ll ceil_div(ll p, ll q) {
    if (q < 0) {
        p = -p;
        q = -q;
    }
    return p >= 0 ? (p + q - 1) / q : p / q;
}

ll floor_div(ll p, ll q) {
    if (q < 0) {
        p = -p;
        q = -q;
    }
    return p >= 0 ? p / q : -((-p + q - 1) / q);
}

ll hitung_nonneg(ll a, ll b, ll c) {
    ll x, y, g;
    if (!dio(a, b, c, x, y, g)) return 0;
    ll bg = b / g, ag = a / g;
    ll tmin = ceil_div(-x, bg);
    ll tmax = floor_div(y, ag);
    if (tmax < tmin) return 0;
    return tmax - tmin + 1;
}

int main() {
    FASTIO;
    ll x, y, g;
    cout << dio(4, 6, 10, x, y, g) << ' ' << x << ' ' << y << '\n';
    cout << 4 * x + 6 * y << '\n';          // 10
    cout << hitung_nonneg(4, 6, 10) << '\n'; // 1
    cout << hitung_nonneg(4, 6, 5) << '\n';  // 0
    cout << hitung_nonneg(9, 6, 3) << '\n';  // 0
    return 0;
}
```

Pembagian ceil/floor bertanda mudah salah. Untuk kontes, uji beberapa `t` di sekitar `-x / (b/g)` jika rentang kecil.

**Jebakan:** lupa `g | c`; overflow `x *= c / g`; menghitung `t` dengan `double`; `a = 0` atau `b = 0` kasus terpisah; `ag` atau `bg` nol.

**Kompleksitas:** `O(log)` plus aritmetika solusi. Enumerasi `t` `O(jumlah solusi)` jika diminta daftar.

---

## Kongruensi ax ≡ b

**Teori:** `a x ≡ b (mod m)` sama dengan `a x − m y = b`. Solvable iff `g | b` dengan `g = gcd(a, m)`. Ada tepat `g` solusi modulo `m`, berjarak `m / g`. Analoginya: lompatan `a` pada lingkaran `m` hanya mengenai sisa yang kelipatan `g`.

**Kapan:** invers adalah kasus `b = 1`. “cari semua x”, pecah persamaan sebelum CRT. Jangan `inv(a) * b` jika `gcd > 1` — invers tidak ada, tetapi persamaan masih bisa punya solusi.

**Proses:** `10 x ≡ 6 (mod 14)`. `gcd(10, 14) = 2`, `2 | 6` ya.

Bagi 2: `5 x ≡ 3 (mod 7)`. `inv(5, 7) = 3` karena `5 * 3 = 15 ≡ 1`. `x ≡ 9 ≡ 2 (mod 7)`.

Dua solusi mod 14: `x = 2` dan `x = 2 + 7 = 9`.

Cek: `10*2 = 20 ≡ 6`, `10*9 = 90`, `90 / 14 = 6 * 14 = 84`, sisa 6.

`10 x ≡ 5 (mod 14)`: `2` tidak membagi 5 → kosong.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

// kembalikan g solusi di [0, m), atau kosong
vector<ll> solve_axb(ll a, ll b, ll m) {
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (g < 0) {
        g = -g;
        x = -x;
    }
    vector<ll> ans;
    if (b % g) return ans;
    m /= g;
    a /= g;
    b /= g;
    x = (ll)((__int128)x * (b % m) % m);
    if (x < 0) x += m;
    for (ll i = 0; i < g; i++)
        ans.push_back((x + i * m) % (m * g));
    return ans;
}

int main() {
    FASTIO;
    auto v = solve_axb(10, 6, 14);
    for (ll x : v) cout << x << ' ';
    cout << '\n'; // 2 9
    cout << solve_axb(10, 5, 14).size() << '\n'; // 0
    return 0;
}
```

**Jebakan:** mengembalikan satu solusi padahal ada `g` buah; modulus setelah bagi vs sebelum bagi tertukar; `x` negatif.

**Kompleksitas:** `O(log m + g)` jika mencetak semua.

---

## Invers lewat exgcd

**Teori:** `a x ≡ 1 (mod m)` = `a x + m y = 1`. Ada iff `gcd(a, m) = 1`. Exgcd memberi `x`, normalisasi ke `[0, m)`. Jalan untuk **modulus apa pun yang koprima dengan a**, tidak harus prima.

**Kapan:** `m` komposit, CRT, invers di `mod 10^9` (bukan +7). Jangan jika `gcd > 1` kecuali soal meminta `a x ≡ b`.

**Proses:** `a = 10`, `m = 21`. `gcd(10, 21) = 1`.

```
21 = 2 * 10 + 1
10 = 10 * 1 + 0
1 = 21 - 2 * 10
10 x + 21 y = 1 → x = -2, y = 1
```

`x ≡ -2 ≡ 19 (mod 21)`. Cek: `10 * 19 = 190`, `9 * 21 = 189`, sisa 1.

`a = 10`, `m = 15`, `gcd = 5 ≠ 1`, tidak ada invers.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

ll inv_exgcd(ll a, ll m) {
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (g != 1 && g != -1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {
    FASTIO;
    cout << inv_exgcd(10, 21) << '\n';      // 19
    cout << (ll)((__int128)10 * 19 % 21) << '\n'; // 1
    cout << inv_exgcd(10, 15) << '\n';      // -1
    cout << inv_exgcd(3, 7) << '\n';        // 5
    return 0;
}
```

**Jebakan:** tidak menormalisasi `x` negatif; `g = -1` dari `a` negatif; mengembalikan `x` tanpa `% m`.

**Kompleksitas:** `O(log m)`.

---

## CRT modulus koprima

**Teori:** sistem `x ≡ a_i (mod m_i)` punya solusi unik modulo `M = Π m_i` jika semua `m_i` **berpasangan koprima**. Rumus: `M_i = M / m_i`, `t_i = invers(M_i, m_i)`, `x = Σ a_i M_i t_i (mod M)`. Kenapa: `M_i ≡ 0 (mod m_j)` untuk `j ≠ i`, dan `M_i t_i ≡ 1 (mod m_i)`, jadi suku ke-`i` menyisakan `a_i` di `m_i` dan 0 di modulus lain. Analoginya tiga jam periode 3, 5, 7 — ada tepat satu menit dalam 105 menit yang cocok.

**Kapan:** pecah modulus `m = p1^{k1} …`, gabung jawaban DP / invers, “cari x yang sisa-sisanya …”. Jangan rumus ini jika `gcd(m_i, m_j) > 1`. Jangan overflow `M` tanpa `__int128`.

**Proses:**

```
x ≡ 2 (mod 3)
x ≡ 3 (mod 5)
x ≡ 2 (mod 7)
```

`M = 105`.

| i | a | m | M_i | M_i mod m | invers | suku |
|---:|---:|---:|---:|---:|---:|---:|
| 1 | 2 | 3 | 35 | 2 | 2 | 140 |
| 2 | 3 | 5 | 21 | 1 | 1 | 63 |
| 3 | 2 | 7 | 15 | 1 | 1 | 30 |

`x = 233 ≡ 23 (mod 105)` karena `233 − 2 * 105 = 23`.

Cek: `23 = 7*3+2`, `23 = 4*5+3`, `23 = 3*7+2`.

Contoh dua: `x ≡ 1 (mod 4)`, `x ≡ 3 (mod 5)`. `M = 20`, `M1 = 5`, `inv(5,4)=1`, suku 5; `M2=4`, `inv(4,5)=4`, suku `3*4*4=48`. `x = 53 ≡ 13 (mod 20)`. Cek: `13 % 4 = 1`, `13 % 5 = 3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

ll inv_exgcd(ll a, ll m) {
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (g != 1 && g != -1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

ll crt_koprima(const vector<ll>& a, const vector<ll>& m) {
    int k = (int)a.size();
    ll M = 1;
    for (ll x : m) M *= x;
    ll x = 0;
    for (int i = 0; i < k; i++) {
        ll Mi = M / m[i];
        ll t = inv_exgcd(Mi % m[i], m[i]);
        ll suku = (ll)((__int128)a[i] * Mi % M * t % M);
        x += suku;
        if (x >= M) x -= M;
    }
    return x;
}

int main() {
    FASTIO;
    cout << crt_koprima({2, 3, 2}, {3, 5, 7}) << '\n'; // 23
    cout << crt_koprima({1, 3}, {4, 5}) << '\n';       // 13
    cout << crt_koprima({1, 1}, {2, 3}) << '\n';       // 1
    return 0;
}
```

**Jebakan:** `M_i % m_i` lupa sebelum invers; overflow `M`; modulus tidak koprima tetap dipaksa; `x` negatif setelah jumlah.

**Kompleksitas:** `O(k log M)`, memori `O(k)`.

---

## CRT umum

**Teori:** dua kongruensi `x ≡ a (mod m)`, `x ≡ b (mod n)` solvable iff `a ≡ b (mod gcd(m, n))`. Jika ya, modulus gabungan `lcm(m, n)`, solusi unik di situ. Gabungkan berpasangan. Syarat: `x = a + m s = b + n t` → `m s − n t = b − a`, jadi `g | (b − a)`. Analoginya: dua jadwal yang periodenya tidak koprima hanya ketemu jika selisih fasenya kelipatan GCD.

**Kapan:** `mod 12` plus `mod 18`, atau dua modulus yang `gcd > 1`. Jangan rumus produk koprima. Jika suatu pasangan gagal, seluruh sistem gagal.

**Proses:** `x ≡ 2 (mod 4)` dan `x ≡ 6 (mod 10)`.

`gcd(4, 10) = 2`. `2 ≡ 6 (mod 2)`? Beda 4, habis 2, ya.

`4 s − 10 t = 4`, bagi 2: `2 s − 5 t = 2`. `s = 1`, `x = 2 + 4 * 1 = 6`.

`lcm = 20`. Umum: `x = 6 + 20 k`. Cek: `6 mod 4 = 2`, `6 mod 10 = 6`. `26` juga.

Gagal: `x ≡ 1 (mod 4)`, `x ≡ 6 (mod 10)`. `1 − 6 = -5` tidak habis 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

bool crt_gabung(ll a, ll m, ll b, ll n, ll& x, ll& mod) {
    ll s, t;
    ll g = exgcd(m, n, s, t);
    if ((b - a) % g) return false;
    ll n_g = n / g;
    ll k = (ll)((__int128)(b - a) / g * s % n_g);
    if (k < 0) k += n_g;
    x = a + m * k;
    mod = m / g * n;
    x %= mod;
    if (x < 0) x += mod;
    return true;
}

bool crt_umum(vector<ll> a, vector<ll> m, ll& x, ll& mod) {
    x = 0;
    mod = 1;
    int k = (int)a.size();
    for (int i = 0; i < k; i++) {
        ll nx, nmod;
        if (!crt_gabung(x, mod, a[i], m[i], nx, nmod)) return false;
        x = nx;
        mod = nmod;
    }
    return true;
}

int main() {
    FASTIO;
    ll x, mod;
    cout << crt_umum({2, 6}, {4, 10}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 6 20
    cout << crt_umum({1, 6}, {4, 10}, x, mod) << '\n'; // 0
    cout << crt_umum({2, 3, 2}, {3, 5, 7}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 23 105
    return 0;
}
```

**Jebakan:** `(b − a)` overflow; `s` dikali tanpa `% (n/g)`; modulus hasil overflow `ll`; menggabungkan tanpa cek `g | (b − a)`.

**Kompleksitas:** `O(k log)`, memori `O(1)` tambahan.

---

## Tiga kongruensi atau lebih

**Teori:** lipat CRT umum kiri-ke-kanan. Setelah dua pertama, kamu punya satu pasangan `(x, M)`. Masukkan kongruensi ketiga sebagai pasangan baru. Jika semua `m_i` koprima, `M` menjadi produk; jika tidak, `M` menjadi LCM (saat solvable). Analoginya: janji tiga orang — cocokkan dua dulu, lalu dengan yang ketiga.

**Kapan:** sistem sisa panjang, pecah jawaban mod `2^k` dan `5^k` lalu gabung ke `10^k`. Jangan kalikan semua modulus dulu jika tidak koprima.

**Proses:**

```
x ≡ 2 (mod 4)
x ≡ 6 (mod 10)
x ≡ 6 (mod 8)
```

Dari sebelumnya: `x ≡ 6 (mod 20)`. Gabung `x ≡ 6 (mod 8)`.

`gcd(20, 8) = 4`. `6 ≡ 6 (mod 4)` ya. `lcm(20, 8) = 40`.

`x = 6` sudah memenuhi `6 % 8 = 6`. Jadi `x ≡ 6 (mod 40)`.

Cek: 6, 46, 86, …  `46 % 4 = 2`, `46 % 10 = 6`, `46 % 8 = 6`.

Gagal jika ketiga adalah `x ≡ 2 (mod 8)`: `6 ≡ 2 (mod 4)`? `4 ≡ 0` ya secara GCD, tetapi `6 % 8 = 6 ≠ 2`. `gcd(20,8)=4`, `6-2=4`, 4 habis 4 — solvable? `6 ≡ 2 (mod 4)` ya. Solusi: `6 + 20 s ≡ 2 (mod 8)`. `20 ≡ 4 (mod 8)`, `6 + 4s ≡ 2 (mod 8)` → `4s ≡ -4 ≡ 4 (mod 8)` → `s` ganjil. `s=1`, `x=26`, `mod=40`. `26%8=2`, `26%4=2`, `26%10=6`. Jadi hati-hati: syarat GCD lolos tidak berarti `x` lama sudah cocok — harus dihitung ulang.

**Kode:** pakai `crt_umum` di seksi sebelumnya. Mini cek:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

bool crt_gabung(ll a, ll m, ll b, ll n, ll& x, ll& mod) {
    ll s, t;
    ll g = exgcd(m, n, s, t);
    if ((b - a) % g) return false;
    ll n_g = n / g;
    ll k = (ll)((__int128)(b - a) / g * s % n_g);
    if (k < 0) k += n_g;
    x = a + m * k;
    mod = m / g * n;
    x %= mod;
    if (x < 0) x += mod;
    return true;
}

bool crt_umum(vector<ll> a, vector<ll> m, ll& x, ll& mod) {
    x = 0;
    mod = 1;
    for (int i = 0; i < (int)a.size(); i++) {
        ll nx, nmod;
        if (!crt_gabung(x, mod, a[i], m[i], nx, nmod)) return false;
        x = nx;
        mod = nmod;
    }
    return true;
}

int main() {
    FASTIO;
    ll x, mod;
    cout << crt_umum({2, 6, 6}, {4, 10, 8}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 6 40
    cout << crt_umum({2, 6, 2}, {4, 10, 8}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 26 40
    return 0;
}
```

**Jebakan:** mengira `x` lama otomatis solusi; overflow LCM berantai; urutan gabung mengubah `x` tetapi tidak mengubah kelas sisa jika benar.

**Kompleksitas:** `O(k log)`.

---

## Peta keputusan

```
ax + by = g              → exgcd
ax + by = c              → g|c, kali c/g, geser t
ax ≡ 1 (mod m)           → invers: Fermat jika m prima, else exgcd
ax ≡ b (mod m)           → g|b, g solusi
sistem sisa
├── m_i koprima berpasangan → rumus Σ a_i M_i t_i
└── ada gcd > 1             → gabung 2-2, cek g|(a-b)
```

| situasi | alat | gagal jika |
|---|---|---|
| invers, `m` prima | Fermat | `m | a` |
| invers, `m` umum | exgcd | `gcd ≠ 1` |
| dua sisa, `gcd=1` | CRT produk | overflow `M` |
| dua sisa, `gcd>1` | CRT umum | `g` tak bagi beda |
| banyak sisa | lipat CRT | satu pasangan gagal |

---

## Ringkasan

1. Exgcd = Euclid plus koefisien. Solusi umum bergeser `b/g` dan `−a/g`.
2. Diophantine solvable iff `g | c`. Non-negatif = irisan rentang `t`.
3. `ax ≡ b` punya `g` solusi, bukan selalu invers.
4. CRT koprima = jumlah suku `a M t`. Tidak koprima = syarat GCD plus LCM.
5. Tiga atau lebih: lipat berpasangan, jangan asumsikan `x` lama sudah cocok.

Uji prima 64-bit: [miller-pollard.md](miller-pollard.md).
