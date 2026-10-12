# 14 — DP: string, grid, range, rekonstruksi

[← Prinsip dan knapsack](13-dp-prinsip-1d-knapsack.md) · [README](README.md) · [Lanjut bitmask dan tree →](15-dp-bitmask-digit-tree-optim.md)

Folder 09 Day **149–153**: LCS, edit distance, grid, range DP, rekonstruksi, rolling array. Latihan harian di `ComProgLearning/CP/Day-149` sampai `Day-153`.

Konvensi dua string: tabel `(n+1) × (m+1)` **1-indexed**, string **0-indexed**. Huruf terakhir prefiks `i` adalah `a[i-1]`. Baris 0 dan kolom 0 = string kosong.

Tiga pertanyaan tetap wajib: **STATE** kalimat lengkap, **TRANSISI**, **BASIS**.

## Daftar isi

- [LCS](#lcs)
- [Edit distance](#edit-distance)
- [Turunan LCS](#turunan-lcs)
- [Grid: hitung jalur](#grid-hitung-jalur)
- [Grid: jumlah minimum](#grid-jumlah-minimum)
- [Grid: dua jalur](#grid-dua-jalur)
- [Range DP: kerangka](#range-dp-kerangka)
- [Matrix chain](#matrix-chain)
- [Stone merge / slimes](#stone-merge--slimes)
- [Palindrome partition](#palindrome-partition)
- [Burst balloons](#burst-balloons)
- [Rekonstruksi jalur](#rekonstruksi-jalur)
- [Rolling array](#rolling-array)
- [Template gabungan](#template-gabungan)
- [Peta jebakan file ini](#peta-jebakan-file-ini)
- [Rectangle cutting](#rectangle-cutting)
- [LPS dan palindrom substring](#lps-dan-palindrom-substring)

---

## LCS

**Teori:** Subsekuens terpanjang yang muncul di kedua string. Bukan substring: tidak harus berdekatan. Keputusan terakhir: apakah `a[i-1]` sama dengan `b[j-1]`? Jika sama, selalu ada LCS optimal yang memakai pasangan itu (bisa dibuktikan dengan tukar pasangan). Jika beda, buang salah satu huruf. Analoginya dua antrean tiket: cocokkan huruf yang sama, atau lewati satu antrean.

**Kapan:** "common subsequence", similarity, atau sebagai batu bata SCS / penghapusan. **Tidak:** harus berdekatan (itu longest common substring). `n, m ≥ 5000` tabel penuh bisa TLE/MLE — rolling hanya panjang.

**STATE:** `dp[i][j]` adalah panjang LCS dari prefiks `a[0..i-1]` dan prefiks `b[0..j-1]`.

**TRANSISI:** jika `a[i-1] == b[j-1]` maka `dp[i][j] = dp[i-1][j-1] + 1`; jika tidak, `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.

**BASIS:** `dp[0][j] = dp[i][0] = 0` karena LCS dengan string kosong bernilai 0.

**Proses angka:** `a = "ABCBDAB"`, `b = "BDCABA"`.

```
        ""  B  D  C  A  B  A
    ""   0  0  0  0  0  0  0
    A    0  0  0  0  1  1  1
    B    0  1  1  1  1  2  2
    C    0  1  1  2  2  2  2
    B    0  1  1  2  2  3  3
    D    0  1  2  2  2  3  3
    A    0  1  2  2  3  3  4
    B    0  1  2  2  3  4  4
```

`dp[7][6] = 4`. Contoh LCS: `BCBA`, `BDAB`, `BCAB`. Panjang unik, barisan tidak.

Rekonstruksi dari `(7,6)`: `B==A`? tidak, atas=4 ≥ kiri=3 → naik ke `(6,6)` `A==A` → ambil A, diagonal `(5,5)` ... lanjut sampai `(0,*)`. Balik string.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int lcsLen(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}

int lcsRolling(string a, string b) {
    if (a.size() < b.size()) swap(a, b);
    int n = (int)a.size(), m = (int)b.size();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int prevDiag = 0;
        for (int j = 1; j <= m; j++) {
            int simpan = dp[j];
            if (a[i - 1] == b[j - 1]) dp[j] = prevDiag + 1;
            else dp[j] = max(dp[j], dp[j - 1]);
            prevDiag = simpan;
        }
    }
    return dp[m];
}

string lcsString(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res += a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a = "ABCBDAB", b = "BDCABA";
    cout << lcsLen(a, b) << " " << lcsRolling(a, b) << "\n";
    cout << lcsString(a, b) << "\n";
    return 0;
}
```

**Jebakan:**

1. Membandingkan `a[i]` dengan `b[j]` (off-by-one).
2. Saat cocok tetap mengambil `max(atas, kiri)` tanpa diagonal — biasanya tidak salah panjang, tapi lebih lambat dan membingungkan rekonstruksi.
3. Rolling menimpa diagonal sebelum disimpan.
4. Mencetak hasil rekonstruksi tanpa `reverse`.

**Kompleksitas:** `O(nm)` waktu. Memori `O(nm)` atau `O(min(n,m))` rolling. Rekonstruksi butuh tabel penuh.

---

## Edit distance

**Teori:** Jumlah operasi minimum mengubah `a` jadi `b`: sisip, hapus, ganti, masing-masing biaya 1 (Levenshtein). Diagonal = ganti (atau gratis jika sama). Atas = hapus `a[i-1]`. Kiri = sisip `b[j-1]`. Base case **bukan nol**: mengubah ke string kosong butuh hapus semua.

**Kapan:** spell-check, beda dua string, DNA. **Tidak:** hanya sisip/hapus tanpa ganti — itu `n+m-2*LCS`. Biaya ganti > sisip+hapus: `min` otomatis menghindari ganti.

**STATE:** `dp[i][j]` adalah jumlah operasi minimum untuk mengubah prefiks `a[0..i-1]` menjadi prefiks `b[0..j-1]`.

**TRANSISI:** jika huruf sama, `dp[i][j] = dp[i-1][j-1]`; jika tidak, `1 + min(ganti, hapus, sisip)`.

**BASIS:** `dp[i][0] = i` (hapus i huruf), `dp[0][j] = j` (sisip j huruf).

**Proses angka:** `a = "kitten"`, `b = "sitting"`.

```
         ""  s  i  t  t  i  n  g
    ""    0  1  2  3  4  5  6  7
    k     1  1  2  3  4  5  6  7
    i     2  2  1  2  3  4  5  6
    t     3  3  2  1  2  3  4  5
    t     4  4  3  2  1  2  3  4
    e     5  5  4  3  2  2  3  4
    n     6  6  5  4  3  3  2  3
```

Jawaban 3: `k→s`, `e→i`, sisip `g`.

Kalau basis baris 0 diisi 0, seluruh tabel terlalu kecil — WA yang "terlihat masuk akal".

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int editDistance(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
    return dp[n][m];
}

vector<string> editOps(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
    vector<string> ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            ops.push_back(string("GANTI ") + a[i - 1] + " -> " + b[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            ops.push_back(string("HAPUS ") + a[i - 1]);
            i--;
        } else {
            ops.push_back(string("SISIP ") + b[j - 1]);
            j--;
        }
    }
    reverse(ops.begin(), ops.end());
    return ops;
}

long long editWeighted(const string& a, const string& b, long long ci, long long cd, long long cr) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = 1LL * i * cd;
    for (int j = 0; j <= m; j++) dp[0][j] = 1LL * j * ci;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min({dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : cr),
                            dp[i - 1][j] + cd, dp[i][j - 1] + ci});
    return dp[n][m];
}

int editDistance2Row(string a, string b) {
    if (b.size() > a.size()) swap(a, b);
    int n = (int)a.size(), m = (int)b.size();
    vector<int> prev(m + 1), cur(m + 1);
    for (int j = 0; j <= m; j++) prev[j] = j;
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++) {
            int cost = (a[i - 1] == b[j - 1] ? 0 : 1);
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + cost});
        }
        prev.swap(cur);
    }
    return prev[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a = "kitten", b = "sitting";
    cout << editDistance(a, b) << " " << editDistance2Row(a, b) << "\n";
    for (auto& s : editOps(a, b)) cout << s << "\n";
    return 0;
}
```

**Jebakan:**

1. Basis nol seperti LCS.
2. Rekonstruksi `while (i && j)` — sisa prefiks tidak terproses. Pakai `||`.
3. Tidak mengutamakan "huruf sama" saat telusur mundur.
4. `cr > ci+cd` tidak masalah jika `min` lengkap.

**Kompleksitas:** `O(nm)` waktu. Memori `O(nm)` atau `O(min(n,m))`.

---

## Turunan LCS

**Teori:** Banyak soal string 2D adalah LCS dengan operator diganti. Longest common **substring** mereset ke 0 saat beda, jawaban `max` seluruh tabel. Penghapusan saja: `n+m-2*LCS`. Shortest common supersequence: `n+m-LCS`.

**Kapan:** soal menyebut substring, supersequence, atau hanya insert/delete. **Tidak:** edit dengan ganti — itu Levenshtein.

**STATE substring:** `dp[i][j]` adalah panjang common substring yang **berakhir** di `a[i-1]` dan `b[j-1]`.

**TRANSISI substring:** sama → `dp[i-1][j-1]+1`; beda → `0`.

**BASIS:** baris 0 dan kolom 0 tetap 0.

**Proses angka:** `a = "abcdae"`, `b = "acdae"`.

```
common substring terpanjang "cdae" = 4
LCS juga 4 di sini; beda muncul pada "abcdef" vs "xbcdyz" :
  LCS "bcd" = 3, LCSubstring "bcd" = 3
  "aa" vs "a a" dengan spasi: LCS 2, substring 1
```

`a = "ABABC"`, `b = "BABCA"`: substring `BABC` panjang 4.

SCS `"abac"` dan `"cab"`: LCS `"ab"` atau `"ac"` panjang 2, SCS panjang `4+3-2 = 5` (`cabac`).

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int lcsLen(const string& a, const string& b); // dari bagian LCS

int lcSubstring(const string& a, const string& b, int& endA) {
    int n = (int)a.size(), m = (int)b.size(), best = 0;
    endA = -1;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = 0;
            if (dp[i][j] > best) {
                best = dp[i][j];
                endA = i;
            }
        }
    return best;
}

int minDeletions(const string& a, const string& b) {
    return (int)a.size() + (int)b.size() - 2 * lcsLen(a, b);
}

int scsLength(const string& a, const string& b) {
    return (int)a.size() + (int)b.size() - lcsLen(a, b);
}

string scsString(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res += a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            res += a[i - 1];
            i--;
        } else {
            res += b[j - 1];
            j--;
        }
    }
    while (i > 0) res += a[--i];
    while (j > 0) res += b[--j];
    reverse(res.begin(), res.end());
    return res;
}

int longestPalindromicSubseq(const string& s) {
    string t = s;
    reverse(t.begin(), t.end());
    return lcsLen(s, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int endA;
    cout << lcSubstring("ABABC", "BABCA", endA) << " end=" << endA << "\n";
    cout << scsLength("abac", "cab") << " " << scsString("abac", "cab") << "\n";
    cout << longestPalindromicSubseq("bbbab") << "\n";
    return 0;
}
```

Salin `lcsLen` dari bagian LCS ke file yang sama sebelum compile.

**Jebakan:** substring memakai `max(atas, kiri)` seperti LCS. Jawaban substring diambil `dp[n][m]` bukan maksimum tabel. SCS lupa sisa prefiks.

**Kompleksitas:** `O(nm)` semua.

---

## Grid: hitung jalur

**Teori:** Grid kanan-bawah adalah DAG. Monovariant `i+j` selalu naik, jadi tidak ada siklus. Urutan topologis gratis: baris demi baris kiri ke kanan. `dp[i][j] = dp[atas] + dp[kiri]`. Halangan: tugaskan 0 (identitas `+`). Tanpa halangan dan `R, C` besar: `C(R+C-2, R-1)` modulo.

**Kapan:** hanya kanan dan bawah, hitung jalur. **Tidak:** boleh atas/kiri (bisa siklus — BFS/DFS+memo di DAG terarah, atau Dijkstra). Empat arah tanpa hambatan = bukan grid DP klasik.

**STATE:** `dp[i][j]` adalah banyak jalur dari (0,0) ke sel `(i, j)`.

**TRANSISI:** `dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD`, kecuali sel terhalang maka 0.

**BASIS:** `dp[0][0] = 1` jika tidak terhalang, selain itu 0. Sel di luar grid dianggap 0.

**Proses angka:** grid 3×3 tanpa halangan.

```
1  1  1
1  2  3
1  3  6
```

Jawaban 6. Dengan `#` di tengah:

```
1  1  1
1  0  1
1  1  2
```

Awal `#` → 0. Padding 1-indexed: set `dp[1][1] = 1` lalu **lewati** sel itu di loop, atau tetangga nol menimpanya.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll countPaths(int R, int C) {
    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    return dp[R][C];
}

ll countPathsObstacle(const vector<string>& g) {
    int R = (int)g.size(), C = (int)g[0].size();
    if (g[0][0] == '#' || g[R - 1][C - 1] == '#') return 0;
    vector<vector<ll>> dp(R + 1, vector<ll>(C + 1, 0));
    dp[1][1] = 1;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++) {
            if (g[i - 1][j - 1] == '#') {
                dp[i][j] = 0;
                continue;
            }
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    return dp[R][C];
}

ll countPathsRolling(const vector<string>& g) {
    int R = (int)g.size(), C = (int)g[0].size();
    if (g[0][0] == '#') return 0;
    vector<ll> dp(C, 0);
    dp[0] = 1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (g[i][j] == '#') {
                dp[j] = 0;
                continue;
            }
            if (j > 0) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    return dp[C - 1];
}

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

ll countPathsCombinatoric(int R, int C) {
    int n = R + C - 2, k = R - 1;
    vector<ll> f(n + 1, 1);
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
    ll inv = power(f[k] * f[n - k] % MOD, MOD - 2, MOD);
    return f[n] * inv % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << countPaths(3, 3) << " " << countPathsCombinatoric(3, 3) << "\n";
    vector<string> g = {"...", ".#.", "..."};
    cout << countPathsObstacle(g) << " " << countPathsRolling(g) << "\n";
    return 0;
}
```

**Jebakan:**

1. `dp[1][1]` ditimpa 0+0.
2. Awal/akhir `#` tidak dicek.
3. Halangan: `continue` tanpa `dp = 0`.
4. Lupa modulo: `C(1998, 999)` ratusan digit.

**Kompleksitas:** `O(RC)` atau kombinatorial `O(R+C + log MOD)`.

---

## Grid: jumlah minimum

**Teori:** Operator `+` diganti `min`, sentinel `INF` bukan 0. Nol pada halangan berarti "gratis" — jalur haram jadi termurah. Jangan `INF + a[i][j]` tanpa cek: sentinel rusak dan menular. Rekonstruksi butuh tabel penuh.

**Kapan:** biaya sel, kanan/bawah. **Tidak:** bobot sisi negatif siklus (bukan grid DAG). Empat arah: Dijkstra.

**STATE:** `dp[i][j]` adalah jumlah minimum jalur dari (0,0) ke `(i, j)`.

**TRANSISI:** `dp[i][j] = a[i][j] + min(dp[atas], dp[kiri])` jika ada tetangga sah.

**BASIS:** `dp[0][0] = a[0][0]`.

**Proses angka:**

```
1  3  1
1  5  1
4  2  1

dp:
1  4  5
2  7  6
6  8  7
```

Jalur `1-3-1-1-1` jumlah 7. Halangan di (1,1):

```
dp 1  4  5
   2 INF  6
   6  8  7
```

`INF` tidak boleh ditambah 5 lalu dipakai.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

ll minPathSum(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, 0));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            ll best = INF;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            dp[i][j] = a[i][j] + best;
        }
    return dp[R - 1][C - 1];
}

ll minPathObstacle(const vector<vector<ll>>& a, const vector<string>& g) {
    int R = (int)a.size(), C = (int)a[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    if (g[0][0] == '#') return -1;
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
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
    return dp[R - 1][C - 1] >= INF ? -1 : dp[R - 1][C - 1];
}

ll gridMinPath1D(const vector<vector<ll>>& grid) {
    int R = (int)grid.size(), C = (int)grid[0].size();
    vector<ll> dp(C, INF);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) dp[j] = grid[i][j];
            else {
                ll up = dp[j];
                ll left = (j > 0 ? dp[j - 1] : INF);
                dp[j] = grid[i][j] + min(up, left);
            }
        }
    return dp[C - 1];
}

vector<pair<int, int>> minPathTrace(const vector<vector<ll>>& dp) {
    int R = (int)dp.size(), C = (int)dp[0].size();
    vector<pair<int, int>> path;
    int i = R - 1, j = C - 1;
    while (i > 0 || j > 0) {
        path.push_back({i, j});
        if (i == 0) j--;
        else if (j == 0) i--;
        else if (dp[i - 1][j] <= dp[i][j - 1]) i--;
        else j--;
    }
    path.push_back({0, 0});
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> a = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << minPathSum(a) << " " << gridMinPath1D(a) << "\n";
    return 0;
}
```

**Jebakan:** sentinel 0 untuk `min`. `INF + a` menular. Trace `while (i && j)`. Rolling lalu diminta jalur.

**Kompleksitas:** `O(RC)` waktu. Memori `O(RC)` atau `O(C)`.

Aturan sentinel:

| Operator | Identitas | Halangan |
|---|---|---|
| `+` (hitung) | 0 | 0 |
| `min` | `+INF` | `+INF` |
| `max` | `-INF` | `-INF` |

---

## Grid: dua jalur

**Teori:** Dua orang jalan bersamaan dari (0,0) ke (R-1,C-1), sel yang dilalui keduanya dihitung sekali. State naif `(i1,j1,i2,j2)` terlalu besar. Karena `k = i+j` sama, cukup `dp[k][i1][i2]`. `O(R^2 (R+C))`, bukan `O((RC)^2)`.

**Kapan:** AtCoder DP-Y varian / LC cherry pickup. **Tidak:** dua jalur bebas waktu — itu dua kali min-path jika sel boleh dobel.

**STATE:** `dp[i1][i2]` pada langkah `k` adalah nilai maksimum dua jalur yang sudah `k` langkah, baris pertama `i1`, baris kedua `i2` (kolom `k-i`).

**TRANSISI:** dari setiap pasangan arah (bawah/kanan) × (bawah/kanan), tambah `a[n1][j1] + (n1==n2 ? 0 : a[n2][j2])`.

**BASIS:** `dp[0][0] = a[0][0]` pada `k = 0`.

**Proses angka:** grid 2×2 `[[1,1],[1,1]]`. Dua jalur harus berbagi awal dan akhir. Nilai `1+1+1 = 3` jika tengah berbeda, atau 2 jika sama.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;

ll twoPaths(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    int K = R + C - 2;
    vector<vector<ll>> cur(R, vector<ll>(R, NEG)), nxt;
    cur[0][0] = a[0][0];
    for (int k = 0; k < K; k++) {
        nxt.assign(R, vector<ll>(R, NEG));
        for (int i1 = 0; i1 < R; i1++)
            for (int i2 = 0; i2 < R; i2++) {
                if (cur[i1][i2] == NEG) continue;
                for (int d1 = 0; d1 < 2; d1++)
                    for (int d2 = 0; d2 < 2; d2++) {
                        int n1 = i1 + d1, n2 = i2 + d2;
                        int j1 = k + 1 - n1, j2 = k + 1 - n2;
                        if (n1 >= R || n2 >= R || j1 < 0 || j1 >= C || j2 < 0 || j2 >= C) continue;
                        ll add = a[n1][j1] + (n1 == n2 ? 0 : a[n2][j2]);
                        nxt[n1][n2] = max(nxt[n1][n2], cur[i1][i2] + add);
                    }
            }
        cur.swap(nxt);
    }
    return cur[R - 1][R - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> a = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    cout << twoPaths(a) << "\n";
    return 0;
}
```

**Jebakan:** menghitung sel bersama dua kali. Tidak men-skip `NEG`. `R ≠ C` tanpa cek kolom.

**Kompleksitas:** `O(R^2 (R+C))` waktu, `O(R^2)` memori.

---

## Range DP: kerangka

**Teori:** State bukan prefiks, melainkan interval `[l, r]`. Operasi terakhir selalu menggabung dua blok bersebelahan `[l, m]` dan `[m+1, r]`. Karena subinterval lebih pendek, loop **wajib menurut panjang**. Loop `l` lalu `r` mentah sering membaca `dp[m+1][r]` yang belum diisi.

**Kapan:** gabung batu, kurung matriks, potong kayu, palindrom interval, burst balloons. **Tidak:** elemen tidak wajib kontigu (itu knapsack/LIS).

**STATE:** `dp[l][r]` adalah jawaban optimal untuk memproses segmen indeks `l..r` inklusif.

**TRANSISI:** `dp[l][r] = min/max atas m ∈ [l, r) dari (dp[l][m] + dp[m+1][r] + biaya(l,m,r))`.

**BASIS:** `dp[i][i] = 0` (satu elemen, tidak ada gabungan). Kadang panjang 2 diisi khusus.

**Proses angka:** tiga elemen, biaya gabung = jumlah. `a = [1, 2, 3]`.

```
len=1: dp[0][0]=dp[1][1]=dp[2][2]=0
len=2: dp[0][1] = 0+0+(1+2)=3
       dp[1][2] = 0+0+(2+3)=5
len=3: m=0: 0+5+6=11
       m=1: 3+0+6=9
       dp[0][2] = 9
```

Urutan `(1+2)+3` biaya `3+6=9`. `(1)+(2+3)` biaya `5+6=11`.

**Kode kerangka:**

```cpp
for (int i = 0; i < n; i++) dp[i][i] = 0;
for (int len = 2; len <= n; len++)
    for (int l = 0; l + len <= n; l++) {
        int r = l + len - 1;
        dp[l][r] = INF;
        for (int m = l; m < r; m++)
            dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r] + biaya(l, m, r));
    }
```

**Jebakan:** loop `for l, for r=l+1` tanpa `len`. `m` sampai `r` inklusif (interval kanan kosong). Lupa `INF` awal.

**Kompleksitas:** `O(n^3)` waktu, `O(n^2)` memori. `n ≤ 400..500` aman.

---

## Matrix chain

**Teori:** Perkalian matriks asosiatif, jumlah kali skalar tidak. `A(10×100) × B(100×5) × C(5×20)`: `(AB)C = 10*100*5 + 10*5*20 = 6000`, `A(BC) = 100*5*20 + 10*100*20 = 30000`. Dimensi disimpan di `p[0..n]`: matriks `i` berukuran `p[i] × p[i+1]`.

**Kapan:** urutan asosiasi, kurung optimal. **Tidak:** matriks tidak berantai (dimensi tidak nyambung).

**STATE:** `dp[l][r]` adalah biaya minimum mengalikan matriks `l..r` (0-based, inklusif).

**TRANSISI:** pecah setelah `k` (`l ≤ k < r`): `dp[l][k] + dp[k+1][r] + p[l]*p[k+1]*p[r+1]`.

**BASIS:** `dp[i][i] = 0`.

**Proses angka:** `p = [10, 100, 5, 20]`, tiga matriks.

```
dp[0][1] = 10*100*5 = 5000
dp[1][2] = 100*5*20 = 10000
dp[0][2] = min(0+10000+10*100*20, 5000+0+10*5*20)
         = min(30000, 6000) = 6000
```

Kurung `(A1 x A2) x A3`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll matrixChain(const vector<ll>& p) {
    int n = (int)p.size() - 1;
    if (n <= 1) return 0;
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    return dp[0][n - 1];
}

pair<ll, string> matrixChainParens(const vector<ll>& p) {
    int n = (int)p.size() - 1;
    if (n == 0) return {0, ""};
    if (n == 1) return {0, "A1"};
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> split(n, vector<int>(n, -1));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    split[l][r] = k;
                }
            }
        }
    function<string(int, int)> build = [&](int l, int r) -> string {
        if (l == r) return "A" + to_string(l + 1);
        int k = split[l][r];
        return "(" + build(l, k) + " x " + build(k + 1, r) + ")";
    };
    return {dp[0][n - 1], build(0, n - 1)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> p = {10, 100, 5, 20};
    auto [cost, expr] = matrixChainParens(p);
    cout << cost << "\n" << expr << "\n";
    return 0;
}
```

**Jebakan:** `p` berukuran `n` bukan `n+1`. Indeks `p[k+1]` vs `p[k]`. Overflow `int` pada hasil kali tiga dimensi.

**Kompleksitas:** `O(n^3)` waktu, `O(n^2)` memori.

---

## Stone merge / slimes

**Teori:** Gabung dua tumpukan bersebelahan, biaya = jumlah keduanya (AtCoder DP-N Slimes). Setelah gabung, tumpukan baru bisa digabung lagi. Prefix sum membuat `sum(l..r)` O(1). Sama dengan MCM, biaya `sum[l..r]` bukan hasil kali dimensi.

**Kapan:** "merge adjacent", slimes, batu, file concatenation. **Tidak:** boleh gabung tidak bersebelahan (Huffman / greedy).

**STATE:** `dp[l][r]` adalah biaya minimum menggabungkan batu `l..r` menjadi satu.

**TRANSISI:** `dp[l][r] = min_k (dp[l][k] + dp[k+1][r]) + pref[r+1]-pref[l]`.

**BASIS:** `dp[i][i] = 0`.

**Proses angka:** `a = [10, 20, 30]`.

```
pref = [0, 10, 30, 60]
dp[0][1] = 30
dp[1][2] = 50
dp[0][2] = min(0+50+60, 30+0+60) = 90
```

Urutan `(10+20)=30` lalu `+30=60`, total biaya `30+60=90`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll stoneMerging(const vector<ll>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            ll sum_lr = pref[r + 1] - pref[l];
            for (int k = l; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum_lr);
        }
    return dp[0][n - 1];
}

ll minCostCutStick(ll L, vector<int> cuts) {
    cuts.push_back(0);
    cuts.push_back((int)L);
    sort(cuts.begin(), cuts.end());
    int m = (int)cuts.size();
    vector<vector<ll>> dp(m, vector<ll>(m, 0));
    for (int len = 2; len < m; len++)
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INF;
            ll seg = cuts[r] - cuts[l];
            for (int k = l + 1; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + seg);
        }
    return dp[0][m - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << stoneMerging({10, 20, 30}) << "\n";
    cout << minCostCutStick(7, {1, 3, 4, 5}) << "\n";
    return 0;
}
```

Potong kayu: biaya potong = panjang segmen saat ini. Titik 0 dan `L` wajib ditambah. `k` adalah potongan terakhir di dalam `(l, r)`.

**Jebakan:** biaya dihitung dua kali (di anak dan di induk) atau lupa `sum_lr`. Cut stick tanpa sort. `n = 400` `O(n^3)` ketat — Knuth (file 15) jika QI berlaku.

**Kompleksitas:** `O(n^3)` waktu, `O(n^2)` memori.

---

## Palindrome partition

**Teori:** Potong string jadi palindrom, minimalkan jumlah potongan (atau bagian). Dua tahap: `isPal[l][r]` O(n²) dari yang lebih pendek, lalu `dp[r]` = min potongan prefiks `r`. Ini campuran range boolean + DP 1D.

**Kapan:** "palindrome partitioning", minimum cuts. **Tidak:** longest palindromic **substring** (expand / Manacher). LPS subsequence = LCS dengan reverse.

**STATE:** `isPal[l][r]` benar jika `s[l..r]` palindrom. `dp[r]` adalah banyak bagian palindrom minimum untuk `s[0..r-1]`.

**TRANSISI:** `isPal[l][r] = (s[l]==s[r]) && (len≤2 || isPal[l+1][r-1])`. `dp[r] = min (dp[l]+1)` untuk `isPal[l][r-1]`.

**BASIS:** `isPal[i][i] = true`. `dp[0] = 0`. Jawaban potongan = `dp[n]-1`.

**Proses angka:** `s = "aab"`.

```
isPal:
 a a b
a 1 1 0
a   1 0
b     1

dp[0]=0
dp[1] (a)  = 1
dp[2] (aa) = 1   karena [0..1] palindrom
dp[3] (aab)= 2   "aa"|"b"
```

Potongan 1.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int minPalindromeCuts(const string& s) {
    int n = (int)s.size();
    if (n <= 1) return 0;
    vector<vector<char>> isPal(n, vector<char>(n, 0));
    for (int len = 1; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) isPal[l][r] = (len <= 2 || isPal[l + 1][r - 1]);
        }
    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;
    for (int r = 1; r <= n; r++)
        for (int l = 0; l < r; l++)
            if (isPal[l][r - 1]) dp[r] = min(dp[r], dp[l] + 1);
    return dp[n] - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << minPalindromeCuts("aab") << "\n";   // 1
    cout << minPalindromeCuts("aba") << "\n";   // 0
    return 0;
}
```

**Jebakan:** `isPal` diisi tanpa urutan panjang. Mengembalikan jumlah bagian, bukan potongan. `O(n^3)` cek palindrom naif tiap transisi.

**Kompleksitas:** `O(n^2)` waktu dan memori.

---

## Burst balloons

**Teori:** Meletuskan balon `k` di antara yang masih hidup, koin `kiri * k * kanan`. Urutan maju sulit karena tetangga berubah. **Reverse:** anggap `k` adalah yang **terakhir** meletus di interval terbuka `(l, r)`. Saat itu tetangga tetap `nums[l]` dan `nums[r]` (sentinel 1 di ujung).

**Kapan:** LC 312, interval dengan "elemen terakhir". **Tidak:** letus dari tepi saja (itu greedy/stack).

**STATE:** `dp[l][r]` adalah koin maksimum meletuskan semua balon **ketat di antara** `l` dan `r` (tidak termasuk `l, r` yang jadi dinding).

**TRANSISI:** untuk `k = l+1..r-1`: `dp[l][k] + dp[k][r] + nums[l]*nums[k]*nums[r]`.

**BASIS:** interval tanpa isi (`r = l+1`) bernilai 0.

**Proses angka:** `a = [3, 1, 5]`, nums = `[1, 3, 1, 5, 1]`.

```
len=2 dinding: 0
(l,r)=(0,2) k=1: 1*3*1 = 3
(1,3) k=2: 3*1*5 = 15
(2,4) k=3: 1*5*1 = 5
(0,3) k=1: 0+15+1*3*5=30
      k=2: 3+0+1*1*5=8
(1,4) k=2: 0+5+3*1*1=8
      k=3: 15+0+3*5*1=30
(0,4) k=1: 0+30+1*3*1=33
      k=2: 3+5+1*1*1=9
      k=3: 30+0+1*5*1=35
```

Jawaban 35.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll burstBalloons(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    vector<ll> nums(n + 2, 1);
    for (int i = 0; i < n; i++) nums[i + 1] = a[i];
    int m = n + 2;
    vector<vector<ll>> dp(m, vector<ll>(m, 0));
    for (int len = 2; len < m; len++)
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            for (int k = l + 1; k < r; k++) {
                ll gain = dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r];
                dp[l][r] = max(dp[l][r], gain);
            }
        }
    return dp[0][m - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << burstBalloons({3, 1, 5}) << "\n"; // 35
    return 0;
}
```

**Jebakan:** memodelkan "yang pertama meletus" (tetangga berubah). Lupa sentinel 1. Loop `len` dari 1.

**Kompleksitas:** `O(n^3)` waktu, `O(n^2)` memori.

---

## Rekonstruksi jalur

**Teori:** Nilai optimal ≠ objek optimal. Dua cara: (1) simpan `parent` / `pick` saat transisi, (2) bandingkan ulang `dp` saat mundur (hemat memori pointer, butuh tabel utuh). Rolling array hampir selalu **menghancurkan** rekonstruksi. Saat seri, tentukan tie-break (leksikografis terkecil, indeks terkecil).

**Kapan:** soal minta barang, string, atau langkah. **Tidak:** hanya nilai — jangan bangun parent.

**STATE:** sama dengan DP asalnya. Tambahan `par[i]` = pendahulu yang menghasilkan `dp[i]`.

**TRANSISI:** setiap kali kandidat **lebih baik** (bukan `<=` kecuali tie-break), tulis parent.

**BASIS:** `par[basis] = -1`.

**Proses angka knapsack:** dari contoh file 13, `dp[3][5]=7 = dp[2][5]` → skip barang 2. `dp[2][5]=7 ≠ dp[1][5]=3` → ambil (2,4), sisa 3. Ambil (3,3). Barang 0 dan 1.

Grid suffix DP untuk leksikografis `D < R`: isi dari tujuan, lalu dari awal pilih `D` jika `dp` cocok.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

pair<ll, vector<int>> reconstructKnapsack01(const vector<ll>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
        }
    vector<int> chosen;
    int cur = W;
    for (int i = n; i >= 1; i--)
        if (dp[i][cur] != dp[i - 1][cur]) {
            chosen.push_back(i);
            cur -= (int)w[i - 1];
        }
    reverse(chosen.begin(), chosen.end());
    return {dp[n][W], chosen};
}

pair<int, vector<int>> reconstructLIS(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return {0, {}};
    vector<int> dp(n, 1), parent(n, -1);
    int best_len = 1, best_idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        if (dp[i] > best_len) {
            best_len = dp[i];
            best_idx = i;
        }
    }
    vector<int> lis;
    for (int cur = best_idx; cur != -1; cur = parent[cur]) lis.push_back(a[cur]);
    reverse(lis.begin(), lis.end());
    return {best_len, lis};
}

pair<ll, string> reconstructGridMinPath(const vector<vector<ll>>& grid) {
    int R = (int)grid.size(), C = (int)grid[0].size();
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[R - 1][C - 1] = grid[R - 1][C - 1];
    for (int r = R - 1; r >= 0; r--)
        for (int c = C - 1; c >= 0; c--) {
            if (r == R - 1 && c == C - 1) continue;
            ll nxt = INF;
            if (r + 1 < R) nxt = min(nxt, dp[r + 1][c]);
            if (c + 1 < C) nxt = min(nxt, dp[r][c + 1]);
            dp[r][c] = grid[r][c] + nxt;
        }
    string path;
    int r = 0, c = 0;
    while (r < R - 1 || c < C - 1) {
        if (r + 1 < R && dp[r][c] == grid[r][c] + dp[r + 1][c]) {
            path.push_back('D');
            r++;
        } else {
            path.push_back('R');
            c++;
        }
    }
    return {dp[0][0], path};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto [val, idx] = reconstructKnapsack01({3, 2, 4}, {3, 4, 2}, 5);
    cout << val << " idx:";
    for (int i : idx) cout << " " << i;
    cout << "\n";
    auto [len, lis] = reconstructLIS({10, 9, 2, 5, 3, 7, 101, 18});
    cout << len << "\n";
    vector<vector<ll>> g = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    auto [cost, p] = reconstructGridMinPath(g);
    cout << cost << " " << p << "\n";
    return 0;
}
```

**Jebakan:** update parent saat `==` tanpa kebijakan seri. Membandingkan baris yang salah. `reverse` lupa. 1-indexed vs 0-indexed tercampur.

**Kompleksitas:** sama dengan DP asal plus `O(n)` telusur.

---

## Rolling array

**Teori:** Jika `dp[i]` hanya butuh `dp[i-1]` (dan mungkin `i-2`), simpan satu atau dua baris. Knapsack 0-1: satu array, loop mundur. Unbounded: satu array, loop maju. LCS/edit: dua baris atau satu baris plus `prevDiag`. Grid: satu baris, `j` kiri ke kanan (`dp[j]` = atas, `dp[j-1]` = kiri).

**Kapan:** MLE pada `O(nW)` atau `O(nm)`. **Tidak:** butuh rekonstruksi tabel, atau transisi melihat banyak baris acak.

**STATE:** `cur[j]` mewakili baris `i` kolom `j`; `prev[j]` baris `i-1`.

**TRANSISI:** sama, indeks baris diganti `cur`/`prev`.

**BASIS:** `prev` diisi seperti baris 0.

**Proses angka LCS** `"AB"`, `"B"`:

```
prev = [0, 0]
i=A: cur[0]=0, j=B beda -> max(prev[1]=0, cur[0]=0)=0
swap
i=B: cur[0]=0, j=B sama -> prevDiag+1 = 1
```

Knapsack (2,3) `W=4` mundur: `dp[4]←dp[2]+3` memakai `dp[2]` lama. Maju: `dp[2]=3` lalu `dp[4]=6` (dobel).

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

ll knapsack01_1D(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int s = W; s >= w[i]; s--)
            dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
    return dp[W];
}

int lcsLength_2Row(string s, string t) {
    if (t.size() > s.size()) swap(s, t);
    int n = (int)s.size(), m = (int)t.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++)
            cur[j] = (s[i - 1] == t[j - 1] ? prev[j - 1] + 1 : max(prev[j], cur[j - 1]));
        prev.swap(cur);
    }
    return prev[m];
}

ll houseRobber_O1(const vector<ll>& nums) {
    ll prev2 = 0, prev1 = 0;
    for (ll x : nums) {
        ll cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << knapsack01_1D({3, 2, 4}, {3, 4, 2}, 5) << "\n";
    cout << lcsLength_2Row("ABCBDAB", "BDCABA") << "\n";
    cout << houseRobber_O1({2, 1, 1, 2}) << "\n";
    return 0;
}
```

**Jebakan:** `prev.swap(cur)` lalu `cur` kotor tanpa reset. Satu array LCS menimpa diagonal. Rolling + rekonstruksi. Arah loop knapsack.

**Kompleksitas:** waktu sama. Memori `O(W)`, `O(min(n,m))`, atau `O(1)`.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
const ll INF = 4e18;

int lcsLen(const string& a, const string& b);
int editDistance(const string& a, const string& b);
ll countPathsObstacle(const vector<string>& g);
ll minPathSum(const vector<vector<ll>>& a);
ll stoneMerging(const vector<ll>& a);
ll matrixChain(const vector<ll>& p);
int minPalindromeCuts(const string& s);
ll burstBalloons(const vector<int>& a);
```

Urutan isi range: `len` luar, `l` tengah, `k` dalam.

Grid: padding atau `if` tepi. Sentinel = identitas operator.

String: `a[i-1]` untuk prefiks `i`.

---

## Peta jebakan file ini

| Gejala | Penyebab | Perbaikan |
|---|---|---|
| LCS off-by-one | `a[i]` vs `a[i-1]` | tabel n+1, string 0 |
| Edit terlalu kecil | basis 0 | `dp[i][0]=i` |
| Grid awal 0 | loop menimpa | skip (1,1) |
| Min-path aneh | `#` diisi 0 | pakai INF |
| Range WA | loop `l,r` tanpa len | loop panjang |
| MCM overflow | `int * int * int` | `ll` |
| Rekonstruksi kosong | rolling | simpan tabel / parent |
| SCS / edit putus | `while (i && j)` | `\|\|` |
| Palindrom lambat | cek O(n) per sel | `isPal` O(n²) dulu |
| Burst salah | model "pertama meletus" | "terakhir" + sentinel |

Latihan: AtCoder DP-F (LCS), DP-G bukan string, DP-H grid, DP-I/N slimes; CSES Edit Distance, Grid Paths, Rectangle Cutting (range); LC 72, 1143, 64, 312.

---

## Rectangle cutting

**Teori:** Persegi panjang `a × b` dipotong lurus (horizontal atau vertikal) sampai jadi persegi. Minimalkan potongan. Range DP 2D pada ukuran. Memotong jadi `i×k` dan `i×(j-k)` atau `k×j` dan `(i-k)×j`.

**Kapan:** CSES Rectangle Cutting. **Tidak:** potongan tidak lurus / diagonal.

**STATE:** `dp[i][j]` adalah jumlah potongan minimum untuk mengubah persegi panjang `i × j` menjadi kumpulan persegi.

**TRANSISI:** `dp[i][j] = 1 + min( min_k dp[i][k]+dp[i][j-k], min_k dp[k][j]+dp[i-k][j] )`.

**BASIS:** `dp[i][i] = 0` (sudah persegi).

**Proses angka:** `3 × 5`.

```
dp[1][1]=0
dp[1][j]=j-1   (potong jadi j kotak 1×1)
dp[2][2]=0
dp[2][3]: potong vert 1+2 -> 0+0+1=1? 2×1 dan 2×2:  dp[2][1]+dp[2][2]+1
          dp[2][1] = 1 (satu potong jadi dua 1×1) 
          lebih teliti:
dp[2][1] = dp[1][1]+dp[1][1]+1 = 1
dp[3][5] optimal 3
```

Satu cara: potong 3×5 → 3×3 + 3×2 (1 potong). 3×3 selesai. 3×2 → 2×2 + 1×2 (1). 1×2 → dua 1×1 (1). Total 3.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int rectangleCuts(int a, int b) {
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 1e9));
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            for (int k = 1; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            for (int k = 1; k < i; k++)
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
        }
    return dp[a][b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << rectangleCuts(3, 5) << "\n"; // 3
    cout << rectangleCuts(4, 4) << "\n"; // 0
    return 0;
}
```

**Jebakan:** `dp[i][j]` dan `dp[j][i]` tidak disamakan padahal simetris — boleh, asal keduanya dihitung. `a, b ≤ 500` → `O(a b (a+b))` ≈ `2e8` ketat.

**Kompleksitas:** `O(ab(a+b))` waktu, `O(ab)` memori.

---

## LCS kedua: `"AXYT"` dan `"AYZX"`

**Proses angka:**

```
       "" A Y Z X
    ""  0 0 0 0 0
    A   0 1 1 1 1
    X   0 1 1 1 2
    Y   0 1 2 2 2
    T   0 1 2 2 2
```

Panjang 2. Rekonstruksi dari (4,4): `T≠X`, atas=2 ≥ kiri=2 → naik (3,4) `Y≠X`, kiri 2 < atas? `dp[2][4]=2`, `dp[3][3]=2` — pilih atas (3,3) `Y≠Z`, atas `dp[2][3]=1`, kiri `dp[3][2]=2` → kiri (3,2) `Y==Y` ambil Y, (2,1) `X≠A`, ... ambil A. Salah satu LCS `AY`.

---

## Edit `"sunday"` → `"saturday"`

**Proses angka (ringkas):**

```
sunday
saturday

sisip a, t setelah s; ganti n→r. Jawaban 3.
Basis: sunday -> "" = 6 hapus; "" -> saturday = 8 sisip.
```

Sel `(1,1)` `s==s` → 0. Ini memastikan prefiks `s` gratis.

---

## Grid 2×3 jejak lengkap

```
nilai:
1 2 3
4 5 6

dp jumlah min:
1   3   6
5   8  12

jalur 1-2-3-6 = 12, 1-4-5-6 = 16. Min 12.
Trace dari (1,2): atas 6 vs kiri 8 → atas ke (0,2), kiri ke (0,1), kiri (0,0).
Sel: (0,0)-(0,1)-(0,2)-(1,2)  langkah R,R,D
```

Hitung jalur 2×3 tanpa halangan: `C(3,1)=3` yaitu RR D, RDR, DRR.

Dengan `#` di (0,1):

```
1 # 3
4 5 6

hitung: awal 1, kanan mati, bawah 1.
(1,1)=1 (dari kiri), (0,2)=0, (1,2)=1.
```

---

## LPS dan palindrom substring

**Teori:** Longest palindromic subsequence = LCS(s, reverse(s)). Longest palindromic **substring** adalah range DP boolean + catat panjang, atau expand dari pusat.

**STATE substring:** `dp[l][r]` benar jika `s[l..r]` palindrom.

**TRANSISI:** `s[l]==s[r] && (r-l<2 || dp[l+1][r-1])`.

**BASIS:** `dp[i][i] = true`.

**Proses angka:** `"babad"` → substring `"bab"` atau `"aba"` panjang 3. Subsequence bisa `"bbad`? `"bab"` / `"aba"` / `"bb"` — terpanjang 3 juga di sini. `"bbbab"` subsequence 4 (`bbbb`).

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

string longestPalSubstring(const string& s) {
    int n = (int)s.size(), bestL = 0, bestLen = 1;
    vector<vector<char>> dp(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r] && (len == 2 || dp[l + 1][r - 1])) {
                dp[l][r] = 1;
                if (len > bestLen) {
                    bestLen = len;
                    bestL = l;
                }
            }
        }
    return s.substr(bestL, bestLen);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << longestPalSubstring("babad") << "\n";
    cout << longestPalSubstring("cbbd") << "\n";
    return 0;
}
```

**Jebakan:** mencetak subsequence sebagai substring. Loop tanpa `len`.

**Kompleksitas:** `O(n^2)` waktu dan memori.

---

## Tabel uji file 14

| Soal | Input | Jawaban |
|---|---|---|
| LCS | `ABCBDAB` / `BDCABA` | 4 |
| LCS string | sama | `BCBA` (salah satu) |
| Edit | `kitten` / `sitting` | 3 |
| LCSubstring | `ABABC` / `BABCA` | 4 |
| SCS len | `abac` / `cab` | 5 |
| LPS | `bbbab` | 4 |
| Grid 3×3 jalur | tanpa `#` | 6 |
| Grid `#` tengah | | 2 |
| Min path | `[[1,3,1],[1,5,1],[4,2,1]]` | 7 |
| MCM | p=`10,100,5,20` | 6000 |
| Slimes | `10 20 30` | 90 |
| Pal cuts | `aab` | 1 |
| Burst | `3,1,5` | 35 |
| Rect cut | 3×5 | 3 |

---

Lanjut ke [15 — bitmask, digit, tree, CHT](15-dp-bitmask-digit-tree-optim.md).
