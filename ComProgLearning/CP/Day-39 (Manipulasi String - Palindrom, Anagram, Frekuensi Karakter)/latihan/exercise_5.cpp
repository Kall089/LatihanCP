/*
============================================================
🏋️ Exercise 5: Menghitung Kemunculan Pola
============================================================
Day: 32 | Difficulty: Medium
Topic: Pencarian pola (boleh tumpang tindih)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah teks T dan sebuah pola P. Hitung berapa kali P muncul
di dalam T. Kemunculan yang saling tumpang tindih tetap dihitung terpisah.

Contoh: pada teks "ababa", pola "aba" muncul 2 kali, yaitu pada posisi 0
dan posisi 2, walaupun keduanya berbagi huruf 'a' di tengah.

📥 INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah kemunculan P di dalam T.

📏 CONSTRAINTS:
- 1 <= |P| <= |T| <= 2000
- T dan P hanya berisi huruf kecil 'a'-'z'

📎 SAMPLE INPUT 1:
ababa
aba

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
aaaa
aa

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
abcde
xyz

📎 SAMPLE OUTPUT 3:
0

💡 HINT:
- Karena |T| <= 2000, pencarian naif O(|T| x |P|) sudah cukup cepat.
- Coba tiap posisi awal i, lalu bandingkan |P| huruf berikutnya.
- Untuk teks yang jauh lebih panjang, teknik ini diganti KMP (Day 34).

🎯 Learning Goals:
- [ ] Memahami arti kemunculan tumpang tindih
- [ ] Menyadari batas kapan pencarian naif masih aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string t, p;

    cin >> t >> p;

    int n = t.size();
    int m = p.size();
    int total = 0;

    for (int i = 0; i + m <= n; i++)
    {
        bool cocok = true;
        for (int j = 0; j < m; j++)
        {
            if (t[i + j] != p[j])
            {
                cocok = false;
                break;
            }
        }
        if (cocok)
        {
            total++;
        }
    }

    cout << total;
}
