/*
============================================================
🏋️ Exercise 2: Naik Tangga dengan K Langkah
============================================================
Day: 85 | Difficulty: Easy-Medium
Topic: DP 1D dengan banyak transisi
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sama seperti soal sebelumnya, tetapi sekarang langkah yang boleh diambil
diberikan dalam sebuah daftar. Ada K jenis langkah, yaitu L1, L2, ..., LK.
Hitung ada berapa cara mencapai anak tangga ke-N, modulo 1000000007.

Contoh N = 4 dengan langkah {1, 3}: ada 3 cara, yaitu
(1+1+1+1), (1+3), dan (3+1).

📥 INPUT FORMAT:
- Baris pertama: dua bilangan N dan K
- Baris kedua: K bilangan L1..LK

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya cara modulo 1000000007.

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 1 <= K <= 100
- 1 <= Li <= N

📎 SAMPLE INPUT 1:
4 2
1 3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
6 3
1 2 3

📎 SAMPLE OUTPUT 2:
24

📎 SAMPLE INPUT 3:
5 1
2

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Transisinya sama, hanya sekarang ada K kemungkinan langkah terakhir.
- dp[i] = jumlah dp[i - L] untuk setiap L yang tidak membuat indeks negatif.
- Perhatikan sample 3: dengan langkah hanya {2}, tangga ganjil mustahil dicapai.

🎯 Learning Goals:
- [ ] Memperluas transisi dari 2 menjadi K kemungkinan
- [ ] Menangani kasus tidak ada jalan (jawaban 0)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> dp(n + 1, 0);

    vector<int> x(k);

    for (int i = 0; i < k; i++)
    {
        cin >> x[i];
    }

    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i >= x[j])
            {
                dp[i] = dp[i] + dp[i - x[j]];
            }
        }
    }

    cout << dp[n];
}