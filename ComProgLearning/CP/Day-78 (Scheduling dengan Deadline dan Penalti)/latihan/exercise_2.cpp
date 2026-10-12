/*
============================================================
🏋️ Exercise 2: Sesedikit Mungkin Terlambat
============================================================
Day: 78 | Difficulty: Easy
Topic: Moore-Hodgson
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan yang semuanya harus dikerjakan pada satu mesin, satu per
satu tanpa jeda, mulai dari waktu 0. Pekerjaan ke-i memerlukan t[i] satuan
waktu dan punya tenggat d[i].
Sebuah pekerjaan disebut TERLAMBAT kalau selesai setelah tenggatnya.
Susun urutan pengerjaan sehingga JUMLAH pekerjaan yang terlambat menjadi
sekecil mungkin, lalu cetak jumlah itu.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i] dan d[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah pekerjaan terlambat minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= t[i] <= 10^9
- 1 <= d[i] <= 10^18

📎 SAMPLE INPUT 1:
3
5 5
5 9
3 12

📎 SAMPLE OUTPUT 1:
1

📎 SAMPLE INPUT 2:
2
5 1
5 100

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Godaan terbesar: pakai jawaban Exercise 1 apa adanya, lalu hitung
         berapa yang terlambat. Uji itu pada sampel 1 — kamu akan mendapat
         jawaban yang lebih besar dari 1.
         Kenapa gagal? Karena Exercise 1 meminimalkan keterlambatan
         TERBESAR, bukan JUMLAH yang terlambat. Dua fungsi tujuan yang
         berbeda membutuhkan algoritma yang berbeda, meski keduanya
         diawali dengan pengurutan yang sama.
         Kerangka yang benar sudah kamu pelajari kemarin: ambil semua
         secara serakah, lalu batalkan saat melanggar.
         Pertanyaan kuncinya: pekerjaan yang "dibatalkan" itu tidak
         menghilang — ia tetap harus dikerjakan. Ke mana ia pergi, dan
         kenapa itu tidak memengaruhi jawabanmu?
         Pertanyaan kedua: saat membatalkan, pekerjaan mana yang kamu
         pilih, dan kenapa?
         Sampel 1 dirancang agar jawaban naif memberi hasil berbeda.
         Hitung dengan tangan untuk melihat perbedaannya.

🎯 Learning Goals:
- [ ] Membedakan "minimalkan maksimum" dan "minimalkan jumlah"
- [ ] Menerapkan kerangka regret pada penjadwalan
- [ ] Memahami bahwa pekerjaan yang dibuang tetap dikerjakan di belakang
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan; kerangka regret

    // TODO: tentukan apa yang dibatalkan saat melanggar

    return 0;
}
