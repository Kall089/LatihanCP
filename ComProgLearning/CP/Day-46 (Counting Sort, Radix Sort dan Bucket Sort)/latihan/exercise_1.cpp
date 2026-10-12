/*
============================================================
🏋️ Exercise 1: Urutkan Umur
============================================================
Day: 46 | Difficulty: Easy
Topic: Counting sort dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah sensus mencatat umur N penduduk. Setiap umur adalah bilangan bulat
antara 1 dan 100. Urutkan seluruh umur itu secara menaik dan cetak hasilnya
dalam satu baris.
Perhatikan bahwa N bisa sangat besar (sampai 2 juta) sementara rentang
nilainya sangat kecil. Manfaatkan fakta itu — mengurutkan dengan
perbandingan adalah pekerjaan yang tidak perlu di sini.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^6
- 1 <= umur <= 100

📎 SAMPLE INPUT 1:
5
3 4 2 1 5

📎 SAMPLE OUTPUT 1:
1 2 3 4 5

📎 SAMPLE INPUT 2:
6
30 20 10 20 30 50

📎 SAMPLE OUTPUT 2:
10 20 20 30 30 50

💡 HINT: Kamu tidak perlu membandingkan satu elemen pun. Hitung berapa kali
         setiap umur muncul, lalu cetak umur 1 sebanyak hitungannya, umur 2
         sebanyak hitungannya, dan seterusnya.
         Dengan N sebesar ini, perhatikan juga cara kamu mencetak: mencetak
         2 juta bilangan satu per satu dengan cout bisa jauh lebih lambat
         daripada membangun satu string lalu mencetaknya sekali.

🎯 Learning Goals:
- [ ] Menyadari kapan perbandingan sama sekali tidak diperlukan
- [ ] Menghitung O(n + V) dan membandingkannya dengan O(n log n)
- [ ] Menangani keluaran berukuran besar dengan efisien
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: array frekuensi berukuran 101

    // TODO: cetak tiap nilai sebanyak frekuensinya

    return 0;
}
