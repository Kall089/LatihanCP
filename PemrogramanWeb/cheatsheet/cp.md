# Cheatsheet Competitive Programming (peta cepat)

[← Daftar panduan](README.md) · [**Folder lengkap `cp/`**](cp/README.md) · [**DP**](cp/09-dp/README.md)

Ini peta satu halaman. Materi lengkap (teori + proses + fungsi modular) ada di folder **[`cp/`](cp/README.md)**. Dynamic programming: **[`cp/09-dp/`](cp/09-dp/README.md)** (27 file, Day 141–168 / 244 / 248).

Latihan harian tetap di `KULIAH/ComprogLearning/CP`. Jangan menyalin ~2500 file itu ke sini.

## Daftar isi

- [Cara memakai peta ini](#cara-memakai-peta-ini)
- [Peta materi](#peta-materi)
- [Kerangka program](#kerangka-program)
- [Kompleksitas](#kompleksitas)
- [STL](#stl)
- [Prefix, beda, dan jendela](#prefix-beda-dan-jendela)
- [Greedy](#greedy)
- [Graf](#graf)
- [Dynamic programming](#dynamic-programming)
- [Segment tree](#segment-tree)
- [String](#string)
- [Pilih senjata dari batasan](#pilih-senjata-dari-batasan)
- [Kesalahan umum](#kesalahan-umum)

## Cara memakai peta ini

**Untuk apa:** membuka satu teknik, menyalin **satu fungsi modular**, lalu menguji dengan angka kecil sebelum menempelkannya ke `main`.

Urutan belajar yang sama dengan deck di `KULIAH/ComprogLearning/CP`:

1. Fondasi: kompleksitas, STL, prefix, two pointers, greedy.
2. Alat kerja: teori bilangan ringan, BFS/DFS, Dijkstra, DSU, MST.
3. DP: 1D, knapsack, LCS, bitmask, pohon.
4. Struktur data: Fenwick, segtree, lazy.
5. String dan graf lanjut sesuai kebutuhan soal.

**Contoh implementasi:** buka [DAFTAR-MATERI.md](../../ComprogLearning/CP/DAFTAR-MATERI.md) di folder latihan, pilih Day yang namanya cocok (misalnya Day-029 Prefix Sum), kerjakan `latihan/`, baru bandingkan `solusi/` jika macet.

**Biasanya digabungkan dengan:** satu file `template.cpp`, plus ensiklopedia untuk teori yang lebih panjang.

## Peta materi

Kolom **Day** merujuk folder di `KULIAH/ComprogLearning/CP`. Kolom ensiklopedia merujuk bab di `cheatsheet/ensiklopedia/cp/` bila sudah ada.

| Kategori | Isi yang sering keluar | Day acuan | Fungsi di bawah |
|---|---|---|---|
| Kompleksitas | Big-O, baca `n` dan waktu | 015 | `muat_waktu` |
| STL | `vector`, `set`, `map`, `sort`, `lower_bound` | 018–026 | `ada_setelah_urut` |
| Prefix | jumlah rentang, difference array | 029–038 | `jumlah_rentang` |
| Greedy | interval, tukar argumen | 071–075 | `banyak_interval` |
| Graf | BFS, DFS, Dijkstra, DSU | 113–136 | `jarak_bfs` |
| DP | submasalah, knapsack, LCS | 141–168 | `knapsack_01` |
| Segtree | query/update rentang | 169–176 | `SegTree::query` |
| String | hash, KMP, Z, trie | 211–223 | `prefix_kmp` |

Pendukung tanpa fungsi sendiri: binary search on answer (Day-048), two pointers (032), DSU/MST (134/136), Fenwick (170), LCA (201). Definisi panjang: [ensiklopedia/cp/README.md](ensiklopedia/cp/README.md).

## Kerangka program

**Untuk apa:** I/O cepat dan `main` yang hanya membaca, memanggil fungsi, lalu menulis jawaban.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // long long ans = fungsi_modular(a);
    // cout << ans << '\n';
    return 0;
}
```

`bits/stdc++.h` nyaman di GCC/kontes. Di tugas kuliah yang menuntut header resmi, tulis `#include` satu-satu. `ios::sync_with_stdio(false)` memutus sinkron dengan `printf`; jangan campur `cin` dan `scanf`.

**Contoh implementasi:** salin kerangka ke `KULIAH/ComprogLearning/CP/_template.cpp`, lalu tiap hari hanya menambah fungsi baru di atas `main`.

**Biasanya digabungkan dengan:** fungsi modular di bagian berikut, bukan logika panjang di dalam `main`.

## Kompleksitas

**Untuk apa:** menolak algoritma yang tidak muat **sebelum** mengetik loop bersarang.

Aturan kasar: 1 detik ≈ `10^8` operasi sederhana. Jika `n = 2·10^5` dan waktu 1 detik, `O(n^2)` hampir pasti TLE, `O(n log n)` biasanya aman.

```cpp
// n, batas_ops: perkiraan operasi yang masih muat.
bool muat_waktu(long long n, long long pangkat, long long batas_ops = 100000000LL) {
    long long ops = 1;
    for (long long i = 0; i < pangkat; ++i) {
        if (ops > batas_ops / max(1LL, n)) return false;
        ops *= n;
    }
    return ops <= batas_ops;
}
```

Tabel baca batasan (satu tes, 1 detik):

| n sampai | yang biasanya muat | yang biasanya tidak |
|---|---|---|
| `20` | `O(2^n · n)`, backtrack | `O(n!)` tanpa potong |
| `100` | `O(n^3)`, Floyd, DP berat | `O(n^4)` |
| `400` | `O(n^2)` longgar | `O(n^3)` ketat |
| `2·10^3` | `O(n^2)` | `O(n^3)` |
| `1·10^5` | `O(n log n)`, `O(n √n)` hati-hati | `O(n^2)` |
| `1·10^6` | `O(n)` / `O(n log n)` ramping | `O(n log^2 n)` berat |
| `1·10^18` | `O(log n)`, rumus, matriks | loop linear |

Memori: array `int` berukuran `n` ≈ `4n` byte. `2·10^5` `long long` ≈ 1,6 MB. Array 2D `dp[n][n]` dengan `n = 5000` sudah ≈ 100 MB jika `int`.

**Contoh implementasi:** soal `n ≤ 1e5`, `q ≤ 1e5`, jumlah rentang. `muat_waktu` menolak `pangkat = 2`. Pilih prefix `O(n + q)`, bukan loop `l..r` per query.

**Yang terjadi:** kamu membuang solusi `O(nq)` di kertas, bukan setelah 10 menit koding.

**Biasanya digabungkan dengan:** peta di [Pilih senjata dari batasan](#pilih-senjata-dari-batasan). Teori lintas bahasa: [teori-fondasi.md](ensiklopedia/teori-fondasi.md).

## STL

**Untuk apa:** memakai kontainer dan algoritma pustaka supaya tidak menulis urut/cari manual yang rawan off-by-one.

```cpp
// a harus sudah terurut menaik.
bool ada_setelah_urut(const vector<int>& a, int x) {
    return binary_search(a.begin(), a.end(), x);
}
```

Peta kontainer singkat:

| Butuh | Pakai | Jangan |
|---|---|---|
| daftar dinamis | `vector<T>` | array C mentah kecuali `n` tetap |
| cek ada, unik, terurut | `set<T>` | `vector` + `find` berulang |
| kunci → nilai, terurut | `map<K,V>` | dua `vector` yang harus sinkron |
| kunci → nilai, cepat | `unordered_map` | jika butuh urutan atau anti-hash |
| ambil min/maks berulang | `priority_queue` | `sort` ulang tiap langkah |
| antrian BFS | `queue` | `vector` + hapus depan `O(n)` |

`sort` `O(n log n)`. `lower_bound` hanya pada data terurut. Comparator irrefleksif: `comp(x, x) == false`. `pair` diurut kunci pertama, lalu kedua.

**Contoh implementasi:** baca `n` angka, `sort`, lalu untuk tiap query `x` panggil `ada_setelah_urut`. Ini pola Day-025.

**Yang terjadi:** pencarian per query `O(log n)`, bukan `O(n)`.

**Biasanya digabungkan dengan:** prefix setelah diurut, greedy interval, dan binary search on answer. STL lengkap: ensiklopedia C++ [03–05](ensiklopedia/cpp/README.md) plus [ensiklopedia CP](ensiklopedia/cp/README.md).

## Prefix, beda, dan jendela

**Untuk apa:** mengubah query jumlah/selisih rentang menjadi `O(1)` setelah praproses `O(n)`.

```cpp
vector<long long> buat_prefix(const vector<long long>& a) {
    vector<long long> pref(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); ++i) pref[i + 1] = pref[i] + a[i];
    return pref;
}

// l, r inklusif, 0-based. pref.size() == n + 1.
long long jumlah_rentang(const vector<long long>& pref, int l, int r) {
    return pref[r + 1] - pref[l];
}
```

Difference array: update `+x` pada `[l, r]` jadi `d[l] += x`, `d[r+1] -= x`, lalu prefix-kan `d` untuk dapat array akhir.

Two pointers: dua indeks hanya maju, sehingga `O(n)` menggantikan `O(n^2)` saat syarat monoton (jumlah membesar jika jendela membesar).

```cpp
// terpendek [l, r] agar jumlah >= s; -1 jika mustahil.
int jendela_terpendek(const vector<long long>& a, long long s) {
    int n = int(a.size()), kanan = 0, jawab = n + 1;
    long long jumlah = 0;
    for (int kiri = 0; kiri < n; ++kiri) {
        while (kanan < n && jumlah < s) jumlah += a[kanan++];
        if (jumlah >= s) jawab = min(jawab, kanan - kiri);
        jumlah -= a[kiri];
    }
    return jawab == n + 1 ? -1 : jawab;
}
```

**Contoh implementasi:** `a = {1, 2, 3, 4}`, `pref = {0, 1, 3, 6, 10}`, `jumlah_rentang(pref, 1, 3) == 9`.

**Yang terjadi:** empat query jumlah tidak mengulang penjumlahan elemen yang sama.

**Biasanya digabungkan dengan:** binary search on prefix, Kadane (Day-035), dan Fenwick jika ada update.

## Greedy

**Untuk apa:** mengambil pilihan lokal yang bisa dibuktikan tidak merusak jawaban global. Jika bukti gagal, pindah ke DP.

```cpp
// Interval [mulai, akhir). Ambil sebanyak mungkin yang tidak tabrakan.
int banyak_interval(vector<pair<int,int>> interval) {
    sort(interval.begin(), interval.end(),
         [](const auto& p, const auto& q) { return p.second < q.second; });
    int ambil = 0, selesai = INT_MIN;
    for (auto [l, r] : interval) {
        if (l >= selesai) {
            ++ambil;
            selesai = r;
        }
    }
    return ambil;
}
```

Pola greedy yang sering aman:

- Urut akhir interval, ambil yang selesai paling cepat.
- Urut nilai, ambil terbesar yang masih muat kapasitas (hanya jika bukti exchange berlaku).
- Huffman / gabung dua terkecil — antrean prioritas.

Pola yang sering **salah** dianggap greedy: knapsack 0-1, LCS, jalur terpendek dengan bobot negatif, dan “ambil terbesar dulu” tanpa bukti.

**Contoh implementasi:** interval `(1,4), (3,5), (0,6), (5,7)` → urut akhir → ambil `(1,4)` lalu `(5,7)` → `2`.

**Yang terjadi:** menukar pilihan “selesai lebih lambat” dengan yang lebih cepat tidak mengurangi jumlah yang bisa diambil (exchange argument, Day-072).

**Biasanya digabungkan dengan:** `sort` + `priority_queue`. Jika pilihan sekarang memengaruhi sisa secara tidak monoton, tulis DP.

## Graf

**Untuk apa:** memodelkan hubungan (kota, prasyarat, grid) lalu menelusuri tetangga, bukan mengarang loop 2D sembarangan.

```cpp
vector<int> jarak_bfs(const vector<vector<int>>& g, int sumber) {
    int n = int(g.size());
    vector<int> dist(n, -1);
    queue<int> q;
    dist[sumber] = 0;
    q.push(sumber);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}
```

Pilih penelusuran:

| Soal | Alat | Catatan |
|---|---|---|
| terhubung? komponen? | DFS / BFS | grid = graf implisit 4 arah |
| jarak sisi sama 1 | BFS | `jarak_bfs` |
| jarak bobot ≥ 0 | Dijkstra | `priority_queue` + `dist` |
| bobot negatif | Bellman-Ford | deteksi siklus negatif |
| semua pasangan, `n ≤ 400` | Floyd-Warshall | `O(n^3)` |
| gabung himpunan | DSU | Kruskal, komponen dinamis |
| prasyarat kuliah | topo sort | siklus = mustahil |

Representasi: `vector<vector<int>> g(n)` untuk tak berarah (tambah dua sisi) atau berarah (satu sisi). Jangan memakai matriks `n×n` jika `n = 1e5`.

**Contoh implementasi:** `g = {{1},{0,2},{1}}`, `jarak_bfs(g, 0)` → `{0, 1, 2}`.

**Yang terjadi:** tiap simpul masuk antrean sekali, jadi `O(n + m)`.

**Biasanya digabungkan dengan:** DP pada DAG setelah topo sort, dan DSU untuk MST. Deck graf: Day-113 dan seterusnya di `KULIAH/ComprogLearning/CP`.

## Dynamic programming

**Untuk apa:** mengingat jawaban submasalah yang overlap, supaya rekursi tidak mengulang kerja yang sama.

Tiga pertanyaan wajib sebelum menulis kode:

1. **State** — apa yang sudah diputuskan? (indeks, sisa kapasitas, bitmask)
2. **Transisi** — dari state itu, pilihan apa yang sah?
3. **Dasar** — state kosong / penuh nilainya berapa?

```cpp
// Nilai maksimum, tiap barang sekali. w[i], v[i], kapasitas W.
long long knapsack_01(const vector<int>& w, const vector<long long>& v, int W) {
    vector<long long> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); ++i) {
        for (int sisa = W; sisa >= w[i]; --sisa) {
            dp[sisa] = max(dp[sisa], dp[sisa - w[i]] + v[i]);
        }
    }
    return dp[W];
}
```

Loop kapasitas **mundur** agar tiap barang dipakai paling banyak sekali. Mundur → 0-1. Maju → unbounded (koin boleh berulang).

Peta DP singkat:

| Nama | State kasar | Waktu |
|---|---|---|
| tangga / Kadane | `dp[i]` | `O(n)` |
| 0-1 knapsack | `dp[i][w]` atau 1D mundur | `O(nW)` |
| LCS / edit | `dp[i][j]` dua string | `O(nm)` |
| LIS | `tails` + `lower_bound` | `O(n log n)` |
| bitmask / TSP | `dp[mask][v]` | `O(2^n · n^2)` |
| digit DP | posisi, ketat, leading | `O(digit · state)` |

**Contoh implementasi:** `w = {2, 3, 3}`, `v = {3, 4, 5}`, `W = 5` → `knapsack_01` mengembalikan `8` (barang 2+3 atau 2+3).

**Yang terjadi:** `dp[sisa]` hanya melihat versi **sebelum** barang `i` dipakai, karena update dari kanan ke kiri.

**Biasanya digabungkan dengan:** rekonstruksi jalur (simpan `prev`), dan greedy jika bukti “ambil lokal” sudah ada. Prinsip: Day-141 di folder latihan.

## Segment tree

**Untuk apa:** query agregat rentang **dan** update titik/rentang, keduanya `O(log n)`, saat prefix biasa sudah tidak cukup.

```cpp
struct SegTree {
    int n;
    vector<long long> t;

    explicit SegTree(int n_) : n(n_), t(4 * n_, 0) {}

    void build(const vector<long long>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, v * 2, l, m);
        build(a, v * 2 + 1, m + 1, r);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    void update(int v, int l, int r, int pos, long long val) {
        if (l == r) {
            t[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) update(v * 2, l, m, pos, val);
        else update(v * 2 + 1, m + 1, r, pos, val);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    long long query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return query(v * 2, l, m, ql, qr) + query(v * 2 + 1, m + 1, r, ql, qr);
    }
};
```

Pakai `build(a, 1, 0, n-1)`, `update(1, 0, n-1, pos, val)`, `query(1, 0, n-1, L, R)` dengan `L,R` inklusif 0-based.

Kapan **jangan** segtree:

- Data tetap, hanya min/max/gcd rentang → Sparse Table `O(1)` query (Day-169).
- Hanya prefix + update titik → Fenwick lebih pendek (Day-170).
- Hanya jumlah rentang **tanpa update** → prefix.

Lazy propagation (Day-176) perlu jika update juga berupa rentang.

**Contoh implementasi:** `a = {1, 2, 3, 4}`, `query` `[1, 2]` → `5`. `update` indeks `1` jadi `10`, query yang sama → `13`.

**Yang terjadi:** pohon menyimpan jumlah anak; update hanya menyentuh `O(log n)` simpul dari daun ke akar.

**Biasanya digabungkan dengan:** kompresi koordinat (Day-038) jika nilai besar tetapi `n` kecil.

## String

**Untuk apa:** membandingkan potongan, mencari pola, atau menghitung palindrom tanpa `O(n^2)` naif.

```cpp
// prefix[i] = panjang border terpanjang untuk s[0..i].
vector<int> prefix_kmp(const string& s) {
    int n = int(s.size());
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int hitung_pola(const string& teks, const string& pola) {
    string t = pola + '#' + teks;
    auto pi = prefix_kmp(t);
    int m = int(pola.size()), cnt = 0;
    for (int x : pi) if (x == m) ++cnt;
    return cnt;
}
```

Alat string lain (buka ensiklopedia / Day terkait, jangan disalin semua file latihan):

| Alat | Day | Kapan |
|---|---|---|
| hashing 1/2 modulus | 211 | banding substring `O(1)` |
| KMP / prefix function | 213 | cari pola, border, periode |
| Z-function, Manacher | 215 | prefix, palindrom |
| Trie / binary trie | 217 | kamus, XOR maksimum |
| Suffix array + LCP | 219 | substring berulang |
| Aho-Corasick | 221 | banyak pola sekaligus |

Hashing: pilih basis ganjil dan modulus prima; untuk anti-hack, dua modulus atau `unsigned long long` plus modulus.

**Contoh implementasi:** `hitung_pola("ababab", "ab")` → `3`.

**Yang terjadi:** prefix function melompat ke border yang sudah diketahui, jadi tiap indeks maju-mundur amortisasi `O(n)`.

**Biasanya digabungkan dengan:** binary search pada panjang substring + hash, atau DP pada string (LCS, edit distance).

## Pilih senjata dari batasan

**Untuk apa:** memutuskan kategori **dari `n`, `q`, dan kalimat soal**, bukan dari intuisi “ini kayaknya DP”.

```text
n <= 20                  → bitmask / backtrack
n <= 400, semua pasangan → Floyd / DP n^3
n <= 2000                → O(n^2) DP atau prefix 2D
n, q ~ 1e5, data tetap   → prefix / sparse table
n, q ~ 1e5, ada update   → Fenwick / segtree
graf, sisi = 1           → BFS
graf, bobot >= 0         → Dijkstra
"sebanyak mungkin interval" → greedy urut akhir
"nilai maksimum knapsack" → DP, bukan greedy
substring / pola         → KMP atau hash, bukan find O(n^2)
```

Kalimat pemicu: jumlah `l..r` berkali-kali → prefix/pohon; ada update → Fenwick/segtree; jarak terpendek → BFS/Dijkstra (DP hanya DAG); ambil-atau-tidak → knapsack 0-1; koin tak terbatas → unbounded; susun ulang → greedy berbukti atau DP.

**Contoh implementasi:** `n = 1e5`, `q = 1e5`, “ganti `a[i]`, lalu jumlah `l..r`”. Pilih `SegTree`, bukan `jumlah_rentang` prefix statis.

**Yang terjadi:** kamu membuka Day yang tepat di `KULIAH/ComprogLearning/CP` alih-alih mengacak 2500 file.

**Biasanya digabungkan dengan:** [muat_waktu](#kompleksitas) di kertas 30 detik pertama.

## Kesalahan umum

**Untuk apa:** menandai bug yang memakan waktu kontes lebih dari algoritma itu sendiri.

```cpp
// 1) overflow: n * n untuk n = 1e5 tidak muat di int.
long long n2 = 1LL * n * n;

// 2) modulo negatif di C++.
long long mod_norm(long long x, long long MOD) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

// 3) BFS tanpa penanda: simpul masuk antrean berkali-kali.
//    Set dist[v] saat push, bukan saat pop.

// 4) lower_bound pada vector yang belum di-sort.

// 5) DP knapsack 0-1 di-loop maju → barang terpakai berulang.
```

Daftar cepat lain:

- Indeks 1-based di soal, 0-based di `vector` — samakan di satu tempat.
- `endl` flush tiap baris; pakai `'\n'`.
- Recursion DFS pada `n = 1e5` bisa stack overflow; tulis iteratif atau `vector` sebagai tumpukan.
- `unordered_map` bisa diserang hash; siapkan `map` atau custom hash.
- Membaca seluruh `KULIAH/ComprogLearning/CP` sekaligus tidak membantu; ikut satu Day, kerjakan `latihan/`, baru `tugas/`.

**Contoh implementasi:** tes `mod_norm(-1, 1e9+7)` harus `1000000006`, bukan `-1`.

**Yang terjadi:** WA pada kasus kecil yang bisa kamu buat sendiri, sebelum submit.

**Biasanya digabungkan dengan:** stress test (Day-250): solusi naif vs fungsi modular pada input acak.

---

Lanjut teori yang bolong di banyak bahasa (bukan hanya CP): [teori-fondasi.md](ensiklopedia/teori-fondasi.md). Lanjut katalog teknik: [ensiklopedia/cp/README.md](ensiklopedia/cp/README.md). Latihan harian: folder `KULIAH/ComprogLearning/CP`, jangan disalin ke sini.
