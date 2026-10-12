/*
============================================================
🏋️ Exercise 3: Reverse String with Stack
============================================================
Day: 5 | Difficulty: Easy-Medium
Topic: Stack, string reversal
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string yang mengandung huruf dan tanda '#'.
Tanda '#' berarti BACKSPACE (hapus karakter sebelumnya).
Proses string tersebut dan cetak hasil akhirnya.

Contoh: "abc#d" → ketik a,b,c lalu backspace (hapus c), ketik d → "abd"

📥 INPUT FORMAT:
- Satu baris: string s (huruf kecil dan '#')

📤 OUTPUT FORMAT:
- Satu baris: string hasil setelah semua backspace diproses
  (bisa kosong, jika kosong cetak baris kosong)

📏 CONSTRAINTS:
- 1 ≤ |s| ≤ 200,000
- s hanya berisi huruf kecil a-z dan '#'
- Backspace pada string kosong = tidak ada efek

📎 SAMPLE INPUT 1:
abc#d

📎 SAMPLE OUTPUT 1:
abd

📎 SAMPLE INPUT 2:
ab##c

📎 SAMPLE OUTPUT 2:
c

📎 SAMPLE INPUT 3:
###abc

📎 SAMPLE OUTPUT 3:
abc

💡 HINT: Gunakan stack. Huruf → push. '#' → pop (jika tidak kosong).
         Di akhir, baca stack dari bawah ke atas (atau pakai string/deque).

🎯 Learning Goals:
- [ ] Stack sebagai simulator "undo"
- [ ] Handle edge case (backspace saat kosong)
- [ ] Reconstruct string dari stack
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

  string st = "";

  for (char v : s)
  {
    if (v != '#')
    {
      st.push_back(v);
    }
    else
    {
      st.pop_back();
    }
  }

  cout << st;

  return 0;
}
