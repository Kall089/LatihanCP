/*
============================================================
📋 TUGAS 06: Jarak Edit Levenshtein Dua Baris
============================================================
Source: Classic DP / Edit Distance Memory Optimization
Difficulty: Medium-Hard
Topics: 2-Row DP, Space Optimization

PROBLEM:
Diberikan dua string S1 dan S2.
Tentukan jarak Levenshtein minimum untuk mengubah S1 menjadi S2 dengan operasi:
- Sisip (Insert), biaya 1
- Hapus (Delete), biaya 1
- Ganti (Replace), biaya 1
- Pertahankan jika sama, biaya 0
Gunakan teknik 2-Row Rolling Array dengan menukar dimensi agar memori O(min(|S1|, |S2|)).

INPUT FORMAT:
Baris pertama berisi string S1.
Baris kedua berisi string S2.

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: jarak edit minimum.

CONSTRAINTS:
0 <= |S1|, |S2| <= 4.000

SAMPLE INPUT 1:
sunday
saturday

SAMPLE OUTPUT 1:
3
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2;
    if (!(cin >> s1 >> s2)) return 0;

    // TODO: Selesaikan Edit Distance dengan 2-baris prev dan cur

    return 0;
}
