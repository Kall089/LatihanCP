# Ternary search dan fungsi unimodal

[← README](README.md) · [Indeks CP](../README.md)

Satu titik tengah tidak memberi arah pada fungsi yang naik lalu turun. Dua titik bisa: bandingkan tingginya, lalu buang sepertiga ruang yang sudah mustahil memuat puncak. Itulah ternary search.

Day terkait: **050**. Untuk integer, binary search pada selisih sering lebih aman daripada menyalin rumus real.

## Daftar isi

- [Apa itu unimodal](#apa-itu-unimodal)
- [Ternary search real](#ternary-search-real)
- [Ternary search minimum](#ternary-search-minimum)
- [Ternary search integer](#ternary-search-integer)
- [Binary search pada selisih](#binary-search-pada-selisih)
- [Kapan ternary gagal](#kapan-ternary-gagal)
- [Peta keputusan](#peta-keputusan)

---

## Apa itu unimodal

**Teori:** Fungsi unimodal punya **satu** puncak atau **satu** lembah. Setelah puncak, ia tidak naik lagi. Analoginya satu gunung di kabut: berjalan ke kanan, ketinggian hanya naik lalu turun. Alasan potong ruang sah: tidak ada gunung kedua yang tersembunyi di sisi yang lebih rendah. Binary search biasa gagal karena satu nilai `f(mid)` tidak bilang “masih naik atau sudah turun”.

**Kapan:** domain kontinu atau diskrit yang kamu buktikan unimodal: jarak ke titik, fungsi kuadrat, biaya `|x - a_i|` dengan median, beberapa fungsi geometri. Jangan jika ada dua puncak. Jangan jika ada dataran lebar tanpa aturan.

**Proses:** tiga fungsi di `[0, 6]`.

1. `f(x) = -(x-3)^2 + 10` puncak di `3`, nilai `10`. Unimodal maksimum.
2. `g(x) = (x-2)^2` lembah di `2`. Unimodal minimum.
3. `h(x) = sin(x)` di `[0, 6]` punya lebih dari satu puncak. **Bukan** unimodal di interval itu.

Tabel kasar `f` di integer:

| x | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| f | 1 | 6 | 9 | 10 | 9 | 6 | 1 |

Naik sampai 3, lalu turun. Satu puncak.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double fPuncak(double x) { return -(x - 3) * (x - 3) + 10; }

double gLembah(double x) { return (x - 2) * (x - 2); }

bool naikLaluTurun(const vector<ll>& a) {
    int n = (int)a.size();
    int i = 0;
    while (i + 1 < n && a[i] < a[i + 1]) i++;
    if (i == 0 || i == n - 1) return n == 1;
    while (i + 1 < n && a[i] > a[i + 1]) i++;
    return i == n - 1;
}

int main() {
    FASTIO;
    cout << fPuncak(3) << '\n'; // 10
    cout << gLembah(2) << '\n'; // 0
    cout << naikLaluTurun({1, 6, 9, 10, 9, 6, 1}) << '\n'; // 1
    cout << naikLaluTurun({1, 3, 2, 4}) << '\n';           // 0
    return 0;
}
```

`naikLaluTurun` hanyalah pemeriksa array sampel, bukan algoritma pencarian.

**Jebakan:**
1. Mengira “kelihatan naik turun” di tiga titik sudah bukti.
2. Dataran `5,5,5,4` membingungkan pemeriksa ketat `<`.
3. Memakai ternary pada `sin` di interval panjang.

**Kompleksitas:** pemeriksa linear `O(n)`. Definisi matematika `O(1)` di kepala.

---

## Ternary search real

**Teori:** Analoginya mendaki dalam kabut: bandingkan ketinggian dua patok. Letakkan `m1 = lo + (hi-lo)/3` dan `m2 = hi - (hi-lo)/3`. Untuk maksimum, jika `f(m1) < f(m2)` maka puncak ada di kanan `m1`, jadi `lo = m1`. Jika tidak, puncak ada di kiri `m2`, jadi `hi = m2`. Alasan benar: di kiri `m1` tidak mungkin ada puncak lebih tinggi jika `f(m1)` sudah lebih rendah dan fungsi hanya naik lalu turun.

**Kapan:** domain real, `f` mahal sedikit, unimodal terbukti. Jangan fungsi bergelombang. Dataran (`f` konstan di interval) bisa membuang sisi yang salah. Untuk integer, sering lebih aman binary search pada selisih.

**Proses:** `f(x) = -(x-3)^2 + 10`, puncak di `3`, cari di `[0, 6]`.

1. `m1 = 2`, `m2 = 4`. `f(2) = 9`, `f(4) = 9`. Simetris; implementasi membuang salah satu sisi dan tetap mendekat.
2. `m1 = 2.0`, `m2 = 3.5`: `f(2) = 9`, `f(3.5) = 9.75` → puncak kanan `m1`, `lo = m1`.
3. Interval menyempit ke `3`.
4. 80 iterasi cukup untuk galat `1e-9` pada interval kecil.
5. Cek `f(3) = 10`.

Jejak beberapa iterasi jika selalu `f(m1) < f(m2)` atau sebaliknya akan berbeda, tetapi titik tengah `(lo+hi)/2` menuju 3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double fPuncak(double x) {
    return -(x - 3) * (x - 3) + 10;
}

double ternaryMax(double lo, double hi) {
    for (int it = 0; it < 80; it++) {
        double m1 = lo + (hi - lo) / 3.0;
        double m2 = hi - (hi - lo) / 3.0;
        if (fPuncak(m1) < fPuncak(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2.0;
}

int main() {
    FASTIO;
    cout.setf(ios::fixed);
    cout.precision(6);
    double x = ternaryMax(0, 6);
    cout << x << ' ' << fPuncak(x) << '\n'; // ~3 ~10
    return 0;
}
```

**Jebakan:**
1. Membuang sisi terbalik (mencari max dengan aturan min).
2. Dataran membuat `f(m1) == f(m2)` ambigu.
3. Hanya 20 iterasi pada interval `1e9`.
4. `m1` dan `m2` dihitung dengan pecahan integer ` / 3` tanpa `.0`.

**Kompleksitas:** `O(iter)` evaluasi, memori `O(1)`.

---

## Ternary search minimum

**Teori:** Lembah adalah puncak yang dibalik. Jika `f(m1) > f(m2)`, lembah ada di kanan `m1`. Analoginya turun ke dasar mangkuk: patok yang lebih tinggi tidak menyimpan dasar di luarnya. Alasan benar: unimodal minimum berarti turun lalu naik; sisi yang lebih tinggi di kiri `m1` sudah dilewati.

**Kapan:** biaya kuadrat, jarak ke titik di garis, beberapa fungsi waktu versus kecepatan. Jangan menukar tanda tanpa menulis ulang aturan `lo`/`hi`.

**Proses:** `g(x) = (x-2)^2` di `[0, 5]`. Lembah `x = 2`, nilai `0`.

1. `m1 ≈ 1.666`, `m2 ≈ 3.333`. `g(m1) ≈ 0.11`, `g(m2) ≈ 1.78`.
2. `g(m1) < g(m2)` → lembah di kiri `m2`, `hi = m2`.
3. Interval mengecil ke 2.
4. Setelah 80 langkah, `x ≈ 2`, `g ≈ 0`.
5. Cek titik ujung: `g(0) = 4`, `g(5) = 9`, keduanya lebih buruk.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double gLembah(double x) { return (x - 2) * (x - 2); }

double ternaryMin(double lo, double hi) {
    for (int it = 0; it < 80; it++) {
        double m1 = lo + (hi - lo) / 3.0;
        double m2 = hi - (hi - lo) / 3.0;
        if (gLembah(m1) > gLembah(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2.0;
}

int main() {
    FASTIO;
    cout.setf(ios::fixed);
    cout.precision(6);
    double x = ternaryMin(0, 5);
    cout << x << ' ' << gLembah(x) << '\n'; // ~2 ~0
    return 0;
}
```

**Jebakan:**
1. Menyalin kode max lalu hanya mengganti nama fungsi.
2. Interval awal tidak memuat lembah: jawaban menempel di ujung, itu **bukan** unimodal di dalam interval.
3. Overflow kuadrat pada `x` besar. Geser rumus, jangan `x * x` mentah jika `x` `1e9`.

**Kompleksitas:** `O(iter)` evaluasi, memori `O(1)`.

---

## Ternary search integer

**Teori:** Analoginya tangga: sepertiga interval bisa jatuh di pijakan yang sama. Saat `hi - lo < 3`, `m1` dan `m2` bisa identik, loop tidak maju. Solusi: loop selama `hi - lo > 3`, lalu sapu sisa paling banyak empat kandidat. Alasan banyak WA: menyalin kode real ke `int` apa adanya.

**Kapan:** puncak pada indeks integer, array unimodal, biaya diskrit. Lebih sering: ganti ke binary search pada `f(i+1) - f(i)`. Jangan dataran lebar.

**Proses:** array unimodal `f = [1, 3, 7, 6, 2]`, puncak indeks `2` nilai `7`.

1. `lo = 0`, `hi = 4`. `m1 = 1` (`3`), `m2 = 3` (`6`). `3 < 6` → `lo = 1`.
2. `lo = 1`, `hi = 4`. `m1 = 2` (`7`), `m2 = 3` (`6`). `7 > 6` → `hi = 3`.
3. `hi - lo = 2 <= 3`, sapu `1..3`: nilai `3, 7, 6`. Puncak `7`.
4. Tanpa sapu akhir, risiko `m1 == m2`.
5. Jawaban indeks `2`.

Contoh `m1 == m2` jika dipaksa: `lo = 0`, `hi = 2`, `(hi-lo)/3 = 0`, `m1 = 0`, `m2 = 2 - 0 = 2`. Masih beda. Tetapi `lo = 5`, `hi = 7`: `m1 = 5`, `m2 = 7`. Saat `hi = lo + 1`, keduanya bisa menunjuk sel yang sama tergantung rumus.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int puncakTernary(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (hi - lo > 3) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f[m1] < f[m2]) lo = m1;
        else hi = m2;
    }
    int best = lo;
    for (int i = lo; i <= hi; i++)
        if (f[i] > f[best]) best = i;
    return best;
}

int lembahTernary(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (hi - lo > 3) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f[m1] > f[m2]) lo = m1;
        else hi = m2;
    }
    int best = lo;
    for (int i = lo; i <= hi; i++)
        if (f[i] < f[best]) best = i;
    return best;
}

int main() {
    FASTIO;
    vector<ll> f = {1, 3, 7, 6, 2};
    int i = puncakTernary(f);
    cout << i << ' ' << f[i] << '\n'; // 2 7
    vector<ll> g = {9, 4, 1, 2, 8};
    int j = lembahTernary(g);
    cout << j << ' ' << g[j] << '\n'; // 2 1
    return 0;
}
```

**Jebakan:**
1. Tidak menyapu sisa.
2. `m1` dan `m2` sama lalu `lo`/`hi` tidak bergerak.
3. Dua puncak: unimodal palsu, jawaban bergantung cabang.
4. Array kosong atau satu elemen tidak di-handle.

**Kompleksitas:** `O(log n)` evaluasi plus `O(1)` sapu akhir, memori `O(1)`.

---

## Binary search pada selisih

**Teori:** Analoginya: kamu tidak tanya ketinggian, kamu tanya “langkah berikutnya naik atau turun?”. Untuk integer unimodal, `ok(i) = (f[i+1] < f[i])` menjadi `false, false, …, true`. First true adalah puncak. Alasan ini hampir selalu lebih baik dari ternary integer: tidak ada `m1 == m2`, dan alatnya sudah ada di [binary-search.md](binary-search.md).

**Kapan:** peak index (LC 852, LC 162) jika ada **satu** puncak. Jangan jika ada dataran `f[i] == f[i+1]` tanpa aturan. Jangan array acak.

**Proses:** `f = [1, 3, 7, 6, 2]`.

1. `i = 0`: `3 > 1`, belum turun.
2. `i = 1`: `7 > 3`, belum.
3. `i = 2`: `6 < 7`, sudah turun. First true = `2`.
4. `i = 3`: `2 < 6`, tetap true.
5. Itu lower bound pada predikat “sudah turun”.

Untuk lembah, predikat “sudah naik”: `f[mid] < f[mid+1]` berarti lembah di kiri atau di `mid`? Hati-hati arah. Lebih aman: jika `f[mid] > f[mid+1]` masih turun, lembah di kanan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int puncakDariSelisih(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f[mid] > f[mid + 1]) hi = mid; // sudah turun
        else lo = mid + 1;                 // masih naik
    }
    return lo;
}

int lembahDariSelisih(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f[mid] < f[mid + 1]) hi = mid; // sudah naik, lembah kiri/mid
        else lo = mid + 1;                 // masih turun
    }
    return lo;
}

int main() {
    FASTIO;
    vector<ll> f = {1, 3, 7, 6, 2};
    cout << puncakDariSelisih(f) << '\n'; // 2
    vector<ll> g = {9, 4, 1, 2, 8};
    cout << lembahDariSelisih(g) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `f[mid] >= f[mid+1]` pada dataran: predikat tidak ketat, bisa berhenti di dataran.
2. `hi = n` lalu `f[mid+1]` di luar batas.
3. Memaksa ternary padahal selisih cukup.
4. Array bitonic palsu dengan dua puncak.

**Kompleksitas:** `O(log n)` waktu, `O(1)` memori.

---

## Kapan ternary gagal

**Teori:** Ternary membuang sepertiga. Jika fungsi punya dua gunung, sepertiga yang dibuang bisa memuat gunung yang lebih tinggi. Analoginya kabut di dua puncak: patok kiri lebih rendah tidak berarti puncak dunia ada di kanan. Dataran sama berbahayanya: `f(m1) == f(m2)` tidak memilih sisi dengan aman.

**Kapan:** pakai bagian ini sebagai alarm, bukan sebagai algoritma. Jika kamu tidak bisa membuktikan unimodal, jangan ternary. Pertimbangkan brute pada `n` kecil, atau DP jika ada state.

**Proses:** `f = [1, 8, 3, 9, 2]`. Dua puncak: 8 dan 9.

1. `lo = 0`, `hi = 4`, `m1 = 1` (`8`), `m2 = 3` (`9`). `8 < 9` → `lo = 1`.
2. Ruang `[1,4] = [8,3,9,2]`. Masih memuat keduanya.
3. Langkah berikutnya bisa membuang 9 atau 8 tergantung perbandingan.
4. Tidak ada jaminan puncak global.
5. Selisih juga gagal: “sudah turun” pertama di indeks `1` (`8 → 3`), padahal puncak global di `3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int puncakTernary(const vector<ll>& f) {
    int lo = 0, hi = (int)f.size() - 1;
    while (hi - lo > 3) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f[m1] < f[m2]) lo = m1;
        else hi = m2;
    }
    int best = lo;
    for (int i = lo; i <= hi; i++)
        if (f[i] > f[best]) best = i;
    return best;
}

int puncakLinear(const vector<ll>& f) {
    return (int)(max_element(f.begin(), f.end()) - f.begin());
}

int main() {
    FASTIO;
    vector<ll> f = {1, 8, 3, 9, 2};
    cout << "ternary=" << puncakTernary(f)
         << " linear=" << puncakLinear(f) << '\n';
    // linear=3 (nilai 9). ternary bisa 1 atau 3 tergantung cabang.
    return 0;
}
```

Kalau hasilnya beda, itu bukti kamu tidak boleh memakai ternary pada soal itu.

**Jebakan:**
1. Lolos sampel unimodal lalu WA di tes dua puncak.
2. Mengira “hampir unimodal” cukup.
3. Menambah iterasi untuk “memperbaiki” fungsi yang salah bentuk.

**Kompleksitas:** linear `O(n)` adalah oracle yang jujur untuk n kecil.

---

## Peta keputusan

```text
f unimodal real
  → ternary 80 iter, atau golden section

f unimodal integer
  → binary search pada selisih
  → ternary integer + sapu sisa

f tidak terbukti unimodal
  → jangan potong sepertiga

ok(x) monoton false→true
  → itu binary search, bukan ternary
```

| gejala | arti |
| --- | --- |
| `m1 == m2` | ruang diskrit terlalu sempit |
| `f(m1) == f(m2)` | dataran, sisi ambigu |
| predikat “cukup / tidak” | file binary search |
| dua gunung | linear / DP / matematika lain |

Ringkasan: unimodal dulu, baru potong ruang. Integer lebih aman lewat selisih. Dataran dan gunung kedua adalah musuh.

Kembali ke [binary-search.md](binary-search.md) atau lanjut ke [interaktif.md](interaktif.md) jika nilai `f` datang dari juri.
