/*
============================================================
🏋️ Exercise 5: Selisih Maksimum-Minimum Terbatas
============================================================
Day: 169 | Difficulty: Hard
Topic: Sparse table + binary search / two pointers
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan dan sebuah bilangan L.
Cari SUBARRAY TERPANJANG (potongan berurutan) sedemikian sehingga selisih
antara elemen terbesar dan elemen terkecil di dalamnya tidak melebihi L.
Cetak panjang subarray terpanjang itu.

📥 INPUT FORMAT:
- Baris pertama: N dan L
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: panjang terpanjang

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= L <= 10^9
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
5 2
8 2 4 7 2

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
4 0
3 3 3 1

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Perhatikan sebuah sifat penting: kalau sebuah subarray sudah
         memenuhi syarat, maka SETIAP potongan di dalamnya juga memenuhi
         syarat. Sifat itu punya nama, dan ia membuka dua pendekatan
         sekaligus.
         Pendekatan pertama: untuk setiap ujung kiri, cari ujung kanan
         terjauh yang masih memenuhi — dan karena sifat tadi, pencarian itu
         bisa dilakukan dengan pencarian biner. Kamu butuh cara menjawab
         "berapa maksimum dan minimum pada rentang ini" dengan cepat.
         Pendekatan kedua: perhatikan bahwa saat ujung kiri maju, ujung
         kanan terjauh juga tidak pernah mundur. Apa artinya untuk
         kompleksitas?
         Kerjakan dengan pendekatan pertama dulu (memakai struktur hari ini),
         lalu pikirkan bagaimana pendekatan kedua menghilangkan faktor log.

🎯 Learning Goals:
- [ ] Menggabungkan sparse table dengan binary search
- [ ] Mengenali monotonisitas yang memungkinkan two pointers
- [ ] Membandingkan O(n log n) dan O(n) untuk masalah yang sama
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: dua sparse table (max dan min)

    // TODO: untuk tiap l, binary search ujung kanan terjauh

    return 0;
}
