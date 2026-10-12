/*
============================================================
🏋️ Exercise 6: Denda dengan Waktu Rilis
============================================================
Day: 78 | Difficulty: Hard (Contest-level)
Topic: Waktu rilis + bitmask
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan pada satu mesin. Pekerjaan ke-i baru TERSEDIA mulai waktu
r[i], memerlukan t[i] satuan waktu, punya tenggat d[i], dan denda w[i] yang
dibayar kalau ia selesai setelah tenggatnya.
Mesin boleh menganggur menunggu sebuah pekerjaan tersedia. Sekali dimulai
sebuah pekerjaan harus diselesaikan tanpa jeda.
Seluruh pekerjaan harus dikerjakan.
Cari TOTAL DENDA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: r[i], t[i], d[i], dan w[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total denda minimum

📏 CONSTRAINTS:
- 1 <= N <= 18
- 0 <= r[i] <= 10^9
- 1 <= t[i] <= 10^9
- 1 <= d[i] <= 10^18
- 1 <= w[i] <= 10^9

📎 SAMPLE INPUT 1:
3
0 3 3 5
0 3 4 10
0 3 5 1

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
2
0 1 1 5
5 1 6 7

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
2
0 5 5 3
1 1 2 100

📎 SAMPLE OUTPUT 3:
3

💡 HINT: Perhatikan batasannya lebih dulu: N paling besar 18. Angka itu
         adalah petunjuk yang sangat spesifik — hanya satu keluarga
         pendekatan yang masuk akal dengan batasan seperti itu.
         Kenapa tidak bisa memakai pendekatan Exercise 4? Karena waktu
         rilis membuat "waktu sekarang" tidak lagi sama dengan jumlah
         durasi yang sudah dikerjakan: mesin bisa menganggur menunggu.
         Pengamatan kunci untuk pendekatan bitmask: kalau kamu sudah tahu
         HIMPUNAN pekerjaan mana yang sudah dikerjakan, apakah kamu bisa
         menentukan waktu sekarang secara unik? Pikirkan baik-baik —
         jawabannya berbeda dari soal tanpa waktu rilis.
         Petunjuk: kamu bisa, asalkan kamu melacaknya sebagai bagian dari
         nilai yang dihitung, bukan menghitungnya ulang dari himpunan.
         Jadi rumuskan tabelmu sebagai: untuk tiap himpunan, berapa denda
         minimum, dan berapa waktu selesai yang menyertainya.
         Hati-hati: dua besaran itu bisa bertentangan. Sebuah jadwal dengan
         denda lebih kecil bisa berakhir lebih lambat. Pikirkan apakah
         kamu perlu menyimpan keduanya, atau apakah salah satunya sudah
         ditentukan oleh himpunannya.
         Sampel 3 dibuat khusus untuk menguji apakah kamu benar-benar
         menangani waktu rilis: pekerjaan kedua baru tersedia pada waktu 1
         tetapi tenggatnya 2.

🎯 Learning Goals:
- [ ] Membaca batasan n <= 18 sebagai tanda bitmask
- [ ] Menyadari bahwa waktu rilis merusak asumsi "waktu = jumlah durasi"
- [ ] Merumuskan keadaan yang cukup untuk menentukan transisi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: keadaan berupa himpunan pekerjaan yang sudah dikerjakan

    // TODO: tentukan apa yang harus disimpan bersama tiap himpunan

    return 0;
}
