/*
============================================================
📋 TUGAS 07: Sum of Subarray Minimums
============================================================
Source: LeetCode 907
Difficulty: Hard
Topics: monotonic stack + menghitung KONTRIBUSI (Day 36 + 40)

PROBLEM:
Diberikan array N bilangan. Untuk SETIAP subarray, ambil nilai
minimumnya, lalu jumlahkan semua nilai minimum itu. Cetak hasilnya
modulo 1000000007.

Membalik cara pandang adalah kuncinya. Jangan bertanya "berapa minimum
subarray ini" untuk tiap subarray (itu O(n^2)). Tanyakan sebaliknya:
"elemen a[i] menjadi minimum pada BERAPA BANYAK subarray?"

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan modulo 1000000007

CONSTRAINTS:
- 1 <= N <= 3*10^4
- 1 <= a[i] <= 3*10^4

------------------------------------------------------------
SAMPLE 1 - kasus kecil, hitung manual dulu
input:
4
3 1 2 4
output:
17
penjelasan: minimum dari 10 subarray: 3,1,1,1,1,1,2,2,2,4 = 17.
Coba juga lewat kontribusi: a[2]=1 menjadi minimum pada 2*3 = 6
subarray, menyumbang 6. Dua cara harus memberi angka sama.

SAMPLE 2 - kasus acak
input:
5
11 81 94 43 3
output:
444

SAMPLE 3 - N = 1
input:
1
7
output:
7

SAMPLE 4 - SEMUA KEMBAR, ini jebakannya
input:
3
2 2 2
output:
12
penjelasan: ada 6 subarray, semuanya bernilai minimum 2, jadi 12.
Kalau kamu memakai kondisi pop yang sama (misalnya <= di kedua sisi),
subarray yang sama akan terhitung DUA KALI dan jawabanmu jadi lebih
besar. Aturannya: satu sisi pakai < dan sisi lain pakai <=, supaya
tiap subarray dimiliki tepat satu elemen.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kontribusi a[i] = a[i] * (i - kiri[i]) * (kanan[i] - i)
  dengan kiri[i] = indeks elemen LEBIH KECIL terdekat di kiri
       kanan[i] = indeks elemen LEBIH KECIL ATAU SAMA terdekat di kanan
  (atau kebalikannya - yang penting ASIMETRIS)
- verifikasi dengan brute force O(n^2) pada n <= 100 sebelum submit
- modulo di akhir tiap penambahan
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
