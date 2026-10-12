/*
============================================================
📋 TUGAS 15: Penugasan Pekerja Dua Shift (Alternating Task Assignment)
============================================================
Source: Original
Difficulty: Medium-Hard
Topics: State Design, Load Balancing DP

PROBLEM:
Terdapat N tugas berurutan yang harus diselesaikan (tugas 0 sampai N-1).
Tersedia dua pekerja: Alice (pekerja 0) dan Bob (pekerja 1).
Menugaskan tugas i kepada Alice membutuhkan waktu timeA[i], sedangkan
menugaskan tugas i kepada Bob membutuhkan waktu timeB[i].
Aturan pergantian shift:
Untuk menjaga stamina, tidak boleh ada pekerja yang mengerjakan LEBIH DARI K TUGAS BERTURUT-TURUT!
(Artinya, setelah seorang pekerja mengerjakan K tugas berturut-turut, tugas berikutnya
WAJIB dikerjakan oleh pekerja lainnya).
Cari total waktu minimum yang dibutuhkan untuk menyelesaikan seluruh N tugas.

INPUT FORMAT:
Baris pertama: N K
Baris kedua: N bilangan bulat timeA[0], ..., timeA[N-1]
Baris ketiga: N bilangan bulat timeB[0], ..., timeB[N-1]

OUTPUT FORMAT:
Satu bilangan bulat: total waktu minimum.

CONSTRAINTS:
1 <= N <= 10.000
1 <= K <= 50
1 <= timeA[i], timeB[i] <= 10.000

SAMPLE INPUT 1:
4 2
10 10 10 10
100 1 1 100

SAMPLE OUTPUT 1:
22
(Penjelasan:
Tugas 0: Alice (10) [Alice streak 1]
Tugas 1: Bob (1) [Bob streak 1]
Tugas 2: Bob (1) [Bob streak 2]
Tugas 3: Alice (10) [Alice streak 1, Bob tidak boleh karena streak sudah 2]
Total waktu = 10 + 1 + 1 + 10 = 22.)

SAMPLE INPUT 2:
3 1
1 10 1
10 1 10

SAMPLE OUTPUT 2:
3
(Penjelasan: K=1 artinya pekerja harus bergantian setiap tugas: Alice (1), Bob (1), Alice (1) = 3.)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // TODO: Definisikan state dp[i][pekerja][streak]
    // pekerja in {0: Alice, 1: Bob}
    // streak in {1 s.d. K}
    // Total state: N x 2 x K = 10.000 x 2 x 50 = 10^6 (sangat cepat dan aman)

    return 0;
}
