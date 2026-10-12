/*
============================================================
🏋️ Exercise 1: Antrean Kasir
============================================================
Day: 71 | Difficulty: Easy
Topic: Exchange argument dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pelanggan di sebuah kasir. Pelanggan ke-i membutuhkan waktu layanan
t[i] detik. Hanya satu pelanggan yang bisa dilayani pada satu waktu, dan
sekali dimulai layanan tidak bisa dihentikan.
Waktu selesai seorang pelanggan adalah saat ia selesai dilayani, dihitung
dari detik nol.
Susun urutan pelayanan sehingga JUMLAH waktu selesai seluruh pelanggan
menjadi SEKECIL MUNGKIN, lalu cetak jumlah itu.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan t[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah waktu selesai minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= t[i] <= 10^9

📎 SAMPLE INPUT 1:
3
3 1 2

📎 SAMPLE OUTPUT 1:
10

📎 SAMPLE INPUT 2:
1
5

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Mulailah dari kasus terkecil yang bermakna: hanya DUA pelanggan
         dengan waktu a dan b. Hitung jumlah waktu selesai untuk kedua
         urutan yang mungkin, lalu bandingkan. Mana yang lebih kecil, dan
         syarat apa yang membuatnya begitu?
         Setelah kamu tahu jawabannya untuk dua pelanggan, pikirkan apakah
         aturan itu bisa diperluas: kalau sebuah urutan memuat dua pelanggan
         BERDAMPINGAN yang melanggar aturan tadi, apa yang terjadi kalau
         kamu menukar keduanya? Apakah pelanggan lain terpengaruh?
         Peringatan: 2*10^5 pelanggan dengan waktu 10^9 — perhatikan tipe
         data untuk jumlahnya.

🎯 Learning Goals:
- [ ] Menemukan kriteria greedy lewat perbandingan dua elemen
- [ ] Menyadari bahwa menukar pasangan berdampingan tidak memengaruhi yang lain
- [ ] Refleks memakai long long untuk akumulasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: tentukan urutan yang benar

    // TODO: sapu sekali sambil mengakumulasi waktu berjalan dan totalnya

    return 0;
}
