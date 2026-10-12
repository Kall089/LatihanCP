/*
============================================================
✅ Solution 3: Keuntungan Saham Sekali Beli
============================================================
Approach: Kadane pada array selisih (varian BOLEH KOSONG)
Complexity: Time O(n) | Space O(1)
Key Insight: Keuntungan dari beli di hari x dan jual di hari y sama dengan
             JUMLAH selisih harian d[x+1..y]. Jadi soal ini adalah soal
             maximum subarray yang sama persis dengan Exercise 1, hanya
             berpakaian berbeda. Kebiasaan bertanya "bagaimana kalau saya
             lihat selisihnya?" mengubah soal yang terlihat baru menjadi
             soal yang sudah kamu kuasai.

📖 PENJELASAN PENDEKATAN:
1. d[i] = harga[i] - harga[i-1] untuk i = 1..n-1.
2. Jawabannya subarray maksimum dari d, dengan subarray BOLEH KOSONG
   (karena kita boleh tidak bertransaksi sama sekali).
3. Karena boleh kosong: best = 0 dan cur = max(0, cur + d[i]).

⚠️ Perhatikan bahwa di sini "boleh kosong" adalah pilihan yang BENAR,
   berbeda dari Solution 1. Pertanyaan "boleh kosong atau tidak?" harus
   dijawab dari teks soal setiap kali, bukan dari kebiasaan.

CARA PANDANG ALTERNATIF (tanpa array selisih sama sekali):
   simpan harga terendah sejauh ini, lalu
       best = max(best, harga[i] - terendah);
       terendah = min(terendah, harga[i]);
   Ini persis versi prefix-sum dari Kadane, diterapkan langsung pada harga.
   Banyak orang menemukan versi ini lebih alami untuk soal saham.

VERIFIKASI SAMPEL 1 (harga = [7,1,5,3,6,4]):
   d = [-6, 4, -2, 3, -2]
   Kadane boleh kosong: 4 + (-2) + 3 = 5   ✓  (beli di hari 2, jual di hari 5)

🔄 ALTERNATIVE APPROACHES:
- Versi "harga terendah sejauh ini": O(n), tanpa membentuk array d.
- Kalau boleh bertransaksi DUA kali: butuh DP empat state (LeetCode 123).
- Kalau boleh transaksi tak terbatas: greedy, jumlahkan semua d[i] positif.
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
    vector<ll> h(n);
    for (ll& v : h) cin >> v;

    // Kadane pada selisih, varian BOLEH KOSONG (best mulai dari 0)
    ll best = 0, cur = 0;
    for (int i = 1; i < n; i++) {
        ll d = h[i] - h[i - 1];
        cur = max(0LL, cur + d);
        best = max(best, cur);
    }

    cout << best << '\n';
    return 0;
}
