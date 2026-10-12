/*
============================================================
🏋️ Exercise 6: Substring Bersama Terpanjang
============================================================
Day: 33 | Difficulty: Hard
Topic: Binary search + hash dua string
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan dua string A dan B. Cari panjang substring TERPANJANG yang muncul
di dalam A sekaligus di dalam B. Jika tidak ada satu pun huruf yang sama,
cetak 0.

Contoh: A = "kompetisi", B = "kompas" memiliki substring bersama "komp"
sepanjang 4.

📥 INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

📤 OUTPUT FORMAT:
- Satu bilangan: panjang substring bersama terpanjang.

📏 CONSTRAINTS:
- 1 <= |A|, |B| <= 5000
- Keduanya hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
kompetisi
kompas

📎 SAMPLE OUTPUT 1:
4

📎 SAMPLE INPUT 2:
abcdef
zzz

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
aaaa
aa

📎 SAMPLE OUTPUT 3:
2

💡 HINT:
- Sama seperti soal sebelumnya, jawabannya MONOTON, jadi binary search lagi.
- Untuk mengecek panjang L: kumpulkan hash semua substring sepanjang L dari A
  ke dalam sebuah set, lalu telusuri B dan cek apakah ada yang cocok.
- Jangan lupa kedua string butuh prefix hash-nya masing-masing.
- Batas atas binary search adalah panjang string yang lebih pendek.

🎯 Learning Goals:
- [ ] Menerapkan pola binary search + hash pada dua string
- [ ] Mengelola dua prefix hash sekaligus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca A dan B, bangun prefix hash untuk keduanya

    // TODO: Buat fungsi cek(len): kumpulkan hash panjang len dari A ke set,
    //       lalu cek apakah ada substring B yang cocok

    // TODO: Binary search panjang terbesar

    return 0;
}
