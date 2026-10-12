/*
============================================================
✅ Solution 6: Pasangan Palindrom Bersinggungan (CF 17E)
============================================================
Approach: Manacher + difference array + komplemen
Complexity: Time O(n) | Space O(n)
Key Insight: Menghitung pasangan yang BERSINGGUNGAN itu sulit; menghitung
             pasangan yang TERPISAH itu mudah, karena "terpisah" berarti
             satu berakhir sebelum yang lain dimulai — satu titik pemisah
             yang unik. Jadi: jawaban = total pasangan - pasangan terpisah.

📖 PENJELASAN PENDEKATAN:
1. Manacher versi dua array untuk mendapat d1 (ganjil) dan d2 (genap).
   T = jumlah seluruh palindrom = sum(d1) + sum(d2).
2. Total pasangan = T * (T - 1) / 2.
3. cntStart[i] = berapa palindrom MULAI di i, cntEnd[i] = berapa BERAKHIR di i.
   Untuk pusat ganjil di c dengan k = d1[c]: palindromnya S[c-t..c+t], t=0..k-1
     -> start berada di rentang [c-k+1, c]      (rentang, bukan satu titik)
     -> end   berada di rentang [c, c+k-1]
   Untuk pusat genap sebelum i dengan k = d2[i]: palindromnya S[i-t..i+t-1], t=1..k
     -> start di [i-k, i-1]
     -> end   di [i, i+k-1]
   Semua ini adalah PENAMBAHAN RENTANG. Menandai satu per satu = O(n^2) -> TLE.
   Pakai difference array (Day 31): dua operasi O(1) per pusat, satu sapuan di akhir.
4. Pasangan terpisah = sum atas j dari cntEnd[j] * (jumlah cntStart[i] untuk i > j).
   Hitung suffix sum cntStart sekali, lalu satu loop.
5. Jawaban = (total pasangan - terpisah) mod 51123987.

⚠️ MODULUS 51123987 BUKAN PRIMA yang nyaman. Jangan menghitung invers 2.
   Sebagai gantinya, bagi 2 SEBELUM modulo: dari T dan T-1, salah satunya
   pasti genap — bagi yang genap itu, baru kalikan secara modular.

⚠️ OVERFLOW: T bisa mencapai ~2*10^12 untuk n = 2*10^6. T*(T-1) akan meluap
   bahkan di long long (4*10^24), makanya pembagian 2 harus dilakukan lebih dulu
   DAN kedua faktor di-mod sebelum dikalikan.
   Untuk langkah 4, cntEnd[j] <= n dan suffix sum <= T, jadi produknya bisa
   mencapai 4*10^18 — sudah dekat batas long long. Mod dulu keduanya.

VERIFIKASI "aa":
   palindrom: "a"(0,0), "a"(1,1), "aa"(0,1)  -> T = 3, total pasangan = 3
   terpisah: hanya pasangan (a di 0, a di 1) -> 1
   jawaban = 3 - 1 = 2  ✓

VERIFIKASI "babb":
   palindrom: b(0), a(1), b(2), b(3), bab(0..2), bb(2..3)  -> T = 6
   total pasangan = 15
   terpisah: pasangan yang tidak beririsan sama sekali = 9
   jawaban = 15 - 9 = 6  ✓

🔄 ALTERNATIVE APPROACHES:
- Eertree + counting: bisa, tapi lebih panjang dan tidak lebih cepat.
- Hashing + binary search per posisi: O(n log n), probabilistik, dan soal ini
  punya batas n = 2*10^6 sehingga faktor log terasa.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 51123987;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    n = s.size();

    // ── Manacher dua array ───────────────────────────────
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) { l = i - k; r = i + k; }
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) { l = i - k - 1; r = i + k; }
    }

    // ── Total palindrom ──────────────────────────────────
    ll T = 0;
    for (int i = 0; i < n; i++) T += d1[i] + d2[i];

    // ── Sebarkan kontribusi lewat difference array ───────
    vector<ll> dStart(n + 2, 0), dEnd(n + 2, 0);
    auto tambah = [&](vector<ll>& d, int a, int b) {   // += 1 pada [a, b]
        if (a > b) return;
        d[a]++; d[b + 1]--;
    };
    for (int c = 0; c < n; c++) {
        int k = d1[c];
        if (k > 0) { tambah(dStart, c - k + 1, c); tambah(dEnd, c, c + k - 1); }
    }
    for (int i = 0; i < n; i++) {
        int k = d2[i];
        if (k > 0) { tambah(dStart, i - k, i - 1); tambah(dEnd, i, i + k - 1); }
    }

    vector<ll> cntStart(n, 0), cntEnd(n, 0);
    ll run = 0;
    for (int i = 0; i < n; i++) { run += dStart[i]; cntStart[i] = run; }
    run = 0;
    for (int i = 0; i < n; i++) { run += dEnd[i];   cntEnd[i]   = run; }

    // ── Pasangan terpisah: end di j, start di > j ────────
    vector<ll> sufStart(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) sufStart[i] = (sufStart[i + 1] + cntStart[i]) % MOD;

    ll terpisah = 0;
    for (int j = 0; j < n; j++)
        terpisah = (terpisah + (cntEnd[j] % MOD) * sufStart[j + 1]) % MOD;

    // ── Total pasangan = T*(T-1)/2, bagi 2 SEBELUM modulo ─
    ll a = T, b = T - 1;
    if (a % 2 == 0) a /= 2; else b /= 2;
    ll totalPasangan = (a % MOD) * (b % MOD) % MOD;

    ll ans = ((totalPasangan - terpisah) % MOD + MOD) % MOD;
    cout << ans << '\n';
    return 0;
}
