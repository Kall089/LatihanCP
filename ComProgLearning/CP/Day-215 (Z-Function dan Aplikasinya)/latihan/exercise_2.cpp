/*
============================================================
🏋️ Exercise 2: Cari Pola dengan Z
============================================================
Day: 215 | Difficulty: Easy
Topic: Trik pola + separator + teks
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan teks T dan pola P. Cari semua posisi awal (1-based) tempat P muncul
sebagai substring di dalam T. Kemunculan yang tumpang tindih tetap dihitung.
Selesaikan menggunakan Z-function, bukan KMP.
Jika P tidak pernah muncul, cetak 0 pada baris pertama dan baris kedua kosong.

📥 INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya kemunculan C
- Baris kedua: C posisi awal (1-based), dipisah spasi

📏 CONSTRAINTS:
- 1 <= |P| <= 10^6
- 1 <= |T| <= 10^6
- Huruf kecil semua

📎 SAMPLE INPUT 1:
ababa
aba

📎 SAMPLE OUTPUT 1:
2
1 3

📎 SAMPLE INPUT 2:
aaaa
aa

📎 SAMPLE OUTPUT 2:
3
1 2 3

📎 SAMPLE INPUT 3:
abc
xyz

📎 SAMPLE OUTPUT 3:
0


💡 HINT: Bangun g = P + separator + T lalu cari indeks dengan z[i] >= |P|.
         Pilih separator yang MUSTAHIL muncul di input — '\1' aman, '#' belum tentu.
         Jangan lupa mengonversi indeks di g kembali ke indeks di T.

🎯 Learning Goals:
- [ ] Memahami peran separator (kenapa tanpa itu hasilnya bisa palsu)
- [ ] Konversi indeks g -> indeks T
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t, p;
    cin >> t >> p;

    // TODO: bentuk g = p + '\1' + t

    // TODO: bangun z dari g

    // TODO: untuk i mulai dari |p|+1, cek z[i] >= |p|
    //       posisi di T = i - |p| - 1 (0-based) -> +1 untuk 1-based

    return 0;
}
