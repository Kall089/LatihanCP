/*
============================================================
🏋️ Exercise 4: Membagi Menjadi Dua Bagian Sama
============================================================
Day: 81 | Difficulty: Medium
Topic: Paritas sebagai penyaring, lalu konstruksi
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan n. Bagilah bilangan 1 sampai n menjadi DUA kelompok (keduanya
boleh kosong) sehingga JUMLAH bilangan di kedua kelompok SAMA.
Kalau bisa, cetak "YES" lalu ukuran kelompok pertama dan isinya.
Kalau tidak bisa, cetak "NO".
Kalau ada beberapa jawaban, cetak mana saja.

📥 INPUT FORMAT:
- Satu baris berisi n

📤 OUTPUT FORMAT:
- "NO", atau "YES" lalu baris berisi ukuran kelompok pertama, lalu baris
  berisi anggota kelompok pertama

📏 CONSTRAINTS:
- 1 <= n <= 10^6

📎 SAMPLE INPUT 1:
4

📎 SAMPLE OUTPUT 1:
YES
2
1 4

📎 SAMPLE INPUT 2:
2

📎 SAMPLE OUTPUT 2:
NO

💡 HINT: Kerjakan bagian yang MURAH lebih dulu. Total seluruh bilangan
         punya rumus tertutup yang kamu kenal. Agar bisa dibagi dua sama
         rata, apa syarat yang harus dipenuhi total itu?
         Syarat itu langsung menyelesaikan separuh kasus uji tanpa kerja
         sama sekali. Kebiasaan memeriksa kemustahilan lebih dulu sangat
         menghemat waktu.
         Untuk kasus yang mungkin, kamu perlu memilih sebagian bilangan
         yang jumlahnya tepat setengah total. Pendekatan serakah bekerja
         dengan baik di sini: ambil bilangan dari yang TERBESAR selama
         masih muat.
         Kenapa greedy ini pasti berhasil? Pikirkan: setelah mengambil
         bilangan-bilangan besar, sisa target yang perlu dipenuhi selalu
         lebih kecil dari bilangan berikutnya yang tersedia — dan karena
         bilangan 1 sampai sesuatu tersedia semua, target berapa pun bisa
         dicapai persis.
         Tuliskan alasan itu dengan rapi sebelum menulis kode. Itu bukti
         konstruksinya.
         Sampel 1 memberikan {1, 4} tetapi {2, 3} juga benar.

🎯 Learning Goals:
- [ ] Memeriksa kemustahilan lewat paritas sebelum bekerja
- [ ] Membuktikan bahwa konstruksi serakah selalu berhasil
- [ ] Menangani keluaran berformat majemuk
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: periksa paritas total

    // TODO: konstruksi serakah dari yang terbesar

    return 0;
}
