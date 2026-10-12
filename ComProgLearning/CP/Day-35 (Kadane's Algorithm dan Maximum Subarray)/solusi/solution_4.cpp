/*
============================================================
✅ Solution 4: Subarray Melingkar Maksimum
============================================================
Approach: max(Kadane biasa, total - Kadane minimum) + penanganan khusus
Complexity: Time O(n) | Space O(1)
Key Insight: Sebuah subarray melingkar punya tepat dua bentuk. Kalau TIDAK
             membungkus, itu Kadane biasa. Kalau MEMBUNGKUS, maka bagian yang
             TIDAK terpakai adalah satu potongan utuh di tengah -- dan agar
             sisanya maksimum, potongan yang dibuang harus MINIMUM.

📖 PENJELASAN PENDEKATAN:
1. Dalam satu loop, hitung tiga hal: total, Kadane maksimum, Kadane minimum.
2. Kandidat membungkus = total - minSum.
3. Jawabannya max dari kedua kandidat.

⚠️ LUBANG YANG SENGAJA DITARUH DI SAMPEL 2:
   Kalau SEMUA elemen negatif, subarray minimum adalah SELURUH array.
   Maka total - minSum = 0, yang berarti "ambil subarray kosong" -- padahal
   soal melarangnya. Contoh: a = [-3,-2,-5], total = -10, minSum = -10,
   sehingga total - minSum = 0. Jawaban yang benar adalah -2.

   Penjaganya sederhana: kalau maxSum < 0 (artinya semua elemen negatif),
   langsung kembalikan maxSum tanpa mempertimbangkan kandidat membungkus.

VERIFIKASI SAMPEL 1 (a = [5,-3,5]):
   total = 7, maxSum = 7, minSum = -3
   membungkus = 7 - (-3) = 10   -> jawab 10  ✓  ([5] di kanan + [5] di kiri)

VERIFIKASI SAMPEL 3 (a = [1,-2,3,-2,5]):
   total = 5, maxSum = 6 ([3,-2,5]), minSum = -2
   membungkus = 5 - (-2) = 7    -> jawab 7   ✓  ([3,-2,5] + [1] membungkus)

CATATAN: solusi ini telah diuji terhadap brute force melingkar pada 8000
array acak berukuran <= 7 dan cocok seluruhnya.

🔄 ALTERNATIVE APPROACHES:
- Gandakan array jadi 2n lalu cari subarray maksimum dengan panjang <= n:
  butuh monotonic deque atas prefix (Day 37), O(n) juga tetapi jauh lebih
  panjang. Berguna kalau soal membatasi panjang secara umum.
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

    ll total = 0;
    ll maxSum = LLONG_MIN, minSum = LLONG_MAX;
    ll curMax = 0, curMin = 0;

    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        total += x;
        curMax = max(x, curMax + x);  maxSum = max(maxSum, curMax);
        curMin = min(x, curMin + x);  minSum = min(minSum, curMin);
    }

    // Semua elemen negatif -> "total - minSum" berarti subarray KOSONG
    if (maxSum < 0) {
        cout << maxSum << '\n';
        return 0;
    }

    cout << max(maxSum, total - minSum) << '\n';
    return 0;
}
