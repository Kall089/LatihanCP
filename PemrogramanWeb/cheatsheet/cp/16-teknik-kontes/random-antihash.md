# Random dan anti-hash

[← Stress test](stress-test.md) · [Teknik kontes](README.md) · [Hashing](../12-string/hashing.md)

Day 252. Keacakan untuk menghindari pola jahat dan tabrakan hash. Edukatif: melindungi **solusimu** di kontes, bukan merakit tes untuk menyerang peserta lain atau menembus sistem.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [mt19937](#mt19937)
- [Distribusi, bukan modulo](#distribusi-bukan-modulo)
- [Shuffle](#shuffle)
- [Peluang gagal](#peluang-gagal)
- [Kenapa single hash rapuh](#kenapa-single-hash-rapuh)
- [Double hash](#double-hash)
- [Basis dan modulus acak](#basis-dan-modulus-acak)
- [2^64 dan Thue–Morse](#264-dan-thuemorse)
- [Hasher aman](#hasher-aman)
- [Checklist submit](#checklist-submit)
- [Ringkasan](#ringkasan)

## mt19937

**Teori:** `rand()` C lama, periode pendek, `rand()%n` bias. Pakai `mt19937` (32 bit) atau `mt19937_64`. Seed dari waktu + (opsional) hash input supaya dua run beda.

Di Codeforces, seed tetap 1 membuat hash P tetap — lawan yang tahu P bisa merancang tabrakan jika P klasik. Seed waktu membuat P tidak diketahui sebelum run.

**Kapan:** hash basis, shuffle, Miller–Rabin, generator stress ([stress-test.md](stress-test.md)).

**Proses:** dua `mt19937` default tanpa seed menghasilkan urutan sama. Seed `chrono` beda tiap detik.

**Kode:**

```cpp
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void seedCampur(ull extra) {
    rng.seed(chrono::steady_clock::now().time_since_epoch().count() ^ extra);
}
```

`ull` = `unsigned long long`. Extra bisa `n` atau xor semua a[i] supaya tes sama di debug tetap beda P antar tes berbeda.

**Jebakan:** seed 0 di semua tes. Dua objek `mt19937` tanpa seed. Mencetak seed ke stdout (merusak output soal).

**Kompleksitas:** O(1) generate.

## Distribusi, bukan modulo

**Teori:** `rng() % (r-l+1)` bias jika rentang tidak membagi 2^32, dan overflow jika `r-l+1` dihitung `int`. `uniform_int_distribution` merata.

**Kapan:** semua acak integer di kontes.

**Proses:** l=1, r=3. Ingin 1,2,3 merata. `rng()%3` pada 32-bit hampir merata, tetap bias kecil. Kebiasaan distribusi lebih bersih.

**Kode:**

```cpp
ll randInt(ll l, ll r) {                    // inklusif
    uniform_int_distribution<ll> dist(l, r);
    return dist(rng);
}

double rand01() {
    uniform_real_distribution<double> d(0.0, 1.0);
    return d(rng);
}
```

**Jebakan:** `l > r`. `rng() % (r-l+1)` saat `r-l+1` = 0. `int` overflow `r-l+1` untuk l=0, r=INT_MAX.

**Kompleksitas:** O(1) amortised.

## Shuffle

**Teori:** `random_shuffle` usang. `shuffle(v.begin(), v.end(), rng)` Fisher–Yates dengan mesinmu.

Pakai: urutan pemrosesan agar kasus jahat rata-rata, Quick-select, acak urutan sisi (bukan untuk Kruskal yang deterministik benar).

**Kapan:** kompleksitas harapan, bukan kebenaran.

**Proses:** `[1,2,3,4]` setelah shuffle salah satu 24 permutasi.

**Kode:**

```cpp
void acakUrutan(vector<int>& a) { shuffle(a.begin(), a.end(), rng); }

vector<int> permId(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    acakUrutan(a);
    return a;
}
```

**Jebakan:** `shuffle` tanpa rng (overload lama). Mengira shuffle membuat algoritma O(n²) “selalu” cepat — masih ada tes jahat, hanya jarang.

**Kompleksitas:** O(n).

## Peluang gagal

**Teori:** Monte Carlo: jawaban salah dengan peluang p. Jika p=2^{-60} dan 100 tes, aman. Jika p=10^{-6} dan 10^5 banding hash, mulai hitung.

```
P(minimal satu tabrakan) ≈ 1 − (1 − 1/M)^k  ≈ k/M
```

Satu modulus 10^9+7, k=10^5 banding: ~10^{-4}. Di CF dengan hack, lawan **mencari** tabrakan, bukan acak — rumus acak tidak berlaku.

**Kapan:** putuskan double hash vs single.

**Proses:** dua modulus 10^9+7 dan 10^9+9: k/M1/M2 ~ 10^{-13} untuk k=10^5, untuk tes acak. Lawan harus menabrakkan keduanya.

**Kode:** tidak ada. Hitung di kertas.

```
k = 2e5
M = 1e9+7
k/M ≈ 2e-4     single, tes acak
1/(M1 M2) * k ≈ 2e-13
```

**Jebakan:** “double mustahil salah”. Masih mungkin, sangat jarang.

**Kompleksitas:** konsep.

## Kenapa single hash rapuh

**Teori:** `mod=1e9+7`, `P=31` atau `P=131` **dikenal**. Orang bisa menyusun dua string beda berhash sama (birthday / konstruksi polinom). Di CF Div. 1, solusi single klasik sering di-hack.

Ini alasan memakai double atau P/M acak pada **programmu**, bukan alasan menulis generator tabrakan untuk menyerang orang.

**Kapan:** selalu di CF hackable. AtCoder/CSES jarang hack; double tetap rapi.

**Proses:** dua string pendek bisa tabrakan 32-bit. 64-bit lebih sulit tetapi 2^64 punya keluarga khusus.

**Kode:** jangan pakai ini sebagai hash utama di CF:

```cpp
const ll BURUK_P = 31;
const ll BURUK_M = 1000000007;
```

Ganti: dua modulus atau acak.

**Jebakan:** “tes contoh lulus jadi aman”. Hack di system test / hacking phase.

**Kompleksitas:** hash tetap O(n).

## Double hash

**Teori:** dua (P,M) independen. Sama hanya jika keduanya setuju. Lihat [hashing.md](../12-string/hashing.md).

**Kapan:** default aman tanpa acak runtime.

**Proses:** tabrakan harus solusi simultan dua kongruensi.

**Kode:**

```cpp
struct Hasher {
    ll P, M;
    vector<ll> h, pw;
    Hasher(const string& s, ll P_, ll M_) : P(P_), M(M_) {
        int n = (int)s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * P % M;
            h[i + 1] = (h[i] + (ll)((unsigned char)s[i] + 1) * pw[i]) % M;
        }
    }
    ll raw(int l, int r) const {
        ll x = h[r + 1] - h[l];
        if (x < 0) x += M;
        return x;
    }
    bool sama(int a, int b, int c, int d) const {
        if (b - a != d - c) return false;
        return raw(a, b) * pw[c] % M == raw(c, d) * pw[a] % M;
    }
};

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

**Jebakan:** dua hasher P,M sama. Overflow kali sebelum `%` — `__int128` jika perlu.

**Kompleksitas:** 2×.

## Basis dan modulus acak

**Teori:** pilih P ganjil acak > 256, M dari daftar prima atau uji prima sederhana untuk n ~ 1e9. Lawan tidak tahu P saat menulis tes (hacking phase melihat kode — di CF hacker **bisa** baca kode. Acak **runtime** tetap menyulitkan tes statis. Tes adaptif lebih sulit).

Daftar prima tetap + shuffle cukup.

**Kapan:** CF. Jangan cetak P ke stdout.

**Proses:** shuffle kandidat, ambil pertama. P = acak ganjil [257, 1e6].

**Kode:**

```cpp
const ll CAND[] = {1000000007, 1000000009, 998244353,
                   1000000033, 1000000087, 1000000093};

bool primaCekKasar(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n && i <= 200000; i++)
        if (n % i == 0) return false;
    return true;
}

pair<ll, ll> pilihMod() {
    vector<ll> c(begin(CAND), end(CAND));
    shuffle(c.begin(), c.end(), rng);
    ll P = randInt(257, 1000000);
    if (P % 2 == 0) P++;
    return {P, c[0]};
}

Hasher buatHasherAman(const string& s) {
    auto [P, M] = pilihMod();
    return Hasher(s, P, M);
}
```

Uji prima penuh untuk M acak 1e9+ tidak wajib jika daftar tetap.

**Jebakan:** `P < 128` pada ASCII. Tabrakan sistematis dengan karakter 0 jika tidak `c+1`. Dua hasher lupa seed beda tetapi P,M sama karena `pilihMod` dipanggil sekali — itu OK jika satu objek. Memakai P sama untuk dua string yang dibanding: **wajib sama** P,M.

**Kompleksitas:** inisialisasi O(1) daftar, atau O(√M) jika uji naif sekali.

## 2^64 dan Thue–Morse

**Teori:** overflow `unsigned long long` = mod 2^64, cepat. Bukan prima. Ada konstruksi string (keluarga Thue–Morse / anti-hash 2^64) yang membuat banyak solusi 2^64 murni gagal di CF.

Pakai 2^64 sebagai **pelengkap**, bukan satu-satunya.

**Kapan:** hash ketiga, atau AtCoder. CF Div. 1: 2^64 + modulus prima.

**Proses:** `Hash64` di hashing.md + `Hasher` prima.

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

bool samaAman(const Hash64& a, const Hasher& b,
              int i1, int j1, int i2, int j2) {
    return a.sama(i1, j1, i2, j2) && b.sama(i1, j1, i2, j2);
}
```

**Jebakan:** `ll` signed overflow UB. 2^64 saja di CF.

**Kompleksitas:** O(n).

## Hasher aman

**Teori:** resep praktis satu struct: dua prima, P acak sama untuk keduanya atau P beda.

**Kapan:** template default string.

**Proses:** banding potongan, kedua modulus setuju.

**Kode:**

```cpp
struct HashAman {
    Hasher a, b;
    HashAman(const string& s)
        : a(s, 0, 0), b(s, 0, 0) {
        ll P = randInt(257, 2000000) | 1;
        a = Hasher(s, P, 1000000007);
        b = Hasher(s, P + 2, 1000000009);
    }
    bool sama(int i1, int j1, int i2, int j2) const {
        return a.sama(i1, j1, i2, j2) && b.sama(i1, j1, i2, j2);
    }
};
```

`Hasher` butuh assign. Jika constructor `Hasher(s,0,0)` merepotkan, bangun a,b di body dengan pointer atau optional. Versi bersih:

```cpp
struct HashAman2 {
    unique_ptr<Hasher> a, b;
    explicit HashAman2(const string& s) {
        ll P = randInt(257, 2000000) | 1;
        a.reset(new Hasher(s, P, 1000000007));
        b.reset(new Hasher(s, P + 4, 1000000009));
    }
};
```

Atau dua field setelah default constructor Hasher kosong yang kamu tambah.

**Jebakan:** verifikasi O(n) setiap match saat n² match → TLE. Verifikasi huruf hanya jika single hash dan jumlah match kecil.

**Kompleksitas:** sama hash biasa.

## Checklist submit

**Teori:** bukan algoritma, menghemat penalty. Random/hash hanya satu poin.

**Kapan:** 2 menit sebelum submit.

**Proses:** baca daftar.

**Kode:** tidak ada. Daftar:

1. Output `Yes/No` vs `YES/NO`, 0/1-index.
2. Overflow: kali `int` 2e9, `n(n+1)`, `ll`.
3. n=1, kosong, semua sama, negatif, sudah terurut.
4. Graf: 1-based, sisi bolak-balik, n=1.
5. Interaktif: `flush`, hati-hati `FASTIO`.
6. Hash: double atau P acak di CF. Jangan 10^9+7 tunggal.
7. Geo: overflow cross, kolinear, duplikat.
8. Game: normal vs misère.
9. WA tes 1: contoh soal. WA tes 2+: [stress-test.md](stress-test.md).
10. TLE: kompleksitas, `endl`, `map` vs array.

Resep 15 menit:

```
tulis brute + gen   (5 menit)
200 tes lokal       (2 menit)
perbaiki            (sisa)
submit
```

**Jebakan:** skip stress karena “yakin”. 4 WA × 20 menit lebih mahal.

**Kompleksitas:** 15 menit manusia.

## Miller–Rabin singkat

**Teori:** uji prima probabilistik memakai saksi acak. Untuk `ll` sampai 10^18, himpunan saksi deterministik kecil sudah cukup (bukan topik hash, tetapi mesin acak yang sama). Di kontes, daftar saksi tetap lebih rapi daripada `rand`.

**Kapan:** “apakah n prima” n besar, bukan sieve. Bukan untuk merancang modulus anti-orang; hanya menguji kandidat M milikmu.

**Proses:** n=91=7*13. Saksi 2 biasanya membongkar. n=10^9+7 lolos.

**Kode:**

```cpp
ll modPow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) r = (ll)((__int128)r * a % m);
        a = (ll)((__int128)a * a % m);
        e >>= 1;
    }
    return r;
}

bool saksi(ll a, ll n, ll d, int s) {
    ll x = modPow(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < s; i++) {
        x = (ll)((__int128)x * x % n);
        if (x == n - 1) return true;
    }
    return false;
}

bool primaMR(ll n) {
    if (n < 2) return false;
    for (ll p : {2LL, 3, 5, 7, 11, 13, 17, 19, 23}) {
        if (n % p == 0) return n == p;
    }
    ll d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (ll a : {2LL, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        if (!saksi(a, n, d, s)) return false;
    }
    return true;
}
```

**Jebakan:** overflow tanpa `__int128`. n genap. Memakai ini untuk “hack” modulus orang lain — di luar tujuan file.

**Kompleksitas:** O(k log n) perkalian.

## Ringkasan

1. `mt19937_64` + `uniform_int_distribution`, bukan `rand()%n`.
2. `shuffle(..., rng)`.
3. Single 10^9+7 + P=31 rawan di CF.
4. Double hash atau P/M acak runtime.
5. 2^64 pelengkap, bukan tunggal.
6. P harus sama saat membandingkan dua potongan. Jangan cetak P.

Latihan Day 252. Jangan salin folder ComprogLearning. Jangan menulis generator tabrakan untuk menyerang orang.
