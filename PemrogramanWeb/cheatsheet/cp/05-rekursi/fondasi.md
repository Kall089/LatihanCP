# Fondasi rekursi

[← README](README.md) · [Indeks CP](../README.md)

Rekursi memecah soal menjadi soal yang sama bentuknya, tetapi lebih kecil. Dua bagian wajib selalu ada: **kasus dasar** yang menghentikan panggilan, dan **kasus rekursif** yang mengecilkan input.

Day terkait: **057**. Semua kode 0-based, fungsi modular, `main` hanya menguji. Latihan harian tetap di ComprogLearning, bukan di sini.

## Daftar isi

- [Kasus dasar dan bingkai tumpukan](#kasus-dasar-dan-bingkai-tumpukan)
- [Faktorial](#faktorial)
- [Fibonacci naif](#fibonacci-naif)
- [Pangkat cepat rekursif](#pangkat-cepat-rekursif)
- [Menara Hanoi](#menara-hanoi)
- [Palindrom dan balik string](#palindrom-dan-balik-string)
- [Rekursi pada grid](#rekursi-pada-grid)
- [Peta keputusan](#peta-keputusan)

---

## Kasus dasar dan bingkai tumpukan

**Teori:** Analoginya tangga: untuk turun dari anak tangga ke-`n`, kamu turun satu undak, lalu mengulang masalah yang sama dari undak `n-1`. Setiap panggilan menaruh satu **bingkai** di call stack: parameter, alamat kembali, dan variabel lokal. Bingkai itu hidup sampai fungsi `return`. Tanpa kasus dasar, `n` terus mengecil melewati batas atau tidak mengecil sama sekali, lalu stack penuh.

**Kapan:** soal punya struktur “sama, tetapi lebih kecil”: pohon, grid DFS, Hanoi, kombinasi, DP top-down. Jangan dipakai untuk loop lurus seperti jumlah `1..n`. Jangan dipakai jika kedalaman bisa `1e5` pada rantai lurus: stack default sering hanya beberapa megabyte.

**Proses:** `countdown(3)` menaruh bingkai bertingkat, lalu melepaskannya dari dalam ke luar.

```text
panggil countdown(3)
  cetak 3, panggil countdown(2)
    cetak 2, panggil countdown(1)
      cetak 1, panggil countdown(0)
        n == 0 → cetak Selesai!, return
      return
    return
  return
keluaran: 3, 2, 1, Selesai!
```

Isi stack saat paling dalam (atas = bingkai aktif):

```text
countdown(0)   n=0, mau return
countdown(1)   n=1, menunggu anak
countdown(2)   n=2, menunggu anak
countdown(3)   n=3, menunggu anak
main
```

Kalau kasus dasar dihapus, `n` menjadi negatif dan stack penuh.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void countdown(int n) {
    if (n == 0) {
        cout << "Selesai!\n";
        return;
    }
    cout << n << '\n';
    countdown(n - 1);
}

int kedalaman_maks = 0;

void ukur_dalam(int n, int dalam) {
    kedalaman_maks = max(kedalaman_maks, dalam);
    if (n == 0) return;
    ukur_dalam(n - 1, dalam + 1);
}

int main() {
    FASTIO;
    countdown(3);
    kedalaman_maks = 0;
    ukur_dalam(4, 1);
    cout << "kedalaman countdown(4) = " << kedalaman_maks << '\n';
    return 0;
}
```

Keluaran yang diharapkan: `3 2 1 Selesai!` lalu `kedalaman countdown(4) = 5`. Lima bingkai: `n = 4,3,2,1,0`. Kedalaman adalah jumlah bingkai, bukan nilai `n`.

**Jebakan:**
1. Lupa kasus dasar.
2. Kasus rekursif tidak mengecil: `f(n)` memanggil `f(n)`.
3. Kedalaman `n = 1e6` pada DFS rantai. Ganti ke stack eksplisit atau BFS.
4. Mengira rekursi gratis. Tiap panggilan lebih mahal dari satu putaran `for`.

**Kompleksitas:** waktu `O(n)` untuk countdown linier. Memori stack `O(n)` bingkai. Batas aman kasar: beberapa ribu sampai puluhan ribu, tergantung compiler dan ukuran bingkai.

---

## Faktorial

**Teori:** `n! = n × (n-1)!` dan `0! = 1`. Definisi itu sudah rekursif. Alasan benar: setiap `n!` hanya bergantung pada satu nilai lebih kecil, dan rantai itu berhenti di `0`. Analoginya menyusun `n` orang di antrean: pilih siapa di depan (`n` pilihan), lalu susun sisa `(n-1)!` cara.

**Kapan:** `n` kecil (`n <= 20` untuk `long long`), atau sebagai latihan rekursi. Untuk `n` besar di soal counting, hitung faktorial modular di folder teori bilangan, bukan `ll` mentah. Jangan rekursi jika kamu hanya butuh satu nilai: loop `for` lebih pendek.

**Proses:** `fact(4)` membuka rantai, lalu mengalikan saat kembali.

```text
fact(4)
= 4 * fact(3)
= 4 * (3 * fact(2))
= 4 * (3 * (2 * fact(1)))
= 4 * (3 * (2 * (1 * fact(0))))
= 4 * (3 * (2 * (1 * 1)))
= 24
```

| n | n! | muat ll? |
| ---: | ---: | --- |
| 0 | 1 | ya |
| 5 | 120 | ya |
| 10 | 3628800 | ya |
| 20 | 2432902008176640000 | ya |
| 21 | 51090942171709440000 | tidak, overflow |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll fact(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1LL;
    return (ll)n * fact(n - 1);
}

ll fact_iter(int n) {
    ll res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int main() {
    FASTIO;
    for (int n = 0; n <= 10; n++) {
        cout << n << "! = " << fact(n)
             << " (iter " << fact_iter(n) << ")\n";
    }
    cout << "20! = " << fact(20) << '\n';
    return 0;
}
```

`fact(5)` adalah `120`. `fact(20)` masih benar. `fact(21)` sudah bukan matematika: bitnya terbungkus.

**Jebakan:**
1. `fact(21)` overflow diam-diam.
2. `int` meledak jauh lebih awal: `13!` sudah di atas `2e9`.
3. Lupa `0! = 1`.
4. Rekursi `fact` untuk `n = 1e6` RTE stack, padahal jawaban tetap overflow.

**Kompleksitas:** waktu `O(n)`, stack `O(n)`. Versi iteratif waktu `O(n)`, memori `O(1)`.

---

## Fibonacci naif

**Teori:** `F(0) = 0`, `F(1) = 1`, `F(n) = F(n-1) + F(n-2)`. Rumus itu benar, tetapi pohon panggilannya bercabang dua. Banyak cabang menghitung **nilai yang sama**. Analoginya kamu ditanya umur keponakan, lalu setiap kali lupa dan menghitung ulang dari tanggal lahir. Itulah *overlapping subproblems* — alasan memo dan DP lahir. Jembatan lengkapnya ada di [memoization.md](memoization.md) lalu folder [09-dp](../09-dp/README.md).

**Kapan:** hanya untuk `n` sangat kecil (`n <= 20`) atau untuk menjelaskan pohon rekursi. Jangan dikirim ke judge untuk `n = 40`. Soal Fibonacci besar memakai memo, bottom-up, atau matrix expo.

**Proses:** pohon `fib(5)`. Setiap kotak adalah satu panggilan.

```text
                    fib(5)
                   /      \
              fib(4)        fib(3)
             /     \        /    \
         fib(3)   fib(2) fib(2) fib(1)=1
         /   \    /   \   /   \
     fib(2) fib(1) 1   0  1    0
     /   \
    1     0
```

`fib(3)` muncul 2 kali, `fib(2)` muncul 3 kali. Jumlah panggilan tumbuh seperti `φ^n`. Nilai unik hanya `n+1` buah.

| n | F(n) | kira-kira panggilan naif |
| ---: | ---: | ---: |
| 5 | 5 | 15 |
| 10 | 55 | 177 |
| 20 | 6765 | 21891 |
| 30 | 832040 | 2.7 juta |
| 40 | 102334155 | 331 juta → TLE |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll panggilan = 0;

ll fib_naif(int n) {
    panggilan++;
    if (n <= 1) return n;
    return fib_naif(n - 1) + fib_naif(n - 2);
}

int main() {
    FASTIO;
    for (int n : {5, 10, 15, 20}) {
        panggilan = 0;
        ll nilai = fib_naif(n);
        cout << "F(" << n << ") = " << nilai
             << ", panggilan = " << panggilan << '\n';
    }
    return 0;
}
```

`F(5) = 5` karena `3+2`. Panggilan 15, bukan 6. Itu bukti cabang terbuang.

**Jebakan:**
1. Mengirim versi naif karena “kodenya benar”.
2. Overflow `F(93)` sudah di luar `ll`. `F(92)` masih muat.
3. Hanya kasus dasar `n == 0`, lalu `fib(1)` memanggil `fib(-1)`.

**Kompleksitas:** waktu `Θ(φ^n)`, stack `O(n)` (kedalaman rantai `fib(n) → fib(n-1) → …`).

---

## Pangkat cepat rekursif

**Teori:** `a^e = (a^{e/2})^2` jika `e` genap, dan `a^e = a · (a^{e/2})^2` jika `e` ganjil. `a^0 = 1`. Setiap langkah membagi eksponen dua, jadi jumlah langkah `O(log e)`. Analoginya lipat kertas: 10 kali lipat jauh lebih cepat daripada menulis 1024 faktor. Kenapa benar: ini hukum eksponen, bukan heuristik.

**Kapan:** `a^b`, `a^b mod m`, jumlah geometri, matrix expo. Jangan pakai `pow()` dari `<cmath>`: itu `double`. Jangan kalikan `a` sebanyak `e` kali jika `e` sampai `1e18`.

**Proses:** `modpow(3, 13, 1000)`. `13` ganjil, `13/2 = 6`. Jangan menulis `3 * (3^6)`. Yang benar `3 * (3^6)^2 = 3^{13}`.

```text
modpow(3,13) = [modpow(3,6)]^2 * 3
modpow(3,6)  = [modpow(3,3)]^2
modpow(3,3)  = [modpow(3,1)]^2 * 3
modpow(3,1)  = [modpow(3,0)]^2 * 3 = 3
modpow(3,3)  = 9 * 3 = 27
modpow(3,6)  = 27^2 = 729
modpow(3,13) = 729^2 * 3 = 1594323
1594323 % 1000 = 323
```

Cek biner: `13 = 1101_2 = 8+4+1`, jadi `3^8 * 3^4 * 3 = 6561 * 81 * 3 = 1594323`. Sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll modpow_rec(ll a, ll e, ll m) {
    if (m == 1) return 0;
    if (e == 0) return 1 % m;
    a %= m;
    if (a < 0) a += m;
    ll half = modpow_rec(a, e / 2, m);
    ll res = half * half % m;
    if (e & 1) res = res * a % m;
    return res;
}

ll modpow_iter(ll a, ll e, ll m) {
    ll res = 1 % m;
    a %= m;
    if (a < 0) a += m;
    while (e > 0) {
        if (e & 1) res = res * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return res;
}

int main() {
    FASTIO;
    cout << modpow_rec(3, 13, 1000) << '\n';        // 323
    cout << modpow_iter(3, 13, 1000) << '\n';       // 323
    cout << modpow_rec(2, 10, 1000000007) << '\n';  // 1024
    cout << modpow_rec(5, 0, 7) << '\n';            // 1
    return 0;
}
```

**Jebakan:**
1. Kuadrat tanpa `%` lalu baru mod di akhir: overflow.
2. `pow(3, 13)` double.
3. `e = 0` harus 1; di CP `0^0` biasanya 1.
4. `m = 1` semua hasil 0. `a` negatif sebelum mod.

**Kompleksitas:** waktu `O(log e)`, stack versi rekursif `O(log e)`, versi iteratif `O(1)` tambahan.

---

## Menara Hanoi

**Teori:** Pindahkan `n` cakram dari tiang `A` ke `C`, bantuan `B`. Aturan: satu cakram per langkah, cakram besar tidak boleh di atas yang lebih kecil. Solusi rekursif: pindahkan `n-1` ke tiang bantu, pindahkan cakram terbesar, pindahkan `n-1` ke tujuan. Kenapa benar: setelah `n-1` ada di bantu, cakram terbesar bebas pindah; menara `n-1` adalah soal yang sama. Jumlah langkah `T(n) = 2 T(n-1) + 1`, `T(1) = 1`, jadi `T(n) = 2^n - 1`.

**Kapan:** soal “urutkan dengan satu aturan plus tiga tumpukan”, atau untuk merasakan rekursi belah dua. Jangan enumerasi langkah jika `n >= 30`: keluarannya miliaran baris. Kalau soal hanya minta jumlah, rumus cukup.

**Proses:** `n = 3`, tiang A ke C, bantu B.

```text
hanoi(3, A, C, B)
  hanoi(2, A, B, C)
    hanoi(1, A, C, B) → A ke C
    A ke B
    hanoi(1, C, B, A) → C ke B
  A ke C
  hanoi(2, B, C, A)
    hanoi(1, B, A, C) → B ke A
    B ke C
    hanoi(1, A, C, B) → A ke C
```

Tujuh langkah, sesuai `2^3 - 1 = 7`: A→C, A→B, C→B, A→C, B→A, B→C, A→C.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void hanoi(int n, char dari, char ke, char bantu, vector<string>& langkah) {
    if (n == 0) return;
    hanoi(n - 1, dari, bantu, ke, langkah);
    string s = "";
    s += dari;
    s += " -> ";
    s += ke;
    langkah.push_back(s);
    hanoi(n - 1, bantu, ke, dari, langkah);
}

ll jumlah_langkah(int n) {
    return (1LL << n) - 1; // n <= 62
}

int main() {
    FASTIO;
    vector<string> langkah;
    hanoi(3, 'A', 'C', 'B', langkah);
    cout << "jumlah = " << langkah.size()
         << " rumus = " << jumlah_langkah(3) << '\n';
    for (size_t i = 0; i < langkah.size(); i++)
        cout << i + 1 << ". " << langkah[i] << '\n';
    return 0;
}
```

**Jebakan:**
1. Menukar argumen `bantu` dan `ke`.
2. Mencetak langkah untuk `n = 20` saat soal hanya minta jumlah.
3. `1 << n` overflow jika `n >= 31` pada `int`. Pakai `1LL << n`.

**Kompleksitas:** waktu dan keluaran `O(2^n)`. Stack `O(n)`. Rumus jumlah saja `O(1)`.

---

## Palindrom dan balik string

**Teori:** String palindrom jika karakter pertama sama dengan terakhir, dan bagian tengah juga palindrom. Analoginya membaca kata dari kiri dan kanan sekaligus. Rekursi mengecilkan rentang `[l, r]` menjadi `[l+1, r-1]`. Kasus dasar: `l >= r` (satu huruf atau kosong) selalu palindrom.

**Kapan:** cek palindrom, atau latihan dua pointer lewat rekursi. Untuk cek saja, dua pointer iteratif lebih sederhana. Jangan rekursi per karakter pada string `1e5` jika tiap panggilan tidak memangkas banyak.

**Proses:** `"katak"` versus `"kata"`.

`"katak"`, indeks `0..4`:

```text
l=0 r=4  k == k  → lanjut [1,3]
l=1 r=3  a == a  → lanjut [2,2]
l=2 r=2  l>=r → ya
```

`"kata"`, indeks `0..3`: `k != a` langsung bukan palindrom.

Balik `"abc"`: `rev(bc)+a = (rev(c)+b)+a = cba`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool palindrom(const string& s, int l, int r) {
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return palindrom(s, l + 1, r - 1);
}

string balik(const string& s) {
    if (s.size() <= 1) return s;
    return balik(s.substr(1)) + s[0];
}

int main() {
    FASTIO;
    cout << palindrom("katak", 0, 4) << '\n'; // 1
    cout << palindrom("kata", 0, 3) << '\n';  // 0
    cout << palindrom("", 0, -1) << '\n';     // 1
    cout << balik("abc") << '\n';             // cba
    return 0;
}
```

`balik` memakai `substr`: enak dibaca, mahal `O(n^2)`. Untuk CP, dua pointer atau `reverse`.

**Jebakan:**
1. `substr` di rekursi `O(n^2)`.
2. Indeks `r` eksklusif versus inklusif tertukar.
3. String kosong harus true.

**Kompleksitas:** palindrom dua indeks `O(n)` waktu, `O(n)` stack. `balik` plus `substr` `O(n^2)`.

---

## Rekursi pada grid

**Teori:** Sel grid adalah graf: tepi ke tetangga 4-arah. Flood fill = DFS mewarnai komponen terhubung. Dari `(r, c)`, kunjungi tetangga yang masih dalam batas, belum dikunjungi, dan sewarna. Tandai **sebelum** rekursi agar tidak bolak-balik. Analoginya tuang cat di peta. Ini masih fondasi rekursi; pola undo ada di [backtracking.md](backtracking.md).

**Kapan:** hitung pulau, luas daerah, labirin kecil. Grid `n, m <= 1000` lebih aman BFS atau DFS iteratif. DFS rekursif pada ular panjang `n*m = 1e6` RTE stack.

**Proses:** grid `3×3`:

```text
1 1 0
0 1 0
1 0 1
```

Flood dari `(0,0)` mewarnai tiga sel `1` di sudut kiri-atas: `(0,0), (0,1), (1,1)`. `(2,0)` dan `(2,2)` komponen lain. Jumlah pulau = 3. Luas komponen pertama = 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int flood(int r, int c, vector<vector<int>>& g, vector<vector<int>>& vis) {
    int n = (int)g.size(), m = (int)g[0].size();
    if (r < 0 || c < 0 || r >= n || c >= m) return 0;
    if (vis[r][c] || g[r][c] == 0) return 0;
    vis[r][c] = 1;
    int luas = 1;
    for (int k = 0; k < 4; k++)
        luas += flood(r + dr[k], c + dc[k], g, vis);
    return luas;
}

int hitung_pulau(vector<vector<int>> g) {
    int n = (int)g.size(), m = (int)g[0].size();
    vector<vector<int>> vis(n, vector<int>(m, 0));
    int pulau = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!vis[i][j] && g[i][j] == 1) {
                flood(i, j, g, vis);
                pulau++;
            }
    return pulau;
}

int main() {
    FASTIO;
    vector<vector<int>> g = {
        {1, 1, 0},
        {0, 1, 0},
        {1, 0, 1}
    };
    cout << hitung_pulau(g) << '\n'; // 3
    vector<vector<int>> vis(3, vector<int>(3, 0));
    cout << flood(0, 0, g, vis) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. Cek batas **setelah** akses `g[r][c]` → RTE.
2. Lupa `vis` → rekursi tak hingga.
3. 8-arah versus 4-arah salah baca soal.
4. DFS rekursif grid 1000×1000 ular.

**Kompleksitas:** waktu `O(n · m)` untuk satu sapuan penuh. Stack rekursif terburuk `O(n · m)`.

---

## Peta keputusan

```text
Soal "sama tetapi lebih kecil"
├── satu cabang, n kecil          → rekursi linier (fact, countdown)
├── dua cabang overlap            → jangan naif, buka memoization.md
├── pecah n jadi n-1 + 1          → Hanoi, interval
└── tetangga grid                 → flood fill, jaga stack

Kedalaman 1e5
  → stack eksplisit / loop

Hanya butuh rumus
  → jangan simulasi 2^n langkah
```

| n | rekursi linier | fib naif | Hanoi langkah |
| ---: | --- | --- | --- |
| 10 | aman | masih | 1023 |
| 20 | aman | berat | 1 juta |
| 40 | stack? | TLE | mustahil cetak |
| 1e5 | RTE stack | — | — |

Ringkasan: kasus dasar dulu, input mengecil, stack adalah memori tersembunyi. Fibonacci naif adalah alasan folder ini punya [memoization.md](memoization.md).

Lanjut ke [subset-bitmask.md](subset-bitmask.md) untuk enumerasi himpunan, atau [backtracking.md](backtracking.md) jika ada undo.
