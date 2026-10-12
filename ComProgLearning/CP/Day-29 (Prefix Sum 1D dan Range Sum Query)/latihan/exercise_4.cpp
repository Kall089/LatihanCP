/*
============================================================
🏋️ Exercise 4: Subarray Kelipatan K
============================================================
Day: 29 | Difficulty: Medium
Topic: Prefix sum modulo
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan sebuah bilangan bulat positif K.
Hitung ada berapa banyak subarray tidak kosong yang jumlah elemennya
habis dibagi K.
Perhatikan bahwa elemen array boleh negatif, dan di C++ operator % pada
bilangan negatif menghasilkan sisa negatif — ini akan membuat indeks array
menjadi negatif kalau tidak ditangani.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= K <= 10^6
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
3 3
2 -2 3

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
5 5
1 2 3 4 5

📎 SAMPLE OUTPUT 2:
4

💡 HINT: (pre[r+1] - pre[l]) habis dibagi K berarti pre[r+1] dan pre[l]
         punya SISA BAGI yang sama. Jadi tinggal menghitung berapa pasang
         prefix yang sisanya kembar. Jangan lupa menormalisasi sisa negatif
         dengan ((x % K) + K) % K.

🎯 Learning Goals:
- [ ] Menerjemahkan "habis dibagi" jadi "sisa bagi sama"
- [ ] Menangani sisa bagi negatif dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca input

    // TODO: cnt berukuran K, cnt[0] = 1

    // TODO: cur = ((cur + v) % K + K) % K; hasil += cnt[cur]; cnt[cur]++

    return 0;
}
