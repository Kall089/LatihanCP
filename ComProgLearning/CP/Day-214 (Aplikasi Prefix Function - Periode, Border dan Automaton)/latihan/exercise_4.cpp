/*
============================================================
🏋️ Exercise 4: Pencocokan Pola pada Stream
============================================================
Day: 214 | Difficulty: Medium
Topic: KMP Automaton
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah mesin sensor mengirim karakter satu per satu. Kamu tidak boleh
menyimpan seluruh aliran karakter dan tidak boleh mundur ke karakter
sebelumnya. Diberikan pola P, kamu harus melaporkan setiap kali P baru
saja selesai muncul di aliran tersebut.
Untuk keperluan pengujian, aliran diberikan sebagai satu string T, tetapi
solusimu harus memproses T secara berurutan dengan memori O(|P| * 26)
dan waktu O(1) worst-case per karakter — artinya TIDAK BOLEH ada loop
while di dalam pemrosesan karakter.
Cetak semua posisi AKHIR (1-based) tempat pola selesai muncul.

📥 INPUT FORMAT:
- Baris pertama: string T (aliran)
- Baris kedua: string P (pola)

📤 OUTPUT FORMAT:
- Baris pertama: banyaknya kemunculan C
- Baris kedua: C posisi akhir, dipisah spasi (kosong jika C = 0)

📏 CONSTRAINTS:
- 1 <= |P| <= 10^5
- 1 <= |T| <= 10^6
- Huruf kecil semua

📎 SAMPLE INPUT 1:
ababa
aba

📎 SAMPLE OUTPUT 1:
2
3 5

📎 SAMPLE INPUT 2:
aaaa
aa

📎 SAMPLE OUTPUT 2:
3
2 3 4

💡 HINT: Bangun tabel transisi aut[state][c] dari pola + '#'. Setelah tabel
         jadi, pemrosesan tiap karakter hanya satu lookup array.

🎯 Learning Goals:
- [ ] Membangun automaton dan mengerti kenapa aut[pi[i-1]][c] boleh dipinjam
- [ ] Memahami perbedaan O(1) amortisasi vs O(1) sejati
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

    // TODO: bangun automaton dari p + '#'
    //       aut[i][c] = (i > 0 && 'a'+c != pola[i]) ? aut[pi[i-1]][c]
    //                                               : i + ('a'+c == pola[i])

    // TODO: jalankan state melalui t, catat saat state == |p|

    // TODO: cetak jumlah lalu posisinya

    return 0;
}
