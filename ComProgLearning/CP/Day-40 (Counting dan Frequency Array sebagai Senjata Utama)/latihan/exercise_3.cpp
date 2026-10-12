/*
============================================================
🏋️ Exercise 3: Pasangan dengan Selisih Tepat K
============================================================
Day: 40 | Difficulty: Medium
Topic: Pola "hitung sebelum mendaftarkan diri"
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array berisi N bilangan bulat dan sebuah bilangan K yang
non-negatif. Hitung ada berapa PASANGAN INDEKS (i, j) dengan i < j
sehingga selisih absolut antara a[i] dan a[j] tepat sama dengan K.
Perhatikan bahwa K boleh bernilai 0. Kasus itu punya perlakuan khusus
yang harus kamu temukan sendiri.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan

📤 OUTPUT FORMAT:
- Satu bilangan: banyaknya pasangan

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= K <= 10^9
- 1 <= a[i] <= 10^9
- Jawaban bisa mencapai ~2 * 10^10

📎 SAMPLE INPUT 1:
5 2
1 5 3 4 2

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
4 0
7 7 7 1

📎 SAMPLE OUTPUT 2:
3

💡 HINT: Sapu dari kiri sambil menyimpan berapa kali setiap nilai sudah
         terlihat. Untuk setiap elemen baru, pasangkan ia dengan yang
         SUDAH lewat — bukan dengan seluruh array.
         Urutan dua operasi (menghitung dan mendaftarkan diri sendiri)
         menentukan kebenaran, bukan sekadar gaya. Sampel 2 akan
         menunjukkan mana urutan yang benar.

🎯 Learning Goals:
- [ ] Pola "hitung dulu, daftarkan kemudian"
- [ ] Menyadari kenapa K = 0 butuh perlakuan terpisah
- [ ] Ingat long long untuk hitungan pasangan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: map atau kompresi (nilai sampai 10^9)

    // TODO: untuk tiap x: hasil += hitungan(x-K) + hitungan(x+K), lalu daftarkan x

    // TODO: pisahkan kasus K == 0

    return 0;
}
