/*
============================================================
🏋️ Exercise 6: Nilai yang Muncul Tepat K Kali
============================================================
Day: 40 | Difficulty: Hard (Contest-level)
Topic: Frekuensi dari frekuensi + banyak test case
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan T kasus uji. Setiap kasus berisi sebuah array dan sebuah
bilangan K, dan kamu harus menjawab: ADA BERAPA NILAI BERBEDA yang muncul
TEPAT K kali di dalam array itu.
Sebagai contoh, pada array [1,1,2,2,3] dengan K = 2, jawabannya 2 karena
nilai 1 dan nilai 2 masing-masing muncul tepat dua kali.
Perhatikan bahwa jumlah kasus uji bisa sangat banyak. Membersihkan seluruh
array frekuensi yang berukuran 10^6 pada setiap kasus akan menghasilkan
10^11 operasi dan pasti TLE — kamu harus membersihkannya dengan cara lain.

📥 INPUT FORMAT:
- Baris pertama: T
- Setiap kasus: baris berisi N dan K, lalu baris berisi N bilangan

📤 OUTPUT FORMAT:
- T baris berisi bilangan

📏 CONSTRAINTS:
- 1 <= T <= 10^5
- 1 <= N, dan total seluruh N <= 10^6
- 1 <= a[i] <= 10^6
- 1 <= K <= N

📎 SAMPLE INPUT 1:
2
5 2
1 1 2 2 3
4 1
7 7 7 7

📎 SAMPLE OUTPUT 1:
2
0

💡 HINT: Ada dua lapis penghitungan di sini: pertama hitung berapa kali
         tiap nilai muncul, lalu hitung berapa nilai yang punya hitungan
         tertentu. Pola dua lapis ini sering terlewat oleh pemula.
         Untuk pembersihan, perhatikan bahwa kamu hanya menyentuh paling
         banyak N slot per kasus — jadi kamu hanya perlu membersihkan
         slot-slot itu saja, bukan seluruh array.

🎯 Learning Goals:
- [ ] Menghitung frekuensi dari frekuensi
- [ ] Membersihkan array frekuensi dalam O(n), bukan O(domain)
- [ ] Menyadari kenapa memset di dalam loop test case berbahaya
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: array global

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: untuk tiap kasus: hitung, hitung lagi, jawab

    // TODO: bersihkan HANYA slot yang tersentuh

    return 0;
}
