/*
============================================================
🏋️ Exercise 3: Muatan Maksimum
============================================================
Day: 54 | Difficulty: Medium
Topic: Meet in the middle, maksimalkan tanpa melebihi batas
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah truk punya kapasitas angkut W kilogram. Ada N peti dengan berat
masing-masing, dan kamu boleh memilih subhimpunan peti mana pun untuk
diangkut.
Cari BERAT TOTAL TERBESAR yang bisa diangkut tanpa melebihi kapasitas W.
Jika tidak ada peti yang muat sama sekali, jawabannya 0 (truk berangkat
kosong).

📥 INPUT FORMAT:
- Baris pertama: N dan W
- Baris kedua: N bilangan berat

📤 OUTPUT FORMAT:
- Satu bilangan: berat total maksimum

📏 CONSTRAINTS:
- 1 <= N <= 40
- 1 <= W <= 10^18
- 1 <= berat <= 10^18

📎 SAMPLE INPUT 1:
4 5
1 2 3 4

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
3 2
5 6 7

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Strukturnya sama dengan Exercise 2, tetapi sekarang kamu mencari
         nilai TERBESAR yang tidak melebihi batas, bukan yang sama persis.
         Setelah mengurutkan salah satu paruh, untuk setiap jumlah paruh
         lain kamu perlu mencari "nilai terbesar yang tidak melebihi sisa
         kapasitas". Bound mana yang memberimu itu, dan langkah tambahan
         apa yang diperlukan setelah menemukannya?
         Perhatikan bahwa W dan berat masing-masing bisa mencapai 10^18,
         sehingga menjumlahkan dua di antaranya bisa meluap. Pikirkan cara
         menghindarinya.

🎯 Learning Goals:
- [ ] Varian "terbesar yang tidak melebihi"
- [ ] Memakai upper_bound lalu mundur satu, dengan pemeriksaan batas
- [ ] Mencegah overflow saat menjumlahkan dua nilai besar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: dua paruh, urutkan salah satunya

    // TODO: untuk tiap jumlah paruh lain, cari yang terbesar <= sisa

    return 0;
}
