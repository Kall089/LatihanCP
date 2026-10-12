/*
============================================================
🏋️ Exercise 1: Range Sum Query Statis
============================================================
Day: 29 | Difficulty: Easy
Topic: Prefix sum dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan Q pertanyaan. Setiap pertanyaan
berisi sepasang indeks L dan R (1-based, inklusif), dan kamu harus menjawab
berapa jumlah seluruh elemen dari posisi L sampai posisi R.
Tidak ada perubahan nilai array di antara pertanyaan.
Menjawab setiap pertanyaan dengan loop akan menghasilkan 10^10 operasi dan
pasti TLE. Kamu perlu preprocessing agar setiap pertanyaan dijawab O(1).

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan a[1..N]
- Q baris berikutnya: masing-masing L dan R

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= a[i] <= 10^9
- 1 <= L <= R <= N

📎 SAMPLE INPUT 1:
5 3
3 1 4 1 5
1 5
2 4
3 3

📎 SAMPLE OUTPUT 1:
14
6
4

📎 SAMPLE INPUT 2:
3 2
-1 -2 -3
1 3
2 2

📎 SAMPLE OUTPUT 2:
-6
-2

💡 HINT: Buat pre berukuran N+1 dengan pre[0] = 0. Dengan konvensi itu,
         kamu tidak perlu percabangan khusus untuk L = 1.
         Perhatikan juga: 2*10^5 dikali 10^9 tidak muat di int.

🎯 Learning Goals:
- [ ] Membangun prefix sum dengan konvensi n+1
- [ ] Konversi 1-based (input) ke 0-based (array)
- [ ] Refleks memakai long long
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca n dan q

    // TODO: bangun pre berukuran n+1, pre[0] = 0

    // TODO: untuk setiap query, konversi L dan R lalu cetak pre[?] - pre[?]

    return 0;
}
