/*
============================================================
🏋️ Exercise 4: Difference Array 2D — Cat Dinding
============================================================
Day: 29 | Difficulty: Medium-Hard
Topic: Difference Array 2D
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah dinding berbentuk grid N baris × M kolom. Setiap petak awalnya
punya ketebalan cat 0. Ada Q perintah pengecatan, masing-masing berbentuk
"r1 c1 r2 c2 v" yang berarti menambah ketebalan cat sebanyak v pada
SELURUH petak di dalam persegi panjang dari (r1, c1) sampai (r2, c2).
Setelah semua pengecatan selesai, cetak ketebalan cat seluruh dinding.

Karena N × M dan Q sama-sama besar, mengecat petak satu per satu
untuk setiap perintah jelas terlalu lambat.

📥 INPUT FORMAT:
- Baris pertama: tiga integer N, M, dan Q
- Q baris berikutnya: lima integer r1, c1, r2, c2, v

📤 OUTPUT FORMAT:
- N baris, masing-masing berisi M integer (dipisah spasi):
  ketebalan cat akhir tiap petak.

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 1000
- 1 ≤ Q ≤ 10^5
- 1 ≤ r1 ≤ r2 ≤ N, 1 ≤ c1 ≤ c2 ≤ M
- 1 ≤ v ≤ 10^9  (gunakan long long!)

📎 SAMPLE INPUT 1:
3 3 2
1 1 2 2 1
2 2 3 3 2

📎 SAMPLE OUTPUT 1:
1 1 0
1 3 2
0 2 2

📎 SAMPLE INPUT 2:
2 4 1
1 2 2 3 5

📎 SAMPLE OUTPUT 2:
0 5 5 0
0 5 5 0

💡 HINT:
- Di 1D efek update bocor ke kanan, jadi butuh 1 penambal di r+1.
- Di 2D efek bocor ke kanan DAN ke bawah, jadi butuh 3 penambal.
- Pojok kanan-bawah terlanjur dikurangi dua kali, kembalikan sekali:
    d[r1][c1] += v;      d[r1][c2+1] -= v;
    d[r2+1][c1] -= v;    d[r2+1][c2+1] += v;
- Rekonstruksinya adalah prefix sum 2D biasa.

🎯 Learning Goals:
- [ ] Memperluas difference array dari 1 ke 2 dimensi
- [ ] Memahami inklusi-eksklusi pada empat titik penanda
- [ ] Menyiapkan array berukuran (N+2) × (M+2) agar aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N, M, Q

    // TODO: Siapkan grid difference berukuran (N+2) x (M+2)

    // TODO: Untuk setiap perintah, tandai EMPAT titik

    // TODO: Rekonstruksi dengan prefix sum 2D lalu cetak

    return 0;
}
