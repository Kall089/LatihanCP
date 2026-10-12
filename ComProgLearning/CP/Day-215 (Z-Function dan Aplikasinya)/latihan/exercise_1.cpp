/*
============================================================
🏋️ Exercise 1: Bangun Z-Array
============================================================
Day: 215 | Difficulty: Easy
Topic: Konstruksi Z-function
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N. Hitung Z-array dari S, di mana z[i]
didefinisikan sebagai panjang string terpanjang yang sekaligus merupakan
awalan dari S dan awalan dari S[i..N-1]. Gunakan konvensi z[0] = 0.
Solusi naif O(N^2) akan TLE pada string seperti "aaaa...a", jadi kamu harus
mengimplementasikan versi z-box yang berjalan dalam O(N).

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan z[0..N-1], dipisah spasi

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
aaaa

📎 SAMPLE OUTPUT 1:
0 3 2 1

📎 SAMPLE INPUT 2:
aabcaabxaabc

📎 SAMPLE OUTPUT 2:
0 1 0 0 3 1 0 0 4 1 0 0

💡 HINT: Simpan interval [l, r) yang paling jauh menjangkau ke kanan dan sudah
         terbukti sama dengan awalan S. Saat i berada di dalamnya, posisi i
         punya "kembaran" di i - l yang jawabannya sudah kamu ketahui.

🎯 Learning Goals:
- [ ] Menulis 9 baris z-box dengan benar dari nol
- [ ] Mengerti kenapa tebakan awal dibatasi r - i
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: siapkan z, l = 0, r = 0

    // TODO: untuk i = 1..n-1
    //   - kalau i < r, salin tebakan dari kembaran (ingat batasnya!)
    //   - perluas manual dengan while
    //   - kalau jangkauan baru melewati r, perbarui l dan r

    // TODO: cetak z

    return 0;
}
