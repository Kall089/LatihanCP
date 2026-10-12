/*
============================================================
🏋️ Exercise 5: Pasangan Terbalik Kuat
============================================================
Day: 44 | Difficulty: Hard
Topic: Merge dua fase
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Hitung banyaknya pasangan indeks
(i, j) dengan i < j dan a[i] > 2 * a[j].
Perhatikan bahwa kondisinya BUKAN a[i] > a[j], melainkan melibatkan
pengali 2. Perhatikan juga bahwa nilainya bisa negatif, sehingga 2 * a[j]
bisa lebih kecil maupun lebih besar dari a[j].
Karena N bisa mencapai 5 * 10^4, pendekatan O(N^2) berisiko TLE.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 <= N <= 5 * 10^4
- -2^31 <= a[i] <= 2^31 - 1

📎 SAMPLE INPUT 1:
5
1 3 2 3 1

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
5
2 4 3 5 1

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Strukturnya mirip Exercise 3, tetapi ada satu perbedaan penting:
         kondisi yang kamu hitung (melibatkan pengali 2) BERBEDA dari
         kondisi yang dipakai untuk menggabungkan (perbandingan biasa).
         Karena itu kamu tidak bisa menghitung dan menggabungkan dalam satu
         loop yang sama. Pisahkan menjadi dua fase.
         Pada fase penghitungan, kedua bagian sudah terurut — jadi kamu
         bisa memakai dua penunjuk yang sama-sama hanya MAJU.
         Perhatikan juga tipe data saat mengalikan dengan 2.

🎯 Learning Goals:
- [ ] Memisahkan fase menghitung dan fase menggabungkan
- [ ] Memakai two pointers di dalam merge sort
- [ ] Mewaspadai overflow saat mengalikan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: rekursi; fase 1 hitung dengan two pointers, fase 2 merge biasa

    return 0;
}
