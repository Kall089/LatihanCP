# 24 — Game DP pada DAG (Day 165)

[← Bitset](23-bitset.md) · [README](README.md) · [Broken profile →](25-broken-profile.md)

> **Satu kalimat:** posisi menang jika ada langkah ke posisi kalah; seri jika tidak ada paksaan menang dan ada siklus/jalan ke seri.

Day ComprogLearning: **165**. Grundy / Nim lengkap ada di [folder 14](../14-game-theory/README.md) ([nim-grundy](../14-game-theory/nim-grundy.md)). File ini: DP win/lose/draw pada graf state.

Tiga pertanyaan:

```
1. STATE     : win[s] / hasil[s] untuk pemain yang bergerak dari s
2. TRANSISI  : OR (lawan kalah) ; draw jika ada siklus belum selesai
3. BASIS     : terminal tanpa langkah = kalah (normal play)
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [Win / lose pada DAG](#win--lose-pada-dag)
- [Proses Nim 1 tumpukan](#proses-nim-1-tumpukan)
- [Draw pada graf bersiklus](#draw-pada-graf-bersiklus)
- [Grundy: sebutan + tautan](#grundy-sebutan--tautan)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Permainan 2 orang, giliran bergantian, informasi sempurna, tanpa undian acak (itu [22](22-probabilitas.md)). State membentuk graf berarah: sisi = langkah legal.

**Normal play:** yang tidak bisa gerak kalah. (Misère: yang terakhir kalah — jauh lebih sulit, jangan campur.)

Pada **DAG** (tidak ada siklus, permainan pasti selesai):

```
lose(s)  jika semua langkah ke win, atau tidak ada langkah
win(s)   jika ada langkah ke lose
```

Itu DP: isi dari terminal (outdegree 0) mundur, atau memo + rekursi karena DAG menjamin basis.

Analoginya: posisi aman jika kamu bisa mendorong lawan ke jurang; jurang = tidak ada langkah.

Kalau graf **punya siklus**, permainan bisa tak hingga. Muncul hasil ketiga: **draw**. Aturan: pemain menang jika bisa **memaksa** menang; jika kedua pemain bisa menahan, seri.

---

## Kapan

**Kapan dipakai.**

| Soal | Alat |
|---|---|
| grid / token / string, langkah memperkecil sesuatu | win/lose DAG |
| beberapa tumpukan independen | Grundy, folder 14 |
| ada ulang posisi | win/lose/draw |
| skor maksimal (bukan hanya menang) | minimax DP |

**Kapan tidak.**

1. Hidden info / kartu acak — bukan file ini.
2. `n` tumpukan Nim klasik — rumus XOR, bukan DP 2^n.
3. Misère Nim — aturan khusus, folder 14.

---

## Win / lose pada DAG

**STATE:** `win[s] = true` jika pemain yang **akan bergerak** dari `s` menang jika keduanya optimal.

**TRANSISI:** `win[s] = OR atas t langkah (not win[t])`.

**BASIS:** tidak ada langkah → `win[s] = false`.

Ekuivalen: `lose` jika `AND` lawan menang.

Top-down: memo. Bottom-up: urutan topo terbalik (sink dulu).

---

## Proses Nim 1 tumpukan

Ambil 1 atau 2 dari tumpukan `n`. Yang menghadapi 0 kalah.

```
win[0] = 0
win[1] = not win[0] = 1
win[2] = not win[0] atau not win[1] = 1
win[3] = not win[2] and not win[1] = 0
win[4] = 1
```

Pola: `win[i] = (i % 3 != 0)`.

Catur-caturan: 3,6,9,... losing.

Brute n=10: 0 L, 1 W, 2 W, 3 L, 4 W, 5 W, 6 L.

---

## Draw pada graf bersiklus

Tiga nilai: `WIN = 1`, `LOSE = -1`, `DRAW = 0` (atau enum).

Ide retrograde:

1. State tanpa langkah = LOSE.
2. Queue: setiap kali sebuah state **sudah pasti** WIN atau LOSE, perbarui ayah (state yang bisa ke sana).
3. Hitung `deg[s]` = banyak langkah masih "belum tentu".
4. Jika ada langkah ke LOSE → `s` = WIN (bisa memaksa).
5. Jika semua langkah ke WIN (`deg` habis tanpa pernah ke LOSE) → `s` = LOSE.
6. Yang tidak pernah terisi = DRAW (terjebak di siklus atau ke draw).

Ini mirip Kahn / topo, tapi tiga warna.

**Proses: dua state A↔B**, tidak ada terminal.

```
deg[A]=1, deg[B]=1
tidak ada LOSE awal
keduanya DRAW
```

Masuk akal: bisa muter selamanya.

**Proses: A → B, B terminal.**

```
B LOSE
A punya langkah ke LOSE → WIN
```

**Proses: A → B, B → B (loop), plus B tidak...** hati-hati loop self.

---

## Grundy: sebutan + tautan

Jika permainan = **jumlah** (XOR) beberapa komponen independen (beberapa tumpukan, beberapa papan), win/lose satu komponen tidak cukup. Perlu **Grundy / nimber**.

```
grundy[s] = mex { grundy[t] | s → t }
mex = bilangan non-negatif terkecil yang tidak muncul
```

Komponen gabungan menang iff XOR semua grundy ≠ 0.

Itu **bukan** fokus file ini. Baca:

- [14-game-theory/README](../14-game-theory/README.md)
- [nim-grundy.md](../14-game-theory/nim-grundy.md)

Di sini cukup: `mex` kode, dan ingat "kalau ada beberapa tumpukan, jangan hanya `win[]`".

**Proses satu tumpukan ambil 1/2:**

```
g[0]=mex{}=0
g[1]=mex{0}=1
g[2]=mex{0,1}=2
g[3]=mex{1,2}=0
```

`g[i]=i%3`. Dua tumpukan `(3,1)`: `0 xor 1 = 1 ≠ 0` menang. Win/lose terpisah: tumpukan 3 losing, 1 winning — **tidak** boleh "OR". Harus XOR.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool winNim12(int n) {
    vector<char> win(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (i >= 1 && !win[i - 1]) win[i] = 1;
        if (i >= 2 && !win[i - 2]) win[i] = 1;
    }
    return win[n];
}

int mex(const vector<int>& s) {
    vector<char> seen(s.size() + 2, 0);
    for (int x : s)
        if (0 <= x && x < (int)seen.size()) seen[x] = 1;
    int m = 0;
    while (seen[m]) m++;
    return m;
}

vector<int> grundyNim12(int n) {
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> nxt;
        if (i >= 1) nxt.push_back(g[i - 1]);
        if (i >= 2) nxt.push_back(g[i - 2]);
        g[i] = mex(nxt);
    }
    return g;
}

// graf berarah: adj[s] = daftar t
vector<int> winLoseDAG(const vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<int> indeg(n, 0);
    vector<vector<int>> rev(n);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) {
            rev[v].push_back(u);
            indeg[v]++; // tidak dipakai Kahn biasa
        }
    vector<int> win(n, -1); // -1 belum, 0 lose, 1 win
    function<int(int)> dfs = [&](int u) {
        if (win[u] != -1) return win[u];
        win[u] = 0;
        for (int v : adj[u])
            if (!dfs(v)) win[u] = 1;
        return win[u];
    };
    for (int i = 0; i < n; i++) dfs(i);
    return win;
}

enum Res { DRAW = 0, WIN = 1, LOSE = 2 };

vector<int> winLoseDraw(const vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<int> deg(n);
    vector<vector<int>> rev(n);
    for (int u = 0; u < n; u++) {
        deg[u] = (int)adj[u].size();
        for (int v : adj[u]) rev[v].push_back(u);
    }
    vector<int> res(n, DRAW);
    queue<int> q;
    for (int u = 0; u < n; u++)
        if (deg[u] == 0) {
            res[u] = LOSE;
            q.push(u);
        }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : rev[v]) {
            if (res[u] != DRAW) continue;
            if (res[v] == LOSE) {
                res[u] = WIN;
                q.push(u);
            } else if (res[v] == WIN) {
                deg[u]--;
                if (deg[u] == 0) {
                    res[u] = LOSE;
                    q.push(u);
                }
            }
        }
    }
    return res;
}

int main() {
    FASTIO;
    for (int i = 0; i <= 6; i++)
        cout << winNim12(i) << " ";
    cout << "\n"; // 0 1 1 0 1 1 0
    auto g = grundyNim12(6);
    for (int x : g) cout << x << " ";
    cout << "\n"; // 0 1 2 0 1 2 0

    vector<vector<int>> cyc(2);
    cyc[0].push_back(1);
    cyc[1].push_back(0);
    auto r = winLoseDraw(cyc);
    cout << r[0] << " " << r[1] << "\n"; // 0 0 DRAW
    return 0;
}
```

Minimax skor (bukan hanya W/L), DAG, pemain max mulai:

```cpp
const ll NEG = LLONG_MIN / 4;

ll dfsScore(int u, const vector<vector<int>>& adj, const vector<ll>& leaf,
            vector<ll>& memo, vector<char>& vis, bool maxing) {
    if (adj[u].empty()) return leaf[u];
    if (vis[u]) return memo[u];
    vis[u] = 1;
    ll best = maxing ? NEG : -NEG;
    for (int v : adj[u]) {
        ll s = dfsScore(v, adj, leaf, memo, vis, !maxing);
        best = maxing ? max(best, s) : min(best, s);
    }
    return memo[u] = best;
}
```

Hanya sah di DAG. Siklus butuh depth-limit atau deteksi draw.

---

## Jebakan

1. **Misère vs normal.** "Yang mengambil terakhir kalah" membalik terminal. Jangan pakai template normal.

2. **Beberapa tumpukan + hanya `win[]`.** Harus Grundy / XOR. Tautan folder 14.

3. **Memo win/lose pada siklus** tanpa 3-warna. Recursion tak hingga atau salah WIN.

4. **`win[s] = OR win[t]`.** Salah. Harus `OR not win[t]` (ingin mendorong ke losing lawan).

5. **Pemain yang sama dihitung dua kali.** State harus "siapa yang gerak" jika papan tidak simetris; sering giliran tersirat di definisi `win[s]`.

6. **Terminal draw.** Beberapa soal: pat / ulang = seri, bukan lose. Baca.

7. **Overflow langkah.** Grid besar, state = posisi kedua token: `n^2`.

8. **Grundy `mex` tanpa 0.** `seen` harus cukup panjang `derajat+1`.

9. **Mengisi `win` dari 0 ke n tanpa cek dependensi.** Untuk Nim 1D aman (i bergantung i-1). Untuk graf umum, DFS/topo.

10. **Draw: `deg` tidak berkurang hanya pada langkah ke WIN.** Langkah ke DRAW tidak membuat LOSE.

---

## Kompleksitas

`O(|V| + |E|)` untuk win/lose DAG dan win/lose/draw.

Grundy satu komponen: sama, kali biaya `mex` (derajat).

`n` tumpukan ukuran `a_i`, satu tumpukan DP `O(max A)`, lalu XOR. Jangan `O(Π a_i)` kecuali terpaksa.

---

## Tabel uji

| Permainan | State | Hasil |
|---|---|---|
| ambil 1/2 | n=0..6 | L W W L W W L |
| grundy 1/2 | 0..6 | 0 1 2 0 1 2 0 |
| dua tumpukan (3,1) | XOR | 1 ≠ 0 menang |
| A↔B | draw | DRAW DRAW |
| A→B terminal | | A WIN, B LOSE |
| satu simpul tanpa sisi | | LOSE |

---

## Checklist

1. Normal atau misère?
2. Satu komponen atau jumlah permainan?
3. Ada siklus → 3 nilai, bukan memo 2 nilai.
4. `win = ada langkah ke lose`.
5. Uji n=0 kalah.
6. Beberapa tumpukan → [14-game-theory](../14-game-theory/README.md).

---

## Contoh grid: token mundur

Satu token di sel `i`, boleh pindah ke `i-1` atau `i-2` jika ada batu. Itu isomorf Nim 1/2.

Dua token tidak bisa satu sel: state `(i,j)`, `i < j`. Langkah: gerakkan satu token tanpa lewat. DAG karena jumlah posisi turun. `win[i][j]`.

`n ≤ 400` → `O(n^2)` state.

Jangan XOR dua token jika mereka **berinteraksi** (blokir). Interaksi = **satu** permainan, bukan jumlah. Grundy terpisah hanya jika langkah di satu tumpukan tidak mengubah yang lain.

---

## Hubungan folder 14

| Topik | Di mana |
|---|---|
| win/lose satu graf | **file ini** |
| draw | **file ini** |
| Nim XOR, Sprague-Grundy | [14](../14-game-theory/nim-grundy.md) |
| mex | disebutkan di sini, detail di 14 |
| game + probabilitas | [22](22-probabilitas.md) — lawan acak, bukan optimal |

---

## Proses retrograde 4 state

```
0 → 1 → 2
↑         ↓
3 ← ← ← ← 2   (2→3, 3→0)   plus 2 terminal? tidak

Sederhanakan:
S0 tanpa sisi          → LOSE
S1 hanya ke S0         → WIN
S2 ke S1 dan ke S2     → self-loop + ke WIN
S3 ke S2
```

Hitung:

1. `S0` deg 0 → LOSE, antre.
2. `S1` melihat LOSE → WIN, antre.
3. `S2` melihat WIN: `deg` 2 menjadi 1 (sisi ke S1). Sisi ke diri: kalau self-loop dihitung, `deg` masih ≥ 1. Tidak pernah 0, tidak pernah lihat LOSE → **DRAW**.
4. `S3` hanya ke DRAW → tetap DRAW (tidak bisa memaksa).

Kalau `S2` hanya ke `S1` (tanpa loop): `deg` habis → LOSE? Tidak: ia punya sisi ke WIN saja, `deg` habis tanpa sisi ke LOSE → LOSE. Lalu `S3` ke LOSE → WIN.

Gambar ini wajib sebelum mengetik queue.

---

## Mini-max vs win/lose

Kalau setiap terminal punya skor, dan pemain max/min bergantian, `win[]` tidak cukup. Pakai `dfsScore`. Optimal play = nilai unik di DAG.

Hubungan: jika skor terminal hanya `{+1,-1}` dan tidak ada seri, tanda skor = win/lose.

---

## Kode: subtract a square (satu tumpukan)

Dari `n`, kurangi kuadrat `1,4,9,...`. Klasik: beberapa `n` losing.

```cpp
vector<char> winSquare(int n) {
    vector<char> win(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k * k <= i; k++)
            if (!win[i - k * k]) {
                win[i] = 1;
                break;
            }
    }
    return win;
}
```

`win[0]=0`, `win[1]=1`, `win[2]=0` (hanya ke 1), `win[3]=1` (ke 2). Pola tidak periodik pendek seperti 1/2 — itu alasan DP, bukan rumus `% 3`.

---

## Impasse: langkah ilegal

Soal "tidak boleh ke posisi yang sudah dikunjungi" menambah mask ke state. `n` sel kecil → bitmask + posisi, itu [15](15-bitmask-tsp.md) + win/lose. Jangan memaksa graf tak hingga.

---

## Siapa mulai?

`win[start]` adalah untuk pemain **pertama**. Jika soal "second player win", jawab `!win[start]` pada DAG tanpa draw. Dengan draw, second menang hanya jika `res[start]==LOSE`; `DRAW` bukan kemenangan second.

---

## Topo vs DFS memo

DAG murni: DFS memo `win[u]` aman (setelah anak). Graf mungkin siklus: DFS memo 2-nilai **dilarang**. Pakai `winLoseDraw`.

Deteksi: jika input "boleh mundur", anggap ada siklus sampai terbukti DAG (nilai berkurang ketat).

Contoh DAG: `n` batu, ambil 1..k, `n` turun. Contoh bukan DAG: dua token saling injak di papan yang boleh maju-mundur tanpa cap.

---

## Output tiga bahasa

Beberapa judge: `Win` / `Lose` / `Loop`. Petakan `WIN/LOSE/DRAW`. Jangan cetak `0/1` tanpa baca format.

Untuk first player di start `s`:

```
if (res[s]==WIN) ...
else if (res[s]==LOSE) ...
else ...
```

---

## Satu langkah ke diri sendiri

Self-loop = selalu bisa "tunggu". Tanpa terminal lain, DRAW. Jika ada juga sisi ke LOSE, WIN (paksa sekarang, jangan muter).

Jangan menghapus self-loop diam-diam saat membangun `adj`.

---

## Ringkasan dinding

```
terminal: LOSE (normal)
WIN  = ada sisi ke LOSE
LOSE = semua sisi ke WIN (atau tidak ada sisi)
DRAW = sisanya (siklus)
banyak tumpukan: grundy XOR → folder 14
```
