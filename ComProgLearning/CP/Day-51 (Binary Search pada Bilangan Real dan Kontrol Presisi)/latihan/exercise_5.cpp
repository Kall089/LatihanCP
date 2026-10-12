/*
============================================================
🏋️ Exercise 5: Rasio Terbaik
============================================================
Day: 51 | Difficulty: Hard
Topic: Fractional programming
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N benda, benda ke-i punya NILAI p[i] dan BOBOT q[i] yang keduanya
bilangan bulat positif. Pilih TEPAT K benda sehingga rasio
(jumlah nilai yang dipilih) dibagi (jumlah bobot yang dipilih)
menjadi sebesar mungkin.
Cetak rasio maksimum itu dikalikan 100, dibulatkan ke bilangan bulat
terdekat.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: masing-masing p[i] dan q[i]

📤 OUTPUT FORMAT:
- Satu bilangan bulat

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^5
- 1 <= p[i], q[i] <= 10^6

📎 SAMPLE INPUT 1:
3 2
1 1
2 1
3 1

📎 SAMPLE OUTPUT 1:
250

Penjelasan: pilih benda kedua dan ketiga, rasionya (2+3)/(1+1) = 2.5,
dikalikan 100 menjadi 250.

📎 SAMPLE INPUT 2:
2 1
7 2
1 1

📎 SAMPLE OUTPUT 2:
350

💡 HINT: Rasio, seperti rata-rata, tidak monoton. Tetapi transformasi yang
         sama bekerja:

             jumlah p / jumlah q >= x
             jumlah p - x * jumlah q >= 0
             jumlah dari (p[i] - x * q[i]) >= 0

         Perhatikan bahwa langkah kedua hanya sah karena seluruh q[i]
         POSITIF — kalau ada q[i] negatif, mengalikan pertidaksamaan dengan
         jumlah q bisa membalik tandanya.
         Teknik ini disebut fractional programming, dan berlaku untuk
         banyak soal optimasi rasio.
         Untuk pembulatan akhir, hati-hati: nilai seperti 2.4999999 karena
         keterbatasan presisi harus tetap menjadi 250, bukan 249.

🎯 Learning Goals:
- [ ] Menerapkan transformasi pada rasio, bukan hanya rata-rata
- [ ] Menyadari syarat q[i] > 0 agar transformasinya sah
- [ ] Menangani pembulatan akhir dengan aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikat bisa(x): ambil K nilai (p[i] - x*q[i]) terbesar

    // TODO: hati-hati saat membulatkan hasil akhir

    return 0;
}
