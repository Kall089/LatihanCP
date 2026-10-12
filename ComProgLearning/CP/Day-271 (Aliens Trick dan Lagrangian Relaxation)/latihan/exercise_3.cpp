/*
============================================================
🏋️ Exercise 3: Memilih K Interval Berbobot Maksimum yang Saling Lepas
============================================================
Day: 271 | Difficulty: Hard | Topic: Aliens Trick (Lagrangian Relaxation)
Source: Maximum Weight K Disjoint Intervals
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N interval pekerjaan bernomor 1 sampai N.
Pekerjaan ke-i dimulai pada waktu L[i], selesai pada waktu R[i], dan memberikan keuntungan sebesar W[i].
Dua pekerjaan i dan j dikatakan tidak tumpang tindih jika waktu selesainya tidak mendahului waktu mulainya,
yaitu R[i] <= L[j] atau R[j] <= L[i].
Kamu diperbolehkan memilih PALING BANYAK K pekerjaan yang saling lepas (tidak tumpang tindih).

Tentukan TOTAL KEUNTUNGAN MAKSIMUM yang dapat diperoleh dengan memilih paling banyak K pekerjaan!

Selesaikan dengan ALIENS TRICK (WQS Binary Search) dalam waktu O(N log N + N log(MaxWeight))!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan K.
- N baris berikutnya masing-masing berisi tiga bilangan bulat: L[i], R[i], dan W[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total keuntungan maksimum.

📏 CONSTRAINTS:
- 1 <= K <= N <= 100.000
- 0 <= L[i] < R[i] <= 1.000.000.000
- 1 <= W[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
3 2
1 3 10
2 5 20
4 6 15

📎 SAMPLE OUTPUT 1:
25

[Penjelasan Sample 1:
Pilih K = 2 interval: [1, 3] (bobot 10) dan [4, 6] (bobot 15).
Keduanya saling lepas (3 <= 4). Total bobot = 10 + 15 = 25.]

📎 SAMPLE INPUT 2:
3 1
1 3 10
2 5 20
4 6 15

📎 SAMPLE OUTPUT 2:
20

[Penjelasan Sample 2:
Dengan K = 1, pilih interval tunggal terbaik yaitu [2, 5] dengan bobot 20.]

💡 HINT:
- Urutkan interval berdasarkan waktu selesai R[i] menaik.
- Untuk setiap interval i, cari indeks interval terakhir prev(i) dengan R[prev(i)] <= L[i]
  menggunakan binary search (upper_bound) dalam O(log N).
- Terapkan penalti biaya lambda >= 0 setiap kali satu interval dipilih.
- Transisi DP untuk penalti lambda:
  dp[i] = max(dp[i-1], {dp[prev(i)].val + W[i] - lambda, dp[prev(i)].cnt + 1}).
- Gunakan Binary Search pada rentang lambda [0, max_total_weight].
- Jawaban asli: dp[N].val + K * lambda*.

🎯 Learning Goals:
- [ ] Menerapkan Aliens Trick pada masalah Interval Scheduling berbobot.
- [ ] Menghilangkan dimensi batas K pada Weighted Activity Selection.
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

    // TODO: Selesaikan dengan Aliens Trick O(N log N)

    return 0;
}
