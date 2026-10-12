# Memoization: jembatan ke DP

[← README](README.md) · [Indeks CP](../README.md)

Memo adalah buku catatan untuk rekursi. Sebelum menghitung state, cek catatan. Kalau sudah ada, langsung pakai. Kalau belum, hitung sekali, tulis, baru `return`. Pohon eksponensial menjadi tabel.

File ini adalah **jembatan ke folder [09-dp](../09-dp/README.md)**. Top-down di sini = tabel yang sama dengan bottom-up di sana. Baca [01-prinsip.md](../09-dp/01-prinsip.md) dan [02-topdown-bottomup.md](../09-dp/02-topdown-bottomup.md) setelah file ini.

Day terkait: **066–067**.

## Daftar isi

- [Tiga baris sakti](#tiga-baris-sakti)
- [Fibonacci dengan memo](#fibonacci-dengan-memo)
- [Tangga](#tangga)
- [0-1 knapsack top-down](#0-1-knapsack-top-down)
- [Subset sum dengan memo](#subset-sum-dengan-memo)
- [Dari memo ke tabel bottom-up](#dari-memo-ke-tabel-bottom-up)
- [Desain state singkat](#desain-state-singkat)
- [Peta ke folder 09](#peta-ke-folder-09)

---

## Tiga baris sakti

**Teori:** Analoginya PR yang sama dikumpulkan satu kunci jawaban. Tiga baris: cek cache, hitung, simpan. Overlapping subproblems hilang; setiap state dihitung paling banyak sekali. Itu definisi DP top-down. Optimal substructure juga perlu: jawaban state besar tersusun dari jawaban state kecil. Tanpa overlap, memo tidak menolong. Tanpa substruktur, rumus transisi tidak ada.

**Kapan:** rekursi alami, tidak semua state terpakai, atau kamu belum yakin urutan isi tabel. Fibonacci, tangga, knapsack, LCS, digit DP. Jangan jika kedalaman `1e5` rantai: stack overflow, pindah bottom-up. Jangan sentinel `-1` jika jawaban sah bisa `-1`.

**Proses:** kerangka.

```text
f(state):
    if basis: return nilai_kecil
    if seen[state]: return dp[state]
    seen[state] = true
    dp[state] = gabung(f(anak1), f(anak2), ...)
    return dp[state]
```

Tanpa `seen`, sentinel `-1` dipakai jika `0` tidak pernah jawaban, atau jika kamu mengisi awal dengan `-1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int MAXN = 10005;
ll memo[MAXN];

ll contoh(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = contoh(n - 1) + contoh(n - 2);
}

void reset_memo(int n) {
    for (int i = 0; i <= n; i++) memo[i] = -1;
}

int main() {
    FASTIO;
    reset_memo(10);
    cout << contoh(10) << '\n'; // 55
    return 0;
}
```

**Jebakan:**
1. `return f(...)` tanpa `memo[s] =`.
2. Lupa reset antar testcase.
3. `vector` memo di dalam fungsi rekursif: disalin, cache mati.
4. State kurang dimensi: fungsi baca global yang berubah.

**Kompleksitas:** waktu `O(jumlah state × kerja transisi)`. Memori tabel plus stack kedalaman.

---

## Fibonacci dengan memo

**Teori:** Nilai unik `F(0)..F(n)` hanya `n+1` buah. Naif menghitung ulang. Memo membuat tiap `F(k)` sekali. Analoginya menuliskan barisan di kertas, bukan mengulang dari awal setiap ditanya. Alasan benar: transisi `F(n) = F(n-1)+F(n-2)` plus dua basis.

**Kapan:** `n <= 90` untuk `ll` (`F(92)` masih muat, `F(93)` tidak). Lebih besar: modular atau big integer. Jangan naif. Untuk `n = 1e18` bukan memo, melainkan matrix expo di folder 09 / teori bilangan.

**Proses:** `fib_memo(5)`, cache awal semua `-1`.

```text
fib(5) miss → fib(4)+fib(3)
  fib(4) miss → fib(3)+fib(2)
    fib(3) miss → fib(2)+fib(1)
      fib(2) miss → 1+0, memo[2]=1
      fib(1)=1
    memo[3]=2
    fib(2) HIT 1
  memo[4]=3
  fib(3) HIT 2
memo[5]=5
```

Setelah itu `fib(5)` lagi = satu kali baca cache.

| n | naif | memo |
| ---: | ---: | ---: |
| 20 | 21891 | 21 state |
| 40 | 331 juta | 41 state |
| 90 | mustahil | 91 state |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int MAXN = 10005;
ll memo[MAXN];

ll fib_memo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
}

void reset_memo(int n) {
    for (int i = 0; i <= n; i++) memo[i] = -1;
}

int main() {
    FASTIO;
    reset_memo(50);
    cout << fib_memo(10) << '\n'; // 55
    cout << fib_memo(40) << '\n'; // 102334155
    cout << fib_memo(50) << '\n'; // 12586269025
    return 0;
}
```

Sentinel terpisah jika 0 atau -1 bisa jawaban:

```cpp
bool seen[MAXN];
ll dp[MAXN];

ll f(int n) {
    if (n <= 1) return n;
    if (seen[n]) return dp[n];
    seen[n] = true;
    return dp[n] = f(n - 1) + f(n - 2);
}
```

**Jebakan:**
1. Overflow diam-diam di `n >= 93`.
2. `memset` pada `bool` mudah, pada `ll` `-1` sah (semua bit 1).
3. State `n` negatif jika basis hanya `n == 0`.

**Kompleksitas:** waktu `O(n)`, memori `O(n)` plus stack `O(n)`.

---

## Tangga

**Teori:** `naik(i)` = banyak cara menuju undak `i` dengan langkah 1 atau 2. `naik(i) = naik(i-1) + naik(i-2)`. Basis: `naik(0) = 1` (sudah di tanah, satu cara: tidak jalan), `naik` negatif = 0. Analoginya Fibonacci yang digeser. Alasan benar: langkah terakhir hanya 1 atau 2.

**Kapan:** `n` undak sampai `1e5` lebih aman bottom-up karena stack. Jangan tangga naif tanpa memo. Varian “langkah 1..k” menambah loop di transisi: folder 09 file linear 1D.

**Proses:** `n = 4`.

```text
naik(4) = naik(3)+naik(2)
naik(3) = naik(2)+naik(1)
naik(2) = naik(1)+naik(0) = 1+1 = 2
naik(1) = 1
naik(0) = 1
naik(3) = 2+1 = 3
naik(4) = 3+2 = 5
```

Lima cara: `1+1+1+1`, `1+1+2`, `1+2+1`, `2+1+1`, `2+2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll memo_t[10005];

ll naik(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (memo_t[n] != -1) return memo_t[n];
    return memo_t[n] = naik(n - 1) + naik(n - 2);
}

int main() {
    FASTIO;
    memset(memo_t, -1, sizeof(memo_t));
    cout << naik(4) << '\n';  // 5
    cout << naik(5) << '\n';  // 8
    cout << naik(0) << '\n';  // 1
    return 0;
}
```

**Jebakan:**
1. `naik(0)` diisi 0. Itu menghapus semua cara.
2. Soal 1-based “anak tangga 1..n” versus “sudah di tanah”.
3. Overflow cara: `n = 50` sudah besar, sering diminta modulo.

**Kompleksitas:** `O(n)` waktu dan memori.

---

## 0-1 knapsack top-down

**Teori:** `knap(i, sisa)` = nilai maksimum memakai barang `i..n-1` dengan kapasitas `sisa`. Transisi: lewati, atau ambil jika `wt[i] <= sisa`. Analoginya rak tas: tiap barang keputusan ya/tidak, dan keputusan itu diingat. Greedy rasio **gagal** pada 0-1: barang `(2,3), (3,4)`, `W = 3` → greedy 3, optimal 4. Itu alasan file greedy `kapan-dp.md` menunjuk ke sini.

State harus lengkap: semua yang memengaruhi keputusan masa depan masuk parameter. Basis: `i == n` nilai 0.

**Kapan:** `n <= 100`, `W <= 1e5`, atau state jarang. Jangan `W = 1e9` sebagai indeks array. Jangan greedy.

**Proses:** barang `(2,3), (3,4), (4,5)`, `W = 5`.

```text
knap(0,5) = max( knap(1,5),  3 + knap(1,3) )
knap(1,5) = max( knap(2,5),  4 + knap(2,2) )
knap(2,5) = max(0, 5) = 5
knap(2,2) = 0
knap(1,5) = max(5, 4) = 5
knap(1,3) = max(0, 4) = 4
knap(0,5) = max(5, 3+4=7) = 7
```

Ambil barang 0 dan 1: berat 5, nilai 7.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int MAXN = 105, MAXW = 10005;
ll memo_k[MAXN][MAXW];
int nbarang;
ll wt[MAXN], val[MAXN];

ll knap(int i, int sisa) {
    if (i == nbarang) return 0;
    if (memo_k[i][sisa] != -1) return memo_k[i][sisa];
    ll ans = knap(i + 1, sisa);
    if (wt[i] <= sisa)
        ans = max(ans, val[i] + knap(i + 1, (int)(sisa - wt[i])));
    return memo_k[i][sisa] = ans;
}

ll greedy_rasio(int W) {
    vector<int> idx(nbarang);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return val[i] * wt[j] > val[j] * wt[i];
    });
    ll sisa = W, nilai = 0;
    for (int i : idx) if (wt[i] <= sisa) {
        sisa -= wt[i];
        nilai += val[i];
    }
    return nilai;
}

int main() {
    FASTIO;
    nbarang = 3;
    wt[0] = 2; val[0] = 3;
    wt[1] = 3; val[1] = 4;
    wt[2] = 4; val[2] = 5;
    memset(memo_k, -1, sizeof(memo_k));
    cout << knap(0, 5) << '\n';     // 7
    cout << greedy_rasio(5) << '\n'; // 7 di contoh ini
    nbarang = 2;
    wt[0] = 2; val[0] = 3;
    wt[1] = 3; val[1] = 4;
    memset(memo_k, -1, sizeof(memo_k));
    cout << knap(0, 3) << ' ' << greedy_rasio(3) << '\n'; // 4 3
    return 0;
}
```

**Jebakan:**
1. `sisa` jadi indeks negatif jika tidak cek `wt[i] <= sisa`.
2. `W` jadi indeks array saat `W` besar.
3. Loop kapasitas naik di versi bottom-up 0-1: barang terpakai berkali-kali.
4. Percaya greedy karena sampel kebetulan sama.

**Kompleksitas:** `O(n · W)` waktu dan memori, plus stack `O(n)`.

---

## Subset sum dengan memo

**Teori:** `ada(pos, sisa)` true jika sisa barang `pos..` bisa membentuk `sisa`. Transisi: lewat atau ambil. Memo mengubah `O(2^n)` menjadi `O(nS)`. Analoginya: pertanyaan “dari indeks 3, bisakah membuat 10?” hanya perlu dijawab sekali. Rekonstruksi: setelah tabel hidup, telusuri pilihan yang menjaga `true`.

**Kapan:** `n <= 200`, `S <= 1e5`, atau `n = 40` dengan `S` sedang. Jangan `S = 1e12`. Jangan backtracking telanjang pada `n = 40`.

**Proses:** `a = {3, 1, 7, 4}`, `S = 8`.

Beberapa state:

1. `ada(0,8)` = `ada(1,8)` atau `ada(1,5)`.
2. `ada(1,5)` menjadi true lewat `3` sudah diambil, lalu `1` dan `4`.
3. `ada(2,2)` false.
4. `ada(4,0)` true (basis).
5. `ada(4, k>0)` false.

Tanpa memo, jalur `{3,1,4}` dan jalur yang kembali ke state sama akan dihitung ulang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int memo_s[105][1005];
vector<ll> arr;

int ada(int pos, int sisa) {
    if (sisa == 0) return 1;
    if (pos == (int)arr.size() || sisa < 0) return 0;
    int& res = memo_s[pos][sisa];
    if (res != -1) return res;
    if (ada(pos + 1, sisa)) return res = 1;
    if (arr[pos] <= sisa && ada(pos + 1, sisa - (int)arr[pos])) return res = 1;
    return res = 0;
}

int main() {
    FASTIO;
    arr = {3, 1, 7, 4};
    memset(memo_s, -1, sizeof(memo_s));
    cout << ada(0, 8) << '\n'; // 1
    memset(memo_s, -1, sizeof(memo_s));
    cout << ada(0, 2) << '\n'; // 0
    return 0;
}
```

Lanjut formal di [09-dp/06-subset-sum.md](../09-dp/06-subset-sum.md).

**Jebakan:**
1. `sisa` sebagai indeks tanpa batas.
2. Tidak reset memo saat `S` atau array berubah.
3. `int` memo `0` sebagai “belum” padahal `0` artinya false.

**Kompleksitas:** `O(nS)` waktu dan memori.

---

## Dari memo ke tabel bottom-up

**Teori:** Tabel memo dan tabel DP adalah benda yang sama. Bedanya urutan isi. Top-down: “butuh state ini, hitung dependensinya dulu”. Bottom-up: “isi dari kasus dasar menuju soal besar”. Analoginya masak: memo = masak bahan saat dibutuhkan; tingkat bawah = masak dari yang paling sederhana menurut resep. Jawaban sama jika transisi sama.

**Kapan:** pindah ke bottom-up jika stack dalam, atau butuh rolling array, atau loop lebih cepat. Tetap memo jika state jarang (hanya 1% sel hidup) atau transisi sulit diurutkan. Jangan mengisi tabel tanpa memastikan urutan.

**Proses:** Fibonacci `n = 6`.

Memo (urutan hitung pertama kali) meloncat sesuai pohon, tetapi tiap angka sekali.

Bottom-up:

```text
dp[0]=0
dp[1]=1
i=2: 0+1=1
i=3: 1+1=2
i=4: 1+2=3
i=5: 2+3=5
i=6: 3+5=8
```

Knapsack 0-1, loop barang lalu kapasitas **turun** (supaya tiap barang sekali):

```text
W=5, (2,3), (3,4), (4,5)
awal      [0,0,0,0,0,0]
ambil 2,3 [0,0,3,3,3,3]
ambil 3,4 [0,0,3,4,4,7]
ambil 4,5 [0,0,3,4,5,7]
```

Jawaban `dp[5] = 7`, sama dengan memo.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll fib_up(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = a + b;
        a = b;
        b = c;
    }
    return b;
}

ll naik_up(int n) {
    if (n <= 1) return 1;
    vector<ll> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

ll knap_up(const vector<ll>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        for (int cap = W; cap >= (int)w[i]; cap--)
            dp[cap] = max(dp[cap], v[i] + dp[cap - (int)w[i]]);
    }
    return dp[W];
}

int main() {
    FASTIO;
    cout << fib_up(10) << '\n';  // 55
    cout << naik_up(4) << '\n';  // 5
    cout << knap_up({2, 3, 4}, {3, 4, 5}, 5) << '\n'; // 7
    return 0;
}
```

**Jebakan:**
1. Knapsack loop kapasitas **naik** untuk 0-1: itu unbounded.
2. Off-by-one `dp[n]` versus `dp[n-1]`.
3. Menyalin kode memo ke loop tanpa meniru dependensi.
4. Mengira bottom-up selalu lebih hemat: state jarang, memo menang.

**Kompleksitas:** sama dengan jumlah sel tabel kali transisi. Fibonacci `O(n)` atau `O(1)` memori rolling. Knapsack `O(nW)` waktu, `O(W)` memori.

---

## Desain state singkat

**Teori:** Sebelum menulis memo, jawab tiga kalimat dari [README CP](../README.md):

```text
1. STATE     : dp[i] artinya apa?
2. TRANSISI  : dihitung dari state mana, operator apa?
3. BASIS     : state terkecil nilainya berapa, kenapa?
```

Analoginya label kotak: jika label kurang, dua situasi beda menumpuk di sel yang sama. Alasan WA klasik: lupa memasukkan “sisa kapasitas”, “apakah barang sebelumnya diambil”, atau “digit sudah bound”.

**Kapan:** setiap soal DP baru. Jangan menambah dimensi “untuk jaga-jaga” sampai `n^5`. Jangan mengurangi dimensi karena sampel kebetulan benar.

**Proses:** tiga soal, tiga state.

1. Tangga: `dp[i]` = cara ke undak `i`. Satu dimensi.
2. Knapsack: `dp[i][w]` = nilai dari `i` barang pertama, kapasitas `w`. Dua dimensi, atau rolling `dp[w]`.
3. LCS: `dp[i][j]` = LCS awalan `s[0..i)` dan `t[0..j)`. Dua indeks string.

Kalau soal “paling banyak `K` kali skip”, `K` masuk state. Kalau tidak, greedy atau rumus lain mungkin cukup.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// LCS pendek sebagai contoh dua dimensi
int memo_l[20][20];
string s, t;

int lcs(int i, int j) {
    if (i == (int)s.size() || j == (int)t.size()) return 0;
    int& res = memo_l[i][j];
    if (res != -1) return res;
    if (s[i] == t[j]) return res = 1 + lcs(i + 1, j + 1);
    return res = max(lcs(i + 1, j), lcs(i, j + 1));
}

int main() {
    FASTIO;
    s = "ABCBDAB";
    t = "BDCABA";
    memset(memo_l, -1, sizeof(memo_l));
    cout << lcs(0, 0) << '\n'; // 4
    return 0;
}
```

LCS lengkap: [09-dp/09-lcs-edit.md](../09-dp/09-lcs-edit.md).

**Jebakan:**
1. State tidak memuat semua yang masa depan butuhkan.
2. Transisi memakai state yang belum “lebih kecil” menurut urutan apa pun: loop tak hingga.
3. Basis salah: LCS `i==n` harus 0, bukan `-inf`.

**Kompleksitas:** LCS memo `O(|s| |t|)`.

---

## Peta ke folder 09

```text
File ini (top-down)
  → 09-dp/01-prinsip.md        overlapping + substruktur
  → 09-dp/02-topdown-bottomup  memo vs tabel
  → 09-dp/03-linear-1d         tangga, robber, frog
  → 09-dp/04-coin-unbounded    koin min / banyak cara
  → 09-dp/05-01-knapsack       ambil atau tidak
  → 09-dp/06-subset-sum        partition
```

| gejala | arah |
| --- | --- |
| rekursi alami, state jarang | tetap memo |
| n besar, rantai dalam | bottom-up |
| greedy rasio knapsack | DP, bukan greedy |
| n <= 20 himpunan | bitmask DP 09-15 |
| W besar, n <= 40 | MITM, bukan tabel W |

Ringkasan tiga baris: cek, hitung, simpan. Tabel yang sama menunggu di folder 09, diisi dari dasar jika stack atau urutan memaksa.

Lanjut wajib ke [09-dp/README.md](../09-dp/README.md). Jangan loncat ke bitmask TSP sebelum knapsack dan subset sum.
