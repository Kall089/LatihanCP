# Small-to-large (DSU on tree)

[← Pohon](README.md) · [Diameter & Euler →](diameter-euler.md) · [Tree DP](../09-dp/19-tree.md)

Day 193. Gabungkan himpunan anak ke ayah dengan menyalin yang **kecil ke yang besar**. Tiap nilai pindah O(log n) kali.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Graf 0-indexed. Pohon berakar di 0 kecuali soal menentukan lain.

## Daftar isi

- [Pohon dan himpunan subtree](#pohon-dan-himpunan-subtree)
- [Kenapa log n](#kenapa-log-n)
- [Versi set pointer](#versi-set-pointer)
- [Sack: warisi anak berat](#sack-warisi-anak-berat)
- [Warna unik per subtree](#warna-unik-per-subtree)
- [Jawaban di jalur? Bukan](#jawaban-di-jalur-bukan)
- [Beberapa agregat](#beberapa-agregat)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Pohon dan himpunan subtree

**Teori:** untuk setiap simpul v kamu ingin sesuatu dari **multiset nilai di subtree v**. Naif: tiap v menyalin semua anak. Satu nilai di daun disalin sepanjang jalur ke akar: O(n) per nilai, total O(n²).

Small-to-large: himpunan yang lebih kecil selalu disalin ke yang lebih besar. Setelah gabung, ukuran minimal **dobel**. Satu nilai tidak bisa disalin lebih dari log₂ n kali.

Analogi: tumpukan kertas. Jangan pindahkan tumpukan besar ke yang kecil. Tuang yang kecil ke yang besar.

**Kapan:**

- Pakai: “banyak warna berbeda di subtree”, “jumlah pasangan sama warna di subtree”, query subtree offline.
- Jangan: query jalur u–v — itu [HLD](hld-centroid.md) atau [LCA](lca.md).
- Jangan: update nilai online di tengah — sack offline lebih enak.

**Proses:** n=6, sisi `0-1, 0-2, 1-3, 1-4, 2-5`, warna `[1,2,1,3,2,1]` pada 0..5.

```
        0 (1)
       / \
     1(2) 2(1)
     / \    \
   3(3) 4(2) 5(1)

subtree 3 = {3}        unik 1
subtree 1 = {2,3,2}    unik 2
subtree 2 = {1,1}      unik 1
subtree 0 = {1,2,1,3,2,1} unik 3
```

**Kode:** baca pohon.

```cpp
vector<vector<int>> bacaPohon(int n, istream& in) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        in >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    return g;
}

void dfsSz(int v, int p, const vector<vector<int>>& g, vector<int>& sz) {
    sz[v] = 1;
    for (int u : g[v]) if (u != p) {
        dfsSz(u, v, g, sz);
        sz[v] += sz[u];
    }
}
```

**Jebakan:** DFS tanpa menolak ayah. Soal 1-based lupa −1. n=1: subtree = satu simpul.

**Kompleksitas:** DFS O(n). Gabung himpunan O(n log n) add.

## Kenapa log n

**Teori:** saat nilai x pindah dari himpunan A ke B, |B| ≥ |A| (kita selalu tuang kecil ke besar). Himpunan baru berukuran ≥ 2|A|. Ukuran ≤ n, jadi rantai pindah ≤ log₂ n.

Total: tiap dari n nilai × log n pindahan × biaya satu insert.

**Kapan:** berlaku untuk `std::set` merge, `unordered` hati-hati, atau `cnt` array + sack.

**Proses:** n=8, nilai daun pindah: 1→2→4→8 = 3 kali = log 8.

**Kode:** merge set, pointer ke yang besar.

```cpp
void gabungSet(set<int>*& a, set<int>*& b) {
    if (a->size() < b->size()) swap(a, b);
    a->insert(b->begin(), b->end());
    b->clear();
}
```

Setelah `swap` pointer, ayah memegang set besar tanpa menyalin besar ke kecil.

**Jebakan:** `insert` ke set kecil dari yang besar — O(|besar| log) mematahkan argumen. Wajib `swap` dulu.

**Kompleksitas:** O(n log² n) jika tiap insert `set` O(log n). Sack + array `cnt` O(n log n).

## Versi set pointer

**Teori:** setiap simpul punya `set<int>*`. DFS: gabung anak ke ayah, lalu `ans[v] = set.size()` (unik). Pointer swap menjaga alokasi.

**Kapan:** mudah ditulis, n ≤ 10^5, log² ≈ 18² · n masih sering lolos. Warna sudah unik per kebutuhan set (bukan multiset).

**Proses:** daun 3 set `{3}`, daun 4 `{2}`. Ayah 1: gabung `{3}` ke `{2}` → `{2,3}`, tambah warna 1? Warna simpul 1 adalah 2: `{2,3}`. Unik 2.

Hati-hati: tambah warna **v sendiri** setelah gabung anak.

**Kode:**

```cpp
void dfsSet(int v, int p, const vector<vector<int>>& g,
            const vector<int>& warna, vector<set<int>*>& st, vector<int>& ans) {
    st[v] = new set<int>();
    st[v]->insert(warna[v]);
    for (int u : g[v]) if (u != p) {
        dfsSet(u, v, g, warna, st, ans);
        if (st[v]->size() < st[u]->size()) swap(st[v], st[u]);
        st[v]->insert(st[u]->begin(), st[u]->end());
        delete st[u];
        st[u] = nullptr;
    }
    ans[v] = (int)st[v]->size();
}
```

Versi tanpa `delete` di tengah (lebih aman bocor kecil):

```cpp
vector<int> unikSet(const vector<vector<int>>& g, const vector<int>& warna) {
    int n = (int)g.size();
    vector<set<int>*> st(n, nullptr);
    vector<int> ans(n);
    if (n) dfsSet(0, -1, g, warna, st, ans);
    if (n && st[0]) delete st[0];
    return ans;
}
```

**Jebakan:** `delete` anak lalu ayah masih menunjuk ke sana. Setelah `swap`, hapus yang **kecil** (yang sudah disalin). Double insert warna v di anak dan ayah.

**Kompleksitas:** O(n log² n) waktu, O(n) memori set.

## Sack: warisi anak berat

**Teori:** seperti HLD. Anak **berat** = subtree terbesar. DFS: olah anak ringan dulu (`keep=false`: setelah `ans` dihitung, hapus datanya), lalu anak berat (`keep=true`: data tetap), lalu tambah subtree ringan lagi + simpul v.

Euler tour: subtree = `[tin[v], tout[v]]` inklusif. Tambah/hapus O(ukuran) untuk ringan. Total tetap O(n log n) karena ringan ≤ n/2 berulang.

**Kapan:** `cnt[]` array, agregat lebih kaya dari `set.size()` (jumlah `cnt[c]*cnt[c]`, mode).

**Proses:** pohon contoh. Anak berat 0 adalah 1 (sz 3 > 2).

```
DFS 0:
  anak ringan 2 keep=false
    hitung ans[2], ans[5], hapus warna 2 dan 5
  anak berat 1 keep=true
    mewarisi cnt {2,3,2}
  tambah v=0 warna 1
  tambah ulang subtree 2
  ans[0]=3
  keep akar true: tidak hapus
```

**Kode:** Euler pendek.

```cpp
struct Euler {
    vector<int> tin, tout, id;
    int timer = 0;
    void dfs(int v, int p, const vector<vector<int>>& g) {
        tin[v] = timer;
        id[timer] = v;
        timer++;
        for (int u : g[v]) if (u != p) dfs(u, v, g);
        tout[v] = timer - 1;
    }
};

void dfsHeavy(int v, int p, const vector<vector<int>>& g,
              vector<int>& sz, vector<int>& heavy) {
    sz[v] = 1;
    heavy[v] = -1;
    for (int u : g[v]) if (u != p) {
        dfsHeavy(u, v, g, sz, heavy);
        sz[v] += sz[u];
        if (heavy[v] == -1 || sz[u] > sz[heavy[v]]) heavy[v] = u;
    }
}
```

**Jebakan:** `tout` eksklusif vs inklusif. Daun `tin==tout` pada gaya inklusif. Anak berat tidak dikunjungi `keep=true`.

**Kompleksitas:** O(n log n) add/remove.

## Warna unik per subtree

**Teori:** `cnt[c]++` dari 0 ke 1 → `jenis++`. Remove kebalikan.

**Kapan:** CF/CSES *Tree Queries* warna unik. Kompres warna dulu.

**Proses:** warna `[1,2,1,3,2,1]` sudah kecil. `cnt` berukuran max warna + 1.

Saat di v=1 setelah anak:

```
tambah 1 (warna 2): cnt[2] 0→1 jenis=1
tambah subtree 3: warna 3 jenis=2
tambah subtree 4: warna 2 cnt 1→2 jenis tetap 2
ans[1]=2
```

**Kode:**

```cpp
void tambahWarna(int c, int d, vector<int>& cnt, int& jenis) {
    if (d > 0) {
        if (cnt[c]++ == 0) jenis++;
    } else {
        if (--cnt[c] == 0) jenis--;
    }
}

void dfsSack(int v, int p, bool keep,
             const vector<vector<int>>& g,
             const vector<int>& heavy,
             const vector<int>& tin, const vector<int>& tout,
             const vector<int>& id, const vector<int>& warna,
             vector<int>& cnt, int& jenis, vector<int>& ans) {
    for (int u : g[v])
        if (u != p && u != heavy[v])
            dfsSack(u, v, false, g, heavy, tin, tout, id, warna, cnt, jenis, ans);
    if (heavy[v] != -1)
        dfsSack(heavy[v], v, true, g, heavy, tin, tout, id, warna, cnt, jenis, ans);
    tambahWarna(warna[v], +1, cnt, jenis);
    for (int u : g[v]) if (u != p && u != heavy[v])
        for (int t = tin[u]; t <= tout[u]; t++)
            tambahWarna(warna[id[t]], +1, cnt, jenis);
    ans[v] = jenis;
    if (!keep)
        for (int t = tin[v]; t <= tout[v]; t++)
            tambahWarna(warna[id[t]], -1, cnt, jenis);
}

vector<int> unikSack(const vector<vector<int>>& g, vector<int> warna) {
    int n = (int)g.size();
    vector<int> b = warna;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int& x : warna) x = int(lower_bound(b.begin(), b.end(), x) - b.begin());

    Euler eu;
    eu.tin.assign(n, 0);
    eu.tout.assign(n, 0);
    eu.id.assign(n, 0);
    if (n) eu.dfs(0, -1, g);
    vector<int> sz(n), heavy(n, -1);
    if (n) dfsHeavy(0, -1, g, sz, heavy);
    vector<int> cnt((int)b.size() + 2), ans(n);
    int jenis = 0;
    if (n) dfsSack(0, -1, true, g, heavy, eu.tin, eu.tout, eu.id, warna,
                   cnt, jenis, ans);
    return ans;
}

int main() {
    FASTIO;
    int n = 6;
    vector<vector<int>> g(n);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    vector<int> w = {1, 2, 1, 3, 2, 1};
    auto ans = unikSack(g, w);
    for (int x : ans) cout << x << ' ';     // 3 2 1 1 1 1
    cout << '\n';
}
```

**Jebakan:** menambah v dua kali jika kamu juga iterasi subtree berat. Menghapus anak berat. `keep` akar `false` mengosongkan sebelum kamu baca. Warna 10^9 tanpa kompresi.

**Kompleksitas:** O(n log n).

## Jawaban di jalur? Bukan

**Teori:** sack mengisi `ans[v]` untuk subtree v menurut **akar tetap**. Query jalur 3–5 bukan subtree. `isAncestor` + rumus jalur butuh LCA, bukan small-to-large.

**Kapan:** jika soal “pada jalur”, tutup file ini.

**Proses:** unik pada jalur 3–5 = {3,2,1,1,1} = {1,2,3} = 3. `ans[0]=3` kebetulan sama, bukan alasan memakai sack.

**Kode:** jangan `ans[lca]`.

**Jebakan:** “subtree dari LCA” ≠ jalur. Subtree LCA memuat cabang lain.

**Kompleksitas:** salah algoritma, kompleksitas tidak menolong.

## Beberapa agregat

**Teori:** ganti `jenis`. Contoh: jumlah `cnt[c]^2` di subtree.

```
saat cnt[c]  k → k+1: sum2 += 2k+1
saat k → k-1: sum2 -= 2k-1
```

Mode: pantau `cnt` maksimum dan banyak yang mencapai.

**Kapan:** CF *D. Tree Requests* sejenis.

**Proses:** subtree 1 warna 2,3,2. `cnt[2]=2, cnt[3]=1`, sum2 = 4+1=5.

**Kode:**

```cpp
void tambahSum2(int c, int d, vector<int>& cnt, ll& sum2) {
    ll k = cnt[c];
    if (d > 0) {
        sum2 += 2 * k + 1;
        cnt[c]++;
    } else {
        sum2 -= 2 * k - 1;
        cnt[c]--;
    }
}
```

**Jebakan:** update `sum2` setelah `cnt++` dengan rumus lama. Urutan k harus sebelum ubah `cnt`.

**Kompleksitas:** tetap O(n log n).

## Uji naif

**Teori:** untuk setiap v, masukkan warna subtree ke `set`. Bandingkan sack.

**Kapan:** n ≤ 50.

**Proses:** pohon bintang, pohon rantai, semua warna sama, semua beda.

**Kode:**

```cpp
void kumpul(int v, int p, const vector<vector<int>>& g,
            const vector<int>& w, vector<int>& isi) {
    isi.push_back(w[v]);
    for (int u : g[v]) if (u != p) kumpul(u, v, g, w, isi);
}

int unikNaifV(int v, const vector<vector<int>>& g, const vector<int>& w) {
    vector<int> isi;
    kumpul(v, -1, g, w, isi);
    sort(isi.begin(), isi.end());
    return int(unique(isi.begin(), isi.end()) - isi.begin());
}

bool cek(const vector<vector<int>>& g, const vector<int>& w) {
    auto ans = unikSack(g, w);
    int n = (int)g.size();
    for (int v = 0; v < n; v++)
        if (ans[v] != unikNaifV(v, g, w)) return false;
    return true;
}

int main() {
    FASTIO;
    vector<vector<int>> g(6);
    auto e = [&](int a, int b) { g[a].push_back(b); g[b].push_back(a); };
    e(0, 1); e(0, 2); e(1, 3); e(1, 4); e(2, 5);
    vector<int> w = {1, 2, 1, 3, 2, 1};
    cout << (cek(g, w) ? "ok\n" : "WA\n");
}
```

Catatan: `unikNaifV` DFS dari v dengan `p=-1` merambah **seluruh** pohon jika v bukan akar — salah. Perbaiki: kirim ayah menurut pohon berakar 0, atau kumpulkan lewat `tin/tout`.

```cpp
int unikNaifSub(int v, const Euler& eu, const vector<int>& w) {
    vector<int> isi;
    for (int t = eu.tin[v]; t <= eu.tout[v]; t++) isi.push_back(w[eu.id[t]]);
    sort(isi.begin(), isi.end());
    return int(unique(isi.begin(), isi.end()) - isi.begin());
}
```

**Jebakan:** naif dari v tanpa akar = seluruh graf. Itu bug tes, bukan bug sack.

**Kompleksitas:** naif O(n²).

## Ringkasan

1. Small-to-large: tuang kecil ke besar, tiap nilai pindah O(log n).
2. Query **subtree**, bukan jalur.
3. Sack = warisi anak berat, hapus ringan.
4. Euler `[tin, tout]` memudahkan add/remove rentang.
5. Kompres warna. Jangan hapus data berat.
6. Agregat lain: sesuaikan increment `cnt`.

Latihan Day 193. Jangan salin `exercise_*.cpp`.
