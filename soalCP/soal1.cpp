/*
 * SOAL: Arvy Menjemur Pakaian
 *
 * Update Solusi (Berdasarkan Feedback User):
 * Menggunakan pendekatan DP Iteratif (Reachability) dengan satu pass 1..N.
 *
 * ALGORITMA:
 * 1. Faktorisasi Prima dari N.
 * 2. Gunakan array DP Boolean (reachability).
 *    dp[i] = true jika nilai i bisa dibentuk dari penjumlahan faktor-faktor
 * prima.
 * 3. Loop dari i = 1 sampai N.
 *    Untuk setiap faktor p, jika dp[i-p] true, maka dp[i] true.
 * 4. Cek dp[M] dan dp[N-M].
 */

#include <bits/stdc++.h>
using namespace std;

int t;
int n, m;
int dp[200005]; // Global array untuk DP

void solve()
{
  // Input N dan M
  scanf("%d%d", &n, &m);

  // 1. Cari Faktor Prima Unik dari N
  vector<int> factors;
  // Loop faktorisasi sesuai referensi (l <= k)
  // Walaupun O(N) worst case, untuk problem ini pass time limit
  for (int l = 2, k = n; l <= k && k > 1; l++)
  {
    if (k % l == 0)
    {
      factors.push_back(l);
      while (k % l == 0)
        k /= l;
    }
  }

  // 2. DP Reachability
  dp[0] = 1; // Base case: 0 selalu bisa dibentuk

  // Loop state 1 sampai N
  for (int i = 1; i <= n; i++)
  {
    dp[i] = 0; // Reset state
    for (int f : factors)
    {
      if (f <= i)
      {
        // Jika i-f bisa dibentuk, maka i juga bisa (tambah faktor f)
        dp[i] |= dp[i - f];
      }
    }
  }

  // Output: M dan N-M harus bisa dibentuk
  printf("%s\n", (dp[m] && dp[n - m] ? "YA" : "TIDAK"));
}

int main()
{
  scanf("%d", &t);
  while (t--)
  {
    solve();
  }
  return 0;
}
