/*
============================================================
🏋️ Exercise 4: Urutkan Tiga Warna
============================================================
Day: 45 | Difficulty: Medium
Topic: Partisi tiga arah (Dutch national flag)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan yang setiap elemennya bernilai 0, 1,
atau 2 (mewakili tiga warna). Susun ulang array itu sehingga seluruh 0
berada di depan, diikuti seluruh 1, lalu seluruh 2.
Kamu harus melakukannya IN-PLACE, dalam SATU KALI sapuan (setiap elemen
diperiksa paling banyak sekali), dan tanpa memakai array frekuensi.
Batasan "satu kali sapuan" ini yang membuat soal menarik — dengan array
frekuensi soal ini terlalu mudah.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan bernilai 0, 1, atau 2

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan terurut

📏 CONSTRAINTS:
- 1 <= N <= 10^6
- a[i] ada di {0, 1, 2}

📎 SAMPLE INPUT 1:
6
2 0 2 1 1 0

📎 SAMPLE OUTPUT 1:
0 0 1 1 2 2

📎 SAMPLE INPUT 2:
3
2 2 2

📎 SAMPLE OUTPUT 2:
2 2 2

💡 HINT: Jaga TIGA daerah sekaligus: yang sudah pasti 0 (di kiri), yang
         sudah pasti 2 (di kanan), dan yang belum diperiksa (di tengah).
         Ada satu detail yang sangat mudah salah: ketika kamu menukar
         sebuah elemen dengan elemen dari daerah KANAN, apakah penunjuk
         penjelajahmu boleh maju? Pikirkan baik-baik — elemen yang baru
         datang itu berasal dari mana?

🎯 Learning Goals:
- [ ] Menjaga tiga invariant sekaligus
- [ ] Memahami kenapa penunjuk tidak boleh maju setelah tukar dengan kanan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tiga penunjuk: lt (batas kiri), i (penjelajah), gt (batas kanan)

    // TODO: hati-hati kapan i boleh maju

    return 0;
}
