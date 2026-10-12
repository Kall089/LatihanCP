# 03 — DP linear 1D

[← Top-down / bottom-up](02-topdown-bottomup.md) · [← 09-dp](README.md) · [Coin unbounded →](04-coin-unbounded.md)

Day ComprogLearning: **143**. Empat soal klasik plus jump game adalah satu bentuk: `dp[i]` digabung dari beberapa `dp[j]` dengan `j < i`.

> **Ide satu kalimat:** bedakan "sampai i" (jawaban `dp[n-1]`) dari "berakhir tepat di i" (jawaban `max` / `min` seluruh `dp[i]`).

## Daftar isi

- [Empat pola transisi](#empat-pola-transisi)
- [Sampai i versus berakhir di i](#sampai-i-versus-berakhir-di-i)
- [Naik tangga](#naik-tangga)
- [House robber](#house-robber)
- [Frog jump](#frog-jump)
- [Kadane](#kadane)
- [Jump game](#jump-game)
- [Rolling dan rekonstruksi](#rolling-dan-rekonstruksi)

---

## Empat pola transisi

**Teori:** Climbing stairs, house robber, frog jump, dan Kadane sering diajarkan sebagai empat trik. Semuanya `dp[i] = gabungan atas dp[j], j < i`. Yang berbeda hanya objek, operator, dan jendela. "Berapa cara" menjumlahkan cabang yang saling lepas. "Maksimum" memilih cabang terbaik dengan larangan tetangga. "Minimal biaya / langkah" mengambil `min` plus biaya atau plus satu. "Bisa / tidak" memakai OR. Kalau kamu bisa menurunkan satu dari keputusan terakhir, kamu bisa menurunkan semuanya.

**Kapan:** `n` linear, keputusan hanya melihat ke kiri. **Tidak:** kapasitas, dua string, atau himpunan — itu file berikutnya.

**STATE:** `dp[i]` adalah angka untuk prefiks atau untuk ekor di `i`, jenisnya mengikuti operator: cacah, nilai, biaya, atau boolean.

**TRANSISI:** daftar keputusan terakhir, pastikan saling lepas dan lengkap, lalu pasang `+`, `max`, `min`, atau `||`.

**BASIS:** uji `n = 0` dan `n = 1` di kertas sebelum loop.

**Proses:**

```
Pola              Operator        Contoh                 Jawaban uji
berapa cara       +               tangga n=5             8
maksimum          max             robber [2,1,1,2]       4
minimal biaya     min             frog [10,30,40,20]     30
minimal langkah   min + 1         jump [2,3,1,1,4]       2
bisa / tidak      ||              jump [3,2,1,0,4]       tidak
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll naikTangga(int n) {
    if (n == 0) return 1;
    ll a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

ll houseRobber(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int main() {
    FASTIO;
    cout << naikTangga(5) << " " << houseRobber({2, 1, 1, 2}) << "\n"; // 8 4
    return 0;
}
```

**Jebakan:** menghafal empat rumus lalu menempelkannya tanpa menulis STATE. Operator yang salah mengubah soal menjadi soal lain.

**Kompleksitas:** keempat pola dasar `O(n)` atau `O(nk)`.

---

## Sampai i versus berakhir di i

**Teori:** Ini sumber bug nomor satu di DP 1D. Definisi "sampai i" berarti elemen `i` boleh dipakai atau dilewati; jawaban akhir biasanya `dp[n-1]`. Definisi "berakhir tepat di i" berarti elemen `i` wajib menjadi ekor; jawaban akhir adalah `max` atau `min` atas seluruh `dp[i]`. House robber memakai yang pertama. Kadane dan LIS memakai yang kedua. Mencampurnya membuat tes kecil lolos dan tes besar WA, karena pada array pendek ekor terbaik kebetulan ada di ujung.

**Kapan:** setiap kali kamu menulis `dp[i]`. **Tidak:** menunda keputusan ini sampai debugging.

**STATE:** kalimat STATE wajib memuat frasa "sampai i" atau "berakhir tepat di i".

**TRANSISI:** "sampai i" biasanya `max(dp[i-1], sesuatu + a[i])`. "Berakhir di i" biasanya `max(a[i], dp[i-1] + a[i])` atau `1 + max dp[j]`.

**BASIS:** "sampai i" sering `dp[-1] = 0`. "Berakhir di i" memakai `dp[0] = a[0]`, bukan 0.

**Proses:** array `[2, 1, 1, 2]`.

```
Definisi robber sampai i:
i   dp[i]
0   2
1   2
2   3
3   4          jawaban dp[3]=4

Definisi palsu "berakhir di i" untuk robber:
i   wajib ambil i    nilai
0   2                2
1   1                1
2   1+2=3            3
3   2+2=4            4
max=4, kebetulan sama

Array [5, 1, 2]:
sampai i: 5, 5, 7  -> dp[n-1]=7
berakhir di i jika dipaksa ambil: 5, 1, 7  -> max=7 kebetulan
Array [5, 100, 1]:
sampai i: 5, 100, 100 -> 100 (ambil rumah 1 saja)
kalau salah ambil dp "berakhir" di ujung: 1+5=6  WA
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll sampaiI(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1;
        p1 = c;
    }
    return p1; // dp[n-1]
}

ll berakhirDiI(const vector<ll>& a) {
    ll best = a[0], cur = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best; // max seluruh dp[i]
}

int main() {
    FASTIO;
    cout << sampaiI({5, 100, 1}) << " " << berakhirDiI({5, 100, 1}) << "\n";
    // 100 vs 106 (Kadane, bukan robber)
    return 0;
}
```

**Jebakan:** mencetak `dp[n-1]` pada Kadane atau LIS. Mencetak `max(dp)` pada house robber tanpa alasan; pada robber "sampai i" memang monoton, jadi kebetulan sama, lalu kamu lulus tes dan membawa kebiasaan buruk ke LIS.

**Kompleksitas:** kedua cuplikan `O(n)`.

---

## Naik tangga

**Teori:** Ada `n` anak tangga. Sekali langkah naik 1 atau 2. Banyak cara mencapai puncak. Turunkan dari keputusan terakhir, jangan kenali sebagai Fibonacci. Varian: langkah `1..k`, anak tangga rusak, biaya minimum saat menginjak (LC 746). Untuk `k` besar, `dp[i] = S(i-1) - S(i-k-1)` dengan prefix, jadi `O(n)`. CSES Dice Combinations memakai `k = 6`, naif sudah cukup. `dp[0] = 1` karena barisan kosong. Kalau `i` rusak, tugaskan `0`, jangan `continue` yang meninggalkan sampah.

**Kapan:** menghitung barisan langkah ke `n`. **Tidak:** langkah boleh mundur (bukan DAG), atau "tidak boleh dua langkah 2 berturut-turut" tanpa dimensi.

**STATE:** `dp[i]` adalah banyaknya barisan langkah sah yang jumlahnya tepat `i`.

**TRANSISI:** `dp[i] = dp[i-1] + dp[i-2]` karena langkah terakhir 1 atau 2, dan kedua himpunan tidak tumpang tindih.

**BASIS:** `dp[0] = 1`, `dp[1] = 1`. Untuk `n = 0` jawaban 1.

**Proses:** `n = 6`, langkah 1 atau 2.

```
i    dp[i-1]  dp[i-2]  dp[i]   contoh
0    —        —        1       ()
1    1        —        1       (1)
2    1        1        2       (1+1), (2)
3    2        1        3       (1+1+1), (1+2), (2+1)
4    3        2        5       lima barisan
5    5        3        8
6    8        5        13
```

Langkah `1..3`, `n = 4`:

```
i    rumus                    dp[i]
0    basis                    1
1    dp[0]                    1
2    dp[1]+dp[0]              2
3    dp[2]+dp[1]+dp[0]        4
4    dp[3]+dp[2]+dp[1]        7
```

Rusak di 2, langkah 1/2, `n = 5`: `dp = [1,1,0,1,1,2]`.

LC 746, `cost = [10, 15, 20]`: boleh mulai dari indeks 0 atau 1; biaya dibayar saat menginjak; atap berada setelah `n`. Jejak `dp[0]=10`, `dp[1]=15`, `dp[2]=20+min(10,15)=30`. Jawaban adalah biaya mencapai atap `min(dp[n-1], dp[n-2]) = min(30, 15) = 15` (mulai di indeks 1, injak 15, lalu ke atap).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll naikTangga(int n) {
    if (n == 0) return 1;
    ll a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

ll tanggaK(int n, int k, const vector<char>& rusak) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i < (int)rusak.size() && rusak[i]) {
            dp[i] = 0;
            continue;
        }
        for (int j = 1; j <= k && j <= i; j++) dp[i] = (dp[i] + dp[i - j]) % MOD;
    }
    return dp[n];
}

ll tanggaPrefix(int n, int k) {
    vector<ll> dp(n + 1, 0), pref(n + 2, 0);
    dp[0] = 1;
    pref[1] = 1;
    for (int i = 1; i <= n; i++) {
        ll L = pref[i];
        ll R = (i - k - 1 >= 0 ? pref[i - k] : 0);
        dp[i] = (L - R + MOD) % MOD;
        pref[i + 1] = (pref[i] + dp[i]) % MOD;
    }
    return dp[n];
}

ll tanggaMinCost(const vector<ll>& cost) {
    int n = (int)cost.size();
    ll a = 0, b = 0;
    for (int i = 2; i <= n; i++) {
        ll c = min(b + cost[i - 1], a + cost[i - 2]);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    FASTIO;
    cout << naikTangga(5) << "\n"; // 8
    vector<char> rusak(6, 0);
    rusak[2] = 1;
    cout << tanggaK(5, 2, rusak) << "\n"; // 2
    cout << tanggaPrefix(4, 3) << "\n";   // 7
    cout << tanggaMinCost({10, 15, 20}) << "\n"; // 15
    return 0;
}
```

**Jebakan:**

1. `dp[0] = 0` membuat semua nol.
2. Tangga rusak: `continue` tanpa menugaskan `0`.
3. Lupa modulo.
4. LC 746: biaya dibayar saat menginjak, jawaban adalah biaya mencapai atap setelah `n`.

**Kompleksitas:** langkah 1/2: `O(n)` / `O(1)`. Langkah `1..k` naif `O(nk)`, prefix `O(n)`.

---

## House robber

**Teori:** Deret rumah, tidak boleh merampok dua yang bersebelahan, maksimalkan total. Greedy selang-seling gagal pada `[2, 1, 1, 2]`: genap 3, ganjil 3, optimal 4. Keputusan terakhir: rumah `i` diambil atau tidak. Definisi "sampai i". Rolling `prev2 = 0, prev1 = 0` memuat basis `dp[-1] = dp[-2] = 0`, jadi `n = 1` tidak perlu cabang khusus. Varian melingkar (LC 213): rumah pertama dan terakhir bertetangga. Jalankan versi linear dua kali, bukan menambal `if`. Kasus `n = 1` pada versi melingkar wajib dipisah karena rentang kosong.

**Kapan:** pilih subset dengan larangan tetangga pada jalur. **Tidak:** boleh ambil bersebelahan (itu prefix sum). Graf umum adalah independent set.

**STATE:** `dp[i]` adalah total maksimum setelah mempertimbangkan rumah `0..i` ("sampai i"); rumah `i` boleh diambil atau dilewati.

**TRANSISI:** `dp[i] = max(dp[i-1], dp[i-2] + a[i])` — lewati `i`, atau ambil `i` dan haramkan `i-1`.

**BASIS:** `dp[0] = a[0]`, `dp[1] = max(a[0], a[1])`, atau rolling dari nol.

**Proses:** `a = [2, 7, 9, 3, 1]`.

```
i   a[i]   lewati=dp[i-1]   ambil=dp[i-2]+a[i]   dp[i]   pilih
0   2      —                2                    2       ambil
1   7      2                7                    7       ambil
2   9      7                2+9=11               11      ambil
3   3      11               7+3=10               11      lewati
4   1      11               11+1=12              12      ambil
```

Jawaban 12 dari rumah 0, 2, 4 yaitu `2+9+1`.

`[2, 1, 1, 2]`:

```
i   a    lewati   ambil   dp
0   2    —        2       2
1   1    2        1       2
2   1    2        3       3
3   2    3        4       4
```

Melingkar pada `[2, 1, 1, 2]`: tanpa akhir `[2,1,1] -> 3`; tanpa awal `[1,1,2] -> 3`; `max = 3`. Linear biasa 4 haram karena rumah 0 dan 3 bertetangga.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll houseRobber(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1; // URUTAN PENTING
        p1 = c;
    }
    return p1;
}

ll robberCircular(const vector<ll>& a) {
    int n = (int)a.size();
    if (n == 1) return a[0];
    vector<ll> tanpaAkhir(a.begin(), a.end() - 1);
    vector<ll> tanpaAwal(a.begin() + 1, a.end());
    return max(houseRobber(tanpaAkhir), houseRobber(tanpaAwal));
}

vector<int> robberPilihan(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
        dp[i] = max(dp[i - 1], (i >= 2 ? dp[i - 2] : 0) + a[i - 1]);
    vector<int> pilih;
    for (int i = n; i > 0; ) {
        if (dp[i] == dp[i - 1]) i--;
        else {
            pilih.push_back(i - 1);
            i -= 2;
        }
    }
    reverse(pilih.begin(), pilih.end());
    return pilih;
}

int main() {
    FASTIO;
    vector<ll> a = {2, 1, 1, 2};
    cout << houseRobber(a) << "\n";         // 4
    cout << robberCircular(a) << "\n";     // 3
    for (int i : robberPilihan(a)) cout << i << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Greedy selang-seling.
2. Melingkar ditambal `if` di rekurens.
3. `n = 1` pada versi melingkar.
4. `prev2 = prev1` harus sebelum `prev1 = cur`.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori. Rekonstruksi `O(n)`.

---

## Frog jump

**Teori:** Katak di batu 0 ingin ke `n-1`. Dari `i` boleh ke `i+1..i+k` dengan biaya `|h[i]-h[j]|`. Greedy "loncat ke tinggi paling mirip" gagal karena biaya lokal kecil bisa menutup posisi murah nanti. AtCoder DP-A adalah `k = 2`. DP-B adalah `k ≤ 100`, masih `O(nk)`. Untuk `k` besar dan biaya berbentuk `dp[j] + c[i]`, pakai deque monoton, bukan file ini. Inisialisasi `INF`, bukan 0.

**Kapan:** AtCoder DP-A/B. **Tidak:** `n, k = 1e5` dengan `O(nk)`.

**STATE:** `dp[i]` adalah biaya minimum untuk sampai di batu `i` dari batu 0.

**TRANSISI:** `dp[i] = min_{1≤j≤k, j≤i} (dp[i-j] + |h[i]-h[i-j]|)`.

**BASIS:** `dp[0] = 0`. State lain `INF`.

**Proses:** `h = [10, 30, 40, 20]`, `k = 2`.

```
i   kandidat                              dp[i]
0   —                                     0
1   0+|30-10|=20                          20
2   20+|40-30|=30, 0+|40-10|=30           30
3   30+|20-40|=50, 20+|20-30|=30          30
```

Jalur `0 -> 1 -> 3` biaya 30. Jalur `0 -> 2 -> 3` biaya 50, kalah.

`h = [10, 30, 40, 50, 20]`, `k = 2`:

```
i   h     dp
0   10    0
1   30    20
2   40    30
3   50    min(30+10, 20+20)=40
4   20    min(40+30, 30+20)=50
```

Jawaban 50. Greedy tinggi terdekat dari 0 ke 1 (selisih 20), lalu terus ke kanan, tidak otomatis lebih baik.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll INF = 4e18;

ll frog(const vector<ll>& h, int k) {
    int n = (int)h.size();
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++)
            dp[i] = min(dp[i], dp[i - j] + llabs(h[i] - h[i - j]));
    return dp[n - 1];
}

vector<int> frogJalur(const vector<ll>& h, int k) {
    int n = (int)h.size();
    vector<ll> dp(n, INF);
    vector<int> par(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++) {
            ll cand = dp[i - j] + llabs(h[i] - h[i - j]);
            if (cand < dp[i]) {
                dp[i] = cand;
                par[i] = i - j;
            }
        }
    vector<int> path;
    for (int v = n - 1; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    FASTIO;
    vector<ll> h = {10, 30, 40, 20};
    cout << frog(h, 2) << "\n";
    for (int x : frogJalur(h, 2)) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** inisialisasi `dp` dengan 0. Overflow `INF + |h|`. Greedy tinggi terdekat. `O(nk)` pada `k = n = 1e5`.

**Kompleksitas:** `O(nk)` waktu, `O(n)` memori.

---

## Kadane

**Teori:** Subarray tidak kosong dengan jumlah maksimum. Definisi "sampai i" buntu: kita tidak tahu apakah subarray terbaik sampai `i-1` bisa disambung. Definisi yang benar: jumlah terbaik di antara subarray yang **berakhir tepat di i**. Keputusan: mulai ulang di `i`, atau sambung `i-1`. Itulah Kadane — DP yang digulung, bukan trik tiga baris. `best = 0` salah pada array semua negatif. Melingkar: `max(kadaneMax, total - kadaneMin)`, kecuali semua negatif. Produk: simpan maksimum dan minimum karena negatif membalik peran.

**Kapan:** subarray kontigu, jumlah atau produk. **Tidak:** subsequence (boleh loncat). Kalau kosong diizinkan, jawaban tidak boleh negatif.

**STATE:** `dp[i]` adalah jumlah maksimum dari subarray yang berakhir tepat di indeks `i`.

**TRANSISI:** `dp[i] = max(a[i], dp[i-1] + a[i])`.

**BASIS:** `dp[0] = a[0]`. Jawaban = maksimum seluruh `dp[i]`, diinisialisasi `a[0]`, bukan 0.

**Proses:** `a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`.

```
i   a[i]   cur=max(a[i], cur+a[i])   best   s
0   -2     -2                        -2     0
1    1      1                        1      1
2   -3     -2                        1      1
3    4      4                        4      3
4   -1      3                        4      3
5    2      5                        5      3
6    1      6                        6      3
7   -5      1                        6      3
8    4      5                        6      3
```

Subarray `[4, -1, 2, 1]` jumlah 6, indeks `[3, 6]`.

Semua negatif `[-5, -2, -9]`:

```
i   a     cur   best
0   -5    -5    -5
1   -2    -2    -2
2   -9    -9    -2
```

Jawaban `-2`, bukan 0.

Melingkar `[5, -3, 5]`: `kadaneMax = 7` dari seluruh array `5 + (-3) + 5`, `total = 7`, `kadaneMin = -3`, `total - min = 10`. Subarray melingkar adalah `5` di akhir plus `5` di awal. `max(7, 10) = 10`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll kadane(const vector<ll>& a) {
    ll cur = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

ll kadaneIdx(const vector<ll>& a, int& bs, int& be) {
    ll cur = a[0], best = a[0];
    int s = 0;
    bs = be = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i] > cur + a[i]) {
            cur = a[i];
            s = i;
        } else cur = cur + a[i];
        if (cur > best) {
            best = cur;
            bs = s;
            be = i;
        }
    }
    return best;
}

ll kadaneCircular(const vector<ll>& a) {
    ll total = 0, mx = a[0], mn = a[0], cmx = a[0], cmn = a[0];
    for (ll x : a) total += x;
    for (size_t i = 1; i < a.size(); i++) {
        cmx = max(a[i], cmx + a[i]);
        mx = max(mx, cmx);
        cmn = min(a[i], cmn + a[i]);
        mn = min(mn, cmn);
    }
    if (mx < 0) return mx;
    return max(mx, total - mn);
}

ll kadaneProduct(const vector<ll>& a) {
    ll mx = a[0], mn = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        ll x = a[i];
        ll nmx = max({x, mx * x, mn * x});
        ll nmn = min({x, mx * x, mn * x});
        mx = nmx;
        mn = nmn;
        best = max(best, mx);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int bs, be;
    cout << kadane(a) << "\n";
    cout << kadaneIdx(a, bs, be) << " [" << bs << "," << be << "]\n";
    cout << kadaneCircular({5, -3, 5}) << "\n";
    cout << kadaneProduct({2, 3, -2, 4}) << "\n";
    return 0;
}
```

**Jebakan:**

1. `best = 0` pada array semua negatif.
2. Indeks: `s` dan `bs` diperbarui di `if` yang sama.
3. Melingkar: `total - min = 0` saat semua negatif.
4. Produk: menugaskan `mx` sebelum menghitung `mn` baru.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori.

---

## Jump game

**Teori:** `a[i]` adalah jarak lompat maksimum dari `i`. Versi "apakah bisa ke akhir" adalah DP boolean, atau greedy jangkauan terjauh yang lebih cepat. Versi "minimal lompatan" kembali ke `min + 1`. Push dari `i` ke `i+1..i+a[i]`. Array `[3, 2, 1, 0, 4]` memblokir di indeks 3. Jangan memakai `O(n^2)` pada `n = 1e5` jika hanya ditanya bisa atau tidak.

**Kapan:** LC 55 / 45. **Tidak:** lompat mundur tanpa batas — bisa siklus.

**STATE:** `bisa[i]` benar jika indeks `i` dapat dicapai dari 0. Versi min: `dp[i]` adalah jumlah lompatan minimum ke `i`.

**TRANSISI:** jika `bisa[j]` dan `j + a[j] >= i` maka `bisa[i] = true`. Min: `dp[i] = min(dp[j] + 1)` untuk setiap `j` yang menjangkau `i`.

**BASIS:** `bisa[0] = true`, `dp[0] = 0`. Lainnya `false` / `INF`.

**Proses:** `a = [2, 3, 1, 1, 4]`.

```
i   a[i]   far setelah i   bisa
0   2      2               ya
1   3      4               ya (1<=2)
2   1      4               ya
3   1      4               ya
4   4      8               ya, sudah di akhir
```

Min lompat:

```
i   dp[i]   dari
0   0       —
1   1       0
2   1       0
3   2       1 atau 2
4   2       1  (1+3>=4)
```

Optimal `0 -> 1 -> 4` (2 lompat). `0 -> 2 -> 3 -> 4` adalah 3.

`a = [3, 2, 1, 0, 4]`:

```
i   a   far
0   3   3
1   2   3
2   1   3
3   0   3
4   4   tidak tercapai, i=4 > far
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int INF = 1e9;

bool jumpBisa(const vector<int>& a) {
    int far = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > far) return false;
        far = max(far, i + a[i]);
    }
    return true;
}

int jumpMin(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> dp(n, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        if (dp[i] < INF)
            for (int k = 1; k <= a[i] && i + k < n; k++)
                dp[i + k] = min(dp[i + k], dp[i] + 1);
    return dp[n - 1] >= INF ? -1 : dp[n - 1];
}

int jumpMinGreedy(const vector<int>& a) {
    int n = (int)a.size();
    if (n <= 1) return 0;
    int lompat = 0, far = 0, end = 0;
    for (int i = 0; i < n - 1; i++) {
        far = max(far, i + a[i]);
        if (i == end) {
            if (far <= end) return -1;
            lompat++;
            end = far;
        }
    }
    return lompat;
}

int main() {
    FASTIO;
    cout << jumpBisa({2, 3, 1, 1, 4}) << " " << jumpMin({2, 3, 1, 1, 4}) << "\n";
    cout << jumpBisa({3, 2, 1, 0, 4}) << " " << jumpMin({3, 2, 1, 0, 4}) << "\n";
    cout << jumpMinGreedy({2, 3, 1, 1, 4}) << "\n";
    return 0;
}
```

**Jebakan:** DP `O(n^2)` pada `n = 1e5` untuk versi "bisa". Tidak men-skip `INF`. Mengembalikan `INF` bukan `-1`.

**Kompleksitas:** greedy bisa `O(n)`. Min naif `O(n · max a)`. Greedy BFS-lapis `O(n)`.

---

## Rolling dan rekonstruksi

**Teori:** Kalau `dp[i]` hanya butuh sejumlah tetap nilai lama, gulung memori. Kalau soal minta rumah mana, batu mana, atau indeks subarray, simpan `dp` penuh atau `par[]`. Jangan menggabungkan "mulai ulang" dan "rekor baru" dalam satu `if` pada Kadane. House robber rekonstruksi membandingkan `dp[i]` dengan `dp[i-1]`: sama berarti `i` dilewati, beda berarti `i` diambil lalu loncat `i-2`.

**Kapan:** setelah angka benar, baru rekonstruksi. **Tidak:** menggulung dulu lalu kaget soal minta jalur.

**STATE:** `par[i]` adalah pendahulu yang menghasilkan `dp[i]`, atau `-1` pada basis.

**TRANSISI:** setiap kali kandidat memperbaiki `dp[i]`, tulis `par[i] = j`.

**BASIS:** `par[0] = -1`.

**Proses:** robber `[2, 7, 9, 3, 1]`, tabel `dp[1..5] = [2, 7, 11, 11, 12]`.

```
i=5  dp[5]=12 != dp[4]=11  -> ambil rumah 4, i=3
i=3  dp[3]=11 != dp[2]=7   -> ambil rumah 2, i=1
i=1  dp[1]=2               -> ambil rumah 0
indeks 0-based: 0, 2, 4
```

Frog `par = [-1, 0, 0, 1]` memberi `3 -> 1 -> 0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll houseRobber(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int main() {
    FASTIO;
    vector<ll> a = {2, 7, 9, 3, 1};
    cout << houseRobber(a) << "\n"; // 12, jalur di robberPilihan
    return 0;
}
```

**Jebakan:** rolling lalu diminta indeks. Membandingkan `dp[i]` dengan `dp[i-2] + a[i]` memakai `a` 1-based tertukar.

**Kompleksitas:** rolling `O(1)` memori. Rekonstruksi `O(n)` memori.

---

Uji cepat wajib: tangga 5 = 8, robber `[2,1,1,2]` = 4, robber lingkar = 3, Kadane contoh = 6, Kadane all-neg = -2, frog contoh = 30, jump bisa / min = 1 / 2, jump blok = 0. Lanjut ke [04 — coin unbounded](04-coin-unbounded.md) untuk koin minimum, kombinasi versus permutasi, dan knapsack tak terbatas.
