/*
============================================================
📋 TUGAS 06: Circular Deque
============================================================
Source: Original
Difficulty: Medium
Topics: deque, circular buffer

PROBLEM:
Implementasikan Circular Deque dengan kapasitas tetap k.
Operasi: insertFront, insertLast, deleteFront, deleteLast, getFront, getRear,
isEmpty, isFull. Jika operasi insert/delete gagal, cetak "false".

INPUT FORMAT:
- Baris 1: integer k dan q
- q baris: nama operasi dan nilai (jika insert)

OUTPUT FORMAT:
- Untuk get/is: cetak nilai atau true/false

CONSTRAINTS:
- 1 ≤ k ≤ 1000, 1 ≤ q ≤ 10^4

SAMPLE INPUT 1:
3 8
INSERT_LAST 1
INSERT_LAST 2
INSERT_FRONT 3
GET_FRONT
GET_REAR
IS_FULL
INSERT_LAST 4
INSERT_FRONT 5

SAMPLE OUTPUT 1:
3
2
true
false
false

SAMPLE INPUT 2:
2 4
INSERT_FRONT 1
INSERT_LAST 2
IS_FULL
INSERT_FRONT 3

SAMPLE OUTPUT 2:
true
false

NOTE: Gunakan deque<int> dengan cek size < k sebelum insert.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
