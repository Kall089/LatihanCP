# Treap, DSU rollback, PBS

[← Persisten, sqrt, Mo](persistent-sqrt-mo.md) · [Struktur data](README.md) · [Pohon →](../11-pohon/README.md)

Day 185–189. Tiga teknik “berat”: BST acak yang bisa di-split, DSU yang bisa mundur, dan binary search paralel pada banyak query.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Bukan malware, bukan exploit. Ini struktur data kontes.

## Daftar isi

- [Treap eksplisit](#treap-eksplisit)
- [Split dan merge](#split-dan-merge)
- [Treap implisit](#treap-implisit)
- [Array dinamis](#array-dinamis)
- [DSU biasa vs rollback](#dsu-biasa-vs-rollback)
- [DSU rollback](#dsu-rollback)
- [Parallel Binary Search](#parallel-binary-search)
- [PBS + DSU](#pbs--dsu)
- [Kapan pilih yang mana](#kapan-pilih-yang-mana)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Treap eksplisit

**Teori:** Treap = BST menurut **kunci** + heap menurut **prioritas acak**. Anak kiri kunci lebih kecil, anak kanan lebih besar. Prioritas ayah ≥ anak (max-heap). Prioritas acak membuat bentuk pohon “seperti random BST”, tinggi harapan O(log n).

Analogi: antrian orang terurut nama (BST), tetapi yang “tinggi prioritas” lebih dekat ke akar.

`mt19937` untuk prioritas. Jangan `rand()` kecil jika n besar (tabrakan prioritas hanya merusak keseimbangan, tetap BST benar).

**Kapan:**

- Pakai: set dinamis, split menurut kunci, gabung dua pohon dengan semua kunci kiri < semua kunci kanan.
- Jangan: `std::set` sudah cukup dan kamu tidak butuh split/merge.
- Jangan: prioritas deterministik monoton — pohon jadi rantai.

**Proses:** sisip kunci 2, 1, 3. Misal prioritas 2 > 1 > 3.

```
sisip 2: akar 2
sisip 1: kiri dari 2 (kunci), prioritas 1 < 2 → tetap anak
sisip 3: kanan dari 2
pohon:    2
         / \
        1   3
```

Jika 3 punya prioritas terbesar, rotasi: 3 akar, 2 di kiri, 1 di kiri-kiri.

**Kode:** simpul.

```cpp
struct Treap {
    struct Node {
        int key, pri, sz;
        ll sum;
        Node *L, *R;
        Node(int k, int p) : key(k), pri(p), sz(1), sum(k), L(0), R(0) {}
    };
    Node* root = nullptr;
    mt19937 rng{123};

    int sz(Node* v) const { return v ? v->sz : 0; }
    ll sum(Node* v) const { return v ? v->sum : 0; }

    void pull(Node* v) {
        if (!v) return;
        v->sz = 1 + sz(v->L) + sz(v->R);
        v->sum = v->key + sum(v->L) + sum(v->R);
    }
};
```

**Jebakan:** lupa `pull` setelah ubah anak. Pointer mentah: di kontes biasanya tidak `delete` (waktu habis), program selesai = OS bersihkan. Jangan bocor di aplikasi panjang.

**Kompleksitas:** harapan O(log n) per operasi, memori O(n).

## Split dan merge

**Teori:** dua primitif.

- `split(t, k) → (L, R)`: L semua kunci `< k`, R sisanya. (Kadang `<= k`.)
- `merge(L, R)`: semua kunci L < semua kunci R, gabung menurut prioritas.

Sisip `x`: split di `x`, split lagi di `x+1` untuk cek duplikat, merge tiga bagian dengan simpul baru.

Hapus `x`: split `<x`, split `≤x`, buang tengah, merge sisa.

Kenapa merge O(log): hanya jalan di tulang prioritas, seperti heap.

**Kapan:** semua operasi treap diturunkan dari split/merge.

**Proses:** pohon kunci `{1,2,4,7}`, split k=4.

```
L = {1,2}   (kunci < 4)
R = {4,7}
sisip 3: merge(L, node 3, R) setelah split <3 dan <4...
```

Angka: split 4 pada urutan 1,2,4,7.

```
akar 4? tergantung pri. Secara set: {1,2} dan {4,7}.
```

**Kode:**

```cpp
void split(Treap::Node* t, int k, Treap::Node*& a, Treap::Node*& b) {
    if (!t) {
        a = b = nullptr;
        return;
    }
    if (t->key < k) {
        split(t->R, k, t->R, b);
        a = t;
    } else {
        split(t->L, k, a, t->L);
        b = t;
    }
    // pull t setelah anak berubah — panggil method pull di luar atau inline
    if (t) {
        t->sz = 1 + (t->L ? t->L->sz : 0) + (t->R ? t->R->sz : 0);
        t->sum = t->key + (t->L ? t->L->sum : 0) + (t->R ? t->R->sum : 0);
    }
}

Treap::Node* merge(Treap::Node* a, Treap::Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) {
        a->R = merge(a->R, b);
        a->sz = 1 + (a->L ? a->L->sz : 0) + (a->R ? a->R->sz : 0);
        a->sum = a->key + (a->L ? a->L->sum : 0) + (a->R ? a->R->sum : 0);
        return a;
    }
    b->L = merge(a, b->L);
    b->sz = 1 + (b->L ? b->L->sz : 0) + (b->R ? b->R->sz : 0);
    b->sum = b->key + (b->L ? b->L->sum : 0) + (b->R ? b->R->sum : 0);
    return b;
}

void sisip(Treap& tr, int key) {
    Treap::Node *a, *b;
    split(tr.root, key, a, b);
    auto* nd = new Treap::Node(key, int(tr.rng()));
    tr.root = merge(a, merge(nd, b));
}

bool ada(Treap& tr, int key) {
    Treap::Node *a, *b, *c;
    split(tr.root, key, a, b);
    split(b, key + 1, b, c);
    bool ok = b != nullptr;
    tr.root = merge(a, merge(b, c));
    return ok;
}
```

**Jebakan:** `split` dengan `<=` vs `<` tidak konsisten antara sisip dan hapus. `merge` dipanggil saat kunci tidak terurut → BST rusak, gejala acak. `new` tanpa simpan pointer: tidak bisa hapus fisik, cukup putus.

**Kompleksitas:** harapan O(log n).

## Treap implisit

**Teori:** kunci = **posisi** di array, tidak disimpan. Ukuran subtree kiri = indeks. Split menurut **banyak elemen** k: L punya k simpul, R sisanya.

Ini array dinamis: sisip di tengah, hapus segmen, reverse segmen (lazy flip), jumlah segmen.

Prioritas tetap acak. `push` lazy sebelum baca ukuran anak.

**Kapan:** “array yang dipotong-tempel”, rotate range, reverse `[l,r]`, CSES *Cut and Paste* / *Reversals*.

**Jangan:** `vector` + `insert` O(n). n,q 10^5 butuh treap/splay.

**Proses:** array `[10, 20, 30, 40]`. Split k=2 → `[10,20]` dan `[30,40]`. Merge balik. Reverse `[1,2]` (0-based 1..2) → `[10, 30, 20, 40]`.

Langkah reverse `[1,2]`:

```
split 1 → A=[10]  rest=[20,30,40]
split rest 2 → B=[20,30] C=[40]
flip B
merge A,B,C
```

**Kode:** simpul implisit.

```cpp
struct INode {
    int pri, sz;
    ll val, sum;
    bool rev;
    INode *L, *R;
    INode(ll v, int p) : pri(p), sz(1), val(v), sum(v), rev(0), L(0), R(0) {}
};

int isz(INode* v) { return v ? v->sz : 0; }
ll isum(INode* v) { return v ? v->sum : 0; }

void ipull(INode* v) {
    if (!v) return;
    v->sz = 1 + isz(v->L) + isz(v->R);
    v->sum = v->val + isum(v->L) + isum(v->R);
}

void applyRev(INode* v) {
    if (!v) return;
    v->rev ^= 1;
    swap(v->L, v->R);
}

void ipush(INode* v) {
    if (!v || !v->rev) return;
    applyRev(v->L);
    applyRev(v->R);
    v->rev = 0;
}
```

**Jebakan:** `split` implisit memakai ukuran **setelah** `push`. Lupa `push` lalu ukuran kiri salah, potongan bergeser.

**Kompleksitas:** harapan O(log n) per split/merge.

## Array dinamis

**Teori:** `split_sz(t, k, a, b)`: a mendapat k elemen kiri.

**Kapan:** semua query posisi 0-based `[l, r]` inklusif: ambil `k = r-l+1` setelah membuang prefix l.

**Proses:** jumlah `[1, 2]` pada `[10, 20, 30, 40]`.

```
split 1 → A, rest
split rest 2 → B, C
jawab B.sum = 50
root = merge(A, merge(B, C))
```

**Kode:**

```cpp
void splitSz(INode* t, int k, INode*& a, INode*& b) {
    if (!t) {
        a = b = nullptr;
        return;
    }
    ipush(t);
    if (isz(t->L) >= k) {
        splitSz(t->L, k, a, t->L);
        b = t;
    } else {
        splitSz(t->R, k - isz(t->L) - 1, t->R, b);
        a = t;
    }
    ipull(t);
}

INode* mergeI(INode* a, INode* b) {
    if (!a || !b) return a ? a : b;
    ipush(a);
    ipush(b);
    if (a->pri > b->pri) {
        a->R = mergeI(a->R, b);
        ipull(a);
        return a;
    }
    b->L = mergeI(a, b->L);
    ipull(b);
    return b;
}

ll rangeSum(INode*& root, int l, int r, mt19937&) {
    INode *A, *B, *C;
    splitSz(root, l, A, B);
    splitSz(B, r - l + 1, B, C);
    ll ans = isum(B);
    root = mergeI(A, mergeI(B, C));
    return ans;
}

void rangeRev(INode*& root, int l, int r) {
    INode *A, *B, *C;
    splitSz(root, l, A, B);
    splitSz(B, r - l + 1, B, C);
    applyRev(B);
    root = mergeI(A, mergeI(B, C));
}

INode* bangunArray(const vector<ll>& a, mt19937& rng) {
    INode* t = nullptr;
    for (ll x : a) t = mergeI(t, new INode(x, int(rng())));
    return t;
}
```

**Jebakan:** `r-l+1` saat `r<l`. Indeks 1-based soal lupa −1. `applyRev` pada `B` null jika rentang kosong.

**Kompleksitas:** O(log n) harapan per query.

## DSU biasa vs rollback

**Teori:** DSU biasa: `parent`, `sz`, path compression + union by size. Path compression **menulis** banyak simpul. Tidak bisa di-undo murah.

DSU rollback: **tanpa** path compression, hanya union by size/rank. `find` O(log n). Setiap `unite` mencatat apa yang berubah. `rollback` ke timestamp.

**Kapan:** DSU biasa untuk MST, konektivitas offline tanpa mundur. Rollback untuk “tambah sisi, tanya, hapus sisi” secara DFS pada waktu, atau PBS.

**Proses:** unite 1-2, unite 2-3, rollback sekali → 3 lepas, 1-2 tetap.

```
awal: {1}{2}{3}  komponen 3
unite 1,2: {1,2}{3}  komponen 2
unite 2,3: {1,2,3}   komponen 1
rollback:  {1,2}{3}
```

**Kode:** DSU biasa (tidak rollback):

```cpp
struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};
```

**Jebakan:** memakai `p[x]=find(p[x])` lalu berharap rollback mudah. Jangan.

**Kompleksitas:** biasa hampir O(1). Rollback O(log n) find.

## DSU rollback

**Teori:** stack perubahan: `(simpul, parentLama, szAyahLama)` atau cukup simpul yang `p[b]=a` dan ukuran. `snapshot()` = ukuran stack. `rollback(t)` pop sampai t.

`find` hanya naik, tidak menulis.

**Kapan:** DFS pada segmen waktu sisi hidup, divide & conquer on queries, PBS.

**Proses:** angka di atas, jejak stack.

```
unite 1,2: simpan (b=2, p=2, sz[1]=1), p[2]=1, sz[1]=2
unite 2,3: find 2→1, simpan (3,3,sz1=2), p[3]=1, sz[1]=3
rollback: p[3]=3, sz[1]=2
```

**Kode:**

```cpp
struct DSURoll {
    vector<int> p, sz;
    vector<pair<int, int>> stk;             // (b, a) : p[b] jadi a, sz[a] bertambah
    int kom;

    explicit DSURoll(int n) : p(n), sz(n, 1), kom(n) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) const {
        while (x != p[x]) x = p[x];
        return x;
    }

    int snap() const { return (int)stk.size(); }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            stk.push_back({-1, -1});        // no-op agar rollback selaras
            return false;
        }
        if (sz[a] < sz[b]) swap(a, b);
        stk.push_back({b, a});
        p[b] = a;
        sz[a] += sz[b];
        kom--;
        return true;
    }

    void rollback(int t) {
        while ((int)stk.size() > t) {
            auto [b, a] = stk.back();
            stk.pop_back();
            if (b < 0) continue;
            sz[a] -= sz[b];
            p[b] = b;
            kom++;
        }
    }
};
```

**Jebakan:** rollback tanpa no-op: jumlah `unite` dan `rollback` tidak selaras jika kamu hitung langkah. Path compression terselip. `swap(a,b)` setelah simpan — simpan **setelah** putuskan ayah.

**Kompleksitas:** unite/find O(log n), rollback O(1) per pop.

## Parallel Binary Search

**Teori:** q query, masing-masing “kapan pertama syarat jadi benar?” (misalnya kapan dua kota terhubung setelah sisi ditambah berurutan). Naif: binary search per query × simulasi = O(q log m · biaya).

PBS: semua query binary search **bersamaan**. Pertahankan `lo[i], hi[i]`. Mid = `(lo+hi)/2`. Kelompokkan query yang mid-nya sama, jalankan **satu** simulasi maju, jawab semua kelompok, mundur (rollback) atau bangun ulang.

Satu “gelombang” O(biaya simulasi penuh). Ada O(log m) gelombang. Total O(log m · (m + q) · α) untuk DSU.

Analogi: ujian banyak orang, tanya “lulus di tes ke berapa?”. Jangan ulang seluruh semester per orang. Maju kalender sekali, catat siapa yang lulus hari ini.

**Kapan:**

- Pakai: banyak query monoton terhadap waktu/parameter, simulasi bisa maju + rollback atau diulang per lapisan.
- Jangan: syarat tidak monoton.
- Jangan: q kecil dan simulasi murah — binary search biasa lebih pendek.

**Proses:** 3 query, m = 8 sisi. Awal lo=0, hi=8 (waktu 1..8, 0 = belum).

```
gelombang 1 mid = 4
  jalankan sisi 1..4
  query A sudah terhubung → hi=4
  query B,C belum → lo=4
gelombang 2 mid A=2, mid B,C=6
  ...
sampai hi=lo+1
```

**Kode:** kerangka.

```cpp
vector<int> pbsWaktu(int q, int m, function<void(int)> resetSim,
                     function<void(int)> applyWaktu, // apply event ke-t (1-based)
                     function<bool(int)> sudah) {    // query i terpenuhi?
    vector<int> lo(q, 0), hi(q, m + 1);
    for (int iter = 0; iter < 18; iter++) {
        vector<vector<int>> bucket(m + 2);
        bool ada = false;
        for (int i = 0; i < q; i++) {
            if (lo[i] + 1 >= hi[i]) continue;
            int mid = (lo[i] + hi[i]) / 2;
            bucket[mid].push_back(i);
            ada = true;
        }
        if (!ada) break;
        resetSim(0);
        for (int t = 1; t <= m; t++) {
            applyWaktu(t);
            for (int i : bucket[t]) {
                if (sudah(i)) hi[i] = t;
                else lo[i] = t;
            }
        }
    }
    return hi;
}
```

Versi ini **membangun ulang** tiap gelombang (reset + apply 1..m). Lebih mudah daripada rollback. Jika apply mahal dan m besar, pakai DSU rollback + DFS pada segmen mid.

**Jebakan:** `hi = m+1` artinya tidak pernah. Off-by-one mid: event t diterapkan sebelum dicek query mid=t. Monoton: jika benar di t, benar di t+1 — wajib.

**Kompleksitas:** O(log m · (m + q) · biaya apply/cek).

## PBS + DSU

**Teori:** sisi terurut waktu. Query “kapan x dan y satu komponen?”. `apply` = `unite`. `sudah` = `find(x)==find(y)`.

**Kapan:** CSES *Road Construction* varian query, CF klasik “when connected”.

**Proses:** n=4, sisi (1-2), (3-4), (2-3). Query (1,4).

```
setelah 1: 1-2, 3|4  belum
setelah 2: 1-2, 3-4  belum
setelah 3: semua     ya → jawaban 3
```

PBS: mid=2, belum, lo=2; mid=3, ya, hi=3.

**Kode:**

```cpp
struct Sisi { int a, b; };

vector<int> kapanTerhubung(int n, const vector<Sisi>& e,
                           const vector<pair<int, int>>& qq) {
    int m = (int)e.size(), q = (int)qq.size();
    DSU dsu(n);
    auto reset = [&](int) {
        dsu = DSU(n);
    };
    auto apply = [&](int t) {               // t 1-based
        dsu.unite(e[t - 1].a, e[t - 1].b);
    };
    auto sudah = [&](int i) {
        return dsu.find(qq[i].first) == dsu.find(qq[i].second);
    };
    return pbsWaktu(q, m, reset, apply, sudah);
}
```

**Jebakan:** simpul 1-based, DSU 0-based. Sisi ganda. Query x=y jawaban 0.

**Kompleksitas:** O(log m · (m + q) α(n)).

## Kapan pilih yang mana

**Teori:**

| Kebutuhan | Alat |
|---|---|
| set kunci split | treap eksplisit |
| array potong-tempel / reverse | treap implisit |
| `std::set` cukup | `set`, bukan treap |
| undo unite | DSU rollback |
| banyak “kapan pertama” | PBS |
| k-th pada kunci | treap atau Fenwick + kompresi |

**Kapan:** treap implisit adalah senjata terakhir array. Coba SegTree + lazy reverse dulu jika hanya reverse (bisa), tetapi cut-and-paste antar segmen jauh = treap.

**Proses:** soal reverse `[l,r]` + jumlah. Lazy SegTree cukup. Soal “pindah `[l,r]` ke depan”: treap.

**Kode:** jangan tulis treap 150 baris jika Fenwick 30 baris cukup.

**Jebakan:** prioritas `i` sebagai pri → ter degenerasi.

**Kompleksitas:** harapan vs terburuk: treap harapan; splay terburuk amortized; policy based `order_statistics` GNU — tidak portabel.

## Uji naif

**Teori:** treap implisit vs `vector`. DSU rollback vs salin DSU. PBS vs binary search per query pada n kecil.

**Kapan:** setelah `splitSz`.

**Proses:** n≤15, reverse acak, cek jumlah.

**Kode:**

```cpp
bool cekRev(int n, int q, int seed) {
    mt19937 rng(seed);
    vector<ll> a(n);
    for (int i = 0; i < n; i++) a[i] = i + 1;
    INode* root = bangunArray(a, rng);
    for (int i = 0; i < q; i++) {
        int l = rng() % n, r = rng() % n;
        if (l > r) swap(l, r);
        reverse(a.begin() + l, a.begin() + r + 1);
        rangeRev(root, l, r);
        ll naif = 0;
        for (int j = l; j <= r; j++) naif += a[j];
        if (rangeSum(root, l, r, rng) != naif) return false;
    }
    return true;
}

int main() {
    FASTIO;
    for (int s = 1; s <= 80; s++)
        if (!cekRev(12, 30, s)) {
            cout << "WA " << s << '\n';
            return 0;
        }
    cout << "ok\n";
}
```

**Jebakan:** membandingkan setelah reverse tanpa `push` di `isum` — `rangeSum` sudah split+push. Dump inorder tanpa push mencetak urutan salah.

**Kompleksitas:** tes O(q n).

## Ringkasan

1. Treap = BST + heap acak. Primitif: split, merge.
2. Implisit: kunci = posisi, `push` sebelum baca ukuran.
3. DSU rollback: tanpa path compression, stack perubahan.
4. PBS: binary search semua query bareng, satu simulasi per lapisan.
5. PBS + DSU menjawab “kapan terhubung”.
6. Jangan pakai treap jika `set` atau SegTree cukup.

Latihan Day 185–189. Jangan salin `exercise_*.cpp`.
