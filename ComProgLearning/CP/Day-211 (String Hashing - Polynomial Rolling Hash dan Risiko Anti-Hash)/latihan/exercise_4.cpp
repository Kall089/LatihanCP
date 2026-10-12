/*
============================================================
🏋️ Exercise 4: Menghitung Substring Berbeda
============================================================
Day: 33 | Difficulty: Medium-Hard
Topic: Hash + set
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan sebuah string S. Hitung ada berapa substring BERBEDA yang bisa
diambil darinya. Dua substring dianggap sama kalau isinya persis sama,
walaupun diambil dari posisi yang berbeda.

Contoh: dari "ababa" ada 9 substring berbeda, yaitu
a, b, ab, ba, aba, bab, abab, baba, ababa.

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya substring berbeda.

📏 CONSTRAINTS:
- 1 <= |S| <= 2000
- S hanya berisi huruf kecil 'a'-'z'
- Batas kecil karena solusi yang diharapkan O(n^2)

📎 SAMPLE INPUT 1:
ababa

📎 SAMPLE OUTPUT 1:
9

📎 SAMPLE INPUT 2:
aaa

📎 SAMPLE OUTPUT 2:
3

📎 SAMPLE INPUT 3:
abc

📎 SAMPLE OUTPUT 3:
6

💡 HINT:
- Ada O(n^2) substring; kumpulkan hash masing-masing ke dalam sebuah set.
- Ukuran akhir set itulah jawabannya.
- PENTING: hash harus DINORMALKAN dulu sebelum dimasukkan ke set, karena
  get(l, r) masih berbobot p^l. Tanpa normalisasi, dua substring identik
  di posisi berbeda akan dianggap berbeda.
- Cara menormalkan: kalikan dengan p[n - l].

🎯 Learning Goals:
- [ ] Menyadari perlunya normalisasi hash sebelum masuk set
- [ ] Menghitung substring berbeda dalam O(n^2 log n)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun prefix hash

    // TODO: Untuk tiap pasangan (l, r), masukkan hash TERNORMALISASI ke set

    // TODO: Cetak ukuran set

    return 0;
}
