# 23 — DP bitset (Day 164)

[← Probabilitas](22-probabilitas.md) · [README](README.md) · [Game DP →](24-game.md)

> **Satu kalimat:** knapsack boolean / subset sum jadi `bs |= bs << w` — 64 transisi per register.

Day ComprogLearning: **164**. Melanjutkan [06](06-subset-sum.md). Bukan SOS ([17](17-sos.md)) dan bukan bitmask TSP ([15](15-bitmask-tsp.md)).

Tiga pertanyaan:

```
1. STATE     : bit j nyala = jumlah j bisa dibentuk
2. TRANSISI  : bs |= (bs << w)   atau shift-or string
3. BASIS     : bit 0 nyala
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [Subset sum](#subset-sum)
- [Proses angka](#proses-angka)
- [Unbounded vs 0-1](#unbounded-vs-0-1)
- [Shift-or string](#shift-or-string)
- [Banyak cara modulo 2](#banyak-cara-modulo-2)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** DP 0-1 knapsack "bisa / tidak" adalah array boolean `can[s]`. Transisi barang `w`:

```
for s = S..w:
    can[s] = can[s] || can[s-w]
```

Itu menggeser seluruh array `w` langkah lalu OR. `std::bitset` melakukan 64 bit sekaligus.

```
bs |= bs << w;
```

Analoginya: sisir gigi boolean, geser, satukan.

Keuntungan: `S / 64` lebih kecil. `n = 1000`, `S = 1e6` → `1e9` operasi naif berat; bitset ≈ `1e9/64 ≈ 1.5e7` plus konstanta.

Ini **bukan** menyimpan himpunan elemen sebagai mask. Nilai adalah **jumlah**, indeks bit = jumlah.

---

## Kapan

**Kapan dipakai.**

| Gejala | Bitset |
|---|---|
| subset sum / partition, `S ≤ 1e6`, `n ≤ 1e4` | ya |
| "apakah ada subset jumlah = k" | ya |
| banyak subset jumlah = k **modulo 2** | XOR shift (hati-hati) |
| string matching shift-or | ya, pola pendek |
| perlu **nilai max** bukan bisa/tidak | bukan; itu knapsack biasa |
| perlu rekonstruksi barang | bitset saja tidak cukup; simpan jejak terpisah |

**Kapan tidak.**

1. Jawaban "berapa cara" modulo 1e9+7 — bitset hanya 1 bit.
2. Kapasitas 1e9 — tidak ada indeks bit.
3. `W` negatif — geser ke kiri tidak berarti.
4. Ingin `O(n S / 64)` tapi `S = 1e8` — memori `1e8 bit ≈ 12 MB` masih, waktu `n*S/64` cek.

---

## Subset sum

**STATE:** `bs[j] = 1` jika ada subset (sudah diproses) berjumlah `j`.

**TRANSISI 0-1:** untuk tiap barang `w`: `bs |= bs << w`.

Kenapa tidak dobel-pakai barang? `bs << w` memakai **salinan lama** di sisi kanan `|=`. Dalam satu pernyataan, bit baru tidak dipakai lagi untuk barang yang sama. Itu penting.

**BASIS:** `bs[0] = 1`.

**Jawaban:** `bs[target]`. Partition: `total` genap dan `bs[total/2]`.

---

## Proses angka

Barang `{3, 5, 7}`, target 10? 3+7=10.

```
awal     bits 0:     1 00000000...
+3       <<3 OR:     1 00100000...     (0 dan 3)
+5       <<5 OR:     0,3,5,8
+7       <<7 OR:     0,3,5,8,7,10,12,15
```

`10` nyala. Ya.

Tanpa 7, `{3,5}`: 0,3,5,8 — 10 mati.

Simulasi bit kecil (`S = 16`):

```
step0  0000 0000 0000 0001   // bit 0
+3     0000 0000 0000 1001
+5     0000 0001 0010 1001   // 0,3,5,8
+7     1001 0101 1010 1001   // +7,10,12,15
```

---

## Unbounded vs 0-1

**0-1:** `bs |= bs << w` sekali per barang. Barang terpakai ≤ 1.

**Unbounded:** ingin memakai `w` berkali-kali. Naif:

```
for (int s = w; s <= S; s++)
    can[s] |= can[s-w];
```

Arah naik memakai hasil baru — itu **boleh ulang**.

Bitset unbounded **tidak** cukup satu `|= << w`, karena itu 0-1.

Kira-kira:

```
// ulang sampai stabil, atau
for (int k = 1; (w << (k-1)) <= S; k++)
    bs |= bs << (w * (1 << (k-1)));  // pecah biner stok tak terbatas hati-hati overflow
```

Lebih bersih: loop `bs |= bs << w` sebanyak `S/w` — terlalu lambat.

Unbounded bitset yang rapi: untuk tiap `w`, OR prefix "bisa mencapai s-w":

```
// untuk tiap bit s, if bs[s-w] then bs[s]=1, dari kecil
// bitset tidak punya loop arah mudah yang cepat
```

Kesimpulan: **bitset paling nyaman untuk 0-1**. Unbounded: array `char` naik, atau pecah biner stok besar lalu 0-1 bitset ([07](07-bounded-knapsack.md)).

**Bounded stok `c`:** pecah biner `1,2,4,...,sisa`, tiap potongan 0-1 `|= <<`.

---

## Shift-or string

**Teori:** pola `p` panjang `m ≤ 64` atau beberapa `ull`. Teks `t`.

`mask[c]` = bit posisi pola yang karakter `c`.

State `bit i` = "prefiks pola sepanjang i+1 cocok di sini". Geser 1, OR/AND sesuai literatur.

Salah satu bentuk (shift-and):

```
st = ((st << 1) | 1) & mask[t[i]];
if (st >> (m-1) & 1) match di i
```

**STATE:** bit ke-`j` = apakah `p[0..j]` mencocokkan `t[i-j..i]`.

**TRANSISI:** geser, masukkan bit baru, AND himpunan posisi yang karakternya cocok.

**BASIS:** kosong, lalu `| 1` mengizinkan mulai baru.

**Proses:** `t = ababc`, `p = ab`.

```
mask['a'] bit0, mask['b'] bit1
i=0 'a': st = 1 & mask_a = 1
i=1 'b': st = ((1<<1)|1) & mask_b = 3 & 2 = 2  → bit1 → match
```

Berguna jika `m ≤ 64` dan alfabet kecil, banyak query pola pendek. Untuk pola panjang: KMP (folder 12).

---

## Banyak cara modulo 2

Kalau hanya paritas banyak subset:

```
bs ^= bs << w;
```

XOR, bukan OR. Dua cara ke `s` saling mematikan.

**Bukan** jumlah cara biasa. Jangan pakai untuk "berapa subset", kecuali soal minta paritas.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool subsetSumBitset(const vector<int>& w, int target) {
    if (target < 0) return false;
    bitset<1000001> bs;
    bs[0] = 1;
    for (int x : w) {
        if (x <= target) bs |= (bs << x);
    }
    return bs[target];
}

bool canPartition(const vector<int>& w) {
    ll s = 0;
    for (int x : w) s += x;
    if (s % 2) return false;
    return subsetSumBitset(w, (int)(s / 2));
}

// S diketahui, kembalikan semua jumlah yang mungkin
vector<int> allSums(const vector<int>& w, int S) {
    bitset<1000001> bs;
    bs[0] = 1;
    for (int x : w)
        if (x <= S) bs |= (bs << x);
    vector<int> res;
    for (int i = 0; i <= S; i++)
        if (bs[i]) res.push_back(i);
    return res;
}

int minDiffPartition(const vector<int>& w) {
    int S = 0;
    for (int x : w) S += x;
    bitset<1000001> bs;
    bs[0] = 1;
    for (int x : w) bs |= (bs << x);
    int best = S;
    for (int i = 0; i <= S / 2; i++)
        if (bs[i]) best = min(best, S - 2 * i);
    return best;
}

vector<int> shiftAndMatches(const string& text, const string& pat) {
    int m = (int)pat.size();
    vector<int> pos;
    if (m == 0 || m > 64) return pos;
    unsigned long long mask[256] = {};
    for (int j = 0; j < m; j++)
        mask[(unsigned char)pat[j]] |= 1ULL << j;
    unsigned long long st = 0;
    unsigned long long need = 1ULL << (m - 1);
    for (int i = 0; i < (int)text.size(); i++) {
        st = ((st << 1) | 1ULL) & mask[(unsigned char)text[i]];
        if (st & need) pos.push_back(i - m + 1);
    }
    return pos;
}

bool subsetSumMod2(const vector<int>& w, int target) {
    bitset<1000001> bs;
    bs[0] = 1;
    for (int x : w)
        if (x <= target) bs ^= (bs << x);
    return bs[target];
}

int main() {
    FASTIO;
    cout << subsetSumBitset({3, 5, 7}, 10) << "\n"; // 1
    cout << subsetSumBitset({3, 5}, 10) << "\n";    // 0
    cout << canPartition({1, 5, 11, 5}) << "\n";    // 1
    cout << minDiffPartition({1, 6, 11, 5}) << "\n";
    auto p = shiftAndMatches("ababc", "ab");
    cout << p.size() << "\n"; // 2 : index 0 dan 2
    return 0;
}
```

Ukuran `bitset<1000001>` harus **konstanta compile-time**. Kalau `S` sampai 1e6, sediakan konstanta itu. `S = 1e7` → `bitset<10000001>` ≈ 1.25 MB, masih wajar.

Template dengan `S` dinamis: array `ull`:

```cpp
void orShift(vector<unsigned long long>& a, int sh, int bits) {
    int n = (int)a.size();
    int word = sh / 64, rem = sh % 64;
    for (int i = n - 1; i >= 0; i--) {
        unsigned long long val = 0;
        int src = i - word;
        if (src >= 0) val = a[src] << rem;
        if (rem && src - 1 >= 0) val |= a[src - 1] >> (64 - rem);
        a[i] |= val;
    }
    int last = bits % 64;
    if (last) a.back() &= (1ULL << last) - 1;
}
```

Arah loop dari kata tinggi: seperti knapsack 0-1 mundur, agar tidak memakai hasil baru. Hati-hati: `|=` in-place dari tinggi aman jika kita baca `src = i-word` yang sudah di-OR? Bisa kotor. Lebih aman salin `old = a` lalu OR ke salinan baru, atau `bitset`.

---

## Jebakan

1. **`bs << w` memakai `w` negatif / `w > size`.** Undefined atau semua 0.

2. **Unbounded ditulis `|= <<`.** Barang hanya sekali.

3. **`bitset` size < `target`.** `bs[target]` out of range — di `std::bitset` itu UB / salah.

4. **Rekonstruksi.** Setelah bitset, kamu tidak tahu barang mana. Simpan `parent[s]` di array terpisah **sebelum** optimasi, atau DP kedua.

5. **`int` jumlah `S`.** Jumlah `n * w` overflow sebelum cap.

6. **Mengira 64× selalu cukup.** Konstanta bitset lebih dari 1/64; ukur `n * (S/64)`.

7. **Shift-or pola `m > 64` tanpa multi-word.**

8. **`can[s] |= can[s-w]` naik untuk 0-1.** Dobel pakai. Bitset `|= <<` tidak kena jebakan ini — jangan "perbaiki" jadi loop naik.

9. **Partition total ganjil.** Langsung tidak.

10. **Memori 32 MB limit + beberapa `bitset<1e7>`.**

---

## Kompleksitas

```
waktu  ≈  O(n * S / 64)
memori ≈  O(S / 8) byte   (bitset)
```

| n | S | nS/64 |
|---|---|---|
| 200 | 1e5 | 3e5 |
| 1000 | 1e6 | 1.5e7 |
| 500 | 1e6 | 8e6 |
| 10000 | 1e5 | 1.5e7 |
| 1000 | 1e7 | 1.5e8  berat |

Naif boolean `O(n S)`: `n=200, S=1e5` = 2e7 masih hidup. Bitset menjadi wajib sekitar `nS > 5e8`.

---

## Tabel uji

| Barang | Target | Bisa |
|---|---|---|
| 3,5,7 | 10 | ya |
| 3,5 | 10 | tidak |
| 1,5,11,5 | partition | ya (1+5+5 vs 11) |
| kosong | 0 | ya |
| kosong | 1 | tidak |
| 2,2,2 | 3 | tidak |

Shift-and: `ababc` vs `ab` → posisi 0, 2.

---

## Checklist

1. 0-1 → `|= <<`. Unbounded → jangan itu.
2. `bs[0] = 1`.
3. Konstanta bitset `≥ target`.
4. `w ≤ target` sebelum geser.
5. Partition: genap dulu.
6. Bukan "berapa cara mod 1e9+7".
7. Uji `{3,5,7}` → 10.

---

## Hubungan file

| File | Perbedaan |
|---|---|
| [06](06-subset-sum.md) | teori bisa/tidak, array `char` |
| [05](05-01-knapsack.md) | nilai max, bukan bit |
| [07](07-bounded-knapsack.md) | pecah biner lalu bitset |
| [15](15-bitmask-tsp.md) | mask = himpunan elemen |
| [17](17-sos.md) | agregat per mask |
| folder 02 bitset STL | operasi `count`, `any`, bukan DP |

---

## Meet-in-the-middle + bitset

`n ≤ 40`, `S` besar: pecah 20+20, enumerasi jumlah kiri, bitset kanan? Enumerasi kanan 2^20 jumlah, simpan di `set` / sort. Bitset hanya jika **nilai** jumlah ≤ 1e7.

Kalau nilai `1e12`, bitset mustahil. Pakai sort + two pointers (folder 04 MITM).

---

## Rekonstruksi setelah bitset

Bitset hanya menjawab "bisa". Untuk daftar barang, simpan `from[s] = index barang` saat bit `s` **baru** nyala.

```cpp
vector<int> reconstruct(const vector<int>& w, int target) {
    const int S = target;
    bitset<1000001> bs;
    bs[0] = 1;
    vector<int> from(S + 1, -1);
    for (int i = 0; i < (int)w.size(); i++) {
        int x = w[i];
        if (x > S) continue;
        bitset<1000001> nxt = bs | (bs << x);
        bitset<1000001> baru = nxt & ~bs;
        for (int s = baru._Find_first(); s <= S; s = baru._Find_next(s))
            from[s] = i;
        bs = nxt;
    }
    if (!bs[target]) return {};
    vector<int> idx;
    for (int s = target; s > 0; ) {
        int i = from[s];
        idx.push_back(i);
        s -= w[i];
    }
    return idx;
}
```

`_Find_first` tergantung libstdc++. Alternatif: loop `s = S..x` seperti knapsack biasa hanya untuk jejak — lebih portabel, lebih lambat.

Uji `{3,5,7}` target 10: jejak `{0,2}` atau `{2,0}`.

---

## Beberapa target sekaligus

Satu bitset, lalu baca `bs[t]` untuk semua query `t ≤ S`. Itu alasan kuat memakai bitset dibanding `n` kali DFS.

Kalau query `t` sampai `1e12` tetapi barang `≤ 200` dan `n` kecil: bukan bitset, melainkan MITM / gcd.

---

## Grouped items (pilih tepat satu dari grup)

Untuk tiap grup, OR hasil "geser tiap opsi dari **salinan lama**":

```
old = bs
bs_new = 0  // atau old jika boleh tidak pilih
for w in grup:
    bs_new |= old << w
bs = bs_new
```

Jangan `|= <<` beruntun dalam satu grup — itu 0-1 semua opsi sekaligus (boleh ambil dua opsi).

---

## Proses `|=` vs loop mundur

Array `char can[S+1]`, 0-1:

```
for i barang:
    for s = S; s >= w[i]; s--
        can[s] |= can[s - w[i]]
```

Arah mundur = memakai salinan "sebelum barang i". `bs |= bs << w` adalah vektorisasi loop itu.

Arah naik = unbounded. Mengganti bitset dengan loop naik adalah bug 0-1.

Uji barang `{2}` dua kali vs sekali: 0-1 mencapai 2, bukan 4. `bs |= << 2` sekali → bit 0 dan 2, bukan 4.

---

## Count bit = banyak jumlah berbeda

`bs.count()` = banyak nilai yang bisa dibentuk, termasuk 0. Soal "berapa jumlah berbeda" = `count`. Soal "berapa selain 0" = `count-1` jika `bs[0]`.

---

## Cap `S` ke jumlah aktual

Jika `sum(w) < target`, langsung tidak. Jika `sum < bitset size`, loop `count` cukup sampai `sum`, bukan 1e6.

```cpp
int cap = 0;
for (int x : w) cap += x;
if (target > cap) return false;
```

---

## Ringkasan dinding

```
bs[0]=1
for w: bs |= bs << w          // 0-1
jawab bs[target]
waktu n S / 64
XOR <<  : paritas cara
satu grup: geser dari salinan lama
```
