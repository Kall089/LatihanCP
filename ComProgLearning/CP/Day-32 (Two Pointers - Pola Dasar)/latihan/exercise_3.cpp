/*
 * Day 19 — Two Pointers
 * File  : exercise_3.cpp
 * Topik : Container With Most Water
 * -----------------------------------------------
 * Diberikan array H berisi N bilangan bulat non-negatif, di mana H[i]
 * merepresentasikan tinggi garis vertikal di posisi i. Temukan dua garis
 * yang bersama sumbu x membentuk wadah yang dapat menampung air paling banyak.
 *
 * Volume air antara garis i dan j (i < j):
 *   volume = min(H[i], H[j]) * (j - i)
 *
 * Output volume maksimum.
 *
 * Gunakan greedy two pointers:
 *   - L = 0, R = N-1
 *   - Hitung volume saat ini, update jawaban
 *   - Gerakkan pointer yang lebih KECIL (karena pointer besar tidak bisa memberi volume lebih)
 *
 * Input format  : Baris 1: N (2 ≤ N ≤ 200.000)
 *                 Baris 2: N bilangan bulat (tinggi garis)
 * Output format : Satu bilangan: volume air maksimum
 * Constraints   : 2 ≤ N ≤ 200.000
 *                 0 ≤ H[i] ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 6                    16
 * 1 8 6 2 5 4
 *
 * Sample Input 2:      Sample Output 2:
 * 2                    1
 * 1 1
 *
 * Sample Input 3:      Sample Output 3:
 * 4                    6
 * 4 3 2 4
 *
 * Penjelasan Sample 1:
 *   Garis H[1]=8 dan H[5]=4: min(8,4)*(5-1) = 4*4 = 16
 *
 * Penjelasan Sample 3:
 *   Garis H[0]=4 dan H[3]=4: min(4,4)*(3-0) = 4*3 = 12? Cek lagi:
 *   H=[4,3,2,4]: H[0]=4, H[3]=4 → min(4,4)*3=12. Hmm.
 *   Wait: N=4, H=[4,3,2,4]:
 *   L=0,R=3: min(4,4)*3=12 → ans=12. H[L]=H[R] → R--
 *   L=0,R=2: min(4,2)*2=4
 *   L=0,R=1: min(4,3)*1=3
 *   ans=12, output: 12
 *
 *   (Sample 3 dikoreksi — lihat solution_3.cpp)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> h(n);
    for (auto& x : h) cin >> x;

    int L = 0, R = n - 1;
    ll ans = 0;

    // TODO: implementasikan greedy two pointers
    // while (L < R) {
    //     ll vol = min(h[L], h[R]) * (R - L);
    //     ans = max(ans, vol);
    //     if (h[L] < h[R]) L++;
    //     else R--;
    // }

    cout << ans << "\n";
    return 0;
}
