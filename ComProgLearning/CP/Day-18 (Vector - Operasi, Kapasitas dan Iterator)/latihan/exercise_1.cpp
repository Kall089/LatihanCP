/*
============================================================
🏋️ Exercise 1: Distinct Numbers (Hitung Elemen Unik)
============================================================
Day: 3 | Difficulty: Easy
Topic: Vector, Sort, Unique
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N buah bilangan bulat. Hitung berapa banyak bilangan
yang BERBEDA (distinct) dari kumpulan tersebut.

Contoh: dari [2, 3, 2, 1, 3], ada 3 bilangan berbeda: {1, 2, 3}

📥 INPUT FORMAT:
- Baris pertama: integer N (jumlah bilangan)
- Baris kedua: N buah integer a1, a2, ..., aN

📤 OUTPUT FORMAT:
- Satu integer: jumlah bilangan berbeda

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
5
2 3 2 1 3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
4
1 1 1 1

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
6
1 2 3 4 5 6

📎 SAMPLE OUTPUT 3:
6

💡 HINT: Sort dulu, lalu gunakan unique() + erase()

🎯 Learning Goals:
- [ ] Input N elemen ke vector
- [ ] Gunakan sort + unique + erase untuk remove duplicates
- [ ] Output size vector setelah remove duplicates
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int &x : arr)
    {
        cin >> x;
    }

    sort(arr.begin(), arr.end());

    // TODO: Remove duplicates (unique + erase)
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    // TODO: Output jumlah elemen unik
    cout << arr.size();

    return 0;
}
