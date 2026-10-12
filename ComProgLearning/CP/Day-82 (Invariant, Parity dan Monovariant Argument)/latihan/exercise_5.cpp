/*
============================================================
🏋️ Exercise 5: Proses Pasti Berhenti
============================================================
Day: 82 | Difficulty: Hard
Topic: Monovarian
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tumpukan koin; tumpukan ke-i berisi a[i] koin.
Satu langkah dilakukan sebagai berikut: ambil TEPAT SATU koin dari SETIAP
tumpukan yang tidak kosong, lalu bentuk tumpukan BARU berisi koin-koin yang
baru saja diambil.
Keadaan dianggap STABIL kalau setelah satu langkah, susunan ukuran tumpukan
(diurutkan menaik) tidak berubah.
Cari BERAPA LANGKAH yang dibutuhkan sampai keadaan menjadi stabil.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah langkah sampai stabil

📏 CONSTRAINTS:
- 1 <= N <= 500
- 1 <= a[i] <= 500
- Total seluruh koin tidak melebihi 10^5
- Dijamin total seluruh koin merupakan BILANGAN SEGITIGA, yaitu berbentuk
  k dikali (k+1) dibagi 2 untuk suatu bilangan bulat k

📎 SAMPLE INPUT 1:
3
3 1 2

📎 SAMPLE OUTPUT 1:
0

📎 SAMPLE INPUT 2:
1
6

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
2
5 5

📎 SAMPLE OUTPUT 3:
6

💡 HINT: Pertanyaan pertama yang harus kamu jawab: apakah prosesnya PASTI
         berhenti? Kalau tidak, soal ini tidak punya jawaban.
         Untuk membuktikannya, cari MONOVARIAN — besaran bilangan bulat
         non-negatif yang selalu turun (atau selalu naik dan terbatas di
         atas).
         Petunjuk: pikirkan tentang jumlah kuadrat selisih terhadap
         susunan target, atau tentang berapa banyak pasangan tumpukan yang
         "salah urutan". Salah satu besaran itu bergerak satu arah.
         Perhatikan bahwa TOTAL koin tidak pernah berubah — itu invarian,
         dan ia membatasi keadaan akhirnya.
         Pertanyaan kedua: seperti apa keadaan stabilnya? Coba beberapa
         contoh kecil dengan tangan dan cari polanya. Jawabannya sangat
         teratur, dan itulah alasan soal ini MENJAMIN total koin berupa
         bilangan segitiga — tanpa jaminan itu, prosesnya bisa berputar
         dalam siklus dan tidak pernah stabil. Coba sendiri dengan total
         4 koin dan lihat apa yang terjadi.
         Setelah kamu tahu bentuk keadaan stabilnya, kamu punya dua pilihan:
         mensimulasikan sampai mencapainya, atau menghitung langsung. Karena
         total koin dibatasi 10^5, simulasi masih layak — tetapi kamu perlu
         yakin bahwa jumlah langkahnya tidak terlalu besar. Monovarian yang
         kamu temukan tadi memberi batas atas itu.
         Kasus tepi: keadaan yang SUDAH stabil sejak awal (sampel 1).

🎯 Learning Goals:
- [ ] Membuktikan proses berhenti dengan monovarian
- [ ] Memakai monovarian untuk membatasi jumlah langkah simulasi
- [ ] Mengenali bentuk keadaan stabil lewat percobaan kecil
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: buktikan proses berhenti (monovarian)

    // TODO: simulasikan sampai stabil

    return 0;
}
