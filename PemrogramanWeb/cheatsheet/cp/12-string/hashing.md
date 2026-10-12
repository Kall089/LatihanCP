# Polynomial hashing

[← String](README.md) · [KMP →](kmp.md) · [Anti-hash](../16-teknik-kontes/random-antihash.md)

Day 211. Potongan string jadi angka. Banding O(1) setelah prahitung O(n).

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Indeks string **0-based**. Jangan bandingkan `double` untuk hash. Anti-hash lengkap di folder teknik kontes.

## Daftar isi

- [Rumus polinom](#rumus-polinom)
- [Prefix hash](#prefix-hash)
- [Samakan pangkat](#samakan-pangkat)
- [Double hash](#double-hash)
- [Overflow 2^64](#overflow-264)
- [Rabin-Karp](#rabin-karp)
- [Palindrom dua arah](#palindrom-dua-arah)
- [LCP biner](#lcp-biner)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Rumus polinom

**Teori:** tiap posisi punya bobot pangkat basis P.

```
hash(s) = s[0]·P^0 + s[1]·P^1 + ... + s[n-1]·P^{n-1}   (mod M)
```

Urutan huruf masuk rumus, jadi `"ab"` ≠ `"ba"`. Jika hanya jumlah kode, anagram selalu tabrakan.

M biasanya prima 10^9+7 atau 10^9+9, atau 2^64 lewat overflow `unsigned long long`.

Analogi: nomor punggung. Beda → pemain beda. Sama → hampir pasti sama, kecuali tabrakan.

`c+1` menghindari huruf bernilai 0 yang menghapus bobot.

**Kapan:**

- Pakai: banyak potongan sama?, substring berbeda kasar, binary search + hash.
- Jangan: bukti mutlak tanpa double / modulus acak di CF.
- Jangan: `P <= ukuran alfabet` (P=10 untuk huruf). Tabrakan sistematis.

**Proses:** s=`"abc"`, P=31, M besar, a=1,b=2,c=3.

```
1·1 + 2·31 + 3·961 = 1+62+2883 = 2946
"cba" = 3 + 2·31 + 1·961 = 1026
berbeda
```

**Kode:**

```cpp
const ll MODH = 1000000009LL;
const ll PBASE = 911382323LL;               // > 128

ll hashPolinom(const string& s, ll P = PBASE, ll M = MODH) {
    ll h = 0, pk = 1;
    for (unsigned char c : s) {
        h = (h + (ll)(c + 1) * pk % M) % M;
        pk = pk * P % M;
    }
    return h;
}
```

**Jebakan:** overflow `ll` sebelum `%`. Kalikan bertahap. `P=31` ketat untuk ASCII campur. Modulus 10^9+7 sangat populer — hacker punya tes; lihat [random-antihash.md](../16-teknik-kontes/random-antihash.md).

**Kompleksitas:** O(n) per string.

## Prefix hash

**Teori:** `h[i] = hash(s[0..i-1])`. Potongan `s[l..r]` inklusif:

```
raw = h[r+1] − h[l]     masih berbobot P^l, P^{l+1}, ...
```

Precompute `pw[i] = P^i`.

**Kapan:** q sampai 10^6 banding potongan.

**Proses:** s=`"abac"`, P=3, a=1,b=2,c=3.

```
h[0]=0
h[1]=1
h[2]=1+2·3=7
h[3]=7+1·9=16
h[4]=16+3·27=97

s[0..1]="ab" raw=7     bobot P^0,P^1
s[2..3]="ac" raw=80    bobot P^2,P^3
```

**Kode:**

```cpp
struct Hasher {
    ll P, M;
    vector<ll> h, pw;

    Hasher(const string& s, ll P_ = PBASE, ll M_ = MODH) : P(P_), M(M_) {
        int n = (int)s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * P % M;
            h[i + 1] = (h[i] + (ll)((unsigned char)s[i] + 1) * pw[i]) % M;
        }
    }

    ll raw(int l, int r) const {            // inklusif, berbobot P^l
        ll x = h[r + 1] - h[l];
        if (x < 0) x += M;
        return x;
    }
};
```

**Jebakan:** `h[r+1]-h[l]` negatif tanpa `+M`. `r < l` jangan dipanggil.

**Kompleksitas:** build O(n), raw O(1).

## Samakan pangkat

**Teori:** dua potongan sama panjang dibanding setelah dikalikan pangkat lawan:

```
raw(a,b) * P^c  ?==  raw(c,d) * P^a    (mod M)
```

Ini menghindari invers modular. Cek panjang dulu.

**Kapan:** semua `sama`. Beda panjang → false.

**Proses:** lanjut `"abac"`.

```
7 * P^2 = 7*9 = 63
80 * P^0 = 80
63 ≠ 80 → "ab" ≠ "ac"
```

`"aba"` di `"abacaba"`: posisi 0 dan 4 harus sama.

**Kode:**

```cpp
    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        ll x = raw(a, b) * pw[c] % M;
        ll y = raw(c, d) * pw[a] % M;
        return x == y;
    }
```

Kalikan dalam `__int128` jika P dan M dekat 2·10^9:

```cpp
ll mul(ll a, ll b, ll M) { return (ll)((__int128)a * b % M); }
```

**Jebakan:** membandingkan `raw` tanpa samakan pangkat. `pw[c]` vs `pw[a]` tertukar.

**Kompleksitas:** O(1).

## Double hash

**Teori:** dua pasangan (P, M) independen. Sama hanya jika keduanya setuju. Peluang tabrakan ≈ 1/(M1 M2).

**Kapan:** CF Div. 1 / hackable. AtCoder juga rapi.

**Proses:** satu modulus tabrakan, kedua hampir tidak pada tes acak.

**Kode:**

```cpp
struct DoubleHash {
    Hasher a, b;
    DoubleHash(const string& s)
        : a(s, 911382323, 1000000007),
          b(s, 972663749, 1000000009) {}

    bool sama(int i1, int j1, int i2, int j2) const {
        return a.sama(i1, j1, i2, j2) && b.sama(i1, j1, i2, j2);
    }
};
```

**Jebakan:** dua hasher P,M **sama**. Menganggap “mustahil” tabrakan.

**Kompleksitas:** 2× memori dan waktu.

## Overflow 2^64

**Teori:** `unsigned long long` overflow natural mod 2^64. Cepat, tanpa `%`. Bukan prima. Ada konstruksi anti-hash Thue–Morse. Di CF campur 2^64 + satu modulus acak.

**Kapan:** lokal / AtCoder, atau sebagai hash ketiga.

**Proses:** sama rumus, tanpa mod.

**Kode:**

```cpp
struct Hash64 {
    vector<unsigned long long> h, pw;
    static const unsigned long long P = 2464354610519ULL;

    explicit Hash64(const string& s) {
        int n = (int)s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * P;
            h[i + 1] = h[i] + (unsigned long long)((unsigned char)s[i] + 1) * pw[i];
        }
    }

    unsigned long long raw(int l, int r) const { return h[r + 1] - h[l]; }

    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        return raw(a, b) * pw[c] == raw(c, d) * pw[a];
    }
};
```

**Jebakan:** `ll` signed overflow UB. Wajib `unsigned long long`. 2^64 saja di CF Div. 1 berisiko.

**Kompleksitas:** O(n) / O(1).

## Rabin-Karp

**Teori:** geser jendela |pola|. Dengan prefix hash: banding `teks[i..i+m-1]` vs `pola[0..m-1]`.

**Kapan:** cari pola. Satu pola + jaminan tanpa tabrakan → [KMP](kmp.md).

**Proses:** teks `abacaba`, pola `aba`.

```
i=0 aba  sama → 0
i=1 bac  beda
i=2 aca  beda
i=3 cab  beda
i=4 aba  sama → 4
```

**Kode:**

```cpp
vector<int> rabinKarp(const string& teks, const string& pola) {
    vector<int> pos;
    int n = (int)teks.size(), m = (int)pola.size();
    if (m == 0 || m > n) return pos;
    Hasher ht(teks), hp(pola);
    for (int i = 0; i + m <= n; i++)
        if (ht.sama(i, i + m - 1, 0, m - 1) && hp.sama(0, m - 1, 0, m - 1)
            && ht.raw(i, i + m - 1) * hp.pw[0] % ht.M
               == hp.raw(0, m - 1) * ht.pw[i] % ht.M)
            pos.push_back(i);
    return pos;
}
```

Lebih bersih: satu Hasher pada `pola + char(1) + teks` tidak wajib. Samakan dua hasher dengan P,M **identik**:

```cpp
vector<int> cariHash(const string& teks, const string& pola) {
    vector<int> pos;
    int n = (int)teks.size(), m = (int)pola.size();
    if (m == 0 || m > n) return pos;
    Hasher ht(teks), hp(pola);              // P,M default sama
    for (int i = 0; i + m <= n; i++) {
        ll x = ht.raw(i, i + m - 1) * hp.pw[0] % ht.M;
        ll y = hp.raw(0, m - 1) * ht.pw[i] % ht.M;
        if (x == y) pos.push_back(i);
    }
    return pos;
}
```

**Jebakan:** `i+m-1 >= n`. False positive single hash. Verifikasi string jika jumlah match kecil.

**Kompleksitas:** O(n+m) expected.

## Palindrom dua arah

**Teori:** bangun hasher pada s dan reverse(s). `s[l..r]` palindrom iff sama dengan cermin `rev[n-1-r .. n-1-l]`.

**Kapan:** banyak pertanyaan `[l,r]` palindrom. Semua radius → [Manacher](z-manacher.md).

**Proses:** s=`"abba"`, n=4.

```
rev = "abba"
[0,3] vs rev[0,3] sama
[0,2]="abb" vs rev[1,3]="bba" beda
```

**Kode:**

```cpp
bool palindrom(const Hasher& fw, const Hasher& bw, int n, int l, int r) {
    if (l > r) return true;
    int a = n - 1 - r, b = n - 1 - l;
    return fw.raw(l, r) * bw.pw[a] % fw.M == bw.raw(a, b) * fw.pw[l] % fw.M;
}

struct PalHash {
    int n;
    Hasher fw, bw;
    explicit PalHash(string s) : n((int)s.size()), fw(s), bw("") {
        string r = s;
        reverse(r.begin(), r.end());
        bw = Hasher(r);
    }
    bool pal(int l, int r) const { return palindrom(fw, bw, n, l, r); }
};
```

`Hasher` butuh constructor assignable — default copy OK karena vector.

Jika `bw("")` merepotkan:

```cpp
Hasher buatReverse(string s) {
    reverse(s.begin(), s.end());
    return Hasher(s);
}
```

**Jebakan:** indeks cermin `n-1-r` tertukar. P,M fw dan bw harus sama.

**Kompleksitas:** O(1) per cek.

## LCP biner

**Teori:** LCP dua sufiks: binary search panjang, cek hash. O(log n) per pasangan.

**Kapan:** tanpa Suffix Array. Distinct substring kasar dengan set hash (tabrakan).

**Proses:** s=`"aabaab"`, i=0 j=3. `"aab"` vs `"aab"` LCP=3.

```
mid=3 sama → lo=3
mid lebih besar tidak ada
```

**Kode:**

```cpp
int lcpHash(const Hasher& h, int i, int j, int n) {
    int lo = 0, hi = n - max(i, j);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (h.sama(i, i + mid - 1, j, j + mid - 1)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
```

**Jebakan:** `mid=0` jangan `sama` dengan r < l. `hi` awal `n-max(i,j)` bukan n.

**Kompleksitas:** O(log n) kali hash.

## Uji naif

**Teori:** banding `s.substr` vs `sama`. Cari pola vs loop.

**Kapan:** setelah tulis `raw`.

**Proses:** `"abacaba"` / `"aba"` posisi 0,4.

**Kode:**

```cpp
int main() {
    FASTIO;
    string t = "abacaba", p = "aba";
    Hasher ht(t), hp(p);
    assert(ht.sama(0, 2, 4, 6));
    assert(!ht.sama(0, 2, 1, 3));
    auto pos = cariHash(t, p);
    assert((pos == vector<int>{0, 4}));
    PalHash ph("abba");
    assert(ph.pal(0, 3));
    assert(!ph.pal(0, 2));
    cout << "ok\n";
}
```

Stress kecil:

```cpp
bool cekHash(const string& s) {
    Hasher h(s);
    int n = (int)s.size();
    for (int l = 0; l < n; l++)
        for (int r = l; r < n; r++)
            for (int i = 0; i + (r - l) < n; i++) {
                bool a = h.sama(l, r, i, i + (r - l));
                bool b = s.compare(l, r - l + 1, s, i, r - l + 1) == 0;
                if (a != b) return false;
            }
    return true;
}
```

Single hash bisa `a!=b` sangat jarang. Double lebih aman untuk assert.

**Jebakan:** `substr` di loop n³ pada tes besar. n ≤ 20.

**Kompleksitas:** tes O(n³).

## Ringkasan

1. Hash polinom membedakan posisi. P > alfabet, `c+1`.
2. Prefix + samakan pangkat = banding O(1).
3. Double atau P/M acak di CF. Jangan 10^9+7 tunggal.
4. 2^64 cepat, bukan bukti.
5. Palindrom: hasher terbalik. LCP: binsearch.
6. Satu pola pasti: KMP/Z.

Latihan Day 211. Jangan salin `exercise_*.cpp`.
