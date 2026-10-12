/*
============================================================
🏋️ Exercise 5: Derajat Palindrom
============================================================
Day: 216 | Difficulty: Hard
Topic: Manacher/awalan palindromik + DP rekursif
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Definisikan "derajat palindrom" k(S) sebagai berikut:
- k(S) = 0 jika S BUKAN palindrom.
- k(S) = 1 + k(A) jika S adalah palindrom, di mana A adalah AWALAN dari S
  yang panjangnya tepat setengah dari |S| (dibulatkan ke bawah).
Sebagai contoh: k("") = 0, k("a") = 1, k("aa") = 2, k("aaaa") = 3,
k("abaaba") = 3, k("abacaba") = 2.
Diberikan string S, hitung JUMLAH k(P) untuk seluruh awalan P dari S
(termasuk S sendiri, tidak termasuk awalan kosong).

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Satu bilangan: total derajat seluruh awalan

📏 CONSTRAINTS:
- 1 <= |S| <= 5 * 10^6
- Jawaban muat di long long

📎 SAMPLE INPUT 1:
a2A

📎 SAMPLE OUTPUT 1:
1

📎 SAMPLE INPUT 2:
abacaba

📎 SAMPLE OUTPUT 2:
6

💡 HINT: Kamu butuh, untuk setiap panjang i, jawaban dari "apakah awalan
         sepanjang i merupakan palindrom". Manacher memberi itu: cari p[c]
         yang menyentuh ujung KIRI. Setelah itu k[i] = k[i/2] + 1 kalau
         awalan i palindrom, dan 0 kalau bukan — DP satu arah.
         Catatan: input bisa memuat huruf besar dan angka, jadi jangan
         berasumsi hanya 'a'..'z'.

🎯 Learning Goals:
- [ ] Menandai SEMUA awalan palindromik, bukan hanya yang terpanjang
- [ ] Menggabungkan Manacher dengan DP rekurens sederhana
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: Manacher; hati-hati memilih separator karena alfabet luas

    // TODO: isPrefPal[i] = apakah awalan sepanjang i palindrom

    // TODO: k[i] = isPrefPal[i] ? k[i/2] + 1 : 0, jumlahkan semua k[i]

    return 0;
}
