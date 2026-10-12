# Sort, Bound, Unique, dan Permutasi

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** urutkan sekali, lalu potong ruang dengan bound; jangan tulis binary search manual jika STL sudah punya.

Day ComprogLearning: **025** algoritma STL. Semua 0-based. Fungsi modular. `typedef long long ll`.

## Daftar isi

- [sort](#sort)
- [stable_sort](#stable_sort)
- [nth_element](#nth_element)
- [lower_bound](#lower_bound)
- [upper_bound](#upper_bound)
- [Frekuensi pada array terurut](#frekuensi-pada-array-terurut)
- [equal_range](#equal_range)
- [unique](#unique)
- [next_permutation](#next_permutation)
- [prev_permutation](#prev_permutation)
- [accumulate dan min/max_element](#accumulate-dan-minmax_element)
- [reverse dan rotate](#reverse-dan-rotate)

---

## sort

> **Ide satu kalimat:** `std::sort` adalah introsort: cepat rata-rata, terjamin O(n log n), **tidak** stabil.

### sort

**Teori:** Analoginya menata kartu dengan campur quick + heap: biasanya cepat, jika pivot jelek beralih ke cara aman. `sort(v.begin(), v.end())` menaik. Tidak menjanjikan elemen sama tetap urutan semula. Alasan benar untuk CP: n=2e5 wajib n log n, dan hampir semua soal tidak peduli stabilitas. Custom urutan lewat lambda atau `greater<>`.

**Kapan:** Pakai hampir setiap kali data perlu urut. Jangan sort tiap query jika data statis — sort sekali. Jangan andalkan urutan asli pada nilai kembar.

**Proses:** `[4, 1, 4, 2]`.

1. Banding dan partisi sampai terurut.
2. Hasil `[1,2,4,4]`.
3. Dua angka 4 boleh tertukar dari posisi asal 0 dan 2.
4. `sort` descending: `greater<ll>()` → `[4,4,2,1]`.
5. Tanpa sort, `lower_bound` tidak sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void urutNaik(vector<ll>& a) {
    sort(a.begin(), a.end());
}

void urutTurun(vector<ll>& a) {
    sort(a.begin(), a.end(), greater<ll>());
}

int main() {
    FASTIO;
    vector<ll> a = {4, 1, 4, 2};
    urutNaik(a);
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n'; // 1 2 4 4
    urutTurun(a);
    cout << a[0] << '\n'; // 4
    return 0;
}
```

**Jebakan:**
1. `sort` pada list atau set iterator tidak random-access — pakai vector.
2. Comparator `<=`.
3. Sort sebagian `sort(a.begin(), a.begin()+k)` lalu lupa k=0.

**Kompleksitas:** waktu O(n log n), memori O(1) tambahan (plus log stack).

---

## stable_sort

> **Ide satu kalimat:** kalau tiket sama harga harus tetap urutan antrean, pakai `stable_sort`.

### stable_sort

**Teori:** Analoginya guru yang mengurut nilai, tapi jika nilai sama nomor absen tidak boleh tertukar. `stable_sort` biasanya mergesort: O(n log n), memori tambahan. Alasan benar: sort multi-kunci bisa dilakukan **bertahap dari kunci terakhir** hanya jika tiap tahap stabil. `std::sort` mematahkan tahap sebelumnya.

**Kapan:** Pakai jika urutan relatif kembar penting, atau sort bertahap. Jangan jika tidak peduli — `sort` lebih cepat konstanta.

**Proses:** Nama-nilai `(Ani,80), (Budi,90), (Cici,80)`. Sort nilai naik, nama tetap pada nilai sama.

| Nama | Nilai | Urutan input | Setelah stable_sort nilai |
| --- | ---: | ---: | ---: |
| Ani | 80 | 0 | 0 |
| Budi | 90 | 1 | 2 |
| Cici | 80 | 2 | 1 |

1. Dua 80: Ani sebelum Cici di input.
2. `stable_sort` by nilai: Ani, Cici, Budi.
3. `sort` by nilai: Ani dan Cici **boleh** tertukar.
4. Jika kamu butuh “siapa daftar lebih dulu”, `sort` bisa WA.
5. Alternatif satu tahap: comparator nilai lalu indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Siswa {
    string nama;
    int nilai;
};

void urutStabilNilai(vector<Siswa>& v) {
    stable_sort(v.begin(), v.end(), [](const Siswa& a, const Siswa& b) {
        return a.nilai < b.nilai;
    });
}

int main() {
    FASTIO;
    vector<Siswa> v = {{"Ani", 80}, {"Budi", 90}, {"Cici", 80}};
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

**Kapan:** Pakai median, k-th, partition. Jangan andalkan kiri sudah terurut. Jangan `k == n`.

**Proses:** `[7,1,5,3,9]`, cari elemen urut ke-2 (0-based) = ke-3 terkecil.

| Urutan penuh | Indeks 0 | 1 | 2 | 3 | 4 |
| --- | ---: | ---: | ---: | ---: | ---: |
| nilai | 1 | 3 | 5 | 7 | 9 |

1. Setelah `nth_element(..., begin+2, ...)`: `a[2]==5`.
2. Kiri `{1,3}` dalam urutan tidak tentu.
3. Kanan `{7,9}` tidak tentu.
4. Median ganjil n=5 ada di indeks 2.
5. Sort penuh juga benar, tetapi lebih mahal jika hanya butuh satu kursi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll elemenKeK(vector<ll> a, int k) {
    nth_element(a.begin(), a.begin() + k, a.end());
    return a[k];
}

int main() {
    FASTIO;
    vector<ll> a = {7, 1, 5, 3, 9};
    cout << elemenKeK(a, 2) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. `k` 1-based terkirim ke `nth_element`.
2. Mengiterasi kiri mengira sudah sort.
3. `nth_element` pada salinan versus in-place tanpa sadar.

**Kompleksitas:** rata-rata O(n), terburuk O(n²) secara teori (mirip quickselect); memori O(1).

---

## lower_bound

> **Ide satu kalimat:** kursi pertama yang orangnya **tidak lebih pendek** dari target: nilai pertama ≥ x.

### lower_bound

**Teori:** Analoginya rak kamus: cari kata pertama yang tidak muncul sebelum x. Iterator ke elemen pertama `>= x`, atau `end()` jika semua lebih kecil. Alasan benar: array **harus terurut naik** (urut yang sama dengan comparator). Mengurangi binary search manual yang rawan off-by-one. Indeks = `it - v.begin()`.

**Kapan:** Pakai pada vector/set terurut. Jangan pada array acak. Jangan `*it` tanpa cek `end()`.

**Proses:** `a = [1,3,3,6,8]`, beberapa x.

| x | arti | indeks | nilai |
| ---: | --- | ---: | ---: |
| 3 | pertama ≥ 3 | 1 | 3 |
| 4 | pertama ≥ 4 | 3 | 6 |
| 0 | pertama ≥ 0 | 0 | 1 |
| 9 | pertama ≥ 9 | 5 | tidak ada |

1. Posisi 0: 1 < 3, maju.
2. Posisi 1: 3 ≥ 3 — berhenti.
3. Indeks 1, bukan 2.
4. x=4 → indeks 3.
5. x=9 → n.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int firstGe(const vector<ll>& a, ll x) {
    return (int)(lower_bound(a.begin(), a.end(), x) - a.begin());
}

int main() {
    FASTIO;
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
3. Comparator sort versus bound tidak sama.

**Kompleksitas:** waktu O(log n), memori O(1).

---

## upper_bound

> **Ide satu kalimat:** kursi pertama yang orangnya **lebih tinggi** dari target: nilai pertama > x.

### upper_bound

**Teori:** Analoginya “setelah semua yang nilainya x”. `upper_bound` = pertama `> x`. Bersama `lower_bound`, jendela `[lo, hi)` adalah semua x. Alasan benar: menghitung kemunculan tanpa scan linear. Pada `set`, `upper_bound` juga ada, log n.

**Kapan:** Pakai hitung berapa x, atau “berapa yang ≤ batas” = `upper_bound(batas) - begin`. Jangan tertukar dengan lower saat soal “≥” versus “>”.

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int firstGt(const vector<ll>& a, ll x) {
    return (int)(upper_bound(a.begin(), a.end(), x) - a.begin());
}

int main() {
    FASTIO;
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

**Teori:** Analoginya menghitung siswa nilai 80: cari orang pertama 80 dan orang pertama 81, selisihnya jumlah. Alasan benar: setelah sort, kemunculan x menempel. Ini pola “berapa elemen di `[L,R]`” juga: `upper(R) - lower(L)`.

**Kapan:** Pakai setelah sort atau pada vector yang sudah urut. Jangan jika banyak update — `map`/Fenwick. Jangan `count(begin,end,x)` di dalam loop n (itu O(n²)).

**Proses:** `a = [1,3,3,6,8]`.

| Pertanyaan | lower | upper | hasil |
| --- | ---: | ---: | ---: |
| jumlah 3 | 1 | 3 | 2 |
| nilai di [3,6] | 1 | 4 | 3 |
| nilai < 6 | 0 | 3 | 3 |
| nilai > 3 | 3 | 5 | 2 |

1. Jumlah 3: `2`.
2. Jumlah nilai di `[3,6]`: 3 elemen.
3. Jumlah `< 6`: 3.
4. Jumlah `> 3`: 2.
5. Semua dari dua indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    vector<ll> a = {1, 3, 3, 6, 8};
    cout << jumlahSama(a, 3) << '\n';         // 2
    cout << jumlahDiRentang(a, 3, 6) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. `R < L` tidak dicek.
2. Memakai `binary_search` yang hanya `bool` lalu scan.
3. Bound pada array menurun tanpa comparator.

**Kompleksitas:** O(log n) per query setelah sort O(n log n); memori O(1).

---

## equal_range

> **Ide satu kalimat:** satu panggilan mengembalikan kedua ujung jendela x.

### equal_range

**Teori:** Analoginya menandai pita “mulai semua 80” dan “habis semua 80” sekaligus. `equal_range` mengembalikan `pair` iterator `{lower, upper}`. Alasan benar: dua binary search internal, kode lebih pendek, dan niat “semua yang sama” terbaca.

**Kapan:** Pakai jika kamu butuh keduanya. Jangan jika hanya butuh “apakah ada” — `binary_search` cukup. Jangan dereferensi `.first` jika jendela kosong.

**Proses:** `a = [1,3,3,6,8]`, x=3.

1. `.first` di indeks 1.
2. `.second` di indeks 3.
3. Jendela `[1,3)` berisi dua angka 3.
4. x=5: `.first == .second` di indeks 3, jendela kosong.
5. Panjang jendela = jarak iterator.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<int, int> jendelaSama(const vector<ll>& a, ll x) {
    auto rg = equal_range(a.begin(), a.end(), x);
    int L = (int)(rg.first - a.begin());
    int R = (int)(rg.second - a.begin());
    return {L, R};
}

int main() {
    FASTIO;
    vector<ll> a = {1, 3, 3, 6, 8};
    auto [L, R] = jendelaSama(a, 3);
    cout << L << ' ' << R << ' ' << (R - L) << '\n'; // 1 3 2
    return 0;
}
```

**Jebakan:**
1. Mengira `.second` inklusif.
2. Array belum sort.
3. Memakai hasil sebagai nilai, bukan indeks.

**Kompleksitas:** O(log n) waktu, O(1) memori.

---

## unique

> **Ide satu kalimat:** `unique` hanya merapikan ke depan; `erase` yang memotong ekor sampah.

### unique

**Teori:** Analoginya barisan siswa: kembar yang **berdampingan** disuruh ke belakang, panjang resmi belum berubah sampai kamu potong. `unique` memindahkan nilai unik berurutan ke prefix, mengembalikan iterator akhir prefix. `size()` tetap. Alasan WA: orang panggil `unique` tanpa `erase`, atau tanpa `sort` dulu sehingga `1,2,1` tetap tiga elemen.

**Kapan:** Pakai kompresi koordinat, distinct numbers. Jangan tanpa sort jika yang diinginkan semua nilai unik global. Jangan lupa `erase`.

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void jadikanUnik(vector<ll>& a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

int main() {
    FASTIO;
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
3. Menyimpan iterator `unique` lalu vector di-`push_back`.

**Kompleksitas:** sort O(n log n) + unique O(n); memori O(1) tambahan.

---

## next_permutation

> **Ide satu kalimat:** dari satu urutan, STL tahu “antrean kamus berikutnya”.

### next_permutation

**Teori:** Analoginya gembok digit yang maju ke kombinasi leksikografis berikutnya. `next_permutation(b,e)` mengubah ke permutasi berikutnya, return `false` jika sudah yang terakhir (lalu kembali ke urutan pertama terurut). Alasan benar: n≤10, 10! = 3.6e6, enumerasi muat. Harus mulai dari urutan terurut jika ingin **semua** permutasi.

**Kapan:** Pakai n kecil, TSP n=8, coba urutan tugas. Jangan n=12 (12! = 479e6, biasanya TLE). Jangan lupa sort awal.

**Proses:** `[1,2,3]`.

| Langkah | Isi | next return |
| ---: | --- | --- |
| 0 | 1 2 3 | true |
| 1 | 1 3 2 | true |
| 2 | 2 1 3 | true |
| 3 | 2 3 1 | true |
| 4 | 3 1 2 | true |
| 5 | 3 2 1 | false, kembali 1 2 3 |

1. Enam permutasi untuk tiga elemen beda.
2. `do-while` wajib agar urutan awal ikut.
3. Duplikat elemen: jumlah < n!.
4. Tanpa sort awal, kamu hanya jalan dari titik sekarang ke akhir.
5. n=10 masih sering muat; n=12 jarang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<ll>> semuaPermutasi(vector<ll> a) {
    sort(a.begin(), a.end());
    vector<vector<ll>> semua;
    do {
        semua.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return semua;
}

int main() {
    FASTIO;
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
3. Duplikat elemen: jumlah < n! (itu benar, unik leksiko).

**Kompleksitas:** n! permutasi, tiap next O(n); total O(n · n!), memori O(n · n!) jika disimpan semua.

---

## prev_permutation

> **Ide satu kalimat:** gembok yang diputar mundur satu langkah kamus.

### prev_permutation

**Teori:** Analoginya tombol “sebelumnya” di playlist yang diurut judul. `prev_permutation` mengubah ke permutasi leksiko sebelumnya. Return `false` jika sudah yang paling kecil, lalu isi menjadi yang paling besar. Alasan benar: kadang soal minta “urutan sebelumnya”, atau kamu enumerasi mundur dari urutan akhir.

**Kapan:** Pakai jika mulai dari urutan besar, atau butuh satu langkah mundur. Jangan campur `next` dan `prev` tanpa sadar arah.

**Proses:** `[1,3,2]`.

1. Sekarang `1,3,2`.
2. `prev` → `1,2,3`.
3. `prev` lagi return false, isi jadi `3,2,1`.
4. Dari `3,2,1`, `prev` → `3,1,2`.
5. Arah berlawanan `next`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> mundurSatu(vector<ll> a) {
    prev_permutation(a.begin(), a.end());
    return a;
}

int main() {
    FASTIO;
    auto a = mundurSatu({1, 3, 2});
    cout << a[0] << a[1] << a[2] << '\n'; // 123
    return 0;
}
```

**Jebakan:**
1. Mengabaikan nilai `bool` — tidak tahu apakah sudah di ujung.
2. Array tidak diisi lengkap n elemen berbeda.
3. Mengira `prev` mengembalikan vector baru; ia mengubah in-place.

**Kompleksitas:** O(n) per panggilan, memori O(1) tambahan.

---

## accumulate dan min/max_element

> **Ide satu kalimat:** jumlah, minimum, dan maksimum sudah ada; yang rawan adalah identitas dan tipe.

### accumulate dan min/max_element

**Teori:** Analoginya kalkulator meja yang harus kamu setel ke 0 sebelum menambah. `accumulate(b,e,0LL)` menjumlah dengan identitas `ll`. Identitas `0` bertipe `int` membuat overflow. `min_element` / `max_element` mengembalikan iterator ke ekstrem pertama. Alasan benar: loop manual sering off-by-one; STL tidak, asal identitas benar.

**Kapan:** Pakai jumlah dan ekstrem pada rentang. Jangan `accumulate` untuk XOR tanpa identitas 0 yang disengaja. Jangan dereference pada range kosong.

**Proses:** `[3, -1, 4]`.

| Fungsi | Identitas / hasil | Nilai |
| --- | --- | ---: |
| jumlah | 0LL | 6 |
| min_element | iterator ke -1 | -1 |
| max_element | iterator ke 4 | 4 |
| posisi min | indeks 1 | 1 |

1. Jumlah 6.
2. Min -1 di indeks 1.
3. Max 4 di indeks 2.
4. Array kosong: iterator `end()`, jangan `*`.
5. `accumulate(..., 0)` overflow jika jumlah > 2e9.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll jumlah(const vector<ll>& a) {
    return accumulate(a.begin(), a.end(), 0LL);
}

pair<ll, ll> minMax(const vector<ll>& a) {
    auto mn = min_element(a.begin(), a.end());
    auto mx = max_element(a.begin(), a.end());
    return {*mn, *mx};
}

int main() {
    FASTIO;
    vector<ll> a = {3, -1, 4};
    cout << jumlah(a) << '\n'; // 6
    auto [mn, mx] = minMax(a);
    cout << mn << ' ' << mx << '\n'; // -1 4
    return 0;
}
```

**Jebakan:**
1. `accumulate` dengan `0` bertipe `int`.
2. `*min_element` pada vector kosong.
3. Mengira `max_element` mengembalikan nilai, bukan iterator.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## reverse dan rotate

> **Ide satu kalimat:** balik pita, atau potong prefix lalu tempel di belakang.

### reverse dan rotate

**Teori:** Analoginya antrian: `reverse` memutar semua orang; `rotate(b, b+k, e)` membuat orang ke-k jadi paling depan. `rotate` memindahkan `[b, mid)` ke belakang. Alasan benar: banyak soal “geser k langkah” atau “balik segmen” tanpa menulis loop rawan. `reverse` pada `[l, r+1)` membalik inklusif 0-based `l..r`.

**Kapan:** Pakai geser array, konstruksi, two pointers palindrom. Jangan `rotate` n kali di loop n — itu O(n²). Jangan `mid` di luar `[b,e]`.

**Proses:** `a = [1,2,3,4,5]`.

1. `reverse` penuh → `[5,4,3,2,1]`.
2. Kembali ke semula, `rotate` k=2 → `[3,4,5,1,2]`.
3. `reverse` hanya `[1,3]` (indeks 1..3 pada array asli) → `[1,4,3,2,5]`.
4. `rotate` k=0 tidak berubah.
5. `rotate` k=n juga tidak berubah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void balikPenuh(vector<ll>& a) {
    reverse(a.begin(), a.end());
}

void geserKiri(vector<ll>& a, int k) {
    int n = (int)a.size();
    if (n == 0) return;
    k %= n;
    rotate(a.begin(), a.begin() + k, a.end());
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 3, 4, 5};
    geserKiri(a, 2);
    for (int i = 0; i < 5; i++) cout << a[i] << " \n"[i == 4];
    // 3 4 5 1 2
    balikPenuh(a);
    cout << a[0] << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `k` lebih besar dari n tanpa modulo.
2. `rotate` ke kanan dikira sama dengan kiri — kanan = `n-k`.
3. `reverse(a.begin()+l, a.begin()+r)` lupa `+1` untuk inklusif r.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Ringkasan

- `sort` tidak stabil; `stable_sort` menjaga kembar.
- `nth_element` hanya menjamin kursi ke-k.
- `lower_bound` ≥, `upper_bound` >; array wajib urut.
- `unique` perlu `sort` plus `erase`.
- Permutasi: sort awal, `do-while`, n kecil.
- `accumulate` wajib `0LL`.

Lanjut: [bitset](bitset.md).
