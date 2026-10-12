/*
============================================================
🏋️ Exercise 6: Membagi Warisan Seadil Mungkin
============================================================
Day: 145 | Difficulty: Hard (Contest-level)
Topic: Subset sum sebagai masalah partisi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N benda warisan dengan nilai masing-masing, yang harus dibagi kepada
DUA ahli waris. Setiap benda harus diberikan utuh kepada salah satu ahli
waris (tidak boleh dipotong, dan tidak boleh disimpan).
Bagilah benda-benda itu sehingga SELISIH ABSOLUT antara total nilai yang
diterima kedua ahli waris menjadi SEKECIL MUNGKIN.
Cetak selisih minimum itu.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N nilai benda

📤 OUTPUT FORMAT:
- Satu bilangan: selisih absolut minimum

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= nilai <= 1000

📎 SAMPLE INPUT 1:
5
3 1 4 2 2

📎 SAMPLE OUTPUT 1:
0

📎 SAMPLE INPUT 2:
2
1 100

📎 SAMPLE OUTPUT 2:
99

📎 SAMPLE INPUT 3:
1
7

📎 SAMPLE OUTPUT 3:
7

💡 HINT: Misalkan total seluruh nilai adalah S, dan salah satu ahli waris
         menerima total x. Berapa yang diterima yang lain, dan berapa
         selisihnya dinyatakan dalam S dan x?
         Setelah kamu menuliskannya, akan jelas nilai x seperti apa yang
         kamu cari — dan itu mengubah soal ini menjadi soal yang sudah kamu
         kerjakan di Exercise 4.
         Perhatikan bahwa tidak semua nilai x bisa dicapai; kamu hanya boleh
         memilih di antara yang benar-benar bisa dibentuk dari subhimpunan.
         Sampel 3 menguji kasus di mana salah satu ahli waris tidak menerima
         apa pun — pastikan pendekatanmu mengizinkan itu.

🎯 Learning Goals:
- [ ] Menerjemahkan masalah partisi menjadi subset sum
- [ ] Menyatakan tujuan dalam satu variabel saja
- [ ] Menangani kasus bagian kosong
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung total S

    // TODO: tandai seluruh jumlah subhimpunan yang bisa dicapai

    // TODO: cari x tercapai yang meminimumkan |S - 2x|

    return 0;
}
