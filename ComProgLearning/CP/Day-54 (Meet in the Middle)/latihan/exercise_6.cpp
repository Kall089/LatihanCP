/*
============================================================
🏋️ Exercise 6: Empat Bilangan Berjumlah Nol
============================================================
Day: 54 | Difficulty: Hard (Contest-level)
Topic: Meet in the middle tanpa bitmask (4-SUM)
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan empat array A, B, C, dan D yang masing-masing berisi N bilangan
bulat. Hitung ADA BERAPA BANYAK cara memilih tepat satu bilangan dari
masing-masing array sehingga keempatnya berjumlah TEPAT NOL.
Dua cara dianggap berbeda jika setidaknya satu indeks yang dipilih berbeda,
meskipun nilainya sama.
Pendekatan memeriksa seluruh kemungkinan membutuhkan N^4 operasi dan akan
TLE.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: masing-masing empat bilangan A[i], B[i], C[i], D[i]

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya cara

📏 CONSTRAINTS:
- 1 <= N <= 1000
- -2^28 <= nilai <= 2^28
- Jawaban bisa mencapai ~10^12

📎 SAMPLE INPUT 1:
6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45

📎 SAMPLE OUTPUT 1:
5

📎 SAMPLE INPUT 2:
1
1 -1 1 -1

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Meet in the middle tidak selalu tentang bitmask. Semangatnya
         adalah "pecah menjadi dua bagian yang bisa dikerjakan, lalu
         gabungkan dengan pencarian".
         Di sini, pecah keempat array menjadi dua kelompok: {A, B} dan
         {C, D}. Berapa banyak kemungkinan jumlah dari masing-masing
         kelompok, dan berapa biaya membangkitkannya?
         Setelah kedua kelompok dibangkitkan, kamu perlu menghitung berapa
         pasang yang berjumlah nol. Ada dua pilihan struktur untuk itu:
         mengurutkan lalu binary search, atau memakai tabel hash.
         Kalau kamu memilih tabel hash, ingatlah bahwa di beberapa juri
         (terutama Codeforces) tabel hash bawaan bisa dijadikan lambat
         oleh masukan yang dirancang khusus.

🎯 Learning Goals:
- [ ] Menerapkan semangat MITM di luar konteks bitmask
- [ ] Menghitung PASANGAN, bukan sekadar keberadaan
- [ ] Memilih antara sorting dan tabel hash secara sadar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: bangkitkan seluruh A[i] + B[j]

    // TODO: untuk tiap C[k] + D[l], cari berapa yang berpasangan

    return 0;
}
