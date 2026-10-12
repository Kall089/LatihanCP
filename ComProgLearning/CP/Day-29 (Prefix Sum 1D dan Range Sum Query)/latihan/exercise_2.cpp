/*
============================================================
🏋️ Exercise 2: Hitung Bilangan Genap dalam Rentang
============================================================
Day: 29 | Difficulty: Easy
Topic: Prefix count
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan Q pertanyaan. Setiap pertanyaan
berupa rentang L sampai R (1-based, inklusif). Untuk setiap pertanyaan,
jawab BERAPA BANYAK bilangan genap yang ada di dalam rentang tersebut.
Perhatikan bahwa yang diminta adalah BANYAKNYA, bukan jumlahnya. Ini melatih
pola pikir yang lebih sering berguna daripada prefix sum biasa: ubah dulu
pertanyaannya menjadi array berisi 0 dan 1.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan a[1..N]
- Q baris berikutnya: L dan R

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6 3
1 2 3 4 5 6
1 6
2 3
5 5

📎 SAMPLE OUTPUT 1:
3
1
0

📎 SAMPLE INPUT 2:
4 1
-2 -4 1 3
1 4

📎 SAMPLE OUTPUT 2:
2

💡 HINT: Buat array b di mana b[i] = 1 kalau a[i] genap dan 0 kalau ganjil,
         lalu prefix sum pada b. Hati-hati: di C++, (-3) % 2 bernilai -1,
         bukan 1. Cek kegenapan dengan cara yang aman untuk bilangan negatif.

🎯 Learning Goals:
- [ ] Mengubah predikat menjadi array 0/1
- [ ] Sadar bahwa operator % pada bilangan negatif berperilaku beda
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca input

    // TODO: cnt[i+1] = cnt[i] + (a[i] genap ? 1 : 0)

    // TODO: jawab tiap query

    return 0;
}
