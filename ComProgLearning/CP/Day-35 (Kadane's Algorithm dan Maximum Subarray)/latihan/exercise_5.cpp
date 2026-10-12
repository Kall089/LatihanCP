/*
============================================================
🏋️ Exercise 5: Hasil Kali Subarray Maksimum
============================================================
Day: 35 | Difficulty: Hard
Topic: Kadane dua variabel
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Cari subarray tidak kosong yang
HASIL KALI seluruh elemennya paling besar, lalu cetak hasil kali itu.
Dijamin jawabannya muat di dalam tipe 64-bit bertanda.
Perhatikan bahwa Kadane versi penjumlahan TIDAK bekerja di sini: dua
bilangan negatif bisa menghasilkan bilangan positif yang sangat besar,
sehingga nilai yang tampak "paling buruk" justru bisa menjadi yang terbaik.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10 <= a[i] <= 10

📎 SAMPLE INPUT 1:
4
2 -3 -2 4

📎 SAMPLE OUTPUT 1:
48

📎 SAMPLE INPUT 2:
3
-2 0 -1

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2
-2 -3

📎 SAMPLE OUTPUT 3:
6

💡 HINT: Bawa DUA nilai berjalan: hasil kali terbesar dan terkecil yang
         berakhir di posisi sekarang. Saat bertemu bilangan negatif,
         peran keduanya bertukar.
         Perhatikan juga peran angka nol: ia memutus rantai perkalian.

🎯 Learning Goals:
- [ ] Memahami kenapa minimum harus ikut dilacak
- [ ] Menangani nol sebagai pemutus rantai
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: curMax, curMin, best -- semuanya mulai dari a[0]

    // TODO: kalau x < 0, tukar curMax dan curMin sebelum memperbarui

    return 0;
}
