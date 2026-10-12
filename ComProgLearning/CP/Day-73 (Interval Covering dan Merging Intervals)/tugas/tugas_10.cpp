/*
============================================================
📋 TUGAS 10: Menghapus Interval Berlebih
============================================================
Source: Latihan mandiri
Difficulty: Medium
Topics: Interval termuat

PROBLEM:
Diberikan n interval [l, r]. Sebuah interval disebut BERLEBIH kalau ada interval lain
yang memuatnya seluruhnya (yaitu l lain <= l dan r <= r lain, dan keduanya bukan
interval yang sama).
Cari berapa banyak interval yang TIDAK berlebih.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: l dan r

OUTPUT FORMAT:
Satu bilangan: jumlah interval yang tidak berlebih

CONSTRAINTS:
1 <= n <= 2*10^5, 1 <= l <= r <= 10^9

SAMPLE INPUT 1:
4
1 4
3 6
2 8
1 4

SAMPLE OUTPUT 1:
1
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Urut menurut l menaik, dan bila l sama urut r MENURUN. Setelah itu satu sapuan cukup. Kasus interval yang identik persis butuh perhatian khusus — sampel sengaja memuatnya.

    return 0;
}
