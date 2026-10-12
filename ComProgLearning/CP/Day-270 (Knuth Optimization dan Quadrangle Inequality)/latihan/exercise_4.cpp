/*
============================================================
🏋️ Exercise 4: Pohon Pencarian Biner Optimal (Optimal BST)
============================================================
Day: 270 | Difficulty: Hard | Topic: Knuth Optimization (Optimal Binary Search Tree)
Source: Classic Computer Science OBST (Donald Knuth)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N buah kunci terurut k[1] < k[2] < ... < k[N].
Setiap kunci k[i] memiliki frekuensi pencarian f[i].
Kita ingin menyusun N kunci tersebut ke dalam sebuah Binary Search Tree (BST) sehingga
total biaya pencarian seluruh kunci seminimum mungkin.

Definisi Biaya Pencarian:
- Simpul akar (root) pohon memiliki kedalaman (depth) 1.
- Setiap anak memiliki kedalaman = kedalaman orang tua + 1.
- Biaya pencarian kunci k[i] adalah: `depth(k[i]) * f[i]`.
- Total biaya pohon adalah: `sum_{i=1}^N (depth(k[i]) * f[i])`.

Tentukan TOTAL BIAYA PENCARIAN MINIMUM dari BST optimal yang dapat dibentuk!

Selesaikan dengan KNUTH OPTIMIZATION dalam waktu O(N^2)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat positif f[0], f[1], ..., f[N-1] (frekuensi pencarian).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya pencarian minimum.

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= f[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3
10 12 20

📎 SAMPLE OUTPUT 1:
72

[Penjelasan Sample 1:
Konfigurasi pohon terbaik memilih kunci 1 (f=12) sebagai akar:
- Kunci 1 di kedalaman 1: 1 * 12 = 12.
- Kunci 0 (f=10) di anak kiri (kedalaman 2): 2 * 10 = 20.
- Kunci 2 (f=20) di anak kanan (kedalaman 2): 2 * 20 = 40.
Total biaya = 12 + 20 + 40 = 72.]

📎 SAMPLE INPUT 2:
1
25

📎 SAMPLE OUTPUT 2:
25

💡 HINT:
- Definisikan `dp[l][r]` sebagai biaya minimum sub-pohon untuk kunci l..r (dengan anggapan kedalaman relatif mulai dari 1).
- Rekurensi:
  Jika kunci k dipilih sebagai akar sub-pohon l..r:
  Seluruh simpul di kiri (l..k-1) dan kanan (k+1..r) kedalamannya bertambah 1.
  Maka biaya bertambah sebesar jumlah frekuensi seluruh kunci dalam sub-pohon `sum(l, r)`:
  `dp[l][r] = sum(l, r) + min_{l <= k <= r} (dp[l][k-1] + dp[k+1][r])`.
- Dengan basis `dp[l][l-1] = 0` dan `dp[l][l] = f[l]`.
- Karena fungsi `C(l, r) = sum(l, r)` memenuhi Quadrangle Inequality, titik akar optimal `opt[l][r]` memenuhi:
  `opt[l][r-1] <= opt[l][r] <= opt[l+1][r]`.

🎯 Learning Goals:
- [ ] Menerapkan Knuth Optimization untuk masalah klasik Optimal Binary Search Tree.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization untuk OBST O(N^2)

    return 0;
}
