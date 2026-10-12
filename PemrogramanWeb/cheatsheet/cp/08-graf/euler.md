# Lintasan dan sirkuit Euler

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **121**. Lewati **setiap sisi tepat sekali**. Bukan Hamilton (setiap **simpul** sekali) — itu NP-berat. Dasar keterhubungan di [flood-komponen.md](flood-komponen.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Euler versus Hamilton](#euler-versus-hamilton)
- [Syarat tak berarah](#syarat-tak-berarah)
- [Syarat berarah](#syarat-berarah)
- [Hierholzer tak berarah](#hierholzer-tak-berarah)
- [Hierholzer berarah](#hierholzer-berarah)
- [Keluaran sisi dan de Bruijn](#keluaran-sisi-dan-de-bruijn)
- [Ringkasan](#ringkasan)

---

## Euler versus Hamilton

**Teori:** Lintasan Euler memakai setiap **sisi** tepat sekali (boleh mengulang simpul). Sirkuit Euler kembali ke awal. Lintasan Hamilton memakai setiap **simpul** tepat sekali. Analoginya: keliling kota memakai setiap **jalan** sekali (Euler) vs mengunjungi setiap **gedung** sekali (Hamilton). Hierholzer menyelesaikan Euler dalam `O(n+m)`. Hamilton tidak punya algoritma polinomial umum.

**Kapan:** “gambar tanpa angkat pena”, “urutkan domino”, rekonstruksi string dari pasangan beruntun. Jangan Hierholzer jika soal bilang “kunjungi kota sekali”.

**Proses:** graf `0-1, 1-2, 2-0, 0-3`.

```
Euler sirkuit? derajat 0=3 ganjil → bukan sirkuit.
Euler lintasan? dua ganjil (0 dan 3) → ya, mulai di 0 atau 3.
Hamilton lintasan? 3-0-1-2 memakai semua simpul, ya (kebetulan).
```

Graf lengkap `K_3` punya keduanya. Graf bintang 3 daun: Euler tidak (3 ganjil? pusat derajat 3, 3 daun derajat 1 → 4 ganjil), Hamilton tidak (daun tidak saling nyambung).

**Kode:** kerangka cek cepat (bukan Hierholzer).

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int hitungGanjil(const vector<int>& deg) {
    int g = 0;
    for (int d : deg) if (d & 1) g++;
    return g;
}

int main() {
    FASTIO;
    vector<int> deg = {3, 2, 2, 1}; // graf contoh
    cout << hitungGanjil(deg) << '\n';             // 2 → calon lintasan
    return 0;
}
```

**Jebakan:**

1. Menjawab Hamilton dengan Hierholzer.
2. Mengira “semua derajat genap” cukup tanpa keterhubungan.
3. Menghitung ganjil termasuk simpul isolasi (derajat 0 genap, aman, tetapi isolasi tidak boleh mematahkan syarat “yang berderajat > 0 terhubung”).

**Kompleksitas:** hitung derajat `O(n + m)`.

---

## Syarat tak berarah

**Teori:** Abaikan simpul isolasi. Sirkuit: graf terhubung dan semua derajat genap. Lintasan: terhubung dan tepat 0 atau 2 derajat ganjil (jika 0, itu sirkuit; jika 2, mulai di salah satu ganjil). Analoginya: di setiap persimpangan kamu masuk dan keluar berpasangan; ujung lintasan adalah dua persimpangan “sisa satu jalan”.

**Kapan:** cek dulu sebelum Hierholzer. Kalau syarat gagal, jangan jalankan tur — output “TIDAK”.

**Proses:** sisi `0-1, 1-2, 2-3, 3-0, 0-2`. Derajat: 0:3, 1:2, 2:3, 3:2 → dua ganjil (0 dan 2) → **lintasan**, start 0 atau 2.

```
    0 --- 1
    |\    |
    | \   |
    3---2
```

Jika hapus `0-2`: semua genap → sirkuit. Jika tambah `1-3` saja? Derajat 1 dan 3 jadi 3, sekarang 4 ganjil → mustahil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool eulerBisaTakBerarah(int n, const vector<pair<int, int>>& sisi, int& start) {
    vector<int> deg(n);
    vector<vector<int>> g(n);
    for (auto [u, v] : sisi) {
        deg[u]++;
        deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    start = 0;
    for (int i = 0; i < n; i++) if (deg[i]) { start = i; break; }
    int ganjil = 0;
    for (int i = 0; i < n; i++) if (deg[i] & 1) { ganjil++; start = i; }
    if (ganjil != 0 && ganjil != 2) return false;
    vector<int> vis(n);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs(v);
    };
    dfs(start);
    for (int i = 0; i < n; i++) if (deg[i] && !vis[i]) return false;
    return true;
}

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    int start;
    cout << eulerBisaTakBerarah(4, sisi, start) << ' ' << start << '\n';
    // 1  dan start 0 atau 2
    return 0;
}
```

**Jebakan:**

1. DFS dari simpul 0 yang isolasi: `start` harus simpul berderajat > 0.
2. Dua komponen, masing-masing derajat genap: syarat lokal lolos, global gagal.
3. `ganjil == 0` tetap Euler (sirkuit); jangan return false.

**Kompleksitas:** `O(n + m)`.

---

## Syarat berarah

**Teori:** Abaikan isolasi. Graf harus **lemah-terhubung** (abaikan arah). Sirkuit: `in[u] == out[u]` untuk semua u. Lintasan: tepat satu start `out = in+1`, tepat satu end `in = out+1`, sisanya sama. Analoginya: setiap simpang, jumlah masuk = jumlah keluar, kecuali ujung.

**Kapan:** “urutkan pasangan (a,b) sehingga b bertemu a berikutnya”, Euler pada graf kata. Jangan cek hanya `in==out` tanpa lemah-terhubung.

**Proses:** sisi `0→1, 1→2, 2→0, 0→2`.

| u | out | in | selisih |
|---|---|---|---|
| 0 | 2 | 1 | out = in+1 → start |
| 1 | 1 | 1 | sama |
| 2 | 1 | 2 | in = out+1 → end |

Lemah: satu komponen. Lintasan dari 0 ke 2. Contoh tur: `0-1-2-0-2`.

Kalau tambah `2→1`: in/out 1 dan 2 berubah, bisa jadi sirkuit atau rusak — hitung ulang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool eulerBisaBerarah(int n, const vector<pair<int, int>>& sisi, int& start) {
    vector<int> in(n), out(n);
    vector<vector<int>> und(n);
    for (auto [u, v] : sisi) {
        out[u]++;
        in[v]++;
        und[u].push_back(v);
        und[v].push_back(u);
    }
    start = 0;
    for (int i = 0; i < n; i++) if (in[i] + out[i]) { start = i; break; }
    int nStart = 0, nEnd = 0;
    for (int i = 0; i < n; i++) {
        if (out[i] == in[i]) continue;
        if (out[i] == in[i] + 1) { nStart++; start = i; }
        else if (in[i] == out[i] + 1) nEnd++;
        else return false;
    }
    if (!((nStart == 0 && nEnd == 0) || (nStart == 1 && nEnd == 1))) return false;
    vector<int> vis(n);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : und[u]) if (!vis[v]) dfs(v);
    };
    dfs(start);
    for (int i = 0; i < n; i++) if ((in[i] + out[i]) && !vis[i]) return false;
    return true;
}

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 0}, {0, 2}};
    int start;
    cout << eulerBisaBerarah(3, sisi, start) << ' ' << start << '\n'; // 1 0
    return 0;
}
```

**Jebakan:**

1. Cek kuat-terhubung (SCC=1) padahal cukup lemah plus syarat derajat.
2. Dua start (`out=in+1` dua kali).
3. Start di end, bukan di `out=in+1`.

**Kompleksitas:** `O(n + m)`.

---

## Hierholzer tak berarah

**Teori:** Dari simpul sekarang, jalan greedy menyusuri sisi belum dipakai sampai macet. Macet = sirkuit lokal selesai. Sisipkan sirkuit itu ke tur global, lanjut sisa sisi di simpul sebelumnya. Analoginya: keliling sampai pulang, lalu sisipkan putaran kecil di persimpangan yang masih punya jalan. Sisi tak berarah harus punya **id** dan `used[id]`, bukan hanya hapus satu arah.

**Kapan:** syarat sudah lolos. Output barisan simpul panjang `m+1`.

**Proses:** sisi id `0:0-1, 1:1-2, 2:2-3, 3:3-0, 4:0-2`. Start 0.

| stack | sisi terpakai | catatan |
|---|---|---|
| `[0]` | — | mulai |
| `[0, 1]` | 0-1 | |
| `[0, 1, 2]` | 1-2 | |
| `[0, 1, 2, 3]` | 2-3 | |
| `[0, 1, 2, 3, 0]` | 3-0 | |
| `[0, 1, 2, 3, 0, 2]` | 0-2 | 0 macet setelah ini |
| pop 2,0,3,2,1,0 | | tur balik lalu di-reverse |

Tur `0-1-2-3-0-2` memakai 5 sisi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct EulerTakBerarah {
    int n;
    vector<vector<pair<int, int>>> g; // {tetangga, id}
    vector<int> used;

    EulerTakBerarah(int n, const vector<pair<int, int>>& sisi) : n(n), g(n) {
        used.assign((int)sisi.size(), 0);
        for (int i = 0; i < (int)sisi.size(); i++) {
            int u = sisi[i].first, v = sisi[i].second;
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }
    }

    vector<int> hierholzer(int start) {
        vector<int> st = {start}, path, it(n, 0);
        while (!st.empty()) {
            int u = st.back();
            while (it[u] < (int)g[u].size() && used[g[u][it[u]].second]) it[u]++;
            if (it[u] == (int)g[u].size()) {
                path.push_back(u);
                st.pop_back();
            } else {
                auto [v, id] = g[u][it[u]++];
                used[id] = 1;
                st.push_back(v);
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    EulerTakBerarah e(4, sisi);
    auto p = e.hierholzer(0);
    for (int x : p) cout << x << ' ';
    cout << '\n';
    cout << ((int)p.size() == 6) << '\n';          // m+1 = 6
    return 0;
}
```

**Jebakan:**

1. Tanpa id: sisi `u-v` terpakai satu arah, balik masih “hidup”.
2. Start di derajat genap padahal ada 2 ganjil: sisa sisi, `path.size() != m+1`.
3. Lupa `reverse`.
4. Multi-sisi: id membedakan dua kabel paralel.

**Kompleksitas:** `O(n + m)`. Pointer `it[u]` mencegah menyapu sisi bekas.

---

## Hierholzer berarah

**Teori:** Sama, tetapi sisi hanya satu arah, tidak perlu `used[id]` jika setiap sisi list dihapus lewat pointer `it[u]`. Analoginya: setiap tiket sekali pakai dari kota u.

**Kapan:** graf berarah yang syaratnya lolos. Start di `out = in+1` atau sembarang simpul berderajat jika sirkuit.

**Proses:** sisi `0→1, 1→2, 2→0, 0→2`. Start 0.

| stack | sisa out | aksi |
|---|---|---|
| `[0]` | 0 punya 1,2 | ambil 1 |
| `[0,1]` | 1 punya 2 | ambil 2 |
| `[0,1,2]` | 2 punya 0 | ambil 0 |
| `[0,1,2,0]` | 0 sisa 2 | ambil 2 |
| `[0,1,2,0,2]` | 2 kosong | pop 2 |
| | 0 kosong | pop 0,2,1,0 |

Reverse: `0 1 2 0 2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> eulerBerarahDari(int start, vector<vector<int>> g) {
    int n = (int)g.size();
    vector<int> st = {start}, path, it(n, 0);
    while (!st.empty()) {
        int u = st.back();
        if (it[u] < (int)g[u].size()) st.push_back(g[u][it[u]++]);
        else {
            path.push_back(u);
            st.pop_back();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

bool turLengkap(const vector<int>& path, int m) {
    return (int)path.size() == m + 1;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1, 2}, {2}, {0}};
    auto p = eulerBerarahDari(0, g);
    for (int x : p) cout << x << ' ';
    cout << '\n';                                  // 0 1 2 0 2
    cout << turLengkap(p, 4) << '\n';              // 1
    return 0;
}
```

**Jebakan:**

1. `g` di-pass by value agar `it` aman; jika referensi dan `it` global, tes kedua rusak.
2. Tidak memverifikasi `path.size() == m+1` setelah Hierholzer (syarat derajat lolos tetapi komponen lemah pecah).
3. Start 0 isolasi.

**Kompleksitas:** `O(n + m)`.

---

## Keluaran sisi dan de Bruijn

**Teori:** Soal kadang minta **id sisi**, bukan simpul. Simpan `(v, id)` di stack. Pola de Bruijn: simpul = string panjang `k-1`, sisi = string panjang `k`. Tur Euler pada graf itu merangkai string superpendek yang memuat semua substring. Analoginya: merangkai overlapping.

**Kapan:** “susun n pasangan beruntun”, “circular string memuat semua biner panjang k”. Jangan membangun string dengan backtrack `k!` jika Euler muat.

**Proses:** pasangan `ab, bc, cd, da`. Simpul huruf, sisi kata. Tur `a-b-c-d-a` merangkai `abcd` (sirkuit menutup).

Numerik: sisi id 10,11,12. Hierholzer mencatat id saat meninggalkan u.

```
stack simpul [0,1,2], id terpakai [10,11]
pop → path simpul ...
path id = [10, 11, 12] setelah reverse sesuai implementasi
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> eulerIdTakBerarah(int n, const vector<pair<int, int>>& sisi, int start) {
    int m = (int)sisi.size();
    vector<vector<pair<int, int>>> g(n);
    vector<int> used(m, 0);
    for (int i = 0; i < m; i++) {
        g[sisi[i].first].push_back({sisi[i].second, i});
        g[sisi[i].second].push_back({sisi[i].first, i});
    }
    vector<int> st = {start}, pathId, it(n, 0);
    vector<int> lastId(n, -1);
    // jejak id yang dipakai untuk masuk ke st.back()
    vector<int> edgeInto = {-1};
    while (!st.empty()) {
        int u = st.back();
        while (it[u] < (int)g[u].size() && used[g[u][it[u]].second]) it[u]++;
        if (it[u] == (int)g[u].size()) {
            if (edgeInto.back() != -1) pathId.push_back(edgeInto.back());
            st.pop_back();
            edgeInto.pop_back();
        } else {
            auto [v, id] = g[u][it[u]++];
            used[id] = 1;
            st.push_back(v);
            edgeInto.push_back(id);
        }
    }
    reverse(pathId.begin(), pathId.end());
    return pathId;
}

string rangkaiHuruf(const vector<pair<char, char>>& pasangan) {
    // simpul = huruf, asumsikan 'a'.. dan Euler sudah dijamin
    map<char, vector<char>> g;
    map<char, int> in, out;
    for (auto [a, b] : pasangan) {
        g[a].push_back(b);
        out[a]++;
        in[b]++;
    }
    char start = pasangan[0].first;
    for (auto [c, k] : out)
        if (k == in[c] + 1) start = c;
    map<char, int> it;
    vector<char> st = {start}, path;
    while (!st.empty()) {
        char u = st.back();
        if (it[u] < (int)g[u].size()) st.push_back(g[u][it[u]++]);
        else {
            path.push_back(u);
            st.pop_back();
        }
    }
    reverse(path.begin(), path.end());
    return string(path.begin(), path.end());
}

int main() {
    FASTIO;
    vector<pair<int, int>> sisi = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}};
    auto ids = eulerIdTakBerarah(4, sisi, 0);
    cout << ids.size() << '\n';                    // 5
    vector<pair<char, char>> p = {{'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'a'}};
    cout << rangkaiHuruf(p) << '\n';               // abcda
    return 0;
}
```

**Jebakan:**

1. Merangkai substring: karakter pertama saja lalu append huruf terakhir tiap sisi — off-by-one jika kamu append seluruh string.
2. `pathId.size()` harus `m`, bukan `m+1`.
3. Huruf di luar `map` tidak punya `in`/`out` 0 secara eksplisit — start salah.

**Kompleksitas:** `O(n + m)` plus `O(m log Σ)` jika pakai `map` huruf.

---

## Ringkasan

**Teori:** Cek derajat + keterhubungan, mulai di ujung yang benar, Hierholzer stack + pointer sisi. Euler ≠ Hamilton.

**Kapan:** setiap sisi sekali. String overlapping. Domino. Bukan TSP.

**Proses:** hitung ganjil tangan, gambar tur `0-1-2-3-0-2`, cocokkan `m+1`.

**Jebakan lintas:**

1. Tanpa id di tak berarah.
2. Start salah.
3. Dua komponen genap.
4. Output simpul vs id sisi.

**Kompleksitas saku:** `O(n + m)`.

Lanjut: [bfs-state.md](bfs-state.md) · [flood-komponen.md](flood-komponen.md) · [topo-dp-dag.md](topo-dp-dag.md)
