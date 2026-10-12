/*
============================================================
📋 TUGAS 11: Maximum Subarray Sum II
============================================================
Source: CSES 1644
Difficulty: Hard
Topics: BUKAN kadane - prefix sum + monotonic deque

PROBLEM:
Cari jumlah subarray maksimum dengan syarat PANJANG subarray berada di
antara a dan b (inklusif). Subarray tidak boleh kosong.

Kenapa Kadane gagal: bukti Kadane berbunyi "subarray terbaik yang
berakhir di i = subarray terbaik yang berakhir di i-1, ditambah a[i]".
Begitu ada batas panjang, langkah itu runtuh - subarray terbaik di i-1
mungkin sudah mentok panjangnya, sehingga memperpanjangnya ILEGAL.
Diagnosisnya: state-nya kurang.

INPUT FORMAT:
- Baris pertama: N, a, dan b
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= a <= b <= N <= 2*10^5
- -10^9 <= x[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - panjang 1 sampai 2
input:
8 1 2
-1 3 -2 5 3 -5 2 2
output:
8
penjelasan: [5,3] = 8. Kadane biasa akan menjawab 9 dengan
[3,-2,5,3] yang panjangnya 4 - melanggar batas b = 2.

SAMPLE 2 - array sama, batas panjang berbeda
input:
8 3 4
-1 3 -2 5 3 -5 2 2
output:
9
penjelasan: [3,-2,5,3] panjangnya 4, kini sah. Bandingkan dengan
sample 1: array identik, jawaban berbeda. Panjang benar-benar bagian
dari soal.

SAMPLE 3 - semua negatif dengan panjang minimum > 1
input:
5 2 3
-4 -2 -7 -1 -9
output:
-6
penjelasan: kamu DIPAKSA mengambil minimal 2 elemen, jadi tidak bisa
sekadar memilih elemen terbesar. [-2,-7] = -9, [-7,-1] = -8,
[-1,-9] = -10, [-4,-2] = -6 <- terbaik.

SAMPLE 4 - jendela di tengah
input:
7 2 5
2 -5 7 -1 3 -6 4
output:
9
penjelasan: [7,-1,3] = 9, panjang 3.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- pakai prefix sum: sum(l..r) = P[r] - P[l-1]
- kunci r, lalu cari P minimum pada jendela indeks [r-b, r-a]
- jendela itu bergerak ke kanan secara monoton -> monotonic deque
  (Day 37). Kalau belum sampai Day 37, sparse table juga bisa
- perhatikan batas jendela saat r masih kecil (r-b bisa negatif)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Kadane TIDAK bisa membatasi panjang. Pakai prefix sum + monotonic deque (Day 37) untuk mencari prefix minimum dalam jendela geser.

    return 0;
}
