# 12 — Rekonstruksi: pointer, knapsack, LCS, robber

[← 11-range](11-range.md) · [README](README.md) · [13-memori →](13-memori.md)

Day **152**. Nilai optimal ≠ objek optimal. Soal sering minta barang, string, atau indeks rumah — bukan hanya angka. Dua cara: (1) simpan `prev` / `pick` saat transisi, (2) bandingkan ulang `dp` saat mundur.

> **Satu kalimat:** setiap kali kandidat **lebih baik**, catat dari mana ia datang; di akhir, jalan mundur dari jawaban sampai basis, lalu `reverse`.

Rolling array hampir selalu **menghancurkan** rekonstruksi. Jika butuh jejak, simpan tabel penuh atau pointer terpisah ([13-memori](13-memori.md)).

## Daftar isi

- [Dua gaya jejak](#dua-gaya-jejak)
- [Kebijakan seri](#kebijakan-seri)
- [Rekonstruksi knapsack 0-1](#rekonstruksi-knapsack-0-1)
- [Rekonstruksi LCS](#rekonstruksi-lcs)
- [Rekonstruksi house robber](#rekonstruksi-house-robber)
- [Rekonstruksi LIS](#rekonstruksi-lis)
- [Rekonstruksi grid](#rekonstruksi-grid)
- [Rekonstruksi MCM](#rekonstruksi-mcm)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Dua gaya jejak

**Teori:** Transisi `dp[s] = gabung(dp[t] ⋆ pilihan)` menyembunyikan `t` dan pilihan. Gaya A menulis `prev[s] = t` saat relaksasi. Gaya B tidak menulis apa-apa, lalu saat mundur menguji "apakah `dp[s]` bisa berasal dari `t`?". Analoginya: A = meninggalkan peta; B = menelusuri semua jalan yang cocok dengan jarak tempuh.

| | gaya A pointer | gaya B banding ulang |
|---|---|---|
| memori ekstra | `O(state)` pointer | 0 |
| butuh tabel `dp` | tidak wajib jika pointer lengkap | ya, utuh |
| tie-break | saat update (`<` vs `<=`) | saat tes mundur |
| rolling | pointer harus hidup | hampir mustahil |

**Kapan A:** state 1D (robber, LIS), atau ingin cetak tanpa menyimpan `dp` 2D. **Kapan B:** knapsack 2D sudah ada, banding `dp[i][w] != dp[i-1][w]` murah. **Tidak:** keduanya sekaligus tanpa alasan — membingungkan.

**STATE:** sama dengan DP asal. Tambahan `prev[s]` = pendahulu yang menghasilkan `dp[s]`, atau `-1` jika basis.

**TRANSISI:** jika `kandidat` **lebih baik** dari `dp[s]`, set `dp[s]` dan `prev[s]`.

**BASIS:** `prev[basis] = -1`.

**Proses (table):** fibonacci jejak "dari mana" untuk `n=5` (hanya ilustrasi, bukan soal).

| i | dp | prev (pilih i-1 jika seri) |
|---|---|---|
| 0 | 0 | -1 |
| 1 | 1 | -1 |
| 2 | 1 | 1 |
| 3 | 2 | 2 |
| 4 | 3 | 3 |
| 5 | 5 | 4 |

Jejak 5→4→3→2→1. Untuk fib ini sepele; pola yang sama dipakai robber.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> jalanMundur(const vector<int>& prev, int start) {
    vector<int> path;
    for (int cur = start; cur != -1; cur = prev[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    FASTIO;
    vector<int> prev = {-1, -1, 1, 2, 3, 4};
    for (int x : jalanMundur(prev, 5)) cout << x << ' ';
    cout << '\n';
    return 0;
}
```

**Jebakan:** update pointer saat `==` tanpa kebijakan. Lupa `reverse`. Mencampur 0-index barang dengan 1-index output.

**Kompleksitas:** jejak `O(panjang jawaban)` setelah DP selesai.

---

## Kebijakan seri

**Teori:** Banyak state punya beberapa pendahulu dengan nilai sama. Tanpa aturan, dua compiler / dua urutan loop mencetak objek berbeda — keduanya optimal, tetapi checker leksikografis bisa WA. Tetapkan **sebelum** mengetik: indeks terkecil, leksikografis terkecil, atau "yang pertama ditemukan".

Aturan praktis:

```
lebih baik ketat  (<  atau >)  : jejak stabil, pertama menang
lebih baik longgar (<= atau >=): jejak diganti ke yang baru
```

Untuk string grid `D < R` secara leksikografis: saat seri, pilih `D` dulu.

**Kapan:** soal minta "any" — pilih satu dan tetap. Soal minta leksikografis — banding karakter, bukan hanya nilai. **Tidak:** mengacak saat seri di kontes.

**STATE:** tidak menambah dimensi jika tie-break bisa diputus saat jejak. Jika "semua solusi", itu enumerasi, bukan satu `prev`.

**TRANSISI:** `if (cand < dp[s] || (cand == dp[s] && lebihBaik(pilihan)))`.

**BASIS:** pointer `-1`.

**Proses (table):** LCS `ABCD`/`ACBD`, panjang 3, dua string.

| kebijakan mundur saat atas==kiri | hasil |
|---|---|
| atas dulu | `ABD` |
| kiri dulu | `ACD` |

Keduanya panjang 3. Checker "any" menerima keduanya. Checker string tepat harus mengikuti statement.

**Kode modular:**

```cpp
bool updateMin(ll& dp, ll cand, int& prev, int dari, bool longgar) {
    if (cand < dp || (longgar && cand == dp)) {
        dp = cand;
        prev = dari;
        return true;
    }
    return false;
}
```

**Jebakan:** `<=` di knapsack membuat barang ke-`i` selalu diambil saat seri — himpunan berubah, nilai sama. Untuk "indeks terkecil" biasanya `>` ketat saat isi dari kiri.

**Kompleksitas:** O(1) per relaksasi.

---

## Rekonstruksi knapsack 0-1

**Teori:** `dp[i][w]` nilai maksimum memakai item `0..i-1` dengan kapasitas `w` ([05-01-knapsack](05-01-knapsack.md)). Mundur dari `(n, W)`: jika `dp[i][w] != dp[i-1][w]`, item `i-1` **wajib** diambil (satu-satunya cara nilai naik), kurangi `w` sebesar `w[i-1]`. Jika sama, item itu dilewati.

Ini gaya B. Gaya A: `pick[i][w] = true` saat cabang ambil menang.

**Kapan:** soal minta daftar barang. **Tidak:** hanya nilai — jangan bangun vektor.

**STATE:** `dp[i][j]` nilai max. `chosen` terkumpul saat mundur.

**TRANSISI mundur:**

```
jika dp[i][cur] != dp[i-1][cur]: ambil i, cur -= w[i-1]
else: skip
```

**BASIS mundur:** `i = 0` atau `cur` tidak cukup untuk sisa yang diambil.

**Proses (table):** `w = [3, 2, 4]`, `v = [3, 4, 2]`, `W = 5`.

Baris = setelah mempertimbangkan item 0..i-1.

| i \\ w | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 (3,3) | 0 | 0 | 0 | 3 | 3 | 3 |
| 2 (2,4) | 0 | 0 | 4 | 4 | 4 | **7** |
| 3 (4,2) | 0 | 0 | 4 | 4 | 4 | 7 |

Mundur dari `(3,5)`:

| i | dp[i][5] vs dp[i-1][5] | keputusan | cur |
|---|---|---|---|
| 3 | 7 == 7 | skip item 2 (berat 4) | 5 |
| 2 | 7 != 3 | ambil item 1 (berat 2, nilai 4) | 3 |
| 1 | 3 != 0 | ambil item 0 (berat 3, nilai 3) | 0 |

Barang 0-based: `{0, 1}`. Nilai 3+4=7. Item 2 tidak muat bersama mereka.

Contoh kedua: `w=[2,2]`, `v=[3,3]`, `W=2`. Seri dua barang. Dengan banding `!=` dan loop `i` menurun, yang diambil adalah barang **terakhir** yang menaikkan nilai (indeks 1), karena `dp[2][2]=3 != dp[1][2]=3`? Hati-hati: `dp[1][2]=3`, `dp[2][2]=max(3, dp[1][0]+3)=3`, sama → skip item 1, ambil item 0. Jadi `!=` memilih barang **paling kiri** yang masih menjelaskan nilai. Jika ingin barang kanan, pakai pointer saat `>=`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<ll, vector<int>> reconstructKnapsack(const vector<ll>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - (int)w[i - 1]] + v[i - 1]);
        }
    }
    vector<int> chosen;
    int cur = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][cur] != dp[i - 1][cur]) {
            chosen.push_back(i - 1); // 0-based
            cur -= (int)w[i - 1];
        }
    }
    reverse(chosen.begin(), chosen.end());
    return {dp[n][W], chosen};
}

int main() {
    FASTIO;
    auto [val, idx] = reconstructKnapsack({3, 2, 4}, {3, 4, 2}, 5);
    cout << val;
    for (int i : idx) cout << ' ' << i;
    cout << '\n'; // 7 0 1
    return 0;
}
```

**Jebakan:**

1. Membandingkan `dp[i][cur]` dengan `dp[i-1][cur - w]` tanpa cek skip — logika terbalik.
2. `chosen.push_back(i)` padahal item 0-based adalah `i-1`.
3. Satu array knapsack mundur: baris `i-1` sudah hilang, `!=` mustahil.
4. `cur` negatif jika `w` tidak dikurangi saat ambil.

**Kompleksitas:** isi `O(nW)`, jejak `O(n)`.

---

## Rekonstruksi LCS

**Teori:** Sudah di [09-lcs-edit](09-lcs-edit.md). Diulang di sini sebagai pola Day 152: tabel 2D + jejak diagonal saat huruf sama.

**Kapan:** soal minta string LCS / SCS. **Tidak:** hanya panjang — `lcs()` cukup.

**STATE:** `dp[i][j]` panjang LCS prefiks.

**TRANSISI mundur:** sama → ambil huruf, diagonal; beda → atas jika `dp[i-1][j] >= dp[i][j-1]`, else kiri.

**BASIS mundur:** `i==0` atau `j==0`.

**Proses (table):** `ABCD` / `ACBD`, kebijakan atas dulu.

| `(i,j)` | a,b | aksi | stack huruf |
|---|---|---|---|
| 4,4 | D D | ambil | D |
| 3,3 | C B | atas=kiri=2, atas | D |
| 2,3 | B B | ambil | BD |
| 1,2 | A C | kiri lebih besar | BD |
| 1,1 | A A | ambil | BDA |
| reverse |  |  | ABD |

**Kode modular:**

```cpp
string reconstructLCS(const string& a, const string& b) {
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
```

**Jebakan:** mengambil huruf saat beda (itu SCS). Lupa reverse. Edit distance memakai `||` bukan `&&` karena sisa hapus/sisip.

**Kompleksitas:** `O(nm) + O(n+m)`.

---

## Rekonstruksi house robber

**Teori:** `dp[i]` = uang maksimum pada prefiks rumah `0..i` ([03-linear-1d](03-linear-1d.md)). Transisi: `max(dp[i-1], dp[i-2] + a[i])` — skip rumah `i` atau ambil. Pointer: `prev[i] = i-1` (skip) atau `i-2` (ambil). Saat mundur, jika `prev[i] == i-2` (atau `dp[i] == dp[i-2]+a[i]` dan bukan `dp[i-1]`), rumah `i` masuk.

Hati-hati seri: `dp[i-1] == dp[i-2]+a[i]`. Kebijakan "lebih suka skip" memakai `>` ketat pada cabang ambil.

**Kapan:** minta indeks rumah. **Tidak:** hanya angka.

**STATE:** `dp[i]` max sampai `i` (rumah `i` boleh dipakai atau tidak). Ini definisi **sampai i**, jadi jawaban `dp[n-1]`, jejak dari `n-1`.

**TRANSISI:**

```
skip = dp[i-1]
ambil = (i>=2 ? dp[i-2] : 0) + a[i]
jika ambil > skip: dp[i]=ambil, take[i]=true
else: dp[i]=skip, take[i]=false
```

**BASIS:** `dp[0] = a[0]`, `take[0] = true` jika `a[0] > 0` (atau selalu true jika nilai 0 tidak peduli). Satu rumah negatif: jangan ambil.

**Proses (table):** `a = [2, 7, 9, 3, 1]`.

| i | a[i] | skip | ambil | dp | take |
|---|---|---|---|---|---|
| 0 | 2 | — | 2 | 2 | 1 |
| 1 | 7 | 2 | 7 | 7 | 1 |
| 2 | 9 | 7 | 2+9=11 | 11 | 1 |
| 3 | 3 | 11 | 7+3=10 | 11 | 0 |
| 4 | 1 | 11 | 11+1=12 | 12 | 1 |

Mundur dari 4: take → ambil rumah 4, lompat ke 2. take → ambil rumah 2, lompat ke 0. take → ambil rumah 0. Rumah `{0,2,4}`, nilai `2+9+1=12`. Rumah 1 dan 3 dilewati.

`[2, 1, 1, 2]`:

| i | dp | take |
|---|---|---|
| 0 | 2 | 1 |
| 1 | 2 | 0 (skip, 1<2) |
| 2 | 3 | 1 (2+1) |
| 3 | 4 | 1 (2+2) |

Mundur: take 3 → ke 1; take 1? `dp[1]=2` dari skip, bukan ambil. Dari 1 skip → 0, take 0. Rumah `{0,3}` nilai 4. Alternatif `{0,2}` = 3 lebih kecil; `{1,3}` = 3 lebih kecil.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<ll, vector<int>> reconstructRobber(const vector<ll>& a) {
    int n = (int)a.size();
    if (n == 0) return {0, {}};
    vector<ll> dp(n, 0);
    vector<char> take(n, 0);
    dp[0] = max(0LL, a[0]);
    take[0] = (a[0] > 0);
    if (n == 1) {
        vector<int> idx;
        if (take[0]) idx.push_back(0);
        return {dp[0], idx};
    }
    if (a[1] > dp[0]) {
        dp[1] = a[1];
        take[1] = 1;
    } else {
        dp[1] = dp[0];
        take[1] = 0;
    }
    for (int i = 2; i < n; i++) {
        ll skip = dp[i - 1];
        ll ambil = dp[i - 2] + a[i];
        if (ambil > skip) {
            dp[i] = ambil;
            take[i] = 1;
        } else {
            dp[i] = skip;
            take[i] = 0;
        }
    }
    vector<int> idx;
    for (int i = n - 1; i >= 0; ) {
        if (take[i]) {
            idx.push_back(i);
            i -= 2;
        } else i -= 1;
    }
    reverse(idx.begin(), idx.end());
    return {dp[n - 1], idx};
}

int main() {
    FASTIO;
    auto [v, idx] = reconstructRobber({2, 7, 9, 3, 1});
    cout << v;
    for (int i : idx) cout << ' ' << i;
    cout << '\n'; // 12 0 2 4
    return 0;
}
```

**Jebakan:** definisi `dp[i]` "berakhir di i" lalu menjawab `dp[n-1]` tanpa `max` seluruh `dp`. Saat skip, mundur `i-2` (salah). Dua variabel rolling tanpa `take[]` — jejak hilang.

**Kompleksitas:** `O(n)` waktu dan memori.

---

## Rekonstruksi LIS

**Teori:** `dp[i]` = panjang LIS yang **berakhir tepat di i**. Jawaban adalah `max dp[i]`, jejak dari `arg max`. `parent[i] = j` saat `a[j] < a[i]` dan `dp[j]+1` lebih baik. Ini definisi "berakhir di i" — jangan cetak dari `n-1` kecuali ekor kebetulan di situ.

**Kapan:** minta salah satu LIS. **Tidak:** hanya panjang O(n log n) tails tanpa `parent` tambahan.

**STATE:** `dp[i]`, `parent[i]`.

**TRANSISI:** `j < i`, `a[j] < a[i]`, `dp[j]+1 > dp[i]` → update + parent.

**BASIS:** `dp[i]=1`, `parent[i]=-1`.

**Proses (table):** `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

| i | a | dp | parent |
|---|---|---|---|
| 0 | 10 | 1 | -1 |
| 1 | 9 | 1 | -1 |
| 2 | 2 | 1 | -1 |
| 3 | 5 | 2 | 2 |
| 4 | 3 | 2 | 2 |
| 5 | 7 | 3 | 3 atau 4 |
| 6 | 101 | 4 | 5 |
| 7 | 18 | 4 | 5 |

`best_idx = 6` atau 7. Jejak 6→5→3→2: `2,5,7,101`.

**Kode modular:**

```cpp
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
```

**Jebakan:** mencetak dari `n-1`. `parent` menyimpan nilai `a[j]` bukan indeks. Lupa reverse.

**Kompleksitas:** `O(n²) + O(n)`.

---

## Rekonstruksi grid

**Teori:** Min path sum: dari tujuan, banding atas vs kiri (jika DP diisi dari start), atau bawah vs kanan (jika suffix DP dari tujuan). Suffix enak untuk leksikografis `D < R`: dari `(0,0)` pilih `D` jika `dp[r][c] == a[r][c] + dp[r+1][c]`.

**Kapan:** minta jalur `DDRR...`. **Tidak:** hanya angka.

**STATE:** tabel `dp` biaya. String `path` terkumpul maju atau mundur.

**TRANSISI mundur** (prefix DP): jika `i==0` hanya kiri; `j==0` hanya atas; else pilih tetangga yang `dp` lebih kecil (atau sesuai tie-break).

**BASIS:** sampai `(0,0)`.

**Proses (table):** grid

```
1 2 3
4 5 6
```

`dp` min:

```
1  3  6
5  8 12
```

Dari (1,2): atas 6 vs kiri 8 → atas (0,2) → kiri (0,1) → kiri (0,0). Sel `(0,0)-(0,1)-(0,2)-(1,2)`. Langkah maju: R,R,D.

**Kode modular:**

```cpp
pair<ll, string> reconstructGridMin(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    const ll INF = 4e18;
    vector<vector<ll>> dp(R, vector<ll>(C, INF));
    dp[0][0] = a[0][0];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) continue;
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i][j]);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + a[i][j]);
        }
    string path;
    int i = R - 1, j = C - 1;
    while (i > 0 || j > 0) {
        if (i == 0) {
            path.push_back('R');
            j--;
        } else if (j == 0) {
            path.push_back('D');
            i--;
        } else if (dp[i - 1][j] <= dp[i][j - 1]) {
            path.push_back('D');
            i--;
        } else {
            path.push_back('R');
            j--;
        }
    }
    reverse(path.begin(), path.end());
    return {dp[R - 1][C - 1], path};
}
```

**Jebakan:** `while (i && j)`. Membandingkan `dp` setelah menambah `a` dua kali. Rolling 1 baris lalu diminta path.

**Kompleksitas:** `O(RC)`.

---

## Rekonstruksi MCM

**Teori:** `split[l][r] = k` terbaik. Bangun string kurung rekursif. Pola yang sama untuk stone (urutan gabung) dan burst (urutan letus terbalik: `k` terakhir dulu).

**Kapan:** minta ekspresi. **Tidak:** hanya biaya.

**STATE:** `split[l][r]`.

**TRANSISI:** saat `cost < dp[l][r]`, tulis `k`.

**BASIS:** `l==r` cetak `A{l+1}`.

**Proses (table):** `p=[10,100,5,20]`, `split[0][2]=1` → `(A1 x A2) x A3`.

**Kode modular:** `mcmParens` di [11-range](11-range.md).

```cpp
string bangunKurung(const vector<vector<int>>& split, int l, int r) {
    if (l == r) return "A" + to_string(l + 1);
    int k = split[l][r];
    return "(" + bangunKurung(split, l, k) + " x " + bangunKurung(split, k + 1, r) + ")";
}
```

**Jebakan:** `split` tidak diisi saat `n=2` (hanya satu `k=l`). Recursion tanpa basis.

**Kompleksitas:** bangun `O(n)` setelah `O(n³)`.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<ll, vector<int>> reconstructKnapsack(const vector<ll>& w, const vector<ll>& v, int W);
string reconstructLCS(const string& a, const string& b);
pair<ll, vector<int>> reconstructRobber(const vector<ll>& a);
pair<int, vector<int>> reconstructLIS(const vector<int>& a);
pair<ll, string> reconstructGridMin(const vector<vector<ll>>& a);

int main() {
    FASTIO;
    auto [val, idx] = reconstructKnapsack({3, 2, 4}, {3, 4, 2}, 5);
    cout << val << '\n';
    cout << reconstructLCS("ABCD", "ACBD") << '\n';
    auto [uang, rumah] = reconstructRobber({2, 7, 9, 3, 1});
    cout << uang << '\n';
    return 0;
}
```

Checklist jejak:

```
1. Definisi dp: sampai i  atau  berakhir di i?
2. Pointer saat <   atau banding ulang?
3. Tie-break tertulis
4. reverse
5. Jangan rolling
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| knapsack kosong | banding baris salah | `dp[i]!=dp[i-1]` lalu kurangi w |
| knapsack indeks +1 | `push(i)` | `push(i-1)` |
| LCS terbalik | lupa reverse | `reverse` |
| LCS = SCS | ambil huruf saat beda | hanya diagonal |
| robber rumah bersebelahan | mundur selalu `i-1` | jika take, `i-2` |
| LIS dari ekor array | `berakhir di n-1` | `arg max dp` |
| grid putus di tepi | `while(i&&j)` | `\|\|` |
| path aneh setelah hemat memori | rolling | tabel / parent |
| dua output beda di dua mesin | `<=` tidak disepakati | kebijakan ketat |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| knapsack | w 3,2,4 v 3,4,2 W=5 | nilai 7, idx 0 1 |
| LCS | ABCD / ACBD | ABD (atas dulu) |
| robber | 2,7,9,3,1 | 12, rumah 0 2 4 |
| robber | 2,1,1,2 | 4, rumah 0 3 |
| LIS | 10 9 2 5 3 7 101 18 | 4, 2 5 7 101 |
| grid min | `[[1,2,3],[4,5,6]]` | 12, RRD |
| MCM kurung | p 10 100 5 20 | 6000, `(A1 x A2) x A3` |

Day 152 selesai jika kamu bisa menjelaskan **satu kalimat** mengapa pointer di-set, lalu menelusuri tabel di kertas. Lanjut hemat memori di [13-memori](13-memori.md) — ingat: hemat dan jejak bertolak belakang.
