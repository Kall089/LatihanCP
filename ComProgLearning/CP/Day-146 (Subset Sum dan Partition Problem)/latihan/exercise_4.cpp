/*
============================================================
🏋️ Exercise 4: Selisih Terkecil
============================================================
Day: 146 | Difficulty: Medium
Topic: Minimum partition difference
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan positif. Bagi semua bilangan menjadi dua kelompok A dan B.
Setiap bilangan harus masuk tepat ke salah satu kelompok.
Tugasmu adalah meminimalkan nilai |sum(A) - sum(B)|.
Cetak selisih minimum yang bisa diperoleh.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan A[i]

📤 OUTPUT FORMAT:
- Satu bilangan: selisih minimum antara dua kelompok

📏 CONSTRAINTS:
- 1 <= N <= 200
- 1 <= A[i] <= 1000

📎 SAMPLE INPUT 1:
4
1 6 11 5

📎 SAMPLE OUTPUT 1:
1

📎 SAMPLE INPUT 2:
5
3 1 4 2 2

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
1
10

📎 SAMPLE OUTPUT 3:
10

💡 HINT: Jika satu kelompok punya sum s, kelompok lain punya total-s.
         Selisihnya adalah |total - 2*s|. Cari s reachable yang paling dekat
         dengan total/2.

🎯 Learning Goals:
- [ ] Mengubah balancing menjadi subset sum
- [ ] Men-scan reachable sum dari total/2 ke bawah
- [ ] Menjelaskan rumus total - 2*s
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input dan hitung total

    // TODO: Jalankan subset sum sampai total

    // TODO: Cari s terbesar <= total/2 yang reachable

    // TODO: Cetak total - 2*s

    return 0;
}
