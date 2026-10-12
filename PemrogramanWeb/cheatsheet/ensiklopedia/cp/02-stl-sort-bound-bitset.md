# 02 — sort, bound, unique, permutasi, bitset

[← STL kontainer](01-stl-vector-set-map-pq.md) · [README dasar](README-dasar.md) · [Lanjut prefix dan window →](03-prefix-diff-twopointer-window.md)

> **Ide satu kalimat:** urutkan sekali, lalu potong ruang dengan bound; atau kemas 64 jawaban boolean dalam satu register.

Day ComprogLearning: **025** algoritma STL, **026** optimasi bitset.

Semua 0-based. Fungsi modular. `typedef long long ll`.

## Daftar isi

- [sort](#sort)
- [stable_sort](#stable_sort)
- [nth_element](#nth_element)
- [lower_bound](#lower_bound)
- [upper_bound](#upper_bound)
- [Frekuensi pada array terurut](#frekuensi-pada-array-terurut)
- [unique](#unique)
- [next_permutation](#next_permutation)
- [bitset dasar](#bitset-dasar)
- [bitset geser dan subset sum](#bitset-geser-dan-subset-sum)
- [Menghitung bit](#menghitung-bit)
- [accumulate dan min/max_element](#accumulate-dan-minmax_element)
- [reverse dan rotate](#reverse-dan-rotate)

---

## sort

> **Ide satu kalimat:** `std::sort` adalah introsort: cepat rata-rata, terjamin O(n log n), **tidak** stabil.

### sort

**Teori:** Analoginya menata kartu dengan campur quick + heap: biasanya cepat, jika pivot jelek beralih ke cara aman. `sort(v.begin(), v.end())` menaik. Tidak menjanjikan elemen sama tetap urutan semula. Alasan benar untuk CP: n=2e5 wajib n log n, dan hampir semua soal tidak peduli stabilitas. Custom urutan lewat lambda (lihat file 01).

**Kapan dipakai / kapan tidak.** Pakai hampir setiap kali data perlu urut. Jangan sort tiap query jika data statis — sort sekali. Jangan andalkan urutan asli pada nilai kembar.

**Proses:** `[4, 1, 4, 2]`.

1. Banding dan partisi sampai terurut.
2. Hasil mungkin `[1,2,4,4]`.
3. Dua angka 4 boleh tertukar dari posisi asal 0 dan 2.
4. `sort` descending: lambda `x > y` → `[4,4,2,1]`.
5. Tanpa sort, `lower_bound` tidak sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void urutNaik(vector<ll>& a) {
    sort(a.begin(), a.end());
}

void urutTurun(vector<ll>& a) {
    sort(a.begin(), a.end(), greater<ll>());
}

int main() {
    vector<ll> a = {4, 1, 4, 2};
    urutNaik(a);
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n'; // 1 2 4 4
    urutTurun(a);
    cout << a[0] << '\n'; // 4
    return 0;
}
```

**Jebakan:**
1. `sort` pada list / set iterator tidak random-access — pakai vector.
2. Comparator `<=`.
3. Sort sebagian `sort(a.begin(), a.begin()+k)` lalu lupa k=0.

**Kompleksitas:** waktu O(n log n), memori O(1) tambahan (plus log stack).

---

## stable_sort

> **Ide satu kalimat:** kalau tiket sama harga harus tetap urutan antrean, pakai `stable_sort`.

### stable_sort

**Teori:** Analoginya guru yang mengurut nilai, tapi jika nilai sama nomor absen tidak boleh tertukar. `stable_sort` biasanya mergesort: O(n log n), memori tambahan. Alasan benar: sort multi-kunci bisa dilakukan **bertahap dari kunci terakhir** hanya jika tiap tahap stabil. `std::sort` mematahkan tahap sebelumnya.

**Kapan dipakai / kapan tidak.** Pakai jika urutan relatif kembar penting, atau sort bertahap. Jangan jika tidak peduli — `sort` lebih cepat konstanta.

**Proses:** Nama-nilai `(Ani,80), (Budi,90), (Cici,80)`. Sort nilai naik, nama tetap pada nilai sama.

1. Dua 80: Ani sebelum Cici di input.
2. `stable_sort` by nilai: Ani, Cici, Budi.
3. `sort` by nilai: Ani dan Cici **boleh** tertukar.
4. Jika kamu butuh “siapa daftar lebih dulu”, `sort` bisa WA.
5. Alternatif satu tahap: comparator nilai lalu indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Siswa {
    string nama;
    int nilai;
    int idx;
};

void urutStabilNilai(vector<Siswa>& v) {
    stable_sort(v.begin(), v.end(), [](const Siswa& a, const Siswa& b) {
        return a.nilai < b.nilai;
    });
}

int main() {
    vector<Siswa> v = {{"Ani", 80, 0}, {"Budi", 90, 1}, {"Cici", 80, 2}};
    urutStabilNilai(v);
    cout << v[0].nama << ' ' << v[1].nama << ' ' << v[2].nama << '\n';
    // Ani Cici Budi
    return 0;
}
```

**Jebakan:**
1. Sort bertahap dengan `sort` biasa — kunci awal hilang.
2. Membandingkan `string` mahal di n besar tanpa indeks.
3. Mengira `greater<>` otomatis stabil.

**Kompleksitas:** waktu O(n log n), memori O(n).

---

## nth_element

> **Ide satu kalimat:** kamu tidak butuh barisan rapi; kamu butuh orang di kursi ke-k.

### nth_element

**Teori:** Analoginya memilih juara ke-3 tanpa menyusun seluruh podium dengan benar kecuali posisi 3. `nth_element(b, b+k, e)` mengatur supaya `[k]` adalah elemen urut ke-k (0-based), kiri ≤ dia, kanan ≥ dia. Alasan benar: median / quickselect rata-rata O(n), lebih cepat dari sort penuh jika hanya satu statistik urutan.

**Kapan dipakai / kapan tidak.** Pakai median, k-th, partition. Jangan andalkan kiri sudah terurut. Jangan `k == n`.

**Proses:** `[7,1,5,3,9]`, cari elemen urut ke-2 (0-based) = ke-3 terkecil.

1. Urutan penuh: `1,3,5,7,9` → indeks 2 adalah `5`.
2. Setelah `nth_element(..., begin+2, ...)`: `a[2]==5`.
3. Kiri `{1,3}` dalam urutan tidak tentu.
4. Kanan `{7,9}` tidak tentu.
5. Median ganjil n=5 ada di indeks 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll elemenKeK(vector<ll> a, int k) { // k 0-based
    nth_element(a.begin(), a.begin() + k, a.end());
    return a[k];
}

int main() {
    vector<ll> a = {7, 1, 5, 3, 9};
    cout << elemenKeK(a, 2) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `k` 1-based terkirim ke `nth_element`.
2. Mengiterasi kiri mengira sudah sort.
3. `nth_element` pada salinan vs in-place tanpa sadar.

**Kompleksitas:** rata-rata O(n), terburuk O(n²) secara teori (mirip quickselect); memori O(1).

---

## lower_bound

> **Ide satu kalimat:** kursi pertama yang orangnya **tidak lebih pendek** dari target: nilai pertama ≥ x.

### lower_bound

**Teori:** Analoginya rak kamus: cari kata pertama yang tidak muncul sebelum x. Iterator ke elemen pertama `>= x`, atau `end()` jika semua lebih kecil. Alasan benar: array **harus terurut naik** (urut yang sama dengan comparator). Mengurangi binary search manual yang rawan off-by-one. Indeks = `it - v.begin()`.

**Kapan dipakai / kapan tidak.** Pakai pada vector/set terurut. Jangan pada array acak. Jangan `*it` tanpa cek `end()`.

**Proses:** `a = [1,3,3,6,8]`, x=3.

1. Posisi 0: 1 < 3, maju.
2. Posisi 1: 3 ≥ 3 — berhenti.
3. Indeks 1, bukan 2.
4. x=4 → indeks 3 (nilai 6).
5. x=9 → indeks 5 = n (tidak ada).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int firstGe(const vector<ll>& a, ll x) {
    return (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
}

int main() {
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << firstGe(a, 3) << '\n'; // 1
    cout << firstGe(a, 4) << '\n'; // 3
    cout << firstGe(a, 9) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Array belum sort.
2. `*lower_bound` saat hasil `end()`.
3. Comparator sort vs bound tidak sama.

**Kompleksitas:** waktu O(log n), memori O(1).

---

## upper_bound

> **Ide satu kalimat:** kursi pertama yang orangnya **lebih tinggi** dari target: nilai pertama > x.

### upper_bound

**Teori:** Analoginya “setelah semua yang nilainya x”. `upper_bound` = pertama `> x`. Bersama `lower_bound`, jendela `[lo, hi)` adalah semua x. Alasan benar: menghitung kemunculan tanpa scan linear. Pada `set`, `upper_bound` juga ada, log n.

**Kapan dipakai / kapan tidak.** Pakai hitung berapa x, atau “berapa yang ≤ batas” = `upper_bound(batas) - begin`. Jangan tertukar dengan lower saat soal “≥” vs “>”.

**Proses:** `a = [1,3,3,6,8]`, x=3.

1. lower = indeks 1.
2. upper = indeks 3 (nilai 6).
3. Jumlah 3 = `3-1=2`.
4. x=5: lower=3, upper=3, jumlah 0.
5. x=8: lower=4, upper=5, jumlah 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int firstGt(const vector<ll>& a, ll x) {
    return (int)(upper_bound(a.begin(), a.end(), x) - a.begin());
}

int main() {
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << firstGt(a, 3) << '\n'; // 3
    cout << firstGt(a, 8) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `upper - lower` tanpa sort.
2. Mengira upper adalah “terakhir == x” — itu `upper-1`, dan harus `upper>0`.
3. `int idx = upper_bound(...)` — itu iterator, bukan int.

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## Frekuensi pada array terurut

> **Ide satu kalimat:** dua bound, satu pengurangan; tidak ada loop mencari kembar.

### Frekuensi pada array terurut

**Teori:** Analoginya menghitung siswa nilai 80: cari orang pertama 80 dan orang pertama 81, selisihnya jumlah. Alasan benar: setelah sort, kemunculan x menempel. `equal_range` mengembalikan kedua iterator sekaligus. Ini pola “berapa elemen di `[L,R]`” juga: `upper(R) - lower(L)`.

**Kapan dipakai / kapan tidak.** Pakai setelah sort atau pada vector yang sudah urut. Jangan jika banyak update — `map`/`fenwick`. Jangan `count(begin,end,x)` di dalam loop n (itu O(n²)).

**Proses:** `a = [1,3,3,6,8]`.

1. Jumlah 3: `2`.
2. Jumlah nilai di `[3,6]`: lower(3)=1, upper(6)=4 → 3 elemen.
3. Jumlah `< 6`: lower(6)=3.
4. Jumlah `> 3`: n - upper(3) = 5-3 = 2.
5. Semua dari dua indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int jumlahSama(const vector<ll>& a, ll x) {
    auto lo = lower_bound(a.begin(), a.end(), x);
    auto hi = upper_bound(a.begin(), a.end(), x);
    return (int)(hi - lo);
}

int jumlahDiRentang(const vector<ll>& a, ll L, ll R) {
    auto lo = lower_bound(a.begin(), a.end(), L);
    auto hi = upper_bound(a.begin(), a.end(), R);
    return (int)(hi - lo);
}

int main() {
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << jumlahSama(a, 3) << '\n';          // 2
    cout << jumlahDiRentang(a, 3, 6) << '\n';  // 3
    return 0;
}
```

**Jebakan:**
1. `R < L` tidak dicek.
2. Overflow tidak relevan di selisih iterator, tapi `L,R` harus `ll` jika nilai besar.
3. Memakai `binary_search` yang hanya `bool` lalu scan.

**Kompleksitas:** O(log n) per query setelah sort O(n log n); memori O(1).

---

## unique

> **Ide satu kalimat:** `unique` hanya merapikan ke depan; `erase` yang memotong ekor sampah.

### unique

**Teori:** Analoginya barisan siswa: kembar yang **berdampingan** disuruh ke belakang, panjang resmi belum berubah sampai kamu potong. `unique` memindahkan nilai unik berurutan ke prefix, mengembalikan iterator akhir prefix. `size()` tetap. Alasan WA: orang panggil `unique` tanpa `erase`, atau tanpa `sort` dulu sehingga `1,2,1` tetap tiga elemen.

**Kapan dipakai / kapan tidak.** Pakai kompresi koordinat, distinct numbers. Jangan tanpa sort jika yang diinginkan semua nilai unik global. Jangan lupa `erase`.

**Proses:** `[4, 1, 4, 1, 1]`.

1. Tanpa sort, `unique` → `[4,1,4,1, ...]` karena 4 dan 1 tidak selalu berdampingan.
2. Sort dulu: `[1,1,1,4,4]`.
3. `unique` prefix `[1,4, ?, ?, ?]`, iterator di indeks 2.
4. `erase` → `[1,4]`.
5. `size()` baru 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void jadikanUnik(vector<ll>& a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

int main() {
    vector<ll> a = {4, 1, 4, 1, 1};
    jadikanUnik(a);
    cout << a.size() << '\n'; // 2
    cout << a[0] << ' ' << a[1] << '\n'; // 1 4
    return 0;
}
```

**Jebakan:**
1. `unique` tanpa `erase`.
2. `unique` tanpa `sort`.
3. Menyimpan iterator `unique` lalu vector di-`push_back` (invalid).

**Kompleksitas:** sort O(n log n) + unique O(n); memori O(1) tambahan.

---

## next_permutation

> **Ide satu kalimat:** dari satu urutan, STL tahu “antrean kamus berikutnya”.

### next_permutation

**Teori:** Analoginya gembok digit yang maju ke kombinasi lexico berikutnya. `next_permutation(b,e)` mengubah ke permutasi berikutnya, return `false` jika sudah yang terakhir (lalu kembali ke urutan pertama terurut). Alasan benar: n≤10, 10! = 3.6e6, enumerasi muat. Harus mulai dari urutan terurut jika ingin **semua** permutasi.

**Kapan dipakai / kapan tidak.** Pakai n kecil, TSP n=8, coba urutan tugas. Jangan n=12 (12! = 479e6, biasanya TLE). Jangan lupa sort awal.

**Proses:** `[1,2,3]`.

1. Sekarang `1,2,3` → next `1,3,2`.
2. Next `2,1,3`.
3. Next `2,3,1`.
4. Next `3,1,2` lalu `3,2,1`.
5. Next return false, isi kembali `1,2,3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<ll>> semuaPermutasi(vector<ll> a) {
    sort(a.begin(), a.end()); // wajib untuk semua
    vector<vector<ll>> semua;
    do {
        semua.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return semua;
}

int main() {
    auto p = semuaPermutasi({1, 3, 2});
    cout << p.size() << '\n'; // 6
    cout << p[0][0] << p[0][1] << p[0][2] << '\n'; // 123
    cout << p[1][0] << p[1][1] << p[1][2] << '\n'; // 132
    return 0;
}
```

**Jebakan:**
1. Tanpa sort awal → bukan semua.
2. `do-while` terbalik jadi `while` — kehilangan urutan pertama.
3. Duplikat elemen: jumlah < n! (itu benar, unik lexico).

**Kompleksitas:** n! permutasi, tiap next O(n); total O(n · n!), memori O(n · n!) jika disimpan semua.

---

## bitset dasar

> **Ide satu kalimat:** 64 saklar dalam satu register; 256 saklar dalam empat register.

### bitset dasar

**Teori:** Analoginya rak absen 200.000 kursi, tiap kursi 1 bit, bukan 1 `int`. `bitset<N>` memakai bitwise AND/OR/XOR massal. Alasan benar: memori /64 dan operasi /64. `bs[i]` adalah bit ke-i (0-based). `set`, `reset`, `test`, `count`. N harus konstanta compile-time.

**Kapan dipakai / kapan tidak.** Pakai himpunan 0..N-1, DP boolean, visibilitas. Jangan N dinamis besar tanpa `vector<uint64_t>` manual. Jangan `bitset` untuk aritmetika biasa.

**Proses:** N=8, nyalakan bit 1 dan 4.

1. Awal `00000000`.
2. `set(1)` → `00000010` (bit 1 dari kanan jika kamu tulis LSB kanan).
3. `set(4)` → bit 1 dan 4 hidup.
4. `test(4)` true, `test(3)` false.
5. `count()` = 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int nyalakanDanHitung() {
    bitset<8> bs;
    bs.set(1);
    bs.set(4);
    return (int)bs.count();
}

bool nyala(const bitset<8>& bs, int i) {
    return bs.test(i);
}

int main() {
    bitset<8> bs;
    bs.set(1);
    bs.set(4);
    cout << nyalakanDanHitung() << '\n'; // 2
    cout << nyala(bs, 4) << ' ' << nyala(bs, 3) << '\n'; // 1 0
    return 0;
}
```

**Jebakan:**
1. `N` bukan compile-time constant.
2. Tertukar “bit 0 paling kiri” saat debug string — `bs.to_string()` bit terbesar di kiri.
3. `bs[i] = 1` vs `set(i)` sama; `reset(i)` mematikan.

**Kompleksitas:** `count`/`and` O(N/64), memori O(N/8) byte.

---

## bitset geser dan subset sum

> **Ide satu kalimat:** `dp |= dp << a[i]` artinya “semua jumlah lama, plus semua jumlah lama + a[i]”.

### bitset geser dan subset sum

**Teori:** Analoginya fotokopi daftar pencapaian, lalu geser fotokopi sejauh `a[i]`, lalu gabung. Bit `j` hidup = ada subset berjumlah j. Awal: bit 0 hidup (subset kosong). Transisi: `dp |= dp << x`. Alasan benar: OR menggabungkan “tidak ambil” (bit lama) dan “ambil” (bit geser). Ini Day 026: subset sum satu baris.

**State:** `dp[j] = 1` jika jumlah j mungkin.
**Transisi:** untuk tiap barang x, `dp := dp OR (dp geser x)`.

**Kapan dipakai / kapan tidak.** Pakai n≤1000, jumlah ≤ 1e5–1e6. Jangan jika nilai negatif (geser tidak mundur). Jangan jika perlu **rekonstruksi** subset tanpa jejak tambahan.

**Proses:** barang `{2, 3, 5}`, target 5.

1. `dp = 1` (bit 0) → jumlah `{0}`.
2. +2: `dp |= dp<<2` → `{0,2}`.
3. +3: `{0,2} ∪ {3,5}` → `{0,2,3,5}`.
4. +5: tambah `{5,7,8,10}` — 5 sudah hidup.
5. `dp[5] = 1` → ya.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int SUMMAX = 1000;

bool subsetSum(const vector<int>& a, int target) {
    bitset<SUMMAX + 1> dp;
    dp[0] = 1;
    for (int x : a) {
        if (x <= SUMMAX) dp |= (dp << x); // ambil atau tidak
    }
    return target <= SUMMAX && dp[target];
}

int main() {
    vector<int> a = {2, 3, 5};
    cout << subsetSum(a, 5) << '\n'; // 1
    cout << subsetSum(a, 4) << '\n'; // 0
    cout << subsetSum(a, 10) << '\n'; // 1 = 2+3+5
    return 0;
}
```

**Jebakan:**
1. `SUMMAX` terlalu kecil — bit terpotong diam.
2. Geser `ll` biasa, bukan bitset, overflow.
3. Barang 0 membuat loop tak berubah (aman) atau tak terhitung (tergantung soal).
4. Target negatif.

**Kompleksitas:** waktu O(n · SUMMAX / 64), memori O(SUMMAX / 8).

---

## Menghitung bit

> **Ide satu kalimat:** `__builtin_popcountll` menghitung lampu yang nyala, bukan nilainya.

### Menghitung bit

**Teori:** Analoginya menghitung saklar ON di papan 64 saklar. GCC/Clang: `popcount`, `ctz` (trailing zeros = indeks bit terendah), `clz` (leading zeros). Alasan benar di bitmask n≤20: iterasi subset, pecah mask. `x & -x` isolasi bit terendah. `x & (x-1)` mematikan bit terendah.

**Kapan dipakai / kapan tidak.** Pakai bitmask, cek genap/ganjil bit, enumerasi subset. Jangan `__builtin_*` jika butuh portable murni tanpa GCC — di kontes GCC hampir selalu ada.

**Proses:** `x = 12` = `1100₂`.

1. `popcount` = 2.
2. `ctz` = 2 (dua nol di ekor).
3. `x & -x` = 4 = bit 2.
4. `x & (x-1)` = 8 = `1000₂`.
5. Satu lampu padam.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int banyakBit(ll x) { return __builtin_popcountll(x); }
int bitTerendahIdx(ll x) { return __builtin_ctzll(x); } // x != 0
ll matikanTerendah(ll x) { return x & (x - 1); }

int main() {
    ll x = 12;
    cout << banyakBit(x) << '\n';        // 2
    cout << bitTerendahIdx(x) << '\n';   // 2
    cout << matikanTerendah(x) << '\n';  // 8
    return 0;
}
```

**Jebakan:**
1. `ctz(0)` undefined.
2. `popcount` pada `ll` memakai versi `int` — salah untuk bit 32–63.
3. Signed negatif: pakai `unsigned` / `ll` dengan hati-hati.

**Kompleksitas:** O(1) per builtin, memori O(1).

---

## accumulate dan min/max_element

> **Ide satu kalimat:** satu sapu STL; akumulator awal harus `0LL`, bukan `0`.

### accumulate dan min/max_element

**Teori:** Analoginya kasir yang menjumlah dari nol, atau wasit yang menunjuk tertinggi. `accumulate(b,e,0LL)` menambah ke `ll`. `0` bertipe `int` — overflow senyap. `min_element` / `max_element` mengembalikan **iterator**, wajib `*` dan cek kosong. `count_if` menghitung yang lolos predikat.

**Kapan dipakai / kapan tidak.** Pakai reduksi cepat. Jangan pada array kosong tanpa cek. Jangan `accumulate` untuk XOR — ada overload dengan lambda (`0LL, bit_xor<ll>()`).

**Proses:** `a = [3, 1, 4]`.

1. Jumlah `0LL+3+1+4=8`.
2. `*max_element` = 4, indeks `max_element - begin` = 2.
3. `*min_element` = 1, indeks 1.
4. `count_if` ganjil: 3 dan 1 → 2.
5. `accumulate` dengan `0` (int) pada `1e9` tiga kali overflow.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll jumlah(const vector<ll>& a) {
    return accumulate(a.begin(), a.end(), 0LL);
}

int indeksMaks(const vector<ll>& a) {
    return (int)(max_element(a.begin(), a.end()) - a.begin());
}

int banyakGanjil(const vector<ll>& a) {
    return (int)count_if(a.begin(), a.end(), [](ll x) { return x % 2 != 0; });
}

int main() {
    vector<ll> a = {3, 1, 4};
    cout << jumlah(a) << '\n';       // 8
    cout << indeksMaks(a) << '\n';   // 2
    cout << banyakGanjil(a) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `accumulate(..., 0)` overflow.
2. `*max_element` pada vector kosong.
3. `% 2` pada negatif untuk “ganjil”.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## reverse dan rotate

> **Ide satu kalimat:** `reverse` membalik selang; `rotate` memutar sehingga `mid` jadi depan.

### reverse dan rotate

**Teori:** Analoginya antrean: reverse = putar 180°, rotate = orang di posisi `mid` jadi yang pertama, yang di depan pindah ke belakang. `rotate(b, b+k, e)` membuat `a[k]` jadi `a[0]`. Alasan benar: memutar array k langkah kiri tanpa array baru. `rotate` ke kanan k: `rotate(b, e-k, e)` (k modulo n).

**Kapan dipakai / kapan tidak.** Pakai reverse string, rotate array, next permutation internal. Jangan `rotate` n kali di loop (O(n²)).

**Proses:** `a = [1,2,3,4,5]`.

1. `reverse` seluruh: `[5,4,3,2,1]`.
2. Kembali. `rotate` kiri 2: `[3,4,5,1,2]`.
3. Dari situ rotate kanan 1 = rotate kiri 4: `[2,3,4,5,1]`? Dari `[3,4,5,1,2]` kanan 1 → `[2,3,4,5,1]`.
4. `reverse` `[0,3)` pada `[1,2,3,4,5]` → `[3,2,1,4,5]`.
5. Indeks 0-based.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void putarKiri(vector<ll>& a, int k) {
    int n = (int)a.size();
    if (n == 0) return;
    k %= n;
    rotate(a.begin(), a.begin() + k, a.end());
}

void putarKanan(vector<ll>& a, int k) {
    int n = (int)a.size();
    if (n == 0) return;
    k %= n;
    rotate(a.begin(), a.end() - k, a.end());
}

int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    putarKiri(a, 2);
    for (int i = 0; i < 5; i++) cout << a[i] << " \n"[i == 4]; // 3 4 5 1 2
    putarKanan(a, 2); // kembali ke 1 2 3 4 5
    reverse(a.begin(), a.end());
    cout << a[0] << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `k` tidak di-mod `n` — iterator di luar.
2. `rotate` kanan memakai `begin()+k` (itu kiri).
3. Reverse lalu lupa indeks soal 1-based.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Ringkasan file 02

- `sort` tidak stabil; `stable_sort` ya.
- `nth_element` hanya menjamin kursi ke-k.
- `lower_bound` ≥, `upper_bound` >; array wajib urut.
- `unique` + `erase` + `sort` dulu.
- `next_permutation` butuh sort awal untuk semua.
- Subset sum: `dp |= dp << x`.
- `popcountll` untuk 64 bit.
- `accumulate` wajib `0LL`; `rotate(b, b+k, e)` adalah putar kiri.

Lanjut: [03 — prefix, difference, two pointers, window](03-prefix-diff-twopointer-window.md).
