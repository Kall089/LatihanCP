# Catalan, Stirling, dan Burnside

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **099**. Pencacahan klasik: kurung, partisi, simetri.

> **Ide satu kalimat:** Catalan menghitung struktur “tidak pernah negatif”, Stirling membagi objek ke kotak, Burnside merata-ratakan pewarnaan yang tetap di tiap simetri.

Butuh `nCr`: [modular-ncr.md](modular-ncr.md). Inklusi-eksklusi terkait: [inklusi-mobius.md](inklusi-mobius.md).

## Daftar isi

- [Bilangan Catalan](#bilangan-catalan)
- [Catalan DP konvolusi](#catalan-dp-konvolusi)
- [Ballot dan jalur](#ballot-dan-jalur)
- [Stirling jenis kedua](#stirling-jenis-kedua)
- [Stirling jenis pertama](#stirling-jenis-pertama)
- [Bell](#bell)
- [Burnside rotasi](#burnside-rotasi)
- [Burnside diedral singkat](#burnside-diedral-singkat)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Bilangan Catalan

**Teori:** `C_0 = 1`, `C_n = (1/(n+1)) C(2n, n) = C(2n, n) − C(2n, n−1)`. Rekurens: `C_{n} = Σ_{i=0}^{n−1} C_i C_{n−1−i}`. Menghitung: kurung sah `n` pasangan, pohon biner, triangulasi poligon `(n+2)` sisi, jalur monotonic yang tidak melewati diagonal, urutan stack-sortable. Kenapa rekursi: kurung `n` pasangan = `( A ) B` dengan `A` punya `i` pasangan, `B` punya `n−1−i`. Analoginya: setiap ekspresi punya pasangan luar; isi dalam dan sisa kanan independen.

Mod prima: `C(2n, n) * inv(n+1)`. Jangan bagi integer mentah jika tidak yakin habis — kali invers lebih aman.

**Kapan:** “banyak cara kurung / pohon / jalur tidak di bawah y = x”. `n ≤ 1e6` pakai rumus binomial. Jangan DP `O(n^2)` untuk `n = 1e6`. Jangan off-by-one “n pasang” vs “n+2 sisi”.

**Proses:** rumus untuk `C_4` dan `C_5`.

```
C_4 = C(8, 4) / 5 = 70 / 5 = 14
C_5 = C(10, 5) / 6 = 252 / 6 = 42
C_6 = C(12, 6) / 7 = 924 / 7 = 132
```

`C(8, 4) − C(8, 3) = 70 − 56 = 14`. Sama.

Kurung `n = 3` (lima string): `((()))`, `(()())`, `(())()`, `()(())`, `()()()`.

Triangulasi segi-`n+2`: `n = 4` → segi-6 → 14 cara.

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
        for (int i = n; i > 0; i--) invfact[i - 1] = invfact[i] * i % MOD;
    }
    ll C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }
    ll catalan(int n) {
        return C(2 * n, n) * modpow(n + 1, MOD - 2) % MOD;
    }
};

int main() {
    FASTIO;
    Comb cb(30);
    for (int i = 0; i <= 6; i++) cout << cb.catalan(i) << ' ';
    cout << '\n'; // 1 1 2 5 14 42 132
    return 0;
}
```

**Jebakan:** `2n` melewati ukuran `fact`; `MOD | (n+1)` sehingga `n+1` tidak invertibel; overflow `C(2n, n)` di `ll` tanpa mod (`C(40,20)` sudah `1e11`, `C(60,30)` pecah `ll`); indeks poligon.

**Kompleksitas:** prakomputasi `O(n + log MOD)`, query `O(1)`.

---

## Catalan DP konvolusi

**Teori:** `C_0 = 1`, `C_n = Σ_i C_i C_{n−1−i}`. Ini konvolusi — untuk `n` besar bisa [FFT](fft.md), untuk `n ≤ 3000` naif cukup. Berguna jika modulus tidak prima atau kamu sudah punya tabel kecil.

**Kapan:** `n ≤ 2000`, atau merakit jawaban dari potongan “dalam / luar”. Jangan `n = 1e5` naif.

**Proses:**

```
C0 = 1
C1 = C0 C0 = 1
C2 = C0 C1 + C1 C0 = 1+1 = 2
C3 = C0 C2 + C1 C1 + C2 C0 = 2+1+2 = 5
C4 = C0 C3 + C1 C2 + C2 C1 + C3 C0 = 5+2+2+5 = 14
C5 = 14+5+4+5+14 = 42
C6 = 42+14+10+10+14+42 = 132
```

Setiap baris jumlah pasangan yang indeknya `i + j = n−1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

vector<ll> catalan_dp(int n) {
    vector<ll> c(n + 1);
    c[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++)
            c[i] = (c[i] + c[j] * c[i - 1 - j]) % MOD;
    }
    return c;
}

int main() {
    FASTIO;
    auto d = catalan_dp(10);
    for (int i = 0; i <= 6; i++) cout << d[i] << ' ';
    cout << '\n'; // 1 1 2 5 14 42 132
    return 0;
}
```

**Jebakan:** `c[j] * c[i-1-j]` overflow sebelum `%` jika `MOD^2` melewati `ll` — untuk `1e9+7` masih muat `ll`; off-by-one `i-1-j` vs `i-j`.

**Kompleksitas:** `O(n^2)` waktu, `O(n)` memori.

---

## Ballot dan jalur

**Teori:** teorema ballot: kandidat A unggul `a` suara, B `b` suara, `a > b ≥ 0`. Peluang A selalu di depan B (setelah suara pertama, atau ketat sepanjang jalan — cek pernyataan soal) adalah `(a − b) / (a + b) * C(a+b, a)` untuk versi klasik. Catalan adalah kasus `a = n+1`, `b = n` atau jalur `(1,0)` vs `(0,1)` yang tidak di bawah diagonal: banyak jalur dari `(0,0)` ke `(n,n)` dengan langkah `(1,0),(0,1)` yang `y ≤ x` sama dengan `C_n`.

Analoginya: antrian kurung — prefix tidak punya lebih banyak `)` daripada `(`.

**Kapan:** grid, tanda kurung, stack, “skor tidak tersusul”. Jangan pakai Catalan jika jalur **boleh** menyentuh di bawah lalu kembali — itu bilangan lain (Motzkin / Schroeder) atau DP biasa.

**Proses:** ke `(3,3)`, tidak di atas `y = x` jika `x` = buka, `y` = tutup. Sama `C_3 = 5`.

Semua `C(6, 3) = 20` jalur bebas. Yang “buruk” ada `20 − 5 = 15`. Reflection: jalur yang menyentuh `y = x+1` dipantulkan, jumlahnya `C(6, 2) = 15`. `20 − 15 = 5`.

`n = 2`: bebas `C(4,2)=6`, pantul `C(4,1)=4`, Catalan `2`. Dua sah: `()()`, `(())`.

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

ll catalan_ballot(int n, const vector<ll>& fact, const vector<ll>& invfact) {
    auto C = [&](int a, int b) {
        if (b < 0 || b > a) return 0LL;
        return fact[a] * invfact[b] % MOD * invfact[a - b] % MOD;
    };
    // C(2n,n) - C(2n, n-1)
    return (C(2 * n, n) - C(2 * n, n - 1) + MOD) % MOD;
}

int main() {
    FASTIO;
    int N = 20;
    vector<ll> fact(N + 1), invfact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    invfact[N] = modpow(fact[N], MOD - 2);
    for (int i = N; i >= 1; i--) invfact[i - 1] = invfact[i] * i % MOD;
    for (int n = 0; n <= 5; n++) cout << catalan_ballot(n, fact, invfact) << ' ';
    cout << '\n'; // 1 1 2 5 14 42
    return 0;
}
```

**Jebakan:** `C(2n, n-1)` untuk `n = 0` harus 0; pengurangan negatif; versi ballot “lemah vs ketat”.

**Kompleksitas:** `O(1)` setelah tabel.

---

## Stirling jenis kedua

**Teori:** `S(n, k)` = banyak cara membagi `n` objek **berbeda** ke `k` kotak **tidak kosong** yang **tidak berlabel**. Rekurens: `S(n, k) = k S(n−1, k) + S(n−1, k−1)`. Masukkan benda ke-`n` ke salah satu `k` kotak yang sudah ada, atau kotak baru sendiri. `S(n, 1) = 1`, `S(n, n) = 1`, `S(n, 0) = 0` untuk `n > 0`, `S(0, 0) = 1`. Kotak berlabel: `k! S(n, k)` = jumlah surjektif `k^n` minus kosong, rumus inklusi-eksklusi. Analoginya: bagi `n` mahasiswa ke `k` kelompok diskusi tanpa nama kelompok.

**Kapan:** partisi himpunan, “kelompok tidak kosong”, Bell. Jangan tertukar dengan jenis pertama (siklus). Jangan `k^n` jika kosong dilarang.

**Proses:** tabel.

```
      k=0 1 2 3 4
n=0    1
n=1    0 1
n=2    0 1 1
n=3    0 1 3 1
n=4    0 1 7 6 1
n=5    0 1 15 25 10 1
```

`S(4, 2) = 7`: pola `3+1` ada `C(4, 1) = 4` (siapa sendirian), pola `2+2` ada `C(4, 2)/2 = 3`. `4+3=7`.

`S(3, 2) = 3`: `{12|3}`, `{13|2}`, `{23|1}`.

`S(5, 3) = 3 * S(4, 3) + S(4, 2) = 3*6 + 7 = 25`.

Rumus langsung: `S(n, k) = (1/k!) Σ_{j=0}^k (−1)^{k−j} C(k, j) j^n`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

vector<vector<ll>> stirling2(int n) {
    vector<vector<ll>> S(n + 1, vector<ll>(n + 1, 0));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        S[i][1] = 1;
        S[i][i] = 1;
        for (int k = 2; k < i; k++)
            S[i][k] = (k * S[i - 1][k] + S[i - 1][k - 1]) % MOD;
    }
    return S;
}

int main() {
    FASTIO;
    auto S = stirling2(6);
    cout << S[4][2] << ' ' << S[5][3] << '\n'; // 7 25
    ll bell = 0;
    for (int k = 0; k <= 4; k++) bell += S[4][k];
    cout << bell << '\n'; // 15
    return 0;
}
```

**Jebakan:** `k * S[i-1][k]` overflow sebelum `%`; `S[0][0]`; tertukar jenis pertama; lupa `k!` jika kotak berlabel.

**Kompleksitas:** `O(n^2)` waktu dan memori.

---

## Stirling jenis pertama

**Teori:** `|s(n, k)|` (tanda tak) = banyak permutasi `n` objek dengan tepat `k` siklus. Bertanda `s(n, k)` memenuhi `x(x−1)…(x−n+1) = Σ s(n, k) x^k`. Rekurens tak bertanda: `c(n, k) = c(n−1, k−1) + (n−1) c(n−1, k)`. Siklus baru sendirian, atau sisipkan elemen `n` ke salah satu `n−1` celah siklus yang sudah ada. Analoginya: `n` orang menari dalam `k` lingkaran.

**Kapan:** “permutasi dengan k siklus”, tanda naik/turun pada falling factorial. Jangan campur dengan `S(n, k)`.

**Proses:**

```
c(0,0)=1
c(4,1)=6     (3! = 6 siklus Hamilton)
c(4,2)=11
c(4,3)=6
c(4,4)=1
jumlah = 24 = 4!
```

`c(4, 2) = c(3,1) + 3 c(3,2)`. `c(3,1)=2`, `c(3,2)=3`, `2+9=11`.

Siklus `n=3`: `k=1` ada 2 yaitu `(123),(132)`; `k=2` ada 3 yaitu satu 2-siklus plus fixed point; `k=3` identitas.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

vector<vector<ll>> stirling1_unsigned(int n) {
    vector<vector<ll>> c(n + 1, vector<ll>(n + 1, 0));
    c[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        c[i][1] = 1; // untuk i>=1, (i-1)! sebenarnya; isi lewat rekurens lebih aman
        for (int k = 1; k <= i; k++)
            c[i][k] = (c[i - 1][k - 1] + (i - 1) * c[i - 1][k]) % MOD;
    }
    return c;
}

int main() {
    FASTIO;
    auto c = stirling1_unsigned(6);
    cout << c[4][1] << ' ' << c[4][2] << ' ' << c[4][3] << '\n'; // 6 11 6
    ll sum = 0;
    for (int k = 0; k <= 4; k++) sum += c[4][k];
    cout << sum << '\n'; // 24
    return 0;
}
```

Catatan: baris `c[i][1] = 1` di atas ditimpa rekurens; untuk `i ≥ 1`, `c[i][1] = (i−1)!`. Setelah loop, `c[4][1]` harus 6.

**Jebakan:** `+ (n-1) * c[n-1][k]` vs `+ k * …` (itu jenis kedua); tanda `(-1)^{n-k}`; `c[0][0]`.

**Kompleksitas:** `O(n^2)`.

---

## Bell

**Teori:** `B_n = Σ_{k=0}^n S(n, k)` = semua partisi himpunan `n` elemen. Rekurens: `B_{n+1} = Σ_{j=0}^n C(n, j) B_j`. Analoginya: elemen `n+1` memilih j teman serumah, sisa dipartisi bebas.

**Kapan:** “berapa pengelompokan”, exponential generating function `exp(e^x − 1)`. `n ≤ 1000` dari tabel `S`, atau rekurens `O(n^2)`.

**Proses:**

```
B0=1
B1=1
B2=2     {{1,2}}, {{1}{2}}
B3=5
B4=15
B5=52
```

`B_4 = C(3,0)B0 + C(3,1)B1 + C(3,2)B2 + C(3,3)B3 = 1+3+6+5 = 15`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1000000007LL;

vector<ll> bell_dp(int n) {
    vector<ll> B(n + 1), Cprev, Ccur;
    B[0] = 1;
    for (int i = 0; i < n; i++) {
        // C(i, j)
        vector<ll> C(i + 1);
        C[0] = 1;
        for (int j = 1; j <= i; j++)
            C[j] = C[j - 1] * (i - j + 1) % MOD *
                   ([] (ll a, ll m) {
                       ll r = 1, e = m - 2;
                       while (e) {
                           if (e & 1) r = r * a % MOD;
                           a = a * a % MOD;
                           e >>= 1;
                       }
                       return r;
                   })(j, MOD) % MOD;
        ll s = 0;
        for (int j = 0; j <= i; j++) s = (s + C[j] * B[j]) % MOD;
        B[i + 1] = s;
    }
    return B;
}

int main() {
    FASTIO;
    auto B = bell_dp(6);
    for (int i = 0; i <= 5; i++) cout << B[i] << ' ';
    cout << '\n'; // 1 1 2 5 15 52
    return 0;
}
```

Tabel `Comb` di [modular-ncr.md](modular-ncr.md) lebih bersih untuk produksi; di sini C(i,j) dihitung on the fly.

**Jebakan:** `B_0`; overflow `C(i,j)` mentah; mengira `B_n = n!` (itu permutasi, bukan partisi).

**Kompleksitas:** `O(n^2 + n log MOD)` dengan cara di atas.

---

## Burnside rotasi

**Teori:** jumlah pewarnaan **berbeda sampai simetri** = rata-rata jumlah pewarnaan yang **tetap** di tiap elemen grup. `1/|G| Σ_{g ∈ G} Fix(g)`. Untuk `k` warna dan `c(g)` siklus pada benda, `Fix(g) = k^{c(g)}`. Kenapa: tiap orbit dihitung `|G| / |stabilizer|` kali jika dihitung mentah; Burnside meratakan. Analoginya: kalung yang boleh diputar — jangan hitung rotasi sebagai kalung baru.

Rotasi `d` langkah pada `n` manik: jumlah siklus = `gcd(d, n)`.

**Kapan:** kalung, pewarnaan gelang, grid dengan rotasi. `|G|` kecil (4, 6, 8, 24). Jangan enumerasi `k^n` lalu `set` untuk `n = 20`. Jangan lupa invers `|G|` modulo, atau bagi dulu jika `Fix` selalu kelipatan `|G|`.

**Proses:** `n = 3` manik, `k = 2` warna, hanya rotasi `C3`.

```
id   0°   : 3 siklus   Fix = 2^3 = 8
120°      : 1 siklus   Fix = 2
240°      : 1 siklus   Fix = 2
rata      : (8+2+2)/3 = 4
```

Empat kalung: WWW, BBB, WWB, WBB.

`n = 4`, `k = 2`:

```
d=0 gcd(0,4)=4  (pakai gcd(d,n); d=0 → n siklus)  2^4=16
d=1 gcd=1                                     2
d=2 gcd=2                                     4
d=3 gcd=1                                     2
(16+2+4+2)/4 = 6
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

ll kalung_rotasi(int n, int k, ll MOD) {
    ll sum = 0;
    for (int d = 0; d < n; d++) {
        int cyc = std::gcd(d, n);
        if (d == 0) cyc = n;
        sum += modpow(k, cyc, MOD);
        if (sum >= MOD) sum -= MOD;
    }
    return sum * modpow(n, MOD - 2, MOD) % MOD;
}

int main() {
    FASTIO;
    const ll MOD = 1000000007LL;
    cout << kalung_rotasi(3, 2, MOD) << '\n'; // 4
    cout << kalung_rotasi(4, 2, MOD) << '\n'; // 6
    return 0;
}
```

`std::gcd(0, n) = n`, jadi cabang `d == 0` redundan tetapi memperjelas.

**Jebakan:** membagi `n` padahal `MOD | n`; salah hitung siklus (`gcd`); `|G|` tidak lengkap; `k^{cyc}` overflow tanpa mod.

**Kompleksitas:** `O(n log k)` atau `O(d(n))` jika dilipat `φ`. Memori `O(1)`.

---

## Burnside diedral singkat

**Teori:** grup diedral `D_n` punya `2n` elemen: `n` rotasi plus `n` pantulan. Untuk `n` ganjil, tiap pantulan: 1 siklus (manik pada sumbu) + `(n−1)/2` siklus 2-manik → `c = 1 + (n−1)/2`. Untuk `n` genap, ada dua jenis: sumbu melalui 2 manik (`c = 2 + (n−2)/2 = n/2 + 1`) dan sumbu melalui 2 sisi (`c = n/2`). Analoginya: kalung boleh dibalik.

**Kapan:** soal secara eksplisit mengizinkan flip. Jangan campur jika hanya rotasi.

**Proses:** `n = 3`, `k = 2`, diedral `|G| = 6`.

```
3 rotasi: 8+2+2 = 12
3 pantulan (n ganjil): masing-masing c = 1+1 = 2, Fix = 2^2 = 4
jumlah Fix = 12 + 12 = 24
rata = 24/6 = 4
```

Kebetulan sama dengan hanya rotasi untuk `k = 2, n = 3` (WWB sama dengan BWW sudah tercakup rotasi; flip tidak menambah identifikasi baru di kasus ini). 

`n = 4`, `k = 2`, `|G| = 8`.

```
rotasi: 16+2+4+2 = 24
2 sumbu manik: c=3, Fix=8, total 16
2 sumbu sisi:  c=2, Fix=4, total 8
jumlah 48, rata 48/8 = 6
```

Lagi-lagi 6 untuk biner n=4. Untuk `k = 3`, `n = 4` rotasi vs diedral berbeda.

Rotasi `n=4,k=3`: `(3^4 + 3^1 + 3^2 + 3^1)/4 = (81+3+9+3)/4 = 24`.

Diedral: pantulan manik `3^{3}=27` dua kali = 54; sisi `3^2=9` dua kali = 18. `(81+3+9+3+54+18)/8 = 168/8 = 21`.

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

ll kalung_diedral(int n, int k, ll MOD) {
    ll sum = 0;
    for (int d = 0; d < n; d++) {
        int cyc = std::gcd(d, n);
        if (d == 0) cyc = n;
        sum += modpow(k, cyc, MOD);
        if (sum >= MOD) sum -= MOD;
    }
    if (n % 2 == 1) {
        ll fix = modpow(k, 1 + (n - 1) / 2, MOD);
        sum = (sum + (ll)n * fix) % MOD;
    } else {
        ll thru = modpow(k, n / 2 + 1, MOD);
        ll edge = modpow(k, n / 2, MOD);
        sum = (sum + (ll)(n / 2) * thru + (ll)(n / 2) * edge) % MOD;
    }
    ll invG = modpow(2 * n, MOD - 2, MOD);
    return sum * invG % MOD;
}

int main() {
    FASTIO;
    const ll MOD = 1000000007LL;
    cout << kalung_diedral(3, 2, MOD) << '\n'; // 4
    cout << kalung_diedral(4, 3, MOD) << '\n'; // 21
    return 0;
}
```

**Jebakan:** jenis sumbu genap tertukar; membagi `2n` saat `MOD | 2n`; memakai rumus rotasi untuk flip.

**Kompleksitas:** `O(n log k)`.

---

## Peta keputusan

```
kurung / pohon / jalur diagonal   → Catalan
partisi himpunan, kotak tak nama  → Stirling-2
permutasi k siklus                → Stirling-1
semua partisi                     → Bell
kotak bernama, tidak kosong       → k! S(n,k) / IE surjektif
sampai rotasi / flip              → Burnside
n besar, C_n                      → C(2n,n)*inv(n+1), bukan DP
```

| objek | rumus cepat | off-by-one umum |
|---|---|---|
| `n` pasang kurung | `C_n` | `C_{n+1}` |
| segi-`m` triangulasi | `C_{m-2}` | `C_m` |
| jalur `(n,n)` Dyck | `C_n` | `C_{2n}` |
| surjektif `n→k` | `k! S(n,k)` | `S(n,k)` |

---

## Ringkasan

1. Catalan = `C(2n,n)/(n+1)` = konvolusi `C_i C_{n-1-i}` = selisih binomial pantulan.
2. Stirling-2 membagi objek berbeda ke kotak tak bernama; kali `k!` jika bernama.
3. Stirling-1 menghitung siklus; jumlah baris = `n!`.
4. Bell = jumlah baris Stirling-2.
5. Burnside: rata-rata `k^{siklus}`; rotasi memakai `gcd`; flip menambah jenis sumbu.

Inklusi-eksklusi dan Mobius: [inklusi-mobius.md](inklusi-mobius.md).
