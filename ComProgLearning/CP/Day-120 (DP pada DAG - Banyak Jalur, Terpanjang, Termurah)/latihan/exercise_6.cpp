#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-120 (DP pada DAG - Banyak Jalur, Terpanjang, Termurah)
 * Latihan 6: Jalur Terpanjang yang WAJIB Melewati Simpul K
 *
 * DAG berbobot. Cari jalur 1 -> N terpanjang yang HARUS melewati simpul K.
 * Cetak bobotnya, atau -1 jika tidak ada.
 *
 * Petunjuk: pecah menjadi dua bagian yang saling bebas.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 1 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 5 6 3
// 1 2 3
// 1 3 2
// 2 4 4
// 3 4 1
// 3 5 7
// 4 5 2
// Output:
// 9
// (harus lewat 3: 1-3-5 = 9, atau 1-3-4-5 = 5; ambil 9)
//
// Test Case 2 (K = 4):
// Input:
// 5 6 4
// 1 2 3
// 1 3 2
// 2 4 4
// 3 4 1
// 3 5 7
// 4 5 2
// Output:
// 9
// (1-2-4-5 = 9)
//
// Test Case 3 (K tidak bisa dilewati):
// Input:
// 4 3 3
// 1 2 5
// 2 4 5
// 3 4 5
// Output:
// -1
// (simpul 3 tidak terjangkau dari 1)
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // A = jalur terpanjang 1 -> K   (DP maju di graf asli)
    // B = jalur terpanjang K -> N   (DP di graf TERBALIK dari N, atau DP maju
    //                                dengan sumber K)
    // Jawaban = A + B jika keduanya ada. Jalur gabungan otomatis valid
    // karena grafnya DAG -- tidak mungkin ada simpul terulang.
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
