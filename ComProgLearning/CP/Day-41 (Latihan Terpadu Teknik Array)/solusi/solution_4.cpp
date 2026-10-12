/*
============================================================
✅ Solution 4: Jendela dengan Rentang Nilai Terbatas
============================================================
Approach: sliding window variabel + dua monotonic deque
Complexity: Time O(N) amortisasi | Space O(N)
Key Insight: window-nya melebar dan menyempit, jadi kamu butuh struktur yang
             bisa melaporkan max dan min pada window BERJALAN. Satu deque
             menurun memberi maksimum, satu deque menaik memberi minimum.

📖 PENJELASAN PENDEKATAN:
1. Perluas r satu per satu. Sebelum memasukkan indeks r:
     dqMax: buang dari belakang semua yang nilainya <= a[r]
     dqMin: buang dari belakang semua yang nilainya >= a[r]
2. Sekarang a[dqMax.front()] adalah maksimum window, a[dqMin.front()] minimum.
3. Selama selisihnya > K, majukan l. Setiap kali l maju, buang dari DEPAN
   kedua deque semua indeks yang < l.
4. best = max(best, r - l + 1).

⚠️ SIMPAN INDEKS, BUKAN NILAI. Kalau deque berisi nilai, kamu tidak bisa tahu
   mana yang sudah keluar dari window. Ini bug struktural, bukan sekadar
   kelalaian.

⚠️ URUTAN OPERASI di dalam loop while: cek kondisi -> majukan l -> bersihkan
   deque. Kalau kamu membersihkan sebelum memajukan l, front-nya bisa salah.

⚠️ KENAPA O(N) MESKI ADA WHILE BERSARANG: setiap indeks masuk ke tiap deque
   tepat sekali dan keluar paling banyak sekali. Total operasi <= 4N.

⚠️ K = 0: berarti seluruh window harus bernilai sama persis. Sample 3
   ([3,3,3,1,3], K=0) menguji ini.

🔄 ALTERNATIVE APPROACHES:
- multiset<int> untuk window: jauh lebih pendek, O(N log N), aman untuk
  N <= 2*10^5. Layak dipakai di kontes kalau waktu mepet.
- sparse table + binary search pada panjang: O(N log N), lebih rumit.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dqMax, dqMin;   // berisi INDEKS
    int l = 0, best = 0;

    for (int r = 0; r < n; r++) {
        while (!dqMax.empty() && a[dqMax.back()] <= a[r]) dqMax.pop_back();
        dqMax.push_back(r);
        while (!dqMin.empty() && a[dqMin.back()] >= a[r]) dqMin.pop_back();
        dqMin.push_back(r);

        while (a[dqMax.front()] - a[dqMin.front()] > k) {
            l++;
            if (dqMax.front() < l) dqMax.pop_front();
            if (dqMin.front() < l) dqMin.pop_front();
        }

        best = max(best, r - l + 1);
    }

    cout << best << "\n";
    return 0;
}
