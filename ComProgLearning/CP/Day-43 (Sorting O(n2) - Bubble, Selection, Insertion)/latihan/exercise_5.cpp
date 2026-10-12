/*
============================================================
🏋️ Exercise 5: Data Hampir Terurut
============================================================
Day: 43 | Difficulty: Hard
Topic: Insertion sort pada data hampir terurut
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah sensor mengirim pembacaan yang seharusnya terurut menaik, tetapi
karena gangguan jaringan, setiap pembacaan bisa bergeser paling jauh K
posisi dari tempat seharusnya.
Diberikan array N pembacaan dengan jaminan tersebut, urutkan array itu.
Karena N bisa mencapai 10^5, algoritma O(N^2) murni akan TLE — tetapi
kamu boleh memanfaatkan jaminan bahwa datanya HAMPIR TERURUT.
Cetak array yang sudah terurut.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 0 <= K <= 100
- -10^9 <= a[i] <= 10^9
- Dijamin setiap elemen berjarak paling jauh K posisi dari tempatnya
  pada array yang sudah terurut

📎 SAMPLE INPUT 1:
5 2
3 1 2 5 4

📎 SAMPLE OUTPUT 1:
1 2 3 4 5

📎 SAMPLE INPUT 2:
4 0
1 2 3 4

📎 SAMPLE OUTPUT 2:
1 2 3 4

💡 HINT: Insertion sort tidak selalu O(N^2). Kerjanya sebanding dengan
         BERAPA JAUH tiap elemen harus digeser — dan di sini jaraknya
         dijamin paling jauh K.
         Berapa kompleksitasnya kalau dinyatakan dalam N dan K? Apakah
         itu cukup untuk batas soal ini?
         (Ada juga pendekatan lain memakai priority queue berukuran K+1
         yang berjalan dalam O(N log K) — coba pikirkan juga.)

🎯 Learning Goals:
- [ ] Memahami bahwa kompleksitas bergantung pada DATA, bukan hanya N
- [ ] Menghitung O(NK) dan memutuskan apakah lolos
- [ ] Mengetahui alternatif heap berukuran K+1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: insertion sort biasa -- tapi hitung dulu apakah O(NK) lolos

    return 0;
}
