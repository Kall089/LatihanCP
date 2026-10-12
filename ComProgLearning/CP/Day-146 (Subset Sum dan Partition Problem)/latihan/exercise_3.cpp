/*
============================================================
🏋️ Exercise 3: Bagi Rata
============================================================
Day: 146 | Difficulty: Medium
Topic: Equal partition
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan positif. Kamu ingin membagi semua bilangan menjadi dua
kelompok, sehingga setiap bilangan masuk tepat ke salah satu kelompok.
Tentukan apakah mungkin membuat jumlah kedua kelompok sama besar.
Jika mungkin, cetak YES. Jika tidak, cetak NO.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan A[i]

📤 OUTPUT FORMAT:
- Cetak "YES" jika array bisa dibagi menjadi dua kelompok dengan sum sama
- Cetak "NO" jika tidak bisa

📏 CONSTRAINTS:
- 1 <= N <= 200
- 1 <= A[i] <= 1000

📎 SAMPLE INPUT 1:
4
1 5 11 5

📎 SAMPLE OUTPUT 1:
YES

📎 SAMPLE INPUT 2:
4
1 2 3 5

📎 SAMPLE OUTPUT 2:
NO

📎 SAMPLE INPUT 3:
2
10 10

📎 SAMPLE OUTPUT 3:
YES

💡 HINT: Jika total sum ganjil, langsung mustahil. Jika genap, masalahnya
         berubah menjadi: adakah subset dengan sum total/2?

🎯 Learning Goals:
- [ ] Mengenali equal partition sebagai subset sum
- [ ] Mengecek parity total sebelum DP
- [ ] Membatasi DP hanya sampai total/2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input dan hitung total

    // TODO: Jika total ganjil, cetak NO

    // TODO: Jalankan subset sum dengan target total / 2

    // TODO: Cetak YES jika target tercapai

    return 0;
}
