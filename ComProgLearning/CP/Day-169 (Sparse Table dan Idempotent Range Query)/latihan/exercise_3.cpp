/*
============================================================
🏋️ Exercise 3: GCD pada Rentang
============================================================
Day: 169 | Difficulty: Medium
Topic: Sparse table dengan operasi selain min
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat POSITIF dan Q pertanyaan rentang
[a, b] (1-based, inklusif). Untuk setiap pertanyaan, cetak faktor persekutuan
terbesar (GCD) dari seluruh elemen pada rentang tersebut.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: a dan b

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- 1 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
5 3
12 18 6 24 36
1 3
2 5
4 4

📎 SAMPLE OUTPUT 1:
6
6
24

💡 HINT: Pertanyaan pertama yang harus kamu jawab: apakah operasi GCD
         memenuhi syarat yang membuat struktur blok pangkat dua sah dipakai?
         Uji dengan mengambil sebuah bilangan dan menerapkan operasi itu
         pada dirinya sendiri.
         Kalau syaratnya terpenuhi, seluruh struktur dari Exercise 1 bisa
         dipakai apa adanya — kamu hanya mengganti satu fungsi.
         Perhatikan bahwa GCD dari sebuah rentang tidak pernah lebih besar
         daripada elemen terkecilnya, dan bisa turun sangat cepat.
         Bonus untuk dipikirkan: berapa banyak NILAI GCD BERBEDA yang
         mungkin muncul kalau kamu menetapkan ujung kiri dan menggeser ujung
         kanan? Jawabannya jauh lebih kecil dari N, dan fakta itu adalah
         dasar dari banyak soal GCD lanjutan.

🎯 Learning Goals:
- [ ] Memverifikasi idempotensi sebuah operasi sebelum memakainya
- [ ] Memakai struktur yang sama untuk operasi berbeda
- [ ] Mengenal sifat "GCD hanya berubah sedikit kali"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: struktur yang sama, operasi diganti

    return 0;
}
