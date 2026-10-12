/*
============================================================
🏋️ Exercise 6: Pengurutan Setelah K Sapuan
============================================================
Day: 43 | Difficulty: Hard (Contest-level)
Topic: Simulasi bubble sort terbatas
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan dan sebuah bilangan K. Jalankan bubble
sort pada array itu, tetapi HENTIKAN setelah tepat K sapuan penuh dari
kiri ke kanan (atau lebih awal kalau array sudah terurut sebelum itu).
Satu "sapuan penuh" berarti sekali berjalan dari indeks 0 sampai indeks
terakhir yang belum beres, menukar setiap pasangan berdampingan yang
terbalik.
Cetak keadaan array setelah proses berhenti, dan cetak juga berapa sapuan
yang benar-benar dilakukan.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya sapuan yang dilakukan
- Baris kedua: N bilangan keadaan akhir array

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 0 <= K <= N
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5 1
5 4 3 2 1

📎 SAMPLE OUTPUT 1:
1
4 3 2 1 5

📎 SAMPLE INPUT 2:
4 10
1 2 3 4

📎 SAMPLE OUTPUT 2:
1
1 2 3 4

📎 SAMPLE INPUT 3:
4 2
3 1 4 2

📎 SAMPLE OUTPUT 3:
2
1 2 3 4

💡 HINT: Perhatikan sampel 2 dengan saksama: K = 10 tetapi jawabannya 1.
         Artinya sapuan yang "membuktikan array sudah terurut" tetap
         DIHITUNG sebagai satu sapuan.
         Perhatikan juga bahwa batas kanan sapuan menyusut setiap putaran,
         karena ekor array sudah berada di posisi akhirnya.

🎯 Learning Goals:
- [ ] Menerjemahkan deskripsi proses menjadi kode dengan tepat
- [ ] Memperhatikan definisi pencacahan yang diberikan soal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: jalankan paling banyak K sapuan

    // TODO: berhenti lebih awal kalau satu sapuan tidak menghasilkan pertukaran

    // TODO: hitung sapuan yang BENAR-BENAR dilakukan

    return 0;
}
