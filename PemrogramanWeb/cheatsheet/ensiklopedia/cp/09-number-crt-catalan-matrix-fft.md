# 09 — CRT, Catalan, matrix expo, XOR basis, dan FFT

[← 08 sieve & modular](08-number-sieve-gcd-modular.md) · [Indeks](README.md) · [Lanjut: graf →](10-graf-dfs-bfs-topo.md)

Kurikulum: folder **07 — Teori Bilangan & Aljabar** bagian lanjut di `DAFTAR-MATERI` (Day 092 CRT, 099 Catalan/Stirling/Burnside, 103 inklusi-eksklusi, 105 Mobius, 108 matrix expo, 111 XOR basis, 246 FFT).

Latihan harian: `KULIAH/ComProgLearning/CP` (Day-90-an sampai aljabar; FFT di roadmap lanjutan).

> **Ide satu kalimat:** CRT menyatukan sisa-sisa, pencacahan memakai Catalan/Stirling/Mobius, matrix expo meloncat rekurens `10^18` langkah, XOR basis merangkum `2^n` subset jadi ≤64 vektor, FFT/NTT mengubah konvolusi `O(n^2)` menjadi `O(n log n)`.

## Daftar isi

- [CRT untuk modulus koprima](#crt-untuk-modulus-koprima)
- [CRT umum (modulus tidak koprima)](#crt-umum-modulus-tidak-koprima)
- [Bilangan Catalan](#bilangan-catalan)
- [Stirling jenis kedua](#stirling-jenis-kedua)
- [Burnside](#burnside)
- [Inklusi-eksklusi](#inklusi-eksklusi)
- [Fungsi Mobius dan inversi](#fungsi-mobius-dan-inversi)
- [Perkalian matriks dan matrix expo](#perkalian-matriks-dan-matrix-expo)
- [Rekurens linear](#rekurens-linear)
- [Basis linear XOR](#basis-linear-xor)
- [Ide FFT: kenapa konvolusi jadi cepat](#ide-fft-kenapa-konvolusi-jadi-cepat)
- [FFT rekursif yang benar](#fft-rekursif-yang-benar)
- [FFT iteratif dan perkalian polinom](#fft-iteratif-dan-perkalian-polinom)
- [NTT](#ntt)
- [Peta keputusan bab ini](#peta-keputusan-bab-ini)
- [Ringkasan folder 07 lanjut](#ringkasan-folder-07-lanjut)

## CRT untuk modulus koprima

**Teori:** sistem `x ≡ a_i (mod m_i)` punya solusi unik modulo `M = m_1 m_2 … m_k` jika semua `m_i` **berpasangan koprima**. Rumus: `M_i = M / m_i`, `t_i = invers(M_i, m_i)`, `x = Σ a_i M_i t_i (mod M)`. Kenapa benar: `M_i ≡ 0 (mod m_j)` untuk `j≠i`, dan `M_i t_i ≡ 1 (mod m_i)`, jadi suku ke-`i` menyisakan `a_i` di modulus `m_i` dan 0 di modulus lain. Analoginya: tiga jam dengan periode 3, 5, 7 — ada tepat satu menit dalam 105 menit yang cocok dengan ketiga jarum.

**Kapan:** pecah modulus `m = p1^{k1} …`, gabung jawaban DP / invers, “cari x yang sisa-sisanya …”. Jangan rumus ini jika ada `gcd(m_i, m_j) > 1` — pakai CRT umum. Jangan overflow `M` tanpa `__int128`.

**Proses:** 

```
x ≡ 2 (mod 3)
x ≡ 3 (mod 5)
x ≡ 2 (mod 7)
```

`M = 105`.

| i | a | m | M_i=M/m | M_i mod m | invers | suku a·M_i·t |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | 2 | 3 | 35 | 2 | 2 | 2·35·2=140 |
| 2 | 3 | 5 | 21 | 1 | 1 | 3·21·1=63 |
| 3 | 2 | 7 | 15 | 1 | 1 | 2·15·1=30 |

`x = 140+63+30 = 233 ≡ 23 (mod 105)` karena `233-2*105=233-210=23`.

Cek: `23=7*3+2`, `23=4*5+3`, `23=3*7+2`. Pas.

`invers(2,3)`: `2*2=4≡1`.

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
    if (g != 1 && g != -1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

// a[i] mod m[i], m berpasangan koprima, M muat ll
ll crt_koprima(const vector<ll>& a, const vector<ll>& m) {
    int k = (int)a.size();
    ll M = 1;
    for (ll x : m) M *= x;
    ll x = 0;
    for (int i = 0; i < k; i++) {
        ll Mi = M / m[i];
        ll t = inv_exgcd(Mi % m[i], m[i]);
        ll suku = (__int128)a[i] * Mi % M * t % M;
        x += suku;
        if (x >= M) x -= M;
    }
    return x;
}

int main() {
    cout << crt_koprima({2, 3, 2}, {3, 5, 7}) << '\n'; // 23
    cout << crt_koprima({1, 1}, {2, 3}) << '\n';       // 1
    return 0;
}
```

**Jebakan:** `M_i % m_i` lupa sebelum invers (Mi bisa > m); overflow `M`; modulus tidak koprima tetap dipaksa; `x` negatif setelah jumlah.

**Kompleksitas:** `O(k log M)` karena invers. Memori `O(k)`.

---

## CRT umum (modulus tidak koprima)

**Teori:** dua kongruensi `x ≡ a (mod m)`, `x ≡ b (mod n)` solvable iff `a ≡ b (mod gcd(m,n))`. Jika ya, modulus gabungan `lcm(m,n)`, solusi unik di situ. Gabungkan berpasangan. Kenapa syarat itu: `x=a+m s = b+n t` → `m s - n t = b-a`, jadi `gcd(m,n) | (b-a)`. Analoginya: dua jadwal yang periodenya tidak koprima hanya ketemu jika selisih fase-nya kelipatan GCD.

**Kapan:** modulus `10^9` dan `10^9+9` yang `gcd>1`, atau `mod 12` plus `mod 18`. Jangan rumus koprima. Jika suatu pasangan gagal, seluruh sistem gagal.

**Proses:** `x ≡ 2 (mod 4)` dan `x ≡ 6 (mod 10)`.

`gcd(4,10)=2`. `2 ≡ 6 (mod 2)`? `4 ≡ 0` ya (beda 4, habis 2).

Exgcd: `4s - 10t = 4`, bagi 2: `2s - 5t = 2`. Satu solusi `s=1` (`2-5*0=2`), `x=2+4*1=6`.

`lcm=20`. Umum: `x=6+20 k`. Cek: `6 mod 4=2`, `6 mod 10=6`. `26` juga.

Gagal: `x ≡ 1 (mod 4)`, `x ≡ 6 (mod 10)`. `1-6=-5` tidak habis 2.

Tiga modulus: gabung (1) dengan (2) jadi satu, lalu dengan (3).

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

// gabung x ≡ a (mod m) dan x ≡ b (mod n)
// return false jika mustahil; hasil x, mod = lcm
bool crt_gabung(ll a, ll m, ll b, ll n, ll& x, ll& mod) {
    ll s, t;
    ll g = exgcd(m, n, s, t);
    if ((b - a) % g) return false;
    ll n_g = n / g;
    ll k = ((__int128)(b - a) / g * s) % n_g;
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
    ll x, mod;
    cout << crt_umum({2, 6}, {4, 10}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 6 20
    cout << crt_umum({1, 6}, {4, 10}, x, mod) << '\n'; // 0
    cout << crt_umum({2, 3, 2}, {3, 5, 7}, x, mod) << ' ' << x << ' ' << mod << '\n';
    // 1 23 105
    return 0;
}
```

**Jebakan:** `(b-a)` overflow; `s` dari exgcd dikali tanpa `% (n/g)`; modulus hasil overflow `ll`; menggabungkan tanpa cek `g | (b-a)`.

**Kompleksitas:** `O(k log)` plus hati-hati overflow. Memori `O(1)` tambahan.

---

## Bilangan Catalan

**Teori:** `C_0 = 1`, `C_{n+1} = Σ_{i=0}^{n} C_i C_{n-i}`, atau `C_n = (1/(n+1)) C(2n, n) = C(2n,n) - C(2n, n-1)`. Menghitung: kurung sah, pohon biner, triangulasi poligon `(n+2)` sisi, jalur monotonic yang tidak melewati diagonal, urutan stack-sortable. Kenapa rumus rekursi: kurung `n+1` pasangan = `( A ) B` dengan `A` punya `i` pasangan, `B` punya `n-i`. Analoginya: setiap ekspresi kurung punya pasangan luar, isi dalam dan sisa kanan independen.

**Kapan:** “banyak cara kurung / pohon / jalur tidak turun ke bawah y=x”. Mod prima → `C(2n,n) * inv(n+1)`. Jangan loop rekursi `O(n^2)` jika `n=1e6` — pakai rumus binomial. Jangan `C(2n,n)/(n+1)` di integer tanpa pasti habis dulu (lebih aman kali invers).

**Proses:** hitung `C_0..C_5` dari rekursi.

```
C0=1
C1=C0 C0=1
C2=C0 C1 + C1 C0=1+1=2
C3=C0 C2 + C1 C1 + C2 C0=2+1+2=5
C4=C0 C3 + C1 C2 + C2 C1 + C3 C0=5+2+2+5=14
C5=C0 C4 + C1 C3 + C2 C2 + C3 C1 + C4 C0=14+5+4+5+14=42
```

Rumus: `C_4 = C(8,4)/5 = 70/5=14`. `C_5=C(10,5)/6=252/6=42`.

Kurung `n=3`: lima string `((())) (()()) (())() ()(()) ()()()`.

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
    Comb cb(30);
    auto d = catalan_dp(10);
    for (int i = 0; i <= 6; i++)
        cout << cb.catalan(i) << ' ' << d[i] << '\n';
    // 1 1, 1 1, 2 2, 5 5, 14 14, 42 42, 132 132
    return 0;
}
```

**Jebakan:** `2n` melewati ukuran `fact`; `n+1` tidak invertibel jika `MOD | (n+1)` — pecah atau modulus lain; off-by-one “n pasang kurung” vs “n+2 sisi poligon”; overflow `C(2n,n)` di `ll` tanpa mod (`C(40,20)` sudah `1e11`, `C(60,30)` melewati `ll`).

**Kompleksitas:** rumus `O(n + log MOD)` prakomputasi, `O(1)` query. DP `O(n^2)`. Memori `O(n)`.

---

## Stirling jenis kedua

**Teori:** `S(n,k)` = banyak cara membagi `n` objek **berbeda** ke `k` kotak **tidak kosong** yang **tidak berlabel**. Rekurens: `S(n,k) = k S(n-1,k) + S(n-1,k-1)`. Masukkan benda ke-`n` ke salah satu `k` kotak yang sudah ada, atau kotak baru sendiri. `S(n,1)=1`, `S(n,n)=1`, `S(n,0)=0` untuk `n>0`, `S(0,0)=1`. Jika kotak berlabel: `k! S(n,k)` = `k^n` surjektif, rumus inklusi-eksklusi. Analoginya: bagi `n` mahasiswa ke `k` kelompok diskusi tanpa nama kelompok.

**Kapan:** “partisi himpunan”, “kelompok tidak kosong”, Bell number `B_n = Σ S(n,k)`. Jangan tertukar dengan Stirling jenis pertama (siklus). Jangan menghitung `k^n` tanpa surjektif jika kosong dilarang.

**Proses:** tabel kecil.

```
      k=0 1 2 3 4
n=0    1
n=1    0 1
n=2    0 1 1
n=3    0 1 3 1
n=4    0 1 7 6 1
```

`S(4,2)=7`: pola `3+1` ada `C(4,1)=4` (siapa sendirian), pola `2+2` ada `C(4,2)/2=3` (bagi dua, bagi 2 karena urutan kelompok). `4+3=7`.

`S(3,2)=3`: `{12|3},{13|2},{23|1}`.

Bell `B_4 = 1+7+6+1=15`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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

ll surjektif(int n, int k, const vector<vector<ll>>& S, const vector<ll>& fact) {
    return S[n][k] * fact[k] % MOD;
}

int main() {
    auto S = stirling2(6);
    cout << S[4][2] << ' ' << S[5][3] << '\n'; // 7 25
    ll bell = 0;
    for (int k = 0; k <= 4; k++) bell += S[4][k];
    cout << bell << '\n';                      // 15
    return 0;
}
```

`S(5,3)=25`: rumus `3*S(4,3)+S(4,2)=3*6+7=25`.

**Jebakan:** `k * S[i-1][k]` overflow sebelum `%` — cast `ll`; `S[0][0]`; tertukar jenis pertama; `k! S(n,k)` vs `S(n,k)` (label).

**Kompleksitas:** `O(n^2)` waktu dan memori. Ada `O(n log n)` lewat FFT / rumus `S(n,k) = 1/k! Σ (-1)^{k-j} C(k,j) j^n`.

---

## Burnside

**Teori:** jumlah pewarnaan **berbeda sampai simetri** = rata-rata jumlah pewarnaan yang **tetap** di tiap elemen grup. `1/|G| Σ_{g∈G} Fix(g)`. `Fix(g)` = `k^{c(g)}` untuk `k` warna dan `c(g)` siklus pada benda yang diwarnai. Kenapa benar: tiap orbit dihitung `|G| / |stabilizer|` kali jika dihitung mentah; Burnside meratakan. Analoginya: kalung yang boleh diputar — jangan hitung rotasi sebagai kalung baru.

**Kapan:** kalung, pewarnaan kubus/gelang, grid dengan rotasi/refleksi. `|G|` kecil (4, 6, 8, 24). Jangan enumerasi `k^n` lalu masuk `set` untuk `n=20`. Jangan lupa `|G|` invers modulo, atau bagi dulu jika `Fix` selalu kelipatan `|G|`.

**Proses:** pewarna `k=2` pada **3 manik** di gelang, hanya **rotasi** (`C3`).

Grup: rotasi 0°, 120°, 240°.

```
id      : 3 siklus (tiap manik)     Fix=2^3=8
120°    : 1 siklus (semua muter)    Fix=2^1=2   (semua warna sama)
240°    : 1 siklus                  Fix=2
rata    : (8+2+2)/3 = 4
```

Empat kalung: WWW, BBB, WWB (sama dengan BWW, WBW lewat putar), WBB (sama dengan BWB, BBW).

Tanpa Burnside kamu menulis 8 string lalu men-orbit-kan: `{WWW}, {BBB}, {WWB,WBW,BWW}, {WBB,BWB,BBW}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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

// kalung n manik, k warna, hanya rotasi (grup cyclic)
ll kalung_rotasi(int n, int k, ll MOD) {
    ll sum = 0;
    for (int d = 0; d < n; d++) {
        // rotasi d*360/n: jumlah siklus = gcd(d,n)
        int cyc = std::gcd(d, n);
        sum += modpow(k, cyc, MOD);
        if (sum >= MOD) sum -= MOD;
    }
    return sum * modpow(n, MOD - 2, MOD) % MOD; // |G|=n, n vs MOD koprima
}

int main() {
    const ll MOD = 1000000007LL;
    cout << kalung_rotasi(3, 2, MOD) << '\n'; // 4
    cout << kalung_rotasi(4, 2, MOD) << '\n'; // 6
    return 0;
}
```

`n=4,k=2`: `(2^4 + 2^1 + 2^2 + 2^1)/4 = (16+2+4+2)/4=6`. Enam kalung biner sampai rotasi.

Jika ada pantulan (diedral), tambahkan `|G|=2n` elemen, hitung siklus refleksi (beda `n` genap/ganjil).

**Jebakan:** membagi `n` padahal `MOD | n`; salah hitung siklus rotasi (`gcd`); menghitung refleksi seperti rotasi; `|G|` tidak lengkap.

**Kompleksitas:** cyclic `O(n log k)` atau `O(d(n))` jika dilipat `φ`. Memori `O(1)`.

---

## Inklusi-eksklusi

**Teori:** `|A ∪ B| = |A| + |B| - |A ∩ B|`. Tiga himpunan: tambah tunggal, kurang pasangan, tambah irisan tiga. Umum: `Σ (−1)^{|S|+1} |∩_{i∈S} A_i|`. Kenapa: elemen di tepat `r` himpunan dihitung `C(r,1)-C(r,2)+… = 1`. Analoginya: absensi ganda di dua klub harus dikurangi sekali.

**Kapan:** “habis dibagi 2 atau 3 atau 5”, surjektif, derangement `n! Σ (-1)^k / k!`, “tidak ada posisi tetap”. `m` syarat dengan `m ≤ 20` enumerasi mask. Jangan `m=30` tanpa struktur.

**Proses:** berapa angka `1..30` habis 2, 3, atau 5?

```
|A2|=15, |A3|=10, |A5|=6
|A2∩A3|=5 (6,12,18,24,30)
|A2∩A5|=3 (10,20,30)
|A3∩A5|=2 (15,30)
|ketiga|=1 (30)
union = 15+10+6 -5-3-2 +1 = 22
```

Cek cepat: buang yang tidak habis 2,3,5: 1,7,11,13,17,19,23,29 = 8, `30-8=22`.

Derangement `n=3`: `!3 = 3!(1 -1 +1/2 -1/6)=6-6+3-1=2`. Dua: `2,3,1` dan `3,1,2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll habis_atau(ll n, const vector<ll>& p) {
    int m = (int)p.size();
    ll ans = 0;
    for (int mask = 1; mask < (1 << m); mask++) {
        ll l = 1;
        bool ov = false;
        for (int i = 0; i < m && !ov; i++) if (mask & (1 << i)) {
            if (l > n / p[i]) ov = true;
            else l *= p[i];
        }
        if (ov) continue;
        ll tanda = (__builtin_popcount(mask) % 2) ? 1 : -1;
        ans += tanda * (n / l);
    }
    return ans;
}

ll derange(int n) {
    ll d = 1;                              // !0 = 1
    for (int i = 1; i <= n; i++)
        d = i * d + (i % 2 ? -1 : 1);      // !n = n·!(n-1) + (-1)^n
    return d;
}

int main() {
    cout << habis_atau(30, {2, 3, 5}) << '\n'; // 22
    cout << derange(3) << '\n';                // 2
    cout << derange(4) << '\n';                // 9
    return 0;
}
```

`!4=9`. `!n = (n-1) [!(n-1)+!(n-2)]` juga benar.

**Jebakan:** tanda `(-1)^{|S|}` vs `{|S|+1}`; LCM vs kali (jika `p` tidak koprima, **harus LCM** bukan kali — di kode di atas `p` diasumsikan prima / koprima); overflow `l *= p[i]`; derange overflow `ll` cepat.

**Kompleksitas:** `O(2^m · m)` untuk `m` syarat. Derange `O(n)`.

---

## Fungsi Mobius dan inversi

**Teori:** `μ(1)=1`, `μ(n)=0` jika ada kuadrat prima, `μ(n)=(-1)^k` jika `n` hasil `k` prima berbeda. Sifat kunci: `Σ_{d|n} μ(d) = [n==1]`. Inversi: jika `g(n) = Σ_{d|n} f(d)` maka `f(n) = Σ_{d|n} μ(d) g(n/d)`. Versi kelipatan: `g(n)=Σ_{n|d} f(d)` punya inversi serupa. Analoginya: Möbius adalah “tanda inklusi-eksklusi siap pakai” pada kisi pembagi.

**Kapan:** jumlah `gcd(i,j)==1`, “coprime pairs”, ganti syarat `gcd==k` menjadi `k | gcd` lalu Mobius. Sieve `μ[1..n]` linear. Jangan trial `μ` per query jika `n` banyak dan kecil.

**Proses:** `μ` kecil:

| n | faktor | μ |
| ---: | --- | ---: |
| 1 | — | 1 |
| 2 | 2 | -1 |
| 3 | 3 | -1 |
| 4 | 2^2 | 0 |
| 5 | 5 | -1 |
| 6 | 2·3 | 1 |
| 7 | 7 | -1 |
| 8 | 2^3 | 0 |
| 9 | 3^2 | 0 |
| 10 | 2·5 | 1 |
| 30 | 2·3·5 | -1 |

`Σ_{d|6} μ(d) = μ(1)+μ(2)+μ(3)+μ(6)=1-1-1+1=0` karena 6≠1. `Σ_{d|1} μ=1`.

Banyak pasangan `1≤i,j≤n` dengan `gcd=1`: `Σ_{d=1}^n μ(d) floor(n/d)^2`.

`n=3`: pasangan gcd1: (1,1)(1,2)(1,3)(2,1)(2,3)(3,1)(3,2) = 7? Juga (2,1) dst. Total 3×3=9, minus (2,2)(3,3) =7. Rumus: `μ(1)*9 + μ(2)*1 + μ(3)*1 = 9-1-1=7`. Ya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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

ll coprime_pairs(int n, const vector<int>& mu) {
    ll ans = 0;
    for (int d = 1; d <= n; d++) {
        ll t = n / d;
        ans += (ll)mu[d] * t * t;
    }
    return ans;
}

int main() {
    auto mu = sieve_mu(30);
    for (int i = 1; i <= 10; i++) cout << mu[i] << ' ';
    cout << '\n';                          // 1 -1 -1 0 -1 1 -1 0 0 1
    cout << coprime_pairs(3, mu) << '\n';  // 7
    return 0;
}
```

**Jebakan:** `μ[1]`; linear sieve `break` saat `q | i` wajib (supaya kuadrat → 0); rumus `floor` overflow `t*t`; menginversi arah `d|n` vs `n|d` tertukar.

**Kompleksitas:** sieve `O(n)`, rumus pasangan `O(n)` atau `O(√n)` dengan blocks `floor`. Memori `O(n)`.

---

## Perkalian matriks dan matrix expo

**Teori:** `(AB)_{ij} = Σ_k A_{ik} B_{kj}`. Perkalian asosiatif, jadi `A^e` bisa kuadrat berulang seperti `modpow`. Ukuran `k×k`, `e` sampai `10^18` → `O(k^3 log e)`. Analoginya: satu langkah linier “maju satu hari”; `e` hari = matriks dipangkatkan.

**Kapan:** rekurens linear, jumlah jalur berbobot panjang `e` di graf kecil (`adj^e`), tiling. Jangan `k=100`, `e=1e18` tanpa modulus ringan — `k^3 log e ≈ 1e8` masih bisa, `k=300` berat. Jangan kalikan `e` kali.

**Proses:** Fibonacci. Vektor `[F_{n+1}, F_n] = [F_n + F_{n-1}, F_n]`.

```
[ F_{n+1} ]   [ 1 1 ] [ F_n     ]
[ F_n     ] = [ 1 0 ] [ F_{n-1} ]
```

Jadi 

```
[ 1 1 ]^n = [ F_{n+1}  F_n    ]
[ 1 0 ]     [ F_n      F_{n-1}]
```

`n=6`: `F_6=8`, `F_7=13`, `F_5=5`.

```
[1 1]^6 = [13 8]
[1 0]     [ 8 5]
```

Cek kali: `[1 1]^2 = [2 1; 1 1]`, `^3=[3 2; 2 1]`, `^4=[5 3; 3 2]`, `^5=[8 5; 5 3]`, `^6=[13 8; 8 5]`. Cocok (`F_1=1,F_2=1,F_0=0,F_3=2,...`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

using mat = vector<vector<ll>>;

mat kali(const mat& a, const mat& b) {
    int n = (int)a.size();
    int m = (int)b[0].size();
    int p = (int)b.size();
    mat c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < p; k++)
            for (int j = 0; j < m; j++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

mat ident(int n) {
    mat I(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) I[i][i] = 1;
    return I;
}

mat mpow(mat a, ll e) {
    int n = (int)a.size();
    mat r = ident(n);
    while (e) {
        if (e & 1) r = kali(r, a);
        a = kali(a, a);
        e >>= 1;
    }
    return r;
}

ll fib(ll n) {
    if (n == 0) return 0;
    mat a = {{1, 1}, {1, 0}};
    return mpow(a, n - 1)[0][0];           // F_n
}

int main() {
    for (int i = 0; i <= 10; i++) cout << fib(i) << ' ';
    cout << '\n';                          // 0 1 1 2 3 5 8 13 21 34 55
    cout << fib(50) << '\n';               // 12586269025 % MOD? 50 kecil, 12586269025
    return 0;
}
```

`fib(50)` tanpa mod = `12586269025`, muat `ll`. Dengan `MOD` hasilnya `12586269025 % (1e9+7)`.

**Jebakan:** `e=0` harus identitas, bukan nol; `fib(0)`; urutan loop `i,k,j` vs cache; `k=0` matriks kosong; modulus lupa di kali.

**Kompleksitas:** `O(k^3 log e)` waktu, `O(k^2)` memori.

---

## Rekurens linear

**Teori:** `x_n = c_1 x_{n-1} + … + c_k x_{n-k}`. Bentuk matriks companion:

```
[ x_n     ]   [ c1 c2 ... ck ] [ x_{n-1} ]
[ x_{n-1} ]   [ 1  0  ... 0  ] [ x_{n-2} ]
[ ...     ] = [ 0  1  ... 0  ] [ ...     ]
[ x_{n-k+1}]  [ 0  0  ... 0  ] [ x_{n-k} ]
```

Baris pertama koefisien, di bawah pergeseran. Pangkat `n-k` (sesuai indexing) memberi `x_n`. Analoginya: state adalah jendela `k` nilai terakhir.

**Kapan:** trib, rec `k ≤ 100`, `n ≤ 1e18`. Jumlah `x_1+...+x_n` — perbesar state dengan satu akumulator. Jangan DP `O(n)` untuk `n=1e18`.

**Proses:** trib `T_n = T_{n-1}+T_{n-2}+T_{n-3}`, `T_0=0,T_1=0,T_2=1` (seperti Fibonacci digeser; atau `0,1,1` sesuai soal). Pakai `0,1,1`:

```
n=0..7: 0,1,1,2,4,7,13,24
```

Matriks 3×3:

```
[1 1 1]
[1 0 0]
[0 1 0]
```

`[T_n, T_{n-1}, T_{n-2}]^T = M [T_{n-1}, T_{n-2}, T_{n-3}]^T`.

Dari `(T2,T1,T0)=(1,1,0)` ke `(T5,T4,T3)`: `M^3`.

```
M^1 [1,1,0] = [1+1+0, 1, 1] = [2,1,1] = (T3,T2,T1) OK
M^2 [1,1,0] = M[2,1,1] = [2+1+1, 2, 1] = [4,2,1] = (T4,T3,T2) OK
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;
using mat = vector<vector<ll>>;

mat kali(const mat& a, const mat& b) {
    int n = (int)a.size();
    mat c(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

mat mpow(mat a, ll e) {
    int n = (int)a.size();
    mat r(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) r[i][i] = 1;
    while (e) {
        if (e & 1) r = kali(r, a);
        a = kali(a, a);
        e >>= 1;
    }
    return r;
}

ll linear_rec(const vector<ll>& c, vector<ll> init, ll n) {
    // x[i] = c[0] x[i-1] + c[1] x[i-2] + ...  untuk i>=k
    // init = x[0..k-1]
    int k = (int)c.size();
    if (n < k) return init[n] % MOD;
    mat M(k, vector<ll>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = c[j] % MOD;
    for (int i = 1; i < k; i++) M[i][i - 1] = 1;
    mat P = mpow(M, n - (k - 1));
    // state awal: [x_{k-1}, x_{k-2}, ..., x_0]
    ll ans = 0;
    for (int j = 0; j < k; j++) {
        ll x = init[k - 1 - j] % MOD;
        ans = (ans + P[0][j] * x) % MOD;
    }
    return ans;
}

int main() {
    // trib: T_n = T_{n-1}+T_{n-2}+T_{n-3}, init 0,1,1
    vector<ll> c = {1, 1, 1}, init = {0, 1, 1};
    for (int n = 0; n <= 7; n++)
        cout << linear_rec(c, init, n) << ' ';
    cout << '\n';                          // 0 1 1 2 4 7 13 24
    return 0;
}
```

**Jebakan:** indexing `n` 0-based vs “suku ke-n”; urutan `init` terbalik vs baris matriks; `n < k`; koefisien negatif + modulus.

**Kompleksitas:** `O(k^3 log n)`.

---

## Basis linear XOR

**Teori:** himpunan angka, operasi XOR, membentuk ruang vektor atas `GF(2)`. Basis: kumpulan vektor independen yang menghasilkan semua XOR subset. Gaussian: dari bit tinggi, tiap bit punya paling banyak satu perwakilan. Insert `x`: dari bit 63 ke 0, jika bit hidup dan basis ada, `x ^= b[i]`; jika kosong, taruh `x`. `insert` return true jika `x` independen (memperbesar ruang). Ukuran basis `r` → `2^r` nilai XOR berbeda. Analoginya: eliminasi Gauss pada baris biner.

**Kapan:** XOR subset maksimum / ke-k, “bisa membentuk X?”, kueri online sisip angka. `n ≤ 1e5`, nilai `≤ 1e18`. Jangan enumerasi `2^n`.

**Proses:** sisip `5, 3, 7`.

```
5 = 101  bit2 kosong → b[2]=101 (5)
3 = 011  bit1 (tertinggi 3) kosong → b[1]=011 (3)
7 = 111  bit2: 111^101=010
         bit1: 010^011=001
         bit0 kosong → b[0]=001 (1)
```

Basis `{5,3,1}`, rank 3, ruang 8 nilai (semua 0..7).

XOR maksimum (greedy dari bit tinggi):

```
ans=0
bit2: ans^5=5 > 0 → ans=5
bit1: 5^3=6 > 5 → ans=6
bit0: 6^1=7 > 6 → ans=7
```

Cek subset: `5^3^7=5^3^7=1^7=6`? `5^3=6`, `6^7=1`. `5^3=6`. `7` sendiri=7. Maks 7.

Bisa `4`? `4=100`. Reduksi: `100 ^ b[2]=100^101=001`, `001^b[0]=0`. Ya, `4 = 5^1 = 5^3^7` wait 1=7^5^3, `5^1=4`. Ya.

Angka `9=1001` pada basis 3-bit di atas: bit3 kosong jika kita punya 64 slot — `b[3]=9` jika n lebih besar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct XorBasis {
    ll b[64];
    int rank;
    XorBasis() {
        memset(b, 0, sizeof(b));
        rank = 0;
    }
    bool insert(ll x) {
        for (int i = 63; i >= 0; i--) {
            if (((x >> i) & 1) == 0) continue;
            if (!b[i]) {
                b[i] = x;
                rank++;
                return true;
            }
            x ^= b[i];
        }
        return false;                      // x sudah bisa dibentuk
    }
    bool bisa(ll x) const {
        for (int i = 63; i >= 0; i--)
            if ((x >> i) & 1) x ^= b[i];
        return x == 0;
    }
    ll max_xor() const {
        ll ans = 0;
        for (int i = 63; i >= 0; i--)
            ans = max(ans, ans ^ b[i]);
        return ans;
    }
    ll kth_xor(ll k) const {               // 0-index, 0 = XOR kosong
        // asumsikan semua 2^rank nilai, k < 2^rank
        vector<ll> v;
        for (int i = 0; i < 64; i++)
            if (b[i]) v.push_back(b[i]);
        // orthonormal dari rendah: opsional, versi sederhana dari bit basis
        ll ans = 0;
        int idx = 0;
        for (int i = 0; i < 64; i++) if (b[i]) {
            if ((k >> idx) & 1) ans ^= b[i];
            idx++;
        }
        return ans;                        // urutan bukan sorted; lihat catatan
    }
};

int main() {
    XorBasis xb;
    cout << xb.insert(5) << xb.insert(3) << xb.insert(7) << '\n'; // 1 1 1
    cout << xb.rank << '\n';               // 3
    cout << xb.max_xor() << '\n';          // 7
    cout << xb.bisa(4) << ' ' << xb.bisa(8) << '\n'; // 1 0
    cout << xb.insert(4) << '\n';          // 0, sudah di ruang
    return 0;
}
```

`kth_xor` di atas **bukan** “XOR ke-k terkecil” kecuali basis sudah dinormalisasi. Untuk ke-k terkecil: Gaussian sampai tiap `b[i]` unik di bit `i`, lalu pakai bit `k` dari rendah.

Normalisasi tambahan (opsional):

```cpp
void normalisasi(XorBasis& xb) {
    for (int i = 63; i >= 0; i--) if (xb.b[i])
        for (int j = 63; j >= 0; j--)
            if (i != j && ((xb.b[j] >> i) & 1))
                xb.b[j] ^= xb.b[i];
}
```

**Jebakan:** loop bit 31 untuk `ll`; `insert` tidak mengurangi `x` sebelum cek slot; `max` memakai `min` salah arah; `k` 1-based vs 0 = kosong; mengira rank selalu 64.

**Kompleksitas:** insert / query `O(64^2)` atau `O(64)`. `n` insert `O(64 n)`. Memori `O(64)`.

---

## Ide FFT: kenapa konvolusi jadi cepat

**Teori:** konvolusi dua array `c[k] = Σ_{i+j=k} a[i] b[j]` adalah perkalian polinom. Naif `O(n^2)`. DFT mengevaluasi polinom di `n` akar satuan `ω^0,…,ω^{n-1}` dengan `ω = e^{-2π i / n}`. Di titik-titik itu, perkalian polinom = **kali berpasangan** nilai. Inverse DFT mengembalikan koefisien. FFT (Cooley–Tukey) menghitung DFT dalam `O(n log n)`: pecah indeks genap/ganjil, `T(n)=2T(n/2)+O(n)`, `n` pangkat 2.

```
A(x) = A_even(x^2) + x A_odd(x^2)
A(ω^k)   = Ae(ω^{2k}) + ω^k Ao(ω^{2k})
A(ω^{k+n/2}) = Ae(...) - ω^k Ao(...)
```

Dua DFT berukuran `n/2` plus `n/2` kupu-kupu.

Analoginya: daripada menjumlahkan semua pasangan `(i,j)` di meja, kamu “memotret” polinom di titik ajaib, kali foto, lalu rekonstruksi. Titik ajaib membuat geser-indeks menjadi putar-fase.

NTT = FFT yang sama, tetapi `ω` hidup di modulo prima `p = q·2^s + 1`. Tidak ada error pecahan. `998244353 = 119 · 2^{23} + 1`, akar primitif `3`.

**Kapan:** perkalian polinom, string matching (wildcard), 3SUM-ish, count pasangan jumlah, knapsack banyak item sama lewat generating function. `n ≤ 1<<20` (~1e6) lolos. Jangan FFT untuk `n=50` kecuali mau — `O(n^2)` lebih sederhana. Jangan FFT double jika butuh exact mod `1e9+7` (bukan NTT-friendly) tanpa trik (tiga modulus / split).

**Proses:** `A=1+2x+3x^2`, `B=2+x`. Naif:

```
(1+2x+3x^2)(2+x)=2 + x + 4x + 2x^2 + 6x^2 + 3x^3
= 2 + 5x + 8x^2 + 3x^3
```

Koefisien `[1,2,3] * [2,1] = [2,5,8,3]`.

Pilih `n=4` (pangkat 2, `≥ 3+1`). Akar `ω = e^{-2π i / 4} = -i`.

Evaluasi (sketsa): FFT menghitung 4 nilai, kali 4 pasangan, inverse, `llround` → `[2,5,8,3]`.

Ukuran wajib: `n ≥ deg(A)+deg(B)+1`, `n` pangkat 2. Kalau kurang, koefisien berlipat aliasing.

**Kode:** seksi ide tidak perlu implementasi penuh — lihat dua seksi berikut. Mini cek naif:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> conv_naif(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> c(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    return c;
}

int main() {
    auto c = conv_naif({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';       // 2 5 8 3
    cout << '\n';
    return 0;
}
```

**Jebakan:** `n` bukan pangkat 2; `n` terlalu pendek; memakai `pow` double untuk `ω` di loop dalam (akumulasi error) — `cis` berulang juga error, tetapi standar; mengira FFT menggantikan semua `O(n^2)` termasuk yang bukan konvolusi.

**Kompleksitas:** ide `O(n log n)` vs naif `O(n^2)`. Memori `O(n)`.

---

## FFT rekursif yang benar

**Teori:** implementasi langsung rumus pecah genap/ganjil. Basis `n=1`. Inverse memakai `ω^{-1}` dan bagi 2 di tiap level (atau bagi `n` di akhir — di sini bagi 2 tiap level, total `/n`). Ini benar, lebih mudah dibaca, lebih lambat dan boros memori daripada iteratif.

**Kapan:** paham / debug. Untuk submit, pakai iteratif. `n ≤ 1<<18` rekursif masih sering lolos.

**Proses:** `n=2`, `a=[1,2]`, `ω = e^{-π i} = -1` untuk forward? `2π/2=π`, `e^{-iπ}=-1`.

```
a0=[1], a1=[2]
y0 = 1 + (-1)^0 * 2 = 3
y1 = 1 - 2 = -1
```

DFT `[1,2]` size 2 = `[3,-1]`. Inverse: `ω=+1` arah, bagi 2: `[(3+(-1))/2, (3-(-1))/2]=[1,2]`. Kembali.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    auto c = kali_polinom_rec({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';       // 2 5 8 3
    cout << '\n';
    auto d = kali_polinom_rec({4, 0, 1}, {1, 1}); // (4+x^2)(1+x)=4+4x+x^2+x^3
    for (ll x : d) cout << x << ' ';       // 4 4 1 1
    cout << '\n';
    return 0;
}
```

**Jebakan:** `n` ganjil; lupa `resize` pangkat 2; inverse tanpa bagi; `llround` vs `(ll)(x.real()+0.5)` pada negatif; `acos(-1)` vs `M_PI` portabel.

**Kompleksitas:** `O(n log n)` waktu, `O(n log n)` memori stack + vektor sementara. Lebih boros dari iteratif.

---

## FFT iteratif dan perkalian polinom

**Teori:** bit-reversal permutation menaruh indeks seperti daun rekursi, lalu kupu-kupu bottom-up `len=2,4,...,n`. Sama benarnya dengan rekursif. Ini versi yang biasa disalin di kontes.

**Kapan:** submit. Koefisien muat di `double` dengan aman kira-kira `|c[k]| < 1e12` setelah konvolusi (aturan kasar; lebih besar rawan `llround` salah). Exact integer besar → NTT.

**Proses:** sama `[1,2,3]*[2,1]=[2,5,8,3]`. `n=4`. Bit-reversal 2-bit: `00,01,10,11` → `00,10,01,11` yaitu indeks `0,2,1,3`.

Setelah permute `a=[1,3,2,0]` (pad 0). Butterfly `len=2`, lalu `len=4`. Hasil evaluasi, kali `b`, inverse, round.

Cek kedua: `[1,1,1] * [1,1,1] = [1,2,3,2,1]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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

vector<ll> kali_polinom(const vector<ll>& a, const vector<ll>& b) {
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
    auto c = kali_polinom({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n';                          // 2 5 8 3
    auto d = kali_polinom({1, 1, 1}, {1, 1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n';                          // 1 2 3 2 1
    return 0;
}
```

**Jebakan:** `while (n < a.size()+b.size())` vs `size()+size()-1` — `n ≥ deg jumlah + 1` = `sa+sb-1`, loop `n < sa+sb` aman (satu lebih). Bit-reversal salah. `x /= n` lupa. Presisi: koefisien `1e15` bisa salah round. `vector<bool>` bukan isu di sini.

**Kompleksitas:** `O(n log n)` waktu, `O(n)` memori, `n` pangkat 2 ≥ panjang hasil.

---

## NTT

**Teori:** DFT di `Z/pZ`. Butuh `n | (p-1)`, `n=2^k`. `ω = g^{(p-1)/n}` dengan `g` akar primitif. Inverse `ω^{-1}` dan `n^{-1}`. Untuk `p=998244353`, `g=3`, `n ≤ 2^{23}`. Hasil **exact** modulo `p`. Langkah kupu-kupu identik FFT, ganti `cis` jadi `modpow`.

**Kapan:** konvolusi modular `998244353`, banyak soal CF. Mod `1e9+7` **bukan** NTT-friendly — pakai NTT tiga modulus + CRT, atau split coefficient, atau `O(n^2)`. Jangan NTT double-modulus tanpa CRT.

**Proses:** sama `[1,2,3]*[2,1] ≡ [2,5,8,3] (mod 998244353)` karena angka kecil.

`n=4`, `ω = 3^{(p-1)/4}`. `p-1=998244352`, `/4=249561088`. `ω^4=1`, `ω^2=-1`. Butterfly jalan, inverse kali `inv(4)`.

Cek: `2,5,8,3` tidak berubah modulo.

Contoh yang “terbungkus”: kalau hasil `c[i] ≥ p`, NTT memberi `c[i] % p`, bukan `c[i]` asli. Untuk hitung integer kecil, `p` besar jadi aman.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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

vector<ll> kali_ntt(vector<ll> a, vector<ll> b) {
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
    auto c = kali_ntt({1, 2, 3}, {2, 1});
    for (ll x : c) cout << x << ' ';
    cout << '\n';                          // 2 5 8 3
    auto d = kali_ntt({1, 1, 1}, {1, 1, 1});
    for (ll x : d) cout << x << ' ';
    cout << '\n';                          // 1 2 3 2 1
    return 0;
}
```

Akar primitif: `3` benar untuk `998244353`. Modulus NTT lain yang sering: `7340033`, `1004535809`. Jangan ganti `G` sembarangan.

**Jebakan:** `MOD-1` tidak habis `len` (n terlalu besar > 2^23); `G` bukan primitive root; inverse `wlen` vs inverse `n` tertukar; `u-v` negatif tanpa `+MOD`; memakai NTT ini untuk `1e9+7`; `int` overflow `w*v` — di sini `ll`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`, `n ≤ 2^{23}` untuk modulus ini.

---

## Peta keputusan bab ini

```
sistem sisa
├── m_i koprima berpasangan     → CRT rumus produk
└── ada gcd > 1                 → gabung 2-2, cek g|(a-b)

counting
├── kurung / pohon / jalur      → Catalan
├── partisi himpunan            → Stirling-2 / Bell
├── sampai simetri              → Burnside
├── union syarat / derange      → inklusi-eksklusi
└── gcd==1, f ↔ g di pembagi    → Mobius

barisan n=1e18
└── rekurens linear k kecil     → matrix expo

XOR subset
└── max / ada / sisip           → basis 64-bit

kali polinom / konvolusi
├── angka kecil, boleh double   → FFT
├── mod 998244353               → NTT
├── mod 1e9+7 exact             → 3-NTT+CRT atau naif
└── n ≤ 2000                    → naif saja
```

| alat | input tipikal | keluaran |
| --- | --- | --- |
| CRT | sisa + modulus | satu `x` |
| Catalan | `n` | `C_n` |
| Stirling-2 | `n,k` | partisi |
| Burnside | grup + warna | orbit |
| Mobius | `n` atau array | inversi jumlah |
| `A^e` | matriks `k`, `e` | `k×k` |
| XOR basis | `n` angka 64-bit | rank, max |
| FFT/NTT | 2 polinom | konvolusi |

---

## Ringkasan folder 07 lanjut

1. CRT koprima = jumlah `a_i M_i t_i`. Tidak koprima = gabung berpasangan plus syarat GCD.
2. Catalan = `C(2n,n)/(n+1)` = rekursi konvolusi `C_i C_{n-1-i}`.
3. Stirling-2 membagi objek berbeda ke kotak tak bernama; kali `k!` jika kotak bernama.
4. Burnside: rata-rata `Fix(g)`, siklus `gcd` untuk rotasi gelang.
5. Inklusi-eksklusi dan Mobius adalah satu keluarga tanda plus-minus.
6. Matrix expo memindahkan jendela rekurens sejauh `10^18`.
7. XOR basis: Gauss di `GF(2)`, paling banyak 64 vektor.
8. FFT/NTT: evaluasi di akar satuan, kali titik, interpolasi. Kode iteratif di atas adalah versi yang benar; uji dulu `[1,2,3]*[2,1]=[2,5,8,3]`.

Kembali ke [08 sieve & modular](08-number-sieve-gcd-modular.md) jika invers / sieve belum nyaman. Lanjut graf di file 10 jika sudah ada.
