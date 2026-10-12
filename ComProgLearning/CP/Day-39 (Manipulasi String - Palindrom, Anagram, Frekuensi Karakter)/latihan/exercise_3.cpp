/*
============================================================
🏋️ Exercise 3: Huruf Paling Sering Muncul
============================================================
Day: 32 | Difficulty: Easy
Topic: Tabel frekuensi + tie-breaking
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah kata. Tentukan huruf apa yang paling sering muncul
beserta jumlah kemunculannya. Jika ada beberapa huruf dengan jumlah
kemunculan yang sama banyak, pilih huruf yang paling awal secara alfabet.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris berisi huruf dan jumlah kemunculannya, dipisah spasi.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
kompetisi

📎 SAMPLE OUTPUT 1:
i 2

📎 SAMPLE INPUT 2:
aabbb

📎 SAMPLE OUTPUT 2:
b 3

📎 SAMPLE INPUT 3:
zzaa

📎 SAMPLE OUTPUT 3:
a 2

💡 HINT:
- Bangun tabel frekuensi 26 huruf.
- Telusuri dari indeks 0 ke 25 (urutan alfabet).
- Pakai perbandingan ">" saja agar huruf paling awal otomatis menang saat seri.

🎯 Learning Goals:
- [ ] Menangani tie-breaking alfabetis
- [ ] Menelusuri tabel frekuensi dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int hitung[26] = {};

    for (int x : s)
    {
        hitung[x - 'a']++;
    }

    int max_val = 0;

    for (int i = 0; i < 26; i++)
    {
        if (hitung[i] > hitung[max_val])
        {
            max_val = i;
        }
    }

    cout << char('a' + max_val) << " " << hitung[max_val];

    return 0;
}
