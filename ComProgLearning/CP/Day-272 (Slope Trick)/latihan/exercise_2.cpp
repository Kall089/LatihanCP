/*
============================================================
🏋️ Exercise 2: Mengubah Barisan Menjadi Terurut Tegas Menaik (CF 713C)
============================================================
Day: 272 | Difficulty: Hard | Topic: Slope Trick (Index Transformation)
Source: Codeforces 713C - Sonya and Problem Wi-Fi
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah barisan bilangan bulat A = [a_0, a_1, ..., a_{N-1}].
Kamu ingin mengubahnya menjadi barisan bilangan bulat B = [b_0, b_1, ..., b_{N-1}] sedemikian sehingga:
1. B terurut TEGAS MENAIK (strictly increasing): b_0 < b_1 < b_2 < ... < b_{N-1}.
2. Seluruh elemen b_i adalah bilangan bulat.
3. Total biaya perubahan, yaitu sum_{i=0}^{N-1} |a_i - b_i|, bernilai sekecil mungkin.

Selesaikan masalah ini dengan SLOPE TRICK dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a_0, a_1, ..., a_{N-1}.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum perubahan.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000.000 <= a_i <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
2 1 5 11

📎 SAMPLE OUTPUT 1:
2

[Penjelasan Sample 1:
Barisan B optimal adalah [1, 2, 5, 11] (terurut tegas menaik: 1 < 2 < 5 < 11).
Biaya = |2 - 1| + |1 - 2| + |5 - 5| + |11 - 11| = 1 + 1 + 0 + 0 = 2.]

📎 SAMPLE INPUT 2:
7
5 4 3 2 1 0 -1

📎 SAMPLE OUTPUT 2:
24

[Penjelasan Sample 2:
Array a' = [5, 3, 1, -1, -3, -5, -7]. Nilai median adalah -1.
Total biaya perubahan = 6 + 4 + 2 + 0 + 2 + 4 + 6 = 24.]

💡 HINT:
- Syarat b_0 < b_1 < ... < b_{N-1} untuk bilangan bulat sama artinya dengan b_i >= b_{i-1} + 1.
- Kurangkan indeks i dari kedua sisi:
  (b_i - i) >= (b_{i-1} - (i - 1)).
- Misalkan b'_i = b_i - i dan a'_i = a_i - i.
- Persamaan biaya tetap sama: |a_i - b_i| = |(a_i - i) - (b_i - i)| = |a'_i - b'_i|.
- Syarat baru adalah b'_0 <= b'_1 <= ... <= b'_{N-1} (non-decreasing)!
- Masalah ini tereduksi persis menjadi Slope Trick pada Exercise 1 untuk array a'_i = a_i - i.

🎯 Learning Goals:
- [ ] Menguasai teknik reduksi indeks (a_i - i) untuk mengubah kendala strictly increasing menjadi non-decreasing.
- [ ] Menyelesaikan masalah Codeforces 713C dalam O(N log N).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Reduksi Indeks + Slope Trick O(N log N)

    return 0;
}
