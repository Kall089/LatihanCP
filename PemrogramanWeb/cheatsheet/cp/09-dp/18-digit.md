# 18 — Digit DP (Day 159)

[← SOS DP](17-sos.md) · [README](README.md) · [Tree DP →](19-tree.md)

> **Satu kalimat:** bangun bilangan dari kiri, bawa bendera **tight** (masih nempel batas) dan **leading zero**, lalu `f(R) - f(L-1)`.

Day ComprogLearning: **159**. File ini teori + kode modular. Jangan menyalin `latihan/` atau `solusi/`.

Tiga pertanyaan:

```
1. STATE     : sisa posisi + tight + lead + ringkasan syarat (sum / rem / last)
2. TRANSISI  : pilih digit 0..up, update tight/lead/syarat
3. BASIS     : posisi habis → 1 jika syarat terpenuhi, else 0
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Dua bendera](#dua-bendera)
- [Pola rentang](#pola-rentang)
- [Proses: jumlah digit = 4](#proses-jumlah-digit--4)
- [Proses: leading zero](#proses-leading-zero)
- [Sisa bagi](#sisa-bagi)
- [Digit berurutan](#digit-berurutan)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** `R` bisa `10^18`. Loop `for (x = L; x <= R; x++)` mustahil. Digit DP menghitung banyak (atau jumlah) bilangan `0 .. X` yang memenuhi syarat **lokal per digit**: jumlah digit, sisa bagi `m` kecil, tidak ada digit terlarang, tidak ada dua digit sama berurutan, digit naik, dan sejenisnya.

Tulis `X` sebagai string digit `bound[0..n-1]`, paling kiri = paling signifikan. Isi dari posisi 0 ke `n`. Di tiap posisi pilih digit `d`.

Tanpa batas, tiap posisi 0..9 — overcount sampai `10^n - 1`, termasuk yang lebih besar dari `X`. Bendera **tight** menandai "prefiks sejauh ini sama dengan `X`", jadi digit sekarang paling besar `bound[pos]`.

Tanpa leading zero, `007` dan `7` adalah dua jalur berbeda. Bendera **lead** menandai "belum ada digit non-nol". Nol depan biasanya **tidak** ikut jumlah digit, dan **tidak** memicu syarat "digit berurutan".

Jawaban rentang: `solve(R) - solve(L - 1)`, dengan `solve(-1) = 0`.

Analoginya: mengisi formulir nomor antrean dari kiri. Kalau belum menyentuh batas, bebas 0–9. Kalau masih sama dengan nomor terakhir yang diizinkan, digit berikutnya tidak boleh lebih besar.

---

## Kapan

**Kapan dipakai.**

| Gejala | Digit DP? |
|---|---|
| `L, R ≤ 10^18`, syarat pada digit | ya |
| hitung / jumlahkan bilangan dengan sifat digit | ya |
| `x ≡ 0 (mod m)` dan `m ≤ 100` plus syarat digit | ya, tambah dimensi `rem` |
| `R ≤ 1e6` dan syarat mudah di-loop | tidak perlu |
| syarat butuh **seluruh himpunan digit** tanpa ringkas | state meledak |
| program DP vs program | bukan digit; lihat [24](24-game.md) |

**Kapan tidak:** batas kecil; atau sifatnya pada faktor prima / gcd besar yang tidak bisa dilacak per digit; atau `m > 1e5` untuk sisa bagi (kali 18*10*m terlalu besar).

---

## STATE TRANSISI BASIS

Contoh kanonik: banyak bilangan `≤ X` yang jumlah digitnya tepat `target`.

**STATE:** `dp[pos][tight][lead][sum]` = banyak cara mengisi posisi `pos .. n-1` dengan:

- `tight` = 1 jika prefiks masih sama dengan `bound`,
- `lead` = 1 jika masih nol depan,
- `sum` = jumlah digit yang sudah "nyata" (bukan leading zero).

**TRANSISI:** `up = tight ? bound[pos]-'0' : 9`. Untuk `d = 0..up`:

```
nlead  = lead && (d == 0)
nsum   = sum + (nlead ? 0 : d)
ntight = tight && (d == up)
lanjut ke pos+1
```

**BASIS:** `pos == n`:

- jika masih `lead` (bilangan 0): 1 hanya jika `target == 0` dan 0 diizinkan,
- else: 1 jika `sum == target`.

Jawaban satu batas: `dfs(0, tight=1, lead=1, sum=0)`.

---

## Dua bendera

### tight

```
X = 13  → bound = "13"
pos 0: up = 1
  d = 0  → ntight = 0  (sudah lebih kecil, satuan bebas 0..9)
  d = 1  → ntight = 1  (masih nempel, satuan ≤ 3)
  d = 2  → terlarang
```

Jika lupa `tight`, kamu menghitung semua bilangan 2-digit 00..99, bukan 00..13.

### leading zero

```
Jalur 0,4 pada bound "13":
  pos0 d=0  lead tetap 1, sum tetap 0
  pos1 d=4  lead pecah, sum = 4
Bilangan yang terbentuk: 4, bukan 04.
Jumlah digit = 4, bukan 0+4 jika kamu salah menambahkan 0 depan.
```

Bilangan 0: seluruh digit 0, `lead` tetap 1 sampai akhir. Putuskan secara sadar apakah 0 dihitung.

---

## Pola rentang

```
count(L, R) = solve(R) - solve(L - 1)
solve(x)    = 0  jika x < 0
```

Kasus `L = 0`: `solve(R) - solve(-1) = solve(R)`.

Kasus `L = 1`: sering ingin mengecualikan 0.

Setiap kali `bound` berubah, **reset memo**. `memset(vis, 0)` atau stamp.

---

## Proses: jumlah digit = 4

Hitung banyak `x` di `[1, 13]` dengan jumlah digit = 4.

`solve(13)` untuk target 4, lalu kurang `solve(0)`.

Batas `"13"`:

```
pos=0 tight=1 lead=1 sum=0
  d=0: nlead=1 nsum=0 ntight=0 → pos1 bebas 0..9
  d=1: nlead=0 nsum=1 ntight=1 → pos1 d=0..3
```

Dari cabang `d=0` (bukan tight, masih lead):

```
pos1, pilih d=0..9
  d=0: lead tetap, sum 0  → akhir lead=1 → 0 (bukan target 4)
  d=1..9: lead pecah, sum=d → akhir sum=d
  yang match target 4: d=4  → bilangan 4
```

Dari cabang `d=1` (tight, lead pecah, sum=1):

```
pos1 d=0..3, nsum=1+d
  1+3=4 → d=3 → bilangan 13
```

Jadi `solve(13) = 2` jika 0 tidak dihitung (target 4 ≠ 0). Bilangan: **4** dan **13**.

`solve(3)` target 4 = 0. Rentang `[4, 13] = 2`.

Tabel lengkap `0..20`, target 1:

```
1, 10  → 2 bilangan di [1,20]
juga 100 tidak ada
```

---

## Proses: leading zero

Hitung banyak bilangan `≤ 10` (termasuk 0) — tanpa syarat, harus 11.

Kalau `lead` tidak ada dan setiap digit dijumlah sebagai "ada", `00`..`10` tercampur dengan 1-digit.

Simulasi tanpa syarat (`basis` selalu 1):

```
bound "10", dfs(pos,tight,lead)
akhir selalu 1
```

Jalur:

```
0,0 → 0
0,1 → 1
0,2 → 2
...
0,9 → 9
1,0 → 10
```

Itu 11 jalur. Tanpa `lead` kamu tidak salah **count semua bilangan**, tapi salah **syarat yang bergantung nilai digit**. Contoh: "jumlah digit genap" pada 10:

- benar: 1+0=1 ganjil, tidak dihitung,
- salah jika 0 depan dijumlah: `01` dianggap 0+1=1 (kebetulan sama), tapi `08` dianggap 0+8 vs 8.

Syarat "digit pertama = digit terakhir" juga rusak tanpa `lead`.

---

## Sisa bagi

**Teori:** tambah dimensi `rem` = nilai yang sudah dibentuk modulo `m`. Saat pilih `d` dan `lead` pecah / sudah pecah:

```
nrem = (rem * 10 + d) % m
```

Selama masih lead, nilai masih 0, `nrem = 0`.

**Kapan:** `x ≡ k (mod m)` plus syarat digit, `m ≤ 100` (kadang 200).

**STATE:** `dfs(pos, tight, lead, rem)`.

**TRANSISI:** digit `d = 0..up`, skip digit terlarang (kecuali lead + d=0).

**BASIS:** `pos == n` → `rem == 0` (atau `== k`). Bilangan 0: `0 % m == 0`, biasanya 1.

**Proses angka:** banyak genap `0..10` (mod 2 = 0) tanpa larangan digit.

```
0,2,4,6,8,10  → 6
```

Batas `"10"`:

```
cabang 0 + satuan 0..9: genap 0,2,4,6,8  → 5
cabang 1 + satuan 0 (tight): 10 ≡ 0      → 1
total 6
```

Dengan larangan digit 4: buang 4, sisa 0,2,6,8,10 → 5.

---

## Digit berurutan

Syarat "tidak ada dua digit sama berurutan".

**STATE:** tambah `last` = digit terakhir nyata, atau `-1` jika masih lead.

**TRANSISI:** jika `!lead && d == last` skip. `nlast = nlead ? -1 : d`.

**BASIS:** setiap bilangan lengkap sah (termasuk 0).

**Proses:** `X = 21`. Bilangan `0..21` yang punya dua digit sama berurutan: 11. Jadi yang sah = 22 - 1 = 21? Tunggu, 0..21 ada 22 bilangan, hanya 11 yang gagal → 21.

`X = 100`: gagal 11,22,...,99 (9 buah) plus tidak ada 000. Hati-hati 100 sendiri sah.

Jangan menghitung `11` dua kali lewat `01` + `1`.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string bound;
ll memo[20][2][2][200];
char vis[20][2][2][200];

ll dfsSum(int pos, int tight, int lead, int sum, int target) {
    if (pos == (int)bound.size()) {
        if (lead) return target == 0;
        return sum == target;
    }
    ll& res = memo[pos][tight][lead][sum];
    if (vis[pos][tight][lead][sum]) return res;
    vis[pos][tight][lead][sum] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        int nlead = lead && (d == 0);
        int nsum = sum + (nlead ? 0 : d);
        int ntight = tight && (d == up);
        res += dfsSum(pos + 1, ntight, nlead, nsum, target);
    }
    return res;
}

ll countSumEq(ll x, int target) {
    if (x < 0) return 0;
    bound = to_string(x);
    memset(vis, 0, sizeof(vis));
    return dfsSum(0, 1, 1, 0, target);
}

ll countSumEqRange(ll L, ll R, int target) {
    return countSumEq(R, target) - countSumEq(L - 1, target);
}

int MODM;
ll memoM[20][2][2][100];
char visM[20][2][2][100];

ll dfsMod(int pos, int tight, int lead, int rem) {
    if (pos == (int)bound.size()) return rem == 0;
    ll& res = memoM[pos][tight][lead][rem];
    if (visM[pos][tight][lead][rem]) return res;
    visM[pos][tight][lead][rem] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        int nlead = lead && (d == 0);
        int nrem = nlead ? 0 : (rem * 10 + d) % MODM;
        res += dfsMod(pos + 1, tight && (d == up), nlead, nrem);
    }
    return res;
}

ll countDivisible(ll x, int m) {
    if (x < 0) return 0;
    bound = to_string(x);
    MODM = m;
    memset(visM, 0, sizeof(visM));
    return dfsMod(0, 1, 1, 0);
}

ll countDivisibleRange(ll L, ll R, int m) {
    return countDivisible(R, m) - countDivisible(L - 1, m);
}

ll memoA[20][2][2][11];
char visA[20][2][2][11];

ll dfsNoAdj(int pos, int tight, int lead, int last) {
    if (pos == (int)bound.size()) return 1;
    ll& res = memoA[pos][tight][lead][last + 1];
    if (visA[pos][tight][lead][last + 1]) return res;
    visA[pos][tight][lead][last + 1] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        if (!lead && d == last) continue;
        int nlead = lead && (d == 0);
        int nlast = nlead ? -1 : d;
        res += dfsNoAdj(pos + 1, tight && (d == up), nlead, nlast);
    }
    return res;
}

ll countNoAdj(ll x) {
    if (x < 0) return 0;
    bound = to_string(x);
    memset(visA, 0, sizeof(visA));
    return dfsNoAdj(0, 1, 1, -1);
}

int main() {
    FASTIO;
    cout << countSumEqRange(1, 13, 4) << "\n";      // 2
    cout << countSumEqRange(1, 20, 1) << "\n";      // 2 : 1,10
    cout << countDivisibleRange(0, 10, 2) << "\n";  // 6
    cout << countNoAdj(21) - countNoAdj(0) + 1 << "\n";
    return 0;
}
```

Varian "jumlahkan nilai bilangan yang sah" (bukan hanya hitung):

**STATE:** sering dua memo: `cnt` dan `sum`, atau kembalikan `pair<ll,ll>`.

```cpp
struct Pair {
    ll cnt, sum;
};

Pair dfsVal(int pos, int tight, int lead, /* syarat */) {
    if (pos == (int)bound.size()) {
        if (lead) return {1, 0}; // bilangan 0
        return {1, 0};           // sum ditambah di transisi
    }
    // ...
    // saat pilih d dan !nlead:
    //   tempat = 10^(sisa-1)
    //   nsum = child.sum + d * tempat * child.cnt
}
```

Untuk kontes, lebih aman hitung `cnt` dulu, baru `sum` dengan rumus tempat. Jangan campur `int` untuk `sum` — jawaban bisa `≈ R * banyak ≈ 1e18 * 18`.

---

## Jebakan

1. **Lupa `f(R) - f(L-1)`.** Soal minta `[L, R]`, kamu hanya `solve(R)`.

2. **`L = 0` dan `solve(-1)`.** Wajib `if (x < 0) return 0`.

3. **Memo tidak di-reset** saat `bound` berganti. Gejala: `solve(13)` benar, `solve(3)` masih memakai memo 13.

4. **`tight` tidak di-update.** Semua posisi 0..9. Overcount besar.

5. **Leading zero ikut `sum` / `last`.** `07` dianggap dua digit 0 dan 7.

6. **`int` untuk jawaban.** Banyak bilangan `≤ 10^18` bisa `10^18 + 1`. Pakai `ll`.

7. **`rem * 10` overflow?** `rem < m`. Kalau `m` muat `int`, `rem * 10 + d` muat. Tetap rapi: `(rem * 10LL + d) % m`.

8. **Digit terlarang pada leading.** Melarang `d = 0` saat lead mematikan semua bilangan. Nol depan harus lolos.

9. **Panjang tidak sama.** `solve(999)` vs `solve(1000)` — `to_string` otomatis beda panjang. Jangan pad kiri sendiri kecuali kamu sadar `lead` menanganinya.

10. **Bottom-up urutan salah.** Top-down + memo lebih sulit salah. Jika bottom-up, isi dari `pos = n` mundur, loop semua `tight/lead/syarat`.

11. **`memset` pada array `ll` memo tanpa `vis`.** Nilai 0 bisa jawaban sah. Wajib `vis` atau sentinel.

---

## Kompleksitas

```
O( jumlah_posisi × 2 × 2 × |syarat| × 10 )
```

| Varian | |syarat| | kasar |
|---|---|---|
| jumlah digit ≤ 9*18 | 200 | `18*4*200*10 ≈ 1.4e5` |
| sisa `m ≤ 100` | 100 | `18*4*100*10 ≈ 7e4` |
| last digit | 11 | sangat kecil |
| sum + rem | 200*100 | `18*4*2e4*10 ≈ 1.4e7` masih hidup |

Memori: sama dengan jumlah state. `pos = 19` untuk `10^18`.

Kalau `m = 1e5`, state `19*2*2*1e5` ≈ 8e6, kali 10 transisi = 8e7 — pas. Jangan tambah dimensi lagi.

---

## Tabel uji

| Soal | L R / X | Syarat | Jawaban |
|---|---|---|---|
| jumlah digit | `[1,13]` | sum = 4 | 2 (`4,13`) |
| jumlah digit | `[1,20]` | sum = 1 | 2 (`1,10`) |
| jumlah digit | `[1,9]` | sum = 10 | 0 |
| habis dibagi 2 | `[0,10]` | rem 0 | 6 |
| habis dibagi 2 | `[1,10]` | rem 0 | 5 |
| tanpa digit sama berurutan | `X=21` termasuk 0 | no-adj | 21 |
| semua bilangan | `[0,10]` | — | 11 |
| `solve(-1)` | — | apa pun | 0 |

Uji brute untuk `R ≤ 10000`:

```cpp
ll bruteSumEq(ll L, ll R, int target) {
    ll ans = 0;
    for (ll x = L; x <= R; x++) {
        ll y = x, s = 0;
        if (y == 0) s = 0;
        while (y) {
            s += y % 10;
            y /= 10;
        }
        if (s == target) ans++;
    }
    return ans;
}
```

Samakan `countSumEqRange` vs `bruteSumEq` pada banyak `(L,R,target)` acak kecil.

---

## Checklist

1. `solve(x)` untuk `x < 0` mengembalikan 0.
2. Setiap ganti `bound` → `memset(vis)`.
3. `tight` start 1, `lead` start 1.
4. `nlead` dihitung sebelum menambah `sum`.
5. Jawaban `ll`.
6. Dimensi syarat minimal: jangan simpan seluruh prefiks.
7. Bandingkan dengan brute di `R ≤ 1e4`.
8. Baca soal: 0 termasuk atau tidak.

Lanjut pohon: [19-tree](19-tree.md). Kalau syaratnya himpunan mask, kembali ke [15](15-bitmask-tsp.md) / [17](17-sos.md).

---

## Bottom-up singkat

Kalau rekursi dilarang / ingin iteratif:

```cpp
// dp[pos][tight][lead][sum] diisi dari belakang
// pos = n : basis
// pos = n-1 .. 0
```

Ukuran sama. Indeks `pos` adalah "berapa digit sudah dipasang dari kiri" atau "sisa" — pilih satu, jangan campur.

Template iteratif jumlah digit (termasuk 0 jika target 0):

```cpp
ll countSumEqIter(ll x, int target) {
    if (x < 0) return 0;
    string s = to_string(x);
    int n = (int)s.size();
    static ll dp[20][2][2][200];
    memset(dp, 0, sizeof(dp));
    dp[n][0][0][target] = 1;
    dp[n][0][1][0] = 1;
    dp[n][1][0][target] = 1;
    dp[n][1][1][0] = 1;
    for (int pos = n - 1; pos >= 0; pos--)
        for (int tight = 0; tight <= 1; tight++)
            for (int lead = 0; lead <= 1; lead++)
                for (int sum = 0; sum <= target; sum++) {
                    int up = tight ? s[pos] - '0' : 9;
                    ll ways = 0;
                    for (int d = 0; d <= up; d++) {
                        int nlead = lead && (d == 0);
                        int nsum = sum + (nlead ? 0 : d);
                        if (nsum > target) continue;
                        int ntight = tight && (d == up);
                        ways += dp[pos + 1][ntight][nlead][nsum];
                    }
                    dp[pos][tight][lead][sum] = ways;
                }
    return dp[0][1][1][0];
}
```

Perhatikan: di versi mundur ini `sum` berarti "jumlah yang sudah dikumpulkan **sebelum** `pos`" — sama seperti top-down. Jangan membalik arti `sum` jadi "sisa yang dibutuhkan" tanpa mengubah basis.

---

## Desain syarat: apa yang masuk state?

Masukkan ke state **hanya** yang masa depan butuhkan.

| Syarat | Dimensi |
|---|---|
| jumlah digit `= k` | `sum` atau `sisa` |
| `x % m == 0` | `rem` |
| tidak sama dengan digit kiri | `last` |
| digit monoton naik ketat | `last` + lead |
| ada digit 7 atau tidak | bit 0/1 |
| selisih genap/ganjil posisi | dua akumulator kecil |
| palindrom | perlu mencocokkan kiri-kanan — sering bukan digit DP biasa |

Jangan masukkan nilai numerik penuh. Itu `10^18` state.

---

## Ringkasan dinding

```
solve(R) - solve(L-1)
dfs(pos, tight, lead, syarat)
up = tight ? bound[pos] : 9
nlead = lead && d==0
ntight = tight && d==up
memo reset setiap bound berubah
```
