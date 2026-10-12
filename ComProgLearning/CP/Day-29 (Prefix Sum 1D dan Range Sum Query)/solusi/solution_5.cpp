/*
============================================================
✅ Solution 5: Titik Pemotongan Paling Seimbang
============================================================
Approach: Prefix sum + satu sapuan
Complexity: Time O(n) | Space O(n)
Key Insight: Begitu kamu punya prefix, "jumlah bagian kanan" tidak perlu
             dihitung ulang -- ia selalu total dikurangi bagian kiri.
             Selisihnya |pre[i] - (total - pre[i])| = |2*pre[i] - total|,
             sehingga seluruh masalah menjadi satu loop tanpa struktur apa pun.

📖 PENJELASAN PENDEKATAN:
1. Bangun pre, ambil total = pre[n].
2. Untuk setiap titik potong i (artinya kiri berisi i elemen pertama):
   selisih = |2*pre[i] - total|.
3. Batas i adalah 1 sampai n-1, BUKAN 0 sampai n, karena kedua bagian
   harus tidak kosong. Ini satu-satunya jebakan di soal ini.

VERIFIKASI SAMPEL 1 (a = [3,1,4,1,5], total = 14):
   i=1: |6-14|  = 8
   i=2: |8-14|  = 6
   i=3: |16-14| = 2   <- minimum
   i=4: |18-14| = 4
   jawab 2  ✓

⚠️ OVERFLOW: 2*pre[i] bisa mencapai 4*10^14. Tetap muat di long long,
   tapi kalau kamu memakai int di mana pun dalam rantai ini, jebol.

🔄 ALTERNATIVE APPROACHES:
- Menghitung ulang jumlah kanan tiap iterasi: O(n^2), tidak perlu.
- Dua pointer dari kiri dan kanan: bisa, tapi tidak lebih sederhana.
- Kalau soal memperbolehkan bagian kosong, cukup ubah batas loop jadi 0..n.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pre[i + 1] = pre[i] + x;
    }

    ll total = pre[n];
    ll best = LLONG_MAX;

    // i = banyaknya elemen di bagian kiri; kedua bagian harus tidak kosong
    for (int i = 1; i <= n - 1; i++)
        best = min(best, llabs(2 * pre[i] - total));

    cout << best << '\n';
    return 0;
}
