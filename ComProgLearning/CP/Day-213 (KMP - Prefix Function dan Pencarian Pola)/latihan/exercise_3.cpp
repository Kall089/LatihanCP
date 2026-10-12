/*
============================================================
🏋️ Exercise 3: Border Terpanjang
============================================================
Day: 213 | Difficulty: Medium
Topic: pi[n-1] sebagai border
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah "border" dari string S adalah potongan yang menjadi awalan sekaligus
akhiran dari S, tetapi bukan seluruh S itu sendiri.

Diberikan sebuah string S, cetak panjang border TERPANJANG-nya.
Jika tidak ada border sama sekali, cetak 0.

Contoh: "abcababcab" punya border "abcab" sepanjang 5, karena potongan itu
adalah lima huruf pertama sekaligus lima huruf terakhir.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu bilangan: panjang border terpanjang, atau 0 jika tidak ada.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
abcababcab

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
abcd

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
aaaa

📎 SAMPLE OUTPUT 3:
3

💡 HINT:
- Ini soal satu baris kalau kamu sudah punya tabel pi.
- Menurut definisinya, pi[n-1] TEPAT berarti panjang border terpanjang.
- Perhatikan sample 3: "aaaa" jawabannya 3, bukan 4. Border tidak boleh
  seluruh string (harus proper prefix).
- Rumus pi sudah otomatis menjamin hal itu, jadi tidak perlu penanganan khusus.

🎯 Learning Goals:
- [ ] Menghubungkan pi dengan konsep border
- [ ] Memahami arti proper prefix
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun pi

    // TODO: Cetak pi[n-1]

    return 0;
}
