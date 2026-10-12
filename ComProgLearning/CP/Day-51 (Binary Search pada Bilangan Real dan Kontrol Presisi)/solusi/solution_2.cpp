/*
============================================================
✅ Solution 2: Membagi Tali
============================================================
Approach: Binary search real, varian "nilai TERBESAR yang layak"
Complexity: Time O(N * 100) | Space O(N)
Key Insight: Predikat di sini MENURUN terhadap x: semakin panjang potongan
             yang diminta, semakin sedikit potongan yang bisa dihasilkan.
             Polanya menjadi true...true false...false, sehingga kita mencari
             nilai TERBESAR yang masih true -- kebalikan dari Exercise 1.

📖 PENJELASAN PENDEKATAN:
1. bisa(x) = jumlah floor(panjang[i] / x) >= K.
2. Cari x terbesar yang bisa(x) bernilai true:
       if (bisa(mid)) lo = mid;      <- mid layak, coba yang LEBIH BESAR
       else           hi = mid;
   Perhatikan arahnya terbalik dari Exercise 1.
3. Batas atas: potongan tidak mungkin lebih panjang dari tali terpanjang.
   (Batas yang lebih ketat lagi: total panjang dibagi K.)

⚠️ ARAH PENUGASAN adalah satu-satunya perbedaan dari Exercise 1, dan
   menukarnya menghasilkan jawaban yang persis salah (kamu akan mendapat
   nilai terkecil yang TIDAK layak). Sebelum menulis, selalu tanyakan:
   "predikatku naik atau turun terhadap x?"

⚠️ x MENDEKATI NOL: floor(panjang / x) meledak menjadi sangat besar, dan
   pada x = 0 terjadi pembagian dengan nol. Karena lo dimulai dari 0 dan
   mid selalu strictly di antara lo dan hi, mid tidak pernah TEPAT nol --
   tetapi ia bisa sangat kecil, sehingga hasil pembagiannya bisa melebihi
   jangkauan int. Akumulasi dalam long long, dan hentikan penjumlahan
   setelah mencapai K (pola yang sama dengan Day 49 Exercise 4).

⚠️ KASUS TIDAK ADA JAWABAN: kalau total panjang seluruh tali kurang dari
   K * (potongan sekecil apa pun), jawabannya 0. Dengan lo = 0 sebagai
   nilai awal dan predikat yang tidak pernah true, lo tetap 0 dan
   tercetak 0.000000 secara alami -- tidak perlu kasus khusus.

⚠️ PRESISI PADA floor: soal ini memakai pembagian real lalu floor, yang
   rawan kasus seperti 8.02 / 2.0 = 4.009999... yang di-floor menjadi 4
   (benar) versus 4.0 / 2.0 = 1.9999999 yang di-floor menjadi 1 (SALAH,
   seharusnya 2). Untuk soal berbasis 2 desimal seperti ini, pendekatan
   yang jauh lebih aman adalah mengalikan seluruh panjang dengan 100 dan
   bekerja dalam BILANGAN BULAT -- menghilangkan seluruh kelas masalah ini.
   Solusi di bawah tetap memakai double karena soal memintanya, tetapi
   ingatlah alternatif itu.

VERIFIKASI SAMPEL 1 (tali 8.02, 7.43, 4.57, 5.39; K = 11):
   x = 2.0 -> 4 + 3 + 2 + 2 = 11 >= 11   layak
   x sedikit di atas 2.0 -> 4 + 3 + 2 + 2 = 11? 8.02/2.01 = 3.99 -> 3
                         -> 3 + 3 + 2 + 2 = 10 < 11   tidak layak
   jadi jawabannya tepat 2.0   ✓

🔄 ALTERNATIVE APPROACHES:
- Kalikan seluruh panjang dengan 100, binary search INTEGER. Lebih aman,
  lebih cepat, dan menghilangkan seluruh masalah presisi. Ini yang
  sebaiknya kamu lakukan di kontes nyata.
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

    vector<double> a(n);
    double maks = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; maks = max(maks, a[i]); }

    auto bisa = [&](double x) {
        ll total = 0;
        for (double p : a) {
            total += (ll)(p / x);
            if (total >= K) return true;       // hentikan: cegah nilai meledak
        }
        return total >= K;
    };

    double lo = 0, hi = maks;
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) lo = mid;               // layak -> coba LEBIH BESAR
        else           hi = mid;
    }

    printf("%.6f\n", lo);
    return 0;
}
