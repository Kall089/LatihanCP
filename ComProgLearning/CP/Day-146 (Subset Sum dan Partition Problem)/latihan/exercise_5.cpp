/*
============================================================
🏋️ Exercise 5: Berapa Banyak Cara?
============================================================
Day: 146 | Difficulty: Medium
Topic: Counting subset sum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan non-negatif dan target K.
Hitung banyak subset berbeda berdasarkan indeks yang memiliki jumlah tepat K.
Karena jawabannya bisa sangat besar, cetak hasilnya modulo 1.000.000.007.
Elemen bernilai 0 tetap dihitung: mengambil atau tidak mengambil 0 adalah dua
subset indeks yang berbeda.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan A[i]

📤 OUTPUT FORMAT:
- Satu bilangan: banyak subset dengan sum tepat K modulo 1.000.000.007

📏 CONSTRAINTS:
- 1 <= N <= 200
- 0 <= K <= 100000
- 0 <= A[i] <= 1000

📎 SAMPLE INPUT 1:
4 5
1 2 3 2

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3 1
0 0 1

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
5 0
0 0 0 0 0

📎 SAMPLE OUTPUT 3:
32

💡 HINT: Ganti bisa[s] menjadi cara[s]. Basisnya cara[0] = 1.
         Transisi: cara[s] += cara[s - x]. Arah loop tetap mundur.

🎯 Learning Goals:
- [ ] Mengubah DP boolean menjadi DP counting
- [ ] Menangani elemen nol dengan benar
- [ ] Melakukan modulo di setiap transisi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N, K, dan array A

    // TODO: Buat vector<long long> cara(K + 1), cara[0] = 1

    // TODO: Update cara dari K turun ke A[i], modulo 1e9+7

    // TODO: Cetak cara[K]

    return 0;
}
