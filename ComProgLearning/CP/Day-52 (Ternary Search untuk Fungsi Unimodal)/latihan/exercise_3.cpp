/*
============================================================
🏋️ Exercise 3: Titik Temu Dua Pelari
============================================================
Day: 52 | Difficulty: Medium
Topic: Ternary search pada fungsi jarak
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Dua pelari bergerak lurus beraturan pada bidang datar.
Pelari pertama berada di posisi (x1, y1) pada saat t = 0 dan bergerak
dengan kecepatan (vx1, vy1) satuan per detik.
Pelari kedua berada di (x2, y2) dengan kecepatan (vx2, vy2).
Cari JARAK TERDEKAT yang pernah terjadi di antara keduanya selama rentang
waktu t dari 0 sampai T detik. Cetak dengan 6 desimal.

📥 INPUT FORMAT:
- Baris pertama: T
- Baris kedua: x1, y1, vx1, vy1
- Baris ketiga: x2, y2, vx2, vy2

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 1 <= T <= 10^6
- -10^4 <= koordinat dan kecepatan <= 10^4

📎 SAMPLE INPUT 1:
10
0 0 1 0
10 0 -1 0

📎 SAMPLE OUTPUT 1:
0.000000

📎 SAMPLE INPUT 2:
10
0 0 0 0
5 0 0 0

📎 SAMPLE OUTPUT 2:
5.000000

💡 HINT: Tuliskan posisi masing-masing pelari sebagai fungsi waktu, lalu
         tuliskan KUADRAT jarak di antara keduanya. Kamu akan mendapati
         bahwa itu adalah fungsi kuadrat terhadap t dengan koefisien
         pemimpin yang tidak negatif — dan fungsi seperti itu bersifat
         cembung, yang berarti unimodal.
         Bekerjalah dengan kuadrat jaraknya selama pencarian, dan ambil
         akarnya hanya di akhir. Selain lebih cepat, ini menghindari
         kesalahan pembulatan.
         Perhatikan sampel 2: kalau kedua pelari diam, fungsinya KONSTAN.
         Apakah implementasimu tetap benar untuk kasus itu?

🎯 Learning Goals:
- [ ] Mengenali bentuk kuadrat sebagai fungsi cembung
- [ ] Bekerja dengan kuadrat jarak alih-alih jarak
- [ ] Menangani fungsi konstan (kasus tepi unimodalitas)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: fungsi kuadrat jarak terhadap t

    // TODO: ternary search pada [0, T]

    // TODO: ambil akar hanya di akhir

    return 0;
}
