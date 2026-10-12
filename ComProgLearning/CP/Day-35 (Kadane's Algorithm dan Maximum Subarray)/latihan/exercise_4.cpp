/*
============================================================
🏋️ Exercise 4: Subarray Melingkar Maksimum
============================================================
Day: 35 | Difficulty: Medium
Topic: Kadane maksimum + minimum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array MELINGKAR berisi N bilangan bulat: setelah elemen terakhir,
array kembali ke elemen pertama. Cari subarray tidak kosong dengan jumlah
maksimum, di mana subarray tersebut BOLEH membungkus melewati ujung array.
Setiap elemen hanya boleh dipakai paling banyak sekali (jadi subarray tidak
boleh lebih panjang dari N).

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3
5 -3 5

📎 SAMPLE OUTPUT 1:
10

📎 SAMPLE INPUT 2:
3
-3 -2 -5

📎 SAMPLE OUTPUT 2:
-2

📎 SAMPLE INPUT 3:
5
1 -2 3 -2 5

📎 SAMPLE OUTPUT 3:
7

💡 HINT: Jawabannya punya tepat dua bentuk yang mungkin: membungkus atau
         tidak. Yang tidak membungkus adalah Kadane biasa. Yang membungkus
         adalah "seluruh array dikurangi sesuatu di tengah" — dan agar
         hasilnya maksimum, yang dibuang harus MINIMUM.
         Sampel 2 ada di sini karena rumus itu punya satu lubang serius.
         Temukan lubangnya.

🎯 Learning Goals:
- [ ] Trik total - minimum untuk kasus melingkar
- [ ] Menyadari bahwa "total - minSum" bisa berarti subarray KOSONG
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    long long total = 0;
    long long curMax = 0, best = LLONG_MIN;
    long long curMin = 0, worst = LLONG_MAX;

    for (int i = 0; i < n; i++)
    {
        total += arr[i];

        curMax = max(arr[i], curMax + arr[i]);
        best = max(best, curMax);

        curMin = min(arr[i], curMin + arr[i]);
        worst = min(worst, curMin);
    }

    if (best < 0)
    {
        cout << best;
    }
    else
    {
        cout << max(best, total - worst);
    }
}