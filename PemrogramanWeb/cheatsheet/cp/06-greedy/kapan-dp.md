# Kapan greedy, kapan DP

[← README](README.md) · [Indeks CP](../README.md)

Greedy mengambil pilihan yang kelihatan terbaik sekarang, lalu tidak menyesal. DP mencoba **semua** pilihan pada tiap state, lalu mengambil yang optimal. Keduanya memakai optimal substructure. Bedanya: greedy **membuang** cabang, DP **mengingat** cabang.

Day terkait: **071**. File ini wajib dibaca sebelum percaya “ambil maksimum”. Jembatan memo/tabel: [../05-rekursi/memoization.md](../05-rekursi/memoization.md) dan [../09-dp/README.md](../09-dp/README.md).

## Daftar isi

- [Prinsip greedy](#prinsip-greedy)
- [Greedy versus DP](#greedy-versus-dp)
- [0-1 knapsack: greedy gagal](#0-1-knapsack-greedy-gagal)
- [Koin: greedy kadang gagal](#koin-greedy-kadang-gagal)
- [Activity berbobot: greedy gagal](#activity-berbobot-greedy-gagal)
- [Sinyal dari batasan](#sinyal-dari-batasan)
- [Stress test untuk membantah greedy](#stress-test-untuk-membantah-greedy)
- [Peta keputusan](#peta-keputusan)

---

## Prinsip greedy

**Teori:** Greedy membangun jawaban langkah demi langkah. Di tiap langkah ia memilih kandidat yang paling menjanjikan menurut satu kriteria. Dua syarat klasik: **greedy choice** (ada jawaban optimal yang memuat pilihan greedy pertama) dan **optimal substructure** (sisa soal setelah pilihan itu juga soal optimal yang sama bentuknya). Analoginya antrean kasir: kalau tujuanmu meminimalkan jumlah waktu tunggu, layani yang belanjanya paling sedikit dulu. Itu bukan “terasa adil”, itu rumus. Bukti formal exchange ada di [interval-exchange.md](interval-exchange.md).

**Kapan:** kriteria lokal bisa dibuktikan, atau soal klasik yang sudah mapan: activity selection tanpa bobot, fractional knapsack, Huffman, Kruskal, Dijkstra bobot `>= 0`. Jangan hanya karena “ambil maksimum kelihatan benar”. Jangan jika ada kapasitas plus nilai yang saling tukar.

**Proses:** tiga pekerjaan durasi `5, 1, 3`. Satu mesin, minimalkan jumlah waktu selesai `Σ C_i`.

Urutan `5, 1, 3`:

```text
C = 5, 6, 9
ΣC = 20
```

Urutan `1, 3, 5` (SPT):

```text
C = 1, 4, 9
ΣC = 14
```

Urutan `3, 1, 5` jumlah `16`, lebih buruk dari SPT. Greedy “terpendek dulu” menang di contoh ini dan, dengan exchange, selalu.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll jumlah_selesai(vector<ll> dur) {
    sort(dur.begin(), dur.end());
    ll waktu = 0, sum = 0;
    for (ll t : dur) {
        waktu += t;
        sum += waktu;
    }
    return sum;
}

int main() {
    FASTIO;
    cout << jumlah_selesai({5, 1, 3}) << '\n'; // 14
    cout << jumlah_selesai({2, 2, 2}) << '\n'; // 12
    return 0;
}
```

`{2,2,2}`: `C = 2,4,6` jumlah 12. Semua urutan sama karena durasi identik.

**Jebakan:**
1. Meniru “ambil terbesar” dari soal lain.
2. Tidak menulis bukti atau counterexample.
3. Overflow `Σ C_i`: `n = 1e5`, `t_i = 1e9` wajib `ll`.

**Kompleksitas:** sort `O(n log n)`, sapuan `O(n)`, memori `O(n)`.

---

## Greedy versus DP

**Teori:** Analoginya persimpangan: greedy pilih jalan yang kelihatan paling pendek sekarang; DP menghitung jarak lewat semua jalan lalu ambil min. Greedy salah ketika pilihan lokal menutup jalan yang belakangan jauh lebih hemat. DP salah (TLE) ketika kamu mengenumerasi state yang tidak perlu padahal exchange sudah sah.

**Kapan pakai greedy:** bukti exchange ada, atau soal klasik, atau setelah stress test tidak ketemu counterexample **dan** `n` besar memaksa `O(n log n)`. **Kapan DP:** `n <= 20` bitmask, `n <= 100` plus kapasitas, “pilih paling banyak `K` dengan trade-off”, atau kamu menemukan satu counterexample.

**Proses:** bandingkan dua dunia pada soal yang sama bentuknya.

1. Fractional knapsack: boleh potong. Greedy rasio benar.
2. 0-1 knapsack: tidak boleh potong. Greedy rasio bisa salah.
3. Activity tanpa bobot: urut `r` benar.
4. Activity berbobot: urut `r` bisa salah, DP plus `lower_bound` benar.

Tabel singkat:

| soal | greedy | DP |
| --- | --- | --- |
| Σ C_i satu mesin | SPT benar | tidak perlu |
| 0-1 knapsack | sering salah | `O(nW)` |
| koin kanonik (1,5,10) | biasanya benar | selalu benar |
| koin {1,3,4} | bisa salah | selalu benar |
| interval lepas max hitung | urut r | tidak perlu |
| interval lepas max bobot | salah | `O(n log n)` DP |

**Kode:** kerangka pikir, bukan satu rumus.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string pilihAlat(int n, ll W, bool adaBobotInterval, bool bolehPotong) {
    if (adaBobotInterval) return "DP interval berbobot";
    if (bolehPotong) return "greedy rasio";
    if (n <= 40 && W > 1000000) return "MITM atau DP map";
    if (n <= 200 && W <= 100000) return "DP knapsack";
    if (n >= 100000) return "cari greedy berbukti / sort";
    return "tulis brute n kecil dulu";
}

int main() {
    FASTIO;
    cout << pilihAlat(100, 10000, false, false) << '\n';
    cout << pilihAlat(100000, 0, false, false) << '\n';
    cout << pilihAlat(50, 0, true, false) << '\n';
    return 0;
}
```

**Jebakan:**
1. Lolos sampel lalu percaya greedy.
2. Mencontoh knapsack fraksional untuk 0-1.
3. Mengabaikan batasan `n` sebagai petunjuk penulis soal.

**Kompleksitas:** membedakan pendekatan adalah `O(1)` di kepala. Salah pilih algoritma = TLE atau WA, bukan “hampir benar”.

---

## 0-1 knapsack: greedy gagal

**Teori:** Barang utuh. Rasio nilai/berat terbesar tidak menjamin optimal karena sisa kapasitas bisa terbuang. Analoginya: koper sisa 3 kg, kamu sudah memasukkan barang rasio tinggi 2 kg, barang 3 kg yang sedikit lebih “jelek” rasio tertinggal. DP mencoba kedua cabang. Fractional boleh potong, maka satu gram barang mahal selalu mengalahkan satu gram barang murah.

**Kapan:** 0-1 → DP atau MITM. Fractional → greedy. Jangan campur.

**Proses:** `(berat, nilai) = (2,3), (3,4)`, `W = 3`.

1. Rasio `3/2 = 1.5`, `4/3 ≈ 1.33`.
2. Greedy ambil `(2,3)`, sisa 1, tidak muat. Nilai 3.
3. Optimal ambil `(3,4)`. Nilai 4.
4. DP: `dp[3] = 4`.
5. Greedy kalah.

Contoh lain `(2,3), (3,4), (4,5)`, `W = 5`: greedy dan DP sama-sama 7. Sampel yang “cantik” tidak membuktikan greedy.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll greedy_01(vector<ll> w, vector<ll> v, ll W) {
    int n = (int)w.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return v[i] * w[j] > v[j] * w[i];
    });
    ll sisa = W, nilai = 0;
    for (int i : idx) {
        if (w[i] <= sisa) {
            sisa -= w[i];
            nilai += v[i];
        }
    }
    return nilai;
}

ll dp_01(const vector<ll>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int cap = W; cap >= (int)w[i]; cap--)
            dp[cap] = max(dp[cap], v[i] + dp[cap - (int)w[i]]);
    return dp[W];
}

int main() {
    FASTIO;
    vector<ll> w = {2, 3}, v = {3, 4};
    cout << "greedy " << greedy_01(w, v, 3)
         << " dp " << dp_01(w, v, 3) << '\n'; // 3 vs 4
    return 0;
}
```

Tabel penuh: [09-dp/05-01-knapsack.md](../09-dp/05-01-knapsack.md).

**Jebakan:**
1. Banding rasio pakai `double`.
2. Overflow `v[i] * w[j]`.
3. Mengira “kalau W besar greedy makin benar”.

**Kompleksitas:** greedy `O(n log n)`, DP `O(nW)`.

---

## Koin: greedy kadang gagal

**Teori:** Sistem koin kanonik (banyak mata uang nyata) membuat “koin terbesar dulu” optimal. Sistem `{1, 3, 4}` tidak. Analoginya mesin kasir: untuk 6, greedy mengambil 4 lalu dua kali 1 (tiga koin), optimal dua kali 3. DP unbounded menghitung minimum koin untuk setiap sisa.

**Kapan:** koin sebarang → DP. Koin `{1, 5, 10, 25}` di banyak soal masih greedy, tetapi buktikan atau bandingkan DP pada `n` kecil. Jangan mengirim greedy hanya karena “pernah benar di toko”.

**Proses:** koin `{1, 3, 4}`, target `6`.

1. Greedy: `4 + 1 + 1`, tiga koin.
2. Optimal: `3 + 3`, dua koin.
3. DP: `dp[0]=0`, `dp[1]=1`, `dp[2]=2`, `dp[3]=1`, `dp[4]=1`, `dp[5]=2`, `dp[6]=2`.
4. Target `8`: greedy `4+4` dua koin, optimal sama. Tidak semua target membongkar greedy.
5. Satu counterexample cukup untuk menolak greedy.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll greedy_koin(vector<ll> c, ll sisa) {
    sort(c.rbegin(), c.rend());
    ll hit = 0;
    for (ll x : c) {
        hit += sisa / x;
        sisa %= x;
    }
    return sisa == 0 ? hit : -1;
}

ll dp_koin(const vector<ll>& c, int target) {
    const ll INF = 1e18;
    vector<ll> dp(target + 1, INF);
    dp[0] = 0;
    for (int s = 1; s <= target; s++)
        for (ll x : c)
            if (x <= s && dp[s - (int)x] + 1 < dp[s])
                dp[s] = dp[s - (int)x] + 1;
    return dp[target] >= 1e18 ? -1 : dp[target];
}

int main() {
    FASTIO;
    vector<ll> c = {1, 3, 4};
    cout << greedy_koin(c, 6) << ' ' << dp_koin(c, 6) << '\n'; // 3 2
    cout << greedy_koin({1, 5, 10}, 30) << ' ' << dp_koin({1, 5, 10}, 30) << '\n';
    return 0;
}
```

Lanjut: [09-dp/04-coin-unbounded.md](../09-dp/04-coin-unbounded.md).

**Jebakan:**
1. Greedy pada koin yang tidak kanonik.
2. DP loop barang di luar versus di dalam mengubah “kombinasi” menjadi “permutasi” saat menghitung **cara**, bukan minimum.
3. `INF` overflow saat `+ 1`.

**Kompleksitas:** greedy `O(k log k)`, DP `O(k · target)`.

---

## Activity berbobot: greedy gagal

**Teori:** Tanpa bobot, “selesai paling awal” menyisakan ruang terbanyak. Dengan bobot, interval pendek yang selesai awal bisa kalah dari satu interval panjang yang sangat berharga. Analoginya: rapat 1 jam bernilai 1, rapat 3 jam menabraknya bernilai 100. Greedy hitung mengambil yang pendek, total 1. DP memilih 100.

**Kapan:** interval lepas maksimum **jumlah** → urut `r`, file [interval-exchange.md](interval-exchange.md). Interval lepas maksimum **bobot** → DP. Jangan meniru urut `r` hanya karena soalnya masih interval.

**Proses:** interval `[0,2]` bobot 1, `[1,4]` bobot 10, `[3,5]` bobot 1.

1. Urut `r`: ambil `[0,2]`, lalu `[3,5]`, bobot 2. Skip `[1,4]`.
2. Optimal: hanya `[1,4]`, bobot 10.
3. DP: sort `r`, `dp[i] = max(dp[i-1], w[i] + dp[prev[i]])`.
4. `prev` = interval terakhir yang `r <= l[i]`.
5. Jawaban 10.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int greedy_hitung(vector<array<ll, 3>> a) { // l, r, w
    sort(a.begin(), a.end(), [](auto& x, auto& y) { return x[1] < y[1]; });
    int hit = 0;
    ll akhir = LLONG_MIN, bobot = 0;
    for (auto [l, r, w] : a) if (l > akhir) {
        hit++;
        akhir = r;
        bobot += w;
    }
    return (int)bobot;
}

ll dp_bobot(vector<array<ll, 3>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) { return x[1] < y[1]; });
    int n = (int)a.size();
    vector<ll> dp(n);
    for (int i = 0; i < n; i++) {
        ll ambil = a[i][2];
        for (int j = 0; j < i; j++)
            if (a[j][1] < a[i][0]) ambil = max(ambil, dp[j] + a[i][2]);
        ll skip = i ? dp[i - 1] : 0;
        dp[i] = max(skip, ambil);
    }
    return dp[n - 1];
}

int main() {
    FASTIO;
    vector<array<ll, 3>> a = {{0, 2, 1}, {1, 4, 10}, {3, 5, 1}};
    cout << greedy_hitung(a) << ' ' << dp_bobot(a) << '\n'; // 2 10
    return 0;
}
```

Loop `j` di DP di atas `O(n^2)`. Versi `O(n log n)` memakai `lower_bound` pada `r`. Folder 09 membahas rekonstruksi jejak.

**Jebakan:**
1. Menjumlah bobot hasil greedy hitung, mengira itu max weight.
2. Irisan `[l,r]` versus `[l,r)` tertukar di `prev`.
3. `akhir = 0` padahal ada interval negatif.

**Kompleksitas:** greedy `O(n log n)`, DP naif `O(n^2)`, DP bound `O(n log n)`.

---

## Sinyal dari batasan

**Teori:** Penulis soal menulis `n` dan `W` sebagai petunjuk alat. Analoginya papan menu: `n = 1e5` jarang DP kuadrat, `n = 100` plus `W = 1e5` hampir selalu knapsack. Alasan benar: waktu 1–2 detik kira-kira `1e8`–`2e8` operasi.

**Kapan:** baca constraint sebelum rumus. Jangan merancang `O(n^2)` pada `n = 1e5` lalu “mengoptimalkan nanti”.

**Proses:**

| batasan | arah pikir |
| --- | --- |
| `n <= 20` | brute / bitmask, greedy sering umpan |
| `n <= 100`, `W <= 1e5` | DP knapsack |
| `n <= 40`, `W` besar | MITM |
| `n <= 1e5`, tidak ada kapasitas aneh | greedy / sort / struktur |
| jawaban monoton terhadap X | binary search on answer |
| interval plus bobot, `n <= 1e5` | DP `O(n log n)`, bukan greedy |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool muatWaktu(ll operasi) {
    return operasi <= 200000000LL;
}

int main() {
    FASTIO;
    cout << muatWaktu(100000LL * 100000LL) << '\n';     // 0, n^2 1e5
    cout << muatWaktu(100LL * 100000LL) << '\n';        // 1, nW
    cout << muatWaktu(40) << '\n';                      // 1, tetapi 2^40 tidak
    cout << (1LL << 20) << '\n';                        // MITM paruh
    return 0;
}
```

`2^40` tidak dimasukkan ke `muatWaktu` karena kamu tidak boleh menghitungnya begitu.

**Jebakan:**
1. Mengira `n <= 1e5` selalu greedy: LIS `O(n log n)` adalah DP.
2. Mengira `n <= 20` selalu greedy: sering umpan, bitmask lebih jujur.

**Kompleksitas:** membaca constraint `O(1)`, menyelamatkan WA/TLE berhari-hari.

---

## Stress test untuk membantah greedy

**Teori:** Sebelum submit greedy yang tidak terbukti, lawankan dengan brute atau DP untuk `n` kecil. Kalau beda, greedy salah — cetak kasusnya. Kalau sama sampai puluhan ribu tes, belum tentu benar, tetapi jauh lebih aman. Analoginya mencicipi masakan: satu sendok busuk cukup untuk tidak menyajikan porsi.

**Kapan:** selalu untuk greedy baru. Tidak menggantikan bukti, tetapi menggantikan harapan.

**Proses:** “ambil interval paling pendek” lawan brute activity.

Kasus `[1,10], [9,12], [11,20]`:

```text
pendek: [9,12] saja → 1
optimal: [1,10]+[11,20] → 2
```

Stress ketemu jika generator menghasilkan pola ini.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int greedy_pendek(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return (x.second - x.first) < (y.second - y.first);
    });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) if (l > akhir) {
        hit++;
        akhir = r;
    }
    return hit;
}

int brute_activity(const vector<pair<ll, ll>>& a) {
    int n = (int)a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        int hit = 0;
        for (int i = 0; i < n && ok; i++) if (mask & (1 << i)) {
            for (int j = i + 1; j < n; j++) if (mask & (1 << j)) {
                ll L = max(a[i].first, a[j].first);
                ll R = min(a[i].second, a[j].second);
                if (L <= R) ok = false;
            }
            hit++;
        }
        if (ok) best = max(best, hit);
    }
    return best;
}

int activity_benar(vector<pair<ll, ll>> a) {
    sort(a.begin(), a.end(), [](auto x, auto y) { return x.second < y.second; });
    int hit = 0;
    ll akhir = LLONG_MIN;
    for (auto [l, r] : a) if (l > akhir) {
        hit++;
        akhir = r;
    }
    return hit;
}

int main() {
    FASTIO;
    vector<pair<ll, ll>> a = {{1, 10}, {9, 12}, {11, 20}};
    cout << "pendek=" << greedy_pendek(a)
         << " brute=" << brute_activity(a)
         << " r=" << activity_benar(a) << '\n';
    return 0;
}
```

Keluaran: `pendek=1 brute=2 r=2`. Greedy durasi terbantah. Greedy `r` lolos.

**Jebakan:**
1. Brute salah (model irisan beda) sehingga greedy yang benar kelihatan salah.
2. `n` tes terlalu kecil.
3. Tidak mengetes `n` khusus 1, 2, 4.

**Kompleksitas:** satu tes brute `O(2^n n^2)`. 10^4 tes `n = 12` masih hidup.

---

## Peta keputusan

```text
Ada bukti exchange / soal klasik tanpa bobot aneh
  → greedy

Ada counterexample, atau kapasitas + nilai
  → DP / memo / MITM

n besar dan predikat monoton
  → binary search on answer, bukan greedy buta

Ragu
  → brute n kecil, baru pilih
```

| kriteria kelihatan pintar | status |
| --- | --- |
| interval urut `r` untuk max lepas | benar |
| interval urut `l` untuk max lepas | salah |
| interval urut durasi | salah |
| knapsack 0-1 rasio | salah |
| knapsack fraksional rasio | benar |
| koin sebarang terbesar dulu | sering salah |
| Huffman dua terkecil | benar |

Satu counterexample mengalahkan sepuluh sampel. Tulis stress sebelum submit.

Lanjut ke [interval-exchange.md](interval-exchange.md) untuk bukti tukar dan pola interval, atau ke [../09-dp/README.md](../09-dp/README.md) jika greedy sudah terbantah.
