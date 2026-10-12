/*
============================================================
🏋️ Exercise 1: Submatrix Sum Query Dasar
============================================================
Day: 30 | Difficulty: Easy
Topic: Prefix Sum 2D
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan matriks A berukuran N × M dan Q buah query.
Setiap query terdiri dari 4 integer: r1, c1, r2, c2 yang mendefinisikan
submatriks dari baris r1 kolom c1 hingga baris r2 kolom c2.
Hitunglah jumlah semua elemen di dalam submatriks tersebut untuk setiap query!

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan M (1 ≤ N, M ≤ 1000)
- N baris berikutnya: M integer A[i][j] (1 ≤ A[i][j] ≤ 10^9)
- Baris berikutnya: satu integer Q (1 ≤ Q ≤ 10^5)
- Q baris berikutnya: 4 integer r1 c1 r2 c2 (1 ≤ r1 ≤ r2 ≤ N, 1 ≤ c1 ≤ c2 ≤ M)

📤 OUTPUT FORMAT:
- Q baris, masing-masing berisi jumlah elemen submatriks untuk query tersebut.

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 1000
- 1 ≤ A[i][j] ≤ 10^9 (Perhatikan overflow! Gunakan long long)
- 1 ≤ Q ≤ 10^5

📎 SAMPLE INPUT 1:
3 3
1 2 3
4 5 6
7 8 9
2
1 1 2 2
2 2 3 3

📎 SAMPLE OUTPUT 1:
12
28

📎 SAMPLE INPUT 2:
2 4
10 20 30 40
5 15 25 35
1
1 2 2 4

📎 SAMPLE OUTPUT 2:
165

💡 HINT:
- Gunakan 1-indexed array untuk memudahkan handling border (baris 0 dan kolom 0 bernilai 0).
- psum[i][j] = A[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1]
- Query(r1, c1, r2, c2) = psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1]

🎯 Learning Goals:
- [ ] Mampu membangun tabel prefix sum 2D dari matriks 1-indexed
- [ ] Menjawab submatrix sum query dalam O(1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));

    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            pref[i][j] = a[i][j] + pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1];
        }
    }

    int q;
    cin >> q;

    while (q--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int jawab = pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];
        cout << jawab;
    }
}