/*
============================================================
  Day 42 — REVIEW Array & String | Template Diagnosis
============================================================
  Template hari ini BUKAN kumpulan alat (itu ada di Day 41).
  Ini alat DIAGNOSIS: kerangka stress test dan checklist debug.

  PROTOKOL 60 DETIK PERTAMA
    1. Lihat n dan Q            -> kompleksitas target
    2. Ada elemen negatif?      -> menyingkirkan sliding window
    3. Ada batas panjang?       -> menyingkirkan Kadane
    4. "ada berapa" / "maksimum"?
    5. Update di tengah, atau semua di awal?
    6. Nilai 10^9 tapi kejadian sedikit? -> kompresi
    7. Posisi penting?  Kalau TIDAK, kamu boleh sort.

  DIAGNOSIS WA
    salah saat semua negatif       -> best = 0
    salah saat n = 1               -> loop mulai dari indeks salah
    meleset persis 1               -> off-by-one / tertutup vs setengah terbuka
    salah saat ada nilai kembar    -> < vs <= pada monotonic stack
    salah saat ada elemen 0        -> mengira 0 itu negatif
    salah hanya pada input negatif -> % memberi sisa negatif
    benar di sampel, salah di tes besar -> overflow int

  DIAGNOSIS TLE
    terasa O(n) tapi TLE     -> unordered_map kena anti-hash
    while di dalam for       -> cek: tiap elemen keluar berapa kali?
    loop bersarang           -> ada yang di-rebuild per iterasi?
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ════════════════════════════════════════════════════════
//  KERANGKA STRESS TEST
//  Alat paling berharga dari blok ini. Hafalkan bentuknya.
// ════════════════════════════════════════════════════════

// Solusimu yang mau diuji.
ll cepat(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) { cur = max(x, cur + x); best = max(best, cur); }
    return best;
}

// Versi lambat yang JELAS benar. Tulis ini dulu, jangan belakangan.
ll brute(const vector<ll>& a) {
    ll best = LLONG_MIN;
    for (size_t i = 0; i < a.size(); i++) {
        ll s = 0;
        for (size_t j = i; j < a.size(); j++) { s += a[j]; best = max(best, s); }
    }
    return best;
}

void stressTest() {
    mt19937 rng(12345);
    vector<ll> terkecil;

    for (int iter = 0; iter < 200000; iter++) {
        // KECIL. Counterexample 4 elemen bisa ditelusuri tangan; 200 tidak.
        int n = 1 + rng() % 8;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = (ll)(rng() % 21) - 10;

        if (cepat(a) != brute(a))
            if (terkecil.empty() || a.size() < terkecil.size()) terkecil = a;
    }

    if (terkecil.empty()) {
        cout << "lolos semua tes acak\n";
        cout << "CATATAN: stress test TIDAK bisa menemukan bug overflow,\n"
                "bug performa, atau bug batas n besar. Untuk itu baca constraint.\n";
    } else {
        cout << "counterexample terkecil: ";
        for (ll x : terkecil) cout << x << " ";
        cout << "\n  benar = " << brute(terkecil)
             << "\n  dapat = " << cepat(terkecil) << "\n";
    }
}

// ════════════════════════════════════════════════════════
//  CHECKLIST EDGE CASE UNIVERSAL
//  Jalankan tangan-tangan ini sebelum submit apa pun.
// ════════════════════════════════════════════════════════
/*
    n = 1
    semua elemen sama
    semua elemen negatif
    ada elemen bernilai 0
    k = 1  dan  k = n
    jawaban tidak ada        -> soal minta cetak apa?
    nilai maksimum di ujung kiri, lalu di ujung kanan
    input terbesar sesuai constraint  -> uji overflow dan waktu
*/

// ════════════════════════════════════════════════════════
//  DELAPAN INVARIANT — tulis dari ingatan, lalu cocokkan
// ════════════════════════════════════════════════════════
/*
    prefix sum       P[i] = jumlah i elemen pertama
    difference array d menyimpan SELISIH dengan tetangga kiri
    two pointers     untuk l sekarang, semua l' < l sudah pasti gagal
    window variabel  [l, r] = window TERPANJANG yang valid berakhir di r
    kadane           cur = jumlah maksimum subarray yang BERAKHIR di i
    monotonic stack  isi stack = kandidat yang BELUM tertutupi
    monotonic deque  isi deque = kandidat yang belum kadaluarsa & belum tertutupi
    prefix + map     cnt[v] = berapa kali nilai prefix v sudah muncul
*/

int main() {
    FASTIO;

    stressTest();          // ganti cepat() dan brute() sesuai soalmu

    return 0;
}
