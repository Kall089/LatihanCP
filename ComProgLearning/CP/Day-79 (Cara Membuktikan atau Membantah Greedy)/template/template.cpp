/*
============================================================
  Day 79 — Membuktikan / Membantah Greedy | Template
============================================================
  KERANGKA KERJA SIAP PAKAI

  Hari ini bukan tentang algoritma baru, melainkan tentang
  PERKAKAS untuk memutuskan apakah sebuah ide greedy benar.

  URUTAN YANG BENAR (dan hampir semua orang membaliknya):
     1. tulis BRUTE FORCE dulu   (5 menit, pasti benar)
     2. tulis GENERATOR yang dirancang untuk memecahkan
     3. baru tulis greedy
     4. adu keduanya ribuan kali
     5. kalau lolos, BARU cari buktinya

  Menulis bukti untuk ide yang salah adalah pemborosan waktu
  terbesar di kontes. Uji dulu, buktikan kemudian.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. KERANGKA STRESS TEST UMUM ─────────────────────────
// Pakai ini apa adanya untuk soal apa pun: cukup ganti tiga
// lambda (generator, greedy, brute) dan panggil.

template <typename Gen, typename Greedy, typename Brute>
void stressTest(Gen gen, Greedy greedy, Brute brute,
                int iterasi, const string& nama) {
    mt19937 rng(12345);
    int gagal = 0;
    bool sudahCetak = false;
    for (int t = 0; t < iterasi; t++) {
        auto in = gen(rng);
        auto a = greedy(in);
        auto b = brute(in);
        if (a != b) {
            gagal++;
            if (!sudahCetak) {                 // cetak contoh PERTAMA saja
                sudahCetak = true;
                cout << "  [" << nama << "] contoh tandingan:\n";
                cout << "    masukan :";
                for (auto v : in) cout << ' ' << v;
                cout << "\n    greedy  : " << a
                     << "\n    optimal : " << b << '\n';
            }
        }
    }
    cout << "  " << left << setw(28) << nama
         << " gagal " << gagal << "/" << iterasi
         << " (" << fixed << setprecision(2)
         << (100.0 * gagal / iterasi) << "%)\n";
}

// ─── 2. MENCARI CONTOH TANDINGAN TERKECIL ─────────────────
// Setelah menemukan bahwa greedy salah, kecilkan contohnya.
// Contoh tandingan kecil jauh lebih mudah dipahami dan
// diingat daripada yang besar.

template <typename Greedy, typename Brute>
vector<ll> perkecil(vector<ll> buruk, Greedy greedy, Brute brute) {
    bool berubah = true;
    while (berubah) {
        berubah = false;
        // coba buang satu elemen
        for (size_t i = 0; i < buruk.size(); i++) {
            vector<ll> kecil = buruk;
            kecil.erase(kecil.begin() + i);
            if (!kecil.empty() && greedy(kecil) != brute(kecil)) {
                buruk = kecil; berubah = true; break;
            }
        }
        if (berubah) continue;
        // coba kecilkan satu nilai
        for (size_t i = 0; i < buruk.size(); i++) {
            for (ll v = 1; v < buruk[i]; v++) {
                vector<ll> kecil = buruk;
                kecil[i] = v;
                if (greedy(kecil) != brute(kecil)) {
                    buruk = kecil; berubah = true; break;
                }
            }
            if (berubah) break;
        }
    }
    return buruk;
}

// ─── 3. CONTOH KONKRET: TUKAR UANG ────────────────────────
// Klaim: "ambil koin terbesar yang muat" itu optimal.
// SALAH untuk sistem koin sembarang.

ll koinGreedy(const vector<ll>& koin, ll target) {
    vector<ll> c = koin;
    sort(c.rbegin(), c.rend());
    ll sisa = target, n = 0;
    for (ll v : c) if (v <= sisa) { n += sisa / v; sisa %= v; }
    return sisa == 0 ? n : -1;
}

ll koinOptimal(const vector<ll>& koin, ll target) {
    const ll INF = target + 1;
    vector<ll> dp(target + 1, INF);
    dp[0] = 0;
    for (ll x = 1; x <= target; x++)
        for (ll v : koin)
            if (v <= x) dp[x] = min(dp[x], dp[x - v] + 1);
    return dp[target] >= INF ? -1 : dp[target];
}

// ─── 4. CONTOH KONKRET: KNAPSACK 0/1 ──────────────────────

ll knapGreedyRasio(const vector<pair<ll,ll>>& b, ll W) {   // (berat, nilai)
    vector<int> ord(b.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        return (__int128)b[x].second * b[y].first > (__int128)b[y].second * b[x].first;
    });
    ll sisa = W, tot = 0;
    for (int i : ord) if (b[i].first <= sisa) { tot += b[i].second; sisa -= b[i].first; }
    return tot;
}

ll knapOptimal(const vector<pair<ll,ll>>& b, ll W) {
    vector<ll> dp(W + 1, 0);
    for (auto& [w, v] : b)
        for (ll c = W; c >= w; c--) dp[c] = max(dp[c], dp[c - w] + v);
    return dp[W];
}

// ─── 5. EMPAT ALAT BUKTI ──────────────────────────────────
//
//  (a) EXCHANGE ARGUMENT
//      Ambil solusi optimal yang melanggar kriteria. Tukar dua
//      elemen berdampingan. Tunjukkan tidak memburuk.
//      -> paling sering dipakai; lihat Day 71.
//
//  (b) GREEDY STAYS AHEAD
//      Tunjukkan bahwa setelah langkah ke-k, solusi greedy
//      selalu "tidak lebih buruk" dari solusi optimal mana pun
//      pada ukuran tertentu.
//      -> cocok untuk activity selection (Day 72).
//
//  (c) ARGUMEN DOMINASI KEADAAN
//      Tunjukkan keadaan yang dihasilkan greedy MENDOMINASI:
//      apa pun yang bisa dilakukan dari keadaan lain, bisa
//      juga dari keadaan ini.
//      -> cocok untuk regret (Day 77).
//
//  (d) BATAS BAWAH BERTEMU BATAS ATAS
//      Tunjukkan batas bawah B untuk semua solusi, lalu
//      tunjukkan greedy mencapai B.
//      -> cocok untuk "ruangan minimum" (Day 72).

// ─── 6. TANDA-TANDA GREEDY AKAN GAGAL ─────────────────────
//
//   n <= 20              -> bitmask / brute force
//   n <= 100 + kapasitas -> DP knapsack
//   ada BOBOT per elemen -> curigai DP
//   dua besaran bersaing -> hampir pasti DP
//   "paling banyak K"    -> DP atau regret
//   jawaban monoton      -> binary search on answer

// ─── MAIN: menjalankan seluruh eksperimen ─────────────────

int main() {
    FASTIO;
    cout << "=== Eksperimen 1: greedy tukar uang ===\n";
    {
        mt19937 rng(1);
        int gagal = 0, total = 20000;
        vector<ll> contoh; ll contohT = 0; bool ada = false;
        for (int t = 0; t < total; t++) {
            int n = 2 + rng() % 3;
            set<ll> s{1};
            while ((int)s.size() < n) s.insert(2 + rng() % 12);
            vector<ll> koin(s.begin(), s.end());
            ll target = 1 + rng() % 30;
            if (koinGreedy(koin, target) != koinOptimal(koin, target)) {
                gagal++;
                if (!ada) { ada = true; contoh = koin; contohT = target; }
            }
        }
        cout << "  gagal " << gagal << "/" << total << " ("
             << fixed << setprecision(2) << (100.0 * gagal / total) << "%)\n";
        if (ada) {
            cout << "  contoh tandingan: koin {";
            for (size_t i = 0; i < contoh.size(); i++)
                cout << (i ? "," : "") << contoh[i];
            cout << "} target " << contohT
                 << " -> greedy " << koinGreedy(contoh, contohT)
                 << ", optimal " << koinOptimal(contoh, contohT) << '\n';
        }
    }

    cout << "\n=== Eksperimen 2: greedy rasio pada knapsack 0/1 ===\n";
    {
        mt19937 rng(2);
        int gagal = 0, total = 20000;
        for (int t = 0; t < total; t++) {
            int n = 1 + rng() % 8;
            vector<pair<ll,ll>> b(n);
            for (int i = 0; i < n; i++) b[i] = {(ll)(1 + rng() % 12), (ll)(1 + rng() % 20)};
            ll W = 1 + rng() % 25;
            if (knapGreedyRasio(b, W) != knapOptimal(b, W)) gagal++;
        }
        cout << "  gagal " << gagal << "/" << total << " ("
             << fixed << setprecision(2) << (100.0 * gagal / total) << "%)\n";
    }

    cout << "\n=== Eksperimen 3: pengaruh RENTANG generator ===\n";
    {
        // Soal: pilih 2 bilangan berbeda dengan jumlah terbesar.
        // Greedy SALAH: "ambil dua terbesar" tanpa memeriksa keunikan nilai.
        auto greedySalah = [](vector<ll> a) {
            sort(a.rbegin(), a.rend());
            return a[0] + a[1];
        };
        auto benar = [](vector<ll> a) {
            sort(a.rbegin(), a.rend());
            for (size_t i = 1; i < a.size(); i++)
                if (a[i] != a[0]) return a[0] + a[i];
            return -1LL;                      // semua sama -> tidak ada
        };
        for (ll batas : {3LL, 1000000LL}) {
            mt19937 rng(3);
            int gagal = 0, total = 20000;
            for (int t = 0; t < total; t++) {
                int n = 2 + rng() % 5;
                vector<ll> a(n);
                for (int i = 0; i < n; i++) a[i] = 1 + rng() % batas;
                if (greedySalah(a) != benar(a)) gagal++;
            }
            cout << "  rentang 1.." << setw(8) << batas
                 << " -> gagal " << gagal << "/" << total << " ("
                 << fixed << setprecision(2) << (100.0 * gagal / total) << "%)\n";
        }
        cout << "  (bug yang sama, generator berbeda -> kesimpulan berbeda)\n";
    }

    return 0;
}
