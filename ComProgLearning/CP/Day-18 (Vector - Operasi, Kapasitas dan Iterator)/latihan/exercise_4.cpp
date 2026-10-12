/*
============================================================
🏋️ Exercise 4: Rotate Vector (Rotasi Array)
============================================================
Day: 3 | Difficulty: Medium
Topic: Vector Operations
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array dengan N elemen dan integer K.
Lakukan rotasi ke KANAN sebanyak K posisi.

Rotasi ke kanan 1 posisi berarti elemen terakhir pindah ke depan.
Contoh: [1, 2, 3, 4, 5] rotasi kanan 2 → [4, 5, 1, 2, 3]

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan K
- Baris kedua: N buah integer (elemen array)

📤 OUTPUT FORMAT:
- Satu baris: N buah integer setelah rotasi (dipisah spasi)

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 0 ≤ K ≤ 1,000,000,000
- 1 ≤ a[i] ≤ 1,000,000

📎 SAMPLE INPUT 1:
5 2
1 2 3 4 5

📎 SAMPLE OUTPUT 1:
4 5 1 2 3

📎 SAMPLE INPUT 2:
4 4
10 20 30 40

📎 SAMPLE OUTPUT 2:
10 20 30 40

📎 SAMPLE INPUT 3:
3 1
7 8 9

📎 SAMPLE OUTPUT 3:
9 7 8

💡 HINT: K bisa > N, jadi K = K % N dulu.
         Bisa pakai reverse trick: reverse all, reverse [0..K-1], reverse [K..N-1]
         Atau pakai rotate() dari STL.

🎯 Learning Goals:
- [ ] Handle K > N dengan modulo
- [ ] Implementasi rotasi dengan reverse trick atau rotate()
- [ ] Pahami kompleksitas O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO: Baca N dan K
    int n, k;
    cin >> n >> k;

    // TODO: Baca N elemen ke vector

    vector<int> v(n);
    for (int &x : v)
    {
        cin >> x;
    }

    // TODO: Handle K >= N (K = K % N)
    k = k % n;

    if (k == 0)
    {
        for (int i : v)
        {
            cout << i << " ";
        }
    }

    // TODO: Rotasi vector ke kanan sebanyak K posisi
    // Hint: reverse seluruh array, reverse [0..K-1], reverse [K..N-1]

    reverse(v.begin(), v.end());
    reverse(v.begin(), v.begin() + k);
    reverse(v.begin() + k, v.end());

    for (int i : v)
    {
        cout << i << " ";
    }

    // TODO: Output hasil

    return 0;
}
