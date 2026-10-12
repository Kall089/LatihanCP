/*
============================================================
🏋️ Exercise 3: Peringkat Penuh
============================================================
Day: 38 | Difficulty: Medium
Topic: Kompresi jenis B (setiap posisi unik)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Ubahlah array itu menjadi sebuah
PERMUTASI dari 0 sampai N-1, dengan aturan:
- Elemen yang nilainya lebih kecil mendapat peringkat lebih kecil.
- Jika dua elemen nilainya SAMA, yang indeksnya lebih kecil mendapat
  peringkat lebih kecil.
Cetak array peringkat yang dihasilkan.
Perhatikan bahwa ini BERBEDA dari kompresi biasa: di sini nilai yang sama
tetap mendapat peringkat yang berbeda.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
10 50 10 30

📎 SAMPLE OUTPUT 1:
0 3 1 2

📎 SAMPLE INPUT 2:
3
5 5 5

📎 SAMPLE OUTPUT 2:
0 1 2

💡 HINT: Urutkan INDEKS-nya, bukan nilainya. Bandingkan berdasarkan nilai
         terlebih dahulu, lalu berdasarkan indeks sebagai pemecah seri.
         Setelah terurut, posisi ke-k dalam urutan itu adalah peringkat
         untuk indeks yang bersangkutan.

🎯 Learning Goals:
- [ ] Membedakan kompresi jenis A dan jenis B
- [ ] Mengurutkan indeks dengan komparator kustom
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: buat vektor indeks 0..n-1

    // TODO: urutkan indeks berdasarkan (nilai, indeks)

    // TODO: rank[urut[k]] = k

    return 0;
}
