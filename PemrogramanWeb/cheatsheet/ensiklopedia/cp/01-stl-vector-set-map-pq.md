# 01 — vector, pair, set, map, priority_queue

[← Template dan kompleksitas](00-template-io-kompleksitas.md) · [README dasar](README-dasar.md) · [Lanjut sort dan bitset →](02-stl-sort-bound-bitset.md)

> **Ide satu kalimat:** pilih kotak dulu (array dinamis, himpunan terurut, kamus, antrean prioritas), baru pikir algoritmanya.

Day ComprogLearning: **018** kontainer & comparator, **021** set / map / priority_queue.

Semua 0-based. Fungsi modular. `typedef long long ll`.

## Daftar isi

- [vector](#vector)
- [pair](#pair)
- [tuple](#tuple)
- [Comparator](#comparator)
- [set](#set)
- [multiset](#multiset)
- [map](#map)
- [unordered_map](#unordered_map)
- [priority_queue maksimum](#priority_queue-maksimum)
- [priority_queue minimum](#priority_queue-minimum)
- [string](#string)
- [Adjacency list](#adjacency-list)
- [Lazy delete pada heap](#lazy-delete-pada-heap)
- [Memilih kontainer](#memilih-kontainer)

---

## vector

> **Ide satu kalimat:** `vector` adalah rak yang memanjang ke kanan; akses tengah O(1), sisip tengah mahal.

### vector

**Teori:** Analoginya rak toko yang tinggal menambah kotak di ujung. Di memori, elemen berjejer. `v[i]` langsung. `push_back` biasanya O(1) amortized: kadang pindah rumah (alokasi dobel). Alasan benar sebagai array CP: `n` diketahui atau tumbuh satu-satu, indeks acak sering dibutuhkan, dan cache ramah. `size()` bertipe unsigned — `v.size()-1` pada vector kosong menjadi angka raksasa.

**Kapan dipakai / kapan tidak.** Pakai untuk array, daftar sisi graf, buffer sort. Jangan `insert` di tengah pada n besar (O(n) per sisip). Jangan `v[i]` pada i di luar `[0, size)`.

**Proses:** Mulai kosong, masukkan `7, 2, 5`.

1. `push_back(7)` → `[7]`, `size=1`.
2. `push_back(2)` → `[7,2]`.
3. `push_back(5)` → `[7,2,5]`.
4. `v[1]` adalah `2` (0-based).
5. `pop_back()` → `[7,2]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void tambahBelakang(vector<ll>& v, ll x) {
    v.push_back(x);
}

ll elemenKe(const vector<ll>& v, int i) {
    return v[i]; // i 0-based, pemanggil wajib cek
}

int main() {
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

**Kompleksitas:** akses O(1), `push_back` amortized O(1), sisip/hapus tengah O(n), memori O(n).

---

## pair

> **Ide satu kalimat:** dua nilai yang selalu jalan berdua, diurutkan `.first` dulu.

### pair

**Teori:** Analoginya tiket: nomor antrean dan nama. `pair<ll,int>` menaruh dua tipe dalam satu elemen vector. Sort default: `first` naik, seri pecah di `second`. Alasan benar: banyak soal “nilai plus indeks” atau “titik x,y” tanpa perlu `struct`. `make_pair` dan `{a,b}` sama di C++11+.

**Kapan dipakai / kapan tidak.** Pakai untuk dua medan. Kalau medan ≥3 dan sering dibaca, `struct` lebih jelas dari `pair` bersarang. Jangan mengira `{b,a}` sama dengan `{a,b}` saat sort.

**Proses:** Pasangan `(3,9), (3,1), (2,5)` diurut naik.

1. Banding `first`: `2` paling kecil → `(2,5)`.
2. Dua `first=3`: pecah `second` → `(3,1)` lalu `(3,9)`.
3. Hasil: `(2,5), (3,1), (3,9)`.
4. Jika butuh indeks asal, simpan `{nilai, i}`.
5. Setelah sort, `.second` masih membawa indeks.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<ll, int>> pasangIndeks(const vector<ll>& a) {
    vector<pair<ll, int>> p;
    for (int i = 0; i < (int)a.size(); i++) p.push_back({a[i], i});
    sort(p.begin(), p.end()); // first lalu second
    return p;
}

int main() {
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

**Kapan dipakai / kapan tidak.** Pakai 3–4 medan sementara. Lebih dari itu, `struct` bernama. Jangan `get<1>` vs `get<2>` tertukar diam-diam.

**Proses:** Tiga event `(waktu, jenis, id)`: `(5,1,0), (5,0,1), (2,1,2)`.

1. Sort: waktu `2` dulu → `(2,1,2)`.
2. Waktu `5`: jenis `0` sebelum `1` → `(5,0,1)` lalu `(5,1,0)`.
3. Ini pola sweep: proses “keluar” sebelum “masuk” pada waktu sama jika jenis 0=keluar.
4. `id` hanya pembeda.
5. Urutan akhir: id `2, 1, 0`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> urutEvent(vector<tuple<ll, int, int>> ev) {
    sort(ev.begin(), ev.end());
    vector<int> id;
    for (auto [waktu, jenis, i] : ev) {
        (void)waktu; (void)jenis;
        id.push_back(i);
    }
    return id;
}

int main() {
    vector<tuple<ll, int, int>> ev = {{5, 1, 0}, {5, 0, 1}, {2, 1, 2}};
    auto id = urutEvent(ev);
    cout << id[0] << ' ' << id[1] << ' ' << id[2] << '\n'; // 2 1 0
    return 0;
}
```

**Jebakan:**
1. Tertukar urutan medan di `tuple`.
2. Structured binding di C++14 tidak ada.
3. `tie` vs `make_tuple` saat update referensi.

**Kompleksitas:** sort O(n log n), memori O(n).

---

## Comparator

> **Ide satu kalimat:** comparator adalah hakim yang harus selalu konsisten, bukan “yang ini saya suka”.

### Comparator

**Teori:** Analoginya wasit: jika A lebih dulu dari B, dan B lebih dulu dari C, maka A lebih dulu dari C. `sort` menuntut *strict weak ordering*: `cmp(a,b)` artinya “a harus sebelum b”, dan `cmp(a,a)` harus `false`. Alasan benar: sort boleh membandingkan pasangan mana pun; hakim plin-plan membuat crash / infinite loop / urutan acak. Lambda `[](T a, T b){ return a > b; }` mengurut turun.

**Kapan dipakai / kapan tidak.** Pakai jika urutan bukan default. Jangan `return a <= b` — itu tidak ketat, `a==b` jadi true. Jangan akses global yang berubah di tengah sort.

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

typedef long long ll;

void sortTurun(vector<ll>& a) {
    sort(a.begin(), a.end(), [](ll x, ll y) {
        return x > y; // ketat: sama -> false
    });
}

void sortAbsLaluNilai(vector<ll>& a) {
    sort(a.begin(), a.end(), [](ll x, ll y) {
        if (abs(x) != abs(y)) return abs(x) < abs(y);
        return x < y;
    });
}

int main() {
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
2. `return a < b && a > 0` — tidak total, dua negatif tidak terurut konsisten.
3. Overflow `a-b` sebagai pembanding.

**Kompleksitas:** sort O(n log n) banding; tiap banding O(1) jika lambda sederhana.

---

## set

> **Ide satu kalimat:** `set` adalah rak kamus: unik, selalu terurut, cari O(log n).

### set

**Teori:** Analoginya nama di absen: satu orang satu baris, urut abjad. Di bawahnya pohon seimbang. `insert`, `erase`, `find`, `lower_bound` O(log n). Alasan benar: kamu butuh “apakah sudah ada?” plus “tetangga terdekat” plus urutan, tanpa sort ulang. Duplikat dibuang. Iterasi dari `begin()` ke `end()` menaik.

**Kapan dipakai / kapan tidak.** Pakai distinct + order + neighbor. Jangan jika hanya “pernah muncul?” pada kunci 0..1e6 — array `bool` lebih cepat. Jangan jika butuh duplikat — `multiset`.

**Proses:** Sisip `4, 1, 4, 3`.

1. `4` masuk → `{4}`.
2. `1` masuk → `{1,4}`.
3. `4` ditolak (sudah ada).
4. `3` masuk → `{1,3,4}`.
5. `*s.begin()` = 1, `*s.rbegin()` = 4, `s.count(4)` = 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int banyakUnik(const vector<ll>& a) {
    set<ll> s;
    for (ll x : a) s.insert(x);
    return (int)s.size();
}

ll tetanggaAtas(const set<ll>& s, ll x) {
    auto it = s.lower_bound(x); // pertama >= x
    if (it == s.end()) return LLONG_MAX;
    return *it;
}

int main() {
    vector<ll> a = {4, 1, 4, 3};
    cout << banyakUnik(a) << '\n'; // 3
    set<ll> s(a.begin(), a.end());
    cout << tetanggaAtas(s, 2) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. `*s.begin()` pada set kosong.
2. `erase(it++)` salah tulis lalu iterator invalid.
3. Mengira `count` di `set` bisa >1.

**Kompleksitas:** tiap operasi O(log n), bangun dari n sisip O(n log n), memori O(n).

---

## multiset

> **Ide satu kalimat:** `set` yang mengizinkan kembar, dan `erase(x)` bisa menghapus **semua** x.

### multiset

**Teori:** Analoginya gantungan tiket konser: boleh dua tiket harga sama. CSES Concert Tickets adalah contoh kanonik. `erase(x)` pada `multiset` menghapus **seluruh** nilai x. `erase(it)` menghapus satu. Alasan orang WA: mereka perlakukan seperti `set`. `lower_bound` tetap “pertama ≥”, `upper_bound` “pertama >”.

**Kapan dipakai / kapan tidak.** Pakai kumpulan terurut berulang: tiket, sisa kapasitas, dua heap median (dengan `multiset`). Jangan `erase(nilai)` jika hanya ingin satu kemunculan.

**Proses:** Isi `5, 3, 5`. Hapus satu `5`.

1. Isi: `{3,5,5}`.
2. `erase(5)` (nilai) → `{3}` — kedua 5 hilang. Salah jika niat satu.
3. Benar: `auto it = ms.find(5); if (it!=end) ms.erase(it);` → `{3,5}`.
4. `lower_bound(4)` menunjuk `5` yang tersisa.
5. Size 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void hapusSatu(multiset<ll>& ms, ll x) {
    auto it = ms.find(x);
    if (it != ms.end()) ms.erase(it); // satu node
}

ll tiketTidakMelebihi(multiset<ll>& ms, ll batas) {
    auto it = ms.upper_bound(batas); // pertama > batas
    if (it == ms.begin()) return -1; // semua lebih besar
    --it;
    ll ans = *it;
    ms.erase(it);
    return ans;
}

int main() {
    multiset<ll> ms = {5, 3, 5};
    hapusSatu(ms, 5);
    cout << ms.size() << '\n'; // 2
    cout << tiketTidakMelebihi(ms, 4) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. `ms.erase(x)` menghapus semua x.
2. `--it` saat `it == begin()`.
3. Menyimpan iterator lalu `erase` node lain yang merusak (di `multiset` biasanya aman kecuali iterator yang dihapus).

**Kompleksitas:** O(log n) per operasi, memori O(n).

---

## map

> **Ide satu kalimat:** kamus terurut: kunci unik, nilai boleh apa saja, iterasi urut kunci.

### map

**Teori:** Analoginya laci berlabel nama, isinya jumlah stoples. `map<ll,ll> freq` adalah penghitung untuk nilai 10^9. `freq[x]++` membuat entri 0 lalu tambah jika belum ada. Alasan benar: kunci tidak harus rapat. `find` vs `[]`: `[]` **membuat** kunci. Iterasi `begin()` ke `end()` menaik menurut kunci.

**Kapan dipakai / kapan tidak.** Pakai frekuensi nilai besar, memo kunci aneh, “first occurrence index”. Jangan `[]` hanya untuk cek keberadaan — itu menambah sampah 0. Untuk kunci 0..1e6 rapat, array lebih cepat.

**Proses:** Array `2, 3, 2, 2`.

1. `freq[2]=1`.
2. `freq[3]=1`.
3. `freq[2]=2`, lalu `3`.
4. Kunci terurut: 2 dulu, 3 kemudian.
5. `freq[5]` jika dipanggil jadi 0 dan **masuk** map.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<ll, ll> frekuensi(const vector<ll>& a) {
    map<ll, ll> freq;
    for (ll x : a) freq[x]++;
    return freq;
}

bool adaKunci(const map<ll, ll>& freq, ll x) {
    return freq.find(x) != freq.end(); // tidak membuat entri
}

int main() {
    vector<ll> a = {2, 3, 2, 2};
    auto freq = frekuensi(a);
    cout << freq[2] << '\n'; // 3
    cout << (adaKunci(freq, 5) ? 1 : 0) << '\n'; // 0
    cout << freq.size() << '\n'; // 2, tidak bertambah
    return 0;
}
```

**Jebakan:**
1. `if (freq[x])` membuat x.
2. Iterasi lalu `erase` tanpa `it = m.erase(it)`.
3. `map` O(log n) di dalam n=2e5 × log bisa ketat jika konstanta jelek, tapi biasanya lolos; `unordered_map` lebih cepat rata-rata tapi bisa di-hack.

**Kompleksitas:** akses/ubah O(log k), k = jumlah kunci, memori O(k).

---

## unordered_map

> **Ide satu kalimat:** kamus cepat rata-rata, tapi juri bisa membuatnya O(n) per operasi.

### unordered_map

**Teori:** Analoginya locker berdasarkan hash nomor tas: rata-rata langsung, tapi jika semua tas hash ke loker sama, antrean panjang. Codeforces klasik: anti-hash test pada `unordered_map<long long>`. Alasan `map` lebih aman: O(log n) terjamin. Jika tetap mau hash, pakai custom hash (splitmix). `reserve` mengurangi rehash.

**Kapan dipakai / kapan tidak.** Pakai di AtCoder/CSES jika perlu kecepatan dan kunci banyak. Di Codeforces, `map` atau custom hash. Jangan untuk kunci yang perlu diiterasi terurut.

**Proses:** Hitung berapa pasangan jumlah = 5 pada `[1,4,3,2]`.

1. Baca `1`, cari `5-1=4` belum ada.
2. Simpan `1`.
3. Baca `4`, `5-4=1` ada → 1 pasangan.
4. Simpan `4`. Lanjut `3` dengan `2` belum ada; `2` dengan `3` ada.
5. Total 2 pasangan `(1,4)` dan `(3,2)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct HashAman {
    size_t operator()(ll x) const {
        static const uint64_t FIXED = chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
};

ll banyakPasanganJumlah(const vector<ll>& a, ll target) {
    unordered_map<ll, ll, HashAman> freq;
    ll ans = 0;
    for (ll x : a) {
        auto it = freq.find(target - x);
        if (it != freq.end()) ans += it->second;
        freq[x]++;
    }
    return ans;
}

int main() {
    vector<ll> a = {1, 4, 3, 2};
    cout << banyakPasanganJumlah(a, 5) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `unordered_map` default di CF → TLE hack.
2. `[]` membuat kunci saat mencari pasangan.
3. Iterasi tidak terurut — salah jika butuh next key.

**Kompleksitas:** rata-rata O(1) per operasi, terburuk O(n) tanpa hash aman; memori O(k).

---

## priority_queue maksimum

> **Ide satu kalimat:** tumpukan piring: yang paling besar selalu di puncak.

### priority_queue maksimum

**Teori:** Analoginya antrean IGD yang ternyata “kasus terberat dulu” — itu heap, bukan FIFO. `priority_queue<ll>` default max-heap: `top()` terbesar. `push`/`pop` O(log n). Alasan benar: Dijkstra, greedy “ambil terbesar”, Huffman. Tidak ada iterator terurut; tidak ada hapus nilai tengah kecuali lazy-delete.

**Kapan dipakai / kapan tidak.** Pakai jika hanya butuh ekstrem berulang. Jangan jika butuh hapus sembarang kunci efisien — `multiset`. Jangan mengira `pq[i]` ada.

**Proses:** Push `2, 9, 4`.

1. Heap punya 2; top=2.
2. Masuk 9; top=9.
3. Masuk 4; top tetap 9.
4. `pop` buang 9; top=4.
5. `pop` buang 4; top=2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> ambilKTerbesar(vector<ll> a, int k) {
    priority_queue<ll> pq;
    for (ll x : a) pq.push(x);
    vector<ll> ans;
    while (k-- && !pq.empty()) {
        ans.push_back(pq.top());
        pq.pop();
    }
    return ans;
}

int main() {
    auto ans = ambilKTerbesar({2, 9, 4, 7}, 2);
    cout << ans[0] << ' ' << ans[1] << '\n'; // 9 7
    return 0;
}
```

**Jebakan:**
1. `top()` pada heap kosong.
2. Menyimpan indeks yang sudah tidak valid.
3. Menggunakan heap untuk “cek apakah x ada” — tidak cocok.

**Kompleksitas:** bangun n push O(n log n), k pop O(k log n), memori O(n).

---

## priority_queue minimum

> **Ide satu kalimat:** max-heap yang disuruh memandang angka lewat kacamata minus, atau `greater<ll>`.

### priority_queue minimum

**Teori:** Analoginya loket “nomor kecil dipanggil dulu”. Di STL: `priority_queue<ll, vector<ll>, greater<ll>>`. Alasan benar: Dijkstra memakai jarak terkecil. Alternatif: simpan `-x` di max-heap; hati-hati `LLONG_MIN`. Pair di min-heap: `first` kecil dulu.

**Kapan dipakai / kapan tidak.** Pakai jarak, merge k list, “k terkecil streaming”. Jangan campur `greater` dengan lambda terbalik sampai bingung sendiri.

**Proses:** Push `2, 9, 4` di min-heap.

1. top=2.
2. Masuk 9; top tetap 2.
3. Masuk 4; top tetap 2.
4. pop → top=4.
5. pop → top=9.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll jumlahKTerkecil(const vector<ll>& a, int k) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll x : a) pq.push(x);
    ll s = 0;
    for (int i = 0; i < k && !pq.empty(); i++) {
        s += pq.top();
        pq.pop();
    }
    return s;
}

int main() {
    cout << jumlahKTerkecil({2, 9, 4, 7}, 2) << '\n'; // 2+4=6
    return 0;
}
```

**Jebakan:**
1. Lupa `vector<ll>` di tengah template — compile error.
2. `greater<int>` padahal isinya `ll`.
3. Dijkstra + max-heap — jarak membesar.

**Kompleksitas:** sama dengan max-heap: O(n log n) bangun, memori O(n).

---

## string

> **Ide satu kalimat:** `string` adalah `vector<char>` yang pintar banding dan potong, tapi `s+s` di loop bisa O(n²).

### string

**Teori:** Analoginya pita huruf yang bisa diukur, dipotong, dan dibalik. `s.size()`, `s[i]` 0-based, `s.substr(pos,len)`, `s.find(t)` mengembalikan `npos` jika tidak ada. Alasan benar untuk CP: banyak soal string pendek (≤1e6). `s += c` amortized O(1). `s = s + t` di dalam loop menyalin ulang — TLE klasik. `reverse(s.begin(), s.end())` membalik in-place.

**Kapan dipakai / kapan tidak.** Pakai teks, palindrom, parsing token. Jangan `substr` di tiap indeks pada n=1e6 jika tidak perlu (O(n²) memori/waktu). Jangan banding `==` dengan `char*` tanpa sadar panjang.

**Proses:** `s = "abba"`.

1. `n=4`, `s[0]==s[3]`, `s[1]==s[2]`.
2. Palindrom: ya.
3. `find("bb")` = 1.
4. `substr(1,2)` = `"bb"`.
5. `reverse` → `"abba"` lagi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

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
    string s = "abba";
    cout << palindrom(s) << '\n';     // 1
    cout << posisi(s, "bb") << '\n';  // 1
    cout << posisi(s, "cc") << '\n';  // -1
    return 0;
}
```

**Jebakan:**
1. `s = s + t` di loop n kali.
2. `s.find` hasil `npos` di-cast ke `int` jadi −1 kadang kebetulan, ke `size_t` jadi raksasa.
3. `substr(pos)` tanpa cek `pos > n` — exception / UB tergantung versi.

**Kompleksitas:** `find` O(n·m) naif, `+=` amortized O(1) per karakter, memori O(n).

---

## Adjacency list

> **Ide satu kalimat:** graf adalah `vector<vector<int>>`: indeks simpul, isi tetangganya.

### Adjacency list

**Teori:** Analoginya buku alamat: halaman i berisi daftar teman i. 0-based. Sisi tak berarah: masukkan dua arah. Berbobot: `vector<vector<pair<int,ll>>>`. Alasan benar: sparse graph n,m ≤ 2e5, matriks n² MLE. `g.assign(n, {})` mereset multi tes.

**Kapan dipakai / kapan tidak.** Pakai hampir semua graf kontes. Jangan matriks pada n=1e5. Jangan lupa `n` simpul 0..n-1 vs 1..n (konversi di pintu).

**Proses:** n=4, sisi `0-1`, `1-2`, `1-3`.

1. `g[0]={1}`.
2. `g[1]={0,2,3}`.
3. `g[2]={1}`, `g[3]={1}`.
4. Derajat 1 = 3.
5. DFS/BFS mulai dari 0 mengunjungi semua.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

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

## Lazy delete pada heap

> **Ide satu kalimat:** heap tidak bisa cabut nilai tengah; tandai “sudah mati”, buang saat muncul di puncak.

### Lazy delete pada heap

**Teori:** Analoginya papan antrian: nomor yang batal tetap tertulis, diabaikan saat dipanggil. Simpan `priority_queue` plus `map`/`multiset` hitung, atau dua heap. Saat `top()` sudah dihapus, `pop` terus. Alasan benar: hapus sembarang di heap murni tidak ada; lazy membuat amortisasi O(log n). Alternatif lebih bersih: `multiset`.

**Kapan dipakai / kapan tidak.** Pakai Dijkstra “decrease-key palsu”, median dua heap. Jangan jika hampir semua elemen dihapus sebelum dibaca — `multiset` lebih jujur.

**Proses:** heap max `{9,7,4}`. Hapus 9 secara lazy. `top` harus jadi 7.

1. Push 9,7,4. `mati[9]=1` setelah hapus 9.
2. `bersih()`: top=9 mati, pop, `mati[9]=0`.
3. Top=7 hidup.
4. Hapus 4 lazy, top tetap 7.
5. Pop 7, top=4 mati, pop, kosong.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct HeapLazy {
    priority_queue<ll> pq;
    map<ll, int> mati;
    void push(ll x) { pq.push(x); }
    void hapus(ll x) { mati[x]++; }
    void bersih() {
        while (!pq.empty()) {
            ll t = pq.top();
            auto it = mati.find(t);
            if (it == mati.end() || it->second == 0) break;
            pq.pop();
            it->second--;
        }
    }
    ll top() { bersih(); return pq.top(); }
    bool empty() { bersih(); return pq.empty(); }
};

int main() {
    HeapLazy h;
    h.push(9); h.push(7); h.push(4);
    h.hapus(9);
    cout << h.top() << '\n'; // 7
    return 0;
}
```

**Jebakan:**
1. `hapus` nilai yang tidak ada — `top` bisa salah selamanya.
2. Duplikat: harus `mati` sebagai counter, bukan set.
3. Lupa `bersih` sebelum `empty`.

**Kompleksitas:** amortisasi O(log n) per operasi, memori O(n).

---

## Memilih kontainer

> **Ide satu kalimat:** pertanyaan “apa yang harus cepat?” memilih kotak, bukan kebiasaan.

### Memilih kontainer

**Teori:** Analoginya dapur: pisau untuk potong, sendok untuk kuah. Salah kotak bukan “sedikit lebih lambat”; kadang TLE atau mustahil. Alasan tabel ini benar: tiap kontainer menjamin operasi berbeda. Vector cepat indeks, lambat sisip tengah. Set cepat tetangga, lambat dari array rapat. Heap cepat ekstrem, buta terhadap nilai tengah.

**Kapan dipakai / kapan tidak.** Pakai tabel di menit pertama setelah membaca operasi soal. Jangan memegang `map` untuk indeks 0..n-1. Jangan `set` hanya untuk sort sekali — `vector` + `sort` lebih cepat.

**Proses:** Soal: n=2e5, berulang “hapus satu tiket ≤ harga”.

1. Vector + scan = O(n) per query → TLE.
2. `set` menolak duplikat harga.
3. `multiset` + `upper_bound` + hapus iterator — pas (Day 021 / CSES Concert Tickets).
4. Heap tidak bisa hapus “terdekat ≤”.
5. Keputusan: `multiset`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string pilihKotak(const string& butuh) {
    if (butuh == "indeks acak") return "vector";
    if (butuh == "unik terurut") return "set";
    if (butuh == "duplikat terurut") return "multiset";
    if (butuh == "kunci ke nilai") return "map";
    if (butuh == "ekstrem berulang") return "priority_queue";
    if (butuh == "sort sekali") return "vector+sort";
    return "baca ulang soalnya";
}

int main() {
    cout << pilihKotak("duplikat terurut") << '\n';
    cout << pilihKotak("ekstrem berulang") << '\n';
    return 0;
}
```

Tabel cepat:

| Butuh | Kotak |
| --- | --- |
| Array + indeks | `vector` |
| Dua medan | `pair` / `vector<pair>` |
| Unik + tetangga | `set` |
| Tiket kembar | `multiset` |
| Frekuensi nilai besar | `map` / hash aman |
| Selalu max/min | `priority_queue` |
| Graf | `vector<vector<int>>` |

**Jebakan:**
1. `set` untuk frekuensi — kehilangan jumlah.
2. `map<int,int>` untuk 0..n-1.
3. Heap + “cari nilai x” tiap query.

**Kompleksitas:** keputusan O(1); eksekusi mengikuti kotak.

---

## Ringkasan file 01

- `vector`: rak berjejer, `size()` unsigned.
- `pair`/`tuple`: sort leksikografis.
- Comparator ketat: jangan `<=`.
- `set` unik; `multiset.erase(x)` menghapus semua x.
- `map[]` membuat kunci; `find` tidak.
- Hash default di CF berbahaya.
- Heap hanya ekstrem; hapus tengah = `multiset` atau lazy delete.
- `string`: jangan `s = s + t` di loop; graf: `vector<vector<int>>`.

Lanjut: [02 — sort, bound, bitset](02-stl-sort-bound-bitset.md).
