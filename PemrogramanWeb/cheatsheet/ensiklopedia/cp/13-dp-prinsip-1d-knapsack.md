# 13 — DP: prinsip, 1D, knapsack, LIS

[← Graf lanjut](12-graf-dsu-scc-bridge-2sat-flow.md) · [README](README.md) · [Lanjut string dan grid →](14-dp-string-grid-range.md)

Folder 09 di `ComProgLearning/CP/DAFTAR-MATERI.md`: Day **141–148** (prinsip sampai LIS). Latihan harian ada di folder Day itu, jangan disalin ke sini.

Gaya Day-141/143: sebelum mengetik, jawab tiga pertanyaan dengan **kalimat lengkap**.

```
1. STATE     : dp[i] artinya apa? (bukan "jawabannya")
2. TRANSISI  : dp[i] dihitung dari state mana, dengan operator apa?
3. BASIS     : state terkecil nilainya berapa, dan kenapa?
```

Dua definisi yang sering tertukar:

| Definisi | Artinya | Jawaban akhir |
|---|---|---|
| **sampai i** | elemen `i` boleh dipakai atau tidak | biasanya `dp[n-1]` |
| **berakhir tepat di i** | elemen `i` wajib dipakai sebagai ekor | `max` / `min` atas seluruh `dp[i]` |

Kode memakai `#include <bits/stdc++.h>`, `typedef long long ll`, fungsi **terpisah** (bukan semua di `main`), 0-indexed kecuali disebut.

## Daftar isi

- [Cara merancang DP](#cara-merancang-dp)
- [Prinsip: overlapping dan optimal substructure](#prinsip-overlapping-dan-optimal-substructure)
- [Top-down dan bottom-up](#top-down-dan-bottom-up)
- [Tangga](#tangga)
- [House robber](#house-robber)
- [Frog jump](#frog-jump)
- [Kadane](#kadane)
- [Coin change minimum](#coin-change-minimum)
- [Coin combinations](#coin-combinations)
- [Unbounded knapsack](#unbounded-knapsack)
- [0-1 knapsack](#0-1-knapsack)
- [Bounded knapsack](#bounded-knapsack)
- [Subset sum](#subset-sum)
- [Partition](#partition)
- [LIS](#lis)
- [Template gabungan Day-143](#template-gabungan-day-143)
- [Peta jebakan file ini](#peta-jebakan-file-ini)
- [Jump game](#jump-game-varian-1d)
- [Checklist sebelum mengetik](#checklist-sebelum-mengetik)
- [Tabel uji cepat](#tabel-uji-cepat-operator)

---

## Cara merancang DP

**Teori:** Dynamic programming adalah rekursi yang menolak menghitung submasalah yang sama dua kali. Setiap soal DP adalah DAG: simpul = state, sisi = transisi. Jawaban keseluruhan disusun dari jawaban submasalah (optimal substructure). Submasalah yang sama muncul berkali-kali (overlapping). Kalau salah satu syarat hilang, DP tidak membantu: merge sort overlapping-nya sedikit, jalur terpanjang tanpa mengulang simpul di graf bersiklus tidak punya optimal substructure yang bersih.

Empat uji desain state (Day 142):

1. **Bisa dikalimatkan?** Definisi lengkap, bukan "hasil terbaik di i".
2. **Cukup informasinya?** Masa depan hanya bergantung pada state sekarang (Markov).
3. **Setara?** Dua jalur ke state yang sama punya masa depan yang sama.
4. **Muat?** `|state| × biaya transisi ≤ 10^8` untuk 1–2 detik.

**Kapan:** soal meminta banyak cara, nilai maksimum/minimum, atau "bisa/tidak" pada ruang keputusan yang saling menumpuk. **Tidak:** keputusan lokal selalu benar (greedy terbukti), atau setiap submasalah hanya muncul sekali.

**STATE:** `dp[i]` adalah jawaban lengkap untuk submasalah yang diwakili indeks `i`, ditulis sebagai satu kalimat yang menyebut apa yang sudah diputuskan dan apa yang masih bebas.

**TRANSISI:** `dp[i]` dihitung dari beberapa `dp[j]` dengan `j` lebih kecil, digabung dengan `+`, `max`, `min`, atau `||`, dan pilihan terakhirnya saling lepas serta mencakup semua kemungkinan.

**BASIS:** state yang tidak punya pendahulu diisi secara langsung, biasanya `dp[0]` atau `dp` untuk array kosong.

**Proses angka:** fibonacci `fib(5)` tanpa catatan menghitung `fib(3)` dua kali dan `fib(2)` tiga kali. Dengan catatan, tiap `n` dihitung sekali.

```
                 fib(5)
               /        \
          fib(4)          fib(3)     <- sudah pernah
         /      \
    fib(3)     fib(2)
```

`fib(50)` polos ≈ 2 miliar panggilan. Dengan DP: 50 pengisian.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll fibPolos(int n) {
    if (n <= 1) return n;
    return fibPolos(n - 1) + fibPolos(n - 2); // JANGAN dipakai
}

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

ll fibHemat(int n) {
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 10;
    vector<ll> memo(n + 1, -1);
    cout << fibMemo(n, memo) << " " << fibTab(n) << " " << fibHemat(n) << "\n";
    return 0;
}
```

**Jebakan:**

1. Memoisasi dengan sentinel `0` padahal `0` bisa jadi jawaban sah — pakai `-1` atau array `visited`.
2. Menulis `dp[i]` tanpa kalimat, lalu mengambil `dp[n-1]` padahal definisinya "berakhir tepat di i".
3. Lupa modulo pada soal "berapa cara".
4. `int` untuk akumulasi: `2e5 * 1e9` tidak muat.

**Kompleksitas:** rekursi polos `O(2^n)`. Memo/tabulasi `O(n)` waktu. Rolling `O(1)` memori. Rumus umum: waktu = (banyak state) × (biaya satu state).

---

## Prinsip: overlapping dan optimal substructure

**Teori:** Analoginya buku catatan PR. Soal nomor 47 sama dengan nomor 12. Tanpa catatan, dikerjakan ulang. Dengan catatan, dibaca. Tabel DP adalah buku catatan itu. Overlapping: submasalah yang sama muncul di banyak cabang. Optimal substructure: jawaban terbaik keseluruhan bisa disusun dari jawaban terbaik bagian-bagiannya. Contoh yang gagal: longest simple path di graf berarah bersiklus — jalur terbaik ke tetangga bisa memakai simpul yang dibutuhkan nanti.

**Kapan:** pohon rekursi berisi cabang yang sama. **Tidak:** divide and conquer murni (merge sort), atau constraint yang merusak optimal substructure.

**STATE:** `cara[i]` adalah banyaknya barisan langkah yang sah untuk mencapai anak tangga ke-`i`.

**TRANSISI:** langkah terakhir hanya 1 atau 2, jadi `cara[i] = cara[i-1] + cara[i-2]`. Kedua himpunan saling lepas karena dibedakan langkah terakhir.

**BASIS:** `cara[0] = 1` karena berdiri di titik awal adalah satu cara: barisan kosong. `cara[1] = 1`.

**Proses angka:** `n = 5`, langkah 1 atau 2.

```
cara[0] = 1
cara[1] = 1
cara[2] = 1 + 1 = 2     (1+1, 2)
cara[3] = 2 + 1 = 3     (1+1+1, 1+2, 2+1)
cara[4] = 3 + 2 = 5
cara[5] = 5 + 3 = 8
```

Kalau `cara[0]` diisi 0, seluruh hasil jadi 0.

**Kode modular:** lihat fungsi `tangga` di bawah. Pola operator:

| Kata soal | Operator |
|---|---|
| berapa cara | `+` |
| maksimum | `max` |
| minimal langkah / biaya | `min` |
| bisa / tidak | `\|\|` |

**Jebakan:** menghafal rumus Fibonacci tanpa menurunkan keputusan terakhir. Mengisi basis `0` untuk "berapa cara".

**Kompleksitas:** `O(n)` waktu, `O(1)` memori jika digulung.

---

## Top-down dan bottom-up

**Teori:** Rekurens matematisnya sama. Top-down mulai dari target, pecah ke bawah, simpan cache (DFS di DAG state). Bottom-up mulai dari basis, isi menurut urutan topologis. Analoginya piramida: top-down bertanya "penopang sudah siap?", bottom-up menaruh batu dari tanah. Top-down hanya menghitung state yang terjangkau. Bottom-up mengisi seluruh tabel, lebih ramah cache CPU, dan mudah digulung.

**Kapan top-down:** state rumit, banyak state mati, ingin menulis rekursi dulu. **Kapan bottom-up:** `n ≥ 10^5` (stack overflow), butuh rolling array, atau urutan jelas. **Tidak:** kedalaman rekursi `> 10^5` tanpa menaikkan stack.

**STATE:** `memo[i]` menyimpan biaya minimum mencapai batu `i` setelah pernah dihitung; `visited[i]` menandai bahwa nilai itu sah meski bisa negatif atau `-1`.

**TRANSISI:** dari `i` kita menarik jawaban `i-1` dan `i-2` (pull), atau dari `i` kita mendorong ke `i+1` dan `i+2` (push).

**BASIS:** biaya di batu 0 adalah 0.

**Proses angka:** batu tinggi `h = [10, 30, 40, 20]`, lompat 1 atau 2.

```
dp[0] = 0
dp[1] = |30-10| = 20
dp[2] = min(20+|40-30|, 0+|40-10|) = min(30, 30) = 30
dp[3] = min(30+|20-40|, 20+|20-30|) = min(50, 30) = 30
```

Jawaban 30: `0 → 1 → 3`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)4e18;

ll frogTopDown(int i, const vector<ll>& h, vector<ll>& memo, vector<char>& vis) {
    if (i == 0) return 0;
    if (vis[i]) return memo[i];
    vis[i] = 1;
    ll ans = frogTopDown(i - 1, h, memo, vis) + llabs(h[i] - h[i - 1]);
    if (i >= 2) ans = min(ans, frogTopDown(i - 2, h, memo, vis) + llabs(h[i] - h[i - 2]));
    return memo[i] = ans;
}

ll frogBottomUpPull(const vector<ll>& h) {
    int n = (int)h.size();
    if (n <= 1) return 0;
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + llabs(h[i] - h[i - 1]);
        if (i >= 2) dp[i] = min(dp[i], dp[i - 2] + llabs(h[i] - h[i - 2]));
    }
    return dp[n - 1];
}

ll frogBottomUpPush(const vector<ll>& h) {
    int n = (int)h.size();
    if (n <= 1) return 0;
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] >= INF) continue;
        if (i + 1 < n) dp[i + 1] = min(dp[i + 1], dp[i] + llabs(h[i + 1] - h[i]));
        if (i + 2 < n) dp[i + 2] = min(dp[i + 2], dp[i] + llabs(h[i + 2] - h[i]));
    }
    return dp[n - 1];
}

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> h = {10, 30, 40, 20};
    int n = (int)h.size();
    vector<ll> memo(n, -1);
    vector<char> vis(n, 0);
    cout << frogTopDown(n - 1, h, memo, vis) << "\n";
    cout << frogBottomUpPull(h) << " " << frogBottomUpPush(h) << " " << frogRolling(h) << "\n";
    return 0;
}
```

**Jebakan:**

1. Stack overflow top-down pada `n = 1e5`.
2. Sentinel `-1` tabrakan dengan jawaban sah negatif — pakai `visited`.
3. Push tanpa men-skip `INF`, lalu `INF + |h|` menjadi sampah yang menular.
4. Urutan loop bottom-up salah sehingga membaca state yang belum diisi.

**Kompleksitas:** `O(n)` waktu. Top-down: `O(n)` heap + `O(n)` stack. Bottom-up: `O(n)` atau `O(1)` memori.

### Studi kasus menambah dimensi

Kalau masa depan butuh informasi yang tidak ada di indeks saja, tambah dimensi.

**Liburan (AtCoder DP-C).** Tidak boleh aktivitas yang sama dua hari berturut-turut.

- Salah: `dp[i]` = kebahagiaan sampai hari `i` — tidak tahu aktivitas kemarin.
- Benar: `dp[i][act]` = kebahagiaan sampai hari `i` jika hari `i` memilih `act`.

```cpp
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
```

**Tiket diskon.** Satu kupon memotong satu sisi 50 persen. `dp[u]` tidak cukup: tiba dengan kupon utuh berbeda dengan tiba tanpa kupon. Pakai `dp[u][k]`.

---

## Tangga

**Teori:** Ada `n` anak tangga. Sekali langkah naik 1 atau 2. Banyak cara mencapai puncak adalah Fibonacci. Turunkan dari keputusan terakhir, jangan kenali. Varian: langkah `1..k`, anak tangga rusak, biaya minimum saat menginjak (LC 746).

**Kapan:** menghitung barisan langkah ke posisi `n`. **Tidak:** langkah boleh mundur (bukan DAG), atau ada constraint yang butuh state tambahan (misalnya "tidak boleh dua langkah 2 berturut-turut" → tambah dimensi).

**STATE:** `dp[i]` adalah banyaknya cara mencapai anak tangga ke-`i`.

**TRANSISI:** `dp[i] = dp[i-1] + dp[i-2]` karena langkah terakhir hanya 1 atau 2, dan kedua himpunan cara itu tidak tumpang tindih.

**BASIS:** `dp[0] = 1` (diam), `dp[1] = 1`. Untuk `n = 0` jawaban 1.

**Proses angka:** `n = 4`.

```
i    dp[i]   cara
0    1       ()
1    1       (1)
2    2       (1+1), (2)
3    3       (1+1+1), (1+2), (2+1)
4    5       (1+1+1+1), (1+1+2), (1+2+1), (2+1+1), (2+2)
```

Langkah `1..3`, `n = 4`:

```
dp[0] = 1
dp[1] = dp[0] = 1
dp[2] = dp[1]+dp[0] = 2
dp[3] = dp[2]+dp[1]+dp[0] = 4
dp[4] = dp[3]+dp[2]+dp[1] = 7
```

Anak tangga 2 rusak: `dp[2] = 0`, lalu `dp[3] = 0+1+1 = 2`, `dp[4] = 2+0+1 = 3`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll tangga(int n) {
    ll a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return n == 0 ? 1 : b;
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << tangga(5) << "\n";                 // 8
    vector<char> rusak(6, 0);
    rusak[2] = 1;
    cout << tanggaK(5, 2, rusak) << "\n";
    cout << tanggaPrefix(4, 3) << "\n";        // 7
    cout << tanggaMinCost({10, 15, 20}) << "\n";
    return 0;
}
```

**Jebakan:**

1. `dp[0] = 0` membuat semua nol.
2. Tangga rusak: `continue` tanpa menugaskan `0`, nilai lama tersisa.
3. Lupa modulo.
4. LC 746: biaya dibayar saat menginjak, boleh mulai dari indeks 0 atau 1, jawaban adalah biaya mencapai "atap" setelah `n`.

**Kompleksitas:** langkah 1/2: `O(n)` / `O(1)`. Langkah `1..k` naif `O(nk)`, prefix `O(n)`. `k = 6` (CSES Dice Combinations) naif sudah cukup.

---

## House robber

**Teori:** Deret rumah, tidak boleh merampok dua yang bersebelahan, maksimalkan total. Greedy selang-seling gagal: `[2, 1, 1, 2]` memberi 3 secara greedy, optimal 4. Keputusan terakhir: rumah `i` diambil atau tidak. Varian melingkar (LC 213): rumah pertama dan terakhir bertetangga — jalankan versi linear dua kali, bukan menambal `if`.

**Kapan:** pilih subset dengan larangan tetangga. **Tidak:** boleh ambil bersebelahan; itu prefix sum. Kalau graf umum, itu independent set (NP / tree DP).

**STATE:** `dp[i]` adalah total maksimum setelah mempertimbangkan rumah `0..i` ("sampai i"), rumah `i` boleh diambil atau dilewati.

**TRANSISI:** `dp[i] = max(dp[i-1], dp[i-2] + a[i])` — lewati `i`, atau ambil `i` dan haramkan `i-1`.

**BASIS:** `dp[-1] = dp[-2] = 0` konsisten, sehingga rolling `prev2 = 0, prev1 = 0` tidak butuh kasus `n = 1` khusus. Secara eksplisit: `dp[0] = a[0]`, `dp[1] = max(a[0], a[1])`.

**Proses angka:** `a = [2, 1, 1, 2]`.

```
i   a[i]   lewati=dp[i-1]   ambil=dp[i-2]+a[i]   dp[i]
0   2      —                2                    2
1   1      2                1                    2
2   1      2                2+1=3                3
3   2      3                2+2=4                4
```

Jawaban `dp[3] = 4` (rumah 0 dan 3).

Melingkar: tanpa akhir `[2,1,1]` → 3; tanpa awal `[1,1,2]` → 3; `n = 4` linear 4, tetapi 0 dan 3 bertetangga jadi 4 haram. `max(3, 3) = 3`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll robber(const vector<ll>& a) {
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
    return max(robber(tanpaAkhir), robber(tanpaAwal));
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> a = {2, 1, 1, 2};
    cout << robber(a) << "\n";            // 4
    cout << robberCircular(a) << "\n";    // 3
    for (int i : robberPilihan(a)) cout << i << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Greedy selang-seling.
2. Melingkar ditambal `if` di rekurens.
3. `n = 1` pada versi melingkar: rentang kosong.
4. `prev2 = prev1` harus sebelum `prev1 = cur`.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori. Rekonstruksi `O(n)`.

---

## Frog jump

**Teori:** Katak di batu 0 ingin ke `n-1`. Dari `i` boleh ke `i+1..i+k` dengan biaya `|h[i]-h[j]|`. Greedy "loncat ke tinggi paling mirip" gagal karena biaya lokal kecil bisa menutup posisi murah nanti. Untuk `k` besar dan biaya berbentuk `dp[j] + c[i]`, pakai deque monoton (bukan file ini).

**Kapan:** AtCoder DP-A (`k = 2`), DP-B (`k ≤ 100`). **Tidak:** `n, k = 1e5` dengan `O(nk)`.

**STATE:** `dp[i]` adalah biaya minimum untuk sampai di batu `i`.

**TRANSISI:** `dp[i] = min_{1≤j≤k, j≤i} (dp[i-j] + |h[i]-h[i-j]|)`.

**BASIS:** `dp[0] = 0`. State lain diisi `INF`.

**Proses angka:** `h = [10, 30, 40, 20]`, `k = 2`.

```
dp[0] = 0
dp[1] = 0 + |30-10| = 20
dp[2] = min(20+|40-30|, 0+|40-10|) = 30
dp[3] = min(30+|20-40|, 20+|20-30|) = 30
```

Jalur `0 → 1 → 3` biaya 30.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> h = {10, 30, 40, 20};
    cout << frog(h, 2) << "\n";
    for (int x : frogJalur(h, 2)) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** inisialisasi `dp` dengan 0. Overflow `INF + |h|`. Greedy tinggi terdekat.

**Kompleksitas:** `O(nk)` waktu, `O(n)` memori.

---

## Kadane

**Teori:** Subarray tidak kosong dengan jumlah maksimum. Definisi "sampai i" buntu: tidak tahu apakah subarray terbaik sampai `i-1` bisa disambung. Definisi yang benar: jumlah terbaik di antara subarray yang **berakhir tepat di i**. Keputusan: mulai ulang di `i`, atau sambung `i-1`. Itulah Kadane — DP yang digulung, bukan trik tiga baris.

**Kapan:** subarray kontigu, jumlah/produk maksimum. **Tidak:** subsequence (boleh loncat) — itu beda soal. Kalau subarray kosong diizinkan, jawaban tidak boleh negatif.

**STATE:** `dp[i]` adalah jumlah maksimum dari subarray yang berakhir tepat di indeks `i`.

**TRANSISI:** `dp[i] = max(a[i], dp[i-1] + a[i])`.

**BASIS:** `dp[0] = a[0]`. Jawaban = maksimum seluruh `dp[i]`, diinisialisasi `a[0]`, bukan 0.

**Proses angka:** `a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`.

```
i   a[i]   cur = max(a[i], cur+a[i])   best
0   -2     -2                          -2
1    1      1                          1
2   -3     -2                          1
3    4      4                          4
4   -1      3                          4
5    2      5                          5
6    1      6                          6
7   -5      1                          6
8    4      5                          6
```

Subarray `[4, -1, 2, 1]` jumlah 6, indeks `[3, 6]`.

Semua negatif `[-5, -2, -9]`: `best` harus `-2`, bukan 0.

Melingkar: `max(kadaneMax, total - kadaneMin)`, kecuali semua negatif.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
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
3. Melingkar: `total - min` = 0 saat semua negatif (subarray kosong).
4. Produk: menugaskan `mx` sebelum menghitung `mn` baru.

**Kompleksitas:** `O(n)` waktu, `O(1)` memori.

---

## Coin change minimum

**Teori:** Pecahan koin tak terbatas, bentuk tepat `x` dengan **sedikit mungkin** koin. Greedy pecahan terbesar gagal pada sistem non-kanonik: koin `{1,3,4}`, target 6 → greedy `4+1+1` (3 koin), optimal `3+3` (2 koin). Rupiah kanonik, soal CP hampir selalu arbitrer.

**Kapan:** "jumlah koin minimum", stok tak terbatas. **Tidak:** tiap koin sekali (0-1), atau stok terbatas (bounded).

**STATE:** `dp[v]` adalah jumlah koin minimum untuk membentuk nominal tepat `v`. Nilai `INF` berarti belum bisa.

**TRANSISI:** `dp[v] = min atas koin c ≤ v dari (dp[v-c] + 1)`, hanya jika `dp[v-c]` bukan `INF`.

**BASIS:** `dp[0] = 0`. Lainnya `INF`.

**Proses angka:** koin `{1, 3, 4}`, `x = 6`.

```
v    pilihan                         dp[v]
0    —                               0
1    1+dp[0]                         1
2    1+dp[1]                         2
3    min(1+dp[2], 1+dp[0])           1
4    min(1+dp[3], 1+dp[1], 1+dp[0])  1
5    min(1+dp[4], 1+dp[2], 1+dp[1])  2
6    min(1+dp[5], 1+dp[3], 1+dp[2])  2   <- 3+3
```

Rekonstruksi: `pick[6] = 3`, `pick[3] = 3` → `{3, 3}`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF_INT = 1e9;

int coinChangeMin(int x, const vector<int>& coins) {
    if (x == 0) return 0;
    vector<int> dp(x + 1, INF_INT);
    dp[0] = 0;
    for (int i = 1; i <= x; i++)
        for (int c : coins)
            if (i >= c && dp[i - c] != INF_INT)
                dp[i] = min(dp[i], dp[i - c] + 1);
    return dp[x] == INF_INT ? -1 : dp[x];
}

pair<int, vector<int>> coinChangeReconstruct(int x, const vector<int>& coins) {
    if (x == 0) return {0, {}};
    vector<int> dp(x + 1, INF_INT), pick(x + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= x; i++)
        for (int c : coins)
            if (i >= c && dp[i - c] != INF_INT && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
                pick[i] = c;
            }
    if (dp[x] == INF_INT) return {-1, {}};
    vector<int> res;
    for (int cur = x; cur > 0; cur -= pick[cur]) res.push_back(pick[cur]);
    return {dp[x], res};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> coins = {1, 3, 4};
    cout << coinChangeMin(6, coins) << "\n"; // 2
    auto [cnt, isi] = coinChangeReconstruct(6, coins);
    cout << cnt << " :";
    for (int c : isi) cout << " " << c;
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Greedy pecahan terbesar.
2. `INF + 1` overflow jika `INF = INT_MAX`.
3. Tidak mengembalikan `-1` saat mustahil.
4. Loop mundur (itu 0-1, tiap koin sekali).

**Kompleksitas:** `O(n · x)` waktu, `O(x)` memori.

---

## Coin combinations

**Teori:** "Berapa cara" bukan "berapa koin". Urutan loop membedakan **permutasi** (urutan dihitung: `{1,2}` ≠ `{2,1}`) dan **kombinasi** (urutan diabaikan). Koin di luar + nominal maju = kombinasi (CSES Coin Combinations II). Nominal di luar + koin di dalam = permutasi (CSES Coin Combinations I).

**Kapan:** soal "number of ways" dengan koin tak terbatas. **Tidak:** jika stok tiap koin 1 — loop mundur seperti 0-1.

**STATE:** `dp[v]` adalah banyaknya cara (permutasi atau kombinasi, sesuai loop) membentuk nominal `v`.

**TRANSISI kombinasi:** untuk setiap koin `c`, untuk `v = c..x`: `dp[v] += dp[v-c]`. Koin `c` boleh dipakai lagi karena `dp[v-c]` sudah memuat `c`.

**TRANSISI permutasi:** untuk setiap `v`, untuk setiap koin: `dp[v] += dp[v-c]`. Urutan pemakaian menjadi urutan pengisian.

**BASIS:** `dp[0] = 1` (satu cara: tidak mengambil apa pun).

**Proses angka:** koin `{1, 2}`, `x = 3`.

Kombinasi (koin luar):

```
setelah 1: dp = [1, 1, 1, 1]     (hanya 1+1+1)
setelah 2: dp[2] += dp[0] -> 2   (1+1 atau 2)
           dp[3] += dp[1] -> 2   (1+1+1 atau 1+2)
```

Cara: `{1,1,1}`, `{1,2}`. Jawaban 2.

Permutasi (nominal luar):

```
dp[0]=1
dp[1]=dp[0]=1                    (1)
dp[2]=dp[1]+dp[0]=2              (1+1, 2)
dp[3]=dp[2]+dp[1]=3              (1+1+1, 1+2, 2+1)
```

Jawaban 3.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

ll coinPermutasi(int x, const vector<int>& coins) {
    vector<ll> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= x; i++)
        for (int c : coins)
            if (i >= c) dp[i] = (dp[i] + dp[i - c]) % MOD;
    return dp[x];
}

ll coinKombinasi(int x, const vector<int>& coins) {
    vector<ll> dp(x + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int i = c; i <= x; i++) dp[i] = (dp[i] + dp[i - c]) % MOD;
    return dp[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> coins = {1, 2};
    cout << coinKombinasi(3, coins) << "\n"; // 2
    cout << coinPermutasi(3, coins) << "\n"; // 3
    return 0;
}
```

**Jebakan:** tertukar I dan II. Lupa `dp[0] = 1`. Lupa modulo. Loop mundur pada unbounded.

**Kompleksitas:** `O(n · x)` waktu, `O(x)` memori.

---

## Unbounded knapsack

**Teori:** Tiap barang stok tak terbatas. Loop kapasitas **maju**: `dp[w - wt]` sudah memuat barang yang sama, jadi boleh diambil lagi. Satu arah loop memisahkan unbounded dari 0-1.

**Kapan:** "boleh ambil berkali-kali", produksi tanpa batas. **Tidak:** tiap barang unik (0-1).

**STATE:** `dp[w]` adalah nilai maksimum dengan kapasitas tepat atau paling banyak `w`, setelah memproses barang yang sudah dilooping (dan tiap barang boleh berulang).

**TRANSISI:** untuk barang `(wt, val)`, untuk `w = wt..W` maju: `dp[w] = max(dp[w], dp[w-wt] + val)`.

**BASIS:** `dp[0] = 0`. Lainnya 0 jika kapasitas tidak wajib penuh; `INF` jika wajib tepat dan kita meminimalkan biaya.

**Proses angka:** satu barang berat 2 nilai 3, `W = 6`.

```
w=2: dp[2] = 0+3 = 3
w=4: dp[4] = 3+3 = 6
w=6: dp[6] = 6+3 = 9
```

Loop mundur pada barang yang sama hanya memberi 3.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF_LL = (ll)4e18;

ll unboundedKnapsackMax(int W, const vector<int>& wt, const vector<ll>& val) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = wt[i]; w <= W; w++)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

ll unboundedMinCost(int W, const vector<int>& wt, const vector<ll>& cost) {
    vector<ll> dp(W + 1, INF_LL);
    dp[0] = 0;
    for (size_t i = 0; i < wt.size(); i++)
        for (int w = wt[i]; w <= W; w++)
            if (dp[w - wt[i]] < INF_LL)
                dp[w] = min(dp[w], dp[w - wt[i]] + cost[i]);
    return dp[W] == INF_LL ? -1 : dp[W];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << unboundedKnapsackMax(6, {2}, {3}) << "\n"; // 9
    return 0;
}
```

**Jebakan:** loop mundur. Tidak cek `INF` sebelum menambah. `int` overflow nilai.

**Kompleksitas:** `O(n · W)` waktu, `O(W)` memori.

---

## 0-1 knapsack

**Teori:** Tiap barang paling banyak sekali. Greedy rasio benar hanya untuk fractional. Contoh: `W = 10`, A(6,7), B(5,5), C(5,5) — rasio ambil A nilai 7, optimal B+C = 10. Versi 1D loop **mundur** agar `dp[c-w]` masih dari barang sebelumnya. Hitung `n*W` dulu: `W = 1e18` bukan soal 1D kapasitas.

**Kapan:** pilih subset, kapasitas `W`, `n*W ≤ 1e8`. **Tidak:** `W` raksasa nilai kecil → DP atas nilai. `n ≤ 40`, `W` besar → meet in the middle.

**STATE:** `dp[i][c]` adalah nilai maksimum memakai subset dari `i` barang pertama dengan total berat paling banyak `c`. Versi 1D: `dp[c]` setelah barang `0..i-1` selesai.

**TRANSISI:** `dp[i][c] = max(dp[i-1][c], dp[i-1][c-w[i]] + v[i])` jika `c ≥ w[i]`.

**BASIS:** `dp[0][c] = 0` untuk semua `c`. Tanpa barang, nilai nol.

**Proses angka:** barang (3,3), (2,4), (4,2), `W = 5`.

```
       c=0  1  2  3  4  5
i=0     0   0  0  0  0  0
i=1     0   0  0  3  3  3     + (3,3)
i=2     0   0  4  4  4  7     + (2,4)  sel 5 = 3+4
i=3     0   0  4  4  4  7     + (4,2)  tidak memperbaiki
```

Jawaban 7. Rekonstruksi: `dp[3][5] == dp[2][5]` → barang 3 tidak. `dp[2][5] != dp[1][5]` → barang 2 diambil, sisa 3. `dp[1][3] != dp[0][3]` → barang 1 diambil.

Loop 1D mundur barang (2,3), `W = 6`:

```
c: 6,5,4,3,2...  dp[6]=dp[4]+3 tetapi dp[4] masih 0 → hanya 3
```

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll knapsack01(const vector<int>& w, const vector<ll>& v, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++)
        for (int c = W; c >= w[i]; c--)
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

vector<vector<ll>> knapsackTabel(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];
            if (c >= w[i - 1])
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
        }
    return dp;
}

vector<int> knapsackPilih(const vector<int>& w, int W, const vector<vector<ll>>& dp) {
    vector<int> dipilih;
    int c = W;
    for (int i = (int)w.size(); i >= 1; i--)
        if (dp[i][c] != dp[i - 1][c]) {
            dipilih.push_back(i - 1);
            c -= w[i - 1];
        }
    reverse(dipilih.begin(), dipilih.end());
    return dipilih;
}

ll knapsackAtasNilai(const vector<int>& w, const vector<ll>& v, ll W) {
    ll totalV = accumulate(v.begin(), v.end(), 0LL);
    const ll INF = LLONG_MAX / 4;
    vector<ll> dp(totalV + 1, INF);
    dp[0] = 0;
    for (size_t i = 0; i < w.size(); i++)
        for (ll val = totalV; val >= v[i]; val--)
            if (dp[val - v[i]] != INF)
                dp[val] = min(dp[val], dp[val - v[i]] + w[i]);
    for (ll val = totalV; val >= 0; val--)
        if (dp[val] <= W) return val;
    return 0;
}

ll knapsackNaif(const vector<int>& w, const vector<ll>& v, int W) {
    int n = (int)w.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll bw = 0, bv = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                bw += w[i];
                bv += v[i];
            }
        if (bw <= W) best = max(best, bv);
    }
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> w = {3, 2, 4};
    vector<ll> v = {3, 4, 2};
    int W = 5;
    cout << knapsack01(w, v, W) << " " << knapsackNaif(w, v, W) << "\n";
    auto dp = knapsackTabel(w, v, W);
    for (int i : knapsackPilih(w, W, dp)) cout << i << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:**

1. Loop maju pada 0-1.
2. Greedy rasio.
3. Tidak menghitung `n*W` sebelum menulis DP.
4. Rekonstruksi membandingkan `dp[i][c]` dengan `dp[i][c-w]` (salah baris).

**Kompleksitas:** 1D `O(nW)` waktu, `O(W)` memori. 2D `O(nW)` memori. Atas nilai `O(n Σv)`. Naif `O(2^n n)` untuk stress `n ≤ 20`.

---

## Bounded knapsack

**Teori:** Barang `i` tersedia `k[i]` buah. Loop `k` kali naif `O(W Σ k)`. Dekomposisi biner pecah `k` menjadi `1, 2, 4, ..., sisa` lalu tiap paket diperlakukan sebagai barang 0-1. `k = 1e6` menjadi ≈ 20 paket.

**Kapan:** stok terbatas lebih dari 1, kurang dari tak hingga. **Tidak:** `k = 1` (0-1 murni), `k` sangat besar dibanding `W/w` (efektif unbounded).

**STATE:** sama seperti 0-1 setelah paket biner dibuat: `dp[c]` nilai maksimum kapasitas `c`.

**TRANSISI:** tiap paket `(q*w, q*v)` di-loop mundur.

**BASIS:** `dp[0] = 0`.

**Proses angka:** barang berat 2 nilai 3, stok 5, `W = 7`. `c_eff = min(5, 3) = 3`. Paket 1 lalu 2.

```
paket 1: (2,3)  -> dp[2]=3, dp[4]=3, dp[6]=3
paket 2: (4,6)  -> dp[6]=max(3, 3+6)=9, dp[4]=6
```

Nilai 9 = tiga kali barang (berat 6).

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll knapsackBounded(const vector<int>& w, const vector<ll>& v, const vector<int>& k, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); i++) {
        int sisa = k[i];
        for (int p = 1; sisa > 0; p *= 2) {
            int ambil = min(p, sisa);
            sisa -= ambil;
            ll bobot = (ll)ambil * w[i], nilai = (ll)ambil * v[i];
            if (bobot > W) continue;
            for (int c = W; c >= bobot; c--)
                dp[c] = max(dp[c], dp[c - bobot] + nilai);
        }
    }
    return dp[W];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << knapsackBounded({2}, {3}, {5}, 7) << "\n"; // 9
    return 0;
}
```

**Jebakan:** paket di-loop maju. Tidak memotong `k` oleh `W/w`. Overflow `p *= 2` pakai `int` jika `k` besar — di sini `sisa` yang membatasi.

**Kompleksitas:** `O(W · Σ log k)` waktu, `O(W)` memori.

---

## Subset sum

**Teori:** Ada subset jumlah tepat `S`? Ini knapsack 0-1 dengan nilai = berat, jawaban boolean. `bisa[0] = true` wajib: subset kosong. Loop mundur. Bitset `bs |= bs << x` mempercepat 64×.

**Kapan:** "apakah bisa membentuk", "semua jumlah yang mungkin". **Tidak:** elemen boleh diulang (itu coin). `S` raksasa `n` kecil → MITM.

**STATE:** `bisa[s]` bernilai benar jika ada subset dari elemen yang sudah diproses yang jumlahnya tepat `s`.

**TRANSISI:** untuk setiap `x`, mundur `s = S..x`: `bisa[s] |= bisa[s-x]`.

**BASIS:** `bisa[0] = 1`.

**Proses angka:** `a = [3, 5, 7]`, `S = 10`.

```
awal:     0
+3:       0, 3
+5:       0, 3, 5, 8
+7:       0, 3, 5, 7, 8, 10, 12(terpotong), 15(terpotong)
```

`bisa[10] = true` (`3+7`).

Loop maju `a = [3]`, `S = 6`: `bisa[3]` nyala lalu `bisa[6]` nyala — 3 dipakai dua kali. Salah.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

vector<char> subsetSum(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            if (bisa[c - x]) bisa[c] = 1;
    return bisa;
}

vector<ll> subsetSumCara(const vector<int>& a, int S) {
    vector<ll> cara(S + 1, 0);
    cara[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            cara[c] = (cara[c] + cara[c - x]) % MOD;
    return cara;
}

template <size_t MAXS>
bitset<MAXS> subsetSumBitset(const vector<int>& a) {
    bitset<MAXS> bs;
    bs[0] = 1;
    for (int x : a) bs |= bs << x;
    return bs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> a = {3, 5, 7, 10};
    auto bisa = subsetSum(a, 12);
    cout << (bisa[12] ? "YES\n" : "NO\n");
    cout << subsetSumCara(a, 12)[12] << "\n";
    auto bs = subsetSumBitset<64>(a);
    cout << bs[12] << "\n";
    return 0;
}
```

**Jebakan:** lupa `bisa[0]`. Loop maju. Bitset ukuran compile-time: `target >= MAXS` harus dicek. Menghitung cara tanpa modulo.

**Kompleksitas:** `O(nS)` atau bitset `O(nS / 64)`. Memori `O(S)`.

---

## Partition

**Teori:** Bagi array jadi dua subset jumlah sama, atau selisih minimum. Jumlah total `T`. Cari subset jumlah `s ≤ T/2` terbesar yang mungkin, selisih `T - 2s`. Partisi sama persis: `T` genap dan `bisa[T/2]`.

**Kapan:** "bagi dua sama rata", "selisih partisi minimum". **Tidak:** lebih dari dua kelompok (butuh dimensi tambahan), atau urutan/kontigu (itu prefix).

**STATE:** `bisa[s]` sama seperti subset sum sampai `T`.

**TRANSISI:** sama, loop mundur.

**BASIS:** `bisa[0] = 1`.

**Proses angka:** `a = [1, 5, 11, 5]`, `T = 22`, target 11.

```
+1:   0, 1
+5:   0, 1, 5, 6
+11:  0, 1, 5, 6, 11, 12, 16, 17
+5:   ... 11 sudah nyala
```

`bisa[11] = true`, selisih 0. Contoh `[1, 2, 3, 9]`, `T = 15`, `s` terbaik 6, selisih `15-12 = 3`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int minPartitionDiff(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    vector<char> can = [&]() {
        vector<char> bisa(total + 1, 0);
        bisa[0] = 1;
        for (int x : a)
            for (int s = total; s >= x; s--)
                bisa[s] = bisa[s] | bisa[s - x];
        return bisa;
    }();
    for (int s = total / 2; s >= 0; s--)
        if (can[s]) return total - 2 * s;
    return total;
}

bool canPartition(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total % 2) return false;
    auto bisa = vector<char>(total / 2 + 1, 0);
    bisa[0] = 1;
    int S = total / 2;
    for (int x : a)
        for (int s = S; s >= x; s--)
            if (bisa[s - x]) bisa[s] = 1;
    return bisa[S];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << canPartition({1, 5, 11, 5}) << "\n";      // 1
    cout << minPartitionDiff({1, 2, 3, 9}) << "\n";   // 3
    return 0;
}
```

**Jebakan:** `T` ganjil tetap bisa diminta selisih minimum. Overflow `int` pada `total`. Lupa bahwa partisi tidak peduli kontigu.

**Kompleksitas:** `O(nT)` waktu, `O(T)` memori.

---

## LIS

**Teori:** Subsekuens (boleh loncat, urutan tetap) terpanjang yang naik. Greedy "ambil selama naik" gagal: `[1, 100, 2, 3, 4]`. Definisi "sampai i" tidak tahu ekor, jadi tidak bisa menyambung. Pakai "berakhir tepat di i". Versi `O(n log n)` menyimpan `tails[k]` = ekor terkecil di antara semua naik berpanjang `k+1`. `tails` **bukan** LIS-nya; hanya ukurannya benar. `lower_bound` = ketat naik, `upper_bound` = tidak menurun.

**Kapan:** panjang / hitung / rekonstruksi subsekuens monoton. `n ≤ 5000` → `O(n^2)` mudah dimodifikasi. `n ≤ 2e5` → `O(n log n)`. **Tidak:** substring kontigu (itu dua pointer).

**STATE O(n²):** `dp[i]` adalah panjang LIS yang berakhir tepat di indeks `i`.

**TRANSISI:** `dp[i] = 1 + max{ dp[j] : j < i, a[j] < a[i] }`, atau 1 jika kosong.

**BASIS:** setiap `dp[i] = 1` (elemen itu sendiri). Jawaban `max(dp)`, bukan `dp[n-1]`.

**Proses angka O(n²):** `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

```
i   a[i]  pendahulu lebih kecil        dp[i]
0   10    —                            1
1    9    —                            1
2    2    —                            1
3    5    2                            2
4    3    2                            2
5    7    2,5,3                        3
6   101   2,5,3,7                      4
7    18   2,5,3,7                      4
```

`max = 4`. Contoh LIS `[2,5,7,18]` atau `[2,3,7,101]`.

**Proses tails:** `a = [1, 6, 7, 2, 3]`.

```
x=1  tails [1]
x=6  [1, 6]
x=7  [1, 6, 7]
x=2  [1, 2, 7]   <- [1,2,7] BUKAN subsekuens sah
x=3  [1, 2, 3]
```

Panjang 3 benar. Isi tengah bisa gado-gado.

Uji `[1,1,1]`: ketat → 1; tidak menurun → 3.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;

int lisN2(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    return n ? *max_element(dp.begin(), dp.end()) : 0;
}

int lisStrict(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int lisNonDec(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int lds(vector<int> a) {
    for (int& x : a) x = -x;
    return lisStrict(a);
}

vector<int> lisRebuild(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return {};
    vector<int> tails, idx, par(n, -1);
    for (int i = 0; i < n; i++) {
        int p = (int)(lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin());
        if (p > 0) par[i] = idx[p - 1];
        if (p == (int)tails.size()) {
            tails.push_back(a[i]);
            idx.push_back(i);
        } else {
            tails[p] = a[i];
            idx[p] = i;
        }
    }
    vector<int> res;
    for (int v = idx.back(); v != -1; v = par[v]) res.push_back(a[v]);
    reverse(res.begin(), res.end());
    return res;
}

ll countLIS(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    vector<int> len(n, 1);
    vector<ll> cnt(n, 1);
    int best = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) cnt[i] = (cnt[i] + cnt[j]) % MOD;
            }
        best = max(best, len[i]);
    }
    ll total = 0;
    for (int i = 0; i < n; i++)
        if (len[i] == best) total = (total + cnt[i]) % MOD;
    return total;
}

int russianDoll(vector<pair<int, int>> box) {
    sort(box.begin(), box.end(), [](auto A, auto B) {
        if (A.first != B.first) return A.first < B.first;
        return A.second > B.second;
    });
    vector<int> h;
    for (auto& b : box) h.push_back(b.second);
    return lisStrict(h);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lisN2(a) << " " << lisStrict(a) << "\n";
    cout << lisNonDec({1, 1, 1}) << " " << lisStrict({1, 1, 1}) << "\n";
    for (int x : lisRebuild(a)) cout << x << " ";
    cout << "\n" << countLIS(a) << "\n";
    return 0;
}
```

**Jebakan:**

1. Jawaban `dp[n-1]` padahal definisinya berakhir tepat di i.
2. Mencetak `tails` sebagai LIS.
3. `lower_bound` vs `upper_bound` tertukar.
4. Russian doll: saat lebar sama, tinggi harus **menurun** agar dua kotak sama lebar tidak saling menumpuk di LIS.

**Kompleksitas:** `O(n^2)` atau `O(n log n)` waktu. Memori `O(n)`. Hitung banyak LIS biasanya `O(n^2)`.

---

## Template gabungan Day-143

Salin fungsi yang dibutuhkan. Semua 0-indexed.

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007LL;
const int INF_INT = 1e9;
const ll INF = LLONG_MAX / 4;

ll tangga(int n);
ll robber(const vector<ll>& a);
ll frog(const vector<ll>& h, int k);
ll kadane(const vector<ll>& a);
int coinChangeMin(int x, const vector<int>& coins);
ll coinKombinasi(int x, const vector<int>& coins);
ll knapsack01(const vector<int>& w, const vector<ll>& v, int W);
vector<char> subsetSum(const vector<int>& a, int S);
int lisStrict(const vector<int>& a);
```

Implementasinya ada di bagian masing-masing. Pola mengingat:

```
berapa cara     -> dp[i] = dp[i-1] + dp[i-2]
maksimum        -> dp[i] = max(dp[i-1], dp[i-2] + a[i])
minimal langkah -> dp[v] = min(dp[v], dp[v-c] + 1)
bisa/tidak      -> bisa[s] |= bisa[s-x]
```

Hukum arah loop kapasitas:

```
maju   w = wt .. W     unbounded / kombinasi koin
mundur w = W .. wt     0-1 / subset sum / bounded paket
```

---

## Peta jebakan file ini

| Gejala | Penyebab khas | Perbaikan |
|---|---|---|
| Semua nol | `dp[0] = 0` pada "berapa cara" | `dp[0] = 1` |
| WA kasus besar, AC kecil | "sampai i" vs "berakhir di i" | tulis STATE, cek tempat jawaban |
| WA array negatif | Kadane `best = 0` | `best = a[0]` |
| WA knapsack | loop maju pada 0-1 | mundur |
| TLE knapsack | `W = 1e9` | DP nilai / MITM |
| WA coin ways | loop I vs II | uji `{1,2}` target 3 → 2 vs 3 |
| WA LIS | `dp[n-1]` atau cetak tails | `max(dp)` / parent |
| RE top-down | `n = 1e5` rekursi | bottom-up |
| WA robber lingkar | tambalan `if` | dua kali linear |
| Overflow | `INF + 1` atau `int` | `INF = 1e9`, `ll` |

Batas kasar 1–2 detik C++: `n ≤ 1e8` operasi. `n = 5000` → `O(n^2)` pas. `n = 400` → `O(n^3)` pas. `n = 20` → `O(2^n n^2)` TSP. `n = 40` → MITM.

Latihan terarah (buka di situs asalnya, jangan disalin ke repo ini): CSES Dice Combinations, Minimizing Coins, Coin Combinations I/II, Knapsack; AtCoder DP-A/B/C/D/E/F; LeetCode 70, 198, 213, 53, 322, 300.

---

## Jump game (varian 1D)

**Teori:** Array `a[i]` = jarak lompat maksimum dari `i`. Apakah bisa ke akhir? Ini DP boolean, atau greedy "jangkauan terjauh" yang lebih cepat. Versi "minimal lompatan" kembali ke DP `min`.

**Kapan:** LC 55 / 45. **Tidak:** lompat ke belakang tanpa batas — bisa siklus.

**STATE:** `bisa[i]` benar jika indeks `i` dapat dicapai dari 0. Versi min: `dp[i]` adalah jumlah lompatan minimum ke `i`.

**TRANSISI:** jika `bisa[j]` dan `j + a[j] >= i` maka `bisa[i] = true`. Min: `dp[i] = min(dp[j]+1)` untuk `j` yang menjangkau `i`.

**BASIS:** `bisa[0] = true`, `dp[0] = 0`.

**Proses angka:** `a = [2, 3, 1, 1, 4]`.

```
i=0 jangkau 0..2
i=1 tercapai, jangkau 1..4  -> sudah ke akhir
min lompat: 0 -> 1 -> 4  (2 lompat), atau 0 -> 2? 2 hanya +1 ke 3, lalu 4: 3 lompat
optimal 2
```

`a = [3, 2, 1, 0, 4]`: dari 0..3 jangkauan max 3, `0` di indeks 3 memblokir. Tidak bisa.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;

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
    vector<int> dp(n, 1e9);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        if (dp[i] < 1e9)
            for (int k = 1; k <= a[i] && i + k < n; k++)
                dp[i + k] = min(dp[i + k], dp[i] + 1);
    return dp[n - 1] >= 1e9 ? -1 : dp[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << jumpBisa({2, 3, 1, 1, 4}) << " " << jumpMin({2, 3, 1, 1, 4}) << "\n";
    cout << jumpBisa({3, 2, 1, 0, 4}) << "\n";
    return 0;
}
```

**Jebakan:** DP `O(n^2)` pada `n = 1e5` — pakai greedy jangkauan. `dp` tidak di-skip saat `INF`.

**Kompleksitas:** greedy bisa `O(n)`. Min naif `O(n · max a)`.

---

## Checklist sebelum mengetik

Tulis di kertas (atau komentar atas kode) dalam kalimat lengkap:

```
STATE    : dp[?] = ...
TRANSISI : dari keputusan terakhir ...
BASIS    : ...
JAWABAN  : dp[n-1]  ATAU  max(dp)  ATAU  dp[n][W]
```

Uji tangan wajib:

1. `n = 0` atau array kosong (jika soal mengizinkan).
2. `n = 1`.
3. Semua negatif (Kadane, robber).
4. Satu kasus yang menggagalkan greedy.

Stress kecil untuk knapsack / subset:

```cpp
mt19937 rng(123);
for (int t = 0; t < 1000; t++) {
    int n = rng() % 8 + 1, W = rng() % 20;
    vector<int> w(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        w[i] = rng() % 8 + 1;
        v[i] = rng() % 20;
    }
    assert(knapsack01(w, v, W) == knapsackNaif(w, v, W));
}
```

---

## Tabel uji cepat operator

| Soal mini | Input | Jawaban | Pola |
|---|---|---|---|
| tangga n=5 | langkah 1/2 | 8 | `+` |
| robber | `[2,1,1,2]` | 4 | `max` skip tetangga |
| robber lingkar | sama | 3 | dua kali linear |
| Kadane | `[-2,1,-3,4,-1,2,1,-5,4]` | 6 | berakhir di i |
| Kadane all-neg | `[-5,-2,-9]` | -2 | bukan 0 |
| coin min | `{1,3,4}` → 6 | 2 | unbounded min |
| coin kombinasi | `{1,2}` → 3 | 2 | koin luar |
| coin permutasi | `{1,2}` → 3 | 3 | nominal luar |
| knapsack 0-1 | w`[3,2,4]` v`[3,4,2]` W=5 | 7 | loop mundur |
| unbounded | w`[2]` v`[3]` W=6 | 9 | loop maju |
| subset 12 | `[3,5,7,10]` | YES | mundur + `bisa[0]` |
| partisi | `[1,5,11,5]` | YES | `T/2` |
| LIS | `[10,9,2,5,3,7,101,18]` | 4 | `max(dp)` |
| LIS tails | `[1,6,7,2,3]` | 3 | jangan cetak tails |
| `[1,1,1]` ketat | | 1 | `lower_bound` |
| `[1,1,1]` nondec | | 3 | `upper_bound` |

Kalau kode kamu salah di satu baris tabel ini, perbaiki definisi dulu, baru loop.

---

## AtCoder DP-C dikerjakan penuh

**Proses angka:** 3 hari, poin

```
hari0: 10 40 70
hari1: 20 50 80
hari2: 30 60 90
```

```
dp0 = 10 40 70
dp1 A = 20 + max(40,70) = 90
    B = 50 + max(10,70) = 120
    C = 80 + max(10,40) = 120
dp2 A = 30 + max(120,120) = 150
    B = 60 + max(90,120) = 180
    C = 90 + max(90,120) = 210
```

Jawaban 210 (C tiap hari yang boleh: 70-50-90 bukan, 70-50 dilarang? Hari0 C=70, hari1 tidak boleh C, jadi B=120 atau A=90, lalu hari2 C=90+120=210). Urutan aktivitas `C, B, C`.

---

## Knapsack 1D jejak kapasitas

Barang (berat, nilai): (2,3), (3,4), (4,5). `W = 6`. Loop mundur per barang.

```
awal:     [0 0 0 0 0 0 0]
+(2,3):   [0 0 3 3 3 3 3]
+(3,4):   c=6: max(3, 3+4)=7
          c=5: max(3, 3+4)=7
          c=4: max(3, 0+4)=4
          c=3: max(3, 0+4)=4
          -> [0 0 3 4 4 7 7]
+(4,5):   c=6: max(7, 3+5)=8
          c=5: max(7, 3+5)=8
          c=4: max(4, 0+5)=5
          -> [0 0 3 4 5 8 8]
```

Jawaban 8: barang 0 dan 2 (berat 6, nilai 8) atau 1+0 = 7 kalah.

Kalau loop **maju** pada barang ketiga (4,5): setelah `c=4` jadi 5, `c=8` tidak ada, tetapi `c=6` memakai `dp[2]` yang sudah... tetap 8 di sini. Bahaya muncul saat barang kecil: maju pada (2,3) sendirian sudah mengisi 3,6,9.

---

Lanjut ke [14 — string, grid, range](14-dp-string-grid-range.md) untuk LCS, edit, grid, dan interval.
