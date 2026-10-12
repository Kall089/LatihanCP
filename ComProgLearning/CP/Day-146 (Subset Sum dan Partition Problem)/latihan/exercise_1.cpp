/*
============================================================
🏋️ Exercise 1: Ada Target?
============================================================
Day: 146 | Difficulty: Easy
Topic: Subset sum boolean
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan bulat non-negatif dan sebuah target S.
Setiap bilangan boleh dipakai paling banyak sekali.
Tentukan apakah ada subset dari bilangan-bilangan tersebut yang jumlahnya
tepat sama dengan S. Subset kosong diperbolehkan, sehingga target 0 selalu
bisa dicapai.

📥 INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N bilangan A[i]

📤 OUTPUT FORMAT:
- Cetak "YES" jika target bisa dibentuk, selain itu cetak "NO"

📏 CONSTRAINTS:
- 1 <= N <= 100z
- 0 <= S <= 100000
- 1 <= A[i] <= 1000

📎 SAMPLE INPUT 1:
5 11
2 3 7 8 10

📎 SAMPLE OUTPUT 1:
YES

📎 SAMPLE INPUT 2:
4 6
5 9 12 20

📎 SAMPLE OUTPUT 2:
NO

📎 SAMPLE INPUT 3:
1 0
7

📎 SAMPLE OUTPUT 3:
YES

💡 HINT: Definisikan bisa[s] = apakah sum s bisa dibentuk dari elemen yang
         sudah diproses. Basisnya bisa[0] = true.
         Loop sum harus mundur agar setiap elemen hanya dipakai sekali.

🎯 Learning Goals:
- [ ] Menulis subset sum boolean O(N*S)
- [ ] Menginisialisasi basis dengan benar
- [ ] Menjaga arah loop agar tetap 0/1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, S;
    cin >> n >> S;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int x : a)
    {
        for (int i = S; i >= x; i--)
        {
            if (dp[i - x] == 1)
            {
                dp[i] = 1;
            }
        }
    }

    if (dp[S] == 1)
    {
        cout << "YA";
    }
    else
    {
        cout << "TIDAK";
    }
}