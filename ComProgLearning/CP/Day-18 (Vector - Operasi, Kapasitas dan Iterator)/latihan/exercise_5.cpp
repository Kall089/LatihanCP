/*
============================================================
🏋️ Exercise 5: Closest Pair of Points (1D)
============================================================
Day: 3 | Difficulty: Medium-Hard
Topic: Vector, Sort, Pair, Adjacent Difference
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N titik pada garis bilangan (1 dimensi). Cari dua titik
yang jaraknya PALING DEKAT dan outputkan jaraknya.

Jarak antara dua titik x dan y adalah |x - y|.

📥 INPUT FORMAT:
- Baris pertama: integer N (jumlah titik)
- Baris kedua: N buah integer (posisi titik pada garis bilangan)

📤 OUTPUT FORMAT:
- Satu integer: jarak minimum antara dua titik manapun

📏 CONSTRAINTS:
- 2 ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
5
3 8 1 10 5

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3
-5 -2 3

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
4
1 1000000000 -1000000000 0

📎 SAMPLE OUTPUT 3:
1

💡 HINT: Sort dulu! Setelah sort, jarak minimum pasti antara dua
         elemen yang BERSEBELAHAN. Cek semua adjacent pairs.

🎯 Learning Goals:
- [ ] Sort vector untuk mempermudah pencarian
- [ ] Iterasi adjacent pairs setelah sort
- [ ] Handle angka negatif dan abs()
- [ ] Gunakan long long untuk menghindari overflow
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N
    int n;
    cin >> n;

    // TODO: Baca N bilangan ke vector (hati-hati: bisa negatif, besar)
    //       Gunakan long long!

    vector<long long> v(n);

    for (long long &x : v)
    {
        cin >> x;
    }

    // TODO: Sort vector
    sort(v.begin(), v.end());

    // TODO: Cari minimum dari |v[i] - v[i-1]| untuk semua i
    long long min_dist = LLONG_MAX;
    for (int i = 1; i < n; i++)
    {
        long long diff = v[i] - v[i - 1];
        min_dist = min(min_dist, diff);
    }

    // TODO: Output jarak minimum

    cout << min_dist;

    return 0;
}
