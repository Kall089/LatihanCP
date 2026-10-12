/*
============================================================
🏋️ Exercise 2: Titik Pareto
============================================================
Day: 76 | Difficulty: Easy
Topic: Dominasi dengan nilai berulang
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N titik pada bidang; titik ke-i berada di (x[i], y[i]).
Titik i dikatakan DIDOMINASI oleh titik j kalau x[j] >= x[i] dan
y[j] >= y[i], dengan setidaknya salah satu pertidaksamaan itu STRICT.
Titik yang tidak didominasi oleh titik mana pun disebut PARETO-OPTIMAL.
Perhatikan bahwa dua titik yang letaknya sama persis TIDAK saling
mendominasi, sehingga keduanya Pareto-optimal.
Cari berapa banyak titik yang Pareto-optimal.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: x[i] dan y[i]

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya titik Pareto-optimal

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= x[i], y[i] <= 10^9

📎 SAMPLE INPUT 1:
5
1 5
2 3
1 2
3 4
2 3

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3
2 2
2 2
2 2

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Mulailah dengan brute force O(n kuadrat) untuk n kecil. Kamu
         akan membutuhkannya sebagai pembanding, dan menulisnya lebih dulu
         membuat definisinya jelas di kepalamu.
         Untuk versi cepat: urutkan menurut x, lalu sapu. Pertanyaannya,
         ke arah mana mengurutkan, dan apa tie-break-nya?
         Kesulitan sesungguhnya ada pada titik dengan x yang SAMA. Dua
         titik dengan x sama: kapan yang satu mendominasi yang lain?
         Bandingkan dengan dua titik yang x-nya BERBEDA. Apakah syarat
         pada y sama untuk kedua kasus itu?
         Kalau jawabanmu "sama", periksa lagi. Perbedaan halus di situlah
         letak seluruh soal ini.
         Sampel 2 adalah kasus tepi paling penting: tiga titik identik.
         Kalau kodemu menjawab 1, kamu baru saja menemukan bugnya.
         Terakhir: saat menulis stress test, batasi koordinat ke 0 sampai 3.
         Dengan koordinat sampai 10^9 bug ini tidak akan pernah muncul.

🎯 Learning Goals:
- [ ] Membedakan pembanding dalam-kelompok dan antar-kelompok
- [ ] Memproses per kelompok, bukan per elemen
- [ ] Merancang generator yang sengaja memunculkan seri
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan; tentukan arah dan tie-break dengan sadar

    // TODO: proses per KELOMPOK x yang sama

    return 0;
}
