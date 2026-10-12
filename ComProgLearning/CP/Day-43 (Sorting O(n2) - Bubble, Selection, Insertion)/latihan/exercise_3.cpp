/*
============================================================
🏋️ Exercise 3: Menyusun Kartu Bertahap
============================================================
Day: 43 | Difficulty: Medium
Topic: Insertion sort, keadaan setelah tiap langkah
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu sedang menyusun kartu di tangan dengan cara insertion sort: kartu
diambil satu per satu dari kiri ke kanan, dan setiap kartu baru disisipkan
ke posisi yang tepat di antara kartu-kartu yang sudah tersusun.
Diberikan susunan awal N kartu, cetak keadaan array SETELAH setiap kartu
disisipkan, mulai dari penyisipan kartu kedua sampai kartu terakhir.
Jadi akan ada N-1 baris keluaran.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- N-1 baris, masing-masing berisi N bilangan

📏 CONSTRAINTS:
- 2 <= N <= 1000
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
5 1 4 2

📎 SAMPLE OUTPUT 1:
1 5 4 2
1 4 5 2
1 2 4 5

💡 HINT: Insertion sort menggeser elemen ke kanan, bukan menukarnya.
         Perhatikan bahwa bagian kanan array yang belum diproses tetap
         utuh dan ikut dicetak.
         Satu hal yang mudah salah: arah penulisan saat menggeser. Kalau
         kamu menuliskannya terbalik, kamu akan menimpa data.

🎯 Learning Goals:
- [ ] Memahami invariant insertion sort: bagian kiri terurut relatif
- [ ] Menggeser dengan arah yang benar tanpa menimpa data
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk i = 1..n-1, ambil kunci, geser, sisipkan

    // TODO: cetak seluruh array setelah setiap penyisipan

    return 0;
}
