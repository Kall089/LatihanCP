# 06 — Subset sum dan partisi

[← 0-1 knapsack](05-01-knapsack.md) · [← 09-dp](README.md) · [Bounded knapsack →](07-bounded-knapsack.md)

Day ComprogLearning: **146**. Ini knapsack 0-1 yang nilainya sama dengan berat, jawabannya boolean, cacah, atau selisih partisi.

> **Ide satu kalimat:** `bisa[0] = true`, loop **mundur**, dan `bisa[s] |= bisa[s-x]`; partisi adalah subset sum ke `T/2`.

## Daftar isi

- [Subset sum boolean](#subset-sum-boolean)
- [Kenapa loop mundur](#kenapa-loop-mundur)
- [Menghitung banyak subset](#menghitung-banyak-subset)
- [Rekonstruksi subset](#rekonstruksi-subset)
- [Partisi sama rata](#partisi-sama-rata)
- [Selisih partisi minimum](#selisih-partisi-minimum)
- [Bitset](#bitset)
- [Meet in the middle](#meet-in-the-middle)

---

## Subset sum boolean

**Teori:** Diberi `n` bilangan dan target `S`. Setiap bilangan paling banyak sekali. Apakah ada subset jumlah tepat `S`? Ini 0-1 knapsack dengan nilai = berat, yang disimpan hanya bisa atau tidak. `bisa[0] = true` wajib: subset kosong. Tanpa basis itu, elemen pertama tidak pernah menyalakan sel mana pun. Bitset mempercepat 64 kali, dibahas di bagian akhir. `S` raksasa dan `n` kecil menuju meet in the middle, bukan `vector` berukuran `1e12`.

**Kapan:** "apakah bisa membentuk", "semua jumlah yang mungkin". **Tidak:** elemen boleh diulang (itu coin). Jumlah wajib kontigu (itu prefix / Kadane).

**STATE:** `bisa[s]` bernilai benar jika ada subset dari elemen yang sudah diproses yang jumlahnya tepat `s`.

**TRANSISI:** untuk setiap `x`, mundur `s = S..x`: `bisa[s] |= bisa[s-x]`.

**BASIS:** `bisa[0] = 1`. Lainnya 0.

**Proses:** `a = [3, 5, 7]`, `S = 10`.

```
setelah     jumlah yang nyala
awal        {0}
+3          {0, 3}
+5          {0, 3, 5, 8}
+7          {0, 3, 5, 7, 8, 10, 12, 15}  12 dan 15 terpotong jika S=10
```

```
s     0 1 2 3 4 5 6 7 8 9 10
awal  1 0 0 0 0 0 0 0 0 0  0
+3    1 0 0 1 0 0 0 0 0 0  0
+5    1 0 0 1 0 1 0 0 1 0  0
+7    1 0 0 1 0 1 0 1 1 0  1
```

`bisa[10] = true` dari `3+7`. `5+5` tidak muncul karena 5 hanya satu.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<char> subsetSum(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            if (bisa[c - x]) bisa[c] = 1;
    return bisa;
}

bool subsetSumExists(const vector<int>& a, int S) {
    return subsetSum(a, S)[S];
}

int main() {
    FASTIO;
    vector<int> a = {3, 5, 7, 10};
    auto bisa = subsetSum(a, 12);
    cout << (bisa[12] ? "YES\n" : "NO\n"); // YES 5+7
    cout << (subsetSumExists(a, 11) ? "YES\n" : "NO\n"); // NO
    return 0;
}
```

**Jebakan:** lupa `bisa[0]`. Loop maju. Target negatif. `S = 0` harus YES.

**Kompleksitas:** `O(n S)` waktu, `O(S)` memori.

---

## Kenapa loop mundur

**Teori:** Loop maju memakai `x` berkali-kali, persis seperti unbounded. Satu elemen `[3]`, target 6, maju menyalakan 3 lalu 6. Mundur membaca `bisa[3]` yang masih mati saat `s = 6`. Ini hukum yang sama dengan knapsack 0-1. Kalau soal memang mengizinkan ulang, pindah ke file 04, jangan "memperbaiki" subset sum dengan maju.

**Kapan:** setiap elemen unik atau stok 1. **Tidak:** menukar arah untuk "mempercepat".

**STATE:** setelah elemen `x` diproses dengan mundur, `bisa[s]` benar hanya jika `x` dipakai paling banyak sekali.

**TRANSISI:** baca `bisa[s-x]` versi lama, tulis `bisa[s]` versi baru, dari kanan ke kiri.

**BASIS:** `bisa[0]` tetap nyala sepanjang proses.

**Proses:** `a = [3]`, `S = 6`.

```
MUNDUR
s=6 baca bisa[3]=0  tetap 0
s=3 baca bisa[0]=1  nyala
hasil [1,0,0,1,0,0,0]  6 mati  benar

MAJU
s=3 baca bisa[0]=1  nyala
s=6 baca bisa[3]=1  nyala
hasil [1,0,0,1,0,0,1]  6 hidup  salah
```

ASCII sel:

```
indeks   0 1 2 3 4 5 6
awal     1 . . . . . .
mundur   1 . . 1 . . .
maju     1 . . 1 . . 1
```

Dua elemen `[3, 3]`, `S = 6`, mundur sah: 3 pertama menyalakan 3, 3 kedua menyalakan 6. Dua angka 3 yang berbeda, bukan satu angka diulang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<char> majuSalah(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int c = x; c <= S; c++)
            if (bisa[c - x]) bisa[c] = 1;
    return bisa;
}

vector<char> mundurBenar(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            if (bisa[c - x]) bisa[c] = 1;
    return bisa;
}

int main() {
    FASTIO;
    cout << (int)majuSalah({3}, 6)[6] << " " << (int)mundurBenar({3}, 6)[6] << "\n";
    // 1 0
    cout << (int)mundurBenar({3, 3}, 6)[6] << "\n"; // 1
    return 0;
}
```

**Jebakan:** "saya pakai `if (!bisa[c])`" sebagai pengganti mundur. Itu tidak ekuivalen dan tetap bisa dobel pada rantai panjang.

**Kompleksitas:** kedua loop `O(n S)`. Yang salah lebih cepat memberi WA, bukan TLE.

---

## Menghitung banyak subset

**Teori:** Ganti `char` menjadi `ll`, operator `|=` menjadi `+` modulo. `cara[0] = 1`. Loop tetap mundur. Ini menghitung subset, bukan permutasi elemen. Dua subset berbeda yang kebetulan sama angkanya dihitung dua jika asalnya indeks berbeda. Urutan elemen di array tidak mengubah jumlah subset, hanya urutan pengisian.

**Kapan:** "berapa banyak subset jumlah `S`". **Tidak:** urutan pengambilan dianggap beda (itu permutasi koin).

**STATE:** `cara[s]` adalah banyaknya subset dari elemen yang sudah diproses yang jumlahnya tepat `s`, modulo `MOD`.

**TRANSISI:** `cara[s] = (cara[s] + cara[s-x]) % MOD` mundur.

**BASIS:** `cara[0] = 1`.

**Proses:** `a = [1, 1, 2]`, `S = 2`. Indeks 0 dan 1 sama nilainya, tetapi tetap dua elemen berbeda.

```
awal      cara = [1, 0, 0]
+ a0=1    [1, 1, 0]          subset {0}
+ a1=1    mundur s=2 lalu s=1
          s=2: cara[2] += cara[1] -> 1     {0,1}
          s=1: cara[1] += cara[0] -> 2     {0} atau {1}
          [1, 2, 1]
+ a2=2    s=2: cara[2] += cara[0] -> 2     tambah {2}
          [1, 2, 2]
```

Dua subset jumlah 2: `{0,1}` yaitu `1+1`, dan `{2}`. Jawaban 2.

`a = [3, 5, 7, 10]`, `S = 10`: `{10}`, `{3,7}` → 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

vector<ll> subsetSumCara(const vector<int>& a, int S) {
    vector<ll> cara(S + 1, 0);
    cara[0] = 1;
    for (int x : a)
        for (int c = S; c >= x; c--)
            cara[c] = (cara[c] + cara[c - x]) % MOD;
    return cara;
}

int main() {
    FASTIO;
    cout << subsetSumCara({1, 1, 2}, 2)[2] << "\n"; // 2
    cout << subsetSumCara({3, 5, 7, 10}, 10)[10] << "\n"; // 2
    return 0;
}
```

**Jebakan:** lupa modulo. Loop maju menghitung komposisi unbounded. `cara[0]` direset.

**Kompleksitas:** `O(n S)` waktu, `O(S)` memori.

---

## Rekonstruksi subset

**Teori:** Boolean saja tidak menyebut siapa yang diambil. Simpan `pilih[s] = x` atau indeks elemen yang pertama kali menyalakan `s`. Telusur `s -= pilih[s]`. Lebih aman menyimpan indeks, karena angka bisa kembar. Alternatif 2D: `bisa[i][s]` lalu mundur seperti knapsack. Untuk `S` besar, 2D mahal; jejak 1D cukup jika kita merekam elemen saat transisi pertama.

**Kapan:** output himpunan, bukan YES/NO. **Tidak:** mengira elemen unik otomatis terbaca dari `S` dengan greedy.

**STATE:** `dari[s]` adalah indeks elemen yang dipakai untuk menyalakan `s` pertama kali, atau `-1`.

**TRANSISI:** jika `!bisa[s]` dan `bisa[s-x]`, nyalakan dan catat indeks.

**BASIS:** `dari[0] = -1`.

**Proses:** `a = [3, 5, 7]`, `S = 10`.

```
+3 idx0  nyala 3, dari[3]=0
+5 idx1  nyala 5 dari[5]=1, nyala 8 dari[8]=1
+7 idx2  nyala 7 dari[7]=2, nyala 10 dari[10]=2  (karena 3 sudah nyala)
```

Jejak 10: `dari[10]=2` ambil 7, sisa 3; `dari[3]=0` ambil 3. Subset `{3,7}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> subsetReconstruct(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    vector<int> dari(S + 1, -1);
    bisa[0] = 1;
    for (int i = 0; i < (int)a.size(); i++)
        for (int s = S; s >= a[i]; s--)
            if (!bisa[s] && bisa[s - a[i]]) {
                bisa[s] = 1;
                dari[s] = i;
            }
    if (!bisa[S]) return {};
    vector<int> idx;
    for (int s = S; s > 0; s -= a[dari[s]]) idx.push_back(dari[s]);
    reverse(idx.begin(), idx.end());
    return idx;
}

int main() {
    FASTIO;
    for (int i : subsetReconstruct({3, 5, 7}, 10)) cout << i << " ";
    cout << "\n"; // 0 2
    return 0;
}
```

**Jebakan:** `s -= a[dari[s]]` saat `dari[s] = -1`. Menulis nilai `a[i]` ke output padahal soal minta indeks, atau sebaliknya.

**Kompleksitas:** `O(n S)` plus `O(n)` telusur.

---

## Partisi sama rata

**Teori:** Bisakah array dibagi dua subset dengan jumlah sama? Jumlah total `T`. Jika `T` ganjil, mustahil. Jika genap, tanyakan subset sum `T/2`. Subset itu dan pelengkapnya otomatis sama jumlah. Partisi tidak peduli kontigu. `[1, 5, 11, 5]` total 22, target 11, `YES`. `[1, 2, 3, 5]` total 11 ganjil, `NO`.

**Kapan:** "bagi dua sama rata", "equal partition". **Tidak:** lebih dari dua kelompok tanpa dimensi tambahan. Kontigu adalah prefix.

**STATE:** `bisa[s]` sama seperti subset sum sampai `T/2`.

**TRANSISI:** loop mundur, elemen sekali.

**BASIS:** `bisa[0] = 1`. `T % 2 == 1` langsung false.

**Proses:** `a = [1, 5, 11, 5]`, `T = 22`, target 11.

```
+1    {0,1}
+5    {0,1,5,6}
+11   {0,1,5,6,11,12,16,17}
+5    11 sudah nyala
```

`bisa[11] = true`. Satu partisi `{11}` lawan `{1,5,5}`. Lain `{1,5,5}` lawan `{11}`. Sama.

`[1, 2, 3, 9]`, `T = 15` ganjil: partisi sama mustahil, tetapi selisih minimum masih terdefinisi (bagian berikutnya).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool canPartition(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total % 2) return false;
    int S = total / 2;
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int s = S; s >= x; s--)
            if (bisa[s - x]) bisa[s] = 1;
    return bisa[S];
}

int main() {
    FASTIO;
    cout << canPartition({1, 5, 11, 5}) << "\n"; // 1
    cout << canPartition({1, 2, 3, 5}) << "\n";  // 0
    return 0;
}
```

**Jebakan:** overflow `int` pada `total`. Mengira partisi harus dua blok kontigu. Lupa cek ganjil.

**Kompleksitas:** `O(n T)` waktu, `O(T/2)` memori.

---

## Selisih partisi minimum

**Teori:** Bagi menjadi dua kelompok (boleh kosong secara teori, biasanya keduanya ada) supaya `|sumA - sumB|` minimum. `sumB = T - sumA`, selisih `|T - 2 sumA|`. Cari `s ≤ T/2` terbesar yang `bisa[s]`, lalu `T - 2s`. `T` ganjil tetap sah. `[1, 2, 3, 9]`: `s` terbaik 6 (`1+2+3`), selisih `15-12=3`.

**Kapan:** "minimum partition difference". **Tidak:** lebih dari dua tumpukan.

**STATE:** `bisa[s]` benar jika ada subset jumlah `s` dari seluruh array.

**TRANSISI:** subset sum mundur sampai `T`.

**BASIS:** `bisa[0] = 1`.

**Proses:** `a = [1, 2, 3, 9]`, `T = 15`.

```
+1   0,1
+2   0,1,2,3
+3   0,1,2,3,4,5,6
+9   0..6 dan 9..15
```

`s ≤ 7` yang nyala: 6 (dan 0..5). Terbaik 6. Selisih `15 - 12 = 3`. Kelompok `{1,2,3}` dan `{9}`.

`[1, 5, 11, 5]`: `s = 11`, selisih 0.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int minPartitionDiff(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;
    for (int x : a)
        for (int s = total; s >= x; s--)
            bisa[s] = bisa[s] | bisa[s - x];
    for (int s = total / 2; s >= 0; s--)
        if (bisa[s]) return total - 2 * s;
    return total;
}

int main() {
    FASTIO;
    cout << minPartitionDiff({1, 2, 3, 9}) << "\n"; // 3
    cout << minPartitionDiff({1, 5, 11, 5}) << "\n"; // 0
    return 0;
}
```

**Jebakan:** mengembalikan `s` bukan `T-2s`. `T` ganjil dianggap error. Overflow `total`.

**Kompleksitas:** `O(n T)` waktu, `O(T)` memori.

---

## Bitset

**Teori:** `bisa[s] |= bisa[s-x]` adalah geser OR. `bitset` melakukan 64 bit per operasi: `bs |= bs << x`. Ukuran compile-time. Cek `target < MAXS`. Urutan elemen bebas. Ini tetap 0-1 karena setiap `x` digeser sekali. Percepatan nyata saat `T` sampai `1e5` atau `1e6` dan `n` ratusan. Day 164 membahas bitset lebih dalam; di sini cukup untuk subset sum.

**Kapan:** `T` besar, hanya YES/NO atau semua mask jumlah. **Tidak:** butuh banyak cara; bitset tidak menghitung.

**STATE:** bit ke-`s` nyala jika jumlah `s` reachable.

**TRANSISI:** `bs |= bs << x` untuk setiap elemen.

**BASIS:** `bs[0] = 1`.

**Proses:** `a = [3, 5, 7]`.

```
awal          bit0
<<3           bit0, bit3
<<5           bit0,3,5,8
<<7           bit0,3,5,7,8,10,12,15
```

Sama dengan tabel boolean.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

template <size_t MAXS>
bitset<MAXS> subsetSumBitset(const vector<int>& a) {
    bitset<MAXS> bs;
    bs[0] = 1;
    for (int x : a) bs |= bs << x;
    return bs;
}

int main() {
    FASTIO;
    vector<int> a = {3, 5, 7, 10};
    auto bs = subsetSumBitset<64>(a);
    cout << bs[12] << " " << bs[11] << "\n"; // 1 0
    return 0;
}
```

**Jebakan:** `target >= MAXS`. `x` negatif. Menggeser `ll` ke bitset tanpa cek.

**Kompleksitas:** `O(n T / 64)` waktu, `O(T / 64)` memori.

---

## Meet in the middle

**Teori:** Subset sum umum NP-complete jika `S` tak terbatas. Di CP, `n ≤ 40` dan `S` atau `W` sampai `1e18` diselesaikan dengan membelah array. Enumerasi `2^{n/2}` jumlah kiri dan kanan, sort, lalu untuk setiap jumlah kiri cari apakah `S - kiri` ada di kanan. Ini mention, bukan pengganti Day 54. Jangan menulis `vector<char> bisa(1e18)`. MITM juga menolong knapsack nilai pada `n = 40`.

**Kapan:** `n ≤ 40`, target besar. **Tidak:** `n = 100`, `S = 1e5` — DP biasa lebih sederhana.

**STATE:** setiap subset setengah array menghasilkan satu jumlah.

**TRANSISI:** pairing `left + right == S`, bukan rekurens `dp[s]`.

**BASIS:** subset kosong masing-masing setengah menghasilkan 0.

**Proses:** `a = [3, 5, 7, 10]`, `S = 12`, belah `[3,5]` dan `[7,10]`.

```
kiri   {}=0, {3}=3, {5}=5, {3,5}=8
kanan  {}=0, {7}=7, {10}=10, {7,10}=17
12-0=12 tidak ada
12-3=9  tidak
12-5=7  ada
12-8=4  tidak
YES lewat 5+7
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> semuaJumlah(const vector<int>& a) {
    int n = (int)a.size();
    vector<ll> res(1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) s += a[i];
        res[mask] = s;
    }
    sort(res.begin(), res.end());
    return res;
}

bool subsetMITM(vector<int> a, ll S) {
    int n = (int)a.size();
    vector<int> L(a.begin(), a.begin() + n / 2);
    vector<int> R(a.begin() + n / 2, a.end());
    auto kiri = semuaJumlah(L);
    auto kanan = semuaJumlah(R);
    for (ll x : kiri) {
        ll butuh = S - x;
        if (binary_search(kanan.begin(), kanan.end(), butuh)) return true;
    }
    return false;
}

int main() {
    FASTIO;
    cout << subsetMITM({3, 5, 7, 10}, 12) << "\n"; // 1
    cout << subsetMITM({3, 5, 7, 10}, 11) << "\n"; // 0
    return 0;
}
```

**Jebakan:** `n = 40` memakai `1 << n` pada setengah yang salah (harus `n/2`). Overflow jumlah `int`. Lupa subset kosong.

**Kompleksitas:** `O(2^{n/2} n)` enumerasi plus `O(2^{n/2} log)` pencarian.

---

Uji cepat: `[3,5,7]` target 10 YES; satu `[3]` target 6 NO jika mundur, YES jika maju (salah); `[1,1,2]` cara target 2 = 2; `[1,5,11,5]` partisi YES; `[1,2,3,9]` selisih 3; MITM 12 YES. Lanjut ke [07 — bounded knapsack](07-bounded-knapsack.md) untuk pecah biner stok.
