/*
============================================================
🏋️ Exercise 1: Bangun Tabel Pi
============================================================
Day: 213 | Difficulty: Easy
Topic: Failure function
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S. Bangun failure function (tabel pi) dari string
tersebut, lalu cetak seluruh isinya.

Definisi: pi[i] adalah panjang awalan TERPANJANG dari potongan S[0..i] yang
sekaligus menjadi akhiran dari potongan itu, tetapi bukan seluruh potongan
itu sendiri.

Contoh untuk "ababc": pi = 0 0 1 2 0. Pada i = 3, potongan "abab" punya
awalan "ab" yang juga menjadi akhirannya, sehingga pi[3] = 2.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris berisi |S| bilangan: pi[0] sampai pi[|S|-1], dipisah spasi.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
ababc

📎 SAMPLE OUTPUT 1:
0 0 1 2 0

📎 SAMPLE INPUT 2:
aabaaab

📎 SAMPLE OUTPUT 2:
0 1 0 1 2 2 3

📎 SAMPLE INPUT 3:
aaaa

📎 SAMPLE OUTPUT 3:
0 1 2 3

💡 HINT:
- pi[0] SELALU 0, karena tidak ada awalan yang lebih pendek dari satu huruf.
- Untuk posisi i, mulai dari j = pi[i-1] (kecocokan dari langkah sebelumnya).
- Selama huruf tidak cocok, mundur ke border yang lebih pendek: j = pi[j-1].
- Kalau akhirnya cocok, tambah j satu.
- Perhatikan: while bersarang TIDAK membuatnya O(n^2), karena j naik paling
  banyak 1 tiap iterasi sehingga total penurunannya juga terbatas.

🎯 Learning Goals:
- [ ] Memahami arti pi dengan tepat
- [ ] Menulis loop pembangun pi tanpa salah
- [ ] Menyadari kenapa kompleksitasnya O(n)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // TODO: Baca S

  // TODO: Bangun pi. Ingat pola: j = pi[i-1], while mundur, cek cocok

  // TODO: Cetak seluruh isi pi dipisah spasi

  return 0;
}
