/*
============================================================
✅ Solution 2: Pasangan Hari Genap
============================================================
🔑 TEKNIK: PREFIX SUM MODULO + COUNTING  (Day 29 + 40)
Complexity: Time O(N + M) | Space O(M)

📖 FRASA PENENTUNYA: "ada berapa periode", bukan "berapa maksimum".
   Kata kerja itu menyingkirkan Kadane sepenuhnya.

   Transformasinya: jumlah a[l..r] habis dibagi M
                <=> P[r+1] dan P[l] bersisa SAMA saat dibagi M.
   Jadi soalnya menjadi "hitung pasangan prefix dengan sisa sama", dan
   itu dijawab dengan menghitung frekuensi tiap sisa.

⚠️ MODULO NEGATIF - INI INTI SAMPLE 3.
   Di C++, (-1) % 2 menghasilkan -1, bukan 1. Kalau kamu memakainya sebagai
   indeks array, program crash atau salah diam-diam.
   Normalkan: pre = ((pre + x) % m + m) % m;

⚠️ cnt[0] = 1 sebelum loop, mewakili prefix kosong. Tanpa itu, periode yang
   dimulai dari hari pertama tidak terhitung.

⚠️ Jawabannya bisa ~2*10^10 -> long long.

🩺 DIAGNOSIS DIRI:
   Memakai Kadane              -> ulangi Day 35 bagian "kapan BUKAN Kadane"
   Benar tanpa negatif, salah dengan negatif -> ulangi modulo, Day 90
   Meleset persis satu golongan -> lupa cnt[0] = 1
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;

    vector<ll> cnt(m, 0);
    cnt[0] = 1;                       // prefix kosong

    ll pre = 0, res = 0;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pre = ((pre + x) % m + m) % m;    // jaga tetap 0..m-1
        res += cnt[pre];
        cnt[pre]++;
    }

    cout << res << "\n";
    return 0;
}
