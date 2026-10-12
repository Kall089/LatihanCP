/*
============================================================
🏋️ Exercise 4: Periode Terkecil
============================================================
Day: 213 | Difficulty: Medium
Topic: Periode = n - pi[n-1]
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Bilangan p disebut periode dari string S sepanjang n jika S[i] sama dengan
S[i + p] untuk setiap i yang sah (yaitu selama i + p masih di dalam S).
Dengan kata lain, S terbentuk dari pengulangan potongan sepanjang p,
walaupun pengulangan terakhir boleh terpotong.

Diberikan S, cetak periode TERKECIL-nya, lalu cetak "YA" jika S merupakan
pengulangan utuh atau "TIDAK" jika bukan.

S disebut pengulangan utuh kalau ia tersusun dari potongan yang BENAR-BENAR
LEBIH PENDEK yang diulang minimal dua kali. Jadi syaratnya ada dua:
periode harus lebih kecil dari n, DAN n harus habis dibagi periode.

Contoh: "ababab" punya periode terkecil 2, dan 6 habis dibagi 2, sehingga
string itu benar-benar pengulangan utuh dari "ab".

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris berisi dua nilai: periode terkecil dan "YA" atau "TIDAK", dipisah spasi.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
ababab

📎 SAMPLE OUTPUT 1:
2 YA

📎 SAMPLE INPUT 2:
aabaa

📎 SAMPLE OUTPUT 2:
3 TIDAK

📎 SAMPLE INPUT 3:
abcd

📎 SAMPLE OUTPUT 3:
4 TIDAK

💡 HINT:
- Rumusnya sangat pendek: periode terkecil = n - pi[n-1].
- Intuisinya: border terpanjang adalah bagian yang "tumpang tindih" antara
  awal dan akhir; sisanya (n dikurangi border) adalah panjang satu putaran.
- Untuk mengecek pengulangan utuh syaratnya DUA: periode < n DAN n % periode == 0.
  Jangan lupa syarat pertama! Lihat sample 3 di bawah.
- Perhatikan sample 2: "aabaa" berperiode 3 (s[0]==s[3], s[1]==s[4] terpenuhi),
  tetapi 5 tidak habis dibagi 3, sehingga bukan pengulangan utuh.
- Sample 3 adalah jebakannya: "abcd" tidak punya border, jadi periodenya 4
  (sama dengan panjangnya). Walaupun 4 % 4 == 0, ini BUKAN pengulangan
  karena potongannya tidak lebih pendek dari string aslinya.

🎯 Learning Goals:
- [ ] Menurunkan periode dari border
- [ ] Membedakan periode dan pengulangan utuh
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun pi

    // TODO: periode = n - pi[n-1]

    // TODO: Cek apakah n habis dibagi periode

    return 0;
}
