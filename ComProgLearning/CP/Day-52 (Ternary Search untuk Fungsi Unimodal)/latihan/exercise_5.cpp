/*
============================================================
🏋️ Exercise 5: Meminimumkan Kelemahan
============================================================
Day: 52 | Difficulty: Hard
Topic: Ternary search + Kadane
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Untuk sebuah bilangan real x,
definisikan array baru b[i] = a[i] - x.
"Kelemahan" dari x didefinisikan sebagai nilai MAKSIMUM di antara:
- jumlah subarray terbesar dari b, dan
- nilai absolut dari jumlah subarray terkecil dari b.
Cari nilai x yang MEMINIMUMKAN kelemahan itu, lalu cetak kelemahan
minimumnya dengan 6 desimal.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan bulat

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 6 desimal

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^4 <= a[i] <= 10^4

📎 SAMPLE INPUT 1:
3
1 2 3

📎 SAMPLE OUTPUT 1:
1.000000

📎 SAMPLE INPUT 2:
4
1 2 3 4

📎 SAMPLE OUTPUT 2:
2.000000

💡 HINT: Kelemahan sebagai fungsi x adalah MAKSIMUM dari banyak fungsi yang
         masing-masing linear terhadap x (setiap subarray menyumbang satu
         fungsi linear). Maksimum dari kumpulan fungsi linear selalu
         CEMBUNG — jadi fungsinya unimodal dan ternary search berlaku,
         tanpa kamu perlu membuktikan unimodalitasnya satu per satu.
         Untuk menghitung kelemahan pada sebuah x, kamu butuh jumlah
         subarray maksimum DAN minimum dari b — keduanya bisa dihitung
         dalam satu sapuan O(N) dengan teknik dari Day 35.
         Hitung dulu total biayanya: berapa iterasi dikali dua evaluasi
         dikali O(N)? Apakah muat dalam batas waktu?

🎯 Learning Goals:
- [ ] Memakai teorema "max fungsi linear itu cembung" untuk membenarkan ternary
- [ ] Menggabungkan ternary search dengan Kadane
- [ ] Menghitung total biaya sebelum memilih jumlah iterasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: fungsi kelemahan(x) memakai Kadane maksimum dan minimum

    // TODO: ternary search pada rentang yang memuat jawaban

    return 0;
}
