# Matrix expo dan basis XOR

[← 07 Teori bilangan](README.md) · [Indeks CP](../README.md)

Day: **108–111**. Rekurens `10^18` langkah, ruang vektor `GF(2)`.

> **Ide satu kalimat:** pangkatkan matriks seperti `modpow` untuk meloncat rekurens linear; Gaussian pada bit merangkum `2^n` subset XOR menjadi paling banyak 64 vektor.

Perkalian skalar modular: [modular-ncr.md](modular-ncr.md).

## Daftar isi

- [Perkalian matriks](#perkalian-matriks)
- [Matrix expo](#matrix-expo)
- [Fibonacci sebagai matriks](#fibonacci-sebagai-matriks)
- [Rekurens linear umum](#rekurens-linear-umum)
- [Jumlah jalur dan akumulator](#jumlah-jalur-dan-akumulator)
- [Basis XOR: sisip](#basis-xor-sisip)
- [Max XOR dan bisa membentuk](#max-xor-dan-bisa-membentuk)
- [Normalisasi dan XOR ke-k](#normalisasi-dan-xor-ke-k)
- [Peta keputusan](#peta-keputusan)
- [Ringkasan](#ringkasan)

---

## Perkalian matriks

**Teori:** `(AB)_{ij} = Σ_k A_{ik} B_{kj}`. Ukuran `n × p` kali `p × m` → `n × m`. Tidak komutatif: `AB ≠ BA` pada umumnya. Asosiatif: `(AB)C = A(BC)`. Analoginya: tiap entri adalah produk titik baris dan kolom.

Modulo wajib di dalam jumlah jika `MOD` kecil; `a[i][k] * b[k][j]` pakai `ll`.

**Kapan:** satu langkah linier, menyusun expo. Jangan `k = 400` tanpa perlu — `k^3` mahal.

**Proses:** 

```
A = [1 2]     B = [5 6]
    [3 4]         [7 8]

AB = [1*5+2*7  1*6+2*8] = [19 22]
     [3*5+4*7  3*6+4*8]   [43 50]
```

`BA = [5+18 10+24; 7+24 14+32] = [23 34; 31 46] ≠ AB`.

Identitas `I`: diagonal 1. `AI = IA = A`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

int main() {
    FASTIO;
    mat A = {{1, 2}, {3, 4}}, B = {{5, 6}, {7, 8}};
    mat C = kali(A, B);
    cout << C[0][0] << ' ' << C[0][1] << '\n'; // 19 22
    cout << C[1][0] << ' ' << C[1][1] << '\n'; // 43 50
    return 0;
}
```

**Jebakan:** urutan loop `i,k,j` vs cache; `k` dalam (dimensi tengah) tertukar; lupa `%`; `int` overflow hasil kali.

**Kompleksitas:** `O(n p m)`, memori `O(n m)`.

---

## Matrix expo

**Teori:** `A^e` dengan kuadrat berulang. `e = 0` → identitas, bukan nol. Sama seperti `modpow`. Analoginya: satu langkah “maju satu hari”; `e` hari = matriks dipangkatkan.

**Kapan:** rekurens, `adj^e` jumlah jalur panjang `e` di graf kecil. `k ≤ 100`, `e ≤ 1e18` → `k^3 log e ≈ 1e6 * 60` sampai `1e8`. `k = 300` berat. Jangan kalikan `e` kali.

**Proses:** `A = [1 1; 1 0]`, hitung `A^2`, `A^3`.

```
A^2 = [1+1 1+0] = [2 1]
      [1+0 1+0]   [1 1]

A^3 = A^2 A = [2+1 2+0] = [3 2]
              [1+1 1+0]   [2 1]
```

Ini sudah Fibonacci (seksi berikutnya).

`e = 0` harus `I`. Tes: `mpow(A, 0)[0][0] = 1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

int main() {
    FASTIO;
    mat A = {{1, 1}, {1, 0}};
    mat B = mpow(A, 3);
    cout << B[0][0] << ' ' << B[0][1] << '\n'; // 3 2
    cout << B[1][0] << ' ' << B[1][1] << '\n'; // 2 1
    cout << mpow(A, 0)[0][0] << '\n';          // 1
    return 0;
}
```

**Jebakan:** `e = 0` mengembalikan nol; `e` negatif; matriks tidak persegi; modulus lupa di `kali`.

**Kompleksitas:** `O(k^3 log e)` waktu, `O(k^2)` memori.

---

## Fibonacci sebagai matriks

**Teori:**

```
[ F_{n+1} ]   [ 1 1 ] [ F_n     ]
[ F_n     ] = [ 1 0 ] [ F_{n-1} ]
```

Jadi

```
[ 1 1 ]^n = [ F_{n+1}  F_n    ]
[ 1 0 ]     [ F_{n    } F_{n-1}]
```

dengan konvensi `F_0 = 0`, `F_1 = 1`, `F_2 = 1`, `F_3 = 2`. Analoginya: jendela dua suku terakhir.

**Kapan:** `F_n` untuk `n ≤ 1e18`. Jumlah `F_1 + … + F_n = F_{n+2} − 1`. Jangan loop `n` kali.

**Proses:** `n = 6`. `F_6 = 8`, `F_7 = 13`, `F_5 = 5`.

```
A^1 = [1 1; 1 0]
A^2 = [2 1; 1 1]
A^3 = [3 2; 2 1]
A^4 = [5 3; 3 2]
A^5 = [8 5; 5 3]
A^6 = [13 8; 8 5]
```

`F_n = A^{n-1}[0][0]` untuk `n ≥ 1`. `F_0 = 0` khusus.

`F_10 = 55`. `F_50 = 12586269025` (muat `ll` tanpa mod).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

ll fib(ll n) {
    if (n == 0) return 0;
    mat a = {{1, 1}, {1, 0}};
    return mpow(a, n - 1)[0][0];
}

int main() {
    FASTIO;
    for (int i = 0; i <= 10; i++) cout << fib(i) << ' ';
    cout << '\n'; // 0 1 1 2 3 5 8 13 21 34 55
    return 0;
}
```

**Jebakan:** `fib(0)`; indexing `A^n` vs `A^{n-1}`; `F_1` vs `F_2` keduanya 1; `MOD` mengubah `F_50`.

**Kompleksitas:** `O(log n)`.

---

## Rekurens linear umum

**Teori:** `x_n = c_1 x_{n-1} + … + c_k x_{n-k}`. Companion:

```
[ x_n       ]   [ c1 c2 ... ck ] [ x_{n-1} ]
[ x_{n-1}   ]   [ 1  0  ... 0  ] [ x_{n-2} ]
[ ...       ] = [ 0  1  ... 0  ] [ ...     ]
[ x_{n-k+1} ]   [ 0  0  ... 1 0] [ x_{n-k} ]
```

Baris pertama koefisien, di bawah pergeseran. Analoginya: state adalah jendela `k` nilai terakhir.

**Kapan:** trib, rec `k ≤ 100`, `n ≤ 1e18`. Jangan DP `O(n)` untuk `n = 1e18`.

**Proses:** trib `T_n = T_{n-1}+T_{n-2}+T_{n-3}`, init `T_0=0, T_1=1, T_2=1`.

```
n: 0 1 2 3 4 5 6 7
T: 0 1 1 2 4 7 13 24
```

Matriks:

```
[1 1 1]
[1 0 0]
[0 1 0]
```

`M [T2, T1, T0]^T = [1+1+0, 1, 1]^T = [2, 1, 1] = [T3, T2, T1]`.

`M^2 [1,1,0] = M[2,1,1] = [4,2,1] = [T4, T3, T2]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    int k = (int)c.size();
    if (n < k) return init[n] % MOD;
    mat M(k, vector<ll>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = c[j] % MOD;
    for (int i = 1; i < k; i++) M[i][i - 1] = 1;
    mat P = mpow(M, n - (k - 1));
    ll ans = 0;
    for (int j = 0; j < k; j++) {
        ll x = init[k - 1 - j] % MOD;
        ans = (ans + P[0][j] * x) % MOD;
    }
    return ans;
}

int main() {
    FASTIO;
    vector<ll> c = {1, 1, 1}, init = {0, 1, 1};
    for (int n = 0; n <= 7; n++) cout << linear_rec(c, init, n) << ' ';
    cout << '\n'; // 0 1 1 2 4 7 13 24
    return 0;
}
```

**Jebakan:** indexing `n` 0-based vs “suku ke-n”; urutan `init` terbalik vs baris matriks; `n < k`; koefisien negatif + modulus.

**Kompleksitas:** `O(k^3 log n)`.

---

## Jumlah jalur dan akumulator

**Teori:** pada graf berarah `k` simpul, `(A^e)_{ij}` = jumlah jalur panjang `e` dari `i` ke `j` (bobot 1, atau bobot tepi jika `A` berisi bobot). Untuk jumlah prefiks barisan, perbesar state: `[s_n, x_n, x_{n-1}, …]` dengan `s_n = s_{n-1} + x_n`. Analoginya: matriks menyimpan “berapa cara tiba” dan “jumlah sampai sekarang”.

**Kapan:** tiling, jalur grid kecil sebagai graf, `Σ_{i=1}^n F_i`. Jangan Floyd `O(n^3)` untuk “panjang tepat `e`”.

**Proses:** graf 2 simpul, tepi `0→0`, `0→1`, `1→0`.

```
A = [1 1]
    [1 0]
```

Ini lagi Fibonacci: jalur panjang `n` dari 0 ke 0 = `F_{n+1}`.

Jumlah `F_1+…+F_n`: diketahui `F_{n+2}−1`. Atau matriks 3×3:

```
s' = s + F_next
F_next = F + Fold
Fold' = F
```

Susun sesuai indexing yang kamu pilih, uji `n = 6`: jumlah `1+1+2+3+5+8=20`, `F_8−1=21−1=20`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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

ll fib(ll n) {
    if (n == 0) return 0;
    return mpow({{1, 1}, {1, 0}}, n - 1)[0][0];
}

ll fib_sum(ll n) {
    if (n <= 0) return 0;
    return (fib(n + 2) - 1 + MOD) % MOD;
}

int main() {
    FASTIO;
    cout << fib_sum(6) << '\n'; // 20
    cout << fib_sum(1) << '\n'; // 1
    return 0;
}
```

**Jebakan:** jalur **tepat** `e` vs **paling banyak** `e` (jumlah `I + A + … + A^e` butuh trik blok atau kali `(A^{e+1}−I)(A−I)^{-1}` jika invertibel); simpul 0-based.

**Kompleksitas:** sama expo `O(k^3 log e)`.

---

## Basis XOR: sisip

**Teori:** himpunan angka dengan operasi XOR adalah ruang vektor atas `GF(2)`. Basis: kumpulan independen yang menghasilkan semua XOR subset. Gaussian: dari bit tinggi, tiap bit punya paling banyak satu perwakilan. Insert `x`: dari bit 63 ke 0, jika bit hidup dan basis ada, `x ^= b[i]`; jika slot kosong, taruh `x`. Return true jika `x` independen (rank naik). Rank `r` → `2^r` nilai XOR berbeda. Analoginya: eliminasi Gauss pada baris biner.

**Kapan:** XOR subset maksimum / ke-k, “bisa membentuk X?”, sisip online. `n ≤ 1e5`, nilai `≤ 1e18`. Jangan enumerasi `2^n`.

**Proses:** sisip `5, 3, 7`.

```
5 = 101  bit2 kosong → b[2] = 101
3 = 011  bit1 kosong → b[1] = 011
7 = 111  bit2: 111 ^ 101 = 010
         bit1: 010 ^ 011 = 001
         bit0 kosong → b[0] = 001
```

Basis `{5, 3, 1}`, rank 3, ruang 8 nilai (semua 0..7).

Sisip `4 = 100`: `100 ^ b[2] = 001`, `001 ^ b[0] = 0` → dependen, rank tetap.

Sisip `8 = 1000`: bit3 kosong → rank 4.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
        return false;
    }
};

int main() {
    FASTIO;
    XorBasis xb;
    cout << xb.insert(5) << xb.insert(3) << xb.insert(7) << '\n'; // 1 1 1
    cout << xb.rank << '\n'; // 3
    cout << xb.insert(4) << '\n'; // 0
    cout << xb.insert(8) << '\n'; // 1
    cout << xb.rank << '\n'; // 4
    return 0;
}
```

**Jebakan:** loop bit 31 untuk `ll`; `insert` tidak mereduksi `x` sebelum cek slot; mengira rank selalu 64.

**Kompleksitas:** insert `O(64)` sampai `O(64^2)`, `n` sisip `O(64 n)`.

---

## Max XOR dan bisa membentuk

**Teori:** XOR maksimum: dari bit tinggi, jika `ans ^ b[i]` lebih besar, ambil. Karena basis sudah “menguasai” bit itu, greedy benar di `GF(2)` dengan urutan MSB. `bisa(x)`: reduksi sama seperti insert tanpa menulis slot; sisa 0 artinya `x` kombinasi linear. Analoginya: nyalakan bit tinggi dulu seperti koin canonical.

**Kapan:** subset XOR max, cek keanggotaan ruang. Query setelah banyak sisip.

**Proses:** basis `{5, 3, 1}` dari sebelumnya.

```
ans=0
bit2: 0^5=5 > 0 → 5
bit1: 5^3=6 > 5 → 6
bit0: 6^1=7 > 6 → 7
max = 7
```

`bisa(4)`: `4 ^ 5 = 1`, `1 ^ 1 = 0` → ya. `bisa(8)` tanpa `b[3]` → sisa 8 ≠ 0 → tidak.

Subset mentah: `5^3=6`, `7=7`, `5^3^7=1`, `5^7=2`, `3^7=4`. Maks 7.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
        return false;
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
};

int main() {
    FASTIO;
    XorBasis xb;
    xb.insert(5);
    xb.insert(3);
    xb.insert(7);
    cout << xb.max_xor() << '\n';                 // 7
    cout << xb.bisa(4) << ' ' << xb.bisa(8) << '\n'; // 1 0
    return 0;
}
```

**Jebakan:** `max` memakai `min` salah arah; `bisa` menulis ke `b`; `x` negatif (geser bit implementasi-defined pada `ll` — pakai `unsigned long long` jika perlu).

**Kompleksitas:** `O(64)` per query.

---

## Normalisasi dan XOR ke-k

**Teori:** setelah Gauss, bersihkan bit: untuk tiap `b[i] ≠ 0`, XOR-kan ke `b[j]` lain yang masih punya bit `i`. Tiap basis vektor jadi unik di bit pivotnya. XOR ke-`k` terkecil (0 = kosong): pakai bit `k` dari rendah pada daftar pivot terurut. Tanpa normalisasi, “bit `k` pada urutan insert” **bukan** urutan terurut. Analoginya: bentuk eselon tereduksi.

**Kapan:** “XOR subset ke-k terkecil”, enumerasi terurut. Jangan pakai `kth` mentah jika soal ingin sorted.

**Proses:** basis setelah sisip `5,3,7`: `b[2]=5=101`, `b[1]=3=011`, `b[0]=1=001`.

Normalisasi:

```
b[2] punya bit1? 101 ya → 101^011=110 = 6, sekarang b[2]=6
b[2] punya bit0? 110 tidak
b[1]=011 punya bit0? ya → 011^001=010 = 2
b[0]=1
```

Pivot: bit2: 6 (`110`), bit1: 2 (`010`), bit0: 1 (`001`). Ruang tetap.

Ke-k (0-based, `k < 8`):

```
k=0: 0
k=1: 1
k=2: 2
k=3: 2^1=3
k=4: 6
k=5: 6^1=7
k=6: 6^2=4
k=7: 6^2^1=5
```

Urutan nilai: 0,1,2,3,6,7,4,5 — **bukan** sorted numerik. Untuk sorted, Gaussian tambahan dari bit rendah atau generate `2^r` jika `r` kecil. Banyak soal hanya butuh ke-k pada urutan pivot (cek pernyataan). Versi sorted: kumpulkan semua, sort, hanya jika `r ≤ 20`.

Untuk ke-k terkecil numerik: setelah RREF, interpret bit `k` dari pivot rendah ke tinggi menghasilkan urutan **gray-ish** yang tidak monoton. Cara aman `r ≤ 20`: enumerate. Cara `r ≤ 63` sorted: lebih rumit (DP bit); sebutkan di jebakan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
        return false;
    }
    void normalisasi() {
        for (int i = 63; i >= 0; i--)
            if (b[i])
                for (int j = 63; j >= 0; j--)
                    if (i != j && ((b[j] >> i) & 1))
                        b[j] ^= b[i];
    }
    ll kth_pivot(ll k) const {
        ll ans = 0;
        int idx = 0;
        for (int i = 0; i < 64; i++)
            if (b[i]) {
                if ((k >> idx) & 1) ans ^= b[i];
                idx++;
            }
        return ans;
    }
};

int main() {
    FASTIO;
    XorBasis xb;
    xb.insert(5);
    xb.insert(3);
    xb.insert(7);
    xb.normalisasi();
    for (ll k = 0; k < 8; k++) cout << xb.kth_pivot(k) << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** mengira keluaran `kth_pivot` terurut naik; `k ≥ 2^rank`; `k` 1-based vs 0 = kosong; normalisasi mengubah `b[i]` sehingga `max_xor` tetap benar tetapi jejak insert hilang.

**Kompleksitas:** normalisasi `O(64^2)`, `kth` `O(64)`.

---

## Peta keputusan

```
F_n / rekurens k, n=1e18     → matrix expo
jumlah jalur panjang e       → adj^e
Σ x_i                        → perbesar state / identitas tertutup
XOR subset max / ada / sisip → basis 64-bit
XOR ke-k terurut             → RREF + hati-hati, atau enumerate r≤20
2^n brute                    → jangan jika n>28
```

| ukuran | alat | waktu |
|---|---|---|
| `k ≤ 2` Fibonacci | `A^n` 2×2 | `O(log n)` |
| `k ≤ 100` rec | companion | `O(k^3 log n)` |
| `n` angka 64-bit | XOR basis | `O(64 n)` |
| `n ≤ 20` XOR | brute mask | `O(2^n)` |

---

## Ringkasan

1. Kali matriks = produk titik; expo = kuadrat berulang; `e = 0` → `I`.
2. Fibonacci dan trib adalah companion kecil; uji `n < k` dulu.
3. Jalur panjang `e` = `A^e`; jumlah barisan sering identitas plus satu state.
4. XOR basis: Gauss MSB, rank `r` ⇒ `2^r` nilai.
5. Max XOR greedy dari bit tinggi; `bisa` = reduksi ke 0.
6. `kth` tanpa RREF bukan urutan numerik.

Konvolusi cepat: [fft.md](fft.md).
