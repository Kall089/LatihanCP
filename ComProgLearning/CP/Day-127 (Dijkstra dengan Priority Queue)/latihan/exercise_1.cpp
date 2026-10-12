#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-127 (Dijkstra dengan Priority Queue)
 * Latihan 1: Jarak Terpendek dari Simpul 1
 *
 * Graf BERARAH berbobot non-negatif, N simpul, M edge. Cetak jarak terpendek
 * dari simpul 1 ke setiap simpul 1..N, dipisah spasi. Cetak -1 untuk simpul
 * yang tidak terjangkau.
 *
 * Batas: 1 <= N <= 10^5, 1 <= M <= 2*10^5, 0 <= w <= 10^9
 *
// Test Case 1:
// Input:
// 4 5
// 1 2 6
// 1 3 2
// 3 2 3
// 2 4 1
// 3 4 5
// Output:
// 0 5 2 6
//
// Test Case 2 (ada yang tak terjangkau):
// Input:
// 4 2
// 1 2 3
// 3 4 3
// Output:
// 0 3 -1 -1
//
// Test Case 3 (bobot besar, uji overflow):
// Input:
// 3 2
// 1 2 1000000000
// 2 3 1000000000
// Output:
// 0 1000000000 2000000000
 */

void solve() {
    // TODO: Tulis implementasi di sini
    // long long WAJIB. INF = LLONG_MAX/4, bukan LLONG_MAX.
    // priority_queue<pair<ll,int>, vector<...>, greater<...>>
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
