/*
============================================================
🏋️ Exercise 1: Bangkitkan Semua Jumlah Subset
============================================================
Day: 54 | Difficulty: Easy
Topic: Enumerasi subset dengan bitmask
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Bangkitkan JUMLAH dari setiap
kemungkinan subhimpunan (termasuk subhimpunan kosong yang jumlahnya 0),
lalu cetak seluruh jumlah itu dalam urutan MENAIK.
Akan ada tepat 2^N bilangan yang dicetak.
Perhatikan bahwa jumlah yang sama boleh muncul beberapa kali dan semuanya
harus dicetak.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi 2^N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 20
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3
1 2 3

📎 SAMPLE OUTPUT 1:
0 1 2 3 3 4 5 6

📎 SAMPLE INPUT 2:
2
-1 1

📎 SAMPLE OUTPUT 2:
-1 0 0 1

💡 HINT: Setiap subhimpunan bisa diwakili oleh sebuah bilangan biner
         sepanjang N bit: bit ke-i menyala berarti elemen ke-i terpilih.
         Cara paling langsung adalah dua loop bersarang, tetapi ada cara
         yang lebih cepat: jumlah untuk sebuah mask bisa dibangun dari
         jumlah mask yang SATU BIT lebih kecil, yang sudah dihitung
         sebelumnya. Pikirkan bit mana yang paling mudah dilepas.
         Perhatikan bahwa nilainya bisa negatif, sehingga jumlah subset
         kosong (nol) tidak selalu yang terkecil.

🎯 Learning Goals:
- [ ] Memetakan subhimpunan ke bitmask
- [ ] Membangun jawaban secara inkremental, O(2^N) alih-alih O(2^N * N)
- [ ] Menyadari bahwa subset kosong ikut terhitung
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: array hasil berukuran 2^N

    // TODO: untuk tiap mask, bangun dari mask yang satu bit lebih kecil

    // TODO: urutkan lalu cetak

    return 0;
}
