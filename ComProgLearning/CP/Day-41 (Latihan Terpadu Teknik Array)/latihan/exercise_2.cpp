/*
============================================================
🏋️ Exercise 2: Pengecatan Pagar
============================================================
Day: 41 | Difficulty: Easy
Topic: difference array (Day 31) + counting (Day 40)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pagar terdiri dari N papan bernomor 1 sampai N, semuanya awalnya
memiliki 0 lapis cat. Ada Q perintah pengecatan; perintah ke-i berbunyi
"cat papan L sampai R sebanyak V lapis tambahan".

Setelah SEMUA perintah dijalankan, tentukan:
  1. jumlah lapis terbanyak yang dimiliki sebuah papan
  2. ada berapa papan yang memiliki jumlah lapis sebanyak itu

Perhatikan batasannya: N dan Q sama-sama besar, sehingga menjalankan setiap
perintah secara harfiah (loop dari L ke R) akan memakan O(N·Q) dan TLE.
Kuncinya adalah semua query baru ditanyakan SETELAH semua update selesai.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Q baris berikutnya: L, R, dan V

📤 OUTPUT FORMAT:
- Dua bilangan: lapis terbanyak, lalu banyaknya papan yang mencapainya

📏 CONSTRAINTS:
- 1 ≤ N, Q ≤ 2·10^5
- 1 ≤ L ≤ R ≤ N
- 1 ≤ V ≤ 10^9

📎 SAMPLE INPUT 1:
5 3
1 3 5
2 4 3
5 5 2

📎 SAMPLE OUTPUT 1:
8 2

📎 SAMPLE INPUT 2:
4 1
1 4 7

📎 SAMPLE OUTPUT 2:
7 4

📎 SAMPLE INPUT 3:
3 2
1 1 10
3 3 10

📎 SAMPLE OUTPUT 3:
10 2

💡 HINT: Simpan SELISIH antar papan bertetangga, bukan nilai papannya.
         Satu perintah cuma menyentuh dua posisi.

🎯 Learning Goals:
- [ ] Update rentang dalam O(1)
- [ ] Memahami kenapa array selisih berukuran N+1
- [ ] Menggabungkan hasil finalisasi dengan penghitungan frekuensi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan Q

    // TODO: Bangun difference array berukuran N+2 (aman untuk d[R+1])
    // Hint: satu perintah = d[L] += V, d[R+1] -= V

    // TODO: Finalisasi dengan prefix sum berjalan, sambil melacak
    //       nilai maksimum dan berapa kali nilai itu muncul

    // Hati-hati: V sampai 10^9 dikali 2*10^5 perintah -> pakai long long

    return 0;
}
