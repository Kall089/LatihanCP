/*
============================================================
🏋️ Exercise 6: K Terbesar dari Aliran Data
============================================================
Day: 45 | Difficulty: Hard (Contest-level)
Topic: Heap ukuran K vs quickselect
Time Limit: 2 detik | Memory Limit: 16 MB

📋 PROBLEM STATEMENT:
Sebuah sensor mengirim N bilangan satu per satu. Kamu harus melaporkan
K bilangan TERBESAR di antara seluruh data yang dikirim, dicetak dalam
urutan MENURUN.
Perhatikan BATAS MEMORI pada soal ini: hanya 16 MB. Dengan N mencapai
10^7, menyimpan seluruh data dalam array membutuhkan 40 MB dan akan MLE.
Kamu harus memproses data secara mengalir, tanpa menyimpan semuanya.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi K bilangan terbesar, urut MENURUN

📏 CONSTRAINTS:
- 1 <= K <= 1000
- K <= N <= 10^7
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
6 3
3 1 5 2 9 4

📎 SAMPLE OUTPUT 1:
9 5 4

💡 HINT: nth_element membutuhkan SELURUH array berada di memori, jadi ia
         tidak bisa dipakai di sini. Kamu butuh struktur yang menyimpan
         paling banyak K elemen pada satu waktu.
         Pikirkan: kalau kamu sudah punya K kandidat terbaik dan datang
         satu bilangan baru, elemen mana yang harus dibuang?
         Struktur apa yang memberi elemen itu dengan cepat? Perhatikan
         bahwa yang harus dibuang adalah yang TERKECIL di antara kandidat,
         padahal yang kita cari adalah yang terbesar.

🎯 Learning Goals:
- [ ] Memahami kapan heap mengalahkan quickselect (batas memori, stream)
- [ ] Menyadari bahwa mencari "terbesar" memakai MIN-heap
- [ ] Menghitung pemakaian memori sebelum memilih pendekatan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca satu per satu, JANGAN simpan semuanya

    // TODO: jaga heap berukuran paling banyak K

    // TODO: keluarkan dan cetak menurun

    return 0;
}
