/*
============================================================
✅ Solution 2: Hitung Bilangan Genap dalam Rentang
============================================================
Approach: Prefix count pada array 0/1
Complexity: Time O(n + q) | Space O(n)
Key Insight: Prefix sum tidak harus menjumlahkan nilainya. Ubah dulu
             pertanyaan apa pun yang berbentuk "berapa banyak elemen yang
             memenuhi P" menjadi array berisi 0 dan 1, lalu jumlahkan.
             Pola ini jauh lebih sering terpakai daripada prefix sum biasa.

📖 PENJELASAN PENDEKATAN:
1. cnt[i+1] = cnt[i] + (a[i] genap ? 1 : 0).
2. Jawaban rentang [L, R] 1-based = cnt[R] - cnt[L-1].

⚠️ KEGENAPAN BILANGAN NEGATIF: di C++, (-3) % 2 bernilai -1, bukan 1.
   Jadi `x % 2 == 1` GAGAL mendeteksi ganjil negatif. Cara aman:
     x % 2 == 0        -> benar untuk genap, termasuk negatif
     abs(x) % 2 == 1   -> benar untuk ganjil
     (x & 1)           -> pada representasi two's complement juga benar,
                          tapi hanya untuk tipe bertanda yang perilakunya
                          didefinisikan implementasi; pakai % 2 == 0 saja.
   Di solusi ini kita memakai `x % 2 == 0` yang aman untuk semua kasus.

🔄 ALTERNATIVE APPROACHES:
- Naif per query: O(n*q) -> TLE.
- Prefix untuk banyak predikat sekaligus: kalau soal menanyakan beberapa
  kategori (genap, prima, > X), buat satu array prefix per kategori.
- Kalau predikatnya bergantung pada query (misalnya "> X" dengan X berubah),
  prefix count TIDAK cukup -- perlu merge sort tree atau wavelet tree.
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

    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cnt[i + 1] = cnt[i] + (x % 2 == 0 ? 1 : 0);
    }

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;
        out += to_string(cnt[r] - cnt[l - 1]);
        out += '\n';
    }
    cout << out;

    return 0;
}
