/*
============================================================
✅ Kunci Drill 3 — Turunkan Variasinya Sendiri
============================================================
Setiap solusi didahului TIGA BARIS TURUNAN. Itu bagian yang penting.
Kodenya cuma konsekuensi.

  g++ -std=c++17 -O2 -o kunci3 drill_3_kunci.cpp && ./kunci3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 4;   // sentinel aman untuk dijumlahkan

ll kadaneMax(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) { cur = max(x, cur + x); best = max(best, cur); }
    return best;
}

// ════════════════════════════════════════════════════════
// A — Minimum subarray
//   dp[i]   = jumlah MINIMUM subarray yang berakhir di i
//   pilihan = mulai baru di a[i], atau lanjutkan dp[i-1]
//   boleh   = argumen sama persis dengan Kadane, cuma max ditukar min
//
//   Tapi cara terbaik adalah TIDAK menulis kode baru sama sekali:
//     min sum subarray a = -( max sum subarray (-a) )
//   Negasi membalik urutan, jadi "terkecil" jadi "terbesar".
//   Satu implementasi, satu tempat bug. Ini kebiasaan yang layak dibentuk.
// ════════════════════════════════════════════════════════
ll soalA_minSubarray(const vector<ll>& a) {
    vector<ll> b(a.size());
    for (size_t i = 0; i < a.size(); i++) b[i] = -a[i];
    return -kadaneMax(b);
}

// ════════════════════════════════════════════════════════
// B — Melingkar
//   Ruang jawaban terbelah dua, tidak ada bentuk ketiga:
//     tidak membungkus -> subarray biasa            -> kadaneMax
//     membungkus       -> yang TIDAK dipakai adalah satu subarray di tengah
//                      -> nilainya total - (subarray tengah)
//                      -> maksimalkan dengan meminimalkan yang tengah
//   PENJAGA: kalau semua negatif, subarray tengah = seluruh array,
//   sehingga total - min = 0 = subarray KOSONG. Tidak diizinkan.
//   Deteksi paling bersih: kalau kadaneMax < 0, semua elemen negatif.
// ════════════════════════════════════════════════════════
ll soalB_melingkar(const vector<ll>& a) {
    ll mx = kadaneMax(a);
    if (mx < 0) return mx;                       // penjaga semua-negatif
    ll total = accumulate(a.begin(), a.end(), 0LL);
    return max(mx, total - soalA_minSubarray(a));
}

// ════════════════════════════════════════════════════════
// C — Boleh hapus paling banyak satu elemen
//   dp0[i] = max sum berakhir di i, BELUM memakai jatah hapus
//   dp1[i] = max sum berakhir di i, jatah hapus SUDAH terpakai
//   pilihan di i:
//     dp0: mulai baru (a[i])              | lanjut (dp0[i-1] + a[i])
//     dp1: hapus a[i] sekarang (dp0[i-1]) | sudah pernah hapus, ambil a[i] (dp1[i-1]+a[i])
//   boleh ambil optimal dari i-1: a[i] tetap konstanta tambahan yang sama
//   untuk semua kandidat di dalam tiap state -> argumen Kadane utuh per-state.
//
//   Perhatikan: dp1[i] = dp0[i-1] otomatis menjamin hasilnya tidak kosong,
//   karena dp0[i-1] sendiri sudah berisi minimal satu elemen.
// ════════════════════════════════════════════════════════
ll soalC_hapusSatu(const vector<ll>& a) {
    ll dp0 = a[0], dp1 = NEG, best = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        ll ndp1 = max(dp1 + a[i], dp0);          // pakai dp0 LAMA
        ll ndp0 = max(a[i], dp0 + a[i]);
        dp0 = ndp0; dp1 = ndp1;
        best = max(best, max(dp0, dp1));
    }
    return best;
}

// ════════════════════════════════════════════════════════
// D — Panjang minimal k
//   Kadane murni GAGAL di sini: buktinya runtuh. "Subarray terbaik yang
//   berakhir di i-1" belum tentu bisa dipakai, karena panjangnya ikut
//   menentukan kelayakan -> state-nya kurang.
//
//   Yang saya kunci     = ujung kanan r
//   Yang saya minimalkan= P[l] dengan syarat l <= r - k
//   sum(l..r-1) = P[r] - P[l];  maksimalkan -> minimalkan P[l]
//   Trik: jaga minPre yang TERTINGGAL k langkah. Setiap kali r maju,
//   satu prefix baru menjadi "layak" dan boleh masuk ke minPre.
// ════════════════════════════════════════════════════════
ll soalD_panjangMinimalK(const vector<ll>& a, int k) {
    int n = a.size();
    if (k > n) return NEG;
    vector<ll> P(n + 1, 0);
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + a[i];

    ll best = LLONG_MIN, minPre = LLONG_MAX;
    for (int r = k; r <= n; r++) {
        minPre = min(minPre, P[r - k]);          // baru sekarang layak
        best = max(best, P[r] - minPre);
    }
    return best;
}

// ════════════════════════════════════════════════════════
// E — Dua subarray tidak bertumpang tindih
//   Yang saya kunci = TITIK POTONG. Ada tepat satu posisi i sehingga
//   segmen pertama seluruhnya di a[0..i] dan segmen kedua di a[i+1..n-1].
//   Sekali titik potong dikunci, kedua sisi jadi masalah Kadane biasa
//   yang saling bebas.
//     kiri[i]  = max subarray di dalam a[0..i]      (prefix)
//     kanan[i] = max subarray di dalam a[i..n-1]    (suffix)
//     jawaban  = max atas i dari kiri[i] + kanan[i+1]
//   Perhatikan bedanya kiri[] dengan dp[] Kadane: kiri[] TIDAK wajib
//   berakhir di i, ia maksimum berjalan. Salah membedakan keduanya
//   adalah bug nomor satu di soal ini.
// ════════════════════════════════════════════════════════
ll soalE_duaSubarray(const vector<ll>& a) {
    int n = a.size();
    if (n < 2) return NEG;
    vector<ll> kiri(n), kanan(n);

    ll cur = NEG, best = NEG;
    for (int i = 0; i < n; i++) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
        kiri[i] = best;
    }
    cur = NEG; best = NEG;
    for (int i = n - 1; i >= 0; i--) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
        kanan[i] = best;
    }

    ll ans = NEG;
    for (int i = 0; i + 1 < n; i++) ans = max(ans, kiri[i] + kanan[i + 1]);
    return ans;
}

// ════════════════════════════════════════════════════════
//                    VERIFIKASI (brute force)
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
        best = max(best, s);
        if (j > i) { ll mn = LLONG_MAX;
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

int main() {
    mt19937 rng(2024);
    int gA = 0, gB = 0, gC = 0, gD = 0, gE = 0, total = 5000;
    for (int it = 0; it < total; it++) {
        int n = 1 + rng() % 7;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = (ll)(rng() % 21) - 10;
        int k = 1 + rng() % n;
        gA += soalA_minSubarray(a)      != bfMin(a);
        gB += soalB_melingkar(a)        != bfMelingkar(a);
        gC += soalC_hapusSatu(a)        != bfHapusSatu(a);
        gD += soalD_panjangMinimalK(a,k)!= bfPanjangMinK(a, k);
        if (n >= 2) gE += soalE_duaSubarray(a) != bfDuaSubarray(a);
    }
    cout << "A minimum    : " << (gA ? "GAGAL" : "OK") << "\n"
         << "B melingkar  : " << (gB ? "GAGAL" : "OK") << "\n"
         << "C hapus satu : " << (gC ? "GAGAL" : "OK") << "\n"
         << "D panjang>=k : " << (gD ? "GAGAL" : "OK") << "\n"
         << "E dua segmen : " << (gE ? "GAGAL" : "OK") << "\n";
    return 0;
}
