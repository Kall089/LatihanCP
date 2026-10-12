/*
============================================================
🏋️ Exercise 6: Keranjang Buah
============================================================
Day: 42 | Difficulty: Hard
Topic: ❓ DIRAHASIAKAN — tebak sendiri sebelum menulis kode
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah deretan N pohon berjajar, pohon ke-i menghasilkan buah jenis a[i].
Seorang pemetik berjalan dari satu pohon ke pohon berikutnya tanpa boleh
melompat, dan ia hanya membawa K keranjang. Setiap keranjang hanya boleh
berisi SATU jenis buah.

Cari jumlah pohon terbanyak yang bisa ia lewati secara berurutan, dengan
syarat jenis buah berbeda yang ia kumpulkan tidak lebih dari K.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan, jenis buah tiap pohon

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 2·10^5
- 1 ≤ a[i] ≤ 10^9

📎 SAMPLE INPUT 1:
5 2
1 2 1 2 3

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
4 1
1 2 3 4

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
4 3
7 7 7 7

📎 SAMPLE OUTPUT 3:
4

📎 SAMPLE INPUT 4:
7 2
3 1 2 2 2 1 4

📎 SAMPLE OUTPUT 4:
5

💡 HINT: "Berurutan tanpa melompat" + "terpanjang yang memenuhi syarat" +
         syaratnya rusak kalau window melebar dan pulih kalau menyempit.
         Kombinasi itu cuma menunjuk satu teknik, ditambah satu struktur
         pembantu untuk melacak jumlah jenis.

🎯 Learning Goals:
- [ ] Menggabungkan window variabel dengan penghitungan frekuensi
- [ ] Menghapus kunci dari map saat hitungannya nol
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: TEKNIK SAYA: ______________________
    //       ALASAN     : ______________________

    // TODO: Implementasi

    return 0;
}
