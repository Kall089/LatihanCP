/*
============================================================
🏋️ Exercise 2: Segmen Terpendek yang Cukup
============================================================
Day: 34 | Difficulty: Easy
Topic: Window terpendek
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat POSITIF dan sebuah target S.
Cari subarray (potongan berurutan) TERPENDEK yang jumlah elemennya
setidaknya S. Cetak panjangnya. Jika tidak ada subarray yang jumlahnya
mencapai S, cetak 0.

📥 INPUT FORMAT:
- Baris pertama: N dan S
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: panjang terpendek, atau 0

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= S <= 10^14
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
6 7
2 3 1 2 4 3

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3 100
1 2 3

📎 SAMPLE OUTPUT 2:
0

💡 HINT: Kerangkanya nyaris sama dengan Exercise 1, tetapi baris pencatatan
         jawabannya pindah KE DALAM while. Pikirkan baik-baik kenapa.
         Perhatikan juga: S bisa mencapai 10^14.

🎯 Learning Goals:
- [ ] Memahami perbedaan letak baris "catat" antara terpanjang dan terpendek
- [ ] Menangani kasus "tidak ada jawaban" tanpa mencetak INT_MAX
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca input

    // TODO: for r: sum += a[r];
    //       while (sum >= S) { best = min(best, r-l+1); sum -= a[l]; l++; }

    // TODO: cetak 0 kalau best tidak pernah berubah

    return 0;
}
