/*
============================================================
🏋️ Exercise 4: K-th Largest Element (Priority Queue)
============================================================
Day: 5 | Difficulty: Medium
Topic: Priority Queue (min heap), streaming K-th largest
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N bilangan secara streaming (satu per satu).
Setelah setiap bilangan ke-i masuk (mulai i = K), cetak elemen
TERBESAR KE-K dari semua bilangan yang sudah masuk.

Untuk i < K, cetak -1.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan K
- Baris kedua: N integer (stream)

📤 OUTPUT FORMAT:
- N integer: K-th largest setelah setiap insert, atau -1

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- 1 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
7 3
5 2 8 1 9 3 7

📎 SAMPLE OUTPUT 1:
-1 -1 2 2 5 5 7

📎 SAMPLE INPUT 2:
5 1
3 1 4 1 5

📎 SAMPLE OUTPUT 2:
3 3 4 4 5

💡 HINT: Maintain min-heap berukuran K. top() = K-th largest.
         Jika heap size > K, pop (buang yang terkecil).

🎯 Learning Goals:
- [ ] Min heap untuk maintain K elemen terbesar
- [ ] top() min heap ukuran K = K-th largest
- [ ] Streaming processing
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int u, v;
    cin >> u >> v;

    return 0;
}
