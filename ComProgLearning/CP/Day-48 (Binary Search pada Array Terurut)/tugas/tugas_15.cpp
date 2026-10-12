/*
============================================================
📋 Tugas 15: Special Array With X Elements (LeetCode 1608)
============================================================
Day: 48 | Difficulty: Medium
Topic: Binary Search & Counting

PROBLEM STATEMENT:
Diberikan array A tak negatif berukuran N.
Array A disebut 'spesial' jika terdapat suatu bilangan X sedemikian hingga
terdapat TEPAT X buah elemen di A yang nilainya LEBIH BESAR ATAU SAMA DENGAN X (A[i] ≥ X).
Perhatikan bahwa X TIDAK HARUS merupakan elemen dari A.

Jika A spesial, cetak nilai X tersebut. Jika tidak ada X yang memenuhi, cetak -1.

INPUT FORMAT:
- Baris 1: N
- Baris 2: N integer A[i]

OUTPUT FORMAT:
- Satu integer: nilai X jika ada, atau -1 jika tidak ada.

CONSTRAINTS:
- 1 ≤ N ≤ 1.000
- 0 ≤ A[i] ≤ 1.000

SAMPLE INPUT 1:
3
3 5 0

SAMPLE OUTPUT 1:
2

SAMPLE INPUT 2:
2
0 0

SAMPLE OUTPUT 2:
-1

PENJELASAN SAMPLE 1:
Jika X = 2: ada 2 elemen yang >= 2 (yaitu 3 dan 5). Syarat terpenuhi! Jawaban = 2.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: Sort A lalu cek setiap kemungkinan X dari 1 s/d N dengan Binary Search

    return 0;
}
