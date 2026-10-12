/*
============================================================
✅ Solution 2: Kenapa Sum Tidak Bisa
============================================================
Approach: Sparse table untuk min/max, PREFIX SUM untuk jumlah
Complexity: Time O(n log n + q) | Space O(n log n)
Key Insight: Dua sifat yang berbeda menghasilkan dua teknik yang berbeda,
             dan keduanya saling melengkapi -- bukan bersaing.

             IDEMPOTEN  : op(x, x) = x   -> boleh tumpang tindih -> sparse table
             PUNYA INVERS: ada "pengurangan" -> boleh dikurangkan -> prefix sum

             min dan max IDEMPOTEN tetapi tidak punya invers.
             sum dan XOR punya INVERS tetapi tidak idempoten.

📖 DEMONSTRASI KENAPA SPARSE TABLE GAGAL UNTUK SUM:
   a = [1, 2, 3, 4, 5], query [0, 4], len = 5, k = 2 (blok panjang 4)
       blok kiri  : sum a[0..3] = 10
       blok kanan : sum a[1..4] = 14
       "jawab"    : 10 + 14 = 24
       BENAR      : 15
   Selisihnya 9 = 2+3+4, yaitu daerah tumpang tindih a[1..3] yang terhitung
   DUA KALI. Untuk min, terhitung dua kali tidak berpengaruh; untuk sum,
   ia merusak jawabannya.

   Inilah arti "idempoten" secara konkret, dan kenapa ia menjadi SYARAT
   sparse table -- bukan sekadar istilah teknis.

📖 KENAPA PREFIX SUM GAGAL UNTUK MIN:
       min(a[0..r]) dan min(a[0..l-1]) tidak memberitahu min(a[l..r]).
       a = [5, 1, 9]: min(a[0..2]) = 1, min(a[0..0]) = 5.
       Tidak ada operasi yang "membuang" pengaruh 5 dari hasil 1.
   Sum punya invers (pengurangan); min tidak.

⚠️ TIPE DATA: jumlah 2*10^5 elemen bernilai 10^9 mencapai 2*10^14.
   long long WAJIB untuk prefix sum. min dan max tetap boleh int.

⚠️ MEMORI: dua sparse table (min dan max) berarti 2 x n log n = 28 MB untuk
   n = 2*10^5. Ditambah prefix sum long long (1.6 MB). Masih aman, tetapi
   kalau n lebih besar pertimbangkan menggabungkan keduanya dalam satu tabel
   berisi pair, atau memakai segment tree.

VERIFIKASI SAMPEL (a = [1,2,3,4,5], query [1,5] = seluruh array):
   min 1, max 5, sum 15   ✓
   Perhatikan bahwa sum dihitung lewat pre[5] - pre[0] = 15 - 0, sama sekali
   tidak menyentuh sparse table.

🔄 ALTERNATIVE APPROACHES:
- Segment tree tunggal yang menyimpan (min, max, sum) sekaligus: O(n) memori,
  O(log n) query, dan mendukung update. Pilihan yang lebih baik kalau ada
  update atau kalau memori ketat.
- Disjoint sparse table: varian yang membagi di titik tengah alih-alih
  tumpang tindih, sehingga bekerja untuk operasi ASOSIATIF apa pun termasuk
  sum. Build O(n log n), query O(1), tanpa syarat idempoten. Jarang
  dibutuhkan karena prefix sum sudah menyelesaikan sum dengan O(n).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    int K = lg[n] + 1;

    // IDEMPOTEN -> sparse table
    vector<vector<int>> mn(K, vector<int>(n)), mx(K, vector<int>(n));
    mn[0] = a;
    mx[0] = a;
    for (int k = 1; k < K; k++)
        for (int i = 0; i + (1 << k) <= n; i++) {
            mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
            mx[k][i] = max(mx[k - 1][i], mx[k - 1][i + (1 << (k - 1))]);
        }

    // PUNYA INVERS -> prefix sum (jauh lebih sederhana, O(n) memori)
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        int k = lg[r - l + 1];

        out += to_string(min(mn[k][l], mn[k][r - (1 << k) + 1]));
        out += ' ';
        out += to_string(max(mx[k][l], mx[k][r - (1 << k) + 1]));
        out += ' ';
        out += to_string(pre[r + 1] - pre[l]);               // bukan sparse table
        out += '\n';
    }
    cout << out;

    return 0;
}
