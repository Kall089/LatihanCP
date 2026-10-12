/*
============================================================
🏋️ Exercise 3: Relai Pengiriman di Jalur Pantai (Classic Monotone DP CHT)
============================================================
Day: 268 | Difficulty: Hard | Topic: Convex Hull Trick (Dynamic DP)
Source: Codeforces 319C (Kalila and Dimna in the Logging Industry)
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N pos relai pengiriman di sepanjang jalur pantai bernomor 1 sampai N.
Pos 1 sudah aktif sejak awal dengan biaya 0.
Tujuanmu adalah mengaktifkan pos ke-N dengan total biaya seminimum mungkin.

Setiap pos i memiliki dua parameter: a[i] dan b[i].
Diketahui bahwa:
- Nilai a terurut TIDAK MENURUN: a[0] <= a[1] <= ... <= a[N-1].
- Nilai b terurut TIDAK MENAIK: b[0] >= b[1] >= ... >= b[N-1].
- a[0] = 1, b[N-1] = 0.

Untuk mengaktifkan pos i (di mana i > 1), kamu harus memilih SALAH SATU pos j yang sudah aktif sebelumnya (j < i).
Biaya pengaktifan pos i dari pos j adalah:
`Biaya(j, i) = dp[j] + b[j] * a[i]`.

Tentukan TOTAL BIAYA MINIMUM untuk mengaktifkan pos ke-N!

Selesaikan dengan CONVEX HULL TRICK DENGAN DEQUE dalam waktu O(N)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat a[0], a[1], ..., a[N-1].
- Baris ketiga berisi N bilangan bulat b[0], b[1], ..., b[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum mengaktifkan pos N.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- 0 <= a[i], b[i] <= 1.000.000
- a[i] tidak menurun, b[i] tidak menaik

📎 SAMPLE INPUT 1:
3
1 2 3
5 3 1

📎 SAMPLE OUTPUT 1:
15

[Penjelasan Sample 1:
- dp[0] = 0 (pos 1 sudah aktif). Garis 0: y = 5x + 0.
- Pos 2 (a[1] = 2): dp[1] = dp[0] + b[0] * a[1] = 0 + 5 * 2 = 10. Garis 1: y = 3x + 10.
- Pos 3 (a[2] = 3):
  Pilih dari pos 0: 0 + 5 * 3 = 15.
  Pilih dari pos 1: 10 + 3 * 3 = 19.
  Minimum = 15.]

📎 SAMPLE INPUT 2:
1
10
4

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
3
0 0 0
0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Rekurensi: `dp[i] = min_{0 <= j < i} { dp[j] + b[j] * a[i] }`.
- Setiap state j menghasilkan garis: `slope m = b[j]`, `intercept c = dp[j]`.
- Titik evaluasi pada i: `x = a[i]`.
- Karena b tidak menaik, slope monoton menurun.
- Karena a tidak menurun, kueri x monoton menaik.
- Gunakan Lower Convex Hull berbasis Deque!

🎯 Learning Goals:
- [ ] Menyelesaikan permasalahan arketipe legendaris Kalila & Dimna menggunakan CHT Deque.
- [ ] Memahami hubungan langsung parameter array masukan dengan garis-garis CHT.
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

    // TODO: Selesaikan dengan CHT Deque

    return 0;
}
