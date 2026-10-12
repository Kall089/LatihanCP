/*
============================================================
📋 TUGAS 05: Sliding Window Maximum
============================================================
Source: LeetCode 239 / CSES 3221
Difficulty: Medium
Topics: monotonic deque (Day 37)

PROBLEM:
Diberikan array N bilangan dan bilangan K. Untuk setiap jendela
berurutan berukuran K, cetak nilai maksimum di dalamnya.

INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

OUTPUT FORMAT:
- N-K+1 bilangan dipisah spasi

CONSTRAINTS:
- 1 <= K <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
8 3
1 3 -1 -3 5 3 6 7
output:
3 3 5 5 6 7

SAMPLE 2 - menurun
input:
4 2
9 8 7 6
output:
9 8 7
penjelasan: saat array menurun, maksimumnya selalu elemen paling kiri
window. Deque tidak pernah mem-pop dari belakang, hanya dari depan.

SAMPLE 3 - K = 1
input:
1 1
4
output:
4
penjelasan: hasilnya array itu sendiri.

SAMPLE 4 - semua sama, K = N
input:
4 4
2 2 2 2
output:
2
penjelasan: dengan nilai kembar, pilihan <= atau < pada kondisi pop
menentukan indeks mana yang bertahan. Nilainya tetap benar, tapi
pahami perbedaannya.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- deque menyimpan INDEKS, bukan nilai
- urutan: buang yang KADALUARSA dari depan, lalu buang yang
  TERTUTUPI dari belakang, baru push
- mulai mencetak saat i >= K-1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini

    return 0;
}
