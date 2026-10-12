/*
============================================================
🏋️ Exercise 2: Cari Semua Posisi Pola
============================================================
Day: 213 | Difficulty: Easy-Medium
Topic: KMP matching
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan teks T dan pola P. Cetak semua posisi awal tempat P muncul di
dalam T. Posisi dihitung mulai dari 1. Kemunculan yang saling tumpang tindih
tetap dihitung terpisah.
Jika pola tidak muncul sama sekali, cetak -1.

Contoh: pada teks "ababa", pola "aba" muncul di posisi 1 dan 3 — keduanya
berbagi huruf 'a' di tengah, dan keduanya tetap dihitung.

📥 INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

📤 OUTPUT FORMAT:
- Satu baris berisi posisi-posisi kemunculan dipisah spasi, atau -1.

📏 CONSTRAINTS:
- 1 <= |P| <= |T| <= 10^6
- T dan P hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
ababa
aba

📎 SAMPLE OUTPUT 1:
1 3

📎 SAMPLE INPUT 2:
aaaa
aa

📎 SAMPLE OUTPUT 2:
1 2 3

📎 SAMPLE INPUT 3:
abcde
xyz

📎 SAMPLE OUTPUT 3:
-1

💡 HINT:
- Bangun pi dari POLA saja, bukan dari teks.
- Telusuri teks dengan indeks i yang TIDAK PERNAH mundur.
- Saat huruf tidak cocok, yang mundur hanya j: j = pi[j-1].
- Setelah pola lengkap ditemukan, JANGAN set j = 0. Set j = pi[j-1]
  supaya kemunculan tumpang tindih ikut terdeteksi.

🎯 Learning Goals:
- [ ] Menerapkan KMP matching
- [ ] Menjaga indeks teks agar tidak mundur
- [ ] Menangani kemunculan tumpang tindih
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca T dan P, bangun pi dari P

    // TODO: Telusuri T dengan j sebagai panjang kecocokan

    // TODO: Saat j == |P|, catat posisi lalu j = pi[j-1]

    return 0;
}
