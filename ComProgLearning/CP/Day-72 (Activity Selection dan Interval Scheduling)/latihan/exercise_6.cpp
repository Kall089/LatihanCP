/*
============================================================
🏋️ Exercise 6: Menyewakan Mesin
============================================================
Day: 72 | Difficulty: Hard (Contest-level)
Topic: Menggabungkan tiga pola interval
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki K mesin identik. Ada N permintaan sewa; permintaan ke-i
memakai sebuah mesin dari waktu l[i] sampai r[i] (setengah terbuka: mesin
bebas kembali tepat pada r[i]) dan memberimu bayaran p[i].
Kamu boleh MENOLAK permintaan mana pun. Setiap permintaan yang diterima
harus dilayani utuh oleh tepat satu mesin.
Cari TOTAL BAYARAN MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: l[i], r[i], dan p[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total bayaran maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= K <= 50
- 1 <= l[i] < r[i] <= 10^9
- 1 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
4 1
1 4 4
3 6 6
5 7 3
6 8 2

📎 SAMPLE OUTPUT 1:
8

📎 SAMPLE INPUT 2:
3 2
1 10 5
2 3 4
4 5 4

📎 SAMPLE OUTPUT 2:
13

💡 HINT: Soal ini menggabungkan tiga hal yang kamu pelajari hari ini:
         penolakan (Exercise 1), bobot (Exercise 5), dan banyak sumber daya
         (Exercise 3 dan 4).
         Perhatikan batasannya: N <= 2000 dan K <= 50. Batasan sekecil ini
         adalah petunjuk keras — ini BUKAN soal greedy, dan bahkan
         solusinya boleh berkompleksitas sekitar N*N atau N*K*sesuatu.
         Sebuah pendekatan yang bekerja: setelah semua waktu dikompresi,
         pikirkan keadaan sebagai "sudah sampai waktu t, dan ada berapa
         mesin yang masih bebas". Tapi keadaan seperti itu sulit karena
         mesin bebas pada waktu yang berbeda-beda.
         Alternatif yang lebih rapi: pikirkan berapa banyak permintaan yang
         boleh saling menindih pada satu titik waktu, lalu cari cara
         memaksimalkan bayaran dengan batasan tindihan itu.
         Kalau kamu menemukan bahwa batasnya berbentuk "pada tiap titik
         waktu, paling banyak K interval terpilih yang menindih", kamu sudah
         sangat dekat. Salah satu cara menyelesaikannya memakai DP di atas
         waktu terkompresi dengan dimensi tambahan.

🎯 Learning Goals:
- [ ] Menggabungkan beberapa pola interval dalam satu soal
- [ ] Membaca batasan sebagai petunjuk kompleksitas yang diharapkan
- [ ] Merumuskan keadaan DP untuk sumber daya jamak
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kompresi koordinat waktu

    // TODO: rumuskan keadaan yang menangkap batas K tindihan

    // TODO: DP

    return 0;
}
