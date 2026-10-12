/*
============================================================
🏋️ Exercise 6: Jarak Maksimum ke Pompa Bensin
============================================================
Day: 51 | Difficulty: Hard (Contest-level)
Topic: Binary search real dengan predikat greedy pembagian
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sepanjang sebuah jalan lurus terdapat N pompa bensin pada posisi yang
diberikan, sudah terurut menaik. Kamu boleh menambahkan tepat K pompa baru
di posisi mana pun (tidak harus bilangan bulat, dan boleh di antara pompa
yang sudah ada).
Definisikan D sebagai jarak TERBESAR antara dua pompa yang bersebelahan
setelah penambahan. Cari nilai D SEKECIL MUNGKIN.
Cetak dengan 6 desimal.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N posisi pompa, terurut menaik

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 2 <= N <= 10^5
- 0 <= K <= 10^6
- 0 <= posisi <= 10^9, seluruhnya berbeda dan terurut

📎 SAMPLE INPUT 1:
10 9
1 2 3 4 5 6 7 8 9 10

📎 SAMPLE OUTPUT 1:
0.500000

📎 SAMPLE INPUT 2:
2 1
0 10

📎 SAMPLE OUTPUT 2:
5.000000

💡 HINT: Ini bentuk "minimalkan yang maksimum" yang khas untuk binary search
         on answer. Predikatnya: "dengan jarak maksimum D, berapa pompa
         tambahan yang dibutuhkan?"
         Untuk sebuah celah sepanjang g, berapa pompa yang harus disisipkan
         agar setiap potongannya tidak melebihi D? Pikirkan berapa potongan
         yang terbentuk, lalu berapa pompa yang memisahkannya.
         Predikat itu MENURUN terhadap D: semakin longgar batasnya, semakin
         sedikit pompa yang dibutuhkan. Jadi kamu mencari D terkecil yang
         kebutuhannya masih <= K.
         Peringatan presisi: hasil pembagian celah dengan D bisa menghasilkan
         nilai seperti 2.9999999 yang seharusnya 3. Pikirkan bagaimana
         pembulatanmu bisa salah dan bagaimana mengatasinya.

🎯 Learning Goals:
- [ ] Mengenali pola "minimalkan yang maksimum"
- [ ] Menurunkan rumus kebutuhan pompa per celah
- [ ] Menangani kesalahan pembulatan pada pembagian bilangan real
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikat butuh(D) = total pompa tambahan yang diperlukan

    // TODO: untuk celah g, berapa pompa? perhatikan pembulatan

    return 0;
}
