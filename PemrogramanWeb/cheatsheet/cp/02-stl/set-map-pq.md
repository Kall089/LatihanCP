# Set, Map, dan Priority Queue

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** himpunan terurut, kamus, dan tumpukan ekstrem adalah tiga jawaban untuk tiga pertanyaan berbeda.

Day ComprogLearning: **021** set, map, priority_queue. Semua 0-based. Fungsi modular. `typedef long long ll`.

## Daftar isi

- [set](#set)
- [Tetangga pada set](#tetangga-pada-set)
- [multiset](#multiset)
- [map](#map)
- [unordered_map](#unordered_map)
- [priority_queue maksimum](#priority_queue-maksimum)
- [priority_queue minimum](#priority_queue-minimum)
- [Lazy delete pada heap](#lazy-delete-pada-heap)
- [Dua heap untuk median](#dua-heap-untuk-median)
- [Memilih set map atau heap](#memilih-set-map-atau-heap)

---

## set

> **Ide satu kalimat:** `set` adalah rak kamus: unik, selalu terurut, cari O(log n).

### set

**Teori:** Analoginya nama di absen: satu orang satu baris, urut abjad. Di bawahnya pohon seimbang. `insert`, `erase`, `find`, `lower_bound` O(log n). Alasan benar: kamu butuh “apakah sudah ada?” plus “tetangga terdekat” plus urutan, tanpa sort ulang. Duplikat dibuang. Iterasi dari `begin()` ke `end()` menaik.

**Kapan:** Pakai distinct + order + neighbor. Jangan jika hanya “pernah muncul?” pada kunci 0..1e6 — array `bool` lebih cepat. Jangan jika butuh duplikat — `multiset`.

**Proses:** Sisip `4, 1, 4, 3`.

| Operasi | Isi set | Keterangan |
| --- | --- | --- |
| insert 4 | `{4}` | baru |
| insert 1 | `{1,4}` | urut otomatis |
| insert 4 | `{1,4}` | ditolak |
| insert 3 | `{1,3,4}` | di tengah |
| begin / rbegin | 1 / 4 | ekstrem O(1) |

1. `4` masuk.
2. `1` masuk di kiri.
3. `4` kedua ditolak.
4. `3` masuk di tengah.
5. `s.count(4) = 1` selalu 0 atau 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int banyakUnik(const vector<ll>& a) {
    set<ll> s;
    for (ll x : a) s.insert(x);
    return (int)s.size();
}

int main() {
    FASTIO;
    vector<ll> a = {4, 1, 4, 3};
    cout << banyakUnik(a) << '\n'; // 3
    set<ll> s(a.begin(), a.end());
    cout << *s.begin() << ' ' << *s.rbegin() << '\n'; // 1 4
    return 0;
}
```

**Jebakan:**
1. `*s.begin()` pada set kosong.
2. `erase(it++)` salah tulis lalu iterator invalid.
3. Mengira `count` di `set` bisa lebih dari 1.

**Kompleksitas:** tiap operasi O(log n), bangun dari n sisip O(n log n), memori O(n).

---

## Tetangga pada set

> **Ide satu kalimat:** `lower_bound` adalah orang pertama yang tidak lebih kecil dari x.

### Tetangga pada set

**Teori:** Analoginya rak kamus: kamu membuka halaman “paling dekat dari atas” untuk kata x. `lower_bound(x)` → pertama ≥ x. `upper_bound(x)` → pertama > x. Untuk “terbesar ≤ x”, mundur satu langkah dari `upper_bound`. Alasan benar: array terurut plus bound juga bisa, tetapi `set` tahan sisip dan hapus di tengah.

**Kapan:** Pakai “tiket terdekat”, “ceiling/floor”, dan successor. Jangan `--it` saat `it == begin()`. Jangan `*it` saat `it == end()`.

**Proses:** Set `{1,3,4}`, tanya tetangga 2.

| Pertanyaan | Iterator | Nilai |
| --- | --- | ---: |
| pertama ≥ 2 | lower_bound(2) | 3 |
| pertama > 2 | upper_bound(2) | 3 |
| terbesar ≤ 2 | --upper_bound(2) | 1 |
| pertama ≥ 5 | end() | tidak ada |

1. `lower_bound(2)` menunjuk 3.
2. Tidak ada 2 di set.
3. Floor 2 adalah 1.
4. Ceiling 4 adalah 4.
5. Ceiling 5 gagal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll tetanggaAtas(const set<ll>& s, ll x) {
    auto it = s.lower_bound(x);
    if (it == s.end()) return LLONG_MAX;
    return *it;
}

ll tetanggaBawah(const set<ll>& s, ll x) {
    auto it = s.upper_bound(x);
    if (it == s.begin()) return LLONG_MIN;
    --it;
    return *it;
}

int main() {
    FASTIO;
    set<ll> s = {1, 3, 4};
    cout << tetanggaAtas(s, 2) << '\n';  // 3
    cout << tetanggaBawah(s, 2) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `--begin()` pada set.
2. `*end()`.
3. Menggunakan `find` lalu `++it` tanpa cek apakah x ada.

**Kompleksitas:** O(log n) per pertanyaan, memori O(n).

---

## multiset

> **Ide satu kalimat:** `set` yang mengizinkan kembar, dan `erase(x)` bisa menghapus **semua** x.

### multiset

**Teori:** Analoginya gantungan tiket konser: boleh dua tiket harga sama. CSES Concert Tickets adalah contoh kanonik. `erase(x)` pada `multiset` menghapus **seluruh** nilai x. `erase(it)` menghapus satu. Alasan orang WA: mereka perlakukan seperti `set`. `lower_bound` tetap “pertama ≥”, `upper_bound` “pertama >”.

**Kapan:** Pakai kumpulan terurut berulang: tiket, sisa kapasitas, dua heap median (dengan `multiset`). Jangan `erase(nilai)` jika hanya ingin satu kemunculan.

**Proses:** Isi `5, 3, 5`. Hapus satu `5`.

1. Isi: `{3,5,5}`.
2. `erase(5)` (nilai) → `{3}` — kedua 5 hilang. Salah jika niat satu.
3. Benar: `auto it = ms.find(5); ms.erase(it);` → `{3,5}`.
4. `lower_bound(4)` menunjuk `5` yang tersisa.
5. Size 2.

| Operasi | Isi | size |
| --- | --- | ---: |
| insert 5,3,5 | `{3,5,5}` | 3 |
| erase(nilai 5) | `{3}` | 1 |
| erase(iterator 5) | `{3,5}` | 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void hapusSatu(multiset<ll>& ms, ll x) {
    auto it = ms.find(x);
    if (it != ms.end()) ms.erase(it);
}

ll tiketTidakMelebihi(multiset<ll>& ms, ll batas) {
    auto it = ms.upper_bound(batas);
    if (it == ms.begin()) return -1;
    --it;
    ll ans = *it;
    ms.erase(it);
    return ans;
}

int main() {
    FASTIO;
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
3. Menyimpan iterator lalu menghapus node itu, lalu memakai iterator lama.

**Kompleksitas:** O(log n) per operasi, memori O(n).

---

## map

> **Ide satu kalimat:** kamus terurut: kunci unik, nilai boleh apa saja, iterasi urut kunci.

### map

**Teori:** Analoginya laci berlabel nama, isinya jumlah stoples. `map<ll,ll> freq` adalah penghitung untuk nilai 10^9. `freq[x]++` membuat entri 0 lalu tambah jika belum ada. Alasan benar: kunci tidak harus rapat. `find` versus `[]`: `[]` **membuat** kunci. Iterasi `begin()` ke `end()` menaik menurut kunci.

**Kapan:** Pakai frekuensi nilai besar, memo kunci aneh, “first occurrence index”. Jangan `[]` hanya untuk cek keberadaan — itu menambah sampah 0. Untuk kunci 0..1e6 rapat, array lebih cepat.

**Proses:** Array `2, 3, 2, 2`.

| x | freq[2] | freq[3] | size |
| ---: | ---: | ---: | ---: |
| 2 | 1 | 0 | 1 |
| 3 | 1 | 1 | 2 |
| 2 | 2 | 1 | 2 |
| 2 | 3 | 1 | 2 |

1. Kunci terurut: 2 dulu, 3 kemudian.
2. `freq[5]` jika dipanggil jadi 0 dan **masuk** map.
3. `find(5)` tidak membuat entri.
4. Iterasi mencetak `2:3` lalu `3:1`.
5. Hapus kunci: `freq.erase(2)`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

map<ll, ll> frekuensi(const vector<ll>& a) {
    map<ll, ll> freq;
    for (ll x : a) freq[x]++;
    return freq;
}

bool adaKunci(const map<ll, ll>& freq, ll x) {
    return freq.find(x) != freq.end();
}

int main() {
    FASTIO;
    vector<ll> a = {2, 3, 2, 2};
    auto freq = frekuensi(a);
    cout << freq[2] << '\n'; // 3
    cout << (adaKunci(freq, 5) ? 1 : 0) << '\n'; // 0
    cout << freq.size() << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `if (freq[x])` membuat x.
2. Iterasi lalu `erase` tanpa `it = m.erase(it)`.
3. `map` O(log n) di dalam n=2e5 × log bisa ketat jika konstanta jelek.

**Kompleksitas:** akses/ubah O(log k), k = jumlah kunci, memori O(k).

---

## unordered_map

> **Ide satu kalimat:** kamus cepat rata-rata, tapi juri bisa membuatnya O(n) per operasi.

### unordered_map

**Teori:** Analoginya locker berdasarkan hash nomor tas: rata-rata langsung, tapi jika semua tas hash ke loker sama, antrean panjang. Codeforces klasik: anti-hash test pada `unordered_map<long long>`. Alasan `map` lebih aman: O(log n) terjamin. Jika tetap mau hash, pakai custom hash (splitmix). `reserve` mengurangi rehash.

**Kapan:** Pakai di AtCoder/CSES jika perlu kecepatan dan kunci banyak. Di Codeforces, `map` atau custom hash. Jangan untuk kunci yang perlu diiterasi terurut.

**Proses:** Hitung berapa pasangan jumlah = 5 pada `[1,4,3,2]`.

| i | x | cari 5-x | pasangan baru | freq setelah |
| ---: | ---: | ---: | ---: | --- |
| 0 | 1 | 4 belum | 0 | {1:1} |
| 1 | 4 | 1 ada | 1 | {1:1,4:1} |
| 2 | 3 | 2 belum | 1 | +3 |
| 3 | 2 | 3 ada | 2 | +2 |

1. Pasangan `(1,4)` dan `(3,2)`.
2. Total 2.
3. Urutan hash tidak terurut — jangan andalkan iterasi.
4. Tanpa custom hash, tes CF bisa TLE.
5. `[]` saat mencari pasangan membuat kunci palsu.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Kapan:** Pakai jika hanya butuh ekstrem berulang. Jangan jika butuh hapus sembarang kunci efisien — `multiset`. Jangan mengira `pq[i]` ada.

**Proses:** Push `2, 9, 4`.

| Operasi | top | Isi logis |
| --- | ---: | --- |
| push 2 | 2 | {2} |
| push 9 | 9 | {9,2} |
| push 4 | 9 | {9,4,2} |
| pop | 4 | {4,2} |
| pop | 2 | {2} |

1. Heap punya 2; top=2.
2. Masuk 9; top=9.
3. Masuk 4; top tetap 9.
4. `pop` buang 9; top=4.
5. Tidak ada cara melihat “ke-2 terbesar” tanpa pop.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Kapan:** Pakai jarak, merge k list, “k terkecil streaming”. Jangan campur `greater` dengan lambda terbalik sampai bingung sendiri.

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

## Lazy delete pada heap

> **Ide satu kalimat:** heap tidak bisa cabut nilai tengah; tandai “sudah mati”, buang saat muncul di puncak.

### Lazy delete pada heap

**Teori:** Analoginya papan antrian: nomor yang batal tetap tertulis, diabaikan saat dipanggil. Simpan `priority_queue` plus `map` hitung. Saat `top()` sudah dihapus, `pop` terus. Alasan benar: hapus sembarang di heap murni tidak ada; lazy membuat amortisasi O(log n). Alternatif lebih bersih: `multiset`.

**Kapan:** Pakai Dijkstra “decrease-key palsu”, median dua heap. Jangan jika hampir semua elemen dihapus sebelum dibaca — `multiset` lebih jujur.

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    ll top() {
        bersih();
        return pq.top();
    }
    bool empty() {
        bersih();
        return pq.empty();
    }
};

int main() {
    FASTIO;
    HeapLazy h;
    h.push(9);
    h.push(7);
    h.push(4);
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

## Dua heap untuk median

> **Ide satu kalimat:** max-heap menahan setengah kecil, min-heap menahan setengah besar.

### Dua heap untuk median

**Teori:** Analoginya kelas dibagi dua baris: baris kiri nilai kecil, baris kanan nilai besar, dan kedua ketua baris saling berdekatan. `low` (max-heap) menyimpan nilai ≤ median, `high` (min-heap) menyimpan nilai ≥ median. Invarian: `low.size()` sama atau satu lebih besar dari `high`. Median: `low.top()` jika ganjil, rata-rata kedua top jika genap. Alasan benar: sisip O(log n), median O(1), tanpa sort ulang.

**Kapan:** Pakai streaming median, CSES Sliding Median (plus hapus). Jangan jika n kecil dan sort tiap kali sudah cukup. Jangan lupa rebalance setelah tiap sisip.

**Proses:** Masuk `5, 2, 8`.

| x | low (max) | high (min) | median |
| ---: | --- | --- | ---: |
| 5 | {5} | {} | 5 |
| 2 | {2} | {5} | (2+5)/2 |
| 8 | {2,5} | {8} | 5 |

1. 5 masuk `low`.
2. 2 lebih kecil, `low` jadi {2}, 5 pindah ke `high` setelah rebalance.
3. 8 masuk `high`, lalu satu elemen pindah ke `low` agar selisih size ≤ 1.
4. Median 5.
5. Jika 1 masuk, `low={1,2}`, `high={5,8}`, median (2+5)/2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct MedianDuaHeap {
    priority_queue<ll> low;
    priority_queue<ll, vector<ll>, greater<ll>> high;
    void rebalance() {
        if (low.size() > high.size() + 1) {
            high.push(low.top());
            low.pop();
        } else if (high.size() > low.size()) {
            low.push(high.top());
            high.pop();
        }
    }
    void sisip(ll x) {
        if (low.empty() || x <= low.top()) low.push(x);
        else high.push(x);
        rebalance();
    }
    ll median() { return low.top(); }
};

int main() {
    FASTIO;
    MedianDuaHeap m;
    m.sisip(5);
    m.sisip(2);
    m.sisip(8);
    cout << m.median() << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Tidak rebalance — size timpang, median salah.
2. Membandingkan ke `low.top()` saat `low` kosong.
3. Median genap: soal kadang minta yang lebih kecil, bukan rata-rata.

**Kompleksitas:** sisip O(log n), baca median O(1), memori O(n).

---

## Memilih set map atau heap

> **Ide satu kalimat:** “tetangga”, “kamus”, dan “puncak” tidak bisa diganti satu sama lain.

### Memilih set map atau heap

**Teori:** Analoginya tiga laci di meja juri. `set` menjawab “siapa tetangga x”. `map` menjawab “nilai untuk kunci x”. Heap menjawab “siapa terbesar sekarang”. Alasan salah pilih klasik: memakai heap untuk tiket ≤ harga, atau memakai `set` hanya untuk frekuensi tanpa butuh urutan.

**Kapan:** Pakai tabel ini di menit pertama. Jangan `set` untuk frekuensi (kehilangan jumlah). Jangan heap jika kamu harus hapus nilai tengah sering.

| Pertanyaan soal | Alat |
| --- | --- |
| Unik + tetangga | `set` |
| Tiket kembar + ceiling | `multiset` |
| Kunci → nilai / frekuensi besar | `map` |
| Frekuensi cepat, tidak terurut | hash aman |
| Selalu max/min | `priority_queue` |
| Hapus tengah + ekstrem | `multiset` |
| Median streaming | dua heap |

**Proses:** Soal: n=2e5, berulang “hapus satu tiket ≤ harga”.

1. Vector + scan = O(n) per query → TLE.
2. `set` menolak duplikat harga.
3. `multiset` + `upper_bound` + hapus iterator — pas.
4. Heap tidak bisa hapus “terdekat ≤”.
5. Keputusan: `multiset`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string pilihKotak(const string& butuh) {
    if (butuh == "unik terurut") return "set";
    if (butuh == "duplikat terurut") return "multiset";
    if (butuh == "kunci ke nilai") return "map";
    if (butuh == "ekstrem berulang") return "priority_queue";
    if (butuh == "median streaming") return "dua heap";
    return "baca ulang soalnya";
}

int main() {
    FASTIO;
    cout << pilihKotak("duplikat terurut") << '\n';
    cout << pilihKotak("ekstrem berulang") << '\n';
    return 0;
}
```

**Jebakan:**
1. `set` untuk frekuensi — kehilangan jumlah.
2. `map<int,int>` untuk 0..n-1.
3. Heap + “cari nilai x” tiap query.

**Kompleksitas:** keputusan O(1); eksekusi mengikuti kotak.

---

## Ringkasan

- `set` unik; `multiset.erase(x)` menghapus semua x.
- `map[]` membuat kunci; `find` tidak.
- Hash default di CF berbahaya.
- Heap hanya ekstrem; hapus tengah = `multiset` atau lazy delete.
- Median streaming: max-heap kiri + min-heap kanan.

Lanjut: [algoritma STL](algoritma-stl.md).
