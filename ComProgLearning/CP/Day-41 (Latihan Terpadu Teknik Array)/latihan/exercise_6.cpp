/*
============================================================
🏋️ Exercise 6: Kepadatan Pengunjung Maksimum
============================================================
Day: 41 | Difficulty: Hard (Contest-level)
Topic: coordinate compression (Day 38) + difference array (Day 31) + sorting
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah museum mencatat N pengunjung. Pengunjung ke-i masuk pada detik L[i]
dan keluar pada detik R[i]; ia dianggap berada di dalam museum selama
interval [L[i], R[i]] termasuk kedua ujungnya.

Tentukan jumlah pengunjung terbanyak yang pernah berada di dalam museum pada
saat yang bersamaan.

Perhatikan batasan waktunya: sampai 10^9. Kamu tidak mungkin membuat array
sebesar itu. Tapi jumlah PERISTIWA-nya hanya 2N. Di situlah kompresi
koordinat masuk.

Hati-hati pada detail interval TERTUTUP: kalau pengunjung A keluar pada detik
5 dan pengunjung B masuk pada detik 5, keduanya dihitung berada di dalam
museum pada detik 5.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: L[i] dan R[i]

📤 OUTPUT FORMAT:
- Satu bilangan

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2·10^5
- 1 ≤ L[i] ≤ R[i] ≤ 10^9

📎 SAMPLE INPUT 1:
3
1 5
2 8
9 10

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
3
1 5
5 9
5 5

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
2
1 1000000000
500000000 500000000

📎 SAMPLE OUTPUT 3:
2

📎 SAMPLE INPUT 4:
4
1 2
3 4
5 6
7 8

📎 SAMPLE OUTPUT 4:
1

💡 HINT: Pendekatan paling bersih bukan kompresi eksplisit, melainkan
         SWEEP LINE: buat 2N peristiwa (+1 di L, -1 di R+1), urutkan
         berdasarkan waktu, lalu jalankan penjumlahan berjalan.
         Sample 2 ada untuk memastikan kamu memakai R+1, bukan R.

🎯 Learning Goals:
- [ ] Menangani nilai sampai 10^9 tanpa array sebesar itu
- [ ] Memahami hubungan antara sweep line dan difference array
- [ ] Menangani interval tertutup dengan benar (+1 di L, -1 di R+1)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan semua interval

    // TODO: Bangun daftar peristiwa: (L, +1) dan (R+1, -1)

    // TODO: Urutkan peristiwa berdasarkan waktu.
    // Hati-hati: pada waktu yang SAMA, semua +1 harus diproses sebelum -1?
    //            Kalau kamu memakai R+1, urutan itu tidak lagi penting.
    //            Pikirkan kenapa.

    // TODO: Jalankan penjumlahan berjalan, catat nilai tertingginya

    return 0;
}
