/*
============================================================
🏋️ Exercise 1: Hitung Pertukaran Bubble Sort
============================================================
Day: 43 | Difficulty: Easy
Topic: Bubble sort + jumlah swap
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Jalankan bubble sort pada array
tersebut dan hitung BERAPA KALI operasi pertukaran (swap) dilakukan.
Bubble sort yang dimaksud adalah versi baku: berulang kali menyapu array
dari kiri ke kanan, menukar setiap pasangan berdampingan yang urutannya
terbalik, sampai tidak ada lagi pertukaran.
Cetak jumlah pertukaran itu, lalu cetak array setelah terurut.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Baris pertama: jumlah pertukaran
- Baris kedua: N bilangan yang sudah terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 2000
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
5 1 4 2

📎 SAMPLE OUTPUT 1:
4
1 2 4 5

📎 SAMPLE INPUT 2:
3
1 2 3

📎 SAMPLE OUTPUT 2:
0
1 2 3

💡 HINT: Perhatikan batas loop dalamnya. Setelah putaran ke-i, sebanyak i
         elemen terbesar sudah berada di posisi akhirnya, jadi kamu tidak
         perlu menyapu bagian itu lagi.
         Setelah selesai, coba hitung sendiri berapa pasangan (i, j) dengan
         i < j dan a[i] > a[j] pada array ASLI. Angkanya akan menarik.

🎯 Learning Goals:
- [ ] Menulis bubble sort dengan batas loop yang benar
- [ ] Menemukan sendiri hubungan swap dengan inversi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca array

    // TODO: bubble sort, hitung swap. Perhatikan batas j+1 < n-i

    // TODO: cetak jumlah swap lalu array

    return 0;
}
