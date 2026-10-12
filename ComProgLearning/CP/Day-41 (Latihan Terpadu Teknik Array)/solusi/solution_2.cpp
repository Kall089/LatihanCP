/*
============================================================
✅ Solution 2: Pengecatan Pagar
============================================================
Approach: difference array + satu kali sapuan penghitungan
Complexity: Time O(N + Q) | Space O(N)
Key Insight: kalau semua update datang SEBELUM semua query, kamu tidak perlu
             struktur data canggih. Simpan selisih antar tetangga: satu update
             rentang cuma menyentuh dua posisi.

📖 PENJELASAN PENDEKATAN:
1. d[L] += V dan d[R+1] -= V untuk setiap perintah. O(1) per perintah.
2. Setelah semua perintah, jalankan prefix sum berjalan pada d untuk
   mendapatkan nilai asli tiap papan.
3. Selagi menjalankan prefix sum itu, langsung lacak maksimum dan
   hitungannya - tidak perlu sapuan kedua.

⚠️ UKURAN ARRAY: d harus berukuran N+2 (indeks 0..N+1) supaya d[R+1] aman
   saat R = N. Ini bug paling sering di difference array.

⚠️ OVERFLOW: 2*10^5 perintah x 10^9 = 2*10^14. Wajib long long.

⚠️ MELACAK MAKSIMUM DAN HITUNGAN SEKALIGUS:
   kalau nilai > best  -> best = nilai, cnt = 1
   kalau nilai == best -> cnt++
   Urutan dua cabang ini penting; kalau dibalik, cnt tidak pernah direset.

🔄 ALTERNATIVE APPROACHES:
- Fenwick tree dengan range update: benar, tapi O((N+Q) log N) dan jauh lebih
  panjang. Berlebihan kalau tidak ada query di tengah.
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

    vector<ll> d(n + 2, 0);
    for (int i = 0; i < q; i++) {
        int l, r; ll v;
        cin >> l >> r >> v;
        d[l] += v;
        d[r + 1] -= v;
    }

    ll run = 0, best = LLONG_MIN, cnt = 0;
    for (int i = 1; i <= n; i++) {
        run += d[i];
        if (run > best) { best = run; cnt = 1; }
        else if (run == best) cnt++;
    }

    cout << best << " " << cnt << "\n";
    return 0;
}
