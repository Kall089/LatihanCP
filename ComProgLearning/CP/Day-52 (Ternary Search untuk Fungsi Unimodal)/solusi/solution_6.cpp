/*
============================================================
✅ Solution 6: Menyeberangi Padang Pasir
============================================================
Approach: Ternary search pada titik penyeberangan
Complexity: Time O(200) | Space O(1)
Key Insight: Waktu tempuh sebagai fungsi titik penyeberangan p adalah
             jumlah dua fungsi akar kuadrat. Setiap akar kuadrat dari
             bentuk sqrt((p-c)^2 + d^2) bersifat CEMBUNG terhadap p, dan
             jumlah fungsi cembung juga cembung -- karena itu unimodal,
             dan ternary search berlaku.

📖 MENYUSUN FUNGSINYA:
   Dari (0,0) ke (p,0) sepanjang aspal: jaraknya |p|, waktunya |p| / v1.
   Dari (p,0) ke (bx,by) melintasi padang pasir: jaraknya
       sqrt((bx - p)^2 + by^2), waktunya jarak / v2.

       waktu(p) = |p| / v1 + sqrt((bx-p)^2 + by^2) / v2

   Suku pertama cembung (nilai absolut selalu cembung), suku kedua cembung
   (akar dari kuadrat plus konstanta). Jumlahnya cembung.  ✓

⚠️ MENENTUKAN RENTANG PENCARIAN adalah bagian nyata dari soal ini.
   Secara intuitif, menyeberang jauh melampaui bx tidak masuk akal --
   dan memang benar, tetapi membuktikannya butuh sedikit kerja.
   Pendekatan yang AMAN: pakai rentang yang jelas-jelas memuat jawaban,
   misalnya [-3*10^4, 3*10^4] mengingat |bx| <= 10^4.
   Biaya rentang yang terlalu lebar hanya satu-dua iterasi tambahan
   (karena penyempitannya eksponensial). Biaya rentang yang terlalu SEMPIT
   adalah jawaban yang salah. Ketika ragu, lebarkan.

⚠️ v1 == v2 (sampel 1): tidak ada keuntungan menyeberang di tempat lain,
   sehingga jawabannya persis jarak lurus dari (0,0) ke B. Untuk bx = 0,
   itu berarti p = 0 dan waktunya by / v2 = 10. Kasus ini bagus untuk
   memverifikasi implementasi karena jawabannya bisa dihitung dengan tangan.

⚠️ TITIK PATAH DI p = 0: fungsi |p| tidak diferensiabel di nol, tetapi
   TETAP CEMBUNG. Ternary search tidak butuh diferensiabilitas -- hanya
   unimodalitas. Ini keunggulan ternary search dibandingkan metode berbasis
   turunan seperti Newton.

VERIFIKASI SAMPEL 2 (bx=10, by=10, v1=2, v2=1):
   Jawabannya 13.660254038, yang sama dengan 5 + 5*sqrt(3).
   Titik optimalnya sekitar p = 4.226, di mana keuntungan bergerak cepat di
   aspal seimbang dengan tambahan jarak yang harus ditempuh.
   (Secara fisika, ini adalah hukum Snell -- pembiasan cahaya mengikuti
   prinsip yang sama persis.)

🔄 ALTERNATIVE APPROACHES:
- Hukum Snell: sin(theta1)/sin(theta2) = v1/v2 memberi solusi analitis,
  tetapi menyelesaikan persamaannya tetap butuh pencarian numerik.
- Binary search pada TURUNAN waktu(p): turunannya monoton karena fungsinya
  cembung. Lebih cepat (1 evaluasi per iterasi), tetapi butuh menurunkan
  rumus turunannya dengan benar.
- Ternary search adalah pilihan paling praktis: tidak perlu turunan, tidak
  perlu menangani titik patah.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double bx, by, v1, v2;
    if (!(cin >> bx >> by >> v1 >> v2)) return 0;

    auto waktu = [&](double p) {
        return fabs(p) / v1 + sqrt((bx - p) * (bx - p) + by * by) / v2;
    };

    // Rentang sengaja dilebarkan: biaya kelebihan hanya 1-2 iterasi,
    // sedangkan biaya kekurangan adalah jawaban yang salah.
    double lo = -3e4, hi = 3e4;
    for (int it = 0; it < 300; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (waktu(m1) < waktu(m2)) hi = m2;
        else                       lo = m1;
    }

    printf("%.9f\n", waktu((lo + hi) / 2));
    return 0;
}
