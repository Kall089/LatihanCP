# 19 — Geometri, Nim, stress test, anti-hash

[← 18 string](18-string-hash-kmp-z-trie.md) · [README](README.md)

Folder 13, 14, dan 16 di `DAFTAR-MATERI`: geometri dasar, teori permainan, dan **cara kerja** kontes. Day 250 dan 252 tidak butuh prasyarat berat. Semakin awal dipakai, semakin banyak WA yang ketemu di rumah, bukan di *system test*.

Latihan harian: `ComProgLearning/CP` Day 240 (geo & hull), 236 (Sprague-Grundy), 250 (stress), 252 (random & anti-hash). Sweep line lanjut: Day 242.

`typedef long long ll`. Titik memakai `ll` supaya hasil kali tidak pecah di tengah. Jangan bandingkan `double` dengan `==`.

## Daftar isi

- [Titik, vektor, hasil kali](#titik-vektor-hasil-kali)
- [Orientasi dan belok](#orientasi-dan-belok)
- [Segmen, potong, di dalam](#segmen-potong-di-dalam)
- [Luas poligon](#luas-poligon)
- [Convex hull](#convex-hull)
- [Sweep line — peta](#sweep-line--peta)
- [Nim klasik](#nim-klasik)
- [Sprague-Grundy](#sprague-grundy)
- [Game DP singkat](#game-dp-singkat)
- [Stress test](#stress-test)
- [Memperkecil kasus](#memperkecil-kasus)
- [Random di kontes](#random-di-kontes)
- [Anti-hash](#anti-hash)
- [Checklist sebelum submit](#checklist-sebelum-submit)
- [Ringkasan](#ringkasan)

## Titik, vektor, hasil kali

**Teori:** titik adalah pasangan koordinat. Vektor `B-A` = geseran dari A ke B. Dua hasil kali yang wajib:

- **Dot** `a·b = ax*bx + ay*by`. Tanda: sama arah (>0), tegak lurus (0), berlawanan (<0). `|a|² = a·a`.
- **Cross** di 2D `a×b = ax*by − ay*bx`. Ini **luas jajaran genjang bertanda**. Tanda: `b` di kiri `a` (positif, CCW), di kanan (negatif, CW), sejajar (0).

Kenapa cross yang paling sering: hampir semua “di kiri / di kanan / segaris” adalah tanda `cross`. Tidak perlu sudut `atan2` kecuali kamu memang mengurutkan polar dan sudah sadar presisi.

Analogi: setir. Cross positif = belok kiri. Nol = lurus. Negatif = belok kanan.

**Kapan dipakai / kapan tidak.**

- Pakai: orientasi, hull, potong segmen, luas, urutan polar.
- Jangan: `double` untuk koordinat bilangan bulat 10⁹. Cross muat di `ll`? `2e9 * 2e9 = 4e18`, masih di bawah 9e18. `4e9*4e9` **tidak** muat — pakai `__int128` atau pecah rumus.

**Proses:** A=(0,0), B=(2,0), C=(1,1), D=(1,-1), E=(3,0).

```
AB × AC = 2*1 - 0*1 = 2     C di kiri AB
AB × AD = 2*(-1) - 0*1 = -2 D di kanan
AB × AE = 2*0 - 0*3 = 0     E segaris
AB · AC = 2*1 + 0*1 = 2     sudut lancip
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pt {
    ll x, y;
    Pt() : x(0), y(0) {}
    Pt(ll x_, ll y_) : x(x_), y(y_) {}
};

Pt operator+(Pt a, Pt b) { return {a.x + b.x, a.y + b.y}; }
Pt operator-(Pt a, Pt b) { return {a.x - b.x, a.y - b.y}; }
Pt operator*(Pt a, ll k) { return {a.x * k, a.y * k}; }

ll dot(Pt a, Pt b) { return a.x * b.x + a.y * b.y; }
ll cross(Pt a, Pt b) { return a.x * b.y - a.y * b.x; }
ll cross(Pt o, Pt a, Pt b) { return cross(a - o, b - o); } // o->a vs o->b
ll norm2(Pt a) { return dot(a, a); }

int tanda(ll v) { return (v > 0) - (v < 0); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Pt A(0, 0), B(2, 0), C(1, 1);
    cout << cross(A, B, C) << '\n';         // 2
}
```

**Jebakan:**

- Menulis `ax*by + ay*bx` — itu bukan cross.
- Overflow: dua kali 2·10⁹ aman di `ll`, dua kali 10¹⁸ tidak. Baca batas koordinat dulu.
- `hypot` dan `sqrt` untuk membandingkan jarak: bandingkan `norm2` tanpa akar.

**Kompleksitas:** O(1) per operasi. Memori O(1).

## Orientasi dan belok

**Teori:** `orient(o, a, b) = tanda(cross(o,a,b))`.

| Nilai | Arti |
| --- | --- |
| +1 | `o→a→b` belok kiri (CCW) |
| −1 | belok kanan (CW) |
| 0 | segaris |

Tiga titik segaris belum tentu `b` di antara `o` dan `a`. Cek bounding box / dot.

Urutan polar di sekitar `o`: sort dengan `orient`, tie-break jarak. Titik di `o` harus disingkirkan.

**Kapan dipakai / kapan tidak.**

- Pakai: sort sudut, cek belokan hull, titik di dalam sudut.
- `atan2` boleh untuk debug, rawan titik hampir segaris.

**Proses:** o=(0,0), titik (1,0), (0,1), (−1,0), (1,1).

```
urutan CCW dari sumbu +x: (1,0), (1,1), (0,1), (-1,0)
cross((1,0),(0,1))=1>0 jadi (0,1) di kiri (1,0) → belakangan di CCW? 
Sort: a sebelum b jika a×b > 0 (a di kanan b, jadi a lebih “awal” dari +x jika kuadran atas).
```

Uji mental: (1,0) × (0,1) = 1 > 0 → (1,0) sebelum (0,1) pada urutan CCW. Benar.

**Kode:**

```cpp
int orient(Pt o, Pt a, Pt b) { return tanda(cross(o, a, b)); }

bool lePolar(Pt o, Pt a, Pt b) {
    ll c = cross(o, a, b);
    if (c != 0) return c > 0;
    return norm2(a - o) < norm2(b - o);
}

void sortPolar(Pt o, vector<Pt>& v) {
    sort(v.begin(), v.end(), [&](Pt a, Pt b) { return lePolar(o, a, b); });
}
```

**Jebakan:** titik berimpit dengan `o` membuat semua cross 0, urutan acak. Kuadran bawah vs atas: rumus `cross>0` saja **tidak** mengurutkan penuh 360° tanpa memisahkan setengah bidang (misalnya `y>0 || (y==0 && x>0)` dulu). Untuk hull, kamu tidak butuh 360° — monotone chain lebih aman.

**Kompleksitas:** sort O(n log n).

## Segmen, potong, di dalam

**Teori:** dua segmen `AB` dan `CD` berpotongan (termasuk ujung) jika masing-masing memisahkan ujung yang lain, atau mereka kolinear dan intervalnya overlap.

`AB` memisahkan C dan D: `orient(A,B,C) * orient(A,B,D) ≤ 0`.

Kolinear: keempat orient 0, lalu cek proyeksi x dan y overlap.

Titik P di segmen AB: `orient(A,B,P)==0` dan `dot(P-A, P-B) ≤ 0` (P di antara, sudut di P tumpul terhadap A dan B).

**Kapan dipakai / kapan tidak.**

- Pakai: geometri ad-hoc, pipa, “apakah jembatan silang”.
- Jangan: floating intersection point jika soal hanya butuh ya/tidak.

**Proses:** A=(0,0), B=(2,2), C=(0,2), D=(2,0).

```
orient(A,B,C)= + , orient(A,B,D)= −  hasil kali <0
orient(C,D,A)= + , orient(C,D,B)= −
berpotongan di (1,1)
```

A=(0,0), B=(2,0), C=(3,0), D=(4,0): kolinear, interval x [0,2] dan [3,4] tidak overlap → tidak potong.

**Kode:**

```cpp
bool onSeg(Pt a, Pt b, Pt p) {
    if (orient(a, b, p) != 0) return false;
    return dot(p - a, p - b) <= 0;
}

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

Titik di dalam poligon sederhana: ray casting (hitung potongan ke kanan) atau winding. Untuk **convex** lebih mudah: semua belokan sama tanda.

```cpp
bool diDalamConvex(const vector<Pt>& h, Pt p) { // h CCW, termasuk batas
    int n = (int)h.size();
    if (n < 3) return n == 1 ? (h[0].x == p.x && h[0].y == p.y)
                             : (n == 2 && onSeg(h[0], h[1], p));
    for (int i = 0; i < n; i++) {
        ll cr = cross(h[i], h[(i + 1) % n], p);
        if (cr < 0) return false;           // di kanan sisi CCW → luar
        if (cr == 0 && !onSeg(h[i], h[(i + 1) % n], p)) return false;
    }
    return true;
}
```

**Jebakan:** `o1*o2 < 0` menolak ujung (hasil 0). Soal “termasuk sentuhan” butuh cabang `onSeg`. Overflow kali `o1*o2` tidak masalah karena nilainya −1,0,1. Titik integer di tepi sering salah jika hanya ray casting tanpa cek batas.

**Kompleksitas:** potong O(1), dalam convex O(n), dalam convex + binsearch sudut O(log n) jika hull terurut.

## Luas poligon

**Teori:** shoelace. Untuk poligon `p0..p_{n-1}`:

```
2 * luas = Σ (pi × p{i+1})     (p_n = p_0)
```

Nilai bertanda: positif jika CCW. Luas sesungguhnya = abs / 2. Untuk titik integer, 2·luas integer — cetak `L/2` atau `L/2.0` sesuai soal (banyak soal minta `x.5`).

Pick's theorem (lanjutan): `luas = i + b/2 - 1`. Berguna di lattice.

**Kapan dipakai / kapan tidak.** Poligon berpotongan diri: shoelace tetap jalan tetapi “luas” bernilai aljabar, bukan area visual.

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

**Jebakan:** lupa nutup poligon (`% n`). Overflow Σ cross. Mencetak `a/2` integer padahal soal ingin 4.5.

**Kompleksitas:** O(n).

## Convex hull

**Teori:** hull = pagar karet di sekeliling paku. Semua titik di dalam atau di batas poligon cembung terkecil.

**Monotone chain (Andrew):**

1. Unikkan dan urutkan titik `(x, y)`.
2. Bangun **lower** dari kiri ke kanan: selama belokan kanan (atau lurus, jika tidak ingin kolinear), pop.
3. Bangun **upper** dari kanan ke kiri, syarat sama.
4. Gabung, buang duplikat ujung.

Kenapa benar: setelah sortir, rantai bawah dan atas masing-masing monoton di x. Menjaga belokan kiri = menjaga cembung. Semua titik yang terbuang ada di kiri (CCW) pagar.

**Kapan dipakai / kapan tidak.**

- Pakai: diameter himpunan (rotating calipers), “titik ekstrem”, convex layers.
- Jangan: n=3 sudah cembung — tetap benar, uji.
- Semua kolinear: hull = dua ujung, atau seluruh titik jika kamu **menyimpan** kolinear.

**Proses:** titik (0,0), (1,0), (2,0), (1,1), (0,2).

```
sort: (0,0) (0,2) (1,0) (1,1) (2,0)
lower: (0,0)-(1,0)-(2,0)   (1,0) kolinear, pop jika tidak menyimpan
       lalu (0,0)-(2,0)
upper dari kanan: (2,0)-(1,1)-(0,2)  (cek belok)
hull CCW: (0,0) (2,0) (1,1) (0,2)   atau termasuk (1,0)
```

**Kode:**

```cpp
vector<Pt> convexHull(vector<Pt> p, bool keepColinear = false) {
    sort(p.begin(), p.end(), [](Pt a, Pt b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    p.erase(unique(p.begin(), p.end(),
                   [](Pt a, Pt b) { return a.x == b.x && a.y == b.y; }),
            p.end());
    int n = (int)p.size();
    if (n <= 2) return p;

    auto buruk = [&](Pt a, Pt b, Pt c) {
        ll cr = cross(a, b, c);
        if (keepColinear) return cr < 0;    // pop hanya belok kanan
        return cr <= 0;                     // pop kanan dan lurus
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

Diameter himpunan (calipers kasar O(h²), cukup h≤2000):

```cpp
ll diameter2(const vector<Pt>& h) {
    ll best = 0;
    int m = (int)h.size();
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            best = max(best, norm2(h[i] - h[j]));
    return best;                            // kuadrat jarak, bandingkan ini
}
```

**Jebakan:**

- Tidak `unique` titik sama → pop aneh, kadang infinite tidak, tetapi hull jelek.
- `cross<=0` membuang kolinear; soal “semua titik di pagar” butuh `keepColinear`.
- Upper/lower lupa `pop_back` ujung → titik ujung dobel.
- n=1, n=2 harus keluar awal.
- Mengurut polar dari titik min-y lalu Graham: rawan titik min tidak unik.

**Kompleksitas:** O(n log n) karena sort, rantai O(n). Memori O(n).

## Sweep line — peta

**Teori:** garis vertikal bergerak dari kiri ke kanan. Event = titik awal/akhir segmen, atau perpotongan. Status = struktur terurut di garis (set). Bidang 2D menjadi barisan 1D.

Pakai: segmen berpotongan (Bentley-Ottmann), titik terdekat (bagi-tengah + strip), overlapping intervals (itu sweep 1D, file 07).

**Kapan:** n log n dibutuhkan, naif n² TLE. **Tidak** di file ini sebagai kode penuh — Day 242. Ide yang dibawa: sort event, jaga invariant pada garis, hapus yang sudah lewat.

**Kompleksitas khas:** O((n+k) log n) untuk k potongan, atau O(n log n) closest pair.

## Nim klasik

**Teori:** beberapa tumpukan batu. Satu giliran: pilih **satu** tumpukan, buang minimal satu batu (boleh semua). Yang tidak bisa gerak kalah (normal play).

Posisi menang jika ada langkah ke posisi kalah. Posisi kalah jika semua langkah ke posisi menang.

Untuk satu tumpukan ukuran n: n=0 kalah, n≥1 menang (buang semua). Beberapa tumpukan: **XOR** semua ukuran. XOR=0 kalah, ≠0 menang.

Kenapa XOR: tiap tumpukan adalah permainan terpisah. Gabungan normal play memakai nimber (berikut). Nimber tumpukan n adalah n itu sendiri. XOR adalah jumlah di nimber.

**Kapan dipakai / kapan tidak.**

- Pakai: tumpukan independen, aturan “kurangi dari satu tumpukan”.
- Variasi: subtraction game, misère (yang terakhir kalah) — rumus XOR **berubah** jika semua tumpukan ≤1 dan n kecil.
- Jangan: satu papan catur dengan aturan aneh tanpa memecah komponen.

**Proses:** tumpukan 3, 4, 5.

```
3^4^5 = 011 ^ 100 ^ 101 = 010 ≠ 0  → first win
strategi: buat XOR jadi 0. 3^4^5=2, ubah 5 (101) jadi 5^2=7? 
target tumpukan 5 menjadi 5^2 = 7 terlalu besar.
ingin y < 5, y^3^4 = 0 → y = 3^4 = 7, 7>5 mustahil.
tumpukan 4: y^3^5=0 → y=3^5=6 >4.
tumpukan 3: y^4^5=0 → y=4^5=1, 1<3 OK. Buang 2, sisa 1,4,5.
1^4^5=0. Benar.
```

**Kode:**

```cpp
int xorSemua(const vector<int>& a) {
    int x = 0;
    for (int v : a) x ^= v;
    return x;
}

bool nimMenang(const vector<int>& a) { return xorSemua(a) != 0; }

pair<int, int> langkahNim(const vector<int>& a) { // {indeks, sisa}
    int x = xorSemua(a);
    if (x == 0) return {-1, -1};
    for (int i = 0; i < (int)a.size(); i++) {
        int y = a[i] ^ x;                   // ingin a[i] jadi y? salah
        // benar: a[i] jadi a[i]^x hanya jika itu < a[i]
        y = a[i] ^ x;
        if (y < a[i]) return {i, y};
    }
    return {-1, -1};
}
```

Perbaiki komentar: `y = a[i] ^ x` memang rumus standar, dan `y < a[i]` menjamin legal. Contoh: a[i]=3, x=2, y=1 < 3. 1^4^5=0.

**Jebakan:** `a[i] ^= x` tanpa cek `y < a[i]`. Misère Nim: jika ada tumpukan ≥2, strategi hampir sama; jika semua ≤1, kebalikan. Baca soal “yang mengambil terakhir **kalah**”.

**Kompleksitas:** O(n).

## Sprague-Grundy

**Teori:** setiap posisi permainan impartial (aturan sama untuk kedua pemain) punya **Grundy** / nimber:

```
g(pos) = mex { g(pos') | pos' langkah sah dari pos }
mex = angka non-negatif terkecil yang tidak muncul
```

- `g = 0` → kalah jika giliranmu dan lawan sempurna.
- Gabungan **jumlah disjoint** (satu giliran = gerak di **tepat satu** komponen): `g_total = g1 XOR g2 XOR ...`.

Kenapa mex: itu angka terkecil yang tidak bisa dipaksa oleh lawan. Sama seperti “tumpukan Nim seukuran g”.

Analogi: tiap komponen diganti tumpukan batu imajiner. Kamu tidak perlu melihat papan, hanya XOR.

**Kapan dipakai / kapan tidak.**

- Pakai: beberapa permainan kecil independen, subtraction, Kayles, graf-nim, “ambil 1..k dari satu baris”.
- Jangan: partizan (putih/hitam beda langkah) — itu bukan SG.
- Jangan: satu giliran boleh gerak di **dua** komponen sekaligus — XOR rusak.

**Proses:** subtraction {1,3}. `g(0)=mex{}=0`.

```
n=1 → ke 0 (g=0)           mex{0}=1
n=2 → ke 1 (g=1)           mex{1}=0
n=3 → ke 2 atau 0          mex{0,0}=1
n=4 → ke 3 atau 1          mex{1,1}=0
pola: g = n%2  ?  tidak: 0,1,0,1,0 ... ya untuk {1,3} di awal
n=5 → ke 4,2  g=0,0        mex=1
```

Dua tumpukan n=4 dan n=1: 0 XOR 1 = 1 ≠ 0, first win. Gerak di tumpukan 1 ke 0.

**Kode:**

```cpp
int mex(vector<int> s) {
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    int m = 0;
    for (int x : s) {
        if (x == m) m++;
        else if (x > m) break;
    }
    return m;
}

vector<int> grundySub(int n, const vector<int>& steps) {
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> nxt;
        for (int s : steps)
            if (i >= s) nxt.push_back(g[i - s]);
        g[i] = mex(nxt);
    }
    return g;
}

// permainan: beberapa tumpukan, langkah = kurangi step
bool menangSub(const vector<int>& tumpukan, const vector<int>& steps) {
    int mx = 0;
    for (int x : tumpukan) mx = max(mx, x);
    auto g = grundySub(mx, steps);
    int x = 0;
    for (int t : tumpukan) x ^= g[t];
    return x != 0;
}
```

Game di graf (contoh: Nimbers pada DAG, “ambil objek di simpul + hapus outgoing”): DP `g[v] = mex { g[u] }` sesuai aturan. Ingat **state harus DAG** atau di-memo dengan hati-hati (tidak ada siklus gerak).

**Jebakan:**

- mex dihitung dari set kosong = 0, bukan −1.
- Meng-XOR ukuran tumpukan padahal aturan bukan Nim klasik.
- Komponen tidak independen (satu gerak mengubah dua tumpukan) — pecah ulang state.
- Overflow vektor `nxt` tanpa unique: mex tetap benar jika diurut, tetapi lambat jika kamu naif O(n) salah tulis.

**Kompleksitas:** subtraction O(n · |steps| + n log n) jika mex sort; mex array boolean O(n · |steps|).

## Game DP singkat

**Teori:** kadang papan tunggal, state kecil. `win[s] = ada langkah ke !win[s']`. Itu Grundy yang dikompres jadi 1 bit (hanya peduli 0 vs bukan). Cukup jika **satu** komponen.

**Kode:**

```cpp
// contoh: n batu, ambil 1 atau 2, yang tidak bisa kalah
vector<char> menangBatu(int n) {
    vector<char> w(n + 1, 0);
    for (int i = 1; i <= n; i++)
        w[i] = (i >= 1 && !w[i - 1]) || (i >= 2 && !w[i - 2]);
    return w;                               // w[n] first-win?
}
```

`w[0]=0`, `w[1]=1`, `w[2]=1`, `w[3]=0` (karena ke 2 dan 1, keduanya menang untuk lawan).

**Jebakan:** mengisi bottom-up tanpa urutan “semua s' lebih kecil”. State harus menuju basis.

**Kompleksitas:** O(jumlah state × cabang).

## Stress test

**Teori:** dua program. **Cepat** = solusimu. **Lambat** = naif yang jelas benar (O(n²), brute). Generator membuat input acak. Jika output beda, kamu punya tes gagal. Perkecualikan: soal interaktif, output banyak yang sah (konstruktif) — bandingkan **properti**, bukan string persis.

Tiga file:

1. `gen.cpp` — cetak tes.
2. `brute.cpp` — naif.
3. `fast.cpp` — solusi.
4. skrip: loop generate → jalankan keduanya → diff.

Analogi: kunci jawaban ujian dibuat teman yang menghitung manual 10 soal kecil. Kalau kalian beda, salah satu (biasanya kamu) salah.

**Kapan dipakai / kapan tidak.**

- Pakai: WA tidak ketemu, off-by-one, struktur data, hash, geometri integer.
- Jangan: membandingkan konstruktif “sembarang array sah” tanpa checker.
- Jangan: generator yang **tidak** pernah membuat kasus tepi (n=1, semua sama, sudah terurut).

**Proses:** soal jumlah `[l,r]` dengan update. Brute array biasa. Fast BIT. 1000 tes n≤30, jika beda cetak tes.

**Kode:**

```cpp
// gen.cpp
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int seed = argc > 1 ? atoi(argv[1]) : 1;
    mt19937 rng(seed);
    int n = rng() % 8 + 1;
    int q = rng() % 10 + 1;
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; i++) cout << int(rng() % 7) << " \n"[i + 1 == n];
    for (int i = 0; i < q; i++) {
        int t = rng() % 2 + 1;
        if (t == 1) {
            int idx = rng() % n + 1;
            int d = int(rng() % 5) - 2;
            cout << 1 << ' ' << idx << ' ' << d << '\n';
        } else {
            int l = rng() % n + 1, r = rng() % n + 1;
            if (l > r) swap(l, r);
            cout << 2 << ' ' << l << ' ' << r << '\n';
        }
    }
}

// brute.cpp — array biasa
// fast.cpp — BIT
```

Skrip zsh:

```bash
#!/bin/zsh
g++ -std=c++17 -O2 -o fast fast.cpp
g++ -std=c++17 -O2 -o brute brute.cpp
g++ -std=c++17 -O2 -o gen gen.cpp
for i in {1..2000}; do
  ./gen $i > in.txt
  ./fast < in.txt > outf.txt
  ./brute < in.txt > outb.txt
  if ! cmp -s outf.txt outb.txt; then
    echo "BEDA seed=$i"
    cat in.txt
    echo "fast:"; cat outf.txt
    echo "brute:"; cat outb.txt
    exit 1
  fi
done
echo "lulus 2000 tes"
```

Generator di dalam satu file (praktis):

```cpp
void stressBit() {
    mt19937 rng(123);
    for (int tc = 0; tc < 1000; tc++) {
        int n = rng() % 20 + 1;
        vector<ll> a(n);
        for (ll& x : a) x = int(rng() % 11) - 5;
        BIT bit;
        bit.build(a);
        for (int k = 0; k < 50; k++) {
            if (rng() & 1) {
                int i = rng() % n;
                ll d = int(rng() % 7) - 3;
                a[i] += d;
                bit.update(i + 1, d);
            } else {
                int l = rng() % n, r = rng() % n;
                if (l > r) swap(l, r);
                ll naif = 0;
                for (int i = l; i <= r; i++) naif += a[i];
                if (bit.range(l + 1, r + 1) != naif) {
                    cerr << "WA tc=" << tc << '\n';
                    exit(1);
                }
            }
        }
    }
}
```

**Jebakan:**

- Fast dan brute beda format (`Yes` vs `YES`) → diff palsu. Samakan printer.
- `endl` vs spasi akhir: `cmp` ketat. Cetak sama persis, atau token-compare.
- Generator `n` selalu genap — bug ganjil lolos.
- Seed tetap 1 setiap kali: kamu menguji satu tes. Pakai `i` sebagai seed.
- Soalnya banyak jawaban sah: tulis `bool sah(input, output)`.

**Kompleksitas:** brute menentukan seberapa besar n. n≤20, 2000 tes, O(n²) nyaman.

## Memperkecil kasus

**Teori:** tes gagal n=40 sulit dibaca. **Delta debugging:** hapus satu elemen / satu query, jalankan lagi. Jika masih beda, tetap hapus. Sampai minimal.

Juga: turunkan nilai, urutkan ulang (kadang bug urutan), ganti ke 0/1.

**Kapan:** setelah stress ketemu tes. Jangan skip — tes 8 baris lebih mudah dari 80.

**Proses:** array 9 elemen, hapus dari belakang. Jika brute=fast lagi, kembalikan, coba indeks lain.

**Kode ide:**

```cpp
// punyamu: bool beda(vector<int> a)
// perkecil:
bool bisa(const vector<int>& a) { /* jalankan fast vs brute */ return true; }

vector<int> perkecil(vector<int> a) {
    bool berubah = true;
    while (berubah) {
        berubah = false;
        for (int i = 0; i < (int)a.size(); i++) {
            vector<int> b = a;
            b.erase(b.begin() + i);
            if (b.empty()) continue;
            if (bisa(b)) {                  // masih WA
                a.swap(b);
                berubah = true;
                break;
            }
        }
    }
    return a;
}
```

**Jebakan:** “bisa” terbalik (kamu menyimpan tes yang **lulus**). Setelah perkecil, cetak tes dan kerjakan tangan.

**Kompleksitas:** O(n²) percobaan kali biaya satu run.

## Random di kontes

**Teori:** keacakan dipakai untuk (1) menghindari pola jahat lawan, (2) algoritma Monte Carlo yang peluang salah 2⁻⁶⁰, (3) shuffle urutan agar kompleksitas rata-rata.

`mt19937` / `mt19937_64` + `chrono` seed. Jangan `rand() % n` (bias) tanpa `uniform_int_distribution`.

Peluang gagal: jika tiap tes peluang salah p=10⁻⁹, 100 tes masih aman. Jika p=10⁻⁶ dan 10⁵ tes, mulai rawan.

**Kapan dipakai / kapan tidak.**

- Pakai: hash basis, urutan Kruskal acak tidak — Kruskal deterministik. Shuffle Quick-select, random binary search pada fungsi berisik, Miller-Rabin.
- Jangan: seed tetap 1 di CF jika lawan bisa mereproduksi **dan** merugikanmu (hash). Seed dari waktu + input.
- Jangan: `random_shuffle` usang; pakai `shuffle(v.begin(), v.end(), rng)`.

**Proses:** peluang 2 hash 10⁹+7 dan 10⁹+9 tabrakan ≈ 10⁻¹⁸ per banding. 10⁵ banding masih ~10⁻¹³.

**Kode:**

```cpp
mt19937_64 rng(
    chrono::steady_clock::now().time_since_epoch().count());

ll randInt(ll l, ll r) {                    // inklusif
    uniform_int_distribution<ll> dist(l, r);
    return dist(rng);
}

void acakUrutan(vector<int>& a) { shuffle(a.begin(), a.end(), rng); }
```

**Jebakan:** seed 0 di semua tes. `rng() % (r-l+1)` overflow jika selang besar. Dua `mt19937` tanpa seed beda tetap sama di awal jika default.

**Kompleksitas:** generate O(1) amortized.

## Anti-hash

**Teori:** single hash `mod = 1e9+7`, `P=31` **dikenal**. Pembuat soal atau hacker CF menyusun string yang tabrakan. Solusi: (1) dua modulus, (2) modulus/`P` **acak** di runtime, (3) tambah hash 2⁶⁴, (4) verifikasi string jika hash sama dan niz.

Di Codeforces, anti-hash pada 10⁹+7 klasik sudah cerita rakyat. Jangan kalah di sana setelah algoritma benar.

**Kapan dipakai / kapan tidak.**

- Pakai selalu di CF Div. 1 / hackable: random P dan M, atau double.
- AtCoder/CSES jarang hack; double tetap rapi.
- Jangan: `M=2^64` saja di CF — ada generator Thue–Morse.

**Proses:** pilih `P` ganjil acak di [256, 1e9], `M` prima acak. Atau pakai dua prima tetap yang **bukan** pasangan paling klise, plus overflow 64.

Cari prima:

```cpp
bool primaCek(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n && i <= 1000000; i++)
        if (n % i == 0) return false;
    return true;                            // cukup untuk n ~ 1e9+ acak kecil
}

ll primaAcak() {
    while (true) {
        ll x = randInt(1000000000LL, 2000000000LL);
        if (x % 2 == 0) x++;
        if (primaCek(x)) return x;
    }
}
```

Untuk kontes, lebih aman daftar prima:

```cpp
const ll CAND[] = {1000000007, 1000000009, 998244353,
                   1000000033, 1000000087, 1000000093};

pair<ll, ll> pilihMod() {
    shuffle(begin(CAND), end(CAND), rng);
    ll P = randInt(256, 1000000) * 2 + 1;
    return {P, CAND[0]};
}
```

Hasher acak:

```cpp
Hasher buatHasherAman(const string& s) {
    auto [P, M] = pilihMod();
    return Hasher(s, P, M);
}
```

Double + 64 bit di soal “substring sama”:

```
bool sama = h1.sama(...) && h2.sama(...)    // dua M
// atau h64.sama && h1.sama
```

Peluang: lawan harus menabrakkan **semua** modulus sekaligus tanpa tahu P. Jauh lebih mahal.

**Jebakan:**

- Mengacak P tetapi `P < 128` pada ASCII. Tabrakan sistematis `"a"` vs karakter 0.
- Mencetak P dan M ke stderr di CF — tidak apa, tetapi jangan ke stdout.
- Dua hasher dengan P,M sama “karena lupa seed”.
- Verifikasi O(n) setiap match di n² match → TLE. Verifikasi hanya jika single hash dan jumlah match kecil.

**Kompleksitas:** sama dengan hash biasa. Inisialisasi prima acak O(√M) sekali jika uji naif; daftar tetap O(1).

## Checklist sebelum submit

Bukan algoritma, tetapi menghemat penalty.

1. **Baca ulang output.** `Yes/No` vs `YES/NO`, 0/1-index, spasi.
2. **Overflow.** Kali dua `int` 2e9, `n(n+1)` , faktorial. `ll`.
3. **n=1, array kosong, semua sama, sudah terurut, negatif.**
4. **Graf:** 1-based input, sisi bolak-balik, komponen >1, n=1 tanpa sisi.
5. **Interaktif:** `flush` (`cout << flush` atau `endl`), jangan `FASTIO` tanpa sadar buffer.
6. **Hash:** double atau P acak di CF.
7. **Geometri:** overflow cross, kolinear, titik duplikat.
8. **Game:** normal vs misère, XOR vs “selalu first”.
9. **Jika WA di tes 1:** contoh soal. Jika WA tes 2+: stress.
10. **Jika TLE:** constraint vs kompleksitas (file 00), `endl`, `map` vs array, `bitset` vs `vector<bool>` bukan isu utama.

Resep 15 menit terakhir:

```
tulis brute + gen  (5 menit)
200 tes lokal      (2 menit)
perbaiki           (sisa)
baru submit ulang
```

Lebih murah daripada 4 WA × 20 menit.

## Ringkasan

1. Cross = luas bertanda = belok. Hafalkan `ax*by − ay*bx`.
2. Orientasi + on-segment = potong segmen termasuk ujung.
3. Hull = sort + rantai monoton, jaga belokan kiri.
4. Nim = XOR ukuran. SG = mex langkah, gabungan = XOR.
5. Stress = cepat vs naif vs generator. Perkecil tes sebelum mikir 20 menit.
6. Random = `mt19937_64` + distribusi. Anti-hash = dua modulus atau P/M acak, jangan 10⁹+7 tunggal di CF.

Latihan: CSES *Convex Hull*, *Polygon Area*, *Nim Game I*, lalu buat stress untuk BIT milikmu (file 16) hari ini juga. Day 236, 240, 250, 252 di `ComProgLearning/CP` adalah paket “siap kontes” yang tidak harus menunggu semua algoritma lain selesai.
