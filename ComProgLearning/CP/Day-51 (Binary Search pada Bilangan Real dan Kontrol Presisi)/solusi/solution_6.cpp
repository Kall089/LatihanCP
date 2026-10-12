/*
============================================================
✅ Solution 6: Jarak Maksimum ke Pompa Bensin
============================================================
Approach: Binary search real pada jawaban + predikat greedy
Complexity: Time O(100 * N) | Space O(N)
Key Insight: Pola "minimalkan yang maksimum" hampir selalu berarti binary
             search on answer. Alih-alih mencari penempatan optimal secara
             langsung (sulit), kita menebak jawabannya D lalu bertanya
             "berapa pompa yang dibutuhkan agar setiap celah <= D?" --
             pertanyaan yang jauh lebih mudah dan bisa dijawab greedy.

📖 BERAPA POMPA UNTUK SATU CELAH:
   Celah sepanjang g harus dipecah menjadi potongan-potongan yang masing-
   masing <= D. Banyaknya potongan minimal adalah ceil(g / D), dan untuk
   membuat k potongan dibutuhkan k - 1 pompa penyekat.
   Jadi kebutuhan untuk celah itu adalah ceil(g / D) - 1.

   Total kebutuhan = jumlah atas seluruh celah. Predikatnya:
       butuh(D) <= K

   Monoton: semakin besar D, semakin longgar batasnya, semakin sedikit pompa
   yang dibutuhkan. Jadi kita mencari D TERKECIL yang kebutuhannya <= K.

⚠️ PEMBULATAN PADA ceil ADALAH JEBAKAN PRESISI YANG NYATA.
   Kalau g = 10 dan D = 5, secara matematis g/D = 2 tepat, sehingga
   ceil = 2 dan butuh 1 pompa. Tetapi dalam aritmetika double, 10.0/5.0
   bisa menghasilkan 2.0000000001, sehingga ceil menjadi 3 dan kita
   menghitung 2 pompa -- terlalu banyak. Akibatnya D = 5 dianggap tidak
   layak padahal seharusnya layak, dan jawabannya sedikit terlalu besar.

   Solusinya: tambahkan toleransi kecil sebelum ceil:
       (ll)ceil(g / D - 1e-9)
   Ini memaafkan kesalahan pembulatan ke atas tanpa mengubah kasus yang
   benar-benar butuh potongan tambahan.
   Sampel 2 (dua pompa di 0 dan 10, K = 1) memang menguji tepat kasus ini:
   jawabannya harus 5.000000, dan tanpa toleransi kamu bisa mendapat
   5.000001 atau lebih.

⚠️ BATAS: lo = 0, hi = celah terbesar yang ada di awal. Tidak mungkin
   jawabannya melebihi itu karena tanpa menambah pompa pun D sudah segitu.

⚠️ OVERFLOW PADA KEBUTUHAN: kalau D sangat kecil, ceil(g/D) meledak.
   Akumulasi dalam long long dan hentikan penjumlahan setelah melewati K
   -- pola yang sama dengan Day 49 Exercise 4 dan Exercise 2 hari ini.

VERIFIKASI SAMPEL 1 (posisi 1..10, K = 9):
   Ada 9 celah masing-masing sepanjang 1. Dengan D = 0.5, setiap celah butuh
   ceil(1/0.5) - 1 = 1 pompa, total 9 <= 9. Layak.
   Dengan D sedikit di bawah 0.5, setiap celah butuh 2 pompa, total 18 > 9.
   Tidak layak. Jadi jawabannya 0.5   ✓

🔄 ALTERNATIVE APPROACHES:
- Priority queue greedy: berulang kali pecah celah yang "terburuk" (celah
  dengan rasio g/(k+1) terbesar). O(K log N) -- untuk K = 10^6 masih lolos,
  dan hasilnya EKSAK tanpa masalah presisi. Sebenarnya ini pendekatan yang
  lebih baik untuk soal ini.
- Kalau posisinya bilangan bulat dan jawabannya dijamin bulat, binary search
  integer -- selalu lebih disukai kalau memungkinkan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll K;
    if (!(cin >> n >> K)) return 0;
    vector<double> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    vector<double> celah(n - 1);
    double maksCelah = 0;
    for (int i = 0; i + 1 < n; i++) {
        celah[i] = x[i + 1] - x[i];
        maksCelah = max(maksCelah, celah[i]);
    }

    auto butuhCukup = [&](double D) {
        ll total = 0;
        for (double g : celah) {
            total += (ll)ceil(g / D - 1e-9) - 1;   // toleransi: hindari ceil palsu
            if (total > K) return false;           // hentikan lebih awal
        }
        return total <= K;
    };

    double lo = 0, hi = maksCelah;
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (mid <= 0) { lo = mid; continue; }      // hindari pembagian nol
        if (butuhCukup(mid)) hi = mid;             // layak -> coba LEBIH KECIL
        else                 lo = mid;
    }

    printf("%.6f\n", hi);
    return 0;
}
