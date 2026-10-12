/*
============================================================
🏋️ Exercise 4: Lompat Sejauh Mungkin
============================================================
Day: 73 | Difficulty: Medium
Topic: Covering dalam penyamaran (jump game)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu berdiri di petak 0 dari sebuah barisan N petak bernomor 0 sampai N-1.
Dari petak i kamu dapat melompat ke petak mana pun dari i+1 sampai i+a[i]
(kalau a[i] bernilai 0 kamu tidak bisa melompat dari petak itu).
Cari JUMLAH LOMPATAN MINIMUM untuk mencapai petak N-1, atau -1 kalau tidak
mungkin.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah lompatan minimum, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= a[i] <= 10^5

📎 SAMPLE INPUT 1:
5
2 3 1 1 4

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
5
3 2 1 0 4

📎 SAMPLE OUTPUT 2:
-1

📎 SAMPLE INPUT 3:
1
0

📎 SAMPLE OUTPUT 3:
0

💡 HINT: Ini adalah Exercise 3 yang menyamar sangat rapi. Coba ubah setiap
         petak i menjadi sebuah interval — interval apa yang tepat?
         Petunjuk: dari petak i kamu bisa mendarat di mana saja pada
         rentang tertentu, dan untuk berada di petak i kamu harus sudah
         sampai posisi i.
         Setelah kamu melihat pemetaannya, algoritmanya identik dengan
         Exercise 3 dan bisa ditulis tanpa membuat array interval sama
         sekali: cukup lacak "sejauh mana aku bisa sampai dengan lompatan
         sekarang" dan "sejauh mana aku bisa sampai dengan satu lompatan
         lagi".
         Sampel 3 adalah kasus tepi: kamu sudah berada di tujuan.

🎯 Learning Goals:
- [ ] Mengenali covering dalam penyamaran yang tidak menyebut interval
- [ ] Menerapkan pola yang sama tanpa membangun struktur data
- [ ] Menangani kasus tepi n = 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: petakan tiap petak menjadi interval

    // TODO: greedy jangkauan terjauh, tanpa perlu array interval

    return 0;
}
