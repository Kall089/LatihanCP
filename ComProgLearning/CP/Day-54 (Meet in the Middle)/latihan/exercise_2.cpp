/*
============================================================
🏋️ Exercise 2: Berapa Subset Berjumlah Tepat X
============================================================
Day: 54 | Difficulty: Easy
Topic: Meet in the middle, pola dasar
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat POSITIF dan sebuah target X.
Hitung ADA BERAPA BANYAK subhimpunan (termasuk yang kosong) yang jumlah
elemennya tepat sama dengan X.
Perhatikan batas N: terlalu besar untuk memeriksa seluruh 2^N subhimpunan,
tetapi cukup kecil untuk sesuatu yang lain.

📥 INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya subhimpunan

📏 CONSTRAINTS:
- 1 <= N <= 40
- 1 <= a[i] <= 10^9
- 1 <= X <= 10^18

📎 SAMPLE INPUT 1:
4 6
1 2 3 4

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3 100
1 2 3

📎 SAMPLE OUTPUT 2:
0

💡 HINT: 2^40 sekitar 10^12 — mustahil. Tetapi 2^20 sekitar 10^6 — seketika.
         Bagi array menjadi dua paruh, bangkitkan seluruh jumlah subset
         masing-masing paruh secara terpisah.
         Setiap subhimpunan dari array penuh adalah gabungan dari tepat satu
         subset paruh kiri dan satu subset paruh kanan. Jadi kalau kamu tahu
         jumlah subset kanan adalah s, berapa yang kamu butuhkan dari kiri?
         Untuk mencarinya dengan cepat, urutkan salah satu paruh.
         Jangan lupa: jawabannya bisa mencapai 2^40, jadi perhatikan tipe
         datanya.

🎯 Learning Goals:
- [ ] Menerapkan pembagian dua paruh
- [ ] Menggabungkan dengan sorting dan pencarian biner
- [ ] Menyadari bahwa setiap subset terhitung TEPAT SEKALI
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: bagi jadi dua paruh, bangkitkan subset masing-masing

    // TODO: urutkan salah satu paruh

    // TODO: untuk tiap jumlah paruh lain, hitung kemunculan pasangannya

    return 0;
}
