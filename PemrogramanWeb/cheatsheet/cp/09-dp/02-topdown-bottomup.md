# 02 — Top-down dan bottom-up

[← Prinsip](01-prinsip.md) · [← 09-dp](README.md) · [Linear 1D →](03-linear-1d.md)

Day ComprogLearning: **142**. Rekurens matematisnya sama dengan Day 141. Yang berubah hanya cara mengevaluasi DAG state.

> **Ide satu kalimat:** top-down bertanya ke bawah lalu menyimpan cache; bottom-up menaruh batu dari tanah menurut urutan topologis.

## Daftar isi

- [Dua cara mengevaluasi rekurens](#dua-cara-mengevaluasi-rekurens)
- [Sentinel memo minus satu](#sentinel-memo-minus-satu)
- [Tabulasi dan urutan isi DAG](#tabulasi-dan-urutan-isi-dag)
- [Pull versus push](#pull-versus-push)
- [Empat uji desain state](#empat-uji-desain-state)
- [Frog jump: top-down dan bottom-up](#frog-jump-top-down-dan-bottom-up)
- [Menambah dimensi: liburan](#menambah-dimensi-liburan)
- [Menambah dimensi: tiket diskon](#menambah-dimensi-tiket-diskon)
- [Rolling array](#rolling-array)
- [Stack overflow dan multi-test](#stack-overflow-dan-multi-test)

---

## Dua cara mengevaluasi rekurens

**Teori:** Rekurens `f(n) = gabungan f(lebih kecil)` belum memilih algoritma. Top-down (memoisasi) mulai dari target, pecah ke bawah, dan menyimpan hasil. Itu DFS pada DAG state. Bottom-up (tabulasi) mulai dari basis, lalu mengisi setiap simpul setelah seluruh pendahulunya siap. Analoginya piramida. Top-down berdiri di puncak dan bertanya, "penopang sudah siap?" Bottom-up menaruh fondasi dulu, lalu naik lapis demi lapis. Top-down hanya menghitung state yang terjangkau. Bottom-up mengisi seluruh tabel, lebih ramah cache CPU, dan mudah digulung. Keduanya salah jika urutan dependensi dilanggar: top-down salah jika lupa cache, bottom-up salah jika loop membaca sel yang belum diisi.

**Kapan top-down:** state rumit, banyak state mati, ingin menulis rekursi dulu. **Kapan bottom-up:** `n ≥ 10^5` (stack overflow), butuh rolling array, atau urutan jelas. **Tidak:** kedalaman rekursi `> 10^5` tanpa menaikkan stack.

**STATE:** `f(i)` adalah jawaban lengkap untuk submasalah `i`, dan dua pemanggilan dengan argumen sama harus mengembalikan angka yang sama.

**TRANSISI:** sisi DAG `i -> j` berarti `f(i)` membutuhkan `f(j)` dengan `j` lebih kecil menurut urutan topologis yang kita pilih.

**BASIS:** simpul tanpa pendahulu, biasanya `i = 0`, diisi konstanta sebelum DFS atau sebelum loop.

**Proses:** bandingkan jejak `f(5)` Fibonacci.

```
Top-down (kiri dulu)              Bottom-up
panggil f(5)                      isi dp[0]=0
  panggil f(4)                    isi dp[1]=1
    panggil f(3)                  isi dp[2]=1
      ... basis                   isi dp[3]=2
    baca f(2) dari cache          isi dp[4]=3
  panggil f(3) -> HIT cache       isi dp[5]=5
tulis memo[5]=5                   baca dp[5]
```

```
Aspek              Top-down                 Bottom-up
urutan             DFS on-demand            topologis manual
state mati         dilewati                 tetap diisi
stack              O(kedalaman)             O(1) selain tabel
rolling            sulit                    mudah
overhead           panggilan fungsi         loop polos
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll fibMemo(int n, vector<ll>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = (fibMemo(n - 1, memo) + fibMemo(n - 2, memo)) % MOD;
}

ll fibTab(int n) {
    if (n <= 1) return n;
    vector<ll> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    return dp[n];
}

int main() {
    FASTIO;
    int n = 10;
    vector<ll> memo(n + 1, -1);
    cout << fibMemo(n, memo) << " " << fibTab(n) << "\n";
    return 0;
}
```

**Jebakan:** mengira top-down "lebih benar" daripada bottom-up. Yang benar adalah rekurensnya. Evaluasi hanya alat.

**Kompleksitas:** keduanya `O(n)` waktu untuk Fibonacci. Top-down menambah `O(n)` stack. Bottom-up `O(n)` heap atau `O(1)` jika digulung.

---

## Sentinel memo minus satu

**Teori:** Cache butuh penanda "belum dihitung". Angka `0` adalah jebakan paling sering karena banyak soal punya jawaban sah `0`: `fib(0)`, "tidak ada cara", "untung nol", "biaya nol". Sentinel `-1` aman jika jawaban tidak pernah negatif. Kalau jawaban boleh negatif (selisih, keuntungan rugi, Kadane), `-1` tabrakan. Solusinya array `visited` terpisah, atau sentinel di luar rentang seperti `INF + 1`. Setelah multi-testcase, cache global wajib direset. Lupa reset adalah WA yang hanya muncul di tes kedua.

**Kapan:** setiap top-down. **Tidak:** memakai `if (memo[n])` sebagai tes "sudah ada".

**STATE:** `memo[i]` menyimpan jawaban sah untuk state `i` setelah pernah dihitung; nilai sentinel berarti "belum".

**TRANSISI:** sebelum merekursi, jika `memo[i] != sentinel` maka kembalikan cache; sesudah merekursi, tulis `memo[i] = ans`.

**BASIS:** basis boleh ditulis tanpa menyentuh cache, atau ditulis ke cache agar cabang lain membacanya.

**Proses:** fungsi yang jawabannya bisa `0`, yaitu banyak cara mencapai `0`.

```
n    jawaban sah    memo awal 0          memo awal -1
0    0              dikira belum         basis, return 0
1    1              dihitung             dihitung, tulis 1
2    1              dihitung             dihitung, tulis 1
```

Jika `memo` diisi 0 dan kita menulis `if (memo[n]) return memo[n];`, pemanggilan `f(0)` selalu turun lagi. Pada soal "berapa cara", itu bisa TLE. Pada Fibonacci, `fib(0)` saja sudah salah secara logika meski kadang kebetulan tidak dipanggil.

Tabel keputusan sentinel:

```
Rentang jawaban              Sentinel yang aman
0 .. INF (cacah, koin min)   -1
negatif .. positif           visited[] terpisah
hanya -1 atau positif        visited[] atau -2
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll memoSentinel(int i, vector<ll>& memo) {
    if (i == 0) return 0;
    if (memo[i] != -1) return memo[i];
    return memo[i] = memoSentinel(i - 1, memo) + 1;
}

ll memoVisited(int i, vector<ll>& memo, vector<char>& vis) {
    if (i == 0) return 0;
    if (vis[i]) return memo[i];
    vis[i] = 1;
    return memo[i] = memoVisited(i - 1, memo, vis) + 1;
}

int main() {
    FASTIO;
    int n = 5;
    vector<ll> a(n + 1, -1);
    vector<ll> b(n + 1, 0);
    vector<char> vis(n + 1, 0);
    cout << memoSentinel(n, a) << " " << memoVisited(n, b, vis) << "\n";
    return 0;
}
```

**Jebakan:**

1. `vector<ll> memo(n+1, 0)` plus `if (memo[i])`.
2. Jawaban sah `-1` (mustahil) tertukar dengan "belum".
3. Lupa `memset` / `assign` pada tes berikutnya.

**Kompleksitas:** cek cache `O(1)`. Memori cache sama dengan banyak state. `visited` menambah `O(|state|)` byte.

---

## Tabulasi dan urutan isi DAG

**Teori:** Bottom-up wajib menghormati urutan topologis DAG. Pada DP 1D linear, urutan itu biasanya `i = 0 .. n`. Pada knapsack 2D, barang di luar, kapasitas di dalam, dan kapasitas versi 1D harus mundur. Pada coin unbounded, kapasitas maju. Salah urutan berarti membaca sampah atau memakai barang dua kali. Cara memeriksa: untuk setiap transisi `dp[i] <- dp[j]`, pastikan `j` sudah final saat `i` diisi. Jika `j` dan `i` berada di array yang sama dan `j` bisa baru diubah pada iterasi barang yang sama, tanyakan apakah pengulangan itu disengaja (unbounded) atau bug (0-1).

**Kapan:** setiap loop bottom-up. **Tidak:** mengisi `dp[n]` dulu lalu berjalan mundur pada Fibonacci 1D tanpa mengubah rekurens.

**STATE:** `dp[i]` adalah jawaban untuk simpul `i` setelah semua pendahulu `j` selesai.

**TRANSISI:** tulis sisi `j -> i` di kertas, lalu pilih arah loop yang menjamin `j` sebelum `i`.

**BASIS:** isi seluruh simpul sumber sebelum loop utama. Untuk Fibonacci, `dp[0]` dan `dp[1]`. Untuk frog, `dp[0] = 0` dan sisanya `INF`.

**Proses:** tiga urutan pada `dp[i] = dp[i-1] + dp[i-2]`, `n = 5`.

```
Urutan i=2..5 (benar)
i   baca          tulis
2   1, 0          1
3   1, 1          2
4   2, 1          3
5   3, 2          5

Urutan i=5..2 (salah)
i   baca (masih 0 kecuali basis)   tulis
5   dp[4]=0, dp[3]=0               0
4   0, 0                           0
seluruhnya 0
```

DAG Fibonacci:

```
0 --> 2 --> 4 --> 6
 \   / \   / \   /
  1 --> 3 --> 5
```

Setiap sisi menuju indeks lebih besar, jadi loop menaik sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll fibUrutanBenar(int n) {
    if (n <= 1) return n;
    vector<ll> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    return dp[n];
}

ll fibUrutanSalah(int n) {
    if (n <= 1) return n;
    vector<ll> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = n; i >= 2; i--) dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    return dp[n]; // hampir selalu 0
}

int main() {
    FASTIO;
    cout << fibUrutanBenar(10) << " " << fibUrutanSalah(10) << "\n";
    return 0;
}
```

**Jebakan:** menyalin loop knapsack maju ke soal 0-1. Menyalin loop mundur ke coin unbounded. Keduanya "mengisi tabel", tetapi DAG-nya berbeda.

**Kompleksitas:** memilih urutan tidak menambah waktu asimptotik. Salah urutan tidak TLE; ia WA diam.

---

## Pull versus push

**Teori:** Ada dua gaya menulis transisi. Pull: berdiri di `i`, menarik nilai dari pendahulu `i-1`, `i-2`, .... Push: berdiri di `j` yang sudah final, mendorong kandidat ke `j+1`, `j+2`, .... Secara matematika sama. Pull lebih dekat ke rekurens. Push lebih alami saat dari satu state banyak tujuan, misalnya jump game. Push wajib men-skip state yang masih `INF`, supaya `INF + biaya` tidak menular. Pull wajib menginisialisasi `dp[i] = INF` (untuk min) sebelum mengambil minimum.

**Kapan pull:** rumus `dp[i] = min/max/sum atas j < i`. **Kapan push:** dari `i` kita tahu daftar tujuan. **Tidak:** mencampur keduanya di loop yang sama tanpa alasan.

**STATE:** `dp[i]` tetap "biaya minimum mencapai batu `i`", independen dari gaya tulis.

**TRANSISI pull:** `dp[i] = min(dp[i-1] + |h[i]-h[i-1]|, dp[i-2] + |h[i]-h[i-2]|)`.

**TRANSISI push:** dari `i` yang sudah punya `dp[i]`, perbarui `dp[i+1]` dan `dp[i+2]`.

**BASIS:** `dp[0] = 0`. State lain `INF` pada kedua gaya.

**Proses:** `h = [10, 30, 40, 20]`.

```
Pull
i=1  min(INF, 0+|30-10|) = 20
i=2  min(20+|40-30|, 0+|40-10|) = 30
i=3  min(30+|20-40|, 20+|20-30|) = 30

Push, awal [0, INF, INF, INF]
dari 0: dp[1]=20, dp[2]=30
dari 1: dp[2]=min(30,20+10)=30, dp[3]=20+10=30
dari 2: dp[3]=min(30,30+20)=30
dari 3: tidak ada tujuan
```

Hasil sama. Jalur `0 -> 1 -> 3` biaya 30.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll frogPull(const vector<ll>& h) {
    int n = (int)h.size();
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + llabs(h[i] - h[i - 1]);
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + llabs(h[i] - h[i - 2]));
    }
    return dp[n - 1];
}

ll frogPush(const vector<ll>& h) {
    int n = (int)h.size();
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] >= INF) continue;
        if (i + 1 < n) dp[i + 1] = min(dp[i + 1], dp[i] + llabs(h[i + 1] - h[i]));
        if (i + 2 < n) dp[i + 2] = min(dp[i + 2], dp[i] + llabs(h[i + 2] - h[i]));
    }
    return dp[n - 1];
}

int main() {
    FASTIO;
    vector<ll> h = {10, 30, 40, 20};
    cout << frogPull(h) << " " << frogPush(h) << "\n";
    return 0;
}
```

**Jebakan:** push tanpa `if (dp[i] >= INF) continue`. Overflow `INF + |h|` jika `INF = LLONG_MAX`.

**Kompleksitas:** keduanya `O(n)` untuk `k = 2`. Push dengan derajat keluar `k` menjadi `O(nk)`.

---

## Empat uji desain state

**Teori:** Bagian tersulit DP bukan mengetik loop, melainkan merancang STATE. Empat uji dari Day 142 menolak tebakan. Uji 1: bisa dikalimatkan? "Hasil terbaik di i" gagal. Uji 2: cukup informasinya? Masa depan hanya bergantung pada state sekarang (Markov). Uji 3: setara? Dua jalur ke state yang sama punya masa depan yang sama. Uji 4: muat? `|state| × biaya ≤ 10^8` untuk 1–2 detik, dan tabel muat memori. Kalau uji 2 atau 3 gagal, tambah dimensi. Kalau uji 4 gagal, ganti model: rolling, bitset, MITM, atau soal punya struktur lain.

**Kapan:** sebelum baris kode pertama. **Tidak:** menambah dimensi "untuk berjaga-jaga" sampai uji 4 pecah.

**STATE:** kalimat uji 1 adalah definisi resmi yang akan ditulis di komentar atas fungsi.

**TRANSISI:** uji 2 lolos jika keputusan legal berikutnya bisa ditentukan tanpa membaca jalur ke state ini.

**BASIS:** uji 4 dihitung termasuk basis. Tabel `int dp[1000][1000]` kira-kira 4 MB, aman. Tabel `int dp[10000][10000]` kira-kira 400 MB, biasanya RE.

**Proses:** empat percobaan state untuk "liburan tiga aktivitas, tidak boleh sama berturut-turut".

```
Percobaan                         U1 kalimat   U2 Markov   U3 setara   U4 muat
dp[i] = bahagia sampai hari i     lemah        gagal       gagal       ya
dp[i][act] = bahagia jika hari i  kuat         lolos       lolos       3n
  memilih act
dp[i] plus string seluruh act     kuat         lolos       lolos       3^i gagal
dp[i][prev][sisaHari]             berlebih     lolos       lolos       n*3*n boros
```

Hanya baris kedua yang lolos keempat uji dengan hemat.

Contoh uji 3 gagal: tiket diskon. Jalur A tiba di kota `u` dengan kupon utuh. Jalur B tiba lebih murah tetapi kupon habis. Menggabungkan keduanya ke `dp[u]` membuang jalur A, padahal A bisa lebih murah di masa depan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool ujiMuat(ll nState, ll biaya) {
    return nState > 0 && nState <= 100000000LL / max(1LL, biaya);
}

ll vacation(const vector<array<ll, 3>>& a) {
    int n = (int)a.size();
    vector<array<ll, 3>> dp(n);
    dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = a[i][0] + max(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = a[i][1] + max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = a[i][2] + max(dp[i - 1][0], dp[i - 1][1]);
    }
    return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}

int main() {
    FASTIO;
    vector<array<ll, 3>> a = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    cout << ujiMuat((int)a.size() * 3, 1) << " " << vacation(a) << "\n"; // 1 210
    return 0;
}
```

**Jebakan:** lolos uji 1 dengan kalimat kabur. "dp[i][j] adalah hasil terbaik" bukan kalimat. Sebut apa `i`, apa `j`, wajib atau boleh.

**Kompleksitas:** vacation `O(n)` waktu, `O(n)` memori, atau `O(1)` memori jika hanya tiga variabel kemarin disimpan.

---

## Frog jump: top-down dan bottom-up

**Teori:** Katak di batu 0 ingin ke `n-1`. Lompat 1 atau 2 batu, biaya `|h[i]-h[j]|`. Soal ini adalah laboratorium Day 142 karena rekurensnya pendek, jejaknya pendek, dan kedua paradigma terlihat. Top-down dari batu terakhir menarik batu `i-1` dan `i-2`. Cache `memo[i] = -1` aman karena biaya tidak negatif. Bottom-up mengisi dari batu 0. Jawaban 30 pada `h = [10, 30, 40, 20]` harus keluar dari kedua fungsi.

**Kapan:** AtCoder DP-A, atau sebagai kerangka sebelum menambah `k` (DP-B di file 03). **Tidak:** greedy "loncat ke tinggi paling mirip" sebagai pengganti.

**STATE:** `dp[i]` adalah biaya minimum untuk sampai di batu `i` dari batu 0.

**TRANSISI:** `dp[i] = min(dp[i-1] + |h[i]-h[i-1]|, dp[i-2] + |h[i]-h[i-2]|)` jika `i >= 2`.

**BASIS:** `dp[0] = 0` karena sudah berada di start tanpa lompatan.

**Proses:** jejak top-down `solve(3)`, `h = [10, 30, 40, 20]`.

```
solve(3) cache miss
  solve(2) cache miss
    solve(1) cache miss
      solve(0) = 0
      memo[1] = 0+|30-10| = 20
    dari 1: 20+|40-30| = 30
    dari 0: 0+|40-10| = 30
    memo[2] = 30
  dari 2: 30+|20-40| = 50
  solve(1) HIT 20
  dari 1: 20+|20-30| = 30
  memo[3] = 30
```

Jejak bottom-up:

```
i    dari i-1              dari i-2              dp[i]
0    —                     —                     0
1    0+20=20               —                     20
2    20+10=30              0+30=30               30
3    30+20=50              20+10=30              30
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll frogTopDown(int i, const vector<ll>& h, vector<ll>& memo) {
    if (i == 0) return 0;
    if (memo[i] != -1) return memo[i];
    ll ans = frogTopDown(i - 1, h, memo) + llabs(h[i] - h[i - 1]);
    if (i >= 2) ans = min(ans, frogTopDown(i - 2, h, memo) + llabs(h[i] - h[i - 2]));
    return memo[i] = ans;
}

ll frogBottomUp(const vector<ll>& h) {
    int n = (int)h.size();
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + llabs(h[i] - h[i - 1]);
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + llabs(h[i] - h[i - 2]));
    }
    return dp[n - 1];
}

int main() {
    FASTIO;
    vector<ll> h = {10, 30, 40, 20};
    int n = (int)h.size();
    vector<ll> memo(n, -1);
    cout << frogTopDown(n - 1, h, memo) << " " << frogBottomUp(h) << "\n";
    return 0;
}
```

**Jebakan:** inisialisasi `dp` dengan 0 pada bottom-up min. Top-down tanpa `i == 0`. Stack pada `n = 1e5`.

**Kompleksitas:** `O(n)` waktu. Top-down `O(n)` heap plus `O(n)` stack. Bottom-up `O(n)` atau `O(1)` memori.

---

## Menambah dimensi: liburan

**Teori:** Uji 2 gagal jika masa depan butuh informasi yang tidak ada di indeks. AtCoder DP-C: setiap hari pilih aktivitas A, B, atau C, tidak boleh sama dengan kemarin. `dp[i]` = kebahagiaan sampai hari `i` tidak tahu kemarin, jadi tidak tahu mana yang haram. Perbaikan: `dp[i][act]` = kebahagiaan sampai hari `i` jika hari `i` memilih `act`. Transisi mengambil maksimum dari dua aktivitas lain. Ini pola umum: constraint "tidak boleh X berturut-turut" hampir selalu menambah dimensi `X` terakhir.

**Kapan:** ada larangan yang bergantung pada pilihan kemarin, bukan hanya pada "sudah sampai i". **Tidak:** kalau larangannya sudah terwakili oleh "ambil atau lewati" seperti house robber.

**STATE:** `dp[i][act]` adalah kebahagiaan maksimum untuk hari `0..i` jika aktivitas hari `i` tepat `act`.

**TRANSISI:** `dp[i][A] = a[i][A] + max(dp[i-1][B], dp[i-1][C])`, dan cyclic untuk B serta C.

**BASIS:** `dp[0][act] = a[0][act]` karena hari pertama bebas.

**Proses:** tiga hari, poin

```
hari0: 10 40 70
hari1: 20 50 80
hari2: 30 60 90
```

```
          A    B    C
dp[0]     10   40   70
dp[1] A   20+max(40,70)=90
      B   50+max(10,70)=120
      C   80+max(10,40)=120
dp[2] A   30+max(120,120)=150
      B   60+max(90,120)=180
      C   90+max(90,120)=210
```

Jawaban 210. Urutan `C, B, C` yaitu 70 + 50 + 90. `C, C, C` haram dan tidak pernah muncul di tabel.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll vacation(const vector<array<ll, 3>>& a) {
    int n = (int)a.size();
    ll x = a[0][0], y = a[0][1], z = a[0][2];
    for (int i = 1; i < n; i++) {
        ll nx = a[i][0] + max(y, z);
        ll ny = a[i][1] + max(x, z);
        ll nz = a[i][2] + max(x, y);
        x = nx;
        y = ny;
        z = nz;
    }
    return max({x, y, z});
}

int main() {
    FASTIO;
    vector<array<ll, 3>> a = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    cout << vacation(a) << "\n"; // 210
    return 0;
}
```

**Jebakan:** `dp[i] = max(A,B,C) + max poin hari i` tanpa menolak aktivitas sama. Menugaskan `x = ... + max(y,z)` sambil `y` sudah tertimpa.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori setelah digulung.

---

## Menambah dimensi: tiket diskon

**Teori:** Uji 3 gagal jika dua jalur ke simpul yang sama tidak setara. Cari jalur termurah, satu kupon memotong satu sisi 50 persen. `dp[u]` mencatat satu angka. Jalur yang lebih mahal tetapi masih memegang kupon bisa kalah di `u`, lalu menang di `t`. State yang benar: `dp[u][k]` = biaya minimum tiba di `u` dengan sisa kupon `k`. Ini pola "resource yang mengubah masa depan harus masuk state". Kupon, cooldown saham, sisa skip, sisa modulo, semuanya dimensi.

**Kapan:** ada satu atau beberapa resource diskrit yang belum terpakai. **Tidak:** resource yang sudah bisa diringkas ke nilai saja, misalnya "sudah mengambil atau belum" pada 0-1 yang diwakili baris barang.

**STATE:** `dp[u][k]` adalah biaya minimum mencapai kota `u` dengan sisa `k` kupon, `k` bernilai 0 atau 1 pada soal satu tiket.

**TRANSISI:** dari `(u, k)` lewat sisi `u -> v` berbiaya `w`: tanpa kupon `dp[v][k] = min(..., dp[u][k] + w)`; dengan kupon jika `k >= 1` maka `dp[v][k-1] = min(..., dp[u][k] + w/2)`.

**BASIS:** `dp[sumber][1] = 0` jika kita mulai dengan satu kupon. `dp[sumber][0]` biasanya `INF` kecuali kupon boleh dibuang.

**Proses:** tiga kota, sisi `0-1` biaya 10, `1-2` biaya 10, `0-2` biaya 18. Satu kupon 50 persen.

```
Tanpa dimensi kupon, Dijkstra biasa:
0 --10--> 1 --10--> 2   total 20
0 --18--> 2             total 18  <- "terbaik" ke 2

Dengan kupon di sisi 0-1:
bayar 5, tiba di 1 dengan k=0, lalu 10, total 15 ke 2. Lebih baik.
Dengan kupon di sisi 1-2: 10 + 5 = 15.
Dengan kupon di sisi 0-2: 9.
Jawaban 9.
```

Tabel:

```
state     biaya
(0,1)     0
(1,1)     10   (tanpa kupon)
(1,0)     5    (kupon di 0-1)
(2,1)     18   (tanpa kupon lewat 0-2)
(2,0)     9    (kupon di 0-2)  <- jawaban
```

Kalau `dp[2]` hanya menyimpan 18 dulu dari jalur tanpa kupon yang kebetulan dievaluasi salah, kita kehilangan 9.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll tiketDiskon(int n, const vector<vector<pair<int, ll>>>& g) {
    vector<array<ll, 2>> dp(n, {INF, INF});
    dp[0][1] = 0;
    using T = tuple<ll, int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, 0, 1});
    while (!pq.empty()) {
        auto [cost, u, k] = pq.top();
        pq.pop();
        if (cost != dp[u][k]) continue;
        for (auto [v, w] : g[u]) {
            if (dp[v][k] > cost + w) {
                dp[v][k] = cost + w;
                pq.push({dp[v][k], v, k});
            }
            if (k && dp[v][k - 1] > cost + w / 2) {
                dp[v][k - 1] = cost + w / 2;
                pq.push({dp[v][k - 1], v, k - 1});
            }
        }
    }
    return min(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
    FASTIO;
    int n = 3;
    vector<vector<pair<int, ll>>> g(n);
    g[0] = {{1, 10}, {2, 18}};
    g[1] = {{2, 10}};
    cout << tiketDiskon(n, g) << "\n"; // 9
    return 0;
}
```

**Jebakan:** memotong 50 persen dengan `w / 2` pada `int` ganjil tanpa aturan soal. Mencatat `dp[u]` saja lalu "kalau masih ada kupon, potong sisi terakhir" secara greedy.

**Kompleksitas:** Dijkstra pada `n * 2` state, `O((n + m) log n)` untuk satu kupon.

---

## Rolling array

**Teori:** Jika `dp[i]` hanya membaca sejumlah tetap state lama, tabel penuh tidak wajib. Fibonacci dan frog `k = 2` cukup dua variabel. House robber sama. Rolling menghapus riwayat, jadi rekonstruksi jalur hilang. Kalau soal minta barisan batu atau rumah, simpan tabel atau array `par[]`. Urutan penugasan mutlak: hitung `cur` dulu, baru geser `prev2 = prev1`, `prev1 = cur`. Terbalik, kedua variabel merujuk nilai yang sama.

**Kapan:** transisi jendela tetap dan soal hanya minta angka. **Tidak:** butuh `par[]`, atau jendela `k` sampai `n`.

**STATE:** `prev1` adalah `dp[i-1]`, `prev2` adalah `dp[i-2]`, keduanya menurut definisi `dp` yang sama.

**TRANSISI:** `cur = gabungan(prev1, prev2)`, lalu geser jendela satu langkah.

**BASIS:** `prev2` dan `prev1` diisi dari `dp[0]` dan `dp[1]` yang dihitung manual.

**Proses:** frog `h = [10, 30, 40, 20]`.

```
awal   prev2=0 (batu 0)   prev1=20 (batu 1)
i=2    cur=min(20+10, 0+30)=30    prev2=20  prev1=30
i=3    cur=min(30+20, 20+10)=30    prev2=30  prev1=30
jawab  30
```

Kalau `prev1 = cur` dulu, `prev2 = prev1` menyalin `cur`, jejak batu 1 hilang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll frogRolling(const vector<ll>& h) {
    int n = (int)h.size();
    if (n <= 1) return 0;
    ll prev2 = 0;
    ll prev1 = llabs(h[1] - h[0]);
    for (int i = 2; i < n; i++) {
        ll cur = min(prev1 + llabs(h[i] - h[i - 1]), prev2 + llabs(h[i] - h[i - 2]));
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    FASTIO;
    cout << frogRolling({10, 30, 40, 20}) << "\n";
    return 0;
}
```

**Jebakan:** rolling pada soal yang minta jalur. `n = 1` mengakses `h[1]`.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori.

---

## Stack overflow dan multi-test

**Teori:** Setiap panggilan fungsi memakai stack frame. Judge sering memberi stack 8 MB, kadang 1 MB. Kedalaman `10^5` pada rekursi linear mudah SIGSEGV meski memory limit soal 256 MB. Aturan praktis: `n ≤ 10^4` top-down aman, `10^4..10^5` waspada, `> 10^5` wajib bottom-up. Multi-test menambah jebakan kedua: cache global sisa tes lama. Reset dengan `assign(n+1, -1)` per tes, bukan sekali di luar loop `T`.

**Kapan:** baca constraint `n` dan `T` sebelum memilih paradigma. **Tidak:** menaikkan stack di lokal lalu lupa bahwa judge tidak memakai flag yang sama.

**STATE:** kedalaman rekursi kira-kira jarak terpanjang dari target ke basis di DAG. Pada Fibonacci top-down kiri-dulu, kedalaman `n`.

**TRANSISI:** setiap panggilan menambah satu frame sampai basis atau cache hit.

**BASIS:** cache hit tidak menambah kedalaman di bawahnya.

**Proses:** perkiraan memori stack.

```
kedalaman    ~64 byte/frame    total
1000         64 KB             aman
10000        640 KB            biasanya aman
100000       6.4 MB            berbahaya di 8 MB
200000       12.8 MB           RE hampir pasti
```

Skenario multi-test:

```
Tes 1: n=3, memo terisi [0,1,1,2]
Tes 2: n=4, lupa reset
       memo[3] masih 2 dari tes 1
       kalau soal berbeda (bukan fib murni), WA
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll fibMemo(int n, vector<ll>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = (fibMemo(n - 1, memo) + fibMemo(n - 2, memo)) % MOD;
}

ll fibTab(int n) {
    if (n <= 1) return n;
    ll dua = 0, satu = 1;
    for (int i = 2; i <= n; i++) {
        ll kini = (dua + satu) % MOD;
        dua = satu;
        satu = kini;
    }
    return satu;
}

int main() {
    FASTIO;
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        if (n > 10000) {
            cout << fibTab(n) << "\n";
        } else {
            vector<ll> memo(n + 1, -1);
            cout << fibMemo(n, memo) << "\n";
        }
    }
    return 0;
}
```

**Jebakan:** `static vector<ll> memo` yang tidak di-assign ulang. Membaca `n = 1e6` lalu `fibMemo(n)` "karena lebih natural".

**Kompleksitas:** memilih bottom-up tidak mengubah `O(n)` waktu; ia menghapus risiko `O(n)` stack.

---

Day 142 selesai jika kamu bisa menulis ulang frog dengan kedua paradigma, menjelaskan kenapa `-1` dipakai, mengisi DAG dari basis, dan menjalankan empat uji pada state baru. Lanjut ke [03 — linear 1D](03-linear-1d.md) untuk tangga, house robber, frog, Kadane, dan jump game.
