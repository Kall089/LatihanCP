# Lazy propagation

[← Segment Tree](segment-tree.md) · [Struktur data](README.md) · [Persisten, sqrt, Mo →](persistent-sqrt-mo.md)

Day 176. Update **seluruh rentang** dalam O(log n): tandai simpul, jangan turun ke daun sampai perlu.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Prasyarat: [segment-tree.md](segment-tree.md) sudah AC untuk point update.

## Daftar isi

- [Ide tunda](#ide-tunda)
- [Apply dan push](#apply-dan-push)
- [Range add + jumlah](#range-add--jumlah)
- [Simulasi add](#simulasi-add)
- [Range assign](#range-assign)
- [Add plus assign](#add-plus-assign)
- [Range add + min](#range-add--min)
- [Kapan tidak memakai lazy](#kapan-tidak-memakai-lazy)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Ide tunda

**Teori:** update satu juta indeks satu-satu = O(n log n) per perintah. Jika sebuah simpul **seluruhnya** masuk rentang update, terapkan angka ke ringkasan simpul itu, tempel tanda **lazy** “anak belum tahu”, selesai.

Tanda didorong ke anak hanya ketika query/update berikutnya **butuh** anak (`push`).

Kenapa setara menulis ke semua daun: simpul menyimpan nilai **sudah termasuk** update tertunda di dirinya. Anak belum. `push` menyalin angka yang sama ke dua anak, lalu mengosongkan lazy ayah. Urutan “tulis di ayah, turunkan saat perlu” komutatif untuk add seragam.

Analogi: pengumuman. Kepala sekolah menempel “lantai 2 +10 poin” di pintu gedung. Tidak menemui tiap siswa. Saat kamu membuka kelas, kertas disalin ke papan kelas.

Dua jenis paling sering:

1. **Range add:** `a[i] += v` pada `[L, R]`.
2. **Range assign:** `a[i] = v` pada `[L, R]`. Assign menimpa add yang belum didorong.

**Kapan:**

- Pakai: update rentang + query rentang, n,q ≤ 2·10^5.
- Jangan: hanya point update — lazy menambah bug tanpa manfaat.
- Jangan: update tidak seragam (“tambah i pada posisi i”) tanpa rumus tertutup.
- Jangan: operasi yang tidak bisa diringkas di simpul (modus tanpa struktur tambahan).

**Proses:** a = `[1, 2, 3, 4]`. Add +5 pada `[0, 3]` sekaligus.

```
apply akar: t[1] += 5*4 = 20, lz[1] = 5
daun belum disentuh
query [0,0] baru push ke bawah
```

**Kode:** tanda hidup di `lz[v]`. Nol berarti “tidak ada add tertunda” untuk varian add-only.

```cpp
bool adaLazyAdd(ll lz) { return lz != 0; }
```

**Jebakan:** mengira lazy menggantikan `t[v]`. `t[v]` sudah **termasuk** lazy sendiri. `push` hanya untuk anak.

**Kompleksitas:** tetap O(log n) per update/query, memori O(n).

## Apply dan push

**Teori:** pecah dua tugas.

- `apply(v, l, r, add)`: ubah ringkasan `t[v]` **dan** tambah `lz[v]`.
- `push(v, l, r)`: jika ada lazy dan v bukan daun, `apply` ke kedua anak, lalu `lz[v]=0`.

Untuk jumlah: `t[v] += add * (r-l+1)`. Lazy menyimpan `add` per elemen, **bukan** `add * panjang`. Jangan dobel.

**Kapan:** setiap varian lazy. Assign punya `apply` berbeda (lihat bawah).

**Proses:** simpul `[0, 3]` panjang 4, add +5.

```
t lama 10 → 10 + 5*4 = 30
lz 0 → 5
push: anak kiri [0,1] apply +5 → t += 10, lz += 5
      anak kanan [2,3] sama
      lz ayah = 0
```

**Kode:**

```cpp
void applyAdd(vector<ll>& t, vector<ll>& lz, int v, int l, int r, ll add) {
    t[v] += add * (r - l + 1);
    lz[v] += add;
}

void pushAdd(vector<ll>& t, vector<ll>& lz, int v, int l, int r) {
    if (lz[v] == 0 || l == r) return;
    int m = (l + r) / 2;
    applyAdd(t, lz, 2 * v, l, m, lz[v]);
    applyAdd(t, lz, 2 * v + 1, m + 1, r, lz[v]);
    lz[v] = 0;
}
```

**Jebakan:** `apply` menambah `v * panjang` ke `t` lalu menyimpan `v * panjang` di `lz` — anak akan dikali panjang lagi. `push` pada daun tidak perlu, dan `l==r` wajib keluar.

**Kompleksitas:** O(1) per apply/push, dipanggil O(log n) kali per operasi.

## Range add + jumlah

**Teori:** `struct LazyAdd` dengan `build`, `update` (range add), `query` (range sum). Sebelum turun ke anak, `push`. Jika simpul penuh di dalam `[ql,qr]`, `apply` dan **jangan** turun.

**Kapan:** pola paling sering. Dua BIT juga bisa (lihat [fenwick.md](fenwick.md)); lazy lebih mudah diganti jadi min.

**Proses:** a = `[1, 2, 3, 4]`. Update +5 pada `[1, 2]`.

```
akar [0..3] tidak penuh → pecah
kiri [0..1] tidak penuh → pecah
  daun [1]: apply +5, t=7
kanan [2..3] tidak penuh → pecah
  daun [2]: apply +5, t=8
naik: kiri 1+7=8, kanan 8+4=12, akar 20
array efektif [1,7,8,4]
```

Jika n besar dan `[0,3]` di-update: satu `apply` di akar.

**Kode:**

```cpp
struct LazyAdd {
    int n;
    vector<ll> t, lz;

    explicit LazyAdd(int n_) : n(n_), t(4 * n_ + 4, 0), lz(4 * n_ + 4, 0) {}

    void apply(int v, int l, int r, ll add) {
        t[v] += add * (r - l + 1);
        lz[v] += add;
    }

    void push(int v, int l, int r) {
        if (lz[v] == 0 || l == r) return;
        int m = (l + r) / 2;
        apply(2 * v, l, m, lz[v]);
        apply(2 * v + 1, m + 1, r, lz[v]);
        lz[v] = 0;
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int v, int l, int r, int ql, int qr, ll add) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, l, r, add);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, add);
        update(2 * v + 1, m + 1, r, ql, qr, add);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};

struct LazySum {
    LazyAdd st;
    int n;
    explicit LazySum(const vector<ll>& a) : st((int)a.size()), n((int)a.size()) {
        if (n) st.build(1, 0, n - 1, a);
    }
    void addRange(int l, int r, ll x) { st.update(1, 0, n - 1, l, r, x); }
    ll range(int l, int r) { return st.query(1, 0, n - 1, l, r); }
};
```

**Jebakan:**

- Lupa `push` sebelum turun — anak memakai nilai basi.
- Setelah `apply` pada simpul penuh, tetap `push` lalu menimpa anak secara tidak konsisten.
- Recursion `update` yang sudah `apply` **tidak** boleh turun.
- `t[v] = kiri+kanan` setelah update parsial tanpa `push` dulu — ayah mencampur anak basi.

**Kompleksitas:** O(log n), memori O(n) dua vektor.

## Simulasi add

**Teori:** jejak lazy yang **tidak** turun, lalu query kecil memaksa `push`.

**Kapan:** memahami kenapa query `[0,0]` setelah update penuh tetap benar.

**Proses:** a = `[1, 2, 3, 4]`, `addRange(0, 3, +5)`, lalu `range(0, 0)`.

```
setelah add penuh:
  t[1] = 10+20 = 30, lz[1] = 5
  daun masih 1,2,3,4

query [0,0]:
  v=1 tidak penuh → push
    apply v=2 [0,1]: t=3+10=13, lz=5
    apply v=3 [2,3]: t=7+10=17, lz=5
    lz[1]=0
  turun kiri v=2 [0,1] vs [0,0]
    tidak penuh → push
      apply v=4 [0]: t=1+5=6, lz=5 (daun)
      apply v=5 [1]: t=2+5=7, lz=5
      lz[2]=0
    v=4 penuh → 6
    v=5 di luar → 0
  kanan v=3 vs [0,0] di luar → 0
jawaban 6
```

Array efektif `[6,7,8,9]`. Benar.

**Kode:** `main` jejak.

```cpp
int main() {
    FASTIO;
    vector<ll> a = {1, 2, 3, 4};
    LazySum seg(a);
    seg.addRange(0, 3, 5);
    cout << seg.range(0, 0) << '\n';        // 6
    cout << seg.range(1, 2) << '\n';        // 15
}
```

**Jebakan:** mencetak `t[daun]` tanpa query — daun bisa basi. Baca lewat `query`.

**Kompleksitas:** O(log n).

## Range assign

**Teori:** `a[i] = x` pada seluruh `[L,R]`. Ringkasan jumlah jadi `x * panjang`. Lazy assign **menimpa** nilai lama, bukan menambah.

Butuh tanda “apakah ada assign tertunda”. Nol bukan sentinel jika x boleh 0. Pakai `bool dirty` atau `ll` plus flag.

**Kapan:** “set semua di `[l,r]` jadi x”, pewarnaan segmen.

**Proses:** a = `[1, 2, 3, 4]`, assign 9 pada `[1, 2]`.

```
array [1, 9, 9, 4]
jumlah [0,3] = 23
```

Jika lalu assign 0 pada `[0, 3]`: seluruhnya 0. Lazy akar menimpa tanda anak yang belum sempat di-push — `push` assign harus menimpa lazy anak.

**Kode:**

```cpp
struct LazySet {
    int n;
    vector<ll> t, lz;
    vector<char> on;                        // ada assign tertunda

    explicit LazySet(int n_) : n(n_), t(4 * n_ + 4, 0), lz(4 * n_ + 4, 0),
                               on(4 * n_ + 4, 0) {}

    void apply(int v, int l, int r, ll x) {
        t[v] = x * (r - l + 1);
        lz[v] = x;
        on[v] = 1;
    }

    void push(int v, int l, int r) {
        if (!on[v] || l == r) return;
        int m = (l + r) / 2;
        apply(2 * v, l, m, lz[v]);
        apply(2 * v + 1, m + 1, r, lz[v]);
        on[v] = 0;
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        on[v] = 0;
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int v, int l, int r, int ql, int qr, ll x) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, x);
        update(2 * v + 1, m + 1, r, ql, qr, x);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) + query(2 * v + 1, m + 1, r, ql, qr);
    }
};
```

**Jebakan:** memakai `lz==0` sebagai “tidak ada assign” padahal assign 0 legal. `apply` assign harus menimpa `on` anak saat `push`, bukan menambah.

**Kompleksitas:** O(log n).

## Add plus assign

**Teori:** dua jenis lazy di satu pohon. Prioritas: assign baru membuang add lama. Add baru menumpuk di atas assign yang sudah diterapkan ke `t`/`lz` assign.

Implementasi aman untuk kontes pertama: **jangan campur** jika soal hanya salah satu. Jika wajib keduanya, simpan pasangan `(tipe, nilai)` atau dua flag dengan aturan:

```
push: jika ada assign, apply assign ke anak (bersihkan add anak)
      lalu jika ada add, apply add ke anak
```

**Kapan:** soal “1 l r x = add, 2 l r x = set, 3 l r = sum”.

**Proses:** set `[0,3]=7` lalu add `[0,3]+1` → semua 8. Kebalikan: add +1 dulu lalu set 7 → semua 7. Urutan penting.

**Kode:** kerangka prioritas (bukan template terpendek):

```cpp
struct LazyMix {
    ll sum = 0, add = 0, setv = 0;
    char hasSet = 0;
};

void applySet(LazyMix& u, int len, ll x) {
    u.sum = x * len;
    u.setv = x;
    u.hasSet = 1;
    u.add = 0;
}

void applyAdd(LazyMix& u, int len, ll x) {
    u.sum += x * len;
    if (u.hasSet) u.setv += x;
    else u.add += x;
}
```

`push` menurunkan `hasSet` dulu, lalu `add`.

**Jebakan:** add ke `setv` lupa, atau set tidak mengosongkan `add`. Uji urutan set-then-add dan add-then-set.

**Kompleksitas:** O(log n), konstanta dua kali.

## Range add + min

**Teori:** min + add seragam: semua elemen +v, minimum juga +v. `apply` pada min: `t[v]+=add`, `lz[v]+=add`. **Tidak** kali panjang.

**Kapan:** “tambah `[l,r]`, berapa min `[L,R]`”.

**Proses:** a = `[5, 1, 4]`. Add +3 pada `[1, 2]` → `[5, 4, 7]`. Min `[0, 2]` = 4.

**Kode:**

```cpp
struct LazyMin {
    int n;
    vector<ll> t, lz;

    explicit LazyMin(int n_) : n(n_), t(4 * n_ + 4, 0), lz(4 * n_ + 4, 0) {}

    void apply(int v, ll add) {
        t[v] += add;
        lz[v] += add;
    }

    void push(int v, int l, int r) {
        if (lz[v] == 0 || l == r) return;
        apply(2 * v, lz[v]);
        apply(2 * v + 1, lz[v]);
        lz[v] = 0;
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    void update(int v, int l, int r, int ql, int qr, ll add) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, add);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        update(2 * v, l, m, ql, qr, add);
        update(2 * v + 1, m + 1, r, ql, qr, add);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return (ll)4e18;
        if (ql <= l && r <= qr) return t[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return min(query(2 * v, l, m, ql, qr),
                   query(2 * v + 1, m + 1, r, ql, qr));
    }
};
```

**Jebakan:** menyalin `apply` jumlah (`* panjang`) ke pohon min. Identitas query `0` bukan +∞.

**Kompleksitas:** O(log n).

## Kapan tidak memakai lazy

**Teori:** lazy adalah alat, bukan default. Point update: [segment-tree.md](segment-tree.md) polos. Range add + point query: difference + [Fenwick](fenwick.md). Range add + range sum saja: dua BIT.

**Kapan:** pilih yang paling sedikit state. Setiap flag lazy adalah cabang WA.

**Proses:** soal hanya `a[i]+=x` dan jumlah `[l,r]`. Tidak ada range update. Tulis Fenwick, bukan lazy.

**Kode:** tidak perlu `lz`.

**Jebakan:** template lazy 120 baris untuk point update. Lebih lama debug.

**Kompleksitas:** lazy tidak memperburuk big-O, memperburuk peluang bug.

## Uji naif

**Teori:** array biasa `+=` pada rentang, bandingkan jumlah. Generator harus memuat update penuh, update 1 elemen, query 1 elemen, n=1.

**Kapan:** wajib. Bug `push` jarang kelihatan di contoh soal.

**Proses:** n=8, 60 operasi acak.

**Kode:**

```cpp
ll jumlahNaif(const vector<ll>& a, int l, int r) {
    ll s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

bool cekLazy(int n, int q, int seed) {
    mt19937 rng(seed);
    vector<ll> a(n);
    for (ll& x : a) x = int(rng() % 7) - 3;
    LazySum seg(a);
    for (int i = 0; i < q; i++) {
        int l = rng() % n, r = rng() % n;
        if (l > r) swap(l, r);
        if (rng() & 1) {
            ll x = int(rng() % 7) - 3;
            for (int j = l; j <= r; j++) a[j] += x;
            seg.addRange(l, r, x);
        } else if (seg.range(l, r) != jumlahNaif(a, l, r)) return false;
    }
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 300; s++)
        if (!cekLazy(1, 20, s) || !cekLazy(12, 80, s)) {
            cout << "WA seed=" << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

**Jebakan:** generator yang tidak pernah update rentang penuh — bug `apply` akar lolos.

**Kompleksitas:** tes O(q n).

## Ringkasan

1. Lazy = tunda pekerjaan ke anak. `apply` mengubah `t` + menandai, `push` menurunkan.
2. Jumlah: `t += v * panjang`, lazy hanya `v`.
3. Min: `t += v`, tanpa kali panjang.
4. Assign butuh flag; nol boleh jadi nilai.
5. Campur add+assign: prioritas jelas, atau hindari.
6. Point update saja: jangan lazy.

Latihan Day 176. Jangan salin `exercise_*.cpp`.
