/*
============================================================
🏋️ Exercise 6: Sliding Window Distinct Count
============================================================
Day: 4 | Difficulty: Hard
Topic: Map, sliding window, frequency count
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array N bilangan dan integer K. Untuk setiap window berukuran K
yang bergeser dari kiri ke kanan, hitung jumlah elemen DISTINCT di window.

Window 1: arr[0..K-1]
Window 2: arr[1..K]
...
Window (N-K+1): arr[N-K..N-1]

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan K
- Baris kedua: N buah integer

📤 OUTPUT FORMAT:
- (N-K+1) integer: jumlah distinct per window, dipisah spasi

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
7 3
1 2 1 3 2 1 4

📎 SAMPLE OUTPUT 1:
2 3 2 3 3

📎 SAMPLE INPUT 2:
5 2
1 1 1 1 1

📎 SAMPLE OUTPUT 2:
1 1 1 1

📎 SAMPLE INPUT 3:
5 5
1 2 3 4 5

📎 SAMPLE OUTPUT 3:
5

💡 HINT: Maintain map<int,int> freq yang track frekuensi elemen di window.
         Saat geser window: tambah elemen baru (freq[x]++), hapus elemen lama
         (freq[x]--, jika jadi 0 maka erase). map.size() = jumlah distinct.

🎯 Learning Goals:
- [ ] Sliding window technique
- [ ] Map sebagai frequency counter yang dynamic
- [ ] Erase dari map saat frekuensi = 0
- [ ] Maintain state efisien saat window bergeser
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan K

    // TODO: Baca array

    // TODO: Inisialisasi window pertama [0..K-1]
    //       Masukkan semua ke map freq

    // TODO: Output distinct count window pertama (freq.size())

    // TODO: Slide window dari i=K sampai i=N-1:
    //       - Tambah arr[i]: freq[arr[i]]++
    //       - Hapus arr[i-K]: freq[arr[i-K]]--; jika 0, erase
    //       - Output freq.size()

    return 0;
}
