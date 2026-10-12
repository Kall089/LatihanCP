# 28 — Li Chao tree (Day 244 lanjut)

[← D&C / Knuth](27-dnc-knuth.md) · [README](README.md) · [Alien / slope →](29-alien-slope.md)

> **Satu kalimat:** kalau slope dan `x` keduanya acak, deque CHT salah; Li Chao adalah segment tree yang di tiap node menyimpan **satu garis** dan berduel di titik tengah.

Day ComprogLearning: **244 lanjut**. File [26](26-cht.md) sudah membahas deque + ide duel `mid`. File ini implementasi penuh, bandingkan kapan deque cukup, dan DP yang **gagal monoton**.

Tiga pertanyaan:

```
1. STATE     : node [L,R] menyimpan garis yang terbaik di mid; DP tetap dp[i]
2. TRANSISI  : insert: yang kalah di mid turun ke anak; query: min sepanjang jalur
3. BASIS     : pohon kosong → +INF; dp[0] = 0 lalu insert garis j = 0
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [STATE TRANSISI BASIS](#state-transisi-basis)
- [Deque vs Li Chao](#deque-vs-li-chao)
- [Proses duel di mid](#proses-duel-di-mid)
- [Proses query](#proses-query)
- [Proses DP slope acak](#proses-dp-slope-acak)
- [Domain: array, kompres, sparse](#domain-array-kompres-sparse)
- [Sisip garis pada segmen](#sisip-garis-pada-segmen)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Convex Hull Trick menyimpan selubung bawah garis `y = m x + c`. Jika garis masuk dengan slope monoton dan query `x` monoton, deque di [26](26-cht.md) cukup. Begitu salah satu urutan rusak, `pop_front` membuang garis yang masih dibutuhkan.

Li Chao tree tidak menjaga hull secara eksplisit. Ia mempartisi domain `x` seperti segment tree. Di tiap segmen `[L,R]` disimpan **paling banyak satu** garis. Saat garis baru datang:

1. Evaluasi lama vs baru di `mid = (L+R)/2`.
2. Garis yang **lebih baik di mid** tinggal di node ini.
3. Garis yang kalah di mid mungkin masih menang di kiri atau kanan — ia turun ke anak itu saja.
4. Karena dua garis berpotongan paling banyak sekali, sisi yang kalah tidak perlu dikunjungi.

Analoginya: dua tarif taksi. Di kilometer tengah kota, pilih yang lebih murah. Yang kalah hanya mungkin lebih murah di pinggir kiri **atau** pinggir kanan, tidak keduanya (kecuali garis identik).

Query `x`: jalan dari akar ke daun yang memuat `x`, ambil minimum evaluasi semua garis di jalur. Setiap garis yang pernah "menang" di suatu ancestor bisa jadi yang terbaik di `x`.

Ini **bukan** state DP baru. Ini struktur `add_line(m, c)` dan `query(x)` yang menggantikan loop `for j`.

---

## Kapan

**Kapan dipakai.**

| Gejala | Alat |
|---|---|
| `min_j (dp[j] + m[j] * x[i])`, `m` dan `x` acak | Li Chao |
| `m` monoton, `x` acak | deque + binary search, atau Li Chao |
| `m` dan `x` keduanya monoton | deque [26](26-cht.md) — lebih pendek |
| garis hanya hidup di `[ql, qr]` | Li Chao + descent ke segmen |
| `n ≤ 2000` dan rumus belum yakin | `O(n^2)` dulu |
| `C(j,i)` bukan linear | D&C / Knuth [27](27-dnc-knuth.md), bukan Li Chao |

**Kapan tidak.**

1. Slope sudah turun dan `x` sudah naik — deque lebih jarang bug overflow.
2. Transisi `min dp[j] + |h[i]-h[j]|` — bukan garis; jangan memaksa.
3. Domain `x` kontinu real tanpa kompres — butuh hati-hati `mid`.
4. Kamu hanya butuh satu query setelah semua garis — bisa sort + hull statis.

---

## STATE TRANSISI BASIS

Struktur, bukan DP:

**STATE:** tiap node merepresentasikan interval integer `x ∈ [L, R]` dan menyimpan garis `ln` yang saat ini terbaik di `mid`. Anak kiri `[L, mid]`, anak kanan `[mid+1, R]`.

**TRANSISI insert:**

```
jika node kosong: simpan nw, selesai
bandingkan nw vs ln di mid
jika nw lebih baik di mid: tukar (nw jadi yang kalah)
jika L == R: selesai
jika yang kalah lebih baik di L: turun kiri
else: turun kanan
```

**TRANSISI query(x):**

```
ans = ln.eval(x)   (atau +INF jika kosong)
jika x <= mid: ans = min(ans, query kiri)
else:          ans = min(ans, query kanan)
```

**BASIS:** pohon kosong, `query` = `+INF` (minimisasi). Setelah `dp[0] = 0`, insert garis milik `j = 0`.

Untuk DP:

```
1. STATE     : dp[i] = biaya min mencapai i
2. TRANSISI  : dp[i] = query(x[i]) + extra[i]; add(m[i], dp[i] + shift[i])
3. BASIS     : dp[0] = 0
```

Kalimat lengkap: `dp[i]` adalah jawaban optimal untuk prefiks sampai indeks `i`, dan hull/Li Chao hanya mengingat kandidat `j` sebagai garis.

---

## Deque vs Li Chao

File 26 memakai contoh monoton (frog kuadrat, slope `-2h`). Di sini kita sengaja merusak monoton.

Misal `dp[i] = min_{j < i} (dp[j] + m[j] * x[i])`, `dp[0] = 0`.

```
i :  0   1   2   3
x :  3   1   8   2
m :  2  -3   4  -1
```

`x` meloncat 3→1→8→2. `m` meloncat 2→−3→4→−1. Deque `query` yang `pop_front` **dilarang**.

Hitung naif:

| i | x | kandidat j | nilai | dp[i] |
|---|---|---|---|---|
| 1 | 1 | j=0: 0+2·1=2 | 2 | 2 |
| 2 | 8 | j=0: 16; j=1: 2+(−3)·8=−22 | −22 | −22 |
| 3 | 2 | j=0: 4; j=1: 2−6=−4; j=2: −22+4·2=−14 | −14 | −14 |

Li Chao harus menghasilkan `2, -22, -14`.

Kalau kamu memaksa deque dan `pop_front` saat `x` turun dari 3 ke 1, garis depan (slope 2) bisa terbuang, lalu saat `x=8` jawaban rusak.

**Aturan praktis:**

| Syarat | Struktur |
|---|---|
| insert slope turun, query `x` naik | deque `O(n)` |
| insert slope turun, query `x` acak | deque + `queryBs`, jangan `pop_front` |
| insert slope acak | Li Chao / set dinamis |
| garis hidup sebagian domain | Li Chao segmen |

Deque **bukan** subset Li Chao secara kode: deque menjaga urutan potong. Li Chao menjaga duel lokal. Keduanya benar pada input monoton; hanya Li Chao yang benar pada input acak.

---

## Proses duel di mid

Domain integer `x ∈ [0, 8]`. Akar `[0,8]`, `mid = 4`.

Garis (beda dari 26):

```
P:  y = 3x + 7      eval(4) = 19
Q:  y = -2x + 15    eval(4) = 7
R:  y =  x + 4      eval(4) = 8
S:  y = -4x + 30    eval(4) = 14
```

### Insert P

Pohon kosong. Akar menyimpan `P`.

### Insert Q

```
lef = Q(0) < P(0)  →  15 < 7   ? false
md  = Q(4) < P(4)  →   7 < 19  ? true
```

`md` benar → tukar: akar jadi `Q`, yang kalah = `P`.
`lef != md` → `P` turun ke kiri `[0,4]`.

Kiri `[0,4]`, `mid=2`:

```
node kosong → simpan P
```

### Insert R

Akar ada `Q`. `mid=4`:

```
R(4)=8, Q(4)=7  → R kalah di mid, tidak tukar
R(0)=4, Q(0)=15 → R lebih baik di kiri
lef=true, md=false → R turun kiri
```

Kiri `[0,4]` ada `P`, `mid=2`:

```
R(2)=6, P(2)=13 → R menang di mid → tukar, kalah = P
R(0)=4, P(0)=7  → yang sekarang di node (R) lebih baik di L
lef untuk P: P(0)<R(0)? 7<4 false
md sudah dipakai untuk tukar
P kalah di mid dan di L → P turun kanan anak ini, yaitu [3,4]
```

`[3,4]` kosong, simpan `P`.

### Insert S

Akar `Q`, `mid=4`:

```
S(4)=14, Q(4)=7 → S kalah di mid
S(0)=30, Q(0)=15 → S kalah di L
S(8)=−2, Q(8)=−1 → S menang tipis di R
lef=false, md=false → S turun kanan [5,8]
```

Kanan kosong, simpan `S`.

Pohon setelah empat insert (sketsa):

```
[0,8]  Q: -2x+15
 ├─[0,4]  R: x+4
 │   └─[3,4]  P: 3x+7
 └─[5,8]  S: -4x+30
```

Cek manual beberapa `x`:

| x | P | Q | R | S | min | jalur Li Chao |
|---|---|---|---|---|---|---|
| 0 | 7 | 15 | 4 | 30 | **4** | Q=15, R=4 → 4 |
| 2 | 13 | 11 | 6 | 22 | **6** | Q=11, R=6 → 6 |
| 4 | 19 | 7 | 8 | 14 | **7** | Q=7, R=8, P=19 → 7 |
| 6 | 25 | 3 | 10 | 6 | **3** | Q=3, S=6 → 3 |
| 8 | 31 | −1 | 12 | −2 | **−2** | Q=−1, S=−2 → −2 |

Semua benar. Perhatikan `x=8`: `S` hanya hidup di anak kanan, tetapi tetap ketemu karena query turun ke kanan.

---

## Proses query

Query `x=6` langkah demi langkah:

```
akar [0,8], mid=4, garis Q: -2*6+15 = 3
6 > 4 → kanan [5,8], garis S: -4*6+30 = 6
min(3, 6) = 3
daun tercapai, selesai
```

Query `x=3`:

```
akar Q: -2*3+15 = 9
3 <= 4 → kiri [0,4], mid=2, garis R: 3+4 = 7
3 > 2 → kanan [3,4], garis P: 9+7 = 16
min(9, 7, 16) = 7
```

Manual: `P(3)=16, Q(3)=9, R(3)=7, S(3)=18` → 7. Cocok.

Jika node kosong, cabang itu menyumbang `+INF` dan diabaikan.

---

## Proses DP slope acak

Lanjut tabel `x = [3,1,8,2]`, `m = [2,-3,4,-1]`.

**STATE:** `dp[i]` = `min_{j<i} dp[j] + m[j]*x[i]`.

**TRANSISI:** `query(x[i])` lalu `add(m[i], dp[i])`.

**BASIS:** `dp[0]=0`, `add(2, 0)`.

Simulasi Li Chao domain misalnya `x ∈ [0, 8]`:

```
setelah j=0: garis 2x + 0
i=1, x=1: query=2, dp=2, add(-3, 2)   → y = -3x + 2
i=2, x=8: garis0: 16; garis1: -22; query=-22
          dp=-22, add(4, -22)         → y = 4x - 22
i=3, x=2: 2*2+0=4; -3*2+2=-4; 4*2-22=-14 → -14
```

Sama dengan naif.

Varian dengan extra di luar `min`:

```
dp[i] = extra[i] + min_j (dp[j] + m[j]*x[i])
```

`extra` tidak masuk garis. Contoh `extra = [0, 10, 0, 5]`:

```
dp[1] = 10 + 2 = 12, garis1: -3x + 12
dp[2] = 0 + min(2*8, 12-24) = min(16, -12) = -12
dp[3] = 5 + min(4, 12-6, -12+8) = 5 + min(4, 6, -4) = 1
```

Jangan memasukkan `extra[i]` ke intercept garis `i` jika `extra` hanya untuk `i` sebagai **tujuan**. Intercept garis `j` = `dp[j]` (+ suku yang bergantung `j` saja).

---

## Domain: array, kompres, sparse

Tiga implementasi yang sama secara teori.

### 1. Array tetap, `x` kecil

Kalau `x ∈ [0, X]` dan `X ≤ 1e6`, segment tree array `4X` muat. Indeks node seperti segtree biasa.

### 2. Kompres titik query

Kalau `x` sampai `1e9` tetapi hanya `n` nilai query, urutkan nilai unik, Li Chao pada indeks `0..n-1`. **Salah:** mengevaluasi garis di indeks kompres, bukan di `x` asli.

```
benar:  eval memakai x_asli, tree memotong menurut x_asli
salah:  mid = indeks, eval(mid) seolah mid adalah x
```

Kalau kamu kompres, node `[L,R]` harus berarti `x` di `[xs[L], xs[R]]`, dan `mid` adalah indeks, `eval(xs[mid])`.

### 3. Sparse / dinamis

Domain `[L,R] = [-1e9, 1e9]`, node dialokasi saat insert. Tiap insert `O(log X)` node baru. Memori `O(n log X)`. Cocok kontes `n ≤ 2e5`.

Pointer `new` di C++ kontes boleh bocor. Versi arena (`vector<Node>`) lebih rapi.

Jangan membuat array ukuran `1e9`.

---

## Sisip garis pada segmen

Kadang garis `y = m x + c` hanya berlaku untuk `x ∈ [ql, qr]` (tarif musiman, penawaran terbatas).

Pola sama dengan update range segtree: pecah `[ql,qr]` jadi `O(log X)` node kanonik, lalu jalankan duel Li Chao **hanya di dalam** node itu (seolah domain node adalah seluruh hidup garis).

```
add_segment(ql, qr, line):
    descent seperti update range
    saat [L,R] ⊆ [ql,qr]: insert_line biasa pada node ini
```

Query tetap titik. Garis di luar `[ql,qr]` tidak pernah masuk jalur yang relevan? Hati-hati: garis disimpan di node kanonik yang domainnya subset `[ql,qr]`, jadi query `x` hanya melihat garis jika `x` ada di dalam salah satu node itu — benar.

**Bukan** untuk soal 26: di sana setiap garis hidup di seluruh domain.

Contoh mini: garis `A: 5x+1` hanya di `[0,3]`, garis `B: -x+10` hanya di `[2,8]`.

```
x=1: hanya A → 6
x=2: A=11, B=8 → 8
x=7: hanya B → 3
```

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
const ll INF = (ll)4e18;

struct Line {
    ll m, c;
    Line(ll m = 0, ll c = INF) : m(m), c(c) {}
    ll eval(ll x) const {
        if (c >= INF / 2) return INF;
        return (ll)((__int128)m * x + c);
    }
};

struct LiChaoSparse {
    struct Node {
        Line ln;
        int l = -1, r = -1;
        Node() : ln() {}
        Node(Line x) : ln(x) {}
    };
    vector<Node> t;
    ll L, R;

    LiChaoSparse(ll l, ll r) : L(l), R(r) {
        t.reserve(64);
        t.push_back(Node());
    }

    int baru(Line ln = Line()) {
        t.push_back(Node(ln));
        return (int)t.size() - 1;
    }

    void insert(int p, ll l, ll r, Line nw) {
        ll mid = l + (r - l) / 2;
        bool lef = nw.eval(l) < t[p].ln.eval(l);
        bool md = nw.eval(mid) < t[p].ln.eval(mid);
        if (md) swap(nw, t[p].ln);
        if (l == r) return;
        if (lef != md) {
            if (t[p].l == -1) t[p].l = baru();
            insert(t[p].l, l, mid, nw);
        } else {
            if (t[p].r == -1) t[p].r = baru();
            insert(t[p].r, mid + 1, r, nw);
        }
    }

    void add(ll m, ll c) { insert(0, L, R, Line(m, c)); }

    ll query(int p, ll l, ll r, ll x) const {
        if (p == -1) return INF;
        ll ans = t[p].ln.eval(x);
        if (l == r) return ans;
        ll mid = l + (r - l) / 2;
        if (x <= mid) return min(ans, query(t[p].l, l, mid, x));
        return min(ans, query(t[p].r, mid + 1, r, x));
    }

    ll query(ll x) const { return query(0, L, R, x); }
};

struct LiChaoSeg {
    // insert line hanya pada [ql, qr]
    LiChaoSparse inner;
    LiChaoSeg(ll l, ll r) : inner(l, r) {}

    void addOn(int p, ll l, ll r, ll ql, ll qr, Line nw) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            inner.insert(p, l, r, nw);
            return;
        }
        ll mid = l + (r - l) / 2;
        if (inner.t[p].l == -1) inner.t[p].l = inner.baru();
        if (inner.t[p].r == -1) inner.t[p].r = inner.baru();
        addOn(inner.t[p].l, l, mid, ql, qr, nw);
        addOn(inner.t[p].r, mid + 1, r, ql, qr, nw);
    }

    void addSegment(ll ql, ll qr, ll m, ll c) {
        addOn(0, inner.L, inner.R, ql, qr, Line(m, c));
    }

    ll query(ll x) const { return inner.query(x); }
};

vector<ll> lichaoLinearDP(const vector<ll>& x, const vector<ll>& m) {
    int n = (int)x.size();
    ll lo = *min_element(x.begin(), x.end());
    ll hi = *max_element(x.begin(), x.end());
    if (lo > hi) return {};
    LiChaoSparse hull(lo, hi);
    vector<ll> dp(n, INF);
    dp[0] = 0;
    hull.add(m[0], dp[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = hull.query(x[i]);
        hull.add(m[i], dp[i]);
    }
    return dp;
}

vector<ll> bruteLinearDP(const vector<ll>& x, const vector<ll>& m) {
    int n = (int)x.size();
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            dp[i] = min(dp[i], dp[j] + m[j] * x[i]);
    return dp;
}

ll minOfLines(const vector<Line>& ls, ll x) {
    ll ans = INF;
    for (const auto& ln : ls) ans = min(ans, ln.eval(x));
    return ans;
}

int main() {
    FASTIO;
    LiChaoSparse t(0, 8);
    t.add(3, 7);
    t.add(-2, 15);
    t.add(1, 4);
    t.add(-4, 30);
    for (ll x : {0LL, 2, 4, 6, 8})
        cout << t.query(x) << (x == 8 ? '\n' : ' ');
    // 4 6 7 3 -2

    vector<ll> xs = {3, 1, 8, 2};
    vector<ll> ms = {2, -3, 4, -1};
    auto dp = lichaoLinearDP(xs, ms);
    auto br = bruteLinearDP(xs, ms);
    for (int i = 0; i < 4; i++)
        cout << dp[i] << " " << br[i] << "\n";
    // 0 0, 2 2, -22 -22, -14 -14

    LiChaoSeg seg(0, 8);
    seg.addSegment(0, 3, 5, 1);
    seg.addSegment(2, 8, -1, 10);
    cout << seg.query(1) << " " << seg.query(2) << " " << seg.query(7) << "\n";
    // 6 8 3
    return 0;
}
```

Versi max: simpan `(-m, -c)`, query min, kalikan −1. Atau ganti `<` menjadi `>` dan `INF` menjadi `-INF`.

---

## Jebakan

1. **Pakai deque padahal `x` tidak monoton.** Gejala: tes kecil lolos kebetulan, tes acak WA.

2. **`eval` overflow `ll`.** `m` dan `x` bisa `±1e9`. Wajib `__int128` seperti di atas.

3. **`mid = (l+r)>>1` pada domain negatif.** Untuk `l=-5, r=-1` biasanya aman; untuk `l+r` overflow, pakai `l + (r-l)/2`.

4. **Kompres: `eval(mid_indeks)`.** Harus `eval(xs[mid])`.

5. **Query sebelum ada garis.** Kembalikan `INF`, jangan `0`.

6. **Urutan add vs query.** Untuk `j < i`, query dulu, baru add garis `i`.

7. **Max vs min.** Satu tanda `<` terbalik merusak semua duel.

8. **Dua garis sama di mid.** `swap` atau tidak harus konsisten; keduanya sah asal sisi dipilih dari `lef != md`.

9. **Domain tidak memuat semua `x`.** Query di luar `[L,R]` turun salah atau crash.

10. **Garis segmen memakai insert global.** Tarif terbatas jadi berlaku di mana-mana.

11. **Membandingkan Li Chao dengan deque pada input acak lalu "Li Chao salah".** Yang salah biasanya overflow atau domain.

12. **Memory: array `4e9`.** Sparse / kompres.

13. **`c = INF` lalu `m * x + c` wrap.** Guard di `eval`.

14. **Lupa shift `h[j]^2` ke intercept** saat rumus kuadrat — itu rumus, bukan bug Li Chao. Jabarkan dulu seperti 26, baru masukkan `m,c`.

---

## Kompleksitas

| Operasi | Waktu | Memori |
|---|---|---|
| insert / query sparse | `O(log (R-L+1))` | `O(n log X)` |
| insert array `X` | `O(log X)` | `O(X)` |
| insert pada segmen | `O(log^2 X)` | `O(n log X)` |
| naif `O(n^2)` | `O(n^2)` | `O(n)` |

Untuk `n = 2e5`, `X = 2e9`: `log X ≈ 32`, aman.

Jangan kalikan dimensi DP di dalam tiap node. Li Chao **mengganti** loop `j`, bukan menambah layer.

---

## Tabel uji

| Tes | Hasil |
|---|---|
| P,Q,R,S query 0,2,4,6,8 | 4 6 7 3 −2 |
| DP `x=3,1,8,2` `m=2,-3,4,-1` | 0, 2, −22, −14 |
| satu garis `2x+3`, query 5 | 13 |
| pohon kosong, query 0 | INF |
| segmen A `[0,3]`, B `[2,8]` | 6, 8, 3 |

Brute garis:

```cpp
void tesAcak() {
    mt19937_64 rng(42);
    for (int tc = 0; tc < 50; tc++) {
        int n = 30;
        vector<Line> ls;
        LiChaoSparse t(-1000, 1000);
        for (int i = 0; i < n; i++) {
            ll m = (ll)rng() % 21 - 10;
            ll c = (ll)rng() % 41 - 20;
            ls.push_back(Line(m, c));
            t.add(m, c);
        }
        for (ll x = -20; x <= 20; x++)
            assert(t.query(x) == minOfLines(ls, x));
    }
}
```

Samakan `lichaoLinearDP` vs `bruteLinearDP` pada `n ≤ 40` acak.

---

## Checklist

1. Tulis `O(n^2)`, jabarkan `m, c, x`.
2. Cek monoton. Kalau gagal → Li Chao, bukan paksa deque.
3. Domain memuat semua query (dan insert `x` jika perlu).
4. `__int128` di `eval`.
5. Query sebelum add.
6. Min vs max sadar.
7. Uji 4 6 7 3 −2 dan DP 0 2 −22 −14.
8. Kalau `C` bukan garis → [27](27-dnc-knuth.md).
9. Kalau `m` dan `x` monoton → [26](26-cht.md) deque.

---

## Kenapa duel cukup satu anak?

Dua garis berpotongan di paling banyak satu titik. Setelah yang lebih baik di `mid` tinggal:

- jika yang kalah lebih baik di `L`, potong ada di kiri `mid` → hanya anak kiri perlu garis kalah;
- jika yang kalah lebih baik di `R`, potong ada di kanan;
- jika yang kalah kalah di `L` dan di `mid`, ia hanya mungkin menang di kanan.

Tidak ada kasus "kalah di mid tetapi menang di kiri **dan** kanan" — itu akan berarti dua potong, mustahil untuk garis lurus.

Gambar mental: `V` terbalik vs `V` biasa. Yang lebih rendah di tengah menutup yang lain di satu sisi.

---

## Hubungan dengan set dinamis

Alternatif Li Chao: `std::set` garis terurut slope, hapus yang tertutup dengan uji potong `__int128` (hull dinamis). 

| | Li Chao | set hull |
|---|---|---|
| kode | duel mid, pendek | `isBad` + iterator, panjang |
| domain | butuh `[L,R]` | tidak |
| segmen hidup | alami | sulit |
| monoton | overkill | overkill |

Untuk kontes DP linear, Li Chao biasanya lebih cepat ditulis setelah template ada. Untuk geometri murni, set kadang lebih fleksibel (hapus garis).

File ini **tidak** mengulang `isBad` deque 26. Uji potong hanya relevan jika kamu menulis set.

---

## Max-hull singkat (bukan contoh 26)

Garis `y = -x + 3`, `y = 2x - 8`, `y = 0x + 1`. Ingin **maksimum**.

```
x=0: 3, -8, 1 → 3
x=4: -1, 0, 1 → 1
x=6: -3, 4, 1 → 4
```

Implementasi: `add(-m, -c)`, `query` min, hasil `−query`.

```
add(1, -3), add(-2, 8), add(0, -1)
min di 0: -3 → max 3
min di 4: -1 → max 1
min di 6: -4 → max 4
```

---

## Proses kompres yang benar

Query `x = {100, 7, 100, 50}`. Unik terurut `xs = [7, 50, 100]`.

Node bukan `[0,2]` dengan `eval(1)` (itu `m*1+c`, salah). Node `[0,2]` berarti `x` di `{7,50,100}`, `mid=1`, duel di `x=50`.

```cpp
void insertIdx(int p, int l, int r, Line nw, const vector<ll>& xs) {
    int mid = (l + r) / 2;
    bool lef = nw.eval(xs[l]) < t[p].ln.eval(xs[l]);
    bool md = nw.eval(xs[mid]) < t[p].ln.eval(xs[mid]);
    // sama seperti biasa, anak [l,mid] / [mid+1,r]
}
```

Kalau semua `x` sudah dijamin masuk `[min,max]` asli, sparse pada nilai asli lebih sulit salah daripada kompres.

---

## DP dengan extra dan shift

Rumus yang sering muncul (bentuk lain, **bukan** frog `h=1,3,6` di 26):

```
dp[i] = min_j dp[j] + A[j] * B[i] + D[j]
```

```
m = A[j]
c = dp[j] + D[j]
x = B[i]
```

`D[j]` masuk intercept. `B[i]` hanya di query.

Kalau ada suku `E[i]` di luar:

```
dp[i] = E[i] + query(B[i])
```

Contoh angka: `A = [4, 0, -2]`, `B = [5, 1, 3]`, `D = [0, 7, 2]`, `E = [0, 0, 10]`, `dp[0]=0`.

```
garis0: 4x + 0
i=1: query(1)=4, dp=0+4=4, garis1: 0*x + (4+7)=11
i=2: query(3)= min(12, 11, ...) = 11? 
     j=0: 0+4*3+0=12
     j=1: 4+0*3+7=11
     dp=10+11=21
```

Li Chao harus 21.

---

## Kapan tetap deque meski "terasa acak"

Baca ulang constraint. Banyak soal AtCoder/CSES menjamin `h` menaik. Jika `h` terurut, **jangan** tulis Li Chao 80 baris — deque 40 baris lebih mudah di-debug.

Tanda boleh deque:

1. Statement: "strictly increasing".
2. Kamu sort sendiri tanpa merusak makna (jarang untuk DP urutan waktu).
3. `b[j]` berasal dari prefiks yang monoton berdasar rumus.

Tanda wajib Li Chao:

1. `x[i] = a[i]` tidak terurut.
2. Garis datang dari update offline acak.
3. Garis hidup di interval `x`.

---

## Ringkasan dinding

```
duel di mid, yang kalah turun satu anak
query = min eval di jalur akar-daun
x dan m acak → Li Chao
x dan m monoton → deque 26
uji: query 4 6 7 3 -2
uji DP: 0 2 -22 -14
eval pakai __int128
```

Lanjut: kadang yang kamu butuhkan bukan garis, melainkan **binary search pada slope** — [29](29-alien-slope.md).
