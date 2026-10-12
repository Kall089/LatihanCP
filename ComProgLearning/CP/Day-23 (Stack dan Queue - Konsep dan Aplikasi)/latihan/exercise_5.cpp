/*
============================================================
🏋️ Exercise 5: Sliding Window Maximum (Monotonic Deque)
============================================================
Day: 5 | Difficulty: Medium-Hard
Topic: Deque, monotonic deque, sliding window
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array N bilangan dan integer K. Untuk setiap window
berukuran K, cetak elemen TERBESAR di window tersebut.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan K
- Baris kedua: N integer

📤 OUTPUT FORMAT:
- (N-K+1) integer: maximum per window

📏 CONSTRAINTS:
- 1 ≤ K ≤ N ≤ 200,000
- -1,000,000,000 ≤ a[i] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
8 3
1 3 -1 -3 5 3 6 7

📎 SAMPLE OUTPUT 1:
3 3 5 5 6 7

📎 SAMPLE INPUT 2:
5 2
5 4 3 2 1

📎 SAMPLE OUTPUT 2:
5 4 3 2

📎 SAMPLE INPUT 3:
5 5
1 2 3 4 5

📎 SAMPLE OUTPUT 3:
5

💡 HINT: Monotonic deque (decreasing). Simpan INDEX di deque.
         - Pop front jika out of window
         - Pop back jika value ≤ current (mereka tidak akan pernah jadi max)
         - Push current index
         - front = index of maximum

🎯 Learning Goals:
- [ ] Implementasi monotonic deque
- [ ] Pahami mengapa complexity O(N) (setiap elemen di-push & pop max 1x)
- [ ] Pattern sliding window maximum
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N, K, dan array

    // TODO: Implementasi monotonic deque:
    //       deque<int> dq; (simpan index)
    //       Untuk setiap i:
    //         - pop front jika dq.front() <= i - K
    //         - pop back jika arr[dq.back()] <= arr[i]
    //         - push_back(i)
    //         - jika i >= K-1: output arr[dq.front()]

    return 0;
}
