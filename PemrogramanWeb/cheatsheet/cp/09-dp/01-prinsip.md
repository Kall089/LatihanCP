# 01 — Prinsip DP

[← 09-dp](README.md) · [Top-down / bottom-up →](02-topdown-bottomup.md)

Day ComprogLearning: **141**. Latihan harian tetap di folder Day itu. Jangan menyalin `latihan/`, `solusi/`, atau `tugas/` ke sini.

> **Ide satu kalimat:** DP adalah rekursi yang menolak menghitung submasalah yang sama dua kali.

Sebelum mengetik tabel, jawab tiga pertanyaan dengan **kalimat lengkap**. Kalau STATE tidak muat satu kalimat, definisinya belum siap.

```
1. STATE     : dp[...] artinya apa? (bukan "jawabannya")
2. TRANSISI  : dihitung dari state mana, operator apa (+ / max / min / ||)
3. BASIS     : state terkecil nilainya berapa, dan kenapa?
```

## Daftar isi

- [Apa itu dynamic programming](#apa-itu-dynamic-programming)
- [Analogi buku catatan PR](#analogi-buku-catatan-pr)
- [Overlapping subproblem](#overlapping-subproblem)
- [Pohon Fibonacci tanpa catatan](#pohon-fibonacci-tanpa-catatan)
- [Optimal substructure](#optimal-substructure)
- [Kapan DP gagal](#kapan-dp-gagal)
- [Tiga pertanyaan merancang DP](#tiga-pertanyaan-merancang-dp)
- [Fibonacci: polos, memo, tabulasi, rolling](#fibonacci-polos-memo-tabulasi-rolling)
- [Naik tangga sebagai keputusan terakhir](#naik-tangga-sebagai-keputusan-terakhir)
- [Empat pola transisi](#empat-pola-transisi)
- [Rumus kompleksitas](#rumus-kompleksitas)
- [Checklist Day 141](#checklist-day-141)

---

## Apa itu dynamic programming

**Teori:** Dynamic programming menyusun jawaban besar dari jawaban submasalah yang sudah dihitung sekali, lalu disimpan. Setiap soal DP adalah DAG: simpul adalah state, sisi adalah transisi. Rekursi polos menelusuri DAG itu tanpa cache, sehingga simpul yang sama dikunjungi berkali-kali. DP menambahkan catatan: setelah sebuah simpul selesai, kunjungan berikutnya hanya membaca. Dua syarat wajib harus ada bersama. Overlapping subproblem artinya submasalah yang sama muncul di banyak cabang. Optimal substructure artinya jawaban terbaik keseluruhan bisa disusun dari jawaban terbaik bagian-bagiannya. Kalau overlapping hilang, menyimpan jawaban sia-sia. Kalau optimal substructure rusak, menggabungkan jawaban lokal menghasilkan solusi yang tidak sah.

**Kapan:** soal meminta banyak cara, nilai maksimum atau minimum, atau "bisa / tidak" pada ruang keputusan yang saling menumpuk. **Tidak:** keputusan lokal selalu benar dan bisa dibuktikan dengan exchange argument (itu greedy), atau setiap submasalah hanya muncul sekali (itu divide and conquer murni).

**STATE:** `dp[n]` adalah jawaban lengkap untuk submasalah berukuran `n`, ditulis sebagai satu kalimat yang menyebut apa yang sudah diputuskan dan apa yang masih bebas.

**TRANSISI:** `dp[n]` dihitung dari beberapa `dp[k]` dengan `k < n`, digabung dengan `+`, `max`, `min`, atau `||`, dan pilihan terakhirnya saling lepas serta mencakup semua kemungkinan.

**BASIS:** state yang tidak punya pendahulu diisi secara langsung, biasanya `dp[0]` atau `dp[1]`, karena tidak ada keputusan yang tersisa.

**Proses:** bandingkan tiga cara menghitung `fib(5)`. Tanpa catatan, `fib(3)` muncul dua kali dan `fib(2)` muncul tiga kali. Dengan catatan, tiap `n` dihitung sekali. Dengan tabulasi, kita mengisi dari 0 ke 5 tanpa rekursi.

```
Pendekatan          Panggilan / pengisian     Hasil
rekursi polos       puluhan panggilan         5, tetapi lambat
memo (top-down)     6 pengisian (0..5)        5
tabulasi            6 sel                     5
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;
const ll INF = 4e18;

ll fibPolos(int n) {
    if (n <= 1) return n;
    return fibPolos(n - 1) + fibPolos(n - 2); // JANGAN dipakai di kontes
}

int main() {
    FASTIO;
    cout << fibPolos(10) << "\n"; // 55, hanya untuk n kecil
    return 0;
}
```

**Jebakan:**

1. Menghafal rumus Fibonacci lalu menempelkannya ke soal yang hanya "mirip Fibonacci".
2. Menulis `dp[i]` tanpa kalimat, lalu mengambil `dp[n-1]` padahal definisinya "berakhir tepat di i".
3. Mengira setiap rekursi otomatis adalah DP.

**Kompleksitas:** rekursi polos Fibonacci `O(2^n)` waktu. Setelah ada catatan, waktu menjadi `O(n)` karena tiap state sekali.

---

## Analogi buku catatan PR

**Teori:** Bayangkan 100 soal PR. Soal nomor 47 ternyata sama persis dengan nomor 12. Tanpa buku catatan, nomor 47 dikerjakan ulang dari awal. Dengan buku catatan, setelah nomor 12 selesai jawabannya ditulis, lalu nomor 47 hanya dibaca. Tabel DP adalah buku catatan itu. Analogi ini memaksa dua kebiasaan. Pertama, setiap soal yang sudah selesai harus punya tempat penyimpanan yang jelas (indeks state). Kedua, sebelum mengerjakan, kita cek apakah catatan sudah ada. Di kode, cek itu adalah `if (memo[n] != -1) return memo[n];`. Kalau penanda "belum dikerjakan" tertukar dengan jawaban sah, kita mengerjakan ulang terus-menerus atau, lebih parah, menganggap pekerjaan belum selesai padahal sudah.

**Kapan:** pohon rekursi berisi cabang yang sama. **Tidak:** setiap nomor PR unik, seperti merge sort yang memecah rentang yang tidak pernah bertemu lagi kecuali saat gabung.

**STATE:** `catatan[nomor]` adalah jawaban lengkap soal PR bernomor itu setelah pernah dikerjakan, atau penanda "belum" jika belum pernah.

**TRANSISI:** jika soal `n` bergantung pada soal `n-1` dan `n-2`, maka setelah kedua catatan siap kita menulis `catatan[n] = catatan[n-1] + catatan[n-2]`.

**BASIS:** soal nomor 0 dan 1 tidak merujuk soal lain, jadi ditulis langsung tanpa membuka catatan lama.

**Proses:** sepuluh soal PR yang polanya Fibonacci.

```
Nomor PR   Tanpa catatan                    Dengan catatan
0          tulis 0                          tulis 0 sekali
1          tulis 1                          tulis 1 sekali
2          hitung 0+1                       baca 0 dan 1, tulis 1
3          hitung 2 dan 1 dari nol          baca 2 dan 1, tulis 2
4          hitung 3 dan 2 dari nol          baca 3 dan 2, tulis 3
5          hitung 4 dan 3; 3 dihitung 2x    baca 4 dan 3, tulis 5
```

Tanpa catatan, mengerjakan nomor 5 mengulang nomor 3. Dengan catatan, nomor 3 hanya dibaca.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll bacaCatatan(int nomor, vector<ll>& catatan) {
    if (nomor <= 1) return nomor;
    if (catatan[nomor] != -1) return catatan[nomor]; // sudah ada di buku
    ll jawab = (bacaCatatan(nomor - 1, catatan) + bacaCatatan(nomor - 2, catatan)) % MOD;
    return catatan[nomor] = jawab;
}

int main() {
    FASTIO;
    int n = 10;
    vector<ll> catatan(n + 1, -1);
    cout << bacaCatatan(n, catatan) << "\n";
    return 0;
}
```

**Jebakan:**

1. Mengisi catatan dengan `0` sebagai "belum", padahal `0` bisa jadi jawaban sah.
2. Lupa menulis ke catatan setelah selesai, sehingga cabang berikutnya menghitung ulang.
3. Memakai array global tanpa reset pada multi-testcase.

**Kompleksitas:** setiap nomor PR dihitung paling banyak sekali, lalu dibaca `O(1)`. Total waktu `O(n)`, memori `O(n)`.

---

## Overlapping subproblem

**Teori:** Overlapping subproblem berarti submasalah yang sama muncul di lebih dari satu cabang pohon rekursi. Fibonacci adalah contoh paling bersih: `fib(n)` memanggil `fib(n-1)` dan `fib(n-2)`, lalu `fib(n-1)` memanggil `fib(n-2)` lagi. Tanpa cache, `fib(n-2)` dikerjakan dua kali hanya dari satu level, dan pengulangan itu tumbuh eksponensial. Merge sort memecah array, tetapi potongan `[l, mid)` dan `[mid, r)` tidak pernah sama. Menyimpan hasil merge sort potongan kiri tidak menolong potongan kanan. Itulah beda DP dan divide and conquer. Syarat overlapping berdiri sendiri dari syarat optimal: kita bisa punya overlapping tanpa jawaban yang bisa digabung (jarang berguna), dan kita bisa punya optimal substructure tanpa overlapping (rekursi sekali jalan sudah cukup).

**Kapan:** menggambar dua cabang rekursi dan menemukan simpul berlabel sama. **Tidak:** setiap pemanggilan memakai rentang atau himpunan yang tidak pernah terulang.

**STATE:** `fib(n)` adalah suku Fibonacci ke-`n`, yaitu jumlah dua suku sebelumnya, dan dua pemanggilan dengan `n` yang sama harus menghasilkan angka yang sama.

**TRANSISI:** `fib(n) = fib(n-1) + fib(n-2)` untuk `n >= 2`, sehingga setiap state menunjuk tepat dua state yang lebih kecil.

**BASIS:** `fib(0) = 0` dan `fib(1) = 1` karena definisi barisan dimulai di situ, bukan karena "supaya rumusnya cantik".

**Proses:** hitung berapa kali setiap `fib(k)` dipanggil saat menghitung `fib(6)` tanpa memo.

```
Panggilan fib(6)
                 fib(6)
               /        \
           fib(5)        fib(4)
          /     \       /     \
      fib(4)   fib(3) fib(3)  fib(2)
      /   \     /  \   /  \    /  \
   fib(3) fib(2) ... ... ...  ... ...
```

```
k     banyak panggilan fib(k) tanpa memo
6     1
5     1
4     2
3     3
2     5
1     8     (daun)
0     5     (daun, tergantung implementasi n<=1)
```

Jumlah panggilan interior tumbuh seperti Fibonacci itu sendiri. `fib(50)` polos sekitar 2 miliar panggilan. Dengan memo, tiap `k` sekali.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll hitungPanggilan;

ll fibHitung(int n) {
    hitungPanggilan++;
    if (n <= 1) return n;
    return fibHitung(n - 1) + fibHitung(n - 2);
}

ll fibMemoHitung(int n, vector<ll>& memo, vector<int>& kali) {
    kali[n]++;
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibMemoHitung(n - 1, memo, kali) + fibMemoHitung(n - 2, memo, kali);
}

int main() {
    FASTIO;
    hitungPanggilan = 0;
    cout << fibHitung(10) << " panggilan-polos=" << hitungPanggilan << "\n";
    vector<ll> memo(11, -1);
    vector<int> kali(11, 0);
    cout << fibMemoHitung(10, memo, kali) << "\n";
    for (int k = 0; k <= 10; k++) cout << k << ":" << kali[k] << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** menghitung "sudah overlapping" hanya karena dua fungsi saling memanggil, tanpa memeriksa apakah argumennya sama. `f(l, r)` pada merge sort tidak overlapping meski bentuknya rekursif.

**Kompleksitas:** tanpa memo, jumlah daun Fibonacci `Θ(φ^n)`. Dengan memo, `O(n)` state dan `O(1)` kerja per state.

---

## Pohon Fibonacci tanpa catatan

**Teori:** Pohon rekursi Fibonacci adalah cara paling jujur melihat overlapping. Setiap simpul interior punya dua anak. Banyak simpul pada kedalaman `d` tidak berkurang, justru hampir berlipat. Memo memotong sisi menuju simpul yang sudah ada. Secara visual, cabang kanan `fib(n-2)` sering sudah dihitung oleh cabang kiri `fib(n-1)`. Itulah mengapa memo mengubah pohon menjadi DAG: sisi tetap ada, tetapi simpul digabung.

**Kapan:** menjelaskan ke diri sendiri kenapa `n = 50` tidak selesai. **Tidak:** memakai pohon ini sebagai algoritma produksi; pohon hanya alat diagnosis.

**STATE:** setiap simpul `fib(k)` mewakili permintaan "berapa suku ke-`k`", dan dua simpul berlabel `k` adalah permintaan yang sama.

**TRANSISI:** dari `fib(k)` keluar dua sisi ke `fib(k-1)` dan `fib(k-2)`, kecuali `k <= 1` yang menjadi daun.

**BASIS:** daun `fib(0)` dan `fib(1)` mengembalikan konstanta, tidak membuka cabang baru.

**Proses:** jejak lengkap `fib(5)` tanpa memo, kiri dulu.

```
1. fib(5)
2.   fib(4)
3.     fib(3)
4.       fib(2)
5.         fib(1) = 1
6.         fib(0) = 0
7.       fib(2) = 1
8.       fib(1) = 1
9.     fib(3) = 2
10.    fib(2)
11.      fib(1) = 1
12.      fib(0) = 0
13.    fib(2) = 1
14.  fib(4) = 3
15.  fib(3)          <- ini yang kedua, dihitung ulang
16.    fib(2) ...
17.    fib(1) ...
18.  fib(3) = 2
19. fib(5) = 5
```

Dengan memo, langkah 15 langsung membaca `2`.

Tabel nilai yang seharusnya tersimpan:

```
n    fib(n)
0    0
1    1
2    1
3    2
4    3
5    5
6    8
7    13
8    21
9    34
10   55
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

void jejakPolos(int n, int spasi) {
    for (int i = 0; i < spasi; i++) cout << ' ';
    cout << "fib(" << n << ")\n";
    if (n <= 1) return;
    jejakPolos(n - 1, spasi + 2);
    jejakPolos(n - 2, spasi + 2);
}

void jejakMemo(int n, int spasi, vector<ll>& memo) {
    for (int i = 0; i < spasi; i++) cout << ' ';
    if (n > 1 && memo[n] != -1) {
        cout << "fib(" << n << ") [baca catatan]\n";
        return;
    }
    cout << "fib(" << n << ")\n";
    if (n <= 1) {
        memo[n] = n;
        return;
    }
    jejakMemo(n - 1, spasi + 2, memo);
    jejakMemo(n - 2, spasi + 2, memo);
    memo[n] = (memo[n - 1] + memo[n - 2]) % MOD;
}

int main() {
    FASTIO;
    cout << "=== polos ===\n";
    jejakPolos(5, 0);
    vector<ll> memo(6, -1);
    cout << "=== memo ===\n";
    jejakMemo(5, 0, memo);
    return 0;
}
```

**Jebakan:** mengira memo menghapus sisi DAG. Sisi tetap ada; yang hilang hanya kerja berulang di simpul.

**Kompleksitas:** mencetak pohon polos `O(2^n)` baris. Mencetak pohon ber-memo `O(n)` simpul baru plus `O(n)` hit cache.

---

## Optimal substructure

**Teori:** Optimal substructure berarti kita boleh mengganti potongan solusi dengan potongan terbaik tanpa merusak keabsahan keseluruhan. Pada naik tangga, setiap cara mencapai `i` adalah cara mencapai `i-1` plus langkah 1, atau cara mencapai `i-2` plus langkah 2. Kita tidak perlu menyimpan seluruh barisan; cukup banyaknya cara, karena masa depan hanya peduli posisi sekarang. Pada house robber, total terbaik sampai rumah `i` memakai total terbaik sampai `i-1` atau sampai `i-2`. Kita tidak perlu tahu rumah mana saja yang dipilih di masa lalu, selama larangan tetangga sudah terwakili oleh pilihan "ambil atau lewati i". Contoh yang gagal: jalur sederhana terpanjang di graf berarah yang boleh bersiklus. Jalur terbaik ke tetangga bisa sudah memakai simpul yang kita butuhkan nanti. Menggabungkan "jalur terpanjang ke u" dengan sisi `u -> v` bisa mengulang simpul. Constraint "tidak boleh ulang simpul" merusak optimal substructure yang bersih, kecuali kita membawa seluruh himpunan simpul (bitmask, Day 156).

**Kapan:** keputusan terakhir membagi solusi menjadi "ekor" plus "sisa yang tidak bertabrakan dengan ekor". **Tidak:** ada constraint global yang tidak bisa diringkas ke state kecil.

**STATE:** `dp[i]` adalah nilai terbaik (atau banyak cara) untuk submasalah yang berakhir dengan keputusan di posisi `i`, dan nilai itu sudah cukup untuk masa depan.

**TRANSISI:** jika solusi optimal memakai keputusan terakhir `d`, maka sisa solusinya adalah solusi optimal untuk state pendahulu `pred(d)`.

**BASIS:** submasalah kosong atau berukuran satu tidak punya keputusan terakhir, jadi diisi dari definisi soal.

**Proses:** house robber `[2, 1, 1, 2]` menunjukkan optimal substructure, dan sekaligus menggagalkan greedy.

```
i   a[i]   lewati = dp[i-1]   ambil = dp[i-2]+a[i]   dp[i]
0   2      —                  2                      2
1   1      2                  1                      2
2   1      2                  2+1=3                  3
3   2      3                  2+2=4                  4
```

Jawaban 4 memakai rumah 0 dan 3. Potongan "rumah 0 saja" adalah optimal untuk prefiks `[2]`. Potongan "rumah 0 dan 2" bernilai 3, optimal untuk prefiks tiga rumah. Menyambung rumah 3 ke `dp[1]` (bukan ke `dp[2]`) adalah penggantian potongan yang sah.

Greedy selang-seling memberi 3. Greedy gagal karena pilihan lokal "ambil yang kelihatan besar di dekat sini" merusak pasangan 2+2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll houseRobber(const vector<ll>& a) {
    ll prev2 = 0, prev1 = 0;
    for (ll x : a) {
        ll cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    FASTIO;
    vector<ll> a = {2, 1, 1, 2};
    cout << houseRobber(a) << "\n"; // 4
    return 0;
}
```

**Jebakan:** menganggap "kalau greedy salah, pasti DP" tanpa menulis STATE. Soal jalur sederhana terpanjang juga membuat greedy salah, tetapi DP 1D tidak cukup.

**Kompleksitas:** house robber `O(n)` waktu, `O(1)` memori. Itu karena optimal substructure hanya butuh dua nilai sebelumnya.

---

## Kapan DP gagal

**Teori:** DP gagal dalam dua arah. Arah pertama: overlapping tidak ada, jadi tabel hanya membuang memori. Merge sort, binary search, dan banyak D&C geometri masuk sini. Arah kedua: overlapping ada, tetapi menggabungkan jawaban submasalah melanggar constraint. Longest simple path, knapsack dengan "barang A dan B tidak boleh bersama" yang tidak dimasukkan ke state, atau "jumlah modulo 3 harus 0" tanpa dimensi modulo, semuanya menghasilkan WA yang terasa misterius. Perbaikan arah kedua hampir selalu sama: tambah dimensi sampai Uji 2 dan Uji 3 lolos (lihat [02-topdown-bottomup.md](02-topdown-bottomup.md)). Perbaikan arah pertama: jangan memaksa DP.

**Kapan:** setelah tiga pertanyaan dijawab, hitung `|state| × biaya`. Kalau state tidak bisa ditulis, atau muat hanya dengan membawa seluruh himpunan tak terkompresi berukuran `n > 20`, DP klasik bukan alat yang tepat.

**STATE:** sebuah percobaan state yang gagal tetap harus ditulis sebagai kalimat, supaya jelas informasi mana yang hilang. Contoh gagal: `dp[u]` adalah panjang jalur sederhana terpanjang yang berakhir di simpul `u`.

**TRANSISI:** `dp[v] = max(dp[u] + 1)` untuk sisi `u -> v` terlihat masuk akal, tetapi `dp[u]` bisa memakai `v` di tengah jalur.

**BASIS:** `dp[sumber] = 1` tidak menyelamatkan definisi yang sudah bocor.

**Proses:** graf `A -> B -> C -> A` plus sisi `A -> C`.

```
Jalur sederhana terpanjang dari A:
A-B-C     panjang 3
A-C       panjang 2

Kalau dp[C] diambil dari "jalur terpanjang ke B lalu C", kita dapat A-B-C.
Kalau lalu kita memakai dp[C] untuk kembali ke A, jalur A-B-C-A mengulang A.
```

Tabel yang seolah-olah terisi:

```
simpul   dp salah (abaikan siklus)   dp sah (simple)
A        4 (lewat siklus)            1 (mulai)
B        2                           2 (A-B)
C        3                           3 (A-B-C)
```

Tanpa himpunan simpul, angka di kolom kiri tidak berarti.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// Hanya untuk n kecil: enumerasi jalur sederhana, BUKAN DP 1D.
int jalurSederhana(int u, int mask, const vector<vector<int>>& g, int n) {
    int best = 1;
    for (int v : g[u]) {
        if (mask >> v & 1) continue;
        best = max(best, 1 + jalurSederhana(v, mask | (1 << v), g, n));
    }
    return best;
}

int main() {
    FASTIO;
    int n = 3;
    vector<vector<int>> g(n);
    g[0] = {1, 2};
    g[1] = {2};
    g[2] = {0};
    cout << jalurSederhana(0, 1, g, n) << "\n"; // 3 = A-B-C
    return 0;
}
```

**Jebakan:** memaksa `dp[u]` pada graf bersiklus lalu "menghindari siklus" dengan `visited` global. Itu backtracking, bukan DP, dan overlapping-nya rusak karena `visited` adalah riwayat.

**Kompleksitas:** enumerasi himpunan `O(2^n n)` pada graf padat. Itulah harga membawa constraint "simple" ke dalam state.

---

## Tiga pertanyaan merancang DP

**Teori:** Tiga pertanyaan memaksa desain sebelum sintaksis. STATE adalah kontrak: siapa pun yang membaca `dp[i]` harus tahu persis apa yang sudah diputuskan. TRANSISI adalah keputusan terakhir, bukan "rumus yang dihafal". BASIS adalah uji `n = 0` dan `n = 1` dengan tangan. Banyak WA lahir karena orang menulis loop dulu, lalu menyesuaikan STATE supaya cocok dengan loop. Urutan yang benar terbalik: kalimat, lalu rumus, lalu kode, lalu jejak angka.

**Kapan:** setiap soal baru, termasuk soal yang "kelihatan sama seperti kemarin". **Tidak:** menyalin loop knapsack dari ingatan tanpa menulis ulang tiga kalimat.

**STATE:** `dp[i]` harus menyebut objek (rumah, tangga, koin, kapasitas), rentang yang sudah dipertimbangkan, dan apakah elemen `i` wajib dipakai.

**TRANSISI:** tuliskan keputusan terakhir dalam bahasa manusia, lalu baru ubah menjadi `+` / `max` / `min` / `||`.

**BASIS:** sebut kenapa angkanya begitu. "Karena Fibonacci" bukan alasan. "Karena berdiri di tanah adalah satu cara: barisan kosong" adalah alasan.

**Proses:** soal naik tangga `n = 4`, langkah 1 atau 2, diisi lewat tiga pertanyaan.

```
STATE    : dp[i] adalah banyaknya barisan langkah sah yang jumlahnya tepat i.
TRANSISI : langkah terakhir 1 atau 2, himpunan saling lepas, jadi dp[i] = dp[i-1] + dp[i-2].
BASIS    : dp[0] = 1 karena barisan kosong; dp[1] = 1 karena satu langkah berukuran 1.
```

Jejak:

```
i    dp[i]   barisan
0    1       ()
1    1       (1)
2    2       (1+1), (2)
3    3       (1+1+1), (1+2), (2+1)
4    5       (1+1+1+1), (1+1+2), (1+2+1), (2+1+1), (2+2)
```

Kalau STATE diganti menjadi "dp[i] adalah jawabannya", kita tidak tahu apakah `dp[4]` atau `dp[5]` yang dicetak, dan tidak tahu apakah `n = 0` boleh.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll naikTangga(int n) {
    if (n == 0) return 1;
    ll a = 1, b = 1; // dp[0], dp[1]
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    FASTIO;
    cout << naikTangga(0) << " " << naikTangga(1) << " " << naikTangga(4) << " " << naikTangga(5) << "\n";
    // 1 1 5 8
    return 0;
}
```

**Jebakan:** menulis TRANSISI sebelum STATE. Rumus `dp[i] = dp[i-1] + dp[i-2]` milik banyak soal; tanpa kalimat, modulo, basis, dan tempat jawaban mudah tertukar.

**Kompleksitas:** setelah tiga pertanyaan benar, kode tangga `O(n)` / `O(1)`. Waktu desain biasanya lebih mahal daripada waktu mengetik.

---

## Fibonacci: polos, memo, tabulasi, rolling

**Teori:** Empat implementasi menghitung objek yang sama. Polos menelusuri pohon. Memo (top-down) menelusuri dari `n` ke basis, menyimpan di vektor. Tabulasi (bottom-up) mengisi dari basis ke `n`. Rolling membuang tabel dan hanya menyimpan dua nilai terakhir, karena transisi hanya membaca `i-1` dan `i-2`. Rekurens matematisnya identik. Yang berubah hanya urutan evaluasi dan memori. Di kontes, memo paling dekat dengan cara berpikir, tabulasi paling aman dari stack overflow, rolling paling hemat. Sentinel memo harus `-1` atau `visited`, bukan `0`, karena `fib(0) = 0`.

**Kapan:** `n` muat di `O(n)` dan kita butuh suku ke-`n` modulo `MOD`. **Tidak:** `n` sampai `10^18` — itu perkalian matriks atau rumus tertutup berketelitian, bukan tabel linear.

**STATE:** `dp[i]` adalah suku Fibonacci ke-`i` modulo `MOD`, yaitu `F(i)` dengan `F(0) = 0` dan `F(1) = 1`.

**TRANSISI:** `dp[i] = (dp[i-1] + dp[i-2]) % MOD` untuk setiap `i >= 2`.

**BASIS:** `dp[0] = 0`, `dp[1] = 1`. Tanpa kedua baris ini, loop tidak punya titik pijak.

**Proses:** isi tabulasi sampai `n = 10`.

```
i   dp[i-2]   dp[i-1]   dp[i]
0   —         —         0
1   —         —         1
2   0         1         1
3   1         1         2
4   1         2         3
5   2         3         5
6   3         5         8
7   5         8         13
8   8         13        21
9   13        21        34
10  21        34        55
```

Rolling pada langkah `i = 6`: `dua = 3`, `satu = 5`, `kini = 8`, lalu `dua = 5`, `satu = 8`.

Memo pada `fibMemo(6)` mengisi urutan 1, 0, 2, 3, 4, 5, 6 (DFS kiri dulu).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;
const int INF = 1e9;

ll fibMemo(int n, vector<ll>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = (fibMemo(n - 1, memo) + fibMemo(n - 2, memo)) % MOD;
}

ll fibTab(int n) {
    if (n <= 1) return n;
    vector<ll> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    return dp[n];
}

ll fibHemat(int n) {
    if (n <= 1) return n;
    ll dua = 0, satu = 1;
    for (int i = 2; i <= n; i++) {
        ll kini = (dua + satu) % MOD;
        dua = satu;
        satu = kini;
    }
    return satu;
}

int main() {
    FASTIO;
    int n = 10;
    vector<ll> memo(n + 1, -1);
    cout << fibMemo(n, memo) << " " << fibTab(n) << " " << fibHemat(n) << "\n";
    return 0;
}
```

**Jebakan:**

1. `memset(memo, 0)` lalu `if (memo[n])` — `fib(0)` dan beberapa suku yang kebetulan 0 modulo `MOD` rusak.
2. `int` untuk `fib(n)` tanpa modulo: `fib(47)` sudah melewati `2^31`.
3. Rolling menugaskan `satu = dua` sebelum menyimpan `kini`.
4. `fibTab` tanpa `if (n >= 1)` saat `n = 0` menulis `dp[1]`.

**Kompleksitas:** memo dan tabulasi `O(n)` waktu, `O(n)` memori. Rolling `O(n)` waktu, `O(1)` memori. Polos `O(2^n)`.

---

## Naik tangga sebagai keputusan terakhir

**Teori:** Naik tangga mengajarkan cara menurunkan rumus, bukan mengenali Fibonacci. Ada `n` anak tangga. Sekali langkah naik 1 atau 2. Pertanyaan: berapa banyak barisan langkah yang jumlahnya `n`? Keputusan terakhir hanya dua, dan kedua himpunan barisan dibedakan oleh langkah terakhir, jadi tidak double count. `dp[0] = 1` sering terasa aneh sampai kita menyebut barisan kosong. Kalau `dp[0] = 0`, seluruh tabel menjadi 0. Varian langkah `1..k` hanya memperpanjang daftar keputusan terakhir. Varian anak tangga rusak memaksa `dp[i] = 0` pada indeks rusak, bukan `continue` yang meninggalkan sampah.

**Kapan:** menghitung barisan langkah ke posisi `n` pada garis. **Tidak:** langkah boleh mundur tanpa state tambahan (bukan DAG), atau ada larangan "tidak boleh dua langkah 2 berturut-turut" tanpa dimensi ekstra.

**STATE:** `dp[i]` adalah banyaknya barisan langkah sah yang jumlahnya tepat `i`.

**TRANSISI:** `dp[i] = dp[i-1] + dp[i-2]` karena langkah terakhir hanya 1 atau 2, dan kedua himpunan tidak tumpang tindih.

**BASIS:** `dp[0] = 1` karena berdiri di titik awal adalah satu cara. `dp[1] = 1` karena hanya `(1)`.

**Proses:** `n = 5`.

```
i    dp[i]   contoh barisan (sebagian)
0    1       ()
1    1       (1)
2    2       (1+1), (2)
3    3       (1+1+1), (1+2), (2+1)
4    5       lima barisan
5    8       delapan barisan  <- jawaban
```

Langkah `1..3`, `n = 4`:

```
i    sumber                         dp[i]
0    basis                          1
1    dp[0]                          1
2    dp[1]+dp[0]                    2
3    dp[2]+dp[1]+dp[0]              4
4    dp[3]+dp[2]+dp[1]              7
```

Anak tangga 2 rusak, langkah 1 atau 2, `n = 5`:

```
i    rusak?   dp[i]
0    tidak    1
1    tidak    1
2    ya       0
3    tidak    0+1 = 1   (hanya dari 1)
4    tidak    1+0 = 1
5    tidak    1+1 = 2
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll naikTangga(int n) {
    if (n == 0) return 1;
    ll a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

ll naikTanggaK(int n, const vector<int>& langkah) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int l : langkah)
            if (i - l >= 0) dp[i] = (dp[i] + dp[i - l]) % MOD;
    return dp[n];
}

int main() {
    FASTIO;
    cout << naikTangga(5) << "\n";              // 8
    cout << naikTanggaK(4, {1, 2, 3}) << "\n";  // 7
    return 0;
}
```

**Jebakan:** `dp[0] = 0`. Menghafal "tangga = Fibonacci" lalu mengembalikan `fib(n)` dengan `F(0)=0, F(1)=1` tanpa menyesuaikan indeks: `naikTangga(1)` harus 1, `naikTangga(2)` harus 2.

**Kompleksitas:** langkah 1/2 adalah `O(n)` / `O(1)`. Langkah `1..k` naif `O(nk)`.

---

## Empat pola transisi

**Teori:** Hampir semua DP 1D hanya berbeda operator. "Berapa cara" menjumlahkan cabang yang saling lepas. "Maksimum / minimum" memilih cabang terbaik. "Bisa / tidak" memakai OR. "Minimal langkah" adalah minimum plus satu. Menghafal empat rumus tanpa keputusan terakhir tetap berbahaya, tetapi mengenali operator dari kata soal mempercepat draf pertama. File [03-linear-1d.md](03-linear-1d.md) mengisi keempatnya dengan jejak penuh.

**Kapan:** setelah STATE tertulis, pilih operator dari kata kerja soal. **Tidak:** mencampur `+` dan `max` di state yang sama tanpa dimensi terpisah (itu biasanya dua soal sekaligus: nilai dan banyak cara).

**STATE:** `dp[i]` adalah angka yang jenisnya ditentukan operator: cacah, nilai, boolean, atau jarak.

**TRANSISI:** operator harus cocok dengan arti STATE. Menjumlahkan nilai rumah menghasilkan "total semua subset", bukan "subset terbaik".

**BASIS:** "berapa cara" hampir selalu `dp[0] = 1`. "Minimal" hampir selalu `dp[0] = 0` dan sisanya `INF`. "Maksimum" sering `0`. "Bisa" memakai `bisa[0] = true`.

**Proses:** satu array keputusan, empat bacaan soal.

```
Kata soal                         Operator     Basis khas
berapa cara naik 5 tangga         +            dp[0]=1 -> 8
untung maksimum rumah [2,1,1,2]   max          0,0 -> 4
koin minimum {1,3,4} target 6     min + 1      dp[0]=0, lain INF -> 2
apakah loncat [2,3,1,1,4]         ||           bisa[0]=true -> ya
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;
const int INF = 1e9;

ll polaCara(int n) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i >= 1) dp[i] = (dp[i] + dp[i - 1]) % MOD;
        if (i >= 2) dp[i] = (dp[i] + dp[i - 2]) % MOD;
    }
    return dp[n];
}

ll polaMaks(const vector<ll>& a) {
    ll p2 = 0, p1 = 0;
    for (ll x : a) {
        ll c = max(p1, p2 + x);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int polaMinLangkah(int x, const vector<int>& koin) {
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int v = 1; v <= x; v++)
        for (int c : koin)
            if (c <= v && dp[v - c] != INF) dp[v] = min(dp[v], dp[v - c] + 1);
    return dp[x] == INF ? -1 : dp[x];
}

bool polaBisa(const vector<int>& a) {
    int far = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > far) return false;
        far = max(far, i + a[i]);
    }
    return true;
}

int main() {
    FASTIO;
    cout << polaCara(5) << "\n";
    cout << polaMaks({2, 1, 1, 2}) << "\n";
    cout << polaMinLangkah(6, {1, 3, 4}) << "\n";
    cout << polaBisa({2, 3, 1, 1, 4}) << "\n";
    return 0;
}
```

**Jebakan:** memakai `+` pada house robber. Memakai `max` pada tangga. Mengisi `dp[0] = 1` pada coin minimum.

**Kompleksitas:** keempat cuplikan di atas `O(n)` atau `O(n · |koin|)`.

---

## Rumus kompleksitas

**Teori:** Waktu DP adalah banyak state dikali biaya mengisi satu state. Memori adalah banyak state, atau lebih kecil jika digulung. `fib(n)` punya `n+1` state, tiap state `O(1)`, total `O(n)`. Coin change punya `x+1` state, tiap state melihat semua koin, total `O(n x)`. LIS `O(n^2)` punya `n` state, tiap state melihat `i` pendahulu. Batas kasar 1–2 detik C++ adalah `10^8` operasi. `n = 5000` muat `O(n^2)`. `n = 400` muat `O(n^3)`. `n = 20` muat `O(2^n n^2)`. `n = 40` biasanya meet in the middle, bukan DP penuh.

**Kapan:** setelah STATE dan TRANSISI tertulis, sebelum mengetik. **Tidak:** menulis kode dulu lalu kaget TLE.

**STATE:** jumlah sel tabel adalah hasil kali ukuran setiap dimensi.

**TRANSISI:** biaya satu sel adalah banyak pendahulu yang diloop, bukan "O(1)" secara otomatis.

**BASIS:** pengisian basis `O(ukuran basis)`, biasanya tidak mendominasi.

**Proses:** beberapa paket constraint.

```
n      W atau k     transisi    operasi        verdict
1e5    —            O(1)        1e5            aman
1e5    k=100        O(k)        1e7            aman
5000   —            O(n)        2.5e7          aman
400    —            O(n^2)      6.4e7          ketat-aman
100    W=1e5        O(W)        1e7            aman
100    W=1e9        O(W)        mustahil       ganti model
40     W=1e18       2^{n/2}     ~1e6 * n       MITM
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool muatWaktu(ll nState, ll biaya, ll batas = 100000000LL) {
    return nState <= 0 ? false : nState <= batas / max(1LL, biaya);
}

int main() {
    FASTIO;
    cout << muatWaktu(100000, 1) << "\n";      // 1
    cout << muatWaktu(100, 1000000000LL) << "\n"; // 0
    return 0;
}
```

**Jebakan:** menghitung `n * W` dengan `int` lalu overflow menjadi negatif sehingga "terlihat muat". Memakai `O(n!)` feeling untuk Fibonacci memo.

**Kompleksitas:** rumus itu sendiri `O(1)` untuk dihitung di kertas. Yang mahal adalah salah taksir dimensi.

---

## Checklist Day 141

**Teori:** Day 141 selesai jika kamu bisa menjelaskan overlapping dan optimal substructure tanpa membaca ulang, menuliskan tiga pertanyaan untuk tangga, dan membedakan pohon Fibonacci dari tabel memo. File berikutnya ([02-topdown-bottomup.md](02-topdown-bottomup.md)) memakai prinsip yang sama untuk membandingkan arah evaluasi dan menguji state.

**Kapan:** sebelum membuka latihan Day 141. **Tidak:** loncat ke knapsack karena "itu yang keluar di kontes".

**STATE:** checklist ini bukan array `dp`, melainkan daftar kalimat yang harus bisa diucapkan.

**TRANSISI:** setiap kotak yang belum bisa dijelaskan mengembalikan kamu ke bagian terkait di file ini.

**BASIS:** jika analogi buku catatan belum terasa, jangan lanjut.

**Proses:** uji lisan.

```
Pertanyaan                                              Jawaban singkat
DP itu apa?                                             rekursi + catatan
Dua syarat?                                             overlapping + optimal substructure
Kenapa merge sort bukan DP?                             potongan tidak overlapping
Kenapa longest simple path sulit?                       optimal substructure bocor
Kenapa memo[-1] bukan 0?                                0 bisa sah
fib(5) tanpa memo menghitung fib(3) berapa kali?        dua
dp[0] tangga?                                           1
Rumus waktu?                                            |state| x biaya
```

**Kode:** fungsi `fibMemo`, `fibTab`, dan `naikTangga` di atas sudah cukup untuk menguji kontrak Day 141. `main` hanya memanggil ketiga fungsi itu, bukan mengulang rumus.

**Jebakan:** merasa selesai karena sudah menyalin `fibTab` tanpa mampu mengisi tabel `fib(6)` di kertas.

**Kompleksitas:** waktu belajar Day 141 adalah satu sesi teori plus jejak angka. Setelah jejak cocok, mengetik kode biasanya cepat.

Lanjut ke [02 — top-down dan bottom-up](02-topdown-bottomup.md) untuk memo `-1`, tabulasi, urutan isi DAG, dan empat uji state.
