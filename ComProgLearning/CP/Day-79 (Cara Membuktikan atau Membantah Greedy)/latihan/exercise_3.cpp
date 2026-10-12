/*
============================================================
🏋️ Exercise 3: Pengaruh Rentang Generator
============================================================
Day: 79 | Difficulty: Medium
Topic: Merancang generator yang memecahkan
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array berisi N bilangan. Definisikan JAWABAN BENAR sebagai
jumlah terbesar dari dua elemen array yang NILAINYA BERBEDA (kalau seluruh
elemen bernilai sama, jawabannya -1).
Sebuah kode yang salah menghitungnya sebagai jumlah dua elemen terbesar
tanpa memeriksa apakah nilainya berbeda.

Tugasmu: untuk sebuah batas B yang diberikan, hitung berapa persen dari
seluruh array yang mungkin dengan panjang N dan elemen dari 1 sampai B akan
membuat kode salah itu memberikan jawaban yang berbeda dari jawaban benar.
Karena jumlah array bisa sangat banyak, hitunglah secara TEPAT dengan
kombinatorika, bukan dengan pencacahan satu per satu.
Cetak persentasenya dengan enam angka di belakang koma.

📥 INPUT FORMAT:
- Satu baris berisi N dan B

📤 OUTPUT FORMAT:
- Satu bilangan real dengan enam angka di belakang koma

📏 CONSTRAINTS:
- 2 <= N <= 60
- 1 <= B <= 10^6

📎 SAMPLE INPUT 1:
2 3

📎 SAMPLE OUTPUT 1:
33.333333

📎 SAMPLE INPUT 2:
2 1000000

📎 SAMPLE OUTPUT 2:
0.000100

💡 HINT: Mulailah dengan menjawab pertanyaan yang lebih sederhana: KAPAN
         kode salah itu memberikan jawaban yang berbeda?
         Pikirkan baik-baik. Kode salah mengambil dua elemen terbesar. Ia
         berbeda dari jawaban benar hanya kalau kedua elemen terbesar itu
         bernilai SAMA. Rumuskan syarat itu dengan tepat dalam bahasa
         "berapa banyak elemen yang bernilai maksimum".
         Setelah syaratnya jelas, hitung berapa banyak array yang
         memenuhinya. Petunjuk: kelompokkan menurut nilai maksimumnya, lalu
         hitung berapa array dengan maksimum tepat sebesar itu dan muncul
         minimal dua kali.
         Trik yang sangat berguna: banyaknya array dengan seluruh elemen
         tidak melebihi m adalah m pangkat N. Dari situ kamu bisa
         menurunkan banyaknya array dengan maksimum TEPAT m.
         Perhatikan bahwa pembaginya adalah B pangkat N, yang bisa sangat
         besar. Jangan menghitung pembilang dan pembagi secara terpisah
         lalu membaginya — susun ulang rumusnya agar kamu bekerja dengan
         rasio langsung.
         Setelah selesai, lihat kedua sampel bersebelahan. Bug yang sama,
         generator berbeda, dan kesimpulan yang berlawanan. Itulah pelajaran
         terpenting hari ini.

🎯 Learning Goals:
- [ ] Merumuskan dengan tepat kapan sebuah bug terlihat
- [ ] Menghitung peluang bug tertangkap secara eksak
- [ ] Menyadari bahwa rentang generator menentukan kesimpulan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: rumuskan kapan kode salah itu terlihat salah

    // TODO: hitung peluangnya secara eksak, bekerja dengan rasio

    return 0;
}
