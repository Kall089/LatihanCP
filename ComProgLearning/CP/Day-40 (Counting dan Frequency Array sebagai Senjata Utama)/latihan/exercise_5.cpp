/*
============================================================
🏋️ Exercise 5: Hitung Huruf dalam Substring
============================================================
Day: 40 | Difficulty: Hard
Topic: Frekuensi prefiks per huruf
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N yang terdiri dari huruf kecil, dan Q
pertanyaan. Setiap pertanyaan berisi tiga hal: dua indeks L dan R
(1-based, inklusif) dan sebuah huruf c. Kamu harus menjawab berapa kali
huruf c muncul di dalam substring S[L..R].
Menjawab setiap pertanyaan dengan menyapu substringnya akan menghasilkan
10^10 operasi dan pasti TLE.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: string S
- Q baris berikutnya: L, R, dan satu huruf c

📤 OUTPUT FORMAT:
- Q baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= N <= 10^5
- 1 <= Q <= 10^5
- 1 <= L <= R <= N

📎 SAMPLE INPUT 1:
8 3
abacabad
1 8 a
2 5 a
3 3 b

📎 SAMPLE OUTPUT 1:
4
2
0

💡 HINT: Buat prefix sum TERPISAH untuk masing-masing dari 26 huruf.
         Kamu bisa menyimpannya sebagai array dua dimensi berukuran
         (N+1) kali 26.
         Hitung dulu berapa memori yang dibutuhkan sebelum menulis:
         apakah muat dalam 256 MB untuk N = 10^5? Bagaimana kalau
         N = 10^6?

🎯 Learning Goals:
- [ ] Membangun 26 prefix sum sekaligus secara efisien
- [ ] Memperkirakan pemakaian memori sebelum menulis kode
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: pre[i+1] = pre[i], lalu naikkan satu slot

    // TODO: jawab dengan pre[r][c] - pre[l-1][c]

    return 0;
}
