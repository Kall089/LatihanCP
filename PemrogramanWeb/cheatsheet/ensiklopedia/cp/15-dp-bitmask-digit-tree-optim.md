# 15 — DP: bitmask, digit, pohon, optimasi

[← String dan grid](14-dp-string-grid-range.md) · [README](README.md) · [Lanjut segtree →](16-segtree-bit-sparse-mo.md)

Folder 09 Day **155–168**, plus **244 / 248** (CHT, Knuth). Latihan harian di `ComProgLearning/CP` folder Day terkait. File ini memberi **ide + kode modular** untuk pola yang paling sering muncul; CHT punya satu implementasi sederhana yang bisa dikompilasi.

Tiga pertanyaan tetap: **STATE** kalimat lengkap, **TRANSISI**, **BASIS**.

Bitmask: himpunan = bilangan `0 .. 2^n-1`. Bit `i` nyala = elemen `i` sudah dipilih. `n ≤ 20` untuk `O(2^n n^2)`.

## Daftar isi

- [Operasi bitmask](#operasi-bitmask)
- [TSP bitmask](#tsp-bitmask)
- [Assignment bitmask](#assignment-bitmask)
- [Hamilton path dan varian](#hamilton-path-dan-varian)
- [SOS DP](#sos-dp)
- [Digit DP](#digit-dp)
- [Tree DP](#tree-dp)
- [Knapsack pada pohon](#knapsack-pada-pohon)
- [Rerooting](#rerooting)
- [CHT sederhana](#cht-sederhana)
- [Knuth optimization](#knuth-optimization)
- [D&C DP ide](#dc-dp-ide)
- [Pola lain menengah](#pola-lain-menengah)
- [Template gabungan](#template-gabungan)
- [Peta jebakan file ini](#peta-jebakan-file-ini)
- [Digit DP sisa bagi](#digit-dp-sisa-bagi)
- [Matching pada pohon](#matching-pada-pohon)
- [CHT jabarkan kuadrat](#cht-jabarkan-kuadrat)

---

## Operasi bitmask

**Teori:** Subset berukuran `n` ada `2^n` buah. Integer 32/64 bit menyimpan keanggotaan. Analoginya saklar lampu: 1 = nyala = sudah dikunjungi.

**Kapan:** `n ≤ 20` (kadang 23 dengan `O(2^n n)`). **Tidak:** `n = 30` tanpa MITM / SOS khusus.

**STATE:** tidak ada DP di sini; ini kamus operasi.

**TRANSISI / BASIS:** tidak berlaku.

**Proses angka:** `n = 4`, mask `10` = `1010_2` = elemen 1 dan 3.

```
nyalakan i     mask | (1 << i)
matikan i      mask & ~(1 << i)
cek i          mask >> i & 1
toggle i       mask ^ (1 << i)
subset T ⊆ S   for (int t = s; ; t = (t - 1) & s)
jumlah bit     __builtin_popcount(mask)
bit terendah   mask & -mask
```

Enumerate subset of `s = 13` (`1101`): 13, 12, 9, 8, 5, 4, 1, 0.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int on(int mask, int i) { return mask | (1 << i); }
int off(int mask, int i) { return mask & ~(1 << i); }
int has(int mask, int i) { return mask >> i & 1; }

vector<int> subsetsOf(int s) {
    vector<int> res;
    for (int t = s; ; t = (t - 1) & s) {
        res.push_back(t);
        if (t == 0) break;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int t : subsetsOf(13)) cout << t << " ";
    cout << "\n" << __builtin_popcount(13) << "\n";
    return 0;
}
```

**Jebakan:** `1 << 31` overflow `int` bertanda. Pakai `1LL << i` untuk `i ≥ 31`. Loop subset tanpa `if (t==0) break` infinite.

**Kompleksitas:** operasi O(1). Enumerate subset `O(2^{|s|})`. Semua mask `O(2^n)`.

---

## TSP bitmask

**Teori:** Kelilingi `n` kota, tiap kota sekali, kembali ke awal, biaya minimum. Brute `n!` mati di `n = 12`. Held-Karp: state = himpunan yang sudah dikunjungi + kota sekarang. Transisi menyalakan satu bit baru. Karena bit hanya bertambah, loop `mask` menaik otomatis topologis.

**Kapan:** `n ≤ 16..20`, graf lengkap atau padat. **Tidak:** `n = 100` — itu heuristik / ILP, bukan bitmask. Pohon: tree DP.

**STATE:** `dp[mask][u]` adalah biaya minimum untuk mengunjungi **tepat** himpunan kota `mask` dan **saat ini berada di kota `u`**. Bit `u` wajib nyala di `mask`.

**TRANSISI:** `dp[mask | (1<<v)][v] = min(dp[mask][u] + w[u][v])` untuk `v` belum masuk `mask`.

**BASIS:** `dp[1<<s][s] = 0` jika mulai di `s`. Lainnya `INF`. Tutup siklus: `min_u dp[(1<<n)-1][u] + w[u][s]`.

**Proses angka:** 4 kota, mulai 0. Bobot (tak berarah):

```
    0   1   2   3
0   0   10  15  20
1   10  0   35  25
2   15  35  0   30
3   20  25  30  0
```

```
dp[0001][0] = 0
+kota1: dp[0011][1] = 10
+kota2: dp[0101][2] = 15
+kota3: dp[1001][3] = 20

mask 0111 = {0,1,2}:
  ke 2 dari 1: 10+35=45
  ke 1 dari 2: 15+35=50
  ...
full 1111, kembali ke 0:
  klasik 0-1-3-2-0 = 10+25+30+15 = 80
```

Jejak parent: simpan `par[mask][v] = u` saat relaksasi.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll tspHeldKarp(const vector<vector<ll>>& w, int s = 0) {
    int n = (int)w.size();
    int N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));
    dp[1 << s][s] = 0;
    for (int mask = 0; mask < N; mask++)
        for (int u = 0; u < n; u++) {
            if (!((mask >> u) & 1) || dp[mask][u] >= INF) continue;
            for (int v = 0; v < n; v++) {
                if ((mask >> v) & 1) continue;
                int nmask = mask | (1 << v);
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + w[u][v]);
            }
        }
    ll ans = INF;
    int full = N - 1;
    for (int u = 0; u < n; u++)
        if (dp[full][u] < INF) ans = min(ans, dp[full][u] + w[u][s]);
    return ans;
}

pair<ll, vector<int>> tspPath(const vector<vector<ll>>& w, int s = 0) {
    int n = (int)w.size();
    int N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));
    vector<vector<int>> par(N, vector<int>(n, -1));
    dp[1 << s][s] = 0;
    for (int mask = 0; mask < N; mask++)
        for (int u = 0; u < n; u++) {
            if (!((mask >> u) & 1) || dp[mask][u] >= INF) continue;
            for (int v = 0; v < n; v++) {
                if ((mask >> v) & 1) continue;
                int nmask = mask | (1 << v);
                ll cand = dp[mask][u] + w[u][v];
                if (cand < dp[nmask][v]) {
                    dp[nmask][v] = cand;
                    par[nmask][v] = u;
                }
            }
        }
    int full = N - 1, last = s;
    ll best = INF;
    for (int u = 0; u < n; u++) {
        ll cand = dp[full][u] + w[u][s];
        if (cand < best) {
            best = cand;
            last = u;
        }
    }
    vector<int> path;
    int mask = full, cur = last;
    while (cur != -1) {
        path.push_back(cur);
        int p = par[mask][cur];
        mask ^= 1 << cur;
        cur = p;
    }
    reverse(path.begin(), path.end());
    path.push_back(s);
    return {best, path};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> w = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << tspHeldKarp(w) << "\n"; // 80
    auto [cost, p] = tspPath(w);
    cout << cost << " :";
    for (int x : p) cout << " " << x;
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Tidak menutup siklus (`+ w[u][s]`).
2. `dp[0][s] = 0` padahal mask kosong tidak berisi `s`.
3. Loop `v` yang sudah di mask.
4. `n = 20`: `2^20 * 20^2 = 4e8` ketat; pakai `int` jika bobot kecil, hindari vektor of vektor cache-buruk — array statis lebih aman.
5. Graf tidak lengkap: `w[u][v] = INF`, jangan dijumlah tanpa cek.

**Kompleksitas:** `O(2^n n^2)` waktu, `O(2^n n)` memori. `n = 16` nyaman, `n = 20` batas.

---

## Assignment bitmask

**Teori:** `n` orang, `n` tugas, biaya `c[i][j]`. Satu orang satu tugas. State: himpunan tugas yang sudah diisi, orang ke-`popcount(mask)` yang akan dipasangkan (orang diurutkan 0..n-1). Lebih hemat daripada `dp[mask_orang][mask_tugas]`.

**Kapan:** penugasan `n ≤ 20`, matching bipartit berbobot kecil. **Tidak:** `n = 200` → Hungarian `O(n^3)` / MCMF.

**STATE:** `dp[mask]` adalah biaya minimum menugaskan `popcount(mask)` orang pertama ke tepat himpunan tugas `mask`.

**TRANSISI:** orang `i = popcount(mask)` memilih tugas `j` kosong: `dp[mask|(1<<j)] = min(dp[mask] + c[i][j])`.

**BASIS:** `dp[0] = 0`.

**Proses angka:** 2 orang, biaya

```
   t0  t1
o0  4   1
o1  2   3
```

```
dp[00] = 0
orang0 ambil t0: dp[01] = 4
orang0 ambil t1: dp[10] = 1
orang1 + t1 dari 01: 4+3=7
orang1 + t0 dari 10: 1+2=3
dp[11] = 3
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll assignmentMin(const vector<vector<ll>>& c) {
    int n = (int)c.size();
    int N = 1 << n;
    vector<ll> dp(N, INF);
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
        if (dp[mask] >= INF) continue;
        int i = __builtin_popcount(mask);
        if (i == n) continue;
        for (int j = 0; j < n; j++)
            if (!((mask >> j) & 1))
                dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + c[i][j]);
    }
    return dp[N - 1];
}

ll assignmentMax(const vector<vector<ll>>& c) {
    int n = (int)c.size();
    int N = 1 << n;
    vector<ll> dp(N, LLONG_MIN / 4);
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
        int i = __builtin_popcount(mask);
        if (i == n) continue;
        for (int j = 0; j < n; j++)
            if (!((mask >> j) & 1))
                dp[mask | (1 << j)] = max(dp[mask | (1 << j)], dp[mask] + c[i][j]);
    }
    return dp[N - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> c = {{4, 1}, {2, 3}};
    cout << assignmentMin(c) << "\n"; // 3
    return 0;
}
```

**Jebakan:** memakai orang `j` bukan `popcount`. `n` orang ≠ `m` tugas tanpa padding. Maksimisasi diisi `INF` (salah sentinel).

**Kompleksitas:** `O(2^n n)` waktu, `O(2^n)` memori.

---

## Hamilton path dan varian

**Teori:** TSP tanpa kembali. Atau hitung banyak jalur Hamilton. Atau "visit any order, collect keys" (bit kunci di state). Tambah dimensi kecil: `dp[mask][u][mod]` dll.

**Kapan:** jalur yang mengunjungi semua / subset wajib, `n ≤ 20`. **Tidak:** DAG biasa tanpa himpunan — topo DP `O(n+m)`.

**STATE:** `dp[mask][u]` banyak (atau biaya) jalur yang sudah mengunjungi `mask`, berakhir di `u`.

**TRANSISI:** dari `u` ke `v` belum dikunjungi, kalikan/tambah sesuai soal.

**BASIS:** `dp[1<<i][i] = 1` (atau 0 biaya) untuk setiap start, atau hanya start yang diizinkan.

**Proses angka:** jalur 3 simpul garis `0-1-2`.

```
dp[001][0]=1
dp[011][1]=1
dp[111][2]=1
satu Hamilton 0-1-2
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll countHamilton(const vector<vector<int>>& g) {
    int n = (int)g.size();
    int N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
    for (int mask = 0; mask < N; mask++)
        for (int u = 0; u < n; u++) {
            if (!dp[mask][u]) continue;
            for (int v : g[u]) {
                if ((mask >> v) & 1) continue;
                dp[mask | (1 << v)][v] = (dp[mask | (1 << v)][v] + dp[mask][u]) % MOD;
            }
        }
    ll ans = 0;
    int full = N - 1;
    for (int u = 0; u < n; u++) ans = (ans + dp[full][u]) % MOD;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> g = {{1}, {0, 2}, {1}};
    cout << countHamilton(g) << "\n"; // 2 : 0-1-2 dan 2-1-0
    return 0;
}
```

**Jebakan:** menghitung siklus sebagai jalur (dobel arah). Graf berarah vs tak berarah. Lupa modulo.

**Kompleksitas:** `O(2^n n^2)` jika padat, `O(2^n (n+m))` jika daftar tetangga.

---

## SOS DP

**Teori:** Sum Over Subsets. Untuk setiap mask `x`, hitung `f[x] = sum_{s ⊆ x} a[s]`. Naif `O(3^n)` (enumerate subset). SOS: untuk tiap bit, "sebarkan" nilai ke mask yang bitnya nyala. Analoginya prefix sum di kubus `{0,1}^n`.

**Kapan:** "jumlah / OR / max atas semua subset", zeta transform, AND convolution sederhana. **Tidak:** butuh subset tepat berukuran k tanpa bit DP tambahan; atau `n > 23`.

**STATE:** setelah memproses bit `0..i-1`, `f[mask]` adalah jumlah `a[s]` untuk `s` yang boleh beda dari `mask` hanya pada bit `< i`.

**TRANSISI:** `for i in 0..n-1: for mask: if mask punya bit i: f[mask] += f[mask ^ (1<<i)]`.

**BASIS:** `f = a` (array awal).

**Proses angka:** `n = 2`, `a[00]=1, a[01]=2, a[10]=4, a[11]=8`.

```
bit 0 (nilai 1):
  mask 01: f[01] += f[00] -> 2+1=3
  mask 11: f[11] += f[10] -> 8+4=12
  f = [1, 3, 4, 12]

bit 1 (nilai 2):
  mask 10: f[10] += f[00] -> 4+1=5
  mask 11: f[11] += f[01] -> 12+3=15
  f = [1, 3, 5, 15]
```

Cek: subset dari 11 = semua, 1+2+4+8=15. Subset dari 10 = 00 dan 10 → 1+4=5.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> sosSubsetSum(vector<ll> f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask >> i & 1) f[mask] += f[mask ^ (1 << i)];
    return f;
}

vector<ll> sosSupersetSum(vector<ll> f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (!(mask >> i & 1)) f[mask] += f[mask ^ (1 << i)];
    return f;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 2;
    vector<ll> a = {1, 2, 4, 8};
    auto f = sosSubsetSum(a, n);
    for (ll x : f) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** urutan loop bit vs mask terbalik secara salah (boleh mask luar selama bit tetap berurutan). Menjumlah superset dengan rumus subset. Overflow. `n = 20` memori `8 * 1e6` aman, `n = 26` tidak.

**Kompleksitas:** `O(n 2^n)` waktu dan `O(2^n)` memori. Naif subset `O(3^n)`.

---

## Digit DP

**Teori:** Hitung banyak bilangan di `[L, R]` yang memenuhi syarat digit (jumlah digit, tidak ada angka berurutan sama, habis dibagi `m` kecil, dll). `R` sampai `10^18` — loop mustahil. Bangun dari kiri. Bendera **tight**: prefiks masih sama dengan batas, digit berikutnya terbatas. Bendera **leading**: masih nol di depan, `007` vs `7`. Pola rentang: `f(R) - f(L-1)`.

**Kapan:** batas besar, syarat bisa dilacak per digit. **Tidak:** `R ≤ 1e6` (loop). Syarat tidak bisa diringkas ke state kecil (seluruh bilangan sebagai himpunan digit tanpa kompresi).

**STATE:** `dp[pos][tight][lead][sum]` (contoh) adalah banyak cara mengisi digit dari posisi `pos` sampai akhir, dengan status menempel batas, masih leading zero, dan jumlah digit `sum`.

**TRANSISI:** pilih digit `d` dari 0 sampai `up = tight ? bound[pos] : 9`. `ntight = tight && (d==up)`. `nlead = lead && (d==0)`. Update akumulator syarat.

**BASIS:** jika `pos == n` (semua digit terisi), kembalikan 1 jika syarat terpenuhi (sering: bukan "bilangan kosong" kecuali 0 diizinkan), else 0.

**Proses angka:** hitung banyak bilangan `0..13` yang jumlah digitnya `= 4`. Batas `"13"`.

```
pos0 (puluhan), tight=1, lead=1
  d=0: lead tetap, tight=0 (0<1), ke pos1 bebas 0-9
  d=1: lead=0, tight=1, ke pos1 d<=3

Dari d=0 (bukan tight):
  satuan 0..9, lead pecah saat d>0
  jumlah 4: 4 saja (bilangan 4)

Dari d=1 tight:
  satuan 0..3, lead=0, sum sudah 1
  butuh satuan 3 -> 13, sum=4

Juga 04 dari cabang lead... tergantung apakah 4 dihitung.
Jawaban: 4 dan 13 (dan 40 tidak ada). Jika 0..13: {4, 13} = 2.
```

Hitung `f(13)` untuk sum=4: 2. `f(3)`: 0. Rentang `[4,13]` = 2.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string bound;
ll memo[20][2][2][200];
char vis[20][2][2][200];

ll dfsDigit(int pos, int tight, int lead, int sum, int target) {
    if (pos == (int)bound.size()) return (!lead && sum == target) || (lead && target == 0);
    ll& res = memo[pos][tight][lead][sum];
    if (vis[pos][tight][lead][sum]) return res;
    vis[pos][tight][lead][sum] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        int nlead = lead && (d == 0);
        int nsum = sum + (nlead ? 0 : d);
        int ntight = tight && (d == up);
        res += dfsDigit(pos + 1, ntight, nlead, nsum, target);
    }
    return res;
}

ll countSumEq(ll x, int target) {
    if (x < 0) return 0;
    bound = to_string(x);
    memset(vis, 0, sizeof(vis));
    return dfsDigit(0, 1, 1, 0, target);
}

ll countSumEqRange(ll L, ll R, int target) {
    return countSumEq(R, target) - countSumEq(L - 1, target);
}

ll dfsNoAdjSame(int pos, int tight, int lead, int last) {
    if (pos == (int)bound.size()) return 1;
    static ll dp[20][2][2][11];
    static char seen[20][2][2][11];
    static int stamp = 1, cur = 0;
    if (cur != stamp) {
        memset(seen, 0, sizeof(seen));
        cur = stamp;
    }
    ll& res = dp[pos][tight][lead][last + 1];
    if (seen[pos][tight][lead][last + 1]) return res;
    seen[pos][tight][lead][last + 1] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        if (!lead && d == last) continue;
        int nlead = lead && d == 0;
        int nlast = nlead ? -1 : d;
        res += dfsNoAdjSame(pos + 1, tight && d == up, nlead, nlast);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << countSumEqRange(1, 13, 4) << "\n"; // 2 : 4 dan 13
    cout << countSumEqRange(1, 20, 1) << "\n"; // 1,10
    return 0;
}
```

Catatan: `dfsNoAdjSame` di atas memakai stamp yang tidak di-reset antar panggilan — untuk kontes, `memset` memo setiap kali `bound` berubah, seperti `countSumEq`.

Versi bersih "berapa bilangan ≤ x":

```cpp
ll solveTo(ll x) {
    if (x < 0) return 0;
    bound = to_string(x);
    memset(vis, 0, sizeof(vis));
    return dfsDigit(0, 1, 1, 0, /*target=*/0); // ganti syarat
}
```

**Jebakan:**

1. Lupa `f(R)-f(L-1)` dan `L=0`.
2. Leading zero: `007` menambah sum 7+0+0 atau 7? Biasanya nol depan tidak dihitung sebagai digit.
3. Memo tidak di-reset saat `bound` berubah.
4. `tight` tidak di-update: semua digit dianggap 0-9, overcount.
5. `int` untuk jawaban; `R-L+1` bisa `1e18` → `ll`.

**Kompleksitas:** `O(pos * 2 * 2 * (sum+1) * 10)` ≈ `O(18 * 4 * 200 * 10)` kecil. Tambah dimensi `mod m` → kali `m`. `m ≤ 100` aman.

---

## Tree DP

**Teori:** Akarkan pohon di simpul mana saja (misalnya 1). DFS: anak selesai sebelum ayah. Jawaban subtree digabung ke ayah. Pola klasik: independent set maksimum, diameter, jumlah jalur, pewarnaan, "ambil / tidak ambil simpul".

**Kapan:** input pohon, "pada subtree", "pilih simpul dengan larangan tetangga". **Tidak:** graf umum bersiklus — itu bitmask / flow / NP.

**STATE (independent set):** `dp[u][0]` adalah nilai maksimum di subtree `u` jika `u` **tidak** diambil. `dp[u][1]` jika `u` **diambil**.

**TRANSISI:** `dp[u][0] = sum_v max(dp[v][0], dp[v][1])`. `dp[u][1] = a[u] + sum_v dp[v][0]`.

**BASIS:** daun: `dp[u][0] = 0`, `dp[u][1] = a[u]`.

**Proses angka:**

```
    1 (3)
   / \
  2(2) 3(1)
  |
  4(4)

daun 4: (0, 4)
2: 0 = max(0,4)=4 ; 1 = 2+0=2  -> (4,2)
3: (0,1)
1: 0 = max(4,2)+max(0,1)=5
   1 = 3+4+0=7
jawaban max(5,7)=7  (ambil 1 dan 4)
```

Diameter: di tiap `u` simpan dua jalur turun terpanjang. Diameter lewat `u` = jumlah dua terbaik + (jika berbobot sisi). Global = max.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfsIS(int u, int p, const vector<vector<int>>& g, const vector<ll>& a,
           vector<array<ll, 2>>& dp) {
    dp[u][0] = 0;
    dp[u][1] = a[u];
    for (int v : g[u]) {
        if (v == p) continue;
        dfsIS(v, u, g, a, dp);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

ll maxIndependentSet(const vector<vector<int>>& g, const vector<ll>& a, int root = 0) {
    int n = (int)g.size();
    vector<array<ll, 2>> dp(n);
    dfsIS(root, -1, g, a, dp);
    return max(dp[root][0], dp[root][1]);
}

ll diameterDown(int u, int p, const vector<vector<pair<int, ll>>>& g, ll& ans) {
    ll best1 = 0, best2 = 0;
    for (auto [v, w] : g[u]) {
        if (v == p) continue;
        ll d = diameterDown(v, u, g, ans) + w;
        if (d > best1) {
            best2 = best1;
            best1 = d;
        } else if (d > best2) best2 = d;
    }
    ans = max(ans, best1 + best2);
    return best1;
}

ll treeDiameter(const vector<vector<pair<int, ll>>>& g) {
    ll ans = 0;
    diameterDown(0, -1, g, ans);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 4;
    vector<vector<int>> g(n);
    auto add = [&](int u, int v) { g[u].push_back(v); g[v].push_back(u); };
    add(0, 1);
    add(0, 2);
    add(1, 3);
    vector<ll> a = {3, 2, 1, 4};
    cout << maxIndependentSet(g, a) << "\n"; // 7
    return 0;
}
```

**Jebakan:** tidak men-skip parent (infinite recursion). Akar 1-indexed vs 0. `dp[u][1] += max(anak)` — boleh ambil anak, salah. Pohon tidak terhubung: loop semua akar.

**Kompleksitas:** `O(n)` waktu dan memori.

---

## Knapsack pada pohon

**Teori:** Kapasitas `W` dibagi ke anak-anak. Menggabungkan dua knapsack subtree: konvolusi `O(s1*s2)`. Jika selalu merge kecil ke besar / urutan hati-hati, total `O(n W^2)` naif, bisa `O(n W)` dengan teknik ukuran subtree (setiap pasangan ancestor-descendant terbatas). Ide: `tmp[k] = max atas j (dp_u[k-j] + dp_v[j])` lalu `dp_u = tmp`.

**Kapan:** pilih subset simpul dengan kapasitas, constraint subtree. **Tidak:** `n*W^2` terlalu besar tanpa optimasi.

**STATE:** `dp[u][w]` adalah nilai maksimum di subtree `u` dengan memakai kapasitas tepat / paling banyak `w`.

**TRANSISI:** inisialisasi `dp[u][0] = 0`, jika ambil `u` maka `dp[u][cost[u]] = val[u]`. Untuk tiap anak, konvolusi.

**BASIS:** daun hanya dua pilihan: ambil atau tidak.

**Proses angka:**

```
u cost 1 val 5, anak v cost 1 val 3, W=2
v: [0]=0, [1]=3
u tanpa merge: [0]=0, [1]=5
merge: [2] = 5+3 = 8
```

**Kode modular (ide, O(n W^2)):**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

void dfsKnapsack(int u, int p, int W, const vector<vector<int>>& g,
                 const vector<int>& cost, const vector<ll>& val,
                 vector<vector<ll>>& dp) {
    vector<ll> cur(W + 1, NEG);
    cur[0] = 0;
    if (cost[u] <= W) cur[cost[u]] = val[u];
    for (int v : g[u]) {
        if (v == p) continue;
        dfsKnapsack(v, u, W, g, cost, val, dp);
        vector<ll> nxt(W + 1, NEG);
        for (int a = 0; a <= W; a++)
            if (cur[a] > NEG)
                for (int b = 0; a + b <= W; b++)
                    if (dp[v][b] > NEG) nxt[a + b] = max(nxt[a + b], cur[a] + dp[v][b]);
        cur.swap(nxt);
    }
    dp[u] = cur;
}

ll treeKnapsack(const vector<vector<int>>& g, const vector<int>& cost,
                const vector<ll>& val, int W, int root = 0) {
    int n = (int)g.size();
    vector<vector<ll>> dp(n, vector<ll>(W + 1, NEG));
    dfsKnapsack(root, -1, W, g, cost, val, dp);
    return *max_element(dp[root].begin(), dp[root].end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> g(2);
    g[0].push_back(1);
    g[1].push_back(0);
    cout << treeKnapsack(g, {1, 1}, {5, 3}, 2) << "\n"; // 8
    return 0;
}
```

**Jebakan:** konvolusi tanpa `NEG` cek. Kapasitas "paling banyak" vs "tepat". Menggabung ayah ke anak sebelum anak selesai.

**Kompleksitas:** naif `O(n W^2)`. Dengan merge by size sering `O(n W)` atau `O(n W log n)` tergantung soal.

---

## Rerooting

**Teori:** Butuh jawaban "jika akar = setiap simpul". DFS dua kali: (1) `down[u]` = jawaban / agregat **hanya subtree** `u`; (2) saat turun ke `v`, hitung kontribusi dari "sisa pohon" (`up`) memakai `down` saudara + `up` ayah. Analoginya: sudah tahu nilai di rumah, lalu pindah rumah, sesuaikan angka yang keluar/masuk.

**Kapan:** "untuk setiap simpul sebagai ibu kota", jumlah jarak ke semua, ukuran komponen setelah hapus. **Tidak:** hanya satu akar — satu DFS cukup.

**STATE:** `down[u]` adalah jumlah jarak (contoh) dari `u` ke semua simpul di subtree. `ans[u]` adalah jumlah jarak dari `u` ke semua simpul di pohon, jika `u` akar.

**TRANSISI:** `down[u] = Σ (down[v] + sz[v])`. Saat reroot ke `v`: `up_v = (ans[u] - (down[v]+sz[v])) + (n - sz[v])`. `ans[v] = down[v] + up_v`.

**BASIS:** daun `down = 0`, `sz = 1`. `ans[root] = down[root]`.

**Proses angka:** garis `0-1-2`, `n=3`.

```
akar 0:
  sz[2]=1 down[2]=0
  sz[1]=2 down[1]=0+1=1
  sz[0]=3 down[0]=1+2=3
  ans[0]=3   (jarak 1+2)

reroot ke 1:
  sisa dari 0: ans[0]-(down[1]+sz[1]) = 3-(1+2)=0
  up = 0 + (3-2) = 1
  ans[1] = 1+1 = 2   (jarak ke 0 dan 2 = 1+1)

reroot ke 2 dari 1:
  ans[2] = 3  simetris dengan 0
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfs1(int u, int p, const vector<vector<int>>& g,
          vector<int>& sz, vector<ll>& down) {
    sz[u] = 1;
    down[u] = 0;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs1(v, u, g, sz, down);
        sz[u] += sz[v];
        down[u] += down[v] + sz[v];
    }
}

void dfs2(int u, int p, int n, const vector<vector<int>>& g,
          const vector<int>& sz, const vector<ll>& down, vector<ll>& ans) {
    for (int v : g[u]) {
        if (v == p) continue;
        ll up = (ans[u] - (down[v] + sz[v])) + (n - sz[v]);
        ans[v] = down[v] + up;
        dfs2(v, u, n, g, sz, down, ans);
    }
}

vector<ll> sumDistancesAllRoots(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> sz(n);
    vector<ll> down(n), ans(n);
    dfs1(0, -1, g, sz, down);
    ans[0] = down[0];
    dfs2(0, -1, n, g, sz, down, ans);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> g(3);
    g[0].push_back(1);
    g[1].push_back(0);
    g[1].push_back(2);
    g[2].push_back(1);
    for (ll x : sumDistancesAllRoots(g)) cout << x << " ";
    cout << "\n"; // 3 2 3
    return 0;
}
```

**Jebakan:** `up` memakai `ans[u]` sebelum `ans[v]` diisi — itu benar, jangan pakai `down[u]` saja. Pohon berbobot: ganti `+sz` dengan `+sz*w`. Multi-child: rumus `ans[u] - kontribusi v` harus tepat, bukan `sum salah`.

**Kompleksitas:** `O(n)` waktu, `O(n)` memori.

---

## CHT sederhana

**Teori:** Banyak DP berbentuk `dp[i] = min_j (dp[j] + b[j] * a[i]) + C[i]`. Itu minimum atas garis `y = m x + c` dengan `m = b[j]`, `c = dp[j]`, query `x = a[i]`. Convex Hull Trick membuang garis yang tidak pernah optimal. Jika kemiringan monoton dan query `x` monoton, deque `O(1)` amortized. Analoginya: dari kumpulan garis, hanya yang membentuk selubung bawah yang perlu disimpan.

Syarat kasar minimisasi + deque: garis ditambah dengan slope **menurun**, query `x` **menaik**.

**Kapan:** `O(n^2)` DP garis, `n ≤ 1e5`. Contoh: `dp[i] = min_{j<i} dp[j] + (h[i]-h[j])^2` bisa diubah jadi garis jika dijabarkan. **Tidak:** `m` dan `x` acak tanpa Li Chao / hull dinamis (Day 269). Jangan pakai CHT jika transisi bukan linear.

**STATE:** bukan tabel 2D; `dp[i]` tetap nilai optimal prefiks `i`, dihitung sebagai query hull lalu insert garis baru.

**TRANSISI:** `dp[i] = hull.query(x[i]) + extra[i]`, lalu `hull.add(m[i], c[i])`.

**BASIS:** `dp[0] = 0`, insert garis dari `j = 0`.

**Proses angka:** garis `y = -2x + 0`, `y = -x + 3`, `y = 0x + 10`. Query `x = 0, 1, 4` (x naik), slope -2, -1, 0 (naik — ini **max** hull; untuk min, slope harus turun).

Min-hull contoh: slope `3, 1, -1` ditambah berurutan, query `x = 0, 2, 5`.

```
garis A: 3x + 0
garis B: 1x + 5    perpotongan A/B di x=2.5
garis C: -1x + 12  buang B jika tidak pernah optimal

query 0: A = 0
query 2: A = 6, B = 7 -> 6
query 5: C = 7 lebih baik
```

Contoh DP konkret: `a` naik, `dp[i] = min_{j<i} dp[j] + a[i]*b[j]` dengan `b` menurun.

```
b = [4, 3, 1]  (slope)
a query x = [1, 2, 4]
dp[0]=0, garis m=4 c=0
dp[1] = 4*1 + extra0
...
```

**Kode modular (MinConvexHull + satu DP):**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
    ll m, b;
    ll eval(ll x) const { return m * x + b; }
};

struct MinConvexHull {
    deque<Line> hull;

    static bool isBad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(b.b - a.b) * (b.m - c.m) >= (__int128)(c.b - b.b) * (a.m - b.m);
    }

    void add(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b) return;
            hull.pop_back();
        }
        while (hull.size() >= 2 && isBad(hull[hull.size() - 2], hull.back(), cur))
            hull.pop_back();
        hull.push_back(cur);
    }

    ll query(ll x) {
        while (hull.size() >= 2 && hull[1].eval(x) <= hull[0].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }
};

// dp[i] = min_{j < i} dp[j] + b[j] * a[i]
// syarat: b menurun, a menaik
vector<ll> chtLinearDP(const vector<ll>& a, const vector<ll>& b) {
    int n = (int)a.size();
    vector<ll> dp(n, 0);
    MinConvexHull hull;
    hull.add(b[0], dp[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = hull.query(a[i]);
        hull.add(b[i], dp[i]);
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    MinConvexHull h;
    h.add(3, 0);
    h.add(1, 5);
    h.add(-1, 12);
    cout << h.query(0) << " " << h.query(2) << " " << h.query(5) << "\n";
    vector<ll> a = {0, 1, 2, 4};
    vector<ll> b = {5, 3, 2, 0};
    auto dp = chtLinearDP(a, b);
    for (ll x : dp) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Slope tidak monoton → deque salah; pakai binary search hull atau Li Chao.
2. Overflow perpotongan: wajib `__int128`.
3. Query sebelum ada garis.
4. Max vs min tertukar (`<=` vs `>=`).
5. Dua garis slope sama: simpan intercept lebih baik saja.

**Kompleksitas:** `O(n)` amortized insert+query jika monoton. `O(n log n)` jika query acak pada hull terurut.

---

## Knuth optimization

**Teori:** Range DP `dp[l][r] = min_{l≤k<r} dp[l][k]+dp[k+1][r] + C(l,r)` dari `O(n^3)` menjadi `O(n^2)` jika `C` memenuhi quadrangle inequality dan monoton. Akibatnya titik pecah `opt[l][r]` monoton: `opt[l][r-1] ≤ opt[l][r] ≤ opt[l+1][r]`. Cukup menelusuri `k` di rentang itu. Contoh: stone merge dengan `C = sum[l..r]` (sering QI).

**Kapan:** `n ≤ 2000` range DP, `C` kontigu jumlah. **Tidak:** `C` sembarang — monoton `opt` bisa rusak, WA diam.

**STATE:** sama `dp[l][r]`, plus `opt[l][r]` = `k` terbaik.

**TRANSISI:** `k` hanya dari `opt[l][r-1]` sampai `opt[l+1][r]`.

**BASIS:** `opt[i][i] = i`, `dp[i][i] = 0`.

**Proses angka:** `a = [1, 1, 1, 1]`. Tanpa Knuth, 4 titik pecah per sel panjang 4. Dengan monoton, rentang `k` menyempit. Hasil sama: selalu `sum` berulang, biaya `6` untuk empat 1 (dua gabung 2, lalu 4, plus tengah — hitung: total `12`? 

Empat batu 1:
```
gabung bersebelahan berulang:
((1+1)+(1+1)) biaya 2+2+4=8
((1+1)+1)+1 biaya 2+3+4=9
Knuth menemukan 8.
```

**Kode modular (ide):**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll knuthMerge(const vector<ll>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            int lo = opt[l][r - 1];
            int hi = (l + 1 <= r) ? opt[l + 1][r] : r - 1;
            hi = min(hi, r - 1);
            lo = min(lo, hi);
            ll add = pref[r + 1] - pref[l];
            for (int k = lo; k <= hi; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + add;
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    return dp[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << knuthMerge({1, 1, 1, 1}) << "\n";
    cout << knuthMerge({10, 20, 30}) << "\n"; // 90, sama file 14
    return 0;
}
```

**Jebakan:** memakai Knuth pada `C` yang tidak QI. `opt` tidak diinisialisasi diagonal. `hi < lo` karena urutan `len`. Tetap `O(n^3)` jika rentang `k` tidak menyempit — cek total iterasi.

**Kompleksitas:** `O(n^2)` waktu jika monoton berlaku, `O(n^2)` memori.

---

## D&C DP ide

**Teori:** Bentuk `dp[i][j] = min_{k<j} dp[i-1][k] + C(k+1, j)` dengan `opt[i][j]` monoton terhadap `j`. Hitung satu lapisan `i` dengan divide and conquer pada `j`: untuk tengah `mid`, brute `k` di rentang, lalu rekursi kiri dengan `k ≤ opt`, kanan `k ≥ opt`.

**Kapan:** `i ≤ 100`, `j ≤ 1e5`, `C` O(1) atau O(log) setelah precompute (misalnya cost segmen). **Tidak:** `opt` tidak monoton.

**STATE:** `dp[i][j]` = biaya membagi `j` elemen pertama jadi `i` kelompok.

**TRANSISI:** titik pecah `k` terakhir kelompok.

**BASIS:** `dp[1][j] = C(1,j)`, `dp[i][0] = 0` / INF.

**Proses angka:** bagi `[1, 3, 5]` jadi 2 kelompok, `C(l,r) = (sum)^2` (contoh).

```
1 kelompok: (1+3+5)^2 = 81
2 kelompok:
  k=0: 0 + (1+3+5)^2 tidak
  k=1: 1^2 + (3+5)^2 = 1+64=65
  k=2: (1+3)^2 + 5^2 = 16+25=41
opt di 2
```

**Kode ide:**

```cpp
void dnc(int l, int r, int optL, int optR, int layer,
         const vector<ll>& prev, vector<ll>& cur, function<ll(int,int)> C) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<ll, int> best = {4e18, optL};
    for (int k = optL; k <= min(mid - 1, optR); k++)
        best = min(best, {prev[k] + C(k + 1, mid), k});
    cur[mid] = best.first;
    dnc(l, mid - 1, optL, best.second, layer, prev, cur, C);
    dnc(mid + 1, r, best.second, optR, layer, prev, cur, C);
}
```

**Jebakan:** `C` tidak QI/monoton. Indeks 0/1. `optR` vs `mid-1`.

**Kompleksitas:** `O(K n log n)` untuk `K` lapisan jika `C` O(1).

---

## Pola lain menengah

### Game DP pada DAG

**Teori:** Posisi menang jika ada langkah ke posisi kalah. Posisi kalah jika semua langkah ke menang (atau tidak ada langkah). Itu DP di DAG state.

**STATE:** `win[s]` benar jika pemain yang bergerak dari `s` menang (permainan normal).

**TRANSISI:** `win[s] = OR (not win[t])` atas langkah `s→t`.

**BASIS:** terminal `win = false` (tidak bisa gerak = kalah).

**Proses:** Nim 1 tumpukan `n=3` ambil 1/2: `win[0]=0, win[1]=1, win[2]=1, win[3]=1`.

**Kode:**

```cpp
int mex(const vector<int>& s) {
    vector<char> seen(s.size() + 2);
    for (int x : s)
        if (x < (int)seen.size()) seen[x] = 1;
    int m = 0;
    while (seen[m]) m++;
    return m;
}
```

Grundy gabungan XOR. Detail di file game theory (folder 14 DAFTAR-MATERI).

**Kompleksitas:** `O(|state| + |transisi|)`.

### Broken profile (ide)

Mengisi grid `R × C` dengan ubin 1×2. State: kolom + bitmask baris yang sudah tertutup. `R ≤ 12`, `C ≤ 1e3`. Transisi menelusuri konfigurasi kompatibel. Kode panjang; hafalkan ide: `dp[col][mask]`.

### Bitset knapsack

`bs |= bs << w` seperti subset sum file 13. 64× lebih cepat. `n * S / 64 ≤ 1e8`.

### Ekspektasi

`E[s] = 1 + (Σ E[t]) / deg` untuk random walk. Sistem linear atau DP DAG. Hati-hati siklus: Gaussian.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

ll tspHeldKarp(const vector<vector<ll>>& w, int s);
ll assignmentMin(const vector<vector<ll>>& c);
vector<ll> sosSubsetSum(vector<ll> f, int n);
ll countSumEqRange(ll L, ll R, int target);
ll maxIndependentSet(const vector<vector<int>>& g, const vector<ll>& a, int root);
vector<ll> sumDistancesAllRoots(const vector<vector<int>>& g);

struct MinConvexHull {
    struct Line { ll m, b; ll eval(ll x) const { return m * x + b; } };
    deque<Line> hull;
    static bool isBad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(b.b - a.b) * (b.m - c.m) >= (__int128)(c.b - b.b) * (a.m - b.m);
    }
    void add(ll m, ll b);
    ll query(ll x);
};

ll knuthMerge(const vector<ll>& a);
```

Batas cepat:

| Pola | n aman |
|---|---|
| TSP `O(2^n n^2)` | 16–20 |
| Assignment `O(2^n n)` | 20–22 |
| SOS `O(n 2^n)` | 20–23 |
| Digit DP | 18 digit × state kecil |
| Tree DP | `n ≤ 2e5` |
| Tree knapsack naif | `n W^2 ≤ 1e8` |
| CHT monoton | `n ≤ 1e6` |
| Knuth | `n ≤ 2000` |
| Range tanpa Knuth | `n ≤ 400` |

---

## Peta jebakan file ini

| Gejala | Penyebab | Perbaikan |
|---|---|---|
| TSP terlalu besar | tidak kembali / start mask 0 | `dp[1<<s][s]`, `+w[u][s]` |
| Assignment WA | orang ≠ popcount | `i = __builtin_popcount` |
| SOS salah | rumus subset vs superset | uji n=2 manual |
| Digit overcount | lupa tight / lead | dua bendera |
| Digit WA L=0 | `f(-1)` | khusus 0 |
| Tree RE | tidak skip parent | `if (v==p)` |
| Reroot WA | rumus up | uji garis 3 simpul 3,2,3 |
| CHT WA | slope tidak monoton | cek syarat / Li Chao |
| CHT overflow | kali silang 64-bit | `__int128` |
| Knuth WA | C tidak QI | jatuh ke O(n^3) |
| MLE bitmask | `vector<vector<ll>>(1<<20, n)` | array statis / `int` |

Latihan: AtCoder DP-O (matching), DP-S (digit), DP-V (subtree), DP-W lebih berat; CSES Hamiltonian Flights, Counting Numbers; classic TSP n=16; CHT AtCoder DP-Z Frog 3; Knuth stone merge n=2000.

---

## Digit DP: sisa bagi

**Teori:** Hitung banyak `x` di `[L, R]` yang `x ≡ 0 (mod m)` dan tidak punya digit `4` (contoh). Tambah dimensi `mod`. Leading zero: bilangan 0 biasanya sah sebagai 0 mod m.

**STATE:** `dfs(pos, tight, lead, rem)` = banyak kelanjutan agar sisa akhir 0 dan tanpa digit 4.

**TRANSISI:** digit `d ≠ 4` (kecuali masih lead dan d=0). `nrem = (rem*10 + d) % m`.

**BASIS:** `pos==n`: jika `lead` (bilangan 0) hitung 1; else 1 jika `rem==0`.

**Proses angka:** `m = 2`, tanpa larangan, `R = 10`. Genap `0..10` = 6 buah (0,2,4,6,8,10).

```
"10"
pos0 tight: d=0 lead, d=1
dari 1 tight: satuan 0 saja, rem dari 1, *10+0 = 10 ≡ 0 -> 1
dari 0 not tight: satuan 0-9, bilangan 0..9, genap 5 (0,2,4,6,8) + ...
total 6 termasuk 10 dan 0.
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string bound;
int MODM;
ll memo[20][2][2][100];
char vis[20][2][2][100];

ll dfsMod(int pos, int tight, int lead, int rem) {
    if (pos == (int)bound.size()) return rem == 0;
    ll& res = memo[pos][tight][lead][rem];
    if (vis[pos][tight][lead][rem]) return res;
    vis[pos][tight][lead][rem] = 1;
    res = 0;
    int up = tight ? bound[pos] - '0' : 9;
    for (int d = 0; d <= up; d++) {
        if (d == 4 && !(lead && d == 0)) continue;
        int nlead = lead && d == 0;
        int nrem = nlead ? 0 : (rem * 10 + d) % MODM;
        res += dfsMod(pos + 1, tight && d == up, nlead, nrem);
    }
    return res;
}

ll countModNo4(ll x, int m) {
    if (x < 0) return 0;
    bound = to_string(x);
    MODM = m;
    memset(vis, 0, sizeof(vis));
    return dfsMod(0, 1, 1, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << countModNo4(10, 2) - countModNo4(0, 2) + (0 % 2 == 0) << "\n";
    return 0;
}
```

Hati-hati double-count 0; lebih aman `countModNo4(R) - countModNo4(L-1)`.

**Jebakan:** `rem*10` overflow `int` — `rem` sudah `< m`. Digit 4 dilarang juga pada leading. Memo `m > 100` melewati array.

**Kompleksitas:** `O(digit · 2 · 2 · m · 10)`.

---

## Matching pada pohon

**Teori:** Matching maksimum: tiap simpul paling banyak satu pasangan (sisi). Untuk `u`, tidak dipasangkan ke anak: jumlahkan max anak. Atau dipasangkan ke tepat satu anak `v`: `1 + (anak v tidak terpakai) + max sisanya`.

**STATE:** `dp[u][0]` matching max di subtree jika `u` masih bebas. `dp[u][1]` jika `u` sudah dipasangkan ke bawah.

**TRANSISI:** `dp[u][0] = Σ max(dp[v][0], dp[v][1])`. `dp[u][1] = max_v (1 + dp[v][0] + Σ_{x≠v} max(dp[x][0], dp[x][1]))`.

**BASIS:** daun keduanya 0 (tidak ada sisi).

**Proses angka:** bintang 1 pusat + 3 daun. Matching max 1. Jalur 4 simpul: matching 2.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

void dfsMatch(int u, int p, const vector<vector<int>>& g, vector<array<int, 2>>& dp) {
    int sum = 0;
    dp[u][0] = dp[u][1] = 0;
    for (int v : g[u]) {
        if (v == p) continue;
        dfsMatch(v, u, g, dp);
        sum += max(dp[v][0], dp[v][1]);
    }
    dp[u][0] = sum;
    for (int v : g[u]) {
        if (v == p) continue;
        int tanpa = sum - max(dp[v][0], dp[v][1]);
        dp[u][1] = max(dp[u][1], 1 + dp[v][0] + tanpa);
    }
}

int treeMatching(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<array<int, 2>> dp(n);
    dfsMatch(0, -1, g, dp);
    return max(dp[0][0], dp[0][1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<int>> g(4);
    auto add = [&](int u, int v) { g[u].push_back(v); g[v].push_back(u); };
    add(0, 1);
    add(1, 2);
    add(2, 3);
    cout << treeMatching(g) << "\n"; // 2
    return 0;
}
```

**Jebakan:** memasangkan `u` ke dua anak. `dp[v][1]` saat memasangkan `u-v` (v sudah ke bawah, tidak bisa ke ayah).

**Kompleksitas:** `O(n)`.

---

## CHT: jabarkan kuadrat

**Teori:** AtCoder DP-Z: `dp[i] = min_j dp[j] + (h[i]-h[j])^2 + C`. Jabarkan:

```
(h[i]-h[j])^2 = h[i]^2 + h[j]^2 - 2 h[i] h[j]
dp[i] = h[i]^2 + min_j ( dp[j] + h[j]^2 - 2 h[j] * h[i] ) + C
```

Garis: slope `m_j = -2 h[j]`, intercept `dp[j] + h[j]^2`. Query `x = h[i]`. Jika `h` naik, `x` naik. Slope `-2h` menurun. Deque min sah.

**Proses angka:** `h = [1, 3, 6]`, `C = 0`, `dp[0]=0`.

```
j=0 garis m=-2 c=0+1=1
i=1 x=3: query= -6+1=-5; dp[1]=9 + (-5)=4
  cek: (3-1)^2=4  ok
i=2 x=6:
  garis j=1: m=-6, c=4+9=13
  query min( -2*6+1= -11, -6*6+13= -23 ) = -23
  dp[2]=36-23=13
  cek: 0+(6-1)^2=25, 4+(6-3)^2=13  ok
```

**Kode:** pakai `MinConvexHull` di atas: `add(-2*h[j], dp[j]+h[j]*h[j])`, `dp[i] = h[i]*h[i] + query(h[i]) + C`.

**Jebakan:** lupa `h[i]^2` di luar min. `C` dikali jumlah lompatan vs sekali — baca soal.

**Kompleksitas:** `O(n)` jika `h` monoton.

---

## Subset DP: OR / AND / gcd

**Teori:** `dp[mask]` = OR semua elemen di mask, dihitung dari `dp[mask ^ (1<<i)] | a[i]`. Isi dari mask kecil ke besar. Berguna untuk "apakah ada subset OR = target".

**STATE:** `dp[mask]` adalah hasil agregat elemen di `mask`.

**TRANSISI:** `dp[mask] = dp[mask ^ lowbit] ⋆ a[index(lowbit)]`.

**BASIS:** `dp[0] = identitas` (0 untuk OR, ~0 untuk AND, 0 untuk jumlah).

**Proses angka:** `a = [1, 2, 4]`.

```
dp[001]=1 dp[010]=2 dp[100]=4
dp[011]=1|2=3
dp[111]=3|4=7
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> subsetOr(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> dp(1 << n, 0);
    for (int mask = 1; mask < (1 << n); mask++) {
        int i = __builtin_ctz(mask);
        dp[mask] = dp[mask ^ (1 << i)] | a[i];
    }
    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto dp = subsetOr({1, 2, 4});
    cout << dp[7] << "\n"; // 7
    return 0;
}
```

**Jebakan:** `ctz(0)`. Identitas AND bukan 0.

**Kompleksitas:** `O(2^n)`.

---

## Tabel uji file 15

| Soal | Input | Jawaban |
|---|---|---|
| TSP 4 kota | matriks 10/15/20/35/25/30 | 80 |
| Assignment 2×2 | `[[4,1],[2,3]]` | 3 |
| Hamilton garis 3 | 0-1-2 | 2 jalur |
| SOS n=2 | a=`1,2,4,8` | `1,3,5,15` |
| Digit sum=4 | `[1,13]` | 2 |
| MIS pohon | nilai 3,2,1,4 | 7 |
| Tree knapsack | (1,5)+(1,3) W=2 | 8 |
| Reroot jarak | garis 3 | 3 2 3 |
| Matching jalur 4 | | 2 |
| CHT kuadrat | h=`1,3,6` | dp akhir 13 |
| Knuth 1,1,1,1 | | 8 |
| Knuth 10,20,30 | | 90 |

---

## Urutan belajar folder 09

1. Day 141–142: kalimat STATE, dua gaya evaluasi.
2. Day 143: tangga, robber, frog, Kadane.
3. Day 144–147: koin dan semua knapsack; hafalkan arah loop.
4. Day 148: LIS `max(dp)` lalu tails.
5. Day 149–151: tabel 2 string, grid DAG, interval + `len`.
6. Day 152–153: parent vs banding ulang; rolling merusak jejak.
7. Day 155–159: tambah dimensi, bitmask, SOS, digit.
8. Day 160–162: DFS anak dulu, lalu reroot.
9. Day 244 / 248: CHT dan Knuth hanya setelah `O(n^2)` / `O(n^3)` terasa.

Kembali ke [13](13-dp-prinsip-1d-knapsack.md) jika STATE masih kabur. Lanjut struktur data di [16](16-segtree-bit-sparse-mo.md).
