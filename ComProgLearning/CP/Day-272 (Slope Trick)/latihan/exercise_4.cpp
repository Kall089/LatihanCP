/*
============================================================
🏋️ Exercise 4: Mengatur Posisi Titik dengan Batas Jarak Maksimum (Lazy Tags)
============================================================
Day: 272 | Difficulty: Hard | Topic: Slope Trick (Full 2-Heap with Lazy Offsets)
Source: Bounded Distance Sequence Alignment
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N objek pada garis bilangan dengan posisi awal target: a_0, a_1, ..., a_{N-1}.
Kamu harus menentukan posisi akhir baru b_0, b_1, ..., b_{N-1} sedemikian sehingga:
1. Seluruh b_i adalah bilangan bulat.
2. Jarak antara dua objek yang bersebelahan tidak melebihi D:
   |b_i - b_{i-1}| <= D untuk setiap i = 1, 2, ..., N-1.
3. Total biaya perpindahan, yaitu sum_{i=0}^{N-1} |a_i - b_i|, bernilai sekecil mungkin.

Selesaikan masalah ini dengan SLOPE TRICK menggunakan DUA PRIORITY QUEUE (Max-Heap L dan Min-Heap R)
serta LAZY TAGS pergeseran dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan D.
- Baris kedua berisi N bilangan bulat a_0, a_1, ..., a_{N-1}.

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya minimum perpindahan.

📏 CONSTRAINTS:
- 1 <= N <= 100.000
- 0 <= D <= 1.000.000.000
- -1.000.000.000 <= a_i <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 5
0 10 20

📎 SAMPLE OUTPUT 1:
10

[Penjelasan Sample 1:
Pilih posisi baru b = [5, 10, 15].
Jarak antar elemen bersebelahan: |10 - 5| = 5 <= 5, dan |15 - 10| = 5 <= 5 (valid).
Total biaya = |0 - 5| + |10 - 10| + |20 - 15| = 5 + 0 + 5 = 10.]

📎 SAMPLE INPUT 2:
3 10
0 10 20

📎 SAMPLE OUTPUT 2:
0

[Penjelasan Sample 2:
Posisi awal sudah memenuhi |10 - 0| <= 10 dan |20 - 10| <= 10, tidak perlu dipindahkan (biaya 0).]

📎 SAMPLE INPUT 3:
2 2
0 10

📎 SAMPLE OUTPUT 3:
8

[Penjelasan Sample 3:
Pilih b = [0, 2] atau b = [4, 6] -> biaya = 8.]

💡 HINT:
- Rekurensi DP:
  dp[i](x) = |x - a_i| + min_{x - D <= y <= x + D} dp[i-1](y).
- Operasi min_{x - D <= y <= x + D} adalah perlebaran daerah minimum (Minkowski Sum dengan [-D, D]).
- Efek pada struktur data:
  - Seluruh breakpoint di L bergeser ke kiri sebesar D (tag_L -= D).
  - Seluruh breakpoint di R bergeser ke kanan sebesar D (tag_R += D).
- Lalu tambahkan |x - a_i| ke struktur data 2-heap:
  - Bandingkan a_i dengan L.top() + tag_L dan R.top() + tag_R.
  - Perbarui min_val dan seimbangkan heap secara tepat.

🎯 Learning Goals:
- [ ] Mengimplementasikan representasi Slope Trick lengkap dengan 2-Heap (L dan R).
- [ ] Menguasai teknik pergeseran lazy (lazy tags) pada infimal convolution / Minkowski sum.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll d;
    if (!(cin >> n >> d)) return 0;

    // TODO: Selesaikan dengan Slope Trick 2-Heap + Lazy Tags O(N log N)

    return 0;
}
