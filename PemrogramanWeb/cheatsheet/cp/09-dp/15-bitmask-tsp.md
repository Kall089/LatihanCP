# 15 — Bitmask TSP: Held-Karp, Hamilton, kamus bit

[← 14-state-lanjut](14-state-lanjut.md) · [README](README.md) · [16-bitmask-assignment →](16-bitmask-assignment.md)

Day **156**. Himpunan berukuran `n` ada `2^n` buah. Integer menyimpan keanggotaan: bit `i` nyala = elemen `i` sudah dipilih. Analoginya deretan saklar lampu.

> **Satu kalimat:** `dp[mask][u]` = jawaban untuk himpunan `mask` dengan posisi terakhir `u`; transisi menyalakan satu bit baru.

Batas: `n ≤ 16` nyaman untuk `O(2^n n²)`, `n ≤ 20` batas (≈ 4·10^8 operasi, ketat). `n = 24` bukan TSP penuh.

## Daftar isi

- [Kamus operasi bit](#kamus-operasi-bit)
- [Mengapa n ≤ 20](#mengapa-n--20)
- [TSP Held-Karp](#tsp-held-karp)
- [Menutup siklus](#menutup-siklus)
- [Rekonstruksi tur](#rekonstruksi-tur)
- [Hamilton path](#hamilton-path)
- [Hitung jalur Hamilton](#hitung-jalur-hamilton)
- [Varian: start tetap vs bebas](#varian-start-tetap-vs-bebas)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Kamus operasi bit

**Teori:** Bit ke-`i` adalah saklar elemen `i`. Mask adalah himpunan. Operasi di bawah adalah alfabet file 15–16; hafalkan sampai refleks. `1 << i` untuk `i ≥ 31` overflow `int` bertanda — pakai `1LL << i`.

**Kapan:** semua DP himpunan. **Tidak:** `n > 63` dalam satu `ll` (butuh bitset / array).

**STATE:** tidak ada DP di sini; ini kamus.

**TRANSISI / BASIS:** tidak berlaku.

**Proses (table):** `n = 4`, mask `10` = `1010₂` = elemen 1 dan 3.

| tujuan | kode | hasil pada 10 |
|---|---|---|
| nyalakan i=0 | `mask \| (1 << 0)` | 11 (`1011`) |
| matikan i=1 | `mask & ~(1 << 1)` | 8 (`1000`) |
| cek i=3 | `(mask >> 3) & 1` | 1 |
| cek i=2 | `(mask >> 2) & 1` | 0 |
| toggle i=3 | `mask ^ (1 << 3)` | 2 (`0010`) |
| jumlah bit | `__builtin_popcount(mask)` | 2 |
| bit terendah | `mask & -mask` | 2 |
| indeks bit rendah | `__builtin_ctz(mask)` | 1 |

Enumerate subset `T ⊆ S` untuk `S = 13` (`1101₂` = {0,2,3}):

| langkah | t |
|---|---|
| 1 | 13 |
| 2 | 12 |
| 3 | 9 |
| 4 | 8 |
| 5 | 5 |
| 6 | 4 |
| 7 | 1 |
| 8 | 0 |

Rumus loop: `for (int t = s; ; t = (t - 1) & s) { ...; if (!t) break; }`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int on(int mask, int i) { return mask | (1 << i); }
int off(int mask, int i) { return mask & ~(1 << i); }
int has(int mask, int i) { return (mask >> i) & 1; }
int tog(int mask, int i) { return mask ^ (1 << i); }

vector<int> subsetsOf(int s) {
    vector<int> res;
    for (int t = s; ; t = (t - 1) & s) {
        res.push_back(t);
        if (t == 0) break;
    }
    return res;
}

int main() {
    FASTIO;
    cout << has(10, 1) << ' ' << has(10, 2) << '\n';
    for (int t : subsetsOf(13)) cout << t << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** `1 << 31` UB. Loop subset tanpa `if (t==0) break` infinite. `__builtin_ctz(0)` undefined. `popcount` pada `ll` = `__builtin_popcountll`.

**Kompleksitas:** operasi O(1). Enumerate subset `O(2^{|s|})`. Semua mask `O(2^n)`.

---

## Mengapa n ≤ 20

**Teori:** Held-Karp menelusuri setiap pasangan `(mask, u)` dan mencoba `v`. Waktu `O(2^n n²)`. Memori `O(2^n n)`.

**Kapan:** baca constraint `n` sebelum mengetik. **Tidak:** memaksa n=22 "mungkin lolos".

**STATE:** ukuran tabel.

**TRANSISI:** n² per mask.

**BASIS:** — 

**Proses (table):**

| n | 2^n | 2^n n² | 2^n n * 8 byte | status |
|---|---|---|---|---|
| 12 | 4096 | 6e5 | 0.4 MB | longgar |
| 16 | 65536 | 1.7e7 | 8 MB | nyaman |
| 18 | 262144 | 8.5e7 | 38 MB | ok |
| 20 | 1e6 | 4.2e8 | 160 MB | ketat waktu+memori |
| 22 | 4e6 | 2e9 | 700 MB | TLE/MLE |
| 24 | 1.7e7 | 1e10 | 3 GB | tidak |

Hamilton path pada graf jarang: `O(2^n (n+m))` sedikit lebih baik, n=20 masih batas.

**Kode modular:**

```cpp
ll estimasiTSP(int n) {
    ll masks = 1LL << n;
    return masks * n * n;
}
```

**Jebakan:** `vector<vector<ll>> dp(1<<20, vector<ll>(20))` alokasi lambat + fragment. Array statis `int dp[1<<20][20]` lebih rapi jika memori global cukup. Bobot kecil: pakai `int` bukan `ll`.

**Kompleksitas:** hafal tabel, jangan hitung di kertas saat detik terakhir.

---

## TSP Held-Karp

**Teori:** Kelilingi `n` kota, tiap kota sekali, **kembali ke awal**, biaya sisi minimum. Brute `n!` mati di `n=12` (`12! = 479 juta` sudah tanpa kalikan n). Held-Karp: state = himpunan yang sudah dikunjungi + kota sekarang. Bit hanya bertambah, jadi loop `mask` menaik otomatis topologis.

Analoginya keliling pasar: yang penting tas (kota mana saja sudah) dan di kios mana kamu berdiri, bukan urutan lengkap masuk tas.

**Kapan:** `n ≤ 16..20`, graf lengkap atau padat, CSES / klasik TSP. **Tidak:** `n=100` (heuristik, ILP). Pohon (tree DP). DAG tanpa "semua simpul" (topo biasa).

**STATE:** `dp[mask][u]` adalah biaya minimum untuk mengunjungi **tepat** himpunan `mask` dan **saat ini berada di** `u`. Bit `u` wajib nyala.

**TRANSISI:** untuk `v` belum masuk `mask`:

```
dp[mask | (1<<v)][v] = min( ..., dp[mask][u] + w[u][v] )
```

**BASIS:** `dp[1<<s][s] = 0`. Lainnya `INF`. Jangan `dp[0][s]=0`: mask kosong tidak berisi `s`.

**Proses (table):** 4 kota, mulai 0. Bobot tak berarah:

```
     0   1   2   3
0    0  10  15  20
1   10   0  35  25
2   15  35   0  30
3   20  25  30   0
```

Lapisan mask berukuran 1 (hanya start):

| mask | u | dp |
|---|---|---|
| 0001 | 0 | 0 |

Ukuran 2:

| mask | u | dari | dp |
|---|---|---|---|
| 0011 | 1 | 0→1 | 10 |
| 0101 | 2 | 0→2 | 15 |
| 1001 | 3 | 0→3 | 20 |

Ukuran 3, contoh `{0,1,2}=0111`:

| u | kandidat | dp |
|---|---|---|
| 2 | 10+35 (dari 1) | 45 |
| 1 | 15+35 (dari 2) | 50 |

Ukuran 4 `1111`, lalu tutup siklus `+ w[u][0]`:

Tur klasik `0-1-3-2-0 = 10+25+30+15 = 80`.

| last u | dp[1111][u] + w[u][0] |
|---|---|
| 1 | … |
| 2 | … |
| 3 | … |
| min | **80** |

Verifikasi tangan: `0-1-3-2-0 = 80`, `0-1-2-3-0 = 10+35+30+20 = 95`, `0-2-1-3-0 = 15+35+25+20 = 95`, `0-2-3-1-0 = 15+30+25+10 = 80`. Minimum 80.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll tsp(const vector<vector<ll>>& w, int s = 0) {
    int n = (int)w.size();
    int N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));
    dp[1 << s][s] = 0;
    for (int mask = 0; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!((mask >> u) & 1) || dp[mask][u] >= INF) continue;
            for (int v = 0; v < n; v++) {
                if ((mask >> v) & 1) continue;
                int nmask = mask | (1 << v);
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + w[u][v]);
            }
        }
    }
    ll ans = INF;
    int full = N - 1;
    for (int u = 0; u < n; u++)
        if (dp[full][u] < INF) ans = min(ans, dp[full][u] + w[u][s]);
    return ans;
}

int main() {
    FASTIO;
    vector<vector<ll>> w = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << tsp(w) << '\n'; // 80
    return 0;
}
```

**Jebakan:**

1. Tidak menutup siklus (`+ w[u][s]`).
2. `dp[0][s] = 0`.
3. Loop `v` yang sudah di mask (kota dobel).
4. Sisi tak ada: `w[u][v]` harus `INF`, jangan 0 (kecuali loop `u==v`).
5. `INF + w` overflow: cek `dp[mask][u] >= INF` sebelum tambah.

**Kompleksitas:** `O(2^n n²)` waktu, `O(2^n n)` memori.

---

## Menutup siklus

**Teori:** Hamilton **cycle** = path yang mengunjungi semua + sisi pulang. Tanpa sisi pulang kamu menjawab path. Soal "round trip" wajib langkah extra. Jika graf berarah, `w[u][s]` mungkin ≠ `w[s][u]`.

**Kapan:** kata "kembali", "tour", "cycle". **Tidak:** "path visiting all".

**STATE:** sama; jawaban `min_u dp[full][u] + w[u][s]`.

**TRANSISI:** satu kali di luar loop utama.

**BASIS:** start `s` sama dengan ujung pulang.

**Proses (table):** 3 kota garis? Tidak ada siklus Hamilton jika tidak lengkap. Matriks lengkap 3 kota sama 1:

`dp[111][u] = 2` (dua sisi), pulang +1 = 3. Setiap tur panjang 3.

**Kode modular:** potongan di `tsp`. Versi path:

```cpp
ll hamiltonPathCost(const vector<vector<ll>>& w, int s = 0) {
    // sama seperti tsp tanpa + w[u][s]
    int n = (int)w.size(), N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));
    dp[1 << s][s] = 0;
    for (int mask = 0; mask < N; mask++)
        for (int u = 0; u < n; u++) {
            if (!((mask >> u) & 1) || dp[mask][u] >= INF) continue;
            for (int v = 0; v < n; v++)
                if (!((mask >> v) & 1))
                    dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + w[u][v]);
        }
    ll ans = INF;
    for (int u = 0; u < n; u++) ans = min(ans, dp[N - 1][u]);
    return ans;
}
```

**Jebakan:** path memakai rumus cycle. Cycle dengan `s` berubah-ubah: pilih satu `s` saja (simetri), atau `n` kali start jika sisi tidak lengkap dari semua titik — biasanya satu `s` cukup pada graf lengkap tak berarah.

**Kompleksitas:** sama.

---

## Rekonstruksi tur

**Teori:** `par[nmask][v] = u` saat relaksasi. Mundur dari `(full, last)` dengan `last` yang meminimalkan `dp+w[u][s]`, matikan bit `cur`, lompat ke `par`. Reverse, tambah `s` di ekor.

**Kapan:** minta urutan kota. **Tidak:** hanya biaya.

**STATE:** `par[mask][v]`.

**TRANSISI:** update ketat `<` agar jejak stabil.

**BASIS:** `par[1<<s][s] = -1`.

**Proses (table):** tur 80: `0-1-3-2-0`.

| mundur mask | cur | par | mask baru |
|---|---|---|---|
| 1111 | 2 | 3 | 1011 |
| 1011 | 3 | 1 | 0011 |
| 0011 | 1 | 0 | 0001 |
| 0001 | 0 | -1 | — |

Path `2,3,1,0` → reverse `0,1,3,2` + pulang `0`.

**Kode modular:**

```cpp
pair<ll, vector<int>> tspPath(const vector<vector<ll>>& w, int s = 0) {
    int n = (int)w.size(), N = 1 << n;
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
```

**Jebakan:** `mask ^= 1<<cur` sebelum baca `par` (par butuh mask lama). Lupa append start. `last` tetap `s` jika semua `INF`.

**Kompleksitas:** isi sama, jejak `O(n)`.

---

## Hamilton path

**Teori:** Kunjungi setiap simpul sekali, **tidak** wajib pulang. Graf boleh jarang: iterasi tetangga, bukan `v=0..n-1`. CSES Hamiltonian Flights: berarah, hitung cara 1→n mengunjungi semua.

**Kapan:** "visit each vertex once", path. **Tidak:** cycle (tutup). `n>20`.

**STATE:** `dp[mask][u]` biaya atau cara, berakhir di `u`.

**TRANSISI:** `u → v` jika `v` belum di mask.

**BASIS:** `dp[1<<s][s] = 0` (biaya) atau `1` (cara). Beberapa soal: basis semua `i` (start bebas).

**Proses (table):** garis tak berarah `0-1-2`.

Biaya sisi 1, start 0:

| mask | u | dp |
|---|---|---|
| 001 | 0 | 0 |
| 011 | 1 | 1 |
| 111 | 2 | 2 |

Satu path `0-1-2` biaya 2. Start bebas: juga `2-1-0`.

**Kode modular:** lihat `hamiltonPathCost`. Graf daftar tetangga di bagian hitung.

**Jebakan:** menghitung `0-1-2` dan `2-1-0` sebagai sama pada soal berarah. Sisi balik tak ada.

**Kompleksitas:** padat `O(2^n n²)`, jarang `O(2^n n + 2^n m)` kira-kira `O(2^n (n+m))`.

---

## Hitung jalur Hamilton

**Teori:** Ganti `min` menjadi `+`. Modulo. Basis 1. Jawaban jumlah `dp[full][u]` atau hanya `u = n-1`.

**Kapan:** CSES Hamiltonian Flights, "number of Hamiltonian paths". **Tidak:** biaya min.

**STATE:** `dp[mask][u]` banyak path.

**TRANSISI:** `dp[nmask][v] += dp[mask][u]`.

**BASIS:** `dp[1<<i][i] = 1` untuk start yang diizinkan.

**Proses (table):** garis 0-1-2 tak berarah, start mana saja, full path:

```
dp[001][0]=1
dp[010][1]=1
dp[100][2]=1
dp[011][1] += dari 0
dp[011][0] += dari 1
...
full: 0-1-2 dan 2-1-0 → 2
```

Segitiga lengkap 3 simpul tak berarah: `3! = 6` path (setiap permutasi). Cycle directed? Hati-hati dobel.

**Kode modular:**

```cpp
ll countHamilton(const vector<vector<int>>& g) {
    int n = (int)g.size(), N = 1 << n;
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
    for (int u = 0; u < n; u++) ans = (ans + dp[N - 1][u]) % MOD;
    return ans;
}

ll countHamiltonFixed(const vector<vector<int>>& g, int s, int t) {
    int n = (int)g.size(), N = 1 << n;
    vector<vector<ll>> dp(N, vector<ll>(n, 0));
    dp[1 << s][s] = 1;
    for (int mask = 0; mask < N; mask++)
        for (int u = 0; u < n; u++) {
            if (!dp[mask][u]) continue;
            for (int v : g[u]) {
                if ((mask >> v) & 1) continue;
                dp[mask | (1 << v)][v] = (dp[mask | (1 << v)][v] + dp[mask][u]) % MOD;
            }
        }
    return dp[N - 1][t];
}
```

**Jebakan:** lupa modulo. Start semua + jawab semua = 2× directed pair. Graf tak berarah: tiap undirected path dihitung dua arah — baca soal.

**Kompleksitas:** sama orde TSP.

---

## Varian: start tetap vs bebas

**Teori:** Graf lengkap tak berarah: tur adalah siklus, pilih start 0 menekan simetri n (setiap tur dihitung n kali jika start bebas). Graf berarah / tidak lengkap: start ditentukan soal.

Path "antara sembarang pasangan": `min` atas semua `dp[full][u]` setelah basis semua `i`, atau `n` kali Held-Karp — mahal. Satu kali dengan basis semua start: `dp[1<<i][i]=0` untuk semua `i` **salah** jika kamu men-min-kan campuran start di mask yang sama — sebenarnya sah untuk path (mask mencatat siapa yang sudah, start implisit). Untuk cycle, campur start merusak sisi pulang.

**Kapan:** baca "starts at 1", "any city". **Tidak:** menyalin basis dari editorial lain.

**STATE:** sama.

**TRANSISI:** sama.

**BASIS:** satu bit vs semua bit tunggal.

**Proses (table):**

| soal | basis | jawaban |
|---|---|---|
| TSP start 0 | `dp[1][0]=0` | min_u dp[full][u]+w[u][0] |
| path start 0 end bebas | sama | min_u dp[full][u] |
| path start 0 end n-1 | sama | dp[full][n-1] |
| path start bebas | semua `dp[1<<i][i]=0` | min_u dp[full][u] |
| hitung 1→n semua kota | `dp[1][0]=1` | dp[full][n-1] |

**Kode modular:** parameter `s` pada `tsp`.

**Jebakan:** cycle + basis semua start + pulang ke 0: tur yang tidak lewat logika start 0 tetap punya `w[u][0]`. Boleh, tetapi setiap tur dihitung sekali dari prefiks yang kebetulan dibangun dari 0... berantakan. Tetap satu start.

**Kompleksitas:** tidak berubah.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

int on(int mask, int i);
int off(int mask, int i);
int has(int mask, int i);
ll tsp(const vector<vector<ll>>& w, int s);
pair<ll, vector<int>> tspPath(const vector<vector<ll>>& w, int s);
ll hamiltonPathCost(const vector<vector<ll>>& w, int s);
ll countHamilton(const vector<vector<int>>& g);

int main() {
    FASTIO;
    vector<vector<ll>> w = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << tsp(w) << '\n';
    return 0;
}
```

Checklist n=20:

```
1. int vs ll pada dp
2. array datar dp[mask*n+u]
3. skip INF
4. tutup siklus?
5. 1LL<<i
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| TSP 60 bukan 80 | tidak pulang | `+w[u][s]` |
| TSP 0 | `dp[0][s]=0` + sisi 0 | basis `1<<s` |
| kota dobel | tidak cek bit v | `if (mask>>v&1)` |
| overflow negatif | `INF+w` | skip INF |
| RE shift | `1<<31` | `1LL` |
| MLE n=20 | `vector<vector<ll>>` | `int` / array |
| path 2× | undirected count | baca soal |
| loop subset hang | lupa break di 0 | `if(!t) break` |
| `ctz(0)` | mask kosong | jangan |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `has(10,1)` |  | 1 |
| `subsetsOf(13)` |  | 13 12 9 8 5 4 1 0 |
| `tsp` | matriks 4 kota | 80 |
| `tspPath` | sama | 80, `0 1 3 2 0` |
| `hamiltonPathCost` | sama, start 0 | 50? 0-1-3-2 = 10+25+30=65; 0-1-2-3=10+35+30=75; 0-2-3-1=15+30+25=70; 0-3-1-2=20+25+35=80; min **65** |
| `countHamilton` | garis 3 | 2 |
| `countHamiltonFixed` | garis, 0→2 | 1 |
| `estimasiTSP(16)` |  | 16777216 |

Penugasan orang-tugas (matching berbobot kecil) memakai mask **tanpa** kota terakhir: [16-bitmask-assignment](16-bitmask-assignment.md).
