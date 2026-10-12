/*
============================================================
✅ Solution 2: Segmen Terpendek yang Cukup
============================================================
Approach: Sliding window ukuran variabel, varian TERPENDEK
Complexity: Time O(n) | Space O(n)
Key Insight: Kerangkanya identik dengan Solution 1, tetapi baris pencatatan
             jawaban pindah KE DALAM while. Alasannya: untuk "terpanjang"
             kita ingin window SELEBAR mungkin yang masih layak, sedangkan
             untuk "terpendek" kita ingin window SESEMPIT mungkin yang masih
             layak -- jadi kita catat tepat sebelum ia berhenti layak.

📖 PENJELASAN PENDEKATAN:
1. sum += a[r].
2. Selama window MASIH layak (sum >= S):
   catat panjangnya, lalu susutkan.
3. Kalau best tidak pernah berubah, berarti tidak ada jawaban -> cetak 0.

⚠️ JANGAN mencetak INT_MAX. Ini kesalahan yang sering lolos dari pengujian
   lokal karena sampel biasanya punya jawaban.

⚠️ TIPE DATA: S bisa 10^14 dan a[i] sampai 10^9, jadi sum wajib long long.
   Panjangnya sendiri muat di int.

VERIFIKASI SAMPEL 1 (a = [2,3,1,2,4,3], S = 7):
   r=3: sum=8 >= 7 -> catat 4, susut -> sum=6
   r=4: sum=10     -> catat 4, susut -> sum=7 -> catat 3, susut -> sum=6
   r=5: sum=9      -> catat 3, susut -> sum=7 -> catat 2, susut -> sum=3
   best = 2, yaitu [4,3]  ✓

🔄 ALTERNATIVE APPROACHES:
- Prefix sum + binary search: O(n log n), bekerja juga untuk elemen positif.
- Binary search on answer (Day 50): tebak panjangnya, cek dengan window
  ukuran tetap. O(n log n) -- berlebihan di sini tapi pola yang berguna.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll S;
    cin >> n >> S;
    vector<ll> a(n);
    for (ll& v : a) cin >> v;

    int l = 0, best = INT_MAX;
    ll sum = 0;

    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum >= S) {                 // selama MASIH layak
            best = min(best, r - l + 1);   // catat SEBELUM menyusut
            sum -= a[l];
            l++;
        }
    }

    cout << (best == INT_MAX ? 0 : best) << '\n';
    return 0;
}
