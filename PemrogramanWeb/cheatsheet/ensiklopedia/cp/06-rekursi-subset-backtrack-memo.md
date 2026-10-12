# 06 — Rekursi, subset, backtracking, dan memo

[← 05 searching](05-sorting-binsearch-ternary-mitm.md) · [Indeks](README.md) · [Lanjut: greedy →](07-greedy-interval-konstruktif.md)

Kurikulum: folder **05 — Rekursi** di `DAFTAR-MATERI` (Day 057, 060, 062, 066, 067).

Latihan harian ada di `KULIAH/ComProgLearning/CP` (Day-57, Day-60, Day-62, Day-66). Folder itu latihan, bukan file yang disalin ke sini.

Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, **fungsi modular**, indeks **0-based**, plus `main` mini untuk mengetes.

> **Ide satu kalimat:** rekursi memecah soal jadi soal yang lebih kecil; backtracking mencoba lalu mundur; bitmask menomori himpunan; memo mengingat jawaban supaya cabang yang sama tidak dihitung dua kali.

## Daftar isi

- [Cara baca bab ini](#cara-baca-bab-ini)
- [Rekursi: kasus dasar dan bingkai tumpukan](#rekursi-kasus-dasar-dan-bingkai-tumpukan)
- [Faktorial](#faktorial)
- [Fibonacci naif](#fibonacci-naif)
- [Pangkat cepat rekursif](#pangkat-cepat-rekursif)
- [Menara Hanoi](#menara-hanoi)
- [Palindrom dan balik string](#palindrom-dan-balik-string)
- [Enumerasi subset rekursif](#enumerasi-subset-rekursif)
- [Operasi bitmask](#operasi-bitmask)
- [Enumerasi subset dengan bitmask](#enumerasi-subset-dengan-bitmask)
- [Subset dari sebuah mask dan enumerasi 3^n](#subset-dari-sebuah-mask-dan-enumerasi-3n)
- [Enumerasi permutasi](#enumerasi-permutasi)
- [Pola backtracking: coba, lanjut, mundur](#pola-backtracking-coba-lanjut-mundur)
- [N-Queens](#n-queens)
- [Combination Sum dan pruning](#combination-sum-dan-pruning)
- [Subset Sum plus rekonstruksi](#subset-sum-plus-rekonstruksi)
- [Memoization: tiga baris sakti](#memoization-tiga-baris-sakti)
- [Memo tangga dan knapsack](#memo-tangga-dan-knapsack)
- [Dari memo ke tabel bottom-up](#dari-memo-ke-tabel-bottom-up)
- [Rekursi pada grid dan flood fill](#rekursi-pada-grid-dan-flood-fill)
- [Peta keputusan bab ini](#peta-keputusan-bab-ini)
- [Ringkasan folder 05](#ringkasan-folder-05)

## Cara baca bab ini

Tiap topik memakai enam blok tetap:

1. **Teori** — analogi plus alasan kenapa langkahnya sah.
2. **Kapan** — dipakai / tidak dipakai.
3. **Proses** — simulasi angka kecil, bisa dihitung di kertas.
4. **Kode** — fungsi terpisah, `main` hanya menguji.
5. **Jebakan** — dua sampai empat kesalahan yang sering WA / RTE / TLE.
6. **Kompleksitas** — waktu dan memori.

Compile satu contoh per file:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -o tes tes.cpp
./tes
```

Di macOS, `bits/stdc++.h` kadang tidak ada di `clang++`. Pakai `g++` Homebrew, atau ganti include ke header yang dipakai saja.

---

## Rekursi: kasus dasar dan bingkai tumpukan

**Teori:** rekursi adalah fungsi yang memanggil dirinya sendiri untuk soal yang lebih kecil. Analoginya tangga: untuk turun dari anak tangga ke-`n`, kamu turun satu undak, lalu mengulang masalah yang sama dari undak `n-1`. Dua bagian wajib selalu ada. **Kasus dasar** menghentikan panggilan. **Kasus rekursif** mengecilkan input. Tanpa kasus dasar, tumpukan panggilan tidak pernah turun dan program meledak (*stack overflow*). Setiap panggilan menaruh satu **bingkai** di call stack: parameter, alamat kembali, dan variabel lokal. Bingkai itu hidup sampai fungsi `return`.

**Kapan:** soal punya struktur “sama, tetapi lebih kecil”: pohon, grid DFS, Hanoi, kombinasi, DP top-down. Jangan dipakai untuk loop lurus (`jumlah 1..n`) — overhead panggilan tidak perlu. Jangan dipakai jika kedalaman bisa `10^5` atau lebih pada rantai lurus: stack default sering hanya beberapa megabyte.

**Proses:** `countdown(3)` menaruh bingkai bertingkat, lalu melepaskannya dari dalam ke luar.

```
panggil countdown(3)
  cetak 3, panggil countdown(2)
    cetak 2, panggil countdown(1)
      cetak 1, panggil countdown(0)
        n == 0 → cetak "Selesai!", return
      return
    return
  return
keluaran: 3, 2, 1, Selesai!
```

Isi stack saat paling dalam (atas = bingkai aktif):

```
countdown(0)   n=0, mau return
countdown(1)   n=1, menunggu anak
countdown(2)   n=2, menunggu anak
countdown(3)   n=3, menunggu anak
main
```

Kalau kasus dasar dihapus, `n` terus menjadi negatif dan stack penuh.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void countdown(int n) {
    if (n == 0) {                 // kasus dasar
        cout << "Selesai!\n";
        return;
    }
    cout << n << '\n';
    countdown(n - 1);             // input mengecil
}

int kedalaman_maks = 0;

void ukur_dalam(int n, int dalam) {
    kedalaman_maks = max(kedalaman_maks, dalam);
    if (n == 0) return;
    ukur_dalam(n - 1, dalam + 1);
}

int main() {
    countdown(3);
    kedalaman_maks = 0;
    ukur_dalam(4, 1);
    cout << "kedalaman countdown(4) = " << kedalaman_maks << '\n';
    return 0;
}
```

Keluaran yang diharapkan:

```
3
2
1
Selesai!
kedalaman countdown(4) = 5
```

`ukur_dalam(4)` membuat lima bingkai: `n=4,3,2,1,0`. Kedalaman = jumlah bingkai, bukan nilai `n`.

**Jebakan:** lupa kasus dasar; kasus rekursif tidak mengecil (`f(n)` memanggil `f(n)`); kedalaman `n = 1e6` pada DFS rantai — ganti ke stack eksplisit / BFS; mengira rekursi “gratis” — tiap panggilan lebih mahal dari satu putaran `for`.

**Kompleksitas:** waktu `O(n)` untuk countdown linier. Memori stack `O(n)` bingkai. Batas aman kasar: kedalaman beberapa ribu sampai puluhan ribu, tergantung compiler dan ukuran bingkai.

---

## Faktorial

**Teori:** `n! = n × (n-1)!` dan `0! = 1`. Definisi itu sudah rekursif. Alasan benar: setiap `n!` hanya bergantung pada satu nilai lebih kecil, dan rantai itu berhenti di `0`. Analoginya menyusun `n` orang di antrean: pilih siapa di depan (`n` pilihan), lalu susun sisa `(n-1)!` cara.

**Kapan:** n kecil (`n ≤ 20` untuk `long long`), atau sebagai latihan rekursi. Untuk `n` besar di soal counting, hitakan faktorial modular (file 08), bukan `ll` mentah. Jangan rekursi jika kamu hanya butuh satu nilai — loop `for` lebih pendek dan tidak memakai stack.

**Proses:** `fact(4)` membuka rantai, lalu mengalikan saat kembali.

```
fact(4)
= 4 * fact(3)
= 4 * (3 * fact(2))
= 4 * (3 * (2 * fact(1)))
= 4 * (3 * (2 * (1 * fact(0))))
= 4 * (3 * (2 * (1 * 1)))
= 24
```

Tabel nilai yang muat di `long long` (batas `~9.22e18`):

| n | n! | muat ll? |
| --- | ---: | --- |
| 0 | 1 | ya |
| 5 | 120 | ya |
| 10 | 3 628 800 | ya |
| 20 | 2 432 902 008 176 640 000 | ya |
| 21 | 51 090 942 171 709 440 000 | tidak, overflow |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fact(int n) {
    if (n < 0) return -1;          // penanda input salah
    if (n == 0) return 1LL;        // kasus dasar
    return (ll)n * fact(n - 1);
}

ll fact_iter(int n) {
    ll res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int main() {
    for (int n = 0; n <= 10; n++) {
        cout << n << "! = " << fact(n)
             << " (iter " << fact_iter(n) << ")\n";
    }
    cout << "20! = " << fact(20) << '\n';
    return 0;
}
```

`fact(5)` mencetak `120`. `fact(20)` masih benar. `fact(21)` sudah bukan matematika — bitnya terbungkus.

**Jebakan:** `fact(21)` overflow diam-diam; `int` meledak jauh lebih awal (`13!` sudah di atas `2e9`); lupa `0! = 1`; rekursi `fact` untuk `n = 1e6` RTE stack, padahal jawaban tetap overflow.

**Kompleksitas:** waktu `O(n)`, stack `O(n)`. Versi iteratif waktu `O(n)`, memori `O(1)`.

---

## Fibonacci naif

**Teori:** `F(0) = 0`, `F(1) = 1`, `F(n) = F(n-1) + F(n-2)`. Rumus itu benar, tetapi pohon panggilannya bercabang dua. Banyak cabang menghitung **nilai yang sama**. Analoginya kamu ditanya umur keponakan, lalu setiap kali lupa dan menghitung ulang dari tanggal lahir. Itulah *overlapping subproblems* — alasan memo dan DP lahir.

**Kapan:** hanya untuk n sangat kecil (`n ≤ 20`) atau untuk menjelaskan pohon rekursi. Jangan dikirim ke judge untuk `n = 40`. Soal Fibonacci besar memakai memo, bottom-up, atau matrix expo (file 09).

**Proses:** pohon `fib(5)`. Setiap kotak adalah satu panggilan.

```
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

Hitung ulang yang terlihat:

- `fib(3)` muncul 2 kali.
- `fib(2)` muncul 3 kali.
- `fib(1)` dan `fib(0)` muncul berkali-kali.

Jumlah panggilan tumbuh seperti `~ φ^n`. Nilai yang unik hanya `n+1` buah: `F(0)..F(n)`.

| n | F(n) | kira-kira jumlah panggilan naif |
| --- | ---: | ---: |
| 5 | 5 | 15 |
| 10 | 55 | 177 |
| 20 | 6765 | 21 891 |
| 30 | 832040 | 2.7 juta |
| 40 | 102334155 | 331 juta → TLE |
| 50 | 12586269025 | tidak selesai |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll panggilan = 0;

ll fib_naif(int n) {
    panggilan++;
    if (n <= 1) return n;
    return fib_naif(n - 1) + fib_naif(n - 2);
}

int main() {
    for (int n : {5, 10, 15, 20}) {
        panggilan = 0;
        ll nilai = fib_naif(n);
        cout << "F(" << n << ") = " << nilai
             << ", panggilan = " << panggilan << '\n';
    }
    return 0;
}
```

Keluaran kira-kira:

```
F(5) = 5, panggilan = 15
F(10) = 55, panggilan = 177
F(15) = 610, panggilan = 1973
F(20) = 6765, panggilan = 21891
```

`F(5) = 5` karena `3+2`. Panggilan 15, bukan 6. Itu bukti cabang terbuang.

**Jebakan:** mengirim versi naif karena “kodenya benar”; overflow `F(93)` sudah di luar `ll` (`F(92)` masih muat); dua kasus dasar harus `0` dan `1` — kalau hanya `n==0` maka `fib(1)` memanggil `fib(-1)`.

**Kompleksitas:** waktu `Θ(φ^n)`, stack `O(n)` (kedalaman rantai `fib(n) → fib(n-1) → …`).

---

## Pangkat cepat rekursif

**Teori:** `a^e = (a^{e/2})^2` jika `e` genap, dan `a^e = a · (a^{e/2})^2` jika `e` ganjil. `a^0 = 1`. Setiap langkah membagi eksponen dua, jadi jumlah langkah `O(log e)`. Analoginya lipat kertas: 10 kali lipat jauh lebih cepat daripada menulis 1024 faktor. Kenapa benar: ini hanya hukum eksponen, bukan heuristik.

**Kapan:** `a^b`, `a^b mod m`, jumlah geometri, matrix expo (file 09). Jangan pakai `pow()` dari `<cmath>` — itu `double`, presisi hilang. Jangan kalikan `a` sebanyak `e` kali jika `e` sampai `10^18`.

**Proses:** `modpow(3, 13, 1000)`. `13` ganjil, `13/2 = 6`. Jangan menulis `3 * (3^6)` — yang benar `3 * (3^6)^2 = 3^{13}`.

```
modpow(3,13) = [modpow(3,6)]^2 * 3
modpow(3,6)  = [modpow(3,3)]^2
modpow(3,3)  = [modpow(3,1)]^2 * 3
modpow(3,1)  = [modpow(3,0)]^2 * 3 = 1 * 3 = 3
modpow(3,3)  = 3^2 * 3 = 27
modpow(3,6)  = 27^2 = 729
modpow(3,13) = 729^2 * 3 = 531441 * 3 = 1594323
1594323 % 1000 = 323
```

Cek biner: `13 = 1101_2 = 8+4+1`, jadi `3^8 * 3^4 * 3 = 6561 * 81 * 3 = 1594323`. Sama. `%` boleh dipasang di setiap kuadrat: `729^2 % 1000 = 441`, `441*3 % 1000 = 323`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    cout << modpow_rec(3, 13, 1000) << '\n';   // 323
    cout << modpow_iter(3, 13, 1000) << '\n';  // 323
    cout << modpow_rec(2, 10, 1000000007) << '\n'; // 1024
    cout << modpow_rec(5, 0, 7) << '\n';       // 1
    return 0;
}
```

**Jebakan:** kuadrat tanpa `%` lalu baru mod di akhir — overflow; `pow(3,13)` double; `e = 0` harus 1, termasuk `0^0` di CP biasanya dianggap 1; `m = 1` semua hasil 0; `a` negatif sebelum mod.

**Kompleksitas:** waktu `O(log e)`, stack versi rekursif `O(log e)`, versi iteratif `O(1)` tambahan.

---

## Menara Hanoi

**Teori:** pindahkan `n` cakram dari tiang `A` ke `C`, bantuan `B`. Aturan: satu cakram per langkah, cakram besar tidak boleh di atas yang lebih kecil. Solusi rekursif: pindahkan `n-1` ke tiang bantu, pindahkan cakram terbesar, pindahkan `n-1` ke tujuan. Kenapa benar: setelah `n-1` ada di bantu, cakram terbesar bebas pindah; menara `n-1` adalah soal yang sama. Jumlah langkah `T(n) = 2 T(n-1) + 1`, `T(1) = 1`, jadi `T(n) = 2^n - 1`.

**Kapan:** soal “urutkan dengan satu aturan + tiga tumpukan”, atau untuk merasakan rekursi belah dua. Jangan enumerasi langkah jika `n ≥ 30` — keluarannya `1e9` baris. Kalau soal hanya minta jumlah langkah, rumus `2^n - 1` cukup, tidak perlu simulasi.

**Proses:** `n = 3`, tiang A → C, bantu B.

```
hanoi(3, A, C, B)
  hanoi(2, A, B, C)
    hanoi(1, A, C, B) → A ke C
    A ke B              (cakram 2)
    hanoi(1, C, B, A) → C ke B
  A ke C                (cakram 3)
  hanoi(2, B, C, A)
    hanoi(1, B, A, C) → B ke A
    B ke C              (cakram 2)
    hanoi(1, A, C, B) → A ke C
```

Tujuh langkah, sesuai `2^3 - 1 = 7`:

1. A→C, 2. A→B, 3. C→B, 4. A→C, 5. B→A, 6. B→C, 7. A→C.

Setelah langkah 4, cakram terbesar sudah di C. Sisa adalah Hanoi berukuran 2 dari B ke C.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    // 2^n - 1, n muat di ll selama n <= 62
    return (1LL << n) - 1;
}

int main() {
    vector<string> langkah;
    hanoi(3, 'A', 'C', 'B', langkah);
    cout << "jumlah = " << langkah.size()
         << " rumus = " << jumlah_langkah(3) << '\n';
    for (size_t i = 0; i < langkah.size(); i++)
        cout << i + 1 << ". " << langkah[i] << '\n';
    return 0;
}
```

**Jebakan:** menukar argumen `bantu` dan `ke` — menara salah susun; mencetak langkah untuk `n = 20` (`1 juta` baris) saat soal hanya minta jumlah; `1 << n` overflow jika `n ≥ 31` pada `int` — pakai `1LL << n` dan `n ≤ 62`.

**Kompleksitas:** waktu dan keluaran `O(2^n)`. Stack `O(n)`. Rumus jumlah saja `O(1)`.

---

## Palindrom dan balik string

**Teori:** string palindrom jika karakter pertama sama dengan terakhir, dan bagian tengah juga palindrom. Analoginya membaca kata dari kiri dan kanan sekaligus. Rekursi mengecilkan rentang `[l, r]` menjadi `[l+1, r-1]`. Kasus dasar: `l >= r` (satu huruf atau kosong) selalu palindrom.

**Kapan:** cek palindrom, generate palindrome partition (backtracking), atau latihan dua pointer lewat rekursi. Untuk cek saja, dua pointer iteratif lebih sederhana. Jangan rekursi per karakter pada string `1e5` jika tiap panggilan tidak memangkas banyak — stack dalam.

**Proses:** `"kata"` vs `"katak"`.

`"katak"`, indeks 0..4:

```
l=0 r=4  s[0]=k == s[4]=k  → lanjut [1,3]
l=1 r=3  s[1]=a == s[3]=a  → lanjut [2,2]
l=2 r=2  l>=r → ya
```

`"kata"`, indeks 0..3:

```
l=0 r=3  k == a ? tidak → bukan palindrom
```

Balik `"abc"`:

```
rev(abc) = rev(bc) + a
         = (rev(c) + b) + a
         = (c + b) + a
         = cba
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    cout << palindrom("katak", 0, 4) << '\n'; // 1
    cout << palindrom("kata", 0, 3) << '\n';  // 0
    cout << palindrom("", 0, -1) << '\n';     // 1, kosong
    cout << balik("abc") << '\n';             // cba
    return 0;
}
```

`balik` memakai `substr` — enak dibaca, mahal (`O(n^2)` salin). Untuk CP, dua pointer atau `reverse(s.begin(), s.end())`.

**Jebakan:** `substr` di rekursi `O(n^2)`; indeks `r` eksklusif vs inklusif tertukar; string kosong harus true; membandingkan `int` dengan `'0'` saat soal digit vs huruf.

**Kompleksitas:** palindrom dua indeks `O(n)` waktu, `O(n)` stack. `balik` + `substr` `O(n^2)` waktu dan memori.

---

## Enumerasi subset rekursif

**Teori:** untuk setiap elemen, ada dua pilihan: **ambil** atau **tidak**. Itu pohon biner berukuran `2^n`. Analoginya tas belanja: tiap barang “masuk / tinggal”. Urutan keputusan mengikuti indeks `0..n-1` supaya setiap himpunan muncul tepat sekali. Posisi daun (sudah lewat elemen terakhir) adalah satu subset jadi.

**Kapan:** `n ≤ 20` jika kerja per subset `O(n)` atau lebih kecil; `n ≤ 15` jika per subset mahal. Kalau hanya butuh cek “ada subset berjumlah S”, DP / knapsack lebih baik untuk `n = 40` plus kapasitas kecil. Jangan rekursi subset untuk `n = 30` (`1e9` daun).

**Proses:** array `{1, 2, 3}`. Pohon ambil/tidak dari kiri.

```
pos=0, cur=[]
  tidak 1 → pos=1 []
    tidak 2 → pos=2 []
      tidak 3 → { }
      ambil 3 → {3}
    ambil 2 → pos=2 [2]
      tidak 3 → {2}
      ambil 3 → {2,3}
  ambil 1 → pos=1 [1]
    tidak 2 → pos=2 [1]
      tidak 3 → {1}
      ambil 3 → {1,3}
    ambil 2 → pos=2 [1,2]
      tidak 3 → {1,2}
      ambil 3 → {1,2,3}
```

Delapan daun = `2^3`. Urutan di atas: `{} {3} {2} {2,3} {1} {1,3} {1,2} {1,2,3}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void enum_subset(int pos, const vector<int>& a, vector<int>& cur,
                 vector<vector<int>>& semua) {
    if (pos == (int)a.size()) {
        semua.push_back(cur);
        return;
    }
    enum_subset(pos + 1, a, cur, semua);   // tidak ambil a[pos]
    cur.push_back(a[pos]);
    enum_subset(pos + 1, a, cur, semua);   // ambil
    cur.pop_back();                        // mundur (backtrack)
}

int main() {
    vector<int> a = {1, 2, 3};
    vector<int> cur;
    vector<vector<int>> semua;
    enum_subset(0, a, cur, semua);
    cout << "jumlah = " << semua.size() << '\n';
    for (auto& s : semua) {
        cout << "{";
        for (size_t i = 0; i < s.size(); i++) {
            if (i) cout << ',';
            cout << s[i];
        }
        cout << "}\n";
    }
    return 0;
}
```

**Jebakan:** lupa `pop_back()` — subset berikutnya membawa barang lama; menghitung daun di tengah jalan, bukan saat `pos == n`; `n = 25` TLE; menyalin `cur` by value di setiap panggilan (lambat, tetapi benar).

**Kompleksitas:** waktu `O(2^n · n)` jika tiap subset disalin. Memori hasil `O(2^n · n)`, stack `O(n)`.

---

## Operasi bitmask

**Teori:** himpunan `n` elemen muat di satu bilangan: bit ke-`i` hidup artinya elemen `i` masuk. Analoginya deretan saklar. Operasi himpunan jadi operasi bit: gabungan `|`, irisan `&`, beda simetris `^`, komplemen di `n` bit `~x & ((1<<n)-1)`. Kenapa benar: setiap bit independen, jadi operator bit = operator koordinat ke koordinat pada vektor `{0,1}^n`.

**Kapan:** `n ≤ 20` (pakai `int` / `1 << n`), atau `n ≤ 60` (`1LL << n`). State DP himpunan, cek kepemilikan, enumerasi. Jangan `1 << n` untuk `n ≥ 31` pada `int`. Jangan `~x` mentah jika kamu hanya ingin `n` bit — bit tinggi ikut terbalik.

**Proses:** elemen `{A,B,C,D}` = indeks `{0,1,2,3}`. Himpunan `{A,C}` = bit 0 dan 2 = `0101_2 = 5`.

| mask | biner | himpunan |
| ---: | --- | --- |
| 0 | 0000 | {} |
| 1 | 0001 | {A} |
| 5 | 0101 | {A,C} |
| 10 | 1010 | {B,D} |
| 15 | 1111 | {A,B,C,D} |

Operasi pada `mask = 10` (`1010`, {B,D}):

```
cek bit 1: (10 >> 1) & 1 = 1      B ada
set bit 0: 10 | 1 = 11 (1011)    {A,B,D}
clear bit 3: 10 & ~(8) = 2       {B}
toggle bit 2: 10 ^ 4 = 14 (1110) {B,C,D}
lowbit: 10 & -10 = 2             bit 1
hapus lowbit: 10 & 9 = 8         {D}
popcount(10) = 2
```

Irisan `{A,C}=5` dan `{A,B}=3`: `5 & 3 = 1` = `{A}`. Gabungan `5 | 3 = 7` = `{A,B,C}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool bit_on(int mask, int i) { return (mask >> i) & 1; }
int set_bit(int mask, int i) { return mask | (1 << i); }
int clear_bit(int mask, int i) { return mask & ~(1 << i); }
int tog_bit(int mask, int i) { return mask ^ (1 << i); }
int lowbit(int mask) { return mask & -mask; }
int popc(int mask) { return __builtin_popcount(mask); }

vector<int> elemen(int mask, int n) {
    vector<int> isi;
    for (int i = 0; i < n; i++)
        if (bit_on(mask, i)) isi.push_back(i);
    return isi;
}

int main() {
    int mask = 10; // 1010
    cout << bit_on(mask, 1) << '\n';          // 1
    cout << set_bit(mask, 0) << '\n';         // 11
    cout << clear_bit(mask, 3) << '\n';       // 2
    cout << tog_bit(mask, 2) << '\n';         // 14
    cout << lowbit(mask) << ' ' << popc(mask) << '\n'; // 2 2
    auto isi = elemen(5, 4);
    for (int x : isi) cout << x << ' ';       // 0 2
    cout << '\n';
    return 0;
}
```

**Jebakan:** `1 << 31` *undefined behavior* pada `int` bertanda; `1LL << 63` sama berbahayanya; `~mask` 32-bit mengubah bit tanda; `__builtin_popcount` untuk `int`, pakai `ll` → `__builtin_popcountll`; `mask & -mask` butuh representasi two's complement (selalu di CP modern).

**Kompleksitas:** tiap operasi `O(1)`. Menulis isi mask `O(n)`.

---

## Enumerasi subset dengan bitmask

**Teori:** semua himpunan bagian dari `{0..n-1}` adalah bilangan `0, 1, …, 2^n - 1`. Loop `for (mask = 0; mask < (1<<n); mask++)` mengunjungi semuanya. Di dalam, bit yang hidup = elemen yang dipilih. Ini **sama** dengan pohon ambil/tidak, hanya ditulis iteratif. Kenapa lengkap dan tanpa duplikat: setiap vektor bit muncul tepat sekali sebagai bilangan.

**Kapan:** `n ≤ 20` standar kontes (2^20 ≈ 1e6). Subset sum naif, TSP intro, cek sifat “untuk setiap himpunan”. Jangan jika `n = 28` dan kerja per mask `O(n)` — 28·268 juta berat. Untuk `n = 40` belah jadi meet in the middle (file 05).

**Proses:** `a = {4, 7, 2}`, `n = 3`. Cari subset berjumlah 6? Tidak ada. Jumlah 13 = `{4,7,2}`. Jumlah 11 = `{4,7}`.

Tabel lengkap:

| mask | bit | isi | jumlah |
| ---: | --- | --- | ---: |
| 0 | 000 | {} | 0 |
| 1 | 001 | {4} | 4 |
| 2 | 010 | {7} | 7 |
| 3 | 011 | {4,7} | 11 |
| 4 | 100 | {2} | 2 |
| 5 | 101 | {4,2} | 6 |
| 6 | 110 | {7,2} | 9 |
| 7 | 111 | {4,7,2} | 13 |

Ada subset jumlah 6: mask `5`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool ada_jumlah(const vector<int>& a, ll target) {
    int n = (int)a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += a[i];
        if (s == target) return true;
    }
    return false;
}

vector<int> salah_satu(const vector<int>& a, ll target) {
    int n = (int)a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += a[i];
        if (s == target) {
            vector<int> isi;
            for (int i = 0; i < n; i++)
                if (mask & (1 << i)) isi.push_back(a[i]);
            return isi;
        }
    }
    return {};
}

int main() {
    vector<int> a = {4, 7, 2};
    cout << ada_jumlah(a, 6) << '\n';     // 1
    cout << ada_jumlah(a, 8) << '\n';     // 0
    auto isi = salah_satu(a, 6);
    for (int x : isi) cout << x << ' ';   // 4 2
    cout << '\n';
    return 0;
}
```

Optimasi kecil: jumlah mask `m` dan mask `m` tanpa lowbit berbeda satu elemen. Bisa `O(2^n)` murni dengan DP SOS / Gray code, tetapi loop ganda di atas sudah cukup untuk `n ≤ 20`.

**Jebakan:** `1 << n` saat `n = 31`; menjumlah `int` overflow; lupa mask `0` (subset kosong, jumlah 0 — sering jawaban sah); `mask & (1 << i)` vs `(mask >> i) & 1` tertukar prioritas — kurung wajib.

**Kompleksitas:** waktu `O(2^n · n)`, memori `O(1)` plus keluaran.

---

## Subset dari sebuah mask dan enumerasi 3^n

**Teori:** kadang kamu sudah punya himpunan `mask`, lalu ingin semua subset-nya. Trik: `sub = (sub - 1) & mask` berjalan dari `mask` turun ke subset tak kosong, lalu proses `0` terpisah. Kenapa jalan: `sub - 1` mematikan lowbit dan menyalakan bit di kanannya; `& mask` membuang bit yang bukan milik `mask`, jadi `sub` tetap subset.

Enumerasi **subset-of-subset** untuk semua mask: untuk tiap elemen, tiga pilihan — tidak masuk mask, masuk mask tapi tidak masuk sub, atau masuk keduanya. Itu `3^n`. Dipakai di DP transisi “pecah himpunan”.

**Kapan:** enumerasi subset sebuah grup, TSP / assignment transisi, SOS intro. `n ≤ 14` untuk `3^n` murni (`3^14 ≈ 4.7e6`), `n ≤ 18` jika konstan kecil. Jangan `3^n` untuk `n = 20` (`3.4e9`).

**Proses:** `mask = 13` = `1101` = bit `{0,2,3}`.

```
sub = 13 (1101)
sub = 12 (1100)
sub = 9  (1001)
sub = 8  (1000)
sub = 5  (0101)
sub = 4  (0100)
sub = 1  (0001)
lalu 0   (0000)  ← ditambah manual
```

Delapan nilai = `2^{popcount(13)} = 2^3 = 8`. Tidak ada `0010` karena bit 1 tidak milik mask.

Untuk `n = 2`, semua pasangan `(mask, sub ⊆ mask)`:

| mask | sub yang sah |
| ---: | --- |
| 00 | 00 |
| 01 | 00, 01 |
| 10 | 00, 10 |
| 11 | 00, 01, 10, 11 |

Total `1+2+2+4 = 9 = 3^2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> subset_dari_mask(int mask) {
    vector<int> res;
    for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
        res.push_back(sub);
    res.push_back(0);
    return res;
}

ll enum_3n(int n, function<void(int,int)> kerja) {
    ll hit = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int sub = mask; ; sub = (sub - 1) & mask) {
            kerja(mask, sub);
            hit++;
            if (sub == 0) break;
        }
    }
    return hit;
}

int main() {
    auto s = subset_dari_mask(13);
    for (int x : s) cout << x << ' ';
    cout << '\n';
    ll hit = enum_3n(3, [](int, int) {});
    cout << "3^3 = " << hit << '\n';          // 27
    return 0;
}
```

Loop dalam **harus** `if (sub == 0) break` setelah memproses. Kalau `for (sub = mask; sub; sub = (sub-1)&mask)` maka `0` terlewat.

**Jebakan:** lupa subset kosong; `sub = (sub-1) & mask` pada `sub = 0` menjadi `(-1) & mask = mask` → loop tak berujung jika kamu tidak `break`; overflow `1 << n`.

**Kompleksitas:** subset satu mask `O(2^{popcount})`. Semua pasangan `O(3^n)`. Memori `O(1)` plus keluaran.

---

## Enumerasi permutasi

**Teori:** permutasi adalah urutan semua elemen tepat sekali. Rekursi: pilih siapa di posisi `pos`, tandai `used`, lanjut `pos+1`, lalu lepas tanda. Analoginya mengisi kursi satu per satu dari sisa orang. `n!` daun. Iteratif: `next_permutation` pada array terurut.

**Kapan:** `n ≤ 8` kalau kerja per permutasi `O(n)` atau lebih (`8! = 40320`, `9! = 362880`, `10! = 3.6e6`, `11! = 4e7` sudah berat). Jadwal, assignment kecil, cek semua urutan. Untuk `n = 12` jangan brute. Ada duplikat? Sort dulu, skip nilai sama yang sudah dipakai.

**Proses:** `{1,2,3}`.

```
pos0 pilih 1 → pos1 pilih 2 → pos2 pilih 3 → 1 2 3
                 pos1 pilih 3 → pos2 pilih 2 → 1 3 2
pos0 pilih 2 → 2 1 3 , 2 3 1
pos0 pilih 3 → 3 1 2 , 3 2 1
```

Enam permutasi. `next_permutation` dari `1 2 3` menghasilkan urutan leksikografis yang sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void permute(int pos, vector<int>& a, vector<int>& used, vector<int>& cur,
             vector<vector<int>>& semua) {
    int n = (int)a.size();
    if (pos == n) {
        semua.push_back(cur);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = 1;
        cur[pos] = a[i];
        permute(pos + 1, a, used, cur, semua);
        used[i] = 0;
    }
}

vector<vector<int>> permute_stl(vector<int> a) {
    sort(a.begin(), a.end());
    vector<vector<int>> semua;
    do {
        semua.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return semua;
}

int main() {
    vector<int> a = {1, 2, 3};
    vector<int> used(3, 0), cur(3);
    vector<vector<int>> semua;
    permute(0, a, used, cur, semua);
    cout << semua.size() << '\n';             // 6
    auto b = permute_stl(a);
    cout << b.size() << ' ' << b.back()[0] << b.back()[1] << b.back()[2] << '\n';
    // 6 321
    return 0;
}
```

**Jebakan:** lupa `used[i] = 0`; `next_permutation` tanpa `sort` awal hanya jalan dari urutan sekarang sampai habis, bukan semua jika input belum terurut; duplikat `1,1,2` tanpa skip menghasilkan twin; `n = 11` TLE.

**Kompleksitas:** waktu `O(n! · n)` jika menyalin. Stack `O(n)`. STL sama secara asimtotik, konstanta lebih baik.

---

## Pola backtracking: coba, lanjut, mundur

**Teori:** backtracking adalah rekursi plus **undo**. Kamu memasang satu pilihan, memanggil rekursi, lalu **mengembalikan state persis seperti semula**. Analoginya maze: maju, kalau buntu mundur satu langkah, coba lorong lain. Tiga baris mental: **pilih → rekursi → batal**. Pruning memotong cabang yang sudah mustahil sebelum daun.

**Kapan:** bangun objek dengan syarat (kurung sah, papan catur, sudoku, IP address, subset dengan constraint). Ruang pencarian terbatas atau bisa dipangkas. Jangan jika submasalah overlap berat tanpa memo — itu DP. Jangan jika `n` besar tanpa pruning kuat.

**Proses:** kurung sah `n = 2` (dua buka, dua tutup). State: `buka` terpakai, `tutup` terpakai, string `cur`. Syarat: `tutup ≤ buka` di setiap awalan, total masing-masing `n`.

```
""
  "("  buka=1 tutup=0
    "((" buka=2
      "(()" 
        "(())"  selesai
    "()" buka=1 tutup=1
      "()("
        "()()"  selesai
```

Dua hasil: `(())` dan `()()`. Cabang `")..."` dipotong karena `tutup > buka`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void kurung(int buka, int tutup, int n, string& cur, vector<string>& semua) {
    if ((int)cur.size() == 2 * n) {
        semua.push_back(cur);
        return;
    }
    if (buka < n) {
        cur.push_back('(');
        kurung(buka + 1, tutup, n, cur, semua);
        cur.pop_back();
    }
    if (tutup < buka) {
        cur.push_back(')');
        kurung(buka, tutup + 1, n, cur, semua);
        cur.pop_back();
    }
}

int main() {
    string cur;
    vector<string> semua;
    kurung(0, 0, 2, cur, semua);
    for (auto& s : semua) cout << s << '\n';
    // (())
    // ()()
    return 0;
}
```

Pola yang sama untuk hampir semua soal backtracking:

```
void dfs(state):
    if selesai: catat; return
    if mustahil: return          // pruning
    for pilihan p:
        pasang(p)
        dfs(state')
        cabut(p)                 // wajib
```

**Jebakan:** undo tidak simetris (mengeset `board[i]=1` lalu lupa `=0`); memangkas terlalu agresif sampai jawaban hilang; memangkas terlalu longgar sampai TLE; mengubah variabel global tanpa restore.

**Kompleksitas:** kurung sah adalah Catalan `C_n` daun (file 09), waktu `O(C_n · n)`. Umumnya: ukuran pohon setelah pruning, sulit rumus tertutup — ukur `n` kecil lalu extrapolasi.

---

## N-Queens

**Teori:** taruh `n` ratu di papan `n×n` supaya tidak ada dua yang sebaris, sekolom, atau sediagonal. Backtracking baris demi baris: di baris `r` coba kolom `c` yang aman, lalu baris `r+1`. Kolom dipakai disimpan di `col[c]`. Diagonal `/` punya `r+c` konstan. Diagonal `\` punya `r-c` konstan (geser `+ n-1` agar indeks ≥ 0). Kenapa lengkap: setiap solusi punya tepat satu ratu per baris (kalau tidak, pigeonhole).

**Kapan:** `n ≤ 14` hitung solusi (`n=14` ~ 365 ribu, `n=15` ~ 2 juta). Soal klasik, latihan bitmask kolom/diagonal. Jangan simulasi papan `O(n^2)` per cek jika `n` besar — bitmask `O(1)`.

**Proses:** `n = 4`. Dua solusi (simetris).

Coba baris 0, kolom 0 (A1). Baris 1: kolom 0,1 terlarang (kolom / diagonal). Kolom 2: diagonal `1-2` vs `0-0`? `r-c`: `0-0=0`, `1-2=-1` beda. `r+c`: 0 dan 3 beda. OK. Lanjut... jalur ini akhirnya buntu atau tidak, tergantung cabang.

Satu solusi terkenal (0-index, kolom per baris): `1 3 0 2`

```
baris 0 ratu di kolom 1
. Q . .
. . . Q
Q . . .
. . Q .
```

Cek: kolom `{1,3,0,2}` unik. `r+c = {1,4,2,5}` unik. `r-c = {-1,-2,2,1}` unik. Aman.

Solusi kedua: `2 0 3 1`.

`n = 2` dan `n = 3` nol solusi. `n = 1` satu solusi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int nqueens_hitung(int n) {
    int ans = 0;
    int col = 0, d1 = 0, d2 = 0; // bitmask
    function<void(int)> dfs = [&](int r) {
        if (r == n) {
            ans++;
            return;
        }
        for (int c = 0; c < n; c++) {
            int a = 1 << c;
            int b = 1 << (r + c);
            int d = 1 << (r - c + n - 1);
            if ((col & a) || (d1 & b) || (d2 & d)) continue;
            col ^= a; d1 ^= b; d2 ^= d;
            dfs(r + 1);
            col ^= a; d1 ^= b; d2 ^= d;   // undo lewat XOR
        }
    };
    dfs(0);
    return ans;
}

int main() {
    cout << nqueens_hitung(1) << '\n'; // 1
    cout << nqueens_hitung(2) << '\n'; // 0
    cout << nqueens_hitung(3) << '\n'; // 0
    cout << nqueens_hitung(4) << '\n'; // 2
    cout << nqueens_hitung(8) << '\n'; // 92
    return 0;
}
```

**Jebakan:** lupa geser `r-c` agar tidak negatif; undo tidak lengkap; menghitung rotasi sebagai unik atau tidak — ikuti soal; `1 << (2n-2)` untuk `n = 16` melewati 31.

**Kompleksitas:** kasar `O(n!)` dengan pruning jauh lebih kecil. `n=8` instan, `n=14` masih lolos, `n=16` perlu bit-twiddling lebih agresif. Memori `O(n)` stack plus beberapa `int`.

---

## Combination Sum dan pruning

**Teori:** cari semua kombinasi (boleh ulang atau tidak, tergantung soal) yang jumlahnya `target`. Urutkan array, selalu maju `start` supaya kombinasi tidak muncul dua kali dalam urutan beda (`1,2` dan `2,1` dianggap sama). Pruning: jika `a[i] > sisa`, `break` karena array sudah terurut. Kenapa benar: setiap kombinasi non-menurun dihasilkan tepat sekali.

**Kapan:** `target` dan `n` kecil, atau nilai membesar cepat sehingga pruning kuat. Coin change yang minta **semua** kombinasi. Kalau hanya jumlah cara / minimum koin, DP (folder 09) jauh lebih tepat.

**Proses:** `a = {2, 3, 6, 7}`, `target = 7`, boleh ulang.

```
start=0 sisa=7 cur=[]
  ambil 2 → [2] sisa=5
    ambil 2 → [2,2] sisa=3
      ambil 2 → [2,2,2] sisa=1  (2>1 stop)
      ambil 3 → [2,2,3] sisa=0  JAWAB
    ambil 3 → [2,3] sisa=2  (3>2 stop)
  ambil 3 → [3] sisa=4
    ambil 3 → [3,3] sisa=1 stop
  ambil 6 → [6] sisa=1 stop
  ambil 7 → [7] sisa=0 JAWAB
```

Jawaban: `{2,2,3}` dan `{7}`.

Tanpa sort + break, kamu tetap benar tetapi lebih lambat, dan tanpa `start` kamu menggandakan urutan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void comb_sum(int start, ll sisa, vector<int>& a, vector<int>& cur,
              vector<vector<int>>& semua) {
    if (sisa == 0) {
        semua.push_back(cur);
        return;
    }
    for (int i = start; i < (int)a.size(); i++) {
        if (a[i] > sisa) break;            // pruning, a terurut
        cur.push_back(a[i]);
        comb_sum(i, sisa - a[i], a, cur, semua); // i = boleh ulang
        cur.pop_back();
    }
}

void comb_sum_sekali(int start, ll sisa, vector<int>& a, vector<int>& cur,
                     vector<vector<int>>& semua) {
    if (sisa == 0) {
        semua.push_back(cur);
        return;
    }
    for (int i = start; i < (int)a.size(); i++) {
        if (i > start && a[i] == a[i - 1]) continue; // skip duplikat
        if (a[i] > sisa) break;
        cur.push_back(a[i]);
        comb_sum_sekali(i + 1, sisa - a[i], a, cur, semua);
        cur.pop_back();
    }
}

int main() {
    vector<int> a = {2, 3, 6, 7};
    sort(a.begin(), a.end());
    vector<int> cur;
    vector<vector<int>> semua;
    comb_sum(0, 7, a, cur, semua);
    cout << semua.size() << '\n';          // 2
    for (auto& s : semua) {
        for (int x : s) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
```

**Jebakan:** `comb_sum(i+1)` padahal soal boleh ulang (kehilangan `{2,2,3}`); sebaliknya `i` padahal soal 1 kali pakai; lupa sort sebelum `break`; duplikat input `{2,2,3}` menghasilkan `{2,3}` dua kali tanpa skip.

**Kompleksitas:** tergantung target dan nilai. Terburuk eksponensial. Pruning + sort memangkas banyak jika `a[i]` besar.

---

## Subset Sum plus rekonstruksi

**Teori:** “apakah ada subset berjumlah `S`?” plus “berikan satu subsetnya”. Rekursi `pos, sisa`: lewat elemen atau ambil jika `a[pos] ≤ sisa`. Rekonstruksi: simpan pilihan yang sukses, atau setelah tahu `ya`, telusuri ulang. Untuk `n ≤ 20` bitmask lebih pendek. Untuk `n = 40, S ≤ 1e6` memo/DP. Kenapa backtracking cukup di `n` kecil: ruang `2^n`.

**Proses:** `a = {3, 1, 7, 4}`, `S = 8`.

```
pos0 3: ambil → sisa 5
  pos1 1: ambil → sisa 4
    pos2 7: 7>4 skip
    pos3 4: ambil → sisa 0  YA {3,1,4}
```

Jalur lain `{1,7}` juga 8. `{4,3,1}` sama dengan jalur pertama. `{8}` tidak ada.

Tanpa solusi: `S = 2` — semua jalur gagal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool subset_sum(int pos, ll sisa, const vector<ll>& a, vector<ll>& pilih) {
    if (sisa == 0) return true;
    if (pos == (int)a.size() || sisa < 0) return false;
    // ambil
    pilih.push_back(a[pos]);
    if (subset_sum(pos + 1, sisa - a[pos], a, pilih)) return true;
    pilih.pop_back();
    // tidak ambil
    return subset_sum(pos + 1, sisa, a, pilih);
}

int main() {
    vector<ll> a = {3, 1, 7, 4};
    vector<ll> pilih;
    bool ok = subset_sum(0, 8, a, pilih);
    cout << ok << '\n';                    // 1
    ll s = 0;
    for (ll x : pilih) {
        cout << x << ' ';
        s += x;
    }
    cout << "\njumlah=" << s << '\n';      // 3 1 4  jumlah=8
    pilih.clear();
    cout << subset_sum(0, 2, a, pilih) << '\n'; // 0
    return 0;
}
```

**Jebakan:** `sisa < 0` tidak dicek (jalan terus); merekonstruksi dari indeks yang salah; `n = 40` tanpa memo TLE; angka negatif — kasus dasar `sisa < 0` tidak lagi sah, harus enumerasi penuh.

**Kompleksitas:** `O(2^n)` waktu, stack `O(n)`. Dengan memo `(pos, sisa)` menjadi `O(n · S)` (lihat bawah).

---

## Memoization: tiga baris sakti

**Teori:** memo adalah buku catatan untuk rekursi. Sebelum menghitung state, cek catatan. Kalau sudah ada, langsung pakai. Kalau belum, hitung sekali, tulis, baru `return`. Analoginya PR yang sama dikumpulkan satu kunci jawaban. Tiga baris: cek cache, hitung, simpan. Overlapping subproblems hilang; setiap state dihitung paling banyak sekali. Itu jembatan ke DP: tabel yang sama, diisi malas (top-down).

**Kapan:** rekursi alami, tidak semua state terpakai, atau kamu belum yakin urutan isi tabel. Fibonacci, tangga, knapsack, LCS, digit DP. Jangan jika kedalaman `1e5` rantai — stack overflow, pindah bottom-up. Jangan sentinel `-1` jika jawaban sah bisa `-1`.

**Proses:** `fib_memo(5)`, cache awal semua `-1`.

```
fib(5) miss → fib(4)+fib(3)
  fib(4) miss → fib(3)+fib(2)
    fib(3) miss → fib(2)+fib(1)
      fib(2) miss → fib(1)+fib(0) = 1+0, memo[2]=1
      fib(1) = 1
    memo[3]=2
    fib(2) HIT 1
  memo[4]=3
  fib(3) HIT 2
memo[5]=5
```

Setelah itu `fib(5)` lagi = satu kali baca cache. Panggilan unik: `0..5` saja.

| n | naif | memo |
| --- | ---: | ---: |
| 20 | 21 891 | 21 state |
| 40 | 331 juta | 41 state |
| 90 | mustahil | 91 state, hati-hati overflow ll |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10005;
ll memo[MAXN];

ll fib_memo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];     // HIT
    return memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
}

void reset_memo(int n) {
    for (int i = 0; i <= n; i++) memo[i] = -1;
}

int main() {
    reset_memo(50);
    cout << fib_memo(10) << '\n';          // 55
    cout << fib_memo(40) << '\n';          // 102334155
    cout << fib_memo(50) << '\n';          // 12586269025
    return 0;
}
```

Sentinel terpisah jika 0 atau -1 bisa jawaban:

```cpp
bool seen[MAXN];
ll dp[MAXN];

ll f(int n) {
    if (n <= 1) return n;
    if (seen[n]) return dp[n];
    seen[n] = true;
    return dp[n] = f(n - 1) + f(n - 2);
}
```

State jarang / koordinat `1e9`: `map<ll,ll>` atau `unordered_map`.

**Jebakan:** lupa `memset` / reset antar testcase; `return f(...)` tanpa `memo[s]=`; sentinel bentrok; state kurang dimensi (fungsi baca global yang berubah); `vector` memo di dalam fungsi rekursif — disalin, cache mati.

**Kompleksitas:** waktu `O(jumlah state × kerja transisi)`. Fibonacci `O(n)`. Memori `O(n)` tabel plus `O(n)` stack.

---

## Memo tangga dan knapsack

**Teori:** dua pola yang paling sering diubah dari rekursi jadi DP. **Tangga:** `naik(i) = naik(i-1) + naik(i-2)` — cara menuju undak `i`. **0-1 knapsack:** `knap(i, sisa)` = max dari “lewati barang `i`” dan “ambil jika muat”. State harus lengkap: semua yang memengaruhi keputusan masa depan masuk parameter. Transisi = keputusan. Basis = tidak ada barang / indeks di luar / kapasitas 0.

**Kapan:** `n` undak sampai `1e5` (lebih aman bottom-up), knapsack `n ≤ 100`, `W ≤ 1e5` atau `n ≤ 40` meet in the middle. Jangan knapsack memo `n=100, W=1e9` — tabel tidak muat. Jangan tangga naif tanpa memo.

**Proses tangga:** `n = 4` undak, langkah 1 atau 2.

```
naik(4) = naik(3)+naik(2)
naik(3) = naik(2)+naik(1)
naik(2) = naik(1)+naik(0)
naik(1) = 1   (satu langkah)
naik(0) = 1   (sudah di tanah, 1 cara: tidak jalan)
```

Jadi `naik(2)=2` yaitu `1+1` dan `2`. `naik(3)=3`, `naik(4)=5`. Urutan cara untuk 4: `1+1+1+1`, `1+1+2`, `1+2+1`, `2+1+1`, `2+2`.

**Proses knapsack:** barang `(berat, nilai) = (2,3), (3,4), (4,5)`, `W = 5`.

```
knap(0,5) = max( knap(1,5),  3 + knap(1,3) )
knap(1,5) = max( knap(2,5),  4 + knap(2,2) )
knap(2,5) = max( knap(3,5)=0, 5 + knap(3,1)=5 ) = 5
knap(2,2) = 0  (4>2)
knap(1,5) = max(5, 4+0) = 5
knap(1,3) = max( knap(2,3)=0, 4 + knap(2,0)=4 ) = 4
knap(0,5) = max(5, 3+4=7) = 7
```

Ambil barang 0 dan 1: berat 5, nilai 7. Tidak bisa 3+4+5.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll memo_t[10005];

ll naik(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (memo_t[n] != -1) return memo_t[n];
    return memo_t[n] = naik(n - 1) + naik(n - 2);
}

const int MAXN = 105, MAXW = 10005;
ll memo_k[MAXN][MAXW];
int nbarang;
ll wt[MAXN], val[MAXN];

ll knap(int i, int sisa) {
    if (i == nbarang) return 0;
    if (memo_k[i][sisa] != -1) return memo_k[i][sisa];
    ll ans = knap(i + 1, sisa);
    if (wt[i] <= sisa)
        ans = max(ans, val[i] + knap(i + 1, (int)(sisa - wt[i])));
    return memo_k[i][sisa] = ans;
}

int main() {
    memset(memo_t, -1, sizeof(memo_t));
    cout << naik(4) << '\n';               // 5

    nbarang = 3;
    wt[0] = 2; val[0] = 3;
    wt[1] = 3; val[1] = 4;
    wt[2] = 4; val[2] = 5;
    memset(memo_k, -1, sizeof(memo_k));
    cout << knap(0, 5) << '\n';            // 7
    return 0;
}
```

**Jebakan:** `naik(0)` harus 1, bukan 0 (kecuali soal menghitung undak yang sudah dilangkah beda definisi); knapsack `sisa` jadi indeks negatif jika tidak cek `wt[i] <= sisa`; `memset` pada `ll` `-1` sah (semua bit 1), tetapi `memset(arr, 0x3f, ...)` untuk `ll` perlu hati-hati; `W` jadi indeks array — kompres atau ganti map jika `W` besar.

**Kompleksitas:** tangga `O(n)` waktu dan memori. Knapsack `O(n · W)` waktu dan memori, plus stack `O(n)`.

---

## Dari memo ke tabel bottom-up

**Teori:** tabel memo dan tabel DP adalah benda yang sama. Bedanya urutan isi. Top-down: “butuh state ini, hitung dependensinya dulu”. Bottom-up: “isi dari kasus dasar menuju soal besar, sesuai dependensi”. Analoginya masak: memo = masak bahan saat dibutuhkan; bottom-up = masak dari yang paling sederhana menurut resep. Jawaban sama jika transisi sama.

**Kapan:** pindah ke bottom-up jika stack dalam, atau butuh rolling array, atau loop lebih cepat (cache CPU). Tetap memo jika state jarang (hanya 1% sel hidup) atau transisi sulit diurutkan. Jangan mengisi tabel tanpa memastikan urutan: memakai `dp[i]` sebelum `dp[i-1]` siap.

**Proses:** Fibonacci n=6.

Memo (urutan hitung pertama kali): `1, 0, 2, 3, 4, 5, 6` — meloncat sesuai pohon, tetapi tiap angka sekali.

Bottom-up:

```
dp[0]=0
dp[1]=1
i=2: dp[2]=0+1=1
i=3: 1+1=2
i=4: 1+2=3
i=5: 2+3=5
i=6: 3+5=8
```

Tangga n=4, array `dp[0..4]`: `1,1,2,3,5`.

Knapsack 0-1, isi dari `i = n-1` turun ke `0`, atau loop barang lalu kapasitas **turun** (supaya tiap barang sekali):

```
W=5, barang (2,3), (3,4), (4,5)
dp = [0,0,0,0,0,0]
ambil (2,3): dp[5..2] ← max(lama, 3+dp[w-2])
  dp = [0,0,3,3,3,3]
ambil (3,4):
  w=5: max(3, 4+dp[2]=7)=7
  w=4: max(3, 4+dp[1]=4)=4
  w=3: max(3, 4+0)=4
  dp = [0,0,3,4,4,7]
ambil (4,5):
  w=5: max(7, 5+dp[1]=5)=7
  w=4: max(4, 5+0)=5
  dp = [0,0,3,4,5,7]
```

Jawaban `dp[5]=7`, sama dengan memo.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fib_up(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = a + b;
        a = b;
        b = c;
    }
    return b;
}

ll naik_up(int n) {
    if (n <= 1) return 1;
    vector<ll> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

ll knap_up(const vector<ll>& wt, const vector<ll>& val, int W) {
    vector<ll> dp(W + 1, 0);
    int n = (int)wt.size();
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--)
            dp[w] = max(dp[w], val[i] + dp[w - (int)wt[i]]);
    }
    return dp[W];
}

int main() {
    cout << fib_up(10) << '\n';            // 55
    cout << naik_up(4) << '\n';            // 5
    cout << knap_up({2, 3, 4}, {3, 4, 5}, 5) << '\n'; // 7
    return 0;
}
```

**Jebakan:** knapsack loop kapasitas **naik** untuk 0-1 — barang terpakai berkali-kali (itu unbounded); off-by-one `dp[n]` vs `dp[n-1]`; menyalin kode memo ke loop tanpa meniru dependensi; mengira bottom-up selalu lebih hemat — kalau state jarang, memo menang.

**Kompleksitas:** sama dengan jumlah sel tabel × transisi. Fibonacci `O(n)` atau `O(1)` memori rolling. Knapsack `O(nW)` waktu, `O(W)` memori.

---

## Rekursi pada grid dan flood fill

**Teori:** sel grid adalah graf: tepi ke tetangga 4-arah (kadang 8). Flood fill = DFS/BFS mewarnai komponen terhubung. Rekursi: dari `(r,c)`, kunjungi tetangga yang masih dalam batas, belum dikunjungi, dan sewarna / boleh dilalui. Tandai **sebelum** rekursi agar tidak bolak-balik. Analoginya tuang cat di peta.

**Kapan:** hitung pulau, luas daerah, jarak di labirin kecil, generate jalur. Grid `n, m ≤ 1000` lebih aman BFS / DFS iteratif — DFS rekursif pada ular panjang `n*m = 1e6` RTE stack. Jangan flood fill `O(n^2)` per query tanpa DSU / prefix jika query banyak.

**Proses:** peta 4×5, `'#'` tembok, `'.'` tanah. Mulai `(0,0)`.

```
. # . . .
. # . # .
. . . # .
# # . . .
```

DFS 4-arah dari (0,0):

```
(0,0) → (1,0) → (2,0) → (2,1) → (2,2) → (1,2) → (0,2) → (0,3) → (0,4)
                                    ↘ (3,2) → (3,3) → (3,4)
```

`(1,4)` terhalang `#` di (1,3) dan tidak tersambung lewat 4-arah dari (0,4)? (0,4) ke (1,4) ya, jika (1,4) adalah `.` — di peta (1,4)=`.` jadi ikut. Komponen kiri-atas+bawah menyatu lewat (2,2). Satu pulau besar, minus sel terpisah? (1,4) tersambung (0,4). Semua `.` terhubung kecuali tidak ada yang terpisah. Hitung: total `.` = 13. Ya satu komponen.

Grid lebih kecil untuk hitung pasti, 3×3:

```
1 1 0
0 1 0
1 0 1
```

Flood dari (0,0) mewarnai tiga sel `1` di sudut kiri-atas (0,0),(0,1),(1,1). (2,0) dan (2,2) komponen lain. Jumlah pulau = 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
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
    vector<vector<int>> g = {
        {1, 1, 0},
        {0, 1, 0},
        {1, 0, 1}
    };
    cout << hitung_pulau(g) << '\n';       // 3
    vector<vector<int>> vis(3, vector<int>(3, 0));
    cout << flood(0, 0, g, vis) << '\n';   // 3
    return 0;
}
```

**Jebakan:** cek batas **setelah** akses `g[r][c]` → RTE; lupa `vis` → rekursi tak hingga bolak-balik; 8-arah vs 4-arah salah baca soal; DFS rekursif grid 1000×1000 ular; memodifikasi `g` in-place lalu butuh peta asli lagi.

**Kompleksitas:** waktu `O(n · m)` untuk satu sapuan penuh (tiap sel masuk queue/stack sekali). Stack rekursif terburuk `O(n · m)`.

---

## Peta keputusan bab ini

```
Soal "coba semua"
├── himpunan bagian, n ≤ 20          → bitmask / subset rekursif
├── urutan, n ≤ 8..10                → permutasi / next_permutation
├── bangun dengan syarat + undo      → backtracking + pruning
├── pecah mask jadi sub              → loop (sub-1)&mask , 3^n
└── n = 40 belah dua                 → meet in the middle (file 05)

Soal "nilai optimal / banyak cara" dengan submasalah berulang
├── rekursi alami, state jarang      → memo top-down
├── semua state terpakai / n besar   → bottom-up
└── kedalaman 1e5                    → jangan DFS rekursif

Soal grid
├── komponen / luas                  → flood fill
└── jalur terpendek                  → BFS, bukan rekursi naif
```

| n | 2^n | n! | 3^n | aman brute? |
| ---: | ---: | ---: | ---: | --- |
| 8 | 256 | 4e4 | 6561 | ya, hampir semua |
| 10 | 1024 | 3.6e6 | 59049 | permutasi pas-pasan |
| 12 | 4096 | 4.8e8 | 5e5 | permutasi jangan |
| 15 | 3e4 | — | 1.4e7 | 3^n berat |
| 20 | 1e6 | — | 3e9 | bitmask O(n 2^n) ok |
| 24 | 1.6e7 | — | — | hanya kerja O(1) per mask |

---

## Ringkasan folder 05

1. **Rekursi** butuh kasus dasar dan input yang mengecil. Stack = memori tersembunyi.
2. **Subset** = pohon 2^n atau loop mask. **Permutasi** = n!. **3^n** = subset-of-subset.
3. **Backtracking** = pasang, rekursi, cabut. Pruning memotong yang mustahil.
4. **Memo** mengubah pohon eksponensial menjadi tabel state. Tiga baris: cek, hitung, simpan.
5. **Bottom-up** adalah tabel yang sama, diisi dari dasar. Pilih gaya yang stack-nya aman.
6. Fibonacci naif, Hanoi, N-Queens, knapsack memo, flood fill — satu keluarga: pecah, coba, ingat.

Lanjut ke [07 greedy, interval, konstruktif](07-greedy-interval-konstruktif.md) jika pilihan lokal sudah terasa “jelas”, atau ke [08 teori bilangan](08-number-sieve-gcd-modular.md) jika soalnya tentang sisa bagi dan prima.
