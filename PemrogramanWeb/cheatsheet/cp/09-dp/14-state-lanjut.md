# 14 — State lanjut: dimensi extra

[← 13-memori](13-memori.md) · [README](README.md) · [15-bitmask-tsp →](15-bitmask-tsp.md)

Day **155**. File 01–13 cukup jika keputusan terakhir hanya "ambil atau tidak" pada prefiks. Begitu soal menyebut **warna terakhir**, **barang sebelumnya**, atau **genap/ganjil**, `dp[i]` kehilangan informasi. Tambah dimensi yang **tepat satu** untuk fakta yang masa depan butuh.

> **Satu kalimat:** state harus Markov — masa depan hanya bergantung pada yang kamu simpan; kalau transisi masih "tergantung sejarah tersembunyi", dimensi kurang.

Ini bukan bitmask (itu [15](15-bitmask-tsp.md)). Di sini domain extra kecil: warna `≤ 10`, flag 0/1, sisa bagi `m ≤ 100`, last-taken 0/1.

## Daftar isi

- [Cara memilih state](#cara-memilih-state)
- [Uji Markov](#uji-markov)
- [Last-color](#last-color)
- [Last-taken](#last-taken)
- [Paritas](#paritas)
- [Sisa bagi kecil](#sisa-bagi-kecil)
- [Dua flag sekaligus](#dua-flag-sekaligus)
- [Dimensi yang salah](#dimensi-yang-salah)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Cara memilih state

**Teori:** Tulis keputusan satu elemen (rumah `i`, hari `i`, item `i`). Tulis **larangan** yang merujuk ke masa lalu: "tidak sama dengan warna rumah `i-1`", "tidak boleh dua ambil berurutan", "jumlah yang diambil genap". Setiap rujukan ke masa lalu yang tidak tercermin di indeks `i` butuh slot di tuple state.

Empat uji (lanjutan Day 142):

1. **Kalimat:** `dp[i][c]` = "biaya min mengecat rumah `0..i`, rumah `i` berwarna `c`".
2. **Cukup:** dari `(i,c)` kamu bisa memutuskan rumah `i+1` tanpa membuka warna `i-1`.
3. **Setara:** dua cara mencapai `(i,c)` dengan biaya beda — yang lebih buruk boleh dibuang.
4. **Muat:** `n * |warna| * |flag| ≤ 1e7` nyaman, `1e8` ketat.

Analoginya packing koper: setiap atribut yang petugas bandara (transisi) akan tanya harus masuk koper (state). Atribut yang tidak pernah ditanya jangan dimasukkan — pemborosan.

**Kapan:** 1D WA pada contoh kecil yang jelas butuh sejarah. **Tidak:** greedy terbukti; atau sejarah adalah himpunan `n≤20` (bitmask).

**STATE:** tuple `(posisi, ringkasan sejarah)`. Ringkasan = last-color / last-taken / parity / sisa / sudah-pakai-joker, dll.

**TRANSISI:** pilih keputusan di posisi sekarang yang sah terhadap ringkasan, hasilkan ringkasan baru.

**BASIS:** posisi -1 atau 0 dengan ringkasan netral (belum ada warna, belum ambil, paritas 0).

**Proses (table):** soal "cat 3 rumah, 2 warna, tetangga beda".

| kandidat state | cukup? | ukuran |
|---|---|---|
| `dp[i]` min biaya sampai i | tidak, warna i tidak diketahui | n |
| `dp[i][c]` rumah i warna c | ya | n·2 |
| `dp[i][c][c_prev]` | berlebih | n·4 |
| `dp[subset]` rumah yang dicat | salah soal (semua harus dicat) | 2^n |

**Kode modular:** kerangka komentar, bukan rumus ajaib.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// 1. tulis kalimat dp[i][extra]
// 2. tulis extra' dari keputusan
// 3. baru buka array
int perkiraanState(int n, int extra) {
    return n * extra;
}

int main() {
    FASTIO;
    cout << perkiraanState(1e5, 3) << '\n'; // 3e5 aman
    return 0;
}
```

**Jebakan:** menambah dimensi "supaya terasa DP". Menyalin `dp[i-1]` tanpa mengubah extra. `int` untuk `n=1e5 * 100` masih oke; kalikan lagi `m=1000` sudah MLE.

**Kompleksitas:** waktu ≈ `|state| × |keputusan|`.

---

## Uji Markov

**Teori:** Properti Markov: `P(masa depan | seluruh sejarah) = P(masa depan | state sekarang)`. Dalam DP: dua jalur ke state yang sama harus punya himpunan kelanjutan yang sama. Jika jalur A tidak boleh memilih X tetapi jalur B boleh, padahal keduanya di `dp[i]`, state kurang.

**Kapan:** debug WA "contoh kedua beda padahal `dp[n]` sama rumusnya". **Tidak:** bug off-by-one biasa (itu indeks, bukan Markov).

**STATE:** kandidat yang sedang diuji.

**TRANSISI:** daftarkan semua keputusan legal dari state itu.

**BASIS:** dua prefiks berbeda yang landas di state sama.

**Proses (table):** house robber tanpa last-taken, hanya `dp[i]` = max sampai i (ini **sudah** Markov karena keputusan "ambil i" hanya butuh `dp[i-2]`, bukan daftar rumah). Lawan: "tidak boleh 3 rumah berurutan" — `dp[i]` tidak cukup: kamu perlu tahu apakah `i-1` dan `i-2` sama-sama diambil.

| soal | ringkasan wajib |
|---|---|
| tidak 2 berurutan | last-taken 0/1, atau pecah `dp` skip/ambil |
| tidak 3 berurutan | panjang streak ambil 0,1,2 |
| tetangga beda warna | last-color |
| jumlah genap | parity |
| jumlah % k | sisa k |
| sudah pernah ambil jenis A | flag 0/1 |

**Kode modular:**

```cpp
bool markovCukup(int butuhStreak, int simpanStreak) {
    return simpanStreak >= butuhStreak;
}
```

**Jebakan:** "tidak 3 berurutan" disimpan hanya 0/1 last-taken — masih boleh `ambil,ambil,ambil` jika last=1 lalu... wait, jika last-taken hanya 1 bit, transisi `ambil` dari `last=1` harus dilarang, itu "tidak 2 berurutan". Untuk 3, dari streak=2 dilarang ambil, dari streak=1 boleh.

**Kompleksitas:** uji manual O(contoh).

---

## Last-color

**Teori:** Paint house / pewarnaan barisan: rumah `i` berwarna `c` dengan biaya `cost[i][c]`, tetangga tidak boleh sama. `dp[i][c] = cost[i][c] + min_{d≠c} dp[i-1][d]`. Analoginya mengecat pagar: yang penting warna papan terakhir, bukan seluruh pola.

Jika `k` warna dan `min` naif, transisi `O(k)` → total `O(n k²)`. Bisa `O(nk)`: simpan dua minimum baris sebelumnya (terkecil dan kedua, plus argmin). Jika `c != argmin` pakai min1, else min2.

**Kapan:** "adjacent different color", AtCoder DP-C Vacation (3 kegiatan), paint house. **Tidak:** graf pewarnaan umum (NP / bitmask).

**STATE:** `dp[i][c]` biaya / nilai optimal untuk prefiks `0..i` dengan posisi `i` memakai warna/kegiatan `c`.

**TRANSISI:** `dp[i][c] = cost[i][c] + min(dp[i-1][d] untuk d≠c)` (min biaya) atau `a[i][c] + max(dp[i-1][d], d≠c)` (max poin).

**BASIS:** `dp[0][c] = cost[0][c]`.

**Proses (table):** Vacation 3 hari, poin

```
hari0: 10 40 70
hari1: 20 50 80
hari2: 30 60 90
```

`dp` max, kegiatan 0,1,2 tidak boleh sama berurutan.

| i \\ c | 0 | 1 | 2 |
|---|---|---|---|
| 0 | 10 | 40 | 70 |
| 1 | 20+70=90 | 50+70=120 | 80+40=120 |
| 2 | 30+120=150 | 60+90=150 | 90+120=**210** |

Jawaban 210 (hari0 kegiatan 1? 40 → hari1 kegiatan 2 =120 → hari2 kegiatan 0 =150, atau 70→50? 70+50=120 hari1 c1, +90=210 hari2 c2: kegiatan 2,1,2). 70+50+90=210.

Cat 3 rumah, biaya

```
7 5 10
3 6 1
8 4 2
```

min, 3 warna:

| i \\ c | 0 | 1 | 2 |
|---|---|---|---|
| 0 | 7 | 5 | 10 |
| 1 | 3+5=8 | 6+7=13 | 1+5=6 |
| 2 | 8+6=14 | 4+6=10 | 2+8=10 |

Jawaban 10.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll paintMin(const vector<vector<ll>>& cost) {
    int n = (int)cost.size(), k = (int)cost[0].size();
    vector<ll> dp = cost[0];
    for (int i = 1; i < n; i++) {
        vector<ll> nxt(k, INF);
        for (int c = 0; c < k; c++)
            for (int d = 0; d < k; d++)
                if (c != d) nxt[c] = min(nxt[c], dp[d] + cost[i][c]);
        dp.swap(nxt);
    }
    return *min_element(dp.begin(), dp.end());
}

ll vacationMax(const vector<array<ll, 3>>& a) {
    ll x = 0, y = 0, z = 0; // extra = kegiatan terakhir, digulung
    for (auto [A, B, C] : a) {
        ll nx = A + max(y, z);
        ll ny = B + max(x, z);
        ll nz = C + max(x, y);
        x = nx;
        y = ny;
        z = nz;
    }
    return max({x, y, z});
}

int main() {
    FASTIO;
    vector<array<ll, 3>> a = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    cout << vacationMax(a) << '\n'; // 210
    vector<vector<ll>> cost = {{7, 5, 10}, {3, 6, 1}, {8, 4, 2}};
    cout << paintMin(cost) << '\n'; // 10
    return 0;
}
```

**Jebakan:** `c==d` diizinkan. Jawaban `dp[n-1][0]` bukan `min`/`max` seluruh warna. `k=1`, `n>1` tidak mungkin — handle. Menggulung satu array tanpa `nxt` menimpa warna yang masih dibaca.

**Kompleksitas:** `O(n k²)` atau `O(nk)` dengan dua minimum. Memori `O(k)`.

---

## Last-taken

**Teori:** Keputusan biner ambil/skip, plus larangan "jika tadi ambil, sekarang jangan". House robber adalah kasus ini; `dp[i][0/1]` lebih eksplisit daripada rumus `i-2`. Berguna saat larangan lebih kaya: "jika ambil, bayar denda jika last-taken", atau "ambil jenis A hanya jika last bukan A".

**Kapan:** barisan, tidak bersebelahan, stock cooldown (last = jual/tahan/beli). **Tidak:** subset bebas (knapsack tanpa urutan).

**STATE:** `dp[i][t]` optimal untuk prefiks `0..i` dengan flag `t` = apakah posisi `i` diambil.

**TRANSISI:**

```
dp[i][0] = max(dp[i-1][0], dp[i-1][1])   // skip i
dp[i][1] = dp[i-1][0] + a[i]             // ambil i hanya dari skip
```

**BASIS:** `dp[0][0] = 0`, `dp[0][1] = a[0]` (atau `-INF` jika wajib skip awal).

**Proses (table):** `[2, 7, 9, 3, 1]`.

| i | a | dp[i][0] | dp[i][1] |
|---|---|---|---|
| 0 | 2 | 0 | 2 |
| 1 | 7 | max(0,2)=2 | 0+7=7 |
| 2 | 9 | max(2,7)=7 | 2+9=11 |
| 3 | 3 | 11 | 7+3=10 |
| 4 | 1 | 11 | 11+1=12 |

Jawaban `max(11,12)=12`. Sama dengan [12](12-rekonstruksi.md), tetapi extra-nya kelihatan.

Cooldown 1 hari (tidak boleh ambil sehari setelah ambil — sudah sama). Cooldown 2: tambah flag atau pecah 3 status: skip, ambil, istirahat.

**Kode modular:**

```cpp
ll robberLastTaken(const vector<ll>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    ll skip = 0, take = a[0];
    for (int i = 1; i < n; i++) {
        ll nskip = max(skip, take);
        ll ntake = skip + a[i];
        skip = nskip;
        take = ntake;
    }
    return max(skip, take);
}

// tidak boleh 3 ambil berurutan: extra = streak 0..2
ll maxNoThree(const vector<ll>& a) {
    ll s0 = 0, s1 = LLONG_MIN / 4, s2 = LLONG_MIN / 4;
    s0 = 0;
    if (!a.empty()) s1 = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        ll n0 = max({s0, s1, s2}); // skip → streak 0
        ll n1 = s0 + a[i];         // ambil setelah skip
        ll n2 = s1 + a[i];         // ambil setelah tepat 1
        s0 = n0;
        s1 = n1;
        s2 = n2;
    }
    return max({s0, s1, s2});
}

int main() {
    FASTIO;
    cout << robberLastTaken({2, 7, 9, 3, 1}) << '\n';
    cout << maxNoThree({2, 7, 9, 3, 1}) << '\n'; // boleh 7+9+1? 7,9 berurutan 2, lalu skip 3, ambil 1 → 17? 
    return 0;
}
```

`maxNoThree([2,7,9,3,1])`: boleh `2,7,3,1`? 7 dan 9 berurutan ok (2), 9 dan 3 ketiga — jika ambil 2,7,9 itu 3 berurutan, dilarang. `7+9+1=17` (streak 2 lalu skip 3 ambil 1). `2+9+1=12`. Jawaban 17.

**Jebakan:** `dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + a[i]` — itu mengizinkan dua ambil. Streak 3 disimpan 1 bit.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori jika digulung.

---

## Paritas

**Teori:** Yang dibutuhkan masa depan hanya "jumlah pengambilan genap atau ganjil", bukan jumlahnya. Extra 1 bit. Analoginya saklar lampu: setiap ambil membalik saklar. Jawaban sering `dp[n][0]` (genap) atau `max(dp[n][0], dp[n][1])` tergantung soal.

Pola: `dp[i][p]` = cara / nilai memakai elemen `0..i-1` dengan paritas `p`.

```
skip:  dp[i+1][p] += dp[i][p]
ambil: dp[i+1][p^1] += dp[i][p]
```

**Kapan:** "even number of items", "xor bit terakhir", "beda genap". **Tidak:** butuh jumlah persis `k` dengan `k` besar — itu dimensi `k` (knapsack) atau MITM.

**STATE:** `dp[i][0/1]` atau `dp[pos][parity]`.

**TRANSISI:** XOR 1 saat keputusan membalik paritas.

**BASIS:** `dp[0][0] = 1` (nol elemen, genap, satu cara) atau `0` nilai.

**Proses (table):** hitung subset dengan **jumlah elemen genap**, `a` panjang 3 (nilai tidak penting).

| i (sudah proses) | cara genap | cara ganjil |
|---|---|---|
| 0 | 1 | 0 |
| 1 | 1 (skip) | 1 (ambil) |
| 2 | 2 | 2 |
| 3 | 4 | 4 |

Total 8 subset, setengah genap (termasuk kosong). `2^{n-1} = 4` genap. Ya.

Nilai max dengan **jumlah item genap**: `a=[5, 4, 3]`.

| item | dp genap | dp ganjil |
|---|---|---|
| awal | 0 | -INF |
| +5 | 0 | 5 |
| +4 | max(0, 5+4)=9 | max(5, 0+4)=5 |
| +3 | max(9, 5+3)=9 | max(5, 9+3)=12 |

`dp genap akhir = 9` (`5+4`). Ganjil 12 (`5+4+3`) tidak dipakai jika soal minta genap.

**Kode modular:**

```cpp
ll countEvenSubsets(int n, ll MOD) {
    ll even = 1, odd = 0;
    for (int i = 0; i < n; i++) {
        ll ne = (even + odd) % MOD;
        ll no = (even + odd) % MOD;
        even = ne;
        odd = no;
    }
    return even;
}

ll maxEvenCount(const vector<ll>& a) {
    const ll NEG = LLONG_MIN / 4;
    ll even = 0, odd = NEG;
    for (ll x : a) {
        ll ne = max(even, (odd == NEG ? NEG : odd + x));
        ll no = max(odd, even + x);
        even = ne;
        odd = no;
    }
    return even;
}

int main() {
    FASTIO;
    cout << countEvenSubsets(3, 1000000007LL) << '\n'; // 4
    cout << maxEvenCount({5, 4, 3}) << '\n';           // 9
    return 0;
}
```

**Jebakan:** basis `even=0` untuk **cara** (harusnya 1). `-INF+x` overflow. Mencampur paritas jumlah elemen dengan paritas **nilai** (`x&1`) — itu extra berbeda: `p ^ (x&1)`.

**Kompleksitas:** `O(n)`.

---

## Sisa bagi kecil

**Teori:** Paritas adalah sisa 2. Umum: `dp[i][r]` = cara agar jumlah `≡ r (mod m)`. Transisi `r_baru = (r + a[i]) % m`. Extra berukuran `m`. Digit DP juga begini ([18-digit](18-digit.md)); di sini array 1D biasa.

**Kapan:** `m ≤ 200`, "habis dibagi m", "sisa k". **Tidak:** `m = 1e9` tanpa sifat lain.

**STATE:** `dp[r]` setelah memproses prefiks item (boleh digulung dengan `nxt`).

**TRANSISI:** skip tetap `r`; ambil ke `(r+a[i])%m`.

**BASIS:** `dp[0] = 1` (cara) atau `dp[0]=0` nilai dengan 0 item.

**Proses (table):** `a=[2, 3, 5]`, `m=5`, banyak subset jumlah ≡ 0 (termasuk kosong).

| setelah | r0 | r1 | r2 | r3 | r4 |
|---|---|---|---|---|---|
| ∅ | 1 | 0 | 0 | 0 | 0 |
| +2 | 1 | 0 | 1 | 0 | 0 |
| +3 | 1 | 0 | 1 | 1 | 0 | 
| +5 | 2 | 0 | 1 | 1 | 0 |

Tunggu +5: 5≡0, setiap ember dobel. `r0: 1+1=2`. Subset ≡0: `{}`, `{2,3}`, `{5}`, `{2,3,5}` = 4? Saya salah hitung.

Setelah +3:
- skip: (1,0,1,0,0)
- ambil +3: dari r0→r3, r2→r0. Jadi r0: 1 (skip) + 1 (dari r2) = 2, r2: 1, r3: 1. Tabel saya salah.

Benar setelah +3: `r0=2` (`{}`, `{2,3}`), `r2=1` (`{2}`), `r3=1` (`{3}`).

+5 (≡0): semua r bertambah dirinya sendiri → kali 2: `r0=4`. Ya 4 subset.

**Kode modular:**

```cpp
ll subsetMod(const vector<int>& a, int m, int target, ll MOD) {
    vector<ll> dp(m, 0), nxt;
    dp[0] = 1;
    for (int x : a) {
        nxt = dp;
        for (int r = 0; r < m; r++)
            if (dp[r]) nxt[(r + (x % m) + m) % m] = (nxt[(r + (x % m) + m) % m] + dp[r]) % MOD;
        dp.swap(nxt);
    }
    return dp[target];
}
```

**Jebakan:** `x` negatif, `%` C++. In-place tanpa `nxt` menular dalam satu barang (0-1 jadi unbounded). Lupa `x%m`.

**Kompleksitas:** `O(n m)`.

---

## Dua flag sekaligus

**Teori:** Kadang last-color **dan** parity. Kali kan domain: `dp[i][c][p]`. Tetap tulis kalimat. Jika flag independen, jangan gabung jadi bitmask kecuali `n` flag (itu file 15).

Contoh: cat rumah, tetangga beda, **jumlah rumah warna 0 genap**. Extra `c` dan `p`.

**Kapan:** dua syarat lokal. **Tidak:** 10 syarat 0/1 pada 10 jenis yang bisa semua aktif — `2^10` = bitmask item.

**STATE:** `dp[i][c][p]`.

**TRANSISI:** pilih `c' != c`, `p' = p ^ (c'==0)`.

**BASIS:** rumah 0, tiap warna, paritas sesuai warna itu.

**Proses (table):** 2 rumah, 2 warna, biaya 1 semua, minta akhir `p=0`. Beberapa pola valid. Latihan: hitung dengan kode, jangan tebak.

| i | c | p | arti |
|---|---|---|---|
| 0 | 0 | 1 | satu rumah warna 0, ganjil |
| 0 | 1 | 0 | satu rumah warna 1, nol warna 0 |

**Kode modular:**

```cpp
ll paintParity(const vector<vector<ll>>& cost) {
    int n = (int)cost.size(), k = (int)cost[0].size();
    const ll INF = 4e18;
    vector<vector<ll>> dp(k, vector<ll>(2, INF));
    for (int c = 0; c < k; c++) dp[c][c == 0] = cost[0][c];
    for (int i = 1; i < n; i++) {
        vector<vector<ll>> nxt(k, vector<ll>(2, INF));
        for (int c = 0; c < k; c++)
            for (int p = 0; p < 2; p++)
                if (dp[c][p] < INF)
                    for (int d = 0; d < k; d++)
                        if (d != c) {
                            int np = p ^ (d == 0);
                            nxt[d][np] = min(nxt[d][np], dp[c][p] + cost[i][d]);
                        }
        dp.swap(nxt);
    }
    ll ans = INF;
    for (int c = 0; c < k; c++) ans = min(ans, dp[c][0]);
    return ans;
}
```

**Jebakan:** `p` di-update dengan `c` lama. Jawaban min semua `c` pada `p` yang diminta.

**Kompleksitas:** `O(n k² · 2)`.

---

## Dimensi yang salah

**Teori:** Kesalahan desain lebih mahal daripada bug loop. Tiga pola salah: (1) extra terlalu kasar, (2) extra menyimpan seluruh vektor sejarah, (3) extra yang bisa diturunkan dari yang lain.

`dp[i][last][second_last]` untuk "tetangga beda" — `second_last` tidak pernah dibaca. `dp[i][mask_10_bit]` untuk 10 rumah — `n=10` kebetulan hidup, `n=40` mati; padahal last-color O(n).

**Kapan:** review state sebelum coding 1 jam. **Tidak:** menambah dimensi saat WA tanpa contoh penjelas.

**STATE:** bandingkan dua kandidat di kertas.

**TRANSISI:** lihat variabel yang benar-benar dibaca.

**BASIS:** sama.

**Proses (table):**

| gejala WA / TLE | extra kurang / lebih | perbaiki |
|---|---|---|
| dua contoh sama `dp[n]` beda legal | kurang | tambah last / parity |
| TLE `n=1e5`, `k=100` `O(nk²)` | mungkin ok 1e9? 1e9 TLE | dua min O(nk) |
| MLE `dp[n][n][n]` | 3 indeks item | biasanya salah soal |
| `dp[i][sum]` sum 1e9 | terlalu halus | modulus atau greedy |
| bitmask n=30 | domain himpunan | MITM / greedy |

**Kode modular:** tidak ada; ini filter desain.

**Jebakan:** "saya punya 3 loop jadi 3 dimensi". Loop `k` di range DP bukan dimensi extra, itu transisi.

**Kompleksitas:** desain O(waktu kontes). Eksekusi mengikuti tabel.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll paintMin(const vector<vector<ll>>& cost);
ll vacationMax(const vector<array<ll, 3>>& a);
ll robberLastTaken(const vector<ll>& a);
ll maxNoThree(const vector<ll>& a);
ll maxEvenCount(const vector<ll>& a);
ll subsetMod(const vector<int>& a, int m, int target, ll MOD);

int main() {
    FASTIO;
    cout << robberLastTaken({2, 1, 1, 2}) << '\n';
    cout << maxEvenCount({5, 4, 3}) << '\n';
    return 0;
}
```

Checklist sebelum array 3D:

```
1. Kalimat lengkap setiap indeks
2. Extra mana yang transisi baca?
3. |state| * keputusan <= 1e8
4. Bisa digulung?
5. Bukan bitmask terselubung?
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| cat tetangga sama | lupa `c!=d` | filter |
| vacation 180 bukan 210 | `max` termasuk kegiatan sama | max dua lainnya |
| robber 2 ambil berurutan | `take` dari `take` | hanya dari `skip` |
| 3 berurutan lolos | extra 1 bit | streak 0..2 |
| even count 0 | basis cara = 0 | `dp[0]=1` |
| mod WA | in-place 0-1 | array `nxt` |
| TLE nk² | k=400 | dua minimum |
| MLE 3D n=2000 | extra tidak perlu | uji Markov |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `vacationMax` | 10/40/70, 20/50/80, 30/60/90 | 210 |
| `paintMin` | [[7,5,10],[3,6,1],[8,4,2]] | 10 |
| `robberLastTaken` | 2,7,9,3,1 | 12 |
| `robberLastTaken` | 2,1,1,2 | 4 |
| `maxNoThree` | 2,7,9,3,1 | 17 |
| `countEvenSubsets` | n=3 | 4 |
| `maxEvenCount` | 5,4,3 | 9 |
| `subsetMod` | [2,3,5] m=5 target 0 | 4 |

Kalau extra sudah berupa **himpunan** kota atau tugas, berhenti menambah flag 0/1 satu-satu. Itu bitmask: [15-bitmask-tsp](15-bitmask-tsp.md).
