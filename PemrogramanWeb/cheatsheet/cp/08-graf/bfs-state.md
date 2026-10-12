# BFS pada ruang state

[← 08 Graf](README.md) · [Indeks CP](../README.md)

Day **124**. “Simpul” bukan tempat, melainkan **keadaan**. BFS biasa dan 0-1 BFS tetap benar jika biaya transisi seragam atau `{0,1}`. Dasar antrean di [dfs-bfs.md](dfs-bfs.md).

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Ide state](#ide-state)
- [Encoding id](#encoding-id)
- [Labirin plus kunci](#labirin-plus-kunci)
- [Dua token](#dua-token)
- [Operasi pada angka](#operasi-pada-angka)
- [0-1 BFS di state](#0-1-bfs-di-state)
- [Ringkasan](#ringkasan)

---

## Ide state

**Teori:** BFS menghitung jarak di graf. Kamu bebas memilih apa itu simpul, asal transisi berbiaya 1 (atau 0/1). State memuat **semua informasi** yang membedakan “bisa/tidak” ke depan. Analoginya: kamu bukan hanya di ruangan, tetapi “di ruangan plus sudah punya kunci merah”. Dua orang di ruangan sama dengan kunci beda adalah dua simpul beda.

**Kapan:** labirin + kunci, sliding puzzle kecil, knight + status, “minimum operasi mengubah string” jika alfabet kecil. Jangan jika biaya transisi tidak seragam — Dijkstra. Jangan jika `|S|` di atas ~1e7.

**Proses:** koridor 4 sel `0-1-2-3`, kunci di sel 1, pintu 2→3 butuh kunci. Start `(pos=0, kunci=0)`, goal `(3, 1)`.

| dist | state `(pos, kunci)` | catatan |
|---|---|---|
| 0 | (0, 0) | start |
| 1 | (1, 1) | ambil kunci di tempat, sering digabung |
| 2 | (2, 1) | |
| 3 | (3, 1) | goal |

Tanpa bit kunci, BFS dari 0 ke 3 menjawab 3 tetapi **curang** (pintu tidak dicek). `vis` hanya pada `pos` membuat kunci diabaikan.

**Kode:** kerangka id.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int idState(int pos, int mask, int nMask) {
    return pos * nMask + mask;
}

pair<int, int> pecah(int id, int nMask) {
    return {id / nMask, id % nMask};
}

int main() {
    FASTIO;
    int nMask = 2;
    int id = idState(3, 1, nMask);
    auto [p, m] = pecah(id, nMask);
    cout << id << ' ' << p << ' ' << m << '\n';    // 7 3 1
    return 0;
}
```

**Jebakan:**

1. State kurang field: BFS menemukan jalur mustahil atau kehilangan jalur.
2. `vis` hanya posisi.
3. `|S| = n * n * n` dengan `n = 400` (64 juta) tanpa alasan.

**Kompleksitas:** `O(|S| + |transisi|)`.

---

## Encoding id

**Teori:** Ubah tuple jadi integer agar `dist` dan `queue<int>` sederhana. `id = (((a * B) + b) * C + c)`. Analoginya: indeks array multidimensi diratakan. Decode dengan modulo dan bagi.

**Kapan:** 2–4 dimensi kecil. Jangan encode jika satu dimensi `1e9` (pakai `map` / hash, lebih lambat).

**Proses:** `pos ∈ [0,5)`, `mask ∈ [0,8)`, `nyawa ∈ [0,3)`.

```
nMask = 8, nNyawa = 3
id = (pos * 8 + mask) * 3 + nyawa
|S| = 5 * 8 * 3 = 120
```

Contoh: `(pos=2, mask=5, nyawa=1)` → `(2*8+5)*3+1 = 64`. Balik: `64%3=1`, `21%8=5`, `2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Enc {
    int A, B, C; // ukuran dimensi
    Enc(int A, int B, int C) : A(A), B(B), C(C) {}
    int id(int a, int b, int c) const { return (a * B + b) * C + c; }
    int total() const { return A * B * C; }
    void pecah(int x, int& a, int& b, int& c) const {
        c = x % C;
        x /= C;
        b = x % B;
        a = x / B;
    }
};

int main() {
    FASTIO;
    Enc e(5, 8, 3);
    int x = e.id(2, 5, 1);
    int a, b, c;
    e.pecah(x, a, b, c);
    cout << x << ' ' << a << ' ' << b << ' ' << c << '\n'; // 64 2 5 1
    cout << e.total() << '\n';                             // 120
    return 0;
}
```

**Jebakan:**

1. Urutan kali tertukar saat decode.
2. Overflow `int` jika `A*B*C > 2e9` — pakai cek `1LL*A*B*C`.
3. `queue` menyimpan tuple tanpa `vis[id]` — TLE.

**Kompleksitas:** encode/decode `O(1)`.

---

## Labirin plus kunci

**Teori:** Bit `k` kunci → `2^k` mask. Masuk sel `v` hanya jika `(mask & butuh[v]) == butuh[v]`. Saat menginjak sel, `mask |= kunciDi[v]`. Analoginya: kunci di saku, pintu cek bit.

**Kapan:** `n * 2^k ≤ ~1e7`, `k ≤ 12` kasar bersama `n ≤ 1000`, atau `k ≤ 20` dengan `n` kecil. Jangan `k = 20` dan `n = 1e5`.

**Proses:** `g`: `0-1-2-3`, `kunciDi = [0,1,0,0]`, `butuh = [0,0,0,1]`, `K=1`.

```
id = pos * 2 + mask
start id = 0*2+0 = 0
dari 0 ke 1, mask 0, butuh[1]=0 OK, nmask=1, id=3, dist 1
dari 3 ke 2, nmask=1, id=5, dist 2
dari 5 ke 3, butuh[3]=1 OK, id=7, dist 3
```

Jawaban 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const int INF = 1e9;

int idState(int pos, int mask, int nMask) { return pos * nMask + mask; }

int bfsKunci(int n, const vector<vector<int>>& g,
             const vector<int>& kunciDi, const vector<int>& butuh,
             int start, int goal, int K) {
    int M = 1 << K;
    vector<int> dist(n * M, INF);
    queue<int> q;
    int mask0 = kunciDi[start];
    int s = idState(start, mask0, M);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int pos = cur / M, mask = cur % M;
        if (pos == goal) return dist[cur];
        for (int v : g[pos]) {
            if ((mask & butuh[v]) != butuh[v]) continue;
            int nmask = mask | kunciDi[v];
            int nxt = idState(v, nmask, M);
            if (dist[nxt] > dist[cur] + 1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {{1}, {0, 2}, {1, 3}, {2}};
    vector<int> kunciDi = {0, 1, 0, 0};
    vector<int> butuh = {0, 0, 0, 1};
    cout << bfsKunci(4, g, kunciDi, butuh, 0, 3, 1) << '\n'; // 3
    return 0;
}
```

**Jebakan:**

1. Pintu di sisi, bukan di sel: `butuh` harus pada transisi `(u,v)`, bukan `v` saja.
2. Pickup tidak digabung: state `(1,0)` dan `(1,1)` — boleh, tetapi dist bisa +0 di tempat; samakan model.
3. Goal “posisi saja” vs “posisi + semua kunci” — baca soal.

**Kompleksitas:** `O((n + m) · 2^K)`.

---

## Dua token

**Teori:** Dua pion di papan: state `(posA, posB)` atau `(posA, posB, giliran)`. Jika keduanya simetris dan giliran tidak penting, urutkan id agar `a ≤ b` (hati-hati jika pion dibedakan). Analoginya: dua robot penyedot, tabrakan dilarang.

**Kapan:** papan `n ≤ 200` dua pion → `40000` state. Jangan tiga pion di `n = 100` (`1e6` masih, `n=400` berat).

**Proses:** garis 3 sel, pion A di 0, B di 2, tujuan bertukar tempat, tidak boleh satu sel. Langkah: geser satu pion ±1.

```
start (0,2)
A ke 1 → (1,2)
B ke 1 terlarang (tabrak)
dari (1,2): A tidak ke 2 (tabrak), B diam? jika wajib gerak:
...
target (2,0)
```

Jejak minimum (salah satu model: tiap langkah satu pion):

| dist | state |
|---|---|
| 0 | (0,2) |
| 1 | (1,2) |
| 2 | (1,0) jika B 2→0 tidak langsung; B hanya ±1 jadi (1,2)→ B ke? hanya 2 |
| | model ketat: B dari 2 hanya ke 1, terlarang. Perlu A mundur. |

Garis 3 dengan larangan tabrak **tidak bisa bertukar** tanpa loncat. Jawaban `-1`. Itu tes bagus: kode yang lupa tabrak menjawab 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const int INF = 1e9;

int bfsDuaPion(int n, int a0, int b0, int a1, int b1) {
    auto id = [&](int a, int b) { return a * n + b; };
    vector<int> dist(n * n, INF);
    queue<int> q;
    if (a0 == b0) return -1;
    dist[id(a0, b0)] = 0;
    q.push(id(a0, b0));
    const int dlt[2] = {-1, 1};
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int a = cur / n, b = cur % n;
        if (a == a1 && b == b1) return dist[cur];
        for (int da : dlt) {
            int na = a + da;
            if (na < 0 || na >= n || na == b) continue;
            int nxt = id(na, b);
            if (dist[nxt] > dist[cur] + 1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
        for (int db : dlt) {
            int nb = b + db;
            if (nb < 0 || nb >= n || nb == a) continue;
            int nxt = id(a, nb);
            if (dist[nxt] > dist[cur] + 1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

int main() {
    FASTIO;
    cout << bfsDuaPion(3, 0, 2, 2, 0) << '\n';     // -1
    cout << bfsDuaPion(4, 0, 3, 1, 3) << '\n';     // 1
    return 0;
}
```

**Jebakan:**

1. Mengizinkan `na == b` (tabrak) atau tukar sel di langkah yang sama tanpa model “swap”.
2. Pion identik tetapi state `(1,2)` dan `(2,1)` dihitung beda — dobel, masih benar jika target terurut.
3. Giliran wajib bergantian tetapi state tanpa bit giliran.

**Kompleksitas:** `O(n^2)`.

---

## Operasi pada angka

**Teori:** State = bilangan. Transisi `+1, -1, *2` atau ganti digit. Potong domain: `*2` tanpa batas = TLE/MLE. Analoginya: mesin kalkulator, tiap tombol satu langkah.

**Kapan:** “minimum operasi dari A ke B”, `B` sampai ~1e6. Jangan BFS jika operasi bisa meloncat `1e18` tanpa modulus.

**Proses:** `3 → 11` dengan `+1, -1, *2`. Satu jalur: `3*2=6 +1=7 +1=8 +1=9 +1=10 +1=11` (6 langkah) — buruk. Lebih baik: `3+1=4*2=8 +1=9 +1=10 +1=11` (5). Atau `3*2+1=7` ... hitung BFS.

BFS menjamin minimum. Batas `2*target+5` menampung sedikit overshoot.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const int INF = 1e9;

int minOperasiAngka(int start, int target) {
    if (start == target) return 0;
    int BATAS = max(start, target) * 2 + 5;
    vector<int> dist(BATAS + 1, INF);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) return dist[u];
        int kandidat[3] = {u + 1, u - 1, u * 2};
        for (int v : kandidat) {
            if (v < 0 || v > BATAS) continue;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return -1;
}

int main() {
    FASTIO;
    cout << minOperasiAngka(3, 11) << '\n';
    cout << minOperasiAngka(5, 5) << '\n';         // 0
    return 0;
}
```

**Jebakan:**

1. Batas terlalu kecil: `*2` melewati target lalu `-1` adalah jalur sah.
2. `vis` tidak dipasang saat push: antrean meledak.
3. `start > target` dan hanya `+1, *2` tanpa `-1` → potong model.

**Kompleksitas:** `O(BATAS)`.

---

## 0-1 BFS di state

**Teori:** Transisi ada yang gratis (0) dan ada yang berbayar (1): deque, sama seperti [dfs-bfs.md](dfs-bfs.md). State tetap diratakan. Analoginya: berjalan di lantai biasa vs merobohkan satu tembok (biaya 1, sisa 0).

**Kapan:** “boleh hancurkan ≤ k tembok” lebih naturally **state `(pos, sisa)` + BFS biasa** (biaya 1 seragam). “hancurkan tembok biaya 1, jalan biaya 0” adalah 0-1 BFS pada grid. “portal gratis + langkah mahal” = 0-1.

**Proses:** grid 1×4 `. # . .`, start kolom 0, goal kolom 3. Masuk `'#'` biaya 1, `'.'` biaya 0. (Biaya pada sel tujuan.)

```
id = kolom
0 (.) dist 0
→ 1 (#) dist 1
→ 2 (.) dist 1
→ 3 (.) dist 1
```

Jawaban 1 (satu tembok). Jika `'#'` dilarang, tak tercapai.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

vector<ll> bfs01Grid(const vector<string>& a, pair<int, int> S, char mahal) {
    int R = (int)a.size(), C = (int)a[0].size();
    auto id = [&](int r, int c) { return r * C + c; };
    vector<ll> dist(R * C, INF);
    deque<int> dq;
    dist[id(S.first, S.second)] = 0;
    dq.push_front(id(S.first, S.second));
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        int r = u / C, c = u % C;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (a[nr][nc] == '*') continue; // tembok mutlak
            int w = (a[nr][nc] == mahal);
            int v = id(nr, nc);
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

int bfsHancurK(const vector<string>& a, pair<int, int> S, pair<int, int> T, int K) {
    int R = (int)a.size(), C = (int)a[0].size();
    int P = R * C;
    auto id = [&](int r, int c, int sisa) { return (r * C + c) * (K + 1) + sisa; };
    vector<int> dist(P * (K + 1), -1);
    queue<int> q;
    int s = id(S.first, S.second, K);
    dist[s] = 0;
    q.push(s);
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int sisa = cur % (K + 1);
        int cell = cur / (K + 1);
        int r = cell / C, c = cell % C;
        if (r == T.first && c == T.second) return dist[cur];
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            int ns = sisa;
            if (a[nr][nc] == '#') {
                if (!ns) continue;
                ns--;
            }
            int nxt = id(nr, nc, ns);
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

int main() {
    FASTIO;
    vector<string> a = {".#.."};
    auto d = bfs01Grid(a, {0, 0}, '#');
    cout << d[3] << '\n';                          // 1
    vector<string> b = {".#.#."};
    cout << bfsHancurK(b, {0, 0}, {0, 4}, 1) << '\n'; // 4 jika 1 tembok cukup
    return 0;
}
```

**Jebakan:**

1. Mencampur 0-1 BFS dengan “sisa k tembok”: dua model berbeda. Sisa k = dimensi state + BFS seragam.
2. `push_back` untuk biaya 0.
3. Tembok mutlak `'#'` vs tembok boleh dihancurkan — dua karakter.

**Kompleksitas:** 0-1 `O(RC)`, hancur-k `O(RC · K)`.

---

## Ringkasan

**Teori:** Pilih field state sampai transisi jadi tepi graf. Encode. BFS atau 0-1 BFS. Potong domain.

**Kapan:** kunci, dua pion, tombol kalkulator, hancurkan k tembok. Bobot sebarang → [dijkstra.md](dijkstra.md).

**Proses:** tulis tuple di kertas, hitung `|S|`, baru kode.

**Jebakan lintas:**

1. `vis` kurang dimensi.
2. `|S|` tidak dihitung.
3. `*2` tanpa batas.
4. 0-1 vs state-k tercampur.

**Kompleksitas saku:** `O(|S| + |E_state|)`.

Lanjut: [dijkstra.md](dijkstra.md) · [dfs-bfs.md](dfs-bfs.md) · [euler.md](euler.md)
