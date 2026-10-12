/*
============================================================
🏋️ Exercise 6: Banyak Query Target
============================================================
Day: 146 | Difficulty: Hard
Topic: Bitset subset sum
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan non-negatif dan Q query.
Untuk setiap query target T, jawab apakah ada subset dari bilangan-bilangan
tersebut yang jumlahnya tepat T. Array bilangan sama untuk semua query, jadi
kamu harus melakukan preprocessing sekali, lalu menjawab query dengan cepat.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan A[i]
- Baris ketiga: Q bilangan target T[j]

📤 OUTPUT FORMAT:
- Untuk setiap query, cetak "YES" jika target bisa dibentuk, selain itu "NO"
- Cetak satu jawaban per baris

📏 CONSTRAINTS:
- 1 <= N <= 200
- 1 <= Q <= 200000
- 0 <= A[i] <= 1000
- 0 <= T[j] <= 200000
- Total seluruh A[i] <= 200000

📎 SAMPLE INPUT 1:
5 5
2 3 7 8 10
0 5 11 14 30

📎 SAMPLE OUTPUT 1:
YES
YES
YES
NO
YES

📎 SAMPLE INPUT 2:
3 4
4 4 4
4 8 12 16

📎 SAMPLE OUTPUT 2:
YES
YES
YES
NO

💡 HINT: Gunakan bitset. Jika bs[s] menyala, sum s bisa dibentuk.
         Untuk elemen x, operasi bs |= (bs << x) menambahkan pilihan ambil x.

🎯 Learning Goals:
- [ ] Melakukan preprocessing reachable sum satu kali
- [ ] Menjawab query subset sum dalam O(1)
- [ ] Memahami arti bs |= bs << x
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N, Q, dan array A

    // TODO: Precompute reachable sum dengan bitset<200001>

    // TODO: Untuk setiap query, cek bit target dan cetak YES/NO

    return 0;
}
