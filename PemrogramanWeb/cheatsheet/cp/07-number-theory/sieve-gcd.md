# Sieve, GCD, LCM, dan faktor

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **088**. Fondasi Euclid, prima, sieve, dan pembagi.

> **Ide satu kalimat:** GCD merapikan dua bilangan lewat sisa bagi, LCM disusun dari GCD, sieve menyiapkan semua prima dan SPF sampai `n`, lalu faktor serta `d(n)`/`σ(n)` dihitung dari pangkat.

Lanjut: [invers & nCr](modular-ncr.md) · [exgcd & CRT](ext-euclid-crt.md) · [Miller & Pollard](miller-pollard.md)

## Daftar isi

- [GCD Euclid](#gcd-euclid)
- [GCD banyak bilangan](#gcd-banyak-bilangan)
- [LCM dua dan banyak](#lcm-dua-dan-banyak)
- [Uji prima trial](#uji-prima-trial)
- [Sieve of Eratosthenes](#sieve-of-eratosthenes)
- [Sieve tersegmentasi](#sieve-tersegmentasi)
- [Linear sieve dan SPF](#linear-sieve-dan-spf)
- [Faktorisasi dengan SPF](#faktorisasi-dengan-spf)
- [Banyak dan jumlah pembagi](#banyak-dan-jumlah-pembagi)
- [Sieve kelipatan untuk d dan σ](#sieve-kelipatan-untuk-d-dan-σ)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## GCD Euclid

**Teori:** `gcd(a, b)` adalah bilangan positif terbesar yang membagi keduanya. Identitas Euclid: `gcd(a, b) = gcd(b, a mod b)`, basis `gcd(a, 0) = |a|`. Setiap pembagi bersama `a` dan `b` juga membagi `a - q b`, jadi himpunan pembagi bersama tidak berubah. Analoginya dua pita: potong yang panjang dengan yang pendek sampai habis; sisa terakhir adalah ubin terbesar.

Versi iteratif menukar `a, b` sambil `a %= b`. Versi rekursif sama tetapi memakai stack. `__gcd` (GCC) dan `std::gcd` (C++17) sudah ada; tetap pahami Euclid karena pola yang sama muncul di exgcd.

**Kapan:** sederhanakan pecahan, rumus LCM, langkah katak, jumlah kotak di persegi `a × b`, syarat CRT, cek koprima. `n` sampai `10^18` tetap cepat. Jangan loop mundur `for (i = min(a,b); i >= 1; i--)`. Jangan rekursi pada `int` negatif tanpa `llabs`.

**Proses:** `gcd(252, 105)`.

```
252 = 2 * 105 + 42
105 = 2 * 42  + 21
42  = 2 * 21  + 0
gcd = 21
```

Cek: `252 / 21 = 12`, `105 / 21 = 5`, dan `gcd(12, 5) = 1`. Jadi 21 tepat.

`gcd(0, 18) = 18`. `gcd(0, 0)` di implementasi biasanya 0; soal hampir tidak memberi kasus itu.

Kasus terburuk dekat Fibonacci: `gcd(F_{n+1}, F_n) = 1` butuh n langkah. Untuk 64-bit, langkah < 100. Contoh: `gcd(89, 55)` turun `89,55,34,21,13,8,5,3,2,1` (9 langkah).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll gcd_rec(ll a, ll b) {
    a = llabs(a);
    b = llabs(b);
    if (b == 0) return a;
    return gcd_rec(b, a % b);
}

ll gcd_iter(ll a, ll b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    FASTIO;
    cout << gcd_iter(252, 105) << '\n';   // 21
    cout << gcd_iter(0, 18) << '\n';      // 18
    cout << gcd_iter(-36, 24) << '\n';    // 12
    cout << gcd_rec(89, 55) << '\n';      // 1
    cout << std::gcd(252, 105) << '\n';   // 21, C++17
    return 0;
}
```

**Jebakan:** `%` pada negatif mengikuti tanda pembilang; `gcd(0, 0)`; mengira `__gcd` ada di semua compiler; `llabs(LLONG_MIN)` overflow; menulis `a % b` saat `b == 0` sebelum cek basis.

**Kompleksitas:** waktu `O(log min(a, b))`, memori `O(1)` iteratif, `O(log)` stack rekursif.

---

## GCD banyak bilangan

**Teori:** `gcd(a, b, c) = gcd(gcd(a, b), c)`. Identitas asosiatif. GCD array mengecil monoton: setelah ketemu 1, sisa elemen tidak mengubah hasil. Analoginya: ukuran ubin bersama untuk banyak pita adalah ubin bersama dari (ubin dua pita pertama) dengan pita ketiga.

**Kapan:** “pembagi bersama terbesar seluruh array”, sederhanakan semua elemen, cek apakah semua habis `g`. Jangan `gcd` berpasangan `O(n^2)` jika lipatan kiri-ke-kanan sudah cukup.

**Proses:** `a = [48, 18, 30, 12]`.

```
g = 48
g = gcd(48, 18) = 6
g = gcd(6, 30)  = 6
g = gcd(6, 12)  = 6
```

Cek: 48, 18, 30, 12 semua habis 6, dan `48/6=8`, `18/6=3`, `30/6=5`, `12/6=2` — GCD sisanya 1, jadi 6 maksimal.

`[7, 14, 21, 8]`: `gcd(7,14)=7`, `gcd(7,21)=7`, `gcd(7,8)=1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll gcd_iter(ll a, ll b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll gcd_arr(const vector<ll>& a) {
    ll g = 0;
    for (ll x : a) g = gcd_iter(g, x);
    return g;
}

int main() {
    FASTIO;
    cout << gcd_arr({48, 18, 30, 12}) << '\n'; // 6
    cout << gcd_arr({7, 14, 21, 8}) << '\n';   // 1
    cout << gcd_arr({0, 0, 15}) << '\n';       // 15
    return 0;
}
```

**Jebakan:** inisialisasi `g = a[0]` tanpa jaga array kosong; lupa `llabs` jika ada negatif; berhenti dini hanya jika kamu memang ingin “apakah GCD jadi 1”.

**Kompleksitas:** `O(n log A)` waktu, `O(1)` memori tambahan.

---

## LCM dua dan banyak

**Teori:** `lcm(a, b) = |a / gcd(a, b) * b|`. Bagi dulu, baru kali, supaya tidak overflow di tengah. Jika `a = g x`, `b = g y` dan `gcd(x, y) = 1`, kelipatan persekutuan terkecil adalah `g x y`. Analoginya dua bus: periode 12 dan 18 ketemu setiap 36.

Untuk banyak angka, lipat LCM berantai. Secara faktor: ambil pangkat maksimum tiap prima.

**Kapan:** periode bersama, ukuran kotak, “kelipatan terkecil yang habis dibagi semua”. Jangan `a * b / gcd` pada `int` jika `a * b` melewati `2e9`. Jangan LCM `1..n` naif sampai `n = 1e6` tanpa cek overflow / pecah modulus.

**Proses:** `a = 12`, `b = 18`. `gcd = 6`. `12 / 6 * 18 = 36`.

Tiga angka `12, 18, 30`:

```
lcm(12, 18) = 36
lcm(36, 30) = 180
```

Faktor: `12 = 2^2 · 3`, `18 = 2 · 3^2`, `30 = 2 · 3 · 5` → `2^2 · 3^2 · 5 = 180`.

`lcm(0, 5)` secara matematika sering 0. Di kode, jika `a == 0 || b == 0` kembalikan 0.

Overflow: `lcm(10^9, 10^9 + 7)` = `10^9 * (10^9+7)` melewati `ll` hampir `1e18`, masih muat; `lcm(LLONG_MAX / 2, 6)` bisa melewati. Cek `x > LLONG_MAX / b`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll gcd_iter(ll a, ll b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm_ll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    a = llabs(a);
    b = llabs(b);
    return a / gcd_iter(a, b) * b;
}

bool lcm_aman(ll a, ll b, ll& out) {
    if (a == 0 || b == 0) {
        out = 0;
        return true;
    }
    a = llabs(a);
    b = llabs(b);
    ll g = gcd_iter(a, b);
    ll x = a / g;
    if (x > LLONG_MAX / b) return false;
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
    FASTIO;
    cout << lcm_ll(12, 18) << '\n';            // 36
    cout << lcm_banyak({12, 18, 30}) << '\n';  // 180
    cout << lcm_banyak({4, 6, 8}) << '\n';     // 24
    ll out;
    cout << lcm_aman(LLONG_MAX, 2, out) << '\n'; // 0, overflow
    return 0;
}
```

**Jebakan:** `a * b / gcd` overflow sebelum bagi; LCM berantai melewati `ll` tanpa cek; tertukar rumus `gcd = a / lcm * b`; `lcm(0, x)`.

**Kompleksitas:** sama Euclid `O(log)` per pasangan, `O(n log A)` untuk array.

---

## Uji prima trial

**Teori:** `n > 1` prima jika tidak punya pembagi di `2 .. √n`. Cukup cek 2 lalu ganjil, atau 2 dan 3 lalu langkah 6 (`i`, `i + 2`). Jika `n = a b` dan `a ≤ b` maka `a ≤ √n`. Analoginya: kalau kotak tidak tersusun dari bata lebih kecil dari sisi akar, ia batu utuh.

**Kapan:** satu atau sedikit `n ≤ 10^12` (`√n = 1e6` aman). `n ≤ 10^18` sekali-sekali masih lolos jika konstan ketat. Banyak query `n ≤ 1e6` → sieve. Banyak query `n ≤ 10^18` → [Miller-Rabin](miller-pollard.md).

**Proses:** `n = 91 = 7 · 13`. `√91 ≈ 9.54`. Cek 2, 3, 5, 7. `91 % 7 == 0` → komposit.

`n = 97`. `√97 ≈ 9.85`. Cek 2, 3, 5, 7. Tidak habis → prima.

`n = 1` bukan prima. `n = 2` prima. `n = 9` habis 3. `n = 25`: `√25 = 5`, `25 % 5 == 0`.

Faktor 84 secara trial:

```
2 | 84 → 42
2 | 42 → 21
3 | 21 → 7
7 prima
84 = 2^2 · 3 · 7
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    cout << is_prime(1) << is_prime(2) << is_prime(91) << is_prime(97) << '\n';
    // 0 1 0 1
    auto f = faktor_trial(84);
    for (ll x : f) cout << x << ' ';
    cout << '\n'; // 2 2 3 7
    return 0;
}
```

**Jebakan:** `i * i <= n` overflow jika `i` bertipe `int` dekat 46341 — cast `ll`; `n` negatif; loop `i <= n` TLE; `1` dianggap prima; `i * i` pada `n` dekat `LLONG_MAX` — bandingkan `i <= n / i`.

**Kompleksitas:** uji `O(√n)`, faktor `O(√n)`, memori `O(jumlah faktor)`.

---

## Sieve of Eratosthenes

**Teori:** dari 2 sampai `n`, setiap bilangan yang masih hidup adalah prima; matikan semua kelipatannya. Optimasi: mulai menandai dari `p * p` karena kelipatan lebih kecil sudah dipukul prima lebih kecil. Analoginya barisan anak: setiap kapten yang belum duduk menyuruh kelipatannya duduk.

**Kapan:** semua prima `≤ n` dengan `n ≤ 1e7` nyaman, `1e8` jika hafal memori. Banyak query “apakah `x` prima” untuk `x ≤ n`. Jangan sieve sampai `1e12`. Jangan membangun sieve di tiap testcase `t = 1e4` — prakomputasi sekali.

**Proses:** `n = 30`. Awal semua hidup kecuali 0 dan 1.

```
p=2  matikan 4,6,8,10,12,14,16,18,20,22,24,26,28,30
p=3  mulai 9: 9,12,15,18,21,24,27,30
p=5  mulai 25: 25,30
p=7  49 > 30, selesai
```

Hidup: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29. Ada 10 prima.

`π(10) = 4`, `π(20) = 8`, `π(30) = 10`, `π(100) = 25`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> sieve_primes(int n) {
    vector<char> is(n + 1, 1);
    if (n >= 0) is[0] = 0;
    if (n >= 1) is[1] = 0;
    for (int p = 2; (ll)p * p <= n; p++) {
        if (!is[p]) continue;
        for (int q = p * p; q <= n; q += p) is[q] = 0;
    }
    vector<int> p;
    for (int i = 2; i <= n; i++)
        if (is[i]) p.push_back(i);
    return p;
}

int main() {
    FASTIO;
    auto p = sieve_primes(30);
    for (int x : p) cout << x << ' ';
    cout << '\n'; // 2 3 5 7 11 13 17 19 23 29
    cout << sieve_primes(100).size() << '\n'; // 25
    return 0;
}
```

`p * p` wajib dihitung sebagai `ll` saat `n` dekat `INT_MAX`, atau tulis `p <= n / p`.

**Jebakan:** mulai kelipatan dari `2p` bukan `p*p` (lebih lambat, tetap benar); `vector<bool>` lambat dan bukan kontainer asli; `n = 1` akses `is[1]`; sieve di setiap tes.

**Kompleksitas:** waktu `O(n log log n)`, memori `O(n)`.

---

## Sieve tersegmentasi

**Teori:** prima di `[L, R]` dengan `R` besar (`1e12`) tetapi `R - L` kecil (`≤ 1e6`). Prakomputasi prima `≤ √R`, lalu di array segmen panjang `R - L + 1` matikan kelipatan. Analoginya: kamu tidak menyaring seluruh kota, hanya satu blok jalan, tetapi masih memakai daftar kapten global.

**Kapan:** “prima di `[L, R]`”, `R ≤ 1e12`, `R - L ≤ 1e6`. Jangan alokasi `is[R]`. Jangan trial setiap angka di segmen jika segmen panjang 1e6 dan `√R = 1e6` — itu `1e12` kerja.

**Proses:** prima di `[20, 40]`. `√40 ≈ 6.3`, prima kecil: 2, 3, 5.

```
segmen indeks: 20..40
2 memukul 20,22,...,40
3 memukul 21,24,27,30,33,36,39
5 memukul 20,25,30,35,40
hidup: 23,29,31,37
```

Kelipatan pertama `p` di `[L, R]` adalah `ceil(L / p) * p`, minimal `p * p` jika ingin skip kelipatan yang lebih kecil dari `p^2` (sudah ditangani karena `p` sendiri di luar segmen jika `p < L`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> primes_upto(int n) {
    vector<char> is(n + 1, 1);
    is[0] = is[1] = 0;
    for (int p = 2; (ll)p * p <= n; p++)
        if (is[p])
            for (int q = p * p; q <= n; q += p) is[q] = 0;
    vector<int> p;
    for (int i = 2; i <= n; i++)
        if (is[i]) p.push_back(i);
    return p;
}

vector<ll> sieve_segment(ll L, ll R) {
    ll lim = sqrt((long double)R) + 2;
    auto small = primes_upto((int)lim);
    vector<char> is(R - L + 1, 1);
    for (int p : small) {
        ll start = max((ll)p * p, (L + p - 1) / p * p);
        for (ll x = start; x <= R; x += p) is[x - L] = 0;
    }
    if (L == 1) is[0] = 0;
    if (L == 0) {
        is[0] = 0;
        if (R >= 1) is[1] = 0;
    }
    vector<ll> ans;
    for (ll i = L; i <= R; i++)
        if (is[i - L]) ans.push_back(i);
    return ans;
}

int main() {
    FASTIO;
    auto a = sieve_segment(20, 40);
    for (ll x : a) cout << x << ' ';
    cout << '\n'; // 23 29 31 37
    return 0;
}
```

**Jebakan:** `L = 1` masih menandai 1 sebagai prima; overflow `p * p` pada `int`; start kelipatan salah (`L / p * p` ke bawah tanpa ceil); `sqrt(R)` pada `ll` besar pakai `long double` atau integer sqrt.

**Kompleksitas:** prakomputasi `O(√R log log √R)`, segmen `O((R - L + 1) log log R + π(√R))`, memori `O(R - L + √R)`.

---

## Linear sieve dan SPF

**Teori:** setiap komposit ditandai tepat sekali, oleh prima terkecilnya (SPF, smallest prime factor). Loop `i = 2 .. n`: jika `i` belum punya SPF, ia prima. Lalu untuk setiap prima `p` dengan `p ≤ spf[i]` dan `i * p ≤ n`, set `spf[i * p] = p`. Linear karena tiap `j` dikunjungi sekali. SPF membuat faktorisasi `O(log n)` setelah `O(n)` prakomputasi.

Syarat `p ≤ spf[i]` menjamin `i * p` dicatat oleh prima terkecilnya: jika `p > spf[i]`, maka `spf[i] * (i / spf[i] * p)` sudah / akan ditandai lewat rute lain.

**Kapan:** `n ≤ 1e7`, banyak faktorisasi, totient, Mobius. Sieve biasa cukup jika hanya daftar prima. Jangan linear sieve sampai `1e8` jika memori ketat (`spf` array `int` ≈ 400 MB).

**Proses:** `n = 12`.

```
i=2  prima, spf[2]=2, tandai 4
i=3  prima, spf[3]=3, tandai 6 lalu 9
i=4  spf=2, tandai 8; p=3 berhenti (3 > 2)
i=5  prima, tandai 10
i=6  spf=2, tandai 12; p=3 > 2 stop
i=7  prima
...
```

Hasil SPF: `4:2, 6:2, 8:2, 9:3, 10:2, 12:2`. Prima: 2, 3, 5, 7, 11.

Kenapa 12 tidak ditandai oleh 3: `12 = 3 * 4` tetapi `p = 3 > spf[4] = 2`, loop berhenti. 12 sudah ditandai saat `i = 6`, `p = 2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    LinearSieve s(20);
    for (int p : s.primes) cout << p << ' ';
    cout << '\n';
    for (int i = 2; i <= 20; i++)
        cout << i << ':' << s.spf[i] << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** kondisi `p > spf[i]` dibalik → tidak linear, SPF salah; `i * p` overflow `int`; memakai `spf[1]`; mengisi `spf[i] = i` hanya untuk prima — komposit harus sudah terisi sebelumnya.

**Kompleksitas:** waktu `O(n)`, memori `O(n)`.

---

## Faktorisasi dengan SPF

**Teori:** selama `n > 1`, bagi `n` dengan `spf[n]`, catat pangkat. Setiap langkah `n` mengecil minimal terbagi prima, jumlah langkah `O(log n)`. Tanpa sieve: trial sampai `√n`. Untuk `n ≤ 10^18` sekali: trial sampai `1e7` plus Miller-Rabin / Pollard di file [miller-pollard.md](miller-pollard.md).

**Kapan:** banyak `n ≤ N` setelah sieve `N`. Fungsi multiplikatif, pecah modulus. Jangan trial `√(1e18)` sebanyak `1e5` query.

**Proses:** `n = 360`, anggap SPF sudah ada.

```
spf[360]=2 → 2, n=180
spf[180]=2 → 2, n=90
spf[90]=2  → 2, n=45
spf[45]=3  → 3, n=15
spf[15]=3  → 3, n=5
spf[5]=5   → 5, n=1
360 = 2^3 · 3^2 · 5
```

Tanpa array, trial:

```
2|360 tiga kali → 45
3|45 dua kali  → 5
5 prima
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    auto spf = spf_build(1000);
    auto f = faktor_spf(360, spf);
    for (auto [p, c] : f) cout << p << '^' << c << ' ';
    cout << '\n'; // 2^3 3^2 5^1
    return 0;
}
```

**Jebakan:** `n` lebih besar dari ukuran array SPF; `n = 1` hasil kosong (benar); push setiap faktor tanpa menggabungkan pangkat; `spf` sieve klasik lupa `if (spf[j] == j)` sehingga menimpa dengan prima lebih besar.

**Kompleksitas:** prakomputasi `O(n log log n)` atau `O(n)` linear, query `O(log n)`.

---

## Banyak dan jumlah pembagi

**Teori:** jika `n = p1^{a1} … pk^{ak}`, maka jumlah pembagi `d(n) = (a1+1)…(ak+1)`, jumlah nilai pembagi `σ(n) = Π (p^{a+1} − 1) / (p − 1)`. Pembagi = pilih pangkat `0 .. ai` independen. Analoginya menu: untuk tiap topping, pilih berapa sendok dari 0 sampai maksimum.

**Kapan:** “berapa pembagi”, “jumlah semua pembagi”, bilangan sempurna `σ(n) − n = n`. Hitung `d(n)` untuk semua `n ≤ N` dengan sieve kelipatan. Jangan enumerasi `1 .. n` per query.

**Proses:** `n = 360 = 2^3 · 3^2 · 5^1`.

```
d(360) = 4 * 3 * 2 = 24
σ(360) = (2^4-1)/(2-1) * (3^3-1)/(3-1) * (5^2-1)/(5-1)
       = 15 * 13 * 6 = 1170
```

Sebagian pembagi: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 120, 180, 360. Ada 24.

`n = 1`: `d(1) = 1`, `σ(1) = 1`.

`n = 28` sempurna: pembagi proper 1+2+4+7+14 = 28.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

int main() {
    FASTIO;
    vector<pair<ll, int>> f = {{2, 3}, {3, 2}, {5, 1}};
    cout << d_from_faktor(f) << ' ' << sigma_from_faktor(f) << '\n';
    // 24 1170
    return 0;
}
```

**Jebakan:** overflow `σ` untuk `n` besar; `d(1) = 1`; rumus `(p^{a+1}-1)/(p-1)` bagi integer vs jumlah pangkat (jumlah pangkat lebih aman); menghitung `d(n)` sebagai jumlah loop `i <= n`.

**Kompleksitas:** rumus `O(jumlah prima berbeda)` setelah faktor.

---

## Sieve kelipatan untuk d dan σ

**Teori:** untuk semua `n ≤ N`, setiap `i` adalah pembagi semua kelipatan `j = i, 2i, 3i, …`. Tambah 1 ke `d[j]` dan tambah `i` ke `sig[j]`. Ini lemma harmonik: `Σ_{i=1}^N floor(N / i) = Θ(N log N)`.

Linear sieve juga bisa: jika `spf[i] = p` dan `p^2 | i` maka `d[i] = d[i / p] / a * (a + 1)` dengan `a` pangkat `p`; jika `p` baru, `d[i] = d[i / p] * 2`.

**Kapan:** butuh `d[1..N]` atau `σ[1..N]` sekaligus, `N ≤ 1e7`. Satu query `n ≤ 1e12` → faktor lalu rumus, bukan sieve.

**Proses:** `N = 10`.

| n | pembagi | d | σ |
|---:|---|---:|---:|
| 1 | 1 | 1 | 1 |
| 2 | 1,2 | 2 | 3 |
| 3 | 1,3 | 2 | 4 |
| 4 | 1,2,4 | 3 | 7 |
| 5 | 1,5 | 2 | 6 |
| 6 | 1,2,3,6 | 4 | 12 |
| 7 | 1,7 | 2 | 8 |
| 8 | 1,2,4,8 | 4 | 15 |
| 9 | 1,3,9 | 3 | 13 |
| 10 | 1,2,5,10 | 4 | 18 |

`i = 3` menambah `d` dan `σ` pada 3, 6, 9.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

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
    FASTIO;
    vector<int> d;
    vector<ll> sig;
    sieve_d_sigma(10, d, sig);
    cout << d[10] << ' ' << sig[10] << '\n'; // 4 18
    cout << d[9] << ' ' << sig[8] << '\n';   // 3 15
    return 0;
}
```

**Jebakan:** loop dari `i = 0`; `sig` `int` overflow; membangun tabel `1e7` per tes; mengira kompleksitas `O(n)` — ini `O(n log n)`.

**Kompleksitas:** waktu `O(n log n)`, memori `O(n)`.

---

## Peta keputusan

```
gcd / lcm / pecahan          → Euclid, bagi dulu baru kali
gcd / lcm array              → lipat kiri-ke-kanan
prima satu n ≤ 1e12          → trial √n
prima banyak n ≤ 1e7         → sieve / linear sieve
prima di [L,R], R besar      → sieve tersegmentasi
prima n ≤ 1e18 banyak query  → Miller-Rabin
faktor banyak n ≤ 1e7        → SPF
faktor n ≤ 1e18              → Pollard + MR
d(n), σ(n) satu angka        → faktor lalu rumus
d[1..N], σ[1..N]             → sieve kelipatan
```

| alat | batas nyaman | keluaran |
|---|---|---|
| Euclid | 64-bit | `gcd` |
| LCM aman | produk muat `ll` | `lcm` atau gagal |
| trial | `n ≤ 1e12` | prima / faktor |
| Eratosthenes | `n ≤ 1e7` | daftar prima |
| linear + SPF | `n ≤ 1e7` | `spf`, `φ`, `μ` |
| segmen | `R−L ≤ 1e6` | prima di rentang |

---

## Ringkasan

1. Euclid = sisa bagi berulang. Inisialisasi GCD array dari 0 aman.
2. LCM = bagi dulu, baru kali. Cek overflow sebelum `x * b`.
3. Trial `√n` untuk sedikit angka; sieve untuk banyak angka kecil.
4. Linear sieve menandai tiap komposit sekali dan memberi SPF.
5. `d(n)` dan `σ(n)` dari pangkat, atau sieve kelipatan untuk seluruh prefix.
6. `n = 1e18` bukan ranah sieve — pindah ke [miller-pollard.md](miller-pollard.md).

Invers dan `nCr`: [modular-ncr.md](modular-ncr.md).
