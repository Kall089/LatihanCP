/*
============================================================
  Day 53 — Parallel Binary Search | CP Template
============================================================
  MASALAH: q query, masing-masing butuh binary search, dan setiap
  pengujian predikat berbiaya O(n)  ->  O(q n log n)  MUSTAHIL.

  IDE: jalankan SEMUA binary search BERBARENGAN. log(n) putaran,
  masing-masing SATU sapuan yang melayani seluruh query sekaligus.

  SYARAT WAJIB:
    1. OFFLINE -- harus tahu semua query di awal untuk mengelompokkannya
    2. MONOTON -- sekali terpenuhi, selamanya terpenuhi
    3. struktur data bisa dibangun ulang dengan biaya wajar

  PERIKSA DULU SEBELUM MENULIS INI:
    ambang query bisa DIURUTKAN? -> satu sapuan + two pointers, O(n+q)
                                    LEBIH SEDERHANA DAN LEBIH CEPAT
    query harus online?          -> teknik ini TIDAK berlaku
    n, q <= 1000?                -> naif saja, jangan menambah risiko

  BUG NOMOR SATU: lupa reset struktur data di tiap putaran.
  Gejalanya: putaran pertama benar, sisanya salah -- sangat membingungkan
  karena sampel kecil sering hanya butuh satu putaran.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. BIT: range update, point query ───────────────────
// Pilihan struktur yang tepat untuk PBS: update DAN query keduanya
// O(log n). Difference array cepat untuk update tetapi baca O(n) --
// tidak cocok karena kita membaca berkali-kali di tengah sapuan.

struct BIT {
    int n;
    vector<ll> t;

    void init(int n_) { n = n_; t.assign(n + 2, 0); }
    void reset() { fill(t.begin(), t.end(), 0); }          // dipanggil TIAP putaran

    void add(int i, ll v) { for (; i <= n; i += i & -i) t[i] += v; }

    // tambahkan v ke seluruh posisi pada [l, r]
    void rangeAdd(int l, int r, ll v) {
        if (l > r) return;
        add(l, v);
        add(r + 1, -v);
    }

    // nilai pada posisi i
    ll get(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
};

// ─── 2. KERANGKA UMUM PARALLEL BINARY SEARCH ─────────────
/*
    Pakai kerangka ini apa adanya, ganti tiga bagian yang ditandai:

    int n, q;
    vector<int> lo(q, 1), hi(q, n + 1);   // n+1 = "tidak pernah terpenuhi"
    vector<vector<int>> bucket(n + 2);

    while (true) {
        for (auto& b : bucket) b.clear();          // clear, bukan realokasi
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                bucket[lo[i] + (hi[i] - lo[i]) / 2].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        resetStruktur();                            // <-- GANTI (WAJIB ADA)

        for (int t = 1; t <= n; t++) {
            terapkanKejadian(t);                    // <-- GANTI
            for (int i : bucket[t]) {
                if (cukup(i)) hi[i] = t;            // <-- GANTI
                else          lo[i] = t + 1;
            }
        }
    }
    // lo[i] == n+1 berarti kondisinya tidak pernah terpenuhi
*/

// ─── 3. CONTOH LENGKAP: "KAPAN MENCAPAI TARGET" ──────────
// n operasi; operasi ke-t menambah v[t] ke rentang posisi [l[t], r[t]].
// q query: (posisi p, target T) -> operasi keberapa yang membuat
// nilai di posisi p mencapai T? (n+1 kalau tidak pernah)

struct Operasi { int l, r; ll v; };
struct Query   { int p; ll T; };

vector<int> parallelBinarySearch(int m,                    // banyak posisi
                                 const vector<Operasi>& op, // 1-indexed
                                 const vector<Query>& qs) {
    int n = op.size() - 1;                 // op[0] tidak dipakai
    int q = qs.size();

    BIT bit;
    bit.init(m);

    vector<int> lo(q, 1), hi(q, n + 1);
    vector<vector<int>> bucket(n + 2);

    while (true) {
        for (auto& b : bucket) b.clear();
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                int mid = lo[i] + (hi[i] - lo[i]) / 2;
                bucket[mid].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        bit.reset();                        // WAJIB: tanpa ini seluruhnya salah

        for (int t = 1; t <= n; t++) {
            bit.rangeAdd(op[t].l, op[t].r, op[t].v);

            for (int i : bucket[t]) {
                if (bit.get(qs[i].p) >= qs[i].T) hi[i] = t;
                else                             lo[i] = t + 1;
            }
        }
    }
    return lo;                              // lo[i] == n+1 -> tidak pernah
}

// ─── 4. VARIAN SATU SAPUAN (periksa ini DULU!) ───────────
// Kalau ambang query bisa DIURUTKAN dan kondisinya monoton terhadap
// ambang, kamu tidak butuh log n putaran sama sekali -- cukup SATU
// sapuan dengan two pointers. O(n + q log q), jauh lebih sederhana.
//
// Berlaku kalau: seluruh query memeriksa BESARAN GLOBAL yang sama
// (misalnya "total kumulatif"), bukan posisi yang berbeda-beda.

vector<int> satuSapuan(const vector<ll>& tambahan,   // tambahan[t], 1-indexed
                       vector<pair<ll, int>> qs) {   // {target, id}
    int n = tambahan.size() - 1;
    int q = qs.size();
    sort(qs.begin(), qs.end());             // urutkan berdasarkan target

    vector<int> jawab(q, n + 1);
    ll total = 0;
    int ptr = 0;

    for (int t = 1; t <= n; t++) {
        total += tambahan[t];
        while (ptr < q && qs[ptr].first <= total) {
            jawab[qs[ptr].second] = t;
            ptr++;
        }
    }
    return jawab;
}

// ─── 5. NAIF (untuk stress test -- WAJIB dipakai) ────────

vector<int> naif(int m, const vector<Operasi>& op, const vector<Query>& qs) {
    int n = op.size() - 1, q = qs.size();
    vector<int> jawab(q, n + 1);

    for (int i = 0; i < q; i++) {
        vector<ll> a(m + 2, 0);
        for (int t = 1; t <= n; t++) {
            for (int p = op[t].l; p <= op[t].r; p++) a[p] += op[t].v;
            if (a[qs[i].p] >= qs[i].T) { jawab[i] = t; break; }
        }
    }
    return jawab;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int m, n, q;
    if (!(cin >> m >> n >> q)) return 0;

    vector<Operasi> op(n + 1);
    for (int t = 1; t <= n; t++) cin >> op[t].l >> op[t].r >> op[t].v;

    vector<Query> qs(q);
    for (int i = 0; i < q; i++) cin >> qs[i].p >> qs[i].T;

    vector<int> hasil = parallelBinarySearch(m, op, qs);
    vector<int> cek   = naif(m, op, qs);

    for (int i = 0; i < q; i++) {
        cout << (hasil[i] > n ? -1 : hasil[i]);
        cout << (i + 1 == q ? '\n' : ' ');
    }
    cout << "cek naif    :";
    for (int i = 0; i < q; i++) cout << ' ' << (cek[i] > n ? -1 : cek[i]);
    cout << '\n';

    return 0;
}
