/*
============================================================
📋 TUGAS 12: Beautiful Array
============================================================
Source: Codeforces 1155D
Difficulty: Hard
Topics: kadane + tiga state

PROBLEM:
Diberikan array N bilangan dan bilangan x. Kamu boleh memilih PALING
BANYAK satu subarray dan mengalikan seluruh elemennya dengan x (boleh
juga tidak memilih apa pun). Setelah itu, cari jumlah subarray
maksimum. Subarray BOLEH KOSONG, sehingga jawabannya minimal 0.

Sudut pandangnya: saat berjalan dari kiri ke kanan, setiap posisi
berada di salah satu dari tiga keadaan - belum masuk bagian yang
dikali, sedang berada di dalamnya, atau sudah melewatinya.

INPUT FORMAT:
- Baris pertama: N dan x
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 1 <= N <= 3*10^5
- -100 <= x <= 100
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - x negatif membalik kerugian jadi keuntungan
input:
5 -2
-3 8 -2 1 -6
output:
22
penjelasan: kalikan subarray [-2,1,-6] dengan -2 -> [4,-2,12].
Array jadi [-3,8,4,-2,12], jumlah subarray maksimumnya 8+4-2+12 = 22.

SAMPLE 2 - array panjang berpola
input:
12 -3
1 3 3 7 1 3 3 7 1 3 3 7
output:
42
penjelasan: sample resmi Codeforces. Berguna untuk memastikan
transisi antar state kamu benar pada input yang lebih besar.

SAMPLE 3 - lebih baik tidak melakukan apa-apa
input:
5 10
-1 -2 -3 -4 -5
output:
0
penjelasan: semua elemen negatif, dan x = 10 hanya memperburuknya.
Karena subarray boleh kosong, jawabannya 0. Uji apakah kodemu berani
memilih "tidak mengambil apa pun".

SAMPLE 4 - x = 0 berarti menghapus satu segmen
input:
3 0
5 -3 5
output:
10
penjelasan: x = 0 mengubah operasi menjadi "nolkan satu subarray".
Nolkan [-3] -> [5,0,5] -> jumlahnya 10. Kasus x = 0 sering terlupakan
karena orang menganggap perkalian selalu mengubah besaran.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- dp[0] = belum mulai dikali, dp[1] = sedang di dalam, dp[2] = sudah selesai
- transisi: dp0 -> dp1 -> dp2, tidak boleh mundur
- ketiganya berbasis Kadane BOLEH KOSONG, jadi lantainya 0
- uji x = 0, x = 1, dan x negatif
- pakai long long: 3*10^5 * 10^9 * 100 jelas melewati int
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Tiga state: belum mulai dikali, sedang di dalam bagian yang dikali, sudah selesai dikali.

    return 0;
}
