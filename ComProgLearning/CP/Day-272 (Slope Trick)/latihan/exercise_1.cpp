/*
============================================================
🏋️ Exercise 1: Mengubah Barisan Menjadi Terurut Tidak Menurun
============================================================
Day: 272 | Difficulty: Medium | Topic: Slope Trick (Piecewise Linear Convex DP)
Source: Classic Non-Decreasing Sequence Alignment
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah barisan bilangan bulat A = [a_0, a_1, ..., a_{N-1}].
Kamu ingin membuat barisan baru B = [b_0, b_1, ..., b_{N-1}] sedemikian rupa sehingga:
1. B terurut tidak menurun: b_0 <= b_1 <= b_2 <= ... <= b_{N-1}.
2. Seluruh elemen b_i adalah bilangan bulat.
3. Total biaya perubahan, yaitu sum_{i=0}^{N-1} |a_i - b_i|, bernilai sekecil mungkin.

Jika diselesaikan dengan DP koordinat biasa, kompleksitasnya adalah O(N^2), yang akan TLE untuk N = 200.000.
Selesaikan masalah ini menggunakan SLOPE TRICK dengan satu Max-Heap dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a_0, a_1, ..., a_{N-1}.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum perubahan.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- -1.000.000.000 <= a_i <= 1.000.000.000

📎 SAMPLE INPUT 1:
5
5 4 3 2 1

📎 SAMPLE OUTPUT 1:
6

[Penjelasan Sample 1:
Barisan B optimal adalah [3, 3, 3, 3, 3] (semua sama dengan median).
Total biaya = |5 - 3| + |4 - 3| + |3 - 3| + |2 - 3| + |1 - 3| = 2 + 1 + 0 + 1 + 2 = 6.]

📎 SAMPLE INPUT 2:
5
1 2 3 4 5

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Barisan A sudah terurut tidak menurun, tidak perlu perubahan apapun (biaya 0).]

💡 HINT:
- Misalkan dp[i](x) adalah biaya minimum hingga elemen i dengan b_i = x.
- Rekurensi: dp[i](x) = |x - a_i| + min_{y <= x} dp[i-1](y).
- Operasi min_{y <= x} adalah prefiks minimum, yang memotong semua kemiringan positif (slope > 0) menjadi datar (slope = 0).
- Dengan demikian, kita hanya perlu memelihara titik belok lereng menurun (slope <= 0) menggunakan sebuah Max-Heap `L`!
- Untuk setiap a_i:
  - Jika !L.empty() dan a_i < L.top():
    tambah jawaban sebesar (L.top() - a_i)
    L.pop()
    L.push(a_i)
    L.push(a_i)
  - Selain itu:
    L.push(a_i)

🎯 Learning Goals:
- [ ] Memahami representasi kemiringan konveks dengan Max-Heap.
- [ ] Menyelesaikan masalah perataan barisan non-decreasing dalam O(N log N).
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

    // TODO: Selesaikan dengan Slope Trick O(N log N)

    return 0;
}
