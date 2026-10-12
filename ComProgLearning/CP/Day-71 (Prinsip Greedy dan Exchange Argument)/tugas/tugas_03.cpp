/*
============================================================
📋 TUGAS 03: Towers
============================================================
Source: CSES 1073
Difficulty: Medium
Topics: Greedy, multiset

PROBLEM:
Kamu diberi n kubus dalam urutan tertentu, masing-masing dengan ukuran tersendiri.
Kubus diproses satu per satu dan harus diletakkan di atas sebuah menara yang kubus
teratasnya LEBIH BESAR dari kubus baru, atau memulai menara baru.
Cari jumlah menara minimum di akhir.

INPUT FORMAT:
Baris 1: n
Baris 2: n ukuran kubus dalam urutan pemrosesan

OUTPUT FORMAT:
Satu bilangan: jumlah menara minimum

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= ukuran <= 10^9

SAMPLE INPUT 1:
5
3 8 2 1 5

SAMPLE OUTPUT 1:
2
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Untuk tiap kubus, letakkan pada menara yang puncaknya PALING PAS (terkecil yang masih lebih besar). Buktikan dulu kenapa ini optimal, lalu cari struktur data untuk mencarinya cepat.

    return 0;
}
