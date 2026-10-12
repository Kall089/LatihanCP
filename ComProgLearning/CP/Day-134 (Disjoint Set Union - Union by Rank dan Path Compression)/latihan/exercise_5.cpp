/*
============================================================
🏋️ Exercise 5: Biaya Menghubungkan Semua Kota
============================================================
Day: 134 | Difficulty: Hard
Topic: Kruskal (minimum spanning tree)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah negara punya N kota dan M kemungkinan jalan. Jalan ke-i
menghubungkan kota u dan v dengan biaya pembangunan w.
Pilih sekumpulan jalan yang akan dibangun sehingga SELURUH kota saling
terhubung (langsung maupun tidak langsung) dengan TOTAL BIAYA MINIMUM.
Cetak total biaya minimum itu. Jika mustahil menghubungkan seluruh kota
dengan jalan-jalan yang tersedia, cetak "IMPOSSIBLE".

📥 INPUT FORMAT:
- Baris pertama: N dan M
- M baris berikutnya: u, v, dan w

📤 OUTPUT FORMAT:
- Satu bilangan, atau "IMPOSSIBLE"

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= M <= 2 * 10^5
- 1 <= w <= 10^9

📎 SAMPLE INPUT 1:
4 5
1 2 1
2 3 2
1 3 3
3 4 4
1 4 5

📎 SAMPLE OUTPUT 1:
7

📎 SAMPLE INPUT 2:
3 1
1 2 5

📎 SAMPLE OUTPUT 2:
IMPOSSIBLE

💡 HINT: Strategi greedy yang benar di sini: pertimbangkan jalan dari yang
         TERMURAH, dan bangun sebuah jalan hanya kalau ia menghubungkan dua
         kelompok kota yang belum terhubung. Jalan yang kedua ujungnya sudah
         sekelompok akan membentuk siklus dan pasti tidak diperlukan.
         Operasi penggabunganmu sudah memberi tahu apakah sebuah jalan
         benar-benar menghubungkan dua kelompok — manfaatkan itu, jangan
         memanggil pencarian perwakilan dua kali.
         Untuk mendeteksi kasus IMPOSSIBLE, perhatikan berapa jalan yang
         DIPERLUKAN untuk menghubungkan N kota, dan bandingkan dengan
         berapa yang benar-benar terpakai.
         Ingat tipe data: 10^5 jalan dengan biaya 10^9.

🎯 Learning Goals:
- [ ] Menulis Kruskal dalam lima baris memakai DSU
- [ ] Mendeteksi graf tidak terhubung lewat hitungan sisi terpakai
- [ ] Memahami kenapa greedy termurah-dulu benar untuk MST
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca seluruh sisi, urutkan berdasarkan bobot

    // TODO: ambil sisi kalau unite berhasil, akumulasi biaya

    // TODO: cek apakah sisi yang terpakai cukup

    return 0;
}
