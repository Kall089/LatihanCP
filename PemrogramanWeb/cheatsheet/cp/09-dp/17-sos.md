# 17 — SOS DP (Day 158)

[← Assignment](16-bitmask-assignment.md) · [README](README.md) · [Digit DP →](18-digit.md)

> **Satu kalimat:** SOS adalah prefix-sum di kubus `{0,1}^n` — setiap mask mengumpulkan nilai seluruh subset-nya dalam `O(n 2^n)`, bukan `O(3^n)`.

Day ComprogLearning: **158**. File ini teori + kode modular. Jangan menyalin `latihan/` atau `solusi/` dari folder Day.

Sebelum mengetik, tiga pertanyaan tetap:

```
1. STATE     : setelah bit 0..i-1 diproses, f[mask] menyimpan apa?
2. TRANSISI  : bit i nyala → tambah / max / OR dari mask tanpa bit i
3. BASIS     : f = array awal a
```

## Daftar isi

- [Teori: prefix sum di hiperkubus](#teori-prefix-sum-di-hiperkubus)
- [Kapan dipakai](#kapan-dipakai)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Naif O(3^n) dulu](#naif-o3n-dulu)
- [Proses angka n = 2](#proses-angka-n--2)
- [Proses angka n = 3](#proses-angka-n--3)
- [Superset sum](#superset-sum)
- [Invers SOS (Mobius)](#invers-sos-mobius)
- [OR, AND, max, count](#or-and-max-count)
- [Pasangan AND / OR](#pasangan-and--or)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori: prefix sum di hiperkubus

**Teori:** Diberi array `a[0 .. 2^n - 1]`. Untuk setiap mask `x`, kita ingin

```
F[x] = jumlah semua a[s] dengan s ⊆ x
```

Itu **Sum Over Subsets**. Analoginya prefix-sum 1D:

```
pref[i] = a[0] + a[1] + ... + a[i]
```

hanya saja dimensinya `n` bit, tiap bit adalah satu sumbu `{0, 1}`.

Bayangkan dua bit sebagai persegi:

```
     bit1
      ↑
  10  ·  11
  00  ·  01  → bit0
```

Prefix-sum di persegi: setiap titik mengambil semua titik di "kiri-bawah"-nya. Bit yang nyala boleh "turun" jadi 0; bit yang mati harus tetap 0. Itu persis `s ⊆ x`.

Kenapa bukan loop subset biasa? Karena untuk tiap `x` kita bisa enumerasi `s ⊆ x` dalam `O(2^{popcount(x)})`, total `O(3^n)`. SOS menghemat: tiap bit sekali "disebar", total `O(n 2^n)`.

Untuk `n = 20`: `3^20 ≈ 3.4e9` (mati), `20 * 2^20 ≈ 2.1e7` (aman).

**Kapan:** lihat bagian berikutnya. Intinya: banyak soal "agregat atas seluruh subset / seluruh superset" adalah SOS, bukan TSP dan bukan knapsack biasa.

---

## Kapan dipakai

**Kapan dipakai.**

| Gejala soal | Arah SOS |
|---|---|
| "untuk setiap mask, jumlahkan `a` di seluruh subset-nya" | subset zeta |
| "untuk setiap mask, jumlahkan `a` di seluruh superset-nya" | superset zeta |
| "berapa pasangan `(i, j)` dengan `a[i] & a[j] = 0`" | SOS count + komplement |
| "OR / AND / max seluruh subset" | SOS dengan operator lain |
| "kembalikan `a` dari `F`" | invers / Mobius |
| "subset convolution" (lanjut) | SOS + per-ukuran |

**Kapan tidak.**

1. `n > 23` — memori `2^n` sudah berat; `n = 26` array `ll` ≈ 2 GB.
2. Hanya butuh **satu** mask tertentu — enumerasi subset mask itu saja, `O(2^{popcount})`.
3. Butuh subset **tepat ukuran k** dan tidak mau dimensi ukuran — tambah dimensi `popcount`, atau loop per bit dengan hati-hati.
4. Soal TSP / assignment — itu file [15](15-bitmask-tsp.md) dan [16](16-bitmask-assignment.md): state-nya "sudah mengunjungi himpunan", bukan "jumlah seluruh subset".
5. Subset sum nilai (bukan mask) — itu [06](06-subset-sum.md) atau [23](23-bitset.md).

---

## STATE TRANSISI BASIS

**STATE:** setelah memproses bit `0 .. i-1`, `f[mask]` adalah agregat `a[s]` untuk semua `s` yang:

- pada bit `≥ i`: sama persis dengan `mask`,
- pada bit `< i`: boleh 0 di tempat `mask` bernilai 1 (subset di bit yang sudah diproses).

Kalau semua `n` bit sudah diproses, syarat kedua mencakup seluruh subset: itu `F[mask]`.

**TRANSISI (subset, operator +):**

```
for i in 0..n-1:
    for mask in 0 .. 2^n-1:
        if bit i nyala di mask:
            f[mask] += f[mask ^ (1 << i)]
```

Artinya: "ambil juga semua nilai yang sudah terkumpul di versi mask dengan bit `i` dimatikan".

**TRANSISI (superset):** kebalikan tes bit:

```
if bit i mati di mask:
    f[mask] += f[mask | (1 << i)]
```

atau ekuivalen `if (!(mask >> i & 1)) f[mask] += f[mask ^ (1 << i)]`.

**BASIS:** `f = a` (salin array awal). Tidak ada `f[0] = 0` ajaib — `a[0]` ikut dijumlah ke semua mask, karena `∅ ⊆ x` selalu.

**Operator lain:** ganti `+=` jadi `|=`, `&=`, `max`, `min`, atau `+=` modulo. Syarat: operator **asosiatif** dan "menambah elemen" masuk akal sebagai prefix-sum di kubus.

---

## Naif O(3^n) dulu

Pahami dulu versi lambat. Itu yang dibuktikan benar, lalu SOS hanya mempercepatnya.

**STATE:** tidak ada DP; `F[x]` dihitung langsung.

**TRANSISI:** untuk tiap `x`, loop `s = x; ; s = (s - 1) & x`.

**BASIS:** `F[x] = 0`, lalu tambah `a[s]`.

**Proses angka:** `x = 5 = 101_2`. Subset: `101, 100, 001, 000` yaitu 5, 4, 1, 0.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> sosNaive(const vector<ll>& a, int n) {
    int N = 1 << n;
    vector<ll> F(N, 0);
    for (int x = 0; x < N; x++) {
        for (int s = x; ; s = (s - 1) & x) {
            F[x] += a[s];
            if (s == 0) break;
        }
    }
    return F;
}
```

**Jebakan:** loop subset tanpa `if (s == 0) break` jalan tak hingga. `s = (s - 1) & x` pada `s = 0` menghasilkan `x` lagi.

**Kompleksitas:** `O(3^n)` karena `Σ_k C(n,k) 2^k = 3^n`.

---

## Proses angka n = 2

`n = 2`, `a[00]=1, a[01]=2, a[10]=4, a[11]=8`. Target subset-sum:

```
F[00] = a[00]                 = 1
F[01] = a[00]+a[01]           = 3
F[10] = a[00]+a[10]           = 5
F[11] = a[00]+a[01]+a[10]+a[11] = 15
```

SOS per bit.

```
awal:  f = [1, 2, 4, 8]

bit 0 (nilai 1):
  mask 01: f[01] += f[00]  →  2+1 = 3
  mask 11: f[11] += f[10]  →  8+4 = 12
  mask 00 dan 10 tidak berubah (bit 0 mati)
  f = [1, 3, 4, 12]

bit 1 (nilai 2):
  mask 10: f[10] += f[00]  →  4+1 = 5
  mask 11: f[11] += f[01]  → 12+3 = 15
  f = [1, 3, 5, 15]
```

Cocok. Urutan bit 0 dulu atau bit 1 dulu **sama hasil akhirnya**, karena tiap dimensi prefix-sum independen.

Jika bit 1 dulu:

```
awal [1, 2, 4, 8]
bit1: 10 ← 00  → [1, 2, 5, 8]
      11 ← 01  → [1, 2, 5, 10]
bit0: 01 ← 00  → [1, 3, 5, 10]
      11 ← 10  → [1, 3, 5, 15]
```

Sama.

---

## Proses angka n = 3

`n = 3`, `a[mask] = mask` sendiri: `a = [0,1,2,3,4,5,6,7]`.

Hitung `F[7]` naif: jumlah `0+1+...+7 = 28`.

SOS:

```
awal: 0 1 2 3 4 5 6 7

bit 0:
  1+=0 → 1
  3+=2 → 5
  5+=4 → 9
  7+=6 → 13
  f = 0 1 2 5 4 9 6 13

bit 1:
  2+=0 → 2
  3+=1 → 6
  6+=4 → 10
  7+=5 → 22
  f = 0 1 2 6 4 9 10 22

bit 2:
  4+=0 → 4
  5+=1 → 10
  6+=2 → 12
  7+=6 → 28
  f = 0 1 2 6 4 10 12 28
```

Cek beberapa mask:

| mask | subset | jumlah | SOS |
|---|---|---|---|
| 000 = 0 | {0} | 0 | 0 |
| 001 = 1 | 0,1 | 1 | 1 |
| 010 = 2 | 0,2 | 2 | 2 |
| 011 = 3 | 0,1,2,3 | 6 | 6 |
| 100 = 4 | 0,4 | 4 | 4 |
| 101 = 5 | 0,1,4,5 | 10 | 10 |
| 110 = 6 | 0,2,4,6 | 12 | 12 |
| 111 = 7 | semua | 28 | 28 |

---

## Superset sum

**Teori:** `G[x] = sum_{x ⊆ t} a[t]`. Setiap mask mengumpulkan **superset**-nya. Analoginya prefix-sum ke arah berlawanan: bit yang mati boleh "naik" jadi 1.

**Kapan:** "berapa nilai di array yang merupakan superset mask ini", atau "jumlah `a[t]` untuk semua `t` yang memuat bit-bit `x`".

**STATE:** setelah bit `0..i-1`, `f[mask]` sudah menggabungkan perbedaan pada bit `< i` ke arah **nyala**.

**TRANSISI:**

```
if (!(mask >> i & 1))
    f[mask] += f[mask ^ (1 << i)];
```

`mask ^ (1<<i)` di sini adalah `mask` dengan bit `i` dinyalakan (karena tadinya mati).

**BASIS:** `f = a`.

**Proses angka:** `n = 2`, `a = [1,2,4,8]`.

```
G[00] = 1+2+4+8 = 15   (semua adalah superset ∅)
G[01] = 2+8 = 10       (01 dan 11)
G[10] = 4+8 = 12
G[11] = 8
```

SOS:

```
awal [1, 2, 4, 8]
bit 0 (sebar dari nyala ke mati):
  00 += 01 → 1+2=3
  10 += 11 → 4+8=12
  f = [3, 2, 12, 8]
bit 1:
  00 += 10 → 3+12=15
  01 += 11 → 2+8=10
  f = [15, 10, 12, 8]
```

Cocok.

Relasi cepat: subset-sum dari `a` pada mask `x` sama dengan superset-sum dari array yang diindeks komplement, setelah dibalik bit. Tidak wajib dihafal; uji `n = 2` lebih aman.

---

## Invers SOS (Mobius)

**Teori:** Zeta (SOS) punya invers. Jika `F[x] = Σ_{s ⊆ x} a[s]`, maka

```
a[x] = Σ_{s ⊆ x} μ(x \ s) F[s]
```

di kubus boolean, `μ` hanya `+1` / `-1` menurut paritas bit yang dimatikan. Praktis: jalankan SOS **mundur** — kurangi, bukan tambah.

**Kapan:** soal memberi agregat, kamu butuh nilai per-mask asli. Atau setelah transform, kalikan, lalu invers (cikal bakal AND/OR convolution).

**STATE:** sama seperti SOS, tapi operator `-=`.

**TRANSISI:**

```
for i in 0..n-1:
    for mask:
        if mask punya bit i:
            f[mask] -= f[mask ^ (1 << i)]
```

Urutan bit boleh sama; yang penting setiap dimensi diinvers setelah dizeta.

**BASIS:** `f = F` (hasil SOS).

**Proses angka:** dari `F = [1, 3, 5, 15]` kembali ke `a = [1, 2, 4, 8]`.

```
F = [1, 3, 5, 15]
bit 0:
  01 -= 00 → 3-1=2
  11 -= 10 → 15-5=10
  f = [1, 2, 5, 10]
bit 1:
  10 -= 00 → 5-1=4
  11 -= 01 → 10-2=8
  f = [1, 2, 4, 8]
```

Jika kamu SOS lalu invers pada array yang sama, harus kembali ke semula. Itu tes pertama.

**Jebakan:** invers memakai `-=` pada **arah yang sama** dengan zeta yang dipakai. Jangan invers subset pada hasil superset.

---

## OR, AND, max, count

SOS bukan hanya jumlah.

### Max over subsets

`F[x] = max_{s ⊆ x} a[s]`.

Ganti `+=` jadi `f[mask] = max(f[mask], f[mask ^ (1<<i)])`.

Proses `a = [1, 2, 4, 8]`:

```
bit0: [1, max(2,1)=2, 4, max(8,4)=8]
bit1: [1, 2, max(4,1)=4, max(8,2)=8]
```

Memang `max` subset dari `11` adalah 8.

### OR over subsets

Kalau `a[s]` sudah nilai elemen, dan kamu ingin OR semua elemen di dalam mask, itu **bukan** SOS — itu subset-DP biasa `O(2^n)`:

```
dp[0] = 0;
for mask > 0:
    i = ctz(mask);
    dp[mask] = dp[mask ^ (1<<i)] | a[i];
```

SOS dipakai jika `a` sudah terindeks **per mask**, dan kamu ingin OR seluruh `a[s]` untuk `s ⊆ x`.

### Count

Kalau `a[s] ∈ {0,1}` artinya "mask `s` ada", maka `F[x]` = banyak subset (yang ada) di dalam `x`. Berguna untuk "berapa nilai `a[i]` yang merupakan subset dari `x`".

---

## Pasangan AND / OR

Pola klasik: array `v[1..m]` dengan `0 ≤ v[i] < 2^n`, `n ≤ 20`.

**Berapa pasangan i < j dengan `v[i] & v[j] == 0`?**

`v[i] & v[j] == 0` berarti `v[j]` subset dari komplement `v[i]`.

1. `cnt[x]` = banyak elemen bernilai `x`.
2. `F = sosSubsetSum(cnt)` → `F[x]` = banyak elemen yang `⊆ x`.
3. Untuk tiap elemen `v[i]`, tambah `F[complement(v[i])]`.
4. Kurangi pasangan `(i, i)` jika `v[i] & v[i] == 0` yaitu hanya `v[i] == 0`, dan bagi 2 karena tiap pasangan dihitung dua kali.

**Proses angka:** `n = 3`, `v = [1, 2, 4, 3]`.

```
1=001, 2=010, 4=100, 3=011
pasangan AND 0: (1,2), (1,4), (2,4)  → 3
(3,4)=011&100=0 juga! → 4 pasangan
```

```
cnt: 1,2,3,4 masing-masing 1
F[110]=6?  tunggu, hitung F[complement]:
comp(1)=110=6, subset 110: 000,010,100,110 → nilai ada: 2 dan 4 → 2
comp(2)=101=5, ada: 1 dan 4 → 2
comp(4)=011=3, ada: 1,2,3 → 3
comp(3)=100=4, ada: 4 → 1
jumlah 2+2+3+1=8, bagi 2 = 4. Cocok.
```

**Berapa pasangan `v[i] | v[j] == (1<<n)-1`?** Ekuivalen `comp(v[i]) ⊆ v[j]`. Superset-count atau subset-count pada komplement.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> sosSubsetSum(vector<ll> f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < N; mask++)
            if (mask >> i & 1) f[mask] += f[mask ^ (1 << i)];
    return f;
}

vector<ll> sosSupersetSum(vector<ll> f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < N; mask++)
            if (!(mask >> i & 1)) f[mask] += f[mask ^ (1 << i)];
    return f;
}

vector<ll> sosSubsetInv(vector<ll> f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < N; mask++)
            if (mask >> i & 1) f[mask] -= f[mask ^ (1 << i)];
    return f;
}

vector<ll> sosSubsetMax(vector<ll> f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < N; mask++)
            if (mask >> i & 1)
                f[mask] = max(f[mask], f[mask ^ (1 << i)]);
    return f;
}

vector<ll> sosNaive(const vector<ll>& a, int n) {
    int N = 1 << n;
    vector<ll> F(N, 0);
    for (int x = 0; x < N; x++) {
        for (int s = x; ; s = (s - 1) & x) {
            F[x] += a[s];
            if (s == 0) break;
        }
    }
    return F;
}

ll countAndZeroPairs(const vector<int>& v, int n) {
    int N = 1 << n;
    vector<ll> cnt(N, 0);
    for (int x : v) cnt[x]++;
    auto F = sosSubsetSum(cnt, n);
    ll raw = 0;
    for (int x : v) raw += F[((1 << n) - 1) ^ x];
    ll zeros = 0;
    for (int x : v) if (x == 0) zeros++;
    raw -= zeros;
    return raw / 2;
}

int main() {
    FASTIO;
    int n = 2;
    vector<ll> a = {1, 2, 4, 8};
    auto F = sosSubsetSum(a, n);
    auto G = sosSupersetSum(a, n);
    auto back = sosSubsetInv(F, n);
    for (ll x : F) cout << x << " ";
    cout << "\n";
    for (ll x : G) cout << x << " ";
    cout << "\n";
    for (ll x : back) cout << x << " ";
    cout << "\n";
    cout << countAndZeroPairs({1, 2, 4, 3}, 3) << "\n";
    return 0;
}
```

Keluaran yang diharapkan:

```
1 3 5 15
15 10 12 8
1 2 4 8
4
```

Versi modulo: ganti `+=` / `-=` dengan

```cpp
f[mask] += f[mask ^ (1 << i)];
if (f[mask] >= MOD) f[mask] -= MOD;
```

dan untuk invers:

```cpp
f[mask] -= f[mask ^ (1 << i)];
if (f[mask] < 0) f[mask] += MOD;
```

---

## Jebakan

1. **Subset vs superset tertukar.** Gejala: `F[0]` bukan `a[0]`, atau `F[full]` bukan jumlah semua. Uji `n = 2` di atas.

2. **Loop bit di dalam loop mask dengan update in-place yang salah arah.** In-place sah **hanya** jika untuk tiap bit, kamu membaca `mask ^ (1<<i)` yang sudah selesai untuk bit itu (tidak dobel-sebar). Pola `if (bit nyala) f[mask] += f[tanpa bit]` aman. Jangan `f[tanpa bit] += f[mask]` kecuali kamu sengaja arah sebaliknya dan paham urutan.

3. **`1 << n` overflow.** Untuk `n = 31` pakai `1LL << n`. SOS praktis `n ≤ 23`, jadi `int` masih aman untuk `1 << n`.

4. **Overflow nilai.** `n = 20`, `a[i] ≤ 1e9`, `F[full]` bisa `1e9 * 1e6`. Wajib `ll`.

5. **Lupa `a[0]`.** `∅ ⊆ x` selalu. Kalau `a[0]` adalah "tidak ada elemen" dan seharusnya 0, isi 0, jangan biarkan sampah.

6. **Mengira SOS = enumerate subset untuk TSP.** TSP menambah **satu** elemen per transisi. SOS mengumpulkan **semua** subset sekaligus.

7. **Invers tanpa uji putar-balik.** Setelah menulis zeta, langsung `assert(sosSubsetInv(sosSubsetSum(a, n), n) == a)`.

8. **Memori `vector<vector<>>`.** Satu dimensi `2^n` cukup. Jangan `dp[n+1][1<<n]` kecuali kamu debug lapisan per bit.

9. **`n` dari nilai maksimum, bukan dari `log2(max)` yang salah.** Jika nilai sampai `1e6`, `n` = 20 (`2^20 > 1e6`), bukan 6.

10. **Count pasangan: lupa bagi 2 dan diagonal.** `v[i] & v[i] == 0` hanya jika `v[i] == 0`.

---

## Kompleksitas

| Varian | Waktu | Memori |
|---|---|---|
| naif subset per mask | `O(3^n)` | `O(2^n)` |
| SOS subset / superset | `O(n 2^n)` | `O(2^n)` |
| invers | `O(n 2^n)` | `O(2^n)` |
| max / OR analog | `O(n 2^n)` | `O(2^n)` |
| count pasangan AND 0 | `O(n 2^n + m)` | `O(2^n)` |

Batas aman kontes 1–2 detik:

| n | `n 2^n` | catatan |
|---|---|---|
| 16 | 1e6 | sangat longgar |
| 20 | 2.1e7 | standar |
| 22 | 9e7 | masih masuk |
| 23 | 1.9e8 | pas, jangan banyak konstanta |
| 24 | 4e8 | berbahaya kecuali bitset / `int` ketat |

`ll` pada `n = 23`: `8 * 8e6 ≈ 64 MB` — cek limit 32/64/128 MB.

---

## Tabel uji

| Fungsi | Input | Output |
|---|---|---|
| subset sum | `n=2`, `a=1,2,4,8` | `1 3 5 15` |
| superset sum | sama | `15 10 12 8` |
| invers | `F=1,3,5,15` | `1 2 4 8` |
| subset sum | `n=3`, `a=0..7` | `F[7]=28` |
| subset max | `a=1,2,4,8` | `1 2 4 8` |
| AND-0 pairs | `{1,2,4,3}`, `n=3` | `4` |
| naif vs SOS | acak `n=10` | harus identik |

Generator mini untuk stres (bukan soal kontes):

```cpp
bool sama(const vector<ll>& a, const vector<ll>& b) {
    return a == b;
}

void tesAcak() {
    int n = 10;
    vector<ll> a(1 << n);
    mt19937_64 rng(42);
    for (ll& x : a) x = (ll)(rng() % 100);
    assert(sama(sosNaive(a, n), sosSubsetSum(a, n)));
    assert(sama(a, sosSubsetInv(sosSubsetSum(a, n), n)));
}
```

---

## Checklist

Sebelum submit:

1. Kalimat STATE bisa diucapkan tanpa kata "jawabannya".
2. Arah subset atau superset sudah dipilih, dan `F[0]` / `F[full]` masuk akal.
3. `f` bertipe `ll` jika menjumlah.
4. `n` = lebar bit, `N = 1 << n`, array berukuran `N` bukan `n`.
5. Invers diuji putar-balik pada contoh `n = 2`.
6. Pasangan: bagi 2, kurangi diagonal.
7. Tidak menyalin kode dari `ComprogLearning/.../solusi`.

Peta cepat folder ini: bitmask kunjungi kota di [15](15-bitmask-tsp.md), penugasan di [16](16-bitmask-assignment.md), digit batas di [18](18-digit.md), subset sum nilai di [06](06-subset-sum.md) dan [23](23-bitset.md).

---

## FAQ singkat

**Q: Loop mask luar, bit dalam — boleh?**  
Boleh, asal **satu bit selesai** sebelum bit berikutnya. Yang dilarang: mencampur update dua bit di array yang sama tanpa lapisan.

**Q: Kenapa namanya zeta?**  
Di poset subset, transform `F(x) = Σ_{s ≤ x} a(s)` disebut zeta. Inversnya Mobius. Hafalkan kode dulu, nama belakangan.

**Q: Perlu FWHT?**  
XOR-convolution memakai FWHT, bukan SOS biasa. Jangan campur. Kalau soal AND/OR convolution, SOS + invers + perkalian per mask sering cukup.

**Q: `O(n 2^n)` vs `O(3^n)` di n = 12?**  
`3^12 ≈ 5e5`, `12*2^12 ≈ 5e4`. Keduanya hidup. Tetap tulis SOS agar kebiasaan untuk `n = 20`.

**Q: Bisa top-down?**  
Bisa memo `F(x)` = `a[x] + Σ F(x tanpa satu bit)`, tapi overlapping-nya jelek dan mudah dobel-hitung. Bottom-up per bit lebih bersih.

---

## Ringkasan dinding

```
F[x] = Σ_{s ⊆ x} a[s]          ← subset SOS
G[x] = Σ_{x ⊆ t} a[t]          ← superset SOS
invers: ganti += menjadi -=
waktu: O(n 2^n)
uji wajib: n=2  →  1 3 5 15
```
