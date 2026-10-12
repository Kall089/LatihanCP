/*
============================================================
🏋️ Exercise 3: Playlist Tanpa Pengulangan
============================================================
Day: 34 | Difficulty: Medium
Topic: Window + posisi kemunculan terakhir
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah playlist berisi N lagu, dan lagu ke-i punya ID sebesar a[i].
ID yang sama boleh muncul beberapa kali di playlist.
Kamu ingin mendengarkan rangkaian lagu BERURUTAN yang selama itu TIDAK ADA
lagu yang terulang. Cari rangkaian terpanjang yang memenuhi syarat ini dan
cetak jumlah lagunya.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: panjang rangkaian terpanjang

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
8
1 2 1 3 2 7 4 2

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
4
5 5 5 5

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Simpan posisi kemunculan TERAKHIR setiap ID. Saat menemukan ID yang
         pernah muncul, lompatkan ujung kiri ke posisi setelahnya —
         TETAPI hanya kalau kemunculan itu masih berada DI DALAM window.
         Kalau syarat itu dilewatkan, ujung kiri bisa MUNDUR dan jawabanmu
         akan salah pada input seperti sampel 1.

🎯 Learning Goals:
- [ ] Memahami kenapa syarat "masih di dalam window" wajib
- [ ] Menyadari bahwa l yang mundur merusak jaminan O(n)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: map dari nilai ke indeks kemunculan terakhir

    // TODO: kalau lastSeen[a[r]] >= l, majukan l

    // TODO: perbarui lastSeen dan best

    return 0;
}
