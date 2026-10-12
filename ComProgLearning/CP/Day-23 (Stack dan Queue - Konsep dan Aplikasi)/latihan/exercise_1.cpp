/*
============================================================
🏋️ Exercise 1: Valid Brackets (Stack)
============================================================
Day: 5 | Difficulty: Easy
Topic: Stack, bracket matching
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string yang terdiri dari karakter '(', ')', '{', '}', '[', ']'.
Tentukan apakah string tersebut VALID (balanced brackets).

Aturan:
- Setiap bracket buka harus ditutup oleh bracket tutup yang SESUAI
- Bracket harus ditutup dalam urutan yang BENAR
- String kosong dianggap valid

📥 INPUT FORMAT:
- Satu baris: string s

📤 OUTPUT FORMAT:
- "YES" jika valid, "NO" jika tidak

📏 CONSTRAINTS:
- 0 ≤ |s| ≤ 200,000
- s hanya berisi '(', ')', '{', '}', '[', ']'

📎 SAMPLE INPUT 1:
({[]})

📎 SAMPLE OUTPUT 1:
YES

📎 SAMPLE INPUT 2:
({[}])

📎 SAMPLE OUTPUT 2:
NO

📎 SAMPLE INPUT 3:
((

📎 SAMPLE OUTPUT 3:
NO

💡 HINT: Push bracket buka ke stack. Saat ketemu bracket tutup,
         cek apakah top stack match. Di akhir, stack harus kosong.

🎯 Learning Goals:
- [ ] Implementasi bracket matching dengan stack
- [ ] Handle edge cases (stack kosong saat match, sisa di stack)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    stack<char> st;

    for (char v : s)
    {
        if (v == '(' || v == '{' || v == '[')
        {
            st.push(v);
        }
        else
        {
        }
    }

    return 0;
}
