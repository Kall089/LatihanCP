/*
============================================================
🏋️ Exercise 2: Merge Sort dari Nol
============================================================
Day: 44 | Difficulty: Easy
Topic: Divide and conquer
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat, urutkan menaik menggunakan
MERGE SORT yang kamu tulis sendiri. Kamu tidak boleh memakai fungsi
pengurutan dari pustaka.
Cetak array yang sudah terurut.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6
5 2 4 6 1 3

📎 SAMPLE OUTPUT 1:
1 2 3 4 5 6

📎 SAMPLE INPUT 2:
1
42

📎 SAMPLE OUTPUT 2:
42

💡 HINT: Pakai konvensi setengah terbuka [l, r) — kondisi basisnya menjadi
         r - l <= 1, dan kamu tidak perlu memikirkan apakah batas kanan
         inklusif atau tidak.
         Satu hal yang berdampak besar pada kecepatan: alokasikan array
         sementara SEKALI di luar rekursi, bukan setiap kali fungsinya
         dipanggil.
         Untuk menghitung titik tengah, biasakan menulis l + (r - l) / 2.

🎯 Learning Goals:
- [ ] Menulis rekursi divide and conquer dengan basis yang benar
- [ ] Memahami kenapa tmp harus dialokasikan di luar
- [ ] Kebiasaan menghindari overflow pada perhitungan titik tengah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: tulis fungsi mergeSort(a, tmp, l, r) di sini

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: alokasikan tmp SEKALI, lalu panggil mergeSort(a, tmp, 0, n)

    return 0;
}
