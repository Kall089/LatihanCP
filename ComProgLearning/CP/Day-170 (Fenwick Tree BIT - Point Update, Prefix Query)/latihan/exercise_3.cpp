/*
============================================================
🏋️ Exercise 3: Berapa yang Lebih Kecil di Kanan
============================================================
Day: 170 | Difficulty: Medium
Topic: BIT per posisi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat. Untuk SETIAP posisi i, hitung
berapa banyak elemen di sebelah KANAN posisi itu yang nilainya LEBIH KECIL
dari a[i].
Cetak N bilangan.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- -10^9 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
5 2 6 1

📎 SAMPLE OUTPUT 1:
2 1 1 0

📎 SAMPLE INPUT 2:
3
7 7 7

📎 SAMPLE OUTPUT 2:
0 0 0

💡 HINT: Ini adalah Exercise 2 yang "dipecah per posisi" — alih-alih
         menjumlahkan seluruh kontribusi menjadi satu angka, kamu menyimpan
         kontribusi masing-masing posisi.
         Struktur dan urutan operasinya sama persis; yang berubah hanya apa
         yang kamu lakukan dengan hasil query.
         Perhatikan sampel 2 dengan saksama: seluruh elemen bernilai sama,
         dan jawabannya nol semua. Pastikan query-mu menghitung yang
         BENAR-BENAR lebih kecil, bukan yang lebih kecil atau sama.
         Perbedaan satu angka pada batas query menentukan benar atau salah.

🎯 Learning Goals:
- [ ] Menyimpan hasil per posisi, bukan agregat
- [ ] Berhati-hati pada batas query (lebih kecil vs lebih kecil-sama)
- [ ] Menangani nilai kembar dengan benar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: sama seperti Exercise 2, tetapi simpan hasil tiap posisi

    // TODO: perhatikan batas query untuk nilai kembar

    return 0;
}
