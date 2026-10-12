/*
============================================================
🏋️ Exercise 4: Kalung Berputar
============================================================
Day: 215 | Difficulty: Medium
Topic: Rotasi via z pada A + sep + B + B
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Dua kalung direpresentasikan sebagai string A dan B dengan panjang sama.
Kalung dapat diputar, sehingga A dianggap SAMA dengan B jika A bisa diperoleh
dengan memutar B (memindahkan sejumlah karakter dari depan ke belakang).
Untuk setiap pasangan yang diberikan, tentukan apakah A adalah rotasi dari B.
Jika ya, cetak juga berapa banyak nilai pergeseran k (0 <= k < |B|) yang
berbeda sehingga memutar B sejauh k menghasilkan A.

📥 INPUT FORMAT:
- Baris pertama: Q (banyaknya pasangan)
- Setiap pasangan: dua baris, A lalu B

📤 OUTPUT FORMAT:
- Untuk tiap pasangan: "YES <banyak_k>" atau "NO"

📏 CONSTRAINTS:
- 1 <= Q <= 10
- 1 <= |A| = |B| <= 5 * 10^5

📎 SAMPLE INPUT 1:
3
abcde
cdeab
aaaa
aaaa
abc
acb

📎 SAMPLE OUTPUT 1:
YES 1
YES 4
NO

💡 HINT: Setiap rotasi B adalah substring sepanjang |B| dari B+B. Jadi cukup
         cari A di dalam B+B — tapi hati-hati, B+B punya |B|+1 posisi awal
         yang valid, dan posisi terakhir adalah duplikat dari posisi 0.

🎯 Learning Goals:
- [ ] Trik "B + B memuat semua rotasi"
- [ ] Menghindari menghitung rotasi yang sama dua kali
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        string a, b;
        cin >> a >> b;

        // TODO: bentuk g = a + '\1' + b + b

        // TODO: hitung z, cari posisi i pada bagian b+b dengan z[i] >= |a|

        // TODO: hanya hitung pergeseran k = 0..|b|-1 (posisi ke-|b| adalah duplikat)
    }

    return 0;
}
