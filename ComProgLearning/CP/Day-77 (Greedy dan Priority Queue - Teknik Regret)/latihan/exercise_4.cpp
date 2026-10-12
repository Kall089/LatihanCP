/*
============================================================
🏋️ Exercise 4: Modal Bertumbuh
============================================================
Day: 77 | Difficulty: Medium
Topic: Dua struktur bekerja sama
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki modal awal C dan boleh menjalankan PALING BANYAK K proyek.
Proyek ke-i hanya boleh dijalankan kalau modalmu saat itu minimal m[i], dan
setelah selesai ia menambah modalmu sebesar p[i] (modal tidak berkurang).
Setiap proyek hanya boleh dijalankan sekali, dan kamu bebas memilih
urutannya.
Cari MODAL AKHIR MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N, K, dan C
- N baris berikutnya: m[i] dan p[i]

📤 OUTPUT FORMAT:
- Satu bilangan: modal akhir maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= K <= 10^5
- 0 <= C <= 10^9
- 0 <= m[i] <= 10^9
- 0 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
3 2 0
0 1
1 2
1 3

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
2 5 100
1000 1
2000 2

📎 SAMPLE OUTPUT 2:
100

💡 HINT: Kalau semua proyek terjangkau sejak awal, jawabannya mudah: ambil
         K keuntungan terbesar. Yang membuat soal ini menarik adalah bahwa
         himpunan proyek yang TERJANGKAU membesar seiring modalmu naik.
         Jadi kamu butuh dua kumpulan yang berbeda: proyek yang belum
         terjangkau, dan proyek yang sudah terjangkau.
         Untuk kumpulan pertama, apa yang kamu butuhkan? Kamu ingin tahu
         proyek mana yang menjadi terjangkau saat modal naik ke nilai baru.
         Struktur apa yang paling cocok?
         Untuk kumpulan kedua, kamu selalu butuh yang keuntungannya
         terbesar. Struktur apa yang cocok?
         Pengamatan yang membuat ini cepat: modal hanya MEMBESAR, tidak
         pernah mengecil. Apa artinya bagi penunjuk yang memindahkan proyek
         dari kumpulan pertama ke kumpulan kedua?
         Sampel 2 menguji kasus ketika tidak ada proyek yang terjangkau
         sama sekali. Pastikan kodemu berhenti, bukan berputar.

🎯 Learning Goals:
- [ ] Mengoordinasikan dua struktur data dengan peran berbeda
- [ ] Memanfaatkan monotonisitas agar penunjuk tidak perlu mundur
- [ ] Menangani kasus tidak ada pilihan yang tersedia
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kumpulan proyek belum terjangkau

    // TODO: kumpulan proyek sudah terjangkau

    // TODO: penunjuk monoton memindahkan antar keduanya

    return 0;
}
