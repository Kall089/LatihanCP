/*
============================================================
✅ Solution 3: Rute Pendakian Terbaik
============================================================
🔑 TEKNIK: KADANE  (Day 35)
Complexity: Time O(N) | Space O(1)

📖 FRASA PENENTUNYA: "rentang BERURUTAN" + "total paling besar" +
   ada nilai negatif + tidak ada batas panjang. Empat sinyal itu bersamaan
   hanya menunjuk Kadane.

   Ceritanya soal pendakian, tapi struktur soalnya identik dengan
   "maximum subarray sum". Mengupas cerita adalah setengah pekerjaan.

⚠️ SAMPLE 2 ADALAH INTI SOAL INI. Semua ruas menurun, dan pendaki WAJIB
   menempuh minimal satu ruas. Jawabannya -1 (ruas yang paling sedikit
   merugikan), bukan 0. Kalau kodemu mencetak 0, kamu memakai versi
   "boleh kosong" untuk soal yang melarangnya.

⚠️ 2*10^5 x 10^9 = 2*10^14 -> long long.

🩺 DIAGNOSIS DIRI:
   Mencetak 0 di sample 2      -> best diinisialisasi 0. Ulangi Day 35.
   Tidak mengenali sama sekali -> latih pengupasan cerita; baca ulang
                                  Day 35B bagian B.3 "kalimat penyamaran"
   Mencoba sliding window      -> ada elemen negatif, window tidak sah
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

    ll best = LLONG_MIN, cur = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cur = max(x, cur + x);
        best = max(best, cur);
    }

    cout << best << "\n";
    return 0;
}
