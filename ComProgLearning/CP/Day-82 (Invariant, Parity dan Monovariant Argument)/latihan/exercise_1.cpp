/*
============================================================
🏋️ Exercise 1: Bilangan Terakhir di Papan
============================================================
Day: 82 | Difficulty: Easy
Topic: Invarian paritas jumlah
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N bilangan bulat positif di papan. Berulang kali kamu memilih DUA
bilangan x dan y, menghapus keduanya, lalu menuliskan nilai mutlak dari
x dikurangi y.
Proses berhenti ketika tersisa tepat satu bilangan.
Tentukan apakah bilangan terakhir itu GENAP atau GANJIL. Cetak "GENAP" atau
"GANJIL".

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- "GENAP" atau "GANJIL"

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
3 5 7 11

📎 SAMPLE OUTPUT 1:
GENAP

📎 SAMPLE INPUT 2:
3
1 2 4

📎 SAMPLE OUTPUT 2:
GANJIL

💡 HINT: Perhatikan bahwa soal tidak menyebutkan urutan operasi sama sekali,
         dan tetap menuntut jawaban yang pasti. Itu petunjuk sangat kuat
         bahwa jawabannya TIDAK BERGANTUNG pada urutan — dengan kata lain,
         ada sesuatu yang tidak berubah.
         Cari besaran yang nilainya tetap setelah setiap operasi. Untuk
         menemukannya, coba jalankan beberapa operasi dengan tangan pada
         sampel 1 dan catat: jumlah seluruh bilangan, jumlahnya modulo 2,
         banyaknya bilangan ganjil, dan XOR seluruhnya.
         Salah satu di antaranya tidak akan pernah berubah.
         Setelah menemukannya, buktikan secara aljabar. Petunjuk: bandingkan
         paritas dari nilai mutlak x dikurangi y dengan paritas dari x
         ditambah y. Apa hubungannya?
         Kasus tepi: kalau N sama dengan 1, tidak ada operasi sama sekali.
         Apakah kodemu tetap benar?

🎯 Learning Goals:
- [ ] Mengenali petunjuk "jawaban tidak bergantung urutan"
- [ ] Menemukan invarian dengan mencoba beberapa kandidat
- [ ] Membuktikan invarian secara aljabar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: temukan besaran yang tidak berubah

    return 0;
}
