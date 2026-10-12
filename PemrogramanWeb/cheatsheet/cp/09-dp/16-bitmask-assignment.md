# 16 — Assignment bitmask: biaya min, hitung permutasi

[← 15-bitmask-tsp](15-bitmask-tsp.md) · [README](README.md) · [17-sos →](17-sos.md)

Day **157**. `n` orang, `n` tugas, satu orang satu tugas. Itu permutasi. Brute `n!` mati di `n=12`. DP: mask = himpunan tugas yang sudah diisi; orang ke-`popcount(mask)` yang menyusul. Tidak perlu `dp[mask_orang][mask_tugas]`.

> **Satu kalimat:** `dp[mask]` = biaya / banyak cara menugaskan `popcount(mask)` orang pertama ke tepat tugas-tugas di `mask`.

Beda dengan TSP: tidak ada "kota terakhir". Transisi O(n) per mask → `O(2^n n)`. `n ≤ 20` nyaman, `n=22` ketat.

## Daftar isi

- [Model penugasan](#model-penugasan)
- [Assignment biaya minimum](#assignment-biaya-minimum)
- [Assignment maksimum](#assignment-maksimum)
- [Rekonstruksi pasangan](#rekonstruksi-pasangan)
- [Hitung permutasi dengan larangan](#hitung-permutasi-dengan-larangan)
- [Kompatibilitas 0/1](#kompatibilitas-01)
- [n orang ≠ m tugas](#n-orang--m-tugas)
- [Kapan Hungarian](#kapan-hungarian)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Model penugasan

**Teori:** Matching sempurna pada graf bipartit lengkap berbobot. Orang diurutkan 0..n-1 supaya state hanya mask tugas. Analoginya mengisi formulir dari atas: baris ke-`i` memilih kolom yang masih kosong. Urutan orang tetap; yang dienumerasi hanya pilihan kolom — itu cukup karena setiap matching muncul tepat sekali (orang i selalu dipasang di tahap `popcount = i`).

TSP butuh `u` terakhir karena biaya sisi bergantung pada dari mana. Assignment: biaya `c[i][j]` hanya bergantung pada pasangan, bukan urutan pengisian.

**Kapan:** `n ≤ 20`, AtCoder DP-O, "assign jobs", "min cost permutation". **Tidak:** `n=200` → Hungarian `O(n³)` / MCMF. TSP (ada urutan keliling).

**STATE:** `dp[mask]` jawaban untuk tugas `mask` sudah diisi oleh orang `0..popcount-1`.

**TRANSISI:** orang `i = popcount(mask)` memilih `j` kosong:

```
dp[mask | (1<<j)] ⋆=  dp[mask] + c[i][j]
```

`⋆` = `min`, `max`, atau `+` (cara).

**BASIS:** `dp[0] = 0` (min/max biaya) atau `1` (cara).

**Proses (table):** 2 orang, biaya

```
     t0  t1
o0    4   1
o1    2   3
```

| mask | i=pop | pilihan | dp |
|---|---|---|---|
| 00 | 0 | — | 0 |
| 01 (t0) |  | o0 ambil t0 | 4 |
| 10 (t1) |  | o0 ambil t1 | 1 |
| 11 | 1 | dari 01 + t1: 4+3=7; dari 10 + t0: 1+2=3 | **3** |

Matching optimal: o0-t1, o1-t0.

**Kode modular:** kamus bit sama [15](15-bitmask-tsp.md).

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int pop(int mask) { return __builtin_popcount(mask); }

int main() {
    FASTIO;
    cout << pop(5) << '\n'; // 2
    return 0;
}
```

**Jebakan:** memakai orang `j` (indeks tugas) sebagai baris biaya. Dua mask: orang dan tugas — 4^n, bunuh diri.

**Kompleksitas:** kerangka `O(2^n n)`.

---

## Assignment biaya minimum

**Teori:** Relaksasi `min`. Sentinel `INF`. Setiap mask dijangkau dari mask dengan satu bit lebih kecil; loop `mask` 0..2^n-1 otomatis topologis.

**Kapan:** min cost matching n×n. **Tidak:** maksimisasi dengan sentinel `INF` (salah arah).

**STATE:** `dp[mask]` biaya min.

**TRANSISI:** `dp[mask|(1<<j)] = min(..., dp[mask] + c[i][j])` untuk `j` kosong, `i=popcount(mask)`.

**BASIS:** `dp[0] = 0`, lain `INF`.

**Proses (table):** 3×3

```
  8  4  7
  5  2  4
  3  6  5
```

Hitung bertahap. Mask 000 = 0.

Orang 0 mengisi satu tugas:

| mask | tugas | dp |
|---|---|---|
| 001 | t0 | 8 |
| 010 | t1 | 4 |
| 100 | t2 | 7 |

Orang 1, contoh mask 011 = {t0,t1}:

| dari | tambah | biaya |
|---|---|---|
| 001 + t1 | 8+2 | 10 |
| 010 + t0 | 4+5 | 9 |

`dp[011] = 9`.

Lanjut sampai 111. Satu matching bagus: o0-t1 (4), o1-t2 (4), o2-t0 (3) = 11. Cek: o0-t1 (4), o1-t0 (5), o2-t2 (5) = 14 lebih mahal. o0-t2 (7)+o1-t1 (2)+o2-t0 (3)=12. Minimum 11.

Verifikasi lengkap dengan fungsi `assignmentMask`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll assignmentMask(const vector<vector<ll>>& c) {
    int n = (int)c.size();
    int N = 1 << n;
    vector<ll> dp(N, INF);
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
        if (dp[mask] >= INF) continue;
        int i = __builtin_popcount(mask);
        if (i == n) continue;
        for (int j = 0; j < n; j++) {
            if ((mask >> j) & 1) continue;
            dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + c[i][j]);
        }
    }
    return dp[N - 1];
}

int main() {
    FASTIO;
    vector<vector<ll>> c2 = {{4, 1}, {2, 3}};
    cout << assignmentMask(c2) << '\n'; // 3
    vector<vector<ll>> c3 = {{8, 4, 7}, {5, 2, 4}, {3, 6, 5}};
    cout << assignmentMask(c3) << '\n'; // 11
    return 0;
}
```

**Jebakan:** `i` dihitung `j` atau `ctz`. `c` bukan persegi. Skip `INF` tidak dilakukan lalu `INF+c` overflow. `n=0` → `dp[0]` ok, `1<<0=1`, `N-1=0`, jawaban 0.

**Kompleksitas:** `O(2^n n)` waktu, `O(2^n)` memori.

---

## Assignment maksimum

**Teori:** Ganti `min` jadi `max`, sentinel `-INF`, basis 0. AtCoder DP-O adalah **hitung**, bukan max; jangan campur.

**Kapan:** "maximum compatibility", "max score assignment". **Tidak:** min cost dengan `-c` jika nilai sudah negatif campur — lebih aman operator `max`.

**STATE:** `dp[mask]` skor max.

**TRANSISI:** `max`.

**BASIS:** `dp[0] = 0`.

**Proses (table):** 2×2 `[[4,1],[2,3]]`. Max = 4+3=7 (o0-t0, o1-t1), bukan 3.

| mask | dp max |
|---|---|
| 00 | 0 |
| 01 | 4 |
| 10 | 1 |
| 11 | max(4+3, 1+2)=7 |

**Kode modular:**

```cpp
ll assignmentMax(const vector<vector<ll>>& c) {
    int n = (int)c.size(), N = 1 << n;
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
```

**Jebakan:** inisialisasi `INF`. Tidak skip `-INF` lalu `-INF + c` masih `-INF` (ok) kecuali overflow. Mencetak `dp[0]`.

**Kompleksitas:** sama.

---

## Rekonstruksi pasangan

**Teori:** `choice[nmask] = j` tugas yang baru dipilih, atau banding ulang: dari `full`, orang `n-1` mencoba `j` nyala, cek `dp[full] == dp[full^(1<<j)] + c[n-1][j]`. Mundur `i`.

**Kapan:** minta pasangan. **Tidak:** hanya angka.

**STATE:** `pair[i] = j`.

**TRANSISI mundur:** cari `j` yang menjelaskan nilai.

**BASIS:** mask 0.

**Proses (table):** 2×2 min, `dp[11]=3` dari `10 + c[1][0]`. Orang 1 → t0. Mask sisa `10`, orang 0 → t1. Pasangan `(0,1), (1,0)`.

**Kode modular:**

```cpp
pair<ll, vector<int>> assignmentPairs(const vector<vector<ll>>& c) {
    int n = (int)c.size(), N = 1 << n;
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
    vector<int> who(n, -1);
    int mask = N - 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++)
            if ((mask >> j) & 1) {
                int prev = mask ^ (1 << j);
                if (dp[prev] < INF && dp[mask] == dp[prev] + c[i][j]) {
                    who[i] = j;
                    mask = prev;
                    break;
                }
            }
    }
    return {dp[N - 1], who};
}
```

**Jebakan:** `who[j]=i` tertukar. Seri dua `j`: ambil yang pertama. Rolling tidak relevan (1D mask harus utuh).

**Kompleksitas:** isi `O(2^n n)`, jejak `O(n²)`.

---

## Hitung permutasi dengan larangan

**Teori:** Banyak bijeksi `π` dengan syarat `ok[i][π(i)]`. Sama assignment, operator `+`, `c[i][j]` diganti 0/1 (boleh/tidak). `dp[mask] += dp[prev]` jika `ok[i][j]`. AtCoder DP-O Matching.

Permutasi tanpa larangan: `dp[full] = n!`. Dengan larangan: derangement adalah kasus `ok[i][i]=false`.

**Kapan:** "count permutations such that", matching count, derangement n≤20. **Tidak:** n=1e6 derangement (rumus inklusi / rekuren `!n`).

**STATE:** `dp[mask]` banyak cara.

**TRANSISI:** `if (ok[i][j]) dp[nmask] = (dp[nmask] + dp[mask]) % MOD`.

**BASIS:** `dp[0] = 1`.

**Proses (table):** 2×2 semua boleh.

| mask | cara |
|---|---|
| 00 | 1 |
| 01 | 1 |
| 10 | 1 |
| 11 | 1+1=2 |

`2! = 2`.

Larangan diagonal (derangement n=2): `ok = [[0,1],[1,0]]`.

| mask | cara |
|---|---|
| 00 | 1 |
| 01 | 0 (o0 tidak boleh t0) |
| 10 | 1 (o0-t1) |
| 11 | dari 10, o1-t0 boleh → 1 |

`!2 = 1`. n=3 derangement = 2.

n=3 semua boleh: 6.

n=3, orang 0 tidak boleh tugas 0:

Hitung dengan kode; kira-kira `3! - 2! = 4` (bukan inklusi penuh jika hanya satu larangan: ya, `n! * (1-1/n) = 4`).

**Kode modular:**

```cpp
ll countAssignment(const vector<vector<int>>& ok) {
    int n = (int)ok.size(), N = 1 << n;
    vector<ll> dp(N, 0);
    dp[0] = 1;
    for (int mask = 0; mask < N; mask++) {
        if (!dp[mask]) continue;
        int i = __builtin_popcount(mask);
        if (i == n) continue;
        for (int j = 0; j < n; j++)
            if (!((mask >> j) & 1) && ok[i][j])
                dp[mask | (1 << j)] = (dp[mask | (1 << j)] + dp[mask]) % MOD;
    }
    return dp[N - 1];
}

ll countPermutationsConstrained(int n, const vector<pair<int, int>>& forbidden) {
    vector<vector<int>> ok(n, vector<int>(n, 1));
    for (auto [i, j] : forbidden) ok[i][j] = 0;
    return countAssignment(ok);
}

ll derangementMask(int n) {
    vector<vector<int>> ok(n, vector<int>(n, 1));
    for (int i = 0; i < n; i++) ok[i][i] = 0;
    return countAssignment(ok);
}

int main() {
    FASTIO;
    cout << derangementMask(2) << ' ' << derangementMask(3) << '\n'; // 1 2
    vector<vector<int>> all2 = {{1, 1}, {1, 1}};
    cout << countAssignment(all2) << '\n'; // 2
    return 0;
}
```

**Jebakan:** basis 0. Lupa `% MOD`. `ok[j][i]`. Menghitung derangement n=20 dengan rekursi `!n` lebih baik untuk **tanpa** larangan lain; campuran larangan tetap bitmask.

**Kompleksitas:** `O(2^n n)`.

---

## Kompatibilitas 0/1

**Teori:** Kadang `ok[i][j]` dari bit `a[i] & (1<<j)` (AtCoder DP-O: wanita bit). Baca input jadi matriks boolean, lalu `countAssignment`. Jangan DP langsung pada bit wanita tanpa popcount orang.

**Kapan:** input bitmask per baris. **Tidak:** mengira mask input = mask DP.

**STATE:** sama `dp[mask]`.

**TRANSISI:** `if ((a[i] >> j) & 1)`.

**BASIS:** 1.

**Proses (table):** n=3, `a = [7, 7, 7]` semua kompatibel → 6. `a = [2, 2, 2]` hanya tugas 1 → 0 (dua orang berebut).

`a = [6, 5, 3]` = o0:{1,2}, o1:{0,2}, o2:{0,1}. Ini permutasi tanpa titik tetap? 6=`110` tidak ada 0, 5=`101` tidak ada 1, 3=`011` tidak ada 2 — derangement. Jawaban 2.

**Kode modular:**

```cpp
ll countFromBits(const vector<int>& a) {
    int n = (int)a.size();
    vector<vector<int>> ok(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ok[i][j] = (a[i] >> j) & 1;
    return countAssignment(ok);
}
```

**Jebakan:** `a[i]` 1-indexed bit. `n=21` `int` mask tugas masih 21 bit — `1<<n` overflow int: `N` wajib `int` dengan `n<=30` hati-hati, `1<<31` UB. `n<=20` aman jika `N = 1<<n` pada `int` untuk n<=30 kecuali 31.

**Kompleksitas:** sama plus O(n²) bangun `ok`.

---

## n orang ≠ m tugas

**Teori:** Jika `n < m`, orang tetap 0..n-1, mask tugas `2^m`, jawab `min` atas mask berukuran n (tidak wajib semua tugas). Jika `n > m`, tukar peran atau pad `c` dengan baris dummy biaya 0 / INF sesuai "wajib terpakai".

`O(2^m n)` mensyaratkan `m ≤ 20`. Jika `n ≤ 20 < m`, mask **orang** dan loop tugas — sama ide, tukar.

**Kapan:** "assign each worker one job, leftover jobs ok". **Tidak:** `m=40` tanpa MITM.

**STATE:** `dp[mask]` mask di sisi yang lebih kecil.

**TRANSISI:** popcount = berapa yang sudah dipasang.

**BASIS:** 0.

**Proses (table):** 2 orang, 3 tugas, biaya

```
1 5 2
4 1 3
```

Mask berukuran 2, min:

| pasangan | biaya |
|---|---|
| t0,t1 | 1+1=2 |
| t0,t2 | 1+3=4 |
| t1,t2 | 5+3=8 atau 2+1=3 |

Minimum 2.

**Kode modular:**

```cpp
ll assignmentRect(const vector<vector<ll>>& c) {
    int n = (int)c.size(), m = (int)c[0].size();
    if (n > m) return INF; // atau tukar
    int N = 1 << m;
    vector<ll> dp(N, INF);
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
        if (dp[mask] >= INF) continue;
        int i = __builtin_popcount(mask);
        if (i >= n) continue;
        for (int j = 0; j < m; j++)
            if (!((mask >> j) & 1))
                dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + c[i][j]);
    }
    ll ans = INF;
    for (int mask = 0; mask < N; mask++)
        if (__builtin_popcount(mask) == n) ans = min(ans, dp[mask]);
    return ans;
}
```

**Jebakan:** menjawab `dp[2^m-1]` padahal tidak semua tugas wajib. `n>m` tanpa cek.

**Kompleksitas:** `O(2^m n)`.

---

## Kapan Hungarian

**Teori:** Hungarian / Kuhn-Munkres `O(n³)` untuk n≈400. MCMF pada bipartit juga. Bitmask kalah di n=24. Jangan tulis Held-Karp untuk assignment (lebih lambat `n` kali).

| n | senjata |
|---|---|
| ≤ 20 | `assignmentMask` |
| 21–25 | hanya jika TL longgar + `int` + pruning |
| 50–400 | Hungarian |
| 1000+ | greedy khusus / tidak matching umum |

**Kapan:** constraint n. **Tidak:** hafalan satu senjata.

**STATE:** — 

**TRANSISI:** — 

**BASIS:** — 

**Proses (table):** n=15, Waktu bitmask 15*2^15 ≈ 5e5, Hungarian 15³=3375 — keduanya hidup, bitmask lebih pendek diketik.

n=100: bitmask mustahil, Hungarian 1e6 nyaman.

**Kode modular:** tidak ada Hungarian di Day 157; ingat namanya saja.

```cpp
bool pakaiBitmaskAssignment(int n) { return n <= 20; }
```

**Jebakan:** menuliskan TSP `dp[mask][u]` untuk assignment (membuang faktor n memori).

**Kompleksitas:** keputusan O(1).

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

ll assignmentMask(const vector<vector<ll>>& c);
ll assignmentMax(const vector<vector<ll>>& c);
pair<ll, vector<int>> assignmentPairs(const vector<vector<ll>>& c);
ll countAssignment(const vector<vector<int>>& ok);
ll derangementMask(int n);
ll assignmentRect(const vector<vector<ll>>& c);

int main() {
    FASTIO;
    vector<vector<ll>> c = {{4, 1}, {2, 3}};
    cout << assignmentMask(c) << ' ' << assignmentMax(c) << '\n';
    cout << derangementMask(3) << '\n';
    return 0;
}
```

Checklist:

```
1. i = popcount(mask), bukan j
2. min: INF; max: -INF; count: 0 dengan dp[0]=1
3. ok[i][j] sebelum tambah cara
4. n != m → jangan full mask otomatis
5. n > 20 → bukan file ini
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| biaya 7 bukan 3 | max vs min / orang salah | `i=popcount` |
| cara 0 | `dp[0]=0` | `dp[0]=1` |
| cara n! padahal ada larangan | lupa `ok` | filter |
| overflow min | `INF+c` | skip INF |
| RE `1<<n` | n=31 | n≤20 |
| jawaban dummy | `dp[full]` padahal m>n | min mask berukuran n |
| TLE n=22 | 22*4e6 | Hungarian / pruning |
| pasangan terbalik | `who[j]=i` | `who[i]=j` |
| TSP state tersalin | `dp[mask][u]` | `dp[mask]` |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `assignmentMask` | `[[4,1],[2,3]]` | 3 |
| `assignmentMax` | sama | 7 |
| `assignmentMask` | 3×3 `8 4 7 / 5 2 4 / 3 6 5` | 11 |
| `assignmentPairs` | 2×2 min | 3, who `[1,0]` |
| `countAssignment` | 2×2 semua 1 | 2 |
| `derangementMask` | 2 | 1 |
| `derangementMask` | 3 | 2 |
| `derangementMask` | 4 | 9 |
| `countFromBits` | `[6,5,3]` | 2 |
| `assignmentRect` | 2×3 `1 5 2 / 4 1 3` | 2 |
| `countPermutationsConstrained` | n=3, forbid (0,0) | 4 |

SOS (jumlah seluruh subset mask) adalah teknik **berbeda**: bukan matching, melainkan prefix-sum di kubus bit. Lanjut [17-sos](17-sos.md).

Day 154 dan 158+ punya folder latihan sendiri; jangan menyalin `solusi/` ComprogLearning ke cheatsheet ini.
