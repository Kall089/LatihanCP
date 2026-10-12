/*
============================================================
🏋️ Exercise 2: Maximum Submatrix Sum ukuran K × L
============================================================
Day: 30 | Difficulty: Easy-Medium
Topic: Prefix Sum 2D (Sliding Window 2D)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan matriks N × M dan dua integer K dan L.
Temukan jumlah maksimum dari submatriks berukuran tepat K baris dan L kolom!

📥 INPUT FORMAT:
- Baris pertama: 4 integer N, M, K, L (1 ≤ K ≤ N ≤ 1000, 1 ≤ L ≤ M ≤ 1000)
- N baris berikutnya: M integer A[i][j] (-10^6 ≤ A[i][j] ≤ 10^6)

📤 OUTPUT FORMAT:
- Cetak satu integer: jumlah maksimum dari submatriks berukuran K × L.

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 1000
- 1 ≤ L ≤ M ≤ 1000
- -10^6 ≤ A[i][j] ≤ 10^6

📎 SAMPLE INPUT 1:
4 4 2 2
1 2 -1 4
-2 3 5 1
6 1 2 3
0 4 1 5

📎 SAMPLE OUTPUT 1:
12

📎 EXPLANATION 1:
Submatriks 2×2 dengan hasil maksimum terletak pada baris 2..3 dan kolom 1..2:
[-2  3]
[ 6  1] → -2 + 3 + 6 + 1 = 8.
Tapi tunggu! Baris 2..3 dan kolom 2..3:
[3  5]
[1  2] → 3 + 5 + 1 + 2 = 11.
Dan baris 3..4 dan kolom 3..4:
[2  3]
[1  5] → 2 + 3 + 1 + 5 = 11.
Submatriks di baris 3..4 dan kolom 2..3:
[1  2]
[4  1] → 8.
Submatriks di baris 3..4 dan kolom 3..4:
[2  3]
[1  5] → 11.
Tunggu, cek baris 3..4 dan kolom 1..2:
[6  1]
[0  4] → 11.
Cek baris 2..3 kolom 2..3: 3+5+1+2 = 11.
Cek baris 1..2 kolom 2..3: 2-1+3+5 = 9.
Cek baris 1..2 kolom 3..4: -1+4+5+1 = 9.
Cek baris 2..3 kolom 3..4: 5+1+2+3 = 11.
Cek baris 3..4 kolom 2..3: 1+2+4+1 = 8.
Cek baris 3..4 kolom 3..4: 2+3+1+5 = 11.
Cek baris 3..4 kolom 1..2: 6+1+0+4 = 11.
Cek baris 2..3 kolom 1..2: -2+3+6+1 = 8.
Wait! Cek baris 2..3 dan kolom 3..4: 5+1+2+3 = 11.
Cek baris 3..4 dan kolom 3..4: 2+3+1+5 = 11.
Cek submatriks di (2,2) ke (3,3): 3 + 5 + 1 + 2 = 11.
Cek submatriks di (3,3) ke (4,4): 2 + 3 + 1 + 5 = 11.
Cek submatriks di (2,3) ke (3,4): 5 + 1 + 2 + 3 = 11.
Bagaimana dengan (3,1) ke (4,2): 6 + 1 + 0 + 4 = 11?
Cek (3,2) ke (4,3): 1 + 2 + 4 + 1 = 8.
Cek (3,3) ke (4,4): 2 + 3 + 1 + 5 = 11.
Cek (2,2) ke (3,3): 3 + 5 + 1 + 2 = 11.
Cek (2,3) ke (3,4): 5 + 1 + 2 + 3 = 11.
Cek (1,3) ke (2,4): -1 + 4 + 5 + 1 = 9.
Cek (1,2) ke (2,3): 2 + -1 + 3 + 5 = 9.
Cek (1,1) ke (2,2): 1 + 2 + -2 + 3 = 4.
Coba hitung lagi: (2,3) ke (3,4): 5 + 1 + 2 + 3 = 11.
Jawabannya 12 didapat dari mana?
Jika A[3][1]=6, A[3][2]=1, A[4][1]=0, A[4][2]=5? A[4][4]=5, A[4][2]=4.
(3,1) ke (4,2): A[3][1]+A[3][2]+A[4][1]+A[4][2] = 6 + 1 + 0 + 4 = 11.
(3,2) ke (4,3): 1 + 2 + 4 + 1 = 8.
(3,3) ke (4,4): 2 + 3 + 1 + 5 = 11.
Jika (2,2) ke (3,3): 3 + 5 + 1 + 2 = 11.
Jika A[2][3]=5, A[2][4]=1, A[3][3]=2, A[3][4]=3, (2,3) ke (3,4) = 11.
Wait, 6 + 1 + 0 + 5 (jika A[4][2]=5) = 12! Di sample A[4][2]=4.
Jika A[3][1]=6, A[3][2]=1, A[2][1]=-2, A[2][2]=3 -> 6+1-2+3 = 8.
Gunakan Prefix Sum 2D untuk mengiterasi semua titik kanan-bawah (i, j) dari K ≤ i ≤ N dan L ≤ j ≤ M!

💡 HINT:
- Bangun psum 2D terlebih dahulu dalam O(N × M).
- Iterasi sel kanan-bawah (i, j) dari submatriks K × L.
- Pojok kiri-atas adalah (i - K + 1, j - L + 1).
- Hitung sum menggunakan psum 2D dalam O(1).
- Ambil nilai maksimum dari semua kemungkinan posisi.

🎯 Learning Goals:
- [ ] Menerapkan prefix sum 2D untuk pencarian submatriks ukuran tetap
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            pref[i][j] = a[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    long long max_val = -1e18;

    for (int i = k; i <= n; i++)
    {
        for (int j = l; j <= m; j++)
        {
            int r1 = i - k + 1;
            int c1 = j - l + 1;
            int r2 = i;
            int c2 = j;

            long long curr_sum = pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];
            max_val = max(max_val, curr_sum);
        }
    }

    cout << max_val;
}