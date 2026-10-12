/*
============================================================
🏋️ Exercise 1: Kapan Tabungan Mencapai Target
============================================================
Day: 53 | Difficulty: Easy
Topic: Varian satu sapuan (periksa ini SEBELUM parallel binary search)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Setiap hari selama N hari, kamu menabung sejumlah uang: pada hari ke-t kamu
menabung a[t] rupiah (a[t] selalu positif).
Ada Q pertanyaan. Pertanyaan ke-i berisi sebuah target T[i], dan kamu harus
menjawab pada HARI KEBERAPA total tabunganmu pertama kali mencapai
setidaknya T[i]. Jika sampai hari ke-N total tabungan belum mencapai target
itu, cetak -1.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan a[t]
- Baris ketiga: Q bilangan T[i]

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, Q <= 5 * 10^5
- 1 <= a[t] <= 10^9
- 1 <= T[i] <= 10^18

📎 SAMPLE INPUT 1:
5 3
1 2 3 4 5
3
10
100

📎 SAMPLE OUTPUT 1:
2
4
-1

💡 HINT: Soal ini SENGAJA ditaruh sebagai latihan pertama untuk menunjukkan
         bahwa kamu tidak selalu butuh parallel binary search.
         Perhatikan bahwa seluruh pertanyaan memeriksa BESARAN YANG SAMA
         (total tabungan), hanya ambangnya yang berbeda. Kalau kamu
         mengurutkan pertanyaan berdasarkan ambangnya, apa yang terjadi
         saat kamu menyapu hari demi hari?
         Jawabannya: kamu bisa menjawab SEMUA pertanyaan dalam SATU sapuan,
         tanpa binary search sama sekali.
         Jangan lupa memulihkan urutan keluaran sesuai urutan pertanyaan
         pada input.

🎯 Learning Goals:
- [ ] Mengenali kapan satu sapuan sudah cukup
- [ ] Memakai two pointers atas pertanyaan yang sudah diurutkan
- [ ] Menjaga id asli agar keluaran tetap urut
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca query BESERTA id aslinya, lalu urutkan berdasarkan target

    // TODO: satu sapuan; majukan penunjuk query selama targetnya tercapai

    // TODO: cetak sesuai urutan id asli

    return 0;
}
