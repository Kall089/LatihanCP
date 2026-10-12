/*
============================================================
🏋️ Exercise 6: Menjadwalkan dengan Mesin Ganda
============================================================
Day: 77 | Difficulty: Hard (Contest-level)
Topic: Regret dengan kapasitas lebih dari satu
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan dan M mesin identik yang bekerja paralel.
Setiap pekerjaan memerlukan TEPAT SATU satuan waktu. Pekerjaan ke-i
memberi keuntungan p[i] dan harus dikerjakan pada salah satu slot waktu
1 sampai d[i].
Pada setiap slot waktu, PALING BANYAK M pekerjaan bisa dikerjakan
bersamaan (satu per mesin).
Cari TOTAL KEUNTUNGAN MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- N baris berikutnya: d[i] dan p[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total keuntungan maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= M <= 10^5
- 1 <= d[i] <= N
- 1 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
4 2
1 10
1 20
1 30
2 5

📎 SAMPLE OUTPUT 1:
55

📎 SAMPLE INPUT 2:
3 1
1 5
1 5
1 5

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Ini Exercise 2 dengan satu perubahan kecil pada aturannya, dan
         perubahan itu masuk ke dalam kodemu pada tepat SATU tempat.
         Pada Exercise 2, batasannya adalah "jumlah pekerjaan terpilih
         tidak melebihi tenggat sekarang". Dengan M mesin, berapa banyak
         pekerjaan yang bisa diselesaikan sampai waktu d?
         Setelah kamu menjawab itu, sisanya identik.
         Tapi berhati-hatilah: buktinya juga harus diperiksa ulang. Apakah
         "memeriksa prefiks" masih cukup untuk menjamin seluruh jadwal
         layak ketika ada M mesin? Tuliskan alasannya sebelum melanjutkan.
         Sampel 1 memakai M = 2 dengan tiga pekerjaan bertenggat 1. Hitung
         dengan tangan: berapa yang muat di slot 1, dan berapa di slot 2?
         Sebagai pemeriksaan tambahan, jalankan kodemu dengan M = 1 dan
         bandingkan dengan solusi Exercise 2 pada masukan acak yang sama.
         Keduanya harus memberi hasil identik.

🎯 Learning Goals:
- [ ] Memperluas regret dari kapasitas 1 ke kapasitas M
- [ ] Memeriksa ulang bukti setelah mengubah batasan
- [ ] Memverifikasi kasus khusus terhadap solusi yang sudah benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sesuaikan syarat kapasitas untuk M mesin

    return 0;
}
