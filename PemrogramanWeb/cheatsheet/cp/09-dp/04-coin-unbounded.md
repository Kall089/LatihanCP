# 04 — Coin change dan unbounded knapsack

[← Linear 1D](03-linear-1d.md) · [← 09-dp](README.md) · [0-1 knapsack →](05-01-knapsack.md)

Day ComprogLearning: **144**. Setiap koin atau barang boleh dipakai berkali-kali. Satu arah loop memisahkan soal ini dari 0-1.

> **Ide satu kalimat:** loop kapasitas **maju** mengizinkan barang yang sama dipakai lagi; greedy pecahan terbesar gagal pada sistem non-kanonik.

## Daftar isi

- [Unbounded versus 0-1](#unbounded-versus-0-1)
- [Coin change minimum](#coin-change-minimum)
- [Greedy gagal pada {1,3,4} target 6](#greedy-gagal-pada-134-target-6)
- [Rekonstruksi koin](#rekonstruksi-koin)
- [Kombinasi versus permutasi](#kombinasi-versus-permutasi)
- [Unbounded knapsack](#unbounded-knapsack)
- [Hukum arah loop](#hukum-arah-loop)

---

## Unbounded versus 0-1

**Teori:** Keluarga knapsack dibedakan oleh stok. 0-1: tiap jenis paling banyak sekali. Bounded: stok `c[i]` terbatas. Unbounded: stok tak hingga, atau setidaknya `floor(W / w[i])`. Coin change adalah unbounded yang nilai barangnya sama dengan berat, dan yang dioptimalkan adalah jumlah koin atau banyak cara. Di kehidupan, laci kasir tidak kehabisan pecahan 1000. Di kontes, pecahan hampir selalu arbitrer, jadi greedy kanonik tidak boleh diasumsikan.

**Kapan:** soal berkata "boleh dipakai berkali-kali", "stok tak terbatas", atau "koin pecahan". **Tidak:** tiap barang unik (0-1, file 05), atau stok tertulis terbatas (file 07).

**STATE:** `dp[w]` adalah jawaban terbaik (min koin, max nilai, atau banyak cara) untuk kapasitas atau nominal tepat `w` setelah jenis yang sudah dilooping boleh diulang.

**TRANSISI:** dari `w - item` kita menambah satu salinan item yang sama, karena `dp[w - item]` sudah boleh memuat item itu.

**BASIS:** `dp[0] = 0` untuk min/max nilai, `dp[0] = 1` untuk banyak cara.

**Proses:** satu barang berat 2 nilai 3, `W = 6`.

```
Loop maju (unbounded)
w    rumus              dp[w]
0    basis              0
2    0+3                3
4    3+3                6
6    6+3                9     tiga kali barang

Loop mundur (0-1)
w=6  dp[4]+3, dp[4] masih 0 -> 3
w=4  dp[2]+3, dp[2] masih 0 -> 3
w=2  dp[0]+3 -> 3
hasil 3, satu kali barang
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll unboundedSatuBarang(int W, int wt, ll val) {
    vector<ll> dp(W + 1, 0);
    for (int w = wt; w <= W; w++) dp[w] = max(dp[w], dp[w - wt] + val);
    return dp[W];
}

ll zeroOneSatuBarang(int W, int wt, ll val) {
    vector<ll> dp(W + 1, 0);
    for (int w = W; w >= wt; w--) dp[w] = max(dp[w], dp[w - wt] + val);
    return dp[W];
}

int main() {
    FASTIO;
    cout << unboundedSatuBarang(6, 2, 3) << " " << zeroOneSatuBarang(6, 2, 3) << "\n";
    // 9 3
    return 0;
}
```

**Jebakan:** menyalin loop 0-1 ke soal koin. Gejalanya: jawaban terlalu kecil, seolah tiap koin sekali.

**Kompleksitas:** `O(W)` untuk satu jenis, `O(n W)` untuk `n` jenis.

---

## Coin change minimum

**Teori:** Diberi pecahan `C` dan target `X`. Cari jumlah koin paling sedikit yang jumlahnya tepat `X`. Jika mustahil, laporkan `-1`. State `dp[v]` = min koin untuk nominal tepat `v`. Transisi: koin terakhir `c` memberi `dp[v-c] + 1`. Inisialisasi `INF`, basis `0`. Jangan menambah `1` ke `INF`. Rupiah dan dolar sering kanonik; soal CP hampir tidak.

**Kapan:** "jumlah koin minimum", stok tak terbatas. **Tidak:** tiap koin fisik sekali (0-1), atau "berapa cara" (bagian kombinasi).

**STATE:** `dp[v]` adalah jumlah koin minimum untuk membentuk nominal tepat `v`; nilai `INF` berarti belum bisa.

**TRANSISI:** `dp[v] = min atas koin c ≤ v dari (dp[v-c] + 1)`, hanya jika `dp[v-c]` bukan `INF`.

**BASIS:** `dp[0] = 0`. Lainnya `INF`.

**Proses:** koin `{1, 3, 4}`, `X = 6`. Tabel ini wajib hafal.

```
v    c=1           c=3           c=4           min    isi khas
0    —             —             —             0      {}
1    0+1=1         —             —             1      {1}
2    1+1=2         —             —             2      {1,1}
3    2+1=3         0+1=1         —             1      {3}
4    1+1=2         1+1=2         0+1=1         1      {4}
5    1+1=2         2+1=3         1+1=2         2      {4,1}
6    2+1=3         1+1=2         2+1=3         2      {3,3}
```

Jawaban `dp[6] = 2`. Greedy `4+1+1 = 3` kalah.

Target 2 tanpa koin 1, koin `{3, 4}`: semua tetap `INF`, fungsi mengembalikan `-1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int INF = 1e9;

int coinChangeMin(const vector<int>& koin, int target) {
    vector<int> dp(target + 1, INF);
    dp[0] = 0;
    for (int v = 1; v <= target; v++)
        for (int k : koin)
            if (k <= v && dp[v - k] != INF)
                dp[v] = min(dp[v], dp[v - k] + 1);
    return dp[target] == INF ? -1 : dp[target];
}

int main() {
    FASTIO;
    cout << coinChangeMin({1, 3, 4}, 6) << "\n"; // 2
    cout << coinChangeMin({3, 4}, 2) << "\n";    // -1
    cout << coinChangeMin({1, 3, 4}, 0) << "\n"; // 0
    return 0;
}
```

**Jebakan:**

1. `INF = INT_MAX` lalu `INF + 1` overflow menjadi negatif.
2. Tidak mengembalikan `-1` saat mustahil.
3. Loop mundur (itu 0-1).
4. `dp[0] = INF`.

**Kompleksitas:** `O(n · X)` waktu, `O(X)` memori.

---

## Greedy gagal pada {1,3,4} target 6

**Teori:** Greedy "selalu ambil pecahan terbesar yang muat" benar hanya pada sistem kanonik. Bukti penyangkal cukup satu contoh. `{1, 3, 4}` target 6: greedy mengambil 4, sisa 2, lalu `1+1`, total 3 koin. DP menemukan `3+3`, total 2 koin. Tidak ada urutan greedy yang menyelamatkan semua target. `{1, 5, 10, 25}` kebetulan aman; jangan mengekstrapolasi. Di kertas, selalu isi tabel sampai target, jangan berhenti di "4 kelihatan bagus".

**Kapan:** setiap kali tergoda greedy koin. **Tidak:** memakai contoh ini sebagai bukti bahwa greedy selalu salah; kanonik tetap ada.

**STATE:** sama dengan `coinChangeMin`: `dp[v]` min koin untuk `v`.

**TRANSISI:** seluruh koin diuji, bukan hanya yang terbesar.

**BASIS:** `dp[0] = 0`.

**Proses:** bandingkan langkah greedy dan langkah DP berdampingan.

```
Greedy
sisa 6  ambil 4   sisa 2
sisa 2  ambil 1   sisa 1
sisa 1  ambil 1   sisa 0
koin: 4,1,1     jumlah 3

DP mengisi semua v
v=3  lebih baik pakai 3 daripada 1+1+1
v=4  lebih baik pakai 4
v=6  kandidat 1+dp[5]=3, 3+dp[3]=2, 4+dp[2]=3
     pemenang 3+3
```

Pohon keputusan target 6:

```
6
├── +4 -> 2 -> +1 -> 1 -> +1 -> 0    (3 koin)
├── +3 -> 3 -> +3 -> 0               (2 koin)  optimal
└── +1 -> 5 -> ...                   (>=2, tidak lebih baik)
```

Greedy hanya menelusuri cabang pertama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int INF = 1e9;

int greedyCoin(vector<int> koin, int target) {
    sort(koin.rbegin(), koin.rend());
    int cnt = 0;
    for (int k : koin) {
        if (k <= 0) continue;
        int pakai = target / k;
        cnt += pakai;
        target -= pakai * k;
    }
    return target == 0 ? cnt : INF;
}

int coinChangeMin(const vector<int>& koin, int target) {
    vector<int> dp(target + 1, INF);
    dp[0] = 0;
    for (int v = 1; v <= target; v++)
        for (int k : koin)
            if (k <= v && dp[v - k] != INF)
                dp[v] = min(dp[v], dp[v - k] + 1);
    return dp[target] == INF ? -1 : dp[target];
}

int main() {
    FASTIO;
    vector<int> c = {1, 3, 4};
    cout << greedyCoin(c, 6) << " " << coinChangeMin(c, 6) << "\n"; // 3 2
    return 0;
}
```

**Jebakan:** menguji greedy hanya pada target yang kebetulan optimal, misalnya target 4. Selalu uji 6.

**Kompleksitas:** greedy `O(n log n)` sort plus `O(n)`, tetapi salah. DP `O(n X)` dan benar.

---

## Rekonstruksi koin

**Teori:** Mengetahui `dp[X] = 2` belum cukup jika soal minta pecahannya. Array `pick[v]` mencatat koin terakhir yang memperbaiki `v`. Dari `X` berjalan `v -= pick[v]` sampai 0. Urutan pecahan yang tercetak bergantung pada urutan loop koin; jumlahnya tetap minimum. Jika ada beberapa optimal, `pick` menyimpan yang terakhir (atau pertama, jika kita memakai `<` ketat).

**Kapan:** soal minta daftar koin, bukan hanya angka. **Tidak:** rolling tanpa `pick` lalu diminta daftar.

**STATE:** `pick[v]` adalah pecahan `c` yang dipakai sebagai koin terakhir pada sebuah solusi optimal untuk `v`, atau `-1` jika `v` mustahil.

**TRANSISI:** jika `dp[v-c] + 1 < dp[v]` maka `dp[v] = dp[v-c] + 1` dan `pick[v] = c`.

**BASIS:** `pick[0]` tidak dipakai. `dp[0] = 0`.

**Proses:** `{1, 3, 4}`, target 6, koin diuji 1 lalu 3 lalu 4.

```
v   dp  pick   catatan
0   0   -1
1   1    1
2   2    1
3   1    3     3 mengalahkan 1+1+1
4   1    4
5   2    1     4+1, pick=1 (setelah 4 juga 2, tergantung < atau <=)
6   2    3     3+dp[3]
```

Jejak: `6 --pick 3--> 3 --pick 3--> 0`. Daftar `{3, 3}`.

Kalau `pick[5] = 4` (karena `4+1` ditulis dulu), jejak 5 menjadi `{4, 1}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int INF = 1e9;

pair<int, vector<int>> coinChangeReconstruct(const vector<int>& koin, int target) {
    if (target == 0) return {0, {}};
    vector<int> dp(target + 1, INF), pick(target + 1, -1);
    dp[0] = 0;
    for (int v = 1; v <= target; v++)
        for (int c : koin)
            if (c <= v && dp[v - c] != INF && dp[v - c] + 1 < dp[v]) {
                dp[v] = dp[v - c] + 1;
                pick[v] = c;
            }
    if (dp[target] == INF) return {-1, {}};
    vector<int> isi;
    for (int cur = target; cur > 0; cur -= pick[cur]) isi.push_back(pick[cur]);
    return {dp[target], isi};
}

int main() {
    FASTIO;
    auto [cnt, isi] = coinChangeReconstruct({1, 3, 4}, 6);
    cout << cnt << " :";
    for (int c : isi) cout << " " << c;
    cout << "\n";
    return 0;
}
```

**Jebakan:** `cur -= pick[cur]` saat `pick[cur] = -1` (mustahil) membuat loop tak hingga. Cek `dp[target]` dulu.

**Kompleksitas:** isi tabel `O(n X)`, rekonstruksi `O(jumlah koin) ≤ O(X)`.

---

## Kombinasi versus permutasi

**Teori:** "Berapa cara" bukan "berapa koin". Urutan loop membedakan **kombinasi** (urutan diabaikan: `{1,2} = {2,1}`) dan **permutasi** (urutan dihitung). Koin di luar, nominal maju: kombinasi. CSES Coin Combinations II dan LeetCode 518. Nominal di luar, koin di dalam: permutasi. CSES Coin Combinations I. `dp[0] = 1` wajib: satu cara tidak mengambil apa pun. Lupa modulo pada `n` besar. Loop mundur pada unbounded mengubahnya jadi 0-1 counting.

**Kapan:** soal "number of ways" dengan koin tak terbatas. **Tidak:** stok tiap koin 1 — itu subset sum counting.

**STATE:** `dp[v]` adalah banyaknya cara membentuk nominal `v`; arti "cara" mengikuti urutan loop.

**TRANSISI kombinasi:** untuk setiap koin `c`, untuk `v = c..X`: `dp[v] += dp[v-c]`.

**TRANSISI permutasi:** untuk setiap `v`, untuk setiap koin: `dp[v] += dp[v-c]`.

**BASIS:** `dp[0] = 1`.

**Proses:** koin `{1, 2}`, `X = 3`.

Kombinasi, koin luar:

```
awal          dp = [1, 0, 0, 0]
setelah c=1   [1, 1, 1, 1]     hanya 1+1+1
c=2, v=2      dp[2] += dp[0] -> 2
c=2, v=3      dp[3] += dp[1] -> 2
cara: {1,1,1}, {1,2}
jawaban 2
```

Permutasi, nominal luar:

```
v=1  +1 -> 1                 (1)
v=2  +1 -> dp[1]=1; +2 -> dp[0]=1; total 2    (1+1, 2)
v=3  +1 -> dp[2]=2; +2 -> dp[1]=1; total 3    (1+1+1, 1+2, 2+1)
jawaban 3
```

Uji wajib: `{1,2} -> 3` memberi 2 versus 3. Kalau kodemu sama di kedua fungsi, loop tertukar atau identik.

Trace kombinasi `{1, 3, 4}` target 6:

```
c=1: dp = [1,1,1,1,1,1,1]
c=3: v=3 -> 2, v=4 -> 2, v=5 -> 2, v=6 -> 2
c=4: v=4 -> 3, v=5 -> 3, v=6 -> 4
```

Empat kombinasi: `1+1+1+1+1+1`, `1+1+1+3`, `3+3`, `1+1+4`. Tidak ada `4+1+1` sebagai cara baru.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll coinKombinasi(const vector<int>& koin, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    for (int k : koin)
        for (int v = k; v <= target; v++)
            dp[v] = (dp[v] + dp[v - k]) % MOD;
    return dp[target];
}

ll coinPermutasi(const vector<int>& koin, int target) {
    vector<ll> dp(target + 1, 0);
    dp[0] = 1;
    for (int v = 1; v <= target; v++)
        for (int k : koin)
            if (k <= v) dp[v] = (dp[v] + dp[v - k]) % MOD;
    return dp[target];
}

int main() {
    FASTIO;
    vector<int> c = {1, 2};
    cout << coinKombinasi(c, 3) << " " << coinPermutasi(c, 3) << "\n"; // 2 3
    cout << coinKombinasi({1, 3, 4}, 6) << "\n"; // 4
    return 0;
}
```

**Jebakan:** tertukar CSES I dan II. Lupa `dp[0] = 1`. Lupa modulo. Loop mundur.

**Kompleksitas:** `O(n · X)` waktu, `O(X)` memori.

---

## Unbounded knapsack

**Teori:** Tiap barang stok tak terbatas, maksimalkan nilai tanpa melebihi `W`. Coin min adalah kasus khusus: nilai = -1 per koin, berat = pecahan, wajib tepat. Di sini kapasitas boleh tidak penuh, jadi sisa diisi 0. Loop maju per barang. Jika wajib tepat dan kita meminimalkan biaya, inisialisasi `INF` kecuali `dp[0]`.

**Kapan:** "boleh ambil berkali-kali", produksi tanpa batas. **Tidak:** tiap barang unik.

**STATE:** `dp[w]` adalah nilai maksimum dengan kapasitas paling banyak `w` setelah jenis yang sudah dilooping boleh diulang.

**TRANSISI:** untuk barang `(wt, val)`, untuk `w = wt..W` maju: `dp[w] = max(dp[w], dp[w-wt] + val)`.

**BASIS:** `dp[0] = 0`. Lainnya 0 jika tidak wajib penuh.

**Proses:** barang `(2, 3)` dan `(3, 4)`, `W = 8`. Loop maju, barang pertama dulu.

```
awal      [0 0 0 0 0 0 0 0 0]
+(2,3)    w=2:3  w=4:6  w=6:9  w=8:12
          [0 0 3 3 6 6 9 9 12]
```

Barang kedua memakai array itu, `w` dari 3 ke 8:

```
w   tidak ambil   dp[w-3]+4        dp baru
3   3             0+4=4            4
4   6             3+4=7            7
5   6             3+4=7            7
6   9             4+4=8            9     tiga kali 2 menang
7   9             7+4=11           11    satu (3,4) + dua (2,3)
8   12            7+4=11           12    empat kali 2 menang
```

Jawaban `dp[8] = 12`. Satu barang `(2,3)` saja pada `W = 6` memberi 9, seperti bagian awal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll unboundedKnapsackMax(int W, const vector<int>& wt, const vector<ll>& val) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = wt[i]; w <= W; w++)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

ll unboundedMinCost(int W, const vector<int>& wt, const vector<ll>& cost) {
    vector<ll> dp(W + 1, INF);
    dp[0] = 0;
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = wt[i]; w <= W; w++)
            if (dp[w - wt[i]] < INF)
                dp[w] = min(dp[w], dp[w - wt[i]] + cost[i]);
    return dp[W] == INF ? -1 : dp[W];
}

int main() {
    FASTIO;
    cout << unboundedKnapsackMax(6, {2}, {3}) << "\n"; // 9
    cout << unboundedKnapsackMax(8, {2, 3}, {3, 4}) << "\n"; // 12
    cout << unboundedMinCost(6, {1, 3, 4}, {1, 1, 1}) << "\n"; // 2
    return 0;
}
```

**Jebakan:** loop mundur. Tidak cek `INF` sebelum menambah. `int` overflow nilai. Mengambil `dp[W]` padahal soal "paling banyak W" sudah benar dengan inisialisasi 0; soal "tepat W" butuh `INF`.

**Kompleksitas:** `O(n · W)` waktu, `O(W)` memori.

---

## Hukum arah loop

**Teori:** Satu kata — maju atau mundur — mengubah keluarga masalah. Maju: `dp[w - wt]` sudah memuat barang berjalan, jadi barang itu boleh masuk lagi. Mundur: `dp[w - wt]` masih milik barang-barang sebelumnya, jadi barang berjalan paling banyak sekali. Kombinasi koin memakai maju plus koin di luar. Permutasi memakai nominal di luar, yang secara tak langsung juga maju per nominal. 0-1 dan subset sum memakai mundur. Bounded paket biner memakai mundur per paket. Hafalkan tabel, lalu uji dengan satu barang `(2,3)` `W=6`.

**Kapan:** setiap kali menulis `for (int w = ...)` pada array 1D kapasitas. **Tidak:** menebak arah dari "kebiasaan kemarin".

**STATE:** `dp[w]` setelah loop barang `i` berarti "barang `0..i` sudah diputuskan", dengan aturan ulang yang ditentukan arah.

**TRANSISI:** arah loop adalah bagian dari transisi, bukan detail implementasi.

**BASIS:** `dp[0]` tidak bergantung arah; yang bergantung adalah `w > 0`.

**Proses:** matriks keputusan.

```
Masalah                    loop luar     loop kapasitas     uji (2,3) W=6
unbounded max              barang        maju               9
0-1 max                    barang        mundur             3
coin min                   nominal atau barang   maju       3 kali? berat 2 target 6 -> 3
kombinasi                  koin          maju               —
permutasi                  nominal       (koin dalam)       —
subset sum                 elemen        mundur             2 tidak menyala dari satu 3? n/a
bounded paket              paket         mundur             —
```

Uji tangan wajib sebelum submit:

```
satu item wt=2 val=3 W=6
maju   -> 9
mundur -> 3
kalau kodemu 9 pada soal 0-1, arah salah
kalau kodemu 3 pada soal unbounded, arah salah
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll isi(int W, int wt, ll val, bool maju) {
    vector<ll> dp(W + 1, 0);
    if (maju) {
        for (int w = wt; w <= W; w++) dp[w] = max(dp[w], dp[w - wt] + val);
    } else {
        for (int w = W; w >= wt; w--) dp[w] = max(dp[w], dp[w - wt] + val);
    }
    return dp[W];
}

int main() {
    FASTIO;
    cout << isi(6, 2, 3, true) << " " << isi(6, 2, 3, false) << "\n"; // 9 3
    return 0;
}
```

**Jebakan:** dua barang, loop barang di dalam kapasitas. Itu mencampur jenis di setiap `w` dengan cara yang sulit dikontrol. Tetap: barang atau koin sebagai unit keputusan di loop luar, kecuali permutasi yang memang ingin mencampur urutan.

**Kompleksitas:** arah tidak mengubah `O(n W)`. Ia mengubah arti `dp`.

---

Uji cepat: `{1,3,4}` target 6 min = 2 pecahan `{3,3}`; greedy = 3; `{1,2}` target 3 kombinasi = 2, permutasi = 3; satu barang `(2,3)` `W=6` unbounded = 9, 0-1 = 3. Lanjut ke [05 — 0-1 knapsack](05-01-knapsack.md) untuk loop mundur, tabel 2D, dan rekonstruksi `prev`.
