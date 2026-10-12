/*
============================================================
🏋️ Exercise 5: Substring Berulang Terpanjang
============================================================
Day: 33 | Difficulty: Hard
Topic: Binary search + hash
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S. Cari panjang substring TERPANJANG yang muncul
minimal dua kali di dalam S. Kedua kemunculan boleh saling tumpang tindih.
Jika tidak ada substring yang berulang, cetak 0.

Contoh: pada "banana", substring "ana" muncul dua kali (indeks 1 dan 3),
sehingga jawabannya 3.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu bilangan: panjang substring berulang terpanjang.

📏 CONSTRAINTS:
- 1 <= |S| <= 2 x 10^4
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
banana

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
abcd

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
aaaa

📎 SAMPLE OUTPUT 3:
3

💡 HINT:
- Sifat kuncinya MONOTON: kalau ada substring berulang sepanjang L,
  pasti ada juga yang sepanjang L-1 (potong saja satu huruf).
- Karena monoton, panjangnya bisa dicari dengan BINARY SEARCH.
- Untuk mengecek panjang tertentu: masukkan hash semua substring sepanjang L
  ke dalam set; kalau ada yang sudah pernah ada, berarti ada yang berulang.
- Perhatikan sample 3: pada "aaaa", substring "aaa" muncul di indeks 0 dan 1
  (tumpang tindih) sehingga jawabannya 3, bukan 2.

🎯 Learning Goals:
- [ ] Mengenali sifat monoton untuk binary search
- [ ] Menggabungkan binary search dengan hashing
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun prefix hash

    // TODO: Buat fungsi cek(len): apakah ada substring sepanjang len yang berulang?

    // TODO: Binary search nilai len terbesar yang masih memenuhi

    return 0;
}
