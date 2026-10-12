# 13 — Hemat memori: dua baris, satu baris, dua variabel

[← 12-rekonstruksi](12-rekonstruksi.md) · [README](README.md) · [14-state-lanjut →](14-state-lanjut.md)

Day **153**. Waktu DP biasanya `(banyak state) × (biaya transisi)`. Memori sering bisa dipotong jika `dp[i]` hanya butuh `dp[i-1]` (dan mungkin `i-2`). Analoginya papan tulis: setelah baris baru selesai, baris lama boleh dihapus.

> **Satu kalimat:** gulung dimensi yang tidak lagi dibaca; **jangan** gulung jika masih butuh jejak ([12-rekonstruksi](12-rekonstruksi.md)).

Tiga pola wajib: dua baris (LCS/edit/grid), satu baris knapsack **mundur**, dua variabel Fibonacci.

## Daftar isi

- [Kapan boleh digulung](#kapan-boleh-digulung)
- [Dua baris](#dua-baris)
- [Satu baris knapsack mundur](#satu-baris-knapsack-mundur)
- [Unbounded maju vs 0-1 mundur](#unbounded-maju-vs-0-1-mundur)
- [Dua variabel fib dan robber](#dua-variabel-fib-dan-robber)
- [Grid satu baris](#grid-satu-baris)
- [LCS satu baris plus diagonal](#lcs-satu-baris-plus-diagonal)
- [Menghitung memori](#menghitung-memori)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Kapan boleh digulung

**Teori:** Dimensi `i` bisa digulung jika setiap transisi ke lapisan `i` hanya membaca lapisan `i`, `i-1`, … `i-k` dengan `k` kecil tetap. Jika transisi membaca `dp[j]` untuk `j` acak (LIS `j < i`, range `[l,r]`, bitmask subset sebarang), gulung merusak nilai.

Uji: gambar ketergantungan satu sel. Jika panah hanya ke baris atas dan kiri, dua baris atau satu baris cukup.

**Kapan:** MLE pada `O(nW)` atau `O(nm)`; soal hanya minta nilai akhir. **Tidak:** rekonstruksi, atau `dp[l][r]` range.

**STATE:** `cur[j]` mewakili `dp[i][j]`; `prev[j]` mewakili `dp[i-1][j]`.

**TRANSISI:** rumus sama, ganti indeks lapisan.

**BASIS:** `prev` diisi seperti lapisan 0.

**Proses (table):**

| pola | butuh lapisan | gulung jadi |
|---|---|---|
| fib / tangga | i-1, i-2 | 2 variabel |
| robber | i-1, i-2 | 2 variabel |
| LCS / edit | baris i-1 + kiri | 2 baris atau 1+diag |
| grid kanan-bawah | atas + kiri | 1 baris |
| 0-1 knapsack | item i-1, kapasitas ≤ j | 1 array mundur |
| unbounded knapsack | item yang sama, j lebih kecil | 1 array maju |
| LIS O(n²) | semua j < i | tidak (atau tails beda) |
| range DP | semua subinterval | tidak |

**Kode modular:** fungsi uji ketergantungan tidak perlu; pakai checklist di kepala.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool bolehGulung(bool butuhJejak, int lapisanAcak) {
    return !butuhJejak && lapisanAcak <= 2;
}

int main() {
    FASTIO;
    cout << bolehGulung(false, 1) << ' ' << bolehGulung(true, 1) << '\n';
    return 0;
}
```

**Jebakan:** gulung dulu, baru sadar soal minta barang. LIS dikira "hanya i-1". Range DP `dp[l][r]` bukan baris.

**Kompleksitas:** waktu **tidak** berkurang. Yang berubah hanya memori.

---

## Dua baris

**Teori:** `prev` dan `cur` masing-masing panjang `m+1`. Setelah baris `i` selesai, `swap(prev, cur)`. Analoginya dua ember: isi yang kosong, lalu tukar peran. `vector::swap` O(1) (tukar pointer).

Edit distance: `cur[0] = i` (hapus i huruf). LCS: `cur[0] = 0`.

**Kapan:** LCS/edit `n,m ≤ 4000` nilai saja; grid jika ingin jelas atas vs kiri. **Tidak:** jejak string.

**STATE:** `prev[j] = dp[i-1][j]`, `cur[j] = dp[i][j]`.

**TRANSISI LCS:** `cur[j] = sama ? prev[j-1]+1 : max(prev[j], cur[j-1])`.

**BASIS:** `prev[j] = 0` (LCS) atau `j` (edit).

**Proses (table):** LCS `"AB"` vs `"CB"`.

Awal `prev = [0, 0, 0]`.

Baris A:

| j | huruf | rumus | cur |
|---|---|---|---|
| 0 | — | 0 | 0 |
| 1 | A≠C | max(prev[1]=0, cur[0]=0) | 0 |
| 2 | A≠B | max(0,0) | 0 |

`swap` → `prev = [0,0,0]`.

Baris B:

| j | huruf | rumus | cur |
|---|---|---|---|
| 0 | — | 0 | 0 |
| 1 | B≠C | max(0,0) | 0 |
| 2 | B=B | prev[1]+1 = 1 | 1 |

Jawaban `prev[2] = 1` setelah swap.

Edit `"cat"` / `"cut"` dua baris, setelah i=3: `prev[3] = 1`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lcs2Row(string s, string t) {
    if (t.size() > s.size()) swap(s, t);
    int n = (int)s.size(), m = (int)t.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) cur[j] = prev[j - 1] + 1;
            else cur[j] = max(prev[j], cur[j - 1]);
        }
        prev.swap(cur);
    }
    return prev[m];
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
    FASTIO;
    cout << lcs2Row("ABCD", "ACBD") << '\n';           // 3
    cout << editDistance2Row("kitten", "sitting") << '\n'; // 3
    return 0;
}
```

**Jebakan:** `swap` lalu `cur` masih berisi baris lama; `cur[0]` harus di-set ulang. Membaca `prev[m]` sebelum swap terakhir. Edit: lupa `cur[0]=i`.

**Kompleksitas:** waktu `O(nm)`, memori `O(min(n,m))`.

---

## Satu baris knapsack mundur

**Teori:** 0-1: tiap barang paling sekali. `dp[s]` = nilai max kapasitas `s`. Saat memproses barang `w,v`, kita ingin `dp[s] = max(dp[s], dp[s-w]+v)` memakai **nilai lama** (barang belum diambil). Jika loop `s` dari 0 ke W, `dp[s-w]` sudah di-update barang yang sama → barang dipakai dua kali. Loop **mundur** `s = W .. w` memakai `dp[s-w]` yang masih lama.

Analoginya mengisi formulir dari bawah: kotak atas belum ditimpa.

**Kapan:** 0-1 / bounded yang sudah dipecah, `W ≤ 1e6`, `n*W` waktu lolos, memori `O(W)`. **Tidak:** rekonstruksi himpunan. Unbounded (loop harus maju).

**STATE:** `dp[s]` nilai max memakai barang yang sudah diproses, kapasitas tepat / paling banyak `s`.

**TRANSISI:** `for s=W; s>=w; s--: dp[s] = max(dp[s], dp[s-w]+v)`.

**BASIS:** `dp[0..W] = 0` (nilai; untuk subset-sum boolean, `dp[0]=true`).

**Proses (table):** barang `(w,v) = (2,3)` lalu `(3,4)`, `W=4`.

Awal: `dp = [0, 0, 0, 0, 0]`.

Barang (2,3), mundur:

| s | baca `dp[s-2]` lama | tulis |
|---|---|---|
| 4 | dp[2]=0 | 3 |
| 3 | dp[1]=0 | 3 |
| 2 | dp[0]=0 | 3 |

`dp = [0, 0, 3, 3, 3]`.

Barang (3,4), mundur:

| s | baca | tulis |
|---|---|---|
| 4 | dp[1]=0 → 4; max(3,4)=4 | 4 |
| 3 | dp[0]=0 → 4 | 4 |

`dp = [0, 0, 3, 4, 4]`. Jawaban `dp[4]=4` (ambil barang kedua saja). `(2,3)+(?)` tidak ada sisa 2. Benar.

Jika **maju** pada barang pertama: `s=2` jadi 3, `s=4` baca `dp[2]=3` jadi 6 — barang (2,3) dobel. Itulah dosa loop maju pada 0-1.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll knapsack01_1D(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int s = W; s >= w[i]; s--)
            dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
    return dp[W];
}

int main() {
    FASTIO;
    cout << knapsack01_1D({3, 2, 4}, {3, 4, 2}, 5) << '\n'; // 7
    cout << knapsack01_1D({2, 3}, {3, 4}, 4) << '\n';       // 4
    return 0;
}
```

**Jebakan:** loop maju. `s` bertipe `size_t` mundur underflow. Mencoba rekonstruksi dari satu array. `W=0` atau `w[i]=0` (loop tak terbatas jika tidak dijaga).

**Kompleksitas:** `O(nW)` waktu, `O(W)` memori.

---

## Unbounded maju vs 0-1 mundur

**Teori:** Unbounded (koin, stok tak terbatas) **ingin** memakai update yang sama: `dp[s] += dp[s-coin]` atau `min(dp[s], dp[s-coin]+1)` dengan `s` menaik. Satu array, loop maju. Mencampur arah = WA diam (angka "hampir masuk akal").

**Kapan:** lihat kata "unlimited" / "each item once". **Tidak:** menebak arah dari kebiasaan.

**STATE:** sama `dp[s]`.

**TRANSISI:** 0-1 mundur; unbounded maju; kombinasi (urutan koin luar) vs permutasi (kapasitas luar) — file [04-coin-unbounded](04-coin-unbounded.md).

**BASIS:** `dp[0]=0` (min koin) atau `dp[0]=1` (banyak cara).

**Proses (table):** koin `{1,2}`, jumlah 3, **banyak kombinasi** (urutan tidak dihitung).

Loop koin luar, `s` maju:

| setelah koin | dp[0..3] |
|---|---|
| awal | 1 0 0 0 |
| +1 | 1 1 1 1 |
| +2 | 1 1 2 2 |

`dp[3]=2` yaitu `{1,1,1}` dan `{1,2}`.

0-1 dengan barang `{1,2}` (masing-masing sekali): mundur, `dp[3]` hanya 1 cara jika subset-sum count, atau nilai sesuai `v`.

**Kode modular:**

```cpp
ll unboundedMinCoins(const vector<int>& c, int T) {
    const ll INF = 4e18;
    vector<ll> dp(T + 1, INF);
    dp[0] = 0;
    for (int x : c)
        for (int s = x; s <= T; s++)
            if (dp[s - x] < INF) dp[s] = min(dp[s], dp[s - x] + 1);
    return dp[T] >= INF ? -1 : dp[T];
}

ll knapsack01_1D(const vector<int>& w, const vector<ll>& v, int W);
```

**Jebakan:** copy-paste arah dari soal kemarin. Min-koin 0-1 vs unbounded tertukar.

**Kompleksitas:** sama `O(nT)` / `O(nW)`.

---

## Dua variabel fib dan robber

**Teori:** Jika hanya `i-1` dan `i-2`, dua skalar cukup. Fibonacci: `dua, satu = n-2, n-1`. Robber: `prev2 = dp[i-2]`, `prev1 = dp[i-1]`. Analoginya mengingat dua langkah kaki, bukan seluruh jalan.

Urutan assignment wajib: hitung `cur`, baru geser `prev2 = prev1`, `prev1 = cur`. Menimpa `prev1` dulu = kehilangan `dp[i-1]`.

**Kapan:** fib, tangga, robber nilai saja, frog 2-lompat. **Tidak:** frog k-lompat `k>2` tanpa deque; jejak rumah.

**STATE:** `prev1` = jawaban sampai i-1, `prev2` sampai i-2.

**TRANSISI robber:** `cur = max(prev1, prev2 + a[i])`.

**BASIS:** `prev2 = 0`, `prev1 = 0` sebelum loop (rumah belum ada), atau inisialisasi dua rumah pertama secara eksplisit.

**Proses (table):** fib `n=6`.

| i | dua | satu | kini |
|---|---|---|---|
| 2 | 0 | 1 | 1 |
| 3 | 1 | 1 | 2 |
| 4 | 1 | 2 | 3 |
| 5 | 2 | 3 | 5 |
| 6 | 3 | 5 | 8 |

Robber `[2,7,9,3,1]`:

| rumah | prev2 | prev1 | cur = max(prev1, prev2+x) |
|---|---|---|---|
| 2 | 0 | 0 | 2 |
| 7 | 0 | 2 | 7 |
| 9 | 2 | 7 | 11 |
| 3 | 7 | 11 | 11 |
| 1 | 11 | 11 | 12 |

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

ll fib2var(int n) {
    if (n <= 1) return n;
    ll dua = 0, satu = 1;
    for (int i = 2; i <= n; i++) {
        ll kini = (dua + satu) % MOD;
        dua = satu;
        satu = kini;
    }
    return satu;
}

ll houseRobber2var(const vector<ll>& a) {
    ll prev2 = 0, prev1 = 0;
    for (ll x : a) {
        ll cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

ll tangga2var(int n) {
    if (n <= 1) return 1;
    ll a = 1, b = 1; // cara[0], cara[1]
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    FASTIO;
    cout << fib2var(10) << '\n';
    cout << houseRobber2var({2, 7, 9, 3, 1}) << '\n'; // 12
    cout << tangga2var(5) << '\n';                    // 8
    return 0;
}
```

**Jebakan:** `satu = dua + satu` lalu `dua = satu` memakai nilai baru. Robber inisialisasi `prev1 = a[0]` dan loop dari 0 lagi (rumah 0 dobel) — pilih satu gaya. Jejak setelah 2 var: mustahil tanpa array `take`.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori.

---

## Grid satu baris

**Teori:** `dp[j]` saat memproses baris `i`: sebelum update, `dp[j]` adalah **atas** (baris `i-1`); `dp[j-1]` yang baru adalah **kiri**. Loop `j` kiri ke kanan. Analoginya mengecat pagar: kotak kiri baru kering, kotak ini masih warna lama (= atas).

Halangan: set `dp[j]=0` atau `INF` lalu lanjut. Jangan tambah kiri ke sel batu.

**Kapan:** unique paths / min path, nilai saja. **Tidak:** 3 arah falling yang butuh `j-1` dan `j+1` baris atas — satu baris menimpa `j-1` atas; pakai `prev` terpisah atau salin baris.

**STATE:** `dp[j]` = jawaban sel `(i,j)` setelah update.

**TRANSISI hitung:** `dp[j] = (dp[j] + dp[j-1]) % MOD` jika bukan batu.

**TRANSISI min:** `dp[j] = a[i][j] + min(dp[j], dp[j-1])` dengan tepi `INF`.

**BASIS:** baris 0 diisi prefiks.

**Proses (table):** unique 3×3.

Awal `dp = [1, 0, 0]` lalu baris 0: `j=1: 0+1=1`, `j=2: 0+1=1` → `[1,1,1]`.

Baris 1: `j=0` tetap 1 (atas); `j=1: 1+1=2`; `j=2: 1+2=3` → `[1,2,3]`.

Baris 2: `[1,3,6]`.

Min path `[[1,3,1],[1,5,1],[4,2,1]]`:

Setelah baris 0: `[1, 4, 5]`.

Baris 1: `j=0: 1+1=2`; `j=1: 5+min(2,2)=7`; `j=2: 1+min(7,5)=6` → `[2,7,6]`.

Baris 2: `[6,8,7]`.

**Kode modular:**

```cpp
ll uniquePaths1D(int R, int C) {
    vector<ll> dp(C, 0);
    dp[0] = 1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (j > 0) dp[j] = (dp[j] + dp[j - 1]) % MOD;
    return dp[C - 1];
}

ll minPathSum1D(const vector<vector<ll>>& a) {
    int R = (int)a.size(), C = (int)a[0].size();
    const ll INF = 4e18;
    vector<ll> dp(C, INF);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i == 0 && j == 0) dp[j] = a[i][j];
            else {
                ll up = dp[j];
                ll left = (j > 0 ? dp[j - 1] : INF);
                dp[j] = a[i][j] + min(up, left);
            }
        }
    }
    return dp[C - 1];
}
```

**Jebakan:** baris 0 tidak diinisialisasi prefiks, `dp[j]` atas masih `INF`/`0` salah. Falling 3 arah memakai satu array tanpa salin.

**Kompleksitas:** `O(RC)` waktu, `O(C)` memori.

---

## LCS satu baris plus diagonal

**Teori:** Satu array `dp[j]`. Saat `j` menaik, `dp[j]` lama = atas, `dp[j-1]` baru = kiri, tetapi diagonal adalah `dp[j-1]` **lama**. Simpan `prevDiag` sebelum menimpa. Analoginya kamu butuh foto sudut kiri-atas sebelum mengecat.

**Kapan:** MLE ketat, hanya panjang. **Tidak:** rekonstruksi.

**STATE:** `dp[j]` + `prevDiag`.

**TRANSISI:**

```
simpan = dp[j]          // atas, jadi diagonal untuk j+1
jika sama: dp[j] = prevDiag + 1
else: dp[j] = max(dp[j], dp[j-1])
prevDiag = simpan
```

**BASIS:** `dp` nol. `prevDiag = 0` di awal setiap baris (`dp[0]` lama).

**Proses (table):** `"AB"` vs `"B"`.

`dp=[0,0]`.

Baris A, `prevDiag=0`: `j=1` A≠B, max(0,0)=0, `prevDiag` jadi 0 (simpan atas).

Baris B, `prevDiag=0`: `j=1` B=B, `dp[1]=0+1=1`.

**Kode modular:**

```cpp
int lcs1Row(string a, string b) {
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
```

**Jebakan:** `prevDiag` tidak di-reset tiap baris. Menimpa dulu, baru ingat diagonal.

**Kompleksitas:** `O(nm)` waktu, `O(min(n,m))` memori.

---

## Menghitung memori

**Teori:** `vector<vector<int>>(n+1, vector<int>(m+1))` ≈ `4(n+1)(m+1)` byte plus overhead per baris. `n=m=5000` ≈ 100 MB — sering MLE. Dua baris `2*5001*4` ≈ 40 KB. Knapsack `n=100, W=1e6` tabel 2D ≈ 800 MB; 1D ≈ 8 MB (`ll`).

Aturan kasar 128 MB: `state * 8 byte < 1e8`.

**Kapan:** sebelum mengetik `vector<vector<ll>>(1<<20, n)`. **Tidak:** mengoptimasi memori soal `n=100` yang sudah 80 KB.

**STATE:** tidak ada.

**TRANSISI:** tidak ada.

**BASIS:** tidak ada.

**Proses (table):**

| tabel | n | byte kira-kira | lolos 128MB? |
|---|---|---|---|
| LCS int 2D | 3000 | 36 MB | ya |
| LCS int 2D | 8000 | 256 MB | tidak |
| LCS 2 baris | 8000 | 64 KB | ya |
| knapsack ll 2D | n=200 W=1e5 | 160 MB | tidak |
| knapsack ll 1D | W=1e5 | 800 KB | ya |
| TSP ll `2^n * n` | n=20 | 160 MB | rapuh |
| range ll `n²` | 400 | 1.3 MB | ya |
| range ll `n²` | 2000 | 32 MB | ya, waktunya yang mati |

**Kode modular:**

```cpp
ll bytePerkiraan(ll baris, ll kolom, ll lebar) {
    return baris * kolom * lebar;
}
```

**Jebakan:** lupa overhead `vector` per baris (pointer). `bool` di `vector<bool>` khusus, bukan array bit portabel untuk DP.

**Kompleksitas:** hitung O(1), keputusan desain O(otak).

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll MOD = 1000000007LL;

int lcs2Row(string s, string t);
int editDistance2Row(string a, string b);
ll knapsack01_1D(const vector<int>& w, const vector<ll>& v, int W);
ll fib2var(int n);
ll houseRobber2var(const vector<ll>& a);
ll uniquePaths1D(int R, int C);
int lcs1Row(string a, string b);

int main() {
    FASTIO;
    cout << knapsack01_1D({3, 2, 4}, {3, 4, 2}, 5) << '\n';
    cout << fib2var(10) << ' ' << houseRobber2var({2, 1, 1, 2}) << '\n';
    return 0;
}
```

Urutan keputusan:

```
1. Butuh jejak? → jangan gulung
2. Ketergantungan berapa lapisan?
3. 0-1 atau unbounded? → arah loop
4. Hitung byte
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| knapsack terlalu besar | loop maju 0-1 | mundur |
| koin terlalu kecil | loop mundur unbounded | maju |
| LCS 0 setelah swap | `cur` kotor / `cur[0]` | reset |
| LCS 1D salah | diagonal tertimpa | `prevDiag` |
| fib 1,1,2,4 | `satu` ditimpa dulu | `kini` sementara |
| robber 2 var + idx | tidak ada `take` | array O(n) |
| falling 3 arah rusak | satu baris | salin `prev` |
| MLE tetap | gulung dimensi yang salah | hitung byte lagi |
| WA setelah hemat | soal minta path | kembali ke tabel |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `lcs2Row` | ABCD / ACBD | 3 |
| `lcs1Row` | sama | 3 |
| `editDistance2Row` | kitten / sitting | 3 |
| `knapsack01_1D` | w 3,2,4 v 3,4,2 W=5 | 7 |
| `knapsack01_1D` | w 2,3 v 3,4 W=4 | 4 |
| `unboundedMinCoins` | {1,2} target 3 | 2 |
| `fib2var` | 10 | 55 |
| `houseRobber2var` | 2,7,9,3,1 | 12 |
| `houseRobber2var` | 2,1,1,2 | 4 |
| `tangga2var` | 5 | 8 |
| `uniquePaths1D` | 3×3 | 6 |
| `minPathSum1D` | [[1,3,1],[1,5,1],[4,2,1]] | 7 |

Day 154 di ComprogLearning adalah review, bukan teori baru. Lanjut desain state tambahan di [14-state-lanjut](14-state-lanjut.md).
