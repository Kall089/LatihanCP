/*
============================================================
✅ Solution 5: Persegi Panjang Terbesar di Peta Ladang
============================================================
Approach: histogram per baris + monotonic stack
Complexity: Time O(R*C) | Space O(C)
Key Insight: setiap persegi panjang subur punya SATU baris paling bawah.
             Kunci baris bawah itu, dan masalahnya berubah menjadi "persegi
             panjang terbesar di dalam histogram" - persis pola "kunci satu
             ujung" yang sama dengan Kadane.

📖 PENJELASAN PENDEKATAN:
1. tinggi[j] = banyaknya petak subur berturut-turut ke ATAS dari baris
   sekarang pada kolom j. Diperbarui inkremental: subur -> +1, berbatu -> 0.
2. Untuk tiap baris, jalankan luasHistogram(tinggi).
3. Di dalam luasHistogram, monotonic stack menaik memberi kita, untuk tiap
   batang, batas kiri dan kanan pertama yang LEBIH PENDEK. Lebar maksimum
   batang itu adalah jarak antara kedua batas tersebut.

⚠️ TRIK SENTINEL: tambahkan batang bertinggi 0 di ujung kanan. Karena tidak
   ada yang lebih pendek dari 0, stack dijamin kosong di akhir loop, sehingga
   kamu tidak perlu menulis loop pembersihan terpisah. Setengah bug di soal
   histogram berasal dari loop pembersihan yang ditulis buru-buru.

⚠️ RUMUS LEBAR: saat batang di st.top() di-pop oleh batang ke-i,
     tinggi = h[st.top()], lalu pop
     lebar  = st.empty() ? i : (i - st.top() - 1)
   Perhatikan -1 nya. Salah satu karakter di sini menghasilkan jawaban yang
   nyaris benar, yang justru paling sulit didebug.

⚠️ DUPLIKAT: memakai `>=` atau `>` pada kondisi pop sama-sama menghasilkan
   LUAS yang benar di soal ini, meski persegi panjang yang terpilih berbeda.
   Jangan tergoda mengoptimasi ini sebelum yang dasar jalan.

🔄 ALTERNATIVE APPROACHES:
- DP dengan tiga array (tinggi, kiri, kanan) per baris: O(R*C) juga, tanpa
  stack eksplisit. Setara, sebagian orang merasa lebih mudah diingat.
- Brute force semua pasangan baris: O(R^2 * C), TLE pada R = 1000.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll luasHistogram(vector<int>& h) {
    int m = h.size();
    h.push_back(0);              // sentinel
    stack<int> st;
    ll best = 0;
    for (int i = 0; i <= m; i++) {
        while (!st.empty() && h[st.top()] >= h[i]) {
            ll tinggi = h[st.top()];
            st.pop();
            ll lebar = st.empty() ? i : (i - st.top() - 1);
            best = max(best, tinggi * lebar);
        }
        st.push(i);
    }
    h.pop_back();
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    cin >> r >> c;
    vector<string> g(r);
    for (int i = 0; i < r; i++) cin >> g[i];

    vector<int> tinggi(c, 0);
    ll best = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            tinggi[j] = (g[i][j] == '.') ? tinggi[j] + 1 : 0;
        best = max(best, luasHistogram(tinggi));
    }

    cout << best << "\n";
    return 0;
}
