/*
============================================================
🏋️ Exercise 5: Jumlah Substring Berbeda
============================================================
Day: 214 | Difficulty: Hard
Topic: Prefix function pada string terbalik, inkremental
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S. Hitung banyaknya SUBSTRING BERBEDA (tidak kosong) yang
dimiliki S. Dua substring dianggap sama jika isinya identik, tidak peduli
posisinya. Sebagai contoh, "aba" memiliki substring berbeda:
"a", "b", "ab", "ba", "aba" — total 5 buah.
Karena |S| kecil, kamu boleh memakai algoritma O(N^2). Idenya: tambahkan
karakter satu per satu dan hitung berapa substring BARU yang lahir setiap
kali sebuah karakter ditambahkan di akhir.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya substring berbeda

📏 CONSTRAINTS:
- 1 <= |S| <= 5000
- Jawaban muat di long long

📎 SAMPLE INPUT 1:
aba

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
aaaa

📎 SAMPLE OUTPUT 2:
4

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:
10

💡 HINT: Substring baru saat menambah karakter = sufiks dari string saat ini
         yang belum pernah muncul sebelumnya. Sufiks dari cur adalah prefiks
         dari reverse(cur). Berapa banyak prefiks reverse(cur) yang muncul
         lagi di dalamnya? Lihat nilai maksimum pi.

🎯 Learning Goals:
- [ ] Menerjemahkan "sufiks" jadi "prefiks dari string terbalik"
- [ ] Melihat max(pi) sebagai "bagian yang sudah pernah ada"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: bangun string cur secara bertahap

    // TODO: untuk setiap tahap, balik cur, hitung pi, ambil max(pi)

    // TODO: total += |cur| - max(pi)

    return 0;
}
