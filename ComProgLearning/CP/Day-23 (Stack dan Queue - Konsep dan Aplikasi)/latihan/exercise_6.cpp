/*
============================================================
🏋️ Exercise 6: Next Greater Element (Monotonic Stack)
============================================================
Day: 5 | Difficulty: Hard
Topic: Monotonic Stack
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array N bilangan. Untuk setiap elemen, cari elemen
PERTAMA di SEBELAH KANAN yang nilainya LEBIH BESAR.
Jika tidak ada, outputkan -1.

📥 INPUT FORMAT:
- Baris pertama: integer N
- Baris kedua: N integer

📤 OUTPUT FORMAT:
- N integer: next greater element untuk setiap posisi

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
5
4 5 2 10 8

📎 SAMPLE OUTPUT 1:
5 10 10 -1 -1

📎 SAMPLE INPUT 2:
4
3 2 1 4

📎 SAMPLE OUTPUT 2:
4 4 4 -1

📎 SAMPLE INPUT 3:
3
5 4 3

📎 SAMPLE OUTPUT 3:
-1 -1 -1

💡 HINT: Iterasi dari kiri ke kanan. Stack simpan INDEX yang belum
         punya next greater. Saat ketemu elemen lebih besar dari top,
         pop dan assign result[top] = elemen saat ini.

🎯 Learning Goals:
- [ ] Monotonic stack pattern
- [ ] Pahami: setiap elemen di-push dan di-pop PALING BANYAK 1x → O(N)
- [ ] Next greater / next smaller variants
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan array

    // TODO: Inisialisasi result[i] = -1 untuk semua i

    // TODO: Stack simpan index
    //       Untuk setiap i:
    //         while stack not empty AND arr[stack.top()] < arr[i]:
    //           result[stack.top()] = arr[i]
    //           stack.pop()
    //         stack.push(i)

    // TODO: Output result

    return 0;
}
