# Flood fill dan komponen terhubung

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **117**. Mewarnai daerah yang saling nyambung: di graf abstrak itu komponen terhubung, di peta itu flood fill. Dasar DFS/BFS ada di [dfs-bfs.md](dfs-bfs.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Komponen terhubung](#komponen-terhubung)
- [Flood fill 4 arah](#flood-fill-4-arah)
- [Delapan arah dan diagonal](#delapan-arah-dan-diagonal)
- [Label, ukuran, dan agregat](#label-ukuran-dan-agregat)
- [Grid hidup satu-satu](#grid-hidup-satu-satu)
- [Keterhubungan lemah](#keterhubungan-lemah)
- [Ringkasan](#ringkasan)

---

## Komponen terhubung

**Teori:** Dua simpul satu komponen jika ada jalur (abaikan arah jika graf tak berarah). Flood fill di graf adalah DFS/BFS yang menempelkan `id` yang sama ke semua yang tercapai dari seorang wakil. Jumlah wakil = jumlah komponen. Analoginya: tuang cat di satu kota, cat mengalir ke kota yang punya jalan; kota yang tidak kena cat butuh tuangan baru.

**Kapan:** “berapa kelompok teman”, “bisa dari A ke B?”, pewarnaan partisi. Jangan flood jika sisi **bertambah seiring waktu** dan kamu butuh jawaban setelah setiap tambah — itu DSU di [dsu-mst.md](dsu-mst.md). Jangan memakai komponen tak berarah sebagai SCC.

**Proses:** sisi `0-1, 1-2, 3-4`. Simpul 5 terisolasi.

```
0—1—2    3—4    5
```

| wakil | BFS | id | ukuran |
|---|---|---|---|
| 0 | 0, 1, 2 | 0 | 3 |
| 3 | 3, 4 | 1 | 2 |
| 5 | 5 | 2 | 1 |

`k = 3`. `id = [0, 0, 0, 1, 1, 2]`. A dan B satu komponen iff `id[A] == id[B]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int komponenTerhubung(int n, const vector<vector<int>>& g, vector<int>& id) {
    id.assign(n, -1);
    int k = 0;
    for (int s = 0; s < n; s++) if (id[s] == -1) {
        queue<int> q;
        q.push(s);
        id[s] = k;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (id[v] == -1) {
                id[v] = k;
                q.push(v);
            }
        }
        k++;
    }
    return k;
}

void dfsKomponen(int u, int k, const vector<vector<int>>& g, vector<int>& id) {
    id[u] = k;
    for (int v : g[u]) if (id[v] == -1) dfsKomponen(v, k, g, id);
}

int komponenDFS(int n, const vector<vector<int>>& g, vector<int>& id) {
    id.assign(n, -1);
    int k = 0;
    for (int s = 0; s < n; s++) if (id[s] == -1) {
        dfsKomponen(s, k, g, id);
        k++;
    }
    return k;
}

bool satuKomponen(int n, const vector<int>& id, int a, int b) {
    return id[a] == id[b];
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1}, {0, 2}, {1}, {4}, {3}, {}};
    vector<int> id;
    cout << komponenTerhubung(6, g, id) << '\n';   // 3
    cout << satuKomponen(6, id, 0, 2) << ' ' << satuKomponen(6, id, 0, 3) << '\n';
    // 1 0
    return 0;
}
```

**Jebakan:**

1. Hanya menelusuri dari simpul 0: komponen lain tidak terhitung.
2. Graf berarah diperlakukan tak berarah tanpa menambahkan sisi balik — “bisa kirim pesan” bukan komponen biasa, itu SCC.
3. `id` tidak di-reset antar tes.
4. Simpul terisolasi tetap komponen berukuran 1; jangan diskip.

**Kompleksitas:** `O(n + m)`. Setiap simpul dan sisi sekali.

---

## Flood fill 4 arah

**Teori:** Di grid, “tetangga” adalah sel atas-bawah-kiri-kanan (4 arah). Flood fill mewarnai semua sel bernilai sama yang terhubung. Analoginya menuang cat pada peta: cat berhenti di tembok. Implementasi BFS lebih aman di grid `1000 × 1000` karena rekursi DFS bisa meledak stack.

**Kapan:** “berapa pulau `'.'`”, “ukuran daerah”, “isi ember”. Jangan rekursi flood pada grid besar tanpa yakin stack. Jangan 4 arah jika soal bilang diagonal nyambung.

**Proses:** grid 4×5, `#` tembok, `.` lantai.

```
. # . . #
. # # . .
# . . # .
. . # . .
```

Mulai `(0,0)` 4-arah: hanya `(0,0)` dan `(1,0)` — ukuran 2.

| antrian | sel | cat id 1 |
|---|---|---|
| `[(0,0)]` | (0,0) | ya |
| `[(1,0)]` | (1,0) | ya |
| `[]` | selesai | ukuran 2 |

Wakil berikutnya `(0,2)` mewarnai `(0,2),(0,3),(1,3),(1,4)` — 4 sel. Lalu `(2,1)` menyentuh daerah tengah-bawah. Lalu pulau kanan-bawah. Total **4** pulau lantai 4-arah (uji di `main`).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int DR4[4] = {-1, 1, 0, 0};
const int DC4[4] = {0, 0, -1, 1};

bool dalam(int r, int c, int R, int C) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

int floodUkuran(vector<string>& a, int sr, int sc, char dari, char ke) {
    int R = (int)a.size(), C = (int)a[0].size();
    if (a[sr][sc] != dari) return 0;
    queue<pair<int, int>> q;
    q.push({sr, sc});
    a[sr][sc] = ke;
    int sz = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        sz++;
        for (int k = 0; k < 4; k++) {
            int nr = r + DR4[k], nc = c + DC4[k];
            if (!dalam(nr, nc, R, C) || a[nr][nc] != dari) continue;
            a[nr][nc] = ke;
            q.push({nr, nc});
        }
    }
    return sz;
}

int hitungPulau(vector<string> a) {
    int R = (int)a.size(), ans = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < (int)a[r].size(); c++)
            if (a[r][c] == '.') {
                floodUkuran(a, r, c, '.', '#');
                ans++;
            }
    return ans;
}

int main() {
    FASTIO;
    vector<string> grid = {".#..#", ".##..", "#..#.", "..#.."};
    cout << hitungPulau(grid) << '\n';
    vector<string> g2 = grid;
    cout << floodUkuran(g2, 0, 0, '.', '#') << '\n'; // 2
    return 0;
}
```

**Jebakan:**

1. Menandai `vis` setelah pop di grid besar: antrean meledak karena sel yang sama didorong dari banyak tetangga. Tandai **saat push**.
2. Recolor `'.'` menjadi `'#'` menimpa peta asli — salin grid jika masih dipakai.
3. `(r, c)` vs `(x, y)` tertukar; `n` baris `m` kolom dibaca terbalik.
4. Karakter tembok bukan hanya `'#'` — baca pernyataan.

**Kompleksitas:** `O(R C)`. Setiap sel sekali.

---

## Delapan arah dan diagonal

**Teori:** 8 arah menambah 4 diagonal. Dua sel yang hanya bertemu di sudut menjadi satu daerah. Analoginya percikan tinta: kalau soal menganggap “bersentuhan termasuk sudut”, pakai 8. Pilihan 4 vs 8 mengubah jumlah pulau.

**Kapan:** soal “pulau” sering 8-arah (diagonal nyambung). Soal “labirin jalan” hampir selalu 4-arah. Baca kalimat “bersebelahan termasuk diagonal”.

**Proses:** grid 3×3:

```
. # .
# . #
. # .
```

4-arah: 5 pulau `'.'` terpisah (tengah + 4 sudut). 8-arah: semua `'.'` nyambung lewat diagonal → **1** pulau.

Langkah 8-arah dari `(0,0)`:

| antrian | ambil | tetangga `.` baru |
|---|---|---|
| `[(0,0)]` | (0,0) | (1,1) diagonal |
| `[(1,1)]` | (1,1) | (0,2), (2,0), (2,2) |
| empat sudut | selesai | 5 sel, 1 komponen |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int DR4[4] = {-1, 1, 0, 0};
const int DC4[4] = {0, 0, -1, 1};
const int DR8[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DC8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int floodArah(vector<string>& a, int sr, int sc, char dari, char ke,
              const int* dr, const int* dc, int nArah) {
    int R = (int)a.size(), C = (int)a[0].size();
    if (a[sr][sc] != dari) return 0;
    queue<pair<int, int>> q;
    q.push({sr, sc});
    a[sr][sc] = ke;
    int sz = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        sz++;
        for (int k = 0; k < nArah; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (a[nr][nc] != dari) continue;
            a[nr][nc] = ke;
            q.push({nr, nc});
        }
    }
    return sz;
}

int hitungPulauArah(vector<string> a, bool delapan) {
    const int* dr = delapan ? DR8 : DR4;
    const int* dc = delapan ? DC8 : DC4;
    int nA = delapan ? 8 : 4, ans = 0;
    for (int r = 0; r < (int)a.size(); r++)
        for (int c = 0; c < (int)a[r].size(); c++)
            if (a[r][c] == '.') {
                floodArah(a, r, c, '.', '#', dr, dc, nA);
                ans++;
            }
    return ans;
}

int main() {
    FASTIO;
    vector<string> a = {".#.", "#.#", ".#."};
    cout << hitungPulauArah(a, false) << ' ' << hitungPulauArah(a, true) << '\n';
    // 5 1
    return 0;
}
```

**Jebakan:**

1. Menyalin hanya 4 arah padahal contoh soal memakai diagonal.
2. Array `DR8` 8 elemen tetapi loop `k < 4`.
3. Grid tidak persegi: `a[r].size()` bisa beda — jangan asumsikan `C` global tanpa cek.

**Kompleksitas:** tetap `O(R C)`. Konstanta 8 vs 4 tidak mengubah orde.

---

## Label, ukuran, dan agregat

**Teori:** Selain menghitung banyaknya daerah, soal sering minta ukuran terbesar, jumlah nilai di daerah, atau keliling. Setelah flood, simpan `sz[id]` dan `agg[id]`. Analoginya: setiap genangan punya volume dan luas permukaan.

**Kapan:** “pulau terbesar”, “jumlah ‘1’ di komponen”, perimeter. Jangan menghitung keliling dengan rumus salah: tiap sisi sel yang bertemu tembok/luar peta menambah 1, atau rumus `4*sz - 2*sisi_dalam`.

**Proses:** grid

```
1 1 0
1 0 0
0 0 1
```

Komponen `1` kiri-atas ukuran 3, komponen kanan-bawah ukuran 1. Terbesar = 3.

Keliling komponen 3 (bentuk L): sel (0,0) 2 sisi luar + 1 ke 0 di kanan? Hitung sisi yang tidak menempel `1` lain.

```
(0,0): atas, kiri = 2 (bawah dan kanan menempel 1)
(0,1): atas, kanan, bawah = 3 (kiri menempel)
(1,0): kiri, bawah, kanan = 3 (atas menempel)
total keliling = 8
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};

struct InfoDaerah {
    vector<int> id;
    vector<int> sz;
    int R, C, ncomp = 0;
};

InfoDaerah labelGrid(const vector<string>& a, char hidup) {
    int R = (int)a.size(), C = (int)a[0].size();
    InfoDaerah info;
    info.R = R;
    info.C = C;
    info.id.assign(R * C, -1);
    auto idx = [&](int r, int c) { return r * C + c; };
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (a[r][c] != hidup || info.id[idx(r, c)] != -1) continue;
            queue<pair<int, int>> q;
            q.push({r, c});
            info.id[idx(r, c)] = info.ncomp;
            int s = 0;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                s++;
                for (int k = 0; k < 4; k++) {
                    int nx = x + DR[k], ny = y + DC[k];
                    if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
                    if (a[nx][ny] != hidup || info.id[idx(nx, ny)] != -1) continue;
                    info.id[idx(nx, ny)] = info.ncomp;
                    q.push({nx, ny});
                }
            }
            info.sz.push_back(s);
            info.ncomp++;
        }
    return info;
}

int kelilingKomponen(const vector<string>& a, const InfoDaerah& info, int want, char hidup) {
    int R = info.R, C = info.C, ans = 0;
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++) {
            if (info.id[r * C + c] != want) continue;
            for (int k = 0; k < 4; k++) {
                int nr = r + DR[k], nc = c + DC[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || a[nr][nc] != hidup) ans++;
            }
        }
    return ans;
}

int ukuranTerbesar(const InfoDaerah& info) {
    int mx = 0;
    for (int s : info.sz) mx = max(mx, s);
    return mx;
}

int main() {
    FASTIO;
    vector<string> a = {"110", "100", "001"};
    auto info = labelGrid(a, '1');
    cout << info.ncomp << ' ' << ukuranTerbesar(info) << '\n'; // 2 3
    cout << kelilingKomponen(a, info, 0, '1') << '\n';         // 8
    return 0;
}
```

**Jebakan:**

1. `id` diisi `r*C+c` tetapi `C` memakai `n` (baris) — indeks tabrakan.
2. Keliling dihitung `4*sz` tanpa mengurangi sisi dalam.
3. `ukuranTerbesar` pada grid kosong harus 0, bukan sampah.

**Kompleksitas:** label `O(R C)`, keliling satu komponen `O(R C)` naif (boleh, grid kecil) atau `O(sz)` jika hanya iterasi anggota.

---

## Grid hidup satu-satu

**Teori:** Kadang sel “hidup” muncul satu per satu (air merendam, virus menyebar per query). Flood ulang tiap query adalah `O(Q R C)`. DSU memetakan `(r,c) → r*C+c` dan `unite` ke tetangga yang sudah hidup. Analoginya: pulau-pulau baru menyatu saat jembatan darat muncul.

**Kapan:** query “hidupkan sel, berapa pulau sekarang?”. Jangan DSU jika kamu butuh **hapus** sel (DSU tidak bisa split) kecuali proses mundur. Detail DSU di [dsu-mst.md](dsu-mst.md).

**Proses:** grid 2×2, hidupkan `(0,0), (0,1), (1,1), (1,0)`.

| hidup | unite tetangga hidup | pulau |
|---|---|---|
| (0,0) | — | 1 |
| (0,1) | ke (0,0) | 1 |
| (1,1) | ke (0,1) | 1 |
| (1,0) | ke (0,0) dan (1,1), sudah satu | 1 |

Kalau urutan `(0,0), (1,1)` dulu: 2 pulau, lalu `(0,1)` menyatukan keduanya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    int komponen;
    DSU(int n) : par(n), sz(n, 1), komponen(n) {
        iota(par.begin(), par.end(), 0);
    }
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

int idxGrid(int r, int c, int C) { return r * C + c; }

vector<int> pulauOnline(int R, int C, const vector<pair<int, int>>& hidup) {
    DSU d(R * C);
    d.komponen = 0;
    vector<int> on(R * C, 0), jejak;
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    for (auto [r, c] : hidup) {
        int u = idxGrid(r, c, C);
        if (on[u]) { jejak.push_back(d.komponen); continue; }
        on[u] = 1;
        d.komponen++;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            int v = idxGrid(nr, nc, C);
            if (on[v]) d.unite(u, v);
        }
        jejak.push_back(d.komponen);
    }
    return jejak;
}

int main() {
    FASTIO;
    auto j = pulauOnline(2, 2, {{0, 0}, {1, 1}, {0, 1}});
    for (int x : j) cout << x << ' ';
    cout << '\n';                                  // 1 2 1
    return 0;
}
```

**Jebakan:**

1. `komponen` DSU diinisialisasi `n` (semua sel), padahal sel mati bukan pulau.
2. Hidupkan sel yang sama dua kali tanpa guard.
3. `r*C+c` vs `c*R+r` tercampur.

**Kompleksitas:** `O(Q α(RC))` plus tetangga konstan.

---

## Keterhubungan lemah

**Teori:** Pada graf **berarah**, “bisa jalan tanpa peduli arah” adalah komponen **lemah**: anggap setiap sisi dua arah, lalu flood biasa. “Saling mencapai mengikuti anak panah” adalah SCC di [scc-bridge.md](scc-bridge.md). Analoginya: peta satu arah vs “kalau jalan boleh dilawan”.

**Kapan:** “jaringan tetap satu potong jika panah diabaikan”, syarat Euler berarah (lemah-terhubung). Jangan mengganti SCC dengan flood lemah.

**Proses:** sisi `0→1, 2→1`. Lemah: `{0,1,2}` satu komponen. Kuat: tiga SCC `{0},{1},{2}` karena tidak ada jalan balik.

| dari | tercapai di G | tercapai jika sisi dibalik ikut |
|---|---|---|
| 0 | 0, 1 | 0, 1, 2 |
| 1 | 1 | 0, 1, 2 |
| 2 | 2, 1 | 0, 1, 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int komponenLemah(int n, const vector<pair<int, int>>& sisi, vector<int>& id) {
    vector<vector<int>> g(n);
    for (auto [u, v] : sisi) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    id.assign(n, -1);
    int k = 0;
    for (int s = 0; s < n; s++) if (id[s] == -1) {
        queue<int> q;
        q.push(s);
        id[s] = k;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (id[v] == -1) {
                id[v] = k;
                q.push(v);
            }
        }
        k++;
    }
    return k;
}

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {2, 1}};
    vector<int> id;
    cout << komponenLemah(3, sisi, id) << '\n';    // 1
    return 0;
}
```

**Jebakan:**

1. Menambah sisi balik ke graf asli yang masih dipakai DFS berarah.
2. Mengira “lemah 1 komponen” berarti kuat-terhubung.
3. Isolasi derajat 0: tetap dihitung, Euler biasanya **mengabaikan** isolasi.

**Kompleksitas:** `O(n + m)`.

---

## Ringkasan

**Teori:** Komponen = flood. Grid = flood dengan 4 atau 8 arah. Query hidup = DSU. Berarah + abaikan panah = lemah, bukan SCC.

**Kapan:** pewarnaan daerah, pulau, ukuran, keliling, “nyambung tidak”. Sisi dinamis → DSU. Saling mencapai berarah → SCC.

**Proses:** uji grid 3×3 tangan, cocokkan jumlah pulau 4 vs 8, baru percaya kode.

**Jebakan lintas:**

1. 4 vs 8 arah.
2. Recolor menimpa peta.
3. Vis setelah pop.
4. DSU menghitung sel mati sebagai pulau.

**Kompleksitas saku:** grid `O(R C)`, graf `O(n + m)`, online `O(Q α)`.

Lanjut: [siklus-bipartit.md](siklus-bipartit.md) · [dfs-bfs.md](dfs-bfs.md) · [dsu-mst.md](dsu-mst.md)
