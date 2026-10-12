/*
============================================================
✅ Solution 1: Pemanas Gedung
============================================================
🔑 TEKNIK: DIFFERENCE ARRAY  (Day 31)  + counting (Day 40)
Complexity: Time O(N + Q) | Space O(N)

📖 FRASA PENENTUNYA: "setelah SEMUA perintah selesai".
   Itu berarti tidak ada query di tengah-tengah update. Begitu semua update
   datang lebih dulu, kamu tidak butuh struktur data apa pun - cukup simpan
   SELISIH antar tetangga, dan bayar sekali O(N) di akhir.
   Update naif akan O(N*Q) = 4*10^10 -> TLE.

⚠️ d berukuran N+2 supaya d[R+1] aman saat R = N.
⚠️ Q * V bisa 2*10^14 dan T sampai 10^18 -> long long di mana-mana.
⚠️ Sample 2 (semua ruangan bersuhu 2, T = 3) menjawab 0. Jawaban nol itu sah.

🩺 DIAGNOSIS DIRI:
   Tidak mengenali tekniknya   -> ulangi Day 31
   Mengenali tapi TLE          -> kamu masih mengupdate rentang secara naif
   Jawaban meleset di ujung    -> lupa d[R+1], atau array kurang besar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, q, t;
    cin >> n >> q >> t;

    vector<ll> d(n + 2, 0);
    for (ll i = 0; i < q; i++) {
        ll l, r, v;
        cin >> l >> r >> v;
        d[l] += v;
        d[r + 1] -= v;
    }

    ll run = 0, cnt = 0;
    for (ll i = 1; i <= n; i++) {
        run += d[i];
        if (run >= t) cnt++;
    }

    cout << cnt << "\n";
    return 0;
}
