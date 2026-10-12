/*
============================================================
📋 TUGAS 08: Handshaking Lemma Verification
============================================================
Source: Original
Difficulty: Easy
Topics: degree sequence, handshaking lemma, graph theory

PROBLEM:
Diberikan T graph berbeda. Untuk tiap graph dengan n node dan m edge,
hitung degree sequence, verifikasi handshaking lemma (sum degree = 2×E),
dan cetak apakah jumlah node ber-degree ganjil adalah genap (selalu true).

INPUT FORMAT:
- Baris 1: integer T
- Untuk setiap graph:
  - Baris 1: dua integer n dan m
  - m baris berikutnya: dua integer u v (edge, 1-indexed)

OUTPUT FORMAT:
- Untuk graph ke-i: "Graph i: sum_deg=S, 2*E=2M VALID/INVALID, odd_count=K (genap/ganjil)"

CONSTRAINTS:
- 1 ≤ T ≤ 10
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5

SAMPLE INPUT 1:
2
3 3
1 2
2 3
1 3
3 2
1 2
1 3

SAMPLE OUTPUT 1:
Graph 1: sum_deg=6, 2*E=6 VALID, odd_count=0 (genap)
Graph 2: sum_deg=4, 2*E=4 VALID, odd_count=2 (genap)

NOTE: Handshaking lemma selalu berlaku untuk undirected graph.
      Jumlah node ber-degree ganjil selalu genap (ini juga properti yang selalu true).
      Kasus "INVALID" tidak mungkin untuk graph yang dibangun dari edge list normal,
      tapi bisa terjadi jika input graph langsung berupa degree sequence.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int g = 1; g <= T; g++) {
        int n, m;
        cin >> n >> m;

        vector<int> deg(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            deg[u]++; deg[v]++;
        }

        long long sumDeg = 0;
        int oddCount = 0;
        for (int i = 1; i <= n; i++) {
            sumDeg += deg[i];
            if (deg[i] % 2 != 0) oddCount++;
        }

        long long twoE = 2LL * m;
        bool valid = (sumDeg == twoE);

        cout << "Graph " << g << ": sum_deg=" << sumDeg
             << ", 2*E=" << twoE
             << ' ' << (valid ? "VALID" : "INVALID")
             << ", odd_count=" << oddCount
             << ' ' << (oddCount % 2 == 0 ? "(genap)" : "(ganjil)")
             << '\n';
    }
    return 0;
}
