/*
============================================================
🏋️ Exercise 5: Menutupi dengan Panjang Tetap
============================================================
Day: 73 | Difficulty: Hard
Topic: Covering titik dengan interval bergerak
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N rumah pada sebuah jalan lurus; rumah ke-i berada di posisi x[i].
Kamu memasang menara pemancar; setiap menara yang dipasang di posisi p
melayani semua rumah pada rentang [p, p + K] (posisi p boleh bilangan real
mana pun, dan K adalah jangkauan yang sudah tetap).
Cari JUMLAH MENARA MINIMUM agar setiap rumah terlayani.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N posisi rumah (boleh tidak terurut, boleh ada yang sama)

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah menara minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= K <= 10^9
- 0 <= x[i] <= 10^9

📎 SAMPLE INPUT 1:
5 2
1 2 3 4 5

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3 0
7 7 7

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
4 1
1 5 9 13

📎 SAMPLE OUTPUT 3:
4

💡 HINT: Perhatikan bedanya dengan Exercise 3. Di sana intervalnya SUDAH
         DITENTUKAN dan kamu memilih sebagian. Di sini kamu BEBAS menaruh
         intervalnya di mana pun, tetapi panjangnya tetap.
         Urutkan posisi rumah lebih dulu. Sekarang pikirkan rumah paling
         kiri yang belum terlayani. Menara harus dipasang di suatu tempat
         yang melayaninya. Di antara semua posisi yang mungkin, mana yang
         paling menguntungkan?
         Tuliskan exchange argument-nya: kalau sebuah solusi optimal
         memasang menara lebih ke kiri dari pilihan itu, apakah menggesernya
         ke kanan pernah merugikan?
         Sampel 2 menguji K bernilai nol dan rumah yang berimpit.
         Waspadai overflow: x sampai 10^9 dan K sampai 10^9.

🎯 Learning Goals:
- [ ] Membedakan "pilih dari interval yang ada" dan "tempatkan interval bebas"
- [ ] Menurunkan posisi penempatan optimal lewat exchange argument
- [ ] Menangani K = 0 dan titik yang berimpit
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan posisi rumah

    // TODO: untuk rumah terkiri yang belum terlayani, tempatkan menara
    //       pada posisi yang sudah kamu buktikan optimal

    return 0;
}
