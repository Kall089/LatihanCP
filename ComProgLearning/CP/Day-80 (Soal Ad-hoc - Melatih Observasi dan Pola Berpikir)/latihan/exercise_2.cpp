/*
============================================================
🏋️ Exercise 2: Jumlah Seluruh Subarray
============================================================
Day: 80 | Difficulty: Easy
Topic: Hitung sumbangan, bukan objek
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan. Untuk setiap subarray (bagian kontigu tak
kosong), hitung jumlah elemennya. Lalu jumlahkan seluruh nilai itu.
Cetak hasilnya modulo 10^9 + 7.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan modulo 10^9 + 7

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3
1 2 3

📎 SAMPLE OUTPUT 1:
20

📎 SAMPLE INPUT 2:
1
5

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Pendekatan langsung menghitung setiap subarray membutuhkan N
         kuadrat langkah. Dengan N sampai 10^6 itu jelas tidak mungkin.
         Balik cara berpikirmu. Alih-alih bertanya "berapa sumbangan tiap
         subarray", tanyakan "berapa kali tiap ELEMEN ikut terhitung".
         Untuk elemen di posisi ke-i, sebuah subarray memuatnya kalau ujung
         kirinya berada di suatu tempat dan ujung kanannya di suatu tempat.
         Berapa pilihan untuk masing-masing?
         Kalikan kedua bilangan itu, dan kamu punya jawabannya.
         Verifikasi rumusmu dengan tangan pada sampel 1 sebelum menulis
         kode: hitung berapa kali angka 1, 2, dan 3 masing-masing muncul.
         Hati-hati dengan modulo: hasil kali (i+1) dikali (n-i) dikali a[i]
         bisa melampaui long long kalau tidak di-mod bertahap.

🎯 Learning Goals:
- [ ] Membalik urutan penjumlahan
- [ ] Menurunkan rumus sumbangan tiap posisi
- [ ] Mengelola modulo pada perkalian bertingkat
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap elemen, berapa subarray yang memuatnya?

    return 0;
}
