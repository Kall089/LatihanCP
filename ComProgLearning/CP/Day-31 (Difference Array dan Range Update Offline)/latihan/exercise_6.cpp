/*
============================================================
🏋️ Exercise 6: Menyiram Tanaman (Difference Array Terbalik)
============================================================
Day: 29 | Difficulty: Hard
Topic: Difference Array dibaca terbalik (dari hasil ke operasi)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tanaman berjajar. Tinggi tanaman ke-i yang DIINGINKAN adalah b[i].
Saat ini semua tanaman masih setinggi 0.
Kamu punya alat penyiram yang, dalam satu kali pemakaian, dapat memilih
sebuah rentang tanaman [l, r] dan menambah tinggi SEMUANYA sebanyak 1.

Tentukan berapa kali MINIMAL kamu harus memakai alat penyiram
agar semua tanaman mencapai tinggi yang diinginkan.

📥 INPUT FORMAT:
- Baris pertama: satu integer N
- Baris kedua: N integer b[1], b[2], ..., b[N]

📤 OUTPUT FORMAT:
- Satu integer: jumlah minimal pemakaian alat penyiram.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2 × 10^5
- 0 ≤ b[i] ≤ 10^9  (jawaban bisa mencapai 10^9, gunakan long long)

📎 SAMPLE INPUT 1:
5
1 2 3 2 1

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3
3 1 2

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
4
0 0 0 0

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Setiap pemakaian alat menambah TEPAT SATU nilai positif pada
  difference array (di posisi l), dan satu nilai negatif (di posisi r+1).
- Jadi total pemakaian minimal = jumlah seluruh KENAIKAN pada
  difference array dari array target.
- Rumusnya: jawaban = jumlah dari max(0, b[i] - b[i-1]) untuk semua i,
  dengan b[0] dianggap 0.
- Penjelasan Sample 1: b = 1 2 3 2 1 -> selisih = +1 +1 +1 -1 -1
  -> total kenaikan = 3.

🎯 Learning Goals:
- [ ] Membaca difference array dari arah sebaliknya (hasil -> operasi)
- [ ] Menyadari bahwa satu range update = satu kenaikan pada diff
- [ ] Menyelesaikan soal greedy yang intinya adalah difference array
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan array target b[1..N]

    // TODO: Jumlahkan semua kenaikan: max(0, b[i] - b[i-1])
    //       dengan b[0] = 0

    return 0;
}
