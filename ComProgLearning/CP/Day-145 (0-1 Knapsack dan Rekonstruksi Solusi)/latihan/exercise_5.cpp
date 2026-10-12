/*
============================================================
🏋️ Exercise 5: Kapasitas Raksasa
============================================================
Day: 145 | Difficulty: Hard
Topic: DP atas nilai (membalik peran indeks dan isi)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N barang dengan berat w[i] dan nilai v[i], serta kapasitas tas W.
Maksimalkan total nilai tanpa melebihi kapasitas.
Perhatikan batas dengan saksama: kapasitas dan berat masing-masing barang
bisa mencapai 10^9, sehingga tabel yang diindeks oleh kapasitas MUSTAHIL
dibuat. Tetapi ada besaran lain di soal ini yang jauh lebih kecil.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total nilai maksimum

📏 CONSTRAINTS:
- 1 <= N <= 100
- 1 <= W <= 10^9
- 1 <= w[i] <= 10^9
- 1 <= v[i] <= 1000

📎 SAMPLE INPUT 1:
3 8
3 30
4 50
5 60

📎 SAMPLE OUTPUT 1:
90

📎 SAMPLE INPUT 2:
1 1000000000
1000000000 1

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Perhatikan bahwa v[i] paling besar 1000 dan N paling besar 100,
         sehingga total nilai seluruh barang paling besar 10^5 — jauh lebih
         kecil daripada kapasitas.
         Kalau kamu tidak bisa mengindeks tabel dengan kapasitas, apa lagi
         yang bisa dijadikan indeks? Dan kalau nilainya menjadi indeks, apa
         yang harus disimpan di dalam selnya?
         Setelah tabelnya terisi, bagaimana kamu membaca jawabannya?
         Pikirkan nilai TERBESAR yang masih bisa dicapai dalam kapasitas W.
         Peringatan: sel yang belum terjangkau harus dibedakan dari sel yang
         berbobot nol. Pikirkan nilai penanda apa yang aman dipakai, dan
         apa yang terjadi kalau kamu menambahkan sesuatu ke penanda itu.

🎯 Learning Goals:
- [ ] Membalik peran indeks dan isi pada DP
- [ ] Memilih varian berdasarkan batas soal, bukan kebiasaan
- [ ] Menangani nilai penanda tak-terjangkau dengan aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung total nilai seluruh barang

    // TODO: dp[val] = berat minimum untuk mencapai nilai val

    // TODO: cari val terbesar dengan dp[val] <= W

    return 0;
}
