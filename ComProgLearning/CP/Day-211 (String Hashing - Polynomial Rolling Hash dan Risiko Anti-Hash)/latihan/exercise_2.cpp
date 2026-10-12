/*
============================================================
🏋️ Exercise 2: Rabin-Karp: Hitung Kemunculan Pola
============================================================
Day: 33 | Difficulty: Easy-Medium
Topic: Rabin-Karp
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah teks T dan sebuah pola P. Hitung berapa kali P muncul
di dalam T. Kemunculan yang saling tumpang tindih tetap dihitung terpisah.

Contoh: pada teks "ababa", pola "aba" muncul 2 kali (pada indeks 0 dan 2),
walaupun keduanya berbagi huruf 'a' di tengah.

📥 INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah kemunculan P di dalam T.

📏 CONSTRAINTS:
- 1 <= |P| <= |T| <= 2 x 10^5
- T dan P hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
ababa
aba

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
aaaa
aa

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
abcde
xyz

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Hitung hash pola sekali saja.
- Bangun prefix hash teks, lalu geser jendela sepanjang |P| dari kiri ke kanan.
- Bandingkan hash jendela dengan hash pola setelah bobotnya disamakan.
- Karena setelah cocok kita tetap maju satu langkah (bukan sepanjang pola),
  kemunculan tumpang tindih ikut terhitung.

🎯 Learning Goals:
- [ ] Menerapkan Rabin-Karp
- [ ] Menyamakan bobot hash jendela dengan hash pola
- [ ] Memahami kemunculan tumpang tindih
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca T dan P

    // TODO: Bangun prefix hash T, hitung hash P secara terpisah

    // TODO: Geser jendela sepanjang |P|, bandingkan hash-nya

    return 0;
}
