/*
============================================================
🏋️ Exercise 3: Quickselect Manual
============================================================
Day: 45 | Difficulty: Medium
Topic: Quickselect dengan pivot acak
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan Q pertanyaan. Setiap pertanyaan
berisi sebuah bilangan k, dan kamu harus menjawab elemen TERKECIL ke-k
(1-based) di dalam array.
Untuk latihan ini, kamu TIDAK BOLEH memakai sort maupun nth_element dari
pustaka — tulis sendiri prosedur pemilihannya.
Array tidak berubah di antara pertanyaan (setiap pertanyaan melihat array
yang sama).

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: masing-masing satu bilangan k

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= Q <= 10
- 1 <= k <= N

📎 SAMPLE INPUT 1:
6 3
5 2 8 1 9 3
1
3
6

📎 SAMPLE OUTPUT 1:
1
3
9

💡 HINT: Setelah satu langkah partisi, kamu tahu PERSIS di indeks berapa
         pivot berakhir. Bandingkan indeks itu dengan k: kalau sama, selesai;
         kalau tidak, kamu hanya perlu menelusuri SATU sisi saja.
         Karena hanya satu sisi, kamu tidak butuh rekursi — loop while cukup.
         Satu hal yang WAJIB: pilih pivot secara ACAK. Kalau tidak, array
         yang sudah terurut akan membuat programmu O(N^2).
         Perhatikan juga bahwa array berubah setelah pemilihan, sehingga
         pertanyaan berikutnya perlu salinan yang segar.

🎯 Learning Goals:
- [ ] Menulis quickselect tanpa rekursi
- [ ] Memahami kenapa rata-ratanya O(n): n + n/2 + n/4 + ... = 2n
- [ ] Menyadari pentingnya pivot acak
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: fungsi partisi

// TODO: fungsi quickSelect tanpa rekursi

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap query, pakai SALINAN array

    return 0;
}
