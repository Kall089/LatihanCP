/*
============================================================
🏋️ Exercise 3: Hitung Kemunculan Setiap Prefiks
============================================================
Day: 214 | Difficulty: Medium
Topic: Agregasi mundur pada rantai pi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N. Untuk setiap i dari 1 sampai N, hitung
berapa kali prefiks S[0..i-1] (yaitu awalan sepanjang i) muncul sebagai
substring di dalam S. Kemunculan yang tumpang tindih tetap dihitung.
Sebagai contoh, pada string "aaa": awalan "a" muncul 3 kali, "aa" muncul
2 kali, dan "aaa" muncul 1 kali.
Solusi O(N^2) akan TLE — kamu perlu menyelesaikannya dalam satu kali jalan.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- N baris. Baris ke-i berisi banyaknya kemunculan awalan sepanjang i.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- Jawaban bisa mencapai ~5 * 10^11, gunakan long long

📎 SAMPLE INPUT 1:
aaa

📎 SAMPLE OUTPUT 1:
3
2
1

📎 SAMPLE INPUT 2:
abacaba

📎 SAMPLE OUTPUT 2:
4
2
2
1
1
1
1

💡 HINT: Setiap posisi i menyumbang satu kemunculan untuk awalan sepanjang
         pi[i]. Sumbangan itu harus diwariskan ke border-nya. Kalau kamu
         memproses panjang dari BESAR ke KECIL, satu langkah pewarisan cukup.

🎯 Learning Goals:
- [ ] Memahami pewarisan nilai lewat rantai pi
- [ ] Menghindari penelusuran rantai berulang (yang membuatnya O(n^2))
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

    // TODO: bangun pi

    // TODO: cnt[pi[i]]++ untuk semua i

    // TODO: wariskan MUNDUR: for len = n..1 -> cnt[pi[len-1]] += cnt[len]

    // TODO: tambahkan 1 untuk kemunculan awalan itu sendiri, lalu cetak

    return 0;
}
