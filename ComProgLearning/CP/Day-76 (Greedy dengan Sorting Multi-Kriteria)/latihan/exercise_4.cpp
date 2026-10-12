/*
============================================================
🏋️ Exercise 4: Pekerjaan Dua Tahap
============================================================
Day: 76 | Difficulty: Medium
Topic: Menurunkan kriteria pengurutan, bukan menebaknya
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan. Pekerjaan ke-i memerlukan dua tahap:
  - Tahap pertama membutuhkan a[i] satuan waktu pada SATU mesin bersama.
    Mesin ini hanya bisa mengerjakan satu tahap pertama pada satu waktu.
  - Tahap kedua membutuhkan b[i] satuan waktu dan dikerjakan secara
    PARALEL tanpa batas: tahap kedua sebuah pekerjaan dimulai tepat
    setelah tahap pertamanya selesai, dan tidak bersaing dengan pekerjaan
    mana pun.
Kamu bebas memilih urutan pengerjaan tahap pertama.
Cari WAKTU SELESAI TERAKHIR (saat seluruh pekerjaan sudah selesai tahap
keduanya) yang paling kecil.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: a[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu bilangan: waktu selesai terakhir minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i], b[i] <= 10^9

📎 SAMPLE INPUT 1:
3
1 3
2 1
3 2

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
1
5 5

📎 SAMPLE OUTPUT 2:
10

💡 HINT: Ada tiga dugaan yang terasa masuk akal: urutkan a menaik
         (kerjakan yang cepat dulu), urutkan a+b menurun, atau urutkan
         menurut rasio a/b. Uji ketiganya pada sampel 1.
         Kalau semuanya kebetulan benar di situ, buat masukan kecil lain
         dan bandingkan dengan brute force atas seluruh permutasi. Untuk
         n sampai 7 itu masih sangat cepat.
         Setelah menemukan kriteria yang bertahan, buktikan dengan
         exchange argument. Ambil dua pekerjaan BERDAMPINGAN, tuliskan
         waktu selesai terakhir untuk kedua urutan, lalu kurangkan.
         Petunjuk aljabar: bagian yang memuat waktu mesin sebelum kedua
         pekerjaan itu, dan bagian yang memuat jumlah a keduanya, akan
         saling hilang. Yang tersisa adalah perbandingan yang sangat
         sederhana.
         Kamu mungkin terkejut menemukan bahwa salah satu dari a atau b
         SAMA SEKALI tidak muncul dalam kriteria akhirnya.

🎯 Learning Goals:
- [ ] Menolak menebak kriteria pengurutan
- [ ] Menurunkan kriteria lewat exchange argument pada max
- [ ] Memakai brute force permutasi sebagai penemu kriteria
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan kriteria pengurutan lewat exchange argument

    // TODO: sapu sekali sambil melacak maksimum

    return 0;
}
