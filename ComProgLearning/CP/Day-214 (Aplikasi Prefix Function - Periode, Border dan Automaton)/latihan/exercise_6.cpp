/*
============================================================
🏋️ Exercise 6: Kata Sandi Aman
============================================================
Day: 214 | Difficulty: Hard (Contest-level)
Topic: DP di atas KMP automaton
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah sistem menganggap kata sandi TIDAK AMAN jika di dalamnya muncul
sebuah pola terlarang P sebagai substring (di posisi mana pun).
Diberikan panjang kata sandi L, ukuran alfabet A (kata sandi hanya boleh
memakai A huruf pertama: 'a', 'b', ..., huruf ke-A), dan pola terlarang P,
hitung banyaknya kata sandi AMAN yang mungkin dibuat. Karena jawabannya
bisa sangat besar, cetak hasilnya modulo 1_000_000_007.
Dijamin P hanya memakai huruf yang termasuk dalam A huruf pertama.

📥 INPUT FORMAT:
- Baris pertama: dua bilangan L dan A
- Baris kedua: string P

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya kata sandi aman mod 1e9+7

📏 CONSTRAINTS:
- 1 <= L <= 2000
- 1 <= A <= 26
- 1 <= |P| <= 200

📎 SAMPLE INPUT 1:
3 2
aa

📎 SAMPLE OUTPUT 1:
5

Penjelasan: dari 8 string panjang 3 atas {a,b}, yang memuat "aa" adalah
"aaa", "aab", "baa" -> 3 buah. Sisanya 8 - 3 = 5.

📎 SAMPLE INPUT 2:
4 2
ab

📎 SAMPLE OUTPUT 2:
5

📎 SAMPLE INPUT 3:
2 3
abc

📎 SAMPLE OUTPUT 3:
9

💡 HINT: State DP = "sudah cocok berapa huruf dari P". Transisinya persis
         tabel automaton. State |P| berarti gagal — buang cabang itu.

🎯 Learning Goals:
- [ ] Melihat automaton sebagai graf state untuk DP
- [ ] Menghitung "menghindari pola" alih-alih "mengandung pola"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, A;
    cin >> L >> A;
    string p;
    cin >> p;

    // TODO: bangun automaton dari p + '#'

    // TODO: dp[state], mulai dp[0] = 1

    // TODO: L kali: untuk tiap state dan tiap huruf c < A, pindah ke aut[s][c],
    //       lewati kalau tujuannya == |p|

    // TODO: jumlahkan seluruh dp, cetak mod 1e9+7

    return 0;
}
