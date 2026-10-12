/*
============================================================
✅ Solution 1: Titik Minimum Parabola
============================================================
Approach: Ternary search real
Complexity: Time O(Q * 200) | Space O(1)
Key Insight: Binary search membutuhkan predikat MONOTON. Fungsi kuadrat
             dengan a > 0 turun lalu naik, sehingga tidak ada predikat
             monoton yang bisa dibentuk. Tetapi dengan mengevaluasi f di
             DUA titik, kita mendapat informasi arah yang cukup untuk
             membuang sepertiga ruang pencarian.

📖 KENAPA DUA TITIK SUDAH CUKUP:
   Ambil m1 < m2 di dalam [lo, hi].
   Jika f(m1) < f(m2): minimum tidak mungkin berada di kanan m2.
       Sebab kalau minimum ada di kanan m2, maka pada [lo, m2] fungsinya
       masih menurun, sehingga f(m1) > f(m2) -- kontradiksi.
       -> buang [m2, hi], set hi = m2.
   Jika f(m1) > f(m2): dengan alasan cermin, buang [lo, m1], set lo = m1.
   Jika sama: keduanya boleh (untuk fungsi unimodal KETAT).

📖 BERAPA ITERASI: setiap langkah menyisakan 2/3 rentang.
   Setelah k iterasi: lebar = awal * (2/3)^k.
   Untuk rentang 2000 dan presisi 1e-9: (2/3)^k <= 5e-13, jadi k >= 70.
   200 iterasi jauh lebih dari cukup.

⚠️ TERNARY LEBIH MAHAL DARIPADA BINARY: ia mengevaluasi f DUA KALI per
   iterasi, dan hanya membuang 1/3 (bukan 1/2). Totalnya bisa 4x lebih
   lambat. Kalau ada cara mengubahnya menjadi binary search, lakukan itu.

⚠️ TANDA PERBANDINGAN ADALAH BUG PALING UMUM.
   Untuk MINIMUM: if (f(m1) < f(m2)) hi = m2; else lo = m1;
   Untuk MAKSIMUM: balik tandanya, ATAU (lebih aman) cari minimum dari -f(x)
   sehingga tidak ada tanda yang bisa tertukar.
   Selalu uji dengan f(x) = (x-3)^2 pada [0,10] yang jawabannya 3.

⚠️ MINIMUM DI LUAR RENTANG: kalau titik optimal sesungguhnya berada di luar
   [-1000, 1000], ternary search akan konvergen ke ujung rentang -- dan itu
   memang jawaban yang benar untuk soal ini. Tidak perlu penanganan khusus,
   karena fungsinya tetap monoton di dalam rentang yang diberikan (kasus
   khusus dari unimodal).

CATATAN: parabola punya rumus eksak x = -b/(2a). Kalau kamu mengenali
bentuknya di kontes, pakai rumusnya -- jauh lebih cepat dan eksak.
Soal ini memakai ternary search sebagai LATIHAN, dan rumus eksaknya berguna
untuk MEMVERIFIKASI implementasimu.

🔄 ALTERNATIVE APPROACHES:
- Rumus eksak: x = clamp(-b/(2a), -1000, 1000). O(1), eksak.
- Golden section search: 1 evaluasi per iterasi (bukan 2) dengan memakai
  kembali salah satu titik. ~40% lebih cepat, tetapi lebih rumit ditulis.
- Binary search pada TURUNAN f'(x) = 2ax + b, yang monoton. Ini pola umum
  yang berlaku untuk fungsi cembung yang turunannya mudah dihitung.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    if (!(cin >> Q)) return 0;

    while (Q--) {
        double a, b, c;
        cin >> a >> b >> c;

        auto f = [&](double x) { return a * x * x + b * x + c; };

        double lo = -1000, hi = 1000;
        for (int it = 0; it < 200; it++) {
            double m1 = lo + (hi - lo) / 3;
            double m2 = hi - (hi - lo) / 3;
            if (f(m1) < f(m2)) hi = m2;    // minimum di kiri m2
            else               lo = m1;    // minimum di kanan m1
        }

        printf("%.6f\n", f((lo + hi) / 2));
    }
    return 0;
}
