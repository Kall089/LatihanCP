# Vector, Pair, Tuple, dan Comparator

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** pilih kotak dulu (array dinamis, pasangan, hakim urutan), baru pikir algoritmanya.

Day ComprogLearning: **018** kontainer dan comparator. Semua indeks 0-based. Fungsi modular. `typedef long long ll`.

## Daftar isi

- [vector](#vector)
- [resize versus reserve](#resize-versus-reserve)
- [pair](#pair)
- [tuple](#tuple)
- [struct bernama](#struct-bernama)
- [Comparator](#comparator)
- [operator kurang pada struct](#operator-kurang-pada-struct)
- [string](#string)
- [stack dan queue](#stack-dan-queue)
- [deque](#deque)
- [Adjacency list](#adjacency-list)
- [Memilih kontainer dasar](#memilih-kontainer-dasar)

---

## vector

> **Ide satu kalimat:** `vector` adalah rak yang memanjang ke kanan; akses tengah O(1), sisip tengah mahal.

### vector

**Teori:** Analoginya rak toko yang tinggal menambah kotak di ujung. Di memori, elemen berjejer. `v[i]` langsung. `push_back` biasanya O(1) amortized: kadang pindah rumah (alokasi dobel). Alasan benar sebagai array CP: `n` diketahui atau tumbuh satu-satu, indeks acak sering dibutuhkan, dan cache ramah. `size()` bertipe unsigned — `v.size()-1` pada vector kosong menjadi angka raksasa.

**Kapan:** Pakai untuk array, daftar sisi graf, dan buffer sort. Jangan `insert` di tengah pada n besar (O(n) per sisip). Jangan `v[i]` pada i di luar `[0, size)`.

**Proses:** Mulai kosong, masukkan `7, 2, 5`.

| Langkah | Operasi | Isi | size |
| ---: | --- | --- | ---: |
| 1 | `push_back(7)` | `[7]` | 1 |
| 2 | `push_back(2)` | `[7, 2]` | 2 |
| 3 | `push_back(5)` | `[7, 2, 5]` | 3 |
| 4 | `v[1]` | nilai `2` | 3 |
| 5 | `pop_back()` | `[7, 2]` | 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void tambahBelakang(vector<ll>& v, ll x) {
    v.push_back(x);
}

ll elemenKe(const vector<ll>& v, int i) {
    return v[i];
}

int main() {
    FASTIO;
    vector<ll> v;
    tambahBelakang(v, 7);
    tambahBelakang(v, 2);
    tambahBelakang(v, 5);
    cout << elemenKe(v, 1) << '\n'; // 2
    v.pop_back();
    cout << v.size() << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `v[v.size()-1]` saat kosong — underflow unsigned.
2. Referensi ke elemen rusak setelah `push_back` yang realloc.
3. `vector<int> v(n); v[n] = 1;` — out of bounds.

**Kompleksitas:** akses O(1), `push_back` amortized O(1), sisip atau hapus tengah O(n), memori O(n).

---

## resize versus reserve

> **Ide satu kalimat:** `resize` menambah elemen sungguhan; `reserve` hanya memesan kursi kosong.

### resize versus reserve

**Teori:** Analoginya restoran: `reserve(100)` menyiapkan 100 kursi tanpa tamu; `resize(100)` mendudukkan 100 tamu bernilai default. `capacity()` adalah kursi, `size()` adalah tamu. Alasan orang TLE atau WA: mereka `reserve` lalu menulis `v[i]` seolah size sudah n, atau mereka `push_back` setelah `resize(n)` sehingga array jadi 2n.

**Kapan:** Pakai `vector<ll> a(n)` atau `resize(n)` jika kamu akan mengisi `a[i]`. Pakai `reserve(n)` jika kamu akan `push_back` n kali. Jangan campur keduanya tanpa sadar.

**Proses:** Ingin array tiga angka `9, 8, 7`.

1. `resize(3)` → `[0,0,0]`, lalu `a[0]=9`, `a[1]=8`, `a[2]=7`.
2. `reserve(3)` → size masih 0; `a[0]=9` adalah undefined behavior.
3. `reserve(3)` lalu `push_back` tiga kali — benar, tidak realloc.
4. `resize(3)` lalu tiga `push_back` → size 6.
5. Pilih satu gaya dan konsisten.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> isiDenganIndeks(const vector<ll>& sumber) {
    int n = (int)sumber.size();
    vector<ll> a(n);
    for (int i = 0; i < n; i++) a[i] = sumber[i];
    return a;
}

vector<ll> isiDenganPush(const vector<ll>& sumber) {
    vector<ll> a;
    a.reserve(sumber.size());
    for (ll x : sumber) a.push_back(x);
    return a;
}

int main() {
    FASTIO;
    vector<ll> sumber = {9, 8, 7};
    auto a = isiDenganIndeks(sumber);
    auto b = isiDenganPush(sumber);
    cout << a[2] << ' ' << b[2] << '\n'; // 7 7
    cout << a.size() << ' ' << b.size() << '\n'; // 3 3
    return 0;
}
```

**Jebakan:**
1. `reserve` lalu `v[i] = x`.
2. `resize` lalu `push_back` tanpa niat menggandakan.
3. Mengira `capacity()` ikut tersimpan di file tes.

**Kompleksitas:** alokasi sekali O(n), isi O(n), memori O(n).

---

## pair

> **Ide satu kalimat:** dua nilai yang selalu jalan berdua, diurutkan `.first` dulu.

### pair

**Teori:** Analoginya tiket: nomor antrean dan nama. `pair<ll,int>` menaruh dua tipe dalam satu elemen vector. Sort default: `first` naik, seri pecah di `second`. Alasan benar: banyak soal “nilai plus indeks” atau “titik x,y” tanpa perlu `struct`. `make_pair` dan `{a,b}` sama di C++11+.

**Kapan:** Pakai untuk dua medan. Kalau medan ≥3 dan sering dibaca, `struct` lebih jelas dari `pair` bersarang. Jangan mengira `{b,a}` sama dengan `{a,b}` saat sort.

**Proses:** Pasangan `(3,9), (3,1), (2,5)` diurut naik.

| Urutan input | Kunci first | Kunci second | Urutan setelah sort |
| --- | ---: | ---: | --- |
| (3, 9) | 3 | 9 | ketiga |
| (3, 1) | 3 | 1 | kedua |
| (2, 5) | 2 | 5 | pertama |

1. Banding `first`: `2` paling kecil → `(2,5)`.
2. Dua `first=3`: pecah `second` → `(3,1)` lalu `(3,9)`.
3. Hasil: `(2,5), (3,1), (3,9)`.
4. Jika butuh indeks asal, simpan `{nilai, i}`.
5. Setelah sort, `.second` masih membawa indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<pair<ll, int>> pasangIndeks(const vector<ll>& a) {
    vector<pair<ll, int>> p;
    for (int i = 0; i < (int)a.size(); i++) p.push_back({a[i], i});
    sort(p.begin(), p.end());
    return p;
}

int main() {
    FASTIO;
    vector<ll> a = {3, 3, 2};
    auto p = pasangIndeks(a);
    cout << p[0].first << ' ' << p[0].second << '\n'; // 2 2
    cout << p[1].first << ' ' << p[1].second << '\n'; // 3 0
    return 0;
}
```

**Jebakan:**
1. Lupa indeks ikut tersimpan lalu tidak bisa kembali ke posisi semula.
2. `pair` di `priority_queue` — urutan prioritas bisa terasa terbalik.
3. Membandingkan hanya `.first` di kepala, padahal sort memakai keduanya.

**Kompleksitas:** sort O(n log n), memori O(n).

---

## tuple

> **Ide satu kalimat:** `pair` yang punya kursi ketiga (dan seterusnya).

### tuple

**Teori:** Analoginya formulir tiga kolom: nilai, waktu, indeks. `tuple<ll,ll,int>` diurutkan leksikografis dari kiri. Akses lama `get<0>(t)`, C++17 `auto [x,y,z] = t`. Alasan benar: tiga kunci sort tanpa menulis `struct` + `operator<`. Keterbacaan menurun cepat setelah empat medan.

**Kapan:** Pakai 3–4 medan sementara. Lebih dari itu, `struct` bernama. Jangan `get<1>` versus `get<2>` tertukar diam-diam.

**Proses:** Tiga event `(waktu, jenis, id)`: `(5,1,0), (5,0,1), (2,1,2)`.

1. Sort: waktu `2` dulu → `(2,1,2)`.
2. Waktu `5`: jenis `0` sebelum `1` → `(5,0,1)` lalu `(5,1,0)`.
3. Ini pola sweep: proses “keluar” sebelum “masuk” pada waktu sama jika jenis 0=keluar.
4. `id` hanya pembeda.
5. Urutan akhir id: `2, 1, 0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> urutEvent(vector<tuple<ll, int, int>> ev) {
    sort(ev.begin(), ev.end());
    vector<int> id;
    for (auto [waktu, jenis, i] : ev) {
        (void)waktu;
        (void)jenis;
        id.push_back(i);
    }
    return id;
}

int main() {
    FASTIO;
    vector<tuple<ll, int, int>> ev = {{5, 1, 0}, {5, 0, 1}, {2, 1, 2}};
    auto id = urutEvent(ev);
    cout << id[0] << ' ' << id[1] << ' ' << id[2] << '\n'; // 2 1 0
    return 0;
}
```

**Jebakan:**
1. Tertukar urutan medan di `tuple`.
2. Structured binding di C++14 tidak ada.
3. `tie` versus `make_tuple` saat update referensi.

**Kompleksitas:** sort O(n log n), memori O(n).

---

## struct bernama

> **Ide satu kalimat:** kalau medan punya arti, beri nama; jangan `pair` di dalam `pair`.

### struct bernama

**Teori:** Analoginya formulir rumah sakit: “nama” dan “umur” lebih aman daripada “first” dan “second”. `struct` membuat kode dibaca seperti soal. Tanpa `operator<`, `sort` tidak tahu cara membandingkan. Alasan benar: bug “tertukar medan” turun drastis saat nama lapangan berbicara.

**Kapan:** Pakai saat tiga medan atau lebih, atau dua medan yang sering dibaca. Jangan `struct` jika hanya sekali sort kecil dan `pair` sudah jelas.

**Proses:** Tiga siswa: Ani 80, Budi 90, Cici 80. Urut nilai naik, jika seri nama naik.

1. Banding nilai: Budi 90 paling besar → terakhir.
2. Ani dan Cici sama 80: nama `Ani < Cici`.
3. Hasil: Ani, Cici, Budi.
4. Jika hanya `pair<int,string>`, `first` harus nilai.
5. Jika tertukar, sort jadi urut nama — WA senyap.

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

bool lebihDulu(const Siswa& a, const Siswa& b) {
    if (a.nilai != b.nilai) return a.nilai < b.nilai;
    return a.nama < b.nama;
}

int main() {
    FASTIO;
    vector<Siswa> v = {{"Ani", 80}, {"Budi", 90}, {"Cici", 80}};
    sort(v.begin(), v.end(), lebihDulu);
    cout << v[0].nama << ' ' << v[1].nama << ' ' << v[2].nama << '\n';
    // Ani Cici Budi
    return 0;
}
```

**Jebakan:**
1. Lupa pecah seri — urutan jadi tidak deterministik relatif terhadap `sort` tidak stabil.
2. Membandingkan `string` mahal di n besar tanpa indeks.
3. `struct` di `set` tanpa `operator<`.

**Kompleksitas:** sort O(n log n) kali biaya banding; memori O(n).

---

## Comparator

> **Ide satu kalimat:** comparator adalah hakim yang harus selalu konsisten, bukan “yang ini saya suka”.

### Comparator

**Teori:** Analoginya wasit: jika A lebih dulu dari B, dan B lebih dulu dari C, maka A lebih dulu dari C. `sort` menuntut *strict weak ordering*: `cmp(a,b)` artinya “a harus sebelum b”, dan `cmp(a,a)` harus `false`. Alasan benar: sort boleh membandingkan pasangan mana pun; hakim plin-plan membuat crash, infinite loop, atau urutan acak. Lambda `[](T a, T b){ return a > b; }` mengurut turun.

**Kapan:** Pakai jika urutan bukan default. Jangan `return a <= b` — itu tidak ketat, `a==b` jadi true. Jangan akses global yang berubah di tengah sort.

**Proses:** Angka `3, 1, 2` diurut turun.

1. Hakim: `a` sebelum `b` jika `a > b`.
2. `3` sebelum `2`, `2` sebelum `1`.
3. Hasil `[3,2,1]`.
4. Jika hakim `a >= b`, saat `a==b` ia bilang “a sebelum b” dan “b sebelum a” — rusak.
5. Untuk struct: banding satu medan, seri ke medan kedua.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void sortTurun(vector<ll>& a) {
    sort(a.begin(), a.end(), [](ll x, ll y) {
        return x > y;
    });
}

void sortAbsLaluNilai(vector<ll>& a) {
    sort(a.begin(), a.end(), [](ll x, ll y) {
        if (abs(x) != abs(y)) return abs(x) < abs(y);
        return x < y;
    });
}

int main() {
    FASTIO;
    vector<ll> a = {3, 1, 2};
    sortTurun(a);
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n'; // 3 2 1
    vector<ll> b = {-2, 2, -3};
    sortAbsLaluNilai(b);
    cout << b[0] << ' ' << b[1] << ' ' << b[2] << '\n'; // -2 2 -3
    return 0;
}
```

**Jebakan:**
1. `<=` atau `>=` di comparator.
2. `return a < b && a > 0` — dua negatif tidak terurut konsisten.
3. Overflow `a-b` sebagai pembanding.

**Kompleksitas:** sort O(n log n) banding; tiap banding O(1) jika lambda sederhana.

---

## operator kurang pada struct

> **Ide satu kalimat:** `set` dan `map` memakai `<`; kalau structmu bisu, mereka menolak.

### operator kurang pada struct

**Teori:** Analoginya kamus yang hanya bisa disusun jika setiap kata punya urutan abjad. `operator<` memberi urutan default. Harus ketat: `a < a` false, dan tidak boleh `a < b` sekaligus `b < a`. Alasan benar: `set<Siswa>` dan `sort` tanpa lambda memakai operator ini.

**Kapan:** Pakai jika struct masuk `set`/`map` atau sering di-sort default. Jangan menulis `<` yang bergantung pada medan yang berubah setelah objek masuk set.

**Proses:** Titik `(1,4), (1,2), (0,9)`.

1. Banding x dulu: `(0,9)` paling kiri.
2. x sama 1: y `2` sebelum `4`.
3. Urutan: `(0,9), (1,2), (1,4)`.
4. `set` menolak titik sama karena `!(a<b) && !(b<a)` artinya ekuivalen.
5. Jika butuh duplikat titik, tambah indeks ke kunci.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Titik {
    ll x, y;
    bool operator<(const Titik& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

vector<Titik> urutTitik(vector<Titik> a) {
    sort(a.begin(), a.end());
    return a;
}

int main() {
    FASTIO;
    auto a = urutTitik({{1, 4}, {1, 2}, {0, 9}});
    cout << a[0].x << ' ' << a[0].y << '\n'; // 0 9
    cout << a[1].x << ' ' << a[1].y << '\n'; // 1 2
    return 0;
}
```

**Jebakan:**
1. `operator<` memakai `<=`.
2. Mengubah `x` objek yang sudah ada di `set`.
3. Lupa `const` pada operator — `set` mengeluh.

**Kompleksitas:** sort O(n log n), `set` insert O(log n), memori O(n).

---

## string

> **Ide satu kalimat:** `string` adalah `vector<char>` yang pintar banding dan potong, tapi `s+s` di loop bisa O(n²).

### string

**Teori:** Analoginya pita huruf yang bisa diukur, dipotong, dan dibalik. `s.size()`, `s[i]` 0-based, `s.substr(pos,len)`, `s.find(t)` mengembalikan `npos` jika tidak ada. Alasan benar untuk CP: banyak soal string pendek (≤1e6). `s += c` amortized O(1). `s = s + t` di dalam loop menyalin ulang — TLE klasik.

**Kapan:** Pakai teks, palindrom, parsing token. Jangan `substr` di tiap indeks pada n=1e6 jika tidak perlu. Jangan banding `==` dengan `char*` tanpa sadar panjang.

**Proses:** `s = "abba"`.

| i | s[i] | s[n-1-i] | sama? |
| ---: | --- | --- | --- |
| 0 | a | a | ya |
| 1 | b | b | ya |

1. `n=4`, dua pasangan cocok.
2. Palindrom: ya.
3. `find("bb")` = 1.
4. `substr(1,2)` = `"bb"`.
5. `reverse` → `"abba"` lagi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool palindrom(const string& s) {
    int n = (int)s.size();
    for (int i = 0; i < n / 2; i++)
        if (s[i] != s[n - 1 - i]) return false;
    return true;
}

int posisi(const string& s, const string& t) {
    auto p = s.find(t);
    if (p == string::npos) return -1;
    return (int)p;
}

int main() {
    FASTIO;
    string s = "abba";
    cout << palindrom(s) << '\n';    // 1
    cout << posisi(s, "bb") << '\n'; // 1
    cout << posisi(s, "cc") << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. `s = s + t` di loop n kali.
2. `s.find` hasil `npos` di-cast ke `size_t` jadi raksasa.
3. `substr(pos)` tanpa cek `pos > n`.

**Kompleksitas:** `find` O(n·m) naif, `+=` amortized O(1) per karakter, memori O(n).

---

## stack dan queue

> **Ide satu kalimat:** `stack` hanya puncak, `queue` hanya kepala; keduanya bukan array.

### stack dan queue

**Teori:** Analoginya tumpukan piring versus antrean loket. `stack` LIFO: `push`, `pop`, `top`. `queue` FIFO: `push`, `pop`, `front`. Alasan benar: DFS iteratif memakai stack, BFS memakai queue. Tidak ada akses indeks. `pop` tidak mengembalikan nilai — ambil dulu, buang kemudian.

**Kapan:** Pakai DFS/BFS, matching kurung, simulasi antrean. Jangan jika butuh hapus tengah atau cari nilai. Jangan `top()` pada stack kosong.

**Proses:** Kurung `"(()())"`.

| i | karakter | stack setelah | valid sementara |
| ---: | --- | --- | --- |
| 0 | `(` | `(` | ya |
| 1 | `(` | `((` | ya |
| 2 | `)` | `(` | ya |
| 3 | `(` | `((` | ya |
| 4 | `)` | `(` | ya |
| 5 | `)` | kosong | ya |

1. Buka: push.
2. Tutup: pop jika tidak kosong.
3. Akhir harus kosong.
4. `")("` gagal di indeks 0.
5. `"(()"` gagal karena sisa satu buka.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool kurungSeimbang(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') st.push(c);
        else {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    FASTIO;
    cout << kurungSeimbang("(()())") << '\n'; // 1
    cout << kurungSeimbang(")(") << '\n';     // 0
    cout << kurungSeimbang("(()") << '\n';    // 0
    return 0;
}
```

**Jebakan:**
1. `pop` sebelum cek kosong.
2. Mengira `queue` punya `back` untuk BFS jarak — `front` yang diproses.
3. Memakai `stack` untuk antrean BFS.

**Kompleksitas:** tiap operasi O(1), memori O(n).

---

## deque

> **Ide satu kalimat:** vector yang pintar di dua ujung; tengah tetap mahal.

### deque

**Teori:** Analoginya antrean yang boleh potong kompas dan potong buntut. `push_front`, `push_back`, `pop_front`, `pop_back` amortized O(1). `dq[i]` ada, tetapi tidak secepat `vector` di cache. Alasan benar: sliding window dan BFS 0-1 butuh potong depan tanpa `erase` O(n).

**Kapan:** Pakai window, 0-1 BFS, “antrian dua ujung”. Jangan sebagai pengganti vector biasa jika hanya `push_back`. Jangan `insert` di tengah pada n besar.

**Proses:** Mulai kosong. Masuk belakang 1, depan 9, belakang 3.

1. `push_back(1)` → `[1]`.
2. `push_front(9)` → `[9,1]`.
3. `push_back(3)` → `[9,1,3]`.
4. `dq[1] = 1`.
5. `pop_front()` → `[1,3]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void prosesUjung(deque<ll>& dq, ll depan, ll belakang) {
    dq.push_front(depan);
    dq.push_back(belakang);
}

int main() {
    FASTIO;
    deque<ll> dq;
    dq.push_back(1);
    prosesUjung(dq, 9, 3);
    cout << dq[0] << ' ' << dq[1] << ' ' << dq[2] << '\n'; // 9 1 3
    dq.pop_front();
    cout << dq.front() << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `pop_front` pada deque kosong.
2. Referensi ke elemen rusak setelah pertumbuhan besar.
3. Memakai deque untuk array acak murni tanpa alasan.

**Kompleksitas:** ujung O(1), akses `dq[i]` O(1) tapi konstanta lebih jelek, memori O(n).

---

## Adjacency list

> **Ide satu kalimat:** graf adalah `vector<vector<int>>`: indeks simpul, isi tetangganya.

### Adjacency list

**Teori:** Analoginya buku alamat: halaman i berisi daftar teman i. 0-based. Sisi tak berarah: masukkan dua arah. Berbobot: `vector<vector<pair<int,ll>>>`. Alasan benar: sparse graph n,m ≤ 2e5, matriks n² MLE. `g.assign(n, {})` mereset multi tes.

**Kapan:** Pakai hampir semua graf kontes. Jangan matriks pada n=1e5. Jangan lupa `n` simpul 0..n-1 versus 1..n (konversi di pintu).

**Proses:** n=4, sisi `0-1`, `1-2`, `1-3`.

| Simpul | Tetangga |
| ---: | --- |
| 0 | 1 |
| 1 | 0, 2, 3 |
| 2 | 1 |
| 3 | 1 |

1. `g[0]={1}`.
2. `g[1]={0,2,3}`.
3. Derajat 1 = 3.
4. DFS/BFS mulai dari 0 mengunjungi semua.
5. Sisi berarah hanya `push` satu arah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<int>> bangunTakBerarah(int n, const vector<pair<int, int>>& sisi) {
    vector<vector<int>> g(n);
    for (auto [u, v] : sisi) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

int derajat(const vector<vector<int>>& g, int u) {
    return (int)g[u].size();
}

int main() {
    FASTIO;
    auto g = bangunTakBerarah(4, {{0, 1}, {1, 2}, {1, 3}});
    cout << derajat(g, 1) << '\n'; // 3
    cout << g[0][0] << '\n';       // 1
    return 0;
}
```

**Jebakan:**
1. Hanya satu arah pada graf tak berarah.
2. `g[n]` pada `vector(n)`.
3. Multi tes: `g` tidak di-`assign`.

**Kompleksitas:** bangun O(n+m), memori O(n+m).

---

## Memilih kontainer dasar

> **Ide satu kalimat:** pertanyaan “apa yang harus cepat?” memilih kotak, bukan kebiasaan.

### Memilih kontainer dasar

**Teori:** Analoginya dapur: pisau untuk potong, sendok untuk kuah. Salah kotak bukan “sedikit lebih lambat”; kadang TLE atau mustahil. Vector cepat indeks, lambat sisip tengah. Stack/queue cepat ujung, buta terhadap tengah. Deque cepat dua ujung. Pair/tuple hanya kemasan.

**Kapan:** Pakai tabel di menit pertama setelah membaca operasi soal. Jangan memegang `map` untuk indeks 0..n-1. Jangan `deque` jika `vector` cukup.

**Proses:** Soal: n=2e5, akses `a[i]` dan `push_back`.

1. `list` — akses tengah O(n), salah.
2. `set` — tidak ada `a[i]` O(1).
3. `vector` — pas.
4. Jika nanti butuh potong depan window, pindah ke `deque`.
5. Keputusan mengikuti operasi, bukan mengikuti “kontainer favorit”.

| Butuh | Kotak |
| --- | --- |
| Array + indeks | `vector` |
| Dua medan | `pair` |
| Tiga medan sementara | `tuple` |
| Medan bernama | `struct` |
| LIFO / kurung | `stack` |
| FIFO / BFS | `queue` |
| Dua ujung | `deque` |
| Graf | `vector<vector<int>>` |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string pilihKotakDasar(const string& butuh) {
    if (butuh == "indeks acak") return "vector";
    if (butuh == "dua medan") return "pair";
    if (butuh == "bfs") return "queue";
    if (butuh == "kurung") return "stack";
    if (butuh == "dua ujung") return "deque";
    return "baca ulang soalnya";
}

int main() {
    FASTIO;
    cout << pilihKotakDasar("indeks acak") << '\n';
    cout << pilihKotakDasar("bfs") << '\n';
    return 0;
}
```

**Jebakan:**
1. `set` untuk sort sekali — `vector` + `sort` lebih cepat.
2. `queue` untuk akses indeks.
3. `pair<pair<...>>` sampai tidak terbaca.

**Kompleksitas:** keputusan O(1); eksekusi mengikuti kotak.

---

## Ringkasan

- `vector`: rak berjejer, `size()` unsigned, `reserve` bukan `resize`.
- `pair`/`tuple`: sort leksikografis.
- Comparator ketat: jangan `<=`.
- `struct` bernama lebih aman dari `pair` bersarang.
- `string`: jangan `s = s + t` di loop.
- Graf: `vector<vector<int>>`.

Lanjut: [set, map, priority_queue](set-map-pq.md).
