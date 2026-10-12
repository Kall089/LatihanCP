/*
============================================================
🏋️ Exercise 1: Toko Buku
============================================================
Day: 145 | Difficulty: Easy
Topic: 0/1 knapsack dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu berada di toko buku dengan uang sebanyak X. Ada N buku; buku ke-i
berharga h[i] dan punya "jumlah halaman" s[i].
Setiap buku hanya tersedia SATU eksemplar, jadi kamu boleh membelinya paling
banyak sekali.
Maksimalkan total halaman dari buku-buku yang kamu beli, dengan total harga
tidak melebihi X. Cetak total halaman maksimum itu.

📥 INPUT FORMAT:
- Baris pertama: N dan X
- Baris kedua: N bilangan h[i]
- Baris ketiga: N bilangan s[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total halaman maksimum

📏 CONSTRAINTS:
- 1 <= N <= 1000
- 1 <= X <= 10^5
- 1 <= h[i] <= X
- 1 <= s[i] <= 1000

📎 SAMPLE INPUT 1:
4 10
4 8 5 3
5 12 8 1

📎 SAMPLE OUTPUT 1:
13

📎 SAMPLE INPUT 2:
2 1
5 5
100 100

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Godaan pertama adalah greedy: beli buku dengan rasio halaman
         terhadap harga tertinggi lebih dulu. Coba dulu pada sampel 1 dan
         periksa apakah hasilnya benar — kalau ya, coba cari contoh
         tandingan sendiri sebelum melanjutkan.
         Pendekatan yang benar: untuk setiap buku, kamu punya tepat DUA
         pilihan. Kalau kamu bisa menjawab "berapa halaman maksimum dengan
         i buku pertama dan sisa uang c", jawaban akhirnya tinggal dibaca.
         Perhatikan batas: N kali X adalah 10^8 kalau kamu menyimpan seluruh
         tabel. Hitung memorinya sebelum menulis — ada cara meringkasnya
         karena setiap baris hanya bergantung pada baris tepat di atasnya.

🎯 Learning Goals:
- [ ] Menurunkan rekurens dua pilihan
- [ ] Menghitung memori sebelum memilih versi 1D atau 2D
- [ ] Menyadari bahwa greedy rasio tidak berlaku untuk 0/1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, X;
    cin >> n >> X;

    vector<int> buku(n + 1);
    vector<int> halaman(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> buku[i];
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> halaman[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(X + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= X; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (buku[i] <= j)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - buku[i]] + halaman[i]);
            }
        }
    }

    cout << dp[n][X];
}