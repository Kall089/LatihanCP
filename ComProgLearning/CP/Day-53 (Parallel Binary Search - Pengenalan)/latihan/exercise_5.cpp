/*
============================================================
🏋️ Exercise 5: Nilai Terkecil ke-K pada Rentang
============================================================
Day: 53 | Difficulty: Hard
Topic: Parallel binary search atas NILAI (bukan waktu)
Time Limit: 3 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan Q pertanyaan. Pertanyaan ke-i
berisi tiga bilangan l, r, dan k, dan kamu harus menjawab nilai TERKECIL
KE-K di antara elemen a[l], a[l+1], ..., a[r].
Perhatikan bahwa di sini yang di-binary-search bukan WAKTU, melainkan NILAI
jawabannya. Kerangkanya tetap sama persis.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: l, r, dan k

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 10^5
- 1 <= k <= r - l + 1 <= N
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
5 2
1 5 2 6 3
1 3 2
2 5 3

📎 SAMPLE OUTPUT 1:
2
5

💡 HINT: Predikatnya: "apakah nilai terkecil ke-k pada [l, r] tidak melebihi
         x?" Itu sama dengan bertanya "apakah ada setidaknya k elemen pada
         [l, r] yang nilainya <= x?" — dan itu MONOTON terhadap x.
         Untuk menghitungnya, urutkan seluruh elemen berdasarkan NILAI,
         lalu dalam satu sapuan tambahkan posisi elemen ke sebuah struktur
         yang bisa menghitung "berapa posisi yang sudah ditambahkan berada
         di dalam rentang [l, r]".
         Karena nilainya bisa mencapai 10^9, kompres dulu (Day 38).
         Perhatikan bahwa "waktu" dalam kerangka parallel binary search di
         sini berarti "sudah berapa nilai terkecil yang dimasukkan".

🎯 Learning Goals:
- [ ] Menerapkan kerangka pada ruang NILAI, bukan waktu
- [ ] Menggabungkan dengan kompresi koordinat dan BIT
- [ ] Menerjemahkan "terkecil ke-k" menjadi predikat penghitungan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kompres nilai, urutkan elemen berdasarkan nilai

    // TODO: parallel binary search atas indeks nilai terkompresi

    // TODO: BIT menghitung berapa posisi yang aktif di dalam [l, r]

    return 0;
}
