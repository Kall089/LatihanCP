# 26 — Convex Hull Trick (Day 244)

[← Broken profile](25-broken-profile.md) · [README](README.md) · [D&C / Knuth →](27-dnc-knuth.md)

> **Satu kalimat:** `dp[i] = min_j (dp[j] + b[j] * a[i])` adalah query garis; deque membuang garis yang tidak pernah optimal.

Day ComprogLearning: **244**. Pakai setelah kamu sudah bisa menulis `O(n^2)` yang benar. Li Chao = ide pohon garis jika monoton gagal.

Tiga pertanyaan:

```
1. STATE     : dp[i] tetap jawaban prefiks i; hull menyimpan kandidat j
2. TRANSISI  : dp[i] = hull.query(x[i]) + extra[i]; hull.add(m[i], c[i])
3. BASIS     : dp[0] = 0, masukkan garis j = 0
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [Ubah rumus jadi garis](#ubah-rumus-jadi-garis)
- [Syarat deque](#syarat-deque)
- [Proses garis](#proses-garis)
- [Proses DP kuadrat](#proses-dp-kuadrat)
- [Li Chao: ide](#li-chao-ide)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Banyak DP `O(n^2)` berbentuk

```
dp[i] = min_{j < i}  (  A[i] * B[j]  +  C[j]  )  +  D[i]
```

Untuk `i` tetap, `A[i]` adalah `x`, tiap `j` adalah garis `y = m_j x + c_j` dengan `m_j = B[j]`, `c_j = C[j]`. Kita butuh **minimum** (atau maksimum) atas garis di `x = A[i]`.

Gambar: banyak garis di bidang. Yang pernah jadi yang terendah membentuk **selubung bawah** (convex hull). Garis di tengah-tengah yang selalu di atas dua tetangganya tidak pernah terpakai — buang.

Analoginya: toko menawarkan tarif `biaya tetap + harga per unit * x`. Untuk tiap `x`, pilih tarif termurah. Jika harga per unit monoton, tarif baru hanya perlu dibandingkan dengan dua terakhir.

Convex Hull Trick (CHT) = struktur yang menjaga selubung itu.

---

## Kapan

**Kapan dipakai.**

| Gejala | Alat |
|---|---|
| `min (dp[j] + b[j]*a[i])`, `a` monoton, `b` monoton | deque CHT `O(n)` |
| slope monoton, `x` acak | hull terurut + binary search `O(n log n)` |
| slope dan `x` keduanya acak | Li Chao / hull dinamis (set) |
| transisi `min dp[j] + (h[i]-h[j])^2` | jabarkan → CHT |
| transisi `min dp[j] + |h[i]-h[j]|` | biasanya deque lain / D&C, bukan CHT |

**Kapan tidak.**

1. `C(j,i)` bukan linear di `i` setelah jabar.
2. `n ≤ 2000` dan kamu belum yakin rumus — tulis `O(n^2)` dulu.
3. Slope tidak monoton tapi kamu memaksa deque — WA diam.

---

## Ubah rumus jadi garis

Contoh AtCoder DP-Z / Frog 3:

```
dp[i] = min_j dp[j] + (h[i] - h[j])^2 + C
```

Jabarkan:

```
(h[i]-h[j])^2 = h[i]^2 + h[j]^2 - 2 h[i] h[j]
dp[i] = h[i]^2 + C + min_j ( dp[j] + h[j]^2 - 2 h[j] * h[i] )
```

Garis `j`:

```
m = -2 * h[j]
c = dp[j] + h[j]^2
x = h[i]
```

`dp[i] = h[i]^2 + C + query(h[i])`.

Jika `h` menaik, `x` menaik. `m = -2h` menurun. Deque **min** sah.

**Latihan jabar:** `dp[i] = min_j dp[j] + a[i]*b[j]` sudah jadi garis, `D[i]=0`.

`dp[i] = min_j (sum[i]-sum[j])^2 + dp[j]`:

```
= sum[i]^2 + min_j ( dp[j] + sum[j]^2 - 2 sum[i] sum[j] )
m = -2 sum[j], c = dp[j]+sum[j]^2, x = sum[i]
```

---

## Syarat deque

Untuk **minimisasi**, insert garis dengan slope **menurun** (lebih kecil), query `x` **menaik**:

1. Buang belakang: garis baru membuat tengah tidak pernah optimal.
2. Query: buang depan jika garis kedua sudah lebih baik di `x` sekarang (karena `x` hanya naik, garis depan tidak kembali).

Untuk **maksimisasi**: kebalikan tanda, atau kalikan `m,c,x` dengan −1 dan pakai min.

Uji `isBad(a,b,c)`: perpotongan `a,b` vs `b,c`. `b` buruk jika potong `a,b` di kanan potong `b,c` (untuk min hull, slope turun).

Banding silang tanpa `double`:

```
(b.b - a.b) / (a.m - b.m) >= (c.b - b.b) / (b.m - c.m)
```

Kali silang, hati-hati arah pembagi (slope turun ⇒ `a.m > b.m > c.m`, pembagi positif). Pakai `__int128`.

---

## Proses garis

Min-hull, slope `3, 1, -1`, query `x = 0, 2, 5`.

```
A: 3x + 0
B: 1x + 5     potong A/B: 3x = x+5 → x=2.5
C: -x + 12    potong B/C: x+5 = -x+12 → x=3.5
```

Apakah B buruk? Potong A/B = 2.5 < potong B/C = 3.5, B masih hidup di `[2.5, 3.5]`.

```
x=0: A=0, B=5, C=12 → 0
x=2: A=6, B=7, C=10 → 6
x=5: A=15, B=10, C=7 → 7
```

Deque query: mulai A di depan. Di `x=2` masih A. Di `x=5` geser ke C.

Kalau kita insert D: `m=-1, c=100` (lebih buruk dari C, slope sama): simpan intercept lebih kecil saja, buang D.

---

## Proses DP kuadrat

`h = [1, 3, 6]`, `C = 0`, `dp[0]=0`.

```
j=0: m=-2, c=0+1=1
i=1, x=3: query = -2*3+1 = -5
     dp[1] = 9 + (-5) = 4
     cek: (3-1)^2 = 4

j=1: m=-6, c=4+9=13
i=2, x=6:
     garis0: -12+1=-11
     garis1: -36+13=-23
     query=-23
     dp[2]=36-23=13
     cek: 0+(6-1)^2=25, 4+(6-3)^2=13
```

---

## Li Chao: ide

Kalau `m` dan `x` acak, deque salah.

**Li Chao tree:** segment tree pada domain `x` (kompres jika perlu). Tiap node menyimpan **satu** garis yang terbaik di titik tengah segmen. Saat insert garis baru:

- bandingkan baru vs tersimpan di `mid`,
- yang lebih baik di `mid` tinggal,
- yang lebih baik di kiri/kanan turun ke anak yang domainnya "menang di sisi itu".

Query `x`: jalan ke daun, min evaluasi garis di jalur.

**STATE:** bukan DP baru; ini struktur `add_line(m,c)` dan `query(x)`.

**Tidak** kita tulis pohon lengkap 200 baris di sini — ide cukup: "segtree of lines, fight at mid". Implementasi penuh biasanya Day lanjut / pustaka. Untuk monoton, **deque lebih pendek dan lebih jarang bug**.

Kalau domain `x` sampai `1e9`, Li Chao rekursif pada rentang `[L,R]` tanpa array 1e9: tiap insert `O(log^2)` node baru (sparse) atau `O(log)` jika array kompres `n` titik query.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

struct Line {
    ll m, b;
    ll eval(ll x) const { return m * x + b; }
};

struct MinConvexHull {
    deque<Line> hull;

    static bool isBad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(b.b - a.b) * (b.m - c.m) >=
               (__int128)(c.b - b.b) * (a.m - b.m);
    }

    void add(ll m, ll b) {
        Line cur{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b) return;
            hull.pop_back();
        }
        while (hull.size() >= 2 && isBad(hull[hull.size() - 2], hull.back(), cur))
            hull.pop_back();
        hull.push_back(cur);
    }

    ll query(ll x) {
        while (hull.size() >= 2 && hull[1].eval(x) <= hull[0].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }

    ll queryBs(ll x) const {
        int lo = 0, hi = (int)hull.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hull[mid].eval(x) <= hull[mid + 1].eval(x)) hi = mid;
            else lo = mid + 1;
        }
        return hull[lo].eval(x);
    }
};

vector<ll> chtLinearDP(const vector<ll>& a, const vector<ll>& b) {
    int n = (int)a.size();
    vector<ll> dp(n, 0);
    MinConvexHull hull;
    hull.add(b[0], dp[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = hull.query(a[i]);
        hull.add(b[i], dp[i]);
    }
    return dp;
}

vector<ll> frogSquare(const vector<ll>& h, ll C) {
    int n = (int)h.size();
    vector<ll> dp(n, 0);
    MinConvexHull hull;
    hull.add(-2 * h[0], dp[0] + h[0] * h[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = h[i] * h[i] + C + hull.query(h[i]);
        hull.add(-2 * h[i], dp[i] + h[i] * h[i]);
    }
    return dp;
}

int main() {
    FASTIO;
    MinConvexHull h;
    h.add(3, 0);
    h.add(1, 5);
    h.add(-1, 12);
    cout << h.query(0) << " " << h.query(2) << " " << h.query(5) << "\n";
    // 0 6 7

    vector<ll> hs = {1, 3, 6};
    auto dp = frogSquare(hs, 0);
    for (ll x : dp) cout << x << " ";
    cout << "\n"; // 0 4 13
    return 0;
}
```

Sketsa Li Chao (domain `[ql, qr]`, min), ide saja:

```cpp
struct LiChao {
    struct Node {
        Line ln;
        Node *l = nullptr, *r = nullptr;
        Node(Line x) : ln(x) {}
    };
    Node* root = nullptr;
    ll L, R;
    LiChao(ll l, ll r) : L(l), R(r) {}

    void insert(Node*& p, ll l, ll r, Line nw) {
        if (!p) {
            p = new Node(nw);
            return;
        }
        ll mid = (l + r) >> 1;
        bool lef = nw.eval(l) < p->ln.eval(l);
        bool md = nw.eval(mid) < p->ln.eval(mid);
        if (md) swap(nw, p->ln);
        if (l == r) return;
        if (lef != md) insert(p->l, l, mid, nw);
        else insert(p->r, mid + 1, r, nw);
    }

    ll query(Node* p, ll l, ll r, ll x) {
        if (!p) return 4e18;
        ll mid = (l + r) >> 1;
        ll ans = p->ln.eval(x);
        if (l == r) return ans;
        if (x <= mid) return min(ans, query(p->l, l, mid, x));
        return min(ans, query(p->r, mid + 1, r, x));
    }
};
```

Ini **ide**. Perhatikan overflow `eval`, domain negatif, dan memory leak di kontes (boleh). Untuk soal monoton, pakai deque.

---

## Jebakan

1. **Slope tidak monoton + deque.** WA. Cek `b[j]` sebelum coding.

2. **Overflow potong.** Wajib `__int128`, bukan `double` untuk koordinat `1e9`.

3. **Max vs min.** `<=` terbalik. Uji tiga garis di atas.

4. **Query hull kosong.**

5. **Dua slope sama:** simpan `b` lebih kecil (untuk min).

6. **Lupa `h[i]^2` di luar `min`.**

7. **`C` dikali jumlah lompatan vs sekali.** Baca soal.

8. **`query` merusak deque lalu query `x` lebih kecil.** Deque query hanya untuk `x` monoton. Kalau `x` acak: `queryBs` dan **jangan** `pop_front`.

9. **Urutan add vs query.** Biasanya query dulu (pakai `j < i`) lalu add `i`.

10. **Kalikan `m*x` overflow `ll` sebelum `__int128` di `eval`.** Jika `m,x` 1e9, `m*x` 1e18 masih `ll`; 2e9*2e9 pecah. Pakai `__int128` di `eval` jika ragu.

---

## Kompleksitas

| Struktur | Add | Query | Syarat |
|---|---|---|---|
| deque | amort. O(1) | amort. O(1) | slope & x monoton |
| deque + binsearch | O(1) | O(log n) | slope monoton, x acak |
| Li Chao | O(log X) | O(log X) | domain X |
| naif O(n^2) | — | — | n ≤ 4000 |

Memori: `O(n)` garis.

---

## Tabel uji

| Tes | Hasil |
|---|---|
| query 0,2,5 pada A,B,C | 0 6 7 |
| frog h=1,3,6 C=0 | dp 0 4 13 |
| satu garis 2x+3, query 5 | 13 |
| dua slope sama, b=10 lalu b=4 | simpan 4 |

Brute:

```cpp
vector<ll> bruteFrog(const vector<ll>& h, ll C) {
    int n = (int)h.size();
    vector<ll> dp(n, 4e18);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++) {
            ll d = h[i] - h[j];
            dp[i] = min(dp[i], dp[j] + d * d + C);
        }
    return dp;
}
```

Samakan `frogSquare` vs `bruteFrog` pada `h` menaik acak `n ≤ 80`.

---

## Checklist

1. Tulis dulu `O(n^2)`, jabarkan, identifikasi `m, c, x`.
2. Cek monoton `m` dan `x`.
3. Min vs max.
4. `__int128` di `isBad`.
5. Query sebelum add jika `j < i`.
6. Uji 0,6,7 dan frog 0,4,13.
7. Kalau gagal monoton: Li Chao / `queryBs`, bukan paksa deque.

---

## Kapan D&C lebih cocok

Jika `dp[i][j] = min_k dp[i-1][k] + C(k,j)` dan `opt` monoton tetapi `C` **bukan** garis, pakai [27](27-dnc-knuth.md), bukan CHT.

CHT = geometri garis. D&C opt = monoton titik pecah. Jangan menukar nama.

---

## Turunan `isBad` (min, slope turun)

Tiga garis `a,b,c` dengan `m_a > m_b > m_c`. Potong:

```
x_ab = (b.b - a.b) / (a.m - b.m)
x_bc = (c.b - b.b) / (b.m - c.m)
```

`b` tidak berguna jika `x_ab >= x_bc` (selubung bawah: `b` di atas titik potong `a-c`).

Kalikan (`a.m-b.m > 0`, `b.m-c.m > 0`):

```
(b.b - a.b) * (b.m - c.m) >= (c.b - b.b) * (a.m - b.m)
```

Itu `__int128` di kode. Jika slope **naik** (kamu salah urutan insert), pembagi negatif — rumus pecah. Insert harus sudah terurut slope.

---

## Max hull singkat

Ingin `max (m x + c)`. Opsi paling aman: simpan garis `(-m, -c)`, query min, kalikan −1. Atau salin `isBad` dengan `<=` dibalik dan `eval` lebih besar `pop_front`.

Uji: garis `y=x`, `y=3`, `y=-x+10`. Max di `x=0,2,6` = `3, 3, 4`? 

```
x=0: 0,3,10 → 10
x=2: 2,3,8 → 8
x=6: 6,3,4 → 6
```

---

## Proses `chtLinearDP`

`a = [0, 1, 2, 4]`, `b = [5, 3, 2, 0]`, `dp[i]=min_{j<i} dp[j]+b[j]*a[i]`, `dp[0]=0`.

```
hull: (m=5,c=0)
i=1 x=1: query=5, dp=5, add (3,5)
i=2 x=2: garis5:10, garis3:6+5=11?  3*2+5=11, min=10
        tunggu dp[j]+b[j]*a[i]: j=0 → 0+5*2=10; j=1 → 5+3*2=11 → 10
        add (2,10)
i=3 x=4: j=0: 0+20=20; j=1:5+12=17; j=2:10+8=18 → 17
```

Deque min, slope 5,3,2,0 turun, `x` 1,2,4 naik. Sah.

Cek `isBad` saat insert slope 2: potong (5,0)-(3,5) di `x=(5-0)/(5-3)=2.5`. Potong (3,5)-(2,10) di `(10-5)/(3-2)=5`. 2.5 < 5, tengah hidup.

---

## Integer `x` vs `double`

Jangan simpan potong sebagai `double` lalu banding `1e-12` untuk `x` 1e9. Kali silang `__int128` menutup kasus `m` beda 1, `b` beda 1e18.

---

## Urutan add jika slope naik

Kalau data `b[j]` naik tetapi rumus minta slope turun, kamu mungkin memaksimisasi atau salah jabar. Jangan `reverse` deque tanpa uji.

Opsi: insert ke **depan** (simetris) — mudah kacau. Lebih aman sort ulang indeks menurut slope, lalu query dengan `queryBs` jika `i` tidak ikut terurut.

---

## Template cek monoton

```cpp
bool slopeTurun(const vector<ll>& b) {
    for (int i = 1; i < (int)b.size(); i++)
        if (b[i] > b[i - 1]) return false;
    return true;
}
```

Kalau `false`, deque `query` (yang `pop_front`) dilarang.

---

## Ringkasan dinding

```
y = m x + c
min hull, slope turun, x naik → deque
jabarkan (h[i]-h[j])^2 → m=-2h[j]
Li Chao: segtree, duel di mid
uji: 0 6 7 dan dp 0 4 13
```
