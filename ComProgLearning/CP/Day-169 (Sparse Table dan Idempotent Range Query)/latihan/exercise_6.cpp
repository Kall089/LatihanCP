/*
============================================================
🏋️ Exercise 6: Nilai yang Paling Sering Muncul
============================================================
Day: 169 | Difficulty: Hard (Contest-level)
Topic: Sparse table pada array terkompresi (run-length)
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan yang sudah TERURUT MENAIK (boleh ada
nilai yang sama berulang), dan Q pertanyaan rentang [a, b] (1-based,
inklusif).
Untuk setiap pertanyaan, cetak BERAPA KALI nilai yang paling sering muncul
di dalam rentang itu muncul.
Sebagai contoh, pada rentang berisi (2, 2, 3, 3, 3, 5), nilai 3 muncul tiga
kali dan itulah yang terbanyak, sehingga jawabannya 3.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan terurut menaik
- Q baris berikutnya: a dan b

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 10^5
- -10^5 <= nilai <= 10^5

📎 SAMPLE INPUT 1:
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10

📎 SAMPLE OUTPUT 1:
1
4
3

💡 HINT: Karena array sudah terurut, nilai yang sama selalu berkelompok
         dalam blok yang berdampingan. Padatkan array menjadi daftar blok:
         setiap blok punya panjang, indeks awal, dan indeks akhir.
         Sebuah rentang query akan memotong paling banyak DUA blok secara
         sebagian (yang pertama dan yang terakhir), sedangkan blok-blok di
         tengahnya termuat UTUH.
         Untuk bagian tengah, kamu butuh "panjang blok terbesar di antara
         blok-blok utuh" — dan itulah tempat struktur hari ini dipakai.
         Untuk kedua blok tepi, hitung potongannya secara langsung.
         Waspadai kasus khusus: bagaimana kalau seluruh rentang query berada
         DI DALAM SATU blok saja? Sampel pertama menguji tepat kasus itu.

🎯 Learning Goals:
- [ ] Memadatkan array terurut menjadi blok (run-length)
- [ ] Memisahkan bagian tepi dan bagian tengah pada query rentang
- [ ] Menangani kasus "seluruh query di dalam satu blok"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: padatkan menjadi blok: nilai, awal, akhir, panjang

    // TODO: sparse table MAKSIMUM atas panjang blok

    // TODO: per query: potongan blok tepi + maksimum blok tengah

    return 0;
}
