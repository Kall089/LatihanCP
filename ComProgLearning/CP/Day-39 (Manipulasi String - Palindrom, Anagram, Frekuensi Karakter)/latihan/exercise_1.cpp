/*
============================================================
🏋️ Exercise 1: Cek Palindrom
============================================================
Day: 32 | Difficulty: Easy
Topic: Dua pointer pada string
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah kata yang hanya terdiri dari huruf kecil a-z.
Tentukan apakah kata tersebut merupakan palindrom, yaitu kata yang
dibaca dari depan dan dari belakang menghasilkan urutan huruf yang sama.
Contohnya "katak" adalah palindrom, sedangkan "kodak" bukan.
Kerjakan tanpa membuat salinan string yang dibalik.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris: "YA" jika palindrom, "TIDAK" jika bukan.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- S hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
katak

📎 SAMPLE OUTPUT 1:
YA

📎 SAMPLE INPUT 2:
kodak

📎 SAMPLE OUTPUT 2:
TIDAK

📎 SAMPLE INPUT 3:
a

📎 SAMPLE OUTPUT 3:
YA

💡 HINT:
- Taruh satu penunjuk di huruf paling kiri, satu lagi di paling kanan.
- Bandingkan, lalu majukan keduanya ke tengah.
- Berhenti ketika kedua penunjuk bertemu. Huruf tengah tidak perlu dicek.

🎯 Learning Goals:
- [ ] Menerapkan dua pointer pada string
- [ ] Menyadari cukup N/2 perbandingan
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

    int left = 0;
    int right = s.size() - 1;

    while (right >= left)
    {
        if (s[left] != s[right])
        {
            cout << "TIDAK";
            return 0;
        }
        else
        {
            left++;
            right--;
        }
    }

    cout << "YA";

    return 0;
}
