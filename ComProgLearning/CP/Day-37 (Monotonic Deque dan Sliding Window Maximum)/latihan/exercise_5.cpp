/*
============================================================
  Exercise 5: First Non-Repeating Character in Stream
============================================================
Diberikan stream karakter satu per satu. Setelah setiap karakter baru masuk,
cetak karakter pertama yang belum pernah muncul lebih dari satu kali.
Jika tidak ada, cetak '#'.

📏 CONSTRAINTS:
  - 1 ≤ |s| ≤ 10^5
  - s hanya berisi huruf kecil a-z

📎 SAMPLE INPUT:
  aabccd

📎 SAMPLE OUTPUT:
  a # b b b d

📎 SAMPLE INPUT 2:
  abcabc

📎 SAMPLE OUTPUT 2:
  a a a b c #

💡 HINT:
  Gunakan queue<char> untuk menjaga urutan karakter yang muncul.
  Gunakan freq[] untuk menghitung frekuensi.
  Setiap langkah: hapus front queue jika freq > 1 (sudah repeating).
  Front queue adalah first non-repeating character.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    queue<char> q;
    int freq[26] = {};

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        freq[c-'a']++;
        q.push(c);

        // TODO: hapus dari front semua karakter yang freq > 1
        // TODO: cetak q.front() atau '#' jika q kosong

        if (i < (int)s.size()-1) cout << ' ';
    }
    cout << "\n";
    return 0;
}
