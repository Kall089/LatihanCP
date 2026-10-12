# 21 — Rerooting (Day 162)

[← Knapsack pohon](20-knapsack-pohon.md) · [README](README.md) · [Probabilitas →](22-probabilitas.md)

> **Satu kalimat:** dua DFS — pertama rekap subtree, kedua pindahkan akar dan sesuaikan kontribusi yang keluar/masuk.

Day ComprogLearning: **162**. Satu akar sudah cukup di [19](19-tree.md). File ini untuk **setiap** simpul sebagai akar, tanpa `O(n^2)`.

Tiga pertanyaan:

```
1. STATE     : down[u] = agregat subtree; ans[u] = agregat seluruh pohon jika u akar
2. TRANSISI  : up_v = (ans[u] minus kontribusi v) digabung sisa
3. BASIS     : daun down=identitas; ans[root]=down[root]
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Jumlah jarak](#jumlah-jarak)
- [Proses: garis 3 simpul](#proses-garis-3-simpul)
- [Proses: bintang](#proses-bintang)
- [Pohon berbobot](#pohon-berbobot)
- [Agregat max](#agregat-max)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Banyak soal: "jika ibu kota di `u`, berapa jumlah jarak / ukuran komponen / nilai DP?". DFS sekali hanya mengisi untuk satu akar.

Naif: akar-kan tiap `u`, DFS `O(n)` → `O(n^2)`. Untuk `n = 1e5` mati.

Reroot: pindah akar dari `u` ke anak `v` hanya mengubah:

- subtree `v` **keluar** dari "bawah `u`",
- sisa pohon **masuk** sebagai anak baru `v`.

Kalau agregat bisa **dikurangi** (sum) atau **dihitung ulang dari 2-3 kandidat** (max), perpindahan `O(1)` atau `O(derajat)` — total `O(n)`.

Analoginya: kamu sudah tahu statistik rumah di kota A. Pindah ke kota tetangga: keluarkan angka kampung yang sekarang jadi "luar", masukkan angka kota lama sebagai "satu cabang".

Dua fase:

1. `dfs1` dari akar sembarang: `sz`, `down` (hanya subtree).
2. `dfs2`: `ans[root] = down[root]`; saat turun ke `v`, hitung `up` dari `ans[u]` dan `down[v]`.

---

## Kapan

**Kapan dipakai.**

| Soal | Agregat |
|---|---|
| jumlah jarak ke semua simpul, untuk setiap u | sum + size |
| "jika akar = u, berapa jawaban tree DP" | reroot status 0/1 (lebih hati-hati) |
| max jarak dari u (eccentricity) | max, perlu 2 terbaik |
| jumlah pasangan / warna di seluruh pohon vs u | sum |

**Kapan tidak.**

1. Hanya satu akar — satu DFS.
2. Agregat tidak bisa di-invers (hash aneh, min+max campur tanpa kandidat).
3. Graf bukan pohon.
4. Perlu semua *ordered pairs* dengan path query — kadang centroid / LCA.

---

## STATE TRANSISI BASIS

Contoh kanonik: jumlah jarak (tiap sisi bobot 1).

**STATE:**

- `sz[u]` = ukuran subtree `u` (akar sementara),
- `down[u]` = jumlah jarak dari `u` ke semua simpul di subtree `u`,
- `ans[u]` = jumlah jarak dari `u` ke **semua** simpul di pohon, seolah `u` akar.

**TRANSISI dfs1:**

```
sz[u] = 1 + Σ sz[v]
down[u] = Σ (down[v] + sz[v])
```

Alasan `+ sz[v]`: setiap simpul di subtree `v` bertambah 1 (sisi `u-v`).

**TRANSISI dfs2** (pindah `u → v`):

```
sisa = ans[u] - (down[v] + sz[v])
up   = sisa + (n - sz[v])
ans[v] = down[v] + up
```

`sisa` = jumlah jarak dari `u` ke simpul di luar subtree `v`.
Setiap simpul luar, saat akar pindah ke `v`, jaraknya **bertambah 1** (lewat `v-u`). Ada `n - sz[v]` simpul luar.

**BASIS:** daun `sz=1`, `down=0`. `ans[root] = down[root]`.

---

## Jumlah jarak

Rumus `down[u] = Σ (down[v] + sz[v])` adalah pohon berbobot 1.

Verifikasi di daun: tidak ada suku, 0. Di ayah daun: `0 + 1 = 1`, yaitu jarak ke satu anak.

`ans[u]` selalu `down` (yang di bawah) plus `up` (yang di atas, termasuk saudara).

---

## Proses: garis 3 simpul

```
0 — 1 — 2     n = 3
akar sementara = 0
```

dfs1:

```
sz[2]=1  down[2]=0
sz[1]=2  down[1]=0+1=1
sz[0]=3  down[0]=1+2=3
ans[0]=3
```

Jarak dari 0: ke1=1, ke2=2, jumlah 3. Cocok.

Reroot ke 1:

```
kontribusi v=1 dari sudut 0: down[1]+sz[1]=1+2=3
sisa = 3-3=0          // tidak ada simpul di "sisi lain" 0 selain subtree 1? 
                      // tunggu: subtree 1 berisi 1 dan 2, luar = hanya 0?
n-sz[1]=3-2=1
up = 0 + 1 = 1        // jarak dari 1 ke 0
ans[1] = down[1]+1 = 2
```

Jarak dari 1: ke0=1, ke2=1, jumlah 2. Cocok.

Reroot 1 → 2:

```
kontribusi 2 dari sudut 1: 0+1=1
sisa = ans[1]-1 = 1
n-sz[2]=2
up = 1+2 = 3
ans[2] = 0+3 = 3
```

Simetris dengan 0. Jawaban `3 2 3`.

---

## Proses: bintang

```
      0
    / | \
   1  2  3
n = 4
```

dfs1 dari 0:

```
daun down=0 sz=1
down[0] = (0+1)*3 = 3
ans[0] = 3
```

Reroot ke 1:

```
sisa = 3 - (0+1) = 2
up = 2 + (4-1) = 5
ans[1] = 0+5 = 5
```

Dari daun: jarak ke pusat 1, ke dua daun lain 2+2=4, total 5. Ya.

Semua daun 5. Jawaban `3 5 5 5`.

---

## Pohon berbobot

Sisi `w(u,v)`.

```
down[u] += down[v] + sz[v] * w(u,v)
```

Reroot:

```
kontrib = down[v] + sz[v] * w
sisa = ans[u] - kontrib
up = sisa + (n - sz[v]) * w
ans[v] = down[v] + up
```

**Proses:** 0-1 bobot 3, 1-2 bobot 4. Garis.

```
down[2]=0
down[1]=0+1*4=4
down[0]=4+2*3=10
ans[0]=10   // 3 + (3+4)=10
```

Ke 1:

```
kontrib=4+2*3=10
sisa=0
up=0+1*3=3
ans[1]=4+3=7   // 3 + 4 = 7
```

Ke 2:

```
kontrib=0+1*4=4
sisa=7-4=3
up=3+2*4=11
ans[2]=11   // 4+3 + 4 = 11?  jarak 2→1=4, 2→0=7, jumlah 11
```

---

## Agregat max

Jumlah mudah dikurangi. **Max tidak.**

Contoh: untuk setiap `u`, jarak terpanjang dari `u` (tinggi jika `u` akar, yaitu eccentricity ke bawah+atas).

`down[u]` = max jarak turun.

Saat reroot, `up[v]` = max(

- `up[u] + w(u,v)`,
- max `down[saudara] + w(u,saudara) + w(u,v)`
)

Perlu **dua** jalur turun terbaik di `u`, supaya saat `v` adalah yang terbaik, kita pakai kedua.

**STATE:** `best1[u]`, `best2[u]`, `who1[u]`.

**TRANSISI:** `up_v = max(up_u, (who1==v ? best2 : best1)) + w`.

**BASIS:** `up[root] = 0`. `ans[u] = max(down[u], up[u])`.

Ini tetap `O(n)`: precompute 2 terbaik per simpul di dfs1, dfs2 `O(derajat)`.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    if (n == 0) return ans;
    dfs1(0, -1, g, sz, down);
    ans[0] = down[0];
    dfs2(0, -1, n, g, sz, down, ans);
    return ans;
}

void dfs1w(int u, int p, const vector<vector<pair<int, ll>>>& g,
           vector<int>& sz, vector<ll>& down) {
    sz[u] = 1;
    down[u] = 0;
    for (auto [v, w] : g[u]) {
        if (v == p) continue;
        dfs1w(v, u, g, sz, down);
        sz[u] += sz[v];
        down[u] += down[v] + sz[v] * w;
    }
}

void dfs2w(int u, int p, int n, const vector<vector<pair<int, ll>>>& g,
           const vector<int>& sz, const vector<ll>& down, vector<ll>& ans) {
    for (auto [v, w] : g[u]) {
        if (v == p) continue;
        ll kontrib = down[v] + sz[v] * w;
        ll up = (ans[u] - kontrib) + (n - sz[v]) * w;
        ans[v] = down[v] + up;
        dfs2w(v, u, n, g, sz, down, ans);
    }
}

vector<ll> sumDistWeighted(const vector<vector<pair<int, ll>>>& g) {
    int n = (int)g.size();
    vector<int> sz(n);
    vector<ll> down(n), ans(n);
    dfs1w(0, -1, g, sz, down);
    ans[0] = down[0];
    dfs2w(0, -1, n, g, sz, down, ans);
    return ans;
}

void dfsDownMax(int u, int p, const vector<vector<int>>& g,
                vector<ll>& d1, vector<ll>& d2, vector<int>& who) {
    d1[u] = d2[u] = 0;
    who[u] = -1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfsDownMax(v, u, g, d1, d2, who);
        ll cand = d1[v] + 1;
        if (cand >= d1[u]) {
            d2[u] = d1[u];
            d1[u] = cand;
            who[u] = v;
        } else if (cand > d2[u]) {
            d2[u] = cand;
        }
    }
}

void dfsUpMax(int u, int p, ll up, const vector<vector<int>>& g,
              const vector<ll>& d1, const vector<ll>& d2, const vector<int>& who,
              vector<ll>& ecc) {
    ecc[u] = max(d1[u], up);
    for (int v : g[u]) {
        if (v == p) continue;
        ll other = (who[u] == v) ? d2[u] : d1[u];
        ll nup = max(up, other) + 1;
        dfsUpMax(v, u, nup, g, d1, d2, who, ecc);
    }
}

vector<ll> eccentricityAll(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<ll> d1(n), d2(n), ecc(n);
    vector<int> who(n);
    dfsDownMax(0, -1, g, d1, d2, who);
    dfsUpMax(0, -1, 0, g, d1, d2, who, ecc);
    return ecc;
}

void addEdge(vector<vector<int>>& g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int main() {
    FASTIO;
    vector<vector<int>> line(3);
    addEdge(line, 0, 1);
    addEdge(line, 1, 2);
    for (ll x : sumDistancesAllRoots(line)) cout << x << " ";
    cout << "\n"; // 3 2 3

    vector<vector<int>> star(4);
    addEdge(star, 0, 1);
    addEdge(star, 0, 2);
    addEdge(star, 0, 3);
    for (ll x : sumDistancesAllRoots(star)) cout << x << " ";
    cout << "\n"; // 3 5 5 5

    for (ll x : eccentricityAll(line)) cout << x << " ";
    cout << "\n"; // 2 1 2
    return 0;
}
```

---

## Jebakan

1. **`up` memakai `down[u]` bukan `ans[u]`.** `down[u]` tidak memuat saudara dan atas. Wajib `ans[u]`.

2. **Salah tanda `n - sz[v]`.** Simpul luar ada `n - sz[v]`, termasuk `u`.

3. **Max tanpa 2 terbaik.** Jika `v` adalah cabang terpanjang, `other` harus cabang kedua, bukan `d1` lagi.

4. **Satu simpul.** `ans[0] = 0`. DFS2 tidak loop. Jangan akses `g[0]` kosong dengan rumus aneh.

5. **Hutan.** Reroot per komponen; `n` diganti ukuran komponen.

6. **Overflow.** `n = 2e5`, jarak `n^2` → `2e5 * 2e5 = 4e10`, `ll`.

7. **Bobot lupa dikali `sz`.**

8. **`ans[v]` diisi setelah rekursi.** Harus sebelum `dfs2(v)`, karena anak `v` butuh `ans[v]`.

9. **0-based / 1-based.**

10. **Mencoba reroot knapsack `W` besar.** Biasanya `O(n W)` atau lebih — bukan pola ini.

---

## Kompleksitas

`O(n)` waktu dan memori untuk sum jarak dan eccentricity.

Naif `O(n^2)`: hanya untuk `n ≤ 3000` atau debug.

Reroot tree DP `0/1` (independent set untuk setiap akar): tiap pindah, `ans` ayah tanpa anak `v` dihitung dari precompute prefix/suffix max anak. Tetap `O(n)` jika agregat anak bisa di-prefix.

---

## Tabel uji

| Pohon | Fungsi | Output |
|---|---|---|
| garis 3 | sum dist | `3 2 3` |
| bintang 4 | sum dist | `3 5 5 5` |
| satu simpul | sum dist | `0` |
| garis 3 | eccentricity | `2 1 2` |
| 0-1 w=3, 1-2 w=4 | sum weighted | `10 7 11` |

Brute:

```cpp
vector<ll> bruteSum(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<ll> ans(n);
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans[s] += dist[u];
            for (int v : g[u])
                if (dist[v] < 0) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
        }
    }
    return ans;
}
```

Samakan dengan `sumDistancesAllRoots` pada pohon acak `n ≤ 50`.

---

## Checklist

1. dfs1 selesai sebelum dfs2.
2. `ans[root] = down[root]`.
3. Rumus `ans[u] - kontrib + (n-sz)*w`.
4. `ans[v]` diisi **sebelum** turun.
5. Max: dua kandidat.
6. `ll`.
7. Uji garis 3: `3 2 3`.

---

## Reroot independent set (sketsa)

`down0[u]`, `down1[u]` seperti [19](19-tree.md).

Untuk `ans` di `u` sebagai akar, kita perlu kontribusi "sisa pohon" seolah anak tambahan.

Precompute di `u`: produk / jumlah `max(down0[v], down1[v])` semua anak, plus prefix agar bisa keluarkan `v`.

Saat turun ke `v`:

- virtual parent-as-child: status sisa seolah simpul `u` dengan anak-anak kecuali `v` plus `up`,
- gabung ke `v` seperti anak biasa.

Detailnya mudah salah. Tulis dulu rumus `g(sisa)` identitas: sum vs max vs product. Uji pohon 2 simpul:

```
nilai a,b
akar 0: max(b, a)  —  tidak ambil 0 → boleh ambil 1; ambil 0 → tidak ambil 1
kedua akar harus simetris jika a=b.
```

Kalau hanya butuh satu akar, **jangan** reroot.

---

## Ringkasan dinding

```
dfs1: down[u] = Σ (down[v] + sz[v]*w)
dfs2: up = ans[u] - kontrib + (n-sz[v])*w
      ans[v] = down[v] + up
uji wajib: garis 3 → 3 2 3
```
