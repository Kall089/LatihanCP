/*
============================================================
  Day 76 — Greedy Sorting Multi-Kriteria | Template
============================================================
  PERTANYAAN INTI
    Ketika kriteria pertama SERI, apa yang menentukan urutan?

  Jawaban yang salah pada tie-break menghasilkan WA yang
  sangat sulit dilacak: kodenya benar pada hampir semua
  masukan acak, dan hanya gagal ketika ada nilai yang sama.

  KARENA ITU: generator stress test-mu HARUS memakai rentang
  nilai KECIL, agar seri sering terjadi.

  TIGA POLA UTAMA
    1. urut a menaik, tie-break b menurun   (mis. nested/dominasi)
    2. urut a menaik, tie-break b menaik    (mis. sapuan event)
    3. komparator turunan exchange argument (Day 71)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. TIE-BREAK: TIGA BENTUK PENULISAN ──────────────────

struct Item { ll a, b; int idx; };

// (a) komparator lambda eksplisit — paling jelas, paling aman
bool cmpNaikTurun(const Item& x, const Item& y) {
    if (x.a != y.a) return x.a < y.a;      // kriteria utama: a menaik
    return x.b > y.b;                      // tie-break     : b menurun
}

// (b) tuple — ringkas, tetapi HANYA untuk semua-menaik
//     Untuk membalik satu kolom, negasikan nilainya.
//     Hati-hati: negasi tidak aman untuk nilai = LLONG_MIN.
bool cmpTuple(const Item& x, const Item& y) {
    return make_tuple(x.a, -x.b) < make_tuple(y.a, -y.b);
}

// (c) pair<> di dalam vector — cara tercepat menulis saat kontes
//     vector<pair<ll,ll>> v;  v.push_back({a, -b});  sort(...);

// ─── 2. STRICT WEAK ORDERING ──────────────────────────────
//
//  Komparator WAJIB memenuhi: cmp(x, x) == false.
//  Memakai <= atau >= melanggar itu dan bisa membuat
//  std::sort MEMBACA DI LUAR BATAS (bukan sekadar salah urut).
//
//  ❌ return x.a <= y.a;
//  ✅ if (x.a != y.a) return x.a < y.a; return x.b < y.b;
//
//  Pemeriksa cepat: jalankan komparatormu pada elemen yang
//  IDENTIK. Kalau mengembalikan true, kodenya salah.

template <typename T, typename Cmp>
bool komparatorSah(const vector<T>& v, Cmp cmp) {
    int n = v.size();
    for (int i = 0; i < n; i++)
        if (cmp(v[i], v[i])) return false;              // irrefleksif
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cmp(v[i], v[j]) && cmp(v[j], v[i])) return false;  // asimetris
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (cmp(v[i], v[j]) && cmp(v[j], v[k]) && !cmp(v[i], v[k]))
                    return false;                       // transitif
    return true;
}

// ─── 3. STABILITAS ────────────────────────────────────────
//
//  std::sort        TIDAK stabil
//  std::stable_sort stabil, O(n log^2 n) tanpa memori tambahan
//                   atau O(n log n) dengan memori tambahan
//
//  Kalau urutan elemen seri PENTING, ada dua pilihan:
//    (a) pakai stable_sort
//    (b) tambahkan indeks asli sebagai tie-break TERAKHIR
//  Pilihan (b) lebih eksplisit dan tidak bergantung pada
//  implementasi pustaka. Disarankan.

// ─── 4. POLA: DOMINASI / PARETO FRONT ─────────────────────
// Titik i disebut PARETO-OPTIMAL kalau tidak ada j yang
// mendominasinya, yaitu tidak ada j dengan
//     a_j >= a_i  DAN  b_j >= b_i  DAN  minimal satu STRICT.
// Dua titik yang IDENTIK tidak saling mendominasi, sehingga
// keduanya Pareto-optimal.
//
// Di sinilah tie-break menentukan segalanya. Aturannya:
//   titik i Pareto-optimal
//   <=> b_i adalah maksimum di dalam kelompok ber-a SAMA
//       DAN b_i > maksimum b di antara semua titik ber-a LEBIH BESAR
//
// Perhatikan dua tanda pembanding yang BERBEDA: ">=" di dalam
// kelompok (sesama a sama boleh seri) dan ">" terhadap
// kelompok yang a-nya lebih besar (a sudah strict, jadi b seri
// pun sudah kalah).
// Menyamakan keduanya adalah bug klasik yang hanya muncul saat
// ada nilai berulang.

int hitungParetoOptimal(vector<Item> v) {
    int n = v.size();
    // a MENURUN; saat a seri, b MENURUN
    sort(v.begin(), v.end(), [](const Item& x, const Item& y) {
        if (x.a != y.a) return x.a > y.a;
        return x.b > y.b;
    });

    int hasil = 0;
    ll maxBdiKiri = LLONG_MIN;          // maks b dari kelompok ber-a LEBIH BESAR
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && v[j].a == v[i].a) j++;      // kelompok [i, j)
        ll maxBkelompok = v[i].b;                    // sudah terurut menurun
        for (int k = i; k < j; k++)
            if (v[k].b == maxBkelompok && v[k].b > maxBdiKiri) hasil++;
        maxBdiKiri = max(maxBdiKiri, maxBkelompok);
        i = j;
    }
    return hasil;
}

// ─── 5. POLA: SAPUAN EVENT DENGAN TIE-BREAK ───────────────
// Pada waktu yang SAMA, urutan pemrosesan menentukan jawaban.
//   setengah terbuka [l, r) -> proses SELESAI dulu
//   tertutup        [l, r]  -> proses MULAI dulu
// pair<> mengurutkan {t,-1} sebelum {t,+1} secara otomatis.

int tumpangTindihMaks(const vector<pair<ll, ll>>& iv, bool setengahTerbuka) {
    vector<pair<ll, int>> ev;
    for (auto& [l, r] : iv) {
        ev.push_back({l, +1});
        ev.push_back({r, setengahTerbuka ? -1 : +2});   // +2 diurut setelah +1
    }
    sort(ev.begin(), ev.end());
    int cur = 0, best = 0;
    for (auto& [t, d] : ev) {
        cur += (d == +2) ? -1 : d;
        best = max(best, cur);
    }
    return best;
}

// ─── 6. POLA: PENGURUTAN BERTINGKAT UNTUK PENJADWALAN ─────
// Contoh: n pekerjaan (a, b). Kerjakan bagian a lebih dulu
// (satu mesin), lalu bagian b (paralel tak terbatas).
// Minimalkan waktu selesai terakhir.
// Jawaban: urut b MENURUN. (Buktinya exchange argument.)

ll penjadwalanDuaTahap(vector<pair<ll, ll>> job) {
    sort(job.begin(), job.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        return x.second > y.second;            // b menurun
    });
    ll t = 0, best = 0;
    for (auto& [a, b] : job) {
        t += a;                                // selesai tahap pertama
        best = max(best, t + b);               // tahap kedua paralel
    }
    return best;
}

// ─── 7. JEBAKAN ───────────────────────────────────────────
//
//  a) Lupa tie-break sama sekali. Lolos hampir semua masukan
//     acak berentang besar, gagal saat ada nilai sama.
//     -> generator stress test HARUS berentang kecil.
//
//  b) Memakai <= di dalam komparator. Melanggar strict weak
//     ordering, bisa crash.
//
//  c) Menegasikan nilai untuk membalik urutan pada tuple,
//     padahal nilainya bisa LLONG_MIN (negasinya meluap).
//
//  d) Mengandalkan std::sort untuk stabilitas. Tidak stabil.
//
//  e) Membandingkan rasio dengan pembagian (Day 74).

// ─── MAIN: demo + stress test ─────────────────────────────

int main() {
    FASTIO;

    vector<Item> v = {{1,5,0},{2,3,1},{1,2,2},{3,4,3},{2,3,4}};
    cout << "pareto      : " << hitungParetoOptimal(v) << " (harusnya 2)\n";

    vector<pair<ll,ll>> iv = {{1,5},{5,9},{2,3}};
    cout << "tindih [l,r) : " << tumpangTindihMaks(iv, true)  << " (harusnya 2)\n";
    cout << "tindih [l,r]  : " << tumpangTindihMaks(iv, false) << " (harusnya 2)\n";

    vector<pair<ll,ll>> job = {{1,3},{2,1},{3,2}};
    cout << "dua tahap   : " << penjadwalanDuaTahap(job) << " (harusnya 7)\n";

    // Uji bahwa komparator kita memenuhi strict weak ordering
    // pada data yang PENUH SERI — inilah yang menangkap bug <=.
    mt19937 rng(76);
    bool sah = true;
    for (int t = 0; t < 200 && sah; t++) {
        int n = 1 + rng() % 6;
        vector<Item> w(n);
        for (int i = 0; i < n; i++) w[i] = {(ll)(rng() % 2), (ll)(rng() % 2), i};
        if (!komparatorSah(w, cmpNaikTurun)) sah = false;
    }
    cout << "komparator sah : " << (sah ? "200 kasus OK" : "MELANGGAR") << '\n';

    // Verifikasi Pareto terhadap brute force O(n^2).
    // Nilai sengaja DIBATASI 0..3 agar seri sering muncul —
    // dengan rentang besar, bug tie-break tidak akan pernah
    // tertangkap.
    bool ok = true;
    for (int t = 0; t < 20000 && ok; t++) {
        int n = 1 + rng() % 8;
        vector<Item> w(n);
        for (int i = 0; i < n; i++) w[i] = {(ll)(rng() % 4), (ll)(rng() % 4), i};
        int brute = 0;
        for (int i = 0; i < n; i++) {
            bool dom = false;
            for (int j = 0; j < n && !dom; j++) {
                if (j == i) continue;
                if (w[j].a >= w[i].a && w[j].b >= w[i].b &&
                    (w[j].a > w[i].a || w[j].b > w[i].b)) dom = true;
            }
            if (!dom) brute++;
        }
        if (hitungParetoOptimal(w) != brute) ok = false;
    }
    cout << "stress pareto : " << (ok ? "20000 kasus OK" : "GAGAL") << '\n';

    return 0;
}
