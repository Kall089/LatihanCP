/*
============================================================
🏋️ Exercise 4: Query Rentang Nilai
============================================================
Day: 40 | Difficulty: Medium
Topic: Frekuensi + prefix sum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat antara 1 dan 10^6, dan Q
pertanyaan. Setiap pertanyaan berisi sepasang bilangan L dan R, dan kamu
harus menjawab BERAPA BANYAK elemen array yang nilainya berada di antara
L dan R (inklusif).
Perhatikan bahwa yang ditanyakan adalah rentang NILAI, bukan rentang
posisi. Setiap pertanyaan harus dijawab O(1) setelah preprocessing.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: L dan R

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 5 * 10^5
- 1 <= a[i] <= 10^6
- 1 <= L <= R <= 10^6

📎 SAMPLE INPUT 1:
5 3
3 1 4 1 5
1 2
2 4
1 10

📎 SAMPLE OUTPUT 1:
2
2
5

💡 HINT: Bangun array frekuensi, lalu ubah ia menjadi prefix sum.
         Setelah diubah, isi slot ke-v punya arti yang berbeda dari
         sebelumnya — pikirkan artinya apa, dan bagaimana dua slot bisa
         dikurangkan untuk menjawab rentang.

🎯 Learning Goals:
- [ ] Menggabungkan dua teknik: frekuensi (hari ini) dan prefix (Day 29)
- [ ] Memahami perubahan makna slot setelah menjadi prefix
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: array global

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung frekuensi

    // TODO: ubah jadi prefix sum atas NILAI

    // TODO: jawab tiap query dengan satu pengurangan

    return 0;
}
