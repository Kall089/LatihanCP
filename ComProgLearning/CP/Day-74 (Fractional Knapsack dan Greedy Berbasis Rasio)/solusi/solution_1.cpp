/*
============================================================
✅ SOLUSI Exercise 1: Perampokan Gudang Emas
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Karena barang boleh dipotong, setiap kilogram ruang di tas bisa
dinilai secara terpisah. Belanjakan setiap kilogram pada karung
dengan NILAI PER KILOGRAM tertinggi.
Urutkan menurut rasio v/w MENURUN, ambil utuh selama muat,
potong yang terakhir.

── BUKTI (exchange argument) ───────────────────────────────
Klaim: ada solusi optimal yang mengambil karung berasio
tertinggi sebanyak-banyaknya.

Sebut karung itu x. Ambil solusi optimal O. Andaikan O
mengambil x kurang dari maksimum yang mungkin. Kapasitas pasti
terpakai penuh (kalau tidak, tambahkan x dan nilainya naik —
kontradiksi), jadi ada karung lain y dengan porsi > 0 dan
rasio v_y/w_y <= v_x/w_x.
Kurangi y sebanyak berat d, tambahkan x sebanyak berat d.
  perubahan nilai = d*(v_x/w_x) - d*(v_y/w_y) >= 0
Nilainya tidak turun. Ulangi sampai x terambil maksimal. ∎

Perhatikan bahwa langkah "kurangi sebanyak berat d" HANYA sah
karena barang boleh dipotong. Inilah yang hilang pada 0/1.

── MEMBANDINGKAN RASIO TANPA PEMBAGIAN ─────────────────────
    v_a/w_a > v_b/w_b   <=>   v_a * w_b > v_b * w_a   (w > 0)

Kenapa penting: double punya 53 bit mantissa. Dengan v dan w
sampai 10^9, dua rasio yang berbeda sangat tipis bisa terbaca
sama atau bahkan tertukar. Komparator yang tidak konsisten
melanggar strict weak ordering dan bisa membuat std::sort
membaca di luar batas — bukan sekadar jawaban salah, tetapi
crash.

Perkalian v*w mencapai 10^18, masih muat di long long
(9.2*10^18) tetapi nyaris. __int128 menghilangkan
kekhawatiran itu tanpa biaya berarti.

── JEBAKAN ─────────────────────────────────────────────────
1. Membandingkan rasio dengan double.
2. Kapasitas lebih besar dari total berat (sampel 2): kode
   harus berhenti tanpa mencoba memotong. Penjaga
   'if (sisa == 0) break;' menanganinya, dan cabang pemotongan
   hanya dijalankan saat w[i] > sisa.
3. Akumulasi nilai bisa mencapai 2*10^5 * 10^9 = 2*10^14.
   Muat di double (presisi ~15-16 digit signifikan) tetapi
   sudah di batas. Kalau soal minta presisi tinggi pada nilai
   sebesar ini, pertimbangkan long double.
4. Lupa fixed << setprecision(6).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll W;
    if (!(cin >> n >> W)) return 0;
    vector<ll> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return (__int128)v[a] * w[b] > (__int128)v[b] * w[a];   // rasio menurun
    });

    long double total = 0;
    ll sisa = W;
    for (int i : ord) {
        if (sisa == 0) break;
        if (w[i] <= sisa) {                       // muat utuh
            total += v[i];
            sisa  -= w[i];
        } else {                                  // potong sisanya
            total += (long double)v[i] * sisa / w[i];
            sisa = 0;
        }
    }

    cout << fixed << setprecision(6) << (double)total << '\n';
    return 0;
}
