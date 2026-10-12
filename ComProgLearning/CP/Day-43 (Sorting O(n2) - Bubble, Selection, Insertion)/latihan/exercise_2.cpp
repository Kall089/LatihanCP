/*
============================================================
🏋️ Exercise 2: Selection Sort Hemat Pertukaran
============================================================
Day: 43 | Difficulty: Easy
Topic: Selection sort + jumlah swap minimum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah lengan robot memindahkan kotak-kotak yang berjajar. Setiap operasi
PERTUKARAN dua kotak sangat mahal (butuh 1 menit), sedangkan MEMBANDINGKAN
berat dua kotak praktis gratis.
Diberikan berat N kotak, urutkan kotak-kotak itu menaik dengan jumlah
pertukaran SESEDIKIT MUNGKIN menggunakan selection sort. Cetak berapa
pertukaran yang dibutuhkan.
Perhatikan bahwa kalau elemen sudah berada di posisi yang benar, kamu tidak
perlu menukarnya dengan dirinya sendiri.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah pertukaran

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
5 1 4 2

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
4
1 2 3 4

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Selection sort melakukan paling banyak N-1 pertukaran — jauh lebih
         sedikit daripada bubble sort. Tapi ada satu detail yang membuat
         sampel 2 menghasilkan 0 dan bukan 3.

🎯 Learning Goals:
- [ ] Memahami kenapa selection sort punya swap paling sedikit
- [ ] Menghindari pertukaran yang sia-sia
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap i, cari indeks minimum di a[i..n-1]

    // TODO: tukar HANYA kalau indeksnya berbeda

    return 0;
}
