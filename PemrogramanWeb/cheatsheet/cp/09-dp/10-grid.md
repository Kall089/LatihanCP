# 10 — Grid DP: jalur, halangan, jumlah, 3 arah

[← 09-lcs-edit](09-lcs-edit.md) · [README](README.md) · [11-range →](11-range.md)

Day **150**. Grid kanan-bawah adalah DAG. Monovariant `i+j` selalu naik, jadi **tidak ada siklus**. Urutan topologis gratis: baris demi baris, kiri ke kanan. Huruf pada LCS diganti sel; operator `+` (hitung jalur) atau `min` (biaya).

> **Satu kalimat:** `dp[i][j]` adalah jawaban untuk sampai di sel `(i,j)`; tetangga sah hanya yang sudah selesai (atas, kiri, kadang diagonal atau tiga arah jatuh).

Empat arah bebas (atas/kiri/kanan/bawah) tanpa hambatan arah **bukan** grid DP klasik: bisa siklus, pakai BFS/Dijkstra.

## Daftar isi

- [Kerangka grid DAG](#kerangka-grid-dag)
- [Unique paths](#unique-paths)
- [Halangan](#halangan)
- [Min path sum](#min-path-sum)
- [Tiga arah](#tiga-arah)
- [Sentinel menurut operator](#sentinel-menurut-operator)
- [Kombinatorial tanpa batu](#kombinatorial-tanpa-batu)
- [Dua jalur ide](#dua-jalur-ide)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Kerangka grid DAG

**Teori:** Setiap sel adalah simpul. Sisi menuju tetangga yang diizinkan soal. Jika setiap sisi menaikkan `i`, `j`, atau `i+j`, graf berarah aciklik. DP = relaksasi menurut urutan itu. Analoginya air mengalir ke hilir: kamu tidak perlu cek "sudah dikunjungi" seperti DFS di graf umum.

Dua gaya isi:

| gaya | urutan | rumus |
|---|---|---|
| pull | untuk tiap sel, tarik tetangga yang menunjuk ke sini | `dp[i][j] = gabung(tetangga) ⋆ a[i][j]` |
| push | dari sel, dorong ke tetangga keluar | `dp[nxt] = gabung(dp[nxt], dp[cur] ⋆ …)` |

Pull lebih sering: loop `i`, `j` menaik sudah benar.

**Kapan:** hanya gerak yang tidak bisa kembali (kanan+bawah, atau jatuh ke baris berikutnya). **Tidak:** empat arah, atau sisi menaik dan menurun — itu graf, bukan "isi baris".

**STATE:** `dp[i][j]` adalah banyak cara / biaya optimal / nilai maksimum untuk mencapai sel `(i,j)` dari awal, dengan aturan gerak soal.

**TRANSISI:** gabungkan tetangga masuk dengan operator soal (`+`, `min`, `max`), lalu terapkan isi sel (tambah biaya, atau nolkan jika batu).

**BASIS:** sel awal = 1 (hitung) atau `a[0][0]` (jumlah). Sel di luar grid = identitas operator (0 untuk `+`, `+INF` untuk `min`).

**Proses (table):** grid 2×3, hanya kanan dan bawah, hitung jalur.

| langkah | sel | dari | nilai |
|---|---|---|---|
| 1 | (0,0) | basis | 1 |
| 2 | (0,1) | kiri | 1 |
| 3 | (0,2) | kiri | 1 |
| 4 | (1,0) | atas | 1 |
| 5 | (1,1) | atas+kiri | 2 |
| 6 | (1,2) | atas+kiri | 3 |

Ada 3 jalur: KKB, KBK, BKK.

**Kode modular:** kerangka pull kosong — isi operator di fungsi khusus.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool dalam(int i, int j, int R, int C) {
    return i >= 0 && j >= 0 && i < R && j < C;
}

int main() {
    FASTIO;
    cout << dalam(1, 2, 2, 3) << '\n';
    return 0;
}
```

**Jebakan:** mengisi `dp[0][0]` di dalam loop dari `0+0`. Padding 1-indexed menolong, tetapi `continue` pada sel awal wajib jika loop menyentuhnya.

**Kompleksitas:** `O(RC)` state, transisi O(1) atau O(arah).

---

## Unique paths

**Teori:** Robot di `(0,0)` ingin `(R-1, C-1)`, hanya kanan atau bawah. Banyak jalur = jumlah jalur ke atas plus ke kiri. Tanpa batu, ini koefisien binomial: harus ada tepat `(R-1)` bawah dan `(C-1)` kanan, urutan bebas, jadi `C(R+C-2, R-1)`.

**Kapan:** "unique paths", CSES Grid Paths tanpa batu, AtCoder DP-H tanpa `#`. **Tidak:** boleh mundur. `R,C ≤ 1e6` tanpa batu — jangan DP `O(RC)`, pakai binomial.

**STATE:** `dp[i][j]` adalah banyak jalur dari `(0,0)` ke `(i,j)`.

**TRANSISI:** `dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD`, tetangga di luar = 0.

**BASIS:** `dp[0][0] = 1`. Baris pertama semua 1 (hanya dari kiri). Kolom pertama semua 1 (hanya dari atas).

**Proses (table):** 3×3, 0-indexed tampilan nilai.

|  | c0 | c1 | c2 |
|---|---|---|---|
| r0 | 1 | 1 | 1 |
| r1 | 1 | 2 | 3 |
| r2 | 1 | 3 | **6** |

Enam jalur. Sama dengan `C(4,2) = 6`.

Grid 2×3:

|  | c0 | c1 | c2 |
|---|---|---|---|
| r0 | 1 | 1 | 1 |
| r1 | 1 | 2 | **3** |

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

ll uniquePaths(int R, int C) {
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = 1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll atas = (i > 0 ? dp[i - 1][j] : 0);
            ll kiri = (j > 0 ? dp[i][j - 1] : 0);
            dp[i][j] = (atas + kiri) % MOD;
        }
    }
    return dp[R - 1][C - 1];
}

ll uniquePathsPad(int R, int C) {
    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    return dp[R][C];
}

int main() {
    FASTIO;
    cout << uniquePaths(3, 3) << ' ' << uniquePathsPad(2, 3) << '\n';
    return 0;
}
```

**Jebakan:**

1. `dp[0][0]` ditimpa `0+0`.
2. `R` atau `C` = 1: hanya satu jalur, jangan bagi nol di binomial.
3. Lupa modulo: `C(1998, 999)` ratusan digit.
4. Mencampur 0-index loop dengan array berukuran `R+1` tanpa disiplin.

**Kompleksitas:** `O(RC)` waktu dan memori. Satu baris: `O(C)` (file [13-memori](13-memori.md)).

---

## Halangan

**Teori:** Batu (`#`, 1, atau sel terlarang) memutus aliran. Identitas operator `+` adalah 0, jadi sel batu **diisi 0** lalu dilewati. Analoginya bendungan: air tidak lewat, hilir hanya menerima dari saluran lain.

Awal atau akhir batu → 0 jalur, selesai cepat. `continue` tanpa menolkan berbahaya: nilai sampah atau sisa inisialisasi bisa bocor.

**Kapan:** CSES Grid Paths, AtCoder DP-H, LC Unique Paths II. **Tidak:** batu bisa dipindah / dihancurkan dengan biaya — itu state tambahan.

**STATE:** `dp[i][j]` banyak jalur ke `(i,j)`; 0 jika terhalang atau tidak terjangkau.

**TRANSISI:** jika `g[i][j]` batu maka `dp = 0`; else jumlah tetangga seperti unique paths.

**BASIS:** `dp[0][0] = 1` jika `g[0][0]` kosong, else 0.

**Proses (table):** 3×3, batu di tengah.

Peta:

```
. . .
. # .
. . .
```

|  | c0 | c1 | c2 |
|---|---|---|---|
| r0 | 1 | 1 | 1 |
| r1 | 1 | 0 | 1 |
| r2 | 1 | 1 | **2** |

Dua jalur: pinggir kiri lalu bawah-kanan-kanan, atau kanan-kanan-bawah-kiri-kanan? Jalur kanan-bawah terhalang di tengah. Yang hidup: kanan-kanan-bawah-bawah, dan bawah-bawah-kanan-kanan. (Lewat tepi.)

Awal batu:

|  | |
|---|---|
| `# .` | seluruh grid 0 |

Batu di `(0,1)` pada 2×3:

```
. # .
. . .
```

|  | c0 | c1 | c2 |
|---|---|---|---|
| r0 | 1 | 0 | 0 |
| r1 | 1 | 1 | **1** |

Kolom 2 baris 0 tidak terjangkau (hanya bisa dari kiri yang mati). Satu jalur: bawah, kanan, kanan.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

ll uniquePathsObstacles(const vector<string>& g) {
    int R = (int)g.size(), C = (int)g[0].size();
    if (g[0][0] == '#' || g[R - 1][C - 1] == '#') return 0;
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = 1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') {
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0) continue;
            ll atas = (i > 0 ? dp[i - 1][j] : 0);
            ll kiri = (j > 0 ? dp[i][j - 1] : 0);
            dp[i][j] = (atas + kiri) % MOD;
        }
    }
    return dp[R - 1][C - 1];
}

ll uniquePathsRolling(const vector<string>& g) {
    int R = (int)g.size(), C = (int)g[0].size();
    if (g[0][0] == '#') return 0;
    vector<ll> dp(C, 0);
    dp[0] = 1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') {
                dp[j] = 0;
                continue;
            }
            if (j > 0) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }
    return dp[C - 1];
}

int main() {
    FASTIO;
    vector<string> g = {"...", ".#.", "..."};
    cout << uniquePathsObstacles(g) << ' ' << uniquePathsRolling(g) << '\n';
    return 0;
}
```

**Jebakan:**

1. `continue` pada `#` tanpa `dp = 0` (sisa 1 dari inisialisasi salah).
2. Tidak cek start/finish `#`.
3. Rolling: `dp[j]` adalah atas; jika `#` tidak di-nol, baris berikutnya minum sampah.
4. Grid 1×1 `"."` → 1; `"#"` → 0.

**Kompleksitas:** `O(RC)`.

---

## Min path sum

**Teori:** Operator `+` (hitung) diganti `min` (biaya). Setiap sel punya angka `a[i][j]` yang **harus** dibayar saat dilalui. Jalur minimum dari kiri-atas ke kanan-bawah, hanya kanan/bawah.

Sentinel **bukan 0**. Nol adalah biaya gratis, jadi "tidak ada tetangga" yang diisi 0 akan membuat tepi palsu termurah. Pakai `INF`. Jangan `INF + a[i][j]` tanpa cek: overflow menular, `INF` rusak, seluruh hilir salah.

**Kapan:** LC 64, grid cost, AtCoder varian jumlah. **Tidak:** bobot sisi (bukan sel) dengan 4 arah — Dijkstra. Bobot negatif dengan siklus — bukan DAG.

**STATE:** `dp[i][j]` adalah jumlah minimum jalur dari `(0,0)` ke `(i,j)`.

**TRANSISI:** `dp[i][j] = a[i][j] + min(dp[atas], dp[kiri])` untuk tetangga yang ada.

**BASIS:** `dp[0][0] = a[0][0]`.

**Proses (table):**

Grid:

| 1 | 3 | 1 |
| 1 | 5 | 1 |
| 4 | 2 | 1 |

`dp`:

| 1 | 4 | 5 |
| 2 | 7 | 6 |
| 6 | 8 | **7** |

Jalur `1-3-1-1-1` jumlah 7. Alternatif `1-1-4-2-1` = 9, lebih mahal.

Grid 2×3:

| 1 | 2 | 3 |
| 4 | 5 | 6 |

`dp`:

| 1 | 3 | 6 |
| 5 | 8 | **12** |

Jalur `1-2-3-6 = 12`, `1-4-5-6 = 16`. Min 12.

Dengan batu di (1,1) pada contoh 3×3, `dp[1][1] = INF`, `dp[1][2] = 5+1 = 6` dari atas, `dp[2][1]` dari kiri 6+2=8.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll minPathSum(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            if (best < INF) dp[i][j] = a[i][j] + best;
        }
    }
    return dp[R - 1][C - 1];
}

ll minPathObstacle(const vector<vector<ll>>& a, const vector<string>& g) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    if (g[0][0] == '#') return -1;
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') {
                dp[i][j] = INF;
                continue;
            }
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            dp[i][j] = (best >= INF ? INF : a[i][j] + best);
        }
    }
    return dp[R - 1][C - 1] >= INF ? -1 : dp[R - 1][C - 1];
}

int main() {
    FASTIO;
    vector<vector<ll>> a = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSum(a) << '\n'; // 7
    return 0;
}
```

**Jebakan:** sentinel 0 untuk `min`. `INF + a` menular (`LLONG_MAX + 5` jadi negatif). Trace jalur setelah rolling (tabel hilang). `while (i && j)` saat rekonstruksi — tepi tidak selesai.

**Kompleksitas:** `O(RC)` waktu, `O(RC)` atau `O(C)` memori.

---

## Tiga arah

Dua varian yang sering disebut "3 directions". Jangan campur rumusnya.

### Varian A — jatuh (falling path)

**Teori:** Dari baris `i` kamu hanya ke baris `i+1`, kolom `j-1`, `j`, atau `j+1`. Analoginya bola jatuh di papan paku: tiap tingkat pilih kiri, lurus, atau kanan. DAG-nya per baris: isi dari atas ke bawah. Ini **bukan** kanan+bawah.

**Kapan:** LC Falling Path Sum, "minimum falling path", triangle kadang mirip (2 arah). **Tidak:** masih boleh kanan di baris yang sama — itu varian B atau 2 arah klasik.

**STATE:** `dp[i][j]` biaya minimum jalur yang **berakhir** di `(i,j)` mulai dari baris 0.

**TRANSISI:**

```
dp[i][j] = a[i][j] + min(
    j>0     ? dp[i-1][j-1] : INF,   // dari atas-kiri
              dp[i-1][j],           // dari atas
    j+1<C   ? dp[i-1][j+1] : INF    // dari atas-kanan
)
```

**BASIS:** `dp[0][j] = a[0][j]` untuk semua kolom (boleh mulai di mana saja di baris atas).

**Proses (table):**

Grid:

```
2 1 3
6 5 4
7 8 9
```

Baris 0: `2 1 3`.

Baris 1:

| sel | kandidat atas | +isi | dp |
|---|---|---|---|
| (1,0)=6 | 2, 1 | min 1 | 7 |
| (1,1)=5 | 2, 1, 3 | min 1 | 6 |
| (1,2)=4 | 1, 3 | min 1 | 5 |

Baris 2:

| sel | kandidat | dp |
|---|---|---|
| (2,0)=7 | 7, 6 | 13 |
| (2,1)=8 | 7, 6, 5 | 13 |
| (2,2)=9 | 6, 5 | 14 |

Jawaban `min` baris terakhir = 13. Satu jalur: `1-5-7` atau `1-4-8`.

Triangle `[[2],[3,4],[6,5,7]]` (hanya 2 anak) adalah kasus jatuh yang kolomnya menyempit — rumus sama, tetangga kanan kadang tidak ada.

### Varian B — kanan, bawah, diagonal

**Teori:** Selain kanan dan bawah, boleh selangkah diagonal kanan-bawah. Untuk **hitung jalur**, diagonal menambah cara. Untuk **min sum**, diagonal adalah pintasan yang tetap membayar sel tujuan (bukan dua sel).

**Kapan:** soal eksplisit "boleh ke (i+1,j+1)". **Tidak:** mengasumsikan diagonal gratis tanpa membaca statement.

**STATE hitung:** `dp[i][j]` banyak jalur ke `(i,j)` dengan 3 gerak.

**TRANSISI hitung:** `dp[i][j] = atas + kiri + diagonal_atas_kiri`.

**BASIS:** `dp[0][0] = 1`.

**Proses (table) hitung 2×2:**

| 1 | 1 |
| 1 | 3 |

Ke `(1,1)`: dari kiri (1), dari atas (1), dari diagonal (1) → 3 jalur: kanan-bawah, bawah-kanan, diagonal.

**Proses (table) min 3×3** angka `[[1,3,1],[1,5,1],[4,2,1]]` dengan 3 masuk (atas, kiri, diagonal):

| sel | min tetangga | +isi |
|---|---|---|
| (0,0) | — | 1 |
| (0,1) | 1 | 4 |
| (0,2) | 4 | 5 |
| (1,0) | 1 | 2 |
| (1,1) | min(4,2,1)=1 | 6 |
| (1,2) | min(5,6,4)=4 | 5 |
| (2,0) | 2 | 6 |
| (2,1) | min(6,6,2)=2 | 4 |
| (2,2) | min(5,4,6)=4 | **5** |

Diagonal merendahkan jawaban dari 7 (2 arah) menjadi 5, misalnya `1-5-1`? `1 (0,0) + diagonal ke (1,1)=5 → 6`, lalu kanan ke 1 → 7. Lebih baik `1 → kanan 3 → diagonal ke (1,2)=1 → 5`, lalu bawah 1? Itu 6. Tabel bilang 5: `1 → bawah 1 → kanan? ` jalurnya `1-1-1` via (0,0)-(1,0) lalu diagonal ke (2,1)? (2,1) isi 2 → 4, lalu kanan 1 → 5. Ya: bawah, diagonal, kanan.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;
const ll MOD = 1000000007LL;

ll fallingPathMin(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<ll> dp = a[0];
    for (int i = 1; i < R; i++) {
        vector<ll> nxt(C, INF);
        for (int j = 0; j < C; j++) {
            ll best = dp[j];
            if (j > 0) best = min(best, dp[j - 1]);
            if (j + 1 < C) best = min(best, dp[j + 1]);
            nxt[j] = a[i][j] + best;
        }
        dp.swap(nxt);
    }
    return *min_element(dp.begin(), dp.end());
}

ll uniquePaths3(int R, int C) {
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = 1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
            if (i > 0 && j > 0) dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] %= MOD;
        }
    return dp[R - 1][C - 1];
}

ll minPathSum3(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            if (i > 0 && j > 0) best = min(best, dp[i - 1][j - 1]);
            dp[i][j] = a[i][j] + best;
        }
    return dp[R - 1][C - 1];
}

int main() {
    FASTIO;
    vector<vector<ll>> fall = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << fallingPathMin(fall) << '\n'; // 13
    cout << uniquePaths3(2, 2) << '\n';   // 3
    vector<vector<ll>> a = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSum3(a) << '\n';       // 5
    return 0;
}
```

**Jebakan:**

1. Falling: jawaban `dp[R-1][C-1]` — salah, boleh selesai di kolom mana pun.
2. Falling: mulai hanya `(0,0)` — salah, seluruh baris 0 sah.
3. 3-gerak kanan/bawah/diagonal dihitung seperti 2-gerak.
4. Indeks `j-1` tanpa cek tepi → RE.
5. Mencampur falling (antar-baris) dengan kanan-dalam-baris.

**Kompleksitas:** `O(RC)` semua. Falling satu baris `O(C)` memori.

---

## Sentinel menurut operator

**Teori:** Identitas adalah nilai yang tidak mengubah gabungan. Halangan harus memegang identitas itu agar tidak dipilih (`min`/`max`) atau tidak menambah cara (`+`).

| operator | identitas | halangan | basis salah yang sering |
|---|---|---|---|
| `+` hitung | 0 | 0 | menimpa start jadi 0 |
| `min` | `+INF` | `+INF` | 0, jalur tepi palsu |
| `max` | `-INF` | `-INF` | 0, sel negatif kalah dari "kosong" |

**Kapan:** setiap kali menulis `dp` grid. **Tidak:** Dijkstra punya `dist` awal `INF` juga, tetapi urutannya beda.

**STATE:** tidak menambah dimensi; ini kebijakan inisialisasi.

**TRANSISI:** `if (tetangga tidak ada || tetangga terhalang) jangan ikut` atau ikut dengan identitas.

**BASIS:** start bukan identitas kecuali start terhalang.

**Proses (table):** min-path 1×3 `[5, 0, 2]`.

| inisialisasi | dp | salah? |
|---|---|---|
| `INF` lalu `dp[0]=5` | 5, 5, 7 | benar (`0` adalah biaya sel) |
| semua 0 | 5, 0, 2 | salah: seolah mulai di tengah |

**Kode modular:**

```cpp
ll identitas(char op) {
    if (op == '+') return 0;
    if (op == 'm') return 4e18;  // min
    return LLONG_MIN / 4;        // max
}
```

**Jebakan:** `memset(dp, 0x3f, …)` untuk `ll` tidak sama dengan `0x3f3f3f3f` pada `int`. Campur `INF` int dan `ll`.

**Kompleksitas:** O(1) kebijakan, O(RC) isi.

---

## Kombinatorial tanpa batu

**Teori:** Tanpa halangan dan hanya kanan+bawah, setiap jalur adalah kata dengan `(R-1)` huruf D dan `(C-1)` huruf R. Banyaknya `C(R+C-2, R-1)`. Hitung faktorial modulo, atau perkalian berurutan dengan invers.

**Kapan:** `R,C` besar, tidak ada batu. **Tidak:** ada satu batu pun — binomial mentah salah (kecuali inclusion-exclusion pada batu sedikit).

**STATE:** tidak ada tabel grid; `C(n,k)`.

**TRANSISI:** `C(n,k) = n! / (k! (n-k)!)`.

**BASIS:** `C(n,0) = 1`, `C(n,n) = 1`.

**Proses (table):**

| R | C | n=R+C-2 | k | C(n,k) |
|---|---|---|---|---|
| 3 | 3 | 4 | 2 | 6 |
| 2 | 3 | 3 | 1 | 3 |
| 1 | 8 | 7 | 0 | 1 |
| 5 | 5 | 8 | 4 | 70 |

**Kode modular:**

```cpp
ll power(ll b, ll e, ll m) {
    ll r = 1;
    b %= m;
    while (e) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}

ll uniquePathsCombinatoric(int R, int C) {
    int n = R + C - 2, k = R - 1;
    if (k < 0 || k > n) return 0;
    vector<ll> f(n + 1, 1);
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
    ll inv = power(f[k] * f[n - k] % MOD, MOD - 2, MOD);
    return f[n] * inv % MOD;
}
```

**Jebakan:** `k = R` bukan `R-1`. MOD bukan prima → jangan Fermat. `R=1,C=1` → `C(0,0)=1`.

**Kompleksitas:** `O(R+C + log MOD)`.

---

## Dua jalur ide

**Teori:** Dua orang jalan dari (0,0) ke (R-1,C-1), sel bersama dihitung sekali. State naif `(i1,j1,i2,j2)` = `O(R²C²)`. Karena keduanya sudah `k` langkah, `i+j = k` sama, cukup `dp[k][i1][i2]`. File ini hanya ide; implementasi penuh jarang di Day 150.

**Kapan:** cherry pickup, "two paths collect max". **Tidak:** sel boleh dihitung dua kali — cukup dua kali min/max path terpisah.

**STATE:** pada langkah `k`, jalur 1 di baris `i1`, jalur 2 di baris `i2`.

**TRANSISI:** 2×2 pilihan arah, tambah isi sel, kurangi dobel jika `i1==i2`.

**BASIS:** `k=0`, `i1=i2=0`, nilai `a[0][0]`.

**Proses (table):** 2×2 semua 1. Awal dan akhir bersama. Tengah: jika pecah, nilai 3; jika sama, 2.

**Kode modular:** skelet singkat — jangan hafal sebelum 1 jalur lancar.

```cpp
// ide: O(R^2 * (R+C)), bukan kode wajib Day 150
ll twoPathsHint(int R, int C) {
    return 1LL * R * R * (R + C);
}
```

**Jebakan:** menghitung sel bersama dua kali. `R≠C` tanpa cek kolom `k-i`.

**Kompleksitas:** `O(R²(R+C))`.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;
const ll INF = 4e18;

ll uniquePaths(int R, int C);
ll uniquePathsObstacles(const vector<string>& g);
ll minPathSum(const vector<vector<ll>>& a);
ll fallingPathMin(const vector<vector<ll>>& a);
ll uniquePaths3(int R, int C);
ll minPathSum3(const vector<vector<ll>>& a);

int main() {
    FASTIO;
    cout << uniquePaths(3, 3) << '\n';
    return 0;
}
```

Urutan cek sebelum kode:

```
1. Arah apa saja? 2 / 3 jatuh / 3 diagonal / 4 (bukan DP ini)
2. Operator? +  atau min/max
3. Start unik atau seluruh tepi?
4. Finish unik atau min seluruh baris akhir?
5. Ada batu? isi identitas
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| jalur 0 pada grid kosong | start ditimpa 0+0 | skip `(0,0)` |
| jalur 1 padahal ada `#` tengah | `#` tidak dinolkan | `dp=0; continue` |
| min-path = jumlah tepi saja | sentinel 0 | `INF` |
| min-path negatif aneh | `INF+a` overflow | cek `best < INF` |
| falling salah di pojok | jawab `dp[R-1][C-1]` | `min` seluruh baris |
| 3 jalur 2×2 = 2 | lupa diagonal | tambah `dp[i-1][j-1]` |
| TLE 1e6 × 1e6 | DP pada tanpa batu | binomial |
| RE j-1 | tepi falling | `if (j>0)` |
| 4 arah WA/TLE | siklus | BFS/Dijkstra |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `uniquePaths` | 3×3 | 6 |
| `uniquePaths` | 2×3 | 3 |
| `uniquePaths` | 1×1 | 1 |
| `uniquePathsObstacles` | 3×3 `#` tengah | 2 |
| `uniquePathsObstacles` | 2×3 `#` di (0,1) | 1 |
| `uniquePathsObstacles` | start `#` | 0 |
| `minPathSum` | `[[1,3,1],[1,5,1],[4,2,1]]` | 7 |
| `minPathSum` | `[[1,2,3],[4,5,6]]` | 12 |
| `fallingPathMin` | `[[2,1,3],[6,5,4],[7,8,9]]` | 13 |
| `uniquePaths3` | 2×2 | 3 |
| `minPathSum3` | `[[1,3,1],[1,5,1],[4,2,1]]` | 5 |
| `uniquePathsCombinatoric` | 5×5 | 70 |

Rekonstruksi jalur grid ada di [12-rekonstruksi](12-rekonstruksi.md). Hemat memori satu baris di [13-memori](13-memori.md).

Lanjut ke [11-range](11-range.md): state berubah dari sel ke **interval**.
