# Cross, orientasi, convex hull

[← Geometri](README.md) · [Sweep →](sweep.md) · [Indeks CP](../README.md)

Day 240. Titik pakai `ll`. Cross = luas jajaran genjang bertanda = belok. Jangan bandingkan `double` dengan `==`.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [Titik dan vektor](#titik-dan-vektor)
- [Dot dan cross](#dot-dan-cross)
- [Orientasi](#orientasi)
- [Urutan polar](#urutan-polar)
- [Segmen dan potong](#segmen-dan-potong)
- [Titik di dalam](#titik-di-dalam)
- [Luas poligon](#luas-poligon)
- [Monotone chain](#monotone-chain)
- [Diameter himpunan](#diameter-himpunan)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Titik dan vektor

**Teori:** titik = pasangan koordinat. Vektor `B-A` = geseran A ke B. Jumlah, selisih, kali skalar.

Koordinat integer 10^9: cross `2e9*2e9=4e18` masih muat `ll`. `4e9*4e9` tidak — pakai `__int128`.

**Kapan:** semua geo 2D kontes. Jangan `double` untuk input bilangan bulat.

**Proses:** A=(0,0), B=(2,1). `B-A=(2,1)`, `2*(B-A)=(4,2)`.

**Kode:**

```cpp
struct Pt {
    ll x, y;
    Pt() : x(0), y(0) {}
    Pt(ll x_, ll y_) : x(x_), y(y_) {}
};

Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator*(Pt a, ll k) { return {a.x * k, a.y * k}; }

bool operator<(Pt a, Pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(Pt a, Pt b) { return a.x == b.x && a.y == b.y; }
```

**Jebakan:** overflow penjumlahan jarang; overflow kali sering. Baca batas.

**Kompleksitas:** O(1).

## Dot dan cross

**Teori:**

- Dot `a·b = ax*bx + ay*by`. Sama arah >0, tegak lurus 0, berlawanan <0. `|a|² = a·a`.
- Cross 2D `a×b = ax*by − ay*bx`. Luas bertanda. `b` di kiri `a` positif (CCW), kanan negatif (CW), sejajar 0.

Analogi setir: cross positif = belok kiri.

Bandingkan jarak dengan `norm2`, tanpa `sqrt`.

**Kapan:** orientasi, hull, potong, luas. `atan2` hanya jika sadar presisi.

**Proses:** A=(0,0), B=(2,0), C=(1,1), D=(1,-1), E=(3,0).

```
AB × AC = 2*1 - 0*1 = 2     C kiri
AB × AD = 2*(-1) = -2       D kanan
AB × AE = 0                 E segaris
AB · AC = 2                 sudut lancip
AB · AD = -2                tumpul
```

**Kode:**

```cpp
ll dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
ll cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
ll cross(Pt o, Pt a, Pt b) { return cross(a - o, b - o); }
ll norm2(Pt a) { return dot(a, a); }

int tanda(ll v) { return (v > 0) - (v < 0); }

__int128 cross128(Pt a, Pt b) {
    return (__int128)a.x * b.y - (__int128)a.y * b.x;
}
```

**Jebakan:** menulis `ax*by + ay*bx`. `hypot` untuk banding jarak.

**Kompleksitas:** O(1).

## Orientasi

**Teori:** `orient(o,a,b) = tanda(cross(o,a,b))`.

| Nilai | Arti |
|---|---|
| +1 | o→a→b belok kiri (CCW) |
| −1 | belok kanan (CW) |
| 0 | segaris |

Tiga titik segaris belum tentu b di antara o dan a. Cek bounding box / dot.

**Kapan:** hull, potong, sort sudut.

**Proses:** o=(0,0), a=(2,0), b=(1,1) → +1. b=(1,-1) → −1. b=(3,0) → 0.

Apakah (3,0) di segmen (0,0)–(2,0)? Segaris tapi di luar. `dot((3,0)-(0,0), (3,0)-(2,0))=2*1>0` tidak di antara.

**Kode:**

```cpp
int orient(Pt o, Pt a, Pt b) { return tanda(cross(o, a, b)); }

bool onSeg(Pt a, Pt b, Pt p) {
    if (orient(a, b, p) != 0) return false;
    return dot(p - a, p - b) <= 0;
}
```

**Jebakan:** `dot <= 0` untuk ujung: `p=a` → `dot(0, a-b)=0`, termasuk. Baik.

**Kompleksitas:** O(1).

## Urutan polar

**Teori:** sort di sekitar o dengan `cross`, tie jarak. Titik = o harus disingkirkan.

`cross>0` saja **tidak** mengurut 360° tanpa memisah setengah bidang. Untuk hull, monotone chain lebih aman (tidak butuh polar penuh).

**Kapan:** radial sweep, sudut.

**Proses:** o=(0,0), titik (1,0), (0,1), (−1,0), (1,1).

```
(1,0)×(0,1)=1>0 → (1,0) sebelum (0,1) pada CCW kuadran atas
```

**Kode:**

```cpp
bool lePolar(Pt o, Pt a, Pt b) {
    ll c = cross(o, a, b);
    if (c != 0) return c > 0;
    return norm2(a - o) < norm2(b - o);
}

void sortPolarSetengah(Pt o, vector<Pt>& v) {
    sort(v.begin(), v.end(), [&](Pt a, Pt b) { return lePolar(o, a, b); });
}

int kuadran(Pt p) {                         // 0: +x+y ... sesuaikan
    if (p.y >= 0 && p.x > 0) return 0;
    if (p.x <= 0 && p.y > 0) return 1;
    if (p.y <= 0 && p.x < 0) return 2;
    return 3;
}

bool lePolar360(Pt o, Pt a, Pt b) {
    Pt A = a - o, B = b - o;
    int qa = kuadran(A), qb = kuadran(B);
    if (qa != qb) return qa < qb;
    ll c = cross(A, B);
    if (c != 0) return c > 0;
    return norm2(A) < norm2(B);
}
```

**Jebakan:** titik berimpit o, semua cross 0. Kuadran (0,0) liar.

**Kompleksitas:** O(n log n).

## Segmen dan potong

**Teori:** AB dan CD berpotongan (termasuk ujung) jika masing-masing memisahkan ujung lawan, atau kolinear dan interval overlap.

`AB` memisahkan C,D: `orient(A,B,C)*orient(A,B,D) ≤ 0` dengan cabang `onSeg` untuk 0.

**Kapan:** geo ad-hoc, jembatan silang. Jangan intersection `double` jika soal ya/tidak.

**Proses:** A=(0,0), B=(2,2), C=(0,2), D=(2,0) → potong (1,1).

A=(0,0), B=(2,0), C=(3,0), D=(4,0): kolinear, [0,2]∩[3,4] kosong → tidak.

A=(0,0), B=(2,0), C=(2,0), D=(2,1): sentuh ujung B=C → ya jika termasuk ujung.

**Kode:**

```cpp
bool bboxOverlap(Pt a, Pt b, Pt c, Pt d) {
    if (max(a.x, b.x) < min(c.x, d.x)) return false;
    if (max(c.x, d.x) < min(a.x, b.x)) return false;
    if (max(a.y, b.y) < min(c.y, d.y)) return false;
    if (max(c.y, d.y) < min(a.y, b.y)) return false;
    return true;
}

bool segmenPotong(Pt a, Pt b, Pt c, Pt d) {
    int o1 = orient(a, b, c), o2 = orient(a, b, d);
    int o3 = orient(c, d, a), o4 = orient(c, d, b);
    if (o1 * o2 < 0 && o3 * o4 < 0) return true;
    if (o1 == 0 && onSeg(a, b, c)) return true;
    if (o2 == 0 && onSeg(a, b, d)) return true;
    if (o3 == 0 && onSeg(c, d, a)) return true;
    if (o4 == 0 && onSeg(c, d, b)) return true;
    return false;
}
```

**Jebakan:** `o1*o2 < 0` menolak ujung (hasil 0). Soal sentuhan butuh `onSeg`. `o1*o2` aman (−1,0,1).

**Kompleksitas:** O(1).

## Titik di dalam

**Teori:** poligon **cembung** CCW: semua `cross(sisi, p) ≥ 0` (termasuk batas). `cross==0` wajib `onSeg`.

Poligon sederhana: ray casting atau winding. Tepi integer rawan.

**Kapan:** hull + query titik. Non-convex: hati-hati.

**Proses:** segitiga (0,0),(2,0),(0,2). P=(1,0) di sisi. P=(1,1) di luar (di garis x+y=2? 1+1=2 di sisi miring). P=(0.5,0.5) dalam — integer (1,0) tepi, (1,1) tepi.

(1,1): cross (0,0)-(2,0)-(1,1)=2>0, (2,0)-(0,2)-(1,1)=0 onSeg? (1,1) di (2,0)-(0,2) ya.

**Kode:**

```cpp
bool diDalamConvex(const vector<Pt>& h, Pt p) {
    int n = (int)h.size();
    if (n == 0) return false;
    if (n == 1) return h[0] == p;
    if (n == 2) return onSeg(h[0], h[1], p);
    for (int i = 0; i < n; i++) {
        ll cr = cross(h[i], h[(i + 1) % n], p);
        if (cr < 0) return false;
        if (cr == 0 && !onSeg(h[i], h[(i + 1) % n], p)) return false;
    }
    return true;
}
```

**Jebakan:** hull CW: semua tanda terbalik. Ray casting lupa tepi.

**Kompleksitas:** O(n). Binsearch sudut O(log n) jika hull terurut.

## Luas poligon

**Teori:** shoelace. `2*luas = Σ (pi × p{i+1})`. Positif jika CCW. Titik integer: 2·luas integer. Banyak soal minta `x.5`.

Poligon berpotongan diri: nilai aljabar, bukan area visual.

Pick (lanjutan): `luas = i + b/2 - 1`.

**Kapan:** CSES *Polygon Area*.

**Proses:** (0,0),(2,0),(0,2).

```
cross: 0 + 4 + 0 = 4
luas = 2
```

**Kode:**

```cpp
ll duaLuas(const vector<Pt>& p) {
    int n = (int)p.size();
    ll a = 0;
    for (int i = 0; i < n; i++) a += cross(p[i], p[(i + 1) % n]);
    return a;
}

void cetakLuas(const vector<Pt>& p) {
    ll a = abs(duaLuas(p));
    cout << (a / 2);
    if (a & 1) cout << ".5";
    else cout << ".0";
    cout << '\n';
}
```

**Jebakan:** lupa `% n`. Overflow Σ. Mencetak `a/2` integer padahal 4.5.

**Kompleksitas:** O(n).

## Monotone chain

**Teori:** hull = pagar karet. Andrew:

1. Unikkan, sort `(x,y)`.
2. Lower kiri→kanan: pop selama belok kanan (atau lurus jika tidak simpan kolinear).
3. Upper kanan→kiri, syarat sama.
4. Gabung, buang ujung dobel.

Setelah sort, rantai monoton di x. Jaga belok kiri = cembung.

**Kapan:** titik ekstrem, diameter, convex layers. n=1,2 keluar awal. Semua kolinear: dua ujung, atau semua jika `keepColinear`.

**Proses:** (0,0),(1,0),(2,0),(1,1),(0,2).

```
sort: (0,0)(0,2)(1,0)(1,1)(2,0)
lower tanpa kolinear: (0,0)(2,0)
upper: (2,0)(1,1)(0,2)
hull CCW: (0,0)(2,0)(1,1)(0,2)
```

Langkah lower dengan pop lurus:

```
(0,0)
+(0,2)
+(1,0): cross (0,0)(0,2)(1,0) = ? (0,2)×(1,0)= -2 <0 belok kanan? 
sebenarnya sort x dulu: (0,0),(0,2),(1,0)...
```

Lebih aman jejak setelah sort x:

```
titik: (0,0),(1,0),(2,0),(1,1),(0,2)
sort: (0,0),(0,2),(1,0),(1,1),(2,0)  — (0,2) sebelum (1,0) karena x
```

Andrew tetap benar. Tes tangan: lower dari kiri menurut urutan sort.

**Kode:**

```cpp
vector<Pt> convexHull(vector<Pt> p, bool keepColinear = false) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = (int)p.size();
    if (n <= 2) return p;

    auto buruk = [&](Pt a, Pt b, Pt c) {
        ll cr = cross(a, b, c);
        if (keepColinear) return cr < 0;
        return cr <= 0;
    };

    vector<Pt> lo, hi;
    for (int i = 0; i < n; i++) {
        while (lo.size() >= 2 && buruk(lo[lo.size() - 2], lo.back(), p[i]))
            lo.pop_back();
        lo.push_back(p[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        while (hi.size() >= 2 && buruk(hi[hi.size() - 2], hi.back(), p[i]))
            hi.pop_back();
        hi.push_back(p[i]);
    }
    lo.pop_back();
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}
```

**Jebakan:** tidak `unique` → pop aneh. `cross<=0` buang kolinear. Lupa `pop_back` ujung. Graham polar dari min-y: rawan min tidak unik.

**Kompleksitas:** O(n log n) sort, rantai O(n).

## Diameter himpunan

**Teori:** dua titik terjauh ada di hull. h kecil: O(h²) `norm2`. h besar: rotating calipers O(h).

**Kapan:** “jarak terbesar”. Bandingkan kuadrat.

**Proses:** hull 4 titik, cek 6 pasangan.

**Kode:**

```cpp
ll diameter2(const vector<Pt>& h) {
    ll best = 0;
    int m = (int)h.size();
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            best = max(best, norm2(h[i] - h[j]));
    return best;
}

ll diameterTitik(vector<Pt> p) {
    auto h = convexHull(p);
    return diameter2(h);
}
```

**Jebakan:** `sqrt` lalu banding `double`. n=1 diameter 0.

**Kompleksitas:** O(n log n + h²).

## Uji naif

**Teori:** potong vs gambar. Hull: semua titik di dalam / di batas, luas maksimal.

**Kapan:** n kecil.

**Proses:** 5 titik di atas, luas hull 2·luas = 2*((0,0)×(2,0)+(2,0)×(1,1)+...) hitung.

**Kode:**

```cpp
int main() {
    FASTIO;
    Pt A(0, 0), B(2, 0), C(1, 1);
    cout << cross(A, B, C) << '\n';         // 2
    assert(segmenPotong({0, 0}, {2, 2}, {0, 2}, {2, 0}));
    assert(!segmenPotong({0, 0}, {2, 0}, {3, 0}, {4, 0}));
    vector<Pt> p = {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {0, 2}};
    auto h = convexHull(p);
    cout << h.size() << '\n';
    cetakLuas(h);
}
```

**Jebakan:** assert hull ukuran 4 tanpa kolinear. (1,0) terbuang.

**Kompleksitas:** O(1) contoh.

## Ringkasan

1. Cross `ax*by − ay*bx`. Positif = kiri.
2. Orient + `onSeg` = potong termasuk ujung.
3. Banding jarak pakai `norm2`.
4. Shoelace: 2·luas integer.
5. Hull = sort + rantai, jaga belok kiri.
6. Overflow: baca batas, `__int128` jika perlu.

Latihan Day 240. Jangan salin `exercise_*.cpp`.
