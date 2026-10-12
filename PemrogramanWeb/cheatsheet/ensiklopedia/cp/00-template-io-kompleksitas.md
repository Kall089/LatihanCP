# 00 — Template, Fast I/O, dan Kompleksitas

[← README dasar](README-dasar.md) · [Lanjut STL kontainer →](01-stl-vector-set-map-pq.md)

> **Ide satu kalimat:** sebelum mengetik algoritma, baca batas soal lalu pilih senjata yang muat di waktu dan memori.

Day ComprogLearning: **015** Analisis Kompleksitas. File ini juga memuat template I/O yang dipakai di semua file berikutnya.

Semua indeks **0-based**. `long long` ditulis `ll`. Fungsi dipisah dari `main`.

## Daftar isi

- [Template CP standar](#template-cp-standar)
- [Fast I/O](#fast-io)
- [Newline, bukan endl](#newline-bukan-endl)
- [Pola baca input](#pola-baca-input)
- [Multi test case](#multi-test-case)
- [long long dan overflow](#long-long-dan-overflow)
- [Big-O](#big-o)
- [Membaca constraint](#membaca-constraint)
- [Tabel n versus algoritma](#tabel-n-versus-algoritma)
- [Nested loop dan TLE](#nested-loop-dan-tle)
- [Rekursi dan stack](#rekursi-dan-stack)
- [Estimasi memori](#estimasi-memori)
- [Konvensi 0-index](#konvensi-0-index)
- [Stress test mini](#stress-test-mini)

---

## Template CP standar

> **Ide satu kalimat:** satu kerangka yang sama, supaya otak hanya memikirkan soal.

### Template CP standar

**Teori:** Analoginya kotak perkakas yang sudah tersusun sebelum masuk bengkel. `#include <bits/stdc++.h>` menarik hampir semua header STL sekaligus, `using namespace std` memendekkan nama, `FASTIO` mematikan sinkronisasi lambat dengan `stdio`, dan `typedef long long ll` membuat tipe jumlah besar menjadi refleks. Template tidak membuat program benar; ia hanya menghapus pekerjaan yang sama di setiap soal. Alasan ia “benar” sebagai kebiasaan: waktu kontes terbuang di salah ketik include dan overflow, bukan di rumus. Isi logika tetap kamu tulis di fungsi terpisah supaya bisa diuji.

**Kapan dipakai / kapan tidak.** Pakai di hampir semua soal Codeforces, AtCoder, CSES, TLX. Jangan andalkan `bits/stdc++.h` jika compiler kampus hanya `clang++` tanpa header itu — ganti ke include eksplisit. Jangan `using namespace std` di header proyek besar; di file tunggal kontes itu wajar.

**Proses:** Soal: baca `n`, lalu `n` bilangan, cetak jumlahnya. Angka kecil `n = 4`, array `3 1 4 1`.

1. `FASTIO` dipanggil sekali di awal `main`.
2. `cin >> n` dapat `4`.
3. `vector<ll> a(n)` lalu loop isi `3, 1, 4, 1`.
4. `jumlahArray(a)` menambah `3+1+4+1`.
5. `cout` menulis `9` plus newline.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll jumlahArray(const vector<ll>& a) {
    ll s = 0;
    for (ll x : a) s += x; // akumulasi wajib ll
    return s;
}

int main() {
    FASTIO;
    int n = 4;
    vector<ll> a = {3, 1, 4, 1};
    cout << jumlahArray(a) << '\n'; // 9
    return 0;
}
```

**Jebakan:**
1. Menaruh seluruh solusi di `main` lalu tidak bisa mengetes fungsi.
2. Lupa `FASTIO` pada input 2·10^5 baris — TLE meski algoritmanya O(n).
3. Compile `clang++` tanpa `bits/stdc++.h`.
4. Menyalin `#define int long long` lalu `main` jadi `void` tanpa sadar.

**Kompleksitas:** waktu O(n) untuk jumlah; memori O(n) untuk array. Template sendiri O(1).

---

## Fast I/O

> **Ide satu kalimat:** `cin` default berbagi buffer dengan `scanf`, dan berbagi itu mahal.

### Fast I/O

**Teori:** Analoginya kasir yang setiap barang harus konfirmasi ke gudang sebelah. `ios_base::sync_with_stdio(false)` memutus hubungan `cin`/`cout` dengan `scanf`/`printf`. `cin.tie(NULL)` memutus aturan “sebelum baca, kosongkan keluaran dulu”. Setelah itu, `cin` cukup cepat untuk 10^6 angka jika kamu tidak memakai `endl`. Alasan benar: sinkronisasi adalah kerja ekstra yang tidak mengubah nilai yang dibaca, hanya mengubah kapan buffer dikirim. Di kontes, 2·10^5 baris input sering lebih lambat dari algoritma O(n log n)-nya.

**Kapan dipakai / kapan tidak.** Pakai hampir selalu. Jangan campur `cin` dengan `scanf` setelah mematikan sinkronisasi — urutan baca bisa kacau. Jangan matikan tie lalu berharap prompt interaktif muncul sebelum `flush` (lihat file 05).

**Proses:** Input buatan: `5` lalu lima angka `1 2 3 4 5`.

1. Tanpa fast I/O: tiap `cin` bisa memicu flush `cout` tersembunyi.
2. Dengan `sync_with_stdio(false)`: buffer C++ mandiri.
3. Dengan `cin.tie(NULL)`: baca tidak menunggu tulis.
4. Lima angka masuk vector dalam satu loop.
5. Jumlah `15` tertulis sekali di akhir.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> bacaArray(int n) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    return a;
}

int main() {
    FASTIO;
    // tes tanpa stdin: isi manual, fungsi baca tetap sama polanya
    vector<ll> a = {1, 2, 3, 4, 5};
    ll s = 0;
    for (ll x : a) s += x;
    cout << s << '\n'; // 15
    return 0;
}
```

**Jebakan:**
1. `scanf` + `cin` setelah `sync_with_stdio(false)`.
2. Fast I/O di soal interaktif tanpa `flush`.
3. Mengira fast I/O menggantikan algoritma yang salah.

**Kompleksitas:** I/O O(n) token. Konstanta turun jauh; kompleksitas asimtotik sama.

---

## Newline, bukan endl

> **Ide satu kalimat:** `endl` = newline **plus** kirim buffer sekarang, dan “sekarang” itu mahal.

### Newline, bukan endl

**Teori:** Analoginya mengirim satu surat per kata, bukan satu amplop berisi halaman. `'\n'` hanya karakter. `endl` memaksa flush. Di loop `2·10^5` baris, ratusan ribu flush membuat TLE meski hitungannya O(n). Alasan benar: isi yang tertulis sama; yang berbeda hanya kapan sistem operasi ikut kerja. Buffer akan dikirim otomatis di akhir program atau saat penuh.

**Kapan dipakai / kapan tidak.** Pakai `'\n'` di soal biasa. Pakai `endl` atau `flush` hanya jika juri harus membaca keluaranmu **sebelum** kamu membaca jawaban berikutnya (soal interaktif).

**Proses:** Cetak tiga baris `1`, `2`, `3`.

1. `cout << 1 << endl` — tulis + flush.
2. `cout << 2 << endl` — tulis + flush lagi.
3. `cout << 3 << endl` — flush ketiga.
4. Ganti ke `'\n'`: tiga tulis, satu flush di akhir.
5. Hasil di layar sama; waktu tidak.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void cetakBaris(const vector<ll>& a) {
    for (ll x : a) cout << x << '\n'; // bukan endl
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cetakBaris({1, 2, 3});
    return 0;
}
```

**Jebakan:**
1. `endl` di dalam loop besar.
2. Lupa flush di soal interaktif.
3. `printf` tanpa `'\n'` lalu buffer tertahan saat debug.

**Kompleksitas:** waktu I/O tetap O(n); konstanta flush bisa membuat TLE.

---

## Pola baca input

> **Ide satu kalimat:** hampir semua soal adalah `n`, lalu `n` angka, atau `n m`, lalu `m` baris.

### Pola baca input

**Teori:** Analoginya formulir yang kolomnya tetap: jumlah dulu, isi kemudian. Kalau kamu baca `n` angka tanpa membuat vector berukuran `n`, kamu meresize di tengah jalan atau menulis di indeks liar. Alasan benar: ukuran diketahui di awal, jadi alokasi sekali lebih aman dan lebih cepat. Fungsi `bacaN` dan `bacaGraph` memisahkan “cara masuk data” dari “cara mengolah data”.

**Kapan dipakai / kapan tidak.** Pakai pola ini untuk array, daftar sisi, dan string. Jangan mengira `while (cin >> x)` selalu benar — beberapa soal punya beberapa tes tanpa sentinel, harus baca `t` dulu.

**Proses:** Input logis `n=3`, `a = [10, 20, 40]`.

1. Baca `n = 3`.
2. Buat `vector<ll> a(3)`.
3. Isi indeks `0,1,2` — bukan `1,2,3` kecuali soal 1-based.
4. Fungsi `maksimum` jalan di array yang sudah penuh.
5. Jawaban `40`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll maksimum(const vector<ll>& a) {
    ll best = a[0];
    for (int i = 1; i < (int)a.size(); i++) best = max(best, a[i]);
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {10, 20, 40};
    cout << maksimum(a) << '\n'; // 40
    return 0;
}
```

**Jebakan:**
1. `vector<ll> a;` lalu `a[i] = x` tanpa `resize` — UB.
2. Loop `i <= n` pada array 0-based.
3. `int n; vector<int> a(n);` sebelum `cin >> n`.

**Kompleksitas:** baca O(n), cari maksimum O(n), memori O(n).

---

## Multi test case

> **Ide satu kalimat:** reset semua array di awal tes, atau tes kedua memakai sampah tes pertama.

### Multi test case

**Teori:** Analoginya papan tulis yang harus dihapus sebelum soal berikutnya. Banyak soal Codeforces: baris pertama `t`, lalu `t` tes mandiri. Global vector yang di-`push_back` tanpa `clear` adalah WA klasik. Alasan benar: juri menjalankan **satu** program untuk semua tes; state hidup terus. Solusinya: data lokal di fungsi `solve()`, atau `clear`/`assign` eksplisit.

**Kapan dipakai / kapan tidak.** Pakai `solve()` per tes jika `t` ada. Jangan mengira `t` selalu kecil — kadang `t · n ≤ 2·10^5`, jadi kompleksitas harus dijumlah seluruh tes, bukan per tes saja.

**Proses:** Dua tes. Tes 1: `n=2`, `1 2` jumlah `3`. Tes 2: `n=3`, `4 5 6` jumlah `15`.

1. `t = 2`.
2. Tes 1: bangun array baru, jumlah `3`.
3. Tes 2: array baru lagi — jangan sisa `{1,2}`.
4. Keluaran dua baris: `3` lalu `15`.
5. Jika lupa reset, tes 2 bisa jadi `1 2 4 5 6` = `18` (WA).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll jumlahArray(const vector<ll>& a) {
    ll s = 0;
    for (ll x : a) s += x;
    return s;
}

void solveSatuTes(const vector<ll>& a) {
    cout << jumlahArray(a) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<ll>> tes = {{1, 2}, {4, 5, 6}};
    for (auto& a : tes) solveSatuTes(a); // 3 lalu 15
    return 0;
}
```

**Jebakan:**
1. `static` / global tanpa reset.
2. Menghitung O(n²) per tes padahal `sum n` besar.
3. Lupa `t` lalu membaca tes pertama sebagai `n`.

**Kompleksitas:** waktu jumlah seluruh tes. Jika `Σ n ≤ 2·10^5`, O(Σ n log n) aman, O(Σ n²) tidak.

---

## long long dan overflow

> **Ide satu kalimat:** `2·10^5 × 10^9 = 2·10^14`, sedangkan `int` mati di `2·10^9`.

### long long dan overflow

**Teori:** Analoginya ember 2 liter yang kamu isi dari bak 200 liter. Di C++, overflow `int` **bukan** error; ia membungkus (undefined untuk signed, tapi di praktiknya wrap). Jawaban jadi negatif aneh atau positif kecil. Alasan memakai `ll`: rentang `±9·10^18` menampung hampir semua jumlah kontes. Perkalian dua `int` tetap `int` dulu — harus cast sebelum `*`.

**Kapan dipakai / kapan tidak.** Pakai `ll` untuk jumlah, prefix, hasil kali, inversi, jarak. `int` cukup untuk indeks dan `n` jika `n ≤ 1e6`. Jangan `ll` untuk array boolean raksasa tanpa alasan — memori dobel.

**Proses:** `n = 3`, nilai `1000000000, 1000000000, 1000000000`.

1. Jumlah benar `3·10^9`.
2. Jika `int s = 0; s += x` tiga kali, `s` overflow.
3. `ll s = 0` mendapat `3000000000`.
4. `int a=1e9, b=1e9; ll c = a*b` — `a*b` tetap `int`, `c` sudah rusak.
5. `ll c = 1LL * a * b` — benar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll jumlahAman(const vector<int>& a) {
    ll s = 0;
    for (int x : a) s += x;
    return s;
}

ll kaliAman(int a, int b) {
    return 1LL * a * b; // cast dulu
}

int main() {
    vector<int> a = {1000000000, 1000000000, 1000000000};
    cout << jumlahAman(a) << '\n';          // 3000000000
    cout << kaliAman(1000000000, 3) << '\n'; // 3000000000
    return 0;
}
```

**Jebakan:**
1. `accumulate(v.begin(), v.end(), 0)` — `0` adalah `int`.
2. `a * b` dua `int` sebelum disimpan ke `ll`.
3. `abs` pada `INT_MIN`.
4. `n * (n-1) / 2` untuk `n = 1e5` tanpa `1LL`.

**Kompleksitas:** waktu sama; tiap `ll` 8 byte, `int` 4 byte.

---

## Big-O

> **Ide satu kalimat:** Big-O menghitung **pertumbuhan**, bukan detik persis di laptopmu.

### Big-O

**Teori:** Analoginya waktu antre: kalau orang dobel dan kamu cek setiap pasangan, waktu jadi empat kali — itu O(n²). O(f(n)) berarti untuk n besar, langkahnya tidak tumbuh lebih cepat dari konstanta kali f(n). Alasan benar sebagai alat pilih algoritma: juri memberi n dan waktu 1–2 detik. Kita kira ±10^8 operasi sederhana per detik. Yang dibuang adalah konstanta kecil dan kasus terbaik; yang dijaga adalah kasus terburuk yang bisa dibuat juri.

Notasi yang sering muncul:

| Notasi | Artinya kasar |
| --- | --- |
| O(1) | tidak bergantung n |
| O(log n) | potong dua berulang |
| O(n) | sekali sapu |
| O(n log n) | sort / heap / set |
| O(n²) | semua pasangan |
| O(2^n) | semua subset |

**Kapan dipakai / kapan tidak.** Pakai untuk menolak ide sebelum coding. Jangan memakai Big-O untuk mengabaikan konstanta besar (`set` vs array, `unordered_map` vs array frekuensi). Jangan bilang “O(n²) aman” hanya karena n=1000 jika di dalam masih ada log berat atau I/O aneh.

**Proses:** Hitung pasangan `i < j` pada `n=4`, indeks `0..3`.

1. `i=0`, `j=1,2,3` — 3 pasangan.
2. `i=1`, `j=2,3` — 2.
3. `i=2`, `j=3` — 1.
4. Total 6 = `n(n-1)/2` = O(n²).
5. Untuk `n=2·10^5`, pasangan ≈ `2·10^10` — mustahil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll hitungPasanganNaif(int n) {
    ll cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            cnt++; // O(n^2)
    return cnt;
}

ll hitungPasanganO1(int n) {
    return 1LL * n * (n - 1) / 2;
}

int main() {
    cout << hitungPasanganNaif(4) << '\n'; // 6
    cout << hitungPasanganO1(4) << '\n';   // 6
    return 0;
}
```

**Jebakan:**
1. Mengira O(n² / 2) “bukan O(n²)”.
2. Lupa `t` tes: O(t n²).
3. Recursion tree yang ternyata O(2^n), bukan O(n).

**Kompleksitas:** naif O(n²) waktu, O(1) memori; rumus O(1) waktu dan memori.

---

## Membaca constraint

> **Ide satu kalimat:** baris `1 ≤ n ≤ …` adalah petunjuk algoritma yang ditulis juri.

### Membaca constraint

**Teori:** Analoginya plang jembatan “maksimal 5 ton”: truk 10 ton jangan dipaksa lewat. Constraint memberitahu n, nilai `a_i`, jumlah tes, waktu, memori. Alasan benar: setiap batas menutup kelas algoritma. `n ≤ 20` mengundang 2^n. `n ≤ 40` mengundang meet in the middle. `n ≤ 2·10^5` menuntut O(n log n). `a_i ≤ 10^9` menolak array frekuensi indeks langsung. Membaca constraint adalah langkah desain, bukan formalitas.

**Kapan dipakai / kapan tidak.** Selalu, sebelum mengetik. Jangan membaca hanya sampel. Jangan mengabaikan `Σ n` pada multi tes.

**Proses:** Soal fiktif: `1 ≤ t ≤ 10^4`, `1 ≤ n ≤ 10^5`, `Σ n ≤ 2·10^5`, `1 ≤ a_i ≤ 10^9`, waktu 2 detik.

1. `t` besar, tapi `Σ n` yang dihitung.
2. O(n²) per tes ditolak karena satu tes bisa n=1e5.
3. O(n log n) total ≈ `2e5 · 18` ≈ 4e6 — aman.
4. `a_i = 1e9` — jangan `cnt[a_i]`.
5. Pilih sort / set / prefix, bukan frequency array.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// memetakan constraint n ke "kelas" algoritma
string kelasAlgoritma(ll n) {
    if (n <= 20) return "eksponensial 2^n mungkin";
    if (n <= 40) return "meet in the middle 2^(n/2)";
    if (n <= 400) return "O(n^3) kadang muat";
    if (n <= 3000) return "O(n^2) biasanya muat";
    if (n <= 200000) return "O(n log n) atau O(n)";
    if (n <= 1000000) return "hampir hanya O(n) atau O(n log n) ketat";
    return "O(n) linier / rumus O(1)";
}

int main() {
    cout << kelasAlgoritma(20) << '\n';
    cout << kelasAlgoritma(200000) << '\n';
    return 0;
}
```

**Jebakan:**
1. Membaca `n ≤ 1e5` tapi mengabaikan `t ≤ 1e5`.
2. `a_i ≤ 1e9` tetap membuat `int cnt[1000000001]`.
3. Waktu 1 detik dianggap sama dengan 8 detik.

**Kompleksitas:** fungsi pemetaan O(1). Yang diukur adalah algoritma yang kamu pilih setelahnya.

---

## Tabel n versus algoritma

> **Ide satu kalimat:** hafalkan plang jembatan, bukan hafalkan 50 rumus dulu.

### Tabel n versus algoritma

**Teori:** Analoginya menu restoran: jumlah tamu menentukan apakah kamu masak per porsi atau prasmanan. Tabel di bawah adalah kira-kira 1–2 detik, ±10^8 operasi. Alasan benar: juri merancang n supaya solusi yang dimaksud muat dan solusi naif tidak. Deviasi ada (konstanta `set` lebih berat dari array), tetapi plang ini mencegah kamu menulis O(n²) pada n=1e5.

**Kapan dipakai / kapan tidak.** Pakai di menit pertama. Jangan kaku: O(n²) pada n=5000 kadang TLE jika dalam loop masih ada `map`. Jangan mengira O(n log n) selalu lolos pada n=1e7.

**Proses:** Soal `n=1000`, cari dua indeks jumlah = x.

1. Naif dua loop O(n²) = 10^6 — muat.
2. Sort + two pointers O(n log n) juga muat, lebih rapi.
3. Jika n jadi `2·10^5`, langkah 1 mati, langkah 2 hidup.
4. Jika n=20 dan “pilih subset”, even two pointers salah arah.
5. Constraint mengubah alat.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string pilihAlat(ll n, const string& jenis) {
    if (jenis == "subset" && n <= 20) return "bitmask";
    if (jenis == "subset" && n <= 40) return "meet in the middle";
    if (jenis == "pasangan" && n <= 3000) return "dua loop";
    if (jenis == "pasangan") return "sort + two pointers / hash";
    if (n <= 200000) return "n log n";
    return "linier";
}

int main() {
    cout << pilihAlat(20, "subset") << '\n';
    cout << pilihAlat(200000, "pasangan") << '\n';
    return 0;
}
```

Tabel plang:

| n sampai | Kelas yang biasanya muat |
| ---: | --- |
| 12–20 | O(n!), O(2^n · n) |
| 40 | MITM O(2^{n/2} n) |
| 100 | O(n^4) ketat, O(n^3) longgar |
| 400 | O(n^3) |
| 2.000–3.000 | O(n²) |
| 1e5–2e5 | O(n log n) |
| 1e6 | O(n) atau O(n log n) sangat ramping |
| 1e9–1e18 | O(log n) / O(√n) / rumus |

**Jebakan:**
1. Menghafal tabel lalu mengabaikan `k` tambahan: O(n² k).
2. `set` di dalam O(n²) pada n=2000.
3. Rekursi 2^n pada n=30.

**Kompleksitas:** keputusan O(1); eksekusi mengikuti kelas yang dipilih.

---

## Nested loop dan TLE

> **Ide satu kalimat:** dua loop bersarang pada n=1e5 adalah 10^10, bukan “kedua-duanya O(n)”.

### Nested loop dan TLE

**Teori:** Analoginya mengecek setiap murid dengan setiap murid lain: 300 orang masih sempat, 200.000 orang tidak selesai minggu ini. Loop luar n kali, loop dalam n kali, hasil perkalian. Alasan orang tertipu: tiap loop terlihat “satu sapu”. Compiler tidak menggabungkan itu jadi O(n). Two pointers dan prefix ada justru untuk mengganti loop dalam.

**Kapan dipakai / kapan tidak.** Nested O(n²) sah jika n≤2000 atau `Σ n²` kecil. Jangan dipakai “dulu yang naif di kontes 2 detik n=1e5” — tidak akan lolos.

**Proses:** Array `2 1 3`, hitung pasangan `a[i] > a[j]` untuk `i < j` (bukan inversi posisi klasik: di sini i kiri).

Array `a = [2,1,3]`, cari berapa `i < j` dan `a[i] > a[j]`.

1. `(0,1)`: `2>1` ya.
2. `(0,2)`: `2>3` tidak.
3. `(1,2)`: `1>3` tidak.
4. Jawaban 1.
5. Untuk n=1e5, tiga langkah semacam ini jadi 5·10^9 banding — TLE; pakai merge sort (file 05).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll inversiNaif(const vector<ll>& a) {
    int n = (int)a.size();
    ll inv = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) inv++;
    return inv;
}

int main() {
    vector<ll> a = {2, 1, 3};
    cout << inversiNaif(a) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `for i` + `for j=i` pada n=1e5.
2. Loop dalam `lower_bound` di vector **tidak** terurut.
3. `count` linear di dalam loop = O(n²).

**Kompleksitas:** waktu O(n²), memori O(1) di luar input.

---

## Rekursi dan stack

> **Ide satu kalimat:** tiap panggilan makan stack; n=1e5 rekursi linier bisa RE.

### Rekursi dan stack

**Teori:** Analoginya tumpukan piring: satu piring per panggilan yang belum selesai. DFS ke daun, merge sort, rekursi `f(n-1)`. Limit stack kontes sering ±8–64 MB, kira-kira 10^5 frame dangkal atau jauh lebih sedikit jika frame gemuk. Alasan benar: heap (`vector`) besar biasanya aman sampai ratusan MB sesuai limit; stack tidak. Tail recursion tidak dijamin dioptimasi C++.

**Kapan dipakai / kapan tidak.** Rekursi nyaman untuk D&C dan DFS pohon kecil-sedang. Jangan rekursi `n` dalam pada n=1e6. Ubah ke iteratif atau naik `stack` di heap.

**Proses:** Faktorial rekursif `n=5`.

1. `fak(5)` menunggu `fak(4)`.
2. `fak(4)` menunggu `fak(3)`.
3. … sampai `fak(0) = 1`.
4. Kembali `1,1,2,6,24,120`.
5. Kedalaman 6. Untuk `fak(200000)` stack habis.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll faktorialRekursif(int n) {
    if (n == 0) return 1; // basis
    return n * faktorialRekursif(n - 1);
}

ll faktorialIteratif(int n) {
    ll a = 1;
    for (int i = 1; i <= n; i++) a *= i;
    return a;
}

int main() {
    cout << faktorialRekursif(5) << '\n'; // 120
    cout << faktorialIteratif(5) << '\n'; // 120
    return 0;
}
```

**Jebakan:**
1. DFS rekursif pada garis n=1e5.
2. Lupa basis → stack overflow.
3. `vector` lokal besar di tiap frame rekursi.

**Kompleksitas:** waktu O(n), memori stack O(n) versi rekursif, O(1) iteratif.

---

## Estimasi memori

> **Ide satu kalimat:** `4 · 10^8` byte ≈ 400 MB; limit sering 256 MB.

### Estimasi memori

**Teori:** Analoginya koper kabin: hitung dulu, jangan di bandara. `int` 4 byte, `ll` 8 byte, `bool` di `vector<bool>` khusus (bit), `bool` biasa 1 byte. `vector<ll>(2e5)` ≈ 1.6 MB. `int dp[2000][2000]` ≈ 16 MB. `int dp[10000][10000]` ≈ 400 MB — MLE. Alasan benar: MLE tidak bisa “dioptimasi compiler”; harus ganti struktur.

**Kapan dipakai / kapan tidak.** Hitung sebelum membuat tabel 2D. Jangan alokasi `int freq[1000000001]`. Array global besar lebih aman dari lokal (stack).

**Proses:** Butuh frekuensi nilai `1..1e9`, n=1e5.

1. Array indeks langsung 1e9 sel — mustahil.
2. `map` atau sort+unique: hanya n kunci.
3. `vector<ll> a(1e5)` ≈ 0.8 MB — aman.
4. `ll pref[n+1][n+1]` untuk n=5000 — 200 juta `ll` ≈ 1.6 GB — MLE.
5. Pilih alat yang memori O(n) atau O(n log n).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll byteVectorLL(int n) {
    return 1LL * n * (ll)sizeof(ll);
}

int main() {
    cout << byteVectorLL(200000) << '\n'; // 1600000
    cout << (byteVectorLL(200000) < 256LL * 1024 * 1024 ? "muat\n" : "mle\n");
    return 0;
}
```

Perkiraan cepat:

| Benda | Ukuran kasar |
| --- | --- |
| `int` / `ll` | 4 / 8 byte |
| `vector<ll>(2e5)` | ~1.6 MB |
| `int [2000][2000]` | ~16 MB |
| `int [5000][5000]` | ~100 MB |
| `map` n=2e5 | puluhan MB (node) |

**Jebakan:**
1. Array 2D lokal besar → RE stack, bukan hanya MLE heap.
2. `vector<vector<int>>` pecah-pecah, overhead per baris.
3. Menyimpan 2^20 `pair<ll,ll>` tanpa hitung (≈16 MB, masih aman; 2^26 tidak).

**Kompleksitas:** waktu O(1) untuk estimasi. Memori mengikuti rumus di atas.

---

## Konvensi 0-index

> **Ide satu kalimat:** di folder ini `a[0]` adalah elemen pertama; soal 1-based dikonversi di pintu masuk.

### Konvensi 0-index

**Teori:** Analoginya nomor kursi bioskop versus nomor urut antrean. C++ array 0-based. Banyak soal menulis “elemen l sampai r” 1-based. Campur tanpa aturan = off-by-one. Alasan konvensi ini benar untuk cheatsheet: satu bahasa. Jika soal 1-based, baca ke `a[0..n-1]`, lalu `l--, r--`, atau pakai prefix `n+1` dengan `pre[i]` = jumlah `i` elemen pertama.

**Kapan dipakai / kapan tidak.** Pakai 0-based di semua fungsi di folder ini. Jangan campur `pre[r]-pre[l-1]` (1-based) dengan `pre[r+1]-pre[l]` (0-based) di satu fungsi.

**Proses:** Soal 1-based: elemen 2 sampai 3 pada `10 20 30 40` (nilai 20+30).

1. Array 0-based: `[10,20,30,40]`.
2. Query 1-based `l=2, r=3` → 0-based `l=1, r=2`.
3. Prefix `pre = [0,10,30,60,100]`.
4. Jumlah = `pre[3]-pre[1] = 60-10 = 50`.
5. Setara `pre[r+1]-pre[l]` dengan `l,r` 0-based.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> bangunPrefix(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    return pre;
}

// l, r 0-based inklusif
ll rangeSum(const vector<ll>& pre, int l, int r) {
    return pre[r + 1] - pre[l];
}

int main() {
    vector<ll> a = {10, 20, 30, 40};
    auto pre = bangunPrefix(a);
    cout << rangeSum(pre, 1, 2) << '\n'; // 50
    return 0;
}
```

**Jebakan:**
1. `for (int i = 1; i <= n; i++)` pada `vector(n)`.
2. `l--` dua kali.
3. `pre[r]-pre[l-1]` saat `l=0`.

**Kompleksitas:** bangun O(n), query O(1), memori O(n).

---

## Stress test mini

> **Ide satu kalimat:** versi lambat adalah wasit yang tidak pernah lelah.

### Stress test mini

**Teori:** Analoginya menimbang buah dengan timbangan pasar dan timbangan dapur: kalau beda, salah satu rusak. Tulis `naif()` yang jelas benar (O(n²) atau 2^n kecil), `cepat()` yang kamu curigai, generator acak, bandingkan. Alasan benar: sampel soal jarang memuat jebakan yang kamu ciptakan sendiri. Bug Kadane `best=0`, bug inversi `+=1`, bug bound off-by-one ketahuan dalam detik.

**Kapan dipakai / kapan tidak.** Pakai saat rumus rawan dan n kecil bisa disimulasikan. Jangan stress test O(n²) pada n=1e5. Jangan generator yang tidak pernah membuat kasus semua-negatif jika itu jebakannya.

**Proses:** Bandingkan jumlah naif vs `accumulate` pada `[3,-1,4]`.

1. Naif: `3 + (-1) + 4 = 6`.
2. Cepat: sama.
3. Generator membuat array acak panjang 1..8.
4. Jika suatu saat beda, cetak array itu — itu kasus minimal.
5. Perbaiki `cepat`, ulangi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll jumlahNaif(const vector<ll>& a) {
    ll s = 0;
    for (ll x : a) s += x;
    return s;
}

ll jumlahCepat(const vector<ll>& a) {
    return accumulate(a.begin(), a.end(), 0LL);
}

vector<ll> acak(int n, int lo, int hi, mt19937& rng) {
    uniform_int_distribution<int> dist(lo, hi);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rng);
    return a;
}

int main() {
    mt19937 rng(42);
    for (int t = 0; t < 1000; t++) {
        int n = 1 + (rng() % 8);
        auto a = acak(n, -5, 5, rng);
        if (jumlahNaif(a) != jumlahCepat(a)) {
            cout << "beda\n";
            return 0;
        }
    }
    cout << "lolos 1000 tes\n";
    return 0;
}
```

**Jebakan:**
1. Seed tetap tapi generator tidak pernah `n=1`.
2. Membandingkan floating tanpa epsilon.
3. Naif juga salah (dua bug sama).

**Kompleksitas:** 1000 tes × O(n) di sini. Untuk algoritma O(n²) naif, jaga n≤200.

---

## Ringkasan file 00

- Template: `bits`, `FASTIO`, `ll`, fungsi terpisah.
- I/O: matikan sync, jangan `endl`, flush hanya interaktif.
- Overflow: cast `1LL *` sebelum kali.
- Constraint adalah desain: n memilih Big-O.
- ±10^8 operasi / detik, hitung `Σ n`, hitung byte.
- 0-based di fungsi; konversi 1-based di pintu.
- Versi naif adalah wasit.

Lanjut: [01 — vector, set, map, priority_queue](01-stl-vector-set-map-pq.md).
