/*
============================================================
📋 TUGAS 11: Cari Pola Tanpa Fungsi Terpisah
============================================================
Source: Original
Difficulty: Hard
Topics: Trik penggabungan

PROBLEM:
Selesaikan pencarian pola HANYA dengan membangun satu tabel pi, tanpa
menulis loop pencarian terpisah.
Petunjuk: bangun pi dari P + "#" + T, lalu cari posisi dengan nilai pi == |P|.
Pemisah "#" wajib karakter yang tidak muncul di kedua string.

INPUT FORMAT:
- Baris pertama: string T
- Baris kedua: string P

OUTPUT FORMAT:
- Satu baris: posisi kemunculan (1-based), atau -1.

CONSTRAINTS:
- 1 <= |P| <= |T| <= 10^5

SAMPLE INPUT 1:
ababa
aba

SAMPLE OUTPUT 1:
1 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Ingat inti KMP: j = pi[j - 1], dan indeks teks tidak pernah mundur

    return 0;
}
