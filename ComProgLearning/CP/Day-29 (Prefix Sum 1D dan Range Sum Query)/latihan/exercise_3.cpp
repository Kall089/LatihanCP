/*
============================================================
🏋️ Exercise 3: Subarray dengan Jumlah Tepat K
============================================================
Day: 29 | Difficulty: Medium
Topic: Prefix sum + map
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat (boleh negatif) dan sebuah bilangan K.
Hitung ADA BERAPA BANYAK subarray (potongan berurutan yang tidak kosong)
yang jumlah seluruh elemennya tepat sama dengan K.
Dua subarray dianggap berbeda jika posisi awal atau akhirnya berbeda,
meskipun isinya sama.
Perhatikan bahwa array boleh memuat bilangan negatif dan nol, sehingga
pendekatan sliding window TIDAK berlaku di sini.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya subarray

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9
- -10^14 <= K <= 10^14

📎 SAMPLE INPUT 1:
5 5
1 2 3 -1 2

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
4 0
0 0 0 0

📎 SAMPLE OUTPUT 2:
10

📎 SAMPLE INPUT 3:
3 7
1 2 3

📎 SAMPLE OUTPUT 3:
0

💡 HINT: jumlah a[l..r] = K berarti pre[r+1] - pre[l] = K, yaitu
         pre[l] = pre[r+1] - K. Jadi untuk setiap ujung kanan, kamu hanya
         perlu tahu BERAPA BANYAK prefix sebelumnya yang bernilai itu.
         Satu hal yang mudah terlupa: prefix kosong juga sebuah prefix.

🎯 Learning Goals:
- [ ] Mengubah kondisi subarray jadi kondisi pasangan prefix
- [ ] Menyadari peran freq[0] = 1
- [ ] Melihat kenapa sampel 2 jawabannya 10, bukan 4
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca n dan K

    // TODO: map freq, inisialisasi prefix kosong

    // TODO: jalan sekali, akumulasi cur, tambahkan freq[cur - K], lalu freq[cur]++

    return 0;
}
