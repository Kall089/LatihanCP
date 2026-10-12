/*
============================================================
🏋️ Exercise 4: Kapan Dua Kota Terhubung
============================================================
Day: 53 | Difficulty: Hard
Topic: Parallel binary search + DSU
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kota yang mula-mula tidak terhubung sama sekali.
Selama M hari, setiap hari dibangun tepat satu jalan yang menghubungkan
dua kota (jalan bersifat dua arah, dan boleh saja menghubungkan kota yang
sudah terhubung sebelumnya).
Ada Q pertanyaan. Pertanyaan ke-i berisi dua kota u dan v, dan kamu harus
menjawab pada HARI KEBERAPA kedua kota itu pertama kali terhubung (langsung
maupun melalui kota lain). Cetak -1 kalau sampai hari terakhir mereka tetap
tidak terhubung.

📥 INPUT FORMAT:
- Baris pertama: N, M, dan Q
- M baris berikutnya: dua kota yang dihubungkan pada hari itu
- Q baris berikutnya: u dan v

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, M, Q <= 2 * 10^5

📎 SAMPLE INPUT 1:
4 3 3
1 2
3 4
2 3
1 2
1 4
1 3

📎 SAMPLE OUTPUT 1:
1
3
3

💡 HINT: Keterhubungan bersifat MONOTON: sekali dua kota terhubung, mereka
         terhubung selamanya (jalan tidak pernah dihancurkan). Jadi setiap
         pertanyaan bisa di-binary-search.
         Struktur data yang tepat untuk keterhubungan adalah Disjoint Set
         Union. Perhatikan bahwa kamu TIDAK butuh DSU dengan rollback di
         sini — karena setiap putaran memulai dari nol, DSU biasa sudah
         cukup. Cukup buat DSU baru (atau reset arraynya) di awal setiap
         putaran.
         Menjawab satu pertanyaan hanya butuh dua pencarian akar, jadi
         biayanya sangat kecil.

🎯 Learning Goals:
- [ ] Menggabungkan parallel binary search dengan DSU
- [ ] Menyadari kenapa rollback tidak diperlukan di sini
- [ ] Menerapkan pola pada masalah graf, bukan hanya array
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DSU dengan path compression dan union by size

    // TODO: reset DSU di AWAL setiap putaran

    // TODO: menjawab query = cek apakah find(u) == find(v)

    return 0;
}
