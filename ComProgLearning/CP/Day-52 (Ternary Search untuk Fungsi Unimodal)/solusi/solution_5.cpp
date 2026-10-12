/*
============================================================
✅ Solution 5: Meminimumkan Kelemahan
============================================================
Approach: Ternary search + Kadane maksimum dan minimum
Complexity: Time O(iter * N) | Space O(1)
Key Insight: Kita tidak perlu membuktikan unimodalitas dengan tangan.
             Ada teorema yang menjaminnya: MAKSIMUM dari sekumpulan fungsi
             LINEAR selalu CEMBUNG. Karena setiap subarray menyumbang satu
             fungsi linear terhadap x, kelemahan adalah maksimum atas
             kumpulan fungsi linear -- karena itu cembung, karena itu
             unimodal.

📖 KENAPA SETIAP SUBARRAY ADALAH FUNGSI LINEAR TERHADAP x:
   Untuk subarray [l, r] dengan panjang len dan jumlah asli S:
       jumlah setelah transformasi = S - len * x
   Itu fungsi linear terhadap x dengan kemiringan -len.

   Kelemahan(x) = max atas seluruh subarray dari |S - len*x|
                = max( max(S - len*x),  max(len*x - S) )
   Keduanya maksimum atas fungsi linear -> cembung.
   Maksimum dari dua fungsi cembung juga cembung.  -> UNIMODAL  ✓

   Teorema "max fungsi linear itu cembung" sangat berguna di kontes: ia
   membebaskanmu dari keharusan membuktikan unimodalitas satu per satu.

📖 MENGHITUNG KELEMAHAN DALAM O(N):
   Butuh jumlah subarray MAKSIMUM dan MINIMUM dari b[i] = a[i] - x.
   Keduanya adalah Kadane (Day 35), dan bisa dihitung dalam SATU sapuan
   dengan menjaga empat variabel sekaligus.
   Kelemahan = max(maxSubarray, -minSubarray).

⚠️ MENGHITUNG TOTAL BIAYA SEBELUM MEMILIH JUMLAH ITERASI:
   N = 2*10^5, dan setiap evaluasi kelemahan berbiaya O(N).
   Ternary search mengevaluasi DUA KALI per iterasi.
       200 iterasi -> 200 * 2 * 2*10^5 = 8*10^7   berisiko dengan double
       100 iterasi -> 4*10^7                       lebih aman
   Solusi ini memakai 100 iterasi, yang tetap memberi presisi
   (2/3)^100 ~ 2.5*10^-18 relatif terhadap rentang -- jauh lebih dari cukup
   untuk 6 desimal.
   Pelajarannya: jumlah iterasi bukan angka keramat. Hitung berdasarkan
   presisi yang dibutuhkan DAN batas waktu yang tersedia.

⚠️ RENTANG PENCARIAN: jawaban optimal x pasti berada di antara nilai
   minimum dan maksimum array. Di luar rentang itu, seluruh b[i] bertanda
   sama dan kelemahan hanya bertambah. Memakai [min(a), max(a)] aman dan
   seketat mungkin.

VERIFIKASI SAMPEL 1 (a = [1,2,3]):
   Pada x = 2: b = [-1, 0, 1]
       subarray maksimum: [1] -> 1
       subarray minimum : [-1] -> -1
       kelemahan = max(1, 1) = 1
   Nilai x lain menghasilkan kelemahan lebih besar, jadi jawabannya 1.  ✓

🔄 ALTERNATIVE APPROACHES:
- Binary search pada turunan: kelemahan cembung, sehingga turunannya monoton.
  Tetapi turunannya tidak mudah dihitung di sini, jadi ternary lebih praktis.
- Ini adalah CF 578C. Beberapa solusi memakai long double untuk presisi
  tambahan; kalau kamu mendapat WA pada digit terakhir, coba itu.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<double> a(n);
    for (double& x : a) cin >> x;

    // Kelemahan(x): satu sapuan Kadane maksimum DAN minimum sekaligus
    auto kelemahan = [&](double x) {
        double curMax = 0, bestMax = 0;
        double curMin = 0, bestMin = 0;
        for (int i = 0; i < n; i++) {
            double b = a[i] - x;
            curMax = max(b, curMax + b);  bestMax = max(bestMax, curMax);
            curMin = min(b, curMin + b);  bestMin = min(bestMin, curMin);
        }
        return max(bestMax, -bestMin);
    };

    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    // 100 iterasi: presisi (2/3)^100 ~ 2.5e-18, dan biayanya 100*2*N = 4e7
    for (int it = 0; it < 100; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (kelemahan(m1) < kelemahan(m2)) hi = m2;
        else                               lo = m1;
    }

    printf("%.6f\n", kelemahan((lo + hi) / 2));
    return 0;
}
