# Prefix Sum dan Difference Array

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** jumlah rentang jadi pengurangan, ubah rentang jadi dua coretan.

Day ComprogLearning: **029** prefix dan difference. Semua 0-based inklusif kecuali disebut. `pre` berukuran `n+1`, `pre[0]=0`. `ll` wajib untuk jumlah.

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
- [Kenapa prefix min gagal](#kenapa-prefix-min-gagal)

---

## Prefix sum 1D

> **Ide satu kalimat:** pasang patokan kilometer sekali, lalu setiap jarak jadi satu pengurangan.

### Prefix sum 1D

**Teori:** Analoginya patok KM di pinggir jalan. `pre[i]` = jumlah `i` elemen pertama, jadi `pre[0]=0` adalah gerbang kota. Alasan benar: jumlah `a[l]+…+a[r]` = (kota ke patok r+1) minus (kota ke patok l). Tidak ada cabang `if (l==0)`. Operasi harus punya invers: tambah punya kurang, XOR punya XOR. Min/max/gcd tidak punya invers — prefix tidak menolong.

**Kapan:** Pakai banyak query jumlah pada array **diam**. Jangan jika ada update di tengah (Fenwick). Jangan prefix min.

**Proses:** `a = [3, 1, 4, 1, 5]`.

```
i        0  1  2  3  4
a[i]     3  1  4  1  5
pre[i]   0  3  4  8  9  14
indeks   0  1  2  3  4   5
```

1. `pre[0]=0`.
2. +3 → `pre[1]=3`.
3. +1 → `pre[4]=9` setelah dua langkah berikutnya.
4. +5 → `pre[5]=14`.
5. Seluruh array = `pre[5]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> bangunPrefix(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    return pre;
}

int main() {
    FASTIO;
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

**Kapan:** Pakai q besar, array statis. Jangan untuk rata-rata tanpa bagi (bagi dulu jumlah). Jangan untuk “jumlah setelah beberapa update”.

**Proses:** `pre = [0,3,4,8,9,14]`, query `l=1, r=3` (nilai 1+4+1).

| Query l..r | rumus | hitung | cek manual |
| --- | --- | ---: | ---: |
| 1..3 | pre[4]-pre[1] | 9-3=6 | 1+4+1 |
| 0..4 | pre[5]-pre[0] | 14 | seluruh |
| 2..2 | pre[3]-pre[2] | 4 | satu elemen |

1. `pre[4] = 9` = 3+1+4+1.
2. `pre[1] = 3`.
3. `9-3=6`.
4. Query penuh `0..4`: `14-0=14`.
5. Satu elemen `a[2]`: `8-4=4`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Kapan:** Pakai query XOR statis, subarray XOR = 0. Jangan untuk OR/AND rentang (tidak ada invers).

**Proses:** `a = [1, 2, 3]` (`01,10,11`).

| i | a[i] | px[i+1] |
| ---: | ---: | ---: |
| (awal) |  | 0 |
| 0 | 1 | 1 |
| 1 | 2 | 3 |
| 2 | 3 | 0 |

1. XOR `a[0..1] = 1^2=3 = px[2]^px[0]`.
2. XOR `a[1..2] = 2^3=1 = px[3]^px[1] = 0^1`.
3. XOR seluruh = 0 = `px[3]`.
4. Subarray XOR 0: seluruh array.
5. AND tidak bisa rumus yang sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Teori:** Analoginya counter orang berkacamata di antrean: tiap orang 1 atau 0, jumlah rentang = berapa yang berkacamata. Alasan benar: syarat boolean punya invers tambah. Syarat “berapa pasangan berurutan” dihitung di posisi i sebagai 1 jika `s[i-1]s[i]` cocok.

**Kapan:** Pakai “berapa elemen genap di [l,r]”, “berapa huruf A”. Jangan jika syarat melibatkan seluruh rentang (bukan sifat per indeks).

**Proses:** `a = [2,5,4,7,8]`, berapa genap di `[1,3]` (5,4,7)?

| i | a[i] | bendera genap | c[i+1] |
| ---: | ---: | ---: | ---: |
| 0 | 2 | 1 | 1 |
| 1 | 5 | 0 | 1 |
| 2 | 4 | 1 | 2 |
| 3 | 7 | 0 | 2 |
| 4 | 8 | 1 | 3 |

1. Bendera: `[1,0,1,0,1]`.
2. `c[4]-c[1] = 2-1 = 1` (hanya 4).
3. Seluruh array: `3` genap.
4. Tanpa prefix, tiap query scan ulang.
5. `% 2` pada negatif bisa −1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> bangunPrefixCountGenap(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> c(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int genap = (a[i] % 2 == 0) ? 1 : 0;
        c[i + 1] = c[i] + genap;
    }
    return c;
}

int main() {
    FASTIO;
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
3. Syarat “apakah rentang palindrom” bukan prefix count.

**Kompleksitas:** O(n) bangun, O(1) query, memori O(n).

---

## Subarray jumlah = K

> **Ide satu kalimat:** kalau jumlah sampai sini = S, cari berapa prefix lama yang bernilai S−K.

### Subarray jumlah = K

**Teori:** Analoginya dompet: saldo sekarang S, kamu ingin pengeluaran tepat K, jadi pernah ada saldo S−K. `freq[0]=1` adalah “prefix kosong” — subarray yang mulai di indeks 0. Alasan benar: `pre[r+1]-pre[l]=K` ⇔ `pre[l]=pre[r+1]-K`. Map menghitung berapa `l`. Sliding window **gagal** jika ada negatif (menambah elemen bisa menurunkan jumlah).

**Kapan:** Pakai K tetap, nilai boleh negatif. Jangan window “maju kanan, mundur kiri” jika tanda campur. Jangan `unordered_map` telanjang di CF.

**Proses:** `a = [1, 2, -1, 3]`, K=3.

| x | cur | cari cur-K | ans | freq setelah |
| ---: | ---: | ---: | ---: | --- |
| 1 | 1 | -2 | 0 | {0:1, 1:1} |
| 2 | 3 | 0 | 1 | +3 |
| -1 | 2 | -1 | 1 | +2 |
| 3 | 5 | 2 | 2 | +5 |

1. `freq[0]=1` wajib.
2. Subarray `[1,2]` jumlah 3.
3. Subarray `[3]` jumlah 3.
4. `[-1,3]=2`, `[2,-1,3]=4`, bukan 3.
5. Jawaban 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll hitungSubarraySamaDengan(const vector<ll>& a, ll K) {
    map<ll, ll> freq;
    freq[0] = 1;
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
    FASTIO;
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

**Kapan:** Pakai CSES Subarray Divisibility. Jangan jika K=0. Jangan jika K > 1e7 dan kamu membuat `vector(K)` — pakai map.

**Proses:** `a = [4, 5, 0]`, K=3. Sisa: 4≡1, 5≡2, 0≡0.

| x | cur mod 3 | hasil += cnt[cur] | cnt setelah |
| ---: | ---: | ---: | --- |
| 4 | 1 | 0 | cnt[1]=1 |
| 5 | 0 | 1 | cnt[0]=2 |
| 0 | 0 | 2 | cnt[0]=3 |

1. `cnt[0]=1` di awal.
2. `[4,5]=9` kelipatan 3.
3. `[4,5,0]` dan `[0]` juga.
4. Total 3.
5. Sisa negatif harus dinormalisasi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Kapan:** Pakai submatriks statis, n,m ≤ 1000–2000. Jangan update sering. Jangan n=5000 jika memori ketat.

**Proses:** matriks `[[1,2],[3,4]]`.

| p | 0 | 1 | 2 |
| ---: | ---: | ---: | ---: |
| 0 | 0 | 0 | 0 |
| 1 | 0 | 1 | 3 |
| 2 | 0 | 4 | 10 |

1. `p` ukuran 3×3, baris/kolom 0 nol.
2. Submatriks kanan-bawah `[1..1][1..1]` = 4.
3. Rumus: `10 - 3 - 4 + 1 = 4`.
4. Seluruh: `10`.
5. Lupa `+1` mengembalikan pojok = 2, WA.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    vector<vector<ll>> a = {{1, 2}, {3, 4}};
    auto p = bangunPrefix2D(a);
    cout << submatriks(p, 1, 1, 1, 1) << '\n'; // 4
    cout << submatriks(p, 0, 0, 1, 1) << '\n'; // 10
    return 0;
}
```

**Jebakan:**
1. Lupa `+ p[r1][c1]`.
2. Ukuran `n×m` versus `n+1×m+1`.
3. Overflow `int` pada grid 1000×1000×1e9.

**Kompleksitas:** bangun O(nm), query O(1), memori O(nm).

---

## Difference array 1D

> **Ide satu kalimat:** kalau prefix mempercepat bertanya, difference mempercepat mengubah.

### Difference array 1D

**Teori:** Analoginya sticky note HRD: “mulai hari L tambah gaji v, mulai hari R+1 cabut”. `diff[L]+=v`, `diff[R+1]-=v`. Satu prefix di akhir merekonstruksi array. Alasan benar: difference adalah invers prefix. Offline: semua update dulu, baru bangun. Online update+query campur → bukan alat ini.

**Kapan:** Pakai banyak range add, satu kali baca akhir. Jangan query di tengah-tengah update tanpa rebuild.

**Proses:** n=5, awal nol. Update `[1,3]+=2`, `[0,4]+=1` (0-based).

| Setelah | diff |
| --- | --- |
| awal | 0 0 0 0 0 0 |
| [1,3]+=2 | 0 2 0 0 -2 0 |
| [0,4]+=1 | 1 2 0 0 -2 -1 |
| prefix | 1 3 3 3 1 |

1. `diff` berukuran n+1 untuk `R+1`.
2. Posisi 0 hanya update kedua.
3. Posisi 1–3 keduanya.
4. Posisi 4 hanya update kedua.
5. Membangun prefix tiap update merusak O(1).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Kapan:** Pakai banyak cat persegi offline. Jangan query campuran online.

**Proses:** 2×2 nol, cat seluruh `+=1`, lalu sel `[1][1]+=5`.

1. Empat paku seluruh matriks.
2. Empat paku satu sel.
3. Prefix 2D: `1 1 / 1 6`.
4. Tanda pojok luar harus plus.
5. Ukuran `d` wajib `(n+1)×(m+1)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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
3. Bangun prefix memakai rumus tanpa mengembalikan pojok.

**Kompleksitas:** update O(1), bangun O(nm), memori O(nm).

---

## Kenapa prefix min gagal

> **Ide satu kalimat:** minimum tidak punya tombol “undo”; selisih dua prefix min bukan min rentang.

### Kenapa prefix min gagal

**Teori:** Analoginya suhu terendah sepanjang tahun: mengetahui rekor sampai Juni dan rekor sampai Desember tidak memberi rekor Juli–Desember. `min(preMin[r], ?)` tidak bisa membuang kiri. Alasan benar: operasi prefix butuh invers. Tambah punya kurang. Min tidak punya. Untuk range min, pakai sparse table atau SegTree.

**Kapan:** Ingat ini saat tergoda menulis `preMin`. Jangan memakai rumus `preMin[r+1] - preMin[l]`. Pakai alat range-min yang benar.

**Proses:** `a = [3, 1, 4]`.

| i | a[i] | prefix min sampai i |
| ---: | ---: | ---: |
| 0 | 3 | 3 |
| 1 | 1 | 1 |
| 2 | 4 | 1 |

1. Min `[0,2]` = 1, prefix min akhir juga 1. Kebetulan.
2. Min `[2,2]` = 4, prefix min sampai 2 = 1. Bukan 4.
3. Selisih 1-3 tidak berarti.
4. XOR berhasil karena invers diri sendiri.
5. Jadi prefix min hanya menjawab “min prefix 0..i”, bukan sembarang `[l,r]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll minNaif(const vector<ll>& a, int l, int r) {
    ll best = a[l];
    for (int i = l; i <= r; i++) best = min(best, a[i]);
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {3, 1, 4};
    vector<ll> preMin(3);
    preMin[0] = a[0];
    for (int i = 1; i < 3; i++) preMin[i] = min(preMin[i - 1], a[i]);
    cout << minNaif(a, 2, 2) << '\n'; // 4, benar
    cout << preMin[2] << '\n';        // 1, bukan min [2,2]
    return 0;
}
```

**Jebakan:**
1. Menyalin rumus range sum ke min.
2. Mengira gcd prefix juga bisa di-selisih — gcd juga tanpa invers sederhana untuk buang kiri.
3. Memaksa prefix min lalu WA pada query yang tidak mulai di 0.

**Kompleksitas:** naif O(n) per query; prefix min O(n) bangun tetapi **salah** untuk range bebas.

---

## Ringkasan

- Prefix: `pre[0]=0`, query `pre[r+1]-pre[l]`.
- Bukan untuk min/max/gcd; bukan untuk update.
- Difference: `+v` di L, `−v` di R+1.
- 2D: inklusi-eksklusi empat sudut.
- Subarray = K: map prefix, `freq[0]=1`.
- Negatif membunuh window jumlah.

Lanjut: [two pointers dan window](two-pointers-window.md).
