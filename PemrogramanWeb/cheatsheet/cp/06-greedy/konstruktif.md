# Algoritma konstruktif

[← README](README.md) · [Indeks CP](../README.md)

Soal konstruktif minta **objek**, bukan hanya angka: permutasi, matriks, pewarnaan, urutan operasi. Banyak jawaban benar, jadi membandingkan ke sampel tidak cukup. Tulis **pemeriksa** dulu. Banyak konstruksi adalah greedy yang membangun objek; kalau pilihan lokal menutup semua objek sah, itu alarm DP atau brute.

Day terkait: **075**. Pasangkan dengan [kapan-dp.md](kapan-dp.md) saat “bangun optimal” ternyata butuh state, dan dengan [interval-exchange.md](interval-exchange.md) saat objeknya jadwal.

## Daftar isi

- [Pemeriksa lebih dulu](#pemeriksa-lebih-dulu)
- [Pola dari n kecil](#pola-dari-n-kecil)
- [Geser siklik dan derangement](#geser-siklik-dan-derangement)
- [Ganjil-genap dan titik sambung](#ganjil-genap-dan-titik-sambung)
- [Invariant dan paritas](#invariant-dan-paritas)
- [Konstruksi versus DP](#konstruksi-versus-dp)
- [Huffman sebagai konstruktif](#huffman-sebagai-konstruktif)
- [Stress n kecil](#stress-n-kecil)
- [Peta keputusan](#peta-keputusan)

---

## Pemeriksa lebih dulu

**Teori:** Analoginya merakit furniture: cek “semua lubang terisi” sebelum memamerkan lemari. Pemeriksa menguji ukuran, rentang, keunikan, dan syarat khusus. Alasan benar: konstruksi bisa terlihat rapi di `n = 5` lalu duplikat di `n = 6`. Tanpa pemeriksa, kamu men-debug mata.

**Kapan:** setiap soal “construct / any permutation / print a sequence / yes and give example”. Jangan mengoptimalkan jika soal hanya minta salah satu yang sah. Jangan klaim `-1` tanpa menguji `n` kecil dengan brute.

**Proses:** syarat “permutasi `1..n`”.

1. Panjang harus `n`.
2. Setiap nilai di `[1, n]`.
3. Tidak ada duplikat.
4. Syarat tambahan soal, misalnya selisih tetangga bukan 1.
5. Kalau gagal, cetak kasus sebelum submit.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool permutasi_1_n(const vector<int>& a, int n) {
    if ((int)a.size() != n) return false;
    vector<int> ada(n + 1, 0);
    for (int x : a) {
        if (x < 1 || x > n || ada[x]) return false;
        ada[x] = 1;
    }
    return true;
}

int main() {
    FASTIO;
    cout << permutasi_1_n({2, 4, 1, 3}, 4) << '\n'; // 1
    cout << permutasi_1_n({2, 4, 1, 1}, 4) << '\n'; // 0
    cout << permutasi_1_n({1, 2, 3}, 4) << '\n';    // 0
    return 0;
}
```

**Jebakan:**
1. Pemeriksa 1-based padahal array 0-based berisi `0..n-1`.
2. Lupa cek duplikat.
3. Memeriksa hanya sampel resmi.

**Kompleksitas:** pemeriksa biasanya `O(n)`.

---

## Pola dari n kecil

**Teori:** Cetak semua objek sah untuk `n = 1..8` dengan brute, lalu baca polanya. Analoginya melihat deret angka sebelum menebak rumus. Alasan benar: titik sambung (`n` genap/ganjil, `n = 2,3,4`) sering merusak rumus yang “hampir selalu” jalan.

**Kapan:** syarat lokal sederhana, ruang `n!` atau `2^n` masih hidup. Jangan brute `n = 12` permutasi. Jangan menggeneralisasi dari tiga nilai `n` yang semuanya ganjil.

**Proses:** susun `1..n` supaya `|a[i]-a[i+1]| != 1`.

Coba ganjil dulu lalu genap:

```text
n=5: 1 3 5 2 4     selisih 2,2,3,2  OK
n=4: 1 3 2 4       3-2=1  GAGAL
```

Satu nilai `n` merusak pola. Genap dulu lalu ganjil:

```text
n=4: 2 4 1 3       selisih 2,3,2  OK
n=5: 2 4 1 3 5     OK
n=2: 1 2           mustahil
n=3: semua permutasi punya tetangga selisih 1
```

Mustahil: `n = 2, 3`. Untuk `n >= 4` genap-lalu-ganjil, titik sambung genap terbesar ke 1: selisih `>= 3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool sah_tidak_tetangga(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> ada(n + 1, 0);
    for (int x : a) {
        if (x < 1 || x > n || ada[x]) return false;
        ada[x] = 1;
    }
    for (int i = 0; i + 1 < n; i++)
        if (abs(a[i] - a[i + 1]) == 1) return false;
    return true;
}

vector<int> konstruk_tidak_tetangga(int n) {
    if (n == 1) return {1};
    if (n == 2 || n == 3) return {};
    vector<int> a;
    for (int x = 2; x <= n; x += 2) a.push_back(x);
    for (int x = 1; x <= n; x += 2) a.push_back(x);
    return a;
}

int main() {
    FASTIO;
    for (int n = 1; n <= 8; n++) {
        auto a = konstruk_tidak_tetangga(n);
        cout << n << ": ";
        if (a.empty() && n != 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (int x : a) cout << x << ' ';
        cout << " cek=" << sah_tidak_tetangga(a) << '\n';
    }
    return 0;
}
```

**Jebakan:**
1. Menguji 3 nilai `n` lalu submit.
2. Klaim mustahil padahal `n = 1` trivial.
3. Mencetak `n` elemen 1-based padahal loop `0..n-2`.

**Kompleksitas:** konstruksi `O(n)`, pemeriksa `O(n)`.

---

## Geser siklik dan derangement

**Teori:** Derangement adalah permutasi tanpa titik tetap: `a[i] != i`. Geser `2,3,...,n,1` (1-based) bekerja untuk `n >= 2`. Analoginya semua orang memberi hadiah ke tetangga kanan. Alasan benar: `i` mendapat `i+1`, `n` mendapat `1`, tidak ada yang mendapat dirinya.

**Kapan:** “any derangement”, “no element in place”. Jangan untuk `n = 1` jika 1-based `a[1]=1` wajib titik tetap. Jangan mengira ini satu-satunya derangement: soal “any” cukup satu.

Greedy “taruh `i+1` jika belum dipakai” mirip geser, tetapi bisa macet di akhir jika kamu sudah memakai `n` terlalu awal. DP menghitung **jumlah** derangement `!n = (n-1) [!(n-1)+!(n-2)]`. Kalau soal minta jumlah, itu DP, bukan konstruktif.

**Proses:**

1. `n = 5`: `2 3 4 5 1`. Cek `2!=1, 3!=2, 4!=3, 5!=4, 1!=5`.
2. `n = 2`: `2 1`.
3. `n = 1`: mustahil jika indeks 1 harus `!= 1`.
4. Swap acak berpasangan juga jalan untuk `n` genap: `2 1 4 3`.
5. `n` ganjil: pasangan plus geser sisa.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> derange_geser(int n) {
    if (n == 1) return {};
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = (i + 1) % n + 1; // 1-based nilai
    return a;
}

bool sah_derange(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> ada(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (a[i] < 1 || a[i] > n || ada[a[i]] || a[i] == i + 1) return false;
        ada[a[i]] = 1;
    }
    return true;
}

ll hitung_derange(int n) { // DP jumlah, bukan konstruksi
    if (n == 0) return 1;
    if (n == 1) return 0;
    ll a = 1, b = 0; // !0, !1
    for (int i = 2; i <= n; i++) {
        ll c = (i - 1) * (b + a);
        a = b;
        b = c;
    }
    return b;
}

int main() {
    FASTIO;
    auto a = derange_geser(5);
    for (int x : a) cout << x << ' ';
    cout << " cek=" << sah_derange(a) << '\n';
    cout << hitung_derange(5) << '\n'; // 44, banyak objek; kita hanya cetak satu
    return 0;
}
```

**Jebakan:**
1. Indeks 0-based `a[i] != i` versus 1-based `a[i] != i+1`.
2. Mengirim DP jumlah saat soal minta permutasi.
3. `n = 1` tidak ditangani.

**Kompleksitas:** konstruksi `O(n)`. DP jumlah `O(n)`.

---

## Ganjil-genap dan titik sambung

**Teori:** Banyak syarat selisih, pewarnaan, atau paritas dipecah: tulis semua genap, lalu semua ganjil, atau sebaliknya. Titik **sambung** di tengah adalah tempat rumus paling sering gagal. Analoginya dua antrian yang digabung: masalahnya antrean terakhir kiri dan pertama kanan.

**Kapan:** syarat `|a[i]-a[i+1]|` besar, pewarnaan selang-seling, konstruksi array “tidak ada 3 AP”. Jangan meniru pola `n` ganjil untuk `n` genap tanpa cek sambung.

**Proses:** pewarnaan `1..n` selang-seling paritas sudah otomatis jika kamu menulis ganjil-genap, tetapi syarat tambahan “jumlah berurutan bukan kuadrat” butuh cek titik sambung.

Contoh titik sambung `n = 4` pola ganjil-genap `1 3 2 4`: `3-2 = 1` gagal jika selisih 1 dilarang. Tukar menjadi `2 4 1 3`.

Tabel pola yang sering:

| pola | contoh | rawan |
| --- | --- | --- |
| geser siklik | `2,3,...,n,1` | `n=1` |
| belah ganjil/genap | selisih, warna | titik sambung |
| ekstrem dulu | `n,1,n-1,2,...` | tengah |
| induk + sisipan | bangun `n` dari `n-1` | posisi sisip |
| semua sama | jika syarat izinkan | bound |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> ekstrem_dulu(int n) {
    vector<int> a;
    int l = 1, r = n;
    while (l <= r) {
        a.push_back(r--);
        if (l <= r) a.push_back(l++);
    }
    return a;
}

int min_selisih(const vector<int>& a) {
    int m = INT_MAX;
    for (int i = 0; i + 1 < (int)a.size(); i++)
        m = min(m, abs(a[i] - a[i + 1]));
    return m;
}

int main() {
    FASTIO;
    for (int n = 1; n <= 6; n++) {
        auto a = ekstrem_dulu(n);
        cout << n << ": ";
        for (int x : a) cout << x << ' ';
        cout << " minΔ=" << min_selisih(a) << '\n';
    }
    return 0;
}
```

`n = 4`: `4 1 3 2`, `minΔ = 1` di ujung. Pola ekstrem tidak menyelesaikan syarat “selisih bukan 1”. Itu pelajaran: pola cantik ≠ syarat terpenuhi.

**Jebakan:**
1. Memakai ekstrem dulu untuk semua soal permutasi.
2. Tidak menguji `n` genap dan ganjil.
3. Titik sambung hanya dicek di kepala.

**Kompleksitas:** `O(n)`.

---

## Invariant dan paritas

**Teori:** Invariant adalah besaran yang **tidak berubah** oleh operasi soal. Jika target beda invariant dengan awal, mustahil. Yang paling sering: paritas jumlah, paritas jumlah tukar, warna papan, jumlah modulo `k`, XOR total. Monovariant bergerak satu arah (selalu turun) — dipakai untuk bukti berhenti atau greedy. Analoginya puzzle 15: paritas permutasi plus kotak kosong.

**Kapan:** “operasi: tukar / geser / tambah ±1 di dua tempat”, constructive yes/no, game. Jangan mengandalkan invariant yang belum diuji pada satu operasi. Tulis Δ pada satu langkah.

**Proses:** array, operasi pilih `i`, lakukan `a[i]+=1`, `a[i+1]-=1`. Invariant: **jumlah total** tetap.

1. Awal `{1,2,3}` jumlah 6. Target `{3,3,0}` jumlah 6, mungkin.
2. Target `{4,4,0}` jumlah 8, mustahil.
3. Invariant lebih ketat kadang perlu prefix, bukan hanya jumlah.
4. Operasi “tukar tetangga” **mengubah** paritas inversi. Jadi paritas inversi bukan invariant untuk tukar tetangga.
5. Operasi “putar tiga elemen” mengubah inversi genap: paritas inversi invariant. `{2,1,3}` inversi ganjil tidak bisa ke `{1,2,3}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll jumlah(const vector<ll>& a) {
    ll s = 0;
    for (ll x : a) s += x;
    return s;
}

int paritas_inversi(const vector<int>& a) {
    int n = (int)a.size(), inv = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv & 1;
}

bool maybe_jumlah(const vector<ll>& a, const vector<ll>& b) {
    return jumlah(a) == jumlah(b);
}

int main() {
    FASTIO;
    cout << maybe_jumlah({1, 2, 3}, {3, 3, 0}) << '\n'; // 1
    cout << maybe_jumlah({1, 2, 3}, {4, 4, 0}) << '\n'; // 0
    cout << paritas_inversi({2, 1, 3}) << '\n';         // 1
    cout << paritas_inversi({1, 2, 3}) << '\n';         // 0
    return 0;
}
```

Inversi naif `O(n^2)`. Untuk `n` besar, merge di [../04-sorting-searching/merge-inversi.md](../04-sorting-searching/merge-inversi.md).

**Jebakan:**
1. Invariant “terasa benar” tanpa uji satu operasi.
2. Paritas indeks 1-based versus 0-based pada papan.
3. XOR versus jumlah tertukar.
4. Bilangan negatif modulo di C++.

**Kompleksitas:** jumlah / XOR `O(n)`. Inversi naif `O(n^2)`.

---

## Konstruksi versus DP

**Teori:** “Cetak salah satu array yang jumlahnya `S`” bisa greedy (ambil terbesar yang muat) **atau** DP rekonstruksi. Greedy gagal pada subset sum utuh: `{5,4,3}`, `S = 7`. DP `ada[s]` lalu jejak barang memberi `{4,3}`. Analoginya: konstruktif “any” tidak selalu berarti greedy; kadang artinya “rekonstruksi dari tabel”.

**Kapan:** soal any + constraint lokal sederhana → pola / greedy berbukti. Soal any + kapasitas / jumlah tepat + barang utuh → DP jejak, folder 09 file rekonstruksi. Jangan mencetak “IMPOSSIBLE” hanya karena greedy gagal.

**Proses:**

1. Greedy terbesar pada `{5,4,3}`, `S=7` gagal.
2. DP subset: `ada[0]=1`, masuk 5 → 5, masuk 4 → 4 dan 9, masuk 3 → 3,7,8,12. `ada[7]=1`.
3. Jejak: 7 datang dari 3, sisa 4 datang dari 4.
4. Objek `{3,4}` sah.
5. Greedy tidak boleh menutup kasus YES.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool greedy_subset(vector<ll> a, ll S) {
    sort(a.rbegin(), a.rend());
    for (ll x : a) if (x <= S) S -= x;
    return S == 0;
}

vector<ll> dp_subset(const vector<ll>& a, int S) {
    int n = (int)a.size();
    vector<int> ada(S + 1, 0), dari(S + 1, -1);
    ada[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int s = S; s >= (int)a[i]; s--) if (ada[s - (int)a[i]] && !ada[s]) {
            ada[s] = 1;
            dari[s] = i;
        }
    }
    if (!ada[S]) return {};
    vector<ll> isi;
    int s = S;
    while (s > 0) {
        int i = dari[s];
        isi.push_back(a[i]);
        s -= (int)a[i];
    }
    return isi;
}

int main() {
    FASTIO;
    vector<ll> a = {5, 4, 3};
    cout << greedy_subset(a, 7) << '\n'; // 0
    auto isi = dp_subset(a, 7);
    for (ll x : isi) cout << x << ' ';
    cout << '\n'; // 3 4
    return 0;
}
```

**Jebakan:**
1. NO palsu dari greedy.
2. Rekonstruksi DP memakai barang yang sama dua kali pada 0-1.
3. Loop kapasitas naik saat 0-1.

**Kompleksitas:** greedy `O(n log n)` dan bisa salah. DP `O(nS)` plus jejak.

---

## Huffman sebagai konstruktif

**Teori:** Bangun pohon prefix-code biaya minimum. Selalu gabungkan dua pohon dengan frekuensi terkecil. Exchange: kode optimal punya dua simbol terjarang sebagai saudara di daun terdalam. Analoginya packing kardus: satukan dua tumpukan paling ringan dulu. Ini konstruktif plus greedy plus heap: objeknya pohon, angkanya biaya.

Bukan knapsack. Bukan jika biaya gabung tidak `f+g`.

**Kapan:** kompresi, “biaya gabung file / batu”. `n = 1` biaya 0.

**Proses:** frekuensi `3,3,4,5`.

```text
heap 3,3,4,5
gabung 3+3=6   biaya += 6
gabung 4+5=9   biaya += 9
gabung 6+9=15  biaya += 15
total 30
```

Panjang kode seimbang 2, biaya `3*2+3*2+4*2+5*2 = 30`. Sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll biaya_huffman(vector<ll> f) {
    if (f.size() <= 1) return 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll x : f) pq.push(x);
    ll biaya = 0;
    while (pq.size() > 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ll s = a + b;
        biaya += s;
        pq.push(s);
    }
    return biaya;
}

int main() {
    FASTIO;
    cout << biaya_huffman({3, 3, 4, 5}) << '\n'; // 30
    cout << biaya_huffman({1, 1, 1, 1}) << '\n'; // 8
    cout << biaya_huffman({7}) << '\n';          // 0
    return 0;
}
```

`{1,1,1,1}`: dua gabung 2, lalu 4, total 8.

**Jebakan:**
1. Max-heap.
2. `n=1` biaya `f[0]`.
3. Overflow jumlah berulang: `ll`.

**Kompleksitas:** `O(n log n)`, memori `O(n)`.

---

## Stress n kecil

**Teori:** Generator `n = 1..12`, brute semua objek atau bandingkan pemeriksa. Analoginya mencicipi semua porsi mini. Alasan benar: konstruktif gagal di ujung, bukan di tengah sampel.

**Kapan:** selalu sebelum submit pola baru. Tidak menggantikan bukti mustahil.

**Proses:** untuk syarat “selisih tetangga bukan 1”:

1. Brute semua permutasi `n <= 7`, catat apakah ada yang sah.
2. Bandingkan dengan konstruktor: jika brute ada dan konstruktor kosong → salah klaim IMPOSSIBLE.
3. Jika konstruktor mengisi dan pemeriksa gagal → pola salah.
4. Khusus `n = 1,2,3,4`.
5. Baru generalisasi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool sah(const vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i + 1 < n; i++)
        if (abs(a[i] - a[i + 1]) == 1) return false;
    return true;
}

bool brute_ada(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    do {
        if (sah(a)) return true;
    } while (next_permutation(a.begin(), a.end()));
    return false;
}

vector<int> konstruk(int n) {
    if (n == 1) return {1};
    if (n <= 3) return {};
    vector<int> a;
    for (int x = 2; x <= n; x += 2) a.push_back(x);
    for (int x = 1; x <= n; x += 2) a.push_back(x);
    return a;
}

int main() {
    FASTIO;
    for (int n = 1; n <= 7; n++) {
        auto a = konstruk(n);
        bool ada = brute_ada(n);
        bool ok = a.empty() ? !ada : sah(a);
        cout << n << " brute=" << ada << " konstruk_ok=" << ok << '\n';
    }
    return 0;
}
```

Semua baris `konstruk_ok=1` berarti pola dan klaim mustahil selaras dengan brute.

**Jebakan:**
1. Brute memakai model syarat yang beda.
2. Tidak mengacak `n`, hanya satu contoh.
3. `next_permutation` tanpa `iota` terurut.

**Kompleksitas:** `n! · n` untuk brute. `n <= 8` nyaman.

---

## Peta keputusan

```text
Soal "print any / construct"
├── cek mustahil (paritas, bound) dulu
├── tulis pemeriksa
├── pola n kecil, awasi titik sambung
└── stress n=1..30

Soal "print optimal object"
├── greedy berbukti / exchange
└── kalau tidak: DP + rekonstruksi (folder 09)

Soal "berapa banyak objek"
  → DP / combinatorics, bukan cetak satu contoh
```

| langkah | pertanyaan |
| --- | --- |
| invariant | target bisa dicapai? |
| pemeriksa | objekku sah? |
| titik sambung | `n=2,3,4` hidup? |
| greedy vs DP | any atau optimal? satu counterexample? |

Ringkasan: pemeriksa dulu, mustahil dulu, titik sambung diuji untuk semua `n` kecil. Greedy yang gagal membangun objek bukan bukti NO: kadang DP jejak masih YES.

Kembali ke [kapan-dp.md](kapan-dp.md) atau [../09-dp/12-rekonstruksi.md](../09-dp/12-rekonstruksi.md) jika objeknya jejak tabel.
