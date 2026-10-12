/*
============================================================
🏋️ Exercise 2: Anagram Beruntun
============================================================
Day: 40 | Difficulty: Easy
Topic: Frekuensi 26 huruf
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan T pasang string yang seluruhnya terdiri dari huruf kecil.
Untuk setiap pasangan, tentukan apakah kedua string merupakan ANAGRAM,
yaitu apakah keduanya tersusun dari huruf yang sama persis dengan jumlah
yang sama persis, hanya urutannya yang boleh berbeda.
Cetak "YES" atau "NO" untuk setiap pasangan.

📥 INPUT FORMAT:
- Baris pertama: T
- Setiap kasus: dua baris berisi string s dan t

📤 OUTPUT FORMAT:
- T baris berisi YES atau NO

📏 CONSTRAINTS:
- 1 <= T <= 10^4
- 1 <= |s|, |t| <= 10^5
- Total panjang seluruh string <= 10^6

📎 SAMPLE INPUT 1:
3
listen
silent
hello
world
abc
abcd

📎 SAMPLE OUTPUT 1:
YES
NO
NO

💡 HINT: Ada satu pemeriksaan yang sangat murah dan harus dilakukan
         PALING AWAL — perhatikan kasus ketiga.
         Kamu juga bisa menggabungkan dua sapuan menjadi satu: hitung
         huruf string pertama, lalu KURANGI saat menyapu string kedua.
         Kalau ada yang menjadi negatif, jawabannya sudah pasti.
         Karena ada banyak kasus uji, perhatikan bagaimana kamu
         membersihkan penghitungmu.

🎯 Learning Goals:
- [ ] Memakai array 26 elemen untuk huruf
- [ ] Melakukan pemeriksaan murah lebih dulu
- [ ] Membersihkan penghitung dengan benar di multi-test case
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int hitung[26] = {};

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        for (char c : s)
        {
        }
    }
}