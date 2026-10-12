/*
============================================================
✅ Solution 6: Kata Sandi Aman
============================================================
Approach: DP di atas KMP automaton
Complexity: Time O(L * m * A) | Space O(m * 26)
Key Insight: "Apakah pola sudah muncul" tidak butuh seluruh riwayat string —
             cukup satu bilangan: sudah cocok berapa huruf awal pola.
             Itulah state automaton. Membangun string huruf demi huruf
             sambil berjalan di automaton mengubah masalah counting string
             menjadi masalah menghitung jalur pada graf state.

📖 PENJELASAN PENDEKATAN:
1. Bangun automaton dari P + '#'. State 0..m-1 = aman, state m = pola muncul.
2. dp[s] = banyaknya string (dari yang sudah dibangun) yang berakhir di state s
   dan belum pernah menyentuh state m.
3. Untuk setiap dari L posisi, coba semua A huruf. Transisi ke aut[s][c].
   Kalau tujuannya m, cabang itu dibuang (kata sandi jadi tidak aman).
4. Jawabannya jumlah seluruh dp setelah L langkah.

Kenapa membuang state m sudah cukup, padahal pola bisa muncul lalu "hilang"
dari state? Karena kita membuang cabang PADA SAAT transisi ke m terjadi.
String apa pun yang memuat P pasti melewati state m tepat pada karakter
terakhir kemunculan pertamanya, dan di titik itu cabangnya sudah dipangkas.

Verifikasi sampel 1 (L=3, A=2, P="aa"):
   total string = 2^3 = 8; yang memuat "aa": aaa, aab, baa -> 3; aman = 5 ✓

🔄 ALTERNATIVE APPROACHES:
- Inklusi-eksklusi: rumit dan mudah salah untuk pola dengan border.
- L sangat besar (10^18): ganti loop dengan perpangkatan matriks m x m,
  menjadi O(m^3 log L).
- Kalau soal minta "HARUS memuat P": jawabannya A^L - hasil di sini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

vector<int> bangunPi(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int L, A;
    cin >> L >> A;
    string p;
    cin >> p;
    int m = p.size();

    // Step 1: automaton
    string pola = p + '#';
    int sz = pola.size();
    vector<int> pi = bangunPi(pola);
    vector<array<int, 26>> aut(sz);
    for (int i = 0; i < sz; i++)
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != pola[i]) aut[i][c] = aut[pi[i - 1]][c];
            else                             aut[i][c] = i + ('a' + c == pola[i]);
        }

    // Step 2: DP atas state aman 0..m-1
    vector<ll> dp(m, 0), nx;
    dp[0] = 1;

    for (int step = 0; step < L; step++) {
        nx.assign(m, 0);
        for (int s = 0; s < m; s++) {
            if (!dp[s]) continue;
            for (int c = 0; c < A; c++) {
                int t = aut[s][c];
                if (t == m) continue;       // pola muncul -> buang
                nx[t] = (nx[t] + dp[s]) % MOD;
            }
        }
        dp.swap(nx);
    }

    // Step 3: total
    ll ans = 0;
    for (ll v : dp) ans = (ans + v) % MOD;
    cout << ans << '\n';

    return 0;
}
