/*
============================================================
🏋️ Exercise 2: Word Frequency (Map)
============================================================
Day: 4 | Difficulty: Easy
Topic: Map as frequency counter
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N buah kata. Untuk setiap kata UNIK, cetak berapa kali
kata tersebut muncul. Output diurutkan secara LEXICOGRAPHIC (A-Z).

📥 INPUT FORMAT:
- Baris pertama: integer N
- N baris berikutnya: satu kata per baris (huruf kecil)

📤 OUTPUT FORMAT:
- Untuk setiap kata unik (urut lexicographic):
  "kata frekuensi"

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ |kata| ≤ 20
- Kata hanya berisi huruf kecil a-z

📎 SAMPLE INPUT 1:
7
apple
banana
apple
cherry
banana
apple
date

📎 SAMPLE OUTPUT 1:
apple 3
banana 2
cherry 1
date 1

📎 SAMPLE INPUT 2:
3
hello
hello
hello

📎 SAMPLE OUTPUT 2:
hello 3

💡 HINT: map<string, int> freq; lalu freq[word]++
         map otomatis sorted by key!

🎯 Learning Goals:
- [ ] Gunakan map<string, int> untuk frequency count
- [ ] Iterasi map (otomatis urut by key)
- [ ] Output key dan value
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // TODO: Baca N
  int n;
  cin >> n;

  // TODO: Baca N kata, hitung frekuensi dengan map
  map<string, int> freq;

  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    freq[s]++;
  }
  cout << endl;

  for (auto &[s, i] : freq)
  {
    cout << s << " " << i << endl;
  }

  // TODO: Iterasi map dan output (otomatis sorted by key)

  return 0;
}
