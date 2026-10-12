/*
============================================================
🏋️ Exercise 1: Akar Kuadrat Tanpa sqrt
============================================================
Day: 51 | Difficulty: Easy
Topic: Kerangka binary search real
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan Q bilangan real non-negatif. Untuk setiap bilangan, hitung akar
kuadratnya dan cetak dengan 9 angka di belakang koma.
Kamu TIDAK BOLEH memakai fungsi sqrt, pow, maupun fungsi akar lain dari
pustaka — hitung sendiri dengan binary search.
Kesalahan absolut atau relatif tidak boleh melebihi 1e-9.

📥 INPUT FORMAT:
- Baris pertama: Q
- Q baris berikutnya: masing-masing satu bilangan real v

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan real dengan 9 desimal

📏 CONSTRAINTS:
- 1 <= Q <= 10^4
- 0 <= v <= 10^18

📎 SAMPLE INPUT 1:
3
2
9
0.25

📎 SAMPLE OUTPUT 1:
1.414213562
3.000000000
0.500000000

💡 HINT: Predikatnya "mid * mid >= v", dan itu monoton naik terhadap mid.
         Dua hal yang harus kamu putuskan sendiri:
         Pertama, batas atas pencarian. Perhatikan bahwa untuk v < 1,
         akarnya justru LEBIH BESAR dari v — jadi memakai hi = v akan salah.
         Kedua, kriteria berhentinya. Pikirkan apa yang terjadi pada
         "while (hi - lo > 1e-9)" ketika v bernilai 10^18.
         Untuk mencetak, ingat bahwa setprecision saja tidak cukup.

🎯 Learning Goals:
- [ ] Menulis kerangka iterasi tetap
- [ ] Menentukan batas atas yang benar untuk kedua kasus (v < 1 dan v > 1)
- [ ] Mencetak dengan presisi yang benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap v, tentukan lo dan hi

    // TODO: iterasi tetap, lo = mid (bukan mid + 1)

    // TODO: cetak dengan 9 desimal

    return 0;
}
