/*
============================================================
🏋️ Exercise 6: Kerangka Stress Test Generik
============================================================
Day: 79 | Difficulty: Hard (Contest-level)
Topic: Membangun perkakas yang dipakai selamanya
Time Limit: 5 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Bangun sebuah program yang menjalankan stress test untuk beberapa soal
sekaligus, lalu melaporkan hasilnya.

Program menerima sebuah nomor soal S dan jumlah iterasi ITER, lalu:
  - membangkitkan ITER masukan acak untuk soal S,
  - menjalankan strategi greedy dan jawaban optimal pada tiap masukan,
  - menghitung berapa kali keduanya berbeda,
  - mencari contoh tandingan TERKECIL di antara yang berbeda,
  - mencetak laporannya.

Soal yang harus didukung:
  S = 1 : knapsack 0/1, greedy rasio nilai per berat tertinggi
  S = 2 : tukar uang, greedy koin terbesar
  S = 3 : interval saling lepas, greedy interval terpendek dulu

Gunakan generator dengan nilai KECIL (1 sampai 12) dan ukuran kecil
(1 sampai 8) agar contoh tandingan sering muncul.
Gunakan bilangan acak yang deterministik dengan benih tetap 20240817 agar
hasilnya bisa direproduksi.

📥 INPUT FORMAT:
- Satu baris berisi S dan ITER

📤 OUTPUT FORMAT:
- Baris pertama: jumlah kegagalan dan jumlah iterasi, dipisah spasi
- Baris kedua: ukuran contoh tandingan terkecil (jumlah elemen), atau -1
  kalau tidak ada kegagalan

📏 CONSTRAINTS:
- 1 <= S <= 3
- 1 <= ITER <= 20000

📎 SAMPLE INPUT 1:
1 1000

📎 SAMPLE OUTPUT 1:
(bergantung implementasimu — tidak ada jawaban tunggal)

💡 HINT: Soal ini sengaja tidak punya jawaban tunggal, karena tujuannya
         BUKAN mendapat AC melainkan membangun perkakas yang akan kamu
         simpan dan pakai berkali-kali.
         Rancang kodenya agar bagian yang berubah antar soal hanya TIGA
         hal: cara membangkitkan masukan, cara menjalankan greedy, dan cara
         menghitung jawaban optimal. Sisanya harus sama persis untuk soal
         apa pun.
         Di C++, cara paling rapi adalah membuat fungsi bertemplat yang
         menerima tiga objek fungsi. Kalau itu terasa rumit, tiga fungsi
         biasa dengan sebuah percabangan juga cukup — yang penting
         strukturnya terpisah.
         Untuk pengecilan contoh tandingan, pakai kembali gagasan Exercise
         2: berulang kali coba buang atau kecilkan, terima kalau masih
         gagal.
         Setelah selesai, salin kerangka ini ke dalam berkas templatemu
         sendiri. Perkakas yang siap pakai adalah perbedaan antara
         "seharusnya aku uji" dan "sudah kuuji".
         Sebagai perluasan: tambahkan mode yang menguji beberapa RENTANG
         nilai berbeda untuk soal yang sama, lalu bandingkan persentase
         kegagalannya. Kamu akan melihat sendiri bahwa rentang generator
         mengubah kesimpulan.

🎯 Learning Goals:
- [ ] Memisahkan bagian yang berubah dari bagian yang tetap
- [ ] Membangun perkakas yang bisa dipakai ulang tanpa ditulis ulang
- [ ] Menjadikan stress test kebiasaan, bukan usaha khusus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerangka umum yang menerima generator, greedy, dan optimal

    // TODO: tiga soal, masing-masing hanya mengisi tiga bagian itu

    // TODO: pengecilan contoh tandingan

    return 0;
}
