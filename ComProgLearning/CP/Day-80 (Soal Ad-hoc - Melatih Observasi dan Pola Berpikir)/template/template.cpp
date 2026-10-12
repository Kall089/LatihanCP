/*
============================================================
  Day 80 — Soal Ad-hoc | Template
============================================================
  SOAL AD-HOC = soal yang tidak memakai algoritma standar.
  Kuncinya satu PENGAMATAN, dan setelah pengamatan itu
  ditemukan, kodenya biasanya kurang dari 20 baris.

  TUJUH PERTANYAAN PEMBUKA
    1. Apa yang TIDAK BERUBAH? (invarian — Day 82)
    2. Apa jawabannya untuk n = 1, 2, 3? (cari pola)
    3. Apa BATAS BAWAH dan BATAS ATAS jawabannya?
    4. Bisakah soal dibalik? (dari akhir ke awal)
    5. Apakah ada besaran yang MONOTON?
    6. Apa kasus EKSTREM-nya? (semua sama, semua beda)
    7. Bisakah aku hitung jawabannya untuk n kecil lalu
       cari polanya di OEIS atau dengan tangan?

  ALAT UTAMA HARI INI: program pencari pola.
  Hitung jawaban untuk n kecil secara brute force, cetak
  barisannya, lalu tebak rumusnya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PENCARI POLA: cetak jawaban untuk n kecil ─────────
// Ini alat paling berharga untuk soal ad-hoc. Pakai brute
// force untuk n = 1..12, cetak barisannya, lalu cari polanya.

template <typename F>
void cetakBarisan(F brute, int sampai, const string& nama) {
    cout << nama << ": ";
    vector<ll> v;
    for (int n = 1; n <= sampai; n++) {
        ll x = brute(n);
        v.push_back(x);
        cout << x << ' ';
    }
    cout << "\n  selisih pertama : ";
    for (size_t i = 1; i < v.size(); i++) cout << v[i] - v[i-1] << ' ';
    cout << "\n  selisih kedua   : ";
    for (size_t i = 2; i < v.size(); i++)
        cout << (v[i] - v[i-1]) - (v[i-1] - v[i-2]) << ' ';
    cout << "\n  rasio           : ";
    cout << fixed << setprecision(3);
    for (size_t i = 1; i < v.size(); i++)
        if (v[i-1] != 0) cout << (double)v[i] / v[i-1] << ' ';
    cout << "\n";
}
// Selisih pertama tetap  -> rumus LINEAR
// Selisih kedua tetap    -> rumus KUADRAT
// Rasio tetap            -> rumus EKSPONENSIAL

// ─── 2. POLA: BATAS BAWAH BERTEMU KONSTRUKSI ──────────────
// Banyak soal ad-hoc berbentuk "berapa langkah minimum".
// Strateginya SELALU dua bagian:
//   (a) buktikan tidak mungkin kurang dari B  (batas bawah)
//   (b) tunjukkan cara mencapai tepat B       (konstruksi)
// Menjawab hanya satu bagian bukan solusi.

// Contoh: membalik tanda elemen agar jumlahnya positif.
// Batas bawah: setiap operasi mengubah jumlah paling banyak
// 2*|a_i|, jadi butuh minimal ceil(kekurangan / 2*maks).

// ─── 3. POLA: PIKIRKAN DARI BELAKANG ──────────────────────
// Kalau operasi maju sulit dianalisis, coba balik.
// Contoh klasik: "berapa cara mencapai (a,b) dari (1,1)
// dengan operasi (x,y) -> (x+y,y) atau (x,y+x)?"
// Dari belakang, operasinya menjadi PENGURANGAN dan langsung
// terlihat sebagai algoritma Euclid.

ll langkahEuclidMundur(ll a, ll b) {
    ll langkah = 0;
    while (a > 1 || b > 1) {
        if (a == b) return -1;                   // macet
        if (a > b) { langkah += (a - 1) / b; a -= b * ((a - 1) / b); }
        else       { langkah += (b - 1) / a; b -= a * ((b - 1) / a); }
    }
    return langkah;
}

// ─── 4. POLA: ARGUMEN PENUKARAN / PENGGABUNGAN ────────────
// "Berapa operasi minimum untuk membuat semua sama?"
// Sering jawabannya adalah jumlah selisih terhadap MEDIAN
// (untuk jarak absolut) atau terhadap RATA-RATA (untuk
// jumlah tetap).

ll biayaKeMedian(vector<ll> a) {
    sort(a.begin(), a.end());
    ll m = a[a.size() / 2], s = 0;
    for (ll x : a) s += llabs(x - m);
    return s;
}

// ─── 5. POLA: HITUNG SUMBANGAN, BUKAN OBJEK ───────────────
// "Jumlahkan f(subarray) atas SEMUA subarray" biasanya
// diselesaikan dengan membalik urutan penjumlahan: untuk tiap
// ELEMEN, hitung berapa subarray yang memuatnya.
// Elemen ke-i (0-indexed) muncul di (i+1)*(n-i) subarray.

ll jumlahSeluruhSubarray(const vector<ll>& a) {
    ll n = a.size(), total = 0;
    for (ll i = 0; i < n; i++) total += a[i] * (i + 1) * (n - i);
    return total;
}

// ─── 6. POLA: PARITAS SEBAGAI PENYARING CEPAT ─────────────
// Sebelum mencari konstruksi, periksa apakah paritasnya
// memungkinkan. Sering separuh kasus langsung terjawab
// "tidak mungkin". Dibahas penuh di Day 82.

// ─── 7. BRUTE FORCE UNTUK MENCARI POLA ────────────────────
// Contoh: banyaknya cara menyusun n bilangan 1..n sehingga
// tidak ada yang menempati posisi aslinya (derangement).

ll bruteDerangement(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    ll hit = 0;
    do {
        bool ok = true;
        for (int i = 0; i < n; i++) if (p[i] == i) { ok = false; break; }
        if (ok) hit++;
    } while (next_permutation(p.begin(), p.end()));
    return hit;
}

// ─── 8. JEBAKAN ───────────────────────────────────────────
//
//  a) Langsung menulis kode sebelum menemukan pengamatannya.
//     Soal ad-hoc yang benar biasanya SANGAT pendek. Kalau
//     kodemu panjang, kamu belum menemukan pengamatannya.
//
//  b) Hanya membuktikan batas bawah, atau hanya membuat
//     konstruksi. Soal "minimum" butuh KEDUANYA.
//
//  c) Menebak pola dari terlalu sedikit suku. Hitung minimal
//     8-10 suku sebelum menebak.
//
//  d) Lupa memeriksa n = 1 dan n = 2. Rumus yang benar untuk
//     n besar sering gagal di situ.
//
//  e) Tidak memverifikasi rumus tebakan terhadap brute force
//     untuk n yang lebih besar dari yang dipakai menebak.

// ─── MAIN: demo alat pencari pola ─────────────────────────

int main() {
    FASTIO;

    cout << "=== Alat pencari pola ===\n\n";

    cetakBarisan([](int n) { return (ll)n * (n + 1) / 2; }, 10, "segitiga  ");
    cout << "  -> selisih kedua tetap = rumus KUADRAT\n\n";

    cetakBarisan([](int n) { return (ll)1 << n; }, 10, "pangkat 2 ");
    cout << "  -> rasio tetap = rumus EKSPONENSIAL\n\n";

    cetakBarisan(bruteDerangement, 8, "derangement");
    cout << "  -> selisih tidak tetap, rasio mendekati n\n";
    cout << "     dugaan: D(n) = n * D(n-1) + (-1)^n\n";

    // verifikasi dugaan terhadap brute force
    bool ok = true;
    ll d = 1;                                    // D(0) = 1
    for (int n = 1; n <= 8; n++) {
        d = (ll)n * d + ((n % 2 == 0) ? 1 : -1);
        if (d != bruteDerangement(n)) ok = false;
    }
    cout << "     verifikasi rumus: " << (ok ? "COCOK untuk n = 1..8" : "GAGAL") << "\n\n";

    cout << "=== Pola lain ===\n";
    vector<ll> a = {1, 2, 3};
    cout << "jumlah seluruh subarray {1,2,3} : "
         << jumlahSeluruhSubarray(a) << " (harusnya 20)\n";
    cout << "biaya ke median {1,5,7,10}      : "
         << biayaKeMedian({1, 5, 7, 10}) << " (harusnya 11)\n";
    cout << "langkah Euclid mundur (5,3)     : "
         << langkahEuclidMundur(5, 3) << " (harusnya 3)\n";

    return 0;
}
