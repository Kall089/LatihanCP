/*
============================================================
🏋️ Exercise 6: Menyeberangi Jembatan
============================================================
Day: 71 | Difficulty: Hard (Contest-level)
Topic: Exchange argument nontrivial + analisis kasus
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
N orang harus menyeberangi sebuah jembatan gelap pada malam hari. Orang
ke-i membutuhkan waktu t[i] menit untuk menyeberang.
Aturannya:
- Jembatan hanya kuat menahan PALING BANYAK DUA orang sekaligus.
- Hanya ada SATU senter, dan menyeberang tanpa senter tidak diperbolehkan.
- Kalau dua orang menyeberang bersama, waktunya sama dengan waktu orang
  yang LEBIH LAMBAT.
- Setelah menyeberang, seseorang harus membawa senter kembali agar yang lain
  bisa menyeberang.
Cari WAKTU TOTAL MINIMUM agar seluruh orang berada di seberang.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan t[i]

📤 OUTPUT FORMAT:
- Satu bilangan: waktu total minimum

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= t[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 2 5 10

📎 SAMPLE OUTPUT 1:
17

📎 SAMPLE INPUT 2:
1
5

📎 SAMPLE OUTPUT 2:
5

📎 SAMPLE INPUT 3:
3
1 2 5

📎 SAMPLE OUTPUT 3:
8

💡 HINT: Soal ini terkenal karena dugaan greedy yang paling alami TERNYATA
         SALAH. Dugaan itu: "orang tercepat selalu menemani, lalu kembali
         membawa senter". Hitung sampel 1 dengan strategi itu dan
         bandingkan dengan 17 — kamu akan menemukan selisihnya.
         Urutkan dulu, lalu pikirkan: dua orang TERLAMBAT harus menyeberang
         entah bagaimana. Ada tepat DUA cara masuk akal untuk memindahkan
         keduanya ke seberang, dan mana yang lebih murah bergantung pada
         nilai-nilainya.
         Tuliskan biaya kedua cara itu dalam t[0], t[1], dan dua yang
         terlambat. Lalu tangani dua orang terlambat itu sekaligus di setiap
         langkah, dan ulangi.
         Jangan lupa kasus dasarnya: apa yang terjadi kalau tersisa satu,
         dua, atau tiga orang?

🎯 Learning Goals:
- [ ] Menyadari bahwa greedy paling alami bisa salah
- [ ] Membandingkan dua strategi lokal dan memilih yang lebih murah
- [ ] Menangani kasus dasar dengan teliti
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan

    // TODO: proses dua orang terlambat sekaligus, pilih strategi termurah

    // TODO: tangani sisa 1, 2, dan 3 orang

    return 0;
}
