# Persisten, sqrt, Mo

[← Lazy](lazy.md) · [Struktur data](README.md) · [Treap & PBS →](treap-pbs.md)

Day 179–183. Tiga alat yang **bukan** Segment Tree biasa: menyimpan versi lama, memotong blok √n, dan mengurutkan query offline.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [Peta tiga alat](#peta-tiga-alat)
- [Segment Tree persisten](#segment-tree-persisten)
- [K-th pada prefix](#k-th-pada-prefix)
- [Sqrt decomposition](#sqrt-decomposition)
- [Sqrt: update dan blok](#sqrt-update-dan-blok)
- [Algoritma Mo](#algoritma-mo)
- [Add/remove unik](#addremove-unik)
- [Mo dengan update? Peta](#mo-dengan-update-peta)
- [Pilih alat](#pilih-alat)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Peta tiga alat

**Teori:** ketiganya menjawab query rentang yang “sulit digabung” atau “butuh sejarah”.

| Alat | Online? | Update array | Yang diingat |
|---|---|---|---|
| Persisten | ya, versi | tiap update = versi baru | akar per versi |
| Sqrt | ya | titik / rebuild blok | ringkasan blok |
| Mo | **offline** | tidak (versi dasar) | jendela `[cl,cr]` |

**Kapan:**

- Persisten: “kembalikan ke versi t”, k-th pada prefix, jumlah pada versi lama.
- Sqrt: operasi aneh per blok (mode, banyak distinct kasar, rebuild murah).
- Mo: banyak query `[l,r]` diketahui di muka, add/remove O(1).
- Jangan Mo jika query online (jawaban i dipakai untuk query i+1).
- Jangan persisten 200 baris di 20 menit pertama jika Fenwick cukup.

**Proses:** soal “berapa nilai unik di `[l,r]`”, 10^5 query, array mati. Segment Tree biasa tidak punya `gabung` unik yang murah. Mo + `cnt[]` pas.

**Kode:** tidak ada satu struct untuk ketiga alat.

**Jebakan:** memakai Mo untuk n=5·10^5, q=5·10^5, add O(log n) — total ~ n√n log n ketat. Ukur dulu.

**Kompleksitas:** lihat tiap bagian.

## Segment Tree persisten

**Teori:** update tidak menimpa simpul lama. Tiap update membuat **O(log n) simpul baru** di jalur akar–daun. Simpul di luar jalur dipakai bersama (pointer anak yang tidak berubah).

Versi = indeks akar. `root[0]` array awal. `root[k]` setelah k update. Query versi k memanggil `query(root[k], ...)`.

Analogi: dokumen dengan riwayat. Halaman yang tidak diubah tidak disalin. Hanya jalur ke halaman baru.

**Kapan:** k-th pada `[1..i]` setelah insert berurutan, “jumlah `[l,r]` pada versi t”, rollback implisit tanpa stack.

**Proses:** n = 4, a = `[2, 1, 4, 3]`. Update versi 1: `a[1] = 8`.

```
versi 0: akar A0, daun [2,1,4,3]
versi 1: akar A1
  jalur baru: A1 → kiri baru → daun 8
  anak kanan A1 = anak kanan A0 (sama, sum 7)
query jumlah [1,2] versi 0 = 5
query jumlah [1,2] versi 1 = 12
versi 0 tetap 5
```

**Kode:**

```cpp
struct Persist {
    struct Node {
        ll sum;
        int L, R;
        Node() : sum(0), L(-1), R(-1) {}
    };
    vector<Node> t;
    vector<int> root;
    int n;

    int buat(ll sum = 0, int L = -1, int R = -1) {
        t.push_back(Node());
        t.back().sum = sum;
        t.back().L = L;
        t.back().R = R;
        return (int)t.size() - 1;
    }

    int build(int l, int r, const vector<ll>& a) {
        if (l == r) return buat(a[l]);
        int m = (l + r) / 2;
        int L = build(l, m, a), Rgt = build(m + 1, r, a);
        return buat(t[L].sum + t[Rgt].sum, L, Rgt);
    }

    int update(int v, int l, int r, int i, ll x) {
        if (l == r) return buat(x);
        int m = (l + r) / 2;
        int L = t[v].L, Rgt = t[v].R;
        if (i <= m) L = update(L, l, m, i, x);
        else Rgt = update(Rgt, m + 1, r, i, x);
        return buat(t[L].sum + t[Rgt].sum, L, Rgt);
    }

    ll query(int v, int l, int r, int ql, int qr) const {
        if (v < 0 || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v].sum;
        int m = (l + r) / 2;
        return query(t[v].L, l, m, ql, qr) + query(t[v].R, m + 1, r, ql, qr);
    }

    void init(const vector<ll>& a) {
        n = (int)a.size();
        t.clear();
        root.clear();
        t.reserve((n + 5) * 20);
        root.push_back(n ? build(0, n - 1, a) : -1);
    }
};
```

Pakai: `root.push_back(update(root.back(), 0, n-1, i, x))`.

**Jebakan:** menimpa `t[v]` seperti pohon biasa — versi lama rusak. `reserve` kurang → realloc lambat, tetap benar. n + q log n simpul: q=2e5, log=18 → ~ 4e6 simpul, hitung memori.

**Kompleksitas:** build O(n), update O(log n) simpul baru, query O(log n). Memori O(n + q log n).

## K-th pada prefix

**Teori:** pohon persisten sebagai BIT frekuensi per prefix. Versi i = frekuensi `a[0..i-1]` (nilai terkompresi). k-th pada `[L, R]` (0-based inklusif) = jalan bersama `root[R+1]` dan `root[L]`: selisih count kiri memutus ke kiri atau kanan.

**Kapan:** CSES *Range Queries* k-th, “median subarray” offline.

**Proses:** a = `[3, 1, 2, 1]`, kompres 1→0, 2→1, 3→2.

```
versi 0 kosong
versi 1: {3}
versi 2: {3,1}
versi 3: {3,1,2}
versi 4: {3,1,2,1}

k-th=2 pada [0,3] = urutan 1,1,2,3 → 1
k-th=3 pada [1,3] = 1,2,1 → 1,1,2 → 2
```

**Kode:** pohon jumlah pada domain 0..m-1.

```cpp
int updateCnt(Persist& P, int v, int l, int r, int i, ll add) {
    if (l == r) return P.buat(P.t[v].sum + add);
    int m = (l + r) / 2;
    int L = P.t[v].L, Rgt = P.t[v].R;
    if (L < 0) L = P.buat();
    if (Rgt < 0) Rgt = P.buat();
    if (i <= m) L = updateCnt(P, L, l, m, i, add);
    else Rgt = updateCnt(P, Rgt, m + 1, r, i, add);
    return P.buat(P.t[L].sum + P.t[Rgt].sum, L, Rgt);
}

int kth(const Persist& P, int vl, int vr, int l, int r, int k) {
    if (l == r) return l;
    int m = (l + r) / 2;
    ll kiri = 0;
    int Lr = P.t[vr].L, Ll = (vl >= 0 ? P.t[vl].L : -1);
    if (Lr >= 0) kiri += P.t[Lr].sum;
    if (Ll >= 0) kiri -= P.t[Ll].sum;
    if (k <= kiri) return kth(P, Ll, Lr, l, m, k);
    return kth(P, (vl >= 0 ? P.t[vl].R : -1), P.t[vr].R, m + 1, r, k - (int)kiri);
}
```

Bangun versi: mulai `root[0]` pohon kosong, `root[i+1] = updateCnt(..., idx(a[i]), +1)`.

**Jebakan:** k di luar 1..panjang rentang. Kompresi 1-based vs 0-based campur. `vl` pohon kosong: simpul dummy sum 0, atau cek `-1`.

**Kompleksitas:** O((n+q) log m).

## Sqrt decomposition

**Teori:** potong array jadi blok berukuran B ≈ √n. Precompute jawaban tiap blok. Query = ekor kiri + blok utuh + ekor kanan. Update titik: ubah elemen, bangun ulang **satu blok**.

Ini jembatan mental ke Mo: keduanya hidup dari blok akar.

**Kapan:** operasi sulit masuk Segment Tree (misalnya jumlah nilai di blok yang > k, rebuild O(B) cukup). Jangan jika SegTree sudah cukup.

**Proses:** n=9, B=3, a = `[4, 1, 3, 2, 8, 5, 7, 6, 0]`.

```
blok 0: 4 1 3   min=1
blok 1: 2 8 5   min=2
blok 2: 7 6 0   min=0

query min [2,7] = min(ekor 3, blok 2, ekor 7 6) = min(3,2,7,6) = 2
```

**Kode:**

```cpp
struct SqrtMin {
    int n, B, nb;
    vector<int> a, blk;

    explicit SqrtMin(const vector<int>& a_) : a(a_) {
        n = (int)a.size();
        B = max(1, (int)sqrt(n));
        nb = (n + B - 1) / B;
        blk.assign(nb, INT_MAX);
        for (int i = 0; i < n; i++) blk[i / B] = min(blk[i / B], a[i]);
    }

    void setPos(int i, int x) {
        a[i] = x;
        int b = i / B;
        int L = b * B, R = min(n, L + B);
        blk[b] = INT_MAX;
        for (int j = L; j < R; j++) blk[b] = min(blk[b], a[j]);
    }

    int query(int l, int r) const {         // inklusif
        int ans = INT_MAX;
        while (l <= r && l % B != 0) ans = min(ans, a[l++]);
        while (l + B - 1 <= r) {
            ans = min(ans, blk[l / B]);
            l += B;
        }
        while (l <= r) ans = min(ans, a[l++]);
        return ans;
    }
};
```

**Jebakan:** `B=0` jika n=0. Rebuild lupa `min(n, L+B)`. Query seluruhnya di dalam satu blok harus tetap benar (hanya loop ekor).

**Kompleksitas:** build O(n), query O(√n), update O(√n) jika rebuild. Memori O(n).

## Sqrt: update dan blok

**Teori:** kadang update rentang: tandai blok utuh “+v”, ekor diubah mentah. Query memasukkan tanda blok. Ini lazy versi kasar.

**Kapan:** n ≤ 10^5, O(√n) lolos (√n ≈ 320, q·√n ≈ 3·10^7).

**Proses:** n=6, B=3, add +2 pada `[1, 4]`.

```
ekor kiri indeks 1,2 (blok 0): a mentah +2
blok 1 utuh [3,5] tidak penuh karena r=4
ekor kanan 3,4: a mentah +2
```

Jika `[0,5]` penuh dua blok: `lazyBlok[0]+=2`, `lazyBlok[1]+=2`.

**Kode:** jumlah + lazy blok.

```cpp
struct SqrtAdd {
    int n, B, nb;
    vector<ll> a, sum, lz;

    explicit SqrtAdd(const vector<ll>& a_) : a(a_) {
        n = (int)a.size();
        B = max(1, (int)sqrt(n));
        nb = (n + B - 1) / B;
        sum.assign(nb, 0);
        lz.assign(nb, 0);
        for (int i = 0; i < n; i++) sum[i / B] += a[i];
    }

    void addRange(int l, int r, ll v) {
        while (l <= r && l % B != 0) {
            a[l] += v;
            sum[l / B] += v;
            l++;
        }
        while (l + B - 1 <= r) {
            lz[l / B] += v;
            sum[l / B] += v * B;
            l += B;
        }
        while (l <= r) {
            a[l] += v;
            sum[l / B] += v;
            l++;
        }
    }

    ll query(int l, int r) const {
        ll ans = 0;
        while (l <= r && l % B != 0) {
            ans += a[l] + lz[l / B];
            l++;
        }
        while (l + B - 1 <= r) {
            ans += sum[l / B];
            l += B;
        }
        while (l <= r) {
            ans += a[l] + lz[l / B];
            l++;
        }
        return ans;
    }
};
```

Blok terakhir lebih pendek dari B: `sum += v*B` salah. Perbaiki: panjang nyata `min(B, n - b*B)`.

```cpp
int panjangBlok(int b, int n, int B) { return min(B, n - b * B); }
```

**Jebakan:** blok terakhir. Query ekor harus + `lz`. Double count: `sum` sudah termasuk lazy utuh, jangan + lz lagi pada blok utuh.

**Kompleksitas:** O(√n).

## Algoritma Mo

**Teori:** q query `[l,r]` **offline**. Kamu bisa menambah/menghapus **satu indeks** ke jendela dan menjaga jawaban (misalnya banyak nilai unik). Naif: tiap query dari nol, O(n) per query.

Mo mengurutkan query supaya jendela jarang loncat. Potong kiri jadi blok B ≈ √n. Urut: blok kiri dulu; dalam blok sama, urut `r` (zigzag: blok ganjil `r` menurun).

Total pergerakan ≈ O((n+q) √n) add/remove.

Analogi: perpustakaan. Jangan ambil lantai 1, lalu 8, lalu 2. Kelompokkan per lorong.

**Kapan:**

- Pakai: query offline, add/remove O(1) atau O(log n), n,q ≈ 10^5.
- Jangan: update array di tengah (Mo dengan waktu, lebih rumit).
- Jangan: query online.
- Jangan: add/remove mahal.

**Proses:** a = `[1, 2, 1, 3]`, unik: Q0=`[0,2]`, Q1=`[1,3]`, Q2=`[0,3]`. B=2.

```
semua l di blok 0
urut r: Q0 r=2, Q2 r=3, Q1 r=3
jendela cl=0, cr=-1 kosong

Q0: cr ke 2, add 0,1,2 → unik 2
Q2: cr ke 3, add 3 → unik 3
Q1: cl ke 1, del 0 → unik 3
```

**Kode:** urutan.

```cpp
struct Query {
    int l, r, idx;
};

int Bmo;

bool moKurang(const Query& a, const Query& b) {
    int ba = a.l / Bmo, bb = b.l / Bmo;
    if (ba != bb) return ba < bb;
    if (ba & 1) return a.r > b.r;
    return a.r < b.r;
}
```

**Jebakan:** menulis jawaban ke `qs` yang sudah di-sort tanpa `idx`. `B = 0`.

**Kompleksitas:** O((n+q) √n · biaya add/remove).

## Add/remove unik

**Teori:** `cnt[x]++`: jika 0→1, jawaban +1. `cnt[x]--`: jika 1→0, jawaban −1. Nilai besar dikompresi.

Urutan geser **wajib**:

```
while cr < qr: add(++cr)
while cr > qr: del(cr--)
while cl < ql: del(cl++)
while cl > ql: add(--cl)
```

Salah urutan `++` / `--` = akses di luar atau dobel.

**Kapan:** distinct, jumlah frekuensi², “banyak yang muncul tepat k kali” (sesuaikan `cur`).

**Proses:** dari jendela `[0,2]` ke `[1,3]` pada contoh: del indeks 0 (nilai 1, cnt 2→1, unik tetap), add indeks 3 (nilai 3, unik +1). Di urutan Mo di atas, Q1 setelah Q2: hanya del 0 dari `[0,3]`.

**Kode:**

```cpp
vector<int> moUnik(vector<int> a, vector<Query> qs) {
    int n = (int)a.size(), q = (int)qs.size();
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int& x : a) x = int(lower_bound(b.begin(), b.end(), x) - b.begin());

    Bmo = max(1, (int)sqrt(n));
    sort(qs.begin(), qs.end(), moKurang);

    vector<int> cnt((int)b.size() + 2), ans(q);
    int cur = 0, cl = 0, cr = -1;

    auto add = [&](int i) {
        if (cnt[a[i]]++ == 0) cur++;
    };
    auto del = [&](int i) {
        if (--cnt[a[i]] == 0) cur--;
    };

    for (auto qu : qs) {
        while (cr < qu.r) add(++cr);
        while (cr > qu.r) del(cr--);
        while (cl < qu.l) del(cl++);
        while (cl > qu.l) add(--cl);
        ans[qu.idx] = cur;
    }
    return ans;
}

int main() {
    FASTIO;
    vector<int> a = {1, 2, 1, 3};
    vector<Query> qs = {{0, 2, 0}, {1, 3, 1}, {0, 3, 2}};
    auto ans = moUnik(a, qs);
    for (int x : ans) cout << x << ' ';     // 2 3 3
    cout << '\n';
}
```

**Jebakan:**

- `++cr` vs `add(cr++)` — yang kedua add dulu pada indeks lama.
- `cnt` diindeks 10^9.
- `cl=0, cr=-1` awal; jangan `cr=0` lalu add 0 tanpa sadar.
- Hilbert order kadang lebih cepat; zigzag blok sudah cukup sering.

**Kompleksitas:** O((n+q)√n). n=q=1e5, √n=316, ~ 3e7 operasi.

## Mo dengan update? Peta

**Teori:** tiap update punya waktu. Query jadi `(l, r, waktu)`. Blok 3D, lebih rumit. Untuk cheatsheet ini: jika ada update, pikir persisten, SegTree, atau sqrt dulu.

**Kapan:** bukan pilihan pertama.

**Proses:** soal “ubah a[i], berapa unik `[l,r]`”. Offline dengan waktu = Mo+update. Alternatif: SegTree of sets O(n log²) memori berat.

**Kode:** tidak ditulis penuh — mudah salah 50 baris urutan.

**Jebakan:** menempel Mo biasa pada soal ber-update. Jawaban memakai array awal, tes 1 lolos jika update di akhir.

**Kompleksitas:** khas O(n^{5/3}) dengan ukuran blok n^{2/3}.

## Pilih alat

**Teori:**

| Kalimat | Alat |
|---|---|
| unik `[l,r]`, offline, array mati | Mo |
| min `[l,r]`, update titik, malas SegTree | sqrt |
| k-th `[l,r]` | persisten + kompresi |
| jumlah versi t | persisten |
| jumlah `[l,r]` update titik | Fenwick, bukan Mo |

**Kapan:** baca “online/offline” di soal. Jika query ke-i tergantung jawaban i−1, Mo mati.

**Proses:** n=5000, q=5000 unik. O(nq) naif 25 juta juga lolos. Jangan pamer Mo.

**Kode:** naif kadang juara.

**Jebakan:** over-engineering.

**Kompleksitas:** n≤5000 → O(n²) sah.

## Uji naif

**Teori:** Mo vs set pada setiap query. Sqrt vs loop. Persisten vs salin array.

**Kapan:** setelah menulis add/remove.

**Proses:** n≤12, semua query.

**Kode:**

```cpp
int unikNaif(const vector<int>& a, int l, int r) {
    vector<int> b(a.begin() + l, a.begin() + r + 1);
    sort(b.begin(), b.end());
    return int(unique(b.begin(), b.end()) - b.begin());
}

bool cekMo(int n, int q, int seed) {
    mt19937 rng(seed);
    vector<int> a(n);
    for (int& x : a) x = int(rng() % 6);
    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        int l = rng() % n, r = rng() % n;
        if (l > r) swap(l, r);
        qs[i] = {l, r, i};
    }
    auto ans = moUnik(a, qs);
    for (int i = 0; i < q; i++)
        if (ans[i] != unikNaif(a, qs[i].l, qs[i].r)) return false;
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 100; s++)
        if (!cekMo(10, 20, s)) {
            cout << "WA " << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

Catatan: setelah `moUnik`, `qs` ter-sort — simpan salinan untuk naif, atau pakai `idx` + array `l,r` terpisah. Versi di atas bug: `qs` sudah berubah urutan. Perbaiki:

```cpp
    vector<Query> asal = qs;
    auto ans = moUnik(a, qs);
    for (int i = 0; i < q; i++)
        if (ans[asal[i].idx] != unikNaif(a, asal[i].l, asal[i].r)) return false;
```

`moUnik` mengembalikan menurut `idx`, jadi `ans[i]` = query dengan `idx=i`. Cukup `unikNaif(a, asal[i].l, asal[i].r)` vs `ans[asal[i].idx]`.

**Jebakan:** membandingkan `ans[i]` dengan query ter-sort ke-i.

**Kompleksitas:** tes O(q n log n) naif.

## Ringkasan

1. Persisten = salin jalur, versi = akar. Memori O(n + q log n).
2. k-th `[L,R]` = selisih dua versi prefix.
3. Sqrt = blok √n, query/update O(√n).
4. Mo = jadwal jendela, bukan struktur. Offline saja.
5. Urutan add/remove mudah WA — hafalkan empat `while`.
6. Ada update + unik: pikir dulu sebelum Mo+waktu.

Latihan Day 179–183. Jangan salin folder latihan.
