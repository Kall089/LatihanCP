/*
============================================================
🏋️ Exercise 1: Segmen Terpanjang dengan Jumlah Terbatas
============================================================
Day: 34 | Difficulty: Easy
Topic: Window terpanjang
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang pembaca punya N buku yang tersusun berurutan di rak, dan buku ke-i
membutuhkan waktu a[i] menit untuk dibaca. Ia ingin membaca sebanyak mungkin
buku BERURUTAN (tidak boleh melompat) dengan total waktu tidak melebihi T menit.
Cetak jumlah buku terbanyak yang bisa ia baca.
Semua a[i] dijamin bernilai positif — perhatikan bahwa ini yang membuat
sliding window boleh dipakai.

📥 INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah buku terbanyak

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= T <= 10^9
- 1 <= a[i] <= 10^4

📎 SAMPLE INPUT 1:
4 5
3 1 2 1

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3 1
5 5 5

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Perluas ujung kanan satu per satu. Kalau totalnya melewati T,
         majukan ujung kiri sampai kembali muat. Catat panjangnya SETELAH
         window kembali layak, bukan sebelumnya.

🎯 Learning Goals:
- [ ] Menulis kerangka window terpanjang
- [ ] Menangani kasus semua elemen lebih besar dari T
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca n dan T

    // TODO: l = 0, sum = 0, best = 0

    // TODO: untuk r = 0..n-1: sum += a[r];
    //       while (sum > T) { sum -= a[l]; l++; }
    //       best = max(best, r - l + 1);

    return 0;
}
