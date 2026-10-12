/*
============================================================
🏋️ Exercise 3: Rentang Bersarang
============================================================
Day: 76 | Difficulty: Medium
Topic: Dominasi pada interval
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N rentang [l[i], r[i]]. Rentang i dikatakan TERMUAT di dalam
rentang j (dengan i berbeda dari j) kalau l[j] <= l[i] dan r[i] <= r[j].
Untuk setiap rentang, tentukan apakah ia termuat di dalam rentang lain, dan
apakah ia memuat rentang lain.
Cetak dua baris berisi 0 atau 1.
Perhatikan bahwa dua rentang yang identik saling memuat satu sama lain.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: l[i] dan r[i]

📤 OUTPUT FORMAT:
- Baris pertama: N bilangan; yang ke-i bernilai 1 kalau rentang i MEMUAT
  rentang lain
- Baris kedua: N bilangan; yang ke-i bernilai 1 kalau rentang i TERMUAT di
  dalam rentang lain

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= l[i] <= r[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 6
2 4
4 8
3 6

📎 SAMPLE OUTPUT 1:
1 0 0 0
0 1 0 1

📎 SAMPLE INPUT 2:
2
5 5
5 5

📎 SAMPLE OUTPUT 2:
1 1
1 1

💡 HINT: Ini soal dominasi Exercise 2 dengan satu perbedaan penting: arah
         perbandingan pada kedua koordinat TIDAK sama. Rentang j memuat
         rentang i kalau l[j] lebih KECIL dan r[j] lebih BESAR.
         Trik yang lazim: negasikan salah satu koordinat sehingga kedua
         arahnya seragam, lalu soalnya kembali menjadi dominasi biasa.
         Untuk "memuat": urutkan l menaik, dan saat l seri urutkan r
         MENURUN. Lalu sapu sambil melacak r maksimum yang sudah terlihat.
         Untuk "termuat": lakukan hal serupa dari arah lain. Pikirkan
         apakah kamu perlu mengurutkan ulang atau cukup menyapu balik.
         Sampel 2 menguji kasus rentang identik. Perhatikan bahwa keduanya
         saling memuat, sehingga kedua baris keluarannya berisi 1 semua.
         Ini persis kasus yang membedakan tie-break benar dan salah.
         Jangan lupa: r seri juga bisa terjadi. Rancang generator dengan
         koordinat 1 sampai 4 saja.

🎯 Learning Goals:
- [ ] Menyeragamkan arah perbandingan lewat negasi
- [ ] Menangani kasus rentang identik dengan benar
- [ ] Melakukan dua sapuan berlawanan arah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan dengan tie-break yang tepat untuk "memuat"

    // TODO: sapu; lalu ulangi untuk "termuat"

    return 0;
}
