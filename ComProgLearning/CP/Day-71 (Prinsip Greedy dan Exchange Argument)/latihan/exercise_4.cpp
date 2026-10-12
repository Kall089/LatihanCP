/*
============================================================
🏋️ Exercise 4: Mencari Contoh Tandingan
============================================================
Day: 71 | Difficulty: Medium
Topic: Membantah greedy dengan stress test
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan himpunan berisi N nilai koin yang BERBEDA (selalu memuat nilai 1)
dan sebuah target T.
Seorang teman mengusulkan strategi berikut untuk membayar tepat T dengan
koin sesedikit mungkin: "ambil terus koin dengan nilai TERBESAR yang tidak
melebihi sisa yang harus dibayar".
Tugasmu: tentukan apakah strategi itu memberikan hasil yang OPTIMAL untuk
target T pada himpunan koin ini.
Cetak "OPTIMAL" kalau strategi teman itu menghasilkan jumlah koin minimum,
atau cetak dua bilangan: jumlah koin menurut strategi teman dan jumlah koin
minimum sesungguhnya.

📥 INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N nilai koin

📤 OUTPUT FORMAT:
- "OPTIMAL", atau dua bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= N <= 20
- 1 <= T <= 10^4
- 1 <= nilai koin <= 10^4, salah satunya pasti 1

📎 SAMPLE INPUT 1:
3 6
1 3 4

📎 SAMPLE OUTPUT 1:
3 2

📎 SAMPLE INPUT 2:
4 30
1 5 10 25

📎 SAMPLE OUTPUT 2:
OPTIMAL

💡 HINT: Soal ini melatih kebiasaan paling berharga dari hari ini: JANGAN
         percaya dugaan greedy sebelum diuji.
         Bagian pertama mudah: simulasikan strategi temanmu apa adanya.
         Bagian kedua membutuhkan jawaban yang benar-benar optimal. Karena
         T paling besar 10^4, kamu punya ruang untuk pendekatan yang
         mencoba semua kemungkinan secara sistematis — pikirkan struktur
         yang sudah kamu kenal untuk "bayar tepat T dengan sesedikit
         mungkin benda, benda boleh dipakai berkali-kali".
         Setelah menyelesaikan soal ini, coba jalankan programmu pada
         himpunan koin acak dan lihat seberapa SERING greedy gagal. Angkanya
         mungkin mengejutkanmu.

🎯 Learning Goals:
- [ ] Membandingkan greedy dengan jawaban optimal secara terprogram
- [ ] Menyadari bahwa kebenaran greedy bergantung pada STRUKTUR soal
- [ ] Membangun kebiasaan menguji sebelum mempercayai
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: simulasikan strategi greedy

    // TODO: hitung jawaban optimal yang sesungguhnya

    // TODO: bandingkan keduanya

    return 0;
}
