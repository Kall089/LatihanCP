/*
============================================================
🏋️ Exercise 4: Paritas Permutasi
============================================================
Day: 82 | Difficulty: Medium
Topic: Paritas permutasi sebagai invarian
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah permutasi p dari bilangan 1 sampai n.
Kamu boleh berulang kali memilih dua posisi dan MENUKAR isinya.
Diberikan juga sebuah bilangan k, tentukan apakah mungkin mengubah p menjadi
permutasi identitas (yaitu 1, 2, 3, ..., n) dengan TEPAT k penukaran.
Cetak "YA" atau "TIDAK".

📥 INPUT FORMAT:
- Baris pertama: n dan k
- Baris kedua: n bilangan p[i]

📤 OUTPUT FORMAT:
- "YA" atau "TIDAK"

📏 CONSTRAINTS:
- 1 <= n <= 2 * 10^5
- 0 <= k <= 10^18

📎 SAMPLE INPUT 1:
3 1
2 1 3

📎 SAMPLE OUTPUT 1:
YA

📎 SAMPLE INPUT 2:
3 2
2 1 3

📎 SAMPLE OUTPUT 2:
TIDAK

📎 SAMPLE INPUT 3:
3 3
2 1 3

📎 SAMPLE OUTPUT 3:
YA

💡 HINT: Perhatikan sampel 1, 2, dan 3: masukannya sama persis, hanya k yang
         berbeda, dan jawabannya berselang-seling. Itu petunjuk sangat kuat
         bahwa PARITAS k adalah kuncinya.
         Sekarang cari invariannya. Apa yang terjadi pada permutasi setiap
         kali kamu melakukan satu penukaran? Ada satu sifat yang selalu
         BERBALIK, dan sifat itulah invariannya (lebih tepatnya, paritas
         dari sifat itu yang menjadi invarian bersama paritas jumlah
         penukaran).
         Untuk menghitung sifat itu, pecah permutasi menjadi SIKLUS. Sebuah
         siklus dengan panjang L membutuhkan berapa penukaran untuk
         diluruskan? Hitung dengan tangan untuk siklus panjang 2 dan 3.
         Setelah itu, jumlah penukaran MINIMUM untuk mencapai identitas
         punya rumus sederhana dalam n dan banyaknya siklus.
         Terakhir, pikirkan: kalau kamu sudah mencapai identitas dengan m
         penukaran, bisakah kamu memakai lebih banyak? Berapa banyak
         tambahan yang mungkin, dan apa syaratnya?
         Kasus tepi penting: n sama dengan 1. Berapa penukaran tambahan yang
         mungkin di situ?

🎯 Learning Goals:
- [ ] Menghitung paritas permutasi lewat dekomposisi siklus
- [ ] Menggabungkan jumlah minimum dengan syarat paritas
- [ ] Menangani kasus tepi n = 1 yang membatasi penukaran tambahan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: pecah menjadi siklus

    // TODO: jumlah penukaran minimum, lalu syarat paritas untuk k

    return 0;
}
