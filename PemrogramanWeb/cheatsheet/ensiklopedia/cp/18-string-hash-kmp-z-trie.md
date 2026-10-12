# 18 — Hashing, KMP, Z, Manacher, Trie, Suffix Array

[← 17 pohon](17-pohon-lca-hld-centroid.md) · [README](README.md) · [Lanjut 19 →](19-geo-nim-stress-random.md)

Folder 12 di `DAFTAR-MATERI`: string. Pertanyaan paling sering: “apakah dua potongan sama?”, “di mana pola muncul?”, “berapa palindrom?”, “XOR terbesar”, “urutkan semua sufiks”.

Latihan harian: `ComProgLearning/CP` Day 211 (hash), 213 (KMP), 215 (Z & Manacher), 217 (Trie), 219 (Suffix Array). Anti-hash dan random ada di file 19.

Indeks string **0-based**. `typedef long long ll`. Jangan bandingkan `double` untuk hash.

## Daftar isi

- [Peta alat string](#peta-alat-string)
- [Polynomial hashing](#polynomial-hashing)
- [Prefix hash dan potongan O(1)](#prefix-hash-dan-potongan-o1)
- [Rabin-Karp](#rabin-karp)
- [Hash palindrom dan LCP biner](#hash-palindrom-dan-lcp-biner)
- [KMP dan prefix function](#kmp-dan-prefix-function)
- [Border, periode, KMP search](#border-periode-kmp-search)
- [Z-function](#z-function)
- [Manacher — ide](#manacher--ide)
- [Trie](#trie)
- [Binary Trie XOR](#binary-trie-xor)
- [Suffix Array — ide](#suffix-array--ide)
- [Aho-Corasick dan SAM — peta](#aho-corasick-dan-sam--peta)
- [Tabel pilih alat string](#tabel-pilih-alat-string)
- [Ringkasan](#ringkasan)

## Peta alat string

**Teori:** membandingkan dua substring naif O(panjang). n,q = 10⁵ membuat 10¹⁰ perbandingan. Semua alat di file ini menukar huruf menjadi **angka, tabel, atau pohon** supaya perbandingan atau pencarian jadi linear atau logaritmik.

| Alat | Yang diingat | Query khas |
| --- | --- | --- |
| Hash | satu/dua angka per prefix | sama / tidak, O(1) |
| KMP | `pi[i]` border | cari pola, periode |
| Z | LCP dengan awal string | cari pola, border |
| Manacher | radius palindrom | palindrom terpanjang |
| Trie | pohon awalan | kamus, prefix |
| Binary Trie | bit MSB→LSB | XOR max/min |
| SA + LCP | sufiks terurut | distinct substring, LCS |

**Kapan dipakai / kapan tidak.** Hash cepat ditulis, ada risiko tabrakan — lawan anti-hash di file 19. KMP/Z pasti benar, sedikit lebih kaku. Trie memakai memori. SA lebih berat di implementasi.

**Jebakan:** memakai `std::string::substr` di dalam loop n². Membandingkan hash 32-bit tunggal di Codeforces Div. 1.

**Kompleksitas:** target kontes hampir selalu O(n) atau O(n log n).

## Polynomial hashing

**Teori:** beri setiap posisi bobot pangkat basis `P`.

```
hash(s) = s[0]·P^0 + s[1]·P^1 + ... + s[n-1]·P^{n-1}   (mod M)
```

Urutan huruf masuk ke rumus, jadi `"ab"` ≠ `"ba"`. `M` biasanya prima 10⁹+7 atau 10⁹+9, atau 2⁶⁴ lewat overflow `unsigned long long` (bukan prima, tapi cepat).

Analogi: nomor punggung. Nomor beda → pemain pasti beda. Nomor sama → hampir pasti pemain sama, kecuali tabrakan.

Kenapa polynomial: jika hanya jumlah kode huruf, anagram tabrakan selalu. Pangkat membedakan posisi.

**Kapan dipakai / kapan tidak.**

- Pakai: bandingkan banyak potongan, hitung substring berbeda, binary search + hash.
- Jangan: bukti matematis mutlak tanpa double hash / modulus acak (soal anti-hash).
- Jangan: `P <= ukuran alfabet` (misalnya P=10 untuk huruf). Tabrakan sistematis.

**Proses:** `s = "abc"`, `P=31`, `M=10^9+9`, `a=1,b=2,c=3`.

```
1·1 + 2·31 + 3·961 = 1+62+2883 = 2946
hash("abc") = 2946
hash("cba") = 3 + 2·31 + 1·961 = 3+62+961 = 1026   berbeda
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MODH = 1000000009LL;
const ll PBASE = 911382323LL;               // > 128, acak-ish tetap

ll hashPolinom(const string& s, ll P = PBASE, ll M = MODH) {
    ll h = 0, pk = 1;
    for (unsigned char c : s) {
        h = (h + (ll)(c + 1) * pk) % M;
        pk = pk * P % M;
    }
    return h;
}
```

`c+1` menghindari huruf bernilai 0 yang menghapus bobot.

**Jebakan:** overflow `ll` saat `h + code * pk` sebelum `%`. Kalikan dalam `__int128` atau modulus bertahap. `P=31` untuk string ASCII campur angka kadang ketat; 911382323 lebih aman. Modulus 10⁹+7 **sangat** populer — hacker punya test anti-hash; lihat file 19.

**Kompleksitas:** O(n) per string. Satu angka, memori O(1).

## Prefix hash dan potongan O(1)

**Teori:** `h[i] = hash(s[0..i-1])`. Potongan `s[l..r]` (inklusif) punya hash

```
raw = h[r+1] − h[l]     (masih berbobot P^l, P^{l+1}, ...)
```

Agar dua potongan bisa dibanding, samakan pangkat:

```
hash(s[a..b]) * P^c  ?==  hash(s[c..d]) * P^a     (mod M)
```

atau kalikan `raw` dengan invers `P^l` supaya selalu mulai P^0. Cara pertama menghindari invers.

Precompute `pw[i] = P^i`.

**Kapan dipakai / kapan tidak.**

- Pakai: q sampai 10⁶ bandingkan potongan sama panjang.
- Jangan: potongan beda panjang dianggap sama hanya karena hash sama — cek panjang dulu.

**Proses:** `s = "abac"`, P=3, M besar, `a=1,b=2,c=3`.

```
h[0]=0
h[1]=1
h[2]=1 + 2·3 = 7
h[3]=7 + 1·9 = 16
h[4]=16 + 3·27 = 97

s[0..1]="ab" raw = h[2]-h[0]=7        bobot P^0,P^1
s[2..3]="ac" raw = h[4]-h[2]=80       bobot P^2,P^3
samakan: 7 * P^2 = 7*9=63
         80 * P^0 = 80
63 ≠ 80 → berbeda. Benar.
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

    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        ll x = raw(a, b) * pw[c] % M;
        ll y = raw(c, d) * pw[a] % M;
        return x == y;
    }
};
```

Double hash: dua `(P, M)` independen. Sama hanya jika kedua pasangan setuju. Peluang tabrakan ≈ 1/M₁M₂.

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

Overflow 2⁶⁴:

```cpp
struct Hash64 {
    vector<unsigned long long> h, pw;
    static const unsigned long long P = 2464354610519ULL;

    Hash64(const string& s) {
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

2⁶⁴ bukan prima. Ada konstruksi anti-hash Thue–Morse. Di CF, campur 2⁶⁴ + satu modulus acak, atau dua modulus.

**Jebakan:**

- `h[r+1]-h[l]` negatif lalu dipakai tanpa `+M`.
- Membandingkan `raw` tanpa menyamakan pangkat.
- `P^n` overflow sebelum modulo jika bukan `ull`.
- Menganggap double hash “mustahil tabrakan” — masih mungkin, hanya sangat jarang.

**Kompleksitas:** build O(n), banding O(1), memori O(n).

## Rabin-Karp

**Teori:** geser jendela sepanjang |pola| di teks. Hash jendela berikutnya = “buang huruf kiri, tambah huruf kanan” O(1). Jika hash sama, (opsional) cek huruf demi huruf.

```
baru = (lama − s[i]·P^0) / P  + s[i+m]·P^{m-1}
```

Dengan prefix hash, lebih mudah: bandingkan `teks[i..i+m-1]` dengan `pola[0..m-1]` lewat `sama`.

**Kapan dipakai / kapan tidak.**

- Pakai: cari pola, banyak pola pendek, “anagram jendela” (hash berbeda: frekuensi).
- KMP lebih bersih jika satu pola dan kamu ingin jaminan tanpa tabrakan.

**Proses:** teks `abacaba`, pola `aba`.

```
i=0 aba  hash sama → ketemu
i=1 bac  beda
i=2 aca  beda
i=3 cab  beda
i=4 aba  sama → ketemu
posisi 0 dan 4
```

**Kode:**

```cpp
vector<int> rabinKarp(const string& teks, const string& pola) {
    vector<int> pos;
    int n = (int)teks.size(), m = (int)pola.size();
    if (m == 0 || m > n) return pos;
    Hasher ht(teks), hp(pola);
    for (int i = 0; i + m <= n; i++) {
        ll x = ht.raw(i, i + m - 1) * hp.pw[0] % ht.M;
        ll y = hp.raw(0, m - 1) * ht.pw[i] % ht.M;
        if (x == y) pos.push_back(i);
    }
    return pos;
}
```

**Jebakan:** jendela menabrak akhir (`i+m-1 >= n`). False positive jika single hash; di soal hack, verifikasi string atau double hash.

**Kompleksitas:** O(n+m) expected jika hash O(1) dan jarang verifikasi penuh.

## Hash palindrom dan LCP biner

**Teori:** palindrom = string = kebalikannya. Bangun hasher pada `s` dan pada `reverse(s)`. `s[l..r]` palindrom jika sama dengan potongan cermin di string terbalik.

Indeks terbalik: karakter `s[i]` duduk di `rev[n-1-i]`. Potongan `s[l..r]` cerminnya `rev[n-1-r .. n-1-l]`.

LCP dua sufiks: binary search panjang, cek hash potongan. O(log n) per pasangan.

**Kapan dipakai / kapan tidak.**

- Pakai: banyak pertanyaan “apakah [l,r] palindrom”, distinct palindrom kasar, LCP tanpa SA.
- Manacher lebih tepat untuk **semua** radius palindrom dalam O(n).

**Proses:** `s = "abba"`, n=4. Cek `[0,3]`.

```
rev = "abba" juga
s[0..3] vs rev[0..3] sama → palindrom
[1,2] = "bb" vs rev[1,2]="bb" sama
[0,2]="abb" vs rev[1,3]="bba" beda
```

**Kode:**

```cpp
struct PalHash {
    int n;
    Hasher fw, bw;

    PalHash(string s) : n((int)s.size()), fw(s) {
        string r = s;
        reverse(r.begin(), r.end());
        bw = Hasher(r);
    }

    bool pal(int l, int r) const {
        if (l > r) return true;
        int a = n - 1 - r, b = n - 1 - l;
        return fw.sama(l, r, l, r) && fw.raw(l, r) * bw.pw[a] % fw.M
               == bw.raw(a, b) * fw.pw[l] % fw.M;
    }
};

// perbaikan: bandingkan fw[l..r] dengan bw[a..b]
bool palindrom(const Hasher& fw, const Hasher& bw, int n, int l, int r) {
    int a = n - 1 - r, b = n - 1 - l;
    return fw.sama(l, r, l, r) &&
           (fw.raw(l, r) * bw.pw[a] % fw.M == bw.raw(a, b) * fw.pw[l] % fw.M);
}

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

Fungsi `PalHash::pal` di atas agak berlebih; pakai `palindrom(fw,bw,n,l,r)`.

**Jebakan:** indeks cermin `n-1-r` tertukar. Binary search LCP: `mid=0` jangan panggil `sama` dengan r < l.

**Kompleksitas:** palindrom O(1), LCP O(log n) kali hash.

## KMP dan prefix function

**Teori:** `pi[i]` = panjang **prefiks terpanjang** dari `s[0..i]` yang juga **sufiks** dari `s[0..i]`, tetapi bukan seluruh `s[0..i]`. Itu disebut **border**.

Saat mencocokkan pola ke teks, kalau gagal di posisi `j`, jangan mundurkan jari di teks. Turunkan `j` menjadi `pi[j-1]`: sisa huruf itu masih cocok sebagai awalan.

Kenapa O(n): setiap kali `j` naik (cocok), suatu saat turun. `j` tidak negatif, total kenaikan ≤ n, jadi total penurunan ≤ n.

Analogi: mencari kata di buku. Kamu sudah mengeja `abab`, huruf berikutnya salah. Kamu sadar dua huruf terakhir `ab` = awal kata. Tidak perlu mengulang dari huruf pertama buku.

**Kapan dipakai / kapan tidak.**

- Pakai: cari pola, periode string, banyak kemunculan prefiks, string compression.
- Z-function sering lebih mudah dibayangkan untuk “LCP dengan awal”.
- Hash lebih pendek untuk “apakah sama”, bukan untuk periode ketat.

**Proses:** `s = "ababc"`.

```
i=0 "a"     pi=0
i=1 "ab"    a≠b           pi=0
i=2 "aba"   sufiks "a" = prefiks "a"         pi=1
i=3 "abab"  sufiks "ab" = prefiks "ab"       pi=2
i=4 "ababc" c ≠ a (lanjut dari j=2, lalu j=0) pi=0
pi = [0,0,1,2,0]
```

Simulasi mesin `j`:

```
i=2: s[2]='a' == s[0], j: 0→1
i=3: s[3]='b' == s[1], j: 1→2
i=4: s[4]='c' != s[2]='a', j=pi[1]=0, s[4]!=s[0], j=0
```

**Kode:**

```cpp
vector<int> prefixFunction(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
```

**Jebakan:** `pi[0]` harus 0. Menulis `j = pi[i]` saat `i` belum diisi. Loop `while` tanpa `j>0` akses `pi[-1]`. Mengira `pi[i]=i` legal — itu seluruh string, dilarang definisi.

**Kompleksitas:** O(n) waktu dan memori.

## Border, periode, KMP search

**Teori:** rantai `i, pi[i-1], pi[pi[i-1]-1], ...` adalah semua border. Periode terkecil kandidat `p = n - pi[n-1]`. Jika `n % p == 0`, maka `p` periode sejati (string = `s[0..p-1]` diulang).

Cari pola: bangun `pi` pada `pola + SEP + teks`. Setiap `pi[i] == |pola|` di bagian teks adalah kemunculan. `SEP` karakter yang **tidak muncul** di input (`'\1'`, bukan `'#'` jika `#` bisa ada).

Tanpa gabung: jalankan mesin `j` pada teks.

**Kapan dipakai / kapan tidak.** Satu pola vs banyak pola: KMP ulang tiap pola, atau Aho-Corasick.

**Proses:** pola `aba` (m=3), teks `abacaba`. Mesin `j` pada teks (tanpa gabung):

```
i  huruf  j sebelum  cocok?  j sesudah  ketemu?
0  a      0          ya      1          tidak
1  b      1          ya      2          tidak
2  a      2          ya      3          YA di 0   lalu j=pi[2]=1
3  c      1          tidak   0          (c≠b, c≠a)
4  a      0          ya      1
5  b      1          ya      2
6  a      2          ya      3          YA di 4   lalu j=1
posisi: 0 dan 4
```

Cara gabung `g = pola + SEP + teks`:

```
g indeks:  0 1 2  3   4 5 6 7 8 9 10
g huruf :  a b a SEP  a b a c a b a
pi[6]=3, pi[10]=3  (panjang pola tercapai)

Kemunculan berakhir di i, mulai di g pada startG = i-m+1
Posisi di teks = startG - (m+1)     karena pola+SEP memakan m+1 karakter
i=6  → startG=4  → teks 0
i=10 → startG=8  → teks 4

Setara: posisi = i - 2*m   jika |SEP|=1. Hafalkan startG, lebih sulit tertukar.
```

`"ababab"`: `pi` akhir 4, `p=6-4=2`, `6%2==0` → periode 2.
`"ababa"`: `pi` akhir 3, `p=2`, `5%2≠0` → periode sejati 5, bukan 2.

**Kode:**

```cpp
vector<int> kmpCari(const string& teks, const string& pola) {
    vector<int> ans;
    int m = (int)pola.size(), n = (int)teks.size();
    if (m == 0) return ans;
    vector<int> pi = prefixFunction(pola);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && teks[i] != pola[j]) j = pi[j - 1];
        if (teks[i] == pola[j]) j++;
        if (j == m) {
            ans.push_back(i - m + 1);
            j = pi[j - 1];                  // izinkan tumpang tindih
        }
    }
    return ans;
}

vector<int> kmpCariGabung(const string& teks, const string& pola) {
    const char SEP = 1;
    string g = pola + SEP + teks;
    vector<int> pi = prefixFunction(g), ans;
    int m = (int)pola.size();
    for (int i = m + 1; i < (int)g.size(); i++)
        if (pi[i] == m) {
            int startG = i - m + 1;
            ans.push_back(startG - (m + 1));
        }
    return ans;
}

int periodeTerkecil(const string& s) {
    int n = (int)s.size();
    if (n == 0) return 0;
    int p = n - prefixFunction(s)[n - 1];
    if (n % p == 0) return p;
    return n;
}

vector<int> semuaBorder(const string& s) {
    vector<int> pi = prefixFunction(s), b;
    int k = (int)s.size() ? pi.back() : 0;
    while (k > 0) {
        b.push_back(k);
        k = pi[k - 1];
    }
    return b;
}

// berapa kali tiap prefiks muncul sebagai prefiks potongan s[0..i]
vector<int> hitungPrefiks(const string& s) {
    vector<int> pi = prefixFunction(s);
    int n = (int)s.size();
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) c[pi[i]]++;
    for (int i = n - 1; i > 0; i--) c[pi[i - 1]] += c[i];
    for (int i = 1; i <= n; i++) c[i]++;   // prefiks itu sendiri
    return c;                               // c[len]
}
```

**Jebakan:**

- `j = pi[j]` saat `j==m` tanpa `-1`.
- SEP muncul di teks → mesin menyatu, WA.
- Periode: `n-pi[n-1]` **kandidat**. `"ababab"` p=2, 6%2=0 OK. `"ababa"` p=5-3=2, 5%2≠0 → periode sejati 5, bukan 2.
- Rumus indeks gabung: uji dengan contoh `aba` di `abacaba` harus `[0, 4]`.

**Kompleksitas:** O(n+m). `hitungPrefiks` O(n).

## Z-function

**Teori:** `z[i]` = LCP antara `s` dan `s[i..n-1]`. `z[0]=0` pada template ini (beberapa orang mengisi n; pilih satu).

Z-box `[l, r)` adalah segmen paling kanan yang sudah terbukti sama dengan awalan. Untuk `i` di dalam box, `z[i]` minimal `min(r-i, z[i-l])`, lalu diperpanjang manual. Setiap perpanjangan mendorong `r` maju, jadi total O(n).

**Kapan dipakai / kapan tidak.**

- Pakai: cari pola (`pola + SEP + teks`, cari `z[i]>=|pola|`), border (`z[i]==n-i`), periode.
- KMP dan Z saling menggantikan untuk banyak soal; hafalkan **satu** yang kamu bisa debug.

**Proses:** `s = "aabcaab"`.

```
i=1 "abcaab" vs "aabcaab"  LCP=1 ('a')
i=2 "bcaab"  vs "a..."     0
i=3 "caab"                 0
i=4 "aab"    vs "aab..."   3
i=5 "ab"                   1
i=6 "b"                    0
z = [0,1,0,0,3,1,0]
```

Box saat i=4: r maju ke 7. i=5 di dalam box: `z[5] = min(7-5, z[1]) = min(2,1)=1`, cocok.

**Kode:**

```cpp
vector<int> bangunZ(const string& s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;                       // [l, r) terbukti = s[0..r-l)
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

vector<int> cariZ(const string& teks, const string& pola) {
    vector<int> ans;
    int m = (int)pola.size();
    if (m == 0) return ans;
    string g = pola + char(1) + teks;
    vector<int> z = bangunZ(g);
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) ans.push_back(i - m - 1);
    return ans;
}

int periodeZ(const string& s) {
    int n = (int)s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (i + z[i] == n && n % i == 0) return i;
    return n;
}
```

**Jebakan:** konvensi `r` inklusif vs eksklusif campur. Template ini `r` eksklusif. `z[0]=n` lalu `z[i-l]` saat `l=0` merusak. SEP `'#'` di string yang berisi `#`.

**Kompleksitas:** O(n).

## Manacher — ide

**Teori:** palindrom berpusat di suatu titik, radius `r` berarti `s[c-r..c+r]` palindrom. Naif O(n²). Manacher memakai simetri: jika kamu sudah punya palindrom besar `[L, R]` berpusat `C`, maka palindrom di `i` di dalam `[L,R]` punya “cermin” `i' = 2C-i`. Radius di `i` minimal `min(radius[i'], R-i)`, lalu diperpanjang.

Agar pusat genap dan ganjil seragam, sisipkan sentinel: `^#a#b#a#$`. Semua palindrom jadi ganjil di string baru.

Kamu tidak wajib menghafal setiap indeks di kontes pertama. Ide yang harus dibawa: **radius + cermin + kanan terjauh**, sama semangatnya dengan Z-box.

**Kapan dipakai / kapan tidak.**

- Pakai: longest palindromic substring, jumlah palindrom, “untuk setiap pusat, radius”.
- Jangan: satu pertanyaan palindrom `[l,r]` — hash dua arah cukup.
- Jika lupa rumus, binary search + hash palindrom O(n log n) sering lolos.

**Proses:** `s = "aba"`. String baru `^#a#b#a#$` (atau `#a#b#a#`).

```
pusat 'b': radius 3 di string baru → palindrom "aba" di asli
pusat 'a' kiri: radius 1 → huruf tunggal
```

Cermin: pada `"aaa"`, setelah pusat pertama panjang, pusat berikutnya menyalin radius.

**Kode (versi kerja, pusat ganjil+genap tanpa sentinel — dua pass):**

```cpp
pair<int, int> palindromTerpanjang(const string& s) {
    int n = (int)s.size();
    int bestL = 0, bestR = 0;               // [L, R] inklusif, panjang 1
    auto perluas = [&](int L, int R) {
        while (L >= 0 && R < n && s[L] == s[R]) {
            if (R - L > bestR - bestL) {
                bestL = L;
                bestR = R;
            }
            L--;
            R++;
        }
    };
    for (int i = 0; i < n; i++) {
        perluas(i, i);
        perluas(i, i + 1);
    }
    return {bestL, bestR};
}

// Manacher penuh: d1[i] radius ganjil, d2[i] radius genap
void manacher(const string& s, vector<int>& d1, vector<int>& d2) {
    int n = (int)s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}

long long jumlahPalindrom(const string& s) {
    vector<int> d1, d2;
    manacher(s, d1, d2);
    ll ans = 0;
    for (int x : d1) ans += x;
    for (int x : d2) ans += x;
    return ans;
}
```

`palindromTerpanjang` O(n²) terburuk (`aaaa...`) tetapi mudah. `manacher` O(n). Untuk latihan, kerjakan keduanya dan bandingkan hasil.

**Jebakan:** mencampur d1/d2. Radius ganjil `d1[i]=k` berarti palindrom panjang `2k-1` berpusat i. Genap `d2[i]=k` panjang `2k` berpusat di antara i-1 dan i (tergantung implementasi — uji `"aa"`). Off-by-one di sini sangat umum.

**Kompleksitas:** Manacher O(n), expand-all O(n²) terburuk.

## Trie

**Teori:** pohon, tiap sisi satu huruf. Jalur dari akar = awalan. Simpul bisa menandai “ada kata berakhir di sini” plus hitungan. Insert/cari O(panjang).

Analogi: indeks kamus per huruf. Semua kata `app`, `apple`, `ape` berbagi `ap`.

**Kapan dipakai / kapan tidak.**

- Pakai: kamus, prefix matching, XOR (versi biner), Aho-Corasick (lanjutan).
- Jangan: n·|Σ|·L meledak memori jika kamu alokasi 26 anak di setiap simpul tanpa hemat, pada L besar. Map/array dinamis atau `next[26]` dengan simpul ≤ jumlah huruf total.

**Proses:** sisip `"ab"`, `"ac"`, `"b"`.

```
    *
   / \
  a   b (akhir)
 / \
b   c
(akhir) (akhir)
```

Cari `"a"`: sampai simpul a, bukan akhir → tidak ada kata `"a"`, tetapi ada prefix. Cari `"ab"`: akhir → ya.

**Kode:**

```cpp
struct Trie {
    struct Node {
        int next[26];
        int akhir, hitung;                  // kata berakhir; berapa sisipan lewat sini
        Node() {
            memset(next, -1, sizeof next);
            akhir = hitung = 0;
        }
    };
    vector<Node> t;

    Trie() { t.push_back(Node()); }

    int buat() {
        t.push_back(Node());
        return (int)t.size() - 1;
    }

    void sisip(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) t[v].next[c] = buat();
            v = t[v].next[c];
            t[v].hitung++;
        }
        t[v].akhir++;
    }

    bool cariKata(const string& s) const {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) return false;
            v = t[v].next[c];
        }
        return t[v].akhir > 0;
    }

    int hitungPrefix(const string& p) const {
        int v = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) return 0;
            v = t[v].next[c];
        }
        return t[v].hitung;
    }
};
```

Hapus: turunkan `hitung`/`akhir`, jangan wajib hapus sisi (cukup tandai).

**Jebakan:** `ch-'a'` negatif jika ada huruf besar. Alfabet bukan 26: ganti `map<char,int>` atau 256. Lupa `hitung++` di setiap simpul → prefix count salah. Akar `hitung` tidak naik di kode ini (sengaja: hitung prefix kosong = jumlah kata, bisa ditambah di akar jika perlu).

**Kompleksitas:** O(total huruf) waktu dan memori.

## Binary Trie XOR

**Teori:** masukkan angka 30–32 bit, MSB dulu. XOR terbesar dengan `x`: di tiap bit, usahakan ambil cabang **lawan** bit `x` jika ada (supaya XOR 1). XOR terkecil: usahakan cabang **sama**.

**Kapan dipakai / kapan tidak.**

- Pakai: max XOR pair, max XOR subarray (prefix XOR + trie), k-th XOR.
- Jangan: n=10⁷, 32 bit, memori  n·32 simpul — hitung dulu.

**Proses:** masukkan 5=`101`, 7=`111`. Query x=2=`010`.

```
bit2: x=0, lawan=1 ada (5 dan 7) → ambil 1
bit1: x=1, lawan=0? 5=101 bit1=0 ya → ambil 0  (angka 5)
bit0: x=0, lawan=1, 5=101 bit0=1 ya
hasil XOR 5^2=7. 7^2=5, max=7. Benar.
```

**Kode:**

```cpp
struct BinTrie {
    static const int B = 30;
    vector<array<int, 2>> next;
    vector<int> cnt;

    BinTrie() { buat(); }

    int buat() {
        next.push_back({-1, -1});
        cnt.push_back(0);
        return (int)next.size() - 1;
    }

    void sisip(int x, int d = 1) {
        int v = 0;
        cnt[v] += d;
        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (next[v][bit] == -1) next[v][bit] = buat();
            v = next[v][bit];
            cnt[v] += d;
        }
    }

    int maxXor(int x) const {
        if (cnt[0] == 0) return 0;
        int v = 0, ans = 0;
        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            if (next[v][want] != -1 && cnt[next[v][want]] > 0) {
                ans |= 1 << b;
                v = next[v][want];
            } else v = next[v][bit];
        }
        return ans;
    }
};

int maxXorSubarray(const vector<int>& a) {
    BinTrie tr;
    tr.sisip(0);
    int px = 0, ans = 0;
    for (int x : a) {
        px ^= x;
        ans = max(ans, tr.maxXor(px));
        tr.sisip(px);
    }
    return ans;
}
```

**Jebakan:** LSB dulu → salah total. `sisip` negatif: pakai unsigned / geser aman. Hapus dengan `d=-1` wajib `cnt`. Query trie kosong.

**Kompleksitas:** O(B) per operasi, B=30/31. Memori O(n B).

## Suffix Array — ide

**Teori:** suffix array `sa[i]` = indeks awal sufiks ke-i jika **semua sufiks diurutkan leksikografis**. `s = "banana"`:

```
0 banana
1 anana
2 nana
3 ana
4 na
5 a

terurut:
5 a
3 ana
1 anana
0 banana
4 na
2 nana
sa = [5,3,1,0,4,2]
```

LCP `lcp[i]` = prefix bersama `sa[i]` dan `sa[i-1]` (atau `sa[i]` dan `sa[i+1]`, pilih konvensi). Kasai menghitung LCP O(n) setelah SA ada: `lcp` sufiks `k` dan tetangga di SA berkaitan dengan `lcp` sufiks `k+1` — turun paling 1.

Kegunaan:

- Jumlah substring berbeda = n(n+1)/2 − jumlah LCP.
- LCS dua string: gabung `A + SEP + B`, cari LCP tetangga SA yang berasal dari string berbeda.
- Pattern search: binary search di SA, O(|P| log n).

Membangun SA:

1. Naif: sort semua sufiks O(n² log n) — hanya n ≤ 2000.
2. Doubling (Kasai/Manber-Myers): urutkan berdasar 2^k huruf, O(n log² n) dengan pair.
3. SA-IS linear — panjang, jarang ditulis di kontes live.

**Kapan dipakai / kapan tidak.**

- Pakai: distinct substring, LCS, banyak query sufiks.
- Hash + binary search sering menggantikan SA untuk LCP dua indeks.
- Jangan memulai SA di jam terakhir kontes jika belum ada template sendiri.

**Proses doubling (ide):**

```
peringkat awal = urutan karakter
k=1: gabung peringkat [i] dan [i+1]
k=2: gabung [i] dan [i+2]
k=4: ...
setelah log n putaran, peringkat unik = urutan sufiks
```

**Kode (doubling, cukup untuk n ≤ 2·10⁵):**

```cpp
vector<int> suffixArray(const string& s) {
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rnk[i] = (unsigned char)s[i];
    }
    for (int k = 1; k < n; k <<= 1) {
        auto kurang = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), kurang);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (kurang(sa[i - 1], sa[i]) ? 1 : 0);
        rnk.swap(tmp);
        if (rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

vector<int> bangunLCP(const string& s, const vector<int>& sa) {
    int n = (int)s.size();
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        int r = rank[i];
        if (r == 0) continue;
        int j = sa[r - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[r] = h;
        if (h) h--;
    }
    return lcp;                             // lcp[i] = LCP(sa[i], sa[i-1])
}

ll substringBerbeda(int n, const vector<int>& lcp) {
    ll semua = 1LL * n * (n + 1) / 2;
    for (int i = 1; i < n; i++) semua -= lcp[i];
    return semua;
}
```

Cari pola di SA:

```cpp
bool adaPola(const string& s, const vector<int>& sa, const string& p) {
    int n = (int)s.size(), m = (int)p.size();
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int cmp = s.compare(sa[mid], m, p);
        if (cmp < 0) lo = mid + 1;
        else hi = mid;
    }
    return lo < n && s.compare(sa[lo], m, p) == 0;
}
```

**Jebakan:**

- Sentinel: gabung dua string tanpa karakter pemisah → sufiks menyeberang. Pakai `char(1)`.
- `lcp[0]` tidak bermakna. Kasai `h--` boleh jadi 0, jangan negatif.
- `sort` O(n log n) per putaran = O(n log² n); radix sort mempercepat, tidak wajib.
- `s.compare(pos, m, p)` jika `pos+m > n` tetap aman di C++ (membandingkan sisa).

**Kompleksitas:** doubling O(n log² n), LCP Kasai O(n), memori O(n).

## Aho-Corasick dan SAM — peta

**Teori singkat, bukan implementasi penuh.**

**Aho-Corasick:** banyak pola. Bangun Trie semua pola, isi *failure link* seperti KMP di pohon. Teks ditelusuri sekali, O(n + total pola + laporan). Pakai jika ≥ 2 pola dan n besar.

**Suffix Automaton:** automata terkecil yang menerima semua substring. Banyaknya state O(n). Menghitung distinct substring, endpos, kemunculan, sangat elegan dan mudah salah. Day 223.

Untuk cheatsheet ini: jika soal “banyak pola”, ingat Aho. Jika “semua substring / endpos”, ingat SAM atau SA+LCP. Jangan menulis keduanya dari nol di jam pertama.

**Kapan:** Aho ≈ kamus + teks. SAM ≈ substring statistics. SA ≈ urutan sufiks.

**Kompleksitas:** Aho O(n + Σ·simpul). SAM O(n).

## Tabel pilih alat string

| Kalimat soal | Alat pertama |
| --- | --- |
| dua potongan sama? | prefix hash (double) |
| cari satu pola | KMP atau Z |
| periode / border | `n-pi[n-1]` atau Z |
| palindrom terpanjang | Manacher, atau expand |
| banyak [l,r] palindrom? | hash dua arah |
| kamus prefix | Trie |
| XOR pasangan maksimum | Binary Trie |
| substring berbeda | SA+LCP atau SAM atau hash set |
| dua string, LCS substring | SA gabungan atau hash + binsearch |
| banyak pola | Aho-Corasick |
| anti-hash di CF | file 19, jangan single 10⁹+7 |

Uji kecil wajib:

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string t = "abacaba", p = "aba";
    auto a = kmpCari(t, p);
    auto b = cariZ(t, p);
    auto c = rabinKarp(t, p);
    assert(a == b && b == c);
    assert((a == vector<int>{0, 4}));
    assert(periodeTerkecil("ababab") == 2);
    assert(periodeTerkecil("ababa") == 5);
    cout << "ok\n";
}
```

## Ringkasan

1. Hash mengubah potongan jadi angka. Samakan pangkat. Pakai dua modulus atau basis acak.
2. `pi` = border. Jari teks tidak mundur. Periode kandidat `n-pi[n-1]`, cek `n%p==0`.
3. `z[i]` = LCP dengan awal. Z-box = Manacher-box = “sudah terbukti, salin cermin”.
4. Manacher = radius palindrom linear. Kalau lupa, expand atau hash.
5. Trie = kamus. Binary Trie = XOR bit demi bit, MSB dulu.
6. Suffix Array = semua sufiks terurut. LCP Kasai linear. Ide doubling: pangkat dua huruf.
7. Aho dan SAM cukup dikenal namanya sampai kamu butuh Day 221–223.

Latihan: CSES *String Matching*, *Finding Borders*, *Word Combinations* (Trie/DP), *Suffix Array* jika sudah siap. Day 211–219 di `ComProgLearning/CP` adalah jalur harian. Setelah AC hash+KMP+Z, baru SA.
