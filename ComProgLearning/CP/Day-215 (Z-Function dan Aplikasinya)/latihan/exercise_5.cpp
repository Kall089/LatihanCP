/*
============================================================
🏋️ Exercise 5: Awalan Bersama Minimal K
============================================================
Day: 215 | Difficulty: Hard
Topic: Agregasi pada Z-array + jawaban untuk semua k
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N. Untuk setiap k dari 1 sampai N, hitung
f(k) = banyaknya posisi i (0 <= i < N) sedemikian sehingga sufiks S[i..N-1]
diawali oleh prefiks S sepanjang k. Dengan kata lain, f(k) menghitung berapa
kali prefiks sepanjang k muncul sebagai substring di dalam S.
Perhatikan bahwa posisi i = 0 selalu ikut terhitung untuk setiap k.
Solusi O(N^2) akan TLE — kamu perlu O(N).

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- N baris. Baris ke-k berisi f(k).

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- Jawaban muat di long long

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

💡 HINT: Posisi i menyumbang untuk SEMUA k dari 1 sampai z[i] sekaligus.
         Itu adalah penambahan pada satu rentang. Kamu tidak perlu segment
         tree untuk ini — ada cara yang jauh lebih murah untuk banyak
         penambahan rentang yang dijawab sekali di akhir (ingat Day 31).

🎯 Learning Goals:
- [ ] Melihat z[i] sebagai "sumbangan ke rentang [1, z[i]]"
- [ ] Menggabungkan Z-function dengan suffix sum
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

    // TODO: bangun z (ingat z[0] = 0, tapi i = 0 harus tetap dihitung)

    // TODO: buat array hitung[len] = berapa posisi punya z tepat sebesar len

    // TODO: f(k) = banyaknya i dengan z[i] >= k -> suffix sum, lalu +1 untuk i = 0

    return 0;
}
