# 19 — Tree DP (Day 160)

[← Digit DP](18-digit.md) · [README](README.md) · [Knapsack pohon →](20-knapsack-pohon.md)

> **Satu kalimat:** akarkan pohon, DFS anak selesai sebelum ayah, gabung jawaban subtree.

Day ComprogLearning: **160**. File ini size, independent set, matching, plus diameter sebagai latihan pola. Bukan HLD / LCA — itu folder 11.

Tiga pertanyaan:

```
1. STATE     : dp[u][...] = jawaban di subtree u dengan status u
2. TRANSISI  : gabung anak satu per satu (jumlah / max)
3. BASIS     : daun tidak punya anak
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [Kerangka DFS](#kerangka-dfs)
- [Ukuran subtree](#ukuran-subtree)
- [Independent set](#independent-set)
- [Matching pada pohon](#matching-pada-pohon)
- [Diameter](#diameter)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Pohon = graf terhubung tanpa siklus. Pilih satu akar (biasanya 1 atau 0). Setiap sisi mengarah "jauh dari akar" secara logika. Subtree `u` = `u` plus semua keturunan.

Tree DP menghitung sesuatu di subtree, lalu ayah hanya melihat **ringkasan** anak-anaknya. Itu optimal substructure: setelah anak selesai, ayah tidak perlu tahu bentuk dalam subtree.

Analoginya: kantor cabang mengirim rekap ke kantor pusat, bukan seluruh daftar karyawan mentah.

Pohon tak berarah di input. Saat DFS, **skip parent** agar tidak jalan balik. Itu menggantikan "arah".

Kalau graf punya siklus, kerangka ini salah: "subtree" tidak terdefinisi. Itu DP bitmask, flow, atau bukan DP.

---

## Kapan

**Kapan dipakai.**

| Soal | Pola |
|---|---|
| ukuran / jumlah / XOR subtree | satu nilai per simpul |
| pilih simpul, tetangga tidak boleh bareng | independent set `dp[u][0/1]` |
| pilih sisi, tiap simpul ≤ 1 sisi | matching `dp[u][0/1]` |
| jalur terpanjang | diameter: dua cabang terbaik |
| pewarnaan / ambil k dari subtree | knapsack pohon → [20](20-knapsack-pohon.md) |
| jawaban untuk **setiap** akar | reroot → [21](21-reroot.md) |

**Kapan tidak.**

1. Input bukan pohon (ada siklus / tidak terhubung tanpa disebutkan komponen).
2. Hanya jarak dua simpul berulang — LCA, bukan tree DP.
3. `n ≤ 16` pada graf lengkap — bitmask.

---

## Kerangka DFS

```cpp
void dfs(int u, int p) {
    // inisialisasi basis u
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        // gabung dp[v] ke dp[u]
    }
}
```

Urutan: **rekursi dulu, gabung kemudian**. Jangan gabung sebelum anak selesai.

Jika pohon tidak terhubung (hutan): panggil DFS pada setiap akar komponen.

---

## Ukuran subtree

**Teori:** `sz[u] = 1 + Σ sz[v]` atas anak. Paling dasar, sering jadi bahan rumus lain.

**Kapan:** "berapa simpul di bawah u", centroid kasar, reroot jarak.

**STATE:** `sz[u]` = banyak simpul di subtree `u` (termasuk `u`).

**TRANSISI:** `sz[u] += sz[v]` untuk tiap anak `v`.

**BASIS:** daun `sz[u] = 1`.

**Proses angka:**

```
    0
   / \
  1   2
  |
  3

sz[3]=1
sz[1]=2
sz[2]=1
sz[0]=4
```

**Kode modular:** lihat `dfsSize` di bawah.

**Jebakan:** lupa `sz[u] = 1` sebelum loop. `sz` ayah memakai anak yang belum di-DFS.

**Kompleksitas:** `O(n)`.

---

## Independent set

**Teori:** Pilih himpunan simpul, tidak ada dua yang bertetangga, jumlah nilai maksimum (atau banyak cara). Jika `u` diambil, semua anak **wajib tidak** diambil. Jika `u` tidak diambil, tiap anak bebas.

Analoginya: pilih karyawan rapat, atasan dan bawahan langsung tidak boleh ikut bersama.

**Kapan:** "maximum weight independent set on a tree", CSES Tree Matching varian simpul, house robber pada pohon.

**STATE:**

- `dp[u][0]` = nilai max di subtree `u` jika `u` **tidak** diambil,
- `dp[u][1]` = nilai max jika `u` **diambil**.

**TRANSISI:**

```
dp[u][0] = Σ_v max(dp[v][0], dp[v][1])
dp[u][1] = a[u] + Σ_v dp[v][0]
```

**BASIS:** daun: `dp[u][0] = 0`, `dp[u][1] = a[u]`.

**Proses angka:**

```
      1 (nilai 3)
     / \
   2(2) 3(1)
    |
   4(4)

daun 4: (0, 4)
daun 3: (0, 1)
simpul 2: 0 = max(0,4)=4 ; 1 = 2+0=2  → (4, 2)
simpul 1: 0 = 4 + 1 = 5
          1 = 3 + 4 + 0 = 7
jawaban max(5, 7) = 7   (ambil 1 dan 4)
```

Ambil 2 dan 3 dan? 2+1=3, lebih kecil. Ambil 4 dan 3: 4+1=5. Ambil 4 dan 1: 7. Benar.

Jawaban global: `max(dp[root][0], dp[root][1])`.

Banyak cara (bukan nilai): ganti `max` jadi `+`, `a[u]` jadi `1` jika hanya hitung himpunan, atau kalikan cara anak. Hati-hati: `dp[u][0]` mengalikan `(cara0[v] + cara1[v])`.

---

## Matching pada pohon

**Teori:** Matching = himpunan sisi tanpa dua sisi berbagi simpul. Di pohon, untuk `u`:

- tidak memasangkan `u` ke anak mana pun: jumlahkan matching max tiap anak (anak boleh terpasang ke bawah),
- atau pasangkan `u` ke **tepat satu** anak `v`: sisi `u-v` terpakai, `v` **tidak** boleh terpasang ke bawah, anak lain bebas.

**STATE:**

- `dp[u][0]` = matching max (jumlah sisi) di subtree jika `u` **masih bebas**,
- `dp[u][1]` = matching max jika `u` **sudah dipasangkan ke salah satu anak**.

Kadang cukup satu nilai `best[u] = max(dp[u][0], dp[u][1])` plus `dp[u][0]`.

**TRANSISI:**

```
sum = Σ_v max(dp[v][0], dp[v][1])
dp[u][0] = sum
dp[u][1] = max atas v dari
           1 + dp[v][0] + (sum - max(dp[v][0], dp[v][1]))
```

**BASIS:** daun: keduanya 0 (tidak ada sisi).

**Proses angka: jalur 4 simpul** `0-1-2-3`.

```
3 daun: (0,0)
2: sum = 0, dp0=0, dp1 = 1+0+0 = 1     → max 1
1: anak 2: max=1, dp0=1
   pasang ke 2: 1 + dp[2][0]=0 + 0 = 1 → max 1
0: anak 1: max=1, dp0=1
   pasang ke 1: 1 + dp[1][0]=1 + 0 = 2 → max 2
```

Matching max jalur 4 simpul = 2. Benar.

**Proses: bintang** pusat + 3 daun. Matching max = 1.

```
daun (0,0)
pusat: sum=0, dp0=0
  pilih satu daun: 1+0+0=1
  max = 1
```

**Jebakan:** memasangkan `u` ke dua anak. Memakai `dp[v][1]` saat sisi `u-v` dipakai — `v` sudah "penuh" ke bawah, tidak bisa ke ayah.

---

## Diameter

**Teori:** jalur terpanjang. Di tiap `u`, simpan jalur turun terpanjang. Diameter yang **puncaknya** `u` = dua jalur turun terbaik dijumlah (plus bobot sisi). Global = max over `u`.

**STATE:** fungsi mengembalikan "tinggi" (jalur turun max dari `u`). `ans` global di-update sebagai efek samping.

**TRANSISI:** untuk tiap anak, `d = down(v) + w(u,v)`. Pertahankan `best1`, `best2`. `ans = max(ans, best1+best2)`. Return `best1`.

**BASIS:** daun return 0.

**Proses:** garis 0-1-2 bobot 1.

```
2: down=0
1: best1=1, ans=1, return 1
0: best1=2, ans=2, return 2
diameter 2
```

Ini bukan independent set, tapi pola "gabung anak + efek lewat u" sama.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void dfsSize(int u, int p, const vector<vector<int>>& g, vector<int>& sz) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfsSize(v, u, g, sz);
        sz[u] += sz[v];
    }
}

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

int treeMatching(const vector<vector<int>>& g, int root = 0) {
    int n = (int)g.size();
    vector<array<int, 2>> dp(n);
    dfsMatch(root, -1, g, dp);
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
        } else if (d > best2) {
            best2 = d;
        }
    }
    ans = max(ans, best1 + best2);
    return best1;
}

ll treeDiameter(const vector<vector<pair<int, ll>>>& g) {
    ll ans = 0;
    if (g.empty()) return 0;
    diameterDown(0, -1, g, ans);
    return ans;
}

void addEdge(vector<vector<int>>& g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int main() {
    FASTIO;
    int n = 4;
    vector<vector<int>> g(n);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    vector<ll> a = {3, 2, 1, 4};
    cout << maxIndependentSet(g, a) << "\n"; // 7

    vector<vector<int>> path(4);
    addEdge(path, 0, 1);
    addEdge(path, 1, 2);
    addEdge(path, 2, 3);
    cout << treeMatching(path) << "\n"; // 2

    vector<int> sz(n);
    dfsSize(0, -1, g, sz);
    cout << sz[0] << " " << sz[1] << "\n"; // 4 2
    return 0;
}
```

Banyak cara independent set (mod `MOD`), nilai simpul tidak dipakai:

```cpp
const ll MOD = 1000000007LL;

void dfsISways(int u, int p, const vector<vector<int>>& g,
               vector<array<ll, 2>>& dp) {
    dp[u][0] = 1; // tidak ambil u, awal perkalian
    dp[u][1] = 1; // ambil u
    for (int v : g[u]) {
        if (v == p) continue;
        dfsISways(v, u, g, dp);
        dp[u][0] = dp[u][0] * ((dp[v][0] + dp[v][1]) % MOD) % MOD;
        dp[u][1] = dp[u][1] * dp[v][0] % MOD;
    }
}
```

Jawaban `(dp[root][0] + dp[root][1]) % MOD` termasuk himpunan kosong.

---

## Jebakan

1. **Tidak skip parent.** Recursion tak hingga, RE / TLE.

2. **`dp[u][1] += max(anak)`.** Kalau `u` diambil, anak **tidak** boleh diambil. Wajib `dp[v][0]`.

3. **Matching: `dp[v][1]` saat sisi `u-v`.** `v` sudah terpasang ke bawah, tidak bisa ke `u`. Pakai `dp[v][0]`.

4. **Akar 1-based vs 0-based.** Input `n` simpul 1..n: buat `g(n+1)` atau geser `-1`. Campur = WA diam.

5. **Hutan.** Satu DFS dari 0 hanya satu komponen. Loop `if (sz[u]==0) dfs(u)`.

6. **Bobot sisi vs bobot simpul.** Independent set biasanya bobot simpul. Matching biasanya jumlah sisi atau jumlah bobot sisi.

7. **Update ayah sebelum anak kembali.** Semua gabungan setelah `dfs(v)`.

8. **Overflow.** `n = 2e5`, nilai `1e9` → `ll`.

9. **Diameter hanya tinggi.** Tinggi ≠ diameter. Perlu dua cabang.

10. **Mengakar ulang tiap query.** Kalau butuh semua akar, jangan `O(n^2)` DFS; pakai [21](21-reroot.md).

---

## Kompleksitas

Semua pola di file ini: **O(n)** waktu, **O(n)** memori (rekursi + array).

`n ≤ 2e5` aman. Recursion depth `n` pada garis lurus: di C++, stack bisa meledak. Beberapa judge 256 MB stack; kalau RE di garis, beri `dfs` iteratif atau `std::function` tetap dalam, naik stack: compile tidak membantu — tulis DFS dengan stack manual, atau `ulimit` tidak ada di judge.

Untuk `n = 2e5` garis, banyak solusi rekursif masih lolos di C++17 64-bit. Tetap waspada.

Matching: dua loop anak = `O(derajat(u))` per simpul, total `O(n)`.

---

## Tabel uji

| Pola | Pohon | Nilai | Jawaban |
|---|---|---|---|
| size | 0-1, 0-2, 1-3 | — | sz[0]=4 |
| MIS | nilai 3,2,1,4 | seperti di atas | 7 |
| MIS | satu simpul 10 | 10 | 10 |
| MIS | dua simpul 5-6 | — | 6 |
| matching | jalur 4 | — | 2 |
| matching | bintang 4 simpul | — | 1 |
| matching | satu sisi | — | 1 |
| diameter | garis 3, bobot 1 | — | 2 |

Brute MIS `n ≤ 16`: coba semua mask, cek sisi.

```cpp
ll bruteMIS(const vector<vector<int>>& g, const vector<ll>& a) {
    int n = (int)g.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int u = 0; u < n && ok; u++) {
            if (!((mask >> u) & 1)) continue;
            for (int v : g[u])
                if ((mask >> v) & 1) ok = false;
        }
        if (!ok) continue;
        ll s = 0;
        for (int u = 0; u < n; u++)
            if ((mask >> u) & 1) s += a[u];
        best = max(best, s);
    }
    return best;
}
```

Samakan dengan `maxIndependentSet` pada pohon acak kecil.

---

## Checklist

1. Kalimat STATE menyebut **subtree** dan **status u**.
2. Setiap loop tetangga punya `if (v == p)`.
3. Anak di-DFS sebelum gabung.
4. Independent set: ambil u → hanya `dp[v][0]`.
5. Matching: pasang u-v → hanya `dp[v][0]` + sisi 1.
6. Jawaban `max` dua status di akar, bukan hanya `dp[root][1]`.
7. `ll` untuk jumlah nilai.
8. Hutan: semua komponen.

Lanjut kapasitas dibagi anak: [20](20-knapsack-pohon.md). Semua akar: [21](21-reroot.md).

---

## Varian: "ambil u atau tidak" plus nilai sisi

Kadang sisi punya bonus jika tepat satu ujung diambil. Itu masih dua status, tapi transisi menambah `w(u,v)` saat status u dan v berbeda. Tulis di kertas dulu:

```
gabung anak v:
  baru[0] = max( lama[0]+dp[v][0], lama[0]+dp[v][1]+w )
  baru[1] = max( lama[1]+dp[v][0]+w, lama[1]+dp[v][1] )
```

Jangan mengarang di editor. Simulasi pohon 2 simpul.

---

## Varian: k-path / jarak ≤ 2

Kalau larangan "tidak boleh dua simpul berjarak ≤ 2", state `0/1` tidak cukup. Perlu status "u diambil / anak ada yang diambil / bersih". Itu file [14-state-lanjut](14-state-lanjut.md) diterapkan di pohon: **tambah dimensi yang tepat**, bukan menebak 5 dimensi.

Uji: garis 3 simpul nilai 1,1,1. Independent set biasa = 2. Larangan jarak ≤ 2 = 1.

---

## Rekonstruksi independent set

Setelah `dfsIS`, jejak: jika `dp[root][1] >= dp[root][0]`, ambil akar, lalu semua anak wajib status 0. Jika tidak ambil `u`, tiap anak pilih argmax.

```cpp
void traceIS(int u, int p, int ambil, const vector<vector<int>>& g,
             const vector<array<ll, 2>>& dp, vector<int>& out) {
    if (ambil) out.push_back(u);
    for (int v : g[u]) {
        if (v == p) continue;
        if (ambil) traceIS(v, u, 0, g, dp, out);
        else {
            int pilih = dp[v][1] >= dp[v][0];
            traceIS(v, u, pilih, g, dp, out);
        }
    }
}
```

Uji pohon contoh nilai 3,2,1,4: jejak harus `{0, 3}` (simpul 1 dan 4 jika 1-based). Jumlah 7.

---

## Pewarnaan 2 warna di pohon

Pohon selalu bipartit. `dp` tidak wajib, cukup BFS warna. DP muncul jika **≥ 3 warna** dengan larangan tetangga: `dp[u][c]` = cara mewarnai subtree, `u` warna `c`.

```
dp[u][c] = Π_v (Σ_{d≠c} dp[v][d])
```

`k` warna, `O(n k^2)` naif, `O(n k)` dengan precompute jumlah.

Ini masih pola "anak selesai, ayah kalikan".

---

## Ringkasan dinding

```
dfs(u, p):
  inisialisasi u
  for v anak:
      dfs(v, u)
      gabung
MIS:  (tidak, ambil) = (Σ max anak,  a[u]+Σ anak[0])
Match: bebas = Σ max;  pasang = 1 + v[0] + Σ lainnya
```
