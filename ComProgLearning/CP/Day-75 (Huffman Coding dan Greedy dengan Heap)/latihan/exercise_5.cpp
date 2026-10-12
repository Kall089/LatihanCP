/*
============================================================
🏋️ Exercise 5: Membagi Tugas ke Mesin
============================================================
Day: 75 | Difficulty: Hard
Topic: Heap sebagai penjadwal (bukan Huffman)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tugas dengan durasi t[i], dan M mesin identik yang bekerja paralel.
Setiap tugas dikerjakan utuh oleh satu mesin, dan sebuah mesin mengerjakan
tugas satu per satu tanpa jeda.
Tugas HARUS dijadwalkan dalam urutan yang diberikan: tugas ke-1 lebih dulu,
lalu tugas ke-2, dan seterusnya. Setiap tugas diberikan kepada mesin yang
paling cepat menganggur (bila seri, mesin bernomor terkecil).
Cari WAKTU SELESAI TERAKHIR (makespan) dari seluruh tugas.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N durasi t[i]

📤 OUTPUT FORMAT:
- Satu bilangan: waktu selesai terakhir

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= M <= 2 * 10^5
- 1 <= t[i] <= 10^9

📎 SAMPLE INPUT 1:
5 2
3 1 4 1 5

📎 SAMPLE OUTPUT 1:
9

📎 SAMPLE INPUT 2:
3 5
7 2 9

📎 SAMPLE OUTPUT 2:
9

💡 HINT: Perhatikan bahwa soal ini SUDAH memberitahumu aturannya —
         kamu tidak perlu membuktikan greedy apa pun, cukup
         menyimulasikannya dengan efisien.
         Simulasi naif memeriksa seluruh M mesin untuk setiap tugas,
         menghasilkan N kali M operasi. Dengan batasan yang diberikan itu
         terlalu lambat.
         Yang kamu butuhkan hanyalah "mesin yang paling cepat menganggur".
         Struktur data mana yang memberimu itu dengan cepat, dan tetap
         benar setelah waktu bebasnya berubah?
         Sampel 2 menguji kasus mesin lebih banyak daripada tugas. Pastikan
         kodemu tidak salah ketika ada mesin yang tidak pernah dipakai.
         Sebagai renungan: seandainya tugas BOLEH diurutkan ulang, aturan
         mana yang meminimalkan makespan? Itu soal yang jauh lebih sulit
         dan bukan bagian dari latihan ini, tetapi menarik untuk dipikirkan.

🎯 Learning Goals:
- [ ] Memakai heap untuk simulasi penjadwalan
- [ ] Membedakan "simulasikan aturan yang diberikan" dan "temukan aturan"
- [ ] Menangani kasus mesin berlebih
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: heap berisi waktu bebas tiap mesin

    // TODO: proses tugas berurutan

    return 0;
}
