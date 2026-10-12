# Subset dan bitmask

[← README](README.md) · [Indeks CP](../README.md)

Setiap elemen punya dua pilihan: masuk atau tidak. Itu `2^n` himpunan. Kamu bisa menelusurinya sebagai pohon rekursi, atau menomori setiap himpunan sebagai bilangan biner.

Day terkait: **060**. `n <= 20` adalah zona nyaman. `n = 40` belah dua di [meet-in-the-middle](../04-sorting-searching/meet-in-the-middle.md).

## Daftar isi

- [Enumerasi subset rekursif](#enumerasi-subset-rekursif)
- [Operasi bitmask](#operasi-bitmask)
- [Enumerasi subset dengan bitmask](#enumerasi-subset-dengan-bitmask)
- [Subset dari sebuah mask](#subset-dari-sebuah-mask)
- [Enumerasi 3^n](#enumerasi-3n)
- [Subset sum naif](#subset-sum-naif)
- [Peta keputusan](#peta-keputusan)

---

## Enumerasi subset rekursif

**Teori:** Analoginya tas belanja: tiap barang “masuk / tinggal”. Urutan keputusan mengikuti indeks `0..n-1` supaya setiap himpunan muncul tepat sekali. Posisi daun (`pos == n`) adalah satu subset jadi. Cabang “ambil” mendorong elemen ke `cur`, cabang “tidak” membiarkan. Setelah cabang ambil, `pop_back` mengembalikan tas. Itu sudah backtracking kecil; pola umum ada di [backtracking.md](backtracking.md).

**Kapan:** `n <= 20` jika kerja per subset `O(n)` atau lebih kecil; `n <= 15` jika per subset mahal. Kalau hanya cek “ada subset berjumlah `S`” dan kapasitas kecil, DP lebih baik. Jangan `n = 30` (`1e9` daun).

**Proses:** array `{1, 2, 3}`. Pohon ambil/tidak dari kiri.

```text
pos=0, cur=[]
  tidak 1 → pos=1 []
    tidak 2 → pos=2 []
      tidak 3 → {}
      ambil 3 → {3}
    ambil 2 → pos=2 [2]
      tidak 3 → {2}
      ambil 3 → {2,3}
  ambil 1 → pos=1 [1]
    tidak 2 → [1]
      tidak 3 → {1}
      ambil 3 → {1,3}
    ambil 2 → [1,2]
      tidak 3 → {1,2}
      ambil 3 → {1,2,3}
```

Delapan daun = `2^3`. Urutan di atas: `{} {3} {2} {2,3} {1} {1,3} {1,2} {1,2,3}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void enum_subset(int pos, const vector<int>& a, vector<int>& cur,
                 vector<vector<int>>& semua) {
    if (pos == (int)a.size()) {
        semua.push_back(cur);
        return;
    }
    enum_subset(pos + 1, a, cur, semua);
    cur.push_back(a[pos]);
    enum_subset(pos + 1, a, cur, semua);
    cur.pop_back();
}

int main() {
    FASTIO;
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

**Jebakan:**
1. Lupa `pop_back()`: subset berikutnya membawa barang lama.
2. Menghitung daun di tengah jalan, bukan saat `pos == n`.
3. `n = 25` TLE.
4. Menyalin `cur` by value di setiap panggilan: benar tetapi lambat.

**Kompleksitas:** waktu `O(2^n · n)` jika tiap subset disalin. Memori hasil `O(2^n · n)`, stack `O(n)`.

---

## Operasi bitmask

**Teori:** Himpunan `n` elemen muat di satu bilangan: bit ke-`i` hidup artinya elemen `i` masuk. Analoginya deretan saklar. Operasi himpunan jadi operasi bit: gabungan `|`, irisan `&`, beda simetris `^`, komplemen di `n` bit `~x & ((1<<n)-1)`. Kenapa benar: setiap bit independen, jadi operator bit = operator koordinat pada vektor `{0,1}^n`.

**Kapan:** `n <= 20` pakai `int` / `1 << n`, atau `n <= 60` pakai `1LL << n`. State DP himpunan, cek kepemilikan, enumerasi. Jangan `1 << n` untuk `n >= 31` pada `int`. Jangan `~x` mentah jika kamu hanya ingin `n` bit.

**Proses:** elemen `{A,B,C,D}` = indeks `{0,1,2,3}`. Himpunan `{A,C}` = bit 0 dan 2 = `0101_2 = 5`.

| mask | biner | himpunan |
| ---: | --- | --- |
| 0 | 0000 | {} |
| 1 | 0001 | {A} |
| 5 | 0101 | {A,C} |
| 10 | 1010 | {B,D} |
| 15 | 1111 | {A,B,C,D} |

Operasi pada `mask = 10` (`1010`, `{B,D}`):

```text
cek bit 1: (10 >> 1) & 1 = 1      B ada
set bit 0: 10 | 1 = 11            {A,B,D}
clear bit 3: 10 & ~(8) = 2        {B}
toggle bit 2: 10 ^ 4 = 14         {B,C,D}
lowbit: 10 & -10 = 2              bit 1
hapus lowbit: 10 & 9 = 8          {D}
popcount(10) = 2
```

Irisan `{A,C}=5` dan `{A,B}=3`: `5 & 3 = 1` = `{A}`. Gabungan `5 | 3 = 7` = `{A,B,C}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    int mask = 10;
    cout << bit_on(mask, 1) << '\n';                 // 1
    cout << set_bit(mask, 0) << '\n';                // 11
    cout << clear_bit(mask, 3) << '\n';              // 2
    cout << tog_bit(mask, 2) << '\n';                // 14
    cout << lowbit(mask) << ' ' << popc(mask) << '\n'; // 2 2
    auto isi = elemen(5, 4);
    for (int x : isi) cout << x << ' ';              // 0 2
    cout << '\n';
    return 0;
}
```

**Jebakan:**
1. `1 << 31` undefined behavior pada `int` bertanda.
2. `1LL << 63` sama berbahayanya.
3. `~mask` 32-bit mengubah bit tanda.
4. `__builtin_popcount` untuk `int`; `ll` memakai `__builtin_popcountll`.

**Kompleksitas:** tiap operasi `O(1)`. Menulis isi mask `O(n)`.

---

## Enumerasi subset dengan bitmask

**Teori:** Semua himpunan bagian dari `{0..n-1}` adalah bilangan `0, 1, …, 2^n - 1`. Loop `for (mask = 0; mask < (1<<n); mask++)` mengunjungi semuanya. Di dalam, bit yang hidup = elemen yang dipilih. Ini **sama** dengan pohon ambil/tidak, hanya ditulis iteratif. Kenapa lengkap dan tanpa duplikat: setiap vektor bit muncul tepat sekali sebagai bilangan.

**Kapan:** `n <= 20` standar kontes (`2^20 ≈ 1e6`). Subset sum naif, pengantar TSP, cek sifat “untuk setiap himpunan”. Jangan jika `n = 28` dan kerja per mask `O(n)`. Untuk `n = 40` belah jadi meet in the middle.

**Proses:** `a = {4, 7, 2}`, `n = 3`. Cari subset berjumlah 6.

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    vector<int> a = {4, 7, 2};
    cout << ada_jumlah(a, 6) << '\n';   // 1
    cout << ada_jumlah(a, 8) << '\n';   // 0
    auto isi = salah_satu(a, 6);
    for (int x : isi) cout << x << ' '; // 4 2
    cout << '\n';
    return 0;
}
```

Optimasi kecil: jumlah mask `m` dan mask `m` tanpa lowbit berbeda satu elemen. Bisa `O(2^n)` murni, tetapi loop ganda sudah cukup untuk `n <= 20`.

**Jebakan:**
1. `1 << n` saat `n = 31`.
2. Menjumlah `int` overflow.
3. Lupa mask `0` (subset kosong, jumlah 0 sering jawaban sah).
4. `mask & (1 << i)` tanpa kurung, prioritas operator.

**Kompleksitas:** waktu `O(2^n · n)`, memori `O(1)` plus keluaran.

---

## Subset dari sebuah mask

**Teori:** Kadang kamu sudah punya himpunan `mask`, lalu ingin semua subset-nya. Trik: `sub = (sub - 1) & mask` berjalan dari `mask` turun ke subset tak kosong, lalu proses `0` terpisah. Kenapa jalan: `sub - 1` mematikan lowbit dan menyalakan bit di kanannya; `& mask` membuang bit yang bukan milik `mask`, jadi `sub` tetap subset.

**Kapan:** enumerasi subset sebuah grup, transisi DP “pecah himpunan”, SOS intro. Jangan menuliskan loop `0..2^n` lalu membuang yang bukan subset: itu lebih lambat jika `popcount` kecil.

**Proses:** `mask = 13` = `1101` = bit `{0,2,3}`.

```text
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

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> subset_dari_mask(int mask) {
    vector<int> res;
    for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
        res.push_back(sub);
    res.push_back(0);
    return res;
}

int main() {
    FASTIO;
    auto s = subset_dari_mask(13);
    for (int x : s) cout << x << ' ';
    cout << '\n';
    cout << s.size() << '\n'; // 8
    auto t = subset_dari_mask(0);
    cout << t.size() << ' ' << t[0] << '\n'; // 1 0
    return 0;
}
```

**Jebakan:**
1. Lupa subset kosong.
2. `sub = (sub-1) & mask` pada `sub = 0` menjadi `(-1) & mask = mask` → loop tak berujung jika kamu tidak `break`.
3. Mengira urutan subset leksikografis. Urutan trik ini adalah urutan bit, bukan urutan elemen.

**Kompleksitas:** `O(2^{popcount})` untuk satu mask. Memori `O(1)` plus keluaran.

---

## Enumerasi 3^n

**Teori:** Pasangan `(mask, sub ⊆ mask)` dihitung sebagai berikut: untuk tiap elemen, tiga pilihan — tidak masuk mask, masuk mask tetapi tidak masuk sub, atau masuk keduanya. Itu `3^n`. Dipakai di DP transisi “pecah himpunan”. Analoginya tiap orang: absen, hadir tanpa tugas, hadir dengan tugas.

**Kapan:** `n <= 14` untuk `3^n` murni (`3^14 ≈ 4.7e6`), `n <= 18` jika konstan kecil. Jangan `3^n` untuk `n = 20` (`3.4e9`).

**Proses:** untuk `n = 2`, semua pasangan sah:

| mask | sub yang sah |
| ---: | --- |
| 00 | 00 |
| 01 | 00, 01 |
| 10 | 00, 10 |
| 11 | 00, 01, 10, 11 |

Total `1+2+2+4 = 9 = 3^2`. Untuk `n = 3` harus `27`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll enum_3n(int n) {
    ll hit = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int sub = mask; ; sub = (sub - 1) & mask) {
            hit++;
            if (sub == 0) break;
        }
    }
    return hit;
}

ll pangkat3(int n) {
    ll p = 1;
    for (int i = 0; i < n; i++) p *= 3;
    return p;
}

int main() {
    FASTIO;
    cout << enum_3n(2) << ' ' << pangkat3(2) << '\n'; // 9 9
    cout << enum_3n(3) << ' ' << pangkat3(3) << '\n'; // 27 27
    cout << enum_3n(4) << '\n';                       // 81
    return 0;
}
```

Loop dalam **harus** `if (sub == 0) break` setelah memproses. Kalau `for (sub = mask; sub; sub = (sub-1)&mask)` maka `0` terlewat.

**Jebakan:**
1. Lupa `0`.
2. Loop tak berujung di `sub == 0`.
3. Overflow `1 << n`.

**Kompleksitas:** semua pasangan `O(3^n)`. Memori `O(1)`.

---

## Subset sum naif

**Teori:** “Apakah ada subset berjumlah `S`?” Pada `n <= 20` bitmask cukup. Pada `n` lebih besar dengan `S` kecil, memo/DP `O(nS)` di [memoization.md](memoization.md) dan folder 09. Greedy “ambil terbesar yang muat” **bukan** subset sum: `{5, 4, 3}`, `S = 7` gagal jika mengambil 5 dulu, padahal `4+3 = 7`.

**Kapan:** brute atau sebagai oracle stress. Jangan greedy. Jangan `n = 40` tanpa belah dua.

**Proses:** `a = {5, 4, 3}`, `S = 7`.

1. Mask lengkap 8 kemungkinan. `{5}` 5, `{4}` 4, `{3}` 3, `{5,4}` 9, `{5,3}` 8, `{4,3}` 7, `{5,4,3}` 12, `{}` 0.
2. Ada: `{4,3}`.
3. Greedy terbesar: ambil 5, sisa 2, tidak ada. Salah.
4. `S = 1` tidak ada.
5. `S = 0` ada (kosong), kecuali soal melarang kosong.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool subset_bitmask(const vector<ll>& a, ll S) {
    int n = (int)a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += a[i];
        if (s == S) return true;
    }
    return false;
}

bool greedy_salah(vector<ll> a, ll S) {
    sort(a.rbegin(), a.rend());
    for (ll x : a) if (x <= S) S -= x;
    return S == 0;
}

int main() {
    FASTIO;
    vector<ll> a = {5, 4, 3};
    cout << subset_bitmask(a, 7) << '\n'; // 1
    cout << greedy_salah(a, 7) << '\n';   // 0, greedy gagal
    cout << subset_bitmask(a, 1) << '\n'; // 0
    return 0;
}
```

Itu kontras penting ke folder greedy dan DP: subset sum utuh bukan greedy.

**Jebakan:**
1. Percaya greedy “terbesar dulu”.
2. Overflow jumlah.
3. Melarang kosong atau tidak, tergantung statement.

**Kompleksitas:** bitmask `O(n 2^n)`. Greedy `O(n log n)` tetapi bisa salah.

---

## Peta keputusan

```text
n <= 20, semua himpunan
  → rekursi ambil/tidak atau loop mask

Sudah punya mask, ingin subsetnya
  → (sub-1) & mask

Pecah himpunan, transisi DP
  → 3^n

n = 40
  → meet in the middle, bukan 2^40

Hanya "ada jumlah S", S kecil
  → DP / memo, bukan 2^n
```

| n | 2^n | 3^n | aman? |
| ---: | ---: | ---: | --- |
| 8 | 256 | 6561 | ya |
| 12 | 4096 | 5e5 | 3^n masih |
| 15 | 3e4 | 1.4e7 | 3^n berat |
| 20 | 1e6 | 3e9 | bitmask O(n 2^n) ok |
| 24 | 1.6e7 | — | hanya kerja O(1) |

Ringkasan: pohon dan mask adalah benda yang sama. `popcount`, lowbit, dan `(sub-1)&mask` adalah kosakata wajib sebelum DP bitmask di folder 09.

Lanjut ke [backtracking.md](backtracking.md) jika ada syarat dan undo, atau [memoization.md](memoization.md) jika cabang menghitung state yang sama.
