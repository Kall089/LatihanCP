# 20 — Knapsack pada pohon (Day 161)

[← Tree DP](19-tree.md) · [README](README.md) · [Reroot →](21-reroot.md)

> **Satu kalimat:** kapasitas `W` dibagi ke anak-anak; menggabung dua subtree = konvolusi knapsack.

Day ComprogLearning: **161**. Lanjut dari [19](19-tree.md) (status 0/1) dan [05](05-01-knapsack.md) (ambil/tidak + kapasitas).

Tiga pertanyaan:

```
1. STATE     : dp[u][w] = nilai max di subtree u memakai kapasitas w
2. TRANSISI  : tmp[a+b] = cur[a] + dp_anak[b]
3. BASIS     : daun hanya "ambil u" atau "tidak"
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Mengapa konvolusi](#mengapa-konvolusi)
- [Proses angka kecil](#proses-angka-kecil)
- [Proses tiga anak](#proses-tiga-anak)
- [Ambil u wajib / opsional](#ambil-u-wajib--opsional)
- [Merge by size](#merge-by-size)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Setiap simpul punya biaya `cost[u]` dan nilai `val[u]`. Memilih simpul memakai kapasitas. Constraint tambahan: pilihan di satu subtree **independen** terhadap subtree saudara, kecuali mereka berbagi sisa kapasitas ayah.

Ayah punya sisa `W`. Setelah (mungkin) membayar `cost[u]`, sisa dibagi ke anak-anak. Tidak peduli cara membagi, kita mau nilai total maksimum.

Menggabungkan anak `v` ke rekap `u` yang sudah memuat saudara sebelumnya:

```
nxt[k] = max atas i+j = k dari (cur[i] + dp[v][j])
```

Itu konvolusi `(max, +)` dua array knapsack.

Analoginya: tas ayah, tiap cabang toko boleh diisi sebagian ruang. Menggabung dua daftar "ruang → keuntungan" seperti menjumlah dua knapsack.

Naif: tiap merge `O(W^2)`, `n` merge → `O(n W^2)`. Untuk `n, W ≤ 200` hidup; `n = 2000, W = 2000` mati.

---

## Kapan

**Kapan dipakai.**

| Gejala | Pakai |
|---|---|
| pohon + kapasitas + pilih simpul | knapsack pohon |
| "pilih paling banyak k simpul di subtree" | `W = k`, cost = 1 |
| group / backpack on tree | sama |
| hanya ambil/tidak tanpa `W` | [19](19-tree.md) cukup |
| array biasa, bukan pohon | [05](05-01-knapsack.md) |

**Kapan tidak.**

1. `n * W^2 > 1e8` tanpa merge-by-size atau batasan khusus.
2. Kapasitas pada **sisi** (aliran) — itu flow, bukan knapsack ini.
3. Harus mereroot setiap `W` — biasanya terlalu mahal.

---

## STATE TRANSISI BASIS

**STATE:** `dp[u][w]` = nilai maksimum yang bisa dikumpulkan dari **subtree `u` saja**, memakai total biaya **tepat** `w` (atau paling banyak `w` — pilih satu dan konsisten).

Dua sekolah:

| Definisi | Jawaban | Catatan |
|---|---|---|
| tepat `w` | `max` atas semua `w` | mudah merge |
| paling banyak `w` | `dp[u][W]` | harus isi prefix-max di akhir, atau izinkan "buang sisa" |

File ini memakai **tepat**, lalu `max_element` di akar.

**TRANSISI:**

1. Inisialisasi `cur` untuk simpul `u` sendiri (belum anak):
   - `cur[0] = 0` (tidak ambil u, belum ada anak),
   - jika `cost[u] ≤ W`: `cur[cost[u]] = val[u]` (ambil u saja).
2. Untuk tiap anak `v` (sudah selesai):
   - `nxt[a+b] = max(cur[a] + dp[v][b])` untuk `cur[a]` dan `dp[v][b]` valid,
   - `cur = nxt`.

**BASIS:** daun = langkah 1 saja.

Kalau aturan soal: "kalau ambil ayah, boleh ambil anak; kalau tidak ambil ayah, subtree kosong" — itu **bukan** knapsack bebas. Itu transisi bersyarat (lihat bagian wajib/opsional).

---

## Mengapa konvolusi

Misal ayah sudah menggabung saudara-saudara ke `cur`. `cur[3] = 10` artinya "pakai 3 slot, nilai 10". Anak baru punya `dp[v][2] = 7`. Gabungan 5 slot: `10+7=17`.

Semua pasangan `(i, j)` harus ditinjau karena tidak ada greedy "beri sisa ke anak terkaya" yang selalu benar.

Itu sebabnya `O(W^2)` per anak, bukan `O(W)`.

---

## Proses angka kecil

```
u cost=1 val=5
 └── v cost=1 val=3
W = 2
```

Daun `v`:

```
cur_v[0] = 0
cur_v[1] = 3
dp[v] = [0, 3, -∞]
```

Ayah `u` sebelum merge:

```
cur[0] = 0
cur[1] = 5
```

Merge `v`:

```
0+0 → nxt[0] = 0
0+1 → nxt[1] = 3     (tidak ambil u, ambil v)
1+0 → nxt[1] = max(3, 5) = 5
1+1 → nxt[2] = 5+3 = 8
```

`dp[u] = [0, 5, 8]`. Jawaban `8`.

Cek manual: {(u,v)} biaya 2 nilai 8; {u} = 5; {v} = 3; {} = 0.

---

## Proses tiga anak

```
      u (cost 0, val 0)     // "akar palsu", hanya pembagi
     / | \
   a   b   c
  2/4  3/5  1/2             // cost/val
W = 4
```

Akar cost 0: `cur[0] = 0`.

Merge a: `dp[a] = [0, -∞, 4, ...]`

```
nxt[0]=0, nxt[2]=4
```

Merge b: `dp[b][3]=5`

```
0+0=0
0+3=5
2+0=4
2+3=7 → w=5 > 4 terbuang
```

Merge c: `dp[c][1]=2`

```
0+1=2
3+1=7
2+1=6
4? tidak ada
```

Kandidat max: 7 (b+c: 3+1) atau 4 (hanya a) atau 5 (hanya b). `a+c` = 2+1=3, nilai 4+2=6. Jawaban 7.

Tanpa konvolusi, greedy "ambil paling besar val/cost" bisa pilih a+c = 6 < 7.

---

## Ambil u wajib / opsional

Tiga model soal yang sering tertukar.

### Model A — bebas

Setiap simpul independen, kapasitas global. Pohon hanya "tempat duduk" (jarang; biasanya array biasa cukup). Merge tetap sama.

### Model B — subtree utuh jika pilih u

Kadang: memilih `u` membuka hak memilih di anak. Tidak memilih `u` ⇒ tidak boleh pilih keturunan.

**STATE:** `dp[u][w][0/1]` atau dua array `tanpaU`, `denganU`.

**TRANSISI kasar:**

- `tanpaU`: hanya 0 (subtree kosong),
- `denganU`: bayar `cost[u]`, lalu konvolusi anak (anak boleh tanpa/dengan sesuai aturan).

### Model C — connected knapsack (pilih komponen terhubung)

Himpunan terpilih harus terhubung. Biasanya: pilih "akar" komponen di `u`, lalu tiap anak boleh tidak diambil (putus) atau diambil dengan knapsack bersambung.

Ini lebih berat. State sering `dp[u][k]` = max jika `u` diambil dan tepat `k` simpul terhubung di subtree.

**TRANSISI:** merge anak: `j` simpul dari anak yang dipilih (harus termasuk anak itu), atau 0 jika anak diputus.

File ini mengimplementasikan **model A/B campuran yang paling sering:** setiap simpul boleh diambil bebas, kapasitas dijumlah. Itu cukup untuk "pilih k simpul di pohon" tanpa syarat keterhubungan. Untuk connected, lihat komentar di kode `dfsConnected`.

---

## Merge by size

**Teori:** jika `dp[u]` hanya diisi sampai `min(W, sz[u] * maxCost)` atau sampai `sz[u]` saat cost = 1, merge kecil-ke-besar / urutan hati-hati membuat setiap pasangan (simpul, kapasitas) tidak terlalu sering.

Kasus klasik **cost = 1**, pilih paling banyak `k` simpul, `k ≤ n`:

`dp[u][j]` = max nilai memakai `j` simpul di subtree.

Merge anak berukuran `s1`, `s2`: loop `i ≤ s1`, `j ≤ s2`, total per merge `O(s1 s2)`. Jumlah over pohon `O(n^2)` terburuk, tapi jika kita batasi `j ≤ k` dan `k` kecil, `O(n k)`.

Ide "setiap pasangan ancestor-descendant terbatas": saat cost 1 dan kita selalu loop sampai ukuran subtree aktual, total `O(n^2)`. Dengan `k` sebagai cap, `O(n k)`.

**Kapan:** `k ≤ 500`, `n ≤ 5000` atau `n k ≤ 1e7`.

**STATE:** `dp[u][j]` untuk `j = 0..min(k, sz[u])`.

**TRANSISI:** sama, tapi batas loop `sz`.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

void dfsKnapsackClean(int u, int p, int W, const vector<vector<int>>& g,
                      const vector<int>& cost, const vector<ll>& val,
                      vector<vector<ll>>& dp) {
    vector<ll> cur(W + 1, NEG);
    cur[0] = 0;
    if (cost[u] <= W) cur[cost[u]] = max(cur[cost[u]], val[u]);
    for (int v : g[u]) {
        if (v == p) continue;
        dfsKnapsackClean(v, u, W, g, cost, val, dp);
        vector<ll> nxt(W + 1, NEG);
        for (int a = 0; a <= W; a++) {
            if (cur[a] <= NEG / 2) continue;
            for (int b = 0; a + b <= W; b++) {
                if (dp[v][b] <= NEG / 2) continue;
                nxt[a + b] = max(nxt[a + b], cur[a] + dp[v][b]);
            }
        }
        cur.swap(nxt);
    }
    dp[u] = cur;
}

ll treeKnapsack(const vector<vector<int>>& g, const vector<int>& cost,
                const vector<ll>& val, int W, int root = 0) {
    int n = (int)g.size();
    vector<vector<ll>> dp(n, vector<ll>(W + 1, NEG));
    dfsKnapsackClean(root, -1, W, g, cost, val, dp);
    return *max_element(dp[root].begin(), dp[root].end());
}

// cost = 1, pilih paling banyak K simpul
void dfsPickK(int u, int p, int K, const vector<vector<int>>& g,
              const vector<ll>& val, vector<int>& sz,
              vector<vector<ll>>& dp) {
    sz[u] = 1;
    dp[u].assign(2, NEG);
    dp[u][0] = 0;
    dp[u][1] = val[u];
    for (int v : g[u]) {
        if (v == p) continue;
        dfsPickK(v, u, K, g, val, sz, dp);
        int s1 = min(K, (int)dp[u].size() - 1);
        int s2 = min(K, (int)dp[v].size() - 1);
        vector<ll> nxt(min(K, s1 + s2) + 1, NEG);
        for (int a = 0; a <= s1; a++) {
            if (dp[u][a] <= NEG / 2) continue;
            for (int b = 0; b <= s2 && a + b < (int)nxt.size(); b++) {
                if (dp[v][b] <= NEG / 2) continue;
                nxt[a + b] = max(nxt[a + b], dp[u][a] + dp[v][b]);
            }
        }
        dp[u].swap(nxt);
        sz[u] += sz[v];
    }
}

ll pickKOnTree(const vector<vector<int>>& g, const vector<ll>& val, int K) {
    int n = (int)g.size();
    vector<int> sz(n);
    vector<vector<ll>> dp(n);
    dfsPickK(0, -1, K, g, val, sz, dp);
    ll ans = NEG;
    for (ll x : dp[0]) ans = max(ans, x);
    return ans;
}

int main() {
    FASTIO;
    vector<vector<int>> g(2);
    g[0].push_back(1);
    g[1].push_back(0);
    cout << treeKnapsack(g, {1, 1}, {5, 3}, 2) << "\n"; // 8
    cout << pickKOnTree(g, {5, 3}, 2) << "\n";           // 8
    return 0;
}
```

Catatan: `dfsKnapsack` pertama di atas sengaja tidak dipakai (`main` memanggil `dfsKnapsackClean`). Jangan salin fungsi rusak itu ke kontes — itu contoh mengapa kerangka harus **satu** DFS bersih.

Connected knapsack (sketsa, cost 1, `u` wajib diambil):

```cpp
void dfsConnected(int u, int p, int K, const vector<vector<int>>& g,
                  const vector<ll>& val, vector<vector<ll>>& dp) {
    dp[u].assign(2, NEG);
    dp[u][1] = val[u]; // u diambil, ukuran 1
    for (int v : g[u]) {
        if (v == p) continue;
        dfsConnected(v, u, K, g, val, dp);
        int s1 = (int)dp[u].size() - 1;
        int s2 = (int)dp[v].size() - 1;
        vector<ll> nxt(min(K, s1 + s2) + 1, NEG);
        for (int a = 1; a <= s1; a++) {          // u sudah masuk
            if (dp[u][a] <= NEG / 2) continue;
            nxt[a] = max(nxt[a], dp[u][a]);      // putus anak v
            for (int b = 1; b <= s2 && a + b < (int)nxt.size(); b++) {
                if (dp[v][b] <= NEG / 2) continue;
                nxt[a + b] = max(nxt[a + b], dp[u][a] + dp[v][b]);
            }
        }
        dp[u].swap(nxt);
    }
}
```

Jawaban connected: max `dp[u][k]` atas semua `u` (akar komponen), atau hanya dari akar tetap jika komponen harus memuat akar.

---

## Jebakan

1. **Tidak memakai `NEG`.** `0 + 0` menimpa slot yang seharusnya mustahil. Inisialisasi `-∞`, izinkan `0` hanya untuk kapasitas 0 kosong.

2. **Kapasitas "tepat" vs "paling banyak".** Kalau jawaban harus `dp[root][W]` padahal definisi tepat, slot `W` mungkin kosong padahal `W-1` sah. Ambil `max` atau isi prefix.

3. **Merge sebelum anak selesai.**

4. **Dobel-hitung `val[u]`.** `val[u]` hanya di inisialisasi `u`, bukan lagi saat merge anak.

5. **`O(n W^2)` tanpa cek constraint.** Hitung dulu.

6. **Connected vs bebas.** Soal "kelompok terhubung" vs "sebarang subset".

7. **`int` jumlah nilai.** `n * 1e9` → `ll`.

8. **Loop `a+b ≤ W` tapi `nxt` tidak diisi `-∞`.** Sampah.

9. **Menyalin `dp[u] = dp[v]`.** Harus konvolusi, bukan salin.

10. **Akar cost besar.** Kalau `cost[root] > W`, masih bisa tidak mengambil root (model bebas).

---

## Kompleksitas

| Varian | Waktu | Memori |
|---|---|---|
| naif tepat `W` | `O(n W^2)` | `O(n W)` |
| rolling: simpan `dp` anak, `cur` ayah | `O(n W^2)` | `O(n W)` tetap jika `dp` disimpan; bisa `O(W)` per frame rekursi + simpan hasil anak |
| cost 1, cap `K` | `O(n K^2)` terburuk, sering `O(n K)` dengan ukuran | `O(n K)` |
| connected sketsa | sama | sama |

Batas:

| n | W | naif |
|---|---|---|
| 100 | 100 | 1e8 longgar? `100*10000=1e6` | 
| 200 | 200 | `200*40000=8e6` |
| 400 | 400 | `400*160000=6.4e7` pas |
| 1000 | 1000 | `1e9` TLE |

`O(n W)` memori: `n=400, W=400`, `ll` ≈ 1.3 MB. `n=2000, W=2000` ≈ 32 MB.

---

## Tabel uji

| Pohon | cost | val | W | Jawaban |
|---|---|---|---|---|
| u-v | 1,1 | 5,3 | 2 | 8 |
| u-v | 1,1 | 5,3 | 1 | 5 |
| u-v | 1,1 | 5,3 | 0 | 0 |
| bintang 3 daun | 0 + 2,3,1 | 0 + 4,5,2 | 4 | 7 |
| satu simpul | 5 | 10 | 4 | 0 |
| satu simpul | 5 | 10 | 5 | 10 |

Brute `n ≤ 12`: mask simpul, cek jumlah cost, (opsional) cek terhubung.

```cpp
ll bruteFree(const vector<int>& cost, const vector<ll>& val, int W) {
    int n = (int)cost.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int c = 0;
        ll v = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) {
                c += cost[i];
                v += val[i];
            }
        if (c <= W) best = max(best, v);
    }
    return best;
}
```

Pada pohon, `treeKnapsack` model bebas harus sama dengan `bruteFree` (pohon tidak mengubah himpunan yang diizinkan). Kalau tidak sama, bug merge. Kalau soal connected, brute harus cek induced / konektivitas.

---

## Checklist

1. STATE menyebut **subtree** dan **kapasitas**.
2. `NEG` untuk slot mustahil.
3. DFS anak sebelum konvolusi.
4. `val[u]` sekali.
5. Jawaban `max` seluruh slot jika definisi "tepat".
6. Hitung `n W^2`.
7. Model bebas vs connected vs "ayah wajib".
8. `ll`.

---

## Prefix-max jika soal minta "paling banyak W"

Setelah DFS:

```cpp
void toAtMost(vector<ll>& row) {
    for (int i = 1; i < (int)row.size(); i++)
        row[i] = max(row[i], row[i - 1]);
}
```

Atau izinkan transisi `nxt[k] = max(nxt[k], cur[k])` "buang anak" — itu sudah ada jika `dp[v][0] = 0`.

`dp[v][0] = 0` berarti "tidak memakai apa pun di subtree v", sama dengan membuang anak. Jangan sekaligus prefix-max di tengah merge — bisa dobel arti.

---

## Hubungan dengan file lain

| File | Peran |
|---|---|
| [05](05-01-knapsack.md) | satu tas, array barang |
| [07](07-bounded-knapsack.md) | stok terbatas, pecah biner |
| [19](19-tree.md) | tanpa kapasitas, status 0/1 |
| [21](21-reroot.md) | setiap akar, biasanya tanpa `W^2` |
| [23](23-bitset.md) | knapsack boolean, bukan pohon |

---

## Simulasi merge dua baris

`cur = [0, 5, −∞]`, `anak = [0, 3, −∞]`, `W=2`:

```
a=0,b=0 → nxt[0]=0
a=0,b=1 → nxt[1]=3
a=1,b=0 → nxt[1]=max(3,5)=5
a=1,b=1 → nxt[2]=8
```

Tanpa skip `NEG`, `a=2` sampah + 3 merusak `nxt[3]` di luar `W`.

---

## Ringkasan dinding

```
cur = knapsack hanya u
for anak v:
    nxt[a+b] = cur[a] + dp[v][b]
    cur = nxt
dp[u] = cur
waktu naif O(n W^2)
```
