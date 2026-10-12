/*
============================================================
📋 TUGAS 10: Jaringan Listrik
============================================================
Source: Original
Difficulty: Hard
Topics: PBS + DSU berbobot

PROBLEM:
N gardu listrik, M kabel dipasang satu per hari; kabel ke-t punya kapasitas
c[t]. Untuk tiap query (u, v, K), cari hari keberapa u dan v terhubung
melalui jalur yang SETIAP kabelnya berkapasitas setidaknya K.

INPUT FORMAT:
- Baris pertama: N, M, Q
- M baris: u v c
- Q baris: u v K

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= N, M, Q <= 10^5

SAMPLE INPUT 1:
3 3 1
1 2 5
2 3 3
1 3 7
1 3 5

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Perhatikan bahwa syarat kapasitas membuat himpunan kabel yang boleh dipakai bergantung pada K - jadi mengelompokkan query berdasarkan K bisa membantu.

    return 0;
}
