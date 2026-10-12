/*
============================================================
🏋️ Exercise 2: Palindrome Check (Cek Palindrom)
============================================================
Day: 3 | Difficulty: Easy
Topic: String, Reverse
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string s yang hanya terdiri dari huruf kecil.
Tentukan apakah string tersebut merupakan palindrome atau bukan.

Palindrome = string yang sama jika dibaca dari depan maupun belakang.
Contoh palindrome: "aba", "racecar", "a", "abba"
Bukan palindrome: "abc", "hello"

📥 INPUT FORMAT:
- Satu baris: string s (hanya huruf kecil a-z)

📤 OUTPUT FORMAT:
- "YES" jika palindrome, "NO" jika bukan

📏 CONSTRAINTS:
- 1 ≤ |s| ≤ 100,000

📎 SAMPLE INPUT 1:
racecar

📎 SAMPLE OUTPUT 1:
YES

📎 SAMPLE INPUT 2:
hello

📎 SAMPLE OUTPUT 2:
NO

📎 SAMPLE INPUT 3:
a

📎 SAMPLE OUTPUT 3:
YES

💡 HINT: Bandingkan string asli dengan string yang di-reverse

🎯 Learning Goals:
- [ ] Baca string
- [ ] Reverse string
- [ ] Bandingkan dua string
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca string s
    string s;
    cin >> s;

    // TODO: Buat salinan string lalu reverse
    string rev = s;
    reverse(rev.begin(), rev.end());

    // TODO: Bandingkan string asli dengan reversed
    //       Output "YES" atau "NO"
    if (rev == s)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
