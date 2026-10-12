/*
============================================================
✅ Solution 4: Menunggu Hari Lebih Panas
============================================================
🔑 TEKNIK: MONOTONIC STACK  (Day 36)
Complexity: Time O(N) amortisasi | Space O(N)

📖 FRASA PENENTUNYA: "untuk SETIAP i, cari yang TERDEKAT".
   Di seluruh blok Day 29-41, frasa itu hanya menunjuk satu teknik.

   Stack menyimpan indeks hari yang BELUM menemukan hari lebih panas.
   Nilainya otomatis menurun dari bawah ke atas. Saat hari baru datang dan
   lebih panas dari puncak stack, puncak itu baru saja mendapat jawabannya.

⚠️ KENAPA BOLEH MEMBUANG: begitu hari j mendapat jawabannya dari hari i,
   hari j tidak akan pernah dibutuhkan lagi - hari i lebih panas DAN lebih
   dekat bagi semua hari sesudahnya. Ia tertutupi selamanya.

⚠️ SAMPLE 4 ([5,5,5] -> 0 0 0): soal meminta LEBIH TINGGI, bukan lebih
   tinggi atau sama. Jadi kondisi pop harus a[st.top()] < a[i], memakai <
   yang ketat. Kalau kamu menulis <=, hari kembar akan saling menjawab dan
   hasilnya 1 1 0 - salah.

⚠️ Simpan INDEKS di stack, bukan suhu. Jawabannya jarak, jadi kamu butuh
   posisinya.

🩺 DIAGNOSIS DIRI:
   Menulis O(N^2) dua loop     -> ulangi Day 36
   Salah hanya di sample 4     -> < vs <= pada nilai kembar
   Stack berisi nilai          -> bug struktural, bukan kelalaian
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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> res(n, 0);
    stack<int> st;                    // berisi INDEKS, suhunya menurun

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {   // < ketat, bukan <=
            res[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    // sisa di stack tetap 0 (tidak pernah ada hari lebih panas)

    for (int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];
    return 0;
}
