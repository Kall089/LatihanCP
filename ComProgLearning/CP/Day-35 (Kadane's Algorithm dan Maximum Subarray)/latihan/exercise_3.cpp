/*
============================================================
🏋️ Exercise 3: Keuntungan Saham Sekali Beli
============================================================
Day: 35 | Difficulty: Medium
Topic: Transformasi ke array selisih
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan harga sebuah saham selama N hari berturut-turut. Kamu boleh
membeli saham itu tepat satu kali pada suatu hari, lalu menjualnya tepat
satu kali pada hari BERIKUTNYA (hari jual harus setelah hari beli).
Cari keuntungan maksimum yang bisa kamu peroleh. Jika semua kemungkinan
transaksi merugi, kamu boleh memilih untuk TIDAK bertransaksi sama sekali,
sehingga jawabannya 0.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan harga[i]

📤 OUTPUT FORMAT:
- Satu bilangan: keuntungan maksimum (0 kalau lebih baik tidak bertransaksi)

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= harga[i] <= 10^9

📎 SAMPLE INPUT 1:
6
7 1 5 3 6 4

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
5
7 6 4 3 1

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Perhatikan array SELISIH d[i] = harga[i] - harga[i-1]. Keuntungan
         dari membeli di hari x dan menjual di hari y sama dengan jumlah
         d[x+1] sampai d[y]. Soal ini ternyata soal yang sama dengan
         Exercise 1, hanya berpakaian berbeda.
         Perhatikan juga bahwa di sini subarray BOLEH kosong.

🎯 Learning Goals:
- [ ] Kebiasaan bertanya "bagaimana kalau saya lihat selisihnya?"
- [ ] Membedakan varian "boleh kosong" dan "tidak boleh kosong"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n + 1);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int best = 0;
    int curr = 0;

    for (int i = 1; i <= n; i++)
    {
        int d = arr[i] - arr[i - 1];
        curr = max(0, curr + d);
        best = max(curr, best);
    }

    cout << best;
}