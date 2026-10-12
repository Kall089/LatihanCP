/*
============================================================
🏋️ Exercise 1: Menguji Klaim Tukar Uang
============================================================
Day: 79 | Difficulty: Easy
Topic: Membangun pembanding brute force
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N nilai koin BERBEDA (selalu memuat nilai 1) dan sebuah target T.
Seorang teman mengklaim: "ambil terus koin dengan nilai TERBESAR yang tidak
melebihi sisa" selalu menghasilkan jumlah koin minimum.
Tentukan apakah klaim itu benar untuk masukan ini.
Cetak "OPTIMAL" kalau strategi teman itu benar-benar minimum, atau dua
bilangan: jumlah koin menurut strategi teman dan jumlah koin minimum
sesungguhnya.

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

💡 HINT: Kerjakan bagian yang PASTI BENAR lebih dulu, yaitu jawaban optimal
         yang sesungguhnya. Batasan T paling besar 10^4 memberitahumu
         ukuran tabel yang dimaksud, dan kamu sudah mengenal polanya dari
         Day 145.
         Perhatikan bahwa koin boleh dipakai BERKALI-KALI. Itu menentukan
         arah loop pada tabelmu. Arah yang salah akan menghitung soal yang
         berbeda.
         Untuk bagian greedy, simulasikan saja apa adanya. Jangan
         "memperbaiki" strateginya — tugasmu menguji klaim, bukan
         memperbaikinya.
         Setelah selesai, lakukan ini: buat generator koin acak dan
         jalankan programmu ribuan kali. Catat berapa persen kasus yang
         TIDAK optimal. Angkanya sekitar sepuluh persen, dan itu angka
         yang layak kamu ingat seumur hidup.
         Renungkan artinya: kalau kamu menguji sebuah ide greedy pada lima
         sampel dan semuanya lolos, peluang idemu tetap salah masih sekitar
         separuh.

🎯 Learning Goals:
- [ ] Menulis pembanding yang pasti benar sebelum menguji greedy
- [ ] Menyadari arah loop menentukan soal yang berbeda
- [ ] Mengukur tingkat kegagalan greedy secara empiris
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung jawaban optimal yang PASTI BENAR lebih dulu

    // TODO: simulasikan strategi greedy apa adanya

    // TODO: bandingkan

    return 0;
}
