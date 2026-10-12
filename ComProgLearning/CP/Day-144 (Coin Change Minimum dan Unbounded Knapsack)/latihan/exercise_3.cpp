/*
============================================================
🏋️ Exercise 3: Rekonstruksi Koin Minimum
============================================================
Day: 144 | Difficulty: Medium | Topic: Rekonstruksi Solusi DP
Source: Classic DP
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N jenis koin c[0], ..., c[N-1] dan sebuah nominal target X.
Setiap jenis koin tersedia dalam jumlah tak terbatas.
Tentukan jumlah koin minimum untuk membentuk tepat nominal X, serta tampilkan
seluruh koin yang digunakan untuk membentuk nominal tersebut.

Jika terdapat beberapa kombinasi koin yang sama-sama menghasilkan jumlah koin minimum,
tampilkan salah satu kombinasi yang valid.
Jika nominal X tidak mungkin dibentuk, cukup cetak -1 pada baris pertama.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan X.
- Baris kedua berisi N bilangan bulat c[0], c[1], ..., c[N-1].

📤 OUTPUT FORMAT:
- Jika tidak mungkin: cetak satu baris berisi -1.
- Jika mungkin:
  - Baris pertama: jumlah koin minimum K.
  - Baris kedua: K bilangan bulat yang menyatakan koin-koin yang dipakai (dipisahkan spasi).

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= X <= 100.000
- 1 <= c[i] <= 100.000

📎 SAMPLE INPUT 1:
3 6
1 3 4

📎 SAMPLE OUTPUT 1:
2
3 3

[Penjelasan Sample 1: 6 dibentuk oleh dua koin bernilai 3]

📎 SAMPLE INPUT 2:
3 11
1 5 7

📎 SAMPLE OUTPUT 2:
3
1 5 5

[Penjelasan Sample 2: 11 = 1 + 5 + 5 (atau 5 + 5 + 1 / 7 + ... tidak, 7+1+1+1+1 = 5 koin)]

📎 SAMPLE INPUT 3:
2 5
2 4

📎 SAMPLE OUTPUT 3:
-1

💡 HINT:
- Gunakan array pick berukuran (X + 1) diinisialisasi dengan -1.
- Saat dp[i - c] + 1 < dp[i], perbarui dp[i] dan set pick[i] = c.
- Setelah selesai, telusuri mundur dari X menggunakan pick:
  curr = X; while (curr > 0) { ambil pick[curr]; curr -= pick[curr]; }

🎯 Learning Goals:
- [ ] Memahami cara merekam keputusan optimal dengan pointer parent/pick.
- [ ] Mampu melakukan penelusuran balik (backtracking) untuk menghasilkan solusi konkret.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    // TODO: Selesaikan dengan Dynamic Programming + Rekonstruksi Solusi
    // 1. vector<int> dp(x + 1, INF), pick(x + 1, -1);
    // 2. dp[0] = 0;
    // 3. Tabulasi dengan pencatatan pick[i] saat dp diperbarui
    // 4. Jika dp[x] == INF cetak -1
    // 5. Jika tidak, cetak dp[x], lalu lacak balik dan cetak koin-koinnya

    return 0;
}
