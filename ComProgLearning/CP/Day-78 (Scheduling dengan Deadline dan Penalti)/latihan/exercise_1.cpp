/*
============================================================
🏋️ Exercise 1: Keterlambatan Terkecil
============================================================
Day: 78 | Difficulty: Easy
Topic: EDF (Earliest Deadline First)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan yang SEMUANYA harus dikerjakan pada satu mesin, satu per
satu tanpa jeda, mulai dari waktu 0. Pekerjaan ke-i memerlukan t[i] satuan
waktu dan punya tenggat d[i].
Kalau pekerjaan ke-i selesai pada waktu C, keterlambatannya didefinisikan
sebagai C - d[i] (boleh bernilai negatif kalau selesai lebih awal).
Susun urutan pengerjaan sehingga KETERLAMBATAN TERBESAR di antara seluruh
pekerjaan menjadi sekecil mungkin, lalu cetak nilai itu.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i] dan d[i]

📤 OUTPUT FORMAT:
- Satu bilangan: keterlambatan terbesar minimum (boleh negatif)

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= t[i] <= 10^9
- 1 <= d[i] <= 10^18

📎 SAMPLE INPUT 1:
3
3 6
2 8
1 9

📎 SAMPLE OUTPUT 1:
-3

📎 SAMPLE INPUT 2:
2
5 1
5 100

📎 SAMPLE OUTPUT 2:
4

💡 HINT: Ada tiga dugaan yang terasa masuk akal: urutkan durasi menaik,
         urutkan tenggat menaik, atau urutkan menurut selisih tenggat
         dikurangi durasi. Uji ketiganya pada sampel 2.
         Kalau lebih dari satu bertahan, buat masukan kecil lain dan
         bandingkan dengan brute force atas seluruh permutasi. Untuk n
         sampai 7 itu sangat cepat.
         Setelah menemukan yang bertahan, buktikan dengan exchange
         argument. Ambil dua pekerjaan berdampingan yang melanggar
         kriteriamu, tukar, lalu bandingkan keterlambatan terbesar sebelum
         dan sesudah.
         Petunjuk untuk buktinya: setelah ditukar, salah satu keterlambatan
         pasti TURUN. Yang perlu kamu tunjukkan adalah bahwa yang satunya,
         meski naik, tetap tidak melebihi nilai maksimum yang lama.
         Kamu mungkin terkejut menemukan bahwa durasi sama sekali tidak
         muncul dalam kriteria akhirnya.
         Perhatikan bahwa jawabannya BOLEH NEGATIF (sampel 1). Jangan
         menginisialisasi maksimum dengan nol.

🎯 Learning Goals:
- [ ] Menurunkan kriteria EDF lewat exchange argument
- [ ] Menyadari bahwa durasi tidak memengaruhi urutan optimal
- [ ] Menangani nilai negatif dan tipe data besar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan kriteria pengurutan, jangan menebak

    // TODO: sapu sekali; hati-hati dengan nilai awal maksimum

    return 0;
}
