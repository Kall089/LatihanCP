/*
============================================================
🏋️ Exercise 3: Hujan Meteor
============================================================
Day: 53 | Difficulty: Medium
Topic: Parallel binary search dengan rentang melingkar
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah planet dibagi menjadi M sektor yang tersusun MELINGKAR (setelah
sektor M kembali ke sektor 1).
Ada N negara. Setiap sektor dimiliki oleh tepat satu negara, dan sebuah
negara bisa memiliki beberapa sektor yang tidak berdampingan.
Negara ke-i punya target pengumpulan sebesar P[i] unit meteor.
Terjadi K hujan meteor. Hujan ke-t menjatuhkan a[t] unit meteor ke SETIAP
sektor pada rentang melingkar [l[t], r[t]]. Jika l[t] > r[t], rentangnya
membungkus melewati sektor M kembali ke sektor 1.
Untuk setiap negara, tentukan setelah hujan keberapa total meteor yang
terkumpul di seluruh sektornya mencapai targetnya. Cetak "NIE" kalau
targetnya tidak pernah tercapai.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: M bilangan, pemilik setiap sektor
- Baris ketiga: N bilangan P[i]
- Baris keempat: K
- K baris berikutnya: l[t], r[t], a[t]

📤 OUTPUT FORMAT:
- N baris, masing-masing satu bilangan atau "NIE"

📏 CONSTRAINTS:
- 1 <= N, M, K <= 3 * 10^5
- 1 <= P[i] <= 10^9
- 1 <= a[t] <= 10^9

📎 SAMPLE INPUT 1:
3 5
1 3 2 1 3
10 5 7
3
4 2 4
1 3 1
3 5 2

📎 SAMPLE OUTPUT 1:
3
NIE
1

💡 HINT: Ini adalah bentuk klasik dari soal parallel binary search.
         Dua hal yang membedakannya dari Exercise 2:
         Pertama, rentangnya bisa MEMBUNGKUS. Pecah rentang membungkus
         [l, r] dengan l > r menjadi dua rentang biasa: [l, M] dan [1, r].
         Kedua, satu pertanyaan (negara) memeriksa BEBERAPA sektor
         sekaligus, bukan satu. Perhatikan bahwa total seluruh sektor milik
         semua negara adalah M — jadi menjawab SELURUH pertanyaan dalam
         satu putaran tetap O(M log M), bukan O(N × M).
         Peringatan: saat menjumlahkan meteor di seluruh sektor sebuah
         negara, totalnya bisa sangat besar. Hentikan penjumlahan segera
         setelah target tercapai.

🎯 Learning Goals:
- [ ] Menangani rentang melingkar dengan memecahnya menjadi dua
- [ ] Menyadari bahwa biaya menjawab dijamin oleh TOTAL ukuran data
- [ ] Mencegah overflow dengan menghentikan akumulasi lebih awal
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kelompokkan sektor berdasarkan pemiliknya

    // TODO: kerangka parallel binary search

    // TODO: rentang membungkus dipecah menjadi [l, M] dan [1, r]

    return 0;
}
