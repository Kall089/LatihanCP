/*
============================================================
🏋️ Exercise 6: Rentang Seimbang Terpanjang
============================================================
Day: 29 | Difficulty: Hard (Contest-level)
Topic: Prefix sum sebagai selisih + map posisi pertama
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string biner S sepanjang N yang hanya terdiri dari karakter '0'
dan '1'. Cari SUBSTRING TERPANJANG yang jumlah karakter '0'-nya sama persis
dengan jumlah karakter '1'-nya. Cetak panjangnya. Jika tidak ada substring
seperti itu, cetak 0.
Contoh: pada "10110", substring "1011" tidak seimbang, tetapi substring "10"
(posisi 1 sampai 2) seimbang dengan panjang 2, dan "0110" (posisi 2 sampai 5)
juga seimbang dengan panjang 4 — jadi jawabannya 4.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: string S

📤 OUTPUT FORMAT:
- Satu bilangan: panjang substring seimbang terpanjang

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5

📎 SAMPLE INPUT 1:
6
110100

📎 SAMPLE OUTPUT 1:
6

Penjelasan: seluruh string punya tiga '1' dan tiga '0'.

📎 SAMPLE INPUT 2:
4
1111

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2
10

📎 SAMPLE OUTPUT 3:
2

💡 HINT: Ubah '0' menjadi -1 dan '1' menjadi +1. Substring seimbang berarti
         jumlahnya nol, yaitu pre[r+1] == pre[l]. Kamu mencari yang
         TERPANJANG, jadi untuk tiap nilai prefix simpan posisi
         KEMUNCULAN PERTAMA saja — jangan diperbarui.

🎯 Learning Goals:
- [ ] Trik +1/-1 untuk mengubah "sama banyak" jadi "jumlah nol"
- [ ] Memahami kenapa yang disimpan posisi PERTAMA, bukan terakhir
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca n dan s

    // TODO: map dari nilai prefix ke indeks kemunculan PERTAMA
    //       inisialisasi: prefix 0 muncul pertama di posisi 0

    // TODO: untuk tiap i, kalau nilai prefix sudah pernah ada,
    //       kandidat panjang = i - posisiPertama[nilai]

    return 0;
}
