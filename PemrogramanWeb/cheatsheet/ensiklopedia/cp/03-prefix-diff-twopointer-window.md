# 03 — Prefix, difference, two pointers, window

[← Sort dan bitset](02-stl-sort-bound-bitset.md) · [README dasar](README-dasar.md) · [Lanjut Kadane dan mono →](04-kadane-mono-stack-deque-compress.md)

> **Ide satu kalimat:** jumlah rentang jadi pengurangan, ubah rentang jadi dua coretan, dua jari yang hanya maju mengganti O(n²).

Day ComprogLearning: **029** prefix & difference, **032** two pointers & sliding window.

Semua 0-based inklusif kecuali disebut. `pre` berukuran `n+1`, `pre[0]=0`. `ll` wajib untuk jumlah.

## Daftar isi

- [Prefix sum 1D](#prefix-sum-1d)
- [Range sum query](#range-sum-query)
- [Prefix XOR](#prefix-xor)
- [Prefix count](#prefix-count)
- [Subarray jumlah = K](#subarray-jumlah--k)
- [Subarray kelipatan K](#subarray-kelipatan-k)
- [Prefix sum 2D](#prefix-sum-2d)
- [Difference array 1D](#difference-array-1d)
- [Difference array 2D](#difference-array-2d)
- [Two pointers berlawanan](#two-pointers-berlawanan)
- [Two pointers searah](#two-pointers-searah)
- [Sliding window ukuran tetap](#sliding-window-ukuran-tetap)
- [Sliding window terpanjang](#sliding-window-terpanjang)
- [Sliding window terpendek](#sliding-window-terpendek)

---

## Prefix sum 1D

> **Ide satu kalimat:** pasang patokan kilometer sekali, lalu setiap jarak jadi satu pengurangan.

### Prefix sum 1D

**Teori:** Analoginya patok KM di pinggir jalan. `pre[i]` = jumlah `i` elemen pertama, jadi `pre[0]=0` adalah gerbang kota. Alasan benar: jumlah `a[l]+…+a[r]` = (kota ke patok r+1) minus (kota ke patok l). Tidak ada cabang `if (l==0)`. Operasi harus punya invers: tambah punya kurang, XOR punya XOR. Min/max/gcd tidak punya invers — prefix tidak menolong.

**State:** `pre[i]` = `a[0]+…+a[i-1]`.
**Transisi:** `pre[i+1] = pre[i] + a[i]`.

**Kapan dipakai / kapan tidak.** Pakai banyak query jumlah pada array **diam**. Jangan jika ada update di tengah (Fenwick, Day 170). Jangan prefix min.

**Proses:** `a = [3, 1, 4, 1, 5]`.

1. `pre[0]=0`.
2. +3 → `pre[1]=3`.
3. +1 → `pre[2]=4`.
4. +4 → `pre[3]=8`.
5. +1 → `pre[4]=9`, +5 → `pre[5]=14`.

Tabel:

```
i      0  1  2  3  4
a[i]   3  1  4  1  5
pre    0  3  4  8  9  14
indeks pre: 0  1  2  3  4   5
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> bangunPrefix(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    return pre;
}

int main() {
    vector<ll> a = {3, 1, 4, 1, 5};
    auto pre = bangunPrefix(a);
    cout << pre[5] << '\n'; // 14
    cout << pre[3] << '\n'; // 8
    return 0;
}
```

**Jebakan:**
1. `int` untuk prefix.
2. `pre` berukuran `n` lalu `if (l==0)`.
3. Prefix min/max.

**Kompleksitas:** bangun O(n), memori O(n).

---

## Range sum query

> **Ide satu kalimat:** `jumlah a[l..r] = pre[r+1] - pre[l]` (0-based inklusif).

### Range sum query

**Teori:** Analoginya jarak KM 12 ke KM 19 = 7, tidak perlu jalan lagi. Setelah patok ada, tiap pertanyaan O(1). Alasan rumus benar: `pre[r+1]` memuat `a[0..r]`, `pre[l]` memuat `a[0..l-1]`, selisihnya `a[l..r]`. Versi 1-based: `pre[R]-pre[L-1]`. Jangan campur rumus.

**Kapan dipakai / kapan tidak.** Pakai q besar, array statis. Jangan untuk rata-rata tanpa bagi (bagi dulu jumlah). Jangan untuk “jumlah setelah beberapa update”.

**Proses:** `pre = [0,3,4,8,9,14]`, query `l=1, r=3` (nilai 1+4+1).

1. `pre[4] = 9` = 3+1+4+1.
2. `pre[1] = 3`.
3. `9-3=6`.
4. Cek manual `1+4+1=6`.
5. Query penuh `0..4`: `14-0=14`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> bangunPrefix(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    return pre;
}

ll rangeSum(const vector<ll>& pre, int l, int r) {
    return pre[r + 1] - pre[l];
}

int main() {
    vector<ll> a = {3, 1, 4, 1, 5};
    auto pre = bangunPrefix(a);
    cout << rangeSum(pre, 1, 3) << '\n'; // 6
    cout << rangeSum(pre, 0, 4) << '\n'; // 14
    return 0;
}
```

**Jebakan:**
1. `pre[r]-pre[l]` off-by-one.
2. `l>r` tidak dijaga.
3. Query 1-based tanpa `--`.

**Kompleksitas:** O(1) per query, memori O(n) untuk `pre`.

---

## Prefix XOR

> **Ide satu kalimat:** XOR adalah tambah tanpa pinjaman; inversnya XOR itu sendiri.

### Prefix XOR

**Teori:** Analoginya lampu yang saklarnya di-toggle: tekan dua kali = kembali. `x ^ x = 0`, `x ^ 0 = x`. Jadi XOR rentang = `px[r+1] ^ px[l]`. Alasan benar: suku `a[0..l-1]` muncul dua kali dan padam. CSES Range XOR Queries memakai ini.

**State:** `px[i]` = XOR `i` elemen pertama.
**Transisi:** `px[i+1] = px[i] ^ a[i]`.

**Kapan dipakai / kapan tidak.** Pakai query XOR statis, subarray XOR = 0. Jangan untuk OR/AND rentang (tidak ada invers).

**Proses:** `a = [1, 2, 3]` (`01,10,11`).

1. `px=[0,1,3,0]`.
2. XOR `a[0..1] = 1^2=3 = px[2]^px[0]`.
3. XOR `a[1..2] = 2^3=1 = px[3]^px[1] = 0^1`.
4. XOR seluruh = 0 = `px[3]`.
5. Subarray XOR 0: seluruh array.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> bangunPrefixXor(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> px(n + 1, 0);
    for (int i = 0; i < n; i++) px[i + 1] = px[i] ^ a[i];
    return px;
}

ll rangeXor(const vector<ll>& px, int l, int r) {
    return px[r + 1] ^ px[l];
}

int main() {
    vector<ll> a = {1, 2, 3};
    auto px = bangunPrefixXor(a);
    cout << rangeXor(px, 0, 1) << '\n'; // 3
    cout << rangeXor(px, 1, 2) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. Pakai `+` alih-alih `^`.
2. `px` `int` padahal nilai 64-bit.
3. Mengira AND punya prefix invers.

**Kompleksitas:** bangun O(n), query O(1), memori O(n).

---

## Prefix count

> **Ide satu kalimat:** ubah pertanyaan jadi array 0/1, lalu jumlahkan seperti prefix biasa.

### Prefix count

**Teori:** Analoginya counter orang berkacamata di antrean: tiap orang 1 atau 0, jumlah rentang = berapa yang berkacamata. AtCoder ABC122 C (GeT AC) adalah prefix count pola. Alasan benar: syarat boolean punya invers tambah. Syarat “berapa pasangan berurutan” dihitung di posisi i sebagai 1 jika `s[i-1]s[i]` cocok.

**Kapan dipakai / kapan tidak.** Pakai “berapa elemen genap di [l,r]”, “berapa huruf A”. Jangan jika syarat melibatkan seluruh rentang (bukan sifat per indeks).

**Proses:** `a = [2,5,4,7,8]`, berapa genap di `[1,3]` (5,4,7)?

1. Bendera: `[1,0,1,0,1]`.
2. `c = [0,1,1,2,2,3]`.
3. `c[4]-c[1] = 2-1 = 1` (hanya 4).
4. Seluruh array: `3` genap.
5. Tanpa prefix, tiap query scan ulang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> bangunPrefixCountGenap(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) c[i + 1] = c[i] + ((a[i] % 2 == 0) ? 1 : 0);
    return c;
}

int main() {
    vector<ll> a = {2, 5, 4, 7, 8};
    auto c = bangunPrefixCountGenap(a);
    cout << c[4] - c[1] << '\n'; // 1
    cout << c[5] - c[0] << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. `% 2` pada negatif di C++ — sisa bisa −1.
2. Menghitung pola 2 karakter di indeks salah.
3. `int` vs `ll` tidak masalah di count kecil, tapi konsisten lebih aman.

**Kompleksitas:** O(n) bangun, O(1) query, memori O(n).

---

## Subarray jumlah = K

> **Ide satu kalimat:** kalau jumlah sampai sini = S, cari berapa prefix lama yang bernilai S−K.

### Subarray jumlah = K

**Teori:** Analoginya dompet: saldo sekarang S, kamu ingin pengeluaran tepat K, jadi pernah ada saldo S−K. `freq[0]=1` adalah “prefix kosong” — subarray yang mulai di indeks 0. Alasan benar: `pre[r+1]-pre[l]=K` ⇔ `pre[l]=pre[r+1]-K`. Map menghitung berapa `l`. Sliding window **gagal** jika ada negatif (menambah elemen bisa menurunkan jumlah).

**State:** `cur` = prefix sampai i, `freq` = berapa kali prefix itu muncul **sebelum** i+1.
**Transisi:** `hasil += freq[cur-K]; freq[cur]++;`

**Kapan dipakai / kapan tidak.** Pakai K tetap, nilai boleh negatif. Jangan window “maju kanan, mundur kiri” jika tanda campur. Jangan `unordered_map` telanjang di CF.

**Proses:** `a = [1, 2, -1, 3]`, K=3.

1. `freq[0]=1`, `cur=0`.
2. +1 → cur=1; `1-3=-2` tidak ada; freq[1]=1.
3. +2 → cur=3; `3-3=0` ada 1 kali → ans=1 (subarray `[1,2]`).
4. −1 → cur=2; `2-3` tidak ada; freq[2]=1.
5. +3 → cur=5; `5-3=2` ada 1 kali → ans=2. Dua subarray: `[1,2]` dan `[3]`. (`[-1,3]=2`, `[2,-1,3]=4`, bukan 3.)

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll hitungSubarraySamaDengan(const vector<ll>& a, ll K) {
    map<ll, ll> freq;
    freq[0] = 1; // prefix kosong
    ll cur = 0, hasil = 0;
    for (ll v : a) {
        cur += v;
        auto it = freq.find(cur - K);
        if (it != freq.end()) hasil += it->second;
        freq[cur]++;
    }
    return hasil;
}

int main() {
    vector<ll> a = {1, 2, -1, 3};
    cout << hitungSubarraySamaDengan(a, 3) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Lupa `freq[0]=1`.
2. `freq[cur]++` sebelum menambah jawaban saat K=0 (menghitung kosong).
3. Window pada array ada negatif.

**Kompleksitas:** waktu O(n log n) dengan `map`, memori O(n).

---

## Subarray kelipatan K

> **Ide satu kalimat:** dua prefix dengan sisa bagi sama selisihnya habis dibagi K.

### Subarray kelipatan K

**Teori:** Analoginya jam 12 jam: kalau dua kali menunjukkan jam 3, selisih putaran adalah kelipatan 12. `cur % K` sama di dua prefix ⇒ subarray di antaranya ≡ 0 (mod K). Negatif: `(-7)%3` di C++ bisa −1. Normalisasi `((x%K)+K)%K`. `cnt[0]=1` untuk prefix kosong.

**Kapan dipakai / kapan tidak.** Pakai CSES Subarray Divisibility. Jangan jika K=0. Jangan jika K > 1e7 dan kamu membuat `vector(K)` — pakai map.

**Proses:** `a = [4, 5, 0]`, K=3. Sisa: 4≡1, 5≡2, 0≡0.

1. cnt[0]=1, cur=0.
2. +4 → cur=1; hasil += cnt[1]=0; cnt[1]=1.
3. +5 → cur=1+2=0 (mod 3); hasil += cnt[0]=1; cnt[0]=2.
   Subarray `[4,5]` =9.
4. +0 → cur=0; hasil += cnt[0]=2; cnt[0]=3.
   Subarray `[4,5,0]` dan `[0]`.
5. Total 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll hitungHabisDibagi(const vector<ll>& a, ll K) {
    vector<ll> cnt(K, 0);
    cnt[0] = 1;
    ll cur = 0, hasil = 0;
    for (ll v : a) {
        cur = ((cur + v) % K + K) % K;
        hasil += cnt[cur];
        cnt[cur]++;
    }
    return hasil;
}

int main() {
    vector<ll> a = {4, 5, 0};
    cout << hitungHabisDibagi(a, 3) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. Sisa negatif sebagai indeks.
2. `K` tidak muat sebagai ukuran array.
3. `hasil` overflow `int` (bisa n²/2).

**Kompleksitas:** O(n) waktu, O(K) memori (atau O(n) dengan map).

---

## Prefix sum 2D

> **Ide satu kalimat:** empat sudut; yang dikurang dua kali harus dikembalikan.

### Prefix sum 2D

**Teori:** Analoginya luas karpet dari (0,0) ke (r,c), lalu inklusi-eksklusi. `p[i+1][j+1] = p[i][j+1] + p[i+1][j] - p[i][j] + a[i][j]`. Query `a[r1..r2][c1..c2]` (0-based inklusif):

`p[r2+1][c2+1] - p[r1][c2+1] - p[r2+1][c1] + p[r1][c1]`.

Alasan `+`: pojok kiri-atas terkurang dua kali.

**Kapan dipakai / kapan tidak.** Pakai submatriks statis, n,m ≤ 1000–2000. Jangan update sering. Jangan n=5000 jika memori ketat (lihat file 00).

**Proses:** matriks

```
1 2
3 4
```

1. `p` ukuran 3×3, baris/kolom 0 nol.
2. Isi `p[1][1]=1`, `p[1][2]=3`, `p[2][1]=4`, `p[2][2]=10`.
3. Submatriks kanan-bawah `[1..1][1..1]` = 4.
4. Rumus: `10 - 3 - 4 + 1 = 4`.
5. Seluruh: `10`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<ll>> bangunPrefix2D(const vector<vector<ll>>& a) {
    int n = (int)a.size(), m = (int)a[0].size();
    vector<vector<ll>> p(n + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            p[i + 1][j + 1] = p[i][j + 1] + p[i + 1][j] - p[i][j] + a[i][j];
    return p;
}

ll submatriks(const vector<vector<ll>>& p, int r1, int c1, int r2, int c2) {
    return p[r2 + 1][c2 + 1] - p[r1][c2 + 1] - p[r2 + 1][c1] + p[r1][c1];
}

int main() {
    vector<vector<ll>> a = {{1, 2}, {3, 4}};
    auto p = bangunPrefix2D(a);
    cout << submatriks(p, 1, 1, 1, 1) << '\n'; // 4
    cout << submatriks(p, 0, 0, 1, 1) << '\n'; // 10
    return 0;
}
```

**Jebakan:**
1. Lupa `+ p[r1][c1]`.
2. Ukuran `n×m` vs `n+1×m+1`.
3. Overflow `int` pada grid 1000×1000×1e9.

**Kompleksitas:** bangun O(nm), query O(1), memori O(nm).

---

## Difference array 1D

> **Ide satu kalimat:** kalau prefix mempercepat bertanya, difference mempercepat mengubah.

### Difference array 1D

**Teori:** Analoginya sticky note HRD: “mulai hari L tambah gaji v, mulai hari R+1 cabut”. `diff[L]+=v`, `diff[R+1]-=v`. Satu prefix di akhir merekonstruksi array. Alasan benar: difference adalah invers prefix. Offline: semua update dulu, baru bangun. Online update+query campur → bukan alat ini.

**State:** `diff[i] = a[i] - a[i-1]` (dengan `a[-1]=0`).
**Transisi update:** dua coretan O(1).

**Kapan dipakai / kapan tidak.** Pakai banyak range add, satu kali baca akhir. Jangan query di tengah-tengah update tanpa rebuild.

**Proses:** n=5, awal nol. Update `[1,3]+=2`, `[0,4]+=1` (0-based).

1. `diff=[0,0,0,0,0,0]` (n+1 untuk `R+1`).
2. `[1,3]+=2`: `diff[1]+=2`, `diff[4]-=2` → `[0,2,0,0,-2,0]`.
3. `[0,4]+=1`: `diff[0]+=1`, `diff[5]-=1` → `[1,2,0,0,-2,-1]`.
4. Prefix: `1, 3, 3, 3, 1`.
5. Cek: posisi 0 hanya update kedua; 1–3 keduanya; 4 hanya kedua.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void rangeAdd(vector<ll>& diff, int l, int r, ll v) {
    diff[l] += v;
    diff[r + 1] -= v;
}

vector<ll> bangunDariDiff(const vector<ll>& diff, int n) {
    vector<ll> a(n);
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        a[i] = cur;
    }
    return a;
}

int main() {
    int n = 5;
    vector<ll> diff(n + 1, 0);
    rangeAdd(diff, 1, 3, 2);
    rangeAdd(diff, 0, 4, 1);
    auto a = bangunDariDiff(diff, n);
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    // 1 3 3 3 1
    return 0;
}
```

**Jebakan:**
1. `diff[r]-=v` alih-alih `r+1`.
2. `diff` berukuran `n` lalu `r=n-1` overflow.
3. Membangun prefix tiap update (jadi O(n) per update).

**Kompleksitas:** update O(1), bangun O(n), memori O(n).

---

## Difference array 2D

> **Ide satu kalimat:** empat paku di sudut karpet: +v, −v, −v, +v.

### Difference array 2D

**Teori:** Analoginya mengecat persegi di dinding: tambah di pojok kiri-atas, cabut di kanan+1 dan bawah+1, kembalikan pojok luar supaya tidak tercabut dobel. Update `a[r1..r2][c1..c2]+=v`:

```
d[r1][c1] += v
d[r1][c2+1] -= v
d[r2+1][c1] -= v
d[r2+1][c2+1] += v
```

Lalu prefix 2D sekali.

**Kapan dipakai / kapan tidak.** Pakai banyak cat persegi offline. Jangan query campuran online — lazy segtree 2D jarang; biasanya offline atau struktur lain.

**Proses:** 2×2 nol, cat seluruh `+=1`.

1. `d[0][0]+=1`, `d[0][2]-=1`, `d[2][0]-=1`, `d[2][2]+=1`.
2. Prefix 2D: semua sel 1.
3. Cat hanya `[1][1]+=5` (satu sel).
4. Empat paku di (1,1), (1,2), (2,1), (2,2).
5. Hasil akhir `1 1 / 1 6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void rangeAdd2D(vector<vector<ll>>& d, int r1, int c1, int r2, int c2, ll v) {
    d[r1][c1] += v;
    d[r1][c2 + 1] -= v;
    d[r2 + 1][c1] -= v;
    d[r2 + 1][c2 + 1] += v;
}

vector<vector<ll>> bangun2D(const vector<vector<ll>>& d, int n, int m) {
    vector<vector<ll>> a(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll v = d[i][j];
            if (i) v += a[i - 1][j];
            if (j) v += a[i][j - 1];
            if (i && j) v -= a[i - 1][j - 1];
            a[i][j] = v;
        }
    }
    return a;
}

int main() {
    int n = 2, m = 2;
    vector<vector<ll>> d(n + 1, vector<ll>(m + 1, 0));
    rangeAdd2D(d, 0, 0, 1, 1, 1);
    rangeAdd2D(d, 1, 1, 1, 1, 5);
    auto a = bangun2D(d, n, m);
    cout << a[0][0] << ' ' << a[0][1] << '\n'; // 1 1
    cout << a[1][0] << ' ' << a[1][1] << '\n'; // 1 6
    return 0;
}
```

**Jebakan:**
1. Tanda pojok kanan-bawah salah (harus +).
2. Ukuran `d` tidak `+1`.
3. Bangun prefix memakai `d` in-place tanpa salin dengan rumus salah.

**Kompleksitas:** update O(1), bangun O(nm), memori O(nm).

---

## Two pointers berlawanan

> **Ide satu kalimat:** kiri kecil, kanan besar, array sudah urut; tiap langkah buang satu ujung.

### Two pointers berlawanan

**Teori:** Analoginya dua orang di ujung rak buku, mencari dua tebal yang jumlahnya tepat. Jika jumlah terlalu besar, orang kanan mundur (buang yang besar). Terlalu kecil, orang kiri maju. Alasan benar: array naik ⇒ keputusan monoton, setiap indeks paling sekali disentuh. Tanpa urut, langkah “buang kanan” tidak sah.

**Kapan dipakai / kapan tidak.** Pakai two sum terurut, container with most water, pair sum ≤ X. Jangan array acak tanpa sort (kecuali sifat lain, mis. height water). Sort merusak indeks — simpan pair nilai-indeks dulu.

**Proses:** `a = [1,2,4,7]`, target 6.

1. L=0,R=3: 1+7=8 > 6 → R=2.
2. 1+4=5 < 6 → L=1.
3. 2+4=6 = target. Indeks 1 dan 2.
4. Berhenti atau lanjut cari pasangan lain dengan L++/R--.
5. Tidak ada loop n².

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

pair<int, int> twoSumUrut(const vector<ll>& a, ll target) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        ll s = a[l] + a[r];
        if (s == target) return {l, r};
        if (s < target) l++;
        else r--;
    }
    return {-1, -1};
}

int main() {
    vector<ll> a = {1, 2, 4, 7};
    auto [i, j] = twoSumUrut(a, 6);
    cout << i << ' ' << j << '\n'; // 1 2
    return 0;
}
```

**Jebakan:**
1. Array belum urut.
2. `l <= r` lalu pasangan elemen yang sama dua kali.
3. Overflow `a[l]+a[r]` tanpa `ll`.

**Kompleksitas:** O(n) setelah sort O(n log n), memori O(1).

---

## Two pointers searah

> **Ide satu kalimat:** kanan maju menambah barang, kiri maju membuang; keduanya tidak mundur.

### Two pointers searah

**Teori:** Analoginya pita konveyor: kamu hanya boleh geser jendela ke kanan. Jika syarat “jumlah ≤ K” dan elemen **non-negatif**, membuang kiri selalu memperkecil jumlah. Alasan O(n): tiap pointer naik paling n kali. Ada negatif? Jumlah bisa naik saat buang kiri — monoton rusak, kembali ke prefix+map.

**State:** jendela `[L, R]` inklusif, invariant jumlah (atau hitung unik, dll).
**Transisi:** R++ tambah; while invalid L++.

**Kapan dipakai / kapan tidak.** Pakai subarray positif + batas jumlah, unique count, longest dengan syarat monoton. Jangan nilai negatif untuk syarat jumlah.

**Proses:** `a = [1,2,3,1]`, jumlah ≤ 5, hitung jendela valid saat R maju (contoh: terpanjang).

1. R=0: sum=1 ≤5, L=0, panjang 1.
2. R=1: sum=3, panjang 2.
3. R=2: sum=6 >5 → buang L=0 (1), sum=5, L=1, panjang 2.
4. R=3: sum=6 >5 → buang 2, sum=4, L=2, panjang 2.
5. Terpanjang 2. Kandidat: `[1,2]`, `[2,3]`, `[3,1]`. Tidak ada yang panjang 3 karena `[1,2,3]=6` dan `[2,3,1]=6`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int terpanjangJumlahPaling(const vector<ll>& a, ll K) {
    int n = (int)a.size(), L = 0, best = 0;
    ll sum = 0;
    for (int R = 0; R < n; R++) {
        sum += a[R];
        while (L <= R && sum > K) { // elemen dianggap >= 0
            sum -= a[L];
            L++;
        }
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    vector<ll> a = {1, 2, 3, 1};
    cout << terpanjangJumlahPaling(a, 5) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Negatif di array.
2. `while` tidak `L<=R` lalu L lewat R+1.
3. Update `best` sebelum menstabilkan jendela.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Sliding window ukuran tetap

> **Ide satu kalimat:** jendelanya lebar k; masuk satu, keluar satu.

### Sliding window ukuran tetap

**Teori:** Analoginya antrian kasir yang hanya menampung k orang: orang baru masuk, orang terdepan pergi. Jumlah jendela baru = jumlah lama + masuk − keluar. Alasan O(n): bukan O(nk). Kadane **bukan** ini; Kadane panjangnya bebas.

**Kapan dipakai / kapan tidak.** Pakai “tepat k”, rata-rata k hari, max sum panjang k. Jangan k berubah-ubah (itu window variabel). Jangan k>n tanpa penjaga.

**Proses:** `a = [2,1,5,1,3]`, k=3.

1. Jendela `[2,1,5]` sum=8, best=8.
2. Keluar 2, masuk 1 → `[1,5,1]` sum=7, best=8.
3. Keluar 1, masuk 3 → `[5,1,3]` sum=9, best=9.
4. Selesai.
5. Jawaban 9.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll maxJumlahPanjangK(const vector<ll>& a, int k) {
    int n = (int)a.size();
    if (k > n) return LLONG_MIN;
    ll sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    ll best = sum;
    for (int i = k; i < n; i++) {
        sum += a[i] - a[i - k]; // masuk i, keluar i-k
        best = max(best, sum);
    }
    return best;
}

int main() {
    vector<ll> a = {2, 1, 5, 1, 3};
    cout << maxJumlahPanjangK(a, 3) << '\n'; // 9
    return 0;
}
```

**Jebakan:**
1. Keluar `a[i-k-1]` salah indeks.
2. `best` diinisialisasi 0 padahal semua negatif.
3. Pakai Kadane untuk “tepat k”.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Sliding window terpanjang

> **Ide satu kalimat:** pertahankan invariant “jendela sah”; raih panjang maksimum.

### Sliding window terpanjang

**Teori:** Analoginya tas belanja: masukkan barang selama masih muat, jika penuh keluarkan dari yang paling lama. Pola sama dengan two pointers searah. Contoh: paling banyak k jenis, jumlah ≤ X, tidak ada nol, dll. Alasan benar: untuk syarat yang **monoton** (jendela lebih lebar lebih “berat”), jendela terpanjang yang berakhir di R didapat dengan L seminimal mungkin yang masih sah.

**Kapan dipakai / kapan tidak.** Pakai syarat monoton terhadap pelebaran. Jangan “jumlah = K” dengan negatif.

**Proses:** `s = "aababc"`, paling banyak 2 huruf berbeda.

1. R=0 `a` — jenis 1, best=1.
2. `aa` — jenis 1, best=2. Lalu `aab` / `aaba` / `aabab` — jenis 2, best=5.
3. Masuk `c`: `aababc` punya 3 jenis. Geser L: buang `a`, `a`, `b`, `a` sampai sisa `bc` (jenis 2).
4. Panjang setelah geser = 2, tidak memecahkan best.
5. Jawaban 5 yaitu `aabab`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int terpanjangPalingKUnik(const vector<ll>& a, int k) {
    int n = (int)a.size(), L = 0, best = 0, jenis = 0;
    map<ll, int> freq;
    for (int R = 0; R < n; R++) {
        if (++freq[a[R]] == 1) jenis++;
        while (jenis > k) {
            if (--freq[a[L]] == 0) jenis--;
            L++;
        }
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    vector<ll> a = {1, 1, 2, 1, 2, 3}; // seperti aababc
    cout << terpanjangPalingKUnik(a, 2) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Lupa kurangi `jenis` saat freq jadi 0.
2. `map` vs array 26 huruf — konstanta.
3. `best` dihitung saat masih invalid.

**Kompleksitas:** O(n log n) dengan map, O(n) dengan array alfabet; memori O(n).

---

## Sliding window terpendek

> **Ide satu kalimat:** yang terpendek = setelah jendela **baru saja** sah, catat, lalu coba gemukkan kiri.

### Sliding window terpendek

**Teori:** Analoginya minum air sampai haus hilang, lalu tanya “bisakah gelas lebih kecil?”. Kanan maju sampai syarat terpenuhi (jumlah ≥ S, sudah memuat semua huruf, dll). Lalu kiri maju selama masih sah, tiap kali catat panjang. Alasan berbeda dari terpanjang: `best` diupdate **di dalam** setelah shrink, bukan setiap R.

**Kapan dipakai / kapan tidak.** Pakai shortest subarray sum ≥ S (positif), minimum window substring. Jangan sum ≥ S dengan negatif — itu deque (file 04 / Day 37).

**Proses:** `a = [2,3,1,2,4,3]`, S=7.

1. R sampai `[2,3,1,2]` sum=8 ≥7, shrink: buang 2 sum=6 <7 berhenti. Panjang 3 (`3,1,2`).
2. R+ `4`: sum=10, shrink buang 3 sum=7, buang 1 sum=6. Catat `1,2,4`? After adding 4 window was [1,4]=3,1,2,4 sum=10. Shrink L=1 (3): [2,4]=1,2,4 sum=7. Shrink L=2 (1): [3,4]=2,4 sum=6 stop. best min(3,3)=3.
3. R+ `3`: [2,5] 2,4,3=9. Shrink 2 → 4,3=7. Shrink 4 → 3=3. best=2 (`4,3`).
4. Jawaban 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int terpendekJumlahPaling(const vector<ll>& a, ll S) {
    int n = (int)a.size(), L = 0, best = n + 1;
    ll sum = 0;
    for (int R = 0; R < n; R++) {
        sum += a[R];
        while (L <= R && sum >= S) {
            best = min(best, R - L + 1);
            sum -= a[L];
            L++;
        }
    }
    return (best == n + 1) ? 0 : best;
}

int main() {
    vector<ll> a = {2, 3, 1, 2, 4, 3};
    cout << terpendekJumlahPaling(a, 7) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Update `best` di luar `while` (jendela bisa belum sah).
2. Return `n+1` tanpa sentinel.
3. Negatif: window boleh perlu memanjang setelah shrink — salah alat.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Ringkasan file 03

- Prefix: `pre[0]=0`, query `pre[r+1]-pre[l]`.
- Bukan untuk min/max/gcd; bukan untuk update.
- Difference: `+v` di L, `−v` di R+1.
- 2D: inklusi-eksklusi empat sudut.
- Two pointers butuh monoton.
- Negatif membunuh window jumlah; pakai prefix+map.
- Tetap k: masuk satu keluar satu. Bebas: Kadane (file 04).

Lanjut: [04 — Kadane, mono stack/deque, kompresi](04-kadane-mono-stack-deque-compress.md).
