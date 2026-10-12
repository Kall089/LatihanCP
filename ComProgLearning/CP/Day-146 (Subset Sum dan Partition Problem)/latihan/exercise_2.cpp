/*
============================================================
🏋️ Exercise 2: Semua Jumlah Koin
============================================================
Day: 146 | Difficulty: Easy
Topic: Reachable sums
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu memiliki N koin, masing-masing dengan nilai A[i].
Setiap koin hanya boleh dipakai paling banyak sekali.
Cetak semua jumlah positif berbeda yang bisa dibentuk dari satu atau lebih
koin. Urutan output harus menaik.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N nilai koin

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya jumlah positif berbeda
- Baris kedua: daftar jumlah tersebut dalam urutan menaik

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= A[i] <= 1000

📎 SAMPLE INPUT 1:
4
4 2 5 2

📎 SAMPLE OUTPUT 1:
9
2 4 5 6 7 8 9 11 13

📎 SAMPLE INPUT 2:
1
7

📎 SAMPLE OUTPUT 2:
1
7

📎 SAMPLE INPUT 3:
3
1 1 1

📎 SAMPLE OUTPUT 3:
3
1 2 3

💡 HINT: Batas sum terbesar adalah total semua koin. Setelah DP selesai,
         scan semua s dari 1 sampai total dan ambil yang bisa[s] = true.

🎯 Learning Goals:
- [ ] Mengubah target tunggal menjadi semua reachable sums
- [ ] Tidak mencetak sum 0 untuk subset kosong
- [ ] Menangani nilai koin kembar sebagai jumlah berbeda
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> coin(N);

    for (int i = 0; i < N; i++)
    {
        cin >> coin[i];
    }

    vector<bool> dp(N + 1, false);
    dp[0] = 1;

    for (int c : coin)
    {

        for (int sum = N; sum >= c; sum--)
        {
            if (dp[sum - c])
            {
                dp[sum] = true;
            }
        }
    }
    vector<int> hasil;
    for (int i = 1; i <= N; i++)
    {
        if (dp[i])
        {
            hasil.push_back(i);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << dp[i] << " ";
    }
}