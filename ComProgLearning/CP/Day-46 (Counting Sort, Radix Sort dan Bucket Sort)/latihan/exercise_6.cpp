/*
============================================================
🏋️ Exercise 6: Urutan Relatif Kustom
============================================================
Day: 46 | Difficulty: Hard (Contest-level)
Topic: Counting sort dengan urutan yang ditentukan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array A berisi N bilangan dan array B berisi M bilangan BERBEDA.
Setiap elemen B dijamin muncul setidaknya sekali di dalam A.
Susun ulang A sehingga:
- Elemen yang muncul di B diletakkan lebih dulu, mengikuti urutan
  kemunculannya di dalam B.
- Elemen yang TIDAK muncul di B diletakkan setelahnya, terurut menaik.
Cetak array A hasil penyusunan.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N bilangan array A
- Baris ketiga: M bilangan array B

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan

📏 CONSTRAINTS:
- 1 <= M <= N <= 10^6
- 0 <= nilai <= 1000

📎 SAMPLE INPUT 1:
11 5
2 3 1 3 2 4 6 7 9 2 19
5
2 1 4 3 9

📎 SAMPLE OUTPUT 1:
2 2 2 1 4 3 3 9 6 7 19

📎 SAMPLE INPUT 2:
3 1
5 5 5
1
5

📎 SAMPLE OUTPUT 2:
5 5 5

💡 HINT: Karena nilainya paling besar 1000, array frekuensi menyelesaikan
         hampir seluruh soal ini.
         Cetak dulu nilai-nilai yang ada di B mengikuti urutan B, masing-
         masing sebanyak frekuensinya di A. Setelah itu, sapu seluruh nilai
         dari kecil ke besar dan cetak yang frekuensinya masih tersisa.
         Perhatikan bagaimana kamu menandai nilai yang sudah tercetak agar
         tidak tercetak dua kali.

🎯 Learning Goals:
- [ ] Memakai array frekuensi untuk urutan yang bukan menaik
- [ ] Menyadari bahwa "mengurutkan" kadang hanya berarti "mencetak dalam
      urutan tertentu"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung frekuensi seluruh nilai di A

    // TODO: cetak sesuai urutan B, nolkan frekuensinya setelah tercetak

    // TODO: cetak sisanya dari kecil ke besar

    return 0;
}
