/*
============================================================
🏋️ Exercise 3: Ruang Rapat Minimum
============================================================
Day: 72 | Difficulty: Medium
Topic: Sapuan event / heap
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N rapat yang SEMUANYA harus terlaksana. Rapat ke-i berlangsung dari
menit s[i] sampai menit e[i]. Sebuah ruangan hanya bisa dipakai satu rapat
pada satu waktu, tetapi rapat baru boleh mulai tepat saat rapat sebelumnya
di ruangan itu selesai.
Cari JUMLAH RUANGAN MINIMUM yang dibutuhkan.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: s[i] dan e[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah ruangan minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= s[i] < e[i] <= 10^9

📎 SAMPLE INPUT 1:
3
0 30
5 10
15 20

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
2
7 10
2 4

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Bacalah kata "SEMUANYA harus terlaksana" dengan serius. Tidak ada
         rapat yang dibuang, sehingga ini BUKAN soal Exercise 1 sama sekali.
         Bayangkan kamu berjalan di sepanjang sumbu waktu dan menghitung
         berapa rapat yang sedang berlangsung pada tiap saat. Berapa nilai
         terbesar yang pernah kamu lihat, dan apa artinya bagi jumlah
         ruangan?
         Kalau kamu memilih pendekatan berbasis event, pikirkan hal ini:
         pada waktu yang sama persis, mana yang harus diproses lebih dulu,
         event MULAI atau event SELESAI? Jawabannya menentukan benar atau
         salah.
         Ada juga pendekatan kedua memakai struktur data yang selalu
         memberimu ruangan yang paling cepat bebas. Coba tulis keduanya.

🎯 Learning Goals:
- [ ] Membedakan "buang sebagian" dan "jadwalkan semua"
- [ ] Menguasai teknik sapuan event
- [ ] Menyadari pentingnya urutan pemrosesan pada waktu yang sama
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: ubah tiap rapat menjadi dua event

    // TODO: urutkan; perhatikan urutan pada waktu yang sama

    // TODO: sapu sambil melacak nilai maksimum

    return 0;
}
