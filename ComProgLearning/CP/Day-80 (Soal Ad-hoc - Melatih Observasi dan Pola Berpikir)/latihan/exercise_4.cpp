/*
============================================================
🏋️ Exercise 4: Memindahkan Batu ke Tetangga
============================================================
Day: 80 | Difficulty: Medium
Topic: Batas bawah bertemu konstruksi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kotak berjajar; kotak ke-i berisi a[i] batu.
Satu operasi memindahkan TEPAT SATU batu dari sebuah kotak ke kotak
tetangganya (kiri atau kanan).
Kamu ingin membuat seluruh kotak berisi jumlah batu yang sama.
Cari JUMLAH OPERASI MINIMUM, atau -1 kalau tidak mungkin.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah operasi minimum, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
0 0 6 2

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
3
1 2 3

📎 SAMPLE OUTPUT 2:
2

📎 SAMPLE INPUT 3:
2
1 2

📎 SAMPLE OUTPUT 3:
-1

💡 HINT: Mulailah dengan pertanyaan paling murah: KAPAN soal ini tidak
         mungkin? Perhatikan bahwa satu operasi tidak mengubah jumlah total
         batu. Apa artinya bagi nilai akhir tiap kotak?
         Setelah itu, soal ini adalah soal "minimum", jadi kamu butuh DUA
         hal: batas bawah dan konstruksi yang mencapainya.
         Untuk batas bawahnya, pikirkan tentang SEKAT di antara kotak ke-i
         dan kotak ke-(i+1). Berapa batu yang HARUS melintasi sekat itu,
         berapa pun caranya kamu mengatur operasi?
         Jawaban pertanyaan itu memberi batas bawah untuk tiap sekat, dan
         menjumlahkannya memberi batas bawah keseluruhan.
         Untuk konstruksinya, tunjukkan bahwa kamu bisa mencapai batas itu
         dengan memindahkan batu ke satu arah saja pada tiap sekat.
         Perhatikan bahwa jawabannya bisa sangat besar: 2*10^5 kotak dengan
         10^9 batu.
         Sampel 1 bagus untuk dihitung dengan tangan. Hitung berapa batu
         yang melintasi tiap sekat dan jumlahkan.

🎯 Learning Goals:
- [ ] Memeriksa kemustahilan lewat invarian sebelum mencari jawaban
- [ ] Menurunkan batas bawah lewat argumen sekat
- [ ] Menunjukkan konstruksi yang mencapai batas bawah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: periksa kemustahilan lebih dulu

    // TODO: batas bawah lewat argumen sekat

    return 0;
}
