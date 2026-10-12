/*
============================================================
🏋️ Exercise 1: Kompres Array
============================================================
Day: 38 | Difficulty: Easy
Topic: Idiom sort + unique + erase + lower_bound
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat yang nilainya bisa sangat besar.
Gantilah setiap elemen dengan PERINGKATNYA di antara seluruh nilai BERBEDA
yang ada di array, dihitung dari 0 untuk nilai terkecil.
Dua elemen yang nilainya sama harus mendapat peringkat yang sama.
Cetak array hasil kompresi, lalu cetak berapa banyak nilai berbeda yang ada.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Baris pertama: N bilangan hasil kompresi
- Baris kedua: banyaknya nilai berbeda

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5
1000000000 5 999 5 1000000000

📎 SAMPLE OUTPUT 1:
2 0 1 0 2
3

📎 SAMPLE INPUT 2:
4
7 7 7 7

📎 SAMPLE OUTPUT 2:
0 0 0 0
1

💡 HINT: Salin array, urutkan, buang duplikat, lalu cari posisi tiap elemen
         dengan pencarian biner.
         Satu peringatan: fungsi yang membuang duplikat di STL sebenarnya
         TIDAK menghapus apa pun — ia hanya memindahkan elemen unik ke depan
         dan memberitahu di mana bagian uniknya berakhir. Kamu harus
         menghapusnya sendiri.

🎯 Learning Goals:
- [ ] Menulis idiom baku tanpa melihat contoh
- [ ] Memahami kenapa erase wajib setelah unique
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca array

    // TODO: salin -> sort -> unique + erase

    // TODO: petakan tiap elemen dengan lower_bound

    return 0;
}
