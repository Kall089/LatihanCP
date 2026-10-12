# Bitset dan Operasi Bit

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** kemas puluhan jawaban boolean dalam satu register, lalu geser semuanya sekaligus.

Day ComprogLearning: **026** optimasi bitset. Semua 0-based. Fungsi modular. `typedef long long ll`. Ini materi struktur bit, bukan DP bitmask folder 09.

## Daftar isi

- [bitset dasar](#bitset-dasar)
- [set test reset flip](#set-test-reset-flip)
- [Geser bitset](#geser-bitset)
- [Subset sum dengan bitset](#subset-sum-dengan-bitset)
- [AND OR XOR massal](#and-or-xor-massal)
- [Menghitung bit](#menghitung-bit)
- [Iterasi bit menyala](#iterasi-bit-menyala)
- [Mask integer 64-bit](#mask-integer-64-bit)
- [bitset versus vector bool](#bitset-versus-vector-bool)
- [Graf kecil sebagai bitset](#graf-kecil-sebagai-bitset)

---

## bitset dasar

> **Ide satu kalimat:** 64 saklar dalam satu register; 256 saklar dalam empat register.

### bitset dasar

**Teori:** Analoginya rak absen 200.000 kursi, tiap kursi 1 bit, bukan 1 `int`. `bitset<N>` memakai bitwise AND/OR/XOR massal. Alasan benar: memori dibagi 64 dan operasi dibagi 64. `bs[i]` adalah bit ke-i (0-based). N harus konstanta compile-time. `to_string()` menulis bit terbesar di kiri, jadi debug mudah tertukar arah.

**Kapan:** Pakai himpunan 0..N-1, DP boolean, visibilitas. Jangan N dinamis besar tanpa `vector<uint64_t>` manual. Jangan `bitset` untuk aritmetika biasa.

**Proses:** N=8, nyalakan bit 1 dan 4.

| Langkah | Operasi | Bit yang hidup | count |
| ---: | --- | --- | ---: |
| 1 | awal | tidak ada | 0 |
| 2 | `set(1)` | 1 | 1 |
| 3 | `set(4)` | 1, 4 | 2 |
| 4 | `test(4)` | true | 2 |
| 5 | `test(3)` | false | 2 |

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int nyalakanDanHitung() {
    bitset<8> bs;
    bs.set(1);
    bs.set(4);
    return (int)bs.count();
}

bool nyala(const bitset<8>& bs, int i) {
    return bs.test(i);
}

int main() {
    FASTIO;
    bitset<8> bs;
    bs.set(1);
    bs.set(4);
    cout << nyalakanDanHitung() << '\n'; // 2
    cout << nyala(bs, 4) << ' ' << nyala(bs, 3) << '\n'; // 1 0
    return 0;
}
```

**Jebakan:**
1. `N` bukan compile-time constant.
2. Tertukar “bit 0 paling kiri” saat membaca `to_string()`.
3. `bs[i]` di luar `[0, N)` tidak seperti vector — perilaku terpotong atau exception tergantung implementasi.

**Kompleksitas:** `count` / `and` O(N/64), memori O(N/8) byte.

---

## set test reset flip

> **Ide satu kalimat:** nyalakan, tanya, matikan, atau balik; jangan campur arti keempatnya.

### set test reset flip

**Teori:** Analoginya saklar kamar. `set(i)` menyalakan, `reset(i)` mematikan, `flip(i)` membalik, `test(i)` bertanya tanpa mengubah. `set()` tanpa argumen menyalakan semua. `reset()` mematikan semua. Alasan benar: banyak WA “vis[i]=0” yang sebenarnya `flip` tidak sengaja, atau `set(i,0)` yang orang kira tidak ada.

**Kapan:** Pakai untuk himpunan kehadiran dan toggle. Jangan `flip` jika soal minta “pastikan nyala”. Jangan `reset` seluruh bitset di dalam loop n tanpa alasan.

**Proses:** Mulai `0000` (N=4).

1. `set(0)` → bit 0 hidup.
2. `set(2)` → bit 0 dan 2 hidup.
3. `flip(2)` → bit 2 mati, sisa bit 0.
4. `reset(0)` → kosong.
5. `set()` → semua hidup, `count=4`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int toggleLaluHitung(int i, int j) {
    bitset<4> bs;
    bs.set(i);
    bs.flip(j);
    return (int)bs.count();
}

int main() {
    FASTIO;
    cout << toggleLaluHitung(0, 2) << '\n'; // 2: bit 0 nyala, bit 2 jadi nyala
    cout << toggleLaluHitung(0, 0) << '\n'; // 0: set lalu flip bit yang sama
    return 0;
}
```

**Jebakan:**
1. `set(i)` dua kali dianggap menambah 2 — bit tetap 1.
2. `flip` seluruh `bs.flip()` membalik  semua N bit, termasuk yang tidak kamu pakai.
3. `test` versus `[]` — keduanya sah, `test` lebih eksplisit.

**Kompleksitas:** O(1) per bit, O(N/64) untuk operasi seluruh bitset.

---

## Geser bitset

> **Ide satu kalimat:** geser kiri menambah semua jumlah lama dengan k; bit yang keluar terbuang.

### Geser bitset

**Teori:** Analoginya fotokopi daftar pencapaian, lalu geser fotokopi sejauh k. `bs << k` memindahkan tiap bit i ke i+k. Bit yang melewati N-1 hilang. `bs >> k` menuju 0. Alasan benar: ini transisi “ambil barang bernilai k” pada subset sum. Geser tidak memutar; tidak ada wrap-around.

**Kapan:** Pakai DP boolean jumlah, konvolusi OR sederhana. Jangan geser negatif. Jangan N terlalu kecil sehingga jumlah terpotong diam-diam.

**Proses:** bitset 8-bit, bit 0 dan 2 hidup (`00000101`), geser 2.

| Operasi | Bit hidup | Arti jumlah |
| --- | --- | --- |
| awal | 0, 2 | {0, 2} |
| `<< 2` | 2, 4 | {2, 4} |
| `|=` dengan awal | 0, 2, 4 | {0, 2, 4} |

1. Awal mewakili jumlah 0 dan 2.
2. Geser 2 mewakili “ambil 2 lagi”.
3. OR menggabungkan “tidak ambil” dan “ambil”.
4. Bit 6 tidak hidup karena tidak ada rantai itu.
5. Jika N=4, geser 2 dari bit 2 hilang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bitset<8> gabungGeser(const bitset<8>& bs, int k) {
    return bs | (bs << k);
}

int main() {
    FASTIO;
    bitset<8> bs;
    bs.set(0);
    bs.set(2);
    auto gabung = gabungGeser(bs, 2);
    cout << gabung[0] << gabung[2] << gabung[4] << '\n'; // 111
    return 0;
}
```

**Jebakan:**
1. `N` lebih kecil dari jumlah maksimum — bit terpotong, jawaban “tidak mungkin” palsu.
2. Geser `ll` biasa overflow, bukan bitset.
3. `<<` versus `>>` tertukar arah.

**Kompleksitas:** O(N/64) per geser, memori O(N/8).

---

## Subset sum dengan bitset

> **Ide satu kalimat:** `dp |= dp << a[i]` artinya “semua jumlah lama, plus semua jumlah lama + a[i]”.

### Subset sum dengan bitset

**Teori:** Analoginya fotokopi daftar pencapaian, lalu geser fotokopi sejauh `a[i]`, lalu gabung. Bit `j` hidup = ada subset berjumlah j. Awal: bit 0 hidup (subset kosong). Transisi: `dp |= dp << x`. Alasan benar: OR menggabungkan “tidak ambil” (bit lama) dan “ambil” (bit geser). Ini Day 026: subset sum satu baris.

**Kapan:** Pakai n≤1000, jumlah ≤ 1e5–1e6. Jangan jika nilai negatif (geser tidak mundur). Jangan jika perlu **rekonstruksi** subset tanpa jejak tambahan.

**Proses:** barang `{2, 3, 5}`, target 5.

| Barang | Jumlah yang mungkin |
| ---: | --- |
| (kosong) | {0} |
| +2 | {0, 2} |
| +3 | {0, 2, 3, 5} |
| +5 | {0, 2, 3, 5, 7, 8, 10} |

1. `dp = 1` (bit 0).
2. +2: `{0,2}`.
3. +3: `{0,2,3,5}`.
4. Target 5 sudah hidup sebelum barang 5.
5. Target 4 tidak pernah hidup.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int SUMMAX = 1000;

bool subsetSum(const vector<int>& a, int target) {
    bitset<SUMMAX + 1> dp;
    dp[0] = 1;
    for (int x : a) {
        if (x <= SUMMAX) dp |= (dp << x);
    }
    return target <= SUMMAX && dp.test(target);
}

int main() {
    FASTIO;
    vector<int> a = {2, 3, 5};
    cout << subsetSum(a, 5) << '\n';  // 1
    cout << subsetSum(a, 4) << '\n';  // 0
    cout << subsetSum(a, 10) << '\n'; // 1 = 2+3+5
    return 0;
}
```

**Jebakan:**
1. `SUMMAX` terlalu kecil — bit terpotong diam.
2. Barang 0 membuat loop tak berubah (aman) atau tak terhitung (tergantung soal).
3. Target negatif.
4. Mengira urutan barang mengubah kemungkinan — untuk subset sum tidak.

**Kompleksitas:** waktu O(n · SUMMAX / 64), memori O(SUMMAX / 8).

---

## AND OR XOR massal

> **Ide satu kalimat:** satu operator menggabungkan 64 keputusan boolean sekaligus.

### AND OR XOR massal

**Teori:** Analoginya dua penggaris lubang: AND hanya lubang yang tembus dua-duanya, OR lubang mana pun, XOR lubang yang berbeda. Pada `bitset`, `&=`, `|=`, `^=` berjalan per blok 64 bit. Alasan benar: irisan himpunan, gabungan, dan beda simetris jadi O(N/64), bukan O(N).

**Kapan:** Pakai irisan teman bersama, visibilitas, filter mask. Jangan jika kamu butuh jumlah aritmetika, bukan boolean.

**Proses:** A = {0,1,3}, B = {1,2,3}, N=8.

| Operasi | Hasil himpunan |
| --- | --- |
| A AND B | {1, 3} |
| A OR B | {0, 1, 2, 3} |
| A XOR B | {0, 2} |

1. Irisan dua orang.
2. Gabungan empat orang.
3. Yang hanya di satu sisi: 0 dan 2.
4. `count` pada AND = ukuran irisan.
5. Ini pola “berapa teman bersama” pada graf kecil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int ukuranIrisan(bitset<8> a, bitset<8> b) {
    return (int)(a & b).count();
}

int ukuranBeda(bitset<8> a, bitset<8> b) {
    return (int)(a ^ b).count();
}

int main() {
    FASTIO;
    bitset<8> a, b;
    a.set(0); a.set(1); a.set(3);
    b.set(1); b.set(2); b.set(3);
    cout << ukuranIrisan(a, b) << '\n'; // 2
    cout << ukuranBeda(a, b) << '\n';   // 2
    return 0;
}
```

**Jebakan:**
1. `a & b` tanpa menaruh hasil — ekspresi terbuang.
2. Tertukar XOR dengan OR.
3. Membandingkan `bitset` dengan `==` setelah geser yang terpotong, mengira masih sama.

**Kompleksitas:** O(N/64) waktu, O(N/8) memori.

---

## Menghitung bit

> **Ide satu kalimat:** `__builtin_popcountll` menghitung lampu yang nyala, bukan nilainya.

### Menghitung bit

**Teori:** Analoginya menghitung saklar ON di papan 64 saklar. GCC/Clang: `popcount`, `ctz` (trailing zeros = indeks bit terendah), `clz` (leading zeros). Alasan benar di bitmask n≤20: iterasi subset, pecah mask. `x & -x` isolasi bit terendah. `x & (x-1)` mematikan bit terendah. Pada `bitset`, `count()` sudah cukup.

**Kapan:** Pakai bitmask, cek paritas bit, enumerasi subset. Jangan `__builtin_*` jika butuh portable murni tanpa GCC — di kontes GCC hampir selalu ada. Jangan `ctz(0)`.

**Proses:** `x = 12` = `1100₂`.

| Fungsi | Hasil | Arti |
| --- | ---: | --- |
| popcount | 2 | dua bit nyala |
| ctz | 2 | dua nol di ekor |
| `x & -x` | 4 | bit terendah |
| `x & (x-1)` | 8 | padamkan bit terendah |

1. Dua lampu hidup: bit 2 dan 3.
2. Bit terendah indeks 2.
3. Isolasi memberi 4.
4. Mematikan terendah menyisakan 8.
5. `ctz(0)` tidak terdefinisi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int banyakBit(ll x) { return __builtin_popcountll(x); }
int bitTerendahIdx(ll x) { return __builtin_ctzll(x); }
ll matikanTerendah(ll x) { return x & (x - 1); }

int main() {
    FASTIO;
    ll x = 12;
    cout << banyakBit(x) << '\n';      // 2
    cout << bitTerendahIdx(x) << '\n'; // 2
    cout << matikanTerendah(x) << '\n'; // 8
    return 0;
}
```

**Jebakan:**
1. `ctz(0)` undefined.
2. `popcount` pada `ll` memakai versi `int` — salah untuk bit 32–63.
3. Signed negatif: pakai `unsigned` atau `ll` dengan hati-hati.

**Kompleksitas:** O(1) per builtin, memori O(1).

---

## Iterasi bit menyala

> **Ide satu kalimat:** jangan loop 0..63 jika kamu bisa loncat dari lampu ke lampu.

### Iterasi bit menyala

**Teori:** Analoginya koridor gelap: kamu hanya berhenti di lampu yang nyala. `x & -x` mengambil lampu terendah, lalu padamkan, ulangi. Alasan benar: jika hanya 3 bit hidup di mask 64-bit, kamu kerja 3 langkah, bukan 64. Pada `bitset`, loop `for (int i = 0; i < N; i++) if (bs[i])` masih O(N); untuk N besar, blok `uint64_t` manual lebih cepat.

**Kapan:** Pakai enumerasi subset, pecah mask, tetangga bit. Jangan jika N kecil dan loop biasa lebih jelas.

**Proses:** mask `12` = bit 2 dan 3.

1. `low = 4`, indeks 2, padamkan → `x=8`.
2. `low = 8`, indeks 3, padamkan → `x=0`.
3. Selesai. Dua iterasi.
4. Mask 0 tidak masuk loop.
5. Urutan dari bit rendah ke tinggi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> indeksBit(ll x) {
    vector<int> idx;
    while (x) {
        ll low = x & -x;
        idx.push_back(__builtin_ctzll(low));
        x ^= low;
    }
    return idx;
}

int main() {
    FASTIO;
    auto idx = indeksBit(12);
    cout << idx.size() << '\n'; // 2
    cout << idx[0] << ' ' << idx[1] << '\n'; // 2 3
    return 0;
}
```

**Jebakan:**
1. `x & -x` pada `int` dengan bit 31 — overflow signed.
2. Loop `i=0..63` lalu lupa `x` bertipe `ll`.
3. `x ^= low` versus `x -= low` — sama untuk satu bit, tapi `^=` lebih jujur.

**Kompleksitas:** O(jumlah bit nyala), memori O(jumlah bit) jika disimpan.

---

## Mask integer 64-bit

> **Ide satu kalimat:** kalau N≤64, `unsigned long long` sering lebih ringan dari `bitset`.

### Mask integer 64-bit

**Teori:** Analoginya satu kotak saklar genggam. `1ULL << i` menyalakan bit i. `(m >> i) & 1` bertanya. `m |= 1ULL << i` nyalakan, `m &= ~(1ULL << i)` matikan. Alasan benar: n≤20 bitmask DP muat di `int`. n=60 masih muat di `unsigned long long`. `1 << 31` pada `int` overflow; wajib `1LL` atau `1ULL`.

**Kapan:** Pakai n≤64, DP bitmask, himpunan kecil. Jangan `1 << i` untuk i≥31 pada `int`. Jangan n=70 tanpa `bitset` atau dua `ull`.

**Proses:** Nyalakan bit 1 dan 4 pada mask 0.

1. `m |= 1ULL << 1` → 2.
2. `m |= 1ULL << 4` → 18.
3. `test(4)` = 1, `test(3)` = 0.
4. Matikan bit 1 → 16.
5. `popcount` = 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

unsigned long long nyalakan(unsigned long long m, int i) {
    return m | (1ULL << i);
}

bool nyala(unsigned long long m, int i) {
    return (m >> i) & 1ULL;
}

int main() {
    FASTIO;
    unsigned long long m = 0;
    m = nyalakan(m, 1);
    m = nyalakan(m, 4);
    cout << nyala(m, 4) << ' ' << nyala(m, 3) << '\n'; // 1 0
    cout << __builtin_popcountll(m) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `1 << 32` pada `int`.
2. Geser sebesar 64 — undefined.
3. Mencetak mask sebagai `int` bertanda, jadi negatif.

**Kompleksitas:** O(1) per operasi, memori 8 byte.

---

## bitset versus vector bool

> **Ide satu kalimat:** `vector<bool>` adalah spesialisasi aneh; `bitset` lebih jujur untuk bit massal.

### bitset versus vector bool

**Teori:** Analoginya laci yang kelihatan seperti vector, tetapi isinya bukan `bool` sungguhan. `vector<bool>` memampatkan bit, proxy referensi rusak, dan tidak punya AND massal. `bitset<N>` punya operator bit, tetapi N tetap. `vector<char>` atau `vector<uint64_t>` adalah jalan tengah. Alasan benar: banyak TLE/WA dari `&v[i]` pada `vector<bool>`.

**Kapan:** Pakai `bitset` jika N tetap dan butuh geser/AND. Pakai `vector<char>` untuk flag dinamis. Jangan `vector<bool>` kecuali kamu sadar konsekuensinya.

**Proses:** Tandai indeks 1 dan 4, hitung yang hidup.

1. `bitset<8>`: `set` + `count` = 2.
2. `vector<char>`: `a[1]=a[4]=1`, loop jumlah 2.
3. `vector<bool>`: jumlah 2, tetapi `&a[1]` tidak sah.
4. Geser hanya ada di `bitset`.
5. N runtime hanya mudah di vector.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int hitungFlag(const vector<char>& a) {
    int s = 0;
    for (char x : a) s += (x != 0);
    return s;
}

int main() {
    FASTIO;
    vector<char> a(8, 0);
    a[1] = 1;
    a[4] = 1;
    cout << hitungFlag(a) << '\n'; // 2
    bitset<8> bs;
    bs.set(1);
    bs.set(4);
    cout << bs.count() << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. `vector<bool>::reference` sebagai `auto&`.
2. Mengira `vector<bool>` secepat `bitset` pada AND.
3. N compile-time lupa diubah saat constraint ganti.

**Kompleksitas:** akses O(1); operasi massal hanya cepat pada `bitset` / blok 64-bit.

---

## Graf kecil sebagai bitset

> **Ide satu kalimat:** baris adj[u] adalah himpunan tetangga; irisan dua baris adalah teman bersama.

### Graf kecil sebagai bitset

**Teori:** Analoginya absen kelas: tiap orang punya selembar centang “siapa temannya”. `adj[u] & adj[v]` lalu `count()` = banyak tetangga bersama. Alasan benar: n≤2000, n²/64 muat; tiga loop n³ tidak. Ini bukan max-flow; ini hanya irisan himpunan.

**Kapan:** Pakai n≤2000–4000, hitung segitiga, teman bersama. Jangan n=1e5 — pakai daftar sisi biasa. Jangan graf berbobot.

**Proses:** n=4, sisi 0-1, 0-2, 1-2, 1-3.

| u | tetangga |
| ---: | --- |
| 0 | 1, 2 |
| 1 | 0, 2, 3 |
| 2 | 0, 1 |
| 3 | 1 |

1. Irisan 0 dan 1: {2} → 1 teman bersama.
2. Irisan 0 dan 3: kosong.
3. Segitiga 0-1-2 terlihat dari irisan.
4. Derajat 1 = `adj[1].count() = 3`.
5. Sisi tak berarah: nyalakan dua arah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const int NMAX = 64;

int temanBersama(const vector<bitset<NMAX>>& adj, int u, int v) {
    return (int)(adj[u] & adj[v]).count();
}

int main() {
    FASTIO;
    vector<bitset<NMAX>> adj(4);
    auto tambah = [&](int u, int v) {
        adj[u].set(v);
        adj[v].set(u);
    };
    tambah(0, 1);
    tambah(0, 2);
    tambah(1, 2);
    tambah(1, 3);
    cout << temanBersama(adj, 0, 1) << '\n'; // 1
    cout << (int)adj[1].count() << '\n';     // 3
    return 0;
}
```

**Jebakan:**
1. Hanya satu arah pada graf tak berarah.
2. `NMAX` lebih kecil dari n.
3. Menghitung irisan termasuk u atau v sendiri jika ada loop.

**Kompleksitas:** bangun O(n+m), irisan O(n/64), memori O(n²/8).

---

## Ringkasan

- `bitset<N>`: N compile-time, `to_string` bit besar di kiri.
- Subset sum: `dp |= dp << x`, jaga `SUMMAX`.
- `popcountll` untuk 64 bit; `ctz(0)` haram.
- `1ULL << i`, bukan `1 << i` untuk i besar.
- `vector<bool>` bukan vector biasa.
- Graf kecil: irisan baris adj.

Kembali ke [algoritma STL](algoritma-stl.md) atau lanjut array: [prefix dan difference](../03-array/prefix-difference.md).
