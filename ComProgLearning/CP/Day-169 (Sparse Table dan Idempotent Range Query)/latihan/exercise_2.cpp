/*
============================================================
🏋️ Exercise 2: Kenapa Sum Tidak Bisa
============================================================
Day: 169 | Difficulty: Easy
Topic: Idempoten versus punya invers
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan dan Q pertanyaan rentang [a, b]
(1-based, inklusif). Untuk setiap pertanyaan, cetak TIGA nilai:
- minimum pada rentang itu,
- maksimum pada rentang itu, dan
- jumlah seluruh elemen pada rentang itu.
Ketiganya harus dijawab dalam O(1) per pertanyaan setelah preprocessing.
Perhatikan bahwa tidak semua dari ketiganya bisa diselesaikan dengan
struktur yang sama — salah satunya membutuhkan pendekatan yang berbeda.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan
- Q baris berikutnya: a dan b

📤 OUTPUT FORMAT:
- Q baris, masing-masing tiga bilangan dipisah spasi

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- -10^9 <= nilai <= 10^9

📎 SAMPLE INPUT 1:
5 3
1 2 3 4 5
1 5
2 4
3 3

📎 SAMPLE OUTPUT 1:
1 5 15
2 4 9
3 3 3

💡 HINT: Untuk minimum dan maksimum, struktur blok pangkat dua bekerja
         karena kedua blok yang dipakai boleh TUMPANG TINDIH tanpa merusak
         jawaban.
         Coba pikirkan apa yang terjadi kalau kamu memaksakan struktur yang
         sama untuk penjumlahan: pada rentang sepanjang 5 dengan blok
         sepanjang 4, elemen mana yang akan terhitung dua kali, dan seberapa
         besar kesalahannya?
         Untuk penjumlahan, ada teknik jauh lebih sederhana yang sudah kamu
         pelajari jauh sebelum ini. Sifat apa yang dimiliki penjumlahan
         tetapi tidak dimiliki minimum?
         Perhatikan tipe data untuk jumlahnya.

🎯 Learning Goals:
- [ ] Memahami arti idempoten secara konkret
- [ ] Membedakan "punya invers" dan "idempoten"
- [ ] Memilih struktur yang tepat per jenis operasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: dua sparse table (min dan max)

    // TODO: untuk jumlah, pakai teknik yang BERBEDA

    return 0;
}
