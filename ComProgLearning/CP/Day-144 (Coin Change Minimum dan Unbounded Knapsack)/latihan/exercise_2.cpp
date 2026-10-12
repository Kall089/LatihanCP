/*
============================================================
🏋️ Exercise 2: Unbounded Knapsack Maksimum Nilai
============================================================
Day: 144 | Difficulty: Medium | Topic: Unbounded Knapsack
Source: Classic DP / AtCoder
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N jenis barang dan sebuah tas ransel dengan kapasitas bobot maksimum W.
Barang ke-i memiliki bobot w[i] dan nilai keuntungan v[i].
Setiap jenis barang tersedia dalam jumlah tak terbatas (boleh diambil berkali-kali).
Tentukan total nilai maksimum yang bisa didapatkan tanpa melebihi kapasitas bobot W.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan W.
- N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan v[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: total nilai maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 1.000
- 1 <= W <= 100.000
- 1 <= w[i] <= W
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3 8
2 4
3 5
4 11

📎 SAMPLE OUTPUT 1:
22

[Penjelasan Sample 1:
Ambil barang ke-3 sebanyak dua kali:
Total bobot = 4 + 4 = 8 <= 8
Total nilai = 11 + 11 = 22]

📎 SAMPLE INPUT 2:
2 5
3 10
2 6

📎 SAMPLE OUTPUT 2:
16

[Penjelasan Sample 2:
Ambil barang ke-1 (bobot 3, nilai 10) dan barang ke-2 (bobot 2, nilai 6).
Total bobot = 3 + 2 = 5 <= 5. Total nilai = 10 + 6 = 16.]

📎 SAMPLE INPUT 3:
1 7
2 5

📎 SAMPLE OUTPUT 3:
15

[Penjelasan Sample 3:
Ambil barang ke-1 sebanyak 3 kali: total bobot = 2*3 = 6 <= 7. Total nilai = 5*3 = 15.]

💡 HINT:
- Gunakan tipe data long long untuk nilai DP agar tidak overflow.
- Perhatikan arah loop kapasitas: loop MAJU dari w[i] ke W agar barang boleh diambil berulang.

🎯 Learning Goals:
- [ ] Memahami implementasi loop MAJU (Forward loop) pada Unbounded Knapsack.
- [ ] Menggunakan tipe data 64-bit (`long long`) untuk mencegah overflow akumulasi nilai.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<int> wt(n);
    vector<ll> val(n);
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }

    // TODO: Selesaikan dengan Unbounded Knapsack
    // 1. Inisialisasi vector<ll> dp(W + 1, 0)
    // 2. Loop setiap barang i dari 0 sampai n - 1
    // 3. Loop kapasitas w MAJU dari wt[i] sampai W
    // 4. Update dp[w] = max(dp[w], dp[w - wt[i]] + val[i])
    // 5. Cetak dp[W]

    return 0;
}
