/*
============================================================
🏋️ Exercise 4: Knapsack dengan Barang Sedikit
============================================================
Day: 54 | Difficulty: Medium
Topic: Meet in the middle dengan bobot dan nilai terpisah
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N barang; barang ke-i punya BERAT w[i] dan NILAI v[i].
Sebuah tas mampu menampung total berat paling banyak C.
Pilih subhimpunan barang yang total beratnya tidak melebihi C sehingga
TOTAL NILAINYA maksimum. Cetak nilai maksimum itu.
Perhatikan bahwa berat bisa mencapai 10^15, sehingga pendekatan dynamic
programming berbasis kapasitas MUSTAHIL — tabelnya terlalu besar.

📥 INPUT FORMAT:
- Baris pertama: N dan C
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total nilai maksimum

📏 CONSTRAINTS:
- 1 <= N <= 40
- 1 <= C <= 10^15
- 1 <= w[i] <= 10^15
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
4 5
1 10
2 20
3 30
4 40

📎 SAMPLE OUTPUT 1:
50

📎 SAMPLE INPUT 2:
3 1
2 100
3 200
4 300

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Sekarang setiap subset punya DUA besaran: total berat dan total
         nilai. Urutkan salah satu paruh berdasarkan BERAT.
         Di sinilah ada jebakan yang tidak muncul di Exercise 3: setelah
         diurutkan berdasarkan berat, subset dengan berat lebih kecil bisa
         punya NILAI LEBIH BESAR daripada subset dengan berat lebih besar.
         Artinya, "subset terberat yang masih muat" belum tentu yang
         nilainya terbaik.
         Pikirkan satu langkah pemrosesan tambahan pada paruh yang sudah
         diurutkan yang membuat pencarian binermu langsung memberi jawaban
         terbaik. Petunjuk: kamu ingin agar nilainya menjadi TIDAK MENURUN
         seiring bertambahnya berat.

🎯 Learning Goals:
- [ ] Menangani dua besaran sekaligus
- [ ] Menemukan sendiri kenapa PREFIX MAKSIMUM diperlukan
- [ ] Menyadari kapan DP knapsack mustahil dan MITM menjadi jawabannya
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: bangkitkan pasangan (berat, nilai) untuk tiap subset paruh

    // TODO: urutkan berdasarkan berat, LALU langkah tambahan itu

    // TODO: binary search untuk tiap subset paruh lain

    return 0;
}
