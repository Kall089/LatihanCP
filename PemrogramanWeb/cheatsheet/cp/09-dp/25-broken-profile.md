# 25 — Broken profile (Day 166)

[← Game DP](24-game.md) · [README](README.md) · [CHT →](26-cht.md)

> **Satu kalimat:** isi grid `n × m` kolom demi kolom; state = bitmask "lubang" di kolom sekarang.

Day ComprogLearning: **166**. Tiling 1×2 / 2×1 (domino). Bukan knapsack, bukan TSP — meskipun sama-sama bitmask.

Tiga pertanyaan:

```
1. STATE     : dp[col][mask] = banyak cara mengisi kolom 0..col-1 penuh, kolom col berprofil mask
2. TRANSISI  : letakkan vertikal / sepasang horizontal, geser ke sel berikutnya
3. BASIS     : dp[0][0] = 1  (belum ada apa-apa, profil kosong)
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Dua gaya transisi](#dua-gaya-transisi)
- [Proses 2 × 3](#proses-2--3)
- [Proses 3 × 2](#proses-3--2)
- [Sel rusak](#sel-rusak)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Papan `n` baris × `m` kolom, `n` kecil (`≤ 12`), `m` boleh 10^3. Isi penuh dengan domino 1×2 (horizontal) dan 2×1 (vertikal). Hitung banyak cara, atau "bisa/tidak", atau max nilai.

Jika kita mengisi sel demi sel (urutan kolom, dalam kolom dari atas):

- sel sudah tertutup → lewati,
- letakkan vertikal: menutup sel ini dan sel bawah (jika kosong),
- letakkan horizontal: menutup sel ini dan sel **kolom berikutnya** baris yang sama.

Horizontal menonjol ke depan: kolom berikutnya punya "bit sudah terisi" sebelum kita tiba. Itu **profil patah** (broken profile): mask bit = sel di kolom saat ini yang sudah diisi oleh ubin dari kolom sebelumnya.

Analoginya: merajut kiri ke kanan. Jarum di kolom sekarang; beberapa lubang sudah tertutup oleh tusukan dari kiri.

Jumlah sel harus genap (tiap ubin 2 sel), kecuali ada sel rusak.

---

## Kapan

**Kapan dipakai.**

| Gejala | Broken profile |
|---|---|
| tiling domino / tromino kecil | ya |
| `min(n,m) ≤ 12`, `max` sampai 1e3 | ya |
| 2×m atau 3×m rumus tertutup | DP masih OK, rumus lebih cepat |
| pewarnaan grid dengan larangan tetangga | kadang, mask kolom |
| n=m=20 penuh enumerasi | tidak, `2^20` per kolom kali transisi berat |

**Kapan tidak.**

1. `n,m ≥ 16` tanpa struktur — state `2^16` × 16 × transisi DFS sel bisa  TLE.
2. Ubin besar tak beraturan tanpa bound profil.
3. Hanya 2×m domino: ada rumus Fibonacci. Tetap bagus untuk belajar DP.

---

## STATE TRANSISI BASIS

Asumsikan `n ≤ m`, tukar jika perlu agar `n` = tinggi (bit).

**STATE:** `dp[c][mask]` = banyak cara sehingga:

- kolom `0 .. c-1` penuh,
- kolom `c` memiliki sel-sel yang bitnya nyala di `mask` **sudah terisi** (oleh horizontal dari kiri), bit mati = masih kosong.

Kadang orang memakai `dp[c][i][mask]` dengan `i` = baris yang sedang diproses. Itu gaya DFS-transisi.

**TRANSISI (gaya pasangan mask):** precompute semua `(mask, nmask)` kompatibel untuk satu kolom, lalu

```
dp[c+1][nmask] += dp[c][mask]
```

`nmask` = bit yang "didorong" ke kolom kanan oleh horizontal.

**TRANSISI (gaya sel):** fungsi `dfs(c, r, cur, nxt)`:

- jika `r == n`: simpan ke `dp[c+1][nxt]`,
- jika bit `r` sudah 1 di `cur`: skip (`dfs(c, r+1, cur, nxt)`),
- vertikal: `r+1` kosong → `dfs(c, r+2, cur, nxt)`,
- horizontal: nyalakan bit `r` di `nxt` → `dfs(c, r+1, cur, nxt | (1<<r))`.

**BASIS:** `dp[0][0] = 1`. Jawaban `dp[m][0]` (setelah kolom terakhir, tidak boleh ada tonjolan).

---

## Dua gaya transisi

### Gaya A — DFS satu kolom

Lebih mudah ditulis, mudah sel rusak. Waktu: tiap kolom, tiap mask, DFS `O(n)` cabang terbatas. Praktis `O(m 2^n n)` sampai `O(m 2^n 2^{n/2})` tergantung cabang.

### Gaya B — enumerasi transisi

Untuk tiap `mask`, DFS sekali menghasilkan daftar `nmask`. Lalu `m` kali hanya loop daftar. Berguna jika `m` besar dan transisi diulang.

Keduanya benar jika aturan sama.

---

## Proses 2 × 3

`n=2` baris, `m=3` kolom. Jumlah cara domino: **3**.

```
|| || ||     == == ==     || == ==
|| || ||     == == ==     || == ==

tunggu, 2x3:
1) tiga vertikal
2) dua horizontal di kolom 0-1, vertikal kolom 2
3) vertikal kolom 0, dua horizontal kolom 1-2
```

Tidak bisa tiga pasang horizontal di 2×3? Dua horizontal menutup 2 kolom. Ya 3 cara.

Simulasi mask (bit0 atas, bit1 bawah):

```
dp[0][00] = 1

Dari (0, 00):
  VV: kedua sel vertikal... di tinggi 2, satu vertikal menutup 2 baris 1 kolom.
  HH: dua horizontal, nxt = 11
  tidak bisa satu horizontal saja (sisa 1 sel)

hasil:
  dp[1][00] += 1   // VV
  dp[1][11] += 1   // HH

Dari (1, 00): sama
  dp[2][00] += dp[1][00]
  dp[2][11] += dp[1][00]

Dari (1, 11): kedua sel sudah terisi → harus skip semua, nxt=00
  dp[2][00] += dp[1][11]

Dari (2, 00):
  dp[3][00] += ... VV
  dp[3][11] += ... HH  (tonjolan, ilegal di akhir)

Dari (2, 11):
  dp[3][00] += ...
```

`dp[3][00]` = cara VV+VV+VV, HH+skip+VV, VV+HH+skip = 3.

---

## Proses 3 × 2

Tinggi 3, lebar 2. Jumlah sel 6, genap. Cara: **3**? 3×2 = dua kolom.

Sebenarnya 3×2 sama dengan 2×3 diputar: 3 cara.

Mask 3 bit. Vertikal tidak menutup seluruh kolom (tinggi ganjil): satu vertikal = 2 sel, sisa 1 harus horizontal.

```
Kolom penuh vertikal mustahil (3 ganjil).
Harus kombinasi V + H.
```

Uji kode dengan `ways(3,2)==ways(2,3)==3`.

`1×1`: 0. `2×2`: 2 (dua V, atau dua pasang H). `2×1`: 1 (satu V). `3×1`: 0.

---

## Sel rusak

Grid punya sel terlarang. Saat DFS:

- jika sel rusak dan mask bilang "harus diisi" → 0,
- jika sel rusak dan kosong: **lewati** tanpa meletakkan ubin (anggap sudah "tertutup").

Jumlah sel bebas harus genap.

**STATE** sama; cek `blocked[r][c]` saat memproses `(c,r)`.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

int nR, nC;
vector<ll> dpCur, dpNxt;

void dfsCol(int r, int cur, int nxt, ll ways) {
    if (r == nR) {
        dpNxt[nxt] = (dpNxt[nxt] + ways) % MOD;
        return;
    }
    if ((cur >> r) & 1) {
        dfsCol(r + 1, cur, nxt, ways);
        return;
    }
    // vertikal 2x1
    if (r + 1 < nR && !((cur >> (r + 1)) & 1))
        dfsCol(r + 2, cur, nxt, ways);
    // horizontal 1x2 : isi sel kanan pada baris r
    dfsCol(r + 1, cur, nxt | (1 << r), ways);
}

ll tileDomino(int rows, int cols) {
    if (rows > cols) swap(rows, cols);
    nR = rows;
    nC = cols;
    int N = 1 << nR;
    dpCur.assign(N, 0);
    dpCur[0] = 1;
    for (int c = 0; c < nC; c++) {
        dpNxt.assign(N, 0);
        for (int mask = 0; mask < N; mask++)
            if (dpCur[mask]) dfsCol(0, mask, 0, dpCur[mask]);
        dpCur.swap(dpNxt);
    }
    return dpCur[0];
}

ll tileBlocked(const vector<string>& g) {
    int rows = (int)g.size();
    int cols = rows ? (int)g[0].size() : 0;
    nR = rows;
    nC = cols;
    int N = 1 << nR;
    dpCur.assign(N, 0);
    dpCur[0] = 1;
    function<void(int, int, int, int, ll)> dfs = [&](int r, int cur, int nxt, int c, ll ways) {
        if (r == nR) {
            dpNxt[nxt] = (dpNxt[nxt] + ways) % MOD;
            return;
        }
        bool block = g[r][c] == '#';
        if ((cur >> r) & 1) {
            if (block) return;
            dfs(r + 1, cur, nxt, c, ways);
            return;
        }
        if (block) {
            dfs(r + 1, cur, nxt, c, ways);
            return;
        }
        if (r + 1 < nR && !((cur >> (r + 1)) & 1) && g[r + 1][c] != '#')
            dfs(r + 2, cur, nxt, c, ways);
        if (c + 1 < nC && g[r][c + 1] != '#')
            dfs(r + 1, cur, nxt | (1 << r), c, ways);
    };
    for (int c = 0; c < nC; c++) {
        dpNxt.assign(N, 0);
        for (int mask = 0; mask < N; mask++)
            if (dpCur[mask]) dfs(0, mask, 0, c, dpCur[mask]);
        dpCur.swap(dpNxt);
    }
    return dpCur[0];
}

int main() {
    FASTIO;
    cout << tileDomino(2, 3) << "\n"; // 3
    cout << tileDomino(2, 2) << "\n"; // 2
    cout << tileDomino(3, 2) << "\n"; // 3
    cout << tileDomino(1, 1) << "\n"; // 0
    cout << tileDomino(3, 1) << "\n"; // 0
    return 0;
}
```

Precompute transisi:

```cpp
vector<vector<int>> trans;

void buildTrans(int n) {
    nR = n;
    int N = 1 << n;
    trans.assign(N, {});
    function<void(int, int, int)> dfs = [&](int r, int cur, int nxt) {
        if (r == nR) {
            trans[cur].push_back(nxt);
            return;
        }
        if ((cur >> r) & 1) {
            dfs(r + 1, cur, nxt);
            return;
        }
        if (r + 1 < nR && !((cur >> (r + 1)) & 1))
            dfs(r + 2, cur, nxt);
        dfs(r + 1, cur, nxt | (1 << r));
    };
    for (int mask = 0; mask < N; mask++) dfs(0, mask, 0);
}

ll tileFast(int rows, int cols) {
    if (rows > cols) swap(rows, cols);
    buildTrans(rows);
    int N = 1 << rows;
    vector<ll> cur(N), nxt(N);
    cur[0] = 1;
    for (int c = 0; c < cols; c++) {
        fill(nxt.begin(), nxt.end(), 0);
        for (int mask = 0; mask < N; mask++)
            if (cur[mask])
                for (int nm : trans[mask])
                    nxt[nm] = (nxt[nm] + cur[mask]) % MOD;
        cur.swap(nxt);
    }
    return cur[0];
}
```

---

## Jebakan

1. **Tidak menukar `n > 12`.** Tinggi harus sisi pendek.

2. **Jawaban `dp[m][sesuatu]` bukan 0.** Tonjolan horizontal melewati batas. Wajib mask akhir 0.

3. **Dua vertikal overlapping.** Cek bit `r` dan `r+1` kosong.

4. **Horizontal menonjol tapi kolom terakhir.** Gaya DFS masih mengizinkan `nxt` ≠ 0; mereka tidak masuk jawaban jika kita baca `[0]`.

5. **`int` cara.** 2×m Fibonacci, 8×m sudah besar. `ll` / `MOD`.

6. **Sel ganjil.** Langsung 0, atau biarkan DP mengembalikan 0.

7. **Tromino:** tiga sel, transisi tambahan. Jangan memaksa domino.

8. **Urutan baris vs bit.** Konsisten bit0 = baris 0.

9. **`swap(rows,cols)` pada grid rusak.** Tidak boleh flip kalau `#` tidak ikut dirotasi.

10. **Memo `dfs` per sel tanpa `cur`.** Harus membawa profil.

---

## Kompleksitas

```
O(m · 2^n · poly(n))
```

Gaya DFS kasar: tiap mask, pohon keputusan ≤ `O(2^{n/2})` (pasangan). Praktis `n ≤ 11` nyaman, `n = 12` pas.

Memori: dua array `2^n`, atau `m × 2^n` jika tidak rolling.

| n | m | kasar |
|---|---|---|
| 8 | 1000 | sangat aman |
| 11 | 100 | aman |
| 12 | 1000 | hati-hati konstanta |
| 16 | 16 | berbahaya |

---

## Tabel uji

| n m | Cara |
|---|---|
| 1 1 | 0 |
| 1 2 | 1 |
| 2 1 | 1 |
| 2 2 | 2 |
| 2 3 | 3 |
| 3 2 | 3 |
| 3 4 | 11 |
| 4 4 | 36 |

`2 × m` = Fibonacci: `f(0)=1, f(1)=1, f(2)=2, f(3)=3, f(4)=5`. (`f(0)` papan kosong 1 cara.)

---

## Checklist

1. Tinggi = `min(n,m)` kecuali grid rusak berorientasi.
2. `dp[0][0] = 1`, jawab `dp[m][0]`.
3. Vertikal cek dua sel.
4. Horizontal nyalakan bit kolom kanan.
5. MOD / `ll`.
6. Uji 2×3 = 3, 2×2 = 2.
7. Sel `#` jangan di-rotasi diam-diam.

---

## Varian nilai

Setiap sel skor. Max jumlah skor sel yang ditutup? Biasanya semua harus tertutup, skor pada ubin.

`dp` menyimpan max, bukan jumlah cara. Transisi sama, operator `max` + nilai ubin yang baru diletakkan.

Jangan campur `+` cara dan `max` nilai.

---

## Tromino L dan I (ide)

Ubin 3 sel: state sama, cabang lebih banyak (bentuk L menonjol 2 bit ke kanan, atau 1 bit + vertikal). Gambar kertas dulu. Uji 3×2 (bisa 2 I vertikal? I 3×1 menutup satu kolom — 2 cara kolom I; L lebih rumit).

Jika soal hanya domino, **jangan** menambah L.

---

## 2 × m = Fibonacci, kenapa?

Kolom pertama:

- satu vertikal, sisa `2 × (m-1)`,
- atau dua horizontal yang menutup 2 kolom, sisa `2 × (m-2)`.

Tidak ada cara lain tanpa celah. Jadi `a[m] = a[m-1] + a[m-2]`, `a[0]=1`, `a[1]=1`.

Broken profile tetap berguna: pola yang sama jalan untuk `3 × m` (bukan Fibonacci) dan sel rusak.

Tabel `3 × m` (cara):

| m | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| cara | 1 | 0 | 3 | 0 | 11 |

`m` ganjil: jumlah sel `3m` ganjil → 0.

---

## Rekonstruksi satu tiling

Simpan `parent[c+1][nmask] = mask` saat transisi pertama yang mencapai. Mundur dari `(m, 0)`. Dari pasangan `(mask, nmask)` jalankan DFS yang sama untuk mengetahui V/H di kolom itu.

Untuk soal "berapa cara", jejak tidak perlu. Untuk "cetak satu papan", perlu.

---

## Urutan sel alternatif

Beberapa orang mengisi **baris demi baris** (lebar `m` kecil). Sama persis, tukar nama. Yang penting: sisi pendek = lebar mask.

Jangan mengisi diagonal — profil jadi dua sisi, state `2^{2n}`.

---

## Proses 2 × 2 pelan-pelan

Mask 2 bit. `dp[0][00]=1`.

```
Kolom 0, mask 00:
  V: r=0+2 selesai, nxt=00     → dp[1][00] += 1
  H atas: nxt bit0, r=1 masih kosong
    H bawah: nxt bit0|bit1=11  → dp[1][11] += 1
    V dari r=1? hanya 1 sel, tidak
Kolom 1, mask 00: sama → dp[2][00] += 1 (VV), dp[2][11]+=1 (HH, tonjol)
Kolom 1, mask 11: skip skip, nxt=00 → dp[2][00] += 1
Jawaban dp[2][00] = 2
```

Dua cara: VV dan HH (dua pasang horizontal).

---

## Kenapa tidak "dua horizontal hanya atas"?

Sisa sel bawah kolom 0 kosong. DFS memaksa mengisi sebelum pindah kolom. Satu H atas tanpa H bawah tidak mencapai `r==n` dengan sel legal — cabang V di `r=1` gagal jika tinggi 2 dan sel atas sudah... wait: setelah H atas, `r=1` kosong, bisa V? V butuh `r` dan `r+1`, `r+1=2==n` gagal. H bawah wajib. Profil menjaga tidak ada lubang.

---

## Cek paritas cepat

`n * m` ganjil → 0 cara (domino). Tulis di awal `main` sebelum DP. Grid rusak: hitung sel `.` ganjil → 0.

---

## Ringkasan dinding

```
n = tinggi ≤ 12
dp[col][mask]
isi sel atas→bawah:
  sudah terisi → skip
  V → r+2
  H → nyalakan bit kanan
akhir: mask 0
2×3 → 3 ; 2×m Fibonacci
```
