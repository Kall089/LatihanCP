/*
============================================================
🏋️ Exercise 2: Anagram atau Bukan
============================================================
Day: 32 | Difficulty: Easy
Topic: Tabel frekuensi 26 huruf
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Dua kata disebut anagram jika keduanya tersusun dari huruf-huruf yang
sama persis, hanya urutannya yang berbeda. Contoh: "gerak" dan "kerag"
adalah anagram karena keduanya memuat g, e, r, a, k masing-masing satu kali.
Diberikan dua kata A dan B, tentukan apakah keduanya anagram.
Jangan memakai sorting; selesaikan dalam O(N).

📥 INPUT FORMAT:
- Baris pertama: string A
- Baris kedua: string B

📤 OUTPUT FORMAT:
- Satu baris: "YA" jika anagram, "TIDAK" jika bukan.

📏 CONSTRAINTS:
- 1 <= |A|, |B| <= 10^6
- A dan B hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
gerak
kerag

📎 SAMPLE OUTPUT 1:
YA

📎 SAMPLE INPUT 2:
abc
abd

📎 SAMPLE OUTPUT 2:
TIDAK

📎 SAMPLE INPUT 3:
aab
aba

📎 SAMPLE OUTPUT 3:
YA

💡 HINT:
- Kalau panjangnya sudah beda, langsung TIDAK (pengecekan paling murah).
- Buat array hitung[26]. Tambah 1 untuk tiap huruf A, kurangi 1 untuk tiap huruf B.
- Kalau semua isinya nol di akhir, keduanya anagram.

🎯 Learning Goals:
- [ ] Memakai tabel frekuensi sebagai pengganti sorting
- [ ] Melakukan pengecekan murah lebih dulu
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    cin >> a >> b;

    int hitung[26] = {};

    for (int x : a)
    {
        hitung[x - 'a']++;
    }

    for (int x : b)
    {
        hitung[x - 'a']--;
    }

    for (int i = 0; i < 26; i++)
    {
        if (hitung[i] != 0)
        {
            cout << "TIDAK";
            return 0;
        }
    }
    cout << "YA";

    return 0;
}
