/*
============================================================
🏋️ Exercise 5: Difference Array 2D (Range Update Offline)
============================================================
Day: 30 | Difficulty: Medium-Hard
Topic: Difference Array 2D & Prefix Sum 2D Reconstruction
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Awalnya kamu memiliki matriks berukuran N × M yang berisi semua angka 0.
Kamu diberikan Q buah perintah update. Setiap update ditentukan oleh (r1, c1, r2, c2, val)
yang menambahkan nilai `val` ke semua sel di submatriks (r1, c1) hingga (r2, c2).

Setelah seluruh Q update dilakukan, cetaklah matriks hasil akhirnya!

Input 1-indexed.

📥 INPUT FORMAT:
- Baris pertama: N, M, Q (1 ≤ N, M ≤ 1000, 1 ≤ Q ≤ 10^5)
- Q baris berikutnya: r1 c1 r2 c2 val (1 ≤ r1 ≤ r2 ≤ N, 1 ≤ c1 ≤ c2 ≤ M, -10^9 ≤ val ≤ 10^9)

📤 OUTPUT FORMAT:
- Cetak matriks N × M hasil akhir setelah Q update.

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 1000
- 1 ≤ Q ≤ 10^5
- -10^9 ≤ val ≤ 10^9 (Gunakan long long!)

📎 SAMPLE INPUT 1:
3 3 2
1 1 2 2 5
2 2 3 3 3

📎 SAMPLE OUTPUT 1:
5 5 0
5 8 3
0 3 3

📎 EXPLANATION 1:
Update 1 (+5 pada [1..2][1..2]):
5 5 0
5 5 0
0 0 0

Update 2 (+3 pada [2..3][2..3]):
5 5 0
5 8 3
0 3 3

💡 HINT:
- Jika melakukan update manual per sel, kompleksitasnya O(Q × N × M) -> TLE!
- Gunakan **Difference Array 2D**:
  diff[r1][c1] += val;
  diff[r1][c2 + 1] -= val;
  diff[r2 + 1][c1] -= val;
  diff[r2 + 1][c2 + 1] += val;
- Setelah semua Q update selesai, jalankan Prefix Sum 2D pada matriks `diff` untuk merekonstruksi matriks asli dalam O(N × M)!

🎯 Learning Goals:
- [ ] Menerapkan 2D Difference Array untuk range update O(1) per operasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // TODO: Deklarasi diff array 2D berukuran (N+2) x (M+2) dengan long long

    // TODO: Proses Q update ke diff array dalam O(1) per update

    // TODO: Rekonstruksi matriks menggunakan Prefix Sum 2D pada diff array

    // TODO: Cetak matriks N x M hasil akhir

    return 0;
}
