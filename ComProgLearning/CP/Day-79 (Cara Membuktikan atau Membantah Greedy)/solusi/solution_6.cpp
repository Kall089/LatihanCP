/*
============================================================
✅ SOLUSI Exercise 6: Kerangka Stress Test Generik
============================================================
Difficulty: Hard | Kompleksitas: O(ITER * biaya satu kasus)

── INI PERKAKAS YANG DISIMPAN, BUKAN SOAL YANG DI-SUBMIT ───
Tujuan berkas ini adalah menjadi bagian dari template
pribadimu. Salin, simpan, pakai berkali-kali.

── PRINSIP RANCANGAN: PISAHKAN YANG BERUBAH ────────────────
Untuk soal apa pun, hanya TIGA hal yang berubah:
    1. cara membangkitkan masukan acak
    2. cara menjalankan strategi yang diuji
    3. cara menghitung jawaban yang pasti benar
Sisanya — perulangan, pencatatan, pengecilan, pelaporan —
identik selamanya.

Di C++, cara terapi adalah fungsi bertemplat yang menerima tiga
objek fungsi. Kode di bawah memakainya. Kalau template terasa
rumit, tiga fungsi biasa dengan percabangan juga cukup; yang
penting strukturnya terpisah.

── BENIH TETAP ─────────────────────────────────────────────
Memakai benih tetap (di sini 20240817) membuat hasilnya bisa
DIREPRODUKSI. Itu penting: kalau kamu menemukan kegagalan lalu
mengubah kode, kamu ingin menjalankan kasus yang SAMA lagi
untuk memastikan perbaikanmu bekerja.
Jangan pernah memakai time(0) sebagai benih pada stress test.

── PENGECILAN ──────────────────────────────────────────────
Dipakai kembali dari Exercise 2: berulang kali coba buang atau
kecilkan; terima kalau greedy MASIH salah.
Ingat pelajaran Exercise 2: JANGAN mengurutkan hasilnya kalau
algoritma yang diuji sensitif terhadap urutan masukan.

── TIGA SOAL YANG DIDUKUNG ─────────────────────────────────
  S = 1 : knapsack 0/1, greedy rasio        (gagal ~11%)
  S = 2 : tukar uang, greedy koin terbesar  (gagal ~8-10%)
  S = 3 : interval, greedy terpendek dulu   (gagal ~2%)

Angka-angka itu diukur, bukan ditebak. Perhatikan bahwa
ketiganya cukup jarang untuk lolos beberapa sampel, dan cukup
sering untuk membuatmu WA.

── PERLUASAN YANG DISARANKAN ───────────────────────────────
Tambahkan mode yang menjalankan soal yang SAMA dengan beberapa
RENTANG nilai berbeda, lalu bandingkan persentase kegagalannya.
Kamu akan melihat sendiri bahwa rentang generator mengubah
kesimpulan (lihat Exercise 3).

── JEBAKAN ─────────────────────────────────────────────────
1. Benih acak berbasis waktu -> hasil tidak bisa direproduksi.
2. Generator berentang besar -> bug tidak pernah muncul.
3. Membandingkan greedy dengan greedy lain, bukan dengan
   jawaban yang pasti benar.
4. Mengoptimalkan brute force sehingga ia sendiri jadi salah.
5. Berhenti pada kegagalan pertama tanpa mengecilkannya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ─── kerangka umum: hanya tiga lambda yang berubah ─────────
template <typename Gen, typename Greedy, typename Benar, typename Kecil>
void jalankan(Gen gen, Greedy greedy, Benar benar, Kecil kecilkan,
              int iter, unsigned benih) {
    mt19937 rng(benih);
    int gagal = 0;
    int ukuranTerkecil = -1;

    for (int t = 0; t < iter; t++) {
        auto in = gen(rng);
        if (greedy(in) != benar(in)) {
            gagal++;
            auto kecil = kecilkan(in);
            int u = (int)kecil.size();
            if (ukuranTerkecil < 0 || u < ukuranTerkecil) ukuranTerkecil = u;
        }
    }
    cout << gagal << ' ' << iter << '\n';
    cout << ukuranTerkecil << '\n';
}

// ─── SOAL 1: knapsack 0/1 ─────────────────────────────────
struct KnapIn { vector<pair<ll, ll>> b; ll W; size_t size() const { return b.size(); } };

ll knapGreedy(const KnapIn& in) {
    vector<int> ord(in.b.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        __int128 k = (__int128)in.b[x].second * in.b[y].first;
        __int128 n = (__int128)in.b[y].second * in.b[x].first;
        if (k != n) return k > n;
        return x < y;
    });
    ll sisa = in.W, tot = 0;
    for (int i : ord) if (in.b[i].first <= sisa) { tot += in.b[i].second; sisa -= in.b[i].first; }
    return tot;
}
ll knapBenar(const KnapIn& in) {
    vector<ll> dp(in.W + 1, 0);
    for (auto& [w, v] : in.b)
        for (ll c = in.W; c >= w; c--) dp[c] = max(dp[c], dp[c - w] + v);
    return dp[in.W];
}

// ─── SOAL 2: tukar uang ───────────────────────────────────
struct KoinIn { vector<ll> c; ll T; size_t size() const { return c.size(); } };

ll koinGreedy(const KoinIn& in) {
    vector<ll> t = in.c;
    sort(t.rbegin(), t.rend());
    ll sisa = in.T, n = 0;
    for (ll v : t) if (v <= sisa) { n += sisa / v; sisa %= v; }
    return sisa == 0 ? n : -1;
}
ll koinBenar(const KoinIn& in) {
    const ll INF = in.T + 1;
    vector<ll> dp(in.T + 1, INF);
    dp[0] = 0;
    for (ll x = 1; x <= in.T; x++)
        for (ll v : in.c) if (v <= x) dp[x] = min(dp[x], dp[x - v] + 1);
    return dp[in.T] >= INF ? -1 : dp[in.T];
}

// ─── SOAL 3: interval saling lepas ────────────────────────
struct IvIn { vector<pair<ll, ll>> v; size_t size() const { return v.size(); } };

ll ivGreedy(const IvIn& in) {
    vector<pair<ll, ll>> a = in.v;
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.second - x.first < y.second - y.first;
    });
    vector<pair<ll, ll>> pilih;
    for (auto& iv : a) {
        bool bentrok = false;
        for (auto& p : pilih)
            if (iv.first < p.second && p.first < iv.second) { bentrok = true; break; }
        if (!bentrok) pilih.push_back(iv);
    }
    return (ll)pilih.size();
}
ll ivBenar(const IvIn& in) {
    vector<pair<ll, ll>> a = in.v;
    sort(a.begin(), a.end(), [](auto& x, auto& y) { return x.second < y.second; });
    ll akhir = LLONG_MIN, hit = 0;
    for (auto& [l, r] : a) if (l >= akhir) { hit++; akhir = r; }
    return hit;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int S, ITER;
    if (!(cin >> S >> ITER)) return 0;
    const unsigned BENIH = 20240817;            // TETAP: hasil bisa direproduksi

    if (S == 1) {
        auto gen = [](mt19937& rng) {
            KnapIn in;
            int n = 1 + rng() % 8;
            in.b.resize(n);
            for (int i = 0; i < n; i++)
                in.b[i] = {(ll)(1 + rng() % 12), (ll)(1 + rng() % 12)};
            in.W = 1 + rng() % 25;
            return in;
        };
        auto kecilkan = [](KnapIn in) {
            bool ubah = true;
            while (ubah) {
                ubah = false;
                for (size_t i = 0; i < in.b.size() && !ubah; i++) {
                    KnapIn k = in;
                    k.b.erase(k.b.begin() + i);
                    if (!k.b.empty() && knapGreedy(k) != knapBenar(k)) { in = k; ubah = true; }
                }
            }
            return in.b;
        };
        jalankan(gen, knapGreedy, knapBenar, kecilkan, ITER, BENIH);

    } else if (S == 2) {
        auto gen = [](mt19937& rng) {
            KoinIn in;
            int n = 2 + rng() % 3;
            set<ll> s{1};
            while ((int)s.size() < n) s.insert(2 + rng() % 12);
            in.c.assign(s.begin(), s.end());
            in.T = 1 + rng() % 30;
            return in;
        };
        auto kecilkan = [](KoinIn in) {
            bool ubah = true;
            while (ubah) {
                ubah = false;
                for (size_t i = 0; i < in.c.size() && !ubah; i++) {
                    if (in.c[i] == 1) continue;         // nilai 1 wajib ada
                    KoinIn k = in;
                    k.c.erase(k.c.begin() + i);
                    if (k.c.size() >= 1 && koinGreedy(k) != koinBenar(k)) { in = k; ubah = true; }
                }
            }
            return in.c;
        };
        jalankan(gen, koinGreedy, koinBenar, kecilkan, ITER, BENIH);

    } else {
        auto gen = [](mt19937& rng) {
            IvIn in;
            int n = 1 + rng() % 8;
            in.v.resize(n);
            for (int i = 0; i < n; i++) {
                ll l = rng() % 12;
                in.v[i] = {l, l + 1 + (ll)(rng() % 6)};
            }
            return in;
        };
        auto kecilkan = [](IvIn in) {
            bool ubah = true;
            while (ubah) {
                ubah = false;
                for (size_t i = 0; i < in.v.size() && !ubah; i++) {
                    IvIn k = in;
                    k.v.erase(k.v.begin() + i);
                    if (!k.v.empty() && ivGreedy(k) != ivBenar(k)) { in = k; ubah = true; }
                }
            }
            return in.v;
        };
        jalankan(gen, ivGreedy, ivBenar, kecilkan, ITER, BENIH);
    }

    return 0;
}
