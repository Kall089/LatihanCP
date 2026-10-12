/*
============================================================
✅ Solution 3: Titik Temu Dua Pelari
============================================================
Approach: Ternary search pada kuadrat jarak
Complexity: Time O(200) | Space O(1)
Key Insight: Kuadrat jarak antara dua benda yang bergerak lurus beraturan
             adalah fungsi KUADRAT terhadap waktu dengan koefisien pemimpin
             tidak negatif -- karena itu ia CEMBUNG, dan fungsi cembung
             selalu unimodal. Kita tidak perlu membuktikan unimodalitas
             secara terpisah; bentuk aljabarnya sudah menjaminnya.

📖 TURUNAN BENTUKNYA:
   dx(t) = (x1 + vx1*t) - (x2 + vx2*t) = (x1-x2) + (vx1-vx2)*t
   dy(t) = (y1-y2) + (vy1-vy2)*t

   jarak^2(t) = dx(t)^2 + dy(t)^2
              = [(vx1-vx2)^2 + (vy1-vy2)^2] * t^2 + (suku linear) + (konstanta)

   Koefisien t^2 adalah jumlah dua kuadrat, jadi selalu >= 0. Fungsi kuadrat
   dengan koefisien pemimpin >= 0 bersifat cembung.

⚠️ BEKERJA DENGAN KUADRAT JARAK, BUKAN JARAK.
   Tiga alasan:
   1. Akar kuadrat lambat, dan kita memanggilnya 400 kali.
   2. Akar kuadrat memperkenalkan kesalahan pembulatan di setiap evaluasi.
   3. Akar kuadrat adalah fungsi monoton naik, sehingga MEMINIMUMKAN
      jarak^2 sama persis dengan meminimumkan jarak. Urutannya tidak berubah.
   Ambil akarnya HANYA SEKALI di akhir.

⚠️ KASUS KOEFISIEN NOL (sampel 2): kalau kedua pelari punya kecepatan yang
   sama (termasuk kasus keduanya diam), koefisien t^2 menjadi nol dan
   fungsinya LINEAR -- bahkan KONSTAN kalau suku linearnya juga nol.
   Fungsi konstan secara teknis bukan unimodal KETAT, sehingga f(m1) == f(m2)
   di setiap langkah. Namun karena nilainya sama di mana-mana, cabang mana
   pun yang dipilih tetap menghasilkan NILAI yang benar. Implementasi ini
   aman untuk kasus tersebut tanpa penanganan khusus.
   Untuk fungsi LINEAR (koefisien t^2 nol tetapi suku linear tidak),
   minimumnya berada di salah satu ujung -- dan ternary search tetap
   menemukannya karena fungsi monoton adalah kasus khusus unimodal.

⚠️ RENTANG WAKTU: soal membatasi t pada [0, T]. Titik minimum matematis
   mungkin berada di luar rentang itu (misalnya pada t negatif). Ternary
   search pada [0, T] akan konvergen ke ujung yang benar -- sekali lagi
   karena monoton adalah kasus khusus unimodal.

VERIFIKASI SAMPEL 1: dua pelari bergerak saling mendekat dari (0,0) dan
   (10,0) dengan kecepatan 1 dan -1. Mereka bertemu di t = 5 pada titik
   (5,0), jaraknya 0.   ✓

🔄 ALTERNATIVE APPROACHES:
- Rumus eksak: minimum parabola di t = -b/(2a), lalu clamp ke [0, T].
  O(1) dan eksak. Kalau kamu mengenali bentuknya, ini pilihan yang benar.
  Perlu penanganan khusus untuk a = 0.
- Ternary search dipakai di sini sebagai latihan, dan berguna kalau
  fungsinya lebih rumit (misalnya ada percepatan atau lebih dari dua benda).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double T;
    double x1, y1, vx1, vy1, x2, y2, vx2, vy2;
    if (!(cin >> T)) return 0;
    cin >> x1 >> y1 >> vx1 >> vy1;
    cin >> x2 >> y2 >> vx2 >> vy2;

    // Kuadrat jarak sebagai fungsi waktu -- cembung, jadi unimodal
    auto jarak2 = [&](double t) {
        double dx = (x1 + vx1 * t) - (x2 + vx2 * t);
        double dy = (y1 + vy1 * t) - (y2 + vy2 * t);
        return dx * dx + dy * dy;
    };

    double lo = 0, hi = T;
    for (int it = 0; it < 200; it++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (jarak2(m1) < jarak2(m2)) hi = m2;
        else                         lo = m1;
    }

    printf("%.6f\n", sqrt(jarak2((lo + hi) / 2)));   // akar HANYA di akhir
    return 0;
}
