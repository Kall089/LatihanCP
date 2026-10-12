#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 3: Membuktikan Dijkstra Gagal pada Bobot Negatif
 *
 * Graf BERARAH yang bobotnya BOLEH NEGATIF, dan dijamin TIDAK punya siklus
 * negatif. Cetak DUA bilangan pada satu baris:
 *   (a) jarak 1 -> N menurut Dijkstra versi "kunci" (setiap simpul diproses
 *       paling banyak sekali, ditandai saat dipop),
 *   (b) jarak 1 -> N yang BENAR (pakai Bellman-Ford atau DP topologis).
 * Cetak -1 untuk yang tak terjangkau.
 *
 * Tujuannya bukan mendapat jawaban benar dengan Dijkstra, melainkan MELIHAT
 * perbedaannya sendiri.
 *
 * Batas: 1 <= N <= 1000, 1 <= M <= 5000, |w| <= 10^6
 *
// Test Case 1 (Dijkstra SALAH):
// Input:
// 4 4
// 1 2 1
// 1 3 2
// 2 4 5
// 3 2 -4
// Output:
// 6 3
// (Dijkstra mengunci simpul 2 pada jarak 1 lalu memberi 6; jawaban benar 3
//  lewat 1-3-2-4 = 2 + (-4) + 5)
//
// Test Case 2 (semua non-negatif, keduanya sama):
// Input:
// 3 3
// 1 2 4
// 2 3 4
// 1 3 9
// Output:
// 8 8
//
// Test Case 3 (edge negatif tidak berpengaruh, keduanya sama):
// Input:
// 3 2
// 1 2 5
// 2 3 -1
// Output:
// 4 4
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // (a) Dijkstra dengan array bool terkunci[] yang di-set saat POP,
    //     dan tetangga yang sudah terkunci TIDAK direlaksasi lagi.
    // (b) Bellman-Ford: ulangi relaksasi semua edge sebanyak N-1 kali.
    // Bandingkan hasilnya dan pahami dari mana selisihnya datang.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
