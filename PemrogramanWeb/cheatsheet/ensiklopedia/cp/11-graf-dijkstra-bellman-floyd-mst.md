# 11 — Graf: Dijkstra, Bellman-Ford, Floyd-Warshall, MST

[← 10 DFS BFS topo](10-graf-dfs-bfs-topo.md) · [Indeks](README.md) · [Lanjut 12 →](12-graf-dsu-scc-bridge-2sat-flow.md)

Lanjutan folder **08 Graf** di `DAFTAR-MATERI.md`: Day 127 Dijkstra, 129 Bellman-Ford, 131 Floyd-Warshall, 136 MST. DSU penuh ada di file 12; di sini hanya DSU ringkas untuk Kruskal. Semua kode 0-indexed, `#include <bits/stdc++.h>`, `typedef long long ll`.

## Daftar isi

- [Peta jarak dan pohon rentang](#peta-jarak-dan-pohon-rentang)
- [Dijkstra heap](#dijkstra-heap)
- [Dijkstra O(n²) dan rekonstruksi](#dijkstra-on²-dan-rekonstruksi)
- [Varian Dijkstra](#varian-dijkstra)
- [Bellman-Ford](#bellman-ford)
- [SPFA](#spfa)
- [Kendala selisih](#kendala-selisih)
- [Floyd-Warshall](#floyd-warshall)
- [MST Kruskal](#mst-kruskal)
- [MST Prim](#mst-prim)
- [Varian MST](#varian-mst)
- [Johnson semua pasangan](#johnson-semua-pasangan)
- [Ringkasan file ini](#ringkasan-file-ini)

---

## Peta jarak dan pohon rentang

**Teori:** “Jarak” adalah jumlah bobot sepanjang jalur. “Pohon rentang minimum” adalah himpunan `n-1` sisi yang menghubungkan semua simpul dengan total bobot terkecil. Keduanya memakai relaksasi: `dist[v] = min(dist[v], dist[u] + w(u,v))`. Perbedaan hanya pada **urutan** relaksasi dan pada **syarat bobot**. Analoginya peta kota: Dijkstra seperti selalu memperluas kota terdekat yang sudah “pasti”; Bellman seperti mengulang “mungkin masih ada jalan lebih murah” sampai `n-1` putaran; Floyd seperti mencoba setiap kota sebagai titik transit; Kruskal seperti memasang kabel termurah yang belum membuat loop.

**Kapan dipakai:**

| Soal | Alat | Syarat |
|---|---|---|
| 1 sumber, `w ≥ 0` | Dijkstra | tak ada negatif |
| 1 sumber, ada negatif | Bellman-Ford / SPFA | deteksi siklus negatif |
| 1 sumber, DAG | DP topo (file 10) | lebih sederhana |
| 1 sumber, `w ∈ {0,1}` | 0-1 BFS (file 10) | lebih cepat |
| semua pasangan, `n ≤ 400` | Floyd | `O(n³)` muat |
| semua pasangan, jarang, ada minus | Johnson | Bellman + n Dijkstra |
| sambung semua, min total | MST Kruskal/Prim | tak berarah |
| ada siklus negatif tercapai | Bellman putaran ke-`n` | jawaban sering `-∞` |

**Proses:** kartu keputusan: lihat tanda bobot, lihat `n` vs `m`, lihat 1 sumber atau semua pasangan.

**Kode:** konstanta yang dipakai seluruh file.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;          // BUKAN LLONG_MAX: dist[u] + w harus aman

vector<vector<pair<int, ll>>> bacaBerbobot(int n, int m, bool berarah) {
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].push_back({v, w});
        if (!berarah) g[v].push_back({u, w});
    }
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << INF << '\n';
    return 0;
}
```

**Jebakan:** `INF = LLONG_MAX` lalu `dist[u] + w` overflow jadi negatif, seolah-olah jalan super murah. `INF = 4e18` aman untuk `w ≤ 1e12` dan `n` wajar.

**Kompleksitas:** membangun graf `O(n + m)`.

---

## Dijkstra heap

**Teori:** Dijkstra membagi simpul menjadi FINAL (jarak sudah pasti) dan SEMENTARA (perkiraan). Setiap langkah mengambil `u` sementara dengan `dist[u]` terkecil, mengunci `u`, lalu merelaksasi tetangga. Analoginya: dari rumah, selalu perluas tetangga yang biayanya paling kecil di antara yang belum dikunci. Bukti kunci: jika semua `w ≥ 0` dan ada jalur lebih pendek ke `u`, jalur itu harus menyeberang dari FINAL ke SEMENTARA di suatu `y`, dan `dist[y] < dist[u]`, kontradiksi. Asumsi `w ≥ 0` dipakai persis di “awalan jalur tidak lebih mahal dari seluruh jalur”.

`std::priority_queue` tidak punya *decrease-key*. Solusinya **lazy deletion**: push entri baru, abaikan entri usang saat `d > dist[u]`.

**Kapan dipakai:** 1 sumber, bobot tak negatif, `n, m` sampai `1e5`. Jangan dipakai jika ada sisi negatif — kadang kebetulan benar, kadang menyebarkan nilai terkunci yang salah. Jangan dipakai untuk *longest path* (ganti tanda hanya aman di DAG).

**Proses:** graf berarah

```
0 --1--> 1 --3--> 3
|        |
2        1
v        v
2 --4--> 3
```

Sisi: `0→1 (1), 0→2 (2), 1→3 (3), 1→2 (1), 2→3 (4)`. Sumber 0.

| pop `(d,u)` | aksi | dist |
|---|---|---|
| init | | `[0, ∞, ∞, ∞]` |
| (0,0) | 1←1, 2←2 | `[0, 1, 2, ∞]` |
| (1,1) | 3←4, 2←2 (sama, tidak lebih baik) | `[0, 1, 2, 4]` |
| (2,2) | 3←6 tidak lebih baik | `[0, 1, 2, 4]` |
| (4,3) | selesai | |

Jalur 0-1-3 = 4 mengalahkan 0-2-3 = 6. Heap juga bisa memuat entri usang jika suatu saat `dist` membaik dua kali.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

vector<ll> dijkstra(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;          // entri USANG
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 1});
    g[0].push_back({2, 2});
    g[1].push_back({3, 3});
    g[1].push_back({2, 1});
    g[2].push_back({3, 4});
    auto d = dijkstra(n, g, 0);
    for (int i = 0; i < n; i++)
        cout << (d[i] >= INF ? -1 : d[i]) << " \n"[i + 1 == n];
    // 0 1 2 4
    return 0;
}
```

**Jebakan:**

1. `priority_queue` default adalah **max-heap**. Wajib `greater<pli>`.
2. Pasangan harus `(jarak, simpul)` — jarak di `first` supaya terurut benar.
3. Menghapus `if (d > dist[u]) continue` tidak selalu salah, tetapi bisa TLE.
4. `int` untuk jarak: `n * w` sampai `1e5 * 1e9` overflow. Pakai `ll`.

**Kompleksitas:** `O((n + m) log m)` ≈ `O(m log n)` dengan lazy heap. Memori `O(n + m)`.

---

## Dijkstra O(n²) dan rekonstruksi

**Teori:** Versi tanpa heap menyapu semua simpul belum final untuk mencari `dist` terkecil: `O(n)` per pengambilan, `n` kali, plus relaksasi `O(n²)` jika matriks. Lebih cepat daripada heap jika graf **padat** (`m ≈ n²`), karena `n² < m log n` di situ. Rekonstruksi: simpan `par[v] = u` saat relaksasi berhasil, lalu jalan mundur dari `t` ke `s`.

**Kapan dipakai:** `n ≤ 2000` padat, atau soal matriks ketetanggaan. Rekonstruksi selalu, jika soal minta jalur. Jangan `O(n²)` pada `n = 1e5`.

**Proses:** graf yang sama. Versi `O(n²)`:

| iter | pilih u | done | relaksasi |
|---|---|---|---|
| 1 | 0 (dist 0) | {0} | dist[1]=1, dist[2]=2 |
| 2 | 1 (dist 1) | {0,1} | dist[3]=4, dist[2] tetap 2 |
| 3 | 2 (dist 2) | {0,1,2} | dist[3] tetap 4 |
| 4 | 3 | semua | |

`par[1]=0, par[2]=0, par[3]=1`. Jalur ke 3: `3 ← 1 ← 0` → `0 1 3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

vector<ll> dijkstraPadat(int n, const vector<vector<ll>>& w, int s) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    dist[s] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] >= INF) break;
        done[u] = 1;
        for (int v = 0; v < n; v++)
            if (w[u][v] < INF) dist[v] = min(dist[v], dist[u] + w[u][v]);
    }
    return dist;
}

vector<ll> dijkstraPar(int n, const vector<vector<pair<int, ll>>>& g, int s,
                       vector<int>& par) {
    vector<ll> dist(n, INF);
    par.assign(n, -1);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dist[v]) {
            dist[v] = d + w;
            par[v] = u;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

vector<int> bangunJalur(int s, int t, const vector<ll>& dist, const vector<int>& par) {
    if (dist[t] >= INF) return {};
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path.empty() || path[0] != s) return {};
    return path;
}

int main() {
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 1});
    g[0].push_back({2, 2});
    g[1].push_back({3, 3});
    g[2].push_back({3, 4});
    vector<int> par;
    auto dist = dijkstraPar(n, g, 0, par);
    auto path = bangunJalur(0, 3, dist, par);
    for (int x : path) cout << x << ' ';
    cout << '\n';                                  // 0 1 3
    return 0;
}
```

**Jebakan:**

1. Matriks `w[u][v] = 0` untuk “tidak ada sisi” — 0 adalah bobot sah. Isi `INF` jika tidak ada sisi, `0` hanya di diagonal.
2. `par[s]` harus `-1`. Jika 0, loop tak hingga pada graf 0-indexed ketika `s = 0`... tunggu: jika `par[s] = 0` dan `s = 0`, `for (v = t; v != -1; v = par[v])` pada `s=0` berhenti karena kita cek `v != -1`, tetapi `par[0]=0` membuat loop `0, 0, 0, ...`. **Wajib `par[s] = -1`.**
3. Tie-break: `d + w == dist[v]` tidak mengganti parent; boleh jika ingin jalur tertentu.

**Kompleksitas:** padat `O(n²)`, heap `O(m log n)`, rekonstruksi `O(n)`.

---

## Varian Dijkstra

**Teori:** Kerangka heap sama; yang berubah hanya **cara menggabung biaya**. Jumlah biasa: `nd = d + w`. Minimax (hambat terburuk): `nd = max(d, w)` — minimalkan sisi terbesar di jalur. Maximin (kapasitas): `nd = min(d, w)` — maksimalkan sisi terkecil. Banyak jalur: jika `d+w == dist[v]`, tambah `cnt[v] += cnt[u]`. Berlapis: state `(simpul, kupon terpakai)`. Analoginya: kadang yang diukur bukan km, melainkan “tanjakan terjal” atau “jembatan terlemah”.

**Kapan dipakai:** “minimum effort”, “lebar jalur maksimum”, “berapa shortest path”, “boleh skip K sisi”. Jangan mencampur operator: `max` untuk effort, `min` untuk kapasitas, `+` untuk jarak.

**Proses:** minimax pada `0-1 (5), 0-2 (1), 2-1 (2), 1-3 (4), 2-3 (6)`.

Jalur `0-1-3` hambatan `max(5,4)=5`. Jalur `0-2-1-3` hambatan `max(1,2,4)=4`. Jalur `0-2-3` hambatan `6`. Jawaban ke 3 = **4**.

| pop | dist minimax |
|---|---|
| (0,0) | 1←5, 2←1 |
| (1,2) | 1←max(1,2)=2 (lebih baik dari 5), 3←6 |
| (2,1) | 3←max(2,4)=4 |
| (4,3) | kunci 4 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

vector<ll> minimax(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            ll nd = max(d, w);
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

vector<ll> maximin(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, -1);
    priority_queue<pli> pq;                 // MAX-heap
    dist[s] = INF;
    pq.push({INF, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d < dist[u]) continue;
        for (auto [v, w] : g[u]) {
            ll nd = min(d, w);
            if (nd > dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
    return dist;
}

void dijkstraHitung(int n, const vector<vector<pair<int, ll>>>& g, int s,
                    vector<ll>& dist, vector<ll>& cnt) {
    dist.assign(n, INF);
    cnt.assign(n, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    cnt[s] = 1;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u];
                pq.push({dist[v], v});
            } else if (d + w == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
}

vector<vector<ll>> dijkstraKupon(int n, int K, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<vector<ll>> dist(n, vector<ll>(K + 1, INF));
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s][0] = 0;
    pq.push({0, s * (K + 1)});
    while (!pq.empty()) {
        auto [d, code] = pq.top();
        pq.pop();
        int u = code / (K + 1), k = code % (K + 1);
        if (d > dist[u][k]) continue;
        for (auto [v, w] : g[u]) {
            if (d + w < dist[v][k]) {
                dist[v][k] = d + w;
                pq.push({dist[v][k], v * (K + 1) + k});
            }
            if (k < K && d < dist[v][k + 1]) {     // skip bayar
                dist[v][k + 1] = d;
                pq.push({d, v * (K + 1) + k + 1});
            }
        }
    }
    return dist;
}

int main() {
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 5});
    g[0].push_back({2, 1});
    g[2].push_back({1, 2});
    g[1].push_back({3, 4});
    g[2].push_back({3, 6});
    cout << minimax(n, g, 0)[3] << '\n';           // 4
    vector<ll> dist, cnt;
    dijkstraHitung(n, g, 0, dist, cnt);
    cout << dist[3] << ' ' << cnt[3] << '\n';      // 7 1   (0-2-1-3)
    return 0;
}
```

**Jebakan:**

1. Minimax menginisialisasi `dist[s] = INF` — salah; sumber 0 (tidak ada sisi yang sudah dilalui).
2. Maximin menginisialisasi `dist[s] = 0` — salah; sumber “kapasitas tak hingga”.
3. Menghitung jalur pada entri usang: wajib `if (d > dist[u]) continue` sebelum menambahkan `cnt`.
4. Kupon: state harus `(u, k)`, bukan hanya `u`.

**Kompleksitas:** sama Dijkstra, dikali `K+1` untuk berlapis: `O(K (n + m) log (K n))`.

---

## Bellman-Ford

**Teori:** Relaksasi semua sisi diulang `n-1` kali. Setelah `i` putaran, `dist[v]` sudah benar untuk semua jalur yang memakai paling banyak `i` sisi (jika tidak ada siklus negatif tercapai). Analoginya: berita harga disebar putaran demi putaran; setelah `n-1` hop, jalur sederhana paling panjang sudah tertampung. Putaran ke-`n` yang masih merelaksasi berarti ada siklus negatif **yang tercapai dari sumber** (atau dari simpul yang sudah berhingga).

**Kapan dipakai:** ada bobot negatif, deteksi siklus negatif, kendala selisih. Jangan dipakai sebagai default: `O(n m)` TLE pada `n, m = 1e5`. Jangan Dijkstra “dengan harapan” pada negatif.

**Proses:** sisi `0→1 (4), 0→2 (5), 1→2 (-3), 2→3 (1), 1→3 (4)`, sumber 0. Tidak ada siklus negatif.

Setelah putaran 1 (urut sisi di atas):

| sisi | dist baru |
|---|---|
| 0→1 | 4 |
| 0→2 | 5 |
| 1→2 | 4 + (−3) = 1 |
| 2→3 | 1 + 1 = 2 |
| 1→3 | 4 + 4 = 8, kalah dari 2 |

`dist = [0, 4, 1, 2]`. Putaran 2 tidak mengubah. Jika tambah `3→1 (−4)`: siklus `1-2-3-1` bobot `-3-wait`: 1→2 (−3), 2→3 (1), 3→1 (−4) total −6. Putaran ke-4 masih merelaksasi.

Trace siklus negatif singkat: setelah dist berhingga di 1, 2, 3, setiap putaran ketiga jarak mereka −6.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

pair<vector<ll>, bool> bellman(int n, const vector<Edge>& e, int s) {
    vector<ll> dist(n, INF);
    dist[s] = 0;
    bool siklusNeg = false;
    for (int it = 0; it < n; it++) {
        bool ubah = false;
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ubah = true;
                if (it == n - 1) siklusNeg = true;
            }
        }
        if (!ubah) break;
    }
    return {dist, siklusNeg};
}

vector<int> kenaSiklusNegatif(int n, const vector<Edge>& e, int s) {
    vector<ll> dist(n, INF);
    dist[s] = 0;
    vector<int> kena(n, 0);
    for (int it = 0; it < n; it++) {
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (it == n - 1) kena[v] = 1;
            }
        }
    }
    // tandai semua yang tercapai dari simpul yang terelaksasi di putaran n
    vector<vector<int>> g(n);
    for (auto [u, v, w] : e) g[u].push_back(v);
    queue<int> q;
    for (int i = 0; i < n; i++) if (kena[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (!kena[v]) {
            kena[v] = 1;
            q.push(v);
        }
    }
    return kena;
}

int main() {
    vector<Edge> e = {
        {0, 1, 4}, {0, 2, 5}, {1, 2, -3}, {2, 3, 1}, {1, 3, 4}
    };
    auto [d, neg] = bellman(4, e, 0);
    cout << neg << ' ' << d[3] << '\n';            // 0 2
    e.push_back({3, 1, -4});
    auto [d2, neg2] = bellman(4, e, 0);
    cout << neg2 << '\n';                          // 1
    return 0;
}
```

**Jebakan:**

1. Merelaksasi dari `dist[u] == INF`: `INF + (−5)` masih “berhingga palsu” jika `INF` tidak dijaga. Skip `dist[u] >= INF`.
2. Siklus negatif yang **tidak tercapai dari s** tidak boleh menggagalkan jawaban ke simpul lain.
3. Setelah terdeteksi, `dist` di simpul siklus bukan angka bermakna; tandai `-∞`.
4. `n-1` vs `n` putaran: deteksi hanya di putaran ke-`n` (indeks `n-1` jika 0-based loop `it = 0..n-1`).

**Kompleksitas:** `O(n m)` waktu, `O(n + m)` memori.

---

## SPFA

**Teori:** SPFA adalah Bellman yang hanya merelaksasi sisi dari simpul yang `dist`-nya baru saja membaik (antrean). Rata-rata cepat pada graf acak, terburuk masih `O(n m)` dan bisa dibuat TLE oleh kasus anti-SPFA. Deteksi siklus: sebuah simpul masuk antrean lebih dari `n` kali, atau pakai *SLF* hanya sebagai heuristik. Analoginya: Bellman menyiarkan ke semua radio setiap jam; SPFA hanya menyiarkan dari stasiun yang baru dapat berita baru.

**Kapan dipakai:** graf negatif, `n` sedang, kamu butuh kode pendek dan *biasanya* lolos. Jangan andalkan di Codeforces jika `n, m` besar — juri punya tes anti-SPFA. Untuk kontes aman, Bellman `O(n m)` jika `n m ≤ 1e8`, atau Dijkstra jika tidak negatif.

**Proses:** graf Bellman tanpa siklus. Antrean mulai `[0]`.

| pop | relaksasi yang membaik | antrean |
|---|---|---|
| 0 | 1←4, 2←5 | [1, 2] |
| 1 | 2←1, 3←8 | [2, 2, 3] |
| 2 (dist 5, usang) | 5+1=6 > 1, skip | [2, 3] |
| 2 (dist 1) | 3←2 | [3, 3] |
| 3 usang / 3 dist 2 | selesai | |

`inqueue` mencegah simpul yang sama duduk dua kali **sekaligus**; tetap boleh masuk lagi setelah keluar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

pair<vector<ll>, bool> spfa(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    vector<int> inq(n, 0), cnt(n, 0);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inq[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto [v, w] : g[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            if (!inq[v]) {
                q.push(v);
                inq[v] = 1;
                if (++cnt[v] >= n) return {dist, true};   // siklus negatif
            }
        }
    }
    return {dist, false};
}

int main() {
    int n = 4;
    vector<vector<pair<int, ll>>> g(n);
    g[0].push_back({1, 4});
    g[0].push_back({2, 5});
    g[1].push_back({2, -3});
    g[2].push_back({3, 1});
    g[1].push_back({3, 4});
    auto [d, neg] = spfa(n, g, 0);
    cout << neg << ' ' << d[3] << '\n';            // 0 2
    return 0;
}
```

**Jebakan:**

1. Lupa `inq[v]`: antrean meledak, tetap benar secara nilai jika relaksasi ketat, tetapi TLE.
2. `cnt[v] >= n` adalah tes praktis, bukan satu-satunya; graf aneh bisa lambat sebelum terdeteksi.
3. Relaksasi tanpa cek `dist[u] >= INF` (sumber tak terhubung).
4. Memakai SPFA sebagai “Dijkstra lebih cepat” pada bobot positif: heap Dijkstra lebih stabil.

**Kompleksitas:** rata-rata sering `O(k m)` dengan `k` kecil, terburuk `O(n m)`.

---

## Kendala selisih

**Teori:** Sistem `x_v - x_u ≤ w` setara dengan sisi berarah `u → v` berbobot `w`. Solusi ada jika dan hanya jika graf kendala **tidak punya siklus negatif**. Nilai `x_v = dist[v]` dari sumber dummy yang dihubungkan ke semua simpul dengan bobot 0 adalah satu solusi (paling ketat dari dummy). Analoginya: “B tidak boleh lebih dari 5 jam setelah A” menjadi jalan A→B biaya 5. Jika syarat berputar dan menekan total negatif, sistem mustahil.

**Kapan dipakai:** “jadwal dengan batasan beda waktu”, *difference constraints*, beberapa soal *graph construction*. Jangan memaksa jika kendala berbentuk perkalian atau XOR.

**Proses:** variabel `x0, x1, x2`.

```
x1 - x0 ≤ 3
x2 - x1 ≤ 2
x0 - x2 ≤ -6    →  x2 - x0 ≥ 6
```

Sisi: `0→1 (3), 1→2 (2), 2→0 (−6)`. Siklus `0-1-2-0` bobot `3+2-6 = −1` → **mustahil**.

Ganti syarat ketiga `x0 - x2 ≤ −4` (sisi `2→0 (−4)`). Siklus bobot `3+2-4 = 1 ≥ 0`. Dummy `3` ke `0,1,2` bobot 0. Bellman dari 3 memberi `dist[0], dist[1], dist[2]` sebagai nilai `x`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

// tambahSyarat: x[v] - x[u] <= w
void tambahSyarat(vector<Edge>& e, int u, int v, ll w) {
    e.push_back({u, v, w});
}

pair<bool, vector<ll>> selesaikanKendala(int n, vector<Edge> e) {
    int s = n;                                 // dummy
    for (int i = 0; i < n; i++) e.push_back({s, i, 0});
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;
    for (int it = 0; it < n + 1; it++) {
        bool ubah = false;
        for (auto [u, v, w] : e) {
            if (dist[u] >= INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ubah = true;
                if (it == n) return {false, {}};
            }
        }
        if (!ubah) break;
    }
    dist.pop_back();                           // buang dummy
    return {true, dist};
}

int main() {
    vector<Edge> e;
    tambahSyarat(e, 0, 1, 3);
    tambahSyarat(e, 1, 2, 2);
    tambahSyarat(e, 2, 0, -4);
    auto [ok, x] = selesaikanKendala(3, e);
    cout << ok << ' ' << x[0] << ' ' << x[1] << ' ' << x[2] << '\n';
    return 0;
}
```

**Jebakan:**

1. Arah `x[v] - x[u] ≤ w` terbalik menjadi `v → u`. Ingat: sisi **dari u ke v**.
2. Lupa dummy: Bellman dari simpul 0 saja tidak melihat komponen lain.
3. `x_v - x_u ≥ c` diubah jadi `x_u - x_v ≤ -c`.
4. `x_v = x_u` menjadi dua sisi 0.

**Kompleksitas:** Bellman `O(n (n + m))` dengan dummy.

---

## Floyd-Warshall

**Teori:** `dp[k][i][j]` = jarak `i → j` yang hanya boleh transit di `{0,1,...,k-1}`. Transisi: lewat `k` atau tidak: `min(dp[k][i][j], dp[k][i][k] + dp[k][k][j])`. Urutan loop **k di luar** adalah wajib: `k` adalah “lapisan transit”. Analoginya: tahun ke-`k` bandara `k` baru dibuka sebagai transit; semua pasangan kota meninjau ulang tiket. Setelah `k = 0..n-1`, semua simpul boleh jadi transit → jarak semua pasangan.

`dist[i][i] < 0` setelah selesai artinya `i` mencapai siklus negatif.

**Kapan dipakai:** `n ≤ 400`, semua pasangan, *transitive closure* (`or` / `min` 0-1), *minimax* semua pasangan (`max` di jalur, `min` antar jalur). Jangan pada `n = 1000` (`1e9` operasi). Jangan 1 sumber saja — Dijkstra/Bellman lebih hemat.

**Proses:** 4 simpul, tak berarah (isi dua arah):

```
0-1: 3, 0-2: 8, 1-2: 2, 1-3: 5, 2-3: 1
```

Matriks awal (`INF` kosong, 0 diagonal):

```
    0  3  8  ∞
    3  0  2  5
    8  2  0  1
    ∞  5  1  0
```

Setelah `k = 1` (transit 1): `0→2` menjadi `3+2=5`, `0→3` menjadi `3+5=8`.

Setelah `k = 2`: `0→3` menjadi `5+1=6` (0-1-2-3). `1→3` menjadi `2+1=3`.

Setelah `k = 3`: tidak lebih baik. `dist[0][3] = 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

void floyd(int n, vector<vector<ll>>& d) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k] < INF)
                for (int j = 0; j < n; j++)
                    if (d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

vector<vector<int>> floydPar(int n, vector<vector<ll>>& d) {
    vector<vector<int>> nxt(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) nxt[i][j] = i;
            else if (d[i][j] < INF) nxt[i][j] = j;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (d[i][k] < INF)
                for (int j = 0; j < n; j++)
                    if (d[k][j] < INF && d[i][k] + d[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        nxt[i][j] = nxt[i][k];
                    }
    return nxt;
}

vector<int> jalurFloyd(int s, int t, const vector<vector<int>>& nxt) {
    if (nxt[s][t] == -1) return {};
    vector<int> path = {s};
    while (s != t) {
        s = nxt[s][t];
        path.push_back(s);
    }
    return path;
}

bool adaSiklusNegatifFloyd(int n, const vector<vector<ll>>& d) {
    for (int i = 0; i < n; i++) if (d[i][i] < 0) return true;
    return false;
}

void tutupTransitif(int n, vector<vector<int>>& reach) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (reach[i][k])
                for (int j = 0; j < n; j++)
                    reach[i][j] |= reach[k][j];
}

int main() {
    int n = 4;
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    auto add = [&](int u, int v, ll w) {
        d[u][v] = min(d[u][v], w);
        d[v][u] = min(d[v][u], w);
    };
    add(0, 1, 3); add(0, 2, 8); add(1, 2, 2); add(1, 3, 5); add(2, 3, 1);
    auto nxt = floydPar(n, d);
    cout << d[0][3] << '\n';                       // 6
    auto p = jalurFloyd(0, 3, nxt);
    for (int x : p) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 3
    cout << adaSiklusNegatifFloyd(n, d) << '\n';
    return 0;
}
```

**Jebakan:**

1. Loop `i,j,k` — **salah**. Harus `k, i, j`.
2. Tidak mengisi `d[i][i] = 0`.
3. Multi-sisi: ambil `min`, bukan menimpa.
4. `d[i][k] + d[k][j]` tanpa cek `INF`: overflow.
5. Setelah siklus negatif, rekonstruksi jalur bisa loop abadi — cek `d[x][x] < 0` pada simpul di jalur.

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## MST Kruskal

**Teori:** Urutkan sisi naik bobot, pasang sisi jika kedua ujung **belum** satu komponen (DSU). Teorema cut: sisi paling ringan yang menyeberangi suatu potongan aman masuk suatu MST. Kruskal adalah greedy yang selalu mengambil sisi global paling ringan yang belum membuat siklus; cut property menjamin tidak menyesal. Analoginya: memasang kabel kota dari yang termurah, skip jika kedua kota sudah saling nyambung lewat kabel sebelumnya.

Pohon rentang punya `n-1` sisi. Jika sisi terpakai `< n-1`, graf tidak terhubung.

**Kapan dipakai:** graf tak berarah berbobot, `m` sampai `2e5` (sort mendominasi). Jangan pada graf berarah (itu *arborescence*, beda algoritma). Jangan jika butuh “MST yang memuat sisi X” tanpa cek ulang.

**Proses:** 6 simpul, sisi (bobot, u, v):

```
(1,0,1), (2,1,2), (2,0,2), (3,1,3), (4,2,4), (4,3,4), (5,3,5), (6,4,5), (10,0,5)
```

| sisi | DSU | ambil? | total |
|---|---|---|---|
| 0-1 : 1 | beda | ya | 1 |
| 1-2 : 2 | beda | ya | 3 |
| 0-2 : 2 | sama (0-1-2) | tidak | 3 |
| 1-3 : 3 | beda | ya | 6 |
| 2-4 : 4 | beda | ya | 10 |
| 3-4 : 4 | sama | tidak | 10 |
| 3-5 : 5 | beda | ya | 15 |
| 4-5 : 6 | sama | tidak | 15 |
| 0-5 :10 | sama | tidak | 15 |

5 sisi, `n-1=5`, MST = 15. Sisi `0-2` ditolak karena siklus segitiga.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    int komponen;
    DSU(int n) : par(n), sz(n, 1), komponen(n) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
        return true;
    }
};

struct Sisi { ll w; int u, v; };
bool operator<(const Sisi& a, const Sisi& b) { return a.w < b.w; }

pair<ll, vector<Sisi>> kruskal(int n, vector<Sisi> sisi) {
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    ll total = 0;
    vector<Sisi> pakai;
    for (auto e : sisi) if (d.unite(e.u, e.v)) {
        total += e.w;
        pakai.push_back(e);
        if ((int)pakai.size() == n - 1) break;
    }
    if ((int)pakai.size() != n - 1) return {-1, {}};
    return {total, pakai};
}

int main() {
    vector<Sisi> sisi = {
        {1, 0, 1}, {2, 1, 2}, {2, 0, 2}, {3, 1, 3}, {4, 2, 4},
        {4, 3, 4}, {5, 3, 5}, {6, 4, 5}, {10, 0, 5}
    };
    auto [tot, pakai] = kruskal(6, sisi);
    cout << tot << ' ' << pakai.size() << '\n';    // 15 5
    return 0;
}
```

**Jebakan:**

1. Graf 0-indexed tetapi DSU dibuat `n` sementara simpul sampai `n` — off-by-one.
2. Tidak mengecek `pakai.size() == n-1` lalu mencetak total seolah terhubung.
3. `unite` diabaikan nilainya: sisi siklus ikut dijumlah.
4. Bobot sama: urutan tidak unik, total MST tetap sama (jika tidak ada bobot beda yang setara secara keliru di-cast `int`).

**Kompleksitas:** `O(m log m)` sort + `O(m α(n))` DSU.

---

## MST Prim

**Teori:** Prim menumbuhkan satu pohon: mulai dari simpul 0, selalu tambah sisi paling ringan yang keluar dari himpunan yang sudah diambil. Ini dual Kruskal: Kruskal global-sort, Prim “Dijkstra pada *min edge ke pohon*”. Analoginya: kota ibukota memasang kabel ke desa terdekat yang belum terlayani, berulang. Cut property tetap: sisi paling ringan keluar himpunan S adalah aman.

Implementasi heap identik Dijkstra, tetapi `dist[v]` berarti **bobot sisi** ke pohon, bukan jumlah jalur. `dist[v]` tidak dijumlah dengan `dist[u]`.

**Kapan dipakai:** graf padat (`n ≤ 2000`, matriks) versi `O(n²)`; atau ketika sisi tidak ingin disortir semua. Kruskal biasanya lebih pendek pada graf jarang. Keduanya menghasilkan bobot MST sama.

**Proses:** graf Kruskal, mulai 0.

| pohon | kandidat terdekat | ambil | dist sisi |
|---|---|---|---|
| {0} | 0-1:1 | 1 | +1 |
| {0,1} | 1-2:2 (0-2:2 sama) | 2 | +2 |
| {0,1,2} | 1-3:3 | 3 | +3 |
| {0..3} | 2-4:4 | 4 | +4 |
| {0..4} | 3-5:5 | 5 | +5 |

Total 15, sama Kruskal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

ll prim(int n, const vector<vector<pair<int, ll>>>& g) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    ll total = 0;
    int ambil = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (done[u]) continue;
        done[u] = 1;
        total += d;
        ambil++;
        for (auto [v, w] : g[u])
            if (!done[v] && w < dist[v]) {
                dist[v] = w;                 // BUKAN dist[u] + w
                pq.push({w, v});
            }
    }
    return ambil == n ? total : -1;
}

ll primPadat(int n, const vector<vector<ll>>& w) {
    vector<ll> dist(n, INF);
    vector<int> done(n, 0);
    dist[0] = 0;
    ll total = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (u == -1 || dist[u] >= INF) return -1;
        done[u] = 1;
        total += dist[u];
        for (int v = 0; v < n; v++)
            if (!done[v]) dist[v] = min(dist[v], w[u][v]);
    }
    return total;
}

int main() {
    int n = 6;
    vector<vector<pair<int, ll>>> g(n);
    auto add = [&](int u, int v, ll w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
    add(0, 1, 1); add(1, 2, 2); add(0, 2, 2); add(1, 3, 3);
    add(2, 4, 4); add(3, 4, 4); add(3, 5, 5); add(4, 5, 6); add(0, 5, 10);
    cout << prim(n, g) << '\n';                    // 15
    return 0;
}
```

**Jebakan:**

1. Menulis `dist[v] = dist[u] + w` — itu Dijkstra, bukan Prim. MST jadi salah (biasanya lebih besar).
2. Graf tidak terhubung: `ambil < n`, kembalikan `-1`.
3. `total += d` pada sumber: `d = 0`, aman. Jangan menambah sisi imajiner.
4. Multi-komponen: Prim dari 0 hanya satu komponen — beda dari Kruskal yang terlihat dari `komponen`.

**Kompleksitas:** heap `O(m log n)`, padat `O(n²)`.

---

## Varian MST

**Teori:** Beberapa pertanyaan memakai tulang MST. **Bottleneck MST:** minimalkan sisi terberat di pohon — sebenarnya setiap MST adalah bottleneck-optimal. **Maximum spanning tree:** Kruskal menurun (atau negasi bobot). **Second-best MST:** setelah MST, untuk setiap sisi non-MST `e=(u,v)`, ganti sisi terberat di jalur `u-v` pada MST; ambil peningkatan terkecil. **MST dengan sisi wajib:** satukan dulu ujung-ujung sisi wajib (jika membentuk siklus, mustahil). Analoginya: jaringan kabel punya cadangan “hampir sehemat MST”.

**Kapan dipakai:** “pohon kedua terbaik”, “wajib memakai jembatan ini”, “minimalkan kabel termahal”. Jangan *second-best* naif `O(m²)` jika `m` besar tanpa LCA/RMQ pada MST.

**Proses:** MST = 15, sisi non-MST `0-2:2`. Jalur 0-2 di MST adalah `0-1-2` dengan sisi terberat 2. Ganti 2 dengan 2: total tetap 15 (MST alternatif, bukan ketat kedua). Sisi `3-4:4`: jalur 3-1-2-4, terberat 4, total tetap. Sisi `4-5:6`: jalur 4-2-1-3-5, terberat 5 (sisi 3-5), ganti 5 dengan 6 → total **16**. Itu second-best ketat.

| non-MST | sisi max di jalur MST | total baru |
|---|---|---|
| 0-2 : 2 | 2 | 15 |
| 3-4 : 4 | 4 | 15 |
| 4-5 : 6 | 5 | 16 |
| 0-5 :10 | 5 | 20 |

Second-best ketat = 16.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
        return true;
    }
};

struct Sisi { ll w; int u, v; int id; };
bool operator<(const Sisi& a, const Sisi& b) { return a.w < b.w; }

ll mstMaksimum(int n, vector<Sisi> sisi) {
    sort(sisi.begin(), sisi.end(), [](Sisi a, Sisi b) { return a.w > b.w; });
    DSU d(n);
    ll tot = 0;
    int k = 0;
    for (auto e : sisi) if (d.unite(e.u, e.v)) { tot += e.w; k++; }
    return k == n - 1 ? tot : -1;
}

ll bottleneckMin(int n, vector<Sisi> sisi) {
    // sisi terberat pada suatu MST = jawaban bottleneck
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    ll berat = -1;
    int k = 0;
    for (auto e : sisi) if (d.unite(e.u, e.v)) { berat = e.w; k++; }
    return k == n - 1 ? berat : -1;
}

// second-best O(n^2) pada pohon MST: precompute maxEdge[u][v] lewat DFS dari tiap akar
ll maxDiJalur(int u, int target, const vector<vector<pair<int, ll>>>& tree) {
    vector<ll> mx(tree.size(), -1);
    vector<int> vis(tree.size());
    function<void(int, ll)> dfs = [&](int x, ll cur) {
        vis[x] = 1;
        mx[x] = cur;
        for (auto [y, w] : tree[x]) if (!vis[y]) dfs(y, max(cur, w));
    };
    dfs(u, 0);
    return mx[target];
}

ll secondBest(int n, const vector<Sisi>& sisi, const vector<int>& inMST,
              const vector<vector<pair<int, ll>>>& tree, ll totMST) {
    ll best = INF;
    for (auto e : sisi) if (!inMST[e.id]) {
        ll mx = maxDiJalur(e.u, e.v, tree);
        if (mx < 0) continue;
        ll cand = totMST - mx + e.w;
        if (cand > totMST) best = min(best, cand);
    }
    return best >= INF ? -1 : best;
}

ll kruskalWajib(int n, vector<Sisi> sisi, const vector<Sisi>& wajib) {
    DSU d(n);
    ll tot = 0;
    int k = 0;
    for (auto e : wajib) {
        if (!d.unite(e.u, e.v)) return -1;       // wajib membentuk siklus
        tot += e.w;
        k++;
    }
    sort(sisi.begin(), sisi.end());
    for (auto e : sisi) if (d.unite(e.u, e.v)) { tot += e.w; k++; }
    return k == n - 1 ? tot : -1;
}

int main() {
    vector<Sisi> sisi = {
        {1, 0, 1, 0}, {2, 1, 2, 1}, {2, 0, 2, 2}, {3, 1, 3, 3}, {4, 2, 4, 4},
        {4, 3, 4, 5}, {5, 3, 5, 6}, {6, 4, 5, 7}, {10, 0, 5, 8}
    };
    cout << bottleneckMin(6, sisi) << '\n';        // 5
    cout << mstMaksimum(6, sisi) << '\n';          // 25
    return 0;
}
```

MST maksimum (Kruskal menurun) pada graf yang sama: 10 (`0-5`) + 6 (`4-5`) + 4 (`3-4`) + 3 (`1-3`) + 2 (`1-2`) = **25**. Jangan menjumlahkan lima sisi terberat mentah-mentah (itu 28 dan biasanya membuat siklus).

**Jebakan:**

1. Second-best yang **sama** total dengan MST (ada banyak MST) vs **ketat lebih besar**. Baca soal.
2. `maxDiJalur` `O(n)` per sisi non-MST → `O(n m)`. Untuk `n=1e5` butuh binary lifting (file 17).
3. Sisi wajib yang sudah siklus: langsung mustahil, bukan “skip”.
4. Bottleneck pada graf berarah bukan MST.

**Kompleksitas:** Kruskal/Prim biasa; second-best naif `O(n m)`; bottleneck = sisi terakhir Kruskal `O(m log m)`.

---

## Johnson semua pasangan

**Teori:** Floyd `O(n³)` mahal jika graf jarang. Johnson: tambah simpul dummy `s` dengan sisi 0 ke semua simpul, Bellman-Ford dari `s` memberi potensial `h[v]`. Bobot baru `w'(u,v) = w(u,v) + h[u] - h[v]` dijamin `≥ 0` (bukti: `h[v] ≤ h[u] + w(u,v)`). Lalu Dijkstra dari setiap simpul pada `w'`, kembalikan `dist(u,v) = dist'(u,v) - h[u] + h[v]`. Analoginya: menaik-turunkan “ketinggian” kota supaya semua tanjakan tidak negatif, tanpa mengubah jalur terpendek.

**Kapan dipakai:** semua pasangan, `n ≤ 2000` jarang, ada bobot negatif tanpa siklus negatif. Jangan jika `n ≤ 400` padat — Floyd lebih pendek. Jangan jika ada siklus negatif (Bellman dummy gagal).

**Proses:** sisi `0→1 (1), 1→2 (-3), 0→2 (2)`. Dummy 3 ke 0,1,2 bobot 0.

Bellman dari 3: `h = [0, 0, -3]` untuk simpul 0,1,2 (1→2 menurunkan 2).

```
w'(0,1) = 1 + 0 - 0 = 1
w'(1,2) = -3 + 0 - (-3) = 0
w'(0,2) = 2 + 0 - (-3) = 5
```

Dijkstra dari 0 pada `w'`: dist' `[0, 1, 1]`. Kembali: ke 2 = `1 - 0 + (-3) = -2`. Cocok `0-1-2 = 1-3 = -2`, lebih baik dari `0-2 = 2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 4e18;

struct Edge { int u, v; ll w; };

vector<ll> dijkstraW(int n, const vector<vector<pair<int, ll>>>& g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) if (d + w < dist[v]) {
            dist[v] = d + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

pair<bool, vector<vector<ll>>> johnson(int n, const vector<Edge>& e) {
    vector<Edge> ee = e;
    int s = n;
    for (int v = 0; v < n; v++) ee.push_back({s, v, 0});
    vector<ll> h(n + 1, INF);
    h[s] = 0;
    for (int it = 0; it < n + 1; it++) {
        bool ubah = false;
        for (auto [u, v, w] : ee) {
            if (h[u] >= INF) continue;
            if (h[u] + w < h[v]) {
                h[v] = h[u] + w;
                ubah = true;
                if (it == n) return {false, {}};
            }
        }
        if (!ubah) break;
    }
    vector<vector<pair<int, ll>>> g(n);
    for (auto [u, v, w] : e)
        g[u].push_back({v, w + h[u] - h[v]});
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for (int u = 0; u < n; u++) {
        auto dist = dijkstraW(n, g, u);
        for (int v = 0; v < n; v++)
            if (dist[v] < INF) d[u][v] = dist[v] - h[u] + h[v];
    }
    return {true, d};
}

int main() {
    vector<Edge> e = {{0, 1, 1}, {1, 2, -3}, {0, 2, 2}};
    auto [ok, d] = johnson(3, e);
    cout << ok << ' ' << d[0][2] << '\n';          // 1 -2
    return 0;
}
```

**Jebakan:**

1. Lupa mengembalikan `dist' - h[u] + h[v]`.
2. Dummy tidak dihubungkan ke semua simpul: komponen tak tercapai punya `h = INF`, `w'` rusak.
3. Memakai Johnson padahal ada siklus negatif: harus gagal di Bellman, bukan diam-diam Dijkstra.

**Kompleksitas:** `O(n m)` Bellman + `n` Dijkstra = `O(n m log n)` heap, memori `O(n²)` untuk matriks hasil.

---

## Ringkasan file ini

**Teori:** Relaksasi adalah satu kalimat: “apakah lewat `u` lebih murah?”. Dijkstra mengunci yang terkecil karena bobot tak negatif. Bellman mengulang sampai jalur sederhana habis. Floyd membuka transit satu-satu. MST memakai cut property, bukan jarak.

**Kapan dipakai:** lihat tabel di puncak file. Kartu saku: `w≥0` → Dijkstra; ada minus → Bellman; `n` kecil semua pasangan → Floyd; sambung semua → Kruskal.

**Proses:** uji selalu graf 4–6 simpul di `main` sebelum menempel ke soal. Cocokkan angka tangan dengan `dist`.

**Kode:** semua fungsi di atas modular. Kruskal memakai DSU ringkas; teori DSU penuh di file 12.

**Jebakan lintas topik:**

1. `INF` overflow.
2. Dijkstra + sisi negatif.
3. Floyd loop bukan `k` di luar.
4. Prim memakai `+` seperti Dijkstra.
5. 1-indexed vs 0-indexed pada DSU.

**Kompleksitas saku:**

| Alat | Waktu |
|---|---|
| Dijkstra heap | `O(m log n)` |
| Dijkstra padat | `O(n²)` |
| Bellman / SPFA terburuk | `O(n m)` |
| Floyd | `O(n³)` |
| Kruskal | `O(m log m)` |
| Prim heap / padat | `O(m log n)` / `O(n²)` |
| Johnson | `O(n m log n)` |

### Latihan harian

`ComProgLearning/CP/` Day 127, 129, 131, 136. Jangan menyalin 2500 file latihan ke ensiklopedia.

### Isi file berikutnya

File 12: DSU lengkap, SCC (Kosaraju/Tarjan), jembatan dan titik artikulasi, 2-SAT, aliran maksimum, matching bipartit, MCMF.
