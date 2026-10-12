/*
============================================================
🏋️ Exercise 4: Registration System (Map)
============================================================
Day: 4 | Difficulty: Medium
Topic: Map, string processing
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah sistem registrasi menerima request nama user.
- Jika nama BELUM terdaftar: output "OK" dan daftarkan
- Jika nama SUDAH terdaftar: beri nama baru "nama_i" dimana i
  adalah jumlah kali nama itu pernah di-request sebelumnya,
  lalu output nama baru tersebut

📥 INPUT FORMAT:
- Baris pertama: integer N (jumlah request)
- N baris berikutnya: satu nama per baris

📤 OUTPUT FORMAT:
- N baris: "OK" atau "nama_i"

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ |nama| ≤ 20

📎 SAMPLE INPUT 1:
4
abacaba
acaba
abacaba
acaba

📎 SAMPLE OUTPUT 1:
OK
OK
abacaba_1
acaba_1

📎 SAMPLE INPUT 2:
6
first
first
second
second
first
second

📎 SAMPLE OUTPUT 2:
OK
first_1
OK
second_1
first_2
second_2

💡 HINT: map<string, int> count — track berapa kali setiap nama
         sudah diminta. Jika count > 0, output nama_count lalu increment.

🎯 Learning Goals:
- [ ] Gunakan map untuk track state per key
- [ ] String concatenation dengan to_string
- [ ] Conditional logic berdasarkan map value
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

  map<string, int> val;

  while (n--)
  {
    string s;
    cin >> s;

    if (val[s] == 0)
    {
      cout << "OK" << endl;
    }
    else
    {
      cout << s << "_" << val[s] << endl;
    }
    val[s]++;
  }

  // TODO: Untuk setiap nama:
  //       - Jika belum ada di map (count == 0): output "OK", set count = 1
  //       - Jika sudah ada: output "nama_count", increment count

  return 0;
}
