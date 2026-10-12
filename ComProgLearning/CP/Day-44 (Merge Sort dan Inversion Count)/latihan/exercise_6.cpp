/*
============================================================
🏋️ Exercise 6: Gabungkan K Barisan
============================================================
Day: 44 | Difficulty: Hard (Contest-level)
Topic: Merge k array dengan heap
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan K barisan bilangan yang MASING-MASING sudah terurut menaik.
Gabungkan seluruhnya menjadi satu barisan terurut menaik.
Total seluruh elemen dari semua barisan adalah N.
Menggabungkan barisan satu per satu (barisan 1 dengan 2, hasilnya dengan 3,
dan seterusnya) membutuhkan O(N*K) dan akan TLE untuk batas soal ini.
Kamu perlu pendekatan yang lebih baik.

📥 INPUT FORMAT:
- Baris pertama: K
- K baris berikutnya: masing-masing dimulai dengan L (panjang barisan),
  diikuti L bilangan yang sudah terurut

📤 OUTPUT FORMAT:
- Satu baris berisi seluruh N bilangan terurut menaik

📏 CONSTRAINTS:
- 1 <= K <= 10^4
- Total N <= 10^5
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
3
3 1 4 7
2 2 5
3 3 6 9

📎 SAMPLE OUTPUT 1:
1 2 3 4 5 6 7 9

📎 SAMPLE INPUT 2:
2
1 5
0

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Pada setiap langkah, elemen berikutnya yang harus dikeluarkan
         pasti berada di antara elemen TERDEPAN dari K barisan. Kamu butuh
         struktur yang bisa memberi minimum dari K kandidat dengan cepat,
         dan memperbaruinya setelah satu kandidat diambil.
         Berapa kompleksitas total kalau setiap pengambilan berbiaya
         log K?
         Perhatikan sampel 2: sebuah barisan boleh KOSONG.

🎯 Learning Goals:
- [ ] Memakai priority queue untuk merge k arah
- [ ] Membandingkan O(N log K) dengan O(NK)
- [ ] Menangani barisan kosong
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: masukkan elemen pertama tiap barisan yang TIDAK KOSONG ke heap

    // TODO: ambil minimum, lalu masukkan penerusnya dari barisan yang sama

    return 0;
}
