/*
============================================================
🏋️ Exercise 5: Partisi Pasangan Kembar Minimum (Two-Pointer D&C DP)
============================================================
Day: 267 | Difficulty: Menantang | Topic: Divide & Conquer DP with Sliding Pointers
Source: Codeforces 868F (Yet Another Minimization Problem)
Time Limit: 2.5 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah array bilangan bulat a[0], a[1], ..., a[N-1] berukuran N.
Kamu diminta untuk membagi array tersebut menjadi TEPAT K segmen berurutan tak kosong.
Biaya dari suatu segmen [l..r] didefinisikan sebagai BANYAKNYA PASANGAN INDEKS (i, j)
sedemikian sehingga l <= i < j <= r dan a[i] == a[j] (pasangan elemen yang bernilai sama).

Tentukan TOTAL BIAYA MINIMUM untuk membagi seluruh array menjadi tepat K segmen!

Selesaikan dengan algoritma DIVIDE & CONQUER DP OPTIMIZATION dipadukan dengan
SLIDING WINDOW / TWO POINTERS untuk menghitung biaya segmen!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum.

📏 CONSTRAINTS:
- 1 <= K <= min(N, 20)
- 1 <= N <= 20.000
- 1 <= a[i] <= N

📎 SAMPLE INPUT 1:
7 3
1 1 3 3 3 2 1

📎 SAMPLE OUTPUT 1:
1

[Penjelasan Sample 1:
Bagi menjadi 3 segmen:
- Segmen 1: [1, 1] -> 1 pasang angka kembar (biaya = 1)
- Segmen 2: [3, 3, 3] -> tunggu: jika [1, 1] biayanya 1, lalu [3, 3, 3] biayanya 3 (total 4).
Alternatif:
- Segmen 1: [1] (biaya 0)
- Segmen 2: [1, 3] (biaya 0)
- Segmen 3: [3, 3, 2, 1] (pasang 3-3 = 1, total biaya = 1).
Biaya minimum = 1.]

📎 SAMPLE INPUT 2:
6 2
1 2 1 2 1 2

📎 SAMPLE OUTPUT 2:
2

[Penjelasan Sample 2:
Bagi menjadi [1, 2, 1] (biaya 1 dari sepasang 1-1) dan [2, 1, 2] (biaya 1 dari sepasang 2-2).
Total biaya = 1 + 1 = 2.]

💡 HINT:
- Banyak pasangan kembar pada segmen [l..r] adalah `sum_x C(count_x, 2)`.
- Fungsi biaya ini memenuhi sifat Monge / Quadrangle Inequality.
- Karena biaya segmen tidak bisa dihitung dalam O(1) dengan prefix sum sederhana,
  gunakan DUA POINTER GLOBAL (`cur_l` dan `cur_r`) yang bergeser masuk/keluar mirip algoritma Mo.
- Total pergeseran pointer pada seluruh level rekursi D&C terbukti hanya O(N log N)!

🎯 Learning Goals:
- [ ] Menguasai integrasi teknik Sliding Pointer / Window ke dalam rekursi D&C DP.
- [ ] Memahami bukti amortisasi gerak pointer O(N log N) per layer DP.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan D&C DP + Two Pointers

    return 0;
}
