/*
============================================================
🏋️ Exercise 5: Jadwal Berbobot
============================================================
Day: 72 | Difficulty: Hard
Topic: Weighted interval scheduling (DP, bukan greedy)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N proyek. Proyek ke-i berlangsung dari hari a[i] sampai hari b[i]
(kedua ujung termasuk, artinya proyek itu menempati hari a[i] hingga b[i]),
dan memberimu keuntungan p[i].
Kamu hanya bisa mengerjakan satu proyek pada satu hari, dan proyek yang
diambil harus dikerjakan utuh.
Cari TOTAL KEUNTUNGAN MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: a[i], b[i], dan p[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total keuntungan maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= b[i] <= 10^9
- 1 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
4
2 4 4
3 6 6
6 8 2
5 7 3

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
3
1 10 100
1 2 1
3 4 1

📎 SAMPLE OUTPUT 2:
100

💡 HINT: Sampel 2 dibuat khusus untuk menghancurkan greedy. Jalankan
         algoritma Exercise 1 di atasnya dan lihat hasilnya. Kenapa
         buktinya rusak begitu ada bobot?
         Kembali ke bukti exchange argument di teori: kita menukar satu
         interval dengan interval lain dan berkata "jumlahnya sama". Dengan
         bobot, kalimat itu tidak lagi berlaku.
         Jadi kamu butuh pendekatan lain. Urutkan tetap menurut waktu
         selesai, lalu untuk setiap proyek ada dua pilihan: ambil atau
         lewati. Kalau kamu mengambilnya, proyek terakhir yang masih boleh
         diambil sebelumnya adalah proyek yang selesai sebelum a[i].
         Menemukan proyek itu bisa dilakukan dengan cepat karena daftarnya
         sudah terurut.
         Perhatikan ujung TERTUTUP: proyek sebelumnya harus selesai pada
         hari yang benar-benar lebih kecil dari a[i].

🎯 Learning Goals:
- [ ] Mengenali sinyal "ada bobot" sebagai tanda DP
- [ ] Menyusun relasi ambil/lewati
- [ ] Memakai pencarian biner untuk menemukan pendahulu
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan menurut waktu selesai

    // TODO: dp ambil / lewati

    // TODO: cari pendahulu dengan pencarian biner

    return 0;
}
