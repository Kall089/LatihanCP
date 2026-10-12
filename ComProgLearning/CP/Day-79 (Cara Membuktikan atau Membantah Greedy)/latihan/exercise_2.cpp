/*
============================================================
🏋️ Exercise 2: Mencari Contoh Tandingan Terkecil
============================================================
Day: 79 | Difficulty: Easy
Topic: Pengecilan otomatis
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah kapasitas W dan N barang dengan berat w[i] dan nilai v[i].
Diketahui bahwa strategi greedy "ambil terus barang dengan rasio nilai per
berat tertinggi yang masih muat" TIDAK optimal untuk masukan ini.
Carilah contoh tandingan yang PALING KECIL yang bisa diperoleh dari masukan
ini dengan dua jenis operasi:
  - menghapus sebuah barang
  - menurunkan berat atau nilai sebuah barang menjadi bilangan bulat
    positif yang lebih kecil
dengan syarat greedy tetap TIDAK optimal setelah operasi itu.
Ukuran sebuah masukan didefinisikan sebagai jumlah barang, lalu (bila jumlah
barangnya sama) sebagai jumlah seluruh berat dan nilai.
Cetak contoh tandingan terkecil yang kamu temukan, dalam urutan yang
dihasilkan prosedurmu (JANGAN diurutkan ulang).

Agar hasilnya bisa direproduksi, ikuti prosedur ini persis:
  - greedy membandingkan rasio dengan perkalian silang, dan bila rasionya
    SERI, barang berindeks lebih kecil didahulukan;
  - pada setiap putaran, coba dulu menghapus barang dari indeks terkecil
    ke terbesar; kalau ada yang berhasil, terima dan mulai putaran baru;
  - kalau tidak ada, coba kecilkan berat lalu nilai, dari indeks terkecil
    ke terbesar, dan untuk tiap barang coba nilai dari 1 ke atas;
  - berhenti kalau tidak ada langkah yang bisa diterima.
Kapasitas W tidak boleh diubah.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Baris pertama: jumlah barang pada contoh tandingan terkecil
- Baris berikutnya: masing-masing satu barang, w dan v

📏 CONSTRAINTS:
- 1 <= N <= 8
- 1 <= W <= 30
- 1 <= w[i], v[i] <= 20
- Dijamin greedy tidak optimal untuk masukan yang diberikan

📎 SAMPLE INPUT 1:
3 10
6 7
5 5
5 5

📎 SAMPLE OUTPUT 1:
3
6 6
5 2
5 5

📎 SAMPLE INPUT 2:
4 10
6 7
5 5
5 5
1 1

📎 SAMPLE OUTPUT 2:
3
6 6
5 2
5 5

💡 HINT: Ini bukan soal algoritma melainkan soal PERKAKAS. Kamu sedang
         membangun alat yang akan kamu pakai berkali-kali sepanjang
         latihanmu.
         Strateginya sederhana dan serakah: berulang kali coba lakukan satu
         langkah pengecilan; kalau setelah langkah itu greedy MASIH tidak
         optimal, terima pengecilannya dan ulangi dari awal.
         Berhentilah ketika tidak ada satu pun langkah pengecilan yang bisa
         diterima.
         Perhatikan bahwa kamu butuh dua fungsi yang sudah kamu tulis di
         Exercise 1: simulasi greedy, dan jawaban optimal.
         Waspadai satu jebakan halus. Naluri dari Day 76 mengatakan
         "urutkan keluaran agar deterministik". DI SINI itu justru bisa
         MERUSAK jawabannya — pikirkan kenapa, mengingat greedy memakai
         tie-break indeks saat rasionya seri.
         Determinisme di sini datang dari prosedur yang tetap, bukan dari
         mengurutkan hasilnya.
         Kenapa contoh kecil begitu berharga? Karena ia bisa DIPAHAMI. Kamu
         bisa melihat dengan mata telanjang kenapa greedy gagal, dan itu
         berubah menjadi intuisi yang terbawa ke soal berikutnya.
         Sampel 2 menguji apakah alatmu bisa membuang barang yang tidak
         berpengaruh.

🎯 Learning Goals:
- [ ] Membangun perkakas pengecilan yang bisa dipakai ulang
- [ ] Memahami kenapa contoh tandingan kecil lebih berharga
- [ ] Menghasilkan keluaran deterministik
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: fungsi greedy dan fungsi optimal

    // TODO: berulang kali coba buang barang atau kecilkan nilainya

    // TODO: keluarkan hasil yang deterministik

    return 0;
}
