/*
============================================================
📋 TUGAS 07: Menyeberangi Padang Pasir
============================================================
Source: Original
Difficulty: Medium
Topics: ternary geometris

PROBLEM:
Dari (0,0) ke (bx,by). Daerah y <= 0 berkecepatan v1, daerah y > 0
berkecepatan v2 (v2 <= v1). Bergerak lurus sampai titik (p,0) lalu lurus
ke tujuan. Cari waktu minimum, 9 desimal.

INPUT FORMAT:
- Satu baris: bx by v1 v2

OUTPUT FORMAT:
- Satu bilangan, 9 desimal

CONSTRAINTS:
- 1 <= by <= 10^4
- 1 <= v2 <= v1 <= 10^4

SAMPLE INPUT 1:
10 10 2 1

SAMPLE OUTPUT 1:
13.660254038
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Fungsi |p|/v1 + jarak/v2 cembung meski tidak diferensiabel di p = 0. Ternary search tidak butuh turunan.

    return 0;
}
