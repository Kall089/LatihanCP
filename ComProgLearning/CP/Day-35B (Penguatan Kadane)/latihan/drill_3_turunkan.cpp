/*
============================================================
🔧 Drill 3: Turunkan Variasinya Sendiri
============================================================
Day: 35B | Target: 60 menit
Tujuan: berhenti menghafal varian, mulai menurunkannya.

CARA MAIN
  Isi setiap fungsi ber-TODO. Untuk MASING-MASING, sebelum menulis kode,
  jawab dulu di komentar tepat di atasnya:

      // dp[i] saya = ...
      // pilihan yang ada di i = ...
      // kenapa boleh ambil yang optimal dari i-1 = ...

  Kalau tiga baris itu tidak bisa kamu isi, kodenya pasti akan asal tebak.

  Semua fungsi punya pembanding brute force. Jalankan:
    g++ -std=c++17 -O2 -o drill_3 drill_3_turunkan.cpp && ./drill_3

  Kunci: solusi/drill_3_kunci.cpp — buka HANYA setelah stress test mu hijau
  atau setelah kamu benar-benar mentok 20 menit.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ════════════════════════════════════════════════════════
// SOAL A — Subarray dengan jumlah MINIMUM (tidak boleh kosong)
//   Jangan tulis Kadane baru dari nol. Pakai yang sudah ada.
// ════════════════════════════════════════════════════════
ll kadaneMax(const vector<ll>& a) {          // sudah benar, silakan pakai
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) { cur = max(x, cur + x); best = max(best, cur); }
    return best;
}

// dp[i] saya = ...
ll soalA_minSubarray(const vector<ll>& a) {
    // TODO
    (void)a;
    return 0;
}

// ════════════════════════════════════════════════════════
// SOAL B — Melingkar. Subarray boleh membungkus lewat ujung.
//   Tidak boleh kosong. Ingat penjaga kasus semua-negatif.
// ════════════════════════════════════════════════════════
// dp[i] saya = ...
ll soalB_melingkar(const vector<ll>& a) {
    // TODO
    (void)a;
    return 0;
}

// ════════════════════════════════════════════════════════
// SOAL C — Boleh membuang PALING BANYAK SATU elemen dari dalam subarray.
//   Hasilnya tetap harus berisi minimal satu elemen.
//   Contoh: [1, -2, 3] -> buang -2 -> 4
// ════════════════════════════════════════════════════════
// dp0[i] = ...   dp1[i] = ...
ll soalC_hapusSatu(const vector<ll>& a) {
    // TODO
    (void)a;
    return 0;
}

// ════════════════════════════════════════════════════════
// SOAL D — Jumlah maksimum subarray dengan panjang MINIMAL k.
//   Ini BUKAN Kadane murni. Petunjuk: prefix sum, dan prefix minimum
//   yang tertinggal k langkah di belakang.
// ════════════════════════════════════════════════════════
// yang saya kunci = ...   yang saya minimalkan = ...
ll soalD_panjangMinimalK(const vector<ll>& a, int k) {
    // TODO
    (void)a; (void)k;
    return 0;
}

// ════════════════════════════════════════════════════════
// SOAL E — Dua subarray TIDAK BERTUMPANG TINDIH, total maksimum.
//   Keduanya tidak boleh kosong. Petunjuk: pikirkan "titik potong".
// ════════════════════════════════════════════════════════
// yang saya kunci = ...
ll soalE_duaSubarray(const vector<ll>& a) {
    // TODO
    (void)a;
    return 0;
}

// ════════════════════════════════════════════════════════
//                     BRUTE FORCE PEMBANDING
// ════════════════════════════════════════════════════════
ll bfMin(const vector<ll>& a) {
    ll best = LLONG_MAX;
    for (size_t i = 0; i < a.size(); i++) { ll s = 0;
        for (size_t j = i; j < a.size(); j++) { s += a[j]; best = min(best, s); } }
    return best;
}
ll bfMelingkar(const vector<ll>& a) {
    int n = a.size(); ll best = LLONG_MIN;
    for (int i = 0; i < n; i++) { ll s = 0;
        for (int len = 1; len <= n; len++) { s += a[(i + len - 1) % n]; best = max(best, s); } }
    return best;
}
ll bfHapusSatu(const vector<ll>& a) {
    int n = a.size(); ll best = LLONG_MIN;
    for (int i = 0; i < n; i++) for (int j = i; j < n; j++) {
        ll s = 0; for (int t = i; t <= j; t++) s += a[t];
        best = max(best, s);                       // tanpa membuang
        if (j > i) { ll mn = LLONG_MAX;            // buang satu elemen
            for (int t = i; t <= j; t++) mn = min(mn, a[t]);
            best = max(best, s - mn); } }
    return best;
}
ll bfPanjangMinK(const vector<ll>& a, int k) {
    int n = a.size(); ll best = LLONG_MIN;
    for (int i = 0; i < n; i++) { ll s = 0;
        for (int j = i; j < n; j++) { s += a[j];
            if (j - i + 1 >= k) best = max(best, s); } }
    return best;
}
ll bfDuaSubarray(const vector<ll>& a) {
    int n = a.size(); ll best = LLONG_MIN;
    for (int i = 0; i < n; i++) for (int j = i; j < n; j++)
        for (int p = j + 1; p < n; p++) for (int q = p; q < n; q++) {
            ll s = 0;
            for (int t = i; t <= j; t++) s += a[t];
            for (int t = p; t <= q; t++) s += a[t];
            best = max(best, s); }
    return best;
}

// ════════════════════════════════════════════════════════
int main() {
    mt19937 rng(2024);
    int gagalA = 0, gagalB = 0, gagalC = 0, gagalD = 0, gagalE = 0, total = 3000;
    vector<ll> ceA, ceB, ceC, ceD, ceE; int ceK = 0;

    for (int it = 0; it < total; it++) {
        int n = 1 + rng() % 7;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = (ll)(rng() % 21) - 10;
        int k = 1 + rng() % n;

        if (soalA_minSubarray(a)     != bfMin(a))          { if (!gagalA++) ceA = a; }
        if (soalB_melingkar(a)       != bfMelingkar(a))    { if (!gagalB++) ceB = a; }
        if (soalC_hapusSatu(a)       != bfHapusSatu(a))    { if (!gagalC++) ceC = a; }
        if (soalD_panjangMinimalK(a,k)!= bfPanjangMinK(a,k)){ if (!gagalD++){ceD=a;ceK=k;} }
        if (n >= 2 && soalE_duaSubarray(a) != bfDuaSubarray(a)) { if (!gagalE++) ceE = a; }
    }

    auto lapor = [&](const char* nama, int gagal, const vector<ll>& ce, int kk) {
        cout << (gagal ? "❌ " : "✅ ") << nama << " : ";
        if (!gagal) { cout << "lolos " << total << " tes acak\n"; return; }
        cout << gagal << " gagal. Contoh: a = [";
        for (size_t i = 0; i < ce.size(); i++) cout << ce[i] << (i + 1 < ce.size() ? ", " : "");
        cout << "]";
        if (kk) cout << "  k = " << kk;
        cout << "\n";
    };

    lapor("A minimum   ", gagalA, ceA, 0);
    lapor("B melingkar ", gagalB, ceB, 0);
    lapor("C hapus satu", gagalC, ceC, 0);
    lapor("D panjang>=k", gagalD, ceD, ceK);
    lapor("E dua segmen", gagalE, ceE, 0);
    return 0;
}
