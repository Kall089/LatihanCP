# Sweep line

[← Cross & hull](cross-hull.md) · [Geometri](README.md) · [Teori permainan →](../14-game-theory/README.md)

Day 242. Garis (biasanya vertikal) bergerak. Bidang 2D jadi barisan event 1D. Status di garis disimpan terurut.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Titik `ll`. Ini **bukan** kode penyerangan atau pelacak; hanya geometri kontes.

## Daftar isi

- [Ide sweep](#ide-sweep)
- [Interval 1D](#interval-1d)
- [Banyak segmen overlap](#banyak-segmen-overlap)
- [Persegi panjang union kasar](#persegi-panjang-union-kasar)
- [Titik terdekat](#titik-terdekat)
- [Closest pair: strip](#closest-pair-strip)
- [Segmen berpotongan — peta](#segmen-berpotongan--peta)
- [Event + set](#event--set)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Ide sweep

**Teori:** urutkan peristiwa (awal/akhir segmen, titik, potongan). Proses kiri ke kanan. Invariant: semua yang “hidup” di garis sekarang ada di struktur status (`set`, Fenwick pada y).

Analogi: sapu lantai. Debu yang sudah dilewati tidak dihitung lagi. Yang di sapu = aktif.

**Kapan:**

- Pakai: n log n dibutuhkan, naif n² TLE. Interval overlap, closest pair, rectangle union, “ada dua segmen silang”.
- Jangan: n ≤ 2000 potong segmen — O(n²) `segmenPotong` lebih pendek (lihat [cross-hull.md](cross-hull.md)).
- Jangan: floating event intersection jika soal hanya ya/tidak dan n kecil.

**Proses:** 3 interval [1,5], [2,3], [4,8]. Event:

```
x=1 buka, aktif=1
x=2 buka, aktif=2  max=2
x=3 tutup, aktif=1
x=4 buka, aktif=2
x=5 tutup, aktif=1
x=8 tutup, aktif=0
```

**Kode:** event.

```cpp
struct Ev {
    ll x;
    int tipe;                               // -1 tutup dulu, +1 buka
    bool operator<(const Ev& o) const {
        if (x != o.x) return x < o.x;
        return tipe < o.tipe;               // tutup sebelum buka di x sama
    }
};
```

Urutan di x sama: jika interval [1,2] dan [2,3] **tidak** dianggap overlap, proses tutup dulu. Jika sentuh dihitung, buka dulu.

**Jebakan:** tie-break x sama. Off-by-one ujung.

**Kompleksitas:** khas O((n+k) log n).

## Interval 1D

**Teori:** ini sweep paling sederhana. File greedy interval juga overlap; di sini kita hitung **berapa** yang hidup, bukan pilih.

**Kapan:** “maksimum rapat”, reservasi kamar, *parking*.

**Proses:** [0,2], [1,3], [2,2] titik. Jika sentuh overlap: di x=2 aktif bisa 3.

**Kode:**

```cpp
int maxOverlap(vector<pair<ll, ll>> seg, bool sentuh = false) {
    vector<Ev> ev;
    for (auto [l, r] : seg) {
        ev.push_back({l, +1});
        ev.push_back({r, -1});
    }
    sort(ev.begin(), ev.end(), [&](Ev a, Ev b) {
        if (a.x != b.x) return a.x < b.x;
        if (sentuh) return a.tipe > b.tipe; // buka dulu
        return a.tipe < b.tipe;
    });
    int cur = 0, best = 0;
    for (auto e : ev) {
        cur += e.tipe;
        best = max(best, cur);
    }
    return best;
}
```

**Jebakan:** `l > r` input. Interval kosong. `int` overflow banyak event — `cur` tetap ≤ n.

**Kompleksitas:** O(n log n).

## Banyak segmen overlap

**Teori:** selain max, kadang jumlah panjang yang tertutup ≥1. Saat `cur` berubah dari 0 ke 1, catat `x`. Saat kembali 0, tambah `x-last`.

**Kapan:** union panjang interval.

**Proses:** [1,5]+[2,3]+[4,8] = [1,8] panjang 7 (jika ujung tertutup ukur x, hati-hati diskrit vs kontinu).

Titik integer inklusif: panjang `[1,5]` = 5. Union [1,5]∪[4,8]=8.

Untuk integer, event tutup di `r+1` (difference array).

**Kode:** kontinu (panjang = selisih x):

```cpp
ll unionPanjang(vector<pair<ll, ll>> seg) {
    vector<Ev> ev;
    for (auto [l, r] : seg) {
        if (l > r) swap(l, r);
        ev.push_back({l, +1});
        ev.push_back({r, -1});
    }
    sort(ev.begin(), ev.end(), [](Ev a, Ev b) {
        if (a.x != b.x) return a.x < b.x;
        return a.tipe > b.tipe;
    });
    int cur = 0;
    ll last = 0, ans = 0;
    for (auto e : ev) {
        if (cur > 0) ans += e.x - last;
        cur += e.tipe;
        last = e.x;
    }
    return ans;
}

ll unionInteger(vector<pair<ll, ll>> seg) {
    vector<pair<ll, int>> ev;
    for (auto [l, r] : seg) {
        ev.push_back({l, +1});
        ev.push_back({r + 1, -1});
    }
    sort(ev.begin(), ev.end());
    int cur = 0;
    ll ans = 0;
    for (int i = 0; i < (int)ev.size();) {
        int j = i;
        while (j < (int)ev.size() && ev[j].first == ev[i].first) {
            cur += ev[j].second;
            j++;
        }
        if (j < (int)ev.size() && cur > 0) ans += ev[j].first - ev[i].first;
        i = j;
    }
    return ans;
}
```

**Jebakan:** campur kontinu dan integer. `[1,1]` integer panjang 1, kontinu 0 jika l=r dan tutup di r.

**Kompleksitas:** O(n log n).

## Persegi panjang union kasar

**Teori:** sweep vertikal pada x. Event kiri = masuk interval y, kanan = keluar. Status: struktur y (lazy SegTree pada y terkompresi) menyimpan “berapa kali tertutup” dan panjang tertutup. Setiap langkah x: `ans += panjangY * dx`.

**Kapan:** n ≤ 1e5 rectangle union. n ≤ 200: O(n²) scanline kasar atau grid.

**Proses:** satu persegi [0,2]×[0,3]. dx=2, panjangY=3, luas 6.

Dua persegi overlap: y ter-cover tidak dobel.

**Kode:** n kecil, y tidak dikompresi — naif aktif list.

```cpp
struct Rect {
    ll x1, y1, x2, y2;
};

ll unionRectNaif(const vector<Rect>& r) {
    vector<ll> xs, ys;
    for (auto a : r) {
        xs.push_back(a.x1);
        xs.push_back(a.x2);
        ys.push_back(a.y1);
        ys.push_back(a.y2);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    ll ans = 0;
    for (int i = 0; i + 1 < (int)xs.size(); i++)
        for (int j = 0; j + 1 < (int)ys.size(); j++) {
            ll mx = (xs[i] + xs[i + 1]) / 2;
            ll my = (ys[j] + ys[j + 1]) / 2;
            if (xs[i] == xs[i + 1] || ys[j] == ys[j + 1]) continue;
            bool ada = false;
            for (auto a : r)
                if (a.x1 <= mx && mx < a.x2 && a.y1 <= my && my < a.y2) {
                    ada = true;
                    break;
                }
            if (ada) ans += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
        }
    return ans;
}
```

Ini O(n² · n) kasar untuk grid 2n. Cukup n ≤ 80. Untuk n besar: SegTree + kompresi y, bukan dihafal 5 menit pertama.

**Jebakan:** batas setengah-terbuka `[x1,x2) × [y1,y2)` vs inklusif. Tes satu sel 1×1.

**Kompleksitas:** naif O(n³), sweep+segtree O(n log n).

## Titik terdekat

**Teori:** closest pair. Divide & conquer: bagi di median x, rekursi kiri/kanan, lalu periksa **strip** lebar d (d = min jawaban dua sisi). Di strip, tiap titik hanya perlu ~7 tetangga terurut y.

Sweep: jaga set titik dalam jendela x berlebar d, terurut y, cek tetangga y.

**Kapan:** n 10^5, naif n² TLE. CSES *Closest Points*.

**Proses:** titik (0,0),(3,0),(1,1).

```
jarak²: 9, 2, (3-1)²+1=5
terdekat (0,0)-(1,1) = 2
```

**Kode:** naif dulu.

```cpp
struct P {
    ll x, y;
};

ll dist2(P a, P b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

ll closestNaif(const vector<P>& a) {
    ll best = (ll)8e18;
    int n = (int)a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) best = min(best, dist2(a[i], a[j]));
    return best;
}
```

**Jebakan:** `ll` overflow dx=2e9: 4e18 aman, 3e9 tidak. n=1 tidak ada pasangan.

**Kompleksitas:** naif O(n²).

## Closest pair: strip

**Teori:** sort x. Fungsi rekursif `[l,r)` pada array sudah sort x. `d = min(kiri, kanan)`. Kumpulkan strip `|x-midX|² < d` (atau `|x-midX|` dibandingkan dengan sqrt — lebih aman kuadrat hati-hati). Sort strip menurut y, scan ke depan selama `dy² < d`.

**Kapan:** implementasi standar D&C.

**Proses:** 4 titik, mid memisah 2-2, d dari sisi, strip memeriksa lintas.

**Kode:**

```cpp
ll closestDC(vector<P> a) {
    sort(a.begin(), a.end(), [](P p, P q) {
        return p.x < q.x || (p.x == q.x && p.y < q.y);
    });
    function<ll(int, int)> rec = [&](int l, int r) -> ll {
        if (r - l <= 3) {
            ll best = (ll)8e18;
            for (int i = l; i < r; i++)
                for (int j = i + 1; j < r; j++) best = min(best, dist2(a[i], a[j]));
            sort(a.begin() + l, a.begin() + r, [](P p, P q) { return p.y < q.y; });
            return best;
        }
        int m = (l + r) / 2;
        ll mx = a[m].x;
        ll d = min(rec(l, m), rec(m, r));
        vector<P> strip;
        for (int i = l; i < r; i++) {
            ll dx = a[i].x - mx;
            if (dx * dx < d) strip.push_back(a[i]);
        }
        // a[l..r) sudah merge y jika kita merge
        vector<P> tmp;
        merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r,
              back_inserter(tmp), [](P p, P q) { return p.y < q.y; });
        copy(tmp.begin(), tmp.end(), a.begin() + l);
        strip.clear();
        for (int i = l; i < r; i++) {
            ll dx = a[i].x - mx;
            if (dx * dx < d) strip.push_back(a[i]);
        }
        for (int i = 0; i < (int)strip.size(); i++)
            for (int j = i + 1; j < (int)strip.size() &&
                 (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; j++)
                d = min(d, dist2(strip[i], strip[j]));
        return d;
    };
    return rec(0, (int)a.size());
}
```

Catatan: merge y setelah rekursi mengasumsikan masing-masing sisi terurut y. Basis `sort` y. Dua `strip` di kode: yang pertama sebelum merge dibuang; yang setelah merge benar.

**Jebakan:** `dx*dx` overflow. Titik sama: dist 0. `d=8e18` awal, `dx*dx < d` selalu untuk dx kecil.

**Kompleksitas:** O(n log n).

## Segmen berpotongan — peta

**Teori:** Bentley–Ottmann: event = ujung + perpotongan. Status = urutan y di sweep. Dua segmen bertetangga di status bisa potong; sisip event potong. O((n+k) log n).

Untuk cheatsheet: jika n ≤ 2000, dobel loop + `segmenPotong`. Jika hanya “ada tidak”, kadang D&C atau sweep + `set` tetangga.

**Kapan:** banyak potongan k. k besar: output k.

**Proses:** dua segmen silang satu event tengah.

**Kode:** naif.

```cpp
int hitungPotongNaif(const vector<pair<Pt, Pt>>& s) {
    int n = (int)s.size(), c = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (segmenPotong(s[i].first, s[i].second, s[j].first, s[j].second))
                c++;
    return c;
}
```

Butuh `Pt` dan `segmenPotong` dari [cross-hull.md](cross-hull.md).

**Jebakan:** ujung bersama dihitung potong — baca soal. Segmen degenerate titik.

**Kompleksitas:** O(n²).

## Event + set

**Teori:** sweep horizontal segments vs vertical, atau “ada silang”. Contoh klasik: hanya horisontal dan vertikal. Event: x kiri H masuk set y, x kanan H keluar, x V cek apakah ada H dengan y di [y1,y2] — Fenwick/set.

**Kapan:** labirin axis-aligned.

**Proses:** H y=1 x=[0,5], V x=2 y=[0,3]. Saat x=2, y=1 di [0,3] → potong.

**Kode:**

```cpp
struct SegHV {
    ll x1, y1, x2, y2;                      // sudah normal l<=r
};

int potongHV(vector<SegHV> s) {
    struct E {
        ll x;
        int tipe;                           // 0 in H, 1 V, 2 out H
        ll y1, y2;
    };
    vector<E> ev;
    for (auto a : s) {
        if (a.y1 == a.y2) {                 // horizontal
            ev.push_back({a.x1, 0, a.y1, a.y1});
            ev.push_back({a.x2, 2, a.y1, a.y1});
        } else {                            // vertical
            ev.push_back({a.x1, 1, min(a.y1, a.y2), max(a.y1, a.y2)});
        }
    }
    sort(ev.begin(), ev.end(), [](E a, E b) {
        if (a.x != b.x) return a.x < b.x;
        return a.tipe < b.tipe;
    });
    multiset<ll> ys;
    int ans = 0;
    for (auto e : ev) {
        if (e.tipe == 0) ys.insert(e.y1);
        else if (e.tipe == 2) ys.erase(ys.find(e.y1));
        else {
            auto it = ys.lower_bound(e.y1);
            while (it != ys.end() && *it <= e.y2) {
                ans++;
                ++it;
            }
        }
    }
    return ans;
}
```

Tie: di x yang sama, masuk H dulu (`tipe 0`) sebelum V (`1`) jika sentuhan di ujung dihitung; keluar H setelah V jika tidak.

**Jebakan:** `ys.erase(y)` hapus semua sama. Pakai `find`. Vertikal di ujung H.

**Kompleksitas:** O(n log n + laporan).

## Uji naif

**Teori:** overlap vs loop pasangan. Closest DC vs naif. HV vs `segmenPotong`.

**Kapan:** n ≤ 40.

**Proses:** interval di atas max overlap 2. Titik (0,0),(1,1),(3,0) closest 2.

**Kode:**

```cpp
int main() {
    FASTIO;
    vector<pair<ll, ll>> seg = {{1, 5}, {2, 3}, {4, 8}};
    cout << maxOverlap(seg, false) << '\n';
    cout << unionInteger(seg) << '\n';      // 8
    vector<P> pts = {{0, 0}, {3, 0}, {1, 1}};
    cout << closestNaif(pts) << ' ' << closestDC(pts) << '\n';
}
```

Stress closest:

```cpp
bool cekClose(int n, int seed) {
    mt19937 rng(seed);
    vector<P> a(n);
    for (auto& p : a) {
        p.x = int(rng() % 21) - 10;
        p.y = int(rng() % 21) - 10;
    }
    return closestNaif(a) == closestDC(a);
}
```

**Jebakan:** titik duplikat. n=2.

**Kompleksitas:** tes O(n²).

## Ringkasan

1. Sweep = sort event + status di garis.
2. Tie-break x sama menentukan sentuhan.
3. Interval: max overlap dan union panjang.
4. Closest pair: D&C + strip, banding `dist2`.
5. Segmen umum n besar: Bentley–Ottmann; n kecil: O(n²).
6. HV: set y + event x.

Latihan Day 242. Jangan salin latihan ComprogLearning.
