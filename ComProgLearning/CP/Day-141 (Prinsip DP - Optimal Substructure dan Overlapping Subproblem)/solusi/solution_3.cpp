/*
============================================================
🏋️ Exercise 3: Perampok Rumah
============================================================
Day: 85 | Difficulty: Medium
Topic: DP 1D — pola "maksimum" dengan larangan bertetangga
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N rumah berjajar, rumah ke-i berisi uang sebanyak a[i].
Kamu boleh mengambil uang dari rumah mana pun, TETAPI tidak boleh
mengambil dari dua rumah yang berdampingan (karena alarmnya akan berbunyi).
Tentukan jumlah uang MAKSIMUM yang bisa kamu peroleh.

📥 INPUT FORMAT:
- Baris pertama: bilangan N
- Baris kedua: N bilangan a[1..N]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah uang maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- 0 <= a[i] <= 10^9 (total bisa 10^15, gunakan long long)

📎 SAMPLE INPUT 1:
5
2 7 9 3 1

📎 SAMPLE OUTPUT 1:
12

📎 SAMPLE INPUT 2:
4
1 2 3 1

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
1
5

📎 SAMPLE OUTPUT 3:
5

💡 HINT:
- Untuk tiap rumah, kamu hanya punya DUA pilihan: ambil atau lewati.
- Kalau LEWATI rumah ke-i, hasilnya sama dengan hasil terbaik sampai rumah (i-1).
- Kalau AMBIL rumah ke-i, rumah (i-1) tidak boleh diambil, jadi hasilnya
  adalah hasil terbaik sampai rumah (i-2) ditambah a[i].
- dp[i] = max(dp[i-1], dp[i-2] + a[i]).

🎯 Learning Goals:
- [ ] Menerjemahkan larangan menjadi transisi DP
- [ ] Memahami pola ambil-atau-lewati
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n))
        return 0;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<ll> dp(n + 1, 0);
    dp[1] = a[1]; // basis
    for (int i = 2; i <= n; i++)
        dp[i] = max(dp[i - 1],         // lewati rumah ke-i
                    dp[i - 2] + a[i]); // ambil rumah ke-i

    cout << dp[n] << "\n";

    return 0;
}
