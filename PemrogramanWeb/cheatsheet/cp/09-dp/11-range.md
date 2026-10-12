# 11 — Range DP: MCM, balon, palindrom, batu

[← 10-grid](10-grid.md) · [README](README.md) · [12-rekonstruksi →](12-rekonstruksi.md)

Day **151**. State bukan prefiks atau sel, melainkan **interval** `[l, r]`. Operasi terakhir selalu menggabung dua blok bersebelahan. Karena anak lebih pendek dari induk, loop **wajib menurut panjang**.

> **Satu kalimat:** `dp[l][r]` = jawaban optimal untuk segmen `l..r`; pecah di `k`, bayar biaya gabung.

Kalau elemen tidak wajib kontigu, ini bukan range DP — itu knapsack atau LIS ([05](05-01-knapsack.md), [08](08-lis.md)).

## Daftar isi

- [Kerangka range](#kerangka-range)
- [Mengapa loop panjang](#mengapa-loop-panjang)
- [Matrix chain](#matrix-chain)
- [Stone merging](#stone-merging)
- [Burst balloons](#burst-balloons)
- [Palindrome partition](#palindrome-partition)
- [Potong kayu](#potong-kayu)
- [Perbandingan biaya](#perbandingan-biaya)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Kerangka range

**Teori:** Analoginya merangkai kalung: kamu sudah tahu biaya merangkai manik `l..k` dan `k+1..r`, lalu membayar satu kali untuk menyambung keduanya. Semua urutan kurung yang berbeda hanya beda di titik sambung terakhir `k`. Itu optimal substructure: induk memakai anak yang sudah optimal.

Bentuk umum:

```
dp[l][r] = min/max atas k ∈ [l, r)
           ( dp[l][k] + dp[k+1][r] + biaya(l, k, r) )
```

Kadang `k` adalah elemen **terakhir** yang diproses di dalam interval (burst balloons), bukan potongan dua blok. Intinya sama: subinterval lebih pendek dihitung dulu.

**Kapan:** gabung batu, kurung matriks, potong kayu, palindrom interval, burst balloons, rectangle cutting. **Tidak:** "pilih subset" tanpa syarat bersebelahan. `n > 500` tanpa Knuth/D&C — `O(n³)` mati.

**STATE:** `dp[l][r]` adalah biaya / nilai / potongan optimal untuk memproses indeks `l..r` inklusif.

**TRANSISI:** enumerasi titik pecah `k`, gabung dua anak, tambah `biaya`.

**BASIS:** `dp[i][i] = 0` (satu elemen, tidak ada gabungan). Kadang panjang 2 diisi rumus langsung.

**Proses (table):** tiga angka `[1, 2, 3]`, biaya gabung = jumlah kedua tumpukan.

| len | `[l,r]` | k | rumus | nilai |
|---|---|---|---|---|
| 1 | 0..0, 1..1, 2..2 | — | basis | 0 |
| 2 | 0..1 | 0 | 0+0+(1+2) | 3 |
| 2 | 1..2 | 1 | 0+0+(2+3) | 5 |
| 3 | 0..2 | 0 | 0+5+(1+2+3)=11 | |
| 3 | 0..2 | 1 | 3+0+6=9 | **9** |

Urutan `(1+2)+3` biaya `3+6=9`. Urutan `1+(2+3)` biaya `5+6=11`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

// kerangka: isi biaya() sesuai soal
ll rangeKerangka(int n, function<ll(int,int,int)> biaya) {
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + biaya(l, k, r));
        }
    }
    return dp[0][n - 1];
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 3};
    vector<ll> pref(4, 0);
    for (int i = 0; i < 3; i++) pref[i + 1] = pref[i] + a[i];
    auto biaya = [&](int l, int, int r) { return pref[r + 1] - pref[l]; };
    cout << rangeKerangka(3, biaya) << '\n'; // 9
    return 0;
}
```

**Jebakan:**

1. `for l, for r = l+1` tanpa urutan panjang: `dp[k+1][r]` masih `INF` mentah.
2. `k` sampai `r` inklusif: interval kanan kosong.
3. Lupa set `INF` sebelum `min`.
4. `n = 1` tidak masuk loop `len=2` — kembalikan 0.

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori. `n ≤ 400` nyaman, `n = 500` ketat.

---

## Mengapa loop panjang

**Teori:** Ketergantungan range DP adalah "anak lebih pendek". Loop `l` menaik lalu `r` menaik **tidak** menjamin `dp[l][k]` dan `dp[k+1][r]` sudah siap jika `k` di tengah. Contoh: menghitung `[0,3]` butuh `[1,3]`. Jika `l` luar dan `r` dalam, saat `l=0,r=3` nilai `[1,3]` mungkin belum diisi karena `l=1` belum dikunjungi.

Urutan aman:

```
for len = 2..n
    for l = 0..n-len
        r = l+len-1
        for k = l..r-1
```

Top-down memo juga aman: rekursi otomatis menunggu anak.

**Kapan:** selalu untuk bottom-up range. **Tidak:** LIS/knapsack — dependensi bukan panjang interval.

**STATE:** tidak berubah; ini urutan evaluasi.

**TRANSISI:** baca hanya `len' < len`.

**BASIS:** `len = 1` diisi sebelum loop.

**Proses (table):** `n=4`, urutan pengisian sel (hanya `(l,r)`).

| urutan | len | sel |
|---|---|---|
| 1–4 | 1 | (0,0) (1,1) (2,2) (3,3) |
| 5–7 | 2 | (0,1) (1,2) (2,3) |
| 8–9 | 3 | (0,2) (1,3) |
| 10 | 4 | (0,3) |

Saat `(0,3)` dihitung, `(0,1),(0,2),(1,3),(2,3)` sudah ada.

**Kode modular:** lihat kerangka. Versi salah (jangan):

```cpp
// SALAH: l lalu r tanpa len
for (int l = 0; l < n; l++)
    for (int r = l + 1; r < n; r++)
        { /* dp[1][3] belum ada saat l=0 r=3 jika n>3 */ }
```

**Jebakan:** top-down tanpa memo = eksponensial. Bottom-up `r` menurun kadang kebetulan lolos untuk `n` kecil, WA di `n` besar.

**Kompleksitas:** urutan tidak mengubah `O(n³)`, hanya kebenaran.

---

## Matrix chain

**Teori:** Perkalian matriks asosiatif, jumlah kali skalar **tidak**. `A(10×100) × B(100×5) × C(5×20)`:

```
(AB)C = 10*100*5 + 10*5*20  = 5000+1000 = 6000
A(BC) = 100*5*20 + 10*100*20 = 10000+20000 = 30000
```

Dimensi disimpan di `p[0..n]`: matriks ke-`i` berukuran `p[i] × p[i+1]`. Ada `n` matriks, array `p` panjang `n+1`. Analoginya kurung pada ekspresi: yang berubah hanya letak kurung, bukan urutan faktor.

**Kapan:** urutan asosiasi, "minimum scalar multiplications", kurung optimal. **Tidak:** matriks tidak berantai (dimensi tidak nyambung). Perkalian elemen-wise.

**STATE:** `dp[l][r]` adalah biaya minimum mengalikan matriks `l..r` (0-based, inklusif).

**TRANSISI:** pecah setelah `k` (`l ≤ k < r`):

```
dp[l][r] = min_k  dp[l][k] + dp[k+1][r] + p[l] * p[k+1] * p[r+1]
```

Hasil kali tiga itu adalah biaya mengalikan blok kiri (`p[l] × p[k+1]`) dengan blok kanan (`p[k+1] × p[r+1]`).

**BASIS:** `dp[i][i] = 0`.

**Proses (table):** `p = [10, 100, 5, 20]`, tiga matriks A,B,C.

| sel | k | biaya | pilih |
|---|---|---|---|
| `dp[0][1]` | 0 | 10*100*5 = 5000 | 5000 |
| `dp[1][2]` | 1 | 100*5*20 = 10000 | 10000 |
| `dp[0][2]` | 0 | 0+10000+10*100*20 = 30000 | |
| `dp[0][2]` | 1 | 5000+0+10*5*20 = 6000 | **6000** |

Kurung `(A×B)×C`.

Empat matriks `p = [2, 3, 4, 2, 5]` (latihan tangan):

| len | sel | hasil yang diharapkan |
|---|---|---|
| 2 | (0,1) | 2*3*4 = 24 |
| 2 | (1,2) | 3*4*2 = 24 |
| 2 | (2,3) | 4*2*5 = 40 |
| 3 | (0,2) | min(24+0+2*4*2, 0+24+2*3*2) = min(40, 36) = 36 |
| 3 | (1,3) | min(24+40? hitung teliti) | pakai kode |
| 4 | (0,3) | lihat `mcm` |

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll mcm(const vector<ll>& p) {
    int n = (int)p.size() - 1;
    if (n <= 1) return 0;
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + p[l] * p[k + 1] * p[r + 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }
    return dp[0][n - 1];
}

pair<ll, string> mcmParens(const vector<ll>& p) {
    int n = (int)p.size() - 1;
    if (n <= 0) return {0, ""};
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
    FASTIO;
    vector<ll> p = {10, 100, 5, 20};
    cout << mcm(p) << '\n'; // 6000
    auto [cost, expr] = mcmParens(p);
    cout << cost << ' ' << expr << '\n';
    return 0;
}
```

**Jebakan:**

1. `p` berukuran `n` bukan `n+1` — dimensi terakhir hilang.
2. Indeks `p[k]` vs `p[k+1]`: yang benar `p[l]*p[k+1]*p[r+1]`.
3. Overflow `int` pada hasil kali tiga dimensi (`200*200*200 = 8e6` masih aman; `1000³` tidak).
4. Mengembalikan `dp[0][n]` padahal matriks hanya `0..n-1`.

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## Stone merging

**Teori:** Gabung dua tumpukan **bersebelahan**, biaya = jumlah keduanya (AtCoder DP-N Slimes). Tumpukan baru bisa digabung lagi sampai satu. Sama dengan MCM, tetapi biaya `sum[l..r]`, bukan hasil kali dimensi. Prefix sum membuat `sum(l..r)` O(1).

Kenapa `sum[l..r]` ditambah di **setiap** pecah, bukan hanya daun? Karena setiap gabung membayar isi kedua blok, dan isi blok adalah jumlah batu di dalamnya. Setiap batu di `[l,r]` dibayar lagi setiap kali interval itu digabung. Itu disengaja.

Tidak boleh gabung yang tidak bersebelahan: urutan spasial penting. Huffman coding (gabung dua terkecil global) adalah soal lain.

**Kapan:** "merge adjacent piles", slimes, file concatenation berurutan. **Tidak:** gabung sebarang pasangan (Huffman / greedy).

**STATE:** `dp[l][r]` biaya minimum menggabungkan batu `l..r` menjadi satu tumpukan.

**TRANSISI:** `dp[l][r] = min_k (dp[l][k] + dp[k+1][r]) + pref[r+1]-pref[l]`.

**BASIS:** `dp[i][i] = 0`.

**Proses (table):** `a = [10, 20, 30]`.

`pref = [0, 10, 30, 60]`

| sel | k | anak + sum | nilai |
|---|---|---|---|
| (0,1) | 0 | 0+0+30 | 30 |
| (1,2) | 1 | 0+0+50 | 50 |
| (0,2) | 0 | 0+50+60 = 110 | |
| (0,2) | 1 | 30+0+60 = 90 | **90** |

Urutan `(10+20)=30` lalu `30+30=60`, total biaya `30+60=90`.

Empat batu `[1,1,1,1]`:

| urutan | biaya |
|---|---|
| `((1+1)+(1+1))` | 2+2+4 = **8** |
| `(((1+1)+1)+1)` | 2+3+4 = 9 |

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll stoneMerging(const vector<ll>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INF;
            ll sum_lr = pref[r + 1] - pref[l];
            for (int k = l; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum_lr);
        }
    }
    return dp[0][n - 1];
}

int main() {
    FASTIO;
    cout << stoneMerging({10, 20, 30}) << '\n'; // 90
    cout << stoneMerging({1, 1, 1, 1}) << '\n'; // 8
    return 0;
}
```

**Jebakan:** biaya ditambah di anak **dan** induk dengan rumus berbeda sampai dobel. Lupa `sum_lr`. `n=400` `O(n³)` ≈ 6e7 aman; `n=2000` butuh Knuth ([27](27-dnc-knuth.md)).

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## Burst balloons

**Teori:** Meletuskan balon `k` di antara yang masih hidup memberi koin `kiri * k * kanan`. Urutan maju sulit karena tetangga berubah setiap letusan. **Balik pikiran:** anggap `k` adalah yang **terakhir** meletus di interval terbuka `(l, r)`. Saat itu dinding kiri dan kanan sudah tetap `nums[l]` dan `nums[r]` — semua balon di antaranya sudah lenyap lebih dulu.

Pasang sentinel `1` di kedua ujung. Analoginya kembang api di antara dua dinding: yang terakhir meledak melihat dinding asli, bukan tetangga yang sudah mati.

**Kapan:** LC 312, "burst balloons", interval dengan elemen terakhir. **Tidak:** hanya boleh letus dari tepi (itu stack/greedy). Model "yang pertama meletus" tanpa update tetangga — WA.

**STATE:** `dp[l][r]` adalah koin maksimum meletuskan semua balon **ketat di antara** `l` dan `r` (dinding `l` dan `r` tidak meletus di dalam state ini).

**TRANSISI:** untuk `k = l+1 .. r-1`:

```
dp[l][r] = max_k  dp[l][k] + dp[k][r] + nums[l]*nums[k]*nums[r]
```

Anak `(l,k)` dan `(k,r)` tidak overlap: `k` masih hidup sampai terakhir, jadi dua sisi independen.

**BASIS:** interval tanpa isi (`r = l+1`) bernilai 0.

**Proses (table):** `a = [3, 1, 5]`, `nums = [1, 3, 1, 5, 1]`, indeks 0..4.

| `(l,r)` | k | gain | terbaik |
|---|---|---|---|
| (0,2) | 1 | 1*3*1 = 3 | 3 |
| (1,3) | 2 | 3*1*5 = 15 | 15 |
| (2,4) | 3 | 1*5*1 = 5 | 5 |
| (0,3) | 1 | 0+15+1*3*5 = 30 | |
| (0,3) | 2 | 3+0+1*1*5 = 8 | 30 |
| (1,4) | 2 / 3 | 8 / 30 | 30 |
| (0,4) | 1 | 0+30+1*3*1 = 33 | |
| (0,4) | 2 | 3+5+1*1*1 = 9 | |
| (0,4) | 3 | 30+0+1*5*1 = 35 | **35** |

Jawaban 35. Satu urutan yang mencapai 35: letus `1` dulu (tengah), lalu `3`, lalu `5` terakhir (dinding 1 dan 1).

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll burstBalloons(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    vector<ll> nums(n + 2, 1);
    for (int i = 0; i < n; i++) nums[i + 1] = a[i];
    int m = n + 2;
    vector<vector<ll>> dp(m, vector<ll>(m, 0));
    for (int len = 2; len < m; len++) {
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            for (int k = l + 1; k < r; k++) {
                ll gain = dp[l][k] + dp[k][r] + nums[l] * nums[k] * nums[r];
                dp[l][r] = max(dp[l][r], gain);
            }
        }
    }
    return dp[0][m - 1];
}

int main() {
    FASTIO;
    cout << burstBalloons({3, 1, 5}) << '\n'; // 35
    cout << burstBalloons({3, 1, 5, 8}) << '\n';
    return 0;
}
```

**Jebakan:**

1. Model "pertama meletus": tetangga berubah, state tidak cukup `[l,r]`.
2. Lupa sentinel 1: ujung memakai 0, seluruh hasil 0.
3. Loop `len` dari 1: `r=l+1` tidak punya `k`, oke, tetapi `k` harus `l+1..r-1`.
4. `max` diinisialisasi `INF` (salah arah).

**Kompleksitas:** `O(n³)` waktu, `O(n²)` memori.

---

## Palindrome partition

**Teori:** Potong string menjadi potongan palindrom, minimalkan **jumlah potongan** (atau jumlah bagian). Dua tahap: (1) `isPal[l][r]` O(n²) dari interval lebih pendek, (2) `cut[r]` DP 1D: prefiks `r` jadi palindrom minimum. Ini campuran range boolean + linear DP, bukan `O(n³)` murni jika palindrom diprecompute.

**Kapan:** "palindrome partitioning", minimum cuts. **Tidak:** longest palindromic **substring** (expand / Manacher). LPS subsequence = LCS dengan reverse ([09](09-lcs-edit.md)).

**STATE:** `isPal[l][r]` benar jika `s[l..r]` palindrom. `dp[r]` banyak **bagian** palindrom minimum untuk `s[0..r-1]`.

**TRANSISI:**

```
isPal[l][r] = (s[l]==s[r]) && (len<=2 || isPal[l+1][r-1])
dp[r] = min { dp[l] + 1 | isPal[l][r-1] }
```

**BASIS:** `isPal[i][i] = true`. `dp[0] = 0`. Jumlah **potongan** = `dp[n] - 1`.

**Proses (table):** `s = "aab"`.

`isPal` (1 = ya):

| l\\r | 0 a | 1 a | 2 b |
|---|---|---|---|
| 0 | 1 | 1 | 0 |
| 1 |  | 1 | 0 |
| 2 |  |  | 1 |

| r (panjang prefiks) | pilihan l | dp[r] |
|---|---|---|
| 0 | — | 0 |
| 1 | [0,0] "a" | 1 |
| 2 | [0,1] "aa" | 1 |
| 3 | [0,1]+"b" atau [2,2] | **2** |

Bagian `"aa"|"b"`. Potongan = 1.

`"aba"` sudah palindrom: `dp[3]=1`, potongan 0.

`"aabba"`: `"a"|"abba"` atau `"aa"|"bb"|"a"` — minimum bagian 2, potongan 1 (`a|abba`? `a` dan `abba` — `abba` palindrom). Ya.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int minPalindromeCuts(const string& s) {
    int n = (int)s.size();
    if (n <= 1) return 0;
    vector<vector<char>> isPal(n, vector<char>(n, 0));
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) isPal[l][r] = (len <= 2 || isPal[l + 1][r - 1]);
        }
    }
    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;
    for (int r = 1; r <= n; r++)
        for (int l = 0; l < r; l++)
            if (isPal[l][r - 1]) dp[r] = min(dp[r], dp[l] + 1);
    return dp[n] - 1;
}

int palindromeParts(const string& s) {
    return minPalindromeCuts(s) + (s.empty() ? 0 : 1);
}

int main() {
    FASTIO;
    cout << minPalindromeCuts("aab") << '\n';  // 1
    cout << minPalindromeCuts("aba") << '\n';  // 0
    cout << minPalindromeCuts("aabba") << '\n';
    return 0;
}
```

**Jebakan:** `isPal` diisi tanpa urutan panjang (`isPal[l+1][r-1]` sampah). Mengembalikan jumlah bagian padahal soal minta potongan. Cek palindrom O(n) per transisi → `O(n³)` tidak perlu.

**Kompleksitas:** `O(n²)` waktu dan memori.

---

## Potong kayu

**Teori:** Tongkat `[0, L]` harus dipotong di titik-titik wajib. Biaya satu potongan = **panjang segmen saat ini**. Urutan potong mengubah biaya, sama seperti range DP: potongan **terakhir** di dalam `(l, r)` membelah jadi dua anak plus bayar `cuts[r]-cuts[l]`.

Tambah 0 dan `L` ke daftar titik, lalu **sort**. Tanpa ujung, interval tidak tertutup.

**Kapan:** LC Minimum Cost to Cut a Stick, CSES varian. **Tidak:** potong diagonal / tidak lurus.

**STATE:** `dp[i][j]` biaya minimum memotong semua titik wajib ketat di antara titik terurut `i` dan `j`.

**TRANSISI:** `k` di `(i, j)`: `dp[i][k] + dp[k][j] + (cuts[j]-cuts[i])`.

**BASIS:** tidak ada titik dalam → 0.

**Proses (table):** `L=7`, cuts `{1,3,4,5}`. Titik `[0,1,3,4,5,7]`.

Satu urutan mahal vs murah: selalu membayar 7 pada potongan pertama (seluruh tongkat), lalu segmen lebih kecil. Semua urutan membayar 7 sekali; yang beda adalah potongan berikutnya. Jawaban klasik 16.

Hitung kasar: potong 3 dulu (bayar 7) → `[0,3]` dan `[3,7]`. Lanjut bisa 1 (bayar 3) lalu 4 (bayar 4) lalu 5 (bayar 4) — total `7+3+4+4=18`. Urutan lebih baik ada 16; percayai DP, jangan greedy titik tengah.

**Kode modular:**

```cpp
ll minCostCutStick(ll L, vector<int> cuts) {
    cuts.push_back(0);
    cuts.push_back((int)L);
    sort(cuts.begin(), cuts.end());
    int m = (int)cuts.size();
    vector<vector<ll>> dp(m, vector<ll>(m, 0));
    for (int len = 2; len < m; len++) {
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INF;
            ll seg = cuts[r] - cuts[l];
            for (int k = l + 1; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + seg);
        }
    }
    return dp[0][m - 1];
}
```

**Jebakan:** lupa sort. Lupa ujung 0 dan `L`. `k` termasuk `l` atau `r` (dinding).

**Kompleksitas:** `O(m³)` pada jumlah titik, bukan `L`.

---

## Perbandingan biaya

**Teori:** Semua soal file ini memakai kerangka yang sama; yang berubah hanya **apa yang dibayar** dan **apa yang menjadi `k`**.

| soal | `k` artinya | biaya / gain |
|---|---|---|
| MCM | potong rantai setelah matriks `k` | `p[l]*p[k+1]*p[r+1]` |
| stone | gabung dua blok di `k` | `sum[l..r]` |
| burst | `k` meletus **terakhir** di `(l,r)` | `nums[l]*nums[k]*nums[r]` |
| cut stick | potong terakhir di titik `k` | panjang segmen sekarang |
| pal cut | ujung potongan prefiks | +1 bagian jika palindrom |

**Kapan:** memilih rumus saat statement membingungkan. **Tidak:** memaksa semua jadi `sum[l..r]`.

**STATE:** tetap interval.

**TRANSISI:** ganti satu baris biaya.

**BASIS:** hampir selalu 0 untuk interval kosong/tunggal; burst dinding bersebelahan 0.

**Proses (table):** satu input dua rumus — `[10,20,30]` sebagai stone vs sebagai dimensi palsu. Jangan campur: stone jawab 90; kalau dipaksa MCM butuh `p` panjang 4.

**Kode modular:** tidak ada fungsi baru; pilih `mcm` / `stoneMerging` / `burstBalloons`.

**Jebakan:** burst memakai `k` seperti stone (`k < r` termasuk dinding). Palindrom memakai `O(n³)` pecah seperti MCM padahal `O(n²)` cukup.

**Kompleksitas:** sama `O(n³)` kecuali palindrom `O(n²)`.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = 4e18;

ll mcm(const vector<ll>& p);
ll stoneMerging(const vector<ll>& a);
ll burstBalloons(const vector<int>& a);
int minPalindromeCuts(const string& s);
ll minCostCutStick(ll L, vector<int> cuts);

int main() {
    FASTIO;
    cout << mcm({10, 100, 5, 20}) << '\n';
    cout << stoneMerging({10, 20, 30}) << '\n';
    cout << burstBalloons({3, 1, 5}) << '\n';
    cout << minPalindromeCuts("aab") << '\n';
    return 0;
}
```

Checklist isi tabel:

```
1. n kecil? <= 400 untuk n^3
2. Loop len di luar
3. Basis diagonal 0
4. k tidak membuat anak kosong (kecuali soal izinkan)
5. biaya ll
```

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| semua `INF` | loop `l,r` tanpa `len` | loop panjang |
| MCM 30000 bukan 6000 | salah kurung / salah indeks `p` | `p[l]*p[k+1]*p[r+1]` |
| stone 60 bukan 90 | hanya biaya gabung terakhir | tambah biaya tiap level |
| burst 0 | lupa sentinel 1 | `nums = [1]+a+[1]` |
| burst terlalu kecil | model pertama meletus | `k` terakhir |
| pal 2 untuk `"aba"` | mengembalikan bagian | potongan = bagian-1 |
| pal TLE | cek O(n) per pasangan | `isPal` O(n²) |
| cut stick aneh | cuts tidak di-sort | sort + ujung |
| overflow | `int * int * int` | `ll` |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| kerangka stone | `[1,2,3]` | 9 |
| `mcm` | `p=10,100,5,20` | 6000 |
| `mcmParens` | sama | `(A1 x A2) x A3` |
| `mcm` | satu matriks `p=2,3` | 0 |
| `stoneMerging` | `10 20 30` | 90 |
| `stoneMerging` | `1 1 1 1` | 8 |
| `burstBalloons` | `3,1,5` | 35 |
| `burstBalloons` | `[]` | 0 |
| `minPalindromeCuts` | `aab` | 1 |
| `minPalindromeCuts` | `aba` | 0 |
| `minPalindromeCuts` | `a` | 0 |
| `minCostCutStick` | `L=7`, `{1,3,4,5}` | 16 |

Rekonstruksi kurung MCM memakai `split[l][r]` — pola yang sama di [12-rekonstruksi](12-rekonstruksi.md). `n=2000` stone: Knuth di [27-dnc-knuth](27-dnc-knuth.md), bukan mengulang `O(n³)` di sini.

Lanjut ke jejak jawaban: nilai optimal ≠ objek optimal.
