/*
============================================================
🏋️ Exercise 5: Penjadwalan Server dengan Penalti Acak
============================================================
Day: 269 | Difficulty: Hard | Topic: Li Chao Tree (Task Scheduling)
Source: Scheduling Optimization with Li Chao Tree
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pusat komputasi awan memproses N batch antrean pekerjaan bernomor 1 sampai N.
Batch ke-i memiliki waktu proses t[i] dan faktor penalti p[i].
Nilai t[i] dan p[i] TIDAK DIJAMIN TERURUT (bisa bernilai acak).

Sistem dapat melakukan partisi antrean. Pekerjaan ke-1 sudah berada pada basis dengan dp[0] = 0.
Untuk menyelesaikan pekerjaan ke-i (i > 1), sistem dapat memilih salah satu titik pemutus j (j < i)
dengan biaya penalti:
`dp[i] = min_{0 <= j < i} { dp[j] + t[j] * p[i] + K }`.
Di mana K adalah biaya tetap overhead server pada setiap transisi.

Tentukan TOTAL BIAYA PENALTI MINIMUM untuk memproses seluruh N pekerjaan sampai pekerjaan ke-N!

Selesaikan dengan LI CHAO TREE dalam waktu O(N log N)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- Baris kedua berisi N bilangan bulat t[0], ..., t[N-1].
- Baris ketiga berisi N bilangan bulat p[0], ..., p[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya penalti minimum.

📏 CONSTRAINTS:
- 1 <= N <= 200.000
- 0 <= K <= 1.000.000.000
- -1.000.000 <= t[i], p[i] <= 1.000.000

📎 SAMPLE INPUT 1:
3 10
4 1 2
2 5 3

📎 SAMPLE OUTPUT 1:
22

[Penjelasan Sample 1:
Pekerjaan 0: t=4, p=2 -> dp[0] = 0. Garis L0: y = 4x + 0.
Pekerjaan 1: p[1] = 5 -> dp[1] = dp[0] + t[0]*p[1] + 10 = 0 + 4*5 + 10 = 30. Garis L1: y = 1x + 30.
Pekerjaan 2: p[2] = 3 ->
- dari j=0: dp[0] + t[0]*p[2] + 10 = 0 + 4*3 + 10 = 22.
- dari j=1: dp[1] + t[1]*p[2] + 10 = 30 + 1*3 + 10 = 43.
Minimum = 22.]

📎 SAMPLE INPUT 2:
1 100
5
10

📎 SAMPLE OUTPUT 2:
0

💡 HINT:
- Parameter garis j: kemiringan `m = t[j]`, intersep `b = dp[j]`.
- Titik evaluasi pada i: `x = p[i]`.
- Karena p[i] dan t[j] acak, gunakan Li Chao Tree di atas himpunan nilai p[i].

🎯 Learning Goals:
- [ ] Mengidentifikasi variabel garis dan kueri pada problem penjadwalan acak.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll k;
    if (!(cin >> n >> k)) return 0;

    // TODO: Selesaikan dengan Li Chao Tree

    return 0;
}
