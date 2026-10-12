/*
 * Day 22 — Aritmatika Modular
 * File  : solution_5.cpp
 * Topik : Prefix Sum Modular + Range Query — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Prefix sum yang dinormalisasi + pengurangan modular aman
 *
 * Idea:
 *   pre[i] = (pre[i-1] + A[i]) dinormalisasi ke [0, MOD)
 *   jawab(L,R) = (pre[R] - pre[L-1] + MOD) % MOD
 *
 *   Karena pre[] disimpan sebagai nilai di [0, MOD), selisihnya berada di
 *   rentang (-MOD, MOD). Menambahkan MOD sekali sudah cukup untuk membuatnya
 *   non-negatif, lalu %MOD mengembalikannya ke [0, MOD).
 *
 * INI PITFALL PALING SERING DI CONTEST:
 *   ans = (pre[R] - pre[L-1]) % MOD;         ← ❌ bisa negatif → WA
 *   ans = (pre[R] - pre[L-1] + MOD) % MOD;   ← ✅
 *
 * A[i] boleh negatif, jadi saat membangun prefix juga harus dinormalisasi:
 *   pre[i] = ((pre[i-1] + A[i]) % MOD + MOD) % MOD
 *
 * Verifikasi sample 1: A=[1,2,3,4,5]
 *   pre = [0, 1, 3, 6, 10, 15]
 *   (1,3): pre[3]-pre[0] = 6-0 = 6                  ✓
 *   (2,4): pre[4]-pre[1] = 10-1 = 9  (A[2..4] = 2+3+4 = 9)  ✓
 *   (1,5): pre[5]-pre[0] = 15                       ✓
 *
 * Verifikasi sample 2: A=[-5, 3, -2, 10]
 *   pre[1] = -5 → norm = 1000000002
 *   pre[2] = 1000000002 + 3 = 1000000005
 *   pre[3] = 1000000005 - 2 = 1000000003
 *   pre[4] = 1000000003 + 10 = 1000000013 % MOD = 6
 *   (1,2): pre[2]-pre[0] = 1000000005 - 0 = 1000000005   ✓ (= -2 mod MOD)
 *   (1,4): pre[4]-pre[0] = 6                              ✓
 *   (2,4): pre[4]-pre[1] = 6 - 1000000002 = -999999996
 *          + MOD = 11                                     ✓ (3-2+10 = 11)
 *          ← tanpa +MOD hasilnya negatif! Inilah gunanya.
 *
 * Complexity: O(N) preprocessing + O(1) per query → O(N + Q). Space O(N).
 *
 * Edge cases:
 *   - L == R           → jawaban = A[L] mod MOD (dinormalisasi)
 *   - L == 1           → pre[0] = 0, aman
 *   - Semua A[i] negatif → semua prefix ternormalisasi, tetap benar
 *   - Jumlah ≡ 0 mod MOD → output 0, bukan MOD
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // Step 1: Bangun prefix sum modular (1-indexed), ternormalisasi ke [0, MOD)
    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        x %= MOD;                              // A[i] bisa negatif → sisa negatif
        pre[i] = ((pre[i - 1] + x) % MOD + MOD) % MOD;
    }

    // Step 2: Jawab tiap query dengan pengurangan modular yang aman
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        ll ans = (pre[r] - pre[l - 1] + MOD) % MOD;   // +MOD WAJIB
        cout << ans << "\n";
    }

    return 0;
}
