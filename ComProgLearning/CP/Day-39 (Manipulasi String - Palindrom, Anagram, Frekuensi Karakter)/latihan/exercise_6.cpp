/*
============================================================
🏋️ Exercise 6: Palindrom Terpanjang
============================================================
Day: 32 | Difficulty: Hard
Topic: Expand around center
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah kata S. Cari substring terpanjang dari S yang merupakan
palindrom. Substring berarti potongan huruf yang berurutan (tidak boleh melompat).
Jika ada beberapa palindrom terpanjang dengan panjang sama, cetak yang
posisi awalnya paling kiri.

Contoh: pada "babad", terdapat "bab" (posisi 0) dan "aba" (posisi 1),
keduanya sepanjang 3. Jawabannya adalah "bab" karena posisinya lebih kiri.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris: substring palindrom terpanjang.

📏 CONSTRAINTS:
- 1 <= |S| <= 5000
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
babad

📎 SAMPLE OUTPUT 1:
bab

📎 SAMPLE INPUT 2:
cbbd

📎 SAMPLE OUTPUT 2:
bb

📎 SAMPLE INPUT 3:
abcde

📎 SAMPLE OUTPUT 3:
a

💡 HINT:
- Setiap palindrom punya PUSAT. Ada dua jenis pusat:
  satu huruf (untuk panjang ganjil) dan dua huruf berdampingan (panjang genap).
- Untuk tiap pusat, lebarkan ke kiri dan ke kanan selama hurufnya masih sama.
- Total ada 2N-1 pusat yang perlu dicoba.
- Jangan lupa menangani KEDUA jenis pusat, ini kesalahan paling umum.

🎯 Learning Goals:
- [ ] Memahami konsep pusat palindrom
- [ ] Menangani panjang ganjil dan genap sekaligus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S

    // TODO: Untuk tiap i, lebarkan dari pusat (i, i) -> panjang ganjil

    // TODO: Untuk tiap i, lebarkan dari pusat (i, i+1) -> panjang genap

    // TODO: Simpan posisi awal & panjang terbaik, lalu cetak substr-nya

    return 0;
}
