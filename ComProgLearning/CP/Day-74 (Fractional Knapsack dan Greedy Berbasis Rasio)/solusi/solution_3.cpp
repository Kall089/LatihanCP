/*
============================================================
✅ SOLUSI Exercise 3: Mencampur Bahan Bakar
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── IDE UTAMA ────────────────────────────────────────────────
Tujuannya MEMINIMALKAN biaya, jadi arah greedy-nya dibalik:
urutkan menurut harga per liter MENAIK, beli sebanyak mungkin
dari yang termurah, lalu lanjut ke berikutnya.

── KENAPA ARAHNYA DIBALIK ──────────────────────────────────
Exercise 1 memaksimalkan nilai dengan kapasitas terbatas, jadi
setiap kilogram dibelanjakan pada nilai per kilogram TERTINGGI.
Di sini kita memenuhi kebutuhan tetap L liter dengan biaya
terkecil, jadi setiap liter harus dibeli dengan harga per liter
TERENDAH.
Buktinya cerminan langsung dari Exercise 1: kalau solusi optimal
membeli dari pemasok mahal padahal masih ada kuota murah yang
belum terpakai, tukar sebagian — biayanya turun.

── SOAL SUDAH MEMBERI RASIONYA ─────────────────────────────
Perbedaan halus tapi penting: di Exercise 1 kamu harus MENGHITUNG
rasio v/w sendiri, dan karena itu perlu berhati-hati dengan
pembagian. Di sini harga sudah dinyatakan per liter, sehingga
pengurutannya cukup membandingkan c[i] secara langsung — tidak
ada pembagian, tidak ada risiko presisi.

Kebiasaan yang baik: setelah membaca soal, tanyakan "apakah
rasio yang saya butuhkan sudah diberikan?" sebelum menulis
komparator yang rumit.

── OVERFLOW ────────────────────────────────────────────────
a[i] sampai 10^9 dan c[i] sampai 10^9, jadi biaya satu pemasok
saja bisa mencapai 10^18. Total bisa melampaui long long, dan
karena itu akumulasinya memakai long double.
Kalau soal meminta jawaban EKSAK, kumpulkan hasilnya sebagai
__int128 (semua pembelian di sini berupa bilangan bulat liter,
sehingga totalnya selalu bilangan bulat).

── KASUS TIDAK MUNCUKUPI ───────────────────────────────────
Setelah semua pemasok habis, kalau masih ada sisa kebutuhan,
cetak -1. Memeriksa total pasokan di awal juga sah dan mungkin
lebih jelas.

── JEBAKAN ─────────────────────────────────────────────────
1. Mengurutkan menurun (menyalin Exercise 1 tanpa berpikir).
2. Lupa kasus -1.
3. Memakai double untuk akumulasi 10^18.
4. Menyangka jawabannya selalu pecahan — di sini justru selalu
   bilangan bulat karena harga per liter bilangan bulat.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll L;
    if (!(cin >> n >> L)) return 0;
    vector<pair<ll, ll>> p(n);                    // (harga per liter, kuota)
    for (int i = 0; i < n; i++) {
        ll a, c;
        cin >> a >> c;
        p[i] = {c, a};
    }

    sort(p.begin(), p.end());                     // termurah dulu

    long double total = 0;
    ll sisa = L;
    for (auto& [harga, kuota] : p) {
        if (sisa == 0) break;
        ll beli = min(kuota, sisa);
        total += (long double)beli * harga;
        sisa  -= beli;
    }

    if (sisa > 0) cout << -1 << '\n';             // pasokan tidak cukup
    else cout << fixed << setprecision(6) << (double)total << '\n';

    return 0;
}
