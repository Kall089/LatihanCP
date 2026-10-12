/*
============================================================
🏋️ Exercise 1: Lower Bound dan Upper Bound Manual
============================================================
Day: 49 | Difficulty: Easy
Topic: Kerangka binary search
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat yang SUDAH TERURUT menaik, dan Q
pertanyaan. Setiap pertanyaan berisi satu bilangan x, dan kamu harus
mencetak dua bilangan:
- indeks PERTAMA yang nilainya lebih besar atau sama dengan x
- indeks PERTAMA yang nilainya lebih besar dari x
Keduanya 0-based. Jika tidak ada indeks yang memenuhi, cetak N.
Untuk latihan ini kamu TIDAK BOLEH memakai lower_bound maupun upper_bound
dari pustaka — tulis sendiri.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan terurut menaik
- Q baris berikutnya: masing-masing satu bilangan x

📤 OUTPUT FORMAT:
- Q baris, masing-masing dua bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= nilai, x <= 10^9

📎 SAMPLE INPUT 1:
6 3
1 3 3 3 5 7
3
4
9

📎 SAMPLE OUTPUT 1:
1 4
4 4
6 6

💡 HINT: Pakai satu kerangka untuk keduanya. Bayangkan sebuah predikat
         boolean atas indeks yang bernilai false lalu true (monoton), dan
         kamu mencari batas peralihannya.
         Untuk lower bound, predikatnya "a[i] >= x". Untuk upper bound,
         predikatnya berubah hanya satu karakter.
         Pakai konvensi setengah terbuka: mulai dengan hi = N, bukan N-1.

🎯 Learning Goals:
- [ ] Menulis kerangka first-true dengan benar
- [ ] Melihat bahwa kedua bound hanya berbeda satu karakter
- [ ] Terbiasa dengan konvensi [lo, hi)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: lo = 0, hi = n; while (lo < hi) { ... }

    // TODO: jangan lupa mid = lo + (hi - lo) / 2

    return 0;
}
