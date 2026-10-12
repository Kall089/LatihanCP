/*
============================================================
  Day 134 — Disjoint Set Union | CP Template
============================================================
  Struktur data dengan rasio manfaat-terhadap-panjang-kode TERBAIK
  di seluruh CP: sepuluh baris, hampir konstanta, ratusan soal.

  DUA OPTIMASI, KEDUANYA DIBUTUHKAN
    union by size saja     -> O(log n)
    path compression saja  -> O(log n) amortisasi
    KEDUANYA               -> O(alpha(n)), praktis KONSTANTA

  SELALU TULIS VERSI LENGKAPNYA, bukan versi minimal:
    - unite mengembalikan bool  -> dipakai Kruskal & deteksi siklus
    - lacak `komponen`          -> "berapa kelompok"
    - simpan `sz`               -> "berapa anggota"
  Ketiganya GRATIS dan sering langsung diminta soal.

  YANG DSU TIDAK BISA: memisahkan, jarak, jalur, struktur dalam komponen.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. DSU BAKU (hafalkan ini) ──────────────────────────

struct DSU {
    vector<int> par, sz;
    int komponen;

    DSU(int n) : par(n), sz(n, 1), komponen(n) {
        iota(par.begin(), par.end(), 0);
    }

    // PATH HALVING, iteratif -> tidak ada risiko stack overflow
    int find(int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    }

    // true kalau BENAR-BENAR menggabungkan (dipakai Kruskal & deteksi siklus)
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);        // UNION BY SIZE
        par[b] = a;
        sz[a] += sz[b];
        komponen--;
        return true;
    }

    bool sama(int a, int b) { return find(a) == find(b); }

    // find DULU -- membaca sz[x] langsung adalah bug nomor satu
    int ukuran(int x) { return sz[find(x)]; }
};

// ─── 2. KRUSKAL (MST) ────────────────────────────────────
// Mengembalikan total bobot, atau -1 kalau graf tidak terhubung.

ll kruskal(int n, vector<array<ll, 3>> sisi) {     // {bobot, u, v}
    sort(sisi.begin(), sisi.end());
    DSU d(n);
    ll total = 0;
    int dipakai = 0;
    for (auto& e : sisi)
        if (d.unite((int)e[1], (int)e[2])) {       // nilai kembalian dipakai
            total += e[0];
            if (++dipakai == n - 1) break;         // MST selesai
        }
    return dipakai == n - 1 ? total : -1;
}

// ─── 3. DSU DENGAN AGREGAT PER KOMPONEN ──────────────────
// Pola umum: simpan agregat apa pun di AKAR komponen.
// PERINGATAN: agregat hanya valid di akar -> baca lewat find(x).

struct DSUAgregat {
    vector<int> par, sz;
    vector<ll> jumlah;                             // total nilai komponen
    vector<ll> maksimum;                           // nilai terbesar komponen
    int komponen;

    DSUAgregat(const vector<ll>& nilai)
        : par(nilai.size()), sz(nilai.size(), 1),
          jumlah(nilai), maksimum(nilai), komponen((int)nilai.size()) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        jumlah[a] += jumlah[b];                    // gabungkan agregat
        maksimum[a] = max(maksimum[a], maksimum[b]);
        komponen--;
        return true;
    }

    ll totalKomponen(int x) { return jumlah[find(x)]; }   // find DULU
    ll maksKomponen(int x)  { return maksimum[find(x)]; }
};

// ─── 4. DSU DENGAN ROLLBACK (pratinjau Day 191) ──────────
// PATH COMPRESSION HARUS DIBUANG: ia mengubah struktur secara tidak
// terlacak sehingga pembatalan mustahil. Akibatnya O(log n), bukan alpha(n).

struct DSURollback {
    vector<int> par, sz;
    vector<pair<int, int>> riwayat;                // {simpul diubah, ukuran lama}

    DSURollback(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int x) {                              // TANPA path compression
        while (par[x] != x) x = par[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        riwayat.push_back({b, sz[a]});
        par[b] = a;
        sz[a] += sz[b];
        return true;
    }

    void rollback() {
        if (riwayat.empty()) return;
        auto pr = riwayat.back(); riwayat.pop_back();
        sz[par[pr.first]] = pr.second;
        par[pr.first] = pr.first;
    }

    int checkpoint() const { return (int)riwayat.size(); }
    void rollbackKe(int titik) { while ((int)riwayat.size() > titik) rollback(); }
};

// ─── 5. DSU PADA GRID ────────────────────────────────────
// Petakan (r, c) menjadi indeks tunggal. Sering LEBIH MUDAH daripada
// BFS/DFS ketika sel diaktifkan satu per satu.

struct DSUGrid {
    DSU d;
    int R, C;
    DSUGrid(int R_, int C_) : d(R_ * C_), R(R_), C(C_) {}
    int idx(int r, int c) const { return r * C + c; }
    bool valid(int r, int c) const { return r >= 0 && r < R && c >= 0 && c < C; }
};

// ─── 6. TRIK "POSISI KOSONG BERIKUTNYA" ──────────────────
// par[i] berarti "posisi kosong pertama mulai dari i".
// Berguna untuk "tempatkan tiap benda di posisi kosong pertama".

struct PosisiKosong {
    vector<int> nxt;
    PosisiKosong(int n) : nxt(n + 1) { iota(nxt.begin(), nxt.end(), 0); }

    int find(int x) {
        while (nxt[x] != x) { nxt[x] = nxt[nxt[x]]; x = nxt[x]; }
        return x;
    }
    // pakai posisi p, lalu tandai bahwa berikutnya harus mulai dari p+1
    int pakai(int i) {
        int p = find(i);
        if (p < (int)nxt.size() - 1) nxt[p] = p + 1;
        return p;
    }
};

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DSU d(n);
    vector<array<ll, 3>> sisi;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        sisi.push_back({w, (ll)u, (ll)v});
        d.unite(u, v);
    }

    cout << "banyak komponen  : " << d.komponen << '\n';
    cout << "ukuran komp. 0   : " << d.ukuran(0) << '\n';
    cout << "0 dan n-1 sama?  : " << (d.sama(0, n - 1) ? "YA" : "TIDAK") << '\n';
    cout << "bobot MST        : " << kruskal(n, sisi) << '\n';

    return 0;
}
