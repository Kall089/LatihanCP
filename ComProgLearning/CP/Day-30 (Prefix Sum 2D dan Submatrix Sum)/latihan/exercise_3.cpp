/*
============================================================
🏋️ Exercise 3: Forest Queries (Jumlah Pohon di Area Grid)
============================================================
Day: 30 | Difficulty: Medium
Topic: Prefix Sum 2D pada Character Grid
Source: CSES - Forest Queries (task/1652)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan peta sebuah hutan berukuran N × N.
Peta digambarkan sebagai grid karakter:
- '.' menyatakan tanah kosong (0 pohon)
- '*' menyatakan ada pohon (1 pohon)

Kamu diberikan Q buah query. Setiap query berisi 4 integer y1, x1, y2, x2
yang mendefinisikan area persegi panjang (y1, x1) sebagai pojok kiri-atas
dan (y2, x2) sebagai pojok kanan-bawah (1-indexed, y = baris, x = kolom).
Hitung berapa banyak pohon di dalam area tersebut!

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan Q (1 ≤ N ≤ 1000, 1 ≤ Q ≤ 2 × 10^5)
- N baris berikutnya: string sepanjang N berisi '.' atau '*'
- Q baris berikutnya: 4 integer y1 x1 y2 x2 (1 ≤ y1 ≤ y2 ≤ N, 1 ≤ x1 ≤ x2 ≤ N)

📤 OUTPUT FORMAT:
- Q baris: jumlah pohon untuk setiap query.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 1000
- 1 ≤ Q ≤ 2 × 10^5

📎 SAMPLE INPUT 1:
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 4 4

📎 SAMPLE OUTPUT 1:
3
1
9

💡 HINT:
- Ubah karakter '*' menjadi 1 dan '.' menjadi 0.
- Bangun tabel psum 2D berukuran (N+1) × (N+1).
- Gunakan rumus query submatriks biasa!

🎯 Learning Goals:
- [ ] Mengubah problem grid karakter menjadi matriks numerik 0/1
- [ ] Menyelesaikan soal klasifikasi CSES Forest Queries
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    vector<vector<int>> pref(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char c;
            cin >> c;

            if (c == '*')
            {
                a[i][j] = 1;
            }
            else if (c == '.')
            {
                a[i][j] = 0;
            }

            pref[i][j] = a[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    while (m--)
    {
        int r1, c1, r2, c2;

        cin >> r1 >> c1 >> r2 >> c2;
        int ans = pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];

        cout << ans << "\n";
    }
}