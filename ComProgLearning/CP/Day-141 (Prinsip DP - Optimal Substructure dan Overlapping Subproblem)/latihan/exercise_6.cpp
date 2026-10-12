/*
============================================================
🏋️ Exercise 6: Lompatan Minimum
============================================================
Day: 85 | Difficulty: Hard
Topic: DP 1D — pola minimal + jangkauan
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N batu berjajar. Batu ke-i punya kekuatan lompat a[i], artinya dari
batu ke-i kamu bisa melompat ke batu mana pun dari (i+1) sampai (i + a[i]).
Kamu mulai dari batu ke-1 dan ingin mencapai batu ke-N.
Tentukan jumlah lompatan MINIMAL yang dibutuhkan.
Jika batu ke-N tidak bisa dicapai, cetak -1.

📥 INPUT FORMAT:
- Baris pertama: bilangan N
- Baris kedua: N bilangan a[1..N]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah lompatan minimal, atau -1.

📏 CONSTRAINTS:
- 1 <= N <= 5000
- 0 <= a[i] <= N

📎 SAMPLE INPUT 1:
5
2 3 1 1 4

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
5
3 2 1 0 4

📎 SAMPLE OUTPUT 2:
-1

📎 SAMPLE INPUT 3:
1
0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- dp[i] = lompatan minimal untuk mencapai batu ke-i.
- Dari batu i, perbarui semua batu j yang bisa dicapai: dp[j] = min(dp[j], dp[i] + 1).
- Basis: dp[1] = 0 (sudah berada di sana, belum melompat).
- Batu yang tidak terjangkau tetap bernilai INF; kalau dp[N] masih INF, cetak -1.
- Perhatikan sample 3: N = 1, jadi kita sudah di tujuan tanpa melompat.

🎯 Learning Goals:
- [ ] Menerapkan DP dengan transisi ke depan (forward DP)
- [ ] Menangani simpul yang tidak terjangkau
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan array a

    // TODO: dp[1] = 0, sisanya INF

    // TODO: Untuk tiap i yang terjangkau, perbarui dp[j] untuk j = i+1 .. i+a[i]

    return 0;
}
