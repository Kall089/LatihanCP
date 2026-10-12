/*
============================================================
🏋️ Exercise 1: Distinct Numbers (Set)
============================================================
Day: 4 | Difficulty: Easy
Topic: Set basic operations
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N buah bilangan. Hitung berapa banyak bilangan BERBEDA.
(Sama seperti Day 3 exercise 1, tapi kali ini pakai SET)

📥 INPUT FORMAT:
- Baris pertama: integer N
- Baris kedua: N buah integer

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
7
1 1 1 1 1 1 1

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Masukkan semua ke set, lalu output set.size()

🎯 Learning Goals:
- [ ] Deklarasi dan insert ke set
- [ ] Pahami bahwa set otomatis menghapus duplikat
- [ ] Output size
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

    set<int> v;

    // TODO: Baca N bilangan, masukkan ke set<int>
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        v.insert(x);
    }

    cout << v.size();

    // TODO: Output set.size()

    return 0;
}
