/*
============================================================
🏋️ Exercise 2: Berapa Elemen dalam Rentang Nilai
============================================================
Day: 49 | Difficulty: Easy
Topic: Turunan dari kedua bound
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat (TIDAK dijamin terurut) dan Q
pertanyaan. Setiap pertanyaan berisi dua bilangan L dan R, dan kamu harus
menjawab berapa banyak elemen array yang nilainya berada di antara L dan R
(inklusif di kedua ujung).
Perhatikan bahwa yang ditanyakan adalah rentang NILAI, bukan rentang posisi.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: L dan R

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= nilai, L, R <= 10^9
- L <= R dijamin

📎 SAMPLE INPUT 1:
6 3
5 1 7 3 3 3
3 5
1 7
4 4

📎 SAMPLE OUTPUT 1:
4
6
0

💡 HINT: Ada satu langkah persiapan yang harus dilakukan sebelum binary
         search bisa dipakai sama sekali. Jangan lewatkan itu.
         Setelah itu, jawabannya adalah selisih dua bound. Pikirkan bound
         mana untuk L dan bound mana untuk R — salah satu memakai lower dan
         yang lain memakai upper, dan menukarnya menghasilkan hitungan yang
         meleset.

🎯 Learning Goals:
- [ ] Menyadari bahwa binary search WAJIB pada data terurut
- [ ] Menurunkan rumus hitungan rentang dari kedua bound
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: langkah persiapan

    // TODO: jawab tiap query dengan selisih dua bound

    return 0;
}
