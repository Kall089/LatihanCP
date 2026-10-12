/*
============================================================
📋 TUGAS 13: Dynamic Set with Queries
============================================================
Source: Codeforces-style
Difficulty: Hard
Topics: set, lower_bound, insert, erase

PROBLEM:
Awalnya set kosong. Ada Q operasi:
- "1 x": Insert x ke set
- "2 x": Hapus x dari set (dijamin x ada)
- "3 x": Output elemen TERBESAR di set yang STRICTLY KURANG dari x.
          Jika tidak ada, output -1.

INPUT:
- Baris pertama: integer Q
- Q baris berikutnya: operasi (tipe dan x)

OUTPUT:
- Untuk setiap operasi tipe 3: output jawaban

CONSTRAINTS:
- 1 ≤ Q ≤ 200,000
- 1 ≤ x ≤ 1,000,000,000

SAMPLE INPUT:
7
1 5
1 3
1 8
3 6
2 5
3 6
3 3

SAMPLE OUTPUT:
5
3
-1

NOTE: After ops 1-3: set = {3, 5, 8}
      Query 3 6: largest < 6 = 5
      After erase 5: set = {3, 8}
      Query 3 6: largest < 6 = 3
      Query 3 3: largest < 3 = none → -1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Untuk "largest < x": gunakan lower_bound(x), mundur 1.
    //       Jika lower_bound(x) == begin(), maka tidak ada.

    return 0;
}
