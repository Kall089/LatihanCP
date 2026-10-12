/*
============================================================
🏋️ Exercise 3: Membagi Apartemen
============================================================
Day: 71 | Difficulty: Medium
Topic: Greedy dua pointer
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pelamar dan M apartemen. Pelamar ke-i menginginkan apartemen berukuran
a[i], dan apartemen ke-j berukuran b[j].
Seorang pelamar bersedia menerima apartemen kalau selisih ukurannya dengan
keinginannya tidak melebihi K, yaitu ukuran apartemen berada di antara
a[i] - K dan a[i] + K (inklusif).
Setiap pelamar menerima paling banyak satu apartemen, dan setiap apartemen
diberikan kepada paling banyak satu pelamar.
Cari BERAPA BANYAK pelamar yang bisa mendapatkan apartemen.

📥 INPUT FORMAT:
- Baris pertama: N, M, dan K
- Baris kedua: N bilangan a[i]
- Baris ketiga: M bilangan b[j]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah pelamar yang mendapat apartemen

📏 CONSTRAINTS:
- 1 <= N, M <= 2 * 10^5
- 0 <= K <= 10^9
- 1 <= a[i], b[j] <= 10^9

📎 SAMPLE INPUT 1:
4 3 5
60 45 80 60
30 60 75

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
1 1 0
5 5

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Kalau kedua daftar diurutkan, masalahnya menjadi jauh lebih jelas.
         Bayangkan kamu memproses pelamar dari yang menginginkan apartemen
         TERKECIL. Apartemen mana yang sebaiknya kamu berikan kepadanya?
         Pikirkan: kalau ada dua apartemen yang sama-sama cocok untuknya,
         memberikan yang LEBIH BESAR akan menyisakan apa untuk pelamar
         berikutnya (yang keinginannya lebih besar)?
         Argumen itu adalah exchange argument dalam bentuk paling sederhana.
         Karena kedua daftar terurut, kamu bisa memproses keduanya dengan
         dua penunjuk yang keduanya hanya MAJU.
         Apartemen yang terlalu KECIL untuk pelamar sekarang tidak akan
         pernah cocok untuk pelamar berikutnya — apa artinya bagi
         penunjukmu?

🎯 Learning Goals:
- [ ] Menerapkan exchange argument pada pemasangan
- [ ] Memakai dua penunjuk yang keduanya monoton
- [ ] Menyadari kapan sebuah kandidat bisa dibuang selamanya
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan kedua daftar

    // TODO: dua penunjuk; putuskan kapan masing-masing maju

    return 0;
}
