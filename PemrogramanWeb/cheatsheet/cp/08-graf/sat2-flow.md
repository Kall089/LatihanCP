# 2-SAT, aliran, matching, MCMF

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **229–234**. 2-SAT memakai SCC ([scc-bridge.md](scc-bridge.md)). Aliran di sini **hanya edukasi algoritma jaringan** (pipa, residual, jalur augmenting) — bukan serangan atau penyalahgunaan. Matching bipartit dan ide MCMF menutup folder graf.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [2-SAT](#2-sat)
- [Aliran: residual dan Edmonds-Karp](#aliran-residual-dan-edmonds-karp)
- [Dinic](#dinic)
- [Min-cut](#min-cut)
- [Matching Kuhn](#matching-kuhn)
- [König dan path cover](#könig-dan-path-cover)
- [Ide MCMF](#ide-mcmf)
- [Ringkasan](#ringkasan)

---

## 2-SAT

**Teori:** Setiap klausa paling banyak 2 literal, misalnya `(a ∨ ¬b)`. Klausa `(x ∨ y)` setara `(¬x → y) ∧ (¬y → x)`. Graf implikasi: simpul `2*i` = `x_i`, `2*i+1` = `¬x_i`. Solusi ada iff tidak ada `x` dan `¬x` di SCC yang sama. Analoginya: menolak A memaksa B; jika menolak A memaksa A, sistem jebak.

Penugasan Kosaraju (id naik saat DFS2): `x_i = true` jika `comp[2*i] > comp[2*i+1]` (literal yang SCC-nya lebih hilir). Tarjan increment-saat-pop memakai perbandingan terbalik.

**Kapan:** “pilih satu dari dua”, “tidak boleh A dan B bersamaan”, pewarnaan 2 sisi bersyarat. Jangan 3-SAT (NP-berat). Klausa unit `(x)` = `(x ∨ x)`.

**Proses:** variabel `x0, x1`. Klausa `(x0 ∨ x1)`, `(¬x0 ∨ x1)` → `x1` wajib true.

```
simpul: 0=x0, 1=¬x0, 2=x1, 3=¬x1
(x0 ∨ x1):   1→2, 3→0
(¬x0 ∨ x1):  0→2, 3→1
```

`x1` dan `¬x1` tidak satu SCC → SAT. Tambah unit `¬x1` (sisi `2→3`) bisa menyatukan `x1` dengan `¬x1` → UNSAT.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct TwoSAT {
    int n;
    vector<vector<int>> g, gt;
    vector<int> vis, order, comp, ans;

    TwoSAT(int nvar) : n(nvar), g(2 * nvar), gt(2 * nvar) {}

    int id(int x, bool isTrue) { return 2 * x + (isTrue ? 0 : 1); }
    int neg(int u) { return u ^ 1; }

    void implikasi(int u, int v) {
        g[u].push_back(v);
        gt[v].push_back(u);
    }
    void klausa(int x, bool vx, int y, bool vy) {
        implikasi(id(x, !vx), id(y, vy));
        implikasi(id(y, !vy), id(x, vx));
    }
    void unit(int x, bool vx) { klausa(x, vx, x, vx); }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    }
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : gt[u]) if (comp[v] == -1) dfs2(v, c);
    }

    bool solve() {
        int N = 2 * n;
        vis.assign(N, 0);
        order.clear();
        for (int s = 0; s < N; s++) if (!vis[s]) dfs1(s);
        comp.assign(N, -1);
        int cid = 0;
        for (int i = N - 1; i >= 0; i--)
            if (comp[order[i]] == -1) dfs2(order[i], cid++);
        ans.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            ans[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};

int main() {
    FASTIO;
    TwoSAT sat(2);
    sat.klausa(0, true, 1, true);
    sat.klausa(0, false, 1, true);
    cout << sat.solve() << ' ' << sat.ans[1] << '\n'; // 1 1
    TwoSAT bad(1);
    bad.unit(0, true);
    bad.unit(0, false);
    cout << bad.solve() << '\n';                   // 0
    return 0;
}
```

**Jebakan:**

1. `id` tertukar: samakan `neg = xor 1`.
2. Hanya satu implikasi per klausa.
3. `comp[x] > comp[~x]` hanya untuk Kosaraju penomoran DFS2 naik.
4. Variabel 1-index di soal, graf 0-index.

**Kompleksitas:** `O(n + m)` dengan `m` = 2 × jumlah klausa.

---

## Aliran: residual dan Edmonds-Karp

**Teori (edukasi jaringan):** Setiap sisi punya kapasitas pipa. Aliran `f` memenuhi `0 ≤ f ≤ cap` dan kekekalan di simpul selain sumber `s` dan tenggelam `t` (yang masuk = yang keluar). Teorema **max-flow min-cut**: aliran maksimum = kapasitas potongan `s-t` minimum.

**Sisi residual:** sisa `cap-f` maju, plus sisi balik `f` untuk membatalkan kiriman (menyesal, alihkan ke pipa lain). Jalur augmenting di residual menambah aliran. Ford-Fulkerson mencari jalur apa pun (DFS). Edmonds-Karp memakai BFS (paling sedikit sisi). Analoginya: pipa air; sisi balik = “tarik kembali air supaya rute lain kebagian”.

Ini model **kontes pemrograman** (kirim barang di graf), bukan alat penyerangan.

**Kapan:** “maksimum barang gudang ke toko”, matching via flow, potongan minimum kapasitas. Jangan DFS naif jika kapasitas `1e9` dan `n` besar (bisa augment 1 satuan berkali-kali). Edmonds-Karp `O(n m²)` kasar untuk `n ≤ 200`.

**Proses:** `s=0, t=3`. Sisi `(u,v,cap)`: `0-1:3, 0-2:2, 1-2:1, 1-3:2, 2-3:4`.

| jalur BFS | bottleneck | flow kumulatif |
|---|---|---|
| 0-1-3 | 2 | 2 |
| 0-2-3 | 2 | 4 |
| 0-1-2-3 | 1 | 5 |

Kapasitas keluar 0 = 5. Max flow **5**. Cut `{0}` vs sisanya: 3+2=5.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct EK {
    int n;
    vector<vector<int>> g;
    vector<ll> cap;
    vector<int> to;

    EK(int n) : n(n), g(n) {}

    void add(int u, int v, ll c) {
        g[u].push_back((int)to.size());
        to.push_back(v);
        cap.push_back(c);
        g[v].push_back((int)to.size());
        to.push_back(u);
        cap.push_back(0);
    }

    ll bfs(int s, int t, vector<int>& par) {
        par.assign(n, -1);
        par[s] = -2;
        queue<pair<int, ll>> q;
        q.push({s, INF});
        while (!q.empty()) {
            auto [u, f] = q.front();
            q.pop();
            for (int id : g[u]) {
                int v = to[id];
                if (par[v] != -1 || cap[id] <= 0) continue;
                par[v] = id;
                ll nf = min(f, cap[id]);
                if (v == t) return nf;
                q.push({v, nf});
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0, add;
        vector<int> par;
        while ((add = bfs(s, t, par))) {
            flow += add;
            for (int v = t; v != s; ) {
                int id = par[v];
                cap[id] -= add;
                cap[id ^ 1] += add;
                v = to[id ^ 1];
            }
        }
        return flow;
    }
};

int main() {
    FASTIO;
    EK ek(4);
    ek.add(0, 1, 3);
    ek.add(0, 2, 2);
    ek.add(1, 2, 1);
    ek.add(1, 3, 2);
    ek.add(2, 3, 4);
    cout << ek.maxflow(0, 3) << '\n';              // 5
    return 0;
}
```

**Jebakan:**

1. Lupa sisi balik `cap=0` — aliran tidak bisa dibatalkan, jawaban terlalu kecil.
2. `id ^ 1` mensyaratkan balik dipush **langsung setelah** maju.
3. Graf tak berarah: dua `add` terpisah (empat residual), jangan dobel tanpa pikir.
4. Multi-sisi: `add` berkali-kali, jangan timpa.

**Kompleksitas:** Edmonds-Karp `O(n m²)`. Ford-Fulkerson DFS `O(F m)` dengan `F` nilai flow.

---

## Dinic

**Teori:** Bangun **graf berlevel** (BFS jarak residual dari `s`), lalu kirim *blocking flow*: DFS hanya maju ke level +1 sampai tidak ada jalur di level graph. Ulangi BFS. Analoginya: gelombang (level) plus menyedot semua pipa selevel sebelum menggambar ulang peta. Pointer sisi `ptr` mencegah menyapu pipa kering berulang.

**Kapan:** default max-flow kontes, `n ≤ 1000`, `m ≤ 5000` sering lolos; matching via Dinic cepat. Jangan DFS tanpa `ptr`.

**Proses:** jaringan yang sama. Level awal: 0:0, 1:1, 2:1, 3:2. Satu atau dua fase menutup flow 5: kirim 2 lewat 0-1-3, 2 lewat 0-2-3, 1 lewat 0-1-2-3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct Dinic {
    struct E { int v; ll c; int rev; };
    int n;
    vector<vector<E>> g;
    vector<int> lvl, ptr;

    Dinic(int n) : n(n), g(n) {}

    void add(int u, int v, ll c) {
        g[u].push_back({v, c, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size() - 1});
    }

    bool bfs(int s, int t) {
        lvl.assign(n, -1);
        queue<int> q;
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& e : g[u]) if (e.c > 0 && lvl[e.v] == -1) {
                lvl[e.v] = lvl[u] + 1;
                q.push(e.v);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(int u, int t, ll f) {
        if (!f || u == t) return f;
        for (int& i = ptr[u]; i < (int)g[u].size(); i++) {
            auto& e = g[u][i];
            if (e.c <= 0 || lvl[e.v] != lvl[u] + 1) continue;
            ll pushed = dfs(e.v, t, min(f, e.c));
            if (pushed) {
                e.c -= pushed;
                g[e.v][e.rev].c += pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }
};

int main() {
    FASTIO;
    Dinic d(4);
    d.add(0, 1, 3);
    d.add(0, 2, 2);
    d.add(1, 2, 1);
    d.add(1, 3, 2);
    d.add(2, 3, 4);
    cout << d.maxflow(0, 3) << '\n';               // 5
    return 0;
}
```

**Jebakan:**

1. DFS ke `lvl[v] != lvl[u]+1` — bisa loop.
2. `ptr` di-reset tiap fase, bukan sekali.
3. Kapasitas `int` overflow jika banyak sisi `1e9`.
4. Lupa `rev`.

**Kompleksitas:** `O(n² m)` terburuk, praktis jauh lebih baik. Unit cap lebih cepat.

---

## Min-cut

**Teori:** Setelah max-flow, residual dari `s` mewarnai himpunan `S` yang masih tercapai. Sisi asli `u→v` dengan `u ∈ S`, `v ∉ S` adalah min-cut. Kapasitasnya = max-flow. Analoginya: setelah pipa jenuh, kota masih “basah” dari sumber vs yang kering; perbatasan = potongan termurah.

**Kapan:** “hapus sisi berkapasitas minimum supaya s tak sampai t”, partisi proyek. Jangan mengambil semua sisi jenuh: tidak semua ada di suatu min-cut.

**Proses:** flow 5. Residual dari 0: 0→1 sisa 0, 0→2 sisa 0. `S={0}`. Cut maju 0-1 dan 0-2 kapasitas 5.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// struct Dinic seperti bab sebelumnya
vector<int> himpunanS(Dinic& d, int s) {
    vector<int> vis(d.n), S;
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        S.push_back(u);
        for (auto& e : d.g[u]) if (e.c > 0 && !vis[e.v]) {
            vis[e.v] = 1;
            q.push(e.v);
        }
    }
    return S;
}

vector<pair<int, int>> sisiCut(Dinic& d, int s, const vector<pair<int, int>>& asli) {
    vector<int> vis(d.n);
    for (int u : himpunanS(d, s)) vis[u] = 1;
    vector<pair<int, int>> cut;
    for (auto [u, v] : asli) if (vis[u] && !vis[v]) cut.push_back({u, v});
    return cut;
}

int main() {
    FASTIO;
    Dinic d(4);
    vector<pair<int, int>> asli;
    auto addasli = [&](int u, int v, ll c) {
        d.add(u, v, c);
        asli.push_back({u, v});
    };
    addasli(0, 1, 3); addasli(0, 2, 2); addasli(1, 2, 1);
    addasli(1, 3, 2); addasli(2, 3, 4);
    cout << d.maxflow(0, 3) << '\n';
    auto S = himpunanS(d, 0);
    cout << S.size() << '\n';                      // 1
    return 0;
}
```

Di unit nyata, tempel `struct Dinic` utuh di atas fungsi ini.

**Jebakan:**

1. BFS cut memakai residual `c>0`, bukan graf asli.
2. Mencetak sisi balik sebagai cut.
3. Multi-sumber: tambah super-sumber dulu.

**Kompleksitas:** satu BFS `O(n + m)` setelah flow.

---

## Matching Kuhn

**Teori:** Matching: sisi tanpa dua sisi berbagi simpul. Pada graf bipartit, jalur augmenting: mulai kiri bebas, selang-seling non-matching / matching, berakhir kanan bebas, lalu *flip*. Kuhn: DFS dari setiap kiri belum berpasangan, `used` di-reset tiap percobaan. Analoginya: jika pasanganmu bisa pindah ke kursi kosong, kamu mengambil tempatnya.

**Kapan:** penugasan 0-1, “berapa orang dapat kursi”. Jangan Kuhn pada graf umum (butuh Blossom). Jangan sisi berbobot — Hungarian/MCMF.

**Proses:** kiri {0,1,2}, kanan {0,1,2}. Sisi `0-0, 0-1, 1-0, 2-1`.

| coba kiri | DFS | `mt[kanan]=kiri` |
|---|---|---|
| 0 | ambil kanan 0 | 0←0 |
| 1 | augment: 1 ambil 0, 0 pindah ke 1 | 0←1, 1←0 |
| 2 | hanya ke 1, 1 terisi, gagal | matching 2 |

Maksimum 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Kuhn {
    int nL, nR;
    vector<vector<int>> g;
    vector<int> mt, used;

    Kuhn(int nL, int nR) : nL(nL), nR(nR), g(nL), mt(nR, -1) {}
    void add(int u, int v) { g[u].push_back(v); }

    bool dfs(int u) {
        if (used[u]) return false;
        used[u] = 1;
        for (int v : g[u]) {
            if (mt[v] == -1 || dfs(mt[v])) {
                mt[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int match = 0;
        mt.assign(nR, -1);
        for (int u = 0; u < nL; u++) {
            used.assign(nL, 0);
            if (dfs(u)) match++;
        }
        return match;
    }

    vector<pair<int, int>> pasangan() const {
        vector<pair<int, int>> res;
        for (int v = 0; v < nR; v++) if (mt[v] != -1) res.push_back({mt[v], v});
        return res;
    }
};

int matchingViaDinic(int nL, int nR, const vector<pair<int, int>>& sisi) {
    int s = nL + nR, t = s + 1;
    Dinic d(t + 1);
    for (int u = 0; u < nL; u++) d.add(s, u, 1);
    for (int v = 0; v < nR; v++) d.add(nL + v, t, 1);
    for (auto [u, v] : sisi) d.add(u, nL + v, 1);
    return (int)d.maxflow(s, t);
}

int main() {
    FASTIO;
    Kuhn k(3, 3);
    k.add(0, 0); k.add(0, 1); k.add(1, 0); k.add(2, 1);
    cout << k.maxMatching() << '\n';               // 2
    return 0;
}
```

`matchingViaDinic` butuh `struct Dinic` di unit yang sama.

**Jebakan:**

1. `used` tidak di-reset tiap kiri.
2. Indeks kiri/kanan tertukar.
3. Graf tidak bipartit: Kuhn salah (blossom).

**Kompleksitas:** Kuhn `O(n_L · (n + m))`. Dinic matching lebih baik pada padat.

---

## König dan path cover

**Teori:** Pada graf bipartit, vertex cover minimum = matching maksimum. Konstruksi: dari kiri **bebas**, jalan non-matching ke kanan lalu matching kembali. `Z` = tersentuh. Cover = `(Kiri − Z) ∪ (Kanan ∩ Z)`. Analoginya: satpam seminimum di “sisi matching yang tidak bisa di-augment”.

Path cover DAG: split `u` jadi kiri/kanan, sisi `u→v` jadi matching; jawaban `n - matching`.

**Kapan:** “hapus minimum baris/kolom menutup semua 1”, minimum path cover DAG. Jangan rumus ini di non-bipartit.

**Proses:** matching 2, kiri 2 bebas. Cover ukuran 2 = matching.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<vector<int>, vector<int>> konig(const Kuhn& k) {
    int nL = k.nL, nR = k.nR;
    vector<int> kiriPas(nL, -1);
    for (int v = 0; v < nR; v++) if (k.mt[v] != -1) kiriPas[k.mt[v]] = v;
    vector<int> visL(nL), visR(nR);
    function<void(int)> dfs = [&](int u) {
        if (visL[u]) return;
        visL[u] = 1;
        for (int v : k.g[u]) if (k.mt[v] != u && !visR[v]) {
            visR[v] = 1;
            if (k.mt[v] != -1) dfs(k.mt[v]);
        }
    };
    for (int u = 0; u < nL; u++) if (kiriPas[u] == -1) dfs(u);
    vector<int> coverL, coverR;
    for (int u = 0; u < nL; u++) if (!visL[u]) coverL.push_back(u);
    for (int v = 0; v < nR; v++) if (visR[v]) coverR.push_back(v);
    return {coverL, coverR};
}

int pathCoverDAG(int n, const vector<vector<int>>& g) {
    Kuhn k(n, n);
    for (int u = 0; u < n; u++)
        for (int v : g[u]) k.add(u, v);
    return n - k.maxMatching();
}

int main() {
    FASTIO;
    Kuhn k(3, 3);
    k.add(0, 0); k.add(0, 1); k.add(1, 0); k.add(2, 1);
    k.maxMatching();
    auto [cl, cr] = konig(k);
    cout << cl.size() + cr.size() << '\n';         // 2
    return 0;
}
```

**Jebakan:**

1. Cover `Kiri ∩ Z` alih-alih `Kiri − Z`.
2. Path cover `n - matching` hanya DAG setelah split.
3. Independent set bipartit = `n - matching`.

**Kompleksitas:** matching plus `O(n + m)`.

---

## Ide MCMF

**Teori:** Minimum Cost Maximum Flow: sisi punya kapasitas dan **biaya per satuan**. Cari aliran sebesar mungkin (atau tepat `K`) dengan `Σ flow·cost` minimum. Algoritma: berulang kali cari jalur augmenting berbiaya terkecil di residual (SPFA, karena balik berbiaya `−cost`), kirim bottleneck, `cost += bottleneck * dist[t]`. Analoginya: kirim barang lewat rute termurah dulu; setelah pipa penuh, rute sisa mungkin membatalkan rute lama.

Penugasan `n×n`: sumber ke kiri cap 1 cost 0, kanan ke tenggelam cap 1 cost 0, kiri-kanan cap 1 cost `a[i][j]`. Hungarian `O(n³)` adalah dual khusus; MCMF lebih umum.

**Kapan:** penugasan berbobot, “kirim K unit termurah”. Jangan jika hanya max flow tanpa biaya. Jangan Dijkstra tanpa potensial jika biaya residual negatif.

**Proses:**

```
0→1 cap 1 cost 2
0→2 cap 1 cost 5
1→3 cap 1 cost 4
2→3 cap 1 cost 1
```

Jalur termurah `0-1-3` cost 6, kirim 1. Lalu `0-2-3` cost 6. Flow 2, cost **12**.

Penugasan

```
3 1
2 4
```

Pilihan `1+2=3` (bukan `3+4=7`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

struct MCMF {
    struct E { int v; ll cap, cost; int rev; };
    int n;
    vector<vector<E>> g;

    MCMF(int n) : n(n), g(n) {}

    void add(int u, int v, ll cap, ll cost) {
        g[u].push_back({v, cap, cost, (int)g[v].size()});
        g[v].push_back({u, 0, -cost, (int)g[u].size() - 1});
    }

    pair<ll, ll> minCostFlow(int s, int t, ll maxF = INF) {
        ll flow = 0, cost = 0;
        while (flow < maxF) {
            vector<ll> dist(n, INF);
            vector<int> inq(n, 0), pu(n, -1), pe(n, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            inq[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = 0;
                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto& e = g[u][i];
                    if (e.cap > 0 && dist[u] + e.cost < dist[e.v]) {
                        dist[e.v] = dist[u] + e.cost;
                        pu[e.v] = u;
                        pe[e.v] = i;
                        if (!inq[e.v]) { q.push(e.v); inq[e.v] = 1; }
                    }
                }
            }
            if (dist[t] >= INF) break;
            ll add = maxF - flow;
            for (int v = t; v != s; v = pu[v])
                add = min(add, g[pu[v]][pe[v]].cap);
            for (int v = t; v != s; v = pu[v]) {
                auto& e = g[pu[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
            cost += add * dist[t];
        }
        return {flow, cost};
    }
};

ll penugasanMCMF(const vector<vector<ll>>& a) {
    int n = (int)a.size();
    int s = 2 * n, t = 2 * n + 1;
    MCMF f(t + 1);
    for (int i = 0; i < n; i++) {
        f.add(s, i, 1, 0);
        f.add(n + i, t, 1, 0);
        for (int j = 0; j < n; j++) f.add(i, n + j, 1, a[i][j]);
    }
    return f.minCostFlow(s, t, n).second;
}

int main() {
    FASTIO;
    MCMF f(4);
    f.add(0, 1, 1, 2);
    f.add(0, 2, 1, 5);
    f.add(1, 3, 1, 4);
    f.add(2, 3, 1, 1);
    auto [fl, cs] = f.minCostFlow(0, 3);
    cout << fl << ' ' << cs << '\n';               // 2 12
    vector<vector<ll>> a = {{3, 1}, {2, 4}};
    cout << penugasanMCMF(a) << '\n';              // 3
    return 0;
}
```

**Jebakan:**

1. Sisi balik harus `−cost`.
2. SPFA tanpa `inq`: TLE.
3. `cost += dist[t]` tanpa kali bottleneck.
4. Siklus biaya negatif berkapasitas: SPFA bisa loop; jaringan penugasan yang benar biasanya aman.

**Kompleksitas:** `O(F · SPFA)` ≈ `O(F n m)`. Penugasan `F ≤ n`.

---

## Ringkasan

**Teori:** 2-SAT = SCC implikasi. Aliran = residual + augmenting (pipa edukasi). Dinic = level + blocking flow. Kuhn = augmenting matching. MCMF = jalur termurah beruntun.

**Kapan:**

| Soal | Alat |
|---|---|
| Klausa 2 literal | 2-SAT |
| Kapasitas s-t | Dinic |
| Pasangan 0-1 | Kuhn atau Dinic |
| Vertex cover bipartit | König |
| Kirim berbiaya | MCMF |

**Proses:** uji SAT `x1=1`, flow 5, matching 2, MCMF 12 di `main`.

**Jebakan lintas:**

1. 2-SAT perbandingan `comp` salah versi SCC.
2. Flow tanpa balik.
3. Kuhn tanpa reset `used`.
4. MCMF balik bukan `−cost`.

**Kompleksitas saku:** 2-SAT `O(n+m)`, EK `O(n m²)`, Dinic `O(n² m)`, Kuhn `O(n(n+m))`, MCMF `O(F n m)`.

Kembali: [scc-bridge.md](scc-bridge.md) · [siklus-bipartit.md](siklus-bipartit.md) · [08 Graf](README.md)
