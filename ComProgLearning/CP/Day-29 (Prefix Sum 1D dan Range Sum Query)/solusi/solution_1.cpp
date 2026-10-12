/*
============================================================
✅ Solution 1: Range Sum Query Statis
============================================================
Approach: Prefix sum dengan konvensi n+1
Complexity: Time O(n + q) | Space O(n)
Key Insight: Bayar O(n) sekali untuk memasang "patokan kilometer", lalu setiap
             pertanyaan jarak menjadi satu pengurangan. Kuncinya bukan
             rumusnya, melainkan konvensi pre[0] = 0 yang menghapus semua
             percabangan tepi.

📖 PENJELASAN PENDEKATAN:
1. pre berukuran n+1, pre[0] = 0, pre[i+1] = pre[i] + a[i].
2. Query L, R (1-based) -> jumlah = pre[R] - pre[L-1].
   Perhatikan: dengan input 1-based, rumusnya justru lebih rapi lagi,
   karena pre[i] sudah berarti "jumlah i elemen pertama".
3. Kumpulkan output ke satu string agar tidak kena I/O lambat.

⚠️ TIPE DATA: 2*10^5 elemen bernilai sampai 10^9 menghasilkan 2*10^14.
   int jebol di 2.1*10^9. long long wajib, bukan opsional.

⚠️ I/O: dengan q = 2*10^5, cout << ... << '\n' per baris masih aman, tapi
   membangun string sekali lebih cepat dan jadi kebiasaan baik.

🔄 ALTERNATIVE APPROACHES:
- Naif per query: O(n*q) = 4*10^10 -> TLE.
- Segment tree: O(log n) per query. Berlebihan; baru perlu kalau ADA UPDATE.
- Sparse table: bisa, tapi untuk sum tidak ada keuntungan sama sekali.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // Step 1: prefix sum, ukuran n+1
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pre[i + 1] = pre[i] + x;
    }

    // Step 2: jawab query
    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;                 // 1-based
        out += to_string(pre[r] - pre[l - 1]);
        out += '\n';
    }
    cout << out;

    return 0;
}
