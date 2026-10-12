/*
============================================================
🏋️ Exercise 4: Susun Ulang Jadi Palindrom
============================================================
Day: 32 | Difficulty: Medium
Topic: Tabel frekuensi + konstruksi
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah kata. Tentukan apakah huruf-hurufnya bisa disusun ulang
menjadi sebuah palindrom. Jika bisa, cetak salah satu palindrom yang mungkin;
agar jawabannya tunggal, susun paruh kirinya berurutan secara alfabet.
Jika tidak mungkin, cetak "TIDAK ADA".

Contoh: dari "aabbc" bisa dibentuk "abcba" (paruh kiri "ab" terurut alfabet,
huruf tengah "c", lalu paruh kanan adalah cerminannya).

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris: palindrom hasil susunan, atau "TIDAK ADA".

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
aabbc

📎 SAMPLE OUTPUT 1:
abcba

📎 SAMPLE INPUT 2:
aabbcd

📎 SAMPLE OUTPUT 2:
TIDAK ADA

📎 SAMPLE INPUT 3:
aabb

📎 SAMPLE OUTPUT 3:
abba

💡 HINT:
- Dalam palindrom, setiap huruf harus berpasangan.
- Paling banyak SATU huruf boleh berjumlah ganjil; huruf itu ditaruh di tengah.
- Jadi: hitung berapa huruf yang frekuensinya ganjil. Kalau lebih dari 1 -> mustahil.
- Untuk menyusunnya: ambil separuh dari tiap huruf secara alfabet, lalu cerminkan.

🎯 Learning Goals:
- [ ] Menerapkan syarat palindrom pada tabel frekuensi
- [ ] Menyusun jawaban, bukan sekadar mengecek
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int f[26] = {};

    for (char c : s)
    {
        f[c - 'a']++;
    }

    int ganjil = 0;

    for (int i = 0; i < 26; i++)
    {
        if (f[i] % 2 == 1)
        {
            ganjil++;
        }
    }

    if (ganjil > 1)
    {
        cout << "TIDAK ADA";
        return 0;
    }

    string kiri, tengah;

    for (int i = 0; i < 26; i++)
    {
        if (f[i] % 2 == 1)
        {
            tengah = string(1, char(i + 'a'));
        }
        kiri += string(f[i] / 2, char(i + 'a'));
    }

    string kanan = kiri;

    reverse(kanan.begin(), kanan.end());

    cout << kiri << tengah << kanan;
}
