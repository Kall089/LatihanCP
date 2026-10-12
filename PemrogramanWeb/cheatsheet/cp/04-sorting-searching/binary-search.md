# Binary search

[← README](README.md) · [Indeks CP](../README.md)

Tiap langkah membuang setengah ruang yang sudah pasti tidak memuat jawaban. Syaratnya satu: predikat yang kamu tanyakan **monoton**. Tanpa monoton, potongan itu bisa membuang jawaban yang benar.

Day terkait: **048**. Array selalu 0-based. Bound manual memakai ruang `[lo, hi]` dengan `hi` awal sama dengan `n`.

## Daftar isi

- [Binary search nilai pasti](#binary-search-nilai-pasti)
- [Lower bound manual](#lower-bound-manual)
- [Upper bound manual](#upper-bound-manual)
- [Kemunculan pertama dan terakhir](#kemunculan-pertama-dan-terakhir)
- [Binary search on answer](#binary-search-on-answer)
- [Binary search bilangan real](#binary-search-bilangan-real)
- [Pola predikat monoton](#pola-predikat-monoton)
- [Peta keputusan](#peta-keputusan)

---

## Binary search nilai pasti

**Teori:** Analoginya kamus kertas: buka tengah, kalau kata target lebih kecil buang kanan. Array harus **naik**. Alasan `O(log n)`: ruang `n, n/2, n/4, …` sampai satu sel. `mid = lo + (hi - lo) / 2` menghindari overflow `lo + hi`. Loop `lo <= hi`, lalu maju `lo = mid + 1` atau `hi = mid - 1` supaya jendela benar-benar menyusut.

**Kapan:** cari ada atau tidak pada array yang sudah urut. Jangan pada array acak. Jangan mencampur `while (lo < hi)` dengan `hi = mid - 1` tanpa cek: mudah infinite atau melewatkan elemen.

**Proses:** `a = [1, 3, 4, 7, 9]`, target `7`.

1. `lo = 0`, `hi = 4`, `mid = 2`, `a[2] = 4 < 7` → `lo = 3`.
2. `lo = 3`, `hi = 4`, `mid = 3`, `a[3] = 7` ketemu indeks `3`.
3. Target `2`: `mid = 2` (`4 > 2`) → `hi = 1`; `mid = 0` (`1 < 2`) → `lo = 1`; `mid = 1` (`3 > 2`) → `hi = 0`; `lo > hi` gagal.
4. Tidak pernah akses di luar `[0, n)`.
5. Lima elemen, paling sekitar tiga langkah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int binsearch(const vector<ll>& a, ll target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 3, 4, 7, 9};
    cout << binsearch(a, 7) << '\n'; // 3
    cout << binsearch(a, 2) << '\n'; // -1
    cout << binsearch(a, 1) << '\n'; // 0
    cout << binsearch({}, 1) << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. `(lo + hi) / 2` overflow pada `int` besar.
2. `lo = mid` tanpa `+ 1` saat `a[mid] < target` → loop.
3. Array belum diurut.
4. Mengembalikan `mid` setelah loop, padahal loop sudah gagal.

**Kompleksitas:** waktu `O(log n)`, memori `O(1)`.

---

## Lower bound manual

**Teori:** Analoginya “kursi paling kiri yang orangnya sudah lebih tinggi atau sama dengan target”. Invariant: jawaban ada di `[lo, hi]`, dan `hi` awal boleh `n` (artinya “setelah akhir”). Jika `a[mid] >= x`, jawaban di kiri termasuk `mid` (`hi = mid`). Jika `a[mid] < x`, `mid` bukan kandidat (`lo = mid + 1`). Berhenti saat `lo == hi`. Alasan benar: tiap langkah membuang sisi yang mustahil, dan predikat `>=` menjaga kemunculan sama yang paling kiri.

**Kapan:** first `>= x`, posisi sisip, awal blok nilai. Jangan `hi = n - 1` jika jawaban sah adalah `n`.

**Proses:** `a = [1, 3, 3, 6, 8]`, `x = 3`.

1. `lo = 0`, `hi = 5`.
2. `mid = 2`, `a[2] = 3 >= 3` → `hi = 2`.
3. `mid = 1`, `a[1] = 3 >= 3` → `hi = 1`.
4. `mid = 0`, `a[0] = 1 < 3` → `lo = 1`.
5. `lo = hi = 1`. Itu kemunculan pertama `3`.

`x = 4` berakhir di indeks `3` (nilai `6`). `x = 9` berakhir di `5`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lowerBoundManual(const vector<ll>& a, ll x) {
    int lo = 0, hi = (int)a.size(); // [0, n]
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << lowerBoundManual(a, 3) << '\n'; // 1
    cout << lowerBoundManual(a, 4) << '\n'; // 3
    cout << lowerBoundManual(a, 9) << '\n'; // 5
    cout << (int)(lower_bound(a.begin(), a.end(), 3) - a.begin()) << '\n';
    return 0;
}
```

Baris terakhir harus sama dengan `1`. Kalau berbeda, predikatmu terbalik.

**Jebakan:**
1. `hi = n - 1` kehilangan jawaban `n`.
2. `if (a[mid] > x)` — itu upper bound.
3. `while (lo <= hi)` plus `hi = mid` infinite saat `lo = hi = mid`.
4. Mengakses `a[lo]` tanpa cek `lo < n`.

**Kompleksitas:** `O(log n)` waktu, `O(1)` memori.

---

## Upper bound manual

**Teori:** Kursi pertama yang orangnya **lebih** dari target. Predikatnya `a[mid] > x`. Selisih `upper - lower` adalah frekuensi `x`. Alasan benar: setelah sort, semua salinan `x` menempel; ujung kanan jendela adalah first `> x`.

**Kapan:** last occurrence (`upper - 1` jika ada), hitung `<= x`, sisip setelah blok `x`. Jangan `*--it` tanpa cek `it == begin` di versi iterator.

**Proses:** `a = [1, 3, 3, 6, 8]`, `x = 3`.

1. `lo = 0`, `hi = 5`, `mid = 2`, `3 > 3`? tidak → `lo = 3`.
2. `mid = 4`, `8 > 3` → `hi = 4`.
3. `mid = 3`, `6 > 3` → `hi = 3`.
4. `lo = hi = 3`. First lebih dari `3`.
5. Frekuensi `3` = `3 - 1 = 2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int upperBoundManual(const vector<ll>& a, ll x) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

ll frekuensi(const vector<ll>& a, ll x) {
    return (ll)upperBoundManual(a, x) - lower_bound(a.begin(), a.end(), x)
        + a.begin();
}

int main() {
    FASTIO;
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << upperBoundManual(a, 3) << '\n'; // 3
    cout << upperBoundManual(a, 8) << '\n'; // 5
    cout << upperBoundManual(a, 0) << '\n'; // 0
    int lo = (int)(lower_bound(a.begin(), a.end(), 3) - a.begin());
    cout << upperBoundManual(a, 3) - lo << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Tertukar `>=` dan `>`.
2. Last = `upper - 1` saat `upper == 0`.
3. Membandingkan `double` dengan `==` di dalam bound.

**Kompleksitas:** `O(log n)` waktu, `O(1)` memori.

---

## Kemunculan pertama dan terakhir

**Teori:** Analoginya mencari halaman pertama dan terakhir bab yang sama. First = lower bound, last = upper bound minus satu. Jika `first == upper`, target tidak ada. Alasan benar: setelah sort, blok nilai `x` kontigu. Ini pola LC 34.

**Kapan:** “posisi pertama dan terakhir”, hitung rentang sama. Jangan scan linear setelah `binary_search` yang hanya mengembalikan `bool`.

**Proses:** `a = [5, 7, 7, 8, 8, 10]`, target `8`.

1. Lower = `3`, upper = `5`.
2. First `3`, last `4`.
3. Target `6`: lower = `1` (nilai `7`), upper = `1`, tidak ada.
4. Target `10`: first = last = `5`.
5. Target `4`: lower = `0`, `a[0] != 4`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<int, int> firstLast(const vector<ll>& a, ll x) {
    int lo = (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
    int hi = (int)(upper_bound(a.begin(), a.end(), x) - a.begin());
    if (lo == hi) return {-1, -1};
    return {lo, hi - 1};
}

int main() {
    FASTIO;
    vector<ll> a = {5, 7, 7, 8, 8, 10};
    auto [f, l] = firstLast(a, 8);
    cout << f << ' ' << l << '\n'; // 3 4
    auto [f2, l2] = firstLast(a, 6);
    cout << f2 << ' ' << l2 << '\n'; // -1 -1
    auto [f3, l3] = firstLast(a, 5);
    cout << f3 << ' ' << l3 << '\n'; // 0 0
    return 0;
}
```

**Jebakan:**
1. Return `{lo, hi}` tanpa minus satu.
2. Array tidak urut.
3. Mengurangkan iterator lalu menaruhnya di `int` tanpa cek kosong.

**Kompleksitas:** `O(log n)` waktu, `O(1)` memori.

---

## Binary search on answer

**Teori:** Yang dicari bukan indeks, melainkan **angka jawaban**, asal predikat “apakah `X` cukup?” monoton. Analoginya thermostat: jika suhu `X` sudah membuat kue matang, suhu lebih tinggi juga matang. Kita binary search `X`, bukan array. Ruang jawaban `[lo, hi]` integer; tiap tanya membuang setengah. Contoh klasik: minimum kapasitas tas, minimum waktu, CSES Array Division.

State mental: `ok(x)` = “`x` layak”. Transisi: jika `ok(mid)` coba lebih kecil (`hi = mid`), else `lo = mid + 1`.

**Kapan:** kamu bisa cek kandidat dalam `O(n)` dan predikat berubah sekali dari salah ke benar. Jangan jika `ok` naik-turun; itu unimodal, buka [ternary.md](ternary.md). Jangan `hi` terlalu kecil sampai jawaban terpotong.

**Proses:** bagi `[7, 2, 5, 10, 8]` jadi `2` kelompok, minimize jumlah maksimum.

1. `lo = 10` (max elemen), `hi = 32` (total).
2. `mid = 21`: `7+2+5 = 14`, `10+8 = 18`, keduanya `<= 21`, dua kelompok. Layak → `hi = 21`.
3. `mid = 15`: `7+2 = 9`, lalu `5`, `10`, `8` butuh empat kelompok. Tidak → `lo = 16`.
4. Lanjut sampai `lo = hi = 18` (`10+8`).
5. `ok(18)` benar, `ok(17)` salah karena `10+8 = 18`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool muat(const vector<ll>& a, int k, ll batas) {
    int kelompok = 1;
    ll cur = 0;
    for (ll x : a) {
        if (x > batas) return false;
        if (cur + x > batas) {
            kelompok++;
            cur = 0;
        }
        cur += x;
    }
    return kelompok <= k;
}

ll minBeban(const vector<ll>& a, int k) {
    ll lo = 0, hi = 0;
    for (ll x : a) {
        lo = max(lo, x);
        hi += x;
    }
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (muat(a, k, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    FASTIO;
    vector<ll> a = {7, 2, 5, 10, 8};
    cout << minBeban(a, 2) << '\n'; // 18
    cout << muat(a, 2, 17) << '\n'; // 0
    cout << muat(a, 2, 18) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `lo = 0` padahal satu elemen lebih besar dari `0` dan `ok` salah di bawah max.
2. `hi = 1e9` terlalu kecil: jumlah `2e5 * 1e9` butuh `2e14`.
3. Predikat tidak monoton — binary search diam-diam WA.
4. `mid = 0` lalu bagi `x / mid` tanpa jaga.

**Kompleksitas:** waktu `O(n log S)` dengan `S` selisih batas, memori `O(1)` di luar input.

---

## Binary search bilangan real

**Teori:** Analoginya menimbang beras: tiap kali bagi dua, galat tinggal setengah. `double` punya galat relatif sekitar `1e-15`. Loop tetap `for (int it = 0; it < 80; it++)` lebih aman daripada `while (hi - lo > eps)` yang bisa menggantung. Alasan benar: `2^{-80}` jauh lebih halus dari `1e-9`. Predikat tetap harus monoton.

**Kapan:** minimum waktu real, akar, geometri. Jangan banding `==` dua `double`. Jangan 20 iterasi jika butuh `1e-12`.

**Proses:** akar `2`, cari `x >= 0` dengan `x^2 >= 2`.

1. `lo = 0`, `hi = 2`.
2. `mid = 1`, `1 < 2` → `lo = 1`.
3. `mid = 1.5`, `2.25 >= 2` → `hi = 1.5`.
4. Setelah 80 langkah, `lo` dan `hi` dekat `1.41421356`.
5. Cek `hi * hi` dekat `2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double akar(double n) {
    double lo = 0, hi = max(1.0, n);
    for (int it = 0; it < 80; it++) {
        double mid = (lo + hi) / 2;
        if (mid * mid >= n) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main() {
    FASTIO;
    cout.setf(ios::fixed);
    cout.precision(9);
    cout << akar(2) << '\n';   // 1.414213562
    cout << akar(0) << '\n';   // 0
    cout << akar(100) << '\n'; // 10
    return 0;
}
```

**Jebakan:**
1. `eps = 1e-18` plus `while`, loop tak berhenti.
2. `hi` awal `1` padahal `n = 100`.
3. Overflow `mid * mid` untuk `n` besar. Banding `mid >= n / mid` dengan jaga nol.
4. Mencetak 2 digit lalu heran tes `1e-9` gagal.

**Kompleksitas:** `O(iter)` evaluasi, di sini 80, memori `O(1)`.

---

## Pola predikat monoton

**Teori:** Semua binary search adalah lower bound pada predikat boolean. Tulis `ok(x)` yang berubah `false, false, ..., true, true`. First true adalah jawaban. Analoginya lampu di koridor: dari kiri gelap, dari suatu titik terus terang. Alasan benar: ruang kandidat tetap interval, jadi membuang kiri atau kanan aman.

**Kapan:** setiap kali kamu ragu `hi = mid` atau `lo = mid + 1`. Jangan memaksa pola ini pada fungsi yang naik lalu turun.

**Proses:** cari minimum `x` di `[1, 20]` supaya `x * x >= 30`.

1. `ok(5)`: `25 >= 30` salah.
2. `ok(6)`: `36 >= 30` benar.
3. First true = `6`.
4. `ok(4)` salah, `ok(7)` benar. Monoton.
5. Kalau soalnya “`x` genap saja bagus”, predikat tidak monoton.

Tabel pola:

| soal | `ok(x)` | jawaban |
| --- | --- | --- |
| first `>= t` | `a[i] >= t` | lower bound |
| first `> t` | `a[i] > t` | upper bound |
| min kapasitas | `muat(x)` | first true |
| max yang masih sah | `!ok(x+1)` atau ubah arah | last true |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll firstTrue(ll lo, ll hi, function<bool(ll)> ok) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

ll lastTrue(ll lo, ll hi, function<bool(ll)> ok) {
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2; // condong kanan
        if (ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

int main() {
    FASTIO;
    auto ok = [](ll x) { return x * x >= 30; };
    cout << firstTrue(1, 20, ok) << '\n'; // 6
    auto muat = [](ll x) { return x <= 10; };
    cout << lastTrue(0, 20, muat) << '\n'; // 10
    return 0;
}
```

Last true **wajib** `mid` condong kanan. Tanpa `+ 1`, `lo = mid` menggantung.

**Jebakan:**
1. Menyalin `firstTrue` untuk last true tanpa mengubah mid.
2. `ok` dengan efek samping mengubah array.
3. `hi` tidak inklusif padahal jawaban bisa sama dengan `hi` awal.

**Kompleksitas:** `O(log (hi - lo))` kali biaya `ok`.

---

## Peta keputusan

```text
Array urut, cari nilai?
  → binsearch / lower / upper

Butuh frekuensi atau first-last?
  → upper - lower

Jawaban adalah angka, cek O(n) monoton?
  → binary search on answer

Domain real?
  → 80 iterasi, bukan ==

Predikat naik lalu turun?
  → jangan di file ini, buka ternary.md
```

| pola loop | mid | jika `ok` |
| --- | --- | --- |
| first true | `lo + (hi-lo)/2` | `hi = mid` |
| last true | `lo + (hi-lo+1)/2` | `lo = mid` |
| ketemu sama | `lo + (hi-lo)/2` | `return mid` |

Ringkasan: tulis predikat dulu, baru loop. `hi` awal untuk bound array adalah `n`. On answer, `lo` awal sering `max elemen`, `hi` awal jumlah.

Lanjut ke [ternary.md](ternary.md) untuk fungsi berpuncak satu, atau [interaktif.md](interaktif.md) jika predikatnya dijawab juri.
