/*
============================================================
📋 TUGAS 13: Rekonstruksi Pembagian Kata dalam Kamus (Word Break II)
============================================================
Source: LeetCode 140 (Word Break II)
Difficulty: Hard
Topics: 1D DP on Strings, Parent Array, Sentence Reconstruction

PROBLEM:
Diberikan sebuah string S dan kamus yang berisi M kata unik dict[0], ..., dict[M-1].
Tentukan apakah string S dapat dipecah menjadi rangkaian kata-kata yang semuanya ada di dalam kamus.
Jika bisa, cetak kalimat hasil pemecahan dengan setiap kata dipisahkan oleh satu SPASI.
Jika ada beberapa kemungkinan kalimat valid, cetak salah satu yang valid.
Jika tidak bisa dipecah sama sekali, cetak teks `TIDAK BISA`.

INPUT FORMAT:
Baris pertama berisi string S.
Baris kedua berisi bilangan bulat M.
M baris berikutnya masing-masing berisi satu kata dalam kamus.

OUTPUT FORMAT:
Satu baris berisi kalimat hasil pemecahan dengan spasi, atau `TIDAK BISA`.

CONSTRAINTS:
1 <= |S| <= 300
1 <= M <= 1.000
1 <= panjang kata <= 50

SAMPLE INPUT 1:
leetcode
2
leet
code

SAMPLE OUTPUT 1:
leet code

SAMPLE INPUT 2:
applepenapple
2
apple
pen

SAMPLE OUTPUT 2:
apple pen apple

SAMPLE INPUT 3:
catsandog
5
cats
dog
sand
and
cat

SAMPLE OUTPUT 3:
TIDAK BISA
============================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int m;
    if (!(cin >> m)) return 0;

    unordered_set<string> dict;
    for (int i = 0; i < m; i++) {
        string w;
        cin >> w;
        dict.insert(w);
    }

    // TODO: Selesaikan Word Break dan rekonstruksi kalimat

    return 0;
}
